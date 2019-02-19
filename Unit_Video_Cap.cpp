//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "WinRDefs.h"
#include "Unit_Video_Cap.h"
#include <vfw.h>
#include "Unit4.h"
#include "Unit3.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
        : TForm(Owner)
{
hWndC       = 0;
close_query = false;
vcam_width  = 0;
vcam_height = 0;
vcam_size   = 0;
bitmap      = NULL;
ResizeReq   = false;
Button1->Caption = "Управление камерой";
Button3->Left = 50;
Button2->Left = Button3->Left + Button3->Width + Button3->Width/2;
ComboBox1->Width = ComboBox1->Width + ComboBox1->Width/2;
ComboBox1->Style = Stdctrls::csDropDown;
Label1->Font->Style = Label1->Font->Style << fsUnderline;
Label1->Caption  = "Видео камера";
Width = 480;
#ifndef VIDEO_CAP_WITH_WINDOWS_FUNC
Button2->Visible = false;
Button3->Visible = false;
Button4->Visible = false;
Button5->Visible = false;
#endif
Button6->Width = Button1->Width;
//Position = poScreenCenter;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Timer1Timer(TObject *Sender)
{
Timer1->Enabled = false;
if(close_query)
  return;

#ifdef VIDEO_CAP_WITH_WINDOWS_FUNC
SendMessage(hWndC, WM_CAP_GRAB_FRAME, 0, 0L);    // Only 0,0
#else
//corrective_resize();
if(Form4->devID != -1)
 if(vcam_is_frame_new(Form4->devID))
   {
   //check_on_corrective_resize_req();
   vcam_get_pixels( Form4->devID,  &vcam_frame[0], false, true );

                         //  prepare_frame_to_send(vcam_frame);
  
   if(Visible)
     if(bitmap)
       if(bitmap->Width)
         if(bitmap->Height)
          {
          int screen_size = vencdec_get_bgr24_buff_size( bitmap->Width, bitmap->Height);
          if((screen_size > 0)&&(screen_size < 10000000))
            {
            load_vcam_frame_to_bitmap();
            draw_bitmap_on_screen();
            }
          }
   }
#endif
Timer1->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Button2Click(TObject *Sender)
{
capDlgVideoFormat(hWndC);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Button3Click(TObject *Sender)
{
capDlgVideoSource(hWndC);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Button4Click(TObject *Sender)
{
char szName[128];
capFileGetCaptureFile( hWndC,szName,128);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Button5Click(TObject *Sender)
{
//int size = capGetVideoFormatSize(hWndC);
//capDlgVideoCompression(hWndC);
capDlgVideoDisplay(hWndC);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::FormResize(TObject *Sender)
{ /*
Panel1->Top = 0;
Panel1->Left = 0;
*/
//Panel1->Width = 10;

ComboBox1->Top = Height - 70;
Label1->Top    = ComboBox1->Top - 20;
Button1->Top   = Height  - 75;
Button3->Top   = Button1->Top;
Button2->Top   = Button3->Top;

Repaint();
}
//---------------------------------------------------------------------------
void __fastcall TForm2::FormCreate(TObject *Sender)
{
//Width = Panel1->Width- 100;
}
//---------------------------------------------------------------------------

void __fastcall TForm2::FormHide(TObject *Sender)
{
SendMessage(Form2->hWndC, WM_CAP_DRIVER_DISCONNECT, 0, 0L);
}
//---------------------------------------------------------------------------
void __fastcall TForm2::ComboBox1KeyPress(TObject *Sender, char &Key)
{
Key = 0;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::ComboBox1KeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
Key = 0;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Button1Click(TObject *Sender)
{
string s = ComboBox1->Text.c_str();
if(s.find("Logitech") != -1)
  {
  string file_name = "C:\\Windows\\SysWOW64\\LogiDPPApp.exe";
  if(FileExists(file_name.c_str()))
     ShellExecute(Handle, "open", file_name.c_str(), NULL, NULL, SW_SHOWNORMAL);
  }
else
  {
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm2::set_bitmap_size()
{
if(bitmap)
  {
  bitmap->Width  = vcam_width;
  bitmap->Height = vcam_height;
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm2::load_vcam_frame_to_bitmap()
{
int Y = 0;
int w_size = bitmap->Width*3;
for(int y = 0; y < bitmap->Height; y++)
   {
   Byte* ptr = (Byte *)bitmap->ScanLine[y];
   memcpy(ptr,&vcam_frame[Y],w_size);
   Y += w_size;
   }
}
//---------------------------------------------------------------------------
void __fastcall TForm2::draw_bitmap_on_screen()
{
if(bitmap)
  {
  int width      = Width;
  int height     = Height - 100;
  if(width & 1)  --width;
  if(height & 1) --height;
  TRect TheRect = Rect(0,0,width,height);
  Canvas->StretchDraw(TheRect, bitmap);
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm2::FormCloseQuery(TObject *Sender, bool &CanClose)
{
if(!__selected_current.empty())
   Form4->vcam_user_selected = __selected_current;
close_query = true;
Form4->vcam_reinit_req = true;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::FormClose(TObject *Sender, TCloseAction &Action)
{
#ifndef VIDEO_CAP_WITH_WINDOWS_FUNC
if((!Form3->call_in_progress) &&  (!Form4->Visible) && (!(Form3->Visible && Form3->LocalVideoPanel->Visible)))
   Form4->deactivate_selected_video_camera();
if(bitmap)
  {
  delete bitmap;
  bitmap = NULL;
  }
#endif
}
//---------------------------------------------------------------------------
//-- Перед вызовом окна TForm2 были закрыты Form4 и Form3->LocalVideoPanel
//-- если событие TForm2->FormShow() пришло раньше, чем закрылись окна
//-- то из FormShow() происходит выход и надо повторно вызвать TForm2
//-- (!!! не делать Close() - Excception)
//--------------------------------------------------------------------------
void __fastcall TForm2::FormShow(TObject *Sender)
{
if(Form4->Visible)
   return;
if(Form3->Visible)
   if(Form3->LocalVideoPanel->Visible)
      return;
close_query = false;
bool user_selected_camera_is_connected = false;
ComboBox1->Clear();
Form4->devID = -1;    //!!!
vcam_init();
Form4->select_vcam();
queue<string> q;
Form4->get_all_device_name(q);
bool selected = false;
while(!q.empty())
     {
     string s = q.front();
     q.pop();
     ComboBox1->Items->Add(s.c_str());
     if(!selected)
       {
       if(!Form4->get_vc_user_selected())
         {
         if(Form4->vcam_selected_auto == s)
           {
         __selected_current = s;
           AnsiString S     = s.c_str();
           Caption = "Видео: \"" + S + "\"";
           ComboBox1->Text  = S;
           selected = true;
           }
         }
       else
         {
         if(Form4->vcam_user_selected == s)
           {
           user_selected_camera_is_connected = true;
           Caption = "Видео: \"" + (AnsiString)s.c_str() + "\"";
         __selected_current = Form4->vcam_user_selected;
           ComboBox1->Text  = __selected_current.c_str();
           selected = true;
           }
         }
       }
     }

if(Form4->get_vc_user_selected())
  {
  if(Form4->devID == -1)          //Камера с данным именем выбрана пользователем, но ее нет в списке подключенных
    {
    Form4->select_vcam_by_name();
    if(Form4->devID == -1)
       Form4->select_first_active_vc();
    if(!Form4->vcam_selected_auto.empty())
      {
    __selected_current = Form4->vcam_selected_auto;
      ComboBox1->Text  = __selected_current.c_str();
      Caption = "Видео: \"" + (AnsiString)Form4->vcam_selected_auto.c_str() + "\"";
      }
    Form4->log_selected_vcam();
    }
  else
    {
    if(!user_selected_camera_is_connected)    //Камера, выбраная пользователем, в данный момент не подключена
      {
      if(!Form4->vcam_selected_auto.empty())
        {
         Caption = "Видео: \"" + (AnsiString)Form4->vcam_selected_auto.c_str() + "\"";
       __selected_current = Form4->vcam_selected_auto;
         ComboBox1->Text  = __selected_current.c_str();
        }
      }
    }
  }


if(__selected_current.find("Logitech") != -1)
  {
  string file_name = "C:\\Windows\\SysWOW64\\LogiDPPApp.exe";
  if(FileExists(file_name.c_str()))
     Button1->Visible = true;
  else
     Button1->Visible = false;
  }
else
  Button1->Visible = false;

#ifdef VIDEO_CAP_WITH_WINDOWS_FUNC
if(hWndC)
  {
  // SendMessage(hWndC, WM_CAP_DRIVER_CONNECT, 1, 0L);
   SendMessage(hWndC, WM_CAP_DRIVER_CONNECT, 0, 0L);
  // capPreview(hWndC,true);

   /*
   capPreviewRate(hWndC, 66);     // rate, in milliseconds
   capPreview(hWndC, TRUE);       // starts preview

// Preview

  capPreview(hWndC, FALSE);        // disables preview
  */
  }
#else
vcam_width  = 640;
vcam_height = 480;
if(Form4->devID != -1)
  {
  vcam_setup_device(Form4->devID, vcam_width, vcam_height);
  vcam_width     =  vcam_get_width(Form4->devID);
  vcam_height    =  vcam_get_height(Form4->devID);
  vcam_size      =  vcam_get_size(Form4->devID);
  if(vcam_size)
    {
    vcam_frame.resize(vcam_size);
    if(!bitmap)
       bitmap = new Graphics::TBitmap;
    if(bitmap)
      {
      if(venc_par.rgb24_yuv420_scalerId < 1)
         venc_par.rgb24_yuv420_scalerId = vencdec_create_scaler();
   // if(venc_par.encoderId < 1)
   // venc_par.encoderId            = vencdec_create_encoder(net_width, net_height,5,max_video_payload_size);
      set_bitmap_size();
      bitmap->PixelFormat = pf24bit;
      bitmap->Canvas->Brush->Style = bsSolid;
      Timer1->Enabled = true;
      }
    }
  }
#endif
}
//------------------------------------------------------------------------------
void __fastcall  TForm2::prepare_frame_to_send(vector<UCHAR>& vcam_frame)
{
//try{
if(Form4->is_vcl_empty())
   return;
vcam_frame.size();
int yuv420t_frame_sz = vencdec_get_yuv420p_buff_size( Form4->net_width, Form4->net_height);
if((yuv420t_frame_sz > 0)&&(yuv420t_frame_sz < 10000000))
  {
  vector<UCHAR> vbuf_yuv420p(yuv420t_frame_sz);
  int scale_rezult = vencdec_bgr24_to_yuv420p( venc_par.rgb24_yuv420_scalerId, vcam_width, vcam_height, &vcam_frame[0], vcam_frame.size(),
                          Form4->net_width, Form4->net_height, &vbuf_yuv420p[0], vbuf_yuv420p.size() );
  if((scale_rezult > 0)&&(scale_rezult < 10000000))
    {
    vector<UCHAR> vbuf_h263(scale_rezult);
    vencdec_encode(venc_par.encoderId, &vbuf_yuv420p[0], vbuf_yuv420p.size(), &vbuf_h263[0], vbuf_h263.size());
    }    //then see rtpCallBack()!!!
  }
//}//try
//catch(Exception& e){exsSstEXCEPTION(*eltp,"__TForm4::prepare_frame_to_send()",e);}
}
//---------------------------------------------------------------------------
void __fastcall TForm2::ComboBox1Click(TObject *Sender)
{
AnsiString S = ComboBox1->Text;
if(__selected_current == S.c_str())
   return;
Timer1->Enabled = false;
Form4->deactivate_selected_video_camera();
Form4->create_vcam_list();
Form4->select_vcam_by_appr_name(S.c_str());
if(Form4->devID != -1)
  {
  Caption = "Видео: \"" + S + "\"";
__selected_current = S.c_str();
  vcam_setup_device(Form4->devID, vcam_width, vcam_height);
  vcam_width     =  vcam_get_width(Form4->devID);
  vcam_height    =  vcam_get_height(Form4->devID);
  vcam_size      =  vcam_get_size(Form4->devID);
  if(vcam_size)
    {
    vcam_frame.resize(vcam_size);
    if(!bitmap)
        bitmap = new Graphics::TBitmap;
    if(bitmap)
      {
      if(venc_par.rgb24_yuv420_scalerId < 1)
         venc_par.rgb24_yuv420_scalerId = vencdec_create_scaler();
      set_bitmap_size();
      }
    }
  }
if(__selected_current.find("Logitech") != -1)
  {
  string file_name = "C:\\Windows\\SysWOW64\\LogiDPPApp.exe";
  if(FileExists(file_name.c_str()))
     Button1->Visible = true;
  else
     Button1->Visible = false;
  }
else
  Button1->Visible = false;
Timer1->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::__write_registry()
{
TRegistry& regKey = *new TRegistry();
regKey.RootKey = ROOT_KEY;
bool keyGood = regKey.OpenKey(key_name.c_str(),false);
if(!keyGood)
  keyGood = regKey.OpenKey(key_name.c_str(),true);
if(keyGood)
  {
  keyGood = regKey.OpenKey(dev_key_name.c_str(),false);
  if(!keyGood)
     keyGood = regKey.OpenKey(dev_key_name.c_str(),true);
  if(keyGood)
    {
    keyGood = regKey.OpenKey(video_key_name.c_str(),false);
    if(!keyGood)
        keyGood = regKey.OpenKey(video_key_name.c_str(),true);
    if(keyGood)
      {
      string dev_in = __selected_current;
      regKey.WriteString(video_in_device_name.c_str(),dev_in.c_str());
      }
    }
  regKey.CloseKey();
  }
delete &regKey;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Button6Click(TObject *Sender)
{
if(!__selected_current.empty())
  {
  Form4->set_vc_user_selected(true);
__write_registry();
  }
Close();
}
//---------------------------------------------------------------------------

