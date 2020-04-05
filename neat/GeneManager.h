#ifndef GENEMANAGER_H
#define GENEMANAGER_H

#include <vector>

#include "Gene.h"

namespace neat
{

	/**
		Has ownership of all created genes.

	*/
	class GeneManager
	{

	public:

		///
		/// ctors/dtors
		///

		//! Constructor
		GeneManager();

		//! Destructor
		virtual ~GeneManager();

		///
		/// Gene Manager
		///

		//!
		bool FindGene(Gene*& gene, int inNode, int outNode);

		//! 
		Gene* CreateGene(int inNode, int outNode);

		//! Ends the generation for newly created genes.
		void EndGeneration();

		//! Completely resets the manager.
		void Nuke();

	private:

		//! Complete gene pool.
		std::vector<Gene*> _GenePool;

		//! Generation gene pool.
		std::vector<Gene*> _GenerationalGenePool;

		//! Innovation increment
		int _InnovationId = 0;

	};
}

#endif