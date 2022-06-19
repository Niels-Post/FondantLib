#include <fd/fondant_targets.hpp>


#if FONDANT_TARGET==FONDANT_TARGET_STM32_HAL

#include <fd/targets/base/core.hpp>
#include "stm32f1xx_hal.h"
#include "fd/targets/stm32_hal/core.hpp"


void fd::sleep(long ms) {
    HAL_Delay(ms);
}

void fd::software_reset() {
    HAL_NVIC_SystemReset();

    while(true) {}
}

__attribute__((optimize("O0")))
void fd::none() {

}

#endif

