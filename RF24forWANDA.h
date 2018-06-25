/*
Header file for RF24forWanda Library
Library enables using the nRF24L01 with Teensy, to transmit audio in an ad hoc wireless network.

Methods herein implemented

Config()
beginTX()
TX()
beingRX()
RX()

Multiceiver: this nRF24L01 feature is the one that provides the wireless diffusion functionality for this network.
It is a feature used in RX mode that contains a set of 6 parallel data pipes with unique addresses. A data pipe is a
logical channel in the physical RF channel. Each data pipe has its own physical address decoding in the nRF24L01.

*/

#ifndef RF24forWANDA_h_
#define RF24forWANDA_h_

 /***************************************************************************************************
 Libraries needed
 ***************************************************************************************************/
#include <RF24.h>
#include <AudioStrem.h>
#include <Arduino.h>
#include <stddef.h>
#include <SPI.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

class RF24;

class RF24forWANDA
{
public:
  RF24forWANDA(RF24& _radio, uint8_t radioNum);

  void beginRX();
  void beginTX();
  void transmit();
  void receive();
  void multiceiver(uint8_t radioID); //  feature used in RX mode
  uint64_t getAddress(uint8_t addressNo); // Get any of the preset radio addresses

private:
  audio_block_t *block;
  RF24& radio;
};

config();
TX();
RX();


#endif
