CC=gcc
CFLAGS=-g -Wall
SPECLIBS=
EXECUTABLES=grounda

gorounda: gorounda.c
	${CC} ${CFLAGS} -o $@ $^

.PHONY: clean

clean:
	rm -f ${EXECUTABLES}
