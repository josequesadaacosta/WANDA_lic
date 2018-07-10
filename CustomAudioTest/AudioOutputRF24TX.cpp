//WANDA transmitter implementation

#include "AudioOutputRF24TX.h"
#include "AudioStream.h"

/*static void decimate(audio_block_t *block, int8_t *peine, int downsample)
  {

	int i = 0;

	while(i<PEINE_BLOCK_SAMPLES){
		peine[i] = static_cast<int8_t>(block->data[downsample*i]>>8);
		i++;
	}

  }*/

static void decimate(audio_block_t *block, int8_t *peine, int downsample)
{

  for (int i = 0; i < PEINE_BLOCK_SAMPLES; i++) {
    peine[i] = static_cast<int8_t>(block->data[downsample * i]);
  }

}



#include "utility/dspinst.h"


static void multiplyGain(int16_t *data, int32_t mult)
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




void AudioOutputRF24TX::update()
{
  audio_block_t *block;
  uint16_t gain = multiplier;

  block = receiveWritable();
  if (!block) return;

  //multiplyGain(block->data, gain);  // audio_block_t ->  int16_t data[AUDIO_BLOCK_SAMPLES]
  transmit(block);
  release(block);

  
//  downsample = 2;
//  block = receiveReadOnly();
//
//  if (!block) 
//  {
//    Serial.println("Cromé");
//    return;
//  }
//  
//  Serial.println("block =========");
//  printArray(block->data, 128);
//  Serial.println("Peine =========");
//  printArray(peine, 64);
//
//  delay(10000);
//  decimate(block, peine, downsample);
//  this->updated = true;
//  
//  __disable_irq();
//
//  transmit(block);
////  radio.startWrite(peine, sizeof(uint8_t)*32);
//  
//  __enable_irq();
//
//  release(block);
}
