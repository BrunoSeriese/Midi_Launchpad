
// Code was geschreven voor de ESP8266
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <SPI.h>
#include <SD.h>
#include <FS.h>

#include <I2S.h>
#include <I2S_reg.h>

// sd vars
#define SD_CS_PIN 15

// playback vars
// samplerate
int rate = 32000;
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
  if (!SD.begin(SD_CS_PIN))
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

  // unsigned long tStart = millis();

    while (myFile.position() < (myFile.size()-1)) {
        int numBytes = _min(sizeof(buffer), myFile.size() - myFile.position() - 1);
        myFile.readBytes((char*)buffer, numBytes);
        for (int i = 0; i < 512; i++) {
            // i2s_write_sample(sampToI2sDeltaSigma(buffer[i]));
            Serial.println((char)buffer[i]);
        }
        Serial.println();
        // unsigned long tTime = millis()-tStart;
        // tStart = millis();
        // Serial.print("Time: ");
        // Serial.println(tTime);

    }
    

  myFile.close();
  i2s_end();
  
}











