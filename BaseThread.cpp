//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "BaseThread.h"
#include "utils.h"

#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall TBaseThread::~TBaseThread()
{
#ifdef SIP_Thread_Destruction_Log
TEventLogThread* elt = getLog();
if(elt)elt->FputEvt("\n~TBaseThread()");
#endif
__clearBaseQueue();
checkSent();
::DeleteCriticalSection(&sc);
::DeleteCriticalSection(&in_queue);
::DeleteCriticalSection(&base_sent_cs);
::DeleteCriticalSection(&exchlst_cs);
}
//-----------------------------------------------------------------------------
void __fastcall TBaseThread::Suspend_Thread()
{
::EnterCriticalSection(&sc);
  suspend_count++;
::LeaveCriticalSection(&sc);
Suspend();
}
//-----------------------------------------------------------------------------
void __fastcall TBaseThread::Resume_Thread()
{
::EnterCriticalSection(&sc);
  if(suspend_count < 1)   //Important for critical Resume in the Timer1Timer()
    {
    suspend_count = 0;
    Resume();
    }
  else
    {
    while(suspend_count)
         {
         suspend_count--;
         Resume();
         }
    }
::LeaveCriticalSection(&sc);
}
//-----------------------------------------------------------------------------
void __fastcall TBaseThread::setQueue_not_suspended(void* opb)
{
::EnterCriticalSection(&in_queue);
  ((BaseExchangeBlock*)opb)->incReferenceCount();
  base_q.push_back(opb);
::LeaveCriticalSection(&in_queue);
}
//-----------------------------------------------------------------------------
void __fastcall TBaseThread::setQueue(void* opb)
{
::EnterCriticalSection(&in_queue);
  ((BaseExchangeBlock*)opb)->incReferenceCount();
  base_q.push_back(opb);
 //if(Suspended)
     Resume_Thread();
::LeaveCriticalSection(&in_queue);
}
//---------------------------------------------------------------------------
void* __fastcall TBaseThread::getQueue()
{
void* opb=NULL;
::EnterCriticalSection(&in_queue);
if(!base_q.empty())
  {
  opb = base_q.front();
  base_q.pop_front();
  }
::LeaveCriticalSection(&in_queue);
return opb;
}
//---------------------------------------------------------------------------
int  __fastcall TBaseThread::getQueueSize()
{
int rv=0;
::EnterCriticalSection(&in_queue);
  rv = base_q.size();
::LeaveCriticalSection(&in_queue);
return rv;
}
//---------------------------------------------------------------------------
bool  __fastcall TBaseThread::QueueEmpty()
{
bool rv=false;
::EnterCriticalSection(&in_queue);
  if(base_q.empty())
    rv = true;
::LeaveCriticalSection(&in_queue);
return rv;
}
//---------------------------------------------------------------------------
void __fastcall  TBaseThread::__clearBaseQueue()
{
::EnterCriticalSection(&in_queue);
  while(!base_q.empty())
     {
     BaseExchangeBlock* bb = (BaseExchangeBlock*)base_q.front();
     base_q.pop_front();
     if(bb->get_req_to_delete())
       {
       if(bb->getReferenceCount() < 3)
         {
         exsDeleteSentBlock(bb);
         continue;
         }
       }
     if(bb->getBlockType() == TWaveOutPutBuf_BLOCKTYPE)
        exsDeleteSentBlock(bb);
     else
       bb->decReferenceCount();
     }
::LeaveCriticalSection(&in_queue);
}
//---------------------------------------------------------------------------
TEventLogThread* __fastcall TBaseThread::getLog()
{
TEventLogThread* elt = *eltp;
if(elt)
 if(elt->getlog())
    return elt;
return NULL;
}
//---------------------------------------------------------------------------
void __fastcall TBaseThread::sendlasterr()
{
TEventLogThread* elt = getLog();
if(elt)elt->FputEvt(lasterr,1);
}
//---------------------------------------------------------------------------
int __fastcall TBaseThread::getSentSize()
{
int rv;
::EnterCriticalSection(&base_sent_cs);
  rv = base_sent.size();
::LeaveCriticalSection(&base_sent_cs);
return rv;
}
//---------------------------------------------------------------------------
/*
void __fastcall TBaseThread::unknownBlockType()
{
lasterr = "\nError: try to delete block with unknown BLOCKTYPE ";
sendlasterr();
}
*/
//---------------------------------------------------------------------------
void __fastcall TBaseThread::getSent()
{
try{
::EnterCriticalSection(&base_sent_cs);
  while(!base_sent.empty())
       {
       BaseExchangeBlock* opb = (BaseExchangeBlock*)base_sent.front();
       if(opb->getReferenceCount() < 1)
         {
         base_sent.pop_front();
         exsDeleteSentBlock(opb);
         }
       else
         break;
       }
::LeaveCriticalSection(&base_sent_cs);
}//try
catch(Exception& e){exsSstEXCEPTION(*eltp,"__TBaseThread::getSent()",e);}
}
//------------------------------------------------------------------------------
void __fastcall TBaseThread::checkSent()
{
try{
::EnterCriticalSection(&base_sent_cs);
  if(!base_sent.empty())
    {
    deque<void*>::iterator it = base_sent.begin();
    while(it != base_sent.end())
         {
         BaseExchangeBlock* opb = (BaseExchangeBlock*)(*it);
         if(opb->getReferenceCount() < 1)
           {
           base_sent.erase(it);
           exsDeleteSentBlock(opb);
           }
         else
           break;
         it = base_sent.begin();
         }
    }
::LeaveCriticalSection(&base_sent_cs);
}//try
catch(Exception& e){exsSstEXCEPTION(*eltp,"__TBaseThread::checkSent()",e);}
}
//------------------------------------------------------------------------------
void __fastcall TBaseThread::updateSentQueue(BaseExchangeBlock* opb, bool& in_sent_queue)
{
try{
if(opb)
  {
  ::EnterCriticalSection(&base_sent_cs);
    base_sent.push_back(opb);
  ::LeaveCriticalSection(&base_sent_cs);
  }
if((++checkCount & 0xFF) == 0xFF)
     checkSent();
   else
     getSent();
in_sent_queue = true;
}//try
catch(Exception& e){exsSstEXCEPTION(*eltp,"__TBaseThread::updateSentQueue()",e);}
}
//------------------------------------------------------------------------------
void __fastcall TBaseThread::insertExchLst(TExchBuf* buf)
{
::EnterCriticalSection(&exchlst_cs);
  exchlst.push(buf);
::LeaveCriticalSection(&exchlst_cs);
}
//-----------------------------------------------------------------------------
TExchBuf* __fastcall TBaseThread::getExchLst()
{
TExchBuf* rv = NULL;
::EnterCriticalSection(&exchlst_cs);
  if(!exchlst.empty())
    {
    rv = exchlst.front();
    exchlst.pop();
    }
::LeaveCriticalSection(&exchlst_cs);
return rv;
}
//-----------------------------------------------------------------------------
void __fastcall TBaseThread::clearExchLst()
{
::EnterCriticalSection(&exchlst_cs);
  while(!exchlst.empty())
       {
       TExchBuf* buf = exchlst.front();
       if(buf)delete buf;
       exchlst.pop();
       }
 ::LeaveCriticalSection(&exchlst_cs);
}
//-----------------------------------------------------------------------------
string  __fastcall TBaseThread::get_tag(const string& s)
{
string rv;
int len = s.length();
int st  = s.rfind(";tag=");
if(st != -1)
  {
  st += 5;
  if(st < len)
    {
    int en = s.find(crlf,st);
    if(st < en)
       rv = s.substr(st,en-st); 
    }
  }
return rv;
}
//------------------------------------------------------------------------------

