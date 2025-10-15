#include "labyrinth.h"
#ifndef FILES_H
#define FILES_H

/** \brief Saves the Labyrinth
 * 
 * \param labyrinth The labyrinth to be saved
 * 
 * \return An error code: 0 if passed, -1 if an error has occured
 */
void saveLabyrinth(Labyrinth labyrinth);

/** \brief Charges the Labyrinth
 * 
 * \param labyrinth The address to charge the labyrinth
 */
void chargeLabyrinth(Labyrinth* Labyrinth);

#endif