#ifndef FD_HDR_BASE_UART
#define FD_HDR_BASE_UART

#include <stddef.h>
#include <fd/fondant.hpp>

namespace fd {

    enum class uart_status: uint8_t {
        /// Transactie succesvol afgerond
        OK = 0x01U,
        /// Er was een error tijdens de transactie
        ERROR = 0x02U,
        /// De SPI-bus was al bezig met iets anders
        BUSY = 0x04U,
        /// De transactie is gestart, gebruikt wait() om op het resultaat te wachten
        STARTED = 0x08U,
        /// De andere partij heeft niet op tijd data verstuurd
        TIMEOUT = 0x10u,
        /// De aangeroepen functie is niet geïmplementeerd. Let erop dat je spi_base altijd by reference of by pointer gebruikt.
        NOT_IMPLEMENTED = 0x20u
    };


    class uart_base {
    public:
        virtual uart_status transmit(uint8_t *data, size_t size) {
            return uart_status::NOT_IMPLEMENTED;
        };

        uart_status transmit_wait(uint8_t *data, size_t size) {
            auto code = transmit(data, size);
            if(code != uart_status::STARTED) {
                return code;
            }
            return wait();
        };

        virtual uart_status receive(uint8_t *inData, size_t size, size_t max_wait_ms) {
            return uart_status::NOT_IMPLEMENTED;
        }

        uart_status receive_wait(uint8_t *data, size_t size, size_t max_wait_ms) {
            auto code = receive(data, size, max_wait_ms);
            if(code != uart_status::STARTED) {
                return code;
            }
            return wait();
        };


        uart_status wait() {
            return uart_status::NOT_IMPLEMENTED;
        };
    };
}

#endif //FD_HDR_BASE_UART
