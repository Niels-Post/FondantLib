#include <stm32f1xx_hal.h>
#include <fd/i2c.hpp>
#include <cstring>
#include <cstdio>
#include "fd/peripherals/displays/hd44780.hpp"
#include "fd/targets/base/core.hpp"

extern I2C_HandleTypeDef hi2c1;
namespace examples::i2c_hd44780 {

    void setup() {
    }


    void run() {
        // Maak een pin_out aan voor PC13
        auto bus = fd::stm32_hal::i2c(hi2c1, false, 1000 );
        auto screen = fd::peripherals::hd44780(bus, 4, 20, 0x27);

        uint8_t data[] = {0, 5, 0, 0};

        volatile fd::i2c_status read_status;
        volatile fd::i2c_status wait_status;

        char output[20];

        int i = 0;
        while (true) {
            // Lees de input pin en schrijf de waarde naar de interne LED
            snprintf(output, 20, "Test %d", i++);
            screen.display_string(output, 1);
            fd::sleep(10);
        }
    }

}