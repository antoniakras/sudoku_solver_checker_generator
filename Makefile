CC=gcc
CFLAGS= -ansi -pedantic -Wall

all: sudoku

sudoku: grid.o sudoku.o
	$(CC) $(OFLAGS)  grid.o sudoku.c -o sudoku

sudoku.o : sudoku.c  sudoku.h
	$(CC) $(CFLAGS) -c grid.c 

grid.o: grid.c grid.h
	$(CC) $(CFLAGS) -c grid.c 

clean:
	-rm *.o sudoku


