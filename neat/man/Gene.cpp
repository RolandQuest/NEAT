#include "Gene.h"

namespace neat
{
	Gene::Gene(int inNode, int outNode, int geneId) {
		_InputNode = inNode;
		_OutputNode = outNode;
		_GeneId = geneId;
	}

	int Gene::InputNode() const {
		return _InputNode;
	}

	int Gene::OutputNode() const {
		return _OutputNode;
	}

	int Gene::GeneId() const {
		return _GeneId;
	}
}

