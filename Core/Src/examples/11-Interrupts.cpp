#include <stm32f1xx_hal.h>
#include <cstdio>
#include "fd/peripherals/displays/hd44780.hpp"
#include "fd/peripherals/input/keypad_matrix_4x4.hpp"
#include "fd/targets/stm32_hal/interrupt.hpp"
#include "fd/targets/base/core.hpp"

#include <fd/gpio.hpp>

#ifdef FONDANT_HW_I2C

#include <fd/fondant.hpp>

extern I2C_HandleTypeDef hi2c1;
namespace examples::interrupts {

    void setup() {
        fd::stm32_hal::pin_out::setup(GPIOC, GPIO_PIN_13);
    }


    void run() {
        auto pinOut = fd::stm32_hal::pin_out{GPIOC, GPIO_PIN_13};

        auto func = [&pinOut](fd::stm32_hal::interrupt_data data) {
            static uint32_t last_ticks = 0;
            uint32_t new_ticks = fd::stm32_hal::get_current_ticks();
            if((new_ticks - last_ticks) > 100) {
                pinOut.toggle();
                last_ticks = new_ticks;
            }
        };

        fd::stm32_hal::interrupt_handler.registerListener(fd::stm32_hal::interrupts::ExternalInterrupt, func );


        while (true) {
//            fd::stm32_hal::interrupt_handler.call(fd::stm32_hal::interrupts::ExternalInterrupt, {});
            fd::sleep(100);
        }
    }

}

#endif