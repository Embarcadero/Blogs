//---------------------------------------------------------------------------

#ifndef uOperatorH
#define uOperatorH

#include <string>
#include <memory>
#include "uInterfaces.h"

class IOperator {
public:
	virtual double Calc(const double A,const double B) = 0;
	virtual std::wstring Name() const = 0;
};

std::unique_ptr<IOperator> CreateOp(const EOperator Op);

#endif
