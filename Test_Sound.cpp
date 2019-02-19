//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Test_Sound.h"
#include "SipClient_Unit.h"
#include "MediaChannels.h"
#include "Sip.h"
#include "G711.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TTTest_Sound *TTest_Sound;
//---------------------------------------------------------------------------
__fastcall TTTest_Sound::TTTest_Sound(TComponent* Owner)
        : TForm(Owner)
{
FGC = 50; //50 Hz Первая гарм  
echo_compensation = false;
Normal->Checked = true;
MAX_ECHO_DELAY = 10;  //10 * 20 = 200 ms  // 200 = 200 * 20 = 4 sec //  10;  //10 = 10 * 20 ms = 200 ms
Echo_Log->Checked = false;
kih->Checked = true;
ec_mic->Checked = false;
ec_sound->Checked = true;
First_Block_Only->Checked = false; //true;
Edit1->Text = IntToStr(MAX_ECHO_DELAY);
Label5->Caption = IntToStr(MAX_ECHO_DELAY) + " x 20 ms = " + IntToStr(MAX_ECHO_DELAY * 20) + " ms";
dft_full->Checked = true;
MIC_LEVEL   = 1.2;  //Отношение pic/average
SOUND_LEVEL = 1.5;  //Отношение pic/average
Edit2->Text = FloatToStr(MIC_LEVEL);
Edit3->Text = FloatToStr(SOUND_LEVEL);
LF_Suppr->Checked = true;
LF_Suppr_Freq = 30;
Edit4->Text = 2*LF_Suppr_Freq*FGC;  //3000 Hz //50  Hz
freq_number = 2;
Edit5->Text = IntToStr(freq_number);
Left_Margin = 30;
Edit10->Text = 2*Left_Margin*FGC;  //3000 Hz
Bound = false;
voice_count = 0;
JBD_Min_Control->Checked       = true;
ChDispUnpackRtpPacket->Checked = true;
ChDispToDouble->Checked        = true;
}
//---------------------------------------------------------------------------
void __fastcall TTTest_Sound::Button1Click(TObject *Sender)
{
/*
OpenDialog1->Title = "Sound File";
OpenDialog1->Options.Clear();
OpenDialog1->Options  << ofFileMustExist;// << ofAllowMultiSelect;
OpenDialog1->Filter = "All files (*.*)";
if(OpenDialog1->Execute())
  {
  AnsiString S = OpenDialog1->FileName;
  FILE* f = fopen(S.c_str(),"rb");
  if(f)
    if(MainFormSLS->Sip->ucs)
      {
      TUdpChannel* uc = NULL;
      MainFormSLS->Sip->ucs->Create_RTP_SoundTestCh(&uc);
      uc->wopt->__clearBaseQueue();
      uc->wopt->wave_log("StartAlerting: begin");
      uc->wopt->WAVE_OUT_RESET(WaveOutputState_RECEIVING_VOICE);
      uc->wopt->set_std_format();
      uc->wopt->WAVE_OUT_OPEN(WaveOutputState_RECEIVING_VOICE);
      uc->wopt->WAVE_OUT_SET_VOLUME(0x7FFF7FFF);
      vector<UBYTE> v;
      for(int j=0;j<10;j++)
         {
         TOutPutUdpBlock* opb = new TOutPutUdpBlock;
         opb->v.resize(12,0);
         opb->v[1] = 1;
         for(int i=0;i<320;i++)
            {
            int c = fgetc(f);
            if(c !=EOF)
               opb->v.push_back(c);
            }
         uc->wopt->setQueue(opb);
         }
      }
  }
  */
}
//---------------------------------------------------------------------------
void __fastcall TTTest_Sound::Button5Click(TObject *Sender)
{
if(echo_compensation)
  {
  echo_compensation = false;
  Button5->Caption = "OFF";
  }
else
  {
  echo_compensation = true;
  Button5->Caption = "ON";
  }
}
//---------------------------------------------------------------------------

void __fastcall TTTest_Sound::Button6Click(TObject *Sender)
{
AnsiString S = Edit1->Text;
MAX_ECHO_DELAY = S.ToInt();
Label5->Caption = IntToStr(MAX_ECHO_DELAY) + " x 20 ms = " + IntToStr(MAX_ECHO_DELAY * 20) + " ms";
}
//---------------------------------------------------------------------------

void __fastcall TTTest_Sound::Button2Click(TObject *Sender)
{
AnsiString S = Edit2->Text;
MIC_LEVEL = S.ToDouble();
}
//---------------------------------------------------------------------------

void __fastcall TTTest_Sound::Button3Click(TObject *Sender)
{
AnsiString S = Edit3->Text;
SOUND_LEVEL = S.ToDouble();
}
//---------------------------------------------------------------------------

void __fastcall TTTest_Sound::Button4Click(TObject *Sender)
{
AnsiString S = Edit4->Text;
LF_Suppr_Freq = (StrToIntDef(S,0)/FGC)/2;
}
//---------------------------------------------------------------------------

void __fastcall TTTest_Sound::Button7Click(TObject *Sender)
{
AnsiString S = Edit5->Text;
freq_number = S.ToIntDef(0);
}
//---------------------------------------------------------------------------

void __fastcall TTTest_Sound::Button8Click(TObject *Sender)
{
Bound = true;
}
//---------------------------------------------------------------------------

static short I = 0;
void __fastcall TTTest_Sound::Button9Click(TObject *Sender)
{
UBYTE Ba = linear2alaw(I);
short C = alaw2linear(Ba);
//UBYTE Ba = linear2ulaw(I);
//short C = ulaw2linear(Ba);


AnsiString S = IntToHex(I,4);
Edit7->Text = "0x" + S;
S = IntToHex(Ba,4);
Edit8->Text = "0x" + S;
S = IntToHex(C,4);
Edit9->Text = "0x" + S;
I++;
}
//---------------------------------------------------------------------------

void __fastcall TTTest_Sound::Button10Click(TObject *Sender)
{
I = 0;
Edit7->Text = "";
Edit8->Text = "";
Edit9->Text = "";
}
//---------------------------------------------------------------------------

void __fastcall TTTest_Sound::Button11Click(TObject *Sender)
{
AnsiString S = Edit10->Text;
Left_Margin  = (StrToIntDef(S,0)/FGC)/2;
}
//---------------------------------------------------------------------------


