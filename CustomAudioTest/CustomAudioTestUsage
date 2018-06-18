#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <CustomAudioTest.h>


// GUItool: begin automatically generated code
AudioPlaySdWav           playSdWav1;
AudioMixer4              mixer1;
AudioOutputI2S           i2s1;
CustomAudioTest          audiotest;
AudioConnection          patchCord1(playSdWav1, 0, mixer1, 0);
AudioConnection          patchCord2(playSdWav1, 1, mixer1, 1);
AudioConnection          patchCord3(mixer1, 0, audiotest, 0);
AudioConnection          patchCord4(audiotest, 0, i2s1, 0);
AudioConnection          patchCord5(audiotest, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;


// Use these with the Teensy Audio Shield
#define SDCARD_CS_PIN    10
#define SDCARD_MOSI_PIN  7
#define SDCARD_SCK_PIN   14


void setup() {
  Serial.begin(9600);
  AudioMemory(8);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.5);
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
    mixer1.gain(0, 1.0);
    mixer1.gain(1, 1.0);
    audiotest.gain(0.1);
  }
  //audiotest.gain(0.0);
}
