#include <fd/fondant.hpp>
#include <fd/fondant_main.hpp>
#include <fd/gpio.hpp>

#include <examples.hpp>

int fd_main() {

    // Voorbeeld 1: Hello World (blink)
//    examples::helloworld::setup();
//    examples::helloworld::run();

    // Voorbeeld 2: Pin In Pin Out
//    examples::pininpinout::setup();
//    examples::pininpinout::run();

    // Voorbeeld 3: Pins doorgeven
//    examples::pinsdoorgeven::setup();
//    examples::pinsdoorgeven::run();

    // Voorbeeld 4: SPI
//    examples::spi::setup();
//    examples::spi::run();

    // Voorbeeld 5: SPI_DMA
//    examples::spi_dma::setup();
//    examples::spi_dma::run();

    // Voorbeeld 6: I2C
    examples::i2c::setup();
    examples::i2c::run();


    // Voorbeeld 7: I2C_HHD44780
//    examples::i2c_hd44780::setup();
//    examples::i2c_hd44780::run();

    // Voorbeeld 8: I2C_HHD44780_BMP280
//    examples::i2c_bme280_hd44780::setup();
//    examples::i2c_bme280_hd44780::run();

    // Voorbeeld 9: I2C_HHD44780_MPU6050
//    examples::i2c_mpu6050_hd44780::setup();
//    examples::i2c_mpu6050_hd44780::run();

    // Voorbeeld 10: Matrix Keypad
//    examples::matrix_keypad::setup();
//    examples::matrix_keypad::run();

    return 0;
}
