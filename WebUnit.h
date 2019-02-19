#ifndef Unit_Sst_Web_H
#define Unit_Sst_Web_H

#include "WinRDefs.h"
#include "ip.h"
#include <vector>
#include <queue>
#include <map>
#include <stdio.h>
#include <winsock2.h>
#include "utils.h"
#include "tls.h"

#ifndef UBYTE
typedef unsigned char UBYTE;
#endif

#define WEB_REQ_MAX_PACKET  10000

class TEventLogThread;
class TSip;
class TWebReq;
class TFileExch;
class TExchNotifyMsg;

using namespace std;

//------------------------------------------------------------------------------
class TDataWebBlock{
public:
int bread;
vector<UBYTE> v;
TDateTime dt;
  __fastcall TDataWebBlock(int SZ){  // Used on receive data
           bread = 0;
           v.resize(SZ,0);
           }
  __fastcall TDataWebBlock(){        // Used on send data
           bread = 0;
           }
  TDataWebBlock(const char* buf, int size);  // Used on receive data
};
//------------------------------------------------------------------------------
class TExchFileMsg{
int  __req_type;  //0 - request on receive file; 1 - req on send file
bool __parsed;
void __fastcall __get_file_id(TExchNotifyMsg&, int);
void __fastcall __get_file_name(TExchNotifyMsg&, int);
void __fastcall __get_thumb_id(TExchNotifyMsg&, int);
string  __received_file_storage;
public:
string s;           //<file> id='upload_6b97d1c58d8627cc0735dae8ea89619e'  name='noname.JPG'  thumb='upload_ae94977b52410eadeecf17b8d96d9d3a' </file>
string file_name;
string file_sender;    // user name of file sender (for instance 2001)
string year_month_day;
int    grid_arow;
vector<string> v;   //if(__parsed) -> v contains file_id, name, thumb from request of file receiving (from history)

string sending_file_path;
queue<string> q_cont;    //List of Contact to whom we try to send file (notification about file)

     __fastcall TExchFileMsg(int REQ_TYPE){
              __req_type  = REQ_TYPE;
              __parsed    = false;
                grid_arow = -1;
                }
int    __fastcall get_req_type(){return __req_type;}
bool   __fastcall parsed(){return __parsed;}
void   __fastcall set_parsed(bool a){__parsed = a;}
void   __fastcall parsing_notfy_msg(TExchNotifyMsg&);
string __fastcall get_substring_by_pattern(const string&); // used if(__parsed)
string __fastcall get_received_file_storage(){return __received_file_storage;}
};
//------------------------------------------------------------------------------
class TExchNotifyMsg{
public:
string file_id;
string file_name;
string thumb_id;
};
//------------------------------------------------------------------------------
class TWebBaseThread : public TThread {
CRITICAL_SECTION  __cs;
int               __suspend_count;
TEventLogThread** __eltp;
protected:
string            __lasterr;
public:
__fastcall TWebBaseThread(bool CS,TEventLogThread** ELTP) : TThread(CS){
                       ::InitializeCriticalSection(&__cs);
                       __suspend_count = 0;
                       __eltp          = ELTP;
                         }
virtual  __fastcall ~TWebBaseThread(){
                       ::DeleteCriticalSection(&__cs);
                         }
void             __fastcall Suspend_Thread();
void             __fastcall Resume_Thread();
TEventLogThread* __fastcall getLog();
void             __fastcall sendlasterr();
};
//------------------------------------------------------------------------------
class TWebPlannerTcpThread : public TWebBaseThread {
TWebReq* __WR;
string   __resource;
void     __fastcall __get_dest_ip_addr_by_dns_host();
string   __fastcall __get_default_file_storage(const string&);
string   __fastcall __get_content_type(const string&);
void     __fastcall __FILE_RECEIVE_IN_PROGRESS(int);
public:
     __fastcall TWebPlannerTcpThread(bool CS, TEventLogThread** ELTP, TWebReq* WebReq):
                                 TWebBaseThread(CS,ELTP){
                                          __WR = WebReq;
                                            }
void __fastcall PROC_OF_FILE_SENDING_REQUEST(TExchFileMsg&);
void __fastcall select_dns_host(const string&, string&, unsigned&);
void __fastcall Execute();
};

