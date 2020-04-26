#include "neat_settings.h"

#include <time.h>

namespace neat
{

	///
	/// Common objects.
	///

	InnovationManager InnovationPool;
	GeneManager GenePool;
	NodeManager NodePool;
	Population* CurrentPopulation;

	///
	/// Rng Objects
	///

	std::mt19937 Rando(time(0));
	std::uniform_real_distribution<double> ProbabilitySpace(0.0, 1.0);
	int randposneg() { return ProbabilitySpace(Rando) < 0.5 ? -1 : 1; }

	///
	/// Population Settings
	///

	int PopulationSize = 150;

	///
	/// Weight Settings
	///

	double InitialConnectionWeightMax = 2.0;
	double ConnectionWeightMax = 8.0;

	///
	/// Speciation Settings
	///

	double SpeciationDeltaThresh = 3.0;
	double CompatExcessCoeff = 1.0;
	double CompatDisjointCoeff = 1.0;
	double CompatWeightCoeff = 0.4;

	///
	/// Breeding and Mutation
	///

	double MutateOnlyProbability = 0.25;
	double BreedOnlyProbability = 0.25;
	double MutateAddNodeProbability = 0.01;
	double MutateAddLinkProbability = 0.30;
	double MutateWeightsProbability = 1.0 - MutateAddLinkProbability - MutateAddNodeProbability;
	double BreedMultipointProbability = 1.0;
	double BreedMultipointAverageProbability = 0.0;
	double BreedSinglepointProbability = 1.0 - BreedMultipointProbability - BreedMultipointAverageProbability;
	double MutateWeightMaxPower = 2.0;

	///
	/// Unsorted
	///

	int CCS_Generations = 30;
	int CSS_AgeThresh = 20;
	int SpeciesDropOffAge = 15;
	int SpeciesAgeOfSignificanceThresh = 10;
	double SpeciesAgeOfSignificanceBonus = 1.0;
	double SpeciesNumberOfParentsPercent = 0.75;
}
