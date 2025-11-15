#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "labyrinth.h"


tile** allocateLabyrinthTiles(int width, int height) {
    //allocates the memory for the labyrinth
    tile** tiles = malloc(sizeof(tile*) * height);
    for (int i = 0; i < height; i++) {
        tile* line = malloc(sizeof(tile) * width);
        //Adds a '#' character to have a wall in each of the labyrinth box
        for (int j = 0; j < width; j++) {
            line[j].c = WALL;
            line[j].unionType = 1;
        }
        tiles[i] = line;
    }
    return tiles;
}

Labyrinth allocateLabyrinth(int width, int height, char* name) {
    Labyrinth labyrinth;
    labyrinth.name = malloc(sizeof(char*) * 50);
    strcpy(labyrinth.name, name);
    labyrinth.width = width;
    labyrinth.height = height;
    labyrinth.keyFound = 0;
    labyrinth.score = 0;
    labyrinth.playerRow = 0;
    labyrinth.playerColumn = 1;
    labyrinth.tiles = allocateLabyrinthTiles(width, height);
    return labyrinth;
}


void freeLabyrinth(Labyrinth* labyrinth) {
    if (!labyrinth || !labyrinth->tiles) return;

    for (int i = 0; i < labyrinth->height; i++) {
        free(labyrinth->tiles[i]);
    }
    free(labyrinth->tiles);
    labyrinth->height = 0;
    labyrinth->width = 0;
    labyrinth->keyFound = 0;
    labyrinth->score = 0;
    labyrinth->playerColumn = 0;
    labyrinth->playerRow = 0;
    labyrinth->tiles = NULL;
}

int getLine(Labyrinth* labyrinth, int identifier) {
    int nbPerLine = labyrinth->width/2;
    return (identifier/nbPerLine)*2 +1;
}

int getColumn(Labyrinth* labyrinth, int identifier) {
    int nbPerLine = labyrinth->width/2;
    return (identifier%nbPerLine)*2 +1;
}

int getIdentifier(Labyrinth* labyrinth, int line, int column) {
    int nbPerLine = labyrinth->width/2;
    return (line-1)/2*nbPerLine + (column-1)/2;
}

int getValue(Labyrinth* labyrinth, int line, int column) {
    return labyrinth->tiles[line][column].nb;
}

static int preparePathGrid(Labyrinth* labyrinth) {
    int nb = 0;
    for (int i = 1; i <= labyrinth->height-2; i+=2) {
        for(int j = 1; j <= labyrinth->width-2; j+=2) {
            labyrinth->tiles[i][j].nb = nb;
            labyrinth->tiles[i][j].unionType = 2;
            nb++;
        }
    }
    return nb;
}

static void link(Labyrinth* labyrinth, int originIdentifier, int destinationIdentifier) {

    tile ** tiles = labyrinth->tiles;

    int originLine = getLine(labyrinth, originIdentifier);
    int originColumn = getColumn(labyrinth, originIdentifier);
    int destinationLine = getLine(labyrinth, destinationIdentifier);
    int destinationColumn = getColumn(labyrinth, destinationIdentifier);

    int originValue = getValue(labyrinth, originLine, originColumn);
    int destinationValue = getValue(labyrinth, destinationLine, destinationColumn);

    //The linked tile gets the origin tile's value
    tiles[destinationLine][destinationColumn].nb = originValue;

    //We calculate the coords of the wall that is broken and sets his value to the origin tile's value
    int tileInBetweenLine = (destinationLine+originLine)/2;
    int tileInBetweenColumn = (destinationColumn+originColumn)/2;
    tiles[tileInBetweenLine][tileInBetweenColumn].nb = originValue;
    tiles[tileInBetweenLine][tileInBetweenColumn].unionType = 2;

    //check arrond the destination if it has neighbors and link them if so
    int nextDestIdentifier;
    tile neighbour;
    neighbour = tiles[destinationLine+1][destinationColumn];
    if (neighbour.unionType == 2 && neighbour.nb == destinationValue) {
        nextDestIdentifier = getIdentifier(labyrinth, destinationLine+2, destinationColumn);
        link(labyrinth, destinationIdentifier, nextDestIdentifier);
    }
    neighbour = tiles[destinationLine-1][destinationColumn];
    if (neighbour.unionType == 2 && neighbour.nb == destinationValue) {
        nextDestIdentifier = getIdentifier(labyrinth, destinationLine-2, destinationColumn);
        link(labyrinth, destinationIdentifier, nextDestIdentifier);
    }
    neighbour = tiles[destinationLine][destinationColumn+1];
    if (neighbour.unionType == 2 && neighbour.nb == destinationValue) {
        nextDestIdentifier = getIdentifier(labyrinth, destinationLine, destinationColumn+2);
        link(labyrinth, destinationIdentifier, nextDestIdentifier);
    }
    neighbour = tiles[destinationLine][destinationColumn-1];
    if (neighbour.unionType == 2 && neighbour.nb == destinationValue) {
        nextDestIdentifier = getIdentifier(labyrinth, destinationLine, destinationColumn-2);
        link(labyrinth, destinationIdentifier, nextDestIdentifier);
    }

}

