#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <windows.h>
#include "labyrinth.h"

int main (void) { 

    WIN32_FIND_DATA findData;
    HANDLE hFind = FindFirstFile(".\\fichiers\\*", &findData);

    if (hFind == INVALID_HANDLE_VALUE) {
        printf("Erreur ouverture dossier\n");
        return 1;
    }

    printf("Contenu du dossier :\n");
    do {
        printf("- %s\n", findData.cFileName);
    } while (FindNextFile(hFind, &findData));

    FindClose(hFind);

    //setup a random seed;
    srand(time(NULL));
    //test seed
    //srand(0);

    startGame();

    return 0; 

}