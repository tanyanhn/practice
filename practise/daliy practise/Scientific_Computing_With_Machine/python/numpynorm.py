#! /usr/bin/env python3

import numpy as np
a = np.array([0, 0])
b = np.array([5, 5])

print(np.linalg.norm(b - a))

data = np.array([x ** 3 + np.random.rand() for x in np.arange(10)])

print(data)
print(np.polyfit(np.arange(len(data)), data, 3))
