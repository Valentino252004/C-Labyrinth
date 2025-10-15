#include "labyrinth.h"
#include "files.h"
#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* chooseAction(int loaded) {
    int index = 0;
    char** choices = malloc(5 * sizeof(char*));
    printf("Que voulez-vous faire ?\n");
    choices[index] = "generate";
    printf("%d: Créer un labyrinthe\n", ++index);
    choices[index] = "charge";
    printf("%d: charger un labyrinthe\n", ++index);
    if (loaded) {
        choices[index] = "save";
        printf("%d: Sauvegarder le labyrinthe\n", ++index);
    }
    choices[index] = "play";
    printf("%d: Jouer\n", ++index);
    choices[index] = "exit";
    printf("%d: quitter\n", ++index);
    printf("Votre choix [1-%d] : ", index);
    int choice;
    scanf("%d", &choice);

    char* action = choices[choice-1];
    free(choices);

    return action;
}

void startGame() {
    char* action = "";
    Labyrinth currentLabyrinth;
    currentLabyrinth.tiles = NULL;
    currentLabyrinth.height = 0;
    currentLabyrinth.width = 0;
    int loaded = 0;
    //TODO system("clear");
    while(strcmp((action = chooseAction(loaded)), "exit") != 0) {
        printf("action: %s\n", action);

        if (strcmp(action, "generate") == 0) {
            freeLabyrinth(&currentLabyrinth);
            currentLabyrinth = newLabyrinth();
            printf("Votre labyrinth: ");
            showLabyrinth(currentLabyrinth);
            loaded = 1;
        }

        if (strcmp(action, "charge") == 0) {
            chargeLabyrinth(&currentLabyrinth);
            printf("Le labyrinthe chargé :");
            showLabyrinth(currentLabyrinth);
        }

        if (strcmp(action, "save") == 0) {
            saveLabyrinth(currentLabyrinth);
        }
        
        if (strcmp(action, "play") == 0) {
            play(currentLabyrinth);
        }
    }

    freeLabyrinth(&currentLabyrinth);
} 