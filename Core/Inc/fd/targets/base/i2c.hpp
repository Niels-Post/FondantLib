#ifndef FD_HDR_BASE_I2C
#define FD_HDR_BASE_I2C

#include <stddef.h>
#include <cstdint>

namespace fd {
	/**
	 * Resultaat van een I2C transactie.
	 */
	enum class i2c_status: uint8_t {
		/// Transactie is succesvol afgerond
		OK,
		/// Er is een fout opgetreden tijdens de transactie
		ERROR,
		/// Er is in de transactie geen ACK van de andere partij ontvangen
		NO_ACK,
		/// De transactie is niet gestart omdat de I2C bus nog bezig is met iets anders
		BUSY,
		/// De transactie is gestart (gebruikt wait() om op het einde te wachten) (TIP: tijdens het wachten kan je ook wat anders berekenen!)
		STARTED,
		/// De aangeroepen functie is niet geïmplementeerd. Let erop dat je i2c_base altijd by reference of by pointer gebruikt.
		NOT_IMPLEMENTED
	};

	/**
	 * Basisklasse voor I2C-implementaties.
	 *
	 * Bescrhijft een aantal basisfuncties die geïmplementeerd kunnen worden om I2C functies te vervullen.
	 *
	 * Functies kunnen (afhankelijk van het aparaat) ingesteld zijn om asynchroon uitgevoerd te worden.
	 * Bij het aanroepen van een lees- of schrijffunctie zal deze i2c_status::STARTED teruggeven.
	 * Wanneer het resultaat nodig is kan wait() aangeroepen worden.
	 * Om de functie aan te roepen en direct af te wachten kunnen ook de read_wait/write_wait functies gebruikt worden.
	 */
	class i2c_base {

	public:
		/**
		 * Voer een schrijftransactie uit naar het gegeven apparaat
		 * @param device_address Apparaatadres
		 * @param write_data Pointer naar een data array om te schrijven
		 * @param size Aantal bytes om te schrijven (exclusief het adres)
		 * @return De resultaatstatus
		 */
		virtual i2c_status write(uint16_t device_address, uint8_t *write_data, size_t size) {
			return i2c_status::NOT_IMPLEMENTED;
		};

		/**
		 * Voer een leestransactie uit vanuit het gegeven apparaat
		 * @param device_address Apparaatadres
		 * @param read_data Pointer naar een data array om naartoe te schrijven (let erop dat er genoeg ruimte beschikbaar is)
		 * @param size Aantal bytes om te lezen (exclusief het adres)
		 * @return De resultaatstatus
		 */
		virtual i2c_status read(uint16_t device_address, uint8_t *read_data, size_t size) {
			return i2c_status::NOT_IMPLEMENTED;
		};

		/**
		 * Schrijf gegevens naar een register op het gegeven apparaat
		 * @param device_address Apparaatadres
		 * @param reg_address Adres van het register
		 * @param address_length Lengte van het adresregister (1 of 2 bytes)
		 * @param write_data Pointer naar een data array om te schrijven
		 * @param size Aantal bytes om te schrijven (exclusief het device- en register-adres)
		 * @return De resultaatstatus
		 */
        virtual i2c_status write_reg(uint16_t device_address, uint16_t reg_address, uint8_t address_length, uint8_t *write_data, size_t data_size){
            return i2c_status::NOT_IMPLEMENTED;
        }

		/**
		 * Lees gegevens uit een register op het gegeven apparaat.
		 * @param device_address Apparaatadres
		 * @param reg_address Adres van het register
		 * @param address_length Lengte van het adresregister (1 of 2 bytes)
		 * @param write_data Pointer naar een data array om naartoe te lezen
		 * @param size Aantal bytes om te schrijven (exclusief het device- en register-adres)
		 * @return De resultaatstatus
		 */
        virtual i2c_status read_reg(uint16_t device_address, uint16_t reg_address, uint8_t address_length, uint8_t *read_data, size_t data_size){
            return i2c_status::NOT_IMPLEMENTED;
        }

        /**
         * Wacht totdat de laatste transactie klaar is.
         * @return
         */
		virtual i2c_status wait() {
			return i2c_status::NOT_IMPLEMENTED;
		}


		/**
		 * Start een schrijftransactie en wacht direct tot deze voltooid is
		 * Zie i2c_base::write voor een beschrijving van de parameters
		 */
		virtual i2c_status write_wait(uint16_t device_address, uint8_t *write_data, const uint8_t size) {
			i2c_status result = write(device_address, write_data, size);
			if (result != i2c_status::STARTED) {
				return result;
			}

			return wait();
		};

		/**
		 * Start een register-schrijftransactie en wacht direct tot deze voltooid is
		 * Zie i2c_base::write_reg voor een beschrijving van de parameters
		 */
        virtual i2c_status write_reg_wait(uint16_t device_address, uint16_t reg_address, uint8_t address_length, uint8_t *write_data, uint8_t data_size) {
            i2c_status result = write_reg(device_address, reg_address, address_length, write_data, data_size);
            if (result != i2c_status::STARTED) {
                return result;
            }

            return wait();
        };

        /**
         * Start een leestransactie en wacht direct tot deze voltooid is
         * Zie i2c_base::read voor een beschrijving van de parameters
         */
		virtual i2c_status read_wait(uint16_t deviec_address, uint8_t *read_data, uint8_t size) {
			i2c_status result = read(deviec_address, read_data, size);
			if (result != i2c_status::STARTED) {
				return result;
			}

			return wait();
		};

		/**
         * Start een register-leestransactie en wacht direct tot deze voltooid is
         * Zie i2c_base::read_reg voor een beschrijving van de parameters
         */
        virtual i2c_status read_reg_wait(uint16_t device_address, uint16_t reg_address, uint8_t address_length, uint8_t *read_data, uint8_t data_size) {
            i2c_status result = read_reg(device_address, reg_address, address_length, read_data, data_size);
            if (result != i2c_status::STARTED) {
                return result;
            }

            return wait();
        };
	};
}
#endif //FD_HDR_BASE_I2C
