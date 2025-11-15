#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "sdl.h"
#include "labyrinth.h"
#include "files.h"
#include "game.h"

/*int get_square_size(labyrinth * laby) {
    return (LABY_SCREEN_WIDTH / laby->width < SCREEN_HEIGHT / laby->height) ? (LABY_SCREEN_WIDTH / laby->width) : (SCREEN_HEIGHT / laby->height);
}*/

void display_gameMenu(SDL_Renderer* renderer, TTF_Font* font, Scene* scene){

    setMainMenuFields(scene->menu);

    display_menu(renderer, font, scene->menu);

    freeMenuItems(scene->menu);
}

void display_labyrinthCreationMenu(SDL_Renderer* renderer, TTF_Font* font, Scene* scene) {

    setCreationMenuFields(scene->menu);
    
    display_menu(renderer, font, scene->menu);

    freeMenuItems(scene->menu);
}

void display_labyrinthCreation(SDL_Renderer* renderer, TTF_Font* font, Scene* scene) {

    setCreatingLabyrinthMenuFields(scene->menu);
    
    display_menu(renderer, font, scene->menu);

    freeMenuItems(scene->menu);
}

void display_playerWon(SDL_Renderer* renderer, TTF_Font* font, Scene* scene, Labyrinth* labyrinth) {

    setPlayerWonMenu(scene->menu);
    
    display_winningMenu(renderer, font, scene->menu, labyrinth);

    freeMenuItems(scene->menu);
}

