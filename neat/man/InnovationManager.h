#ifndef INNOVATIONMANAGER_H
#define INNOVATIONMANAGER_H

#include <vector>

#include "man/Innovation.h"

namespace neat
{

	/**
		Records the innovations from generation to generation.
	*/
	class InnovationManager
	{

	public:

		//! Constructor
		InnovationManager() = default;

		//! Destructor
		virtual ~InnovationManager() = default;


		//! Finds an innovation in the current generation.
		bool Find(Innovation*& storage, int from, int to, int newNodeId = -1);

		//! Register an innovation.
		bool Create(Innovation*& storage, int from, int to, int newNodeId = -1);

		//! Completely resets the manager.
		void Nuke();

	private:

		std::vector<Innovation*> _AllInnovations;

	};
}

#endif