//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "SipResendThread.h"
#include "SipParsThread.h"
#include "utils.h"
#include "Sip.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
void __fastcall TSipResendThread::Execute()
{
try{
   while(!Terminated)
        {
        TResendReqData rrd;
        switch(procResendBlock(rrd)){
               case 0:
                      #ifdef SIP_ResendQueue_Log
                     // logResendListSize("TSipResendThread::Execute() case 0:");
                      #endif
                      Sleep(1);
                      continue;
               case 1:
                      #ifdef SIP_ResendQueue_Log
                     // logResendListSize("TSipResendThread::Execute() case 1:");
                      #endif
                      Sleep(1);
                      continue;
               case 2:
                      #ifdef SIP_ResendQueue_Log
                      logResendListSize("TSipResendThread::Execute() case 2:");
                      #endif
                      switch(uatt){
                            case SipUAThreadType_UAC:
                                 if(Sip->uac)
                                    Sip->uac->setRsnd(rrd);
                                 break;
                            case SipUAThreadType_UAS:
                                 if(Sip->uas)
                                    Sip->uas->setRsnd(rrd);
                                 break;
                             }
                      continue;
              }
        }
 }//try
catch(Exception& e){exsSstEXCEPTION(*eltp,"__TSipResendThread::Execute",e);}
}
//---------------------------------------------------------------------------
__fastcall TSipResendThread::~TSipResendThread()
{
#ifdef SIP_Thread_Destruction_Log
TEventLogThread* elt = getLog();
if(elt)elt->FputEvt("\n~TSipResendThread()");
#endif
::DeleteCriticalSection(&srst_cs);
}
//---------------------------------------------------------------------------
void __fastcall TSipResendThread::insertResendList(const TResendReqData& rrd)
{
::EnterCriticalSection(&srst_cs);
  rsl.insert(TResendList::value_type(rrd.dt,rrd.callid));
::LeaveCriticalSection(&srst_cs);
}
//-----------------------------------------------------------------------------
void __fastcall TSipResendThread::eraseResendReq(const TResendReqData& rrd)
{
::EnterCriticalSection(&srst_cs);
  TEventLogThread* elt = getLog();
  if(elt)
    {
    // int a = rsl.size();  //test only
    elt->FputEvt("\n" + (string)"resend_list size " + inttostr(rsl.size()));
    }
  TResendList::iterator it = rsl.find(rrd.dt);
 // if(it!=rsl.end())
    while(it != rsl.end())
         {
         if(rrd.callid == (*it).second)
           {
           rsl.erase(it);
           #ifdef SIP_Erase_Resend_Req_Log
           log_Erase_Resend_Req(rrd);
           #endif
           it = rsl.find(rrd.dt);
           }
         else
           it++;
         }
::LeaveCriticalSection(&srst_cs);
}
//-----------------------------------------------------------------------------
int __fastcall TSipResendThread::procResendBlock(TResendReqData& rrd)
{
int rv=0;
TDateTime dt = dt.CurrentDateTime();
::EnterCriticalSection(&srst_cs);
  TResendList::iterator it = rsl.begin();
  if(it != rsl.end())
    {
    if(dt < (*it).first)
       rv = 1;
    else
       {
       rrd.dt = (*it).first;
       rrd.callid = (*it).second;
       rsl.erase(it);
       rv = 2;
       }
    }
::LeaveCriticalSection(&srst_cs);
return rv;
}
//-----------------------------------------------------------------------------
void __fastcall TSipResendThread::logResendListSize(const string& s)
{
TEventLogThread* elt = getLog();
if(elt)
  {
  int sz;
  ::EnterCriticalSection(&srst_cs);
    sz = rsl.size();
  ::LeaveCriticalSection(&srst_cs);
  elt->FputEvt("\n" + s + " ResendListSize: " + inttostr(sz));
  }
}
//-----------------------------------------------------------------------------
int  __fastcall TSipResendThread::getRslSize()
{
int rv;
::EnterCriticalSection(&srst_cs);
  rv = rsl.size();
::LeaveCriticalSection(&srst_cs);
return rv;
}
//-----------------------------------------------------------------------------
void __fastcall TSipResendThread::log_Erase_Resend_Req(const TResendReqData& rrd)
{
TEventLogThread* elt = getLog();
if(elt)
  {
  string s = "\nErased Resend request: Call-ID " + rrd.callid + "  iStatus ";
  if(rrd.iStatus)
    s += inttostr(rrd.iStatus);
  else
    s += "NDef";
  elt->FputEvt(s);
  }
}
//-----------------------------------------------------------------------------


