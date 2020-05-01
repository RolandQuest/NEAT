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
	}

	void Network::Initialize(const std::map<int, double>& input, std::map<int, double>& output) {

		Reset();

		bool keepGoing = true;
		while (keepGoing) {

			SetInput(input);
			Activate();
			GetOutput(output);

			keepGoing = false;
			for (auto& out : output) {

				if (out.second == 0.0) {
					keepGoing = true;
					break;
				}
			}
		}

	}

	void Network::SetInput(const std::map<int, double>& input) {

		for (auto& entry : input) {
			_Nodes[entry.first]->SetIncomingValue(entry.second);
			_Nodes[entry.first]->Activate();
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