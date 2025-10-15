CC=gcc
CPPFLAGS=-I$(INCLUDES)
SRC=src/
BIN=bin/
INCLUDES=includes
MAIN_OFILES=$(SRC)labyrinth.o $(SRC)mazeMenu.o $(SRC)game.o $(SRC)files.o $(SRC)sdl.o
SDL_LIBS = $(shell pkg-config --libs sdl2 SDL2_image SDL2_ttf)
SDL_CFLAGS = $(shell pkg-config --cflags sdl2 SDL2_image SDL2_ttf)
CFLAGS=-Wall -Wextra -pedantic $(SDL_CFLAGS)
LDFLAGS = $(SDL_LIBS)

.PHONY: labyrinth clean distclean

all: labyrinth clean

%/:
	mkdir -p $@  

labyrinth: main.o $(MAIN_OFILES) | $(BIN)
	$(CC) $(CFLAGS) $^ -o $(BIN)labyrinth $(LDFLAGS)

$(SRC)%.o : $(SRC)%.c $(INCLUDES) | $(SRC)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@


clean:
	rm -f *.o src/*.o
	
distclean:
	rm -f *.o src/*.o bin/*
