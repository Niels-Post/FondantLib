#include <fd/fondant_targets.hpp>

#ifdef FONDANT_HW_I2C

#include <fd/targets/stm32_hal/interrupt.hpp>
#include <stm32f1xx_it.h>
#include <fd/functional.hpp>


namespace fd::stm32_hal {
    _interrupt_handler_type<> interrupt_handler{};
}

using namespace fd::stm32_hal;

extern "C" void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart) {
    fd::stm32_hal::interrupt_handler.call(interrupts::UART_TxComplete, interrupt_data{huart});
}

extern "C" void HAL_UART_TxHalfCpltCallback(UART_HandleTypeDef *huart) {
    fd::stm32_hal::interrupt_handler.call(interrupts::UART_TxHalfComplete, interrupt_data{huart});
}

extern "C" void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
    fd::stm32_hal::interrupt_handler.call(interrupts::UART_RxComplete, interrupt_data{huart});
}

extern "C" void HAL_UART_RxHalfCpltCallback(UART_HandleTypeDef *huart) {
    fd::stm32_hal::interrupt_handler.call(interrupts::UART_RxHalfComplete, interrupt_data{huart});
}

extern "C" void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart){
    fd::stm32_hal::interrupt_handler.call(interrupts::UART_Error, interrupt_data{huart});
}

extern "C" void HAL_UART_AbortCpltCallback(UART_HandleTypeDef *huart) {
    fd::stm32_hal::interrupt_handler.call(interrupts::UART_AbortComplete, interrupt_data{huart});
}

extern "C" void HAL_UART_AbortTransmitCpltCallback(UART_HandleTypeDef *huart){
    fd::stm32_hal::interrupt_handler.call(interrupts::UART_AbortTransmitComplete, interrupt_data{huart});
}

extern "C" void HAL_UART_AbortReceiveCpltCallback(UART_HandleTypeDef *huart){
    fd::stm32_hal::interrupt_handler.call(interrupts::UART_AbortReceiveComplete, interrupt_data{huart});
}

extern "C" void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size){
    fd::stm32_hal::interrupt_handler.call(interrupts::UART_RxEvent, interrupt_data{huart, Size});
}

extern "C" void HAL_GPIO_EXTI_Callback(uint16_t gpioPin) {
    fd::stm32_hal::interrupt_handler.call(interrupts::ExternalInterrupt, interrupt_data{nullptr, gpioPin});
}


#endif