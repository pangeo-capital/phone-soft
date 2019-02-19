//---------------------------------------------------------------------------
#ifndef CallIn_UnitH
#define CallIn_UnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <ImgList.hpp>
//----------------------------------------------------------------------------
typedef enum{
CallBtnState_Active,
CallBtnState_Focus,
CallBtnState_Pressed,
CallBtnState_NotActive,
}CallBtnState;
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
HWND MF_Handle;
CallBtnState ans_bs;       //Answer button state
CallBtnState ans_video_bs; //Answer with video button state
CallBtnState dcl_bs;       //Decline button state

int  ans_bs_left;          //left margin of telephone img
int  ans_video_bs_left;    //left margin of video cam img
int  decl_bs_left;         //left margin of decline img

TColor __btn_backgr_color;

int  ans_base;
int  ans_video_base;
int  dcl_base;
unsigned _order;
Lang lng;
void __fastcall answer_incoming_call_with_video();
void __fastcall answer_incoming_call();

__published:	// IDE-managed Components
        TImage *ans_audio_img_static;
        TImage *ans_video_img_static;
        TImage *decline_img_static;
        void __fastcall FormMouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall FormShow(TObject *Sender);
private:	// User declarations
public:		// User declarations
TPanel* Panel1;
TLabel* Label1;
TImage* Image1;
TImage* Image2;
TImage* Image3;
string  callingName;
string  displayName; //Используется только в случае, если вызывающего абонента нет в личном списке контактов и в поступившем INVITE в заголовке From: есть поле Diplay Name
string  callid;
bool    closed_by_btn;
bool    connected_to_pph; // pph - parallel phone
string  callid_pph;       // callid of call to parallel phone

void     __fastcall AudioCall();
void     __fastcall VideoCall();
void     __fastcall answer_incoming_call_with_pph(const string&);
unsigned __fastcall get_order(){return _order;}
void     __fastcall set_order(unsigned a){_order = a;}
void     __fastcall decline_incoming_call();

void     __fastcall DRAW_AUDIO_ANS_BTN__ACTIVE(int  /* CURR_BTN_COLOR */);
void     __fastcall DRAW_AUDIO_ANS_BTN__FOCUS(int   /* CURR_BTN_COLOR */);
void     __fastcall DRAW_AUDIO_ANS_BTN__PRESSED(int /* CURR_BTN_COLOR */);

void     __fastcall DRAW_VIDEO_ANS_BTN(int /* CURR_BTN_COLOR */, CallBtnState /* new_btn_state */);
void     __fastcall DRAW_DECLINE_BTN(int   /* CURR_BTN_COLOR */, CallBtnState /* new_btn_state */);

//void     __fastcall DRAW_DECLINE_BTN__FOCUS(int   /* CURR_BTN_COLOR */);
//void     __fastcall DRAW_DECLINE_BTN__PRESSED(int /* CURR_BTN_COLOR */);

void __fastcall Image1MouseUp(TObject *Sender, TMouseButton Button,
                             TShiftState Shift, int X, int Y);
void __fastcall Image1MouseMove(TObject *Sender, TShiftState Shift,
                               int X, int Y);
void __fastcall Image1MouseDown(TObject *Sender,
                     TMouseButton Button, TShiftState Shift, int X, int Y);
void __fastcall Image2MouseUp(TObject *Sender, TMouseButton Button,
                     TShiftState Shift, int X, int Y);
void __fastcall Image2MouseDown(TObject *Sender,
                     TMouseButton Button, TShiftState Shift, int X, int Y);
void __fastcall Image2MouseMove(TObject *Sender, TShiftState Shift,
                     int X, int Y);
void __fastcall Image3MouseDown(TObject *Sender,
                     TMouseButton Button, TShiftState Shift, int X, int Y);
void __fastcall Image3MouseMove(TObject *Sender, TShiftState Shift,
                     int X, int Y);
void __fastcall Image3MouseUp(TObject *Sender, TMouseButton Button,
                     TShiftState Shift, int X, int Y);
void __fastcall Panel1MouseMove(TObject *Sender, TShiftState Shift,
                     int X, int Y);

        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
