#include <fd/fondant.hpp>
#include <fd/fondant_main.hpp>
#include <fd/gpio.hpp>

#include <examples.hpp>

int fd_main() {

    // Voorbeeld 1: Hello World (blink)
//    examples::helloworld::setup();
//    examples::helloworld::run();

    // Voorbeeld 2: Pin In Pin Out
//    examples::pininpinout::setup();
//    examples::pininpinout::run();

    // Voorbeeld 3: Pins doorgeven
//    examples::pinsdoorgeven::setup();
//    examples::pinsdoorgeven::run();

    // Voorbeeld 4: SPI
    examples::spi::setup();
    examples::spi::run();

    return 0;
}
