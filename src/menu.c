#include <stdlib.h>
#include "menu.h"

void freeMenuItems(Menu* menu) {
    for (int i = 0; i < menu->nbItems; i++) {
        free(menu->items[i]);
    } 
    free(menu->items);
}

void verifyMenuSelection(Menu* menu) {
    if (menu->selectedMenuItem < 0) {
        menu->selectedMenuItem += menu->nbItems;
    }
    else if (menu->selectedMenuItem > (menu->nbItems)-1) {
        menu->selectedMenuItem = 0;
    }
}