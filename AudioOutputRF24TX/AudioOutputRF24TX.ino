#include <Audio.h>
#include <Wire.h>
#include <SD.h>
#include <SPI.h>
#include <SerialFlash.h>
#include "./AudioOutputRF24TX.h"

AudioOutputRF24TX        audiotest;
AudioInputI2S            i2s1;
AudioOutputI2S           i2s2;

AudioConnection          patchCord1(i2s1, 0, audiotest, 0);
AudioConnection          patchCord2(audiotest, 0, i2s2, 0);

AudioControlSGTL5000     sgtl5000_1;


void setup()
{  
  AudioMemory(12);

  sgtl5000_1.enable();
  sgtl5000_1.inputSelect(AUDIO_INPUT_LINEIN);
  sgtl5000_1.volume(0.5);

  audiotest.transmitterSetup();
}

void loop()
{}
