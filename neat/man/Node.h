#ifndef NODE_H
#define NODE_H

namespace neat
{
	//! Types of nodes in a network.
	enum class NodeType : int {
		BIAS,
		SENSOR,
		HIDDEN,
		OUTPUT
	};

	/**
		A node in the neural network.

		TODO: Abstract activation functions away.
	*/
	class Node
	{

	public:

		//! Constructor
		Node(NodeType type);

		//! Destructor
		virtual ~Node() = default;

		//! Returns the node type.
		NodeType Type();

		//! Sets the incoming value to be activated.
		void SetIncomingValue(double val);

		//! Adds to the incoming value to be activated.
		void AddToIncomingValue(double val);

		//! Activates the incoming value and returns the result.
		double Activate();

		//! Returns the activated value.
		double ActivatedValue();

		//! Resets incoming/activated values to 0.
		void Reset();

	private:

		NodeType _Type;
		double _IncomingValue = 0.0;
		double _ActivatedValue = 0.0;
	};
}



#endif