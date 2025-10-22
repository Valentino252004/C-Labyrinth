#ifndef GAME_H
#define GAME_H
#include "labyrinth.h"


void play(Labyrinth labyrinth);

void movePlayer(Labyrinth* labyrinth, int nextR, int nextC);

/** \brief allow the user to create a new labyrinth
 * 
 */
Labyrinth newLabyrinth();

#endif