//---------------------------------------------------------------------------

#ifndef SipClient_UnitH
#define SipClient_UnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <inifiles.hpp>
#include "WinRDefs.h"
#include "wm_def.h"
#include "log.h"
#include "Sip.h"
#include "StunClient.h"
#include <Buttons.hpp>
#include <Graphics.hpp>
#include <ComCtrls.hpp>
#include <Grids.hpp>
#include <ImgList.hpp>
#include <Dialogs.hpp>
#include <jpeg.hpp>
#include <Menus.hpp>
#include "CallIn_Unit.h"
#include "DialPad_Panel.h"
#include "DialPad_FORM.h"
#include "CommentPanel.h"
#include "Unit_EnterpriseSubscList.h"
#include "AudioInterface.h"
#include "ScreenSharing.h"
#include "ParallelPhone_Unit.h"
#include "WebUnit.h"

#ifdef SIP_Video
#include "videoCam.h"
#include "vencdec.h"
#endif

#include <Menus.hpp>
#include <jpeg.hpp>
#include <Dialogs.hpp>
#include "transmit_file.h"
#include "SoundTool_Unit.h"
#include "RegistryPanel_Unit.h"
#include "ServConf_Unit.h"
#include "ContactMenu_Unit.h"
#include "RBitMap.h"
#include "LastCallsFileThread_Unit.h"

#define DRAWGRID1_LEFT_SHIFT 15
#define CLIENT_INTERFACE_STYLE  1  //0-rastel 1-Skype
#define MYWM_NOTIFY         (WM_APP+100)
#define IDC_MYICON          1006

using namespace std;

