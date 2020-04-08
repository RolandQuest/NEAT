#include "innov/InnovationManager.h"

namespace neat
{

	void InnovationManager::Register(Innovation* innov) {
		_AllInnovations.push_back(innov);
	}

	bool InnovationManager::Find(Innovation*& storage, InnovationType type, int from, int to){
		
		for (auto& entry : _AllInnovations) {
			
			if (entry->Type() == type && from == entry->From() && to == entry->To()) {

				storage = entry;
				return true;
			}
		}
		return false;
	}

	void InnovationManager::Nuke(){
		
		for (auto& innov : _AllInnovations) {
			delete innov;
		}
		_AllInnovations.clear();
	}


}