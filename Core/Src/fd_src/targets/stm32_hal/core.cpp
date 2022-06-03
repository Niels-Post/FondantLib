#include <fd/fondant_targets.hpp>


#if FONDANT_TARGET==stm32_hal

#include <fd/targets/base/core.hpp>
#include "stm32f1xx_hal.h"


void fd::sleep(long ms) {
    HAL_Delay(ms);
}

void fd::software_reset() {
    HAL_NVIC_SystemReset();

    while(true) {}
}

#endif
