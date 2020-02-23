#where's python

PYTHON_VERSION = 2.7
PYTHON_VERSION_NAME = py27

PYTHON_INC = /usr/include/python$(PYTHON_VERSION)
PYTHON_LIB = -lboost_python-$(PYTHON_VERSION_NAME)

#where's Boost

BOOST_INC = ~/Desktop/boost_1_72_0/boost
BOOST_LIB = ~/Desktop/boost/lib

in_out.so: in_out.o
	g++ -shared -Wl, -export-dynamic in_out.o -L$(BOOST_LIB) \
        -L$(PYTHON_LIB) -lboost_python-$(PYTHON_VERSION_NAME) \
        -lpython$(PYTHON_VERSION) -o in_out.so

in_out.o: in_out.cpp
	g++ -g -O0 -I$(PYTHON_INC) -I$(BOOST_INC) -fPIC -c in_out.cpp

clean:
	rm -f in_out.o in_out.so
