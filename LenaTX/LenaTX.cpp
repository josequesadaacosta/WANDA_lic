#include "LenaTX.h"


LenaTX::LenaTX(void) : AudioStream(1, inputQueueArray), radio(28, 39)
{
  __disable_irq();
  this->peine = new int8_t [PEINE_BLOCK_SAMPLES];
  this->transmitterSetup();
}

LenaTX::~LenaTX()
{
  __enable_irq();
}

void LenaTX::gain(float gain)
{
  if (gain > 32767.0f) gain = 32767.0f;
  else if (gain < -32767.0f) gain = -32767.0f;
  multiplier = gain * 65536.0f;
}

int16_t LenaTX::getBlockDataAt(int i)
{
  return block->data[i];
}

int8_t LenaTX::getPeineAt(int i)
{
  return peine[i];
}

void LenaTX::transmitterSetup()
{
  //choose the PTX pipe address from the following variable list:
  //not declaring in an array to save mem.
  const uint64_t PTXpipe = 0x7878787878LL;
  //uint64_t PTXpipe = 0xB3B4B5B6F1LL;
  //uint64_t PTXpipe = 0xB3B4B5B6CDLL;
  //uint64_t PTXpipe = 0xB3B4B5B6A3LL;
  //uint64_t PTXpipe = 0xB3B4B5B60FLL;
  //uint64_t PTXpipe = 0xB3B4B5B605LL;


  //radio setup, disable dynamic payloads, sets channel, flushes rx and tx buffers
  radio.begin();

  // Disable Acknowledgement packets
  radio.setAutoAck(0);

  //data rate at 2MBPS, 8 bits for CRC
  radio.setPALevel(RF24_PA_LOW);
  radio.setDataRate(RF24_2MBPS);
  radio.setCRCLength(RF24_CRC_8);
  radio.setRetries(0, 0);


  radio.stopListening();
  radio.openWritingPipe(PTXpipe);
}

void LenaTX::decimate()
{
  for (int i = 0; i < PEINE_BLOCK_SAMPLES; i++) {
    this->peine[i] = static_cast<int8_t>(this->block->data[this->downsample * i]);
  }
}

void LenaTX::multiplyGain(int16_t *data, int32_t mult)
{
  uint32_t *p = (uint32_t *)data;
  const uint32_t *end = (uint32_t *)(data + AUDIO_BLOCK_SAMPLES);
  do {
    uint32_t tmp32 = *p; // read 2 samples from *data
    int32_t val1 = signed_multiply_32x16b(mult, tmp32); // computes ((a[31:0] * b[15:0]) >> 16)
    int32_t val2 = signed_multiply_32x16t(mult, tmp32); // computes ((a[31:0] * b[31:16]) >> 16)
    val1 = signed_saturate_rshift(val1, 16, 0);  // computes limit((val >> rshift), 2**bits)
    val2 = signed_saturate_rshift(val2, 16, 0);
    *p++ = pack_16b_16b(val2, val1); // computes ((a[15:0] << 16) | b[15:0])
  } while (p < end);
}

void LenaTX::update()
{
  this->block = receiveReadOnly();
  if (!(this->block)) return;

  //this->multiplyGain(this->block->data, this->multiplier);  // audio_block_t ->	int16_t data[AUDIO_BLOCK_SAMPLES]
  this->decimate();


  //  __disable_irq();
  //  this->radio.startWrite(block->data, sizeof(uint8_t)*32);
  //this->radio.startWrite(peine, sizeof(uint8_t)*32);
  //  __enable_irq();
  transmit(block);
  release(block);
}