class TConfPanel;
class TConferenceWin;
//---------------------------------------------------------------------------
class TIniData{
int log;
public:
TIniFile* ifl;
TSipCommonData    StunIniData;
TSipProxyData     SipProxyData;
TSipCommonData    SipLocalProxyData;
TSipCommonData    SipTunnelData;
TSipCommonData    SipLocalTunnelData;
TSipCommonData    FTransferIniData;
TSipCommonData    SipTcp;
TSipCommonData    SipTls;
TSipCommonData    SipTunnel;
TSipCommonData    SubscDB;
TSipCommonData    ScreenSharing;
TAccountIniData   AccountIniData;
TSignalIniData    SignalIniData;
TMediaIniData     MediaIniData;
TTransportIniData TransportIniData;
TG729IniData      G729IniData;
void __fastcall ReadIniData();
void __fastcall ReadLogIniData();
void __fastcall ReadStunIniData();
void __fastcall ReadSipProxyData();
void __fastcall ReadSipLocalProxyData();
void __fastcall ReadSipTunnelIniData();
void __fastcall ReadSipLocalTunnelIniData();
void __fastcall ReadFileTransferIniData();
void __fastcall ReadAccountIniData();
void __fastcall ReadSipTcpIniData();
void __fastcall ReadSipTlsIniData();
void __fastcall ReadTransport();
void __fastcall ReadSignalIniData();
void __fastcall ReadSubscDBIniData();
void __fastcall ReadScreenSharringIniData();
void __fastcall ReadMediaIniData();
void __fastcall ReadG729IniData();
void __fastcall ReadUserName();
void __fastcall ReadDomainName();
void __fastcall ReadDisplayName();
void __fastcall ReadAlertingType();
void __fastcall ReadSipTransport();
void __fastcall ReadPortRange();
void __fastcall ReadG729Annexb();
void __fastcall CheckIniData(string&);
int  __fastcall findTerminationSymbol(string&);
void __fastcall trimString(string&,int);
int  __fastcall getLog(){return log;}
__fastcall TIniData(){
                     log=0;
                     }
__fastcall ~TIniData(){
                      if(ifl)
                         delete ifl;
                      }
};
//-------------------------------------------------------------------------------------------------
//--- !!! Данный класс не должен содержать CriticalSection и указателей т.к. делаются копии объекта.
//--- !!! Do not use pointers (see devide_html_string_on_substrings())!!!!!
//-------------------------------------------------------------------------------------------------
class TImSubStr{
im_element_type iet;     //normal(plain) text or html reference (href)
void __fastcall __devide_plain_string_on_substrings(vector<TImSubStr>&, string&, bool&);
int  __fastcall __get_first_inclusion_of_start_ref(const string&);
public:
string      s;
string      href_s;
TColor      font_color;
int         font_size;
AnsiString font_name;
TCOORD coord;
bool begin;
__fastcall TImSubStr(){
                      iet = im_element_type_plain;
                      font_color = clBlack;
                      font_size  = 10; //8;
                      begin      = false;
                      }

im_element_type __fastcall get_im_element_type(){return iet;}
string          __fastcall get_substr_by_pattern(const string&);
void            __fastcall set_im_element_type(im_element_type a){iet = a;}
void            __fastcall set_top_string_initial_parameters(const string&, TColor, int);
void            __fastcall set_top_string_parameters(int, int&);
void            __fastcall check_max_width(TImSubStr**,queue<TImSubStr*>&,int);
void            __fastcall draw_string_with_web_refereces(TCanvas*, TGridDrawState, TRect&, int, int&, int&, bool&);
void            __fastcall draw_string_with_plain_text(TCanvas*, TRect&, int, int&, int&);
};
//---------------------------------------------------------------------------
typedef enum{
CC_PANEL_TYPE__GROUP_CREATE,
CC_PANEL_TYPE__NDEF,
}TCC_PANEL_TYPE;
//---------------------------------------------------------------------------
typedef map <int, TImSubStr*, less<int>, allocator<int> > TImSubStrList;
//-------------------------------------------------------------------------------------------------------------------------------
//-- !!!!! TImStr создавать только по new ---------------------------------------------------------------------------------------
//-- !!!!! Создвать в стеке (TImStr imstr) - запрещено т.к. внутри CriticalSection
//-- и любая копия с последующим удалением оригинала (напр при выходе из подпрограммы)
//-- приводит к краху оригинала (see InitialiseCriricalSecrtion(&cs) snd DeleteiseCriricalSecrtion(&cs) - работают с указателями)
//-------------------------------------------------------------------------------------------------------------------------------
class TImStr{
im_text_type __im_tt;
int          __subs_id;    //current id for substrings in issl
int          __subs_id_m;  //current id for substrings in issl_m
int          __arow;
bool         __href;       //if true,  Instant Message contains at least one web reference (http://, https://, www.)
string       __contact_name;
string       __year_month_day;
int          __FILE_TRANSFER_STATE; //0 - состояние еще не определено, 1 - transfer in PROGRESS, 2 - file RECEIVED, файл еще не получен
string       __s_file_length;
string       t_stmp;
string       t_duration;
int          v_delta;
SYSTEMTIME   systime;
bool         sing_addition;

CRITICAL_SECTION issl_cs;
TImSubStrList  __issl;
TImSubStrList    issl_m; //m - modified

int  __fastcall __calculate_row_height(int);
int  __fastcall __calculate_row_height__INSTANT_MESSAGE(int);
void __fastcall __clear_ssl();
void __fastcall __clear_issl_m();
int  __fastcall __devide_plain_string_on_substrings__ON_MOUSE_UP(TCanvas*, TImSubStr*,TImSubStr*,int,int,bool&,bool&);

public:
bool rem_user_selected;
int  display_layers;         //количество строк, выводимых в данный в данный cell (отличается от substring, которые могут выводиться в одну строку).Используется на данный момент пока только в IM_TEXT_TOP_STRING
//vector<TWebRef> webref_list; //Contains list of references to web sites in this TImStr (in other words - list of references in appropriate Instant Message)
       __fastcall  TImStr(im_text_type IM_TT)
                         {
                       ::InitializeCriticalSection(&issl_cs);
                         __im_tt               = IM_TT;
                         ::GetLocalTime(&systime);
                         __subs_id             = 0;
                         __subs_id_m           = 0;
                         __arow                = 0;
                         __href                = false;
                         __FILE_TRANSFER_STATE = 0;
                         v_delta               = 6;
                         sing_addition         = false;
                         rem_user_selected     = false;
                         display_layers        = 1;
                         }
virtual  __fastcall ~TImStr();

im_text_type __fastcall get_im_tt(){return __im_tt;}
bool   __fastcall read_time_stmp(FILE*);
void   __fastcall read_time_stmp(string&);
void   __fastcall time_stmp_to_str();
void   __fastcall set_duration(const string& s){if(!s.empty())t_duration = s;}
string __fastcall get_duration(){return t_duration;}
string __fastcall get_time_stmp(){return t_stmp;}
void   __fastcall SET_ROW_HEIGHT(int);
void   __fastcall set_top_row_height();
void   __fastcall addSubStr(TImSubStr*);

void   __fastcall copy_of_issl_strings( vector<string>&);
void   __fastcall copy_of_issl_strings(queue<string>&);
void   __fastcall copy_of_issl_elements(queue<TImSubStr>&);

void   __fastcall set_arow(int a){__arow = a;}
int    __fastcall get_arow(){return __arow;}

void   __fastcall set_file_length(int a);
string __fastcall get_file_length(){return __s_file_length;}

void   __fastcall set_file_transfer_state__PROGRESS(){__FILE_TRANSFER_STATE = 1;}
void   __fastcall set_file_transfer_state__RECVD(){__FILE_TRANSFER_STATE = 2;}
void   __fastcall set_file_transfer_state__NOT_RECVD(){__FILE_TRANSFER_STATE = 3;}
int    __fastcall get_file_transfer_state(){return __FILE_TRANSFER_STATE;}

int    __fastcall get_v_delta(){return v_delta;}
void   __fastcall set_single_addition(bool a){sing_addition = a;}
bool   __fastcall single_addition(){return sing_addition;}
void   __fastcall write_tmstmp(FILE*);
void   __fastcall write_call_duration(FILE*);
void   __fastcall HSTRY_SAVE(const vector<string>&,TExchBuf*);
void   __fastcall hstry_add_empty_substr();
void   __fastcall hstry_substrs(const vector<string>&);
void   __fastcall hstry_tstmp(FILE*);
void   __fastcall hstry_call_duration(FILE*,string&);

void   __fastcall set_contact_name(const string& s){__contact_name = s;}
string __fastcall get_contact_name(){return __contact_name;}

void   __fastcall set_year_month_day(const string& s){__year_month_day = s;}
string __fastcall get_year_month_day(){return  __year_month_day;}

bool   __fastcall get_href(){return __href;}
void   __fastcall check_local_im_substr_on_ref(const string&);
void   __fastcall check_remote_im_substr_on_ref(const string&);

//void   __fastcall check_on_href();

void   __fastcall SELECT_AND_OPEN_WEB_REFERENCE(TDrawGrid*, int, int, int, int);
void   __fastcall DRAW_IM_SUBSTRINGS(TCanvas*, TGridDrawState, TRect&);

SYSTEMTIME& __fastcall get_systemtime(){return systime;}
};
//---------------------------------------------------------------------------
class TLastMsgSender{
string last_msg_sender;
public:
im_text_type imtt;
string       remote_user_name; //used only for sending msg from local comp
string __fastcall get_last_msg_sender(){return last_msg_sender;}
void   __fastcall set_last_msg_sender(const string& s,im_text_type IMTT){
                                                                        last_msg_sender = s;
                                                                        imtt = IMTT;
                                                                        }
__fastcall TLastMsgSender(){
                            imtt = im_text_type_ndef;
                           }
};
//---------------------------------------------------------------------------
/*
class TMissedCall{
int count;  //Count of missed calls from clien "name"
public:
string name;
__fastcall TMissedCall(string s){
                        count = 1;
                        name  = s;
                        }
void __fastcall inc_count(){++count;}
};
*/
//---------------------------------------------------------------------------
class TInsMsgMissedStruct{
deque<string> q;
public:
void   __fastcall push(const string& s){q.push_back(s);}
bool   __fastcall clear(const string&);
bool   __fastcall saved(const string&);
string __fastcall back();
int    __fastcall size(){return q.size();}
};
//---------------------------------------------------------------------------
class TMissedCallStruct{
//typedef map < string, TMissedCall > TMissedCallList;
//TMissedCallList mcl;
public:
TInsMsgMissedStruct IMMS;
bool   __fastcall save_im_sender_name(const string&);
void   __fastcall clear_im_sender_name(const string&);
string __fastcall get_im_last_sender();
//void __fastcall
//void __fastcall update(const string&);
//void __fastcall erase(const string&);
};
//---------------------------------------------------------------------------
typedef map <int, TImStr*, less<int>, allocator<int> > TImStrList;
//---------------------------------------------------------------------------
class TIM_Struct{
int _id;
string selected_remote_user;
CRITICAL_SECTION isl_cs;
TImStrList isl;    //Работа с isl возможна в основном и в любых других потоках. !!!Работа с IM_DrawGrid возможна только в основном потоке
string __fn;       //full_name for clients not including in abonent list
string __show_dir; //Temp directory for "Показать в папке"
void __fastcall _clear_im_str_list_FINALLY();
void __fastcall _set_top_string();
bool __fastcall _read_history_block(FILE*, const string&, const string&);
bool __fastcall _find_start_of_block(im_text_type&,FILE*);
bool __fastcall _get_block_size(unsigned&,FILE*);
void __fastcall _erase_trail(string&);
bool __fastcall _read_block_content(vector<string>&,unsigned,FILE*);
im_text_type __fastcall _int_to_im_text_type(int);
bool __fastcall _empty(){
                        bool rv = false;
                        ::EnterCriticalSection(&isl_cs);
                          rv = isl.empty();
                        ::LeaveCriticalSection(&isl_cs);
                        return rv;
                        }
public:
TMissedCallStruct MCS;
TLastMsgSender    LMS;
TLastCallsFileThread* LCFT;
int curr_hstry_period;
string remote_im_client;
        __fastcall  TIM_Struct(){
                                ::InitializeCriticalSection(&isl_cs);
                                _id=0;
                                curr_hstry_period = -1;
                                LCFT = new TLastCallsFileThread(true);
                                }
  virtual __fastcall ~TIM_Struct();
TImStr* __fastcall  getStr(int a){
                                 TImStr* rv = NULL;
                                 ::EnterCriticalSection(&isl_cs);
                                   TImStrList::iterator it = isl.find(a);
                                   if(it != isl.end())
                                      rv = (*it).second;
                                 ::LeaveCriticalSection(&isl_cs);
                                 return rv;
                                 }
int  __fastcall get_raw_count(){
                               int rv = 0;
                               ::EnterCriticalSection(&isl_cs);
                                 rv = isl.size();
                               ::LeaveCriticalSection(&isl_cs);
                               return rv;
                               }
void __fastcall _clear_im_str_list();
void __fastcall addStr_by_read_hstry_block(TImStr*); //использовать при внесении hstry msgs блоками (при чтении файлов из директории hstry)
void __fastcall addStr(TImStr*);                     //использовать при внесении единичных записей (по окнчании вызова, при получении или отправке IM)
void __fastcall AddLastCall(const string&,const string&,bool,im_text_type);
void __fastcall dissect_html_text_msg(const string&,TExchBuf*);
void __fastcall dissect_plain_text_msg(const string&,TExchBuf*);
void __fastcall devide_html_msg_by_strings(vector<string>&,string&);
void __fastcall devide_plain_msg_by_strings(vector<string>&,string&);
void __fastcall update(const string&, TExchBuf*, im_text_type);
void __fastcall update_IM(/*const*/ vector<string>&, TExchBuf*, im_text_type);
string __fastcall get_selected_remote_user(){return selected_remote_user;}
void   __fastcall set_selected_remote_user(const string& s){selected_remote_user = s;}
void   __fastcall clear_selected_remote_user(){selected_remote_user.clear();}
void   __fastcall load_user_history();
void   __fastcall load_user_history(TDateTime&,TDateTime&);
void   __fastcall read_user_history(FILE*, const string&, const string&);
void   __fastcall insert_date_string(const SYSTEMTIME&);

void   __fastcall set_fn(string s){__fn = s;}
string __fastcall get_fn(){return __fn;}
void   __fastcall clear_fn(){__fn.clear();}

void   __fastcall clear_show_dir();
void   __fastcall set_show_dir(const string&);
string __fastcall get_show_dir();

void   __fastcall set_state_of_file_transfer_PROGRESS(int);
void   __fastcall set_state_of_file_transfer_RECEIVED(int,int,const string&);

bool   __fastcall create_file_downloading_path(TImStr*, int);
void   __fastcall create_file_sending_path(TImStr*);

void   __fastcall SetRowHeightsForLast_25_HSTRY_Msgs(TDrawGrid*);
void   __fastcall USER_HSTRY_LOAD(const SYSTEMTIME&,const SYSTEMTIME&);
void   __fastcall HSTRY_SAVE_AND_DISPLAY(TExchBuf*,TImStr*,const vector<string>&);
};
//---------------------------------------------------------------------------
class TBaseTstmp{
protected:
bool ready;  //Protect from duplication of get_tstmp()
public:
     __fastcall TBaseTstmp(){ready = false;}
bool __fastcall get_ready(){return ready;}
void __fastcall set_ready(){ready = true;}
};
//---------------------------------------------------------------------------
class TCallTstmp : public TBaseTstmp{
public:
TDateTime tstmp;
void __fastcall get_tstmp();
};
//---------------------------------------------------------------------------
class TCallDuration : public TBaseTstmp{
public:
TDateTime duration;
string    s_duration;
void  __fastcall duration_to_str();
};
//---------------------------------------------------------------------------
//----------- Time Stamps ---------------------------------------------------
//---------------------------------------------------------------------------
class TTstmps{
public:
TCallTstmp    conv_start;
TCallTstmp    conv_stop;
TCallDuration conv_duration;
void __fastcall get_conv_start_tstmp();
void __fastcall get_conv_stop_tstmp();
void __fastcall get_conv_duration();
};
//----------------------------------------------------------------------------
typedef enum{
On_Line_Active_NSI_INDX,
On_Line_Focus_NSI_INDX,
On_Line_Press_NSI_INDX,
Off_Line_Active_NSI_INDX,
Off_Line_Focus_NSI_INDX,
Off_Line_Press_NSI_INDX,
Dnd_Active_NSI_INDX,
Dnd_Focus_NSI_INDX,
Dnd_Press_NSI_INDX,
Away_Active_NSI_INDX,
Away_Focus_NSI_INDX,
Away_Press_NSI_INDX,
}TNSI_INDX;
//----------------------------------------------------------------------------
class TNetStatus_Panel : public TPanel{
public:
TImage*      NSI;
TLabel*      full_user_name;
TLabel*      comment;
CallBtnState NS;        //NetworkStatus
     __fastcall TNetStatus_Panel(TComponent* Owner);
void __fastcall NSP_MouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
void __fastcall NSI_MouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
void __fastcall NSI_MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
void __fastcall NSI_MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
void __fastcall Comment_MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
void __fastcall Clear();
void __fastcall Set_Focus();
void __fastcall Clear_Focus();
void __fastcall Set_Pressed();
TNSI_INDX __fastcall Get_Active_Indx();
TNSI_INDX __fastcall Get_Focus_Indx();
TNSI_INDX __fastcall Get_Press_Indx();
};
//-------------------------------------------------------------------------------------
/*
class TGroupName{
public:
string  name;
string  full_name;
};
*/
//-------------------------------------------------------------------------------------
//-- id   - used if ConfCont - internal (present in contact list) ---------------------
//-- name - used if ConfCont - external  ----------------------------------------------
//-- user_name - applyed for INFO req  (for internal - user_name == contact->name
//-- for external - user_name == name (from ConfCont)) --------------------------------
//-------------------------------------------------------------------------------------
class TConfCont{
public:
bool    internal;
int     id;           //for contact from my contact list (internal)
string  name;         //for external contact (internal = false)
string  full_name;
string  callid;       //this is important for sending INFO messages (for reflections participants of conference on screens of passive members)
int     cc_call_state;   //0 - waiting for answer; 1 - answered (when answered we can send to this participant information about conference members and there call states)
LegType lt;
bool    conference_creator;
string  user_name;   //need for create INFO request
int     call_panel_tag;
bool    from_enterprise_db;  //в конференцию добавляется контакт из БД предприятия. Данный абонент отсутствует в личном контакт листе
TDateTime dt_flash;         //for flashing outgoing no answered calls

bool   vad_enable;         // if(true) - разрешает отправлять VAD events пассивным участникам (т.е. if(ConfereceWin->CONFERNCE_CREATOR) and if(vad_enable) то отправлять можно).
                           // Устанавливается при получении 200 OK на ьып INFO.
                           // Пассивные участники отправляют на  conference_creator независимо от значения conference_creator

string   screen_sharing_sender_call_id; // for screen sharing sender (when screen sharing applied for conference participants)
TScreenSharingStruct* sss_loc;          // for screen sharing sender (when screen sharing applied for conference participants)
TScreenSharingStruct* sss_rem;          // for screen sharing sender (when screen sharing applied for conference participants)

TConfPanel* conf_panel;   //Used for display of conference participants image onto TConferenceWin  only
TLabel*     lbl;          //Used for display of participants full_name onto TConferenceWin  only
TLabel*     lbl1;         //Used for display of participants full_name onto TConferenceWin  only. Used for long user full_name/
TBtnImage*  ctr_disc_img; //creator_disc_btn for conf participants. This btn is visible on CONFERENCE_CREATOR ConfWin 

bool denied_of_deletion_conf_panel;

TDateTime del_time;

void __fastcall init_sss_rem(const string&, unsigned);
void __fastcall conf_cont__create_local_connection_for_OUT_screen_sharing(unsigned);
void __fastcall delete_screen_sharing_structs();

__fastcall TConfCont(){
                      ConstructMain();
                      internal           = true;
                      id                 = -1;
                      }
__fastcall TConfCont(int ID){
                      ConstructMain();
                      internal           = true;
                      id                 = ID;
                      }
__fastcall TConfCont(const string& s){
                      ConstructMain();
                      internal           = false;
                      id                 = -1;
                      name               = s;
                      user_name          = s;
                      }

void __fastcall ConstructMain(){
                   //   Conf_Win           = NULL;
                      from_enterprise_db = false;
                      cc_call_state      = 0;
                      call_panel_tag     = 0;
                      conference_creator = false;
                      vad_enable         = false;
                      lt                 = Lt_NDef; 
                      sss_loc            = NULL;
                      sss_rem            = NULL;
                      conf_panel         = NULL;
                      lbl                = NULL;
                      lbl1               = NULL;
                      ctr_disc_img       = NULL; 
                      denied_of_deletion_conf_panel = false;
                      }

virtual __fastcall ~TConfCont(){
                       if(!denied_of_deletion_conf_panel)  //Set when make copy of participants list
                         {
                          if(conf_panel)
                             delete conf_panel;
                          if(lbl)
                             delete lbl;
                          if(lbl1)
                             delete lbl1;
                          if(ctr_disc_img)
                             delete ctr_disc_img;
                          delete_screen_sharing_structs();
                         }
                       }
};
//-----------------------------------------------------------------------------
class TCall_Panel : public TPanel{
TCall_Type call_type;
Call_State call_state;
LegType    lt;          // Lt_Out - panel for Outgoing Call; Lt_In - panel for Incoming Call
int        referred_call_panel_tag;  //Используется в call_panel with call_type == Call_Type_Refer для идентификации call_panel, от которой поступил запрос на переадресацию.
TDateTime  start_play_sound;
TDateTime  dt_activate_screen_sharing;

bool file_transfer_complete;

bool RESP_200_OK_RCVD;

bool conf_host;        //if(true) - this panel is a HOST  and CREATOR of the conference
bool conf_participant; //if(true) - this panel is a PARICIPANT of the conference (MUST BE set for all participants of confrence - for HOST and for passive PARTICIPANTS)
int  conf_creator;     //(conf_owner) - call_tag of the TCall_Panel (HOST) from which  a conference was created (set for passive PARTICIPANTS of the conference !!!)

TConfCont ConfCont;
bool hstry_written;

CRITICAL_SECTION ccl_q_cs;
deque<TConfCont> ccl_q;      //Queue to Conference contact List (Before start of INVITE sending)

CRITICAL_SECTION ccl_cs;
deque<TConfCont> ccl;        //Conference Contact List

void __fastcall _img_btn_clear(TImage*);
void __fastcall _delete_conference_participant(TMediaSession*,TMediaSession*);
void __fastcall _delete_conference_participant(TMediaSession*);

public:
string   nick_name;
string   display_name;

TImage*  disc_img;
TImage*  cam_img;
TImage*  mic_img;
TImage*  speak_img;
TImage*  conf_img;
TImage*  dial_img;
TImage*  refer_img;
TImage*  screen_img;
TImage*  chat_img;
TImage*  conn_img;
TImage*  lochold_img;
TImage*  remhold_img;

bool cam_img_visible;

int disc_img__default_left;
int cam_img__default_left;
int mic_img__default_left;
int speak_img__default_left;
int conf_img__default_left;
int dial_img__default_left;
int refer_img__default_left;
int screen_img__default_left;
int chat_img__default_left;
bool default_left;

TLabel*  lb;
TLabel*  lb_1;
TLabel*  lb_2;
TButton* btn_0;
TButton* btn_1;
TProgressBar* progbar;
TTransferFilePar TFP;
TTransmitFileThread* t_trn_f;
TReceiveFileThread*  t_rcv_f;
TTstmps  tstmps;
TScreenSharingStruct* sss_loc;
TScreenSharingStruct* sss_rem;
bool     screen_sharing_active;         //активная трансляция своего экрана
string   screen_sharing_sender_call_id; // for screen sharing sender

bool     connected_to_pph;               // pph - parallel phone
string   callid_pph;                     // callid of call to parallel phone

