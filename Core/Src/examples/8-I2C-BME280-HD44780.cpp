#include <fd/fondant_targets.hpp>
#include <cstdio>
#include <fd/fondant.hpp>
#include "fd/peripherals/displays/hd44780.hpp"
#include "fd/peripherals/sensors/bme280.hpp"

#ifdef FONDANT_HW_I2C

#include <fd/i2c.hpp>

extern I2C_HandleTypeDef hi2c1;
namespace examples::i2c_bme280_hd44780 {

    void setup() {
    }


    void run() {
        // Maak het busobject voor de bus waar het scherm en de sensor op zitten
        auto bus = fd::stm32_hal::i2c(hi2c1, false, 1000);

        // Maak het schermobject aan
        auto screen = fd::peripherals::hd44780(bus, 4, 20, 0x27);

        // Maak het sensorobject voor de BME280 aan
        auto sensor = fd::peripherals::bme280(bus, 0x76);

        char output[20];

        while (true) {
            // Lees de data van de BME280 sensor
            sensor.readData();

            // Haal de berekende waarden van de sensor op
            uint8_t chipid = sensor.readRegister(fd::peripherals::bme280::Register::ID);
            float   temp   = sensor.getTemperature();
            float   pres   = sensor.getPressure();
            float   hum    = sensor.getHumidity();

            // Schrijf de opgehaalde waarden naar het scherm
            snprintf(output, 20, "ID: %d   ", chipid);
            screen.display_string(output, 1);
            snprintf(output, 20, "Temp: %.2f   ", temp);
            screen.display_string(output, 2);
            snprintf(output, 20, "Pres: %.2f   ", pres);
            screen.display_string(output, 3);
            snprintf(output, 20, "Hum: %.2f   ", hum);
            screen.display_string(output, 4);
            fd::sleep(100);
        }
    }

}

#endif