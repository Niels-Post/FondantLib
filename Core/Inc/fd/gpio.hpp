#ifndef FD_HDR_GPIO
#define FD_HDR_GPIO

#include <fd/fondant_targets.hpp>




#if FONDANT_TARGET == FONDANT_TARGET_STM32_HAL
#include "./targets/stm32_hal/gpio.hpp"
#else
#error "Geen GPIO implementatie gevonden voor target"
#endif


#endif //FD_HDR_GPIO
