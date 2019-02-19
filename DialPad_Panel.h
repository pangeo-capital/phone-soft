#ifndef DialPad_Panel_UnitH
#define DialPad_Panel_UnitH

#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>

#include "WinRDefs.h"
#include <string>

using namespace std;
//------------------------------------------------------------------------------
typedef enum{
CALL_BTN_INACTIVE_INDX,
CALL_BTN_ACTIVE_INDX,
CALL_BTN_FOCUS_INDX,
CALL_BTN_PRESSED_INDX,
}CALL_BTN_INDX;
//--------------------------------------------------------------------------
typedef enum{
InitState_DTMF,
InitState_DIAL,
InitState_NDef,
}InitState;
//--------------------------------------------------------------------------
class TBtnImage : public TImage{
int    state;  //0 - Inactive, 1 - Active, 2 - Focused, 3 - Pressed, 4 - Switch_Off
public:
int       call_panel_tag;
string    user_name; //for hide ConfParticipant if TCall_Panel already closed(Call disconnected)
TDateTime flash_end; //used for ctr_disc_img
     __fastcall TBtnImage(TComponent* Owner) : TImage(Owner){
                                                            state          = 0;
                                                            call_panel_tag = 0;
                                                            }
void __fastcall clear();
void __fastcall set_btn_state(a){state = a;}
int  __fastcall get_btn_state(){return state;}
};
//---------------------------------------------------------------------------
class TDigImage : public TImage{
TDateTime  dt;
InitState  is;
int        dig;
int        state;  // 0 - normal, 1 - focused, 2 - pressed
AnsiString sdig;
int        sdig_left;
int        sdig_top;
AnsiString sletter;
int        sletter_left;
int        sletter_top;
void __fastcall refresh_background_color();
void __fastcall refresh_dig_inscription();
void __fastcall refresh_sdig();
void __fastcall refresh_sletter();
public:
     __fastcall TDigImage(TComponent* Owner, int DIG);
void __fastcall set_is(InitState a){is = a;}
void __fastcall set_state(st);
int  __fastcall get_dig(){return dig;}
int  __fastcall get_state(){return state;}
AnsiString __fastcall get_sdig(){return sdig;}
void __fastcall set_sdig_coord();
void __fastcall set_sletter_coord();
void __fastcall create_dig_inscription();
void __fastcall create_letter_inscription();
void __fastcall time_stmp();
TDateTime __fastcall get_time_stmp(){return dt;}
void __fastcall refresh_image();
};
//----------------------------------------------------
class TDial : public TPanel{
int input_left_margin;
void __fastcall calc_input_left_margin();
public:
TPanel*    Panel;
TEdit*     Edit;

TDigImage* dig1;  TDigImage* dig2;  TDigImage* dig3;
TDigImage* dig4;  TDigImage* dig5;  TDigImage* dig6;
TDigImage* dig7;  TDigImage* dig8;  TDigImage* dig9;
TDigImage* dig10; TDigImage* dig11; TDigImage* dig12;
TBtnImage* CallBtn;

     __fastcall TDial(TComponent* Owner);
void __fastcall resize();
void __fastcall CreatePanel();
void __fastcall CreateEdit();
void __fastcall Clear_Digits_State();
void __fastcall CreateDigImg();
void __fastcall PanelMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);

};
//------------------------------------------------------------------------------
class TDialPad_Panel : public TPanel{
public:
TDial* Dial;
     __fastcall TDialPad_Panel(TComponent* Owner);
void __fastcall CreateDial();
void __fastcall resize();     
void __fastcall ShowDialPad();
void __fastcall DialPad_Panel_KeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
};
//-----------------------------------------------------------------------------
#endif