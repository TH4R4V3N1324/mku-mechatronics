#ifndef SOUND_H
#define SOUND_H

#include <Arduino.h>

class Sound {
public:
    Sound(int sensorPin);
    void begin();
    int getLevel();
private:
    int sensorPin;
};

#endif // SOUND_H
