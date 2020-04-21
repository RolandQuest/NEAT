#ifndef SPECIES_H
#define SPECIES_H

#include <vector>
#include <random>

#include "Genome.h"

namespace neat
{
	/**
		A group of genomes that are similar in topography.
	*/
	class Species
	{

	public:

		//! Constructor
		Species(Genome* templ);

		//! Destructor
		virtual ~Species();


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
		Species* GetHollowClone(std::mt19937& rng);

		//!
		double Delta(Genome* wanderer);

		//!
		static double Delta(Genome* g1, Genome* g2);

	private:

		Genome* _Template;

		std::vector<Genome*> _Genomes;

		int _Age = 0;
	};
}


#endif