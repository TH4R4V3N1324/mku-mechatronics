#include "ultraSonic.h"

UltraSonic::UltraSonic(int triggerPin, int echoPin) {
    this->triggerPin = triggerPin;
    this->echoPin = echoPin;
}

void UltraSonic::begin() {
    pinMode(triggerPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

long UltraSonic::getDistance() {
    digitalWrite(triggerPin, LOW);
    delayMicroseconds(2);
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerPin, LOW);

    // 30 ms timeout (~5 m) so a missed echo cannot stall the other sensors; returns 0
    long duration = pulseIn(echoPin, HIGH, 30000UL);
    long distance = duration * 0.034 / 2; // Convert to centimeters
    return distance;
}