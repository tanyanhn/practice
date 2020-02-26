#! /usr/bin/env python3
from scipy.optimize import minimize


def func(x):
    return x ** 3 - x ** 2


print(minimize(func, 0.1))
print(minimize(func, -2.1))
print(minimize(lambda x: x ** 3 - x ** 2, 0.1))
print(minimize(lambda x: x ** 3 - x ** 2, -2.1))
