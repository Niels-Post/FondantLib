#ifndef FONDANT_GPIO_HPP
#define FONDANT_GPIO_HPP

#include <fd/fondant_targets.hpp>




#if FONDANT_TARGET == FONDANT_TARGET_STM32_HAL
#include "./targets/stm32_hal/gpio.hpp"
#else
#error "Geen GPIO implementatie gevonden voor target"
#endif


#endif //FONDANT_GPIO_HPP
