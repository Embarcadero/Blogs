//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "frmMain.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TForm2 *Form2;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
	: TForm(Owner)
{
}

//---------------------------------------------------------------------------
void TForm2::ClearForm()
{
  spedEmployeeNumber->Value   =  0;
  edFirstName->Text           =  "";
  edLastName->Text            =  "";
  edtPhoneExt->Text           =  "";
  spedDepartmentNumber->Value =  0;
  edtJobCode->Text            =  "";
  edtJobGrade->Text           =  "";
  edtJobCountry->Text         =  "";
  spedSalary->Value           = 0.0;
  dtedHireDate->DateTime      =  Now();
}

//---------------------------------------------------------------------------
void TForm2::JSONToForm()
{
  TJSONObject* o;
//  ClearForm;
  if (fJSONArray->Count>0) {
	o = (TJSONObject*) fJSONArray->Items[fCurrentIndex];
	spedEmployeeNumber->Value     =  StrToInt( o->GetValue("EmployeeNumber")->Value() );
	edFirstName->Text             =  o->GetValue("FirstName")->Value();
	edLastName->Text              =  o->GetValue("LastName")->Value();
	if (!(o->GetValue("PhoneExt")==NULL)) {
	  edtPhoneExt->Text           =  o->GetValue("PhoneExt")->Value();
	}
	spedDepartmentNumber->Value   =  StrToFloat( o->GetValue("DepartmentNumber")->Value() );
	edtJobCode->Text              =  o->GetValue("JobCode")->Value();
	edtJobGrade->Text             =  o->GetValue("JobGrade")->Value();
	edtJobCountry->Text           =  o->GetValue("JobCountry")->Value();
	spedSalary->Text              =  o->GetValue("Salary")->Value();
	dtedHireDate->DateTime        =  StrToDateTime( o->GetValue("HireDate")->Value() );
  }
}

//---------------------------------------------------------------------------
void TForm2::CreateMode()
{
  // Read Only
  edFirstName->ReadOnly            = False;
  edLastName->ReadOnly             = False;
  edtPhoneExt->ReadOnly            = False;
  edtJobCode->ReadOnly             = False;
  edtJobGrade->ReadOnly            = False;
  spedSalary->ReadOnly             = False;
  edtJobCountry->ReadOnly          = False;
  dtedHireDate->ReadOnly           = False;
  // Text Prompt
  edFirstName->TextPrompt          = "First Name";
  edLastName->TextPrompt           = "Last Name";
  edtPhoneExt->TextPrompt          = "Phone Ext";
  spedDepartmentNumber->TextPrompt = "Dept No";
  spedDepartmentNumber->ReadOnly   = False;
  edtJobCode->TextPrompt           = "Job Code";
  edtJobGrade->TextPrompt          = "Job Grade";
  edtJobCountry->TextPrompt        = "Job Country";
  spedSalary->TextPrompt           = "0.0";
  // Text Color
  edFirstName->TextSettings->FontColor          = TAlphaColorRec::Red;
  edLastName->TextSettings->FontColor           = TAlphaColorRec::Red;
  edtPhoneExt->TextSettings->FontColor          = TAlphaColorRec::Red;
  spedDepartmentNumber->TextSettings->FontColor = TAlphaColorRec::Red;
  edtJobCode->TextSettings->FontColor           = TAlphaColorRec::Red;
  edtJobGrade->TextSettings->FontColor          = TAlphaColorRec::Red;
  edtJobCountry->TextSettings->FontColor        = TAlphaColorRec::Red;
  spedSalary->TextSettings->FontColor           = TAlphaColorRec::Red;
  dtedHireDate->TextSettings->FontColor         = TAlphaColorRec::Red;
  // adjust buttons
  btnRead->Enabled    = False;
  btnNext->Enabled    = False;
  btnPrev->Enabled    = False;
  btnLast->Enabled    = False;
  btnFirst->Enabled   = False;
  btnCreate->Enabled  = False;
  btnCommit->Enabled  = True;
  btnEdit->Enabled    = False;
  btnUpdate->Enabled  = False;
  btnDelete->Enabled  = False;
}

