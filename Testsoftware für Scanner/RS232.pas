unit RS232;

interface
uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, ExtCtrls, Comms ,Main;

var
  com :Tcomport; // Eintrag um die Comms Unit benutzen zu können

  Port       :TPortType       = COM1;
  BauRate    :TBaudRate       = br9600;
  DBit       :TDataBits       = dbEight;
  Parit      :TParityBits     = prNone;
  StpBit     :TStopBits       = sbOneStopBit;
  DTR_Enable :TDtrFlowControl = dtrEnable;
  RTS_Enable :TRtsFlowControl = rtsEnable;
  RsEvents   :TEvent;                     //[evCTS, evDSR, evRLSD];



  RS232_Ergebn    : real;
  RS232_Einheit   : string;


// COM Port
procedure ComSettings;
procedure OpenCom;
procedure CloseCom;


// RS232 Aufrufe
function RS232_Write(kommand:string):string;
function RS232_Read:string;


Function RS232_PunktToKomma(s: string):string;

implementation



procedure ComSettings;
begin
  Com.SetPort(Port);
  Com.SetBaudRate(BauRate);
  Com.DataBits := DBit;
  Com.Parity.Bits := Parit;
  Com.StopBits := StpBit;
  com.FlowControl.ControlDtr := DTR_Enable;
  com.FlowControl.ControlRts := RTS_Enable;

  com.SyncMethod := smSynchronize; // Synchrone datenübertragung benötigt ??????
  com.Events := [evRxChar, evTxEmpty, evRxFlag, evRing, evBreak, evCTS,
            evDSR, evError, evRLSD, evRx80Full];
end;

procedure OpenCom;
begin
 if not Com.Connected then
 begin
    Com.Open;
 end;
end;

procedure CloseCom;
begin
  Com.close;
end;


// *******************************************************
// *******           Command senden              *********
// *******************************************************
function RS232_Write(kommand:string):string;
var
  TextLang : Dword;
begin
  kommand := kommand + #13;

  TextLang := com.WriteString(kommand,true);
end;

// *******************************************************
// *******             Buffer read               *********
// *******************************************************
function RS232_Read:string;
var
  i        : DWord;  // Time out Zähler
  u        : word;
  Echar    : Dword;
  Zeichen  : char;
  ErgebnStr: string;
  switch   : byte;
begin
  ErgebnStr:='';
  i := 0;
  u:= 0;
  switch := 0;
  main.Form1.Memo2.Clear;
  repeat

     Echar := Com.InQue;

     if Echar > 0 then
     begin
        Com.Read(Zeichen, 1,True);

        main.Form1.memo2.Lines.Add(' '+ inttostr(Echar) +
           '               ' +inttostr(ord(Zeichen)) +
           '               ' + Zeichen);   
        ErgebnStr := ErgebnStr + zeichen;

        if zeichen = #13 then switch := 1


        //if zeichen <> #10 then ErgebnStr := ErgebnStr + zeichen;
     end;

     if switch = 1 then
     begin
       sleep(1);
       Echar := Com.InQue;

       if Echar > 0 then
       begin
          Com.Read(Zeichen, 1,True);
          main.Form1.memo2.Lines.Add(' '+ inttostr(Echar) +
           '               ' +inttostr(ord(Zeichen)) +
           '               ' + Zeichen);
          ErgebnStr := ErgebnStr + zeichen;

             switch := 0;

        //if zeichen <> #10 then ErgebnStr := ErgebnStr + zeichen;
       end;
     end;

 // sleep(1);
    //Application.ProcessMessages;
    //main.form1.label2.Caption:= inttostr(i);
    inc(i);
  until (Zeichen = #13) or (I > 500000);
  if I >= 500000 Then Showmessage('RS232 lese Time Out');
  //showmessage('ErgebnStr = >'+ErgebnStr+'<' + 'I = '+ inttostr(i));
  result := ErgebnStr;
end;




// *****************************************************
// ****     Im String Punkt durch komma resetzen    ****
// *****************************************************

Function RS232_PunktToKomma(s: string):string;
begin
  result:=copy(s,0,pos('.',s)-1)+','+copy( s, pos('.',s)+1, length(s)-pos('.',s));
end;



end.
