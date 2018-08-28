unit formMain;

interface

uses
  System.SysUtils, System.Types, System.UITypes, System.Classes, System.Variants,
  FMX.Types, FMX.Controls, FMX.Forms, FMX.Graphics, FMX.Dialogs, System.Rtti,
  IPPeerClient, Data.DB, Datasnap.DBClient, REST.Response.Adapter, REST.Client,
  Data.Bind.Components, Data.Bind.ObjectScope, FMX.Layouts, FMX.Grid,
  FMX.Controls.Presentation, FMX.StdCtrls, FMX.TabControl, Data.Bind.EngExt,
  Fmx.Bind.DBEngExt, Fmx.Bind.Grid, System.Bindings.Outputs, Fmx.Bind.Editors,
  Data.Bind.Grid, Data.Bind.DBScope, Data.Bind.Controls, Fmx.Bind.Navigator,
  FMX.DateTimeCtrls, FMX.EditBox, FMX.SpinBox, FMX.Edit,
  System.JSON;

type
  TfrmMain = class(TForm)
    RESTClient: TRESTClient;
    RESTRequest: TRESTRequest;
    RESTResponse: TRESTResponse;
    Panel3: TPanel;
    lblFirstName: TLabel;
    lblLastName: TLabel;
    lblEmployeeNumber: TLabel;
    lblPhoneExt: TLabel;
    lblHireDate: TLabel;
    lblDepartmentNumber: TLabel;
    lblJobCode: TLabel;
    lblJobGrade: TLabel;
    lblJobCountry: TLabel;
    lblSalary: TLabel;
    edFirstName: TEdit;
    edLastName: TEdit;
    edtPhoneExt: TEdit;
    edtJobCode: TEdit;
    edtJobGrade: TEdit;
    edtJobCountry: TEdit;
    spedEmployeeNumber: TSpinBox;
    spedDepartmentNumber: TSpinBox;
    dtedHireDate: TDateEdit;
    Panel1: TPanel;
    Panel2: TPanel;
    btnPrev: TButton;
    btnNext: TButton;
    btnRead: TButton;
    btnCreate: TButton;
    btnCommit: TButton;
    btnEdit: TButton;
    btnUpdate: TButton;
    btnDelete: TButton;
    btnFirst: TButton;
    btnLast: TButton;
    spedSalary: TSpinBox;
    procedure btnReadClick(Sender: TObject);
    procedure btnPrevClick(Sender: TObject);
    procedure btnNextClick(Sender: TObject);
    procedure btnCreateClick(Sender: TObject);
    procedure btnCommitClick(Sender: TObject);
    procedure btnFirstClick(Sender: TObject);
    procedure btnLastClick(Sender: TObject);
    procedure btnEditClick(Sender: TObject);
    procedure btnUpdateClick(Sender: TObject);
    procedure btnDeleteClick(Sender: TObject);
  private
    fJSONArray: TJSONArray;
    fCurrentIndex: int32;
  private
    procedure JSONToForm;
    procedure ClearForm;
    procedure CreateMode;
    procedure BrowseMode;
    procedure EditMode;
  public
    { Public declarations }
  end;

var
  frmMain: TfrmMain;

implementation
uses
  strutils,
  REST.Types;

{$R *.fmx}

procedure TfrmMain.ClearForm;
begin
  spedEmployeeNumber.Value   :=  0;
  edFirstName.Text           :=  '';
  edLastName.Text            :=  '';
  edtPhoneExt.Text           :=  '';
  spedDepartmentNumber.Value :=  0;
  edtJobCode.Text            :=  '';
  edtJobGrade.Text           :=  '';
  edtJobCountry.Text         :=  '';
  spedSalary.Value           := 0.0;
  dtedHireDate.DateTime      :=  Now;
end;

