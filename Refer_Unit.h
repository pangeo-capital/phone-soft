//---------------------------------------------------------------------------

#ifndef Refer_UnitH
#define Refer_UnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include "RBitMap.h"
#include <queue>
#include "wm_def.h"
#include "ContactMenu_Unit.h"

class TReferWin;
//---------------------------------------------------------------------------
class TBtnParameter{
public:
AnsiString S;
BtnState   bs;
int        w;
int        h;
int        text_left;
int        text_top;
__fastcall TBtnParameter(){
                          bs = BtnState_ACTIVE;
                          w = 0; h = 0; text_left = 0; text_top = 0;
                          }
};
//---------------------------------------------------------------------------
class TBtnStateThread : public TThread{
public:
TReferWin* win;
     __fastcall TBtnStateThread(bool CS, TReferWin* WIN):TThread(CS){
                               win = WIN;
                               }
bool __fastcall out_of_area(TImage*);                               
void __fastcall Execute();
};
//---------------------------------------------------------------------------
class TReferWin : public TForm
{
__published:	// IDE-managed Components
        TImage *Refer_Img;
        TImage *Refer_Ans_Img;
        void __fastcall Refer_ImgMouseMove(TObject *Sender,
          TShiftState Shift, int X, int Y);
        void __fastcall Refer_Ans_ImgMouseMove(TObject *Sender,
          TShiftState Shift, int X, int Y);
        void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
        void __fastcall Refer_ImgMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall Refer_Ans_ImgMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall Refer_ImgMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall Refer_Ans_ImgMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
private:	// User declarations
public:		// User declarations
string           refer_name;
TEditBox*        EditBox;
TBtnParameter    bp_1;
TBtnParameter    bp_2;
TBtnStateThread* BST;
        __fastcall TReferWin(TComponent* Owner);
void __fastcall create_BST();
void __fastcall delete_BST();        
void __fastcall refresh_btn_state(TImage*,BtnState);
void __fastcall set_focused(TImage*);
void __fastcall set_btn_state(TImage*,BtnState);
void __fastcall clear_btn(TImage*);
void __fastcall draw_btn_state(TImage*,TBtnParameter*);
void __fastcall change_state(TImage*,BtnState);
void __fastcall Get_REFER_BTN_MSG(TMessage &Message);
BEGIN_MESSAGE_MAP
MESSAGE_HANDLER(REFER_BTN_MSG, TMessage, Get_REFER_BTN_MSG);
END_MESSAGE_MAP(TForm)
};
//---------------------------------------------------------------------------
extern PACKAGE TReferWin *ReferWin;
//---------------------------------------------------------------------------
#endif
