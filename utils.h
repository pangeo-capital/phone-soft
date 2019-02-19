#ifndef UTILS_H
#define UTILS_H
#include "WinRDefs.h"
#ifndef _WINSOCK2API_
 #include <winsock2.h>
#endif
#include <map>
#include "log.h"
#include "SipLegState.h"
#include <Registry.hpp>

using namespace std;

#include "TRACE_MEM_ALLOC.h"

#ifndef UBYTE
typedef unsigned char UBYTE;
#endif

#ifndef USHORT
typedef unsigned short USHORT;
#endif

const string lf = "\n";
const string crlf = "\r\n";
const string sdpboundary = "\r\n\r\n";
//const string ws = " ";
const string strempty  = "";

const AnsiString AWS = " ";
const string WS = " ";
const string COLON = ":";
const string SEMICOLON = ";";
const string SipVers      = "SIP/2.0";
const string SipVersTcp   = "SIP/2.0/TCP";
const string SipVersUdp   = "SIP/2.0/UDP";
const string const_Via    = "Via:";
const string const_RecordRoute = "Record-Route:";
const string DOTSTRING = ".";
const string out_pref  = "out_";
const string in_pref   = "in_";
const string const_sendrecv  = "sendrecv";
const string const_sendonly  = "sendonly";
const string const_recvonly  = "recvonly";

const max_video_payload_size            = 1024;//512;//
const jitter_buffer_video_delay_maximum = 40;//10;

const jitter_buffer_delay_minimum = 3;
const jitter_buffer_delay_maximum = 20;//10;
const jitter_buffer_delay_audio_conf_maximum = 20;//10  //20 * 20 = 400   //10 * 20 = 200

const audio_report_interval = 5;//10; // 1 - 59 sec
const video_report_interval = 5;//10; // 1 - 59 sec

