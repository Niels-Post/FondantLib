#ifndef FD_SPI_HPP
#define FD_SPI_HPP

#include <fd/fondant_targets.hpp>


#if FONDANT_TARGET == FONDANT_TARGET_STM32_HAL

#ifndef FONDANT_HW_SPI
#error "SPI is niet ingesteld STM32IDE. Stel tenminste 1 SPI-bus in"
#endif

#include "./targets/stm32_hal/spi.hpp"

#else
#error "Geen SPI implementatie gevonden voor target"
#endif


#endif //FD_SPI_HPP
