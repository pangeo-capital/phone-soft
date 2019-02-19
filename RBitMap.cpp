#include "RBitMap.h"
#include <math.h>
//(TColor)0x001BCAEF;  желтый

//---------------------------------------------------------------------------
//----------------------- Constructor for circle ----------------------------
//---------------------------------------------------------------------------
__fastcall TRBitMap::TRBitMap(int w, int h, int backgr, int foregr)
{
if(w & 1) --w;
if(h & 1) --h;
WIDTH     = w;
HEIGHT    = h;
R         = h/2;
LAST_LINE = h - 1;
WIDTH_3   = w*3; // (RGB)
prepare_color(bgr,backgr);
prepare_color(fgr,foregr);
create_bmp();
calc_circle_line_imgs();
fill_bitmap();
}
//--------------------------------------------------------------------------
//------------------------ Constructor for Contur Btn ----------------------
//--------------------------------------------------------------------------
__fastcall TRBitMap::TRBitMap(int w, int h, int backgr, int contur, int foregr)
{
if(w & 1) --w;
if(h & 1) --h;
WIDTH     = w;
HEIGHT    = h;
R         = h/2;
LAST_LINE = h - 1;
WIDTH_3   = w*3; // (RGB)
prepare_color(bgr,backgr);
prepare_color(cntr,contur);
prepare_color(fgr,foregr);
create_bmp();
calc_contur_circle_line_imgs();
fill_contur_bitmap();
}
//--------------------------------------------------------------------------
//------------------------ Constructor for line ----------------------------
//--------------------------------------------------------------------------
__fastcall TRBitMap::TRBitMap(int w, int h, int foregr)
{
WIDTH     = w;
HEIGHT    = h;
WIDTH_3   = w*3; // (RGB)
prepare_color(fgr,foregr);
create_bmp();
}
//-----------------------------------------------------------------------------
void __fastcall TRBitMap::prepare_line_img()
{
calc_line_imgs();
fill_line_bitmap();
}
//-----------------------------------------------------------------------------
void __fastcall TRBitMap::create_bmp()
{
bmp = new Graphics::TBitmap;
bmp->PixelFormat = pf24bit;
bmp->Width       = WIDTH;
bmp->Height      = HEIGHT;
}
//--------------------------------------------------------------------------
void __fastcall TRBitMap::fill_bitmap()
{
for(int Y = 0; Y < bmp->Height; Y++)
   {
    Byte* ptr = (Byte*)bmp->ScanLine[Y];
    TXPar A = Lines[Y];
    fill_bitmap_line(ptr, A.X*3);
    }
}
//--------------------------------------------------------------------------
void __fastcall TRBitMap::fill_bitmap_line(Byte* ptr, int X_3)
{
for(int x = 0; x < WIDTH_3; x += 3)
   {
   if((x < X_3)||(x >= WIDTH_3 - X_3))
       background(&ptr[x],x);
   else
       foreground(&ptr[x],x);
   }
}
//--------------------------------------------------------------------------
void  __fastcall TRBitMap::fill_contur_bitmap()
{
for(int Y = 0; Y < bmp->Height; Y++)
   {
    Byte* ptr = (Byte*)bmp->ScanLine[Y];
    TXPar A = Lines[Y];
    fill_contur_bitmap_line(ptr, A.X*3, A.a, Y);
    }
}
//--------------------------------------------------------------------------
void __fastcall TRBitMap::prepare_color(vector<Byte>& v,int a)
{
for(int i = 0; i < 3; i++)
    v.push_back(a >> 16 - 8*i);
}
//-------------------------------------------------------------------------
void __fastcall TRBitMap::background(Byte* ptr, int x)
{
for(int i = 0; i < 3; i++)
   *(ptr + i) = bgr[i];
}
//------------------------------------------------------------------------
void __fastcall TRBitMap::contur(Byte* ptr, int x)
{
for(int i = 0; i < 3; i++)
   *(ptr + i) = cntr[i];
}
//------------------------------------------------------------------------
void __fastcall TRBitMap::foreground(Byte* ptr, int x)
{
for(int i = 0; i < 3; i++)
   *(ptr + i) = fgr[i];
}
//------------------------------------------------------------------------
int __fastcall TRBitMap::calc_circle_line_img(int Y)
{
double X = R - sqrt(R*R - (R - Y)*(R - Y));
if((X - floor(X)) < 0.5)
   return  floor(X);
return ceil(X);
}
//--------------------------------------------------------------------------
void  __fastcall TRBitMap::calc_circle_line_imgs()
{
int count = HEIGHT/2;
for(int Y = 0;Y < count; Y++)
   {
   int X = calc_circle_line_img(Y);
   TXPar A;
   A.X = X;
   Lines.insert(TLines::value_type(Y,A));
   Lines.insert(TLines::value_type(LAST_LINE - Y,A));
   }
}
//----------------------------------------------------------------------------
void  __fastcall TRBitMap::calc_line_imgs()
{
for(int Y = 0;Y < HEIGHT; Y++)
   {
   TXPar A;
   A.X = WIDTH;
   Lines.insert(TLines::value_type(Y,A));
   }
}
//----------------------------------------------------------------------------
void __fastcall TRBitMap::fill_line_bitmap()
{
for(int Y = 0; Y < bmp->Height; Y++)
   {
    Byte* ptr = (Byte*)bmp->ScanLine[Y];
    TXPar A = Lines[Y];
    for(int x = 0; x < WIDTH_3; x += 3)
        foreground(&ptr[x],x);
    }
}
//--------------------------------------------------------------------------
void  __fastcall TRBitMap::calc_contur_circle_line_imgs()
{
vector<TXPar> v;
int count = HEIGHT/2;
for(int Y = 0;Y < count; Y++)
   {
   int X = calc_circle_line_img(Y);
   TXPar A;
   A.Y = Y;
   A.X = X;
   v.push_back(A);
   }
int sz = v.size();
for(int i = 0;i < sz;i++)  //В верхней и нижней половине точки рисуются как отрезки прямых (a - разница по горизотали между между началами двух соседних линий )
   {
   if(i)
     {
     int a = v[i-1].X - v[i].X;
     v[i-1].a = a;
     }
   }
for(int i = 0;i < sz;i++)
   {
   Lines.insert(TLines::value_type(v[i].Y, v[i]));
   Lines.insert(TLines::value_type(LAST_LINE - v[i].Y, v[i]));
   }
}
//-----------------------------------------------------------------------------------
void __fastcall TRBitMap::fill_contur_bitmap_line(Byte* ptr, int X_3, int a, int Y)
{
int a_3 = a*3;
int X_3_a_3 = X_3 - a_3;

if((Y == 0)||(Y == LAST_LINE))
  {
  for(int x = 0; x < WIDTH_3; x += 3)
     {
     if((x < X_3 - a_3)||(x > WIDTH_3 - X_3_a_3))
        background(&ptr[x],x);
     else
        contur(&ptr[x],x);
     }
  return;
  }

if(X_3 == 0)
  {
  for(int x = 0; x < WIDTH_3; x += 3)
     {
     if((x == X_3) || (x == WIDTH_3 - 3))
       contur(&ptr[x],x);
     else if((x < X_3)||(x > WIDTH_3 - 3))
       background(&ptr[x],x);
     else
       foreground(&ptr[x],x);
     }
  return;
  }

if(a == 0)
  {
  for(int x = 0; x < WIDTH_3; x += 3)
     {
     if((x == X_3) || (x == WIDTH_3 - X_3))
       contur(&ptr[x],x);
     else if((x < X_3)||(x > WIDTH_3 - X_3))
       background(&ptr[x],x);
     else
       foreground(&ptr[x],x);
     }
  return;
  }

if(X_3_a_3 == 0)
  {
  for(int x = 0; x < WIDTH_3; x += 3)
     {
     if((x == X_3)||(x == WIDTH_3 - X_3))
       contur(&ptr[x],x);
     else if((x < X_3)||(x > WIDTH_3 - X_3))
       background(&ptr[x],x);
     else
       foreground(&ptr[x],x);
     }
   return;
   }

if(X_3_a_3 == 3)
  {
  for(int x = 0; x < WIDTH_3; x += 3)
     {
     if((x == X_3) || (x == WIDTH_3 - X_3))
       contur(&ptr[x],x);
     else if((x < X_3)||(x > WIDTH_3 - X_3))
       background(&ptr[x],x);
     else
       foreground(&ptr[x],x);
     }
   return;
   }

for(int x = 0; x < WIDTH_3; x += 3)
   {
   if((x < X_3_a_3) ||(x > WIDTH_3 - X_3_a_3))
     background(&ptr[x],x);
   else if((x >= X_3) && (x <= WIDTH_3 - X_3))
     foreground(&ptr[x],x);
   else
     contur(&ptr[x],x);
   }
}
//-----------------------------------------------------------------------------
//---- Color must be presented int 24 bit format ------------------------------
//-----------------------------------------------------------------------------
void __fastcall RBitMap::change_color(int src, int dst, TImage* img)
{
change_color(src, dst, img->Picture->Bitmap);
img->Refresh();
}
//------------------------------------------------------------------------------------
//-- На данный момент работаем только с bmDIB(при получении Bitmap от TImage)
//-- При получении Bitmap от TImageList по GetBitmap() Graphics::TBitMap*  gjkexftv
//-- с установленным  HandleType == bmDDB. В результате изменения цвета не происходит
//-- хотя ptr[j], ptr[j+1],  ptr[j+2] показывают измененные состояния.
//-- Попытка принудительно установить  HandleType = bmDШB приводит к искажению
//-- в цветопередаче
//-----------------------------------------------------------------------------------
void __fastcall RBitMap::change_color(int src, int dst, Graphics::TBitmap* bmp)
{
if(bmp->HandleType == bmDIB) //Device Independent Bitmap
  {
  UBYTE rez[3];
  rez[0] = dst >> 16;
  rez[1] = dst >> 8;
  rez[2] = dst;
  for (int y = 0; y < bmp->Height; y++)
      {
      Byte* ptr = (Byte*)bmp->ScanLine[y];
      for (int x = 0,j=0; x < bmp->Width; x++, j+=3)
          {
          int a  = ptr[j]   << 16;
              a |= ptr[j+1] << 8;
              a |= ptr[j+2];
          if(a == src)
            {
            ptr[j]   = rez[0];
            ptr[j+1] = rez[1];
            ptr[j+2] = rez[2];
            }
          }
      }
  }
}
//------------------------------------------------------------------------------

