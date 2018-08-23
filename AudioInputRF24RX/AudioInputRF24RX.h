#ifndef AudioInputRF24RX_h_
#define AudioInputRF24RX_h_

#include "Arduino.h"
#include "AudioStream.h"
#include "RF24.h"
#include "nRF24L01.h"
#include "SPI.h"

#define NEW_BLOCK_SAMPLES  64


class AudioInputRF24RX : public AudioStream
{
public:
	AudioInputRF24RX(void);
	virtual void update(void);
	void receiverSetup(); 
  void qwerty();
  
private:
	RF24 radio;
};

#endif
