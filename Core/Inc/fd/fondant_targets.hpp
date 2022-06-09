#ifndef FONDANTLIB_FONDANT_TARGETS_HPP
#define FONDANTLIB_FONDANT_TARGETS_HPP


#ifdef USE_HAL_DRIVER
#define FONDANT_TARGET stm32_hal
#include <stm32f1xx_hal_conf.h>

#ifdef HAL_SPI_MODULE_ENABLED
#define FONDANT_HW_SPI
#endif

#endif


#ifndef FONDANT_TARGET
#error "Kan target board niet vinden"
#endif

#endif //FONDANTLIB_FONDANT_TARGETS_HPP
