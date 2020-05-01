#ifndef TRACKER_H
#define TRACKER_H

namespace neat
{
	class Tracker
	{

	public:

		Tracker() {
			count++;
		}

		Tracker(const Tracker& other) = delete;
		Tracker(Tracker& other) = delete;
		Tracker(const Tracker* other) = delete;
		Tracker(Tracker* other) = delete;

		~Tracker() {
			count--;
		}

		static int count;

	};
}

#endif