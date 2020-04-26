#include "man/Innovation.h"

namespace neat
{
	Innovation::Innovation(int from, int to, int newNodeId){

		if (newNodeId != -1) {
			_Type = InnovationType::kNode;
			_NewNode = newNodeId;
		}
		_FromNode = from;
		_ToNode = to;
	}

	InnovationType Innovation::Type(){
		return _Type;
	}

	int Innovation::From(){
		return _FromNode;
	}

	int Innovation::To(){
		return _ToNode;
	}

	int Innovation::NewNodeId(){
		return _NewNode;
	}

}