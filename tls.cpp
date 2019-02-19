//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "WinRDefs.h"
#include "tls.h"
#include "SipClient_Unit.h"

#pragma package(smart_init)
static unsigned tls_disconnect_count = 0;  //необходим , чтобы уменьшить размер log файла при отсутствии выхода в интернет - постоянный вызов tcp_disconnect_handler()
//---------------------------------------------------------------------------
void tls_connect_handler(void* ref) {
try{
tls_disconnect_count = 0;
if(MainFormSLS->ofs->elt)
  {
  TDateTime DateTime = DateTime.CurrentDateTime();
  string time_str;
  exsDateTime(DateTime,time_str);
  string s = "\n" + time_str + WS + "TLS connection" + WS + inttostr((int)ref) + WS + "established";
  if(MainFormSLS->Sip->sr_tls_t)
    s += WS + "to" + WS + MainFormSLS->Sip->sr_tls_t->host + ":" + inttostr(MainFormSLS->Sip->sr_tls_t->port);
  MainFormSLS->ofs->elt->FputEvt(s,1);
  }
MainFormSLS->Sip->collectLocalHostInterfaces(&MainFormSLS->iniData);
MainFormSLS->Stun.StunClientProc(&MainFormSLS->iniData,MainFormSLS->Sip,MainFormSLS->ofs->elt);
if(MainFormSLS->Sip->sr_tls_t)
 if(MainFormSLS->Sip->ss_tls_t)
   {
   MainFormSLS->Sip->ss_tls_t->r = MainFormSLS->Sip->sr_tls_t->r;
   if(MainFormSLS->Sip->ss_tls_t->Suspended)
      MainFormSLS->Sip->ss_tls_t->Resume_Thread();
   }
if(MainFormSLS->Sip->TLS_Dropped)
  {
  MainFormSLS->Sip->TLS_Dropped = false;
  MainFormSLS->Sip->initRegistrationProc();
  }
}//try
catch(Exception& e){exsSstEXCEPTION(MainFormSLS->ofs->elt,"__tls_connect_handler",e);}
}
//-----------------------------------------------------------------------------
void tls_disconnect_handler(void* ref)
{
try{
tls_disconnect_count++;
if(!MainFormSLS->Sip->TLS_Dropped)
  {
  if(MainFormSLS->lng == Lang_RU)
     MainFormSLS->Caption = "Потеряно соединение с сервером!";
  else
     MainFormSLS->Caption = "Connection Lost!";
  }
MainFormSLS->Sip->TLS_Dropped = true;
if(tls_disconnect_count < 3)    //Ограничение размера лог файла
 if(MainFormSLS->ofs->elt)
   {
   TDateTime DateTime = DateTime.CurrentDateTime();
   string time_str;
   exsDateTime(DateTime,time_str);
   string s = "\n" + time_str + WS + "TLS link" + WS + inttostr((int)ref) + WS + "disconnected. Try reconnect";
   if(MainFormSLS->Sip->sr_tls_t)
      s += WS + "to" + WS + MainFormSLS->Sip->sr_tls_t->host + ":" + inttostr(MainFormSLS->Sip->sr_tls_t->port);
   MainFormSLS->ofs->elt->FputEvt(s,1);
   }
  //Возможно необходимо добавить CRITICAL_SECTION как и в TCP connection
::Sleep(1000);
if(MainFormSLS->Sip->sr_tls_t)
  if(MainFormSLS->Sip->sr_tls_t->r==ref)
     MainFormSLS->Sip->sr_tls_t->r = so_start_client_tcp_ssl((char*)MainFormSLS->Sip->sr_tls_t->host.c_str(),MainFormSLS->Sip->sr_tls_t->port);
}//try
catch(Exception& e){exsSstEXCEPTION(MainFormSLS->ofs->elt,"__tls_disconnect_handler",e);}
}
//-----------------------------------------------------------------------------
static int pktn;
void tls_read_handler(const char* rcvbuf, size_t bread, void* ref)
{
try{
if(bread)
  {
  TOutPutUdpBlock* opb = new TOutPutUdpBlock(pktn);
  if(opb)
    {
    opb->s.resize(bread);
    memcpy(&opb->s[0],rcvbuf,bread);
    opb->datasize = bread; //for non string content
    opb->getDateTime();
    if((MainFormSLS->Sip->spt)&&(MainFormSLS->Sip->sr_tls_t))
      {
      opb->FromIP   = MainFormSLS->Sip->sr_tls_t->host;
      opb->FromPort = MainFormSLS->Sip->sr_tls_t->port;
      bool a = false;
      MainFormSLS->Sip->spt->setQueue(opb);
      MainFormSLS->Sip->sr_tls_t->updateSentQueue(opb, a);
      }
    else
      delete opb;
    }
  }
}//try
catch(Exception& e){exsSstEXCEPTION(MainFormSLS->ofs->elt,"__tls_read_handler",e);}
}
//-----------------------------------------------------------------------------
void __fastcall TSipRecvTlsThread::Execute()
{
try{
so_set_start_handler(&tls_connect_handler);
so_set_destr_handler(&tls_disconnect_handler);
so_set_read_handler(&tls_read_handler);
r=so_start_client_tcp_ssl((char*)host.c_str(),port);
so_run();
}//try
catch(Exception& e){exsSstEXCEPTION(*eltp,"__TSipRecvTlsThread::Execute",e);}
}
//----------------------------------------------------------------------------
void __fastcall TSipSendTlsThread::Execute()
{
try{
while(!Terminated)
     {
     if(!r)
       {
       TEventLogThread* elt = getLog();
       if(elt)
         {
         int sz = getQueueSize();
         elt->FputEvt("\nTSipSendTlsThread::Execute(): INACTIVE, in_queue size " + inttostr(sz));
         }
       Suspend_Thread();
       continue;
       }
     TEventLogThread* elt = getLog();
     if(elt)
       {
       int sz = getQueueSize();
       elt->FputEvt("\nTSipSendTlsThread::Execute(): ACTIVE, in_queue size " + inttostr(sz));
       }
     BaseExchangeBlock* bb = (BaseExchangeBlock*)getQueue();
     if(!bb)
       {
       Suspend_Thread();
       continue;
       }
     switch(bb->getBlockType()){
           case TOutputSipBuf_BLOCKTYPE:{
                TOutputSipBuf* ospb = (TOutputSipBuf*)bb;
                sendbuf(ospb);
                break;
                }
           case TOutPutUdpBlock_BLOCKTYPE:{
                TOutPutUdpBlock* opb = (TOutPutUdpBlock*)bb;
                sendbuf(opb);
                break;
                }
           case TSipParsBuf_BLOCKTYPE:{
                TSipParsBuf* spb = (TSipParsBuf*)bb;
                sendbuf(spb);
                break;
                }
           }
     if(bb->get_req_to_delete())
       {
       if(bb->getReferenceCount() < 3)
          exsDeleteSentBlock(bb);
       }
     else
       bb->decReferenceCount();
     }
}//try
catch(Exception& e){exsSstEXCEPTION(*eltp,"__TSipSendTlsThread::Execute",e);}
}
//----------------------------------------------------------------------------
void __fastcall TSipSendTlsThread::sendbuf(TOutputSipBuf* ospb)
{
int len = ospb->s.size();
if(len)
  {
  #ifdef SIP_LogSendPacket
  TDateTime DateTime = DateTime.CurrentDateTime();
  #endif
  so_write_some(r,&ospb->s[0],len);
  #ifdef SIP_LogSendPacket
  LOG_SendPacket(DateTime,ospb,len);
  #endif
  }
}
//----------------------------------------------------------------------------
void __fastcall TSipSendTlsThread::sendbuf(TOutPutUdpBlock* opb)
{
int len = opb->s.size();
if(len)
  {
  #ifdef SIP_LogSendPacket
  TDateTime DateTime = DateTime.CurrentDateTime();
  #endif
  so_write_some(r,&opb->s[0],len);
  #ifdef SIP_LogSendPacket
  LOG_SendPacket(DateTime,opb,len);
  #endif
  }
}
//----------------------------------------------------------------------------
void __fastcall TSipSendTlsThread::sendbuf(TSipParsBuf* spb)
{
int len = spb->s.size();
if(len)
  {
  #ifdef SIP_LogSendPacket
  TDateTime DateTime = DateTime.CurrentDateTime();
  #endif
  so_write_some(r,&spb->s[0],len);
  #ifdef SIP_LogSendPacket
  LOG_SendPacket(DateTime,spb,len);
  #endif
  }
}
//----------------------------------------------------------------------------
#ifdef SIP_LogSendPacket
void __fastcall TSipSendTlsThread::LOG_SendPacket(TDateTime& DateTime,TOutPutUdpBlock* opb,int len)
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
void __fastcall TSipSendTlsThread::LOG_SendPacket(TDateTime& DateTime,TOutPutDtmfBlock* opd,int len)
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
void __fastcall TSipSendTlsThread::LOG_SendPacket(TDateTime& DateTime,TOutputSipBuf* ospb,int len)
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
void __fastcall TSipSendTlsThread::LOG_SendPacket(TDateTime& DateTime,TSipParsBuf* spb,int len)
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


