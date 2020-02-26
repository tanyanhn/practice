#! /usr/bin/env python3

from math import sqrt


class Point:
    x = 0.0
    y = 0.0


a = Point()
b = Point()
b.x = 5
b.y = 5.0

print(sqrt((b.x - a.x) ** 2 + (b.y - a.y) ** 2))  # option 1


a = [0, 0]
b = [5, 5]
print(sqrt((b[0] - a[0]) ** 2 + (b[1] - a[1]) ** 2))  # option 2
print(sqrt(sum((b[i] - a[i]) ** 2 for i in [0, 1])))  # option 3
