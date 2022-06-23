#ifndef FD_HDR_STM32_HAL_INTERRUPT
#define FD_HDR_STM32_HAL_INTERRUPT


#include <utility>
#include <variant>
#include "fd/functional.hpp"

namespace fd::stm32_hal {
    /**
     * Bevat informatie over de aanroep van een interrupt.
     * Afhankelijk van de specifieke interrupt kan deze informatie variëren.
     * Zie de documentatie in de fd::stm32_hal::interrupts hiervoor
     */
    struct interrupt_data {
        void     *peripheralHandle = nullptr;
        uint16_t data0             = 0;
        uint16_t data1             = 0;
    };

    enum class interrupts : uint16_t {
        /// Gebruikt voor alle externe interrupts. Dezen worden aangeroepen wanneer de staat van een pin veranderd
        /// Interrupt_data.data0 bevat het bitmask van het pinnummer (In HAL opgenomen met macro's: GPIO_PIN_N)
        ExternalInterrupt = 0x0101,

        /// Aangeroepen wanneer een UART transmissie volledig afgerond is
        /// Interrupt_data.peripheralHandle bevat een pointer naar de UART_HandleTypeDef
        UART_TxComplete            = 0x0201,
        /// Angeroepen wanneer de helft van het aangegeven aantal bytes van een UART transmissie is verzonden
        /// Interrupt_data.peripheralHandle bevat een pointer naar de UART_HandleTypeDef
        UART_TxHalfComplete        = 0x0202,
        /// Aangeroepen wanneer een UART ontvangst volledig afgerond is
        /// Interrupt_data.peripheralHandle bevat een pointer naar de UART_HandleTypeDef
        UART_RxComplete            = 0x0203,
        /// Aangeroepen wanneer de helft van het aangegeven aantal bytes via UART is ontvangen
        /// Interrupt_data.peripheralHandle bevat een pointer naar de UART_HandleTypeDef
        UART_RxHalfComplete        = 0x0204,
        /// Aangeroepen wanneer er een error voorkomt bij een UART transmissie/ontvangst
        /// Interrupt_data.peripheralHandle bevat een pointer naar de UART_HandleTypeDef
        UART_Error                 = 0x0205,
        /// Aangeroepen wanneer HAL_UART_Abort volledig is afgerond
        /// Interrupt_data.peripheralHandle bevat een pointer naar de UART_HandleTypeDef
        UART_AbortComplete         = 0x0206,
        /// Aangeroepen wanneer HAL_UART_AbortTransmit volledig is afgerond
        /// Interrupt_data.peripheralHandle bevat een pointer naar de UART_HandleTypeDef
        UART_AbortTransmitComplete = 0x0207,
        /// Aangeroepen wanneer HAL_UART_AbortReceive volledig is afgerond
        /// Interrupt_data.peripheralHandle bevat een pointer naar de UART_HandleTypeDef
        UART_AbortReceiveComplete  = 0x0208,
        /// Legacy
        /// Interrupt_data.peripheralHandle bevat een pointer naar de UART_HandleTypeDef
        /// Data0 bevat de size van al gelezen bytes
        UART_RxEvent               = 0x0209,


        /// Aangeroepen wanneer een SPI transmissie volledig afgerond is
        /// Interrupt_data.peripheralHandle bevat een pointer naar de SPI_HandleTypeDef
        SPI_TxComplete       = 0x0301,
        /// Aangeroepen wanneer een SPI ontvangst volledig afgerond is
        /// Interrupt_data.peripheralHandle bevat een pointer naar de SPI_HandleTypeDef
        SPI_RxComplete       = 0x0302,
        /// Aangeroepen wanneer een SPI uitwisseling volledig afgerond is
        /// Interrupt_data.peripheralHandle bevat een pointer naar de SPI_HandleTypeDef
        SPI_TxRxComplete     = 0x0303,
        /// Angeroepen wanneer de helft van het aangegeven aantal bytes van een SPI transmissie is verzonden
        /// Interrupt_data.peripheralHandle bevat een pointer naar de SPI_HandleTypeDef
        SPI_TxHalfComplete   = 0x0304,
        /// Aangeroepen wanneer de helft van het aangegeven aantal bytes via SPI is ontvangen
        /// Interrupt_data.peripheralHandle bevat een pointer naar de SPI_HandleTypeDef
        SPI_RxHalfComplete   = 0x0305,
        /// Aangeroepen wanneer de helft van het aangegeven aantal bytes via SPI is ontvangen en verzonden
        /// Interrupt_data.peripheralHandle bevat een pointer naar de SPI_HandleTypeDef
        SPI_TxRxHalfComplete = 0x0306,
        /// Aangeroepen wanneer er een error voorkomt bij een SPI transmissie/ontvangst
        /// Interrupt_data.peripheralHandle bevat een pointer naar de SPI_HandleTypeDef
        SPI_Error            = 0x0307,
        /// Aangeroepen wanneer HAL_SPI_Abort volledig is afgerond
        /// Interrupt_data.peripheralHandle bevat een pointer naar de SPI_HandleTypeDef
        SPI_AbortComplete    = 0x0308,

