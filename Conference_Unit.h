//---------------------------------------------------------------------------
#ifndef Conference_UnitH
#define Conference_UnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "WinRDefs.h"
#include "wm_def.h"
#include <ImgList.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <map>
#include <queue>
#include <ImgList.hpp>
#include <ImgList.hpp>
#include <ImgList.hpp>
#include <ImgList.hpp>
#include "UserAgent_defs.h"
#include <ImgList.hpp>
#include <ExtCtrls.hpp>
#include "LegTrn.h"
#include "DialPad_Panel.h"

using namespace std;

class TConferenceWin;
class TConfExchBlock;
class TConfCont;
class TMediaSession;

typedef enum{
WM_CONFERENCE_PLAIN_MSG_WPARAM__VAD,
WM_CONFERENCE_PLAIN_MSG_WPARAM__MAXIMIXE,
WM_CONFERENCE_PLAIN_MSG_WPARAM__SHIFT_BTNS_DOWN,
WM_CONFERENCE_PLAIN_MSG_WPARAM__SHIFT_BTNS_UP,
WM_CONFERENCE_PLAIN_MSG_WPARAM__SHIFT_BTNS_ON_TOP,
WM_CONFERENCE_PLAIN_MSG_WPARAM__NDEF,
}WM_CONFERENCE_PLAIN_MSG_WPARAM;

typedef enum{
WM_CONFERENCE_PLAIN_MSG_LPARAM__NDEF,
}WM_CONFERENCE_PLAIN_MSG_LPARAM;

typedef enum{
WM_CONFERENCE_MSG_WPARAM__NDEF,
}WM_CONFERENCE_MSG_WPARAM;

typedef enum{
WM_CONFERENCE_MSG_LPARAM__NDEF,
}WM_CONFERENCE_MSG_LPARAM;

typedef enum{
BS_CLOSED,
BS_RAISED,
BS_DOWN,
BS_MOUSEMOVED,
BS_NDEF,
}TBTNS_STATE;

