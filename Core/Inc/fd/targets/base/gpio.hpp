#ifndef FD_HDR_BASE_GPIO
#define FD_HDR_BASE_GPIO

namespace fd {

    class pin_out_base {
    public:
        virtual void write(bool new_value) {}

        virtual void toggle() {}
    };

    extern pin_out_base pin_out_dummy;

    class pin_in_base {
    public:
        virtual bool read() {
            return false;
        };
    };

    extern pin_in_base pin_in_dummy;


};


#endif //FD_HDR_BASE_GPIO
