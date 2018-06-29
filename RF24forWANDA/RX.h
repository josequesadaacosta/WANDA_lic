// WANDA Transmitter header.

#ifndef RX_h_
#define RX_h_

#include "Arduino.h"
#include "AudioStream.h"
#include "SPI.h"
#include "RF24.h"

class RX : public AudioStream
{
#if defined(KINETISK)
public:
  RX(int cePin, int csnPin)
  : AudioStream(1, inputQueueArray) {
    ce_pin = cePin;
    csn_pin = csnPin;
  }
  virtual void update(void);

private:
  audio_block_t *inputQueueArray[1];
  //int16_t multiplier;
  int ce_pin;
  int csn_pin;
#endif
};

#endif
