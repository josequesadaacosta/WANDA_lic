/*
Custom Block for WANDA tests
Header file
*/

#ifndef _CustomAudioTest_H_INCLUDED_
#define _CustomAudioTest_H_INCLUDED_

#include "Arduino.h"
#include "AudioStream.h"

class CustomAudioTest : public AudioStream
{
	public:
		CustomAudioTest(void)
	  : AudioStream(1, inputQueueArray), position(0xFFFFFFFF) {}    //Position function?
	virtual void update(void);
	void gain(unsigned int channel, float gain) {
		if (channel >= 1) return;
		if (gain > 32767.0f) gain = 32767.0f;
		else if (gain < -32767.0f) gain = -32767.0f;
		multiplier[channel] = gain * 65536.0f;
	}

private:
audio_block_t *inputQueueArray[1];
uint32_t position; // 0 = off, 0xFFFFFFFF = on
int16_t multiplier[1];

};

#endif
