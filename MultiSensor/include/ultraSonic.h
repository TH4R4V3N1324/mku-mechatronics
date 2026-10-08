#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include <Arduino.h>

class UltraSonic {
public:
    UltraSonic(int triggerPin, int echoPin);
    void begin();
    long getDistance();
private:
    int triggerPin;
    int echoPin;
};

#endif // ULTRASONIC_H