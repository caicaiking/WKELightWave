object Form1: TForm1
  Left = 203
  Top = 122
  Width = 720
  Height = 595
  Caption = 'Scanner Testsoftware'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 8
    Top = 8
    Width = 329
    Height = 361
    Caption = 'Panel1'
    TabOrder = 0
    object Label1: TLabel
      Left = 197
      Top = 16
      Width = 20
      Height = 13
      Caption = 'Que'
    end
    object Label2: TLabel
      Left = 230
      Top = 16
      Width = 27
      Height = 13
      Caption = 'ASCII'
    end
    object Label3: TLabel
      Left = 267
      Top = 16
      Width = 22
      Height = 13
      Caption = 'Char'
    end
    object Edit1: TEdit
      Left = 16
      Top = 16
      Width = 169
      Height = 21
      TabOrder = 0
      Text = '1'
      OnKeyDown = Edit1KeyDown
    end
    object Button3: TButton
      Left = 16
      Top = 48
      Width = 169
      Height = 25
      Caption = 'send'
      TabOrder = 1
      OnClick = Button3Click
    end
    object Memo1: TMemo
      Left = 16
      Top = 80
      Width = 169
      Height = 233
      Lines.Strings = (
        'Memo1')
      ScrollBars = ssVertical
      TabOrder = 2
    end
    object Button4: TButton
      Left = 16
      Top = 320
      Width = 169
      Height = 25
      Caption = 'Memo CLR'
      TabOrder = 3
      OnClick = Button4Click
    end
    object Memo2: TMemo
      Left = 192
      Top = 32
      Width = 121
      Height = 281
      Lines.Strings = (
        'Memo2')
      ScrollBars = ssVertical
      TabOrder = 4
    end
    object Button7: TButton
      Left = 192
      Top = 320
      Width = 121
      Height = 25
      Caption = 'clr'
      TabOrder = 5
      OnClick = Button7Click
    end
  end
  object Panel2: TPanel
    Left = 8
    Top = 376
    Width = 329
    Height = 185
    TabOrder = 1
    object GroupBox1: TGroupBox
      Left = 8
      Top = 32
      Width = 153
      Height = 145
      Caption = 'RS232'
      Enabled = False
      TabOrder = 0
      object ComboBox4: TComboBox
        Left = 8
        Top = 21
        Width = 73
        Height = 21
        ItemHeight = 13
        TabOrder = 0
        Text = 'ComboBox4'
        OnChange = ComboBox4Change
        Items.Strings = (
          'COM1'
          'COM2'
          'COM3'
          'COM4'
          'COM5'
          'COM6'
          'COM7'
          'COM8')
      end
      object Button5: TButton
        Left = 8
        Top = 72
        Width = 75
        Height = 25
        Caption = 'Open RS232'
        TabOrder = 1
        OnClick = Button5Click
      end
      object Button9: TButton
        Left = 8
        Top = 112
        Width = 75
        Height = 25
        Caption = 'Close RS232'
        TabOrder = 2
        OnClick = Button9Click
      end
      object RadioButton6: TRadioButton
        Left = 96
        Top = 72
        Width = 49
        Height = 17
        Caption = '9600'
        Checked = True
        TabOrder = 3
        TabStop = True
        OnClick = RadioButton6Click
      end
      object RadioButton7: TRadioButton
        Left = 96
        Top = 96
        Width = 49
        Height = 17
        Caption = '19200'
        TabOrder = 4
        OnClick = RadioButton7Click
      end
      object RadioButton8: TRadioButton
        Left = 96
        Top = 120
        Width = 49
        Height = 17
        Caption = '38400'
        TabOrder = 5
        OnClick = RadioButton8Click
      end
    end
    object GroupBox2: TGroupBox
      Left = 168
      Top = 32
      Width = 153
      Height = 145
      Caption = 'FTDI'
      TabOrder = 1
      object Label4: TLabel
        Left = 9
        Top = 48
        Width = 43
        Height = 13
        Caption = 'Baudrate'
      end
      object Button6: TButton
        Left = 8
        Top = 72
        Width = 137
        Height = 25
        Caption = 'Open FTDI'
        TabOrder = 0
        OnClick = Button6Click
      end
      object ComboBox1: TComboBox
        Left = 8
        Top = 17
        Width = 137
        Height = 21
        ItemHeight = 13
        TabOrder = 1
        OnDropDown = ComboBox1DropDown
      end
      object Button10: TButton
        Left = 8
        Top = 112
        Width = 137
        Height = 25
        Caption = 'Close FTDI'
        TabOrder = 2
        OnClick = Button10Click
      end
      object ComboBox2: TComboBox
        Left = 64
        Top = 44
        Width = 81
        Height = 21
        ItemHeight = 13
        TabOrder = 3
        Text = 'ComboBox2'
        OnClick = ComboBox2Click
        Items.Strings = (
          '1 = 9600'
          '2 = 14400'
          '3 = 19200'
          '4 = 38400'
          '5 = 57600'
          '6 = 115200'
          '7 = 230400'
          '8 = 460800'
          '9 = 921600')
      end
    end
    object RadioButton1: TRadioButton
      Left = 176
      Top = 8
      Width = 57
      Height = 17
      Caption = 'FTDI'
      Checked = True
      TabOrder = 2
      TabStop = True
      OnClick = RadioButton1Click
    end
    object RadioButton2: TRadioButton
      Left = 8
      Top = 8
      Width = 57
      Height = 17
      Caption = 'RS232'
      TabOrder = 3
      OnClick = RadioButton2Click
    end
  end
  object Panel3: TPanel
    Left = 344
    Top = 8
    Width = 361
    Height = 553
    TabOrder = 2
    object Label5: TLabel
      Left = 302
      Top = 8
      Width = 23
      Height = 13
      Caption = 'Time'
    end
    object Label6: TLabel
      Left = 294
      Top = 28
      Width = 32
      Height = 13
      Caption = 'Label6'
    end
    object Label7: TLabel
      Left = 294
      Top = 52
      Width = 32
      Height = 13
      Caption = 'Label7'
    end
    object Label8: TLabel
      Left = 294
      Top = 76
      Width = 32
      Height = 13
      Caption = 'Label8'
    end
    object Label9: TLabel
      Left = 294
      Top = 100
      Width = 32
      Height = 13
      Caption = 'Label9'
    end
    object Label10: TLabel
      Left = 294
      Top = 124
      Width = 38
      Height = 13
      Caption = 'Label10'
    end
    object Label11: TLabel
      Left = 294
      Top = 148
      Width = 38
      Height = 13
      Caption = 'Label11'
    end
    object Label12: TLabel
      Left = 294
      Top = 172
      Width = 38
      Height = 13
      Caption = 'Label12'
    end
    object Label13: TLabel
      Left = 294
      Top = 196
      Width = 38
      Height = 13
      Caption = 'Label13'
    end
    object Label14: TLabel
      Left = 294
      Top = 220
      Width = 38
      Height = 13
      Caption = 'Label14'
    end
    object Label15: TLabel
      Left = 294
      Top = 244
      Width = 38
      Height = 13
      Caption = 'Label15'
    end
    object Label16: TLabel
      Left = 294
      Top = 308
      Width = 38
      Height = 13
      Caption = 'Label16'
    end
    object Label17: TLabel
      Left = 294
      Top = 332
      Width = 38
      Height = 13
      Caption = 'Label17'
    end
    object Label18: TLabel
      Left = 294
      Top = 356
      Width = 38
      Height = 13
      Caption = 'Label18'
    end
    object Label19: TLabel
      Left = 294
      Top = 380
      Width = 38
      Height = 13
      Caption = 'Label19'
    end
    object Label20: TLabel
      Left = 294
      Top = 404
      Width = 38
      Height = 13
      Caption = 'Label20'
    end
    object Label21: TLabel
      Left = 294
      Top = 428
      Width = 38
      Height = 13
      Caption = 'Label21'
    end
    object Label22: TLabel
      Left = 294
      Top = 452
      Width = 38
      Height = 13
      Caption = 'Label22'
    end
    object Label23: TLabel
      Left = 294
      Top = 476
      Width = 38
      Height = 13
      Caption = 'Label23'
    end
    object Label24: TLabel
      Left = 294
      Top = 500
      Width = 38
      Height = 13
      Caption = 'Label24'
    end
    object Label25: TLabel
      Left = 294
      Top = 524
      Width = 38
      Height = 13
      Caption = 'Label25'
    end
    object Label26: TLabel
      Left = 334
      Top = 28
      Width = 13
      Height = 13
      Caption = 'ms'
    end
    object Label27: TLabel
      Left = 334
      Top = 52
      Width = 13
      Height = 13
      Caption = 'ms'
    end
    object Label28: TLabel
      Left = 334
      Top = 76
      Width = 13
      Height = 13
      Caption = 'ms'
    end
    object Label29: TLabel
      Left = 334
      Top = 100
      Width = 13
      Height = 13
      Caption = 'ms'
    end
    object Label30: TLabel
      Left = 334
      Top = 124
      Width = 13
      Height = 13
      Caption = 'ms'
    end
    object Label31: TLabel
      Left = 334
      Top = 148
      Width = 13
      Height = 13
      Caption = 'ms'
    end
    object Label32: TLabel
      Left = 334
      Top = 172
      Width = 13
      Height = 13
      Caption = 'ms'
    end
    object Label33: TLabel
      Left = 334
      Top = 196
      Width = 13
      Height = 13
      Caption = 'ms'
    end
    object Label34: TLabel
      Left = 334
      Top = 220
      Width = 13
      Height = 13
      Caption = 'ms'
    end
    object Label35: TLabel
      Left = 334
      Top = 244
      Width = 13
      Height = 13
      Caption = 'ms'
    end
    object Label36: TLabel
      Left = 334
      Top = 308
      Width = 13
      Height = 13
      Caption = 'ms'
    end
    object Label37: TLabel
      Left = 334
      Top = 332
      Width = 13
      Height = 13
      Caption = 'ms'
    end
    object Label38: TLabel
      Left = 334
      Top = 356
      Width = 13
      Height = 13
      Caption = 'ms'
    end
    object Label39: TLabel
      Left = 334
      Top = 380
      Width = 13
      Height = 13
      Caption = 'ms'
    end
    object Label40: TLabel
      Left = 334
      Top = 404
      Width = 13
      Height = 13
      Caption = 'ms'
    end
    object Label41: TLabel
      Left = 334
      Top = 428
      Width = 13
      Height = 13
      Caption = 'ms'
    end
    object Label42: TLabel
      Left = 334
      Top = 452
      Width = 13
      Height = 13
      Caption = 'ms'
    end
    object Label43: TLabel
      Left = 334
      Top = 476
      Width = 13
      Height = 13
      Caption = 'ms'
    end
    object Label44: TLabel
      Left = 334
      Top = 500
      Width = 13
      Height = 13
      Caption = 'ms'
    end
    object Label45: TLabel
      Left = 334
      Top = 524
      Width = 13
      Height = 13
      Caption = 'ms'
    end
    object GroupBox3: TGroupBox
      Left = 16
      Top = 8
      Width = 273
      Height = 257
      Caption = 'Command'
      TabOrder = 0
      object Button1: TButton
        Left = 112
        Top = 16
        Width = 33
        Height = 21
        Caption = '1'
        TabOrder = 0
        OnClick = Button1Click
      end
      object Button2: TButton
        Left = 112
        Top = 40
        Width = 33
        Height = 21
        Caption = '2'
        TabOrder = 1
        OnClick = Button2Click
      end
      object Button8: TButton
        Left = 112
        Top = 64
        Width = 33
        Height = 21
        Caption = '3'
        TabOrder = 2
        OnClick = Button8Click
      end
      object Button11: TButton
        Left = 112
        Top = 88
        Width = 33
        Height = 21
        Caption = '4'
        TabOrder = 3
        OnClick = Button11Click
      end
      object Button12: TButton
        Left = 112
        Top = 112
        Width = 33
        Height = 21
        Caption = '5'
        TabOrder = 4
        OnClick = Button12Click
      end
      object Button13: TButton
        Left = 112
        Top = 136
        Width = 33
        Height = 21
        Caption = '6'
        TabOrder = 5
        OnClick = Button13Click
      end
      object Button14: TButton
        Left = 112
        Top = 160
        Width = 33
        Height = 21
        Caption = '7'
        TabOrder = 6
        OnClick = Button14Click
      end
      object Button15: TButton
        Left = 112
        Top = 184
        Width = 33
        Height = 21
        Caption = '8'
        TabOrder = 7
        OnClick = Button15Click
      end
      object Button16: TButton
        Left = 112
        Top = 208
        Width = 33
        Height = 21
        Caption = '9'
        TabOrder = 8
        OnClick = Button16Click
      end
      object Button17: TButton
        Left = 112
        Top = 232
        Width = 33
        Height = 21
        Caption = '10'
        TabOrder = 9
        OnClick = Button17Click
      end
      object Edit2: TEdit
        Left = 8
        Top = 16
        Width = 97
        Height = 21
        TabOrder = 10
        Text = 'Edit2'
        OnChange = Edit2Change
      end
      object Edit3: TEdit
        Left = 8
        Top = 40
        Width = 97
        Height = 21
        TabOrder = 11
        Text = 'Edit2'
        OnChange = Edit3Change
      end
      object Edit4: TEdit
        Left = 8
        Top = 64
        Width = 97
        Height = 21
        TabOrder = 12
        Text = 'Edit2'
        OnChange = Edit4Change
      end
      object Edit5: TEdit
        Left = 8
        Top = 88
        Width = 97
        Height = 21
        TabOrder = 13
        Text = 'Edit2'
        OnChange = Edit5Change
      end
      object Edit6: TEdit
        Left = 8
        Top = 112
        Width = 97
        Height = 21
        TabOrder = 14
        Text = 'Edit2'
        OnChange = Edit6Change
      end
      object Edit7: TEdit
        Left = 8
        Top = 136
        Width = 97
        Height = 21
        TabOrder = 15
        Text = 'Edit2'
        OnChange = Edit7Change
      end
      object Edit8: TEdit
        Left = 8
        Top = 160
        Width = 97
        Height = 21
        TabOrder = 16
        Text = 'Edit2'
        OnChange = Edit8Change
      end
      object Edit9: TEdit
        Left = 8
        Top = 184
        Width = 97
        Height = 21
        TabOrder = 17
        Text = 'Edit2'
        OnChange = Edit9Change
      end
      object Edit10: TEdit
        Left = 8
        Top = 208
        Width = 97
        Height = 21
        TabOrder = 18
        Text = 'Edit2'
        OnChange = Edit10Change
      end
      object Edit11: TEdit
        Left = 8
        Top = 232
        Width = 97
        Height = 21
        TabOrder = 19
        Text = 'Edit2'
        OnChange = Edit11Change
      end
      object Edit22: TEdit
        Left = 152
        Top = 16
        Width = 113
        Height = 21
        TabOrder = 20
        Text = 'Edit22'
        OnChange = Edit22Change
        OnKeyDown = Edit22KeyDown
      end
      object Edit23: TEdit
        Left = 152
        Top = 40
        Width = 113
        Height = 21
        TabOrder = 21
        Text = 'Edit22'
        OnChange = Edit23Change
        OnKeyDown = Edit23KeyDown
      end
      object Edit24: TEdit
        Left = 152
        Top = 64
        Width = 113
        Height = 21
        TabOrder = 22
        Text = 'Edit22'
        OnChange = Edit24Change
        OnKeyDown = Edit24KeyDown
      end
      object Edit25: TEdit
        Left = 152
        Top = 88
        Width = 113
        Height = 21
        TabOrder = 23
        Text = 'Edit22'
        OnChange = Edit25Change
        OnKeyDown = Edit25KeyDown
      end
      object Edit26: TEdit
        Left = 152
        Top = 112
        Width = 113
        Height = 21
        TabOrder = 24
        Text = 'Edit22'
        OnChange = Edit26Change
        OnKeyDown = Edit26KeyDown
      end
      object Edit27: TEdit
        Left = 152
        Top = 136
        Width = 113
        Height = 21
        TabOrder = 25
        Text = 'Edit22'
        OnChange = Edit27Change
        OnKeyDown = Edit27KeyDown
      end
      object Edit28: TEdit
        Left = 152
        Top = 160
        Width = 113
        Height = 21
        TabOrder = 26
        Text = 'Edit22'
        OnChange = Edit28Change
        OnKeyDown = Edit28KeyDown
      end
      object Edit29: TEdit
        Left = 152
        Top = 184
        Width = 113
        Height = 21
        TabOrder = 27
        Text = 'Edit22'
        OnChange = Edit29Change
        OnKeyDown = Edit29KeyDown
      end
      object Edit30: TEdit
        Left = 152
        Top = 208
        Width = 113
        Height = 21
        TabOrder = 28
        Text = 'Edit22'
        OnChange = Edit30Change
        OnKeyDown = Edit30KeyDown
      end
      object Edit31: TEdit
        Left = 152
        Top = 232
        Width = 113
        Height = 21
        TabOrder = 29
        Text = 'Edit22'
        OnChange = Edit31Change
        OnKeyDown = Edit31KeyDown
      end
    end
    object GroupBox4: TGroupBox
      Left = 16
      Top = 288
      Width = 273
      Height = 257
      Caption = 'Command'
      TabOrder = 1
      object Button18: TButton
        Left = 112
        Top = 16
        Width = 33
        Height = 21
        Caption = '11'
        TabOrder = 0
        OnClick = Button18Click
      end
      object Button19: TButton
        Left = 112
        Top = 40
        Width = 33
        Height = 21
        Caption = '12'
        TabOrder = 1
        OnClick = Button19Click
      end
      object Button20: TButton
        Left = 112
        Top = 64
        Width = 33
        Height = 21
        Caption = '13'
        TabOrder = 2
        OnClick = Button20Click
      end
      object Button21: TButton
        Left = 112
        Top = 88
        Width = 33
        Height = 21
        Caption = '14'
        TabOrder = 3
        OnClick = Button21Click
      end
      object Button22: TButton
        Left = 112
        Top = 112
        Width = 33
        Height = 21
        Caption = '15'
        TabOrder = 4
        OnClick = Button22Click
      end
      object Button23: TButton
        Left = 112
        Top = 136
        Width = 33
        Height = 21
        Caption = '16'
        TabOrder = 5
        OnClick = Button23Click
      end
      object Button24: TButton
        Left = 112
        Top = 160
        Width = 33
        Height = 21
        Caption = '17'
        TabOrder = 6
        OnClick = Button24Click
      end
      object Button25: TButton
        Left = 112
        Top = 184
        Width = 33
        Height = 21
        Caption = '18'
        TabOrder = 7
        OnClick = Button25Click
      end
      object Button26: TButton
        Left = 112
        Top = 208
        Width = 33
        Height = 21
        Caption = '19'
        TabOrder = 8
        OnClick = Button26Click
      end
      object Button27: TButton
        Left = 112
        Top = 232
        Width = 33
        Height = 21
        Caption = '20'
        TabOrder = 9
        OnClick = Button27Click
      end
      object Edit12: TEdit
        Left = 8
        Top = 16
        Width = 97
        Height = 21
        TabOrder = 10
        Text = 'Edit2'
        OnChange = Edit12Change
      end
      object Edit13: TEdit
        Left = 8
        Top = 40
        Width = 97
        Height = 21
        TabOrder = 11
        Text = 'Edit2'
        OnChange = Edit13Change
      end
      object Edit14: TEdit
        Left = 8
        Top = 64
        Width = 97
        Height = 21
        TabOrder = 12
        Text = 'Edit2'
        OnChange = Edit14Change
      end
      object Edit15: TEdit
        Left = 8
        Top = 88
        Width = 97
        Height = 21
        TabOrder = 13
        Text = 'Edit2'
        OnChange = Edit15Change
      end
      object Edit16: TEdit
        Left = 8
        Top = 112
        Width = 97
        Height = 21
        TabOrder = 14
        Text = 'Edit2'
        OnChange = Edit16Change
      end
      object Edit17: TEdit
        Left = 8
        Top = 136
        Width = 97
        Height = 21
        TabOrder = 15
        Text = 'Edit2'
        OnChange = Edit17Change
      end
      object Edit18: TEdit
        Left = 8
        Top = 160
        Width = 97
        Height = 21
        TabOrder = 16
        Text = 'Edit2'
        OnChange = Edit18Change
      end
      object Edit19: TEdit
        Left = 8
        Top = 184
        Width = 97
        Height = 21
        TabOrder = 17
        Text = 'Edit2'
        OnChange = Edit19Change
      end
      object Edit20: TEdit
        Left = 8
        Top = 208
        Width = 97
        Height = 21
        TabOrder = 18
        Text = 'Edit2'
        OnChange = Edit20Change
      end
      object Edit21: TEdit
        Left = 8
        Top = 232
        Width = 97
        Height = 21
        TabOrder = 19
        Text = 'Edit2'
        OnChange = Edit21Change
      end
      object Edit32: TEdit
        Left = 152
        Top = 16
        Width = 113
        Height = 21
        TabOrder = 20
        Text = 'Edit22'
        OnChange = Edit32Change
        OnKeyDown = Edit32KeyDown
      end
      object Edit33: TEdit
        Left = 152
        Top = 40
        Width = 113
        Height = 21
        TabOrder = 21
        Text = 'Edit22'
        OnChange = Edit33Change
        OnKeyDown = Edit33KeyDown
      end
      object Edit34: TEdit
        Left = 152
        Top = 64
        Width = 113
        Height = 21
        TabOrder = 22
        Text = 'Edit22'
        OnChange = Edit34Change
        OnKeyDown = Edit34KeyDown
      end
      object Edit35: TEdit
        Left = 152
        Top = 88
        Width = 113
        Height = 21
        TabOrder = 23
        Text = 'Edit22'
        OnChange = Edit35Change
        OnKeyDown = Edit35KeyDown
      end
      object Edit36: TEdit
        Left = 152
        Top = 112
        Width = 113
        Height = 21
        TabOrder = 24
        Text = 'Edit22'
        OnChange = Edit36Change
        OnKeyDown = Edit36KeyDown
      end
      object Edit37: TEdit
        Left = 152
        Top = 136
        Width = 113
        Height = 21
        TabOrder = 25
        Text = 'Edit22'
        OnChange = Edit37Change
        OnKeyDown = Edit37KeyDown
      end
      object Edit38: TEdit
        Left = 152
        Top = 160
        Width = 113
        Height = 21
        TabOrder = 26
        Text = 'Edit22'
        OnChange = Edit38Change
        OnKeyDown = Edit38KeyDown
      end
      object Edit39: TEdit
        Left = 152
        Top = 184
        Width = 113
        Height = 21
        TabOrder = 27
        Text = 'Edit22'
        OnChange = Edit39Change
        OnKeyDown = Edit39KeyDown
      end
      object Edit40: TEdit
        Left = 152
        Top = 208
        Width = 113
        Height = 21
        TabOrder = 28
        Text = 'Edit22'
        OnChange = Edit40Change
        OnKeyDown = Edit40KeyDown
      end
      object Edit41: TEdit
        Left = 152
        Top = 232
        Width = 113
        Height = 21
        TabOrder = 29
        Text = 'Edit22'
        OnChange = Edit41Change
        OnKeyDown = Edit41KeyDown
      end
    end
  end
end
