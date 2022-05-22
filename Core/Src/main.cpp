#include <fd/fondant.hpp>

int fd_main();
extern "C" int fd_main_() {
	return fd_main();
}

int fd_main() {
//	fd::pin_out led_pin(GPIOC, GPIO_PIN_13);
	fd::setup::pin_out_pp(GPIOC, GPIO_PIN_13);
	auto led_pin = fd::pin_out_pp(GPIOC, GPIO_PIN_13);
	while(true) {
		led_pin.toggle();
		fd::sleep(1000);
	}

	return 0;
}
