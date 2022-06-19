#include <examples.hpp>

// Include de GPIO module
#include "fd/gpio.hpp"


namespace examples::pininpinout {

    void setup() {
        fd::stm32_hal::pin_out::setup(GPIOC, GPIO_PIN_13);
        fd::stm32_hal::pin_in::setup(GPIOA, GPIO_PIN_15, fd::stm32_hal::pin_pull::UP);
    }

    void run() {
        // LET OP: voordat een pin_out of pin_in werkt moet deze al ingesteld zijn op de microcontroller als pin_out (dus in de STM32 IDE)

        // Maak een pin_out aan voor PC13 (de onboard LED)
        auto led_pin = fd::stm32_hal::pin_out(GPIOC, GPIO_PIN_13);

        // Maak een pin_in voor PA15
        auto in_pin = fd::stm32_hal::pin_in(GPIOA, GPIO_PIN_15);

        while (true) {
            // Lees de input pin en schrijf de waarde naar de interne LED
            led_pin.write(in_pin.read());
        }
    }

}