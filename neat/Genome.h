#ifndef GENOME_H
#define GENOME_H

#include <map>

#include "Gene.h"

using SortedGeneMap = std::map<neat::Gene*, neat::GeneProperties, neat::GeneComparator>;

namespace neat
{
	/**
	
	
	*/
	class Genome
	{

	public:

		///
		/// ctors/dtors
		///

		//! Constructor
		Genome() = default;

		//! Destructor
		virtual ~Genome() = default;

		
		///
		/// Genome
		///

		//!
		void AddGene(Gene* gene, GeneProperties& props);

		//! The fitness.
		double Fitness();

		//! 
		const SortedGeneMap& GeneMap();


	private:

		SortedGeneMap _Genes;

		double _Fitness = -1.0;
	};
}

#endif