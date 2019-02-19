//---------------------------------------------------------------------------

#ifndef MediaChannelsH
#define MediaChannelsH


#include "WinRDefs.h"
//#include "Sip.h"  !!!DoNot include Sip.h in this Header

#ifndef _WINSOCK2API_
 #include <winsock2.h>
#endif

#include <map>
#include <queue>
#include "BaseThread.h"
#include "log.h"
#include "udp.h"
#include "OutPutSipBuf.h"
#include "rsrtp.h"
#include "Sound.h"
#include "Video.h"
#include "LegTrn.h"
#include "usc.h"
#include "UserAgent_defs.h"
#include "rtcp.h"

#ifdef SIP_Video
#include "vencdec.h"
#include "vencpar.h"
#endif

using namespace std;

const MFSW_MAX_PACKET = 2048;
class TUdpChannel;
//------------------------------------------------------------------------------
typedef enum{
PayLoadType_RTP,   //for tranzit only, without transcoding
PayLoadType_LINEAR,
PayLoadType_ULAW,
PayLoadType_ALAW,
PayLoadType_UNKNOWN,
}PayLoadType;
//-----------------------------------------------------------------------------
class TSRTPCrypto{
int  err_count;
bool err_threshold;
bool   __fastcall get_AES_CM_128_HMAC_SHA1_80(vector<string>&,string&);
string __fastcall get_remote_key(const string&);
public:
void*    ses;
string   protect_key;
unsigned protect_key_sz;
__fastcall TSRTPCrypto(){
                        ses            = NULL;
                        protect_key_sz = 40;
                        err_count      = 0;
                        err_threshold  = false;
                        }
virtual __fastcall ~TSRTPCrypto(){
                                 if(ses)
                                    rsrtp_drop_session(ses);
                                 }
void __fastcall create_egress_srtp_session();
void __fastcall create_ingress_srtp_session(vector<string>&);
void __fastcall printDecryptionError(TUdpChannel*,int);
void __fastcall printEncryptionError(TUdpChannel*,int);
};
//------------------------------------------------------------------------------
class TChannelDispThread : public TThread{
bool thread_block;
TEventLogThread** eltp;

TSRTPCrypto* SRTP;

CRITICAL_SECTION cdt_sc;
int suspend_count;
void __fastcall Suspend_Thread();

queue<TOutPutUdpBlock*> tosend;
deque<TOutPutUdpBlock*> sent;
int checkCount;
void __fastcall updateSentQueue(TOutPutUdpBlock*);
TUdpChannel* Uc;
CRITICAL_SECTION cs_tosend;

void __fastcall __deleteAllToSend();
void __fastcall __deleteAllSent();   //Used in ~TChannelDispThread() ONLY !!!

public:
void             __fastcall pushToSend(TOutPutUdpBlock*);
TOutPutUdpBlock* __fastcall getToSend();
int              __fastcall getSizeToSend();

void __fastcall getSent();
void __fastcall checkSent();
void __fastcall Resume_Thread();
void __fastcall set_thread_block(){thread_block = true;}
TSRTPCrypto* __fastcall getSRTP(){return SRTP;}
void         __fastcall createSRTP(){SRTP = new TSRTPCrypto;}
__fastcall TChannelDispThread(bool CS, TUdpChannel* uc, TEventLogThread** ELTP):TThread(CS){
                              ::InitializeCriticalSection(&cdt_sc);
                              ::InitializeCriticalSection(&cs_tosend);
                               Uc = uc;
                               eltp = ELTP;
                               SRTP = NULL;
                               suspend_count=0;
                               checkCount=0;
                               thread_block = false;
                               }
virtual __fastcall ~TChannelDispThread(){
                                  if(SRTP)
                                    delete SRTP;
                                __deleteAllToSend();
                                __deleteAllSent();
                                ::DeleteCriticalSection(&cdt_sc);
                                ::DeleteCriticalSection(&cs_tosend);
                                }
void __fastcall Execute();
};
//-----------------------------------------------------------------------------
class TDigitTransmitSection{
CRITICAL_SECTION dts_cs;
deque<TOutPutDtmfBlock*> q;
bool              __fastcall dtmf_queue_empty();
TOutPutDtmfBlock* __fastcall get_dtmf();
public:
TDateTime last_dtmf_sent;
TDateTime last_dtmf_duration;
unsigned  current_2833_timestamp;
__fastcall TDigitTransmitSection(){
                                  ::InitializeCriticalSection(&dts_cs);
                                  current_2833_timestamp = 0;
                                  }
virtual __fastcall ~TDigitTransmitSection(){
                                           ::DeleteCriticalSection(&dts_cs);
                                           }
void __fastcall push_dtmf(void*,TOutPutDtmfBlock*);
bool __fastcall digit_transmission(void*);
};
//-----------------------------------------------------------------------------
class TG729CODEC{
public:
int            lenDst;
int            nbanks;
USC_Fxns*      USC_Gxxx_Fnxs;
USC_CodecInfo* pInfo;
USC_MemBank*   pBanks;
char*          OutputBuffer;
__fastcall TG729CODEC(){
                       lenDst          = 0;
                       nbanks          = 0;
                       USC_Gxxx_Fnxs   = NULL;
                       pInfo           = NULL;
                       pBanks          = NULL;
                       OutputBuffer    = NULL;
                       }
virtual __fastcall ~TG729CODEC();
};
//-----------------------------------------------------------------------------
class TG729ENC : public TG729CODEC{
USC_Handle hUSCEncoder;
public:
bool __fastcall init_encoder(USC_Fxns*,int);
void __fastcall LinearToG729(TOutPutUdpBlock*);
     __fastcall TG729ENC(){
                          hUSCEncoder = NULL;
                          }
};
//------------------------------------------------------------------------------
class TG729DEC : public TG729CODEC{
USC_Handle hUSCDecoder;
public:
bool __fastcall init_decoder(USC_Fxns*,int);
void __fastcall G729_To_Linear(TOutPutUdpBlock*);
     __fastcall TG729DEC(){
                          hUSCDecoder = NULL;
                          }
};
//------------------------------------------------------------------------------
class TSendThread : public TThread{
TSip*  Sip;
CRITICAL_SECTION rhost_cs;
string sRemoteHost;
int    RemotePort;
TDateTime __dt_prev_sent_packet;
unsigned  __sent_packet_count;
bool   FirstPacketSent;
bool   FirstMediaPacketSent;
TEventLogThread** eltp;
TSRTPCrypto*      SRTP;
bool OnHold;
unsigned not_assigned_count;

CRITICAL_SECTION st_sc;
int suspend_count;
void __fastcall Suspend_Thread();

//unsigned short delay;
TDateTime dt;
TDateTime halfdt;
TDateTime nextdt;
TUdpChannel* Uc;

TG729ENC* G729ENC;

CRITICAL_SECTION optudp;
std::queue<TOutPutUdpBlock*> q;

TEventLogThread* __fastcall getLog();
void __fastcall LOG_InitialPacketSent(TOutPutUdpBlock*);
void __fastcall LOG_SendPacket(TDateTime&,TOutPutUdpBlock*,int);
void __fastcall LOG_first_20_sent_packets(int);
public:
string lasterr;
int currentSeqNumber;
int currentTimeStamp;
int sourceId;      //RTP Packet parameter
int remoteCodec;
TDigitTransmitSection DTS;
#ifdef SIP_Video
TVencPar vencpar;
#endif
void __fastcall Resume_Thread();
TOutPutUdpBlock* __fastcall getQueue();
void __fastcall clearQueue();
void __fastcall setQueue(TOutPutUdpBlock*);
int  __fastcall sendbuf(TOutPutUdpBlock*);
int  __fastcall getQueueSize();

string __fastcall getRemoteAddr();
int    __fastcall getRemotePort(){return RemotePort;}
void   __fastcall setRemoteAddress(const string& s,int port){
                                                          ::EnterCriticalSection(&rhost_cs);
                                                            sRemoteHost = s;
                                                          ::LeaveCriticalSection(&rhost_cs);
                                                          RemotePort = port;
                                                          }


void*  __fastcall getUc(){return Uc;}
bool  _fastcall ENCRYPT(TOutPutUdpBlock*);
void __fastcall prepare_2833_RtpPacket(TOutPutUdpBlock*,TOutPutDtmfBlock*);
void __fastcall prepare_audio_RtpPacket(TOutPutUdpBlock*);
void __fastcall prepare_video_RtpPacket(TOutPutUdpBlock*,TOutPutUdpBlock*);
void __fastcall setFirstRtpByte(vector<UBYTE>&,int,bool,bool,int);
void __fastcall setSecondRtpByte(vector<UBYTE>&,bool,int);
void __fastcall set2833SeqNumber(vector<UBYTE>&);
void __fastcall set2833TimeStamp(vector<UBYTE>&,TOutPutDtmfBlock*);
void __fastcall setSeqNumber(vector<UBYTE>&);
void __fastcall setTimeStamp(vector<UBYTE>&);
void __fastcall set_2833_TimeStamp(vector<UBYTE>&,TOutPutDtmfBlock*);
void __fastcall set_2833_DuplicatedTimeStamp(vector<UBYTE>&,TOutPutDtmfBlock*);
void __fastcall setTimeStamp_Video(vector<UBYTE>& v);
void __fastcall setSourceId(vector<UBYTE>&);
void __fastcall LinearToALaw(vector<UBYTE>&);
void __fastcall LinearToULaw(vector<UBYTE>&);
void __fastcall SEND_RTP_PACKET(TOutPutUdpBlock*,BaseExchangeBlock*);
void __fastcall SEND_TUNNEL_RTP_PACKET(void*);

TG729ENC*    __fastcall CREATE_G729_IPP_ENCODER();
TSRTPCrypto* __fastcall getSRTP(){return SRTP;}
void         __fastcall createSRTP(){SRTP = new TSRTPCrypto;}
void         __fastcall setOnHold(bool a){OnHold = a;}
__fastcall TSendThread(bool CS, TUdpChannel* uc, const string& remHost, int remPort, TSip* SIP, TEventLogThread** ELTP /*, unsigned short Delay = 0*/ ):TThread(CS){
                                           ::InitializeCriticalSection(&optudp);
                                           ::InitializeCriticalSection(&st_sc);
                                           ::InitializeCriticalSection(&rhost_cs);
                                           suspend_count        = 0;
                                           Uc                   = uc;
                                           Sip                  = SIP;
                                           sRemoteHost          = remHost;
                                           RemotePort           = remPort;
                                         __sent_packet_count    = 0;
                                           FirstPacketSent      = false;
                                           FirstMediaPacketSent = false;
                                           OnHold               = false;
                                           not_assigned_count   = 0;
                                           eltp = ELTP;

                                           /*
                                           delay = Delay;
                                           if(delay)
                                             {
                                             dt = TDateTime(0,0,0,delay);
                                             nextdt = nextdt.CurrentDateTime() + dt;
                                             halfdt = TDateTime(0,0,0,delay/2);
                                             }
                                            */

                                           currentSeqNumber = 0;
                                           currentTimeStamp = 0;
                                           sourceId = 0;
                                           remoteCodec = 0;
                                           G729ENC = NULL;
                                           SRTP    = NULL;
                                           }
virtual __fastcall ~TSendThread();
void  __fastcall sendlasterr();
void  __fastcall Execute();
};
//------------------------------------------------------------------------------
class TRecvThread : public TThread{
bool thread_block;
TEventLogThread** eltp;
string lasterr;
TDateTime PrevPacketTime;
int pktn;
char rcvbuf[MFSW_MAX_PACKET];
bool RemotePortAssigned;
bool FirstPacketReceived;
TUdpChannel* Uc; //TUdpChannel*
TEventLogThread* __fastcall getLog();
void __fastcall LOG_RecvdPacket(TOutPutUdpBlock*,int);
void __fastcall LOG_InitialPacketReceived(TOutPutUdpBlock*,int);
public:
__fastcall TRecvThread(bool CS, TUdpChannel* uc, TEventLogThread** ELTP):TThread(CS){
                       pktn = 0;
                       Uc   = uc;
                       eltp = ELTP;
                       RemotePortAssigned  = false;
                       FirstPacketReceived = false;
                       thread_block        = false;
                       PrevPacketTime      = PrevPacketTime.CurrentDateTime();
                       }
bool  __fastcall first_packet_rcvd(){return FirstPacketReceived;} 
void  __fastcall set_thread_block(){thread_block = true;}
void  __fastcall sendlasterr();
void  __fastcall PROC_SOCKET_ERROR();
void  __fastcall WSAECONNRESET_PROC(SOCKET);
void  __fastcall Execute();
};
//------------------------------------------------------------------------------
#ifdef Client_Test_Block
class TTestBlock{          //do not use any pointers!!!
public:
bool auto_answer;
bool local_video_rtp_loop;
bool remote_video_rtp_loop;
__fastcall TTestBlock(){
                  auto_answer           = false;
                  local_video_rtp_loop  = false;
                  remote_video_rtp_loop = false;
                  }
};
#endif
//------------------------------------------------------------------------------
class TUdpChannel{
TEventLogThread** eltp;
unsigned re_create_sck_count;
SOCKET sck;
int chID;
int reqtodelete;
string callid;
string in_out__callid;  //callid with either "in_" or "out_" prefix
int mid_cnt_thresh;
unsigned rtp_audio_packet_count;
unsigned rtp_packet_rcvd;
unsigned rtp_packet_lost;
unsigned rtp_packet_discarded;
unsigned rtp_packet_duplicated;
bool video_pause;           //for VIDEO_MPT only
MediaPacketType mpt;
deque<TUdpChannel*> myCtns; //connections this channel to other channels
deque<int> cntdToMe;        //connections other channels to this channel
void __fastcall cntdToMe_Add(int);
void __fastcall cntdToMe_Remove(int);
void __fastcall sound_packet_to_double(TOutPutUdpBlock*);
void __fastcall _try_to_get_EVEN_port();
void __fastcall _log_uc(const string&);
public:
CRITICAL_SECTION mycnts;
CRITICAL_SECTION cntdtome;
TG729DEC* G729DEC;
#ifdef Client_Test_Block
TTestBlock test_block;
#endif
int delayToTransmitPacketCount;
string lasterr;
string localhost;
int localport;
TWaveInputThread*   mic;   // Thread for microphone
TWaveOutputThread*  wopt;  // Thread for playback;
#ifdef SIP_Video
//TVideoInputThread*  vcam;      //Do not open!!!
TVideoOutputThread* vscr;
#endif
TClass_pjmedia_rtcp_session* rtcp_s;
TSendThread*        sendThread;
TChannelDispThread* chDispThread;
TRecvThread*        recvThread;
int incReqToDelete(){return ++reqtodelete;}
__fastcall TUdpChannel(MediaPacketType MPT,TEventLogThread** ELTP){
                         ::InitializeCriticalSection(&mycnts);
                         ::InitializeCriticalSection(&cntdtome);
                         sck = INVALID_SOCKET;
                         eltp = ELTP;
                         chID = 0;
                         reqtodelete         = 0;
                         re_create_sck_count = 7;     //ѕопытка переназначить SOCKET после получени€ WSAECONNRESET - через 500 ms.  MAX = 7 * 500ms = 3,5 sec
                         video_pause         = false;
                         mpt                 = MPT;
                         localport           = 0;
                         delayToTransmitPacketCount = 0;
                         G729DEC = NULL;
                         mic             = NULL;
                         wopt            = NULL;
                         #ifdef SIP_Video
                        // vcam            = NULL;
                         vscr            = NULL;
                         #endif
                         sendThread      = NULL;
                         chDispThread    = NULL;
                         recvThread      = NULL;
                        // recvDispThread  = NULL;
                        // transFileThread = NULL;
                        rtp_audio_packet_count = 0;
                        rtp_packet_rcvd        = 0;
                        rtp_packet_lost        = 0;
                        rtp_packet_discarded   = 0;
                        rtp_packet_duplicated  = 0;
                        mid_cnt_thresh         = 0;
                        rtcp_s                 = NULL;
                        }
virtual __fastcall ~TUdpChannel(){
                         printStartDeleteChannel();
                         if(recvThread)
                            recvThread->set_thread_block();
                         if(chDispThread)
                            chDispThread->set_thread_block();
                         if(G729DEC)
                           delete G729DEC;
                         if(mic)
                           {
                          _log_uc("mic terminate...");
                           mic->WIS  = WaveInputState_DESTROY;
                           TWaveInputThread* MIC = mic;
                           mic = NULL;
                           MIC->AEC.TerminateReq = true; //for terminate AEC dll
                           MIC->Resume_Thread();
                           MIC->WaitFor();
                           delete MIC;
                          _log_uc("mic terminated");
                           }
                         if(wopt)
                           {
                          _log_uc("wopt terminate...");
                           wopt->DESTROY_REQUEST = true;
                           if(wopt->f)
                             fclose(wopt->f);
                           TWaveOutputThread* WOPT = wopt;
                           wopt = NULL;
                           rtp_packet_rcvd       = WOPT->SNC.get_rcvd_count();
                           rtp_packet_lost       = WOPT->SNC.get_loss_count();
                           rtp_packet_discarded  = WOPT->SNC.get_discarded_count();
                           rtp_packet_duplicated = WOPT->SNC.get_dupl_count();
                           WOPT->Resume_Thread();
                           WOPT->WaitFor();
                           delete WOPT;
                          _log_uc("wopt terminated");
                           }

                         #ifdef SIP_Video
                           /*
                         if(vcam)
                           {
                           TVideoInputThread* VCAM = vcam;
                           vcam = NULL;
                           VCAM->Terminate();
                           VCAM->Resume_Thread();
                           VCAM->WaitFor();
                           delete VCAM;
                           } */

                         if(vscr)
                           {
                          _log_uc("vscr terminate...");
                           TVideoOutputThread* VSCR = vscr;
                           vscr = NULL;
                           VSCR->Terminate();
                           VSCR->Resume_Thread();
                           VSCR->WaitFor();
                           delete VSCR;
                          _log_uc("vscr terminated");
                           }
                         #endif

                         if(sendThread)
                            {
                          _log_uc("sendThread terminate...");
                            TSendThread* ST = sendThread;
                            sendThread = NULL;
                            ST->Terminate();
                            ST->Resume_Thread();
                            ST->WaitFor();
                            delete ST;
                          _log_uc("sendThread terminated");
                            }
                         if(recvThread)
                           {
                          _log_uc("recvThread terminate...");
                           recvThread->Terminate();
                           if(sck != INVALID_SOCKET)
                              {
                              closesocket(sck);
                              string s = "SOCKET " + inttostr(sck) + " closed";
                             _log_uc(s);
                              sck = INVALID_SOCKET;
                              }
                           recvThread->Resume();  //Do not use Resume_Thread() because we never Suspend thread
                           recvThread->WaitFor();
                           delete recvThread;
                          _log_uc("recvThread terminated");
                           }
                         if(chDispThread)      //Must be last deleted thread!!! Destructor TChannelDispThread calls  deleteAllToSend(); deleteAllSent();
                           {
                          _log_uc("chDispThread terminate...");
                           TChannelDispThread* CDT = chDispThread;
                           chDispThread = NULL;
                           CDT->Terminate();
                           CDT->Resume_Thread();
                           CDT->WaitFor();
                           delete CDT;
                          _log_uc("chDispThread terminated");
                           }
                        if(sck != INVALID_SOCKET)
                           {
                           closesocket(sck);
                           string s = "SOCKET " + inttostr(sck) + " closed";
                          _log_uc(s);
                           sck = INVALID_SOCKET;
                           }
                        if(rtcp_s)
                          {
                          if(rtcp_s->GET_REFERENCE_COUNT() > 1)
                             rtcp_s->DEC_REFERENCE_COUNT();
                          else
                            delete rtcp_s;
                          }
                        printChannelDeleted();
                        ::DeleteCriticalSection(&mycnts);
                        ::DeleteCriticalSection(&cntdtome);
                        }
SOCKET __fastcall getSocket(){return sck;}
void   __fastcall setSocket(SOCKET SCK){sck = SCK;}
int    __fastcall CreateUdpSocket();
unsigned __fastcall get_re_create_sck_count(){return re_create_sck_count ? re_create_sck_count-- : 0;}
bool   __fastcall SetSockOpt(int,char);
void   __fastcall decompress_sound_packet(TUdpChannel*,TOutPutUdpBlock*);
void   __fastcall sound_jbd_min_proc(int,TUdpChannel*,TOutPutUdpBlock*);
void   __fastcall SoundPacketToDouble(TOutPutUdpBlock*);
//void   __fastcall sound_jbd_min_proc_1(int,TUdpChannel*,TOutPutUdpBlock*);
TG729DEC* __fastcall CREATE_G729_IPP_DECODER();

void   __fastcall Connect(TUdpChannel*);
void   __fastcall Disconnect(TUdpChannel*);
bool   __fastcall IsConnected(TUdpChannel*);
void   __fastcall DisconnectAllMyConnections();
void   __fastcall getAllMyConnections(vector<int>&);
void   __fastcall getAllConnectionsToMe(vector<int>&);

void   __fastcall pushBufToSend(TOutPutUdpBlock*);
void   __fastcall proc_RTCP_PCKT(TOutPutUdpBlock*);
void   __fastcall checkWoptQueue();
void   __fastcall pushBufToConf(TOutPutUdpBlock*);
bool   __fastcall myCtns_Empty();
bool   __fastcall cntdToMe_Empty();
void   __fastcall INIT_Sdp_For_SRTP_Session(TSdpMedia*, SipUAThreadType);
bool   __fastcall DECRYPT(TOutPutUdpBlock*);

int    __fastcall getChId(){return chID;}
string __fastcall getCallID(){return callid;}
string __fastcall getInOutCallID(){return in_out__callid;}
bool   __fastcall get_video_pause(){return video_pause;}       //for VIDEO_MPT only
MediaPacketType __fastcall getMpt(){return mpt;}

void   __fastcall Send_VAD_EVENT();
void   __fastcall Send_Complex_VAD_EVENT(const string&);

void  __fastcall getMediaPacketType(string&);
void  __fastcall CreateNetworkThreads(unsigned,unsigned,TSip*);
unsigned  __fastcall getLocalSocketParameters(bool);
void  __fastcall setChId(int a){chID=a;}
void  __fastcall setCallID(const string& s){callid=s;}
void  __fastcall setCallID_Null(){callid.resize(0);}
void  __fastcall setInOutCallID(const string& s){in_out__callid=s;}
void  __fastcall set_video_pause(bool a){video_pause = a;}       //for VIDEO_MPT only
void  __fastcall sendlasterr(int=0);
TEventLogThread* __fastcall getLogThread();
void  __fastcall printAllMyConnections(int=0);
void  __fastcall printStartDeleteChannel();
void  __fastcall printChannelDeleted();
void  __fastcall printCryptoError(int,int);
};
//----------------------------------------------------------------------------
class TSessionChannelCollect{
public:
TUdpChannel* uc_sound;
TUdpChannel* uc_video;
TUdpChannel* uc_rtp_audio;
TUdpChannel* uc_rtcp_audio;
TUdpChannel* uc_rtp_video;
TUdpChannel* uc_rtcp_video;
__fastcall TSessionChannelCollect(){                        //Do not make destructor.This is buffer only for  transmition data in the function
                                    uc_sound      = NULL;
                                    uc_video      = NULL;
                                    uc_rtp_audio  = NULL;
                                    uc_rtcp_audio = NULL;
                                    uc_rtp_video  = NULL;
                                    uc_rtcp_video = NULL;
                                   }
};
//---------------------------------------------------------------------------
typedef map < int, TUdpChannel*, less<int>, allocator<int> >  TUdpChannelList;
//---------------------------------------------------------------------------
class TUdpChannelStruct : public TBaseThread{
int id;
public:
CRITICAL_SECTION deqint;
CRITICAL_SECTION udpcs;
std::queue<int> q_req_to_del;   // list of requested to delete channels
TUdpChannelList ucl; //list of created udp channels
__fastcall TUdpChannelStruct(bool CS, TEventLogThread** ELTP, TSip* SIP):TBaseThread(CS, ELTP, SIP){
                                                 ::InitializeCriticalSection(&deqint);
                                                 ::InitializeCriticalSection(&udpcs);
                                                 id = 0;
                                                 }
virtual __fastcall ~TUdpChannelStruct(){
                                 clear_ucl();
                               ::DeleteCriticalSection(&deqint);
                               ::DeleteCriticalSection(&udpcs);
                               }
void __fastcall insReqToDel(int a){
                                  ::EnterCriticalSection(&deqint);
                                    q_req_to_del.push(a);
                                  ::LeaveCriticalSection(&deqint);
                                  }
int __fastcall getReqToDel(){
                             int a;
                            ::EnterCriticalSection(&deqint);
                              if(q_req_to_del.empty())
                                 a=0;
                              else{
                                   a = q_req_to_del.front();
                                   q_req_to_del.pop();
                                  }
                            ::LeaveCriticalSection(&deqint);
                            return a;
                            }
int __fastcall reqToDelSize(){
                             int rv;
                             ::EnterCriticalSection(&deqint);
                               rv = q_req_to_del.size();
                             ::LeaveCriticalSection(&deqint);
                             return rv;
                             }
bool __fastcall isReqToDelEmpty(){
                                 bool rv=false;
                                 ::EnterCriticalSection(&deqint);
                                   if(q_req_to_del.empty())
                                      rv=true;
                                 ::LeaveCriticalSection(&deqint);
                                 return rv;
                                 }

void __fastcall Insert(TUdpChannel* uc){
                        ::EnterCriticalSection(&udpcs);
                          ucl.insert(TUdpChannelList::value_type(++id,uc));
                          uc->setChId(id);
                        ::LeaveCriticalSection(&udpcs);
                        }
TUdpChannel* __fastcall getUdpChannel(int a){
                                       TUdpChannel* uc=NULL;
                                       ::EnterCriticalSection(&udpcs);
                                         TUdpChannelList::iterator it = ucl.find(a);
                                         if(it != ucl.end())
                                            uc = (*it).second;
                                       ::LeaveCriticalSection(&udpcs);
                                       return uc;
                                       }

TUdpChannel* __fastcall get_First_RtpAudioChannel();
#ifdef SIP_Video
TUdpChannel* __fastcall get_First_RtpVideoChannel();
#endif

void __fastcall Remove(int Ind){
                               TUdpChannel* uc=NULL;
                               ::EnterCriticalSection(&udpcs);
                                 TUdpChannelList::iterator it = ucl.find(Ind);
                                 if(it != ucl.end())
                                   {
                                   uc = (*it).second;
                                   ucl.erase(it);
                                   if(ucl.empty())
                                      id = 0;
                                   }
                               ::LeaveCriticalSection(&udpcs);
                               if(uc)
                                 delete uc;    //delete TUdpChannel* outside of CriticalSection for protect from deadlock
                               }
int __fastcall GetSize(){
                        int rv=0;
                        ::EnterCriticalSection(&udpcs);
                          rv = ucl.size();
                        ::LeaveCriticalSection(&udpcs);
                        return rv;
                        }
void __fastcall getAllBusiedChannels(vector<string>&);
void __fastcall clear_ucl();

void __fastcall Create_RTP_PairCh(MediaPacketType,TUdpChannel**,TUdpChannel**,void*,unsigned,unsigned,BaseExchangeBlock*);
void __fastcall Create_RTP_SoundTestCh(TUdpChannel**);
void __fastcall FFlash();
void __fastcall Execute();
};
#ifndef RTP_exsCreateUDPSocket_ADDR_ANY
//---------------------------------------------------------------------------
typedef map < int, int, less<int>, allocator<int> > TMediaPortList;
//----------------------------------------------------------------------------
class TVoipMediaPortBlock{
public:
int fport; //first port
int eport; //end  port
int lbp;   //LastBusiedPort;
int step;
CRITICAL_SECTION mpl_cs;
TMediaPortList* mpl;  //Busied Port List
__fastcall  TVoipMediaPortBlock(){
                                  ::InitializeCriticalSection(&mpl_cs);
                                  mpl = new TMediaPortList;
                                  fport = 0;eport = 0;lbp = 0;step = 4;
                                 }
virtual __fastcall ~TVoipMediaPortBlock(){
                                  if(mpl)
                                    delete mpl;
                                  ::DeleteCriticalSection(&mpl_cs);  
                                  }
bool __fastcall isPortFree(int);
void __fastcall insertPort(int);
void __fastcall freePort(int);
};
#endif //#ifndef RTP_exsCreateUDPSocket_ADDR_ANY
//------------------------------------------------------------------------------
#endif