//---------------------------------------------------------------------------
void TForm2::BrowseMode()
{
  spedEmployeeNumber->Enabled     = True;
  // Read only
  edFirstName->ReadOnly           = True;
  edLastName->ReadOnly            = True;
  edtPhoneExt->ReadOnly           = True;
  edtJobCode->ReadOnly            = True;
  edtJobGrade->ReadOnly           = True;
  edtJobCountry->ReadOnly         = True;
  spedSalary->ReadOnly            = True;
  spedDepartmentNumber->ReadOnly  = True;
  dtedHireDate->ReadOnly          = True;
  // Text prompt
  edFirstName->TextPrompt          = "";
  edLastName->TextPrompt           = "";
  edtPhoneExt->TextPrompt          = "";
  spedDepartmentNumber->TextPrompt = "";
  edtJobCode->TextPrompt           = "";
  edtJobGrade->TextPrompt          = "";
  edtJobCountry->TextPrompt        = "";
  spedSalary->TextPrompt           = "";
  // Text Color
  edFirstName->TextSettings->FontColor          = TAlphaColorRec::Black;
  edLastName->TextSettings->FontColor           = TAlphaColorRec::Black;
  edtPhoneExt->TextSettings->FontColor          = TAlphaColorRec::Black;
  spedDepartmentNumber->TextSettings->FontColor = TAlphaColorRec::Black;
  edtJobCode->TextSettings->FontColor           = TAlphaColorRec::Black;
  edtJobGrade->TextSettings->FontColor          = TAlphaColorRec::Black;
  edtJobCountry->TextSettings->FontColor        = TAlphaColorRec::Black;
  spedSalary->TextSettings->FontColor           = TAlphaColorRec::Black;
  dtedHireDate->TextSettings->FontColor         = TAlphaColorRec::Black;
  // adjust buttons
  btnRead->Enabled    = True;
  btnNext->Enabled    = True;
  btnPrev->Enabled    = True;
  btnLast->Enabled    = True;
  btnFirst->Enabled   = True;
  btnCreate->Enabled  = True;
  btnCommit->Enabled  = False;
  btnEdit->Enabled    = True;
  btnUpdate->Enabled  = False;
  btnDelete->Enabled  = True;
}

//---------------------------------------------------------------------------
void TForm2::EditMode()
{
  // Read Only
  edFirstName->ReadOnly            = False;
  edLastName->ReadOnly             = False;
  edtPhoneExt->ReadOnly            = False;
  edtJobCode->ReadOnly             = False;
  edtJobGrade->ReadOnly            = False;
  edtJobCountry->ReadOnly          = False;
  spedDepartmentNumber->ReadOnly   = False;
  spedSalary->ReadOnly             = False;
  dtedHireDate->ReadOnly           = False;
  // Text Prompt
  edFirstName->TextPrompt          = "First Name";
  edLastName->TextPrompt           = "Last Name";
  edtPhoneExt->TextPrompt          = "Phone Ext";
  spedDepartmentNumber->TextPrompt = "Dept No";
  edtJobCode->TextPrompt           = "Job Code";
  edtJobGrade->TextPrompt          = "Job Grade";
  edtJobCountry->TextPrompt        = "Job Country";
  spedSalary->TextPrompt           = "Salary";
  // Text Color
  edFirstName->TextSettings->FontColor          = TAlphaColorRec::Blue;
  edLastName->TextSettings->FontColor           = TAlphaColorRec::Blue;
  edtPhoneExt->TextSettings->FontColor          = TAlphaColorRec::Blue;
  spedDepartmentNumber->TextSettings->FontColor = TAlphaColorRec::Blue;
  edtJobCode->TextSettings->FontColor           = TAlphaColorRec::Blue;
  edtJobGrade->TextSettings->FontColor          = TAlphaColorRec::Blue;
  edtJobCountry->TextSettings->FontColor        = TAlphaColorRec::Blue;
  spedSalary->TextSettings->FontColor           = TAlphaColorRec::Blue;
  dtedHireDate->TextSettings->FontColor         = TAlphaColorRec::Blue;
  // adjust buttons
  btnRead->Enabled    = False;
  btnNext->Enabled    = False;
  btnPrev->Enabled    = False;
  btnLast->Enabled    = False;
  btnFirst->Enabled   = False;
  btnCreate->Enabled  = False;
  btnCommit->Enabled  = False;
  btnEdit->Enabled    = False;
  btnUpdate->Enabled  = True;
  btnDelete->Enabled  = False;
}

