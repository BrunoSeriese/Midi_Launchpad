
// Code was geschreven voor de ESP8266
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <SPI.h>
#include <SD.h>
#include <FS.h>

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
// #include "src/play_sounds/play_sounds.h"

// sd vars
#define SD_CS_PIN 16

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

  // init sd
  if (!SD.begin(SD_CS_PIN))
  {
    Serial.println("initialization failed!");
    return;
  }

  Serial.println("POG");

  play_sounds();

  
}
 


void loop()
{}




void play_sounds() {
  File frogSound = SD.open("/Frog.wav", "r");  
  if (!frogSound) {
    Serial.println("Frog File not found");
    return;
  }

  File fearSound = SD.open("/Fear.wav", "r");  
  if (!fearSound) {
    Serial.println("Fear File not found");
    return;
  }

  Serial.println("Playing: Frog.wav + Fear.wav");
  int16_t buffer1[512];
  int16_t buffer2[512];
  int16_t newSample[512];
  int16_t finalSample[512];

  i2s_begin();  
  i2s_set_rate(sample_rate);

  int numBytes = 0;
  while (frogSound.position() < (frogSound.size()-1)) {
        
    if (i2s_available()) {
      numBytes = _min(sizeof(buffer1), frogSound.size() - frogSound.position() - 1);

      frogSound.readBytes((char*)buffer1, numBytes);
      fearSound.readBytes((char*)buffer2, numBytes);
      
      for (int i = 0; i < numBytes / 2; i++) {
        newSample[i] = (buffer1[i] + buffer2[i]) /4;
      }

      // while(i2s_available() < numBytes/2) {}
      i2s_write_buffer_mono(newSample, numBytes/2);
    }
    
    
    
    
    
        

        
  }
    

  frogSound.close();
  fearSound.close();
  i2s_end();
}

