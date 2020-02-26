#! /usr/bin/env python3

from grid import GridPoint
# from grid import magnitude

# Create instance of the GridPoint class called mypoint, set list elements.
mypoint = GridPoint()
mypoint.pts[0] = 1.0
mypoint.pts[1] = 2.0

print(mypoint.magnitude())  # 2.23606797749979

grid = []  # Create a list.
for gpoint in range(10):  # For loop over a sequence.
    # Create an instance of the GridPoint class and add it to the grid list.
    grid.append(GridPoint())
    # Set some variables within each class.
    grid[gpoint].color = "blue"
    grid[gpoint].diameter = gpoint
    grid[gpoint].pts = [1.0, 1.0]

print(grid[5].diameter)
