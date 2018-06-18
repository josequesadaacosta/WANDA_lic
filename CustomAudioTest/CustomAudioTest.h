/*
Custom Block for WANDA tests
Header file
*/

#ifndef CustomAudioTest_h_
#define CustomAudioTest_h_

#include "Arduino.h"
#include "AudioStream.h"

class CustomAudioTest : public AudioStream
{
	#if defined(KINETISK)
	public:
		CustomAudioTest(void)
	  : AudioStream(1, inputQueueArray) {}
	virtual void update(void);
	void gain(float gain) {
		if (gain > 32767.0f) gain = 32767.0f;
		else if (gain < -32767.0f) gain = -32767.0f;
		multiplier = gain * 65536.0f;
	}

	private:
	audio_block_t *inputQueueArray[1];
	int16_t multiplier;
	#endif
};
#endif
