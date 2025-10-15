#ifndef SDL_H
#define SDL_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "labyrinth.h"

typedef enum state { MENU, PLAYING } state;

typedef struct {
    int running;
    state state;
} Scene;    

void sdl_loop();

void display_maze(SDL_Renderer* renderer, Labyrinth labyrinth, TTF_Font* font);

void display_scene(SDL_Renderer* renderer, Scene scene, TTF_Font* font, Labyrinth labyrinth);


// ============ SDL_UTILS ============

void display_string(SDL_Renderer* renderer, TTF_Font* font, SDL_Color color, char* string, int x, int y);

#endif