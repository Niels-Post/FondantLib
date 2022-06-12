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

	class i2c_base {

	public:
		virtual i2c_status write(uint16_t address, uint8_t *write_data, uint8_t size) {
			return i2c_status::NOT_IMPLEMENTED;
		};

		virtual i2c_status read(uint16_t address, uint8_t *read_data, uint8_t size) {
			return i2c_status::NOT_IMPLEMENTED;
		};

        virtual i2c_status write_reg(uint16_t address, uint16_t reg_address, uint8_t address_length,uint8_t *write_data, uint8_t data_size){
            return i2c_status::NOT_IMPLEMENTED;
        }

        virtual i2c_status read_reg(uint16_t address, uint16_t reg_address, uint8_t address_length,uint8_t *read_data, uint8_t data_size){
            return i2c_status::NOT_IMPLEMENTED;
        }

		virtual i2c_status wait() {
			return i2c_status::NOT_IMPLEMENTED;
		}


		virtual i2c_status write_wait(uint16_t address, uint8_t *write_data, const uint8_t size) {
			i2c_status result = write(address, write_data, size);
			if (result != i2c_status::STARTED) {
				return result;
			}

			return wait();
		};

        virtual i2c_status write_reg_wait(uint16_t address, uint16_t reg_address, uint8_t address_length,uint8_t *write_data, uint8_t data_size) {
            i2c_status result = write_reg(address, reg_address, address_length, write_data, data_size);
            if (result != i2c_status::STARTED) {
                return result;
            }

            return wait();
        };

		virtual i2c_status read_wait(uint16_t address, uint8_t *read_data, uint8_t size) {
			i2c_status result = read(address, read_data, size);
			if (result != i2c_status::STARTED) {
				return result;
			}

			return wait();
		};

        virtual i2c_status read_reg_wait(uint16_t address, uint16_t reg_address, uint8_t address_length,uint8_t *read_data, uint8_t data_size) {
            i2c_status result = read_reg(address, reg_address, address_length, read_data, data_size);
            if (result != i2c_status::STARTED) {
                return result;
            }

            return wait();
        };
	};
}
#endif //FD_HDR_BASE_I2C
