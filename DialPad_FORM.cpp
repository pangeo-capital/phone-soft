//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "DialPad_FORM.h"
#include "SipClient_Unit.h"
#include "About_Unit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TDialPad *DialPad;
const input_left_margin       = 20;
const input_top_margin        = 15;
const input_height            = 40;
const dig_img_width           = 80;
const dig_img_width_interval  = 2;
const dig_img_height          = 40;
const dig_img_height_interval = 2;
const dig_string_top          = 2;
const btn_width               = 80;
const btn_height              = 30;
//---------------------------------------------------------------------------
__fastcall TDialPad::TDialPad(TComponent* Owner)
        : TForm(Owner)
{
if(MainFormSLS->lng == Lang_RU)
   Caption = "";
else
   Caption = "DialPad";
IS          = InitState_NDef;
Tag         = -1;
Width       = 300;
Height      = 300;
Color       = clWhite;
TBorderIcons BI = BorderIcons;
BI = BI << biSystemMenu;
BorderIcons = BI;
BorderStyle = bsDialog;
Visible     = false;  //Must be set in Object Inspector
KeyPreview  = true;   //ForHide wind by Esc key
FormStyle   = fsStayOnTop;
OnMouseMove = DialPadMouseMove;
OnKeyUp     = DialPadKeyUp;

CreatePanel();
Width = 2*input_left_margin + Panel->Width;
CreateEdit();
CreateDigImg();
CreateCallBtnImg();
CreateAddBtnImg();
DialPad_Height_0    = dig10->Top + dig10->Height + 2*dig_img_height + 40;
DialPad_Height_DTMF = dig10->Top + dig10->Height + 50;
Height              = DialPad_Height_0;
}
//---------------------------------------------------------------------------
TDigImage* __fastcall TDialPad::create_dig_img(int dig)
{
TDigImage* img = new TDigImage(this,dig);
img->Parent = this;
img->Left   = get_left_dig_margin(dig);
img->Top    = get_top_dig_margin(dig); //Bevel->Top + Bevel->Height + 1;
img->Width  = dig_img_width;
img->Height = dig_img_height;
//img->ShowHint    = true;
//img->Hint        = "Отбой";
//disc_img->Transparent = true;
img->set_state(0);
img->create_dig_inscription();
img->create_letter_inscription();
return img;
}
//---------------------------------------------------------------------------
int __fastcall TDialPad::get_left_dig_margin(int dig)
{
switch(dig){
      case  1:
      case  4:
      case  7:
      case 10: return input_left_margin;
      case  2:
      case  5:
      case  8:
      case 11: return input_left_margin + dig_img_width + dig_img_width_interval;
      case  3:
      case  6:
      case  9:
      case 12: return input_left_margin + 2*dig_img_width + 2*dig_img_width_interval;
      }
return input_left_margin;
}
//--------------------------------------------------------------------------
int __fastcall TDialPad::get_top_dig_margin(int dig)
{
switch(dig){
      case  1:
      case  2:
      case  3: return input_top_margin + Panel->Height + dig_img_height_interval;
      case  4:
      case  5:
      case  6: return input_top_margin + Panel->Height + dig_img_height + 2*dig_img_height_interval;
      case  7:
      case  8:
      case  9: return input_top_margin + Panel->Height + 2*dig_img_height + 3*dig_img_height_interval;
      case 10:
      case 11:
      case 12: return input_top_margin + Panel->Height + 3*dig_img_height + 4*dig_img_height_interval;
      }
return input_top_margin;
}
//--------------------------------------------------------------------------
void __fastcall TDialPad::CreateDigImg()
{
dig1  =  create_dig_img(1);
dig2  =  create_dig_img(2);
dig3  =  create_dig_img(3);
dig4  =  create_dig_img(4);
dig5  =  create_dig_img(5);
dig6  =  create_dig_img(6);
dig7  =  create_dig_img(7);
dig8  =  create_dig_img(8);
dig9  =  create_dig_img(9);
dig10 =  create_dig_img(10);
dig11 =  create_dig_img(11);
dig12 =  create_dig_img(12);
}
//----------------------------------------------------------------------------
__fastcall TDigImage::TDigImage(TComponent* Owner, int DIG)
           :TImage(Owner),
            dig(DIG),
            state(0)
{
is = InitState_NDef;
Canvas->Font->Name  = "Arial";
}
//------------------------------------------------------------------------------
void __fastcall TDigImage::set_state(int st)
{
state = st;
refresh_image();
}
//---------------------------------------------------------------------------
void __fastcall TDigImage::refresh_image()
{
refresh_background_color();
refresh_dig_inscription();
}
//---------------------------------------------------------------------------
void __fastcall TDigImage::refresh_dig_inscription()
{
refresh_sdig();
refresh_sletter();
}
//---------------------------------------------------------------------------
void __fastcall TDigImage::refresh_sdig()
{
Canvas->Font->Color = clBlack;
if(dig == 10)
  Canvas->Font->Size = 22;
else
  Canvas->Font->Size = 14;
if(state == 2)
  Canvas->TextOut(sdig_left, sdig_top + 1, sdig);
else
  Canvas->TextOut(sdig_left, sdig_top, sdig);
}
//---------------------------------------------------------------------------
void __fastcall TDigImage::refresh_sletter()
{
Canvas->Font->Color = (TColor)0x00EFB824;
if(dig == 11)
  {
  if(is == InitState_DTMF)
     return;
  Canvas->Font->Size = 12;
  }
else
   Canvas->Font->Size = 8;
if(state == 2)
  Canvas->TextOut(sletter_left, sletter_top + 1, sletter);
else
  Canvas->TextOut(sletter_left, sletter_top, sletter);
}
//---------------------------------------------------------------------------
void __fastcall TDigImage::set_sdig_coord()
{
sdig_left = Width/2 - Canvas->TextWidth(sdig)/2;
sdig_top  = dig_string_top;
}
//----------------------------------------------------------------------------
void __fastcall TDigImage::set_sletter_coord()
{
sletter_left = Width/2 - Canvas->TextWidth(sletter)/2;
sletter_top  = Height/2;
if(dig != 11)
  sletter_top += 2;
}
//----------------------------------------------------------------------------
void __fastcall TDigImage::create_dig_inscription()
{
Canvas->Font->Color = clBlack;
Canvas->Font->Style = Canvas->Font->Style << fsBold;
switch(dig){
       case 10: sdig = "*";
                Canvas->Font->Size = 22;
                break;
       case 11: sdig = "0";
                Canvas->Font->Size = 14;
                break;
       case 12: sdig = "#";
                Canvas->Font->Size = 14;
                break;
       default: sdig = IntToStr(dig);
                Canvas->Font->Size = 14;
                break;
       }
set_sdig_coord();
Canvas->TextOut(sdig_left, sdig_top, sdig);
}
//----------------------------------------------------------------------------
void __fastcall TDigImage::create_letter_inscription()
{
Canvas->Font->Color = (TColor)0x00EFB824; //turquoise_color;  //0x0024B8EF;
Canvas->Font->Style = Canvas->Font->Style << fsBold;
Canvas->Font->Size  = 8;
switch(dig){
      case  2: sletter = "ABC";  break;
      case  3: sletter = "DEF";  break;
      case  4: sletter = "GHI";  break;
      case  5: sletter = "JKL";  break;
      case  6: sletter = "MNO";  break;
      case  7: sletter = "PQRS"; break;
      case  8: sletter = "TUV";  break;
      case  9: sletter = "PQRS"; break;
      case 11: sletter = "+";
               Canvas->Font->Size = 12;
               break;
      }
set_sletter_coord();
Canvas->TextOut(sletter_left, sletter_top, sletter);
}
//-----------------------------------------------------------------------------
void __fastcall TDigImage::refresh_background_color()
{
switch(state){
       case 0: Canvas->Brush->Color = (TColor)0x00EDEDED; break; // Normal
       case 1: Canvas->Brush->Color = (TColor)0x00E4E4E4; break; // Focused
       case 2: Canvas->Brush->Color = (TColor)0x00E0E0E0; break; // Focused
      }
Canvas->FillRect(Rect(0,0,Width,Height));
}
//-------------------------------------------------------------------------
void __fastcall TDialPad::Clear_Digits_State()
{
for(int i = 0; i < ControlCount; i++)
   {
   TDigImage* dig = dynamic_cast<TDigImage*>(Controls[i]);
   if(dig)
     {
     if(dig->get_state())
        dig->set_state(0);   //set dig img to normal state
     }
   }
}
//--------------------------------------------------------------------------
void __fastcall TDialPad::Clear_Btn_State()
{
if(CallBtn->get_btn_state() != 1)
  {
  CallBtn->set_btn_state(1);
  Refresh_CallBtn();
  }
}
//--------------------------------------------------------------------------
void __fastcall TDialPad::CreatePanel()
{
Panel = new TPanel(this);
Panel->Parent      = this;
Panel->Color       = clWhite;
Panel->BorderStyle = bsNone;
Panel->BevelWidth  = 1;
Panel->BorderWidth = 0;
Panel->Top         = input_top_margin;
Panel->Left        = input_left_margin;
Panel->Height      = input_height;
Panel->Width       = 3*dig_img_width + 2*dig_img_width_interval;
Panel->BevelInner  = bvRaised;
Panel->BevelOuter  = bvLowered;
Panel->OnMouseMove = PanelMouseMove;
}
//----------------------------------------------------------------------------
void __fastcall TDialPad::CreateEdit()
{
Edit = new TEdit(Panel);
Edit->Parent      = Panel;
Edit->Font->Size  = 12;//10;
Edit->Font->Style = Edit->Font->Style << fsBold;
Edit->Width       = Panel->Width - 4;
Edit->Top         = Panel->Height/2 - Edit->Height/2 + 2;
Edit->Left        = 2; //15;
Edit->Ctl3D       = false;
Edit->BorderStyle = bsNone;
}
//----------------------------------------------------------------------------
void __fastcall TDialPad::DigImgMouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
Clear_Controls_State();
TDigImage* img = (TDigImage*)Sender;
img->set_state(1); // Focused
}
//-----------------------------------------------------------------------------
void __fastcall TDialPad::Clear_Controls_State()
{
Clear_Digits_State();
Clear_Btn_State();
}
//------------------------------------------------------------------------------
void __fastcall TDialPad::DialPadMouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
Clear_Controls_State();
}
//-------------------------------------------------------------------------
void __fastcall TDialPad::PanelMouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
Clear_Controls_State();
}
//--------------------------------------------------------------------------
void __fastcall TDialPad::DialPadKeyUp(TObject *Sender, WORD &Key, TShiftState Shift)
{
 if(Key == 27)
    Hide();
}
//-----------------------------------------------------------------------------
void __fastcall TDialPad::FormShow(TObject *Sender)
{
if(AboutWin)
  if(AboutWin->Visible)
     AboutWin->Hide();
dig11->refresh_image();
switch(IS){
      case InitState_DTMF:
           Top  = MainFormSLS->Panel1->ClientOrigin.y + MainFormSLS->Panel1->Height + 50;
           Left = MainFormSLS->Panel1->ClientOrigin.x + MainFormSLS->Panel1->Width/2 - MainFormSLS->Panel1->Width/9 - Width/2;
      break;
      default:
           Top  = MainFormSLS->Panel1->ClientOrigin.y + MainFormSLS->Panel1->Height;
           Left = MainFormSLS->Panel1->ClientOrigin.x + MainFormSLS->Panel1->Width/2 - Width/2;
           if(!last_called_name.empty())
             {
             AnsiString S = last_called_name.c_str();
             Edit->Text = S;
             }
      break;
      }
}
//---------------------------------------------------------------------------
void __fastcall TDialPad::Assign_DTMF_PressBtnActions(int tag)
{
Height = DialPad_Height_DTMF; //DialPad_Height_0 - dig_img_height + 20;
Tag = tag;
for(int i = 0; i < ControlCount; i++)
   {
   TDigImage* img = dynamic_cast<TDigImage*>(Controls[i]);
   if(img)
     {
     img->set_is(IS);     
     img->Tag         = tag;
     img->OnMouseMove = DigImgMouseMove;
     img->OnMouseDown = DigImg_DTMF_MouseDown;
     img->OnMouseUp   = DigImg_DTMF_MouseUp;
     }
   }
CallBtn->Hide();
AddBtn->Hide();
Caption = "DTMF";
}
//--------------------------------------------------------------------------
void __fastcall TDialPad::Assign_DIAL_PressBtnActions()
{
Height = DialPad_Height_0;
for(int i = 0; i < ControlCount; i++)
   {
   TDigImage* img = dynamic_cast<TDigImage*>(Controls[i]);
   if(img)
     {
     img->set_is(IS);
     img->OnMouseMove = DigImgMouseMove;
     img->OnMouseDown = DigImg_DIAL_MouseDown;
     img->OnMouseUp   = DigImg_DIAL_MouseUp;
     }
   }

CallBtn->set_btn_state(1); //Active
Refresh_CallBtn();
CallBtn->OnMouseMove = CallBtn_MouseMove;
CallBtn->OnMouseDown = CallBtn_MouseDown;
CallBtn->OnMouseUp   = CallBtn_MouseUp;
CallBtn->Show();

AddBtn->set_btn_state(0); //Active
Refresh_AddBtn();
AddBtn->OnMouseMove = AddBtn_MouseMove;
AddBtn->OnMouseDown = AddBtn_MouseDown;
AddBtn->OnMouseUp   = AddBtn_MouseUp;
AddBtn->Show();
Caption = AnsiString();
}
//--------------------------------------------------------------------------
void __fastcall TDialPad::Show_DPW(InitState is,int tag)
{
//if(IS != is)
Edit->Clear();
IS = is;
switch(IS){
      case InitState_DTMF:
           Assign_DTMF_PressBtnActions(tag);
           break;
      case InitState_DIAL:
           Assign_DIAL_PressBtnActions();
           break;
      }
Show();
}
//------------------------------------------------------------------------------
void __fastcall TDialPad::Hide_DPW()
{
Tag = -1;
Hide();
}
//-----------------------------------------------------------------------------
void __fastcall TDialPad::DigImg_DIAL_MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
TDigImage* img = (TDigImage*)Sender;
img->set_state(2); // Pressed
if(img->get_dig() == 11)  //Presse "0"
   img->time_stmp();
}
//---------------------------------------------------------------------------
void __fastcall TDialPad::DigImg_DIAL_MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
TDigImage* img = (TDigImage*)Sender;
img->set_state(0); // Normal
AnsiString dial = img->get_sdig();
if(img->get_dig() == 11) //Pressed "0"
 if(Edit->Text.IsEmpty())
   {
   TDateTime dt;
   dt = dt.CurrentDateTime();
   if(dt - img->get_time_stmp() > TDateTime(0,0,0,500))
      dial = "+";
   }
