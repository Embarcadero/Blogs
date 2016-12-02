//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "uFormCalculator.h"
#include "uInterfaces.h"

#pragma package(smart_init)
#pragma resource "*.fmx"
TfrmCalculator *frmCalculator;

//---------------------------------------------------------------------------
__fastcall TfrmCalculator::TfrmCalculator(TComponent* Owner) :
	TForm(Owner),
	m_Calc(CreateCalculator(*this))
{
}

//---------------------------------------------------------------------------
void TfrmCalculator::UpdateUI(const std::wstring& strText) {
	edtResult->Text = strText.c_str();
}

//---------------------------------------------------------------------------
void __fastcall TfrmCalculator::btnAddClick(TObject *Sender)
{
	m_Calc->SetOperator(EOperator::eAdd);
}

//---------------------------------------------------------------------------

void __fastcall TfrmCalculator::btnSubtractClick(TObject *Sender)
{
	 m_Calc->SetOperator(EOperator::eSubtract);
}
//---------------------------------------------------------------------------

void __fastcall TfrmCalculator::btnMultiplyClick(TObject *Sender)
{
	 m_Calc->SetOperator(EOperator::eMultiply);
}

//---------------------------------------------------------------------------
void __fastcall TfrmCalculator::btnDivideClick(TObject *Sender)
{
	 m_Calc->SetOperator(EOperator::eDivide);
}

//---------------------------------------------------------------------------

void __fastcall TfrmCalculator::btnEqualsClick(TObject *Sender)
{
	m_Calc->Equals();
}
//---------------------------------------------------------------------------

void __fastcall TfrmCalculator::btnDecimalPointClick(TObject *Sender)
{
	m_Calc->AddDecimalSeparator();
}
//---------------------------------------------------------------------------

void __fastcall TfrmCalculator::btnNumberClick(TObject *Sender)
{
	m_Calc->AddDigit(dynamic_cast<TButton*>(Sender)->Tag);
}
//---------------------------------------------------------------------------


