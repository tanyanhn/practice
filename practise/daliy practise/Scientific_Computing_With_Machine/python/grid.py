#! /usr/bin/env python3

from math import sqrt


class GridPoint(object):
    def __init__(self):
        # Executed upon the creation of the class.
        self.color = None
        self.diameter = None
        self.pts = []
        self.pts.append(0.0)
        self.pts.append(0.0)

    def magnitude(self):
        # Require no arguments when called, must define with "self"
        mag = self.pts[0] * self.pts[0] + self.pts[1] * self.pts[1]
        return sqrt(mag)
