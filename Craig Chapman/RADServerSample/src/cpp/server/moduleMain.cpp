//---------------------------------------------------------------------------
#pragma hdrstop

#include "moduleMain.h"
#include <memory>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma classgroup "System.Classes.TPersistent"
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
__fastcall TEmployeesResource1::TEmployeesResource1(TComponent* Owner)
	: TDataModule(Owner)
{
}

void TEmployeesResource1::Get(TEndpointContext* AContext, TEndpointRequest* ARequest, TEndpointResponse* AResponse)
{
  // Put results in a JSON object...
  qry->Active = true;
  if (qry->Active) {
	if (qry->RecordCount>0) {
	  TJSONArray* a = new TJSONArray();
	  qry->First();
	  while (!qry->Eof) {
		  TJSONObject* o = new TJSONObject();
		  o->AddPair("EmployeeNumber", (TJSONValue*) new TJSONNumber( qry->FieldByName("EMP_NO")->AsInteger ));
		  o->AddPair("FirstName",qry->FieldByName("FIRST_NAME")->AsString );
		  o->AddPair("LastName",qry->FieldByName("LAST_NAME")->AsString );
		  o->AddPair("PhoneExt",qry->FieldByName("PHONE_EXT")->AsString );
		  o->AddPair("HireDate",qry->FieldByName("HIRE_DATE")->AsString );
		  o->AddPair("DepartmentNumber", (TJSONValue*) new TJSONNumber( qry->FieldByName("DEPT_NO")->AsInteger ));
		  o->AddPair("JobCode",qry->FieldByName("JOB_CODE")->AsString );
		  o->AddPair("JobGrade",qry->FieldByName("JOB_GRADE")->AsString );
		  o->AddPair("JobCountry", qry->FieldByName("JOB_COUNTRY")->AsString );
		  o->AddPair("Salary", (TJSONValue*) new TJSONNumber( qry->FieldByName("SALARY")->AsFloat ) );
		  a->AddElement(o);
		  qry->Next();
	  }
	  AResponse->Body->SetValue( a, TRUE );
	}
  }
}

void TEmployeesResource1::GetItem(TEndpointContext* AContext, TEndpointRequest* ARequest, TEndpointResponse* AResponse)
{
  qry->SQL->Text = "select * from employee where EMP_NO = :item";
  qry->Params->ParamByName("item")->AsString = ARequest->Params->Values["item"];

  qry->Active = true;
  if (qry->Active) {
	if (qry->RecordCount>0) {
	  qry->First();
	  TJSONObject* o = new TJSONObject();
	  o->AddPair("EmployeeNumber", (TJSONValue*) new TJSONNumber( qry->FieldByName("EMP_NO")->AsInteger ));
	  o->AddPair("FirstName",qry->FieldByName("FIRST_NAME")->AsString );
	  o->AddPair("LastName",qry->FieldByName("LAST_NAME")->AsString );
	  o->AddPair("PhoneExt",qry->FieldByName("PHONE_EXT")->AsString );
	  o->AddPair("HireDate",qry->FieldByName("HIRE_DATE")->AsString );
	  o->AddPair("DepartmentNumber", (TJSONValue*) new TJSONNumber( qry->FieldByName("DEPT_NO")->AsInteger ));
	  o->AddPair("JobCode",qry->FieldByName("JOB_CODE")->AsString );
	  o->AddPair("JobGrade",qry->FieldByName("JOB_GRADE")->AsString );
	  o->AddPair("JobCountry", qry->FieldByName("JOB_COUNTRY")->AsString );
	  o->AddPair("Salary", (TJSONValue*) new TJSONNumber( qry->FieldByName("SALARY")->AsFloat ) );
	  AResponse->Body->SetValue( o, TRUE );
	}
  }
}

void TEmployeesResource1::Post(TEndpointContext* AContext, TEndpointRequest* ARequest, TEndpointResponse* AResponse)
{
  // Parse the JSON
  TJSONObject* RequestObject = (TJSONObject*) ARequest->Body->GetValue();

  // Insert New Record
  qry->SQL->Clear();
  qry->SQL->Add("insert into employee ( ");
  qry->SQL->Add(" FIRST_NAME, ");
  qry->SQL->Add(" LAST_NAME, ");
  qry->SQL->Add(" PHONE_EXT, ");
  qry->SQL->Add(" HIRE_DATE, ");
  qry->SQL->Add(" DEPT_NO, ");
  qry->SQL->Add(" JOB_CODE, ");
  qry->SQL->Add(" JOB_GRADE, ");
  qry->SQL->Add(" JOB_COUNTRY, ");
  qry->SQL->Add(" SALARY ) values( ");
  qry->SQL->Add(" :FIRST_NAME, ");
  qry->SQL->Add(" :LAST_NAME, ");
  qry->SQL->Add(" :PHONE_EXT, ");
  qry->SQL->Add(" :HIRE_DATE, ");
  qry->SQL->Add(" :DEPT_NO, ");
  qry->SQL->Add(" :JOB_CODE, ");
  qry->SQL->Add(" :JOB_GRADE, ");
  qry->SQL->Add(" :JOB_COUNTRY, ");
  qry->SQL->Add(" :SALARY);");

  // Set query parameters.
  qry->Params->ParamByName("FIRST_NAME")->AsString   = RequestObject->GetValue("FirstName")->Value();
  qry->Params->ParamByName("LAST_NAME")->AsString    = RequestObject->GetValue("LastName")->Value();
  qry->Params->ParamByName("PHONE_EXT")->AsString    = RequestObject->GetValue("PhoneExt")->Value();
  qry->Params->ParamByName("HIRE_DATE")->AsDateTime  = StrToDateTime(RequestObject->GetValue("HireDate")->Value());
  qry->Params->ParamByName("DEPT_NO")->AsInteger     = StrToInt(RequestObject->GetValue("DepartmentNumber")->Value());
  qry->Params->ParamByName("JOB_CODE")->AsString     = RequestObject->GetValue("JobCode")->Value();
  qry->Params->ParamByName("JOB_GRADE")->AsInteger   = StrToInt(RequestObject->GetValue("JobGrade")->Value());
  qry->Params->ParamByName("JOB_COUNTRY")->AsString  = RequestObject->GetValue("JobCountry")->Value();
  qry->Params->ParamByName("SALARY")->AsFloat        = StrToFloat(RequestObject->GetValue("Salary")->Value());

  // Execute SQL
  qry->ExecSQL();

  // Get new record ID from Generator.
  qry->SQL->Text = "select GEN_ID(EMP_NO_GEN,0) as ID from RDB$DATABASE;";
  qry->Active = True;
  qry->First();
  int NewRecordID = qry->Fields->FieldByName("ID")->AsInteger;
  qry->Active = False;

  // Send response
  TJSONObject* o = new TJSONObject();
  o->AddPair("EmployeeNumber",(TJSONValue*) new TJSONNumber(NewRecordID));
  AResponse->Body->SetValue(o,TRUE);
}

