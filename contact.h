#ifndef SipClient_Contact_H
#define SipClient_Contact_H
#include "WinRDefs.h"
#include <Grids.hpp>
//#include <queue.h>

#define SHIFT_STATE_LEFT 10
#define SHIFT_FNAME_LEFT 25
#define SHIFT_STATE_TOP  8

using namespace std;

const SUBSCRIPTIONS_EXPIRES_CONST = 360; //360sec    //3600

class TAbonents;
class TContact;
class TContacts;
class TDBIContacts;
class TExchBuf;
class TNotifyStruct;
class TDBData;
class TOutputSipBuf;
//------------------------------------------------------------------------------
typedef enum{
ClientState_On_Line,
ClientState_Away,
ClientState_Busy,
ClientState_DND,         //Do Not Disturb
ClientState_Off_Line,
ClientState_Terminated,
ClientState_NDef,
}ClientState;
//------------------------------------------------------------------------------
typedef enum{
ContactType_CLIENT,
ContactType_DIVISION,
ContactType_GROUP,
}ContactType;
//------------------------------------------------------------------------------
typedef enum{
LastCallStrType_DateTime,   // Separator with date
LastCallStrType_ContactInt, //Contact From contact list
LastCallStrType_ContactExt, //Contact not included in contact list (for example phone number)
LastCallStrType_NDef,
}LastCallStrType;
//------------------------------------------------------------------------------
typedef enum{
Location_INT,
Location_EXT,
}TContactLocation;
//------------------------------------------------------------------------------
//--- Перед тем как аналмзировать HasSubgroups и HasSubgroups надо проверить Requested
//--- if(Requested) and HasSubgroups == 0 and HasContacts == 0, то список абонентов
//--- подразделения пустой. if(!Requested), то просто еще не было запроса к БД по данному
//--- подразделению.
//------------------------------------------------------------------------------
class TBaseContact{
protected:
int fname_left;
int  __fastcall get_state_left(const TRect& Rect){return Rect.Left + SHIFT_STATE_LEFT;}
int  __fastcall get_fname_left(const TRect& Rect){return Rect.Left + fname_left;}
int  __fastcall get_top(const TRect& Rect){return Rect.Top + Rect.Height()/2 - SHIFT_STATE_TOP;}
void __fastcall draw_contact_state(TContact*,TImageList*,TCanvas*,const TRect&);
void __fastcall draw_group_img(TContact*, TCanvas*, const TRect&);
public:
__fastcall TBaseContact(){
                         fname_left = SHIFT_STATE_LEFT + SHIFT_FNAME_LEFT;
                         }
};
//------------------------------------------------------------------------------
class TDbInterface{
public:
bool RequestedSubgroups;
bool RequestedContacts;
unsigned ID;
unsigned ParentID; //same as OWNER but only for get_Subsc_list from database of enterprise
unsigned HasSubgroups;
unsigned HasContacts;
__fastcall TDbInterface(){
                         RequestedSubgroups = false;
                         RequestedContacts  = false;
                         ID                 = 0;
                         ParentID           = 0;
                         HasSubgroups       = 0;
                         HasContacts        = 0;
                         }
};
//------------------------------------------------------------------------------
class TGroupName{
public:
string  name;
string  s_full_name;
};
//------------------------------------------------------------------------------
class TGroupNameStruct{  //Если вводить CriticalSection, то GRNS может быть только указатель  и ни в коем случае нельзя копировать (только new), т.к. будет копироваться и &CritSect, а это приводит к неопределенным результатам 
deque <TGroupName> GroupNameList;
public:
string   __fastcall gen_group_name(const string&, string& /* out */); //generate group name
void     __fastcall SET_GROUP(deque<TGroupName>&);
void     __fastcall GET_GROUP(deque<TGroupName>&);
void     __fastcall INS_GROUP(TGroupName&);
};
//--------------------------------------------------------------------------------
//-- НЕ использовать указатели м сдожные структуры т.к. используютя копмм TContact
//--------------------------------------------------------------------------------
class TContact{
unsigned _id;
int      _ref_num;
bool     _open;                          //Division contacts visible
bool      my_net_status_visible;         //if true, MY NETWORK STATUS will be visible to this contact
bool      contact_net_status_visible;    //if true, CONTACT NETWORK STATUS will be visible to me
int       missed_calls;
public:
string      name;
string      full_name;
string      group_full_name; // for CT == ContactType_GROUP only (full name will be with prefix "FFFFFFFF")
string      position;        // должность
string      state_note;
unsigned    cos;      //класс обслуживания клиента в центральной БД (не в MFSwitch)
ClientState cs;

unsigned    db_ref;        //reference number for updating from DB ( == seq_num of the contact_list_request). If ref_num is not equal end_of_list dbd->u_2 this client deleted
//string      db_name;
//string      db_second_name;
//string      db_family;
//string      db_local_name; //Имя придуманное пользователем для данного контакта в локальном списке(заменяет full_name, измененное имя должно отобразиться на всех оконечных устройствах данного аккаунта)

int x_pos;
ContactType      CT;                //underlying vectors for ContactType_DIVISION only
TContactLocation CL;
int          CURRENT_OWNER_ID;  //Used in DrawGrid1MousUp() if abonent belongs to different divisions to determin which OWNER is actual on MouseUp action on abonent
TContact*    OWNER;    //DO NOT DELETE IN DESTRUCTOR!!!!!  //Divisions which ownes this Contact (Contact may belong to different divisions (work and friends for example)). Первое появление в списке контактов будет с owner  Work, второе с owner friends and o on
TContact*    pContact; //DO NOT DELETE IN DESTRUCTOR!!!!!  //Used inn dbi_copy() for self address of ContactCopy
vector<int>  underlying_division_ids; //Division ids (for quickly set_open(false) for all undrlying divisions on close topmost)
vector<int>  underlying_ids;          //Contact ids and Division ids
int          subscription_expires;
TGroupNameStruct GRNS;               //Если ContactType == ContactType_GROUP, то здесь хранятся абоненты данной контактной группы
TAbonents*       Abonents;           //Используется только при взаимодействии с внешней БД (TEnterpriseSubscList)
TDbInterface     DBI;                //Хранятся данные, полученные из внешней БД абонентов
    __fastcall TContact(unsigned ID){
                              _id                         = ID;
                              _open                       = false;
                              _ref_num                    = 0;
                               db_ref                     = 0;
                               x_pos                      = 0;
                               CT                         = ContactType_CLIENT;
                               CL                         = Location_INT;
                               CURRENT_OWNER_ID           = 0;
                               OWNER                      = NULL;
                               pContact                   = NULL;
                               my_net_status_visible      = true;
                               contact_net_status_visible = true;
                               cos                        = 0;
                               cs                         = ClientState_Off_Line;
                               missed_calls               = 0;
                               subscription_expires       = SUBSCRIPTIONS_EXPIRES_CONST;
                               Abonents                   = NULL;
                               }
         __fastcall TContact(){
                              _id                         = 0;
                              _open                       = false;
                              _ref_num                    = 0;
                               x_pos                      = 0;
                               CURRENT_OWNER_ID           = 0;
                               CT                         = ContactType_CLIENT;
                               CL                         = Location_INT;
                               OWNER                      = NULL;
                               pContact                   = NULL;
                               my_net_status_visible      = true;
                               contact_net_status_visible = true;
                               cos                        = 0;
                               cs                         = ClientState_Off_Line;
                               missed_calls               = 0;
                               subscription_expires       = SUBSCRIPTIONS_EXPIRES_CONST;
                               Abonents                   = NULL;
                              }
virtual  __fastcall  ~TContact(){
                                if(Abonents)
                                   delete Abonents;
                                }
unsigned __fastcall get_id(){return _id;}
void     __fastcall set_id(int a){_id = a;}
bool     __fastcall get_open(){return _open;}
void     __fastcall set_open(bool a){_open = a;}
void     __fastcall inc_ref_num(){_ref_num++;}
void     __fastcall dec_ref_num(){_ref_num--;}
int      __fastcall get_ref_num(){return _ref_num;}
bool     __fastcall get_my_net_status_visible(){return my_net_status_visible;}
bool     __fastcall get_contact_net_status_visible(){return contact_net_status_visible;}
void     __fastcall inc_missed_calls(){++missed_calls;}
int      __fastcall get_missed_calls(){return missed_calls;}
void     __fastcall set_missed_calls(int a){missed_calls = a;}
void     __fastcall res_missed_calls(){missed_calls = 0;}      //reset missed calls
bool     __fastcall find_underlying_id(vector<int>&,int);
void     __fastcall delete_underlying_id(vector<int>&,int);
void     __fastcall generate_group_name(const string&, string&);

TContact* __fastcall proc_underlying_division_ids_for_cell_display(TContacts*,int&,int,bool);
TContact* __fastcall proc_underlying_abonents_for_cell_display(TContacts*,int&,int);


TContact* __fastcall proc_underlying_division_DBI_ids_for_cell_display(TDBIContacts*,int&,int);
TContact* __fastcall proc_underlying_DBI_abonents_for_cell_display(int&,int);
void      __fastcall copy(TContact& cont){
                                        my_net_status_visible      = cont.my_net_status_visible;
                                        contact_net_status_visible = cont.contact_net_status_visible;
                                        name      = cont.name;
                                        full_name = cont.full_name;
                                        cs        = cont.cs;
                                        subscription_expires = cont.subscription_expires;
                                        }
void     __fastcall dbi_copy(TContact* contact){
                              set_id(contact->get_id());
                              pContact  = contact;
                              name      = contact->name;
                              full_name = contact->full_name;
                              CT        = contact->CT;   //ContactType
                              if(CT == ContactType_DIVISION)
                                 set_open(contact->get_open());
                              DBI       = contact->DBI;
                              OWNER     = contact->OWNER;
                              }
};
//----------------------------------------------------------------------------
typedef map < unsigned, TContact*, less<unsigned>, allocator<unsigned> > TContactList;
typedef map < string, unsigned, less<string>, allocator<string> >        TNameList;
typedef map < unsigned, unsigned >                                       TFullNameList; //fist element - id  complies string DrawGrid1 of contact list, second - contact_id of contact_list
typedef map < string, string,less<string>, allocator<string> >           TCldUserNameToCallID;  //CalledName to CallID
//------------------------------------------------------------------------------
class TReadyOfRefreshSubsc{
public:
bool   check_real_subscr_next;
string name;
TDateTime dt;
__fastcall TReadyOfRefreshSubsc(){
                                 check_real_subscr_next = false;
                                 }
};
//--------------------------------------------------------------------------
//---  TSubscrData - data about appropriate client (endpoint)
//---  If some endpoint on one account (with same login (tel number)) ------
//--------------------------------------------------------------------------
class TSubscribedData{
unsigned   cseq;
TDateTime  subscr_delta;
TDateTime  subscr_next;    //Date when should be received next SUBSCRIBE message from remote contact
TDateTime  subscr_next_tl; // What written in the time list
public:
string     ToIP;
int        ToPort;
string     name;
string     RequestLine;
string     callid;
string     To;
string     From;
unsigned   expires;
string     state_note;
__fastcall TSubscribedData(){
                       ToPort  = 0;
                       cseq    = 2;
                       expires = SUBSCRIPTIONS_EXPIRES_CONST;
                       }
unsigned  __fastcall get_cseq() const {return cseq;}
void      __fastcall inc_cseq(){++cseq;}
void      __fastcall set_cseq(unsigned a){cseq = a;}
TDateTime __fastcall get_subscr_next(){return subscr_next;}
void      __fastcall set_delta_and_next_sabscr_date(unsigned);
void      __fastcall set_real_subscr_next(TDateTime dt){subscr_next_tl = dt;}
};
//--------------------------------------------------------------------------
//--- содержит параметры клиента, который ко мне подписался ----------------
//--------------------------------------------------------------------------
class TSubscribedPar{
typedef map < string, TSubscribedData > TSubscriptionList; //Список подписавшихся ко мне клиентов (по call_id, а не по name, т.к. на одном аккаунте может сидеть несколько клиентов с одним и тем же name)
TSubscriptionList lst;
public:
bool __fastcall find(const string&);
void __fastcall apply_network_parameters(const string&, TOutputSipBuf*);
void __fastcall inc_cseq(const string&);
void __fastcall add_subscribed_data_by_callid(TSubscribedData&);
void __fastcall update_subscribed_data_by_callid(TSubscribedData&, unsigned);
bool __fastcall get_subscribed_data_by_callid(TSubscribedData&, const string&);
void __fastcall get_lst_copy_with_inc_cseq(queue<TSubscribedData>&);
void __fastcall get_lst_copy_with_inc_cseq_and_store_comment(queue<TSubscribedData>&, const string&);
};
//--------------------------------------------------------------------------
class TNotifyData{
public:
string person_id;  //from XML SDP of NOTIFY msg
};
//--------------------------------------------------------------------------
//---  к кому я подписался (от кого получил 202 Responce) ------------------
//---  только name (номер абонента). По тому callid с которым я подписался
//---  мне будут приходить NOTIFY сообщения от данного абонента
//---  Чтобы различить клиентов сидящих на одном номере используется
//---  "dm:person id=" из SDP NOTIFY
//---  Количества абонентов на ОДНОМ НОМЕРЕ к которым я подписался - неизвестно.
//--------------------------------------------------------------------------
class TSubscrPar{
typedef map < string, TNotifyData > TNotifyList;   //from_tag -> TNotifyData
TNotifyList lst;
unsigned  cseq;
TDateTime subscr_delta;
TDateTime subscr_next;
TDateTime subscr_next_tl; // What written in the time list
public:
string     ToIP;
int        ToPort;
unsigned   expires;
string     RequestLine;
string     To;
string     From;
string     callid;
string     name;

__fastcall TSubscrPar(){
                       ToPort  = 0;
                       cseq    = 2;
                       expires = SUBSCRIPTIONS_EXPIRES_CONST;
                       }
unsigned  __fastcall get_cseq() const {return cseq;}
void      __fastcall inc_cseq(){++cseq;}
void      __fastcall set_delta_and_next_sabscr_date(unsigned);
void      __fastcall update_timer(TDateTime&);
void      __fastcall set_cseq(unsigned a){cseq = a;}
TDateTime __fastcall get_subscr_next(){return subscr_next;}
TDateTime __fastcall get_real_subscr_next(){return subscr_next_tl;}
void      __fastcall set_real_subscr_next(TDateTime dt){subscr_next_tl = dt;};

void      __fastcall update_notify_list(TExchBuf*, string&);
int       __fastcall delete_from_notify_list(TExchBuf*, string&);

void      __fastcall check_person_id(const string&, const string&);
};
//---------------------------------------------------------------------------
/*
class TBaseSubscribeStruct{
protected:

typedef map < string, TSubscrPar, less<string>, allocator<string> > TSubscribedList;
CRITICAL_SECTION subscrlist_cs;
TSubscribedList subscribed_list; //subscribed contact name -> TSubscrPar

typedef multimap < TDateTime, string > TTimeList;
CRITICAL_SECTION tl_cs;
TTimeList tl;

public:
__fastcall TBaseSubscribeStruct(){
                                 ::InitializeCriticalSection(&subscrlist_cs);
                                 ::InitializeCriticalSection(&tl_cs);
                                 }
virtual ~TBaseSubscribeStruct(){
                                 ::DeleteCriticalSection(&subscrlist_cs);
                                 ::DeleteCriticalSection(&tl_cs);
                               }

void __fastcall get_full_subscribe_list(queue<TSubscrPar>&);
void __fastcall update_refreshing_time(const string&,TDateTime&);

void __fastcall insert_in_time_list(TDateTime,const string&);


};
*/
//----------------------------------------------------------------------------//
//-- Contains the list of clients who accepted my SUBSCRIBE request ----------//
//----------------------------------------------------------------------------//
class TAcceptedStruct{

CRITICAL_SECTION accepted_list_cs;
typedef map < string, TSubscrPar > TAcceptedList;
TAcceptedList accepted_list; //accepted contact name -> TSubscrPar

CRITICAL_SECTION as_tl_cs;
typedef multimap < TDateTime, string > TTimeList;
TTimeList        as_tl;

public:

__fastcall TAcceptedStruct(){
                          ::InitializeCriticalSection(&accepted_list_cs);
                          ::InitializeCriticalSection(&as_tl_cs);
                          }
virtual ~TAcceptedStruct(){
                         ::DeleteCriticalSection(&accepted_list_cs);
                         ::DeleteCriticalSection(&as_tl_cs);
                         }

void __fastcall add_subscribed_contact(const string&,TExchBuf*,TDateTime&);
void __fastcall get_ready_to_subscribe_list(queue<TReadyOfRefreshSubsc>&);
bool __fastcall refresh_subscribe_proc(const TReadyOfRefreshSubsc&);
bool __fastcall subscribed(const string&);
void __fastcall Final_Subscribe_Proc();

void __fastcall update_person_lst(TExchBuf*, string&);
int  __fastcall delete_from_person_lst(TExchBuf*, string&);

void __fastcall add_subscription_parameters(TExchBuf*);
void __fastcall subscription_declined(const string&);
bool __fastcall get_copy_of_subscrpar(TSubscrPar&,const TReadyOfRefreshSubsc&);
void __fastcall get_full_subscribe_list(queue<TSubscrPar>&);
void __fastcall update_refreshing_time(const string&,TDateTime&);
void __fastcall del_subscribed_contact(const string&);
void __fastcall insert_in_time_list(TDateTime,const string&);
void __fastcall delete_from_time_list(TDateTime,const string&);
void __fastcall clear_time_list();
};
//----------------------------------------------------------------------------//
//-- Contains the list of clients who sent me SUBSCRIBE request --------------//
//----------------------------------------------------------------------------//
class TSubscribedStruct{
bool block_rcv_subscription;
public:
typedef map < string, TSubscribedPar > TSubscribedList;
CRITICAL_SECTION ss_subscrlist_cs;
TSubscribedList  ss_subscribed_list; //subscribed contact name -> TSubscrPar

typedef multimap < TDateTime, TSubscribedData > TTimeList;
CRITICAL_SECTION ss_tl_cs;
TTimeList ss_tl;

public:
__fastcall TSubscribedStruct(){
                            ::InitializeCriticalSection(&ss_subscrlist_cs);
                            ::InitializeCriticalSection(&ss_tl_cs);
                               block_rcv_subscription = false;
                            }
virtual ~TSubscribedStruct(){
                          ::DeleteCriticalSection(&ss_subscrlist_cs);
                          ::DeleteCriticalSection(&ss_tl_cs);
                          }

void __fastcall add_subscribed_contact(const string&,TExchBuf*);
void __fastcall get_temp_subscribed_list(TNotifyStruct*);
void __fastcall get_temp_subscribed_list_for_send_comment(TNotifyStruct*,const string&);
bool __fastcall subscribed_to_me(const string& /*name*/, const string& /*callid*/);
bool __fastcall get_block_rcv_subscription(){return block_rcv_subscription;}
void __fastcall set_block_rcv_subscription(bool a){block_rcv_subscription = a;}

void __fastcall add_subscription_parameters(TExchBuf*);
bool __fastcall get_copy_of_subscribed_data(TSubscribedData&,const string&,const string&,bool);
void __fastcall del_subscribed_contact(const string&);
void __fastcall delete_from_time_list__by_NAME(const string&);
void __fastcall clear_time_list();
};
//------------------------------------------------------------------------------
class TLastCallStr{    //For reflection in TDrawGrid
int missed_calls;
public:
LastCallStrType LCST;
TDateTime  dt;
AnsiString s_time;
string     name;
string     full_name;
__fastcall TLastCallStr(LastCallStrType lcst, TDateTime DT){
                          LCST = lcst;
                          dt = DT;
                          unsigned short h; unsigned short m; unsigned short s; unsigned short ms;
                          dt.DecodeTime(&h, &m, &s, &ms);
                          if(h < 10)
                            s_time = "0" + IntToStr(h) + ":";
                          else
                            s_time = IntToStr(h) + ":";
                          if(m < 10)
                             s_time += "0";
                          s_time += IntToStr(m);
                          missed_calls = 0; //для хелтого знака !!! доделать
                          }
__fastcall TLastCallStr(){
                         LCST = LastCallStrType_NDef;
                         }
void __fastcall inc_missed_calls(){++missed_calls;}
int  __fastcall get_missed_calls(){return missed_calls;}
void __fastcall res_missed_calls(){missed_calls = 0;}
};
//-----------------------------------------------------------------------------
class TLists{
deque<string> missed;  //List of clients from which missed calls or messages (tray icon will be chaged from yellow to blue when missed will be empty)
bool __fastcall find_missed_name(const string& name);
void __fastcall add_missed_name(const string&);
public:
typedef multimap < TDateTime,  TLastCallStr > TLC_DateTime_List;
typedef map      < string, TDateTime >        TLC_Contact_List;     // Last Call Contact name -> TDateTime
TDateTime            today;
TLC_DateTime_List    ldl;     // TDateTime  -> TLastCallStr (ldl - lc_datetime_list)
TLC_Contact_List     lcl;     // Last Call contact name -> TDateTime
void __fastcall arrange_date_times();
void __fastcall update_missed_name(const string&);
void __fastcall delete_missed_name(const string&);
bool __fastcall get_first_missed_name(string&);
bool __fastcall empty(){return missed.empty();}
};
//-----------------------------------------------------------------------------
class TLastCallStruct : public TBaseContact{
CRITICAL_SECTION  lc_contlist_cs;       //for last calls
TLists* Lists;
bool block_repaint;
int  __fastcall get_fname_left(const TRect& Rect){return Rect.Left + fname_left;}
int  __fastcall get_top(const TRect& Rect){return Rect.Top + Rect.Height()/2 - SHIFT_STATE_TOP;}
void __fastcall _proc_display_lc(TImageList*,TCanvas*,int,int,const TRect&,TGridDrawState);
public:
//int row_focused;
__fastcall TLastCallStruct(){
                            ::InitializeCriticalSection(&lc_contlist_cs);
                          //  row_focused   = -1;
                            block_repaint = false;
                            ::EnterCriticalSection(&lc_contlist_cs);
                              Lists = new TLists;
                            ::LeaveCriticalSection(&lc_contlist_cs);
                            }
  virtual ~TLastCallStruct(){
                            ::EnterCriticalSection(&lc_contlist_cs);
                              TLists* ls = Lists;
                              Lists = NULL;
                              delete ls;
                            ::LeaveCriticalSection(&lc_contlist_cs);
                            ::DeleteCriticalSection(&lc_contlist_cs);
                            }
bool __fastcall get_block_repaint(){return block_repaint;}
void __fastcall update_last_call_list(TContact&,TDateTime&,im_text_type,bool,TDrawGrid*);
void __fastcall update_last_call_file(TContact&,TDateTime);
bool __fastcall ldl_empty(){return Lists->ldl.empty();}
void __fastcall Display_LC(TImageList*,TCanvas*,int,int,const TRect&,TGridDrawState);   //Display Last Calls
bool __fastcall get_copy_of_last_call_by_row(TLastCallStr&,int);
void __fastcall ResMissedCalls(const string&);
void __fastcall DeleteMissedName(const string&);
bool __fastcall MissedNameEmpty();
bool __fastcall GetFirstMissedName(string&);
void __fastcall CHANGE_LISTS(TLists*);
};
//-----------------------------------------------------------------------------
class TAccount{
CRITICAL_SECTION acc_cs;
string   user_name;
string   user_pwd;
string   domain;
string   displayname;
string   tuple;        //for NOTIFY
string   person;       //for NOTIFY
public:
unsigned cos;
bool     in_contact_list;
__fastcall TAccount(){
                     ::InitializeCriticalSection(&acc_cs);
                     cos = 0; //!!!
                     in_contact_list = false;
                     randomize();
                     tuple  = "'t" + inttohexstr(random(0x7FFFFFFF)) + "'";
                     person = "'p" + inttohexstr(random(0x7FFFFFFF)) + "'";
                     }
virtual ~TAccount(){
                   ::DeleteCriticalSection(&acc_cs);
                   }

/*const*/ string __fastcall get_user_name();
/*const*/ string __fastcall get_user_pwd();
/*const*/ string __fastcall get_domain();
/*const*/ string __fastcall get_displayname();
          string __fastcall get_tuple();
          string __fastcall get_person();

void __fastcall set_user_name(const string&);
void __fastcall set_user_pwd(const string&);
void __fastcall set_domain(const string& s);
void __fastcall set_displayname(const string&);

void __fastcall displayname_clear();
};
//------------------------------------------------------------------------------
class TContacts : public TBaseContact{
bool      __sorted_by_full_name;
void      __fastcall __sort_by_full_user_name_unsafe();      //Used if CRITICAL_SECTION contlist_cs already Entered
TContact* __fastcall __get_contact_by_row_unsafe(int,bool);  //Used if CRITICAL_SECTION contlist_cs already Entered
TContact* __fastcall __get_contact_by_full_user_name_unsafe(unsigned); //Used if CRITICAL_SECTION contlist_cs already Entered
protected:
int* pContact_list_size;
HWND hwnd;
public:
CRITICAL_SECTION contlist_cs;
unsigned      contact_id;
TContactList  contact_list;   //contact_id -> TContact*
TNameList     name_list;      //subscriber's name -> contact_id
TFullNameList full_name_list; //id -> contact_id  -- id соответствует выделенной строке DrawGrid1 (Contact List)
string        time_stmp;     //for sinchronization local contact_list and contact_list in central DB

TAcceptedStruct   AS;  //Contains the list of clients who accepted my SUBSCRIBE request (to whom subscribed I)
TSubscribedStruct SS;  //Contains the list of clients who sent me SUBSCRIBE request (who subscribed to me)
TLastCallStruct   LCS; //Contains the list of Last Call contacts
void      __fastcall _insert_contact_in_contact_list(TContact*,bool);
bool      __fastcall is_account_user_name(const string&,int&,int,TAccount*,TContact*);      //Чтение списка контактов из файла
void      __fastcall select_full_name(const string&,int&,int,TContact*);  //Чтение списка контактов из файла
void      __fastcall check_on_division(TContact*,FILE*);                       //Чтение списка контактов из файла
void      __fastcall add_to_actual_directory(TContact*);
void      __fastcall get_division_clients(const string&,TContact*,FILE*);
void      __fastcall add_contact_name_to_actual_directory(TContact*);
void      __fastcall add_group_contact_name_to_actual_directory(TContact*);
void      __fastcall add_contact_from_external_db_to_personal_contact_list(vector<TContact*>&,TContact*,TDrawGrid*);
string    __fastcall get_division_name_without_angle_brackets(const string&,string&);
void      __fastcall get_all_parent_divisions(vector<TContact*>&, TContact*);
void      __fastcall del_contact(unsigned);
void      __fastcall del_contact_from_actual_contact_list(TContact*);
void      __fastcall del_group_contact_from_actual_contact_list(TContact*);
int       __fastcall get_size();
void      __fastcall clear_contact_list();
unsigned  __fastcall get_next_contact_id();
TContact* __fastcall get_contact_by_id(int);
bool      __fastcall get_contact_copy_by_id(TContact&,int);
bool      __fastcall get_contact_copy_by_display_name(TContact&, const string&);
bool      __fastcall get_contact_copy_by_user_name(TContact&, TExchBuf*);
bool      __fastcall get_contact_copy_by_user_name(TContact&, const string&);
void      __fastcall open_all_above_divisions(TContact*);
int       __fastcall get_row_id_by_contact_name(const string&,TContact&);
void      __fastcall push_subscr_queue();
void      __fastcall set_contact_state(const string&,ClientState);
void      __fastcall set_contact_state_comment(const string&, string&, bool, bool, bool);
bool      __fastcall is_contact_exists(const string&);

void      __fastcall update_personal_contact_list(TDBData*);   //update from Personal Contact List
void      __fastcall end_of_personal_contact_list(TDBData*);   //update from Personal Contact List

bool      __fastcall missed_call(const string&);
void      __fastcall reset_missed_calls(const string&);
void      __fastcall commit_contact_list(FILE*);
void      __fastcall CC_Display(TImageList*,TCanvas*,int,TRect&);
void      __fastcall Refresh_Presence_Subscribe();
void      __fastcall save_contact_comment(const string&,const string&);
void      __fastcall clear_contact_comment(const string&);
void      __fastcall set_hwnd(HWND hndl){hwnd = hndl;}
HWND      __fastcall get_hwnd(){return hwnd;}

void      __fastcall set_contact_list_size_pointer(int* a){pContact_list_size = a;}
void      __fastcall inc_contact_list_size(){(*pContact_list_size)++;}
void      __fastcall Update_DrawGrid_RowCount(TDrawGrid*);

TContact* __fastcall get_contact_by_row(int,bool);
TContact* __fastcall get_contact_by_full_name(unsigned);

