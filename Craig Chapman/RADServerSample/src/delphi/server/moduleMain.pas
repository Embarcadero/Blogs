unit moduleMain;

// EMS Resource Module

interface

uses
  System.SysUtils, System.Classes, System.JSON,
  EMS.Services, EMS.ResourceAPI, EMS.ResourceTypes, Data.DBXInterBase,
  Data.FMTBcd, Data.DB, Data.SqlExpr, FireDAC.Stan.Intf, FireDAC.Stan.Option,
  FireDAC.Stan.Error, FireDAC.UI.Intf, FireDAC.Phys.Intf, FireDAC.Stan.Def,
  FireDAC.Stan.Pool, FireDAC.Stan.Async, FireDAC.Phys, FireDAC.Phys.IB,
  FireDAC.Phys.IBDef, FireDAC.ConsoleUI.Wait, FireDAC.Stan.Param, FireDAC.DatS,
  FireDAC.DApt.Intf, FireDAC.DApt, FireDAC.Comp.DataSet, FireDAC.Comp.Client;

type
  [ResourceName('employees')]
  TEmployeesResource1 = class(TDataModule)
    conn: TFDConnection;
    qry: TFDQuery;
  published
    procedure Get(const AContext: TEndpointContext; const ARequest: TEndpointRequest; const AResponse: TEndpointResponse);
    [ResourceSuffix('{item}')]
    procedure GetItem(const AContext: TEndpointContext; const ARequest: TEndpointRequest; const AResponse: TEndpointResponse);
    procedure Post(const AContext: TEndpointContext; const ARequest: TEndpointRequest; const AResponse: TEndpointResponse);
    [ResourceSuffix('{item}')]
    procedure PutItem(const AContext: TEndpointContext; const ARequest: TEndpointRequest; const AResponse: TEndpointResponse);
    [ResourceSuffix('{item}')]
    procedure DeleteItem(const AContext: TEndpointContext; const ARequest: TEndpointRequest; const AResponse: TEndpointResponse);
  end;

implementation

{%CLASSGROUP 'System.Classes.TPersistent'}

{$R *.dfm}

procedure TEmployeesResource1.Get(const AContext: TEndpointContext; const ARequest: TEndpointRequest; const AResponse: TEndpointResponse);
var
  a: TJSONArray;
  o: TJSONObject;
begin
  qry.Active := true;
  if qry.Active then begin
    if qry.RecordCount>0 then begin
      a := TJSONArray.Create;
      try
        qry.First;
        while (not qry.Eof) do begin
          o := TJSONObject.Create;
          o.AddPair('EmployeeNumber',TJSONNumber.Create( qry.FieldByName('EMP_NO').AsInteger ));
          o.AddPair('FirstName',qry.FieldByName('FIRST_NAME').AsString );
          o.AddPair('LastName',qry.FieldByName('LAST_NAME').AsString );
          o.AddPair('PhoneExt',qry.FieldByName('PHONE_EXT').AsString );
          o.AddPair('HireDate',qry.FieldByName('HIRE_DATE').AsString );
          o.AddPair('DepartmentNumber',TJSONNumber.Create( qry.FieldByName('DEPT_NO').AsInteger ));
          o.AddPair('JobCode',qry.FieldByName('JOB_CODE').AsString );
          o.AddPair('JobGrade',qry.FieldByName('JOB_GRADE').AsString );
          o.AddPair('JobCountry', qry.FieldByName('JOB_COUNTRY').AsString );
          o.AddPair('Salary', TJSONNumber.Create( qry.FieldByName('SALARY').AsFloat ) );
          a.AddElement(o);
          qry.Next;
        end;
      finally
        AResponse.Body.SetValue(a,TRUE);
      end;
    end;
  end;
end;

procedure TEmployeesResource1.GetItem(const AContext: TEndpointContext; const ARequest: TEndpointRequest; const AResponse: TEndpointResponse);
var
  o: TJSONObject;
  EmployeeNumber: integer;
