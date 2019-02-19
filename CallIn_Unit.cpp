//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "WinRDefs.h"
#include "SipClient_Unit.h"
#include "CallIn_Unit.h"
#include "Unit4.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

#define CALL_IN_ANS_BTN__ACTIVE        0x20E114   //0x20FF14
#define CALL_IN_ANS_BTN__FOCUS         0x20D114
#define CALL_IN_ANS_BTN__PRESSED       0x20C114

#define CALL_IN_ANS_VIDEO_BTN__ACTIVE  0x20E114
#define CALL_IN_ANS_VIDEO_BTN__FOCUS   0x20D114
#define CALL_IN_ANS_VIDEO_BTN__PRESSED 0x20C114

#define CALL_IN_DECLINE_BTN__ACTIVE    0x2933FD
#define CALL_IN_DECLINE_BTN__FOCUS     0x2933ED
#define CALL_IN_DECLINE_BTN__PRESSED   0x2933DD


const ans_en = 0;
const ans_ru = 3;
const dcl_en = 6;
const dcl_ru = 9;
const ans_video_en = 0;//12;
const ans_video_ru = 3;//15;

extern TMainFormSLS *MainFormSLS;
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
lng           = Lang_RU;  //Lang_EN;
MF_Handle     = MainFormSLS->Handle;
ans_bs        = CallBtnState_Active;
ans_video_bs  = CallBtnState_Active;
dcl_bs        = CallBtnState_Active;
BorderStyle   = bsDialog;
Width         = Screen->Width/2;
Height        = Screen->Height/7;
Color         = clSilver;
_order        = 0;
closed_by_btn = false;
ans_audio_img_static->Visible = false;
ans_video_img_static->Visible = false;
decline_img_static->Visible   = false;

Panel1 = new TPanel(this);
Panel1->Parent = this;
Panel1->Top  = 0;
Panel1->Left = 0;
Panel1->Width  = Width-5;
Panel1->Height = Height-25;
Panel1->BevelInner = bvLowered;
Panel1->BevelOuter = bvRaised;
Panel1->Color      = (TColor)0x00EEEEEE; //clSilver;

Image1 = new TImage(Panel1);
Image1->Parent = Panel1;
Image1->Height = 32;
Image1->Width  = 85;
Image1->Top  = Height - 2*Image1->Height - 15;
Image1->Left = Width/4;

Image2 = new TImage(Panel1);
Image2->Parent = Panel1;
Image2->Height = Image1->Height;
Image2->Width  = Image1->Width;
Image2->Top = Image1->Top;
Image2->Left = Width/2;

Image3 = new TImage(Panel1);
Image3->Parent = Panel1;
Image3->Height = Image1->Height;
Image3->Width  = 150; //Image1->Width;
Image3->Top  = Image1->Top;
Image3->Left = Image1->Left - Image1->Width - 10;

Label1 = new TLabel(Panel1);
Label1->Parent = Panel1;
Label1->Height = 24;
Label1->Left  = Image1->Left;
Label1->Top   = Image1->Top/4 - 5;
Label1->Font->Color  = (TColor)0xFF0000;
Label1->Font->Size   = 12; //15;

if(lng == Lang_RU)
  {
  ans_base       = ans_ru;
  ans_video_base = ans_video_ru;
  dcl_base       = dcl_ru;
  }
else
  {
  ans_base       = ans_en;
  ans_video_base = ans_video_en;
  dcl_base       = dcl_en;
  }

__btn_backgr_color  = Panel1->Color;
ans_bs_left         = Image1->Width/2 - ans_audio_img_static->Width/2;
decl_bs_left        = Image2->Width/2 - decline_img_static->Width/2;
ans_video_bs_left   = Image3->Width/2 - ans_video_img_static->Width/2;
DRAW_AUDIO_ANS_BTN__ACTIVE(clBlack);
DRAW_VIDEO_ANS_BTN(clBlack, CallBtnState_Active);
DRAW_DECLINE_BTN(clBlack, CallBtnState_Active);

Image3->Visible = false;

Width = Image2->Left + Image2->Width + Image1->Left;
Panel1->OnMouseMove = Panel1MouseMove;

Image1->OnMouseUp   = Image1MouseUp;      //"Answer"
Image1->OnMouseMove = Image1MouseMove;
Image1->OnMouseDown = Image1MouseDown;

