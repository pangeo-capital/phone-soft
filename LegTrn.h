#ifndef LegTrn_H
#define LegTrn_H

#include "WinRDefs.h"
#include "OutPutSipBuf.h"
#include "MediaChannels.h"

const REGISTER_FAILED_RESEND_COUNT      = 0xFFFFFFFF;
const REGISTER_WAIT_200OK_RESEND_COUNT  = 0xFFFFFFFF;
const KEEP_ALIVE_RESEND_COUNT           = 0xFFFFFFFF;
const REGISTER_INITIAL_RESEND_COUNT     = 12;
const REGISTER_RESEND_COUNT             = 12;
const REGISTER_FINAL_RESEND_COUNT       = 4;
const SUBSCRIBE_INITIAL_RESEND_COUNT    = 12;
const NOTIFY_RESEND_COUNT               = 12;
const MESSAGE_RESEND_COUNT              = 12;
const INVITE_RESEND_COUNT               = 12;
const BYE_RESEND_COUNT                  = 12;
const CANCEL_RESEND_COUNT               = 7;
const DEFAULT_RESEND_COUNT              = 7;
const DECLINE_RESEND_COUNT              = 12;

const REGISTER_RESPONSE_COUNT  = 1;
const SUBSCRIBE_RESPONSE_COUNT = 1;
const NOTIFY_RESPONSE_COUNT    = 1;
const MESSAGE_RESPONSE_COUNT   = 1;
const INVITE_RESPONSE_COUNT    = 1;
const BYE_RESPONSE_COUNT       = 1;
const CANCEL_RESPONSE_COUNT    = 2;
const DEFAULT_RESPONSE_COUNT   = 1;

