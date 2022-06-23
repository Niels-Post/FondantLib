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


        // Maak een SPIbus-object aan
        auto bus = fd::stm32_hal::spi(hspi1, true, 1000, cs_pin);

        uint8_t data[50] = {0};

        uint8_t j = 0;


        while (true) {
            // Verstuur de data
            bus.transmit(data,50);

            // Pas de data aan. We doen dit 5 keer om wat extra tijd te overbruggen om het verschil in snelheid duidelijker te maken
            // In een normale toepassing zou je hier bijvoorbeeld alle schermobjecten renderen voor je deze naar het scherm stuurt
            for(uint8_t i = 0; i < 5; i++) {
                for (auto &d: data) {
                    d += j;
                    j++;
                }
            }

            // Wacht totdat de SPI-peripheral klaar is zodat we niet meerdere transacties tegelijk proberen te doen
            bus.wait();
        }
    }

}

#endif