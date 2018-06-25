/*
RF24forWanda Library
Library enables using the nRF24L01 with Teensy, to transmit audio in an ad hoc wireless network.

Methods herein implemented

Config()
beginTX()
TX()
beingRX()
RX()

AUDIO_BLOCK_SAMPLES = 1 x 128 x 16 (mono, 16 bits, standard quality)

*/

#include <RF24forWanda.h>

// Variable declarationç

#define SAMPLE_RATE 44100                     // The sample rate to use for transferring audio samples  Note: 44khz+ sample rate requires 8-bits per sample
#define RF_SPEED RF24_2MBPS
#define CRC_DEF RF24_CRC_8
int ce_pin = 9;
int csn_pin = 10;
RF24 radio(ce_pin, csn_pin);
#define WHICH_NODE 2     // must be a number from 1 - 6 identifying the PTX node
//Create up to 6 pipe addresses P0 - P5;  the "LL" is for LongLong type
const uint64_t rAddress[] = {0x7878787878LL, 0xB3B4B5B6F1LL, 0xB3B4B5B6CDLL, 0xB3B4B5B6A3LL, 0xB3B4B5B60FLL, 0xB3B4B5B605LL };
const uint64_t PTXpipe = rAddress[ WHICH_NODE - 1 ];   // Pulls the address from the above array for this node's pipe

RF24forWANDA::RF24forWANDA(RF24& radio, uint8_t radioNum): radioNum(radioIdentifier){}


/****************************************************************************************************************************
Method: beginTX()
Input:
Output:
Description: acrtive mode for transmitting packets. For entering this mode, PWR_UP bit must set high,
PRIM_RX set low, a payload in the TX FIFO and a high pulse on the CE por more than 10 us
*****************************************************************************************************************************/

void RF24forWANDA::beginTX()
{

  radio.begin();

  radio.setChannel(1);                 // Set RF channel to 1
  radio.setAutoAck(0);                 // Disable ACKnowledgement packets
  radio.setDataRate(RF_SPEED);         // RF24_2MBPS
  radio.setCRCLength(CRC_DEF);         // First, it was decided to use CRC = 16, but it was preferred speed instead of robustness
  radio.openReadingPipe(0,PTXpipe);    //open reading or receive pipe


  radio.stopListening(); //go into transmit mode
  TX();                               //Start listening for transmissions



}


/****************************************************************************************************************************
Method: beginRX()
Input:
Output:
Description:
*****************************************************************************************************************************/

void RF24forWANDA::beginRX()
{

  // Open up to six pipes for PRX to receive data

  radio.openReadingPipe(0,rAddress[0]);
  radio.openReadingPipe(1,rAddress[1]);
  radio.openReadingPipe(2,rAddress[2]);
  radio.openReadingPipe(3,rAddress[3]);
  radio.openReadingPipe(4,rAddress[4]);
  radio.openReadingPipe(5,rAddress[5]);



}


/****************************************************************************************************************************
Method: RX()
Input:
Output:
Description:
*****************************************************************************************************************************/

void RF24forWANDA::RX()
{



}


void RX()
{


}

void TX()
{


  radio.openWritingPipe(PTXpipe);        //open writing or transmit pipe



}



void RF24forWANDA::transmit(){
	TX();
}
void RF24forWANDA::receive(){
	RX();
}
