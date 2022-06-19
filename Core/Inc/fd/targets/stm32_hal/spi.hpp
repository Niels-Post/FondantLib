#ifndef FD_HDR_STM32_HAL_SPI
#define FD_HDR_STM32_HAL_SPI

#include <fd/targets/base/spi.hpp>
#include <fd/targets/base/gpio.hpp>
#include <stm32f1xx_hal.h>

#include <fd/fondant_targets.hpp>

namespace fd::stm32_hal {

    fd::spi_status get_spi_status(int status);
    enum class spi_error_status: uint32_t {
        NONE = HAL_SPI_ERROR_NONE,
        ERROR_MODF = HAL_SPI_ERROR_MODF,
        ERROR_CRC = HAL_SPI_ERROR_CRC,
        ERROR_OVR = HAL_SPI_ERROR_OVR,
        ERROR_DMA = HAL_SPI_ERROR_DMA,
        ERROR_FLAG = HAL_SPI_ERROR_FLAG,
        ERROR_ABORT = HAL_SPI_ERROR_ABORT
    };

    class spi : public ::fd::spi_base {
        fd::pin_out_base &cs_pin;
        SPI_HandleTypeDef *handle;
        bool dma;
        uint32_t default_timeout;

    public:
        spi_error_status last_error;
        spi(SPI_HandleTypeDef *handle, bool dma, uint32_t defaultTimeout, fd::pin_out_base &cs_pin);

        fd::spi_status transmit_receive(uint8_t *write_data, uint8_t *read_data, uint8_t size) override;

        spi_status wait() override;

    };

}
#endif //FD_HDR_STM32_HAL_SPI