class TVcamPar;
class T38Struct;
class TFileTransSDPAttrib;
class TSdpMediaCont;
//-----------------------------------------------------------------------------
typedef enum{
Lang_EN,
Lang_RU
}Lang;
//---------------------------------------------------------------------------
typedef enum{
IM_TEXT_TOP_STRING,
IM_TEXT_TYPE_LOCAL_IM,   //IM_TEXT_TYPE_PLAIN,       //Отправка Instat Msg
IM_TEXT_TYPE_REMOTE_IM, //IM_TEXT_TYPE_HTML,
IM_TEXT_TYPE_REM_ADDR,
IM_TEXT_TYPE_LOCAL_ADDR,
IM_TEXT_TYPE_DATE,
IM_CALL_IN_DECLINED,
IM_CALL_IN_MISSED,
IM_CALL_IN_ANSWERED,
IM_CALL_OUT_NO_ANSWER,
IM_CALL_OUT_ANSWERED,
IM_CALL_OUT_BUSY,
IM_CALL_OUT_NOT_ACCEPTABLE,
IM_INVITE_ON_FILE_RECEIVING,
IM_INVITE_ON_FILE_SENDING,
im_text_type_ndef,    //Do not assign -1 !!!!
}im_text_type;
//----------------------------------------------------------------------------
typedef enum{
im_element_type_plain,
im_element_type_href,
}im_element_type;
//----------------------------------------------------------------------------
typedef enum{
TOutPutUdpBlock_BLOCKTYPE,
TWaveOutPutBuf_BLOCKTYPE,     //Always deleted without check reference count
TOutputSipBuf_BLOCKTYPE,
TSipParsBuf_BLOCKTYPE,
TRemoteMedia_BLOCKTYPE,
TVcamPar_BLOCKTYPE,
TAuthPar_BLOCKTYPE,
TOutPutDtmf_BLOCKTYPE,
}BLOCKTYPE;
//-----------------------------------------------------------------------------
typedef enum{
Call_Type_Regular,
Call_Type_Refer,
Call_Type_FileTransfer,
}TCall_Type;
//-------------------------------------------------------------------------
typedef enum{
Call_State__Answer,
Call_State__Conference,
Call_State__NotAcceptable,
Call_State__Busy,
Call_State__Request_Hold_By_Local_Party,
Call_State__Hold_By_Local_Party,
Call_State__Hold_By_Remote_Party,
Call_State__Unknown,
}Call_State;
//-----------------------------------------------------------------------------
static int SipClient_BlockCount;
//-----------------------------------------------------------------------------
class TSdpMedia{
public:
string   s_remotertpip;
unsigned localrtpip;
int      localrtpport;
int      remotertpport;
string media_type;     //(m): "audio", "video", etc
string media_protocol; //(m): "RTP/AVP", "image"
vector<int>    codecs;
vector<string> crypto_keys;
vector<string> rtp_attr_list;
  __fastcall TSdpMedia(){
                      localrtpip    =  0;
                      localrtpport  = -1;
                      remotertpport = -1;
                      }
};
//-----------------------------------------------------------------------------
class TSdp{
public:
string content_type;
string content_length;
string SdpVersion;             //(v):
string Owner_UserName;         //(o):
string SessionID;              //(o):
string SessionVersion;         //(o):
string Owner_NeworkType;       //(o):
string Owner_AddressType;      //(o):
string Owner_Address;          //(o):
string SessionName;            //(s):
string Connection_NetworkType; //(c):
string Connection_AddressType; //(c):
string Session_StartTime;      //(t):
string Session_StopTime;       //(t):
string common_connection_addr; //(c): audio and video connection addr
string video_connection_addr;  //(c): separeted conn addr for video - remote endpoint (SipProxy) can use separated  audio and video addresses
TSdpMedia audio;
#ifdef SIP_Video
TSdpMedia video;
#endif
T38Struct* t38;
TFileTransSDPAttrib* tftp;
string Sdp;
void __fastcall prepare_media(TSdpMediaCont*);
void __fastcall prepare_sdp_audio(TSdpMediaCont*);
void __fastcall prepare_sdp_audio_codec_list();
void __fastcall prepare_sdp_audio_attrib_list(TSdpMediaCont*);
#ifdef SIP_Video
void __fastcall prepare_sdp_video(TSdpMediaCont*);
void __fastcall prepare_sdp_video_codec_list();
void __fastcall select_supported_video_codecs();
void __fastcall prepare_sdp_video_attrib_list(TSdpMediaCont*);
#endif
void __fastcall prepSdpStr();
void __fastcall addVideoToSdpStr();
void __fastcall prep_final_media(vector<int>&, vector<string>&, vector<string>&);
__fastcall  TSdp();
__fastcall ~TSdp();
};
//-----------------------------------------------------------------------------
class TBaseHeaderListStruct{  //Pointer MUST NOT be used in this class!!! We using copy of objects - for instance  Lt->OrigVia = spb->ViaSt;
int ind;
protected:
void __fastcall ins(const string&); //insert subsequent via header into lst
int  __fastcall find_subsequent_via_header(const string&,int&,const string&);
public:
map < int, string, less<int>, allocator<int> > lst;
void __fastcall CollectHeaders(const string&,const string&);
void __fastcall InsertHeaders(string&);
__fastcall TBaseHeaderListStruct(){ind=0;}
};
//---------------------------------------------------------------------------
class TViaStruct : public TBaseHeaderListStruct{ //Pointer MUST NOT be used in this class!!! We using copy of objects - for instance  Lt->OrigVia = spb->ViaSt;
public:
bool __fastcall getFirstBranch(string&);
};
//-----------------------------------------------------------------------------
class BaseExchangeBlock{
BLOCKTYPE bt;
SipLegState __sls;
unsigned    __reg_tag;
int referenceCount;
int blockcount;
bool req_to_delete;

public:
SipLegState sps;
string FromIP;
int    FromPort;
string ToIP;
int    ToPort;
string CallID;
string CSeq;
string totag;
string To;
string From;
string Contact;
string UserAgent;
string ContentLength;
bool   queue_filler;
bool   conference_participant;

bool   parallel_phone;
string parallel_phone_call_id;
int    primary_call_direction_pph;   // 0 == Incoming Call, 1 == Outgoing Call
int    source_of_call;
string source_callid;

string s;
#ifdef SIP_Video
TVcamPar* vcpar;
#endif
TViaStruct ViaSt;
TSdp sdp;
__fastcall BaseExchangeBlock(BLOCKTYPE BT){bt=BT;referenceCount=0;
                                         __sls      = SPS_UNKNOWN;
                                           sps      = SPS_UNKNOWN;
                                         __reg_tag  = 3600;
                                           FromPort = 0;
                                           ToPort   = 0;
                                           req_to_delete  = false;
                                           blockcount     = SipClient_BlockCount++;
                                           queue_filler   = false;
                                           parallel_phone             = false;
                                           conference_participant     = false;
                                           primary_call_direction_pph = -1;
                                           source_of_call             =  0;
                                           #ifdef SIP_Video
                                           vcpar = NULL;
                                           #endif
                                          }
virtual __fastcall ~BaseExchangeBlock(){
                                        #ifdef SIP_Video
                                        if(vcpar)
                                          delete vcpar;
                                        #endif
                                       }
void __fastcall decReferenceCount(){--referenceCount;}     //!!!After decReferenceCount() do not any check in BaseExchangeBlock, since this block may be delelted by getSent_1(), getSent(),  checkSent()
void __fastcall incReferenceCount(){++referenceCount;}
int  __fastcall getReferenceCount(){return referenceCount;}
int  __fastcall getBlockCount(){return blockcount;}
void __fastcall set_req_to_delete(){req_to_delete = true;}
bool __fastcall get_req_to_delete(){return req_to_delete;}

void        __fastcall setsls(SipLegState a){__sls = a; __reg_tag = 3600;}  //3600sec default if tag is used for registration interval in REGISTER msg
void        __fastcall setsls_1(SipLegState a){__sls = a;}
SipLegState __fastcall getsls(){return __sls;}

void        __fastcall set_reg_tag(unsigned a){__reg_tag = a;}
unsigned    __fastcall get_reg_tag(){return __reg_tag;}

BLOCKTYPE __fastcall getBlockType(){return bt;}

};
//------------------------------------------------------------------------------
class TTransferFileAttrib{ //!!! Do not use pointers
public:
int sid;
unsigned file_size;
string file_name;
string path;
string complete_file_name;
__fastcall TTransferFileAttrib(){
                                sid = 0; file_size = 0;
                                }
};
//------------------------------------------------------------------------------
class TMfswIpAddrStruct{
public:  //Do not apply any pointers because we use constructor copy
string RemoteAddr;
int    RemotePort;
string LocalAddr;
int    LocalPort;
string errstr;
__fastcall TMfswIpAddrStruct(){RemotePort=-1;LocalPort=0;}
};
//-----------------------------------------------------------------------------
//std::wstring s2ws(const std::string&);
std::string ws2s(const std::wstring&);
string  __fastcall uint_to_str(unsigned);
string  __fastcall inttostr(int);
string  __fastcall inttohexstr(int);
//wstring __fastcall inttowstr(int);
//wstring __fastcall inttowhexstr(int,int);
string  __fastcall inttohexstr(int,int);
string  __fastcall bigendian_to_dot_str(unsigned);
string  __fastcall littleendian_to_dot_str(unsigned);
int     __fastcall strtoint(const string& s);
UBYTE   __fastcall hex_str_to_int(const string&,int);
void    __fastcall lowercase(string&);
void    __fastcall uppercase(string&);
void    __fastcall exsTime(TDateTime&,string&);
void    __fastcall exsDateTime(TDateTime&,string&);
void    __fastcall exsDateTime_FileName(TDateTime&,string&);
int     __fastcall exsWSAStartUp(TEventLogThread*);
SOCKET  __fastcall exsCreateUDPSocket(const string&,int);
SOCKET  __fastcall exsCreateUDPSocket_ADDR_PORT_ANY();
SOCKET  __fastcall exsCreateUDPSocket_ADDR_ANY(UINT);
SOCKET  __fastcall exsCreateTCPSocket_ADDR_ANY();
SOCKET  __fastcall exsCreateTCPSocket(TMfswIpAddrStruct*);
SOCKET  __fastcall exsCreateSrvTCPSocket_ADDR_ANY();
bool    __fastcall get_TCP_server_port(SOCKET,unsigned&);
void    __fastcall GetLastSocketError(string&,int,int = 0);
void    __fastcall GetLastSocketError(string&, int, const string&,int = 0);
void    __fastcall resolve_error_code(string&, int, int);
void    __fastcall PackFixedParameter(UBYTE*,int,int,int&);
void    __fastcall CheckIniData(string&);
bool    __fastcall exs_app_runnig(const string&,const string&,const string&,const string&);
unsigned long __fastcall get_reg_process_id();
int     __fastcall findTerminationSymbol(string&);
void     __fastcall trimString(string&,int);
void     __fastcall left_trim_string(string&);
int      __fastcall getIpSubAddr(string&,string&,int&,int&);
unsigned __fastcall StrIpToInt(string&);
void     __fastcall exsConvByteStrToUnsigned(unsigned&,const string&,int&,int&,int,int);
unsigned __fastcall exsConvStrIpAddrToUnsigned(const string&);
void     __fastcall SipLegStateToStr(string&,SipLegState);
void     __fastcall exsDeleteSentBlock(void*);
bool     __fastcall exsCheck_OnReceive_FileTransfer(const string&,TTransferFileAttrib*);
void     __fastcall exsGet_FileTransfer_Attributes(const string&,int,TTransferFileAttrib*);
void     __fastcall exsGet_Attrib(const string&,const string&,string&,int&);
bool     __fastcall isVideoPacketPSC(vector<UBYTE>&);
string   __fastcall getauthel(const string&,const string&);
double   __fastcall abs_max_value(vector<double>&);
void     __fastcall ubyte_2_short(vector<short>&,vector<UBYTE>&,int); // UBYTE to little endian
void     __fastcall short_2_double(vector<double>&,vector<short>&);
void     __fastcall double_2_short(vector<short>&,vector<double>&,int,bool);
void     __fastcall round_up(vector<double>&,int);
void     __fastcall short_2_ubyte(vector<UBYTE>&,vector<short>&,int);
void     __fastcall NORMALIZE(vector<int>&, int);
void     __fastcall INT_2_UBYTE(vector<UBYTE>&,const vector<int>&,int);
void     __fastcall UBYTE_2_INT(vector<int>&,const vector<UBYTE>&,int);
void     __fastcall MIX_UBYTE_2_INT(vector<int>&,const vector<UBYTE>&,int);
int      __fastcall get_payload_type(UBYTE);
void     __fastcall G711_To_Linear(vector<UBYTE>&,vector<UBYTE>&,int);
unsigned __fastcall get_seq_number(UBYTE,UBYTE);
UINT     __fastcall md_32(char*,int);
UINT     __fastcall random32(int type, int pid, UINT hostid, char* host_name, UINT hostnamelength);
UINT     __fastcall get_random32(int);
bool     __fastcall check_directory_existence(const string&);

