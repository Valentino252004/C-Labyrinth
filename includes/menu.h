#ifndef MENU_H
#define MENU_H

typedef enum mainMenuActions { MAIN_MENU_NEW_LABYRINTH, MAIN_MENU_CHARGE_LABYRINTH, MAIN_MENU_RANKING, MAIN_MENU_EXIT } mainMenuActions;

typedef struct {
    char** items;
    int selectedMenuItem;
    int nbItems;
} Menu;

void freeMenuItems(Menu* menu);
void verifyMenuSelection(Menu* menu);

#endif