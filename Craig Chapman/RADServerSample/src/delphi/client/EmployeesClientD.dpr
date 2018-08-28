program EmployeesClientD;

uses
  System.StartUpCopy,
  FMX.Forms,
  formMain in 'formMain.pas' {frmMain};

{$R *.res}

begin
  Application.Initialize;
  Application.CreateForm(TfrmMain, frmMain);
  Application.Run;
end.
