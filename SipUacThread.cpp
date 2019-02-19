//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "WinRDefs.h"
#include "SipUacThread.h"
#include "wm_def.h"
#include "sip.h"
#include "MediaSession.h"
#include "Unit4.h"
#include "Conference_Unit.h"

#pragma package(smart_init)

extern USC_Fxns USC_G7291_Fxns;
extern USC_Fxns USC_G729I_Fxns;
extern USC_Fxns USC_G729A_Fxns;
extern USC_Fxns USC_G729IFP_Fxns;

#ifdef SIP_Video
extern TForm4* Form4;
#endif
//---------------------------------------------------------------------------
void __fastcall TSipUacThread::Execute()
{
try{
while(!Terminated){
     #ifdef SIP_Uac_In_QUEUE_Log
     log_In_QueueSize("TSipUacThread::Execute(): in_queue size ");
     #endif
     BaseExchangeBlock* bb = (BaseExchangeBlock*)getQueue();
     if(!bb)
       {
       CheckResendQueue();
       continue;
       }//if(!bb)
     switch(bb->getBlockType()){
             case TOutputSipBuf_BLOCKTYPE:{
                  TOutputSipBuf* ospb = (TOutputSipBuf*)bb;
                  switch(ospb->getsls()){
                        case SPS_INIT_REGISTER_REQ:{
                             TEventLogThread* elt = getLog();
                             if(elt)
                               {
                               string timestr;
                               TDateTime dt = dt.CurrentTime();
                               exsTime(dt,timestr);
                               elt->FputEvt("\n" + timestr + " UAC_T SPS_INIT_REGISTER_REQ:\n",1);
                               }
                             TLegTrn* Lt = new TLegTrn(Lt_Out);
                             if(Lt)
                                {
                                Lt->BLOCK_LEG_TRN();
                                Lt->state      = ospb->getsls();
                                Lt->remoteip   = ospb->ToIP;
                                Lt->remoteport = ospb->ToPort;
                                Lt->mytag      = ospb->FromTag;
                                Lt->from       = ospb->from;
                                Lt->contactusername = ospb->calledname;

                                Lt->ac_user_name = ospb->ac_user_name;
                                Lt->ac_user_pwd  = ospb->ac_user_pwd;
                                Lt->ac_domain    = ospb->ac_domain;

                                Lt->call_id.setprimcallid(ospb->CallID);
                                insertLegTrn(ospb->CallID,Lt);
                                if(Check_Transport_On_Resend_Proc())
                                  {
                                  InitResendProc(ospb,Lt);
                                  Sip->SetOutQueue(ospb);
                                  }
                                Lt->UN_BLOCK_LEG_TRN();
                                }
                             ospb->decReferenceCount();
                             continue;
                             }
                        case SPS_REGISTER_REQ:{
                             TEventLogThread* elt = getLog();
                             if(elt)
                               {
                               string timestr;
                               TDateTime dt = dt.CurrentTime();
                               exsTime(dt,timestr);
                               elt->FputEvt("\n" + timestr + " UAC_T SPS_REGISTER_REQ:\n",1);
                               }
                             TResendReqData rrd;
                             TLegTrn* Lt = getLegTrn(Sip->crh.getCurrentCallID());
                             if(Lt)
                               {
                               Lt->BLOCK_LEG_TRN();
                               Lt->state = ospb->getsls();

                               Lt->ac_user_name = ospb->ac_user_name;
                               Lt->ac_user_pwd  = ospb->ac_user_pwd;
                               Lt->ac_domain    = ospb->ac_domain;

                               if(srst)
                                 {
                                 ERASE_RESEND_REQUEST(Lt,rrd);
                                 ospb->set_reg_tag(Sip->regint);     //Registration interval
                                 if(Check_Transport_On_Resend_Proc())
                                   InitResendProc(ospb,Lt);
                                 }

                //              if(Check_Transport_On_Keep_Alive())
                                 if(Sip->regint > KEEP_ALIVE_RESEND_INTERVAL)      //Registration interval > 30 sec
                                   if(!Lt->keepalive)
                                     {

                                     TLegTrn* Lt_kpl_prev = find_previously_created_KEEP_ALIVE_leg_trn();  //if exists ( проверка "на всякий случай": мог случайно остаться от предыдущщих REGISTER)
                                     if(Lt_kpl_prev)
                                       {
                                       Lt_kpl_prev->BLOCK_LEG_TRN();
                                       eraseLegTrn(Lt_kpl_prev->call_id.getcallid());
                                       Lt_kpl_prev->UN_BLOCK_LEG_TRN();
                                       }

                                     TLegTrn* Lt_kpl = new TLegTrn(Lt_Out);
                                     if(Lt_kpl)
                                       {
                                       Lt_kpl->BLOCK_LEG_TRN();
                                       Lt_kpl->state = SPS_KEEP_ALIVE;
                                       Lt_kpl->remoteip   = Sip->SipProxy.IPAddr;
                                       Lt_kpl->remoteport = Sip->SipProxy.Port;
                                       Sip->generateFromTag(ospb);
                                       Sip->generateCallID(ospb);
                                       Lt_kpl->call_id.setprimcallid(ospb->CallID);
                                       insertLegTrn(ospb->CallID,Lt_kpl);
                                       if(srst)
                                         {
                                         ospb->setsls(SPS_KEEP_ALIVE);
                                         ospb->s = sdpboundary;
                                         Lt_kpl->PrepareResendBlock(ospb);
                                         if(Check_Transport_On_Resend_Proc())
                                            INSERT_RESEND_REQUEST(rrd, Lt_kpl);
                                         }
                                       Lt->keepalive = true;
                                       Lt->keepalive_callid = ospb->CallID;
                                       Lt_kpl->UN_BLOCK_LEG_TRN();
                                       }
                                     } //if(!Lt->keepalive)
                               Lt->UN_BLOCK_LEG_TRN();
                               } //if(Lt)
                             ospb->decReferenceCount();   // "1.1.24_118_8_1";
                             continue;//!!!       Не отправлять в передающий thread
                             }
                        case SPS_FINAL_REGISTER_REQ:{
                             TEventLogThread* elt = getLog();
                             if(elt)
                               {
                               string timestr;
                               TDateTime dt = dt.CurrentTime();
                               exsTime(dt,timestr);
                               elt->FputEvt("\n" + timestr + " UAC_T SPS_FINAL_REGISTER_REQ:\n",1);
                               }
                             TLegTrn* Lt = getLegTrn(Sip->crh.getCurrentCallID());
                             if(Lt)
                               {
                               Lt->BLOCK_LEG_TRN();
                               Lt->state = ospb->getsls();

                               Lt->ac_user_name = ospb->ac_user_name;
                               Lt->ac_user_pwd  = ospb->ac_user_pwd;
                               Lt->ac_domain    = ospb->ac_domain;

                               if(srst)
                                 {
                                 ERASE_RESEND_REQUEST(Lt);
                                 InitResendProc(ospb,Lt);
                                 }
                               Lt->UN_BLOCK_LEG_TRN();
                               }
                             break;
                             }
                        case SPS_AUTH_REGISTER_REQ:{
                            // TLegTrn* Lt = getLegTrn(Sip->crh.getCurrentCallID());
                             TLegTrn* Lt = getLegTrn(ospb->callid);
                             if(Lt)
                               {
                               Lt->BLOCK_LEG_TRN();
                               Auth_Register_Req(ospb,Lt);
                               if(srst)
                                 {
                                 ERASE_RESEND_REQUEST(Lt);
                                 ospb->set_reg_tag(Sip->regint);     //Registration interval
                                 ospb->setsls_1(SPS_REGISTER_REQ);
                                 InitResendProc(ospb,Lt);
                                 }
                               Lt->UN_BLOCK_LEG_TRN();
                               }
                             break;
                             }
                        case SPS_INIT_SUBSCRIBE_REQ:{
                             if(!ospb->CallID.empty())
                               {
                               TLegTrn* Lt = getLegTrn(ospb->CallID); //refreshing_SUBSCRIBE
                               if(Lt)                                 //InitResendProc() in the init_Refreshing_SUBSCRIBE_Proc()
                                 break;
                               }
                             TLegTrn* Lt = new TLegTrn(Lt_Out);     //initial SUBSCRIBE
                             if(Lt)
                                {
                                Lt->BLOCK_LEG_TRN();
                                Lt->state        = ospb->getsls();
                                Lt->remoteip     = ospb->ToIP;
                                Lt->remoteport   = ospb->ToPort;
                                Lt->mytag        = ospb->FromTag;
                                Lt->ac_user_name = ospb->ac_user_name;
                                Lt->call_id.setprimcallid(ospb->CallID);
                                if(insertLegTrn(ospb->CallID,Lt))
                                  {
                                  InitResendProc(ospb,Lt);
                                  Lt->UN_BLOCK_LEG_TRN();
                                  }
                                else
                                  {
                                  Lt->UN_BLOCK_LEG_TRN();
                                  delete Lt;
                                  }
                                }
                             break;
                             }
                        case SPS_MESSAGE_REQ:
                             MessageReq(ospb);
                             break;
                        case SPS_INFO_REQ:
                             INFO_REQ(ospb, NULL);
                             break;
                        case SPS_AUTH_MESSAGE_REQ:
                             auth_message_req(ospb);
                             break;
                        case SPS_INVITE_REQ:{
                             TEventLogThread* elt = getLog();
                             if(elt)
                               {
                               string timestr;
                               TDateTime dt = dt.CurrentTime();
                               exsTime(dt,timestr);
                               elt->FputEvt("\n" + timestr + " UAC_Thread  SPS_INVITE_REQ: " + (string)"\"" +  ospb->calledname + "\"\n",1);
                               }
                             TLegTrn* Lt = new TLegTrn(Lt_Out);
                             if(Lt)
                               {
                               if(ospb->parallel_phone)        //когда INVITE посылается непосредственно к параллельному телефону
                                 {
                                 InitMediaSession_To_PPH(Lt,ospb);
                                 if(MainFormSLS->PPS->sst_pph)
                                    MainFormSLS->PPS->sst_pph->setQueue(ospb);
                                 ospb->decReferenceCount();
                                 continue;   //!!!
                                 }
                               else
                                 {
                                 InitMediaSession(Lt,ospb,0);   //without resend

                                 #ifdef Wait_For_First_Mic_Packet
                                 if(Lt->ospb_wait_first_mic_packet)
                                   {
                                   TOutputSipBuf* old_spb = Lt->ospb_wait_first_mic_packet;
                                   old_spb->decReferenceCount();
                                   }
                                 Lt->ospb_wait_first_mic_packet = ospb;
                                 continue;  //Don't send SIP INVITE. Waiting for first mic packet ( SPS_INVITE_ON_RCV_FIRST_MIC_PACKET_REQ ). ospb->reference_count stay without changes
                                 #endif

                                 }
                               }
                             break;
                             }
                        #ifdef Wait_For_First_Mic_Packet
                        case SPS_INVITE_ON_RCV_FIRST_MIC_PACKET_REQ:{
                             INVITE_ON_RCV_FIRST_MIC_PACKET_REQ(ospb);
                             delete ospb; //  !!!
                             continue;    //  !!!
                             }
                        #endif     
                        case SPS_REINVITE_WITH_ADD_VIDEO_REQ:
                             REINVITE_WITH_ADD_VIDEO_REQ(ospb, NULL);
                             break;
                        case SPS_REINVITE_ONHOLD_REQ:
                             REINVITE_ONHOLD_REQ(ospb);
                             break;
                        case SPS_REINVITE_RESUME_REQ:
                             REINVITE_RESUME_REQ(ospb);
                             break;
                        case SPS_AUTH_INVITE_REQ:
                             auth_invite_req(ospb);
                             break;
                        case SPS_INVITE_FILETRANSFER_REQ:{
                             TLegTrn* Lt = new TLegTrn(Lt_Out);
                             if(Lt)
                                InitMediaSession_FileTransfer(Lt,ospb);
                             break;
                             }
                        case SPS_INVITE_SCREENSHARING_REQ:{
                             TLegTrn* Lt = new TLegTrn(Lt_Out);
                             if(Lt)
                                InitMediaSession_ScreenSharing(Lt,ospb);
                             break;
                             }
                        case SPS_DISC_OUT_REQ:
                             DisconnectOut(ospb);
                             if(ospb->parallel_phone)
                               if(MainFormSLS->PPS->sst_pph)
                                 {
                                 MainFormSLS->PPS->sst_pph->setQueue(ospb);
                                 ospb->decReferenceCount();
                                 continue; //!!!
                                 }
                             break;
                        case SPS_INIT_RTP_AUDIO_SEQ:{
                             INIT_RTP_AUDIO_SEQ__UAC(ospb);
                             continue; //!!!     Not need to send any SIP msg
                             }
                        case SPS_INIT_RTCP_AUDIO_SEQ:{
                             INIT_RTCP_AUDIO_SEQ__UAC(ospb);
                             continue;
                             }
                        #ifdef SIP_Video
                        case SPS_INIT_RTP_VIDEO_SEQ:{
                             INIT_RTP_VIDEO_SEQ__UAC(ospb);
                             continue;           //Not need to send any SIP msg
                             }          //case SPS_INIT_RTP_VIDEO_SEQ:{
                        #endif
                        }     // switch(ospb->getsls()){
                  Sip->SetOutQueue(ospb);
                  ospb->decReferenceCount();     //!!!do not call updateSentQueue()
                  break;
                  } // case TOutputSipBuf_BLOCKTYPE:{

             case TSipParsBuf_BLOCKTYPE:{
                  #ifdef SIP_Uac_In_QUEUE_Log
                  log_ua("TSipUacThread::Execute(): TSipParsBuf_BLOCKTYPE ");
                  #endif
                  TSipParsBuf* spb = (TSipParsBuf*)bb;
                  switch(spb->sps){
                         case SPS_RESP_RCVD:
                              Proc_Resp_UAC(spb);
                              break;
                         case SPS_ACK_REQ:
                              Sip->SetOutQueue(spb);
                              break;
                         case SPS_BYE_RCVD:
                              ProcBye_UAC(spb);
                              break;
                         case SPS_IMMEDIATE_REQ:
                              Sip->SetOutQueue(spb);
                              break;
                         case SPS_NOTIFY_RCVD:
                              ProcNotify_UAC(spb);
                              break;
                         case SPS_INFO_RCVD:
                              Proc_INFO_RCVD(spb,uatt);
                              break;
                         case SPS_200OK_NOTIFY_REQ:
                              Sip->SetOutQueue(spb);
                              break;
                         case SPS_INVITE_RCVD:
                              ProcINVITE_Rcvd_UAC(spb);  //if To: header contain tag=, this is REINVITE
                              break;
                         case SPS_200OK_ON_REINVITE_WITH_ADD_VIDEO_REQ:
                              Proc_200OK_ON_REINVITE_WITH_ADD_VIDEO_REQ(spb);
                              break;
                         }//switch(ospb->getsls())
                  spb->decReferenceCount();
                  break;
                  } //case TSipParsBuf_BLOCKTYPE:
             } //switch(bb->getBlockType())
     } //while(!Terminated)
 }//try
catch(Exception& e){exsSstEXCEPTION(*eltp,"__TSipUacThread::Execute",e);}
}
//---------------------------------------------------------------------------
void __fastcall TSipUacThread::INIT_RTP_AUDIO_SEQ__UAC(TOutputSipBuf* ospb)
{
TLegTrn* Lt = getLegTrn(ospb->CallID);
if(Lt)
  {
  Lt->BLOCK_LEG_TRN();
  if(Lt->ch_rtp_audio != -1)
    if(Sip->ucs)
      {
      TUdpChannel* uc = Sip->ucs->getUdpChannel(Lt->ch_rtp_audio);
      if(uc)
        if(uc->sendThread)
          {
          uc->sendThread->setRemoteAddress(ospb->ToIP,ospb->ToPort);
          if(!ospb->sdp.audio.codecs.empty())
             uc->sendThread->remoteCodec = ospb->sdp.audio.codecs[0];
          if(ospb->irp)
            {
            uc->sendThread->currentSeqNumber = ospb->irp->initSeqNumber;
            uc->sendThread->currentTimeStamp = ospb->irp->initTimeStamp;
            uc->sendThread->sourceId         = ospb->irp->sourceId;
            }
          switch(uc->sendThread->remoteCodec){
                case 18:{
                        TG729ENC* G729ENC = uc->sendThread->CREATE_G729_IPP_ENCODER();  //for Cutgoing Call
                        if(G729ENC)
                           G729ENC->init_encoder(&USC_G7291_Fxns,320);
                        TG729DEC* G729DEC = uc->CREATE_G729_IPP_DECODER();
                        if(G729DEC)
                           G729DEC->init_decoder(&USC_G7291_Fxns,320);
                        break; // from switch(uc->sendThread->remoteCodec), not from case SPS_INIT_RTP_AUDIO_SEQ: (::LeaveCriticalSection(&ua_cs) не будет пропущен)
                        }
                }

          SendInitial_RTP_Seq(uc);
          }//if(uc->sendThread)
      }//if(Sip->ucs)
  Lt->UN_BLOCK_LEG_TRN();
  } //if(Lt)
ospb->decReferenceCount();
}
//----------------------------------------------------------------------------
void __fastcall TSipUacThread::INIT_RTCP_AUDIO_SEQ__UAC(TOutputSipBuf* ospb)
{
TLegTrn* Lt = getLegTrn(ospb->CallID);
if(Lt)
  {
  Lt->BLOCK_LEG_TRN();
  if(Lt->ch_rtcp_audio != -1)
    if(Sip->ucs)
      {
      TUdpChannel* uc = Sip->ucs->getUdpChannel(Lt->ch_rtcp_audio);
      if(uc)
        if(uc->sendThread)
          {
          uc->sendThread->setRemoteAddress(ospb->ToIP,ospb->ToPort);
          SendInitial_RTCP_Seq(uc);
          }  //if(uc->sendThread)
      }  //if(Sip->ucs)
  Lt->UN_BLOCK_LEG_TRN();
  } //if(Lt)
ospb->decReferenceCount();
}
//-----------------------------------------------------------------------------
void __fastcall TSipUacThread::INIT_RTP_VIDEO_SEQ__UAC(TOutputSipBuf* ospb)
{
TLegTrn* Lt = getLegTrn(ospb->CallID);
if(Lt)
  {
  Lt->BLOCK_LEG_TRN();
  if(Lt->ch_rtp_video != -1)
    if(Sip->ucs)
      {
      TUdpChannel* uc = Sip->ucs->getUdpChannel(Lt->ch_rtp_video);
      if(uc)
        if(uc->sendThread)
          {
          uc->sendThread->setRemoteAddress(ospb->ToIP,ospb->ToPort);
          if(!ospb->sdp.video.codecs.empty())
             uc->sendThread->remoteCodec = ospb->sdp.video.codecs[0];
          if(ospb->irp)
            {
            uc->sendThread->currentSeqNumber = ospb->irp->initSeqNumber;
            uc->sendThread->currentTimeStamp = ospb->irp->initTimeStamp;
            uc->sendThread->sourceId         = ospb->irp->sourceId;
            }
          SendInitial_RTP_Seq(uc);
          }
      }  // if(Sip->ucs)
  Lt->UN_BLOCK_LEG_TRN();
  } //if(Lt)
ospb->decReferenceCount();
}
//----------------------------------------------------------------------------
__fastcall TSipUacThread::~TSipUacThread()
{
#ifdef SIP_Thread_Destruction_Log
TEventLogThread* elt = getLog();
if(elt)elt->FputEvt("\n~TSipUacThread()");
#endif
}
//----------------------------------------------------------------------------
void __fastcall TSipUacThread::prepare_CANCEL(TOutputSipBuf* ospb,TLegTrn* Lt)
{
Lt->state = SPS_CANCEL_REQ;
ospb->ToIP   = Lt->remoteip;
ospb->ToPort = Lt->remoteport;
ospb->s = "CANCEL" + WS + Lt->addrreqline +
ospb->via    +
Lt->to       +
Lt->from     +
"Call-ID: "  + Lt->call_id.getprimcallid() + crlf +
"CSeq: 1 CANCEL" + crlf +
ospb->UserAgent  +
ospb->ContentLength;
}
//----------------------------------------------------------------------------
void __fastcall TSipUacThread::prepare_UAC_BYE(TOutputSipBuf* ospb,TLegTrn* Lt)
{
ospb->To = Lt->to;
int st = ospb->To.find(crlf);
if(st!=-1)
   ospb->To.resize(st);
ospb->totag = Lt->remotetag;
Sip->prepareToTag_Final(ospb);
Sip->prepareContact(ospb);
Lt->prepareNextCSeq("BYE",ospb);
Lt->state = SPS_BYE_REQ;
ospb->ToIP   = Lt->remoteip;
ospb->ToPort = Lt->remoteport;
ospb->s = "BYE" + WS + Lt->addrreqline +
ospb->via     +
"Max-Forwards:" + WS + "70" + crlf +
ospb->Contact +
ospb->To      +
Lt->from      +
"Call-ID: "   + Lt->call_id.getprimcallid() + crlf +
ospb->cseq    +
ospb->UserAgent +
ospb->ContentLength;
}
//----------------------------------------------------------------------------
void __fastcall TSipUacThread::Proc_Resp_UAC(TSipParsBuf* spb)
{
  TLegTrn* Lt = getLegTrn(spb->call_id.getcallid());
  if(Lt)
    {
    Lt->BLOCK_LEG_TRN();
    ClearResendBlock(Lt,spb->iStatus,true);
    switch(spb->iStatus){
      case 100:Proc_100_Resp(Lt,spb);
               break;
      case 180:Proc_180_Resp(Lt,spb);
               break;
      case 183:Proc_183_Resp(Lt,spb);
               break;
      case 200:Proc_200_Resp(Lt,spb);
               break;
      case 202:Proc_202_Resp(Lt,spb);
               break;
    //  case 400:ProcRespCommon(Lt,spb);
    //           break;
      case 401:Proc_401_Resp(Lt,spb);
               break;
    //  case 402:ProcRespCommon(Lt,spb); //Payment Required
    //           break;
      case 403:Proc_403_Resp(Lt,spb);  //Forbidden
               break;
     // case 404: //Not Found
     // case 405: //Method Not Allowed
     // case 406: //Not Acceptable
     //          ProcRespCommon(Lt,spb);
     //          break;
      case 480:Proc_480_Resp(Lt,spb);
               break;
      case 481:Proc_481_Resp(Lt,spb);
               break;
      case 486:Proc_486_Resp(Lt,spb);
               break;
      case 487:Proc_487_Resp(Lt,spb);
               break;
      case 603:Proc_603_Resp(Lt,spb);
               break;
      default:ProcRespCommon(Lt,spb);
              if(spb->iStatus >= 400)
                {
                if(spb->CSeq.find("INFO") != -1)
                  {
                  ; //send any informatiom to call panel about wrong responce on INFO req (Это исключение было сделано для Conference INFO. From CounterPath we receive 415 responce (not supported media type))
                  }
                else
                  {
                  send_resp_to_call_panel(Lt,ExchMsgType_NotAcceptable);
                  DeleteDialog(Lt);   //Do not replase above
                  }
                }
              break;
      }
    Lt->UN_BLOCK_LEG_TRN();
    }//if(Lt)
}
//----------------------------------------------------------------------------
void __fastcall TSipUacThread::ProcNotify_UAC(TSipParsBuf* spb)
{
try{
spb->ToIP        = spb->FromIP;
spb->ToPort      = spb->FromPort;
spb->from_tag    = get_tag(spb->From);
string Contact   = spb->Contact;
string user_name = get_user_name(Contact); // user name, who sent NOTIFY message
string Event     = spb->Event;
string SubscriptionState  = spb->SubscriptionState;
TXmlBuf Xml_buf;
get_notify_xml_parameters(Xml_buf,spb);
Prepare_200OK_Notify_On_Subscribe_UAC(spb);
setQueue(spb);            //Do not use spb after that place !!!! (may be deleted)
if(Event.find("presence") != -1)
  {
  int st = SubscriptionState.find("active");
  if(st != -1)
    {
    TExchBuf* buf = new TExchBuf(WM_APP_MSG_WPARAM__UAC);
    if(buf)
      {
      buf->emt    = ExchMsgType_Presence;
      buf->msg    = "active";
      buf->b1     = Xml_buf.get_sdp_rcvd();
      buf->msg_3  = Xml_buf.Tuple.basic;        //"open", "close"
      buf->msg_4  = Xml_buf.Person.activities1; //"away", "busy"
      buf->msg_5  = Xml_buf.Person.person;      //person id
      buf->msg_6  = spb->from_tag;
      buf->msg_1  = Xml_buf.Person.note;        //Comment
      buf->callid = user_name;
      insertExchLst(buf);
      ::PostMessage(Sip->getMFHandle(),SIP_UA_MSG,WM_APP_MSG_WPARAM__UAC,WM_APP_MSG_LPARAM__READLIST);
      }
    return;
    } //SubscriptionState.find("active");
  st = SubscriptionState.find("terminated");
  if(st != -1)
    {
    TExchBuf* buf = new TExchBuf(WM_APP_MSG_WPARAM__UAC);
    if(buf)
      {
      buf->emt    = ExchMsgType_Presence;
      buf->msg    = "terminated";
      buf->msg_2  = get_subscription_state_reason(SubscriptionState);
      buf->msg_5  = Xml_buf.Person.person;      //person id
      buf->msg_6  = spb->from_tag;
      buf->callid = user_name;
      insertExchLst(buf);
      ::PostMessage(Sip->getMFHandle(),SIP_UA_MSG,WM_APP_MSG_WPARAM__UAC,WM_APP_MSG_LPARAM__READLIST);
      }
    return;
    } //SubscriptionState.find("terminated");
  }//if(spb->Event.find("presence") != -1)
}//try
catch(Exception& e){exsSstEXCEPTION(*eltp,"__ProcNotify_UAC()",e);}
}
//-----------------------------------------------------------------------------
string __fastcall TSipUacThread::get_subscription_state_reason(const string& s)
{
string rv;
int st = s.rfind("reason=");
if(st)
  {
  st += 7;
  int en = s.rfind(crlf);
  if(st < en)
    rv = s.substr(st,en-st);
  }
return rv;
}
//----------------------------------------------------------------------------
void __fastcall TSipUacThread::ProcBye_UAC(TSipParsBuf* spb)
{
spb->ToIP   = spb->FromIP;
spb->ToPort = spb->FromPort;
TLegTrn* Lt = getLegTrn(spb->call_id.getcallid());
if(Lt)
  {
  Lt->BLOCK_LEG_TRN();
  if(Lt->lt_parallel_phone)   //Bye received from parallel phone
    {
    if(Lt->primary_legtype_pph == Lt_Out)     //Primary call -- outgoing
      {
      TExchBuf* buf = new TExchBuf(WM_APP_MSG_WPARAM__UAC);   // !!! __UAC
      if(buf)
        {
        buf->emt = ExchMsgType_Bye_From_Pph;
        buf->parallel_phone = true;
        buf->msg = Lt->lt_parallel_phone_primary_call_id;
        insertExchLst(buf);
        if(__thread_type == 1)  //for parallel phone
         ::PostMessage(Sip->getMFHandle(), SIP_UA_MSG, WM_APP_MSG_WPARAM__UAC, WM_APP_MSG_LPARAM__READLIST_PPH); //!!! __UAC_PPH
        else
         ::PostMessage(Sip->getMFHandle(), SIP_UA_MSG, WM_APP_MSG_WPARAM__UAC, WM_APP_MSG_LPARAM__READLIST);     //!!! __UAC
        }
      }
    else if(Lt->primary_legtype_pph == Lt_In) //Primary call -- incoming
      {
      TExchBuf* buf = new TExchBuf(WM_APP_MSG_WPARAM__UAS);  // !!! __UAS
      if(buf)
        {
        buf->emt = ExchMsgType_Bye_From_Pph;
        buf->parallel_phone = true;
        buf->msg = Lt->lt_parallel_phone_primary_call_id;
        if(Sip->uas)
           Sip->uas->insertExchLst(buf);
      ::PostMessage(Sip->getMFHandle(),SIP_UA_MSG, WM_APP_MSG_WPARAM__UAS, WM_APP_MSG_LPARAM__READLIST); // __UAS
        }
      }
    TExchBuf* buf = new TExchBuf(WM_APP_MSG_WPARAM__UAC);
    if(buf)
      {
      buf->emt = ExchMsgType_Bye;
      buf->msg = Lt->call_id.getcallid();
      insertExchLst(buf);
    ::PostMessage(Sip->getMFHandle(),SIP_UA_MSG, WM_APP_MSG_WPARAM__UAC, WM_APP_MSG_LPARAM__READLIST);
      }
    } //if(Lt->lt_parallel_phone
else
    {
    TExchBuf* buf = new TExchBuf(WM_APP_MSG_WPARAM__UAC);
    if(buf)
      {
      buf->emt = ExchMsgType_Bye;
      buf->msg = Lt->call_id.getcallid();
      insertExchLst(buf);
      ::PostMessage(Sip->getMFHandle(),SIP_UA_MSG, WM_APP_MSG_WPARAM__UAC, WM_APP_MSG_LPARAM__READLIST);
      }
    }
  Prepare_200OK_COMMON(spb,true);
  if(Lt->lt_parallel_phone)
    {
    if(MainFormSLS->PPS->sst_pph)
       MainFormSLS->PPS->sst_pph->setQueue(spb);
    }
  else
    setQueue(spb);
  DeleteDialog(Lt);
  Lt->UN_BLOCK_LEG_TRN();
  } //if(Lt)
else
  {
  Prepare_200OK_COMMON(spb,true);
  setQueue(spb);
  }
}
//----------------------------------------------------------------------------
void __fastcall TSipUacThread::Proc_487_Resp(TLegTrn* Lt,TSipParsBuf* spb)
{
spb->ToIP   = spb->FromIP;
spb->ToPort = spb->FromPort;
if(!Lt)
  {
  PrepareReqURIFromToHeader(spb);
  PrepareCommonOutACK(NULL,spb);
  setQueue(spb);
  return;
  }
PrepareCommonOutACK(Lt,spb);
DeleteDialog(Lt);
setQueue(spb);
}
//----------------------------------------------------------------------------
void __fastcall TSipUacThread::Proc_100_Resp(TLegTrn* Lt,TSipParsBuf* spb)
{
if(!Lt)return;
if(spb->CSeq.find("INFO") != -1)  //На INFO не менять Lt->Resp
   Lt->resp = SPS_TRYING100_RCVD;
if(Lt->remotetag.empty())
   Lt->remotetag = spb->totag;
if(Lt->state == SPS_INVITE_REQ)
  {
  TExchBuf* buf = new TExchBuf(WM_APP_MSG_WPARAM__UAC);
  if(buf)
    {
    buf->emt = ExchMsgType_Resp100;
    buf->msg = Lt->call_id.getcallid();
    insertExchLst(buf);
    if(__thread_type == 1)  //for parallel phone
     ::PostMessage(Sip->getMFHandle(),SIP_UA_MSG,WM_APP_MSG_WPARAM__UAC,WM_APP_MSG_LPARAM__READLIST_PPH);
    else
     ::PostMessage(Sip->getMFHandle(),SIP_UA_MSG,WM_APP_MSG_WPARAM__UAC,WM_APP_MSG_LPARAM__READLIST);
    }
  }
}
//----------------------------------------------------------------------------
void __fastcall TSipUacThread::Proc_180_Resp(TLegTrn* Lt,TSipParsBuf* spb)
{
if(!Lt)return;
Lt->resp = SPS_RINGING180_RCVD;
if(Lt->remotetag.empty())
   Lt->remotetag = spb->totag;
TExchBuf* buf = new TExchBuf(WM_APP_MSG_WPARAM__UAC);
if(buf)
  {
  buf->emt            = ExchMsgType_Resp180;
  buf->msg            = Lt->call_id.getcallid();
  buf->a1             = __thread_type; //0 - normal, 1 - uac_pph
  buf->parallel_phone = Lt->lt_parallel_phone;
  buf->msg_1          = Lt->out_sdp.Sdp;
  insertExchLst(buf);
  if(__thread_type == 1)  //for parallel phone
   ::PostMessage(Sip->getMFHandle(),SIP_UA_MSG,WM_APP_MSG_WPARAM__UAC,WM_APP_MSG_LPARAM__READLIST_PPH);
  else
   ::PostMessage(Sip->getMFHandle(),SIP_UA_MSG,WM_APP_MSG_WPARAM__UAC,WM_APP_MSG_LPARAM__READLIST);
  }
}
//----------------------------------------------------------------------------
void __fastcall TSipUacThread::Proc_183_Resp(TLegTrn* Lt,TSipParsBuf* spb)
{
if(!Lt)return;
Lt->resp = SPS_RESP183_RCVD;
if(Lt->remotetag.empty())
   Lt->remotetag = spb->totag;
getSDPElements_FromInMsg(Lt,spb);
FindCryptoKeys(Lt,spb);
TExchBuf* buf = new TExchBuf(WM_APP_MSG_WPARAM__UAC);
if(buf)
  {
  buf->emt            = ExchMsgType_Resp183;
  buf->a1             = __thread_type; //0 - normal, 1 - uac_pph
  buf->parallel_phone = Lt->lt_parallel_phone;
  buf->msg_1          = Lt->out_sdp.Sdp;
  TRemoteMedia* rm = new TRemoteMedia;
  if(rm)
    {
    rm->audio_ipaddr = spb->sdp.audio.s_remotertpip;
    rm->audio_port   = spb->sdp.audio.remotertpport;
    rm->callid       = Lt->call_id.getcallid();
    rm->audio_codecs = spb->sdp.audio.codecs;
    buf->setAddBuf(rm);
    Sip->sendInitial_Uac_Rtp_Sequence(RTP_AUDIO_MPT,rm);
    }
  insertExchLst(buf);
  if(__thread_type == 1)  //for parallel phone
   ::PostMessage(Sip->getMFHandle(),SIP_UA_MSG,WM_APP_MSG_WPARAM__UAC,WM_APP_MSG_LPARAM__READLIST_PPH);
  else
   ::PostMessage(Sip->getMFHandle(),SIP_UA_MSG,WM_APP_MSG_WPARAM__UAC,WM_APP_MSG_LPARAM__READLIST);
  }
}
//------------------------------------------------------------------------------
void __fastcall TSipUacThread::Proc_200_Resp(TLegTrn* Lt,TSipParsBuf* spb)
{
if(!Lt)return;
if(spb->CSeq.find("SUBSCRIBE") != -1)
  {
  Proc_202_Resp(Lt,spb);      //Last recommendation asserts that 200 OK equal 202 Accepted and 200Ok on SUBSCRIBE request is rather than 202 Accepted
  return;
  }
if(Proc_200OK_INFO_Responce(spb, Lt))
   return;
switch(Lt->state){
      case SPS_INVITE_REQ:{
           bool chage_call_panel_block = false;
           Lt->resp = SPS_INVITE200OK_RCVD;
           if(!Lt->Referred_CallID.empty())
             {
             if(Sip->uas)
               {
               TLegTrn* Lt_Ref = Sip->uas->getLegTrn(Lt->Referred_CallID);
               if(Lt_Ref)
                 {
                 Lt_Ref->BLOCK_LEG_TRN();
                 send_Next_NOTIFY_AfterReferRcvd(Lt_Ref, "SIP/2.0 200 OK", "terminated;reason=noResource");
                 TMediaSession* ms_Ref = Sip->sss->GetMsIn_by_Callid(Lt_Ref->call_id.getcallid());;
                 if(ms_Ref)
                   {
                   string refer_to_name = get_user_name(Lt->addrreqline);
                   string referred_by   = get_user_name(Lt->ReferredBy);
                   Refresh_CallPanel_C_On_Refer_200OK(ms_Ref, spb, refer_to_name, referred_by);
                   TMediaSession* ms_My = Sip->sss->GetMsOut_by_Callid(Lt->call_id.getcallid());
                   if(ms_My)
                      ms_My->setCallTag(ms_Ref->getCallTag()); //закрепить панель вызова за данной сессией
                   ms_Ref->setCallTag(0);  //"Отстегнуть" Referred медиа-сессию от TCall_Panel
                   ms_Ref->FreeSession();  //Request to MainFormSLS to EraseMediaSession and send Bye
                   chage_call_panel_block = true;
                   }
                 Lt_Ref->UN_BLOCK_LEG_TRN();
                 }
               }
             }
           if(Lt->remotetag.empty())
              Lt->remotetag = spb->totag;
           getSDPElements_FromInMsg(Lt,spb);
           FindCryptoKeys(Lt,spb);
 //          ProcRespCommon(Lt,spb);
           TExchBuf* buf = new TExchBuf(WM_APP_MSG_WPARAM__UAC);
           if(buf)
             {
             buf->emt   = ExchMsgType_200OK_ON_INVITEREQ;
             if(chage_call_panel_block)
               buf->a1 = 1;
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
                    Sip->sendInitial_Uac_Rtp_Sequence(RTP_AUDIO_MPT,rm);
                    }
                   #ifdef SIP_Video
                   if(rm->video_port != -1)
                     if(Lt->out_sdp.video.remotertpport == -1)
                       {
                       prepare_out_video_codec_list(Lt,spb);
                       Sip->sendInitial_Uac_Rtp_Sequence(RTP_VIDEO_MPT,rm);
                       }
                   #endif
               //    ProcRespCommon(Lt,spb);
               }
             if(Lt->lt_parallel_phone)
               {
               buf->parallel_phone = true;
               buf->msg_1          = Lt->lt_parallel_phone_primary_call_id;
               buf->pr_lt_pph      = Lt->primary_legtype_pph;
               }
             else
               {
               buf->msg_1    = spb->sdp.Sdp;         //sdp от 200 OK основного вызова
               if(Lt->source_of_outgoing_call == 1)  //источник вызова - параллельный телефон
                  buf->msg_2 = Lt->pph_call_id;     //callid входящего вызова от параллельного телефона
               }
             ProcRespCommon(Lt,spb);  
             insertExchLst(buf);
             if(__thread_type == 1)  //for parallel phone
              ::PostMessage(Sip->getMFHandle(),SIP_UA_MSG,WM_APP_MSG_WPARAM__UAC,WM_APP_MSG_LPARAM__READLIST_PPH);
             else
              ::PostMessage(Sip->getMFHandle(),SIP_UA_MSG,WM_APP_MSG_WPARAM__UAC,WM_APP_MSG_LPARAM__READLIST);
             } //if(buf)
           break;
           }
      case SPS_INVITE_SCREENSHARING_REQ:
           Lt->resp = SPS_INVITE200OK_RCVD;
           if(Lt->remotetag.empty())
              Lt->remotetag = spb->totag;
           ProcRespCommon(Lt,spb);
           break;
      case SPS_INIT_REGISTER_REQ:{
           TExchBuf* buf = new TExchBuf(WM_APP_MSG_WPARAM__UAC);
           if(buf)
             {
             buf->emt = ExchMsgType_Registered;
             buf->sls_buf = SPS_REGISTER_REQ;
             buf->msg = Sip->Account.get_user_name();
             insertExchLst(buf);
             ::PostMessage(Sip->getMFHandle(),SIP_UA_MSG,WM_APP_MSG_WPARAM__UAC,WM_APP_MSG_LPARAM__READLIST);
             }
           break;
           }
      case SPS_FAILED_REGISTER_REQ:{
           TExchBuf* buf = new TExchBuf(WM_APP_MSG_WPARAM__UAC);
           if(buf)
             {
             buf->emt = ExchMsgType_Registered;
             buf->sls_buf = SPS_REGISTER_REQ;
             buf->msg = Sip->Account.get_user_name();
             insertExchLst(buf);
             ::PostMessage(Sip->getMFHandle(),SIP_UA_MSG,WM_APP_MSG_WPARAM__UAC,WM_APP_MSG_LPARAM__READLIST);
             }
            break;
           }
      case SPS_REGISTER_REQ:{
           TExchBuf* buf = new TExchBuf(WM_APP_MSG_WPARAM__UAC);
           if(buf)
             {
             buf->emt = ExchMsgType_Registered;
             buf->sls_buf = SPS_REGISTER_REQ;
             buf->msg = Sip->Account.get_user_name();
             insertExchLst(buf);
             ::PostMessage(Sip->getMFHandle(),SIP_UA_MSG,WM_APP_MSG_WPARAM__UAC,WM_APP_MSG_LPARAM__READLIST);
             }
           break;
           }
      case SPS_FINAL_REGISTER_REQ:{
           DeleteDialog(Lt);
           ::PostMessage(Sip->getMFHandle(),SIP_UA_MSG,WM_APP_MSG_WPARAM__UAC,WM_APP_MSG_LPARAM__FINAL_REG_END);
           return;
           }
      case SPS_INIT_SUBSCRIBE_REQ:
           DeleteDialog(Lt);
           break;
      case SPS_MESSAGE_REQ:
           DeleteDialog(Lt);
           break;
      case SPS_BYE_REQ:
           DeleteDialog(Lt);
           break;
      }

}
//----------------------------------------------------------------------------
void __fastcall TSipUacThread::Proc_202_Resp(TLegTrn* Lt,TSipParsBuf* spb)
{
if(!Lt)return;
switch(Lt->state){
      case SPS_INIT_SUBSCRIBE_REQ:{
           findCallingParty_ByContactHeader(spb);
           TContact contact(-1);
           if(Sip->Contacts.get_contact_copy_by_user_name(contact,spb->callingParty))
             {
             TExchBuf buf(WM_APP_MSG_WPARAM__NDEF);
             buf.tag    = get_expires_value(spb);
             if(buf.tag == 0)
                {
                TEventLogThread* elt = getLog();
                if(elt){
                   string s = "\nProc_202_Resp: expires = 0, delete subscription to " + contact.name;
                   elt->FputEvt(s);
                   }
                Sip->Contacts.AS.del_subscribed_contact(contact.name);
                }
             else
               {
               buf.tag_1  = get_cseq(spb);
               buf.callid = spb->call_id.getcallid();
               TDateTime next_subcr_time;
               Sip->Contacts.AS.add_subscribed_contact(contact.name, &buf, next_subcr_time);
               TOutputSipBuf* add_buf = new TOutputSipBuf;
               if(add_buf)
                 {
                 buf.msg              = contact.name;
                 add_buf->ToIP        = spb->FromIP;
                 add_buf->ToPort      = spb->FromPort;
                 Sip->prepareRequestLine_SUBSCRIBE(add_buf,contact);
                 add_buf->To          = spb->To;
                 add_buf->from        = spb->From;
                 add_buf->curr_cseq   = buf.tag_1;  //  buf.tag and buf.tag_1 reser in buf.setAddBuf ;
                 buf.setAddBuf(add_buf);
                 Sip->Contacts.AS.add_subscription_parameters(&buf);
                 TDateTime adv = TDateTime(0,0,15,0);
                 next_subcr_time -= adv;
                 if(adv.CurrentDateTime() < next_subcr_time)
                    Sip->Contacts.AS.insert_in_time_list(next_subcr_time, contact.name);
                 }
               }
             }
           DeleteDialog(Lt);
           break;
           }
      }
}
//----------------------------------------------------------------------------
void __fastcall TSipUacThread::Proc_401_Resp(TLegTrn* Lt,TSipParsBuf* spb)
{
if(!Lt)return;
switch(Lt->state){
       case SPS_REGISTER_REQ:
       case SPS_INIT_REGISTER_REQ:
       case SPS_FAILED_REGISTER_REQ:
       case SPS_FINAL_REGISTER_REQ:
            {
            string s = spb->WWWAuthenticate;
            int len = s.length();
            if(len)
              {
              TAuthPar auth_par;
              auth_par.sls        = Lt->state;
              auth_par.rcvdrealm  = getauthel(s,"realm=");
              auth_par.rcvdnonce  = getauthel(s,"nonce=");
              auth_par.rcvdopaque = getauthel(s,"opaque=");

              auth_par.user_name  = Lt->ac_user_name; //Sip->Account.get_user_name();
              auth_par.user_pwd   = Lt->ac_user_pwd;  //Sip->Account.get_user_pwd();
              auth_par.domain     = Lt->ac_domain;    //Sip->Account.get_domain();
              auth_par.callid     = spb->call_id.getcallid();

              Sip->prepare_auth_responce(&auth_par,"REGISTER");
              Sip->sendAuthRegistration(&auth_par);
              } // if(len)
            break;
            }

       case SPS_INVITE_REQ:
       case SPS_INVITE_FILETRANSFER_REQ:
       case SPS_INVITE_SCREENSHARING_REQ:{
            ProcRespCommon(Lt,spb);
            string s = spb->WWWAuthenticate;
            int len = s.length();
            if(len)
              {
              TAuthPar auth_par;
              auth_par.sls        = Lt->state;
              auth_par.rcvdrealm  = getauthel(s,"realm=");
              auth_par.rcvdnonce  = getauthel(s,"nonce=");
              auth_par.rcvdopaque = getauthel(s,"opaque=");

              auth_par.user_name  = Sip->Account.get_user_name();
              auth_par.user_pwd   = Sip->Account.get_user_pwd();
              auth_par.domain     = Sip->Account.get_domain();

              Sip->prepare_auth_responce(&auth_par,"INVITE");
              Sip->sendAuthInvite(&auth_par, spb->call_id.getcallid());
              } //if(len)
            break;
            }
       case SPS_MESSAGE_REQ:{
            string s = spb->WWWAuthenticate;
            int len = s.length();
            if(len)
              {
              TAuthPar auth_par;
              auth_par.sls        = Lt->state;
              auth_par.rcvdrealm  = getauthel(s,"realm=");
              auth_par.rcvdnonce  = getauthel(s,"nonce=");
              auth_par.rcvdopaque = getauthel(s,"opaque=");

              auth_par.user_name  = Sip->Account.get_user_name();
              auth_par.user_pwd   = Sip->Account.get_user_pwd();
              auth_par.domain     = Sip->Account.get_domain();

              Sip->prepare_auth_responce(&auth_par,"MESSAGE");
              Sip->sendAuthMessage(&auth_par, spb->call_id.getcallid());
              } // if(len)
            break;
            }
       }
}
//----------------------------------------------------------------------------
void __fastcall TSipUacThread::Proc_403_Resp(TLegTrn* Lt,TSipParsBuf* spb)
{
if(!Lt)return;
switch(Lt->state){
      case SPS_REGISTER_REQ:
      case SPS_INIT_REGISTER_REQ:
      case SPS_FAILED_REGISTER_REQ:{
                  TResendReqData rrd;
                  ERASE_RESEND_REQUEST(Lt,rrd);
                  TExchBuf* buf = new TExchBuf(WM_APP_MSG_WPARAM__UAC);
                  if(buf)
                    {
                    buf->emt = ExchMsgType_RegisterFailed;
                    buf->msg = Lt->contactusername;
                    buf->tag = 403;
                    insertExchLst(buf);
                    ::PostMessage(Sip->getMFHandle(),SIP_UA_MSG,WM_APP_MSG_WPARAM__UAC,WM_APP_MSG_LPARAM__READLIST);
                    }
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
                  Lt->resendblock.dt       += TDateTime(0,0,REGISTER_FAILED_403_RESEND_INTERVAL,0);
                  Lt->resendblock.resendNum = REGISTER_FAILED_RESEND_COUNT;
                  Lt->resendblock.respNum   = REGISTER_RESPONSE_COUNT;
                  INSERT_RESEND_REQUEST(rrd,Lt);
                  if(Sip->Sip_TransportAuto)
                     Sip->change_sip_transport();
           break;
           }
      case SPS_FINAL_REGISTER_REQ:
           DeleteDialog(Lt);
           ::PostMessage(Sip->getMFHandle(),SIP_UA_MSG,WM_APP_MSG_WPARAM__UAC, WM_APP_MSG_LPARAM__FINAL_REG_END);
           break;
      case SPS_INVITE_REQ:
           ProcRespCommon(Lt,spb);
           send_resp_to_call_panel(Lt,ExchMsgType_NotAcceptable);
           DeleteDialog(Lt);   //Do not replase above
           break;
      }
}
//----------------------------------------------------------------------------
void __fastcall TSipUacThread::Proc_480_Resp(TLegTrn* Lt,TSipParsBuf* spb)
{
if(!Lt)return;
ProcRespCommon(Lt,spb);
send_resp_to_call_panel(Lt,ExchMsgType_Busy);
DeleteDialog(Lt);
}
//---------------------------------------------------------------------------
//--- 481 Responce на SUBSCRIBE. Принятие решения должно производиться
//--- на SIP сервере
//---------------------------------------------------------------------------
void __fastcall TSipUacThread::Proc_481_Resp(TLegTrn* Lt,TSipParsBuf* spb)
{
if(!Lt)return;
if(spb->CSeq.find("SUBSCRIBE") != -1)
  {
  //Sip->reset_OLD_init_NEW_SUBSCRIPTION(Lt->tousername);
  }
DeleteDialog(Lt);
}
//---------------------------------------------------------------------------
void __fastcall TSipUacThread::Proc_486_Resp(TLegTrn* Lt,TSipParsBuf* spb)
{
if(!Lt)return;
ProcRespCommon(Lt,spb);
send_resp_to_call_panel(Lt,ExchMsgType_Busy);
DeleteDialog(Lt);   //Do not replace above
}
//----------------------------------------------------------------------------
void __fastcall TSipUacThread::DisconnectOut(TOutputSipBuf* ospb)
{
TLegTrn* Lt = getLegTrn(ospb->CallID);
if(Lt)
  {
  Lt->BLOCK_LEG_TRN();
  if(Lt->resp == SPS_INVITE200OK_RCVD)
    prepare_UAC_BYE(ospb,Lt);
  else
    prepare_CANCEL(ospb,Lt);
  InitResendProc(ospb,Lt);
  Lt->UN_BLOCK_LEG_TRN();
  }
}
//-----------------------------------------------------------------------------
/*
void __fastcall TSipUacThread::Prepare_200OK_Bye_UAC(BaseExchangeBlock* bb)
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
//-----------------------------------------------------------------------------
void __fastcall TSipUacThread::Prepare_200OK_Notify_On_Subscribe_UAC(TSipParsBuf* spb)
{
Sip->prepareContact(spb);
Sip->prepareUserAgent(spb);
Sip->prepareContentLength_0(spb);
spb->sps = SPS_IMMEDIATE_REQ; //      SPS_200OK_NOTIFY_REQ;
spb->s = SipVers + WS + "200 OK" + crlf;
spb->ViaSt.InsertHeaders(spb->s);spb->s+=
spb->Contact;
if(spb->To.rfind(";tag=") == -1)
  {
  TSipParsBuf temp;
  Sip->generateToTag(&temp);
  int st = spb->To.rfind(">");
  if(st != -1)
    {
    spb->To.resize(st);
    spb->To += ">;tag=" + temp.totag + crlf;
    }
  else
    {
    st = spb->To.rfind(crlf);
    if(st != -1)
      {
      spb->To.resize(st);
      spb->To += ";tag=" + temp.totag + crlf;
      }
    }
  }
spb->s += spb->To +
spb->From         +
spb->CallID       +
spb->CSeq         +
spb->UserAgent    +
spb->ContentLength;
}
//------------------------------------------------------------------------------
void __fastcall TSipUacThread::MessageReq(TOutputSipBuf* ospb)
{
prepareContentLength(ospb);
ospb->s = ospb->requestline   +
          ospb->via           +
          ospb->maxforwards   +
          ospb->To            +
          ospb->from          +
          ospb->callid        +
          ospb->cseq          +
          ospb->allow         +
          ospb->contenttype   +
          ospb->UserAgent     +
          ospb->ContentLength +
          ospb->sdp.Sdp;
TLegTrn* Lt = new TLegTrn(Lt_Out);
if(Lt)
   {
   int st = ospb->requestline.find("sip:");
   if(st != -1)
      Lt->addrreqline = ospb->requestline.substr(st);
   Lt->state        = ospb->getsls();
   Lt->remoteip     = ospb->ToIP;
   Lt->remoteport   = ospb->ToPort;
   Lt->mytag        = ospb->FromTag;
   Lt->Current_CSeq = ospb->curr_cseq;
   Lt->call_id.setprimcallid(ospb->CallID);
   Lt->out_sdp.content_length = ospb->ContentLength;
   Lt->out_sdp.Sdp            = ospb->sdp.Sdp;
   insertLegTrn(ospb->CallID,Lt);
   InitResendProc(ospb,Lt);
   }
}
//------------------------------------------------------------------------------
void __fastcall TSipUacThread::Auth_Register_Req(TOutputSipBuf* ospb,TLegTrn* Lt)
{
if(Lt)
  {
  ospb->s = ospb->requestline;
  Lt->OrigVia.InsertHeaders(ospb->s);ospb->s+=
  ospb->maxforwards           +
  ospb->Contact               +
  ospb->To                    +
  Lt->from                    +

  //Sip->crh.getFrom()          +
  //"Call-ID:" + WS + Sip->crh.getCurrentCallID() +  crlf +

  "Call-ID:" + WS + ospb->callid +  crlf +
  ospb->cseq                  +
  ospb->expires               +
  ospb->allow                 +
  ospb->UserAgent             +
  ospb->authorization         +
  ospb->ContentLength;
  }
}
//------------------------------------------------------------------------------
void __fastcall TSipUacThread::auth_invite_req(TOutputSipBuf* ospb)
{
TLegTrn* Lt = getLegTrn(ospb->callid);
if(Lt)
  {
  Lt->BLOCK_LEG_TRN();
  Lt->prepareNextCSeq("INVITE",ospb);
  ospb->s = "INVITE" + WS + Lt->addrreqline +
  ospb->via         +
  ospb->maxforwards +
  ospb->Contact     +
  Lt->to            +
  Lt->from          +
  "Call-ID:"  + WS  + ospb->callid + crlf +
  ospb->cseq        +
  ospb->allow       +
  Lt->out_sdp.content_type   +
  ospb->UserAgent            +
  ospb->authorization        +
  Lt->ReferredBy             +
  Lt->Replaces               +
  Lt->out_sdp.content_length +
  Lt->out_sdp.Sdp;
  Lt->UN_BLOCK_LEG_TRN();
  }
}
//------------------------------------------------------------------------------
void __fastcall TSipUacThread::auth_message_req(TOutputSipBuf* ospb)
{
TLegTrn* Lt = getLegTrn(ospb->callid);
if(Lt)
  {
  Lt->BLOCK_LEG_TRN();
  Lt->prepareNextCSeq("MESSAGE",ospb);
  ospb->s = "MESSAGE" + WS + Lt->addrreqline +
  ospb->via         +
  ospb->maxforwards +
  ospb->Contact     +
  Lt->to            +
  Lt->from          +
  "Call-ID:"  + WS  + ospb->callid + crlf +
  ospb->cseq        +
  ospb->allow       +
  Lt->out_sdp.content_type   +
  ospb->UserAgent            +
  ospb->authorization        +
  Lt->out_sdp.content_length +
  Lt->out_sdp.Sdp;
  Lt->UN_BLOCK_LEG_TRN();
  }
}
//------------------------------------------------------------------------------
void __fastcall TSipUacThread::send_resp_to_call_panel(TLegTrn* Lt,ExchMsgType Emt)
{
if(!Lt)return;
TExchBuf* buf = new TExchBuf(WM_APP_MSG_WPARAM__UAC);
if(buf)
  {
  buf->emt    = Emt;
  buf->callid = Lt->call_id.getcallid();
  insertExchLst(buf);
  ::PostMessage(Sip->getMFHandle(),SIP_UA_MSG,WM_APP_MSG_WPARAM__UAC,WM_APP_MSG_LPARAM__READLIST);
  }
}
//------------------------------------------------------------------------------
bool __fastcall TSipUacThread::Check_Transport_On_Resend_Proc()
{
TSipSendThread* sst = Sip->getTSipSendThread();
if(sst)return true;

if(Sip->ss_tls_t)
   return Sip->ss_tls_t->r ? true : false;

bool rv  = false;
::EnterCriticalSection(&Sip->tcp_t_cs);
  if(Sip->ss_tcp_t)
     rv  = true;
::LeaveCriticalSection(&Sip->tcp_t_cs);
if(rv)
   return true;

TSipSendTunnelThread* ss_tunnel_t = Sip->getTSipSendTunnelThread();
if(ss_tunnel_t)
   return ss_tunnel_t->r ? true : false;
return true;
}
//-----------------------------------------------------------------------------
bool __fastcall TSipUacThread::Check_Transport_On_Keep_Alive()
{
bool rv = false;
TSipSendThread* sst = Sip->getTSipSendThread();
if(sst)
   rv = true;
return rv;
}
//-----------------------------------------------------------------------------
void __fastcall TSipUacThread::get_notify_xml_parameters(TXmlBuf& buf, TSipParsBuf* spb)
{
if(!spb->sdp.Sdp.empty())
  {
  buf.set_sdp_rcvd(true);
  string ansi_s = spb->sdp.Sdp;
  int en = spb->sdp.Sdp.find("?>");
  if(en != -1)
    {
    int st = spb->sdp.Sdp.find("encoding");
    if(st != -1)
      if(st < en)
        {
        st = spb->sdp.Sdp.find("UTF-8",st);
        if(st != -1)
           ansi_s = UTF8_2_ANSI(spb->sdp.Sdp);
        }
    }
  buf.procSdp(ansi_s);
  }
}
//----------------------------------------------------------------------------
void __fastcall TXmlBuf::procSdp(const string& s)
{
string presence = parsing_block(s,"<presence","</presence>");
if(!presence.empty())
  {
  string tuple  = parsing_block(presence, "<tuple", "</tuple>");
  string person = parsing_block(presence, "<dm:person", "</dm:person>");
  if(!tuple.empty())
    {
    string status = parsing_block(tuple, "<status>", "</status>");
    if(!status.empty())
       Tuple.basic = parsing_block(status, "<basic>", "</basic>");
    }
  if(!person.empty())
    {
    int st = person.find("id=");
    if(st != -1)
      {
      int en = person.find(">",st);
      st += 3;
      if(en > st)
         Person.person = person.substr(st,en-st);
      }
    string activities = parsing_block(person, "<rpid:activities>", "</rpid:activities>");
    if(!activities.empty())
        Person.pars_activities(activities);
     Person.note = parsing_block(person, "<dm:note>", "</dm:note>");
    }
  }
}
//-----------------------------------------------------------------------------
string __fastcall TXmlBuf::parsing_block(const string& s, const string& start_block, const string& end_block)
{
string rv;
int en = s.rfind(end_block);
if(en != -1)
  {
  int st = s.find(start_block);
  if(st != -1)
    {
    st += start_block.length();
    if(st < en)
       rv = s.substr(st,en-st);
    }
  }
return rv;
}
//------------------------------------------------------------------------------
bool  __fastcall TXmlBuf::TPerson::pars_rpid(const string& s,queue<string>& q, int& p)
{
bool rv = false;
int st = s.find("<rpid:",p);
if(st != -1)
  {
  st += 6;
  int en = s.find("/>",st);
  if(st < en)
    {
    string s1 = s.substr(st,en-st);
    st = s1.find(" ");
    if(st != -1)
      s1.resize(st);
    q.push(s1);
    en += 2;
    p = en;
    rv = true;
    }
  }
return rv;
}
//-----------------------------------------------------------------------------
void __fastcall TXmlBuf::TPerson::pars_activities(const string& s)
{
int p = 0;
queue<string> q;
while(pars_rpid(s,q,p));
if(!q.empty())
  {
  activities1 = q.front();
  q.pop();
  if(!q.empty())
    {
    activities2 = q.front();
    q.pop();
    }
  }
}
//------------------------------------------------------------------------------
void __fastcall TSipUacThread::ProcINVITE_Rcvd_UAC(TSipParsBuf* spb)
{
TLegTrn* Lt = getLegTrn(spb->call_id.getcallid());
if(Lt)
  {
  Lt->BLOCK_LEG_TRN();
  if(spb->To.rfind("tag=") != -1) //REINVITE Received
    {
    if(check_on_add_video(Lt, spb))   //REINVITE with add video
      {
      getSDPElements_FromInMsg(Lt,spb); //!!! getSDPElements_FromInMsg(Lt,spb) должен быть после check_on_add_video()
      TExchBuf* buf = new TExchBuf(WM_APP_MSG_WPARAM__UAS);
      if(buf)
        {
        buf->emt    = ExchMsgType_RCVD_REINVITE_WITH_ADD_VIDEO;
        buf->callid = spb->call_id.getcallid();
        buf->setAddBuf(spb);
        spb->incReferenceCount();
        insertExchLst(buf);
        ::PostMessage(Sip->getMFHandle(), SIP_UA_MSG, WM_APP_MSG_WPARAM__UAC, WM_APP_MSG_LPARAM__READLIST);
        }
      Lt->UN_BLOCK_LEG_TRN();  
      return;
      }
    getSDPElements_FromInMsg(Lt,spb);
    if(check_Placed_On_Hold(spb))
      {
      Lt->PLACED_ON_HOLD_BY_REMOTE_PARTY = true;
      TMediaSession* ms = Sip->sss->GetMsOut_by_Callid(spb->call_id.getcallid());
      if(ms)
         ms->set_media_channels_OnHold(true);
      send_place_on_hold_or_resume_to_call_panel(Lt, WM_APP_MSG_WPARAM__UAC, ExchMsgType_Call_OnHold);
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
      TMediaSession* ms = Sip->sss->GetMsOut_by_Callid(spb->call_id.getcallid());
      if(ms)
        {
        TUdpChannel* uc = ms->getSoundChannel();
        if(uc)
          if(uc->wopt)
             uc->wopt->WOS = WaveOutputState_RECEIVING_VOICE;
        ms->set_media_channels_OnHold(false);
        }
      send_place_on_hold_or_resume_to_call_panel(Lt, WM_APP_MSG_WPARAM__UAC, ExchMsgType_Call_Resume);
      TOutputSipBuf* opb = Prepare_200OK_OnReinvite(1, Lt, spb);
      if(opb)
        {
        opb->set_req_to_delete();
        Sip->SetOutQueue(opb);
        }
      }
    }
  Lt->UN_BLOCK_LEG_TRN();
  } //if(Lt)
}
//------------------------------------------------------------------------------

