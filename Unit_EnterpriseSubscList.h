//---------------------------------------------------------------------------
#ifndef Unit_EnterpriseSubscListH
#define Unit_EnterpriseSubscListH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <Grids.hpp>
#ifndef _WINSOCK2API_
 #include <winsock2.h>
#endif
#include "WinRDefs.h"
#include "BaseThread.h"
#include "Sip.h"
#include <ComCtrls.hpp>
#include <Grids.hpp>
#include <Graphics.hpp>
#include "RBitMap.h"

#define DBI_SHIFT               100000000
#define SERV_DB_MAX_PACKET      8192
#define DATABASE_NET_PREF       0xFE
#define LEFT_IMAGE_MARGIN       0x08
#define HORIZONTAL_BTN_INTERVAL 0x05

const CALLBTN_COLOR_INACTIVE = 0xFFFFFF; //White
const CALLBTN_COLOR_ACTIVE   = 0xFFFFFF; //White
const CALLBTN_COLOR_FOCUSED  = 0xF0F0F0; //Gray

using namespace std;

class TEnterpriseSubscList;
class TNestedParameter;
//---------------------------------------------------------------------------
typedef enum{
IapDataType_Bool   = 1,  //(1 байт)
IapDataType_Int1   = 2,  //(1 байт)
IapDataType_Int2   = 3,  //(2 байта)
IapDataType_Int4   = 4,  //(4 байта)
IapDataType_Int8   = 5,  //(8 байт)
IapDataType_Double = 6,  //(8 байт)
IapDataType_String = 7,  //(Variable)
IapDataType_Nested = 14,
IapDataType_Other  = 15, //(Variable))
IapDataType_NDef,        //(3 байта)
}IapDataType;
//------------------------------------------------------------------------------
typedef enum{
ExhangeType__req        = 0,
ExhangeType__ack        = 1,
ExhangeType__evt        = 2,
ExhangeType__evtack     = 3,
ExhangeType__nested_par = 4,
ExhangeType__notdef     = 5,
}ExhangeType;
//------------------------------------------------------------------------------
typedef enum{  //!!! Необходимо сверять с ServDbMsgType в Server_Db_Base_Struct.h MFSwitch 
ServDbMsgType_GET_TIMESTAMP                   = 1,
ServDbMsgType_GET_PERSONAL_CONTACT_LIST       = 2,
ServDbMsgType_GET_REDIRECTION_LIST            = 3,
ServDbMsgType_MODIFY_CONTACT_LIST             = 4,
ServDbMsgType_GET_SUBSCRIBER_LIST             = 5,
ServDbMsgType_MODIF_ON_REG                    = 6,
ServDbMsgType_MODIF_ON_REDIR                  = 7,
ServDbMsgType_CLEAR_REDIR                     = 8,
ServDbMsgType_GET_PROFILE_LIST                = 9,
ServDbMsgType_GET_MEDIA_LIST                  = 10,
ServDbMsgType_GET_PERSONAL_CITY_PHONE_LIST    = 11,
ServDbMsgType_MODIFY_PERSONAL_CITY_PHONE_LIST = 12,
ServDbMsgType_GET_DIVISION_LIST               = 14,
ServDbMsgType_GET_DIVISION_CONTACT_LIST       = 15,
ServDbMsgType_REQ_START_SUBSCR_DATA           = 16,
ServDbMsgType_FIND                            = 23,
ServDbMsgType_NOTDEF,
}ServDbMsgType;
//------------------------------------------------------------------------------
typedef enum{
DbReqTypeBlockType_Out,
DbReqTypeBlockType_In,
DbReqTypeBlockType_Pars,
}DbReqTypeBlockType;
//------------------------------------------------------------------------------
class TDBData{
public:
bool actual;
ServDbMsgType SDMT;
unsigned u_0;
unsigned u_1;
unsigned u_2;
unsigned u_3;
string   s_1;
string   s_2;
string   s_3;
string   s_4;
string   s_5;
string   s_6;
string   s_7;
bool     next_rows_requested;
__fastcall TDBData(){
                    actual =  false;
                    SDMT   =  ServDbMsgType_NOTDEF;
                    u_0    =  0;
                    u_1    = -1;  //!!!
                    u_2    =  0;
                    u_3    =  0;
                    next_rows_requested = false;
                    }
};
//------------------------------------------------------------------------------
class TTempContList{
queue<TContact*> __q;
bool             __enable_delete_queue;
unsigned         __end_of_list;
void __fastcall  __clear();
public:
void      __fastcall ins_contact(TContact* Contact){__q.push(Contact);}
bool      __fastcall empty(){return __q.empty();}
void      __fastcall disable_delete_queue(){__enable_delete_queue = false;}
void      __fastcall set_end_of_list(unsigned a){__end_of_list = a;}
unsigned  __fastcall get_end_of_list(){return __end_of_list;}
TContact* __fastcall get_contact(){
                                   TContact* rv = NULL;
                                   if(!__q.empty())
                                     {
                                     rv = __q.front();
                                   __q.pop();
                                     }
                                  return rv;
                                  }
       __fastcall TTempContList(){
                          __enable_delete_queue = true;
                          __end_of_list         = 0;
                          }
virtual __fastcall ~TTempContList(){
                                   if(__enable_delete_queue)
                                      __clear();
                                   }
};
//------------------------------------------------------------------------------
class TServDBPar{
unsigned __fastcall _par_len(const vector<UBYTE>&,unsigned&);
public:
unsigned          prm_type;
IapDataType       idt;
unsigned          u;
__int64           i64;
string            s;
vector<UBYTE>     vu;
queue<TServDBPar> q_nested;
bool     __fastcall get_par(const vector<UBYTE>&,unsigned&,unsigned);
         __fastcall TServDBPar(){
                       prm_type = 0;
                       idt      = IapDataType_NDef;
                       u        = 0;
                       i64      = 0L;
                       }
};
//------------------------------------------------------------------------------
class TServDBMsg{
public:
unsigned      seq_number;
unsigned      seq_number_1; //Seq_number of get_personal_contact_list in case of request get_personal_city_phone_list
int           status;
queue<TServDBPar> q;
     __fastcall TServDBMsg(){
                       seq_number   = 0;
                       seq_number_1 = 0;
                       status       = 0x10;
                       }
void __fastcall get_parameters(const vector<UBYTE>&);
void __fastcall get_parameter(const vector<UBYTE>&,unsigned&,unsigned);
};
//------------------------------------------------------------------------------
class TBaseDataBlock{
DbReqTypeBlockType dbt;
protected:
ExhangeType et;
unsigned prms;
unsigned    seq_number;
unsigned    msg_type;
unsigned    status;
public:
vector<UBYTE> v;
DbReqTypeBlockType __fastcall get_dbt(){return dbt;}
ExhangeType        __fastcall get_exchange_type(){return et;}
unsigned           __fastcall get_prms(){return prms;}
unsigned           __fastcall get_seq_number(){return seq_number;}
unsigned           __fastcall get_msg_type(){return msg_type;}
void               __fastcall set_msg_type(unsigned a){msg_type = a;}
void               __fastcall set_exch_type(ExhangeType a){et = a;}
                   __fastcall TBaseDataBlock(DbReqTypeBlockType DBT,ExhangeType ET);
virtual __fastcall  ~TBaseDataBlock(){}
};
//------------------------------------------------------------------------------
class TPackBlock : public TBaseDataBlock{
public:
void __fastcall pack_fixed_type(int,IapDataType,unsigned);
void __fastcall pack_string_type(int,const string&);
void __fastcall pack_other_type(int,const vector<UBYTE>&);
     __fastcall TPackBlock(ExhangeType ET, unsigned MT, unsigned SEQ_NUMBER):TBaseDataBlock(DbReqTypeBlockType_Out,ET){
                                            msg_type     = MT;
                                            seq_number   = SEQ_NUMBER;
                                            }

};
//------------------------------------------------------------------------------
class TUnPackBlock : public TBaseDataBlock{
public:
int bread;
     __fastcall TUnPackBlock(int sz):TBaseDataBlock(DbReqTypeBlockType_In,ExhangeType__notdef){
                                     bread = 0;
                                     v.resize(sz);
                                     }
};
//-----------------------------------------------------------------------------
class TSimpleParameter{
int         par_type;
IapDataType idt;
unsigned a;
string s;
vector<UBYTE> v;
TNestedParameter* n_par;
public:
int               __fastcall get_par_type(){return par_type;}
IapDataType       __fastcall get_data_type(){return idt;}
unsigned          __fastcall get_fixed_value(){return a;}
string&           __fastcall get_string_value(){return s;}
vector<UBYTE>&    __fastcall get_other_value(){return v;}
TNestedParameter* __fastcall get_nested_value(){return n_par;}
void              __fastcall get_simple_value(TSimpleParameter&);
                  __fastcall TSimpleParameter(int PAR_TYPE,IapDataType IDT,unsigned value){
                                            par_type     = PAR_TYPE;
                                            idt          = IDT;
                                            a            = value;
                                            n_par        = NULL;
                                            }
                  __fastcall TSimpleParameter(int PAR_TYPE,const string& value){
                                            par_type     = PAR_TYPE;
                                            idt          = IapDataType_String;
                                            s            = value;
                                            a            = 0;
                                            n_par        = NULL;
                                            }
                  __fastcall TSimpleParameter(int PAR_TYPE,const vector<UBYTE>& value){
                                            par_type     = PAR_TYPE;
                                            idt          = IapDataType_Other;
                                            v            = value;
                                            a            = 0;
                                            n_par        = NULL;
                                            }
                  __fastcall TSimpleParameter(int PAR_TYPE,TNestedParameter* value){
                                            par_type     = PAR_TYPE;
                                            idt          = IapDataType_Nested;
                                            a            = 0;
                                            n_par        = value;
                                            }
                  __fastcall TSimpleParameter(){
                                            par_type = 0;
                                            idt      = IapDataType_NDef;
                                            a        = 0;
                                            n_par    = NULL;
                                            }

