#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <windows.h>
#include "menu.h"

int main (int argc, char* argv[]) { 
    
    //setup a random seed;
    srand(time(NULL));
    
    startGame();

    return 0; 

}