if(Edit->Text.IsEmpty())
   Edit->Text = dial;
else
  {
  AnsiString S = Edit->Text;
  S += dial;
  Edit->Text = S;
  }
}

//---------------------------------------------------------------------------
static int dtmf_pktn;
void __fastcall TDialPad::DigImg_DTMF_MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
TDigImage* img = (TDigImage*)Sender;
img->set_state(2); // Pressed

int local_tag = get_pressed_dig(img);

TMediaSession* ms = MainFormSLS->Sip->sss->GetMs_by_Call_Tag(img->Tag);
if(ms)
  {
  TUdpChannel* uc = ms->getSoundChannel();
  if(uc)
    if(uc->wopt)
      if(uc->wopt->WOS == WaveOutputState_RECEIVING_VOICE)
        {
        uc->wopt->dtmf.wos   = uc->wopt->WOS;
        uc->wopt->dtmf.digit = local_tag;
        uc->wopt->WOS = WaveOutputState_GEN_DTMF_DIGITS_START;
        }
  uc = ms->getRtpAudioChannel();
  if(uc)
    if(uc->sendThread)
      {
      int dig = local_tag - 10;
      for(int i=0;i<7;i++)
         switch(i){
               case 0:{
                      TOutPutDtmfBlock* opd = MainFormSLS->exsCreateOutPutDtmfBlock(dtmf_pktn,START_DTT,16,160,1,101);
                      if(opd)
                        {
                        opd->first_byte(dig);
                        opd->second_byte(false,10); //0 - "end" flag,10 - signal volume
                        opd->dig_duration(160);
                        uc->sendThread->DTS.push_dtmf(uc->sendThread,opd);
                        MainFormSLS->Sip->updateSentQueue_1(opd);
                        }
                      break;
                      }
               case 1:{
                      TOutPutDtmfBlock* opd = MainFormSLS->exsCreateOutPutDtmfBlock(dtmf_pktn,CONTINUE_DTT,16,160,0,101);
                      if(opd)
                        {
                        opd->first_byte(dig);
                        opd->second_byte(false,10);
                        opd->dig_duration(320);
                        uc->sendThread->DTS.push_dtmf(uc->sendThread,opd);
                        MainFormSLS->Sip->updateSentQueue_1(opd);
                        }
                       break;
                      }
               case 2:{
                      TOutPutDtmfBlock* opd = MainFormSLS->exsCreateOutPutDtmfBlock(dtmf_pktn,CONTINUE_DTT,16,160,0,101);
                      if(opd)
                        {
                        opd->first_byte(dig);
                        opd->second_byte(false,10);
                        opd->dig_duration(480);
                        uc->sendThread->DTS.push_dtmf(uc->sendThread,opd);
                        MainFormSLS->Sip->updateSentQueue_1(opd);
                        }
                       break;
                      }
               case 3:{
                      TOutPutDtmfBlock* opd = MainFormSLS->exsCreateOutPutDtmfBlock(dtmf_pktn,CONTINUE_DTT,16,160,0,101);
                      if(opd)
                        {
                        opd->first_byte(dig);
                        opd->second_byte(false,10);
                        opd->dig_duration(640);
                        uc->sendThread->DTS.push_dtmf(uc->sendThread,opd);
                        MainFormSLS->Sip->updateSentQueue_1(opd);
                        }
                      break;
                      }
               case 4:{
                      TOutPutDtmfBlock* opd = MainFormSLS->exsCreateOutPutDtmfBlock(dtmf_pktn,STOP_DTT,16,160,0,101);
                      if(opd)
                        {
                        opd->first_byte(dig);
                        opd->second_byte(true,10);
                        opd->dig_duration(800);
                        uc->sendThread->DTS.push_dtmf(uc->sendThread,opd);
                        MainFormSLS->Sip->updateSentQueue_1(opd);
                        }
                       break;
                      }
               case 5:{
                      TOutPutDtmfBlock* opd = MainFormSLS->exsCreateOutPutDtmfBlock(dtmf_pktn,PAUSE_DTT,20,0,0,0);
                      if(opd)
                        {
                        uc->sendThread->DTS.push_dtmf(uc->sendThread,opd);
                        MainFormSLS->Sip->updateSentQueue_1(opd);
                        }
                      break;
                      }
               case 6:{
                      TOutPutDtmfBlock* opd = MainFormSLS->exsCreateOutPutDtmfBlock(dtmf_pktn,PAUSE_DTT,0,0,0,0);
                      if(opd)
                        {
                        uc->sendThread->DTS.push_dtmf(uc->sendThread,opd);
                        MainFormSLS->Sip->updateSentQueue_1(opd);
                        }
                      break;
                      }
               }
      }
  }
}
//-------------------------------------------------------------------------------
void __fastcall TDialPad::DigImg_DTMF_MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
TDigImage* img = (TDigImage*)Sender;
img->set_state(0); // Normal
if(Edit->Text.IsEmpty())
   Edit->Text = img->get_sdig();
