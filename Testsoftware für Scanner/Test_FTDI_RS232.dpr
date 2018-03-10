program Test_FTDI_RS232;

uses
  Forms,
  Main in 'Main.pas' {Form1},
  Comms in 'Comms.pas',
  RS232 in 'RS232.pas',
  FTDI in 'FTDI.pas',
  D2XXUnit in 'D2XXUnit.pas',
  CfgUnit in 'CfgUnit.pas';

{$R *.RES}

begin
  Application.Initialize;
  Application.CreateForm(TForm1, Form1);
  Application.Run;
end.
