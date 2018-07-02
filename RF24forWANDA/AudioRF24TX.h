// WANDA Transmitter header.

#ifndef AudioRF24TX_h_
#define AudioRF24TX_h_

#include "Arduino.h"
#include "AudioStream.h"
#include "SPI.h"
#include "RF24.h"

#define PEINE_BLOCK_SAMPLES  64

typedef struct peine_block_struct{
	unsigned char ref_count;
	unsigned char memory_pool_index;
	unsigned char reserved1;
	unsigned char reserved2;
  uint8_t data[PEINE_BLOCK_SAMPLES];
} peine_block_t;

class AudioRF24TX : public AudioStream
{
#if defined(KINETISK)
public:
  AudioRF24TX(int cePin, int csnPin) : AudioStream(1, inputQueueArray) {
    ce_pin = cePin;
    csn_pin = csnPin;

    //radio configuration
    RF24 radio(ce_pin, csn_pin);

    //Definition of pin modes
    pinMode(ce_pin,OUTPUT);
    pinMode(csn_pin,OUTPUT);

    // Initialize SPI bus
    SPI.begin();

    radio.ce(LOW);
    radio.csn(HIGH);

    // Disable Acknowledgement packets
    radio.setAutoAck(0);

    // Disable dynamic payloads, data rate at 2MBPS, 8 bits for CRC
    radio.setPALevel(RF24_PA_LOW);
    radio.setDataRate(RF24_2MBPS);
    radio.setCRCLength(RF24_CRC_8);
    radio.write_register(DYNPD,0);
    radio.setChannel(76);

    //Empty buffers
    radio.flush_rx();
    radio.flush_tx();
  }

  //Update function happens every 2.9 ms, or 128 samples.
  virtual void update(void);

  //In the case of C++, an empty parameter list in either a declaration
  //or a definition indicates that the function takes no arguments,
  //and is equivalent to using a parameter list of void.
  void transmitterSetup(void)
  {
    //choose the PTX pipe address from the following variable list:
    //not declaring in an array to save mem.
    uint64_t PTXpipe = 0x7878787878LL;
    //uint64_t PTXpipe = 0xB3B4B5B6F1LL;
    //uint64_t PTXpipe = 0xB3B4B5B6CDLL;
    //uint64_t PTXpipe = 0xB3B4B5B6A3LL;
    //uint64_t PTXpipe = 0xB3B4B5B60FLL;
    //uint64_t PTXpipe = 0xB3B4B5B605LL;

    //Set radio in transmission mode
    radio.stopListening();
    radio.openWwritingPipe(PTXpipe);
  }


private:
	// inputQueueArray: array of audio_block pointers used for the inputs. It is a must if
	//the audio block has any inputs. If it does not need inputs, then AudioStream(0, NULL).
  audio_block_t *inputQueueArray[1];
  int ce_pin;
  int csn_pin;
  int downsample;
	audio_block_t *block;
	peine_block_t *peine;
#endif
};

#endif
