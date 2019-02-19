#include <vcl.h>
#pragma hdrstop

#include "DialPad_Panel.h"
#include "SipClient_Unit.h"

#pragma package(smart_init)

#define input_top_margin        15
#define input_height            40
#define dig_img_width           80
#define dig_img_width_interval  2
#define dig_img_height          40
#define dig_img_height_interval 2
#define dig_string_top          2
//------------------------------------------------------------------------------
__fastcall TDial::TDial(TComponent* Owner)
           : TPanel(Owner)
{
Color      = clBtnFace; //clWhite; //clBtnFace;
Width      = 300;
Height     = 300;
BevelInner = bvNone;
BevelOuter = bvNone;
calc_input_left_margin();
CreatePanel();
CreateEdit();
}
//------------------------------------------------------------------------------
__fastcall TDialPad_Panel::TDialPad_Panel(TComponent* Owner)
           : TPanel(Owner)
{
Color      = clWhite; //clBtnFace;
BevelInner = bvNone;
BevelOuter = bvNone;
Visible    = false;
CreateDial();
OnKeyUp    = DialPad_Panel_KeyUp;
}
//------------------------------------------------------------------------------
void __fastcall TDialPad_Panel::ShowDialPad()
{
Top   = MainFormSLS->Panel1->Top  + MainFormSLS->Panel1->Height;
Left  = MainFormSLS->Panel1->Left;
resize();
Show();
}
//------------------------------------------------------------------------------
void __fastcall TDialPad_Panel::resize()
{
Width  = MainFormSLS->Panel1->Width;
Height = MainFormSLS->Panel_Chat->Top - MainFormSLS->Panel1->Top - MainFormSLS->Panel1->Height;
Dial->resize();
}
//-----------------------------------------------------------------------------
void __fastcall TDial::resize()
{
TDialPad_Panel* dpp = (TDialPad_Panel*)Parent;
Left = dpp->Width/2 - Width/2;
}
//-----------------------------------------------------------------------------
void __fastcall TDialPad_Panel::DialPad_Panel_KeyUp(TObject *Sender, WORD &Key, TShiftState Shift)
{
 if(Key == 27)
    Hide();
}
//-----------------------------------------------------------------------------
void __fastcall TDialPad_Panel::CreateDial()
{
Dial = new TDial(this);
Dial->Parent = this;
}
//-----------------------------------------------------------------------------
void __fastcall TDial::CreatePanel()
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
//-----------------------------------------------------------------------------
void __fastcall TDial::calc_input_left_margin()
{
input_left_margin = (Width - 3*dig_img_width - 2*dig_img_width_interval)/2;
}
//-----------------------------------------------------------------------------
void __fastcall TDial::PanelMouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
Clear_Digits_State();
}
//----------------------------------------------------------------------------
void __fastcall TDial::Clear_Digits_State()
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
void __fastcall TDial::CreateEdit()
{
Edit = new TEdit(Panel);
Edit->Parent      = Panel;
Edit->Font->Size  = 12;
Edit->Font->Style = Edit->Font->Style << fsBold;
Edit->Width       = Panel->Width - 4;
Edit->Top         = Panel->Height/2 - Edit->Height/2 + 2;
Edit->Left        = 2;
Edit->Ctl3D       = false;
Edit->BorderStyle = bsNone;
}
//--------------------------------------------------------------------------
void __fastcall TDial::CreateDigImg()
{       /*
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
*/
}
//----------------------------------------------------------------------------
void __fastcall TBtnImage::clear()
{
Canvas->Brush->Color = clWhite;
Canvas->FillRect(Rect(0,0,Width,Height));
}
//---------------------------------------------------------------------------
void __fastcall TDigImage::time_stmp()
{
dt = dt.CurrentDateTime();
}
//---------------------------------------------------------------------------


