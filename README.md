# cwhats
See what happens with simple c code.

# Explanation
Clearly, c also stands for "see" and these are mainly snippets
which show very simple but often, powerful effects

# Contents

## gorounda.c
The name is a mnemonic for "Go around array" and it's used for comparing the
each element of an array with the rest, one by one, in circular fashion.

## pwco.c
Coded much later, but seems to be similar to the above. PairWise Comparison Operations

## mirutma.c
Mnemonic MIR Upper Triangular MAtrix
matrix transformation: principally mirroring triangle matrices.

## aa.c
This was the result of a game presented by Nuritas when looking for bioinformaticians.
a peptide sequence with heterogeneous quantities of the different AA's (as is normal)
must be converted to a sequence with equally represented AA's, and the smallest subsequence
with those change must be calculated. Because it's a single subsequence. Luckily the length of the sequence
is an integer multiple of the number of the AA's used which happens to be the full complement of 20.

There was a number of function here that I have already coded elsewhere ... and I did try to looks for them
but they didn't come up (especialy the codon code from Uppsala), and it was easier to code from zero.

## recukmer.c
Recusion is a key aspect of computing, but being attached to the imperative style of programming, I don't use it much.
But the generation of kmers it turned out to be an ideal approach as it allows arbitrary embedded of for loops inside each other.
The python version is handled very easily, while the c version requires more work.

However one or two notes about recursion are in order. 
* it's imitative of the stack, which is an internal resource of the computer
* however, just be it's internaly used, it does not mean that it's exposed to usage.
* the stack is a FIFO arrangement of commands primarily, not data nor storage.
* recursion and trees and very very related.
* recursion also closely related to the Kronecker product.
* most of the c progam is recording the progress of the recursion tree by storing intermediate results properly in an array
