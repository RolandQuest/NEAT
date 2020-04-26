#ifndef NEAT_SETTINGS_H
#define NEAT_SETTINGS_H

#include <random>

#include "man/InnovationManager.h"
#include "man/GeneManager.h"
#include "man/NodeManager.h"
#include "liv/Population.h"

namespace neat
{

	///
	/// Common objects.
	///

	//! Control for the innovations.
	extern InnovationManager InnovationPool;
	//! Control for the genes.
	extern GeneManager GenePool;
	//! Control for the nodes.
	extern NodeManager NodePool;
	//! The current population.
	extern Population* CurrentPopulation;

	///
	/// Rng Objects
	///

	//! Rng used for the neat objects.
	extern std::mt19937 Rando;
	//! Distribution for raw probabilities.
	extern std::uniform_real_distribution<double> ProbabilitySpace;
	//! Returns -1 or 1 with even chance.
	extern int randposneg();

	///
	/// Population Settings
	///

	//! The size of the poplulation to use.
	extern int PopulationSize;

	///
	/// Weight Settings
	///

	//! The max absolute value of a connection's initial weight.
	extern double InitialConnectionWeightMax;
	//! The max absolute value of a connection's weight.
	extern double ConnectionWeightMax;

	///
	/// Speciation Settings
	///

	//! Speciation delta thresh
	extern double SpeciationDeltaThresh;
	//! Speciation coefficient for Excess genes.
	extern double CompatExcessCoeff;
	//! Speciation coefficient for Disjoint genes.
	extern double CompatDisjointCoeff;
	//! Speciation coefficient for average weights of common genes.
	extern double CompatWeightCoeff;

	///
	/// Breeding and Mutation
	///

	//! The chance to create a genome via mutation and not breeding.
	extern double MutateOnlyProbability;
	//! The chance to create a genome via breeding with no mutation.
	extern double BreedOnlyProbability;
	//! The chance of mutating via adding a node.
	extern double MutateAddNodeProbability;
	//! The chance of mutating via adding a link.
	extern double MutateAddLinkProbability;
	//! The chance of mutating via changing weights.
	extern double MutateWeightsProbability;
	//! The chance of breeding multipoint.
	extern double BreedMultipointProbability;
	//! the chance of breeding multipoint average.
	extern double BreedMultipointAverageProbability;
	//! The chance of breeding singlepoint.
	extern double BreedSinglepointProbability;
	//! The maximum power to mutate a weight by.
	extern double MutateWeightMaxPower;

	///
	/// Unsorted
	///

	//! Number of generations before checking for Competitive Coevolution Stagnation.
	extern int CCS_Generations;
	//! The weakest species as old or older will be forcibly killed when CCS checks occur.
	extern int CSS_AgeThresh;
	//! The generations of no-improvement when a species is forcibly killed.
	extern int SpeciesDropOffAge;
	//! Genomes in a species aged less than or equal to this thresh will recieve a bonus to their fitness.
	extern int SpeciesAgeOfSignificanceThresh;
	//! The bonus multiplier to be applied to the genomes of young species.
	extern double SpeciesAgeOfSignificanceBonus;
	//! The percent of genomes of each species that are eligible for reproduction.
	extern double SpeciesNumberOfParentsPercent;
}

#endif