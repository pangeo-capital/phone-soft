//---------------------------------------------------------------------------

#ifndef About_UnitH
#define About_UnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TAboutWin : public TForm
{
__published:	// IDE-managed Components
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TButton *Button1;
    TImage *Image1;
    TLabel *Label4;
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TAboutWin(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TAboutWin *AboutWin;
//---------------------------------------------------------------------------
#endif
