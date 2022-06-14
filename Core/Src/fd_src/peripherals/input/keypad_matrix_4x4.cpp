#include <fd/peripherals/input/keypad_matrix_4x4.hpp>
#include <fd/fondant.hpp>

using fd::peripherals::keypad_matrix_4x4;
keypad_matrix_4x4::keypad_matrix_4x4(fd::pin_out_base &r1, fd::pin_out_base &r2, fd::pin_out_base &r3,
                                     fd::pin_out_base &r4, fd::pin_in_base &c1, fd::pin_in_base &c2,
                                     fd::pin_in_base &c3, fd::pin_in_base &c4) : rows{&r1, &r2, &r3, &r4},
                                                                                 cols{&c1, &c2, &c3, &c4} {}


uint16_t keypad_matrix_4x4::getValue() {
    uint16_t value = 0;
    for (auto row : rows) {
        row->write(false);

        for (auto col : cols) {
            value <<= 1;
            value |= !col->read();
        }

        row->write(true);
        fd::sleep(10);
    }

    return value;
}

keypad_matrix_4x4::Button fd::peripherals::keypad_matrix_4x4::getSinglePressedButton() {
    uint16_t value = getValue();

    for(auto b : buttons) {
        if(value & b.value) {
            return b;
        }
    }
    return Button{0, "NONE"};
}
