#ifndef FD_HDR_STM32_HAL_UART
#define FD_HDR_STM32_HAL_UART

#include <fd/targets/base/uart.hpp>

namespace fd::stm32_hal {
    fd::uart_status get_uart_status(uint32_t status);
    enum class uart_error_status: uint32_t {
        NONE          = HAL_UART_ERROR_NONE,
        ERROR_PARITY  = HAL_UART_ERROR_PE,
        ERROR_NOISE   = HAL_UART_ERROR_NE,
        ERROR_FRAME   = HAL_UART_ERROR_FE,
        ERROR_OVERRUN = HAL_UART_ERROR_ORE,
        ERROR_DMA     = HAL_UART_ERROR_DMA
    };


    class uart: public fd::uart_base {
        UART_HandleTypeDef &handle;
        bool dma;
        uint32_t           default_timeout;
        uart_error_status last_error = uart_error_status::NONE;


    public:
        uart(UART_HandleTypeDef &handle, bool dma, uint32_t defaultTimeout = 1000);

        uart_status transmit(uint8_t *data, size_t size) override;

        /**
         * Receiving is still a work in progress, TODO: add a way to check when a receive ends
         */
        uart_status receive(uint8_t *inData, size_t size, size_t max_wait_ms) override;

    };
}

#endif //FD_HDR_STM32_HAL_UART
