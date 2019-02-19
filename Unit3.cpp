//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "WinRDefs.h"

#ifdef SIP_Video
#include "Unit4.h"
#include "Unit3.h"
#include "Unit_Video_Cap.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm3 *Form3;
//---------------------------------------------------------------------------
__fastcall TForm3::TForm3(TComponent* Owner)
        : TForm(Owner)
{
::InitializeCriticalSection(&f3_exch_list_cs);
::InitializeCriticalSection(&q_cs);
MF_Handle = MainFormSLS->Handle;
lng = Lang_RU;//Lang_EN;
call_in_progress = false;
close_request    = false;
video_call_tag   = 0;
leg_type         = Lt_NDef;
bitmap = new Graphics::TBitmap;
curWidth  = SC_default_Remote_ScreenWidth;
curHeight = SC_default_Remote_ScreenHeight;

dt_1_sec = TDateTime(0,0,1,0);
PrevVFrameTime = PrevVFrameTime.CurrentDateTime();
frame_count = 0;
resize_block = false;
psst              = passiveScreenSizeType_Unknown;
ResizeReq         = false;

block_hide_panel1      = false;
Prev_Start_Video_Show  = Prev_Start_Video_Show.CurrentDateTime();
Hide_Start_Video_Delay = TDateTime(0,0,2,0); //2 sec
prev_X = 0;
prev_Y = 0;

Panel1 = new TPanel(this);     //this string must be before Width  = curWidth because Event OnResize raised (Panel1 resize on not created object Panel1)
Panel1->Parent = this;
Panel1->BevelInner = bvLowered;
Panel1->BevelOuter = bvRaised;
Panel1->Color = clSilver;
Panel1->Visible = false;
Panel1->OnResize = Panel1Resize;

img1 = new TImage(Panel1);
img1->Parent = Panel1;
img1_size_position();
img1->OnMouseUp   = Img1MouseUp;
img1->OnMouseMove = Img1MouseMove;

LocalVideoPanel->Width  = 176;
LocalVideoPanel->Height = 144;
LocalVideoPanel_TopLeftCorn();
}
//---------------------------------------------------------------------------
void __fastcall TForm3::img1_size_position()
{
img1->Height = 26;
img1->Width  = 130;
img1->Left   = Panel1->Width/2 - img1->Width/2;
img1->Top    = Panel1->Height/2 - img1->Height/2;
ImageList1->Draw(img1->Canvas,0,0,0,true);
TRect TheRect;
img1->Canvas->Brush->Color = clRed;
img1->Canvas->Font->Color  = clWhite;
switch(lng){
      case Lang_EN:
           TheRect = Rect(15,3,112,20);
           img1->Canvas->Font->Height = 20;
           img1->Canvas->Font->Size   = 14;
           img1->Canvas->TextRect(TheRect, 15, 0, "Disconnect");
           img1->Canvas->FrameRect(TheRect);
           break;
      case Lang_RU:
           TheRect = Rect(5,3,118,20);
           img1->Canvas->Font->Height = 20;
           img1->Canvas->Font->Size   = 14;
           img1->Canvas->Font->Charset = RUSSIAN_CHARSET;
           img1->Canvas->TextRect(TheRect, 35, 0, "Отбой");
           img1->Canvas->FrameRect(TheRect);
           break;
      }
}
//---------------------------------------------------------------------------
void __fastcall TForm3::Panel1Resize(TObject *Sender)
{
if(!Panel1->Visible)return;
img1_size_position();
}
//---------------------------------------------------------------------------
void __fastcall TForm3::Img1MouseMove(TObject *Sender,TShiftState Shift, int X, int Y)
{
block_hide_panel1 = true;
}
//---------------------------------------------------------------------------
void __fastcall TForm3::Img1MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
TExchBuf* buf = new TExchBuf(WM_APP_MSG_WPARAM__VIDEOOUT);
if(buf)
  {
  LegType lt = get_leg_type();
  if(lt == Lt_Out)
     buf->emt = ExchMsgType_Video_Out_Disconnect;
  else if(lt == Lt_In)
     buf->emt = ExchMsgType_Video_In_Disconnect;
  buf->tag = get_video_call_tag();
  MainFormSLS->videoout_exchlst_insert(buf);
  ::PostMessage(MF_Handle, VIDEOOUT_MSG, WM_APP_MSG_WPARAM__VIDEOOUT, WM_APP_MSG_LPARAM__READLIST);
  }
if(Form4->Visible)
   Form4->Close();
call_in_progress = false;
if(Form4->devID != -1)
  {
  vcam_stop_device(Form4->devID);
  Form4->devID = -1;
  }
