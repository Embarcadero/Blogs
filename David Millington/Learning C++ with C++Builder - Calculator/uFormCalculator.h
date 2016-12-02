//---------------------------------------------------------------------------

#ifndef uFormCalculatorH
#define uFormCalculatorH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include <FMX.Edit.hpp>
#include "uInterfaces.h"
#include <memory>
//---------------------------------------------------------------------------
class TfrmCalculator : public TForm, ICalculatorDisplay
{
__published:	// IDE-managed Components
	TButton *btnZero;
	TButton *btnDecimalPoint;
	TButton *btnDivide;
	TButton *btnMultiply;
	TButton *btnSubtract;
	TButton *btnAdd;
	TButton *btnEquals;
	TButton *btnTwo;
	TButton *btnNine;
	TButton *btnEight;
	TButton *btnSeven;
	TButton *btnSix;
	TButton *btnFive;
	TButton *btnFour;
	TButton *btnThree;
	TButton *btnOne;
	TEdit *edtResult;
	TStyleBook *StyleBook1;
	void __fastcall btnAddClick(TObject *Sender);
	void __fastcall btnSubtractClick(TObject *Sender);
	void __fastcall btnMultiplyClick(TObject *Sender);
	void __fastcall btnDivideClick(TObject *Sender);
	void __fastcall btnEqualsClick(TObject *Sender);
	void __fastcall btnDecimalPointClick(TObject *Sender);
	void __fastcall btnNumberClick(TObject *Sender);
private:	// User declarations
	std::unique_ptr<ICalculator> m_Calc;
public:		// User declarations
	__fastcall TfrmCalculator(TComponent* Owner);
	virtual void UpdateUI(const std::wstring& strText);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmCalculator *frmCalculator;
//---------------------------------------------------------------------------
#endif
