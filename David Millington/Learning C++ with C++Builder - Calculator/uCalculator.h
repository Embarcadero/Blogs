//---------------------------------------------------------------------------

#ifndef uCalculatorH
#define uCalculatorH

#include "uInterfaces.h"
#include <memory>
#include "uOperator.h"
#include <boost/optional/optional.hpp>
#include <string>

class Accumulator {
private:
	boost::optional<int> m_Whole;
	boost::optional<int> m_Frac;
	int m_FracLeadingZeros;
	bool m_EnteringFraction;

	double Whole() const;
	double Frac() const;
	static int InternalAddDigit(const boost::optional<int>& Value, const int Digit);
public:
	Accumulator();
	bool Entering() const;
	double Value() const;
	std::wstring ValueStr() const;
	void SetEnteringFraction();
	void AddDigit(const int Digit);
};

class TCalculator : public ICalculator {
private:
	ICalculatorDisplay& m_Display;
	std::unique_ptr<IOperator> m_Op;
	boost::optional<double> m_Left;
	boost::optional<double> m_Right;
	boost::optional<double> m_Result;
	Accumulator m_Accum;

    void PromoteAccumulator();
    void UpdateUI();
public:
	TCalculator(ICalculatorDisplay& Display);
	virtual ~TCalculator();
public: // ICalculator
	virtual void AddDigit(const int Digit);
	virtual void AddDecimalSeparator();
	virtual void SetOperator(const EOperator Op);
    virtual void Equals();
};

#endif
