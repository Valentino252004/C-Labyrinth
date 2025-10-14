CC=gcc
CFLAGS=-Wall -Wextra -pedantic
CPPFLAGS=-I$(INCLUDES)
SRC=src/
INCLUDES=includes/
MAIN_OFILES=$(SRC)labyrinth.o $(SRC)menu.o $(SRC)game.o $(SRC)files.o


all: labyrinth clean

labyrinth: main.o $(MAIN_OFILES)
	$(CC) $(CFLAGS) $^ -o labyrinth

main.o: main.c $(INCLUDES)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $<

$(SRC)%.o : $(SRC)%.c $(INCLUDES) # ajoût des fichier entêtes
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@


clean:
	del /Q *.o src\*.o