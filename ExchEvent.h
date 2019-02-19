#ifndef Exch_Event_H
#define Exch_Event_H

#include "WinRDefs.h"
#include "SipLegState.h"
#include "wm_def.h"
#include "utils.h"
//------------------------------------------------------------------------------
typedef enum{
ExchMsgType_Unknown,
ExchMsgType_Registered,
ExchMsgType_RegisterFailed,
ExchMsgType_Resp100,
ExchMsgType_Resp180,
ExchMsgType_Resp183,
ExchMsgType_Presence,
ExchMsgType_200OK_ON_INVITEREQ,
//ExchMsgType_Auth_Req_ON_INVITE,
//ExchMsgType_Auth_Req_ON_REGISTER,
//ExchMsgType_Auth_Req_ON_MESSAGE,
ExchMsgType_NotAcceptable,
ExchMsgType_Busy,
ExchMsgType_Bye,
ExchMsgType_Bye_From_Pph,
ExchMsgType_INVITE,
ExchMsgType_RCVD_REINVITE_WITH_ADD_VIDEO,
ExchMsgType_RCVD_INVITE_ON_CALL_TRANSFER,
ExchMsgType_RCVD_200OK_ON_CALL_TRANSFER,
ExchMsgType_INVITE_IN_ScreenSharing,
ExchMsgType_INVITE_AUTO_ANS,
ExchMsgType_REGISTER,
ExchMsgType_CANCEL,
ExchMsgType_SUBSCRIBE_RCVD,
ExchMsgType_NEWTWORK_NOTIFY_PARAMETERS,
ExchMsgType_MESSAGE,
ExchMsgType_Answer,
ExchMsgType_Decline,
ExchMsgType_Cancel_Out,
ExchMsgType_Busy_Out,
ExchMsgType_Bye_Out,
ExchMsgType_Cancel_In,
ExchMsgType_Bye_In,
ExchMsgType_VideoOut,
ExchMsgType_VideoOut_REINVITE,      //Add Video to Audio Call
ExchMsgType_Video_Out_Disconnect,
ExchMsgType_Video_In_Disconnect,
ExchMsgType_Show_Remote_Video,
ExchMsgType_Update_Remote_Video,
ExchMsgType_Call_OnHold,
ExchMsgType_Call_Resume,
ExchMsgType_DeleteMediaSession,
ExchMsgType_FileTransfer_Notification, //Notification ... "file alredy on server"
ExchMsgType_FileTransfer_FileReceived,
ExchMsgType_FileTransfer_InProgress,
}ExchMsgType;
//------------------------------------------------------------------------------
class TRemoteMedia : public BaseExchangeBlock{
public:
string audio_ipaddr;
int audio_port;
vector<int> audio_codecs;
#ifdef SIP_Video
string video_ipaddr;
int video_port;
vector<int> video_codecs;
#endif
string callid;
__fastcall TRemoteMedia():BaseExchangeBlock(TRemoteMedia_BLOCKTYPE){
                                                                   audio_port=-1;
                                                                   #ifdef SIP_Video
                                                                   video_port=-1;
                                                                   #endif
                                                                   }
};
//------------------------------------------------------------------------------
class TAuthPar : public BaseExchangeBlock{
public:
SipLegState sls;
string rcvdrealm;
string rcvdnonce;
string rcvdopaque;
string calc_response;

string user_name;
string user_pwd;
string domain;
string callid;
__fastcall TAuthPar():BaseExchangeBlock(TAuthPar_BLOCKTYPE){sls = SPS_UNKNOWN;}
};
//--------------------------------------------------------------------------------
class TCOORD{
public:
int top;
int left;
int height;
int width;
int period;  //For top row (date)
__fastcall TCOORD(){top = 0; left = 5; height = 0; width = 0; period = 0;}
};
/*
//---------------------------------------------------------------------------
//-- ссылка на всей длине между top;left and bottom;right не содержит пробелов !!!
//--------------------------------------------------------------------------------
class TWebRefBase{
public:
int top;    // номер строки содержащей начало ссылки (или top in pixels)  (top of reference begin)
int left;   // позиция начального символа ссылки в строке (left of reference begin)
int bottom; // номер строки содержащей окончание ссылки
int right;  // позиция конечного символа ссылки в строке
string full_ref;
string inet_addr;
string ref;
__fastcall TWebRefBase(){
                        top    = 0; left  = 0;
                        bottom = 0; right = 0;
                        }
__fastcall TWebRefBase(int TOP, int LEFT, int BOTTOM, int RIGHT){
                        top    = TOP; left  = LEFT;
                        bottom = BOTTOM; right = RIGHT;
                        }
};
*/
//----------------------------------------------------------------------------
//-- coord - содержит координаты ссылки (X,Y). В одной TImSubStr может быть одна или
//-- несколько ссылок или одна ссылка может занимать несколько TImSubStr's
//----------------------------------------------------------------------------
class TWebRef{
public:
TCOORD coord;
};
//------------------------------------------------------------------------------
//typedef multimap < unsigned, TWebRefBase > TRefList; //first - номер строки в которой найден "<a href="
//------------------------------------------------------------------------------
class TStringsVect{
int __top;
int __left;
int __type; //0 - normal IM message, 1 - invitration on file receiving

string __file_id;
string __file_name;
string __thumb_id;

void __fastcall __parsing_notfy_of_recv_file_msg(const string&, int);
void __fastcall __get_file_id(const string&, int);   //For file transfer
void __fastcall __get_file_name(const string&, int); //For file transfer
void __fastcall __get_thumb_id(const string&, int);  //For file transfer

//#ifdef Receive_IM_reference_like_HTML_ref
//void __fastcall __get_ref_strings();
//#endif
public:
vector<string> v; //Здесь хранится строка SDP, разбитая на подстроки, которая была получена в MESSAGE
//TRefList RL;      //Здесь хранится информация о ссылках, включенных а MESSAGE
bool   __fastcall check_on_file_receiving(const string&);
int    __fastcall get_msg_type(){return  __type;}
string __fastcall get_file_id(){return   __file_id;}
string __fastcall get_file_name(){return __file_name;}
string __fastcall get_thumb_id(){return  __thumb_id;}

