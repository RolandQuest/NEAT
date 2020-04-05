#include "GeneManager.h"

namespace neat
{

	GeneManager::GeneManager() {
		_GenePool.reserve(1000);
	}

	GeneManager::~GeneManager() {
		Nuke();
	}

	bool GeneManager::FindGene(Gene*& gene, int inNode, int outNode) {

		for (auto& g : _GenerationalGenePool) {
			
			if (g->InputNode() == inNode && g->OutputNode() == outNode) {
				gene = g;
				return true;
			}
		}
		return false;
	}

	Gene* GeneManager::CreateGene(int inNode, int outNode) {

		Gene* g = new Gene(inNode, outNode, _InnovationId);
		_GenerationalGenePool.push_back(g);
		_InnovationId++;
		return g;
	}

	void GeneManager::EndGeneration() {

		for (auto& gene : _GenerationalGenePool) {
			_GenePool.push_back(gene);
		}
		_GenerationalGenePool.clear();
	}

	void GeneManager::Nuke() {

		for (auto& gene : _GenePool) {
			delete gene;
		}
		for (auto& gene : _GenerationalGenePool) {
			delete gene;
		}
		_GenePool.clear();
		_GenerationalGenePool.clear();
		_InnovationId = 0;
	}
}