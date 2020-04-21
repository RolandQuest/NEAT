#include "AlterationHub.h"

#include "neat_settings.h"

namespace neat
{

	double AlterationHub::bestFitness = 0.0;
	int AlterationHub::bestFitnessGeneration = 0;
	int AlterationHub::generationsSinceImprovement = 0;

	void AlterationHub::CreateNextGeneration(int curGen, Population* currentPopulation, Population*& newPopulation) {

		currentPopulation->SettleDown();
		Genome* popChampion = currentPopulation->GetSpecies()[0]->Champion();
		if (popChampion->GetFitness() > bestFitness) {
			bestFitness = popChampion->GetFitness();
			bestFitnessGeneration = curGen;
			generationsSinceImprovement = 0;
		}
		else {
			generationsSinceImprovement++;
		}

		//Obliterate old species before adding to new population...
		//They will not be breeding anyways.



		newPopulation = new Population();

		for (auto& spec : currentPopulation->GetSpecies()) {
			newPopulation->AddSpecies(spec->GetHollowClone(Rando));
		}








		//Find number of expected children of each species.

	}

	void AlterationHub::Nuke() {

		bestFitness = 0.0;
		bestFitnessGeneration = 0;
		generationsSinceImprovement = 0;
	}
}