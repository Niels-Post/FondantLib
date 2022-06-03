#ifndef FONDANTLIB_EXAMPLES_HPP
#define FONDANTLIB_EXAMPLES_HPP

#define examplenamespace(name) namespace name { \
    void setup();                               \
    void run();                                 \
}

namespace examples {

    examplenamespace(helloworld)
    examplenamespace(pininpinout)
    examplenamespace(pinsdoorgeven)
}


#endif //FONDANTLIB_EXAMPLES_HPP
