
/*
Custom Block for WANDA tests
*/


#include "CustomAudioTest.h"


static void multiplyGain(int16_t *data, int32_t mult)
{
  uint32_t *p = (uint32_t *)data;
  const uint32_t *end = (uint32_t *)(data + AUDIO_BLOCK_SAMPLES);
  do {
    uint32_t tmp32 = *p; // read 2 samples from *data
    int32_t val1 = signed_multiply_32x16b(mult, tmp32);
    int32_t val2 = signed_multiply_32x16t(mult, tmp32);
    val1 = signed_saturate_rshift(val1, 16, 0);
    val2 = signed_saturate_rshift(val2, 16, 0);
    *p++ = pack_16b_16b(val2, val1);
  } while (p < end);
}

void CustomAudioTest::update()
{
  audio_block_t *block;
  unsigned int channel;
  uint32_t pos;
  int32_t mult;

  pos = position;
	if (pos == 0) {
		// output is silent
		block = receiveReadOnly();
		if (block) release(block);
		return;
	} else if (pos == 0xFFFFFFFF) {
		// output is 100%
		block = receiveReadOnly();
		if (!block) return;
		transmit(block);
		release(block);
		return;
	}
	block = receiveWritable();
	if (!block) return;
  mult = multiplier[channel];  // gain * 256.0f, defined in .h
  multiplyGain(block->data, mult);  // audio_block_t ->	int16_t data[AUDIO_BLOCK_SAMPLES]
  position = pos;
  transmit(block);
  release(block);
}
