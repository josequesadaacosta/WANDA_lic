#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>
#include <SPI.h>

RF24 radio(28, 39);

void setup() {
  const uint64_t address = 0xF0F0F0F0E1LL;
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void loop() {
  if (radio.available()) {
    char text[96] = "";
    //char text1[32] = "";
    //char text2[32] = "";
    radio.read(&text, sizeof(text));
    //radio.read(&text[32], sizeof(uint8_t)*32);
    //radio.read(&text[64], sizeof(uint8_t)*32);
    Serial.println("Received: ");
    Serial.println(text);
    //Serial.println(text1);
    //Serial.println(text2);
  }
}
