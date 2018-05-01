#pragma once
#ifndef RANDOM_H_
#define RANDOM_H_
#include <iostream>
#include <cstdlib>
#include <ctime>

/* Class for generating random numbers needed in any part of the program */
class Random {

public:

	Random() {
		srand((unsigned int)std::time(0));
	}

	Random(int seed) {
		srand(seed);
	}

	// Returns an integer between upper and lower bounds
	int int_range(int first, int second) {
		return rand() % (second - first + 1) + first;
	}

	// Returns an integer between 0 and n
	int next_int(int n) {
		return int(next_double() * n);
	}

	// Returns a double between 0 and 1
	double next_double() {
		return double(rand()) / RAND_MAX;
	}

};

#endif