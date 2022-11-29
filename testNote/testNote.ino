
#include "pitches.h"

const int buttonPin = 2;  
int buttonState = 0; 

int speed=90;  //higher value, slower notes

void setup() {

pinMode(buttonPin, INPUT);
 tone(4,440,2000);
}

void loop() {


buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    // turn LED on:
    tone(4,440,2000);
  }

}
