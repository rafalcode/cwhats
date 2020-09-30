CC=gcc
CFLAGS=-g -Wall
DBGCFLAGS=-g -Wall -DDBG
SPECLIBS=
BZLIBS=-lbz2

# looking for uov? chekc the juegoca repository

EXECUTABLES=grounda opts1 opts2 full64 pfcofs thouptf three2b mn0 pwco pwco2 pwco3 mirutma passing0 cis bz0 isqrt hxv2 minlog10 eqaa loopfun tok0 tokargs given of stc dst2 rea0 recu0 recu1 recu2 recukmr rek0 reksyll0 ti0 fread0 ssl0 cha0 pread0 pread2 poi0 aownsa aownsai freaflo genfaa sscanflo bit4b uov0 uov2 avec discgam avec2 avecn binrd2 updo updo2 mesf ssca0 icp crp0 crp0_d crp2 crp2_d apa phox0 qccmp0 qccmp durstp durstp_d hwplay i2 pffc usconrd po0 gl0 po1 namerd namerdx pdc ascha stst stst0 lread0 glord crwise cr0 cr1 cr1x cr1x sorta0 ins0 ins glord2 numma gl2 lit vecal0 ov0 prm0 fy0 msort0 verifm ms0 scalltp0 mergeatt tabvec floa doub0 upstep0

#Note if you're looking for the occurence coutner in here, forget it, it has its own repo in "juegooca"

# HOw to fill a character array,
fillc: fillc.c
	${CC} ${CFLAGS} -o $@ $^

prm0: prm0.c
	${CC} ${CFLAGS} -o $@ $^
fy0: fy0.c
	${CC} ${CFLAGS} -o $@ $^
msort0: msort0.c
	${CC} ${CFLAGS} -o $@ $^
numma: numma.c
	${CC} ${CFLAGS} -o $@ $^

# sorting, but getting its associated sort array (permutation) out as well.
# taken from old c_circus, and had to be corrected too.
ins0: ins0.c
	${CC} ${CFLAGS} -o $@ $^
ins2: ins2.c
	${CC} ${CFLAGS} -o $@ $^

i2: i2.c
	${CC} ${CFLAGS} -o $@ $^
c22: c22.c
	${CC} ${CFLAGS} -o $@ $^
pffc: pffc.c
	${CC} ${CFLAGS} -o $@ $^

ssca0: ssca0.c
	${CC} ${CFLAGS} -o $@ $^

# memset with floats .. a hack
mesf: mesf.c
	${CC} ${CFLAGS} -o $@ $^

# Quick char comp (instead of strcmp)
# zero is the proto
# this will be faster than strcmp is the strings are short.
# Apparently under 17 chars is small in this case (credit Carmack)
qccmp0: qccmp0.c
	${CC} ${CFLAGS} -o $@ $^
qccmp: qccmp.c
	${CC} ${CFLAGS} -o $@ $^

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
# more sophisticated
pwco2: pwco2.c
	${CC} ${CFLAGS} -o $@ $^ -lm
# even more, when I realised the calculations could be used for cluster analysis
pwco3: pwco3.c
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
	${CC} ${CFLAGS} -o $@ $^
tokargs: tokargs.c
	${CC} ${CFLAGS} -o $@ $^


binrd0: binrd0.c
	${CC} ${CFLAGS} -o $@ $^ -lm
# trying to tone down the hilarity
binrd2: binrd2.c
	${CC} ${CFLAGS} -o $@ $^ -lm


# Unsure what fg0 is 
fg0: fg0.c
	${CC} ${CFLAGS} -o $@ $^ -lm
# But used it for avec ... arbitrary integer vector builder, with its own container.
avec: avec.c
	${CC} ${CFLAGS} -o $@ $^ -lm
# avec2 really looks like a uovo (juegooca) ...
avec2: avec2.c
	${CC} ${CFLAGS} -o $@ $^
	# avec on a names .. i.e. a string: why? to count and give positions of a certain character .. say underscore!
avecn: avecn.c
	${CC} ${CFLAGS} -o $@ $^
# use avec as spring board for permutations using durstmann method?
durstp: durstp.c
	${CC} ${CFLAGS} -o $@ $^ -lm
durstp_d: durstp.c
	${CC} ${DBGCFLAGS} -o $@ $^ -lm


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
# above not quite a prototype .. some playing occuring.
# line read ... again just slurp each line
lread0: lread0.c
	${CC} ${CFLAGS} -o $@ $^
# fread0 for floats.
freaflo: freaflo.c
	${CC} ${CFLAGS} -o $@ $^
genfaa: genfaa.c
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

# scanf floats from a string:
sscanflo: sscanflo.c
	${CC} ${CFLAGS} -o $@ $^

ifbreak: ifbreak.c
	${CC} ${CFLAGS} -o $@ $^

# bit basics ... very simple but bloom filter style detectable!
# simple, but easy to forget!
bit4b: bit4b.c
	${CC} ${CFLAGS} -o $@ $^

icp: icp.c
	${CC} ${CFLAGS} -o $@ $^

