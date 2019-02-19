object Test: TTest
  Left = 528
  Top = 271
  Width = 468
  Height = 291
  Caption = 'Test'
  Color = clBtnFace
  Font.Charset = RUSSIAN_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Local_Video_Rtp_Loop: TCheckBox
    Left = 56
    Top = 56
    Width = 145
    Height = 17
    Caption = 'Local_Video_Rtp_Loop'
    TabOrder = 0
  end
  object Remote_Video_Rtp_Loop: TCheckBox
    Left = 232
    Top = 56
    Width = 153
    Height = 17
    Caption = 'Remote_Video_Rtp_Loop'
    TabOrder = 1
  end
  object Button1: TButton
    Left = 184
    Top = 208
    Width = 75
    Height = 25
    Caption = 'OK'
    TabOrder = 2
    OnClick = Button1Click
  end
  object ComboBox1: TComboBox
    Left = 56
    Top = 88
    Width = 145
    Height = 21
    ItemHeight = 13
    TabOrder = 3
  end
  object Fps: TCheckBox
    Left = 232
    Top = 88
    Width = 145
    Height = 17
    Caption = 'Fps (Timer)'
    TabOrder = 4
  end
  object Auto_Answer: TCheckBox
    Left = 56
    Top = 32
    Width = 97
    Height = 17
    Caption = 'Auto_Answer'
    TabOrder = 5
  end
end
