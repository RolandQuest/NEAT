#ifndef NETWORK_H
#define NETWORK_H

#include <map>

#include "neat_settings.h"
#include "man/Node.h"
#include "liv/Genome.h"

namespace neat
{
	/*
		A functioning network created with a genome.
	*/
	class Network
	{

	public:

		//! Constructs an uninitialized network.
		Network(Genome* genome);

		//! Destructor
		virtual ~Network() = default;


		//! Initializes the network for use.
		void Initialize();

		//! Sets the input of the network.
		void SetInput(const std::map<int, double>& input);

		//! Activates the network a number of times.
		void Activate(int times = 1);

		//! Stores all desired activated values.
		void GetOutput(std::map<int, double>& output);

		//! Resets the state to a pre-initialized state.
		void Reset();

		//! Sets the fitness of the genome.
		void SetFitness(double fitness);

	private:

		//! [nodeId] -> Node
		std::map<int, Node*> _Nodes;

		Genome* _Genome;
	};

}

#endif