                  __fastcall ~TSimpleParameter(){
                                          if(n_par)
                                            delete n_par;
                                          }
};
//------------------------------------------------------------------------------
class TNestedParameter : public TPackBlock{
queue<TSimpleParameter*> q;
void __fastcall pack_parameter_name(int);
void __fastcall pack_nested_data_type();
void __fastcall pack_prms();
void __fastcall pack_simple_parameter(TSimpleParameter*);
public:
void __fastcall push(TSimpleParameter*);
void __fastcall pack_header(int);
void __fastcall pack(int);
TSimpleParameter* __fastcall get_q_parameter();
__fastcall TNestedParameter():TPackBlock(ExhangeType__nested_par,ServDbMsgType_NOTDEF,0){
                                v.resize(4,0);
                                }
virtual __fastcall ~TNestedParameter();
};
//------------------------------------------------------------------------------
class TOutBlock : public TPackBlock{
void __fastcall pack_pref();
void __fastcall pack_length();
void __fastcall pack_seq();
void __fastcall pack_msg_type();
void __fastcall pack_et();
void __fastcall pack_prms_req();
void __fastcall pack_prms_ack();
void __fastcall pack_status();
public:
void      __fastcall set_seq_number(unsigned& a){seq_number = ++a;}
void      __fastcall set_status(unsigned a){status = a;}
unsigned& __fastcall get_prms(){return prms;}
void      __fastcall pack_nested_parameter(int,TNestedParameter&);
void      __fastcall pack_header_REQ();
void      __fastcall pack_header_ACK();
          __fastcall TOutBlock(ExhangeType ET, unsigned SDRT, unsigned SEQ_NUMBER):TPackBlock(ET, SDRT, SEQ_NUMBER){
                                               }
};
//------------------------------------------------------------------------------
class TInBlock : public TUnPackBlock{
public:
TDateTime dt;
__fastcall TInBlock(int sz):TUnPackBlock(sz){}
};
//--------------------------------------------------------------------------
class TSubcrDBRecvTcpThread : public TBaseThread{
SOCKET    sck;
bool      connected;
unsigned  conn_count;
bool     _open_window;
bool     _req_subsc_start_data;
bool     _req_contact_list_time_stmp;
bool    __close_req;
TDateTime NextConnectTime;
TEnterpriseSubscList* Esl;
public:
string host;
int    port;
__fastcall TSubcrDBRecvTcpThread(bool CS, const string& HOST, int PORT, TEventLogThread** ELTP, TSip* SIP, TEnterpriseSubscList* ESL):
                                 TBaseThread(CS,ELTP,SIP){
                                                     sck            = INVALID_SOCKET;
                                                     connected      = false;
                                                     conn_count     = 0;
                                                    _open_window                = false;
                                                    _req_subsc_start_data       = false;
                                                    _req_contact_list_time_stmp = false;
                                                   __close_req      = false;
                                                     host           = HOST; //Connect To
                                                     port           = PORT;
                                                     Esl            = ESL;
                                                     }
void   __fastcall LOG_Connection();
SOCKET __fastcall get_sck(){return sck;}
void   __fastcall set_sck(int a){sck = a;}
void   __fastcall set_open_window(bool a){_open_window = a;}
void   __fastcall set_req_subsc_start_data(bool a){_req_subsc_start_data = a;}
void   __fastcall set_req_contact_list_time_stmp(bool a){_req_contact_list_time_stmp = a;}
bool   __fastcall get_connected(){return connected;}
void   __fastcall set_connected(bool a){connected = a;}
void   __fastcall set_close_req(bool a){__close_req = a;}
void   __fastcall CheckConnError();
void   __fastcall Connect();
void   __fastcall Receive();
void   __fastcall Execute();
};
//---------------------------------------------------------------------------
class TSubcrDBSendTcpThread : public TBaseThread{
public:
     __fastcall TSubcrDBSendTcpThread(bool CS, TEventLogThread** ELTP, TSip* SIP):
                             TBaseThread(CS,ELTP,SIP){}
#ifdef SubscDB_LogSendPacket
void __fastcall LOG_SendPacket(TDateTime&,TOutBlock*);
#endif
void __fastcall send_tcp(const char*,int);
void __fastcall sendbuf(TOutBlock*);
void __fastcall Execute();
};
//-----------------------------------------------------------------------------
class TSubcrDBParsThread : public TBaseThread{
vector<UBYTE> BUF;  //for incomplete msg
TEnterpriseSubscList* esl;
void     __fastcall copy(vector<UBYTE>&, vector<UBYTE>&,int);
bool     __fastcall check_prefix(vector<UBYTE>&);
bool     __fastcall get_single_msg(vector<UBYTE>&,vector<UBYTE>&);
bool     __fastcall get_frame(vector<UBYTE>&,vector<UBYTE>&);
void     __fastcall get_req(vector<UBYTE>&);
void     __fastcall get_ack(const vector<UBYTE>&);
void     __fastcall get_evt(vector<UBYTE>&);
void     __fastcall get_evt_ack(vector<UBYTE>&);
void     __fastcall update_out_seq_list(const TServDBMsg&);
unsigned __fastcall get_length(const vector<UBYTE>&);
unsigned __fastcall get_prm_type(const vector<UBYTE>&,unsigned&);
unsigned __fastcall get_data_type(const vector<UBYTE>&,unsigned&);
void     __fastcall Proc_Ack__GET_TIMESTAMP(TServDBMsg&);
void     __fastcall Proc_Ack__MODIFY_CONTACT_LIST(TServDBMsg&);
void     __fastcall Proc_Ack__GET_DIVISION_LIST(TServDBMsg&);
void     __fastcall Proc_Ack__GET_DIVISION_CONTACT_LIST(TServDBMsg&);
void     __fastcall Proc_Ack__REQ_START_SUBSCR_DATA(TServDBMsg&);
void     __fastcall Proc_Ack__GET_CONTACT_LIST(TServDBMsg&);
void     __fastcall Proc_Ack__GET_CITY_PHONE_LIST(TServDBMsg&);
void     __fastcall Proc_Ack__FIND(TServDBMsg&);

void     __fastcall __get_contact_list(TServDBPar&,unsigned,ServDbMsgType,string&);
void     __fastcall __get_contact_data(TServDBPar&,unsigned,ServDbMsgType,string&);  //Including in parameter ContactList. Nested parameter.
void     __fastcall __get_end_of_list(TTempContList&,TServDBPar&,string&);
void     __fastcall __get_subscr_data(TServDBPar&);

void     __fastcall end_of_client_contact_list(unsigned);
void     __fastcall end_of_client_city_phone_list(unsigned);

public:
     __fastcall TSubcrDBParsThread(bool CS, TEventLogThread** ELTP, TSip* SIP, TEnterpriseSubscList* ESL):
                TBaseThread(CS,ELTP,SIP){
                                        esl = ESL;
                                        }
#ifdef SubscDB_LogRecvPacket
void __fastcall LOG_RecvPacket(TInBlock*);
#endif
#ifdef SubscDB_LogParsedPacket
void __fastcall LOG_ParsPacket(const string&);
#endif
void __fastcall Execute();
};
//-----------------------------------------------------------------------------
class TDBIContacts : public TContacts{
public:
void      __fastcall add_contact(TContact*,TDrawGrid*,bool);
bool      __fastcall get_contact_copy_by_row(TContact&,int);
TContact* __fastcall get_dbi_contact_by_row(int,bool = false);

bool      __fastcall contact_visible(TContact*);
void      __fastcall draw_division(TCanvas*,const TRect&,TContact*);
void      __fastcall set_division_visible(int, TDrawGrid*, bool);
void      __fastcall Display(TImageList*,TDrawGrid*,TCanvas*,int,const TRect&,TGridDrawState);      //Display Contacts
void      __fastcall make_actual_division_directory(string&, vector<TContact*>&);
bool      __fastcall check_actual_directory_existence(const string& directory);
void      __fastcall add_division_name_to_actual_directory(TContact*);
};
//-----------------------------------------------------------------------------
class TTransactionData{
bool     actual;
unsigned seq_num_1;
public:
TDateTime dt;
unsigned  u_1;
unsigned  u_2;
string    s_1;
string    s_2;
string    s_3;
__fastcall TTransactionData(){
                          actual    = false;
                          dt        = dt.CurrentDateTime();
                          seq_num_1 = 0;
                          u_1       = 0;
                          u_2       = 0;
                          }
void __fastcall set_actual(bool a){actual = a;}
bool __fastcall get_actual(){return actual;}

void     __fastcall set_seq_num_1(unsigned a){seq_num_1 = a;}
unsigned __fastcall get_seq_num_1(){return seq_num_1;}
};
//-----------------------------------------------------------------------------
class TSelectedClientItem{
public:
string    selected_name;
string    selected_full_name;
TContact* selected_Contact; //DO NOT DELETE IN DESTRUCTOR!!!
__fastcall TSelectedClientItem(){
                                selected_Contact = NULL;
                                }
void __fastcall set(const TContact& ContCopy){
       selected_name      = ContCopy.name;
       selected_full_name = ContCopy.full_name;
       selected_Contact   = ContCopy.pContact;
       }
void __fastcall clear(){
       selected_Contact = NULL;
       selected_name.clear();
       selected_full_name.clear();
       }
};
//-----------------------------------------------------------------------------
class TDBIExch{
CRITICAL_SECTION dbiexch_cs;
queue<TDBData> q;
public:
__fastcall TDBIExch(){
                     ::InitializeCriticalSection(&dbiexch_cs);
                     }
virtual __fastcall ~TDBIExch(){
                    ::DeleteCriticalSection(&dbiexch_cs);
                    }
void    __fastcall push(const TDBData&);
TDBData __fastcall get();
bool    __fastcall empty();
};
//-----------------------------------------------------------------------------
class TCurrentBtnState{
public:
BtnState  BS;
int       CBS;  //Color of CallBtn
int       img_left;
int       img_top;
int       lbl_left;
int       lbl_top;
int       crc_img_left;//for circular btn shape
int       crc_img_top; //for circular btn shape
TDateTime dt_mouse_up;
__fastcall TCurrentBtnState(){
                             BS       = BtnState_ACTIVE;
                             CBS      = CALLBTN_COLOR_ACTIVE;
                             img_left = 0;     img_top = 0;
                             lbl_left = 0;     lbl_top  = 0;
                             crc_img_left = 0; crc_img_top = 0;
                             }
};
//-----------------------------------------------------------------------------
class TSearchStruct{
unsigned __id;
CRITICAL_SECTION  __fdl_cs;
deque <TDBData>   __new_arrivals;  //элементы, полученные из одного Ack  по ServDbMsgType_FIND
typedef map < unsigned, TDBData > TFoundDataList;
TFoundDataList    __fdl;

string            __last_request;
unsigned          __last_send_seq_number;
bool              __transaction_completed;

void   __fastcall __add_subsc_data(TDBData&);
public:
TCurrentBtnState CSS;
__fastcall TSearchStruct(){
                    ::InitializeCriticalSection(&__fdl_cs);
                    __id = 0;
                    __last_send_seq_number  = 0;
                    __transaction_completed = false;
                    }
virtual __fastcall ~TSearchStruct(){
                    ::DeleteCriticalSection(&__fdl_cs);
                    }

void     __fastcall search_rezult_clear();
void     __fastcall push_new_arrival(TDBData&);
unsigned __fastcall get_new_arrivals_count();
void     __fastcall copy_search_result();
unsigned __fastcall get_list_size();
bool     __fastcall get_db_data_by_row(/* OUT */ TDBData&, int);
void     __fastcall set_next_requested(int);

void     __fastcall last_request_clear(){__last_request.clear();}
void     __fastcall set_last_request(const string& s){__last_request = s;}
string   __fastcall get_last_request(){return __last_request;}

void     __fastcall set_last_send_seq_number(unsigned a){ __last_send_seq_number = a; }
unsigned __fastcall get_last_send_seq_number(){return __last_send_seq_number;}

void     __fastcall set_transaction_complete(bool a){__transaction_completed = a;}
bool     __fastcall transaction_completed(){return __transaction_completed;}

void     __fastcall deactivate_close_btn();
};
//-----------------------------------------------------------------------------
class TEnterpriseSubscList : public TForm
{
typedef map < unsigned, TTransactionData > TOutSeqList;
int min_width;
void __fastcall init_audio_call_btn();
void __fastcall init_video_call_btn();
void __fastcall init_conference_call_btn();
void __fastcall init_add_contact_btn();

void __fastcall add_to_contact_list();

TCurrentBtnState  ACBS;  //Audio_CurrentCallBtnState
TCurrentBtnState  VCBS;  //Video_CurrentCallBtnState
TCurrentBtnState  CCBS;  //Conference_CurrentCallBtnState  -- корпоративный список контактов (EnterpriseSubscriberList)
TCurrentBtnState ADCBS;  //AddContact_CurrentCallBtnState  -- корпоративный список контактов (EnterpriseSubscriberList)

void __fastcall audio_call_mouse_DOWN();
void __fastcall video_call_mouse_DOWN();
void __fastcall conf_call_mouse_DOWN();
void __fastcall add_contact_mouse_DOWN();

void __fastcall audio_call_mouse_UP();
void __fastcall video_call_mouse_UP();
void __fastcall conf_call_mouse_UP();
void __fastcall add_contact_mouse_UP();

void __fastcall set_audio_call_btn_state(BtnState);
void __fastcall set_video_call_btn_state(BtnState);
void __fastcall set_conference_call_btn_state(BtnState);
void __fastcall set_add_contact_btn_state(BtnState);

int  __fastcall __set_Panel1_Top();
int  __fastcall __set_Panel_Find_Height();

__published:	// IDE-managed Components
        TPanel *LEFT_PANEL;
        TDrawGrid *DrawGrid1;
        TPanel *Panel1;
        TPanel *RIGHT_PANEL;
        TPanel *AudioCallPanel2;
        TLabel *Label1;
        TImage *AudioCall_Img;
        TImage *VideoCall_Img;
        TImage *Conference_Img;
        TImage *AddContact_Img;
        TImage *MarginLine;
        TImage *Find_Img;
        TPanel *Panel_Find;
        TDrawGrid *DrawGrid_Find;
        TEdit *Edit_Find;
        TImage *Image_Find_21_21;
        TImage *Image_Close_Find;
        void __fastcall FormShow(TObject *Sender);
        void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
        void __fastcall FormDestroy(TObject *Sender);
        void __fastcall LEFT_PANELResize(TObject *Sender);
        void __fastcall DrawGrid1DrawCell(TObject *Sender, int ACol,
          int ARow, TRect &Rect, TGridDrawState State);
        void __fastcall DrawGrid1MouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall RIGHT_PANELResize(TObject *Sender);
        void __fastcall FormResize(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall DrawGrid1KeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall DrawGrid1MouseMove(TObject *Sender,
          TShiftState Shift, int X, int Y);
        void __fastcall AudioCallPanel2MouseMove(TObject *Sender,
          TShiftState Shift, int X, int Y);
        void __fastcall Panel1MouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
        void __fastcall AudioCallPanel2MouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall AudioCallPanel2MouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall Label_AudioCallMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall Label_AudioCallMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall Img_AudioCallMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall Img_AudioCallMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall VideoCallPanel2MouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall VideoCallPanel2MouseMove(TObject *Sender,
          TShiftState Shift, int X, int Y);
        void __fastcall Label_VideoCallMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall Img_VideoCallMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall AddContactPanel2MouseMove(TObject *Sender,
          TShiftState Shift, int X, int Y);
        void __fastcall AddContactPanel2MouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall Label_AddContactMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall Img_AddContactMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall ConferenceCallPanel2MouseMove(TObject *Sender,
          TShiftState Shift, int X, int Y);
        void __fastcall ConferenceCallPanel2MouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall Label_ConferenceCallMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall Img_ConferenceCallMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall AudioCall_ImgMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall VideoCall_ImgMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall Conference_ImgMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall AddContact_ImgMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall AddContact_ImgMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall AddContact_ImgMouseMove(TObject *Sender,
          TShiftState Shift, int X, int Y);
        void __fastcall Conference_ImgMouseMove(TObject *Sender,
          TShiftState Shift, int X, int Y);
        void __fastcall Conference_ImgMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall VideoCall_ImgMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall VideoCall_ImgMouseMove(TObject *Sender,
          TShiftState Shift, int X, int Y);
        void __fastcall AudioCall_ImgMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall AudioCall_ImgMouseMove(TObject *Sender,
          TShiftState Shift, int X, int Y);
        void __fastcall Panel1Resize(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall Find_ImgMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall Panel_FindResize(TObject *Sender);
        void __fastcall Image_Find_21_21MouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall Edit_FindKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall DrawGrid_FindDrawCell(TObject *Sender, int ACol,
          int ARow, TRect &Rect, TGridDrawState State);
        void __fastcall Edit_FindKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall DrawGrid_FindKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall DrawGrid_FindMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall Image_Close_FindMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall Image_Close_FindMouseMove(TObject *Sender,
          TShiftState Shift, int X, int Y);
        void __fastcall Panel_FindMouseMove(TObject *Sender,
          TShiftState Shift, int X, int Y);
        void __fastcall DrawGrid_FindMouseMove(TObject *Sender,
          TShiftState Shift, int X, int Y);
private:	// User declarations
int      DBI_CONTACT_LIST_SIZE;
unsigned send_seq_number;

//string    selected_client;
//TContact* selected_OWNER; //DO NOT DELETE IN DESTRUCTOR!!!

CRITICAL_SECTION    osl_cs;
TOutSeqList         osl;    //seq_number -> TTransactionData
TSelectedClientItem SCI;    //Fill on DBGrid1MouseUp
void              __fastcall ins_osl(unsigned, const TTransactionData&, queue<unsigned>&);
void              __fastcall clear_osl();
bool              __fastcall empty_osl();
bool              __fastcall exists(unsigned);
TOutBlock*        __fastcall create_start_request_block(const TTransactionData&, ServDbMsgType);
TOutBlock*        __fastcall create_next_request_block(ServDbMsgType, unsigned);
void              __fastcall SEND_REQUEST(TOutBlock*);
public:		// User declarations
CRITICAL_SECTION tcp;
TSubcrDBRecvTcpThread* SDB_RTT;
TSubcrDBSendTcpThread* SDB_STT;
TSubcrDBParsThread*    SDB_PT;
//TSplitter*             Splitter;  Do Not Delete
TDBIContacts           DBIContacts;
TAbonents*             Abonents;  //for clients in root division
TSearchStruct          SearchStruct;
TDBIExch               DBIExch;
        __fastcall  TEnterpriseSubscList(TComponent* Owner);
virtual __fastcall ~TEnterpriseSubscList(){
                                          if(Abonents)
                                             delete Abonents;
                                          ::DeleteCriticalSection(&osl_cs);
                                          ::DeleteCriticalSection(&tcp);
                                          }
void              __fastcall Create_DBChannel(bool,bool,bool);
void              __fastcall Delete_DBChannel();
TTransactionData  __fastcall get_osl(unsigned);
void              __fastcall del_osl(unsigned, queue<unsigned>&);
void              __fastcall UPDATE_TRANSACTION_TIME_STMP(const TServDBMsg&);
void              __fastcall LOG_Window_Actions(const string&);
void              __fastcall log_deleted_seq_numbers(queue<unsigned>&);
int*              __fastcall get_contact_list_size_pointer(){return &DBI_CONTACT_LIST_SIZE;}
unsigned          __fastcall get_contact_list_seq_number(unsigned);
string            __fastcall get_trans_user(unsigned);

void              __fastcall close_find_panel();

void              __fastcall Create_Start_SearchRequest();
void              __fastcall check_end_of_search_transaction(unsigned, unsigned, queue<unsigned>&);

void              __fastcall Make_AudioCall();
void              __fastcall Make_VideoCall();
void              __fastcall Make_ConferenceCall();

void __fastcall GET_SUBSC_START_DATA(const string&);
void __fastcall GET_DIVISION_LIST(const TTransactionData&,unsigned);
void __fastcall GET_DIVISION_CONTACT_LIST(const TTransactionData&,unsigned,unsigned);
void __fastcall REQ_CONTACT_LIST_TIME_STMP(const string&);
void __fastcall GET_PERSONAL_CONTACT_LIST(const string&);
void __fastcall GET_PERSONAL_CITY_PHONE_LIST(const string&,unsigned);
void __fastcall MODIFY_PERSONAL_CONTACT_LIST(const TTransactionData&);
void __fastcall MODIFY_PERSONAL_CITY_PHONE_LIST(const TTransactionData&);

void __fastcall Get_DBI_CONTROL_MSG(TMessage &Message);
BEGIN_MESSAGE_MAP
  MESSAGE_HANDLER(CONTROL_MSG,  TMessage, Get_DBI_CONTROL_MSG)
END_MESSAGE_MAP(TForm)
};
//---------------------------------------------------------------------------
extern PACKAGE TEnterpriseSubscList *EnterpriseSubscList;
//---------------------------------------------------------------------------
#endif
