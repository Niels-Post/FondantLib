#ifndef FD_HDR_STM32_HAL_INTERRUPT
#define FD_HDR_STM32_HAL_INTERRUPT


#include <utility>
#include <variant>
#include "fd/functional.hpp"

namespace fd::stm32_hal {
    struct interrupt_data {
        void *peripheralHandle = nullptr;
        uint16_t data = 0;
    };

    enum class interrupts: uint16_t {
        UART_TxComplete= 0x0101,
        UART_TxHalfComplete = 0x0102,
        UART_RxComplete = 0x0103,
        UART_RxHalfComplete = 0x0104,
        UART_Error = 0x0105,
        UART_AbortComplete =0x0106,
        UART_AbortTransmitComplete = 0x0107,
        UART_AbortReceiveComplete = 0x0108,
        UART_RxEvent = 0x0109,
        ExternalInterrupt = 0x0201,
    };

    using interrupt_function_type = function_ref<void(interrupt_data)>;

    template<uint8_t maxListeners = 5>
    class _interrupt_handler_type {
        std::pair<interrupts, interrupt_function_type> listeners[maxListeners];
        uint8_t listenerCount ;
    public:
        _interrupt_handler_type(): listenerCount{0} {}


        void call(interrupts interruptId, interrupt_data data) {
            for (uint8_t i = 0; i < listenerCount; i++) {
                if (listeners[i].first == interruptId) {
                    listeners[i].second(data);
                }
            }
        }

        void registerListener(interrupts interruptId, const interrupt_function_type &callback) {
            if (listenerCount > maxListeners) {
                return; // Todo throw error
            }

            listeners[listenerCount].first = interruptId;
            listeners[listenerCount++].second = callback;
        }

    };

    extern _interrupt_handler_type<> interrupt_handler;
}



#endif //FD_HDR_STM32_HAL_INTERRUPT
