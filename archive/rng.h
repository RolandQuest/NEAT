#ifndef RNG_H
#define RNG_H

#include <random>

#include "Tracker.h"

namespace neat
{
	class rng : public std::mt19937, public Tracker
	{
	public:

		rng(time_t t) : std::mt19937(t), Tracker() {

		}

		rng(const rng& other) = delete;
		rng(rng& other) = delete;
		rng(const rng* other) = delete;
		rng(rng* other) = delete;
	};
}

#endif