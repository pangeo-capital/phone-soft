//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "SipUasThread.h"
#include "wm_def.h"
#include "utils.h"
#include "sip.h"
#include "SipClient_Unit.h"
#include "Conference_Unit.h"

#pragma package(smart_init)
//---------------------------------------------------------------------------
void __fastcall TSipUasThread::Execute()
{
try{
while(!Terminated){
     #ifdef SIP_Uac_In_QUEUE_Log
     log_In_QueueSize("TSipUasThread::Execute(): in_queue size ");
     #endif
     BaseExchangeBlock* bb = (BaseExchangeBlock*)getQueue();
     if(!bb)
       {
       CheckResendQueue();
       continue;
       }//if(!bb)
     switch(bb->getBlockType()){
           case TSipParsBuf_BLOCKTYPE:
                Proc_TSipParsBuf(bb);
                break;
           case TOutputSipBuf_BLOCKTYPE:
                Proc_TOutputSipBuf(bb);
                break;
           }
     bb->decReferenceCount();
     }//while(!Terminated)
 }//try
catch(Exception& e){exsSstEXCEPTION(*eltp,"__TSipUasThread::Execute",e);}
}
//---------------------------------------------------------------------------
__fastcall TSipUasThread::~TSipUasThread()
{
#ifdef SIP_Thread_Destruction_Log
TEventLogThread* elt = getLog();
if(elt)elt->FputEvt("\n~TSipUasThread()");
#endif
}
//---------------------------------------------------------------------------
void __fastcall TSipUasThread::find_CallingParty_And_DisplayName(TSipParsBuf* spb)
{
int st = spb->From.find("\"");
if(st!=-1)
  {
  if((int)spb->From.length()>(st+1))
    {
    st++;
    int en = spb->From.find("\"",st);
    if(en != -1)
       spb->clngDisplayName = spb->From.substr(st,en-st);
    }
  }
if(st == -1)
  st = spb->From.find("sip:");
else
  st = spb->From.find("sip:",st);
if(st != -1)
  {
  int en = spb->From.find("@",st);
  st+=4;
  if(st < en)
     spb->callingParty = spb->From.substr(st,en-st);
  }
}
//---------------------------------------------------------------------------
void __fastcall TSipUasThread::findCallingDomain_ByFromHeader(TSipParsBuf* spb,string& domain)
{
int st = spb->From.find("@");
if(st!=-1)
  {
  int en = spb->From.find(">",st);
  if(en!=-1)
    {
    st++;
    if(st < en)
      domain = spb->From.substr(st,en-st);
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TSipUasThread::prepare_Resp180_Final(TSipParsBuf* spb)
{
Sip->prepareToTag_Final(spb);
Sip->prepareContact(spb);
Sip->prepareUserAgent(spb);
Sip->prepareContentLength_0(spb);
spb->s = spb->ReqStatusLine;
spb->ViaSt.InsertHeaders(spb->s);spb->s+=
spb->Contact   +
spb->To        +
spb->From      +
spb->CallID    +
spb->CSeq      +
spb->UserAgent +
spb->ContentLength;
}
//-----------------------------------------------------------------------------
void __fastcall TSipUasThread::Proc_TSipParsBuf(BaseExchangeBlock* bb)
{
try{
TSipParsBuf* spb = (TSipParsBuf*)bb;
switch(spb->sps){
      case SPS_INVITE_RCVD:
           Proc_Invite_UAS(spb);
           break;
      case SPS_200OK_ON_REINVITE_WITH_ADD_VIDEO_REQ:
           Proc_200OK_ON_REINVITE_WITH_ADD_VIDEO_REQ(spb);
           break;     
      case SPS_SUBSCRIBE_RCVD:
           Proc_Subscribe_UAS(spb);
           break;
      case SPS_CANCEL_RCVD:
           Proc_Cancel_UAS(spb);
           break;
      case SPS_MESSAGE_RCVD:
           Proc_Message_UAS(spb);
           break;
      case SPS_INFO_RCVD:
           Proc_INFO_RCVD(spb,uatt);
           break;     
      case SPS_ACK_RCVD:{
           TLegTrn* Lt = getLegTrn(spb->call_id.getcallid());
           if(Lt)
             {
             Lt->BLOCK_LEG_TRN();
             switch(Lt->state){
                   case SPS_WAIT_FINAL_ACK:
                        DeleteDialog(Lt);
                        break;
                   case SPS_ANSWER_REQ:
                        ClearResendBlock(Lt,spb->iStatus);
                        break;
                   }
             Lt->UN_BLOCK_LEG_TRN();
             }
           break;
           }
      case SPS_RESP_RCVD:{
           Proc_Resp_UAS(spb);
           break;
           }
      case SPS_BYE_RCVD:{
           ProcBye_UAS(spb);
           break;
           }
      case SPS_REFER_RCVD:
           Proc_REFER_RCVD(spb);
           break;
      case SPS_REGISTER_RCVD:
           Proc_REGISTER_RCVD(spb); //for pararllel_phone
           break;
      case SPS_RINGING180_REQ:{
           proc_ringing_req(spb);
           break;
           }
      case SPS_CREATE_SESSION_REQ:
           create_session(spb);
           break;
      case SPS_200OK_CANCEL_REQ:
           Sip->SetOutQueue(spb);
           break;
      case SPS_IMMEDIATE_REQ:
           Sip->SetOutQueue(spb);
           break;
      case SPS_REGISTER200OK_REQ:{     // parallel phone
           TLegTrn* Lt = getLegTrn(spb->call_id.getcallid());
           if(Lt)
             {
             Lt->BLOCK_LEG_TRN();
             Proc_REGISTER200OK_REQ(spb);
             DeleteDialog(Lt);
             Lt->UN_BLOCK_LEG_TRN();
             }
           break;
           }
      }
 }//try
catch(Exception& e){exsSstEXCEPTION(*eltp,"__Proc_TSipParsBuf()",e);}
}
//-----------------------------------------------------------------------------
void __fastcall TSipUasThread::Proc_REGISTER200OK_REQ(TSipParsBuf* spb)
{
if(spb->parallel_phone)
  if(MainFormSLS->PPS->sst_pph)
     MainFormSLS->PPS->sst_pph->setQueue(spb);
}
//------------------------------------------------------------------------------
void __fastcall TSipUasThread::proc_ringing_req(TSipParsBuf* spb)
{
TLegTrn* Lt = getLegTrn(spb->call_id.getcallid());
if(Lt)
  {
  Lt->BLOCK_LEG_TRN();
  Lt->state       = spb->sps;
  Lt->mytag       = spb->totag;
  spb->ToIP       = Lt->remoteip;
  spb->ToPort     = Lt->remoteport;
  string ContactUri; //sip:user_name@host_name:port или user_name@host_name - необходимо для Refer-To при переадресации
  if(spb->sipbf)
    {
    TRfsd* rfsd = (TRfsd*)spb->sipbf;
    if(!rfsd->ContactUserName.IsEmpty())
       if(!rfsd->ContactHostName.IsEmpty())
         {
         AnsiString S = "sip:" + rfsd->ContactUserName + "@" + rfsd->ContactHostName;
         ContactUri = S.c_str();
         if(rfsd->ContactPort != -1)
            ContactUri += ":" + inttostr(rfsd->ContactPort);
         }
    }
  prepare_Resp180_Final(spb);
  TMediaSession* ms = new TMediaSession(eltp, Sip, spb->callingParty, Lt_In);
  if(ms)
    {
    ms->setCallID(spb->call_id.getcallid());
    ms->set_contact_uri(ContactUri);
    ms->set_display_username(spb->clngDisplayName);
    #ifdef RTP_Print_Session_On_Create
    ms->printCreateSession();
    #endif
    Sip->sss->InsMsIn_by_Callid(spb->call_id.getcallid(),ms);
    }
  Sip->SetOutQueue(spb);
  Lt->UN_BLOCK_LEG_TRN();
  }//if(Lt)
}
//---------------------------------------------------------------------------
//-- implement in case auto_ans ---------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TSipUasThread::create_session(TSipParsBuf* spb)
{
TLegTrn* Lt = getLegTrn(spb->call_id.getcallid());
if(Lt)
  {
  Lt->BLOCK_LEG_TRN();
  Lt->state       = spb->sps;
  Lt->mytag       = spb->totag;
  spb->ToIP       = Lt->remoteip;
  spb->ToPort     = Lt->remoteport;
  TMediaSession* ms = new TMediaSession(eltp, Sip, spb->callingParty, Lt_In);
  if(ms)
    {
    ms->setCallID(spb->call_id.getcallid());
    #ifdef RTP_Print_Session_On_Create
    ms->printCreateSession();
    #endif
    Sip->sss->InsMsIn_by_Callid(spb->call_id.getcallid(),ms);

    TExchBuf* buf = new TExchBuf(WM_APP_MSG_WPARAM__UAS);
    if(buf)
      {
      buf->emt = ExchMsgType_INVITE_AUTO_ANS;
      buf->setAddBuf(spb);
      spb->incReferenceCount();
      insertExchLst(buf);
      ::PostMessage(Sip->getMFHandle(),SIP_UA_MSG,WM_APP_MSG_WPARAM__UAS,WM_APP_MSG_LPARAM__READLIST);
      }
    }
  Lt->UN_BLOCK_LEG_TRN();
  }//if(Lt)
}
//-----------------------------------------------------------------------------
void __fastcall TSipUasThread::Proc_TOutputSipBuf(BaseExchangeBlock* bb)
{
try{
TOutputSipBuf* spb = (TOutputSipBuf*)bb;
TLegTrn* Lt = getLegTrn(spb->CallID);
if(!Lt)return;
Lt->BLOCK_LEG_TRN();
switch(spb->getsls()){
      case SPS_REINVITE_ONHOLD_REQ:{
           prepare_REINVITE_HEADRES(Lt, spb);
           prepare_INVITE_Sdp_OnHold_OR_Resume(0, Lt->out_sdp);
           spb->sdp.Sdp = Lt->out_sdp.Sdp;
           prepareContentLength(spb);
           Lt->out_sdp.content_length = spb->ContentLength;
           spb->s += spb->ContentLength +
           spb->sdp.Sdp;
           InitResendProc(spb,Lt);
           break;
           }
      case SPS_REINVITE_RESUME_REQ:{
           prepare_REINVITE_HEADRES(Lt, spb);
           prepare_INVITE_Sdp_OnHold_OR_Resume(1, Lt->out_sdp);
           spb->sdp.Sdp = Lt->out_sdp.Sdp;
           prepareContentLength(spb);
           Lt->out_sdp.content_length = spb->ContentLength;
           spb->s += spb->ContentLength +
           spb->sdp.Sdp;
           InitResendProc(spb,Lt);
           break;
           }
      case SPS_REINVITE_WITH_ADD_VIDEO_REQ:
           REINVITE_WITH_ADD_VIDEO_REQ(spb, Lt);
           break;
      case SPS_INFO_REQ:
           INFO_REQ(spb, Lt);
           break;
      case SPS_DECLINE_REQ:{
           prepare486_Busy_OnDecline(Lt,spb);
           InitResendProc(spb,Lt);
           break;
           }
      case SPS_ANSWER_PPH_REQ: {
           if(__thread_type == 1)
             {
             spb->setsls(SPS_ANSWER_REQ);
             InitMediaSession_With_PPH__IN_CALL(Lt,spb);
             Lt->UN_BLOCK_LEG_TRN();  //!!!
             if(MainFormSLS->PPS)
               if(MainFormSLS->PPS->sst_pph)
                  MainFormSLS->PPS->sst_pph->setQueue(spb);
             return;                  //!!!     //decReferenceCount - outside Proc_TOutputSipBuf()  !!!
             }
           break;
           }
      case SPS_ANSWER_REQ:{
           if(spb->parallel_phone)
             InitMediaSession_With_PPH__IN_CALL(Lt,spb);
           else
             InitMediaSession(Lt,spb,1);
           TMediaSession* ms =  Sip->sss->GetMs_by_In_Out_Callid(spb->callid);
           if(ms)
             InitMediaChannels(Lt, spb, ms);
           break;
           }
      case SPS_ANSWER_ON_SHARING_INVITE_REQ:
           prepare_ANSWER_ON_SHARING_INVITE_Final(Lt,spb);
           break;
      case SPS_PRESENCE_NOTIFY_REQ:
      case SPS_PRESENCE_NOTIFY_ON_SUBSCRIBE_RCVD_REQ:
           prep_Final_Presence_Notify_Req(Lt,spb);
           InitResendProc(spb,Lt);
           break;
      case SPS_INIT_RTP_AUDIO_SEQ:
           INIT_RTP_AUDIO_SEQ__UAS(Lt, spb);
           Lt->UN_BLOCK_LEG_TRN();
           return; //!!! Not need send any SIP Msg
      case SPS_INIT_RTCP_AUDIO_SEQ:
           INIT_RTCP_AUDIO_SEQ__UAS(Lt, spb);
           Lt->UN_BLOCK_LEG_TRN();
           return; //!!! Not need send any SIP Msg
      case SPS_INIT_RTP_VIDEO_SEQ:
           INIT_RTP_VIDEO_SEQ__UAS(Lt, spb);
           Lt->UN_BLOCK_LEG_TRN();
           return;  //!!! Not need send any SIP Msg
      case SPS_DISC_IN_REQ:
           DisconnectIn(spb);
           break;
      }//switch(spb->getsls())

 Lt->UN_BLOCK_LEG_TRN();
 Sip->SetOutQueue(spb);
 }//try
catch(Exception& e){exsSstEXCEPTION(*eltp,"__Proc_TOutputSipBuf()",e);}
}
//------------------------------------------------------------------------------
void __fastcall TSipUasThread::INIT_RTP_AUDIO_SEQ__UAS(TLegTrn* Lt, TOutputSipBuf* spb)
{
if(Lt->ch_rtp_audio != -1)
  if(Sip->ucs)
    {
    TUdpChannel* uc = Sip->ucs->getUdpChannel(Lt->ch_rtp_audio);
    if(uc)
      if(uc->sendThread)
        SendInitial_RTP_Seq(uc);
    }
spb->decReferenceCount();
}
//------------------------------------------------------------------------------
void __fastcall TSipUasThread::INIT_RTCP_AUDIO_SEQ__UAS(TLegTrn* Lt, TOutputSipBuf* spb)
{
if(Lt->ch_rtcp_audio != -1)
  if(Sip->ucs)
    {
    TUdpChannel* uc = Sip->ucs->getUdpChannel(Lt->ch_rtcp_audio);
    if(uc)
      if(uc->sendThread)
        SendInitial_RTCP_Seq(uc);
    }
spb->decReferenceCount();
}
//------------------------------------------------------------------------------
void __fastcall TSipUasThread::INIT_RTP_VIDEO_SEQ__UAS(TLegTrn* Lt, TOutputSipBuf* spb)
{
if(Lt->ch_rtp_video != -1)
  if(Sip->ucs)
    {
    TUdpChannel* uc = Sip->ucs->getUdpChannel(Lt->ch_rtp_video);
    if(uc)
      if(uc->sendThread)
        SendInitial_RTP_Seq(uc);
    }
spb->decReferenceCount();
}
//------------------------------------------------------------------------------
void __fastcall TSipUasThread::prepare486_Busy_OnDecline(TLegTrn* Lt,TOutputSipBuf* spb)
{
spb->To = Lt->to;
spb->totag = Lt->mytag;
Sip->prepareToTag_Final(spb);
Sip->prepareCallID_Common(spb,Lt->call_id.getcallid());
Sip->prepareUserAgent(spb);
Sip->prepareContentLength_0(spb);
Lt->state   = SPS_WAIT_FINAL_ACK;
spb->ToIP   = Lt->remoteip;
spb->ToPort = Lt->remoteport;
spb->s = SipVers + WS + "486 Busy" + crlf;
Lt->OrigVia.InsertHeaders(spb->s);spb->s+=
spb->To                 +
Lt->from                +
spb->callid             +
Lt->cseqrcvd            +
spb->UserAgent          +
spb->ContentLength;
}
//------------------------------------------------------------------------------
void __fastcall TSipUasThread::ProcBye_UAS(TSipParsBuf* spb)
{
spb->ToIP   = spb->FromIP;
spb->ToPort = spb->FromPort;
TLegTrn* Lt = getLegTrn(spb->call_id.getcallid());
if(!Lt)
  {
  Prepare_200OK_COMMON(spb,true);
  setQueue(spb);
  return;
  }
Lt->BLOCK_LEG_TRN();
TExchBuf* buf = new TExchBuf(WM_APP_MSG_WPARAM__UAS);
if(buf)
  {
  buf->emt = ExchMsgType_Bye;
  buf->msg = Lt->call_id.getcallid();
  buf->b1  = Lt->screen_sharing_viewer;
  insertExchLst(buf);
  ::PostMessage(Sip->getMFHandle(), SIP_UA_MSG,WM_APP_MSG_WPARAM__UAS, WM_APP_MSG_LPARAM__READLIST);
  }
Prepare_200OK_COMMON(spb,true);
DeleteDialog(Lt);
Lt->UN_BLOCK_LEG_TRN();
setQueue(spb);
}
//------------------------------------------------------------------------------
/*
void __fastcall TSipUasThread::Prepare_200OK_Bye_UAS(BaseExchangeBlock* bb)
{
Sip->prepareUserAgent(bb);
Sip->prepareContentLength_0(bb);
bb->sps = SPS_IMMEDIATE_REQ;
bb->s = SipVers + WS + "200 OK" + crlf;
bb->ViaSt.InsertHeaders(bb->s); bb->s +=
bb->To        +
bb->From      +
bb->CallID    +
bb->CSeq      +
bb->UserAgent +
bb->ContentLength;
}
//------------------------------------------------------------------------------
void __fastcall TSipUasThread::Prepare_200OK_MESSAGE_UAS(BaseExchangeBlock* bb)
{
Sip->prepareUserAgent(bb);
Sip->prepareContentLength_0(bb);
bb->sps = SPS_IMMEDIATE_REQ;
bb->s = SipVers + WS + "200 OK" + crlf;
bb->ViaSt.InsertHeaders(bb->s); bb->s +=
bb->To        +
bb->From      +
bb->CallID    +
bb->CSeq      +
bb->UserAgent +
bb->ContentLength;
}
*/
//------------------------------------------------------------------------------
void __fastcall TSipUasThread::Prepare_200OK_Cancel_UAS(TSipParsBuf* spb, TLegTrn* Lt)
{
Sip->prepareUserAgent(spb);
Sip->prepareContentLength_0(spb);
spb->sps = SPS_200OK_CANCEL_REQ;
spb->s = SipVers + WS + "200 OK" + crlf;
spb->ViaSt.InsertHeaders(spb->s);
if(spb->To.find(";tag=") == -1)
  if(!Lt->mytag.empty())
     spb->To += ";tag=" + Lt->mytag + crlf;
if(spb->To.find(crlf) == -1)
   spb->To += crlf;
spb->s += spb->To +
spb->From      +
spb->CallID    +
spb->CSeq      +
spb->UserAgent +
spb->ContentLength;
}
//------------------------------------------------------------------------------
void __fastcall TSipUasThread::sendUas_202_OnSubscribe(TSipParsBuf* spb,TLegTrn* Lt)
{
TOutputSipBuf* ospb = Sip->Prepare_202_Resp_OnSubscribe(spb,Lt);
if(ospb)
  {
   ospb->set_req_to_delete();
   if(spb->parallel_phone)    //!!!!! spb
     {
     if(MainFormSLS->PPS->sst_pph)
        MainFormSLS->PPS->sst_pph->setQueue(ospb);
     else
        delete ospb;   
     }
   else
     Sip->SetOutQueue(ospb);    //!!!Directly to SIp Queue (because ospb->set_req_to_delete()). if setQueue() to SipUasThread, may be ospb deleted in the TSipSendThread before bb->decrementRefCount in TSipUasThread
  }
}
//------------------------------------------------------------------------------
void __fastcall TSipUasThread::sendUas_603_OnSubscribe(TSipParsBuf* spb,TLegTrn* Lt)
{
TOutputSipBuf* ospb = Sip->Prepare_603_Resp_OnSubscribe(spb,Lt);
if(ospb)
  {
   ospb->set_req_to_delete();
   Sip->SetOutQueue(ospb);    //!!!Directly to SIp Queue (because ospb->set_req_to_delete()). if setQueue() to SipUasThread, may be ospb deleted in the TSipSendThread before bb->decrementRefCount in TSipUasThread
  }
}
//------------------------------------------------------------------------------
void __fastcall TSipUasThread::DisconnectIn(TOutputSipBuf* ospb)
{
TLegTrn* Lt = getLegTrn(ospb->CallID);
if(Lt)
  {
  Lt->BLOCK_LEG_TRN();
  prepare_UAS_BYE(ospb,Lt);
  InitResendProc(ospb,Lt);
  Lt->UN_BLOCK_LEG_TRN();
  }
}
//------------------------------------------------------------------------------
void __fastcall TSipUasThread::prepare_UAS_BYE(TOutputSipBuf* ospb,TLegTrn* Lt)
{
prepare_To(ospb->To,Lt->from);
prepare_From(ospb->from,Lt->to);
int st = ospb->from.find(crlf);
if(st!=-1)
   ospb->from.resize(st);
ospb->totag = Lt->mytag;
Sip->prepareFromTag_Final(ospb);
Sip->prepareContact(ospb);
Lt->prepareReqLine_FromRemoteContact();
Lt->prepareNextCSeq("BYE",ospb);
Lt->state = SPS_BYE_REQ;
ospb->ToIP   = Lt->remoteip;
ospb->ToPort = Lt->remoteport;
ospb->s = "BYE" + WS + "sip:" + Lt->addrreqline + WS + SipVers + crlf +
ospb->via     +
"Max-Forwards:" + WS + "70" + crlf +
ospb->Contact +
ospb->To      +
ospb->from    +
//Lt->from      +
"Call-ID: "   + Lt->call_id.getprimcallid() + crlf +
ospb->cseq    +
ospb->UserAgent +
ospb->ContentLength;
}
//------------------------------------------------------------------------------
void __fastcall TSipUasThread::prepare_To(string& dest,const string& s)
{
int st = s.find("<");
if(st!=-1)
   dest = "To:" + WS + s.substr(st);
else
  {
  st = s.find("sip:");
  if(st != -1)
    dest = "To:" + WS + s.substr(st);
  }
}
//------------------------------------------------------------------------------
void __fastcall TSipUasThread::prepare_From(string& dest,const string& s)
{
int st = s.find("<");
if(st!=-1)
   dest = "From:" + WS + s.substr(st);
else
  {
  st = s.find("sip:");
  if(st != -1)
    dest = "From:" + WS + s.substr(st);
  }
}
//------------------------------------------------------------------------------
void __fastcall TSipUasThread::Proc_Resp_UAS(TSipParsBuf* spb)
{
TLegTrn* Lt = getLegTrn(spb->call_id.getcallid());
if(Lt)
  {
  Lt->BLOCK_LEG_TRN();
  ClearResendBlock(Lt,spb->iStatus,true);
  switch(spb->iStatus){
      case 200:if(Lt)
                 {
                 if(Proc_200OK_INFO_Responce(spb, Lt))
                    break;
                 if(Lt->state == SPS_PRESENCE_NOTIFY_REQ)
                    DeleteDialog(Lt);
                 else if(Lt->state == SPS_ANSWER_REQ)
                    {
                    getSDPElements_FromInMsg(Lt,spb);
                    FindCryptoKeys(Lt,spb);
                    TExchBuf* buf = new TExchBuf(WM_APP_MSG_WPARAM__UAS);
                    if(buf)
                      {
                      buf->emt = ExchMsgType_200OK_ON_INVITEREQ;
                      TRemoteMedia* rm = new TRemoteMedia;
                      if(rm)
                        {
                        rm->audio_ipaddr = spb->sdp.audio.s_remotertpip;
                        rm->audio_port   = spb->sdp.audio.remotertpport;
                        rm->audio_codecs = spb->sdp.audio.codecs;
                        #ifdef SIP_Video
                        rm->video_ipaddr = spb->sdp.video.s_remotertpip;
                        rm->video_port   = spb->sdp.video.remotertpport;
                        rm->video_codecs = spb->sdp.video.codecs;
                        #endif
                        rm->callid       = Lt->call_id.getcallid();
                        buf->setAddBuf(rm);
                        if(rm->audio_port != -1)
                          if(Lt->out_sdp.audio.remotertpport == -1)
                            {
                            prepare_out_audio_codec_list(Lt,spb);
                            Sip->sendInitial_Uas_Rtp_Sequence(RTP_AUDIO_MPT,Lt);
                            }
                        #ifdef SIP_Video
                        if(rm->video_port != -1)
                           if(Lt->out_sdp.video.remotertpport == -1)
                             {
                             prepare_out_video_codec_list(Lt,spb);
                             Sip->sendInitial_Uas_Rtp_Sequence(RTP_VIDEO_MPT,Lt);
                             }
                        #endif
                        ProcRespCommon(Lt,spb);
                        }
                      insertExchLst(buf);
                      ::PostMessage(Sip->getMFHandle(),SIP_UA_MSG,WM_APP_MSG_WPARAM__UAS,WM_APP_MSG_LPARAM__READLIST);
                      }
                    }
                 }
               break;
      case 481:if(Lt) //Call/Transaction Does Not Exist
                 {
                 if(Lt->state == SPS_PRESENCE_NOTIFY_REQ)
                   {
                 //  Sip->reset_OLD_init_NEW_SUBSCRIPTION(Lt->tousername); //Принятие решения должно производиться на SIP Сервере
                   DeleteDialog(Lt);
                   }
                 }
               break;
      }
  Lt->UN_BLOCK_LEG_TRN();
  } //if(Lt)
}
//-----------------------------------------------------------------------------
bool __fastcall TSipUserAgentThread::check_on_add_video(TLegTrn* Lt,TSipParsBuf* spb)
{
bool rv = false;
if(spb->sdp.Sdp.find("m=video") != -1)
  if(Lt->in_sdp.Sdp.find("m=video") == -1)
     rv = true;
return rv;
}
//-----------------------------------------------------------------------------
void __fastcall TSipUasThread::Proc_Invite_UAS(TSipParsBuf* spb)
{
if(__thread_type == 1)
   spb->parallel_phone = true;
TLegTrn* Lt = getLegTrn(spb->call_id.getcallid());
if(Lt)
  {
  Lt->BLOCK_LEG_TRN();
  if(Lt->cseqrcvd == spb->CSeq)
    {
    Lt->UN_BLOCK_LEG_TRN();
    return;  //resend Invite received
    }
  if(spb->To.rfind("tag=") != -1)    //REINVITE Received
    {
     if(check_on_add_video(Lt, spb))   //REINVITE with add video
       {
       getSDPElements_FromInMsg(Lt,spb);
       TExchBuf* buf = new TExchBuf(WM_APP_MSG_WPARAM__UAS);
       if(buf)
         {
         buf->emt    = ExchMsgType_RCVD_REINVITE_WITH_ADD_VIDEO;
         buf->callid = spb->call_id.getcallid();
         buf->setAddBuf(spb);
         spb->incReferenceCount();
         insertExchLst(buf);
         ::PostMessage(Sip->getMFHandle(), SIP_UA_MSG, WM_APP_MSG_WPARAM__UAS, WM_APP_MSG_LPARAM__READLIST);
         }
       Lt->UN_BLOCK_LEG_TRN();
       return;
       }
     if(check_Placed_On_Hold(spb))
       {
       Lt->PLACED_ON_HOLD_BY_REMOTE_PARTY = true;
       TMediaSession* ms = Sip->sss->GetMsIn_by_Callid(spb->call_id.getcallid());
       if(ms)
          ms->set_media_channels_OnHold(true);
       send_place_on_hold_or_resume_to_call_panel(Lt, WM_APP_MSG_WPARAM__UAS, ExchMsgType_Call_OnHold);
       TOutputSipBuf* opb = Prepare_200OK_OnReinvite(0, Lt, spb);
       if(opb)
         {
         opb->set_req_to_delete();
         Sip->SetOutQueue(opb);
         }
       }
     else
       {
       Lt->PLACED_ON_HOLD_BY_REMOTE_PARTY = false;
       TMediaSession* ms = Sip->sss->GetMsIn_by_Callid(spb->call_id.getcallid());
       if(ms)
          ms->set_media_channels_OnHold(false);
       send_place_on_hold_or_resume_to_call_panel(Lt, WM_APP_MSG_WPARAM__UAS, ExchMsgType_Call_Resume);
       TOutputSipBuf* opb = Prepare_200OK_OnReinvite(1, Lt, spb);
       if(opb)
         {
         opb->set_req_to_delete();
         Sip->SetOutQueue(opb);
         }
       }
    Lt->UN_BLOCK_LEG_TRN();
    return;
    } //if(spb->To.rfind("tag=") != -1)
  } //if(Lt)
else
  {
  Lt = new TLegTrn(Lt_In);   //INVITE Received
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
  Lt->state        = spb->sps;
  Lt->remoteip     = spb->FromIP;
  Lt->remoteport   = spb->FromPort;
  Lt->to           = spb->To;
  Lt->from         = spb->From;
  Lt->cseqrcvd     = spb->CSeq;
  Lt->Current_CSeq = getcseq(spb);
  Lt->OrigVia      = spb->ViaSt;
  Lt->contact      = spb->Contact;
  Lt->call_id      = spb->call_id;
  Lt->remotetag    = get_tag(spb->From);

  if(!spb->ReferredBy.empty())
    if(!spb->Replaces.empty())
      {
      Proc_Rcvd_CallTransfer_INVITE(Lt,spb);
      Lt->UN_BLOCK_LEG_TRN();
      return;
      }

  if(spb->ContentType.find("application/pidf+xml") != -1)      //Received ScreenSharing Request
    {
    TExchBuf* buf = new TExchBuf(WM_APP_MSG_WPARAM__UAS);
    if(buf)
      {
      Lt->screen_sharing_viewer = true;
      buf->emt    = ExchMsgType_INVITE_IN_ScreenSharing;
      buf->msg    = spb->sdp.Sdp;
      buf->callid = spb->call_id.getcallid();
      buf->msg_1  = spb->To;
      insertExchLst(buf);
      ::PostMessage(Sip->getMFHandle(), SIP_UA_MSG, WM_APP_MSG_WPARAM__UAS, WM_APP_MSG_LPARAM__READLIST);
      }
    Lt->UN_BLOCK_LEG_TRN();
    return;
    }
  getSDPElements_FromInMsg(Lt,spb);
  FindCryptoKeys(Lt,spb);
  TExchBuf* buf = new TExchBuf(WM_APP_MSG_WPARAM__UAS);
  if(buf)
    {
    findCallingParty(spb);
    buf->emt = ExchMsgType_INVITE;
    buf->setAddBuf(spb);
    spb->incReferenceCount();
    insertExchLst(buf);
    if(__thread_type == 1)
      ::PostMessage(Sip->getMFHandle(), SIP_UA_MSG, WM_APP_MSG_WPARAM__UAS, WM_APP_MSG_LPARAM__READLIST_PPH); //Invite received from parallel phone
    else
      ::PostMessage(Sip->getMFHandle(), SIP_UA_MSG, WM_APP_MSG_WPARAM__UAS, WM_APP_MSG_LPARAM__READLIST);
    }
  Lt->UN_BLOCK_LEG_TRN();
  } //if(Lt)
}
//-----------------------------------------------------------------------------
void __fastcall TSipUasThread::Proc_Cancel_UAS(TSipParsBuf* spb)
{
spb->ToIP   = spb->FromIP;
spb->ToPort = spb->FromPort;
TLegTrn* Lt = getLegTrn(spb->call_id.getcallid());
if(Lt)
  {
  Lt->BLOCK_LEG_TRN();
  TExchBuf* buf = new TExchBuf(WM_APP_MSG_WPARAM__UAS);
  if(buf)
    {
    buf->emt = ExchMsgType_CANCEL;
    buf->msg = Lt->call_id.getcallid();
    insertExchLst(buf);
    ::PostMessage(Sip->getMFHandle(), SIP_UA_MSG, WM_APP_MSG_WPARAM__UAS, WM_APP_MSG_LPARAM__READLIST);
    }
  Prepare_200OK_Cancel_UAS(spb,Lt);
  DeleteDialog(Lt);
  setQueue(spb);
  Lt->UN_BLOCK_LEG_TRN();
  }
}
//-----------------------------------------------------------------------------
void __fastcall TSipUasThread::Proc_Subscribe_UAS(TSipParsBuf* spb)
{
findCallingParty_ByContactHeader(spb);
TLegTrn* Lt = getLegTrn(spb->call_id.getcallid());
if(Lt)
  {
  Lt->BLOCK_LEG_TRN();
  if(Lt->cseqrcvd == spb->CSeq)
    {
     ;  //resend Subscribe received
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
  if(!spb->callingParty.empty())
    if(Sip->Contacts.SS.get_block_rcv_subscription())
      {
       sendUas_603_OnSubscribe(spb,Lt);
       Lt->UN_BLOCK_LEG_TRN();
       return;
      }
  string To        = spb->To;       //Chnaged in the sendUas_202_OnSubscribe()
  Lt->state        = spb->sps;
  Lt->remoteip     = spb->FromIP;
  Lt->remoteport   = spb->FromPort;
  Lt->to           = To;
  Lt->from         = spb->From;
  Lt->cseqrcvd     = spb->CSeq;
  Lt->Current_CSeq = getcseq(spb);
  Lt->OrigVia      = spb->ViaSt;
  Lt->contact      = spb->Contact;
  Lt->call_id      = spb->call_id;
  if(MainFormSLS->PPS->getActive())
    if(MainFormSLS->PPS->getRegistered())
      {
      string pph_name = MainFormSLS->PPS->getName();
      if(pph_name == spb->callingParty)
        {
        spb->parallel_phone = true;
        sendUas_202_OnSubscribe(spb,Lt);
        DeleteDialog(Lt);
        Lt->UN_BLOCK_LEG_TRN();
        return;
        }
      }
  sendUas_202_OnSubscribe(spb,Lt);
  TExchBuf* buf = new TExchBuf(WM_APP_MSG_WPARAM__UAS);
  if(buf)
    {
  //  findCallingParty_ByContactHeader(spb);
    string domain;
    findCallingDomain_ByFromHeader(spb,domain);
    buf->emt    = ExchMsgType_SUBSCRIBE_RCVD;
    buf->callid = spb->call_id.getcallid();
    buf->msg    = spb->callingParty;
    buf->msg_1  = domain;
    buf->msg_2  = To;
    buf->tag    = get_expires_value(spb);
    TSubscribedData sd;
    if(Sip->Contacts.SS.get_copy_of_subscribed_data(sd, buf->msg, buf->callid, true))
      buf->tag_1 = sd.get_cseq();
    else
      buf->tag_1  = 2; //CSeq for Notify req
    insertExchLst(buf);
  ::PostMessage(Sip->getMFHandle(),SIP_UA_MSG,WM_APP_MSG_WPARAM__UAS,WM_APP_MSG_LPARAM__READLIST);
    }
  Lt->UN_BLOCK_LEG_TRN();
  }//if(Lt)
}
//----------------------------------------------------------------------------
void __fastcall TSipUasThread::Proc_Message_UAS(TSipParsBuf* spb)
{
TLegTrn* Lt = getLegTrn(spb->call_id.getcallid());
if(Lt)
  {
  Lt->BLOCK_LEG_TRN();
  if(Lt->cseqrcvd == spb->CSeq)
    {
    if(Lt->in_sdp.Sdp != spb->sdp.Sdp)
      {
      Lt->in_sdp.Sdp = spb->sdp.Sdp;
      TExchBuf* buf  = new TExchBuf(WM_APP_MSG_WPARAM__UAS);
      if(buf)
        {
        find_CallingParty_And_DisplayName(spb);
        buf->emt    = ExchMsgType_MESSAGE;
        buf->callid = spb->call_id.getcallid();
        buf->msg    = spb->callingParty;
        buf->msg_1  = spb->clngDisplayName;
        buf->msg_2  = spb->sdp.Sdp;
        buf->msg_3  = spb->ContentType;

        if(buf->msg_3.find("text/html") != -1)      //Dissect string hear for protection of overload main thread of application
           MainFormSLS->Im.dissect_html_text_msg(buf->msg_2,buf);
        else
           MainFormSLS->Im.dissect_plain_text_msg(buf->msg_2,buf);

        /*
        if(buf->SV)
           buf->SV->find_href_inclusions();       //найти в тексте включения <a href=http://; https://
        */

        insertExchLst(buf);
      ::PostMessage(Sip->getMFHandle(),SIP_UA_MSG,WM_APP_MSG_WPARAM__UAS,WM_APP_MSG_LPARAM__READLIST);
        }
      }
    spb->ToIP   = spb->FromIP;
    spb->ToPort = spb->FromPort;
    Prepare_200OK_COMMON(spb);
    setQueue(spb);
    Lt->UN_BLOCK_LEG_TRN();
    return;
    }// if(Lt->cseqrcvd == spb->CSeq)
  else
    {
    Lt->cseqrcvd     = spb->CSeq;
    Lt->Current_CSeq = getcseq(spb);
    Lt->OrigVia      = spb->ViaSt;
    TExchBuf* buf    = new TExchBuf(WM_APP_MSG_WPARAM__UAS);
    if(buf)
      {
      find_CallingParty_And_DisplayName(spb);
      buf->emt    = ExchMsgType_MESSAGE;
      buf->callid = spb->call_id.getcallid();
      buf->msg    = spb->callingParty;
      buf->msg_1  = spb->clngDisplayName;
      buf->msg_2  = spb->sdp.Sdp;
      buf->msg_3  = spb->ContentType;

      if(buf->msg_3.find("text/html") != -1)      //Dissect string hear for protection of ovrload main thread of application
        MainFormSLS->Im.dissect_html_text_msg(buf->msg_2,buf);
      else
        MainFormSLS->Im.dissect_plain_text_msg(buf->msg_2,buf);

       /*
      if(buf->SV)
         buf->SV->find_href_inclusions();       //найти в тексте включения <a href=http://; https://
      */

      insertExchLst(buf);
    ::PostMessage(Sip->getMFHandle(),SIP_UA_MSG,WM_APP_MSG_WPARAM__UAS,WM_APP_MSG_LPARAM__READLIST);
      }
    spb->ToIP   = spb->FromIP;
    spb->ToPort = spb->FromPort;
    Prepare_200OK_COMMON(spb);
    setQueue(spb);
    }
  Lt->UN_BLOCK_LEG_TRN();
  } //if(Lt)
else
  {
  Lt = new TLegTrn(Lt_In);
  if(Lt)
    {
    Lt->BLOCK_LEG_TRN();
    if(!insertLegTrn(spb->call_id.getcallid(),Lt))
      {
      Lt->UN_BLOCK_LEG_TRN();
      delete Lt;
      return;
      }
    Lt->state        = spb->sps;
    Lt->remoteip     = spb->FromIP;
    Lt->remoteport   = spb->FromPort;
    Lt->to           = spb->To;
    Lt->from         = spb->From;
    Lt->cseqrcvd     = spb->CSeq;
    Lt->Current_CSeq = getcseq(spb);
    Lt->OrigVia      = spb->ViaSt;
    Lt->contact      = spb->Contact;
    Lt->call_id      = spb->call_id;
    Lt->in_sdp.Sdp   = spb->sdp.Sdp;
    TExchBuf* buf = new TExchBuf(WM_APP_MSG_WPARAM__UAS);
    if(buf)
      {
      find_CallingParty_And_DisplayName(spb);
      buf->emt    = ExchMsgType_MESSAGE;
      buf->callid = spb->call_id.getcallid();
      buf->msg    = spb->callingParty;
      buf->msg_1  = spb->clngDisplayName;
      buf->msg_2  = spb->sdp.Sdp;
      buf->msg_3  = spb->ContentType;

      if(buf->msg_3.find("text/html") != -1)      //Dissect string hear for protection of ovrload main thread of application
        MainFormSLS->Im.dissect_html_text_msg(buf->msg_2,buf);
      else
        MainFormSLS->Im.dissect_plain_text_msg(buf->msg_2,buf);

      /*
      if(buf->SV)
         buf->SV->find_href_inclusions();       //найти в тексте включения <a href=http://; https://
      */
      
      insertExchLst(buf);
    ::PostMessage(Sip->getMFHandle(),SIP_UA_MSG,WM_APP_MSG_WPARAM__UAS,WM_APP_MSG_LPARAM__READLIST);
      }
    }
  spb->ToIP   = spb->FromIP;
  spb->ToPort = spb->FromPort;
  Prepare_200OK_COMMON(spb);
  setQueue(spb);
  Lt->UN_BLOCK_LEG_TRN();
  }
}
//----------------------------------------------------------------------------
void __fastcall TSipUasThread::prep_Final_Presence_Notify_Req(TLegTrn* Lt, TOutputSipBuf* ospb)
{
Lt->state = SPS_PRESENCE_NOTIFY_REQ;
if(ospb->getsls() == SPS_PRESENCE_NOTIFY_ON_SUBSCRIBE_RCVD_REQ)
  {
  ospb->ToIP   = Lt->remoteip;
  ospb->ToPort = Lt->remoteport;
  ospb->callid = "Call-ID:" + WS + ospb->CallID + crlf; // ospb->callid = "Call-ID:" + WS + Lt->call_id.getcallid() + crlf;
  prepare_from_to_from_incoming_request(Lt, ospb);
  prepare_notify_request_line(Lt,ospb);
  return_network_notify_parameters(ospb);
  ospb->setsls(SPS_PRESENCE_NOTIFY_REQ);  //For correct work InitResendProc()
  }
prepareContentLength(ospb);
ospb->s = ospb->requestline +
ospb->via           +
"Max-Forwards: 70"  + crlf +
ospb->Contact       +
ospb->To            +
ospb->from          +
ospb->callid        +
"CSeq:" + WS + inttostr(ospb->curr_cseq) + WS + "NOTIFY" + crlf +
ospb->contenttype   +
ospb->UserAgent     +
ospb->subscriptionstate +
ospb->event         +
ospb->ContentLength +
ospb->sdp.Sdp;
}
//------------------------------------------------------------------------------
void __fastcall TSipUasThread::prepare_notify_request_line(TLegTrn* Lt, TOutputSipBuf* ospb)
{
int st = Lt->contact.find("<");
if(st != -1)
  {
  int en = Lt->contact.find(">",st);
  if(en != -1)
    {
    st++;
    if(st < en)
      ospb->requestline = "NOTIFY"  + WS + Lt->contact.substr(st,en-st) + WS + SipVers + crlf;
    }
  }
}
//------------------------------------------------------------------------------//
//------------------------ Change From: and To: --------------------------------//
//------------------------------------------------------------------------------//
void __fastcall TSipUasThread::prepare_from_to_from_incoming_request(TLegTrn* Lt, TOutputSipBuf* ospb)
{
ospb->To     = Lt->to;
ospb->from   = Lt->from;
string s_to;
string s_from;
int st = ospb->To.find("To:");
if(st != -1)
  {
  st += 3;
  int en = ospb->To.rfind(crlf);
  if(st < en)
    s_from = "From:" + ospb->To.substr(st);
  }
st = ospb->from.find("From:");
if(st != -1)
  {
  st += 5;
  int en = ospb->from.rfind(crlf);
  if(st < en)
     s_to = "To:" + ospb->from.substr(st);
  }
ospb->To   = s_to;
ospb->from = s_from;
}
//------------------------------------------------------------------------------//
//-- return network parameters which will be used in the next NOTIFY messages -//
//------------------------------------------------------------------------------//
void __fastcall TSipUasThread::return_network_notify_parameters(TOutputSipBuf* ospb)
{
TExchBuf* buf = new TExchBuf(WM_APP_MSG_WPARAM__UAS);
if(buf)
  {
  buf->emt    = ExchMsgType_NEWTWORK_NOTIFY_PARAMETERS;
  buf->msg    = ospb->calledname;
  buf->callid = ospb->CallID;
  TOutputSipBuf* add_buf = new TOutputSipBuf;
  if(add_buf)
    {
    add_buf->ToIP        = ospb->ToIP;
    add_buf->ToPort      = ospb->ToPort;
    add_buf->requestline = ospb->requestline;
    add_buf->To          = ospb->To;
    add_buf->from        = ospb->from;
    add_buf->curr_cseq   = ospb->curr_cseq;
    buf->setAddBuf(add_buf);
    }
  insertExchLst(buf);
  ::PostMessage(Sip->getMFHandle(),SIP_UA_MSG,WM_APP_MSG_WPARAM__UAS,WM_APP_MSG_LPARAM__READLIST);
  }
}
//------------------------------------------------------------------------------
/*
void __fastcall TStringsVect::find_href_inclusions()
{
#ifdef Receive_IM_reference_like_HTML_ref
if(!v.empty())
  {
  int current_x_poz = 0;
  int sz = v.size();
  for(int i = 0; i < sz; i++)
     {
     if(__state == 0)
        while(__find_start_of_ref(i, current_x_poz));
     else
        if(__find_end_of_ref(i, current_x_poz))
          i--;
     }
  __get_ref_strings();  //сформироать выделенные строки (full_ref)
  }
#endif
}
//------------------------------------------------------------------------------
//-- Если ссылка начинается на одной строке, а заканчивается на какой-то другой
//-- то в следующем проходе вызывается  __find_end_of_ref()
//------------------------------------------------------------------------------
int __fastcall TStringsVect::__find_start_of_ref(int i, int& x_poz)
{
#ifdef Receive_IM_reference_like_HTML_ref
if(v[i].find(__href__, x_poz) != -1)
  {
  int st = v[i].find(__a_href__, x_poz);
  if(st != -1)
    {
  __state = 1;        //found "<a href="
  __top   = i;
  __left  = st;
    int en = v[i].find("</a>", st);
    if(en != -1)
      {
      en += 4;
    __end_of_ref_found(en);
      x_poz = en;
      }
    else
      x_poz = 0;
    }
  else
    {
    st = v[i].find(__A_href__, x_poz);
    if(st != -1)
      {
    __state = 2;  //found "<A href="
    __top   = i;
    __left  = st;
      int en = v[i].find("</A>", st);
      if(en != -1)
        {
        en += 4;
      __end_of_ref_found(en);
        x_poz = en;
        }
      else
        x_poz = 0;
      }
    }
  }
else
  x_poz = 0; //!!!
#else
unsigned st = v[i].find("http", x_poz);
if(st != -1)
  {
  if(v[i].find(__http__, x_poz) != st)
    if(v[i].find(__https__, x_poz) != st)
      {
      x_poz = 0;
      return x_poz;
      }
  __top   = i;
  __left  = st;
    int en = v[i].find(WS, st);
    if(en != -1)
      {
      en += 4;
    __end_of_ref_found(en);
      x_poz = en;
      }
  }
else
  x_poz = 0; //!!!
#endif

return x_poz;
}
//------------------------------------------------------------------------------
int __fastcall TStringsVect::__find_end_of_ref(int i, int& x_poz)
{
int en;
#ifdef Receive_IM_reference_like_HTML_ref
switch(__state){
      case 1://was found "<a href="
             en = v[i].find("</a>", x_poz);
             if(en != -1)
               {
               en += 4;
             __end_of_ref_found(en);
               x_poz = en;
               }
             else
               x_poz = 0;
             break;
      case 2://was found "<A href="
             en = v[i].find("</A>", x_poz);
             if(en != -1)
               {
               en += 4;
             __end_of_ref_found(en);
               x_poz = en;
               }
             else
               x_poz = 0;
             break;
       default: x_poz = 0;
      }
#else
en = v[i].find(WS, x_poz);
if(en != -1)
  {
  en += 4;
__end_of_ref_found(en);
  x_poz = en;
  }
else
  x_poz = 0;
#endif
return x_poz;
}
//------------------------------------------------------------------------------
void __fastcall TStringsVect::__end_of_ref_found(int en)
{
if(__left < en)
  {
  TWebRefBase wrb(__top, __left, __top, en);  //right = en include pos + 1 (т.е. включает сам последний элемент)
  RL.insert(TRefList::value_type(__top, wrb));
__top = __left = __state = 0;
  }
}
//-----------------------------------------------------------------------------
#ifdef Receive_IM_reference_like_HTML_ref
void __fastcall TStringsVect::__get_ref_strings()
{
if(!RL.empty())
  {
__state = 0;
  string s;

  int v_sz = v.size();
  TRefList::iterator it = RL.begin();
  while(it != RL.end())
       {
       if((*it).second.top != (*it).second.bottom)  //reference занимает несколько строк
         if((*it).second.bottom < v_sz)
           {
           for( int i = (*it).second.top; i <= (*it).second.bottom; i++ )
               s += v[i];

           it++;
           continue;
           }

       int y = (*it).second.top;
       if(y < v_sz)
         {
         s = v[y];
         int s_sz = s.length();
         int x = (*it).second.left;
         if(x < s_sz)
           {
           if((*it).second.top == (*it).second.bottom) //ссылка начинается и заканчивается на одной строке
             {
             if((*it).second.right <= s_sz)
               {
               s = v[y].substr(x, (*it).second.right - (*it).second.left);  //то что left < right гарантирует  __end_of_ref_found()
               (*it).second.full_ref = s;
               int en = (*it).second.full_ref.rfind("<");
               if(en != -1)
                 {
                 int st = (*it).second.full_ref.rfind(">",en);
                 if(st != -1)
                   {
                   s = (*it).second.full_ref.substr(0,st);
                   st++;
                   if(st < en)
                     (*it).second.inet_addr = (*it).second.full_ref.substr(st,en - st);
                   st = s.rfind("\"");
                   if(st != -1)
                     s.resize(st);
                   st = s.find("\"");
                   if(st != -1)
                     (*it).second.ref = s.substr(st);
                   }
                 }
               }
             }
           }
         }
       it++;
       }
  }
}
#endif
//-----------------------------------------------------------------------------
void __fastcall TStringsVect::get_all_refs_by_str(int i, vector<TWebRefBase>& v)
{
TRefList::iterator it = RL.find(i);
while(it != RL.end())
     {
     if((*it).first != i)
       break;
     v.push_back((*it).second);
     it++;
     }
}
*/
//-----------------------------------------------------------------------------
