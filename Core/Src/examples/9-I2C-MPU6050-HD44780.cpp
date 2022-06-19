#include <fd/fondant_targets.hpp>
#include <cstdio>
#include "fd/peripherals/displays/hd44780.hpp"
#include "fd/peripherals/sensors/mpu6050.hpp"

#ifdef FONDANT_HW_I2C

#include <fd/i2c.hpp>

extern I2C_HandleTypeDef hi2c1;
namespace examples::i2c_mpu6050_hd44780 {

    void setup() {
    }


    void run() {
        // Maak het busobject voor de bus waar het scherm en de sensor op zitten
        auto bus = fd::stm32_hal::i2c(hi2c1, false, 1000);

        // Maak het schermobject aan
        auto screen = fd::peripherals::hd44780(bus, 4, 20, 0x27);

        // Maak het sensorobject voor de mpu6050 aan
        auto sensor = fd::peripherals::mpu6050(bus);


        char output[20];

        while (true) {
            // Haal de sensorwaarden op
            sensor.readData();
            double  temp   = sensor.getTemp();
            int     acc[3] = {sensor.getAccelX(), sensor.getAccelY(), sensor.getAccelZ()};
            int     gyr[3] = {sensor.getGyroX(), sensor.getGyroY(), sensor.getGyroZ()};
            uint8_t whoAmI = sensor.getWhoAmI();


            // Weergeef de opgehaalde waarden
            snprintf(output, 20, "ID: %d   ", whoAmI);
            screen.display_string(output, 1);
            snprintf(output, 20, "A: %04d-%04d-%04d   ", acc[0], acc[1], acc[2]);
            screen.display_string(output, 2);
            snprintf(output, 20, "G: %04d-%04d-%04d   ", gyr[0], gyr[1], gyr[2]);
            screen.display_string(output, 3);
            snprintf(output, 20, "Temp : %.2f   ", temp);
            screen.display_string(output, 4);
        }
    }

}
#endif