unit FTDI;


interface
Uses Windows,Dialogs,SysUtils,D2XXUNIT,
   Classes,StdCtrls,ExtCtrls,CfgUnit,ComCtrls,Messages,Forms , main;

Type
  Names = Array[1..20] of string;
  Names_Ptr = ^Names;

var
  My_Names    : Names;
  PortAIsOpen : boolean;
  EmpfZeichen : integer;

  BitBang_CbusDbus : byte = 0;

procedure List_Devs( My_Names_Ptr : Names_Ptr);
function write_value(enable,data : byte;DName : String) : boolean;
function read_value(var data : byte;DName : String) : boolean;


function FT_RS232_Send(DName,SendTxt: string): boolean;
function FT_RS232_Read(var DataStrg: string ;DName: string):integer;
function FT_WaitOnChar : integer;


implementation



procedure List_Devs( My_Names_Ptr : Names_Ptr);
Var res : FT_Result;
NoOfDevs,i,J,k : integer;
Name : String;
done : boolean;
begin
PortAIsOpen := False;
Name := '';
res := GetFTDeviceCount;
if res <> Ft_OK then exit;
NoOfDevs := FT_Device_Count;
j := 0;
k := 1;
if NoOfDevs > 0 then
  begin
    repeat
    res := GetFTDeviceDescription(J);
   if res = Ft_OK then
      begin
      My_Names_Ptr[k]:= FT_Device_String;
      k := k + 1;
      end;
    J := J + 1;
    until (J = NoOfDevs);
  end;

end;


function write_value(enable,data : byte;DName : String) : boolean;
var
status : integer;
tmpval : byte;
res : FT_Result;
begin

write_value := false;
status :=0;
//status :=  Open_USB_Device_By_Device_Description(DName);
if status = 0 then
  begin
  tmpval := data AND $F;
  tmpval := tmpval OR ((enable AND $F) * 16);


    res := Set_USB_Device_BitMode(tmpval,$20); // enable CBitBang


  if (res = FT_OK) then write_value := true;
  //status := Close_USB_Device;
  end;

end;

function read_value(var data : byte;DName : String) : boolean;
var
  status : integer;
  tmpval : byte;
  res : FT_Result;
begin
read_value := false;
status :=0;
//status := Open_USB_Device_By_Device_Description(DName);
if status = 0 then
  begin
  res := Get_USB_Device_BitMode(data);
  if (res = FT_OK) then read_value := true;
  //status := Close_USB_Device;
  end;
end;



function FT_RS232_Send(DName,SendTxt: string):boolean;
var
  written : byte;
  i : byte;
  StrgLang : word;
  status : integer;
begin
status := 0;
//status := Open_USB_Device_By_Device_Description(DName);
if status = 0 then
  begin
   StrgLang := length(SendTxt);
   StrgLang := StrgLang + 1;
   SendTxt := SendTxt + #13;

   // Daten in den USB Buffer schreiben
   // Write data to the USB buffer
   for i := 1 to StrgLang do
   begin
     FT_Out_Buffer[i-1]:= ord(SendTxt[i]);
     //showmessage(chr(FT_Out_Buffer[i-1]));
   end;

   //  Bytes aus USB Buffer senden
   // Send bytes from USB buffer
   written:= Write_USB_Device_Buffer(StrgLang);
   if (written<>(StrgLang)) then
   begin
     showmessage('No data sent!');
   end;
   //status := Close_USB_Device;
  end;
end;


function FT_WaitOnChar : integer;
var
  res        : integer;
  k          : integer;
  MerkZaeler : integer;
  byte       : integer;
  sch        : integer;
begin
  K      := 0;
  sch    := 0;
  result := 1;

  repeat
    inc (k);
    Application.ProcessMessages;         // Systemeingaben ermöglichen
    res := Get_USB_Device_QueueStatus(); // Abfragen ob Zeichen im Buffer

    if (FT_Q_Bytes>0) then               // Mehr als 0 Zeichen dann
    begin
      if sch = 0 then
      begin
        sch := 1;
        MerkZaeler := k;
        byte := FT_Q_Bytes;
      end;

      if k = (MerkZaeler + 6000) then    // Mehrere Durchleufe werden benötigt,
      begin                              // da sonst nicht alle Zeichen im Buffer

        if FT_Q_Bytes > byte then
        begin
           byte :=FT_Q_Bytes;
           MerkZaeler := k;
        end
        else
        if byte = FT_Q_Bytes then       // Vergleich ob die Anzahl der Zeichen
        begin                           // im Buffer zweimal gleich sind wenn
           result := 0;                 // ja Schleife unterbrechen und  im
           break;                       // Programm weiter und Daten auslesen
        end;
      end;

      //memo1.Lines.Add('= '+inttostr(k) + ' ' + inttostr(FT_Q_Bytes)) ;
    end;
  until k >30000;

  //if k >= 30000 then showmessage ('Time out Error');
end;


function FT_RS232_Read(var DataStrg:string ;DName: string):integer;
var
  i,k       : word;
  usbstatus : integer;
  MemoSTR   : string;
  ch        : byte;
begin
      result := 1;
      MemoSTR :='';
      usbstatus:=Get_USB_Device_QueueStatus();
      EmpfZeichen := FT_Q_Bytes; // Anz. Empf. Zeichen zur Anzeige MainForm
                                 // Num. Rec. Characters to display MainForm
      if (FT_Q_Bytes>0) then
      begin
         // Daten sind vorhanden und können ausgelesen werden
         i := Read_USB_Device_Buffer(FT_Q_Bytes);
         // EmpfZeichen := i;
         for k:=0 to i do
         begin
           //showmessage('Byte '+inttostr(FT_In_Buffer[k])+' empfangen');
           // Data is available and can be read out
           ch := (FT_In_Buffer[k]);
                     main.Form1.Memo2.Lines.Add(' '+ inttostr(i) +
           '         ' +inttostr(ch) +
           '         ' + chr(ch));
           if (ch = 13) and (i-1 = k) then
           begin
              result := 0;
              break;
           end;
           if (ch >= 32) or (ch < 122) then
           begin
             MemoSTR := MemoSTR + chr(ch);
           end;
         end;
      end;

    DataStrg := MemoSTR;

end;

end.
