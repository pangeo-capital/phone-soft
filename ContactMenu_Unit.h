//---------------------------------------------------------------------------

#ifndef ContactMenu_UnitH
#define ContactMenu_UnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Grids.hpp>
#include <ExtCtrls.hpp>
#include <ImgList.hpp>
#include "WinRDefs.h"
#include "utils.h"
#include "contact.h"
#include "RBitMap.h"

class TDialPad;
class TProfileForm;
//---------------------------------------------------------------------------
class TElement{
public:
TLabel*  Label1;
TLabel*  Label2;
TLabel*  Label3;
};
//---------------------------------------------------------------------------
class TEditBox{
public:
TPanel*   Panel1;
TPanel*   Panel2;
TEdit*    Edit;
__fastcall TEditBox(TForm*,int,int,int,int);
};
//---------------------------------------------------------------------------
class TPartialContactData{
public:
bool actual;
string name;
string full_name;
__fastcall TPartialContactData(){
                                actual = false;
                                }
};
//---------------------------------------------------------------------------
class TProfileForm : public TForm{
void __fastcall __edit_contact();
public:
int       TYPE;
TContact* Contact; // Do not delete in destructor !!! Используется для добавления нового TContact ("Add External Contact")
TPartialContactData pd; // Для транзакций использовать TContactData ("Редактирование")
TElement* e1;
TElement* e2;

TEditBox* ed1;
TEditBox* ed2;

int left_1;
int left_2;
int font_sz;

TPanel*   Panel;
TButton*  Btn1;
        __fastcall  TProfileForm(TComponent* Owner,int Dummy);
virtual __fastcall ~TProfileForm(){
                               if(e1)
                                 delete e1;
                               if(e2)
                                 delete e2;
                               if(ed1)
                                 delete ed1;
                               if(ed2)
                                 delete ed2;
                               }
void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
void __fastcall Btn1Click(TObject *Sender);
void __fastcall Btn1Click_OnAddExtContact(TObject *Sender);
void __fastcall Btn1Click_OnEditContact(TObject *Sender);
void __fastcall FullName_KeyUp(TObject *Sender, WORD &Key, TShiftState Shift);

void __fastcall PrintNickName(int,const AnsiString&,const string&);
void __fastcall PrintFullName(int&,int,const AnsiString&,const string&);
void __fastcall PrintPosition(int&,int,const AnsiString&,const string&);
void __fastcall DrawUnderline(int&,int,TRBitMap&);
void __fastcall CheckWidth(queue<string>&,const string&);

void __fastcall EditProfile(TContact*);
void __fastcall EditProfile_OnOpenWindow(TContact*);
void __fastcall AddContactNameControls(TDialPad*);
};
//---------------------------------------------------------------------------
class TContactMenu : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel1;
        TDrawGrid *DrawGrid1;
        TImageList *ImageList1;
        void __fastcall DrawGrid1MouseMove(TObject *Sender,
          TShiftState Shift, int X, int Y);
        void __fastcall DrawGrid1DrawCell(TObject *Sender, int ACol,
          int ARow, TRect &Rect, TGridDrawState State);
        void __fastcall DrawGrid1MouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall FormKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall FormCreate(TObject *Sender);
private:	// User declarations
public:		// User declarations
Lang lng;
ContactType Selected_CT;
     __fastcall TContactMenu(TComponent* Owner);
void __fastcall DrawCell_For_CLIENT(int /*ARow*/, TRect& /*Rect*/, TGridDrawState /*State*/);
void __fastcall DrawCell_For_GROUP(int /*ARow*/, TRect& /*Rect*/, TGridDrawState /*State*/);
void __fastcall DrawCell_For_DIVISION(int /*ARow*/, TRect& /*Rect*/, TGridDrawState /*State*/);
};
//---------------------------------------------------------------------------
extern PACKAGE TContactMenu *ContactMenu;
//---------------------------------------------------------------------------
#endif
