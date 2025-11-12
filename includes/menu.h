#ifndef MENU_H
#define MENU_H

typedef struct {
    char** items;
    int selectedMenuItem;
    int nbItems;
} Menu;

void freeMenu(Menu* menu);
void verifyMenuSelection(Menu* menu);

#endif