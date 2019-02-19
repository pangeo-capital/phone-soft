//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop


#include "SoundTool_Unit.h"
#include "Test_Sound.h"
#include <mmsystem.h>
#include <registry.hpp>
#include <Filectrl.hpp>
#include "const.h"
#include "SipClient_Unit.h"

#pragma package(smart_init)
#pragma resource "*.dfm"

const string _InternalSpeaker = "Speaker";
const string in_s     = "in_s";    //microphone
const string in_vol   = "in_vol";
const string out_s    = "out_s";   //dynamic
const string out_vol  = "out_vol";
const string ring     = "ring";
const string _ws     = " ";
const string _lf     = "\n";

TSoundTool *SoundTool;
//------------------------------------------------------------------------------
__fastcall TSoundTool::TSoundTool(TComponent* Owner)
        : TForm(Owner)
{
stop_sound   = false;
echo_suppr   = false;
mic_level_corrector = 0; //-10; //dB
start_type   = 0;

mic_filter                  = false;
mic_silence_suppr           = false;
mic_noise_reduction         = false;
mic_track_bar_prev_position = 0;
mic_pow_coeff               = 1.0;

sound_filter                  = false;
sound_record                  = false;
sound_silence_suppr           = false;
sound_noise_reduction         = false;
sound_track_bar_prev_position = 0;
sound_pow_coeff               = 1.0;

ProgressBar1->Max  = 8192;
ProgressBar2->Max  = 8192;
TrackBar1->Max     =  20;  // dB Sound
TrackBar1->Min     = -20;
TrackBar2->Max     =  20;  // dB Mic
TrackBar2->Min     = -20;
#ifndef Client_Test_Sound
Label3->Visible   = false;
Label8->Visible   = false;
Label9->Visible   = false;
Label10->Visible  = false;
Label11->Visible  = false;
Label12->Visible  = false;
Label13->Visible  = false;
Label14->Visible  = false;
Edit1->Visible    = false;
Edit2->Visible    = false;
Button6->Visible  = false;
Button3->Visible  = false;
Button4->Visible  = false;
Button5->Visible  = false;
Button7->Visible  = false;
Button8->Visible  = false;
Button9->Visible  = false;
Button10->Visible = false;
Button11->Visible = false;
Label1->Top       = ComboBox1->Top;
ComboBox2->Top    = TrackBar2->Top    + TrackBar2->Height + 40;
Label2->Top       = ComboBox2->Top;
ProgressBar2->Top = ComboBox2->Top    + ComboBox2->Height + 10;
TrackBar1->Top    = ProgressBar2->Top + ProgressBar2->Height + 10;
Label5->Top       = TrackBar1->Top;
Label4->Top       = TrackBar1->Top;
Button1->Top      = TrackBar1->Top    + TrackBar1->Height    + 10;
Button1->Left     = TrackBar1->Left;
Button1->Caption  = "Сохранить";
Button2->Top      = Button1->Top;
Button2->Left     = TrackBar1->Left   + TrackBar1->Width - Button2->Width;
Button2->Caption  = "Выход";
Height            = Button1->Top      + Button1->Height + 80;
Width             = 2*ComboBox1->Left + ComboBox1->Width;
#endif
Panel1->Color     = MainFormSLS->PanelColor;
read_sound_data();
}
//------------------------------------------------------------------------------
void __fastcall TMediaDevice::set_media_device(const string& s, int i)
{
::EnterCriticalSection(&md_cs);
  if(i == -1)
     name.clear();
  else
     name = s;
  num  = i;
::LeaveCriticalSection(&md_cs);
}
//------------------------------------------------------------------------------
void __fastcall TSoundTool::ins_dev(device_list& dl, const string& s, int i)
{
dl.insert(device_list::value_type(s,i));
}
//------------------------------------------------------------------------------
int __fastcall TSoundTool::get_dev_by_string(device_list& dl, const string& s)
{
device_list::iterator it = dl.find(s);
if(it != dl.end())
  return (*it).second;
return -1;
}
//------------------------------------------------------------------------------
void __fastcall TSoundTool::clear_dev(device_list& dl)
{
dl.clear();
}
//------------------------------------------------------------------------------
int  __fastcall TSoundTool::get_size(device_list& dl)
{
return dl.size();
}
//------------------------------------------------------------------------------
void __fastcall TSoundTool::Button1Click(TObject *Sender)
{
TRegistry& regKey = *new TRegistry();
regKey.RootKey = ROOT_KEY;
bool keyGood = regKey.OpenKey(key_name.c_str(),false);
if(!keyGood)
  keyGood = regKey.OpenKey(key_name.c_str(),true);
if(keyGood)
  {
  keyGood = regKey.OpenKey(dev_key_name.c_str(),false);
  if(!keyGood)
     keyGood = regKey.OpenKey(dev_key_name.c_str(),true);
  if(keyGood)
    {
    keyGood = regKey.OpenKey(sound_key_name.c_str(),false);
    if(!keyGood)
        keyGood = regKey.OpenKey(sound_key_name.c_str(),true);
    if(keyGood)
      {
      string dev_in  = ComboBox1->Text.c_str();
      string dev_out = ComboBox2->Text.c_str();
      int num_in = get_dev_by_string(get_in_dev_list(),dev_in);
      int num_out = get_dev_by_string(get_out_dev_list(),dev_out);
      if(get_size(get_in_dev_list()) < 2)
        {
        dev_in.clear();
        MainFormSLS->in_sound_dev.set_media_device(dev_in,-1);
        regKey.WriteString(sound_in_device_name.c_str(),dev_in.c_str());
        }
      else
        {
        if(num_in != -1)
          {
          MainFormSLS->in_sound_dev.set_media_device(dev_in,num_in);
          regKey.WriteString(sound_in_device_name.c_str(),ComboBox1->Text);
          }
        }
      if(get_size(get_out_dev_list()) < 2)
        {
        dev_out.clear();
        MainFormSLS->out_sound_dev.set_media_device(dev_out,-1);
        regKey.WriteString(sound_out_device_name.c_str(),dev_out.c_str());
        }
      else
        {
        if(num_out != -1)
          {
          MainFormSLS->out_sound_dev.set_media_device(dev_out,num_out);
          regKey.WriteString(sound_out_device_name.c_str(),ComboBox2->Text);
          }
        }
      }
    }
  regKey.CloseKey();
  }
delete &regKey;


AnsiString MicDevice;
AnsiString DynamicDevice;
AnsiString RingDevice;
string s_cl = MainFormSLS->get_client_dir();
if(check_directory_existence(s_cl))
  {
  s_cl += "\\cl.rst";
  FILE* f = fopen(s_cl.c_str(),"rt");
  if(f)
    {
    char buf[256];
    if(fgets( buf,sizeof(buf), f))
      {
      fclose(f);
      string s = string(buf);
      s_cl = MainFormSLS->get_clients_dir();
      s_cl += "\\" + s + "\\INI";
      if(check_directory_existence(s_cl))
        {
        s_cl += "\\sound";
        f = fopen(s_cl.c_str(),"wt");
        if(f)
          {
          MicDevice = ComboBox1->Text;  // microphone device
          string s = in_s + _ws + MicDevice.c_str() + _lf;
          fputs(s.c_str(),f);

          int a = TrackBar2->Position;     // microphone level
          s = in_vol + _ws + inttostr(a) + _lf;
          fputs(s.c_str(),f);

          DynamicDevice = ComboBox2->Text;             // dynamic device
          s = out_s + _ws + DynamicDevice.c_str() + _lf;
          fputs(s.c_str(),f);

          a = TrackBar1->Position;         // dynamic level
          s = out_vol + _ws + inttostr(a) + _lf;
          fputs(s.c_str(),f);

          RingDevice = ComboBox3->Text;               // ring device
          s = ring + _ws + RingDevice.c_str() + _lf;
          fputs(s.c_str(),f);

          fclose(f);
          }
        }
      }
    }
  }

string dev_in   = MicDevice.c_str();
string dev_out  = DynamicDevice.c_str();
string dev_ring = RingDevice.c_str();
int num_in      = get_dev_by_string(get_in_dev_list(),dev_in);
int num_out     = get_dev_by_string(get_out_dev_list(),dev_out);
if(get_size(get_in_dev_list()) < 2)
  {
  dev_in.clear();
  MainFormSLS->in_sound_dev.set_media_device(dev_in,-1);
  }
else
  {
  if(num_in != -1)
    MainFormSLS->in_sound_dev.set_media_device(dev_in,num_in);
  }
if(get_size(get_out_dev_list()) < 2)
  {
  dev_out.clear();
  MainFormSLS->out_sound_dev.set_media_device(dev_out,-1);
  }
else
  {
  if(num_out != -1)
    MainFormSLS->out_sound_dev.set_media_device(dev_out,num_out);
  }
Close();
}
//------------------------------------------------------------------------------
void __fastcall TSoundTool::Button2Click(TObject *Sender)
{
Close();
}
//------------------------------------------------------------------------------
void __fastcall TSoundTool::FormShow(TObject *Sender)
{
Panel1->Align       = alClient;
ComboBox1->Width    = Width/3 + 50;
ComboBox1->Left     = Width/2 - ComboBox1->Width/2;
ProgressBar1->Left  = ComboBox1->Left;
ProgressBar1->Width = ComboBox1->Width;
ProgressBar1->Top   = ComboBox1->Top    + ComboBox1->Height    + 3;
TrackBar2->Top      = ProgressBar1->Top + ProgressBar1->Height + 3;
TrackBar2->Left     = ComboBox1->Left  - 8;
TrackBar2->Width    = ComboBox1->Width + 16;
TrackBar2->Height   = 20;

Label1->Top         = ComboBox1->Top;
Label1->Left        = ComboBox1->Left - Label1->Width - 20;
Label7->Top         = TrackBar2->Top;
Label7->Left        = ComboBox1->Left - Label7->Width - 20;
Label6->Top         = Label7->Top;
Label6->Left        = ComboBox1->Left + ComboBox1->Width  + 15;

Bevel1->Top         = TrackBar2->Top  + TrackBar2->Height + 5;
Bevel1->Left        = 10;
Bevel1->Height      = 1;
Bevel1->Width       = Width - 25;

ComboBox2->Left     = ComboBox1->Left;
ComboBox2->Top      = Bevel1->Top + 10;
ComboBox2->Width    = ComboBox1->Width;
ProgressBar2->Left  = ComboBox2->Left;
ProgressBar2->Width = ComboBox2->Width;
ProgressBar2->Top   = ComboBox2->Top    + ComboBox2->Height    + 3;
TrackBar1->Top      = ProgressBar2->Top + ProgressBar2->Height + 3;
TrackBar1->Left     = TrackBar2->Left;
TrackBar1->Width    = TrackBar2->Width;
TrackBar1->Height   = TrackBar2->Height;
Bevel2->Top         = TrackBar1->Top + TrackBar1->Height + 10;
Bevel2->Left        = Bevel1->Left;
Bevel2->Height      = 1;
Bevel2->Width       = Bevel1->Width;
Label2->Left        = Label1->Left;
Label2->Top         = ComboBox2->Top;
Label5->Left        = Label7->Left;
Label5->Top         = TrackBar1->Top;
Label4->Top         = Label5->Top;
Label4->Left        = Label6->Left;

ComboBox3->Left     = ComboBox1->Left;
ComboBox3->Top      = Bevel2->Top + 10;
ComboBox3->Width    = ComboBox1->Width;
Label15->Top        = ComboBox3->Top;
Label15->Left       = ComboBox3->Left - Label15->Width     - 20;
Bevel3->Top         = ComboBox3->Top  + ComboBox3->Height + 10;
Bevel3->Left        = Bevel1->Left;
Bevel3->Height      = 1;
Bevel3->Width       = Bevel1->Width;

Button2->Top        = Bevel3->Top + 10;
Button2->Left       = Width - Button2->Width - 20;
Button1->Width      = Button2->Width;
Button1->Top        = Button2->Top;
Button1->Left       = Button2->Left - Button1->Width - 20;

Height = Button2->Top + Button2->Height + 40;
//Button2->SetFocus();

ComboBox1->Clear();
ComboBox2->Clear();
ComboBox3->Clear();
ProgressBar2->Position = 0;
ProgressBar1->Position = 0;
clear_dev(get_in_dev_list());
clear_dev(get_out_dev_list());
int numDevs = waveInGetNumDevs();
WAVEINCAPS wic;
for (int i = 0; i < numDevs; i++)
    {
     if(!waveInGetDevCaps(i, &wic, sizeof(WAVEINCAPS)))
       {
       ComboBox1->Items->Append(AnsiString(wic.szPname));
       ins_dev(get_in_dev_list(), string(wic.szPname), i);
       }
    }
numDevs = waveOutGetNumDevs();
WAVEOUTCAPS woc;
for (int i = 0; i < numDevs; i++)
   {
   if(!waveOutGetDevCaps(i, &woc, sizeof(WAVEOUTCAPS)))
     {
     ComboBox2->Items->Append(AnsiString(woc.szPname));
     ComboBox3->Items->Append(AnsiString(woc.szPname));
     ins_dev(get_out_dev_list(), string(woc.szPname), i);
     }
   }

if(MainFormSLS->in_sound_dev.num != -1)
   ComboBox1->Text = MainFormSLS->in_sound_dev.name.c_str();
else
   ComboBox1->Text = ComboBox1->Items->Strings[0];

ComboBox3->Items->Append(_InternalSpeaker.c_str());

if(MainFormSLS->out_sound_dev.num != -1)
   ComboBox2->Text = MainFormSLS->out_sound_dev.name.c_str();
else
   {
   ComboBox2->Text = ComboBox2->Items->Strings[0];
   ComboBox3->Text = ComboBox3->Items->Strings[0];
   }

if(IniSound.in_level)
  TrackBar2->Position = IniSound.in_level;
if(IniSound.out_level)
  TrackBar1->Position = IniSound.out_level;

if(start_type == 1)
  {
  Label1->Visible    = false;
  Label2->Visible    = false;
  Label15->Visible   = false;
  Label7->Caption    = "Микрофон";
  Label7->Left        = ComboBox1->Left - Label7->Width - 20;
  Label5->Caption    = "Динамики";
  Label5->Left        = ComboBox2->Left - Label5->Width - 20;
  ComboBox1->Visible = false;
  ComboBox2->Visible = false;
  ComboBox3->Visible = false;
  Button1->Visible   = false;
  }
else
  {
  Label1->Visible    = true;
  Label2->Visible    = true;
  Label15->Visible   = true;
  Label7->Caption    = "Регулировка уровня";
  Label7->Left       = ComboBox1->Left - Label7->Width - 20;
  Label5->Caption    = "Регулировка уровня";
  Label5->Left       = ComboBox2->Left - Label5->Width - 20;
  ComboBox1->Visible = true;
  ComboBox2->Visible = true;
  ComboBox3->Visible = true;
  Button1->Visible   = true;
  }
}
//------------------------------------------------------------------------------
void __fastcall TSoundTool::Button3Click(TObject *Sender)
{
if(stop_sound)
   stop_sound = false;
else
   stop_sound = true;
}
//------------------------------------------------------------------------------
void __fastcall TSoundTool::Button4Click(TObject *Sender)
{
if(mic_filter)
   {
   mic_filter = false;
   Button4->Caption = "OFF";
   }
else
   {
   mic_filter = true;
   Button4->Caption = "ON";
   }
}
//---------------------------------------------------------------------------

