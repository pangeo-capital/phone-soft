//---------------------------------------------------------------------------

#ifndef SipUasThreadH
#define SipUasThreadH

#include "WinRDefs.h"
#include "SipUserAgent.h"
//---------------------------------------------------------------------------
class TSipUasThread : public TSipUserAgentThread{
TSip* Sip;
int  __thread_type; //1 - PPH, 0 - Normal
void __fastcall Proc_TSipParsBuf(BaseExchangeBlock*);
void __fastcall Proc_TOutputSipBuf(BaseExchangeBlock*);
void __fastcall find_CallingParty_And_DisplayName(TSipParsBuf*);
void __fastcall findCallingDomain_ByFromHeader(TSipParsBuf*,string&);
void __fastcall prepare_UAS_BYE(TOutputSipBuf*,TLegTrn*);
void __fastcall prep_Final_Presence_Notify_Req(TLegTrn*,TOutputSipBuf*);
void __fastcall prepare_Resp180_Final(TSipParsBuf*);
void __fastcall prepare486_Busy_OnDecline(TLegTrn*,TOutputSipBuf*);
void __fastcall ProcBye_UAS(TSipParsBuf*);
//void __fastcall Prepare_200OK_Bye_UAS(BaseExchangeBlock*);
void __fastcall Prepare_200OK_Cancel_UAS(TSipParsBuf*,TLegTrn*);
//void __fastcall Prepare_200OK_MESSAGE_UAS(BaseExchangeBlock*);
void __fastcall sendUas_202_OnSubscribe(TSipParsBuf*,TLegTrn*);
void __fastcall sendUas_603_OnSubscribe(TSipParsBuf*,TLegTrn*);
void __fastcall prepare_To(string&,const string&);
void __fastcall prepare_From(string&,const string&);
void __fastcall DisconnectIn(TOutputSipBuf*);

void __fastcall Proc_Invite_UAS(TSipParsBuf*);
void __fastcall Proc_Subscribe_UAS(TSipParsBuf*);
void __fastcall Proc_Cancel_UAS(TSipParsBuf*);
void __fastcall Proc_Message_UAS(TSipParsBuf*);
void __fastcall Proc_Resp_UAS(TSipParsBuf*);
void __fastcall Proc_REGISTER200OK_REQ(TSipParsBuf*); //For parallel phone
void __fastcall proc_ringing_req(TSipParsBuf*);
void __fastcall create_session(TSipParsBuf*);

void __fastcall INIT_RTP_AUDIO_SEQ__UAS(TLegTrn*,TOutputSipBuf*);
void __fastcall INIT_RTCP_AUDIO_SEQ__UAS(TLegTrn*,TOutputSipBuf*);
void __fastcall INIT_RTP_VIDEO_SEQ__UAS(TLegTrn*,TOutputSipBuf*);

void __fastcall prepare_notify_request_line(TLegTrn*,TOutputSipBuf*);
void __fastcall return_network_notify_parameters(TOutputSipBuf*);
void __fastcall prepare_from_to_from_incoming_request(TLegTrn*,TOutputSipBuf*);

public:
__fastcall TSipUasThread(bool CS, TEventLogThread** ELTP, TSip* SIP, int THREAD_TYPE):TSipUserAgentThread(CS, ELTP, SipUAThreadType_UAS, SIP){
                                             Sip = SIP;
                                           __thread_type = THREAD_TYPE;  // 0 - PPH, 1 - Normal
                                             }
virtual __fastcall ~TSipUasThread();
void    __fastcall Execute();
};
//---------------------------------------------------------------------------


#endif
