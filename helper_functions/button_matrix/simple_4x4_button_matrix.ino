#include "button_matrix.h"

// SIZE of the row and column arrays
const uint8_t ROWSIZE    = 4; 
const uint8_t COLUMNSIZE = 4;

// row and column array
uint8_t ROWPINS[ROWSIZE]        = {6,7,8,9};
uint8_t COLUMNPINS[COLUMNSIZE]  = {2,3,4,5};

// init button matrix class
ButtonMatrix buttonMatrix = ButtonMatrix(ROWPINS, COLUMNPINS, ROWSIZE, COLUMNSIZE);

// flat array where the bool values of buttons pressed will be stored
bool buttons[ROWSIZE*COLUMNSIZE];

void setup() {
    Serial.begin(115200);
    Serial.println("Start");

    // setup the correct input and output pins
    buttonMatrix.setupPins();
}

void loop() {
    // updates the buttons
    buttonMatrix.updateButtonsPressed(buttons);
    printArray<bool>(buttons, ROWSIZE*COLUMNSIZE);
    
    delay(10);
}