void TEmployeesResource1::PutItem(TEndpointContext* AContext, TEndpointRequest* ARequest, TEndpointResponse* AResponse)
{
  int EmployeeNumber = StrToInt(ARequest->Params->Values["item"]);

  // Parse the JSON
  TJSONObject* RequestObject = (TJSONObject*) ARequest->Body->GetValue();

  // Insert New Record
  qry->SQL->Clear();
  qry->SQL->Add(" update employee SET ");
  qry->SQL->Add(" FIRST_NAME = :FIRST_NAME, ");
  qry->SQL->Add(" LAST_NAME = :LAST_NAME, ");
  qry->SQL->Add(" PHONE_EXT = :PHONE_EXT, ");
  qry->SQL->Add(" HIRE_DATE = :HIRE_DATE, ");
  qry->SQL->Add(" DEPT_NO = :DEPT_NO, ");
  qry->SQL->Add(" JOB_CODE = :JOB_CODE, ");
  qry->SQL->Add(" JOB_GRADE = :JOB_GRADE, ");
  qry->SQL->Add(" JOB_COUNTRY = :JOB_COUNTRY, ");
  qry->SQL->Add(" SALARY = :SALARY ");
  qry->SQL->Add(" WHERE EMP_NO = :EMP_NO; ");

  // Set query parameters.
  qry->Params->ParamByName("EMP_NO")->AsInteger      = EmployeeNumber;
  qry->Params->ParamByName("FIRST_NAME")->AsString   = RequestObject->GetValue("FirstName")->Value();
  qry->Params->ParamByName("LAST_NAME")->AsString    = RequestObject->GetValue("LastName")->Value();
  qry->Params->ParamByName("PHONE_EXT")->AsString    = RequestObject->GetValue("PhoneExt")->Value();
  qry->Params->ParamByName("HIRE_DATE")->AsDateTime  = StrToDateTime(RequestObject->GetValue("HireDate")->Value());
  qry->Params->ParamByName("DEPT_NO")->AsInteger     = StrToInt(RequestObject->GetValue("DepartmentNumber")->Value());
  qry->Params->ParamByName("JOB_CODE")->AsString     = RequestObject->GetValue("JobCode")->Value();
  qry->Params->ParamByName("JOB_GRADE")->AsInteger   = StrToInt(RequestObject->GetValue("JobGrade")->Value());
  qry->Params->ParamByName("JOB_COUNTRY")->AsString  = RequestObject->GetValue("JobCountry")->Value();
  qry->Params->ParamByName("SALARY")->AsFloat        = StrToFloat(RequestObject->GetValue("Salary")->Value());

  // Execute SQL
  qry->ExecSQL();

  // Build the JSON response.
  TJSONObject* o = new TJSONObject();
  o->AddPair("EmployeeNumber",(TJSONValue*) new TJSONNumber(EmployeeNumber));
  AResponse->Body->SetValue(o,TRUE);
}

void TEmployeesResource1::DeleteItem(TEndpointContext* AContext, TEndpointRequest* ARequest, TEndpointResponse* AResponse)
{
  // Get employee number parameter
  int EmployeeNumber = StrToInt(ARequest->Params->Values["item"]);

  // Insert New Record
  qry->SQL->Text = "DELETE FROM employee WHERE EMP_NO = :EMP_NO; ";

  // Set query parameters.
  qry->Params->ParamByName("EMP_NO")->AsInteger = EmployeeNumber;

  // Execute SQL
  qry->ExecSQL();

  // Build the JSON response.
  TJSONObject* o = new TJSONObject();
  o->AddPair("EmployeeNumber",(TJSONValue*) new TJSONNumber(EmployeeNumber));
  AResponse->Body->SetValue(o,TRUE);
}

static void Register()
{
       	std::auto_ptr<TEMSResourceAttributes> attributes(new TEMSResourceAttributes());
       	attributes->ResourceName = "employees";
       	attributes->ResourceSuffix["GetItem"] = "{item}";
       	attributes->ResourceSuffix["PutItem"] = "{item}";
       	attributes->ResourceSuffix["DeleteItem"] = "{item}";
       	RegisterResource(__typeinfo(TEmployeesResource1), attributes.release());
}

#pragma startup Register 32


