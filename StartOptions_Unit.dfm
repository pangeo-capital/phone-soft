object StartOptionsWin: TStartOptionsWin
  Left = 448
  Top = 438
  HorzScrollBar.Visible = False
  VertScrollBar.Visible = False
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsDialog
  Caption = 'StartOptionsWin'
  ClientHeight = 94
  ClientWidth = 388
  Color = clBtnFace
  Font.Charset = RUSSIAN_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  ShowHint = True
  OnCreate = FormCreate
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object CheckBox1: TCheckBox
    Left = 80
    Top = 16
    Width = 297
    Height = 17
    Caption = 'CheckBox1'
    TabOrder = 0
  end
  object Button1: TButton
    Left = 80
    Top = 48
    Width = 75
    Height = 25
    Caption = 'Сохранить'
    TabOrder = 1
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 184
    Top = 48
    Width = 75
    Height = 25
    Caption = 'Выход'
    TabOrder = 2
    OnClick = Button2Click
  end
end
