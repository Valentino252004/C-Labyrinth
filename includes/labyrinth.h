#ifndef LABYRINTH_H
#define LABYRINTH_H

typedef struct {
    union {
        int nb;
        char c;
    };
    int unionType;
} tile;


typedef struct {
    tile** tiles;
    int height;
    int width;
    int keyFound;
    int score;
} Labyrinth;


/** \brief generates a perfect labyrinth
 * 
 * \param width The width of the labyrinth
 * \param height The height of the labyrinth
 * 
 * \return the newly generated labyrinth
 */
Labyrinth generateLabyrinth(int width, int height);

/** \brief prints the given labyrinth in console
 * 
 * \param labyrinth the labyrinth to be printed
 * 
 * \return the newly generated labyrinth
 */
void showLabyrinth(Labyrinth labyrinth);

/** \brief the action the user will perform
 * 
 * \param loaded Specifies if a labyrinth is currently loaded
 * \param exitIndex A pointer that tells the calling function the index for the exit
 * 
 * \return The code of the action
 */
char* chooseAction(int loaded);

/** \brief Launches the game's menu
 * 
 */
void startGame();

/** \brief allow the user to create a new labyrinth
 * 
 */
Labyrinth newLabyrinth();

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

Labyrinth allocateLabyrinth(int width, int height);

void freeLabyrinth(Labyrinth* labyrinth);

void playLabyrinth(Labyrinth labyrinth);

#endif