                 /*-- sorted by name --*/
bool      __fastcall get_sorted_by_full_name(){return __sorted_by_full_name;}
void      __fastcall sort_by_full_user_name();
int       __fastcall get_row_by_contact_id_in_sorted_contact_list(unsigned);
void      __fastcall set_state_for_all_contacts(ClientState);
                /*--------------------*/
virtual void      __fastcall Display(TImageList*,TDrawGrid*,TCanvas*,int,const TRect&, TGridDrawState);      //Display Contacts
virtual void      __fastcall add_contact(TContact*,TDrawGrid*,bool);
//virtual bool      __fastcall get_contact_copy_by_row(TContact&,int);
virtual bool      __fastcall contact_visible(TContact*);
virtual void      __fastcall draw_division(TCanvas*,const TRect&,TContact*);
virtual void      __fastcall set_division_visible(int,TDrawGrid*,bool);
virtual void      __fastcall make_actual_division_directory(string&,vector<TContact*>&);
virtual void      __fastcall add_division_name_to_actual_directory(TContact* Contact);


__fastcall TContacts(){
                      ::InitializeCriticalSection(&contlist_cs);
                        hwnd                 = (void*)-1;
                      __sorted_by_full_name  = false;
                        pContact_list_size   = NULL;
                        contact_id           = 0;
                        randomize(); // required for generate random group_names
                      }
  virtual ~TContacts(){
                        clear_contact_list();
                      ::DeleteCriticalSection(&contlist_cs);
                      }
};
//------------------------------------------------------------------------------
//---- class TAbonents используется только в EnterpriseSubscList (Работа с
//---- внешней БД) как элемент класса TContact*.                 ---------------
//---- В EnterpriseSubscList контакты НЕ УДАЛЯЮТСЯ !!!           ---------------
//---- В основном списке TContacts контакты как добавляются тпк и --------------
//---- и УДАЛЯЮТСЯ !!!. Если бы TAbonents использовались в основном списке -----
//---- TContacts то возникали бы проблемы при удалении абонентов, входящих -----
//---- в разные подразделения.                                             -----
//------------------------------------------------------------------------------
class TAbonents : public TContacts{
public:
void      __fastcall add_abonent_contact(TContact*,TContact*);
TContact* __fastcall get_abonent_by_row(int&,int);
void      __fastcall add_abonents_to_actual_directory();
void      __fastcall make_actual_division_directory(string&, vector<TContact*>&);
void      __fastcall add_abonents_from_external_db_to_personal_contact_list();
};
//------------------------------------------------------------------------------
#endif