     __fastcall TCall_Panel(TComponent* Owner);
     __fastcall ~TCall_Panel();
void __fastcall create_images();
void __fastcall create_images_on_refer();
void __fastcall create_conn_image(int);
void __fastcall create_disc_image();
void __fastcall create_cam_image();
void __fastcall create_mic_image();
void __fastcall create_speak_image();
void __fastcall create_conf_image();
void __fastcall create_dial_image();
void __fastcall create_refer_image();
void __fastcall create_lochold_image(int);
void __fastcall create_remhold_image(int);
void __fastcall create_screen_image();
void __fastcall create_chat_image();
void __fastcall create_lb();
void __fastcall create_lb_1();
void __fastcall start_time_play_sound(){start_play_sound = start_play_sound.CurrentDateTime();}
TDateTime __fastcall get_start_time_play_sound(){return start_play_sound;}

void __fastcall DiscImg_OutgoingCall_Panel_MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
void __fastcall DiscImg_IncomingCall_Panel_MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
void __fastcall Mic_Img__MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
void __fastcall Cam_Img__MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
void __fastcall Speak_Img__MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
void __fastcall Dial_Img__Mouse_Up(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
void __fastcall Conf_Img__Mouse_Up(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
void __fastcall Refer_img__Mouse_Up(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
void __fastcall LocHold_Img__Mouse_Up(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
void __fastcall Conn_Img_MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
void __fastcall Screen_Img__Mouse_Up(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
void __fastcall Chat_Img__Mouse_Up(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
void __fastcall Btn_OpenFile__MouseUp(TObject *Sender,TMouseButton Button, TShiftState Shift, int X, int Y);
void __fastcall Btn_Quit__MouseUp(TObject *Sender,TMouseButton Button, TShiftState Shift, int X, int Y);

void __fastcall Call_Panel_Resize(TObject *Sender);
void __fastcall panel_resize();

void __fastcall disconnect_incoming_call(TMediaSession*,bool);
void __fastcall disconnect_outgoing_call(TMediaSession*,bool);
void __fastcall outgoing_call_disc_out_hstry(const string&,const string&);
void __fastcall incoming_call_disc_out_hstry(const string&,const string&);
bool __fastcall get_hstry_written(){return hstry_written;}
void __fastcall set_hstry_written(bool a){hstry_written = a;}
void __fastcall set_img_visible(TImage*,bool);
void __fastcall set_img_enabled(TImage*,bool);
void __fastcall SetImgsVisible_ONHOLD();
void __fastcall SetImgsVisible_RESUME();
void __fastcall SetVisible_REM_HOLD();
void __fastcall SetInvisible_REM_HOLD();
void __fastcall draw_passive_cam_img();
void __fastcall draw_active_cam_img();

void __fastcall set_200_OK_RCVD(bool a){RESP_200_OK_RCVD = a;}
bool __fastcall get_200_OK_RCVD(){return RESP_200_OK_RCVD;}

void __fastcall conference_exit(TMediaSession*);

void       __fastcall set_referred_call_panel_tag(int a){referred_call_panel_tag = a;}
string     __fastcall PrepareReferTo_Attendant();
void       __fastcall Prepare_To_From_Contact_CSeq__ForRefer(TOutputSipBuf*,TMediaSession*);

void       __fastcall set_call_type(TCall_Type a){call_type = a;}
TCall_Type __fastcall get_call_type(){return call_type;}

void       __fastcall set_leg_type(LegType a){lt = a;}
LegType    __fastcall get_leg_type(){return lt;}

void       __fastcall set_call_state(Call_State a){call_state = a;}
Call_State __fastcall get_call_state(){return call_state;}

void       __fastcall set_conf_creator(int a){conf_creator = a;}
int        __fastcall get_conf_creator(){return conf_creator;}

bool       __fastcall get_conf_host(){return conf_host;}
void       __fastcall set_conf_host(bool a){conf_host = a;}
void       __fastcall set_conf_participant(bool a){conf_participant = a;}
bool       __fastcall get_conf_participant(){return conf_participant;}

void       __fastcall setConfCont(TConfCont* a){
                                                ConfCont.internal = a->internal;
                                                ConfCont.id       = a->id;
                                                ConfCont.name     = a->name;
                                                }
TConfCont  __fastcall getConfCont(){return ConfCont;}

void       __fastcall transf_to_incoming();
void       __fastcall transf_to_outgoing();

void       __fastcall set_file_transfer_complete(){file_transfer_complete = true;}
bool       __fastcall get_file_transfer_complete(){return file_transfer_complete;}
void       __fastcall set_receiving_file_name_label();

void       __fastcall Start_REINVITE_With_Video_Transmission(TMediaSession*);

bool      __fastcall is_ccl_q_contact(const  TConfCont&);   //is this contact in Conference List before outseize?
void      __fastcall add_ccl_q_contact(const TConfCont&);
void      __fastcall del_ccl_q_contact(const TConfCont&);
int       __fastcall get_ccl_q_size();
TConfCont __fastcall get_first_ccl_q_contact();

void  __fastcall add_ccl_contact(const TConfCont&);
void  __fastcall del_ccl_contact(const TConfCont&);
bool  __fastcall is_ccl_contact(const TConfCont&);   //is this contact in Conference ?
int   __fastcall get_ccl_size();
bool  __fastcall ccl_empty();
void  __fastcall get_ccl_copy(deque<TConfCont>&);
void  __fastcall get_ccl_copy__with_clear_screen_sharing_call_ids(deque<TConfCont>&);
void  __fastcall set_conf_cont_answered(int);
void  __fastcall init_conference_screen_sharing(const string&);
void  __fastcall screen_sharing_action();

TConfCont   __fastcall get_conf_contact_by_row(unsigned);
void        __fastcall check_on_conf_participation();
void        __fastcall check_hidden_remote_video();

void __fastcall create_local_connection_for_OUT_screen_sharing();
void __fastcall disconnect_screen_sharing();
void __fastcall delete_screen_sharing_structs();

void __fastcall create_local_OUT_conn_and_send_INVITE_to_conference_by_user_name(const string&,const string&);
void __fastcall send_disconnect_screen_sharing_to_all_conf_participants();

void __fastcall disconnect_parallel_phone();
};
//----------------------------------------------------------------------------
class TCallPanelsStruct{
::CRITICAL_SECTION cpl_cs;
deque<int> cpl;
public:
vector<int> req_to_del_panel;

__fastcall TCallPanelsStruct(){
                              ::InitializeCriticalSection(&cpl_cs);
                              }
virtual __fastcall ~TCallPanelsStruct(){
                                       ::DeleteCriticalSection(&cpl_cs);
                                       }
void __fastcall add_panel_tag(int,TDrawGrid*);
int  __fastcall get_panel_tag_by_row(int);
void __fastcall del_panel_tag(int,TDrawGrid*);
};
//----------------------------------------------------------------------------
class TSysTimer{
TDateTime time_stamp;   //for determination day changing 
public:
TTimer* timer;
void __fastcall InitTimer();
bool __fastcall day_end();
     __fastcall TSysTimer(){
                           timer = NULL;
                           time_stamp = time_stamp.CurrentTime();
                           }
};
//----------------------------------------------------------------------------
class TInCallBlock{
typedef map < const string, TForm1* >  TInCallList;  //call_id -> TForm1*
typedef map < unsigned, const string > TOrderList;   //cnt -> call_id  -- Order - порядок поступления вх вызовов
TInCallList icl;
TOrderList  ordl;
unsigned    order;
void    __fastcall icl_ins(const string&, TForm1*);
void    __fastcall ordl_del(unsigned);
void    __fastcall get_prev_call_window_coord(int&,int&);
void    __fastcall set_new_call_window_coord(TForm1*);
void    __fastcall __get_all_waiting_callids(queue<string>&);
public:
        __fastcall TInCallBlock(){order = 0;}
TForm1* __fastcall new_incoming_call(const string&);
void    __fastcall icl_del(const string&);
int     __fastcall get_incoming_waiting_ans_calls(){return icl.size();}
void    __fastcall req_to_del_in_call_window_on_receiving_CANCEL(const string&);
TForm1* __fastcall get_form_by_call_id(const string&);
void    __fastcall del_all_waiting_ans_calls();
};
//----------------------------------------------------------------------------//
// -- For notification subscribed presence clients about changing my ---------//
// -- network status ---------------------------------------------------------//
//----------------------------------------------------------------------------//
class TNotifyStruct{
ClientState       my_network_state;
bool              notify_proc_active;
bool              notify_comment_proc_active;

CRITICAL_SECTION  ns_cs;
queue<TSubscribedData> __notify_queue;
queue<TSubscribedData> __notify_comment_queue;
string                 __my_net_state_comment;

void __fastcall   reflect_my_network_state();
void __fastcall   proc_notify_queue_element();
void __fastcall   proc_notify_comment_queue_element();

public:

__fastcall TNotifyStruct(){
                         ::InitializeCriticalSection(&ns_cs);
                           notify_proc_active         = false;
                           notify_comment_proc_active = false;
                           my_network_state           = ClientState_On_Line;
                          }
virtual ~TNotifyStruct(){
                        ::DeleteCriticalSection(&ns_cs);
                        }
bool        __fastcall get_notify_proc_active(){return notify_proc_active;}
void        __fastcall set_notify_proc_active(bool a){notify_proc_active = a;}
bool        __fastcall get_notify_comment_proc_active(){return notify_comment_proc_active;}
void        __fastcall set_notify_comment_proc_active(bool a){notify_comment_proc_active = a;}
ClientState __fastcall get_my_network_state(){return my_network_state;}
void        __fastcall set_my_network_state(ClientState);
void        __fastcall init_notify_proc(ClientState);
void        __fastcall init_notify_comment_proc(const string&);
void        __fastcall notify_subscribed_clients_about_change_network_status();
void        __fastcall notify_comment();
void        __fastcall Final_Notify_Proc();

string      __fastcall get_my_net_state_comment();
void        __fastcall set_my_net_state_comment(const string&);
void        __fastcall my_net_state_comment_clear();
void        __fastcall push_notify_comment_queue(const TSubscribedData&);
void        __fastcall push_notify_queue(const TSubscribedData&);
bool        __fastcall notify_queue_empty();
bool        __fastcall notify_comment_queue_empty();
void        __fastcall clear_notify_queue();
};
//----------------------------------------------------------------------------
class TReconnectSubscribe{
CRITICAL_SECTION sqs;
bool subscr_proc_active;
queue<TContact> subscr_queue;
public:
__fastcall TReconnectSubscribe(){
                     ::InitializeCriticalSection(&sqs);
                     subscr_proc_active = false;
                     }
virtual ~TReconnectSubscribe(){
                              ::DeleteCriticalSection(&sqs);
                              }
void __fastcall set_subscr_proc_active(bool a){subscr_proc_active = a;}
bool __fastcall get_subscr_proc_active(){return subscr_proc_active;}
void __fastcall proc_subscr_queue();
void __fastcall push_contact(TContact& Contact);
void __fastcall clear();
};
//-----------------------------------------------------------------------------
class TDeleteLegTrnStruct{
CRITICAL_SECTION del_leg_trn_cs;
typedef multimap < TDateTime, TLegTrn* > TLst;
TLst Lst;
public:
void __fastcall req_to_del(TLegTrn*);
void __fastcall check_to_del();
__fastcall TDeleteLegTrnStruct(){
                                ::InitializeCriticalSection(&del_leg_trn_cs);
                                }
virtual __fastcall ~TDeleteLegTrnStruct(){
                              ::DeleteCriticalSection(&del_leg_trn_cs);
                              }
};
//----------------------------------------------------------------------------
class TScreenSharingViewer{
public:
TScreenSharingStruct* sss_loc;
TScreenSharingStruct* sss_rem;
__fastcall TScreenSharingViewer(){
                                 sss_loc = NULL;
                                 sss_rem = NULL;
                                 }
void __fastcall create_local_connection_for_IN_screen_sharing();
void __fastcall ssv_delete_screen_sharing_structs();
};
//----------------------------------------------------------------------------
#ifdef Automatic_Out_Calls
class TAutomaticOutCalls{
queue<string> q;
public:
bool     active;
unsigned phone;
unsigned num; //total call numbers 
unsigned n;   //количество вызовов за 1 проход
__fastcall TAutomaticOutCalls(){
                               active = false;
                               phone  = 6300;
                               num    = 10; //10; //100; //40; //10; //5;  //6300 -- 6300 + num -1
                               n      = 10; //10; //100;
                               }
void __fastcall activate();
void __fastcall deactivate();
void __fastcall clear();
bool __fastcall empty(){return q.empty();}
void __fastcall makecalls(); 
};
#endif
//---------------------------------------------------------------------------
class TCtrlExch{
bool actual;
public:
WM_APP_MSG_WPARAM  WPARAM;
string s1;
__fastcall TCtrlExch(){
                      actual = false;
                      WPARAM = WM_APP_MSG_WPARAM__NDEF;
                      }
void __fastcall set_actual(){actual = true;}
bool __fastcall get_actual(){return actual;}                     
};
//---------------------------------------------------------------------------
class TCtrlExchStruct{
CRITICAL_SECTION ctrl_exch_cs;
queue<TCtrlExch> q;
public:
__fastcall TCtrlExchStruct(){
                     ::InitializeCriticalSection(&ctrl_exch_cs);
                     }
virtual __fastcall ~TCtrlExchStruct(){
                    ::DeleteCriticalSection(&ctrl_exch_cs);
                    }
void      __fastcall push(const TCtrlExch&);
TCtrlExch __fastcall get();  /*
bool    __fastcall empty();
*/
};
//---------------------------------------------------------------------------
//--- Used within CC_Panel, when group is collected
//---------------------------------------------------------------------------
class TGroupChatStruct{
deque<TGroupName> __GROUP_NAMES;
int               __fname_left;
BtnState          __CreateGroupChat_BtnState;
bool   __fastcall __get_chat_member_by_row(TGroupName&, int);
int    __fastcall __get_fname_left(const TRect& Rect){return Rect.Left + __fname_left;}
int    __fastcall __get_top(const TRect& Rect){return Rect.Top + Rect.Height()/2 - SHIFT_STATE_TOP;}
public:
TCC_PANEL_TYPE       CC_PANEL_TYPE;
     __fastcall TGroupChatStruct(){
                CC_PANEL_TYPE            = CC_PANEL_TYPE__NDEF;
              __fname_left               = SHIFT_STATE_LEFT + SHIFT_FNAME_LEFT;
              __CreateGroupChat_BtnState = BtnState_INACTIVE;
                }
void       __fastcall Display_Group_Chat(TCanvas*, int, TRect&);
void       __fastcall Push(TGroupName&);
void       __fastcall Delete(int);
bool       __fastcall InQueue(TGroupName&);
TGroupName __fastcall Get();
deque<TGroupName>& __fastcall GetGroup();
unsigned   __fastcall Size(){return __GROUP_NAMES.size();}
void       __fastcall Clear(){__GROUP_NAMES.clear();}
bool       __fastcall get_group_names(string&);
BtnState   __fastcall get_CreateGroupChat_BtnState(){return __CreateGroupChat_BtnState;}
void       __fastcall set_CreateGroupChat_BtnState(TImage*,BtnState);
};
//---------------------------------------------------------------------------
class TMainFormSLS : public TForm
{
int initLeft;
int initTop;
int initWidth;
int intrfStyle;
int bot_margin;
bool _CLOSE_REQUEST;
BtnState AddToConfBtnState;
CallBtnState cbs;
CallBtnState cbsv;  // Video
string client_root; // where work dir
string client_node; // where ApplicationData -- ""
string client_name; // where ApplicationData -- "RSC"
string ini_dir;
string clients_dir; //list of registered clients on my microsoft Account
string client_dir;  //current (active) client
string log_dir;
string cont_dir;    //directory with contacts - correspond with Sip->contact_dir
string sound_dir;
string user_name_to_send;
string selected_remote_user;
int prev_height;
int prev_width;
int prev_height_for_cl;
bool req_to_close_conf_panel;
bool term_explicit;
bool __send_IM_to_conf_participants;
bool __send_IM_to_chat_participants;

TDateTime __StartDateTime;

HICON TrayIcon_Handle;

CRITICAL_SECTION callin_exchlst_cs;
deque<TExchBuf*> call_exchlst;

CRITICAL_SECTION videoout_exchlst_cs;
queue<TExchBuf*> videoout_exchlst;

CRITICAL_SECTION filetrans_exchlst_cs;
queue<TExchBuf*> filetrans_exchlst;

void __fastcall istyle_1();
void __fastcall update_contacts_time_stmp(const string&);
void __fastcall exs_write_reg_pid_value();
void __fastcall get_client_root(string&);
void __fastcall get_client_directories(const string&);
void __fastcall get_media_devices_from_registry();
void __fastcall INIT_CTRL_SET();
void __fastcall logThreadsState();
void __fastcall contactDirToSip();
//bool __fastcall get_cursor_position();
void __fastcall Proc_CALL_IN_Msg_READLIST(TMessage&);
void __fastcall Proc_CALL_OUT_Msg_READLIST(TMessage&);
void __fastcall Proc_UAC_Msg_READLIST(TExchBuf*,string&);
void __fastcall Proc_UAS_Msg_READLIST(TExchBuf*);
void __fastcall InitScreenSharing_Viewer(TExchBuf*);
void __fastcall Answer_On_Outgoing_CallPanel(TMediaSession*);
void __fastcall NotAcceptable_On_Outgoing_CallPanel(TMediaSession*);
void __fastcall PlaceCall_OnHold(TMediaSession*);
void __fastcall ResumeCall(TMediaSession*);
void __fastcall ProcInRegister(TExchBuf*);
void __fastcall Busy_On_Outgoing_CallPanel(TMediaSession*);
void __fastcall PROCESS_NOTIFY_PRESENCE(TEventLogThread*,TExchBuf*);
//void __fastcall LoadLogEventsDll();
//void __fastcall LoadAudioDll();
void __fastcall LoadVoiceCaptureDspDll();
bool __fastcall get_MMI_AudioDevices();
void __fastcall LogAudioDeviceParameters();
bool __fastcall check_on_phone_number(const string&);
void __fastcall CC_Panel_Resize();
void __fastcall Panel_DialPad_Resize();
void __fastcall Panel_AddContact_Resize();

void __fastcall TabSheet1_Resize();
void __fastcall TabSheet2_Resize();
void __fastcall DrawGrid1_Resize();
void __fastcall DG_LastCalls_Init();
void __fastcall DG_LastCall_Resize();
void __fastcall Panel_Chat_Resize();
void __fastcall Memo_Chat_Resize();
void __fastcall Image_StartChat_Resize();
void __fastcall Panel_Dial_Init();
void __fastcall Panel_Dial_Resize();
void __fastcall Image_Dig_Resize(int=1);
void __fastcall Image_Dig_Draw();
void __fastcall Image_Dig_Init();
void __fastcall IM_DrawGrid_Init();
void __fastcall CL_DrawGrid_Init();
void __fastcall CL_DrawGrid_Resize();
void __fastcall CC_DrawGrid_Init();

TCurrentBtnState ACBS;  //Audio_CurrentCallBtnState
void __fastcall  InitAudioCallBtn();
void __fastcall  VoiceCallMouseDOWN();
void __fastcall  VoiceCallMouseUP();
void __fastcall  SetVoiceCallBtn_PRESSED();
void __fastcall  SetVoiceCallBtnState(BtnState);

TCurrentBtnState VCBS;  //Video_CurrentCallBtnState
void __fastcall  InitVideoCallBtn();
void __fastcall  InitRemoteVideoBtn();

void __fastcall  VideoCallMouseDOWN();
void __fastcall  VideoCallMouseUP();
void __fastcall  SetVideoCallBtn_PRESSED();
void __fastcall  SetVideoCallBtnState(BtnState);

void __fastcall  SetAudioAndVideoNormalState();

void __fastcall  add_contact_mouse_up();
void __fastcall  dial_number_mouse_up();

void __fastcall color_btns_correction();

void __fastcall DPP_Resize();
TContact* __fastcall read_send_strings__for_client_list_participant(vector<string>&);
void __fastcall read_send_strings__for_non_client_list_participant(vector<string>&);
void __fastcall read_send_strings_to_conference(vector<string>&);
void __fastcall read_send_strings_to_group_chat(vector<string>&, const string&);
void __fastcall send_IM_to_conference_participants();
void __fastcall send_IM_to_chat_participants();
void __fastcall devide_html_string_on_substrings(vector<TImSubStr>&,string&);
void __fastcall end_of_playing_reorder();
void __fastcall end_of_playing_busy();
void         __fastcall append_active_call_to_conference(TCall_Panel*,TUdpChannel*,const TConfCont&,const string&);
void         __fastcall change_call_state_to_conference(TCall_Panel*,int);
bool         __fastcall IsFileTransfer_INVITE(TSipParsBuf*);
void         __fastcall set_client_roots(const string&);
void         __fastcall draw_call_margin_line(TRect&);
void         __fastcall draw_time_margin_line(TRect&);
AnsiString   __fastcall declined_call_from_text();
AnsiString   __fastcall missed_call_from_text();
AnsiString   __fastcall call_to();
AnsiString   __fastcall call_to_answered();
AnsiString   __fastcall call_from_answered();
void         __fastcall call_text_to_cell(const TRect&,const TContact&,TImStr*);

__published:	// IDE-managed Components
        TPanel *Panel1;
        TComboBox *ComboBox1;
        TPanel *Panel2;
        TPageControl *PageControl1;
        TTabSheet *TabSheet1;
        TTabSheet *TabSheet2;
        TDrawGrid *DrawGrid1;
        TButton *Button1;
        TImageList *ImageList1;
        TImageList *ImageList2;
        TImage *Brand_Image;
        TImageList *ImageList3;
        TMainMenu *MainMenu1;
        TMenuItem *Tools1;
        TMenuItem *Client1;
        TMenuItem *Status1;
        TMenuItem *Online1;
        TMenuItem *Away1;
        TMenuItem *Offline1;
        TMenuItem *DoNotDisturb1;
        TPanel *Panel_DialPad;
        TPanel *Panel_AddContact;
        TLabel *Label1;
        TLabel *Label2;
        TPanel *Panel_Chat;
        TImage *Image_StartChat;
        TPanel *Panel_Dial;
        TImage *Image_Dig_1;
        TImage *Image_Dig_2;
        TImage *Image_Dig_3;
        TImageList *ImageList_Dial_Btn_Norm;
        TImageList *ImageList_Dial_Btn_Pressed;
        TImage *Image_Dig_4;
        TImage *Image_Dig_5;
        TImage *Image_Dig_6;
        TImage *Image_Dig_7;
        TImage *Image_Dig_8;
        TImage *Image_Dig_9;
        TImage *Image_Dig_Star;
        TImage *Image_Dig_0;
        TImage *Image_Dig_Pound;
        TButton *Btn_SaveNumber;
        TButton *Btn_Call;
        TMenuItem *VideoCam1;
        TRichEdit *Memo_Chat;
        TPopupMenu *PopupMenu1;
        TMenuItem *OpenSipClient;
        TMenuItem *ExitSipClient;
        TButton *Button4;
        TButton *Button5;
        TMenuItem *Help;
        TMenuItem *Support;
        TMenuItem *About;
        TMenuItem *N1;
        TDrawGrid *IM_DrawGrid;
        TImage *Image7;
        TDrawGrid *CL_DrawGrid;
        TMenuItem *N2;
        TMenuItem *Exit;
        TImage *TrayIcon_Image;
        TMenuItem *N3;
        TPanel *CC_Panel;
        TEdit *CC_Edit;
        TDrawGrid *CC_DrawGrid;
        TOpenDialog *FileTransfer_Dialog;
        TSaveDialog *FileSave_Dialog;
        TMenuItem *N4;
        TMenuItem *N5;
        TMenuItem *N6;
        TMenuItem *TestSound1;
        TMenuItem *StartOptions;
        TMemo *Memo1;
        TImageList *NetStatusImageList;
        TPopupMenu *NetState_PopupMenu;
        TMenuItem *N7;
        TMenuItem *N8;
        TMenuItem *N9;
        TMenuItem *N10;
        TDrawGrid *DG_LastCalls;
        TImage *CC_Img;
        TImage *Image8;
        TImage *MM_Img;
        TPopupMenu *Comment_NetState_PopupMenu;
        TMenuItem *N11;
        TMenuItem *N12;
        TMenuItem *N13;
        TPanel *LEFT_PANEL;
        TPanel *RIGHT_PANEL;
        TSplitter *Splitter1;
        TMenuItem *N14;
        TMenuItem *N15;
        TLabel *Label3;
        TPanel *Panel3;
        TImage *Image9;
        TImage *Image10;
        TPanel *VoiceCallPanel;
        TPanel *VideoCallPanel;
        TImage *Img_VoiceCall;
        TImage *Img_VideoCall;
        TLabel *Lbl_VoiceCall;
        TLabel *Lbl_VideoCall;
        TLabel *CalledNameLbl;
        TButton *Button9;
        TButton *Button10;
        TMenuItem *N16;
        TMenuItem *N17;
        TImageList *VideoCamImgList;
        TImage *AddContact_Img;
        TImage *DialNumber_Img;
        TImage *mic_img_static;
        TImage *speak_img_static;
        TImage *conf_img_static;
        TImage *dial_img_static;
        TImage *Image_VoiceCall;
        TImage *Image_VideoCall;
        TPopupMenu *PopupMenu_IM;
        TMenuItem *IM_COPY;
        TImage *chat_img_static;
        TImage *Image_RemoteVideo;
        TMenuItem *N18;
        TImage *group_img_static;
        TButton *Button2;
        TButton *Button8;
        TButton *Button3;
        TImage *rcv_file_img;
        TImage *rcv_file_img_1;
        TPopupMenu *PopupMenu_IM_FileReceive;
        TMenuItem *N19;
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
        void __fastcall FormKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall FormResize(TObject *Sender);
        void __fastcall Panel1Resize(TObject *Sender);
        void __fastcall Panel2Resize(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall DrawGrid1DrawCell(TObject *Sender, int ACol,
          int ARow, TRect &Rect, TGridDrawState State);
        void __fastcall Panel1MouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
        void __fastcall FormMouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
        void __fastcall DrawGrid1MouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall DrawGrid1MouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall ComboBox1KeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall FormClick(TObject *Sender);
        void __fastcall PageControl1MouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall TabSheet1MouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall DrawGrid1KeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall ComboBox1Click(TObject *Sender);
        void __fastcall PageControl1Resize(TObject *Sender);
        void __fastcall TabSheet1Resize(TObject *Sender);
        void __fastcall Panel_ChatResize(TObject *Sender);
        void __fastcall Panel_DialPadMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall Label2MouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
        void __fastcall Btn_CallMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall Panel_AddContactMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall Label1MouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
        void __fastcall VideoCam1Click(TObject *Sender);
        void __fastcall Memo_ChatKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
       void __fastcall Image_StartChatMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall Button4Click(TObject *Sender);
        void __fastcall Button5Click(TObject *Sender);
        void __fastcall AboutClick(TObject *Sender);
        void __fastcall SupportClick(TObject *Sender);
        void __fastcall IM_DrawGridDrawCell(TObject *Sender, int ACol,
          int ARow, TRect &Rect, TGridDrawState State);
        void __fastcall IM_DrawGridMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall FormDestroy(TObject *Sender);
        void __fastcall ExitClick(TObject *Sender);
        void __fastcall OpenSipClientClick(TObject *Sender);
        void __fastcall ExitSipClientClick(TObject *Sender);
        void __fastcall CL_DrawGridDrawCell(TObject *Sender, int ACol,
          int ARow, TRect &Rect, TGridDrawState State);
        void __fastcall CC_DrawGridDrawCell(TObject *Sender, int ACol,
          int ARow, TRect &Rect, TGridDrawState State);
        void __fastcall CC_DrawGridMouseMove(TObject *Sender,
          TShiftState Shift, int X, int Y);
        void __fastcall CC_DrawGridMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall Offline1Click(TObject *Sender);
        void __fastcall Comment1Click(TObject *Sender);
        void __fastcall CommentClick(TObject *Sender);
        void __fastcall N4Click(TObject *Sender);
        void __fastcall N5Click(TObject *Sender);
        void __fastcall N6Click(TObject *Sender);
        void __fastcall FormMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
        void __fastcall TestSound1Click(TObject *Sender);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall StartOptionsClick(TObject *Sender);
        void __fastcall Memo1KeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall Btn_SaveNumberMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall Online1Click(TObject *Sender);
        void __fastcall Away1Click(TObject *Sender);
        void __fastcall DoNotDisturb1Click(TObject *Sender);
        void __fastcall Panel2MouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
        void __fastcall Brand_ImageMouseMove(TObject *Sender,
          TShiftState Shift, int X, int Y);
        void __fastcall DrawGrid1MouseMove(TObject *Sender,
          TShiftState Shift, int X, int Y);
        void __fastcall DG_LastCallsDrawCell(TObject *Sender, int ACol,
          int ARow, TRect &Rect, TGridDrawState State);
        void __fastcall FormPaint(TObject *Sender);
        void __fastcall CC_EditKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall CC_ImgMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
        void __fastcall CC_ImgMouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
        void __fastcall CC_PanelMouseMove(TObject *Sender,
          TShiftState Shift, int X, int Y);
        void __fastcall Memo1MouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
        void __fastcall CC_ImgMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall MM_ImgMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
        void __fastcall DG_LastCallsMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall DG_LastCallsMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall CC_PanelResize(TObject *Sender);
        void __fastcall LEFT_PANELResize(TObject *Sender);
        void __fastcall RIGHT_PANELResize(TObject *Sender);
        void __fastcall TabSheet2Resize(TObject *Sender);
        void __fastcall N14Click(TObject *Sender);
        void __fastcall Label3MouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
        void __fastcall Image9MouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
        void __fastcall Image10MouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall FormMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
        void __fastcall Memo1MouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
        void __fastcall Panel1MouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
        void __fastcall RIGHT_PANELMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall VoiceCallPanelMouseMove(TObject *Sender,
          TShiftState Shift, int X, int Y);
        void __fastcall VoiceCallPanelMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall Lbl_VoiceCallMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall Img_VoiceCallMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall VoiceCallPanelMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall Lbl_VoiceCallMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall Img_VoiceCallMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall VideoCallPanelMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall RIGHT_PANELMouseMove(TObject *Sender,
          TShiftState Shift, int X, int Y);
        void __fastcall IM_DrawGridMouseMove(TObject *Sender,
          TShiftState Shift, int X, int Y);
        void __fastcall VideoCallPanelMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall VideoCallPanelMouseMove(TObject *Sender,
          TShiftState Shift, int X, int Y);
        void __fastcall Lbl_VideoCallMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall Img_VideoCallMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall Lbl_VideoCallMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall Img_VideoCallMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall Button9Click(TObject *Sender);
        void __fastcall Button10Click(TObject *Sender);
        void __fastcall N16Click(TObject *Sender);
        void __fastcall AddContact_ImgMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall DialNumber_ImgMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall Image_VoiceCallMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall Image_VideoCallMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall Image_VoiceCallMouseMove(TObject *Sender,
          TShiftState Shift, int X, int Y);
        void __fastcall Image_VideoCallMouseMove(TObject *Sender,
          TShiftState Shift, int X, int Y);
        void __fastcall Image_VoiceCallMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall Image_VideoCallMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall IM_COPYClick(TObject *Sender);
        void __fastcall Image_RemoteVideoMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall N18Click(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall Button8Click(TObject *Sender);
        void __fastcall IM_DrawGridKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall AddContact_ImgMouseMove(TObject *Sender,
          TShiftState Shift, int X, int Y);
        void __fastcall DialNumber_ImgMouseMove(TObject *Sender,
          TShiftState Shift, int X, int Y);
        void __fastcall Image_RemoteVideoMouseMove(TObject *Sender,
          TShiftState Shift, int X, int Y);
        void __fastcall Image_StartChatMouseMove(TObject *Sender,
          TShiftState Shift, int X, int Y);
        void __fastcall Button3Click(TObject *Sender);
        void __fastcall N19Click(TObject *Sender);

private:	// User declarations
bool WSAStartUp;
public:
#ifdef TRACE_ALLOC_MEM
#ifdef _DEBUG
TALLOC_INFO_STRUCT AIS;
#endif
#endif
bool DestroyReq;
void __fastcall Image_Dig_MouseUp(TObject *Sender,
                             TMouseButton Button, TShiftState Shift, int X, int Y);
void __fastcall Image_Dig_MouseDown(TObject *Sender,
                             TMouseButton Button, TShiftState Shift, int X, int Y);
void __fastcall On_Restore_Application(TObject* Sender);
void __fastcall On_Minimize_Application(TObject* Sender);
void __fastcall Timer1Timer(TObject *Sender);
OSVERSIONINFO     osv;
TColor            PanelColor;
TSysTimer         sys_timer;
TIniData          iniData;
TStun             Stun;
TIM_Struct        Im;
TInCallBlock      ICB;         //Block for display all incoming calls (TForm1 "SipClient CallReceiving")
TSip*             Sip;
TReconnectSubscribe RS;
TNotifyStruct     NS;
TNetStatus_Panel* NSP;
TDialPad_Panel*   DPP;
TCommentPanel*    NSCP;        //Network State Comment Panel
TProfileForm*     ProfileForm; //Do Not Delete in the destructor

//TEvtLogDll        EvtLogDll;
TOutPutLogBlock   OPB;

TAudioIntDll      AudioIntDll;
TAecDll           AecDll;

TDeleteLegTrnStruct  DLTS;
TDBIExch             ScreenSh;
TScreenSharingViewer SSV;       //Viewer of remote screen sharing
TCtrlExchStruct      CES;
TGroupChatStruct     GCS;       //Для создания групповых чатов


TFileExch            FEXCH;

#ifdef Automatic_Out_Calls
TAutomaticOutCalls   AOC;
#endif
TMediaDevice in_sound_dev;  //mic
TMediaDevice out_sound_dev; //dyn
TOutputLogFileStruct* ofs;
AnsiString baseCaption;
Lang lng;
bool sound_tool;
bool app_minimized;
bool app_on_tray_only;
TCallPanelsStruct cps;
TServConf_Panel* SCP;
vector<complex<double> > hh;   //для прямого преобразования Фурье
vector<complex<double> > hh_1; //для обратного преобразования Фурье
vector<double> sin_wind;       //sin окно
vector<double> hann_wind;      //окно Ханна
vector<double> blackman_wind;  //окно Блэкмена
TDateTime      CallBtnMouseUp_TmStmp;
bool           LAST_FORM_CREATED;
bool           TIME_STMP_REQUEST;
HWND           ParallelPhoneWin;  //Handler of TParallelPhone Window
TParallelPhoneStruct* PPS;         //Structure of parallel phone date
//TClipboard* CLPBRD;
TRichEdit* RichEdit1;

//bool RequestToReinit_AEC;

        __fastcall TMainFormSLS(TComponent* Owner);
void    __fastcall SPLITTER();
int     __fastcall getIntrfStyle(){return intrfStyle;}
void    __fastcall Create_NSP();
void    __fastcall Create_DialPag_Panel();
void    __fastcall INIT_NetState_Popup_Menu();
void    __fastcall INIT_Comment_NetState_Popup_Menu();
void    __fastcall initial_load_user_history();
int     __fastcall Show_Outgoing_CallPanel(const string&,const string&,TSdpMediaCont*,TConfCont*,int);
int     __fastcall Show_Outgoing_CallPanel_OnRefer(const string&,const string&,TConfCont*,int,int);
void    __fastcall createSocketFailed(TEventLogThread*);
void    __fastcall IM_DrawGrid_Resize();
int     __fastcall get_total_call_panels_height();
void    __fastcall Display_Last_Instant_Msg();
void    __fastcall Display_Last_INVITE_ON_FILE_RECEIVE_Msg();
void    __fastcall getBottomCallPanelMargin();
string& __fastcall getSoundDir(){return sound_dir;}
void    __fastcall log_OS_Version();
void    __fastcall log_result_of_dowloading_dll();
void    __fastcall Log_Start_App_Termination_Explicit();
void    __fastcall Log_Start_App_Termination_By_Alt_F4();
void    __fastcall AudioCall();
void    __fastcall AudioCall_PPH(const string&);
void    __fastcall Refer_AudioCall(int);
void    __fastcall StartOutgoingCall_OnConferenceCreate(TConfCont*,int);
void    __fastcall set_user_name_to_send(const string& s){user_name_to_send = s;}
string  __fastcall get_user_name_to_send(){return user_name_to_send;}
void    __fastcall CallPanels_Resize();
void    __fastcall open_NSCP();
void    __fastcall close_NSCP();
void    __fastcall Proc__CLOSE_COMMENT_PANEL_MSG();
void    __fastcall Proc__DBI_DATA();
void    __fastcall Proc__DBI_ACK__PERSONAL_CONTACT_LIST(TDBData*);
void    __fastcall Proc__DBI_ACK__PERSONAL_CITY_PHONE_LIST(TDBData*);
void    __fastcall Proc__SCREEN_SHARING_OUT_DATA();
void    __fastcall Proc__SCREEN_SHARING_IN_DATA();
void    __fastcall PROC_CONTROL();
void    __fastcall StartVideo();
#ifdef SIP_Video
void    __fastcall VideoCall();
#endif
void    __fastcall Conference_Collect();
void    __fastcall Close_Conf_Panel();
void    __fastcall set_req_to_close_conf_panel(){req_to_close_conf_panel = true;}
string& __fastcall give_client_root(){return client_root;}
void    __fastcall hide_call_hstry();
void    __fastcall restore_call_hstry();
void    __fastcall draw_margin_line(TCanvas*,int,int,TRBitMap&);
void __fastcall PlaySound_Free();
void __fastcall Show_Panel_Dial(int,int);

void __fastcall IM_INVITE_ON_FILE_RECEIVING__DRAW_CELL(TGridDrawState, TRect&, TRect&, TImStr*, TImSubStr&, queue<TImSubStr>&);
void __fastcall IM_INVITE_ON_FILE_SENDING__DRAW_CELL(TGridDrawState, TRect&, TRect&, TImStr*, TImSubStr&, queue<TImSubStr>&);

void __fastcall Send_GroupChat_INFO_INIT(const string&, deque<TGroupName>&);
void __fastcall Send_GroupChat_INFO_to_Participant(TGroupName&, const string&, deque<TGroupName>&);

void __fastcall AddToConference(TCall_Panel*);
void __fastcall SendConference_INFO_INIT(LegType, TConfCont&);
void __fastcall SendConference_INFO_About_NEW_Participant_to_ALL_participants(LegType, TCall_Panel*, TConfCont&, deque<TConfCont>&);
void __fastcall SendConference_INFO_About_DELETED_Participant_to_ALL_participants(LegType,TConfCont&,deque<TConfCont>&);
void __fastcall SendConference_INFO_About_ALL_Participants_to_NEW_participant(TMediaSession* ms, deque<TConfCont>&);
void __fastcall Exclude_UserName_From_Dest_List(deque<TConfCont>&, const string&);
void __fastcall Add_Participant_To_ConfCreator_Window(TConfCont&,SipUAThreadType);
void __fastcall Del_Participant_From_ConfCreator_Window(TConfCont&);
void __fastcall Ans_Participant_To_Conf_Window(const string&);
void __fastcall assign_dig_btn_owner_tag(int);
void __fastcall push_req_to_del_call_panel(int);
void __fastcall Proc_UAC_Msg(TMessage& Message);
void __fastcall Proc_UAS_Msg(TMessage& Message);
void __fastcall Proc_CALL_IN_Msg(TMessage& Message);
void __fastcall Proc_CALL_OUT_Msg(TMessage& Message);
#ifdef SIP_Video
void __fastcall Proc_VIDEOOUT_Msg(TMessage& Message);
void __fastcall Proc_VIDEOOUT_Msg_READLIST();
#endif
void __fastcall Proc_FILE_TRANS_INIT_Msg(TMessage& Message);
void __fastcall Proc_FILE_TRANS_START_Msg(TMessage& Message);
void __fastcall Proc_FILETRANS_Msg(TMessage& Message);
void __fastcall Proc_FILE_PENDING_Msg(TMessage& Message);
void __fastcall Proc_FILE_RECV_Msg(TMessage& Message);
void __fastcall Proc_CONF_SERV_Msg(TMessage& Message);
void __fastcall Get_Sip_UA_Msg(TMessage &Message);
void __fastcall Get_CALL_MSG(TMessage &Message);
void __fastcall Get_CONTROL_MSG(TMessage &Message);
#ifdef SIP_Video
void __fastcall Get_VIDEOOUT_MSG(TMessage &Message);
#endif
void __fastcall Get_FILE_TRANSFER_MSG(TMessage &Message);
void __fastcall RestoreAppFromTray();
void __fastcall MyNotify(TMessage&);

void __fastcall MY_WND_PROC(TMessage&);

//void __fastcall MyNotify_1(TMessage&);
void __fastcall MyNotify_2(TMessage&);

void __fastcall PageControl1_Resize();

void    __fastcall group_chat_selected(const string&);
string  __fastcall create_hint(const string&);

TOutPutDtmfBlock* __fastcall exsCreateOutPutDtmfBlock(int&,DtmfTransmitType,unsigned short,int,int,int);
void __fastcall DrawMessageMarker();
void __fastcall MM_Img_Resize();
void __fastcall HIDE_DPW(int);
void __fastcall REFRESH_IM_DRAW_GRID();
const string&    __fastcall get_clients_dir(){return clients_dir;}
const string&    __fastcall get_client_dir(){return client_dir;}
void      __fastcall callin_exchlst_insert(TExchBuf*);
TExchBuf* __fastcall get_call_ExchLst(TMessage&);
void      __fastcall clear_call_ExchLst();
void      __fastcall videoout_exchlst_insert(TExchBuf*);
TExchBuf* __fastcall get_videoout_ExchLst();
void      __fastcall clear_videoout_ExchLst();
void      __fastcall filetrans_exchlst_insert(TExchBuf*);
TExchBuf* __fastcall get_filetrans_ExchLst();
void      __fastcall clear_filetrans_ExchLst();
void      __fastcall open_web_site(const string&);
//void __fastcall devide_plain_string_on_substrings(vector<TImSubStr>&,string&,bool&,bool&);

bool      __fastcall get_IM_to_conf_participants(){return __send_IM_to_conf_participants;}
void      __fastcall set_IM_to_conf_participants(bool a){__send_IM_to_conf_participants = a;}

bool      __fastcall get_IM_to_chat_participants(){return  __send_IM_to_chat_participants;}
void      __fastcall set_IM_to_chat_participants(bool a){__send_IM_to_chat_participants = a;}

void      __fastcall IM_Send(TContact*,const vector<string>&);

void      __fastcall Rcvd_ExchMsgType_Bye_IN(TExchBuf*);
void      __fastcall Rcvd_ExchMsgType_Bye_OUT(TExchBuf*);
void      __fastcall Rcvd_ExchMsgType_Bye_From_Pph__For_IN_Primary_Call(TExchBuf*);
void      __fastcall Rcvd_ExchMsgType_Bye_From_Pph__For_OUT_Primary_Call(TExchBuf*);
string    __fastcall get_replaces_callid(const string&);
void      __fastcall call_transferred_from(TCall_Panel*,const string&,const string&);
void      __fastcall Rcvd_INVITE_ON_CALL_TRANSFER(int,const string&,const string&);
void      __fastcall Rcvd_200OK_ON_CALL_TRANSFER(int,const string&,const string&);
void      __fastcall ClientRegistered(TExchBuf*);

void      __fastcall ReflectCallingPartyHstry(TExchBuf*);

//bool      __fastcall check_contact_unselect(TContactMenu*,TMouseButton,int,int);
//void      __fastcall prepare_to_show_1(TContactMenu*);
void      __fastcall prepare_to_show(TContactMenu*,int,int,int,int);
bool      __fastcall TrayMessage(DWORD,int=0);
bool      __fastcall TrayMessage_Ext(DWORD,const string&,int=0);
TCall_Panel* __fastcall get_First_Call_Panel();
TCall_Panel* __fastcall get_Call_Panel_By_Row(int);
TCall_Panel* __fastcall get_Call_Panel_By_Tag(int);
TCall_Panel* __fastcall get_Call_Panel_By_Sid(int);
void         __fastcall Make_All_Call_Panels_INVISIBLE();
void         __fastcall Make_All_Call_Panels_VISIBLE();

//queue<TContact>& get_subscr_queue(){return subscr_queue;}
int          __fastcall get_pressed_dig(TImage*);
void         __fastcall draw_dial_btn(int,int);
void         __fastcall OpenFileTransferDialog();
void         __fastcall Open_Profile(bool = true);
void         __fastcall Edit_Profile(bool = true);
void         __fastcall Contact_Delete();
void         __fastcall Play_Sound(playSoundState);
bool         __fastcall get_at_least_one_conv_panel();
void         __fastcall setAddToConfBtnState(BtnState);
void         __fastcall add_dial_contact_to_conf_list(const string&);
void         __fastcall Refresh_AddToConfBtnState();
void         __fastcall Close_All_Open_Window();
string       __fastcall get_lst_calls_sub_dir();
void         __fastcall ActivateVideoCallBtnState(int);
void         __fastcall Proc_OnMouseUp_IM_TEXT_TOP_STRING(TImStr*,int,int);
void         __fastcall Place_AllActiveCalls_OnHold(int);
void         __fastcall ActivateAllPanels_Placed_OnHold();
void         __fastcall Activate_LastCall_TabSheet();
void         __fastcall Activate_Contacts_TabSheet();

//void __fastcall OnIdleHandler(TObject *Sender, bool &Done);

void __fastcall Btn_SaveFileMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y);
void __fastcall Btn_CancelTransmitFile_MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y);
void __fastcall Btn_CancelReceiveFile_MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y);

//bool BLOCK_SEND_RTP;


BEGIN_MESSAGE_MAP
  MESSAGE_HANDLER(SIP_UA_MSG,   TMessage, Get_Sip_UA_Msg)
  MESSAGE_HANDLER(CALL_MSG,     TMessage, Get_CALL_MSG)
  MESSAGE_HANDLER(CONTROL_MSG,  TMessage, Get_CONTROL_MSG)
  #ifdef SIP_Video
  MESSAGE_HANDLER(VIDEOOUT_MSG, TMessage, Get_VIDEOOUT_MSG)
  #endif
  MESSAGE_HANDLER(FILE_TRANSFER_MSG,TMessage,Get_FILE_TRANSFER_MSG)
  MESSAGE_HANDLER(MYWM_NOTIFY,TMessage,MyNotify);
  MESSAGE_HANDLER(WM_NCLBUTTONDOWN,TMessage,MyNotify_2);
END_MESSAGE_MAP(TForm)
};
//---------------------------------------------------------------------------
extern PACKAGE TMainFormSLS *MainFormSLS;
AnsiString   __fastcall get_font_name_Arial();
unsigned     __fastcall get_turquoise_color();
const string __fastcall get_hstry();
const string __fastcall get_lf();
const string __fastcall get_TYPE();
//---------------------------------------------------------------------------
#endif
