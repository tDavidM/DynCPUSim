object f_Terminal: Tf_Terminal
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'Terminal'
  ClientHeight = 439
  ClientWidth = 603
  Color = clBtnFace
  DoubleBuffered = True
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  Visible = True
  OnCreate = FormCreate
  OnKeyPress = FormKeyPress
  OnPaint = FormPaint
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object sbBoot: TSpeedButton
    Left = 8
    Top = 407
    Width = 75
    Height = 25
    AllowAllUp = True
    GroupIndex = 1
    Caption = 'Boot'
    OnClick = sbBootClick
  end
  object sbHalt: TSpeedButton
    Left = 89
    Top = 407
    Width = 75
    Height = 25
    AllowAllUp = True
    GroupIndex = 2
    Caption = 'Halt'
    OnClick = sbHaltClick
  end
  object lValue: TLabel
    Left = 279
    Top = 413
    Width = 44
    Height = 13
    Caption = '0x00 ( )'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object lTimer: TLabel
    Left = 175
    Top = 413
    Width = 23
    Height = 13
    Caption = '( 0 )'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object pScreen: TPanel
    Left = 8
    Top = 8
    Width = 593
    Height = 393
    Color = clBlack
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clLime
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentBackground = False
    ParentFont = False
    TabOrder = 0
    Visible = False
  end
  object pBusy: TPanel
    Left = 519
    Top = 407
    Width = 75
    Height = 25
    Caption = 'Busy'
    Color = clGray
    DoubleBuffered = False
    ParentBackground = False
    ParentDoubleBuffered = False
    TabOrder = 1
  end
  object pInterrupt: TPanel
    Left = 353
    Top = 407
    Width = 75
    Height = 25
    Caption = 'Interrupt'
    Color = clGray
    DoubleBuffered = False
    ParentBackground = False
    ParentDoubleBuffered = False
    TabOrder = 2
  end
  object pDebug: TPanel
    Left = 436
    Top = 407
    Width = 75
    Height = 25
    Caption = 'Debug'
    Color = clGray
    DoubleBuffered = False
    ParentBackground = False
    ParentDoubleBuffered = False
    TabOrder = 3
    OnClick = pDebugClick
  end
  object tRefresh: TTimer
    Enabled = False
    OnTimer = tRefreshTimer
    Left = 24
    Top = 24
  end
end
