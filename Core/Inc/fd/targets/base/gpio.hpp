#ifndef FD_HDR_BASE_GPIO
#define FD_HDR_BASE_GPIO

namespace fd {

	/**
	 * Algemene basisklasse voor een GPIO pin out.
	 */
    class pin_out_base {
    public:
    	/**
    	 * Zet de pin op een hoge of lage staat (hoog=true, laag=false)
    	 * @param new_value
    	 */
        virtual void write(bool new_value) {}

        /**
         * Wissel de staat van de pin (hoog>laag, laag>hoog)
         */
        virtual void toggle() {}
    };

    /**
     * Dummy pin.
     * Kan bijvoorbeeld gebruikt worden als default value voor een pin-reference naar een pin die optioneel is.
     * Alle outputfuncties van deze pin hebben geen effect.
     */
    extern pin_out_base pin_out_dummy;

    /**
     * Generic class for a GPIO pin in
     */
    class pin_in_base {
    public:
        virtual bool read() {
            return false;
        };
    };

	/**
	 * Dummy pin.
	 * Kan bijvoorbeeld gebruikt worden als default value voor een pin-reference naar een pin die optioneel is.
	 * Read geeft altijd false terug vor deze pin
	 */
    extern pin_in_base pin_in_dummy;


};


#endif //FD_HDR_BASE_GPIO