void     __fastcall dissect_sdp_str(queue<string>&,const string&);
bool     __fastcall get_sdp_substr(queue<string>&,const string&,int&,int);

int    Utf8Code_calculateEnBufferSize(const char*,int);
int    Utf8Code_calculateDecBufferSize(const char*,int);
void   Utf8Code_encode(const char*,int,char*,int);
string ANSI_2_UTF8(const string&);
string UTF8_2_ANSI(const string&);

void __fastcall set_img_cursor_type(TImage*);

string    __fastcall get_current_user();
unsigned  __fastcall prep_sub_branch(SYSTEMTIME*,int);
TDateTime __fastcall sec_to_date_time(unsigned);
unsigned  __fastcall DateTimeToSec(const TDateTime&);
string    __fastcall month_to_str(int,Lang);
int       __fastcall expires_to_int(const string&);
bool      __fastcall get_digit_substr(const string&,int&,int);  //basically used for get cseq from spb->CSeq string
void      __fastcall scale_volume(vector<UBYTE>&,double);
string    __fastcall select_local_ip_addr(UINT);
void      __fastcall Get_OS_Version(OSVERSIONINFO*);
void      __fastcall exsSstEXCEPTION(TEventLogThread*,const string&,Exception&);
//-----------------------------------------------------------------------------
#endif
