object f_CPUNode: Tf_CPUNode
  Left = 0
  Top = 0
  Caption = 'Dynamic CPU Simulation'
  ClientHeight = 615
  ClientWidth = 1071
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  OnCloseQuery = FormCloseQuery
  OnCreate = FormCreate
  OnKeyDown = FormKeyDown
  OnMouseDown = FormMouseDown
  OnMouseMove = FormMouseMove
  OnMouseWheel = FormMouseWheel
  OnPaint = FormPaint
  DesignSize = (
    1071
    615)
  PixelsPerInch = 96
  TextHeight = 13
  object p_Area: TPanel
    Left = 8
    Top = 47
    Width = 1055
    Height = 543
    Anchors = [akLeft, akTop, akRight, akBottom]
    TabOrder = 1
    Visible = False
  end
  object p_zoom: TPanel
    Left = 1031
    Top = 396
    Width = 40
    Height = 199
    Anchors = [akRight, akBottom]
    ParentBackground = False
    TabOrder = 0
    object l_gridZoom: TLabel
      Left = 5
      Top = 6
      Width = 30
      Height = 13
      Caption = 'Zoom:'
    end
    object tb_Size: TTrackBar
      Left = 3
      Top = 19
      Width = 33
      Height = 178
      Hint = 'Shortcut: MouseWheel'
      Max = 9
      Orientation = trVertical
      Position = 3
      TabOrder = 0
      TickMarks = tmTopLeft
      OnChange = tb_SizeChange
    end
  end
  object sb_Main: TStatusBar
    Left = 0
    Top = 596
    Width = 1071
    Height = 19
    Panels = <
      item
        Width = 1250
      end>
    SimpleText = 
      #9#9#9#9#9#9#9#9'Mouse: Left=Select, Right=Move, Middle=Create, Shift+Lef' +
      't=Link(1), Ctrl+Left=Link(2)'
  end
  object HeaderControl1: THeaderControl
    Left = 0
    Top = 0
    Width = 1071
    Height = 21
    Sections = <>
  end
  object b_Or: TButton
    Left = 807
    Top = 0
    Width = 38
    Height = 21
    Hint = 'Shortcut: 1 (Quick Edit: O)'
    Anchors = [akTop, akRight]
    Caption = 'OR'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 4
    OnClick = b_OrClick
  end
  object b_And: TButton
    Tag = 1
    Left = 851
    Top = 0
    Width = 38
    Height = 21
    Hint = 'Shortcut: 2 (Quick Edit: A)'
    Anchors = [akTop, akRight]
    Caption = 'AND'
    TabOrder = 5
    OnClick = b_OrClick
  end
  object b_NOr: TButton
    Tag = 2
    Left = 895
    Top = 0
    Width = 38
    Height = 21
    Hint = 'Shortcut: 3 (Quick Edit: R)'
    Anchors = [akTop, akRight]
    Caption = 'NOR'
    TabOrder = 6
    OnClick = b_OrClick
  end
  object b_NAnd: TButton
    Tag = 3
    Left = 939
    Top = 0
    Width = 38
    Height = 21
    Hint = 'Shortcut: 4 (Quick Edit: D)'
    Anchors = [akTop, akRight]
    Caption = 'NAND'
    TabOrder = 7
    OnClick = b_OrClick
  end
  object b_XOr: TButton
    Tag = 4
    Left = 983
    Top = 0
    Width = 38
    Height = 21
    Hint = 'Shortcut: 5 (Quick Edit: X)'
    Anchors = [akTop, akRight]
    Caption = 'XOR'
    TabOrder = 8
    OnClick = b_OrClick
  end
  object b_Not: TButton
    Tag = 5
    Left = 1027
    Top = 0
    Width = 38
    Height = 21
    Hint = 'Shortcut: 6 (Quick Edit: N)'
    Anchors = [akTop, akRight]
    Caption = 'NOT'
    TabOrder = 9
    OnClick = b_OrClick
  end
  object p_DrawCmp: TPanel
    Left = 570
    Top = 1
    Width = 145
    Height = 18
    Caption = 'Draw: 0 - 0'
    ParentBackground = False
    TabOrder = 10
  end
  object b_Init: TButton
    Left = 8
    Top = 0
    Width = 59
    Height = 21
    Caption = 'Init'
    TabOrder = 11
    OnClick = b_InitClick
  end
  object b_Start: TButton
    Left = 81
    Top = 0
    Width = 59
    Height = 21
    Caption = 'Start'
    TabOrder = 12
    OnClick = b_StartClick
  end
  object b_Step: TButton
    Left = 153
    Top = 0
    Width = 59
    Height = 21
    Caption = 'Step'
    TabOrder = 13
    OnClick = b_StepClick
  end
  object b_Save: TButton
    Left = 497
    Top = 0
    Width = 59
    Height = 21
    Caption = 'Save'
    TabOrder = 14
    OnClick = b_SaveClick
  end
  object b_Reset: TButton
    Left = 225
    Top = 0
    Width = 59
    Height = 21
    Caption = 'Reset'
    TabOrder = 15
    OnClick = b_ResetClick
  end
  object cb_ActiveDraw: TCheckBox
    Left = 298
    Top = 2
    Width = 80
    Height = 17
    Caption = 'Active Draw'
    Checked = True
    State = cbChecked
    TabOrder = 16
  end
  object cb_QuickEdit: TCheckBox
    Left = 728
    Top = 2
    Width = 73
    Height = 17
    Caption = 'Quick Edit'
    TabOrder = 17
  end
  object cb_ColorLine: TCheckBox
    Left = 384
    Top = 2
    Width = 89
    Height = 17
    Caption = 'Color Line (10)'
    TabOrder = 18
    OnClick = cb_ColorLineClick
  end
  object Panel1: TPanel
    Left = 1031
    Top = 27
    Width = 40
    Height = 246
    Anchors = [akTop, akRight]
    ParentBackground = False
    TabOrder = 19
    object l_Speed: TLabel
      Left = 4
      Top = 6
      Width = 34
      Height = 13
      Caption = 'Speed:'
    end
    object tb_Speed: TTrackBar
      Left = 4
      Top = 19
      Width = 33
      Height = 226
      Hint = 'Shortcut: MouseWheel'
      Max = 28
      Min = 1
      Orientation = trVertical
      Position = 15
      TabOrder = 0
      TickMarks = tmTopLeft
      OnChange = tb_SpeedChange
    end
  end
  object pgLoading: TProgressBar
    Left = 857
    Top = 598
    Width = 198
    Height = 16
    Anchors = [akRight, akBottom]
    TabOrder = 20
  end
  object t_Work: TTimer
    Enabled = False
    OnTimer = t_WorkTimer
    Left = 16
    Top = 56
  end
  object XPManifest: TXPManifest
    Left = 48
    Top = 56
  end
  object t_Draw: TTimer
    Enabled = False
    OnTimer = t_DrawTimer
    Left = 16
    Top = 88
  end
  object t_DrawMulti1: TTimer
    Enabled = False
    OnTimer = t_DrawMulti1Timer
    Left = 48
    Top = 88
  end
  object t_DrawMulti2: TTimer
    Enabled = False
    OnTimer = t_DrawMulti2Timer
    Left = 80
    Top = 88
  end
  object t_DrawMulti3: TTimer
    Enabled = False
    OnTimer = t_DrawMulti3Timer
    Left = 112
    Top = 88
  end
  object NodeSaveDialog: TSaveDialog
    DefaultExt = '.ndl'
    Filter = 'CPU Sim File|*.ndl'
    Options = [ofHideReadOnly, ofPathMustExist, ofEnableSizing]
    Left = 352
    Top = 88
  end
  object NodeOpenDialog: TOpenDialog
    DefaultExt = '.ndl'
    Filter = 'CPU Sim File|*.ndl'
    Options = [ofHideReadOnly, ofPathMustExist, ofFileMustExist, ofEnableSizing]
    Left = 272
    Top = 88
  end
  object XMLDoc: TXMLDocument
    NodeIndentStr = '   '
    Options = [doNodeAutoCreate, doNodeAutoIndent, doAttrNull, doAutoPrefix, doNamespaceDecl]
    Left = 312
    Top = 56
    DOMVendorDesc = 'MSXML'
  end
end
