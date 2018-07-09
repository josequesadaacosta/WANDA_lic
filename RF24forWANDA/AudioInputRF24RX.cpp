//WANDA receiver implementation

#include "AudioInputRF24RX.h"


//remove shift?

static void interp_zeros(audio_block_t *block, int8_t *peine, int downsample){

	int i = 0;

	while(i<AUDIO_BLOCK_SAMPLES){
		if(i%downsample == 0){
			block->data[i] = static_cast<int>(peine[i/downsample]<<8);
		}else{
			block->data[i] = 0;
		}
		i++;
	}
}

static void interp_linear(audio_block_t *block, int8_t *peine, int downsample){

	int i = 0;

	while(i < PEINE_BLOCK_SAMPLES-1){

		block->data[downsample*i] = (static_cast<uint16_t>(peine[i])<<8);
		block->data[downsample*i+downsample] = (static_cast<uint16_t>(peine[i+1])<<8);

		int j = 1;

		while(j < downsample){

			block->data[i+j] = static_cast<int16_t>((((block->data[i+downsample])-(block->data[i]))*(i+j)/downsample)+((block->data[i+downsample])*-i/downsample)+((block->data[i])*(i+downsample)/downsample));
			j++;
		}

		i++;
	}
}



// happens every 2.9 ms (128 samples)
/*void AudioInputRF24RX::update()
{
    downsample = 2;
	this->doneR1 = false;
    this->doneR2 = false;
	
	block = allocate();

	this->updated = true;
	
	__disable_irq();
	if(radio.available())              //True if there is a payload available, false if none is
	{
		//True if the payload was delivered successfully, false if not
		if(radio.read((void*)(&peine), 32))      //place received data in int8_t array.
		{
			this->doneR1 = true;	
			
		} 
	}

	
	//convert from peine_block_t to audio_block_t
    //interp_zeros(block, peine, downsample);
	
	__enable_irq();
	
	for(int i = 0; i < PEINE_BLOCK_SAMPLES; i++)
	{	
		Serial.print(peine[i]);
	}
	//sending to RX's output
	transmit(block);
	release(block);

}*/


void AudioInputRF24RX::update()
{
    downsample = 2;
	this->doneR1 = false;
    this->doneR2 = false;
	
	block = allocate();

	this->updated = true;
	
	
	__disable_irq();
	if(radio.available())              //True if there is a payload available, false if none is
	{
		//True if the payload was delivered successfully, false if not
		if(radio.read(prueba, sizeof(uint8_t)*32))    //place received data in int8_t array.
		{
			this->doneR1 = true;	
			
		} 
	}

	
	//convert from peine_block_t to audio_block_t
    //interp_zeros(block, peine, downsample);
	
	__enable_irq();
	
	
	//sending to RX's output
	transmit(block);
	release(block);

}
