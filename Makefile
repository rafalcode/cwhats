CC=gcc
CFLAGS=-g -Wall
SPECLIBS=
BZLIBS=-lbz2

EXECUTABLES=grounda opts1 opts2 full64 pfcofs thouptf three2b mn0 pwco mirutma passing0 cis bz0 isqrt hxv2 minlog10 eqaa loopfun tok0 given of stc dst2 rea0 recu0 recu1 recu2 recukmr rek0 reksyll0 ti0 fread0 ssl0 cha0 pread0 pread2 poi0 aownsa aownsai

isqrt: isqrt.c
	${CC} ${CFLAGS} -o $@ $^

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
given: given.c
	${CC} ${CFLAGS} -o $@ $^
of: of.c
	${CC} ${CFLAGS} -o $@ $^
stc: stc.c
	${CC} ${CFLAGS} -o $@ $^
dst2: dst2.c
	${CC} ${CFLAGS} -o $@ $^

# testing directory things ... very trivial, but seem to forget it.
# show how the ~ char in bash does (of course!) resolve properly
dirs0: dirs0.c
	${CC} ${CFLAGS} -o $@ $^

loopfun: loopfun.c
	${CC} ${CFLAGS} -o $@ $^

# pairwise comparison able, simplest possible idea ... turne out to be a bit thorny.
pwco: pwco.c
	${CC} ${CFLAGS} -o $@ $^ -lm

# pairwise comparison able, simplest possible idea ... turne out to be a bit thorny.
passing0: passing0.c
	${CC} ${CFLAGS} -o $@ $^

# Given an upper triangular matrix, mirror the values onto the lower triangle
# not as easy as it seems. Got into knots. WOrking now though.
mirutma: mirutma.c
	${CC} ${CFLAGS} -o $@ $^

# cosine and sine values.
cis: cis.c
	${CC} ${CFLAGS} -o $@ $^ -lm

bz0: bz0.c
	${CC} ${CFLAGS} -o $@ $^ $(BZLIBS)


# Nuritas 800 aa test
eqaa: eqaa.c
	${CC} ${CFLAGS} -o $@ $^

# dec to hex values 
hxv2: hxv2.c
	${CC} ${CFLAGS} -o $@ $^

minlog10: minlog10.c
	${CC} ${CFLAGS} -o $@ $^ -lm

# using strtok (never use string literals liek so: chr *s="mymistake"; rather use char s[]="mymistake";
tok0: tok0.c
	${CC} ${CFLAGS} -o $@ $^ -lm

binrd0: binrd0.c
	${CC} ${CFLAGS} -o $@ $^ -lm

fg0: fg0.c
	${CC} ${CFLAGS} -o $@ $^ -lm

rea0: rea0.c
	${CC} ${CFLAGS} -o $@ $^ -lm


# genread.c has been basis for too long, it was by no means perfect. Behold v2, more watertight .. hoepfully.
# # read Char Array (aka word type)
rdca: rdca.c
	${CC} ${CFLAGS} -o $@ $^ -lm

recu0: recu0.c
	${CC} ${CFLAGS} -o $@ $^ -lm

recu1: recu1.c
	${CC} ${CFLAGS} -o $@ $^ -lm

recu2: recu2.c
	${CC} ${CFLAGS} -o $@ $^ -lm

recukmr: recukmr.c
	${CC} ${CFLAGS} -o $@ $^ -lm
rek0: rek0.c
	${CC} ${CFLAGS} -o $@ $^ -lm


# recursively generating sylables.
# reksyll0: reksyll0.c
sy: sy.c
	${CC} ${CFLAGS} -o $@ $^ -lm

ti0: ti0.c
	${CC} ${CFLAGS} -o $@ $^ -lm

fread0: fread0.c
	${CC} ${CFLAGS} -o $@ $^

# ped file IID reader
pread0: pread0.c
	${CC} ${CFLAGS} -o $@ $^
# try to keeo things simple even if it means iterating over the buffer many times.
pread2: pread2.c
	${CC} ${CFLAGS} -o $@ $^

ssl0: ssl0.c
	${CC} ${CFLAGS} -o $@ $^ -lcrypto

cha0: cha0.c
	${CC} ${CFLAGS} -o $@ $^

poi0: poi0.c
	${CC} ${CFLAGS} -o $@ $^ -lm

aownsa: aownsa.c
	${CC} ${CFLAGS} -o $@ $^ -lm
# change from floating point to long longs!
aownsai: aownsai.c
	${CC} ${CFLAGS} -o $@ $^ -lm
# very simple lines in cairo
cairlin0: cairlin0.c
	${CC} ${CFLAGS} -o $@ $^ -lm -lcairo

.PHONY: clean

clean:
	rm -f ${EXECUTABLES}
