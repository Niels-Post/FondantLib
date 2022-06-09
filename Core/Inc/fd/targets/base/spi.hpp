#ifndef FD_BASE_SPI_HPP
#define FD_BASE_SPI_HPP

#include "fd/fondant.hpp"
#include "stm32f1xx_hal_spi.h"

namespace fd {

    enum class spi_status : uint8_t {
        OK = 0x01U,
        ERROR = 0x02U,
        BUSY = 0x04U,
        TIMEOUT = 0x08U
    };


    class spi_base {
    public:
        virtual fd::spi_status transmit(uint8_t *write_data, uint8_t size) {
            return fd::spi_status::ERROR;
        };

        virtual fd::spi_status transmit_receive(uint8_t *write_data, uint8_t *read_data, uint8_t size) {
            return fd::spi_status::ERROR;
        };

        virtual fd::spi_status receive(uint8_t *read_data, uint8_t size) {
            return fd::spi_status::ERROR;
        };
    };
}

#endif