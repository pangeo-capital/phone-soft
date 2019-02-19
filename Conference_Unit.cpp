//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "WinRDefs.h"
#include "Conference_Unit.h"
#include "SipClient_Unit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

#define MIC_CNVS_ACTIVE  2  //index in ConferenceWin::TImageList::BtImgs
#define MIC_CNVS_SW_OFF  3  //index in ConferenceWin::TImageList::BtnImgs

const  LAYOUT_TOP     = 30;
const  VERT_INTERVAL  = 37;
const  CONF_WIN_COLOR = 0x00372205;

TConferenceWin *ConferenceWin;
//---------------------------------------------------------------------------
__fastcall TConferenceWin::TConferenceWin(TComponent* Owner)
        : TForm(Owner)
{
::InitializeCriticalSection(&cp_cs);
::InitializeCriticalSection(&exch_list_cs);
::InitializeCriticalSection(&erase_cs);
CONF_BST   = NULL;
CONF_FLASH = NULL;
Default_Top = Default_Left = Default_Width = Default_Height = 0;
Default_Size          = true;
CONFERENCE_CREATOR    = false;
screen_sharing_active = false;
mic_switched_on       = false;

Color = (TColor)CONF_WIN_COLOR;
//ImgsTop                 = ClientHeight - 80;
ShowIM                = false;
PrevHeight            = Height;
PrevWidth             = Width;
block_shift           = false;

conf_mic_img = new TBtnImage(this);
conf_mic_img->Parent    = this;
conf_mic_img->Width     = 42;
conf_mic_img->Height    = 42;
conf_mic_img->Left      = 0; //dig11->Left;
conf_mic_img->Top       = 0; //dig11->Top + dig11->Height + 4*dig_img_height_interval;
conf_mic_img->set_btn_state(1);  //Active
conf_mic_img->OnMouseUp = conf_mic_img_MouseUp;

conf_disc_img->ShowHint   = true;
conf_screen_img->ShowHint = true;
conf_add_img->ShowHint    = true;
conf_mic_img->ShowHint    = true;

MIC_SWITCH_ON();  //Draw active microphone
BtnImgs->Draw(conf_screen_img->Canvas,0,0,0,true); conf_screen_img->Refresh();

set_imgs_invisible();

conf_disc_img->Hint   = "Положить трубку";
conf_screen_img->Hint = "Демонстрация экрана";
conf_add_img->Hint    = "Добавить участника";
//conf_mic_img->Hint    = "Выключить микрофон";

//MainFormSLS->LAST_FORM_CREATED = true; //!!!
}
//---------------------------------------------------------------------------
void __fastcall TConferenceWin::FormDestroy(TObject *Sender)
{
delete_CONF_BST();
delete_CONF_FLASH();
::DeleteCriticalSection(&exch_list_cs);
::DeleteCriticalSection(&cp_cs);
::DeleteCriticalSection(&erase_cs);
}
//---------------------------------------------------------------------------
__fastcall TConfPanel::TConfPanel(bool default_avatar, TComponent* Owner)
           : TPanel(Owner)
{
TConferenceWin* Win = (TConferenceWin*) Owner;
lights        = false;
new_vad_event = false;
img           = new TImage(this);
img->Parent   = this;
int sz = Win->get_size_CP(); //Number of conference participants (excluding this contact)
switch(sz){
      case 1:
      case 2:
      case 3:
      case 4: {
               int W  = Win->Width/3;
               if(W > 158)
                  W = 158;
               int H  = 6*W/7;
               if(H > 135)
                  H = 135;
               Width  = W;
               Height = H;
               break;
              }
      default: Width  = 100;
               Height = 100;
               break;
      }
img->Width  = Width;
img->Height = Height;
Graphics::TBitmap *pBitmap = new Graphics::TBitmap();
if(pBitmap)
   {
   if(default_avatar)
     { //Load default_avatar
      pBitmap->Width  = 225;
      pBitmap->Height = 215;
      Win->ImageList1->Draw(pBitmap->Canvas,0,0,0,true);
     //Win->ImageList1->Draw(pBitmap->Canvas,0,0,1,true);
     }
   else
     {  //Load contact avatar from file
     /*
      pBitmap->Width  = 225;
      pBitmap->Height = 215;
      pBitmap->LoadFromFile("C:\\test\\Avt_2.bmp");
      Win->ImageList1->Draw(pBitmap->Canvas,0,0,0,true);
     // Win->ImageList1->Draw(pBitmap->Canvas,0,0,1,true);
     */
     }

   TRect Rect(0,0,Width,Height);
   img->Canvas->StretchDraw(Rect, pBitmap);


   delete pBitmap;
   }
}
//---------------------------------------------------------------------------
__fastcall TConfPanel::~TConfPanel()
{
if(img)
   delete img;
}
//---------------------------------------------------------------------------
void __fastcall TConferenceWin::ins_exch_buf(TConfExchBlock* buf)
{
::EnterCriticalSection(&exch_list_cs);
  exch_list.push(buf);
::LeaveCriticalSection(&exch_list_cs);
}
//--------------------------------------------------------------------------
TConfExchBlock* __fastcall TConferenceWin::_get_exch_buf()
{
TConfExchBlock* buf = NULL;
::EnterCriticalSection(&exch_list_cs);
  if(!exch_list.empty())
    {
    buf = exch_list.front();
    exch_list.pop();
    }
::LeaveCriticalSection(&exch_list_cs);
return buf;
}
//--------------------------------------------------------------------------
void __fastcall TConferenceWin::Get_CONFERENCE_MSG(TMessage &Message)
{
try{
TConfExchBlock* buf = _get_exch_buf();
while(buf){
     proc_conference_msg(buf);
     delete buf;
     buf = _get_exch_buf();
     }
}//try
catch(Exception& e){exsSstEXCEPTION(MainFormSLS->ofs->elt,"__Get_CONFERENCE_MSG(TMessage &Message)",e);}
}
//------------------------------------------------------------------------------
void __fastcall TConferenceWin::Get_CONFERENCE_PLAIN_MSG(TMessage &Message)
{
try{
switch(Message.WParam){
       case WM_CONFERENCE_PLAIN_MSG_WPARAM__VAD:
            if(mic_switched_on)
               Distribute_OWN_Vad_Event();
            break;
       case WM_CONFERENCE_PLAIN_MSG_WPARAM__MAXIMIXE:
            if(Visible)
              if(get_size_CP())
                 ChangeWinLayout_OnResize();
            break;
       case WM_CONFERENCE_PLAIN_MSG_WPARAM__SHIFT_BTNS_DOWN:{
            int a = conf_mic_img->Top;
            conf_mic_img->Top = a + 5;
            conf_add_img->Top    = conf_mic_img->Top;
            conf_screen_img->Top = conf_mic_img->Top;
            conf_disc_img->Top   = conf_mic_img->Top;
            conf_chat_img->Top   = conf_mic_img->Top;
            if(conf_mic_img->Top > Height)
              if(CONF_BST)
                {
                CONF_BST->BTNS_STATE = BS_CLOSED;
                set_imgs_invisible();
                }
            }
            break;
       case WM_CONFERENCE_PLAIN_MSG_WPARAM__SHIFT_BTNS_UP:{
            int a = conf_mic_img->Top;
            if(conf_mic_img->Top <= ClientHeight - 80 + 20)
               conf_mic_img->Top = a - 2;
            else
               conf_mic_img->Top = a - 5;
            conf_add_img->Top    = conf_mic_img->Top;
            conf_screen_img->Top = conf_mic_img->Top;
            conf_disc_img->Top   = conf_mic_img->Top;
            conf_chat_img->Top   = conf_mic_img->Top;
            if(conf_mic_img->Top <= ClientHeight - 80)
              {
              if(CONF_BST)
                {
                __update_last_mouse_move();
                CONF_BST->BTNS_STATE = BS_MOUSEMOVED;
                }
              }
            }
            break;
       case WM_CONFERENCE_PLAIN_MSG_WPARAM__SHIFT_BTNS_ON_TOP:{
            conf_mic_img->Top = ClientHeight - 80;
            conf_add_img->Top    = conf_mic_img->Top;
            conf_screen_img->Top = conf_mic_img->Top;
            conf_disc_img->Top   = conf_mic_img->Top;
            conf_chat_img->Top   = conf_mic_img->Top;
            }
            break;
       }
}//try
catch(Exception& e){exsSstEXCEPTION(MainFormSLS->ofs->elt,"__Get_CONFERENCE_VAD_MSG(TMessage &Message)",e);}
}
//------------------------------------------------------------------------------
void __fastcall TConferenceWin::proc_conference_msg(TConfExchBlock* buf)
{
switch(buf->conf_evnt){
       case ConfEvnt_Add_Participant:   //Add and ans from remote ConferenceCreator
            add_participant(buf);
            break;
       case ConfEvnt_Ans_Participant:
            ans_participant(buf);      //Ans to local win
            break;
       case ConfEvnt_Del_Participant:
            del_participant(buf);
            break;
       case ConfEvnt_VAD_Enable:
            VAD_Enable(buf);
            break;
       case ConfEvnt_VAD_Received:
            VAD_Received(buf);
            break;
       case ConfEvnt_VAD_DISTR_Received:
            VAD_DISTRIBUTED_Received(buf);
            break;
       case ConfEvnt_Restore:   //Восстанавливает размер ConferenceWin после AddParticipant
            _restore();
            break;
       case ConfEvnt_DeactivateWindow:
            DEACTIVATE_CONF_WINDOW();
            break;
       }
}
//---------------------------------------------------------------------------
void __fastcall TConferenceWin::DEACTIVATE_CONF_WINDOW()
{
CLEAR();
Hide();
delete_CONF_BST();
delete_CONF_FLASH();
MainFormSLS->set_IM_to_conf_participants(false);
if(Visible)
   Close();
}
//---------------------------------------------------------------------------
void __fastcall TConferenceWin::CLEAR()
{
clear_CP();
CONFERENCE_CREATOR = false;
MIC_SWITCH_ON();
Tag = 0; //!!! Unbind window from current call
}
//-----------------------------------------------------------------------------
void  __fastcall TConferenceWin::clear_CP()
{
::EnterCriticalSection(&cp_cs);
  while(!CP.empty())
       {
       TConfParticipants::iterator it = CP.begin();
       TConfCont* ConfCont = (*it).second;
       if(ConfCont)
          INS_TO_ERASE_Q(ConfCont);
       CP.erase(it);
       }
::LeaveCriticalSection(&cp_cs);
}
//------------------------------------------------------------------------------
void __fastcall TConferenceWin::add_participant(TConfExchBlock* buf)
{
SetConfWinSize();

WindowState = wsNormal;
FormStyle   = fsStayOnTop;

Default_Left   = Left;
Default_Top    = Top;
Default_Width  = Width;
Default_Height = Height;

CONFERENCE_CREATOR = buf->Buf_Conf_Creator;
Btn_Layout(BS_NDEF);

TConfCont* ConfCont = new TConfCont;
if(ConfCont)
  {
  ConfCont->user_name          = buf->user_name;
  ConfCont->conference_creator = buf->conference_creator_exch;
  ConfCont->cc_call_state      = buf->call_state;
  ConfCont->callid             = buf->callid;
  ConfCont->call_panel_tag     = buf->ttag;
  ConfCont->lt                 = buf->lt;
  TContact ContactCopy;
  if(MainFormSLS->Sip->Contacts.get_contact_copy_by_user_name(ContactCopy, ConfCont->user_name))
     ConfCont->full_name = ContactCopy.full_name;
  else
     ConfCont->full_name = buf->user_name;
  if(ins_to_CP(ConfCont))
    {
    TConfPanel* ConfPanel  = new TConfPanel(true, this);   // Avatar
    ConfPanel->Parent      = this;
    ConfPanel->user_name   = buf->user_name;
    ConfCont->conf_panel   = ConfPanel;

    TLabel* lbl            = new TLabel(this);
    lbl->Parent            = this;
    lbl->Caption           = ConfCont->full_name.c_str();
    lbl->Font->Color       = clWhite;
    lbl->Font->Height      = 16;
    lbl->Font->Name        = "Arial";
    ConfCont->lbl          = lbl;

    TLabel* lbl1           = new TLabel(this); // for long full_name
    lbl1->Parent           = this;
    lbl1->Font->Color      = clWhite;
    lbl1->Font->Height     = 16;
    lbl1->Font->Name       = "Arial";
    ConfCont->lbl1         = lbl1;

    if(CONFERENCE_CREATOR)
      {
      create_ctr_disc_img(ConfCont);
      if(ConfPanel)
        {
        ConfPanel->img->Tag         = ConfCont->call_panel_tag;
        ConfPanel->img->OnMouseMove = conf_panel_OnMouseMove;
        }
      if(lbl)
        {
        lbl->Tag         = ConfCont->call_panel_tag;
        lbl->OnMouseMove = lbl_OnMouseMove;
        }
      if(lbl1)
        {
        lbl1->Tag         = ConfCont->call_panel_tag;
        lbl1->OnMouseMove = lbl_OnMouseMove;
        }
      if(ConfCont->lt == Lt_Out)
        {
        if(CONF_BST)
          if(CONF_BST->Suspended)
             CONF_BST->Resume();
        }
      }
    else  //No CONFERENCE_CREATOR
      {
      if(ConfCont->cc_call_state == 0) //wait for Answer
        if(CONF_BST)
          if(CONF_BST->Suspended)
             CONF_BST->Resume();
      }

    if(!Tag)         //Assign TConference window to current call_tag (TCall_Panel)
      {
      ASSIGN_CALL_TAG(buf);
      if(Tag)
        {
        TCall_Panel* Panel = MainFormSLS->get_Call_Panel_By_Tag(Tag);
        if(Panel)
           Panel->set_conf_participant(true);
        }
      }

    if(!Visible)
      {
      ParticipantsLayout();
      Show();
      if(EnterpriseSubscList->Visible)
         EnterpriseSubscList->SetFocus();
      else
         SetFocus();
      }
    else
      ParticipantsLayout();
    } //if(ins_to_CP(ConfCont))
  else
    {
    INS_TO_ERASE_Q(ConfCont);  //ConfCont with this parameters already present in the ConferenceParticipants List
    }
  }  //if(ConfCont)
}
//--------------------------------------------------------------------------
void __fastcall TConferenceWin::create_ctr_disc_img(TConfCont* ConfCont)
{
TBtnImage* img = new TBtnImage(this);
img->Parent    = this;
img->Width     = 24;
img->Height    = 24;

img->Transparent       = true;
img->Visible           = false;
img->call_panel_tag    = ConfCont->call_panel_tag;
img->user_name         = ConfCont->user_name;
ConfCont->ctr_disc_img = img;

MainFormSLS->ImageList3->Draw(ConfCont->ctr_disc_img->Canvas,0,0,0,true);
ConfCont->ctr_disc_img->OnMouseUp = ctr_disc_img_OnMouseUp;
}
//---------------------------------------------------------------------------
void __fastcall TConferenceWin::ctr_disc_img_OnMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
TBtnImage* btn = (TBtnImage*)Sender;
if((X > 0) && (X < btn->Width))
  if((Y > 0) && (Y < btn->Height))
    {
    TCall_Panel* Panel = MainFormSLS->get_Call_Panel_By_Tag(btn->call_panel_tag);
    if(Panel)
      {
      if(Panel->get_conf_participant())
        {
        Panel->set_call_state(Call_State__Conference);
        if(Panel->get_leg_type() == Lt_In)
          {
          TMediaSession* ms = MainFormSLS->Sip->sss->GetMs_by_Call_Tag(Panel->Tag);
          Panel->disconnect_incoming_call(ms,false); //check if(ms) inside of func ; false means that  disconnect_incoming_call() initialized not from rcvd Bye fron parallel phone
          }
        else if(Panel->get_leg_type() == Lt_Out)
          {
          TMediaSession* ms = MainFormSLS->Sip->sss->GetMs_by_Call_Tag(Panel->Tag);
          Panel->disconnect_outgoing_call(ms,false);  //check if(ms) inside of func ; false means that  disconnect_incoming_call() initialized not from rcvd Bye fron parallel phone
          }
        }
      }
    else  //TCall_Panel not found(call disconnected)
      {
      del_from_CP(btn->user_name);
      if(get_size_CP())
         ParticipantsLayout();
      else
         DEACTIVATE_CONF_WINDOW();
      }
    }
}
//---------------------------------------------------------------------------
void __fastcall TConferenceWin::lbl_OnMouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
TLabel* lb = (TLabel*)Sender;
if(lb)
   flash_local_disc_img(lb->Tag);
}
//---------------------------------------------------------------------------
void __fastcall TConferenceWin::conf_panel_OnMouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
TImage* Img = (TImage*)Sender;
if(Img)
   flash_local_disc_img(Img->Tag);
}
//----------------------------------------------------------------------------
void __fastcall TConferenceWin::flash_local_disc_img(int ttag)
{
if(_flash_disc_img_CP(ttag))
  if(CONF_BST)
    if(CONF_BST->Suspended)
       CONF_BST->Resume();
}
//----------------------------------------------------------------------------
void __fastcall TConferenceWin::Btn_Layout(TBTNS_STATE BS)
{
if(BS == BS_CLOSED)
  ImgsTop = ClientHeight; //кнопки невидимы, т.к. находятся ниже у-ня окна
else
  ImgsTop = ClientHeight - 80;
conf_disc_img->Top   = ImgsTop;
conf_screen_img->Top = conf_disc_img->Top;
conf_add_img->Top    = conf_disc_img->Top;
conf_mic_img->Top    = conf_disc_img->Top;
conf_chat_img->Top   = conf_disc_img->Top;
if(CONFERENCE_CREATOR)
  {
  conf_screen_img->Left = ClientWidth/2 + conf_screen_img->Width/4;
  conf_disc_img->Left   = conf_screen_img->Left + conf_screen_img->Width + conf_disc_img->Width/2;
  conf_add_img->Left    = ClientWidth/2 - conf_add_img->Width - conf_add_img->Width/4;
  conf_mic_img->Left    = conf_add_img->Left - conf_mic_img->Width - conf_mic_img->Width/2;
  }
else
  {
  conf_disc_img->Left = ClientWidth/2 + conf_disc_img->Width/4;
  conf_mic_img->Left  = ClientWidth/2 - conf_mic_img->Width - conf_mic_img->Width/4;
  }
conf_chat_img->Left   = Width - 2 * conf_chat_img->Width;
}
//------------------------------------------------------------------------------
void __fastcall TConferenceWin::ans_participant(TConfExchBlock* buf)
{
ans_to_CP(buf->user_name);
}
//------------------------------------------------------------------------------
void __fastcall TConferenceWin::del_participant(TConfExchBlock* buf)
{
del_from_CP(buf->user_name);
if(buf->ttag == Tag) //Deleted Conference_Creator. Must be defined new conference_creator
  {
  int old_tag = Tag;
  bool new_conf_creator_assigned = false;
  for(int i = 0; i < MainFormSLS->ControlCount; i++)
     {
     TCall_Panel* Panel = dynamic_cast<TCall_Panel*>(MainFormSLS->Controls[i]);
     if(Panel)
       {
       if(Panel->Tag == Tag)  //This is deleting panel (conf creator panel)
          continue;
       else
          {
          int a = Panel->get_conf_creator();
          if(a != -1)
            if(a == Tag) //This passive participant belongs to deleting conference creator
              {
              if(!new_conf_creator_assigned)
                {
                Tag = Panel->Tag;
                Panel->set_conf_creator(Panel->Tag);
                new_conf_creator_assigned = true;
                }
              else
                {
                if(old_tag == Panel->get_conf_creator())  //This passive participant belongs to deleting conference creator
                   Panel->set_conf_creator(Tag);
                }
              }
          }
       }
     }
  }
if(get_size_CP())
   ParticipantsLayout();
else
   DEACTIVATE_CONF_WINDOW();
}
//--------------------------------------------------------------------------
void __fastcall TConferenceWin::VAD_Enable(TConfExchBlock* buf)
{
if(!buf->user_name.empty())
  activate_VAD_CP(buf->user_name);
}
//-----------------------------------------------------------------------------------------------
//-- Received two bytes 0x00,0x01 (from passive participant to conf creator) -
//-- RTCP ch -> callid or in_out_callid -> TMediaSession -> uniq_username ->send to ConferebceWin
//-----------------------------------------------------------------------------------------------
void __fastcall TConferenceWin::VAD_Received(TConfExchBlock* buf)
{
flash_participant_panel(buf);
if(CONFERENCE_CREATOR)
   Distribute_RCVD_Vad_Event(buf->user_name);
}
//-----------------------------------------------------------------------------
void __fastcall TConferenceWin::VAD_DISTRIBUTED_Received(TConfExchBlock* buf)
{
flash_participant_panel(buf);
}
//-----------------------------------------------------------------------------
void __fastcall TConferenceWin::flash_participant_panel(TConfExchBlock* buf)
{
::EnterCriticalSection(&cp_cs);
  TConfParticipants::iterator it = CP.find(buf->user_name);
  if(it != CP.end())
    {
    TConfCont* ConfCont = (*it).second;
    if(ConfCont)
      {
      if(ConfCont->conf_panel)
        if(ConfCont->conf_panel->img)
          {
          if(!ConfCont->conf_panel->lights)
            {
            bool default_avatar = true;
            Graphics::TBitmap *pBitmap = new Graphics::TBitmap();
            if(pBitmap)
              {
               if(default_avatar)
                 { //Load default_avatar
                 pBitmap->Width  = 225;
                 pBitmap->Height = 215;
                 ImageList1->Draw(pBitmap->Canvas,0,0,1,true);
                 }
               else
                 {  //Load contact avatar from file
                 /*
                 pBitmap->Width  = 225;
                 pBitmap->Height = 215;
                 pBitmap->LoadFromFile("C:\\test\\Avt_2.bmp");
                 ImageList1->Draw(pBitmap->Canvas,0,0,1,true);
                // Win->ImageList1->Draw(pBitmap->Canvas,0,0,1,true);
                 */
                 }

               TRect Rect(0, 0, ConfCont->conf_panel->img->Width, ConfCont->conf_panel->img->Height);
               ConfCont->conf_panel->img->Canvas->StretchDraw(Rect, pBitmap);
               ConfCont->conf_panel->lights = true;
               delete pBitmap;
              }  //if(pBitmap)
            }  //if(!ConfCont->conf_panel->lights)
          ConfCont->conf_panel->new_vad_event = true;
          }  //if(ConfCont->conf_panel->img)
      }   //if(ConfCont)
    }  //if(it != CP.end())
::LeaveCriticalSection(&cp_cs);
}
//-----------------------------------------------------------------------------
//--- src_user_name - from which was received VAD event
//-----------------------------------------------------------------------------
void __fastcall TConferenceWin::Distribute_RCVD_Vad_Event(const string& src_user_name)
{
::EnterCriticalSection(&cp_cs);
  deque<TConfCont*> dst;
__get_copy_CP_UNSAFE(dst);
  while(!dst.empty())
       {
       TConfCont* ConfCont = dst.front();
       dst.pop_front();
       if(ConfCont->user_name == src_user_name) //don't send vad to source
          continue;
       if(!ConfCont->vad_enable)               //don't send vad to none rastel client
          continue;
       Send_Complex_VAD_Event_To_Participant(ConfCont, src_user_name);
       }
::LeaveCriticalSection(&cp_cs);
}
//------------------------------------------------------------------------------
void __fastcall TConferenceWin::Distribute_OWN_Vad_Event()
{
::EnterCriticalSection(&cp_cs);
  deque<TConfCont*> dst;
__get_copy_CP_UNSAFE(dst);
  while(!dst.empty())
       {
       TConfCont* ConfCont = dst.front();
       dst.pop_front();
       if(!ConfCont->vad_enable)               //don't send vad to none rastel client
          continue;
       Send_Ordinary_VAD_Event_To_Participant(ConfCont);
       }
::LeaveCriticalSection(&cp_cs);
}
//------------------------------------------------------------------------------
void __fastcall TConferenceWin::Send_Ordinary_VAD_Event_To_Participant(TConfCont* ConfCont)
{
if(ConfCont->lt == Lt_Out)
  {
  TMediaSession* ms = MainFormSLS->Sip->sss->GetMsOut_by_Callid(ConfCont->callid);
  if(ms)
    {
    TUdpChannel* uc = ms->getRtcpAudioChannel();
    if(uc)
       uc->Send_VAD_EVENT();
    }
  }
else if(ConfCont->lt == Lt_In)
  {
  TMediaSession* ms = MainFormSLS->Sip->sss->GetMsIn_by_Callid(ConfCont->callid);
  if(ms)
    {
    TUdpChannel* uc = ms->getRtcpAudioChannel();
    if(uc)
       uc->Send_VAD_EVENT();
    }
  }
}
//------------------------------------------------------------------------------
void __fastcall TConferenceWin::Send_Complex_VAD_Event_To_Participant(TConfCont* ConfCont, const string& src_user_name)
{
if(ConfCont->lt == Lt_Out)
  {
  TMediaSession* ms = MainFormSLS->Sip->sss->GetMsOut_by_Callid(ConfCont->callid);
  if(ms)
    {
    TUdpChannel* uc = ms->getRtcpAudioChannel();
    if(uc)
       uc->Send_Complex_VAD_EVENT(src_user_name);
    }
  }
else if(ConfCont->lt == Lt_In)
  {
  TMediaSession* ms = MainFormSLS->Sip->sss->GetMsIn_by_Callid(ConfCont->callid);
  if(ms)
    {
    TUdpChannel* uc = ms->getRtcpAudioChannel();
    if(uc)
       uc->Send_Complex_VAD_EVENT(src_user_name);
    }
  }
}
//------------------------------------------------------------------------------
void __fastcall TConferenceWin::ParticipantsLayout()
{
::EnterCriticalSection(&cp_cs);
  deque<TConfCont*> dest;
__get_copy_CP_UNSAFE(dest);
  switch(dest.size()){
        case 1: _layout_1(dest); break;
        case 2: _layout_2(dest); break;
        case 3: _layout_3(dest); break;
        case 4: _layout_4(dest); break;
        }
::LeaveCriticalSection(&cp_cs);
}
//--------------------------------------------------------------------------
void __fastcall TConferenceWin::ChangeWinLayout_OnResize()
{
SetConfWinSize();
Btn_Layout(BS_NDEF);
ParticipantsLayout();
}
//--------------------------------------------------------------------------
void __fastcall TConferenceWin::_layout_1(deque<TConfCont*>& dst)
{
int width  = Width/3;
TConfCont* ConfCont = dst.front();
dst.pop_front();
if(ConfCont)
   _set_on_top(ConfCont, width);
}
//--------------------------------------------------------------------------
void __fastcall TConferenceWin::_layout_2(deque<TConfCont*>& dst)
{
_layout_2_X(dst, LAYOUT_TOP);  //1-й ряд из двух элементов
}
//-----------------------------------------------------------------------------
void __fastcall TConferenceWin::_layout_3(deque<TConfCont*>& dst)
{
int next_top = 0;
int width  = Width/3;
TConfCont* ConfCont = _get_conference_creator(dst);
if(ConfCont)
   next_top = _set_on_top(ConfCont, width);
else
   {
   ConfCont = _get_first_participant(dst);
   if(ConfCont)
      next_top = _set_on_top(ConfCont, width);
   }
next_top += VERT_INTERVAL;
_layout_2_X(dst, next_top);   //2-й ряд из двух элементов
}
//--------------------------------------------------------------------------
void __fastcall TConferenceWin::_layout_4(deque<TConfCont*>& dst)
{
int next_top = _layout_2_X(dst, LAYOUT_TOP);  //1-й ряд из двух элементов
_layout_2_X(dst, next_top + VERT_INTERVAL);   //2-й ряд из двух элементов
}
//--------------------------------------------------------------------------
int __fastcall TConferenceWin::_set_on_top(TConfCont* ConfCont, int width)
{
int rv = 0;
if(ConfCont->conf_panel)
  {
  TConfPanel* conf_panel = ConfCont->conf_panel;
  conf_panel->Top        = LAYOUT_TOP;
  conf_panel->Left       = Width/2 - conf_panel->Width/2;
 _label_layout(ConfCont,conf_panel);
  rv = conf_panel->Top + conf_panel->Height;
  }
 return rv;
}
//--------------------------------------------------------------------------
//--- Display  row  from two elements --------------------------------------
//--------------------------------------------------------------------------
int __fastcall TConferenceWin::_layout_2_X(deque<TConfCont*>& dst, int TOP)
{
int rv = 0;
int quarter_width = Width/4;
int i = 0;
while(!dst.empty())
     {
     TConfCont* ConfCont = dst.front();
     dst.pop_front();
     if(ConfCont->conf_panel)
       {
       TConfPanel* conf_panel  = ConfCont->conf_panel;
       conf_panel->Top         = TOP;
       if(!i)
         {
         conf_panel->Left     = quarter_width - conf_panel->Width/2;  //Left panel
        _label_layout(ConfCont,conf_panel);
         }
       else
         {
         conf_panel->Left     = Width - quarter_width - conf_panel->Width/2 - 20;  //Right panel
        _label_layout(ConfCont,conf_panel);
         rv = conf_panel->Top + conf_panel->Height;
         break;
         }
       }
     i++;
     }
return rv;
}
//------------------------------------------------------------------------------
void __fastcall TConferenceWin::_label_layout(TConfCont* ConfCont, TConfPanel* conf_panel)
{
TLabel* lbl  = ConfCont->lbl;
TLabel* lbl1 = ConfCont->lbl1;
if(lbl)
  {
  AnsiString S = ConfCont->full_name.c_str();
  int text_width = lbl->Canvas->TextWidth(S);
  if(text_width < conf_panel->Width)
    {
    lbl->Left = conf_panel->Left +  conf_panel->Width/2  - lbl->Width/2;
    lbl->Caption = S;
    lbl->Top     = conf_panel->Top + conf_panel->Height + 5;
    }
  else if(text_width > conf_panel->Width)
    {
    if(lbl1)
      {
      string s,s0,s1;
      s = ConfCont->full_name;
      int len = s.length();
      int st = s.rfind(WS);
      if(st != -1)
        {
        s0 = s.substr(0,st);
        st++;   //пропустить найденый пробел
        if(st < len)
          s1 = s.substr(st);
        S = s0.c_str();
        lbl->Caption = S;
        int text_width_1 = lbl->Canvas->TextWidth(S);
        S = s1.c_str();
        lbl1->Caption = S;
        int text_width_2 = lbl1->Canvas->TextWidth(S);
        lbl->Top   = conf_panel->Top + conf_panel->Height + 2;
        lbl1->Top  = lbl->Top + lbl->Height;

        if(text_width_1 > text_width_2)
          if(text_width_1 <= conf_panel->Width)
            {
            lbl->Left = conf_panel->Left +  conf_panel->Width/2  - lbl->Width/2;
            lbl1->Left = lbl->Left;
            if(ConfCont->ctr_disc_img)
             if(conf_panel)
               {
               ConfCont->ctr_disc_img->Top  = lbl->Top;
               ConfCont->ctr_disc_img->Left = conf_panel->Left - ConfCont->ctr_disc_img->Width;
               }
            return;
            }
        lbl->Left  = conf_panel->Left;
        lbl1->Left = lbl->Left;
        if(ConfCont->ctr_disc_img)
          {
          ConfCont->ctr_disc_img->Top  = lbl->Top;
          ConfCont->ctr_disc_img->Left = conf_panel->Left - ConfCont->ctr_disc_img->Width;
          }
        return;
        }
      }
    }
  else
    {
    lbl->Left    = conf_panel->Left;
    lbl->Caption = S;
    lbl->Top     = conf_panel->Top + conf_panel->Height + 5;
    }
  if(ConfCont->ctr_disc_img)
    {
    ConfCont->ctr_disc_img->Top  = lbl->Top;
    ConfCont->ctr_disc_img->Left = conf_panel->Left - ConfCont->ctr_disc_img->Width;
    }
  } //if(lbl)
}
//------------------------------------------------------------------------------
TConfCont* __fastcall TConferenceWin::_get_conference_creator(deque<TConfCont*>& dst)
{
TConfCont* Conf_Cont = NULL;
if(!dst.empty())
  {
  deque<TConfCont*>::iterator it = dst.begin();
  while(it != dst.end())
       {
       TConfCont* ConfCont = *it;
       if(ConfCont)
         if(ConfCont->conference_creator)
           {
           Conf_Cont = ConfCont;
           dst.erase(it);
           break;
           }
       it++;
       }
  }
return Conf_Cont;
}
//--------------------------------------------------------------------------
TConfCont* __fastcall TConferenceWin::_get_first_participant(deque<TConfCont*>& dst)
{
TConfCont* Conf_Cont = NULL;
if(!dst.empty())
  {
  Conf_Cont = dst.front();
  dst.pop_front();
  }
return Conf_Cont;
}
//----------------------------------------------------------------------------------
//--- Set Tag of the ConferenceWin and conference_participant and conference creator
//--- to TWaveInputThread (Uc->mic) (mainly for VAD)
//----------------------------------------------------------------------------------
void __fastcall TConferenceWin::ASSIGN_CALL_TAG(TConfExchBlock* buf)
{
if(buf->uatt == SipUAThreadType_UAS)
  {
  TMediaSession* ms = MainFormSLS->Sip->sss->GetMsIn_by_Callid(buf->callid);
  if(ms)
    _set_conference_parameters(ms,buf);
  }
else if(buf->uatt == SipUAThreadType_UAC)
  {
  TMediaSession* ms = MainFormSLS->Sip->sss->GetMsOut_by_Callid(buf->callid);
  if(ms)
    _set_conference_parameters(ms,buf);
  }
}
//--------------------------------------------------------------------------
void  __fastcall TConferenceWin::_set_conference_parameters(TMediaSession* ms,TConfExchBlock* buf)
{
Tag = ms->getCallTag();
if(buf->INFO_msg)
  {
  TUdpChannel* uc = ms->getSoundChannel();
  if(uc)
    if(uc->mic)
       uc->mic->ch_conference_participant = true;
  }
}  
//--------------------------------------------------------------------------
bool  __fastcall TConferenceWin::ins_to_CP(TConfCont* ConfCont)
{
bool rv = false;
::EnterCriticalSection(&cp_cs);
  if(!ConfCont->user_name.empty())
    {
    TConfParticipants::iterator it = CP.find(ConfCont->user_name);
    if(it == CP.end())
      {
      CP.insert(TConfParticipants::value_type(ConfCont->user_name, ConfCont));
      rv = true;
      }
    else //Exists already
      {
      (*it).second->cc_call_state = ConfCont->cc_call_state;  //update call_state
      }
    }
::LeaveCriticalSection(&cp_cs);
return rv;
}
//------------------------------------------------------------------------------
void  __fastcall TConferenceWin::ans_to_CP(const string& user_name)
{
::EnterCriticalSection(&cp_cs);
  TConfParticipants::iterator it = CP.find(user_name);
  if(it != CP.end())
    (*it).second->cc_call_state = 1; //Answered
::LeaveCriticalSection(&cp_cs);
}
//------------------------------------------------------------------------------
void  __fastcall TConferenceWin::del_from_CP(const string& user_name)
{
::EnterCriticalSection(&cp_cs);
  TConfParticipants::iterator it = CP.find(user_name);
  if(it != CP.end())
    {
    TConfCont* ConfCont = (*it).second;
    if(ConfCont)
       INS_TO_ERASE_Q(ConfCont);
    CP.erase(it);
    }
::LeaveCriticalSection(&cp_cs);
}
//------------------------------------------------------------------------------
int __fastcall TConferenceWin::get_size_CP()
{
int rv;
::EnterCriticalSection(&cp_cs);
  rv = CP.size();
::LeaveCriticalSection(&cp_cs);
return rv;
}
//------------------------------------------------------------------------------
void __fastcall TConferenceWin::activate_VAD_CP(const string& user_name )
{
::EnterCriticalSection(&cp_cs);
  TConfParticipants::iterator it = CP.find(user_name);
  if(it != CP.end())
     (*it).second->vad_enable = true;
::LeaveCriticalSection(&cp_cs);
}
//------------------------------------------------------------------------------
bool __fastcall TConferenceWin::_flash_disc_img_CP(int call_tag)
{
bool rv = false;
::EnterCriticalSection(&cp_cs);
  TConfParticipants::iterator it = CP.begin();
  while(it != CP.end())
       {
       if((*it).second->call_panel_tag == call_tag)
         if((*it).second->ctr_disc_img)
            {
           (*it).second->ctr_disc_img->Visible   = true;
           (*it).second->ctr_disc_img->flash_end = (*it).second->ctr_disc_img->flash_end.CurrentDateTime() + TDateTime(0,0,1,0);
            rv = true;
            break;
            }
       it++;
       }
::LeaveCriticalSection(&cp_cs);
return rv;
}
//------------------------------------------------------------------------------
void __fastcall TConferenceWin::check_flashing_local_disc_imgs(bool& rv, const TDateTime& dt)
{
::EnterCriticalSection(&cp_cs);
  TConfParticipants::iterator it = CP.begin();
  while(it != CP.end())
       {
       if((*it).second->ctr_disc_img)
         if((*it).second->ctr_disc_img->Visible)
           {
           if((*it).second->ctr_disc_img->flash_end < dt)
             {
             if(!check_focus_ctr_disc_img((*it).second->ctr_disc_img))
                rv = false; //Do not suspend TConfBtnStateThread.
             else
                (*it).second->ctr_disc_img->Hide();   //Flash off active disc buttom
             }
           else
             rv = false;  //Do not suspend TConfBtnStateThread. Flashing all active disc buttons
           }
         else  //if((*it).second->ctr_disc_img->Visible)
           {
           if(!check_focus_ctr_disc_img((*it).second->ctr_disc_img))
             {
             (*it).second->ctr_disc_img->flash_end = (*it).second->ctr_disc_img->flash_end.CurrentDateTime() + TDateTime(0,0,1,0);
             (*it).second->ctr_disc_img->Visible = true;
             rv = false;
             }
           }
       it++;
       }
::LeaveCriticalSection(&cp_cs);
}
//------------------------------------------------------------------------------
void __fastcall TConferenceWin::check_outgoing_no_answered_participants(bool& rv, const TDateTime& dt)
{
::EnterCriticalSection(&cp_cs);
  TConfParticipants::iterator it = CP.begin();
  while(it != CP.end())
       {
       if(CONFERENCE_CREATOR)
         if((*it).second->lt != Lt_Out)     //  (*it).second - TConfCont
           {
           it++;
           continue;
           }
       if((*it).second->cc_call_state == 0) //no yet answered
         {
         if((*it).second->lbl)
           {
           if((*it).second->dt_flash < dt)  //Interval expires
             {
             if((*it).second->lbl->Visible)
               {
               (*it).second->lbl->Visible = false;
               if((*it).second->lbl1)
                  (*it).second->lbl1->Visible = false;
               }
             else
               {
               (*it).second->lbl->Visible = true;
               if((*it).second->lbl1)
                  (*it).second->lbl1->Visible = true;
               }
             (*it).second->dt_flash = (*it).second->dt_flash.CurrentDateTime() + TDateTime(0,0,1,0);
             }
           }   //if((*it).second->lbl)
         rv = false;          //Do not suspend TConfBtnStateThread
         }     //if((*it).second->call_state == 0)
       else  //answered. Чтобы после ответа и остановки потока надпись не осталась невидимой.
         {
         if((*it).second->lbl)
           if(!(*it).second->lbl->Visible)
             {
             (*it).second->lbl->Visible = true;
             if((*it).second->lbl1)
               (*it).second->lbl1->Visible = true;
             }
         }
       it++;
       }
::LeaveCriticalSection(&cp_cs);
}
//------------------------------------------------------------------------------
bool __fastcall TConferenceWin::check_focus_ctr_disc_img(TBtnImage* img)
{
bool rv = true;
TPoint pt;
if(::GetCursorPos(&pt))           //!!! Do not use Mouse->CursorPos.x. Error 5 - Отказано в доступе к структуре Mouse при старте другой программы в от имени администратора
  {
  if(pt.x > img->ClientOrigin.x)
    if(pt.y > img->ClientOrigin.y)
      if(pt.x < (img->ClientOrigin.x + img->Width))
        if(pt.y < (img->ClientOrigin.y + img->Height))
           rv = false;  //Cursore inside of img
  }
return rv;
}
//------------------------------------------------------------------------------
//--- This function MUST BE used inside CriticalSection(&cp_cs) ONLY!!! --------
//------------------------------------------------------------------------------
void __fastcall TConferenceWin::__get_copy_CP_UNSAFE(deque<TConfCont*>& dest)
{
TConfParticipants::iterator it = CP.begin();
while(it != CP.end())
     {
     TConfCont* ConfCont = (*it++).second;
     dest.push_back(ConfCont);
     }
}
//------------------------------------------------------------------------------
void __fastcall TConferenceWin::get_copy_CP(deque<TConfCont*>& dest)
{
::EnterCriticalSection(&cp_cs);
  __get_copy_CP_UNSAFE(dest);
::LeaveCriticalSection(&cp_cs);
}
//------------------------------------------------------------------------------
void __fastcall TConferenceWin::set_imgs_visible()
{
conf_disc_img->Visible = true;
conf_mic_img->Visible  = true;
conf_chat_img->Visible = true;
if(CONFERENCE_CREATOR)
  {
  conf_screen_img->Visible = true;
  conf_add_img->Visible    = true;
  }
}
//---------------------------------------------------------------------------
void __fastcall TConferenceWin::set_imgs_invisible()
{
conf_disc_img->Visible   = false;
conf_mic_img->Visible    = false;
conf_screen_img->Visible = false;
conf_add_img->Visible    = false;
conf_chat_img->Visible   = false;
}
//---------------------------------------------------------------------------
void __fastcall TConferenceWin::conf_disc_imgMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
TImage* img = (TImage*)Sender;
if((X > 0) && (X < img->Width))
  if((Y > 0) && (Y < img->Height))
    {
    if(Tag)
      {
      if(!CONFERENCE_CREATOR)   //ConferenceWin открыт на пассивном участнике конференции (Disconnect отправляется только создателю конференции)
        {
        TCall_Panel* Panel = MainFormSLS->get_Call_Panel_By_Tag(Tag);
        if(Panel)
          {
          if(Panel->get_conf_participant())
            {
            if(Panel->get_leg_type() == Lt_In)
              {
              TMediaSession* ms = MainFormSLS->Sip->sss->GetMs_by_Call_Tag(Tag);
              Panel->disconnect_incoming_call(ms,false); //check if(ms) inside of func ; false means that  disconnect_incoming_call() initialized not from rcvd Bye fron parallel phone
              }
            else if(Panel->get_leg_type() == Lt_Out)
              {
              TMediaSession* ms = MainFormSLS->Sip->sss->GetMs_by_Call_Tag(Tag);
              Panel->disconnect_outgoing_call(ms,false);  //check if(ms) inside of func ; false means that  disconnect_incoming_call() initialized not from rcvd Bye fron parallel phone
              }
            }
          } //if(Panel)
        }
      else
        {    //ConferenceWin открыт на создателе конференции (Disconnect отправляется всем участникам конференции)
        deque<TConfCont*> dest;
        get_copy_CP(dest);
        while(!dest.empty())
             {
             TConfCont* ConfCont = dest.front();
             dest.pop_front();
             if(ConfCont)
               {
               TCall_Panel* Panel = MainFormSLS->get_Call_Panel_By_Tag(ConfCont->call_panel_tag);
               if(Panel)
                 {
                 if(Panel->get_conf_participant())
                   {
                   if(Panel->get_leg_type() == Lt_In)
                     {
                     TMediaSession* ms = MainFormSLS->Sip->sss->GetMs_by_Call_Tag(Panel->Tag);
                     Panel->disconnect_incoming_call(ms,false); //check if(ms) inside of func ; false means that  disconnect_incoming_call() initialized not from rcvd Bye fron parallel phone
                     }
                   else if(Panel->get_leg_type() == Lt_Out)
                     {
                     TMediaSession* ms = MainFormSLS->Sip->sss->GetMs_by_Call_Tag(Panel->Tag);
                     Panel->disconnect_outgoing_call(ms,false);  //check if(ms) inside of func ; false means that  disconnect_incoming_call() initialized not from rcvd Bye fron parallel phone
                     }
                   }

                 }
               }
             } // while(!dest.empty())
        } // if(CONFERENCE_CREATOR)
      } //if(Tag)

    BtnImgs->Draw(conf_screen_img->Canvas,0,0,0,true); conf_screen_img->Refresh();
    DEACTIVATE_CONF_WINDOW();
    }
}
//---------------------------------------------------------------------------
void __fastcall TConferenceWin::conf_screen_imgMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
TImage* img = (TImage*)Sender;
if((X > 0) && (X < img->Width))
  if((Y > 0) && (Y < img->Height))
    {
    TDateTime dt = dt.CurrentDateTime();
    if((dt - dt_activate_screen_sharing) < TDateTime(0,0,2,0))
       return;
    dt_activate_screen_sharing = dt;

    if(screen_sharing_active)
      {
      screen_sharing_active = false;
      BtnImgs->Draw(conf_screen_img->Canvas,0,0,0,true); conf_screen_img->Refresh();
      }
    else
      {
      screen_sharing_active = true;
      BtnImgs->Draw(conf_screen_img->Canvas,0,0,1,true); conf_screen_img->Refresh();
      }


    if(Tag)
      {
      TCall_Panel* Panel = MainFormSLS->get_Call_Panel_By_Tag(Tag);
      if(Panel)
        if(Panel->get_conf_participant())
           Panel->screen_sharing_action();
      }
    }
}
//---------------------------------------------------------------------------
void __fastcall TConferenceWin::_set_default_size()
{
Top    = Default_Top;
Left   = Default_Left;
Height = Default_Height;
Width  = Default_Width;
Default_Size = true;
}
//--------------------------------------------------------------------------
void __fastcall TConferenceWin::conf_mic_img_MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
TBtnImage* btn = (TBtnImage*)Sender;
if((X > 0) && (X < btn->Width))
  if((Y > 0) && (Y < btn->Height))
    {
    switch(btn->get_btn_state()){
          case 1:{
                  MIC_SWITCH_OFF(); //Active -> Switch_OFF
                  if(Tag)
                    if(!CONFERENCE_CREATOR)   //ConferenceWin открыт на пассивном участнике конференции (Disconnect отправляется только создателю конференции)
                       Mute_Passive_Conference_Participant();
                    else
                       Mute_Conference_Creator();  //Switch off microfons at all passive participants
                  break;
                  }
          case 4: {
                  MIC_SWITCH_ON(); //Swith_OFF -> Active
                  if(Tag)
                    if(!CONFERENCE_CREATOR)   //ConferenceWin открыт на пассивном участнике конференции (Disconnect отправляется только создателю конференции)
                      Mute_OFF_Passive_Conference_Participant();
                    else
                      Mute_OFF_Conference_Creator();  //Switch on microfons at all passive participants
                  break;
                  }
          }  // switch(btn->get_btn_state())
    } //if((X > 0) && (X < btn->Width))
           // if((Y > 0) && (Y < btn->Height))
}
//---------------------------------------------------------------------------
void __fastcall TConferenceWin::MIC_SWITCH_ON()
{
conf_mic_img->set_btn_state(1); //Active (Switch_ON);
conf_mic_img->Hint = "Выключить микрофон";
mic_switched_on    = true;
conf_mic_img->clear();
BtnImgs->Draw(conf_mic_img->Canvas,0,0,MIC_CNVS_ACTIVE,true);
}
//---------------------------------------------------------------------------
void __fastcall TConferenceWin::MIC_SWITCH_OFF()
{
conf_mic_img->set_btn_state(4); // Switch_OFF
conf_mic_img->Hint = "Включить микрофон";
mic_switched_on    = false;
conf_mic_img->clear();
BtnImgs->Draw(conf_mic_img->Canvas,0,0,MIC_CNVS_SW_OFF,true);
}
//---------------------------------------------------------------------------
void __fastcall TConferenceWin::Mute_Conference_Creator()
{
TCall_Panel* Panel_Creator = MainFormSLS->get_Call_Panel_By_Tag(Tag);
if(Panel_Creator)
  if(Panel_Creator->get_conf_participant())
    for(int i = 0; i < MainFormSLS->ControlCount; i++)
       {
       TCall_Panel* Panel = dynamic_cast<TCall_Panel*>(MainFormSLS->Controls[i]);
       if(Panel)
          if(Panel->get_conf_creator() == Tag) //Mute all Panels belongs to this conference (Tag)
            {
            TMediaSession* ms = MainFormSLS->Sip->sss->GetMs_by_Call_Tag(Panel->Tag);
            if(ms)
              {
              TUdpChannel* uc = ms->getSoundChannel();
              if(uc)
               if(uc->mic)
                 {
                 MainFormSLS->ImageList3->Draw(Panel->mic_img->Canvas,0,0,5,true); Panel->mic_img->Refresh();
                 Panel->mic_img->Hint = "Включить микрофон";
                 uc->mic->MS   =  MicrophoneState_Passive;
                 uc->mic->setMute(true);
                 TEventLogThread* elt = MainFormSLS->ofs->elt;
                 if(elt)
                    elt->FputEvt("\nmic switch off");
                 }
              }
            }
       }//  if(Panel->get_conf_participant())
   
}
//---------------------------------------------------------------------------
void __fastcall TConferenceWin::Mute_OFF_Conference_Creator()
{
TCall_Panel* Panel_Creator = MainFormSLS->get_Call_Panel_By_Tag(Tag);
if(Panel_Creator)
  if(Panel_Creator->get_conf_participant())
    for(int i = 0; i < MainFormSLS->ControlCount; i++)
       {
       TCall_Panel* Panel = dynamic_cast<TCall_Panel*>(MainFormSLS->Controls[i]);
       if(Panel)
         if(Panel->get_conf_creator() == Tag)  //Switch on all Panels belongs to this conference (Tag)
           {
           TMediaSession* ms = MainFormSLS->Sip->sss->GetMs_by_Call_Tag(Panel->Tag);
           if(ms)
             {
             TUdpChannel* uc = ms->getSoundChannel();
             if(uc)
              if(uc->mic)
                {
                TEventLogThread* elt = MainFormSLS->ofs->elt;
                if(elt)
                   elt->FputEvt("\nmic switch on");
                Panel->mic_img->Picture->Bitmap = MainFormSLS->mic_img_static->Picture->Bitmap; Panel->mic_img->Refresh();
                Panel->mic_img->Hint = "Выключить микрофон";
                uc->mic->MS = MicrophoneState_Active;
                uc->mic->setMute(false);
                if(uc->mic->WIS == WaveInputState_ACTIVE)
                  if(uc->mic->Suspended)
                     uc->mic->Resume_Thread();
                }
             }
           }
      } //  for(int i = 0; i < MainFormSLS->ControlCount; i++)
}
//---------------------------------------------------------------------------
void __fastcall TConferenceWin::Mute_Passive_Conference_Participant()
{
TCall_Panel* Panel = MainFormSLS->get_Call_Panel_By_Tag(Tag);
if(Panel)
  if(Panel->get_conf_participant())
    {
    TMediaSession* ms = MainFormSLS->Sip->sss->GetMs_by_Call_Tag(Tag);
    if(ms)
      {
      TUdpChannel* uc = ms->getSoundChannel();
      if(uc)
        if(uc->mic)
          {
          MainFormSLS->ImageList3->Draw(Panel->mic_img->Canvas,0,0,5,true); Panel->mic_img->Refresh();
          Panel->mic_img->Hint = "Включить микрофон";
          uc->mic->MS   =  MicrophoneState_Passive;
          uc->mic->setMute(true);
          TEventLogThread* elt = MainFormSLS->ofs->elt;
          if(elt)
             elt->FputEvt("\nmic switch off");
          }
      }
    }
}
//---------------------------------------------------------------------------
void __fastcall TConferenceWin::Mute_OFF_Passive_Conference_Participant()
{
TCall_Panel* Panel = MainFormSLS->get_Call_Panel_By_Tag(Tag);
if(Panel)
  if(Panel->get_conf_participant())
    {
    TMediaSession* ms = MainFormSLS->Sip->sss->GetMs_by_Call_Tag(Tag);
    if(ms)
      {
      TUdpChannel* uc = ms->getSoundChannel();
      if(uc)
        if(uc->mic)
          {
          TEventLogThread* elt = MainFormSLS->ofs->elt;
          if(elt)
            elt->FputEvt("\nmic switch on");
          Panel->mic_img->Picture->Bitmap = MainFormSLS->mic_img_static->Picture->Bitmap; Panel->mic_img->Refresh();
          Panel->mic_img->Hint = "Выключить микрофон";
          uc->mic->MS = MicrophoneState_Active;
          uc->mic->setMute(false);
          if(uc->mic->WIS == WaveInputState_ACTIVE)
            if(uc->mic->Suspended)
               uc->mic->Resume_Thread();
          }
      }
    }
}
//---------------------------------------------------------------------------
void __fastcall TConferenceWin::conf_add_imgMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
TImage* img = (TImage*)Sender;
if((X > 0) && (X < img->Width))
  if((Y > 0) && (Y < img->Height))
    {
    if(Default_Size)
      {
      Height -= 200;
      Top    += 200;
      Default_Size = false;
      Btn_Layout(BS_NDEF);
      if(!MainFormSLS->CC_Panel->Visible)
        {
        if(Tag)
          {
          TCall_Panel* Panel = MainFormSLS->get_Call_Panel_By_Tag(Tag);
          if(Panel)
            {
            MainFormSLS->GCS.CC_PANEL_TYPE     = CC_PANEL_TYPE__NDEF;
            MainFormSLS->Make_All_Call_Panels_INVISIBLE();
            MainFormSLS->CC_Panel->Left        = 0;//MainFormSLS->RIGHT_PANEL->Left;
            MainFormSLS->CC_DrawGrid->RowCount = Panel->get_ccl_q_size();
            MainFormSLS->CC_DrawGrid->Tag      = Panel->Tag;
            MainFormSLS->CC_Panel->Top         = 0; // MainFormSLS->ClientOrigin.y; //Panel->Top + Height;
            MainFormSLS->CC_Panel->Height      = 200;
            MainFormSLS->setAddToConfBtnState(BtnState_ACTIVE);
            MainFormSLS->CC_Panel->Show();
            }
          }
        }
      }
    else
      {
     _restore(); //Restore default size
      ChangeWinLayout_OnResize();
      }
    }
}
//---------------------------------------------------------------------------
void __fastcall TConferenceWin::_restore()
{
_set_default_size();
Btn_Layout(BS_NDEF);
MainFormSLS->CC_Panel->Hide();
MainFormSLS->Make_All_Call_Panels_VISIBLE();
}
//--------------------------------------------------------------------------
void __fastcall TConferenceWin::delete_CONF_BST()
{
if(CONF_BST)
  {
  TConfBtnStateThread* bst = CONF_BST;
  CONF_BST = NULL;
  bst->Terminate();
  bst->Resume();
  bst->WaitFor();
  delete bst;
  }
}
//-----------------------------------------------------------------------------
void __fastcall TConferenceWin::delete_CONF_FLASH()
{
if(CONF_FLASH)
  {
  TFlashingStateThread* fst = CONF_FLASH;
  CONF_FLASH = NULL;
  fst->Terminate();
  fst->Resume();
  fst->WaitFor();
  delete fst;
  }
}
//-----------------------------------------------------------------------------
void __fastcall TConferenceWin::create_CONF_BST()
{
CONF_BST = new TConfBtnStateThread(true,this);
}
//----------------------------------------------------------------------------
void __fastcall TConferenceWin::create_CONF_FLASH()
{
CONF_FLASH = new TFlashingStateThread(true,this);
if(CONF_FLASH)
   CONF_FLASH->Resume();
}
//----------------------------------------------------------------------------
void __fastcall TConfBtnStateThread::Execute()
{
while(!Terminated)
     {
     Synchronize(visible_proc);
     ::Sleep(40);
     }
}
//----------------------------------------------------------------------------
void __fastcall TFlashingStateThread::Execute()
{
while(!Terminated)
     {
     Synchronize(flashing_proc);
     Synchronize(win->CHECK_ERASE_Q);
     ::Sleep(100);
     }
}
//----------------------------------------------------------------------------
void __fastcall TConfBtnStateThread::visible_proc()
{
bool req_suspending = false;
switch(BTNS_STATE){
       case BS_MOUSEMOVED:{
            TDateTime dt = dt.CurrentDateTime();
            if(dt > win->dt_last_mouse_move)
               BTNS_STATE = BS_DOWN;  //Start of shift down btn imgs
            break;
            }
       case BS_DOWN:
            if(!win->block_shift)
              ::PostMessage(win->Handle, CONFERENCE_PLAIN_MSG, WM_CONFERENCE_PLAIN_MSG_WPARAM__SHIFT_BTNS_DOWN, WM_CONFERENCE_PLAIN_MSG_LPARAM__NDEF);
            break;
       case BS_RAISED:
          ::PostMessage(win->Handle, CONFERENCE_PLAIN_MSG, WM_CONFERENCE_PLAIN_MSG_WPARAM__SHIFT_BTNS_UP, WM_CONFERENCE_PLAIN_MSG_LPARAM__NDEF);
            break;
       }

if(win)
  {
  TDateTime dt = dt.CurrentDateTime();
  win->check_outgoing_no_answered_participants(req_suspending, dt);  //flashing no answered outgouing participants
  if(win->Get_CONFERENCE_CREATOR())
     win->check_flashing_local_disc_imgs(req_suspending, dt);
  }
if(req_suspending)
   Suspend();
}
//-----------------------------------------------------------------------------
void __fastcall TFlashingStateThread::flashing_proc()
{
win->detect_flashing_end();
}
//-----------------------------------------------------------------------------
void __fastcall TConferenceWin::detect_flashing_end()
{
::EnterCriticalSection(&cp_cs);
  TConfParticipants::iterator it = CP.begin();
  while(it != CP.end())
       {
       if((*it).second->conf_panel)
         if((*it).second->conf_panel->lights)
           {
           if((*it).second->conf_panel->new_vad_event)
              (*it).second->conf_panel->new_vad_event = false;
           else
              {
               //погасить подсвеченный аватар
               bool default_avatar = true;
               TConfCont* ConfCont = (*it).second;

Graphics::TBitmap *pBitmap = new Graphics::TBitmap();
if(pBitmap)
  {
   if(default_avatar)
     { //Load default_avatar
     pBitmap->Width  = 225;
     pBitmap->Height = 215;
     ImageList1->Draw(pBitmap->Canvas,0,0,0,true);
     }
   else
     {  //Load contact avatar from file
     /*
     pBitmap->Width  = 225;
     pBitmap->Height = 215;
     pBitmap->LoadFromFile("C:\\test\\Avt_2.bmp");
     ImageList1->Draw(pBitmap->Canvas,0,0,1,true);
    // Win->ImageList1->Draw(pBitmap->Canvas,0,0,1,true);
     */
     }

   TRect Rect(0, 0, ConfCont->conf_panel->img->Width, ConfCont->conf_panel->img->Height);
   ConfCont->conf_panel->img->Canvas->StretchDraw(Rect, pBitmap);


   ConfCont->conf_panel->lights = false;
   delete pBitmap;
  }  //if(pBitmap)

              }
           }
       it++;
       }
::LeaveCriticalSection(&cp_cs);
}
//----------------------------------------------------------------------------
void __fastcall TConferenceWin::FormMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
if(!conf_disc_img->Visible)
   set_imgs_visible();
