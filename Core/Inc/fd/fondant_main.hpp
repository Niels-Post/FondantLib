#ifndef FD_HDR_FONDANT_MAIN
#define FD_HDR_FONDANT_MAIN

extern int fd_main();

extern "C" int fd_main_caller() {
    return fd_main();
}


#endif //FD_HDR_FONDANT_MAIN