procedure TfrmMain.btnCommitClick(Sender: TObject);
begin
  //- Prepare to POST data to 'employees' end-point.
  RESTRequest.Resource := 'employees';
  RESTRequest.Method := TRESTRequestMethod.rmPOST;
  RESTRequest.Response := RESTResponse;

  //- Populate the JSON resource to post.
  RESTRequest.Body.ClearBody;
  with RESTRequest.Body.JSONWriter do begin
    WriteStartObject;
    WritePropertyName('FirstName');
    WriteValue(edFirstName.Text);
    WritePropertyName('LastName');
    WriteValue(edLastName.Text);
    WritePropertyName('PhoneExt');
    WriteValue(edtPhoneExt.Text);
    WritePropertyName('DepartmentNumber');
    WriteValue(spedDepartmentNumber.Value);
    WritePropertyName('JobCode');
    WriteValue(edtJobCode.Text);
    WritePropertyName('JobGrade');
    WriteValue(edtJobGrade.Text);
    WritePropertyName('JobCountry');
    WriteValue(edtJobCountry.Text);
    WritePropertyName('Salary');
    WriteValue(spedSalary.Value);
    WritePropertyName('HireDate');
    WriteValue(FormatDateTime('MM/DD/YYYY 00:00:00',dtedHireDate.DateTime));
    WriteEnd;
  end;

  // Adjust the form to recieve the result.
  BrowseMode;

  // Execute the request
  RESTRequest.Execute;

  //- Re-read
  btnReadClick(Sender);

end;

procedure TfrmMain.JSONToForm;
var
  O: TJSONObject;
begin
  ClearForm;
  if fJSONArray.Count>0 then begin
    O := fJSONArray.Items[fCurrentIndex] as TJSONObject;
    spedEmployeeNumber.Value     :=  StrToInt( o.GetValue('EmployeeNumber').ToString );
    edFirstName.Text             :=  o.GetValue('FirstName').Value;
    edLastName.Text              :=  o.GetValue('LastName').Value;
    if assigned(o.GetValue('PhoneExt')) then begin
      edtPhoneExt.Text           :=  o.GetValue('PhoneExt').Value;
    end;
    spedDepartmentNumber.Value   :=  StrToFloat( o.GetValue('DepartmentNumber').Value );
    edtJobCode.Text              :=  o.GetValue('JobCode').Value;
    edtJobGrade.Text             :=  o.GetValue('JobGrade').Value;
    edtJobCountry.Text           :=  o.GetValue('JobCountry').Value;
    spedSalary.Text              :=  o.GetValue('Salary').Value;
    dtedHireDate.DateTime        :=  StrToDateTime( o.GetValue('HireDate').Value );
  end;
end;

procedure TfrmMain.CreateMode;
begin
  // Read Only
  edFirstName.ReadOnly            := False;
  edLastName.ReadOnly             := False;
  edtPhoneExt.ReadOnly            := False;
  edtJobCode.ReadOnly             := False;
  edtJobGrade.ReadOnly            := False;
  spedSalary.ReadOnly             := False;
  edtJobCountry.ReadOnly          := False;
  dtedHireDate.ReadOnly           := False;
  // Text Prompt
  edFirstName.TextPrompt          := 'First Name';
  edLastName.TextPrompt           := 'Last Name';
  edtPhoneExt.TextPrompt          := 'Phone Ext';
  spedDepartmentNumber.TextPrompt := 'Dept No';
  spedDepartmentNumber.ReadOnly   := False;
  edtJobCode.TextPrompt           := 'Job Code';
  edtJobGrade.TextPrompt          := 'Job Grade';
  edtJobCountry.TextPrompt        := 'Job Country';
  spedSalary.TextPrompt           := '0.0';
  // Text Color
  edFirstName.TextSettings.FontColor          := TAlphaColorRec.Red;
  edLastName.TextSettings.FontColor           := TAlphaColorRec.Red;
  edtPhoneExt.TextSettings.FontColor          := TAlphaColorRec.Red;
  spedDepartmentNumber.TextSettings.FontColor := TAlphaColorRec.Red;
  edtJobCode.TextSettings.FontColor           := TAlphaColorRec.Red;
  edtJobGrade.TextSettings.FontColor          := TAlphaColorRec.Red;
  edtJobCountry.TextSettings.FontColor        := TAlphaColorRec.Red;
  spedSalary.TextSettings.FontColor           := TAlphaColorRec.Red;
  dtedHireDate.TextSettings.FontColor         := TAlphaColorRec.Red;
  // adjust buttons
  btnRead.Enabled    := False;
  btnNext.Enabled    := False;
  btnPrev.Enabled    := False;
  btnLast.Enabled    := False;
  btnFirst.Enabled   := False;
  btnCreate.Enabled  := False;
  btnCommit.Enabled  := True;
  btnEdit.Enabled    := False;
  btnUpdate.Enabled  := False;
  btnDelete.Enabled  := False;
