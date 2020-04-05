#ifndef SPECIES_H
#define SPECIES_H

#include <vector>

#include "Genome.h"

namespace neat
{
	class Species
	{

	public:

		///
		/// ctors/dtors
		///

		//! Constructor
		Species() = default;

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
		const std::vector<Genome*>& Genomes();

		///
		/// Species Static
		///

		//!
		static double Delta(Genome* g1, Genome* g2);

	private:

		std::vector<Genome*> _Genomes;


	};
}


#endif