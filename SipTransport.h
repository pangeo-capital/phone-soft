//---------------------------------------------------------------------------

#ifndef SipTransportH
#define SipTransportH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "WinRDefs.h"
//---------------------------------------------------------------------------
class TTransport : public TForm
{
__published:	// IDE-managed Components
        TComboBox *ComboBox1;
        TButton *Button1;
        TButton *Button2;
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TTransport(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TTransport *Transport;
//---------------------------------------------------------------------------
#endif
