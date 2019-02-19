object TTest_Sound: TTTest_Sound
  Left = 5
  Top = 0
  Width = 798
  Height = 560
  Caption = 'Test_Sound'
  Color = clBtnFace
  Font.Charset = RUSSIAN_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Noise_Suppression: TLabel
    Left = 208
    Top = 96
    Width = 91
    Height = 13
    Caption = 'Noise_Suppression'
  end
  object Label4: TLabel
    Left = 408
    Top = 112
    Width = 78
    Height = 13
    Caption = 'Max Echo Delay'
  end
  object Label5: TLabel
    Left = 624
    Top = 112
    Width = 90
    Height = 13
    Caption = 'n  x  20 ms =  N ms'
  end
  object Label1: TLabel
    Left = 496
    Top = 88
    Width = 117
    Height = 13
    Caption = 'ECHO_CANCELLATION'
  end
  object Label2: TLabel
    Left = 496
    Top = 176
    Width = 49
    Height = 13
    Caption = 'Mic_Level'
  end
  object Label6: TLabel
    Left = 488
    Top = 200
    Width = 63
    Height = 13
    Caption = 'Sound_Level'
  end
  object Label7: TLabel
    Left = 688
    Top = 136
    Width = 6
    Height = 13
    Caption = '+'
  end
  object Label3: TLabel
    Left = 488
    Top = 224
    Width = 181
    Height = 13
    Caption = 'Количество  анализируемых частот'
  end
  object Label8: TLabel
    Left = 536
    Top = 472
    Width = 26
    Height = 13
    Caption = '16 bit'
  end
  object Label9: TLabel
    Left = 536
    Top = 520
    Width = 26
    Height = 13
    Caption = '16 bit'
  end
  object Label10: TLabel
    Left = 536
    Top = 496
    Width = 27
    Height = 13
    Caption = 'ALaw'
  end
  object Label11: TLabel
    Left = 488
    Top = 296
    Width = 223
    Height = 13
    Caption = 'Минимальная частота для анализа спектра'
  end
  object Label12: TLabel
    Left = 552
    Top = 440
    Width = 42
    Height = 13
    Caption = '(Info Ctrl)'
  end
  object Button1: TButton
    Left = 72
    Top = 72
    Width = 75
    Height = 25
    Caption = 'Button1'
    TabOrder = 0
    OnClick = Button1Click
  end
  object MicLog: TCheckBox
    Left = 496
    Top = 16
    Width = 97
    Height = 17
    Caption = 'Mic_Log'
    TabOrder = 1
  end
  object SoundLog: TCheckBox
    Left = 624
    Top = 16
    Width = 97
    Height = 17
    Caption = 'Sound_Log'
    TabOrder = 2
  end
  object Button5: TButton
    Left = 208
    Top = 112
    Width = 75
    Height = 25
    Caption = 'OFF'
    TabOrder = 3
    OnClick = Button5Click
  end
  object sqrt: TCheckBox
    Left = 88
    Top = 128
    Width = 97
    Height = 17
    Caption = 'sqrt'
    TabOrder = 4
  end
  object Button6: TButton
    Left = 496
    Top = 136
    Width = 75
    Height = 25
    Caption = 'OK'
    TabOrder = 5
    OnClick = Button6Click
  end
  object Edit1: TEdit
    Left = 496
    Top = 112
    Width = 121
    Height = 21
    TabOrder = 6
  end
  object First_Block_Only: TCheckBox
    Left = 576
    Top = 136
    Width = 97
    Height = 17
    Caption = 'First_Block_Only'
    TabOrder = 7
  end
  object Echo_Log: TCheckBox
    Left = 624
    Top = 88
    Width = 97
    Height = 17
    Caption = 'Echo_Log'
    TabOrder = 8
  end
  object Edit2: TEdit
    Left = 560
    Top = 176
    Width = 49
    Height = 21
    TabOrder = 9
  end
  object Edit3: TEdit
    Left = 560
    Top = 200
    Width = 49
    Height = 21
    TabOrder = 10
  end
  object Button2: TButton
    Left = 616
    Top = 176
    Width = 57
    Height = 25
    Caption = 'OK'
    TabOrder = 11
    OnClick = Button2Click
  end
  object Button3: TButton
    Left = 616
    Top = 200
    Width = 57
    Height = 25
    Caption = 'OK'
    TabOrder = 12
    OnClick = Button3Click
  end
  object Subst_For_Echo: TCheckBox
    Left = 576
    Top = 152
    Width = 97
    Height = 17
    Caption = 'Subst_For_Echo'
    TabOrder = 13
  end
  object Freq_Check: TCheckBox
    Left = 704
    Top = 136
    Width = 97
    Height = 17
    Caption = 'Freq_Check'
    TabOrder = 14
  end
  object GroupBox1: TGroupBox
    Left = 184
    Top = 216
    Width = 185
    Height = 161
    Caption = 'Сглаживающие окна'
    TabOrder = 15
    object Normal: TRadioButton
      Left = 24
      Top = 24
      Width = 113
      Height = 17
      Caption = 'Normal'
      TabOrder = 0
    end
    object Sin: TRadioButton
      Left = 24
      Top = 48
      Width = 113
      Height = 17
      Caption = 'Sin'
      TabOrder = 1
    end
    object RadioButton3: TRadioButton
      Left = 24
      Top = 72
      Width = 113
      Height = 17
      Caption = 'RadioButton3'
      TabOrder = 2
    end
    object Blackman: TRadioButton
      Left = 24
      Top = 96
      Width = 113
      Height = 17
      Caption = 'Blackman'
      TabOrder = 3
    end
    object Hann: TRadioButton
      Left = 24
      Top = 120
      Width = 113
      Height = 17
      Caption = 'Hann'
      TabOrder = 4
    end
  end
  object kih: TCheckBox
    Left = 32
    Top = 208
    Width = 97
    Height = 17
    Caption = 'kih'
    TabOrder = 16
  end
  object Log_In_Out: TCheckBox
    Left = 208
    Top = 192
    Width = 97
    Height = 17
    Caption = 'Log_In_Out'
    TabOrder = 17
  end
  object HF_Suppr: TCheckBox
    Left = 296
    Top = 392
    Width = 97
    Height = 17
    Caption = 'HF_Suppr'
    TabOrder = 18
  end
  object LF_Suppr: TCheckBox
    Left = 168
    Top = 392
    Width = 97
    Height = 17
    Caption = 'LF_Suppr'
    TabOrder = 19
  end
  object Button4: TButton
    Left = 168
    Top = 440
    Width = 75
    Height = 25
    Caption = 'Button4'
    TabOrder = 20
    OnClick = Button4Click
  end
  object Edit4: TEdit
    Left = 168
    Top = 416
    Width = 89
    Height = 21
    TabOrder = 21
  end
  object ec_mic: TCheckBox
    Left = 208
    Top = 144
    Width = 97
    Height = 17
    Caption = 'ec_mic'
    TabOrder = 22
  end
  object ec_sound: TCheckBox
    Left = 304
    Top = 144
    Width = 97
    Height = 17
    Caption = 'ec_sound'
    TabOrder = 23
  end
  object Left_Half_Spect: TCheckBox
    Left = 304
    Top = 192
    Width = 129
    Height = 17
    Caption = 'Left_Half_Spect'
    TabOrder = 24
  end
  object dft_full: TCheckBox
    Left = 576
    Top = 240
    Width = 97
    Height = 17
    Caption = 'dft_full'
    TabOrder = 25
  end
  object mic_dft_full_log: TCheckBox
    Left = 680
    Top = 240
    Width = 113
    Height = 17
    Caption = 'mic_dft_full_log'
    TabOrder = 26
  end
  object sound_dft_full_log: TCheckBox
    Left = 680
    Top = 264
    Width = 145
    Height = 17
    Caption = 'sound_dft_full_log'
    TabOrder = 27
  end
  object dft_full_freq: TCheckBox
    Left = 576
    Top = 264
    Width = 97
    Height = 17
    Caption = 'dft_full_freq'
    TabOrder = 28
  end
  object Button7: TButton
    Left = 488
    Top = 264
    Width = 75
    Height = 25
    Caption = 'Button7'
    TabOrder = 29
    OnClick = Button7Click
  end
  object Edit5: TEdit
    Left = 488
    Top = 240
    Width = 73
    Height = 21
    TabOrder = 30
  end
  object Button8: TButton
    Left = 176
    Top = 496
    Width = 75
    Height = 25
    Caption = 'Bound'
    TabOrder = 31
    OnClick = Button8Click
  end
  object Edit6: TEdit
    Left = 176
    Top = 544
    Width = 121
    Height = 21
    TabOrder = 32
    Text = 'Edit6'
  end
  object FourieTransform: TCheckBox
    Left = 208
    Top = 168
    Width = 129
    Height = 17
    Caption = 'FourieTransform'
    TabOrder = 33
  end
  object Edit7: TEdit
    Left = 576
    Top = 472
    Width = 121
    Height = 21
    TabOrder = 34
    Text = 'Edit7'
  end
  object Edit8: TEdit
    Left = 576
    Top = 496
    Width = 121
    Height = 21
    TabOrder = 35
    Text = 'Edit8'
  end
  object Button9: TButton
    Left = 664
    Top = 560
    Width = 75
    Height = 25
    Caption = 'Button9'
    TabOrder = 36
    OnClick = Button9Click
  end
  object Edit9: TEdit
    Left = 576
    Top = 520
    Width = 121
    Height = 21
    TabOrder = 37
    Text = 'Edit9'
  end
  object Button10: TButton
    Left = 520
    Top = 560
    Width = 75
    Height = 25
    Caption = 'Clear'
    TabOrder = 38
    OnClick = Button10Click
  end
  object Edit10: TEdit
    Left = 488
    Top = 320
    Width = 121
    Height = 21
    TabOrder = 39
  end
  object Button11: TButton
    Left = 488
    Top = 352
    Width = 75
    Height = 25
    Caption = 'Button11'
    TabOrder = 40
    OnClick = Button11Click
  end
  object JBD_Min: TCheckBox
    Left = 488
    Top = 440
    Width = 65
    Height = 17
    Caption = 'JBD_Min'
    TabOrder = 41
  end
  object JBD_Min_Control: TCheckBox
    Left = 488
    Top = 424
    Width = 121
    Height = 17
    Caption = 'JBD_Min_Control'
    TabOrder = 42
  end
  object ChDispUnpackRtpPacket: TCheckBox
    Left = 488
    Top = 392
    Width = 153
    Height = 17
    Caption = 'ChDispUnpackRtpPacket'
    TabOrder = 43
  end
  object ChDispToDouble: TCheckBox
    Left = 488
    Top = 408
    Width = 113
    Height = 17
    Caption = 'ChDispToDouble'
    TabOrder = 44
  end
  object OpenDialog1: TOpenDialog
    Left = 168
    Top = 72
  end
end
