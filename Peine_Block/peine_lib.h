/*
PEINE_BLOCK_SAMPLES = 64 samples

*/

#ifndef peine_lib_h
#define peine_lib_h


#include "Arduino.h"
#include "AudioStream.h"
#include "math.h"

#define PEINE_BLOCK_SAMPLES  64
#define max_norm 1023 //Defines maximum compression value for normalization in method


//typedef bitset<8> BYTE;


typedef struct peine_block_struct{
	unsigned char ref_count;
	unsigned char memory_pool_index;
	unsigned char reserved1;
	unsigned char reserved2;
  uint8_t data[PEINE_BLOCK_SAMPLES];
} peine_block_t;

class ModifyDataRateZeros : public AudioStream {
	public:
	ModifyDataRateZeros(void): AudioStream(1,inputQueueArray){};
	
	void rate(int i){
		downsample = i;
	}	

	
	virtual void update(void);
	
	private:
	audio_block_t *inputQueueArray[1];
	int downsample;
	peine_block_t *peine;
};

class ModifyDataRateBuffer : public AudioStream {
	public:
	ModifyDataRateBuffer(void): AudioStream(1,inputQueueArray){};
	
	void rate(int i){
		downsample = i;
	}	

	
	virtual void update(void);
	
	private:
	audio_block_t *inputQueueArray[1];
	int downsample;
	peine_block_t *peine;
};

class ModifyDataRateLinear : public AudioStream {
	public:
	ModifyDataRateLinear(void): AudioStream(1,inputQueueArray){};
	
	void rate(int i){
		downsample = i;
	}

	
	virtual void update(void);
	
	private:
	audio_block_t *inputQueueArray[1];
	peine_block_t *peine;
	int downsample;
};

class Compressor : public AudioStream
{
	#if defined(KINETISK)
	public:
		Compressor(void)
	  : AudioStream(1, inputQueueArray) {}
	virtual void update(void);
	void threshold(float thres) {
		level = thres ;
	}

	private:
	audio_block_t *inputQueueArray[1];
	int16_t level;
	#endif
};


#endif
