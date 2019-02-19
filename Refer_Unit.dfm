object ReferWin: TReferWin
  Left = 528
  Top = 0
  Width = 544
  Height = 567
  Caption = 'œ≈–≈¿ƒ–≈—¿÷»ﬂ'
  Color = clBtnFace
  Font.Charset = RUSSIAN_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnCloseQuery = FormCloseQuery
  OnCreate = FormCreate
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Refer_Img: TImage
    Left = 80
    Top = 192
    Width = 161
    Height = 49
    Stretch = True
    OnMouseDown = Refer_ImgMouseDown
    OnMouseMove = Refer_ImgMouseMove
    OnMouseUp = Refer_ImgMouseUp
  end
  object Refer_Ans_Img: TImage
    Left = 288
    Top = 192
    Width = 161
    Height = 49
    OnMouseDown = Refer_Ans_ImgMouseDown
    OnMouseMove = Refer_Ans_ImgMouseMove
    OnMouseUp = Refer_Ans_ImgMouseUp
  end
end
