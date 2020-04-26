#include "GeneManager.h"

#include <iostream>

namespace neat
{

	GeneManager::GeneManager() {
		_GenePool.reserve(1000);
	}

	GeneManager::~GeneManager() {
		Nuke();
	}

	bool GeneManager::Find(Gene*& gene, int inNode, int outNode) {

		for (auto& g : _GenePool) {
			
			if (g->InputNode() == inNode && g->OutputNode() == outNode) {
				gene = g;
				return true;
			}
		}
		return false;
	}

	bool GeneManager::Create(Gene*& container, int inNode, int outNode) {

		if (Find(container, inNode, outNode)) {
			return false;
		}

		container = new Gene(inNode, outNode, _GeneIdIncrementer);
		_GenePool.push_back(container);
		_GeneIdIncrementer++;
		return true;
	}

	void GeneManager::Nuke() {

		for (auto& gene : _GenePool) {
			delete gene;
		}
		_GenePool.clear();
		_GeneIdIncrementer = 0;
	}

}