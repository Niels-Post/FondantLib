#include <stm32f1xx_hal.h>
#include <cstdio>
#include "fd/peripherals/displays/hd44780.hpp"
#include "fd/peripherals/input/keypad_matrix_4x4.hpp"

#include <fd/gpio.hpp>

#ifdef FONDANT_HW_I2C

#include <fd/i2c.hpp>

extern I2C_HandleTypeDef hi2c1;
namespace examples::matrix_keypad {

    void setup() {
        fd::stm32_hal::pin_out::setup(GPIOC, GPIO_PIN_13);


        fd::stm32_hal::pin_in::setup(GPIOB, GPIO_PIN_12, fd::stm32_hal::pin_pull::UP);
        fd::stm32_hal::pin_in::setup(GPIOB, GPIO_PIN_13, fd::stm32_hal::pin_pull::UP);
        fd::stm32_hal::pin_in::setup(GPIOB, GPIO_PIN_14, fd::stm32_hal::pin_pull::UP);
        fd::stm32_hal::pin_in::setup(GPIOB, GPIO_PIN_15, fd::stm32_hal::pin_pull::UP);

        fd::stm32_hal::pin_out::setup(GPIOA, GPIO_PIN_8);
        fd::stm32_hal::pin_out::setup(GPIOA, GPIO_PIN_9);
        fd::stm32_hal::pin_out::setup(GPIOA, GPIO_PIN_10);
        fd::stm32_hal::pin_out::setup(GPIOA, GPIO_PIN_11);
    }


    void run() {
        // Maak een pin_out aan voor PC13
        fd::stm32_hal::pin_out{GPIOC, GPIO_PIN_13};

        // Maak pinobjecten aan voor alle rijen en kolommen van het keypad
        fd::stm32_hal::pin_in c1{GPIOB, GPIO_PIN_12};
        fd::stm32_hal::pin_in c2{GPIOB, GPIO_PIN_13};
        fd::stm32_hal::pin_in c3{GPIOB, GPIO_PIN_14};
        fd::stm32_hal::pin_in c4{GPIOB, GPIO_PIN_15};

        fd::stm32_hal::pin_out r1{GPIOA, GPIO_PIN_8};
        fd::stm32_hal::pin_out r2{GPIOA, GPIO_PIN_9};
        fd::stm32_hal::pin_out r3{GPIOA, GPIO_PIN_10};
        fd::stm32_hal::pin_out r4{GPIOA, GPIO_PIN_11};

        // Maak de I2C bus en het schermobject voor het scherm aan
        auto bus    = fd::stm32_hal::i2c(hi2c1, false, 1000);
        auto screen = fd::peripherals::hd44780(bus, 4, 20, 0x27);
        // Maak het keypadobject aan
        auto keypad = fd::peripherals::keypad_matrix_4x4{r1, r2, r3, r4, c1, c2, c3, c4};

		bus.write()
        char output[20];

        while (true) {
            // Haal de huidige uint16 waarde van de ingedrukte knoppen op
            // Elke bit in deze waarde vertegenwoordigt een knop
            uint16_t res = keypad.getValue();

            // Weergeef de uint16-waarde
            snprintf(output, 20, "Key: %d           ", res);
            screen.display_string(output, 1);

            // Weergeef de "eerste" knop die ingedrukt is
            snprintf(output, 20, "FirstButton: %s    ", keypad.getSinglePressedButton().name);
            screen.display_string(output, 2);

        }
    }

}

#endif