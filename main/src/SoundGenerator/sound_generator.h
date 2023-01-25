#ifndef SOUND_GENERATOR_H
#define SOUND_GENERATOR_H
#include <Arduino.h>
#include "../LookupTable/tables.h"


uint32_t calcNewStep(double target_freq) {
  return target_freq/32000*4294967296;
}

enum waveType {
    Sine,
    Square,
    Tri,
    Saw,
    Noise
};


double volume = 0.1;
uint32_t acumelator=0;
uint32_t step=calcNewStep(440.00);
int16_t sample=0;
int16_t updateSound() {
    sample = SINETABLE[acumelator>>24]*volume;
    acumelator+=step;
    return sample;
}





#endif