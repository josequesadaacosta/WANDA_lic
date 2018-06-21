/*
Library for decimation and interpolation. 


#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <RF24.h>
*/
#include "peine_lib.h"

//Downsamples an audio_block_t into a peine_block_t, add an antialiasing filter before 
//implementing to prevent aliasing.
//Downsample has to be a natural int number that satisfies AUDIO_BLOCK_SAMPLES/downsample
peine_block_t * decimate(audio_block_t *block,int downsample){
	
	//agregar update
	
	block = recieveWritable();
	int i = 0;
	peine_block_t *peine;
	
	
	while(i<PEINE_BLOCK_SAMPLES){
		peine->data[i] = static_cast<uint8_t>(block->data[downsample*i]);
		i++;
	}
	
	return *peine;

}

//Interpolates a peine_block_t into an audio_block_t adding zeros, add a low pass filter with an aprox
//25kHz cutoff frequency to have an appropiate output.
//Upsample has to be a natural int number that satisfies PEINE_BLOCK_SAMPLES/downsample
audio_block_t * interp_zeros(peine_block_t *peine, int upsample){
	
	//Encontrar metodo para leer del radio
	//RF24 rad(0, 0);
	//rad.openReadingPipe() meter parametros
	//rad.startListening();
	
	
	audio_block_t *block;
	int i = 0;
	
	while(i<AUDIO_BLOCK_SAMPLES){
		if(i%upsample == 0){
			block->data[i] = static_cast<uint16_t>(peine->data[i]);
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
audio_block_t * interp_linear(peine_block_t *peine,uint16_t upsample){
	
	//Encontrar metodo para leer del radio
	//RF24 rad(0, 0);
	//rad.openReadingPipe() meter parametros
	//rad.startListening();
	
	audio_block_t *block;
	uint16_t i = 0;
	
	while(i < AUDIO_BLOCK_SAMPLES-upsample){

		block->data[i] = static_cast<uint16_t>(peine->data[i]);
		block->data[i+upsample] = static_cast<uint16_t>(peine->data[i+1]);
		
		uint16_t j = 1;
		
		while(j < upsample){
			
			block->data[i+j] = static_cast<uint16_t>(block->data[i+upsample]+(j-i-upsample)*(block->data[i+upsample]-block->data[i])/upsample);
			j++;
		}
					
		i = i + upsample;
	}
}
