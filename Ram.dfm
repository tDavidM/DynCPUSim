object f_Ram: Tf_Ram
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'RAM'
  ClientHeight = 671
  ClientWidth = 814
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
  DesignSize = (
    814
    671)
  PixelsPerInch = 96
  TextHeight = 13
  object l_Page: TLabel
    Left = 600
    Top = 9
    Width = 69
    Height = 13
    Caption = 'Memory Page:'
  end
  object sg_Ram: TStringGrid
    Left = 8
    Top = 33
    Width = 798
    Height = 630
    Anchors = [akLeft, akTop, akRight, akBottom]
    ColCount = 9
    DefaultColWidth = 96
    DefaultRowHeight = 18
    RowCount = 33
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goDrawFocusSelected, goEditing, goAlwaysShowEditor]
    ScrollBars = ssNone
    TabOrder = 0
    OnExit = sg_RamExit
    OnKeyPress = sg_RamKeyPress
    OnSelectCell = sg_RamSelectCell
  end
  object b_Save: TButton
    Left = 8
    Top = 8
    Width = 75
    Height = 17
    Caption = 'Save'
    TabOrder = 1
    OnClick = b_SaveClick
  end
  object b_Load: TButton
    Left = 104
    Top = 8
    Width = 75
    Height = 17
    Caption = 'Load'
    TabOrder = 2
    OnClick = b_LoadClick
  end
  object rb_Hex: TRadioButton
    Left = 459
    Top = 8
    Width = 113
    Height = 17
    Caption = 'Hexadecimal'
    Checked = True
    TabOrder = 3
    TabStop = True
    OnClick = rb_HexClick
  end
  object rb_Dec: TRadioButton
    Left = 383
    Top = 8
    Width = 62
    Height = 17
    Caption = 'Decimal'
    TabOrder = 4
    OnClick = rb_DecClick
  end
  object rb_Bin: TRadioButton
    Left = 307
    Top = 8
    Width = 54
    Height = 17
    Caption = 'Binary'
    TabOrder = 5
    OnClick = rb_BinClick
  end
  object e_Page: TEdit
    Left = 685
    Top = 6
    Width = 76
    Height = 21
    MaxLength = 2
    TabOrder = 6
    Text = '0'
    OnExit = e_PageExit
    OnKeyPress = sg_RamKeyPress
  end
  object b_Import: TButton
    Left = 200
    Top = 8
    Width = 75
    Height = 17
    Caption = 'Import'
    TabOrder = 7
    OnClick = b_ImportClick
  end
  object ud_Page: TUpDown
    Left = 760
    Top = 6
    Width = 46
    Height = 21
    Max = 255
    Orientation = udHorizontal
    TabOrder = 8
    OnClick = ud_PageClick
  end
  object sd_Ram: TSaveDialog
    DefaultExt = '.xml'
    FileName = 'RAM.xml'
    Filter = 'all|*.*|xml|*.xml'
    Options = [ofOverwritePrompt, ofHideReadOnly, ofPathMustExist, ofEnableSizing]
    Title = 'Save RAM to'
    Left = 23
    Top = 84
  end
  object od_Ram: TOpenDialog
    DefaultExt = '.xml'
    FileName = 'RAM.xml'
    Filter = 'all|*.*|xml|*.xml'
    Options = [ofHideReadOnly, ofPathMustExist, ofEnableSizing]
    Title = 'Load RAM from'
    Left = 23
    Top = 124
  end
  object cds_Ram: TClientDataSet
    Aggregates = <>
    Filter = 'Page='#39'00'#39
    Filtered = True
    FilterOptions = [foCaseInsensitive, foNoPartialCompare]
    Params = <>
    Left = 24
    Top = 44
    object cds_RamLine: TIntegerField
      FieldName = 'Line'
    end
    object cds_RamField01: TStringField
      FieldName = '01'
      Size = 2
    end
    object cds_RamField23: TStringField
      FieldName = '23'
      Size = 2
    end
    object cds_RamField45: TStringField
      FieldName = '45'
      Size = 2
    end
    object cds_RamField67: TStringField
      FieldName = '67'
      Size = 2
    end
    object cds_RamField89: TStringField
      FieldName = '89'
      Size = 2
    end
    object cds_RamFieldAB: TStringField
      FieldName = 'AB'
      Size = 2
    end
    object cds_RamFieldCD: TStringField
      FieldName = 'CD'
      Size = 2
    end
    object cds_RamFieldEF: TStringField
      FieldName = 'EF'
      Size = 2
    end
    object cds_RamPage: TStringField
      FieldName = 'Page'
    end
  end
  object od_Import: TOpenDialog
    DefaultExt = '.dat'
    FileName = 'ImportRAM.dat'
    Filter = 'all|*.*|dat|*.dat|txt|*.txt'
    Options = [ofHideReadOnly, ofPathMustExist, ofEnableSizing]
    Title = 'Import Data from'
    Left = 63
    Top = 124
  end
end
