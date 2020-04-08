#ifndef GENE_H
#define GENE_H

namespace neat
{

	//! Unique properties of a Gene for a genome.
	struct GeneProperties
	{
		double weight = 1.0;
		bool frozen = false;
		bool enabled = true;
		bool reccurent = false;
	};

	/**
		Represents a topological innovation for the NEAT algorithm.
		Every Gene in a Genome will have an associated GeneProperties struct that
		is unique to that Genome.
	*/
	class Gene
	{

	public:


		///
		/// ctors/dtors
		///


		//! Constructor
		Gene(int inNode, int outNode, int geneId);

		//! Destructor
		virtual ~Gene() = default;


		///
		/// Gene
		///


		//! The input node.
		int InputNode() const;

		//! The output node.
		int OutputNode() const;

		//! The innovation number.
		int GeneId() const;

	private:

		int _InputNode;
		int _OutputNode;
		int _GeneId;

	};

	//! Used to sort genes by innovation number.
	struct GeneComparator
	{
		bool operator() (const Gene* g1, const Gene* g2) const {
			return g1->GeneId() < g2->GeneId();
		}
	};
}


#endif