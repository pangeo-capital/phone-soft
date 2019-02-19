//---------------------------------------------------------------------------

#ifndef SipUacThreadH
#define SipUacThreadH

#include "WinRDefs.h"
#include "SipUserAgent.h"

//---------------------------------------------------------------------------
class TSipUacThread : public TSipUserAgentThread{
TSip* Sip;
int  __thread_type; //1 - PPH, 0 - Normal
void __fastcall prepare_CANCEL(TOutputSipBuf*,TLegTrn*);
void __fastcall prepare_UAC_BYE(TOutputSipBuf*,TLegTrn*);
void __fastcall DisconnectOut(TOutputSipBuf*);
void __fastcall MessageReq(TOutputSipBuf*);
void __fastcall Auth_Register_Req(TOutputSipBuf*,TLegTrn*);
void __fastcall auth_invite_req(TOutputSipBuf*);
void __fastcall auth_message_req(TOutputSipBuf*);
void __fastcall send_resp_to_call_panel(TLegTrn*,ExchMsgType);
bool __fastcall Check_Transport_On_Resend_Proc();
bool __fastcall Check_Transport_On_Keep_Alive();
public:
void __fastcall Proc_Resp_UAC(TSipParsBuf*);
void __fastcall Proc_100_Resp(TLegTrn*,TSipParsBuf*);
void __fastcall Proc_180_Resp(TLegTrn*,TSipParsBuf*);
void __fastcall Proc_183_Resp(TLegTrn*,TSipParsBuf*);
void __fastcall Proc_200_Resp(TLegTrn*,TSipParsBuf*);
void __fastcall Proc_202_Resp(TLegTrn*,TSipParsBuf*);
void __fastcall Proc_401_Resp(TLegTrn*,TSipParsBuf*);
void __fastcall Proc_403_Resp(TLegTrn*,TSipParsBuf*);
void __fastcall Proc_480_Resp(TLegTrn*,TSipParsBuf*);
void __fastcall Proc_481_Resp(TLegTrn*,TSipParsBuf*);
void __fastcall Proc_486_Resp(TLegTrn*,TSipParsBuf*);
void __fastcall Proc_487_Resp(TLegTrn*,TSipParsBuf*);
void __fastcall ProcBye_UAC(TSipParsBuf*);
void __fastcall ProcNotify_UAC(TSipParsBuf*);
void __fastcall ProcINVITE_Rcvd_UAC(TSipParsBuf*);
void   __fastcall get_notify_xml_parameters(TXmlBuf&,TSipParsBuf*);
string __fastcall get_subscription_state_reason(const string&);

//void __fastcall Prepare_200OK_Bye_UAC(BaseExchangeBlock*);
void __fastcall Prepare_200OK_Notify_On_Subscribe_UAC(TSipParsBuf*);

void __fastcall INIT_RTP_AUDIO_SEQ__UAC(TOutputSipBuf*);
void __fastcall INIT_RTCP_AUDIO_SEQ__UAC(TOutputSipBuf*);
void __fastcall INIT_RTP_VIDEO_SEQ__UAC(TOutputSipBuf*);

__fastcall TSipUacThread(bool CS, TEventLogThread** ELTP, TSip* SIP, int THREAD_TYPE):TSipUserAgentThread(CS, ELTP, SipUAThreadType_UAC, SIP){
                                             Sip = SIP;
                                           __thread_type = THREAD_TYPE;  // 0 - PPH, 1 - Normal
                                             }
virtual __fastcall ~TSipUacThread();
void __fastcall Execute();
};
//---------------------------------------------------------------------------
#endif
