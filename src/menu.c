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

void freeInput(Input* input) {
    if (!input->inputValue) {
        return;
    }
    free(input->inputValue);
}


void freeMenuInputs(Menu* menu) {
    if (!menu || !menu->inputs || menu->nbInputs == 0) {
        return;
    }
    for (int i = 0; i < menu->nbInputs; i++) {
        freeInput(menu->inputs[i]);
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
    menu->inputs = malloc(menu->nbInputs * sizeof(Input*));
    for (int i = 0; i < menu->nbInputs; i++) {
        menu->inputs[i] = malloc(sizeof(Input));
        menu->inputs[i]->inputValue = malloc(50 * sizeof(char));
        strcpy(menu->inputs[i]->inputValue, "");
    }
    menu->inputs[0]->type = TEXT;
    menu->inputs[1]->type = NUMBER;
    menu->inputs[2]->type = NUMBER;
}

void setupMenuWonInputs(Menu* menu) {
    freeMenuInputs(menu);
    menu->nbInputs = 1;
    menu->inputs = malloc(menu->nbInputs * sizeof(Input*));
    for (int i = 0; i < menu->nbInputs; i++) {
        menu->inputs[i] = malloc(sizeof(Input));
        menu->inputs[i]->inputValue = malloc(50 * sizeof(char));
        strcpy(menu->inputs[i]->inputValue, "");
    }
    menu->inputs[0]->type = TEXT;
}

void setCreationMenuFields(Menu* menu) {
    menu->nbItems = 5;
    char ** menu_items = malloc(menu->nbItems * sizeof(char*));
    for(int i = 0; i < menu->nbItems; i++) {
        menu_items[i] = malloc(50 * sizeof(char));
    }
    sprintf(menu_items[0], "Nom: %s", menu->inputs[0]->inputValue);
    sprintf(menu_items[1], "Largeur: %s", menu->inputs[1]->inputValue);
    sprintf(menu_items[2], "Hauteur: %s", menu->inputs[2]->inputValue);
    strcpy(menu_items[3], "Valider");
    strcpy(menu_items[4], "Quitter");
    menu->items = menu_items;
    verifyMenuSelection(menu);
}

void setCreatingLabyrinthMenuFields(Menu* menu) {
    menu->nbItems = 1;
    char ** menu_items = malloc(menu->nbItems * sizeof(char*));
    for(int i = 0; i < menu->nbItems; i++) {
        menu_items[i] = malloc(50 * sizeof(char));
    }
    strcpy(menu_items[0], "Création du labyrinthe ...");
    menu->items = menu_items;
    verifyMenuSelection(menu);
}

void setPlayerWonMenu(Menu* menu) {
    menu->nbItems = 3;
    char ** menu_items = malloc(menu->nbItems * sizeof(char*));
    for(int i = 0; i < menu->nbItems; i++) {
        menu_items[i] = malloc(70 * sizeof(char));
    }
    sprintf(menu_items[0], "Nom du joueur: %s", menu->inputs[0]->inputValue);
    strcpy(menu_items[1], "Enregister le score");
    strcpy(menu_items[2], "Enregistrer le Labyrinthe");
    menu->items = menu_items;
    verifyMenuSelection(menu);
}