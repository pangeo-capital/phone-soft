object SoundTool: TSoundTool
  Left = 420
  Top = 189
  BorderStyle = bsDialog
  Caption = 'Звук'
  ClientHeight = 393
  ClientWidth = 574
  Color = clBtnFace
  Font.Charset = RUSSIAN_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label3: TLabel
    Left = 384
    Top = 8
    Width = 22
    Height = 13
    Caption = 'Filter'
  end
  object Label8: TLabel
    Left = 296
    Top = 8
    Width = 58
    Height = 13
    Caption = 'EchoCancel'
  end
  object Label9: TLabel
    Left = 384
    Top = 200
    Width = 22
    Height = 13
    Caption = 'Filter'
  end
  object Label10: TLabel
    Left = 384
    Top = 248
    Width = 35
    Height = 13
    Caption = 'Record'
  end
  object Label11: TLabel
    Left = 384
    Top = 56
    Width = 96
    Height = 13
    Caption = 'Silence Suppression'
  end
  object Label12: TLabel
    Left = 384
    Top = 296
    Width = 150
    Height = 13
    Caption = 'Silence Suppression (Test Only)'
  end
  object Label13: TLabel
    Left = 384
    Top = 104
    Width = 79
    Height = 13
    Caption = 'Noise Reduction'
  end
  object Label14: TLabel
    Left = 384
    Top = 344
    Width = 79
    Height = 13
    Caption = 'Noise Reduction'
  end
  object Button3: TButton
    Left = 280
    Top = 104
    Width = 75
    Height = 25
    Caption = 'StopSound'
    TabOrder = 0
    Visible = False
    OnClick = Button3Click
  end
  object Button4: TButton
    Left = 384
    Top = 24
    Width = 57
    Height = 25
    Caption = 'OFF'
    TabOrder = 1
    OnClick = Button4Click
  end
  object Button5: TButton
    Left = 384
    Top = 216
    Width = 57
    Height = 25
    Caption = 'OFF'
    TabOrder = 2
    OnClick = Button5Click
  end
  object Edit1: TEdit
    Left = 32
    Top = 296
    Width = 25
    Height = 21
    TabOrder = 3
  end
  object Edit2: TEdit
    Left = 24
    Top = 96
    Width = 25
    Height = 21
    TabOrder = 4
  end
  object Button6: TButton
    Left = 296
    Top = 24
    Width = 57
    Height = 25
    Caption = 'OFF'
    TabOrder = 5
    OnClick = Button6Click
  end
  object Button7: TButton
    Left = 384
    Top = 264
    Width = 57
    Height = 25
    Caption = 'OFF'
    TabOrder = 6
    OnClick = Button7Click
  end
  object Button8: TButton
    Left = 384
    Top = 72
    Width = 57
    Height = 25
    Caption = 'OFF'
    TabOrder = 7
    OnClick = Button8Click
  end
  object Button9: TButton
    Left = 384
    Top = 312
    Width = 57
    Height = 25
    Caption = 'OFF'
    TabOrder = 8
    OnClick = Button9Click
  end
  object Button10: TButton
    Left = 384
    Top = 120
    Width = 57
    Height = 25
    Caption = 'OFF'
    TabOrder = 9
    OnClick = Button10Click
  end
  object Button11: TButton
    Left = 384
    Top = 360
    Width = 75
    Height = 25
    Caption = 'OFF'
    TabOrder = 10
    OnClick = Button11Click
  end
  object Panel1: TPanel
    Left = 40
    Top = 8
    Width = 521
    Height = 289
    TabOrder = 11
    object Bevel1: TBevel
      Left = 0
      Top = 80
      Width = 505
      Height = 1
    end
    object Label1: TLabel
      Left = 64
      Top = 8
      Width = 53
      Height = 13
      Caption = 'Микрофон'
    end
    object Label6: TLabel
      Left = 336
      Top = 48
      Width = 22
      Height = 13
      Caption = '0 dB'
    end
    object Label7: TLabel
      Left = 16
      Top = 48
      Width = 103
      Height = 13
      Caption = 'Регулировка уровня'
    end
    object Bevel2: TBevel
      Left = 8
      Top = 168
      Width = 505
      Height = 1
    end
    object Label2: TLabel
      Left = 80
      Top = 96
      Width = 53
      Height = 13
      Caption = 'Динамики'
    end
    object Label5: TLabel
      Left = 32
      Top = 136
      Width = 103
      Height = 13
      Caption = 'Регулировка уровня'
    end
    object Label4: TLabel
      Left = 336
      Top = 136
      Width = 22
      Height = 13
      Caption = '0 dB'
    end
    object Bevel3: TBevel
      Left = 16
      Top = 216
      Width = 497
      Height = 1
    end
    object Label15: TLabel
      Left = 96
      Top = 184
      Width = 37
      Height = 13
      Caption = 'Звонок'
    end
    object ComboBox1: TComboBox
      Left = 168
      Top = 8
      Width = 145
      Height = 21
      ItemHeight = 13
      TabOrder = 0
    end
    object ProgressBar1: TProgressBar
      Left = 168
      Top = 32
      Width = 150
      Height = 9
      Min = 0
      Max = 100
      TabOrder = 1
    end
    object TrackBar2: TTrackBar
      Left = 160
      Top = 48
      Width = 158
      Height = 25
      Orientation = trHorizontal
      Frequency = 1
      Position = 0
      SelEnd = 0
      SelStart = 0
      TabOrder = 2
      TickMarks = tmBottomRight
      TickStyle = tsNone
      OnChange = TrackBar2Change
    end
    object ComboBox2: TComboBox
      Left = 168
      Top = 96
      Width = 145
      Height = 21
      ItemHeight = 13
      TabOrder = 3
    end
    object ProgressBar2: TProgressBar
      Left = 168
      Top = 120
      Width = 150
      Height = 9
      Min = 0
      Max = 100
      TabOrder = 4
    end
    object TrackBar1: TTrackBar
      Left = 160
      Top = 136
      Width = 150
      Height = 25
      Orientation = trHorizontal
      Frequency = 1
      Position = 0
      SelEnd = 0
      SelStart = 0
      TabOrder = 5
      TickMarks = tmBottomRight
      TickStyle = tsNone
      OnChange = TrackBar1Change
    end
    object ComboBox3: TComboBox
      Left = 168
      Top = 184
      Width = 145
      Height = 21
      ItemHeight = 13
      TabOrder = 6
    end
    object Button2: TButton
      Left = 424
      Top = 224
      Width = 75
      Height = 25
      Caption = 'Cancel'
      TabOrder = 7
      OnClick = Button2Click
    end
    object Button1: TButton
      Left = 328
      Top = 224
      Width = 75
      Height = 25
      Caption = 'Save'
      TabOrder = 8
      OnClick = Button1Click
    end
  end
end