end;

procedure TfrmMain.EditMode;
begin
  // Read Only
  edFirstName.ReadOnly            := False;
  edLastName.ReadOnly             := False;
  edtPhoneExt.ReadOnly            := False;
  edtJobCode.ReadOnly             := False;
  edtJobGrade.ReadOnly            := False;
  edtJobCountry.ReadOnly          := False;
  spedDepartmentNumber.ReadOnly   := False;
  spedSalary.ReadOnly             := False;
  dtedHireDate.ReadOnly           := False;
  // Text Prompt
  edFirstName.TextPrompt          := 'First Name';
  edLastName.TextPrompt           := 'Last Name';
  edtPhoneExt.TextPrompt          := 'Phone Ext';
  spedDepartmentNumber.TextPrompt := 'Dept No';
  edtJobCode.TextPrompt           := 'Job Code';
  edtJobGrade.TextPrompt          := 'Job Grade';
  edtJobCountry.TextPrompt        := 'Job Country';
  spedSalary.TextPrompt           := 'Salary';
  // Text Color
  edFirstName.TextSettings.FontColor          := TAlphaColorRec.Blue;
  edLastName.TextSettings.FontColor           := TAlphaColorRec.Blue;
  edtPhoneExt.TextSettings.FontColor          := TAlphaColorRec.Blue;
  spedDepartmentNumber.TextSettings.FontColor := TAlphaColorRec.Blue;
  edtJobCode.TextSettings.FontColor           := TAlphaColorRec.Blue;
  edtJobGrade.TextSettings.FontColor          := TAlphaColorRec.Blue;
  edtJobCountry.TextSettings.FontColor        := TAlphaColorRec.Blue;
  spedSalary.TextSettings.FontColor           := TAlphaColorRec.Blue;
  dtedHireDate.TextSettings.FontColor         := TAlphaColorRec.Blue;
  // adjust buttons
  btnRead.Enabled    := False;
  btnNext.Enabled    := False;
  btnPrev.Enabled    := False;
  btnLast.Enabled    := False;
  btnFirst.Enabled   := False;
  btnCreate.Enabled  := False;
  btnCommit.Enabled  := False;
  btnEdit.Enabled    := False;
  btnUpdate.Enabled  := True;
  btnDelete.Enabled  := False;
end;

procedure TfrmMain.BrowseMode;
begin
  spedEmployeeNumber.Enabled     := True;
  // Read only
  edFirstName.ReadOnly           := True;
  edLastName.ReadOnly            := True;
  edtPhoneExt.ReadOnly           := True;
  edtJobCode.ReadOnly            := True;
  edtJobGrade.ReadOnly           := True;
  edtJobCountry.ReadOnly         := True;
  spedSalary.ReadOnly            := True;
  spedDepartmentNumber.ReadOnly  := True;
  dtedHireDate.ReadOnly          := True;
  // Text prompt
  edFirstName.TextPrompt          := '';
  edLastName.TextPrompt           := '';
  edtPhoneExt.TextPrompt          := '';
  spedDepartmentNumber.TextPrompt := '';
  edtJobCode.TextPrompt           := '';
  edtJobGrade.TextPrompt          := '';
  edtJobCountry.TextPrompt        := '';
  spedSalary.TextPrompt           := '';
  // Text Color
  edFirstName.TextSettings.FontColor          := TAlphaColorRec.Black;
  edLastName.TextSettings.FontColor           := TAlphaColorRec.Black;
  edtPhoneExt.TextSettings.FontColor          := TAlphaColorRec.Black;
  spedDepartmentNumber.TextSettings.FontColor := TAlphaColorRec.Black;
  edtJobCode.TextSettings.FontColor           := TAlphaColorRec.Black;
  edtJobGrade.TextSettings.FontColor          := TAlphaColorRec.Black;
  edtJobCountry.TextSettings.FontColor        := TAlphaColorRec.Black;
  spedSalary.TextSettings.FontColor           := TAlphaColorRec.Black;
  dtedHireDate.TextSettings.FontColor         := TAlphaColorRec.Black;
  // adjust buttons
  btnRead.Enabled    := True;
  btnNext.Enabled    := True;
  btnPrev.Enabled    := True;
  btnLast.Enabled    := True;
  btnFirst.Enabled   := True;
  btnCreate.Enabled  := True;
  btnCommit.Enabled  := False;
  btnEdit.Enabled    := True;
  btnUpdate.Enabled  := False;
  btnDelete.Enabled  := True;
