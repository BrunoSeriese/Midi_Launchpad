#include "pitches.h"


uint8_t pins[10] = {2,3,4,5,6,A4,A3,A2,A1,A0};

// flat array where the bool values of buttons pressed will be stored
bool buttons[10];

void setup() {
    Serial.begin(115200);
    Serial.println("Start");

    // setup the correct input and output pins
    for (int i = 0; i < 10; i++) {
        pinMode(pins[i], INPUT_PULLUP);
    }
}

void loop() {
    // updates the buttons
    for(int i = 0; i < 10; i++) {
        buttons[i] = !digitalRead(pins[i]);
    }
    
    if (buttons[1]) {
        tone(7,NOTE_C3,100);
    }
    if (buttons[2]) {
        tone(7,NOTE_D3,100);
    }
    if (buttons[3]) {
        tone(7,NOTE_E3,100);
    }
    if (buttons[4]) {
        tone(7,NOTE_F3,100);
    }
    if (buttons[5]) {
        tone(7,NOTE_G3,100);
    }
    if (buttons[6]) {
        tone(7,NOTE_A3,100);
    }
    if (buttons[7]) {
        tone(7,NOTE_B3,100);
    }
    if (buttons[8]) {
        tone(7,NOTE_C4,100);
    }
    
    
    delay(10);
}


void printButtons() {
    for(int i = 0; i < 10; i++) {
        Serial.print(buttons[i]);
        if (i != 9) {
            Serial.print(", ");
        } else {
            Serial.println();
        }
    }
}
