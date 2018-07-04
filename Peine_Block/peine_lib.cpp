//Library for decimation and interpolation. 

#include "peine_lib.h"
#include "AudioStream.h"

//Downsamples an audio_block_t into a peine_block_t, add an antialiasing filter before 
//implementing to prevent aliasing.
//Downsample has to be a natural int number that satisfies AUDIO_BLOCK_SAMPLES/downsample
static void decimate(audio_block_t *block, peine_block_t *peine, int downsample){
	
	int i = 0;
	
	while(i<PEINE_BLOCK_SAMPLES){
		peine->data[i] = static_cast<int8_t>(block->data[downsample*i]>>8);
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
			block->data[i] = static_cast<int>(peine->data[i/downsample]<<8);
		}else{
			block->data[i] = 0;
		}		
		i++;
	}
}

//Interpolates a peine_block_t into an audio_block_t adding zeros, add a low pass filter with an aprox
//25kHz cutoff frequency to have an appropiate output.
//Upsample has to be a natural int number that satisfies PEINE_BLOCK_SAMPLES/downsample
static void interp_buffer(audio_block_t *block, peine_block_t *peine, int downsample){

	int i = 0;
	
	while(i<AUDIO_BLOCK_SAMPLES){
		if(i%downsample == 0){
			block->data[i] = static_cast<uint16_t>(peine->data[i/downsample]<<8);
		}else{
			block->data[i] = block->data[i-1];
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
	
	while(i < PEINE_BLOCK_SAMPLES-1){

		block->data[downsample*i] = (static_cast<uint16_t>(peine->data[i])<<8);
		block->data[downsample*i+downsample] = (static_cast<uint16_t>(peine->data[i+1])<<8);
		
		int j = 1;
		
		while(j < downsample){
			
			block->data[i+j] = static_cast<int16_t>((((block->data[i+downsample])-(block->data[i]))*(i+j)/downsample)+((block->data[i+downsample])*-i/downsample)+((block->data[i])*(i+downsample)/downsample));
			j++;
		}
					
		i++;
	}
}

static void compress(audio_block_t *block, int16_t level)
{
	int i = 0;
	int ratio = (int)pow(10,((1/5)/20)); //Converts a 1:5 compression ratio to linear
	level = (int)pow(10, ((((1-level/max_norm)*50)-40)/20));
	
	
	while(i<AUDIO_BLOCK_SAMPLES){
		
		if(20*log10(block->data[i]) >= level){
			block->data[i] = block->data[i]*ratio;
		}
		i++;
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

void ModifyDataRateBuffer::update(){
	audio_block_t *block;
	peine_block_t peine;

	block = receiveWritable();
	if (!block) return;
	decimate(block, &peine , downsample);
	interp_buffer(block, &peine, downsample);
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

void Compressor::update()
{
  audio_block_t *block;

  block = receiveWritable();
  if (!block) return;
  compress(block, level);  // audio_block_t ->	int16_t data[AUDIO_BLOCK_SAMPLES]
  transmit(block);
  release(block);
}
