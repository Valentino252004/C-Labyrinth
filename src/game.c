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
