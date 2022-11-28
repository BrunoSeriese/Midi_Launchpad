#include "button_matrix.h"

template <typename T> T printArray(T* array, uint8_t size) {
    String result;

    for (int i = 0; i < size; i++) {
        result += String(array[i]);
        result += " ";
    }
    Serial.println(result);
}


void ButtonMatrix::onSetup() {
    Serial.println("rowPins: ");
    printArray<uint8_t>(rowPins, shape.rowSize);

    Serial.println("columnPins: ");
    printArray<uint8_t>(columnPins, shape.columnSize);
}

ButtonMatrix::ButtonMatrix(uint8_t* row, uint8_t* column, uint8_t rowSize, uint8_t columnSize) {
    shape.rowSize = rowSize;
    shape.columnSize = columnSize;
    buttons = shape.rowSize*shape.columnSize;
    
    rowPins = row;
    columnPins = column;
    
}

ButtonMatrix::ButtonMatrix() {}

ButtonMatrix::~ButtonMatrix() {}



void ButtonMatrix::setupPins() {
    // setup rowpins
    for (int row = 0; row < shape.rowSize; row++) {
        pinMode(rowPins[row], OUTPUT);
        digitalWrite(rowPins[row], HIGH);
    }

    // setup columnpins
    for (int column = 0; column < shape.columnSize; column++) {
        pinMode(columnPins[column], INPUT_PULLUP);
    }

    onSetup();
}



void ButtonMatrix::changeOutput(uint8_t active_pin) {
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
    for (int row = 0; row < shape.rowSize; row++) {
        changeOutput(rowPins[row]);
        for (int column = 0; column < shape.columnSize; column++) {
            buff[(row*shape.rowSize)+column] = !digitalRead(columnPins[column]);
        }
    }
}

