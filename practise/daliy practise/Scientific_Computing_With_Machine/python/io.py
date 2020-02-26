#! /usr/bin/env python3

import io

with io.open("parrots.txt", "a") as my_file:
    # Alternative way to open and append.
    # Notice the "\n" to create a newline.
    my_file.write(u"Polly\n")  # the u prefix ensures unicode
    my_file.write(u"Piney\n")
    my_file.write(u"Fjordy\n")

names = []
my_file = io.open("parrots.txt", "r")  # open parrots.txt for reading
names.append(my_file.readline())  # read the first line
names.append(my_file.readline())  # read the second line
my_file.close()

for i, item in enumerate(names):
    print("Parrot #", i, "is", item)  # print read-in lines from the list
