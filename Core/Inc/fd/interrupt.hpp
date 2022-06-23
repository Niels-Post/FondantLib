#ifndef FD_HDR_INTERRUPT
#define FD_HDR_INTERRUPT

#include <fd/fondant_targets.hpp>




#if FONDANT_TARGET == FONDANT_TARGET_STM32_HAL
#include "./targets/stm32_hal/interrupt.hpp"
#else
#error "Geen interrupt implementatie gevonden voor target"
#endif


#endif //FD_HDR_INTERRUPT
