#include "Breeder.h"

#include <random>

#include "neat.h"

namespace neat
{

	bool Breeder::Breed(Genome* mother, Genome* father, Genome*& child) {

		mother->SortGenes();
		father->SortGenes();

		Genome* strong;
		Genome* weak;

		if (mother->GetFitness() > father->GetFitness()) {
			strong = mother;
			weak = father;
		}
		else {
			strong = father;
			weak = mother;
		}

		//Choice between mother and father.
		std::uniform_int_distribution<int> dist(0, 1);

		auto stCur = std::begin(strong->GetGeneData());
		auto weCur = std::begin(weak->GetGeneData());
		auto stEnd = std::end(strong->GetGeneData());
		auto weEnd = std::end(weak->GetGeneData());
		child = new Genome();

		while (stCur != stEnd) {

			//Excess
			if (weCur == weEnd) {
				child->AddGene(stCur->gene, stCur->props);
				stCur++;
				continue;
			}

			//Weak Disjoint
			if (weCur->gene->GeneId() < stCur->gene->GeneId()) {
				weCur++;
				continue;
			}

			//Strong Disjoint
			if (weCur->gene->GeneId() > stCur->gene->GeneId()) {
				child->AddGene(stCur->gene, stCur->props);
				stCur++;
				continue;
			}

			//Matching
			if (weCur->gene->GeneId() == stCur->gene->GeneId()) {

				//Don't add a frozen gene if the stronger is frozen.
				if (stCur->props.frozen) {
					stCur++;
					weCur++;
					continue;
				}

				//Weak frozen and not strong... add the strong.
				if (weCur->props.frozen) {
					child->AddGene(stCur->gene, stCur->props);
					stCur++;
					weCur++;
					continue;
				}

				//Otherwise add a random one.
				if ((bool)dist(Rando)) {
					child->AddGene(stCur->gene, stCur->props);
				}
				else {
					child->AddGene(weCur->gene, weCur->props);
				}
				stCur++;
				weCur++;
				continue;
			}

		}

		return true;
	}


}