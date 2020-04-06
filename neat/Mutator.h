#ifndef MUTATOR_H
#define MUTATOR_H

#include "Genome.h""

namespace neat
{
	/**
		
	*/
	class Mutator
	{

	public:

		//! Mutates the genome in a random way.
		static Genome* MutateRandom(Genome* orig);

		//! Mutates the genome by
		static Genome* Mutate(Genome* orig);

	};
}


#endif