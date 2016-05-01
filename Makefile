CC=gcc
CFLAGS=-g -Wall
SPECLIBS=
EXECUTABLES=grounda opts1 opts2 full64 pfcofs

gorounda: gorounda.c
	${CC} ${CFLAGS} -o $@ $^

opts1: opts1.c
	${CC} ${CFLAGS} -o $@ $^

opts2: opts2.c
	${CC} ${CFLAGS} -o $@ $^

# print a substring. Trivial, but a way of showing how sprintf can be
# used for alot of things.
pfcofs: pfcofs.c
	${CC} ${CFLAGS} -o $@ $^

# you have to be careful using 64 bit masks of unsigned long's
full64: full64.c
	${CC} ${CFLAGS} -o $@ $^

.PHONY: clean

clean:
	rm -f ${EXECUTABLES}
