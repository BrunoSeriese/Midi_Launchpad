#ifndef PLAY_SOUNDS_H
#define PLAY_SOUNDS_H
#include <Arduino.h>

#include <SD.h>
#include <FS.h>



void add_buffers(char* resultBuffer, char* buffer, int length) {
    for(int i=0; i < length; i++) {
        resultBuffer[i] = (resultBuffer[i] + buffer[i])/2; 
    }
}


class Sound
{
    private:
        
        
    public:
        File source;

        int16_t buffer[512];
        bool isPlaying = false;

        Sound() {  
        };

        Sound(String soundPath) {
            source = SD.open(soundPath, "r"); 
            if (!source) {
                Serial.println(soundPath +" not found.");
            } else {
                Serial.println(soundPath+" started!");
                isPlaying = true;
            }    
        };

        ~Sound() {
            source.close();
        };

        void update() {
            source.readBytes((char*)buffer, 512);
            if (isFinished()) {
                isPlaying = false;
            }
        };
        bool isFinished() {
            return source.position() > (source.size()-1);
        };

};




class Play_sounds
{
private:
    Sound soundBuffer[16];
    int index = 0;

    void updateIndex() {
        index++;
        if (index >= 16) {index=0;}
    }

public:
    int16_t buffer[512];

    Play_sounds() {};
    ~Play_sounds() {};

    void play(String soundPath) {
        soundBuffer[index] = Sound(soundPath);
        updateIndex();
    };
 
    void update_sounds() {
        for(int i=0; i < 512; i++) {
            buffer[i] = 0;
        }

        for (int i =0; i < 16; i++) {
            if (soundBuffer[i].isPlaying) {
                // Serial.println(soundBuffer[i].source.fullName());
                soundBuffer[i].update();
                add_buffers((char*)buffer, (char*)soundBuffer[i].buffer, 512);
            }
        }
    };
};








#endif