CC = gcc
CFLAGS = -Wall --pedantic
TARGET = bin/
SRC = source/

zad5:
	${CC} ${CFLAGS} ${SRC}$@/klientTCP.c -o ${TARGET}$@/klientTCP.o
	${CC} ${CFLAGS} ${SRC}$@/serwerTCP.c -o ${TARGET}$@/serwerTCP.o

zad6:
	${CC} ${CFLAGS} ${SRC}$@/klientTCP.c -o ${TARGET}$@/klientTCP.o
	${CC} ${CFLAGS} ${SRC}$@/serwerTCP.c -o ${TARGET}$@/serwerTCP.o

zad7:
	${CC} ${CFLAGS} ${SRC}$@/klientTCP.c -o ${TARGET}$@/klientTCP.o
	${CC} ${CFLAGS} ${SRC}$@/serwerTCP.c -o ${TARGET}$@/serwerTCP.o

zad8:
	${CC} ${CFLAGS} ${SRC}$@/klientTCP.c -o ${TARGET}$@/klientTCP.o
	${CC} ${CFLAGS} ${SRC}$@/serwerTCP.c -o ${TARGET}$@/serwerTCP.o

zad9:
	${CC} ${CFLAGS} ${SRC}$@/klientTCP.c -o ${TARGET}$@/klientTCP.o
	${CC} ${CFLAGS} ${SRC}$@/serwerTCP.c -o ${TARGET}$@/serwerTCP.o

clean:
	find ${TARGET} -name "*.o" | xargs rm -rf

