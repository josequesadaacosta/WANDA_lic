/*
Hello World Example using Wanda library
*/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(28, 39);


void setup(){
  
  const uint64_t address = 0xF0F0F0F0E1LL; //random byte for address. It just needs to match the address in receiver code.
  //const byte address[6] = "00001";
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  //radio.printDetails();
}

void loop(){
  const char text[] = "Hello World";
  radio.write(&text, sizeof(text));
  //delay();
  //Serial.println("Sent.\n");
}

