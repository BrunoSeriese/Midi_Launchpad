
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
  // disable watchdog
  // ESP.wdtDisable();

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

class Sound{
  public:
    int16_t buffer[512];
    uint16_t buffer_length = sizeof(buffer)/2;  
    bool isPlaying=false;
    
    Sound(String filePath) {
      source = SD.open(filePath, "r");  
      if (source) {
        isPlaying = true;
      } else {
        Serial.print("File: ");
        Serial.print(filePath);
        Serial.println(" not found.");
      }
    }

    Sound() {
      isPlaying=false;
    }

    ~Sound() {
      source.close();
    }

    void update() {
      source.readBytes((char*)buffer, 512*2);      
    }

    bool available() {
      return source.position() < (source.size()-1);
    }

    private:
      File source;
};


void play_sounds() {
  // setup sound list
  Sound sounds[2] = {Sound("/Frog.wav"), Sound("/Fear.wav")};
  int16_t final_buffer[512];
  int16_t temp_buffer[512];

  Serial.println("Breakpoint");  

  i2s_begin();  
  i2s_set_rate(sample_rate);

  while (sounds[0].available()) {
    for(int i=0;i<512;i++) {temp_buffer[i]=0;}

    for(int i=0;i<2;i++) {
      sounds[i].update();
    }

    for(int i=0;i<512;i++) {
      for(int j=0;j<2;j++) {
        temp_buffer[i] += sounds[j].buffer[i]/8;
      }
    }
    while(!i2s_is_empty()) {_NOP();ESP.wdtFeed();}
    memcpy(final_buffer, temp_buffer, 512*2);
    i2s_write_buffer_mono_nb(final_buffer, 512);
  }
    

  // frogSound.close();
  // fearSound.close();
  i2s_end();
}

