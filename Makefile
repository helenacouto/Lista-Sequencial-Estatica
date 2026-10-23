CC = gcc
CFLAGS = -Wall -Wextra -std=c11

all: programa

programa: main.o ListaSequencial.o
	$(CC) $(CFLAGS) -o programa main.o ListaSequencial.o

main.o: main.c ListaSequencial.h
	$(CC) $(CFLAGS) -c main.c

ListaSequencial.o: ListaSequencial.c ListaSequencial.h
	$(CC) $(CFLAGS) -c ListaSequencial.c

clean:
	rm -f *.o programa
