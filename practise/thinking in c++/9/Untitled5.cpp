// Inline functions
#ifndef STASH4_H
#define STASH4_H
#include "../require.h"

class Stash {
	int size;          //Size of each space
	int quantity;      //Number of storage spaces
	int next;          //Next empty space
	//Dynamically allocated array of bytes:
	unsigned char* storage;
	void inflate(int increase);
public:
	Stash(int sz) : size(sz), quantity(0),
	  next(0), storage(0) {	  }
	Stash(int sz, int initQuantity) :
};
