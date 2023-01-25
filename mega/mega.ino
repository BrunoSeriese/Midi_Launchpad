#include "src/midi_config/midi_config.h"
#include "src/button_config/button_config.h"


                   
void setup() {
  Serial.begin(115200);
  while(!Serial) {}

  setupButtons();
}



void loop() {
  
  handleButtons();
}








// void tone(uint8_t _pin, unsigned int frequency, unsigned long duration) {
// pinMode (_pin, OUTPUT );
// analogWrite(_pin,500);
// delay(duration);
// analogWrite(_pin,0);
// }