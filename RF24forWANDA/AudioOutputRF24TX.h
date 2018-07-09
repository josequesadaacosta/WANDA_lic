// WANDA Transmitter header.

#ifndef AudioOutputRF24TX_h_
#define AudioOutputRF24TX_h_

#include "AudioStream.h"
#include "RF24.h"
#include "nRF24L01.h"
#include <Arduino.h>


#define PEINE_BLOCK_SAMPLES  64

class AudioOutputRF24TX : public AudioStream
{
  public:
    AudioOutputRF24TX() : AudioStream(1, inputQueueArray), radio(28, 39)
    {
      this->peine = new int8_t [PEINE_BLOCK_SAMPLES];
      this->prueba = new int8_t [32];
    }

    //Update function happens every 2.9 ms, or 128 samples.
    virtual void update(void);

    //transmitter setup
    void transmitterSetup()
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

    bool updated;
    bool sent;

    int16_t getTransmitterData(int i)
    {
      return block->data[i];
    }

    int8_t getTransmitterData1(int i)
    {
      return peine[i];
    }

    int8_t* getTransmitterPrueba()
    {
      return prueba;
    }



  private:
    // inputQueueArray: array of audio_block pointers used for the inputs. It is a must if
    //the audio block has any inputs. If it does not need inputs, then AudioStream(0, NULL).
    audio_block_t *inputQueueArray[1];
    int8_t *peine;
    int8_t *prueba;
    //int8_t peine[PEINE_BLOCK_SAMPLES];
    audio_block_t *block;
    int downsample;
    RF24 radio;
};

#endif
