
#include "stm32f1xx_hal.h"

namespace fd {

    class pin_out {
        GPIO_TypeDef *port;
        uint16_t pinNumber;
    public:
        pin_out(GPIO_TypeDef *port, uint16_t pinNumber) : port(port), pinNumber(pinNumber) {}

        virtual void write(bool new_value) {
            HAL_GPIO_WritePin(port, pinNumber, value ? GPIO_PIN_SET : GPIO_PIN_RESET);

        };

        virtual void toggle() {
            HAL_GPIO_TogglePin(port, pinNumber);
        };
    };

    class pin_in {
        GPIO_TypeDef *port;
        uint16_t pinNumber;

    public:
        pin_in(GPIO_TypeDef *port, uint16_t pinNumber) : port(port), pinNumber(pinNumber) {}

        bool read() {
            return HAL_GPIO_ReadPin(port, pinNumber);
        }
    };

    namespace setup {
        /**
     * Enum om de speed van en output (push/pull) pin te bepalen
     *
     * Door de speed hoger te zetten, kan de pin sneller wisselen van hoog naar laag en andersom, maar
     * dit zorgt ervoor dat de microcontroller meer stroom gebruikt, en zorgt voor meer interferentie in
     * je elektrische schema.
     */
        enum class pin_out_speed : uint32_t {
            HIGH = GPIO_SPEED_FREQ_HIGH,
            MEDIUM = GPIO_SPEED_FREQ_MEDIUM,
            LOW = GPIO_SPEED_LOW
        };

        enum class pin_out_mode : uint32_t {
            OPEN_DRAIN = GPIO_MODE_AF_OD,
            PUSH_PULL = GPIO_MODE_AF_PP
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
        void _enable_gpio_clock(GPIO_TypeDef *port) {
            __HAL_RCC_GPIOA_CLK_ENABLE();
            if (port == GPIOB) {
                __HAL_RCC_GPIOB_CLK_ENABLE();
            } else if (port == GPIOC) {
                __HAL_RCC_GPIOC_CLK_ENABLE();
            } else if (port == GPIOD) {
                __HAL_RCC_GPIOD_CLK_ENABLE();
            } else if (port == GPIOE) {
                __HAL_RCC_GPIOE_CLK_ENABLE();
            }
        }

        /**
         * Stel een pin in als een output pin.
         * @param port De poort van de pin (bv: GPIOC)
         * @param pin_number Het nummer van de pin (bv: GPIO_PIN_13)
         * @param speed De snelheid waarop de pin ingesteld moet worden (bv: fd::pin_out_speed::MEDIUM)
         * @param mode De modus waarop de pin ingesteld moet worden (push/pull of open drain)
         * @param pull De in te schakelen pull-resistor (UP, DOWN of NONE)
         */
        void pin_out(GPIO_TypeDef *port, uint16_t pin_number, pin_out_speed speed = pin_out_speed::LOW,
                     pin_out_mode mode = pin_out_mode::PUSH_PULL, pin_pull pull = pin_pull::NONE) {
            GPIO_InitTypeDef GPIO_InitStruct = {0};

            /* GPIO Ports Clock Enable */
            _enable_gpio_clock(port);

            /*Configure GPIO pin Output Level */
            HAL_GPIO_WritePin(port, pin_number, GPIO_PIN_RESET);

            /*Configure GPIO pin : PC13 */
            GPIO_InitStruct.Pin = pin_number;
            GPIO_InitStruct.Mode = static_cast<uint32_t>(mode);
            GPIO_InitStruct.Pull = static_cast<uint32_t>(pull);
            GPIO_InitStruct.Speed = static_cast<uint32_t>(speed);
        }


        void pin_in(GPIO_TypeDef *port, uint16_t pin_number, pin_pull pull = pin_pull::NONE) {
            GPIO_InitTypeDef GPIO_InitStruct = {0};

            _enable_gpio_clock(port);

            /*Configure GPIO pin : PA1 */
            GPIO_InitStruct.Pin = pin_number;
            GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
            GPIO_InitStruct.Pull = static_cast<uint32_t>(pull);
            HAL_GPIO_Init(port, &GPIO_InitStruct);
        }
    };
};