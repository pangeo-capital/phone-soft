//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "SipSendThread.h"
#include "utils.h"

#pragma package(smart_init)
//---------------------------------------------------------------------------
void __fastcall TSipSendThread::Execute()
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
       bb->decReferenceCount();   //decReferenceCount() must be last operation in block
     }
 }//try
catch(Exception& e){exsSstEXCEPTION(*eltp,"__TSipSendThread::Execute",e);}
}
//---------------------------------------------------------------------------
__fastcall TSipSendThread::~TSipSendThread()
{
#ifdef SIP_Thread_Destruction_Log
TEventLogThread* elt = getLog();
if(elt)elt->FputEvt("\n~TSipSendThread()");
#endif
}
//---------------------------------------------------------------------------
void __fastcall TSipSendThread::LOG_SendPacket(TDateTime& DateTime,TOutPutUdpBlock* opb,int len)
{
TEventLogThread* elt = getLog();
if(elt)
  {
  string str;
  exsTime(DateTime,str);
  str = "\n" + str + " sck " + inttostr(sck);
  str += " Pckt SendTo " + opb->ToIP + ":" + inttostr(opb->ToPort) + " Len " + inttostr(len) + "\n";
 // for(int i=0;i<len;i++)
 //   str += " " + inttohexstr(opb->v[i],2);
 // str+="\n";
  elt->FputEvt(str + opb->s);
  }
}
//----------------------------------------------------------------------------
void __fastcall TSipSendThread::LOG_SendPacket(TDateTime& DateTime,TOutputSipBuf* ospb,int len)
{
TEventLogThread* elt = getLog();
if(elt)
  {
  string str;
  exsTime(DateTime,str);
  str = "\n" + str + " sck " + inttostr(sck);
  str += " Pckt SendTo " + ospb->ToIP + ":" + inttostr(ospb->ToPort) + " Len " + inttostr(len) + "\n";
  elt->FputEvt(str + ospb->s);
  }
}
//----------------------------------------------------------------------------
void __fastcall TSipSendThread::LOG_SendPacket(TDateTime& DateTime,TSipParsBuf* spb,int len)
{
TEventLogThread* elt = getLog();
if(elt)
  {
  string str;
  exsTime(DateTime,str);
  str = "\n" + str + " sck " + inttostr(sck);
  str += " Pckt SendTo " + spb->ToIP + ":" + inttostr(spb->ToPort) + " Len " + inttostr(len) + "\n";
  elt->FputEvt(str + spb->s);
  }
}
//----------------------------------------------------------------------------
void __fastcall TSipSendThread::Error(const string& s)
{
int err = WSAGetLastError();
lasterr = "TSipSendThread::Execute() " + s;
GetLastSocketError(lasterr,err);
sendlasterr();
}
//----------------------------------------------------------------------------
void __fastcall TSipSendThread::sendbuf(TOutputSipBuf* ospb)
{
int len = ospb->s.size();
if(len)
  {
  struct sockaddr_in dest;
  memset(&dest,0,sizeof(dest));
  dest.sin_family = AF_INET;
  dest.sin_addr.s_addr = inet_addr(ospb->ToIP.c_str());
  dest.sin_port = htons(ospb->ToPort);
  TDateTime DateTime = DateTime.CurrentDateTime();
  if(sendto(sck,&ospb->s[0],len,0,(struct sockaddr*)&dest,sizeof(dest))==SOCKET_ERROR)
    Error("TOutputSipBuf");
  else
    {
    #ifdef SIP_LogSendPacket
    LOG_SendPacket(DateTime,ospb,len);
    #endif
    }
  }
}
//----------------------------------------------------------------------------
void __fastcall TSipSendThread::sendbuf(TOutPutUdpBlock* opb)
{
int len = opb->s.size();
if(len)
  {
  struct sockaddr_in dest;
  memset(&dest,0,sizeof(dest));
  dest.sin_family = AF_INET;
  dest.sin_addr.s_addr = inet_addr(opb->ToIP.c_str());
  dest.sin_port = htons(opb->ToPort);
  TDateTime DateTime = DateTime.CurrentDateTime();
  if(sendto(sck,&opb->s[0],len,0,(struct sockaddr*)&dest,sizeof(dest))==SOCKET_ERROR)
    Error("TOutPutUdpBlock");
  else
    {
    #ifdef SIP_LogSendPacket
    LOG_SendPacket(DateTime,opb,len);
    #endif
    }
  }
}
//----------------------------------------------------------------------------
void __fastcall TSipSendThread::sendbuf(TSipParsBuf* spb)
{
int len = spb->s.size();
if(len)
  {
  struct sockaddr_in dest;
  memset(&dest,0,sizeof(dest));
  dest.sin_family = AF_INET;
  dest.sin_addr.s_addr = inet_addr(spb->ToIP.c_str());
  dest.sin_port = htons(spb->ToPort);
  TDateTime DateTime = DateTime.CurrentDateTime();
  if(sendto(sck,&spb->s[0],len,0,(struct sockaddr*)&dest,sizeof(dest))==SOCKET_ERROR)
    Error("TSipParsBuf");
  else
    {
    #ifdef SIP_LogSendPacket
    LOG_SendPacket(DateTime,spb,len);
    #endif
    }
  }
}
//----------------------------------------------------------------------------













