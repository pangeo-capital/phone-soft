object ParallelPhone: TParallelPhone
  Left = 532
  Top = 269
  Width = 400
  Height = 231
  Caption = 'Параллельный телефон'
  Color = clBtnFace
  Font.Charset = RUSSIAN_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsStayOnTop
  OldCreateOrder = False
  OnClose = FormClose
  OnCloseQuery = FormCloseQuery
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 96
    Top = 48
    Width = 25
    Height = 13
    Caption = 'Порт'
  end
  object Label2: TLabel
    Left = 96
    Top = 80
    Width = 22
    Height = 13
    Caption = 'Имя'
  end
  object Edit1: TEdit
    Left = 136
    Top = 40
    Width = 121
    Height = 21
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
  end
  object Edit2: TEdit
    Left = 136
    Top = 72
    Width = 121
    Height = 21
    TabOrder = 1
  end
  object Button1: TButton
    Left = 280
    Top = 152
    Width = 75
    Height = 25
    Caption = 'Button1'
    TabOrder = 2
    OnClick = Button1Click
  end
  object CheckBox1: TCheckBox
    Left = 136
    Top = 16
    Width = 97
    Height = 17
    Caption = 'CheckBox1'
    TabOrder = 3
  end
end
