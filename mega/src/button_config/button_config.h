#include "../midi_config/midi_config.h"

#ifndef BUTTON_CONFIG_H
#define BUTTON_CONFIG_H
#define BUTTON_AMOUNT 24

class Button {
  public:
  int index=0;
  int pin;
  bool isPressed=false;
  int mode = 1;
  Note note;

  Button() {}
  Button(int _pin, int noteId) : pin(_pin) {
    note = Note(noteId);
  } 
  Button(int _index,int _pin, int noteId) : index(_index), pin(_pin) {
    note = Note(noteId);
  } 

  void press() {
    isPressed=true;
    

    switch (mode)
    {
    case 1:
        note.on();
        break;
    case 2:
        break;
    case 3:
        Serial.write((uint8_t)index);
        break;
    
    }
  }

  void unpress() {
    isPressed=false;
   
     switch (mode)
    {
    case 1:
        note.off();
        break;
    case 2:
        break;
    case 3:
        break;
    
    }
  }

  void changeMode(int mode){
    mode = mode;
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
    buttons[i] = Button(i,BUTTON_PINS[i],36+i);
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