//------------------------------------------------------------------------------
class TSipRecvTls_FileTransfer_Thread : public TBaseThread{
TWebReq* __WR;
public:
void*  r;    //connection reference
string host;
int    port;
__fastcall TSipRecvTls_FileTransfer_Thread(bool CS, const string& HOST, int PORT, TEventLogThread** ELTP, TSip* SIP, TWebReq* WebReq):
                             TBaseThread(CS,ELTP,SIP){
                                                   __WR   = WebReq;
                                                     r    = (void*)0;
                                                     host = HOST;
                                                     port = PORT;
                                                     }
void* __fastcall get_r(){return r;}
void __fastcall Execute();
};
//-----------------------------------------------------------------------------
class TSipSendTls_FileTransfer_Thread : public TBaseThread{
TWebReq* __WR;
void __fastcall __sendbuf(TDataWebBlock*);
public:
void*  r;     //connection reference (Used for  EXTRN_TCP)
string host;
int    port;

/*
void __fastcall sendbuf(TOutputSipBuf*);
void __fastcall sendbuf(TOutPutUdpBlock*);
void __fastcall sendbuf(TSipParsBuf*);
*/
/*
#ifdef SIP_LogSendPacket
void __fastcall LOG_SendPacket(TDateTime&,TOutPutUdpBlock*,int);
void __fastcall LOG_SendPacket(TDateTime&,TOutPutDtmfBlock*,int);
void __fastcall LOG_SendPacket(TDateTime&,TOutputSipBuf*,int);
void __fastcall LOG_SendPacket(TDateTime&,TSipParsBuf*,int);
#endif
*/
__fastcall TSipSendTls_FileTransfer_Thread( bool CS, const string& HOST, int PORT, TEventLogThread** ELTP, TSip* SIP, TWebReq* WebReq):
                              TBaseThread(CS,ELTP,SIP){
                                                    __WR   = WebReq;
                                                      r    = (void*)0;
                                                      host = HOST;
                                                      port = PORT;
                                                      }
void __fastcall Execute();
};
//------------------------------------------------------------------------------
class TWebRecvTcpThread : public TWebBaseThread {
TWebReq*          __WR;
TDateTime         __NextConnectTime;
unsigned          __conn_count;
public:
__fastcall TWebRecvTcpThread(bool CS, TEventLogThread** ELTP, TWebReq* WebReq):
                             TWebBaseThread(CS, ELTP){
                                      __WR         = WebReq;
                                      __conn_count = 0;
                                        }
void __fastcall CheckConnError();
void __fastcall LOG_Connection(const string&, unsigned);
void __fastcall Connect();
void __fastcall Receive();
void __fastcall Execute();
};
//------------------------------------------------------------------------------
class TChunk{
public:
int len;
string s;
__fastcall TChunk(){
           len = 0;
           }
};
//------------------------------------------------------------------------------
class TReceivedChunkStruct{
CRITICAL_SECTION __rs_cs;
queue<TChunk>    __chunk_list;
bool             __received_200_OK;
bool             __received_end_chunk;
bool __fastcall  __get_chunk(const string&, int&, int);
void __fastcall  __update_chunks_queue(const TChunk&);
public:
bool   transfer_encoding_chuncked;
string chunks;
__fastcall TReceivedChunkStruct(){
         ::InitializeCriticalSection(&__rs_cs);
           transfer_encoding_chuncked = false;
         __received_200_OK    = false;
         __received_end_chunk = false;
           }
virtual __fastcall ~TReceivedChunkStruct(){
         ::DeleteCriticalSection(&__rs_cs);
           }
void     __fastcall clear_chunks_queue();
void     __fastcall get_received_chunks(const string&, int, int);

void     __fastcall set_received_200_OK(bool a){__received_200_OK = a;}
bool     __fastcall get_received_200_OK(){return __received_200_OK;}

bool     __fastcall get_received_end_chunk(){return __received_end_chunk;}
bool     __fastcall get_chunk_from_received_list(TChunk&);
};
//------------------------------------------------------------------------------
class TWebParsThread : public TWebBaseThread {
TWebReq* __WR;
FILE*    __F;
bool     __first_packet_rcvd;
int      __total_content_length;   // Общее количество байт, которые необходимо принять ( длина файла за исключением http заголовка )
int      __current_content_length; // текущее количество принятых байт

CRITICAL_SECTION sd_cs;
int           __display_index;
string        __file_id;                // Здесь __file_id необходим для сверки отображаемой строки в IM_DrawGrid по окончании загрузки (за время загрузки пользователь может может переключиться на просмотр истории другого абонента)
string        __storage_dir;            // Destination directory to which writes receiving file
string        __storage_file;
string        __year_month_day_hstry_subdir; //Для сооздания мета файла по принимаемому файлу
queue<string> __dest_list;                   //list of file receivers (list of Contact)
string        __thumb;                       //preview file for __sending_file_name. Если __thumb есть то отправляется первым и принимается первым
string        __sending_file_name;


string   __fastcall __get_file_storage();
string   __fastcall __get_rcvd_file_name();
string   __fastcall __get_file_id();
void     __fastcall __clear_address_of_file_storage();
void     __fastcall __clear_year_month_day_hstry_subdir();
void     __fastcall __clear_file_id();

int      __fastcall __GET_HTTP_RESPONCE(const string&);
void     __fastcall __proc_200_ok_resp_on_send_file(const string&);
bool     __fastcall __get_http_content_length(const string& http_header, int*);
void     __fastcall __proc_received_chunks(const string&, const string&, const string&);

void     __fastcall __WRITE_FILE(TDataWebBlock*,int,int); //file receiving
void     __fastcall __CLOSE_FILE();                       //file receiving
void     __fastcall __FILE_RECEIVED();                    //sending notif to grid and history ... "file received"

void     __fastcall __clear_dest_list();                  //file sending

bool     __fastcall __transfer_encoding_chancked(const string&, int);

public:
TReceivedChunkStruct RCS;
__fastcall TWebParsThread(bool CS, TEventLogThread** ELTP, TWebReq* WebReq):
                          TWebBaseThread(CS,ELTP){
                                    ::InitializeCriticalSection(&sd_cs);
                                    __WR                     = WebReq;
                                    __F                      = NULL;
                                    __display_index          = -1;
                                    __first_packet_rcvd      = false;
                                    __total_content_length   = 0;
                                    __current_content_length = 0;
                                      }
virtual __fastcall ~TWebParsThread(){
                                  __CLOSE_FILE();
                                  ::DeleteCriticalSection(&sd_cs);
                                    }

void   __fastcall assign_display_and_htry_index(int);
void   __fastcall assign_file_id(const string&);
void   __fastcall assign_file_storage(const string&, const string&);
void   __fastcall assign_FILE(FILE*);
void   __fastcall assign_hstry_subdir(const string&);
void   __fastcall assign_dest_list(const queue<string>&); //for file sending
bool   __fastcall get_dest(string&);                      //for file sending (at the end of file sending)

void   __fastcall assign_thumb(const string&);
string __fastcall get_thumb();

void   __fastcall assign_sending_file_name(const string&);
string __fastcall get_sending_file_name();

void __fastcall Execute();
};
//------------------------------------------------------------------------------
class TWebSendTcpThread : public TWebBaseThread {
TWebReq* __WR;
void __fastcall __sendbuf(TDataWebBlock*);
public:
__fastcall TWebSendTcpThread(bool CS, TEventLogThread** ELTP, TWebReq* WebReq):
                             TWebBaseThread(CS,ELTP){
                                      __WR = WebReq;
                                        }
void __fastcall Execute();
};
//------------------------------------------------------------------------------
class TWebReq{
TFileExch*          __fexch;
int                 __req_type; //0 - receiving file, 1 - sending file
SOCKET              __sck;
bool                __connected;
bool __wait_connected;
bool                __delete_req;
int                 __transport;
string              __dns_host;  //".dyndns-work.com"
string              __host;      //ip   Connect To
unsigned            __port;      //port Connect To
string              __tcp_resource;
string              __tls_resource;
queue <TIPAddress>  __q;               //destination ip addreses, received by gethostbyname(dns_host.c_str())

int                 __state_of_file_transfer;  //0 - idle, 1 - reciving or send file state, 3 - was received or sent all list

CRITICAL_SECTION       __q_rcvd_cs;
queue<TDataWebBlock*>  __q_rcvd;

CRITICAL_SECTION       __q_send_cs;
queue<TDataWebBlock*>  __q_send;

public:
  TWebPlannerTcpThread* wit;
  TWebRecvTcpThread* wrt;
  TWebParsThread*    wpt;
  TWebSendTcpThread* wst;

