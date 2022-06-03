#ifndef FONDANTLIB_FONDANT_TARGETS_HPP
#define FONDANTLIB_FONDANT_TARGETS_HPP


#ifdef USE_HAL_DRIVER
#define FONDANT_TARGET stm32_hal
#endif


#ifndef FONDANT_TARGET
#error "Kan target board niet vinden"
#endif

#endif //FONDANTLIB_FONDANT_TARGETS_HPP
