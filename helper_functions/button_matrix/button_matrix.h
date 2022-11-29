#ifndef BUTTON_MATRIX_H
#define BUTTON_MATRIX_H
#include <Arduino.h>



typedef struct {
    uint8_t rowSize;
    uint8_t columnSize;
} MatrixShape;



class ButtonMatrix {
    public:
    ButtonMatrix();
    ButtonMatrix(uint8_t* rowPins, uint8_t* columnPins, uint8_t rowSize, uint8_t columnSize);
    ~ButtonMatrix();

    void setupPins();

    void updateButtonsPressed(bool* buff);

    private:
    uint8_t* rowPins;    // output pins
    uint8_t* columnPins;   // input pins
    MatrixShape shape;

    int buttons;

    void changeOutput(uint8_t active_pin);
};



#endif