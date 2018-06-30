//Library for decimation and interpolation. 

#include "peine_lib.h"
#include "AudioStream.h"

//Downsamples an audio_block_t into a peine_block_t, add an antialiasing filter before 
//implementing to prevent aliasing.
//Downsample has to be a natural int number that satisfies AUDIO_BLOCK_SAMPLES/downsample
static void decimate(audio_block_t *block, peine_block_t *peine, int downsample){
	
	int i = 0;
	
	while(i<PEINE_BLOCK_SAMPLES){
		peine->data[i] = static_cast<uint8_t>(block->data[downsample*i]>>8);
		i++;
	}

}

//Interpolates a peine_block_t into an audio_block_t adding zeros, add a low pass filter with an aprox
//25kHz cutoff frequency to have an appropiate output.
//Upsample has to be a natural int number that satisfies PEINE_BLOCK_SAMPLES/downsample
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


//Interpolates a peine_block_t into an audio_block_t getting the samples in between with 
//linear aproximations, add a low pass filter with an aprox 25kHz cutoff frequency 
//to have an appropiate output.
//Upsample has to be a natural int number that satisfies PEINE_BLOCK_SAMPLES/downsample
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


void ModifyDataRateZeros::update(){
	audio_block_t *block;
	peine_block_t peine;

	block = receiveWritable();
	if (!block) return;
	decimate(block, &peine , downsample);
	interp_zeros(block, &peine, downsample);
	transmit(block);
	release(block);
	
}

void ModifyDataRateLinear::update(){
	audio_block_t *block;
	peine_block_t peine;

	block = receiveWritable();
	if (!block) return;
	decimate(block, &peine , downsample);
	interp_linear(block, &peine, downsample);
	transmit(block);
	release(block);
}


