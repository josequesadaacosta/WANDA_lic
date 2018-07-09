// WANDA Transmitter header.

#ifndef AudioInputRF24RX_h_
#define AudioInputRF24RX_h_

#include "AudioStream.h"
#include "RF24.h"
#include "nRF24L01.h"
#include <Arduino.h>

#ifndef PEINE_BLOCK_SAMPLES
#define PEINE_BLOCK_SAMPLES  64
#endif

class AudioInputRF24RX : public AudioStream
{
public:
   AudioInputRF24RX() : AudioStream(0, NULL), radio(28, 39)
   {
	   this->peine = new int8_t [PEINE_BLOCK_SAMPLES];
	   this->prueba = new int8_t [32];
   }
   
  
	//Update function happens every 2.9 ms, or 128 samples.
	virtual void update(void);

	//Set radio in reception mode
	void receiverSetup()
	{
		//radio setup, disable dynamic payloads, sets channel, flushes rx and tx buffers
		radio.begin();

		//Disable Acknowledgement packets
		radio.setAutoAck(0);

		//data rate at 2MBPS, 8 bits for CRC
		radio.setPALevel(RF24_PA_LOW);
		radio.setDataRate(RF24_2MBPS);
		radio.setCRCLength(RF24_CRC_8);
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

	bool updated;
	bool doneR1;
    bool doneR2;
	
	int16_t getReceiverData(int i)
	{
		return block->data[i];
	}

	int8_t getReceiverData1(int i)
	{
		return peine[i];
	}
	
	int8_t* getReceiverPrueba()
	{
		return prueba;
	}
	
	private:
	  // inputQueueArray: array of audio_block pointers used for the inputs. It is a must if
	  //the audio block has any inputs. If it does not need inputs, then AudioStream(0, NULL).
	  RF24 radio;
	  audio_block_t *block;
 	  int8_t *peine;
	  int8_t *prueba;
	  //int8_t peine[PEINE_BLOCK_SAMPLES];
	  int downsample;
};

#endif
