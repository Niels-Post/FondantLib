#ifndef FD_HDR_FONDANT
#define FD_HDR_FONDANT

#include <fd/fondant_targets.hpp>

#include <fd/targets/base/core.hpp>




#if FONDANT_TARGET==FONDANT_TARGET_STM32_HAL
#include "./targets/stm32_hal/core.hpp"
#endif


#endif //FD_HDR_FONDANT


// TODO
// TODO MPU6050
// TODO OLED
// TODO HD44780