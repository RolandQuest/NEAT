#ifndef NEAT_H
#define NEAT_H

#include "neat_settings.h"

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

}

#endif