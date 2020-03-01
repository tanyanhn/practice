#! /usr/bin/env python3

import h5py
import numpy as np
import argparse
import platform


def write_frame_to_restart_file(restart_file_name, time_step, lattice):
    restart_file = h5py.File(restart_file_name, 'a')
# restart_file["/" + simulation_name].create_dataset("time_step",
#                                                      (1024,), dtype=np.int)
# dataset can't be asign
    restart_file["/" + simulation_name + "/" + str(time_step)] = lattice
    restart_file.close()


# default values
run = 10
restart_time = 0
restart_file_name = "restart.h5"
simulation_name = "foo"

# Parse command line arguments
parser = argparse.ArgumentParser()
parser.add_argument('--run', nargs=1, type=int,
                    help='run help')
parser.add_argument('--restart_file_name', nargs=1,
                    help='name of restart file')
parser.add_argument('--restart_time', nargs=1, type=int,
                    help='restart the simulation at ...')
parser.add_argument('--simulation_name', nargs=1,
                    help='simulation name')
args = parser.parse_args()
if args.run is not None:
    run = args.run[0]
if args.restart_time is not None:
    restart_time = args.restart_time[0]
if args.restart_file_name is not None:
    restart_file_name = args.restart_file_name[0]
if args.simulation_name is not None:
    simulation_name = args.simulation_name[0]

restart_file = h5py.File(restart_file_name, 'a')

# create node if it doesn't exist
if not "/" + simulation_name in restart_file:
    restart_file.create_group("/" + simulation_name)
# Write metadata to restart file as attributes
restart_file["/" + simulation_name].attrs.create("system",
                                                 platform.system())
restart_file["/" + simulation_name].attrs.create("release",
                                                 platform.release())

if args.restart_time is not None:  # load state from restart file
    restart_time = args.restart_time[0]
    lattice = restart_file["/" + simulation_name + "/"
                           + str(restart_time)]
    time_step = restart_time

else:  # generate new simulation
    lattice = np.zeros(1024, dtype=np.int)
    lattice[512] = 10000
    time_step = 0
    # delete if it exist
    if "/" + simulation_name + "/0" in restart_file:
        restart_file.__delitem__("/" + simulation_name + "/0")
    write_frame_to_restart_file(restart_file_name, time_step,
                                lattice)

# delete any forward steps from the restart file
restart_time += 1  # begin deleting records from here
next_dataset = "/" + simulation_name + "/" + str(restart_time)
while next_dataset in restart_file:
    restart_file.__delitem__(next_dataset)
    restart_time += 1
    next_dataset = ("/" + simulation_name + "/" + str(restart_time))

# run the simulation
while time_step < run:
    new_lattice = np.zeros(1024, dtype=np.int)
    for i in range(1024):
        for j in range(lattice[i]):
            sample = np.random.random()
            if(i > 0 and i < 1023):
                if(sample <= 0.25):
                    new_lattice[i - 1] += 1
                elif (sample >= 0.75):
                    new_lattice[i + 1] += 1
                else:
                    new_lattice[i] += 1
    # save for this time step
    lattice = new_lattice
    time_step = time_step + 1
    write_frame_to_restart_file(restart_file_name, time_step,
                                lattice)
# end of file
