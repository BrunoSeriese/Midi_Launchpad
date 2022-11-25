#include <button_matrix.h>

const byte ROWSIZE    = 4; 
const byte COLUMNSIZE = 4;

byte ROWPINS[ROWSIZE]       = {2,3,4,5};
byte COLUMNPINS[COLUMNSIZE] = {6,7,8,9};

ButtonMatrix buttonMatrix = ButtonMatrix(ROWPINS, COLUMNPINS, ROWSIZE, COLUMNSIZE);
bool buttons[16];

void setup() {
    Serial.begin(115200);
    delay(1000);
    Serial.println("Start");

    buttonMatrix.onSetup();
}

void loop() {
    buttonMatrix.updateButtonsPressed(buttons);
    Serial.println("Stuff");
    for (int i = 0; i < 16; i++)
    {
        Serial.print(buttons[i]);
        if (i != 15) {
            Serial.print(", ");
        } else {
            Serial.println();
        }
        
    }
    delay(1000);
    
}