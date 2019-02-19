//---------------------------------------------------------------------------

#ifndef AddContact_UnitH
#define AddContact_UnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TAddContact : public TForm
{
__published:	// IDE-managed Components
        TPageControl *PageControl1;
        TTabSheet *TabSheet1;
        TLabel *Label1;
        TLabel *Label2;
        TStaticText *StaticText1;
        TRichEdit *Contact_Name;
        TRichEdit *RichEdit3;
        TRichEdit *RichEdit4;
        TRichEdit *Display_Name;
        TRichEdit *RichEdit2;
        TLabel *Label3;
        TRichEdit *Work_Phone;
        TLabel *Label4;
        TRichEdit *Home_Phone;
        TLabel *Label5;
        TRichEdit *Mobile_Phone;
        TLabel *Label6;
        TRichEdit *Fax_Phone;
        TRichEdit *E_Mail;
        TLabel *Label7;
        TLabel *Label8;
        TButton *Button1;
        TButton *Button2;
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall FormResize(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
int po_Left;
int po_Top;
     __fastcall TAddContact(TComponent* Owner);
void __fastcall RichEditMouseUp(TObject *Sender,TMouseButton Button, TShiftState Shift, int X, int Y);
void __fastcall M_Show();
};
//---------------------------------------------------------------------------
extern PACKAGE TAddContact *AddContact;
//---------------------------------------------------------------------------
#endif
