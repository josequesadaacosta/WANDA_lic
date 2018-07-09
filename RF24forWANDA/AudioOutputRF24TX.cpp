//WANDA transmitter implementation

#include "AudioOutputRF24TX.h"
#include "AudioStream.h"

/*static void decimate(audio_block_t *block, int8_t *peine, int downsample)
  {

	int i = 0;

	while(i<PEINE_BLOCK_SAMPLES){
		peine[i] = static_cast<int8_t>(block->data[downsample*i]>>8);
		i++;
	}

  }*/

static void decimate(audio_block_t *block, int8_t *peine, int downsample)
{

  for (int i = 0; i < PEINE_BLOCK_SAMPLES; i++) {
    peine[i] = static_cast<int8_t>(block->data[downsample * i]);
  }

}

/*void AudioOutputRF24TX::update()
  {
	downsample = 2;

	//block = receiveWritable();
	block = allocate();
	if (!block) return;


	for(int i = 0; i < 128; i++)
	{
		block->data[i] = i + 1;
	}

    //convert from audio_block_t to peine_block_t
	decimate(block, peine, downsample);

	this->updated = true;

	__disable_irq();


	//transmitting
	radio.startWrite(&peine, 32);

	//radio.startWrite(&peine[32], 32);

	__enable_irq();

    //no more ownership for current block
    release(block);
  }*/


void AudioOutputRF24TX::update()
{
  downsample = 2;

  //block = receiveWritable();
  block = allocate();
  if (!block) return;


  for (int i = 0; i < 128; i++)
  {
    block->data[i] = i + 1;
  }




  //convert from audio_block_t to peine_block_t
  decimate(block, peine, downsample);

  this->updated = true;

  __disable_irq();



  //transmitting
  //radio.startWrite(&peine, 32);

  radio.startWrite(peine, sizeof(uint8_t) * 32);

  __enable_irq();

  //no more ownership for current block
  release(block);
}
