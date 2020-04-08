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

		///
		/// ctors/dtors
		///

		//! Constructor
		NodeManager() = default;

		//! Destructor
		virtual ~NodeManager() = default;

		///
		/// Node Manager
		///

		//! 
		int CreateNode(NodeType type);

		//! 
		Node* CopyNode(size_t nodeId);

		//! 
		const std::vector<Node*>& InputNodes();

		//!
		const std::vector<Node*>& OutputNodes();

		//!
		const std::vector<Node*>& HiddenNodes();

		//! 
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