#include <vcl.h>
#pragma hdrstop

#include "CommentPanel.h"
#include "SipClient_Unit.h"
//------------------------------------------------------------------------------
__fastcall TCommentPanel::TCommentPanel(TComponent* Owner)
         : TPanel(Owner)
{
Font->Charset = RUSSIAN_CHARSET;
Color      = clInactiveCaption;
Width      = 354;
Height     = 30;
BevelInner = bvNone;
BevelOuter = bvNone;
Top        = MainFormSLS->Panel2->Top  + MainFormSLS->NSP->Top  + MainFormSLS->NSP->NSI->Top  + MainFormSLS->NSP->NSI->Height - 2;
Left       = MainFormSLS->Panel2->Left + MainFormSLS->NSP->Left + MainFormSLS->NSP->NSI->Left + MainFormSLS->NSP->NSI->Width;
create_edit();
create_img();
}
//------------------------------------------------------------------------------
void __fastcall TCommentPanel::create_edit()
{
edit = new TEdit(this);
edit->Parent   = this;
edit->Width    = Width - 30;
edit->Height   = 20;
edit->Top      = Height/2 - edit->Height/2 - 1;
edit->Left     = 5;
//edit->AutoSize = true;
//edit->AutoSelect = true;
edit->Font->Size = 10;
//edit->Font->Style = edit->Font->Style << fsItalic;
edit->Font->Pitch = fpDefault;
edit->Ctl3D    = false;
edit->BorderStyle = bsNone;
edit->Hint      = "Комментарий";
edit->ShowHint  = true;
edit->OnKeyUp   = Edit_OnKeyUp;
}
//------------------------------------------------------------------------------
void __fastcall TCommentPanel::create_img()
{
img = new TImage(this);
img->Parent = this;
img->Width  = 22;
img->Height = 22;
img->Left   = edit->Left + edit->Width + 2;
img->Top    = Height/2 - img->Height/2;

img->Canvas->Brush->Color = clGray; //clSilver; //(TColor)FOREGR_ACTIVE_GREEN;
img->Canvas->FillRect(Rect(0,0,img->Width,img->Height));
AnsiString S = "+";
img->Canvas->Font->Color = clWhite;
img->Canvas->Font->Size  = 22;
int tw = img->Canvas->TextWidth(S);
int th = img->Canvas->TextHeight(S);
int text_left = img->Width/2 - tw/2;
int text_top  = img->Height/2   - th/2;
img->Canvas->TextOut(text_left, text_top, S);
img->OnMouseUp = Img_OnMouseUp;
}
//-----------------------------------------------------------------------------
void __fastcall TCommentPanel::send_notify_comment()
{
AnsiString S = edit->Text;
if(!S.IsEmpty())
    MainFormSLS->NS.init_notify_comment_proc(S.c_str());
MainFormSLS->close_NSCP();
if(MainFormSLS->NSP)
  {
  if(S.IsEmpty())
    MainFormSLS->NSP->comment->Caption.SetLength(0);
  else
    {
    MainFormSLS->NSP->comment->Font->Color = (TColor)0x00E37506;
    MainFormSLS->NSP->comment->Font->Charset = RUSSIAN_CHARSET;
  //  MainFormSLS->NSP->comment->Caption     = "<< " + S + " >>";
   // MainFormSLS->NSP->comment->Caption     = "- << " + S + " >>";
    MainFormSLS->NSP->comment->Caption     = "\" " + S + " \"";

    MainFormSLS->NSP->comment->Visible     = true;
    MainFormSLS->NSP->Height               = 40;
    MainFormSLS->PageControl1->Top         = MainFormSLS->NSP->Top + MainFormSLS->NSP->Height + 2;
    MainFormSLS->Panel3->Top               = MainFormSLS->PageControl1->Top;

    
    MainFormSLS->NSP->comment->Hint        = S;
    MainFormSLS->NSP->comment->ShowHint    = true;
    }
  MainFormSLS->NS.set_my_net_state_comment(S.c_str());
  if(!S.IsEmpty())
    {
    if(MainFormSLS->Im.LCFT)  //Thread для работы с файлом содержащим последние вызовы (Last Calls)
      {
      TLCSBuf* LCSBuf = new TLCSBuf(SAVE_COMMENT);
      if(LCSBuf)
        {
        LCSBuf->s = S.c_str();
        MainFormSLS->Im.LCFT->push_lcs_buf(LCSBuf);
        }
      }
    }
  }
}
//-----------------------------------------------------------------------------
void __fastcall TCommentPanel::Img_OnMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
send_notify_comment();
}
//-----------------------------------------------------------------------------
void __fastcall TCommentPanel::Edit_OnKeyUp(TObject *Sender, WORD &Key, TShiftState Shift)
{
if(Key == 13) //Enter
   send_notify_comment();
}
//-----------------------------------------------------------------------------

