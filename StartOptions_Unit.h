//---------------------------------------------------------------------------

#ifndef StartOptions_UnitH
#define StartOptions_UnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <string>

using namespace std;
//---------------------------------------------------------------------------
class TStartOptionsWin : public TForm
{
__published:	// IDE-managed Components
        TCheckBox *CheckBox1;
        TButton *Button1;
        TButton *Button2;
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
private:	// User declarations
std::string __fastcall get_app_name(const std::string&);
bool        __fastcall not_changed();
public:		// User declarations
bool OnChowChecked;
        __fastcall TStartOptionsWin(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TStartOptionsWin *StartOptionsWin;
//---------------------------------------------------------------------------
#endif
