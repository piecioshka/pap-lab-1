# constans
SHELL = /bin/sh
SRC = source/
TARGET = bin/

CC = gcc
CFLAGS = -c -Wall --pedantic

# modes
all: server client

client:
	${CC} ${CFLAGS} ${SRC}klientTCP.c -o ${TARGET}klientTCP

server:
	${CC} ${CFLAGS} ${SRC}serwerTCP.c -o ${TARGET}serwerTCP

