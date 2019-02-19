#ifndef SC_RBITMAP_H
#define SC_RBITMAP_H
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <vector>
#include <map>

#ifndef UBYTE
typedef unsigned char UBYTE;
#endif

using namespace std;

#define BACKGR_WHITE         0xFFFFFF
#define FOREGR_ACTIVE_GREEN  0x2FAA2B //0x2FCA2B
#define FOREGR_FOCUSED_GREEN 0x2F8A2B //0x2FAA2B
#define FOREGR_PRESSED_GREEN 0x2F7A2B //0x2F8A2B
#define FOREGR_ACTIVE_YELLOW 0x1ABAFF //0x6BCAFF //0x1BCAFF  //0x1BCAEF //0x1B8AEF

#define FOREGR_ACTIVE_BLUE   0xE4AC22
#define FOREGR_FOCUSED_BLUE  0xE24B09

typedef enum{
BtnState_ACTIVE,
BtnState_FOCUSED,
BtnState_PRESSED,
BtnState_INACTIVE,
}BtnState;
//-----------------------------------------------------------------------------
class TXPar{
public:
int Y;
int X;
int a; //Дельта между данным X и последующим (используется на данный момент только для контурных кнопок)
__fastcall TXPar(){Y = 0; X = 0; a = 0;}
};
//-----------------------------------------------------------------------------
class TRBitMap{
typedef map < int, TXPar > TLines;
int WIDTH;
int HEIGHT;
int LAST_LINE; // == HEIGHT -1
int WIDTH_3;   //image width * 3 (RGB)
int R;         //Радиус закругления
vector<Byte> bgr;
vector<Byte> fgr;
vector<Byte> cntr;  //цвет конура - для контурных кнопок
TLines Lines;
void  __fastcall create_bmp();
void  __fastcall calc_circle_line_imgs();
void  __fastcall calc_contur_circle_line_imgs();
int   __fastcall calc_circle_line_img(int);
void  __fastcall prepare_color(vector<Byte>&,int);
void  __fastcall background(Byte*,int);
void  __fastcall foreground(Byte*,int);
void  __fastcall contur(Byte*,int);
void  __fastcall fill_bitmap();
void  __fastcall fill_bitmap_line(Byte*,int);
void  __fastcall calc_line_imgs();
void  __fastcall fill_line_bitmap();
void  __fastcall fill_contur_bitmap();
void  __fastcall fill_contur_bitmap_line(Byte*,int,int,int);
public:
Graphics::TBitmap* bmp;
      __fastcall TRBitMap(int,int,int,int);     //Constructor for circle
      __fastcall TRBitMap(int,int,int,int,int); //Constructor for contur btns
      __fastcall TRBitMap(int,int,int);         //Constructor for line
void  __fastcall prepare_line_img();
virtual ~TRBitMap(){
                   delete bmp;
                   }
};
//-----------------------------------------------------------------------------
namespace RBitMap{
void __fastcall change_color(int,int,TImage*);
void __fastcall change_color(int,int,Graphics::TBitmap*);
};
//-----------------------------------------------------------------------------
#endif
