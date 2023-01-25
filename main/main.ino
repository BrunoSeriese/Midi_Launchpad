// Code was geschreven voor de ESP8266
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "src/SoundGenerator/sound_generator.h"
#include <Wire.h>

// IOs used for I2S. Not defined in i2s.h, unfortunately.
// Note these are internal GPIO numbers and not pins on an
// Arduino board. Users need to verify their particular wiring.
// Most of the pins are only used when i2s clock is enabled
// I2SO_DATA 3
// I2SO_BCK  15
// I2SO_WS   2
// I2SI_DATA 12
// I2SI_BCK  13
// I2SI_WS   14
#include <I2S.h>
#include <I2S_reg.h>

// i2s pins are
// I2SO_DATA 3(RX)  -> DIN 
// I2SO_BCK  15(D8) -> BCLK
// I2SO_WS   2(D4)  -> LRC

// playback vars
const uint32_t sample_rate = 32000;

#define SLAVE_ADDR 9
const char term = '\n';



void setup()
{
  system_update_cpu_freq(160);

  // turn off ESP8266 RF
  WiFi.forceSleepBegin(); 
  delay(1); 

  // start serial
  Serial.begin(115200);
  while (!Serial);

  // i2c
  Wire.begin(SLAVE_ADDR);

  // start i2s
  i2s_begin();
  i2s_set_rate(sample_rate);
  i2s_set_bits(16);

  Serial.println("Begin!");
}


inline int16_t double2int(double d)
{
    d += 6755399441055744.0;
    return reinterpret_cast<int16_t&>(d);
}


double volume = 0.1;
float offset = 0;
double dSample=0;

int16_t buffer[512];
int noteIndex=0;
int state=0;
double notemap[24] = {
  261.626,277.183,293.665,311.127,329.628,349.228,369.994,391.995,415.305,440.00,466.164,493.883,
  523.251,554.365,587.330,622.254,659.225,698.456,739.989,783.991,830.609,880.00,932.328,987.767
};


void loop()
{
  if (Wire.available()>0) {
    String ms = Wire.readStringUntil(term);
    noteIndex = ms.substring(0,2).toInt();
    state = ms.substring(2,3).toInt();
  }


  // audio stuff
  for(int i=0;i<512;i++) {
    if (noteIndex<25) {
      dSample = sineWave(notemap[noteIndex], offset);
      buffer[i] = double2int(dSample*32767*volume);
      offset+=31.25*0.000001; 
      if (offset>1) {
        offset = offset-1;
      }    
    } else {
      buffer[i] = 0;
    }
  }
  
  for (int i=0; i<512;i++) {
    i2s_write_sample(buffer[i]);
  }  
 
}