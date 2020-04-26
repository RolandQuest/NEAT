#include "neat.h"

#include <tuple>

#include "liv/Genome.h"
#include "alts/AlterationHub.h"

namespace neat
{
	///
	/// NEAT private members.
	///

	int _Generation = 0;

	///
	/// Interface into system.
	///

	void init(int inputNodes, int outputNodes) {

		reset();

		CurrentPopulation = new Population();

		//Record the nodes.
		NodePool.CreateNode(NodeType::BIAS);
		for (size_t i = 0; i < inputNodes; i++) {
			NodePool.CreateNode(NodeType::SENSOR);
		}
		for (size_t i = 0; i < outputNodes; i++) {
			NodePool.CreateNode(NodeType::OUTPUT);
		}

		//Adding +1 for the bias.
		inputNodes++;

		//For selecting random nodes and weights.
		std::uniform_int_distribution<int> distOutput(0, outputNodes - 1);
		std::uniform_int_distribution<int> distInput(0, inputNodes - 1);
		std::uniform_real_distribution<double> distWeight(-InitialConnectionWeightMax, InitialConnectionWeightMax);

		for (int gi = 0; gi < PopulationSize; gi++) {

			//<input node, output node> pairs
			std::vector< std::pair<int, int> > initConnections;

			//Connect to one random output from each input.
			for (int i = 0; i < inputNodes; i++) {
				initConnections.push_back(std::make_pair(i, inputNodes + distOutput(Rando)));
			}

			//Connect disconnected output nodes to a random input node.
			for (int i = 0; i < outputNodes; i++) {

				//Skip if output already has a connection.
				bool found = false;
				for (size_t j = 0; j < inputNodes; j++) {
					if (initConnections[j].second == inputNodes + i) {
						found = true;
						break;
					}
				}
				if (!found) {
					initConnections.push_back(std::make_pair(distInput(Rando), inputNodes + i));
				}
			}

			Genome* genome = new Genome();

			for (auto& con : initConnections) {

				Gene* gene;
				if (!GenePool.Find(gene, con.first, con.second)) {

					//Record the gene.
					GenePool.Create(gene, con.first, con.second);

					//Record the innovation.
					Innovation* innov;
					InnovationPool.Create(innov, con.first, con.second);
				}

				//Initialize and add to the genome.
				GeneData& p = genome->AddGene(gene);
				p.props.weight = distWeight(Rando);
			}

			CurrentPopulation->AddGenome(genome);
		}

	}

	void iterateGeneration() {

		Population* newPopulation;
		AlterationHub::CreateNextGeneration(_Generation, CurrentPopulation, newPopulation);

		delete CurrentPopulation;
		CurrentPopulation = newPopulation;

		_Generation++;
	}

	void reset() {
		InnovationPool.Nuke();
		GenePool.Nuke();
		NodePool.Nuke();
		AlterationHub::Nuke();
		//clearHistory();
		delete CurrentPopulation;
		_Generation = 0;
	}

	/*
	void clearHistory() {

		//for (auto& entry : PopulationHistory) {
			//delete entry;
		//}
		//PopulationHistory.clear();
	}

	Population* lastGeneration() {
		//return PopulationHistory[PopulationHistory.size() - 1];
	}
	*/

	int generationCount() {
		return _Generation;
	}


}