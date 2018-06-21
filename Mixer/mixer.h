#ifndef peine_lib_h
#define peine_lib_h

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <Math.h>
#endif

#ifndef __ASSEMBLER__
class channel{
	
	//Create private constant with max
	//Set real gain parameters 
	
	float gain(){
		//Analog read?
		//Get max value, normalize, multiply times 50, substract 10 [-10,40]
		//Check min = 0
		//float a = 10^(value/20);
		return a;
	}
	
	float hp(){
		//Analog read?
		//Get max value, normalize, multiply times 50, substract 10 [-10,40]
		//Check min = 0
		//float a = 10^(value/20);
		return a;
	}
    
    float bpgain(){
		//Analog read?
		//Get max value, normalize, multiply times 50, substract 10 [-10,40]
		//Check min = 0
		//float a = 10^(value/20);
		return a;
	}
	
	uint16_t bpfreq(){
		//Analog read?
		uint16_t a;
		return a;
	}
	
	float lp(){
		//Analog read?
		//Get max value, normalize, multiply times 50, substract 10 [-10,40]
		//Check min = 0
		//float a = 10^(value/20);
		return a;
	}

	float pan(){
		//Analog read?
		//Get max value and normalize
		//Check min = 0
		float a;
		return a;
	}
	
	float r(){
		float a = this.pan();
		return a;
	}
	
	float l(){	
		float a = 1-this.pan();
		return a;
	}
	
	float level(){
		//Analog read?
		//Get max value, normalize, multiply times 32767.0
		//Check min = 0
		return a;
	}
}


class channel{
	
	//Create private constant with max
	//Set real gain parameters 
	
	float hp(){
		//Analog read?
		//Get max value, normalize, multiply times 50, substract 10 [-10,40]
		//Check min = 0
		//float a = 10^(value/20);
		return a;
	}
    
    float bpgain(){
		//Analog read?
		//Get max value, normalize, multiply times 50, substract 10 [-10,40]
		//Check min = 0
		//float a = 10^(value/20);
		return a;
	}
	
	uint16_t bpfreq(){
		//Analog read?
		uint16_t a;
		return a;
	}
	
	float lp(){
		//Analog read?
		//Get max value, normalize, multiply times 50, substract 10 [-10,40]
		//Check min = 0
		//float a = 10^(value/20);
		return a;
	}
	
	float level(){
		//Analog read?
		//Get max value, normalize, multiply times 32767.0
		//Check min = 0
		return a;
	}
}

class AudioStream;
class AudioConnection;



class peine_lib_h
{
	public:
	peine_lib(){};
	
	peine_block_t * decimate(audio_block_t *block, int downsample);	
	audio_block_t * interp_zeros(peine_block_t *peine, int upsample);
	audio_block_t * interp_linear(peine_block_t *peine, uint16_t upsample);
	
	private:
	audio_block_t *block;
	int downsample;
	peine_block_t *peine;
	int upsample;
	uint16_t upsample;
	}

