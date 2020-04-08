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

	bool GeneManager::FindGene(Gene*& gene, int inNode, int outNode) {

		for (auto& g : _GenePool) {
			
			if (g->InputNode() == inNode && g->OutputNode() == outNode) {
				gene = g;
				return true;
			}
		}
		return false;
	}

	Gene* GeneManager::CreateGene(int inNode, int outNode) {

		Gene* g = new Gene(inNode, outNode, _GeneIdIncrementer);
		_GenePool.push_back(g);
		_GeneIdIncrementer++;
		return g;
	}

	void GeneManager::Nuke() {

		for (auto& gene : _GenePool) {
			delete gene;
		}
		_GenePool.clear();
		_GeneIdIncrementer = 0;
	}

}