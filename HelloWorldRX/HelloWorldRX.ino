/*
Hello World Example using Wanda library
*/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(28, 39);

void setup(){
  const uint64_t address = 0xF0F0F0F0E1LL;
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void loop(){
    if (radio.available()) {
      char text[32] = "";
      radio.read(&text, sizeof(text));
      Serial.println("Received: ");
      Serial.println(text);
    }
}



