//---------------------------------------------------------------------------

#ifndef DialPad_FORMH
#define DialPad_FORMH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include "WinRDefs.h"
#include <ImgList.hpp>
#include "DialPad_Panel.h"
#include <string>

using namespace std;
//--------------------------------------------------
class TDialPad : public TForm
{
__published:	// IDE-managed Components
        TImageList *IL;
        void __fastcall FormShow(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
int DialPad_Height_0;
int DialPad_Height_DTMF;
InitState IS;
std::string last_called_name; // assigned only if dialed number is not exists in contact list
TDigImage* __fastcall create_dig_img(int);
int        __fastcall get_left_dig_margin(int);
int        __fastcall get_top_dig_margin(int);
int        __fastcall get_pressed_dig(TDigImage*);
public:		// User declarations

TPanel*    Panel;
TEdit*     Edit;
TDigImage* dig1;  TDigImage* dig2;  TDigImage* dig3;
TDigImage* dig4;  TDigImage* dig5;  TDigImage* dig6;
TDigImage* dig7;  TDigImage* dig8;  TDigImage* dig9;
TDigImage* dig10; TDigImage* dig11; TDigImage* dig12;
TBtnImage* CallBtn;
TBtnImage* AddBtn;

     __fastcall TDialPad(TComponent* Owner);
void __fastcall CreatePanel();
void __fastcall CreateEdit();
void __fastcall CreateDigImg();

void __fastcall CreateCallBtnImg();
void __fastcall Clear_Digits_State();
void __fastcall Clear_Btn_State();
void __fastcall Clear_Controls_State();
void __fastcall Refresh_CallBtn();

void __fastcall CreateAddBtnImg();
void __fastcall Refresh_AddBtn();

void __fastcall DigImgMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
void __fastcall DialPadMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
void __fastcall DialPadKeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
void __fastcall PanelMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);

void __fastcall Show_DPW(InitState,int);   //Show DialPad Window
void __fastcall Hide_DPW();                //Close DialPad_Window
void __fastcall Assign_DIAL_PressBtnActions();
void __fastcall DigImg_DIAL_MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
void __fastcall DigImg_DIAL_MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
void __fastcall Assign_DTMF_PressBtnActions(int);
void __fastcall DigImg_DTMF_MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
void __fastcall DigImg_DTMF_MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
void __fastcall CallBtn_MouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
void __fastcall CallBtn_MouseDown(TObject *Sender,TMouseButton Button, TShiftState Shift, int X, int Y);
void __fastcall CallBtn_MouseUp(TObject *Sender,TMouseButton Button, TShiftState Shift, int X, int Y);

void __fastcall AddBtn_MouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
void __fastcall AddBtn_MouseDown(TObject *Sender,TMouseButton Button, TShiftState Shift, int X, int Y);
void __fastcall AddBtn_MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
};
//---------------------------------------------------------------------------
extern PACKAGE TDialPad *DialPad;
//---------------------------------------------------------------------------
#endif
