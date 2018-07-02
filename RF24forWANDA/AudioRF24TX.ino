/*
Test for TX block, reading from Line In/microphone.
 Using TX from RF24forWanda.
*/

#include <AudioRF24TX.h>
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

//Audio Connections. data[] is kept in RAM.

//Using Line In.
AudioInputI2S            i2s1;
AudioRF24TX              LenaTX(6,25);
AudioConnection          patchCord1(i2s1, 0, LenaTX, 0);
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
  sgtl5000_1.inputSelect(AUDIO_INPUT_LINEIN);
  //sgtl5000_1.inputSelect(AUDIO_INPUT_MIC);
  //sgtl5000_1.micGain(36);

  LenaTX.transmitterSetup();
  
  delay(1000);
}

void loop()
{
  //do nothing
}