block_shift = false;
if(CONF_BST)
  {
__update_last_mouse_move();
  switch(CONF_BST->BTNS_STATE){
        case BS_CLOSED:
             Btn_Layout(BS_CLOSED);
             CONF_BST->BTNS_STATE = BS_RAISED;
             break;
        case BS_RAISED:
             break;
        case BS_DOWN:   //Imgs в процессе движения вниз -> сразу восстановить на исходную позицию
             CONF_BST->BTNS_STATE = BS_MOUSEMOVED;   //!!! Именно в этом порядке - сначала CONF_BST->BTNS_STATE = BS_MOUSEMOVED, затем PostMessage()
           ::PostMessage(Handle, CONFERENCE_PLAIN_MSG, WM_CONFERENCE_PLAIN_MSG_WPARAM__SHIFT_BTNS_ON_TOP, WM_CONFERENCE_PLAIN_MSG_LPARAM__NDEF);
             break;
        default: CONF_BST->BTNS_STATE = BS_MOUSEMOVED;
        }
  if(CONF_BST->Suspended)
     CONF_BST->Resume();
  }
}
//---------------------------------------------------------------------------
void __fastcall TConferenceWin::__update_last_mouse_move()
{
dt_last_mouse_move = dt_last_mouse_move.CurrentDateTime() + TDateTime(0,0,5,0); //Sec
}
//----------------------------------------------------------------------------
void __fastcall TConferenceWin::FormShow(TObject *Sender)
{
set_imgs_invisible();
delete_CONF_BST();
delete_CONF_FLASH();
create_CONF_BST();
create_CONF_FLASH();
}
//---------------------------------------------------------------------------
void __fastcall TConferenceWin::FormCloseQuery(TObject *Sender,
      bool &CanClose)
{
delete_CONF_BST();
delete_CONF_FLASH();
MainFormSLS->set_IM_to_conf_participants(false);
}
//---------------------------------------------------------------------------
void __fastcall TConferenceWin::INS_TO_ERASE_Q(TConfCont* ConfCont)
{
::EnterCriticalSection(&erase_cs);
  ConfCont->del_time = ConfCont->del_time.CurrentDateTime() + TDateTime(0,0,10,0); //10 sec
  if(ConfCont->lbl)
     ConfCont->lbl->Hide();
  if(ConfCont->lbl1)
     ConfCont->lbl1->Hide();
  if(ConfCont->conf_panel)
     ConfCont->conf_panel->Hide();
  if(ConfCont->ctr_disc_img)
     ConfCont->ctr_disc_img->Hide();
  ERASE_Q.push(ConfCont);
::LeaveCriticalSection(&erase_cs);
}
//---------------------------------------------------------------------------
void __fastcall TConferenceWin::CHECK_ERASE_Q()
{
::EnterCriticalSection(&erase_cs);
  while(!ERASE_Q.empty())
       {
       TConfCont* ConfCont = ERASE_Q.front();
       if(ConfCont)
         {
         if(ConfCont->del_time > ConfCont->del_time.CurrentDateTime())
            break;     //timer from first element not yet expires
         ERASE_Q.pop();
         delete ConfCont;
         }
       }
::LeaveCriticalSection(&erase_cs);
}
//---------------------------------------------------------------------------
void __fastcall TConferenceWin::conf_chat_imgMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
TImage* img = (TImage*)Sender;
if((X > 0) && (X < img->Width))
  if((Y > 0) && (Y < img->Height))
    {
    if(!ShowIM)
      {
      PrevHeight  = Height;
      PrevWidth   = Width;
      ShowIM      = true;
      Height      = Height - MainFormSLS->Panel_Chat->Height - 50;
      block_shift = true;

      ImgsTop     = ClientHeight - 80;
      conf_disc_img->Top   = ImgsTop;
      conf_screen_img->Top = conf_disc_img->Top;
      conf_add_img->Top    = conf_disc_img->Top;
      conf_mic_img->Top    = conf_disc_img->Top;
      conf_chat_img->Top   = conf_disc_img->Top;

      MainFormSLS->set_IM_to_conf_participants(true);
      MainFormSLS->Memo1->SetFocus();
      }
    else
      {
      Height = PrevHeight;
      Width  = PrevWidth;
      ShowIM = false;

      ImgsTop = ClientHeight - 80;
      conf_disc_img->Top   = ImgsTop;
      conf_screen_img->Top = conf_disc_img->Top;
      conf_add_img->Top    = conf_disc_img->Top;
      conf_mic_img->Top    = conf_disc_img->Top;
      conf_chat_img->Top   = conf_disc_img->Top;

      MainFormSLS->set_IM_to_conf_participants(false);
      }
    }
}
//---------------------------------------------------------------------------
void __fastcall TConferenceWin::Send_IM_To_All_Conf_Participants(const vector<string>& v)
{
::EnterCriticalSection(&cp_cs);
  if(!v.empty())
    {
    deque<TConfCont*> dest;
  __get_copy_CP_UNSAFE(dest);
    while(!dest.empty())
         {
         TConfCont* ConfCont = dest.front();
         dest.pop_front();
         TContact Contact;
         Contact.name = ConfCont->user_name;
         MainFormSLS->IM_Send(&Contact,v);
         }
    }
::LeaveCriticalSection(&cp_cs);
}
//-----------------------------------------------------------------------------
void __fastcall TConferenceWin::FormCreate(TObject *Sender)
{
MainFormSLS->LAST_FORM_CREATED = true; //!!!

MainFormSLS->Stun.StunClientProc(&MainFormSLS->iniData, MainFormSLS->Sip, MainFormSLS->ofs->elt);
MainFormSLS->Sip->sck = exsCreateUDPSocket_ADDR_PORT_ANY();
if(MainFormSLS->Sip->sck==INVALID_SOCKET)
  {
  MainFormSLS->createSocketFailed(MainFormSLS->ofs->elt);
  return;
  }
MainFormSLS->Sip->getSockName(MainFormSLS->ofs->elt);
MainFormSLS->Sip->create_work_threads();      //TCP, TLS and so on
#ifdef Tcp_Sock_Log
so_debug_set_log_cb(sock_debug_f);  //sock_debug_f
#endif

if(MainFormSLS->Sip->uac)
  if(MainFormSLS->Sip->uac->srst)       //srtp
    if(MainFormSLS->Sip->uac->srst->Suspended)
       MainFormSLS->Sip->uac->srst->Resume();    //Do not use Resume_Thread() !!!
if(MainFormSLS->Sip->uas)
  if(MainFormSLS->Sip->uas->srst)     //srtp
    if(MainFormSLS->Sip->uas->srst->Suspended)
       MainFormSLS->Sip->uas->srst->Resume();    //Do not use Resume_Thread() !!!
TSipRecvThread* SRT = MainFormSLS->Sip->getTSipRecvThread();
if(SRT)
   SRT->Resume();                   //Do not use Resume_Thread() !!!

if(MainFormSLS->Sip->checkAccount())
  {
  if((MainFormSLS->Sip->sip_transport != Sip_Transport_TCP) && (MainFormSLS->Sip->sip_transport != Sip_Transport_TLS))
      MainFormSLS->Sip->initRegistrationProc();
  MainFormSLS->Sip->readContacts();
  }

MainFormSLS->Sip->readPresenceComment();        // My comment
MainFormSLS->Sip->readPresenceContactComment(); // Comments from contacts of my contact list

#ifdef SIP_Transport_TLS
MainFormSLS->N6->Visible = false;
#endif
#ifdef Hide_Transport_Menu
MainFormSLS->N6->Visible = false;
#endif
#ifdef Hide_Video_Menu
MainFormSLS->VideoCam1->Visible = false;
#endif
MainFormSLS->initial_load_user_history();
if(MainFormSLS->Im.LCFT)  //Thread для работы с файлом содержащим последние вызовы (Last Calls)
  {
  TLCSBuf* LCSBuf = new TLCSBuf(READ);   // Запрос на чтение Last Calls
  if(LCSBuf)
     MainFormSLS->Im.LCFT->push_lcs_buf(LCSBuf);
  }
Application->OnMinimize = MainFormSLS->On_Minimize_Application;
Application->OnRestore  = MainFormSLS->On_Restore_Application;
MainFormSLS->TrayMessage_Ext(NIM_ADD,"Contact",2);
MainFormSLS->sys_timer.InitTimer();

//MainFormSLS->LAST_FORM_CREATED = true; //!!!

if(MainFormSLS->ofs)
  if(MainFormSLS->ofs->elt)
    if(MainFormSLS->ofs->elt->getlog())
      {
      string TimeStr;
      TDateTime DateTime = DateTime.CurrentDateTime();
      exsDateTime(DateTime,TimeStr);
      string str = "\n" + (string)TimeStr + " TConferenceWin_CREATED! " + "\n";
      MainFormSLS->ofs->elt->FputEvt(str, 1);
      }
}
//---------------------------------------------------------------------------

