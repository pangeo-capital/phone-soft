//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "WinRDefs.h"
#include "MediaSession.h"
#include "Sip.h"
#include "Unit4.h"

#ifndef  SIP_Video
#include "SipClient_Unit.h"
#endif

#pragma package(smart_init)
#ifdef SIP_Video
extern TForm4* Form4;
#endif
//------------------------------------------------------------------------------
void __fastcall TMediaSession::pushChannelToDelete(void* VMP,TUdpChannel* uc,TUdpChannelStruct* ucs)
{
#ifndef RTP_exsCreateUDPSocket_ADDR_ANY
TVoipMediaPortBlock* vmp = (TVoipMediaPortBlock*)VMP;
#endif
bool log=false;
TEventLogThread* elt = *eltp;
if(elt)
  if(elt->getlog())
     log=true;
if(uc)
  {
  MediaPacketType mpt = uc->getMpt();
  #ifdef SIP_Video
  if(mpt == VIDEO_MPT)
     Form4->del_vcl(uc->getChId());
  #endif
  #ifndef RTP_exsCreateUDPSocket_ADDR_ANY
  if((mpt!=SOUND_MPT)&&(mpt!=VIDEO_MPT))
      vmp->freePort(uc->localport);
  #endif
  string s;
  if(!uc->cntdToMe_Empty())
    {
    if(log)
      s = "\ncannot delete ch_" + inttostr(uc->getChId()) + ", cntdToMe list is not empty.";
    if(uc->incReqToDelete() < 2)
      {
      channels_Add(uc);
      if(log)
         s+=" re-enter at the end of queue";
      }
    if(log)
       elt->FputEvt(s);
    return;
    }
  if(!uc->myCtns_Empty())
    {
    if(log)
      {
      s = "\ncannot delete ch_" + inttostr(uc->getChId()) + ", myCtns list is not empty.";
      elt->FputEvt(s);
      }
    return;
    }
  printReqToDeleteChannel(uc);
  uc->setCallID_Null();
  ucs->insReqToDel(uc->getChId());
  }
if(ucs->Suspended)
   ucs->Resume_Thread();
}
//------------------------------------------------------------------------------
void __fastcall TMediaSessionStruct::InsMsOut_by_Callid(const string& callid,TMediaSession* ms)
{
::EnterCriticalSection(&msl_cs);
  msl.insert(TMediaSessionList::value_type(out_pref + callid,ms));
::LeaveCriticalSection(&msl_cs);
}
//-----------------------------------------------------------------------------
TMediaSession* __fastcall TMediaSessionStruct::GetMsOut_by_Callid(const string& callid)
{
TMediaSession* rv = NULL;
::EnterCriticalSection(&msl_cs);
  TMediaSessionList::iterator it = msl.find(out_pref + callid);
  if(it!=msl.end())
     rv = (*it).second;
::LeaveCriticalSection(&msl_cs);
return rv;
}
//-----------------------------------------------------------------------------
/*
void __fastcall TMediaSessionStruct::Change_Ms_Callid(LegType legtype, const string& old_callid, const string& new_callid)
{
::EnterCriticalSection(&msl_cs);
  string pref;
  if(legtype == Lt_Out)
     pref = out_pref;
  else
     pref = in_pref;
  TMediaSessionList::iterator it = msl.find(pref + old_callid);
  if(it != msl.end())
    {
    TMediaSession* rv = (*it).second;
    rv->setCallID(new_callid);
    msl.erase(it);
    msl.insert(TMediaSessionList::value_type(new_callid,rv));
    }
::LeaveCriticalSection(&msl_cs);
}
*/
//-----------------------------------------------------------------------------
/*
void __fastcall TMediaSessionStruct::DelMsOut_by_Callid(const string& callid)
{
::EnterCriticalSection(&msl_cs);
  TMediaSessionList::iterator it = msl.find(out_pref + callid);
  if(it != msl.end())
    {
    TMediaSession* ms = (*it).second;
    if(ms)
      delete ms;
    msl.erase(it);
    }
::LeaveCriticalSection(&msl_cs);
}
*/
//-----------------------------------------------------------------------------
TMediaSession* __fastcall TMediaSessionStruct::GetMs_by_Call_Tag(int Call_Tag)
{
TMediaSession* rv = NULL;
::EnterCriticalSection(&msl_cs);
  TMediaSessionList::iterator it = msl.begin();
  while(it != msl.end())
       {
       TMediaSession* ms = (*it++).second;
       if(ms)
         if(ms->getCallTag() == Call_Tag)
           {
           rv = ms;
           break;
           }
       }
::LeaveCriticalSection(&msl_cs);
return rv;
}
//-----------------------------------------------------------------------------
TMediaSession* __fastcall TMediaSessionStruct::GetMs_by_In_Out_Callid(const string& in_out_callid)
{
TMediaSession* rv=NULL;
::EnterCriticalSection(&msl_cs);
  TMediaSessionList::iterator it = msl.find(in_out_callid);
  if(it!=msl.end())
     rv=(*it).second;
::LeaveCriticalSection(&msl_cs);
return rv;
}
//-----------------------------------------------------------------------------
void __fastcall TMediaSessionStruct::InsMsIn_by_Callid(const string& callid,TMediaSession* ms)
{
::EnterCriticalSection(&msl_cs);
  msl.insert(TMediaSessionList::value_type(in_pref + callid,ms));
::LeaveCriticalSection(&msl_cs);
}
//-----------------------------------------------------------------------------
TMediaSession* __fastcall TMediaSessionStruct::GetMsIn_by_Callid(const string& callid)
{
TMediaSession* rv=NULL;
::EnterCriticalSection(&msl_cs);
  TMediaSessionList::iterator it = msl.find(in_pref + callid);
  if(it!=msl.end())
     rv = (*it).second;
::LeaveCriticalSection(&msl_cs);
return rv;
}
//-----------------------------------------------------------------------------
/*
void __fastcall TMediaSessionStruct::DelMsIn_by_Callid(const string& callid)
{
::EnterCriticalSection(&msl_cs);
TMediaSessionList::iterator it = msl.find(in_pref + callid);
if(it != msl.end())
  {
  TMediaSession* ms = (*it).second;
  if(ms)
    delete ms;
  msl.erase(it);
  }
::LeaveCriticalSection(&msl_cs);
}
*/
//-----------------------------------------------------------------------------
void __fastcall TMediaSessionStruct::EraseMediaSession(const string& callid)
{
::EnterCriticalSection(&msl_cs);
  TMediaSessionList::iterator it = msl.find(callid);
  if(it != msl.end())
    {
    TMediaSession* ms = (*it).second;
    if(ms)
      {
      ms->printDeleteSession();
      delete ms;
      }
    msl.erase(it);
    }
::LeaveCriticalSection(&msl_cs);
}
//------------------------------------------------------------------------------
void __fastcall TMediaSession::channels_Add(TUdpChannel* uc)
{
::EnterCriticalSection(&chan_cs);
if(uc)
   channels.push_back(uc);
::LeaveCriticalSection(&chan_cs);
}
//------------------------------------------------------------------------------
TUdpChannel* __fastcall TMediaSession::getFirstChannel()
{
TUdpChannel* uc=NULL;
::EnterCriticalSection(&chan_cs);
  if(!channels.empty())
    {
    uc=channels.front();
    channels.pop_front();
    }
::LeaveCriticalSection(&chan_cs);
return uc;
}
//------------------------------------------------------------------------------
TUdpChannel* __fastcall TMediaSession::getSoundChannel()
{
TUdpChannel* uc = NULL;
::EnterCriticalSection(&chan_cs);
  for(deque<TUdpChannel*>::iterator it = channels.begin(); it<channels.end();it++)
     {
     uc = (*it);
     if(uc->getMpt() == SOUND_MPT)
       break;
     uc = NULL;
     }
::LeaveCriticalSection(&chan_cs);
return uc;
}
//------------------------------------------------------------------------------
TUdpChannel* __fastcall TMediaSession::getVideoChannel()
{
TUdpChannel* uc = NULL;
::EnterCriticalSection(&chan_cs);
  for(deque<TUdpChannel*>::iterator it = channels.begin(); it < channels.end();it++)
     {
     uc = (*it);
     if(uc->getMpt() == VIDEO_MPT)
       break;
     uc = NULL;
     }
::LeaveCriticalSection(&chan_cs);
return uc;
}
//-----------------------------------------------------------------------------
TUdpChannel* __fastcall TMediaSession::getRtpAudioChannel()
{
TUdpChannel* uc=NULL;
::EnterCriticalSection(&chan_cs);
  for(deque<TUdpChannel*>::iterator it = channels.begin(); it<channels.end();it++)
     {
     uc = (*it);
     if(uc->getMpt() == RTP_AUDIO_MPT)
       break;
     uc = NULL;
     }
::LeaveCriticalSection(&chan_cs);
return uc;
}
//------------------------------------------------------------------------------
TUdpChannel* __fastcall TMediaSession::getRtcpAudioChannel()
{
TUdpChannel* uc=NULL;
::EnterCriticalSection(&chan_cs);
  for(deque<TUdpChannel*>::iterator it = channels.begin(); it<channels.end();it++)
     {
     uc = (*it);
     if(uc->getMpt() == RTCP_AUDIO_MPT)
       break;
     uc = NULL;
     }
::LeaveCriticalSection(&chan_cs);
return uc;
}
//------------------------------------------------------------------------------
TUdpChannel* __fastcall TMediaSession::getRtpVideoChannel()
{
TUdpChannel* uc=NULL;
::EnterCriticalSection(&chan_cs);
  for(deque<TUdpChannel*>::iterator it = channels.begin(); it<channels.end();it++)
     {
     uc = (*it);
     if(uc->getMpt() == RTP_VIDEO_MPT)
       break;
     uc = NULL;
     }
::LeaveCriticalSection(&chan_cs);
return uc;
}
//------------------------------------------------------------------------------
void __fastcall TMediaSession::printCreateSession()
{
TEventLogThread* elt = *eltp;
if(!elt)return;
if(!elt->getlog())return;
string timestr;
TDateTime dt = dt.CurrentTime();
exsTime( dt,timestr);
string s = "\n" + timestr + " session created: callid " + callid + " ";
int i=0;
for(deque<TUdpChannel*>::iterator it = channels.begin();it<channels.end();it++,i++)
   {
   if(i)
     s+=",";
   TUdpChannel* uc = (*it);
   if(uc)
     {
     s+="ch_" + inttostr(uc->getChId());
     uc->getMediaPacketType(s);
     }
   }
elt->FputEvt(s);
}
//------------------------------------------------------------------------------
void __fastcall TMediaSession::printDeleteSession()
{
TEventLogThread* elt = *eltp;
if(!elt)return;
if(!elt->getlog())return;
string timestr;
TDateTime dt = dt.CurrentTime();
exsTime( dt,timestr);
string s = "\n" + timestr + " session deleted: callid " + callid;
elt->FputEvt(s);
}
//------------------------------------------------------------------------------
void __fastcall TMediaSession::disconnectAllSessionChannels()
{
TUdpChannel* uc = NULL;
do{
  uc = getFirstChannel();
  if(uc)
    {
    uc->DisconnectAllMyConnections();
    #ifndef RTP_exsCreateUDPSocket_ADDR_ANY
    pushChannelToDelete(&Sip->vmpb,uc,Sip->ucs);
    #else
    pushChannelToDelete(NULL,uc,Sip->ucs);
    #endif
    }
  }while(uc);
}
//------------------------------------------------------------------------------
__fastcall TMediaSession::~TMediaSession()
{
disconnectAllSessionChannels();
::DeleteCriticalSection(&chan_cs);
}
//------------------------------------------------------------------------------
void __fastcall TMediaSession::printReqToDeleteChannel(TUdpChannel* uc)
{
TEventLogThread* elt = *eltp;
if(!elt)return;
if(!elt->getlog())return;
string timestr;
TDateTime dt = dt.CurrentTime();
exsTime( dt,timestr);
string s = "\n" + timestr + " request to delete ch_" +  inttostr(uc->getChId()) + " callid " + uc->getCallID();
elt->FputEvt(s);
}
//------------------------------------------------------------------------------
void  __fastcall TMediaSessionStruct::Connect_Conference_Channels(TUdpChannel* uc_creator,TUdpChannel* uc_party)
{
if(uc_creator)
  if(uc_party)
    if(uc_creator->getChId() != uc_party->getChId())
      {
      if(uc_party->wopt)
        {
        uc_party->wopt->setConf(true);
        if(uc_creator->mic)
          {
          uc_creator->Connect(uc_party);
          uc_creator->mic->setConf(true);
          uc_creator->mic->acqs.add_channel_to_conference(uc_party->getChId());
          vector<int> v;
          uc_creator->getAllMyConnections(v);
          if(!v.empty())
            for(unsigned i=0;i<v.size();i++)    //one opb inserted in all connected audio channels
               {
               TUdpChannel* cntd_uc = MainFormSLS->Sip->ucs->getUdpChannel(v[i]);
               if(cntd_uc)
                  if(cntd_uc->getMpt() == SOUND_MPT)
                     if(cntd_uc->getChId() != uc_party->getChId())
                        if(!uc_party->IsConnected(cntd_uc))
                          {
                          if(cntd_uc->mic)
                            {
                            cntd_uc->Connect(uc_party);
                            cntd_uc->mic->setConf(true);
                            cntd_uc->mic->acqs.add_channel_to_conference(uc_party->getChId());
                            cntd_uc->printAllMyConnections(1);
                            }
                          if(uc_party->mic)
                            {
                            uc_party->Connect(cntd_uc);
                            uc_party->mic->setConf(true);
                            uc_party->mic->acqs.add_channel_to_conference(cntd_uc->getChId());
                            }
                          }
               }
          }
        }
      if(uc_creator->wopt)
        {
        uc_creator->wopt->setConf(true);
        if(uc_party->mic)
          {
          uc_party->Connect(uc_creator);
          uc_party->mic->setConf(true);
          uc_party->mic->acqs.add_channel_to_conference(uc_creator->getChId());
          }
        }
      uc_creator->printAllMyConnections(1);
      uc_party->printAllMyConnections(1);
      }
}
//-----------------------------------------------------------------------------
void __fastcall TMediaSession::set_media_channels_OnHold(bool a)
{
TUdpChannel* uc = getRtpAudioChannel();
if(uc)
  if(uc->sendThread)
     uc->sendThread->setOnHold(a);
uc = getRtpVideoChannel();
if(uc)
  if(uc->sendThread)
     uc->sendThread->setOnHold(a);
}
//------------------------------------------------------------------------------
//-- Request to MainFormSLS Free MediaSession and send BYE ---------------------
//-- to appropriate sip leg  ---------------------------------------------------
//------------------------------------------------------------------------------
void __fastcall TMediaSession::FreeSession()
{
TExchBuf* buf = new TExchBuf(WM_APP_MSG_WPARAM__UAS);  //Удалить медиа сессию, созданную секретарем (т.к. уже произошло соединение с переадресованным абонентом).
if(buf)
  {
  buf->emt    = ExchMsgType_DeleteMediaSession;
  if(lt == Lt_In)
    {
    if(Sip->uas)
      {
      buf->callid = in_pref + callid;       //incoming session (from which was received INVITE from secretary, then REFER)
      Sip->uas->insertExchLst(buf);
      ::PostMessage(Sip->getMFHandle(), SIP_UA_MSG, WM_APP_MSG_WPARAM__UAS, WM_APP_MSG_LPARAM__READLIST);
      }
    Sip->send_call_disc_in(callid);         //Send BYE to initializer REFER (Secretary)
    }
  else if(lt == Lt_Out)
    {
    if(Sip->uac)
      {
      buf->callid = out_pref + callid;       //outgoing session (which was sent INVITE to secretary, then fom secretary sent REFER)
      buf->msg_1  = uniq_username;           //to free called_name -> callid
      Sip->uac->insertExchLst(buf);
      ::PostMessage(Sip->getMFHandle(), SIP_UA_MSG, WM_APP_MSG_WPARAM__UAC, WM_APP_MSG_LPARAM__READLIST);
      }
    Sip->send_call_disc_out(callid, false); //Send BYE to initializer REFER (Secretary)
    }
  }
}
//------------------------------------------------------------------------------
__fastcall TMediaSessionStruct::~TMediaSessionStruct(){
::EnterCriticalSection(&msl_cs);
  TMediaSessionList::iterator it = msl.begin();
  while(it!=msl.end())
       {
       TMediaSession* ms = (*it++).second;
       if(ms)
         delete ms;
       }
::LeaveCriticalSection(&msl_cs);
::DeleteCriticalSection(&msl_cs);
}
//------------------------------------------------------------------------------

