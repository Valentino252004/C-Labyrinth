#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <files.h>
#include "menu.h"
#include "sdl.h"


void freeMenuItems(Menu* menu) {
    if (!menu || !menu->items) {
        return;
    }
    for (int i = 0; i < menu->nbItems; i++) {
        free(menu->items[i]);
    } 
    free(menu->items);
}

void allocateMenuItems(Menu* menu, int nbItems, int itemSize, state newState) {
    freeMenuItems(menu);
    menu->nbItems = nbItems;
    char ** menu_items = malloc(menu->nbItems * sizeof(char*));
    for(int i = 0; i < menu->nbItems; i++) {
        menu_items[i] = malloc(itemSize * sizeof(char));
    }
    menu->items = menu_items;
    menu->state = newState;
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

void allocateMenuInputs(Menu* menu, int nbInputs, int inputSize) {
    freeMenuInputs(menu);
    menu->nbInputs = nbInputs;
    menu->inputs = malloc(menu->nbInputs * sizeof(Input*));
    for (int i = 0; i < menu->nbInputs; i++) {
        menu->inputs[i] = malloc(sizeof(Input));
        menu->inputs[i]->inputValue = malloc(inputSize * sizeof(char));
        strcpy(menu->inputs[i]->inputValue, "");
    }
}


void verifyMenuSelection(Menu* menu) {
    if (menu->selectedMenuItem < 0) {
        menu->selectedMenuItem += menu->nbItems;
    }
    else if (menu->selectedMenuItem > (menu->nbItems)-1) {
        menu->selectedMenuItem = 0;
    }
}

void setMainMenuFields(Menu* menu, state sceneState) {
    if (menu->state != sceneState) {
        allocateMenuItems(menu, 4, 50, sceneState);
        menu->nbInputs = 0;
        strcpy(menu->items[0], "Générer un nouveau labyrinthe");
        strcpy(menu->items[1], "Charger un labyrinthe");
        strcpy(menu->items[2], "Afficher le classement (WIP)");
        strcpy(menu->items[3], "Quitter");
    }

    verifyMenuSelection(menu);
}

void setCreationMenuFields(Menu* menu, state sceneState) {
    if (menu->state != sceneState) {
        allocateMenuItems(menu, 5, 50, sceneState);
        strcpy(menu->items[3], "Valider");
        strcpy(menu->items[4], "Quitter");

        allocateMenuInputs(menu, 3, 50);
        menu->inputs[0]->type = TEXT;
        menu->inputs[1]->type = NUMBER;
        menu->inputs[2]->type = NUMBER;
    }
    sprintf(menu->items[0], "Nom: %s", menu->inputs[0]->inputValue);
    sprintf(menu->items[1], "Largeur: %s", menu->inputs[1]->inputValue);
    sprintf(menu->items[2], "Hauteur: %s", menu->inputs[2]->inputValue);

    verifyMenuSelection(menu);
}

void setCreatingLabyrinthMenuFields(Menu* menu, state sceneState) {
    if (menu->state != sceneState) {
        printf("allocating Items\n");
        allocateMenuItems(menu, 1, 50, sceneState);
    }
    menu->nbInputs = 0;
    strcpy(menu->items[0], "Création du labyrinthe ...");

    verifyMenuSelection(menu);
}

void setPlayerWonMenuFields(Menu* menu, state sceneState) {
    if (menu->state != sceneState) {
        allocateMenuItems(menu, 2, 70, sceneState);
        strcpy(menu->items[1], "Enregistrer le Labyrinthe");
        allocateMenuInputs(menu, 1, 50);
        menu->inputs[0]->type = TEXT;
    }

    sprintf(menu->items[0], "Nom du joueur: %s", menu->inputs[0]->inputValue);
    verifyMenuSelection(menu);
}

void setupMenuLoadingFields(Menu* menu, state sceneState) {
    if (menu->state != sceneState) {
        char** labyrinthNames;
        int nbLabyrinth;
        labyrinthNames = getAllLabyrinthNames(&nbLabyrinth);
        allocateMenuItems(menu, nbLabyrinth+1, 50, sceneState);

        menu->nbInputs = 0;

        for (int i = 0; i < nbLabyrinth; i++) {
            strcpy(menu->items[i], labyrinthNames[i]);
        }
        strcpy(menu->items[menu->nbItems-1], "Retour");

        freeLabyrinthNames(labyrinthNames, nbLabyrinth);
    }

    verifyMenuSelection(menu);
}