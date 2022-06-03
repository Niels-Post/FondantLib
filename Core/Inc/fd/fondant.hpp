#ifndef FONDANT_HPP
#define FONDANT_HPP

#include <fd/fondant_targets.hpp>

#include <fd/targets/base/core.hpp>

#include "stm32f1xx_hal.h"



#if FONDANT_TARGET==stm32
#include "./targets/stm32_hal/core.hpp"
#endif


#endif
