#ifndef GENOME_H
#define GENOME_H

#include <vector>

#include "man/Gene.h"

namespace neat
{
	//! Pairs a gene and properties.
	struct GeneData {
		Gene* gene = nullptr;
		GeneProperties props;
	};

	/**
		A grouping of genes and associated fitness data.
	*/
	class Genome
	{

	public:
		
		//! Constructor
		Genome() = default;

		//! Copy Constructor
		Genome(Genome* g);

		//! Destructor
		virtual ~Genome() = default;


		///
		/// Genome
		///

		//! Adds a gene with given properties.
		GeneData& AddGene(Gene* gene, const GeneProperties& props);

		//! Adds a gene with default properties.
		GeneData& AddGene(Gene* gene);

		//! Check for an already existing gene.
		bool ContainsGene(int fromNode, int toNode) const;

		//! Sets the fitness.
		void SetFitness(double fit);

		//! The fitness.
		double GetFitness() const;

		//! Gets gene data by reference.
		std::vector<GeneData>& GetGeneData();

		//! Sorts the genes according to the gene id.
		void SortGenes();

	private:

		std::vector<GeneData> _GeneData;
		double _Fitness = -1.0;
		bool _IsSorted = true;
	};
}

#endif