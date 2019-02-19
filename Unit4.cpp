//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "WinRDefs.h"

#ifdef SIP_Video
#include "Unit4.h"
#include "Unit3.h"
#include "videoCam.h"
#include "vencdec.h"
#include "Unit_Video_Cap.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

extern TMainFormSLS* MainFormSLS;
TForm4 *Form4;
//---------------------------------------------------------------------------
__fastcall TForm4::TForm4(TComponent* Owner)
        : TForm(Owner)
{
::InitializeCriticalSection(&vcl_cs);
MF_Handle = MainFormSLS->Handle;
eltp = &MainFormSLS->ofs->elt;
vcam_reinit_req   = false;
vc_user_selected  = false;
ResizeReq         = false;
FormIsFullScreen  = false;
resize_block      = false;
rtp_hdr           = 0;
video_call_tag    = 0;
leg_type          = Lt_NDef;
devID             = -1;
vcam_width        = SC_defaultCamWidth;
vcam_height       = SC_defaultCamHeight;
vcam_size         = 0;
net_width         = SC_defaultNetWidth;
net_height        = SC_defaultNetHeight;
send_video_pckn   = 0;
block_hide_panel1 = false;
psst              = passiveScreenSizeType_Unknown;
__read_registry_video_dev();
vcam_init();
select_vcam();
vencdec_init();
vencdec_set_encoder_rtp_handler( rtpCallBack );
bitmap = new Graphics::TBitmap;
curWidth   = SC_default_Local_ScreenWidth;
curHeight  = SC_default_Local_ScreenHeight;
prevWidth  = curWidth;
prevHeight = curHeight;
prevTop    = Top;
prevLeft   = Left;
prevWinState = 0;
Panel1 = new TPanel(this);     //this string must be before Width  = curWidth because Event OnResize raised (Panel1 resize on not created object Panel1)
Panel1->Parent = this;
Panel1->BevelInner = bvLowered;
Panel1->BevelOuter = bvRaised;
Panel1->Color = clSilver;
Panel1->OnResize = Panel1Resize;
Panel1->Visible = false;
Width  = curWidth;
Height = curHeight;
panel1_initsize();

Prev_Start_Video_Show  = Prev_Start_Video_Show.CurrentDateTime();
Hide_Start_Video_Delay = TDateTime(0,0,2,0); //2 sec
prev_X = 0;
prev_Y = 0;

Button1->Visible = true;
Button2->Visible = true;
top_left_btn_init_position();
img1 = new TImage(Panel1);
img1->Parent = Panel1;
img1->Width  = 114;
img1->Height = 26;
//img1->Stretch = true;
img1_size_position();
img1->OnMouseMove = Img1MouseMove;
img1->OnMouseUp   = Img1MouseUp;

/*
FullScreen1 = new TImage(this);
FullScreen1->Parent = this;
FullScreen1->Width  = 32;
FullScreen1->Height = 32;
FullScreen1->Transparent = true;
full_screen_img__size_position();
*/
}
//---------------------------------------------------------------------------
void __fastcall TForm4::__read_registry_video_dev()
{
TRegistry& regKey = *new TRegistry();
regKey.RootKey = ROOT_KEY;
bool keyGood = regKey.OpenKey(key_name.c_str(),false);
if(keyGood)
  {
  keyGood = regKey.OpenKey(dev_key_name.c_str(),false);
  if(keyGood)
    {
    keyGood = regKey.OpenKey(video_key_name.c_str(),false);
    if(keyGood)
      {
      string s = regKey.ReadString(video_in_device_name.c_str()).c_str();
      if(!s.empty())
        {
        vc_user_selected   = true;
        vcam_user_selected = s;
        }
      }
    }
  regKey.CloseKey();
  }
delete &regKey;
}
//-----------------------------------------------------------------------------
void __fastcall TForm4::Timer1Timer(TObject *Sender)
{
if(Form2->Visible)
   return;     //Камера переключена на Form2
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
if(devID != -1)
  {
  if(vcam_reinit_req)
    {
    vcam_reinit_req = false;
    vcam_setup_device(devID,vcam_width,vcam_height);
    vcam_width     =  vcam_get_width(devID);
    vcam_height    =  vcam_get_height(devID);
    vcam_size      =  vcam_get_size(devID);
    if(!vcam_size)return;
      vcam_frame.resize(vcam_size);
    if(!bitmap)
       bitmap = new Graphics::TBitmap;
    if(bitmap)
      {
      if(venc_par.rgb24_yuv420_scalerId < 1)
         venc_par.rgb24_yuv420_scalerId = vencdec_create_scaler();
      if(venc_par.encoderId < 1)
         venc_par.encoderId             = vencdec_create_encoder(net_width, net_height,5,max_video_payload_size);
      set_bitmap_size();
      bitmap->PixelFormat = pf24bit;
      bitmap->Canvas->Brush->Style = bsSolid;
      if(devID == -1)
         select_vcam();
      Timer1->Enabled = true;
      }
    return;
    }  //if(vcam_reinit_req)

  if(vcam_is_frame_new(devID))
    {
    check_on_corrective_resize_req();
    vcam_get_pixels( devID,  &vcam_frame[0], false, true );
    prepare_frame_to_send(vcam_frame);
    if((Visible)||(Form3->LocalVideoPanel->Visible))
     if(bitmap)
      if(bitmap->Width)
       if(bitmap->Height)
         {
         int screen_size = vencdec_get_bgr24_buff_size( bitmap->Width, bitmap->Height);
         if((screen_size > 0)&&(screen_size < 10000000))
           {
           load_vcam_frame_to_bitmap();
           if(Visible)
              draw_bitmap_on_screen();

           if(Form3->LocalVideoPanel->Visible)
             {
             int w = Form3->LocalVideoImage->Width;
             int h = Form3->LocalVideoImage->Height;
             if(w & 1) --w;
             if(h & 1) --h;
             TRect TheRect = Rect(0,0,w,h);
             Form3->LocalVideoImage->Canvas->StretchDraw(TheRect, bitmap);
             }
           }
         }
    }
  }
Timer1->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TForm4::load_vcam_frame_to_bitmap()
{
int Y = 0;
int w_size = bitmap->Width*3;
for(int y = 0; y < bitmap->Height; y++)
   {
   Byte* ptr = (Byte *)bitmap->ScanLine[y];
   memcpy(ptr,&vcam_frame[Y],w_size);
   Y+=w_size;
   }
}
//---------------------------------------------------------------------------
void __fastcall TForm4::draw_bitmap_on_screen()
{
if(bitmap)
  {
  int width      = Width;
  int height     = Height;
  if(width & 1)  --width;
  if(height & 1) --height;
  TRect TheRect = Rect(0,0,width,height);
  Canvas->StretchDraw(TheRect, bitmap);
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm4::ins_vcl(int chId)
{
::EnterCriticalSection(&vcl_cs);
  if(find(video_ch_id_list.begin(), video_ch_id_list.end(), chId) == video_ch_id_list.end())
     video_ch_id_list.push_back(chId);
::LeaveCriticalSection(&vcl_cs);
}
//---------------------------------------------------------------------------
bool __fastcall TForm4::is_vcl_empty()
{
bool rv = false;
::EnterCriticalSection(&vcl_cs);
  if(video_ch_id_list.empty())
     rv = true; 
::LeaveCriticalSection(&vcl_cs);
return rv;
}
//---------------------------------------------------------------------------
void __fastcall TForm4::get_all_vcl(deque<int>& deq)
{
::EnterCriticalSection(&vcl_cs);
  deq = video_ch_id_list;
::LeaveCriticalSection(&vcl_cs);
}
//---------------------------------------------------------------------------
void __fastcall TForm4::del_vcl(int chId)
{
::EnterCriticalSection(&vcl_cs);
  deque<int>::iterator it = video_ch_id_list.begin();
  while(it != video_ch_id_list.end())
       {
       if((*it) == chId)
         {
         video_ch_id_list.erase(it);
         break;
         }
       it++;
       }
::LeaveCriticalSection(&vcl_cs);
}
//---------------------------------------------------------------------------
void __fastcall TForm4::corrective_resize()
{
if(ResizeReq)
  if(ResizeTime.CurrentDateTime() > ResizeTime)
    {
    ResizeReq = false;
    if(psst == passiveScreenSizeType_Height)
       {
       Height    = (Width/1.33333);// + SC_vert_addition_F4;  //Restore size 4:3
       curHeight = Height;
       curWidth  = Width;
       set_bitmap_size();
       }
    else if(psst == passiveScreenSizeType_Width)
      {
      int a = Height; // - SC_vert_addition_F4;
      Width = a * 1.33333;   //Restore size 4:3
      curWidth  = Width;
      curHeight = Height;
      set_bitmap_size();
      }
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm4::check_on_corrective_resize_req()
{
if(resize_block)
   return;
if(WindowState == wsNormal)
  {
  if(curWidth != Width)
    {
    if((GetKeyState(VK_LBUTTON) & 0x80) == 0)  //Left Mouse Buttin is not pressed
       {
       curWidth  = Width;
       psst = passiveScreenSizeType_Height;
       ResizeReq = true;
       set_bitmap_size();
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
      set_bitmap_size();
      ResizeTime = ResizeTime.CurrentDateTime() + TDateTime(0,0,0,20);
      }
    }
  }
else if(WindowState == wsMaximized)
 {
 curHeight = Height;
 curWidth  = Width;
 set_bitmap_size();
 }
}
//---------------------------------------------------------------------------
void __fastcall TForm4::Prepare_Form4_Show()
{
curWidth  = SC_default_Local_ScreenWidth;
curHeight = SC_default_Local_ScreenHeight;
Width     = curWidth;
Height    = curHeight;

Panel1->Visible = false;
panel1_initsize();
if(FormIsFullScreen)
   Button2->Visible = true;
else
   {
   Button1->Visible = false;
   Button2->Visible = false;
   Left = MainFormSLS->Left;
   Top  = MainFormSLS->Top + MainFormSLS->Panel1->Top +  MainFormSLS->Panel1->Height + 25;
   }

//if(devID == -1)
//  {
devID = -1;    //!!!
vcam_init();
select_vcam();
if(devID == -1)
   return;
//  }

vcam_setup_device(devID,vcam_width,vcam_height);
vcam_width     =  vcam_get_width(devID);
vcam_height    =  vcam_get_height(devID);
vcam_size      =  vcam_get_size(devID);
if(!vcam_size)return;
vcam_frame.resize(vcam_size);
if(!bitmap)
    bitmap = new Graphics::TBitmap;
if(bitmap)
  {
  if(venc_par.rgb24_yuv420_scalerId < 1)
    venc_par.rgb24_yuv420_scalerId = vencdec_create_scaler();
  if(venc_par.encoderId < 1)
     venc_par.encoderId            = vencdec_create_encoder(net_width, net_height,5,max_video_payload_size);
  set_bitmap_size();
  bitmap->PixelFormat = pf24bit;
  bitmap->Canvas->Brush->Style = bsSolid;
  Timer1->Enabled = true;
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm4::Local_Video_Show()
{
if(MainFormSLS->lng == Lang_RU)
   Caption = "Локальная камера"; 
Prepare_Form4_Show();
Show();
}
//--------------------------------------------------------------------------
int __fastcall TForm4::create_vcam_list()
{
string s;
vc_list.clear();
int dev_count = vcam_get_device_count();
s = "\nКоличество подключенных видео камер: " + inttostr(dev_count) + "\n";
for(int i = 0;i < dev_count;i++)
   {
   char* buf =  vcam_get_name(i);
   if(buf)
     {
     vc_list.insert(TVCam_List::value_type(i,string(buf)));
     s += "\"" + string(buf) + "\"\n";
     }
   }
if(MainFormSLS->ofs)
  if(MainFormSLS->ofs->elt)
     MainFormSLS->ofs->elt->FputEvt(s);
return dev_count;
}
//---------------------------------------------------------------------------
bool __fastcall TForm4::check_brand_name(TVCam_List::iterator& it)
{
if((*it).second.find("Logitech") != -1) return true;
return false;
}
//----------------------------------------------------------------------------
bool __fastcall TForm4::check_usb_device(TVCam_List::iterator& it)
{
if((*it).second.find("USB") != -1) return true;
return false;
}
//----------------------------------------------------------------------------
//--- vcam selected by "Logitech" name  --------------------------------------
//----------------------------------------------------------------------------
void __fastcall TForm4::select_vcam_by_name()
{
TVCam_List::iterator it = vc_list.begin();
while(it != vc_list.end())
     {
     if(check_brand_name(it))
       {
       vcam_setup_device((*it).first,vcam_width,vcam_height);
       int sz = vcam_get_size((*it).first);
       if(sz)
          {
          devID = (*it).first;
          vcam_selected_auto = (*it).second;
          vcam_width      =  vcam_get_width(devID);
          vcam_height     =  vcam_get_height(devID);
          vcam_size       =  vcam_get_size(devID);
          }
       ::Sleep(100);  //protect from  auto init
       vcam_stop_device((*it).first);
       break;
       }
     it++;
     }
if(devID != -1)
  return;
it = vc_list.begin();
while(it != vc_list.end())
     {
     if(check_usb_device(it))
       {
       vcam_setup_device((*it).first,vcam_width,vcam_height);
       int sz = vcam_get_size((*it).first);
       if(sz)
          {
          devID = (*it).first;
          vcam_selected_auto   = (*it).second;
          vcam_width      =  vcam_get_width(devID);
          vcam_height     =  vcam_get_height(devID);
          vcam_size       =  vcam_get_size(devID);
          }
       ::Sleep(100);  //protect from  auto init
       vcam_stop_device((*it).first);
       break;
       }
     it++;
     }
}
//---------------------------------------------------------------------------
void __fastcall TForm4::select_vcam_by_appr_name(const string& s)
{
TVCam_List::iterator it = vc_list.begin();
while(it != vc_list.end())
     {
     if((*it).second == s)
       {
       devID = (*it).first;
       break;
       }
     it++;
     }
}
//---------------------------------------------------------------------------
void __fastcall TForm4::select_first_active_vc()
{
TVCam_List::iterator it = vc_list.begin();
while(it!=vc_list.end())
     {
     vcam_setup_device((*it).first,vcam_width,vcam_height);
     int sz = vcam_get_size((*it).first);
     if(sz)
       {
       devID = (*it).first;
       vcam_selected_auto = (*it).second;
       vcam_width     =  vcam_get_width(devID);
       vcam_height    =  vcam_get_height(devID);
       vcam_size      =  vcam_get_size(devID);
       ::Sleep(100);
       vcam_stop_device((*it).first);
       break;
       }
     vcam_stop_device((*it).first);
     it++;
     }
}
//---------------------------------------------------------------------------
void __fastcall TForm4::select_vcam()
{
int dev_count = create_vcam_list();
if(vc_user_selected)
  {
  if(dev_count > 1)
    {
    select_vcam_by_appr_name(vcam_user_selected);
    if(devID == -1)
      {
      select_vcam_by_name();
      if(devID == -1)
         select_first_active_vc();
      }
    log_selected_vcam();
    return;
    }
  }
if(devID == -1)
  {
  select_vcam_by_name();
  if(devID == -1)
     select_first_active_vc();
  }
log_selected_vcam();
}
//---------------------------------------------------------------------------
void __fastcall TForm4::log_selected_vcam()
{
if(devID != -1)
  if(MainFormSLS->ofs)
    if(MainFormSLS->ofs->elt)
      {
      string s = "\nВыбрана видео камера: ID = " + inttostr(devID);
      TVCam_List::iterator it = vc_list.find(devID);
      if(it != vc_list.end())
         s += ", \"" + (*it).second + "\"" + "\n";
      MainFormSLS->ofs->elt->FputEvt(s);
      }
}
//---------------------------------------------------------------------------
void __fastcall TForm4::get_all_device_name(queue<string>& q)
{
TVCam_List::iterator it = vc_list.begin();
while(it != vc_list.end())
      q.push((*it++).second);
}
//---------------------------------------------------------------------------
void __fastcall TForm4::FormCreate(TObject *Sender)
{
MainFormSLS->ActivateVideoCallBtnState(devID);
}
//---------------------------------------------------------------------------
void __fastcall TForm4::set_bitmap_size()
{
if(bitmap)
  {
  bitmap->Width  = vcam_width;
  bitmap->Height = vcam_height;
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm4::FormResize(TObject *Sender)
{
if(resize_block)
  return;  
panel1_resize();
if(WindowState == wsNormal)
  if(Button2->Visible)
     Button2->Visible = false;
}
//---------------------------------------------------------------------------
void __fastcall TForm4::panel1_initsize()
{
Panel1->Top    = Height - 70;
Panel1->Height = 26;
Panel1->Width  = 114; 
Panel1->Left   = Width/2 - Panel1->Width/2;
}
//---------------------------------------------------------------------------
void __fastcall TForm4::panel1_resize()
{
if(Panel1->Visible)
   panel1_initsize();
}
//---------------------------------------------------------------------------
void __fastcall TForm4::top_left_btn_init_position()
{
Button1->Top  = 0;
Button1->Left = 0;
Button2->Top  = Button1->Top;
Button2->Left = Button1->Left + Button1->Width + 10;
}
//--------------------------------------------------------------------------
void __fastcall TForm4::FormMouseMove(TObject *Sender, TShiftState Shift,
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
      Panel1->Show();     // Panel with img1 - "Видеозвонок"
           // FullScreen1->Show();
      Prev_Start_Video_Show = Prev_Start_Video_Show.CurrentDateTime();
      prev_X = X; prev_Y = Y;
      }
    }
  }
  
if(resize_block)
  {
  Button1->Visible = false;
  Button2->Visible = false;
  return;
  }
if(Y < 20)
  {
  if(!FormIsFullScreen)
    {
    if(X < Button1->Width/3)
      {
      Button1->Visible = true;
      return;
      }
    }
  else
     {
     Button2->Visible = true;
     return;
     }
  }
Button1->Visible = false;
Button2->Visible = false;

}
//---------------------------------------------------------------------------

void __fastcall TForm4::Button2Click(TObject *Sender)
{
Form4->FormStyle = fsNormal;
Form4->BorderStyle = bsSizeable;
FormIsFullScreen = false;
if(prevWinState == 1)
  {
  prevWinState = 0;
  WindowState = wsNormal;
  Height = 2*Screen->Height/3;
  Width  = Height * 1.33333; // + SC_vert_addition_F4;
  Position = poScreenCenter;
 // Top-= SC_vert_addition_F4;
  }
else
  {
  Top = prevTop;
  Left = prevLeft;
  Width = prevWidth;
  Height = prevHeight;
  }
Button2->Left = Button1->Width + Button2->Width + 10;
//Panel1->Visible = true;
}
//---------------------------------------------------------------------------
void __fastcall TForm4::img1_size_position()
{
ImageList1->Draw(img1->Canvas,0,0,0,true);
img1->Width  = Panel1->Width;
img1->Height = Panel1->Height;
img1->Left = Panel1->Width/2 - img1->Width/2;
img1->Top  = (Panel1->Height/2) - img1->Height/2;//(Panel1->Height/2) - img1->Height;
}
//---------------------------------------------------------------------------
void __fastcall TForm4::Panel1Resize(TObject *Sender)
{
img1_size_position();
}
//---------------------------------------------------------------------------
void __fastcall TForm4::Img1MouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
block_hide_panel1 = true;
}
//---------------------------------------------------------------------------
void __fastcall TForm4::Img1MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
TContact ContCopy(-1);
if(MainFormSLS->Sip->Contacts.get_contact_copy_by_user_name(ContCopy, MainFormSLS->get_user_name_to_send()))
  if(ContCopy.CT == ContactType_GROUP)
    {
     Close();
     return;
    }
TDateTime dt = dt.CurrentDateTime();
if((dt - BtnUpTmStmp) > TDateTime(0,0,1,0))  //Защита от сдвоенного OnMouseUp
  {
  BtnUpTmStmp = dt;
  start_video_call();
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm4::start_video_call()
{
Form3->Top    = Top;
Form3->Left   = Left;
Form3->Width  = Width;
Form3->Height = Height;
Form3->call_in_progress = true;
Form3->FormStyle = fsStayOnTop;
Form3->Remote_Video_Show();
//Form3->FormStyle = fsStayOnTop;
Form4->Close();

TExchBuf* buf = new TExchBuf(WM_APP_MSG_WPARAM__VIDEOOUT);
if(buf)
  {
  buf->emt = ExchMsgType_VideoOut;
  TVcamPar* vcpar = new TVcamPar;
  if(vcpar)
     {
     vcpar->width  = vcam_width;
     vcpar->height = vcam_height;
     vcpar->fps    = 12;
     buf->setAddBuf(vcpar);
     }
  MainFormSLS->videoout_exchlst_insert(buf);
  ::PostMessage(MF_Handle, VIDEOOUT_MSG, WM_APP_MSG_WPARAM__VIDEOOUT, WM_APP_MSG_LPARAM__READLIST);
  }
}
//----------------------------------------------------------------------------
/*
void __fastcall TForm4::OnForm3Resize()
{
if(resize_block)
  {
  Left = Form3->Left + 5;
  Top  = Form3->Top + Form3->Height - Height - 5;
  }
}
*/
//----------------------------------------------------------------------------
void __fastcall TForm4::updateSentQueue_2(TOutPutUdpBlock* opb)
{
if(opb)
   sent.push_back(opb);
getSent_2();
}
//---------------------------------------------------------------------------
void __fastcall TForm4::getSent_2()
{
while(!sent.empty())        //Delete all first released blocks
     {
     TOutPutUdpBlock* opb = sent.front();
     if(opb->getReferenceCount() < 1)
       {
       sent.pop_front();
       delete opb;
       }
     else
       break;
     }
if(sent.size() > 4)   //replace first to end    //log this situation
  {
  TOutPutUdpBlock* opb = sent.front();
  sent.pop_front();
  sent.push_back(opb);
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm4::send_frame(UCHAR* frame,int frame_sz,int mb_nb)
{
try{
if(is_vcl_empty())return;
deque<int> tempDeq;
get_all_vcl(tempDeq);
if(tempDeq.empty())return;
if(!frame_sz)return;
if(MainFormSLS->Sip->ucs)
 {
 TUdpChannelStruct* ucs = MainFormSLS->Sip->ucs;
 for(deque<int>::iterator it = tempDeq.begin(); it < tempDeq.end(); it++)
    {
    TUdpChannel* uc = ucs->getUdpChannel(*it++);
    if(uc)
      if(uc->getMpt() == VIDEO_MPT)
       if(!uc->get_video_pause())
         {
         vector<int> v;
         uc->getAllMyConnections(v);
         if(!v.empty())
           {
           TOutPutUdpBlock* opb = NULL;     //opb created only if any one of connected channels is Answered.
           for(unsigned i=0;i<v.size();i++) //Then this block inserted in the other Answered channels.
              {                             //Created and filled one time, inserted many time.
               TUdpChannel* cntd_uc = ucs->getUdpChannel(v[i]); //This is used for VideoConf
               if(cntd_uc)                                      //or for transmitted for more then one channels
                 if(cntd_uc->sendThread)
                   if(cntd_uc->sendThread->getRemotePort() != -1)
                     {
                    // int queue_sz = cntd_uc->sendThread->getQueueSize();
                    // cntd_uc->sendThread->lasterr = "\nvideo_rtp_send_thread_queue " + inttostr(queue_sz);
                    // cntd_uc->sendThread->sendlasterr();

                     if(!opb)
                        {
                        opb = new TOutPutUdpBlock(send_video_pckn);
                        if(opb)
                          {
                          opb->mpt   = VIDEO_MPT;
                          opb->tunnel_name = "v" + inttostr(cntd_uc->getChId());
                          opb->mb_nb = mb_nb;
                          if((frame_sz > 0)&&(frame_sz < 10000000))
                            {
                            opb->v.resize(frame_sz);
                            memcpy(&opb->v[0],frame,frame_sz);
                            }
                          }
                        }
                     if(opb)
                       {
                       opb->tunnel_name = "v" + inttostr(cntd_uc->getChId());
                       cntd_uc->sendThread->setQueue(opb);
                       }
                     }
              }
           if(opb)
              updateSentQueue_2(opb);
           }//if(!v.empty())
         } //if(!uc->get_video_pause())
    }
 }
}//try
catch(Exception& e){exsSstEXCEPTION(*eltp,"__TForm4::send_frame()",e);}
}
//---------------------------------------------------------------------------
void rtpCallBack ( int encoderId, UCHAR* data, int size, int mb_nb )
{
try{
if((size > 0)&&(size < 10000000))
  Form4->send_frame(data, size, mb_nb);
}//try  
catch(Exception& e){exsSstEXCEPTION(MainFormSLS->ofs->elt,"__rtpCallBack()",e);}
}
//---------------------------------------------------------------------------
void __fastcall  TForm4::prepare_frame_to_send(vector<UCHAR>& vcam_frame)
{
try{
if(is_vcl_empty())
   return;
vcam_frame.size();
int yuv420t_frame_sz = vencdec_get_yuv420p_buff_size( net_width, net_height);
if((yuv420t_frame_sz > 0)&&(yuv420t_frame_sz < 10000000))
  {
  vector<UCHAR> vbuf_yuv420p(yuv420t_frame_sz);
  int scale_rezult = vencdec_bgr24_to_yuv420p( venc_par.rgb24_yuv420_scalerId, vcam_width, vcam_height, &vcam_frame[0], vcam_frame.size(),
                          net_width, net_height, &vbuf_yuv420p[0], vbuf_yuv420p.size() );
  if((scale_rezult > 0)&&(scale_rezult < 10000000))
    {
    vector<UCHAR> vbuf_h263(scale_rezult);
    vencdec_encode(venc_par.encoderId, &vbuf_yuv420p[0], vbuf_yuv420p.size(), &vbuf_h263[0], vbuf_h263.size());
    }    //then see rtpCallBack()!!!
  }
}//try
catch(Exception& e){exsSstEXCEPTION(*eltp,"__TForm4::prepare_frame_to_send()",e);}
}
//---------------------------------------------------------------------------
void __fastcall  TForm4::deactivate_selected_video_camera()
{
if(devID != -1)
  {
  vcam_stop_device(devID);
  devID = -1;
  }
if(venc_par.rgb24_yuv420_scalerId > 0)
  vencdec_destroy_scaler( venc_par.rgb24_yuv420_scalerId );
if(venc_par.encoderId > 0)
   vencdec_destroy_encoder( venc_par.encoderId );
venc_par.rgb24_yuv420_scalerId = 0;
venc_par.encoderId             = 0;
}
//---------------------------------------------------------------------------
/*
static void tdav_codec_h263_rtp_callback(tdav_codec_h263_t *self, const void *data, tsk_size_t size, tsk_bool_t marker)
{
        uint8_t* pdata = (uint8_t*)data;

        if(self->rtp.size < (size + H263_HEADER_MODE_A_SIZE)){
                if(!(self->rtp.ptr = tsk_realloc(self->rtp.ptr, (size + H263_HEADER_MODE_A_SIZE)))){
                        TSK_DEBUG_ERROR("Failed to allocate new buffer");
                        return;
                }
                self->rtp.size = (size + H263_HEADER_MODE_A_SIZE);
        }
        memcpy((self->rtp.ptr + H263_HEADER_MODE_A_SIZE), data, size);

        /* http://eu.sabotage.org/www/ITU/H/H0263e.pdf section 5.1
        * 5.1.1 Picture Start Code (PSC) (22 bits) - PSC is a word of 22 bits. Its value is 0000 0000 0000 0000 1 00000.

        *
        * 5.1.1 Picture Start Code (PSC) (22 bits)
        * 5.1.2 Temporal Reference (TR) (8 bits)
        * 5.1.3 Type Information (PTYPE) (Variable Length)
        *       ? Bit 1: Always "1", in order to avoid start code emulation.
        *       ? Bit 2: Always "0", for distinction with Recommendation H.261.

        *       ? Bit 3: Split screen indicator, "0" off, "1" on.
        *       ? Bit 4: Document camera indicator, "0" off, "1" on.
        *       ? Bit 5: Full Picture Freeze Release, "0" off, "1" on.
        *       ? Bits 6-8: Source Format, "000" forbidden, "001" sub-QCIF, "010" QCIF, "011" CIF,
                "100" 4CIF, "101" 16CIF, "110" reserved, "111" extended PTYPE.
                If bits 6-8 are not equal to "111", which indicates an extended PTYPE (PLUSPTYPE), the following
                five bits are also present in PTYPE:
                ? Bit 9: Picture Coding Type, "0" INTRA (I-picture), "1" INTER (P-picture).
                ? Bit 10: Optional Unrestricted Motion Vector mode (see Annex D), "0" off, "1" on.
                ? Bit 11: Optional Syntax-based Arithmetic Coding mode (see Annex E), "0" off, "1" on.
                ? Bit 12: Optional Advanced Prediction mode (see Annex F), "0" off, "1" on.
                ? Bit 13: Optional PB-frames mode (see Annex G), "0" normal I- or P-picture, "1" PB-frame.
        */


//        if(pdata[0] == 0x00 && pdata[1] == 0x00 && (pdata[2] & 0xfc)==0x80){ /* PSC */
                /* RFC 2190 -5.1 Mode A
                        0                   1                   2                   3
                        0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
                        +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
                        |F|P|SBIT |EBIT | SRC |I|U|S|A|R      |DBQ| TRB |    TR         |
                        +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

                SRC : 3 bits
                Source format, bit 6,7 and 8 in PTYPE defined by H.263 [4], specifies
                the resolution of the current picture.

                I:  1 bit.
                Picture coding type, bit 9 in PTYPE defined by H.263[4], "0" is
                intra-coded, "1" is inter-coded.
                */

                // PDATA[4] ======> Bits 3-10 of PTYPE
/*                uint32_t rtp_hdr = 0;
                uint8_t format, pict_type;

                // Source Format = 4,5,6
                format = (pdata[4] & 0x3C)>>2;
                // Picture Coding Type = 7
                pict_type = (pdata[4] & 0x02)>>1;
                // RTP mode A header
                ((uint8_t*)&rtp_hdr)[1] = (format <<5) | (pict_type << 4);
                //rtp_hdr = tnet_htonl(rtp_hdr);
                memcpy(self->rtp.ptr, &rtp_hdr, sizeof(rtp_hdr));  */
//        }
/*
        // Send data over the network
        if(TMEDIA_CODEC_VIDEO(self)->callback){
                TMEDIA_CODEC_VIDEO(self)->callback(TMEDIA_CODEC_VIDEO(self)->callback_data, self->rtp.ptr, (size + H263_HEADER_MODE_A_SIZE), (3003* (30/TMEDIA_CODEC_VIDEO(self)->fps)), marker);
        }  */
//}
//--------------------------------------------------------------------------
void __fastcall TForm4::FormClose(TObject *Sender, TCloseAction &Action)
{
if(!Form3->call_in_progress)
  Timer1->Enabled = false;
if(devID != -1)
  {
  if(!Form3->call_in_progress)
    {
    vcam_stop_device(devID);
    devID = -1;
    }
  if(video_call_tag)
    {
    TCall_Panel* panel = MainFormSLS->get_Call_Panel_By_Tag(video_call_tag);
    if(panel)
      {
      panel->draw_passive_cam_img();
      TMediaSession* ms = MainFormSLS->Sip->sss->GetMs_by_Call_Tag(video_call_tag);
      if(ms)
        {
        TUdpChannel* uc_video = ms->getVideoChannel();
        if(uc_video)
           uc_video->set_video_pause(true);
        }
      }
    }
  }
if(bitmap)
  {
  if(!Form3->LocalVideoPanel->Visible)
    {
    delete bitmap;
    bitmap = NULL;
    }
  }
curWidth  = SC_default_Local_ScreenWidth;
curHeight = SC_default_Local_ScreenHeight;
}
//---------------------------------------------------------------------------
void __fastcall TForm4::Button1MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
FormIsFullScreen = true;
prevTop = Top;
prevLeft = Left;
prevWidth = Width;
prevHeight = Height;
if(WindowState == wsMaximized)
   prevWinState = 1;
Form4->SetBounds(0,0,Screen->Width,Screen->Height);
Form4->FormStyle = fsStayOnTop;
Form4->BorderStyle = bsNone;
//Form4->Menu = NULL;    // remove menu
Button2->Left = 0;
}
//---------------------------------------------------------------------------
void __fastcall TForm4::FormMouseUp(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
if(Button == mbRight)
 if(resize_block)
   if(Visible)
      Hide();
}
//---------------------------------------------------------------------------
void __fastcall TForm4::FormDestroy(TObject *Sender)
{
vencdec_destroy();
::DeleteCriticalSection(&vcl_cs);
}
//---------------------------------------------------------------------------
#endif //#ifdef SIP_Video
