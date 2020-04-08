#ifndef INNOVATIONMANAGER_H
#define INNOVATIONMANAGER_H

#include <vector>

#include "innov/Innovation.h"

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

		//! Register an innovation.
		void Register(Innovation* innov);

		//! Finds an innovation in the current generation.
		bool Find(Innovation*& storage, InnovationType type, int from, int to);

		//! Completely resets the manager.
		void Nuke();

	private:

		std::vector<Innovation*> _AllInnovations;

	};
}

#endif