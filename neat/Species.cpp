#include "Species.h"

#include <math.h>

#include "neat.h"

namespace neat
{

	Species::~Species() {

		for (auto& g : _Genomes) {
			delete g;
		}
	}

	///
	/// Species
	///

	double Species::SharedFitness() {

		double total = 0.0;

		for (auto& genome : _Genomes) {
			total += genome->Fitness();
		}

		return total / _Genomes.size();
	}

	void Species::AddGenome(Genome* g) {
		_Genomes.push_back(g);
	}

	const std::vector<Genome*>& Species::Genomes() {
		return _Genomes;
	}

	///
	/// Species Static
	///

	double Species::Delta(Genome* g1, Genome* g2) {

		int disjoint = 0;
		int excess = 0;
		int matching = 0;
		double totalWeightDiff = 0.0;

		const SortedGeneMap& g1Genes = g1->GeneMap();
		const SortedGeneMap& g2Genes = g2->GeneMap();
		auto g1End = std::end(g1Genes);
		auto g2End = std::end(g2Genes);
		auto g1Cur = std::begin(g1Genes);
		auto g2Cur = std::begin(g2Genes);

		while (g1Cur != g1End && g2Cur != g2End) {

			if (g1Cur == g1End) {
				excess++;
				g2Cur++;
				continue;
			}

			if (g2Cur == g2End) {
				excess++;
				g1Cur++;
				continue;
			}

			Gene* gene1 = g1Cur->first;
			Gene* gene2 = g2Cur->first;

			if (gene1->InnovationNumber() == gene2->InnovationNumber()) {
				totalWeightDiff += abs(g1Cur->second.weight - g2Cur->second.weight);
				matching++;
				g1Cur++;
				g2Cur++;
				continue;
			}

			disjoint++;

			if (gene1->InnovationNumber() < gene2->InnovationNumber()) {
				g1Cur++;
			}
			else {
				g2Cur++;
			}
		}

		double N = 1.0;

		if (g1Genes.size() >= 20 || g2Genes.size() >= 20) {
			N = fmax(g1Genes.size(), g2Genes.size());
		}

		return
			(CompatExcessCoeff * excess / N) +
			(CompatDisjointCoeff * disjoint / N) +
			(CompatWeightCoeff * totalWeightDiff / matching);
	}
}