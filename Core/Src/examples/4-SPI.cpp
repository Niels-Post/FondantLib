#include <examples.hpp>

// Include de GPIO module
#include <fd/gpio.hpp>

// Include guard. Deze zorgt ervoor dat de onderstaande code niet gecompilet zal worden als de SPI-module niet is ingeschakeld
// Dit voorkomt compile errors binnen het example project.
#ifdef FONDANT_HW_SPI

// Include de SPI module. Deze zorgt automatisch dat platformspecifieke onderdelen geladen worden
#include <fd/spi.hpp>

// Verwijzing naar de automatisch aangemaakte SPI-handle (door CubeIDE)
extern SPI_HandleTypeDef hspi1;

namespace examples::spi {

    void setup() {
        // Maak de CS pin aan als GPIO out
        fd::stm32_hal::pin_out::setup(GPIOA, GPIO_PIN_4);
    }


    void run() {
        // LET OP: voordat een pin_out of pin_in werkt moet deze al ingesteld zijn op de microcontroller als pin_out (dus in de STM32 IDE)
        auto cs_pin = fd::stm32_hal::pin_out{GPIOA, GPIO_PIN_4};

        // Maak een SPI-busobject aan
        // Hierbij houden we DMA uit, en stellen we de timeout in op 1000 ms
        auto bus = fd::stm32_hal::spi(&hspi1, false, 1000, cs_pin);


        // Stel 4 bytes aan data op
        uint8_t data[] = {0, 5, 0, 10};

        while (true) {
            // Verzend de 4 bytes en wacht tot deze voltooid is
            bus.transmit_wait(data, 4);

            // Voor de vorm veranderen we 1 byte
            data[0]++;
        }
    }

}

#endif