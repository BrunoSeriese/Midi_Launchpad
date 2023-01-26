#include "../midi_config/midi_config.h"

#ifndef BUTTON_CONFIG_H
#define BUTTON_CONFIG_H
#define BUTTON_AMOUNT 24

#define MODEBTN1 8
#define MODEBTN2 9

int MODE = 3;

class Button {
  public:
  int index=0;
  int pin;
  bool isPressed=false;
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

    switch (MODE)
    {
    case 1:
        note.on();
        break;
    case 2:
        break;
    case 3:
        Serial1.write((uint8_t)index);
        break;
    
    }
  }

  void unpress() {
    isPressed=false;
   
     switch (MODE)
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

  private:
};

const int BUTTON_PINS[BUTTON_AMOUNT] = {
  53,39,38,36,47,41,45,43,
  52,46,22,37,40,49,44,27,
  30,31,48,35,34,42,26,25};
Button buttons[BUTTON_AMOUNT];


void setupButtons() {
  pinMode(MODEBTN1, INPUT_PULLUP);
  pinMode(MODEBTN2, INPUT_PULLUP);

  for (int i = 0; i < BUTTON_AMOUNT; i++) {
    pinMode(BUTTON_PINS[i], INPUT_PULLUP);
    buttons[i] = Button(i,BUTTON_PINS[i],36+i);
  }
}


void handleButtons() {
  if (digitalRead(MODEBTN1) == LOW) {
    MODE = 3;
  } else {
    MODE = 1;
  }

  for (int i=0;i<BUTTON_AMOUNT;i++){
    if (digitalRead(buttons[i].pin) == LOW && !buttons[i].isPressed){
      buttons[i].press();
    } else if (digitalRead(buttons[i].pin) == HIGH && buttons[i].isPressed) {
      buttons[i].unpress();
    }
  }
}


#endif