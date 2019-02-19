//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "WinRDefs.h"
#include "SipClient_Unit.h"
#include "tunnel.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
void tunnel_connect_handler(void* ref) {
try{
TSipRecvTunnelThread* sr_tunnelt = MainFormSLS->Sip->getTSipRecvTunnelThread();
TSipSendTunnelThread* ss_tunnelt = MainFormSLS->Sip->getTSipSendTunnelThread();
if(MainFormSLS->ofs->elt)
  {
  TDateTime DateTime = DateTime.CurrentDateTime();
  string time_str;
  exsDateTime(DateTime,time_str);
  string s = "\n" + time_str + WS + "Tunnel connection" + WS + inttostr((int)ref) + WS + "established";
  if(sr_tunnelt)
    s += WS + "to" + WS + sr_tunnelt->host + ":" + inttostr(sr_tunnelt->port);
  MainFormSLS->ofs->elt->FputEvt(s,1);
  }
MainFormSLS->Sip->collectLocalHostInterfaces(&MainFormSLS->iniData);
MainFormSLS->Stun.StunClientProc(&MainFormSLS->iniData,MainFormSLS->Sip,MainFormSLS->ofs->elt);
if(sr_tunnelt)
 if(ss_tunnelt)
   {
   ss_tunnelt->r = ref;
   if(ss_tunnelt->Suspended)
      ss_tunnelt->Resume_Thread();
   }
}//try
catch(Exception& e){exsSstEXCEPTION(MainFormSLS->ofs->elt,"__tunnel_connect_handler",e);}
}
//---------------------------------------------------------------------------
void tunnel_disconnect_handler(void* ref)
{
try{
TSipRecvTunnelThread* sr_tunnelt = MainFormSLS->Sip->getTSipRecvTunnelThread();
if(MainFormSLS->ofs->elt)
  {
  TDateTime DateTime = DateTime.CurrentDateTime();
  string time_str;
  exsDateTime(DateTime,time_str);
  string s = "\n" + time_str + WS + "Tunnel link" + WS + inttostr((int)ref) + WS + "disconnected. Try reconnect";
  if(sr_tunnelt)
     s += WS + "to" + WS + sr_tunnelt->host + ":" + inttostr(sr_tunnelt->port);
  MainFormSLS->ofs->elt->FputEvt(s,1);
  }
if(MainFormSLS->Sip->getTSipRecvTunnelThread())
  ::Sleep(2000);
else
  {
  while(!MainFormSLS->Sip->getTSipRecvTunnelThread())
       {
       if(MainFormSLS->Sip->get_destroy_req())
          return;
       ::Sleep(2000);
       }
  }
if(MainFormSLS->Sip->get_destroy_req())
    return;
sr_tunnelt = MainFormSLS->Sip->getTSipRecvTunnelThread();
if(sr_tunnelt)
  if(sr_tunnelt->r==ref)
    sr_tunnelt->r = so_start_tunnel_tcp((char*)sr_tunnelt->host.c_str(),sr_tunnelt->port);
}//try
catch(Exception& e){exsSstEXCEPTION(MainFormSLS->ofs->elt,"__tunnel_disconnect_handler",e);}
}
//---------------------------------------------------------------------------
static int pktn;
void tunnel_read_handler(const char* rcvbuf, size_t bread,unsigned int data_type, void* client_, char* name_,  unsigned char name_sz)
{
try{
bool a = false;
TSipRecvTunnelThread* sr_tunnelt = MainFormSLS->Sip->getTSipRecvTunnelThread();
if(sr_tunnelt)
  if(sr_tunnelt->get_thread_block())
     return;
if(bread)
  {
    switch(data_type){
           case DT_SIP:
                /*
                if(MainFormSLS->ofs->elt)
                  {
                  TDateTime DateTime = DateTime.CurrentDateTime();
                  string time_str;
                  exsDateTime(DateTime,time_str);
                  string s = "\n" + time_str + WS + "DT_SIP" + WS + inttostr((int)client_) + "\n";
                  s += opb->s;
                  MainFormSLS->ofs->elt->FputEvt(s,1);
                  } */
                if((MainFormSLS->Sip->spt)&&(sr_tunnelt))
                  {
                  TOutPutUdpBlock* opb = new TOutPutUdpBlock(pktn);
                  if(opb)
                    {
                    opb->getDateTime();
                    opb->s.resize(bread);
                    memcpy(&opb->s[0],rcvbuf,bread);
                    opb->datasize = bread;
                    opb->FromIP   = sr_tunnelt->host;
                    opb->FromPort = sr_tunnelt->port;
                    MainFormSLS->Sip->spt->setQueue(opb);
                    sr_tunnelt->updateSentQueue(opb, a);
                    }
                  }
                break;
           case DT_RTP:{
                TOutPutUdpBlock* opb = new TOutPutUdpBlock(pktn);
                if(opb)
                  {
                  bool set_queue = false;
                  opb->getDateTime();
                  string name = string(name_);
                  name.resize(name_sz);

              /*  if(MainFormSLS->ofs->elt)
                  {
                  TDateTime DateTime = DateTime.CurrentDateTime();
                  string time_str;
                  exsDateTime(DateTime,time_str);
                  string s = "\n" + time_str + WS + "DT_RTP" + WS + name + WS + inttostr(bread) +  "\n";
                  MainFormSLS->ofs->elt->FputEvt(s,1);
                  } */

                  opb->v.resize(bread);
                  memcpy(&opb->v[0],rcvbuf,bread);
                  opb->datasize = bread;
                  if(!name.empty())
                    {
                    const char* buf = name.c_str();
                    if(buf[0] == 'a')
                      {
                      TUdpChannel* uc  = MainFormSLS->Sip->ucs->get_First_RtpAudioChannel();
                      if(uc)
                       if(uc->chDispThread)
                         {
                         set_queue = true;
                         uc->chDispThread->pushToSend(opb);
                         }
                      }
                    #ifdef SIP_Video
                    else if(buf[0] == 'v')
                      {
                      TUdpChannel* uc  = MainFormSLS->Sip->ucs->get_First_RtpVideoChannel();
                      if(uc)
                       if(uc->chDispThread)
                         {
                         set_queue = true;
                         uc->chDispThread->pushToSend(opb);
                         }
                      }
                    #endif
                    }
                  if(!set_queue)
                    {
                    if(MainFormSLS->ofs->elt)
                      {
                      TDateTime DateTime = DateTime.CurrentDateTime();
                      string time_str;
                      exsDateTime(DateTime,time_str);
                      string s = "\n" + time_str + WS + "DT_RTP" + WS + "UNKNOWN_TYPE";
                      if(!name.empty())
                         s += WS + "name" + WS + name;
                      else
                         s += WS + "empty name";
                      s += WS + "bread" + WS + inttostr(bread);
                      s += "\n";
                      MainFormSLS->ofs->elt->FputEvt(s);
                      }
                    delete opb;
                    }
                  }
                break;
                }
           }
  }//if(bread)
}//try
catch(Exception& e){exsSstEXCEPTION(MainFormSLS->ofs->elt,"__tunnel_read_handler",e);}
}
//---------------------------------------------------------------------------
void __fastcall TSipRecvTunnelThread::Execute()
{
try{
if(MainFormSLS->Sip->get_destroy_req())
   return;
so_set_tunnel_start_handler(tunnel_connect_handler);    //(&tunnel_connect_handler);
so_set_tunnel_destr_handler(&tunnel_disconnect_handler);//(&tunnel_disconnect_handler);
so_set_tunnel_read_handler(&tunnel_read_handler);       //(&tunnel_read_handler);
r = so_start_tunnel_tcp((char*)host.c_str(),port);
so_run();
}//try
catch(Exception& e){exsSstEXCEPTION(MainFormSLS->ofs->elt,"__TSipRecvTunnelThread",e);}
}
//---------------------------------------------------------------------------
void __fastcall TSipSendTunnelThread::Execute()
{
try{
while(!Terminated)
     {
     BaseExchangeBlock* bb = (BaseExchangeBlock*)getQueue();
     if(!bb)
       {
       Suspend_Thread();
       continue;
       }
     if(get_thread_block())
       {
       bb->decReferenceCount();
       continue;
       }
     if(!r)
       {
       bb->decReferenceCount();
       Suspend_Thread();
       continue;
       }
     switch(bb->getBlockType()){
           case TOutputSipBuf_BLOCKTYPE:{
                TOutputSipBuf* ospb = (TOutputSipBuf*)bb;
                sendbuf(ospb,DT_SIP);
                break;
                }
           case TOutPutUdpBlock_BLOCKTYPE:{
                TOutPutUdpBlock* opb = (TOutPutUdpBlock*)bb;
                sendbuf(opb,DT_RTP,opb->tunnel_name);
                break;
                }
           case TOutPutDtmf_BLOCKTYPE:{
                TOutPutDtmfBlock* opd = (TOutPutDtmfBlock*)bb;
                for(int i=0;i<opd->dtmf_transmission_count;i++)
                    sendbuf(opd,DT_RTP,opd->tunnel_name);
                break;
                }
           case TSipParsBuf_BLOCKTYPE:{
                TSipParsBuf* spb = (TSipParsBuf*)bb;
                sendbuf(spb,DT_SIP);
                break;
                }
           }
     bb->decReferenceCount();
     }
}//try
catch(Exception& e){exsSstEXCEPTION(MainFormSLS->ofs->elt,"__TSipSendTunnelThreadd",e);}
}
//---------------------------------------------------------------------------
void __fastcall TSipSendTunnelThread::sendbuf(TOutputSipBuf* ospb, unsigned data_type)
{
int len = ospb->s.size();
if(len)
  {
  #ifdef SIP_LogSendPacket
  TDateTime DateTime = DateTime.CurrentDateTime();
  #endif
  const char* data = ospb->s.c_str();
  so_tunnel_write_some(r,data,len,data_type,NULL,0);
  #ifdef SIP_LogSendPacket
  LOG_SendPacket(DateTime,ospb,len);
  #endif
  }
}
//----------------------------------------------------------------------------
void __fastcall TSipSendTunnelThread::sendbuf(TOutPutUdpBlock* opb, unsigned data_type, const string& name)
{
int len = opb->v.size();
if(len)
  {
  #ifdef RTP_Tunnel_LogSendBufPacket
  TDateTime DateTime = DateTime.CurrentDateTime();
  #endif
  unsigned name_sz  = name.size();
  const char* name_ = name.c_str();
  so_tunnel_write_some(r,&opb->v[0],len,data_type,name_,name_sz);
  #ifdef RTP_Tunnel_LogSendBufPacket
  LOG_SendPacket(DateTime,opb,len);
  #endif
  }
}
//----------------------------------------------------------------------------
void __fastcall TSipSendTunnelThread::sendbuf(TOutPutDtmfBlock* opd, unsigned data_type, const string& name)
{
int len = opd->v.size();
if(len)
  {
  #ifdef RTP_Tunnel_2833_LogSendBufPacket
  TDateTime DateTime = DateTime.CurrentDateTime();
  #endif
  unsigned name_sz  = name.size();
  const char* name_ = name.c_str();
  so_tunnel_write_some(r,&opd->v[0],len,data_type,name_,name_sz);
  #ifdef RTP_Tunnel_2833_LogSendBufPacket
  LOG_SendPacket(DateTime,opd,len);
  #endif
  }
}
//-----------------------------------------------------------------------------
void __fastcall TSipSendTunnelThread::sendbuf(TSipParsBuf* spb, unsigned data_type)
{
int len = spb->s.size();
if(len)
  {
  #ifdef SIP_LogSendPacket
  TDateTime DateTime = DateTime.CurrentDateTime();
  #endif
  const char* data  = spb->s.c_str();
  so_tunnel_write_some(r,data,len,data_type,NULL,0);
  #ifdef SIP_LogSendPacket
  LOG_SendPacket(DateTime,spb,len);
  #endif
  }
}
//----------------------------------------------------------------------------
#ifdef SIP_LogSendPacket
void __fastcall TSipSendTunnelThread::LOG_SendPacket(TDateTime& DateTime,TOutPutUdpBlock* opb,int len)
{
TEventLogThread* elt = getLog();
if(elt)
  {
  string str;
  exsTime(DateTime,str);
  str = "\n" + str + " Pckt Sent Len " + inttostr(len) + "\n";
 // for(int i=0;i<len;i++)
 //   str += " " + inttohexstr(opb->v[i],2);
 // str+="\n";
  elt->FputEvt(str + opb->s);
  }
}
//----------------------------------------------------------------------------
void __fastcall TSipSendTunnelThread::LOG_SendPacket(TDateTime& DateTime,TOutPutDtmfBlock* opd,int len)
{
TEventLogThread* elt = getLog();
if(elt)
  {
  string str;
  exsTime(DateTime,str);
  str = "\n" + str + " Pckt Sent Len " + inttostr(len) + "\n";
  for(int i=0;i<len;i++)
     str += " " + inttohexstr(opd->v[i],2);
  str+="\n";
  elt->FputEvt(str,1);
  }
}
//----------------------------------------------------------------------------
void __fastcall TSipSendTunnelThread::LOG_SendPacket(TDateTime& DateTime,TOutputSipBuf* ospb,int len)
{
TEventLogThread* elt = getLog();
if(elt)
  {
  string str;
  exsTime(DateTime,str);
  str = "\n" + str + " Pckt Sent Len " + inttostr(len) + "\n";
  elt->FputEvt(str + ospb->s);
  }
}
//----------------------------------------------------------------------------
void __fastcall TSipSendTunnelThread::LOG_SendPacket(TDateTime& DateTime,TSipParsBuf* spb,int len)
{
TEventLogThread* elt = getLog();
if(elt)
  {
  string str;
  exsTime(DateTime,str);
  str = "\n" + str + " Pckt Sent Len " + inttostr(len) + "\n";
  elt->FputEvt(str + spb->s);
  }
}
#endif
//----------------------------------------------------------------------------