        /// Aangeroepen wanneer er een I2C-master-schrijftransactie helemaal is afgerond
        /// Interrupt_data.peripheralHandle bevat een pointer naar de I2C_HandleTypeDef
        I2C_MasterTxComplete = 0x0401,
        /// Aangeroepen wanneer er een I2C-master-leestransactie helemaal is afgerond
        /// Interrupt_data.peripheralHandle bevat een pointer naar de I2C_HandleTypeDef
        I2C_MasterRxComplete = 0x0402,
        /// Aangeroepen wanneer er een I2C-slave-transmissie helemaal is afgerond
        /// Interrupt_data.peripheralHandle bevat een pointer naar de I2C_HandleTypeDef
        I2C_SlaveTxComplete  = 0x0403,
        /// Aangeroepen wanneer er een I2C-slave-ontvangst helemaal is afgerond
        /// Interrupt_data.peripheralHandle bevat een pointer naar de I2C_HandleTypeDef
        I2C_SlaveRxComplete  = 0x0404,
        /// Aangeroepen wanneer er door een andere master een I2C transactie wordt gestart naar de slave van de stm32
        /// Interrupt_data.peripheralHandle bevat een pointer naar de I2C_HandleTypeDef
        /// Interrupt_data.data0 bevat de richting van de transmissie (0=receive, 1=transmit)
        /// Interrupt_data.data1 bevat het adres wat door de master gegeven is
        I2C_Addr             = 0x0405,
        /// TODO
        /// Interrupt_data.peripheralHandle bevat een pointer naar de I2C_HandleTypeDef
        I2C_ListenComplete   = 0x0406,
        /// Aangeroepen wanneer schrijftransactie naar een I2C geheugen is afgerond
        /// Interrupt_data.peripheralHandle bevat een pointer naar de I2C_HandleTypeDef
        I2C_MemTxComplete    = 0x0407,
        /// Aangeroepen wanneer leestransactie vanuit een I2C geheugen is afgerond
        /// Interrupt_data.peripheralHandle bevat een pointer naar de I2C_HandleTypeDef
        I2C_MemRxComplete    = 0x0408,
        /// Aangeroepen wanneer er een I2C fout is opgetreden
        /// Interrupt_data.peripheralHandle bevat een pointer naar de I2C_HandleTypeDef
        I2C_Error            = 0x0409,
        /// Aangeroepen wanneer HAL_I2C_Master_Abort_IT volledig is uitgevoerd
        /// Interrupt_data.peripheralHandle bevat een pointer naar de I2C_HandleTypeDef
        I2C_AbortComplete    = 0x0410
    };

    using interrupt_function_type = function_ref<void(interrupt_data)>;

    template<uint8_t maxListeners = 5>
    class _interrupt_handler_type {
        std::pair<interrupts, interrupt_function_type> listeners[maxListeners];
        uint8_t                                        listenerCount;
    public:
        _interrupt_handler_type() : listenerCount{0} {}


        /**
         * Roep de interrupt-listeners van een bepaalde interrupt aan
         * @param interruptId Id van de interrupt
         * @param data Data om mee te geven aan de interrupt functies
         */
        void call(interrupts interruptId, interrupt_data data) {
            for (uint8_t i = 0; i < listenerCount; i++) {
                if (listeners[i].first == interruptId) {
                    listeners[i].second(data);
                }
            }
        }

        /**
         * Voeg een listener toe aan een specifiek interrupt id
         *
         * Let er op dat de functie nog moet bestaan ten tijde van de interrupt. Geef hier dus geen inline lambda oid. aan mee
         * TODO beperk de constructor om dit onmogelijk te maken
         * @param interruptId Id van de interrupt
         * @param callback functie die aangeroepen moet worden voor de interrupt.
         */
        void registerListener(interrupts interruptId, const interrupt_function_type &callback) {
            if (listenerCount > maxListeners) {
                return; // Todo throw error
            }

            listeners[listenerCount].first    = interruptId;
            listeners[listenerCount++].second = callback;
        }

    };

    /// Een statische instantie van interrupt_handler, zodat deze vanuit globale function pointers aangeroepen kan worden
    extern _interrupt_handler_type<> interrupt_handler;
}


#endif //FD_HDR_STM32_HAL_INTERRUPT
