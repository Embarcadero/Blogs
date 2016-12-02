//---------------------------------------------------------------------------

#pragma hdrstop

#include "uOperator.h"

namespace {
	class TNullOp : public IOperator {
		virtual double Calc(const double A, const double B) {
			return 0.0;
		}
		virtual std::wstring Name() const {
			return L"(null)";
		}
	};

	class TAdd : public IOperator {
		virtual double Calc(const double A, const double B) {
			return A + B;
		}
        virtual std::wstring Name() const {
			return L"+";
		}
	};

	class TSubtract : public IOperator {
		virtual double Calc(const double A, const double B) {
			return A - B;
		}
        virtual std::wstring Name() const {
			return L"-";
		}
	};

	class TMult : public IOperator {
		virtual double Calc(const double A, const double B) {
			return A * B;
		}
        virtual std::wstring Name() const {
			return L"×";
		}
	};

	class TDiv : public IOperator {
		virtual double Calc(const double A, const double B) {
			return A / B;
		}
		virtual std::wstring Name() const {
			return L"÷";
		}
	};
}

std::unique_ptr<IOperator> CreateOp(const EOperator Op) {
	switch (Op) {
		case EOperator::eDivide: return make_unique<TDiv>();
		case EOperator::eMultiply: return make_unique<TMult>();
		case EOperator::eAdd: return make_unique<TAdd>();
		case EOperator::eSubtract: return make_unique<TSubtract>();
    default:
		return nullptr;
	}
}
