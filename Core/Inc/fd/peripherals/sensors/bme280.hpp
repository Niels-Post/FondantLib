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
    public:
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

    protected:
        void calculateTemperature();

        void calculatePressure();

        void calculateHumidity();


        void storeTrimParameters();


    public:
        bme280(fd::i2c_base &i2cBus, const uint16_t &address);

        /**
         * Alle beschikbare dataregisters van de BME280
         */


        /**
         * Bitwaarden voor de mogelijke oversamplingwaarden voor Gyro en Accel
         */
        enum class Oversampling : uint8_t {
            SKIPPED = 0,
            X1      = 0x01,
            X2      = 0x02,
            X4      = 0x03,
            X8      = 0x04,
            X16     = 0x05
        };

        /**
         * Mogelijke modi waarin de sensor ingesteld kan worden.
         * De standaardmodus is Forced
         */
        enum class Mode : uint8_t {
            SLEEP  = 0,
            FORCED = 1,
            NORMAL = 3
        };

        /**
         * De standbytijd die de sensor wacht voordat er weer een meting wordt gedaan.
         * Hogere standby-tijden zullen het energieverbruik van de sensor verlagen
         */
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

        /**
         * Mogelijke filterinstellingen voor meetwaarden
         */
        enum class Filter {
            OFF  = 0,
            F_2  = 1,
            F_4  = 2,
            F_8  = 3,
            F_16 = 4
        };

        /**
         * Pas de instellingen van de onderdelen van de sensor aan.
         * @param mode De instelmodus van de sensor
         * @param humidityOversamplingRate Hoe vaak er gemeten moet worden voor 1 meetwaarde voor de humidity sensor
         * @param pressureOversamplingRate Hoe vaak er gemeten moet worden voor 1 meetwaarde voor de pressure sensor
         * @param temperatureOversamplingRate Hoe vaak er gemeten moet worden voor 1 meetwaarde voor de temperature sensor
         * @param standbyTime Hoe lang de sensor moet wachten na een meting om een nieuwe meting te beginnen
         * @param filter Wat voor filterwaarde er toegepast moet worden op meetwaarden.
         */
        void setSettings(Mode mode = Mode::FORCED,
                         Oversampling humidityOversamplingRate = Oversampling::X1,
                         Oversampling pressureOversamplingRate = Oversampling::X1,
                         Oversampling temperatureOversamplingRate = Oversampling::X1,
                         StandbyTime standbyTime = StandbyTime::MS_10,
                         Filter filter = Filter::OFF);

        /**
         * Haal de meest recente meetwaarden op van de sensor, en sla deze op in het bme280-object.
         * Hierna kunnen de getTemperature, getPressure en getHumidity functies gebruikt worden om waarden te lezen
         */
        void readData();

        /**
         * Doet de nodige  berekeningen met de opgehaalde data (van readData) om een temperatuurmeting uit te lezen, en
         * geeft de meetwaarde hiervan terug
         * @return De gemeten temperatuur in graden Celcius
         */
        float getTemperature();

        /**
         * Doet de nodige  berekeningen met de opgehaalde data (van readData) om een barometrische druk uit te lezen, en
         * geeft de meetwaarde hiervan terug
         * @return De gemeten barometrische druk
         */
        float getPressure();

        /**
         * Doet de nodige  berekeningen met de opgehaalde data (van readData) om een luchtvochtigheid uit te lezen, en
         * geeft de meetwaarde hiervan terug
         * @return De gemeten luchtvochtigheid
         */
        float getHumidity();

        /**
         * Reset de sensor naar de standaardinstellingen
         * Het is aan te raden om na een reset de init-functie opnieuw aan te roepen.
         */
        void softReset();

        /**
         * Lees de waarde van een register van de BME280
         * @param reg Het register om te lezen
         * @param data data-array om de data naartoe te schrijven
         * @param size Lengte van de data
         */
        void readRegister(Register reg, uint8_t *data, uint8_t size);

        /**
         * Lees de waarde van een 1-byte-register van de BME280
         * @param reg Het register om te lezen
         * @return De waarde van het register
         */
        uint8_t readRegister(Register Register);

        /**
         * Verander de waarde van een register van de BME280
         * @param reg Register om aan te passen
         * @param data Data om in het register te zetten
         * @param size Lengte van de data
         */
        void writeRegister(Register reg, uint8_t *data, uint8_t size);

        /**
         * Verander de waarde van een 1-byte register van de BME280
         * @param reg Register om aan te passen
         * @param data Data om in het register te zetten
         */
        void writeRegister(Register reg, uint8_t data);

        /**
         * Initialiseer de BME280
         */
        void init();
    };
}
#endif //FD_HDR_PERIPHERAL_BME280