Image2->OnMouseUp   = Image2MouseUp;      //"Decline"
Image2->OnMouseMove = Image2MouseMove;
Image2->OnMouseDown = Image2MouseDown;

Image3->OnMouseUp   = Image3MouseUp;      //"AnswerWithVideo"
Image3->OnMouseMove = Image3MouseMove;
Image3->OnMouseDown = Image3MouseDown;

Visible = false;
}
//---------------------------------------------------------------------------
//---------------------- ANSWER on incoming call ----------------------------
//---------------------------------------------------------------------------
void __fastcall TForm1::Image1MouseUp(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
if(X > 0)
  if(Y > 0)
    if(X < Image1->Width)
      if(Y < Image1->Height)
        {
        answer_incoming_call();
        closed_by_btn = true;
        Close();
        return;
        }
DRAW_AUDIO_ANS_BTN__ACTIVE( CALL_IN_ANS_BTN__PRESSED );
ans_bs = CallBtnState_Active;
}
//---------------------------------------------------------------------------
//---------------------- ANSWER on incoming call with video -----------------
//---------------------------------------------------------------------------
void __fastcall TForm1::Image3MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
if(X > 0)
  if(Y > 0)
    if(X < Image3->Width)
      if(Y < Image3->Height)
        {
        answer_incoming_call_with_video();
        closed_by_btn = true;
        Close();
        return;
        }
