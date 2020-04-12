#ifndef ILIFEFORM_H
#define ILIFEFORM_H

namespace neat
{
	//! Empty interface to force life forms to create their own history types.
	struct IHistory {

	};

	/**
		Tracks the age of a lifeform.
	*/
	class ILifeForm
	{

	public:

		//! Constructor marking the birth of life!
		ILifeForm(int curGen);

		//! Destructor
		virtual ~ILifeForm();

		//! Tells the lifeform to handle aging by 1 generation.
		virtual ILifeForm* GrowOlder() = 0;

		//! Returns the history of this lifeform.
		virtual const IHistory& GetHistory() const = 0;

		//! Marks the time of death.
		void CallIt(int curGen);

		//! Returns the generation born.
		int Born();

		//! Returns the generation deceased.
		int Deceased();

		//! Checks if the lifeform is deceased or not.
		bool CheckPulse();

	protected:

		//! The history of the lifeform.
		IHistory* _History = nullptr;

	private:

		int _GenerationBorn = -1;
		int _GenerationDeceased = -1;
	};

}

#endif