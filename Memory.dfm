object f_Memory: Tf_Memory
  Left = 0
  Top = 0
  Caption = 'Program Memory'
  ClientHeight = 499
  ClientWidth = 685
  Color = clBtnFace
  Constraints.MaxWidth = 701
  Constraints.MinHeight = 169
  Constraints.MinWidth = 701
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
    685
    499)
  PixelsPerInch = 96
  TextHeight = 13
  object l_Data: TLabel
    Left = 205
    Top = 425
    Width = 27
    Height = 13
    Anchors = [akLeft, akBottom]
    Caption = 'Data:'
  end
  object l_AddrTx: TLabel
    Left = 8
    Top = 475
    Width = 71
    Height = 13
    Anchors = [akLeft, akBottom]
    Caption = 'Address Delta:'
  end
  object l_AddrVal: TLabel
    Left = 85
    Top = 475
    Width = 36
    Height = 13
    Anchors = [akLeft, akBottom]
    Caption = '0x0000'
  end
  object l_Sort: TLabel
    Left = 136
    Top = 475
    Width = 24
    Height = 13
    Anchors = [akLeft, akBottom]
    Caption = 'Sort:'
    Visible = False
  end
  object l_Width: TLabel
    Left = 336
    Top = 425
    Width = 76
    Height = 13
    Anchors = [akLeft, akBottom]
    Caption = 'MaxData: 8 bits'
  end
  object cb_OpCode: TComboBox
    Left = 8
    Top = 422
    Width = 185
    Height = 21
    Anchors = [akLeft, akBottom]
    DropDownCount = 18
    ParentShowHint = False
    ShowHint = True
    TabOrder = 0
    Text = 'OpCode'
    OnChange = cb_OpCodeChange
  end
  object cb_D: TComboBox
    Left = 607
    Top = 422
    Width = 70
    Height = 21
    Style = csDropDownList
    Anchors = [akLeft, akBottom]
    DropDownCount = 16
    ItemIndex = 0
    TabOrder = 1
    Text = '0'
    Items.Strings = (
      '0'
      '1'
      '2'
      '3'
      '4'
      '5'
      '6'
      '7'
      '8'
      '9'
      'A'
      'B'
      'C'
      'D'
      'E'
      'F')
  end
  object cb_C: TComboBox
    Left = 519
    Top = 422
    Width = 70
    Height = 21
    Style = csDropDownList
    Anchors = [akLeft, akBottom]
    DropDownCount = 16
    Enabled = False
    ItemIndex = 0
    TabOrder = 2
    Text = '0'
    Items.Strings = (
      '0'
      '1'
      '2'
      '3'
      '4'
      '5'
      '6'
      '7'
      '8'
      '9'
      'A'
      'B'
      'C'
      'D'
      'E'
      'F')
  end
  object cb_B: TComboBox
    Left = 431
    Top = 422
    Width = 70
    Height = 21
    Style = csDropDownList
    Anchors = [akLeft, akBottom]
    DropDownCount = 16
    Enabled = False
    ItemIndex = 0
    TabOrder = 3
    Text = '0'
    Items.Strings = (
      '0'
      '1'
      '2'
      '3'
      '4'
      '5'
      '6'
      '7'
      '8'
      '9'
      'A'
      'B'
      'C'
      'D'
      'E'
      'F')
  end
  object e_Data: TEdit
    Left = 237
    Top = 422
    Width = 94
    Height = 21
    Anchors = [akLeft, akBottom]
    TabOrder = 4
    Text = '0000'
    OnExit = e_DataExit
    OnKeyPress = e_DataKeyPress
  end
  object rb_Bin: TRadioButton
    Left = 237
    Top = 444
    Width = 93
    Height = 17
    Anchors = [akLeft, akBottom]
    Caption = 'Binary'
    TabOrder = 5
    OnClick = rb_BinClick
  end
  object rb_Dec: TRadioButton
    Left = 237
    Top = 461
    Width = 93
    Height = 17
    Anchors = [akLeft, akBottom]
    Caption = 'Decimal'
    TabOrder = 6
    OnClick = rb_DecClick
  end
  object rb_Hex: TRadioButton
    Left = 237
    Top = 478
    Width = 93
    Height = 17
    Anchors = [akLeft, akBottom]
    Caption = 'Hexadecimal'
    Checked = True
    TabOrder = 7
    TabStop = True
    OnClick = rb_HexClick
  end
  object b_Delete: TButton
    Left = 617
    Top = 466
    Width = 60
    Height = 25
    Anchors = [akRight, akBottom]
    Caption = 'Delete'
    TabOrder = 8
    OnClick = b_DeleteClick
  end
  object b_Edit: TButton
    Left = 529
    Top = 466
    Width = 60
    Height = 25
    Anchors = [akRight, akBottom]
    Caption = 'Edit'
    TabOrder = 9
    OnClick = b_EditClick
  end
  object b_Add: TButton
    Left = 352
    Top = 466
    Width = 60
    Height = 25
    Anchors = [akRight, akBottom]
    Caption = 'Add'
    TabOrder = 10
    OnClick = b_AddClick
  end
  object dbg_Mem: TDBGrid
    Left = 8
    Top = 32
    Width = 669
    Height = 384
    Anchors = [akLeft, akTop, akRight, akBottom]
    DataSource = ds_Mem
    Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgConfirmDelete, dgCancelOnExit]
    TabOrder = 11
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'Tahoma'
    TitleFont.Style = []
    OnDblClick = dbg_MemDblClick
  end
  object e_Sort: TEdit
    Left = 161
    Top = 472
    Width = 65
    Height = 19
    Anchors = [akLeft, akBottom]
    Enabled = False
    TabOrder = 12
    Text = 'Sort'
    Visible = False
  end
  object b_Insert: TButton
    Left = 441
    Top = 466
    Width = 60
    Height = 25
    Anchors = [akRight, akBottom]
    Caption = 'Insert ^'
    TabOrder = 13
    OnClick = b_InsertClick
  end
  object b_Save: TButton
    Left = 8
    Top = 8
    Width = 75
    Height = 18
    Caption = 'Save'
    TabOrder = 14
    OnClick = b_SaveClick
  end
  object b_Load: TButton
    Left = 104
    Top = 8
    Width = 75
    Height = 18
    Caption = 'Load'
    TabOrder = 15
    OnClick = b_LoadClick
  end
  object b_Import: TButton
    Left = 602
    Top = 8
    Width = 75
    Height = 18
    Caption = 'Import'
    TabOrder = 16
    OnClick = b_ImportClick
  end
  object e_Comment: TEdit
    Left = 8
    Top = 449
    Width = 185
    Height = 21
    Anchors = [akLeft, akBottom]
    TabOrder = 17
  end
  object b_Clear: TButton
    Left = 504
    Top = 8
    Width = 75
    Height = 18
    Caption = 'Clear'
    TabOrder = 18
    OnClick = b_ClearClick
  end
  object cds_Mem: TClientDataSet
    Aggregates = <>
    FieldDefs = <>
    IndexDefs = <>
    Params = <>
    StoreDefs = True
    AfterScroll = cds_MemAfterScroll
    OnCalcFields = cds_MemCalcFields
    Left = 144
    Top = 40
    object cds_MemAddress: TIntegerField
      DisplayWidth = 8
      FieldKind = fkCalculated
      FieldName = 'Address'
      Visible = False
      Calculated = True
    end
    object cds_MemAddrHex: TStringField
      FieldKind = fkCalculated
      FieldName = 'AddrHex'
      Size = 4
      Calculated = True
    end
    object cds_MemAddrDelta: TIntegerField
      FieldName = 'AddrDelta'
      Visible = False
    end
    object cds_MemMnemonic: TStringField
      FieldName = 'Mnemonic'
      Size = 5
    end
    object cds_MemHumData: TStringField
      DisplayLabel = 'HumanReadable'
      DisplayWidth = 32
      FieldName = 'HumData'
      Size = 64
    end
    object cds_MemCode: TStringField
      DisplayLabel = 'MachineCode'
      DisplayWidth = 18
      FieldName = 'Code'
      Size = 16
    end
    object cds_MemCodeHex: TStringField
      FieldName = 'CodeHex'
      Size = 4
    end
    object cds_MemComment: TStringField
      DisplayWidth = 28
      FieldName = 'Comment'
      Size = 64
    end
    object cds_MemOpCode: TIntegerField
      FieldName = 'OpCode'
      Visible = False
    end
    object cds_MemData: TStringField
      FieldName = 'Data'
      Visible = False
      Size = 8
    end
    object cds_MemDataType: TIntegerField
      FieldName = 'DataType'
      Visible = False
    end
    object cds_MemRB: TIntegerField
      FieldName = 'RB'
      Visible = False
    end
    object cds_MemRC: TIntegerField
      FieldName = 'RC'
      Visible = False
    end
    object cds_MemRD: TIntegerField
      FieldName = 'RD'
      Visible = False
    end
    object cds_MemSort: TIntegerField
      FieldName = 'Sort'
      Visible = False
    end
  end
  object ds_Mem: TDataSource
    DataSet = cds_Mem
    OnDataChange = ds_MemDataChange
    Left = 104
    Top = 40
  end
  object sd_Mem: TSaveDialog
    DefaultExt = '.xml'
    FileName = 'ROM.xml'
    Filter = 'xml|*.xml|all|*.*'
    Options = [ofOverwritePrompt, ofHideReadOnly, ofPathMustExist, ofEnableSizing]
    Title = 'Save ROM to'
    Left = 184
    Top = 40
  end
  object od_Mem: TOpenDialog
    DefaultExt = '.xml'
    FileName = 'ROM.xml'
    Filter = 'xml|*.xml|all|*.*'
    Options = [ofHideReadOnly, ofPathMustExist, ofEnableSizing]
    Title = 'Load ROM from'
    Left = 224
    Top = 40
  end
  object od_Assembler: TOpenDialog
    DefaultExt = '.asm'
    Filter = 'asm|*.asm|txt|*.txt|all|*.*'
    Options = [ofPathMustExist, ofEnableSizing]
    Title = 'Load Program From'
    Left = 304
    Top = 40
  end
end
