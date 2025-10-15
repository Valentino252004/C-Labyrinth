#include "labyrinth.h"
#ifndef GAME_H
#define GAME_H


void play(Labyrinth labyrinth);

void movePlayer(Labyrinth* labyrinth, char direction, int* playerRow, int* playerColumn, char* lastWalkedOn);

/** \brief allow the user to create a new labyrinth
 * 
 */
Labyrinth newLabyrinth();

#endif