#include "labyrinth.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void saveInFile(Labyrinth labyrinth, char* labyrinthName) {
    printf("création\n");
    char filePath[100] = "fichiers/";
    strcat(filePath, labyrinthName);
    strcat(filePath, ".cfg");
    FILE* file = fopen(filePath, "w+");

    fwrite(&labyrinth.height, sizeof(int), 1, file);
    fwrite(&labyrinth.width, sizeof(int), 1, file);
    
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
    char filePath[100] = "fichiers/";
    strcat(filePath, labyrinthName);
    strcat(filePath, ".cfg");

    FILE* file = fopen(filePath, "r+");
    fseek(file, 0, SEEK_SET);
    if (!file) {
        perror("Erreur ouverture fichier en lecture");
    }

    int height, width;
    fread(&height, sizeof(int), 1, file);
    fread(&width, sizeof(int), 1, file);
    
    if (labyrinth != NULL) {
        printf("%d %d\n", labyrinth->height, labyrinth->width);
        freeLabyrinth(labyrinth);
    }
    *labyrinth = allocateLabyrinth(width, height);

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