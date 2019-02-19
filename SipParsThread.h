//---------------------------------------------------------------------------

#ifndef SipParsThreadH
#define SipParsThreadH

#include "WinRDefs.h"
//#include <queue.h>
#include "BaseThread.h"
#include "log.h"
#include "udp.h"
#include "utils.h"
#include "SipLegState.h"
#ifdef SIP_Video
#include "vencpar.h"
#endif
#include "transmit_file.h"

//---------------------------------------------------------------------------
typedef enum{
CallID_Type_Prim,     //Primitive (callid string only)
CallID_Type_Constr    //Constructor (callid + branch)
}CallID_Type;
//------------------------------------------------------------------------------
typedef enum{
RtpAttrType_Attr,
RtpAttrType_RtpMap,
RtpAttrType_String
}RtpAttrType;
//------------------------------------------------------------------------------
typedef enum{
MediaCont_Subtype_Regular,
MediaCont_Subtype_FileTransfer,
}MediaCont_Subtype;
//------------------------------------------------------------------------------
class TCallID{ //!!!Do not use any type of pointers
CallID_Type type;
string callid;
string branch;
string callidcmpx; //callid + "_" + branch
public:
     __fastcall TCallID(){type=CallID_Type_Prim;}
void   __fastcall reset();
string __fastcall getcallid();
string __fastcall getprimcallid();
void   __fastcall setprimcallid(const string&);
void   __fastcall setextcallid(const string&,const string&,const string&);
bool   __fastcall checkcallid();
};
//------------------------------------------------------------------------------
class T38Struct{
public:
unsigned remoteT38port;
unsigned localT38port;
string T38FaxVersion;
int T38MaxBitRate;
int T38FaxFillBitRemoval;
int T38FaxTranscodingMMR;
int T38FaxTranscodingJBIG;
string T38FaxRateManagement;
int T38FaxMaxBuffer;
int T38FaxMaxDatagram;
string T38FaxUdpEC;
vector<string> T38Attrib;
__fastcall T38Struct(){remoteT38port = 0;localT38port = 0;T38MaxBitRate = -1;T38FaxFillBitRemoval = -1;T38FaxTranscodingMMR = -1,
                       T38FaxTranscodingJBIG = -1;T38FaxMaxBuffer = 0;T38FaxMaxDatagram = 0;
                      }
};
//-----------------------------------------------------------------------------
class TSdpMediaCont{
public:
MediaCont_Subtype mcs;
TTransferFilePar  tfp;
bool audio;
bool video;
string audio_direction; //"sendrecv", "sendonly", "recvonly"
string video_direction; //"sendrecv", "sendonly", "recvonly"
#ifdef SIP_Video
TVcamPar vcpar;
#endif
int    src_of_call; //see AudioCall_PPH(const string&)
string src_callid;  //  src_of_call and  src_callid used if call initiated by parallel phone
__fastcall TSdpMediaCont(){
                           mcs = MediaCont_Subtype_Regular;
                           audio = true; video = false;
                           audio_direction = const_sendrecv;
                           video_direction = const_sendrecv;
                           src_of_call     = 0;
                          }
};
//-----------------------------------------------------------------------------
class TFileTransSDPAttrib{
public:
string message;
string session_id;
string file_name;
string file_size;
};
//------------------------------------------------------------------------------
class TRecRouteStruct : public TBaseHeaderListStruct{ //Pointer MUST NOT be used in this class!!! We using copy of objects
public:
};
//-----------------------------------------------------------------------------
class TSstIpDial
{
public:
unsigned char byte1;
unsigned char byte2;
unsigned char byte3;
unsigned char byte4;
int NumOfDigits;
AnsiString dial;
__fastcall TSstIpDial(){NumOfDigits = 0;}
};
//------------------------------------------------------------------------------
class TRfsd
{
public:
AnsiString ToUserName;
AnsiString ToHostName;
int ToPort;
AnsiString ReqLine_ToUserName;
bool DestFromReqLine;
AnsiString FromUserName;
AnsiString FromHostName;
int FromPort;
AnsiString ContactUserName;
AnsiString ContactHostName;
int ContactPort;
int SipContactTransportType;

TSstIpDial* CallingNumber;
TSstIpDial* CalledNumber;
int ContactExpires;
unsigned DestIpAddress;
unsigned DestRtpPort;
int RtpPayloadType;
int RtpPayloadSize;
int SipALegTransportType;
int Auth;
bool Authorized;
int HeaderFielID;
AnsiString viaHostName;
int viaPort;
#ifdef Sst_CallRouter
TRefer* Refer;
TMime*  Mime;
TTrustedNodeParameters* Tnp;
#ifdef IP_Media_Server
bool RouteToIpMediaServer;
string VXML_URL;
#endif //end of #ifdef IP_Media_Server
#endif //end of #ifdef Sst_CallRouter
__fastcall TRfsd(){ToPort = -1; FromPort = -1; ContactPort = -1; SipContactTransportType = -1;
                   DestFromReqLine = false;
                   ContactExpires = -1; CallingNumber = NULL; CalledNumber = NULL;
                   DestIpAddress = -1; DestRtpPort = -1;RtpPayloadType = -1;RtpPayloadSize = -1;
                   SipALegTransportType = -1; Auth = 0;Authorized=false;HeaderFielID = 0;viaPort = -1;
                   #ifdef Sst_CallRouter
                   Refer = NULL; Mime = NULL; Tnp = NULL;
                   #ifdef IP_Media_Server
                   RouteToIpMediaServer = false;
                   #endif
                   #endif
                   }
__fastcall ~TRfsd(){
                    if(CallingNumber)
                      delete CallingNumber;
                    if(CalledNumber)
                      delete CalledNumber;
                    #ifdef Sst_CallRouter
                    if(Refer)
                      delete Refer;
                    if(Mime)
                      delete Mime;
                    if(Tnp)
                      delete Tnp;
                    #endif
                   }
};
//------------------------------------------------------------------------------
class TXmlBuf{
bool  __sdp_rcvd;
  class TTuple{
        public:
        string basic;
        };
  class TPerson{
        bool  __fastcall pars_rpid(const string&,queue<string>&,int&);
        public:
        string person;
        string activities1;
        string activities2;
        string note;
        void __fastcall pars_activities(const string&);
        };
string __fastcall parsing_block(const string&,const string&,const string&);
public:
TTuple  Tuple;
TPerson Person;

void __fastcall procSdp(const string&);

void __fastcall set_sdp_rcvd(bool a){__sdp_rcvd = a;}
bool __fastcall get_sdp_rcvd(){return __sdp_rcvd;}

__fastcall TXmlBuf(){
                __sdp_rcvd = false;
                  }
};
//------------------------------------------------------------------------------
class TSipParsBuf : public BaseExchangeBlock{
public:
TCallID call_id;
string callingParty;
string clngDisplayName;

string ReqStatusLine;

string MaxForwards;
string Server;
string Expires;
string Allow;
string SubscriptionState;
string Accept;
string Event;
string Supported;
string Warning;
string ReferTo;
string ReferredBy;
string Replaces;
string WWWAuthenticate;
string ProxyAuthenticate;
string ContentType;
string to_tag;
string from_tag;
TRecRouteStruct RrSt;
string sStatus;
int    iStatus;
void*  sipbf;

__fastcall TSipParsBuf();
__fastcall ~TSipParsBuf();
};
//---------------------------------------------------------------------------
class TSipParsThread : public TBaseThread{
int __thread_type;
protected:
bool REQ_TO_CLEAR_INCOMPLETE_SIP_TCP_MSGS;
string incomplete_sip_tcp_msgs;  // used with  #ifdef INTRN_TCP
void __fastcall ParsingSipMsg(TOutPutUdpBlock*);
bool __fastcall CheckCommand(const string&,TSipParsBuf*);
TSipParsBuf* __fastcall CreateSipParsBuf();
void  __fastcall setQUEUES_INVITE(TSipParsBuf*);
void  __fastcall setQUEUES_MESSAGE(TSipParsBuf*);
void  __fastcall setQUEUES_REGISTER(TSipParsBuf*);
void  __fastcall setQUEUES_NOTIFY(TSipParsBuf*);
void  __fastcall setQUEUES_INFO(TSipParsBuf*);
void  __fastcall setQUEUES_SUBSCRIBE(TSipParsBuf*);
void  __fastcall setQUEUES_REFER(TSipParsBuf*);
void  __fastcall setQUEUES(TSipParsBuf*);
bool  __fastcall setQUEUES_PPH(TSipParsBuf*);
void  __fastcall PreProcINVITE(TSipParsBuf*);
void  __fastcall PreProcResp(TSipParsBuf*);
void  __fastcall PreProcACK(TSipParsBuf*);
void  __fastcall PreProcBYE(TSipParsBuf*);
void  __fastcall PreProcCANCEL(TSipParsBuf*);
void  __fastcall PreProcSUBSCRIBE(TSipParsBuf*);
void  __fastcall PreProcNOTIFY(TSipParsBuf*);
void  __fastcall PreProcREFER(TSipParsBuf*);
void  __fastcall PreProcMESSAGE(TSipParsBuf*);
void  __fastcall PreProcINFO(TSipParsBuf*);
void  __fastcall PreProcREGISTER(TSipParsBuf*); //for parallel phone
bool  __fastcall unpack_h(TSipParsBuf*);
void  __fastcall getReqStatusLine(TSipParsBuf*);
void  __fastcall getheader(string&,const string&,TSipParsBuf*,int=2);
void  __fastcall getcallid(TSipParsBuf*);
void  __fastcall getsdp(TSipParsBuf*);
void  __fastcall getRespHeaders(TSipParsBuf*);
void  __fastcall getStatus(TSipParsBuf*);
void  __fastcall getouttag(TSipParsBuf*);
void  __fastcall unpackcomp(TSipParsBuf*);
void  __fastcall unpackcomp_1(TSipParsBuf*);
void  __fastcall unpackcomp_2(TSipParsBuf*);
void  __fastcall getToComponents(TSipParsBuf*,void*);
void  __fastcall getToComponentsFromReqLine(TSipParsBuf*,void*);
void  __fastcall getFromComponents(TSipParsBuf*,void*);
int   __fastcall getUserName(AnsiString&,const string&);
int   __fastcall getUserName(string&,const string&);
int   __fastcall getAltUserName(AnsiString&,const string&);
int   __fastcall getAltUserName(string&,const string&);
int   __fastcall getHostName(AnsiString&,const string&,int);
int   __fastcall getHostName(string&,const string&,int);
void  __fastcall getContactComponents(TSipParsBuf*,void*);
void  __fastcall getPort(int&,const string&,int);
void  __fastcall getPort(string&,const string&,int);
void  __fastcall LOG_RecvdPacket(TOutPutUdpBlock*);

void  __fastcall proc_rcvd_sip_tcp_msg(TOutPutUdpBlock*);     //used with #ifdef INTRN_TCP
bool  __fastcall split_sip_tcp_msg(queue<TOutPutUdpBlock*>&); //used with #ifdef INTRN_TCP
void  __fastcall clear_top_of_msg();                          //used with #ifdef INTRN_TCP
int   __fastcall find_top_of_msg();
void  __fastcall log_start_stop_splitting(int);

public:
__fastcall TSipParsThread(bool CS, TEventLogThread** ELTP, TSip* SIP, int THREAD_TYPE) : TBaseThread(CS, ELTP, SIP){
                                                                __thread_type = THREAD_TYPE;   //for normal == 0, for PPH - 1
                                                                  REQ_TO_CLEAR_INCOMPLETE_SIP_TCP_MSGS = false;
                                                                  }
virtual __fastcall ~TSipParsThread();
void    __fastcall set_REQ_TO_CLEAR_INCOMPLETE_SIP_TCP_MSGS(){REQ_TO_CLEAR_INCOMPLETE_SIP_TCP_MSGS = true;}
void __fastcall Execute();
};
//---------------------------------------------------------------------------
#endif
