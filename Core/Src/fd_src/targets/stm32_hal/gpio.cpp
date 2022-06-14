#include <fd/fondant_targets.hpp>

#if FONDANT_TARGET == FONDANT_TARGET_STM32_HAL

#include <fd/targets/stm32_hal/gpio.hpp>

#include <stm32f1xx_hal.h>

namespace fd::stm32_hal {

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

    void pin_out::write(bool new_value) {
        HAL_GPIO_WritePin(port, pinNumber, new_value ? GPIO_PIN_SET : GPIO_PIN_RESET);
    }

    void pin_out::toggle() {
        HAL_GPIO_TogglePin(port, pinNumber);
    }

    void
    pin_out::setup(GPIO_TypeDef *port, uint16_t pin_number, pin_out_speed speed, pin_out_mode mode, pin_pull pull) {
        GPIO_InitTypeDef GPIO_InitStruct = {0};

        /* GPIO Ports Clock Enable */
        _enable_gpio_clock(port);

        /*Configure GPIO value Output Level */
        HAL_GPIO_WritePin(port, pin_number, GPIO_PIN_RESET);

        /*Configure GPIO value : PC13 */
        GPIO_InitStruct.Pin = pin_number;
        GPIO_InitStruct.Mode = static_cast<uint32_t>(mode);
        GPIO_InitStruct.Pull = static_cast<uint32_t>(pull);
        GPIO_InitStruct.Speed = static_cast<uint32_t>(speed);
        HAL_GPIO_Init(port, &GPIO_InitStruct);
    }


    bool pin_in::read() {
        return HAL_GPIO_ReadPin(port, pinNumber);
    }

    void pin_in::setup(GPIO_TypeDef *port, uint16_t pin_number, pin_pull pull) {
        GPIO_InitTypeDef GPIO_InitStruct = {0};

        _enable_gpio_clock(port);

        /*Configure GPIO value : PA1 */
        GPIO_InitStruct.Pin = pin_number;
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
        GPIO_InitStruct.Pull = static_cast<uint32_t>(pull);
        HAL_GPIO_Init(port, &GPIO_InitStruct);
    }
}

#endif
