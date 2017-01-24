CC=gcc
CFLAGS=-g -Wall
SPECLIBS=
EXECUTABLES=grounda opts1 opts2 full64 pfcofs thouptf three2b mn0 pwco mirutma

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

thouptf: thouptf.c
	${CC} ${CFLAGS} -o $@ $^

# looking at thiryt two bits and how they may be got doen to 16 bits nicely.
three2b: three2b.c
	${CC} ${CFLAGS} -o $@ $^

mn0: mn0.c
	${CC} ${CFLAGS} -o $@ $^


# pairwise comparison able, simplest possible idea ... turne out to be a bit thorny.
pwco: pwco.c
	${CC} ${CFLAGS} -o $@ $^

# Given an upper triangular matrix, mirror the values onto the lower triangle
# not as easy as it seems. Got into knots. WOrking now though.
mirutma: mirutma.c
	${CC} ${CFLAGS} -o $@ $^

.PHONY: clean

clean:
	rm -f ${EXECUTABLES}
