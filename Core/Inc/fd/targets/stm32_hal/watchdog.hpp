#ifndef FONDANT_STM32_HAL_WATCHDOG_HPP
#define FONDANT_STM32_HAL_WATCHDOG_HPP
#include <stm32f1xx_hal_conf.h>

#ifdef HAL_WWDG_MODULE_ENABLED
class window_watchdog {
        WWDG_HandleTypeDef *watchdog;
    public:
        window_watchdog(WWDG_HandleTypeDef *watchdog): watchdog(watchdog) {

        }

        void refresh() {
            HAL_WWDG_Refresh(watchdog);
        }
    };
#endif


#endif //FONDANT_STM32_HAL_WATCHDOG_HPP
