#include "labyrinth.h"
#include "files.h"
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <stdio.h>

void saveLabyrinth(Labyrinth* labyrinth) {
    char filePath[100] = "mazes/";
    strcat(filePath, labyrinth->name);
    strcat(filePath, ".cfg");
    FILE* file = fopen(filePath, "w+");

    fwrite(&labyrinth->height, sizeof(int), 1, file);
    fwrite(&labyrinth->width, sizeof(int), 1, file);
    fwrite(&labyrinth->score, sizeof(int), 1, file);
    fwrite(&labyrinth->keyFound, sizeof(int), 1, file);
    fwrite(&labyrinth->playerRow, sizeof(int), 1, file);
    fwrite(&labyrinth->playerColumn, sizeof(int), 1, file);
    fwrite(labyrinth->name, sizeof(char), 50, file);
    
    for (int i = 0; i < 10; i++) {
        fwrite(labyrinth->scores[i].playerName, sizeof(char), 50, file);
        fwrite(&labyrinth->scores[i].score, sizeof(int), 1, file);
    }
    
    for (int i = 0; i < labyrinth->height; i++) {
        fwrite(labyrinth->tiles[i], sizeof(tile), labyrinth->width, file);
    }
    fclose(file);
}

void chargeLabyrinth(Labyrinth* labyrinth, char* labyrinthName) {
    char filePath[100] = "mazes/";
    strcat(filePath, labyrinthName);
    strcat(filePath, ".cfg");
    FILE* file = fopen(filePath, "r+");
    fseek(file, 0, SEEK_SET);
    if (!file) {
        perror("Erreur ouverture fichier en lecture");
    }
    

    int height, width, score, keyFound, playerRow, playerColumn;
    char* buffer = malloc(50* sizeof(char));
    fread(&height, sizeof(int), 1, file);
    fread(&width, sizeof(int), 1, file);
    fread(&score, sizeof(int), 1, file);
    fread(&keyFound, sizeof(int), 1, file);
    fread(&playerRow, sizeof(int), 1, file);
    fread(&playerColumn, sizeof(int), 1, file);
    fread(buffer, sizeof(char), 50, file);
    
    if (labyrinth != NULL) {
        freeLabyrinth(labyrinth);
    }
    labyrinth->score = score;
    labyrinth->keyFound = keyFound;
    labyrinth->playerRow = playerRow;
    labyrinth->playerColumn = playerColumn;
    strcpy(labyrinth->name, buffer);

    for (int i = 0; i < 10; i++) {
        fread(buffer, sizeof(char), 50, file);
        strcpy(labyrinth->scores[i].playerName, buffer);
        fread(&labyrinth->scores[i].score, sizeof(int), 1, file);
    }

    for(int i = 0; i < labyrinth->height; i++) {
        fread(labyrinth->tiles[i], sizeof(tile), labyrinth->width, file);
    }

    fclose(file);
}

char** getAllLabyrinthNames(int* nbLabyrinth) {
    DIR* directory = opendir("/mazes");
    struct dirent* entry;

    if (directory==NULL) {
        printf("t nul\n");
        return;
    }
    printf("t cool\n");
}

