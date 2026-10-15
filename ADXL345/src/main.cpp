#include <Arduino.h>
#include <SPI.h>
#include "ADXL345.h"
#include "kalman.h"

#ifndef ADXL345_USE_SPI
#define ADXL345_USE_SPI 0
#endif

#if ADXL345_USE_SPI
ADXL345 accelerometer(5, SPI); // SPI with chip-select on GPIO 5
#else
ADXL345 accelerometer(0x53); // Create an instance of the ADXL345 class with the default I2C address
#endif

// One filter per axis: each Kalman instance holds a single state estimate
Kalman kalmanX;
Kalman kalmanY;
Kalman kalmanZ;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  if (!accelerometer.begin()) {
    Serial.println("Failed to initialize ADXL345");
    while (1); // Stop if initialization fails
  }
  accelerometer.calibrate();
  Serial.println("ADXL345 calibrated successfully");

  // Seed the filter with a real reading; leaving q/r/p at 0 makes the gain 0/0 = NaN
  accelerometer.readAcceleration();
  kalmanX.init(0.05, 8.0, 10.0, accelerometer.getX());
  kalmanY.init(0.05, 8.0, 10.0, accelerometer.getY());
  kalmanZ.init(0.05, 8.0, 10.0, accelerometer.getZ());
}

void loop() {
  // put your main code here, to run repeatedly:
  accelerometer.readAcceleration();
  float ax = accelerometer.getX();
  float ay = accelerometer.getY();
  float az = accelerometer.getZ();

  float rawTiltAngle = atan2(ay, az) * 180.0 / PI;

  // Apply Kalman filter to the acceleration values
  float filteredAx = kalmanX.update(ax);
  float filteredAy = kalmanY.update(ay);
  float filteredAz = kalmanZ.update(az);
  float filteredTiltAngle = atan2(filteredAy, filteredAz) * 180.0 / PI;

  Serial.print(">Raw Tilt Angle: ");
  Serial.println(rawTiltAngle);
  Serial.print(">Filtered Tilt Angle: ");
  Serial.println(filteredTiltAngle);

  delay(100); // Delay for readability
}
