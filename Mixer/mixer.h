#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <Arduino.h>

use namespace std;

class channel : AudioStream  
{
public:
 channel(void); //constructor
 float gain;
 float hp;
 float bpgain;
 float bpfreq;
 float lp;
 float pan;
 float level;

};

float lineal(float input, int max);
