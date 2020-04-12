
#include <iostream>

#include "neat.h"
#include "liv/Genome.h"
#include "alts/Mutator.h"


void GenomeTest() {

	neat::Genome* g2;
	neat::Genome* g = neat::CurrentPopulation->Genomes()[0];
	neat::Mutator::MutateAddConnection(g, g2);

	for (auto& entry : g->GetGeneData()) {

		std::cout
			<< entry.gene->GeneId() << '\t'
			<< entry.gene->InputNode() << '\t'
			<< entry.gene->OutputNode() << '\t'
			<< entry.props.weight << '\t'
			<< entry.props.enabled << '\t'
			<< entry.props.frozen << '\t'
			<< entry.props.reccurent << '\n';
	}

	for (auto& entry : g2->GetGeneData()) {

		std::cout
			<< entry.gene->GeneId() << '\t'
			<< entry.gene->InputNode() << '\t'
			<< entry.gene->OutputNode() << '\t'
			<< entry.props.weight << '\t'
			<< entry.props.enabled << '\t'
			<< entry.props.frozen << '\t'
			<< entry.props.reccurent << '\n';
	}
}

int main() {

	for (size_t i = 0; i < 10; i++) {

		neat::init(4, 4);
		neat::iterateGeneration();
		neat::iterateGeneration();
		neat::iterateGeneration();
		neat::iterateGeneration();
	}

	return 0;
}