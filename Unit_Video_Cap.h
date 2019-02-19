//---------------------------------------------------------------------------

#ifndef Unit_Video_CapH
#define Unit_Video_CapH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include <vector>
#include "vencdec.h"
#include "vencpar.h"

#ifndef UBYTE
typedef unsigned char UBYTE;
#endif

using namespace std;
//---------------------------------------------------------------------------
class TForm2 : public TForm
{
string __selected_current;
void __fastcall __write_registry();
__published:	// IDE-managed Components
        TPanel *Panel1;
        TTimer *Timer1;
        TButton *Button2;
        TButton *Button3;
        TButton *Button4;
        TButton *Button5;
        TComboBox *ComboBox1;
        TLabel *Label1;
        TButton *Button1;
        TButton *Button6;
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall Button3Click(TObject *Sender);
        void __fastcall Button4Click(TObject *Sender);
        void __fastcall Button5Click(TObject *Sender);
        void __fastcall FormResize(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormHide(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall ComboBox1KeyPress(TObject *Sender, char &Key);
        void __fastcall ComboBox1KeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
        void __fastcall ComboBox1Click(TObject *Sender);
        void __fastcall Button6Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
HWND hWndC;
bool close_query;
int  vcam_width;
int  vcam_height;
int  vcam_size;
bool ResizeReq;
TDateTime ResizeTime;
vector<UBYTE>      vcam_frame;
Graphics::TBitmap* bitmap;
TVencPar           venc_par;
     __fastcall TForm2(TComponent* Owner);
void __fastcall prepare_frame_to_send(vector<UCHAR>&);     
void __fastcall set_bitmap_size();
void __fastcall load_vcam_frame_to_bitmap();
void __fastcall draw_bitmap_on_screen();
};
//---------------------------------------------------------------------------
extern PACKAGE TForm2 *Form2;
//---------------------------------------------------------------------------
#endif
