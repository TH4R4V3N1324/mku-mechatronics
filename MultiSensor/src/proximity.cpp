#include "proximity.h"

Proximity::Proximity(int sensorPin) {
  this->sensorPin = sensorPin;
}

void Proximity::begin() {
  pinMode(sensorPin, INPUT);
}

bool Proximity::isObjectDetected() {
  return digitalRead(sensorPin) == HIGH;
}