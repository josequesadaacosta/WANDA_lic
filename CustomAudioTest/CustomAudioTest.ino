#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include "./CustomAudioTest.h"
#include "./AudioOutputRF24TX.h"

#define SDCARD_CS_PIN    10
#define SDCARD_MOSI_PIN  7
#define SDCARD_SCK_PIN   14

CustomAudioTest          audiotest;


AudioInputI2S            i2s1;
AudioOutputI2S           i2s2;

AudioConnection          patchCord1(i2s1, 0, audiotest, 0);
AudioConnection          patchCord2(audiotest, 0, i2s2, 0);

AudioControlSGTL5000     sgtl5000_1;

//AudioOutputRF24TX        LenaTX;

const int myInput = AUDIO_INPUT_LINEIN;

void setup()
{
  Serial.begin(9600);
  AudioMemory(12);

  sgtl5000_1.enable();
  sgtl5000_1.inputSelect(myInput);
  sgtl5000_1.volume(0.5);
  Serial.println("Setup completed");

}

void loop()
{
  Serial.println("\\_o< CUAK");
  Serial.println("block->data[]");
  for (int j = 0; j < 128; j++)
  {
    Serial.print(audiotest.getTransmitterData(j));
  }
  Serial.println();
  Serial.println("peine");
  for (int j = 0; j < 64; j++)
  {
    Serial.print(audiotest.getTransmitterData1(j));
  }

  Serial.println("EEEK <oO~");
}
