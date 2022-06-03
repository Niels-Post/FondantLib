#include <examples.hpp>

#include "fd/gpio.hpp"


namespace examples::pininpinout {

    void setup() {
        fd::stm32_hal::pin_out::setup(GPIOC, GPIO_PIN_13);
        fd::stm32_hal::pin_in::setup(GPIOA, GPIO_PIN_15, fd::stm32_hal::pin_pull::UP);
    }

    void run() {
        auto led_pin = fd::stm32_hal::pin_out(GPIOC, GPIO_PIN_13);

        auto in_pin = fd::stm32_hal::pin_in(GPIOA, GPIO_PIN_15);

        while (true) {
            led_pin.write(in_pin.read());
        }
    }

}