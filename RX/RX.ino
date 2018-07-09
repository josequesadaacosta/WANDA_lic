#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <AudioInputRF24RX.h>


AudioInputRF24RX         LenaRX;
AudioOutputI2S           i2s1;
AudioConnection          patchCord1(LenaRX, 1, i2s1, 0);
AudioControlSGTL5000     sgtl5000_1;

// Use these with the Teensy Audio Shield
#define SDCARD_CS_PIN    10
#define SDCARD_MOSI_PIN  7
#define SDCARD_SCK_PIN   14

void setup() {
  Serial.begin(9600);
  AudioMemory(8); //can be reduced to AudioMemory(4)

  LenaRX.receiverSetup();

  sgtl5000_1.enable();
  sgtl5000_1.volume(0.5);

  Serial.println("Setup completed");
}

void loop()
{
  if (LenaRX.updated)
  {
    Serial.println("Entered update.");
    if (LenaRX.doneR1)
    {
      Serial.println("Data was received.");
      /*for(int j = 0; j < 128; j++){
          Serial.print(LenaRX.getReceiverData(j));
        }*/
      /*Serial.println("");
        for(int j = 0; j < 32; j++){
          Serial.print(LenaRX.getReceiverData1(j));
        }*/
      int8_t* q = LenaRX.getReceiverPrueba();
      for (int i = 0; i < 32; i++) {
        Serial.println(q[i]);
      }

    }
    Serial.println();
    LenaRX.updated = false;
  }
}


