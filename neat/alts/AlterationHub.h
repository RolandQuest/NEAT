#ifndef ALTERATIONHUB_H
#define ALTERATIONHUB_H

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

		//! 
		static double bestFitness;

		//! 
		static int bestFitnessGeneration;

		//! 
		static int generationsSinceImprovement;
	};
}


#endif