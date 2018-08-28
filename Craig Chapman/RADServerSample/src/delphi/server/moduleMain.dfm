object EmployeesResource1: TEmployeesResource1
  OldCreateOrder = False
  Height = 179
  Width = 214
  object conn: TFDConnection
    Params.Strings = (
      'ConnectionDef=EMPLOYEE')
    LoginPrompt = False
    Left = 52
    Top = 17
  end
  object qry: TFDQuery
    Connection = conn
    SQL.Strings = (
      'SELECT * FROM EMPLOYEE')
    Left = 52
    Top = 65
  end
end
