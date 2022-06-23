#include <fd/interrupt.hpp>
#include <fd/gpio.hpp>

#ifdef FONDANT_INTERRUPTS

#include <fd/fondant.hpp>

namespace examples::interrupts {

    void setup() {
        fd::stm32_hal::pin_out::setup(GPIOC, GPIO_PIN_13);
    }


    void run() {
        // Maak een pin_out aan voor de Onboard LED
        auto pinOut = fd::stm32_hal::pin_out{GPIOC, GPIO_PIN_13};

        // Deze lambda functie togglet de pin
        // [&pinOut] zorgt ervoor dat de pin by reference beschikbaar is in de functie
        auto func = [&pinOut](fd::stm32_hal::interrupt_data data) {

            // We controleren of de interrupt wel aangeroepen is op pin 0
            // Alle pins zijn gegroepeerd op nummer in de interrupt-controller. (niet op poort)
            // Hierdoor is er geen onderscheid mogelijk tussen een interrupt op A0 en een interrupt op B0.
            // Daarom selecteren we alleen op pin-nummer
            if(data.data0 != GPIO_PIN_0) {
                return;
            }

            // Het keyword static geeft aan de variabele last_ticks bewaard moet blijven tussen uitvoeringen van de functie
            // Deze wordt dus alleen de eerste keer dat de functie uitgevoerd wordt op 0 gezet
            static uint32_t last_ticks = 0;

            // Haal de nieuwe "tijd" op
            uint32_t new_ticks = fd::stm32_hal::get_current_ticks();

            // Als er meer dan 500 ticks voorbij zijn sinds de laatste toggle
            if((new_ticks - last_ticks) > 500) {
                // Toggle de LED
                pinOut.toggle();
                // Ververs de last_ticks variabele
                last_ticks = new_ticks;
            }
        };

        // Omdat de EXTI-interrupt al ingesteld is in de IDE hoeven we alleen maar een listener toe te voegen op ExternalInterrupt

        fd::stm32_hal::interrupt_handler.registerListener(fd::stm32_hal::interrupts::ExternalInterrupt, func );


        while (true) {
            // Omdat een interrupt in hardware wordt aangeroepen hoeven we in deze loop niks meer te doen
            fd::sleep(100);
        }
    }

}

#endif