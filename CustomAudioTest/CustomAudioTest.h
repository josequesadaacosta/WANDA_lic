/*
  Custom Block for WANDA tests
  Header file
*/

#ifndef CustomAudioTest_h_
#define CustomAudioTest_h_

#include "Arduino.h"
#include "AudioStream.h"



#include "RF24.h"
#include "nRF24L01.h"


#define PEINE_BLOCK_SAMPLES  64


class CustomAudioTest : public AudioStream
{
#if defined(KINETISK)
  public:
    CustomAudioTest(void) : AudioStream(1, inputQueueArray), radio(28, 39)
    {
      __disable_irq();
      this->peine = new int8_t [PEINE_BLOCK_SAMPLES];
      this->transmitterSetup();
    }

    ~CustomAudioTest()
    {
      __enable_irq();
    }
    virtual void update(void);
    
    void gain(float gain) {
      if (gain > 32767.0f) gain = 32767.0f;
      else if (gain < -32767.0f) gain = -32767.0f;
      multiplier = gain * 65536.0f;
    }

    
    int16_t getBlockDataAt(int i)
    {
      return block->data[i];
    }

    int8_t getPeineAt(int i)
    {
      return peine[i];
    }

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


  private:
    audio_block_t *inputQueueArray[1];
    int16_t multiplier;
    int8_t *peine;
    audio_block_t *block;
    
    int downsample;
    RF24 radio;
#endif
};



template<class T>
static void printArray(T* t, int size)
{
  for (int i = 0; i < size; i++)
  {
    Serial.print(t[i]);
    Serial.print(" ");
  }
  Serial.println();
}
#endif
