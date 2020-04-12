#ifndef NEAT_H
#define NEAT_H

#include <vector>
#include <random>
#include <time.h>

#include "innov/InnovationManager.h"
#include "man/GeneManager.h"
#include "man/NodeManager.h"
#include "liv/Population.h"

namespace neat
{
	///
	/// Interface into system.
	///

	//! Initializes the system. Calls reset before initializing.
	void init(int inputNodes, int outputNodes);

	//! Logs the current generation and generates the next.
	void iterateGeneration();

	//! Completely wipes the system.
	void reset();

	//! Clears the population history books.
	void clearHistory();

	//! Returns the last generation.
	Population* lastGeneration();

	//! Returns the current generation (0 index).
	int generationCount();

	///
	/// Common objects.
	///

	//! Rng used for the neat objects.
	extern std::mt19937 Rando;
	//! Control for the innovations.
	extern InnovationManager InnovationPool;
	//! Control for the genes.
	extern GeneManager GenePool;
	//! Control for the nodes.
	extern NodeManager NodePool;
	//! The current population.
	extern Population* CurrentPopulation;
	
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

}

#endif