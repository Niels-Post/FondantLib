#ifndef FONDANT_MAIN_CALLER_HPP
#define FONDANT_MAIN_CALLER_HPP

extern int fd_main();

extern "C" int fd_main_caller() {
    return fd_main();
}


#endif

