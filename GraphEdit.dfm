object f_GraphEdit: Tf_GraphEdit
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'Edit'
  ClientHeight = 397
  ClientWidth = 289
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  DesignSize = (
    289
    397)
  PixelsPerInch = 96
  TextHeight = 13
  object l_lIntid: TLabel
    Left = 8
    Top = 8
    Width = 53
    Height = 13
    Caption = 'InternalID:'
  end
  object l_InternalID: TLabel
    Left = 88
    Top = 8
    Width = 3
    Height = 13
    Anchors = [akLeft, akTop, akRight]
  end
  object l_lposx: TLabel
    Left = 8
    Top = 72
    Width = 30
    Height = 13
    Caption = 'Pos X:'
  end
  object l_lposy: TLabel
    Left = 8
    Top = 104
    Width = 30
    Height = 13
    Caption = 'Pos Y:'
  end
  object l_lname: TLabel
    Left = 8
    Top = 40
    Width = 31
    Height = 13
    Caption = 'Name:'
  end
  object l_lNameUp: TLabel
    Left = 8
    Top = 168
    Width = 74
    Height = 13
    Caption = 'Name Output1:'
  end
  object l_lNameDown: TLabel
    Left = 8
    Top = 200
    Width = 74
    Height = 13
    Caption = 'Name OutPut2:'
  end
  object l_lType: TLabel
    Left = 8
    Top = 137
    Width = 28
    Height = 13
    Caption = 'Type:'
  end
  object l_pinidinup: TLabel
    Left = 8
    Top = 233
    Width = 67
    Height = 13
    Caption = 'Pin ID Input1:'
  end
  object l_lpinidindown: TLabel
    Left = 8
    Top = 264
    Width = 67
    Height = 13
    Caption = 'Pin ID Input2:'
  end
  object l_lpinidoutup: TLabel
    Left = 8
    Top = 295
    Width = 75
    Height = 13
    Caption = 'Pin ID Output1:'
  end
  object l_lpinidoutdown: TLabel
    Left = 8
    Top = 327
    Width = 75
    Height = 13
    Caption = 'Pin ID Output2:'
  end
  object l_SaveName: TLabel
    Left = 88
    Top = 25
    Width = 3
    Height = 13
    Visible = False
  end
  object l_NameOutUp: TLabel
    Left = 104
    Top = 153
    Width = 3
    Height = 13
    Visible = False
  end
  object l_NameOutDown: TLabel
    Left = 104
    Top = 185
    Width = 3
    Height = 13
    Transparent = False
    Visible = False
  end
  object e_PosX: TEdit
    Left = 88
    Top = 69
    Width = 192
    Height = 21
    Anchors = [akLeft, akTop, akRight]
    TabOrder = 1
    OnKeyPress = e_NameOutUpKeyPress
  end
  object e_PosY: TEdit
    Left = 89
    Top = 101
    Width = 192
    Height = 21
    Anchors = [akLeft, akTop, akRight]
    TabOrder = 2
    OnKeyPress = e_NameOutUpKeyPress
  end
  object e_Name: TEdit
    Left = 88
    Top = 37
    Width = 192
    Height = 21
    Anchors = [akLeft, akTop, akRight]
    TabOrder = 0
    OnKeyPress = e_NameOutUpKeyPress
  end
  object e_NameOutUp: TEdit
    Left = 88
    Top = 165
    Width = 192
    Height = 21
    Anchors = [akLeft, akTop, akRight]
    TabOrder = 4
    OnKeyPress = e_NameOutUpKeyPress
  end
  object e_NameOutDown: TEdit
    Left = 88
    Top = 197
    Width = 192
    Height = 21
    Anchors = [akLeft, akTop, akRight]
    TabOrder = 5
    OnKeyPress = e_NameOutUpKeyPress
  end
  object cb_Type: TComboBox
    Left = 89
    Top = 133
    Width = 192
    Height = 21
    Anchors = [akLeft, akTop, akRight]
    TabOrder = 3
    OnKeyPress = e_NameOutUpKeyPress
    Items.Strings = (
      'OR'
      'AND'
      'NOR'
      'NAND'
      'XOR'
      'NOT')
  end
  object e_PinIDInUp: TEdit
    Left = 88
    Top = 230
    Width = 192
    Height = 21
    Anchors = [akLeft, akTop, akRight]
    TabOrder = 6
    OnKeyPress = e_NameOutUpKeyPress
  end
  object e_PinIDInDown: TEdit
    Left = 88
    Top = 261
    Width = 192
    Height = 21
    Anchors = [akLeft, akTop, akRight]
    TabOrder = 7
    OnKeyPress = e_NameOutUpKeyPress
  end
  object e_PinIDOutUp: TEdit
    Left = 88
    Top = 292
    Width = 192
    Height = 21
    Anchors = [akLeft, akTop, akRight]
    TabOrder = 8
    OnKeyPress = e_NameOutUpKeyPress
  end
  object e_PinIDOutDown: TEdit
    Left = 88
    Top = 324
    Width = 192
    Height = 21
    Anchors = [akLeft, akTop, akRight]
    TabOrder = 9
    OnKeyPress = e_NameOutUpKeyPress
  end
  object b_Update: TButton
    Left = 42
    Top = 360
    Width = 75
    Height = 25
    Hint = 'Shortcut: Enter'
    Anchors = [akLeft, akBottom]
    Caption = 'Update'
    TabOrder = 10
    OnClick = b_UpdateClick
  end
  object b_delete: TButton
    Left = 168
    Top = 360
    Width = 75
    Height = 25
    Hint = 'Shortcut: Delete'
    Anchors = [akRight, akBottom]
    Caption = 'Delete'
    TabOrder = 11
    OnClick = b_deleteClick
  end
  object cb_Delete: TCheckBox
    Left = 205
    Top = 8
    Width = 65
    Height = 17
    Caption = 'Deleted'
    TabOrder = 12
    Visible = False
  end
end
