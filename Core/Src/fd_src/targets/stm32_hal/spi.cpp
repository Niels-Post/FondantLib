
#include <fd/fondant_targets.hpp>

#if FONDANT_TARGET==stm32
#include <fd/targets/stm32_hal/spi.hpp>


fd::spi_status fd::stm32_hal::get_spi_status(int status) {
    switch(status) {
        case HAL_OK:
            return fd::spi_status::OK;
        case HAL_BUSY:
            return fd::spi_status::BUSY;
        case HAL_ERROR:
            return fd::spi_status::ERROR;
        case HAL_TIMEOUT:
            return fd::spi_status::TIMEOUT;
        default:
            return fd::spi_status::ERROR;
    }
}

fd::stm32_hal::spi::spi(SPI_HandleTypeDef *handle, bool dma, uint32_t defaultTimeout) : handle(handle), dma(dma),
                                                                                        default_timeout(defaultTimeout) {}

fd::spi_status fd::stm32_hal::spi::transmit(uint8_t *write_data, uint8_t size) {
    HAL_StatusTypeDef result;
    if (dma) {
        result = HAL_SPI_Transmit_DMA(handle, write_data, size);
    } else {
        result = HAL_SPI_Transmit(handle, write_data, size, default_timeout);
    }

    return get_spi_status(result);
}

fd::spi_status fd::stm32_hal::spi::transmit_receive(uint8_t *write_data, uint8_t *read_data, uint8_t size) {
    HAL_StatusTypeDef result;
    if (dma) {
        result = HAL_SPI_TransmitReceive_DMA(handle, write_data, read_data, size);
    } else {
        result = HAL_SPI_TransmitReceive(handle, write_data, read_data, size, default_timeout);
    }
    return get_spi_status(result);
}

fd::spi_status fd::stm32_hal::spi::receive(uint8_t *read_data, uint8_t size) {
    HAL_StatusTypeDef result;
    if (dma) {
        result = HAL_SPI_Receive_DMA(handle, read_data, size);
    } else {
        result = HAL_SPI_Receive(handle, read_data, size, default_timeout);
    }
    HAL_SPI_GetState(handle);
    return get_spi_status(result);
}



#endif


