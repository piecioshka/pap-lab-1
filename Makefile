CC = gcc
CFLAGS = -Wall --pedantic
TARGET = bin/
SRC = source/

zad5:
	${CC} ${CFLAGS} ${SRC}$@/klientTCP.c -o ${TARGET}$@/klientTCP.o
	${CC} ${CFLAGS} ${SRC}$@/serwerTCP.c -o ${TARGET}$@/serwerTCP.o

clean:
	find ${TARGET} -name "*.o" | xargs rm -rf

.PHONY: all clean
