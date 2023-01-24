
int buttonState = 0;

int buttons[24] = {53,39,38,36,47,41,45,43,
                   52,46,22,37,40,49,44,27,
                   30,31,48,35,34,42,26,25};

int frequencies[24] = {266,266,266,266,266,
                      266,266,266,266,266,
                      266,266,266,266,266,};
                   
void setup() {
  // put your setup code here, to run once:

  for (int i = 0; i < 24; i++){
  pinMode(buttons[i], INPUT_PULLUP);
}

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  for (int i = 0; i < 24; i++){
    buttonState = digitalRead(buttons[i]);
  if ( buttonState == LOW){
      Serial.println("button:" + String(i+1) + "has been pressed");
      // speelt een note af voor x aantal seconden
      tone(1,frequencies[i],1);
      delay(500);
  }
}
  
}

void tone(uint8_t _pin, unsigned int frequency, unsigned long duration) {
pinMode (_pin, OUTPUT );
analogWriteFreq(frequency);
analogWrite(_pin,500);
delay(duration);
analogWrite(_pin,0);
}