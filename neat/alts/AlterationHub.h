#ifndef ALTERATIONHUB_H
#define ALTERATIONHUB_H

#include <random>

#include "liv/Population.h"
#include "liv/Genome.h"

namespace neat
{
	/**

	*/
	class AlterationHub
	{

	public:

		//! 
		static void CreateNextGeneration(int curGen, Population* currentPopulation, Population*& newPopulation);

		//!
		static bool Mutate(Genome* orig, Genome*& child);

		//!
		static bool MutateAddLink(Genome*& child);

		//! 
		static bool MutateAddNode(Genome*& child);

		//!
		static bool MutateWeights(Genome*& child);

		//!
		static bool Breed(Genome* mother, Genome* father, Genome*& child);

		//! 
		static bool BreedMultipoint(Genome* mother, Genome* father, Genome*& child);

		//!
		static bool BreedMultipointAverage(Genome* mother, Genome* father, Genome*& child);

		//!
		static bool BreedSinglepoint(Genome* mother, Genome* father, Genome*& child);

		//! 
		static void Nuke();


		///
		/// Historical records of all past populations. Does this really belong here?
		///

		//! 
		static double bestFitness;

		//! 
		static int bestFitnessGeneration;

		//! 
		static int generationsSinceImprovement;
	};
}


#endif