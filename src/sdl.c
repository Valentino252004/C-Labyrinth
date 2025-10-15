#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "sdl.h"
#include "mazeMenu.h"


void sdl_loop() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Labyrinthe", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 1200, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    Scene scene;

    scene.running = 1;
    scene.state = MENU;
    SDL_Event event;

    while(scene.running) {
        while (SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_QUIT:
                    scene.running = 0;
                    break;
            }
        }
    }
    

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}