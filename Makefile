# makefile for C compilation

CC = gcc
TARGET = os-hell
all: 
	$(CC) Simple-Shell.c Interface.c -o $(TARGET)

clean:
	rm *.o $(TARGET)
