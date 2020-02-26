#! /usr/bin/env python3

years = [2001, 2002, 2003, 2004, 2005]

for i in range(4, 14, 3):
    # A for loop over a sequence form the range function.
    # "i" is a number in the sequence.
    print("Year #", i, "is", years[(i - 4)//3])
