object Form2: TForm2
  Left = 572
  Top = 195
  Width = 628
  Height = 560
  HorzScrollBar.Visible = False
  VertScrollBar.Visible = False
  Caption = 'Видео'
  Color = clBtnFace
  Font.Charset = RUSSIAN_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  OnCloseQuery = FormCloseQuery
  OnCreate = FormCreate
  OnHide = FormHide
  OnResize = FormResize
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 112
    Top = 176
    Width = 32
    Height = 13
    Caption = 'Label1'
  end
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 385
    Height = 169
    Caption = 'Panel1'
    TabOrder = 0
  end
  object Button2: TButton
    Left = 424
    Top = 224
    Width = 75
    Height = 25
    Caption = 'CapDlg'
    TabOrder = 1
    OnClick = Button2Click
  end
  object Button3: TButton
    Left = 336
    Top = 224
    Width = 75
    Height = 25
    Caption = 'VideoSource'
    TabOrder = 2
    OnClick = Button3Click
  end
  object Button4: TButton
    Left = 112
    Top = 224
    Width = 75
    Height = 25
    Caption = 'GetCapFile'
    TabOrder = 3
    Visible = False
    OnClick = Button4Click
  end
  object Button5: TButton
    Left = 200
    Top = 224
    Width = 121
    Height = 25
    Caption = 'GetVideoFormatSize'
    TabOrder = 4
    Visible = False
    OnClick = Button5Click
  end
  object ComboBox1: TComboBox
    Left = 112
    Top = 192
    Width = 145
    Height = 21
    ItemHeight = 13
    TabOrder = 5
    OnClick = ComboBox1Click
    OnKeyDown = ComboBox1KeyDown
    OnKeyPress = ComboBox1KeyPress
  end
  object Button1: TButton
    Left = 112
    Top = 264
    Width = 153
    Height = 25
    Caption = 'Управление камерой'
    TabOrder = 6
    OnClick = Button1Click
  end
  object Button6: TButton
    Left = 304
    Top = 264
    Width = 75
    Height = 25
    Caption = 'Сохранить'
    TabOrder = 7
    OnClick = Button6Click
  end
  object Timer1: TTimer
    Enabled = False
    Interval = 10
    OnTimer = Timer1Timer
    Left = 424
    Top = 16
  end
end
