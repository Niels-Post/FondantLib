#include <stm32f1xx_hal.h>
#include <fd/fondant_targets.hpp>

#ifdef FONDANT_HW_I2C
#include <fd/i2c.hpp>
#include "fd/fondant.hpp"

// Verwijzing naar de door STM32IDE aangemaakte bushandle
extern I2C_HandleTypeDef hi2c1;

namespace examples::i2c {

    void setup() {
    }


    void run() {
        // Maak I2C busobject aan
        auto bus = fd::stm32_hal::i2c(hi2c1, false, 1000 );

        uint8_t data[] = {0, 5, 0, 0};

        volatile fd::i2c_status read_status;
        volatile fd::i2c_status wait_status;

        while (true) {
            // Voer een read transactie uit
            read_status = bus.read(0x15, data, 4);
            wait_status = bus.wait();

            // Deze functie doet niks, maar het is makkelijker om hier een breakpoint op aan te kunnen brengen
            fd::none();
        }
    }

}
#endif