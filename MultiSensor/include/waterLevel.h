#ifndef WATERLEVEL_H
#define WATERLEVEL_H

#include <Arduino.h>

class WaterLevel {
public:
    WaterLevel(int sensorPin);
    void begin();
    int getLevel();
private:
    int sensorPin;
};

#endif // WATERLEVEL_H