end;

procedure TfrmMain.btnCreateClick(Sender: TObject);
begin
  //- Clear the form and adjust text read-only and prompts.
  ClearForm;
  CreateMode;
end;

procedure TfrmMain.btnDeleteClick(Sender: TObject);
var
  o: TJSONObject;
begin
  //- Prepare to DELETE data from 'employees' end-point.
  RESTRequest.Resource := 'employees/'+spedEmployeeNumber.Text;
  RESTRequest.Method   := TRESTRequestMethod.rmDELETE;
  RESTRequest.Response := RESTResponse;

  //- Add the employee number as a parameter to the request.
  RESTREquest.Params.Clear;
  with RESTRequest.Params.AddItem do begin
    name := 'EmployeeNumber';
    value := spedEmployeeNumber.Text;
  end;

  // Execute the request
  RESTRequest.Execute;

  //- Re-read
  btnReadClick(Sender);
end;

procedure TfrmMain.btnEditClick(Sender: TObject);
begin
  EditMode;
end;

procedure TfrmMain.btnFirstClick(Sender: TObject);
begin
  fCurrentIndex := 0;
  JSONToForm;
end;

procedure TfrmMain.btnLastClick(Sender: TObject);
begin
  if fJSONArray.Count>0 then begin
    fCurrentIndex := pred(fJSONArray.Count);
  end else begin
    fCurrentIndex := 0;
  end;
  JSONToForm;
end;

procedure TfrmMain.btnNextClick(Sender: TObject);
begin
  if fCurrentIndex<pred(fJSONArray.Count) then begin
    inc(fCurrentIndex);
  end;
  JSONToForm;
end;

procedure TfrmMain.btnPrevClick(Sender: TObject);
begin
  if fCurrentIndex>0 then begin
    dec(fCurrentIndex);
  end;
  JSONToForm;
end;

procedure TfrmMain.btnReadClick(Sender: TObject);
var
  Param: TRESTRequestParameter;
begin
  //- Request data from 'employees' end-point.
  RESTRequest.Resource := 'employees';
  RESTRequest.Method   := TRESTRequestMethod.rmGet;
  RESTRequest.Response := RESTResponse;

  // Make request.
  RESTRequest.Execute;

  //- Decode the data into a class global
  if assigned(fJSONArray) then begin
    fJSONArray.DisposeOf;
  end;
  fJSONArray := TJSONObject.ParseJSONValue(RESTResponse.Content) as TJSONArray;

  //- set index.
  fCurrentIndex := 0;

  //- Load current resource to form.
  JSONToForm;
end;

procedure TfrmMain.btnUpdateClick(Sender: TObject);
begin
  //- Prepare to PUT data to 'employees' end-point.
  RESTRequest.Resource := 'employees/'+spedEmployeeNumber.Text;
  RESTRequest.Method   := TRESTRequestMethod.rmPUT;
  RESTRequest.Response := RESTResponse;

  //- Populate the JSON resource to post.
  RESTRequest.Body.ClearBody;
  with RESTRequest.Body.JSONWriter do begin
    WriteStartObject;
    WritePropertyName('FirstName');
    WriteValue(edFirstName.Text);
    WritePropertyName('LastName');
    WriteValue(edLastName.Text);
    WritePropertyName('PhoneExt');
    WriteValue(edtPhoneExt.Text);
    WritePropertyName('DepartmentNumber');
    WriteValue(spedDepartmentNumber.Value);
    WritePropertyName('JobCode');
    WriteValue(edtJobCode.Text);
    WritePropertyName('JobGrade');
    WriteValue(edtJobGrade.Text);
    WritePropertyName('JobCountry');
    WriteValue(edtJobCountry.Text);
    WritePropertyName('Salary');
    WriteValue(spedSalary.Value);
    WritePropertyName('HireDate');
    WriteValue(FormatDateTime('MM/DD/YYYY 00:00:00',dtedHireDate.DateTime));
    WriteEnd;
  end;

  // Adjust the form to recieve the result.
  BrowseMode;

  // Execute the request
  RESTRequest.Execute;

  //- Re-read
  btnReadClick(Sender);
end;

end.
