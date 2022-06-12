#ifndef FD_HDR_PERIPHERAL_BME280
#define FD_HDR_PERIPHERAL_BME280

#include "fd/targets/base/i2c.hpp"

namespace fd::peripherals {
    class bme280 {
    private:
        fd::i2c_base &i2c_bus;
        uint16_t     address;

        uint8_t trim_temp[6];
        uint8_t trim_pres[18];
        uint8_t trim_hum1[1];
        uint8_t trim_hum2[7];

        uint32_t raw_temp;
        uint32_t raw_pres;
        uint32_t raw_hum;

        float calculated_temp;
        float calculated_pres;
        float calculated_hum;

        int32_t t_fine;
    protected:
        void calculateTemperature();
        void calculatePressure();
        void calculateHumidity();

    public:
        bme280(fd::i2c_base &i2cBus, const uint16_t &address);

        enum class Register : uint8_t {
            CTRL_HUM  = 0xF2,
            CTRL_MEAS = 0xF4,
            CONFIG    = 0xF5,
            PRESS     = 0xF7,
            TEMP      = 0xFA,
            HUM       = 0xFD,
            TRIM_TEMP = 0x88,
            TRIM_PRES = 0x8E,
            TRIM_HUM1 = 0xA1,
            TRIM_HUM2 = 0xE1,
            ID        = 0xD0,
            RESET     = 0xE0
        };

        enum class Oversampling : uint8_t {
            SKIPPED = 0,
            X1      = 0x01,
            X2      = 0x02,
            X4      = 0x03,
            X8      = 0x04,
            X16     = 0x05
        };

        enum class Mode : uint8_t {
            SLEEP  = 0,
            FORCED = 1,
            NORMAL = 3
        };

        enum class StandbyTime {
            US_500   = 0,
            US_62500 = 1,
            MS_125   = 2,
            MS_250   = 3,
            MS_50    = 4,
            MS_1000  = 5,
            MS_10    = 6,
            MS_20    = 7
        };

        enum class Filter {
            OFF  = 0,
            F_2  = 1,
            F_4  = 2,
            F_8  = 3,
            F_16 = 4
        };

        void setSettings(Mode mode = Mode::FORCED,
                         Oversampling humidityOversamplingRate = Oversampling::X1,
                         Oversampling pressureOversamplingRate = Oversampling::X1,
                         Oversampling temperatureOversamplingRate = Oversampling::X1,
                         StandbyTime standbyTime = StandbyTime::MS_10,
                         Filter filter = Filter::OFF);

        void readData();

        float getTemperature();
        float getPressure();
        float getHumidity();

        void softReset();

        void storeTrimParameters();

        void writeRegister(Register reg, uint8_t *data, uint8_t size);
        void writeRegister(Register reg, uint8_t data);

        void readRegister(Register reg, uint8_t *data, uint8_t size);

        uint8_t readRegister(Register Register);

        void init();
    };
}
#endif //FD_HDR_PERIPHERAL_BME280
