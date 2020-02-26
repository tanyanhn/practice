#! /usr/bin/env python3

ages = [10, 20, 30, 40, 50]
agess = [11, 22, 33, 44, 55]
cy = 2015
print("The year is", cy)
for age1, age in zip(ages, agess):
    # For loop over the elements in the ages list.
    # "age" is the element of ages.
    print("Age:", age, "Born:", cy - age)
    print("Age:", age1, "Born:", cy - age1)
    for j in range(0, 10, 2):
        print("In", cy + j, "age is:", age+j)

while cy < 2020:
    cy = cy + 1
    print("The year is now", cy)
