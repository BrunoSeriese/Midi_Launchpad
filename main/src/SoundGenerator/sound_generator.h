#ifndef SOUND_GENERATOR_H
#define SOUND_GENERATOR_H
#include <Arduino.h>
#include "../LookupTable/tables.h"

#define U32_MAX 4294967296
#define U16_MAX 65535
#define SAMPLE_RATE 32000

#define MAX_NOTE_LIFE_SPAN 15872

uint32_t calcNewStep(double &target_freq) {
  return target_freq/SAMPLE_RATE*U32_MAX;
}


struct Sound {
  uint32_t acumelator = RANDOM_REG32; // pase offset
  uint32_t step;
  uint16 lifespan=MAX_NOTE_LIFE_SPAN;
  double freq;

  Sound() {}
  Sound(double _freq) : freq(_freq) {
    step = calcNewStep(freq);
    lifespan=0;
  }

  int16_t update() {
    if (lifespan>MAX_NOTE_LIFE_SPAN) return 0;
    lifespan++;
    acumelator+=step;
    return SINETABLE[acumelator>>24];
  }

  void changeFreq(double &newFreq) {
    freq = newFreq;
    step = calcNewStep(freq);
  }
};


uint8_t soundIndex=0;
Sound sounds[16];
void playSound(double &freq) {
  sounds[soundIndex] = Sound(freq);
  soundIndex++;
  if (soundIndex==16) soundIndex=0;
}


int32_t sample=0;
int32_t result=0;
int16_t updateSounds() {
  result=0;
  for (int i=0;i<16;i++) {
    sample = sounds[i].update();
    if(sample!=0) {
      result = result/2+sample/2;
    }
  }
  return result;
}





#endif