#include <examples.hpp>

// Include basisfuncties van fondant (nodig voor fd_src::sleep)
#include <fd/fondant.hpp>

// Include de GPIO module
#include <fd/gpio.hpp>


void examples::helloworld::setup() {
    fd::stm32_hal::pin_out::setup(GPIOC, GPIO_PIN_13);
}

void examples::helloworld::run() {
    // Maak een pin_out_base aan voor GPIOC
    // LET OP: voordat een pin_out_base werkt moet deze al ingesteld zijn op de microcontroller als pin_out_base (dus in de STM32 IDE)
    fd::stm32_hal::pin_out internal_led(GPIOC, GPIO_PIN_13);

    while(true) {
        // Wacht 1 seconde
        fd::sleep(1000);

        // Toggle de LED
        internal_led.toggle();
    }
}