  TSipRecvTls_FileTransfer_Thread* sr_tls_ft_t;
  TSipSendTls_FileTransfer_Thread* ss_tls_ft_t;

        __fastcall TWebReq(int transport, TFileExch* FEXCH){
                 ::InitializeCriticalSection(&__q_rcvd_cs);
                 ::InitializeCriticalSection(&__q_send_cs);
                 __fexch        = FEXCH;
                 __req_type     = 0;      //Receive file (by default)
                 __connected    = false;
                 __delete_req   = false;
                 __sck          = INVALID_SOCKET;
                 __transport    = transport;      // 0 - TCP web request, 1 - TLS web request
                 __port         = 80;            // Default. Wil be set from either __tcp_resource or __tls_resource
                 __tcp_resource = ".dyndns-work.com:25069";
                 __tls_resource = ".dyndns-work.com:25070";
                 __state_of_file_transfer = 0; //idle
                   wit          = NULL;

                   wrt          = NULL;
                   wpt          = NULL;
                   wst          = NULL;

                   sr_tls_ft_t  = NULL;
                   ss_tls_ft_t  = NULL;

                   INIT(); //!!!
                   }
  virtual __fastcall ~TWebReq();

  void           __fastcall PUSH_RCVD_BLOCK(TDataWebBlock*);
  TDataWebBlock* __fastcall GET_RCVD_BLOCK();
  void           __fastcall CLEAR_RCVD_QUEUE();

