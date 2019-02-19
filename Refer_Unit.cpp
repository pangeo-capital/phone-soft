//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Refer_Unit.h"
#include "RBitMap.h"
#include "SipClient_Unit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TReferWin *ReferWin;
//---------------------------------------------------------------------------
__fastcall TReferWin::TReferWin(TComponent* Owner)
        : TForm(Owner)
{
Width       = 300;
Height      = 150;
Color       = clWhite;
TBorderIcons BI = BorderIcons;
BI = BI << biSystemMenu;
BorderIcons = BI;
BorderStyle = bsDialog;
Visible     = false;  //Must be set in Object Inspector
KeyPreview  = true;   //ForHide wind by Esc key
FormStyle   = fsStayOnTop;

BST = NULL;

EditBox = new TEditBox(this, 10, 15, Width - 30, 20);
EditBox->Edit->ShowHint = true;
EditBox->Edit->Hint     = "Выберите абонента из контакт листа\nили наберите телефоный номер";

Refer_Img->Tag    = 1;  //Переадресация
Refer_Img->Width  = 130;
Refer_Img->Height = 30;
Refer_Img->Left   = Width/2  -  Refer_Img->Width/2;
Refer_Img->Top    = Height   -  3*Refer_Img->Height - 10;

bp_1.bs = BtnState_ACTIVE;
bp_1.S  = "Переадресация";
bp_1.w  = Refer_Img->Width  - 4;
bp_1.h  = Refer_Img->Height - 4;

Refer_Img->Canvas->Font->Color  = clGrayText;
Refer_Img->Canvas->Font->Name   = "Arial";
Refer_Img->Canvas->Font->Size   = 10;
Refer_Img->Canvas->Font->Style  = Refer_Img->Canvas->Font->Style << fsBold;
int tw           = Refer_Img->Canvas->TextWidth(bp_1.S);
int th           = Refer_Img->Canvas->TextHeight(bp_1.S);
bp_1.text_left   = Refer_Img->Width/2  - tw/2 - 1;
bp_1.text_top    = Refer_Img->Height/2 - th/2 - 1;

                          Refer_Img->Visible = false;

Refer_Ans_Img->Tag    = 2;  //Переадресация из разговора
Refer_Ans_Img->Width  = 220;
Refer_Ans_Img->Height = 30;
Refer_Ans_Img->Left   = Width/2  -  Refer_Ans_Img->Width/2;
Refer_Ans_Img->Top    = Height   -  2*Refer_Ans_Img->Height - 20; //10;

bp_2.bs = BtnState_ACTIVE;
bp_2.S  = "Передать вызов"; //"Переадресация из разговора";
bp_2.w  = Refer_Ans_Img->Width  - 4;
bp_2.h  = Refer_Ans_Img->Height - 4;

Refer_Ans_Img->Canvas->Font->Color  = clGrayText;
Refer_Ans_Img->Canvas->Font->Name   = "Arial";
Refer_Ans_Img->Canvas->Font->Size   = 10;
Refer_Ans_Img->Canvas->Font->Style  = Refer_Ans_Img->Canvas->Font->Style << fsBold;
tw           = Refer_Ans_Img->Canvas->TextWidth(bp_2.S);
th           = Refer_Ans_Img->Canvas->TextHeight(bp_2.S);
bp_2.text_left    = Refer_Ans_Img->Width/2  - tw/2 - 1;
bp_2.text_top     = Refer_Ans_Img->Height/2 - th/2 - 1;

refresh_btn_state(Refer_Img, BtnState_ACTIVE);
refresh_btn_state(Refer_Ans_Img, BtnState_ACTIVE);
}
//---------------------------------------------------------------------------
void __fastcall TReferWin::Refer_ImgMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
set_focused((TImage*)Sender);
}
//----------------------------------------------------------------------------
void __fastcall TReferWin::Refer_Ans_ImgMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
set_focused((TImage*)Sender);
}
//---------------------------------------------------------------------------
void __fastcall TReferWin::Refer_ImgMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
refresh_btn_state((TImage*)Sender, BtnState_PRESSED);
}
//---------------------------------------------------------------------------
void __fastcall TReferWin::Refer_Ans_ImgMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
refresh_btn_state((TImage*)Sender, BtnState_PRESSED);
}
//---------------------------------------------------------------------------
void __fastcall TReferWin::Refer_ImgMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
if((X > 0) && (X < Refer_Img->Width))
  if((Y > 0) && (Y < Refer_Img->Height))
    {
     // int a = 5; //action REFER sip:
    }
