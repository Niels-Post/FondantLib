
#include <fd/fondant_targets.hpp>

#if FONDANT_TARGET == FONDANT_TARGET_STM32_HAL
#ifdef FONDANT_HW_SPI

#include <fd/targets/stm32_hal/spi.hpp>


fd::spi_status fd::stm32_hal::get_spi_status(int status) {
    switch (status) {
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

fd::stm32_hal::spi::spi(SPI_HandleTypeDef *handle, bool dma, uint32_t defaultTimeout, fd::pin_out_base &cs_pin)
        : handle(handle), dma(dma),
          default_timeout(defaultTimeout), cs_pin(cs_pin) {}




fd::spi_status fd::stm32_hal::spi::transmit_receive(uint8_t *write_data, uint8_t *read_data, uint8_t size) {
    HAL_StatusTypeDef result;
    cs_pin.write(GPIO_PIN_RESET);
    if (dma) {
        result = HAL_SPI_TransmitReceive_DMA(handle, write_data, read_data, size);
        if(result == HAL_OK) {
            return fd::spi_status::STARTED;
        }
        cs_pin.write(GPIO_PIN_SET);

    } else {
        result = HAL_SPI_TransmitReceive(handle, write_data, read_data, size, default_timeout);
        cs_pin.write(GPIO_PIN_SET);
    }
    last_error = (spi_error_status) handle->ErrorCode;
    return get_spi_status(result);
}



fd::spi_status fd::stm32_hal::spi::wait() {
    while(handle->State == HAL_SPI_STATE_BUSY ||
            handle->State == HAL_SPI_STATE_BUSY_RX ||
            handle->State == HAL_SPI_STATE_BUSY_TX ||
            handle->State == HAL_SPI_STATE_BUSY_TX_RX) {}
    cs_pin.write(GPIO_PIN_SET);
    last_error = (spi_error_status) handle->ErrorCode;
    return handle->ErrorCode > 0 ? fd::spi_status::ERROR : fd::spi_status::OK;
}


#endif
#endif


