#ifndef ADXL345_H
#define ADXL345_H

#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>

constexpr uint8_t ADXL345_I2C_ADDRESS = 0x53; // Default I2C address for ADXL345
constexpr uint8_t ADXL345_REG_DEVID = 0x00; // Device ID register
constexpr uint8_t ADXL345_REG_POWER_CTL = 0x2D; // Power control register
constexpr uint8_t ADXL345_REG_DATAX0 = 0x32; // X-axis data register (low)
constexpr uint8_t ADXL345_REG_DATAX1 = 0x33; // X-axis data register (high)
constexpr uint8_t ADXL345_REG_DATAY0 = 0x34; // Y-axis data register (low)
constexpr uint8_t ADXL345_REG_DATAY1 = 0x35; // Y-axis data register (high)
constexpr uint8_t ADXL345_REG_DATAZ0 = 0x36; // Z-axis data register (low)
constexpr uint8_t ADXL345_REG_DATAZ1 = 0x37; // Z-axis data register (high)
constexpr uint8_t ADXL345_OFSX = 0x1E; // X-axis offset register
constexpr uint8_t ADXL345_OFSY = 0x1F; // Y-axis offset register
constexpr uint8_t ADXL345_OFSZ = 0x20; // Z-axis offset register
constexpr uint8_t ADXL345_DEVICE_ID = 0xE5;
constexpr uint8_t ADXL345_POWER_CTL_MEASURE = 0x08;
constexpr uint8_t ADXL345_SPI_READ_BIT = 0x80;
constexpr uint8_t ADXL345_SPI_MULTI_BYTE_BIT = 0x40;
constexpr uint8_t ADXL345_SPI_REGISTER_MASK = 0x3F;
constexpr uint8_t ADXL345_SPI_DUMMY_BYTE = 0x00;
constexpr uint32_t ADXL345_SPI_CLOCK_HZ = 5000000;


class ADXL345 {
public:
    ADXL345(int i2cAddress = ADXL345_I2C_ADDRESS); // Default I2C address for ADXL345
    ADXL345(uint8_t chipSelect, SPIClass& spi = SPI);
    bool begin();
    void readAcceleration();
    void calibrate();
    float getX() const { return ax + offsetX; }
    float getY() const { return ay + offsetY; }
    float getZ() const { return az + offsetZ; }
private:
    int i2cAddress;
    uint8_t chipSelect;
    SPIClass* spi;
    bool useSPI;
    SPISettings spiSettings;
    void writeRegister(uint8_t reg, uint8_t value);
    void readRegister(uint8_t reg, uint8_t* buffer, size_t length);
    float ax = 0.0f, ay = 0.0f, az = 0.0f; // Acceleration values in g
    float offsetX = 0.0f, offsetY = 0.0f, offsetZ = 0.0f; // Offset values for calibration
};

#endif // ADXL345_H