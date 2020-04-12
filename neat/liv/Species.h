#ifndef SPECIES_H
#define SPECIES_H

#include <vector>

#include "ILifeForm.h"
#include "Genome.h"

namespace neat
{
	class Species;

	//! Tracks historical information regarding a species.
	struct SpeciesHistory : public IHistory {
		std::vector<Species*> pastSelves;
		double bestFitness_champ = 0.0;
		double bestFitness_shared = 0.0;
		int ageOfBestFitness_champ = 0;
		int ageOfBestFitness_shared = 0;
	};

	/**
		A group of genomes that are similar in topography.
	*/
	class Species : public ILifeForm
	{

	public:

		//! Constructor
		Species(int genBorn, Genome* templ);

		//! Destructor
		virtual ~Species();


		///
		/// ILifeFrom
		///

		//! Tells the lifeform to handle aging by 1 generation.
		Species* GrowOlder();

		//! Returns the history of this lifeform.
		const SpeciesHistory& GetHistory() const;


		///
		/// Species
		///

		//! Calculates the shared fitness of the species.
		double SharedFitness();

		//! 
		void AddGenome(Genome* g);

		//! 
		void SortByFitness();

		//!
		Genome* Champion() const;

		//! 
		std::vector<Genome*>& GetGenomes();

		//!
		double Delta(Genome* wanderer);

		//!
		static double Delta(Genome* g1, Genome* g2);

	private:

		Genome* _Template;

		std::vector<Genome*> _Genomes;
	};
}


#endif