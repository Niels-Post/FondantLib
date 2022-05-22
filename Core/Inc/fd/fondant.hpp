
#include "stm32f1xx_hal.h"

namespace fd {
	/**
	 * Wacht een aangegeven aantal milliseconden
	 * @param ms Aantal milliseconden
	 */
	void sleep(long ms) {
		HAL_Delay(ms);
	}

    enum class status : uint32_t {
        HAL_OK       = 0x00U,
        HAL_ERROR    = 0x01U,
        HAL_BUSY     = 0x02U,
        HAL_TIMEOUT  = 0x03U
    };

#ifdef WWDG_PRESCALER_1
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

}