#include <stm32f1xx_hal.h>
#include <fd/i2c.hpp>
#include <cstring>
#include <cstdio>
#include "fd/peripherals/displays/hd44780.hpp"
#include "fd/targets/base/core.hpp"
#include "fd/peripherals/sensors/bme280.hpp"

extern I2C_HandleTypeDef hi2c1;
namespace examples::i2c_bme280_hd44780 {

    void setup() {
    }


    void run() {
        // Maak een pin_out aan voor PC13
        auto bus     = fd::stm32_hal::i2c(hi2c1, false, 1000);
        auto screen  = fd::peripherals::hd44780(bus, 4, 20, 0x27);
        auto sensor  = fd::peripherals::bme280(bus, 0x76);

        uint8_t data[] = {0, 5, 0, 0};

        volatile fd::i2c_status read_status;
        volatile fd::i2c_status wait_status;

        char output[20];

        int i = 0;
        while (true) {
            // Lees de input pin en schrijf de waarde naar de interne LED
            sensor.readData();
            float temp1   = sensor.getTemperature();
            float pres1   = sensor.getPressure();
            float hum1   = sensor.getHumidity();
            uint8_t chipid1 = sensor.readRegister(fd::peripherals::bme280::Register::ID);

            fd::sleep(100);


            snprintf(output, 20, "ID: %d   ", chipid1);
            screen.display_string(output, 1);
            snprintf(output, 20, "Temp: %.2f   ", temp1);
            screen.display_string(output, 2);
            snprintf(output, 20, "Pres: %.2f   ", pres1);
            screen.display_string(output, 3);
            snprintf(output, 20, "Hum: %.2f   ", hum1);
            screen.display_string(output, 4);
            fd::sleep(100);
        }
    }

}