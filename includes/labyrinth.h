#ifndef LABYRINTH_H
#define LABYRINTH_H

typedef enum tileType { WALL='#', EMPTY=' ', TREASURE='C', TRAP='T', KEY='K', LOCKED_DOOR='L', PLAYER='o' } tileType;

typedef struct {
    union {
        int nb;
        char c;
    };
    int unionType;
} tile;

typedef struct {
    char* playerName;
    int score;
} Score;

typedef struct {
    tile** tiles;
    Score scores[10];
    char* name;
    int height;
    int width;
    int keyFound;
    int score;
    int playerRow;
    int playerColumn;
} Labyrinth;

/** \brief generates a perfect labyrinth
 * 
 * \param width The width of the labyrinth
 * \param height The height of the labyrinth
 * 
 * \return the newly generated labyrinth
 */
Labyrinth generateLabyrinth(int width, int height, char* name);

/** \brief prints the given labyrinth in console
 * 
 * \param labyrinth the labyrinth to be printed
 * 
 * \return the newly generated labyrinth
 */
void showLabyrinth(Labyrinth labyrinth);

Labyrinth allocateLabyrinth(int width, int height, char* name);

void freeLabyrinth(Labyrinth* labyrinth);

#endif