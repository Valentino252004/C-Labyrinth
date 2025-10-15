#ifndef MENU_H
#define MENU_H

#include <SDL2/SDL.h>

/** \brief the action the user will perform
 * 
 * \param loaded Specifies if a labyrinth is currently loaded
 * 
 * \return The code of the action
 */
char *chooseAction(int loaded);

/** \brief Launches the game's menu
 * 
 */
void startGame();

#endif