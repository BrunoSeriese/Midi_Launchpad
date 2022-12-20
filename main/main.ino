
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
// samplerate
// int rate = 32000;
int rate = 32000*2;
int16_t buffer[512];


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
  if (!SD.begin(SD_CS_PIN, SD_SCK_MHZ(38)))
  {
    Serial.println("initialization failed!");
    return;
  } else {
    Serial.println("sd connected");
  }

}

void loop()
{
  Serial.println("song started");
  play_songs();
  delay(500);
}



void play_songs() {
  File myFile = SD.open("/Crabrave.wav", "r");
  
  if (!myFile) {
    return;
  } else {
    Serial.println("File found");
  }


  i2s_begin();  
  i2s_set_rate(rate);

  Serial.println("I2S started");
  delay(2);



  
  // unsigned long tStart = millis();
  
  while(myFile.available()) {
    // tStart = millis();

    myFile.readBytes((char*)buffer, 512);
    for(int i=0; i < 512; i++) {
      i2s_write_sample(sampToI2sDeltaSigma(buffer[i]));
    }
    // Serial.println(buffer[0]);
    // unsigned long tEnd = millis();
    // Serial.print("Time: ");
    // Serial.println(tEnd-tStart);
    

  }
    

  myFile.close();
  i2s_end();
  
}











