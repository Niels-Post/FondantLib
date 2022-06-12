#include <fd/peripherals/displays/hd44780.hpp>
#include <fd/fondant.hpp>

fd::peripherals::hd44780::hd44780(fd::i2c_base &i2CBus, uint8_t rows, uint8_t cols, uint16_t address) : i2c_bus(i2CBus),
                                                                                                        rows(rows),
                                                                                                        cols(cols),
                                                                                                        address(address) {
    write(0x03);
    write(0x03);
    write(0x03);
    write(0x02);

    write(LCD_FUNCTIONSET | LCD_2LINE | LCD_5x8DOTS | LCD_4BITMODE);
    write(LCD_DISPLAYCONTROL | LCD_DISPLAYON);
    write(LCD_CLEARDISPLAY);
    write(LCD_ENTRYMODESET | LCD_ENTRYLEFT);
}

void fd::peripherals::hd44780::strobe(uint8_t data) {
    i2c_write(data | En | LCD_BACKLIGHT);
    i2c_write(((data & ~En) | LCD_BACKLIGHT));
}

void fd::peripherals::hd44780::write_four_bits(uint8_t data) {
    i2c_write(data | LCD_BACKLIGHT);
    strobe(data);
}

void fd::peripherals::hd44780::write(uint8_t cmd, uint8_t mode) {
    write_four_bits(mode | (cmd & ((uint8_t) 0xF0)));
    write_four_bits(mode | ((cmd << 4) & ((uint8_t) 0xF0)));
}

void fd::peripherals::hd44780::display_string(const char *str, uint8_t line) {
    if (line == 1)
        write(0x80);
    if (line == 2)
        write(0xC0);
    if (line == 3)
        write(0x94);
    if (line == 4)
        write(0xD4);

    do {

        write((uint8_t) *str, Rs);
        str++;
    } while (*str != 0);
}

void fd::peripherals::hd44780::clear() {
    write(LCD_CLEARDISPLAY);
    write(LCD_RETURNHOME);
}

void fd::peripherals::hd44780::i2c_write(uint8_t data) {
    i2c_bus.write(address, &data, 1);
    i2c_bus.wait();
}
