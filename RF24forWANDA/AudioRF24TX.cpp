//WANDA transmitter implementation

#include "TX.h"


static void decimate(audio_block_t *block, peine_block_t *peine, int downsample){

	int i = 0;

	while(i<PEINE_BLOCK_SAMPLES){
		peine->data[i] = static_cast<uint8_t>(block->data[downsample*i]>>8);
		i++;
	}

}

void AudioRF24TX::update()
{
  downsample = 2;

	block = receiveWritable();
	if (!block) return;

  //convert from audio_block_t to peine_block_t
	decimate(block, peine, downsample);

  //transmitting
  radio.startWrite(this->peine->data, 32);
  radio.startWrite((this->peine->data + 32), 32);

  //no more ownership for current block
  release(block);
}
