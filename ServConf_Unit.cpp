//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ServConf_Unit.h"
#include "SipClient_Unit.h"

#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall TServConf_Panel::TServConf_Panel(TComponent* Owner,Lang lang,int width,int height)
           : TPanel(Owner)
{
ServConfPanel1_CONTACT_LIST_SIZE = 0;
conf_contacts.set_contact_list_size_pointer(&ServConfPanel1_CONTACT_LIST_SIZE);
lng = lang;
int left   = 5;
int top_lb = 17;

dg1 = new TDrawGrid(this);
dg1->Parent = this;

lb1 = new TLabel(this);
lb1->Parent = this;

dg1->Top   = 20;
dg1->Left  = left;
dg1->Width = width - left - 2;
dg1->FixedCols = 0;
dg1->FixedRows = 0;
dg1->ColCount  = 1;
dg1->ColWidths[0]  = dg1->Width;
dg1->GridLineWidth = 0;
dg1->ScrollBars    = ssNone; //ssVertical;
dg1->RowCount      = 1;
lb1->Left  = dg1->Left + dg1->Width/20;
lb1->Top   = dg1->Top - top_lb;
lb1->Font->Size = 10;

btn_ok = new TButton(this);
btn_ok->Parent = this;
btn_cancel = new TButton(this);
btn_cancel->Parent = this;

btn_ok->Top     = height  - btn_ok->Height - 20;
btn_ok->Left    = width/2 - btn_ok->Width - 10;
btn_ok->OnClick = OK_OnClick;

btn_cancel->Top  = btn_ok->Top;
btn_cancel->Left = width/2 + 10;
btn_cancel->OnClick = Cancel_OnClick;

dg1->Height = btn_ok->Top - dg1->Top - 20;

dg1->OnDrawCell = DG1DrawCell;

if(lng == Lang_RU)
  {
  lb1->Caption = "Участники конференции";
  btn_ok->Caption = "Старт";
  btn_cancel->Caption = "Отменить";
  }
 else
  {
  lb1->Caption = "Conference participants";
  btn_ok->Caption = "OK";
  btn_cancel->Caption = "Cancel";
  }
}
//----------------------------------------------------------------------------
void __fastcall TServConf_Panel::OK_OnClick(TObject* Sender)
{
}
//----------------------------------------------------------------------------
void __fastcall TServConf_Panel::Cancel_OnClick(TObject* Sender)
{
Visible = false;
MainFormSLS->set_req_to_close_conf_panel();
}
//----------------------------------------------------------------------------
void __fastcall TServConf_Panel::DG1DrawCell(TObject *Sender, int ACol,
                           int ARow, const TRect &Rect, TGridDrawState State)
{
if(State.Contains(gdFocused))
  {
  dg1->Canvas->Brush->Color = clActiveCaption;//clBlue;// clBackground;
  dg1->Canvas->Font->Color = clWhite;
  dg1->Canvas->FillRect(Rect);
  dg1->Canvas->DrawFocusRect(Rect);
  }
conf_contacts.Display(MainFormSLS->ImageList1, dg1, dg1->Canvas, ARow, Rect, State);
}
//---------------------------------------------------------------------------

