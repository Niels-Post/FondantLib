#ifndef FD_HDR_STM32_HAL_WATCHDOG
#define FD_HDR_STM32_HAL_WATCHDOG
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


#endif //FD_HDR_STM32_HAL_WATCHDOG
