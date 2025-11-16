#ifndef MENU_H
#define MENU_H
#include "enums.h"

typedef enum mainMenuActions { 
    MAIN_MENU_LABYRINTH_CREATION, 
    MAIN_MENU_LOAD_LABYRINTH, 
    MAIN_MENU_RANKING, 
    MAIN_MENU_EXIT 
} mainMenuActions;

typedef enum creationMenuActions { 
    CREATION_MENU_NAME_INPUT, 
    CREATION_MENU_WIDTH_INPUT, 
    CREATION_MENU_HEIGHT_INPUT, 
    CREATION_MENU_VALIDATE,
    CREATION_MENU_EXIT
} creationMenuActions;

typedef enum wonMenuActions { 
    WON_MENU_NAME_INPUT, 
    WON_MENU_SAVE_LABYRINTH
} wonMenuActions;

typedef enum inputType {
    TEXT,
    NUMBER
} inputType;

typedef struct {
    char* inputValue;
    inputType type;
} Input;

typedef struct {
    state state;
    Input** inputs;
    char** items;
    int selectedMenuItem;
    int isWriting;
    int nbInputs;
    int nbItems;
} Menu;

void freeMenuItems(Menu* menu);
void allocateMenuItems(Menu* menu, int nbItems, int itemSize, state newState);

void freeInput(Input* input);
void freeMenuInputs(Menu* menu);
void allocateMenuInputs(Menu* menu, int nbInputs, int inputSize);

void verifyMenuSelection(Menu* menu);

void setMainMenuFields(Menu* menu, state sceneState);
void setCreationMenuFields(Menu* menu, state sceneState);
void setPlayerWonMenuFields(Menu* menu, state sceneState);
void setupMenuLoadingFields(Menu* menu, state sceneState);

#endif