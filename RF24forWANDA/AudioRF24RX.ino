/*
Test for RX block, reading from Line In/microphone.
 Using RX from RF24forWanda.
*/

#include <AudioRF24RX.h>
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

//Audio Connections. data[] is kept in RAM.

AudioOutputI2S           i2s1;
AudioRF24RX              LenaRX(6,25);
AudioConnection          patchCord1(LenaRX, 0, i2s1 0);
AudioControlSGTL5000     sgtl5000_1;

// Use these with the Teensy Audio Shield
#define SDCARD_CS_PIN    10
#define SDCARD_MOSI_PIN  7
#define SDCARD_SCK_PIN   14

void setup() {
  Serial.begin(9600);
  AudioMemory(8); //can be reduced to AudioMemory(4)

  sgtl5000_1.enable();
  sgtl5000_1.volume(0.5);

  SPI.setMOSI(28);
  SPI.setSCK(27);
  SPI.setMISO(39);

  LenaRX.receiverSetup();

  delay(1000);
}

void loop()
{
  //do nothing
}
