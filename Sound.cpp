//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "WinRDefs.h"
#include <Filectrl.hpp>
#include "Sound.h"
#include "wm_def.h"
#include "Sip.h"
#include "G711.h"
#include "SipClient_Unit.h"
#include "Test_Sound.h"
#include "D_FastFourieTransform_Odd.h"
#include "R_FastFourieTransform_Odd.h"
#include "R_FastFourieTransform_Even.h"
#include "Conference_Unit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
const double TWO__M_PI = 2*M_PI;
const double discr     = 0.000125;
const double d_697     = TWO__M_PI * discr * 697.0;
const double d_770     = TWO__M_PI * discr * 770.0;
const double d_852     = TWO__M_PI * discr * 852.0;
const double d_941     = TWO__M_PI * discr * 941.0;
const double d_1209    = TWO__M_PI * discr * 1209.0;
const double d_1336    = TWO__M_PI * discr * 1336.0;
const double d_1477    = TWO__M_PI * discr * 1477.0;
const double d_1633    = TWO__M_PI * discr * 1633.0;
//---------------------------------------------------------------------------
void __fastcall TWaveOutputThread::Execute()
{
try{
while(!Terminated)
     {
     if(DESTROY_REQUEST)    //for protect race conditions with WaveOutputStates (WOS) - MUST BE check first of all (first step) (after release hear alerting signal)
       {
     __clearBaseQueue();
       WAVE_OUT_RESET(WaveOutputState_DESTROY);
       Terminate();
       continue;
       }
     if(STATIC_WOS == WaveOutputState_REQUEST_TO_START_RECEIVING_VOICE) // for protect race conditions with WaveOutputStates (WOS) (second step) (sometimes not hear remote user)
        proc_request_to_start_receiving_voice();
     else
       {
       switch(WOS){
           case WaveOutputState_REQUEST_TO_START_ALERTING:
                proc_request_to_start_alerting();
                break;
           case WaveOutputState_REQUEST_TO_STOP_ALERTING:
                proc_request_to_stop_alerting();
                continue;
           case WaveOutputState_STOP_ALERTING: //Pause
                if(!proc_stop_alerting())
                  {
                  WOS = WaveOutputState_REQUEST_TO_START_ALERTING;
                  continue;
                  }
                break; //continue;
           case WaveOutputState_GEN_DTMF_DIGITS_START:
                proc_gen_dig_start();
                break;
           case WaveOutputState_GEN_DTMF_DIGITS_CONTINUE:   //Do not delete
                break;
           case WaveOutputState_GEN_DTMF_DIGITS_STOP:
                proc_gen_dig_stop();
                break;
          }
       }// if(STATIC_WOS == WaveOutputState_REQUEST_TO_START_RECEIVING_VOICE) else

     BaseExchangeBlock* bb = NULL;
     if(WOS == WaveOutputState_RECEIVING_VOICE)
       {
       if(JBD_State == JBD_State_Start)
         {
         int queue_sz = getQueueSize();
         if(queue_sz < JBD_Min)
           {
           bb = NULL;
           }
         else
           {
           JBD_State = JBD_State_Stable;
           bb = (BaseExchangeBlock*)getQueue();
           }
         }
       else
        {
         bb = get_Voice_Block_JBD_Stable_State();
        }
       }
     else
       bb = (BaseExchangeBlock*)getQueue();
     if(bb)
       {
       switch(bb->getBlockType()){
           case TWaveOutPutBuf_BLOCKTYPE:{
                TWaveOutPutBuf* wopb = (TWaveOutPutBuf*)bb;
                procTWaveOutPutBuf(wopb);
                delete wopb;  //!!!
                break;
                }
           case TOutPutUdpBlock_BLOCKTYPE:{
                TOutPutUdpBlock* opb = (TOutPutUdpBlock*)bb;
                if(opb->decompressed)
                  {
                  if(!opb->duplicated)
                     SNC.set_sn(opb->seq_num);
                  procTOutPutUdpBlock(&opb,-1);
                  }
                else
                  {
                  int size = opb->v.size();
                  if(size > 12)
                    {
                    int pdt = get_payload_type(opb->v[1]);
                    if(!opb->duplicated)
                       SNC.set_sn(get_seq_number(opb->v[2],opb->v[3]));
                    memcpy(&opb->v[0],&opb->v[12],size-12);
                    opb->v.resize(size-12);
                    procTOutPutUdpBlock(&opb,pdt);
                    }
                  }
                if(opb->queue_filler)
                  delete opb;
                else
                  {
                  if(opb->duplicated)
                    delete opb;
                  else
                    {
                    if(!opb->silence_suppr_queue)
                      {
                      if(opb->get_req_to_delete())
                        if(opb->getReferenceCount() == 1)
                          {
                          exsDeleteSentBlock(opb);  //deleted opb, чтобы не оставалось зависших TOutPutUdpBlock после отбоя
                          continue;                 // !!!
                          }
                      opb->decReferenceCount();
                      }
                    }
                  }
                break;
                }
           } //switch
       } //if(bb)
     else
       {
       if(is_whdr_empty())
         {
         if(WOS == WaveOutputState_START_ALERTING)
           {
            WOS = WaveOutputState_REQUEST_TO_STOP_ALERTING;
            continue;
           }
         if(WOS == WaveOutputState_RECEIVING_VOICE)
            Sleep(1);   //   Suspend_Thread();  //  "1.1.24_115"
         else
            Sleep(1);
         continue;
         }
         #ifdef RTP_whdr_Trace
         TEventLogThread* elt = *eltp;
         if(elt)
           if(elt->getlog())
              {
              string TimeStr;
              TDateTime DateTime = DateTime.CurrentDateTime();
              exsTime(DateTime,TimeStr);
              string str = "\n" + (string)TimeStr + " opb == NULL whdr.size = " + inttostr(get_whdr_size());
              elt->FputEvt(str);
              }
         #endif
       ::EnterCriticalSection(&whdr_cs);
         final_Unprepare_Out_Header();
       ::LeaveCriticalSection(&whdr_cs);
       ::Sleep(1);
       }//else
     }//while
 }//try
catch(Exception& e){exsSstEXCEPTION(*eltp,"__TWaveOutputThread::Execute",e);}
}
//----------------------------------------------------------------------------
BaseExchangeBlock* __fastcall TWaveOutputThread::get_Voice_Block_JBD_Stable_State()
{
return (BaseExchangeBlock*)getQueue();
/*
BaseExchangeBlock* bb = NULL;
if(Req_To_Miss_Packet_Count)
  {
  Req_To_Miss_Packet_Count--;
  }
else
 {
  int queue_sz = getQueueSize();
  if(queue_sz < JBD_Min)
     Req_To_Miss_Packet_Count = JBD_Min - queue_sz;
  bb = (BaseExchangeBlock*)getQueue();
 }
return bb;
*/
}
//------------------------------------------------------------------------------
void __fastcall TWaveBaseThread::get_max_val(vector<double>& y,int sz)
{
bool found = false;
double max = 0;
for(int i=0; i<sz; i++)
   {
    double a;
    if(y[i] < 0)
       a = -y[i];
    else
       a = y[i];
    if(a > 32767)
      if(a > max)
        {
         max = a;
         found = true;
        }
   }
if(found)
  {
  max = max/32767.0;
  for(int i=0; i<sz; i++)
     y[i] = y[i]/max;
  }
}
//------------------------------------------------------------------------------
void __fastcall TWaveBaseThread::double_2_short_low_pass(vector<short>& x,vector<double>& y,int sz,bool type)
{
x.clear();
for(int i=0; i<sz; i++)
   {
      if(y[i] > 32767.0)
        {
        //  y[i] = 32767.0;
        }
      if(y[i] < -32767.0)
        {
        //y[i] = -32767.0;
        }

  if(type)
    y[i] /= 10.0;

   round_up(y,i);
   x.push_back(y[i]);
   }
}
//------------------------------------------------------------------------------
void __fastcall TWaveBaseThread::save_previous( vector<short>& prev_x, vector<short>& x, vector<double>& y, int sz_x, int sz_y)
{
if(prev_x.size() != (unsigned)sz_x)
   prev_x.resize(sz_x,0);
memcpy(&prev_x[0],&x[0],sz_x*sizeof(short));
if(TTest_Sound->kih->Checked)
          return;
if(prev_y.size() != (unsigned)sz_y)
   prev_y.resize(sz_y,0.0);
memcpy(&prev_y[0],&y[0],sz_y*sizeof(double));
}
//------------------------------------------------------------------------------
void __fastcall TWaveBaseThread::filter_LPF_B(vector<short>& prev_x,vector<UBYTE>& v)
{  //Фильтр нижних частот

/*
int N = 3; //порядок фильтра
double b0 = 0.03047, b1 = 0.0914, b2 = 0.0914, b3 = 0.03047;
double a1 = -1.483, a2 = 0.9296, a3 = -0.2033;
double a0 = 0;
*/


 /*
int N = 3; //порядок фильтра
double b0 = 1.0, b1 = 3.0, b2 = 3.0, b3 = 1.0;
double a0 = 1.0, a1 = 2.9994917482444, a2 = 2.99898362563875, a3 = 0.999491877377947;
*/

/*
int N = 3; //порядок фильтра  Частота среза 1000 Hz
double b0 = 0.999745906407636, b1 = 2.99923771922291, b2 = 2.99923771922291, b3 = 0.999745906407636;
double a0 = 1.0, a1 = 2.9994917482444, a2 = 2.99898362563875, a3 = 0.999491877377947;
*/

/*
int N = 3; //порядок фильтра  Частота среза 1000 Hz
double b0 = 0.999218218372557, b1 = 2.99765465511767, b2 = 2.99765465511767, b3 = 0.999218218372557;
double a0 = 1.0, a1 = 2.99843582530834, a2 = 2.99687287372922, a3 = 0.998437047942903;
*/
/*
int N = 3; //порядок фильтра  Частота среза wp = 1 рад.с
double b0 = 0.0304692260816575, b1 = 0.0914076782449726, b2 = 0.0914076782449726, b3 = 0.0304692260816575;
double a0 = 1.0, a1 = -1.48251066422913, a2 = 0.929555149299208, a3 = -0.203290676416819;
*/

/*
int N = 3; //порядок фильтра  Частота среза wp = 2 рад.с
double b0 =  0.120055225403686, b1 = 0.360165676211057, b2 = 0.360165676211057, b3 = 0.120055225403686;
double a0 = 1.0, a1 = -0.374992496548412, a2 = 0.370550453208476, a3 = -0.0351161534305781;
*/

/*
int N = 3; //порядок фильтра  Частота среза wp = 4 рад.с
double b0 = 0.311054084528948, b1 = 0.933162253586842, b2 = 0.933162253586842, b3 = 0.311054084528948;
double a0 = 1.0, a1 = 0.864302655624247, a2 = 0.532563474474124, a3 = 0.0915665461332089;
*/
/*
int N = 3; //порядок фильтра  Частота среза wp = 4 рад.с
double b0 = 0.672584499470497, b1 = 2.01775349841149, b2 = 2.01775349841149, b3 = 0.672584499470497;
double a0 = 1.0, a1 = 2.21660741442439, a2 = 1.71172828679171, a3 = 0.452340294547872;
*/
/*
int N = 3; //порядок фильтра  Частота среза wp = 10 рад.с
double b0 = 0.614638727648663, b1 = 1.84391618294599, b2 = 1.84391618294599, b3 = 0.614638727648663;
double a0 = 1.0, a1 = 2.04438920891079, a2 = 1.49502019702859, a3 = 0.377700415249924;
*/

/*
int N = 3; //порядок фильтра  Частота среза wp = 100 рад.с
double b0 = 0.952052510585701, b1 = 2.8561575317571, b2 = 2.8561575317571, b3 = 0.952052510585701;
//double a0 = 1.0, a1 = 2.90174952139749, a2 = 2.80826652571415, a3 = 0.906404037573964;
double a0 = 1.0, a1 = 0.0, a2 = 0.0, a3 = 0.0;
*/

/*
int N = 3; //порядок фильтра  Частота среза wp = 1885 рад.с   (300 Hz)
double b0 = 0.997396499104091, b1 = 2.99218949731227, b2 = 2.99218949731227, b3 = 0.997396499104091;
//z_znam: 1 + 2,99478621098743*z^-1 + 2,9895860052511*z^-2 + 0,994799776594201*z^-3
double a0 = 1.0, a1 = 0.0, a2 = 0.0, a3 = 0.0;
*/
int N = 3; //порядок фильтра  Частота среза wp = 18850 рад.с   (300 Hz)
double b0 = 0.999739344321312, b1 = 2.99921803296394, b2 = 2.99921803296394, b3 = 0.999739344321312;
//z_znam: 1 + 2,99947862069069*z^-1 + 2,9989573772941*z^-2 + 0,999478756585705*z^-3
/*double a0 = 1.0,*/ double a1 = 0.0, a2 = 0.0, a3 = 0.0;


int sz = v.size();
if(sz)
  {
  vector<short> x; //отсчеты на входе фильтра
  vector<double> y; //отсчеты на выходе фильтра
  ubyte_2_short(x,v,sz);
  int sz_x = x.size();
  if(sz_x)
    {
    if(prev_x.empty())
      {
      prev_x.resize(sz_x,0);
     // prev_y.resize(sz_x,0.0);

          memcpy(&prev_x[0],&x[0],sz_x*sizeof(short));


      for(int i=0; i<sz_x; i++)
         //prev_y.push_back(x[i]);
          prev_y.push_back(0.0);
      return;
      }
    y.resize(sz_x,0.0);
    for(int i=0;i<sz_x;i++)
       {
       if(i < N)
         {
         int prev_x_sz = prev_x.size();
         int prev_y_sz = prev_y.size();
         switch(i){
                case 0: y[0] = b0*x[0] + b1*prev_x[prev_x_sz-1] + b2*prev_x[prev_x_sz-2] + b3*prev_x[prev_x_sz-3] -
                               a1*(short)prev_y[prev_y_sz-1] - a2*(short)prev_y[prev_y_sz-2] - a3*(short)prev_y[prev_y_sz-3];
                        break;
                case 1: y[1] = b0*x[1] + b1*x[0] + b2*prev_x[prev_x_sz-1] + b3*prev_x[prev_x_sz-2] -
                               a1*(short)y[0] - a2*(short)prev_y[prev_y_sz-1] - a3*(short)prev_y[prev_y_sz-2];
                        break;
                case 2: y[2] = b0*x[2] + b1*x[1] + b2*x[0] + b3*prev_x[prev_x_sz-1] -
                               a1*(short)y[1] - a2*(short)y[2] - a3*(short)prev_y[prev_y_sz-1];
                        break;
                }
         }
       else
         y[i] = b0*x[i] + b1*x[i-1] + b2*x[i-2] + b3*x[i-3] - a1*(short)y[i-1] - a2*(short)y[i-2] - a3*(short)y[i-3];
       }

    int sz_y = y.size();
    get_max_val(y,sz_y);
    save_previous(prev_x,x,y,sz_x,sz_y);
    double_2_short_low_pass(x,y,sz_y,false);
    short_2_ubyte(v,x,sz_y);
    }
  }
}
//----------------------------------------------------------------------------
void __fastcall TWaveBaseThread::filter_HPF_K(vector<short>& prev_x,vector<UBYTE>& v)
{  //Фильтр нижних частот
//int N = 3; //порядок фильтра
//double b0 = 0.03047, b1 = 0.0914, b2 = 0.0914, b3 = 0.03047;
//double a1 = -1.483, a2 = 0.9296, a3 = -0.2033;

//double b0 = 1.0, b1 = 0.522, b2 = 0.495, b3 = 0.34; //RC ФНЧ  T = 1,54
//double a1 = 0.0, a2 = 0.0, a3 = 0.0;

/*
int N = 5; //порядок фильтра.   частота среза 500 Hz
double b0 = 1.0, b1 = 2.99999773073327, b2 = 1.9999977307344, b3 = -1.9999977307344, b4 = -2.99999773073327, b5 = -1.0;
double a0 = 1.0, a1 = 4.9994102719464,  a2 = 9.99764182353253,a3 = 9.99646383863602, a4 = 4.99764329446018, a5 = 0.999411007410282;
*/

/*
int N = 5; //порядок фильтра.   частота среза 300 Hz
//double b0 = 1.0, b1 = 2.99999369648488, b2 = 1.99999369649359, b3 = -1.99999369649359, b4 = -2.99999369648488, b5 = -1.0;
//double a0 = 1.0, a1 = 4.99901649567048, a2 = 9.99606802680828, a3 = 9.99410510509043, a4 = 4.99607211243889, a5 = 0.999018538486264;

double b0 = 1.57698342874641E-5, b1 = 4.73094034570035E-5, b2 = 3.15395691696766E-5, b3 = -3.15395691696766E-5, b4 = -4.73094034570035E-5, b5 = -1.57698342874641E-5;
double a0 = 1.0, a1 = 4.99901649567048, a2 = 9.99606802680828, a3 = 9.99410510509043, a4 = 4.99607211243889, a5 = 0.999018538486264;
*/


int N = 5; //порядок фильтра.   частота среза 100 Hz
//double b0 = 1.0, b1 = 2.9999432687659,  b2 = 1.99994326947077, b3 = -1.99994326947077, b4 = -2.9999432687659, b5 = -1.0;
//double a0 = 1.0, a1 = 4.99704012754008, a2 = 9.98817892461091, a3 =  9.98229597311419, a4 = 4.98821568263266, a5 = 0.997058506589236;

double b0 = 4.72635187464217E-5, b1 = 0.000141787874921519, b2 = 9.45243562084115E-5, b3 = -9.45243562084115E-5, b4 = -0.000141787874921519, b5 = -4.72635187464217E-5;
/* double a0 = 1.0, */ double a1 = 4.99704012754008, a2 = 9.98817892461091, a3 = 9.98229597311419, a4 = 4.98821568263266, a5 = 0.997058506589236;
//double a0 = 1.0, a1 = 0, a2 = 0, a3 = 0, a4 = 0, a5 = 0;

//z_chsl:  + 4,72635187464217E-5 + 0,000141787874921519*z^-1 + 9,45243562084115E-5*z^-2 - 9,45243562084115E-5*z^-3 - 0,000141787874921519*z^-4 - 4,72635187464217E-5*z^-5
//z_znam: 1 + 4,99704012754008*z^-1 + 9,98817892461091*z^-2 + 9,98229597311419*z^-3 + 4,98821568263266*z^-4 + 0,997058506589236*z^-5


//double b0 = 4635179927.42717, b1 = 13905276822.8039, b2 = 9270096898.64396, b3 = -9270096898.64396, b4 = -13905276822.8039, b5 = -4635179927.42717;
//double a0 = 98070986891514.3, a1 = 490064656844354, a2 = 979550564385616, a3 = 978973617526498, a4 = 489199234823513, a5 = 97782511729785.9;



/*
int N = 5; //порядок фильтра.   частота среза 50 Hz
double b0 = 1.0, b1 = 2.99977308048952, b2 = 1.99977309176696, b3 =  -1.99977309176696, b4 = -2.99977308048952, b5 = -1.0;
double a0 = 1.0, a1 = 4.99405220265361, a2 = 9.97628257224354, a3 = 9.96453421617818, a4 = 4.97642952746833, a5 = 0.994125680877955;
*/

/*
int N = 5; //порядок фильтра.   частота среза 10 Hz
double b0 = 0.000466904488406115, b1 = 0.0013980667467499, b2 = 0.000931165544798256, b3 = -0.000931165544798256, b4 = -0.0013980667467499, b5 = -0.000466904488406115;
double a0 = 1.0, a1 = 4.6914472197186, a2 = 9.87844362773231, a3 = 9.8204261772171, a4 = 4.88210113062535, a5 = 0.97097385259579;
*/

//double b0 = 1.0, b1 = 2.99433134927128, b2 = 1.99433838808661, b3 = -1.99433838808661, b4 = -2.99433134927128, b5 = -1.0;
//double a0 = 1.0, a1 = 4.96914472197186, a2 = 9.87844362773231, a3 = 9.8204261772171, a4 = 4.88210113062535, a5 = 0.97097385259579;



int sz = v.size();
if(sz)
  {
  vector<short> x; //отсчеты на входе фильтра
  vector<double> y; //отсчеты на выходе фильтра
  ubyte_2_short(x,v,sz);
  int sz_x = x.size();
  if(sz_x)
    {
    if(prev_x.empty())
      {
      prev_x.resize(sz_x,0);
     // prev_y.resize(sz_x,0.0);
      memcpy(&prev_x[0],&x[0],sz_x*sizeof(short));
      for(int i=0; i<sz_x; i++)
       //prev_y.push_back((double)x[i]);
        prev_y.push_back(0.0);
      return;
      }
    y.resize(sz_x,0.0);
    for(int i=0;i<sz_x;i++)
       {
       if(i < N)
         {
         int prev_x_sz = prev_x.size();
         int prev_y_sz = prev_y.size();
         switch(i){
                case 0: y[0] = b0*x[0] + b1*(short)prev_x[prev_x_sz-1] + b2*(short)prev_x[prev_x_sz-2] + b3*(short)prev_x[prev_x_sz-3] +
                               b4*(short)prev_x[prev_x_sz-4] + b5*(short)prev_x[prev_x_sz-5];
                               if(TTest_Sound->kih->Checked)
                                  break;
                              /* a0*y[0] - */y[0] -=  a1*(short)prev_y[prev_y_sz-1] - a2*(short)prev_y[prev_y_sz-2] - a3*(short)prev_y[prev_y_sz-3] -
                               a4*(short)prev_y[prev_y_sz-4] - a5*(short)prev_y[prev_y_sz-5];
                        break;
                case 1: y[1] = b0*x[1] + b1*x[0] + b2*(short)prev_x[prev_x_sz-1] + b3*(short)prev_x[prev_x_sz-2] +
                               b4*(short)prev_x[prev_x_sz-3] + b5*(short)prev_x[prev_x_sz-4];
                               if(TTest_Sound->kih->Checked)
                                  break;
                               /*a0*y[1] - */y[1] -= a1*(short)y[0] - a2*(short)prev_y[prev_y_sz-1] - a3*(short)prev_y[prev_y_sz-2] -
                               a4*(short)prev_y[prev_y_sz-3] - a5*(short)prev_y[prev_y_sz-4];
                        break;
                case 2: y[2] = b0*x[2] + b1*x[1] + b2*x[0] + b3*(short)prev_x[prev_x_sz-1] +
                               b4*(short)prev_x[prev_x_sz-2] + b5*(short)prev_x[prev_x_sz-3];
                               if(TTest_Sound->kih->Checked)
                                  break;
                               /*a0*y[2] -*/y[2] -= a1*(short)y[1] - a2*(short)y[0] - a3*(short)prev_y[prev_y_sz-1] -
                               a4*(short)prev_y[prev_y_sz-2] - a5*(short)prev_y[prev_y_sz-3];
                        break;
                case 3: y[3] = b0*x[3] + b1*x[2] + b2*x[1] + b3*x[0] + b4*(short)prev_x[prev_x_sz-1] + b5*(short)prev_x[prev_x_sz-2];
                               if(TTest_Sound->kih->Checked)
                                  break;
                              /* a0*y[3] -*/y[3] -= a1*(short)y[2] - a2*(short)y[1] - a3*(short)y[0] - a4*(short)prev_y[prev_y_sz-1] - a5*(short)prev_y[prev_y_sz-2];
                        break;
                case 4: y[4] = b0*x[4] + b1*x[3] + b2*x[2] + b3*x[1] + b4*x[0] + b5*(short)prev_x[prev_x_sz-1];
                               if(TTest_Sound->kih->Checked)
                                  break;
                              /*a0*y[4] - */y[4] -= a1*(short)y[3] - a2*(short)y[2] - a3*(short)y[1] - a4*(short)y[0] - a5*(short)prev_y[prev_y_sz-1];
                        break;
                }
         }
       else
         {
            y[i] = b0 * x[i] + b1*x[i-1] + b2*x[i-2] + b3*x[i-3] + b4*x[i-4] + b5*x[i-5];
            if(TTest_Sound->kih->Checked)
               continue;
            y[i] -= a1*(short)y[i-1] - a2*(short)y[i-2] - a3*(short)y[i-3] - a4*(short)y[i-4] - a5*(short)y[i-5];
         }
       }

    int sz_y = y.size();
  //  bool exceed = false;
    for(int i=0;i<sz_y;i++)
       {
       if(abs(y[i]) > 16000)
         {
        // exceed = true;
         break;
         }
       }
  //  get_max_val(y,sz_y);
  /*
    if(exceed)
      {
      prev_y.clear();
      for(int i=0; i<sz_y; i++)
          prev_y.push_back(0.0);
       for(int i=0; i<sz_y; i++)
           y[i]*= 0.01;
      for(int i=0; i<sz_y; i++)
           if(abs(y[i]) > 16000)
             {
             int a = 5;
             }
      }
    else  */

    save_previous(prev_x,x,y,sz_x,sz_y);

    double_2_short(x,y,sz_y,true);
    short_2_ubyte(v,x,sz_y);
    }
  }
}
//----------------------------------------------------------------------------
void __fastcall TWaveBaseThread::filter_HPF_K_1(vector<short>& prev_x,vector<UBYTE>& v)
{
//int N = 3; //порядок фильтра
//double b0 = 0.03047, b1 = 0.0914, b2 = 0.0914, b3 = 0.03047;
//double a1 = -1.483, a2 = 0.9296, a3 = -0.2033;

//double b0 = 1.0, b1 = 0.522, b2 = 0.495, b3 = 0.34; //RC ФНЧ  T = 1,54
//double a1 = 0.0, a2 = 0.0, a3 = 0.0;

/*
int N = 5; //порядок фильтра.   частота среза 500 Hz
double b0 = 1.0, b1 = 2.99999773073327, b2 = 1.9999977307344, b3 = -1.9999977307344, b4 = -2.99999773073327, b5 = -1.0;
double a0 = 1.0, a1 = 4.9994102719464,  a2 = 9.99764182353253,a3 = 9.99646383863602, a4 = 4.99764329446018, a5 = 0.999411007410282;
*/

/*
int N = 5; //порядок фильтра.   частота среза 300 Hz
//double b0 = 1.0, b1 = 2.99999369648488, b2 = 1.99999369649359, b3 = -1.99999369649359, b4 = -2.99999369648488, b5 = -1.0;
//double a0 = 1.0, a1 = 4.99901649567048, a2 = 9.99606802680828, a3 = 9.99410510509043, a4 = 4.99607211243889, a5 = 0.999018538486264;

double b0 = 1.57698342874641E-5, b1 = 4.73094034570035E-5, b2 = 3.15395691696766E-5, b3 = -3.15395691696766E-5, b4 = -4.73094034570035E-5, b5 = -1.57698342874641E-5;
double a0 = 1.0, a1 = 4.99901649567048, a2 = 9.99606802680828, a3 = 9.99410510509043, a4 = 4.99607211243889, a5 = 0.999018538486264;
*/


//int N = 5; //порядок фильтра.   частота среза 100 Hz
//double b0 = 1.0, b1 = 2.9999432687659,  b2 = 1.99994326947077, b3 = -1.99994326947077, b4 = -2.9999432687659, b5 = -1.0;
//double a0 = 1.0, a1 = 4.99704012754008, a2 = 9.98817892461091, a3 =  9.98229597311419, a4 = 4.98821568263266, a5 = 0.997058506589236;

double b0 = 4.72635187464217E-5, b1 = 0.000141787874921519, b2 = 9.45243562084115E-5, b3 = -9.45243562084115E-5, b4 = -0.000141787874921519, b5 = -4.72635187464217E-5;
//double a0 = 1.0, a1 = 4.99704012754008, a2 = 9.98817892461091, a3 = 9.98229597311419, a4 = 4.98821568263266, a5 = 0.997058506589236;
/*double a0 = 1.0,*/ double a1 = 0, a2 = 0, a3 = 0, a4 = 0, a5 = 0;

//z_chsl:  + 4,72635187464217E-5 + 0,000141787874921519*z^-1 + 9,45243562084115E-5*z^-2 - 9,45243562084115E-5*z^-3 - 0,000141787874921519*z^-4 - 4,72635187464217E-5*z^-5
//z_znam: 1 + 4,99704012754008*z^-1 + 9,98817892461091*z^-2 + 9,98229597311419*z^-3 + 4,98821568263266*z^-4 + 0,997058506589236*z^-5


//double b0 = 4635179927.42717, b1 = 13905276822.8039, b2 = 9270096898.64396, b3 = -9270096898.64396, b4 = -13905276822.8039, b5 = -4635179927.42717;
//double a0 = 98070986891514.3, a1 = 490064656844354, a2 = 979550564385616, a3 = 978973617526498, a4 = 489199234823513, a5 = 97782511729785.9;



/*
int N = 5; //порядок фильтра.   частота среза 50 Hz
double b0 = 1.0, b1 = 2.99977308048952, b2 = 1.99977309176696, b3 =  -1.99977309176696, b4 = -2.99977308048952, b5 = -1.0;
double a0 = 1.0, a1 = 4.99405220265361, a2 = 9.97628257224354, a3 = 9.96453421617818, a4 = 4.97642952746833, a5 = 0.994125680877955;
*/

/*
int N = 5; //порядок фильтра.   частота среза 10 Hz
double b0 = 0.000466904488406115, b1 = 0.0013980667467499, b2 = 0.000931165544798256, b3 = -0.000931165544798256, b4 = -0.0013980667467499, b5 = -0.000466904488406115;
double a0 = 1.0, a1 = 4.6914472197186, a2 = 9.87844362773231, a3 = 9.8204261772171, a4 = 4.88210113062535, a5 = 0.97097385259579;
*/

//double b0 = 1.0, b1 = 2.99433134927128, b2 = 1.99433838808661, b3 = -1.99433838808661, b4 = -2.99433134927128, b5 = -1.0;
//double a0 = 1.0, a1 = 4.96914472197186, a2 = 9.87844362773231, a3 = 9.8204261772171, a4 = 4.88210113062535, a5 = 0.97097385259579;



int sz = v.size();
if(sz)
  {
  vector<short> x; //отсчеты на входе фильтра
  vector<double> y; //отсчеты на выходе фильтра
  ubyte_2_short(x,v,sz);
  int sz_x = x.size();
  if(sz_x)
    {
    if(prev_x.empty())
      {
      prev_x.resize(sz_x,0);
     // prev_y.resize(sz_x,0.0);
      memcpy(&prev_x[0],&x[0],sz_x*sizeof(short));
      for(int i=0; i<sz_x; i++)
       //prev_y.push_back((double)x[i]);
        prev_y.push_back(0.0);
      return;
      }
    y.resize(sz_x,0.0);

    int prev_x_sz = prev_x.size();
    for(int i=0;i<prev_x_sz;i++)
       x.push_back(prev_x[i]);
    int prev_y_sz = prev_y.size();
    for(int i=0;i<prev_y_sz;i++)
       y.push_back(prev_y[i]);
    for(int i=0;i<sz_x;i++)
       {
       /*
       if(i < N)
         {
        // int prev_x_sz = prev_x.size();
         int prev_y_sz = prev_y.size();
         switch(i){
                case 0: y[0] = b0*x[0] + b1*(short)prev_x[prev_x_sz-1] + b2*(short)prev_x[prev_x_sz-2] + b3*(short)prev_x[prev_x_sz-3] +
                               b4*(short)prev_x[prev_x_sz-4] + b5*(short)prev_x[prev_x_sz-5];
                               if(TTest_Sound->kih->Checked)
                                  break;
                               y[0] -=  a1*(short)prev_y[prev_y_sz-1] - a2*(short)prev_y[prev_y_sz-2] - a3*(short)prev_y[prev_y_sz-3] -
                               a4*(short)prev_y[prev_y_sz-4] - a5*(short)prev_y[prev_y_sz-5];
                        break;
                case 1: y[1] = b0*x[1] + b1*x[0] + b2*(short)prev_x[prev_x_sz-1] + b3*(short)prev_x[prev_x_sz-2] +
                               b4*(short)prev_x[prev_x_sz-3] + b5*(short)prev_x[prev_x_sz-4];
                               if(TTest_Sound->kih->Checked)
                                  break;
                               y[1] -= a1*(short)y[0] - a2*(short)prev_y[prev_y_sz-1] - a3*(short)prev_y[prev_y_sz-2] -
                               a4*(short)prev_y[prev_y_sz-3] - a5*(short)prev_y[prev_y_sz-4];
                        break;
                case 2: y[2] = b0*x[2] + b1*x[1] + b2*x[0] + b3*(short)prev_x[prev_x_sz-1] +
                               b4*(short)prev_x[prev_x_sz-2] + b5*(short)prev_x[prev_x_sz-3];
                               if(TTest_Sound->kih->Checked)
                                  break;
                               y[2] -= a1*(short)y[1] - a2*(short)y[0] - a3*(short)prev_y[prev_y_sz-1] -
                               a4*(short)prev_y[prev_y_sz-2] - a5*(short)prev_y[prev_y_sz-3];
                        break;
                case 3: y[3] = b0*x[3] + b1*x[2] + b2*x[1] + b3*x[0] + b4*(short)prev_x[prev_x_sz-1] + b5*(short)prev_x[prev_x_sz-2];
                               if(TTest_Sound->kih->Checked)
                                  break;
                              y[3] -= a1*(short)y[2] - a2*(short)y[1] - a3*(short)y[0] - a4*(short)prev_y[prev_y_sz-1] - a5*(short)prev_y[prev_y_sz-2];
                        break;
                case 4: y[4] = b0*x[4] + b1*x[3] + b2*x[2] + b3*x[1] + b4*x[0] + b5*(short)prev_x[prev_x_sz-1];
                               if(TTest_Sound->kih->Checked)
                                  break;
                              y[4] -= a1*(short)y[3] - a2*(short)y[2] - a3*(short)y[1] - a4*(short)y[0] - a5*(short)prev_y[prev_y_sz-1];
                        break;
                }
         }
       else
         {  */
            y[i] = b0 * x[i] + b1*x[i+1] + b2*x[i+2] + b3*x[i+3] + b4*x[i+4] + b5*x[i+5];
            if(TTest_Sound->kih->Checked)
               continue;
            y[i] -= a1*(short)y[i+1] - a2*(short)y[i+2] - a3*(short)y[i+3] - a4*(short)y[i+4] - a5*(short)y[i+5];
    //      }
       }

    x.resize(sz_x);
    y.resize(sz_x);
    int sz_y = y.size();
  //  bool exceed = false;
    for(int i=0;i<sz_y;i++)
       {
       if(abs(y[i]) > 16000)
         {
        // exceed = true;
         break;
         }
       }
  //  get_max_val(y,sz_y);
  /*
    if(exceed)
      {
      prev_y.clear();
      for(int i=0; i<sz_y; i++)
          prev_y.push_back(0.0);
       for(int i=0; i<sz_y; i++)
           y[i]*= 0.01;
      for(int i=0; i<sz_y; i++)
           if(abs(y[i]) > 16000)
             {
             int a = 5;
             }
      }
    else  */

    save_previous(prev_x,x,y,sz_x,sz_y);

    double_2_short(x,y,sz_y,true);
    short_2_ubyte(v,x,sz_y);
    }
  }
}
//------------------------------------------------------------------------------
void __fastcall TWaveBaseThread::filter_HPF_FIRST_ORDER(vector<short>& prev_x,vector<UBYTE>& v)
{
double b0 = 0.0;
double b1 = 0.730854;
double b2 = 0.92756;
double b3 = 0.980503;
double b4 = 0.994752;
double b5 = 0.998588;
double b6 = 0.99962;
double b7 = 0.999898;
double b8  = 0.999972;
double b9  = 0.999973;
double b10 = 0.999998;
double b11 = 0.999999;


int sz = v.size();
if(sz)
  {
  vector<short> x; //отсчеты на входе фильтра
  vector<double> y; //отсчеты на выходе фильтра
  ubyte_2_short(x,v,sz);
  int sz_x = x.size();
  if(sz_x)
    {
    if(prev_x.empty())
      {
      prev_x.resize(sz_x,0);
     // prev_y.resize(sz_x,0.0);
      memcpy(&prev_x[0],&x[0],sz_x*sizeof(short));
      for(int i=0; i<sz_x; i++)
       //prev_y.push_back((double)x[i]);
        prev_y.push_back(0.0);
      return;
      }
    y.resize(sz_x,0.0);


    vector<short> xx;


    int prev_x_sz = prev_x.size();
    for(int i=0;i<prev_x_sz;i++)
        xx.push_back(prev_x[i]);
    for(int i=0;i<sz_x;i++)
        xx.push_back(x[i]);

    int prev_y_sz = prev_y.size();
    for(int i=0;i<prev_y_sz;i++)
       y.push_back(prev_y[i]);



    for(int i=0;i<sz_x;i++)
       {
       y[i] = b0 *(xx[prev_x_sz + i]  - xx[prev_x_sz + i-1]) +
              b1*(xx[prev_x_sz + i-1] - xx[prev_x_sz + i-2]) +
              b2*(xx[prev_x_sz + i-2] - xx[prev_x_sz + i-3]) +
              b3*(xx[prev_x_sz + i-3] - xx[prev_x_sz + i-4]) +
              b4*(xx[prev_x_sz + i-4] - xx[prev_x_sz + i-5]) +
              b5*(xx[prev_x_sz + i-5] - xx[prev_x_sz + i-6]) +
              b6*(xx[prev_x_sz + i-6] - xx[prev_x_sz + i-7]) +
              b7*(xx[prev_x_sz + i-7] - xx[prev_x_sz + i-8]) +
              b8*(xx[prev_x_sz + i-8] - xx[prev_x_sz + i-9]) +
              b9*(xx[prev_x_sz + i-9] - xx[prev_x_sz + i-10]) +
              b10*(xx[prev_x_sz + i-10] - xx[prev_x_sz + i-11]) +
              b11*(xx[prev_x_sz + i-11] - xx[prev_x_sz + i-12]);
       for(int j = 12;j < sz_x;j++ )
           y[i] += (double)xx[prev_x_sz + i - j] - (double)xx[prev_x_sz + i - (j+1)];
       y[i]/= 10000;
       }

   // x.resize(sz_x);
   // y.resize(sz_x);
    int sz_y = y.size();
  //  bool exceed = false;
    for(int i=0;i<sz_y;i++)
       {
       if(abs(y[i]) > 16000)
         {
     //    exceed = true;
         break;
         }
       }

    save_previous(prev_x,x,y,sz_x,sz_y);

    double_2_short(x,y,sz_y,true);
    short_2_ubyte(v,x,sz_y);
    }
  }
}
//------------------------------------------------------------------------------
void __fastcall TWaveBaseThread::filter_LPF_K(vector<short>& prev_x,vector<UBYTE>& v)
{
/*
int N = 5; //порядок фильтра.   частота среза 4000 Hz
double b0 = 1.0, b1 = 3.99999999483594, b2 = 5.99999998967189, b3 = 3.99999999483594, b4 = 1.0;
double a0 = 1.0, a1 = 4.99970902444577, a2 = 9.99883613180181, a3 = 9.99825424872634, a4 = 4.99883619983032, a5 = 0.999709058460023;
*/

/*
int N = 5; //порядок фильтра.   частота среза 4000 Hz
double b0 = 1.0, b1 = 1.50871948148336, b2 = 1.01743896296672, b3 = 0.67829264226971, b4 = 0.169573160786349;
double a0 = 1.0, a1 = 4.99970902444577, a2 = 9.99883613180181, a3 = 9.99825424872634, a4 = 4.99883619983032, a5 = 0.999709058460023;
*/


int N = 5; //порядок фильтра.   частота среза 4000 Hz
double b0 = 1.0, b1 = 4.99999999483594, b2 = 9.99999998450783, b3 = 9.99999998450783, b4 = 4.99999999483594, b5 = 1.0;
double a0 = 1.0, a1 = 4.99970902444577, a2 = 9.99883613180181, a3 = 9.99825424872634, a4 = 4.99883619983032, a5 = 0.999709058460023;


/*
int N = 5; //порядок фильтра.   частота среза 1000 Hz
double b0 = 1.0, b1 = 4.99999991737511, b2 = 9.99999975212532, b3 = 9.99999975212532, b4 = 4.99999991737511, b5 = 1.0;
double a0 = 1.0, a1 = 4.9988361974836,  a2 = 9.99534533431894, a3 = 9.99301881776867, a4 = 4.99534642251494, a5 = 0.998836741581622;
*/

/*
int N = 5; //порядок фильтра.   частота среза 500 Hz
double b0 = 1.0, b1 = 4.99999966950044, b2 = 9.99999900850134, b3 = 9.99999900850132, b4 = 4.99999966950044, b5 = 0.999999999999999;
double a0 = 1.0, a1 = 4.9976726603669,  a2 = 9.9906928194578, a3 = 9.98604249388003, a4 = 4.99069717085501, a5 = 0.997674836065878;
*/

int sz = v.size();
if(sz)
  {
  vector<short> x; //отсчеты на входе фильтра
  vector<double> y; //отсчеты на выходе фильтра
  ubyte_2_short(x,v,sz);
  int sz_x = x.size();
  if(sz_x)
    {
    if(prev_x.empty())
      {
      prev_x.resize(sz_x,0);
      prev_y.resize(sz_x,0.0);
      memcpy(&prev_x[0],&x[0],sz_x*sizeof(short));
      for(int i=0; i<sz_x; i++)
         prev_y.push_back(x[i]);
      return;
      }
    y.resize(sz_x,0.0);
    for(int i=0;i<sz_x;i++)
       {
       if(i < N)
         {
         int prev_x_sz = prev_x.size();
         int prev_y_sz = prev_y.size();
         switch(i){
                case 0: y[0] = b0*x[0] + b1*prev_x[prev_x_sz-1] + b2*prev_x[prev_x_sz-2] + b3*prev_x[prev_x_sz-3] +
                               b4*prev_x[prev_x_sz-4] + b5*prev_x[prev_x_sz-5] -
                               a0*y[0] - a1*prev_y[prev_y_sz-1] - a2*prev_y[prev_y_sz-2] - a3*prev_y[prev_y_sz-3] -
                               a4*prev_y[prev_y_sz-4] - a5*prev_y[prev_y_sz-5];
                        break;
                case 1: y[1] = b0*x[1] + b1*x[0] + b2*prev_x[prev_x_sz-1] + b3*prev_x[prev_x_sz-2] +
                               b4*prev_x[prev_x_sz-3] + b5*prev_x[prev_x_sz-4] -
                               a0*y[1] - a1*y[0] - a2*prev_y[prev_y_sz-1] - a3*prev_y[prev_y_sz-2] -
                               a4*prev_y[prev_y_sz-3] - a5*prev_y[prev_y_sz-4];
                        break;
                case 2: y[2] = b0*x[2] + b1*x[1] + b2*x[0] + b3*prev_x[prev_x_sz-1] +
                               b4*prev_x[prev_x_sz-2] + b5*prev_x[prev_x_sz-3] -
                               a0*y[2] - a1*y[1] - a2*y[0] - a3*prev_y[prev_y_sz-1] -
                               a4*prev_y[prev_y_sz-2] - a5*prev_y[prev_y_sz-3];
                        break;
                case 3: y[3] = b0*x[3] + b1*x[2] + b2*x[1] + b3*x[0] + b4*prev_x[prev_x_sz-1] + b5*prev_x[prev_x_sz-2] -
                               a0*y[3] - a1*y[2] - a2*y[1] - a3*y[0] - a4*prev_y[prev_y_sz-1] - a5*prev_y[prev_y_sz-2];
                        break;
                case 4: y[4] = b0*x[4] + b1*x[3] + b2*x[2] + b3*x[1] + b4*x[0] + b5*prev_x[prev_x_sz-1] -
                               a0*y[4] - a1*y[3] - a2*y[2] - a3*y[1] - a4*y[0] - a5*prev_y[prev_y_sz-1];
                        break;
                }
         }
       else
         {
         y[i] = b0*x[i] + b1*x[i-1] + b2*x[i-2] + b3*x[i-3] + b4*x[i-4] + b5*x[i-5] -
                a0*y[i] - a1*y[i-1] - a2*y[i-2] - a3*y[i-3] - a4*y[i-4] - a5*y[i-5];
         }
       }

    int sz_y = y.size();
    save_previous(prev_x,x,y,sz_x,sz_y);
    double_2_short(x,y,sz_y,false);
    short_2_ubyte(v,x,sz_y);
    }
  }
}
//----------------------------------------------------------------------------
void __fastcall TWaveBaseThread::display_on_prog_bar(vector<short>& xv,queue<XBYTE>& xyz,TProgressBar* prog_bar)
{
unsigned sum = 0;
int xsz = xv.size();
if(xsz != 0)
  {
  for(int i=0;i<xsz;i++)
     sum += xv[i];
  sum = sum/xsz;
  if(SoundTool->Visible)
    {
    int sz_xyz = xyz.size();
    if(sz_xyz > 4)
      {
      unsigned SUM = 0;
      for(int i=0;i<sz_xyz;i++)
         {
         SUM += xyz.front();
         xyz.pop();
         }
      SUM = SUM/sz_xyz;
      prog_bar->Position = SUM;
      }
    else
      xyz.push(sum);
    }
  }
else
  prog_bar->Position = 0;
}
//---------------------------------------------------------------------------
void __fastcall TWaveBaseThread::get_sound_average_volume(const vector<UBYTE>& v,queue<XBYTE>& xyz,TProgressBar* prog_bar)
{
int sz = v.size();
if(sz)
  {
  vector<short> xv;
  for(int i=0;i<sz;i+=2)
     {
     if(i+1 < sz)
       {
       short a = v[i];    //LSB
       a |= v[i+1] << 8;  //MSB with sign
       xv.push_back(abs(a));
       }
     }
  display_on_prog_bar(xv,xyz,prog_bar);
  }
}
//------------------------------------------------------------------------------
void __fastcall TCaptureDSPThread::Execute()
{
while(!Terminated)
     {
    (*MainFormSLS->AecDll.pFunc_CaptureDSP)(AEC,ES);
     ProcComplete = true;
     Sleep(100);  //чтобы не было фальшивых циклов после выхода. Inside pFunc_CaptureDSP additional protection if(AEC->TerminateReq){Sleep(100); return false;}
     }
}
//-----------------------------------------------------------------------------
TOutPutUdpBlock* __fastcall TWaveInputThread::ProDspData(TAExchBuf* cc,int& i)
{
if(i >= (int)cc->n)
  return NULL; //Exit from cyrcle
int n = cc->n - i;
if(cc->n)
  {
  if(__OPB) //буфер, ожидающий дополнительные байты
    {
    if(n >= 160)
      {
      memcpy(&__OPB->v[160], &cc->buf[i], 160);
      TOutPutUdpBlock* opb = __OPB;
    __OPB = NULL;
      i  += 160;
      return opb;
      }
    }  //if(OPB)
   else
    {
    if(n == 160)
      {
      TOutPutUdpBlock* opb = new TOutPutUdpBlock;
      opb->v.resize(320,0);
      memcpy(&opb->v[0], &cc->buf[i], 160);
    __OPB = opb;            //Wait for additional 160 bytes
      return NULL;
      }
    if(n >= 320)
      {
      TOutPutUdpBlock* opb = new TOutPutUdpBlock;
      opb->v.resize(320,0);
      memcpy(&opb->v[0], &cc->buf[i], 320);
      i += 320;
      return opb;
      }
    }  // else
  }  // if(cc->n)


TEventLogThread* elt = getLog();
if(elt)
  {
  string s = "\nERROR: TWaveInputThread::ProDspData(): PacketLength = " + inttostr(cc->n) + "\n";
  elt->FputEvt(s);
  }
return NULL;
}
//-----------------------------------------------------------------------------
#ifdef Log_Capture_DSP
void __fastcall TWaveInputThread::LogCaptureDsp(TAExchBuf* cc)
{
TDateTime DateTime = DateTime.CurrentDateTime();
string s;
exsTime(DateTime,s);
s = "\n" + s + " TWaveInputThread::Execute(): GetAudioPacket() from CaptureDSP " + inttostr(cc->n) + " byte\n";
//int PART_SUM  = 0;
short EL = 0;
for(unsigned i = 0; i < cc->n; i++)
   {
   if(i & 1)
     {
     EL |= cc->buf[i] << 8;
     //PART_SUM += abs(EL);
     AVERAGE_BY_SEC += abs(EL);
     BYTE_CNT_BY_SEC++;
     EL = 0;
     }
   else
     {
     EL = cc->buf[i];
     EL &= 0xFF;
     }

   if(i)
     s += " ";
   s += inttohexstr(cc->buf[i],2);

   }
//s += "\nSUM = " + inttostr(PART_SUM);
//int PART_AV = PART_SUM/cc->n;

//s += " AVERAGE = "  + inttostr(PART_AV);
s += "\n";

//BYTE_CNT_BY_SEC += cc->n;
//AVERAGE_BY_SEC  += PART_AV;
if(BYTE_CNT_BY_SEC >= 3999) //7999 - sec 3999 - half_sec
  {
  TEventLogThread* elt = getLog();
  if(elt)
    {
    string av_by_sec = "\nAV_LEVEL_BY_H_SEC: " + inttostr(AVERAGE_BY_SEC/BYTE_CNT_BY_SEC) + "\n";
    elt->FputEvt(av_by_sec,1);
    }
  BYTE_CNT_BY_SEC = 0;
  AVERAGE_BY_SEC  = 0;
  }

//if(PART_AV > 200)
//  {
  TEventLogThread* elt = getLog();
  if(elt)elt->FputEvt(s);
//  }

}
#endif
//-----------------------------------------------------------------------------
bool __fastcall TMicPause::check_mic_supply_interval(TWaveInputThread* wit)
{
bool rv = false;
TEventLogThread* elt = wit->getLog();
if(elt)
  {
  TDateTime CurrDateTime = CurrDateTime.CurrentDateTime();
  TDateTime dt_diff      = CurrDateTime - __time_of_last_rcvd_mic_packet;
  if(dt_diff > __critical_interval)
    {
     rv = true;
     if((CurrDateTime - __time_of_last_log_writing) > __writing_interval)
       {
       string s;
       exsTime(CurrDateTime, s);
       s = "\n" + s + " ch_" + inttostr(wit->getUc()->getChId()) + " mic not supplies packets with interval ";
       string dt;
       exsTime(dt_diff, dt);
       s += dt + "\n";
       elt->FputEvt(s);
     __time_of_last_log_writing = CurrDateTime;
       }
    }
  }
return rv;  
}
//-----------------------------------------------------------------------------
void __fastcall TWaveInputThread::Execute()
{
try{
__start_thread_time = __start_thread_time.CurrentDateTime();
MP.set_time_of_last_rcvd_packt();
TEventLogThread* elt = getLog();
if(elt)
  {
   string s;
   exsTime(__start_thread_time, s);
   s = "\n" + s + " ch_" + inttostr(Uc->getChId()) + " TWaveInputThread: started\n";
   elt->FputEvt(s);
  }
if(MainFormSLS->AecDll.Initiated) //!!! Use DSPCapture
  {
  void* exch_struct = (*MainFormSLS->AecDll.pFunc_CreateExchStruct)();
  TCaptureDSPThread* CDSPT = new TCaptureDSPThread(true, &AEC, exch_struct);
  if(CDSPT)
    {
    CDSPT->Resume();
    if(elt)
      {
      TDateTime DateTime = DateTime.CurrentDateTime();
      string s;
      exsTime(DateTime,s);
      s = "\n" + s + " ch_" + inttostr(Uc->getChId()) + " TCaptureDSPThread: started\n";
      elt->FputEvt(s);
      }
    while(!CDSPT->ProcComplete){ //цикл для получения данных от CaptureDSP. Прекращается при завершении вызова (удаления канала TUdpChannel::mic) когда в структуре AEC будет установлен бит TerminateReq. Закончится цикл pFunc_CaptureDSP, завершится TCaptureDSPThread::Execute().
         TAExchBuf* cc = MainFormSLS->AecDll.pFunc_GetAudioPacket(exch_struct);
         if(!cc)
           {
            /*
           if(!first_mic_packet_rcvd())
               if((__start_thread_time.CurrentDateTime() - __start_thread_time) > TDateTime(0,0,1,0))
                  if(!get_reinit_aec_by_timeout_first_mic_packet__done()) //protection from double reinit req by timeout inside this func
                     RESTART_AEC_PROC(&CDSPT, exch_struct, 2);
                */

           if(MP.check_mic_supply_interval(this)) //Фиксация длительных интервалов ( > 1 sec) отсутствия аудио пакетов от микрофона
              {
            //  RESTART_AEC_PROC(&CDSPT, exch_struct, 2);   //Перезапуск петли AEC в случае отсутствия пакетов не помогает. Помогает только в случае пропуска пакетов (мульт голос(см ниже))
            //  MP.set_time_of_last_rcvd_packt();
              }
           Sleep(1);
           continue;
           }
         MP.set_time_of_last_rcvd_packt();
         if(get_reinit_aec_by_big_samples_interval())
           if(!get_reinit_aec_by_big_samples_interval__done())   //protection from double reinit req by big_samples_interval inside this func
             {
             RESTART_AEC_PROC(&CDSPT, exch_struct, 1);
             continue;
             }

         if(!pckt_cnt)
           {
           set_first_mic_packet_rcvd(true);
           dt_prev_mic_packet = dt_prev_mic_packet.CurrentDateTime();
           log_first_received_packet_from_mic(cc->n, 1);
           #ifdef Wait_For_First_Mic_Packet
           CALL_CONTINUE();                         //Continue outgoing (send INVITE) or incoming call
           #endif
           }
         else
           {
           if(pckt_cnt < 20)
         //  if(pckt_cnt < 2000)   //test
             {
             TDateTime DateTime = DateTime.CurrentDateTime();
             TDateTime dt_diff  = DateTime - dt_prev_mic_packet;
             dt_prev_mic_packet = DateTime;
             if(dt_diff > TDateTime(0,0,0,24)) //вообще - то, больше 15 (обычно 29 - 32) - идет искажение звука от микрофона
                if((cc->n == 160 ) || (cc->n == 320))
                   set_reinit_aec_request_by_big_samples_interval(true);
             log_aec_packet_count_20(DateTime, dt_diff, cc->n);
             }
           }
         pckt_cnt++;
         #ifdef Log_Capture_DSP
         LogCaptureDsp(cc);
         #endif
         TOutPutUdpBlock* opb = NULL;
         int i = 0;
         while((opb = ProDspData(cc,i)) != NULL)      //Process data, receiving from CaptureDSP procedure
              {
              #ifdef Dsp_VAD
              if(ch_conference_participant)
                if(!Mute)  // microphone active
                  {
                  int vad = AecDecodeVAD((short*)&opb->v[0]);
                  if(vad)
                    {
                    switch(vad){
                         case 0:
                           //  _log_dsp_vad_event(vad);
                               break;
                         case 1: {
                             //   _log_dsp_vad_event(vad);   //Voiced speech.
                                 if(ch_conference_bridge)  //send VAD event to ConferenceWin for distribute to all conference participants
                                   {
                                   ::PostMessage(ConferenceWin->Handle, CONFERENCE_PLAIN_MSG, WM_CONFERENCE_PLAIN_MSG_WPARAM__VAD, WM_CONFERENCE_PLAIN_MSG_LPARAM__NDEF);
                                   }
                                 else  //send VAD event direct to conference creator over RTCP channel
                                   {
                                   if(Uc)
                                     {
                                     TMediaSession* ms = MainFormSLS->Sip->sss->GetMs_by_In_Out_Callid(Uc->getInOutCallID());
                                     if(ms)
                                       {
                                       TUdpChannel* uc = ms->getRtcpAudioChannel();
                                       if(uc)
                                          uc->Send_VAD_EVENT();
                                       }
                                     }
                                   }
                                 break;
                                 }
                         case 2:
                                 break;

                         case 3:
                                 break;
                         } //switch(vad){
                    }  //if(vad)
                  }   //if(!Mute)
              #endif
              mic_vol.pow_volume(opb->v,SoundTool->mic_pow_coeff); //Регулировка уровня, ограничение по уровню для исключения нелинейных искажений
              #ifdef Log_Capture_DSP
              TDateTime DateTime = DateTime.CurrentDateTime();
              string s;
              exsTime(DateTime,s);
              s = "\n" + s + " TWaveInputThread::Execute(): GetAudioPacket() from CaptureDSP " + inttostr(cc->n) + " byte AFTER\n";
              int opb_sz = opb->v.size();
              for(unsigned i = 0; i < opb_sz; i++)
                 {

                 }

              #endif
              if(SoundTool->Visible)
                 get_sound_average_volume(opb->v,xyz_in,SoundTool->ProgressBar1);
              if(!BROADCAST_CAPTURE_DSP_MIC_PACKET_TO_ALL_CONNECTED_CHANNELS(opb))    //Rel Windows >= VISTA
                 delete opb;
              }
         MainFormSLS->AecDll.pFunc_FreeExchBuf(cc);
         }  //while(!CDSPT->ProcComplete)

    if(elt)
      {
      TDateTime DateTime = DateTime.CurrentDateTime();
      string s;
      exsTime(DateTime, s);
      s = "\n" + s + " ch_" + inttostr(Uc->getChId()) + " TCaptureDSPThread: start terminate\n";
      elt->FputEvt(s);
      }

    CDSPT->Terminate();
    CDSPT->WaitFor();
    delete CDSPT;
    if(elt)
      {
      TDateTime DateTime = DateTime.CurrentDateTime();
      string s;
      exsTime(DateTime, s);
      s = "\n" + s + " ch_" + inttostr(Uc->getChId()) + " TCaptureDSPThread: deleted\n";
      elt->FputEvt(s);
      }
    }

  if(exch_struct)
    (*MainFormSLS->AecDll.pFunc_FreeExchStruct)(exch_struct);
  if(elt)
    {
    string s = "\nTotal number of packets received from mic: " + inttostr(pckt_cnt) + "\n";
    elt->FputEvt(s);
    }
  return;  //!!!
  }

while(!Terminated)
     {
     if(WIS == WaveInputState_DESTROY)
       {
     __clearBaseQueue();
       WAVE_IN_RESET(WaveInputState_DESTROY);
       Terminate();
       continue;
       }

     if(!pckt_cnt)
       if(!__sending_voice_started)
          startSendingVoice();

     TOutPutUdpBlock* opb = getWaveData();
     if(!opb)
       {
       if(get_whdr_size() < 4)
         addNewInWaveHdr(nAvgBytesPerSec_devby_50);
       else
         Sleep(1);
       }//if(!opb)
     else
       {
       if(!pckt_cnt++)
         {
         set_first_mic_packet_rcvd(true);
         dt_prev_mic_packet = dt_prev_mic_packet.CurrentDateTime();
         log_first_received_packet_from_mic(opb->v.size(), 0);
         #ifdef Wait_For_First_Mic_Packet
         CALL_CONTINUE();                                //Continue outgoing (send INVITE) or incoming call
         #endif
         }
       else
         {
         if(pckt_cnt < 20)
           log_packet_count_20(opb->v.size());
         }

       mic_vol.pow_volume(opb->v,SoundTool->mic_pow_coeff); //Регулировка уровня, ограничение по уровню для исключения нелинейных искажений
       if(SoundTool->mic_filter)
         {
         filter_HPF_K(PREV_X,opb->v);
        // filter_LPF_B(opb->v);
         }
       mic_vol.voice_detect(this,opb,SoundTool->Edit2);
       if(opb->silence_suppr_queue)
         {
         TOutPutUdpBlock* opb_prev = mic_vol.silence_suppression();  //silence_suppr_queue = false inside this func
         if(!opb_prev)
            continue;   //while(!Terminated)
         if(opb_prev->discard)
           {
           delete opb_prev;
           continue;
           }
         opb = opb_prev;
         }
       if(SoundTool->Visible)
          get_sound_average_volume(opb->v,xyz_in,SoundTool->ProgressBar1);
       if(Sip->ucs)
         {
         if(BROADCAST_MIC_PACKET_TO_ALL_CONNECTED_CHANNELS(opb))     //Rel Windows < VISTA
            continue;
         } //if(Sip->ucs)
       bool a = false;
       updateSentQueue(opb, a);
       if(get_whdr_size() < 4)
          addNewInWaveHdr(nAvgBytesPerSec_devby_50);
       }
     } //while(!Terminated)
 }//try
catch(Exception& e){exsSstEXCEPTION(*eltp,"__TWaveInputThread::Execute",e);}
}
//------------------------------------------------------------------------------
void __fastcall TWaveInputThread::log_first_received_packet_from_mic(int len, int type)
{
TEventLogThread* elt = getLog();
if(elt)
  {
  string s;
  exsTime(dt_prev_mic_packet, s);
  s = "\n" + s;
  if(type == 0)
     s += WS;
  else if(type == 1)
     s += " AEC: ";
  s += "ch_" + inttostr(Uc->getChId()) + " First packet received from mic, length " + inttostr(len) + "\n";
  elt->FputEvt(s);
  }
}
//------------------------------------------------------------------------------
void __fastcall TWaveInputThread::log_aec_packet_count_20(TDateTime& DateTime, TDateTime& dt_diff, int len)
{
TEventLogThread* elt = getLog();
if(elt)
  {
  string s;
  exsTime(DateTime,s);
  s = "\n" + s + " ch_" + inttostr(Uc->getChId()) + " packet " + inttostr(pckt_cnt) + " received from mic, length " + inttostr(len);
  string dt;
  exsTime(dt_diff, dt);
  s += " dt " + dt + "\n";
  elt->FputEvt(s);
  }
}
//------------------------------------------------------------------------------
void __fastcall TWaveInputThread::log_packet_count_20(int len)
{
TEventLogThread* elt = getLog();
if(elt)
  {
  TDateTime DateTime = DateTime.CurrentDateTime();
  TDateTime dt_diff  = DateTime - dt_prev_mic_packet;
  dt_prev_mic_packet = DateTime;
  string s;
  exsTime(DateTime,s);
  s = "\n" + s + " ch_" + inttostr(Uc->getChId()) + " packet " + inttostr(pckt_cnt) + " received from mic, length " + inttostr(len);
  string dt;
  exsTime(dt_diff, dt);
  s += " dt " + dt + "\n";
  elt->FputEvt(s);
  }
}
//------------------------------------------------------------------------------
//--  Continue outgoing (send INVITE) or incoming call after receiving first
//--  packet from mic
//------------------------------------------------------------------------------
void __fastcall TWaveInputThread::CALL_CONTINUE()
{
if(!__referenced_call_id.empty())
  {
  if(__referenced_sls == SPS_INVITE_REQ)
    {
    if(Sip->uac)
      {
      TOutputSipBuf* ospb = new TOutputSipBuf;
      if(ospb)
        {
        ospb->setsls(SPS_INVITE_ON_RCV_FIRST_MIC_PACKET_REQ);
        ospb->CallID = __referenced_call_id;
        Sip->uac->setQueue(ospb);       //Удалим сразу в Sip->uac. Поэтому не вставляем в Sip->updateSentQueue_1(ospb); !!!
        }
      }
    }
__referenced_call_id.clear();
  }
}
//------------------------------------------------------------------------------
void __fastcall TWaveInputThread::RESTART_AEC_PROC(TCaptureDSPThread** P_CDSPT, void* exch_struct, int type)
{
TEventLogThread* elt = getLog();
if(elt)
  {
  TDateTime DateTime = DateTime.CurrentDateTime();
  string s;
  exsTime(DateTime,s);
  s = "\n" + s + " ch_" + inttostr(Uc->getChId()) + " RESTART AEC Proc";
  switch(type){
        case 1: s += "( big interval between samples )";   break;
        case 2: s += "( timeout on receive mic packets )"; break;
        }
  s += " !!!\n";
  elt->FputEvt(s);
  }

AEC.TerminateReq = true; //for terminate AEC dll
TCaptureDSPThread* CDSPT = *P_CDSPT;
CDSPT->Terminate();
CDSPT->WaitFor();
delete CDSPT;
*P_CDSPT = NULL;

CDSPT    = new TCaptureDSPThread(true, &AEC, exch_struct);
*P_CDSPT = CDSPT;
AEC.TerminateReq = false;
pckt_cnt         = 0;
CDSPT->Resume();
}
//------------------------------------------------------------------------------
void __fastcall TWaveInputThread::set_reinit_aec_request_by_big_samples_interval(bool a)
{
__reinit_aec_by_big_samples_interval = a;
}
//------------------------------------------------------------------------------
bool __fastcall TWaveInputThread::get_reinit_aec_by_big_samples_interval()
{
bool rv = false;
if(__reinit_aec_by_big_samples_interval)
  {
  rv = true;
__reinit_aec_by_big_samples_interval = false;
  }
return rv;
}
//------------------------------------------------------------------------------
bool __fastcall TWaveInputThread::get_reinit_aec_by_big_samples_interval__done()
{
bool rv = true;
if(!__reinit_aec_by_big_samples_interval__done)
  {
  rv = false;
__reinit_aec_by_big_samples_interval__done = true;
  }
return rv;
}
//----------------------------------------------------------------------------------
bool __fastcall TWaveInputThread::get_reinit_aec_by_timeout_first_mic_packet__done()
{
bool rv = true;
if(!__reinit_aec_by_timeout_first_mic_packet__done)
  {
  rv = false;
__reinit_aec_by_timeout_first_mic_packet__done = true;
  }
return rv;
}
//----------------------------------------------------------------------------------
void __fastcall TWaveInputThread::save_sls(SipLegState SLS)
{
__referenced_sls = SLS;
}
//----------------------------------------------------------------------------------
void __fastcall TWaveInputThread::save_callid(const string& callid)
{
__referenced_call_id = callid;
}
//----------------------------------------------------------------------------------
void __fastcall TWaveInputThread::_log_dsp_vad_event(int vad)
{
TEventLogThread* elt = getLog();
if(elt)
  {
  TDateTime DateTime = DateTime.CurrentDateTime();
  string s;
  exsTime(DateTime,s);
  s = "\n" + s + " VAD: " + inttostr(vad) +  "\n";
  elt->FputEvt(s);
  }
}
//-----------------------------------------------------------------------------
int __fastcall TWaveInputThread::AecDecodeVAD(short *pOutput)
{
    int iVAD = (*pOutput) & 0x01;
    pOutput++;
    iVAD |= (*pOutput << 1) & 0x02;
    return iVAD;
}
//----------------------------------------------------------------------------
bool __fastcall TWaveInputThread::BROADCAST_MIC_PACKET_TO_ALL_CONNECTED_CHANNELS(TOutPutUdpBlock* opb)
{
bool a = false;
if(Uc)
  {
  vector<int> V;
  Uc->getAllMyConnections(V);
  if(!V.empty())
    {
    int sz = V.size();
    if(sz == 1)
      {
       TUdpChannel* cntd_uc = Sip->ucs->getUdpChannel(V[0]);
       if(cntd_uc)
        if(cntd_uc->getMpt() != SOUND_MPT)
          if(cntd_uc->sendThread)
            {
            opb->mpt = SOUND_MPT;
            opb->tunnel_name = "a" + inttostr(cntd_uc->getChId());
            if(Mute){
              int sz = opb->v.size();
              for(int i=0;i<sz;i++)
                  opb->v[i] = 0;
              }
            cntd_uc->sendThread->setQueue(opb);
            }
      updateSentQueue(opb, a);
      if(get_whdr_size() < 4)
         addNewInWaveHdr(nAvgBytesPerSec_devby_50);
      return true; //continue;
      }
    else    //sz > 1
      {
      if(Conf)
        {
        send_mixed_packet_to_all_conference_participants(opb, V, sz);
        updateSentQueue(opb, a);
        if(get_whdr_size() < 4)
           addNewInWaveHdr(nAvgBytesPerSec_devby_50);
        return true; //continue;
        }
      else  //not a conference
        {
        send_mic_packet_to_all_connected_channels(opb, V, sz);
        updateSentQueue(opb, a);
        if(get_whdr_size() < 4)
           addNewInWaveHdr(nAvgBytesPerSec_devby_50);
        return true; //continue;
        }
      }
    } //if(!V.empty())
  } //if(uc)
return false;
}
//------------------------------------------------------------------------------
//--- For Win_8 ----------------------------------------------------------------
//------------------------------------------------------------------------------
bool __fastcall TWaveInputThread::BROADCAST_CAPTURE_DSP_MIC_PACKET_TO_ALL_CONNECTED_CHANNELS(TOutPutUdpBlock* opb)
{
bool rv = false;
if(Uc)
  {
  vector<int> V;
  Uc->getAllMyConnections(V);
  if(!V.empty())
    {
    int sz = V.size();
    if(sz == 1)
      {
       TUdpChannel* cntd_uc = Sip->ucs->getUdpChannel(V[0]);
       if(cntd_uc)
        if(cntd_uc->getMpt() != SOUND_MPT)
          if(cntd_uc->sendThread)
            {
            opb->mpt = SOUND_MPT;
            opb->tunnel_name = "a" + inttostr(cntd_uc->getChId());
            if(Mute){
              int sz = opb->v.size();
              for(int i=0;i<sz;i++)
                  opb->v[i] = 0;
              }
            cntd_uc->sendThread->setQueue(opb);
            }
      updateSentQueue(opb, rv);
      }
    else    //sz > 1
      {
      if(Conf)
        {
        if(MS == MicrophoneState_Passive)
          {
          int sz = opb->v.size();
          for(int i=0;i<sz;i++)
              opb->v[i] = 0;
          }
        send_mixed_packet_to_all_conference_participants(opb, V, sz);
        updateSentQueue(opb, rv);
        }
      else if(Mute)
        {
        int sz = opb->v.size();
        for(int i=0;i<sz;i++)
            opb->v[i] = 0;
        send_mic_packet_to_all_connected_channels(opb, V, sz);
        updateSentQueue(opb, rv);
        }
      else  //not a conference
        {
        send_mic_packet_to_all_connected_channels(opb, V, sz);
        updateSentQueue(opb, rv);
        }
      }
    } //if(!V.empty())
  } //if(uc)
return rv;
}
//-----------------------------------------------------------------------------
void __fastcall TWaveInputThread::send_mixed_packet_to_all_conference_participants(TOutPutUdpBlock* opb, const vector<int>& V,
                                                                                   int number_of_connected_channels)
{
for(int i = 0; i < number_of_connected_channels; i++)
   {
   TUdpChannel* cntd_uc = Sip->ucs->getUdpChannel(V[i]);
   if(cntd_uc)
     if(cntd_uc->getMpt() != SOUND_MPT)
       if(cntd_uc->sendThread)
         {
         vector<int> v_mix;
         acqs.mix_audio_channels(opb->v, v_mix, V[i]);  //opb->v - const -- not changed !!!
         int SZ = v_mix.size();
         NORMALIZE(v_mix, SZ);  //Нормализация значений, полученных в векторе v_mix (max амплитуды сигнала необходимо вогнатьв диапазон 32000 > v_mix[i] > -32000
         TOutPutUdpBlock* opb_child = new TOutPutUdpBlock(pckn);
         if(opb_child)
           {
           #ifdef Log_Audio_Conference_Mixed_Packet
           Write_Audio_Conference_Mixed_Packet(v_mix, V[i], SZ);
           #endif
           INT_2_UBYTE(opb_child->v, v_mix, SZ);
           opb_child->mpt = SOUND_MPT;
           opb_child->tunnel_name = "a" + inttostr(cntd_uc->getChId());
           bool a = false;
           cntd_uc->sendThread->setQueue(opb_child);
           updateSentQueue(opb_child, a);
           }
         }
   }
}
//----------------------------------------------------------------------------
void __fastcall TWaveInputThread::send_mic_packet_to_all_connected_channels(TOutPutUdpBlock* opb, const vector<int>& V,
                                                                                   int number_of_connected_channels)
{
for(int i = 0; i < number_of_connected_channels; i++)
   {
   TUdpChannel* cntd_uc = Sip->ucs->getUdpChannel(V[i]);
   if(cntd_uc)
     if(cntd_uc->getMpt() != SOUND_MPT)
       if(cntd_uc->sendThread)
         {
         TOutPutUdpBlock* opb_child = new TOutPutUdpBlock(pckn);
         if(opb_child)
           {
           opb_child->v   = opb->v;
           opb_child->mpt = SOUND_MPT;
           opb_child->tunnel_name = "a" + inttostr(cntd_uc->getChId());
           bool a = false;
           cntd_uc->sendThread->setQueue(opb_child);
           updateSentQueue(opb_child, a);
           }
         }
   }
}
//------------------------------------------------------------------------------
void __fastcall TWaveOutputThread::procTWaveOutPutBuf(TWaveOutPutBuf* opb)
{
int size = opb->v.size();
if(size)
  {
  char* buf = new char[size];
  if(buf)
    {
    memcpy(buf,&opb->v[0],size);
    WAVEHDR* WaveOutHdr = new WAVEHDR;
    if(WaveOutHdr)
      {
      ZeroMemory(WaveOutHdr, sizeof(WAVEHDR));
      WaveOutHdr->lpData = (LPSTR)buf;
      WaveOutHdr->dwBufferLength = size;
      result = WAVE_OUT_PREPARE_HEADER(WaveOutHdr, sizeof(WAVEHDR));
      if(result)
        {
        wave_error("procTWaveOutPutBuf: waveOutPrepareHeader",result);
        delete [] WaveOutHdr->lpData;
        delete WaveOutHdr;
        return;
        }
      result = WAVE_OUT_WRITE(WaveOutHdr, sizeof(WAVEHDR));
      if(result)
        {
        wave_error("procTWaveOutPutBuf: waveOutWrite",result);
        delete [] WaveOutHdr->lpData;
        delete WaveOutHdr;
        return;
        }
      push_whdr(WaveOutHdr);
      while(get_whdr_size() > 4 )
         {
         if(!try_UnprepareHeader())
           ::Sleep(1);
         }
      }
    }
  }
             //wave_log("TWaveOutputThread::procTWaveOutPutBuf(): end");
}
//----------------------------------------------------------------------------
void __fastcall TWaveOutputThread::procTOutPutUdpBlock(TOutPutUdpBlock** opb_p,int pt)
{
try{
TOutPutUdpBlock* opb = *opb_p;
if(!opb->decompressed)
  {
  if(pFormat.wFormatTag == WAVE_FORMAT_PCM)
    {
    vector<UBYTE> v;
    switch(pt){
        case 0:
        case 8: G711_To_Linear(v,opb->v,pt);
                opb->v = v;
                break;
        default:break;
        }
    }
  }
int size = opb->v.size();
if(size)
  {
     // count_after_mark использ для постепенного увеличения уровня входного сигнала при silence suppr in webRtc
/*  switch(count_after_mark){
        case 0: scale_volume(opb->v,0.05); break;
        case 1: scale_volume(opb->v,0.2); break;
        case 2: scale_volume(opb->v,0.5); break;
        case 3: scale_volume(opb->v,0.75); break;
        }

  */

  if(Conf)
    {
    Uc->pushBufToConf(opb);
    }

  if(SoundTool->stop_sound)
       return;
  if(!opb->vd.empty())
     sound_vol.pow_volume(opb,SoundTool->sound_pow_coeff);
  else
     sound_vol.pow_volume(opb->v,SoundTool->sound_pow_coeff); //Регулировка уровня, ограничение по уровню для исключения нелинейных искажений
  if(SoundTool->sound_filter)
    {
   // filter_HPF_K(PREV_X,opb->v);
   // filter_HPF_K_1(PREV_X,opb->v);
   // filter_HPF_K(PREV_X_1,opb->v);
    filter_HPF_FIRST_ORDER(PREV_X,opb->v);
    //filter_HPF_FIRST_ORDER(PREV_X_1,opb->v);
   // filter_LPF_B(opb->v);
    }

  sound_vol.voice_detect(this,opb,SoundTool->Edit1);
  if(opb->silence_suppr_queue)
    {
    TOutPutUdpBlock* opb_prev = sound_vol.silence_suppression(); //silence_suppr_queue = false inside this func
    if(!opb_prev)
       return;
    opb    = opb_prev;
    *opb_p = opb_prev;
    if(opb_prev->discard)
      return;
    }
  if(SoundTool->Visible)
     get_sound_average_volume(opb->v,xyz_out,SoundTool->ProgressBar2);

  char* buf = new char[size];
  if(buf)
    {
    memcpy(buf,&opb->v[0],size);
    WAVEHDR* WaveOutHdr = new WAVEHDR;
    if(WaveOutHdr)
      {
      ZeroMemory(WaveOutHdr, sizeof(WAVEHDR));
      WaveOutHdr->lpData = (LPSTR)buf;
      WaveOutHdr->dwBufferLength = size;
      result = WAVE_OUT_PREPARE_HEADER(WaveOutHdr, sizeof(WAVEHDR));
      if(result)
        {
        wave_error("procTOutPutUdpBlock: waveOutPrepareHeader",result);
        delete [] WaveOutHdr->lpData;
        delete WaveOutHdr;
        return;
        }
      result = WAVE_OUT_WRITE(WaveOutHdr, sizeof(WAVEHDR));
      if(result)
        {
        wave_error("procTOutPutUdpBlock: waveOutWrite",result);
        delete [] WaveOutHdr->lpData;
        delete WaveOutHdr;
        return;
        }
      push_whdr(WaveOutHdr);
      while(get_whdr_size() > 4)//12)//8)//4) //4 )
           {
           if(!try_UnprepareHeader())
             ::Sleep(1);
           }
      }
    }
  }
 }//try
catch(Exception& e){exsSstEXCEPTION(*eltp,"__TWaveOutputThread::procTOutPutUdpBlock()",e);}
}
//----------------------------------------------------------------------------
void __fastcall TWaveOutputThread::Stop_Alerting_FINALLY()
{
DESTROY_REQUEST = true;
if(Suspended)
   Resume_Thread();
}
//----------------------------------------------------------------------------
void __fastcall TWaveOutputThread::startAlerting()
{
WOS = WaveOutputState_REQUEST_TO_START_ALERTING;
if(Suspended)
   Resume_Thread();
}
//----------------------------------------------------------------------------
void  __fastcall TWaveOutputThread::startReceivingVoice(TRemoteMedia* rm)
{
if(Uc)
  {
  string s = "\nch_" + inttostr(Uc->getChId()) + " startReceivingVoice\n";
  wave_log(s);
  }
#ifdef Receiving_Wave_Format_PCM
Requested_FormatTag = WAVE_FORMAT_PCM;
#else
if(!rm->audio_codecs.empty())
   switch(rm->audio_codecs[0]){
        case 0:
               Requested_FormatTag  = WAVE_FORMAT_MULAW;
               break;
        case 8:
               Requested_FormatTag  = WAVE_FORMAT_ALAW;
               break;
        default:Requested_FormatTag = WAVE_FORMAT_ALAW;
        }
#endif
STATIC_WOS = WaveOutputState_REQUEST_TO_START_RECEIVING_VOICE;
if(Suspended)
   Resume_Thread();
}
//-----------------------------------------------------------------------------
void __fastcall TWaveOutputThread::proc_request_to_start_alerting()
{
__clearBaseQueue();
wave_log("StartAlerting: begin\n");
WAVE_OUT_RESET(WaveOutputState_START_ALERTING);
pFormat.wFormatTag       = WAVE_FORMAT_PCM;//1;//strtoint(FormayTag);//1; //6;
pFormat.nChannels        = 1;
pFormat.nSamplesPerSec   = 8000; //48000; //8000; //16000; //44100;                                   //8000;//8000;//8000;// 44100
pFormat.wBitsPerSample   = 16;   //8;			//  16 for high quality, 8 for telephone-grade
pFormat.nAvgBytesPerSec  = pFormat.nSamplesPerSec * pFormat.nChannels * (pFormat.wBitsPerSample/8);		// = nSamplesPerSec * n.Channels * wBitsPerSample/8
pFormat.nBlockAlign      = pFormat.nChannels * (pFormat.wBitsPerSample/8); // = n.Channels * wBitsPerSample/8
pFormat.cbSize=0;
nAvgBytesPerSec_devby_50 = pFormat.nAvgBytesPerSec/50;

int   max_amplitude      = 16383;      //32767;//16383;//63; // 32767; //16383;
const buflen             = 16000;      //16000; //32000;    //88200;      // 16000; //1Sec TEST !!!
short buffer[buflen];
memset(buffer, 0, sizeof(buffer));
for(int i = 0; i < buflen; i++)
   {
   switch(Sip->Signal.at){
          case AlertingType_RU:
               buffer[i] = max_amplitude * sin(i * TWO__M_PI * 425/pFormat.nSamplesPerSec);
               break;
          case AlertingType_US:
               buffer[i] = max_amplitude * (sin(i * TWO__M_PI * 440/pFormat.nSamplesPerSec) + sin(i * TWO__M_PI * 480/pFormat.nSamplesPerSec));
               break;
          }
  }
if(WAVE_OUT_OPEN(WaveOutputState_START_ALERTING))
   return;

WAVE_OUT_SET_VOLUME(0x7FFF7FFF);
WOS = WaveOutputState_START_ALERTING; //Do no set above and below
TWaveOutPutBuf* opb = new TWaveOutPutBuf;
if(opb)
  {
  opb->v.resize(buflen);
  memcpy(&opb->v[0], buffer, buflen);
  setQueue(opb);
  }
wave_log("StartAlerting: end\n");
}
//-----------------------------------------------------------------------------
void __fastcall TWaveOutputThread::proc_request_to_stop_alerting()
{
wave_log("stopAlerting: begin\n");
__clearBaseQueue();
alerting_pause = alerting_pause.CurrentDateTime() + TDateTime(0,0,4,0);  //Alerting Pause 4 sec
// /*
int buflen = pFormat.nSamplesPerSec * 2;
TWaveOutPutBuf* opb = new TWaveOutPutBuf;
if(opb)
  {
  opb->v.resize(4*buflen, 0);
  setQueue(opb);
  }
// */
WOS = WaveOutputState_STOP_ALERTING;
wave_log("stopAlerting: end\n");
}
//-----------------------------------------------------------------------------
bool __fastcall TWaveOutputThread::proc_stop_alerting()
{
if(alerting_pause.CurrentDateTime() < alerting_pause)
  {
  ::Sleep(1);
  return true;
  }
return false;
}
//-----------------------------------------------------------------------------
void __fastcall TWaveOutputThread::proc_request_to_start_receiving_voice()
{
if(Uc)
  {
  string s = "\nch_" + inttostr(Uc->getChId()) + " proc_request_to_START_RECEIVING_VOICE: begin\n ";
  wave_log(s);
  }
record = SoundTool->sound_record;
if(record)
  {
  if(f)
     fclose(f);
  string s = MainFormSLS->give_client_root() + "\\Record";
  if(!::DirectoryExists(s.c_str()))
      ::CreateDir(s.c_str());
  string timestr;
  TDateTime dt = dt.CurrentDateTime();
  exsDateTime_FileName(dt,timestr);
  s += "\\Record_" + timestr;
  record_file = s;
  f = fopen(s.c_str(),"wb");
  }
__clearBaseQueue();
WAVE_OUT_RESET(WaveOutputState_RECEIVING_VOICE);
pFormat.wFormatTag = Requested_FormatTag;
pFormat.nChannels  = 1;//2;//1;
pFormat.nSamplesPerSec = 8000; //8000;//8000;//8000;// 44100
if(Requested_FormatTag == WAVE_FORMAT_PCM)
 pFormat.wBitsPerSample = 16;
else
 pFormat.wBitsPerSample  = 8;			//  16 for high quality, 8 for telephone-grade
pFormat.nAvgBytesPerSec  = pFormat.nSamplesPerSec * pFormat.nChannels * (pFormat.wBitsPerSample/8);		// = nSamplesPerSec * n.Channels * wBitsPerSample/8
pFormat.nBlockAlign      = pFormat.nChannels * (pFormat.wBitsPerSample/8); // = n.Channels * wBitsPerSample/8
pFormat.cbSize           = 0;
nAvgBytesPerSec_devby_50 = pFormat.nAvgBytesPerSec/50;


if(!WAVE_OUT_OPEN(WaveOutputState_RECEIVING_VOICE))
  {
  WAVE_OUT_SET_VOLUME(0xFFFFFFFF);
//WAVE_OUT_SET_VOLUME(0x7FFF7FFF);
  JBD_State = JBD_State_Start;
  STATIC_WOS = WaveOutputState_RECEIVING_VOICE;
  WOS        = WaveOutputState_RECEIVING_VOICE;  //!!! Do not set above
  if(Uc)
    {
    string s = "\nch_" + inttostr(Uc->getChId()) + " proc_request_to_START_RECEIVING_VOICE: end\n ";
    wave_log(s);
    }
  }
else
  {
  STATIC_WOS = WaveOutputState_Unknown;
  WOS        = WaveOutputState_Unknown;
  if(Uc)
    {
    string s = "\nERROR on WAVE_OUT_OPEN(): ch_" + inttostr(Uc->getChId()) + " SOUND. STATIC_WOS and WOS set to WaveOutputState_Unknown\n";
    wave_log(s);
    }
  }
}
//-----------------------------------------------------------------------------
void __fastcall TGenDTMFdig::gen(double d_l,double d_h)
{ //w_l,h_l - начальные фазы сигналов
vector<double> v;
double arg_l = w_l; //текущая фаза нижнего сигнала
double arg_h = w_h; //текущая фаза верхнего сигнала
for(int i=0;i<N;i++)
   {
   if(i)
     {
     arg_l += d_l;
     arg_h += d_h;
     }
   v.push_back(ampl*(sin(arg_l) + sin(arg_h)));
   }
w_l += N * d_l;
w_h += N * d_h;
double_2_short(v);
}
//-----------------------------------------------------------------------------
void __fastcall TGenDTMFdig::double_2_short(vector<double>& y)
{
out_short.clear();
for(int i=0; i<N; i++)
   {
   round_up(y,i);
   out_short.push_back(y[i]);
   }
}
//------------------------------------------------------------------------------
void __fastcall TGenDTMFdig::short_2_ubyte()
{
out_ubyte.clear();
for(int i=0; i<N; i++)
   {
   UBYTE a = out_short[i] & 0xFF;
   out_ubyte.push_back(a);
   a = out_short[i] >> 8;
   out_ubyte.push_back(a);
   }
}
//------------------------------------------------------------------------------
void __fastcall TWaveOutputThread::proc_gen_dig_start()
{
string timestr;
TDateTime dt = dt.CurrentTime();
exsTime( dt,timestr);
wave_log("\n" + timestr + " gen_dtmf " + inttostr(dtmf.digit - 10) + ": start");
__clearBaseQueue();
dtmf.w_l = 0.0;  //начальные фазы сигнала нижнего сигнала
dtmf.w_h = 0.0;  //начальные фазы сигнала верхнего сигнала
for(int j=0;j<100;j++)
   {
   switch(dtmf.digit){
          case 11:dtmf.gen(d_697,d_1209); //"1"
                  break;
          case 12:dtmf.gen(d_697,d_1336); //"2"
                  break;
          case 13:dtmf.gen(d_697,d_1477); //"3"
                  break;
          case 14:dtmf.gen(d_770,d_1209); //"4"
                  break;
          case 15:dtmf.gen(d_770,d_1336); //"5"
                  break;
          case 16:dtmf.gen(d_770,d_1477); //"6"
                  break;
          case 17:dtmf.gen(d_852,d_1209); //"7"
                  break;
          case 18:dtmf.gen(d_852,d_1336); //"8"
                  break;
          case 19:dtmf.gen(d_852,d_1477); //"9"
                  break;
          case 24:dtmf.gen(d_941,d_1209); //"*"
                  break;
          case 10:dtmf.gen(d_941,d_1336); //"0"
                  break;
          case 25:dtmf.gen(d_941,d_1477); //"#"
                  break;
          case 20:dtmf.gen(d_697,d_1633); //"A"
                  break;
          case 21:dtmf.gen(d_770,d_1633); //"B"
                  break;
          case 22:dtmf.gen(d_852,d_1633); //"C"
                  break;
          case 23:dtmf.gen(d_941,d_1633); //"D"
                  break;
          default:WOS = WaveOutputState_GEN_DTMF_DIGITS_STOP;
                  return;
          }
   if(!dtmf.out_short.empty())
     {
     TWaveOutPutBuf* opb = new TWaveOutPutBuf;
     if(opb)
       {
       dtmf.short_2_ubyte();
       opb->v = dtmf.out_ubyte;
       setQueue(opb);
       }
     }
   }
WOS = WaveOutputState_GEN_DTMF_DIGITS_CONTINUE;
}
//-----------------------------------------------------------------------------
void __fastcall TWaveOutputThread::proc_gen_dig_stop()
{
string timestr;
TDateTime dt = dt.CurrentTime();
exsTime( dt,timestr);
wave_log(timestr + " gen_dtmf " + inttostr(dtmf.digit - 10) + ": stop");
__clearBaseQueue();
WOS = dtmf.wos;
}
//-----------------------------------------------------------------------------
void __fastcall TWaveOutputThread::WAVE_OUT_RESET(TWaveOutputState state)
{
wave_log("WAVE_OUT_RESET");
MMRESULT RESULT_1=0;
MMRESULT RESULT_2=0;

::EnterCriticalSection(&whdr_cs);
  if(hWaveOut)
    {
    RESULT_1 = waveOutReset(hWaveOut);
    final_Unprepare_Out_Header();
    RESULT_2 = waveOutClose(hWaveOut);
    hWaveOut = NULL;
    }
::LeaveCriticalSection(&whdr_cs);

if((RESULT_1)||(RESULT_2))
  {
  string s = "ch_" + inttostr(Uc->getChId()) + " WAVE_OUT_RESET; " ;
  switch(state){
         case WaveOutputState_START_ALERTING:
              s += "Start_Alerting: ";
              break;
         case WaveOutputState_STOP_ALERTING:
              s += "Stop_Alerting: ";
              break;
         case WaveOutputState_RECEIVING_VOICE:
              s += "ReceivingVoice: ";
              break;
         case WaveOutputState_DESTROY:
              s += "Delete_WaveOutputThread: ";
              break;
        }
  if(RESULT_1)
     wave_error(s + "waveOutReset",RESULT_1);
  else if(RESULT_2)
     wave_error(s + "waveOutClose",RESULT_2);
  }
}
//-----------------------------------------------------------------------------
MMRESULT __fastcall TWaveOutputThread::WAVE_OUT_OPEN(TWaveOutputState state)
{
string s;
switch(state){
       case WaveOutputState_START_ALERTING:
            s = "Start_Alerting: ";
            break;
       case WaveOutputState_STOP_ALERTING:
            s = "Stop_Alerting: ";
            break;
       case WaveOutputState_RECEIVING_VOICE:
            s = "ReceivingVoice: ";
            break;
       case WaveOutputState_DESTROY:
            s = "Delete_WaveOutputThread: ";
            break;
      }
wave_log(s + "waveOutOpen\n");
MMRESULT RESULT = 0;
unsigned  DeviceID;
if(MainFormSLS->out_sound_dev.num == -1)
   DeviceID = WAVE_MAPPER;
else
   DeviceID = MainFormSLS->out_sound_dev.num;
::EnterCriticalSection(&whdr_cs);
  RESULT = waveOutOpen(&hWaveOut, DeviceID,&pFormat, 0, 0, CALLBACK_NULL);
::LeaveCriticalSection(&whdr_cs);

if(RESULT)
  wave_error(s + "waveOutOpen",RESULT);
return RESULT;
}
//-----------------------------------------------------------------------------
void __fastcall TWaveOutputThread::WAVE_OUT_SET_VOLUME(int volume)
{
wave_log("waveOut_SetVolume");
::EnterCriticalSection(&whdr_cs);
  waveOutSetVolume(hWaveOut,volume);
::LeaveCriticalSection(&whdr_cs);
}
//-----------------------------------------------------------------------------
MMRESULT __fastcall TWaveOutputThread::WAVE_OUT_PREPARE_HEADER(WAVEHDR* WaveOutHdr, int size)
{
MMRESULT RESULT = 0;
::EnterCriticalSection(&whdr_cs);
  RESULT = waveOutPrepareHeader(hWaveOut, WaveOutHdr, size);
::LeaveCriticalSection(&whdr_cs);
return RESULT;
}
//-----------------------------------------------------------------------------
MMRESULT __fastcall TWaveOutputThread::WAVE_OUT_WRITE(WAVEHDR* WaveOutHdr, int size)
{
MMRESULT RESULT = 0;
::EnterCriticalSection(&whdr_cs);
  RESULT = waveOutWrite(hWaveOut, WaveOutHdr, size);
::LeaveCriticalSection(&whdr_cs);
return RESULT;
}
//-----------------------------------------------------------------------------
int __fastcall TWaveOutputThread::GET_WAVE_FORMAT_TAG()
{
int rv;
::EnterCriticalSection(&whdr_cs);
  rv = pFormat.wFormatTag;
::LeaveCriticalSection(&whdr_cs);
return rv;
}
//-----------------------------------------------------------------------------
void __fastcall TWaveBaseThread::push_whdr(WAVEHDR* WaveHdr)
{
::EnterCriticalSection(&whdr_cs);
  whdr.push_back(WaveHdr);
::LeaveCriticalSection(&whdr_cs);
}
//----------------------------------------------------------------------------
int __fastcall TWaveBaseThread::get_whdr_size()
{
int rv=0;
::EnterCriticalSection(&whdr_cs);
  rv=whdr.size();
::LeaveCriticalSection(&whdr_cs);
return rv;
}
//----------------------------------------------------------------------------
int __fastcall TWaveBaseThread::get_whdr_done_count()
{
int rv = 0;
::EnterCriticalSection(&whdr_cs);
  deque<WAVEHDR*>::iterator it = whdr.begin();
  while(it != whdr.end())
       {
       if(((*it)->dwFlags & WHDR_DONE) == WHDR_DONE)
          rv++;
       it++;
       }
::LeaveCriticalSection(&whdr_cs);
return rv;
}
//----------------------------------------------------------------------------
bool __fastcall TWaveOutputThread::try_UnprepareHeader()
{
bool rv=false;
MMRESULT RESULT = 0;
::EnterCriticalSection(&whdr_cs);
  if(!whdr.empty())
    {
    WAVEHDR* wh = whdr.front();
    if((wh->dwFlags & WHDR_DONE) == WHDR_DONE)
      {
      RESULT = waveOutUnprepareHeader(hWaveOut, wh, sizeof(WAVEHDR));
      delete [] wh->lpData;
      whdr.pop_front();
      delete wh;
      rv=true;
      }
    }
::LeaveCriticalSection(&whdr_cs);
if(RESULT)
  {
  lasterr = "\nwaveOutUnprepareHeader() result " + inttostr(RESULT);
  sendlasterr();
  }
return rv;
}
//----------------------------------------------------------------------------
bool __fastcall TWaveBaseThread::is_whdr_empty()
{
bool rv=false;
::EnterCriticalSection(&whdr_cs);
  if(whdr.empty())
     rv=true;
::LeaveCriticalSection(&whdr_cs);
return rv;
}
//----------------------------------------------------------------------------
void __fastcall TWaveOutputThread::final_Unprepare_Out_Header()   //must be included in the Critical Section  whdr_cs
{
while(!whdr.empty())
     {
     WAVEHDR* wh = whdr.front();
     if((wh->dwFlags & WHDR_DONE) == WHDR_DONE)
       {
       waveOutUnprepareHeader(hWaveOut, wh, sizeof(WAVEHDR));
       delete [] wh->lpData;
       whdr.pop_front();
       delete wh;
       }
     else
       break;
     }
}
//----------------------------------------------------------------------------
void __fastcall TWaveInputThread::final_Unprepare_In_Header()   //Always calls in Critical Section
{
while(!whdr.empty())
     {
     WAVEHDR* wh = whdr.front();
     if((wh->dwFlags & WHDR_DONE) == WHDR_DONE)
       {
       result = waveInUnprepareHeader(hWaveIn, wh, sizeof(WAVEHDR));
       delete [] wh->lpData;
       whdr.pop_front();
       delete wh;
       }
     else
       break;
     }
}
//----------------------------------------------------------------------------
TOutPutUdpBlock* __fastcall TWaveInputThread::getWaveData()
{
TOutPutUdpBlock* rv = NULL;
::EnterCriticalSection(&whdr_cs);
  if(!whdr.empty())
    {
    WAVEHDR* wh = whdr.front();
    if((wh->dwFlags & WHDR_DONE) == WHDR_DONE)
      {
      if(wh->lpData)
        if(wh->dwBufferLength)
          {
          TOutPutUdpBlock* opb = new TOutPutUdpBlock(pckn);
          if(opb)
            {
            if(wh->dwBufferLength != wh->dwBytesRecorded)
              {
              string s = "ERROR: TWaveInputThread::getWaveData(): wh->dwBufferLength != wh->dwBytesRecorded";
              s += " dwBufferLength = "  + inttostr(wh->dwBufferLength);
              s += " dwBytesRecorded = " + inttostr(wh->dwBytesRecorded);
              s += "\n";
              wave_log(s);
              }
            opb->v.resize(wh->dwBufferLength);
            memcpy(&opb->v[0],wh->lpData,wh->dwBufferLength);
            rv=opb;
            }
          }
      result = waveInUnprepareHeader(hWaveIn, wh, sizeof(WAVEHDR));
      delete [] wh->lpData;
      whdr.pop_front();
      delete wh;
      }
    }
::LeaveCriticalSection(&whdr_cs);
return rv;
}
//----------------------------------------------------------------------------
void  __fastcall TWaveInputThread::startSendingVoice()
{
if(MainFormSLS->AecDll.Initiated)
  {
  if(Uc)
    {
    string s = "\nch_" + inttostr(Uc->getChId()) + " startSendingVoice with AecDll (Resume TWaveInputThread)\n";
    wave_log(s);
    }
  WIS = WaveInputState_ACTIVE;
  if(Suspended) // !!!
    Resume_Thread();
  return;
  }
/*
On Windows, I know you can use waveIn, but it's a complicated process.
1) Open an input device with waveInOpen
2) Prepare one or a few buffers with waveInPrepareHeader
3) Give those buffers to the output device with waveInAddBuffer
4) Start recording with waveInStart
5) Audio is recorded and fills your buffers
6) Continue to provide additional buffers as needed for as long as you want to record audio
7) Stop recording with waveInStop
8) Free buffers with waveInUnprepareHeader
9) Close input device with waveInClose
*/

if(__sending_voice_started)
   return;
__sending_voice_started = true;

__clearBaseQueue();

/*
if(!Suspended)
  {
  Suspend_Thread();
  while(!Suspended)
        ::Sleep(1);
  }
*/

WAVE_IN_RESET(WaveInputState_ACTIVE);

pFormat.wFormatTag       = WAVE_FORMAT_PCM;//1;
pFormat.nChannels        = 1;
pFormat.nSamplesPerSec   = 8000;
pFormat.wBitsPerSample   = 16;	//  16 for high quality, 8 for telephone-grade
pFormat.nAvgBytesPerSec  = pFormat.nSamplesPerSec * pFormat.nChannels * (pFormat.wBitsPerSample/8);		// = nSamplesPerSec * n.Channels * wBitsPerSample/8
pFormat.nBlockAlign      = pFormat.nChannels * (pFormat.wBitsPerSample/8);				// = n.Channels * wBitsPerSample/8
pFormat.cbSize           = 0;
nAvgBytesPerSec_devby_50 = pFormat.nAvgBytesPerSec/50;  //320 - for 20ms payload size(160 samples * 2 bytes) ;
if(WAVE_IN_OPEN())
   return;
WIS = WaveInputState_ACTIVE;  //!!! Do not set above
//int size = pFormat.nAvgBytesPerSec/50;  //320 - for 20ms payload size(160 samples * 2 bytes) ;
for(int i=0;i<4;i++)
    addNewInWaveHdr(nAvgBytesPerSec_devby_50);
if(WAVE_IN_START())
   return;
if(Suspended)
  if(MS == MicrophoneState_Active)
     Resume_Thread();
wave_log("startSendingVoice\n");     
}
//----------------------------------------------------------------------------
MMRESULT __fastcall TWaveInputThread::WAVE_IN_OPEN()
{
wave_log("WAVE_INPUT_OPEN");
MMRESULT RESULT = 0;
unsigned  DeviceID;
if(MainFormSLS->in_sound_dev.num == -1)
   DeviceID = WAVE_MAPPER;
else
   DeviceID = MainFormSLS->in_sound_dev.num;
::EnterCriticalSection(&whdr_cs);
  RESULT = waveInOpen(&hWaveIn,DeviceID,&pFormat,0,0,CALLBACK_NULL);
::LeaveCriticalSection(&whdr_cs);
if(RESULT)
   wave_error("waveInOpen",RESULT);
return RESULT;
}
//-----------------------------------------------------------------------------
MMRESULT __fastcall TWaveInputThread::WAVE_IN_START()
{
wave_log("WAVE_INPUT_START");
MMRESULT RESULT = 0;
::EnterCriticalSection(&whdr_cs);
  RESULT = waveInStart(hWaveIn);
::LeaveCriticalSection(&whdr_cs);
if(RESULT)
   wave_error("waveInStart",RESULT);
return RESULT;
}
//------------------------------------------------------------------------------
MMRESULT __fastcall TWaveInputThread::WAVE_IN_PREPARE_HEADER(WAVEHDR* WaveInHdr, int size)
{
MMRESULT RESULT = 0;
::EnterCriticalSection(&whdr_cs);
  RESULT = waveInPrepareHeader(hWaveIn, WaveInHdr, size);
::LeaveCriticalSection(&whdr_cs);
if(RESULT)
   wave_error("WAVE_IN_PREPARE_HEADER",RESULT);
return RESULT;
}
//------------------------------------------------------------------------------
MMRESULT __fastcall TWaveInputThread::WAVE_IN_ADD_BUFFER(WAVEHDR* WaveInHdr, int size)
{
MMRESULT RESULT = 0;
::EnterCriticalSection(&whdr_cs);
  RESULT = waveInAddBuffer(hWaveIn, WaveInHdr, size);
::LeaveCriticalSection(&whdr_cs);
if(RESULT)
   wave_error("WAVE_IN_ADD_BUFFER",RESULT);
return RESULT;
}
//------------------------------------------------------------------------------
void __fastcall TWaveInputThread::WAVE_IN_RESET(TWaveInputState state)
{
wave_log("WAVE_INPUT_RESET");
MMRESULT RESULT_1=0;
MMRESULT RESULT_2=0;

::EnterCriticalSection(&whdr_cs);
  if(hWaveIn)
    {
    RESULT_1 = waveInReset(hWaveIn);
    final_Unprepare_In_Header();
    RESULT_2 = waveInClose(hWaveIn);
    hWaveIn = NULL;
    }
::LeaveCriticalSection(&whdr_cs);

if((RESULT_1)||(RESULT_2))
  {
  string s;
  switch(state){
         case WaveInputState_ACTIVE:
              s = "Start_Sending_Voice: ";
              break;
         case WaveInputState_DESTROY:
              s = "Delete_WaveInputThread: ";
              break;
        }
  if(RESULT_1)
     wave_error(s + "waveInReset",RESULT_1);
  else if(RESULT_2)
     wave_error(s + "waveInClose",RESULT_2);
  }

}
//-----------------------------------------------------------------------------
void  __fastcall TWaveInputThread::addNewInWaveHdr(int size)
{
if(!size)return;
WAVEHDR* WaveInHdr = new WAVEHDR;
if(WaveInHdr)
  {
  char* buf = new char[size];
  if(buf)
    {
    memset(buf,0,size);
    ZeroMemory(WaveInHdr, sizeof(WAVEHDR));
    WaveInHdr->lpData         = (LPSTR)buf;
    WaveInHdr->dwBufferLength = size;
    result = WAVE_IN_PREPARE_HEADER(WaveInHdr, sizeof(WAVEHDR));
    if(result)
      {
      wave_error("addNewInWaveHdr: waveInPrepareHeader",result);
      delete [] WaveInHdr->lpData;
      delete WaveInHdr;
      return;
      }
    result = WAVE_IN_ADD_BUFFER(WaveInHdr, sizeof(WAVEHDR));
    if(result)
      {
      wave_error("addNewInWaveHdr: waveInAddBuffer",result);
      delete [] WaveInHdr->lpData;
      delete WaveInHdr;
      return;
      }
    push_whdr(WaveInHdr);
    } //if(buf)
  } //if(WaveInHdr)
}
//------------------------------------------------------------------------------
void __fastcall TWaveBaseThread::wave_error(const string& S, MMRESULT RESULT)
{
char fault[256];
waveInGetErrorText(RESULT, fault, 256);
lasterr = "\nError:" + WS + S + COLON + WS + string(fault);
sendlasterr();
}
//------------------------------------------------------------------------------
void __fastcall TWaveBaseThread::wave_log(const string& S)
{
lasterr = "\n" + S;
sendlasterr();
}
//------------------------------------------------------------------------------
void __fastcall TWaveBaseThread::set_std_format()
{
pFormat.wFormatTag = WAVE_FORMAT_PCM;
pFormat.nChannels  = 1;
pFormat.nSamplesPerSec = 8000;
pFormat.wBitsPerSample = 16;
pFormat.nAvgBytesPerSec= pFormat.nSamplesPerSec * pFormat.nChannels * (pFormat.wBitsPerSample/8);		// = nSamplesPerSec * n.Channels * wBitsPerSample/8
pFormat.nBlockAlign = pFormat.nChannels * (pFormat.wBitsPerSample/8); // = n.Channels * wBitsPerSample/8
pFormat.cbSize=0;
nAvgBytesPerSec_devby_50 = pFormat.nAvgBytesPerSec/50;
}
//------------------------------------------------------------------------------
__fastcall TAudioConfQueueStruct::~TAudioConfQueueStruct()
{
TAudioConfQueueList::iterator it = acql.begin();
while(it != acql.end())
      delete (*it++).second;
::DeleteCriticalSection(&acql_cs);      
}
//-----------------------------------------------------------------------------
void __fastcall TAudioConfQueueStruct::add_channel_to_conference(int chId)
{
::EnterCriticalSection(&acql_cs);
  TAudioConfQueueList::iterator it = acql.find(chId);
  if(it == acql.end())
    {
    TMediaQueueStruct* mqs = new TMediaQueueStruct(chId);
    if(mqs)
       acql.insert(TAudioConfQueueList::value_type(chId,mqs));
    }
::LeaveCriticalSection(&acql_cs);
}
//-----------------------------------------------------------------------------
void __fastcall TAudioConfQueueStruct::delete_channel_from_conference(int chId)
{
::EnterCriticalSection(&acql_cs);
  TAudioConfQueueList::iterator it = acql.find(chId);
  if(it != acql.end())
    {
    TMediaQueueStruct* mqs = (*it).second;
    if(mqs)
       delete mqs;
    acql.erase(it);
    }
::LeaveCriticalSection(&acql_cs);
}
//-----------------------------------------------------------------------------
int __fastcall TAudioConfQueueStruct::add_audio_packet(int chId,vector<UBYTE>& audio_packet)
{
int rv=0;
::EnterCriticalSection(&acql_cs);
  TAudioConfQueueList::iterator it = acql.find(chId);
  if(it != acql.end())
    {
    TMediaQueueStruct* mqs = (*it).second;
    if(mqs)
      {
      int sz = mqs->get_size();
      if(sz > JBD_Max)
         rv = JBD_Max;  //Print "RESET block sz > JBD_Max"
      else
         mqs->add_media_packet(audio_packet);
      }
    }
::LeaveCriticalSection(&acql_cs);
return rv;
}
//-----------------------------------------------------------------------------
void __fastcall TAudioConfQueueStruct::read_all_first_conf_packets(vector< vector<UBYTE> >& VECT, int chID)
{
::EnterCriticalSection(&acql_cs);
  TAudioConfQueueList::iterator it = acql.begin();
  while(it != acql.end())
       {
       TMediaQueueStruct* mqs = (*it++).second;
       if(mqs)
         {
         if(mqs->get_chid() != chID) //don"t send packet to that channel from which we receive packet
           {
           vector <UBYTE> v;
           mqs->get_first_media_packet(v);
           if(!v.empty())
             {
             #ifdef Log_Audio_Conference_Mixed_Packet
             Write_ch_id_from_which_packet_mixed(mqs, chID, v);
             #endif
             VECT.push_back(v);
             }
           }
         }
       }
::LeaveCriticalSection(&acql_cs);
}
//-----------------------------------------------------------------------------
//--- v contains samples from microphone --------------------------------------
//-----------------------------------------------------------------------------
void __fastcall TAudioConfQueueStruct::mix_audio_channels(const vector<UBYTE>& v, vector<int>& v_mix, int chID)
{
int sz_UBYTE  = v.size();
UBYTE_2_INT(v_mix, v, sz_UBYTE);
vector< vector<UBYTE> > VECT;
read_all_first_conf_packets(VECT, chID);
if(!VECT.empty())
  {
  int VECT_sz = VECT.size();
  for(int j=0;j<VECT_sz;j++)
     {
     int size = VECT[j].size();
     int min_size;
     if(size < sz_UBYTE)
        min_size = size;
     else
        min_size = sz_UBYTE;
     MIX_UBYTE_2_INT(v_mix, VECT[j], min_size);
     }
  }
}
//-----------------------------------------------------------------------------
void __fastcall TMinValue::get_min_value(double sum,double av_val,TOutPutUdpBlock* opb)
{
if(!ready)
  {
  if(sum < av_val)
    {
    min_val = sum;
    v       = opb->v;
    ready   = true;
    }
  }
else
  {
  if(sum < min_val)
    {
    min_val = sum;
    v = opb->v;
    }
  }
}
//-----------------------------------------------------------------------------
void __fastcall TVolume::dft(TWaveBaseThread* BT,TOutPutUdpBlock* opb,TSampleFreqImage& sfi)
{
int sz = opb->v.size();
if(sz)
  {
  vector<short> x; //отсчеты на входе фильтра
  ubyte_2_short(x,opb->v,sz);
  int sz_x = x.size();
  complex<double> sum_1(0,0);
  for(int i=0;i<sz_x;i++)   //1-я гарм - 50 Hz
     {
     complex<double> a = ((double)x[i])*MainFormSLS->hh[i];
     sum_1 += a;
     }
  double ampl_1 = sqrt(pow(sum_1.real(),2) + pow(sum_1.imag(),2));

  /*
  complex<double> sum_2(0,0);
  int sz_2 = sz_x/2;
  for(int i=0;i<sz_2;i++) //2-я гарм - 100 Hz
     {
     complex<double> a = ((double)x[i] + (double)x[i + 80])*MainFormSLS->hh[2*i];
     sum_2 += a;
     }
  double ampl_2 = sqrt(pow(sum_2.real(),2) + pow(sum_2.imag(),2));

  complex<double> sum_4(0,0);
  int sz_4 = sz_x/4;
  for(int i=0;i<sz_4;i++) //4-я гарм - 200 Hz
     {
     complex<double> a = ((double)x[i] + (double)x[i + 40] + (double)x[i + 80] + (double)x[i + 120])*MainFormSLS->hh[4*i];
     sum_4 += a;
     }
   double ampl_4 = sqrt(pow(sum_4.real(),2) + pow(sum_4.imag(),2));
  */

  complex<double> sum_10(0,0);
  int sz_10 = sz_x/10;
  for(int i=0;i<sz_10;i++) //10-я гарм - 500 Hz
     {
     complex<double> a = ((double)x[i]       + (double)x[i + 16] + (double)x[i + 32] + (double)x[i + 48]  +
                          (double)x[i + 64]  + (double)x[i + 80] + (double)x[i + 96] + (double)x[i + 112] +
                          (double)x[i + 128] + (double)x[i + 144] )*MainFormSLS->hh[10*i];
     sum_10 += a;
     }
  double ampl_10 = sqrt(pow(sum_10.real(),2) + pow(sum_10.imag(),2));
  TFreqComp freq_comp_10;
  freq_comp_10.ampl = ampl_10;
  freq_comp_10.freq = 10;


  complex<double> sum_16(0,0);
  int sz_16 = sz_x/16;
  for(int i=0;i<sz_16;i++) //16-я гарм - 800 Hz
     {
     complex<double> a = ((double)x[i]        + (double)x[i +  10] + (double)x[i +  20] + (double)x[i +  30]  +
                          (double)x[i +  40]  + (double)x[i +  50] + (double)x[i +  60] + (double)x[i +  70]  +
                          (double)x[i +  80]  + (double)x[i +  90] + (double)x[i + 100] + (double)x[i + 110]  +
                          (double)x[i + 120]  + (double)x[i + 130] + (double)x[i + 140] + (double)x[i + 150]) *
                          MainFormSLS->hh[16*i];
     sum_16 += a;
     }
  double ampl_16 = sqrt(pow(sum_16.real(),2) + pow(sum_16.imag(),2));
  TFreqComp freq_comp_16;
  freq_comp_16.ampl = ampl_16;
  freq_comp_16.freq = 16;


  /*
  complex<double> sum_16_1(0,0); // for test only
  for(int i=0;i<sz_x;i++)
     {
     complex<double> w(cos(2*M_PI*i*16/160),-sin(2*M_PI*i*16/160));
     complex<double> a = (double)x[i]*w;
     sum_16_1 += a;
     }
 double ampl_16_1 = sqrt(pow(sum_16_1.real(),2) + pow(sum_16_1.imag(),2));
  */

  complex<double> sum_20(0,0);
  int sz_20 = sz_x/20;
  for(int i=0;i<sz_20;i++) //20-я гарм - 1000 Hz
     {
     complex<double> a = ((double)x[i]       + (double)x[i + 8]   + (double)x[i + 16]  + (double)x[i + 24]  +
                          (double)x[i + 32]  + (double)x[i + 40]  + (double)x[i + 48]  + (double)x[i + 56]  +
                          (double)x[i + 64]  + (double)x[i + 72]  + (double)x[i + 80]  + (double)x[i + 88]  +
                          (double)x[i + 96]  + (double)x[i + 104] + (double)x[i + 112] + (double)x[i + 120] +
                          (double)x[i + 128] + (double)x[i + 136] + (double)x[i + 144] + (double)x[i + 152])*
                          MainFormSLS->hh[20*i];

     sum_20 += a;
     }
  double ampl_20 = sqrt(pow(sum_20.real(),2) + pow(sum_20.imag(),2));
  TFreqComp freq_comp_20;
  freq_comp_20.ampl = ampl_20;
  freq_comp_20.freq = 20;

  complex<double> sum_32(0,0);
  int sz_32 = sz_x/32;
  for(int i=0;i<sz_32;i++) //32-я гарм - 1600 Hz
     {
     complex<double> a = ((double)x[i]        + (double)x[i +   5] + (double)x[i +  10] + (double)x[i +  15]  +
                          (double)x[i +  20]  + (double)x[i +  25] + (double)x[i +  30] + (double)x[i +  35]  +
                          (double)x[i +  40]  + (double)x[i +  45] + (double)x[i +  50] + (double)x[i +  55]  +
                          (double)x[i +  60]  + (double)x[i +  65] + (double)x[i +  70] + (double)x[i +  75]  +
                          (double)x[i +  80]  + (double)x[i +  85] + (double)x[i +  90] + (double)x[i +  95]  +
                          (double)x[i + 100]  + (double)x[i + 105] + (double)x[i + 110] + (double)x[i + 115]  +
                          (double)x[i + 120]  + (double)x[i + 125] + (double)x[i + 130] + (double)x[i + 135]  +
                          (double)x[i + 140]  + (double)x[i + 145] + (double)x[i + 150] + (double)x[i + 155]) *
                          MainFormSLS->hh[32*i];
     sum_32 += a;
     }
  double ampl_32 = sqrt(pow(sum_32.real(),2) + pow(sum_32.imag(),2));
  TFreqComp freq_comp_32;
  freq_comp_32.ampl = ampl_32;
  freq_comp_32.freq = 32;

  complex<double> sum_40(0,0);
  int sz_40 = sz_x/40;
  for(int i=0;i<sz_40;i++) //40-я гарм - 2000 Hz
     {
     complex<double> a = ((double)x[i]       + (double)x[i + 4]   + (double)x[i + 8]   + (double)x[i + 12]  +
                          (double)x[i + 16]  + (double)x[i + 20]  + (double)x[i + 24]  + (double)x[i + 28]  +
                          (double)x[i + 32]  + (double)x[i + 36]  + (double)x[i + 40]  + (double)x[i + 44]  +
                          (double)x[i + 48]  + (double)x[i + 52]  + (double)x[i + 56]  + (double)x[i + 60]  +
                          (double)x[i + 64]  + (double)x[i + 68]  + (double)x[i + 72]  + (double)x[i + 76]  +
                          (double)x[i + 80]  + (double)x[i + 84]  + (double)x[i + 88]  + (double)x[i + 92]  +
                          (double)x[i + 96]  + (double)x[i + 100] + (double)x[i + 104] + (double)x[i + 108] +
                          (double)x[i + 112] + (double)x[i + 116] + (double)x[i + 120] + (double)x[i + 124] +
                          (double)x[i + 128] + (double)x[i + 132] + (double)x[i + 136] + (double)x[i + 140] +
                          (double)x[i + 144] + (double)x[i + 148] + (double)x[i + 152] + (double)x[i + 156])*
                          MainFormSLS->hh[40*i];
     sum_40 += a;
     }
  double ampl_40 = sqrt(pow(sum_40.real(),2) + pow(sum_40.imag(),2));
  TFreqComp freq_comp_40;
  freq_comp_40.ampl = ampl_40;
  freq_comp_40.freq = 40;

  if(ampl_10 > 0.0)
    {
    if(ampl_16 > 0.0)
       freq_comp_16.rs_16_10 = ampl_10/ampl_16;
    if(ampl_20 > 0.0)
       freq_comp_20.rs_20_10 = ampl_10/ampl_20;
    if(ampl_40 > 0.0)
       freq_comp_40.rs_40_10 = ampl_10/ampl_40;
    }
  sfi.fcl.insert(TFreqCompList::value_type(ampl_10,freq_comp_10));
  sfi.fcl.insert(TFreqCompList::value_type(ampl_16,freq_comp_16));
  sfi.fcl.insert(TFreqCompList::value_type(ampl_20,freq_comp_20));
  sfi.fcl.insert(TFreqCompList::value_type(ampl_32,freq_comp_32));
  sfi.fcl.insert(TFreqCompList::value_type(ampl_40,freq_comp_40));


  if((TTest_Sound->MicLog->Checked)||(TTest_Sound->SoundLog->Checked))
    {
    string timestr;
    TDateTime dt = dt.CurrentTime();
    exsTime( dt,timestr);
    string s = "\n\n" + timestr;
    if(vt == TVolume_Type__Mic)
     if(TTest_Sound->MicLog->Checked)
       {
       s += " microphone";
       s += "\n50  Hz: "  + (string)FloatToStr(ampl_1).c_str()   +
           // "\n100 Hz: "  + (string)FloatToStr(ampl_2).c_str() +
           // "\n200 Hz: "  + (string)FloatToStr(ampl_4).c_str() +
            "\n500 Hz: "  + (string)FloatToStr(ampl_10).c_str()+
            "\n800 Hz: "  + (string)FloatToStr(ampl_16).c_str()+  /*" " + FloatToStr(ampl_16_1).c_str() + */
            "\n1000 Hz: " + (string)FloatToStr(ampl_20).c_str()+
            "\n1600 Hz: " + (string)FloatToStr(ampl_32).c_str()+
            "\n2000 Hz: " + (string)FloatToStr(ampl_40).c_str();
       BT->wave_log(s);
       }
     if(vt == TVolume_Type__Sound)
      if(TTest_Sound->SoundLog->Checked)
        {
        s += " sound";
        s += "\n50  Hz: "  + (string)FloatToStr(ampl_1).c_str() +
            // "\n100 Hz: "  + (string)FloatToStr(ampl_2).c_str() +
            // "\n200 Hz: "  + (string)FloatToStr(ampl_4).c_str() +
             "\n500 Hz: "  + (string)FloatToStr(ampl_10).c_str()+
             "\n800 Hz: "  + (string)FloatToStr(ampl_16).c_str()+  /*" " + FloatToStr(ampl_16_1).c_str() +   */
             "\n1000 Hz: " + (string)FloatToStr(ampl_20).c_str()+
             "\n1600 Hz: " + (string)FloatToStr(ampl_32).c_str()+
             "\n2000 Hz: " + (string)FloatToStr(ampl_40).c_str();
        BT->wave_log(s);
        }
    }
  }
}
//-----------------------------------------------------------------------------
/*
void __fastcall TVolume::dft_1(TWaveBaseThread* BT,TOutPutUdpBlock* opb,TSampleFreqImage& sfi)
{
int sz = opb->v.size();
if(sz)
  {
  vector<short> x; //отсчеты на входе фильтра
  ubyte_2_short(x,opb->v,sz);
  int sz_x = x.size();
  complex<double> sum_1(0,0);
  for(int i=0;i<sz_x;i++)   //1-я гарм - 50 Hz
     {
     complex<double> a = ((double)x[i])*MainFormSLS->hh[i];
     sum_1 += a;
     }



    TCoeff_By_2 c2;
    ddft_by_2(x,c2);

   TCoeff_By_5 c5;
   ddft_by_5(x,c5);


  complex<double> sum_6(0,0);
  int sz_6 = sz_x/6 + 1;
  for(int i=0;i<80;i++) //6-я гарм - 300 Hz
     {
     complex<double> a = 0.0;
     if(i < sz_6)   // < 27
       {
       a = ((double)x[i] + (double)x[i + 80])*MainFormSLS->hh[6*i];
       sum_6 += a;
       continue;
       }
     if(i < (2*sz_6))  //27 - 53
       {
       a = ((double)x[i] + (double)x[i + 80])*MainFormSLS->hh[6*i - 160];
       sum_6 += a;
       continue;
       }
     if(i <= (3*sz_6)) //54 - 80
       {
       a = ((double)x[i] + (double)x[i + 80])*MainFormSLS->hh[6*i - 320];
       sum_6 += a;
       continue;
       }

     sum_6 += a;
     }



  complex<double> sum_8(0,0);
  int sz_8 = sz_x/8;
  for(int i=0;i<sz_8;i++) //8-я гарм - 400 Hz
     {
     complex<double> a = ((double)x[i]        + (double)x[i +  20] +  (double)x[i +  40] + (double)x[i +  60] +
                          (double)x[i +  80]  + (double)x[i + 100] +  (double)x[i + 120] + (double)x[i + 140])*
                          MainFormSLS->hh[8*i];
     sum_8 += a;
     }


  complex<double> sum_11(0,0); //11-я гарм - 550 Hz
  ddft_11(x,sum_11);


  complex<double> sum_16(0,0);
  int sz_16 = sz_x/16;
  for(int i=0;i<sz_16;i++) //16-я гарм - 800 Hz
     {
     complex<double> a = ((double)x[i]        + (double)x[i +  10] + (double)x[i +  20] + (double)x[i +  30]  +
                          (double)x[i +  40]  + (double)x[i +  50] + (double)x[i +  60] + (double)x[i +  70]  +
                          (double)x[i +  80]  + (double)x[i +  90] + (double)x[i + 100] + (double)x[i + 110]  +
                          (double)x[i + 120]  + (double)x[i + 130] + (double)x[i + 140] + (double)x[i + 150]) *
                          MainFormSLS->hh[16*i];
     sum_16 += a;
     }



  complex<double> sum_22(0,0); //22-я гарм - 1100 Hz
  ddft_22(x,sum_22);


  complex<double> sum_32(0,0);
  int sz_32 = sz_x/32;
  for(int i=0;i<sz_32;i++) //32-я гарм - 1600 Hz
     {
     complex<double> a = ((double)x[i]        + (double)x[i +   5] + (double)x[i +  10] + (double)x[i +  15]  +
                          (double)x[i +  20]  + (double)x[i +  25] + (double)x[i +  30] + (double)x[i +  35]  +
                          (double)x[i +  40]  + (double)x[i +  45] + (double)x[i +  50] + (double)x[i +  55]  +
                          (double)x[i +  60]  + (double)x[i +  65] + (double)x[i +  70] + (double)x[i +  75]  +
                          (double)x[i +  80]  + (double)x[i +  85] + (double)x[i +  90] + (double)x[i +  95]  +
                          (double)x[i + 100]  + (double)x[i + 105] + (double)x[i + 110] + (double)x[i + 115]  +
                          (double)x[i + 120]  + (double)x[i + 125] + (double)x[i + 130] + (double)x[i + 135]  +
                          (double)x[i + 140]  + (double)x[i + 145] + (double)x[i + 150] + (double)x[i + 155]) *
                          MainFormSLS->hh[32*i];
     sum_32 += a;
     }


     complex<double> sum_44(0,0); //44-я гарм - 2200 Hz
     ddft_44(x,sum_44);




  if((TTest_Sound->MicLog->Checked)||(TTest_Sound->SoundLog->Checked))
    {
    string timestr;
    TDateTime dt = dt.CurrentTime();
    exsTime( dt,timestr);
    string s = "\n\n" + timestr;
    if(vt == TVolume_Type__Mic)
     if(TTest_Sound->MicLog->Checked)
       {
       s += " microphone";
       s += "\n50  Hz: "  + (string)FloatToStr(sum_1.real()).c_str()   +  " i" + (string)FloatToStr(sum_1.imag()).c_str() +
            "\n100 Hz: "  + (string)FloatToStr(c2.sum_2.real()).c_str()   +  " i" + (string)FloatToStr(c2.sum_2.imag()).c_str() +
            "\n200 Hz: "  + (string)FloatToStr(c2.sum_4.real()).c_str()   +  " i" + (string)FloatToStr(c2.sum_4.imag()).c_str() +
            "\n300 Hz: "  + (string)FloatToStr(sum_6.real()).c_str()   +  " i" + (string)FloatToStr(sum_6.imag()).c_str() +
            "\n500 Hz: "  + (string)FloatToStr(c5.sum_10.real()).c_str()+  " i" + (string)FloatToStr(c5.sum_10.imag()).c_str() +
            "\n800 Hz: "  + (string)FloatToStr(sum_16.real()).c_str()   +  " i" + (string)FloatToStr(sum_16.imag()).c_str() +
            "\n1000 Hz: " + (string)FloatToStr(c5.sum_20.real()).c_str()   +  " i" + (string)FloatToStr(c5.sum_20.imag()).c_str() +
            "\n1500 Hz: " + (string)FloatToStr(c5.sum_30.real()).c_str()   +  " i" + (string)FloatToStr(c5.sum_30.imag()).c_str() +
            "\n1600 Hz: " + (string)FloatToStr(sum_32.real()).c_str()   +  " i" + (string)FloatToStr(sum_32.imag()).c_str() +
            "\n2000 Hz: " + (string)FloatToStr(c5.sum_40.real()).c_str()   +  " i" + (string)FloatToStr(c5.sum_40.imag()).c_str();
       BT->wave_log(s);
       }
     if(vt == TVolume_Type__Sound)
      if(TTest_Sound->SoundLog->Checked)
        {
        s += " sound";
       s += "\n50  Hz: "  + (string)FloatToStr(sum_1.real()).c_str()   +  " i" + (string)FloatToStr(sum_1.imag()).c_str() +
            "\n100 Hz: "  + (string)FloatToStr(c2.sum_2.real()).c_str()   +  " i" + (string)FloatToStr(c2.sum_2.imag()).c_str() +
            "\n200 Hz: "  + (string)FloatToStr(c2.sum_4.real()).c_str()   +  " i" + (string)FloatToStr(c2.sum_4.imag()).c_str() +
            "\n250 Hz: "  + (string)FloatToStr(c5.sum_5.real()).c_str()   +  " i" + (string)FloatToStr(c5.sum_5.imag()).c_str() +
            "\n300 Hz: "  + (string)FloatToStr(sum_6.real()).c_str()   +  " i" + (string)FloatToStr(sum_6.imag()).c_str() +
            "\n400 Hz: "  + (string)FloatToStr(sum_8.real()).c_str()   +  " i" + (string)FloatToStr(sum_8.imag()).c_str() +
            "\n500 Hz: "  + (string)FloatToStr(c5.sum_10.real()).c_str()   +  " i" + (string)FloatToStr(c5.sum_10.imag()).c_str() +
            "\n550 Hz: "  + (string)FloatToStr(sum_11.real()).c_str()   +  " i" + (string)FloatToStr(sum_11.imag()).c_str() +
            "\n750 Hz: "  + (string)FloatToStr(c5.sum_15.real()).c_str()   +  " i" + (string)FloatToStr(c5.sum_15.imag()).c_str() +
            "\n800 Hz: "  + (string)FloatToStr(sum_16.real()).c_str()   +  " i" + (string)FloatToStr(sum_16.imag()).c_str() +
            "\n1000 Hz: " + (string)FloatToStr(c5.sum_20.real()).c_str()   +  " i" + (string)FloatToStr(c5.sum_20.imag()).c_str() +
            "\n1250 Hz: " + (string)FloatToStr(c5.sum_25.real()).c_str()   +  " i" + (string)FloatToStr(c5.sum_25.imag()).c_str() +
            "\n1100 Hz: " + (string)FloatToStr(sum_22.real()).c_str()   +  " i" + (string)FloatToStr(sum_22.imag()).c_str() +
            "\n1500 Hz: " + (string)FloatToStr(c5.sum_30.real()).c_str()   +  " i" + (string)FloatToStr(c5.sum_30.imag()).c_str() +
            "\n1750 Hz: " + (string)FloatToStr(c5.sum_35.real()).c_str()   +  " i" + (string)FloatToStr(c5.sum_35.imag()).c_str() +
            "\n1600 Hz: " + (string)FloatToStr(sum_32.real()).c_str()   +  " i" + (string)FloatToStr(sum_32.imag()).c_str() +
            "\n2000 Hz: " + (string)FloatToStr(c5.sum_40.real()).c_str()   +  " i" + (string)FloatToStr(c5.sum_40.imag()).c_str() +
            "\n2200 Hz: " + (string)FloatToStr(sum_44.real()).c_str()   +  " i" + (string)FloatToStr(sum_44.imag()).c_str() +
            "\n2250 Hz: " + (string)FloatToStr(c5.sum_45.real()).c_str()   +  " i" + (string)FloatToStr(c5.sum_45.imag()).c_str() +
            "\n2500 Hz: " + (string)FloatToStr(c5.sum_50.real()).c_str()   +  " i" + (string)FloatToStr(c5.sum_50.imag()).c_str() +
            "\n2750 Hz: " + (string)FloatToStr(c5.sum_55.real()).c_str()   +  " i" + (string)FloatToStr(c5.sum_55.imag()).c_str() +
            "\n3000 Hz: " + (string)FloatToStr(c5.sum_60.real()).c_str()   +  " i" + (string)FloatToStr(c5.sum_60.imag()).c_str() +
            "\n3250 Hz: " + (string)FloatToStr(c5.sum_65.real()).c_str()   +  " i" + (string)FloatToStr(c5.sum_65.imag()).c_str() +
            "\n3500 Hz: " + (string)FloatToStr(c5.sum_70.real()).c_str()   +  " i" + (string)FloatToStr(c5.sum_70.imag()).c_str();
       BT->wave_log(s);
       }
    }


  vector<complex<double> > out; //выходные отсчеты
  vector<double> out_double; //выходные отсчеты
  vector<short> out_short; //выходные отсчеты
  vector<UBYTE> out_ubyte; //выходные отсчеты
  int N = 160;
  for(int i=0; i<N; i++ )
     {
      int idx_2 = i*2;
      if(idx_2 >= N)
         idx_2 = idx_2%N;
      int idx_4 = i*4;
      if(idx_4 >= N)
         idx_4 = idx_4%N;

      int idx_5 = i*5;
      if(idx_5 >= N)
         idx_5 = idx_5%N;

      int idx_6 = i*6;
      if(idx_6 >= N)
         idx_6 = idx_6%N;

      int idx_8 = i*8;
      if(idx_8 >= N)
         idx_8 = idx_8%N;

      int idx_10 = i*10;
      if(idx_10 >= N)
         idx_10 = idx_10%N;
      int idx_11 = i*11;
      if(idx_11 >= N)
         idx_11 = idx_11%N;
      int idx_15 = i*15;
      if(idx_15 >= N)
         idx_15 = idx_15%N;

      int idx_16 = i*16;
      if(idx_16 >= N)
         idx_16 = idx_16%N;
      int idx_20 = i*20;
      if(idx_20 >= N)
         idx_20 = idx_20%N;

      int idx_22 = i*22;
      if(idx_22 >= N)
         idx_22 = idx_22%N;

      int idx_25 = i*25;
      if(idx_25 >= N)
         idx_25 = idx_25%N;

      int idx_30 = i*30;
      if(idx_30 >= N)
         idx_30 = idx_30%N;

      int idx_32 = i*32;
      if(idx_32 >= N)
         idx_32 = idx_32%N;

      int idx_35 = i*35;
      if(idx_35 >= N)
         idx_35 = idx_35%N;

      int idx_40 = i*40;
      if(idx_40 >= N)
         idx_40 = idx_40%N;

      int idx_44 = i*44;
      if(idx_44 >= N)
         idx_44 = idx_44%N;

      int idx_45 = i*45;
      if(idx_45 >= N)
         idx_45 = idx_45%N;

      int idx_50 = i*50;
      if(idx_50 >= N)
         idx_50 = idx_50%N;

      int idx_55 = i*55;
      if(idx_55 >= N)
         idx_55 = idx_55%N;

      int idx_60 = i*60;
      if(idx_60 >= N)
         idx_60 = idx_60%N;

      int idx_65 = i*65;
      if(idx_65 >= N)
         idx_65 = idx_65%N;
      int idx_70 = i*70;
      if(idx_70 >= N)
         idx_70 = idx_70%N;

      complex<double > s = sum_1*MainFormSLS->hh_1[i] +
                           c2.sum_2*MainFormSLS->hh_1[idx_2]   + c2.sum_4*MainFormSLS->hh_1[idx_4]   +
                           c5.sum_5*MainFormSLS->hh_1[idx_5]   +
                           sum_6*MainFormSLS->hh_1[idx_6]      + sum_8*MainFormSLS->hh_1[idx_8]   +
                           c5.sum_10*MainFormSLS->hh_1[idx_10] + sum_11*MainFormSLS->hh_1[idx_11] +
                           c5.sum_15*MainFormSLS->hh_1[idx_15] + sum_16*MainFormSLS->hh_1[idx_16] +
                           c5.sum_20*MainFormSLS->hh_1[idx_20] + sum_22*MainFormSLS->hh_1[idx_22] +
                           c5.sum_25*MainFormSLS->hh_1[idx_25] + c5.sum_30*MainFormSLS->hh_1[idx_30] +
                           sum_32*MainFormSLS->hh_1[idx_32]    + c5.sum_35*MainFormSLS->hh_1[idx_35] +
                           c5.sum_40*MainFormSLS->hh_1[idx_40] +
                           sum_44*MainFormSLS->hh_1[idx_44]    + c5.sum_45*MainFormSLS->hh_1[idx_45] +
                           c5.sum_50*MainFormSLS->hh_1[idx_50] + c5.sum_55*MainFormSLS->hh_1[idx_55] +
                           c5.sum_60*MainFormSLS->hh_1[idx_60] + c5.sum_65*MainFormSLS->hh_1[idx_65] +
                           c5.sum_70*MainFormSLS->hh_1[idx_70];
      s/=40;
      out.push_back(s);
     }
  for(int i=0; i<N; i++ )
     {
     complex<double > s = out[i];

     if(TTest_Sound->sqrt->Checked)
       {
       double ampl = sqrt(pow(s.real(),2) + pow(s.imag(),2));
       out_double.push_back(ampl);
       }
     else
       out_double.push_back(s.real());
     }
  double_2_short(out_short,out_double,N,false);
  short_2_ubyte(out_ubyte,out_short,N);
  opb->v = out_ubyte;
  }
}
*/
//------------------------------------------------------------------------------
#ifdef Full_Fourie_Transform
void __fastcall TVolume::dft_full(TWaveBaseThread* BT,TOutPutUdpBlock* opb,TSampleFreqImage& sfi)
{
try{
int sz = opb->v.size();
if(sz)
  {
  vector<short> x; //отсчеты на входе фильтра
  ubyte_2_short(x,opb->v,sz);
  int sz_x = x.size();
  int sz_x_2 = sz_x/2;

  complex<double> sum_0(0,0);
  for(int i=0;i<sz_x;i++)
     {
     complex<double> w(1,0);
     complex<double> a = (double)x[i]*w;
     sum_0 += a;
     }

  TCoeff_BY_2 c2(sz_x_2);
  dfft_even(x,MainFormSLS->hh,c2);     //Прямое преобразование Фурье для четных отсчетов
  c2.v[0] = sum_0;


  int sz_even_2 = c2.v.size()/2;
  for(int i=TTest_Sound->Left_Margin; i<sz_even_2; i++)
 //   for(int i=1;i<sz_even_2;i++)
     {
     TFreqComp fc;
     fc.sum_xx = c2.v[i];
     fc.ampl   = abs(c2.v[i].real()) + abs(c2.v[i].imag());
    // fc.ampl   = sqrt(c2.v[i].real()*c2.v[i].real() + c2.v[i].imag()*c2.v[i].imag());
   //  fc.ampl   = c2.v[i].real();
     fc.freq   = 2*i;
     sfi.insert(fc);
     }

  TCoeff_BY_2 c1(sz_x_2);
  dfft_odd(x,MainFormSLS->hh,c1); //Прямое преобразование Фурье для нечетных отсчетов

  /*
  int sz_odd_2 = c1.v.size()/2;
  for(int i=0;i<sz_odd_2;i++)
     {
     TFreqComp fc;
     fc.sum_xx = c1.v[i];
     //fc.ampl   = abs(c1.v[i].real()) + abs(c1.v[i].imag());
     fc.ampl   = sqrt(c1.v[i].real()*c1.v[i].real() + c1.v[i].imag()*c1.v[i].imag());
     fc.freq   = 2*i + 1;
     sfi.insert(fc);
     }
   */
      /*
     TFreqComp freq_comp_15;
     freq_comp_15.freq = 15;
     freq_comp_15.sum_xx = c1.v[7];

     TFreqComp freq_comp_20;
     freq_comp_20.freq = 20;
     freq_comp_20.sum_xx = c2.v[10];

     TFreqComp freq_comp_22;
     freq_comp_22.freq = 22;
     freq_comp_22.sum_xx = c2.v[11];

     TFreqComp freq_comp_32;
     freq_comp_32.freq = 32;
     freq_comp_32.sum_xx = c2.v[16];

     TFreqComp freq_comp_40;
     freq_comp_40.freq = 40;
     freq_comp_40.sum_xx = c2.v[20];

    // sfi.v.push_back(freq_comp_10);
     sfi.v.push_back(freq_comp_15);
     sfi.v.push_back(freq_comp_20);
     sfi.v.push_back(freq_comp_22);
     sfi.v.push_back(freq_comp_32);
    // sfi.v.push_back(freq_comp_35);
     sfi.v.push_back(freq_comp_40);
      */

  TFreqCompList::reverse_iterator it = sfi.fcl.rbegin();
  while(it != sfi.fcl.rend())
       {
       TFreqComp fq = (*it).second;
       sfi.smax_ampl += inttostr(fq.freq) + ",";
       sfi.imax_ampl.push_back(fq.freq);
       sfi.v.push_back(fq);
       if(sfi.imax_ampl.size() == (unsigned)TTest_Sound->freq_number)
         break;
       it++;
       }
  sfi.smax_ampl += "\n";

  if(vt == TVolume_Type__Mic)
    {
    if(TTest_Sound->mic_dft_full_log->Checked)
      {
      string s = "\nsummary mic\n" ;
      TFreqCompList::reverse_iterator it = sfi.fcl.rbegin();
      int i=0;
      while(it != sfi.fcl.rend())
           {
           if(i++ > 10)
             break;
           TFreqComp fq = (*it).second;
           s += "f = " + inttostr(fq.freq) + " amp = " + FloatToStr(fq.ampl).c_str() + "\n";
           it++;
           }
      BT->wave_log(s);
      }
    }
  else if(vt == TVolume_Type__Sound)
    {
    if(TTest_Sound->sound_dft_full_log->Checked)
      {
      string s = "\nsummary sound\n" ;
      TFreqCompList::reverse_iterator it = sfi.fcl.rbegin();
      int i=0;
      while(it != sfi.fcl.rend())
           {
           if(i++ > 10)
             break;
           TFreqComp fq = (*it).second;
           s += "f = " + inttostr(fq.freq) + " amp = " + FloatToStr(fq.ampl).c_str() + "\n";
           it++;
           }
      BT->wave_log(s);
      }
    }
  }
}//try
catch(Exception& e){exsSstEXCEPTION(MainFormSLS->ofs->elt,"__TVolume::dft_full",e);}
}
#endif
//------------------------------------------------------------------------------
void __fastcall TVolume::dft_2(TWaveBaseThread* BT,TOutPutUdpBlock* opb,TSampleFreqImage& sfi)
{
int sz = opb->v.size();
if(sz)
  {
  vector<short> x; //отсчеты на входе фильтра
  ubyte_2_short(x,opb->v,sz);
  int sz_x = x.size();

  complex<double> sum_1(0,0);
  for(int i=0;i<sz_x;i++)   //1-я гарм - 50 Hz
     {
     complex<double> a = ((double)x[i])*MainFormSLS->hh[i];
     sum_1 += a;
     }

                     /*
                     sum_2 //100
                     sum_4 //200
                     */

    TCoeff_By_2 c2;
    ddft_by_2(x,c2);

                        /*
                        sum_5   //250  Hz
                        sum_10  //500  Hz
                        sum_15  //750  Hz
                        sum_20  //1000 Hz
                        sum_25  //1250 Hz
                        sum_30  //1500 Hz
                        sum_35  //1750 Hz
                        sum_40  //2000 Hz
                        sum_45  //2250 Hz
                        sum_50  //2500 Hz
                        sum_55  //2750 Hz
                        sum_60  //3000 Hz
                        sum_65  //3250 Hz
                        sum_70  //3500 Hz
                          */

   TCoeff_By_5 c5;
   ddft_by_5(x,c5);

  complex<double> sum_6(0,0);
  int sz_6 = sz_x/6 + 1;
  for(int i=0;i<80;i++) //6-я гарм - 300 Hz
     {
     complex<double> a = 0.0;
     if(i < sz_6)   // < 27
       {
       a = ((double)x[i] + (double)x[i + 80])*MainFormSLS->hh[6*i];
       sum_6 += a;
       continue;
       }
     if(i < (2*sz_6))  //27 - 53
       {
       a = ((double)x[i] + (double)x[i + 80])*MainFormSLS->hh[6*i - 160];
       sum_6 += a;
       continue;
       }
     if(i <= (3*sz_6)) //54 - 80
       {
       a = ((double)x[i] + (double)x[i + 80])*MainFormSLS->hh[6*i - 320];
       sum_6 += a;
       continue;
       }

     sum_6 += a;
     }

  complex<double> sum_8(0,0);
  int sz_8 = sz_x/8;
  for(int i=0;i<sz_8;i++) //8-я гарм - 400 Hz
     {
     complex<double> a = ((double)x[i]        + (double)x[i +  20] +  (double)x[i +  40] + (double)x[i +  60] +
                          (double)x[i +  80]  + (double)x[i + 100] +  (double)x[i + 120] + (double)x[i + 140])*
                          MainFormSLS->hh[8*i];
     sum_8 += a;
     }


  complex<double> sum_11(0,0); //11-я гарм - 550 Hz
  ddft_11(x,sum_11);


  complex<double> sum_16(0,0);
  int sz_16 = sz_x/16;
  for(int i=0;i<sz_16;i++) //16-я гарм - 800 Hz
     {
     complex<double> a = ((double)x[i]        + (double)x[i +  10] + (double)x[i +  20] + (double)x[i +  30]  +
                          (double)x[i +  40]  + (double)x[i +  50] + (double)x[i +  60] + (double)x[i +  70]  +
                          (double)x[i +  80]  + (double)x[i +  90] + (double)x[i + 100] + (double)x[i + 110]  +
                          (double)x[i + 120]  + (double)x[i + 130] + (double)x[i + 140] + (double)x[i + 150]) *
                          MainFormSLS->hh[16*i];
     sum_16 += a;
     }



  complex<double> sum_22(0,0); //22-я гарм - 1100 Hz
  ddft_22(x,sum_22);


  complex<double> sum_32(0,0);
  int sz_32 = sz_x/32;
  for(int i=0;i<sz_32;i++) //32-я гарм - 1600 Hz
     {
     complex<double> a = ((double)x[i]        + (double)x[i +   5] + (double)x[i +  10] + (double)x[i +  15]  +
                          (double)x[i +  20]  + (double)x[i +  25] + (double)x[i +  30] + (double)x[i +  35]  +
                          (double)x[i +  40]  + (double)x[i +  45] + (double)x[i +  50] + (double)x[i +  55]  +
                          (double)x[i +  60]  + (double)x[i +  65] + (double)x[i +  70] + (double)x[i +  75]  +
                          (double)x[i +  80]  + (double)x[i +  85] + (double)x[i +  90] + (double)x[i +  95]  +
                          (double)x[i + 100]  + (double)x[i + 105] + (double)x[i + 110] + (double)x[i + 115]  +
                          (double)x[i + 120]  + (double)x[i + 125] + (double)x[i + 130] + (double)x[i + 135]  +
                          (double)x[i + 140]  + (double)x[i + 145] + (double)x[i + 150] + (double)x[i + 155]) *
                          MainFormSLS->hh[32*i];
     sum_32 += a;
     }


     complex<double> sum_44(0,0); //44-я гарм - 2200 Hz
     ddft_44(x,sum_44);

     TFreqComp freq_comp_10;
     freq_comp_10.freq = 10;
     freq_comp_10.sum_xx = c5.sum_10;

     TFreqComp freq_comp_15;
     freq_comp_15.freq = 15;
     freq_comp_15.sum_xx = c5.sum_15;

     TFreqComp freq_comp_20;
     freq_comp_20.freq = 20;
     freq_comp_20.sum_xx = c5.sum_20;

     TFreqComp freq_comp_22;
     freq_comp_22.freq = 22;
     freq_comp_22.sum_xx = sum_22;

     TFreqComp freq_comp_32;
     freq_comp_32.freq = 32;
     freq_comp_32.sum_xx = sum_32;

     TFreqComp freq_comp_35;
     freq_comp_35.freq = 35;
     freq_comp_35.sum_xx = c5.sum_35;

     TFreqComp freq_comp_40;
     freq_comp_40.freq = 40;
     freq_comp_40.sum_xx = c5.sum_40;

    // sfi.v.push_back(freq_comp_10);
     sfi.v.push_back(freq_comp_15);
     sfi.v.push_back(freq_comp_20);
     sfi.v.push_back(freq_comp_22);
     sfi.v.push_back(freq_comp_32);
    // sfi.v.push_back(freq_comp_35);
     sfi.v.push_back(freq_comp_40);
    // sfi.fcl.insert(TFreqCompList::value_type(ampl_16,freq_comp_16));
    // sfi.fcl.insert(TFreqCompList::value_type(ampl_20,freq_comp_20));
    // sfi.fcl.insert(TFreqCompList::value_type(ampl_32,freq_comp_32));
    // sfi.fcl.insert(TFreqCompList::value_type(ampl_40,freq_comp_40));


  if((TTest_Sound->MicLog->Checked)||(TTest_Sound->SoundLog->Checked))
    {
    string timestr;
    TDateTime dt = dt.CurrentTime();
    exsTime( dt,timestr);
    string s = "\n\n" + timestr;
    if(vt == TVolume_Type__Mic)
     if(TTest_Sound->MicLog->Checked)
       {
       s += " microphone";
       s += "\n50  Hz: "  + (string)FloatToStr(sum_1.real()).c_str()   +  " i" + (string)FloatToStr(sum_1.imag()).c_str() +
            "\n100 Hz: "  + (string)FloatToStr(c2.sum_2.real()).c_str()   +  " i" + (string)FloatToStr(c2.sum_2.imag()).c_str() +
            "\n200 Hz: "  + (string)FloatToStr(c2.sum_4.real()).c_str()   +  " i" + (string)FloatToStr(c2.sum_4.imag()).c_str() +
            "\n250 Hz: "  + (string)FloatToStr(c5.sum_5.real()).c_str()   +  " i" + (string)FloatToStr(c5.sum_5.imag()).c_str() +
            "\n300 Hz: "  + (string)FloatToStr(sum_6.real()).c_str()   +  " i" + (string)FloatToStr(sum_6.imag()).c_str() + /*" " + (string)FloatToStr(sum_6_1.real()).c_str()   +  " i" + (string)FloatToStr(sum_6_1.imag()).c_str() +*/
            "\n400 Hz: "  + (string)FloatToStr(sum_8.real()).c_str()   +  " i" + (string)FloatToStr(sum_8.imag()).c_str() + /*" " + (string)FloatToStr(sum_6_1.real()).c_str()   +  " i" + (string)FloatToStr(sum_6_1.imag()).c_str() +*/
            "\n500 Hz: "  + (string)FloatToStr(c5.sum_10.real()).c_str()   +  " i" + (string)FloatToStr(c5.sum_10.imag()).c_str() +
            "\n550 Hz: "  + (string)FloatToStr(sum_11.real()).c_str()   +  " i" + (string)FloatToStr(sum_11.imag()).c_str() + /*" " + (string)FloatToStr(sum_11_1.real()).c_str() +  " i" + (string)FloatToStr(sum_11_1.imag()).c_str() +*/
            "\n750 Hz: "  + (string)FloatToStr(c5.sum_15.real()).c_str()   +  " i" + (string)FloatToStr(c5.sum_15.imag()).c_str() +
            "\n800 Hz: "  + (string)FloatToStr(sum_16.real()).c_str()   +  " i" + (string)FloatToStr(sum_16.imag()).c_str() +
            "\n1000 Hz: " + (string)FloatToStr(c5.sum_20.real()).c_str()   +  " i" + (string)FloatToStr(c5.sum_20.imag()).c_str() +
            "\n1250 Hz: " + (string)FloatToStr(c5.sum_25.real()).c_str()   +  " i" + (string)FloatToStr(c5.sum_25.imag()).c_str() +
            "\n1100 Hz: " + (string)FloatToStr(sum_22.real()).c_str()   +  " i" + (string)FloatToStr(sum_22.imag()).c_str() + /*" " + (string)FloatToStr(sum_22_1.real()).c_str() +  " i" + (string)FloatToStr(sum_22_1.imag()).c_str() +*/
            "\n1500 Hz: " + (string)FloatToStr(c5.sum_30.real()).c_str()   +  " i" + (string)FloatToStr(c5.sum_30.imag()).c_str() +
            "\n1750 Hz: " + (string)FloatToStr(c5.sum_35.real()).c_str()   +  " i" + (string)FloatToStr(c5.sum_35.imag()).c_str() +
            "\n1600 Hz: " + (string)FloatToStr(sum_32.real()).c_str()   +  " i" + (string)FloatToStr(sum_32.imag()).c_str() +
            "\n2000 Hz: " + (string)FloatToStr(c5.sum_40.real()).c_str()   +  " i" + (string)FloatToStr(c5.sum_40.imag()).c_str() + /*" " + (string)FloatToStr(sum_40_1.real()).c_str() +  " i" + (string)FloatToStr(sum_40_1.imag()).c_str() +*/
            "\n2200 Hz: " + (string)FloatToStr(sum_44.real()).c_str()   +  " i" + (string)FloatToStr(sum_44.imag()).c_str() +  /*" " + (string)FloatToStr(sum_44_1.real()).c_str() +  " i" + (string)FloatToStr(sum_44_1.imag()).c_str(); */
            "\n2250 Hz: " + (string)FloatToStr(c5.sum_45.real()).c_str()   +  " i" + (string)FloatToStr(c5.sum_45.imag()).c_str() +
            "\n2500 Hz: " + (string)FloatToStr(c5.sum_50.real()).c_str()   +  " i" + (string)FloatToStr(c5.sum_50.imag()).c_str() +
            "\n2750 Hz: " + (string)FloatToStr(c5.sum_55.real()).c_str()   +  " i" + (string)FloatToStr(c5.sum_55.imag()).c_str() +
            "\n3000 Hz: " + (string)FloatToStr(c5.sum_60.real()).c_str()   +  " i" + (string)FloatToStr(c5.sum_60.imag()).c_str() +
            "\n3250 Hz: " + (string)FloatToStr(c5.sum_65.real()).c_str()   +  " i" + (string)FloatToStr(c5.sum_65.imag()).c_str() +
            "\n3500 Hz: " + (string)FloatToStr(c5.sum_70.real()).c_str()   +  " i" + (string)FloatToStr(c5.sum_70.imag()).c_str();
       BT->wave_log(s);
       }
     if(vt == TVolume_Type__Sound)
      if(TTest_Sound->SoundLog->Checked)
        {
        s += " sound";
       s += "\n50  Hz: "  + (string)FloatToStr(sum_1.real()).c_str()   +  " i" + (string)FloatToStr(sum_1.imag()).c_str() +
            "\n100 Hz: "  + (string)FloatToStr(c2.sum_2.real()).c_str()   +  " i" + (string)FloatToStr(c2.sum_2.imag()).c_str() +
            "\n200 Hz: "  + (string)FloatToStr(c2.sum_4.real()).c_str()   +  " i" + (string)FloatToStr(c2.sum_4.imag()).c_str() +
            "\n250 Hz: "  + (string)FloatToStr(c5.sum_5.real()).c_str()   +  " i" + (string)FloatToStr(c5.sum_5.imag()).c_str() +
            "\n300 Hz: "  + (string)FloatToStr(sum_6.real()).c_str()   +  " i" + (string)FloatToStr(sum_6.imag()).c_str() + /*" " + (string)FloatToStr(sum_6_1.real()).c_str()   +  " i" + (string)FloatToStr(sum_6_1.imag()).c_str() +*/
            "\n400 Hz: "  + (string)FloatToStr(sum_8.real()).c_str()   +  " i" + (string)FloatToStr(sum_8.imag()).c_str() + /*" " + (string)FloatToStr(sum_6_1.real()).c_str()   +  " i" + (string)FloatToStr(sum_6_1.imag()).c_str() +*/
            "\n500 Hz: "  + (string)FloatToStr(c5.sum_10.real()).c_str()   +  " i" + (string)FloatToStr(c5.sum_10.imag()).c_str() +
            "\n550 Hz: "  + (string)FloatToStr(sum_11.real()).c_str()   +  " i" + (string)FloatToStr(sum_11.imag()).c_str() + /*" " + (string)FloatToStr(sum_11_1.real()).c_str() +  " i" + (string)FloatToStr(sum_11_1.imag()).c_str() +*/
            "\n750 Hz: "  + (string)FloatToStr(c5.sum_15.real()).c_str()   +  " i" + (string)FloatToStr(c5.sum_15.imag()).c_str() +
            "\n800 Hz: "  + (string)FloatToStr(sum_16.real()).c_str()   +  " i" + (string)FloatToStr(sum_16.imag()).c_str() +
            "\n1000 Hz: " + (string)FloatToStr(c5.sum_20.real()).c_str()   +  " i" + (string)FloatToStr(c5.sum_20.imag()).c_str() +
            "\n1250 Hz: " + (string)FloatToStr(c5.sum_25.real()).c_str()   +  " i" + (string)FloatToStr(c5.sum_25.imag()).c_str() +
            "\n1100 Hz: " + (string)FloatToStr(sum_22.real()).c_str()   +  " i" + (string)FloatToStr(sum_22.imag()).c_str() + /*" " + (string)FloatToStr(sum_22_1.real()).c_str() +  " i" + (string)FloatToStr(sum_22_1.imag()).c_str() +*/
            "\n1500 Hz: " + (string)FloatToStr(c5.sum_30.real()).c_str()   +  " i" + (string)FloatToStr(c5.sum_30.imag()).c_str() +
            "\n1750 Hz: " + (string)FloatToStr(c5.sum_35.real()).c_str()   +  " i" + (string)FloatToStr(c5.sum_35.imag()).c_str() +
            "\n1600 Hz: " + (string)FloatToStr(sum_32.real()).c_str()   +  " i" + (string)FloatToStr(sum_32.imag()).c_str() +
            "\n2000 Hz: " + (string)FloatToStr(c5.sum_40.real()).c_str()   +  " i" + (string)FloatToStr(c5.sum_40.imag()).c_str() + /*" " + (string)FloatToStr(sum_40_1.real()).c_str() +  " i" + (string)FloatToStr(sum_40_1.imag()).c_str() +*/
            "\n2200 Hz: " + (string)FloatToStr(sum_44.real()).c_str()   +  " i" + (string)FloatToStr(sum_44.imag()).c_str() +  /*" " + (string)FloatToStr(sum_44_1.real()).c_str() +  " i" + (string)FloatToStr(sum_44_1.imag()).c_str(); */
            "\n2250 Hz: " + (string)FloatToStr(c5.sum_45.real()).c_str()   +  " i" + (string)FloatToStr(c5.sum_45.imag()).c_str() +
            "\n2500 Hz: " + (string)FloatToStr(c5.sum_50.real()).c_str()   +  " i" + (string)FloatToStr(c5.sum_50.imag()).c_str() +
            "\n2750 Hz: " + (string)FloatToStr(c5.sum_55.real()).c_str()   +  " i" + (string)FloatToStr(c5.sum_55.imag()).c_str() +
            "\n3000 Hz: " + (string)FloatToStr(c5.sum_60.real()).c_str()   +  " i" + (string)FloatToStr(c5.sum_60.imag()).c_str() +
            "\n3250 Hz: " + (string)FloatToStr(c5.sum_65.real()).c_str()   +  " i" + (string)FloatToStr(c5.sum_65.imag()).c_str() +
            "\n3500 Hz: " + (string)FloatToStr(c5.sum_70.real()).c_str()   +  " i" + (string)FloatToStr(c5.sum_70.imag()).c_str();
       BT->wave_log(s);
       }
    }

  }
}
//------------------------------------------------------------------------------
void __fastcall normalize(TCoeff_BY_2& c2)
{
if(TTest_Sound->Normal->Checked)
  return;
int even_freq_sz = c2.v.size();
if(TTest_Sound->Sin->Checked)
 {
 c2.N = 80;
 for(int i=0;i<even_freq_sz;i++)
     c2.v[i]*=MainFormSLS->sin_wind[i*2];
 }
else if(TTest_Sound->Blackman->Checked)
  {
  c2.N = 40;
  for(int i=0;i<even_freq_sz;i++)
     c2.v[i]*=MainFormSLS->blackman_wind[i*2];
  }
else if(TTest_Sound->Hann->Checked)
  {
  c2.N = 40;
  for(int i=0;i<even_freq_sz;i++)
     c2.v[i]*=MainFormSLS->hann_wind[i*2];
  }

}
//------------------------------------------------------------------------------
#ifdef Full_Fourie_Transform
void __fastcall TVolume::dft_1_1(TWaveBaseThread* BT,TOutPutUdpBlock* opb,TSampleFreqImage& sfi)
{
//разбор - сбор на гарм
int sz = opb->v.size();
if(sz)
  {
  vector<short> x; //отсчеты на входе фильтра
  ubyte_2_short(x,opb->v,sz);
  int sz_x = x.size();
  int sz_x_2 = sz_x/2;

  int short_sz = x.size();

 if(TTest_Sound->Log_In_Out->Checked)
    {
    string timestr;
    TDateTime dt = dt.CurrentTime();
    exsTime( dt,timestr);
    string short_str;
    if(TTest_Sound->Bound)
      {
      TTest_Sound->Bound = false;
      short_str = "\nBound\n";
      }
    if(vt == TVolume_Type__Mic)
       short_str += "mic ";
    else if(vt == TVolume_Type__Sound)
       short_str += "sound ";
    short_str += "in " + timestr + "\n";
    for(int i=0;i<short_sz;i++)
       //short_str += inttostr(x[i]) + ",";
         short_str += IntToHex(x[i],2).c_str() + (string)",";
    short_str+="\n";
    short_str+="sample_level = " + (string)FloatToStr(sfi.sum_pic_val).c_str() +
               " zero = "  + FloatToStr(sfi.freq_zero).c_str() +
               " max = "   + FloatToStr(sfi.abs_a_max).c_str() +
               " grad = "  + FloatToStr(sfi.gradient).c_str();
    short_str+=" zc = " + inttostr(sfi.zc);
    if(sfi.sum_pic_val > av.av_val)
       short_str+= " thresh";
    short_str += "\n";
    short_str+="prev_average_val = " + (string)FloatToStr(av.av_val).c_str() + "\n";
    if(mq.found)
      {
      short_str+= "voice!!!\n";
      TTest_Sound->voice_count++;
      TTest_Sound->Edit6->Text = TTest_Sound->voice_count;
      }

    TCoeff_BY_2 c2(sz_x_2);
    complex<double> sum_0(0,0); // for test only
    for(int i=0;i<sz_x;i++)
       {
       // complex<double> w(cos(2*M_PI*i*6/160),-sin(2*M_PI*i*6/160));
       complex<double> w(1,0);
       complex<double> a = (double)x[i]*w;
       sum_0 += a;
       }
    dfft_even(x,MainFormSLS->hh,c2);     //Прямое преобразование Фурье для четных отсчетов
    c2.v[0] = sum_0;
    normalize(c2);
    int sz_even_2 = c2.v.size()/2;
 // for(int i=30;i<sz_even_2;i++)
    for(int i=1;i<sz_even_2;i++)
       {
       TFreqComp fc;
       fc.sum_xx = c2.v[i];
       fc.ampl   = abs(c2.v[i].real()) + abs(c2.v[i].imag());
       // fc.ampl   = sqrt(c2.v[i].real()*c2.v[i].real() + c2.v[i].imag()*c2.v[i].imag());
       //  fc.ampl   = c2.v[i].real();
       fc.freq   = 2*i;
       sfi.insert(fc);
       }
    short_str += "freq\n";
    TFreqCompList::reverse_iterator it = sfi.fcl.rbegin();
    int i=0;
    while(it != sfi.fcl.rend())
         {
         if(i++ > 10)
           break;
         TFreqComp fq = (*it).second;
         short_str += "f = " + inttostr(fq.freq) + " amp = " + FloatToStr(fq.ampl).c_str() + "\n";
         it++;
         }



        /*
    short_str += "A_Law:\n";
    vector<short> a_law;
    for(int i=0;i<short_sz;i++)
       {
       UBYTE Ba = linear2alaw(x[i]);
       a_law.push_back(alaw2linear(Ba));
       }
    for(int i=0;i<short_sz;i++)
        short_str += IntToHex(a_law[i],2).c_str() + (string)",";
    short_str += "\n";
    */
    BT->wave_log(short_str);
    }
  mq.found = false;


    TCoeff_BY_2 c2(sz_x_2);
    TCoeff_BY_2 c1(sz_x_2);
    if(TTest_Sound->FourieTransform->Checked)
      {
      complex<double> sum_0(0,0); // for test only
      for(int i=0;i<sz_x;i++)
         {
         // complex<double> w(cos(2*M_PI*i*6/160),-sin(2*M_PI*i*6/160));
         complex<double> w(1,0);
         complex<double> a = (double)x[i]*w;
         sum_0 += a;
         }

      dfft_even(x,MainFormSLS->hh,c2);     //Прямое преобразование Фурье для четных отсчетов
      c2.v[0] = sum_0;
      normalize(c2);

      dfft_odd(x,MainFormSLS->hh,c1); //Прямое преобразование Фурье для нечетных отсчетов
      normalize(c1);

      bool l_h_s = false;
      if(TTest_Sound->Left_Half_Spect->Checked)
         l_h_s = true;
      if(l_h_s)
       {
       for(int i=0;i<40;i++)
          {
          c2.v[i]*=1.2;
          c1.v[i]*=1.2;
          }
       for(int i=40;i<80;i++)
          {
          c2.v[i]=0.0;
          c1.v[i]=0.0;
          }
       }

     if(TTest_Sound->HF_Suppr->Checked)
      {
      if(sfi.zc > 80)
        {
        for(int i=40;i<80;i++)
           {
           c2.v[i]=0.0;
           c1.v[i]=0.0;
           }
        }
      }
    if(TTest_Sound->LF_Suppr->Checked)
      {
      for(int i=0;i<TTest_Sound->LF_Suppr_Freq;i++)
         {
         c2.v[i]=0.0;
         c1.v[i]=0.0;
         }
      }
    }

if(!TTest_Sound->FourieTransform->Checked)
   return;

                      /*
                        sum_5   //250  Hz
                        sum_15  //750  Hz
                        sum_25  //1250 Hz
                        sum_35  //1750 Hz
                        sum_45  //2250 Hz
                        sum_55  //2750 Hz
                        sum_65  //3250 Hz
                          */
    /*
   TCoeff_By_5 c5;
   ddft_by_5(x,c5);

    */

   /*
  complex<double> sum_6_1(0,0); // for test only
  for(int i=0;i<sz_x;i++)
     {
     complex<double> w(cos(2*M_PI*i*6/160),-sin(2*M_PI*i*6/160));
     complex<double> a = (double)x[i]*w;
     sum_6_1 += a;
     }

   */

  /*
  complex<double> sum_50_1(0,0); // for test only
  for(int i=0;i<sz_x;i++)
     {
     complex<double> w(cos(2*M_PI*i*50/160),-sin(2*M_PI*i*50/160));
     complex<double> a = (double)x[i]*w;
     sum_50_1 += a;
     }

   */

  /*
  complex<double> sum_11(0,0); //11-я гарм - 550 Hz
  ddft_11(x,sum_11);
  */


  /*
  if(ampl_10 > 0.0)
    {
    if(ampl_16 > 0.0)
       freq_comp_16.rs_16_10 = ampl_10/ampl_16;
    if(ampl_20 > 0.0)
       freq_comp_20.rs_20_10 = ampl_10/ampl_20;
    if(ampl_40 > 0.0)
       freq_comp_40.rs_40_10 = ampl_10/ampl_40;
    }
    */

    /*
  sfi.fcl.insert(TFreqCompList::value_type(ampl_10,freq_comp_10));
  sfi.fcl.insert(TFreqCompList::value_type(ampl_16,freq_comp_16));
  sfi.fcl.insert(TFreqCompList::value_type(ampl_20,freq_comp_20));
  sfi.fcl.insert(TFreqCompList::value_type(ampl_32,freq_comp_32));
  sfi.fcl.insert(TFreqCompList::value_type(ampl_40,freq_comp_40));
  */

  if((TTest_Sound->MicLog->Checked)||(TTest_Sound->SoundLog->Checked))
    {
    string timestr;
    TDateTime dt = dt.CurrentTime();
    exsTime( dt,timestr);
    string s = "\n\n" + timestr;
    if(vt == TVolume_Type__Mic)
     if(TTest_Sound->MicLog->Checked)
       {
       /*
       s += " microphone";
       s += "\n50  Hz: "  + (string)FloatToStr(sum_1.real()).c_str()   +  " i" + (string)FloatToStr(sum_1.imag()).c_str() +
            "\n100 Hz: "  + (string)FloatToStr(c2.v[1].real()).c_str()   +  " i" + (string)FloatToStr(c2.v[1].imag()).c_str() +
            "\n200 Hz: "  + (string)FloatToStr(c2.sum_4.real()).c_str()   +  " i" + (string)FloatToStr(c2.sum_4.imag()).c_str() +
            "\n300 Hz: "  + (string)FloatToStr(sum_6.real()).c_str()   +  " i" + (string)FloatToStr(sum_6.imag()).c_str() +
            "\n500 Hz: "  + (string)FloatToStr(c5.sum_10.real()).c_str()+  " i" + (string)FloatToStr(c5.sum_10.imag()).c_str() +
            "\n800 Hz: "  + (string)FloatToStr(sum_16.real()).c_str()   +  " i" + (string)FloatToStr(sum_16.imag()).c_str() +
            "\n1000 Hz: " + (string)FloatToStr(c5.sum_20.real()).c_str()   +  " i" + (string)FloatToStr(c5.sum_20.imag()).c_str() +
            "\n1500 Hz: " + (string)FloatToStr(c5.sum_30.real()).c_str()   +  " i" + (string)FloatToStr(c5.sum_30.imag()).c_str() +
            "\n1600 Hz: " + (string)FloatToStr(sum_32.real()).c_str()   +  " i" + (string)FloatToStr(sum_32.imag()).c_str() +
            "\n2000 Hz: " + (string)FloatToStr(c5.sum_40.real()).c_str()   +  " i" + (string)FloatToStr(c5.sum_40.imag()).c_str();
       BT->wave_log(s);  */
       }
     if(vt == TVolume_Type__Sound)
      if(TTest_Sound->SoundLog->Checked)
        {
        s += " sound";
       s +=  "\n0  Hz: "  + (string)FloatToStr(c2.v[0].real()).c_str()   +  " i" + (string)FloatToStr(c2.v[0].imag()).c_str() +
            //"\n50  Hz: "  + (string)FloatToStr(sum_1.real()).c_str()   +  " i" + (string)FloatToStr(sum_1.imag()).c_str() +
            "\n100 Hz: "  + (string)FloatToStr(c2.v[1].real()).c_str()   +  " i" + (string)FloatToStr(c2.v[1].imag()).c_str() +
            "\n200 Hz: "  + (string)FloatToStr(c2.v[2].real()).c_str()   +  " i" + (string)FloatToStr(c2.v[2].imag()).c_str() +
          //  "\n250 Hz: "  + (string)FloatToStr(c5.sum_5.real()).c_str()   +  " i" + (string)FloatToStr(c5.sum_5.imag()).c_str() +
            "\n300 Hz: "  + (string)FloatToStr(c2.v[3].real()).c_str()   +  " i" + (string)FloatToStr(c2.v[3].imag()).c_str() + /*" " + (string)FloatToStr(sum_6_1.real()).c_str()   +  " i" + (string)FloatToStr(sum_6_1.imag()).c_str() +*/
            "\n400 Hz: "  + (string)FloatToStr(c2.v[4].real()).c_str()   +  " i" + (string)FloatToStr(c2.v[4].imag()).c_str() + /*" " + (string)FloatToStr(sum_6_1.real()).c_str()   +  " i" + (string)FloatToStr(sum_6_1.imag()).c_str() +*/
            "\n500 Hz: "  + (string)FloatToStr(c2.v[5].real()).c_str()   +  " i" + (string)FloatToStr(c2.v[5].imag()).c_str() +
          //  "\n550 Hz: "  + (string)FloatToStr(sum_11.real()).c_str()   +  " i" + (string)FloatToStr(sum_11.imag()).c_str() + /*" " + (string)FloatToStr(sum_11_1.real()).c_str() +  " i" + (string)FloatToStr(sum_11_1.imag()).c_str() +*/
          //  "\n750 Hz: "  + (string)FloatToStr(c5.sum_15.real()).c_str()   +  " i" + (string)FloatToStr(c5.sum_15.imag()).c_str() +
            "\n800 Hz: "  + (string)FloatToStr(c2.v[8].real()).c_str()   +  " i" + (string)FloatToStr(c2.v[8].imag()).c_str() +
            "\n1000 Hz: " + (string)FloatToStr(c2.v[10].real()).c_str()   +  " i" + (string)FloatToStr(c2.v[10].imag()).c_str() +
         //   "\n1250 Hz: " + (string)FloatToStr(c5.sum_25.real()).c_str()   +  " i" + (string)FloatToStr(c5.sum_25.imag()).c_str() +
            "\n1100 Hz: " + (string)FloatToStr(c2.v[11].real()).c_str()   +  " i" + (string)FloatToStr(c2.v[11].imag()).c_str() + /*" " + (string)FloatToStr(sum_22_1.real()).c_str() +  " i" + (string)FloatToStr(sum_22_1.imag()).c_str() +*/
            "\n1500 Hz: " + (string)FloatToStr(c2.v[15].real()).c_str()   +  " i" + (string)FloatToStr(c2.v[15].imag()).c_str() +
        //    "\n1750 Hz: " + (string)FloatToStr(c5.sum_35.real()).c_str()   +  " i" + (string)FloatToStr(c5.sum_35.imag()).c_str() +
            "\n1600 Hz: " + (string)FloatToStr(c2.v[16].real()).c_str()   +  " i" + (string)FloatToStr(c2.v[16].imag()).c_str() +
            "\n2000 Hz: " + (string)FloatToStr(c2.v[20].real()).c_str()   +  " i" + (string)FloatToStr(c2.v[20].imag()).c_str() + /*" " + (string)FloatToStr(sum_40_1.real()).c_str() +  " i" + (string)FloatToStr(sum_40_1.imag()).c_str() +*/
            "\n2200 Hz: " + (string)FloatToStr(c2.v[22].real()).c_str()   +  " i" + (string)FloatToStr(c2.v[22].imag()).c_str() +  /*" " + (string)FloatToStr(sum_44_1.real()).c_str() +  " i" + (string)FloatToStr(sum_44_1.imag()).c_str(); */
        //    "\n2250 Hz: " + (string)FloatToStr(c5.sum_45.real()).c_str()   +  " i" + (string)FloatToStr(c5.sum_45.imag()).c_str() +
            "\n2500 Hz: " + (string)FloatToStr(c2.v[25].real()).c_str()   +  " i" + (string)FloatToStr(c2.v[25].imag()).c_str() + // " " +(string)FloatToStr(sum_50_1.real()).c_str() +  " i" + (string)FloatToStr(sum_50_1.imag()).c_str() +
       //     "\n2750 Hz: " + (string)FloatToStr(c5.sum_55.real()).c_str()   +  " i" + (string)FloatToStr(c5.sum_55.imag()).c_str() +
            "\n3000 Hz: " + (string)FloatToStr(c2.v[30].real()).c_str()   +  " i" + (string)FloatToStr(c2.v[30].imag()).c_str() +
        //    "\n3250 Hz: " + (string)FloatToStr(c5.sum_65.real()).c_str()   +  " i" + (string)FloatToStr(c5.sum_65.imag()).c_str() +
            "\n3500 Hz: " + (string)FloatToStr(c2.v[35].real()).c_str()   +  " i" + (string)FloatToStr(c2.v[35].imag()).c_str() +
            "\n7800 Hz: " + (string)FloatToStr(c2.v[78].real()).c_str()   +  " i" + (string)FloatToStr(c2.v[78].imag()).c_str() + // " " +(string)FloatToStr(sum_156_1.real()).c_str() +  " i" + (string)FloatToStr(sum_156_1.imag()).c_str() +
            "\n7900 Hz: " + (string)FloatToStr(c2.v[79].real()).c_str()   +  " i" + (string)FloatToStr(c2.v[79].imag()).c_str();  // " " +(string)FloatToStr(sum_158_1.real()).c_str() +  " i" + (string)FloatToStr(sum_158_1.imag()).c_str();
       BT->wave_log(s);
       }
    }


  vector<complex<double> > out_even; //выходные отсчеты четных гармоник
  vector<complex<double> > out_odd; //выходные отсчеты нечетных гармоник
  vector<double> out_double; //выходные отсчеты
  vector<short> out_short; //выходные отсчеты
  vector<UBYTE> out_ubyte; //выходные отсчеты

  rdft_even(out_even,MainFormSLS->hh_1,c2);  //Обратное преобразование Фурье, четные гарм
  rdft_odd(out_odd,MainFormSLS->hh_1,c1);    //Обратное преобразование Фурье, нечетные гарм

  int out_even_size = out_even.size();
  for(int i=0;i<out_even_size;i++)
      out_even[i] += out_odd[i];


  int size = out_even.size();
  int N = 160;
  for(int i=0; i<N; i++ )
     {
     complex<double > s = out_even[i];

     if(TTest_Sound->sqrt->Checked)
       {
       double ampl = sqrt(pow(s.real(),2) + pow(s.imag(),2));
       out_double.push_back(ampl);
       }
     else
       out_double.push_back(s.real());
     }

  int sz_1 = out_double.size();

  double_2_short(out_short,out_double,N,false);

  short_2_ubyte(out_ubyte,out_short,N);
  opb->v = out_ubyte;
  }
}
#endif
//-----------------------------------------------------------------------------
void __fastcall TSoundQueue::push_sound_queue(TSampleFreqImage& sfi)
{
::EnterCriticalSection(&eqcs);
  q.push_back(sfi);
  if(q.size() > max_echo_delay)
    {
    q.front();
    q.pop_front();
    if(q.size() > max_echo_delay)
       q.clear();
    }
::LeaveCriticalSection(&eqcs);
}
//-----------------------------------------------------------------------------
void __fastcall TSoundQueue::get_sound_queue(deque<TSampleFreqImage>& out)
{
::EnterCriticalSection(&eqcs);
  out = q;
::LeaveCriticalSection(&eqcs);
}
//-----------------------------------------------------------------------------
int __fastcall TSoundQueue::get_echo_queue_size()
{
int rv = 0;
::EnterCriticalSection(&eqcs);
  rv = q.size();
::LeaveCriticalSection(&eqcs);
return rv;
}
//-----------------------------------------------------------------------------
void __fastcall TMicQueue::push_mic_queue(TSampleFreqImage& sfi)
{
::EnterCriticalSection(&mqcs);
  q.push_back(sfi);
  if(q.size() > max_queue_size)
    {
    q.front();
    q.pop_front();
    }
::LeaveCriticalSection(&mqcs);
}
//-----------------------------------------------------------------------------
int __fastcall TMicQueue::get_mic_queue_size()
{
int rv = 0;
::EnterCriticalSection(&mqcs);
  rv = q.size();
::LeaveCriticalSection(&mqcs);
return rv;
}
//------------------------------------------------------------------------------
void __fastcall TMicQueue::clear_mic_queue()
{
::EnterCriticalSection(&mqcs);
  if(convers_state)
    {
    convers_state = 0; //состояние 0, ждем новый голосовой sample
    local_max     = 0.0;
    q.clear();
    }
::LeaveCriticalSection(&mqcs);
}
//-----------------------------------------------------------------------------
bool __fastcall TVolume::compare_sfi_by_ampl(TSampleFreqImage& mic_sfi,TSampleFreqImage& delayed_sound_sfi)
{
TFreqCompList::iterator it = mic_sfi.fcl.begin();
TFreqCompList::iterator it_1 = delayed_sound_sfi.fcl.begin();
if(it == mic_sfi.fcl.end())
  return false;
if(it_1 == delayed_sound_sfi.fcl.end())
  return false;
while((it != mic_sfi.fcl.end()) && (it_1 != delayed_sound_sfi.fcl.end()))
     {
     TFreqComp fq = (*it).second;
     TFreqComp fq_1 = (*it_1).second;
     if(fq.freq != fq_1.freq)
        return false;

     if(fq.freq == 16)
       if((fq.rs_16_10  > (fq_1.rs_16_10 + 1.25)) || (fq.rs_16_10 < (fq_1.rs_16_10 - 1.25)))  //800 Hz
          return false;
     if(fq.freq == 20)
       if((fq.rs_20_10  > (fq_1.rs_20_10 + 1.25)) || (fq.rs_20_10 < (fq_1.rs_20_10 - 1.25))) //1000 Hz
          return false;
     if(fq.freq == 40)
       if((fq.rs_40_10  > (fq_1.rs_40_10 + 2.25)) || (fq.rs_40_10 < (fq_1.rs_40_10 - 2.25))) //2000 Hz
          return false;


     it++;
     it_1++;
     }
return true;
}
//-----------------------------------------------------------------------------
bool __fastcall TVolume::compare_sfi_by_ampl_1(TSampleFreqImage& mic_sfi,TSampleFreqImage& delayed_sound_sfi)
{
int n = 0;
const COUNT = 4;
const THRESHOLD = 1;
int count = COUNT;
TFreqCompList::reverse_iterator it = mic_sfi.fcl.rbegin();
while(it != mic_sfi.fcl.rend())
     {
     if(!count--)
       break;
     TFreqComp fc = (*it).second;
     if(delayed_sound_sfi.compare_by_max_ampl(fc,COUNT,THRESHOLD))
        n++;
     it++;
     }
if(n > THRESHOLD)
  return true;
return false;
}
//-----------------------------------------------------------------------------
bool __fastcall TSampleFreqImage::compare_by_max_ampl(TFreqComp& fc,int count,int threshold)
{
int n = 0;
TFreqCompList::reverse_iterator it = fcl.rbegin();
while(it != fcl.rend())
     {
     if(!count--)
       break;
     TFreqComp f_c = (*it).second;
     if(f_c.freq == fc.freq)
       n++;
     it++;
     }
if(n > threshold)
  return true;
return false;
}
//-----------------------------------------------------------------------------
bool __fastcall TVolume::compare_sfi(TSampleFreqImage& mic_sfi,TSampleFreqImage& delayed_sound_sfi)
{
if(TTest_Sound->dft_full->Checked)
  return compare_sfi_by_freq_full(mic_sfi,delayed_sound_sfi);
return compare_sfi_by_freq(mic_sfi,delayed_sound_sfi);
}
//------------------------------------------------------------------------------
bool __fastcall TVolume::compare_sfi_by_freq(TSampleFreqImage& mic_sfi,TSampleFreqImage& delayed_sound_sfi)
{
int n = 0;
int mic_sz = mic_sfi.v.size();
for(int i=0;i<mic_sz;i++)
  {
  TFreqComp fc = mic_sfi.v[i];
  if(delayed_sound_sfi.compare_by_quadrant(fc))
    n++;
  }
if(((double)n/(double)mic_sz) > 0.5)
  return true;
return false;
}
//-----------------------------------------------------------------------------
bool __fastcall TVolume::compare_sfi_by_freq_full(TSampleFreqImage& mic_sfi,TSampleFreqImage& delayed_sound_sfi)
{
int n = 0;
int mic_sz = mic_sfi.v.size();
if(!mic_sz)
   return false;
if(!mic_sfi.imax_ampl.size())
   return false;
if(mic_sfi.sum_pic_val < 100)
  return false;
for(int i=0;i<mic_sz;i++)
   {
   if(mic_sfi.imax_ampl[i] != delayed_sound_sfi.imax_ampl[i])
      return false;
   }
int count_8 = 0;
int sound_sample_sz = delayed_sound_sfi.sample.size();
for(int i=0;i<sound_sample_sz;i++)
    {
    if(abs(delayed_sound_sfi.sample[i]) == 8)
      {
      if(++count_8 > 10)
         return false;
      }
    }


if(!TTest_Sound->dft_full_freq->Checked)
   return true;
for(int i=0;i<mic_sz;i++)
  {
  TFreqComp fc = mic_sfi.v[i];
  if(delayed_sound_sfi.compare_by_quadrant(fc))
    n++;
  }
if(((double)n/(double)mic_sz) > 0.5)
  return true;
return false;
}
//-----------------------------------------------------------------------------
bool __fastcall TSampleFreqImage::compare_by_quadrant(TFreqComp& fc)
{
int sz = v.size();
for(int i=0;i<sz;i++)
   {
   if(fc.freq == v[i].freq)
     {
     if((fc.sum_xx.real() >= 0)&&(fc.sum_xx.imag() >= 0))
        if((v[i].sum_xx.real() >= 0)&&(v[i].sum_xx.imag() >= 0))
            return true;
     if((fc.sum_xx.real() >= 0)&&(fc.sum_xx.imag() < 0))
        if((v[i].sum_xx.real() >= 0)&&(v[i].sum_xx.imag() < 0))
            return true;
     if((fc.sum_xx.real() < 0)&&(fc.sum_xx.imag() >= 0))
        if((v[i].sum_xx.real() < 0)&&(v[i].sum_xx.imag() >= 0))
            return true;
     if((fc.sum_xx.real() < 0)&&(fc.sum_xx.imag() < 0))
        if((v[i].sum_xx.real() < 0)&&(v[i].sum_xx.imag() < 0))
            return true;
     }
   }
return false;
}
//-----------------------------------------------------------------------------
void __fastcall ddft_11(vector<short>& x,complex<double>& sum_11)
{
//id 11 550 Hz
sum_11 += (double)x[0]*MainFormSLS->hh[0];
sum_11 += (double)x[1]*MainFormSLS->hh[11];
sum_11 += (double)x[2]*MainFormSLS->hh[22];
sum_11 += (double)x[3]*MainFormSLS->hh[33];
sum_11 += (double)x[4]*MainFormSLS->hh[44];
sum_11 += (double)x[5]*MainFormSLS->hh[55];
sum_11 += (double)x[6]*MainFormSLS->hh[66];
sum_11 += (double)x[7]*MainFormSLS->hh[77];
sum_11 += (double)x[8]*MainFormSLS->hh[88];
sum_11 += (double)x[9]*MainFormSLS->hh[99];
sum_11 += (double)x[10]*MainFormSLS->hh[110];
sum_11 += (double)x[11]*MainFormSLS->hh[121];
sum_11 += (double)x[12]*MainFormSLS->hh[132];
sum_11 += (double)x[13]*MainFormSLS->hh[143];
sum_11 += (double)x[14]*MainFormSLS->hh[154];
sum_11 += (double)x[15]*MainFormSLS->hh[5];
sum_11 += (double)x[16]*MainFormSLS->hh[16];
sum_11 += (double)x[17]*MainFormSLS->hh[27];
sum_11 += (double)x[18]*MainFormSLS->hh[38];
sum_11 += (double)x[19]*MainFormSLS->hh[49];
sum_11 += (double)x[20]*MainFormSLS->hh[60];
sum_11 += (double)x[21]*MainFormSLS->hh[71];
sum_11 += (double)x[22]*MainFormSLS->hh[82];
sum_11 += (double)x[23]*MainFormSLS->hh[93];
sum_11 += (double)x[24]*MainFormSLS->hh[104];
sum_11 += (double)x[25]*MainFormSLS->hh[115];
sum_11 += (double)x[26]*MainFormSLS->hh[126];
sum_11 += (double)x[27]*MainFormSLS->hh[137];
sum_11 += (double)x[28]*MainFormSLS->hh[148];
sum_11 += (double)x[29]*MainFormSLS->hh[159];
sum_11 += (double)x[30]*MainFormSLS->hh[10];
sum_11 += (double)x[31]*MainFormSLS->hh[21];
sum_11 += (double)x[32]*MainFormSLS->hh[32];
sum_11 += (double)x[33]*MainFormSLS->hh[43];
sum_11 += (double)x[34]*MainFormSLS->hh[54];
sum_11 += (double)x[35]*MainFormSLS->hh[65];
sum_11 += (double)x[36]*MainFormSLS->hh[76];
sum_11 += (double)x[37]*MainFormSLS->hh[87];
sum_11 += (double)x[38]*MainFormSLS->hh[98];
sum_11 += (double)x[39]*MainFormSLS->hh[109];
sum_11 += (double)x[40]*MainFormSLS->hh[120];
sum_11 += (double)x[41]*MainFormSLS->hh[131];
sum_11 += (double)x[42]*MainFormSLS->hh[142];
sum_11 += (double)x[43]*MainFormSLS->hh[153];
sum_11 += (double)x[44]*MainFormSLS->hh[4];
sum_11 += (double)x[45]*MainFormSLS->hh[15];
sum_11 += (double)x[46]*MainFormSLS->hh[26];
sum_11 += (double)x[47]*MainFormSLS->hh[37];
sum_11 += (double)x[48]*MainFormSLS->hh[48];
sum_11 += (double)x[49]*MainFormSLS->hh[59];
sum_11 += (double)x[50]*MainFormSLS->hh[70];
sum_11 += (double)x[51]*MainFormSLS->hh[81];
sum_11 += (double)x[52]*MainFormSLS->hh[92];
sum_11 += (double)x[53]*MainFormSLS->hh[103];
sum_11 += (double)x[54]*MainFormSLS->hh[114];
sum_11 += (double)x[55]*MainFormSLS->hh[125];
sum_11 += (double)x[56]*MainFormSLS->hh[136];
sum_11 += (double)x[57]*MainFormSLS->hh[147];
sum_11 += (double)x[58]*MainFormSLS->hh[158];
sum_11 += (double)x[59]*MainFormSLS->hh[9];
sum_11 += (double)x[60]*MainFormSLS->hh[20];
sum_11 += (double)x[61]*MainFormSLS->hh[31];
sum_11 += (double)x[62]*MainFormSLS->hh[42];
sum_11 += (double)x[63]*MainFormSLS->hh[53];
sum_11 += (double)x[64]*MainFormSLS->hh[64];
sum_11 += (double)x[65]*MainFormSLS->hh[75];
sum_11 += (double)x[66]*MainFormSLS->hh[86];
sum_11 += (double)x[67]*MainFormSLS->hh[97];
sum_11 += (double)x[68]*MainFormSLS->hh[108];
sum_11 += (double)x[69]*MainFormSLS->hh[119];
sum_11 += (double)x[70]*MainFormSLS->hh[130];
sum_11 += (double)x[71]*MainFormSLS->hh[141];
sum_11 += (double)x[72]*MainFormSLS->hh[152];
sum_11 += (double)x[73]*MainFormSLS->hh[3];
sum_11 += (double)x[74]*MainFormSLS->hh[14];
sum_11 += (double)x[75]*MainFormSLS->hh[25];
sum_11 += (double)x[76]*MainFormSLS->hh[36];
sum_11 += (double)x[77]*MainFormSLS->hh[47];
sum_11 += (double)x[78]*MainFormSLS->hh[58];
sum_11 += (double)x[79]*MainFormSLS->hh[69];
sum_11 += (double)x[80]*MainFormSLS->hh[80];
sum_11 += (double)x[81]*MainFormSLS->hh[91];
sum_11 += (double)x[82]*MainFormSLS->hh[102];
sum_11 += (double)x[83]*MainFormSLS->hh[113];
sum_11 += (double)x[84]*MainFormSLS->hh[124];
sum_11 += (double)x[85]*MainFormSLS->hh[135];
sum_11 += (double)x[86]*MainFormSLS->hh[146];
sum_11 += (double)x[87]*MainFormSLS->hh[157];
sum_11 += (double)x[88]*MainFormSLS->hh[8];
sum_11 += (double)x[89]*MainFormSLS->hh[19];
sum_11 += (double)x[90]*MainFormSLS->hh[30];
sum_11 += (double)x[91]*MainFormSLS->hh[41];
sum_11 += (double)x[92]*MainFormSLS->hh[52];
sum_11 += (double)x[93]*MainFormSLS->hh[63];
sum_11 += (double)x[94]*MainFormSLS->hh[74];
sum_11 += (double)x[95]*MainFormSLS->hh[85];
sum_11 += (double)x[96]*MainFormSLS->hh[96];
sum_11 += (double)x[97]*MainFormSLS->hh[107];
sum_11 += (double)x[98]*MainFormSLS->hh[118];
sum_11 += (double)x[99]*MainFormSLS->hh[129];
sum_11 += (double)x[100]*MainFormSLS->hh[140];
sum_11 += (double)x[101]*MainFormSLS->hh[151];
sum_11 += (double)x[102]*MainFormSLS->hh[2];
sum_11 += (double)x[103]*MainFormSLS->hh[13];
sum_11 += (double)x[104]*MainFormSLS->hh[24];
sum_11 += (double)x[105]*MainFormSLS->hh[35];
sum_11 += (double)x[106]*MainFormSLS->hh[46];
sum_11 += (double)x[107]*MainFormSLS->hh[57];
sum_11 += (double)x[108]*MainFormSLS->hh[68];
sum_11 += (double)x[109]*MainFormSLS->hh[79];
sum_11 += (double)x[110]*MainFormSLS->hh[90];
sum_11 += (double)x[111]*MainFormSLS->hh[101];
sum_11 += (double)x[112]*MainFormSLS->hh[112];
sum_11 += (double)x[113]*MainFormSLS->hh[123];
sum_11 += (double)x[114]*MainFormSLS->hh[134];
sum_11 += (double)x[115]*MainFormSLS->hh[145];
sum_11 += (double)x[116]*MainFormSLS->hh[156];
sum_11 += (double)x[117]*MainFormSLS->hh[7];
sum_11 += (double)x[118]*MainFormSLS->hh[18];
sum_11 += (double)x[119]*MainFormSLS->hh[29];
sum_11 += (double)x[120]*MainFormSLS->hh[40];
sum_11 += (double)x[121]*MainFormSLS->hh[51];
sum_11 += (double)x[122]*MainFormSLS->hh[62];
sum_11 += (double)x[123]*MainFormSLS->hh[73];
sum_11 += (double)x[124]*MainFormSLS->hh[84];
sum_11 += (double)x[125]*MainFormSLS->hh[95];
sum_11 += (double)x[126]*MainFormSLS->hh[106];
sum_11 += (double)x[127]*MainFormSLS->hh[117];
sum_11 += (double)x[128]*MainFormSLS->hh[128];
sum_11 += (double)x[129]*MainFormSLS->hh[139];
sum_11 += (double)x[130]*MainFormSLS->hh[150];
sum_11 += (double)x[131]*MainFormSLS->hh[1];
sum_11 += (double)x[132]*MainFormSLS->hh[12];
sum_11 += (double)x[133]*MainFormSLS->hh[23];
sum_11 += (double)x[134]*MainFormSLS->hh[34];
sum_11 += (double)x[135]*MainFormSLS->hh[45];
sum_11 += (double)x[136]*MainFormSLS->hh[56];
sum_11 += (double)x[137]*MainFormSLS->hh[67];
sum_11 += (double)x[138]*MainFormSLS->hh[78];
sum_11 += (double)x[139]*MainFormSLS->hh[89];
sum_11 += (double)x[140]*MainFormSLS->hh[100];
sum_11 += (double)x[141]*MainFormSLS->hh[111];
sum_11 += (double)x[142]*MainFormSLS->hh[122];
sum_11 += (double)x[143]*MainFormSLS->hh[133];
sum_11 += (double)x[144]*MainFormSLS->hh[144];
sum_11 += (double)x[145]*MainFormSLS->hh[155];
sum_11 += (double)x[146]*MainFormSLS->hh[6];
sum_11 += (double)x[147]*MainFormSLS->hh[17];
sum_11 += (double)x[148]*MainFormSLS->hh[28];
sum_11 += (double)x[149]*MainFormSLS->hh[39];
sum_11 += (double)x[150]*MainFormSLS->hh[50];
sum_11 += (double)x[151]*MainFormSLS->hh[61];
sum_11 += (double)x[152]*MainFormSLS->hh[72];
sum_11 += (double)x[153]*MainFormSLS->hh[83];
sum_11 += (double)x[154]*MainFormSLS->hh[94];
sum_11 += (double)x[155]*MainFormSLS->hh[105];
sum_11 += (double)x[156]*MainFormSLS->hh[116];
sum_11 += (double)x[157]*MainFormSLS->hh[127];
sum_11 += (double)x[158]*MainFormSLS->hh[138];
sum_11 += (double)x[159]*MainFormSLS->hh[149];
}
//------------------------------------------------------------------------------
void __fastcall ddft_22(vector<short>& x,complex<double>& sum_22)
{
//id 22 1100 Hz
sum_22 += ((double)x[0] + (double)x[80])*MainFormSLS->hh[0];
sum_22 += ((double)x[1] + (double)x[81])*MainFormSLS->hh[22];
sum_22 += ((double)x[2] + (double)x[82])*MainFormSLS->hh[44];
sum_22 += ((double)x[3] + (double)x[83])*MainFormSLS->hh[66];
sum_22 += ((double)x[4] + (double)x[84])*MainFormSLS->hh[88];
sum_22 += ((double)x[5] + (double)x[85])*MainFormSLS->hh[110];
sum_22 += ((double)x[6] + (double)x[86])*MainFormSLS->hh[132];
sum_22 += ((double)x[7] + (double)x[87])*MainFormSLS->hh[154];
sum_22 += ((double)x[8] + (double)x[88])*MainFormSLS->hh[16];
sum_22 += ((double)x[9] + (double)x[89])*MainFormSLS->hh[38];
sum_22 += ((double)x[10] + (double)x[90])*MainFormSLS->hh[60];
sum_22 += ((double)x[11] + (double)x[91])*MainFormSLS->hh[82];
sum_22 += ((double)x[12] + (double)x[92])*MainFormSLS->hh[104];
sum_22 += ((double)x[13] + (double)x[93])*MainFormSLS->hh[126];
sum_22 += ((double)x[14] + (double)x[94])*MainFormSLS->hh[148];
sum_22 += ((double)x[15] + (double)x[95])*MainFormSLS->hh[10];
sum_22 += ((double)x[16] + (double)x[96])*MainFormSLS->hh[32];
sum_22 += ((double)x[17] + (double)x[97])*MainFormSLS->hh[54];
sum_22 += ((double)x[18] + (double)x[98])*MainFormSLS->hh[76];
sum_22 += ((double)x[19] + (double)x[99])*MainFormSLS->hh[98];
sum_22 += ((double)x[20] + (double)x[100])*MainFormSLS->hh[120];
sum_22 += ((double)x[21] + (double)x[101])*MainFormSLS->hh[142];
sum_22 += ((double)x[22] + (double)x[102])*MainFormSLS->hh[4];
sum_22 += ((double)x[23] + (double)x[103])*MainFormSLS->hh[26];
sum_22 += ((double)x[24] + (double)x[104])*MainFormSLS->hh[48];
sum_22 += ((double)x[25] + (double)x[105])*MainFormSLS->hh[70];
sum_22 += ((double)x[26] + (double)x[106])*MainFormSLS->hh[92];
sum_22 += ((double)x[27] + (double)x[107])*MainFormSLS->hh[114];
sum_22 += ((double)x[28] + (double)x[108])*MainFormSLS->hh[136];
sum_22 += ((double)x[29] + (double)x[109])*MainFormSLS->hh[158];
sum_22 += ((double)x[30] + (double)x[110])*MainFormSLS->hh[20];
sum_22 += ((double)x[31] + (double)x[111])*MainFormSLS->hh[42];
sum_22 += ((double)x[32] + (double)x[112])*MainFormSLS->hh[64];
sum_22 += ((double)x[33] + (double)x[113])*MainFormSLS->hh[86];
sum_22 += ((double)x[34] + (double)x[114])*MainFormSLS->hh[108];
sum_22 += ((double)x[35] + (double)x[115])*MainFormSLS->hh[130];
sum_22 += ((double)x[36] + (double)x[116])*MainFormSLS->hh[152];
sum_22 += ((double)x[37] + (double)x[117])*MainFormSLS->hh[14];
sum_22 += ((double)x[38] + (double)x[118])*MainFormSLS->hh[36];
sum_22 += ((double)x[39] + (double)x[119])*MainFormSLS->hh[58];
sum_22 += ((double)x[40] + (double)x[120])*MainFormSLS->hh[80];
sum_22 += ((double)x[41] + (double)x[121])*MainFormSLS->hh[102];
sum_22 += ((double)x[42] + (double)x[122])*MainFormSLS->hh[124];
sum_22 += ((double)x[43] + (double)x[123])*MainFormSLS->hh[146];
sum_22 += ((double)x[44] + (double)x[124])*MainFormSLS->hh[8];
sum_22 += ((double)x[45] + (double)x[125])*MainFormSLS->hh[30];
sum_22 += ((double)x[46] + (double)x[126])*MainFormSLS->hh[52];
sum_22 += ((double)x[47] + (double)x[127])*MainFormSLS->hh[74];
sum_22 += ((double)x[48] + (double)x[128])*MainFormSLS->hh[96];
sum_22 += ((double)x[49] + (double)x[129])*MainFormSLS->hh[118];
sum_22 += ((double)x[50] + (double)x[130])*MainFormSLS->hh[140];
sum_22 += ((double)x[51] + (double)x[131])*MainFormSLS->hh[2];
sum_22 += ((double)x[52] + (double)x[132])*MainFormSLS->hh[24];
sum_22 += ((double)x[53] + (double)x[133])*MainFormSLS->hh[46];
sum_22 += ((double)x[54] + (double)x[134])*MainFormSLS->hh[68];
sum_22 += ((double)x[55] + (double)x[135])*MainFormSLS->hh[90];
sum_22 += ((double)x[56] + (double)x[136])*MainFormSLS->hh[112];
sum_22 += ((double)x[57] + (double)x[137])*MainFormSLS->hh[134];
sum_22 += ((double)x[58] + (double)x[138])*MainFormSLS->hh[156];
sum_22 += ((double)x[59] + (double)x[139])*MainFormSLS->hh[18];
sum_22 += ((double)x[60] + (double)x[140])*MainFormSLS->hh[40];
sum_22 += ((double)x[61] + (double)x[141])*MainFormSLS->hh[62];
sum_22 += ((double)x[62] + (double)x[142])*MainFormSLS->hh[84];
sum_22 += ((double)x[63] + (double)x[143])*MainFormSLS->hh[106];
sum_22 += ((double)x[64] + (double)x[144])*MainFormSLS->hh[128];
sum_22 += ((double)x[65] + (double)x[145])*MainFormSLS->hh[150];
sum_22 += ((double)x[66] + (double)x[146])*MainFormSLS->hh[12];
sum_22 += ((double)x[67] + (double)x[147])*MainFormSLS->hh[34];
sum_22 += ((double)x[68] + (double)x[148])*MainFormSLS->hh[56];
sum_22 += ((double)x[69] + (double)x[149])*MainFormSLS->hh[78];
sum_22 += ((double)x[70] + (double)x[150])*MainFormSLS->hh[100];
sum_22 += ((double)x[71] + (double)x[151])*MainFormSLS->hh[122];
sum_22 += ((double)x[72] + (double)x[152])*MainFormSLS->hh[144];
sum_22 += ((double)x[73] + (double)x[153])*MainFormSLS->hh[6];
sum_22 += ((double)x[74] + (double)x[154])*MainFormSLS->hh[28];
sum_22 += ((double)x[75] + (double)x[155])*MainFormSLS->hh[50];
sum_22 += ((double)x[76] + (double)x[156])*MainFormSLS->hh[72];
sum_22 += ((double)x[77] + (double)x[157])*MainFormSLS->hh[94];
sum_22 += ((double)x[78] + (double)x[158])*MainFormSLS->hh[116];
sum_22 += ((double)x[79] + (double)x[159])*MainFormSLS->hh[138];
}
//------------------------------------------------------------------------------
void __fastcall ddft_44(vector<short>& x,complex<double>& sum_44)
{
//id 44 2200 Hz
sum_44 += ((double)x[0] + (double)x[40] + (double)x[80] + (double)x[120])*MainFormSLS->hh[0];
sum_44 += ((double)x[1] + (double)x[41] + (double)x[81] + (double)x[121])*MainFormSLS->hh[44];
sum_44 += ((double)x[2] + (double)x[42] + (double)x[82] + (double)x[122])*MainFormSLS->hh[88];
sum_44 += ((double)x[3] + (double)x[43] + (double)x[83] + (double)x[123])*MainFormSLS->hh[132];
sum_44 += ((double)x[4] + (double)x[44] + (double)x[84] + (double)x[124])*MainFormSLS->hh[16];
sum_44 += ((double)x[5] + (double)x[45] + (double)x[85] + (double)x[125])*MainFormSLS->hh[60];
sum_44 += ((double)x[6] + (double)x[46] + (double)x[86] + (double)x[126])*MainFormSLS->hh[104];
sum_44 += ((double)x[7] + (double)x[47] + (double)x[87] + (double)x[127])*MainFormSLS->hh[148];
sum_44 += ((double)x[8] + (double)x[48] + (double)x[88] + (double)x[128])*MainFormSLS->hh[32];
sum_44 += ((double)x[9] + (double)x[49] + (double)x[89] + (double)x[129])*MainFormSLS->hh[76];
sum_44 += ((double)x[10] + (double)x[50] + (double)x[90] + (double)x[130])*MainFormSLS->hh[120];
sum_44 += ((double)x[11] + (double)x[51] + (double)x[91] + (double)x[131])*MainFormSLS->hh[4];
sum_44 += ((double)x[12] + (double)x[52] + (double)x[92] + (double)x[132])*MainFormSLS->hh[48];
sum_44 += ((double)x[13] + (double)x[53] + (double)x[93] + (double)x[133])*MainFormSLS->hh[92];
sum_44 += ((double)x[14] + (double)x[54] + (double)x[94] + (double)x[134])*MainFormSLS->hh[136];
sum_44 += ((double)x[15] + (double)x[55] + (double)x[95] + (double)x[135])*MainFormSLS->hh[20];
sum_44 += ((double)x[16] + (double)x[56] + (double)x[96] + (double)x[136])*MainFormSLS->hh[64];
sum_44 += ((double)x[17] + (double)x[57] + (double)x[97] + (double)x[137])*MainFormSLS->hh[108];
sum_44 += ((double)x[18] + (double)x[58] + (double)x[98] + (double)x[138])*MainFormSLS->hh[152];
sum_44 += ((double)x[19] + (double)x[59] + (double)x[99] + (double)x[139])*MainFormSLS->hh[36];
sum_44 += ((double)x[20] + (double)x[60] + (double)x[100] + (double)x[140])*MainFormSLS->hh[80];
sum_44 += ((double)x[21] + (double)x[61] + (double)x[101] + (double)x[141])*MainFormSLS->hh[124];
sum_44 += ((double)x[22] + (double)x[62] + (double)x[102] + (double)x[142])*MainFormSLS->hh[8];
sum_44 += ((double)x[23] + (double)x[63] + (double)x[103] + (double)x[143])*MainFormSLS->hh[52];
sum_44 += ((double)x[24] + (double)x[64] + (double)x[104] + (double)x[144])*MainFormSLS->hh[96];
sum_44 += ((double)x[25] + (double)x[65] + (double)x[105] + (double)x[145])*MainFormSLS->hh[140];
sum_44 += ((double)x[26] + (double)x[66] + (double)x[106] + (double)x[146])*MainFormSLS->hh[24];
sum_44 += ((double)x[27] + (double)x[67] + (double)x[107] + (double)x[147])*MainFormSLS->hh[68];
sum_44 += ((double)x[28] + (double)x[68] + (double)x[108] + (double)x[148])*MainFormSLS->hh[112];
sum_44 += ((double)x[29] + (double)x[69] + (double)x[109] + (double)x[149])*MainFormSLS->hh[156];
sum_44 += ((double)x[30] + (double)x[70] + (double)x[110] + (double)x[150])*MainFormSLS->hh[40];
sum_44 += ((double)x[31] + (double)x[71] + (double)x[111] + (double)x[151])*MainFormSLS->hh[84];
sum_44 += ((double)x[32] + (double)x[72] + (double)x[112] + (double)x[152])*MainFormSLS->hh[128];
sum_44 += ((double)x[33] + (double)x[73] + (double)x[113] + (double)x[153])*MainFormSLS->hh[12];
sum_44 += ((double)x[34] + (double)x[74] + (double)x[114] + (double)x[154])*MainFormSLS->hh[56];
sum_44 += ((double)x[35] + (double)x[75] + (double)x[115] + (double)x[155])*MainFormSLS->hh[100];
sum_44 += ((double)x[36] + (double)x[76] + (double)x[116] + (double)x[156])*MainFormSLS->hh[144];
sum_44 += ((double)x[37] + (double)x[77] + (double)x[117] + (double)x[157])*MainFormSLS->hh[28];
sum_44 += ((double)x[38] + (double)x[78] + (double)x[118] + (double)x[158])*MainFormSLS->hh[72];
sum_44 += ((double)x[39] + (double)x[79] + (double)x[119] + (double)x[159])*MainFormSLS->hh[116];
}
//------------------------------------------------------------------------------
void __fastcall ddft_by_2(vector<short>& x,TCoeff_By_2& c2)
{
//коэффициенты с шагом 80 для id 2 100 Hz
double sum_80_0  = (double)x[0] + (double)x[80];
double sum_80_1  = (double)x[1] + (double)x[81];
double sum_80_2  = (double)x[2] + (double)x[82];
double sum_80_3  = (double)x[3] + (double)x[83];
double sum_80_4  = (double)x[4] + (double)x[84];
double sum_80_5  = (double)x[5] + (double)x[85];
double sum_80_6  = (double)x[6] + (double)x[86];
double sum_80_7  = (double)x[7] + (double)x[87];
double sum_80_8  = (double)x[8] + (double)x[88];
double sum_80_9  = (double)x[9] + (double)x[89];
double sum_80_10 = (double)x[10] + (double)x[90];
double sum_80_11 = (double)x[11] + (double)x[91];
double sum_80_12 = (double)x[12] + (double)x[92];
double sum_80_13 = (double)x[13] + (double)x[93];
double sum_80_14 = (double)x[14] + (double)x[94];
double sum_80_15 = (double)x[15] + (double)x[95];
double sum_80_16 = (double)x[16] + (double)x[96];
double sum_80_17 = (double)x[17] + (double)x[97];
double sum_80_18 = (double)x[18] + (double)x[98];
double sum_80_19 = (double)x[19] + (double)x[99];
double sum_80_20 = (double)x[20] + (double)x[100];
double sum_80_21 = (double)x[21] + (double)x[101];
double sum_80_22 = (double)x[22] + (double)x[102];
double sum_80_23 = (double)x[23] + (double)x[103];
double sum_80_24 = (double)x[24] + (double)x[104];
double sum_80_25 = (double)x[25] + (double)x[105];
double sum_80_26 = (double)x[26] + (double)x[106];
double sum_80_27 = (double)x[27] + (double)x[107];
double sum_80_28 = (double)x[28] + (double)x[108];
double sum_80_29 = (double)x[29] + (double)x[109];
double sum_80_30 = (double)x[30] + (double)x[110];
double sum_80_31 = (double)x[31] + (double)x[111];
double sum_80_32 = (double)x[32] + (double)x[112];
double sum_80_33 = (double)x[33] + (double)x[113];
double sum_80_34 = (double)x[34] + (double)x[114];
double sum_80_35 = (double)x[35] + (double)x[115];
double sum_80_36 = (double)x[36] + (double)x[116];
double sum_80_37 = (double)x[37] + (double)x[117];
double sum_80_38 = (double)x[38] + (double)x[118];
double sum_80_39 = (double)x[39] + (double)x[119];
double sum_80_40 = (double)x[40] + (double)x[120];
double sum_80_41 = (double)x[41] + (double)x[121];
double sum_80_42 = (double)x[42] + (double)x[122];
double sum_80_43 = (double)x[43] + (double)x[123];
double sum_80_44 = (double)x[44] + (double)x[124];
double sum_80_45 = (double)x[45] + (double)x[125];
double sum_80_46 = (double)x[46] + (double)x[126];
double sum_80_47 = (double)x[47] + (double)x[127];
double sum_80_48 = (double)x[48] + (double)x[128];
double sum_80_49 = (double)x[49] + (double)x[129];
double sum_80_50 = (double)x[50] + (double)x[130];
double sum_80_51 = (double)x[51] + (double)x[131];
double sum_80_52 = (double)x[52] + (double)x[132];
double sum_80_53 = (double)x[53] + (double)x[133];
double sum_80_54 = (double)x[54] + (double)x[134];
double sum_80_55 = (double)x[55] + (double)x[135];
double sum_80_56 = (double)x[56] + (double)x[136];
double sum_80_57 = (double)x[57] + (double)x[137];
double sum_80_58 = (double)x[58] + (double)x[138];
double sum_80_59 = (double)x[59] + (double)x[139];
double sum_80_60 = (double)x[60] + (double)x[140];
double sum_80_61 = (double)x[61] + (double)x[141];
double sum_80_62 = (double)x[62] + (double)x[142];
double sum_80_63 = (double)x[63] + (double)x[143];
double sum_80_64 = (double)x[64] + (double)x[144];
double sum_80_65 = (double)x[65] + (double)x[145];
double sum_80_66 = (double)x[66] + (double)x[146];
double sum_80_67 = (double)x[67] + (double)x[147];
double sum_80_68 = (double)x[68] + (double)x[148];
double sum_80_69 = (double)x[69] + (double)x[149];
double sum_80_70 = (double)x[70] + (double)x[150];
double sum_80_71 = (double)x[71] + (double)x[151];
double sum_80_72 = (double)x[72] + (double)x[152];
double sum_80_73 = (double)x[73] + (double)x[153];
double sum_80_74 = (double)x[74] + (double)x[154];
double sum_80_75 = (double)x[75] + (double)x[155];
double sum_80_76 = (double)x[76] + (double)x[156];
double sum_80_77 = (double)x[77] + (double)x[157];
double sum_80_78 = (double)x[78] + (double)x[158];
double sum_80_79 = (double)x[79] + (double)x[159];

//коэффициенты с шагом 40 для id 2 200 Hz
double sum_40_0  = sum_80_0  + sum_80_40;
double sum_40_1  = sum_80_1  + sum_80_41;
double sum_40_2  = sum_80_2  + sum_80_42;
double sum_40_3  = sum_80_3  + sum_80_43;
double sum_40_4  = sum_80_4  + sum_80_44;
double sum_40_5  = sum_80_5  + sum_80_45;
double sum_40_6  = sum_80_6  + sum_80_46;
double sum_40_7  = sum_80_7  + sum_80_47;
double sum_40_8  = sum_80_8  + sum_80_48;
double sum_40_9  = sum_80_9  + sum_80_49;
double sum_40_10 = sum_80_10 + sum_80_50;
double sum_40_11 = sum_80_11 + sum_80_51;
double sum_40_12 = sum_80_12 + sum_80_52;
double sum_40_13 = sum_80_13 + sum_80_53;
double sum_40_14 = sum_80_14 + sum_80_54;
double sum_40_15 = sum_80_15 + sum_80_55;
double sum_40_16 = sum_80_16 + sum_80_56;
double sum_40_17 = sum_80_17 + sum_80_57;
double sum_40_18 = sum_80_18 + sum_80_58;
double sum_40_19 = sum_80_19 + sum_80_59;
double sum_40_20 = sum_80_20 + sum_80_60;
double sum_40_21 = sum_80_21 + sum_80_61;
double sum_40_22 = sum_80_22 + sum_80_62;
double sum_40_23 = sum_80_23 + sum_80_63;
double sum_40_24 = sum_80_24 + sum_80_64;
double sum_40_25 = sum_80_25 + sum_80_65;
double sum_40_26 = sum_80_26 + sum_80_66;
double sum_40_27 = sum_80_27 + sum_80_67;
double sum_40_28 = sum_80_28 + sum_80_68;
double sum_40_29 = sum_80_29 + sum_80_69;
double sum_40_30 = sum_80_30 + sum_80_70;
double sum_40_31 = sum_80_31 + sum_80_71;
double sum_40_32 = sum_80_32 + sum_80_72;
double sum_40_33 = sum_80_33 + sum_80_73;
double sum_40_34 = sum_80_34 + sum_80_74;
double sum_40_35 = sum_80_35 + sum_80_75;
double sum_40_36 = sum_80_36 + sum_80_76;
double sum_40_37 = sum_80_37 + sum_80_77;
double sum_40_38 = sum_80_38 + sum_80_78;
double sum_40_39 = sum_80_39 + sum_80_79;

//-----------------------------------------------------------------------------
//id 2 100 Hz
c2.sum_2 += sum_80_0  * MainFormSLS->hh[0];
c2.sum_2 += sum_80_1  * MainFormSLS->hh[2];
c2.sum_2 += sum_80_2  * MainFormSLS->hh[4];
c2.sum_2 += sum_80_3  * MainFormSLS->hh[6];
c2.sum_2 += sum_80_4  * MainFormSLS->hh[8];
c2.sum_2 += sum_80_5  * MainFormSLS->hh[10];
c2.sum_2 += sum_80_6  * MainFormSLS->hh[12];
c2.sum_2 += sum_80_7  * MainFormSLS->hh[14];
c2.sum_2 += sum_80_8  * MainFormSLS->hh[16];
c2.sum_2 += sum_80_9  * MainFormSLS->hh[18];
c2.sum_2 += sum_80_10 * MainFormSLS->hh[20];
c2.sum_2 += sum_80_11 * MainFormSLS->hh[22];
c2.sum_2 += sum_80_12 * MainFormSLS->hh[24];
c2.sum_2 += sum_80_13 * MainFormSLS->hh[26];
c2.sum_2 += sum_80_14 * MainFormSLS->hh[28];
c2.sum_2 += sum_80_15 * MainFormSLS->hh[30];
c2.sum_2 += sum_80_16 * MainFormSLS->hh[32];
c2.sum_2 += sum_80_17 * MainFormSLS->hh[34];
c2.sum_2 += sum_80_18 * MainFormSLS->hh[36];
c2.sum_2 += sum_80_19 * MainFormSLS->hh[38];
c2.sum_2 += sum_80_20 * MainFormSLS->hh[40];
c2.sum_2 += sum_80_21 * MainFormSLS->hh[42];
c2.sum_2 += sum_80_22 * MainFormSLS->hh[44];
c2.sum_2 += sum_80_23 * MainFormSLS->hh[46];
c2.sum_2 += sum_80_24 * MainFormSLS->hh[48];
c2.sum_2 += sum_80_25 * MainFormSLS->hh[50];
c2.sum_2 += sum_80_26 * MainFormSLS->hh[52];
c2.sum_2 += sum_80_27 * MainFormSLS->hh[54];
c2.sum_2 += sum_80_28 * MainFormSLS->hh[56];
c2.sum_2 += sum_80_29 * MainFormSLS->hh[58];
c2.sum_2 += sum_80_30 * MainFormSLS->hh[60];
c2.sum_2 += sum_80_31 * MainFormSLS->hh[62];
c2.sum_2 += sum_80_32 * MainFormSLS->hh[64];
c2.sum_2 += sum_80_33 * MainFormSLS->hh[66];
c2.sum_2 += sum_80_34 * MainFormSLS->hh[68];
c2.sum_2 += sum_80_35 * MainFormSLS->hh[70];
c2.sum_2 += sum_80_36 * MainFormSLS->hh[72];
c2.sum_2 += sum_80_37 * MainFormSLS->hh[74];
c2.sum_2 += sum_80_38 * MainFormSLS->hh[76];
c2.sum_2 += sum_80_39 * MainFormSLS->hh[78];
c2.sum_2 += sum_80_40 * MainFormSLS->hh[80];
c2.sum_2 += sum_80_41 * MainFormSLS->hh[82];
c2.sum_2 += sum_80_42 * MainFormSLS->hh[84];
c2.sum_2 += sum_80_43 * MainFormSLS->hh[86];
c2.sum_2 += sum_80_44 * MainFormSLS->hh[88];
c2.sum_2 += sum_80_45 * MainFormSLS->hh[90];
c2.sum_2 += sum_80_46 * MainFormSLS->hh[92];
c2.sum_2 += sum_80_47 * MainFormSLS->hh[94];
c2.sum_2 += sum_80_48 * MainFormSLS->hh[96];
c2.sum_2 += sum_80_49 * MainFormSLS->hh[98];
c2.sum_2 += sum_80_50 * MainFormSLS->hh[100];
c2.sum_2 += sum_80_51 * MainFormSLS->hh[102];
c2.sum_2 += sum_80_52 * MainFormSLS->hh[104];
c2.sum_2 += sum_80_53 * MainFormSLS->hh[106];
c2.sum_2 += sum_80_54 * MainFormSLS->hh[108];
c2.sum_2 += sum_80_55 * MainFormSLS->hh[110];
c2.sum_2 += sum_80_56 * MainFormSLS->hh[112];
c2.sum_2 += sum_80_57 * MainFormSLS->hh[114];
c2.sum_2 += sum_80_58 * MainFormSLS->hh[116];
c2.sum_2 += sum_80_59 * MainFormSLS->hh[118];
c2.sum_2 += sum_80_60 * MainFormSLS->hh[120];
c2.sum_2 += sum_80_61 * MainFormSLS->hh[122];
c2.sum_2 += sum_80_62 * MainFormSLS->hh[124];
c2.sum_2 += sum_80_63 * MainFormSLS->hh[126];
c2.sum_2 += sum_80_64 * MainFormSLS->hh[128];
c2.sum_2 += sum_80_65 * MainFormSLS->hh[130];
c2.sum_2 += sum_80_66 * MainFormSLS->hh[132];
c2.sum_2 += sum_80_67 * MainFormSLS->hh[134];
c2.sum_2 += sum_80_68 * MainFormSLS->hh[136];
c2.sum_2 += sum_80_69 * MainFormSLS->hh[138];
c2.sum_2 += sum_80_70 * MainFormSLS->hh[140];
c2.sum_2 += sum_80_71 * MainFormSLS->hh[142];
c2.sum_2 += sum_80_72 * MainFormSLS->hh[144];
c2.sum_2 += sum_80_73 * MainFormSLS->hh[146];
c2.sum_2 += sum_80_74 * MainFormSLS->hh[148];
c2.sum_2 += sum_80_75 * MainFormSLS->hh[150];
c2.sum_2 += sum_80_76 * MainFormSLS->hh[152];
c2.sum_2 += sum_80_77 * MainFormSLS->hh[154];
c2.sum_2 += sum_80_78 * MainFormSLS->hh[156];
c2.sum_2 += sum_80_79 * MainFormSLS->hh[158];

//id 4 200 Hz
c2.sum_4 += sum_40_0  * MainFormSLS->hh[0];
c2.sum_4 += sum_40_1  * MainFormSLS->hh[4];
c2.sum_4 += sum_40_2  * MainFormSLS->hh[8];
c2.sum_4 += sum_40_3  * MainFormSLS->hh[12];
c2.sum_4 += sum_40_4  * MainFormSLS->hh[16];
c2.sum_4 += sum_40_5  * MainFormSLS->hh[20];
c2.sum_4 += sum_40_6  * MainFormSLS->hh[24];
c2.sum_4 += sum_40_7  * MainFormSLS->hh[28];
c2.sum_4 += sum_40_8  * MainFormSLS->hh[32];
c2.sum_4 += sum_40_9  * MainFormSLS->hh[36];
c2.sum_4 += sum_40_10 * MainFormSLS->hh[40];
c2.sum_4 += sum_40_11 * MainFormSLS->hh[44];
c2.sum_4 += sum_40_12 * MainFormSLS->hh[48];
c2.sum_4 += sum_40_13 * MainFormSLS->hh[52];
c2.sum_4 += sum_40_14 * MainFormSLS->hh[56];
c2.sum_4 += sum_40_15 * MainFormSLS->hh[60];
c2.sum_4 += sum_40_16 * MainFormSLS->hh[64];
c2.sum_4 += sum_40_17 * MainFormSLS->hh[68];
c2.sum_4 += sum_40_18 * MainFormSLS->hh[72];
c2.sum_4 += sum_40_19 * MainFormSLS->hh[76];
c2.sum_4 += sum_40_20 * MainFormSLS->hh[80];
c2.sum_4 += sum_40_21 * MainFormSLS->hh[84];
c2.sum_4 += sum_40_22 * MainFormSLS->hh[88];
c2.sum_4 += sum_40_23 * MainFormSLS->hh[92];
c2.sum_4 += sum_40_24 * MainFormSLS->hh[96];
c2.sum_4 += sum_40_25 * MainFormSLS->hh[100];
c2.sum_4 += sum_40_26 * MainFormSLS->hh[104];
c2.sum_4 += sum_40_27 * MainFormSLS->hh[108];
c2.sum_4 += sum_40_28 * MainFormSLS->hh[112];
c2.sum_4 += sum_40_29 * MainFormSLS->hh[116];
c2.sum_4 += sum_40_30 * MainFormSLS->hh[120];
c2.sum_4 += sum_40_31 * MainFormSLS->hh[124];
c2.sum_4 += sum_40_32 * MainFormSLS->hh[128];
c2.sum_4 += sum_40_33 * MainFormSLS->hh[132];
c2.sum_4 += sum_40_34 * MainFormSLS->hh[136];
c2.sum_4 += sum_40_35 * MainFormSLS->hh[140];
c2.sum_4 += sum_40_36 * MainFormSLS->hh[144];
c2.sum_4 += sum_40_37 * MainFormSLS->hh[148];
c2.sum_4 += sum_40_38 * MainFormSLS->hh[152];
c2.sum_4 += sum_40_39 * MainFormSLS->hh[156];

}
//------------------------------------------------------------------------------
void __fastcall ddft_by_5(vector<short>& x,TCoeff_By_5& c5)
{
//коэффициенты с шагом 32
double sum_32_0  = (double)x[0] + (double)x[32] + (double)x[64] + (double)x[96] + (double)x[128];
double sum_32_1  = (double)x[1] + (double)x[33] + (double)x[65] + (double)x[97] + (double)x[129];
double sum_32_2  = (double)x[2] + (double)x[34] + (double)x[66] + (double)x[98] + (double)x[130];
double sum_32_3  = (double)x[3] + (double)x[35] + (double)x[67] + (double)x[99] + (double)x[131];
double sum_32_4  = (double)x[4] + (double)x[36] + (double)x[68] + (double)x[100] + (double)x[132];
double sum_32_5  = (double)x[5] + (double)x[37] + (double)x[69] + (double)x[101] + (double)x[133];
double sum_32_6  = (double)x[6] + (double)x[38] + (double)x[70] + (double)x[102] + (double)x[134];
double sum_32_7  = (double)x[7] + (double)x[39] + (double)x[71] + (double)x[103] + (double)x[135];
double sum_32_8  = (double)x[8] + (double)x[40] + (double)x[72] + (double)x[104] + (double)x[136];
double sum_32_9  = (double)x[9] + (double)x[41] + (double)x[73] + (double)x[105] + (double)x[137];
double sum_32_10 = (double)x[10] + (double)x[42] + (double)x[74] + (double)x[106] + (double)x[138];
double sum_32_11 = (double)x[11] + (double)x[43] + (double)x[75] + (double)x[107] + (double)x[139];
double sum_32_12 = (double)x[12] + (double)x[44] + (double)x[76] + (double)x[108] + (double)x[140];
double sum_32_13 = (double)x[13] + (double)x[45] + (double)x[77] + (double)x[109] + (double)x[141];
double sum_32_14 = (double)x[14] + (double)x[46] + (double)x[78] + (double)x[110] + (double)x[142];
double sum_32_15 = (double)x[15] + (double)x[47] + (double)x[79] + (double)x[111] + (double)x[143];
double sum_32_16 = (double)x[16] + (double)x[48] + (double)x[80] + (double)x[112] + (double)x[144];
double sum_32_17 = (double)x[17] + (double)x[49] + (double)x[81] + (double)x[113] + (double)x[145];
double sum_32_18 = (double)x[18] + (double)x[50] + (double)x[82] + (double)x[114] + (double)x[146];
double sum_32_19 = (double)x[19] + (double)x[51] + (double)x[83] + (double)x[115] + (double)x[147];
double sum_32_20 = (double)x[20] + (double)x[52] + (double)x[84] + (double)x[116] + (double)x[148];
double sum_32_21 = (double)x[21] + (double)x[53] + (double)x[85] + (double)x[117] + (double)x[149];
double sum_32_22 = (double)x[22] + (double)x[54] + (double)x[86] + (double)x[118] + (double)x[150];
double sum_32_23 = (double)x[23] + (double)x[55] + (double)x[87] + (double)x[119] + (double)x[151];
double sum_32_24 = (double)x[24] + (double)x[56] + (double)x[88] + (double)x[120] + (double)x[152];
double sum_32_25 = (double)x[25] + (double)x[57] + (double)x[89] + (double)x[121] + (double)x[153];
double sum_32_26 = (double)x[26] + (double)x[58] + (double)x[90] + (double)x[122] + (double)x[154];
double sum_32_27 = (double)x[27] + (double)x[59] + (double)x[91] + (double)x[123] + (double)x[155];
double sum_32_28 = (double)x[28] + (double)x[60] + (double)x[92] + (double)x[124] + (double)x[156];
double sum_32_29 = (double)x[29] + (double)x[61] + (double)x[93] + (double)x[125] + (double)x[157];
double sum_32_30 = (double)x[30] + (double)x[62] + (double)x[94] + (double)x[126] + (double)x[158];
double sum_32_31 = (double)x[31] + (double)x[63] + (double)x[95] + (double)x[127] + (double)x[159];

//коэффициенты с шагом 16
/*
double sum_16_0  = sum_32_0  + sum_32_16;
double sum_16_1  = sum_32_1  + sum_32_17;
double sum_16_2  = sum_32_2  + sum_32_18;
double sum_16_3  = sum_32_3  + sum_32_19;
double sum_16_4  = sum_32_4  + sum_32_20;
double sum_16_5  = sum_32_5  + sum_32_21;
double sum_16_6  = sum_32_6  + sum_32_22;
double sum_16_7  = sum_32_7  + sum_32_23;
double sum_16_8  = sum_32_8  + sum_32_24;
double sum_16_9  = sum_32_9  + sum_32_25;
double sum_16_10 = sum_32_10 + sum_32_26;
double sum_16_11 = sum_32_11 + sum_32_27;
double sum_16_12 = sum_32_12 + sum_32_28;
double sum_16_13 = sum_32_13 + sum_32_29;
double sum_16_14 = sum_32_14 + sum_32_30;
double sum_16_15 = sum_32_15 + sum_32_31;

//коэффициенты с шагом 8
double sum_8_0  = sum_16_0 + sum_16_8;
double sum_8_1  = sum_16_1 + sum_16_9;
double sum_8_2  = sum_16_2 + sum_16_10;
double sum_8_3  = sum_16_3 + sum_16_11;
double sum_8_4  = sum_16_4 + sum_16_12;
double sum_8_5  = sum_16_5 + sum_16_13;
double sum_8_6  = sum_16_6 + sum_16_14;
double sum_8_7  = sum_16_7 + sum_16_15;

//коэффициенты с шагом 4
//double sum_4_0 = sum_8_0 + sum_8_4;
//double sum_4_1 = sum_8_1 + sum_8_5;
//double sum_4_2 = sum_8_2 + sum_8_6;
//double sum_4_3 = sum_8_3 + sum_8_7;

*/


//---------------------------------------------------------------------------
//id 5 250 Hz
c5.sum_5 += sum_32_0  * MainFormSLS->hh[0];
c5.sum_5 += sum_32_1  * MainFormSLS->hh[5];
c5.sum_5 += sum_32_2  * MainFormSLS->hh[10];
c5.sum_5 += sum_32_3  * MainFormSLS->hh[15];
c5.sum_5 += sum_32_4  * MainFormSLS->hh[20];
c5.sum_5 += sum_32_5  * MainFormSLS->hh[25];
c5.sum_5 += sum_32_6  * MainFormSLS->hh[30];
c5.sum_5 += sum_32_7  * MainFormSLS->hh[35];
c5.sum_5 += sum_32_8  * MainFormSLS->hh[40];
c5.sum_5 += sum_32_9  * MainFormSLS->hh[45];
c5.sum_5 += sum_32_10 * MainFormSLS->hh[50];
c5.sum_5 += sum_32_11 * MainFormSLS->hh[55];
c5.sum_5 += sum_32_12 * MainFormSLS->hh[60];
c5.sum_5 += sum_32_13 * MainFormSLS->hh[65];
c5.sum_5 += sum_32_14 * MainFormSLS->hh[70];
c5.sum_5 += sum_32_15 * MainFormSLS->hh[75];
c5.sum_5 += sum_32_16 * MainFormSLS->hh[80];
c5.sum_5 += sum_32_17 * MainFormSLS->hh[85];
c5.sum_5 += sum_32_18 * MainFormSLS->hh[90];
c5.sum_5 += sum_32_19 * MainFormSLS->hh[95];
c5.sum_5 += sum_32_20 * MainFormSLS->hh[100];
c5.sum_5 += sum_32_21 * MainFormSLS->hh[105];
c5.sum_5 += sum_32_22 * MainFormSLS->hh[110];
c5.sum_5 += sum_32_23 * MainFormSLS->hh[115];
c5.sum_5 += sum_32_24 * MainFormSLS->hh[120];
c5.sum_5 += sum_32_25 * MainFormSLS->hh[125];
c5.sum_5 += sum_32_26 * MainFormSLS->hh[130];
c5.sum_5 += sum_32_27 * MainFormSLS->hh[135];
c5.sum_5 += sum_32_28 * MainFormSLS->hh[140];
c5.sum_5 += sum_32_29 * MainFormSLS->hh[145];
c5.sum_5 += sum_32_30 * MainFormSLS->hh[150];
c5.sum_5 += sum_32_31 * MainFormSLS->hh[155];

/*
//id 10 500 Hz
c5.sum_10 += sum_16_0  * MainFormSLS->hh[0];
c5.sum_10 += sum_16_1  * MainFormSLS->hh[10];
c5.sum_10 += sum_16_2  * MainFormSLS->hh[20];
c5.sum_10 += sum_16_3  * MainFormSLS->hh[30];
c5.sum_10 += sum_16_4  * MainFormSLS->hh[40];
c5.sum_10 += sum_16_5  * MainFormSLS->hh[50];
c5.sum_10 += sum_16_6  * MainFormSLS->hh[60];
c5.sum_10 += sum_16_7  * MainFormSLS->hh[70];
c5.sum_10 += sum_16_8  * MainFormSLS->hh[80];
c5.sum_10 += sum_16_9  * MainFormSLS->hh[90];
c5.sum_10 += sum_16_10 * MainFormSLS->hh[100];
c5.sum_10 += sum_16_11 * MainFormSLS->hh[110];
c5.sum_10 += sum_16_12 * MainFormSLS->hh[120];
c5.sum_10 += sum_16_13 * MainFormSLS->hh[130];
c5.sum_10 += sum_16_14 * MainFormSLS->hh[140];
c5.sum_10 += sum_16_15 * MainFormSLS->hh[150];
 */

//id 15 750 Hz
c5.sum_15 += sum_32_0  * MainFormSLS->hh[0];
c5.sum_15 += sum_32_1  * MainFormSLS->hh[15];
c5.sum_15 += sum_32_2  * MainFormSLS->hh[30];
c5.sum_15 += sum_32_3  * MainFormSLS->hh[45];
c5.sum_15 += sum_32_4  * MainFormSLS->hh[60];
c5.sum_15 += sum_32_5  * MainFormSLS->hh[75];
c5.sum_15 += sum_32_6  * MainFormSLS->hh[90];
c5.sum_15 += sum_32_7  * MainFormSLS->hh[105];
c5.sum_15 += sum_32_8  * MainFormSLS->hh[120];
c5.sum_15 += sum_32_9  * MainFormSLS->hh[135];
c5.sum_15 += sum_32_10 * MainFormSLS->hh[150];
c5.sum_15 += sum_32_11 * MainFormSLS->hh[5];
c5.sum_15 += sum_32_12 * MainFormSLS->hh[20];
c5.sum_15 += sum_32_13 * MainFormSLS->hh[35];
c5.sum_15 += sum_32_14 * MainFormSLS->hh[50];
c5.sum_15 += sum_32_15 * MainFormSLS->hh[65];
c5.sum_15 += sum_32_16 * MainFormSLS->hh[80];
c5.sum_15 += sum_32_17 * MainFormSLS->hh[95];
c5.sum_15 += sum_32_18 * MainFormSLS->hh[110];
c5.sum_15 += sum_32_19 * MainFormSLS->hh[125];
c5.sum_15 += sum_32_20 * MainFormSLS->hh[140];
c5.sum_15 += sum_32_21 * MainFormSLS->hh[155];
c5.sum_15 += sum_32_22 * MainFormSLS->hh[10];
c5.sum_15 += sum_32_23 * MainFormSLS->hh[25];
c5.sum_15 += sum_32_24 * MainFormSLS->hh[40];
c5.sum_15 += sum_32_25 * MainFormSLS->hh[55];
c5.sum_15 += sum_32_26 * MainFormSLS->hh[70];
c5.sum_15 += sum_32_27 * MainFormSLS->hh[85];
c5.sum_15 += sum_32_28 * MainFormSLS->hh[100];
c5.sum_15 += sum_32_29 * MainFormSLS->hh[115];
c5.sum_15 += sum_32_30 * MainFormSLS->hh[130];
c5.sum_15 += sum_32_31 * MainFormSLS->hh[145];

/*
//id 20 1000 Hz
c5.sum_20 += sum_8_0 * MainFormSLS->hh[0];
c5.sum_20 += sum_8_1 * MainFormSLS->hh[20];
c5.sum_20 += sum_8_2 * MainFormSLS->hh[40];
c5.sum_20 += sum_8_3 * MainFormSLS->hh[60];
c5.sum_20 += sum_8_4 * MainFormSLS->hh[80];
c5.sum_20 += sum_8_5 * MainFormSLS->hh[100];
c5.sum_20 += sum_8_6 * MainFormSLS->hh[120];
c5.sum_20 += sum_8_7 * MainFormSLS->hh[140];
*/

//id 25 1250 Hz
c5.sum_25 += sum_32_0  * MainFormSLS->hh[0];
c5.sum_25 += sum_32_1  * MainFormSLS->hh[25];
c5.sum_25 += sum_32_2  * MainFormSLS->hh[50];
c5.sum_25 += sum_32_3  * MainFormSLS->hh[75];
c5.sum_25 += sum_32_4  * MainFormSLS->hh[100];
c5.sum_25 += sum_32_5  * MainFormSLS->hh[125];
c5.sum_25 += sum_32_6  * MainFormSLS->hh[150];
c5.sum_25 += sum_32_7  * MainFormSLS->hh[15];
c5.sum_25 += sum_32_8  * MainFormSLS->hh[40];
c5.sum_25 += sum_32_9  * MainFormSLS->hh[65];
c5.sum_25 += sum_32_10 * MainFormSLS->hh[90];
c5.sum_25 += sum_32_11 * MainFormSLS->hh[115];
c5.sum_25 += sum_32_12 * MainFormSLS->hh[140];
c5.sum_25 += sum_32_13 * MainFormSLS->hh[5];
c5.sum_25 += sum_32_14 * MainFormSLS->hh[30];
c5.sum_25 += sum_32_15 * MainFormSLS->hh[55];
c5.sum_25 += sum_32_16 * MainFormSLS->hh[80];
c5.sum_25 += sum_32_17 * MainFormSLS->hh[105];
c5.sum_25 += sum_32_18 * MainFormSLS->hh[130];
c5.sum_25 += sum_32_19 * MainFormSLS->hh[155];
c5.sum_25 += sum_32_20 * MainFormSLS->hh[20];
c5.sum_25 += sum_32_21 * MainFormSLS->hh[45];
c5.sum_25 += sum_32_22 * MainFormSLS->hh[70];
c5.sum_25 += sum_32_23 * MainFormSLS->hh[95];
c5.sum_25 += sum_32_24 * MainFormSLS->hh[120];
c5.sum_25 += sum_32_25 * MainFormSLS->hh[145];
c5.sum_25 += sum_32_26 * MainFormSLS->hh[10];
c5.sum_25 += sum_32_27 * MainFormSLS->hh[35];
c5.sum_25 += sum_32_28 * MainFormSLS->hh[60];
c5.sum_25 += sum_32_29 * MainFormSLS->hh[85];
c5.sum_25 += sum_32_30 * MainFormSLS->hh[110];
c5.sum_25 += sum_32_31 * MainFormSLS->hh[135];

/*
//id 30 1500 Hz
c5.sum_30 += sum_16_0  * MainFormSLS->hh[0];
c5.sum_30 += sum_16_1  * MainFormSLS->hh[30];
c5.sum_30 += sum_16_2  * MainFormSLS->hh[60];
c5.sum_30 += sum_16_3  * MainFormSLS->hh[90];
c5.sum_30 += sum_16_4  * MainFormSLS->hh[120];
c5.sum_30 += sum_16_5  * MainFormSLS->hh[150];
c5.sum_30 += sum_16_6  * MainFormSLS->hh[20];
c5.sum_30 += sum_16_7  * MainFormSLS->hh[50];
c5.sum_30 += sum_16_8  * MainFormSLS->hh[80];
c5.sum_30 += sum_16_9  * MainFormSLS->hh[110];
c5.sum_30 += sum_16_10 * MainFormSLS->hh[140];
c5.sum_30 += sum_16_11 * MainFormSLS->hh[10];
c5.sum_30 += sum_16_12 * MainFormSLS->hh[40];
c5.sum_30 += sum_16_13 * MainFormSLS->hh[70];
c5.sum_30 += sum_16_14 * MainFormSLS->hh[100];
c5.sum_30 += sum_16_15 * MainFormSLS->hh[130];
  */

//id 35 1750 Hz
c5.sum_35 += sum_32_0  * MainFormSLS->hh[0];
c5.sum_35 += sum_32_1  * MainFormSLS->hh[35];
c5.sum_35 += sum_32_2  * MainFormSLS->hh[70];
c5.sum_35 += sum_32_3  * MainFormSLS->hh[105];
c5.sum_35 += sum_32_4  * MainFormSLS->hh[140];
c5.sum_35 += sum_32_5  * MainFormSLS->hh[15];
c5.sum_35 += sum_32_6  * MainFormSLS->hh[50];
c5.sum_35 += sum_32_7  * MainFormSLS->hh[85];
c5.sum_35 += sum_32_8  * MainFormSLS->hh[120];
c5.sum_35 += sum_32_9  * MainFormSLS->hh[155];
c5.sum_35 += sum_32_10 * MainFormSLS->hh[30];
c5.sum_35 += sum_32_11 * MainFormSLS->hh[65];
c5.sum_35 += sum_32_12 * MainFormSLS->hh[100];
c5.sum_35 += sum_32_13 * MainFormSLS->hh[135];
c5.sum_35 += sum_32_14 * MainFormSLS->hh[10];
c5.sum_35 += sum_32_15 * MainFormSLS->hh[45];
c5.sum_35 += sum_32_16 * MainFormSLS->hh[80];
c5.sum_35 += sum_32_17 * MainFormSLS->hh[115];
c5.sum_35 += sum_32_18 * MainFormSLS->hh[150];
c5.sum_35 += sum_32_19 * MainFormSLS->hh[25];
c5.sum_35 += sum_32_20 * MainFormSLS->hh[60];
c5.sum_35 += sum_32_21 * MainFormSLS->hh[95];
c5.sum_35 += sum_32_22 * MainFormSLS->hh[130];
c5.sum_35 += sum_32_23 * MainFormSLS->hh[5];
c5.sum_35 += sum_32_24 * MainFormSLS->hh[40];
c5.sum_35 += sum_32_25 * MainFormSLS->hh[75];
c5.sum_35 += sum_32_26 * MainFormSLS->hh[110];
c5.sum_35 += sum_32_27 * MainFormSLS->hh[145];
c5.sum_35 += sum_32_28 * MainFormSLS->hh[20];
c5.sum_35 += sum_32_29 * MainFormSLS->hh[55];
c5.sum_35 += sum_32_30 * MainFormSLS->hh[90];
c5.sum_35 += sum_32_31 * MainFormSLS->hh[125];

/*
//id 40 2000 Hz
c5.sum_40 += sum_4_0 * MainFormSLS->hh[0];
c5.sum_40 += sum_4_1 * MainFormSLS->hh[40];
c5.sum_40 += sum_4_2 * MainFormSLS->hh[80];
c5.sum_40 += sum_4_3 * MainFormSLS->hh[120];
*/
//id 45 2250 Hz
c5.sum_45 += sum_32_0  * MainFormSLS->hh[0];
c5.sum_45 += sum_32_1  * MainFormSLS->hh[45];
c5.sum_45 += sum_32_2  * MainFormSLS->hh[90];
c5.sum_45 += sum_32_3  * MainFormSLS->hh[135];
c5.sum_45 += sum_32_4  * MainFormSLS->hh[20];
c5.sum_45 += sum_32_5  * MainFormSLS->hh[65];
c5.sum_45 += sum_32_6  * MainFormSLS->hh[110];
c5.sum_45 += sum_32_7  * MainFormSLS->hh[155];
c5.sum_45 += sum_32_8  * MainFormSLS->hh[40];
c5.sum_45 += sum_32_9  * MainFormSLS->hh[85];
c5.sum_45 += sum_32_10 * MainFormSLS->hh[130];
c5.sum_45 += sum_32_11 * MainFormSLS->hh[15];
c5.sum_45 += sum_32_12 * MainFormSLS->hh[60];
c5.sum_45 += sum_32_13 * MainFormSLS->hh[105];
c5.sum_45 += sum_32_14 * MainFormSLS->hh[150];
c5.sum_45 += sum_32_15 * MainFormSLS->hh[35];
c5.sum_45 += sum_32_16 * MainFormSLS->hh[80];
c5.sum_45 += sum_32_17 * MainFormSLS->hh[125];
c5.sum_45 += sum_32_18 * MainFormSLS->hh[10];
c5.sum_45 += sum_32_19 * MainFormSLS->hh[55];
c5.sum_45 += sum_32_20 * MainFormSLS->hh[100];
c5.sum_45 += sum_32_21 * MainFormSLS->hh[145];
c5.sum_45 += sum_32_22 * MainFormSLS->hh[30];
c5.sum_45 += sum_32_23 * MainFormSLS->hh[75];
c5.sum_45 += sum_32_24 * MainFormSLS->hh[120];
c5.sum_45 += sum_32_25 * MainFormSLS->hh[5];
c5.sum_45 += sum_32_26 * MainFormSLS->hh[50];
c5.sum_45 += sum_32_27 * MainFormSLS->hh[95];
c5.sum_45 += sum_32_28 * MainFormSLS->hh[140];
c5.sum_45 += sum_32_29 * MainFormSLS->hh[25];
c5.sum_45 += sum_32_30 * MainFormSLS->hh[70];
c5.sum_45 += sum_32_31 * MainFormSLS->hh[115];
/*
//id 50 2500 Hz
c5.sum_50 += sum_16_0  *MainFormSLS->hh[0];
c5.sum_50 += sum_16_1  *MainFormSLS->hh[50];
c5.sum_50 += sum_16_2  *MainFormSLS->hh[100];
c5.sum_50 += sum_16_3  *MainFormSLS->hh[150];
c5.sum_50 += sum_16_4  *MainFormSLS->hh[40];
c5.sum_50 += sum_16_5  *MainFormSLS->hh[90];
c5.sum_50 += sum_16_6  *MainFormSLS->hh[140];
c5.sum_50 += sum_16_7  *MainFormSLS->hh[30];
c5.sum_50 += sum_16_8  *MainFormSLS->hh[80];
c5.sum_50 += sum_16_9  *MainFormSLS->hh[130];
c5.sum_50 += sum_16_10 *MainFormSLS->hh[20];
c5.sum_50 += sum_16_11 *MainFormSLS->hh[70];
c5.sum_50 += sum_16_12 *MainFormSLS->hh[120];
c5.sum_50 += sum_16_13 *MainFormSLS->hh[10];
c5.sum_50 += sum_16_14 *MainFormSLS->hh[60];
c5.sum_50 += sum_16_15 *MainFormSLS->hh[110];
 */
//id 55 2750 Hz
c5.sum_55 += sum_32_0  * MainFormSLS->hh[0];
c5.sum_55 += sum_32_1  * MainFormSLS->hh[55];
c5.sum_55 += sum_32_2  * MainFormSLS->hh[110];
c5.sum_55 += sum_32_3  * MainFormSLS->hh[5];
c5.sum_55 += sum_32_4  * MainFormSLS->hh[60];
c5.sum_55 += sum_32_5  * MainFormSLS->hh[115];
c5.sum_55 += sum_32_6  * MainFormSLS->hh[10];
c5.sum_55 += sum_32_7  * MainFormSLS->hh[65];
c5.sum_55 += sum_32_8  * MainFormSLS->hh[120];
c5.sum_55 += sum_32_9  * MainFormSLS->hh[15];
c5.sum_55 += sum_32_10 * MainFormSLS->hh[70];
c5.sum_55 += sum_32_11 * MainFormSLS->hh[125];
c5.sum_55 += sum_32_12 * MainFormSLS->hh[20];
c5.sum_55 += sum_32_13 * MainFormSLS->hh[75];
c5.sum_55 += sum_32_14 * MainFormSLS->hh[130];
c5.sum_55 += sum_32_15 * MainFormSLS->hh[25];
c5.sum_55 += sum_32_16 * MainFormSLS->hh[80];
c5.sum_55 += sum_32_17 * MainFormSLS->hh[135];
c5.sum_55 += sum_32_18 * MainFormSLS->hh[30];
c5.sum_55 += sum_32_19 * MainFormSLS->hh[85];
c5.sum_55 += sum_32_20 * MainFormSLS->hh[140];
c5.sum_55 += sum_32_21 * MainFormSLS->hh[35];
c5.sum_55 += sum_32_22 * MainFormSLS->hh[90];
c5.sum_55 += sum_32_23 * MainFormSLS->hh[145];
c5.sum_55 += sum_32_24 * MainFormSLS->hh[40];
c5.sum_55 += sum_32_25 * MainFormSLS->hh[95];
c5.sum_55 += sum_32_26 * MainFormSLS->hh[150];
c5.sum_55 += sum_32_27 * MainFormSLS->hh[45];
c5.sum_55 += sum_32_28 * MainFormSLS->hh[100];
c5.sum_55 += sum_32_29 * MainFormSLS->hh[155];
c5.sum_55 += sum_32_30 * MainFormSLS->hh[50];
c5.sum_55 += sum_32_31 * MainFormSLS->hh[105];

/*
//id 60 3000 Hz
c5.sum_60 += sum_8_0 * MainFormSLS->hh[0];
c5.sum_60 += sum_8_1 * MainFormSLS->hh[60];
c5.sum_60 += sum_8_2 * MainFormSLS->hh[120];
c5.sum_60 += sum_8_3 * MainFormSLS->hh[20];
c5.sum_60 += sum_8_4 * MainFormSLS->hh[80];
c5.sum_60 += sum_8_5 * MainFormSLS->hh[140];
c5.sum_60 += sum_8_6 * MainFormSLS->hh[40];
c5.sum_60 += sum_8_7 * MainFormSLS->hh[100];
*/
//id 65 3250 Hz
c5.sum_65 += sum_32_0  * MainFormSLS->hh[0];
c5.sum_65 += sum_32_1  * MainFormSLS->hh[65];
c5.sum_65 += sum_32_2  * MainFormSLS->hh[130];
c5.sum_65 += sum_32_3  * MainFormSLS->hh[35];
c5.sum_65 += sum_32_4  * MainFormSLS->hh[100];
c5.sum_65 += sum_32_5  * MainFormSLS->hh[5];
c5.sum_65 += sum_32_6  * MainFormSLS->hh[70];
c5.sum_65 += sum_32_7  * MainFormSLS->hh[135];
c5.sum_65 += sum_32_8  * MainFormSLS->hh[40];
c5.sum_65 += sum_32_9  * MainFormSLS->hh[105];
c5.sum_65 += sum_32_10 * MainFormSLS->hh[10];
c5.sum_65 += sum_32_11 * MainFormSLS->hh[75];
c5.sum_65 += sum_32_12 * MainFormSLS->hh[140];
c5.sum_65 += sum_32_13 * MainFormSLS->hh[45];
c5.sum_65 += sum_32_14 * MainFormSLS->hh[110];
c5.sum_65 += sum_32_15 * MainFormSLS->hh[15];
c5.sum_65 += sum_32_16 * MainFormSLS->hh[80];
c5.sum_65 += sum_32_17 * MainFormSLS->hh[145];
c5.sum_65 += sum_32_18 * MainFormSLS->hh[50];
c5.sum_65 += sum_32_19 * MainFormSLS->hh[115];
c5.sum_65 += sum_32_20 * MainFormSLS->hh[20];
c5.sum_65 += sum_32_21 * MainFormSLS->hh[85];
c5.sum_65 += sum_32_22 * MainFormSLS->hh[150];
c5.sum_65 += sum_32_23 * MainFormSLS->hh[55];
c5.sum_65 += sum_32_24 * MainFormSLS->hh[120];
c5.sum_65 += sum_32_25 * MainFormSLS->hh[25];
c5.sum_65 += sum_32_26 * MainFormSLS->hh[90];
c5.sum_65 += sum_32_27 * MainFormSLS->hh[155];
c5.sum_65 += sum_32_28 * MainFormSLS->hh[60];
c5.sum_65 += sum_32_29 * MainFormSLS->hh[125];
c5.sum_65 += sum_32_30 * MainFormSLS->hh[30];
c5.sum_65 += sum_32_31 * MainFormSLS->hh[95];
/*
//id 70 3500 Hz
c5.sum_70 += sum_16_0  *MainFormSLS->hh[0];
c5.sum_70 += sum_16_1  *MainFormSLS->hh[70];
c5.sum_70 += sum_16_2  *MainFormSLS->hh[140];
c5.sum_70 += sum_16_3  *MainFormSLS->hh[50];
c5.sum_70 += sum_16_4  *MainFormSLS->hh[120];
c5.sum_70 += sum_16_5  *MainFormSLS->hh[30];
c5.sum_70 += sum_16_6  *MainFormSLS->hh[100];
c5.sum_70 += sum_16_7  *MainFormSLS->hh[10];
c5.sum_70 += sum_16_8  *MainFormSLS->hh[80];
c5.sum_70 += sum_16_9  *MainFormSLS->hh[150];
c5.sum_70 += sum_16_10 *MainFormSLS->hh[60];
c5.sum_70 += sum_16_11 *MainFormSLS->hh[130];
c5.sum_70 += sum_16_12 *MainFormSLS->hh[40];
c5.sum_70 += sum_16_13 *MainFormSLS->hh[110];
c5.sum_70 += sum_16_14 *MainFormSLS->hh[20];
c5.sum_70 += sum_16_15 *MainFormSLS->hh[90];
*/
}
//------------------------------------------------------------------------------
void __fastcall TSampleFreqImage::insert(TFreqComp& fc)
{
fcl.insert(TFreqCompList::value_type(fc.ampl,fc));
}
//------------------------------------------------------------------------------
void __fastcall TMediaQueueStruct::get_first_media_packet(vector<UBYTE>& v)
{
if(!q.empty())
  {
  v = q.front();
  q.pop();
  }
}
//------------------------------------------------------------------------------
#ifdef Log_Audio_Conference_Mixed_Packet
void __fastcall TWaveInputThread::Write_Audio_Conference_Mixed_Packet(const vector<int>& v_mix, int CH_ID, int SZ)
{
string s = "\n";
s += "To ch_id = " + inttostr(CH_ID) + "\n";
TEventLogThread* elt = *eltp;
if(elt)
  if(elt->getlog())
    {
    for(int i=0;i<SZ;i++)
       {
       if(i)
         s += " ";
       s += inttostr(v_mix[i]);
       }
    s += "\n";
    elt->FputEvt(s,1);
    }
}
//------------------------------------------------------------------------------
void __fastcall TAudioConfQueueStruct::Write_ch_id_from_which_packet_mixed(TMediaQueueStruct* mqs, int chID, const vector<UBYTE>& v)
{
TEventLogThread* elt = *ELTP;
if(elt)
  if(elt->getlog())
    {
    string s = "mix packet from ch_" + inttostr(mqs->get_chid()) + (string)" to ch_" + inttostr(chID) + " sz = " + inttostr(v.size()) + "\n";
    elt->FputEvt(s);
    }
}
#endif //#ifdef Log_Audio_Conference_Mixed_Packet
//------------------------------------------------------------------------------

