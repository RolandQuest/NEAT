#include "Mutator.h"

#include <random>
#include <set>

#include "man/NodeManager.h"
#include "neat.h"

namespace neat
{


	bool Mutator::MutateRandom(Genome* orig, Genome*& child) {
		return false;
	}

	bool Mutator::MutateAddConnection(Genome* orig, Genome*& child) {

		int inputOffset = NodePool.InputNodes().size() + 1;

		std::set<int> availableFromNodes;
		std::set<int> availableToNodes;
		for (auto& con : orig->GetGeneData()) {

			availableFromNodes.insert(con.gene->InputNode());
			availableFromNodes.insert(con.gene->OutputNode());

			if (con.gene->InputNode() >= inputOffset) {
				availableToNodes.insert(con.gene->InputNode());
			}
			if (con.gene->OutputNode() >= inputOffset) {
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

			if (!orig->ContainsGene(fromNode, toNode)) {

				Gene* g;
				if (!GenePool.FindGene(g, fromNode, toNode)) {

					g = GenePool.CreateGene(fromNode, toNode);

					Innovation* innov = new Innovation(fromNode, toNode);
					InnovationPool.Register(innov);
				}

				child = new Genome(*orig);
				child->AddGene(g);
				return true;
			}

			attempts++;
		}

		return false;
	}

	bool Mutator::MutateAddNode(Genome* orig, Genome*& child) {

		//Find eligible connections to add node to.
		std::vector<GeneData*> availableCons;
		for (auto& entry : orig->GetGeneData()) {

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
		if (!InnovationPool.Find(innov, InnovationType::kNode, toSplitData.gene->InputNode(), toSplitData.gene->OutputNode())) {

			int newNodeId = NodePool.CreateNode(NodeType::HIDDEN);
			innov = new Innovation(toSplitData.gene->InputNode(), toSplitData.gene->OutputNode(), newNodeId);
			InnovationPool.Register(innov);
		}

		//The innovation and genes should line up... this might be ripe with simplifications.
		Gene* gene;
		child = new Genome(*orig);

		if (!GenePool.FindGene(gene, innov->From(), innov->NewNodeId())) {
			gene = GenePool.CreateGene(innov->From(), innov->NewNodeId());
		}
		child->AddGene(gene);
		if (!GenePool.FindGene(gene, innov->NewNodeId(), innov->To())) {
			gene = GenePool.CreateGene(innov->NewNodeId(), innov->To());
		}
		child->AddGene(gene);

		return true;
	}

}