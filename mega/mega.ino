#include "src/midi_config/midi_config.h"
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
    Serial.println("Press");
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


                   
void setup() {
  Serial.begin(115200);
  while(!Serial) {}
  Serial.println("Start!");

  setupButtons();
}



void loop() {
  handleButtons();
}



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







// void tone(uint8_t _pin, unsigned int frequency, unsigned long duration) {
// pinMode (_pin, OUTPUT );
// analogWrite(_pin,500);
// delay(duration);
// analogWrite(_pin,0);
// }