/*
PEINE_BLOCK_SAMPLES = 64 samples

*/

#ifndef peine_lib_h
#define peine_lib_h

//#include "stdio.h"  // for NULL
//#include "string.h" // for memcpy
//#include "Audio.h"
//#include "SD.h"
#include "Ardiuno.h"
#include "AudioStream.h"
//#include "SerialFlash.h"
//#include "RF24.h"
//#include "kinetis.h"


#ifndef PEINE_BLOCK_SAMPLES
#if defined(__MK20DX128__) || defined(__MK20DX256__) || defined(__MK64FX512__) || defined(__MK66FX1M0__)
#define PEINE_BLOCK_SAMPLES  64


//typedef bitset<8> BYTE;


typedef struct peine_block_struct{
	unsigned char ref_count;
	unsigned char memory_pool_index;
	unsigned char reserved1;
	unsigned char reserved2;
  uint8_t data[PEINE_BLOCK_SAMPLES];
} peine_block_t;

class peine_lib : public AudioStream {
	public:
	peine_lib(void): AudioStream(1,inputQueueArray){};
	
	peine_block_t * decimate(audio_block_t *block, int downsample);	
	audio_block_t * interp_zeros(peine_block_t *peine, int upsample);
	audio_block_t * interp_linear(peine_block_t *peine, uint16_t upsample);
	virtual void update(void);
	
	private:
	audio_block_t *inputQueueArray[1];
	int downsample;
	peine_block_t *peine;
	int upsample;
	uint16_t upsample;
}
