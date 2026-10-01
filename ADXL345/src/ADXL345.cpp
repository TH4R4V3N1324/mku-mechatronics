#include "ADXL345.h"

ADXL345::ADXL345(int i2cAddress)
    : i2cAddress(i2cAddress), chipSelect(0), spi(nullptr), useSPI(false), spiSettings(ADXL345_SPI_CLOCK_HZ, MSBFIRST, SPI_MODE3) {}

ADXL345::ADXL345(uint8_t chipSelect, SPIClass& spi)
    : i2cAddress(0), chipSelect(chipSelect), spi(&spi), useSPI(true), spiSettings(ADXL345_SPI_CLOCK_HZ, MSBFIRST, SPI_MODE3) {}

bool ADXL345::begin() {
    if (useSPI) {
        pinMode(chipSelect, OUTPUT);
        digitalWrite(chipSelect, HIGH);
        spi->begin();
    } else {
        Wire.begin();
        Wire.setClock(400000); // Set I2C clock speed to 400kHz
    }

    uint8_t deviceId;
    readRegister(ADXL345_REG_DEVID, &deviceId, 1);
    if (deviceId != ADXL345_DEVICE_ID) {
        return false;
    }

    writeRegister(ADXL345_REG_POWER_CTL, ADXL345_POWER_CTL_MEASURE);
    return true;
}

void ADXL345::calibrate() {
    offsetX = 0.0f;
    offsetY = 0.0f;
    offsetZ = 0.0f;

    for (int i = 0; i < 1000; ++i) {
        readAcceleration();
        offsetX += ax;
        offsetY += ay;
        offsetZ += az;
        delay(1);
    }
    offsetX = -(offsetX / 1000.0f);
    offsetY = -(offsetY / 1000.0f);
    offsetZ = 1.0f - (offsetZ / 1000.0f);
}

void ADXL345::readAcceleration() {
    uint8_t data[6];
    readRegister(ADXL345_REG_DATAX0, data, 6);

    ax = (int16_t)((data[1] << 8) | data[0]) * 0.004; // Convert to g
    ay = (int16_t)((data[3] << 8) | data[2]) * 0.004;
    az = (int16_t)((data[5] << 8) | data[4]) * 0.004;
}

void ADXL345::writeRegister(uint8_t reg, uint8_t value) {
    if (useSPI) {
        spi->beginTransaction(spiSettings);
        digitalWrite(chipSelect, LOW);
        spi->transfer(reg & ADXL345_SPI_REGISTER_MASK);
        spi->transfer(value);
        digitalWrite(chipSelect, HIGH);
        spi->endTransaction();
        return;
    }

    Wire.beginTransmission(i2cAddress);
    Wire.write(reg);
    Wire.write(value);
    Wire.endTransmission();
}

void ADXL345::readRegister(uint8_t reg, uint8_t* buffer, size_t length) {
    if (useSPI) {
        spi->beginTransaction(spiSettings);
        digitalWrite(chipSelect, LOW);
        spi->transfer(reg | ADXL345_SPI_READ_BIT |
                      (length > 1 ? ADXL345_SPI_MULTI_BYTE_BIT : 0));
        for (size_t i = 0; i < length; ++i) {
            buffer[i] = spi->transfer(ADXL345_SPI_DUMMY_BYTE);
        }
        digitalWrite(chipSelect, HIGH);
        spi->endTransaction();
        return;
    }

    Wire.beginTransmission(i2cAddress);
    Wire.write(reg);
    Wire.endTransmission(false); // Send a restart condition

    Wire.requestFrom(i2cAddress, length);
    for (size_t i = 0; i < length; i++) {
        buffer[i] = Wire.read();
    }
}