refresh_btn_state((TImage*)Sender, BtnState_ACTIVE);
Close();
}
//---------------------------------------------------------------------------
void __fastcall TReferWin::Refer_Ans_ImgMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
if((X > 0) && (X < Refer_Ans_Img->Width))
  if((Y > 0) && (Y < Refer_Ans_Img->Height))
    {
    if(refer_name.empty())  //May be refer_name was obtained by key board type
      {
      AnsiString S = EditBox->Edit->Text;
      if(!S.IsEmpty())
        MainFormSLS->set_user_name_to_send(S.c_str());
      }
    else
      MainFormSLS->set_user_name_to_send(refer_name); //refer_name was obtained from contact list
    MainFormSLS->ComboBox1->Text        = EditBox->Edit->Text;
    MainFormSLS->CalledNameLbl->Caption = EditBox->Edit->Text;
    MainFormSLS->Place_AllActiveCalls_OnHold(-1);
    MainFormSLS->Refer_AudioCall(Tag);      //Tag == TCall_Panel->Tag от которой (панели) поступил запрос на переадресацию
    }
refresh_btn_state((TImage*)Sender, BtnState_ACTIVE);
Close();
}
//---------------------------------------------------------------------------
void __fastcall TReferWin::set_focused(TImage* img)
{
bool pressed = false;
switch(img->Tag){
      case 1: if(bp_1.bs == BtnState_PRESSED)
                 pressed = true;
              break;
      case 2: if(bp_2.bs == BtnState_PRESSED)
                 pressed = true;
              break;
      }
if(!pressed)
   refresh_btn_state(img, BtnState_FOCUSED);
}
//--------------------------------------------------------------------------
void __fastcall TReferWin::refresh_btn_state(TImage* img, BtnState bs)
{
clear_btn(img);
set_btn_state(img, bs);
}
//----------------------------------------------------------------------------
void __fastcall TReferWin::set_btn_state(TImage* img, BtnState bs)
{
clear_btn(img);
TBtnParameter* bp;
switch(img->Tag){
      case 1: bp_1.bs = bs; bp = &bp_1; break;  //Переадресация без ожидания ответа
      case 2: bp_2.bs = bs; bp = &bp_2; break;  //Переадресация c ожиданием ответа
      }
draw_btn_state(img, bp);
}
//----------------------------------------------------------------------------
void __fastcall TReferWin::clear_btn(TImage* img)
{
img->Canvas->Brush->Color = clWhite;
//img->Canvas->FillRect(Rect(0,0,Width,Height));
img->Canvas->FillRect(Rect(0,0,img->Width,img->Height));
}
//---------------------------------------------------------------------------
void __fastcall TReferWin::draw_btn_state(TImage* img, TBtnParameter* bp)
{
switch(bp->bs){
      case BtnState_ACTIVE:{
           TRBitMap rbmp(bp->w, bp->h, clWhite, clGray, clWhite);
           img->Canvas->Draw(2,2, rbmp.bmp);
           img->Canvas->Brush->Color = clWhite;
           img->Canvas->TextOut(bp->text_left, bp->text_top, bp->S);
           break;
           }
      case BtnState_FOCUSED:{
           TRBitMap rbmp(bp->w, bp->h, clWhite, clGray, (TColor)0xEEEEEE);
           img->Canvas->Draw(2,2, rbmp.bmp);
           img->Canvas->Brush->Color = (TColor)0xEEEEEE;
           img->Canvas->TextOut(bp->text_left, bp->text_top, bp->S);
           break;
           }
      case BtnState_PRESSED:
           TRBitMap rbmp(bp->w, bp->h, clWhite, clGray, clSilver);
           img->Canvas->Draw(2,2, rbmp.bmp);
           img->Canvas->Brush->Color = clSilver;
           img->Canvas->TextOut(bp->text_left, bp->text_top + 1, bp->S);
           break;
      }
img->Refresh();      
}
//---------------------------------------------------------------------------
void __fastcall TReferWin::FormCloseQuery(TObject *Sender, bool &CanClose)
{
refer_name.clear();
EditBox->Edit->Clear();
if(bp_1.bs != BtnState_ACTIVE)
   refresh_btn_state(Refer_Img, BtnState_ACTIVE);
if(bp_2.bs != BtnState_ACTIVE)
   refresh_btn_state(Refer_Ans_Img, BtnState_ACTIVE);
delete_BST();
}
//---------------------------------------------------------------------------
void __fastcall TReferWin::FormShow(TObject *Sender)
{
delete_BST();
create_BST();
}
//---------------------------------------------------------------------------
void __fastcall TReferWin::delete_BST()
{
if(BST)
  {
  TBtnStateThread* bst = BST;
  BST = NULL;
  bst->Terminate();
  bst->Resume();
  bst->WaitFor();
  delete bst;
  }
}
//----------------------------------------------------------------------------
void __fastcall TReferWin::create_BST()
{
BST = new TBtnStateThread(true,this);
if(BST)
   BST->Resume();
}
//----------------------------------------------------------------------------
bool __fastcall TBtnStateThread::out_of_area(TImage* img)
{
TPoint pt;
if(::GetCursorPos(&pt))           //!!! Do not use Mouse->CursorPos.x. Error 5 - Отказано в доступе к структуре Mouse при старте другой программы в от имени администратора
  {
  if(pt.x < img->ClientOrigin.x)
     return true;
  if(pt.y < img->ClientOrigin.y)
     return true;
  if(pt.x > img->ClientOrigin.x + img->Width)
     return true;
  if(pt.y > img->ClientOrigin.y + img->Height)
     return true;
  }
return false;
}
//----------------------------------------------------------------------------
void __fastcall TBtnStateThread::Execute()
{
while(!Terminated)
     {
     if(win->bp_1.bs == BtnState_FOCUSED)
        if(win->bp_1.bs != BtnState_PRESSED)
          {
          if(out_of_area(win->Refer_Img))
            {
            int a  = BtnState_ACTIVE;
                a |=  0x10000;
            ::PostMessage(win->Handle, REFER_BTN_MSG, WM_APP_MSG_WPARAM__NDEF, a);
            }
          }
     if(win->bp_2.bs == BtnState_FOCUSED)
        if(win->bp_2.bs != BtnState_PRESSED)
          {
          if(out_of_area(win->Refer_Ans_Img))
            {
            int a  = BtnState_ACTIVE;
                a |=  0x20000;
            ::PostMessage(win->Handle, REFER_BTN_MSG, WM_APP_MSG_WPARAM__NDEF, a);
            }
          }
     ::Sleep(100);
     }
}
//----------------------------------------------------------------------------
void __fastcall TReferWin::Get_REFER_BTN_MSG(TMessage &Message)
{
int btn        = Message.LParam >> 16;
BtnState state = (BtnState)(Message.LParam & 0xFFFF);
switch(btn){
      case 1:change_state(Refer_Img, state);
             break;
      case 2:change_state(Refer_Ans_Img, state);
             break;
      }
}
//-----------------------------------------------------------------------------
void __fastcall TReferWin::change_state(TImage* img, BtnState state)
{
switch(state){
      case BtnState_ACTIVE:
           refresh_btn_state(img, BtnState_ACTIVE);
           break;
      }
}
//-----------------------------------------------------------------------------

void __fastcall TReferWin::FormCreate(TObject *Sender)
{
if(MainFormSLS->ofs)
  if(MainFormSLS->ofs->elt)
    if(MainFormSLS->ofs->elt->getlog())
      {
      string TimeStr;
      TDateTime DateTime = DateTime.CurrentDateTime();
      exsDateTime(DateTime,TimeStr);
      string str = "\n" + (string)TimeStr + " TReferWin_CREATED! " + "\n";
      MainFormSLS->ofs->elt->FputEvt(str, 1);
      }
}
//---------------------------------------------------------------------------

