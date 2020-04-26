#ifndef MUTATOR_H
#define MUTATOR_H

#include "liv/Genome.h"

namespace neat
{
	/**
		
	*/
	class Mutator
	{

	public:

		//! Mutates the genome in a random way.
		static bool MutateRandom(Genome* orig, Genome*& child);

		//! Mutates the genome by
		static bool MutateAddConnection(Genome* orig, Genome*& child);

		//! Mutates the genome by
		static bool MutateAddNode(Genome* orig, Genome*& child);

	};
}


#endif