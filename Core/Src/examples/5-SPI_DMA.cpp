#include <examples.hpp>

#include <fd/gpio.hpp>

#include <fd/fondant_targets.hpp>

#ifdef FONDANT_HW_SPI

#include <fd/spi.hpp>

extern SPI_HandleTypeDef hspi1;

namespace examples::spi_dma {

    void setup() {
        fd::stm32_hal::pin_out::setup(GPIOA, GPIO_PIN_4);
    }


    void run() {
        // LET OP: voordat een pin_out of pin_in werkt moet deze al ingesteld zijn op de microcontroller als pin_out (dus in de STM32 IDE)
        auto cs_pin = fd::stm32_hal::pin_out{GPIOA, GPIO_PIN_4};


        // Maak een pin_out aan voor PC13
        auto bus = fd::stm32_hal::spi(&hspi1, true, 1000, cs_pin);

        uint8_t data[] = {0, 5, 0, 0};

        while (true) {
            // Lees de input value en schrijf de waarde naar de interne LED
            data[0] = static_cast<uint8_t>(bus.transmit(data, 4));
            data[1] = static_cast<uint8_t>(bus.wait());
        }
    }

}

#endif