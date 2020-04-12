#include "ILifeForm.h"

namespace neat
{
	ILifeForm::ILifeForm(int curGen) {
		_GenerationBorn = curGen;
	}

	ILifeForm::~ILifeForm() {
		delete _History;
	}

	void ILifeForm::CallIt(int curGen) {
		_GenerationDeceased = curGen;
	}

	int ILifeForm::Born() {
		return _GenerationBorn;
	}

	int ILifeForm::Deceased() {
		return _GenerationDeceased;
	}

	bool ILifeForm::CheckPulse() {
		return (_GenerationDeceased == -1);
	}
}