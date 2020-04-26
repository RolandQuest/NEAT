#ifndef BREEDER_H
#define BREEDER_H

#include "liv/Genome.h"

namespace neat
{
	/**
		
	*/
	class Breeder
	{

	public:

		//! Breeds two genomes together.
		static bool Breed(Genome* mother, Genome* father, Genome*& child);

	};

}
#endif