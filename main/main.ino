// Code was geschreven voor de ESP8266
#include <Arduino.h>
#include <ESP8266WiFi.h>

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
int sample_rate = 32000;


void setup()
{
  // turn off ESP8266 RF
  WiFi.forceSleepBegin(); 
  delay(1); 

  // start serial
  Serial.begin(115200);
  while (!Serial);

  // start i2s
  i2s_begin();
  i2s_set_rate(sample_rate);
  i2s_set_bits(16);

  Serial.println("Begin!");
}

double offset = 0;
int16_t buffer[512];
void loop()
{
  
  
  for(int i=0;i<512;i++) {
    double dSample = sin(440.0*offset*PI*2*0.000001);
    buffer[i]=dSample*32767*0.5;
    offset+=31.25;
  }

  for(int i=0;i<512;i++) {
    i2s_write_sample(buffer[i]);
  }
}
