#include "sound.h"

Sound::Sound(int sensorPin) {
    this->sensorPin = sensorPin;
}

void Sound::begin() {
    pinMode(sensorPin, INPUT);
}

int Sound::getLevel() {
    return analogRead(sensorPin);
}