close_request = true;  
Close();   
}
//---------------------------------------------------------------------------
void __fastcall TForm3::FormResize(TObject *Sender)
{
panel1_resize();
LocalVideoPanel_TopLeftCorn();
}
//---------------------------------------------------------------------------
void __fastcall TForm3::LocalVideoPanel_TopLeftCorn()
{
LocalVideoPanel->Top  = Height - LocalVideoPanel->Height - 30;
LocalVideoPanel->Left = 3;
}
//---------------------------------------------------------------------------
void __fastcall TForm3::panel1_resize()
{
if(Panel1->Visible)
  {
  Panel1->Left = Width/2 - Panel1->Width/2;
  Panel1->Top  = Height - SC_vert_addition_F3;
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm3::FormMouseUp(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
if(MainFormSLS->app_minimized)
   {
   if( (Y < (Height - 144)) ||(X > 176))
     {
     Application->Restore();
     }
   }
if(!LocalVideoPanel->Visible)
  {
  if(Form2->Visible)
    return;
  if(X < 176)
    if(Y > (Height - 144))
      {
      Form4->devID = -1;
      vcam_init();
      Form4->select_vcam();
      if(Form4->devID != -1)
        {
        vcam_setup_device(Form4->devID,Form4->vcam_width,Form4->vcam_height);
        Form4->vcam_width     =  vcam_get_width(Form4->devID);
        Form4->vcam_height    =  vcam_get_height(Form4->devID);
        Form4->vcam_size      =  vcam_get_size(Form4->devID);
        if(Form4->vcam_size)
           Form4->vcam_frame.resize(Form4->vcam_size);
        }
      if(!Form4->bitmap)
        {
         Form4->bitmap = new Graphics::TBitmap;
         if(Form4->bitmap)
           {
           Form4->set_bitmap_size();
           Form4->bitmap->PixelFormat = pf24bit;
           Form4->bitmap->Canvas->Brush->Style = bsSolid;
           }
        }
      if(Form4->bitmap)
        if((!Form4->bitmap->Width)||(!Form4->bitmap->Height))
          {
          Form4->set_bitmap_size();
          Form4->bitmap->PixelFormat = pf24bit;
          Form4->bitmap->Canvas->Brush->Style = bsSolid;
          }
      LocalVideoPanel->Visible = true;
      if(!Form4->Timer1->Enabled)
         Form4->Timer1->Enabled = true;
      }
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm3::FormClose(TObject *Sender, TCloseAction &Action)
{
Timer1->Enabled = false;
clear_q();
if(bitmap)
  {
  delete bitmap;
  bitmap = NULL;
  }
curWidth  = SC_default_Remote_ScreenWidth;
curHeight = SC_default_Remote_ScreenHeight;
if(close_request)  //Request by end of session (button Disconnect)
   close_request = false;
else
   {
   MainFormSLS->Image_RemoteVideo->Visible = true;
   MainFormSLS->Image_RemoteVideo->Tag = get_video_call_tag();
   }
}
//---------------------------------------------------------------------------
void __fastcall TForm3::FormHide(TObject *Sender)
{
if(Form4->Visible)
   Form4->Hide();
}
//---------------------------------------------------------------------------
void __fastcall TForm3::push_block(TOutPutUdpBlock* opb)
{
::EnterCriticalSection(&q_cs);
  opb->incReferenceCount();
  q.push(opb);
::LeaveCriticalSection(&q_cs);
}
//---------------------------------------------------------------------------
TOutPutUdpBlock* __fastcall TForm3::get_first_vblock()
{
TOutPutUdpBlock* opb = NULL;
::EnterCriticalSection(&q_cs);
  if(!q.empty())
    {
    opb=q.front();
    q.pop();
    }
::LeaveCriticalSection(&q_cs);
return opb;
}
//---------------------------------------------------------------------------
int __fastcall TForm3::getSize()
{
int rv=0;
::EnterCriticalSection(&q_cs);
  rv=q.size();
::LeaveCriticalSection(&q_cs);
return rv;
}
//---------------------------------------------------------------------------
void __fastcall TForm3::clear_q()
{
::EnterCriticalSection(&q_cs);
  while(!q.empty())
       {
       TOutPutUdpBlock* opb = q.front();
       q.pop();
       opb->decReferenceCount();
       }
::LeaveCriticalSection(&q_cs);
}
//---------------------------------------------------------------------------
void __fastcall TForm3::Timer1Timer(TObject *Sender)
{
try{
Timer1->Enabled = false;
TDateTime curr_date_time = curr_date_time.CurrentDateTime();
if(Panel1->Visible)
  {
  if((curr_date_time - Prev_Start_Video_Show) > Hide_Start_Video_Delay)
     {
     block_hide_panel1 = false;
     Panel1->Hide();
     }
  else if((GetKeyState(VK_LBUTTON) & 0x80) == 0x80)
     {
     if(!block_hide_panel1)
        Panel1->Hide();
     }
  }

corrective_resize();
TOutPutUdpBlock* opb = get_first_vblock();
if(opb)
  {
  frame_count++;
  TDateTime curr_dt = curr_dt.CurrentDateTime();
  if((curr_dt - PrevVFrameTime) >= dt_1_sec)
    {
    PrevVFrameTime = curr_dt;
    Caption = "Remote Video  " + (AnsiString)inttostr(frame_count).c_str() + "  fps" ;
    frame_count = 0;
    }
  if(Visible)
    if(bitmap)
      {
      check_on_corrective_resize_req();
      set_bitmap_size(opb);
      int screen_size = vencdec_get_bgr24_buff_size( bitmap->Width, bitmap->Height);
      if((screen_size > 0)&&(screen_size < 10000000))
        {
        load_rcvd_frame_to_bitmap(opb);
        draw_bitmap_on_screen(Width,Height);
        }
      }
  opb->decReferenceCount();
  }
Timer1->Enabled = true;
}//try
catch(Exception& e){exsSstEXCEPTION(MainFormSLS->ofs->elt,"__Timer1Timer)",e);}
}
//---------------------------------------------------------------------------
void __fastcall TForm3::load_rcvd_frame_to_bitmap(TOutPutUdpBlock* opb)
{
int Y = 0;
int w_size = bitmap->Width*3;
for(int y = 0; y < bitmap->Height; y++)
   {
   Byte* ptr = (Byte *)bitmap->ScanLine[y];
   memcpy(ptr,&opb->v[Y],w_size);
   Y+=w_size;
   }
}
//---------------------------------------------------------------------------

void __fastcall TForm3::set_bitmap_size(TOutPutUdpBlock* opb)
{
if(bitmap)
  {
  if(bitmap->Width != opb->remote_yuv420_width)
     bitmap->Width = opb->remote_yuv420_width;
  if(bitmap->Height != opb->remote_yuv420_height)
     bitmap->Height = opb->remote_yuv420_height;
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm3::draw_bitmap_on_screen(int w,int h)
{
if(bitmap)
  {
  int width      = w;
  int height     = h;
  if(width & 1)  --width;
  if(height & 1) --height;
  TRect TheRect = Rect(0,0,width,height);
  Canvas->StretchDraw(TheRect, bitmap);
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm3::Prepare_Form3_Show()
{
Timer1->Enabled = false;
if(!bitmap)
    bitmap = new Graphics::TBitmap;
if(bitmap)
  {
  bitmap->PixelFormat = pf24bit;
  bitmap->Canvas->Brush->Style = bsSolid;
  Timer1->Enabled = true;
  }
}
//----------------------------------------------------------------------------
void __fastcall TForm3::Remote_Video_Show()
{
if(MainFormSLS->lng == Lang_RU)
   Caption = "Удаленная камера";
Prepare_Form3_Show();
Show();
}
//----------------------------------------------------------------------------
void __fastcall TForm3::check_on_corrective_resize_req()
{
if(resize_block)
   return;
if(WindowState == wsNormal)
  {
  if(curWidth != Width)
    {
    if((GetKeyState(VK_LBUTTON) & 0x80) == 0)  //Left Mouse Button is not pressed
       {
       curWidth  = Width;
       psst = passiveScreenSizeType_Height;
       ResizeReq = true;
       ResizeTime = ResizeTime.CurrentDateTime() + TDateTime(0,0,0,20);
       }
    }
  else if(curHeight != Height)
    {
    if((GetKeyState(VK_LBUTTON) & 0x80) == 0)  //Left Mouse Buttin is not pressed
      {
      curHeight = Height;
      psst = passiveScreenSizeType_Width;
      ResizeReq = true;
      ResizeTime = ResizeTime.CurrentDateTime() + TDateTime(0,0,0,20);
      }
    }
  }
else if(WindowState == wsMaximized)
 {
 curHeight = Height;
 curWidth  = Width;
 }
}
//---------------------------------------------------------------------------
void __fastcall TForm3::corrective_resize()
{
if(ResizeReq)
  if(ResizeTime.CurrentDateTime() > ResizeTime)
    {
    ResizeReq = false;
    if(psst == passiveScreenSizeType_Height)
       {
       Height    = (Width/1.33333);// + SC_vert_addition;  //Restore size 4:3
       curHeight = Height;
       curWidth  = Width;
       }
    else if(psst == passiveScreenSizeType_Width)
      {
      int a = Height;// - SC_vert_addition;
      Width = a * 1.33333;   //Restore size 4:3
      curWidth  = Width;
      curHeight = Height;
      }
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm3::FormMouseMove(TObject *Sender, TShiftState Shift,
      int X, int Y)
{
if(Panel1->Visible)
  {
  if((prev_X != X)||(prev_Y != Y))
     {
     Prev_Start_Video_Show = Prev_Start_Video_Show.CurrentDateTime();
     prev_X = X; prev_Y = Y;
     }
  }
else
  {
  if((prev_X != X)||(prev_Y != Y))
    {
    if(!resize_block)
      {
      panel1_initsize();
      Panel1->Show();
      Prev_Start_Video_Show = Prev_Start_Video_Show.CurrentDateTime();
      prev_X = X; prev_Y = Y;
      }
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm3::LocalVideoImageMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
if(LocalVideoPanel->Visible)
   LocalVideoPanel->Hide();
}
//---------------------------------------------------------------------------
void __fastcall TForm3::panel1_initsize()
{
Panel1->Top    = Height - 70;
Panel1->Height = 26;
Panel1->Width  = 114;
Panel1->Left   = Width/2 - Panel1->Width/2;
}
//---------------------------------------------------------------------------
void __fastcall TForm3::Get_REMOTE_VIDEO_MSG(TMessage &Message)
{
try{
TExchBuf* buf = _get_exch_buf();
while(buf){
     proc_remote_video_event(buf);
     delete buf;
     buf = _get_exch_buf();
     }
}//try
catch(Exception& e){exsSstEXCEPTION(MainFormSLS->ofs->elt,"__Get_CALLIN_MSG(TMessage &Message)",e);}
}
//---------------------------------------------------------------------------
void __fastcall TForm3::proc_remote_video_event(TExchBuf* buf)
{
switch(buf->emt){
       case ExchMsgType_Show_Remote_Video:
            show_remote_video(buf);
            break;
       case ExchMsgType_Update_Remote_Video:
            update_remote_video(buf);
            break;
      }
}
//-----------------------------------------------------------------------------
void __fastcall TForm3::show_remote_video(TExchBuf* buf)
{
Top    = Form4->Top;
Left   = Form4->Left;
Width  = Form4->Width;
Height = Form4->Height;
call_in_progress = true;
Form3->FormStyle = fsStayOnTop;
Remote_Video_Show();
if(buf->b1)
   LocalVideoPanel->Visible = true;
else
   LocalVideoPanel->Visible = false;
if(buf->a1)
  {
  TMediaSession* ms = MainFormSLS->Sip->sss->GetMs_by_In_Out_Callid(buf->callid);
  if(ms)
    {
    leg_type       = ms->get_leg_type();
    video_call_tag = ms->getCallTag();
    }
  }
if(Form4->Visible)
  {
  Form4->set_video_call_tag(0); //Reset video_call_tag for protect from change cam_img on TCall_Panel
  Form4->Close();
  }
}
//-----------------------------------------------------------------------------
void __fastcall TForm3::update_remote_video(TExchBuf* buf)
{
if(Form3->Visible)
  {
  if(buf->b1)
     LocalVideoPanel->Visible = true;
  else
     LocalVideoPanel->Visible = false;;
  }
}
//-----------------------------------------------------------------------------
TExchBuf* __fastcall TForm3::_get_exch_buf()
{
TExchBuf* buf = NULL;
::EnterCriticalSection(&f3_exch_list_cs);
  if(!f3_exch_list.empty())
    {
    buf = f3_exch_list.front();
    f3_exch_list.pop();
    }
::LeaveCriticalSection(&f3_exch_list_cs);
return buf;
}
//----------------------------------------------------------------------------
void __fastcall TForm3::ins_exch_buf(TExchBuf* buf)
{
::EnterCriticalSection(&f3_exch_list_cs);
  f3_exch_list.push(buf);
::LeaveCriticalSection(&f3_exch_list_cs);
}
//----------------------------------------------------------------------------
void __fastcall TForm3::_clear_f3_exch_list()
{
::EnterCriticalSection(&f3_exch_list_cs);
  while(!f3_exch_list.empty())
       {
       TExchBuf* buf = f3_exch_list.front();
       f3_exch_list.pop();
       if(buf)
         delete buf;
       }
::LeaveCriticalSection(&f3_exch_list_cs);
}
//------------------------------------------------------------------------------
//-- Do not make clear_q() here. clear_q makes on every event close F# window
//------------------------------------------------------------------------------
void __fastcall TForm3::FormDestroy(TObject *Sender)
{
_clear_f3_exch_list();
::DeleteCriticalSection(&f3_exch_list_cs);
::DeleteCriticalSection(&q_cs);
}
//--------------------------------------------------------------------------
#endif //#ifdef SIP_Video


