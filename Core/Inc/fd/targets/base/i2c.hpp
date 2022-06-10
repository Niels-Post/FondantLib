#ifndef FD_HDR_BASE_I2C
#define FD_HDR_BASE_I2C

#include <cstdint>

namespace fd {
	enum class i2c_status: uint8_t {
		OK,
		ERROR,
		NO_ACK,
		BUSY,
		STARTED,
		NOT_IMPLEMENTED
	};

	class i2c {

	public:
		virtual i2c_status write(uint16_t address,  uint8_t *write_date, uint8_t size) {
			return i2c_status::NOT_IMPLEMENTED;
		};

		virtual i2c_status read(uint16_t address, uint8_t *read_data, uint8_t size) {
			return i2c_status::NOT_IMPLEMENTED;
		};

		virtual i2c_status wait() {
			return i2c_status::NOT_IMPLEMENTED;
		}


		virtual i2c_status write_wait(uint16_t address, const uint8_t *write_date, const uint8_t size) {
			i2c_status result = write(address, write_date, size);
			if (result != i2c_status::STARTED) {
				return result;
			}

			return wait();
		};

		virtual i2c_status read_wait(uint16_t address, uint8_t *read_data, uint8_t size) {
			i2c_status result = write_wait(address, read_data, size);
			if (result != i2c_status::STARTED) {
				return result;
			}

			return wait();
		};
	};
}
#endif //FD_HDR_BASE_I2C
