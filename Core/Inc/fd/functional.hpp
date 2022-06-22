#ifndef FD_HDR_FUNCTIONAL
#define FD_HDR_FUNCTIONAL

#include <utility>

template <typename Fn>
class function_ref;

template <typename Ret, typename... Args>
class function_ref<Ret (Args...)> {
    using thunk_type = Ret (*)(const function_ref*, Args...);
    const void* _lambda;
    thunk_type _thunk;
public:
    template <typename Lambda>
    function_ref(const Lambda& lambda)
            : _lambda(&lambda) {
        _thunk = thunk_type([] (const function_ref* zis, Args... args) {
            auto lambda = static_cast<const Lambda*>(zis->_lambda);
            return (*lambda)(std::move(args)...);
        });
    }

    template<typename Return=Ret,typename std::enable_if<std::is_same<Return,void>::value,int>::type = 0>
    function_ref(): function_ref([](Args...) {}) {

    }

    Ret operator()(Args... args) const {
        return _thunk(this, std::move(args)...);
    }
};

#endif //FD_HDR_FUNCTIONAL
