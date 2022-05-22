#include "gpio.hpp"

#include <cstdint>
#include <stm32f1xx.h>

namespace fd {
	/**
	 * Wacht een aangegeven aantal milliseconden
	 * @param ms Aantal milliseconden
	 */
	void sleep(long ms) {
		HAL_Delay(ms);

	}

	void refresh_wwdg(WWDG_HandleTypeDef *watchdog) {
		HAL_WWDG_Refresh(watchdog);
	}

	void refresh_iwdg() {
	}

}