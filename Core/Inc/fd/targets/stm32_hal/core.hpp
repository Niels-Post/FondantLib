#ifndef FD_HDR_STM32_HAL_CORE
#define FD_HDR_STM32_HAL_CORE

namespace fd::stm32_hal {
    enum class status : uint32_t {
        HAL_OK = 0x00U,
        HAL_ERROR = 0x01U,
        HAL_BUSY = 0x02U,
        HAL_TIMEOUT = 0x03U
    };

    uint32_t get_current_ticks();

}

#endif //FD_HDR_STM32_HAL_CORE
