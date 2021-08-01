#include "libc/stdio/stdio.h"

extern "C" void kernel_main(void){
    Terminal::init();
    printf("Welcome to Aether!\n");
}