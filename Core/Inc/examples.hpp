#ifndef FD_HDR_EXAMPLES
#define FD_HDR_EXAMPLES

#define examplenamespace(name) namespace name { \
    void setup();                               \
    void run();                                 \
}

namespace examples {

    examplenamespace(helloworld)
    examplenamespace(pininpinout)
    examplenamespace(pinsdoorgeven)
    examplenamespace(spi)
    examplenamespace(spi_dma)
}


#endif //FD_HDR_EXAMPLES
