#include "Node.h"

#include <math.h>

namespace neat
{
	Node::Node(NodeType type) {
		_Type = type;
	}

	NodeType Node::Type() {
		return _Type;
	}

	void Node::SetIncomingValue(double val) {
		_IncomingValue = val;
	}

	void Node::AddToIncomingValue(double val) {
		_IncomingValue += val;
	}

	double Node::Activate() {

		switch (_Type) {

		case NodeType::BIAS:
		case NodeType::SENSOR:
			_ActivatedValue = _IncomingValue;
			break;

		case NodeType::HIDDEN:
			_ActivatedValue = 1 + exp(_IncomingValue);
			_ActivatedValue = log(_ActivatedValue);
			break;

		case NodeType::OUTPUT:
			_ActivatedValue = 1 + exp(-_IncomingValue);
			_ActivatedValue = 1 / _ActivatedValue;
			break;
		}

		return _ActivatedValue;
	}

	double Node::ActivatedValue() {
		return _ActivatedValue;
	}

	void Node::Reset() {
		_ActivatedValue = 0;
		_IncomingValue = 0;
	}

}