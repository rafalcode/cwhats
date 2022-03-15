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
Recursion is a key aspect of computing, but being attached to the imperative style of programming, I don't use it much.  But the generation of kmers it turned out to be an ideal approach as it allows arbitrary embedded of for loops inside each other.
The python version is handled very easily, while the c version requires more work.

However one or two notes about recursion are in order. 
* it's imitative of the stack, which is an internal resource of the computer
* however, just be it's internaly used, it does not mean that it's exposed to usage.
* the stack is a FIFO arrangement of commands primarily, not data nor storage.
* recursion and trees and very very related.
* recursion also closely related to the Kronecker product.
* most of the c progam is recording the progress of the recursion tree by storing intermediate results properly in an array

## aownsa.c
"Array OWNS Array". Quite an interesting exercise that I hadn't thought of before. THis program works on the simplest implementation
where with have an owning array, later called parent array with a limited number of elements, in this case floating point values between 0 and 1, generated randomly. We want to be able to take a second, and bigger array of the same type which can be called a child array and allocate its elements to the elements of the first array based on distance to the nearest element.

Returning to this, some explanation is needed. IrnN any case "parent" array is better than owning array, and child array for the subordinate array. THis nomenclature is actually used internally.

But dynmax is really pretty incomprehensible. The name, for a start. It seems to render the so called nodes into
integers, but then was possible is that two nodes can fall on the same integer in the parent array, which is not really part of the user-case.

However, that can be worked out OK

## qccmp.c
A quick string comparator when strings are short (<17chars)

## tok0.c
strtok at work. Note the string before the first delimiter best taken separately

## glord.c
These programs use getline to read a textfile but then they do some ordering on the columns on the rows. Unsure.
