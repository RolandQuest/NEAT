#include "Genome.h"

namespace neat
{
	void Genome::AddGene(Gene* gene, GeneProperties& props) {

		if (_Genes.find(gene) == std::end(_Genes)) {
			//Uh oh
		}
		_Genes[gene] = props;
	}

	double Genome::Fitness() {
		return _Fitness;
	}

	const SortedGeneMap& Genome::GeneMap() {
		return _Genes;
	}
}