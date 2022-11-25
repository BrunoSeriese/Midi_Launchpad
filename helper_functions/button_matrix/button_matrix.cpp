#include "button_matrix.h"

// void viewIntArray(int* array, int size) {
//     for(int i =0; i < size; i++) {
//         Serial.print(array[i]);
//         if (i!= size-1) {
//             Serial.print(", ");
//         } else {
//             Serial.println();
//         }
//     }
// }

void viewIntArray(byte* array, byte size) {
    for(int i =0; i < size; i++) {
        Serial.print(array[i]);
        if (i!= size-1) {
            Serial.print(", ");
        } else {
            Serial.println();
        }
    }
}


void ButtonMatrix::onSetup() {
    Serial.print("rowPins: ");
    viewIntArray(rowPins, shape.rowSize);

    Serial.print("columnPins: ");
    viewIntArray(columnPins, shape.columnSize);
}

ButtonMatrix::ButtonMatrix(byte* row, byte* column, byte rowSize, byte columnSize) {
    shape.rowSize = rowSize;
    shape.columnSize = columnSize;
    
    // copy row pins
    byte rowBuff[shape.rowSize];
    for (int i = 0; i < shape.rowSize; i++) {rowBuff[i] = row[i];}
    rowPins = rowBuff;

   

    // copy column pins
    byte columnBuff[shape.columnSize];
    for (int i = 0; i < shape.columnSize; i++) {columnBuff[i] = column[i];}
    columnPins = columnBuff;

    

    // setup button vars
    buttons = shape.rowSize*shape.columnSize;

    setupPins();
}

ButtonMatrix::~ButtonMatrix() {}



void ButtonMatrix::setupPins() {
    // setup rowpins
    for (int rowPin = 0; rowPin < shape.rowSize; rowPin++) {
        pinMode(rowPins[rowPin], OUTPUT);
        digitalWrite(rowPins[rowPin], LOW);
    }

    // setup columnpins
    for (int columnPin = 0; columnPin < shape.columnSize; columnPin++) {
        pinMode(columnPins[columnPin], INPUT_PULLUP);
    }
}



void ButtonMatrix::changeOutput(int active_pin) {
    for (int i = 0; i < shape.rowSize; i++) {
        if (rowPins[i] == active_pin) {
            digitalWrite(rowPins[i], LOW);
        }
        else {
            digitalWrite(rowPins[i], HIGH);
        }
    }
}



void ButtonMatrix::updateButtonsPressed(bool* buff) {    
    bool result[shape.rowSize*shape.columnSize];

    for (int row = 0; row < shape.rowSize; row++) {
        // Serial.println("first part");
        changeOutput(rowPins[row]);

        // Serial.println("MiddelPart");
        for (int column = 0; column < shape.columnSize; column++) {
            // Serial.println("allmost there");
            result[(row*shape.rowSize)+column] = !digitalRead(columnPins[column]);
            // Serial.println("done");
        }
    }
    buff = result;
}

