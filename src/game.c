#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "labyrinth.h"
#include "game.h"

Labyrinth newLabyrinth() {
    int width = 0;
    int height = 0;

    while (width%2 != 1 && height%2 != 1) {
        printf("Vous allez générer un nouveau labyrinthe.\n");
        printf("Indiquer la largeur du labyrinthe (impaire uniquement):");
        scanf("%d", &width);
        printf("\n");
        printf("Indiquer la hauteur du labyrinthe (impaire uniquement):");
        scanf("%d", &height);
    }

    Labyrinth labyrinth = generateLabyrinth(width, height);
    return labyrinth;
}


void movePlayer(Labyrinth* labyrinth, char direction, int* playerRow, int* playerColumn, char* lastWalkedOn) {
    int nextR = *playerRow;
    int nextC = *playerColumn;
    if (direction == 'Z' || direction == 'z') {
        nextR -=1;
    } else if (direction == 'Q' || direction == 'q') {
        nextC-=1;
    } else if (direction == 'S' || direction == 's') {
        nextR +=1;
    } else if (direction == 'D' || direction == 'd') {
        nextC+=1;
    }
    if (nextC > 0 && nextR > 0 && nextC < labyrinth->height && nextR < labyrinth->width) {
        char nextTile = labyrinth->tiles[nextR][nextC].c;
        switch(nextTile) {
            case EMPTY:
                break;
            case WALL:
                return;
            case TRAP:
                labyrinth->score-=20;
                break;
            case TREASURE:
                labyrinth->score+=30;
                break;
            case KEY:
                labyrinth->keyFound = 1;
                break;
            case LOCKED_DOOR:
                if (!labyrinth->keyFound) {
                    printf("Vous n'avez pas récupéré la clé.\n");
                    return;
                }
                break;
            default:
                printf("comportement innatendu.\n");
            
        }
        labyrinth->score-=5;
        switch(*lastWalkedOn) {
            case TRAP:
                labyrinth->tiles[*playerRow][*playerColumn].c = TRAP;
                break;
            default:
                labyrinth->tiles[*playerRow][*playerColumn].c = EMPTY;
        }
        labyrinth->tiles[nextR][nextC].c = PLAYER;
        *playerRow = nextR;
        *playerColumn = nextC;
        *lastWalkedOn = nextTile;
        return;
    }
    printf("Direction impossible !\n");
}

void play(Labyrinth labyrinth) {
    int playerRow = 0;
    int playerColumn = 1;
    char dir = ' ';
    char lastWalkedOn = EMPTY;

    while(playerRow != labyrinth.height-1 && playerColumn != labyrinth.width-1) {
        showLabyrinth(labyrinth);

        printf("Que voulez faire ?\n");
        printf("Z: en haut\n");
        printf("Q: à ghauche\n");
        printf("S: en bas\n");
        printf("D: à droite\n");

        //empty the buffer
        char c;
        while ((c = getchar()) != '\n' && c != EOF); // vide jusqu'à fin de ligne

        scanf("%c", &dir);
        
        movePlayer(&labyrinth, dir, &playerRow, &playerColumn, &lastWalkedOn);
    }

    printf("\nVous avez gagné !\n\n");
}