#include "AlterationHub.h"

#include <map>
#include <set>

#include "neat_settings.h"

namespace neat
{

	double AlterationHub::bestFitness = 0.0;
	int AlterationHub::bestFitnessGeneration = 0;

	void AlterationHub::CreateNextGeneration(int curGen, Population* currentPopulation, Population*& newPopulation) {

		std::vector<Species*>& specs = currentPopulation->GetSpecies();

		///
		/// Record population level data.
		///

		currentPopulation->SettleDown(curGen);
		Genome* popChampion = specs[0]->Champion();

		if (popChampion->GetFitness() > bestFitness) {
			bestFitness = popChampion->GetFitness();
			bestFitnessGeneration = curGen;
		}

		///
		/// Competitive Coevolution Stagnation Detection
		///

		if ((curGen + 1) % CCS_Generations) {

			for (auto it = std::end(specs) - 1; it != std::begin(specs); --it) {

				if ((*it)->GetAge() >= 20) {
					specs.erase(it);
					delete (*it);
					break;
				}
			}
		}

		///
		/// Species Age Death
		///

		auto remSpecEnd = std::remove_if(std::begin(specs), std::end(specs), [](Species* s) {
			// -1 used to be true to original algorithm. Doesn't make much sense to me.
			// See Species::adjust_fitness() for original functionality.
			return s->GetAge() - s->GetAgeOfLastImprovement() >= SpeciesDropOffAge - 1;
		});

		for (auto it = remSpecEnd; it < std::end(specs); ++it) {

			for (auto& entry : (*it)->GetGenomes()) {
				delete entry;
			}
			delete* it;
		}
		specs.erase(remSpecEnd, std::end(specs));

		///
		/// Species age significance, fitness sharing, and killing of weaker genomes.
		///

		for (auto& spec : specs) {

			std::vector<Genome*>& genomes = spec->GetGenomes();
			int numParents = SpeciesNumberOfParentsPercent * (genomes.size() + 1);

			for (size_t gIndex = 0; gIndex < genomes.size(); ++gIndex) {

				Genome* g = genomes[gIndex];

				//Kill non parents.
				if (gIndex >= numParents) {
					delete g;
					continue;
				}

				//Don't allow negative fitness.
				if (g->GetFitness() < 0.0) {
					g->SetFitness(0.001);
				}

				//Age significance.
				if (spec->GetAge() <= SpeciesAgeOfSignificanceThresh) {
					g->SetFitness(g->GetFitness() * SpeciesAgeOfSignificanceBonus);
				}

				//Sharing with species.
				g->SetFitness(g->GetFitness() / spec->GetGenomes().size());
			}

			genomes.erase(std::begin(genomes) + numParents, std::end(genomes));
		}

		///
		/// Expected children of each species.
		///

		std::map<Species*, int> expectedChildren;

		double avg_fitness = 0.0;
		for (auto& g : currentPopulation->GetGenomes()) {
			avg_fitness += g->GetFitness();
		}
		avg_fitness /= (double) PopulationSize;

		//Possibility of expected children being thrown off because of premature killing.
		//Premature killing was not done in original algorithm.

		int total_expected = 0;
		double skim = 0.0;
		for (auto& spec : specs) {

			double expected = 0.0;
			for (auto& genome : spec->GetGenomes()) {
				expected += genome->GetFitness() / avg_fitness;
			}

			expectedChildren[spec] = (int)expected;

			if (skim >= 1.0) {
				total_expected++;
				expectedChildren[spec]++;
				skim -= 1.0;
			}

			total_expected += (int)expected;
			skim += expected - (int)expected;
		}

		if (total_expected < PopulationSize) {

			//Find species with most expecting.
			Species* best_species;
			int max_expected = 0;
			for (auto& specExpPair : expectedChildren) {

				if (specExpPair.second > max_expected) {
					best_species = specExpPair.first;
					max_expected = specExpPair.second;
				}
			}

			expectedChildren[best_species]++;
			total_expected++;

			if (total_expected < PopulationSize) {

				expectedChildren = { { best_species, PopulationSize } };

				std::remove_if(std::begin(specs), std::end(specs), [best_species](Species* s) {

					if (s != best_species) {
						delete s;
						return true;
					}
					return false;
					});

				specs.resize(1);
			}
		}

		/*
			Need to implement Population level stagnation and delta coding.
			population.cpp lines 578 - 631 abouts.
			Also skipping stolen babies code.
		*/

		///
		/// Create new population ready for next generation.
		///

		newPopulation = new Population();

		for (auto& spec : specs) {
			newPopulation->AddSpecies(spec->GetHollowClone(Rando));
		}

		///
		/// Reproduction + Mutation
		/// Ignoring special champion rules.
		///

		for (auto& specExpPair : expectedChildren) {

			Species* spec = specExpPair.first;
			std::vector<Genome*>& genomes = spec->GetGenomes();
			int expected = specExpPair.second;

			for (size_t i = 0; i < expected; i++) {

				std::uniform_int_distribution<int> temp(0, genomes.size() - 1);
				double prob = ProbabilitySpace(Rando);

				if (prob < MutateOnlyProbability) {

					std::uniform_int_distribution<int> temp(0, genomes.size() - 1);

					Genome* child;
					//Put in catch for failed attempt.
					Mutate(genomes[temp(Rando)], child);
					newPopulation->AddGenome(child);
					continue;
				}
				prob -= MutateOnlyProbability;

				//Put in interspecies mate rate.

				Genome* child;
				//Put in catch for failed breed.
				Breed(genomes[temp(Rando)], genomes[temp(Rando)], child);

				//Mutate if parents are the same.
				if (prob >= BreedOnlyProbability) {
					Genome* mutChild;
					Mutate(child, mutChild);
					delete child;
					child = mutChild;
				}

				newPopulation->AddGenome(child);
			}

		}

		///
		/// Clean up.
		///

		std::vector<Species*>& newSpecs = newPopulation->GetSpecies();
		for (int i = 0; i < newSpecs.size(); ++i) {
			Species* s = newSpecs[i];
			if (s->GetGenomes().size() == 0) {
				newSpecs.erase(std::begin(newSpecs) + i);
				delete s;
				i--;
			}
		}

	}

