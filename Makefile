# -*-Makefile-*-

CC=gcc
FLAGS= -lGLEW -lglut -lGL

all: main

main: main.o CoppLoader.o
	$(CC) main.o CoppLoader.o $(FLAGS) -o app.bin

main.o: main.c
	$(CC) main.c $(FLAGS) -c -o main.o

CoppLoader.o: CoppLoader.c
	$(CC) CoppLoader.c $(FLAGS) -c -o CoppLoader.o

clean:
	rm -f *.o *.bin
