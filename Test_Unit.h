//---------------------------------------------------------------------------

#ifndef Test_UnitH
#define Test_UnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "WinRDefs.h"
//---------------------------------------------------------------------------
class TTest : public TForm
{
__published:	// IDE-managed Components
        TCheckBox *Local_Video_Rtp_Loop;
        TCheckBox *Remote_Video_Rtp_Loop;
        TButton *Button1;
        TComboBox *ComboBox1;
        TCheckBox *Fps;
        TCheckBox *Auto_Answer;
        void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TTest(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TTest *Test;
//---------------------------------------------------------------------------
#endif
