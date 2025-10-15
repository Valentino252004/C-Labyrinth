#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#ifndef SDL_H
#define SDL_h

enum state { MENU, PLAYING };

typedef struct {
    int running;
    int state;
} SDL_State;    

#endif