//WANDA receiver implementation

#include "RX.h"

static void interp_zeros(audio_block_t *block, peine_block_t *peine, int downsample){

	int i = 0;

	while(i<AUDIO_BLOCK_SAMPLES){
		if(i%downsample == 0){
			block->data[i] = static_cast<uint16_t>(peine->data[i]<<8);
		}else{
			block->data[i] = 0;
		}
		i++;
	}
}

static void interp_linear(audio_block_t *block, peine_block_t *peine, int downsample){

	int i = 0;

	while(i < AUDIO_BLOCK_SAMPLES-downsample){

		block->data[i] = static_cast<uint16_t>(peine->data[i]<<8);
		block->data[i+downsample] = static_cast<uint16_t>(peine->data[i+1]<<8);

		int j = 1;

		while(j < downsample){

			block->data[i+j] = static_cast<uint16_t>((block->data[i+downsample]+(j-i-downsample)*(block->data[i+downsample]-block->data[i])/downsample)<<8);
			j++;
		}

		i = i + downsample;
	}
}


// happens every 2.9 ms (128 samples)
void AudioRF24RX::update()
{
  downsample = 2;

	if(radio.available()){
    radio.read(this->peine->data, 32);
	}

	//convert from peine_block_t to audio_block_t
  interp_zeros(block, peine, downsample);

  //sending to RX's output
  transmit(block);
  release(block);
}
