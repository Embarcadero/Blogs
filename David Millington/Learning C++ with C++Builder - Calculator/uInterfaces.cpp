//---------------------------------------------------------------------------

#pragma hdrstop
#include "uInterfaces.h"
#include "uCalculator.h"

std::unique_ptr<ICalculator> CreateCalculator(ICalculatorDisplay& Display) {
	return make_unique<TCalculator>(Display);
}

