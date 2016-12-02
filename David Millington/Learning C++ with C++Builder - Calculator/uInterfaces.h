//---------------------------------------------------------------------------

#ifndef uInterfacesH
#define uInterfacesH

#include <string>
#include <memory>

// From http://stackoverflow.com/questions/7038357/make-unique-and-perfect-forwarding
template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args)
{
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

class ICalculatorDisplay {
public:
	//virtual __fastcall ~ICalculatorDisplay() {};
	virtual void UpdateUI(const std::wstring& strText) = 0;
};

enum class EOperator {
	eNull,
	eAdd,
	eSubtract,
	eMultiply,
	eDivide
};

class ICalculator {
public:
	virtual ~ICalculator() {};

	virtual void AddDigit(const int Digit) = 0;
	virtual void AddDecimalSeparator() = 0;
	virtual void SetOperator(const EOperator Op) = 0;
	virtual void Equals() = 0;
};

std::unique_ptr<ICalculator> CreateCalculator(ICalculatorDisplay& Display);

#endif
