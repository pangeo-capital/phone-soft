//---------------------------------------------------------------------------

#ifndef SipUserAgentH
#define SipUserAgentH

#include "WinRDefs.h"
#include "BaseThread.h"
#include "SipParsThread.h"
#include "SipResendThread.h"
#include "LegTrn.h"
#include "UserAgent_defs.h"
#include "MediaSession.h"
//---------------------------------------------------------------------------
class TReferToPar{
public:
string refer_to;
string replaces;
string to_tag;
string from_tag;
};
//---------------------------------------------------------------------------
class TSipUserAgentThread : public TBaseThread{
TSip* Sip;
string __fastcall decodeSls(SipLegState);
protected:
SipUAThreadType uatt;
void __fastcall log_ua(const string&);
void __fastcall log_In_QueueSize(const string&);
void __fastcall log_Sent_QueueSize(const string&);
void __fastcall log_Resend_Req_QueueSize(const string&);
void __fastcall log_crypto_keys(const string&,vector<string>&);
void __fastcall CheckResendQueue();
void __fastcall prepareContentLength(BaseExchangeBlock*);
void __fastcall INFO_REQ(TOutputSipBuf*,TLegTrn*);
void __fastcall REINVITE_ONHOLD_REQ(TOutputSipBuf*);
void __fastcall REINVITE_RESUME_REQ(TOutputSipBuf*);
void __fastcall REINVITE_WITH_ADD_VIDEO_REQ(TOutputSipBuf*,TLegTrn*);
void __fastcall INVITE_ON_RCV_FIRST_MIC_PACKET_REQ(TOutputSipBuf*);
void __fastcall InitMediaSession(TLegTrn*, TOutputSipBuf*,int);
void __fastcall InitMediaSession_To_PPH(TLegTrn*, TOutputSipBuf*);   //On Receive INVITE send INVITE to parallel_phone
void __fastcall InitMediaSession_With_PPH__IN_CALL(TLegTrn*, TOutputSipBuf*); //On Receive Answer (200 OK) from parallel phone send Answer to Caller
//void __fastcall InitMediaSession_With_PPH__OUT_CALL(TLegTrn*,TOutputSipBuf*);
void __fastcall InitMediaSession_FileTransfer(TLegTrn*, TOutputSipBuf*);
void __fastcall InitMediaSession_ScreenSharing(TLegTrn*, TOutputSipBuf*);
void __fastcall InitMediaChannels(TLegTrn*,TOutputSipBuf*,TMediaSession*);
void __fastcall prepare_INVITE_Final(TOutputSipBuf*,TUdpChannel*,TUdpChannel*);
void __fastcall prepare_INVITE_Final_For_ScreenSharing(TOutputSipBuf*);
void __fastcall prepare_ANSWER_Final(TLegTrn*,TOutputSipBuf*,TUdpChannel*,TUdpChannel*);
void __fastcall prepare_ANSWER_ON_SHARING_INVITE_Final(TLegTrn*,TOutputSipBuf*);
void __fastcall prepare_Sdp_Final(TSdp*,TUdpChannel*,TUdpChannel*);
void __fastcall prepare_Sdp_Final__for_200OK_On_Reinvite_With_Add_Video_Req(TSdp*,TUdpChannel*);
void __fastcall Create_Media_Channels(TLegTrn*, TOutputSipBuf*, TSessionChannelCollect&);
void __fastcall Create_Video_Channels__For_Transmit_Local_Video(TLegTrn*, BaseExchangeBlock*, TSessionChannelCollect&); //Used in REINVITE sent with add video
void __fastcall Create_Video_Channels__For_Receive_Remote_Video(TLegTrn*, BaseExchangeBlock*, TSessionChannelCollect&); //Used in 200OK on REINVITE rcvd with add video
void __fastcall Connect_Media_Channels(TSessionChannelCollect&);
void __fastcall prepareReqLine_FromReceivedContactHeader(TOutputSipBuf*,const string&,TSipParsBuf*);
void __fastcall prepare_To_ForOutRequest_FromInRequest(TOutputSipBuf*,TSipParsBuf*);
void __fastcall prepare_From_ForOutRequest_FromInRequest(TOutputSipBuf*,TSipParsBuf*);
void __fastcall get_refer_to_parameters(TReferToPar&,const string&);
void __fastcall dissect_filter(queue<string>&,TUdpChannel*);
void __fastcall replace_audio_rtp_port_pph(string& s,TUdpChannel*);
void __fastcall SendInitial_RTP_Seq(TUdpChannel*);
void __fastcall SendInitial_RTCP_Seq(TUdpChannel*);
void __fastcall Log_PrepareInitialRtpSeq(TUdpChannel*,MediaPacketType);
#ifdef Client_Test_Block
void __fastcall Connect_Media_Channels_Test(TSessionChannelCollect&);
#endif
void __fastcall Create_Media_Session(TOutputSipBuf*,TSessionChannelCollect&);
void __fastcall Create_Media_Session_To_PPH(TOutputSipBuf*,TSessionChannelCollect&);
void __fastcall Update_Media_Session(TOutputSipBuf*,TSessionChannelCollect&);
void __fastcall Update_Media_Session__On_Add_Video(const string&,TSessionChannelCollect&);
void __fastcall Create_Media_Session__OnFileTransfer(TOutputSipBuf*);
void __fastcall PREPARE_EGRESS_SRTP_Session(TUdpChannel*);                  //for OUTGOING calls ("INVITE") and RTP TRANSMISSION
void __fastcall PREPARE_INGRESS_SRTP_Session(TUdpChannel*,vector<string>&); //for OUTGOING calls ("200 Ok") and RTP RECEIVING
public:
CRITICAL_SECTION ltl_cs;
TLegTrnList Ltl;
bool     __fastcall insertLegTrn(const string&,TLegTrn*);
void     __fastcall eraseLegTrn(const string&);
TLegTrn* __fastcall find_previously_created_KEEP_ALIVE_leg_trn();
void     __fastcall DeleteDialog(TLegTrn*);
TLegTrn* __fastcall getLegTrn(const string&);
bool     __fastcall isLegTrn(const string&);
int      __fastcall getLegTrnSize();
void     __fastcall clearLegTrn();
void     __fastcall printAllCallId();
void     __fastcall InitResendProc(TOutputSipBuf*,TLegTrn*);

CRITICAL_SECTION rsnd_cs;
queue<TResendReqData> rsnd; //Resend List
void __fastcall setRsnd(const TResendReqData&);
bool __fastcall getRsnd(TResendReqData&);
int  __fastcall getRsndSize();
bool __fastcall IsResendEmpty();
TOutputSipBuf* __fastcall RESEND_PROC(const TResendReqData&);
void  __fastcall ClearResendBlock(TLegTrn*,int,bool=false);
void  __fastcall INSERT_RESEND_REQUEST(TLegTrn*);
void  __fastcall INSERT_RESEND_REQUEST(TOutputSipBuf*);
void  __fastcall INSERT_RESEND_REQUEST(TResendReqData&,TLegTrn*);
void  __fastcall ERASE_RESEND_REQUEST(TLegTrn*);
void  __fastcall ERASE_RESEND_REQUEST(TLegTrn*,int);
void  __fastcall ERASE_RESEND_REQUEST(TLegTrn*,TResendReqData&);

TSipResendThread* srst;

void   __fastcall getSDPElements_FromInMsg(TLegTrn*,TSipParsBuf*);
void   __fastcall FindCryptoKeys(TLegTrn*,TSipParsBuf*);
void   __fastcall getRTPConnectAddr(TSipParsBuf*);
void   __fastcall getMediaParameters(TSipParsBuf*);
void   __fastcall getMediaSubStrParameters(string&,const string&,int&,const);
void   __fastcall pars_m_elements(TSdpMedia&,const string&,const string&,int&,const);
void   __fastcall get_media_crypto_keys(TSdpMedia&,const string&,int);
void   __fastcall getCodecList(vector<int>&,const string&,int&,const);
int    __fastcall getcseq(TSipParsBuf*);
string __fastcall get_user_name(const string&);
int    __fastcall get_expires_value(TSipParsBuf*);
int    __fastcall get_cseq(TSipParsBuf*);
void   __fastcall findCallingParty_ByContactHeader(TSipParsBuf*);
void   __fastcall change_cseq_on_register_failed(string&,int);

bool   __fastcall check_on_add_video(TLegTrn*,TSipParsBuf*);
bool   __fastcall check_Placed_On_Hold(TSipParsBuf*);
void   __fastcall send_place_on_hold_or_resume_to_call_panel(TLegTrn*,WM_APP_MSG_WPARAM,ExchMsgType);
void   __fastcall update_OwnerCreator(vector<string>::iterator&);
void   __fastcall pars_sdp_string(vector<string>&,const string&);
void   __fastcall compile_sdp_string(vector<string>&,string&);
void   __fastcall findCallingParty(TSipParsBuf*);
void   __fastcall prepare_out_audio_codec_list(TLegTrn*,BaseExchangeBlock*);
void   __fastcall prepare_out_video_codec_list(TLegTrn*,BaseExchangeBlock*);


void            __fastcall prepare_REINVITE_HEADRES(TLegTrn*,TOutputSipBuf*);
void            __fastcall prepare_INVITE_Sdp_OnHold_OR_Resume(int,TSdp&);
void            __fastcall prepare_INVITE_sdp_on_reinvite(int,TSdp&,vector<string>&);
void            __fastcall connection_INVITE_Sdp_OnHold(vector<string>::iterator&,TSdp&);
void            __fastcall connection_INVITE_Sdp_OnResume(vector<string>::iterator&,TSdp&);
void            __fastcall direction_INVITE_OnHold(vector<string>::iterator&);
void            __fastcall direction_INVITE_OnResume(vector<string>::iterator&);

TOutputSipBuf*  __fastcall Prepare_200OK_OnReinvite(int,TLegTrn*,TSipParsBuf*);
void            __fastcall prepare_200OK_Sdp_On_REINVITE(int,string&);
void            __fastcall prepare_200ok_sdp_on_reinvite(int,vector<string>&);

void            __fastcall direction_200ok_OnHold(vector<string>::iterator&);
void            __fastcall direction_200ok_OnResume(vector<string>::iterator&);

void            __fastcall Proc_Rcvd_CallTransfer_INVITE(TLegTrn*,TSipParsBuf*);
void            __fastcall Refresh_CallPanel_A_B_On_Refer(TMediaSession*,TSipParsBuf*,const string&);
void            __fastcall Refresh_CallPanel_C_On_Refer_200OK(TMediaSession*,TSipParsBuf*,const string&,const string&);
string          __fastcall get_replaces_callid(const string&);

void            __fastcall Proc_REFER_RCVD(TSipParsBuf*);
void            __fastcall Proc_REGISTER_RCVD(TSipParsBuf*);

void            __fastcall Proc_INFO_RCVD(TSipParsBuf*, SipUAThreadType);
bool            __fastcall Proc_200OK_INFO_Responce(TSipParsBuf*,TLegTrn*);
void            __fastcall Prepare_200OK_COMMON(BaseExchangeBlock*,bool = false);
void            __fastcall Proc_INFO_TEXT_PLAIN(TSipParsBuf*,SipUAThreadType);
void            __fastcall Proc_CONFERENCE_INFO(queue<string>&,TSipParsBuf*,SipUAThreadType);

void            __fastcall send_202_Resp_OnReferRcvd(TSipParsBuf*,TLegTrn*);
void            __fastcall send_First_NOTIFY_OnReferRcvd(TSipParsBuf*,TLegTrn*,const string&);
void            __fastcall send_Next_NOTIFY_AfterReferRcvd(TLegTrn*,const string&,const string&);
void            __fastcall send_INVITE_OnReferRcvd(TLegTrn*,TSipParsBuf*);
void            __fastcall save_NOTIFY_parameters(TLegTrn*,TOutputSipBuf*);

void            __fastcall Proc_200OK_ON_REINVITE_WITH_ADD_VIDEO_REQ(TSipParsBuf*);
void            __fastcall Proc_603_Resp(TLegTrn*,TSipParsBuf*);
void            __fastcall ProcRespCommon(TLegTrn*,TSipParsBuf*);
void            __fastcall PrepareReqURIFromToHeader(TSipParsBuf*);
void            __fastcall PrepareCommonOutACK(TLegTrn*,TSipParsBuf*);
void            __fastcall ConstructReqLine(string&,TSipParsBuf*);
void            __fastcall InsertRouteHeader_1(TRecRouteStruct*,string&);


__fastcall TSipUserAgentThread(bool CS, TEventLogThread** ELTP, SipUAThreadType UATT, TSip* SIP):TBaseThread(CS, ELTP, SIP){
                                             ::InitializeCriticalSection(&ltl_cs);
                                             ::InitializeCriticalSection(&rsnd_cs);
                                             Sip  = SIP;
                                             uatt = UATT;
                                             srst = new TSipResendThread(true,ELTP,UATT,SIP);
                                             }
virtual __fastcall ~TSipUserAgentThread();
};
//---------------------------------------------------------------------------
#endif
