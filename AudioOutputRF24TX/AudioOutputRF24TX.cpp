#include "AudioOutputRF24TX.h"


AudioOutputRF24TX::AudioOutputRF24TX(void) : AudioStream(1, inputQueueArray), radio(28, 39)
{
  SPI.setMOSI(7);
  SPI.setMISO(12);
  SPI.setSCK(14);
  SPI.begin();
}

void AudioOutputRF24TX::transmitterSetup()
{
  //choose the PTX pipe address from the following variable list:
  const uint64_t PTXpipe = 0x7878787878LL;
  //const uint64_t PTXpipe = 0xB3B4B5B6F1LL;
  //const uint64_t PTXpipe = 0xB3B4B5B6CDLL;
  //const uint64_t PTXpipe = 0xB3B4B5B6A3LL;
  //const uint64_t PTXpipe = 0xB3B4B5B60FLL;
  //const uint64_t PTXpipe = 0xB3B4B5B605LL;

  //radio setup, disable dynamic payloads, sets channel, flushes rx and tx buffers
  radio.begin();

  // Disable Acknowledgement packets
  radio.setAutoAck(0);

  //data rate at 2MBPS, 8 bits for CRC
  radio.setDataRate(RF24_2MBPS);
  //radio.setCRCLength(RF24_CRC_8);
  radio.setRetries(0, 0);
  
  radio.openWritingPipe(PTXpipe);
  radio.stopListening(); 
}


void AudioOutputRF24TX::update()
{
  audio_block_t *block;

  block = this->receiveReadOnly();
  
  if (!(block)) return;

  uint16_t audio[64];

  for(int i = 0; i < 64; i++){
    audio[i] = block->data[i*2];
  }

   __disable_irq();

  for(int i = 0; i < 4; i++){
      radio.write(&audio[i*16], sizeof(audio)/4);
  }
  

  __enable_irq();
  
    
  transmit(block);
  release(block);
}
