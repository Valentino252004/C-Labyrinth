#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "labyrinth.h"
#include "game.h"

Labyrinth newLabyrinth(int width, int height, char* name) {

    Labyrinth labyrinth = generateLabyrinth(width, height, name);

    return labyrinth;
}


void movePlayer(Labyrinth* labyrinth, int nextR, int nextC) {

    switch(labyrinth->tiles[nextR][nextC].c) {
        case WALL:
            return;
        case EMPTY:
            labyrinth->score-=5;
            break;
        case TRAP:
            labyrinth->score-=25;
            break;
        case TREASURE:
            labyrinth->score +=50;
            labyrinth->tiles[nextR][nextC].c = EMPTY;
            break;
        case KEY:
            labyrinth->score +=100;
            labyrinth->keyFound = 1;
            labyrinth->tiles[nextR][nextC].c = EMPTY;
            break;
        case LOCKED_DOOR:
            if (!labyrinth->keyFound) {
                return;
            }
            break;
        default:
            printf("movePlayer - Undefined Behavior");
    }
    labyrinth->playerColumn = nextC;
    labyrinth->playerRow = nextR;
}

int hasPlayerWon(Labyrinth* labyrinth) {
    if (labyrinth->playerRow == labyrinth->height-1 && labyrinth->playerColumn == labyrinth->width-2) {
        return 1;
    }
    return 0;
}

/*
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
}*/


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
        
        //movePlayer(&labyrinth, dir, &playerRow, &playerColumn, &lastWalkedOn);
    }

    printf("\nVous avez gagné !\n\n");
}