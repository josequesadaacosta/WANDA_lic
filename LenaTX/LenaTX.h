#ifndef CustomAudioTest_h_
#define CustomAudioTest_h_

#include "Arduino.h"
#include "AudioStream.h"
#include "RF24.h"
#include "nRF24L01.h"
#include "utility/dspinst.h"
#define PEINE_BLOCK_SAMPLES  64


class LenaTX : public AudioStream
{
#if defined(KINETISK)
  public:
    LenaTX(void);
      ~LenaTX(void);
      virtual void update(void);
      void gain(float gain);
      int16_t getBlockDataAt(int i);
      int8_t getPeineAt(int i);
      void transmitterSetup();
      void multiplyGain(int16_t *data, int32_t mult);
      void decimate(); //funcion maldita! -RRB
    private:
      audio_block_t *inputQueueArray[1];
      int16_t multiplier;
      int8_t *peine;
      audio_block_t *block;

      int downsample;
      RF24 radio;
#endif
  };



  template<class T> static void printArray(T * t, int size)
{
  for (int i = 0; i < size; i++)
  {
    Serial.print(t[i]);
    Serial.print(" ");
  }
  Serial.println();
}
#endif
