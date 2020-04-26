#ifndef INNOVATION_H
#define INNOVATION_H

namespace neat
{
	/**
		An invariant class for innovations.
		A new node innovation represents splitting of a link into two others.
		A new link represents connecting two nodes not previously connected.
	*/
	class Innovation
	{

	public:

		//! Constructor for a new link innovation.
		Innovation(int from, int to, int newNodeId = -1);

		//! Destructor.
		virtual ~Innovation() = default;


		//! Returns the 'from' node.
		int From();

		//! Returns the 'to' node.
		int To();

		//! Returns the node id of a new node.
		int NewNodeId();

	private:

		int _FromNode = -1;
		int _ToNode = -1;
		int _NewNode = -1;

	};

}

#endif