/**
 * This file serves as an embedded-friendly alternative for using std::function.
 * Std::function takes too much space to use on STM32.
 *
 * Opposed to regular function pointers, function_ref allows for use of state capturing lambda's.
 *
 * The implementation for function_ref was taken from https://groups.google.com/a/isocpp.org/g/std-proposals/c/vMvzAl0a-P8/m/P1KeGhhGCAAJ
 * A constructor was added to allow for functions returning void to have a default constructor, allowing arrays to be populated with them.
 *
 */
#ifndef FD_HDR_FUNCTIONAL
#define FD_HDR_FUNCTIONAL

#include <utility>

namespace fd {
    template<typename Fn>
    class function_ref;


    /**
     * function_ref slaat een verwijziging op naar een functie/lambda.
     * @tparam Ret Het return type van de functie
     * @tparam Args De argumenten voor de functie
     */
    template<typename Ret, typename... Args>
    class function_ref<Ret(Args...)> {
        using thunk_type = Ret (*)(const function_ref *, Args...);
        const void *_lambda;
        thunk_type _thunk;
    public:
        /**
         * Maak een function_ref door een functie/lambda mee te geven. Hierbij hoef je de template parameter "Lambda" niet te
         * specificeren, omdat deze door de compiler automatisch opgemaakt kan worden.
         *
         * Let op dat de betreffende lambda/functie nog steeds moet bestaan als deze aangeroepen wordt!!
         * @tparam Lambda Het type van de functie/lambda
         * @param lambda De functie/lambda om een function_ref naar te maken
         */
        template<typename Lambda>
        function_ref(const Lambda &lambda)
                : _lambda(&lambda) {
            _thunk = thunk_type([](const function_ref *zis, Args... args) {
                auto lambda = static_cast<const Lambda *>(zis->_lambda);
                return (*lambda)(std::move(args)...);
            });
        }

        template<typename Return=Ret, typename std::enable_if<std::is_same<Return, void>::value, int>::type = 0>
        function_ref(): function_ref([](Args...) {}) {

        }


        Ret operator()(Args... args) const {
            return _thunk(this, std::move(args)...);
        }
    };
}

#endif //FD_HDR_FUNCTIONAL
