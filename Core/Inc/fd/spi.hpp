#include <fd/fondant.hpp>
#include "stm32f1xx_hal_spi.h"

namespace fd {


    class spi {
        SPI_HandleTypeDef *handle;
        bool dma;
        uint32_t default_timeout;

    public:
        spi(SPI_HandleTypeDef *handle, bool dma, uint32_t defaultTimeout) : handle(handle), dma(dma),
                                                                    default_timeout(defaultTimeout) {}


        fd::status transmit(uint8_t *write_data, uint8_t size) {
            HAL_StatusTypeDef result;
            if(dma) {
                result = HAL_SPI_Transmit_DMA(handle, write_data, size);
            } else {
                result = HAL_SPI_Transmit(handle, write_data, size, default_timeout);
            }
            return static_cast<fd::status> (result);
        }

        fd::status transmitreceive(uint8_t *write_data, uint8_t *read_data, uint8_t size) {
            HAL_StatusTypeDef result;
            if(dma) {
                result = HAL_SPI_TransmitReceive_DMA(handle, write_data, read_data, size);
            } else {
                result = HAL_SPI_TransmitReceive(handle, write_data, read_data, size, default_timeout);
            }
            return static_cast<fd::status> (result);
        }

        fd::status receive(uint8_t *read_data, uint8_t size) {
            HAL_StatusTypeDef result;
            if(dma) {
                result = HAL_SPI_Receive_DMA(handle, read_data, size);
            } else {
                result = HAL_SPI_Receive(handle,  read_data, size, default_timeout);
            }
            HAL_SPI_GetState(handle);
            return static_cast<fd::status> (result);
        }


    };
}