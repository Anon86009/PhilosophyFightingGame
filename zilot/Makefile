CC=gcc
CXXFLAGS=-g -Wall -Wextra -lSDL2
EXEC=game
H=headers/
SRC=src/
B=build/

all: $(EXEC)

game: $(B)character.o $(B)fight.o $(B)main.o
	$(CC) -o philosopunch $(B)character.o $(B)fight.o $(B)main.o $(CXXFLAGS)

$(B)character.o: $(SRC)character.c
	$(CC) -o $(B)character.o -c $(SRC)character.c $(CXXFLAGS)

$(B)fight.o: $(SRC)fight.c
	$(CC) -o $(B)fight.o -c $(SRC)fight.c $(CXXFLAGS)

$(B)main.o: $(SRC)main.c
	$(CC) -o $(B)main.o -c $(SRC)main.c $(CXXFLAGS)

clean:
	rm -rf $(B)*.o

mrproper: clean
	rm -rf $(EXEC)
