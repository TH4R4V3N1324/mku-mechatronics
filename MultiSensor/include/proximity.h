#ifndef PROXIMITY_H
#define PROXIMITY_H

#include <Arduino.h>

class Proximity {
public:
    Proximity(int sensorPin);
    void begin();
    bool isObjectDetected();
private:
    int sensorPin;
};

#endif // PROXIMITY_H