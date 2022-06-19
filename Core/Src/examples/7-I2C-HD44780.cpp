#include <fd/fondant_targets.hpp>

#include <cstdio>
#include "fd/peripherals/displays/hd44780.hpp"
#include "fd/targets/base/core.hpp"

#ifdef FONDANT_HW_I2C
#include <fd/i2c.hpp>
extern I2C_HandleTypeDef hi2c1;
namespace examples::i2c_hd44780 {

    void setup() {
    }


    void run() {
        // Maak de I2C bus aan
        auto bus = fd::stm32_hal::i2c(hi2c1, false, 1000 );

        // Maak het HD44780 schermobject aan
        auto screen = fd::peripherals::hd44780(bus, 4, 20, 0x27);

        char output[20];

        int i = 0;
        while (true) {
            // Formatteer een string met een int-waarde
            snprintf(output, 20, "Test %d", i++);

            // Schrijf de string naar het display op regel 1
            screen.display_string(output, 1);

            // Wacht 10 ms
            fd::sleep(10);
        }
    }

}
#endif