begin
  EmployeeNumber := StrToInt(ARequest.Params.Values['item']);
  qry.SQL.Text := 'SELECT * FROM EMPLOYEE WHERE EMP_NO = :EMP_NO';
  qry.Params.ParamByName('EMP_NO').AsInteger := EmployeeNumber;

  qry.Active := true;
  if qry.Active then begin
    if qry.RecordCount>0 then begin
        qry.First;
        o := TJSONObject.Create;
        o.AddPair('EmployeeNumber',TJSONNumber.Create( qry.FieldByName('EMP_NO').AsInteger ));
        o.AddPair('FirstName',qry.FieldByName('FIRST_NAME').AsString );
        o.AddPair('LastName',qry.FieldByName('LAST_NAME').AsString );
        o.AddPair('PhoneExt',qry.FieldByName('PHONE_EXT').AsString );
        o.AddPair('HireDate',qry.FieldByName('HIRE_DATE').AsString );
        o.AddPair('DepartmentNumber',TJSONNumber.Create( qry.FieldByName('DEPT_NO').AsInteger ));
        o.AddPair('JobCode',qry.FieldByName('JOB_CODE').AsString );
        o.AddPair('JobGrade',qry.FieldByName('JOB_GRADE').AsString );
        o.AddPair('JobCountry', qry.FieldByName('JOB_COUNTRY').AsString );
        o.AddPair('Salary', TJSONNumber.Create( qry.FieldByName('SALARY').AsFloat ) );
        AResponse.Body.SetValue(o,TRUE);
    end;
  end;
end;


procedure TEmployeesResource1.Post(const AContext: TEndpointContext; const ARequest: TEndpointRequest; const AResponse: TEndpointResponse);
var
  RequestObject: TJSONObject;
  NewRecordID: int32;
  o: TJSONObject;
begin
  // Parse the JSON
  RequestObject := ARequest.Body.GetObject;

  // Insert New Record
  qry.SQL.Text := 'insert into employee ( '+
                  ' FIRST_NAME, '+
                  ' LAST_NAME, '+
                  ' PHONE_EXT, '+
                  ' HIRE_DATE, '+
                  ' DEPT_NO, '+
                  ' JOB_CODE, '+
                  ' JOB_GRADE, '+
                  ' JOB_COUNTRY, '+
                  ' SALARY ) values( ' +
                  ' :FIRST_NAME, '+
                  ' :LAST_NAME, '+
                  ' :PHONE_EXT, '+
                  ' :HIRE_DATE, '+
                  ' :DEPT_NO, '+
                  ' :JOB_CODE, '+
                  ' :JOB_GRADE, '+
                  ' :JOB_COUNTRY, '+
                  ' :SALARY);';

  // Set query parameters.
  qry.Params.ParamByName('FIRST_NAME').AsString  := RequestObject.GetValue('FirstName').Value;
  qry.Params.ParamByName('LAST_NAME').AsString   := RequestObject.GetValue('LastName').Value;
  qry.Params.ParamByName('PHONE_EXT').AsString   := RequestObject.GetValue('PhoneExt').Value;
  qry.Params.ParamByName('HIRE_DATE').AsDateTime := StrToDateTime(RequestObject.GetValue('HireDate').Value);
  qry.Params.ParamByName('DEPT_NO').AsInteger    := StrToInt(RequestObject.GetValue('DepartmentNumber').Value);
  qry.Params.ParamByName('JOB_CODE').AsString    := RequestObject.GetValue('JobCode').Value;
  qry.Params.ParamByName('JOB_GRADE').AsInteger  := StrToInt(RequestObject.GetValue('JobGrade').Value);
  qry.Params.ParamByName('JOB_COUNTRY').AsString := RequestObject.GetValue('JobCountry').Value;
  qry.Params.ParamByName('SALARY').AsFloat       := StrToFloat(RequestObject.GetValue('Salary').Value);

  // Execute SQL
  qry.ExecSQL;

  // Get new record ID from Generator.
  qry.SQL.Text := 'select GEN_ID(EMP_NO_GEN,0) as ID from RDB$DATABASE;';
  qry.Active := True;
  qry.First;
  NewRecordID := qry.Fields.FieldByName('ID').AsInteger;
  qry.Active := False;

  // Build the JSON response.
  o := TJSONObject.Create;
  o.AddPair('EmployeeNumber',TJSONNumber.Create(NewRecordID));
  AResponse.Body.SetValue(o,TRUE);
