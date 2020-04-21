#ifndef ALTERATIONHUB_H
#define ALTERATIONHUB_H

#include <random>

#include "liv/Population.h"

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