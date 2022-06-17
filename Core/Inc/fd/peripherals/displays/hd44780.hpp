#ifndef FD_HDR_PERIPHERAL_HD44780
#define FD_HDR_PERIPHERAL_HD44780
#include <fd/targets/base/i2c.hpp>
#include <cstdint>

const uint8_t LCD_CLEARDISPLAY = 0x01;
const uint8_t LCD_RETURNHOME = 0x02;
const uint8_t LCD_ENTRYMODESET = 0x04;
const uint8_t LCD_DISPLAYCONTROL = 0x08;
const uint8_t LCD_CURSORSHIFT = 0x10;
const uint8_t LCD_FUNCTIONSET = 0x20;
const uint8_t LCD_SETCGRAMADDR = 0x40;
const uint8_t LCD_SETDDRAMADDR = 0x80;

// flags for display entry mode
const uint8_t LCD_ENTRYRIGHT = 0x00;
const uint8_t LCD_ENTRYLEFT = 0x02;
const uint8_t LCD_ENTRYSHIFTINCREMENT = 0x01;
const uint8_t LCD_ENTRYSHIFTDECREMENT = 0x00;

// flags for display on/off control
const uint8_t LCD_DISPLAYON = 0x04;
const uint8_t LCD_DISPLAYOFF = 0x00;
const uint8_t LCD_CURSORON = 0x02;
const uint8_t LCD_CURSOROFF = 0x00;
const uint8_t LCD_BLINKON = 0x01;
const uint8_t LCD_BLINKOFF = 0x00;

// flags for display/cursor shift
const uint8_t LCD_DISPLAYMOVE = 0x08;
const uint8_t LCD_CURSORMOVE = 0x00;
const uint8_t LCD_MOVERIGHT = 0x04;
const uint8_t LCD_MOVELEFT = 0x00;

// flags for function set
const uint8_t LCD_8BITMODE = 0x10;
const uint8_t LCD_4BITMODE = 0x00;
const uint8_t LCD_2LINE = 0x08;
const uint8_t LCD_1LINE = 0x00;
const uint8_t LCD_5x10DOTS = 0x04;
const uint8_t LCD_5x8DOTS = 0x00;

// flags for backlight control
const uint8_t LCD_BACKLIGHT = 0x08;
const uint8_t LCD_NOBACKLIGHT = 0x00;

const uint8_t En = 0b00000100; // Enable bit
const uint8_t Rw = 0b00000010; // Read/Write bit
const uint8_t Rs = 0b00000001; // Register select bit

namespace fd::peripherals {
	/**
	 * Klasse voor een HD44780 character display.
	 *
	 * Het scherm wordt aangestuurd via een I2C IO extender "backpack"
	 */
    class hd44780 {
    private:
        fd::i2c_base &i2c_bus;
        uint8_t rows;
        uint8_t cols;
        uint16_t address;

		void strobe(uint8_t data);

		void write_four_bits(uint8_t data);

		void write(uint8_t cmd, uint8_t mode = 0);

		void i2c_write(uint8_t data);


	public:
		/**
		 * Maak een niewe HD44780 interface aan. Hiervoor heb je de I2C "backpack" nodig
		 * @param i2CBus Bus waarop het scherm is aangesloten
		 * @param rows Aantal rijen wat het scherm heeft
		 * @param cols Aantal kolommen (karakters) wat het scherm heeft
		 * @param address I2C Adres van het scherm (zie datasheet van de backpack voor meer informatie)
		 */
        hd44780(i2c_base &i2CBus, uint8_t rows, uint8_t cols, uint16_t address);

		/**
		 * Weergeef een string op het karakterdisplay.
		 * @param str String om te weergeven (null-terminated)
		 * @param line Regel om de string op te weergeven (begint op 1)
		 */
        void display_string(const char* str, uint8_t line);

		/**
		 * Maak het scherm leeg
		 */
        void clear();

    };
}

#endif //FD_HDR_PERIPHERAL_HD44780
