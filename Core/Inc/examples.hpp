#ifndef FD_HDR_EXAMPLES
#define FD_HDR_EXAMPLES

#define examplenamespace(name) namespace name { \
    void setup();                               \
    void run();                                 \
}

namespace examples {

    examplenamespace(helloworld)
    examplenamespace(pininpinout)
    examplenamespace(pinsdoorgeven)
    examplenamespace(spi)
    examplenamespace(spi_dma)
    examplenamespace(i2c)
    examplenamespace(i2c_hd44780)
    examplenamespace(i2c_bme280_hd44780)
    examplenamespace(i2c_mpu6050_hd44780)
    examplenamespace(matrix_keypad)
}


#endif //FD_HDR_EXAMPLES