typedef enum{
ConfEvnt_Add_Participant,
ConfEvnt_Ans_Participant,
ConfEvnt_Del_Participant,
ConfEvnt_VAD_Enable,
ConfEvnt_VAD_Received,
ConfEvnt_VAD_DISTR_Received, //VAD размноженные конференс креатором
ConfEvnt_Restore,            //Восстановление размера экрана конференции
ConfEvnt_DeactivateWindow,
ConfEvnt_NDef,
}ConfEvnt;
//-------------------------------------------------------------------------------------
class TConfPanel : public TPanel{
public:
string user_name;
TImage* img;
bool    lights;
bool    new_vad_event;
__fastcall TConfPanel(bool default_avatar, TComponent* Owner);
virtual __fastcall ~TConfPanel();
};
//-------------------------------------------------------------------------------------
//-- Used for parsing sdp on receive INFO about conference participants ---------------
//-------------------------------------------------------------------------------------
class TConfExchBlock{
public:
ConfEvnt        conf_evnt;
string          user_name;
string          callid;
bool            conference_creator_exch; // Для обозначения аватара на экране пассивного участника
bool            Buf_Conf_Creator;           // Для обозначения принадлежности самого экрана
int             call_state;
int             ttag;
LegType         lt;
SipUAThreadType uatt;
bool            INFO_msg;
       __fastcall TConfExchBlock(){
                       conf_evnt          = ConfEvnt_NDef;
                       conference_creator_exch = false;
                       Buf_Conf_Creator        = false;
                       call_state         = 0;
                       ttag               = 0;
                       lt                 = Lt_NDef;
                       uatt               = SipUAThreadType_NDef;
                       INFO_msg           = false;
                       }
void        __fastcall pars_sdp_substr(const string&);
string      __fastcall get_info_type(unsigned&,unsigned,const string&);
string      __fastcall get_user_name(unsigned&,unsigned,const string&);
bool        __fastcall get_creator_participant(unsigned&,unsigned,const string&);
int         __fastcall get_call_state(unsigned&,unsigned,const string&);
};
//---------------------------------------------------------------------------
class TConfBtnStateThread : public TThread{
public:
TConferenceWin* win;
TBTNS_STATE     BTNS_STATE;
     __fastcall TConfBtnStateThread(bool CS, TConferenceWin* WIN):TThread(CS){
                               win = WIN;
                               BTNS_STATE = BS_NDEF;
                               }
void __fastcall visible_proc();
void __fastcall Execute();
};
//------------------------------------------------------------------------------
//--- Processing VAD state
//------------------------------------------------------------------------------
class TFlashingStateThread : public TThread{
public:
TConferenceWin* win;
     __fastcall TFlashingStateThread(bool CS, TConferenceWin* WIN):TThread(CS){
                               win = WIN;
                               }
void __fastcall flashing_proc();
void __fastcall Execute();
};
//------------------------------------------------------------------------------
class TConferenceWin : public TForm
{
CRITICAL_SECTION  exch_list_cs;
queue<TConfExchBlock*> exch_list;  //queue for exchange of buffers(BEGIN_MESSAGE_MAP)
TConfExchBlock* __fastcall _get_exch_buf();

CRITICAL_SECTION cp_cs;
typedef map < string, TConfCont* > TConfParticipants;   //user_name of conf participant -> TConfCont*
TConfParticipants CP;                                   //Access only from this window and CONFERENCE_MSG

TConfBtnStateThread*  CONF_BST;
TFlashingStateThread* CONF_FLASH;

TDateTime  dt_activate_screen_sharing;
bool       screen_sharing_active;

bool       mic_switched_on;

bool CONFERENCE_CREATOR;   //Если true то TConferenceWin вызван создателем конференции

bool Default_Size;
int  Default_Top, Default_Left, Default_Width, Default_Height;

CRITICAL_SECTION erase_cs;
queue<TConfCont*> ERASE_Q;

void       __fastcall _layout_1(deque<TConfCont*>&);         //used inside CriticalSection (&cp_cs) only
void       __fastcall _layout_2(deque<TConfCont*>&);         //used inside CriticalSection (&cp_cs) only
int        __fastcall _layout_2_X(deque<TConfCont*>&,int);   //used inside CriticalSection (&cp_cs) only
void       __fastcall _layout_3(deque<TConfCont*>&);         //used inside CriticalSection (&cp_cs) only
void       __fastcall _layout_4(deque<TConfCont*>&);         //used inside CriticalSection (&cp_cs) only
TConfCont* __fastcall _get_conference_creator(deque<TConfCont*>&); //used inside CriticalSection (&cp_cs) only
TConfCont* __fastcall _get_first_participant(deque<TConfCont*>&);  //used inside CriticalSection (&cp_cs) only
int        __fastcall _set_on_top(TConfCont*,int);                 //used inside CriticalSection (&cp_cs) only
void       __fastcall _label_layout(TConfCont*,TConfPanel*);       //used inside CriticalSection (&cp_cs) only
void       __fastcall __get_copy_CP_UNSAFE(deque<TConfCont*>&); // !!! This function MUST BE used inside CriticalSection(&cp_cs) ONLY!!! -------

void       __fastcall __update_last_mouse_move();

void       __fastcall _set_default_size();
void       __fastcall _restore();
void       __fastcall _set_conference_parameters(TMediaSession*,TConfExchBlock*);

bool       __fastcall _flash_disc_img_CP(int);


__published:	// IDE-managed Components
        TImageList *ImageList1;
        TImage *conf_disc_img;
        TImage *conf_add_img;
        TImage *conf_screen_img;
        TImageList *BtnImgs;
        TImage *conf_chat_img;
        void __fastcall FormDestroy(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall conf_disc_imgMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
        void __fastcall conf_screen_imgMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall conf_add_imgMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall FormMouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
        void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
        void __fastcall conf_chat_imgMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall FormCreate(TObject *Sender);
private:	// User declarations
public:		// User declarations

TBtnImage* conf_mic_img;
int  ImgsTop;

TDateTime dt_last_mouse_move;

bool ShowIM;
int  PrevHeight;
int  PrevWidth;
bool block_shift;

                __fastcall TConferenceWin(TComponent* Owner);

void __fastcall conf_mic_img_MouseUp(TObject *Sender,
                                     TMouseButton Button, TShiftState Shift, int X, int Y);
void __fastcall ctr_disc_img_OnMouseUp(TObject *Sender,
                                       TMouseButton Button, TShiftState Shift, int X, int Y);
void __fastcall lbl_OnMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
void __fastcall conf_panel_OnMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);

void            __fastcall ins_exch_buf(TConfExchBlock*);

void            __fastcall proc_conference_msg(TConfExchBlock*);
void            __fastcall add_participant(TConfExchBlock*);
void            __fastcall ans_participant(TConfExchBlock*);
void            __fastcall del_participant(TConfExchBlock*);
void            __fastcall VAD_Enable(TConfExchBlock*);
void            __fastcall VAD_Received(TConfExchBlock*);
void            __fastcall VAD_DISTRIBUTED_Received(TConfExchBlock*);
void            __fastcall flash_participant_panel(TConfExchBlock*);
void            __fastcall DEACTIVATE_CONF_WINDOW();

bool            __fastcall ins_to_CP(TConfCont*);
void            __fastcall ans_to_CP(const string&);
void            __fastcall del_from_CP(const string&);
int             __fastcall get_size_CP();
void            __fastcall activate_VAD_CP(const string&);
void            __fastcall get_copy_CP(deque<TConfCont*>&);
void            __fastcall clear_CP();
void            __fastcall flash_local_disc_img(int);
void            __fastcall check_flashing_local_disc_imgs(bool&, const TDateTime&);
void            __fastcall check_outgoing_no_answered_participants(bool&, const TDateTime&);

void            __fastcall ASSIGN_CALL_TAG(TConfExchBlock*);

void            __fastcall Distribute_RCVD_Vad_Event(const string&);
void            __fastcall Distribute_OWN_Vad_Event();
void            __fastcall Send_Ordinary_VAD_Event_To_Participant(TConfCont*);
void            __fastcall Send_Complex_VAD_Event_To_Participant(TConfCont*,const string&);
void            __fastcall detect_flashing_end();

void            __fastcall Send_IM_To_All_Conf_Participants(const vector<string>&);

void            __fastcall SetConfWinSize();
void            __fastcall ParticipantsLayout();
void            __fastcall ChangeWinLayout_OnResize();

void            __fastcall set_imgs_visible();
void            __fastcall set_imgs_invisible();
void            __fastcall Btn_Layout(TBTNS_STATE);

void            __fastcall create_ctr_disc_img(TConfCont*);
bool            __fastcall check_focus_ctr_disc_img(TBtnImage*);

void            __fastcall create_CONF_BST();
void            __fastcall delete_CONF_BST();

void            __fastcall create_CONF_FLASH();
void            __fastcall delete_CONF_FLASH();

void            __fastcall MIC_SWITCH_ON();
void            __fastcall MIC_SWITCH_OFF();
void            __fastcall Mute_Passive_Conference_Participant();
void            __fastcall Mute_Conference_Creator();
void            __fastcall Mute_OFF_Passive_Conference_Participant();
void            __fastcall Mute_OFF_Conference_Creator();



void            __fastcall Get_CONFERENCE_MSG(TMessage &Message);
void            __fastcall Get_CONFERENCE_PLAIN_MSG(TMessage &Message);

bool            __fastcall Get_CONFERENCE_CREATOR(){return CONFERENCE_CREATOR;}

void            __fastcall INS_TO_ERASE_Q(TConfCont*);
void            __fastcall CHECK_ERASE_Q();

void            __fastcall CLEAR();

BEGIN_MESSAGE_MAP
MESSAGE_HANDLER(CONFERENCE_MSG, TMessage, Get_CONFERENCE_MSG)
MESSAGE_HANDLER(CONFERENCE_PLAIN_MSG, TMessage, Get_CONFERENCE_PLAIN_MSG)
END_MESSAGE_MAP(TForm)
};
//---------------------------------------------------------------------------
extern PACKAGE TConferenceWin *ConferenceWin;
//---------------------------------------------------------------------------
#endif
