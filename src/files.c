#include "labyrinth.h"
#include "files.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void saveInFile(Labyrinth labyrinth, char* labyrinthName) {
    char filePath[100] = "mazes/";
    strcat(filePath, labyrinthName);
    strcat(filePath, ".cfg");
    FILE* file = fopen(filePath, "w+");

    fwrite(&labyrinth.height, sizeof(int), 1, file);
    fwrite(&labyrinth.width, sizeof(int), 1, file);
    fwrite(&labyrinth.score, sizeof(int), 1, file);
    fwrite(&labyrinth.keyFound, sizeof(int), 1, file);
    fwrite(&labyrinth.playerRow, sizeof(int), 1, file);
    fwrite(&labyrinth.playerColumn, sizeof(int), 1, file);
    
    for (int i = 0; i < labyrinth.height; i++) {
        fwrite(labyrinth.tiles[i], sizeof(tile), labyrinth.width, file);
    }
    fclose(file);
}

void saveLabyrinth(Labyrinth labyrinth) {
    char labyrinthName[50];
    printf("Entrez le nom de la sauvegarde : ");
    scanf("%49s", labyrinthName);
    saveInFile(labyrinth, labyrinthName);
}

static void readFile(Labyrinth* labyrinth, char* labyrinthName) {
    char filePath[100] = "mazes/";
    strcat(filePath, labyrinthName);
    strcat(filePath, ".cfg");
    FILE* file = fopen(filePath, "r+");
    fseek(file, 0, SEEK_SET);
    if (!file) {
        perror("Erreur ouverture fichier en lecture");
    }

    int height, width, score, keyFound, playerRow, playerColumn;
    fread(&height, sizeof(int), 1, file);
    fread(&width, sizeof(int), 1, file);
    fread(&score, sizeof(int), 1, file);
    fread(&keyFound, sizeof(int), 1, file);
    fread(&playerRow, sizeof(int), 1, file);
    fread(&playerColumn, sizeof(int), 1, file);
    
    if (labyrinth != NULL) {
        freeLabyrinth(labyrinth);
    }
    *labyrinth = allocateLabyrinth(width, height);
    labyrinth->score = score;
    labyrinth->keyFound = keyFound;
    labyrinth->playerRow = playerRow;
    labyrinth->playerColumn = playerColumn;

    for(int i = 0; i < labyrinth->height; i++) {
        fread(labyrinth->tiles[i], sizeof(tile), labyrinth->width, file);
    }

    fclose(file);
}

void chargeLabyrinth(Labyrinth* labyrinth) {
    char labyrinthName[50];
    printf("Entrez le nom de la sauvegarde : ");
    scanf("%49s", labyrinthName);
    readFile(labyrinth, labyrinthName);
}