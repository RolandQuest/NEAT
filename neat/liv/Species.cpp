#include "Species.h"

#include <math.h>

#include "neat_settings.h"

namespace neat
{
	Species::Species(Genome* templ) {
		_Template = templ;
	}

	Species::~Species() {

		for (auto& g : _Genomes) {
			delete g;
		}
		if (_DeleteTemplate) {
			delete _Template;
		}
	}

	///
	/// Species
	///
	/*
	double Species::SharedFitness() {

		double total = 0.0;

		for (auto& genome : _Genomes) {
			total += genome->GetFitness();
		}

		return total / _Genomes.size();
	}
	*/
	void Species::AddGenome(Genome* g) {
		_Genomes.push_back(g);
	}

	void Species::SortByFitness() {

		std::sort(std::begin(_Genomes), std::end(_Genomes),
			[](Genome* g1, Genome* g2) {
				return g1->GetFitness() > g2->GetFitness();
			});
	}

	Genome* Species::Champion() const {
		return _Genomes[0];
	}

	std::vector<Genome*>& Species::GetGenomes() {
		return _Genomes;
	}

	Species* Species::GetHollowClone(std::mt19937& rng) {

		std::uniform_int_distribution<size_t> dist(0, _Genomes.size() - 1);
		Species* ret = new Species(new Genome(_Genomes[dist(rng)]));
		ret->_Age = _Age + 1;
		ret->_AgeOfLastImprovement = _AgeOfLastImprovement;
		ret->_BestFitness = _BestFitness;
		ret->_DeleteTemplate = true;
		return ret;
	}

	int Species::GetAge() {
		return _Age;
	}

	int Species::GetAgeOfLastImprovement() {
		return _AgeOfLastImprovement;
	}

	void Species::SetAgeOfLastImprovement(int age) {
		_AgeOfLastImprovement = age;
	}

	double Species::GetBestFitness() {
		return _BestFitness;
	}

	void Species::SetBestFitness(double fitness) {
		_BestFitness = fitness;
	}

	double Species::Delta(Genome* wanderer) {
		return Delta(_Template, wanderer);
	}

	///
	/// Species Static
	///

	double Species::Delta(Genome* g1, Genome* g2) {

		int disjoint = 0;
		int excess = 0;
		int matching = 0;
		double totalWeightDiff = 0.0;

		g1->SortGenes();
		g2->SortGenes();

		const std::vector<GeneData>& g1Genes = g1->GetGeneData();
		const std::vector<GeneData>& g2Genes = g2->GetGeneData();
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

			Gene* gene1 = g1Cur->gene;
			Gene* gene2 = g2Cur->gene;

			if (gene1->GeneId() == gene2->GeneId()) {
				totalWeightDiff += abs(g1Cur->props.weight - g2Cur->props.weight);
				matching++;
				g1Cur++;
				g2Cur++;
				continue;
			}

			disjoint++;

			if (gene1->GeneId() < gene2->GeneId()) {
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