#ifndef POPULATION_H
#define POPULATION_H

#include <vector>

#include "ILifeForm.h"
#include "Genome.h"
#include "Species.h"

namespace neat
{
	class Population;

	//!
	struct PopulationHistory : public IHistory {
		std::vector<Population*> pastSelves;
		double bestFitness = 0.0;
		int ageOfBestFitness = 0;
	};

	/**

	*/
	class Population : public ILifeForm
	{

	public:

		//! Constructor
		Population(int genBorn);

		//! Destructor
		virtual ~Population();


		///
		/// ILifeFrom
		///

		//! Tells the lifeform to handle aging by 1 generation.
		Population* GrowOlder();

		//! Returns the history of this lifeform.
		const PopulationHistory& GetHistory() const;


		///
		/// Population
		///

		//! 
		void AddGenome(Genome* g);

		//!
		std::vector<Species*>& GetSpecies();

		//! 
		std::vector<Genome*> GetGenomes();

		//! 
		size_t SpeciesCount();

		//! 
		void SettleDown();

	private:

		//! The entire population.
		std::vector<Species*> _Species;


	};

}

#endif