#include "man/InnovationManager.h"

namespace neat
{

	bool InnovationManager::Find(Innovation*& storage, int from, int to, int newNodeId){
		
		for (auto& entry : _AllInnovations) {
			
			if (entry->NewNodeId() == newNodeId && from == entry->From() && to == entry->To()) {

				storage = entry;
				return true;
			}
		}
		return false;
	}

	bool InnovationManager::Create(Innovation*& storage, int from, int to, int newNodeId) {

		if (Find(storage, from, to, newNodeId)) {
			return false;
		}

		storage = new Innovation(from, to, newNodeId);
		_AllInnovations.push_back(storage);
		return true;
	}

	void InnovationManager::Nuke(){
		
		for (auto& innov : _AllInnovations) {
			delete innov;
		}
		_AllInnovations.clear();
	}


}