#include "../terminal/terminal.h"

extern "C" void kernel_main(void){
    Terminal terminal;

    terminal.init();
    terminal.writeString("Classtest");
}