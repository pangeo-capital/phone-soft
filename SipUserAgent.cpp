//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "WinRDefs.h"
#include "SipUserAgent.h"
#include "wm_def.h"
#include "Sip.h"
#include "unit4.h"
#include "rsrtp.h"
#include "Conference_Unit.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)
__fastcall TSipUserAgentThread::~TSipUserAgentThread()
{
#ifdef SIP_Thread_Destruction_Log
TEventLogThread* elt = getLog();
if(elt)elt->FputEvt("\n~TSipUserAgentThread()");
#endif
clearLegTrn();
clearExchLst();
if(srst)
  {
  TSipResendThread* SRST = srst;
  srst=NULL;
  SRST->Terminate();
  SRST->Resume_Thread();
  SRST->WaitFor();
  delete SRST;
  }
::DeleteCriticalSection(&ltl_cs);
::DeleteCriticalSection(&rsnd_cs);
}
//---------------------------------------------------------------------------
TLegTrn* __fastcall TSipUserAgentThread::find_previously_created_KEEP_ALIVE_leg_trn()
{
TLegTrn* rv = NULL;
::EnterCriticalSection(&ltl_cs);
  TLegTrnList::iterator it = Ltl.begin();
  while(it != Ltl.end())
       {
       if((*it).second->state == SPS_KEEP_ALIVE)
         {
         rv = (*it).second;
         break;
         }
       it++;
       }
::LeaveCriticalSection(&ltl_cs);
return rv;
}
//---------------------------------------------------------------------------
bool __fastcall TSipUserAgentThread::insertLegTrn(const string& CallID,TLegTrn* lt)
{
bool rv = false;
::EnterCriticalSection(&ltl_cs);
  if(Ltl.find(CallID) == Ltl.end())
    {
    Ltl.insert(TLegTrnList::value_type(CallID,lt));
    rv = true;
    }
::LeaveCriticalSection(&ltl_cs);
return rv;
}
//---------------------------------------------------------------------------
TLegTrn* __fastcall TSipUserAgentThread::getLegTrn(const string& CallID)
{
TLegTrn* lt = NULL;
::EnterCriticalSection(&ltl_cs);
  TLegTrnList::iterator it = Ltl.find(CallID);
  if(it!=Ltl.end())
     lt = (*it).second;
::LeaveCriticalSection(&ltl_cs);
return lt;
}
//---------------------------------------------------------------------------
int __fastcall TSipUserAgentThread::getLegTrnSize()
{
int rv;
::EnterCriticalSection(&ltl_cs);
  rv = Ltl.size();
::LeaveCriticalSection(&ltl_cs);
return rv;
}
//---------------------------------------------------------------------------
bool __fastcall TSipUserAgentThread::isLegTrn(const string& CallID)
{
bool rv;
::EnterCriticalSection(&ltl_cs);
  rv = Ltl.find(CallID) !=  Ltl.end() ? true : false;
::LeaveCriticalSection(&ltl_cs);
return rv;
}
//---------------------------------------------------------------------------
//-- Не удаление Lt, а перенос в очередь на удаление
//---------------------------------------------------------------------------
void __fastcall TSipUserAgentThread::eraseLegTrn(const string&  CallID)
{
::EnterCriticalSection(&ltl_cs);
  TLegTrnList::iterator it = Ltl.find(CallID);
  if(it != Ltl.end())
    {
    TLegTrn* lt = (*it).second;
    MainFormSLS->DLTS.req_to_del(lt);
    Ltl.erase(it);
    }
::LeaveCriticalSection(&ltl_cs);
}
//---------------------------------------------------------------------------
void __fastcall TSipUserAgentThread::DeleteDialog(TLegTrn* Lt)
{
  if(Lt)
    {
    Lt->BLOCK_LEG_TRN();
    ERASE_RESEND_REQUEST(Lt);
    eraseLegTrn(Lt->call_id.getcallid()); //Lt not deleted, replace only in other queue
    Lt->UN_BLOCK_LEG_TRN();
    }
}
//------------------------------------------------------------------------------
void  __fastcall TSipUserAgentThread::clearLegTrn()
{
::EnterCriticalSection(&ltl_cs);
  while(!Ltl.empty())
       {
       TLegTrnList::iterator it = Ltl.begin();
       TLegTrn* lt = (*it).second;
       MainFormSLS->DLTS.req_to_del(lt);
       Ltl.erase(it);
       }
::LeaveCriticalSection(&ltl_cs);
}
//----------------------------------------------------------------------------
void  __fastcall TSipUserAgentThread::printAllCallId()
{
vector<string> v;
::EnterCriticalSection(&ltl_cs);
  for(TLegTrnList::iterator it = Ltl.begin(); it != Ltl.end(); it++)
      v.push_back((*it).first);
::LeaveCriticalSection(&ltl_cs);
if(!v.empty())
  {
  string s;
  switch(uatt){
        case SipUAThreadType_UAC:
             s = "Active UAC Call_IDs:";
             break;
        case SipUAThreadType_UAS:
             s = "Active UAS Call_IDs:";
             break;
        }
  for(unsigned i=0;i<v.size();i++)
      s+="\n" + v[i];
  log_ua(s);
  }
}
//----------------------------------------------------------------------------
void __fastcall TSipUserAgentThread::setRsnd(const TResendReqData& rrd)
{
::EnterCriticalSection(&rsnd_cs);
  rsnd.push(rrd);
  if(Suspended)
     Resume_Thread();
::LeaveCriticalSection(&rsnd_cs);
}
//---------------------------------------------------------------------------
bool __fastcall TSipUserAgentThread::getRsnd(TResendReqData& rrd)
{
bool rv=false;
::EnterCriticalSection(&rsnd_cs);
  if(!rsnd.empty())
    {
    rv=true;
    TResendReqData RRD = rsnd.front();
    rsnd.pop();
    rrd=RRD;
    }
::LeaveCriticalSection(&rsnd_cs);
return rv;
}
//---------------------------------------------------------------------------
int __fastcall TSipUserAgentThread::getRsndSize()
{
int rv=0;
::EnterCriticalSection(&rsnd_cs);
  rv=rsnd.size();
::LeaveCriticalSection(&rsnd_cs);
return rv;
}
//---------------------------------------------------------------------------
bool __fastcall TSipUserAgentThread::IsResendEmpty()
{
bool rv=false;
::EnterCriticalSection(&rsnd_cs);
  if(rsnd.empty())
     rv=true;
::LeaveCriticalSection(&rsnd_cs);
return rv;
}
//---------------------------------------------------------------------------
TOutputSipBuf* __fastcall TSipUserAgentThread::RESEND_PROC(const TResendReqData& rrd)
{
#ifdef SIP_Thread_Resend_Proc_Log
TEventLogThread* elt = getLog();
if(elt)
  elt->FputEvt("\nTSipUserAgentThread::resendProc()");
#endif
TOutputSipBuf* rv = NULL;
TLegTrn* Lt = getLegTrn(rrd.callid);
if(Lt)
 {
 Lt->BLOCK_LEG_TRN();
 if(Lt->resendblock.sls != SPS_UNKNOWN)
  if(Lt->resendblock.dt == rrd.dt)
    {
    #ifdef SIP_Thread_Resend_Proc_Log
    if(elt)
      {
      string t_str;
      TDateTime dt = dt.CurrentTime();
      exsTime(dt, t_str);
      elt->FputEvt("\n" + t_str + " TSipUserAgentThread::resendProc(): " + decodeSls(Lt->resendblock.sls) +
                    " Lt->resendblock.resendNum: " + inttostr(Lt->resendblock.resendNum));
      }
    #endif
    if(--Lt->resendblock.resendNum <= 0)
      {
      switch(Lt->resendblock.sls){
             case SPS_WAIT_FINAL_RESP:{ //Expires timer "Wait final response"
                  ERASE_RESEND_REQUEST(Lt);
                  break;
                  }  //end of case SPS_WAIT_FINAL_RESP:
             case SPS_INIT_REGISTER_REQ:{
                  TResendReqData rrd;
                  ERASE_RESEND_REQUEST(Lt,rrd);
                  ::PostMessage(Sip->getMFHandle(),SIP_UA_MSG,WM_APP_MSG_WPARAM__UAC,WM_APP_MSG_LPARAM__REGISTER_FAILED);
                  if(Lt->keepalive)
                    {
                    Lt->keepalive = false;
                    TLegTrn* Lt_kpl = getLegTrn(Lt->keepalive_callid);
                    if(Lt_kpl)
                      {
                      Lt_kpl->BLOCK_LEG_TRN();
                      eraseLegTrn(Lt_kpl->call_id.getcallid());
                      Lt_kpl->UN_BLOCK_LEG_TRN();
                      }
                    }
                  Lt->state                 = SPS_FAILED_REGISTER_REQ;
                  Lt->resendblock.sls       = SPS_FAILED_REGISTER_REQ;
                  Lt->resendblock.dt        = Lt->resendblock.dt.CurrentDateTime();
                  Lt->resendblock.dt       += TDateTime(0,0,REGISTER_FAILED_RESEND_INTERVAL,0);
                  Lt->resendblock.resendNum = REGISTER_FAILED_RESEND_COUNT;
                  Lt->resendblock.respNum   = REGISTER_RESPONSE_COUNT;
                  INSERT_RESEND_REQUEST(rrd,Lt);
                  if(Sip->Sip_TransportAuto)
                     Sip->change_sip_transport();
                  break;
                  }
             case SPS_REGISTER_REQ:{
                  TResendReqData rrd;
                  ERASE_RESEND_REQUEST(Lt,rrd);
                  ::PostMessage(Sip->getMFHandle(),SIP_UA_MSG,WM_APP_MSG_WPARAM__UAC,WM_APP_MSG_LPARAM__REGISTER_FAILED);
                  if(Lt->keepalive)
                    {
                    Lt->keepalive = false;
                    TLegTrn* Lt_kpl = getLegTrn(Lt->keepalive_callid);
                    if(Lt_kpl)
                      {
                      Lt_kpl->BLOCK_LEG_TRN();
                      eraseLegTrn(Lt_kpl->call_id.getcallid());
                      Lt_kpl->UN_BLOCK_LEG_TRN();
                      }
                    }
                  Lt->state                 = SPS_FAILED_REGISTER_REQ;
                  Lt->resendblock.sls       = SPS_FAILED_REGISTER_REQ;
                  Lt->resendblock.dt        = Lt->resendblock.dt.CurrentDateTime();
                  Lt->resendblock.dt       += TDateTime(0,0,REGISTER_FAILED_RESEND_INTERVAL,0);
                  Lt->resendblock.resendNum = REGISTER_FAILED_RESEND_COUNT;
                  Lt->resendblock.respNum   = REGISTER_RESPONSE_COUNT;
                  INSERT_RESEND_REQUEST(rrd,Lt);
                  break;
                  }

             case SPS_FINAL_REGISTER_REQ:{
                  ::PostMessage(Sip->getMFHandle(),SIP_UA_MSG,WM_APP_MSG_WPARAM__UAC,WM_APP_MSG_LPARAM__FINAL_REG_END);
                  if(Lt->keepalive)
                    {
                    Lt->keepalive = false;
                    TLegTrn* Lt_kpl = getLegTrn(Lt->keepalive_callid);
                    if(Lt_kpl)
                      {
                      Lt_kpl->BLOCK_LEG_TRN();
                      eraseLegTrn(Lt_kpl->call_id.getcallid());
                      Lt_kpl->UN_BLOCK_LEG_TRN();
                      }
                    else
                      DeleteDialog(Lt);  //!!!
                    }
                  else
                    DeleteDialog(Lt);  //!!!
                  break;
                  }
             case SPS_INIT_SUBSCRIBE_REQ:
                //  if(!Lt->tousername.empty())   //On Strat Subscribe Proc Lt->tousername is empty
                //    {
                //    Sip->Contacts.AS.del_subscribed_contact(Lt->tousername);  //Удаляем свою подписку на получение нотификаций от данного абонента
                //    Sip->Contacts.set_contact_state(Lt->tousername, ClientState_Off_Line); // и переводим данног абонента с в сост Off_Line
                //    ::PostMessage(Sip->getMFHandle(),SIP_UA_MSG,WM_APP_MSG_WPARAM__UAC,WM_APP_MSG_LPARAM__CONTACT_LIST_REFRESH);
                //    }
                  DeleteDialog(Lt);  //ERASE_RESEND_REQUEST() inside of this func
                  break;
             case SPS_PRESENCE_NOTIFY_REQ:
                  if(!Lt->tousername.empty())
                     Sip->Contacts.SS.del_subscribed_contact(Lt->tousername);  //Удаляем подписку ко мне на получение нотификаций
                  DeleteDialog(Lt);  //ERASE_RESEND_REQUEST() inside of this func
                  break;
             default:{
                     eraseLegTrn(Lt->call_id.getcallid());  // Lt->UN_BLOCK_LEG_TRN() ниже !!!
                     }
             } //end of switch(Lt->resendblock.sls)
      Lt->UN_BLOCK_LEG_TRN();
      return rv;
      } //if(--Lt->resendblock.resendNum <= 0)

    switch(Lt->resendblock.sls){   //Lt->resendblock.resendNum > 0
             case SPS_INIT_REGISTER_REQ:{
                  TResendReqData rrd;
                  ERASE_RESEND_REQUEST(Lt,rrd);
                  Lt->resendblock.dt = Lt->resendblock.dt.CurrentDateTime();
                  if(Lt->resendblock.resendNum > 10)
                     Lt->resendblock.dt += TDateTime(0,0,0,REGISTER_INITIAL_RESEND_INTERVAL);   //500 msec
                  else if(Lt->resendblock.resendNum > 5)
                     Lt->resendblock.dt += TDateTime(0,0,REGISTER_INITIAL_RESEND_INTERVAL_1,0); //1 sec
                  else
                     Lt->resendblock.dt += TDateTime(0,0,REGISTER_INITIAL_RESEND_INTERVAL_2,0); //2 sec
                  INSERT_RESEND_REQUEST(rrd,Lt);
                  rv = new TOutputSipBuf;
                  if(rv)
                    {
                    rv->ToIP   = Lt->resendblock.ToIP;
                    rv->ToPort = Lt->resendblock.ToPort;
                    rv->CallID = Lt->call_id.getcallid();
                    rv->dt     = Lt->resendblock.dt;
                    rv->s      = Lt->resendblock.s;
                    }
                  Lt->UN_BLOCK_LEG_TRN();
                  return rv;
                  }
             case SPS_FAILED_REGISTER_REQ:{
                  TResendReqData rrd;
                  ERASE_RESEND_REQUEST(Lt,rrd);
                  Lt->resendblock.dt        = Lt->resendblock.dt.CurrentDateTime();
                  Lt->resendblock.dt       += TDateTime(0,0,REGISTER_FAILED_RESEND_INTERVAL,0);
                  Lt->resendblock.resendNum = REGISTER_FAILED_RESEND_COUNT;
                  Lt->resendblock.respNum   = REGISTER_RESPONSE_COUNT;
                  INSERT_RESEND_REQUEST(rrd,Lt);
                  rv = new TOutputSipBuf;
                  if(rv)
                    {
                    int cseq   = Sip->crh.getCSeqRegister();
                    change_cseq_on_register_failed(Lt->resendblock.s, cseq); //При
                    rv->ToIP   = Lt->resendblock.ToIP;
                    rv->ToPort = Lt->resendblock.ToPort;
                    rv->CallID = Lt->call_id.getcallid();
                    rv->dt     = Lt->resendblock.dt;
                    rv->s      = Lt->resendblock.s;
                    }
                  if(Sip->Sip_TransportAuto)
                    if(!--Lt->resendblock.repeat_count)
                      {
                      Sip->change_sip_transport();
                      Lt->resendblock.repeat_count = 2;
                      }
                  Lt->UN_BLOCK_LEG_TRN();
                  return rv;
                  }
             case SPS_INVITE_REQ:
             case SPS_INVITE_FILETRANSFER_REQ:
             case SPS_INVITE_SCREENSHARING_REQ:{
                  TResendReqData rrd;
                  ERASE_RESEND_REQUEST(Lt,rrd);
                  Lt->resendblock.dt  = Lt->resendblock.dt.CurrentDateTime();
                  if(Lt->resendblock.resendNum > 10)
                     Lt->resendblock.dt += TDateTime(0,0,0,INVITE_RESEND_INTERVAL);   //500 msec
                  else if(Lt->resendblock.resendNum > 5)
                     Lt->resendblock.dt += TDateTime(0,0,INVITE_RESEND_INTERVAL_1,0); //1 sec
                  else
                     Lt->resendblock.dt += TDateTime(0,0,INVITE_RESEND_INTERVAL_2,0); //2 sec
                  INSERT_RESEND_REQUEST(rrd,Lt);
                  rv = new TOutputSipBuf;
                  if(rv)
                    {
                    rv->ToIP   = Lt->resendblock.ToIP;
                    rv->ToPort = Lt->resendblock.ToPort;
                    rv->CallID = Lt->call_id.getcallid();
                    rv->dt     = Lt->resendblock.dt;
                    rv->s      = Lt->resendblock.s;
                    }
                  Lt->UN_BLOCK_LEG_TRN();
                  return rv;
                  }
          }

    Lt->UpdateResendInterval();
    rv = new TOutputSipBuf;
    if(rv)
       {
       rv->ToIP   = Lt->resendblock.ToIP;
       rv->ToPort = Lt->resendblock.ToPort;
       rv->CallID = Lt->call_id.getcallid();
       rv->dt     = Lt->resendblock.dt;
       rv->s = Lt->resendblock.s;
       }
    }//if(Lt->resendblock.dt == rrd.dt)
 Lt->UN_BLOCK_LEG_TRN();
 }//if(Lt)
return rv;
}
//----------------------------------------------------------------------------
void  __fastcall TSipUserAgentThread::change_cseq_on_register_failed(string& s,int cseq)
{
string s1,s2;
int st = s.find("CSeq:");
if(st != -1)
  {
  s1 = s.substr(0,st);
  st = s.find(crlf,st);
  if(st != -1)
    {
    s1 += "CSeq:" + WS + inttostr(cseq) + WS + "REGISTER" + s.substr(st);
    s   = s1;
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TSipUserAgentThread::log_ua(const string& s)
{
TEventLogThread* elt = getLog();
if(elt)
  elt->FputEvt("\n" + s);
}
//----------------------------------------------------------------------------
void __fastcall TSipUserAgentThread::log_In_QueueSize(const string& s)
{
TEventLogThread* elt = getLog();
if(elt)
  {
  int sz = getQueueSize();
  elt->FputEvt("\n" + s + inttostr(sz));
  }
}
//----------------------------------------------------------------------------
void __fastcall TSipUserAgentThread::log_Sent_QueueSize(const string& s)
{
TEventLogThread* elt = getLog();
if(elt)
  {
  int sz = getSentSize();
  elt->FputEvt("\n" + s + inttostr(sz));
  }
}
//----------------------------------------------------------------------------
void __fastcall TSipUserAgentThread::log_Resend_Req_QueueSize(const string& s)
{
TEventLogThread* elt = getLog();
if(elt)
  {
  int sz = getRsndSize();
  elt->FputEvt("\n" + s + inttostr(sz));
  }
}
//----------------------------------------------------------------------------
void __fastcall TSipUserAgentThread::log_crypto_keys(const string& h,vector<string>& v)
{
string s = h + "\n";
int sz = v.size();
for(int i= 0;i<sz;i++)
    s += v[i] + "\n";
log_ua(s);
}
//------------------------------------------------------------------------------
//-------------- Check of Lt existing before calling ClearResendBlock() --------
//------------------------------------------------------------------------------
void  __fastcall TSipUserAgentThread::INSERT_RESEND_REQUEST(TLegTrn* Lt)
{
if(srst){
  TResendReqData rrd;
  rrd.dt       = Lt->resendblock.dt;
  rrd.callid   = Lt->call_id.getcallid();
  srst->insertResendList(rrd);
  }
}
//------------------------------------------------------------------------------
void  __fastcall TSipUserAgentThread::INSERT_RESEND_REQUEST(TOutputSipBuf* ospb)
{
if(srst)
  {
  TResendReqData rrd;
  rrd.dt       = ospb->dt;
  rrd.callid   = ospb->CallID;
  srst->insertResendList(rrd);
  }
}
//------------------------------------------------------------------------------
void  __fastcall TSipUserAgentThread::INSERT_RESEND_REQUEST(TResendReqData& rrd, TLegTrn* Lt)
{
if(srst){
   rrd.dt       = Lt->resendblock.dt;
   rrd.callid   = Lt->call_id.getcallid();
   srst->insertResendList(rrd);
   }
}
//------------------------------------------------------------------------------
void  __fastcall TSipUserAgentThread::ERASE_RESEND_REQUEST(TLegTrn* Lt)
{
if(srst){
  TResendReqData rrd;
  rrd.dt       = Lt->resendblock.dt;
  rrd.callid   = Lt->call_id.getcallid();
  srst->eraseResendReq(rrd);
  }
}
//------------------------------------------------------------------------------
void  __fastcall TSipUserAgentThread::ERASE_RESEND_REQUEST(TLegTrn* Lt, int RespStatus)
{
if(srst){
  TResendReqData rrd;
  rrd.iStatus  = RespStatus;
  rrd.dt       = Lt->resendblock.dt;
  rrd.callid   = Lt->call_id.getcallid();
  srst->eraseResendReq(rrd);
  }
}
//------------------------------------------------------------------------------
void  __fastcall TSipUserAgentThread::ERASE_RESEND_REQUEST(TLegTrn* Lt, TResendReqData& rrd)
{
if(srst){
  rrd.dt     = Lt->resendblock.dt;
  rrd.callid = Lt->call_id.getcallid();
  srst->eraseResendReq(rrd);
  }
}
//------------------------------------------------------------------------------
void  __fastcall TSipUserAgentThread::ClearResendBlock(TLegTrn* Lt,int RespStatus,bool Conditional)
{
switch(Lt->resendblock.sls){
       case SPS_UNKNOWN:return;

    /*   case SPS_MESSAGE_REQ:
            case 100:   return;        //Wait for 200

        case SPS_INIT_SUBSCRIBE_REQ:
            switch(RespStatus){
                   case 100:   //return; //Wait for 200 or 202  - возможно необходимо восстановить
                   case 200:
                   case 202:{
                            Lt->resendblock.sls = SPS_UNKNOWN;
                            ERASE_RESEND_REQUEST(Lt,RespStatus);
                            return;
                            }
                   }
            break;

       case SPS_PRESENCE_NOTIFY_REQ:
            switch(RespStatus){
                   case 100:return; //Wait for 200
                   case 200:{
                            Lt->resendblock.sls = SPS_UNKNOWN;
                            ERASE_RESEND_REQUEST(Lt,RespStatus);
                            return;
                            }
                   }
            break;
        */

       case SPS_FAILED_REGISTER_REQ:
            switch(RespStatus){
                  case 100:return; //Wait for 200
                  }
            break;
       case SPS_WAIT_FINAL_RESP:{
            switch(RespStatus){
                  case 100:return;
                  case 180:return; //100, 180 resp don't stop WAIT_FINAL_RESP timer. Another responces stop this timer
                  }
            break;
            }
       }
if(!Conditional)
  {
  Lt->resendblock.sls = SPS_UNKNOWN;
  ERASE_RESEND_REQUEST(Lt,RespStatus);
  }
else
  {
  switch(Lt->resendblock.sls){
        case SPS_INVITE_REQ:
             ERASE_RESEND_REQUEST(Lt,RespStatus);
             return;
        case SPS_INVITE_FILETRANSFER_REQ:
        case SPS_INVITE_SCREENSHARING_REQ:{
             if(RespStatus == 100)
               {
               ERASE_RESEND_REQUEST(Lt,RespStatus);
               Lt->resendblock.dt  += TDateTime(0,0,INVITE_RESEND_AFTER_100_RESP_INTERVAL,0);
               Lt->resendblock.resendNum = INVITE_RESEND_COUNT;
               Lt->resendblock.respNum   = 1;
               INSERT_RESEND_REQUEST(Lt);
               return;
               }
             break;
             }
        case SPS_INIT_REGISTER_REQ:
        case SPS_REGISTER_REQ:{
             if(RespStatus == 100)
               {
               ERASE_RESEND_REQUEST(Lt,RespStatus);
               Lt->resendblock.dt       += TDateTime(0,0,REGISTER_WAIT_200OK_RESEND_INTERVAL,0);  //Wait  20sec 200OK after recvd responce 100
               Lt->resendblock.resendNum = REGISTER_WAIT_200OK_RESEND_COUNT;    //0xFFFFFFFF
               Lt->resendblock.respNum   = REGISTER_RESPONSE_COUNT;
               Lt->resendblock.sls_aux   = SPS_WAIT_200OK_REGISTER;
               INSERT_RESEND_REQUEST(Lt);
               return;
               }
             if(RespStatus == 200)
                Lt->resendblock.sls_aux   = SPS_UNKNOWN;
             break;
             }
        case SPS_BYE_REQ:{
             if(RespStatus == 100)
               {
               ERASE_RESEND_REQUEST(Lt,RespStatus);
               Lt->resendblock.dt       += TDateTime(0,0,WAIT_DEFAULT,0);
               Lt->resendblock.resendNum = 0;
               Lt->resendblock.respNum   = 1;
               INSERT_RESEND_REQUEST(Lt);
               return;
               }
             break;
             }
        }//switch(Lt->resendblock.sls)
      if(--Lt->resendblock.respNum <= 0)
         {
         Lt->resendblock.sls = SPS_UNKNOWN;
         ERASE_RESEND_REQUEST(Lt,RespStatus);
         }
      else //Received 200OK. Wait for 487 -- Request Terminated
        {
        ERASE_RESEND_REQUEST(Lt,RespStatus);
        Lt->resendblock.dt += TDateTime(0,0,WAIT_487_RESPONSE,0);
        Lt->resendblock.resendNum = 0;
        INSERT_RESEND_REQUEST(Lt);
        }
  }
}
//-----------------------------------------------------------------------------
string __fastcall TSipUserAgentThread::decodeSls(SipLegState sls)
{
string s = "sls: ";
switch(sls){
      case SPS_INIT_REGISTER_REQ: return s+"SPS_INIT_REGISTER_REQ";
      case SPS_REGISTER_REQ:      return s+"SPS_REGISTER_REQ";
      case SPS_INIT_SUBSCRIBE_REQ:return s+"SPS_INIT_SUBSCRIBE_REQ";
      case SPS_MESSAGE_REQ:       return s+"SPS_MESSAGE_REQ";  
      case SPS_FINAL_REGISTER_REQ:return s+"SPS_FINAL_REGISTER_REQ";
      case SPS_WAIT_FINAL_RESP:   return s+"SPS_WAIT_FINAL_RESP";
      case SPS_DECLINE_REQ:       return s+"SPS_DECLINE_REQ";      
      case SPS_KEEP_ALIVE:        return s+"SPS_KEEP_ALIVE";
      default:                    return s+="UNKNOWN";
      }
}
//-----------------------------------------------------------------------------
void  __fastcall TSipUserAgentThread::getRTPConnectAddr(TSipParsBuf* spb)
{
int st=spb->sdp.Sdp.find("c=IN IP4");
if(st==-1)return;
st+=9;
int en=spb->sdp.Sdp.find(crlf,st);
if(en==-1)return;
int len=en-st;
if(len<1)return;
spb->sdp.audio.s_remotertpip = spb->sdp.Sdp.substr(st,len);
//spb->sdp.remotertpip = StrIpToInt(spb->sdp.s_remotertpip);
}
//------------------------------------------------------------------------------
void  __fastcall TSipUserAgentThread::getMediaSubStrParameters(string& subs,const string& s,int& n,const length)
{
int en = 0;
while(n < length-1)
     {
     en = s.find_first_of(WS,n);
     if(en==-1)return;
     if(en > n)
        break;
     n++;
     }
int len = en - n;
if(len < 1)return;
subs = s.substr(n,len);
n = en;
}
//------------------------------------------------------------------------------
void  __fastcall TSipUserAgentThread::getCodecList(vector<int>& media,const string& S,int& n,const length)
{
string s = S;
s+=WS;
int len = length + 1; //result of s+=ws
while(n < len)
     {
     if(n < 1)
        return;
     string str;
     getMediaSubStrParameters(str,s,n,len);
     if(str.empty())
        return;
     media.push_back(atoi(str.c_str()));
     }
}
//------------------------------------------------------------------------------
void  __fastcall TSipUserAgentThread::pars_m_elements(TSdpMedia& media, const string& s, const string& media_type, int& en, const length)
{
media.media_type = media_type;
string remrtp;
getMediaSubStrParameters(remrtp,s,en,length);
media.remotertpport = atoi(remrtp.c_str());
getMediaSubStrParameters(media.media_protocol, s, en, length);
getCodecList(media.codecs, s, en, length);
}
//------------------------------------------------------------------------------
void  __fastcall TSipUserAgentThread::get_media_crypto_keys(TSdpMedia& media,const string& s,int pos)
{
int st = 0;
int en = 0;
while((st = s.find("a=crypto:",pos)) != -1)
     {
     en = s.find(crlf,st);
     if(en == -1)
        break;
     media.crypto_keys.push_back(s.substr(st,en - st));
     pos = en;
     }
}
//------------------------------------------------------------------------------
void  __fastcall TSipUserAgentThread::getMediaParameters(TSipParsBuf* spb)
{
//1st step
int st=spb->sdp.Sdp.find("m=");
if(st==-1)return;
int st_1 = st+2; //start position for next search
int en = spb->sdp.Sdp.find_first_of(crlf,st);
if(en==-1)return;
int length = en-st;
if(length<1)return;
string s = spb->sdp.Sdp.substr(st,length);
//if(lt)     //lt - may be NULL
//   lt->in_media = s;

string media_type;
en=2;
getMediaSubStrParameters(media_type, s, en, length);
if(media_type == "audio")
  pars_m_elements(spb->sdp.audio, s, media_type, en, length);
else if(media_type == "video")
  pars_m_elements(spb->sdp.video, s, media_type, en, length);

//2nd step
st_1 += length;
st = spb->sdp.Sdp.find("m=",st_1);
if(st==-1)
  {
  if(media_type == "audio")
     get_media_crypto_keys(spb->sdp.audio,spb->sdp.Sdp,st_1);
  else if(media_type == "video")
     get_media_crypto_keys(spb->sdp.video,spb->sdp.Sdp,st_1);
  return;
  }
else
  {
  if(st_1 < st)
    {
    string s = spb->sdp.Sdp.substr(st_1,st - st_1);
    if(media_type == "audio")
       get_media_crypto_keys(spb->sdp.audio,s,0);
    else if(media_type == "video")
       get_media_crypto_keys(spb->sdp.video,s,0);
    }
  }
//int st_1 = st+2; //start position for next search
en = spb->sdp.Sdp.find_first_of(crlf,st);
if(en==-1)return;
length = en-st;
if(length<1)return;
s = spb->sdp.Sdp.substr(st,length);
//if(lt)
//   lt->in_media_1 = s;
#ifdef SIP_Video
en=2;
getMediaSubStrParameters(media_type, s, en, length);
if(media_type == "audio")
  pars_m_elements(spb->sdp.audio, s, media_type, en, length);
else if(media_type == "video")
  pars_m_elements(spb->sdp.video, s, media_type, en, length);
st_1 = st += length;
if(media_type == "audio")
   get_media_crypto_keys(spb->sdp.audio,spb->sdp.Sdp,st_1);
else if(media_type == "video")
   get_media_crypto_keys(spb->sdp.video,spb->sdp.Sdp,st_1);
#endif
}
//------------------------------------------------------------------------------
void  __fastcall TSipUserAgentThread::getSDPElements_FromInMsg(TLegTrn* lt,TSipParsBuf* spb)
{
int len = spb->sdp.Sdp.length();
if(!len)return;
getRTPConnectAddr(spb);
getMediaParameters(spb);
#ifdef SIP_Video
if(spb->sdp.video.remotertpport != -1)
  if(spb->sdp.video.s_remotertpip.empty())
     spb->sdp.video.s_remotertpip = spb->sdp.audio.s_remotertpip;
#endif
lt->in_sdp = spb->sdp;
}
//------------------------------------------------------------------------------
void  __fastcall TSipUserAgentThread::FindCryptoKeys(TLegTrn* Lt,TSipParsBuf* spb)
{
if(!spb->sdp.audio.crypto_keys.empty())
  {
  log_crypto_keys("Found audio crypto keys:", spb->sdp.audio.crypto_keys);
  TUdpChannel* uc = Sip->ucs->getUdpChannel(Lt->ch_rtp_audio);
  if(uc)
     PREPARE_INGRESS_SRTP_Session(uc, spb->sdp.audio.crypto_keys);
  else
     Lt->request_srtp(SRTP_TYPE_AUDIO, SK_SET, spb->sdp.audio.crypto_keys); //On Invite (not ReInvite) received
  }
if(!spb->sdp.video.crypto_keys.empty())
  {
  log_crypto_keys("Found video crypto keys:", spb->sdp.video.crypto_keys);
  TUdpChannel* uc = Sip->ucs->getUdpChannel(Lt->ch_rtp_video);
  if(uc)
     PREPARE_INGRESS_SRTP_Session(uc, spb->sdp.video.crypto_keys);
  else
     Lt->request_srtp(SRTP_TYPE_VIDEO, SK_SET, spb->sdp.video.crypto_keys);  //On Invite (not ReInvite) received
  }
}
//------------------------------------------------------------------------------
int __fastcall TSipUserAgentThread::getcseq(TSipParsBuf* spb)
{
int st = spb->CSeq.find_first_of("123456789",0);
if(st==-1)return 0;
int en = spb->CSeq.find(" ",st);
if(en==-1)return 0;
if((en-st)<1)return 0;
return atoi(spb->CSeq.substr(st,(en-st)).c_str());
}
//------------------------------------------------------------------------------
void __fastcall TSipUserAgentThread::CheckResendQueue()
{
bool a = false;
TResendReqData rrd;
if(!getRsnd(rrd))
  {
  #ifdef SIP_UA_RESEND_LIST_Log
  switch(uatt){
        case SipUAThreadType_UAC:
             log_Resend_Req_QueueSize("TSipUacThread::Execute(): S_U_S_P_E_N_D resend_req_queue size ");
             break;
        case SipUAThreadType_UAS:
             log_Resend_Req_QueueSize("TSipUasThread::Execute(): S_U_S_P_E_N_D resend_req_queue size ");
             break;
        }
  #endif
  Suspend_Thread();
  return;
  }
TOutputSipBuf* ospb = RESEND_PROC(rrd);
if(ospb)
  {
  INSERT_RESEND_REQUEST(ospb);
  switch(Sip->sip_transport){
      case Sip_Transport_TCP:
           if(!Sip->TCP_Dropped)
               Sip->SetOutQueue(ospb);
           break;
      case Sip_Transport_TLS:
           if(!Sip->TLS_Dropped)
               Sip->SetOutQueue(ospb);
           break;
      default: Sip->SetOutQueue(ospb);
           break;
      }
  }
updateSentQueue(ospb, a);
#ifdef SIP_UA_RESEND_LIST_Log
switch(uatt){
      case SipUAThreadType_UAC:
           log_Sent_QueueSize("TSipUacThread::Execute(): sent_queue size ");
           break;
      case SipUAThreadType_UAS:
           log_Sent_QueueSize("TSipUasThread::Execute(): sent_queue size ");
           break;
      }
#endif
}
//------------------------------------------------------------------------------
void __fastcall TSipUserAgentThread::InitResendProc(TOutputSipBuf* ospb,TLegTrn* Lt)
{
Lt->PrepareResendBlock(ospb);
INSERT_RESEND_REQUEST(Lt);
}
//------------------------------------------------------------------------------
void __fastcall TSipUserAgentThread::prepareContentLength(BaseExchangeBlock* bb)
{
bb->ContentLength = "Content-Length:" + WS + inttostr(bb->sdp.Sdp.length()) + sdpboundary;
}
//----------------------------------------------------------------------------
void __fastcall TSipUserAgentThread::prepare_INVITE_Final(TOutputSipBuf* ospb,TUdpChannel* uc_audio,TUdpChannel* uc_video)
{
if(Sip->ss_tls_t)
  {
  PREPARE_EGRESS_SRTP_Session(uc_audio);
  PREPARE_EGRESS_SRTP_Session(uc_video);
  }
prepare_Sdp_Final(&ospb->sdp,uc_audio,uc_video);
prepareContentLength(ospb);
ospb->s = "INVITE"  + WS + ospb->requestline +
ospb->via           +
ospb->maxforwards   +
ospb->Contact       +
ospb->To            +
ospb->from          +                                                                          
ospb->callid        +
ospb->cseq          +
ospb->allow         +
ospb->contenttype   +
ospb->UserAgent     +
ospb->ReferredBy    +
ospb->Replaces      +
ospb->ContentLength +
ospb->sdp.Sdp;
}
//------------------------------------------------------------------------------
void __fastcall TSipUserAgentThread::prepare_INVITE_Final_For_ScreenSharing(TOutputSipBuf* ospb)
{
prepareContentLength(ospb);
ospb->s = "INVITE" + WS + ospb->requestline +
ospb->via          +
ospb->maxforwards  +
ospb->Contact      +
ospb->To           +
ospb->from         +
ospb->callid       +
ospb->cseq         +
ospb->allow        +
ospb->contenttype  +
ospb->UserAgent    +
ospb->ContentLength +
ospb->sdp.Sdp;
}
//-----------------------------------------------------------------------------------
//-- For RTP TRANSMISSION (OUTGOING calls ("INVITE") and INCOMING calls ("200 Ok") --
//-----------------------------------------------------------------------------------
void __fastcall TSipUserAgentThread::PREPARE_EGRESS_SRTP_Session(TUdpChannel* uc)
{
if(uc)
 if(uc->sendThread)
   {
   if(!uc->sendThread->getSRTP())
       uc->sendThread->createSRTP();
   TSRTPCrypto* crypto = uc->sendThread->getSRTP();
   if(crypto)
      crypto->create_egress_srtp_session();
   }
}
//--------------------------------------------------------------------------------
//-- For RTP RECEIVING (OUTGOING calls ("200 Ok") and INCOMING calls ("INVITE") --
//--------------------------------------------------------------------------------
void __fastcall TSipUserAgentThread::PREPARE_INGRESS_SRTP_Session(TUdpChannel* uc, vector<string>& v)
{
if(uc)
 if(uc->chDispThread)
   {
   if(!uc->chDispThread->getSRTP())
       uc->chDispThread->createSRTP();
   TSRTPCrypto* crypto = uc->chDispThread->getSRTP();
   if(crypto)
      crypto->create_ingress_srtp_session(v);
   }
}
//-----------------------------------------------------------------------------
void __fastcall TSipUserAgentThread::prepare_ANSWER_Final(TLegTrn* Lt,TOutputSipBuf* ospb,TUdpChannel* uc_audio,TUdpChannel* uc_video)
{
if(!Lt)return;
if(Sip->ss_tls_t)
  {
  vector<string> v;
  if(Lt->request_srtp(SRTP_TYPE_AUDIO, SK_GET, v))
     {
     PREPARE_EGRESS_SRTP_Session(uc_audio);
     PREPARE_INGRESS_SRTP_Session(uc_audio,v);
     }
  v.clear();
  if(Lt->request_srtp(SRTP_TYPE_VIDEO, SK_GET, v))
     {
     PREPARE_EGRESS_SRTP_Session(uc_video);
     PREPARE_INGRESS_SRTP_Session(uc_video,v);
     }
  }
Lt->state    = SPS_ANSWER_REQ;
ospb->ToIP   = Lt->remoteip;
ospb->ToPort = Lt->remoteport;
prepare_Sdp_Final(&ospb->sdp,uc_audio,uc_video);
ospb->To    = Lt->to;
if(Lt->mytag.empty())
  {
  TSipParsBuf temp;
  Sip->generateToTag(&temp);
  Lt->mytag = temp.totag;
//      spb->To += ";tag=" + temp.totag + crlf;
  }
ospb->totag = Lt->mytag;
Sip->prepareToTag_Final(ospb);

prepareContentLength(ospb);

ospb->s = SipVers + WS + "200 OK" + crlf;
Lt->OrigVia.InsertHeaders(ospb->s);ospb->s+=
ospb->Contact           +
ospb->To                +
Lt->from                +
"Call-ID:" + WS + Lt->call_id.getcallid() + crlf +
Lt->cseqrcvd            +
ospb->allow             +
ospb->contenttype       +
ospb->UserAgent         +
ospb->ContentLength     +
ospb->sdp.Sdp;
}
//----------------------------------------------------------------------------
void __fastcall TSipUserAgentThread::prepare_ANSWER_ON_SHARING_INVITE_Final(TLegTrn* Lt,TOutputSipBuf* ospb)
{
ospb->s = SipVers + WS + "200 OK" + crlf;
Lt->OrigVia.InsertHeaders(ospb->s);ospb->s+=
ospb->Contact           +
ospb->To                +
Lt->from                +
"Call-ID:" + WS + Lt->call_id.getcallid() + crlf +
Lt->cseqrcvd            +
ospb->UserAgent         +
ospb->ContentLength;
}
//----------------------------------------------------------------------------
void __fastcall TSipUserAgentThread::prepare_Sdp_Final(TSdp* sdp,TUdpChannel* uc_audio,TUdpChannel* uc_video)
{
if(uc_audio)
  {
  uc_audio->INIT_Sdp_For_SRTP_Session(&sdp->audio,uatt);
  sdp->audio.localrtpport = uc_audio->localport;
  }
#ifdef SIP_Video
if(uc_video)
  {
  uc_video->INIT_Sdp_For_SRTP_Session(&sdp->video,uatt);
  sdp->video.localrtpport = uc_video->localport;
  }
#endif
sdp->prepSdpStr();
}
//----------------------------------------------------------------------------
void __fastcall TSipUserAgentThread::prepare_Sdp_Final__for_200OK_On_Reinvite_With_Add_Video_Req(TSdp* sdp,TUdpChannel* uc_video)
{
if(uc_video)
  {
  uc_video->INIT_Sdp_For_SRTP_Session(&sdp->video,uatt);
  sdp->video.localrtpport = uc_video->localport;
  sdp->addVideoToSdpStr();
  }
}
//------------------------------------------------------------------------------
void __fastcall TSipUserAgentThread::Create_Media_Channels(TLegTrn* Lt, TOutputSipBuf* ospb, TSessionChannelCollect& sc)
{
if(Sip->ucs)
  {
  Sip->ucs->Create_RTP_PairCh(SOUND_MPT,&sc.uc_sound,NULL,Lt,1,1,ospb);
  Sip->ucs->Create_RTP_PairCh(RTP_AUDIO_MPT,&sc.uc_rtp_audio,&sc.uc_rtcp_audio,Lt,-1,-1,ospb);//rpp.RemoteHost_1,rpp.RemotePort_1,
  #ifdef SIP_Video
  if(ospb->vcpar)
    {
    Sip->ucs->Create_RTP_PairCh(VIDEO_MPT,&sc.uc_video,NULL,Lt,1,1,ospb);
    Sip->ucs->Create_RTP_PairCh(RTP_VIDEO_MPT,&sc.uc_rtp_video,&sc.uc_rtcp_video,Lt,-1,-1,ospb);
    }
  #endif
  #ifdef Client_Test_Block
  Connect_Media_Channels_Test(sc);
  #else
  Connect_Media_Channels(sc);
  #endif
  #ifdef SIP_Video
  if(sc.uc_video)
    Form4->ins_vcl(sc.uc_video->getChId());
  #endif
  }
}
//------------------------------------------------------------------------------
void __fastcall TSipUserAgentThread::Create_Video_Channels__For_Transmit_Local_Video(TLegTrn* Lt, BaseExchangeBlock* bb, TSessionChannelCollect& sc)
{
if(Sip->ucs)
  {
  if(bb->vcpar)
    {
    Sip->ucs->Create_RTP_PairCh(VIDEO_MPT, &sc.uc_video, NULL, Lt, 1, 1, bb);
    Sip->ucs->Create_RTP_PairCh(RTP_VIDEO_MPT, &sc.uc_rtp_video, &sc.uc_rtcp_video, Lt, -1, -1, bb);
    #ifdef Client_Test_Block
    Connect_Media_Channels_Test(sc);
    #else
    Connect_Media_Channels(sc);
    #endif
    if(sc.uc_video)
      Form4->ins_vcl(sc.uc_video->getChId());   //Local Video
    }
  }
}
//----------------------------------------------------------------------------
void __fastcall TSipUserAgentThread::Create_Video_Channels__For_Receive_Remote_Video(TLegTrn* Lt, BaseExchangeBlock* bb, TSessionChannelCollect& sc)
{
if(Sip->ucs)
  {
  Sip->ucs->Create_RTP_PairCh(VIDEO_MPT, &sc.uc_video, NULL, Lt, 1, 1, bb);
  Sip->ucs->Create_RTP_PairCh(RTP_VIDEO_MPT, &sc.uc_rtp_video, &sc.uc_rtcp_video, Lt, -1, -1, bb);
  #ifdef Client_Test_Block
  Connect_Media_Channels_Test(sc);
  #else
  Connect_Media_Channels(sc);
  #endif
  }       //Screen for remote video prepaid  activate_Remote_Video_OnReInvite_Recv_With_Add_Video()
}
//------------------------------------------------------------------------------
void __fastcall TSipUserAgentThread::Connect_Media_Channels(TSessionChannelCollect& sc)
{
if(sc.uc_sound)
   sc.uc_sound->Connect(sc.uc_rtp_audio);
if(sc.uc_rtp_audio)
   sc.uc_rtp_audio->Connect(sc.uc_sound);
if(sc.uc_video)
   sc.uc_video->Connect(sc.uc_rtp_video);
if(sc.uc_rtp_video)
   sc.uc_rtp_video->Connect(sc.uc_video);
#ifdef RTP_Print_All_Connections_On_Connect
if(sc.uc_sound)
   sc.uc_sound->printAllMyConnections();
if(sc.uc_rtp_audio)
   sc.uc_rtp_audio->printAllMyConnections();
if(sc.uc_video)
   sc.uc_video->printAllMyConnections();
if(sc.uc_rtp_video)
   sc.uc_rtp_video->printAllMyConnections();
#endif
}
//----------------------------------------------------------------------------
#ifdef Client_Test_Block
void __fastcall TSipUserAgentThread::Connect_Media_Channels_Test(TSessionChannelCollect& sc)
{
if(sc.uc_sound)
   sc.uc_sound->Connect(sc.uc_rtp_audio);
if(sc.uc_rtp_audio)
   sc.uc_rtp_audio->Connect(sc.uc_sound);
if(sc.uc_video)
  {
  if(!sc.uc_rtp_video->test_block.remote_video_rtp_loop)
      sc.uc_video->Connect(sc.uc_rtp_video);
  }
if(sc.uc_rtp_video)
  {
  if(sc.uc_rtp_video->test_block.remote_video_rtp_loop)
    sc.uc_rtp_video->Connect(sc.uc_rtp_video);
  else
    sc.uc_rtp_video->Connect(sc.uc_video);
  }
#ifdef RTP_Print_All_Connections_On_Connect
if(sc.uc_sound)
   sc.uc_sound->printAllMyConnections();
if(sc.uc_rtp_audio)
   sc.uc_rtp_audio->printAllMyConnections();
if(sc.uc_video)
   sc.uc_video->printAllMyConnections();
if(sc.uc_rtp_video)
   sc.uc_rtp_video->printAllMyConnections();
#endif
}
#endif
//-----------------------------------------------------------------------------
// -- Used on SPS_INVITE_REQ only ---------------------------------------------
//-----------------------------------------------------------------------------
void __fastcall TSipUserAgentThread::Create_Media_Session(TOutputSipBuf* ospb, TSessionChannelCollect& sc)
{
TMediaSession* ms = new TMediaSession(eltp, Sip, ospb->calledname, Lt_Out);
if(ms)
  {
  ms->set_source_of_outgoing_call(ospb->source_of_call);   //1 - при вызове от параллельного телефона
  ms->setCallID(ospb->CallID);
  ms->set_contact_uri(ospb->RequestUri);  //Если понадобится переадресация из разговора
  ms->set_display_username(ospb->cld_DisplayName);
  ms->channels_Add(sc.uc_sound);
  ms->channels_Add(sc.uc_video);
  ms->channels_Add(sc.uc_rtp_audio);
  ms->channels_Add(sc.uc_rtcp_audio);
  ms->channels_Add(sc.uc_rtp_video);
  ms->channels_Add(sc.uc_rtcp_video);
  ms->setCallTag(ospb->get_tag());      //calltag == Call_Panel->tag
  if(ospb->vcpar)
     ms->set_transmit_video(true);
  #ifdef RTP_Print_Session_On_Create
  ms->printCreateSession();
  #endif
  Sip->sss->InsMsOut_by_Callid(ospb->CallID,ms);
  }
}
//----------------------------------------------------------------------------
//---- Media session for Parallel_Phone --------------------------------------
//----------------------------------------------------------------------------
void __fastcall TSipUserAgentThread::Create_Media_Session_To_PPH(TOutputSipBuf* ospb,TSessionChannelCollect& sc)
{
TMediaSession* ms = new TMediaSession(eltp, Sip, ospb->calledname, Lt_Out);
if(ms)
  {
  ms->set_ms_parallel_phone(true);
  ms->set_ms_parallel_phone_state(1); // state - outseized;
  ms->setCallID(ospb->CallID);
  ms->set_contact_uri(ospb->RequestUri);  //Если понадобится переадресация из разговора
  ms->channels_Add(sc.uc_rtp_audio);
  ms->channels_Add(sc.uc_rtcp_audio);
  Sip->sss->InsMsOut_by_Callid(ospb->CallID,ms);
  }
}
//----------------------------------------------------------------------------
void __fastcall TSipUserAgentThread::Update_Media_Session(TOutputSipBuf* ospb,TSessionChannelCollect& sc)
{
TMediaSession* ms =  Sip->sss->GetMs_by_In_Out_Callid(ospb->callid);
if(ms)
  {
  ms->channels_Add(sc.uc_sound);
  ms->channels_Add(sc.uc_video);
  ms->channels_Add(sc.uc_rtp_audio);
  ms->channels_Add(sc.uc_rtcp_audio);
  ms->channels_Add(sc.uc_rtp_video);
  ms->channels_Add(sc.uc_rtcp_video);
  }
}
//----------------------------------------------------------------------------
void __fastcall TSipUserAgentThread::Update_Media_Session__On_Add_Video(const string& callid,TSessionChannelCollect& sc)
{
TMediaSession* ms = NULL;
if(uatt == SipUAThreadType_UAC)
   ms = Sip->sss->GetMsOut_by_Callid(callid);
else if(uatt == SipUAThreadType_UAS)
   ms = Sip->sss->GetMsIn_by_Callid(callid);
if(ms)
  {
  ms->channels_Add(sc.uc_video);
  ms->channels_Add(sc.uc_rtp_video);
  ms->channels_Add(sc.uc_rtcp_video);
  }
}
//-----------------------------------------------------------------------------
void __fastcall TSipUserAgentThread::Create_Media_Session__OnFileTransfer(TOutputSipBuf* ospb)
{
TMediaSession* ms = new TMediaSession(eltp, Sip, ospb->calledname, Lt_Out);
if(ms)
  {
  ms->setCallID(ospb->CallID);
  ms->setCallTag(ospb->get_tag());      //calltag == Call_Panel->tag
  #ifdef RTP_Print_Session_On_Create
  ms->printCreateSession();
  #endif
  Sip->sss->InsMsOut_by_Callid(ospb->CallID,ms);
  }
}
//----------------------------------------------------------------------------
void __fastcall TSipUserAgentThread::InitMediaSession(TLegTrn* Lt, TOutputSipBuf* ospb, int req_resend)
{
TSessionChannelCollect sc;
Create_Media_Channels(Lt,ospb,sc);
switch(ospb->getsls()){
      case SPS_INVITE_REQ:{
           prepare_INVITE_Final(ospb, sc.uc_rtp_audio, sc.uc_rtp_video);
           Lt->addrreqline  = ospb->requestline;
           Lt->state        = ospb->getsls();
           Lt->remoteip     = ospb->ToIP;
           Lt->remoteport   = ospb->ToPort;
           Lt->mytag        = ospb->FromTag;
           Lt->to           = ospb->To;
           Lt->from         = ospb->from;
           Lt->Current_CSeq = ospb->curr_cseq;
           Lt->call_id.setprimcallid(ospb->CallID);
           Lt->out_Contact             = ospb->Contact;
           Lt->out_sdp.content_type    = ospb->contenttype;
           Lt->ReferredBy              = ospb->ReferredBy;
           Lt->Replaces                = ospb->Replaces;
           Lt->Referred_CallID         = ospb->Referred_CallID;
           Lt->source_of_outgoing_call = ospb->source_of_call;   //0 - Вызов осуществлен от GUI приложения, 1 - от параллельного телефона
           Lt->pph_call_id             = ospb->source_callid;
           Lt->out_sdp.content_length  = ospb->ContentLength;
           Lt->out_sdp.Sdp             = ospb->sdp.Sdp;
           insertLegTrn(ospb->CallID,Lt);
           Create_Media_Session(ospb,sc);
           Sip->ins_CLD_tc(ospb->calledname,ospb->CallID);
           break;
           }
      case SPS_ANSWER_REQ:{
           prepare_ANSWER_Final(Lt,ospb, sc.uc_rtp_audio, sc.uc_rtp_video);
           Lt->out_Contact            = ospb->Contact;
           Lt->out_sdp.content_type   = ospb->contenttype;
           Lt->out_sdp.content_length = ospb->ContentLength;
           Lt->out_sdp.Sdp            = ospb->sdp.Sdp;
           Update_Media_Session(ospb,sc);
           break;
           }
      }
if(req_resend)
   InitResendProc(ospb,Lt);
}
//------------------------------------------------------------------------------
void __fastcall TSipUserAgentThread::InitMediaSession_To_PPH(TLegTrn* Lt, TOutputSipBuf* ospb)
{
TSessionChannelCollect sc;
if(Sip->ucs)
   Sip->ucs->Create_RTP_PairCh(RTP_AUDIO_MPT, &sc.uc_rtp_audio, &sc.uc_rtcp_audio,Lt,-1,-1,ospb);//rpp.RemoteHost_1,rpp.RemotePort_1,
//modify Sdp and Sdp Length
queue<string> qs;
dissect_sdp_str(qs, ospb->sdp.Sdp);
dissect_filter(qs, sc.uc_rtp_audio);
ospb->sdp.Sdp = "v=" + ospb->sdp.SdpVersion + crlf +
"o=" + ospb->sdp.Owner_UserName + ospb->sdp.SessionID + ospb->sdp.SessionVersion  + ospb->sdp.Owner_NeworkType +
ospb->sdp.Owner_AddressType + ospb->sdp.Owner_Address + crlf + //Owner
"s=" + ospb->sdp.SessionName + crlf +
"c=" + ospb->sdp.Connection_NetworkType + ospb->sdp.Connection_AddressType + ospb->sdp.common_connection_addr + crlf + //Connection
"t=" + ospb->sdp.Session_StartTime + ospb->sdp.Session_StopTime  + crlf;
while(!qs.empty())
     {
     string s = qs.front();
     qs.pop();
     ospb->sdp.Sdp += s;
     }
prepareContentLength(ospb);
Lt->lt_parallel_phone = true;   //!!!
if(ospb->primary_call_direction_pph == 0)
   Lt->primary_legtype_pph = Lt_In;
else if(ospb->primary_call_direction_pph == 1)
   Lt->primary_legtype_pph = Lt_Out;
Lt->lt_parallel_phone_primary_call_id = ospb->parallel_phone_call_id;
Lt->addrreqline  = ospb->requestline;
Lt->state        = ospb->getsls();
Lt->remoteip     = ospb->ToIP;
Lt->remoteport   = ospb->ToPort;
Lt->mytag        = ospb->FromTag;
Lt->to           = ospb->To;
Lt->from         = ospb->from;
Lt->Current_CSeq = ospb->curr_cseq;
Lt->call_id.setprimcallid(ospb->CallID);
Lt->out_Contact            = ospb->Contact;
Lt->out_sdp.content_type   = ospb->contenttype;
Lt->ReferredBy             = ospb->ReferredBy;
Lt->Replaces               = ospb->Replaces;
Lt->Referred_CallID        = ospb->Referred_CallID;
Lt->out_sdp.content_length = ospb->ContentLength;
Lt->out_sdp.Sdp            = ospb->sdp.Sdp;
insertLegTrn(ospb->CallID,Lt);
Create_Media_Session_To_PPH(ospb,sc);              //!!! Do Not Set Sip->ins_CLD_tc(ospb->calledname,ospb->CallID);

ospb->s = "INVITE"  + WS + ospb->requestline +
ospb->via           +
ospb->maxforwards   +
ospb->Contact       +
ospb->To            +
ospb->from          +
ospb->callid        +
ospb->cseq          +
ospb->allow         +
ospb->contenttype   +
ospb->UserAgent     +
ospb->ReferredBy    +
ospb->Replaces      +
ospb->ContentLength +
ospb->sdp.Sdp;
}
//------------------------------------------------------------------------------
//--- Оставить только "m=" and "a=" --------------------------------------------
//------------------------------------------------------------------------------
void __fastcall TSipUserAgentThread::dissect_filter(queue<string>& qs, TUdpChannel* uc_rtp_audio)
{
queue<string> tqs;
while(!qs.empty())
     {
     string s = qs.front();
     qs.pop();
     if(s.find("m=") != -1)
       {
       replace_audio_rtp_port_pph(s,uc_rtp_audio);
       tqs.push(s);
       continue;
       }
     if(s.find("a=") != -1)
       {
       tqs.push(s);
       continue;
       }
     }
qs = tqs;
}
//------------------------------------------------------------------------------
void __fastcall TSipUserAgentThread::replace_audio_rtp_port_pph(string& s,TUdpChannel* uc)
{
if(uc)
  {
  string s1,s2;
  int st  = s.find("audio");
  if(st != -1)
    {
    st += 5;
    st = s.find_first_of("1234567890",st);
    if(st != -1)
      {
      s1 = s.substr(0,st);
      int en = s.find(WS,st);
      if(en != -1)
        {
        s2 = s.substr(en);
        s = s1 + inttostr(uc->localport) + s2;
        }
      }
    }
  }
}
//------------------------------------------------------------------------------
void __fastcall TSipUserAgentThread::InitMediaSession_FileTransfer(TLegTrn* Lt, TOutputSipBuf* ospb)
{
prepare_INVITE_Final(ospb,NULL,NULL);
Lt->addrreqline  = ospb->requestline;
Lt->state        = ospb->getsls();
Lt->remoteip     = ospb->ToIP;
Lt->remoteport   = ospb->ToPort;
Lt->mytag        = ospb->FromTag;
Lt->to           = ospb->To;
Lt->from         = ospb->from;
Lt->Current_CSeq = ospb->curr_cseq;
Lt->call_id.setprimcallid(ospb->CallID);
Lt->out_sdp.content_type   = ospb->contenttype;
Lt->out_sdp.content_length = ospb->ContentLength;
Lt->out_sdp.Sdp            = ospb->sdp.Sdp;
insertLegTrn(ospb->CallID,Lt);
Create_Media_Session__OnFileTransfer(ospb);
InitResendProc(ospb,Lt);
}
//------------------------------------------------------------------------------
void __fastcall TSipUserAgentThread::InitMediaSession_ScreenSharing(TLegTrn* Lt, TOutputSipBuf* ospb)
{
prepare_INVITE_Final_For_ScreenSharing(ospb);
Lt->addrreqline  = ospb->requestline;
Lt->state        = ospb->getsls();
Lt->remoteip     = ospb->ToIP;
Lt->remoteport   = ospb->ToPort;
Lt->mytag        = ospb->FromTag;
Lt->to           = ospb->To;
Lt->from         = ospb->from;
Lt->Current_CSeq = ospb->curr_cseq;
Lt->call_id.setprimcallid(ospb->CallID);
Lt->out_sdp.content_type   = ospb->contenttype;
Lt->out_sdp.content_length = ospb->ContentLength;
Lt->out_sdp.Sdp            = ospb->sdp.Sdp;
Lt->resp         = SPS_INVITE200OK_RCVD;  //Чтобы не было проблем при DiscOut с выбором BYE или CANCEL
insertLegTrn(ospb->CallID,Lt);
//Create_Media_Session__OnScreenSharing(ospb);  //Create_Media_Session__OnFileTransfer(ospb);
InitResendProc(ospb,Lt);
}
//------------------------------------------------------------------------------
string __fastcall TSipUserAgentThread::get_user_name(const string& s)
{
string rv;
int st = s.find("sip:");
if(st != -1)
  {
  int en = s.find("@",st);
  st += 4;
  if(st < en)
     rv = s.substr(st,en-st);
  }
return rv;
}
//------------------------------------------------------------------------------
int __fastcall TSipUserAgentThread::get_expires_value(TSipParsBuf* spb)
{
int rv = 0;
int st = spb->Expires.find("Expires:");
if(st != -1)
  {
  st += 9;   //Expires: + " "
  int en = spb->Expires.rfind(crlf);
  if(st < en)
     rv = strtoint(spb->Expires.substr(st,en-st));
  }
return rv;
}
//----------------------------------------------------------------------------
int __fastcall TSipUserAgentThread::get_cseq(TSipParsBuf* spb)
{
int rv = 0;
int st = spb->CSeq.find("CSeq:");
if(st != -1)
  {
  st += 5; //CSeq: + " "
  int en = spb->CSeq.rfind(WS);
  if(st < en)
     rv = strtoint(spb->CSeq.substr(st,en-st));
  }
return rv;
}
//----------------------------------------------------------------------------
void __fastcall TSipUserAgentThread::findCallingParty_ByContactHeader(TSipParsBuf* spb)
{
int st = spb->Contact.find("sip:");
if(st!=-1)
  {
  int en = spb->Contact.find("@",st);
  if(en!=-1)
    {
    st+=4;
    if(st < en)
        spb->callingParty = spb->Contact.substr(st,en-st);
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TSipUserAgentThread::prepare_INVITE_Sdp_OnHold_OR_Resume(int type, TSdp& Sdp)
{
vector<string> v;
pars_sdp_string(v, Sdp.Sdp);
prepare_INVITE_sdp_on_reinvite(type, Sdp, v);
compile_sdp_string(v, Sdp.Sdp);
}
//---------------------------------------------------------------------------
void __fastcall TSipUserAgentThread::prepare_200OK_Sdp_On_REINVITE(int type, string& sdp)
{
vector<string> v;
pars_sdp_string(v, sdp);
prepare_200ok_sdp_on_reinvite(type, v);
compile_sdp_string(v, sdp);
}
//--------------------------------------------------------------------------
void __fastcall TSipUserAgentThread::pars_sdp_string(vector<string>& v, const string& s)
{
int st  = 0;
int len = s.length();
while(st < len)
     {
     int en = s.find(crlf,st);
     if(en != -1)
       {
       en += 2;
       string ss = s.substr(st,en-st);
       v.push_back(ss);
       }
     st = en;
     }
}
//----------------------------------------------------------------------------
void   __fastcall TSipUserAgentThread::compile_sdp_string(vector<string>& v,string& sdp)
{
sdp.clear();
vector<string>::iterator it = v.begin();
while(it != v.end())
      sdp += (*it++);
}
//----------------------------------------------------------------------------
//--- "a=" проверяем по всему списку т.к. их может быть больше одного -
//--- например аудио и видео  ------------------------------------------------
//----------------------------------------------------------------------------
void __fastcall TSipUserAgentThread::prepare_200ok_sdp_on_reinvite(int type, vector<string>& v)
{
bool OwnerCreator_Found = false;
vector<string>::iterator it = v.begin();
while(it != v.end())
     {
     if(!OwnerCreator_Found)
       if((*it).find("o=") != -1)
         {
         OwnerCreator_Found = true;
         update_OwnerCreator(it);
         it++;
         continue;
         }
     if((*it).find("a=") != -1)
       {
       switch(type){
             case 0: direction_200ok_OnHold(it);   break;
             case 1: direction_200ok_OnResume(it); break;
             }
       it++;
       continue;
       }
     it++;
     }
}
//--------------------------------------------------------------------------
void __fastcall TSipUserAgentThread::prepare_INVITE_sdp_on_reinvite(int type,TSdp& Sdp,vector<string>& v)
{
bool OwnerCreator_Found = false;
vector<string>::iterator it = v.begin();
while(it != v.end())
     {
     if(!OwnerCreator_Found)
       if((*it).find("o=") != -1)
         {
         OwnerCreator_Found = true;
         update_OwnerCreator(it);
         it++;
         continue;
         }
     if((*it).find("c=") != -1)
       {
       switch(type){
             case 0: connection_INVITE_Sdp_OnHold(it, Sdp);   break;
             case 1: connection_INVITE_Sdp_OnResume(it, Sdp); break;
             }
       it++;
       continue;
       }
     if((*it).find("a=") != -1)
       {
       switch(type){
             case 0: direction_INVITE_OnHold(it);   break;
             case 1: direction_INVITE_OnResume(it); break;
             }
       it++;
       continue;
       }
     it++;
     }
}
//--------------------------------------------------------------------------
void __fastcall TSipUserAgentThread::update_OwnerCreator(vector<string>::iterator& it)
{
string s1; // "o="
string s2; //session name
string s3;
string s4;
string s5;
int len = (*it).length();
int st  = (*it).find("o=");
if(st != -1)
  {
  int en = st + 2;
  if(en < len)
    {
    s1 = (*it).substr(st,en-st);
    st = (*it).find(WS,en);
    if(st > en)
      {
      s2 = (*it).substr(en,st-en);
      st = en + s2.length() + 1;
      if(st < len)
        {
        en = (*it).find(WS,st);
        if(en < len)
          {
          s3 = (*it).substr(st,en-st);
          st = en + 1;
          en = (*it).find(WS,st);
          if(en < len)
            {
            s4 = (*it).substr(st,en-st);
            s5 = (*it).substr(en);
            int a4 = strtoint(s4);
            (*it) = s1 + s2 + WS + s3 + WS + inttostr(++a4) + s5;
            }
          }
        }
      }
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TSipUserAgentThread::connection_INVITE_Sdp_OnHold(vector<string>::iterator& it, TSdp& Sdp)
{
string rv = (*it);
int st = rv.rfind(WS);
if(st != -1)
  {
  int en = rv.find(crlf,st);
  if(en != -1)
    if(st + 1 < en)
      Sdp.common_connection_addr = rv.substr(st + 1, en - st - 1);
  rv.resize(st);
  rv += WS + "0.0.0.0" + crlf;
  }
(*it) = rv;
}
//--------------------------------------------------------------------------
void __fastcall TSipUserAgentThread::connection_INVITE_Sdp_OnResume(vector<string>::iterator& it, TSdp& Sdp)
{
string rv = (*it);
int st = rv.rfind(WS);
if(st != -1)
  {
  rv.resize(st);
  rv += WS + Sdp.common_connection_addr + crlf;
  }
(*it) = rv;  
}
//--------------------------------------------------------------------------
void __fastcall TSipUserAgentThread::direction_INVITE_OnHold(vector<string>::iterator& it)
{
if((*it).find("a=sendrecv") != -1)
  (*it) = "a=sendonly" + crlf;
else if((*it).find("a=recvonly") != -1)
  (*it) = "a=sendonly" + crlf;
}
//--------------------------------------------------------------------------
void __fastcall TSipUserAgentThread::direction_INVITE_OnResume(vector<string>::iterator& it)
{
if((*it).find("a=sendonly") != -1)
  (*it) = "a=sendrecv" + crlf;
else if((*it).find("a=recvonly") != -1)
  (*it) = "a=sendrecv" + crlf;
}
//--------------------------------------------------------------------------
void __fastcall TSipUserAgentThread::direction_200ok_OnHold(vector<string>::iterator& it)
{
if((*it).find("a=sendrecv") != -1)
  (*it) = "a=recvonly" + crlf;
else if((*it).find("a=sendonly") != -1)
  (*it) = "a=recvonly" + crlf;
}
//---------------------------------------------------------------------------
void __fastcall TSipUserAgentThread::direction_200ok_OnResume(vector<string>::iterator& it)
{
if((*it).find("a=recvonly") != -1)
  (*it) = "a=sendrecv" + crlf;
else if((*it).find("a=sendonly") != -1)
  (*it) = "a=sendrecv" + crlf;
}
//---------------------------------------------------------------------------
TOutputSipBuf*  __fastcall TSipUserAgentThread::Prepare_200OK_OnReinvite(int type, TLegTrn* Lt, TSipParsBuf* spb)
{
TOutputSipBuf* ospb = new TOutputSipBuf();
if(ospb)
  {
  if(spb->To.find(crlf) == -1)
     spb->To += crlf;
  Sip->prepareContact(ospb);
  Sip->prepareUserAgent(ospb);
  prepare_200OK_Sdp_On_REINVITE(type, Lt->out_sdp.Sdp);
  ospb->sdp.Sdp = Lt->out_sdp.Sdp;
  prepareContentLength(ospb);
  Lt->out_sdp.content_length = ospb->ContentLength;
  
  ospb->s = SipVers + WS + "200 OK" + crlf;
  spb->ViaSt.InsertHeaders(ospb->s);ospb->s+=
  spb->From               +
  spb->To                 +
  ospb->Contact           +
  spb->CallID             +
  spb->CSeq               +
  spb->Allow              +
  spb->ContentType        +
  ospb->UserAgent         +
  ospb->ContentLength     +
  ospb->sdp.Sdp;
  }
return ospb;
}
//------------------------------------------------------------------------------
bool __fastcall TSipUserAgentThread::check_Placed_On_Hold(TSipParsBuf* spb)
{
if(!spb->sdp.Sdp.empty())
  {
  int st = spb->sdp.Sdp.find("c=");
  if(st != -1)
    {
    int en = spb->sdp.Sdp.find(crlf, st);
    if(en != -1)
      {
      st = spb->sdp.Sdp.find("0.0.0.0", st);
      if(st != -1)
        if(st < en)
           return true;
      }
    }
  st = spb->sdp.Sdp.find("a=sendonly");
  if(st != -1)
    return true;
  }
return false;
}
//------------------------------------------------------------------------------
void __fastcall TSipUserAgentThread::send_place_on_hold_or_resume_to_call_panel(TLegTrn* Lt, WM_APP_MSG_WPARAM WMW, ExchMsgType Emt)
{
if(!Lt)return;
TExchBuf* buf = new TExchBuf(WMW);
if(buf)
  {
  buf->emt    = Emt;
  buf->callid = Lt->call_id.getcallid();
  insertExchLst(buf);
::PostMessage(Sip->getMFHandle(), SIP_UA_MSG, WMW, WM_APP_MSG_LPARAM__READLIST);
  }
}
//------------------------------------------------------------------------------
void __fastcall TSipUserAgentThread::prepare_REINVITE_HEADRES(TLegTrn* Lt, TOutputSipBuf* spb)
{
Lt->prepareNextCSeq("INVITE",spb);
Sip->prepareRequestLine_INVITE(spb->calledname,spb);
Sip->prepareViaHeader(spb);
Sip->prepareMaxForwards(70,spb);
Sip->prepareAllow(spb);
Sip->prepareUserAgent(spb);

if(Lt->legtype == Lt_In)
  {
  int st = Lt->from.find("From:");
  if(st != -1)
    spb->To = "To:" + Lt->from.substr(st + 5);
  st = Lt->to.find("To:");
  if(st != -1)
    spb->from = "From:" + Lt->to.substr(st + 3);
  if(spb->from.find(";tag=") == -1)
    {
    st = spb->from.rfind(crlf);
    if(st != -1)
      spb->from.resize(st);
    spb->from += ";tag=" + Lt->mytag + crlf;
    }
  }
else if(Lt->legtype == Lt_Out)
  {
  int st = Lt->from.find("From:");
  if(st != -1)
     spb->from = "From:" + Lt->from.substr(st + 5);
  st = Lt->to.find("To:");
  if(st != -1)
    spb->To = "To:" + Lt->to.substr(st + 3);
  if(spb->To.find(";tag=") == -1)
    {
    st = spb->To.rfind(crlf);
    if(st != -1)
      spb->To.resize(st);
    spb->To += ";tag=" + Lt->remotetag + crlf;
    }
  }

spb->s = "INVITE" + WS + spb->requestline +
spb->via          +
spb->maxforwards  +
Lt->out_Contact   +
spb->To           +
spb->from         +
"Call-ID:"        + WS + spb->CallID + crlf +
spb->cseq         +
spb->allow        +
Lt->out_sdp.content_type +
spb->UserAgent;
}
//-----------------------------------------------------------------------------
void __fastcall TSipUserAgentThread::findCallingParty(TSipParsBuf* spb)
{
int st = spb->From.find("@");
if(st>0)   //nor 0 nor -1
  {
  int en = spb->From.rfind(":",st);
  if(en!=-1)
    {
    en++;
    if(en < st)
       spb->callingParty = spb->From.substr(en,st-en);
    }
  }
}
//---------------------------------------------------------------------------
string __fastcall TSipUserAgentThread::get_replaces_callid(const string& s)
{
string rv;
int len = s.length();
int st  = s.find("Replaces:");
if(st != -1)
  {
  st += 10;  //"Replaces:" + whitespace
  if(st < len)
    {
    int en = s.find(";",st);
    if(en != -1)
       rv = s.substr(st,en-st);
    }
  }
return rv;
}
//------------------------------------------------------------------------------
//--- Prepare out codec list with given supported codec list -------------------
//------------------------------------------------------------------------------
void __fastcall TSipUserAgentThread::prepare_out_audio_codec_list(TLegTrn* Lt,BaseExchangeBlock* spb)
{
TSdpMedia* ptOutSdpAudioMedia = &Lt->out_sdp.audio;
TSdpMedia* ptInSdpAudio       = &Lt->in_sdp.audio;
TSdpMedia* ptSupportedAudio   = &spb->sdp.audio;
ptOutSdpAudioMedia->codecs.clear();
ptOutSdpAudioMedia->s_remotertpip = ptInSdpAudio->s_remotertpip;
ptOutSdpAudioMedia->remotertpport = ptInSdpAudio->remotertpport;
int sz = ptSupportedAudio->codecs.size();
for(int i=0;i<sz;i++)
   {
   int codec = ptSupportedAudio->codecs[i];
   vector<int>::iterator it = ptInSdpAudio->codecs.begin();
   while(it != ptInSdpAudio->codecs.end())
        {
        if(codec == (*it++))
           ptOutSdpAudioMedia->codecs.push_back(codec);
        }
   }
}
//------------------------------------------------------------------------------
void __fastcall TSipUserAgentThread::prepare_out_video_codec_list(TLegTrn* Lt,BaseExchangeBlock* spb)
{
TSdpMedia* ptOutSdpVideoMedia = &Lt->out_sdp.video;
TSdpMedia* ptInSdpVideo       = &Lt->in_sdp.video;
TSdpMedia* ptSupportedVideo   = &spb->sdp.video;
ptOutSdpVideoMedia->codecs.clear();
ptOutSdpVideoMedia->s_remotertpip = ptInSdpVideo->s_remotertpip;
ptOutSdpVideoMedia->remotertpport = ptInSdpVideo->remotertpport;
int sz = ptSupportedVideo->codecs.size();
for(int i=0;i<sz;i++)
   {
   int codec = ptSupportedVideo->codecs[i];
   vector<int>::iterator it = ptInSdpVideo->codecs.begin();
   while(it != ptInSdpVideo->codecs.end())
        {
        if(codec == (*it++))
           ptOutSdpVideoMedia->codecs.push_back(codec);
        }
   }
}
//------------------------------------------------------------------------------
void __fastcall TSipUserAgentThread::InitMediaChannels(TLegTrn* Lt, TOutputSipBuf* ospb, TMediaSession* ms)
{
prepare_out_audio_codec_list(Lt,ospb);
Sip->sendInitial_Uas_Rtp_Sequence(RTP_AUDIO_MPT,Lt);
#ifdef SIP_Video
if(Lt->in_sdp.video.remotertpport != -1)
  {
  prepare_out_video_codec_list(Lt,ospb);
  Sip->sendInitial_Uas_Rtp_Sequence(RTP_VIDEO_MPT,Lt);
  }
#endif
TUdpChannel* uc = ms->getSoundChannel();
if(uc)
  {
   if(uc->wopt)
      {
      TRemoteMedia rm;
      rm.audio_codecs = Lt->in_sdp.audio.codecs;
      uc->wopt->startReceivingVoice(&rm);
      }
   if(uc->mic)
      uc->mic->startSendingVoice();
  }
}
//-----------------------------------------------------------------------------------
//-- CallPanel_A - это абонентн А вызываес секретаря и просит соединить с абонентом С
//-- CallPanel_В - это секретарь звонит абоненту В и затем соединяет с абонентом С
//----------------------------------------------------------------------------------
void __fastcall TSipUserAgentThread::Refresh_CallPanel_A_B_On_Refer(TMediaSession* ms, TSipParsBuf* spb, const string& referred_by)
{
TExchBuf* buf = new TExchBuf(WM_APP_MSG_WPARAM__UAS);
if(buf)
  {
  buf->emt   = ExchMsgType_RCVD_INVITE_ON_CALL_TRANSFER;
  buf->tag   = ms->getCallTag();
  buf->msg   = spb->callingParty;
  buf->msg_1 = referred_by;
  insertExchLst(buf);
  ::PostMessage(Sip->getMFHandle(), SIP_UA_MSG, WM_APP_MSG_WPARAM__UAS, WM_APP_MSG_LPARAM__READLIST);
  }
}
//------------------------------------------------------------------------------
void __fastcall TSipUserAgentThread::Refresh_CallPanel_C_On_Refer_200OK(TMediaSession* ms, TSipParsBuf* spb, const string& refer_to_name, const string& referred_by)
{
TExchBuf* buf = new TExchBuf(WM_APP_MSG_WPARAM__UAC);
if(buf)
  {
  buf->emt   = ExchMsgType_RCVD_200OK_ON_CALL_TRANSFER;
  buf->tag   = ms->getCallTag();
  buf->msg   = refer_to_name;
  buf->msg_1 = referred_by;
  insertExchLst(buf);
  ::PostMessage(Sip->getMFHandle(), SIP_UA_MSG, WM_APP_MSG_WPARAM__UAC, WM_APP_MSG_LPARAM__READLIST);
  }
}
//-------------------------------------------------------------------------------
void __fastcall TSipUserAgentThread::Proc_Rcvd_CallTransfer_INVITE(TLegTrn* Lt,TSipParsBuf* spb)
{
string referred_by     = get_user_name(spb->ReferredBy);
string referred_callid = get_replaces_callid(spb->Replaces);
TMediaSession* ms      = Sip->sss->GetMsOut_by_Callid(referred_callid);
if(!ms)
    ms = Sip->sss->GetMsIn_by_Callid(referred_callid);
if(ms)
  {
  getSDPElements_FromInMsg(Lt,spb);
  FindCryptoKeys(Lt,spb);
  findCallingParty(spb);
  Refresh_CallPanel_A_B_On_Refer(ms, spb, referred_by);
  TMediaSession* ms_new = new TMediaSession(eltp, Sip, spb->callingParty, Lt_In);
  if(ms_new)
    {
    ms_new->setCallTag(ms->getCallTag());
    ms->setCallTag(0);  //"Отстегнуть" даныую медиа-сессию от TCall_Panel
    ms->FreeSession();  //Request to MainFormSLS to EraseMediaSession and send Bye
    ms_new->setCallID(spb->call_id.getcallid());
    #ifdef RTP_Print_Session_On_Create
    ms_new->printCreateSession();
    #endif
    Sip->sss->InsMsIn_by_Callid(spb->call_id.getcallid(),ms_new);  //Зарегистрировать новую медиа сессию
    TOutputSipBuf* ospb = new TOutputSipBuf;
    if(ospb)
      {
      ospb->setsls(SPS_ANSWER_REQ);
      ospb->CallID = spb->call_id.getcallid();
      ospb->callid = in_pref + ospb->CallID;

      TSdpMediaCont smc;
      TSessionChannelCollect sc;

      Sip->generateToTag(ospb);
      Lt->mytag = ospb->totag;
      Sip->prepareContact(ospb);
      Sip->prepareAllow(ospb);
      Sip->prepareUserAgent(ospb);
      Sip->prepareContentType(ospb,"application/sdp");
      Sip->prepare_Sdp_Initial(&ospb->sdp,&smc);

      InitMediaSession(Lt, ospb, 1);
      InitMediaChannels(Lt, ospb, ms_new);

      ospb->set_req_to_delete();
      Sip->SetOutQueue(ospb);
      }   //if(ms_new)
    }
  }
}
//------------------------------------------------------------------------------
void __fastcall TSipUserAgentThread::Proc_REFER_RCVD(TSipParsBuf* spb)
{
TLegTrn* Lt = getLegTrn(spb->call_id.getcallid());
if(Lt)
  {
  Lt->BLOCK_LEG_TRN();
  send_202_Resp_OnReferRcvd(spb, Lt);
  send_First_NOTIFY_OnReferRcvd(spb, Lt, "SIP/2.0 100 Trying");
  send_INVITE_OnReferRcvd(Lt, spb);
  Lt->UN_BLOCK_LEG_TRN();
  }
}
//----------------------------------------------------------------------------
//------------- REGISTER Received from parallel phone ------------------------
//----------------------------------------------------------------------------
void __fastcall TSipUserAgentThread::Proc_REGISTER_RCVD(TSipParsBuf* spb)
{
if(spb->parallel_phone)
  {
  TLegTrn* Lt = getLegTrn(spb->call_id.getcallid());
  if(Lt)
    {
    Lt->BLOCK_LEG_TRN();
    if(Lt->cseqrcvd == spb->CSeq)
      {
      Lt->UN_BLOCK_LEG_TRN();
      return;  //resend Invite received
      }
    Lt->UN_BLOCK_LEG_TRN();
    }
  else
    {
    Lt = new TLegTrn(Lt_In);
    if(Lt)
      {
      if(!insertLegTrn(spb->call_id.getcallid(),Lt))
        {
        delete Lt;
        return;
        }
      }
    }
  if(Lt)
    {
    Lt->BLOCK_LEG_TRN();
    TExchBuf* buf = new TExchBuf(WM_APP_MSG_WPARAM__UAS);
    if(buf)
      {
      findCallingParty(spb);
      buf->emt = ExchMsgType_REGISTER;
      buf->setAddBuf(spb);
      spb->incReferenceCount();
      insertExchLst(buf);
      ::PostMessage(Sip->getMFHandle(), SIP_UA_MSG, WM_APP_MSG_WPARAM__UAS, WM_APP_MSG_LPARAM__READLIST);
      }
    Lt->UN_BLOCK_LEG_TRN();
    } //if(Lt)
  } //if(spb->parallel_phone)
}
//----------------------------------------------------------------------------
void __fastcall TSipUserAgentThread::send_202_Resp_OnReferRcvd(TSipParsBuf* spb,TLegTrn* Lt)
{
TOutputSipBuf* ospb = new TOutputSipBuf;
if(ospb)
  {
  ospb->ToIP   = spb->FromIP;
  ospb->ToPort = spb->FromPort;
 // ospb->CallID = spb->call_id.getcallid();
  Sip->prepareContact(ospb);
  Sip->prepareUserAgent(ospb);
  Sip->prepareContentLength_0(ospb);

  ospb->s = SipVers + WS + "202" + WS + "Accepted" + crlf;
  spb->ViaSt.InsertHeaders(ospb->s);ospb->s +=
  ospb->Contact   +
  spb->To         +
  spb->From       +
  spb->CallID     +
  spb->CSeq       +
  "Expires:"      + WS + "60" + crlf +
  ospb->UserAgent +
  ospb->ContentLength;

  ospb->set_req_to_delete();
  Sip->SetOutQueue(ospb);
  }
}
//---------------------------------------------------------------------------------------------
//--- Это первый NOTIFY в процедре REFER - NOTIFY - как правило с "sipfrag SIP/2.0 100 Trying".
//--- последующие NOTIFY идут с использованием Lt->ReferNOTIFY  -------------------------------
//---------------------------------------------------------------------------------------------
void __fastcall TSipUserAgentThread::send_First_NOTIFY_OnReferRcvd(TSipParsBuf* spb, TLegTrn* Lt, const string& sipfrag)
{
TOutputSipBuf* ospb = new TOutputSipBuf;
if(ospb)
  {
  ospb->ToIP   = spb->FromIP;
  ospb->ToPort = spb->FromPort;
  prepareReqLine_FromReceivedContactHeader(ospb,"NOTIFY",spb);
  Sip->Prepare_Via_Header_With_Branch(ospb);
  Sip->prepareContact(ospb);
  prepare_To_ForOutRequest_FromInRequest(ospb,spb);
  prepare_From_ForOutRequest_FromInRequest(ospb,spb);
  ospb->CallID = spb->CallID;
  Sip->prepareUserAgent(ospb);
  ospb->sdp.Sdp = sipfrag + sdpboundary;
  prepareContentLength(ospb);

  save_NOTIFY_parameters(Lt, ospb);  //Необходимо для формирования последующих NOTIFY сообщений

  ospb->s = ospb->requestline +
  ospb->via                   +
  "Max-Forwards:"             + WS   + "70" + crlf +
  ospb->Contact               +
  ospb->To                    +
  ospb->from                  +
  ospb->CallID                +
  "CSeq:"                     + WS   + inttostr(++Lt->Current_CSeq) + WS + "NOTIFY" + crlf +
  "Content-Type:"             + WS   + "message/sipfrag"   + crlf   +
  ospb->UserAgent             +
  "Subscription-State:"       + WS   + "active;expires=56" + crlf   +
  "Event:"                    + WS   + "refer"             + crlf   +
  ospb->ContentLength         +
  ospb->sdp.Sdp;

  ospb->set_req_to_delete();
  Sip->SetOutQueue(ospb);
  }
}
//------------------------------------------------------------------------------
void __fastcall TSipUserAgentThread::send_Next_NOTIFY_AfterReferRcvd(TLegTrn* Lt, const string& sipfrag, const string& subscription_state)
{
TOutputSipBuf* ospb = new TOutputSipBuf;
if(ospb)
 if(Lt->ReferNOTIFY)
   {
   ospb->ToIP        = Lt->ReferNOTIFY->ToIP;
   ospb->ToPort      = Lt->ReferNOTIFY->ToPort;
   ospb->requestline = Lt->ReferNOTIFY->RequestLine;
   ospb->Contact     = Lt->ReferNOTIFY->Contact;
   ospb->To          = Lt->ReferNOTIFY->To;
   ospb->from        = Lt->ReferNOTIFY->From;
   ospb->CallID      = Lt->ReferNOTIFY->CallID;
   Sip->Prepare_Via_Header_With_Branch(ospb);
   Sip->prepareUserAgent(ospb);
   ospb->sdp.Sdp     = sipfrag + sdpboundary;
   prepareContentLength(ospb);

   ospb->s = ospb->requestline +
   ospb->via                   +
   "Max-Forwards:"             + WS   + "70" + crlf +
   ospb->Contact               +
   ospb->To                    +
   ospb->from                  +
   ospb->CallID                +
   "CSeq:"                     + WS   + inttostr(++Lt->Current_CSeq) + WS + "NOTIFY" + crlf +
   "Content-Type:"             + WS   + "message/sipfrag"   + crlf   +
   ospb->UserAgent             +
   "Subscription-State:"       + WS   + subscription_state  + crlf   +
   "Event:"                    + WS   + "refer"             + crlf   +
   ospb->ContentLength         +
   ospb->sdp.Sdp;

   ospb->set_req_to_delete();
   Sip->SetOutQueue(ospb);
   }
}
//------------------------------------------------------------------------------
void __fastcall TSipUserAgentThread::save_NOTIFY_parameters(TLegTrn* Lt, TOutputSipBuf* ospb)
{
if(!Lt->ReferNOTIFY)
    Lt->ReferNOTIFY = new TReferNOTIFY;
if(Lt->ReferNOTIFY)
  {
  Lt->ReferNOTIFY->ToIP        = ospb->ToIP;
  Lt->ReferNOTIFY->ToPort      = ospb->ToPort;
  Lt->ReferNOTIFY->RequestLine = ospb->requestline;;
  Lt->ReferNOTIFY->Contact     = ospb->Contact;
  Lt->ReferNOTIFY->To          = ospb->To;
  Lt->ReferNOTIFY->From        = ospb->from;
  Lt->ReferNOTIFY->CallID      = ospb->CallID; 
  }
}
//------------------------------------------------------------------------------
void __fastcall TSipUserAgentThread::prepareReqLine_FromReceivedContactHeader(TOutputSipBuf* ospb, const string& MSG, TSipParsBuf* spb)
{
int len = spb->Contact.length();
int st  = spb->Contact.find("<");
if(st != -1)
  {
  st++;
  if(st < len)
    {
    int en = spb->Contact.rfind(">");
    if(en > st)
       ospb->requestline = MSG + WS + spb->Contact.substr(st,en-st) + WS + SipVers + crlf;
    }
  }
}
//------------------------------------------------------------------------------
void __fastcall TSipUserAgentThread::prepare_To_ForOutRequest_FromInRequest(TOutputSipBuf* ospb,TSipParsBuf* spb)
{
int len = spb->From.length();
int st  = spb->From.find("From:");
if(st != -1)
  {
  st += 5;
  if(st < len)
     ospb->To = "To:" + spb->From.substr(st);
  }
}
//-------------------------------------------------------------------------------
void __fastcall TSipUserAgentThread::prepare_From_ForOutRequest_FromInRequest(TOutputSipBuf* ospb,TSipParsBuf* spb)
{
int len = spb->To.length();
int st  = spb->To.find("To:");
if(st != -1)
  {
  st += 3;
  if(st < len)
     ospb->from = "From:" + spb->To.substr(st);
  }
}
//-------------------------------------------------------------------------------
void __fastcall TSipUserAgentThread::get_refer_to_parameters(TReferToPar& rp, const string& s)
{
int len = s.length();
int st  = s.find("<");
if(st != -1)
  {
  st++;
  if(st < len)
    {
    int en = s.find("?",st);
    if(st < en)
      {
      rp.refer_to = s.substr(st,en-st);
      if(st < len)
        {
        st = s.find("Replaces=",st);
        if(st != -1)
          {
          st += 9;
          if(st < len)
            {
            en = s.find("%3B",st);
            if(st < en)
              {
              rp.replaces = s.substr(st,en-st);
              st = en;
              st = s.find("to-tag%3D",st);
              if(st != -1)
                {
                st += 9;
                if(st < len)
                  {
                  en = s.find("%3B",st);
                  if(st < en)
                    {
                    rp.to_tag = s.substr(st,en-st);
                    st = en;
                    st = s.find("from-tag%3D",st);
                    if(st != -1)
                      {
                      st += 11;
                      if(st < len)
                        {
                        rp.from_tag = s.substr(st);
                        st = rp.from_tag.rfind(crlf);
                        if(st != -1)
                           rp.from_tag.resize(st);
                        st = rp.from_tag.rfind(">");
                        if(st != -1)
                           rp.from_tag.resize(st);
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    else
      {
      en = s.find(">",st);
      if(st < en)
        rp.refer_to = s.substr(st,en-st);
      }
    }
  }
if(!rp.replaces.empty())
  {
  string s1,s2;
  len = rp.replaces.length();
  st  = rp.replaces.find("%40");
  if(st != -1)
    {
    s1 = rp.replaces.substr(0,st);
    st += 3;
    if(st < len)
      {
      s2 = rp.replaces.substr(st);
      rp.replaces = s1 + "@" + s2;
      }
    }
  }
}
//-------------------------------------------------------------------------------
void __fastcall TSipUserAgentThread::send_INVITE_OnReferRcvd(TLegTrn* Lt,TSipParsBuf* spb)
{
TOutputSipBuf* ospb = new TOutputSipBuf;
if(ospb)
  {
  ospb->Referred_CallID = Lt->call_id.getcallid(); //fot NOTIFY sending on reveive INVITE_200OK
  TSdpMediaCont smc;
  TReferToPar rp;
  get_refer_to_parameters(rp,spb->ReferTo);

  ospb->setsls(SPS_INVITE_REQ);
  ospb->ToIP   = Sip->SipProxy.IPAddr;
  ospb->ToPort = Sip->SipProxy.Port;
  Sip->generateFromTag(ospb);
  Sip->generateCallID(ospb);
  ospb->requestline = rp.refer_to + WS + SipVers + crlf;
  ospb->ReferredBy  = spb->ReferredBy;
  if(!rp.replaces.empty())
    {
    ospb->Replaces = "Replaces:" + WS + rp.replaces;
    if(!rp.to_tag.empty())
        ospb->Replaces += ";to-tag="   + rp.to_tag;
    if(!rp.from_tag.empty())
        ospb->Replaces += ";from-tag=" + rp.from_tag;
    ospb->Replaces += crlf;
    }
  Sip->Prepare_Via_Header_With_Branch(ospb);
  Sip->prepareMaxForwards(70,ospb);
  Sip->prepareContact(ospb);
  ospb->To = "To:" + WS + "<" + rp.refer_to + ">" + crlf;
  Sip->prepareFrom_COMMON(ospb,&Sip->Account,true);
  Sip->prepareCallID_INVITE(ospb);
  Sip->prepareCSeq(1,"INVITE",ospb);
  Sip->prepareAllow(ospb);
  Sip->prepareContentType(ospb,"application/sdp");
  Sip->prepareUserAgent(ospb);
  Sip->prepare_Sdp_Initial(&ospb->sdp,&smc);
  if(Sip->uac)
    {
    Sip->uac->setQueue(ospb);
    Sip->updateSentQueue_1(ospb);
    }
  }
}
//------------------------------------------------------------------------------
//--- Если 603 responce приходит на SUBSCRIBE это говорит о том что нет ни одного
//--- коннекта от абонента к которому инициирцется подписка. Данный responce
//--- приходит от сервера. Случай, когда 603 приходит от клиента в данный момент
//--- не рассматривается.
//------------------------------------------------------------------------------
void __fastcall TSipUserAgentThread::Proc_603_Resp(TLegTrn* Lt,TSipParsBuf* spb)
{
if(spb->CSeq.find("SUBSCRIBE") != -1)
  {
  TEventLogThread* elt = getLog();
  if(elt){
    string s = "\nProc_603_Resp: delete subscription to " + Lt->ac_user_name;
    elt->FputEvt(s);
    }
  Sip->Contacts.set_contact_state(Lt->ac_user_name, ClientState_Off_Line);  //Subscription declined
  Sip->Contacts.AS.del_subscribed_contact(Lt->ac_user_name);
::PostMessage(Sip->getMFHandle(),SIP_UA_MSG,WM_APP_MSG_WPARAM__UAC,WM_APP_MSG_LPARAM__CONTACT_LIST_REFRESH); //DrawGrid1->Repaint()
  }
return;
}
//-------------------------------------------------------------------------------
void __fastcall TSipUserAgentThread::ProcRespCommon(TLegTrn* Lt,TSipParsBuf* spb)
{
if(spb->iStatus == 488)
   return;
spb->ToIP   = spb->FromIP;
spb->ToPort = spb->FromPort;
PrepareReqURIFromToHeader(spb);
if(!Lt)
  {
  /*
  PrepareCommonOutACK(NULL,spb);
  setQueue(spb);
  */
  return;
  }
PrepareCommonOutACK(Lt,spb);
if(Lt->lt_parallel_phone)
  {
   if(MainFormSLS->PPS->sst_pph)
      MainFormSLS->PPS->sst_pph->setQueue(spb);
  }
else
  setQueue(spb);
}
//------------------------------------------------------------------------------
void  __fastcall TSipUserAgentThread::PrepareReqURIFromToHeader(TSipParsBuf* spb)
{
int st = spb->To.find("<");
if(st == -1)return;
int en = spb->To.find(">");
if(en != -1)
  {
  int len = en - st - 1;
  if(len > 1)
     spb->ReqStatusLine = spb->To.substr(st+1,len) + WS + SipVers + crlf;
  }
}
//------------------------------------------------------------------------------
void __fastcall  TSipUserAgentThread::PrepareCommonOutACK(TLegTrn* Lt,TSipParsBuf* spb)
{
spb->sps = SPS_ACK_REQ;
int cseq = getcseq(spb);
string reqline;
ConstructReqLine(reqline,spb);  //Construct Request Line from Contact Header
if(reqline.empty())
   {
   if(Lt)
     {
     if(Lt->addrreqline.empty())
       {
       if(spb->ReqStatusLine.empty())
          return;
       spb->s = "ACK" + WS + spb->ReqStatusLine;   
       }
     else
       spb->s = "ACK" + WS + Lt->addrreqline;
     }
   else
     {
     if(spb->ReqStatusLine.empty())
        return;
     spb->s = "ACK" + WS + spb->ReqStatusLine;
     }
   }
else
   spb->s = "ACK" + WS + reqline;
spb->ViaSt.InsertHeaders(spb->s);spb->s+=
spb->To      +
spb->From    +
spb->CallID  +
"CSeq:" + WS + inttostr(cseq) + WS + "ACK" + crlf;
//if(RouteReq)
//   InsertRouteHeader(spb->Contact,s);   Do not Delete
if(Lt)
   InsertRouteHeader_1(&Lt->RecordRoute,spb->s);
spb->s+="Content-Length: 0" + sdpboundary;
}
//------------------------------------------------------------------------------
void  __fastcall TSipUserAgentThread::ConstructReqLine(string& reqline,TSipParsBuf* spb)
{
int len = spb->Contact.length();
if(!len)return;
int st = spb->Contact.find("sip:");
if(st!=-1)
  {
  int en = spb->Contact.find(">",st);
  if(en==-1)
     en=spb->Contact.find(crlf,st);
  if(en!=-1)
    if(en > st)
       reqline = spb->Contact.substr(st,en-st) + WS + SipVers + crlf;
  }
}
//------------------------------------------------------------------------------
void  __fastcall TSipUserAgentThread::InsertRouteHeader_1(TRecRouteStruct* rrs,string& s)
{
if(rrs->lst.empty())
   return;
map < int, string, less<int>, allocator<int> >::iterator it = rrs->lst.begin();
while(it!=rrs->lst.end())
     {
     string str = (*it++).second;
     int len    = str.length();
     int st = str.find(":");
     if(st!=-1)
       s+="Route" + str.substr(st,len-st);
     }
}
//------------------------------------------------------------------------------
void __fastcall TSipUserAgentThread::SendInitial_RTP_Seq(TUdpChannel* uc)
{
int sz = sdpboundary.length();
if(sz)
  if(uc)
    if(uc->sendThread)
      {
      TOutPutUdpBlock* opb = new TOutPutUdpBlock;
      if(opb)
        {
        opb->mpt = INIT_MPT; //must be deleted after use in the TSendThread
        for(int i = 0;i < sz; i++)
            opb->v.push_back(sdpboundary[i]);
        Log_PrepareInitialRtpSeq(uc,INIT_MPT);
        uc->sendThread->setQueue(opb);
        }
      }
}
//----------------------------------------------------------------------------
void __fastcall TSipUserAgentThread::SendInitial_RTCP_Seq(TUdpChannel* uc)
{
int sz = crlf.length();
if(sz)
  if(uc)
    if(uc->sendThread)
      {
      TOutPutUdpBlock* opb = new TOutPutUdpBlock;
      if(opb)
        {
        opb->mpt = INIT_RTCP_MPT; //must be deleted after use in the TSendThread
        for(int i = 0;i < sz; i++)
            opb->v.push_back(crlf[i]);
        Log_PrepareInitialRtpSeq(uc,INIT_RTCP_MPT);
        uc->sendThread->setQueue(opb);
        }
      }
}
//----------------------------------------------------------------------------
void __fastcall TSipUserAgentThread::Log_PrepareInitialRtpSeq(TUdpChannel* uc, MediaPacketType MPT)
{
TEventLogThread* elt = getLog();
if(elt)
  {
  TDateTime DateTime = DateTime.CurrentDateTime();
  string str;
  exsTime(DateTime,str);
  string s_sck = inttostr(uc->getSocket());
  str = "\n" + str + " sck " + s_sck + " ch_" + inttostr(uc->getChId());
  uc->getMediaPacketType(str);
  if(MPT == INIT_MPT)
     str += " Prepare Initial RTP Seq To Remote Addr\n";
  else if(MPT == INIT_RTCP_MPT)
     str += " Prepare Initial RTCP Seq To Remote Addr\n"; 
  elt->FputEvt(str);
  }
}
//-----------------------------------------------------------------------------
void __fastcall TSipUserAgentThread::REINVITE_ONHOLD_REQ(TOutputSipBuf* ospb)
{
TLegTrn* Lt = getLegTrn(ospb->CallID);
if(Lt)
  {
  Lt->BLOCK_LEG_TRN();
  prepare_REINVITE_HEADRES(Lt, ospb);
  prepare_INVITE_Sdp_OnHold_OR_Resume(0, Lt->out_sdp);
  ospb->sdp.Sdp = Lt->out_sdp.Sdp;
  prepareContentLength(ospb);
  Lt->out_sdp.content_length = ospb->ContentLength;
  ospb->s += ospb->ContentLength +
  ospb->sdp.Sdp;
  InitResendProc(ospb,Lt);
  Lt->UN_BLOCK_LEG_TRN();
  }
}
//------------------------------------------------------------------------------
void __fastcall TSipUserAgentThread::REINVITE_RESUME_REQ(TOutputSipBuf* ospb)
{
TLegTrn* Lt = getLegTrn(ospb->CallID);
if(Lt)
  {
  Lt->BLOCK_LEG_TRN();
  prepare_REINVITE_HEADRES(Lt, ospb);
  prepare_INVITE_Sdp_OnHold_OR_Resume(1, Lt->out_sdp);
  ospb->sdp.Sdp = Lt->out_sdp.Sdp;
  prepareContentLength(ospb);
  Lt->out_sdp.content_length = ospb->ContentLength;
  ospb->s += ospb->ContentLength +
  ospb->sdp.Sdp;
  InitResendProc(ospb,Lt);
  Lt->UN_BLOCK_LEG_TRN();
  }
}
//------------------------------------------------------------------------------
//--- If LegType == Lt_Out Lt == NULL (UacThread) ------------------------------
//--- If LegType == Lt_In  Lt != NULL (UasThread), i.e. Lt get before calling --
//--- REINVITE_WITH_ADD_VIDEO_REQ() --------------------------------------------
//------------------------------------------------------------------------------
void __fastcall TSipUserAgentThread::REINVITE_WITH_ADD_VIDEO_REQ(TOutputSipBuf* ospb,TLegTrn* Lt)
{
if(!Lt)
   Lt = getLegTrn(ospb->CallID);
if(Lt)
  {
  Lt->BLOCK_LEG_TRN();
  prepare_REINVITE_HEADRES(Lt, ospb);
  TSessionChannelCollect sc;
  Create_Video_Channels__For_Transmit_Local_Video(Lt,ospb,sc);
  if(sc.uc_rtp_video)
    {
    Update_Media_Session__On_Add_Video(ospb->CallID, sc);
    if(sc.uc_video)
      if(sc.uc_video->vscr)
         sc.uc_video->vscr->video_sending_only = true;
    if(Sip->ss_tls_t)
       PREPARE_EGRESS_SRTP_Session(sc.uc_rtp_video);
    sc.uc_rtp_video->INIT_Sdp_For_SRTP_Session(&ospb->sdp.video,uatt);
    ospb->sdp.video.localrtpport = sc.uc_rtp_video->localport;
    TSdpMediaCont smc;
    ospb->sdp.prepare_sdp_video(&smc);
    if(!ospb->sdp.video.codecs.empty())
      {
      ospb->sdp.Sdp += "m=" + ospb->sdp.video.media_type + inttostr(ospb->sdp.video.localrtpport) + WS + ospb->sdp.video.media_protocol;
      ospb->sdp.prep_final_media(ospb->sdp.video.codecs, ospb->sdp.video.crypto_keys, ospb->sdp.video.rtp_attr_list);
      Lt->out_sdp.Sdp += ospb->sdp.Sdp;
      ospb->sdp.Sdp = Lt->out_sdp.Sdp;
      prepareContentLength(ospb);
      Lt->out_sdp.content_length = ospb->ContentLength;
      ospb->s += ospb->ContentLength +
      ospb->sdp.Sdp;
      InitResendProc(ospb,Lt);
      }
    }
  Lt->UN_BLOCK_LEG_TRN();
  } //if(Lt)
}
//------------------------------------------------------------------------------
void __fastcall TSipUserAgentThread::INVITE_ON_RCV_FIRST_MIC_PACKET_REQ(TOutputSipBuf* ospb)
{
TLegTrn* Lt = getLegTrn(ospb->CallID);
if(Lt)
  {
  Lt->BLOCK_LEG_TRN();
  if(Lt->ospb_wait_first_mic_packet)
    {
    TOutputSipBuf* waiting_ospb = Lt->ospb_wait_first_mic_packet;
    Lt->ospb_wait_first_mic_packet = NULL;
    Sip->SetOutQueue(waiting_ospb);
    waiting_ospb->decReferenceCount(); //do not call updateSentQueue()
    }
  InitResendProc(ospb,Lt);  
  Lt->UN_BLOCK_LEG_TRN();  
  }
}
//------------------------------------------------------------------------------
void __fastcall TSipUserAgentThread::Proc_200OK_ON_REINVITE_WITH_ADD_VIDEO_REQ(TSipParsBuf* spb)
{
string callid = spb->call_id.getcallid();
TLegTrn* Lt   = getLegTrn(callid);
if(Lt)
  {
  Lt->BLOCK_LEG_TRN();
  TSessionChannelCollect sc;
  Create_Video_Channels__For_Receive_Remote_Video(Lt,spb,sc);
  if(Sip->ss_tls_t)
    {
    vector<string> v;
    if(Lt->request_srtp(SRTP_TYPE_VIDEO, SK_GET, v))
      {
      PREPARE_EGRESS_SRTP_Session(sc.uc_rtp_video);
      PREPARE_INGRESS_SRTP_Session(sc.uc_rtp_video,v);
      }
    }
  spb->ToIP    = Lt->remoteip;
  spb->ToPort  = Lt->remoteport;
  spb->sdp.Sdp = Lt->out_sdp.Sdp;  //out_sdp на данный момент должен содержать только "m=audio"
  prepare_Sdp_Final__for_200OK_On_Reinvite_With_Add_Video_Req(&spb->sdp, sc.uc_rtp_video);  //здесь добавляется "m=video"
  prepareContentLength(spb);
  Lt->out_sdp.content_length = spb->ContentLength;
  Lt->out_sdp.Sdp            = spb->sdp.Sdp;
  Update_Media_Session__On_Add_Video(spb->call_id.getcallid(), sc);

  spb->s = SipVers + WS + "200 OK" + crlf;
  spb->ViaSt.InsertHeaders(spb->s); spb->s +=
  spb->From;
  if(spb->To.find(crlf) == -1)
     spb->To += crlf;
  spb->s += spb->To       +
  spb->Contact            +
  spb->CallID             +
  spb->CSeq               +
  spb->Allow              +
  spb->ContentType        +
  spb->UserAgent          +
  spb->ContentLength      +
  spb->sdp.Sdp;
  Sip->SetOutQueue(spb);
  if(Lt->in_sdp.video.remotertpport != -1)
    {
    prepare_out_video_codec_list(Lt,spb);
    Sip->sendInitial_Uas_Rtp_Sequence(RTP_VIDEO_MPT,Lt);
    }
  Lt->UN_BLOCK_LEG_TRN();  
  } //if(Lt)
}
//------------------------------------------------------------------------------
//--- If LegType == Lt_Out Lt == NULL (UacThread) ------------------------------
//--- If LegType == Lt_In  Lt != NULL (UasThread), i.e. Lt get before calling --
//--- INFO_REQ() ---------------------------------------------------------------
//--- RFC Example --------------------------------------------------------------
//---    INFO sip:alice@pc33.example.com SIP/2.0
//---    Via: SIP/2.0/UDP 192.0.2.2:5060;branch=z9hG4bKnabcdef
//---    To: Bob <sip:bob@example.com>;tag=a6c85cf
//---    From: Alice <sip:alice@example.com>;tag=1928301774
//---    Call-Id: a84b4c76e66710@pc33.example.com
//---    CSeq: 314333 INFO
//---    Info-Package: foo
//---    Content-type: application/foo
//---    Content-Disposition: Info-Package
//---    Content-length: 24
//------------------------------------------------------------------------------
void __fastcall TSipUserAgentThread::INFO_REQ(TOutputSipBuf* spb, TLegTrn* Lt)
{
if(!Lt)
   Lt = getLegTrn(spb->CallID);
if(Lt)
  {
  Lt->BLOCK_LEG_TRN();
  int cseq = Lt->prepareNextCSeq("INFO",spb);
  if(spb->contenttype.find("text/plain") != -1)
    {
    int st = spb->sdp.Sdp.find("conference");
    if(st != -1)
      {
      if(spb->sdp.Sdp.find("add",st) != -1)
        {
        if(!Lt->INFO)
           Lt->INFO = new TSipInfo;
        if(Lt->INFO)
          {
          TCSeqInfo CSeqInfo;
          CSeqInfo.user_name = spb->calledname;
          Lt->INFO->Ins_CSeq_Info(cseq, CSeqInfo);
          }
        }
      }
     }
  Sip->prepareViaHeader(spb);
  if(Lt->legtype == Lt_In)
    {
    int st = Lt->from.find("From:");
    if(st != -1)
      spb->To = "To:" + Lt->from.substr(st + 5);
    st = Lt->to.find("To:");
    if(st != -1)
      spb->from = "From:" + Lt->to.substr(st + 3);
    if(spb->from.find(";tag=") == -1)
      {
      st = spb->from.rfind(crlf);
      if(st != -1)
         spb->from.resize(st);
      spb->from += ";tag=" + Lt->mytag + crlf;
      }
    }
  else if(Lt->legtype == Lt_Out)
    {
    int st = Lt->from.find("From:");
    if(st != -1)
       spb->from = "From:" + Lt->from.substr(st + 5);
    st = Lt->to.find("To:");
    if(st != -1)
       spb->To = "To:" + Lt->to.substr(st + 3);
    if(spb->To.find(";tag=") == -1)
      {
      st = spb->To.rfind(crlf);
      if(st != -1)
         spb->To.resize(st);
      spb->To += ";tag=" + Lt->remotetag + crlf;
      }
    }
  spb->s = spb->requestline +
  spb->via           +
  spb->To            +
  spb->from          +
  spb->callid        +
  spb->cseq          +
  spb->contenttype   +
  spb->ContentLength +
  spb->sdp.Sdp;
  Lt->UN_BLOCK_LEG_TRN();
  } //if(Lt)
}
//-----------------------------------------------------------------------------
void __fastcall TConfExchBlock::pars_sdp_substr(const string& src)
{
string s = src;
unsigned st  = s.rfind(crlf);
if(st != -1)
  s.resize(st);
s += ",";
st = 0;
unsigned len = s.length();
string info_type   = get_info_type(st, len, s);
user_name          = get_user_name(st, len, s);
if(info_type.find("add") == 0)
  {
  conf_evnt               = ConfEvnt_Add_Participant;
  conference_creator_exch = get_creator_participant(st, len, s);  //прмзнак - это создатель или пассивный участник конференции
  call_state              = get_call_state(st, len, s);
  }
else if(info_type.find("del") == 0)
  conf_evnt = ConfEvnt_Del_Participant;
}
//------------------------------------------------------------------------------
string __fastcall TConfExchBlock::get_info_type(unsigned& st, unsigned len, const string& s)
{
string rv;
if(st < len)
  {
  st = s.find(WS,st);
  if(st != -1)
    {
    rv = s.substr(0,st);
    st++;    //WS missing
    }
  }
return rv;
}
//------------------------------------------------------------------------------
string __fastcall TConfExchBlock::get_user_name(unsigned& st, unsigned len, const string& s)
{
string rv;
if(st < len)
  {
  unsigned en = s.find(",",st);
  if(en != -1)
     {
     rv = s.substr(st,en-st);
     st = en;
     }
  }
return rv;
}
//------------------------------------------------------------------------------
bool __fastcall TConfExchBlock::get_creator_participant(unsigned& st, unsigned len, const string& s)
{
bool rv = false;
if(st < len)
  {
  st = s.find_first_of("0123456789",st);
  if(st != -1)
    {
    unsigned en = s.find(",",st);
    if(en != -1)
      {
      string creator = s.substr(st,en-st);
      st = en;
      int a = strtoint(creator);
      if(a)
         rv = true;
      }
    }
  }
return rv;
}
//------------------------------------------------------------------------------
int __fastcall TConfExchBlock::get_call_state(unsigned& st, unsigned len, const string& s)
{
int rv = 0;
if(st < len)
  {
  st = s.find_first_of("0123456789",st);
  if(st != -1)
    {
    unsigned en = s.find(",",st);
    if(en != -1)
      {
      string c_state = s.substr(st,en-st);
      st = en;
      rv = strtoint(c_state);
      }
    }
  }
return rv;
}
//------------------------------------------------------------------------------
void __fastcall TSipUserAgentThread::Proc_INFO_RCVD(TSipParsBuf* spb, SipUAThreadType uatt)
{
if(spb->ContentType.find("text/plain") != -1)
   Proc_INFO_TEXT_PLAIN(spb,uatt);
spb->ToIP   = spb->FromIP;
spb->ToPort = spb->FromPort;
Prepare_200OK_COMMON(spb);
setQueue(spb);
}
//------------------------------------------------------------------------------
void __fastcall TSipUserAgentThread::Prepare_200OK_COMMON(BaseExchangeBlock* bb, bool ContactReq)
{
if(ContactReq)
   Sip->prepareContact(bb);
Sip->prepareUserAgent(bb);
Sip->prepareContentLength_0(bb);
bb->sps = SPS_IMMEDIATE_REQ;
bb->s = SipVers + WS + "200 OK" + crlf;
bb->ViaSt.InsertHeaders(bb->s);
if(ContactReq)
   bb->s += bb->Contact;
bb->s +=
bb->To         +
bb->From       +
bb->CallID     +
bb->CSeq       +
bb->UserAgent  +
bb->ContentLength;
}
//------------------------------------------------------------------------------
void __fastcall TSipUserAgentThread::Proc_INFO_TEXT_PLAIN(TSipParsBuf* spb, SipUAThreadType uatt)
{
queue<string> qs;
dissect_sdp_str(qs, spb->sdp.Sdp);
if(!qs.empty())
  {
  string s = qs.front();
  if(s.find("conference") !=  -1)
    {
    qs.pop();
    Proc_CONFERENCE_INFO(qs,spb,uatt);
    return;
    }
  }
}
//------------------------------------------------------------------------------
void __fastcall TSipUserAgentThread::Proc_CONFERENCE_INFO(queue<string>& qs, TSipParsBuf* spb, SipUAThreadType uatt)
{
queue<TConfCont> q_conf;
while(!qs.empty())
     {
     string s = qs.front();
     qs.pop();
     TConfExchBlock* ExchBlock = new TConfExchBlock;
     if(ExchBlock)
       {
       ExchBlock->callid = spb->call_id.getcallid();
       ExchBlock->uatt   = uatt;
       ExchBlock->pars_sdp_substr(s);
       if(ExchBlock->conf_evnt == ConfEvnt_Add_Participant)
          ExchBlock->INFO_msg = true;
       ConferenceWin->ins_exch_buf(ExchBlock);
     ::PostMessage(ConferenceWin->Handle, CONFERENCE_MSG, WM_CONFERENCE_MSG_WPARAM__NDEF, WM_CONFERENCE_MSG_LPARAM__NDEF);
       }
     }
}
//------------------------------------------------------------------------------
bool __fastcall TSipUserAgentThread::Proc_200OK_INFO_Responce(TSipParsBuf* spb, TLegTrn* Lt)
{
bool rv = false;
if(spb->CSeq.find("INFO") != -1)
  {
  int cseq = 0;
  if(get_digit_substr(spb->CSeq, cseq, 4))
    if(Lt->INFO)
      {
      TCSeqInfo CSeqInfo;
      if(Lt->INFO->Get_CSeq_Info(cseq, CSeqInfo))
        {
        TConfExchBlock* ExchBlock = new TConfExchBlock;
        if(ExchBlock)
          {
          ExchBlock->conf_evnt = ConfEvnt_VAD_Enable;   //Разрешение на отправку события VAD абоненту от которого пришло 200 OK on INFO msg
          ExchBlock->user_name = CSeqInfo.user_name;
          ConferenceWin->ins_exch_buf(ExchBlock);
          ::PostMessage(ConferenceWin->Handle, CONFERENCE_MSG, WM_CONFERENCE_MSG_WPARAM__NDEF, WM_CONFERENCE_MSG_LPARAM__NDEF);
          }
        rv = true;
        }
      }
  }
return rv;
}
//------------------------------------------------------------------------------
void __fastcall TSipUserAgentThread::InitMediaSession_With_PPH__IN_CALL(TLegTrn* Lt, TOutputSipBuf* ospb)
{
TSessionChannelCollect sc;
if(Sip->ucs)
  {
  Sip->ucs->Create_RTP_PairCh(RTP_AUDIO_MPT, &sc.uc_rtp_audio, &sc.uc_rtcp_audio,Lt, -1, -1, ospb);//rpp.RemoteHost_1,rpp.RemotePort_1,
  //get parallel_phone media session
  TMediaSession* ms_pph = Sip->sss->GetMsOut_by_Callid(ospb->parallel_phone_call_id);
  if(ms_pph)
    {
    TUdpChannel* uc_rtp_pph = ms_pph->getRtpAudioChannel();
    if(uc_rtp_pph)
       uc_rtp_pph->Connect(sc.uc_rtp_audio);
    if(sc.uc_rtp_audio)
       sc.uc_rtp_audio->Connect(uc_rtp_pph);
    TUdpChannel* uc_rtcp_pph = ms_pph->getRtcpAudioChannel();
    if(uc_rtcp_pph)
       uc_rtcp_pph->Connect(sc.uc_rtcp_audio);
    if(sc.uc_rtcp_audio)
       sc.uc_rtcp_audio->Connect(uc_rtcp_pph);
    }
  //get main call media session (in this case media session of incomong call)
  TMediaSession* ms = Sip->sss->GetMs_by_In_Out_Callid(ospb->callid);  //ospb->callid содержит in_callid - in_pref + callid (see prepare_Initial_ANSWER_Req())
  if(ms)
    {
    ms->channels_Add(sc.uc_rtp_audio);
    ms->channels_Add(sc.uc_rtcp_audio);
    }
  prepare_ANSWER_Final(Lt,ospb, sc.uc_rtp_audio, sc.uc_rtp_video);
  Lt->out_Contact            = ospb->Contact;
  Lt->out_sdp.content_type   = ospb->contenttype;
  Lt->out_sdp.content_length = ospb->ContentLength;
  Lt->out_sdp.Sdp            = ospb->sdp.Sdp;
  }
}
//------------------------------------------------------------------------------
/*
void __fastcall TSipUserAgentThread::InitMediaSession_With_PPH__OUT_CALL(TLegTrn* Lt, TOutputSipBuf* ospb)
{
TSessionChannelCollect sc;
if(Sip->ucs)
  {
  Sip->ucs->Create_RTP_PairCh(RTP_AUDIO_MPT, &sc.uc_rtp_audio, &sc.uc_rtcp_audio,Lt, -1, -1, ospb);//rpp.RemoteHost_1,rpp.RemotePort_1,
  //get parallel_phone media session
  TMediaSession* ms_pph = Sip->sss->GetMsOut_by_Callid(ospb->parallel_phone_call_id);
  if(ms_pph)
    {
    TUdpChannel* uc_rtp_pph = ms_pph->getRtpAudioChannel();
    if(uc_rtp_pph)
       uc_rtp_pph->Connect(sc.uc_rtp_audio);
    if(sc.uc_rtp_audio)
       sc.uc_rtp_audio->Connect(uc_rtp_pph);
    TUdpChannel* uc_rtcp_pph = ms_pph->getRtcpAudioChannel();
    if(uc_rtcp_pph)
       uc_rtcp_pph->Connect(sc.uc_rtcp_audio);
    if(sc.uc_rtcp_audio)
       sc.uc_rtcp_audio->Connect(uc_rtcp_pph);
    }
  //get main call media session (in this case media session of incomong call)
  TMediaSession* ms = Sip->sss->GetMs_by_In_Out_Callid(ospb->callid);  //ospb->callid содержит in_callid - in_pref + callid (see prepare_Initial_ANSWER_Req())
  if(ms)
    {
    ms->channels_Add(sc.uc_rtp_audio);
    ms->channels_Add(sc.uc_rtcp_audio);
    }
  }
}
*/
//------------------------------------------------------------------------------