void updatePossibilities(Labyrinth* labyrinth, int previousIdentifier, int checkedIdentifier, int possibilities[], int* remainingValidTiles) {

    tile** tiles = labyrinth->tiles;
    int line = getLine(labyrinth, checkedIdentifier);
    int column = getColumn(labyrinth, checkedIdentifier);
    int tileValue = getValue(labyrinth, line, column);

    int possible = 0;
    tile neighbour;
    int nextIdentifier;
    if (line-2 > 0) {
        if (tileValue != tiles[line-2][column].nb) {
            possible = 1;
        }
        else {
            neighbour = tiles[line-1][column];
            nextIdentifier = getIdentifier(labyrinth, line-2, column);
            if (neighbour.unionType == 2 && previousIdentifier != nextIdentifier) {
                updatePossibilities(labyrinth, checkedIdentifier, nextIdentifier, possibilities, remainingValidTiles);
            }
        }
    }
    if (line+2 < labyrinth->height-1) {
        if (tileValue != tiles[line+2][column].nb) {
            possible = 1;
        } else {
            neighbour = tiles[line+1][column];
            nextIdentifier = getIdentifier(labyrinth, line+2, column);
            if (neighbour.unionType == 2 && previousIdentifier != nextIdentifier) {
                updatePossibilities(labyrinth, checkedIdentifier, nextIdentifier, possibilities, remainingValidTiles);
            }
        }
    }
    if (column-2 > 0) {
        if (tileValue != tiles[line][column-2].nb) {
            possible = 1;
        }
        else {
            neighbour = tiles[line][column-1];
            nextIdentifier = getIdentifier(labyrinth, line, column-2);
            if (neighbour.unionType == 2 && previousIdentifier != nextIdentifier) {
                updatePossibilities(labyrinth, checkedIdentifier, nextIdentifier, possibilities, remainingValidTiles);
            }
        }
    }
    if (column+2 < labyrinth->width-1) {
        if (tileValue != tiles[line][column+2].nb) {
            possible = 1;
        }
        else {
            neighbour = tiles[line][column+1];
            nextIdentifier = getIdentifier(labyrinth, line, column+2);
            if (neighbour.unionType == 2 && previousIdentifier != nextIdentifier) {
                updatePossibilities(labyrinth, checkedIdentifier, nextIdentifier, possibilities, remainingValidTiles);
            }
        }
    }

    if (!possible) {
        int identifierPosition = -1;
        for (int i = 0; i < *remainingValidTiles; i++) {
            if (possibilities[i] == checkedIdentifier) {
                identifierPosition = i;
                break;
            }
        }
        //the tile was previously removed from the array
        if (identifierPosition == -1) {
            return;
        }

        for (int i = identifierPosition; i < *remainingValidTiles-1; i++) {
            possibilities[i] = possibilities[i+1];
        }
        *remainingValidTiles = *remainingValidTiles-1;
    }
}


