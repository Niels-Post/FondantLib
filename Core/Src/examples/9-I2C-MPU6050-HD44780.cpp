#include <stm32f1xx_hal.h>
#include <fd/i2c.hpp>
#include <cstring>
#include <cstdio>
#include "fd/peripherals/displays/hd44780.hpp"
#include "fd/targets/base/core.hpp"
#include "fd/peripherals/sensors/mpu6050.hpp"

extern I2C_HandleTypeDef hi2c1;
namespace examples::i2c_mpu6050_hd44780 {

    void setup() {
    }


    void run() {
        // Maak een pin_out aan voor PC13
        auto bus     = fd::stm32_hal::i2c(hi2c1, false, 1000);
        auto screen  = fd::peripherals::hd44780(bus, 4, 20, 0x27);
        auto sensor  = fd::peripherals::mpu6050(bus);


        char output[20];

        int i = 0;
        while (true) {
            // Lees de input value en schrijf de waarde naar de interne LED
            sensor.readData();
            float temp   = sensor.getTemp();
            int acc[3]   = {sensor.getAccelX(), sensor.getAccelY(), sensor.getAccelZ()};
            int gyr[3]   = {sensor.getGyroX(), sensor.getGyroY(), sensor.getGyroZ()};
            uint8_t chipid1;
            sensor.readRegister(fd::peripherals::mpu6050::Register::WHO_AM_I, &chipid1, 1);

//            fd::sleep(100);


            snprintf(output, 20, "ID: %d   ", chipid1);
            screen.display_string(output, 1);
            snprintf(output, 20, "A: %04d-%04d-%04d   ", acc[0],acc[1],acc[2]);
            screen.display_string(output, 2);
            snprintf(output, 20, "G: %04d-%04d-%04d   ", gyr[0],gyr[1],gyr[2]);
            screen.display_string(output, 3);
            snprintf(output, 20, "Temp : %.2f   ", temp);
            screen.display_string(output, 4);
//            fd::sleep(100);
        }
    }

}