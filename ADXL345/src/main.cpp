#include <Arduino.h>
#include <SPI.h>
#include "ADXL345.h"

#ifndef ADXL345_USE_SPI
#define ADXL345_USE_SPI 0
#endif

#if ADXL345_USE_SPI
ADXL345 accelerometer(5, SPI); // SPI with chip-select on GPIO 5
#else
ADXL345 accelerometer(0x53); // Create an instance of the ADXL345 class with the default I2C address
#endif

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  if (!accelerometer.begin()) {
    Serial.println("Failed to initialize ADXL345");
    while (1); // Stop if initialization fails
  }
  accelerometer.calibrate();
  Serial.println("ADXL345 calibrated successfully");
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long startTime = micros();
  accelerometer.readAcceleration();
  float x = accelerometer.getX();
  float y = accelerometer.getY();
  float z = accelerometer.getZ();
  unsigned long elapsedTime = micros() - startTime;
  float dt = elapsedTime / 1000000.0f; // Convert microseconds to seconds

  Serial.print("dt: ");
  Serial.print(dt, 6);
  Serial.println(" s");
}