static int chooseDirection(Labyrinth* labyrinth, int originIdentifier) {
    tile** tiles = labyrinth->tiles;

    int line = getLine(labyrinth, originIdentifier);
    int column = getColumn(labyrinth, originIdentifier);

    int originValue = tiles[line][column].nb;
    int nbPossibilities = 0;
    int possibleTiles[4][2];

    if (line-2 > 0) {
        if (originValue != tiles[line-2][column].nb) {
            //ajouter aux possibilités
            possibleTiles[nbPossibilities][0] = line-2;
            possibleTiles[nbPossibilities][1] = column;
            nbPossibilities++;
        }
    }
    if (line+2 < labyrinth->height-1) {

        if (originValue != tiles[line+2][column].nb) {
            //ajouter aux possibilités
            possibleTiles[nbPossibilities][0] = line+2;
            possibleTiles[nbPossibilities][1] = column;
            nbPossibilities++;
        }
    }
    if (column-2 > 0) {
        if (originValue != tiles[line][column-2].nb) {
            //ajouter aux possibilités
            possibleTiles[nbPossibilities][0] = line;
            possibleTiles[nbPossibilities][1] = column-2;
            nbPossibilities++;
        }
    }
    if (column+2 < labyrinth->width-1) {
        if (originValue != tiles[line][column+2].nb) {
            //ajouter aux possibilités
            possibleTiles[nbPossibilities][0] = line;
            possibleTiles[nbPossibilities][1] = column+2;
            nbPossibilities++;
        }
    }
    int direction = rand()%nbPossibilities;
    int destination = getIdentifier(labyrinth, possibleTiles[direction][0], possibleTiles[direction][1]);
        
    return destination;
}


static void createLabyrinthPaths(Labyrinth* labyrinth, int nbNumber) {
    int possibilities[nbNumber];
    for (int i = 0; i < nbNumber; i++) {
        possibilities[i] = i;
    }

    int remainingValidTiles = nbNumber;

    int originIdentifier, destinationIdentifier;
    while(remainingValidTiles != 0) {
        originIdentifier = possibilities[rand()%remainingValidTiles];
        destinationIdentifier = chooseDirection(labyrinth, originIdentifier);

        link(labyrinth, originIdentifier, destinationIdentifier);
        updatePossibilities(labyrinth, -1, originIdentifier, possibilities, &remainingValidTiles);
    }
}

static void prepareLabyrinth(Labyrinth* labyrinth) {

    tile** tiles = labyrinth->tiles;

    //place the Labyrinth's entrance
    tiles[0][1].c = EMPTY;

    //place the Labyrinth's exit
    tiles[labyrinth->height-1][labyrinth->width-2].c = LOCKED_DOOR;

    for (int i = 0; i < labyrinth->height-1; i++) {
        for (int j = 0; j < labyrinth->width-1; j++) {
            if (tiles[i][j].unionType == 2) {
                tiles[i][j].unionType = 1;
                tiles[i][j].c = EMPTY;
            }
        }
    }
}

static void addCollectibles(Labyrinth* labyrinth, char collectible, int nbCollectible, int force) {
    for (int i = 0; i < nbCollectible; i++) {
        int column = rand()%(labyrinth->width-2)+1;
        int line = rand()%(labyrinth->height-2)+1;

        if (labyrinth->tiles[line][column].c == EMPTY) {
            labyrinth->tiles[line][column].c = collectible;
        }
        else if (force) {
            i--;
        }
    }
}

static void setupCollectibles(Labyrinth* labyrinth) {
    addCollectibles(labyrinth, KEY, 1, 1);
    
    int nbTraps = labyrinth->height*labyrinth->width/20;
    addCollectibles(labyrinth, TRAP, nbTraps, 0);
    
    int nbCoins = labyrinth->height*labyrinth->width/10;
    addCollectibles(labyrinth, TREASURE, nbCoins, 0);
}

static void setBasicScore(Labyrinth* labyrinth) {
    labyrinth->score = labyrinth->width*labyrinth->height/2*5;
}

void showLabyrinth(Labyrinth labyrinth) {

    printf("\n");
    for (int i = 0; i < labyrinth.height; i++) {
        for (int j = 0; j < labyrinth.width; j++) {
            printf("%c ", labyrinth.tiles[i][j].c);
        }
        printf("\n");
    }
    printf("score: %d\n", labyrinth.score);
    printf("\n");
}

Labyrinth generateLabyrinth(int width, int height, char* name) {

    Labyrinth labyrinth = allocateLabyrinth(width, height, name);
    
    //the amount of different tile ids that are to be parsed
    int nbNumber = preparePathGrid(&labyrinth);

    createLabyrinthPaths(&labyrinth, nbNumber);

    prepareLabyrinth(&labyrinth);

    setupCollectibles(&labyrinth);

    setBasicScore(&labyrinth);

    return labyrinth;
}