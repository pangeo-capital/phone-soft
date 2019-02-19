//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Test_Unit.h"
#include "SipClient_Unit.h"
#include "Unit4.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TTest *Test;
//---------------------------------------------------------------------------
__fastcall TTest::TTest(TComponent* Owner)
        : TForm(Owner)
{
ComboBox1->Items->Add("100");
ComboBox1->Items->Add("150");
ComboBox1->Items->Add("200");
}
//---------------------------------------------------------------------------

void __fastcall TTest::Button1Click(TObject *Sender)
{
#ifdef Client_Test_Block
if(Auto_Answer->Checked)
  MainFormSLS->Sip->TestBlock.auto_answer = true;
else
  MainFormSLS->Sip->TestBlock.auto_answer = false;
#ifdef SIP_Video
if(Local_Video_Rtp_Loop->Checked)
  MainFormSLS->Sip->TestBlock.local_video_rtp_loop = true;
else
  MainFormSLS->Sip->TestBlock.local_video_rtp_loop = false;

if(Remote_Video_Rtp_Loop->Checked)
  MainFormSLS->Sip->TestBlock.remote_video_rtp_loop = true;
else
  MainFormSLS->Sip->TestBlock.remote_video_rtp_loop = false;

if(Fps->Checked)
  {
  string s = ComboBox1->Text.c_str();
  int a = strtoint(s);
  Form4->Timer1->Enabled  = false;
  Form4->Timer1->Interval = a;
  Form4->Timer1->Enabled  = true;
  }
#endif //#ifdef SIP_Video
#endif //#ifdef Client_Test_Block
Close();
}
//---------------------------------------------------------------------------


