#include "labyrinth.h"
#include "files.h"
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
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

void loadLabyrinth(Labyrinth* labyrinth, char* labyrinthName) {
    printf("Loading...\n");
    printf("Name : %s\n", labyrinthName);
    char filePath[100] = "mazes/";
    strcat(filePath, labyrinthName);
    strcat(filePath, ".cfg");
    printf("path : %s\n", filePath);
    FILE* file = fopen(filePath, "r+");
    fseek(file, 0, SEEK_SET);
    if (!file) {
        perror("Erreur ouverture fichier en lecture\n");
    }
    
    printf("File openned...\n");

    int height, width, score, keyFound, playerRow, playerColumn;
    char* buffer = malloc(50* sizeof(char));
    fread(&height, sizeof(int), 1, file);
    fread(&width, sizeof(int), 1, file);
    fread(&score, sizeof(int), 1, file);
    fread(&keyFound, sizeof(int), 1, file);
    fread(&playerRow, sizeof(int), 1, file);
    fread(&playerColumn, sizeof(int), 1, file);
    fread(buffer, sizeof(char), 50, file);
    
    printf("Basic informations retrieved ...\n");

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
    DIR* directory = opendir("mazes");
    struct dirent* entry;
    
    if (directory==NULL) {
        return;
    }

    *nbLabyrinth = 0;
    char** buffer = malloc(100* sizeof(char*));
    
    while((entry = readdir(directory)) != NULL) {
        char filePath[300];
        sprintf(filePath, "%s/%s", "mazes", entry->d_name);
        struct stat fileStat;
        stat(filePath, &fileStat);

        if (!S_ISDIR(fileStat.st_mode)) { //if its not a Directory
            size_t len = strlen(entry->d_name);
            size_t nameLen = len-4; //on retire .cfg
            buffer[*nbLabyrinth] = malloc(50 * sizeof(char));
            strcpy(buffer[*nbLabyrinth], entry->d_name); 
            buffer[*nbLabyrinth][nameLen] = '\0';
            (*nbLabyrinth)++;
        }
    }

    char** result = malloc(*nbLabyrinth * sizeof(char*));
    for(int i = 0; i < *nbLabyrinth; i++) {
        result[i] = malloc(50 * sizeof(char));
        strcpy(result[i], buffer[i]);
        free(buffer[i]);
    }
    free(buffer);

    return result;
}

void freeLabyrinthNames(char** labyrinthNames, int nbLabyrinth) {
    if (!labyrinthNames) {
        return;
    }
    for (int i = 0; i < nbLabyrinth; i++) {
        free(labyrinthNames[i]); 
    }
    free(labyrinthNames);
}

int labyrinthExists(char* labyrinthName) {
    char** labyrinthNames;
    int nbLabyrinth;
    labyrinthNames = getAllLabyrinthNames(&nbLabyrinth);
    for (int i = 0; i < nbLabyrinth; i++) {
        if (strcmp(labyrinthNames[i], labyrinthName)) {
            return 1;
        }
    }
    return 0;
}


void saveScore(Labyrinth* labyrinth, char* playerName) {

}