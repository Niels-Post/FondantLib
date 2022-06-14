#ifndef FD_HDR_STM32_HAL_GPIO
#define FD_HDR_STM32_HAL_GPIO

#include "fd/targets/base/gpio.hpp"
#include "stm32f1xx_hal.h"

namespace fd::stm32_hal {
    /**
   * Enum om de speed van en output (push/pull) value te bepalen
   *
   * Door de speed hoger te zetten, kan de value sneller wisselen van hoog naar laag en andersom, maar
   * dit zorgt ervoor dat de microcontroller meer stroom gebruikt, en zorgt voor meer interferentie in
   * je elektrische schema.
   */
    enum class pin_out_speed : uint32_t {
        HIGH = GPIO_SPEED_FREQ_HIGH,
        MEDIUM = GPIO_SPEED_FREQ_MEDIUM,
        LOW = GPIO_SPEED_LOW
    };

    enum class pin_out_mode : uint32_t {
        OPEN_DRAIN = GPIO_MODE_OUTPUT_OD,
        PUSH_PULL = GPIO_MODE_OUTPUT_PP
    };

    enum class pin_pull : uint32_t {
        UP = GPIO_PULLUP,
        DOWN = GPIO_PULLDOWN,
        NONE = GPIO_NOPULL
    };

    /**
     * Schakel de benodigde GPIO-klokken in voor een specifieke GPIO poort
     * @param port Poort om klokken voor in te schakelen.
     */
    void _enable_gpio_clock(GPIO_TypeDef *port);


    class pin_out : public ::fd::pin_out_base {
        GPIO_TypeDef *port;
        uint16_t pinNumber;

    public:
        pin_out(GPIO_TypeDef *port, uint16_t pinNumber) :

                port(port), pinNumber(pinNumber) {}

        void write(bool new_value) override;;

        void toggle() override;;

        /**
         * Stel een value in als een output value.
         * @param port De poort van de value (bv: GPIOC)
         * @param pin_number Het nummer van de value (bv: GPIO_PIN_13)
         * @param speed De snelheid waarop de value ingesteld moet worden (bv: fd_src::pin_out_speed::MEDIUM)
         * @param mode De modus waarop de value ingesteld moet worden (push/pull of open drain)
         * @param pull De in te schakelen pull-resistor (UP, DOWN of NONE)
         */
        [[deprecated("Vermijd de setup-functies. Stel de chip altijd in via de STM32IDE")]]
        static void setup(GPIO_TypeDef *port, uint16_t pin_number, pin_out_speed speed = pin_out_speed::LOW,
                          pin_out_mode mode = pin_out_mode::PUSH_PULL, pin_pull pull = pin_pull::NONE);


    };

    class pin_in : public ::fd::pin_in_base {
        GPIO_TypeDef *port;
        uint16_t pinNumber;

    public:
        pin_in(GPIO_TypeDef *port, uint16_t pinNumber) :
                port(port), pinNumber(pinNumber) {}

        bool read() override;

        [[deprecated("Vermijd de setup-functies. Stel de chip altijd in via de STM32IDE")]]
        static void setup(GPIO_TypeDef *port, uint16_t pin_number, pin_pull pull = pin_pull::NONE);
    };
}


#endif //FD_HDR_STM32_HAL_GPIO