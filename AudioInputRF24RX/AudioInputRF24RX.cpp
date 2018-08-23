#include "AudioInputRF24RX.h"


AudioInputRF24RX::AudioInputRF24RX(void) : AudioStream(0, NULL), radio(28, 39)
{
  SPI.setMOSI(7);
  SPI.setMISO(12);
  SPI.setSCK(14);
  SPI.begin();
}

void AudioInputRF24RX::receiverSetup()
{
  //radio setup, disable dynamic payloads, sets channel, flushes rx and tx buffers
	radio.begin();

	//Disable Acknowledgement packets
	radio.setAutoAck(0);

	//data rate at 2MBPS, 8 bits for CRC
	radio.setDataRate(RF24_2MBPS);
	//radio.setCRCLength(RF24_CRC_8);
    radio.setRetries(0,0);
	
	/*const uint64_t rAddress[] = {0x7878787878LL, 0xB3B4B5B6F1LL, 0xB3B4B5B6CDLL, 0xB3B4B5B6A3LL, 0xB3B4B5B60FLL, 0xB3B4B5B605LL };
	for(int i = 0 ; i < 6 ; i++)
	{
		radio.openReadingPipe(i,rAddress[i]);
	}
	radio.startListening();*/

  const uint64_t address = 0x7878787878LL;
  radio.openReadingPipe(0,address);
  radio.startListening();
}

void LenaTX::myDecimate()
{
  for (int i = 0; i < 128; i++)
  {
    this->peine[i] = static_cast<int8_t>(this->block->data[i * 2]);
  }
}

void AudioInputRF24RX::qwerty()
{
  this->block = allocate();
  for (int i = 0; i < 128; i++)
  {
    block->data[i] = (int16_t)i * 2;
  }

void AudioInputRF24RX::update()
{
  audio_block_t *block;
  //qwerty();
  block = allocate();
  
  if (!(block)) return;

  __disable_irq();

  if (radio.available())
  {

    int16_t audioFull[64];

    for(int i = 0; i < 4; i++){
      radio.read(&audioFull[i*16], sizeof(audioFull)/4);
      delay(1);
    }
        
    for(int i = 0; i < 128; i++){
      if(i%2 == 0){
        block->data[i] = audioFull[i/2];
      }else{
        block->data[i] = (audioFull[(i-1)/2] + audioFull[i/2])/2;
      }
    }
  
  __enable_irq();
  
  transmit(block);
  release(block);
  }
}
