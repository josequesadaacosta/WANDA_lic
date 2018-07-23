#include <peine_lib.h>
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioPlaySdWav            playSdWav1;  //xy=221,373
//AudioInputI2S            i2s1;

AudioFilterStateVariable      lp1;
LinCompressor     dec;
AudioFilterStateVariable        lp;
AudioOutputI2S           i2sout; //xy=1769,373

AudioConnection          patchCord1(playSdWav1, 0, lp1, 0);

AudioConnection          patchCord2(lp1, 0, dec, 0);
AudioConnection          patchCord3(dec, 0, lp, 0);
AudioConnection          patchCord4(dec, 0, i2sout, 0);
AudioConnection          patchCord5(dec, 0, i2sout, 1);
AudioControlSGTL5000     sgt15000_1;
// GUItool: end automatically generated code

// Use these with the Teensy Audio Shield
#define SDCARD_CS_PIN    10
#define SDCARD_MOSI_PIN  7
#define SDCARD_SCK_PIN   14


void setup() {
   Serial.begin(9600);
  AudioMemory(8);
  sgt15000_1.enable();
  sgt15000_1.volume(0.6);

  
  //sgt15000_1.inputSelect(AUDIO_INPUT_MIC);
  //sgt15000_1.micGain(36);
  //delay(1000);

  
  SPI.setMOSI(SDCARD_MOSI_PIN);
  SPI.setSCK(SDCARD_SCK_PIN);
  if (!(SD.begin(SDCARD_CS_PIN))) {
    while (1) {
      Serial.println("Unable to access the SD card");
      delay(500);
   }
  }
  delay(1000);
}

void loop() {
  if (playSdWav1.isPlaying() == false) {
    Serial.println("Start playing");
   playSdWav1.play("SDTEST1.WAV");
    delay(10); // wait for library to parse WAV info
    lp1.frequency(10000);
    lp1.resonance(0.7);
    //dec.rate(2);
    dec.threshold(500);
    lp1.frequency(15000);
    lp1.resonance(0.7);
    
 }
  //audiotest.gain(0.0);
}
