#include "neat.h"

#include <vector>
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

		CurrentPopulation = new Population(_Generation);

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
				if (!GenePool.FindGene(gene, con.first, con.second)) {

					//Record the gene.
					gene = GenePool.CreateGene(con.first, con.second);

					//Record the innovation.
					Innovation* innov = new Innovation(con.first, con.second);
					InnovationPool.Register(innov);
				}

				//Initialize and add to the genome.
				GeneData& p = genome->AddGene(gene);
				p.props.weight = distWeight(Rando);
			}

			CurrentPopulation->AddGenome(genome);
		}

	}

	void iterateGeneration() {

		CurrentPopulation->SettleDown();

		//Population* newPopulation;
		//AlterationHub::CreateNextGeneration(_Generation, CurrentPopulation, newPopulation);

		//CurrentPopulation = new Population;

		_Generation++;
	}

	void reset() {
		InnovationPool.Nuke();
		GenePool.Nuke();
		NodePool.Nuke();
		AlterationHub::Nuke();
		clearHistory();
		delete CurrentPopulation;
		_Generation = 0;
	}

	void clearHistory() {

		//for (auto& entry : PopulationHistory) {
			//delete entry;
		//}
		//PopulationHistory.clear();
	}

	Population* lastGeneration() {
		//return PopulationHistory[PopulationHistory.size() - 1];
	}

	int generationCount() {
		return _Generation;
	}

	///
	/// Common objects.
	///

	std::mt19937 Rando(time(0));
	InnovationManager InnovationPool;
	GeneManager GenePool;
	NodeManager NodePool;
	Population* CurrentPopulation;

	///
	/// Population Settings
	///

	int PopulationSize = 100;

	///
	/// Weight Settings
	///

	double InitialConnectionWeightMax = 2.0;
	double ConnectionWeightMax = 8.0;

	///
	/// Speciation Settings
	///

	double SpeciationDeltaThresh = 8.0;
	double CompatExcessCoeff = 1.0;
	double CompatDisjointCoeff = 1.0;
	double CompatWeightCoeff = 1.0;

}