#include <fd/fondant_targets.hpp>

#ifdef FONDANT_HW_I2C

#include <fd/targets/stm32_hal/i2c.hpp>


fd::i2c_status fd::stm32_hal::get_i2c_status(uint32_t status) {
	switch (status) {
		case HAL_OK:
			return i2c_status::OK;
		case HAL_ERROR:
			return i2c_status::ERROR;
		case HAL_BUSY:
			return i2c_status::BUSY;
		default:
			return i2c_status::NOT_IMPLEMENTED;
	}
}

fd::i2c_status fd::stm32_hal::i2c::write(uint16_t address, uint8_t *write_date, uint8_t size) {
	uint32_t resultStatus;
	if (dma) {
		resultStatus = HAL_I2C_Master_Transmit_DMA(&handle, address, write_date, size);
	} else {
		resultStatus = HAL_I2C_Master_Transmit(&handle, address, write_date, size, default_timeout);
	}
	last_error = (i2c_error_status) handle.ErrorCode;

	return get_i2c_status(resultStatus);
}

fd::i2c_status fd::stm32_hal::i2c::read(uint16_t address, uint8_t *read_data, uint8_t size) {
	uint32_t resultStatus;
	if (dma) {
		resultStatus = HAL_I2C_Master_Receive_DMA(&handle, address, read_data, size);
	} else {
		resultStatus = HAL_I2C_Master_Receive(&handle, address, read_data, size, default_timeout);
	}
	last_error = (i2c_error_status) handle.ErrorCode;

	return get_i2c_status(resultStatus);
}

fd::i2c_status fd::stm32_hal::i2c::wait() {
	while(handle.State == HAL_I2C_STATE_BUSY||
			handle.State == HAL_I2C_STATE_BUSY_RX||
			handle.State == HAL_I2C_STATE_BUSY_RX_LISTEN||
			handle.State == HAL_I2C_STATE_BUSY_TX||
			handle.State == HAL_I2C_STATE_BUSY_TX_LISTEN||
			handle.State == HAL_I2C_STATE_MASTER_BUSY_TX||
			handle.State == HAL_I2C_STATE_MASTER_BUSY_RX){}
	last_error = (i2c_error_status) handle.ErrorCode;
	return handle.ErrorCode == HAL_I2C_ERROR_NONE ? i2c_status::OK : i2c_status::ERROR;
}

#endif