#ifndef SPECIES_H
#define SPECIES_H

#include <vector>
#include <random>

#include "Genome.h"

namespace neat
{
	/**
		A group of genomes that are similar in topography.
	*/
	class Species
	{

	public:

		//! Constructor
		Species(Genome* templ);

		//! Destructor
		virtual ~Species();


		//! Calculates the shared fitness of the species.
		//double SharedFitness();

		//! Adds a genome to the species.
		void AddGenome(Genome* g);

		//! Sorts the genomes in descending fitness.
		void SortByFitness();

		//! Returns the first genome in the species.
		Genome* Champion() const;

		//! Returns all genomes.
		std::vector<Genome*>& GetGenomes();

		//! Constructs a clone with no genomes.
		Species* GetHollowClone(std::mt19937& rng);

		//! Returns the age of the species (incremented by GetHollowClone).
		int GetAge();

		//! The generation of best fitness.
		int GetAgeOfLastImprovement();

		//! Sets the generation of best fitness.
		void SetAgeOfLastImprovement(int age);

		//! Returns the best fitness ever recorded.
		double GetBestFitness();

		//! Sets the best fitness.
		void SetBestFitness(double fitness);

		//! Finds the distance between the given genome and the template.
		double Delta(Genome* wanderer);

		//! Finds the distance between the two given genomes.
		static double Delta(Genome* g1, Genome* g2);

	private:

		Genome* _Template;
		bool _DeleteTemplate = false;

		std::vector<Genome*> _Genomes;

		int _Age = 0;
		int _AgeOfLastImprovement = 0;
		double _BestFitness = 0.0;
		
	};
}


#endif