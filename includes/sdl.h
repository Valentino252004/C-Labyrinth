#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#ifndef SDL_H
#define SDL_h

typedef enum state { MENU, PLAYING } state;

typedef struct {
    int running;
    state state;
} Scene;    

void sdl_loop();


#endif