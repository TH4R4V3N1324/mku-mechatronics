#include <Arduino.h>
#include "sound.h"
#include "ultraSonic.h"
#include "proximity.h"
#include "waterLevel.h"

Sound soundSensor(25);
UltraSonic ultraSonicSensor(33, 32);
Proximity proximitySensor(34);
WaterLevel waterLevelSensor(26);

// Sampling periods in milliseconds
const unsigned long SOUND_INTERVAL      = 50;   // 20 Hz
const unsigned long ULTRASONIC_INTERVAL = 200;  // 5 Hz
const unsigned long PIR_INTERVAL        = 500;  // 2 Hz
const unsigned long WATER_INTERVAL      = 1000; // 1 Hz
const unsigned long PRINT_INTERVAL      = 200;  // 5 Hz

unsigned long lastSound = 0;
unsigned long lastUltraSonic = 0;
unsigned long lastPir = 0;
unsigned long lastWater = 0;
unsigned long lastPrint = 0;

// Latest reading from each sensor
int soundLevel = 0;
long distanceCm = 0;
bool motion = false;
int waterLevel = 0;

void setup() {
  Serial.begin(115200);
  soundSensor.begin();
  ultraSonicSensor.begin();
  proximitySensor.begin();
  waterLevelSensor.begin();
}

void loop() {
  unsigned long now = millis();

  if (now - lastSound >= SOUND_INTERVAL) {
    lastSound += SOUND_INTERVAL;
    soundLevel = soundSensor.getLevel();
  }

  if (now - lastUltraSonic >= ULTRASONIC_INTERVAL) {
    lastUltraSonic += ULTRASONIC_INTERVAL;
    distanceCm = ultraSonicSensor.getDistance();
  }

  if (now - lastPir >= PIR_INTERVAL) {
    lastPir += PIR_INTERVAL;
    motion = proximitySensor.isObjectDetected();
  }

  if (now - lastWater >= WATER_INTERVAL) {
    lastWater += WATER_INTERVAL;
    waterLevel = waterLevelSensor.getLevel();
  }

  if (now - lastPrint >= PRINT_INTERVAL) {
    lastPrint += PRINT_INTERVAL;
    Serial.print("Sound: ");
    Serial.print(soundLevel);
    Serial.print(" | Distance (cm): ");
    Serial.print(distanceCm);
    Serial.print(" | Motion: ");
    Serial.print(motion ? "YES" : "NO");
    Serial.print(" | Water level: ");
    Serial.println(waterLevel);
  }
}
