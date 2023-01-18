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

        void update(int16_t* o_buffer) {
            source.readBytes((char*)o_buffer, 512);
            if (isFinished()) {
                isPlaying = false;
            }
        };
        bool isFinished() {
            return source.position() > (source.size()-1);
        };

};



#endif