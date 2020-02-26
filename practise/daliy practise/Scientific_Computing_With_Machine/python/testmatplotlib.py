#! /usr/bin/env python3

import warnings
import numpy
from matplotlib import pyplot

warnings.simplefilter("ignore")

numResX = 100
resListX0 = [numpy.random.rand(x) * 10 for x in range(numResX)]
pyplot.hist(resListX0, bins=numResX, range=[0.5, numResX + 0.5], align='mid', facecolor='g', rwidth=0.9, alpha=0.75)
pyplot.axis([0.5, 10 + 0.5, 0, 10])
pyplot.xlabel("x-aixs")
pyplot.ylabel("y-aixs")
pyplot.grid(True)
pyplot.savefig("contanct_map_example1")
