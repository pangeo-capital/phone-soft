#ifndef Sip_ScreenSharing_H
#define Sip_ScreenSharing_H

#include "BaseThread.h"
#include "Unit_EnterpriseSubscList.h"

#define SCREEN_SH_TCP_MAX_PACKET  8192 // 32768 // 256000  

class TCall_Panel;
class TScreenSharing__CLIENT_SEND__Thread;
class TScreenSharing__CLIENT_RECV__Thread;
//------------------------------------------------------------------------------
typedef enum{
SSCT_OUT_LOCAL,
SSCT_OUT_REMOTE,
SSCT_IN_LOCAL,
SSCT_IN_REMOTE,
}ScreenShConnectType;
//------------------------------------------------------------------------------
class TScreenSharingStruct{
public:
bool                block;
ScreenShConnectType ssct;
bool                WaitResponce; //Wait responce from server (after connect)
unsigned            send_seq_number;
string              screen_sharing_viewer_call_id;  //for screen_sharing viewer
CRITICAL_SECTION    tcp;
TScreenSharing__CLIENT_SEND__Thread* ss_CS_T;
TScreenSharing__CLIENT_RECV__Thread* ss_CR_T;
__fastcall TScreenSharingStruct(ScreenShConnectType SSCT){
           ::InitializeCriticalSection(&tcp);
           block           = false;
           ssct            = SSCT;
           send_seq_number = 0;
           WaitResponce    = false;
           ss_CS_T         = NULL;
           ss_CR_T         = NULL;
           }
virtual __fastcall ~TScreenSharingStruct();
bool    __fastcall get_local_out_addr(TIPAddress&);
void    __fastcall modify_local_addr_for_rdp_connect(TIPAddress&, string&);
string  __fastcall get_sharing_string();
void    __fastcall PrepareStart_OUT_ServerRequest();
void    __fastcall PrepareStart_IN_ServerRequest(const string&);
void    __fastcall SEND_REQUEST(TOutBlock*);
};
//------------------------------------------------------------------------------
class TScreenSharing__CLIENT_RECV__Thread : public TBaseThread{
SOCKET    slisten;
SOCKET    sck;
TScreenSharingStruct* sss;
TScreenSharingStruct* opposite_sss;
unsigned      conn_count;
unsigned      in_sh_pckt;
TDateTime     NextConnectTime;
//TCall_Panel*  call_panel;
vector<UBYTE> BUF;  //for incomplete msg
bool __fastcall get_single_ip(unsigned&,string&);
void __fastcall source_framing(vector<UBYTE>&,const vector<UBYTE>&,unsigned);
public:
unsigned       tag;       //corresponds with TCall_Panel Tag
unsigned       conf;      //if cong != true, this Thread belongs to ConfCont (not fo TCallPanel)
string         host;
int            port;
string         sharing_str;
string         sss_nick_name;
string         server_session_str;
vector<string> ip_list; //list of ip addresses getting from rdp_start_sharing()
__fastcall TScreenSharing__CLIENT_RECV__Thread(bool CS, const string& HOST, int PORT, TScreenSharingStruct* SSS, TScreenSharingStruct* OPPOSITE_SSS,
                                               TEventLogThread** ELTP, TSip* SIP):
                             TBaseThread(CS,ELTP,SIP){
                             slisten      = INVALID_SOCKET;
                             sck          = INVALID_SOCKET;
                             sss          = SSS;
                             opposite_sss = OPPOSITE_SSS;
                             conn_count   = 0;
                             in_sh_pckt   = 0;
                             host         = HOST;
                             port         = PORT;
                             tag          = 0;
                            // call_panel   = PANEL;
                             conf         = 0;
                             }
bool __fastcall Connect();
void __fastcall Receive();
void __fastcall CheckConnError();
SOCKET __fastcall get_sck(){return sck;}
void __fastcall log_tcp_socket_action(SOCKET,int);
void __fastcall set_opposite_sss(TScreenSharingStruct* OPP_SSS){opposite_sss = OPP_SSS;}
void __fastcall get_ip_list();
void __fastcall modify_sharing_string_OUT();
void __fastcall get_sharing_string(const string&);   //from received sdp
void __fastcall get_server_session_str(const string&);
void __fastcall modify_sharing_string_IN();
void __fastcall parsing_responce(vector<UBYTE>&);
bool __fastcall get_single_msg(vector<UBYTE>&,vector<UBYTE>&);
bool __fastcall check_prefix(vector<UBYTE>&);
bool __fastcall get_frame(vector<UBYTE>&,vector<UBYTE>&);
void __fastcall copy(vector<UBYTE>&, vector<UBYTE>&, int);
void __fastcall get_ack(const vector<UBYTE>&);
void __fastcall LOG_RecvPacket(vector<UBYTE>&);
void __fastcall Proc_Ack__Connect_To_Server_OUT(TServDBMsg&);
void __fastcall Proc_Ack__Connect_To_Server_IN(TServDBMsg&);
void __fastcall CloseSocket();
void __fastcall Execute();
};
//------------------------------------------------------------------------------
class TScreenSharing__CLIENT_SEND__Thread : public TBaseThread{
TScreenSharingStruct* sss;
vector<UBYTE> partial;
unsigned      out_sh_pckt;
void __fastcall unframe_source(queue<vector<UBYTE> >&, vector<UBYTE>&);
public:
     __fastcall TScreenSharing__CLIENT_SEND__Thread(bool CS, TScreenSharingStruct* SSS, TEventLogThread** ELTP, TSip* SIP):
                                                   TBaseThread(CS,ELTP,SIP){
                                                   sss   = SSS;
                                                   out_sh_pckt = 0;
                                                   }
bool   __fastcall sendbuf(TOutBlock*);
bool   __fastcall send_tcp(const char*,int);
SOCKET __fastcall get_socket();
void   __fastcall Execute();
};
//------------------------------------------------------------------------------
#endif
 