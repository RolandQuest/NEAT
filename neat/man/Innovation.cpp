#include "man/Innovation.h"

namespace neat
{
	Innovation::Innovation(int from, int to, int newNodeId){

		_FromNode = from;
		_ToNode = to;
		_NewNode = newNodeId;
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