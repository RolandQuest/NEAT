#include "net/Network.h"

namespace neat
{
	Network::Network(Genome* genome) {

		_Genome = genome;

		for (auto& data : _Genome->GetGeneData()) {

			if (data.props.frozen || !data.props.enabled) {
				continue;
			}

			_Nodes[data.gene->InputNode()] = NodePool.GetNode(data.gene->InputNode());
			_Nodes[data.gene->OutputNode()] = NodePool.GetNode(data.gene->OutputNode());
		}

		Reset();
	}

	void Network::Initialize() {

		//TODO: This should be done smarter.
		for (size_t i = 0; i < 5; i++) {
			Activate();
		}
	}

	void Network::SetInput(const std::map<int, double>& input) {

		for (auto& entry : input) {
			_Nodes[entry.first]->SetIncomingValue(entry.second);
		}
	}

	void Network::Activate(int times) {

		for (; 0 < times; --times) {

			for (auto& data : _Genome->GetGeneData()) {

				if (data.props.frozen || !data.props.enabled) {
					continue;
				}

				Node* inNode = _Nodes[data.gene->InputNode()];
				Node* outNode = _Nodes[data.gene->OutputNode()];

				outNode->AddToIncomingValue(inNode->ActivatedValue() * data.props.weight);
			}

			for (auto& node : _Nodes) {
				node.second->Activate();
			}
		}

	}

	void Network::GetOutput(std::map<int, double>& output) {

		for (auto& entry : output) {
			entry.second = _Nodes[entry.first]->ActivatedValue();
		}
	}

	void Network::Reset() {

		for (auto& node : _Nodes) {
			node.second->Reset();
		}
	}

	void Network::SetFitness(double fitness) {
		_Genome->SetFitness(fitness);
	}


}