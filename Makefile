# constans
SHELL = /bin/sh
SRC = source/
TARGET = bin/

CC = gcc
CFLAGS = -Wall --pedantic

# modes
all: clean server client

clean:
	rm -rf ${TARGET}*.o

client:
	${CC} ${CFLAGS} ${SRC}klientTCP.c -o ${TARGET}klientTCP.o

server:
	${CC} ${CFLAGS} ${SRC}serwerTCP.c -o ${TARGET}serwerTCP.o

