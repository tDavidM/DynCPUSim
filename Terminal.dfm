object f_Terminal: Tf_Terminal
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'Terminal'
  ClientHeight = 540
  ClientWidth = 603
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Visible = True
  OnPaint = FormPaint
  PixelsPerInch = 96
  TextHeight = 13
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
  object tRefresh: TTimer
    OnTimer = tRefreshTimer
    Left = 24
    Top = 24
  end
end
