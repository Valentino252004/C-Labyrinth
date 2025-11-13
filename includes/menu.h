#ifndef MENU_H
#define MENU_H

typedef enum mainMenuActions { 
    MAIN_MENU_LABYRINTH_CREATION, 
    MAIN_MENU_CHARGE_LABYRINTH, 
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

typedef struct {
    char** inputs;
    char** items;
    int selectedMenuItem;
    int isWriting;
    int nbInputs;
    int nbItems;
} Menu;

void setMainMenuFields(Menu* menu);
void freeMenuItems(Menu* menu);
void verifyMenuSelection(Menu* menu);

void setupMenuCreationInputs(Menu* menu);
void setCreationMenuFields(Menu* menu);
void freeMenuInputs(Menu* menu);

#endif