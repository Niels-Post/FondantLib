#include <cstdint>
#include <fd/peripherals/sensors/bme280.hpp>
#include "fd/targets/base/core.hpp"

using fd::peripherals::bme280;

bme280::bme280(fd::i2c_base &i2cBus, const uint16_t &address) : i2c_bus(i2cBus), address(address) {
    init();
}

void bme280::init() {
    storeTrimParameters();
    setSettings();
}

void bme280::storeTrimParameters() {
    readRegister(Register::TRIM_TEMP, trim_temp, sizeof(trim_temp));
    readRegister(Register::TRIM_PRES, trim_pres, sizeof(trim_pres));
    readRegister(Register::TRIM_HUM1, trim_hum1, sizeof(trim_hum1));
    readRegister(Register::TRIM_HUM2, trim_hum2, sizeof(trim_hum2));
}

void bme280::setSettings(bme280::Mode mode,
                         bme280::Oversampling humidityOversamplingRate,
                         bme280::Oversampling pressureOversamplingRate,
                         bme280::Oversampling temperatureOversamplingRate,
                         bme280::StandbyTime standbyTime,
                         bme280::Filter filter) {
    uint8_t ctrl_hum  = (static_cast<uint8_t>(humidityOversamplingRate));
    uint8_t ctrl_meas = (static_cast<uint8_t>(temperatureOversamplingRate) << 5) |
                        (static_cast<uint8_t>(pressureOversamplingRate) << 2) |
                        (static_cast<uint8_t>(mode));
    uint8_t config    = (static_cast<uint8_t>(standbyTime) << 5) |
                        (static_cast<uint8_t>(filter) << 2);

    writeRegister(Register::CTRL_HUM, ctrl_hum);
    writeRegister(Register::CTRL_MEAS, ctrl_meas);
    writeRegister(Register::CONFIG, config);

}

void bme280::softReset() {
    writeRegister(Register::RESET, 0xB6);
    fd::sleep(2);
    init();
}

void bme280::writeRegister(bme280::Register reg, uint8_t *data, uint8_t size) {
    i2c_bus.write_reg_wait(address, static_cast<uint16_t>(reg), 1, data, size);
}

void bme280::writeRegister(bme280::Register reg, uint8_t data) {
    writeRegister(reg, &data, 1);
}

void bme280::readRegister(bme280::Register reg, uint8_t *data, uint8_t size) {
    i2c_bus.read_reg_wait(address, static_cast<uint16_t>(reg), 1, data, size);
}

uint8_t bme280::readRegister(bme280::Register reg) {
    uint8_t data;
    readRegister(reg, &data, 1);
    return data;
}

void fd::peripherals::bme280::readData() {
    uint8_t data[8];
    int32_t data_32[8];
    setSettings();
    readRegister(Register::PRESS, data, 8);
    for (uint8_t i = 0; i < 8; i++) {
        data_32[i] = static_cast<int32_t>(data[i]);
    }

    raw_pres = (data_32[0] << 12) | (data_32[1] << 4) | (data_32[2] >> 4);
    raw_temp = (data_32[3] << 12) | (data_32[4] << 4) | (data_32[5] >> 4);
    raw_hum  = (data_32[6] << 8) | data_32[7];

    // Temperature wordt gebruikt in andere metingen en moet altijd berekend worden
    calculateTemperature();
    calculated_hum  = -1.0;
    calculated_pres = -1.0;
}

void fd::peripherals::bme280::calculateTemperature() {
    int32_t var1, var2, temp;

    uint16_t dig_T1 = (trim_temp[1] << 8) | trim_temp[0];
    int16_t  dig_T2 = (trim_temp[3] << 8) | trim_temp[2];
    int16_t  dig_T3 = (trim_temp[5] << 8) | trim_temp[4];

    var1            = ((((raw_temp >> 3) - ((int32_t) dig_T1 << 1))) * ((int32_t) dig_T2)) >> 11;
    var2            = (((((raw_temp >> 4) - ((int32_t) dig_T1)) * ((raw_temp >> 4) - ((int32_t) dig_T1))) >> 12) *
                       ((int32_t) dig_T3))
            >> 14;
    t_fine          = var1 + var2;
    calculated_temp = ((t_fine * 5 + 128) >> 8) / 100.0;
}

