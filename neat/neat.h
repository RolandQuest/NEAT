#ifndef NEAT_H
#define NEAT_H

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
	//void clearHistory();

	//! Returns the last generation.
	//Population* lastGeneration();

	//! Returns the current generation (0 index).
	int generationCount();

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
	
}

#endif