#include "Population.h"

#include "neat.h"

namespace neat
{
	Population::Population(int genBorn) : ILifeForm(genBorn) {
		_History = new PopulationHistory();
	}

	Population::~Population() {
		
		for (auto& spec : _Species) {
			delete spec;
		}
	}

	///
	/// ILifeForm
	///

	Population* Population::GrowOlder() {

		Population* ret = new Population(Born());

		PopulationHistory& newHistory = (PopulationHistory&)(*ret->_History);
		newHistory = GetHistory();
		newHistory.pastSelves.push_back(this);

		double curGenChampionFitness = _Species[0]->Champion()->GetFitness();
		if (curGenChampionFitness > newHistory.bestFitness) {
			newHistory.bestFitness = curGenChampionFitness;
			newHistory.ageOfBestFitness = newHistory.pastSelves.size() - 1;
		}

		for (auto& spec : _Species) {
			ret->GetSpecies().push_back(spec->GrowOlder());
		}

		return ret;
	}

	const PopulationHistory& Population::GetHistory() const {
		return (PopulationHistory&)*_History;
	}

	///
	/// Population
	///

	void Population::AddGenome(Genome* g) {

		for (auto& spec : _Species) {

			if (spec->Delta(g) < SpeciationDeltaThresh) {
				spec->AddGenome(g);
				return;
			}
		}

		Species* s = new Species(Born(), g);
		s->AddGenome(g);
		_Species.push_back(s);
	}

	std::vector<Species*>& Population::GetSpecies() {
		return _Species;
	}

	std::vector<Genome*> Population::GetGenomes() {

		std::vector<Genome*> ret;
		for (auto& spec : _Species) {
			ret.insert(std::end(ret), std::begin(spec->Genomes()), std::end(spec->Genomes()));
		}

		return ret;
	}

	size_t Population::SpeciesCount() {
		return _Species.size();
	}

	void Population::SettleDown() {

		for (auto& spec : _Species) {
			spec->SortByFitness();
		}

		std::sort(std::begin(_Species), std::end(_Species),
			[](Species* c1, Species* c2) {
				return c1->Champion()->GetFitness() < c2->Champion()->GetFitness();
			});
	}

}