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
		
	*/
	class Node
	{

	public:

		//! Constructor
		Node(NodeType type);

		//! Destructor
		virtual ~Node() = default;

		//!
		NodeType Type();

		//!
		void SetIncomingValue(double val);

		//! 
		void AddToIncomingValue(double val);

		//!
		double Activate();

		//!
		double ActivatedValue();

		//!
		void Reset();

	private:

		NodeType _Type;
		double _IncomingValue = 0.0;
		double _ActivatedValue = 0.0;
	};
}



#endif