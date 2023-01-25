// Code was geschreven voor de ESP8266
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "src/SoundGenerator/sound_generator.h"
#include <SoftwareSerial.h>

/* IOs used for I2S. Not defined in i2s.h, unfortunately.
// Note these are internal GPIO numbers and not pins on an
// Arduino board. Users need to verify their particular wiring.
// Most of the pins are only used when i2s clock is enabled
// I2SO_DATA 3
// I2SO_BCK  15
// I2SO_WS   2
// I2SI_DATA 12
// I2SI_BCK  13
// I2SI_WS   14
*/
#include <I2S.h>
#include <I2S_reg.h>

/* i2s pins are
// I2SO_DATA 3(RX)  -> DIN 
// I2SO_BCK  15(D8) -> BCLK
// I2SO_WS   2(D4)  -> LRC
*/

// playback vars
#define I2S_BUFFER_SIZE 512
const uint32_t sample_rate = 32000;

SoftwareSerial mSerial(13, 12, false);
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

  // mega serial
  mSerial.begin(115200);
  while (!mSerial);

  // start i2s
  i2s_begin();
  i2s_set_rate(sample_rate);
  i2s_set_bits(16);

  Serial.println("Begin!");
}






int noteIndex=0;
int state=0;
double notemap[24] = {
  261.626,277.183,293.665,311.127,
  329.628,349.228,369.994,391.995,
  415.305,440.00,466.164,493.883,
  523.251,554.365,587.330,622.254,
  659.225,698.456,739.989,783.991,
  830.609,880.00,932.328,987.767
};



int16_t buffer[512];
unsigned long sTime = micros();
unsigned long eTime = sTime;
void loop()
{
  // if (mSerial.available()) {
  //   byte data[1];
  //   mSerial.readBytes(data, 1);
  //   noteIndex = reinterpret_cast<uint8&>(data[0]);
  //   Serial.println(noteIndex);
  // }

  // audio stuff
  sTime = micros();
  for(int i=0;i<I2S_BUFFER_SIZE;i++) {
    buffer[i]=updateSound();
  }
  Serial.println(micros()-sTime);
  
  for (int i=0; i<I2S_BUFFER_SIZE;i++) {
    i2s_write_sample(buffer[i]);
  }  
 
}