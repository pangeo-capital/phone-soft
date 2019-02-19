//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "WinRDefs.h"
#include "ContactMenu_Unit.h"
#include "SipClient_Unit.h"
#include "Unit3.h"
#include "Unit4.h"

#define CM_SHIFT_STATE_LEFT 10
#define CM_SHIFT_FNAME_LEFT 30
#define CM_SHIFT_STATE_TOP  8

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TContactMenu *ContactMenu;
//---------------------------------------------------------------------------
__fastcall TContactMenu::TContactMenu(TComponent* Owner)
         : TForm(Owner)
{
lng = Lang_RU;
if(MainFormSLS->getIntrfStyle() == 1)
  Width = Screen->Width/5;
else
  Width = 2*MainFormSLS->Panel2->Width/3;

Panel1->Ctl3D      = false;
Panel1->Top        = 0;
Panel1->Left       = 0;
Panel1->BevelInner = bvNone;
Panel1->BevelOuter = bvNone;
Panel1->Width      = Width;

DrawGrid1->Ctl3D    = false;

DrawGrid1->Top      = 1;
DrawGrid1->Left     = 1;
DrawGrid1->Width    = Panel1->Width - 3;
DrawGrid1->ColWidths[0] = DrawGrid1->Width;

Selected_CT = ContactType_CLIENT;
}
//---------------------------------------------------------------------------
void __fastcall TContactMenu::DrawGrid1MouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
int ACol,ARow;
DrawGrid1->MouseToCell(X,Y,ACol,ARow);
if(ACol == -1)return;
if(ARow == -1)return;
if(ARow ==  5)return;
if(ARow ==  8)return;
DrawGrid1->Row = ARow;
}
//---------------------------------------------------------------------------
void __fastcall TContactMenu::DrawGrid1DrawCell(TObject *Sender, int ACol,
      int ARow, TRect &Rect, TGridDrawState State)
{
if(Selected_CT == ContactType_CLIENT)
   DrawCell_For_CLIENT(ARow, Rect, State);
else if(Selected_CT == ContactType_GROUP)
   DrawCell_For_GROUP(ARow, Rect, State);
else if(Selected_CT == ContactType_DIVISION)
   DrawCell_For_DIVISION(ARow, Rect, State);
}
//---------------------------------------------------------------------------
void __fastcall TContactMenu::DrawCell_For_CLIENT(int ARow, TRect &Rect, TGridDrawState State)
{
if(State.Contains(gdFocused))
  {
  DrawGrid1->Canvas->Brush->Color = clActiveCaption;//clBlue;// clBackground;
  DrawGrid1->Canvas->Font->Color = clWhite;
  DrawGrid1->Canvas->FillRect(Rect);
  DrawGrid1->Canvas->DrawFocusRect(Rect);
  }
string s;
switch(ARow){
  case 0:
  switch(lng){
        case Lang_EN:s="Call";break;
        case Lang_RU:s="Позвонить";break;
        }
  //ImageList1->Draw(DrawGrid1->Canvas,Rect.Left + CM_SHIFT_STATE_LEFT,
  //                           Rect.Top + Rect.Height()/2 - CM_SHIFT_STATE_TOP, 0, true);
  DrawGrid1->Canvas->TextOut(Rect.Left + CM_SHIFT_STATE_LEFT + CM_SHIFT_FNAME_LEFT,
                             Rect.Top + Rect.Height()/2 - CM_SHIFT_STATE_TOP, s.c_str());
  break;

  case 1:
  switch(lng){
        case Lang_EN:s="Video Call";break;
        case Lang_RU:s="Видеозвонок";break;
        }
  //ImageList1->Draw(DrawGrid1->Canvas,Rect.Left + CM_SHIFT_STATE_LEFT,
  //                           Rect.Top + Rect.Height()/2 - CM_SHIFT_STATE_TOP, 8, true);
  DrawGrid1->Canvas->TextOut(Rect.Left + CM_SHIFT_STATE_LEFT + CM_SHIFT_FNAME_LEFT,
                             Rect.Top + Rect.Height()/2 - CM_SHIFT_STATE_TOP, s.c_str());
  break;

  case 2:
  switch(lng){
        case Lang_EN:s="Send IM"; break;
        case Lang_RU:s="Чат";     break;
        }
  //ImageList1->Draw(DrawGrid1->Canvas,Rect.Left + CM_SHIFT_STATE_LEFT,
  //                           Rect.Top + Rect.Height()/2 - CM_SHIFT_STATE_TOP, 1, true);
  DrawGrid1->Canvas->TextOut(Rect.Left + CM_SHIFT_STATE_LEFT + CM_SHIFT_FNAME_LEFT,
                             Rect.Top + Rect.Height()/2 - CM_SHIFT_STATE_TOP, s.c_str());
  break;

  case 30:
  switch(lng){
        case Lang_EN:s="Send IM";break;
        case Lang_RU:s="Отправить SMS";break;
        }
  //ImageList1->Draw(DrawGrid1->Canvas,Rect.Left + CM_SHIFT_STATE_LEFT,
  //                           Rect.Top + Rect.Height()/2 - CM_SHIFT_STATE_TOP, 2, true);
  DrawGrid1->Canvas->TextOut(Rect.Left + CM_SHIFT_STATE_LEFT + CM_SHIFT_FNAME_LEFT,
                             Rect.Top + Rect.Height()/2 - CM_SHIFT_STATE_TOP, s.c_str());
  break;

  /*
  case 4:
  switch(lng){
        case Lang_EN:s="Send Contacts";break;
        case Lang_RU:s="Экспорт Списка Контактов...";break;
        }
  ImageList1->Draw(DrawGrid1->Canvas,Rect.Left + CM_SHIFT_STATE_LEFT,
                             Rect.Top + Rect.Height()/2 - CM_SHIFT_STATE_TOP, 3, true);
  DrawGrid1->Canvas->TextOut(Rect.Left + CM_SHIFT_STATE_LEFT + CM_SHIFT_FNAME_LEFT,
                             Rect.Top + Rect.Height()/2 - CM_SHIFT_STATE_TOP, s.c_str());
  break;
    */

  case 4:
  switch(lng){
        case Lang_EN:s="Send File";break;
        case Lang_RU:s="Отправить файл";break;
        }
  //ImageList1->Draw(DrawGrid1->Canvas,Rect.Left + CM_SHIFT_STATE_LEFT,
  //                           Rect.Top + Rect.Height()/2 - CM_SHIFT_STATE_TOP, 4, true);
  DrawGrid1->Canvas->TextOut(Rect.Left + CM_SHIFT_STATE_LEFT + CM_SHIFT_FNAME_LEFT,
                             Rect.Top + Rect.Height()/2 - CM_SHIFT_STATE_TOP, s.c_str());
  break;

  /*
  case 5:
  switch(lng){
        case Lang_EN:s="Conference";break;
        case Lang_RU:s="Конференция";break;
        }
  ImageList1->Draw(DrawGrid1->Canvas,Rect.Left + CM_SHIFT_STATE_LEFT,
                             Rect.Top + Rect.Height()/2 - CM_SHIFT_STATE_TOP, 10, true);
  DrawGrid1->Canvas->TextOut(Rect.Left + CM_SHIFT_STATE_LEFT + CM_SHIFT_FNAME_LEFT,
                             Rect.Top + Rect.Height()/2 - CM_SHIFT_STATE_TOP, s.c_str());
  break;
   */

  case 5:
  DrawGrid1->Canvas->Font->Color = clGray;
  DrawGrid1->Canvas->TextOut(0,Rect.Top, "__________________________________________");
  break;

  case 6:
  switch(lng){
        case Lang_EN:s="View Profile";break;
        case Lang_RU:s="Просмотреть личные данные";break;
        }
  //ImageList1->Draw(DrawGrid1->Canvas,Rect.Left + CM_SHIFT_STATE_LEFT,
  //                           Rect.Top + Rect.Height()/2 - CM_SHIFT_STATE_TOP, 4, true);
  DrawGrid1->Canvas->TextOut(Rect.Left + CM_SHIFT_STATE_LEFT + CM_SHIFT_FNAME_LEFT,
                             Rect.Top + Rect.Height()/2 - CM_SHIFT_STATE_TOP, s.c_str());
  break;

  case 7:
  switch(lng){
        case Lang_EN:s="Edit";break;
        case Lang_RU:s="Редактировать";break;
        }
  //ImageList1->Draw(DrawGrid1->Canvas,Rect.Left + CM_SHIFT_STATE_LEFT,
  //                           Rect.Top + Rect.Height()/2 - CM_SHIFT_STATE_TOP, 4, true);
  DrawGrid1->Canvas->TextOut(Rect.Left + CM_SHIFT_STATE_LEFT + CM_SHIFT_FNAME_LEFT,
                             Rect.Top + Rect.Height()/2 - CM_SHIFT_STATE_TOP, s.c_str());
  break;


  case 8:
  DrawGrid1->Canvas->Font->Color = clGray;
  DrawGrid1->Canvas->TextOut(0,Rect.Top, "__________________________________________");
  break;

 /*
  case 7:
  switch(lng){
        case Lang_EN:s="View Profile";break;
        case Lang_RU:s="Личные данные";break;
        }
  ImageList1->Draw(DrawGrid1->Canvas,Rect.Left + CM_SHIFT_STATE_LEFT,
                             Rect.Top + Rect.Height()/2 - CM_SHIFT_STATE_TOP, 5, true);
  DrawGrid1->Canvas->TextOut(Rect.Left + CM_SHIFT_STATE_LEFT + CM_SHIFT_FNAME_LEFT,
                             Rect.Top + Rect.Height()/2 - CM_SHIFT_STATE_TOP,  s.c_str());
  break;

  case 8:
  switch(lng){
        case Lang_EN:s="Rename";break;
        case Lang_RU:s="Переименовать";break;
        }
  DrawGrid1->Canvas->TextOut(Rect.Left + CM_SHIFT_STATE_LEFT + CM_SHIFT_FNAME_LEFT,
                             Rect.Top + Rect.Height()/2 - CM_SHIFT_STATE_TOP,  s.c_str());
  break;

  case 9:
  DrawGrid1->Canvas->Font->Color = clGray;
  DrawGrid1->Canvas->TextOut(0,Rect.Top, "__________________________________________");
  break;
   */
  /*
  case 10:
  switch(lng){
        case Lang_EN:s="Mark as Unread";break;
        case Lang_RU:s="Отметить как непрочитанное";break;
        }
  DrawGrid1->Canvas->TextOut(Rect.Left + CM_SHIFT_STATE_LEFT + CM_SHIFT_FNAME_LEFT,
                             Rect.Top + Rect.Height()/2 - CM_SHIFT_STATE_TOP,  s.c_str());
  break;


  case 7:
  switch(lng){
        case Lang_EN:s="Block this Person";break;
        case Lang_RU:s="Блокировать пользователя";break;
        }
  ImageList1->Draw(DrawGrid1->Canvas,Rect.Left + CM_SHIFT_STATE_LEFT,
                             Rect.Top + Rect.Height()/2 - CM_SHIFT_STATE_TOP, 6, true);
  DrawGrid1->Canvas->TextOut(Rect.Left + CM_SHIFT_STATE_LEFT + CM_SHIFT_FNAME_LEFT,
                             Rect.Top + Rect.Height()/2 - CM_SHIFT_STATE_TOP,  s.c_str());
  break;

  case 7:
  switch(lng){
        case Lang_EN:s="View Old Messages";break;
        case Lang_RU:s="Просмотреть старые сообщения";break;
        }
  ImageList1->Draw(DrawGrid1->Canvas,Rect.Left + CM_SHIFT_STATE_LEFT,
                             Rect.Top + Rect.Height()/2 - CM_SHIFT_STATE_TOP, 9, true);
  DrawGrid1->Canvas->TextOut(Rect.Left + CM_SHIFT_STATE_LEFT + CM_SHIFT_FNAME_LEFT,
                             Rect.Top + Rect.Height()/2 - CM_SHIFT_STATE_TOP,  s.c_str());
  break;
  */


  case 9:
  switch(lng){
        case Lang_EN:s="Remove from Contacts";break;
        case Lang_RU:s="Удалить из списка контактов";break;
        }
  ImageList1->Draw(DrawGrid1->Canvas,Rect.Left + CM_SHIFT_STATE_LEFT,
                             Rect.Top + Rect.Height()/2 - CM_SHIFT_STATE_TOP, 7, true);
  DrawGrid1->Canvas->TextOut(Rect.Left + CM_SHIFT_STATE_LEFT + CM_SHIFT_FNAME_LEFT,
                             Rect.Top + Rect.Height()/2 - CM_SHIFT_STATE_TOP,  s.c_str());
  break;

  /*
  case 14:
  DrawGrid1->Canvas->Font->Color = clGray;
  DrawGrid1->Canvas->TextOut(0,Rect.Top, "__________________________________________");
  break;
  */

  /*
  case 15:
  switch(lng){
        case Lang_EN:s="Hide Conversation";break;
        case Lang_RU:s="Скрыть разговор";break;
        }
  DrawGrid1->Canvas->TextOut(Rect.Left + CM_SHIFT_STATE_LEFT + CM_SHIFT_FNAME_LEFT,
                             Rect.Top + Rect.Height()/2 - CM_SHIFT_STATE_TOP,  s.c_str());
  break;
  */
  } //switch(ARow){
}
//------------------------------------------------------------------------------
void __fastcall TContactMenu::DrawCell_For_GROUP(int ARow, TRect &Rect, TGridDrawState State)
{
if(State.Contains(gdFocused))
  {
  DrawGrid1->Canvas->Brush->Color = clActiveCaption;//clBlue;// clBackground;
  DrawGrid1->Canvas->Font->Color = clWhite;
  DrawGrid1->Canvas->FillRect(Rect);
  DrawGrid1->Canvas->DrawFocusRect(Rect);
  }
string s;
switch(ARow){
  case 0:
         switch(lng){
                    case Lang_EN:s="Send IM"; break;
                    case Lang_RU:s="Чат";     break;
                    }
         //ImageList1->Draw(DrawGrid1->Canvas,Rect.Left + CM_SHIFT_STATE_LEFT,
         //                    Rect.Top + Rect.Height()/2 - CM_SHIFT_STATE_TOP, 1, true);
         DrawGrid1->Canvas->TextOut(Rect.Left + CM_SHIFT_STATE_LEFT + CM_SHIFT_FNAME_LEFT,
                             Rect.Top + Rect.Height()/2 - CM_SHIFT_STATE_TOP, s.c_str());
         break;
  case 1:
         DrawGrid1->Canvas->Font->Color = clGray;
         DrawGrid1->Canvas->TextOut(0,Rect.Top, "__________________________________________");
         break;
  case 2:
         switch(lng){
                    case Lang_EN:s="Remove from Contacts";break;
                    case Lang_RU:s="Удалить из списка контактов";break;
                    }
         ImageList1->Draw(DrawGrid1->Canvas,Rect.Left + CM_SHIFT_STATE_LEFT,
                             Rect.Top + Rect.Height()/2 - CM_SHIFT_STATE_TOP, 7, true);
         DrawGrid1->Canvas->TextOut(Rect.Left + CM_SHIFT_STATE_LEFT + CM_SHIFT_FNAME_LEFT,
                             Rect.Top + Rect.Height()/2 - CM_SHIFT_STATE_TOP,  s.c_str());
         break;
  }
}
//------------------------------------------------------------------------------
void __fastcall TContactMenu::DrawCell_For_DIVISION(int ARow, TRect &Rect, TGridDrawState State)
{
if(State.Contains(gdFocused))
  {
  DrawGrid1->Canvas->Brush->Color = clWhite; // clActiveCaption;//clBlue;// clBackground;
  DrawGrid1->Canvas->Font->Color  = clBlack; // clWhite;
  DrawGrid1->Canvas->FillRect(Rect);
  DrawGrid1->Canvas->DrawFocusRect(Rect);
  }
string s;
switch(ARow){
  case 0:
  switch(lng){
        case Lang_EN:s="Remove from Contacts";break;
        case Lang_RU:s="Удалить из списка контактов";break;
        }
  ImageList1->Draw(DrawGrid1->Canvas,Rect.Left + CM_SHIFT_STATE_LEFT,
                             Rect.Top + Rect.Height()/2 - CM_SHIFT_STATE_TOP, 7, true);
  DrawGrid1->Canvas->TextOut(Rect.Left + CM_SHIFT_STATE_LEFT + CM_SHIFT_FNAME_LEFT,
                             Rect.Top + Rect.Height()/2 - CM_SHIFT_STATE_TOP,  s.c_str());
  break;
  }//switch(ARow){
}
//------------------------------------------------------------------------------
void __fastcall TContactMenu::DrawGrid1MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
int ACol,ARow;
DrawGrid1->MouseToCell(X,Y,ACol,ARow);
if(ACol==-1)return;
if(ARow==-1)return;
if(Button == mbLeft)
  {
  if(Selected_CT == ContactType_CLIENT)
    {
    switch(ARow){
        case 0:MainFormSLS->AudioCall();
               break;
        #ifdef SIP_Video
        case 1:MainFormSLS->VideoCall();
               break;
        #endif
        case 2:MainFormSLS->FocusControl(MainFormSLS->Memo1);
               MainFormSLS->set_IM_to_conf_participants(false);
               break;
        case 3:MainFormSLS->FocusControl(MainFormSLS->Memo1);
               MainFormSLS->set_IM_to_conf_participants(false);
               break;
        case 4:MainFormSLS->OpenFileTransferDialog();
               break;
        case 6:MainFormSLS->Open_Profile();
               break;
        case 7:MainFormSLS->Edit_Profile();
               break;
        case 9:MainFormSLS->Contact_Delete();
               break;
        }
    }
  else if(Selected_CT == ContactType_GROUP)
    {
    switch(ARow){
          case 0:MainFormSLS->FocusControl(MainFormSLS->Memo1);
                 MainFormSLS->set_IM_to_chat_participants(true);
                 break;
          case 2:MainFormSLS->Contact_Delete();
                 break;
          }
    }
  else if(Selected_CT == ContactType_DIVISION)
    {
    switch(ARow){
          case 0:MainFormSLS->Contact_Delete();
                 break;
          }
    }
  Close();
  }
}
//---------------------------------------------------------------------------
void __fastcall TContactMenu::FormKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
if(Key == 27) //Esc
   ContactMenu->Close();
}
//---------------------------------------------------------------------------
__fastcall TProfileForm::TProfileForm(TComponent* Owner,int Dummy)
         : TForm(Owner,Dummy)
{
Font->Charset = RUSSIAN_CHARSET;
TYPE      = 0;
Contact   = NULL; //Do Not Delete in Destructor
e1        = NULL;
e2        = NULL;
ed1       = NULL;
ed2       = NULL;
Color     = clWhite;
FormStyle = fsStayOnTop;
switch(Dummy){
case 1:{         //Просмотреть личные данные
  TYPE            = 1;
  TBorderIcons BI = BorderIcons;
  BI              = BI << biSystemMenu;
  BorderIcons     = BI;
  BorderStyle     = bsDialog;
  Left            = MainFormSLS->Left + MainFormSLS->DrawGrid1->Width + 24;
  Top             = MainFormSLS->Top  + MainFormSLS->Panel1->Height   + 60;

  Panel         = new TPanel(this);
  Panel->Parent = this;
  Panel->Align  = alBottom;

  Btn1          = new TButton(Panel);
  Btn1->Parent  = Panel;
  Btn1->Width   = Width/2 - 10;
  Btn1->Height  = 22;
  Btn1->Left    = Width - Btn1->Width - 20;
  Btn1->Top     = Panel->Height/2 - Btn1->Height/2;
  Btn1->Caption = "Закрыть";

  Btn1->OnClick = Btn1Click;
  OnCloseQuery  = FormCloseQuery;
  OnClose       = FormClose;
  break;
  }
case 2:{      //Добавить внешний контакт
  TYPE            = 2;
  TBorderIcons BI = BorderIcons;
  BI              = BI << biSystemMenu;
  BorderIcons     = BI;
  BorderStyle     = bsDialog;

  OnCloseQuery  = FormCloseQuery;
  OnClose       = FormClose;
  break;
  }
 case 3:{    //Редактирование
  TYPE            = 3;
  TBorderIcons BI = BorderIcons;
  BI              = BI << biSystemMenu;
  BorderIcons     = BI;
  BorderStyle     = bsDialog;
  Left            = MainFormSLS->Left + MainFormSLS->DrawGrid1->Width + 24;
  Top             = MainFormSLS->Top  + MainFormSLS->Panel1->Height   + 60;

  OnCloseQuery  = FormCloseQuery;
  OnClose       = FormClose;
  break;
  }
 }
}
//---------------------------------------------------------------------------
void __fastcall TProfileForm::Btn1Click(TObject *Sender)
{
Close();
}
//---------------------------------------------------------------------------
void __fastcall TProfileForm::Btn1Click_OnAddExtContact(TObject *Sender)
{
if(Contact)
  {
  string name = Contact->name;
  AnsiString S = ed1->Edit->Text;
  if(!S.IsEmpty())
    Contact->full_name = S.c_str();
  MainFormSLS->Sip->Contacts.add_contact_name_to_actual_directory(Contact);
  ::EnterCriticalSection(&MainFormSLS->Sip->Contacts.contlist_cs);
    MainFormSLS->Sip->Contacts._insert_contact_in_contact_list(Contact,true);
  ::LeaveCriticalSection(&MainFormSLS->Sip->Contacts.contlist_cs);
  MainFormSLS->Sip->Contacts.inc_contact_list_size();
  MainFormSLS->Sip->Contacts.Update_DrawGrid_RowCount(MainFormSLS->DrawGrid1);

  TTransactionData data;
  data.u_1 = 0; //добавить в персональный контакт лист
  data.s_1 = MainFormSLS->Sip->Account.get_user_name();
  data.s_2 = name;
  EnterpriseSubscList->MODIFY_PERSONAL_CITY_PHONE_LIST(data);
  }
Close();
}
//---------------------------------------------------------------------------
void __fastcall TProfileForm::Btn1Click_OnEditContact(TObject *Sender)
{
__edit_contact();
Close();
}
//---------------------------------------------------------------------------
void __fastcall TProfileForm::FullName_KeyUp(TObject *Sender, WORD &Key, TShiftState Shift)
{
 if(Key == 13)
   {
 __edit_contact();
   Close();
   }
}
//---------------------------------------------------------------------------
void __fastcall TProfileForm::__edit_contact()
{
if(pd.actual)
  {
  TContact ContactCopy;
  if(MainFormSLS->Sip->Contacts.get_contact_copy_by_user_name(ContactCopy, pd.name))
    {
    AnsiString S = ed2->Edit->Text;
    string s = S.c_str();
    if(pd.full_name != s)
      {
      TContact* CONT = MainFormSLS->Sip->Contacts.get_contact_by_id(ContactCopy.get_id());
      if(CONT)
         {
         if(!s.empty())
            CONT->full_name = s;
         else
            CONT->full_name = CONT->name;
         MainFormSLS->Sip->Contacts.add_contact_name_to_actual_directory(CONT);

         TTransactionData data;
         data.u_1 = 2; //изменить локальное имя в списке
         data.s_1 = MainFormSLS->Sip->Account.get_user_name();
         data.s_2 = CONT->name;
         data.s_3 = CONT->full_name;
         if(CONT->CL == Location_EXT)
            EnterpriseSubscList->MODIFY_PERSONAL_CITY_PHONE_LIST(data);
         else
            EnterpriseSubscList->MODIFY_PERSONAL_CONTACT_LIST(data);
         MainFormSLS->Sip->Contacts.sort_by_full_user_name();
         MainFormSLS->DrawGrid1->Refresh();
         int raw = MainFormSLS->Sip->Contacts.get_row_by_contact_id_in_sorted_contact_list(ContactCopy.get_id());
         if(raw != -1)
           if(raw < MainFormSLS->DrawGrid1->RowCount)
             {
             MainFormSLS->DrawGrid1->Row    = raw;
             MainFormSLS->set_user_name_to_send(CONT->name);
             MainFormSLS->ComboBox1->Text = CONT->full_name.c_str();
             MainFormSLS->CalledNameLbl->Caption = CONT->full_name.c_str();
             }
         }
      }
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TProfileForm::FormCloseQuery(TObject *Sender, bool &CanClose)
{
CanClose = true;
}
//-------------------------------------------------------------------------
void __fastcall TProfileForm::FormClose(TObject *Sender, TCloseAction &Action)
{
MainFormSLS->ProfileForm = NULL;
Action = caFree;
}
//--------------------------------------------------------------------------
/*
void __fastcall TProfileForm::ViewProfile(TContact* Contact)
{
//left_1 = 20; left_2 = 150;  font_sz = 10; int underlying_line_length = 92;

AnsiString S;
while(underlying_line_length--)
      S += "-";
Caption = "    " + (AnsiString)Contact->full_name.c_str();
e1 = new TElement;
e1->Label1 = new TLabel(this);
e1->Label1->Parent     = this;
e1->Label1->Left       = left_1;
e1->Label1->Top        = 20;
e1->Label1->Font->Size = font_sz;
e1->Label1->Caption    = "Номер абонента:";

e1->Label2 = new TLabel(this);
e1->Label2->Parent     = this;
e1->Label2->Left       = left_2;
e1->Label2->Top        = e1->Label1->Top;
e1->Label2->Font->Size = font_sz;
e1->Label2->Caption    = Contact->name.c_str();


e1->Label3 = new TLabel(this);
e1->Label3->Parent = this;
e1->Label3->Left   = left_1 - 2;
e1->Label3->Top    = e1->Label1->Top + e1->Label1->Height;// - 5;
e1->Label3->Font->Color = (TColor)0x00D0D0D0; // clGray;
e1->Label3->Caption = S;

 e2 = new TElement;
 e2->Label1 = new TLabel(this);
 e2->Label1->Parent     = this;
 e2->Label1->Left       = left_1;
 e2->Label1->Top        = 50; //40;
 e2->Label1->Font->Size = font_sz;
 e2->Label1->Caption    = "Должность:";


if(!Contact->position.empty())
 {

 e2->Label2 = new TLabel(this);
 e2->Label2->Parent     = this;
 e2->Label2->Left       = left_2;
 e2->Label2->Top        = e2->Label1->Top;
 e2->Label2->Font->Size = font_sz;

 string position = Contact->position;
 //int len = position.length();

 int width = e2->Label2->Canvas->TextWidth(position.c_str());
 if(width > (Width - left_2))
   {
   int A = 5;
   }

// e2->Label2->Caption    = position.c_str();
// this->Canvas->Brush->Color = clBlack;

// this->Canvas->FillRect(Rect(0,0,100,100));


// this->Canvas->Font->Color = clBlack;
// this->Canvas->TextOut(left_2,e2->Label1->Top,position.c_str());


 e2->Label3 = new TLabel(this);
 e2->Label3->Parent = this;
 e2->Label3->Left   = left_1 - 2;
 e2->Label3->Top    = e2->Label1->Top + e2->Label1->Height;// - 5;
 e2->Label3->Font->Color = (TColor)0x00D0D0D0; // clGray;
 e2->Label3->Caption = S;
 }
 

}
*/
//------------------------------------------------------------------------------
void __fastcall TProfileForm::AddContactNameControls(TDialPad* DialPad)
{
Left   = DialPad->Left;
Width  = DialPad->Width;
Height = 130;
Top    = DialPad->Top + DialPad->Height - 85;

e1         = new TElement;
e1->Label1 = new TLabel(this);
e1->Label1->Parent      = this;
e1->Label1->Left        = 10;
e1->Label1->Top         = 10;
e1->Label1->Font->Size  = 10;
e1->Label1->Font->Color = clActiveCaption; //(TColor)0x00E37506; //0xB0B0B0;//0x00EDEDED; //clBlue;
e1->Label1->Font->Style = e1->Label1->Font->Style << fsBold;
e1->Label1->Font->Charset = RUSSIAN_CHARSET;
e1->Label1->Caption     = "Присвоить имя данному контакту";

ed1 = new TEditBox(this, e1->Label1->Left, e1->Label1->Top + e1->Label1->Height + 5, Width - 30, 20);

Btn1          = new TButton(this);
Btn1->Parent  = this;
Btn1->Width   = Width/2 - 10;
Btn1->Height  = 22;
Btn1->Left    = Width - Btn1->Width - 20;
Btn1->Top     = ClientHeight - Btn1->Height - 10;
Btn1->Caption = "Сохранить";

Btn1->OnClick = Btn1Click_OnAddExtContact;
}
//------------------------------------------------------------------------------
__fastcall TEditBox::TEditBox(TForm* PF, int left, int top, int width, int height)
{
Panel1             = new TPanel(PF);
Panel1->Parent     = PF;
Panel1->Height     = height;
Panel1->Left       = left;
Panel1->Top        = top;
Panel1->Width      = width;
Panel1->BevelInner = bvNone;
Panel1->BevelOuter = bvNone;
Panel1->Color      = (TColor)0xD0D0D0;

Panel2             = new TPanel(Panel1);
Panel2->Parent     = Panel1;
Panel2->BevelInner = bvNone;
Panel2->BevelOuter = bvNone;
Panel2->Color      = clWhite;
Panel2->Left       = 1;
Panel2->Top        = 1;
Panel2->Height     = Panel1->Height - 2;
Panel2->Width      = Panel1->Width  - 2;

Edit               = new TEdit(Panel2);
Edit->Parent       = Panel2;
Edit->Top          = 2;
Edit->Left         = 3;
Edit->Width        = Panel2->Width - 4;
Edit->BorderStyle  = bsNone;
}
//------------------------------------------------------------------------------
void __fastcall TProfileForm::EditProfile(TContact* Contact)
{
Caption = "Редактирование";
pd.actual    = true;
pd.name      = Contact->name;
pd.full_name = Contact->full_name;
int left = 20; int font_sz = 10; int edit_width = Width - 50;
e1         = new TElement;
e1->Label1 = new TLabel(this);
e1->Label1->Parent      = this;
e1->Label1->Left        = left;
e1->Label1->Top         = 10;
e1->Label1->Font->Size  = font_sz;
e1->Label1->Font->Color = clActiveCaption;
e1->Label1->Font->Style = e1->Label1->Font->Style << fsBold;
if(Contact->CL == Location_EXT)
  e1->Label1->Caption     = "Номер телефона";
else
  e1->Label1->Caption     = "Номер абонента";

ed1 = new TEditBox(this, left, e1->Label1->Top + e1->Label1->Height + 2, edit_width, 25);
ed1->Panel2->Color = clBtnFace;
ed1->Edit->Color   = clBtnFace;
ed1->Edit->Font->Size  = 10;
ed1->Edit->Font->Style = ed1->Edit->Font->Style << fsBold;
ed1->Edit->Text    = pd.name.c_str();
ed1->Edit->Enabled = false;

e2         = new TElement;
e2->Label1 = new TLabel(this);
e2->Label1->Parent      = this;
e2->Label1->Left        = left;
e2->Label1->Top         = ed1->Panel1->Top + ed1->Panel1->Height + 10;
e2->Label1->Font->Size  = font_sz;
e2->Label1->Font->Color = clActiveCaption;
e2->Label1->Font->Style = e2->Label1->Font->Style << fsBold;
e2->Label1->Caption     = "Имя абонента";

ed2 = new TEditBox(this, left, e2->Label1->Top + e2->Label1->Height + 2, edit_width, 25);
ed2->Edit->Text = pd.full_name.c_str();
ed2->Edit->Font->Size  = 10;
ed2->Edit->Font->Style = ed2->Edit->Font->Style << fsBold;
ed2->Edit->OnKeyUp     = FullName_KeyUp;

Btn1          = new TButton(this);
Btn1->Parent  = this;
Btn1->Width   = ed2->Panel1->Width/2;
Btn1->Left    = ed2->Panel1->Left + ed2->Panel1->Width/2;
Btn1->Height  = 22;
Btn1->Top     = ed2->Panel1->Top + ed2->Panel1->Height + 10;
Btn1->Caption = "Применить";

Height = Btn1->Top + Btn1->Height + 40;

Btn1->OnClick = Btn1Click_OnEditContact;
}
//------------------------------------------------------------------------------
void __fastcall TProfileForm::EditProfile_OnOpenWindow(TContact* Contact)
{
pd.name      = Contact->name;
pd.full_name = Contact->full_name;
if(Contact->CL == Location_EXT)
  e1->Label1->Caption     = "Номер телефона";
else
  e1->Label1->Caption     = "Номер абонента";
ed1->Edit->Text = pd.name.c_str();
ed2->Edit->Text = pd.full_name.c_str();
}
//------------------------------------------------------------------------------
void __fastcall TProfileForm::CheckWidth(queue<string>& q, const string& s)
{
int width = Canvas->TextWidth(s.c_str());
if(width  < (Width - left_2 - 10))
  {
  q.push(s);
  return;
  }
else
  {
  int len = s.length();
  string pref;
  string tail;
  int st = s.rfind(" ");
  if(st != -1)
    {
    pref = s.substr(0,st);
    st++;
    if(st < len)
      {
      tail = s.substr(st);
      }
    q.push(pref);
    q.push(tail);
    }
  }
}
//------------------------------------------------------------------------------
void __fastcall TProfileForm::PrintNickName(int top, const AnsiString& PositionName, const string& name)
{
Canvas->TextOut(left_1, top, PositionName);
Canvas->TextOut(left_2, top, name.c_str());
}
//------------------------------------------------------------------------------
void __fastcall TProfileForm::PrintPosition(int& top, int h, const AnsiString& PositionName, const string& position)
{
top += h;
Canvas->TextOut(left_1, top, PositionName);
queue<string> q;
CheckWidth(q, position);
while(!q.empty())
     {
     string s = q.front();
     q.pop();
     Canvas->TextOut(left_2, top, s.c_str());
     top += h;
     }
}
//------------------------------------------------------------------------------
void __fastcall TProfileForm::DrawUnderline(int& top, int h, TRBitMap& rbmp)
{
top += h;
Canvas->Draw(left_1 - 2, top, rbmp.bmp);
}
//------------------------------------------------------------------------------
void __fastcall TProfileForm::PrintFullName(int& top, int h, const AnsiString& PositionName, const string& fullname)
{
top += h;
Canvas->TextOut(left_1, top, PositionName);
queue<string> q;
CheckWidth(q, fullname);
while(!q.empty())
     {
     string s = q.front();
     q.pop();
     Canvas->TextOut(left_2, top, s.c_str());
     top += h;
     }
}
//------------------------------------------------------------------------------
void __fastcall TContactMenu::FormCreate(TObject *Sender)
{
if(MainFormSLS->ofs)
  if(MainFormSLS->ofs->elt)
    if(MainFormSLS->ofs->elt->getlog())
      {
      string TimeStr;
      TDateTime DateTime = DateTime.CurrentDateTime();
      exsDateTime(DateTime,TimeStr);
      string str = "\n" + (string)TimeStr + " TContactMenu_CREATED! " + "\n";
      MainFormSLS->ofs->elt->FputEvt(str, 1);
      }
}
//---------------------------------------------------------------------------

