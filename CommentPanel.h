#ifndef Comment_Panel_Unit_H
#define Comment_Panel_Unit_H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TCommentPanel : public TPanel{
void __fastcall send_notify_comment();
public:
     __fastcall TCommentPanel(TComponent* Owner);
TEdit*  edit;
TImage* img;
void __fastcall create_edit();
void __fastcall create_img();
void __fastcall Img_OnMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
void __fastcall Edit_OnKeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
};
//---------------------------------------------------------------------------
#endif
