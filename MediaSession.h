//---------------------------------------------------------------------------

#ifndef MediaSessionH
#define MediaSessionH
#include "WinRDefs.h"
#include "MediaChannels.h"

//----------------------------------------------------------------------------
class TMediaSession{
TSip* Sip;
string callid;
int call_tag;  //binding panel with answered call with TMediaSession
deque<TUdpChannel*> channels;
TEventLogThread** eltp;
LegType     lt;
SipLegState resp;
bool transmit_video;    //set on start of transmission video (father pause or release of TUdpChanel->video_pause used )
bool RESP_200_OK_RCVD;
string      uniq_username;
string      display_user_name;
string      contact_uri; //sip:user_name@host_name:port или user_name@host_name - необходимо для Refer-To при переадресации
bool        ms_hstry_written;

bool        pph_session_created;     //Used in primary session to determin that parallel phone session is created
int         source_of_outgoing_call; //Used in primary session. If(1) - outgoing call initiated by parallel phone. If(0) - outgoing call initiated by SipClient over GUI

bool        ms_parallel_phone;  //media session for parallel phone
int         ms_parallel_phone_state; //0 - pph idle, 1 - pph seized, 2 - pph answered

public:
CRITICAL_SECTION chan_cs;
__fastcall TMediaSession(TEventLogThread** ELTP, TSip* SIP, const string& username, LegType Lt){
                                                ::InitializeCriticalSection(&chan_cs);
                                                Sip                     = SIP;
                                                eltp                    = ELTP;
                                                uniq_username           = username;
                                                lt                      = Lt;
                                                resp                    = SPS_UNKNOWN;
                                                call_tag                = 0;
                                                transmit_video          = false;
                                                RESP_200_OK_RCVD        = false;
                                                ms_hstry_written        = false;
                                                pph_session_created     = false;
                                                ms_parallel_phone       = false;
                                                source_of_outgoing_call = 0;
                                                ms_parallel_phone_state = 0;
                                                }
virtual      __fastcall ~TMediaSession();
void         __fastcall setCallID(const string& s){callid=s;}
void         __fastcall setRespState(SipLegState a){resp=a;}
string       __fastcall getCallID(){return callid;}
SipLegState  __fastcall getRespState(){return resp;}
int          __fastcall getCallTag(){return call_tag;}
void         __fastcall setCallTag(int a){call_tag = a;}
void         __fastcall set_contact_uri(const string& s){contact_uri = s;}
string       __fastcall get_contact_uri(){return contact_uri;}
LegType      __fastcall get_leg_type(){return lt;}
//void         __fastcall set_leg_type(LegType a){lt = a;}
bool         __fastcall get_ms_hstry_written(){return ms_hstry_written;}
void         __fastcall set_ms_hstry_written(bool a){ms_hstry_written = a;}
void         __fastcall channels_Add(TUdpChannel*);
void         __fastcall set_media_channels_OnHold(bool);
bool         __fastcall get_transmit_video(){return transmit_video;}
void         __fastcall set_transmit_video(bool a){transmit_video = a;}

void         __fastcall set_pph_session_created(bool a){pph_session_created = a;}
bool         __fastcall get_pph_session_created(){return pph_session_created;}

void         __fastcall set_source_of_outgoing_call(int a){source_of_outgoing_call = a;}
int          __fastcall get_source_of_outgoing_call(){return source_of_outgoing_call;}

void         __fastcall set_ms_parallel_phone(bool a){ms_parallel_phone = a;}
bool         __fastcall get_ms_parallel_phone(){return ms_parallel_phone;}
void         __fastcall set_ms_parallel_phone_state(int a){ms_parallel_phone_state = a;}
int          __fastcall get_ms_parallel_phone_state(){return ms_parallel_phone_state;}

TUdpChannel* __fastcall getFirstChannel();
TUdpChannel* __fastcall getSoundChannel();
TUdpChannel* __fastcall getRtpAudioChannel();
TUdpChannel* __fastcall getRtcpAudioChannel();
TUdpChannel* __fastcall getVideoChannel();
TUdpChannel* __fastcall getRtpVideoChannel();

void __fastcall set_200_OK_RCVD(bool a){RESP_200_OK_RCVD = a;}
bool __fastcall get_200_OK_RCVD(){return RESP_200_OK_RCVD;}

void __fastcall disconnectAllSessionChannels();
void __fastcall pushChannelToDelete(void*,TUdpChannel*,TUdpChannelStruct*);
void __fastcall printCreateSession();
void __fastcall printDeleteSession();
void __fastcall printReqToDeleteChannel(TUdpChannel*);
string& __fastcall get_uniq_username(){return uniq_username;}

void   __fastcall set_display_username(const string& s){display_user_name = s;}
string __fastcall get_display_username(){return display_user_name;}

void __fastcall FreeSession();
};
//---------------------------------------------------------------------------
typedef map <string,TMediaSession*,less<string>,allocator<string> > TMediaSessionList;
//---------------------------------------------------------------------------
class TMediaSessionStruct{
TMediaSessionList msl;
public:
CRITICAL_SECTION msl_cs;
__fastcall TMediaSessionStruct(){
                                ::InitializeCriticalSection(&msl_cs);
                                }
virtual        __fastcall ~TMediaSessionStruct();
void           __fastcall InsMsOut_by_Callid(const string&,TMediaSession*); //for uac
TMediaSession* __fastcall GetMsOut_by_Callid(const string&);                //for uac
//void           __fastcall DelMsOut_by_Callid(const string&);              //for uac

TMediaSession* __fastcall GetMs_by_In_Out_Callid(const string&);
TMediaSession* __fastcall GetMs_by_Call_Tag(int);

void           __fastcall InsMsIn_by_Callid(const string&,TMediaSession*);  //for uas
TMediaSession* __fastcall GetMsIn_by_Callid(const string&);                 //for uas
//void           __fastcall DelMsIn_by_Callid(const string&);               //for uas

void           __fastcall Connect_Conference_Channels(TUdpChannel*,TUdpChannel*);

//void           __fastcall Change_Ms_Callid(LegType,const string&,const string&);
void           __fastcall EraseMediaSession(const string&);
};
//---------------------------------------------------------------------------
#endif
