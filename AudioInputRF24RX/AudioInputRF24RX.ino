#include <Audio.h>
#include <Wire.h>
#include <SD.h>
#include <SerialFlash.h>
#include "./AudioInputRF24RX.h"


AudioInputRF24RX         audiotest;
AudioOutputI2S           i2s1;
AudioConnection          patchCord(audiotest, 0, i2s1, 0);
AudioControlSGTL5000     sgtl5000_1;


void setup()
{
  AudioMemory(12);
  
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.5);
 
  audiotest.receiverSetup();
}

void loop()
{
   //lp1.frequency(10000);
   //lp1.resonance(0.7);
}
