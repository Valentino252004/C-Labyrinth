#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "sdl.h"

int main (int argc, char* argv[]) {
    //setup a random seed;
    srand(time(NULL));
    
    sdl_loop();

    return 0;
}