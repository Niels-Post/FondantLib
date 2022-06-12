#include <stm32f1xx_hal.h>
#include <fd/i2c.hpp>
extern I2C_HandleTypeDef hi2c1;
namespace examples::i2c {

    void setup() {
    }


    void run() {
        // Maak een pin_out aan voor PC13
        auto bus = fd::stm32_hal::i2c(hi2c1, false, 1000 );

        uint8_t data[] = {0, 5, 0, 0};

        volatile fd::i2c_status read_status;
        volatile fd::i2c_status wait_status;

        while (true) {
            // Lees de input pin en schrijf de waarde naar de interne LED
            read_status = bus.read(0x15, data, 4);
            wait_status = bus.wait();
        }
    }

}