#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <AudioOutputRF24TX.h>


AudioInputI2S            i2s1;
AudioOutputRF24TX        LenaTX;
AudioConnection          patchCord2(i2s1, 0, LenaTX, 0);
AudioControlSGTL5000     sgtl5000_1;


// Use these with the Teensy Audio Shield
#define SDCARD_CS_PIN    10
#define SDCARD_MOSI_PIN  7
#define SDCARD_SCK_PIN   14

void setup() {
  Serial.begin(9600);
  //while(!Serial);
  //Serial.println("Debug");
  AudioMemory(8); //can be reduced to AudioMemory(4)

  LenaTX.transmitterSetup();

  sgtl5000_1.enable();
  sgtl5000_1.volume(0.5);

  sgtl5000_1.inputSelect(AUDIO_INPUT_LINEIN);
  //sgtl5000_1.inputSelect(AUDIO_INPUT_MIC);
  //sgtl5000_1.micGain(36);

  Serial.println("Setup completed");

}

void loop()
{
  if (LenaTX.updated)
  {
    Serial.println("Entered update.");
    for (int j = 0; j < 128; j++)
    {
      Serial.print(LenaTX.getTransmitterData(j));
    }
    Serial.println();

    for (int j = 0; j < 64; j++)
    {
      Serial.print(LenaTX.getTransmitterData1(j));
    }
    //    int8_t* q = LenaTX.getTransmitterPrueba();
    //    for (int i = 0; i < 32; i++) {
    //      Serial.print(q[i]);
    //    }
    Serial.println();
    LenaTX.updated = false;
  }
}

