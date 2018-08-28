object EmployeesResource1: TEmployeesResource1
  OldCreateOrder = False
  Height = 150
  Width = 215
  object conn: TFDConnection
    Params.Strings = (
      'ConnectionDef=EMPLOYEE')
    LoginPrompt = False
    Left = 45
    Top = 15
  end
  object qry: TFDQuery
    Connection = conn
    SQL.Strings = (
      'SELECT * FROM EMPLOYEE')
    Left = 45
    Top = 63
  end
end
