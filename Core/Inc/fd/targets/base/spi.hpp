#ifndef FD_HDR_BASE_SPI
#define FD_HDR_BASE_SPI

#include "fd/fondant.hpp"
#include "stm32f1xx_hal_spi.h"

namespace fd {

	/**
	 * Resultaat van een SPI transactie.
	 */
    enum class spi_status : uint8_t {
    	/// Transactie succesvol afgerond
        OK = 0x01U,
        /// Er was een error tijdens de transactie
        ERROR = 0x02U,
        /// De SPI-bus was al bezig met iets anders
        BUSY = 0x04U,
		/// De transactie is gestart, gebruikt wait() om op het resultaat te wachten
        STARTED = 0x08U,
		/// De aangeroepen functie is niet geïmplementeerd. Let erop dat je spi_base altijd by reference of by pointer gebruikt.
		NOT_IMPLEMENTED = 0x10u
    };


    class spi_base {
    public:
		/**
		 * Verstuur en ontvang een aantal bytes
		 * @param write_data Pointer naar de data om te schrijven
		 * @param read_data Pointer naar een data-array om data naartoe te lezen
		 * @param size Aantal bytes aan data om te communiceren
		 * @return De resultaatstatus van de transactie
		 */
        virtual fd::spi_status transmit_receive(uint8_t *write_data, uint8_t *read_data, uint8_t size) {
            return fd::spi_status::NOT_IMPLEMENTED;
        };

		/**
		 * Wacht tot de laatste SPI-transactie afgerond is
		 * @return De resultaatstatus van de laatste SPI transactie
		 */
        virtual fd::spi_status wait() {
            return fd::spi_status::NOT_IMPLEMENTED;
        }

		/**
		 * Verstuur een aantal bytes
		 * @param write_data Pointer naar data array om vanuit te schrijven
		 * @param size Lengte van de data
		 * @return De resultaatstatus van de transactie
		 */
        virtual fd::spi_status transmit(uint8_t *write_data, uint8_t size) {
            return transmit_receive(write_data, nullptr, size);
        };

		/**
		 * Ontvang een aantal bytes
		 * @param write_data Pointer naar data array om naartoe te lezen
		 * @param size Lengte van de data
		 * @return De resultaatstatus van de transactie
		 */
        virtual fd::spi_status receive(uint8_t *read_data, uint8_t size) {
            return transmit_receive(nullptr, read_data, size);
        };

		/**
		 * Verstuur en ontvang een aantal bytes en wacht direct op het resultaat
		 * Zie transmit_receive voor de parameters
		 */
        virtual fd::spi_status transmit_receive_wait(uint8_t *write_data, uint8_t *read_data, uint8_t size) {
            spi_status status = transmit_receive(write_data, read_data, size);
            if(status != fd::spi_status::STARTED) {
                return status;
            }

            return wait();
        }

		/**
		 * Verstuur een aantal bytes en wacht direct op het resultaat
		 * Zie transmit voor de parameters
		 */
        virtual fd::spi_status transmit_wait(uint8_t *write_data, uint8_t size) {
            spi_status status = transmit(write_data, size);
            if(status != fd::spi_status::STARTED) {
                return status;
            }

            return wait();
        }

		/**
		 * Ontvang een aantal bytes en wacht direct op het resultaat
		 * Zie receive voor de parameters
		 */
        virtual fd::spi_status receive_wait(uint8_t *read_data, uint8_t size) {
            spi_status status = receive(read_data, size);
            if(status != fd::spi_status::STARTED) {
                return status;
            }

            return wait();
        }


    };
}

#endif //FD_HDR_BASE_SPI