#! /usr/bin/env python3

import multiprocessing


def worker(n):
    my_name = multiprocessing.current_process().name
    print(n, " : ", my_name)
    return 'Worker %d using process %s' % (n, my_name)


def hello_world():
    pool = multiprocessing.Pool(2)
    results = pool.map(worker, range(4))
    pool.close()
    print(multiprocessing.active_children())
    for message in results:
        print(message)


if __name__ == '__main__':
    hello_world()
