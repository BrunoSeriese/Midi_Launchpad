#ifndef BUTTON_MATRIX_H
#define BUTTON_MATRIX_H
#include <Arduino.h>

typedef uint8_t byte;


typedef struct {
    byte rowSize;
    byte columnSize;
} MatrixShape;



class ButtonMatrix {
    public:
    ButtonMatrix(byte* rowPins, byte* columnPins, byte rowSize, byte columnSize);
    ~ButtonMatrix();

    void onSetup();

    void updateButtonsPressed(bool* buff);

    private:
    byte* rowPins;    // output pins
    byte* columnPins;   // input pins
    MatrixShape shape;

    int buttons;

    void setupPins();
    void changeOutput(int active_pin);
};


#endif