SHELL = /bin/bash

CC = gcc
CFLAGS = -Wall --pedantic

TARGET = bin/
SRC = source/
 
all:
	@for number in {1..4} ; do \
	    cat ${SRC}zad$$number/command ; \
	    if [ $$number -lt 12 ]; then \
		echo "------------------------------------------------------------" ; \
	    fi ; \
	done
	
	@for number in {5..12} ; do \
	    echo ${SRC}zad$$number/client.* ; \
	    ${CC} ${CFLAGS} ${SRC}zad$$number/client.c -o ${TARGET}zad$$number/client.o ; \
	    echo ${SRC}zad$$number/server.* ; \
	    ${CC} ${CFLAGS} ${SRC}zad$$number/server.c -o ${TARGET}zad$$number/server.o ; \
	    if [ $$number -lt 12 ]; then \
		echo "------------------------------------------------------------" ; \
	    fi ; \
	done
	
break:
	@echo "------------------------------------------------------------"

clean:
	find ${TARGET} -name "*.o" | xargs rm -rf

.PHONY: all clean
