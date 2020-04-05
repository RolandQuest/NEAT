
#include <iostream>

#include "neat/neat.h"





int main() {

	for (size_t i = 0; i < 10000; i++) {
		neat::init(5, 5);
		neat::GenePool.EndGeneration();
	}

	

	return 0;
}