void __fastcall TSoundTool::Button5Click(TObject *Sender)
{
if(sound_filter)
   {
   sound_filter = false;
   Button5->Caption = "OFF";
   }
else
   {
   sound_filter = true;
   Button5->Caption = "ON";
   }
}
//---------------------------------------------------------------------------
void __fastcall TSoundTool::TrackBar1Change(TObject *Sender)
{
int pos = TrackBar1->Position;
if(sound_track_bar_prev_position != pos)
  {
  sound_track_bar_prev_position = pos;
  sound_pow_coeff = pow(10.0,pos/20.0);
  AnsiString S;
  if(pos > 0)
     S += "+";
  S += IntToStr(pos) + " dB";
  Label4->Caption = S;
  }
//Button2->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TVolume::pow_volume(vector<UBYTE>& v,double p_coeff)
{
vector<short> x;
vector<double> y;
int sz = v.size();
ubyte_2_short(x,v,sz);
short_2_double(y,x);
double abs_max = abs_max_value(y);
if(p_coeff == 1.0)
  {
  if(abs_max > 32000.0)
     {
     int sz_y = y.size();
     if(sz_y)
       {
       p_coeff = 32000.0/abs_max;
       for(int i=0;i<sz_y;i++)
           y[i] *= p_coeff;
       double_2_short(x,y,sz_y,false);
       short_2_ubyte(v,x,sz_y);
       }
     }
  return;
  }

if(abs_max > 0.1)
   if(abs_max * p_coeff > 32000.0)
     p_coeff = 32000.0/abs_max;
int sz_y = y.size();
for(int i=0;i<sz_y;i++)
    y[i] *= p_coeff;
double_2_short(x,y,sz_y,false);
short_2_ubyte(v,x,sz_y);
}
//---------------------------------------------------------------------------
void __fastcall TVolume::pow_volume(TOutPutUdpBlock* opb,double p_coeff)
{
vector<short> x;
int sz = opb->vd.size();
if(!sz)
   return;
if(p_coeff == 1.0)
  {
  if(opb->abs_max > 32000.0)
     {
     p_coeff = 32000.0/opb->abs_max;
     for(int i=0;i<sz;i++)
         opb->vd[i] *= p_coeff;
     double_2_short(x,opb->vd,sz,false);
     short_2_ubyte(opb->v,x,sz);
     }
  return;
  }

if(opb->abs_max > 0.1)
   if(opb->abs_max * p_coeff > 32000.0)
     p_coeff = 32000.0/opb->abs_max;
for(int i=0;i<sz;i++)
    opb->vd[i] *= p_coeff;
double_2_short(x,opb->vd,sz,false);
short_2_ubyte(opb->v,x,sz);
}
//-----------------------------------------------------------------------------
/*
void __fastcall TVolume::diff_volume(vector<UBYTE>& curr_v,vector<UBYTE>& prev_v)
{
int curr_sz = curr_v.size();
int prev_sz = prev_v.size();
if(curr_sz)
  if(curr_sz == prev_sz)
    {
    vector<short> curr_x;
    ubyte_2_short(curr_x,curr_v,curr_sz);
    vector<short> prev_x;
    ubyte_2_short(prev_x,prev_v,prev_sz);
    curr_sz = curr_x.size();
    for(int i=0;i<curr_sz;i++)
        curr_x[i] = curr_x[i] - prev_x[i];
    short_2_ubyte(curr_v,curr_x,curr_sz);
    }


}
*/
//---------------------------------------------------------------------------
void __fastcall TSoundTool::TrackBar2Change(TObject *Sender)
{
int pos = TrackBar2->Position;
if(mic_track_bar_prev_position != pos)
  {
  mic_track_bar_prev_position = pos;
  mic_pow_coeff = pow(10.0,(pos + mic_level_corrector)/20.0);
  AnsiString S;
  if(pos > 0)
     S += "+";
  S += IntToStr(pos) + " dB";
  Label6->Caption = S;
  }
//Button2->SetFocus();
}
//---------------------------------------------------------------------------
int  __fastcall TVolume::zero_crossing(vector<short>& xv)
{
int count = 0;
int sz = xv.size();
for(int i=0;i<sz;i++)
   {
   if(!i)
     continue;
   if(xv[i] >= 0)
     {
     if(xv[i-1] < 0)
        count++;
     }
   else
     {
     if(xv[i-1] >= 0)
        count++;
     }
   }
return count;
}
//------------------------------------------------------------------------------
void __fastcall TVolume::Detect_Voice_Activity(TWaveBaseThread* BT,int sz_xyz,TEdit* Edit,double sum)
{
switch(av.detect_voice_activity(BT,vt,sz_xyz,Edit,sum)){
      case 1:{
             if(vt == TVolume_Type__Mic)
               {
               /*
               string timestr;
               TDateTime dt = dt.CurrentTime();
               exsTime( dt,timestr);
               double pic     = 20*log10(sum);
               double average = 20*log10(av.av_val);
             //  int zc = zero_crossing(xv_1);
               string s = "\n" + timestr + " mic av: " + (string)FloatToStr(average).c_str() + " pic: " + FloatToStr(pic).c_str();
                          // " zc: " + inttostr(zc);
               BT->wave_log(s);
                */
               }
             else if(vt == TVolume_Type__Sound)
               {
               /*
               string timestr;
               TDateTime dt = dt.CurrentTime();
               exsTime( dt,timestr);
               double pic     = 20*log10(sum);
               double average = 20*log10(av.av_val);
               //int zc = zero_crossing(xv_1);
               string s = "\n" + timestr + " sound av: " + (string)FloatToStr(average).c_str() + " pic: " + FloatToStr(pic).c_str();
                         //  " zc: " + inttostr(zc);
               BT->wave_log(s);
               */
               }
             break;
             }
      case 2:
            break;
      }
}
//------------------------------------------------------------------------------
void __fastcall TVolume::voice_detect_proc(TWaveBaseThread* BT,TOutPutUdpBlock* opb,TEdit* Edit)
{
int sz = opb->v.size();
if(sz)
  {
  vector<short> xv;

  short abs_a_max = 0;
  #ifdef Sound_Freq_Zero
  vector<short> xv_1;
  double freq_zero = 0.0; //0-я частота(постоянная составляющая сигнала)
  #endif
  for(int i=0;i<sz;i+=2)
     {
     if(i+1 < sz)
       {
       short a = opb->v[i];    //LSB
       a |= opb->v[i+1] << 8;  //MSB with sign
       short abs_a = abs(a);
       xv.push_back(abs_a);
       if(abs_a_max < abs_a)
          abs_a_max = abs_a;
       #ifdef Sound_Freq_Zero
       xv_1.push_back(a);
       #endif
       }
     }
  #ifdef Full_Fourie_Transform
  TSampleFreqImage sfi;
  #endif //#ifdef Full_Fourie_Transform

  double sum = 0.0;
  int xsz = xv.size();
  if(xsz != 0)
    {
    for(int i=0;i<xsz;i++)
      sum += xv[i];
    sum = sum/xsz;

    av.xyz.push_back(sum);
    int sz_xyz = av.xyz.size();
    Detect_Voice_Activity(BT,sz_xyz,Edit,sum);


    #ifdef Sound_Freq_Zero
    int xv_1_sz = xv_1.size();
    for(int i=0;i<xv_1_sz;i++)
       freq_zero += xv_1[i];
    freq_zero = freq_zero/xv_1_sz;
    #endif

    #ifdef Full_Fourie_Transform
    sfi.sum_pic_val = sum;
    sfi.abs_a_max   = abs_a_max;
    sfi.freq_zero   = freq_zero;
    sfi.sample      = xv_1;
    sfi.zc = zero_crossing(xv_1);
    #endif

    if(vt == TVolume_Type__Sound)
      {
      #ifdef Full_Fourie_Transform
      if(TTest_Sound->echo_compensation)
        if(TTest_Sound->ec_sound->Checked)
          dft_1_1(BT,opb,sfi);
      if(SoundTool->echo_suppr)
        {
        // dft(BT,opb,sfi);
        if(TTest_Sound->dft_full->Checked)
          dft_full(BT,opb,sfi);
        else
          dft_2(BT,opb,sfi);
        }
      #endif
      if(TTest_Sound->SoundLog->Checked)
        {
        double val_db;
        string timestr;
        TDateTime dt = dt.CurrentTime();
        exsTime( dt,timestr);
        string s = "\n" + timestr + " sound pic_val: " + (string)FloatToStr(sum).c_str();
        BT->wave_log(s);
        }
      }
    else if(vt == TVolume_Type__Mic)
      {
      #ifdef Full_Fourie_Transform
      if(TTest_Sound->echo_compensation)
        if(TTest_Sound->ec_mic->Checked)
          {
          if(sfi.sum_pic_val > av.av_val)
            {
            int mq_sz = mq.get_mic_queue_size();
            switch(mq_sz){
                   case 0: sfi.gradient = sfi.sum_pic_val - prv_mic_sfi.sum_pic_val;
                           if(sfi.gradient < 0)
                              break;
                           if(av.av_val > 0.1)
                            if(sfi.sum_pic_val/av.av_val > TTest_Sound->MIC_LEVEL)
                              {
                              mq.push_mic_queue(sfi);
                              mq.convers_state = 1; //Start of determination
                              mq.local_max     = sfi.sum_pic_val;
                              }
                           break;
                   case 1: sfi.gradient = sfi.sum_pic_val - prv_mic_sfi.sum_pic_val;
                           mq.push_mic_queue(sfi);
                           if(sfi.gradient > 0.0)
                             {
                             mq.convers_state = 3; //Рост, Рост. Ждем след sample
                             mq.local_max     = sfi.sum_pic_val;
                             }
                           else
                             mq.convers_state = 2; // не определенно
                           break;
                   case 2: sfi.gradient = sfi.sum_pic_val - prv_mic_sfi.sum_pic_val;
                           mq.push_mic_queue(sfi);
                           if(sfi.gradient > 0.0)
                             {
                             if(mq.convers_state == 3)
                               {
                               mq.convers_state = 4; //три последовательных роста. Ждем след.
                               mq.local_max = sfi.sum_pic_val;
                               }
                             else if(mq.convers_state == 2)
                               {
                               if(mq.local_max < sfi.sum_pic_val)
                                 {
                                 mq.convers_state = 5; //рост, падение, рост. Последнее значение больше local_max
                                 mq.local_max = sfi.sum_pic_val;
                                 }
                               else
                                 {
                                 mq.convers_state = 6;  //рост, падение, рост. Но последнее значение меньше local_max. Ждем следующий sample
                                 }
                               }
                             }
                           else
                             {
                             if(mq.convers_state == 3)
                               {
                               mq.convers_state = 7; //рост, рост, падение
                               }
                             else if(mq.convers_state == 2)
                               {
                               mq.clear_mic_queue(); //рост, падение, падение. Начало след цикла.
                               }
                             }
                           break;
                   case 3: sfi.gradient = sfi.sum_pic_val - prv_mic_sfi.sum_pic_val;
                           mq.push_mic_queue(sfi);
                           if(sfi.gradient > 0.0)
                             {
                             if(mq.convers_state == 4) //четыре последовательных роста. Start echo analyzer
                               {
                                mq.clear_mic_queue();
                                mq.found = true;
                               }
                             else if(mq.convers_state == 5) //рост, падение, рост, рост. Последнее значение больше local_max
                               {
                               mq.clear_mic_queue();
                               mq.found = true;
                               }
                             else if(mq.convers_state == 6) //рост, падение, рост, рост. Последнее значение меньше local_max
                               mq.clear_mic_queue();
                             else if(mq.convers_state == 7)
                               {
                               mq.clear_mic_queue();       //рост, рост, падение, рост
                               mq.found = true;
                               }
                             }
                           else
                             mq.clear_mic_queue(); //рост, падение, рост, падение. Начало след цикла.
                           break;
                  }
            }
          else
             mq.clear_mic_queue();

          dft_1_1(BT,opb,sfi);
          prv_mic_sfi = sfi;
          }
      if(SoundTool->echo_suppr)
        {
        if(TTest_Sound->dft_full->Checked)
          dft_full(BT,opb,sfi);
        else
          dft_2(BT,opb,sfi);
        }
      #endif
      if(TTest_Sound->Subst_For_Echo->Checked) //Подстановка минимального значения предыдущего сигнала вместо эха
         mv.get_min_value(sum,av.av_val,opb);
      if(TTest_Sound->MicLog->Checked)
        {
        double val_db;
        string timestr;
        TDateTime dt = dt.CurrentTime();
        exsTime( dt,timestr);
        string s = "\n" + timestr + " pic_val: " + (string)FloatToStr(sum).c_str() + " min_val: " + (string)FloatToStr(mv.min_val).c_str();
        BT->wave_log(s);
        }
      }  //else if(vt == TVolume_Type__Mic)




 //   av.xyz.push_back(sum);
 //   int sz_xyz = av.xyz.size();
    #ifdef Full_Fourie_Transform
    if(vt == TVolume_Type__Sound) //прием
      if(SoundTool->echo_suppr)
        {
        eq.push_sound_queue(sfi);
        if(TTest_Sound->Echo_Log->Checked)
           eq.max_echo_delay = TTest_Sound->MAX_ECHO_DELAY; //for test only !!!
        }
    #endif

  //  Detect_Voice_Activity(BT,sz_xyz,Edit,sum);

    #ifdef Full_Fourie_Transform
    if(vt == TVolume_Type__Mic) //передача (mic)
      if(SoundTool->echo_suppr)
        {
        if(eq.count_block)
          {
          eq.count_block--;
          if(TTest_Sound->Subst_For_Echo->Checked)
            {
            if(mv.ready) //min value from mic received ?
               opb->v = mv.v;
            else
               {
               for(int i=0;i<sz;i++)
                   opb->v[i] = 0;
               }
            }
          else
            {
            for(int i=0;i<sz;i++)
                opb->v[i] = 0;
            }
          }
        else
         {
        if(sum > av.av_val)
         if(av.av_val > 0.0)
          if((sum/av.av_val) > TTest_Sound->MIC_LEVEL)
           {
           if(Uc)
             {
             if(Uc->wopt)
               {
               deque<TSampleFreqImage> out;
               Uc->wopt->sound_vol.eq.get_sound_queue(out);
               if(!out.empty())
                 {
                 int ii=0;
                 deque<TSampleFreqImage>::iterator out_it = out.begin();
                 while(out_it != out.end())
                    {
                    TSampleFreqImage sound_sfi = (*out_it);
                    if(sound_sfi.sum_pic_val > Uc->wopt->sound_vol.av.av_val)
                     if(Uc->wopt->sound_vol.av.av_val > 0.0)
                      if((sound_sfi.sum_pic_val/Uc->wopt->sound_vol.av.av_val) >  TTest_Sound->SOUND_LEVEL)
                        {
                        if(TTest_Sound->First_Block_Only->Checked)
                          {
                          if(TTest_Sound->Freq_Check->Checked)
                            {
                            if(!compare_sfi_by_freq(sfi,sound_sfi));
                               break;
                            }
                          if(TTest_Sound->Subst_For_Echo->Checked)
                            {
                            if(mv.ready) //min value from mic received ?
                               opb->v = mv.v;
                            else
                               {
                               for(int i=0;i<sz;i++)
                                   opb->v[i] = 0;
                               }
                            }
                          else
                            {
                            for(int i=0;i<sz;i++)
                                opb->v[i] = 0;
                            }
                          if(TTest_Sound->Echo_Log->Checked)
                            {
                            string s = "\necho detected\n" +
                            (string)"pic_val " + FloatToStr(sum).c_str() +
                            " mic_av_val " +  FloatToStr(av.av_val).c_str() +
                            " pic/av " + FloatToStr(sum/av.av_val).c_str() + "\n" +
                            (string)"sound_pic_val " + (string)FloatToStr(sound_sfi.sum_pic_val).c_str() +
                            " sound_av_val " + FloatToStr(Uc->wopt->sound_vol.av.av_val).c_str() +
                            " pic/av " + FloatToStr(sound_sfi.sum_pic_val/Uc->wopt->sound_vol.av.av_val).c_str();
                            int e_size_1 = out.size();
                            int e_size_2 = Uc->wopt->sound_vol.eq.get_echo_queue_size();
                            s += " sz_1 " + inttostr(e_size_1) + " sz_2 " + inttostr(e_size_2) + "\n";
                            string mic_sfi_time_st;
                            string sound_sfi_time_st;
                            string diff_time_st;
                            exsTime( sfi.dt,mic_sfi_time_st);
                            exsTime( sound_sfi.dt,sound_sfi_time_st);
                            exsTime( sound_sfi.dt - sfi.dt, diff_time_st);
                            s += "tstamp mic " + mic_sfi_time_st + " sound " + sound_sfi_time_st + " diff " + diff_time_st + "\n";
                            s+= "mic_sample\n";
                            int mic_sample_sz = sfi.sample.size();
                            for(int i=0;i<mic_sample_sz;i++)
                               s+=inttostr(sfi.sample[i]) + ",";
                            s+="\n";
                            s+= "sound_sample\n";
                            int sound_sample_sz = sound_sfi.sample.size();
                            for(int i=0;i<sound_sample_sz;i++)
                               s+=inttostr(sound_sfi.sample[i]) + ",";
                            BT->wave_log(s);
                            }
                          break;
                          }
                        //if(compare_sfi_by_ampl(sfi,sound_sfi))
                        //if(compare_sfi_by_freq(sfi,sound_sfi))
                       // if(compare_sfi_by_ampl_1(sfi,sound_sfi))
                        if(compare_sfi(sfi,sound_sfi))
                          {
                          string timestr;
                          TDateTime dt = dt.CurrentTime();
                          exsTime( dt,timestr);
                          eq.count_block = 15;//0;//3;  15 * 20 = 300 ms
                          if(TTest_Sound->Subst_For_Echo->Checked)
                            {
                            if(mv.ready) //min value from mic received ?
                               opb->v = mv.v;
                            else
                               {
                               for(int i=0;i<sz;i++)
                                   opb->v[i] = 0;
                               }
                            }
                          else
                            {
                            for(int i=0;i<sz;i++)
                                opb->v[i] = 0;
                            }


                          if(TTest_Sound->Echo_Log->Checked)
                            {
                            string s = "\necho detected\n";
                            s+= "mic_sfi max_ampl " + sfi.smax_ampl;
                            s+= "sound_sfi max_ampl " + sound_sfi.smax_ampl;
                            int e_size_1 = out.size();
                            int e_size_2 = Uc->wopt->sound_vol.eq.get_echo_queue_size();
                            s += " sz_1 " + inttostr(e_size_1) + " sz_2 " + inttostr(e_size_2) + "\n";
                            s += "out_sz__i: " + inttostr(ii) + "\n";
                            string mic_sfi_time_st;
                            string sound_sfi_time_st;
                            string diff_time_st;
                            exsTime( sfi.dt,mic_sfi_time_st);
                            exsTime( sound_sfi.dt,sound_sfi_time_st);
                            exsTime( sound_sfi.dt - sfi.dt, diff_time_st);
                            s += "tstamp mic " + mic_sfi_time_st + " sound " + sound_sfi_time_st + " diff " + diff_time_st + "\n";
                            s+= "mic_sample\n";
                            int mic_sample_sz = sfi.sample.size();
                            for(int i=0;i<mic_sample_sz;i++)
                               s+=inttostr(sfi.sample[i]) + ",";
                            s+="\n";
                            s+="mic_zc = " + inttostr(sfi.zc) + " sample_level = " + (string)FloatToStr(sfi.sum_pic_val).c_str() +
                               + " av_val = " + (string)FloatToStr(av.av_val).c_str()
                               + " pic/av = " +  FloatToStr(sfi.sum_pic_val/av.av_val).c_str() + "\n";

                            s+= "sound_sample\n";
                            int sound_sample_sz = sound_sfi.sample.size();
                            for(int i=0;i<sound_sample_sz;i++)
                               s+=inttostr(sound_sfi.sample[i]) + ",";
                            s+="\n";
                            s+="sound_zc = " + inttostr(sound_sfi.zc) + " sample_level = " + (string)FloatToStr(sound_sfi.sum_pic_val).c_str() +
                            + " av_val = " + (string)FloatToStr(Uc->wopt->sound_vol.av.av_val).c_str()
                            + " pic/av = " + FloatToStr(sound_sfi.sum_pic_val/Uc->wopt->sound_vol.av.av_val).c_str() + "\n";
                            BT->wave_log(s);
                            }
                         // out.erase(out_it);
                          break;
                          }
                        }
                    ii++;
                    out_it++;
                    } //while(it != out.end())



                 }



               }
             }
           }
         }

        }
   #endif

    if(sz_xyz < 1000)
      av.av_val = (((double)(sz_xyz-1)/(double)sz_xyz)*av.av_val) + sum/sz_xyz;
    else
      {
      deque<double>::iterator it = av.xyz.begin();
      double a = (*it);
      av.xyz.erase(it);

      int s_z = av.xyz.size();
      av.av_val = av.av_val - (a/s_z);
      av.av_val = av.av_val + sum/s_z;
      }

      if(vt == TVolume_Type__Sound)
        {
        if(TTest_Sound->SoundLog->Checked)
          {
          /*
          double val_db;
          if(av.av_val == 0.0)
            val_db = 20*log10(1e-255);
          else
            val_db = 20*log10(av.av_val);
          */
          string timestr;
          TDateTime dt = dt.CurrentTime();
          exsTime( dt,timestr);
          //  string s = "\n" + timestr + " sound " + (string)FloatToStr(val_db).c_str();
          string s = "\n" + timestr + " sound av_val: " + (string)FloatToStr(av.av_val).c_str();
          BT->wave_log(s);
          }
        }
      else if(vt == TVolume_Type__Mic)
        {
        if(TTest_Sound->MicLog->Checked)
          {
          /*
          double val_db;
          if(av.av_val == 0.0)
            val_db = 20*log10(1e-255);
          else
            val_db = 20*log10(av.av_val);
          */
          string timestr;
          TDateTime dt = dt.CurrentTime();
          exsTime( dt,timestr);
        //  string s = "\n" + timestr + " sound " + (string)FloatToStr(val_db).c_str();
          string s = "\n" + timestr + " mic av_val: " + (string)FloatToStr(av.av_val).c_str();
          BT->wave_log(s);
          }
        }
    }
  }
}
//------------------------------------------------------------------------------
void __fastcall TVolume::voice_detect(TWaveBaseThread* BT,TOutPutUdpBlock* opb,TEdit* Edit)
{
if(vt == TVolume_Type__Mic)
  {
  if(SoundTool->mic_silence_suppr)
    {
    sil_suppr = true;
    voice_detect_proc(BT,opb,Edit);
    opb->silence_suppr_queue = true;
    ssb.sil.push_back(opb);
    return;
    }
  else
    sil_suppr = false;
  if(SoundTool->mic_noise_reduction)
    {
    noise_reduction = true;
    voice_detect_proc(BT,opb,Edit);
    opb->silence_suppr_queue = true;
    ssb.sil.push_back(opb);
    return;
    }
  else
    noise_reduction = false;
  }
else if(vt == TVolume_Type__Sound)
  {
  if(SoundTool->sound_silence_suppr)
    {
    sil_suppr = true;
    voice_detect_proc(BT,opb,Edit);
    opb->silence_suppr_queue = true;
    ssb.sil.push_back(opb);
    return;
    }
  else
    sil_suppr = false;
  if(SoundTool->sound_noise_reduction)
    {
    noise_reduction = true;
    voice_detect_proc(BT,opb,Edit);
    opb->silence_suppr_queue = true;
    ssb.sil.push_back(opb);
    return;
    }
  else
    noise_reduction = false;
  }
voice_detect_proc(BT,opb,Edit);
}
//---------------------------------------------------------------------------
TOutPutUdpBlock* __fastcall TVolume::silence_suppression()
{
if(ssb.sil.size() < ssb.get_sil_sz_max())
   return NULL;   //while(!Terminated)
TOutPutUdpBlock* opb_prev = ssb.sil.front();
ssb.sil.pop_front();
opb_prev->silence_suppr_queue = false;
if(av.voice)
  {
  ssb.set_sil_sz_cur();
  return opb_prev;
  }
else
  {
  if(ssb.get_sil_sz_cur())
    {
    ssb.dec_sil_sz_cur();
    double a = (double)ssb.get_sil_sz_cur()/(double)ssb.get_max_sz_cur_tail();
    if(a < 0.1)
       a = 0.1;
  //  pow_volume(opb_prev->v,a);
    return opb_prev;
    }
  else
    {
    if(sil_suppr)
      {
      opb_prev->discard = true;
      return opb_prev;
      }
   // pow_volume(opb_prev->v,0.1);
    return opb_prev;
    }
  }
}
//---------------------------------------------------------------------------
int __fastcall TAverageVol::detect_voice_activity(TWaveBaseThread* BT,TVolume_Type vt,int sz_xyz,TEdit* Edit,double sum)
{
double high_level_voice_detect  = 0.0;
if(vt == TVolume_Type__Mic)
  high_level_voice_detect  = 1.5;
else
  high_level_voice_detect  = 1.5;
if(sz_xyz > 50)
  {
  if(!voice)
    {
    if(av_val > 0.0)
     if(sum > 0.0)
       if((sum/av_val) > high_level_voice_detect)
         {

         if(vt == TVolume_Type__Sound)
           {
           if(TTest_Sound->SoundLog->Checked)
             {
             string timestr;
             TDateTime dt = dt.CurrentTime();
             exsTime( dt,timestr);
             string s = "\n" + timestr + " sound voice activity start";
             BT->wave_log(s);
             }
           }
         else if(vt == TVolume_Type__Mic)
           {
           if(TTest_Sound->MicLog->Checked)
             {
             string timestr;
             TDateTime dt = dt.CurrentTime();
             exsTime( dt,timestr);
             string s = "\n" + timestr + " mic voice activity start";
             BT->wave_log(s);
             }
           }


         ++voice_activity_count;
         if(voice_activity_count < voice_activity_threshold)
           return 1;
         voice = true;
         //SoundTool->sound_pow_coeff = 1.0;
         if(SoundTool->Visible)
           {
           Edit->Color = clRed;
           Edit->Repaint();
           }
         voice_activity_count = 0;
         return 1;
         }
      else
         {
         voice_activity_count = 0;
         return 1;
         }
    }
  else
    {
    if(av_val > 0.0)
      if(sum < av_val)
        {
        if(vt == TVolume_Type__Sound)
          {
          if(TTest_Sound->SoundLog->Checked)
            {
            string timestr;
            TDateTime dt = dt.CurrentTime();
            exsTime( dt,timestr);
            string s = "\n" + timestr + " sound voice activity STOP";
            BT->wave_log(s);
            }
          }
        else if(vt == TVolume_Type__Mic)
          {
          if(TTest_Sound->MicLog->Checked)
            {
            string timestr;
            TDateTime dt = dt.CurrentTime();
            exsTime( dt,timestr);
            string s = "\n" + timestr + " mic voice activity STOP";
            BT->wave_log(s);
            }
          }

        voice = false;
       // SoundTool->sound_pow_coeff = 0.1;
        if(SoundTool->Visible)
           {
           Edit->Color = clWhite;
           Edit->Repaint();
           }


        return 2;
        }
     else
       {

       if(vt == TVolume_Type__Sound)
         {
        if(TTest_Sound->SoundLog->Checked)
          {
          string timestr;
          TDateTime dt = dt.CurrentTime();
          exsTime( dt,timestr);
          string s = "\n" + timestr + " sound voice activity continue";
          BT->wave_log(s);
          }
         }
       else if(vt == TVolume_Type__Mic)
         {
         if(TTest_Sound->MicLog->Checked)
           {
           string timestr;
           TDateTime dt = dt.CurrentTime();
           exsTime( dt,timestr);
           string s = "\n" + timestr + " mic voice activity continue";
           BT->wave_log(s);
           }
         }

       }
    }
  }
return 0;
}
//---------------------------------------------------------------------------
void __fastcall TSoundTool::Button6Click(TObject *Sender)
{
if(echo_suppr)
  {
  echo_suppr = false;
  Button6->Caption = "OFF";
  }
else
  {
  echo_suppr = true;
  Button6->Caption = "ON";
  }
}
//---------------------------------------------------------------------------
void __fastcall TSoundTool::Button7Click(TObject *Sender)
{
if(sound_record)
  {
  sound_record = false;
  Button7->Caption = "OFF";
  }
else
  {
  sound_record = true;
  Button7->Caption = "ON";
  }
}
//---------------------------------------------------------------------------
void __fastcall TSoundTool::Button8Click(TObject *Sender)
{
if(mic_silence_suppr)
  {
  mic_silence_suppr = false;
  Button8->Caption = "OFF";
  }
else
  {
  mic_silence_suppr = true;
  Button8->Caption = "ON";
  }
}
//---------------------------------------------------------------------------
void __fastcall TSoundTool::Button9Click(TObject *Sender)
{
if(sound_silence_suppr)
  {
  sound_silence_suppr = false;
  Button9->Caption    = "OFF";
  }
else
  {
  sound_silence_suppr = true;
  Button9->Caption    = "ON";
  }
}
//---------------------------------------------------------------------------

void __fastcall TSoundTool::Button10Click(TObject *Sender)
{
if(mic_noise_reduction)
  {
  mic_noise_reduction = false;
  Button10->Caption = "OFF";
  }
else
  {
  mic_noise_reduction = true;
  Button10->Caption = "ON";
  }
}
//---------------------------------------------------------------------------

void __fastcall TSoundTool::Button11Click(TObject *Sender)
{
if(sound_noise_reduction)
  {
  sound_noise_reduction = false;
  Button11->Caption = "OFF";
  }
else
  {
  sound_noise_reduction = true;
  Button11->Caption = "ON";
  }
}
//---------------------------------------------------------------------------
void __fastcall TSoundTool::read_user_sound_data(const string& user,queue<string>& q)
{
string s_cl = MainFormSLS->get_clients_dir();
s_cl += "\\" + user + "\\INI";
if(::DirectoryExists(s_cl.c_str()))
  {
  s_cl += "\\sound";
  FILE* f = fopen(s_cl.c_str(),"rt");
  if(f)
    {
    char buf[256];
    while(fgets(buf,sizeof(buf), f))
         q.push(string(buf));
    fclose(f);
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TSoundTool::get_user_sound_data(queue<string>& q)
{
while(!q.empty())
     {
     string s = q.front();
     q.pop();
     IniSound.get_user_sound_parameter(s);
     }
}
//---------------------------------------------------------------------------
void __fastcall TIniSound::get_user_sound_parameter(string& s)
{
int st = s.find(_lf);
if(st != -1)
   s.resize(st);
int len = s.length();
if(get_device(in_s,in_device,s,len))   //microphone device
   return;
if(get_level(in_vol,in_level,s,len))   //microphone level
   return;
if(get_device(out_s,out_device,s,len)) //dynamic device
   return;
if(get_level(out_vol,out_level,s,len)) //dynamic level
   return;
if(get_device(ring,ring_device,s,len)) //ring device
   return;
}
//---------------------------------------------------------------------------
bool __fastcall TIniSound::get_device(const string& name, string& dest, string& s, int s_len)
{
bool rv = false;
if(get_parameter(name,s,s_len))
  {
  dest = s;
  rv = true;
  }
return rv;
}
//---------------------------------------------------------------------------
bool __fastcall TIniSound::get_level(const string& name, int& dest, string& s, int s_len)
{
bool rv = false;
if(get_parameter(name,s,s_len))
  {
  dest = strtoint(s);
  rv   = true;
  }
return rv;
}
//---------------------------------------------------------------------------
bool __fastcall TIniSound::get_parameter(const string& name, string& s, int s_len)
{
bool rv = false;
if(!s.find(name))
  {
  int st = name.length();
  st++;
  if(st < s_len)
    {
    s = s.substr(st);
    rv = true;
    }
  }
return rv;
}
//---------------------------------------------------------------------------
void __fastcall TSoundTool::read_sound_data()
{
string user = get_current_user();
queue<string> q;
read_user_sound_data(user,q);
get_user_sound_data(q);  //!!!
if(IniSound.in_level)
   mic_pow_coeff = pow(10.0,(IniSound.in_level + mic_level_corrector)/20.0);
else if(mic_level_corrector)
   mic_pow_coeff = pow(10.0,(mic_level_corrector)/20.0);    
if(IniSound.out_level)
   sound_pow_coeff = pow(10.0,IniSound.out_level/20.0);
}
//---------------------------------------------------------------------------
void __fastcall TSoundTool::FormClose(TObject *Sender,
      TCloseAction &Action)
{
MainFormSLS->sound_tool = false;
}
//---------------------------------------------------------------------------

