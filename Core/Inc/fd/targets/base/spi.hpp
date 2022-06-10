#ifndef FD_HDR_BASE_SPI
#define FD_HDR_BASE_SPI

#include "fd/fondant.hpp"
#include "stm32f1xx_hal_spi.h"

namespace fd {

    enum class spi_status : uint8_t {
        OK = 0x01U,
        ERROR = 0x02U,
        BUSY = 0x04U,
        TIMEOUT = 0x08U,
        STARTED = 0x10U,
        NOT_IMPLEMENTED = 0x20u
    };


    class spi_base {
    public:
        virtual fd::spi_status transmit_receive(uint8_t *write_data, uint8_t *read_data, uint8_t size) {
            return fd::spi_status::NOT_IMPLEMENTED;
        };

        virtual fd::spi_status wait() {
            return fd::spi_status::NOT_IMPLEMENTED;
        }

        virtual fd::spi_status transmit(uint8_t *write_data, uint8_t size) {
            return transmit_receive(write_data, nullptr, size);
        };

        virtual fd::spi_status receive(uint8_t *read_data, uint8_t size) {
            return transmit_receive(nullptr, read_data, size);
        };
        
        virtual fd::spi_status transmit_receive_wait(uint8_t *write_data, uint8_t *read_data, uint8_t size) {
            spi_status status = transmit_receive(write_data, read_data, size);
            if(status != fd::spi_status::STARTED) {
                return status;
            }

            return wait();
        }

        virtual fd::spi_status transmit_wait(uint8_t *write_data, uint8_t size) {
            spi_status status = transmit(write_data, size);
            if(status != fd::spi_status::STARTED) {
                return status;
            }

            return wait();
        }

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