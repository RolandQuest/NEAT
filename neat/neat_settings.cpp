#include "neat_settings.h"

#include <time.h>

namespace neat
{
	///
	/// Common Objects
	///

	std::mt19937 Rando(time(0));

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
