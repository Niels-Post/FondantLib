#ifndef FD_HDR_PERIPHERAL_MATRIX_4X4_HPP
#define FD_HDR_PERIPHERAL_MATRIX_4X4_HPP

#include <cstdint>
#include <fd/targets/base/gpio.hpp>

namespace fd::peripherals {
    class keypad_matrix_4x4 {
        fd::pin_out_base *rows[4];

        fd::pin_in_base *cols[4];

    public:
        keypad_matrix_4x4(fd::pin_out_base &r1, fd::pin_out_base &r2, fd::pin_out_base &r3, fd::pin_out_base &r4,
                          fd::pin_in_base &c1, fd::pin_in_base &c2, fd::pin_in_base &c3, fd::pin_in_base &c4);

        struct Button {
            uint16_t   value;
            const char *name;
        };

        static inline const Button buttons[] = {
            Button {1 << 15, "1"},
            Button {1 << 14, "2"},
            Button {1 << 13, "3"},
            Button {1 << 12, "A"},
            Button {1 << 11, "4"},
            Button {1 << 10, "5"},
            Button {1 << 9, "6"},
            Button {1 << 8, "B"},
            Button {1 << 7, "7"},
            Button {1 << 6, "8"},
            Button {1 << 5, "9"},
            Button {1 << 4, "C"},
            Button {1 << 3, "STAR"},
            Button {1 << 2, "0"},
            Button {1 << 1, "HASH"},
            Button {1 << 0, "D"}
        };

        uint16_t getValue();

        Button getSinglePressedButton();
    };
}
#endif //FD_HDR_PERIPHERAL_MATRIX_4X4_HPP