else
  {
  AnsiString S = Edit->Text;
  S += img->get_sdig();;
  Edit->Text = S;
  }
TMediaSession* ms = MainFormSLS->Sip->sss->GetMs_by_Call_Tag(img->Tag);
if(ms)
  {
  TUdpChannel* uc = ms->getSoundChannel();
  if(uc)
    if(uc->wopt)
      if((uc->wopt->WOS == WaveOutputState_GEN_DTMF_DIGITS_START)||(uc->wopt->WOS == WaveOutputState_GEN_DTMF_DIGITS_CONTINUE))
         uc->wopt->WOS = WaveOutputState_GEN_DTMF_DIGITS_STOP;
  }
}
//----------------------------------------------------------------------------
int __fastcall TDialPad::get_pressed_dig(TDigImage* img)
{
int dig = img->get_dig();
if(dig < 11)  return dig + 10;
if(dig == 11) return 10;
if(dig == 12) return 21;
return 10; //for exclude warning
}
//----------------------------------------------------------------------------
void __fastcall TDialPad::CreateCallBtnImg()
{
CallBtn = new TBtnImage(this);
CallBtn->Parent   = this;
CallBtn->Width    = btn_width;
CallBtn->Height   = btn_height;
CallBtn->Left     = dig11->Left;
CallBtn->Top      = dig11->Top + dig11->Height + 4*dig_img_height_interval;
CallBtn->Hint     = "Позвонить";
CallBtn->ShowHint = true;
CallBtn->set_btn_state(1);
}
//-----------------------------------------------------------------------------
void __fastcall TDialPad::CreateAddBtnImg()
{
AddBtn = new TBtnImage(this);
AddBtn->Parent = this;
AddBtn->Width  = 3*dig_img_width + 2*dig_img_width_interval;
AddBtn->Height = btn_height;
AddBtn->Left   = dig1->Left;
AddBtn->Top    = CallBtn->Top + CallBtn->Height + 4*dig_img_height_interval;
AddBtn->set_btn_state(0);
}
//-----------------------------------------------------------------------------
void __fastcall TDialPad::Refresh_CallBtn()
{
CallBtn->clear();
switch(CallBtn->get_btn_state()){
       case 0: IL->Draw(CallBtn->Canvas,0,0,CALL_BTN_INACTIVE_INDX,true); break;
       case 1: IL->Draw(CallBtn->Canvas,0,0,CALL_BTN_ACTIVE_INDX,true);   break;
       case 2: IL->Draw(CallBtn->Canvas,0,0,CALL_BTN_FOCUS_INDX,true);    break;
       case 3: IL->Draw(CallBtn->Canvas,0,0,CALL_BTN_PRESSED_INDX,true);  break;
      }
}
//-----------------------------------------------------------------------------
void __fastcall TDialPad::Refresh_AddBtn()
{
AddBtn->clear();
int FOREGROUND;
switch(AddBtn->get_btn_state()){
       case BtnState_ACTIVE:   FOREGROUND = FOREGR_ACTIVE_GREEN;  break;
       case BtnState_FOCUSED:  FOREGROUND = FOREGR_FOCUSED_GREEN; break;
       case BtnState_PRESSED:  FOREGROUND = FOREGR_PRESSED_GREEN; break;
       case BtnState_INACTIVE: FOREGROUND = FOREGR_ACTIVE_GREEN;  break; //надо сменить на FOREGR_INACTIV
       default: FOREGROUND = FOREGR_ACTIVE_GREEN;  break;
       }
TRBitMap rbmp(AddBtn->Width, btn_height, clWhite, FOREGROUND);
AddBtn->Canvas->Draw(0,0, rbmp.bmp);
AnsiString S = "Добавить в личные контакты";
AddBtn->Canvas->Brush->Color = (TColor)FOREGROUND;
AddBtn->Canvas->Font->Charset = RUSSIAN_CHARSET;
AddBtn->Canvas->Font->Color  = clWhite;
AddBtn->Canvas->Font->Size   = 10;
AddBtn->Canvas->Font->Style  = AddBtn->Canvas->Font->Style << fsBold;
int tw = AddBtn->Canvas->TextWidth(S);
int th = AddBtn->Canvas->TextHeight(S);
int text_left = AddBtn->Width/2  - tw/2;
int text_top  = AddBtn->Height/2 - th/2;
if(AddBtn->get_btn_state() == BtnState_PRESSED)
   text_top += 1;
AddBtn->Canvas->TextOut(text_left, text_top, S);
}
//-----------------------------------------------------------------------------
void __fastcall TDialPad::CallBtn_MouseDown(TObject *Sender,TMouseButton Button, TShiftState Shift, int X, int Y)
{
TBtnImage* CallBtn = (TBtnImage*)Sender;
CallBtn->set_btn_state(3);
Refresh_CallBtn();
}
//----------------------------------------------------------------------------
void __fastcall TDialPad::CallBtn_MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
TBtnImage* CallBtn = (TBtnImage*)Sender;
CallBtn->set_btn_state(1);
AnsiString S = Edit->Text;
if(!S.IsEmpty())
  {
  MainFormSLS->set_user_name_to_send(S.c_str());
  MainFormSLS->ComboBox1->Text        = S;
  MainFormSLS->CalledNameLbl->Caption = S;
  string s = S.c_str();
  if(!MainFormSLS->Sip->Contacts.is_contact_exists(s))
    {
    last_called_name = s;
    Edit->Hint     = "Данный номер отсутствует в списке личных контактов";
    Edit->ShowHint = true;
    }
  else
    {
    last_called_name.clear();
    Edit->ShowHint = false;
    }
  MainFormSLS->AudioCall();
  Hide();
  }
}
//------------------------------------------------------------------------------
void __fastcall TDialPad::CallBtn_MouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
TBtnImage* CallBtn = (TBtnImage*)Sender;
CallBtn->set_btn_state(2);
Refresh_CallBtn();
set_img_cursor_type((TImage*)Sender);
}
//------------------------------------------------------------------------------
void __fastcall TDialPad::AddBtn_MouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
set_img_cursor_type((TImage*)Sender);
}
//------------------------------------------------------------------------------
void __fastcall TDialPad::AddBtn_MouseDown(TObject *Sender,TMouseButton Button, TShiftState Shift, int X, int Y)
{
TBtnImage* AddBtn = (TBtnImage*)Sender;
AddBtn->set_btn_state(2);
Refresh_AddBtn();
}
//----------------------------------------------------------------------------
void __fastcall TDialPad::AddBtn_MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
TBtnImage* AddBtn = (TBtnImage*)Sender;
AddBtn->set_btn_state(0);
Refresh_AddBtn();
AnsiString S = Edit->Text;
if(!S.IsEmpty())
  {
  string name = S.c_str();
  if(!MainFormSLS->Sip->Contacts.is_contact_exists(name))
    {
    TContact* CONT   = new TContact(MainFormSLS->Sip->Contacts.get_next_contact_id());
    CONT->CT         = ContactType_CLIENT;
    CONT->CL         = Location_EXT;
    CONT->name       = name;
    CONT->full_name  = name;
    last_called_name.clear();
    Edit->ShowHint = false;
    if(MainFormSLS->ProfileForm)
       delete MainFormSLS->ProfileForm;
    MainFormSLS->ProfileForm = new TProfileForm(this,2);
    MainFormSLS->ProfileForm->AddContactNameControls(this);
    MainFormSLS->ProfileForm->Contact = CONT;
    MainFormSLS->ProfileForm->Show();
    }
  }
}
//------------------------------------------------------------------------------
void __fastcall TDialPad::FormClose(TObject *Sender, TCloseAction &Action)
{
if(MainFormSLS->ProfileForm)
   MainFormSLS->ProfileForm->Close();
}
//---------------------------------------------------------------------------


