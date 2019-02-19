//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "About_Unit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
#include "SipClient_Unit.h"
TAboutWin *AboutWin;
//---------------------------------------------------------------------------
__fastcall TAboutWin::TAboutWin(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TAboutWin::Button1Click(TObject *Sender)
{
Close();        
}
//---------------------------------------------------------------------------
void __fastcall TAboutWin::FormShow(TObject *Sender)
{
Top  = MainFormSLS->Top  + 55;
Left = MainFormSLS->Left + 160;
}
//---------------------------------------------------------------------------


