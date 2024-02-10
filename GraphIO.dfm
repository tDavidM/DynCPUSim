object f_GraphIO: Tf_GraphIO
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'Input/Output'
  ClientHeight = 241
  ClientWidth = 980
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Visible = True
  OnCloseQuery = FormCloseQuery
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object p_MemInput: TPanel
    Left = 601
    Top = 2
    Width = 377
    Height = 237
    TabOrder = 2
    object l_MemInput: TLabel
      Left = 7
      Top = 6
      Width = 67
      Height = 13
      Caption = 'RAM I/O Pins:'
    end
    object l_MemOutput: TLabel
      Left = 107
      Top = 80
      Width = 99
      Height = 13
      Caption = 'RAM Data Line (Out)'
    end
    object l_memflag: TLabel
      Left = 107
      Top = 26
      Width = 99
      Height = 13
      Caption = 'RAM Addr Line (Out)'
    end
    object Label2: TLabel
      Left = 107
      Top = 134
      Width = 91
      Height = 13
      Caption = 'RAM Data Line (In)'
    end
    object l_Line3: TLabel
      Left = 233
      Top = 26
      Width = 38
      Height = 13
      Caption = '[0x00]'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object l_Line4: TLabel
      Left = 233
      Top = 80
      Width = 38
      Height = 13
      Caption = '[0x00]'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object l_Line5: TLabel
      Left = 233
      Top = 134
      Width = 38
      Height = 13
      Caption = '[0x00]'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label3: TLabel
      Left = 106
      Top = 185
      Width = 100
      Height = 13
      Caption = 'RAM Page Line (Out)'
    end
    object l_Line6: TLabel
      Left = 233
      Top = 185
      Width = 38
      Height = 13
      Caption = '[0x00]'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Pin41: TCheckBox
      Left = 19
      Top = 153
      Width = 34
      Height = 17
      Caption = '41'
      TabOrder = 16
      OnClick = Line5Click
    end
    object Pin42: TCheckBox
      Left = 63
      Top = 153
      Width = 34
      Height = 17
      Caption = '42'
      TabOrder = 17
      OnClick = Line5Click
    end
    object Pin43: TCheckBox
      Left = 107
      Top = 153
      Width = 34
      Height = 17
      Caption = '43'
      TabOrder = 18
      OnClick = Line5Click
    end
    object Pin44: TCheckBox
      Left = 151
      Top = 153
      Width = 34
      Height = 17
      Caption = '44'
      TabOrder = 19
      OnClick = Line5Click
    end
    object Pin45: TCheckBox
      Left = 195
      Top = 153
      Width = 34
      Height = 17
      Caption = '45'
      TabOrder = 20
      OnClick = Line5Click
    end
    object Pin46: TCheckBox
      Left = 239
      Top = 153
      Width = 34
      Height = 17
      Caption = '46'
      TabOrder = 21
      OnClick = Line5Click
    end
    object Pin47: TCheckBox
      Left = 283
      Top = 153
      Width = 34
      Height = 17
      Caption = '47'
      TabOrder = 22
      OnClick = Line5Click
    end
    object Pin48: TCheckBox
      Left = 327
      Top = 153
      Width = 34
      Height = 17
      Caption = '48'
      TabOrder = 23
      OnClick = Line5Click
    end
    object Pin21: TCheckBox
      Left = 19
      Top = 45
      Width = 34
      Height = 17
      Caption = '21'
      TabOrder = 0
      OnClick = Line3Click
    end
    object Pin31: TCheckBox
      Left = 19
      Top = 99
      Width = 34
      Height = 17
      Caption = '31'
      TabOrder = 8
      OnClick = Line4Click
    end
    object Pin32: TCheckBox
      Left = 63
      Top = 99
      Width = 34
      Height = 17
      Caption = '32'
      TabOrder = 9
      OnClick = Line4Click
    end
    object Pin22: TCheckBox
      Left = 63
      Top = 45
      Width = 34
      Height = 17
      Caption = '22'
      TabOrder = 1
      OnClick = Line3Click
    end
    object Pin23: TCheckBox
      Left = 107
      Top = 45
      Width = 34
      Height = 17
      Caption = '23'
      TabOrder = 2
      OnClick = Line3Click
    end
    object Pin33: TCheckBox
      Left = 107
      Top = 99
      Width = 34
      Height = 17
      Caption = '33'
      TabOrder = 10
      OnClick = Line4Click
    end
    object Pin34: TCheckBox
      Left = 151
      Top = 99
      Width = 34
      Height = 17
      Caption = '34'
      TabOrder = 11
      OnClick = Line4Click
    end
    object Pin24: TCheckBox
      Left = 151
      Top = 45
      Width = 34
      Height = 17
      Caption = '24'
      TabOrder = 3
      OnClick = Line3Click
    end
    object Pin25: TCheckBox
      Left = 195
      Top = 45
      Width = 34
      Height = 17
      Caption = '25'
      TabOrder = 4
      OnClick = Line3Click
    end
    object Pin35: TCheckBox
      Left = 195
      Top = 99
      Width = 34
      Height = 17
      Caption = '35'
      TabOrder = 12
      OnClick = Line4Click
    end
    object Pin36: TCheckBox
      Left = 239
      Top = 99
      Width = 34
      Height = 17
      Caption = '36'
      TabOrder = 13
      OnClick = Line4Click
    end
    object Pin26: TCheckBox
      Left = 239
      Top = 45
      Width = 34
      Height = 17
      Caption = '26'
      TabOrder = 5
      OnClick = Line3Click
    end
    object Pin27: TCheckBox
      Left = 283
      Top = 45
      Width = 34
      Height = 17
      Caption = '27'
      TabOrder = 6
      OnClick = Line3Click
    end
    object Pin37: TCheckBox
      Left = 283
      Top = 99
      Width = 34
      Height = 17
      Caption = '37'
      TabOrder = 14
      OnClick = Line4Click
    end
    object Pin38: TCheckBox
      Left = 327
      Top = 99
      Width = 34
      Height = 17
      Caption = '38'
      TabOrder = 15
      OnClick = Line4Click
    end
    object Pin28: TCheckBox
      Left = 327
      Top = 45
      Width = 34
      Height = 17
      Caption = '28'
      TabOrder = 7
      OnClick = Line3Click
    end
    object Pin61: TCheckBox
      Left = 19
      Top = 204
      Width = 33
      Height = 17
      Caption = '61'
      TabOrder = 24
      OnClick = Line6Click
    end
    object Pin62: TCheckBox
      Left = 63
      Top = 204
      Width = 33
      Height = 17
      Caption = '62'
      TabOrder = 25
      OnClick = Line6Click
    end
    object Pin63: TCheckBox
      Left = 107
      Top = 204
      Width = 33
      Height = 17
      Caption = '63'
      TabOrder = 26
      OnClick = Line6Click
    end
    object Pin64: TCheckBox
      Left = 151
      Top = 204
      Width = 33
      Height = 17
      Caption = '64'
      TabOrder = 27
      OnClick = Line6Click
    end
    object Pin65: TCheckBox
      Left = 195
      Top = 204
      Width = 33
      Height = 17
      Caption = '65'
      TabOrder = 28
      OnClick = Line6Click
    end
    object Pin66: TCheckBox
      Left = 239
      Top = 204
      Width = 33
      Height = 17
      Caption = '66'
      TabOrder = 29
      OnClick = Line6Click
    end
    object Pin67: TCheckBox
      Left = 283
      Top = 204
      Width = 33
      Height = 17
      Caption = '67'
      TabOrder = 30
      OnClick = Line6Click
    end
    object Pin68: TCheckBox
      Left = 327
      Top = 204
      Width = 33
      Height = 17
      Caption = '68'
      TabOrder = 31
      OnClick = Line6Click
    end
  end
  object p_ROM: TPanel
    Left = 2
    Top = 77
    Width = 593
    Height = 162
    TabOrder = 1
    object l_rom: TLabel
      Left = 7
      Top = 6
      Width = 160
      Height = 13
      Caption = 'ROM I/O Pins (Program Memory):'
    end
    object l_Romdata: TLabel
      Left = 107
      Top = 29
      Width = 92
      Height = 13
      Caption = 'ROM Data Line (In)'
    end
    object Label1: TLabel
      Left = 419
      Top = 81
      Width = 100
      Height = 13
      Caption = 'ROM Addr Line (Out)'
    end
    object l_Line1: TLabel
      Left = 233
      Top = 29
      Width = 52
      Height = 13
      Caption = '[0x0000]'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object l_Line2: TLabel
      Left = 534
      Top = 81
      Width = 38
      Height = 13
      Caption = '[0x00]'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label4: TLabel
      Left = 107
      Top = 113
      Width = 101
      Height = 13
      Caption = 'ROM Page Line (Out)'
    end
    object Label5: TLabel
      Left = 233
      Top = 113
      Width = 38
      Height = 13
      Caption = '[0x00]'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Pin1: TCheckBox
      Left = 19
      Top = 48
      Width = 33
      Height = 17
      Caption = '1'
      TabOrder = 0
      OnClick = Line1Click
    end
    object Pin2: TCheckBox
      Left = 63
      Top = 48
      Width = 33
      Height = 17
      Caption = '2'
      TabOrder = 1
      OnClick = Line1Click
    end
    object Pin3: TCheckBox
      Left = 107
      Top = 48
      Width = 33
      Height = 17
      Caption = '3'
      TabOrder = 2
      OnClick = Line1Click
    end
    object Pin4: TCheckBox
      Left = 151
      Top = 48
      Width = 33
      Height = 17
      Caption = '4'
      TabOrder = 3
      OnClick = Line1Click
    end
    object Pin8: TCheckBox
      Left = 327
      Top = 48
      Width = 33
      Height = 17
      Caption = '8'
      TabOrder = 7
      OnClick = Line1Click
    end
    object Pin7: TCheckBox
      Left = 283
      Top = 48
      Width = 33
      Height = 17
      Caption = '7'
      TabOrder = 6
      OnClick = Line1Click
    end
    object Pin6: TCheckBox
      Left = 239
      Top = 48
      Width = 33
      Height = 17
      Caption = '6'
      TabOrder = 5
      OnClick = Line1Click
    end
    object Pin5: TCheckBox
      Left = 195
      Top = 48
      Width = 32
      Height = 17
      Caption = '5'
      TabOrder = 4
      OnClick = Line1Click
    end
    object Pin16: TCheckBox
      Left = 327
      Top = 80
      Width = 33
      Height = 17
      Caption = '16'
      TabOrder = 15
      OnClick = Line1Click
    end
    object Pin15: TCheckBox
      Left = 283
      Top = 80
      Width = 33
      Height = 17
      Caption = '15'
      TabOrder = 14
      OnClick = Line1Click
    end
    object Pin14: TCheckBox
      Left = 239
      Top = 80
      Width = 33
      Height = 17
      Caption = '14'
      TabOrder = 13
      OnClick = Line1Click
    end
    object Pin13: TCheckBox
      Left = 195
      Top = 80
      Width = 32
      Height = 17
      Caption = '13'
      TabOrder = 12
      OnClick = Line1Click
    end
    object Pin12: TCheckBox
      Left = 151
      Top = 80
      Width = 33
      Height = 17
      Caption = '12'
      TabOrder = 11
      OnClick = Line1Click
    end
    object Pin11: TCheckBox
      Left = 107
      Top = 80
      Width = 33
      Height = 17
      Caption = '11'
      TabOrder = 10
      OnClick = Line1Click
    end
    object Pin10: TCheckBox
      Left = 63
      Top = 80
      Width = 33
      Height = 17
      Caption = '10'
      TabOrder = 9
      OnClick = Line1Click
    end
    object Pin9: TCheckBox
      Left = 19
      Top = 80
      Width = 33
      Height = 17
      Caption = '9'
      TabOrder = 8
      OnClick = Line1Click
    end
    object Pin52: TCheckBox
      Left = 463
      Top = 100
      Width = 33
      Height = 17
      Caption = '52'
      TabOrder = 17
      OnClick = Line2Click
    end
    object Pin51: TCheckBox
      Left = 419
      Top = 100
      Width = 32
      Height = 17
      Caption = '51'
      TabOrder = 16
      OnClick = Line2Click
    end
    object Pin53: TCheckBox
      Left = 507
      Top = 100
      Width = 33
      Height = 17
      Caption = '53'
      TabOrder = 18
      OnClick = Line2Click
    end
    object Pin54: TCheckBox
      Left = 548
      Top = 100
      Width = 33
      Height = 17
      Caption = '54'
      TabOrder = 19
      OnClick = Line2Click
    end
    object Pin55: TCheckBox
      Left = 419
      Top = 132
      Width = 32
      Height = 17
      Caption = '55'
      TabOrder = 20
      OnClick = Line2Click
    end
    object Pin56: TCheckBox
      Left = 463
      Top = 132
      Width = 33
      Height = 17
      Caption = '56'
      TabOrder = 21
      OnClick = Line2Click
    end
    object Pin57: TCheckBox
      Left = 507
      Top = 132
      Width = 33
      Height = 17
      Caption = '57'
      TabOrder = 22
      OnClick = Line2Click
    end
    object Pin58: TCheckBox
      Left = 548
      Top = 132
      Width = 33
      Height = 17
      Caption = '58'
      TabOrder = 23
      OnClick = Line2Click
    end
    object Pin71: TCheckBox
      Left = 19
      Top = 132
      Width = 33
      Height = 17
      Caption = '71'
      TabOrder = 24
      OnClick = Line1Click
    end
    object Pin72: TCheckBox
      Left = 63
      Top = 132
      Width = 33
      Height = 17
      Caption = '72'
      TabOrder = 25
      OnClick = Line1Click
    end
    object Pin73: TCheckBox
      Left = 107
      Top = 132
      Width = 33
      Height = 17
      Caption = '73'
      TabOrder = 26
      OnClick = Line1Click
    end
    object Pin74: TCheckBox
      Left = 151
      Top = 132
      Width = 33
      Height = 17
      Caption = '74'
      TabOrder = 27
      OnClick = Line1Click
    end
    object Pin75: TCheckBox
      Left = 195
      Top = 132
      Width = 32
      Height = 17
      Caption = '75'
      TabOrder = 28
      OnClick = Line1Click
    end
    object Pin76: TCheckBox
      Left = 239
      Top = 132
      Width = 33
      Height = 17
      Caption = '76'
      TabOrder = 29
      OnClick = Line1Click
    end
    object Pin77: TCheckBox
      Left = 283
      Top = 132
      Width = 33
      Height = 17
      Caption = '77'
      TabOrder = 30
      OnClick = Line1Click
    end
    object Pin78: TCheckBox
      Left = 327
      Top = 132
      Width = 33
      Height = 17
      Caption = '78'
      TabOrder = 31
      OnClick = Line1Click
    end
  end
  object p_Misc: TPanel
    Left = 2
    Top = 2
    Width = 593
    Height = 69
    TabOrder = 0
    object l_misc: TLabel
      Left = 7
      Top = 6
      Width = 65
      Height = 13
      Caption = 'Misc I/O Pins:'
    end
    object Pin50: TCheckBox
      Left = 434
      Top = 14
      Width = 138
      Height = 17
      Caption = '50 (ROM Relative Out)'
      TabOrder = 0
      OnClick = Pin50Click
    end
    object Pin29: TCheckBox
      Left = 115
      Top = 14
      Width = 126
      Height = 17
      Caption = '29 (Debug Halt Out)'
      TabOrder = 1
      OnClick = Pin29Click
    end
    object Pin30: TCheckBox
      Left = 271
      Top = 14
      Width = 112
      Height = 17
      Caption = '30 (RAM Write Out)'
      TabOrder = 3
      OnClick = Pin30Click
    end
    object Pin39: TCheckBox
      Left = 115
      Top = 39
      Width = 126
      Height = 17
      Caption = '39 (Debug Halt In)'
      TabOrder = 2
      OnClick = Pin39Click
    end
    object Pin40: TCheckBox
      Left = 271
      Top = 39
      Width = 116
      Height = 17
      Caption = '40 (RAM Read Out)'
      TabOrder = 4
      OnClick = Pin40Click
    end
    object Pin70: TCheckBox
      Left = 19
      Top = 30
      Width = 86
      Height = 17
      Caption = '70 (Boot In)'
      Checked = True
      State = cbChecked
      TabOrder = 5
      OnClick = Pin70Click
    end
    object Pin60: TCheckBox
      Left = 434
      Top = 39
      Width = 138
      Height = 17
      Caption = '60 (ROM Absolute Out)'
      TabOrder = 6
      OnClick = Pin60Click
    end
  end
  object p_Unused: TPanel
    Left = 399
    Top = 77
    Width = 196
    Height = 73
    TabOrder = 3
    object Label6: TLabel
      Left = 78
      Top = 6
      Width = 44
      Height = 13
      Caption = '(Unused)'
    end
    object Pin17: TCheckBox
      Left = 19
      Top = 22
      Width = 34
      Height = 17
      Caption = '17'
      TabOrder = 0
      OnClick = Line2Click
    end
    object Pin49: TCheckBox
      Left = 19
      Top = 45
      Width = 37
      Height = 17
      Caption = '49'
      TabOrder = 1
      OnClick = Pin70Click
    end
    object Pin18: TCheckBox
      Left = 63
      Top = 22
      Width = 35
      Height = 17
      Caption = '18'
      TabOrder = 2
      OnClick = Line2Click
    end
    object Pin59: TCheckBox
      Left = 63
      Top = 45
      Width = 41
      Height = 17
      Caption = '59'
      TabOrder = 3
      OnClick = Pin70Click
    end
    object Pin19: TCheckBox
      Left = 107
      Top = 22
      Width = 35
      Height = 17
      Caption = '19'
      TabOrder = 4
      OnClick = Line2Click
    end
    object Pin69: TCheckBox
      Left = 107
      Top = 45
      Width = 35
      Height = 17
      Caption = '69'
      TabOrder = 5
      OnClick = Pin70Click
    end
    object Pin20: TCheckBox
      Left = 148
      Top = 22
      Width = 35
      Height = 17
      Caption = '20'
      TabOrder = 6
      OnClick = Line2Click
    end
    object Pin79: TCheckBox
      Left = 148
      Top = 45
      Width = 40
      Height = 17
      Caption = '79'
      TabOrder = 7
      OnClick = Pin70Click
    end
  end
end
