#ifndef POPULATION_H
#define POPULATION_H

#include <vector>

#include "Genome.h"
#include "Species.h"

namespace neat
{
	/**

	*/
	class Population
	{

	public:

		///
		/// ctros/dtors
		///

		//! Constructor
		Population() = default;

		//! Destructor
		virtual ~Population();

		///
		/// Population
		///

		//! 
		void AddGenome(Genome* g);

		//! 
		std::vector<Genome*> Genomes();

		//! 
		size_t SpeciesCount();

	private:

		//! The entire population.
		std::vector<Species*> _Species;


	};

}

#endif