#ifndef GENOME_H
#define GENOME_H

#include <vector>

#include "Gene.h"

namespace neat
{
	//! Pairs a gene and properties.
	struct GeneData {
		Gene* gene;
		GeneProperties props;
	};

	/**
		
	*/
	class Genome
	{

	public:
		
		//! Constructor
		Genome() = default;

		//! Copy constructor
		Genome(Genome& other);

		//! Destructor
		virtual ~Genome() = default;


		//! Adds a gene with given properties.
		GeneData& AddGene(Gene* gene, const GeneProperties& props);

		//! Adds a gene with default properties.
		GeneData& AddGene(Gene* gene);

		//! Check for an already existing gene.
		bool ContainsGene(int fromNode, int toNode);

		//! Sets the fitness.
		void SetFitness(double fit);

		//! The fitness.
		double Fitness();

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