void display_maze(SDL_Renderer* renderer, TTF_Font* font, Labyrinth* labyrinth) {
    int squareSize = 20;

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    for (int row = 0; row < labyrinth->height; row++) {
        for (int col = 0; col < labyrinth->width; col++) {
            tile tile = labyrinth->tiles[row][col];
            
            SDL_Rect rectangle;
            rectangle.x = col * squareSize;
            rectangle.y = row * squareSize;
            rectangle.w = squareSize;
            rectangle.h = squareSize;

            if (row == labyrinth->playerRow && col == labyrinth->playerColumn) {
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
                        if (labyrinth->keyFound) {
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
    sprintf(score, "Score: %d", labyrinth->score);
    
    SDL_Color stringColor = {255, 255, 255, 255};

    display_string(renderer, font, stringColor, score, 10, (labyrinth->height+1)*squareSize);

    free(score);
}


void display_scene(SDL_Renderer* renderer, Scene* scene, TTF_Font* font, Labyrinth* labyrinth) {
    switch(scene->state) {
        case MAIN_MENU:
            display_gameMenu(renderer, font, scene);
            return;
        case LABYRINTH_CREATION:
            display_labyrinthCreationMenu(renderer, font, scene);
            return;
        case CREATING_LABYRINTH:
            display_labyrinthCreation(renderer, font, scene);
            return;
        case PLAYING:
            display_maze(renderer, font, labyrinth);
            return;
        case PLAYER_WON:
            display_playerWon(renderer, font, scene, labyrinth);
            return;
        default:
            printf("Unknown behavior sdl.c display_scene\n");
    }
}


void keyHandlerPlaying(SDL_Keycode keyPressed, Scene* scene, Labyrinth* labyrinth) {
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

    if (hasPlayerWon(labyrinth)) {
        setupMenuWonInputs(scene->menu);
        scene->state = PLAYER_WON;
    }

}

void keyHandlerMenuSelection(SDL_Keycode keypressed, Menu* menu) {
    switch(keypressed) {
        case SDLK_s:
        case SDLK_DOWN:
            menu->isWriting = 0;
            menu->selectedMenuItem++;
            break;
        case SDLK_z:
        case SDLK_UP:
            menu->isWriting = 0;
            menu->selectedMenuItem--;
            break;
    }
}

void keyHandlerMainMenu(SDL_Keycode keypressed, Scene* scene, Labyrinth* labyrinth) {
    keyHandlerMenuSelection(keypressed, scene->menu);
    switch(keypressed) {
        case SDLK_KP_ENTER: //Numpad
        case SDLK_RETURN:   //basic enter keys
            switch(scene->menu->selectedMenuItem) {
                case MAIN_MENU_LABYRINTH_CREATION:
                    freeLabyrinth(labyrinth);
                    setupMenuCreationInputs(scene->menu);
                    scene->state = LABYRINTH_CREATION;
                    break;
                case MAIN_MENU_CHARGE_LABYRINTH:
                    printf("WIP");
                    break;
                case MAIN_MENU_RANKING:
                    printf("WIP");
                    break;
                case MAIN_MENU_EXIT:
                    scene->running = 0;
                    break;
                default:
                    break;
            }
            break;
    }
}
void keyHandlerTextInput(Menu* menu, SDL_Event* event) {
    if (menu->isWriting) {
        Input* input = menu->inputs[menu->selectedMenuItem];
        if (input->type == TEXT) {
            int len = strlen(input->inputValue);
            if (len < 49) {
                strcat(input->inputValue, event->text.text);
            }
        }
        else {
            int isNumber = 1;
            if (!isdigit(event->text.text[0])) {
                isNumber = 0;
            }
            if (isNumber) {
                int len = strlen(input->inputValue);
                if (len < 49) {
                    strcat(input->inputValue, event->text.text);
                }
            }
        }
    }
}

void toggleInputWriting(Menu* menu, int action) {
    if (action == 2) { // reverse
        action = !menu->isWriting;
    }
    if (action) {
        printf("startInput\n");
        SDL_StartTextInput();
        menu->isWriting = 1;
    } else {
        printf("stopInput\n");
        SDL_StopTextInput();
        menu->isWriting = 0;
    }
}

void validateLabyrinthCreation(Scene* scene, Labyrinth* labyrinth) {
    Menu* menu = scene->menu;
    char* name = malloc(50* sizeof(char));

    strcpy(name, menu->inputs[0]->inputValue);
    int width = atoi(menu->inputs[1]->inputValue);
    int height = atoi(menu->inputs[2]->inputValue);

    int validInputs = 1;
    if (strlen(name) == 0) {
        printf("Pas bien name !\n");
        validInputs = 0;
    }
    if (width < 5 || width%2 != 1) {
        printf("Pas bien width !\n");
        validInputs = 0;
    }
    if (height < 5 || height%2 != 1) {
        printf("Pas bien height !\n");
        validInputs = 0;
    }
    
    if (validInputs) {
        scene->state = CREATING_LABYRINTH;
        freeLabyrinth(labyrinth);
        *labyrinth = newLabyrinth(width, height, name);
        scene->state = PLAYING;
    }

    free(name);
}

void keyHandlerMenuInputs(SDL_Keycode keyPressed, Scene* scene) {
    Menu* menu = scene->menu;
    Input* input = menu->inputs[menu->selectedMenuItem];
    int isWritingOption; 
    switch (keyPressed) {
        case SDLK_s:
            if (menu->nbInputs > menu->selectedMenuItem) {
                if (menu->isWriting && input->type == TEXT) {
                    break;
                }
            }
            __attribute__((fallthrough));  //Shows the compiler we know we will fall thoughout the next case
        case SDLK_DOWN:
            isWritingOption = 0;
            toggleInputWriting(menu, isWritingOption);
            menu->selectedMenuItem++;
            break;
        case SDLK_z:
            if (menu->nbInputs > menu->selectedMenuItem) {
                if (menu->isWriting && input->type == TEXT) {
                    break;
                }
            }
            __attribute__((fallthrough));  //Shows the compiler we know we will fall thoughout the next case
        case SDLK_UP:
            isWritingOption = 0;
            toggleInputWriting(menu, isWritingOption);
            menu->selectedMenuItem--;
            break;
        case SDLK_KP_ENTER: //Numpad
        case SDLK_RETURN:
            //Activate / deactive inputs
            if (scene->menu->nbInputs > scene->menu->selectedMenuItem) {
                toggleInputWriting(menu, 2);
            }
            break;
        case SDLK_BACKSPACE:
            if (scene->menu->isWriting) {
                Input* input = scene->menu->inputs[scene->menu->selectedMenuItem];
                int len = strlen(input->inputValue);
                if (len > 0) {
                    input->inputValue[len-1] = '\0';
                }
            }
            break;
    }

}

void keyHandlerCreationMenu(SDL_Keycode keyPressed, Scene* scene, Labyrinth* labyrinth) {
    keyHandlerMenuInputs(keyPressed, scene);
    switch (keyPressed) {
        case SDLK_KP_ENTER: //Numpad
        case SDLK_RETURN:
            //Behavior for validation/creation exit
            switch(scene->menu->selectedMenuItem) {
                case CREATION_MENU_VALIDATE:
                    validateLabyrinthCreation(scene, labyrinth);
                    break;
                case CREATION_MENU_EXIT:
                    scene->state = MAIN_MENU;
                    break;
            }
            break;
    }
}

void keyHandlerWon(SDL_KeyCode keyPressed, Scene* scene, Labyrinth* labyrinth) {
    keyHandlerMenuInputs(keyPressed, scene);
    switch(keyPressed) {
        case SDLK_KP_ENTER: //Numpad
        case SDLK_RETURN:
            switch(scene->menu->selectedMenuItem) {
                case WON_MENU_SAVE_LABYRINTH:
                    printf("Saving Labyrinth\n");
                    //if (!labyrinthExists(labyrinth->name)) {
                    saveLabyrinth(labyrinth);
                    //}
                    //saveScore(labyrinth);
                    scene->state = MAIN_MENU;
                    break;
            }
            break;
        default:
            break;
    }
}

void keyHandler(Scene* scene, SDL_Event* event, Labyrinth* labyrinth) {
    SDL_Keycode keyPressed = event->key.keysym.sym;
    switch(scene->state) {
        case MAIN_MENU:
            keyHandlerMainMenu(keyPressed, scene, labyrinth);
            break;
        case LABYRINTH_CREATION:
            keyHandlerCreationMenu(keyPressed, scene, labyrinth);
            break;
        case CREATING_LABYRINTH:
        case PLAYING:
            keyHandlerPlaying(keyPressed, scene, labyrinth);
            break;
        case PLAYER_WON:
            keyHandlerWon(keyPressed, scene, labyrinth);
            break;
        default:
            printf("Undefined behavior => State not handled");
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
    Menu sceneMenu;
    sceneMenu.selectedMenuItem = 0;
    sceneMenu.nbItems = 0;
    sceneMenu.isWriting = 0;
    sceneMenu.nbInputs = 0;
    scene.menu = &sceneMenu;
    scene.state = MAIN_MENU;

    //Labyrinth lab = newLabyrinth(5, 5, "Coucou");
    //saveLabyrinth(&lab);
    //chargeLabyrinth(&lab, "Coucou");
    //printf("Nom : %s\n", lab.name);

    Labyrinth currentLabyrinth;
    currentLabyrinth.tiles = NULL;
    currentLabyrinth.name = "";
    currentLabyrinth.height = 0;
    currentLabyrinth.width = 0;
    currentLabyrinth.playerColumn = 0;
    currentLabyrinth.playerRow = 0;
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
                    keyHandler(&scene, &event, &currentLabyrinth);
                    break;
                case SDL_TEXTINPUT:
                    if (scene.menu->isWriting) {
                        keyHandlerTextInput(scene.menu, &event);
                    }
                    break;
            }
        }
        display_scene(renderer, &scene, font, &currentLabyrinth);
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }
    

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}