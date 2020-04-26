#ifndef GENEMANAGER_H
#define GENEMANAGER_H

#include <vector>

#include "Gene.h"

namespace neat
{
	//! Has ownership of all created genes.
	class GeneManager
	{

	public:

		//! Constructor
		GeneManager();

		//! Destructor
		virtual ~GeneManager();


		//! Locates a gene with given input/ouput nodes.
		bool Find(Gene*& container, int inNode, int outNode);

		//! Creates a new gene.
		bool Create(Gene*& container, int inNode, int outNode);

		//! Completely resets the manager.
		void Nuke();

	private:

		//! Complete gene pool.
		std::vector<Gene*> _GenePool;

		//! Innovation increment.
		int _GeneIdIncrementer = 0;

	};
}

#endif