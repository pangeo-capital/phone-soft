//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "WinRDefs.h"

#ifdef SIP_Video
#include "Video.h"
#include "utils.h"
#include "udp.h"
#include "unit4.h"
#include "unit3.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

void __fastcall TVideoInputThread::Execute()
{
try{

}//try
catch(Exception& e){exsSstEXCEPTION(*eltp,"__TVideoInputThread::Execute",e);}
}
//---------------------------------------------------------------------------
void __fastcall TVideoOutputThread::Execute()
{
try{
while(!Terminated)
     {
     TOutPutUdpBlock* opb = (TOutPutUdpBlock*)getQueue();
     if(!opb)
       {
       Suspend_Thread();
       continue;
       }
     proc_Video_TOutPutUdpBlock(opb);
     opb->decReferenceCount();
     }
}//try
catch(Exception& e){exsSstEXCEPTION(*eltp,"__TVideoOutputThread::Execute",e);}
}
//---------------------------------------------------------------------------
void __fastcall TVideoOutputThread::proc_Video_TOutPutUdpBlock(TOutPutUdpBlock* opb)
{
int sz = opb->v.size();
if(sz > 12)
  {
  UINT payload_type = opb->v[1] & 0x7F;
  UINT marker       = opb->v[1] & 0x80;
  if(marker)
    if(video_sending_only)
      if(!Form3->Visible) //Если экран с удаленным видео неактивен
        {
        video_sending_only = false;
        TExchBuf* buf = new TExchBuf(WM_APP_MSG_WPARAM__NDEF);
        if(buf)
          {
          buf->emt    = ExchMsgType_Show_Remote_Video;
          buf->callid = Uc->getInOutCallID();
          buf->a1     = 1;     //Get MediaSession and tag by In_Out_CallID for following correct disconnet
          if(Form4->Visible)
             buf->b1 = true;    //Show LocalVideo Panel on RemoteVideoScreen
          Form3->ins_exch_buf(buf);
          ::PostMessage(Form3->Handle, REMOTE_VIDEO_MSG, WM_FORM3_MSG_WPARAM__NDEF, WM_FORM3_MSG_LPARAM__NDEF);
          }
        }
  switch(payload_type){
        case 34:{  //H.263
             proc_Video_H263_Packet(opb,sz);
             break;
             }
        case 115:{  //H.263+
             proc_Video_H263_Plus_Packet(opb,sz);
             break;
             }
        }
  }
}
//---------------------------------------------------------------------------
void __fastcall TVideoOutputThread::proc_Video_H263_Packet(TOutPutUdpBlock* opb,int sz)
{
if(sz > 12)
  {
  if(!(opb->v[12] & 0x80))   // RFC2190 bit F  of H263header
    proc_Video_H263_A_Mode(opb,sz);
  else
    proc_Video_H263_B_C_Mode(opb,sz);
  }
}
//---------------------------------------------------------------------------
void __fastcall TVideoOutputThread::proc_Video_H263_Plus_Packet(TOutPutUdpBlock* opb,int sz)
{
if(sz > 12)
  {
  if(!(opb->v[12] & 0x80))   // RFC2190 bit F  of H263header
    proc_Video_H263_Plus_A_Mode(opb,sz);
  else
    proc_Video_H263_Plus_B_C_Mode(opb,sz);
  }
}
//---------------------------------------------------------------------------
void __fastcall TVideoOutputThread::getPictureSize(int resolution,int& width,int& height)
{
switch(resolution){
      case 1: //subQCIF
             width=128;height=96;   break;
      case 2://QCIF
             width=176;height=144;  break;
      case 3://CIF
             width=352;height=288;  break;
      case 4://4CIF
             width=704;height=576;  break;
      case 5://16CIF
             width=1408;height=1152;break;
      case 6://reservrd
             break;
      case 7://extended PTYPE
             break;
      }
}
//---------------------------------------------------------------------------
void __fastcall TVideoOutputThread::proc_Video_H263_Plus_A_Mode(TOutPutUdpBlock* opb,int sz)
{
if(decoderId < 1)return;
if(yuv420_rgb24_scalerId < 1)return;
int sz_plus_h263_A_header = 12;// + H263_HEADER_MODE_A_SIZE;
if(sz > sz_plus_h263_A_header)
  {
  int resolution = 3;//(opb->v[13] & 0xE0) >> 5;
  int yuv420_width=0; int yuv420_height=0;
  getPictureSize(resolution,yuv420_width,yuv420_height);
  int h263_sz = sz - sz_plus_h263_A_header;
  if(h263_sz > 0)
    {
    vector<UBYTE> v(h263_sz);
    memcpy(&v[0],&opb->v[12],h263_sz);
    if(yuv420_width)
      if(yuv420_height)
        {
        int odata_yuv420_len = vencdec_get_yuv420p_buff_size(yuv420_width,yuv420_height);
        if(odata_yuv420_len > 0)
          {
          vector<UBYTE> odata_yuv420(odata_yuv420_len);
          int result = vencdec_decode( decoderId, &v[0], h263_sz, &odata_yuv420[0], odata_yuv420.size(), &yuv420_width, &yuv420_height );
          if(result > 0)
            {
            if(Form3->Visible)
              {
              int rgb24_size = vencdec_get_bgr24_buff_size( yuv420_width, yuv420_height );
              if(rgb24_size > 0)  // !=-1,!=0
                {
                vector<UBYTE> odata_rgb24(rgb24_size);
                result = vencdec_yuv420p_to_bgr24( yuv420_rgb24_scalerId, yuv420_width, yuv420_height, &odata_yuv420[0], odata_yuv420.size(),
                                                         yuv420_width, yuv420_height, &odata_rgb24[0], rgb24_size );
                if((result > 0)&&(result < 10000000))
                  {
                  /*
                  int queue_size = Form3->getSize();
                  lasterr = "\nForm3 queue " + inttostr(queue_size);
                  sendlasterr();
                  */
                  
                  opb->remote_yuv420_width  = yuv420_width;
                  opb->remote_yuv420_height = yuv420_height;
                  opb->v = odata_rgb24;
                  Form3->push_block(opb);
                  }
                }
              }
            }
           }
        }
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TVideoOutputThread::proc_Video_H263_Plus_B_C_Mode(TOutPutUdpBlock* opb,int sz)
{
}
//---------------------------------------------------------------------------
void __fastcall TVideoOutputThread::proc_Video_H263_B_C_Mode(TOutPutUdpBlock* opb,int sz)
{
}
//---------------------------------------------------------------------------
void __fastcall TVideoOutputThread::proc_Video_H263_A_Mode(TOutPutUdpBlock* opb,int sz)
{
if(decoderId < 1)return;
if(yuv420_rgb24_scalerId < 1)return;
int sz_plus_h263_A_header = 12 + H263_HEADER_MODE_A_SIZE;
if(sz > sz_plus_h263_A_header)
  {
  int resolution = (opb->v[13] & 0xE0) >> 5;
  int yuv420_width=0; int yuv420_height=0;
  getPictureSize(resolution,yuv420_width,yuv420_height);
  int h263_sz = sz - sz_plus_h263_A_header;
  if(h263_sz > 0)
    {
    vector<UBYTE> v(h263_sz);
    memcpy(&v[0],&opb->v[sz_plus_h263_A_header],h263_sz);
    if(yuv420_width)
      if(yuv420_height)
        {
        int odata_yuv420_len = vencdec_get_yuv420p_buff_size(yuv420_width,yuv420_height);
        if(odata_yuv420_len > 0)
          {
          vector<UBYTE> odata_yuv420(odata_yuv420_len);
          int result = vencdec_decode( decoderId, &v[0], h263_sz, &odata_yuv420[0], odata_yuv420.size(), &yuv420_width, &yuv420_height );
          if(result > 0)
            {
            if(Form3->Visible)
              {
              int rgb24_size = vencdec_get_bgr24_buff_size( yuv420_width, yuv420_height );
              if(rgb24_size > 0)  // !=-1,!=0
                {
                vector<UBYTE> odata_rgb24(rgb24_size);
                result = vencdec_yuv420p_to_bgr24( yuv420_rgb24_scalerId, yuv420_width, yuv420_height, &odata_yuv420[0], odata_yuv420.size(),
                                                         yuv420_width, yuv420_height, &odata_rgb24[0], rgb24_size );
                if((result > 0)&&(result < 10000000))
                  {
                  opb->remote_yuv420_width  = yuv420_width;
                  opb->remote_yuv420_height = yuv420_height;
                  opb->v = odata_rgb24;
                  Form3->push_block(opb);
                  }
                }
              }
            }
           }
        }
    }
  }
}
//---------------------------------------------------------------------------
#endif
