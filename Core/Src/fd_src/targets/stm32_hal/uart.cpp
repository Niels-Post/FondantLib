#include <fd/fondant_targets.hpp>

#if FONDANT_TARGET == FONDANT_TARGET_STM32_HAL
#ifdef FONDANT_HW_SPI

#include <fd/targets/stm32_hal/uart.hpp>


fd::uart_status fd::stm32_hal::get_uart_status(uint32_t status) {
    switch (status) {
        case HAL_OK:
            return fd::uart_status::OK;
        case HAL_BUSY:
            return fd::uart_status::BUSY;
        case HAL_ERROR:
        case HAL_TIMEOUT:
        default:
            return fd::uart_status::ERROR;
    }
}

fd::uart_status fd::stm32_hal::uart::transmit(uint8_t *data, size_t size) {
    uint32_t resultStatus;
    if (dma) {
        resultStatus = HAL_UART_Transmit(&handle, data, size, default_timeout);
    } else {
        resultStatus = HAL_UART_Transmit_DMA(&handle, data, size);
    }
    last_error = (uart_error_status) handle.ErrorCode;
    return get_uart_status(resultStatus);
}

fd::uart_status fd::stm32_hal::uart::receive(uint8_t *inData, size_t size, size_t max_wait_ms) {
    uint32_t resultStatus;
    if(dma) {
        resultStatus = HAL_UART_Receive_DMA(&handle, inData, size);
        if(resultStatus == HAL_OK) {
            return uart_status::STARTED;
        }
    } else {
        resultStatus = HAL_UART_Receive(&handle, inData, size, max_wait_ms);
    }
    last_error = (uart_error_status) handle.ErrorCode;
    return get_uart_status(resultStatus);
}

fd::stm32_hal::uart::uart(UART_HandleTypeDef &handle, bool dma, uint32_t defaultTimeout) : handle(handle), dma(dma),
                                                                                           default_timeout(defaultTimeout) {}


#endif

#endif