void fd::peripherals::bme280::calculatePressure() {
    // Code based on calibration algorthim provided by Bosch.
    int64_t var1, var2, pressure;

    uint16_t dig_P1 = (trim_pres[1] << 8) | trim_pres[0];
    int16_t  dig_P2 = (trim_pres[3] << 8) | trim_pres[2];
    int16_t  dig_P3 = (trim_pres[5] << 8) | trim_pres[4];
    int16_t  dig_P4 = (trim_pres[7] << 8) | trim_pres[6];
    int16_t  dig_P5 = (trim_pres[9] << 8) | trim_pres[8];
    int16_t  dig_P6 = (trim_pres[11] << 8) | trim_pres[10];
    int16_t  dig_P7 = (trim_pres[13] << 8) | trim_pres[12];
    int16_t  dig_P8 = (trim_pres[15] << 8) | trim_pres[14];
    int16_t  dig_P9 = (trim_pres[17] << 8) | trim_pres[16];

    var1 = (int64_t) t_fine - 128000;
    var2 = var1 * var1 * (int64_t) dig_P6;
    var2 = var2 + ((var1 * (int64_t) dig_P5) << 17);
    var2 = var2 + (((int64_t) dig_P4) << 35);
    var1 = ((var1 * var1 * (int64_t) dig_P3) >> 8) + ((var1 * (int64_t) dig_P2) << 12);
    var1 = (((((int64_t) 1) << 47) + var1)) * ((int64_t) dig_P1) >> 33;
    if (var1 == 0) {
        calculated_pres = -1.0;
        return;
    }                                                         // Don't divide by zero.
    pressure = 1048576 - raw_pres;
    pressure = (((pressure << 31) - var2) * 3125) / var1;
    var1     = (((int64_t) dig_P9) * (pressure >> 13) * (pressure >> 13)) >> 25;
    var2     = (((int64_t) dig_P8) * pressure) >> 19;
    pressure = ((pressure + var1 + var2) >> 8) + (((int64_t) dig_P7) << 4);

    calculated_pres = ((uint32_t) pressure) / 256.0 / 100000.0;
}

void fd::peripherals::bme280::calculateHumidity() {
    // Code based on calibration algorthim provided by Bosch.
    int32_t var1;
    uint8_t dig_H1 = trim_hum1[0];
    int16_t dig_H2 = (trim_hum2[1] << 8) | trim_hum2[0];
    uint8_t dig_H3 = trim_hum2[2];
    int16_t dig_H4 = ((int8_t) trim_hum2[3] * 16) | (0x0F & trim_hum2[4]);
    int16_t dig_H5 = ((int8_t) trim_hum2[5] * 16) | ((trim_hum2[4] >> 4) & 0x0F);
    int8_t  dig_H6 = trim_hum2[6];

    var1 = (t_fine - ((int32_t) 76800));
    var1 = (((((raw_hum << 14) - (((int32_t) dig_H4) << 20) - (((int32_t) dig_H5) * var1)) +
              ((int32_t) 16384)) >> 15) * (((((((var1 * ((int32_t) dig_H6)) >> 10) * (((var1 *
                                                                                        ((int32_t) dig_H3)) >> 11) +
                                                                                      ((int32_t) 32768))) >> 10) +
                                             ((int32_t) 2097152)) *
                                            ((int32_t) dig_H2) + 8192) >> 14));
    var1 = (var1 - (((((var1 >> 15) * (var1 >> 15)) >> 7) * ((int32_t) dig_H1)) >> 4));
    var1 = (var1 < 0 ? 0 : var1);
    var1 = (var1 > 419430400 ? 419430400 : var1);
    calculated_hum = ((uint32_t)(var1 >> 12)) / 1024.0;
}

float fd::peripherals::bme280::getTemperature() {
    return calculated_temp;
}

float fd::peripherals::bme280::getHumidity() {
    if (calculated_hum == -1.0) {
        calculateHumidity();
    }
    return calculated_hum;
}

float fd::peripherals::bme280::getPressure() {
    if (calculated_pres == -1.0) {
        calculatePressure();
    }
    return calculated_pres;
}