Failed:
uov0: uov0.c
	${CC} ${CFLAGS} -o $@ $^
uov2: uov2.c
	${CC} ${CFLAGS} -o $@ $^
uov2_d: uov2.c
	${CC} ${DBGCFLAGS} -o $@ $^

# the afamed Discrete Gamma calc most Num Recips code.
discgam: discgam.c
	${CC} ${DBGCFLAGS} -o $@ $^ -lm

# jumping left and right indices.
updo: updo.c
	${CC} ${DBGCFLAGS} -o $@ $^ -lm
updo2: updo2.c
	${CC} ${DBGCFLAGS} -o $@ $^ -lm

# going over my chinese resto process it's very overwrought.
# it definitely need not be that hard. Try it on a simple array
crp0: crp0.c
	${CC} ${CFLAGS} -o $@ $^ -lm
crp0_d: crp0.c
	${CC} ${DBGCFLAGS} -o $@ $^ -lm
# following is a datastruc rendering also planning normal distribution of max-offspring setting.
crp2: crp2.c
	${CC} ${CFLAGS} -o $@ $^ -lm
crp2_d: crp2.c
	${CC} ${DBGCFLAGS} -o $@ $^ -lm
# failed idea use pointer to skip certain elements (went for mask instead
apa: apa.c
	${CC} ${DBGCFLAGS} -o $@ $^ -lm

phox0: phox0.c
	${CC} ${DBGCFLAGS} -o $@ $^ -lm


# hwplay ... well sort-of Hardy Weinberg play, but really about assortative mating.
hwplay0: hwplay0.c
	${CC} ${DBGCFLAGS} -o $@ $^ -lm

# You have a bunch of names and want to check them out
# particularly sample names, many thousands of them
namerd: namerd.c
	${CC} ${CFLAGS} -o $@ $^
# change of tack on the above ... beter name too: underscore name read: usconrd.
usconrd: usconrd.c
	${CC} ${CFLAGS} -o $@ $^
# In many cases you will have lists of names in separate files
# and you want to output a table of all in the names in the first file together with
# columns representing each of the subsequent files and with a 1 if that name was present and a 0 if not.
namerdx: namerdx.c
	${CC} ${CFLAGS} -o $@ $^

# Testing out popen ... for caputing system call output. Essnetially you ned to retrieve and format it as it gives a text streem.
po0: po0.c
	${CC} ${CFLAGS} -o $@ $^

po1: po1.c
	${CC} ${CFLAGS} -o $@ $^

gl0: gl0.c
	${CC} ${CFLAGS} -o $@ $^
gl2: gl2.c
	${CC} ${CFLAGS} -o $@ $^
# use getline funcs (based on gl0.c) to reorder lines from col to row wise
# use getline funcs (based on gl0.c) to reorder lines from col to row wise
glord: glord.c
	${CC} ${CFLAGS} -o $@ $^
	# following remodelling of thought process in cr1c.c, try it here
glord2: glord2.c
	${CC} ${CFLAGS} -o $@ $^
stst0: stst0.c
	${CC} ${CFLAGS} -o $@ $^
stst: stst.c
	${CC} ${CFLAGS} -o $@ $^
# print 2 strings but only the differnt characters
pdc: pdc.c
	${CC} ${CFLAGS} -o $@ $^
ascha: ascha.c
	${CC} ${CFLAGS} -o $@ $^

# # converting column to row wise and vice versa
# simple mechanism for col-row wise numebr ordering.
# later to be applied to file lines.
cr0: cr0.c
	${CC} ${CFLAGS} -o $@ $^
cr1: cr1.c
	${CC} ${CFLAGS} -o $@ $^
	# same as cr1 except it takes nrows first, and ncols second.
cr1x: cr1x.c
	${CC} ${CFLAGS} -o $@ $^
crwise: crwise.c
	${CC} ${CFLAGS} -o $@ $^
lit0: lit0.c
	${CC} ${CFLAGS} -std=c99 -o $@ $^

vecal0: vecal0.c
	${CC} ${CFLAGS} -std=c99 -o $@ $^

ms0: ms0.c
	${CC} ${CFLAGS} -std=c99 -o $@ $^

# overflow
ov0: ov0.c
	${CC} ${CFLAGS} -std=c99 -o $@ $^

mergeatt: mergeatt.c
	${CC} ${CFLAGS} -std=c99 -o $@ $^

verifm: verifm.c
	${CC} ${CFLAGS} -std=c99 -o $@ $^

# System call templates. Use these to make system calls from c code.
scalltp0: scalltp0.c
	${CC} ${CFLAGS} -std=c99 -o $@ $^

tabvec: tabvec.c
	${CC} ${CFLAGS} -std=c99 -o $@ $^

upstep0: upstep0.c
	${CC} ${CFLAGS} -std=c99 -o $@ $^

floa: floa.c
	${CC} ${CFLAGS} -std=c99 -o $@ $^

# comapirson of doubles
doub0: doub0.c
	${CC} ${CFLAGS} -std=c99 -o $@ $^

.PHONY: clean

clean:
	rm -f ${EXECUTABLES}
