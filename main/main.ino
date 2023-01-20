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

// i2s pins are
// I2SO_DATA 3(RX)  -> DIN 
// I2SO_BCK  15(D8) -> BCLK
// I2SO_WS   2(D4)  -> LRC

// sd vars
#define SD_CS_PIN 16

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

  play_sounds();
}

void loop()
{
  
}


#define BUFFER_SIZE 256
void play_sounds() {
  File S1 = SD.open("piano/C3.wav", "r");  
  if (!S1) {
    Serial.println("Frog File not found");
    return;
  }

  File S2 = SD.open("piano/Db3.wav", "r");  
  if (!S2) {
    Serial.println("Fear File not found");
    return;
  }

  File S3 = SD.open("piano/D3.wav", "r");  
  if (!S3) {
    Serial.println("Fear File not found");
    return;
  }

  File S4 = SD.open("piano/Eb3.wav", "r");  
  if (!S4) {
    Serial.println("Fear File not found");
    return;
  }

  File S5 = SD.open("piano/E3.wav", "r");  
  if (!S5) {
    Serial.println("Fear File not found");
    return;
  }

  Serial.println("Playing: Piano sounds");
  int16_t buffer1[BUFFER_SIZE];
  int16_t buffer2[BUFFER_SIZE];
  int16_t buffer3[BUFFER_SIZE];
  int16_t buffer4[BUFFER_SIZE];
  int16_t buffer5[BUFFER_SIZE];
  int16_t newSample;

  i2s_begin();  
  i2s_set_rate(sample_rate);

  // frogSound is the smaller file
  while (S1.position() < (S1.size()-1)) {
        int numBytes = _min(sizeof(buffer1), S1.size() - S1.position() - 1);
        
        S1.readBytes((char*)buffer1, numBytes);
        S2.readBytes((char*)buffer2, numBytes);
        S3.readBytes((char*)buffer3, numBytes);
        S4.readBytes((char*)buffer4, numBytes);
        S5.readBytes((char*)buffer5, numBytes);
        
        for (int i = 0; i < numBytes / 2; i++) {
            newSample = (buffer1[i] + buffer2[i] + buffer3[i] + buffer4[i] + buffer5[i]) /5;
            i2s_write_sample(newSample);
        }
  }
    

  S1.close();
  S2.close();
  S3.close();
  S4.close();
  S5.close();
  i2s_end();
}