#include "AlterationHub.h"

namespace neat
{

	double AlterationHub::bestFitness = 0.0;
	int AlterationHub::bestFitnessGeneration = 0;
	int AlterationHub::generationsSinceImprovement = 0;

	void AlterationHub::CreateNextGeneration(int curGen, Population* currentPopulation, Population*& newPopulation) {

		Genome* popChampion = currentPopulation->GetSpecies()[0]->Champion();
		if (popChampion->Fitness() > bestFitness) {
			bestFitness = popChampion->Fitness();
			bestFitnessGeneration = curGen;
			generationsSinceImprovement = 0;
		}
		else {
			generationsSinceImprovement++;
		}







		//Find number of expected children of each species.

	}

	void AlterationHub::Nuke() {

		bestFitness = 0.0;
		bestFitnessGeneration = 0;
		generationsSinceImprovement = 0;
	}
}