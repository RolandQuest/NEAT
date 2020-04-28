#ifndef ALTERATIONHUB_H
#define ALTERATIONHUB_H

#include <random>

#include "liv/Population.h"
#include "liv/Genome.h"

namespace neat
{
	/**
		Heart and soul of algorithm.
		Handles generation to generation population creation.
	*/
	class AlterationHub
	{

	public:

		//! Fully constructs a new population from the old one.
		static void CreateNextGeneration(int curGen, Population* currentPopulation, Population*& newPopulation);

		//! Resets fitness metrics to 0.
		static void Nuke();

	private:

		//! Selects a mutation style and mutates given child.
		static bool Mutate(Genome* orig, Genome*& child);

		//! Mutates a genome by adding a connection.
		static bool MutateAddLink(Genome*& child);

		//! Mutates a genome by splitting a connection and adding a node.
		static bool MutateAddNode(Genome*& child);

		//! Mutates a genome by perturbing the weights.
		static bool MutateWeights(Genome*& child);

		//! Selects a breeding style and breeds a child.
		static bool Breed(Genome* mother, Genome* father, Genome*& child);

		//! 
		static bool BreedMultipoint(Genome* mother, Genome* father, Genome*& child);

		//! 
		static bool BreedMultipointAverage(Genome* mother, Genome* father, Genome*& child);

		//! 
		static bool BreedSinglepoint(Genome* mother, Genome* father, Genome*& child);

		///
		/// Historical records of all past populations. Does this really belong here?
		///

		//! The best fitness recorded across all generations.
		static double bestFitness;

		//! The generation of best fitness.
		static int bestFitnessGeneration;

	};
}


#endif