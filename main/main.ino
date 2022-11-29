uint8_t pins[10] = {2,3,4,5,6,A4,A3,A2,A1,A0};

// flat array where the bool values of buttons pressed will be stored
bool buttons[10];

void setup() {
    Serial.begin(115200);
    Serial.println("Start");

    // setup the correct input and output pins
    for (int i = 0; i < 10; i++) {
        pinMode(pins[i], INPUT_PULLUP);
    }
}

void loop() {
    // updates the buttons
    for(int i = 0; i < 10; i++) {
        buttons[i] = !digitalRead(pins[i]);
    }
    
    
    
    delay(10);
}


void printButtons() {
    for(int i = 0; i < 10; i++) {
        Serial.print(buttons[i]);
        if (i != 9) {
            Serial.print(", ");
        } else {
            Serial.println();
        }
    }
}
