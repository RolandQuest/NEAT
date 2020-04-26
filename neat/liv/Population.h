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
		void AddSpecies(Species* s);

		//!
		std::vector<Species*>& GetSpecies();

		//! 
		std::vector<Genome*> GetGenomes();

		//! 
		size_t SpeciesCount();

		//! 
		void SettleDown(int generation);

	private:

		//! The entire population.
		std::vector<Species*> _Species;


	};

}

#endif