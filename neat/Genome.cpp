#include "Genome.h"

#include <algorithm>

namespace neat
{
	Genome::Genome(Genome& other) {

		_GeneData = other._GeneData;
		_IsSorted = other._IsSorted;
	}

	GeneData& Genome::AddGene(Gene* gene, const GeneProperties& props) {

		_GeneData.emplace_back();
		_GeneData[_GeneData.size() - 1].gene = gene;
		_GeneData[_GeneData.size() - 1].props = props;
		_IsSorted = false;
		return _GeneData[_GeneData.size() - 1];
	}

	GeneData& Genome::AddGene(Gene* gene) {

		_GeneData.emplace_back();
		_GeneData[_GeneData.size() - 1].gene = gene;
		_IsSorted = false;
		return _GeneData[_GeneData.size() - 1];
	}

	bool Genome::ContainsGene(int fromNode, int toNode) {

		for (const auto& con : _GeneData) {
			if (con.gene->InputNode() == fromNode && con.gene->OutputNode() == toNode) {
				return true;
			}
		}
		return false;
	}

	void Genome::SetFitness(double fit) {
		_Fitness = fit;
	}

	double Genome::Fitness() {
		return _Fitness;
	}

	std::vector<GeneData>& Genome::GetGeneData() {
		return _GeneData;
	}

	void Genome::SortGenes() {

		if (_IsSorted) {
			return;
		}

		std::sort(std::begin(_GeneData), std::end(_GeneData),
			[](const GeneData& g1, const GeneData& g2) {
				return g1.gene->GeneId() < g2.gene->GeneId();
			});

		_IsSorted = true;
	}
}