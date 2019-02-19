//---------------------------------------------------------------------------
#ifndef SipH
#define SipH
//---------------------------------------------------------------------------
#include "WinRDefs.h"
#include "Grids.hpp"
#include <map>
#ifndef _WINSOCK2API_
 #include <winsock2.h>
#endif
#include "BaseThread.h"
#include "log.h"
#include "SipRecvThread.h"
#include "SipSendThread.h"
#include "SipParsThread.h"
#include "SipUacThread.h"
#include "SipUasThread.h"
#include "SipResendThread.h"
#include "Sound.h"
#include "PlaySound.h"
#include "ip.h"
#include "MediaSession.h"
#include "Contact.h"
#include "RegistryPanel_Unit.h"
#include "tcp.h"
#include "tls.h"
#include "tunnel.h"
#include "const.h"

using namespace std;
//------------------------------------------------------------------------------
#define ROOT_KEY HKEY_CURRENT_USER; //HKEY_LOCAL_MACHINE;
class TConfCont;
class TCall_Panel;
//------------------------------------------------------------------------------
typedef enum{
AlertingType_RU,
AlertingType_US
}AlertingType;
//------------------------------------------------------------------------------
class TSignal{
public:
AlertingType at;
__fastcall TSignal(){at=AlertingType_US;}
};
//-----------------------------------------------------------------------------
class TG729Ini{
public:
bool annexb;
__fastcall TG729Ini(){annexb = false;}
};
//------------------------------------------------------------------------------
class TCodecsIni{
public:
TG729Ini G729Ini;
};
//------------------------------------------------------------------------------
class TContactData{
public:
string name;
string full_name;
string position; //должность
int    ext_db_id;
int    location;
int    cos;

__fastcall TContactData(){
                         ext_db_id = 0;
                         location  = 0; //Location_INT
                         cos       = 0;
                         }
};
//------------------------------------------------------------------------------
class TCurrentRegisterHeaders{
int CSeq_Register;
string From;
string CallID;
public:
int     __fastcall getCSeqRegister();
string& __fastcall getCurrentCallID(){return CallID;}
string& __fastcall getFrom(){return From;}

void  __fastcall setCurrentCallID(const string& s ){CallID=s;}
void  __fastcall setFrom(const string& s){From=s;}

__fastcall TCurrentRegisterHeaders(){
                                    CSeq_Register = 0;
                                    }
};
//-----------------------------------------------------------------------------
class TSip{
TEventLogThread** eltp;
int MAIN_CONTACT_LIST_SIZE;
HWND MF_Handle;
bool destroy_req;
bool stun;
int call_tag;
string lasterr;
int MESSAGE_CSeq;
int started_transferfile_panel_tag;
int Branch;

CRITICAL_SECTION sam_cs;
deque<int> supported_audio_media;
void __fastcall init_default_audio_codecs();

CRITICAL_SECTION svm_cs;
deque<int> supported_video_media;
void __fastcall init_default_video_codecs();

bool registered;
bool init_subscribe;
unsigned inittag;
unsigned initCallID;
unsigned __fastcall getInitTag(){return ++inittag;}
unsigned __fastcall getInitCallID(){return ++initCallID;}

CRITICAL_SECTION sip_sent_cs;
deque<void*> sip_sent;
void __fastcall getSent_1();

void __fastcall check_im_out_str(const vector<string>&,int,string&);
void __fastcall devide_plain_text_on_substrings(vector<string>&,string&);

CRITICAL_SECTION  cldtc_cs;
TCldUserNameToCallID cldtc;    //map calledname to "out_" + CallID

CRITICAL_SECTION req_tfl_cs;
queue<TTransferFileStruct> req_tfl;

TRegistryPanel* rp;

CRITICAL_SECTION ch_transp_cs;       //used for AUTO change tarnsport UDP <-> TUNNEL
TSipRecvThread*       standby_srt;
TSipSendThread*       standby_sst;
TSipRecvTunnelThread* standby_sr_tunnel_t;
TSipSendTunnelThread* standby_ss_tunnel_t;

TSipRecvThread* srt;                //if(srt)  standby_srt = NULL and conversely
TSipSendThread* sst;                //if(sst)  standby_sst = NULL and conversely
TSipRecvTunnelThread* sr_tunnel_t;  //if(sr_tunnel_t)  standby_sr_tunnel_t = NULL and conversely
TSipSendTunnelThread* ss_tunnel_t;  //if(ss_tunnel_t)  standby_ss_tunnel_t = NULL and conversely
void __fastcall sip_active_2_standby(TSipRecvThread*,TSipSendThread*);
void __fastcall sip_tunnel_standby_2_active(TSipRecvTunnelThread*,TSipSendTunnelThread*);
void __fastcall sip_udp_tunnel(TSipRecvThread*,TSipSendThread*,TSipRecvTunnelThread*,TSipSendTunnelThread*);

void __fastcall sip_tunnel_active_2_standby(TSipRecvTunnelThread*,TSipSendTunnelThread*);
void __fastcall sip_standby_2_active(TSipRecvThread*,TSipSendThread*);
void __fastcall sip_tunnel_udp(TSipRecvTunnelThread*,TSipSendTunnelThread*,TSipRecvThread*,TSipSendThread*);
int  __fastcall getBranch(){return ++Branch;}

//void __fastcall __send_instant_message_IN_DIALOG__UAC(const string&, const vector<string>&);
//void __fastcall __send_instant_message_IN_DIALOG__UAS(const string&, const vector<string>&);

public:
SOCKET sck;
SOCKET tunnel_sck;
Sip_Transport sip_transport;
bool Sip_TransportAuto;

bool TCP_Dropped;
CRITICAL_SECTION   tcp_t_cs;  //Protection from access violation on delete TSip only
TSipSendTcpThread* ss_tcp_t;
TSipRecvTcpThread* sr_tcp_t;

bool TLS_Dropped;
TSipSendTlsThread* ss_tls_t;
TSipRecvTlsThread* sr_tls_t;

TSipParsThread*    spt;
TSipUasThread*     uas;
TSipUacThread*     uac;
TUdpChannelStruct* ucs;
TPlaySoundThread*  pst;

TContacts Contacts;
TMediaSessionStruct* sss;
deque<TIPAddress*> localIP;
#ifndef RTP_exsCreateUDPSocket_ADDR_ANY
TVoipMediaPortBlock vmpb;
#endif
TIPAddress MappedAddress;
TIPAddress SipProxy;
TIPAddress SipLocalProxy;
TIPAddress SipTunnel;
TIPAddress SipLocalTunnel;
TIPAddress FileTransfer;
TIPAddress SipTCP;
TIPAddress SipTLS;
TIPAddress SipTUNNEL;
TIPAddress SubscDB;
TIPAddress ScreenSharing;
#ifdef Client_Test_Block
TTestBlock TestBlock;
#endif
unsigned   regint;    //registry interval sec, default 3600
TAccount   Account;
TSignal    Signal;
TCodecsIni CodecsIni;
TCurrentRegisterHeaders crh;
int siphostport;
string clientname;
string vers;
string contact_dir;
string contact_file;

void   __fastcall updateSentQueue_1(void*);
void   __fastcall copy_supported_audio_codecs(vector<int>&);
void   __fastcall copy_supported_video_codecs(vector<int>&);
bool   __fastcall video_codec_supported(int);

void   __fastcall ins_CLD_tc(const string&,const string&);
void   __fastcall del_CLD_tc(const string&);
string __fastcall getCallID_CLD_tc(const string&);

bool   __fastcall get_init_subscribe(){return init_subscribe;}
void   __fastcall set_init_subscribe(bool a){init_subscribe = false;}
void   __fastcall init_on_registration_subscribe_proc();

TRegistryPanel* __fastcall get_rp(){return rp;}
bool __fastcall isStunAssigned(){return stun;}
void __fastcall readContacts();
bool __fastcall readActualClientContacts(AnsiString&,TContact*);
void __fastcall readActualChatGroups(AnsiString&);
void __fastcall read_contacts_time_stmp(AnsiString&);
void __fastcall read_contact_metadata(AnsiString&,TContactData&);
bool __fastcall readPresenceComment();
void __fastcall readPresenceContactComment();
void __fastcall display_full_ser_name();
void __fastcall log(TEventLogThread*,const string&);
void __fastcall Log(const string&,int = 0);
void __fastcall log_selected_transport();
void __fastcall SetOutQueue(void*);
void __fastcall generateToTag(BaseExchangeBlock*);
void __fastcall prepareToTag_Final(BaseExchangeBlock*);
void __fastcall prepareFromTag_Final(TOutputSipBuf*);
void __fastcall generateFromTag(TOutputSipBuf*);
void __fastcall generateCallID(TOutputSipBuf*);
void __fastcall collectLocalHostInterfaces(void*);
void __fastcall selectLocalNetAddr(void*);
void __fastcall getSipProxyFromIniData(void*);
void __fastcall getSipLocalProxyFromIniData(void*);
void __fastcall getSipTunnelFromIniData(void*);
void __fastcall getSipLocalTunnelFromIniData(void*);
void __fastcall get_INIDATA(void*);
void __fastcall getFTransferFromIniData(void*);
void __fastcall getRegistryIntervalFromIniData(void*);
void __fastcall getAccountFromIniData(void*);
void __fastcall getSipTcp(void*);
void __fastcall getSipTls(void*);
void __fastcall getSubscDBData(void*);
void __fastcall getScreenSharingData(void*);
void __fastcall getTransport(void*);
void __fastcall getSignalFromIniData(void*);
bool __fastcall get_destroy_req(){return destroy_req;}
#ifndef RTP_exsCreateUDPSocket_ADDR_ANY
void __fastcall getMediaFromIniData(void*);
#endif
void __fastcall getG729ParFromIniData(void*);
HWND __fastcall getMFHandle(){return MF_Handle;}
void __fastcall getLocalMedia(TUdpChannel*);
void __fastcall getLocalMediaPort(TUdpChannel*);
int  __fastcall getSentSize_1();
void __fastcall printSentBlocks(string&);
int  __fastcall gen_call_tag(){return ++call_tag;};
TIPAddress* __fastcall getLastNIC();
void __fastcall getSockName(TEventLogThread*);
void __fastcall create_work_threads();
bool __fastcall getRegistered(){return registered;}
void __fastcall setRegistered(bool a){registered = a;}
//void __fastcall Tunnel_Connect();
//int  __fastcall Try_Tunnel_Connect(TIPAddress*);
void __fastcall initRegistrationProc();
void __fastcall sendAuthRegistration(TAuthPar*);
void __fastcall sendAuthInvite(TAuthPar*,const string&);
void __fastcall sendAuthMessage(TAuthPar*,const string&);
bool __fastcall checkAccount();
void __fastcall open_reg_win();
void __fastcall resize_reg_win();
void __fastcall init_SUBSCRIBE_Proc(TContact&,int);
void __fastcall init_Refreshing_SUBSCRIBE_Proc(const TSubscrPar&);
void __fastcall reset_SUBSCRIPTION(const string&);
void __fastcall reset_OLD_init_NEW_SUBSCRIPTION(const string&);
void __fastcall regularRegistrationProc(SipLegState);
void __fastcall finalRegistrationProc(TAuthPar*);
void __fastcall change_sip_transport();
void __fastcall change_sip_transport_UDP_TUNNEL();
void __fastcall change_sip_transport_TUNNEL_UDP();
void __fastcall sendInitInvite(const string&,const string&,TSdpMediaCont*);
void __fastcall sendInitInvite_OnReferInit(const string&,const string&,TSdpMediaCont*,int);
void __fastcall sendInitInvite_OnConferenceCreate(const string&,const string&,TSdpMediaCont*,TConfCont*,int);
void __fastcall sendInitInvite_OnFileTransfer(void*);
void __fastcall send_ScreenSharing_INVITE(TCall_Panel*,const string&,const string&);
void __fastcall send_ScreenSharing_INVITE_ToConference(TConfCont& , const string&);
void __fastcall sendInit_REINVITE_WITH_ADD_VIDEO(TExchBuf*,TSdpMediaCont*);
void __fastcall SendInitMessage(TContact*,const vector<string>&);
//void __fastcall SendInstantMessage_IN_DIALOG(LegType,const string&,const vector<string>&);
void __fastcall prepare_Sdp_Initial(TSdp*,TSdpMediaCont*);
void __fastcall prepare_Sdp_200OK_Initial(TSdp*,TSdpMediaCont*);
void __fastcall sendInitial_Uac_Rtp_Sequence(MediaPacketType,TRemoteMedia*);       //on receiving 183 responce and 200OK;
void __fastcall sendInitial_Uas_Rtp_Sequence(MediaPacketType,TLegTrn*);
void __fastcall send_call_disc_out(const string&, bool);
void __fastcall send_call_disc_in(const string&);
void __fastcall sendCallDisc_In(const string&);
void __fastcall send_180_Resp(TSipParsBuf*);
void __fastcall send_Create_Session_Req(TSipParsBuf*);
void __fastcall prepare_Initial_180Resp(TSipParsBuf*);
void __fastcall prepare_Initial_Create_Session_Req(TSipParsBuf*);
void __fastcall sendUas_Decline_OnInvite(TExchBuf*);
void __fastcall sendUas_Answer_OnInvite(TExchBuf*);
void __fastcall activate_Remote_Video_OnReInvite_Recv_With_Add_Video(TExchBuf*, SipUAThreadType);
void __fastcall sendUas_Answer_OnSharingInvite(TExchBuf*);
void __fastcall send_Uas_NOTIFY_ON_SUBSCRIBE_Rcvd(TExchBuf*,bool);
void __fastcall send_Uas_NOTIFY(TSubscribedData&);
TOutputSipBuf* __fastcall prepare_Initial_REGISTERReq();
TOutputSipBuf* __fastcall prepare_Auth_REGISTER_Req(TAuthPar*);
TOutputSipBuf* __fastcall prepare_Initial_SUBSCRIBE_Req(TContact&,int);
TOutputSipBuf* __fastcall prepare_Initial_Refreshing_SUBSCRIBE_Req(const TSubscrPar&);
TOutputSipBuf* __fastcall prepare_regular_REGISTERReq(SipLegState);
TOutputSipBuf* __fastcall prepare_Final_REGISTERReq(TAuthPar*);
TOutputSipBuf* __fastcall prepare_Initial_MESSAGE_Req(TContact*,const vector<string>&);
TOutputSipBuf* __fastcall prepare_Initial_INVITE_Req(const string&,const string&,TSdpMediaCont*);
TOutputSipBuf* __fastcall prepare_Initial_REINVITE_WITH_ADD_VIDEO_Req(TExchBuf*,TSdpMediaCont*);
TOutputSipBuf* __fastcall prepare_Initial_ScreenSharing_INVITE(const string&,const string&);
TOutputSipBuf* __fastcall prepare_Auth_INVITE_Req(TAuthPar*,const string&);
TOutputSipBuf* __fastcall prepare_Auth_MESSAGE_Req(TAuthPar*,const string&);
TOutputSipBuf* __fastcall prepare_Initial_ANSWER_Req(TExchBuf*,int);
TOutputSipBuf* __fastcall prepare_Initial_ANSWER_OnSharingInvite_Req(TExchBuf*);
TOutputSipBuf* __fastcall prepare_Initial_PRESENCE_NOTIFY_Req(TExchBuf*,SipLegState,bool=false);
TOutputSipBuf* __fastcall prepare_init_rtp_audio_seq__uac(TRemoteMedia*);
TOutputSipBuf* __fastcall prepare_init_rtcp_audio_seq__uac(TRemoteMedia*);
#ifdef SIP_Video
TOutputSipBuf* __fastcall prepare_init_rtp_video_seq(TRemoteMedia*);
#endif
TOutputSipBuf* __fastcall prepare_Disc_Out_Req(const string&);
TOutputSipBuf* __fastcall prepare_Disc_In_Req(const string&);
TOutputSipBuf* __fastcall Prepare_202_Resp_OnSubscribe(TSipParsBuf*,TLegTrn*);
TOutputSipBuf* __fastcall Prepare_603_Resp_OnSubscribe(TSipParsBuf*,TLegTrn*);

void __fastcall prepareRequestLine_REGISTER(TOutputSipBuf*);
void __fastcall prepareRequestLine_SUBSCRIBE(TOutputSipBuf*,TContact&);
void __fastcall prepareRequestLine_MESSAGE(TOutputSipBuf*,TContact*);
void __fastcall prepareSdp_MESSAGE(TOutputSipBuf*,const vector<string>&);
void __fastcall prepareRequestLine_INVITE(const string&,TOutputSipBuf*);
void __fastcall prepareViaHeader(TOutputSipBuf*);
void __fastcall Prepare_Via_Header_With_Branch(TOutputSipBuf*);
void __fastcall prepareCallID_REGISTER(TOutputSipBuf*);
void __fastcall prepareCallID_SUBSCRIBE(TOutputSipBuf*);
void __fastcall prepareCallID_MESSAGE(TOutputSipBuf*);
void __fastcall prepareCallID_INVITE(TOutputSipBuf*);
void __fastcall prepareCallID_Common(TOutputSipBuf*,const string&);
void __fastcall prepareAccept(TOutputSipBuf*);
void __fastcall prepareEvent(TOutputSipBuf*,const string&);
void __fastcall prepareMaxForwards(int,TOutputSipBuf*);
void __fastcall prepareCSeq(int,const string&,TOutputSipBuf*);
void __fastcall prepareExpires(int,TOutputSipBuf*);
void __fastcall prepareAllow(TOutputSipBuf*);
void __fastcall prepareContentType(TOutputSipBuf*,const string&);
void __fastcall prepareUserAgent(BaseExchangeBlock*);
void __fastcall prepareContentLength_0(BaseExchangeBlock*);
void __fastcall prepareContact(BaseExchangeBlock*);
void __fastcall prepare_Final_REGISTER_Contact(TAuthPar*, BaseExchangeBlock*);
void __fastcall prepare_Current_REGISTER_CallID(TOutputSipBuf*);
void __fastcall prepareInitialTo(const string&,const string&,const string&,TOutputSipBuf*);
void __fastcall prepareFrom_COMMON(TOutputSipBuf*,TAccount*,bool);
void __fastcall prepareFrom_REGISTER(TOutputSipBuf*);
void __fastcall prepare_auth_responce(TAuthPar* auth_par,const string&);
void __fastcall prepare_authorization_header(TOutputSipBuf*,TAuthPar*);
void                __fastcall tnl_add(TTransferFileStruct&);
bool                __fastcall tnl_get(TTransferFileStruct&);
void                __fastcall transmit_file_init();
unsigned            __fastcall get_file_size(const string&);
void                __fastcall Transmit_File__Labels(void*,TTransferFileStruct*,const string&,unsigned);
void                __fastcall Transmit_File__Cancel_Btn(void*);
void                __fastcall Transmit_File__Progress_Bar(void*,unsigned);
void                __fastcall Transmit_File__Label_Waiting(void*);
void                __fastcall Receive_File__Labels(void*,TSipParsBuf*,TTransferFileAttrib*);
void                __fastcall Receive_File__Btns(void*);
void                __fastcall Receive_File__Progress_Bar(void*,unsigned);
int                 __fastcall get_started_transferfile_panel_tag(){return started_transferfile_panel_tag;}
void                __fastcall update_contact_file();
//bool                __fastcall update_contact_file_with_own_account();
void                __fastcall hide_registry_panel();

TSipRecvThread*       __fastcall getStandbyTSipRecvThread(){return standby_srt;}
TSipSendThread*       __fastcall getStandbyTSipSendThread(){return standby_sst;}
TSipRecvTunnelThread* __fastcall getStandbyTSipRecvTunnelThread(){return standby_sr_tunnel_t;}
TSipSendTunnelThread* __fastcall getStandbyTSipSendTunnelThread(){return standby_ss_tunnel_t;}
void                  __fastcall setStandbyTSipRecvThread(TSipRecvThread* ptr){standby_srt = ptr;}
void                  __fastcall setStandbyTSipSendThread(TSipSendThread* ptr){standby_sst = ptr;}
void                  __fastcall setStandbyTSipRecvTunnelThread(TSipRecvTunnelThread* ptr){standby_sr_tunnel_t = ptr;}
void                  __fastcall setStandbyTSipSendTunnelThread(TSipSendTunnelThread* ptr){standby_ss_tunnel_t = ptr;}

TSipRecvThread*       __fastcall getTSipRecvThread(){return srt;}
TSipSendThread*       __fastcall getTSipSendThread(){return sst;}
TSipRecvTunnelThread* __fastcall getTSipRecvTunnelThread(){return sr_tunnel_t;}
TSipSendTunnelThread* __fastcall getTSipSendTunnelThread(){return ss_tunnel_t;}
void                  __fastcall setTSipRecvThread(TSipRecvThread* ptr){srt = ptr;}
void                  __fastcall setTSipSendThread(TSipSendThread* ptr){sst = ptr;}
void                  __fastcall setTSipRecvTunnelThread(TSipRecvTunnelThread* ptr){sr_tunnel_t = ptr;}
void                  __fastcall setTSipSendTunnelThread(TSipSendTunnelThread* ptr){ss_tunnel_t = ptr;}

void __fastcall delete_SipRecvTunnelThread();
void __fastcall delete_SipSendTunnelThread();
void __fastcall delete_SipRecvThread();
void __fastcall delete_SipSendThread();

void __fastcall Delete_SS_TCP_T();
void __fastcall Delete_SR_TCP_T();


__fastcall TSip(const string& ClientName,const string& Vers,HWND handle,TEventLogThread** ELTP){
                 ::InitializeCriticalSection(&sam_cs);
                 ::InitializeCriticalSection(&svm_cs);
                 ::InitializeCriticalSection(&sip_sent_cs);
                 ::InitializeCriticalSection(&cldtc_cs);
                 ::InitializeCriticalSection(&req_tfl_cs);
                 ::InitializeCriticalSection(&ch_transp_cs);
                 ::InitializeCriticalSection(&tcp_t_cs);
                 MAIN_CONTACT_LIST_SIZE = 0;
                 MF_Handle     = handle;
                 Contacts.set_contact_list_size_pointer(&MAIN_CONTACT_LIST_SIZE);
                 eltp          = ELTP;
                 destroy_req   = false;
                 sck           = INVALID_SOCKET;
                 tunnel_sck    = INVALID_SOCKET;
                 sip_transport = Sip_Transport_UDP;
                 Sip_TransportAuto = false;
                 stun = false;                                     
                 call_tag     = 0;
                 MESSAGE_CSeq = 0;

                 standby_srt         = NULL;
                 standby_sst         = NULL;
                 standby_sr_tunnel_t = NULL;
                 standby_ss_tunnel_t = NULL;

                 TCP_Dropped = true;    //!!!
                 TLS_Dropped = true;    //!!!
                 sr_tcp_t=NULL;
                 ss_tcp_t=NULL;
                 sr_tls_t=NULL;
                 ss_tls_t=NULL;
                 sr_tunnel_t=NULL;
                 ss_tunnel_t=NULL;
                 srt=NULL;
                 spt=NULL;
                 sst=NULL;
                 uas=NULL;
                 uac=NULL;
                 ucs=NULL;
                 pst=NULL;
                 sss = NULL;
                 siphostport=-1;
                 inittag    = 15511659;
                 initCallID = 287542579;
                 Branch     = 274865315;
                 randomize();
                 inittag    += random(inittag);
                 initCallID += random(initCallID);
                 Branch     += random(Branch);
                 clientname = ClientName;
                 vers = "v" + Vers;
                 registered=false;
                 init_subscribe=false;
                 regint=3600;
                 init_default_audio_codecs();
                 init_default_video_codecs();
                 contact_file = "cont.rst";
                 rp = NULL;
                 }
virtual __fastcall ~TSip();
};
//---------------------------------------------------------------------------
const string __fastcall get_CONTACTS_DIR();
#endif
