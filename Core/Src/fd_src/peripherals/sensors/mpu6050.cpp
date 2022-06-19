#include <fd/peripherals/sensors/mpu6050.hpp>

using fd::peripherals::mpu6050;

void fd::peripherals::mpu6050::readRegister(mpu6050::Register reg, uint8_t *data, uint8_t length) {
    bus.read_reg_wait(address, static_cast<uint16_t>(reg), 1, data, length);
}

void fd::peripherals::mpu6050::writeRegister(mpu6050::Register reg, uint8_t data) {
    bus.write_reg_wait(address, static_cast<uint16_t>(reg), 1, &data, 1);
}

void fd::peripherals::mpu6050::setRegisterBits(mpu6050::Register reg, uint8_t bitMask, uint8_t newValue) {
    uint8_t registerValue;
    readRegister(reg, &registerValue, 1);
    registerValue &= ~bitMask;
    registerValue |= newValue;
    writeRegister(reg, registerValue);
}



void mpu6050::readData() {
    setSleepEnabled(false);
    readRegister(Register::ACCEL_XOUT_H, data, 14);
}

void mpu6050::setSampleRateDivider(uint8_t divider) {
    writeRegister(Register::SMPLRT_DIV, divider);
}

void mpu6050::setGyroFullScaleRange(const mpu6050::GyroFullScaleRange &range) {
    setRegisterBits(Register::GYRO_CONFIG, (0x3 << 3), static_cast<uint8_t>(range) << 3);
}

void mpu6050::setAccelFullScaleRange(const mpu6050::AccelFullScaleRange &range) {
    setRegisterBits(Register::ACCEL_CONFIG, (0x3 << 3), static_cast<uint8_t>(range) << 3);

}

void mpu6050::setI2CBypassEnabled(bool enabled) {
    setRegisterBits(Register::INT_PIN_CFG, 0x1 << 2, enabled << 1);
}

void mpu6050::setTempEnabled(bool enabled) {
    setRegisterBits(Register::PWR_MGMT_1, 0x1 << 3, enabled << 3);
}

void mpu6050::resetSignalPaths(bool resetGyro, bool resetAccel, bool resetTemp) {

}

void mpu6050::resetSignalPathsAndRegisters() {

}

uint16_t mpu6050::getAccelX() {
    uint16_t AccX = ((data[0]) | data[1]);
    if(AccX > 32768){
        AccX = AccX - 65536;
    }
    return AccX;
}

uint16_t mpu6050::getAccelY() {
    uint16_t AccY = ((data[2] << 8) | data[3]);
    if(AccY > 32768){
        AccY = AccY - 65536;
    }
    return AccY;
}

uint16_t mpu6050::getAccelZ() {
    uint16_t AccZ = ((data[4] << 8) | data[5]);
    if(AccZ > 32768){
        AccZ = AccZ - 65536;
    }
    return AccZ;
}

double fd::peripherals::mpu6050::getTemp() {
     int16_t tempreading = (data[6] << 8) | data[7];
    double temp = (tempreading / 340.0 + 36.53);
    return temp;
}



int mpu6050::getGyroX() {
    int GyroX = ((data[8] << 8) | data[9]);
    if(GyroX > 32768){
        GyroX -= 65536;
    }
    return GyroX;
}

int mpu6050::getGyroY() {
    int GyroY = ((data[10] << 8) | data[11]);
    if(GyroY > 32768){
        GyroY -= 65536;
    }
    return GyroY;
}

int mpu6050::getGyroZ() {
    int GyroZ = ((data[12] << 8) | data[13]);
    if(GyroZ > 32768){
        GyroZ -= 65536;
    }
    return GyroZ;
}

fd::peripherals::mpu6050::mpu6050(fd::i2c_base &bus, uint16_t address) : bus(bus), address(address) {}

void fd::peripherals::mpu6050::setSleepEnabled(bool enabled) {
    setRegisterBits(Register::PWR_MGMT_1, 1 << 6, enabled << 6);
}

uint8_t fd::peripherals::mpu6050::getWhoAmI() {
    uint8_t id;
    readRegister(fd::peripherals::mpu6050::Register::WHO_AM_I, &id, 1);
    return id;
}


