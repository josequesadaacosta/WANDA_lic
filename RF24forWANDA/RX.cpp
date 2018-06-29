/WANDA receiver implementation

#include "RX.h"

static void interp_zeros(peine_block_t *peine, int downsample) {
  /* code */
}

static void interp_linear(peine_block_t *peine, int downsample) {
  /* code */
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
const uint64_t rAddress[] = {0x7878787878LL, 0xB3B4B5B6F1LL, 0xB3B4B5B6CDLL, 0xB3B4B5B6A3LL, 0xB3B4B5B60FLL, 0xB3B4B5B605LL };

//Set radio in reception mode
 radio.openReadingPipe(0,rAddress[0]);
 radio.openReadingPipe(1,rAddress[1]);
 radio.openReadingPipe(2,rAddress[2]);
 radio.openReadingPipe(3,rAddress[3]);
 radio.openReadingPipe(4,rAddress[4]);
 radio.openReadingPipe(5,rAddress[5]);
 radio.startListening();                 // Start listening for messages


void TX::update() // happens every 2.9 ms (128 samples)
{
  if(radio.available()){
    radio.read(&data,sizeof(data)); //change to adapt to peine_block. Does method accept 64 bytes?
  }
  //interpolation for making an audio_block_t to send. MODIFY PARAMS.
  block = interp_linear(peine_block, 2);
  transmit(block); //sending to RX's output.
  release(block);
}
