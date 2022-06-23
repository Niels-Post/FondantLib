#include <fd/fondant_targets.hpp>

#ifdef FONDANT_HW_I2C

#include <fd/targets/stm32_hal/interrupt.hpp>
#include <fd/functional.hpp>


namespace fd::stm32_hal {
    _interrupt_handler_type<> interrupt_handler{};
}

using namespace fd::stm32_hal;

/*
 * Callback Implementaties voor UART interrupts
 */

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

/*
 * Callback Implementaties voor EXTI interrupts
 */

extern "C" void HAL_GPIO_EXTI_Callback(uint16_t gpioPin) {
    fd::stm32_hal::interrupt_handler.call(interrupts::ExternalInterrupt, interrupt_data{nullptr, gpioPin});
}

/*
 * Callback Implementaties voor SPI interrupts
 */
extern "C" void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi){
    fd::stm32_hal::interrupt_handler.call(fd::stm32_hal::interrupts::SPI_TxComplete, interrupt_data{hspi});
}
extern "C" void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi){
    fd::stm32_hal::interrupt_handler.call(fd::stm32_hal::interrupts::SPI_RxComplete, interrupt_data{hspi});
}
extern "C" void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi){
    fd::stm32_hal::interrupt_handler.call(fd::stm32_hal::interrupts::SPI_TxRxComplete, interrupt_data{hspi});
}
extern "C" void HAL_SPI_TxHalfCpltCallback(SPI_HandleTypeDef *hspi){
    fd::stm32_hal::interrupt_handler.call(fd::stm32_hal::interrupts::SPI_TxHalfComplete, interrupt_data{hspi});
}
extern "C" void HAL_SPI_RxHalfCpltCallback(SPI_HandleTypeDef *hspi){
    fd::stm32_hal::interrupt_handler.call(fd::stm32_hal::interrupts::SPI_RxHalfComplete, interrupt_data{hspi});
}
extern "C" void HAL_SPI_TxRxHalfCpltCallback(SPI_HandleTypeDef *hspi){
    fd::stm32_hal::interrupt_handler.call(fd::stm32_hal::interrupts::SPI_TxRxHalfComplete, interrupt_data{hspi});
}
extern "C" void HAL_SPI_ErrorCallback(SPI_HandleTypeDef *hspi){
    fd::stm32_hal::interrupt_handler.call(fd::stm32_hal::interrupts::SPI_Error, interrupt_data{hspi});
}
extern "C" void HAL_SPI_AbortCpltCallback(SPI_HandleTypeDef *hspi){
    fd::stm32_hal::interrupt_handler.call(fd::stm32_hal::interrupts::SPI_AbortComplete, interrupt_data{hspi});
}

/*
 * Callback implementaties voor I2C interrupts
 */
extern "C" void HAL_I2C_MasterTxCpltCallback(I2C_HandleTypeDef *hi2c){
    fd::stm32_hal::interrupt_handler.call(fd::stm32_hal::interrupts::I2C_MasterTxComplete, interrupt_data{hi2c});
}
extern "C" void HAL_I2C_MasterRxCpltCallback(I2C_HandleTypeDef *hi2c){
    fd::stm32_hal::interrupt_handler.call(fd::stm32_hal::interrupts::I2C_MasterRxComplete, interrupt_data{hi2c});
}
extern "C" void HAL_I2C_SlaveTxCpltCallback(I2C_HandleTypeDef *hi2c){
    fd::stm32_hal::interrupt_handler.call(fd::stm32_hal::interrupts::I2C_SlaveTxComplete, interrupt_data{hi2c});
}
extern "C" void HAL_I2C_SlaveRxCpltCallback(I2C_HandleTypeDef *hi2c){
    fd::stm32_hal::interrupt_handler.call(fd::stm32_hal::interrupts::I2C_SlaveRxComplete, interrupt_data{hi2c});
}
extern "C" void HAL_I2C_AddrCallback(I2C_HandleTypeDef *hi2c, uint8_t TransferDirection, uint16_t AddrMatchCode){
    fd::stm32_hal::interrupt_handler.call(fd::stm32_hal::interrupts::I2C_Addr, interrupt_data{hi2c, TransferDirection, AddrMatchCode});
}
extern "C" void HAL_I2C_ListenCpltCallback(I2C_HandleTypeDef *hi2c){
    fd::stm32_hal::interrupt_handler.call(fd::stm32_hal::interrupts::I2C_ListenComplete, interrupt_data{hi2c});
}
extern "C" void HAL_I2C_MemTxCpltCallback(I2C_HandleTypeDef *hi2c){
    fd::stm32_hal::interrupt_handler.call(fd::stm32_hal::interrupts::I2C_MemTxComplete, interrupt_data{hi2c});
}
extern "C" void HAL_I2C_MemRxCpltCallback(I2C_HandleTypeDef *hi2c){
    fd::stm32_hal::interrupt_handler.call(fd::stm32_hal::interrupts::I2C_MemRxComplete, interrupt_data{hi2c});
}
extern "C" void HAL_I2C_ErrorCallback(I2C_HandleTypeDef *hi2c){
    fd::stm32_hal::interrupt_handler.call(fd::stm32_hal::interrupts::I2C_Error, interrupt_data{hi2c});
}
extern "C" void HAL_I2C_AbortCpltCallback(I2C_HandleTypeDef *hi2c){
    fd::stm32_hal::interrupt_handler.call(fd::stm32_hal::interrupts::I2C_AbortComplete, interrupt_data{hi2c});
}


#endif