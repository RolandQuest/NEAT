#include "Gene.h"

namespace neat
{
	Gene::Gene(int inNode, int outNode, int innovationNum) {
		_InputNode = inNode;
		_OutputNode = outNode;
		_InnovationNumber = innovationNum;
	}

	int Gene::InputNode() const {
		return _InputNode;
	}

	int Gene::OutputNode() const {
		return _OutputNode;
	}

	int Gene::InnovationNumber() const {
		return _InnovationNumber;
	}
}

