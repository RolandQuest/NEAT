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

		//! Completely resets the manager.
		void Nuke();

	private:

		//! Complete gene pool.
		std::vector<Gene*> _GenePool;

		//! Innovation increment
		int _GeneIdIncrementer = 0;

	};
}

#endif