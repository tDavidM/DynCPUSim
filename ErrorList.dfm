object f_ErrorList: Tf_ErrorList
  Left = 0
  Top = 0
  BorderIcons = []
  Caption = 'Error List'
  ClientHeight = 400
  ClientWidth = 500
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poOwnerFormCenter
  DesignSize = (
    500
    400)
  PixelsPerInch = 96
  TextHeight = 13
  object bOk: TButton
    Left = 210
    Top = 365
    Width = 80
    Height = 25
    Anchors = [akLeft, akBottom]
    Caption = 'OK'
    ModalResult = 1
    TabOrder = 0
  end
  object mLog: TMemo
    Left = 8
    Top = 8
    Width = 484
    Height = 345
    Anchors = [akLeft, akTop, akRight, akBottom]
    HideSelection = False
    ReadOnly = True
    ScrollBars = ssVertical
    TabOrder = 1
  end
end
