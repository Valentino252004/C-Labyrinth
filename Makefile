CC=gcc
CFLAGS=-Wall -Wextra -pedantic
CPPFLAGS=-I$(INCLUDES)
SRC=src/
BIN=bin/
INCLUDES=includes
MAIN_OFILES=$(SRC)labyrinth.o $(SRC)menu.o $(SRC)game.o $(SRC)files.o
SDL_LIBS=-lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf

.PHONY: labyrinth clean distclean

all: labyrinth clean

labyrinth: main.o $(MAIN_OFILES)
	$(CC) $(CFLAGS) $^ -o $(BIN)labyrinth $(SDL_LIBS)

$(SRC)%.o : $(SRC)%.c $(INCLUDES)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@


clean:
	del /Q *.o src\*.o
	
distclean:
	del /Q *.o src\*.o bin\*
