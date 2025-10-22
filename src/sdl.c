#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "sdl.h"
#include "mazeMenu.h"
#include "labyrinth.h"
#include "files.h"
#include "game.h"

/*int get_square_size(labyrinth * laby) {
    return (LABY_SCREEN_WIDTH / laby->width < SCREEN_HEIGHT / laby->height) ? (LABY_SCREEN_WIDTH / laby->width) : (SCREEN_HEIGHT / laby->height);
}*/


void display_gameMenu(SDL_Renderer* renderer, TTF_Font* font, int* selectedItem){
    char ** menu_items = malloc(4 * sizeof(char*));
    for(int i = 0; i < 4; i++) {
        menu_items[i] = malloc(50 * sizeof(char));
    }
    strcpy(menu_items[0], "Générer un nouveau labyrinthe");
    strcpy(menu_items[1], "Charger un labyrinthe");
    strcpy(menu_items[2], "Afficher le classement (WIP)");
    strcpy(menu_items[3], "Quitter");

    display_menu(renderer, font, *selectedItem, menu_items);

    for (int i = 0; i < 4; i++) {
        free(menu_items[i]);
    }
    free(menu_items);
}

void display_maze(SDL_Renderer* renderer, Labyrinth labyrinth, TTF_Font* font) {
    int squareSize = 20;

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    for (int row = 0; row < labyrinth.height; row++) {
        for (int col = 0; col < labyrinth.width; col++) {
            tile tile = labyrinth.tiles[row][col];
            
            SDL_Rect rectangle;
            rectangle.x = col * squareSize;
            rectangle.y = row * squareSize;
            rectangle.w = squareSize;
            rectangle.h = squareSize;

            if (row == labyrinth.playerRow && col == labyrinth.playerColumn) {
                SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
            } else {
                switch(tile.c) {
                    case WALL:
                        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                        break;
                    case EMPTY:
                        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                        break;
                    case TREASURE:
                        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
                        break;
                    case TRAP:
                        SDL_SetRenderDrawColor(renderer, 224, 224, 224, 255);
                        break;
                    case KEY:
                        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
                        break;
                    case LOCKED_DOOR:
                        if (labyrinth.keyFound) {
                            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                            break;
                        }
                        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                        break;
                    default:
                        break;
                }
            }
            SDL_RenderFillRect(renderer, &rectangle);
        }
    }

    char * score = malloc(sizeof(char) * 25);
    sprintf(score, "Score: %d", labyrinth.score);
    
    SDL_Color stringColor = {255, 255, 255, 255};

    display_string(renderer, font, stringColor, score, 10, (labyrinth.height+1)*squareSize);

    free(score);
}


void display_scene(SDL_Renderer* renderer, Scene scene, TTF_Font* font, Labyrinth labyrinth) {
    switch(scene.state) {
        case MENU:
            display_gameMenu(renderer, font, &scene.selectedMenuItem);
            break;
        case PLAYING:
            display_maze(renderer, labyrinth, font);
            break;
        default:
            printf("Unknown behavior sdl.c display_scene\n");
    }
}


void keyHandlerPlaying(SDL_Keycode keyPressed, Labyrinth* labyrinth) {
    //TODO Player Row and Column in labyrinth
    int nextR = labyrinth->playerRow;
    int nextC = labyrinth->playerColumn;
    switch(keyPressed) {
        case SDLK_UP:
        case SDLK_z:
            nextR -= 1;
            break;
        case SDLK_DOWN:
        case SDLK_s:
            nextR += 1;
            break;
        case SDLK_LEFT:
        case SDLK_q:
            nextC -= 1;
            break;
        case SDLK_RIGHT:
        case SDLK_d:
            nextC += 1;
            break;
        case SDLK_ESCAPE:
            printf("Escape pressé\n");
            break;
        default: 
            return;
    }

    if (nextR < 0 || nextR >= labyrinth->height || nextC < 0 || nextC >= labyrinth->width) {
        return;
    }

    movePlayer(labyrinth, nextR, nextC);

    

}

void keyHandler(Scene scene, SDL_Event* event, Labyrinth* labyrinth) {
    SDL_Keycode keyPressed = event->key.keysym.sym;
    switch(scene.state) {
        case PLAYING:
            keyHandlerPlaying(keyPressed, labyrinth);
            break;
    }
}


void sdl_loop() {
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    TTF_Font* font = TTF_OpenFont("fonts/Ubuntu-Regular.ttf", 24);
    
    SDL_Window *window = SDL_CreateWindow("La Bireinte", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 800, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    Scene scene;
    scene.running = 1;
    scene.selectedMenuItem = 0;
    scene.state = MENU;

    //Labyrinth lab = newLabyrinth();
    //  saveLabyrinth(lab);

    Labyrinth currentLabyrinth;
    currentLabyrinth.tiles = NULL;
    currentLabyrinth.height = 0;
    currentLabyrinth.width = 0;
    currentLabyrinth.height = 0;
    currentLabyrinth.width = 0;
    currentLabyrinth.score = 0;
    currentLabyrinth.keyFound = 0;
    //chargeLabyrinth(&currentLabyrinth);

    SDL_Event event;
    while(scene.running) {
        while (SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_QUIT:
                    scene.running = 0;
                    break;
                case SDL_KEYDOWN:
                    keyHandler(scene, &event, &currentLabyrinth);
            }
        }
        display_scene(renderer, scene, font, currentLabyrinth);
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }
    

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}