ans_video_bs = CallBtnState_Active;
DRAW_VIDEO_ANS_BTN( CALL_IN_ANS_VIDEO_BTN__PRESSED, ans_video_bs );
}
//---------------------------------------------------------------------------
//---------------------- DECLINE on incoming call ---------------------------
//---------------------------------------------------------------------------
void __fastcall TForm1::Image2MouseUp(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
if(X > 0)
  if(Y > 0)
    if(X < Image2->Width)
      if(Y < Image2->Height)
        {
        decline_incoming_call();
        closed_by_btn = true;
        Close();
        return;
        }
dcl_bs = CallBtnState_Active;
DRAW_DECLINE_BTN( CALL_IN_DECLINE_BTN__PRESSED, dcl_bs );
}
//---------------------------------------------------------------------------
void __fastcall TForm1::answer_incoming_call()
{
TExchBuf* buf = new TExchBuf(WM_APP_MSG_WPARAM__CALL_IN);
if(buf)
  {
  buf->emt    = ExchMsgType_Answer;
  buf->callid = callid;
  buf->msg    = callingName;
  buf->msg_5  = displayName;  //Используется только в случае, если вызывающего абонента нет в личном списке контактов и в поступившем INVITE в заголовке From: есть поле Diplay Name
  if(connected_to_pph) // pph - parallel phone
    {
    buf->parallel_phone = true;
    buf->msg_1  = callid_pph;  // parallel_phone callid
    buf->b1     = true;        //request to delete parallel call (answer comes from desktop application)
    }
  MainFormSLS->callin_exchlst_insert(buf);
::PostMessage(MF_Handle, CALL_MSG, WM_APP_MSG_WPARAM__CALL_IN, WM_APP_MSG_LPARAM__READLIST);
  }
}
//---------------------------------------------------------------------------
//--- With parallel_phone ---------------------------------------------------
//--- call_id_pph - callid of outgoing call to parallel_phone ---------------
//---------------------------------------------------------------------------
void __fastcall TForm1::answer_incoming_call_with_pph(const string& call_id_pph)
{
TExchBuf* buf = new TExchBuf(WM_APP_MSG_WPARAM__CALL_IN);
if(buf)
  {
  buf->emt    = ExchMsgType_Answer;
  buf->parallel_phone = true;  
  buf->msg_1  = call_id_pph;  // parallel_phone callid
  buf->callid = callid;       // primary callid
  buf->msg    = callingName;
  buf->msg_5  = displayName;  //Используется только в случае, если вызывающего абонента нет в личном списке контактов и в поступившем INVITE в заголовке From: есть поле Diplay Name
  MainFormSLS->callin_exchlst_insert(buf);
::PostMessage(MF_Handle, CALL_MSG, WM_APP_MSG_WPARAM__CALL_IN, WM_APP_MSG_LPARAM__READLIST);
  }
}
//----------------------------------------------------------------------------
void __fastcall TForm1::answer_incoming_call_with_video()
{
TExchBuf* buf = new TExchBuf(WM_APP_MSG_WPARAM__CALL_IN);
if(buf)
  {
  buf->emt    = ExchMsgType_Answer;
  buf->callid = callid;
  buf->msg    = callingName;
  buf->msg_5  = displayName;   //Используется только в случае, если вызывающего абонента нет в личном списке контактов и в поступившем INVITE в заголовке From: есть поле Diplay Name
  #ifdef SIP_Video
  TVcamPar* vcpar = new TVcamPar;
  if(vcpar)
     {
     vcpar->width  = Form4->vcam_width;
     vcpar->height = Form4->vcam_height;
     vcpar->fps    = 15;
     buf->setAddBuf(vcpar);
     }
  #endif
  MainFormSLS->callin_exchlst_insert(buf);
::PostMessage(MF_Handle, CALL_MSG, WM_APP_MSG_WPARAM__CALL_IN, WM_APP_MSG_LPARAM__READLIST);
  }
}
//--------------------------------------------------------------------------
void __fastcall TForm1::decline_incoming_call()
{
TMediaSession* ms = MainFormSLS->Sip->sss->GetMsIn_by_Callid(callid);
if(ms)
  if(!ms->get_ms_hstry_written())
    {
    ms->set_ms_hstry_written(true);
    TExchBuf* buf = new TExchBuf(WM_APP_MSG_WPARAM__CALL_IN);
    if(buf)
      {
      buf->emt    = ExchMsgType_Decline;
      buf->callid = callid;
      buf->msg    = callingName;
      buf->msg_5  = ms->get_display_username();
      MainFormSLS->callin_exchlst_insert(buf);
    ::PostMessage(MF_Handle, CALL_MSG, WM_APP_MSG_WPARAM__CALL_IN, WM_APP_MSG_LPARAM__READLIST);
      }
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Image1MouseMove(TObject *Sender, TShiftState Shift,
      int X, int Y)
{
if(ans_bs == CallBtnState_Active)
  {
   DRAW_AUDIO_ANS_BTN__FOCUS( CALL_IN_ANS_BTN__ACTIVE );
   ans_bs = CallBtnState_Focus;
   Image1->Refresh();
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Image2MouseMove(TObject *Sender, TShiftState Shift,
      int X, int Y)
{
if(dcl_bs == CallBtnState_Active)
  {
  dcl_bs = CallBtnState_Focus;
  DRAW_DECLINE_BTN( CALL_IN_DECLINE_BTN__ACTIVE, dcl_bs);
  Image2->Refresh();
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Image3MouseMove(TObject *Sender, TShiftState Shift,
      int X, int Y)
{
if(ans_video_bs == CallBtnState_Active)
  {
  ans_video_bs = CallBtnState_Focus;
  DRAW_VIDEO_ANS_BTN( CALL_IN_ANS_VIDEO_BTN__ACTIVE, ans_video_bs );
  Image3->Refresh();
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormMouseMove(TObject *Sender, TShiftState Shift,
      int X, int Y)
{
if(ans_bs == CallBtnState_Focus)
  {
  ans_bs = CallBtnState_Active;
  DRAW_AUDIO_ANS_BTN__ACTIVE( CALL_IN_ANS_BTN__FOCUS );
  Image1->Refresh();
  }
if(dcl_bs == CallBtnState_Focus)
  {
  dcl_bs = CallBtnState_Active;
  DRAW_DECLINE_BTN( CALL_IN_DECLINE_BTN__FOCUS, dcl_bs );
  Image2->Refresh();
  }
if(Image3->Visible)
  if(ans_video_bs == CallBtnState_Focus)
    {
    ans_video_bs = CallBtnState_Active;
    DRAW_VIDEO_ANS_BTN( CALL_IN_ANS_VIDEO_BTN__FOCUS, ans_video_bs );
    Image3->Refresh();
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Panel1MouseMove(TObject *Sender, TShiftState Shift,
                                        int X, int Y)
{
if(ans_bs == CallBtnState_Focus)
  {
  ans_bs = CallBtnState_Active;
  DRAW_AUDIO_ANS_BTN__ACTIVE(CALL_IN_ANS_BTN__FOCUS);
  Image1->Refresh();
  }
if(dcl_bs == CallBtnState_Focus)
  {
  dcl_bs = CallBtnState_Active;
  DRAW_DECLINE_BTN( CALL_IN_DECLINE_BTN__FOCUS, dcl_bs );
  Image2->Refresh();
  }
if(Image3->Visible)
  if(ans_video_bs == CallBtnState_Focus)
    {
    ans_video_bs = CallBtnState_Active;
    DRAW_VIDEO_ANS_BTN( CALL_IN_ANS_VIDEO_BTN__FOCUS, ans_video_bs);
    Image3->Refresh();
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Image1MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
if(ans_bs == CallBtnState_Focus)
  {
  DRAW_AUDIO_ANS_BTN__PRESSED(CALL_IN_ANS_BTN__FOCUS);
  ans_bs = CallBtnState_Pressed;
  Image1->Refresh();
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Image2MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
if(dcl_bs == CallBtnState_Focus)
  {
  dcl_bs = CallBtnState_Pressed;
  DRAW_DECLINE_BTN(CALL_IN_DECLINE_BTN__FOCUS, dcl_bs);
  Image2->Refresh();
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Image3MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
if(ans_video_bs == CallBtnState_Focus)
  {
  ans_video_bs = CallBtnState_Pressed;
  DRAW_VIDEO_ANS_BTN( CALL_IN_ANS_VIDEO_BTN__FOCUS, ans_video_bs);
  Image3->Refresh();
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::AudioCall()
{
Image3->Visible = false;
Image1->Left = Width/2 - Image1->Width - 40; //20;
Image2->Left = Width/2; // + 20;
Image1->Top  = Height - 2*Image1->Height - 15;
Image1->Top  = Image2->Top;
Label1->Left = Image1->Left;
Label1->Top  = Image1->Top/4 - 5;

DRAW_AUDIO_ANS_BTN__ACTIVE(clBlack);
DRAW_DECLINE_BTN(clBlack, CallBtnState_Active);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::VideoCall()
{
Image3->Visible = true;
Image3->Left = Width/2 - Image3->Width/2;
Image2->Left = Image3->Left + Image3->Width + Image2->Width/3;
Image1->Left = Image3->Left - Image3->Width/2 - Image1->Width/2;
Image1->Top  = Height - 2*Image1->Height - 15;
Image2->Top  = Image1->Top;
Image3->Top  = Image1->Top;
Label1->Left = Image1->Left;
Label1->Top  = Image1->Top/4 - 5;

DRAW_AUDIO_ANS_BTN__ACTIVE(clBlack);
DRAW_DECLINE_BTN(clBlack, CallBtnState_Active);
DRAW_VIDEO_ANS_BTN(clBlack, CallBtnState_Active);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
if(!closed_by_btn)
   decline_incoming_call();
MainFormSLS->ICB.icl_del(callid);
Action = caFree; //!!!
}
//---------------------------------------------------------------------------
 void __fastcall TForm1::FormShow(TObject *Sender)
{
if(MainFormSLS->lng == Lang_RU)
   Caption = "Входящий вызов";
}
//---------------------------------------------------------------------------
void __fastcall TForm1::DRAW_AUDIO_ANS_BTN__ACTIVE(int CURR_BTN_COLOR)
{
Image1->Canvas->Brush->Color = __btn_backgr_color;
Image1->Canvas->FillRect(Rect(0,0,Image1->Width,Image1->Height));
Image1->Canvas->Pen->Color   = __btn_backgr_color;
Image1->Canvas->Brush->Color = (TColor)CALL_IN_ANS_BTN__ACTIVE;
Image1->Canvas->RoundRect(0, 0, Image1->Width, Image1->Height, 20, 20);
RBitMap::change_color(CURR_BTN_COLOR, CALL_IN_ANS_BTN__ACTIVE, ans_audio_img_static);
Image1->Canvas->Draw(ans_bs_left, 2, ans_audio_img_static->Picture->Bitmap);
}
//------------------------------------------------------------------------------
void __fastcall TForm1::DRAW_AUDIO_ANS_BTN__FOCUS(int CURR_BTN_COLOR)
{
Image1->Canvas->Brush->Color = __btn_backgr_color;
Image1->Canvas->FillRect(Rect(0,0,Image1->Width,Image1->Height));
Image1->Canvas->Pen->Color   =  __btn_backgr_color;
Image1->Canvas->Brush->Color = (TColor)CALL_IN_ANS_BTN__FOCUS;
Image1->Canvas->RoundRect(0, 0, Image1->Width, Image1->Height, 20, 20);
RBitMap::change_color(CURR_BTN_COLOR, CALL_IN_ANS_BTN__FOCUS, ans_audio_img_static);
Image1->Canvas->Draw(ans_bs_left, 2, ans_audio_img_static->Picture->Bitmap);
}
//------------------------------------------------------------------------------
void __fastcall TForm1::DRAW_AUDIO_ANS_BTN__PRESSED(int CURR_BTN_COLOR)
{
Image1->Canvas->Brush->Color = __btn_backgr_color;
Image1->Canvas->FillRect(Rect(0,0,Image1->Width,Image1->Height));
Image1->Canvas->Pen->Color   =  __btn_backgr_color;
Image1->Canvas->Brush->Color = (TColor)CALL_IN_ANS_BTN__PRESSED;
Image1->Canvas->RoundRect(0, 0, Image1->Width, Image1->Height, 20, 20);
RBitMap::change_color(CURR_BTN_COLOR, CALL_IN_ANS_BTN__PRESSED, ans_audio_img_static);
Image1->Canvas->Draw(ans_bs_left, 3, ans_audio_img_static->Picture->Bitmap);
}
//------------------------------------------------------------------------------


void __fastcall TForm1::DRAW_DECLINE_BTN(int CURR_BTN_COLOR, CallBtnState new_btn_state)
{
Image2->Canvas->Brush->Color = __btn_backgr_color;
Image2->Canvas->FillRect(Rect(0,0,Image2->Width,Image2->Height));
Image2->Canvas->Pen->Color   =  __btn_backgr_color;
TColor NEW_BTN_COLOR;
switch(new_btn_state){
      case CallBtnState_Active:  NEW_BTN_COLOR = (TColor)CALL_IN_DECLINE_BTN__ACTIVE;  break;
      case CallBtnState_Focus:   NEW_BTN_COLOR = (TColor)CALL_IN_DECLINE_BTN__FOCUS;   break;
      case CallBtnState_Pressed: NEW_BTN_COLOR = (TColor)CALL_IN_DECLINE_BTN__PRESSED; break;
      default:                   NEW_BTN_COLOR = (TColor)CALL_IN_DECLINE_BTN__ACTIVE;  break;
      }
Image2->Canvas->Brush->Color = (TColor)NEW_BTN_COLOR;
Image2->Canvas->RoundRect(0, 0, Image2->Width, Image2->Height, 20, 20);
RBitMap::change_color(CURR_BTN_COLOR, NEW_BTN_COLOR, decline_img_static);
if(new_btn_state == CallBtnState_Pressed)
  Image2->Canvas->Draw(decl_bs_left, 3, decline_img_static->Picture->Bitmap);
else
  Image2->Canvas->Draw(decl_bs_left, 2, decline_img_static->Picture->Bitmap);
}
//------------------------------------------------------------------------------
void __fastcall TForm1::DRAW_VIDEO_ANS_BTN(int CURR_BTN_COLOR, CallBtnState new_btn_state)
{
Image3->Canvas->Brush->Color = __btn_backgr_color;
Image3->Canvas->FillRect(Rect(0,0,Image3->Width,Image3->Height));
Image3->Canvas->Pen->Color   = __btn_backgr_color;
TColor NEW_BTN_COLOR;
switch(new_btn_state){
      case CallBtnState_Active:  NEW_BTN_COLOR = (TColor)CALL_IN_ANS_VIDEO_BTN__ACTIVE;  break;
      case CallBtnState_Focus:   NEW_BTN_COLOR = (TColor)CALL_IN_ANS_VIDEO_BTN__FOCUS;   break;
      case CallBtnState_Pressed: NEW_BTN_COLOR = (TColor)CALL_IN_ANS_VIDEO_BTN__PRESSED; break;
      default:                   NEW_BTN_COLOR = (TColor)CALL_IN_ANS_VIDEO_BTN__ACTIVE;  break;
      }
Image3->Canvas->Brush->Color = NEW_BTN_COLOR;
Image3->Canvas->RoundRect(0, 0, Image3->Width, Image3->Height, 20, 20);
RBitMap::change_color(CURR_BTN_COLOR, NEW_BTN_COLOR, ans_video_img_static);
if(new_btn_state == CallBtnState_Pressed)
  Image3->Canvas->Draw(ans_video_bs_left, 3, ans_video_img_static->Picture->Bitmap);
else
  Image3->Canvas->Draw(ans_video_bs_left, 2, ans_video_img_static->Picture->Bitmap);
}
//------------------------------------------------------------------------------

