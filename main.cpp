
#include <iostream>
#include <time.h>

#include "neat.h"

int main() {

	//neat::Rando.seed(10);

	time_t start, end;
	start = clock();

	for (size_t i = 0; i < 10000; i++) {

		neat::init(4, 4);
		neat::iterateGeneration();
	}

	end = clock();
	std::cout << difftime(end, start) << '\n';

	return 0;
}