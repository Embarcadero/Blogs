//---------------------------------------------------------------------------

#pragma hdrstop

#include "uCalculator.h"
#include <sstream>
#include <math.h>

Accumulator::Accumulator() :
	m_Whole(),
	m_Frac(),
	m_FracLeadingZeros(0),
	m_EnteringFraction(false)
{
}

bool Accumulator::Entering() const {
	// Is user entering a number?
	return (m_Whole || m_Frac || (m_FracLeadingZeros > 0)); // If none of these, nothing entered
}

double Accumulator::Value() const {
	return Whole() + Frac();
}

std::wstring Accumulator::ValueStr() const {
	std::wstringstream str;

	str << Whole();
	if (m_FracLeadingZeros > 0 || m_Frac) {
        str << L".";
		str << std::wstring(m_FracLeadingZeros, L'0'); // Writes, eg, '000' for 3
		if (m_Frac) {
            str << *m_Frac;
		}
	}

	return str.str();
}

double Accumulator::Whole() const {
	if (m_Whole) {
		return *m_Whole;
	}
	return 0.0;
}

double Accumulator::Frac() const {
	// Convert an integer like 123 to 0.123
	// Magnitude can be calculated via log10
	// log10(123) -> 2, +1 -> 3
	// pow(10, 3) -> 1000
	// 123 / 100 = 0.123
	// Note leading zeroes - handle separately
	if (m_Frac && (*m_Frac != 0)) {
		return *m_Frac / pow(10, floor(log10(*m_Frac) + m_FracLeadingZeros + 1));
	}
	return 0.0;
}

void Accumulator::SetEnteringFraction() {
	m_EnteringFraction = true;
}

int Accumulator::InternalAddDigit(const boost::optional<int>& Value, const int Digit) {
	// Add a digit to the number. If it doesn't exist, the number is the digit
	if (Value) {
		return *Value * 10 + Digit;
	} else {
		return Digit;
	}
}

void Accumulator::AddDigit(const int Digit) {
	if (m_EnteringFraction) {
		// Leading zeroes won't get added, mathematically (to enter 1.00001, for
		// example, InternalAddDigit will multiply by 10 and add 0.) Track separately
		if (Digit == 0 && !m_Frac) {
			++m_FracLeadingZeros;
		} else {
			m_Frac = InternalAddDigit(m_Frac, Digit);
		}
	} else {
		m_Whole = InternalAddDigit(m_Whole, Digit);
	}
}

////////////////////////////////////////////////////////////////////////////////

TCalculator::TCalculator(ICalculatorDisplay& Display) :
	m_Display(Display),
	m_Op(),
	m_Left(),
	m_Right(),
	m_Result(),
	m_Accum()
{
}

TCalculator::~TCalculator() {
}

void TCalculator::AddDigit(const int Digit) {
	// Mimic typing into a calculator

	if (m_Result) { // typing after getting an answer. Clear
		m_Result.reset();
	}
	m_Accum.AddDigit(Digit);
	UpdateUI();
}

void TCalculator::AddDecimalSeparator() {
	m_Accum.SetEnteringFraction();
}

void TCalculator::PromoteAccumulator() {
	// The accumulator has had the user enter digits
	// Now it needs to become a number
	// If don't have a left side, it's that
	// If do, and don't have a right side, it's that
	// If have both, then there is a logic error.

	if (!m_Accum.Entering()) {
        return;
	}

	if (!m_Left) {
		m_Left = m_Accum.Value();
	} else {
		assert(!m_Right);
        m_Right = m_Accum.Value();
	}
	// Reset
	m_Accum = Accumulator();
}

void TCalculator::SetOperator(const EOperator Op) {
	if (Op == EOperator::eNull) {
	   m_Op.reset();
	} else {
		PromoteAccumulator(); // once the op changes, stop entering, make it a number

		// 1 + 2 [now press -] -> want to calc that, make it the left operand
		if (!m_Result && m_Left && m_Right) {
			Equals();
		}
		if (m_Result) {
			// Operator after result -> want the result to be the new left operand
			m_Left = m_Result;
			m_Right.reset();
			m_Result.reset();
		}
		if (m_Left) {
			// Require a left operand, because all ops have to operate on at least
			// one operand
			m_Op = CreateOp(Op);
		}
	}

    UpdateUI();
}

void TCalculator::Equals() {
	PromoteAccumulator();

	if (m_Left && m_Right && m_Op) {
		m_Result = m_Op->Calc(*m_Left, *m_Right);
		m_Left.reset(); // No operands any more
		m_Right.reset();
		SetOperator(EOperator::eNull); // Nothing to do any more
	}
	UpdateUI();
}

void TCalculator::UpdateUI() {
	// What should the UI draw?
	// What's being typed in, so the accumulator if it's being typed in
	// The whole expression: if there is a left side, and an operator,
	// it should print that plus then the accumulator
	// The result: all operands, operator, equals.

	std::wstringstream stream;
	if (m_Left) {
		stream << *m_Left;

		if (m_Op) {
			stream << L" " << m_Op->Name() << L" ";

			if (m_Right) {
				stream << *m_Right;
			} else if (m_Accum.Entering()) {
				stream << m_Accum.ValueStr();
			}
		}
	} else if (m_Accum.Entering()) {
		stream << m_Accum.ValueStr();
	} else if (m_Result) {
		stream << *m_Result;
	}

	m_Display.UpdateUI(stream.str());
}
