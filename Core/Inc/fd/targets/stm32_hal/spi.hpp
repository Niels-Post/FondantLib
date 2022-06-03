//
// Created by Niels Post on 03/06/2022.
//

#ifndef FONDANTLIB_SPI_HPP
#define FONDANTLIB_SPI_HPP

#include <fd/targets/base/spi.hpp>
#include <stm32f1xx_hal.h>

namespace fd::stm32_hal {

    fd::spi_status get_spi_status(int status);

    class spi : public ::fd::spi {
        SPI_HandleTypeDef *handle;
        bool dma;
        uint32_t default_timeout;

    public:
        spi(SPI_HandleTypeDef *handle, bool dma, uint32_t defaultTimeout);

        fd::spi_status transmit(uint8_t *write_data, uint8_t size) override;

        fd::spi_status transmit_receive(uint8_t *write_data, uint8_t *read_data, uint8_t size) override;

        fd::spi_status receive(uint8_t *read_data, uint8_t size) override;


    };

}
#endif //FONDANTLIB_SPI_HPP
