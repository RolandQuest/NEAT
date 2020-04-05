#include "Population.h"

#include "neat.h"

namespace neat
{

	Population::~Population() {
		
		for (auto& spec : _Species) {
			delete spec;
		}
	}

	void Population::AddGenome(Genome* g) {

		for (auto& spec : _Species) {

			if (Species::Delta(g, spec->Genomes()[0]) < SpeciationDeltaThresh) {

				spec->AddGenome(g);
				return;
			}
		}

		Species* s = new Species();
		s->AddGenome(g);
		_Species.push_back(s);
	}

	std::vector<Genome*> Population::Genomes() {

		std::vector<Genome*> ret;
		for (auto& spec : _Species) {
			ret.insert(std::end(ret), std::begin(spec->Genomes()), std::end(spec->Genomes()));
		}

		return ret;
	}

	size_t Population::SpeciesCount() {
		return _Species.size();
	}

}