
/*
  Custom Block for WANDA tests
*/

#include "CustomAudioTest.h"
#include "utility/dspinst.h"


static void multiplyGain(int16_t *data, int32_t mult)
{
  uint32_t *p = (uint32_t *)data;
  const uint32_t *end = (uint32_t *)(data + AUDIO_BLOCK_SAMPLES);
  do {
    uint32_t tmp32 = *p; // read 2 samples from *data
    int32_t val1 = signed_multiply_32x16b(mult, tmp32); // computes ((a[31:0] * b[15:0]) >> 16)
    int32_t val2 = signed_multiply_32x16t(mult, tmp32); // computes ((a[31:0] * b[31:16]) >> 16)
    val1 = signed_saturate_rshift(val1, 16, 0);  // computes limit((val >> rshift), 2**bits)
    val2 = signed_saturate_rshift(val2, 16, 0);
    *p++ = pack_16b_16b(val2, val1); // computes ((a[15:0] << 16) | b[15:0])
  } while (p < end);
}

void CustomAudioTest::update()
{
  audio_block_t *block;
  uint16_t gain = multiplier;

  block = receiveReadOnly();
  if (!block) return;

//  printArray(block->data, 128);

  //multiplyGain(block->data, gain);  // audio_block_t ->	int16_t data[AUDIO_BLOCK_SAMPLES]
  transmit(block);
  release(block);
}





