#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

// Use pins 2 and 3 to communicate with DFPlayer Mini
static const uint8_t PIN_MP3_TX = 2; // Connects to module's RX 
static const uint8_t PIN_MP3_RX = 3; // Connects to module's TX 
SoftwareSerial softwareSerial(PIN_MP3_RX, PIN_MP3_TX);

// Create the Player object
DFRobotDFPlayerMini player;

// setup controll vars
#define playPin A2
#define volumeUpPin A1
#define volumeDownPin A0
bool playIsPressed = false;
bool volumeUpIsPressed = false;
bool volumeDownIsPressed = false;


void setup() {
    // setup controlls
    pinMode(playPin, INPUT_PULLUP);
    pinMode(volumeUpPin, INPUT_PULLUP);
    pinMode(volumeDownPin, INPUT_PULLUP);


  // Init USB serial port for debugging
  Serial.begin(9600);
  // Init serial port for DFPlayer Mini
  softwareSerial.begin(9600);

  // Start communication with DFPlayer Mini
  if (player.begin(softwareSerial)) {
    Serial.println("OK");

    // Set volume to maximum (0 to 30).
    player.volume(15);
    // Play the first MP3 file on the SD card
    // player.play(1);
    delay(500);
  } else {
    Serial.println("Connecting to DFPlayer Mini failed!");
  }
}



bool isPlaying = false;

int bpm = 80;
int beat[] = {2, 3, 4, 0, 2, 0, 4, 0};
int beatLength = sizeof(beat)/sizeof(beat[0])-1;

double period = 60000/bpm/(beatLength/2);
unsigned long tStart = millis();
int index = 0;
void loop() {
    handleControlls();

    if (isPlaying && (millis() - tStart) > period) {
        tStart = millis();

        if (beat[index] != 0) {player.play(beat[index]);}   
        
        Serial.print(index);
        if (index != beatLength) {
            Serial.print(", "); 
        } else {
            Serial.println();
        }

        index = (index >= beatLength) ? 0 : index+1;
    }
}


void handleControlls() {
    if (!digitalRead(playPin) && playIsPressed == false) {
        isPlaying = !isPlaying;
        playIsPressed = true;
    } else if (digitalRead(playPin) && playIsPressed == true){
        playIsPressed = false;
    }

    if (!digitalRead(volumeUpPin) && volumeUpIsPressed == false) {
        player.volumeUp();
        volumeUpIsPressed = true;
    } else if (digitalRead(volumeUpPin) && volumeUpIsPressed == true) {
        volumeUpIsPressed = false;
    }

    if (!digitalRead(volumeDownPin) && volumeDownIsPressed == false) {
        player.volumeDown();
        volumeDownIsPressed = true;
    } else if (digitalRead(volumeDownPin) && volumeDownIsPressed == true) {
        volumeDownIsPressed = false;
    }
}