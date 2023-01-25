#ifndef MIDI_CONFIG_H
#define MIDI_CONFIG_H

// define midi vars
#define MIDI_SPEED 31250
#define DEFAULT_VELOCITY 100
int activeChannel=1;
// commands
#define NOTE_ON  B10010000
#define NOTE_OFF B10000000

const int NOTEIDMAP[24] = {
    60,61,62,63,64,65,66,67,68,69,70,71,
    72,73,74,75,76,77,78,79,80,81,82,83
};
const double NOTEFREQMAP[24] = {
  261.626,277.183,293.665,311.127,329.628,349.228,369.994,391.995,415.305,440.00,466.164,493.883,
  523.251,554.365,587.330,622.254,659.225,698.456,739.989,783.991,830.609,880.00,932.328,987.767
};


void sendMIDImessage(byte status, byte data1, byte data2)
{
  Serial.write(status);
  Serial.write(data1);
  Serial.write(data2);
}

void noteOn(int note) {
  sendMIDImessage(NOTE_ON, note, DEFAULT_VELOCITY);
}

void noteOff(int note) {
  sendMIDImessage(NOTE_OFF, note, DEFAULT_VELOCITY);
}


class Note
{
  public:
  int noteId;
  double freq;
  bool isActive=false;
  Note() {}
  Note(int _noteId) : noteId(_noteId) {
    bool hasMappedFreq=false;
    for(int i=0; i<24;i++) {
        if (noteId==NOTEIDMAP[i]) {
            freq=NOTEFREQMAP[i];
            hasMappedFreq=true;
        }
    }
    if (!hasMappedFreq) {
        freq=0.0;
    }
  }
  Note(int _noteId, double _freq) : noteId(_noteId), freq(_freq) {}

  void on() {
    noteOn(noteId);
    isActive=true;
  }
  void off() {
    noteOff(noteId);
    isActive=false;
  }

  private:
};








#endif