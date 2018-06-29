/*
Test for TX block, reading from Line In/microphone.
If test is going to be made using SD Card, comment lines 51-53 and uncomment lines 54-61
 Using TX from RF24forWanda.
*/

#include <TX.h>
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

//Audio Connections. data[] is kept in RAM.

//Using Line In.
AudioInputI2S            i2s1;
TX                       LenaTX;
AudioConnection          patchCord1(i2s1, 0, LenaTX, 0);
AudioControlSGTL5000     sgtl5000_1;

// Use these with the Teensy Audio Shield
#define SDCARD_CS_PIN    10
#define SDCARD_MOSI_PIN  7
#define SDCARD_SCK_PIN   14

//For Teensy 3.6
int cePin = 6;
int csnPin = 25;

void setup() {
  Serial.begin(9600);
  AudioMemory(8); //can be reduced to AudioMemory(4)
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.5);
  SPI.setMOSI(28);
  SPI.setSCK(27);
  SPI.setMISO(39);
  //sgtl5000_1.inputSelect(AUDIO_INPUT_LINEIN);
  sgtl5000_1.inputSelect(AUDIO_INPUT_MIC);
  sgtl5000_1.micGain(36);
  /*SPI.setMOSI(SDCARD_MOSI_PIN);
  SPI.setSCK(SDCARD_SCK_PIN);
  if (!(SD.begin(SDCARD_CS_PIN))) {
    while (1) {
      Serial.println("Unable to access the SD card");
      delay(500);
    }
  }*/
  delay(1000);
}

void loop()
{
  //do nothing
}