	bool AlterationHub::Mutate(Genome* orig, Genome*& child) {

		child = new Genome(orig);
		
		double prob = ProbabilitySpace(Rando);

		if (prob < MutateAddLinkProbability) {
			return MutateAddLink(child);
		}
		prob -= MutateAddLinkProbability;

		if (prob < MutateAddNodeProbability) {
			return MutateAddNode(child);
		}
		prob -= MutateAddNodeProbability;

		if (prob < MutateWeightsProbability) {
			return MutateWeights(child);
		}

		//Problem...
	}

	bool AlterationHub::MutateAddLink(Genome*& child) {

		int sensorOffset = NodePool.InputNodes().size() + 1;

		std::set<int> availableFromNodes;
		std::set<int> availableToNodes;
		for (auto& con : child->GetGeneData()) {

			availableFromNodes.insert(con.gene->InputNode());
			availableFromNodes.insert(con.gene->OutputNode());

			if (con.gene->InputNode() >= sensorOffset) {
				availableToNodes.insert(con.gene->InputNode());
			}
			if (con.gene->OutputNode() >= sensorOffset) {
				availableToNodes.insert(con.gene->OutputNode());
			}
		}

		std::uniform_int_distribution<int> distFrom(0, availableFromNodes.size() - 1);
		std::uniform_int_distribution<int> distTo(0, availableToNodes.size() - 1);

		int attempts = 0;
		while (attempts < 20) {

			auto it1 = std::begin(availableFromNodes);
			std::advance(it1, distFrom(Rando));
			int fromNode = *it1;

			auto it2 = std::begin(availableToNodes);
			std::advance(it2, distTo(Rando));
			int toNode = *it2;

			if (!child->ContainsGene(fromNode, toNode)) {

				Gene* g;
				if (!GenePool.Find(g, fromNode, toNode)) {

					GenePool.Create(g, fromNode, toNode);

					Innovation* innov;
					InnovationPool.Create(innov, fromNode, toNode);
				}

				child->AddGene(g);
				return true;
			}

			attempts++;
		}

		return false;
	}

	bool AlterationHub::MutateAddNode(Genome*& child) {

		//Find eligible connections to add node to.
		std::vector<GeneData*> availableCons;
		for (auto& entry : child->GetGeneData()) {

			if (!entry.props.frozen && entry.props.enabled) {
				availableCons.push_back(&entry);
			}
		}

		if (availableCons.size() == 0) {
			return false;
		}

		//Find the link and disconnect it.
		std::uniform_int_distribution<int> dist(0, availableCons.size() - 1);
		GeneData& toSplitData = *availableCons[dist(Rando)];
		toSplitData.props.frozen = true;

		//Handle innovation tracking.
		Innovation* innov;
		if (!InnovationPool.Find(innov, toSplitData.gene->InputNode(), toSplitData.gene->OutputNode(), toSplitData.gene->GeneId())) {

			int newNodeId = NodePool.CreateNode(NodeType::HIDDEN);
			InnovationPool.Create(innov, toSplitData.gene->InputNode(), toSplitData.gene->OutputNode(), newNodeId);
		}

		//The innovation and genes should line up... this might be ripe with simplifications.
		Gene* gene;

		GenePool.Create(gene, innov->From(), innov->NewNodeId());
		child->AddGene(gene);

		GenePool.Create(gene, innov->NewNodeId(), innov->To());
		child->AddGene(gene);

		return true;
	}

	bool AlterationHub::MutateWeights(Genome*& child) {

		std::vector<GeneData>& geneData = child->GetGeneData();

		//Need to expand on this greatly.
		for (auto& gene : geneData) {

			if (gene.props.enabled && !gene.props.frozen) {
				gene.props.weight *= randposneg() * MutateWeightMaxPower * ProbabilitySpace(Rando);
			}
		}
		return true;
	}

	bool AlterationHub::Breed(Genome* mother, Genome* father, Genome*& child) {

		child = new Genome();

		double prob = ProbabilitySpace(Rando);

		if (prob < BreedMultipointProbability) {
			return BreedMultipoint(mother, father, child);
		}
		prob -= BreedMultipointProbability;

		if (prob < BreedMultipointAverageProbability) {
			return BreedMultipointAverage(mother, father, child);
		}
		prob -= BreedMultipointAverageProbability;

		if (prob < BreedSinglepointProbability) {
			return BreedSinglepoint(mother, father, child);
		}

		//Problem...
	}

	bool AlterationHub::BreedMultipoint(Genome* mother, Genome* father, Genome*& child) {

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

	bool AlterationHub::BreedMultipointAverage(Genome* mother, Genome* father, Genome*& child) {
		return false;
	}

	bool AlterationHub::BreedSinglepoint(Genome* mother, Genome* father, Genome*& child) {
		return false;
	}

	void AlterationHub::Nuke() {

		bestFitness = 0.0;
		bestFitnessGeneration = 0;
	}
}