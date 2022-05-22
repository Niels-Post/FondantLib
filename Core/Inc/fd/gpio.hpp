#include <stm32f1xx.h>

namespace fd {

	class pin_out {
		virtual void write(bool new_value) = 0;
		virtual void toggle() = 0;
	};

	/**
	 * Klasse om een push pull outputpin aan te sturen
	 */
	class pin_out_pp: pin_out {
		GPIO_TypeDef *port;
		uint16_t pinNumber;
		bool lastState = false;
	public:
		/**
		 * Constructor voor pin_out
		 *
		 * Voordat je deze constructor gebruikt moet de pin al ingesteld zijn.
		 * Dit kan door de pin op output (push pull) in te stellen in STM32CubeIDE.
		 * Anders kan je ook fd::setup_pin_out_pp() gebruiken om dit te doen
		 * @param port Verwijzing naar de poort van de pin (bv: GPIOC)
		 * @param pin_number Het nummer van de pin, (bv: GPIO_PIN_13)
		 */
		pin_out_pp(GPIO_TypeDef *port, uint16_t pin_number): port(port), pinNumber(pin_number) {

		}

		void write(bool value) override {
			lastState = value;
			HAL_GPIO_WritePin(port, pinNumber, value ? GPIO_PIN_SET : GPIO_PIN_RESET);
		}

		void toggle() override {
			write(!lastState);
		}
	};


	class pin_in {
		GPIO_TypeDef  *port;
		uint16_t pinNumber;

	public:
		pin_in(GPIO_TypeDef *port, uint16_t pinNumber) : port(port), pinNumber(pinNumber) {}

		bool read() {
			return HAL_GPIO_ReadPin(port, pinNumber);
		}
	};

	namespace setup {
		/**
	 * Enum om de speed van en output (push/pull) pin te bepalen
	 *
	 * Door de speed hoger te zetten, kan de pin sneller wisselen van hoog naar laag en andersom, maar
	 * dit zorgt ervoor dat de microcontroller meer stroom gebruikt, en zorgt voor meer interferentie in
	 * je elektrische schema.
	 */
		enum class pin_out_speed : uint32_t {
			HIGH = GPIO_SPEED_FREQ_HIGH,
			MEDIUM = GPIO_SPEED_FREQ_MEDIUM,
			LOW = GPIO_SPEED_LOW
		};

		/**
		 * Schakel de benodigde GPIO-klokken in voor een specifieke GPIO poort
		 * @param port Poort om klokken voor in te schakelen.
		 */
		void _enable_gpio_clock(GPIO_TypeDef *port) {
			__HAL_RCC_GPIOA_CLK_ENABLE();
			if(port == GPIOB) {
				__HAL_RCC_GPIOB_CLK_ENABLE();
			} else if(port == GPIOC) {
				__HAL_RCC_GPIOC_CLK_ENABLE();
			} else if(port == GPIOD) {
				__HAL_RCC_GPIOD_CLK_ENABLE();
			} else if(port == GPIOE) {
				__HAL_RCC_GPIOE_CLK_ENABLE();
			}
		}

		/**
		 * Stel een pin in als een push/pull output pin, en maak er een fd::pin_out_pp object voor
		 * @param port De poort van de pin (bv: GPIOC)
		 * @param pin_number Het nummer van de pin (bv: GPIO_PIN_13)
		 * @param speed De snelheid waarop de pin ingesteld moet worden (bv: fd::pin_out_speed::MEDIUM)
		 * @return Een pin_out_pp object
		 */
		void pin_out_pp(GPIO_TypeDef *port, uint16_t pin_number, pin_out_speed speed = pin_out_speed::LOW) {
			GPIO_InitTypeDef GPIO_InitStruct = {0};

			/* GPIO Ports Clock Enable */
			_enable_gpio_clock(port);

			/*Configure GPIO pin Output Level */
			HAL_GPIO_WritePin(port, pin_number, GPIO_PIN_RESET);

			/*Configure GPIO pin : PC13 */
			GPIO_InitStruct.Pin = pin_number;
			GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
			GPIO_InitStruct.Pull = GPIO_NOPULL;
			GPIO_InitStruct.Speed = static_cast<uint32_t>(speed);
		}

		enum class pin_in_resistor: uint32_t {
			NONE = GPIO_NOPULL,
			PULLUP = GPIO_PULLUP,
			PULLDOWN = GPIO_PULLDOWN
		};

		void pin_in(GPIO_TypeDef *port, uint16_t pin_number, pin_in_resistor resistor = pin_in_resistor::NONE) {
			GPIO_InitTypeDef GPIO_InitStruct = {0};

			_enable_gpio_clock(port);

			/*Configure GPIO pin : PA1 */
			GPIO_InitStruct.Pin = pin_number;
			GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
			GPIO_InitStruct.Pull = static_cast<uint32_t>(resistor);
			HAL_GPIO_Init(port, &GPIO_InitStruct);
		}
	};
};