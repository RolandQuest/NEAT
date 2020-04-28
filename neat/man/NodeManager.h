#ifndef NODEMANAGER_H
#define NODEMANAGER_H

#include <vector>

#include "Node.h"

namespace neat
{

	/**
		Has ownership of all created nodes.
	*/
	class NodeManager
	{

	public:

		//! Constructor
		NodeManager() = default;

		//! Destructor
		virtual ~NodeManager() = default;


		//! Creates a new node.
		int CreateNode(NodeType type);

		//! Returns the node with given Id.
		Node* GetNode(int nodeId);

		//! Returns all available input nodes.
		const std::vector<Node*>& InputNodes();

		//! Returns all available output nodes.
		const std::vector<Node*>& OutputNodes();

		//! Returns all available hidden nodes.
		const std::vector<Node*>& HiddenNodes();

		//! Returns all available nodes.
		const std::vector<Node*>& AllNodes();

		//! Completely resets the manager.
		void Nuke();

	private:

		std::vector<Node*> _InputNodes;
		std::vector<Node*> _OutputNodes;
		std::vector<Node*> _HiddenNodes;
		std::vector<Node*> _AllNodes;
	};
}

#endif