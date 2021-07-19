CC = gcc
CFLAGS = -Wall -g
OBJ = main.c AuxFunctions.c AuxFunctions2.c Reads_frees.c
TARGET = main

build:
		$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

run:
		./$(TARGET)

clean:
		rm -f *.o $(TARGET) *~

valgrind:

		valgrind --leak-check=yes --track-origins=yes ./$(TARGET) books.in books.out
