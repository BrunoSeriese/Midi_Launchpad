
#include "pitches.h"
#include "melody.h"


int speed=90;  //higher value, slower notes

void setup() {
  for (int thisNote = 0; thisNote < 112; thisNote++) {

    int noteDuration = 750 / noteDurations[thisNote];
    tone(4, melody[thisNote], noteDuration);

    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    
    noTone(4);
  }
}

void loop() {
// no need to repeat the melody.
}
