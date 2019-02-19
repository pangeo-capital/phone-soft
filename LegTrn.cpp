//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "LegTrn.h"
#include "Sip.h"
#pragma package(smart_init)

extern USC_Fxns USC_G7291_Fxns;
extern USC_Fxns USC_G729I_Fxns;
extern USC_Fxns USC_G729A_Fxns;
extern USC_Fxns USC_G729IFP_Fxns;
//---------------------------------------------------------------------------
void __fastcall TLegTrn::PrepareResendBlock(TOutputSipBuf* ospb)
{
resendblock.ToIP   = ospb->ToIP;
resendblock.ToPort = ospb->ToPort;
resendblock.sls    = ospb->getsls();
resendblock.s      = ospb->s;
resendblock.dt     = resendblock.dt.CurrentDateTime();
switch(resendblock.sls){
      case SPS_INIT_REGISTER_REQ:
           resendblock.dt       += TDateTime(0,0,0,REGISTER_INITIAL_RESEND_INTERVAL);
           resendblock.resendNum = REGISTER_INITIAL_RESEND_COUNT;
           resendblock.respNum   = REGISTER_RESPONSE_COUNT;
           break;
      case SPS_REGISTER_REQ:{
           resendblock.dt       += sec_to_date_time(ospb->get_reg_tag());   // get_reg_tag() - in sec
           resendblock.resendNum = REGISTER_RESEND_COUNT;
           resendblock.respNum   = REGISTER_RESPONSE_COUNT;
           break;
           }
      case SPS_FINAL_REGISTER_REQ:
           resendblock.dt       += TDateTime(0,0,0,REGISTER_FINAL_RESEND_INTERVAL);
           resendblock.resendNum = REGISTER_FINAL_RESEND_COUNT;
           resendblock.respNum   = REGISTER_RESPONSE_COUNT;
           break;
      case SPS_INIT_SUBSCRIBE_REQ:
           resendblock.dt       += TDateTime(0,0,SUBSCRIBE_INITIAL_RESEND_INTERVAL,0);
           resendblock.resendNum = SUBSCRIBE_INITIAL_RESEND_COUNT;
           resendblock.respNum   = SUBSCRIBE_RESPONSE_COUNT;
           break;
      case SPS_PRESENCE_NOTIFY_REQ:
           resendblock.dt       += TDateTime(0,0,NOTIFY_RESEND_INTERVAL,0);
           resendblock.resendNum = NOTIFY_RESEND_COUNT;
           resendblock.respNum   = NOTIFY_RESPONSE_COUNT;
           break;
      case SPS_MESSAGE_REQ:
           resendblock.dt       += TDateTime(0,0,MESSAGE_RESEND_INTERVAL,0);
           resendblock.resendNum = MESSAGE_RESEND_COUNT;
           resendblock.respNum   = MESSAGE_RESPONSE_COUNT;
           break;
      case SPS_INVITE_REQ:
      case SPS_INVITE_FILETRANSFER_REQ:
      case SPS_INVITE_SCREENSHARING_REQ:
           resendblock.dt       += TDateTime(0,0,0,INVITE_RESEND_INTERVAL);
           resendblock.resendNum = INVITE_RESEND_COUNT;
           resendblock.respNum   = INVITE_RESPONSE_COUNT;
           break;
      case SPS_CANCEL_REQ:
           resendblock.dt       += TDateTime(0,0,0,CANCEL_RESEND_INTERVAL);
           resendblock.resendNum = CANCEL_RESEND_COUNT;
           resendblock.respNum   = CANCEL_RESPONSE_COUNT;
           break;
      case SPS_BYE_REQ:
           resendblock.dt       += TDateTime(0,0,0,BYE_RESEND_INTERVAL);
           resendblock.resendNum = BYE_RESEND_COUNT;
           resendblock.respNum   = BYE_RESPONSE_COUNT;
           break;
      case SPS_DECLINE_REQ:
           resendblock.dt       += TDateTime(0,0,0,DEFAULT_RESEND_INTERVAL);
           resendblock.resendNum = DECLINE_RESEND_COUNT;
           resendblock.respNum   = DEFAULT_RESPONSE_COUNT;
           break;
      case SPS_WAIT_FINAL_RESP:
           resendblock.dt       += TDateTime(0,0,WAIT_FINAL_RESPONSE,0);
           resendblock.resendNum = 0;
           resendblock.respNum   = 1;
           break;
      case SPS_KEEP_ALIVE:
           resendblock.dt       += TDateTime(0,0,KEEP_ALIVE_RESEND_INTERVAL,0);
           resendblock.resendNum = KEEP_ALIVE_RESEND_COUNT;
           resendblock.respNum   = DEFAULT_RESPONSE_COUNT;
           break;
      default:
           resendblock.dt       += TDateTime(0,0,0,DEFAULT_RESEND_INTERVAL);
           resendblock.resendNum = DEFAULT_RESEND_COUNT;
           resendblock.respNum   = DEFAULT_RESPONSE_COUNT;
           break;
      }
}
//---------------------------------------------------------------------------
void __fastcall TLegTrn::UpdateResendInterval()
{
switch(resendblock.sls){
       case SPS_INIT_REGISTER_REQ:{
            if(resendblock.sls_aux == SPS_WAIT_200OK_REGISTER)
               resendblock.dt += TDateTime(0,0,REGISTER_WAIT_200OK_RESEND_INTERVAL,0); //20 sec
            else
               resendblock.dt += TDateTime(0,0,0,REGISTER_INITIAL_RESEND_INTERVAL);   //500 ms
            }
            break;
       case SPS_FAILED_REGISTER_REQ:
            resendblock.dt += TDateTime(0,0,REGISTER_FAILED_RESEND_INTERVAL,0);
            break;
       case SPS_REGISTER_REQ:{
            if(resendblock.sls_aux == SPS_WAIT_200OK_REGISTER)
               resendblock.dt += TDateTime(0,0,REGISTER_WAIT_200OK_RESEND_INTERVAL,0);  //20 sec
            else
               resendblock.dt += TDateTime(0,0,0,REGISTER_RESEND_INTERVAL);            //500 ms
            }
            break;
       case SPS_FINAL_REGISTER_REQ:
            resendblock.dt += TDateTime(0,0,0,REGISTER_FINAL_RESEND_INTERVAL);
            break;
       case SPS_INIT_SUBSCRIBE_REQ:
            resendblock.dt += TDateTime(0,0,SUBSCRIBE_INITIAL_RESEND_INTERVAL,0);
            break;
       case SPS_PRESENCE_NOTIFY_REQ:
            resendblock.dt += TDateTime(0,0,NOTIFY_RESEND_INTERVAL,0);
            break;
       case SPS_MESSAGE_REQ:
            resendblock.dt += TDateTime(0,0,MESSAGE_RESEND_INTERVAL,0);
            break;
       case SPS_INVITE_REQ:
       case SPS_INVITE_FILETRANSFER_REQ:
       case SPS_INVITE_SCREENSHARING_REQ:
            resendblock.dt += TDateTime(0,0,0,INVITE_RESEND_INTERVAL);
            break;
       case SPS_CANCEL_REQ:
            resendblock.dt += TDateTime(0,0,0,CANCEL_RESEND_INTERVAL);
            break;
       case SPS_BYE_REQ:
            resendblock.dt += TDateTime(0,0,0,BYE_RESEND_INTERVAL);
            break;
       case SPS_DECLINE_REQ:
            resendblock.dt += TDateTime(0,0,0,DEFAULT_RESEND_INTERVAL);
            break;
       case SPS_KEEP_ALIVE:
            resendblock.dt += TDateTime(0,0,KEEP_ALIVE_RESEND_INTERVAL,0);
            resendblock.resendNum = KEEP_ALIVE_RESEND_COUNT;
            break;
       default:
            resendblock.dt += TDateTime(0,0,0,DEFAULT_RESEND_INTERVAL);
            break;
       }
}
//---------------------------------------------------------------------------
int __fastcall TLegTrn::prepareNextCSeq(const string& MSG,TOutputSipBuf* ospb)
{
int rv = ++Current_CSeq;
ospb->cseq = "CSeq:" + WS + inttostr(rv) + WS + MSG + crlf;
return rv;
}
//---------------------------------------------------------------------------
void __fastcall TLegTrn::prepareReqLine_FromRemoteContact()
{
int st = contact.find("sip:");
if(st!=-1)
  {
  st+=4;
  if(contact.size() > (unsigned)st)
    {
    int en = contact.find(">",st);
    if(en!=-1)
       addrreqline = contact.substr(st,en-st);
    else
       {
       en = contact.find(crlf,st);
       if(en!=-1)
          addrreqline = contact.substr(st,en-st);
       else
          addrreqline = contact.substr(st);
       }
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TLegTrn::prepare_init_rtp_seq__uas(TSip* Sip,MediaPacketType mpt)
{
TUdpChannelStruct* ucs = Sip->ucs;
TUdpChannel* uc        = NULL;
TSdp* ptSdp = &out_sdp;
if(!ptSdp)NULL;
TSdpMedia* ptSdpMedia = NULL;
if(mpt == RTP_AUDIO_MPT)
  {
  ptSdpMedia = &ptSdp->audio;
  if(ch_rtp_audio != -1)
     uc = ucs->getUdpChannel(ch_rtp_audio);
  }
#ifdef SIP_Video
else if(mpt == RTP_VIDEO_MPT)
  {
  ptSdpMedia = &ptSdp->video;
  if(ch_rtp_video != -1)
      uc = ucs->getUdpChannel(ch_rtp_video);
  }
#endif
if(uc)
  if(uc->sendThread)
    {
    uc->sendThread->setRemoteAddress(ptSdpMedia->s_remotertpip,ptSdpMedia->remotertpport);
    if(!ptSdpMedia->codecs.empty())
        uc->sendThread->remoteCodec = ptSdpMedia->codecs[0];
    randomize();
    uc->sendThread->currentSeqNumber = get_random32(0) & 0xFFFF; //random(0xFFFF);
    uc->sendThread->sourceId         = get_random32(1); //random(0x7FFFFFFF);  //get_random32(0) & 0xFFFF;
    uc->sendThread->currentTimeStamp = GetTickCount();
    switch(uc->sendThread->remoteCodec){
            case 18:{
                    TG729ENC* G729ENC = uc->sendThread->CREATE_G729_IPP_ENCODER();     //for UAS (Incoming Call)
                    if(G729ENC)
                       G729ENC->init_encoder(&USC_G7291_Fxns,320);
                    TG729DEC* G729DEC = uc->CREATE_G729_IPP_DECODER();
                    if(G729DEC)
                       G729DEC->init_decoder(&USC_G7291_Fxns,320);
                    break;
                    }
          }
    }
}
//------------------------------------------------------------------------------
void __fastcall TLegTrn::prepare_init_rtcp_audio_seq__uas(TSip* Sip)
{
if(ch_rtcp_audio != -1)
  {
  TUdpChannel* uc = Sip->ucs->getUdpChannel(ch_rtcp_audio);
  if(uc)
    if(uc->sendThread)
       uc->sendThread->setRemoteAddress(out_sdp.audio.s_remotertpip, out_sdp.audio.remotertpport + 1);
  }
}
//------------------------------------------------------------------------------
bool __fastcall TCryptoKeys::get_crypto_list_audio(vector<string>& v){
                                            bool rv = false;
                                            if(CryptoList_AUDIO)
                                              {
                                              v = CryptoList_AUDIO->v;
                                              delete CryptoList_AUDIO;
                                              CryptoList_AUDIO = NULL;
                                              rv = true;
                                              }
                                            return rv;
                                            }
//------------------------------------------------------------------------------
bool __fastcall TCryptoKeys::get_crypto_list_video(vector<string>& v){
                                            bool rv = false;
                                            if(CryptoList_VIDEO)
                                              {
                                              v = CryptoList_VIDEO->v;
                                              delete CryptoList_VIDEO;
                                              CryptoList_VIDEO = NULL;
                                              rv = true;
                                              }
                                            return rv;
                                            }
//------------------------------------------------------------------------------
void __fastcall TCryptoKeys::set_crypto_list_audio(const vector<string>& v)
{
if(!CryptoList_AUDIO)
    CryptoList_AUDIO = new TCryptoList;
CryptoList_AUDIO->v = v;
}
//------------------------------------------------------------------------------
void __fastcall TCryptoKeys::set_crypto_list_video(const vector<string>& v)
{
if(!CryptoList_VIDEO)
    CryptoList_VIDEO = new TCryptoList;
CryptoList_VIDEO->v = v;
}
//------------------------------------------------------------------------------
bool __fastcall TLegTrn::request_srtp(SRTP_TYPE ST, SRTP_KEY_ACTION SKA, vector<string>& v)
{
if(SKA == SK_GET)
  {
  if(CryptoKeys){
       switch(ST){
       case SRTP_TYPE_AUDIO:
            return CryptoKeys->get_crypto_list_audio(v);
       case SRTP_TYPE_VIDEO:
            return CryptoKeys->get_crypto_list_video(v);
       }
    }
  return false;
  }
if(!CryptoKeys)    //SKA == SK_SET
    CryptoKeys = new TCryptoKeys;
switch(ST){
      case SRTP_TYPE_AUDIO:
           CryptoKeys->set_crypto_list_audio(v);
           break;
      case SRTP_TYPE_VIDEO:
           CryptoKeys->set_crypto_list_video(v);
           break;
      }
return false;
}
//------------------------------------------------------------------------------
void __fastcall TSipInfo::Ins_CSeq_Info(int cseq, TCSeqInfo& CSI)
{
Check_Expiration();
if(icl.find(cseq) == icl.end())
  {
  CSI.init_dt();
  icl.insert(TInfoCSeqList::value_type(cseq, CSI));
  }
}
//------------------------------------------------------------------------------
bool __fastcall TSipInfo::Get_CSeq_Info(int cseq, TCSeqInfo& CSI)
{
bool rv = false;
TInfoCSeqList::iterator it = icl.find(cseq);
if(it != icl.end())
  {
  CSI = (*it).second;
  icl.erase(it);  //Responce received
  rv = true;
  }
return rv;
}
//------------------------------------------------------------------------------
void __fastcall TSipInfo::Check_Expiration()
{
TDateTime current_dt = current_dt.CurrentDateTime();
TInfoCSeqList::iterator it = icl.begin();
while(it != icl.end())
     {
     if((current_dt - (*it).second.get_dt()) > TDateTime(0,0,10,0))
       {
       icl.erase(it);
       it = icl.begin();  //Responce NOT received in elapsed time. Delete this CSeq from waiting responce list
       continue;
       }
     it++;
     }
}
//------------------------------------------------------------------------------
