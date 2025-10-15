#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "menu.h"

int main (int argc, char* argv[]) { 

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Erreur SDL : %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("Labyrinthe", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
    if (!window) {
        printf("Erreur fenêtre : %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Erreur renderer : %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    /* // Lancement du menu principal
    if (startGame(renderer)) {
        // Si le joueur clique sur "Jouer"
        game_loop(renderer);
    } */

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    printf("passé\n");

    //setup a random seed;
    srand(time(NULL));
    //test seed
    //srand(0);
    
    startGame();

    return 0; 

}