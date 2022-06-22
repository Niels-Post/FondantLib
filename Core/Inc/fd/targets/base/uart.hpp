#ifndef FD_HDR_BASE_UART
#define FD_HDR_BASE_UART

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
        /// De aangeroepen functie is niet geïmplementeerd. Let erop dat je spi_base altijd by reference of by pointer gebruikt.
        NOT_IMPLEMENTED = 0x10u
    };


    class uart_base {
        
    };
}

#endif //FD_HDR_BASE_UART
