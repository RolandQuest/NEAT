
#include <iostream>
#include <time.h>

#include "neat.h"
#include "tests/Pole1.h"

int main() {

	neat::Rando.seed(10);

	neat::SpeciationDeltaThresh = 2.0;
	neat::init(4, 2);

	for (size_t gen = 0; gen < 3; gen++) {

		std::cout << "Generation: " << gen << '\t';

		std::vector<neat::Network*> nets = neat::generateNetworks();

		double bestFitness = 0.0;
		for (auto& net : nets) {

			double fitness = Pole1::Evaluate(neat::Rando, net);
			bestFitness = (fitness > bestFitness) ? fitness : bestFitness;
			net->SetFitness(fitness);
			delete net;
		}

		std::cout << "Fitness: " << bestFitness << '\n';
		neat::iterateGeneration();
	}

	neat::reset();

	return 0;
}