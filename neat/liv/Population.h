#ifndef POPULATION_H
#define POPULATION_H

#include <vector>

#include "Genome.h"
#include "Species.h"

namespace neat
{
	/**
		An entire group of genomes divided into their relative species.
	*/
	class Population
	{

	public:

		//! Constructor
		Population() = default;

		//! Destructor
		virtual ~Population();


		//! Adds a genome to the first relative species.
		void AddGenome(Genome* g);

		//! Adds an entire species to the population.
		void AddSpecies(Species* s);

		//! Returns all the species.
		std::vector<Species*>& GetSpecies();

		//! Creates and returns a vector of all genomes.
		std::vector<Genome*> GetGenomes();

		//! Returns the number of species.
		size_t SpeciesCount();

		//! Sorts and records fitness information for all species.
		void SettleDown(int generation);

	private:

		//! The entire population.
		std::vector<Species*> _Species;


	};

}

#endif