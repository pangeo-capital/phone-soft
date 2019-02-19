//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "WinRDefs.h"
#include "AddContact_Unit.h"
#include "SipClient_Unit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

const string display_name_default = " Имя, которое будет отображаться в списке контактов";
TAddContact *AddContact;
//---------------------------------------------------------------------------
__fastcall TAddContact::TAddContact(TComponent* Owner)
        : TForm(Owner)
{
po_Left  = -1;
po_Top   = -1;
Height   = 350;
Width    = 685;

int left_lbl     = 5;
int v_shift_lbl  = 3;
int left_edit    = 120;
int top_edit     = 24;
int width_int    = 0;
int height_int   = 0;
int height_int_1 = 20;
int height_edit  = 22;

Label1->Left = left_lbl;
Label2->Left = left_lbl;
Label3->Left = left_lbl;
Label4->Left = left_lbl;
Label5->Left = left_lbl;
Label6->Left = left_lbl;
Label7->Left = left_lbl;
Label8->Left = left_lbl;

Contact_Name->Height = height_edit;
RichEdit2->Height    = height_edit;
RichEdit3->Height    = height_edit;
RichEdit4->Height    = height_edit;
Display_Name->Height = height_edit;
Work_Phone->Height   = height_edit;
Home_Phone->Height   = height_edit;
Mobile_Phone->Height = height_edit;
Fax_Phone->Height    = height_edit;
E_Mail->Height       = height_edit;


Contact_Name->Clear();
RichEdit2->Clear();
RichEdit3->Clear();
RichEdit4->Clear();
Display_Name->Clear();
Work_Phone->Clear();
Home_Phone->Clear();
Mobile_Phone->Clear();
Fax_Phone->Clear();
E_Mail->Clear();

Contact_Name->Top  = top_edit;
RichEdit2->Top     = Contact_Name->Top + Contact_Name->Height + height_int;
RichEdit3->Top     = RichEdit2->Top;
RichEdit4->Top     = RichEdit2->Top;
Display_Name->Top  = RichEdit4->Top    + RichEdit4->Height    + height_int;
Work_Phone->Top    = Display_Name->Top + Display_Name->Height + height_int_1;
Home_Phone->Top    = Work_Phone->Top   + Work_Phone->Height   + height_int;
Mobile_Phone->Top  = Home_Phone->Top   + Home_Phone->Height   + height_int;
Fax_Phone->Top     = Mobile_Phone->Top + Mobile_Phone->Height + height_int;
E_Mail->Top        = Fax_Phone->Top    + Fax_Phone->Height    + height_int;

Contact_Name->Width  = 175;
RichEdit2->Width     = Contact_Name->Width;
RichEdit3->Width     = Contact_Name->Width;
RichEdit4->Width     = Contact_Name->Width;
Work_Phone->Width    = Contact_Name->Width;
Home_Phone->Width    = Contact_Name->Width;
Mobile_Phone->Width  = Contact_Name->Width;
Fax_Phone->Width     = Contact_Name->Width;
E_Mail->Width        = Contact_Name->Width;

Contact_Name->Left = left_edit;
RichEdit2->Left    = left_edit;
RichEdit3->Left    = RichEdit2->Left + RichEdit2->Width + width_int;
RichEdit4->Left    = RichEdit3->Left + RichEdit3->Width + width_int;
Display_Name->Left = left_edit;
Work_Phone->Left   = left_edit;
Home_Phone->Left   = left_edit;
Mobile_Phone->Left = left_edit;
Fax_Phone->Left    = left_edit;
E_Mail->Left       = left_edit;

Display_Name->Width  = RichEdit4->Left + RichEdit4->Width - Display_Name->Left;

Contact_Name->Color = clInactiveCaption;
RichEdit2->Color    = clBtnFace;
RichEdit3->Color    = clBtnFace;
RichEdit4->Color    = clBtnFace;
Display_Name->Color = clBtnFace;
Work_Phone->Color   = clBtnFace;
Home_Phone->Color   = clBtnFace;
Mobile_Phone->Color = clBtnFace;
Fax_Phone->Color    = clBtnFace;
E_Mail->Color       = clBtnFace;

Contact_Name->Font->Color = clWhite;
RichEdit2->Font->Color    = clGray;
RichEdit3->Font->Color    = clGray;
RichEdit4->Font->Color    = clGray;
Display_Name->Font->Color = clGray;

Label1->Top = Contact_Name->Top + v_shift_lbl;
Label2->Top = RichEdit2->Top    + v_shift_lbl;
Label3->Top = Display_Name->Top + v_shift_lbl;
Label4->Top = Work_Phone->Top   + v_shift_lbl;
Label5->Top = Home_Phone->Top   + v_shift_lbl;
Label6->Top = Mobile_Phone->Top + v_shift_lbl;
Label7->Top = Fax_Phone->Top    + v_shift_lbl;
Label8->Top = E_Mail->Top       + v_shift_lbl;

Label1->Color = clInactiveCaption;
Label1->Font->Height = 18;
Label1->Font->Color = clWhite;
Label2->Font->Height = 18;
Label3->Font->Height = 18;

Contact_Name->Lines->Add(" name  или  name@domain.com");
RichEdit2->Lines->Add(" Фамилия");
RichEdit3->Lines->Add(" Имя");
RichEdit4->Lines->Add(" Отчество");
Display_Name->Lines->Add(display_name_default.c_str());

Contact_Name->OnMouseUp = RichEditMouseUp;
RichEdit2->OnMouseUp    = RichEditMouseUp;
RichEdit3->OnMouseUp    = RichEditMouseUp;
RichEdit4->OnMouseUp    = RichEditMouseUp;
Display_Name->OnMouseUp = RichEditMouseUp;
Work_Phone->OnMouseUp   = RichEditMouseUp;
Home_Phone->OnMouseUp   = RichEditMouseUp;
Mobile_Phone->OnMouseUp = RichEditMouseUp;
Fax_Phone->OnMouseUp    = RichEditMouseUp;
E_Mail->OnMouseUp       = RichEditMouseUp;
}
//---------------------------------------------------------------------------
void __fastcall TAddContact::M_Show()
{
if(po_Left == -1)
  Position = poScreenCenter;
Show();
}
//---------------------------------------------------------------------------
void __fastcall TAddContact::FormClose(TObject *Sender,
      TCloseAction &Action)
{
po_Left = Left;
po_Top  = Top;
}
//---------------------------------------------------------------------------
void __fastcall TAddContact::RichEditMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
TRichEdit* re = (TRichEdit*)Sender;
if(!re->Tag)
  {
  re->Clear();
  re->Color = clWhite;
  re->Font->Color = clBlack;
  re->Tag = 1;  //RichEdit Active
  }
}
//---------------------------------------------------------------------------
void __fastcall TAddContact::FormResize(TObject *Sender)
{
int dt = 80;
PageControl1->Top    = 0;
PageControl1->Left   = 0;
PageControl1->Width  = Width;
PageControl1->Height = Height - dt;

Button1->Width  = 100;
Button1->Height = dt/3;
Button1->Left = Width - Button1->Width - 20;
Button1->Top  = PageControl1->Height + 10;

Button2->Width  = Button1->Width;
Button2->Height = Button1->Height;
Button2->Top    = Button1->Top;
Button2->Left   = Button1->Left - Button2->Width - 20;
}
//---------------------------------------------------------------------------
void __fastcall TAddContact::Button2Click(TObject *Sender)
{
if(Contact_Name->Lines->Count)
  {
   string s = Contact_Name->Lines->Strings[0].c_str();
   if(!MainFormSLS->Sip->Contacts.is_contact_exists(s))
     {
     TContact* Cont = new TContact(MainFormSLS->Sip->Contacts.get_next_contact_id());
     if(Cont)
       {
       Cont->name = s;
       if(Display_Name->Lines->Count)
          Cont->full_name = Display_Name->Lines->Strings[0].c_str();
       if(Cont->full_name.empty())
          Cont->full_name = Cont->name;
       else if(Cont->full_name == display_name_default)
          Cont->full_name = Cont->name;
       MainFormSLS->Sip->Contacts.add_contact(Cont, MainFormSLS->DrawGrid1, true);
       MainFormSLS->Sip->update_contact_file();
       }
     }
  }
Close();
}
//---------------------------------------------------------------------------
void __fastcall TAddContact::Button1Click(TObject *Sender)
{
Close();
}
//---------------------------------------------------------------------------
//#endif //#ifndef Enterprise_Edition