//---------------------------------------------------------------------------
void __fastcall TForm2::btnReadClick(TObject *Sender)
{
  //- Request data from 'employees' end-point.
  RESTRequest->Resource = "employees";
  RESTRequest->Method   = TRESTRequestMethod::rmGET;
  RESTRequest->Response = RESTResponse;

  // Make request.
  RESTRequest->Execute();

  //- Decode the data into a class global
  if (fJSONArray) {
	fJSONArray->DisposeOf();
  }
  fJSONArray = (TJSONArray*) TJSONObject::ParseJSONValue(RESTResponse->Content);

  //- set index.
  fCurrentIndex = 0;

  //- Load current resource to form.
  JSONToForm();
}
//---------------------------------------------------------------------------
void __fastcall TForm2::btnPrevClick(TObject *Sender)
{
  if (fCurrentIndex>0) {
	fCurrentIndex--;
  }
  JSONToForm();
}
//---------------------------------------------------------------------------
void __fastcall TForm2::btnNextClick(TObject *Sender)
{
  if (fCurrentIndex<(fJSONArray->Count-1)) {
	fCurrentIndex++;
  }
  JSONToForm();
}
//---------------------------------------------------------------------------
void __fastcall TForm2::btnFirstClick(TObject *Sender)
{
  fCurrentIndex = 0;
  JSONToForm();
}
//---------------------------------------------------------------------------
void __fastcall TForm2::btnLastClick(TObject *Sender)
{
  if (fJSONArray->Count>0) {
	fCurrentIndex = (fJSONArray->Count-1);
  } else {
	fCurrentIndex = 0;
  }
  JSONToForm();
}
//---------------------------------------------------------------------------
void __fastcall TForm2::btnCreateClick(TObject *Sender)
{
  //- Clear the form and adjust text read-only and prompts.
  ClearForm();
  CreateMode();
}
//---------------------------------------------------------------------------
void __fastcall TForm2::btnCommitClick(TObject *Sender)
{
  //- Prepare to POST data to 'employees' end-point.
  RESTRequest->Resource  = "employees";
  RESTRequest->Method    = TRESTRequestMethod::rmPOST;
  RESTRequest->Response  = RESTResponse;

  //- Populate the JSON resource to post.
  RESTRequest->Body->ClearBody();
  RESTRequest->Body->JSONWriter->WriteStartObject();
  RESTRequest->Body->JSONWriter->WritePropertyName("FirstName");
  RESTRequest->Body->JSONWriter->WriteValue(edFirstName->Text);
  RESTRequest->Body->JSONWriter->WritePropertyName("LastName");
  RESTRequest->Body->JSONWriter->WriteValue(edLastName->Text);
  RESTRequest->Body->JSONWriter->WritePropertyName("PhoneExt");
  RESTRequest->Body->JSONWriter->WriteValue(edtPhoneExt->Text);
  RESTRequest->Body->JSONWriter->WritePropertyName("DepartmentNumber");
  RESTRequest->Body->JSONWriter->WriteValue(spedDepartmentNumber->Value);
  RESTRequest->Body->JSONWriter->WritePropertyName("JobCode");
  RESTRequest->Body->JSONWriter->WriteValue(edtJobCode->Text);
  RESTRequest->Body->JSONWriter->WritePropertyName("JobGrade");
  RESTRequest->Body->JSONWriter->WriteValue(edtJobGrade->Text);
  RESTRequest->Body->JSONWriter->WritePropertyName("JobCountry");
  RESTRequest->Body->JSONWriter->WriteValue(edtJobCountry->Text);
  RESTRequest->Body->JSONWriter->WritePropertyName("Salary");
  RESTRequest->Body->JSONWriter->WriteValue(spedSalary->Value);
  RESTRequest->Body->JSONWriter->WritePropertyName("HireDate");
  RESTRequest->Body->JSONWriter->WriteValue(FormatDateTime("MM/DD/YYYY 00:00:00",dtedHireDate->DateTime));
  RESTRequest->Body->JSONWriter->WriteEnd();

  // Adjust the form to recieve the result.
  BrowseMode();

  // Execute the request
  RESTRequest->Execute();

  // Refresh form
  this->btnReadClick(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TForm2::btnEditClick(TObject *Sender)
{
  EditMode();
}
//---------------------------------------------------------------------------
void __fastcall TForm2::btnUpdateClick(TObject *Sender)
{
  //- Prepare to PUT data to 'employees' end-point.
  RESTRequest->Resource = "employees/"+spedEmployeeNumber->Text;
  RESTRequest->Method   = TRESTRequestMethod::rmPUT;
  RESTRequest->Response = RESTResponse;

  //- Populate the JSON resource to post.
  RESTRequest->Body->ClearBody();
  RESTRequest->Body->JSONWriter->WriteStartObject();
  RESTRequest->Body->JSONWriter->WritePropertyName("FirstName");
  RESTRequest->Body->JSONWriter->WriteValue(edFirstName->Text);
  RESTRequest->Body->JSONWriter->WritePropertyName("LastName");
  RESTRequest->Body->JSONWriter->WriteValue(edLastName->Text);
  RESTRequest->Body->JSONWriter->WritePropertyName("PhoneExt");
  RESTRequest->Body->JSONWriter->WriteValue(edtPhoneExt->Text);
  RESTRequest->Body->JSONWriter->WritePropertyName("DepartmentNumber");
  RESTRequest->Body->JSONWriter->WriteValue(spedDepartmentNumber->Value);
  RESTRequest->Body->JSONWriter->WritePropertyName("JobCode");
  RESTRequest->Body->JSONWriter->WriteValue(edtJobCode->Text);
  RESTRequest->Body->JSONWriter->WritePropertyName("JobGrade");
  RESTRequest->Body->JSONWriter->WriteValue(edtJobGrade->Text);
  RESTRequest->Body->JSONWriter->WritePropertyName("JobCountry");
  RESTRequest->Body->JSONWriter->WriteValue(edtJobCountry->Text);
  RESTRequest->Body->JSONWriter->WritePropertyName("Salary");
  RESTRequest->Body->JSONWriter->WriteValue(spedSalary->Value);
  RESTRequest->Body->JSONWriter->WritePropertyName("HireDate");
  RESTRequest->Body->JSONWriter->WriteValue(FormatDateTime("MM/DD/YYYY 00:00:00",dtedHireDate->DateTime));
  RESTRequest->Body->JSONWriter->WriteEnd();

  // Adjust the form to recieve the result.
  BrowseMode();

  // Execute the request
  RESTRequest->Execute();

  // Refresh form
  this->btnReadClick(Sender);
}

//---------------------------------------------------------------------------
void __fastcall TForm2::btnDeleteClick(TObject *Sender)
{
  //- Prepare to DELETE data from 'employees' end-point.
  RESTRequest->Resource = "employees/"+spedEmployeeNumber->Text;
  RESTRequest->Method   = TRESTRequestMethod::rmDELETE;
  RESTRequest->Response = RESTResponse;

  // Execute the request
  RESTRequest->Execute();

  // Refresh form
  this->btnReadClick(Sender);
}
//---------------------------------------------------------------------------