end;

procedure TEmployeesResource1.PutItem(const AContext: TEndpointContext; const ARequest: TEndpointRequest; const AResponse: TEndpointResponse);
var
  EmployeeNumber: integer;
  RequestObject: TJSONObject;
  o: TJSONObject;
begin
  EmployeeNumber := StrToInt(ARequest.Params.Values['item']);

  // Parse the JSON
  RequestObject := ARequest.Body.GetObject;

  // Insert New Record
  qry.SQL.Text := 'update employee SET '+
                  ' FIRST_NAME = :FIRST_NAME, '+
                  ' LAST_NAME = :LAST_NAME, '+
                  ' PHONE_EXT = :PHONE_EXT, '+
                  ' HIRE_DATE = :HIRE_DATE, '+
                  ' DEPT_NO = :DEPT_NO, '+
                  ' JOB_CODE = :JOB_CODE, '+
                  ' JOB_GRADE = :JOB_GRADE, '+
                  ' JOB_COUNTRY = :JOB_COUNTRY, '+
                  ' SALARY = :SALARY ' +
                  ' WHERE EMP_NO = :EMP_NO; ';

  // Set query parameters.
  qry.Params.ParamByName('EMP_NO').AsInteger := EmployeeNumber;
  qry.Params.ParamByName('FIRST_NAME').AsString := RequestObject.GetValue('FirstName').Value;
  qry.Params.ParamByName('LAST_NAME').AsString := RequestObject.GetValue('LastName').Value;
  qry.Params.ParamByName('PHONE_EXT').AsString := RequestObject.GetValue('PhoneExt').Value;
  qry.Params.ParamByName('HIRE_DATE').AsDateTime := StrToDateTime(RequestObject.GetValue('HireDate').Value);
  qry.Params.ParamByName('DEPT_NO').AsInteger := StrToInt(RequestObject.GetValue('DepartmentNumber').Value);
  qry.Params.ParamByName('JOB_CODE').AsString := RequestObject.GetValue('JobCode').Value;
  qry.Params.ParamByName('JOB_GRADE').AsInteger := StrToInt(RequestObject.GetValue('JobGrade').Value);
  qry.Params.ParamByName('JOB_COUNTRY').AsString := RequestObject.GetValue('JobCountry').Value;
  qry.Params.ParamByName('SALARY').AsFloat := StrToFloat(RequestObject.GetValue('Salary').Value);

  // Execute SQL
  qry.ExecSQL;

  // Build the JSON response.
  o := TJSONObject.Create;
  o.AddPair('EmployeeNumber',TJSONNumber.Create(EmployeeNumber));
  AResponse.Body.SetValue(o,TRUE);
end;

procedure TEmployeesResource1.DeleteItem(const AContext: TEndpointContext; const ARequest: TEndpointRequest; const AResponse: TEndpointResponse);
var
  o: TJSONObject;
  EmployeeNumber: integer;
begin
  // Get employee number parameter
  EmployeeNumber := StrToInt(ARequest.Params.Values['item']);

  // Insert New Record
  qry.SQL.Text := 'DELETE FROM employee WHERE EMP_NO = :EMP_NO; ';

  // Set query parameters.
  qry.Params.ParamByName('EMP_NO').AsInteger := EmployeeNumber;

  // Execute SQL
  qry.ExecSQL;

  // Build the JSON response.
  o := TJSONObject.Create;
  o.AddPair('EmployeeNumber',TJSONNumber.Create(EmployeeNumber));
  AResponse.Body.SetValue(o,TRUE);
end;

procedure Register;
begin
  RegisterResource(TypeInfo(TEmployeesResource1));
end;

initialization
  Register;
end.