  void           __fastcall PUSH_SEND_BLOCK(TDataWebBlock*);
  TDataWebBlock* __fastcall GET_SEND_BLOCK();
  int            __fastcall SIZE_OF_SEND_QUEUE();
  void           __fastcall CLEAR_SEND_QUEUE();

  TFileExch*     __fastcall get_fexch(){return __fexch;}

  void           __fastcall set_req_type(int a){__req_type = a;}
  int            __fastcall get_req_type(){return __req_type;}

  void     __fastcall  set_connected(bool a) { __connected = a;}
  bool     __fastcall  connected(){return __connected;}
  bool     __fastcall  is_wait_connect(){return __wait_connected;}
  void     __fastcall  set_wait_connect(bool value){__wait_connected = value; }

  bool     __fastcall  get_delete_req(){return __delete_req;}

  void     __fastcall  set_socket(SOCKET sck){__sck = sck;}
  SOCKET   __fastcall  getsck(){return __sck;}
  void     __fastcall  CLOSE_SOCKET();

  string   __fastcall  get_tcp_resource(){return __tcp_resource;}
  string   __fastcall  get_tls_resource(){return __tls_resource;}

  int      __fastcall  get_transport(){return __transport;}

  void     __fastcall  set_dns_host(const string& s){__dns_host = s;}

  void     __fastcall  set_host(const string& s){__host = s;}
  void     __fastcall  set_port(unsigned port){__port = port;}

  string   __fastcall  get_host(){return __host;}
  unsigned __fastcall  get_port(){return __port;}

  string   __fastcall  get_dns_host(){return __dns_host;}
  string   __fastcall  get_first_dest_ip_addr();

  void     __fastcall  dest_ip_push(TIPAddress& a){__q.push(a);}

  bool     __fastcall  file_transfer_in_progress(){return __state_of_file_transfer == 1 ? true : false; }
  bool     __fastcall  request_list_empty(){return __state_of_file_transfer == 3 ? true : false; }
  void     __fastcall  set_idle_state_of_file_transfer(){__state_of_file_transfer = 0;}
  void     __fastcall  set_state_of_file_transfer(int a){__state_of_file_transfer = a;}

  void     __fastcall  INIT();
};
//------------------------------------------------------------------------------
class TFileExch{
CRITICAL_SECTION fexch_cs;
queue <TExchFileMsg> q;
string __default_subdir_of_received_file_storage;  //Если TExchFileMsg не содержит директории (полной, т.е. "C:\\ ..." то тогда берется эта поддиректория и вместе c MainFormSLS->client_dir формируется дир по умолчанию
public:
TWebReq* WebReq;
__fastcall TFileExch(){
         ::InitializeCriticalSection(&fexch_cs);
           WebReq = NULL;
         __default_subdir_of_received_file_storage = "FILES";
           }
virtual __fastcall ~TFileExch(){
          if(WebReq)
            {
            TWebReq* wr = WebReq;
            WebReq = NULL;
            delete wr;
            }
          ::DeleteCriticalSection(&fexch_cs);
           }
bool   __fastcall fexch_empty();
void   __fastcall fexch_ins(/* IN */ TExchFileMsg&);
bool   __fastcall fexch_get(/* OUT */ TExchFileMsg&);
void   __fastcall check_file_exch_activity();
string __fastcall get_default_subdir_of_received_file_storage(){return __default_subdir_of_received_file_storage;}
};
//------------------------------------------------------------------------------
#endif //#ifndef Unit_Sst_Web_H

