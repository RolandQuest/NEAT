#include "NodeManager.h"

namespace neat
{
	int NodeManager::CreateNode(NodeType type) {

		Node* n = new Node(type);
		_AllNodes.push_back(n);

		switch (type) {

		case NodeType::SENSOR:
			_InputNodes.push_back(n);
			break;

		case NodeType::HIDDEN:
			_HiddenNodes.push_back(n);
			break;

		case NodeType::OUTPUT:
			_OutputNodes.push_back(n);
			break;
		}

		return _AllNodes.size() - 1;
	}
	
	const std::vector<Node*>& NodeManager::InputNodes() {
		return _InputNodes;
	}

	const std::vector<Node*>& NodeManager::OutputNodes() {
		return _OutputNodes;
	}

	const std::vector<Node*>& NodeManager::HiddenNodes() {
		return _HiddenNodes;
	}

	const std::vector<Node*>& NodeManager::AllNodes() {
		return _AllNodes;
	}

	void NodeManager::Nuke(){
		
		for (auto& node : _AllNodes) {
			delete node;
		}
		_AllNodes.clear();
		_InputNodes.clear();
		_OutputNodes.clear();
		_HiddenNodes.clear();
	}

}