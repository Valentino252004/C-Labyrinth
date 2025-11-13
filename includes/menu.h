#ifndef MENU_H
#define MENU_H

typedef enum mainMenuActions { MAIN_MENU_LABYRINTH_CREATION, MAIN_MENU_CHARGE_LABYRINTH, MAIN_MENU_RANKING, MAIN_MENU_EXIT } mainMenuActions;

typedef struct {
    char** inputs;
    char** items;
    int selectedMenuItem;
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