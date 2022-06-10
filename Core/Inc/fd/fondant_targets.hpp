#ifndef FD_HDR_FONDANT_TARGETS
#define FD_HDR_FONDANT_TARGETS

#define FONDANT_TARGET_STM32_HAL 10


#ifdef USE_HAL_DRIVER
#define FONDANT_TARGET FONDANT_TARGET_STM32_HAL
#include <stm32f1xx_hal.h>
#include <stm32f1xx_hal_conf.h>

#ifdef HAL_SPI_MODULE_ENABLED
#define FONDANT_HW_SPI
#endif

#ifdef HAL_I2C_MODULE_ENABLED
#define FONDANT_HW_I2C
#endif


#endif


#ifndef FONDANT_TARGET
#error "Kan target board niet vinden"
#endif

#endif //FD_HDR_FONDANT_TARGETS
