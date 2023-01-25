#include "../midi_config/midi_config.h"

#ifndef BUTTON_CONFIG_H
#define BUTTON_CONFIG_H
#define BUTTON_AMOUNT 24

class Button {
  public:
  int pin;
  bool isPressed=false;
  Note note;

  Button() {}
  Button(int _pin, int noteId) : pin(_pin) {
    note = Note(noteId);
  } 

  void press() {
    isPressed=true;
    note.on();
  }

  void unpress() {
    isPressed=false;
    note.off();
  }

  private:
};

const int BUTTON_PINS[BUTTON_AMOUNT] = {
  53,39,38,36,47,41,45,43,
  52,46,22,37,40,49,44,27,
  30,31,48,35,34,42,26,25};
Button buttons[BUTTON_AMOUNT];


void setupButtons() {
  for (int i = 0; i < BUTTON_AMOUNT; i++) {
    pinMode(BUTTON_PINS[i], INPUT_PULLUP);
    buttons[i] = Button(BUTTON_PINS[i],36+i);
  }
}


void handleButtons() {
  for (int i=0;i<BUTTON_AMOUNT;i++){
    if (digitalRead(buttons[i].pin) == LOW && !buttons[i].isPressed){
      buttons[i].press();
    } else if (digitalRead(buttons[i].pin) == HIGH && buttons[i].isPressed) {
      buttons[i].unpress();
    }
  }
}


#endif