/*
PEINE_BLOCK_SAMPLES = 64 samples

*/

#ifndef peine_lib_h
#define peine_lib_h

//#include "stdio.h"  // for NULL
//#include "string.h" // for memcpy
//#include "Audio.h"
//#include "SD.h"
#include "Arduino.h"
#include "AudioStream.h"
//#include "SerialFlash.h"
//#include "RF24.h"
//#include "kinetis.h"


//#ifndef PEINE_BLOCK_SAMPLES
//#if defined(__MK20DX128__) || defined(__MK20DX256__) || defined(__MK64FX512__) || defined(__MK66FX1M0__)
#define PEINE_BLOCK_SAMPLES  64


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


#endif