const REGISTER_INITIAL_RESEND_INTERVAL    = 500; //ms  Don't set 1000 and more msec - Exception !!!
const REGISTER_INITIAL_RESEND_INTERVAL_1  = 1;  //sec!!!  Don't set 60 and more sec - Exception !!!
const REGISTER_INITIAL_RESEND_INTERVAL_2  = 2;  //sec!!!  Don't set 60 and more sec - Exception !!!
const REGISTER_FAILED_RESEND_INTERVAL     = 20; //sec!!!  Don't set 60 and more sec - Exception !!!
const REGISTER_WAIT_200OK_RESEND_INTERVAL = 20; //sec!!!
const REGISTER_FAILED_403_RESEND_INTERVAL = 59; //sec!!!  Don't set 60 and more sec - Exception !!!
const REGISTER_RESEND_INTERVAL            = 500; //ms  Don't set 1000 and more msec - Exception !!!
const REGISTER_FINAL_RESEND_INTERVAL      = 500; //ms  Don't set 1000 and more msec - Exception !!!
const SUBSCRIBE_INITIAL_RESEND_INTERVAL   = 2;   //sec!!!Don't set 60 and more sec - Exception !!!
const NOTIFY_RESEND_INTERVAL              = 2;   //sec!!!Don't set 60 and more sec - Exception !!!
const MESSAGE_RESEND_INTERVAL             = 1;   //sec!!!Don't set 60 and more sec - Exception !!!
const INVITE_RESEND_INTERVAL              = 500; //ms  Don't set 1000 and more msec - Exception !!!
const INVITE_RESEND_INTERVAL_1            = 1;   //sec!!!  Don't set 60 and more sec - Exception !!!
const INVITE_RESEND_INTERVAL_2            = 2;   //sec!!!  Don't set 60 and more sec - Exception !!!
const INVITE_RESEND_AFTER_100_RESP_INTERVAL  = 1; //sec
const BYE_RESEND_INTERVAL      = 500; //ms  Don't set 1000 and more msec - Exception !!!
const CANCEL_RESEND_INTERVAL   = 500; //ms  Don't set 1000 and more msec - Exception !!!
const DEFAULT_RESEND_INTERVAL  = 500; //ms  Don't set 1000 and more msec - Exception !!!
const KEEP_ALIVE_RESEND_INTERVAL = 20; //30; //sec !!!  Don't set 60 and more sec - Exception !!! 20 sec normal for Megafon, 30 - lost of route (defined new port) 
const WAIT_487_RESPONSE        = 32;  //sec -- 64*T1 (see RFC 3261) //!!!  Don't set 60 and more sec - Exception !!!
const WAIT_FINAL_RESPONSE      = 59;  //sec !!!  Don't set 60 and more sec - Exception !!!
const WAIT_DEFAULT             = 32;  //sec !!!  Don't set 60 and more sec - Exception !!!
//---------------------------------------------------------------------------
typedef enum{
Lt_In,
Lt_Out,
Lt_NDef,
}LegType;   //In the SipClient Lt_In equal Uas Lt_Out - Uac
//---------------------------------------------------------------------------
typedef enum{
SRTP_TYPE_AUDIO,
SRTP_TYPE_VIDEO,
}SRTP_TYPE;
//---------------------------------------------------------------------------
typedef enum{
SK_GET,
SK_SET,
}SRTP_KEY_ACTION;
//---------------------------------------------------------------------------
class TAuth{
public:
string realm;
string nonce;
string opaque;
string pwd;
bool   __fastcall authenticate(const string&,const string&);
string __fastcall getauthel(const string&,const string&);
};
//-----------------------------------------------------------------------------
class TRefer{
public:
string To;
string From;
string ToUserName;
string CallID;
string ContactName;
string ContactHost;
string ContactPort;
string ReferToName;
string ReferToHost;
string ReferredByName;
string ReferredByHost;
string ReferTo;
string ReferredBy;
};
//------------------------------------------------------------------------------
//-- Использ в процессе переадресации REFER - NOTIFY ---------------------------
//------------------------------------------------------------------------------
class TReferNOTIFY{
public:
string ToIP;
int    ToPort;
string RequestLine;
string Contact;
string To;
string From;
string CallID;
__fastcall TReferNOTIFY(){ToPort = 0;}
};
//------------------------------------------------------------------------------
class TCSeqInfo{
TDateTime dt;
public:
string    user_name;
void      init_dt(){dt = dt.CurrentDateTime();}
TDateTime get_dt(){return dt;}
};
//--------------------------------------------------------------------------------------------
//---- Not need any CRITICAL_SECTION because TSipInfo used only in the TLegTrn which
//---- always processed inside of CRITICAL_SECTION lt_cs (BLOCK_LEG_TRN(), UN_BLOCK_LEG_TRN())
//---------------------------------------------------------------------------------------------
class TSipInfo{
typedef map <int, TCSeqInfo >  TInfoCSeqList;   //int - this is digit CSeq from ougoing INFO msg, TCSeqInfo содержит информацию из входящего сообщения
TInfoCSeqList icl;
public:
void __fastcall Ins_CSeq_Info(int,TCSeqInfo&);
bool __fastcall Get_CSeq_Info(int,TCSeqInfo&);
void __fastcall Check_Expiration();
};
//------------------------------------------------------------------------------
class TSipMessage{
public:
std::queue<string> q;
string ReqLine;
string To;
string From;
int CSeq;
__fastcall TSipMessage(){
                        CSeq=0;
                        }
};
//------------------------------------------------------------------------------
class TSubscribe{
string branch;
string fromtag;
public:
string RequestLine;
string CallID;
string Via;
string From;
string To;
string Contact;
string Event;
void __fastcall PrepareSubscriptionBranch(int,int);
void __fastcall PrepareRequestLine(void*);
void __fastcall PrepareVia(const string&);
void __fastcall PrepareCallID(void*);
void __fastcall PrepareFrom(void*);
void __fastcall PrepareTo(void*);
//void __fastcall PrepareContact(void*,const string&,const string&);
void __fastcall PrepareEvent();
};
//------------------------------------------------------------------------------
class TMime{
public:
string ContentType_Main;
string boundary;
vector <unsigned char> mime;
vector <unsigned char> outbuf;
__fastcall TMime();
};
//------------------------------------------------------------------------------
class TResendBlock{
public:
string s;
string ToIP;
int ToPort;
TDateTime dt; //Time of the next resend (== TDateTime in the TOutSipResendBlock)
SipLegState sls;
SipLegState sls_aux;
unsigned resendNum; //Number of resend;
int respNum;   //Number of responses should be received before delete record rom the list
int repeat_count;
__fastcall TResendBlock(){sls = SPS_UNKNOWN; sls_aux = SPS_UNKNOWN;
                          ToPort=0;resendNum=0;respNum=0;repeat_count = 2;}
};
//------------------------------------------------------------------------------
class TCryptoList{
public:
vector<string> v;
};
//------------------------------------------------------------------------------
class TCryptoKeys{
TCryptoList* CryptoList_AUDIO;
TCryptoList* CryptoList_VIDEO;
public:
bool __fastcall get_crypto_list_audio(vector<string>&);
bool __fastcall get_crypto_list_video(vector<string>&);
void __fastcall set_crypto_list_audio(const vector<string>&);
void __fastcall set_crypto_list_video(const vector<string>&);
__fastcall TCryptoKeys(){
                        CryptoList_AUDIO = NULL;
                        CryptoList_VIDEO = NULL;
                        }
virtual __fastcall ~TCryptoKeys(){
                                 if(CryptoList_AUDIO)
                                   delete CryptoList_AUDIO;
                                 if(CryptoList_VIDEO)
                                   delete CryptoList_VIDEO;
                                 }
};
//------------------------------------------------------------------------------
class TLegTrn{
TDateTime dt;
TCryptoKeys* CryptoKeys;
CRITICAL_SECTION lt_cs;
public:
void BLOCK_LEG_TRN(){
                    ::EnterCriticalSection(&lt_cs);
                    }
void UN_BLOCK_LEG_TRN(){
                    ::LeaveCriticalSection(&lt_cs);
                    }
string remoteip;       //SIP (not rtp)
int    remoteport;     //SIP (not rtp)
LegType legtype;
SipLegState state;  //Requests
SipLegState resp;   //Responces
bool resp183SdpRcvd;
string cseqrcvd;
string cseqrcvd_200OK;
int Current_CSeq;
int CSeq_NOTIFY;
//int CSeq_INFO;
unsigned refNum;
bool block_BYE;
bool keepalive;
string keepalive_callid;
string to;
string from;
string contact;
string tousername;
string tohostname;
string fromusername;
string fromhostname;
string contactusername;
string contacthostname;
string contactport;
string ReferredBy;
string Replaces;
string Referred_CallID; //CallID по которому получен REFER (для последующих передач сообщений NOTIFY переадресовавшему абоненту (секретарю))
//string origaddrreqline; //on Invite send origaddrreqline = addrreqline. Used for Constructed ACK msg for non 2xx responses (for instance 488)(see RFC 3261 17.1.1.3)
string addrreqline;
TCallID call_id;     //string callid;
//TCallID bindcall_id; //string bindcall-id
//TCallID bind_msg_call_id;
string out_Contact;
TViaStruct OrigVia;
TRecRouteStruct RecordRoute;
//string itag; //inLeg  Transaction
//string otag; //outLeg Transaction
string mytag;
string remotetag;
string ac_user_name;
string ac_user_pwd;
string ac_domain;
bool PLACED_ON_HOLD_BY_LOCAL_PARTY;
bool PLACED_ON_HOLD_BY_REMOTE_PARTY;
TAuth*        Auth;
TReferNOTIFY* ReferNOTIFY;
TSipInfo*     INFO;
TSipMessage*  Message;
TSubscribe*   Subscribe;
TMime*        Mime;
//string in_media;             //from INVITE on incoming Sip Leg  and from 200OK on outgoing Sip Leg
unsigned remote_in_audio_ip; //from INVITE on incoming Sip Leg  and from 200OK on outgoing Sip Leg
int remote_in_audio_port;    //from INVITE on incoming Sip Leg  and from 200OK on outgoing Sip Leg
//string in_media_1;//for m=video for instance
string out_media; //200 OK from MFSw on incoming Sip Leg
string out_media_1;
unsigned RtpLocalAddr;
int      RtpLocalPort;
TSdp in_sdp;         //from INVITE rcvd on legtype Lt_In and from 200OK rcvd on legtype Lt_Out or ReInvite rcvd from Lt_Out
TSdp out_sdp;        //for INVITE sent on  legtype Lt_Out and for 200OK sent on legtype Lt_In
TResendBlock resendblock;
int ch_sound;
int ch_video;
int ch_rtp_audio;     //!!!do not destroy in the destructor
int ch_rtcp_audio;    //!!!do not destroy in the destructor
#ifdef SIP_Video
int ch_rtp_video;     //!!!do not destroy in the destructor
int ch_rtcp_video;    //!!!do not destroy in the destructor
#endif
bool screen_sharing_viewer;

bool    lt_parallel_phone;                 //Используется в TLegTrn параллельного телефона
string  lt_parallel_phone_primary_call_id; //Используется в TLegTrn параллельного телефона
LegType primary_legtype_pph;               //Используется в TLegTrn параллельного телефона - информация о LegType основного вызова

int     source_of_outgoing_call;           //Используется в TLegTrn основного вызова: 0 - вызов из GUI приложения, 1 - вызов от параллельного телефона
string  pph_call_id;                       //Используется в TLegTrn основного исходящего вызова, если вызов инициирован параллельным телефоном (source_of_outgoing_call = 1)

TOutputSipBuf* ospb_wait_first_mic_packet;

void __fastcall PrepareResendBlock(TOutputSipBuf*);
void __fastcall UpdateResendInterval();
void __fastcall prepareReqLine_FromRemoteContact();
int  __fastcall prepareNextCSeq(const string&,TOutputSipBuf*);
void __fastcall prepare_init_rtp_seq__uas(TSip*,MediaPacketType);
void __fastcall prepare_init_rtcp_audio_seq__uas(TSip*);
bool __fastcall request_srtp(SRTP_TYPE, SRTP_KEY_ACTION, vector<string>&);
__fastcall TLegTrn(LegType);
virtual __fastcall ~TLegTrn();
};
//------------------------------------------------------------------------------
typedef map < string, TLegTrn*,less<string>, allocator<string> > TLegTrnList;
//------------------------------------------------------------------------------
#endif
