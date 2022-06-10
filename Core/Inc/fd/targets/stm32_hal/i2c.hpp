#ifndef FD_HDR_STM32_HAL_I2C
#define FD_HDR_STM32_HAL_I2C

#include <fd/targets/base/i2c.hpp>
#include <stm32f1xx_hal.h>

namespace fd::stm32_hal {

	enum class i2c_error_status : uint32_t {
		NONE = HAL_I2C_ERROR_NONE,
		ERROR_BERR = HAL_I2C_ERROR_BERR,
		ERROR_ARLO = HAL_I2C_ERROR_ARLO,
		ERROR_AF = HAL_I2C_ERROR_AF,
		ERROR_OVR = HAL_I2C_ERROR_OVR,
		ERROR_DMA = HAL_I2C_ERROR_DMA,
		ERROR_TIMEOUT = HAL_I2C_ERROR_TIMEOUT,
		ERROR_SIZE = HAL_I2C_ERROR_SIZE,
		ERROR_DMA_PARAM = HAL_I2C_ERROR_DMA_PARAM
	};

	i2c_status get_i2c_status(uint32_t status);

	class i2c : public ::fd::i2c {
		I2C_HandleTypeDef &handle;
		bool dma;
		uint32_t default_timeout;
		i2c_error_status last_error;

	public:
		i2c_status write(uint16_t address, uint8_t *write_date, uint8_t size) override;

		i2c_status read(uint16_t address, uint8_t *read_data, uint8_t size) override;

		i2c_status wait() override;
	};
}

#endif //FD_HDR_STM32_HAL_I2C
