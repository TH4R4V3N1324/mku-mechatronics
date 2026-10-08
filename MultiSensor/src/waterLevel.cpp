#include "waterLevel.h"

WaterLevel::WaterLevel(int sensorPin) {
    this->sensorPin = sensorPin;
}

void WaterLevel::begin() {
    pinMode(sensorPin, INPUT);
}

int WaterLevel::getLevel() {
    return analogRead(sensorPin);
}