
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

// sd vars
#define SD_CS_PIN 16

// playback vars
int sample_rate = 32000;


int sampToI2sDeltaSigma(short s) {
    int x;
    int val = 0;
    int w;
    static int i1v = 0, i2v = 0;
    static int outReg = 0;
    for (x = 0; x < 32; x++) {
        val <<= 1; //next bit
        w = s;
        if (outReg > 0) w -= 32767; else w += 32767; //Difference 1
        w += i1v; i1v = w; //Integrator 1
        if (outReg > 0) w -= 32767; else w += 32767; //Difference 2
        w += i2v; i2v = w; //Integrator 2
        outReg = w;   //register
        if (w > 0) val |= 1; //comparator
    }
    return val;
}


void setup()
{
  // turn off ESP8266 RF
  WiFi.forceSleepBegin(); 
  delay(1); 

  // start serial
  Serial.begin(115200);
  while (!Serial);

  // init sd 
  // max speed i could get to work was
  // 38MHz: SD.begin(SD_CS_PIN, SD_SCK_MHZ(38))
  if (!SD.begin(SD_CS_PIN))
  {
    Serial.println("initialization failed!");
    return;
  }

}

void loop()
{
  play_crab();
}



void play_crab() {
  File myFile = SD.open("/Crabrave.wav", "r");
  
  if (!myFile) {
    Serial.println("File not found");
    return;
  }

  Serial.println("Playing: Crabrave.wav");
  int16_t buffer[512];

  i2s_begin();  
  i2s_set_rate(sample_rate);

  
  while (myFile.position() < (myFile.size()-1)) {
        int numBytes = _min(sizeof(buffer), myFile.size() - myFile.position() - 1);
        myFile.readBytes((char*)buffer, numBytes);
        for (int i = 0; i < numBytes / 2; i++) {
            i2s_write_sample(sampToI2sDeltaSigma(buffer[i]));
        }
  }
    

  myFile.close();
  i2s_end();
}
