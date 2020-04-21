#ifndef NEAT_SETTINGS_H
#define NEAT_SETTINGS_H

#include <random>

namespace neat
{
	///
	/// Common Objects
	///

	//! Rng used for the neat objects.
	extern std::mt19937 Rando;

	///
	/// Population Settings
	///

	//! The size of the poplulation to use.
	extern int PopulationSize;

	///
	/// Weight Settings
	///

	//! The max absolute value of a connection's initial weight.
	extern double InitialConnectionWeightMax;
	//! The max absolute value of a connection's weight.
	extern double ConnectionWeightMax;

	///
	/// Speciation Settings
	///

	//! Speciation delta thresh
	extern double SpeciationDeltaThresh;
	//! Speciation coefficient for Excess genes.
	extern double CompatExcessCoeff;
	//! Speciation coefficient for Disjoint genes.
	extern double CompatDisjointCoeff;
	//! Speciation coefficient for average weights of common genes.
	extern double CompatWeightCoeff;

}

#endif