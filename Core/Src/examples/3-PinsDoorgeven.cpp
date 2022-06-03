#include <examples.hpp>

#include "fd/gpio.hpp"


namespace examples::pinsdoorgeven {
    void setup() {
        fd::stm32_hal::pin_out::setup(GPIOC, GPIO_PIN_13);
        fd::stm32_hal::pin_in::setup(GPIOA, GPIO_PIN_15, fd::stm32_hal::pin_pull::UP);
    }

    // Gebruik de pin_out_base en pin_in_base klassen om nauwe koppeling met een specifiek platform te vermijden
    // Bij het wisselen van platform hoeft nu alleen de constructie van pins in run() aangepast te worden
    // Let erop dat objecten altijd by reference of by pointer worden meegegeven. By value werkt niet met inheritance
    void neem_pin_over(fd::pin_out_base &outputPin, fd::pin_in_base &inputPin) {
        outputPin.write(inputPin.read());
    }

    void run() {
        // LET OP: voordat een pin_out of pin_in werkt moet deze al ingesteld zijn op de microcontroller als pin_out (dus in de STM32 IDE)

        // Maak een pin_out aan voor PC13
        auto led_pin = fd::stm32_hal::pin_out(GPIOC, GPIO_PIN_13);

        // Maak een pin_in voor PA15
        auto in_pin = fd::stm32_hal::pin_in(GPIOA, GPIO_PIN_15);

        while (true) {
            // Lees de input pin en schrijf de waarde naar de interne LED
            neem_pin_over(led_pin, in_pin);
        }
    }

}