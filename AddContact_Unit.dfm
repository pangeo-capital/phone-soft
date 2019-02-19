object AddContact: TAddContact
  Left = 215
  Top = 189
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'Добавить  контакт'
  ClientHeight = 396
  ClientWidth = 677
  Color = clBtnFace
  Font.Charset = RUSSIAN_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  OnResize = FormResize
  PixelsPerInch = 96
  TextHeight = 13
  object PageControl1: TPageControl
    Left = 0
    Top = 0
    Width = 677
    Height = 345
    ActivePage = TabSheet1
    TabOrder = 0
    object TabSheet1: TTabSheet
      Caption = 'Контактная информация'
      object Label1: TLabel
        Left = 0
        Top = 32
        Width = 28
        Height = 13
        Caption = ' Имя '
      end
      object Label2: TLabel
        Left = 0
        Top = 72
        Width = 61
        Height = 13
        Caption = 'Полное имя'
      end
      object Label3: TLabel
        Left = 0
        Top = 112
        Width = 82
        Height = 13
        Caption = 'Контактное имя'
      end
      object Label4: TLabel
        Left = 0
        Top = 168
        Width = 88
        Height = 13
        Caption = 'Рабочий телефон'
      end
      object Label5: TLabel
        Left = 0
        Top = 192
        Width = 101
        Height = 13
        Caption = 'Домашний телефон'
      end
      object Label6: TLabel
        Left = 0
        Top = 216
        Width = 105
        Height = 13
        Caption = 'Мобильный телефон'
      end
      object Label7: TLabel
        Left = 0
        Top = 240
        Width = 29
        Height = 13
        Caption = 'Факс'
      end
      object Label8: TLabel
        Left = 0
        Top = 264
        Width = 97
        Height = 13
        Caption = 'Злектронная почта'
      end
      object StaticText1: TStaticText
        Left = 128
        Top = 176
        Width = 4
        Height = 4
        TabOrder = 0
      end
      object Contact_Name: TRichEdit
        Left = 96
        Top = 24
        Width = 185
        Height = 25
        Color = clWhite
        Lines.Strings = (
          'Contact_Name')
        TabOrder = 1
      end
      object RichEdit3: TRichEdit
        Left = 296
        Top = 64
        Width = 145
        Height = 25
        Lines.Strings = (
          'RichEdit3')
        TabOrder = 2
      end
      object RichEdit4: TRichEdit
        Left = 448
        Top = 64
        Width = 153
        Height = 25
        Lines.Strings = (
          'RichEdit4')
        TabOrder = 3
      end
      object Display_Name: TRichEdit
        Left = 96
        Top = 104
        Width = 441
        Height = 25
        Lines.Strings = (
          'Display_Name')
        TabOrder = 4
      end
      object RichEdit2: TRichEdit
        Left = 96
        Top = 64
        Width = 185
        Height = 25
        Lines.Strings = (
          'RichEdit2')
        TabOrder = 5
      end
      object Work_Phone: TRichEdit
        Left = 112
        Top = 160
        Width = 185
        Height = 25
        Lines.Strings = (
          'Work_Phone')
        TabOrder = 6
      end
      object Home_Phone: TRichEdit
        Left = 112
        Top = 184
        Width = 185
        Height = 25
        Lines.Strings = (
          'Home_Phone')
        TabOrder = 7
      end
      object Mobile_Phone: TRichEdit
        Left = 112
        Top = 208
        Width = 185
        Height = 25
        Lines.Strings = (
          'Mobile_Phone')
        TabOrder = 8
      end
      object Fax_Phone: TRichEdit
        Left = 112
        Top = 232
        Width = 185
        Height = 25
        Lines.Strings = (
          'Fax_Phone')
        TabOrder = 9
      end
      object E_Mail: TRichEdit
        Left = 112
        Top = 256
        Width = 185
        Height = 25
        Lines.Strings = (
          'E_Mail')
        TabOrder = 10
      end
    end
  end
  object Button1: TButton
    Left = 568
    Top = 360
    Width = 81
    Height = 25
    Caption = 'Отменить'
    TabOrder = 1
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 456
    Top = 360
    Width = 89
    Height = 25
    Caption = 'OK'
    TabOrder = 2
    OnClick = Button2Click
  end
end