     __fastcall TStringsVect(){
                         __top  = 0; __left = 0;
                         __type = 0;
                         }
//void __fastcall find_href_inclusions();
//void __fastcall get_all_refs_by_str(int, vector<TWebRefBase>&);
};
//------------------------------------------------------------------------------
class TExchBuf{
void* addbuf;
public:
WM_APP_MSG_WPARAM WPARAM;
ExchMsgType emt;
string callid;
string msg;
string msg_1;
string msg_2;
string msg_3;
string msg_4;
string msg_5;
string msg_6;
int    tag;
int    tag_1;
int    a1;
bool   b1;
bool   parallel_phone;
int    pr_lt_pph;  //primary_legtype_pph - соотвествует LegType, но int т.к. проблема с включениеи=м heder_a;
SipLegState sls_buf;
TStringsVect* SV;
void __fastcall setAddBuf(void* a){addbuf = a; tag = 0; tag_1 = 0;}
bool __fastcall isAddBuf(){
                          if(addbuf)
                             return true;
                          return false;
                          }
void* __fastcall getAddBuf_Reset(){
                            void* rv = addbuf;
                            addbuf   = NULL; //!!!
                            return rv;
                            }
__fastcall TExchBuf(WM_APP_MSG_WPARAM wparam){tag = -1; tag_1 = -1; a1 = 0; b1 = false; parallel_phone = false; WPARAM = wparam; addbuf=NULL;
                    emt       = ExchMsgType_Unknown;
                    sls_buf   = SPS_UNKNOWN;
                    pr_lt_pph = 0;
                    SV        = NULL;
                    }
virtual __fastcall ~TExchBuf(){
                      if(addbuf)
                         exsDeleteSentBlock(addbuf);
                      if(SV)
                         delete SV;
                      }
};
//------------------------------------------------------------------------------
#endif
