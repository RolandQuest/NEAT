
#include <iostream>

#include "neat.h"

int main() {

	neat::Rando.seed(10);

	for (size_t i = 0; i < 10000000; i++) {

		neat::init(4, 4);
		neat::iterateGeneration();
	}

	return 0;
}