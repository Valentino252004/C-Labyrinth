#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "menu.h"

void freeMenuItems(Menu* menu) {
    if (!menu || !menu->items) {
        return;
    }
    for (int i = 0; i < menu->nbItems; i++) {
        free(menu->items[i]);
    } 
    free(menu->items);
}


void freeMenuInputs(Menu* menu) {
    if (!menu || !menu->inputs) {
        return;
    }
    for (int i = 0; i < menu->nbInputs; i++) {
        free(menu->inputs[i]);
    } 
    free(menu->inputs);
}

void verifyMenuSelection(Menu* menu) {
    if (menu->selectedMenuItem < 0) {
        menu->selectedMenuItem += menu->nbItems;
    }
    else if (menu->selectedMenuItem > (menu->nbItems)-1) {
        menu->selectedMenuItem = 0;
    }
}

void setMainMenuFields(Menu* menu) {
    menu->nbItems = 4;
    menu->nbInputs = 0;
    char ** menu_items = malloc(menu->nbItems * sizeof(char*));
    for(int i = 0; i < menu->nbItems; i++) {
        menu_items[i] = malloc(50 * sizeof(char));
    }
    strcpy(menu_items[0], "Générer un nouveau labyrinthe");
    strcpy(menu_items[1], "Charger un labyrinthe");
    strcpy(menu_items[2], "Afficher le classement (WIP)");
    strcpy(menu_items[3], "Quitter");

    menu->items = menu_items;
    verifyMenuSelection(menu);
}

void setupMenuCreationInputs(Menu* menu) {
    freeMenuInputs(menu);
    menu->nbInputs = 3;
    menu->inputs = malloc(menu->nbInputs * sizeof(char *));
    for (int i = 0; i < menu->nbInputs; i++) {
        menu->inputs[i] = malloc(50 * sizeof(char));
        strcpy(menu->inputs[i], "");
    }
}

void setCreationMenuFields(Menu* menu) {
    menu->nbItems = 5;
    char ** menu_items = malloc(menu->nbItems * sizeof(char*));
    for(int i = 0; i < menu->nbItems; i++) {
        menu_items[i] = malloc(50 * sizeof(char));
    }
    sprintf(menu_items[0], "Nom: %s", menu->inputs[0]);
    sprintf(menu_items[1], "Largeur: %s", menu->inputs[1]);
    sprintf(menu_items[2], "Hauteur: %s", menu->inputs[2]);
    strcpy(menu_items[3], "Valider");
    strcpy(menu_items[4], "Quitter");

    menu->items = menu_items;
    verifyMenuSelection(menu);
}