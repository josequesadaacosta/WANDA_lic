#ifndef AudioOutputRF24TX_h_
#define AudioOutputRF24TX_h_

#include "Arduino.h"
#include "AudioStream.h"
#include "RF24.h"
#include "nRF24L01.h"
#include "utility/dspinst.h"
#include "SPI.h"

#define NEW_BLOCK_SAMPLES  64


class AudioOutputRF24TX : public AudioStream
{
  public:
      AudioOutputRF24TX(void);
      virtual void update(void);
      void transmitterSetup();
    private:
      audio_block_t *inputQueueArray[1];
      RF24 radio;
};


#endif
