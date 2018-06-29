//WANDA transmitter implementation

#include "TX.h"


static void  decimate(audio_block_t *block, int downsample) {
  //insert code
}

//radio configuration
RF24 radio(ce_pin, csn_pin);
pinMode(ce_pin,OUTPUT);
pinMode(csn_pin,OUTPUT);
SPI.begin(); // Initialize SPI bus
radio.ce(LOW);
radio.csn(HIGH);
radio.setPALevel(RF24_PA_MAX);
radio.setDataRate(RF24_2MBPS);
radio.setCRCLength(RF24_CRC_8);
radio.write_register(DYNPD,0); // Disable dynamic payloads, to match dynamic_payloads_enabled setting
radio.setChannel(76);
radio.flush_rx();
radio.flush_tx();

//Addresses definition
#define WHICH_NODE 1 // must be a number from 0 - 5 identifying the PTX node
const uint64_t rAddress[] = {0x7878787878LL, 0xB3B4B5B6F1LL, 0xB3B4B5B6CDLL, 0xB3B4B5B6A3LL, 0xB3B4B5B60FLL, 0xB3B4B5B605LL };
const uint64_t PTXpipe = rAddress[WHICH_NODE];   // Pulls the address from the above array for this node's pipe

//Set radio in transmission mode
radio.stopListening();
radio.openWwritingPipe(PTXpipe);


void TX::update() // happens every 2.9 ms (128 samples)
{
  audio_block_t *block;
	block = receiveWritable();
	if (!block) return;
  //convert from audio_block_t to peine_block_t
  decimate(block, 2);
  radio.startWrite(block->data, 32);
  radio.startWrite((block->data + 32), 32);
  release(block);
}
