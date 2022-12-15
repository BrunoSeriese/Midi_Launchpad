// This test was made with the MCP4725 DAC
// The DAC is limited by the transfer speed of the i2c connection
// wich means that it can only generate tones up to 400khz
// sadly i wasnt able to get tones that high
// its probably better to use a different DAC

#include <Wire.h>
#include <Adafruit_MCP4725.h>
 
Adafruit_MCP4725 dac;

void setup()
{
  dac.begin(0x60); 
}
 
// factor to map 0-2PI(radians) to 0-256
float ConversionFactor=(2*PI)/256;
void loop()
{
    // i+? is what determance the frequency 
  for(int i=0;i<256;i+=4){
    // mapping int to rad
    float RadAngle=i*ConversionFactor; 
    // 2047 and 2048 come from 4095/2 cus of the rounding the numbers are not the same. 4095 is the max the DAC can output.
    dac.setVoltage((sin(RadAngle)*2047)+2048, false, 600000U); 
  }
}