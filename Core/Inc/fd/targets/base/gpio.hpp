#ifndef FD_GPIO
#define FD_GPIO

namespace fd {

    class pin_out_base {
    public:
        virtual void write(bool new_value) {}

        virtual void toggle() {}
    };

    class pin_in_base {
    public:
        virtual bool read() {
            return false;
        };
    };


};


#endif
