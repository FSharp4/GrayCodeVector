# GreyCodeVector
Grey Code Vector File Generator written in C++. 
This program was written to assist me in using Cadence Virtuoso. As 
such, vector files generated follow an appropriate but rigid format.

Signal names are declared as "A B C D E ..." to an appropriate number of 
arguments.
All signals are inputs (i) and have radix 1.

The Gray code sequence is generated in a very regular fashion. As an example:
```
0 0 0
0 0 1
0 1 1
0 1 0
1 1 0
1 1 1
1 0 1
1 0 0
0 0 0 <-- The last code is the first code repeated
```

