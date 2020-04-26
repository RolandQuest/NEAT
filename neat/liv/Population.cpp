#include "Population.h"

#include "neat_settings.h"

namespace neat
{
	Population::~Population() {
		
		for (auto& spec : _Species) {
			delete spec;
		}
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

		Species* s = new Species(g);
		s->AddGenome(g);
		_Species.push_back(s);
	}

	void Population::AddSpecies(Species* s) {
		_Species.push_back(s);
	}

	std::vector<Species*>& Population::GetSpecies() {
		return _Species;
	}

	std::vector<Genome*> Population::GetGenomes() {

		std::vector<Genome*> ret;
		for (auto& spec : _Species) {
			ret.insert(std::end(ret), std::begin(spec->GetGenomes()), std::end(spec->GetGenomes()));
		}

		return ret;
	}

	size_t Population::SpeciesCount() {
		return _Species.size();
	}

	void Population::SettleDown(int generation) {

		for (auto& spec : _Species) {
			spec->SortByFitness();

			//Originally done after determining no improvement.
			//This did not make sense to me so I am checking this now.
			if (spec->GetGenomes()[0]->GetFitness() > spec->GetBestFitness()) {
				spec->SetAgeOfLastImprovement(generation);
				spec->SetAgeOfLastImprovement(spec->GetGenomes()[0]->GetFitness());
			}
		}

		std::sort(std::begin(_Species), std::end(_Species),
			[](Species* c1, Species* c2) {
				return c1->Champion()->GetFitness() < c2->Champion()->GetFitness();
			});
	}

}