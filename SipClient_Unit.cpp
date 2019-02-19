//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <Filectrl.hpp>
#include <Registry.hpp>
#include "WinRDefs.h"
#include <pies.h>
#include <windowsx.h>
#include <winuser.h>
#include "SipClient_Unit.h"
#include "AddContact_Unit.h"
#include "utils.h"
#include "Sound.h"
#include "g711.h"
#include "CallIn_Unit.h"
#include <vfw.h>
#include "Unit_Video_Cap.h"
#include "Unit3.h"
#include "Unit4.h"
#include "Test_Unit.h"
#include "ContactMenu_Unit.h"
#include "About_Unit.h"
#include "const.h"
#include "RegistryPanel_Unit.h"
#include "tls.h"
#include "rsrtp.h"
#include "SipTransport.h"
#include <dir.h>
#include "Test_Sound.h"
#include "StartOptions_Unit.h"
#include "RBitMap.h"
#include "Unit_EnterpriseSubscList.h"
#include "rstrdp.h" //ScreenSharing
#include "Refer_Unit.h"
#include "ParallelPhone_Unit.h"
#include "Conference_Unit.h"
#include "md5.h"
#include <string>
#include "src\win_utils.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
/*
Когда используется видео, то небольшими темпами, но все же растет память и увелич количество Handles. Проверить создание и удаление хэндлеров vencdec_create_scaler(), vencdec_create_encoder(), vencdec_create_decoder(), vencdec_destroy_decoder(), vencdec_destroy_scaler()
*/

#define TOP_FILE_TRANSFER_ICON_POSITION   3
#define LEFT_FILE_TRANSFER_ICON_POSITION  6

using namespace std;

TMainFormSLS *MainFormSLS;

const string Comp       = "BC_6_0";
const string ClientName = "Pangeo";
const string Vers       = "1.2";

const ENV_SZ = 128;
const MIN_CLIEN_WIDTH                 = 250;
const char WS_Char                    = ' ';
const string SC_NullString            = "";
const string SipClient_LOG_IS         = "Log";
const string SipClient_LOG            = "Log";
const string Stun_IS                  = "Stun";
const string Stun_Server_ID           = "StunServer";
const string Sip_IS                   = "Sip";
const string Sip_Proxy_ID             = "SipProxyAddr";
const string Sip_Proxy_Port_ID        = "SipProxyPort";
const string Sip_Local_Proxy_ID       = "SipLocalProxyAddr";
const string Sip_Local_Proxy_Port_ID  = "SipLocalProxyPort";
const string Sip_Tunnel_IS            = "SipTunnel";
const string Sip_Tunnel_Addr_ID       = "SipTunnelAddr";
const string Sip_Tunnel_Port_ID       = "SipTunnelPort";
const string Sip_Local_Tunnel_Addr_ID = "SipLocalTunnelAddr";
const string Sip_Local_Tunnel_Port_ID = "SipLocalTunnelPort";
const string File_IS                  = "File";
const string FTransfer_Proxy_Addr_ID  = "FTransferProxyAddr";
const string FTransfer_Proxy_Port_ID  = "FTransferProxyPort";
const string Account_IS               = "Account";
const string User_Name_ID             = "UserName";
const string Domain_Name_ID           = "Domain";
const string Display_Name_ID          = "DisplayName";
const string RegInt_ID                = "RegInt";
const string Signal_IS                = "Signal";
const string Alerting_Type_ID         = "AlertingType";
const string Media_IS                 = "Media";
const string MStrtPort_ID             = "MStrtPort";
const string MEndPort_ID              = "MEndPort";
const string MInt_ID                  = "MInt";
const string SipTransport_IS          = "Transport";
const string SignType_ID              = "Sip";
const string Sip_Tcp_IS               = "TCP";
const string Sip_Tcp_Addr_ID          = "Addr";
const string Sip_Tcp_Port_ID          = "Port";
const string Sip_Tls_IS               = "TLS";
const string Sip_Tls_Addr_ID          = "Addr";
const string Sip_Tls_Port_ID          = "Port";
const string SubscDB_IS               = "SubscDB";
const string ScreenSharing_IS         = "ScreenSharing";
const string Addr_ID                  = "Addr";
const string Port_ID                  = "Port";
const string G729_IS                  = "G729";
const string Annexb_ID                = "annexb";
const string _hstry                   = "HSTRY";
const string _lcs                     = "LCS";
const string _lf                      = "\n";
const string _tstmp                   = "tstmp:";
const _tstmp_len                      = 6;
const string _durtn                   = "durtn:";
const _durtn_len                      = 6;
const string _TYPE                    = "TYPE:";
const text_delta                      = 20; //10; //3;
const AnsiString _font_name_Arial     = "Arial";
const turquoise_color                 = 0x00E37506;
const string  _audio_dll              = "AudioInterface.dll";
const string  _voice_capture_dsp_dll  = "voice_dsp_aec";
//const string  _events_dll             = "elog.dll";
const call_btn_width                  = 40;
const call_btn_height                 = 40;
const LOCAL_IM_TEXT__LEFT             = 40;
const REMOTE_IM_TEXT__LEFT            = 0;

/*
TColor CallBtn_Color_INACTIVE = clWhite;
TColor CallBtn_Color_ACTIVE   = clWhite;
TColor CallBtn_Color_FOCUSED  = (TColor)0xF0F0F0;
*/
static UINT s_uTaskbarRestart;
//----------------------------------------------------------------------------
__fastcall TMainFormSLS::TMainFormSLS(TComponent* Owner)
        : TForm(Owner)
{
s_uTaskbarRestart = RegisterWindowMessage(TEXT("TaskbarCreated"));  //This is requiered for correct reflecting app icon on the TaskBar after Explorer.exe restart (see MY_WND_PROC)
WindowProc = MY_WND_PROC;

//int curr_thr_id = GetCurrentThreadId();

//BLOCK_SEND_RTP = false;
/*
try{
TJPEGImage* examp = new TJPEGImage;
Graphics::TBitmap* pBitmap = new Graphics::TBitmap();
examp->LoadFromFile("C:\\A\\noname_jpg.jpg");
pBitmap->Assign(examp);
delete examp;
}
 catch(...){
        ShowMessage("Could not load or display bitmap");
       }
*/

exs_write_reg_pid_value();
::InitializeCriticalSection(&callin_exchlst_cs);
::InitializeCriticalSection(&videoout_exchlst_cs);
::InitializeCriticalSection(&filetrans_exchlst_cs);
_CLOSE_REQUEST    = false;
LAST_FORM_CREATED = false;
TIME_STMP_REQUEST = false;
DestroyReq        = false;
ProfileForm       = NULL;
Sip = NULL;
PPS = NULL;
ofs = NULL;
SCP = NULL;
NSP = NULL;    //Contains image of my net status. Wil be createdin the INIT_CTRL_SET() istyle_1()
DPP = NULL;    //DialPad_Panel
NSCP = NULL;    //Network State Comment Panel
lng  = Lang_RU; //Lang_EN; //Lang_RU;
RichEdit1 = new TRichEdit(this);
RichEdit1->Parent  = this;
RichEdit1->Visible = false;
ParallelPhoneWin = NULL;
#ifndef Automatic_Out_Calls
Button9->Visible  = false;
Button10->Visible = false;
#endif
__StartDateTime = __StartDateTime.CurrentDateTime();
Get_OS_Version(&osv);
SPLITTER();
KeyPreview    = true;
WSAStartUp    = false;
term_explicit = false;
__send_IM_to_conf_participants = false;
__send_IM_to_chat_participants = false;
//subscr_proc_active = false;
app_minimized      = false;
app_on_tray_only   = false;
sound_tool         = false;
req_to_close_conf_panel = false;
AddToConfBtnState       = BtnState_INACTIVE;
#ifndef Client_Test_Sound
TestSound1->Visible = false;
#endif
client_node = "Pangeo";
client_name = "RSC";
int N = 160;
double a = 2*M_PI/(double)N;
for(int i=0;i<N;i++)
   {
   double b = a*(double)i;
   complex<double> h(cos(b),-sin(b));
   hh.push_back(h);
   }
for(int i=0;i<N;i++)
   {
   double b = a*(double)i;
   complex<double> h(cos(b),sin(b));
   hh_1.push_back(h);
   }
for(int n=0;n<N;n++)//Синус окно
   sin_wind.push_back(sin((double)(M_PI*n)/(double)(N-1)));
for(int n=0;n<N;n++)//Окно Ханна
   hann_wind.push_back(0.5 - (0.5*cos((double)(2*M_PI*n)/(double)(N-1))));
for(int n=0;n<N;n++)
   blackman_wind.push_back(0.42 - 0.5*cos((double)(2*M_PI*n)/(double)(N-1)) + 0.08*cos((double)(4*M_PI*n)/(double)(N-1)));

NetStatusImageList->Height = 18;
NetStatusImageList->Width  = 36;
         //rdp_init();
tf_init();
intrfStyle = CLIENT_INTERFACE_STYLE;
INIT_CTRL_SET();
baseCaption = "";//Caption;
Position = poScreenCenter;
get_client_root(client_root);
if(client_root.empty())
   return;
//LoadLogEventsDll();
//LoadAudioDll();
/*
#ifdef USE_WIN_DSP_CAPTURE_CAPABILITIES
LoadVoiceCaptureDspDll();
#endif
*/
get_media_devices_from_registry();
get_client_directories(client_root);  //client_root + "\\Log";
#ifdef DEBUG__SIP__CLIENT
iniData.ifl = new TIniFile((client_root + "\\Ini\\SipClient.ini").c_str());
#else
iniData.ifl = new TIniFile((ini_dir + "\\SipClient.ini").c_str());
#endif
iniData.ReadIniData();
ofs = new TOutputLogFileStruct(&OPB, log_dir, iniData. getLog(), Vers);
if(ofs)
   ofs->sOpenAllLog();
if(exsWSAStartUp(ofs->elt))
     return;
WSAStartUp = true;

#ifdef USE_WIN_DSP_CAPTURE_CAPABILITIES
LoadVoiceCaptureDspDll();
#endif

Sip = new TSip(ClientName,Vers,this->Handle,&ofs->elt);
log_OS_Version(); //result of Get_OS_Version(&osv);
Sip->get_INIDATA(&iniData);

/*

Stun.StunClientProc(&iniData,Sip,ofs->elt);
Sip->sck = exsCreateUDPSocket_ADDR_PORT_ANY();
if(Sip->sck==INVALID_SOCKET)
  {
  createSocketFailed(ofs->elt);
  return;
  }
Sip->getSockName(ofs->elt);
Sip->create_work_threads();      //TCP, TLS and so on
#ifdef Tcp_Sock_Log
so_debug_set_log_cb(sock_debug_f);  //sock_debug_f
#endif

*/

log_result_of_dowloading_dll();
//if(!get_MMI_AudioDevices())     //get_MMI_AudioDevices() for WINDOWS VISTA, WIN 7, WIN 8 and above
   LogAudioDeviceParameters();  //LogAudioDeviceParameters() fo WINDOWS XP and below
contactDirToSip();

/*

if(Sip->uac)
  if(Sip->uac->srst)       //srtp
    if(Sip->uac->srst->Suspended)
       Sip->uac->srst->Resume();    //Do not use Resume_Thread() !!!
if(Sip->uas)
  if(Sip->uas->srst)     //srtp
    if(Sip->uas->srst->Suspended)
       Sip->uas->srst->Resume();    //Do not use Resume_Thread() !!!
TSipRecvThread* SRT = Sip->getTSipRecvThread();
if(SRT)
   SRT->Resume();                   //Do not use Resume_Thread() !!!

if(Sip->checkAccount())
  {
  if((Sip->sip_transport != Sip_Transport_TCP) && (Sip->sip_transport != Sip_Transport_TLS))
      Sip->initRegistrationProc();
  Sip->readContacts();
  }
*/

PPS = new TParallelPhoneStruct;
PPS->Sip = Sip; //!!!
PPS->set_eltp(&ofs->elt);
PPS->readRegistry();               // ParallelPhone
//Sip->readPresenceComment();        // My comment                                 //Moved to TConferenceWin::FormCreate
//Sip->readPresenceContactComment(); // Comments from contacts of my contact list  //Moved to TConferenceWin::FormCreate

/*                                                                                 //Moved to TConferenceWin::FormCreate
#ifdef SIP_Transport_TLS
N6->Visible = false;
#endif
#ifdef Hide_Transport_Menu
N6->Visible = false;
#endif
#ifdef Hide_Video_Menu
VideoCam1->Visible = false;
#endif
 */


rsrtp_init();

//initial_load_user_history();                                                      //Moved to TConferenceWin::FormCreate
/*
if(Im.LCFT)  //Thread для работы с файлом содержащим последние вызовы (Last Calls)  //Moved to TConferenceWin::FormCreate
  {
  TLCSBuf* LCSBuf = new TLCSBuf(READ);   // Запрос на чтение Last Calls
  if(LCSBuf)
    Im.LCFT->push_lcs_buf(LCSBuf);
  }
*/

if(PPS->getActive())
  {
   SOCKET SCK  = PPS->CreateSock();
   PPS->setSCK(SCK);
   PPS->srt_pph = new TSipRecvThread_PPH(true, &ofs->elt, SCK, Sip, MainFormSLS->PPS);
   PPS->uac_pph = new TSipUacThread(true,  &ofs->elt, Sip, 1);
   PPS->uas_pph = new TSipUasThread(true,  &ofs->elt, Sip, 1);
   PPS->spt_pph = new TSipParsThread(true, &ofs->elt, Sip, 1);
   PPS->sst_pph = new TSipSendThread(true, &ofs->elt, SCK, Sip);
  }

            //  TrayMessage_Ext(NIM_ADD,"Contact",2);              //Moved to TConferenceWin::FormCreate
            //  Application->OnMinimize = On_Minimize_Application; //Moved to TConferenceWin::FormCreate
            //  Application->OnRestore  = On_Restore_Application;  //Moved to TConferenceWin::FormCreate
            //  sys_timer.InitTimer();  //Moved to TMainFormSLS::FormCreate

PanelColor = clWhite;
if(ofs->elt)
   ofs->elt->set_check_files_req();
if(PPS->getActive())
   if(PPS->srt_pph)
      PPS->srt_pph->Resume();

if(ofs->elt)
 if(ofs->elt->getlog())
   {
   string TimeStr;
   TDateTime DateTime = DateTime.CurrentDateTime();
   exsDateTime(DateTime,TimeStr);
   string str = "\n" + (string)TimeStr + " TMainFormSLS_CONSTR_END! " + "\n";
   ofs->elt->FputEvt(str, 1);
   }
}
//---------------------------------------------------------------------------
__fastcall TNetStatus_Panel::TNetStatus_Panel(TComponent* Owner)
           : TPanel(Owner)
{
NS = CallBtnState_Active; //Stae of Btn(Image) Change Network State
OnMouseMove = NSP_MouseMove;

NSI = new TImage(this);
NSI->Parent      = this;
NSI->Left        = 10;
NSI->Width       = MainFormSLS->NetStatusImageList->Width; //36;
NSI->Height      = MainFormSLS->NetStatusImageList->Height;//18;
NSI->Top         = 0;
NSI->OnMouseMove = NSI_MouseMove;
NSI->OnMouseDown = NSI_MouseDown;
NSI->OnMouseUp   = NSI_MouseUp;

MainFormSLS->NetStatusImageList->Draw(NSI->Canvas,0,0,On_Line_Active_NSI_INDX,true);
NSI->Refresh();

full_user_name = new TLabel(this);
full_user_name->Parent      = this;
full_user_name->Left        = NSI->Left + NSI->Width + 10;
full_user_name->Top         = 0;
full_user_name->Font->Name  = _font_name_Arial; 
full_user_name->Font->Size  = 10;
//full_user_name->Font->Style = full_user_name->Font->Style << fsBold;

comment = new TLabel(this);
comment->Parent = this;
comment->Top    = full_user_name->Top;
comment->Font->Size  = 10;
comment->Font->Style = comment->Font->Style << fsItalic;
comment->OnMouseUp   =  Comment_MouseUp;
}
//----------------------------------------------------------------------------
void __fastcall TNetStatus_Panel::Clear()
{
int w = NSI->Width;
int h = NSI->Height;
NSI->Canvas->Brush->Color = clWhite;
NSI->Canvas->FillRect(Rect(0,0,w,h));
}
//----------------------------------------------------------------------------
void __fastcall TNetStatus_Panel::Set_Focus()
{
Clear();
MainFormSLS->NetStatusImageList->Draw(NSI->Canvas, 0, 0, Get_Focus_Indx(), true);
NS = CallBtnState_Focus;
NSI->Refresh();
}
//-----------------------------------------------------------------------------
void __fastcall TNetStatus_Panel::Set_Pressed()
{
Clear();
MainFormSLS->NetStatusImageList->Draw(NSI->Canvas, 0, 0, Get_Press_Indx(), true);
NS = CallBtnState_Focus; //Do not set CallBtnState_Push
NSI->Refresh();
}
//-----------------------------------------------------------------------------
void __fastcall TNetStatus_Panel::Clear_Focus()
{
if(NS == CallBtnState_Focus)
  {
  Clear();
  MainFormSLS->NetStatusImageList->Draw(NSI->Canvas, 0, 0, Get_Active_Indx(), true);
  NS = CallBtnState_Active;
  NSI->Refresh();
  }
}
//-----------------------------------------------------------------------------
TNSI_INDX __fastcall TNetStatus_Panel::Get_Focus_Indx()
{
TNSI_INDX rv = On_Line_Focus_NSI_INDX;
switch(MainFormSLS->NS.get_my_network_state()){
      case ClientState_On_Line:
           rv = On_Line_Focus_NSI_INDX;
           break;
      case ClientState_Off_Line:
           rv = Off_Line_Focus_NSI_INDX;
           break;
      case ClientState_Away:
           rv = Away_Focus_NSI_INDX;
           break;
      case ClientState_DND:
           rv = Dnd_Focus_NSI_INDX;
           break;
      }
return rv;
}
//----------------------------------------------------------------------------
TNSI_INDX __fastcall TNetStatus_Panel::Get_Press_Indx()
{
TNSI_INDX rv = On_Line_Press_NSI_INDX;
switch(MainFormSLS->NS.get_my_network_state()){
      case ClientState_On_Line:
           rv = On_Line_Press_NSI_INDX;
           break;
      case ClientState_Off_Line:
           rv = Off_Line_Press_NSI_INDX;
           break;
      case ClientState_Away:
           rv = Away_Press_NSI_INDX;
           break;
      case ClientState_DND:
           rv = Dnd_Press_NSI_INDX;
           break;
      }
return rv;
}
//-----------------------------------------------------------------------------
TNSI_INDX __fastcall TNetStatus_Panel::Get_Active_Indx()
{
TNSI_INDX rv = On_Line_Active_NSI_INDX;
switch(MainFormSLS->NS.get_my_network_state()){
      case ClientState_On_Line:
           rv = On_Line_Active_NSI_INDX;
           break;
      case ClientState_Off_Line:
           rv = Off_Line_Active_NSI_INDX;
           break;
      case ClientState_Away:
           rv = Away_Active_NSI_INDX;
           break;
      case ClientState_DND:
           rv = Dnd_Active_NSI_INDX;
           break;
      }
return rv;
}
//-----------------------------------------------------------------------------
__fastcall TCall_Panel::TCall_Panel(TComponent* Owner)
           : TPanel(Owner)
{
::InitializeCriticalSection(&ccl_q_cs);
::InitializeCriticalSection(&ccl_cs);
call_type       = Call_Type_Regular;
call_state      = Call_State__Unknown;
lt              = Lt_NDef;
referred_call_panel_tag = 0;
file_transfer_complete  = false;
conf_host         = false;
conf_participant  = false;
conf_creator      = -1;
RESP_200_OK_RCVD  = false;
//conf_contact_id = -1;
disc_img        = NULL;
cam_img         = NULL;
mic_img         = NULL;
speak_img       = NULL;
conf_img        = NULL;
dial_img        = NULL;
refer_img       = NULL;
screen_img      = NULL;
chat_img        = NULL;
conn_img        = NULL;
lochold_img     = NULL;
remhold_img     = NULL;
btn_0           = NULL;
btn_1           = NULL;
progbar         = NULL;
lb              = NULL;
lb_1            = NULL;
lb_2            = NULL;
t_trn_f         = NULL;
t_rcv_f         = NULL;
sss_loc         = NULL;
sss_rem         = NULL;

cam_img_visible = false;

disc_img__default_left   = 0;
cam_img__default_left    = 0;
mic_img__default_left    = 0;
speak_img__default_left  = 0;
conf_img__default_left   = 0;
dial_img__default_left   = 0;
refer_img__default_left  = 0;
screen_img__default_left = 0;
chat_img__default_left   = 0;
default_left             = true;

screen_sharing_active = false;
connected_to_pph      = false;
hstry_written         = false;
}
//---------------------------------------------------------------------------
__fastcall TCall_Panel::~TCall_Panel()
{
if(MainFormSLS->CC_Panel->Visible)     //Conference_Panel
  if(MainFormSLS->CC_DrawGrid->Tag == Tag)
     MainFormSLS->CC_Panel->Hide();
if(t_trn_f)
  {
  TTransmitFileThread* tft = t_trn_f;
  t_trn_f = NULL;
  tft->Terminate();
  tft->Resume_Thread();
  tft->WaitFor();
  delete tft;
  }
if(t_rcv_f)
  {
  TReceiveFileThread* rtf = t_rcv_f;
  t_rcv_f = NULL;
  rtf->Terminate();
  rtf->Resume_Thread();
  rtf->WaitFor();
  delete rtf;
  }
delete_screen_sharing_structs();
if(screen_sharing_active)
  {
  screen_sharing_active = false;
  rdp_stop_sharing();  //ScreenSharing
  rdp_destroy();
  }
::DeleteCriticalSection(&ccl_q_cs);
::DeleteCriticalSection(&ccl_cs);
}
//---------------------------------------------------------------------------
void __fastcall TCall_Panel::delete_screen_sharing_structs()
{
if(sss_loc)
   sss_loc->block = true;
if(sss_rem)
   sss_rem->block = true;
if(sss_loc)
  {
  delete sss_loc;
  sss_loc = NULL;
  }
if(sss_rem)
  {
  delete sss_rem;
  sss_rem = NULL;
  }
}
//---------------------------------------------------------------------------
void __fastcall TScreenSharingViewer::ssv_delete_screen_sharing_structs()
{
if(sss_loc)
   sss_loc->block = true;
if(sss_rem)
   sss_rem->block = true;
if(sss_loc)
  {
  delete sss_loc;
  sss_loc = NULL;
  }
if(sss_rem)
  {
  delete sss_rem;
  sss_rem = NULL;
  }
}
//----------------------------------------------------------------------------
void __fastcall TCall_Panel::create_local_connection_for_OUT_screen_sharing()
{
if(sss_loc)
  {
  TScreenSharingStruct* SSS_LOC = sss_loc;
  sss_loc        = NULL;
  SSS_LOC->block = true;
  if(sss_rem)
     sss_rem->block = true;
  delete SSS_LOC;
  }
sss_loc = new TScreenSharingStruct(SSCT_OUT_LOCAL);
if(sss_loc)
  {
  if(sss_rem)
    {
    TIPAddress addr;
    if(sss_rem->get_local_out_addr(addr))
      {
      sss_loc->ss_CS_T = new TScreenSharing__CLIENT_SEND__Thread(true, sss_loc, &MainFormSLS->ofs->elt, MainFormSLS->Sip );
      sss_loc->ss_CS_T->Resume();
      sss_loc->ss_CR_T = new TScreenSharing__CLIENT_RECV__Thread(true, addr.IPAddr, addr.Port, sss_loc, sss_rem, &MainFormSLS->ofs->elt, MainFormSLS->Sip );
      if(sss_rem)
        if(sss_rem->ss_CR_T)
           sss_rem->ss_CR_T->set_opposite_sss(sss_loc);
      sss_loc->ss_CR_T->tag = Tag; //To find this TCall_Panel
      sss_loc->ss_CR_T->Resume();
      }
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TScreenSharingViewer::create_local_connection_for_IN_screen_sharing()
{
if(sss_loc)
  {
  TScreenSharingStruct* SSS_LOC = sss_loc;
  sss_loc        = NULL;
  SSS_LOC->block = true;
  if(sss_rem)
     sss_rem->block = true;
  delete SSS_LOC;
  }
sss_loc = new TScreenSharingStruct(SSCT_IN_LOCAL);
if(sss_loc)
  {
  TIPAddress addr;    //dummy !!!
  sss_loc->ss_CS_T = new TScreenSharing__CLIENT_SEND__Thread(true, sss_loc, &MainFormSLS->ofs->elt, MainFormSLS->Sip );
  sss_loc->ss_CS_T->Resume();
  sss_loc->ss_CR_T = new TScreenSharing__CLIENT_RECV__Thread(true, addr.IPAddr, addr.Port, sss_loc, sss_rem, &MainFormSLS->ofs->elt, MainFormSLS->Sip ); //addr.IPAddr and addr.Port - dummy, not used in SSCT_IN_LOCAL
  if(sss_rem)
    if(sss_rem->ss_CR_T)
       sss_rem->ss_CR_T->set_opposite_sss(sss_loc);
  sss_loc->ss_CR_T->Resume();
  }
}
//-----------------------------------------------------------------------------
void __fastcall TMainFormSLS::initial_load_user_history()
{
TContact* Contact = NULL;
if(Sip->Contacts.get_sorted_by_full_name())
   Contact = Sip->Contacts.get_contact_by_full_name(0);
else
   Contact = Sip->Contacts.get_contact_by_row(0,false);
if(Contact)
  {
  Im.set_selected_remote_user(Contact->name);
  Im.load_user_history();
  }
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::exs_write_reg_pid_value()
{
unsigned long mProcessID = 0;
GetWindowThreadProcessId(Handle,&mProcessID);
TRegistry& regKey = *new TRegistry();
regKey.RootKey = ROOT_KEY;
bool keyGood = regKey.OpenKey(key_name.c_str(),false);
if(keyGood)
  {
  keyGood = regKey.OpenKey(pid.c_str(),false);
  if(!keyGood)
     keyGood = regKey.OpenKey(pid.c_str(),true);
  if(keyGood)
    regKey.WriteInteger(pid_value.c_str(),mProcessID);
  }
delete &regKey;
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::contactDirToSip()
{
Sip->contact_dir = cont_dir;
}
//---------------------------------------------------------------------------
void __fastcall TSysTimer::InitTimer()
{
timer = new TTimer(MainFormSLS);
timer->Interval = 1000; //1 sec
timer->OnTimer  = MainFormSLS->Timer1Timer;
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::Timer1Timer(TObject *Sender)
{
try{
sys_timer.timer->Enabled = false;

try{
TSipSendThread* SST = Sip->getTSipSendThread();
if(SST)
  if(SST->Suspended)
    if(!SST->QueueEmpty())
        SST->Resume_Thread();
if(Sip->uac)
  if(Sip->uac->Suspended)
    {
    if(!Sip->uac->QueueEmpty())
      Sip->uac->Resume_Thread();
    else if(!Sip->uac->IsResendEmpty())
      Sip->uac->Resume_Thread();
    }
if(Sip->spt)
  if(Sip->spt->Suspended)
    if(!Sip->spt->QueueEmpty())
        Sip->spt->Resume_Thread();
if(Sip->uas)
  if(Sip->uas->Suspended)
    {
    if(!Sip->uas->QueueEmpty())
      Sip->uas->Resume_Thread();
    else if(!Sip->uas->IsResendEmpty())
      Sip->uas->Resume_Thread();
    }
if(Sip->ucs)
  if(Sip->ucs->Suspended)
    if(!Sip->ucs->isReqToDelEmpty())
        Sip->ucs->Resume_Thread();
}//try
catch(Exception& e){exsSstEXCEPTION(ofs->elt,"__CheckSuspendedThreads",e);}

/*
if(ContactMenu->Visible)
  if((GetKeyState(VK_LBUTTON) & 0x80) == 0x80)
    {
    if(get_cursor_position())
       ContactMenu->Close();
  }
 */

if(!cps.req_to_del_panel.empty())       //Deletion of closed TCall_Panel
  {
  for(unsigned i=0;i<cps.req_to_del_panel.size();i++)
     {
     int tag = cps.req_to_del_panel[i];
     for(int i = 0; i < ControlCount; i++)
        {
        TCall_Panel* Panel = dynamic_cast<TCall_Panel*>(Controls[i]);
        if(Panel)
          if(Panel->Tag == tag)
            {
            cps.del_panel_tag(tag,CL_DrawGrid);
            delete Panel;
            getBottomCallPanelMargin();
            break;
            }
        }
     }
  cps.req_to_del_panel.clear();
  if(intrfStyle == 0)
     Panel2->Top = Panel1->Top + Panel1->Height;
::PostMessage(Handle, CONTROL_MSG, WM_APP_MSG_WPARAM__IM__DRAWGRID_RESIZE_ON_CHANGE_CALL_COUNT, WM_APP_MSG_LPARAM__NOPARAM);
  }

if(RS.get_subscr_proc_active())      //On prog start try to subscribe to all presence candidates
   RS.proc_subscr_queue();
else if(NS.get_notify_proc_active())  //Notification subscribed to me clients about changing my network status
   NS.notify_subscribed_clients_about_change_network_status();
else if(NS.get_notify_comment_proc_active())
   NS.notify_comment();

switch(Sip->sip_transport){
      case Sip_Transport_TCP:
           if(!Sip->TCP_Dropped)
              Sip->Contacts.Refresh_Presence_Subscribe();  //Отправить новый SUBSCRIBE, если таймер истек, тем абонентам от которых ранее был получен 202 Responce
           break;
      case Sip_Transport_TLS:
           if(!Sip->TLS_Dropped)
              Sip->Contacts.Refresh_Presence_Subscribe();  //Отправить новый SUBSCRIBE, если таймер истек, тем абонентам от которых ранее был получен 202 Responce
           break;
      default: Sip->Contacts.Refresh_Presence_Subscribe(); //Отправить новый SUBSCRIBE, если таймер истек, тем абонентам от которых ранее был получен 202 Responce
           break;
      }

if(req_to_close_conf_panel)
  {
  req_to_close_conf_panel = false;
  if(SCP)
    {
    delete SCP;
    SCP = NULL;
    }
  }
DLTS.check_to_del();
if(sys_timer.day_end())
  if(ofs->elt)
    {
    ofs->elt->setReopenReq(2);
    ofs->elt->set_check_files_req();
    }

FEXCH.check_file_exch_activity();   //В данный список добавление строки нотификации о файле происходит по щелчку по иконке пришедшего сообщения в истории вызовов и сообщений

#ifdef Automatic_Out_Calls
if(AOC.active)         //used for perfomance testing of mfswith, rtpserver
 if(!AOC.empty())
   AOC.makecalls();
#endif

sys_timer.timer->Enabled = true;
}//try
catch(Exception& e){exsSstEXCEPTION(ofs->elt,"__Timer1Timer()",e);}
}
//----------------------------------------------------------------------------
void   __fastcall TReconnectSubscribe::proc_subscr_queue()
{
try{
::EnterCriticalSection(&sqs);
  if(subscr_queue.empty())
     subscr_proc_active = false;
  else
    {
    for(int i = 0; i < 8; i++)
       {
       if(subscr_queue.empty())
          break;
       TContact contact = subscr_queue.front();
       subscr_queue.pop();
       MainFormSLS->Sip->init_SUBSCRIBE_Proc(contact,contact.subscription_expires);
       }
    }
::LeaveCriticalSection(&sqs);
}
catch(Exception& e){exsSstEXCEPTION(MainFormSLS->ofs->elt,"__proc_subscr_queue()",e);}
}
//----------------------------------------------------------------------------
void __fastcall TReconnectSubscribe::push_contact(TContact& Contact)
{
::EnterCriticalSection(&sqs);
  subscr_queue.push(Contact);
::LeaveCriticalSection(&sqs);
}
//-----------------------------------------------------------------------------
void __fastcall TReconnectSubscribe::clear()
{
::EnterCriticalSection(&sqs);
  while(!subscr_queue.empty())
        subscr_queue.pop();
::LeaveCriticalSection(&sqs);
}
//-----------------------------------------------------------------------------
void   __fastcall TNotifyStruct::init_notify_proc(ClientState cs)
{
MainFormSLS->NS.set_my_network_state(cs);
MainFormSLS->NS.clear_notify_queue();
MainFormSLS->Sip->Contacts.SS.get_temp_subscribed_list(this);
if(!notify_queue_empty())
   MainFormSLS->NS.set_notify_proc_active(true);
}
//------------------------------------------------------------------------------
void  __fastcall TNotifyStruct::init_notify_comment_proc(const string& comment)
{
MainFormSLS->Sip->Contacts.SS.get_temp_subscribed_list_for_send_comment(this,comment);
if(!notify_comment_queue_empty())
    MainFormSLS->NS.set_notify_comment_proc_active(true);
}
//-----------------------------------------------------------------------------
void __fastcall TNotifyStruct::notify_subscribed_clients_about_change_network_status()
{
if(notify_queue_empty())
   set_notify_proc_active(false);
else
  {
  for(int i = 0; i < 10; i++)
     {
     proc_notify_queue_element();
     if(notify_queue_empty())
        break;
     }
  }
}
//-----------------------------------------------------------------------------
void __fastcall TNotifyStruct::notify_comment()
{
if(notify_comment_queue_empty())
   set_notify_comment_proc_active(false);
else
  {
  for(int i = 0; i < 10; i++)
     {
     proc_notify_comment_queue_element();
     if(notify_comment_queue_empty())
        break;
     }
  }
}
//-----------------------------------------------------------------------------
void __fastcall TNotifyStruct::set_my_network_state(ClientState a)
{
my_network_state = a;
reflect_my_network_state();
}
//-----------------------------------------------------------------------------
void __fastcall TNotifyStruct::reflect_my_network_state()
{
if(MainFormSLS->NSP)
  {
   MainFormSLS->NSP->Clear();
   switch(my_network_state){
      case ClientState_On_Line:
           MainFormSLS->NetStatusImageList->Draw(MainFormSLS->NSP->NSI->Canvas,0,0,On_Line_Active_NSI_INDX,true);
           MainFormSLS->NSP->full_user_name->Enabled = true;
           break;
      case ClientState_Away:
           MainFormSLS->NetStatusImageList->Draw(MainFormSLS->NSP->NSI->Canvas,0,0,Away_Active_NSI_INDX,true);
           MainFormSLS->NSP->full_user_name->Enabled = true;
           break;
      case ClientState_DND:
           MainFormSLS->NetStatusImageList->Draw(MainFormSLS->NSP->NSI->Canvas,0,0,Dnd_Active_NSI_INDX,true);
           MainFormSLS->NSP->full_user_name->Enabled = true;
           break;
      case ClientState_Off_Line:
           MainFormSLS->NetStatusImageList->Draw(MainFormSLS->NSP->NSI->Canvas,0,0,Off_Line_Active_NSI_INDX,true);
           MainFormSLS->NSP->full_user_name->Enabled = false;
           break;
      default:
           MainFormSLS->NetStatusImageList->Draw(MainFormSLS->NSP->NSI->Canvas,0,0,On_Line_Active_NSI_INDX,true);
           MainFormSLS->NSP->full_user_name->Enabled = true;
           break;
      }
   MainFormSLS->NSP->NSI->Refresh();
   }
}
//-----------------------------------------------------------------------------
/*
bool __fastcall TMainFormSLS::get_cursor_position()
{
TPoint pt;
if(::GetCursorPos(&pt))           //!!! Do not use Mouse->CursorPos.x. Error 5 - Отказано в доступе к структуре Mouse при старте другой программы в от имени администратора
  {
  if(Left > pt.x)           return false;
  if((Left + Width) < pt.x) return false;
  if(Top > pt.y)            return false;
  if((Top + Height) < pt.y) return false;
  }
return true;
}
*/
//----------------------------------------------------------------------------
void __fastcall TMainFormSLS::createSocketFailed(TEventLogThread* elt)
{
if(elt)
 if(elt->getlog())
   {
   string TimeStr;
   TDateTime DateTime = DateTime.CurrentDateTime();
   exsDateTime(DateTime,TimeStr);
   string str = "\nCreate Socket Failed";
   elt->FputEvt(str, 1);
   }
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::FormClose(TObject *Sender, TCloseAction &Action)
{
sys_timer.timer->Enabled = false;
clear_call_ExchLst();
clear_videoout_ExchLst();
clear_filetrans_ExchLst();
if(AecDll.Initiated)
  if(AecDll.pFunc_UnInit)
    (*AecDll.pFunc_UnInit)();
if(PPS)
   delete PPS;    //Must be deleted before Sip deletion 
if(Sip)
  {
  delete Sip;
  Sip = NULL;  //!!! Protection from access violation on exit
  }
if(WSAStartUp)     //Do not move up
   WSACleanup();
if(ofs)
  {
  TOutputLogFileStruct* OFS = ofs;
  ofs = NULL;
  delete OFS;
  }
rdp_destroy();
}
//---------------------------------------------------------------------------
void __fastcall TIniData::ReadIniData()
{
ReadLogIniData();
ReadStunIniData();
ReadSipProxyData();
ReadSipLocalProxyData();
ReadSipTunnelIniData();
ReadSipLocalTunnelIniData();
ReadFileTransferIniData();
ReadAccountIniData();
ReadSipTcpIniData();
ReadSipTlsIniData();
ReadTransport();
ReadSignalIniData();
ReadSubscDBIniData();
ReadScreenSharringIniData();
ReadMediaIniData();
ReadG729IniData();
}
//---------------------------------------------------------------------------
void __fastcall TIniData::ReadLogIniData()
{
string strLog = ifl->ReadString(SipClient_LOG_IS.c_str(),SipClient_LOG.c_str(),SC_NullString.c_str()).c_str();
CheckIniData(strLog);
log = strtoint(strLog);
}
//---------------------------------------------------------------------------
void __fastcall TIniData::ReadStunIniData()
{
string stunServer = ifl->ReadString(Stun_IS.c_str(),Stun_Server_ID.c_str(),SC_NullString.c_str()).c_str();
CheckIniData(stunServer);
StunIniData.Addr = stunServer;
}
//---------------------------------------------------------------------------
void __fastcall TIniData::ReadSipProxyData()
{
string s = ifl->ReadString(Sip_IS.c_str(),Sip_Proxy_ID.c_str(),SC_NullString.c_str()).c_str();
CheckIniData(s);
SipProxyData.Addr = s;
s = ifl->ReadString(Sip_IS.c_str(),Sip_Proxy_Port_ID.c_str(),SC_NullString.c_str()).c_str();
CheckIniData(s);
SipProxyData.Port = s;
s = ifl->ReadString(Sip_IS.c_str(),RegInt_ID.c_str(),SC_NullString.c_str()).c_str();
CheckIniData(s);
SipProxyData.RegInt = s;
}
//------------------------------------------------------------------------------
void __fastcall TIniData::ReadSipLocalProxyData()
{
string s = ifl->ReadString(Sip_IS.c_str(),Sip_Local_Proxy_ID.c_str(),SC_NullString.c_str()).c_str();
CheckIniData(s);
SipLocalProxyData.Addr = s;
s = ifl->ReadString(Sip_IS.c_str(),Sip_Local_Proxy_Port_ID.c_str(),SC_NullString.c_str()).c_str();
CheckIniData(s);
SipLocalProxyData.Port = s;
}
//------------------------------------------------------------------------------
void __fastcall TIniData::ReadSipTunnelIniData()
{
string s = ifl->ReadString(Sip_Tunnel_IS.c_str(),Sip_Tunnel_Addr_ID.c_str(),SC_NullString.c_str()).c_str();
CheckIniData(s);
SipTunnelData.Addr = s;
s = ifl->ReadString(Sip_Tunnel_IS.c_str(),Sip_Tunnel_Port_ID.c_str(),SC_NullString.c_str()).c_str();
CheckIniData(s);
SipTunnelData.Port = s;
}
//---------------------------------------------------------------------------
void __fastcall TIniData::ReadSipTcpIniData()
{
string s = ifl->ReadString(Sip_Tcp_IS.c_str(),Sip_Tcp_Addr_ID.c_str(),SC_NullString.c_str()).c_str();
CheckIniData(s);
SipTcp.Addr = s;
s = ifl->ReadString(Sip_Tcp_IS.c_str(),Sip_Tcp_Port_ID.c_str(),SC_NullString.c_str()).c_str();
CheckIniData(s);
SipTcp.Port = s;
}
//---------------------------------------------------------------------------
void __fastcall TIniData::ReadSipTlsIniData()
{
string s = ifl->ReadString(Sip_Tls_IS.c_str(),Sip_Tls_Addr_ID.c_str(),SC_NullString.c_str()).c_str();
CheckIniData(s);
SipTls.Addr = s;
s = ifl->ReadString(Sip_Tls_IS.c_str(),Sip_Tls_Port_ID.c_str(),SC_NullString.c_str()).c_str();
CheckIniData(s);
SipTls.Port = s;
}
//---------------------------------------------------------------------------
void __fastcall TIniData::ReadSubscDBIniData()
{
string s = ifl->ReadString(SubscDB_IS.c_str(), Addr_ID.c_str(), SC_NullString.c_str()).c_str();
CheckIniData(s);
SubscDB.Addr = s;
s = ifl->ReadString(SubscDB_IS.c_str(), Port_ID.c_str(), SC_NullString.c_str()).c_str();
CheckIniData(s);
SubscDB.Port = s;
}
//---------------------------------------------------------------------------
void __fastcall TIniData::ReadScreenSharringIniData()
{
string s = ifl->ReadString(ScreenSharing_IS.c_str(), Addr_ID.c_str(), SC_NullString.c_str()).c_str();
CheckIniData(s);
ScreenSharing.Addr = s;
s = ifl->ReadString(ScreenSharing_IS.c_str(), Port_ID.c_str(), SC_NullString.c_str()).c_str();
CheckIniData(s);
ScreenSharing.Port = s;
}
//---------------------------------------------------------------------------
void __fastcall TIniData::ReadSipLocalTunnelIniData()
{
string s = ifl->ReadString(Sip_Tunnel_IS.c_str(),Sip_Local_Tunnel_Addr_ID.c_str(),SC_NullString.c_str()).c_str();
CheckIniData(s);
SipLocalTunnelData.Addr = s;
s = ifl->ReadString(Sip_Tunnel_IS.c_str(),Sip_Local_Tunnel_Port_ID.c_str(),SC_NullString.c_str()).c_str();
CheckIniData(s);
SipLocalTunnelData.Port = s;
}
//----------------------------------------------------------------------------
void __fastcall TIniData::ReadFileTransferIniData()
{
string s = ifl->ReadString(File_IS.c_str(),FTransfer_Proxy_Addr_ID.c_str(),SC_NullString.c_str()).c_str();
CheckIniData(s);
FTransferIniData.Addr = s;
s = ifl->ReadString(File_IS.c_str(),FTransfer_Proxy_Port_ID.c_str(),SC_NullString.c_str()).c_str();
CheckIniData(s);
FTransferIniData.Port = s;
}
//---------------------------------------------------------------------------
void __fastcall TIniData::ReadAccountIniData()
{
ReadUserName();
ReadDomainName();
ReadDisplayName();
}
//---------------------------------------------------------------------------
void __fastcall TIniData::ReadTransport()
{
ReadSipTransport();
}
//---------------------------------------------------------------------------
void __fastcall TIniData::ReadSignalIniData()
{
ReadAlertingType();
}
//---------------------------------------------------------------------------
void __fastcall TIniData::ReadMediaIniData()
{
ReadPortRange();
}
//---------------------------------------------------------------------------
void __fastcall TIniData::ReadG729IniData()
{
ReadG729Annexb();
}
//---------------------------------------------------------------------------
void __fastcall TIniData::ReadAlertingType()
{
string alertingtype = ifl->ReadString(Signal_IS.c_str(),Alerting_Type_ID.c_str(),SC_NullString.c_str()).c_str();
CheckIniData(alertingtype);
SignalIniData.AlertingType = alertingtype;
}
//---------------------------------------------------------------------------
void __fastcall TIniData::ReadSipTransport()
{
string sip_transport = ifl->ReadString(SipTransport_IS.c_str(),SignType_ID.c_str(),SC_NullString.c_str()).c_str();
CheckIniData(sip_transport);
TransportIniData.SipTransport = sip_transport;
}
//---------------------------------------------------------------------------
void __fastcall TIniData::ReadPortRange()
{
string s = ifl->ReadString(Media_IS.c_str(),MStrtPort_ID.c_str(),SC_NullString.c_str()).c_str();
CheckIniData(s);
MediaIniData.MStartPort=s;
s = ifl->ReadString(Media_IS.c_str(),MEndPort_ID.c_str(),SC_NullString.c_str()).c_str();
CheckIniData(s);
MediaIniData.MEndPort=s;
s = ifl->ReadString(Media_IS.c_str(),MInt_ID.c_str(),SC_NullString.c_str()).c_str();
CheckIniData(s);
MediaIniData.MInt=s;
}
//---------------------------------------------------------------------------
void __fastcall TIniData::ReadG729Annexb()
{
string s = ifl->ReadString(G729_IS.c_str(),Annexb_ID.c_str(),SC_NullString.c_str()).c_str();
CheckIniData(s);
G729IniData.annexb = s;
}
//---------------------------------------------------------------------------
void __fastcall TIniData::ReadUserName()
{
string userName = ifl->ReadString(Account_IS.c_str(),User_Name_ID.c_str(),SC_NullString.c_str()).c_str();
CheckIniData(userName);
AccountIniData.UserName = userName;
}
//---------------------------------------------------------------------------
void __fastcall TIniData::ReadDomainName()
{
string domain = ifl->ReadString(Account_IS.c_str(),Domain_Name_ID.c_str(),SC_NullString.c_str()).c_str();
CheckIniData(domain);
AccountIniData.Domain = domain;
}
//---------------------------------------------------------------------------
void __fastcall TIniData::ReadDisplayName()
{
string display_name = ifl->ReadString(Account_IS.c_str(),Display_Name_ID.c_str(),SC_NullString.c_str()).c_str();
CheckIniData(display_name);
AccountIniData.DisplayName = display_name;
}
//---------------------------------------------------------------------------
int __fastcall TIniData::findTerminationSymbol(string& s)
{
int st = s.find("#");
if(st == -1)
   {
   st = s.find("//");
   if(st==-1)
     {
     st=s.find("\\");
     if(st==-1)
       return s.find(";");
     }
   }
return st;
}
//---------------------------------------------------------------------------
void __fastcall TIniData::trimString(string& s,int st)
{
if(s.empty())return;
const char* buf = s.c_str();
int i=st-1;
for(;i>0;i--)
   if(buf[i]!=WS_Char)
      break;
if(i)
  s.resize(i+1);
}
//----------------------------------------------------------------------------
void __fastcall TIniData::CheckIniData(string& s)
{
int st = findTerminationSymbol(s);
if(st==-1)return;
trimString(s,st);
}
//----------------------------------------------------------------------------
void __fastcall TMainFormSLS::Get_Sip_UA_Msg(TMessage &Message)
{
try{
switch(Message.WParam){
      case WM_APP_MSG_WPARAM__UAC:
           Proc_UAC_Msg(Message);
           break;
      case WM_APP_MSG_WPARAM__UAS:
           Proc_UAS_Msg(Message);
           break;
      }
}//try
catch(Exception& e){exsSstEXCEPTION(ofs->elt,"__Get_Sip_UA_Msg(TMessage &Message)",e);}
}
//----------------------------------------------------------------------------
void __fastcall TMainFormSLS::Get_FILE_TRANSFER_MSG(TMessage &Message)
{
try{
switch(Message.WParam){
       case WM_APP_MSG_WPARAM__FILE_TRANS_INIT_MSG:
            Proc_FILE_TRANS_INIT_Msg(Message);
            break;
       case WM_APP_MSG_WPARAM__FILE_TRANS_START_MSG:
            Proc_FILE_TRANS_START_Msg(Message);
            break;
       case WM_APP_MSG_WPARAM__FILE_TRANS_END:
            Proc_FILETRANS_Msg(Message);
            break;
       case WM_APP_MSG_WPARAM__FILE_RECV_END:
            Proc_FILE_RECV_Msg(Message);
            break;
       case WM_APP_MSG_WPARAM__FILE_PENDING_MSG:
            Proc_FILE_PENDING_Msg(Message);
            break;
      }
}//try
catch(Exception& e){exsSstEXCEPTION(ofs->elt,"__Get_FILE_TRANSFER_MSG(TMessage &Message)",e);}
}
//----------------------------------------------------------------------------
void __fastcall TMainFormSLS::Get_CALL_MSG(TMessage &Message)
{
try{
switch(Message.WParam){
       case WM_APP_MSG_WPARAM__CALL_IN:
            Proc_CALL_IN_Msg(Message);
            break;
       case WM_APP_MSG_WPARAM__CALL_OUT:
            Proc_CALL_OUT_Msg(Message);
            break;
      }
}//try
catch(Exception& e){exsSstEXCEPTION(ofs->elt,"__Get_CALLIN_MSG(TMessage &Message)",e);}
}
//----------------------------------------------------------------------------
void __fastcall TMainFormSLS::Get_CONTROL_MSG(TMessage &Message)
{
try{
switch(Message.WParam){
       case WM_APP_MSG_WPARAM__CLOSE_COMMENT_PANEL:
            Proc__CLOSE_COMMENT_PANEL_MSG();
            break;
       case WM_APP_MSG_WPARAM__DBI_DATA:
            Proc__DBI_DATA();
            break;
       case WM_APP_MSG_WPARAM__SCREEN_SHARING_OUT_DATA:
            Proc__SCREEN_SHARING_OUT_DATA();
            break;
       case WM_APP_MSG_WPARAM__SCREEN_SHARING_IN_DATA:
            Proc__SCREEN_SHARING_IN_DATA();
            break;
       case WM_APP_MSG_WPARAM__LAST_CALLS__DRAWGRID_ROW_COUNT:
            DG_LastCalls->RowCount = Message.LParam;
            break;
       case WM_APP_MSG_WPARAM__IM__DRAWGRID_ROW_COUNT_ON_SEND_TEXT_MSG: //added single hstry msg on send IM
            IM_DrawGrid->RowCount = Message.LParam;
            Display_Last_Instant_Msg();
            IM_DrawGrid->Repaint();
            break;
       case WM_APP_MSG_WPARAM__IM__DRAWGRID_RESIZE_ON_CHANGE_CALL_COUNT:
            IM_DrawGrid_Resize();
            break;
       case WM_APP_MSG_WPARAM__IM__DRAWGRID_ROW_COUNT:                  //added single hstry msg
            IM_DrawGrid->RowCount = Message.LParam;
               Im.SetRowHeightsForLast_25_HSTRY_Msgs(IM_DrawGrid);
            IM_DrawGrid_Resize();
            if(IM_DrawGrid->RowCount)
               IM_DrawGrid->Row = IM_DrawGrid->RowCount - 1;
            IM_DrawGrid->Repaint();
            break;
       case WM_APP_MSG_WPARAM__IM_READBLOCK__DRAWGRID_ROW_COUNT:  //added block of hstry msgs by read hstry file
            IM_DrawGrid->RowCount = Message.LParam;
            Im.SetRowHeightsForLast_25_HSTRY_Msgs(IM_DrawGrid);
            IM_DrawGrid_Resize();
            REFRESH_IM_DRAW_GRID();
            break;
       case WM_APP_MSG_WPARAM__IM_READBLOCK__ONTOP_DRAWGRID_ROW_COUNT:
            IM_DrawGrid->RowCount = Message.LParam;
            Im.SetRowHeightsForLast_25_HSTRY_Msgs(IM_DrawGrid);
            IM_DrawGrid_Resize();
            if(IM_DrawGrid->RowCount)
               IM_DrawGrid->Row = IM_DrawGrid->RowCount - 1;
            REFRESH_IM_DRAW_GRID();
            break;
       case WM_APP_MSG_WPARAM__INIT_REG_PROC:
            if(lng == Lang_RU)
               Caption = "Регистрация...";
            else
               Caption = "Initializing...";
            if(Sip)  //!!! see FormClose()
              Sip->initRegistrationProc();
            break;
       case WM_APP_MSG_WPARAM__TCP_CONNECTION_DROPPED:
            ICB.del_all_waiting_ans_calls();
            RS.set_subscr_proc_active(false);
            RS.clear();
            Sip->set_init_subscribe(false);
            Sip->Contacts.set_state_for_all_contacts(ClientState_Off_Line);
            DrawGrid1->Repaint();
            if(lng == Lang_RU)
               Caption = "Потеряно соединение с сервером!";
            else
               Caption = "Connection Lost!";
            break;
       case WM_APP_MSG_WPARAM__IM_REPAINT:
            IM_DrawGrid->Repaint();
            break;
       case WM_APP_MSG_WPARAM__SELECT_FIRST_MISSED_CALL:
            PROC_CONTROL();
            break;
      }
}//try
catch(Exception& e){exsSstEXCEPTION(ofs->elt,"__Get_CONTROL_MSG(TMessage &Message)",e);}
}
//----------------------------------------------------------------------------
void __fastcall TMainFormSLS::PROC_CONTROL()
{
bool rez = true;
while(rez){
     TCtrlExch CE = CES.get();
     rez = CE.get_actual();
     if(rez)
       {
       switch(CE.WPARAM){
             case WM_APP_MSG_WPARAM__SELECT_FIRST_MISSED_CALL:{
                  TContact ContCopy(-1);
                  if(Sip->Contacts.get_contact_copy_by_user_name(ContCopy, CE.s1))
                    {
                    Activate_Contacts_TabSheet();
                    int row_id = Sip->Contacts.get_row_id_by_contact_name(CE.s1,ContCopy);
                    if(Sip->Contacts.get_sorted_by_full_name())
                       row_id = Sip->Contacts.get_row_by_contact_id_in_sorted_contact_list(ContCopy.get_id());
                    if(row_id != -1)
                      {
                      if(Im.get_selected_remote_user()!= CE.s1)
                        {
                        Im.curr_hstry_period = -1;
                        Im.set_selected_remote_user(CE.s1);
                        Im.load_user_history();
                        }
                      if(row_id < DrawGrid1->RowCount)
                        {
                        if(row_id)
                          {  //Если данная строка выбрана (DrawGrid1->Row == row_id) но невидима, то данная операция (временное изменение номера текущей строки) сделает ее видимой)
                          DrawGrid1->Row = row_id - 1;
                          DrawGrid1->Row = row_id;
                          }
                        user_name_to_send      = ContCopy.name;
                        if(ContCopy.CT == ContactType_GROUP)
                           set_IM_to_chat_participants(true);
                        else
                           set_IM_to_chat_participants(false);
                        ComboBox1->Text        = ContCopy.full_name.c_str();
                        CalledNameLbl->Caption = ContCopy.full_name.c_str();
                        DrawGrid1->Repaint();
                        }
                      }
                    }
                  else
                    Activate_LastCall_TabSheet();
                  }
                  break;
             }
       }
     }
}
//-------------------------------------------------------------------------
void __fastcall TMainFormSLS::Proc__CLOSE_COMMENT_PANEL_MSG()
{
TCommentPanel* nscp = NSCP;
NSCP = NULL;
delete nscp;
}
//----------------------------------------------------------------------------
void __fastcall TMainFormSLS::update_contacts_time_stmp(const string& s)
{
Sip->Contacts.time_stmp = s;
string user = get_current_user();
string s_cl = get_clients_dir();
s_cl += "\\" + user + "\\" + get_CONTACTS_DIR();
if(::DirectoryExists(s_cl.c_str()))
  {
  s_cl += "\\tstmp.tsp";
  FILE* f = fopen(s_cl.c_str(),"wt");
  if(f)
    {
    fputs(s.c_str(),f);
    fclose(f);
    }
  }
}
//----------------------------------------------------------------------------
void __fastcall TMainFormSLS::Proc__DBI_DATA()
{
while(!EnterpriseSubscList->DBIExch.empty())
     {
     TDBData dbd = EnterpriseSubscList->DBIExch.get();
     if(dbd.actual)
       {
       switch(dbd.SDMT){
              case ServDbMsgType_REQ_START_SUBSCR_DATA:{   // получение данных ТОЛЬКО для владельца данного softphone (Accoun data)!!!
                   Sip->Account.set_displayname(dbd.s_2);
                   if(dbd.u_1 != -1)         //Если == -1, то Sip->Account.cos остается равным 0
                      Sip->Account.cos = dbd.u_1;
                   Sip->display_full_ser_name();
                   TContact Contact;
                   Contact.name      = dbd.s_1;
                   Contact.full_name = dbd.s_2;
                   Contact.cos       = dbd.u_1;
                   Sip->Contacts.add_contact_name_to_actual_directory(&Contact);
                   if(Im.LCFT)  //Thread для работы с файлом содержащим последние вызовы (Last Calls)
                     {
                     TLCSBuf* LCSBuf = new TLCSBuf(READ);   // Запрос на чтение Last Calls
                     if(LCSBuf)
                       {
                       LCSBuf->new_registration = true;
                       Im.LCFT->push_lcs_buf(LCSBuf);
                       }
                     }
                   break;
                   }
              case ServDbMsgType_GET_TIMESTAMP:{
                   bool equal = true;
                   if(Sip->Contacts.time_stmp != dbd.s_1)
                     {
                     equal = false;
                     update_contacts_time_stmp(dbd.s_1);
                     EnterpriseSubscList->GET_PERSONAL_CONTACT_LIST(Sip->Account.get_user_name());       //Запрос измененного списка контактов
                     }
             //      else
             //        EnterpriseSubscList->GET_PERSONAL_CONTACT_LIST(Sip->Account.get_user_name());  //Test only. Open above
                   if(ofs->elt)
                     if(ofs->elt->getlog())
                       {
                       string s;
                       if(equal)
                          s = "\ntime_stmp: equal\n";
                       else
                          s = "\ntime_stmp: changed. Personal conatact list requested\n";
                       ofs->elt->FputEvt(s,1);
                       }
                   break;
                   }
              case ServDbMsgType_MODIFY_CONTACT_LIST:
                   if(!dbd.s_1.empty())
                      update_contacts_time_stmp(dbd.s_1);
                   break;
              case ServDbMsgType_GET_PERSONAL_CONTACT_LIST:
                   Proc__DBI_ACK__PERSONAL_CONTACT_LIST(&dbd);
                   break;
              case ServDbMsgType_GET_PERSONAL_CITY_PHONE_LIST:
                   Proc__DBI_ACK__PERSONAL_CITY_PHONE_LIST(&dbd);
                   break;
              } //switch(dbd.SDMT)
       }   //if(dbd.actual)
     } //while(!EnterpriseSubscList->DBIExch.empty())
}
//------------------------------------------------------------------------------
void __fastcall TMainFormSLS::Proc__DBI_ACK__PERSONAL_CONTACT_LIST(TDBData* dbd)
{
Sip->Contacts.update_personal_contact_list(dbd);
}
//------------------------------------------------------------------------------
void __fastcall TMainFormSLS::Proc__DBI_ACK__PERSONAL_CITY_PHONE_LIST(TDBData* dbd)
{
if(dbd->u_3)
  Sip->Contacts.end_of_personal_contact_list(dbd);
else
  Sip->Contacts.update_personal_contact_list(dbd);
}
//------------------------------------------------------------------------------
void __fastcall TMainFormSLS::Proc__SCREEN_SHARING_OUT_DATA()
{
while(!ScreenSh.empty())
     {
     TDBData dbd = ScreenSh.get();
     if(dbd.actual)
       {
       switch(dbd.SDMT){
              case 1: {
                      if(dbd.u_3) //if(dbd.u_3) TScreenSharing__CLIENT_RECV__Thread belongs TConfCont (i.e.)
                        {
                        TCall_Panel* panel = get_Call_Panel_By_Tag(dbd.u_2);
                        if(panel)
                          {
                          string s = dbd.s_1 + "<E1>" + inttostr(dbd.u_1) + "</E1>" + crlf;
                          panel->create_local_OUT_conn_and_send_INVITE_to_conference_by_user_name(s,dbd.s_2); //dbd.s_2 - nick_name, whom will be send Screen_Sharing INVITE
                          }
                        }
                      else
                        {
                        TCall_Panel* panel = get_Call_Panel_By_Tag(dbd.u_2);
                        if(panel)
                          {
                          panel->create_local_connection_for_OUT_screen_sharing();
                          string s = dbd.s_1 + "<E1>" + inttostr(dbd.u_1) + "</E1>" + crlf;
                          Sip->send_ScreenSharing_INVITE(panel, dbd.s_2, s);        //dbd.s_2 - nick_name, whom will be send Screen_Sharing INVITE
                          }
                        }
                      break;
                      }
             }
       }
     }
}
//-----------------------------------------------------------------------------
void __fastcall TMainFormSLS::Proc__SCREEN_SHARING_IN_DATA()
{
while(!ScreenSh.empty())
     {
     TDBData dbd = ScreenSh.get();
     if(dbd.actual)
       {
       switch(dbd.SDMT){
             case 2: {
                     SSV.create_local_connection_for_IN_screen_sharing();
                     break;
                     }
             case 3:{
                    TIPAddress addr;
                    addr.IPAddr = "127.0.0.1";    //  "10.10.98.3";   //"192.168.1.36";           //"0.0.0.0";
                    addr.Port   = dbd.u_2;
                    if(SSV.sss_rem)
                      {
                      string s;
                      SSV.sss_rem->modify_local_addr_for_rdp_connect(addr,s);
                      int sz = s.length();
                      const char* buf = s.c_str();
                      rdp_connect(buf, sz);
                      }
                    break;
                    }
             case 4:{
                    if(SSV.sss_rem)
                      {
                      string s = SSV.sss_rem->get_sharing_string();
                      int sz = s.length();
                      const char* buf = s.c_str();
                      rdp_connect(buf, sz);
                      }
                    break;
                    }
             }
       }
     }
}
//-----------------------------------------------------------------------------
#ifdef SIP_Video
void __fastcall TMainFormSLS::Get_VIDEOOUT_MSG(TMessage &Message)
{
try{
switch(Message.WParam){
       case WM_APP_MSG_WPARAM__VIDEOOUT:
            Proc_VIDEOOUT_Msg(Message);
            break;
      }
}//try
catch(Exception& e){exsSstEXCEPTION(ofs->elt,"__Get_VIDEOOUT_MSG(TMessage &Message)",e);}
}
#endif
//----------------------------------------------------------------------------
void __fastcall TMainFormSLS::ClientRegistered(TExchBuf* buf)
{
try{
bool prev_reg_state = Sip->getRegistered();
Sip->setRegistered(true);
Caption = baseCaption + (WS + WS + WS).c_str() + Sip->Account.get_user_name().c_str();
NS.set_my_network_state(ClientState_On_Line);
Sip->regularRegistrationProc(buf->sls_buf);
if(cbs != CallBtnState_Active)
  {
  cbs = CallBtnState_Active;
  SetVoiceCallBtnState(BtnState_ACTIVE);
  }
if(!Sip->get_init_subscribe())
    Sip->init_on_registration_subscribe_proc();
else if(!prev_reg_state)
    Sip->init_on_registration_subscribe_proc();
Sip->log_selected_transport();
bool time_stmp_requested = false;
TRegistryPanel* RP = Sip->get_rp();
if(RP)
  if(RP->getNewRegistration())
    {
    RP->setNewRegistration(false);
    time_stmp_requested = true;
    EnterpriseSubscList->Create_DBChannel(false,true,true);   //Req TimeStmp, req  Start Data
    }
if(!time_stmp_requested)
  if(LAST_FORM_CREATED)
    {
    bool req_start_data = false;
    if(Sip->Account.get_displayname().empty())
       req_start_data = true;
    EnterpriseSubscList->Create_DBChannel(false, req_start_data, true); //Request ContactList TimeStmp
    }
  else
    TIME_STMP_REQUEST = true;
}//try
catch(Exception& e){exsSstEXCEPTION(ofs->elt,"__TMainFormSLS::ClientRegistered()",e);}
}
//-----------------------------------------------------------------------------
void __fastcall TMainFormSLS::Proc_UAC_Msg_READLIST(TExchBuf* buf, string& s_log)
{
try{
switch(buf->emt){
      case ExchMsgType_Registered:
           ClientRegistered(buf);
           break;
      case ExchMsgType_RegisterFailed:
           Sip->setRegistered(false);
           switch(buf->tag){
                  case 403: if(lng == Lang_RU)
                               Caption = baseCaption + (WS + WS + WS).c_str() +  "\"" + buf->msg.c_str() + "\"" + WS.c_str() + "Абонент не зарегистрирован";
                            else
                               Caption = baseCaption + (WS + WS + WS).c_str() + "Registration Failed. \"" + buf->msg.c_str() + "\" is not a subscriber";
                            break;
                  default: if(lng == Lang_RU)
                              Caption = baseCaption + (WS + WS + WS).c_str() + "Абонент не зарегистрирован";
                           else
                              Caption = baseCaption + (WS + WS + WS).c_str() + "Registration Failed";
                           break;
                  }
           cbs = CallBtnState_NotActive;
           SetVoiceCallBtnState(BtnState_INACTIVE);
          // ImageList_CallBtn->Draw(Image3->Canvas,0,0,3,true);
          // Image3->Refresh();
           NS.set_my_network_state(ClientState_Off_Line);
           break;
      case ExchMsgType_Resp100:{
           TMediaSession* ms = Sip->sss->GetMsOut_by_Callid(buf->msg);
           if(ms)
             ms->setRespState(SPS_TRYING100_RCVD);
           break;
           }
      case ExchMsgType_Resp180:{
           if(!s_log.empty())
               s_log += "\nTMainFormSLS::Proc_UAC_Msg_READLIST()::ExchMsgType_Resp180";
           TMediaSession* ms = Sip->sss->GetMsOut_by_Callid(buf->msg);
           if(ms)
             {
             ms->setRespState(SPS_RINGING180_RCVD);
             TUdpChannel* uc = ms->getSoundChannel();
             if(uc)
               if(uc->wopt)
                  uc->wopt->startAlerting();
             if(PPS->getActive())
               if(!buf->parallel_phone)
                 if(buf->a1 == 0)   //Responce received from normal uac_thread (not from uac_pph)
                   if(!ms->get_source_of_outgoing_call()) //вызов не транзитный от pph
                     if(!ms->get_pph_session_created())  //Сессия для параллельного телефона еще не создана
                       {
                       TSipParsBuf spb;
                       spb.call_id.setprimcallid(buf->msg);
                       spb.sdp.Sdp = buf->msg_1;
                       PPS->Check_OUT_Call_To_ParallelPhone(&spb, ms);  //Send INVITE to parallel phone (if(registered)) and set state to 1 - outseized
                       }
             }
           break;
           }
      case ExchMsgType_Resp183:
           if(!s_log.empty())
              s_log += "\nTMainFormSLS::Proc_UAC_Msg_READLIST()::ExchMsgType_Resp183";
           if(buf->isAddBuf())
            {
            TRemoteMedia* rm = (TRemoteMedia*)buf->getAddBuf_Reset();
            if(rm)
              {
            // Sip->sendInitial_Uac_Rtp_Sequence(RTP_AUDIO_MPT,rm);
              TMediaSession* ms = Sip->sss->GetMsOut_by_Callid(rm->callid);
              if(ms)
                {
                ms->setRespState(SPS_RESP183_RCVD);
                TUdpChannel* uc = ms->getSoundChannel();
                if(uc)
                  {
                  if(uc->wopt)
                     uc->wopt->startReceivingVoice(rm);
                  if(uc->mic)      //for test only
                     uc->mic->startSendingVoice();
                  }
                if(PPS->getActive())
                  if(!buf->parallel_phone)
                    if(buf->a1 == 0)  //Responce received from normal uac_thread (not from uac_pph)
                      if(!ms->get_source_of_outgoing_call()) //вызов не транзитный от pph
                        if(!ms->get_pph_session_created())     //Сессия для параллельного телефона еще не создана
                          {
                          TSipParsBuf spb;
                          spb.call_id.setprimcallid(rm->callid);
                          spb.sdp.Sdp = buf->msg_1;
                          PPS->Check_OUT_Call_To_ParallelPhone(&spb, ms);  //Send INVITE to parallel phone (if(registered)) and set state to 1 - outseized
                          }
                } //if(ms)
              delete rm; //!!!
              } //if(rm)
            }
           break;
      case ExchMsgType_200OK_ON_INVITEREQ:{
           if(!s_log.empty())
               s_log += "\nTMainFormSLS::Proc_UAC_Msg_READLIST()::ExchMsgType_200OK_ON_INVITEREQ";
           if(buf->isAddBuf())
             {
             TRemoteMedia* rm = (TRemoteMedia*)buf->getAddBuf_Reset();
             if(rm)
               {
               TMediaSession* ms = Sip->sss->GetMsOut_by_Callid(rm->callid);
               if(ms)
                 {
                 if(buf->parallel_phone)    //200 OK received from parallel_phone
                   {
                   ms->setRespState(SPS_INVITE200OK_RCVD);
                   if(buf->pr_lt_pph == Lt_In)                //Вызов на PPH был осуществлен от ВХОДЯЩЕГО основного вызова
                     {
                     TForm1* form = ICB.get_form_by_call_id(buf->msg_1);   //in msg_1 <- Lt->lt_parallel_primary_call_id
                     if(form)
                       {
                       form->answer_incoming_call_with_pph(rm->callid);
                       form->closed_by_btn = true;   //!!!!!
                       form->Close();
                       }
                     }
                   else if(buf->pr_lt_pph == Lt_Out)        //Вызов на PPH был осуществлен от ИСХОДЯЩЕГО основного вызова
                     {
                     TMediaSession* ms_prm = Sip->sss->GetMsOut_by_Callid(buf->msg_1);  //in msg_1 <- Lt->lt_parallel_primary_call_id
                     if(ms_prm)
                       {
                       TUdpChannel* uc_rtp = ms_prm->getRtpAudioChannel();
                       if(uc_rtp)
                         {
                         TUdpChannel* uc_rtp_pph = ms->getRtpAudioChannel();
                         if(uc_rtp_pph)
                           {
                           TUdpChannel* uc_audio = ms_prm->getSoundChannel();
                           if(uc_audio)
                             {
                             uc_rtp->Disconnect(uc_audio);
                             uc_audio->Disconnect(uc_rtp);
                             }
                           uc_rtp->Connect(uc_rtp_pph);
                           uc_rtp_pph->Connect(uc_rtp);

                           uc_rtp->printAllMyConnections();
                           uc_rtp_pph->printAllMyConnections();
                           }
                         }
                       }
                     }
                   } //if(buf->parallel_phone)
                 else
                   {
                   if(PPS->getActive())
                     {
                     if(!ms->get_source_of_outgoing_call()) //вызов не транзитный от pph
                       {
                       if(!ms->get_pph_session_created())     //Сессия для параллельного телефона еще не создана
                         {
                         TSipParsBuf spb;
                         spb.call_id.setprimcallid(rm->callid);
                         spb.sdp.Sdp = buf->msg_1;
                         PPS->Check_OUT_Call_To_ParallelPhone(&spb, ms);  //Send INVITE to parallel phone (if(registered)) and set state to 1 - outseized
                         }
                       }
                     else
                       {
                       if(PPS->getActive())
                         if(PPS->uas_pph)
                           {
                           TMediaSession* ms_pph = Sip->sss->GetMsIn_by_Callid(buf->msg_2);  //buf->msg_2 == Lt->pph_call_id   - callid входящего вызова от параллельного телефона
                           //TMediaSession* ms_pph = Sip->sss->GetMs_by_In_Out_Callid(buf->msg_2);
                           if(!ms_pph) //Media session not yet initiated for call received from PPH
                             {
                             TOutputSipBuf* ospb = new TOutputSipBuf;
                             if(ospb)
                               {
                               ospb->setsls(SPS_ANSWER_PPH_REQ);
                               string selected_local_ip = select_local_ip_addr(PPS->regUAddr);
                               PPS->prepareContact_PPH(ospb, selected_local_ip);
                               ospb->CallID = buf->msg_2;
                               Sip->prepareAllow(ospb);
                               Sip->prepareUserAgent(ospb);
                               Sip->prepareContentType(ospb,"application/sdp");
                               PPS->prepare_Sdp_Initial_PPH(&ospb->sdp, selected_local_ip);
                               ospb->sdp.Sdp = buf->msg_1; //buf->msg_1 == spb->sdp.Sdp) Копируется полностью принятый SDP для последующей модификации в TSipUaSThread

                               PPS->uas_pph->setQueue(ospb);
                               Sip->updateSentQueue_1(ospb);

                                    /* TOutputSipBuf* ospb = prepare_Initial_ANSWER_Req(buf,panel->Tag);
                                     if(ospb)
                                      {
                                      } */

                               }
                             }
                           }
                       }
                     }
                   TUdpChannel* uc = ms->getSoundChannel();
                   if(uc)
                     {
                     ms->setRespState(SPS_INVITE200OK_RCVD);
                     if(!ms->get_200_OK_RCVD())
                       {
                       if(uc->wopt)
                          uc->wopt->startReceivingVoice(rm);
                       if(uc->mic)
                          uc->mic->startSendingVoice();
                       ms->set_200_OK_RCVD(true);
                       }
                     }
                   if(!buf->a1)  //if chage_call_panel_block (in case of refer)
                      Answer_On_Outgoing_CallPanel(ms);
                   }
                 } //if(ms)
               delete rm;
               }
             }
           break;
           }
      case ExchMsgType_RCVD_REINVITE_WITH_ADD_VIDEO:      // Получен REINVITE with add video на исходящий вызов
           Sip->activate_Remote_Video_OnReInvite_Recv_With_Add_Video(buf, SipUAThreadType_UAC);
           break;
      case ExchMsgType_DeleteMediaSession:
           Sip->del_CLD_tc(buf->msg_1);   //Удалить из списка called_name -> out_callid
           Sip->sss->EraseMediaSession(buf->callid);   //Уже с префиксом out_
           break;
      case ExchMsgType_RCVD_200OK_ON_CALL_TRANSFER:
           Rcvd_200OK_ON_CALL_TRANSFER(buf->tag, buf->msg, buf->msg_1);
           break;
       case ExchMsgType_NotAcceptable:{
           TMediaSession* ms = Sip->sss->GetMsOut_by_Callid(buf->callid);
           if(ms)
             {
             NotAcceptable_On_Outgoing_CallPanel(ms);
             Play_Sound(playSoundState_Reorder);
             }
           break;
           }
      case ExchMsgType_Busy:{
           TMediaSession* ms = Sip->sss->GetMsOut_by_Callid(buf->callid);
           if(ms)
             {
             Busy_On_Outgoing_CallPanel(ms);
             TUdpChannel* uc = ms->getSoundChannel();
             if(uc)
               if(uc->wopt)
                  uc->wopt->Stop_Alerting_FINALLY();

             TCall_Panel* call_panel = get_Call_Panel_By_Tag(ms->getCallTag());
             if(call_panel)
               if(call_panel->get_conf_participant())
                  call_panel->conference_exit(ms);

             Play_Sound(playSoundState_Busy);
             }
           break;
           }
      case ExchMsgType_Bye:
           Rcvd_ExchMsgType_Bye_OUT(buf);
           break;
      case ExchMsgType_Bye_From_Pph:
           Rcvd_ExchMsgType_Bye_From_Pph__For_OUT_Primary_Call(buf);
           break;
      case ExchMsgType_Presence:
           PROCESS_NOTIFY_PRESENCE(ofs->elt,buf);
           break;
      case ExchMsgType_Call_OnHold:{
           TMediaSession* ms = Sip->sss->GetMsOut_by_Callid(buf->callid);
           if(ms)
              PlaceCall_OnHold(ms);
           break;
           }
      case ExchMsgType_Call_Resume:{
           TMediaSession* ms = Sip->sss->GetMsOut_by_Callid(buf->callid);
           if(ms)
              ResumeCall(ms);
           break;
           }
      case ExchMsgType_FileTransfer_Notification:{
           TContact ContactCopy;
           if(Sip->Contacts.get_contact_copy_by_user_name(ContactCopy, buf->msg_1))
             {
             vector<string> v;
             string utf8_s = ANSI_2_UTF8(buf->msg);
             v.push_back(utf8_s);
             IM_Send(&ContactCopy,v);
             }
           break;
           }
      case ExchMsgType_FileTransfer_InProgress:
           Im.set_state_of_file_transfer_PROGRESS(buf->tag);                                 //Update Display View:  buf->tag - display index (IM_DrawGrid)
         ::PostMessage(MainFormSLS->Handle, CONTROL_MSG, WM_APP_MSG_WPARAM__IM_REPAINT, 0);  //Refresh IM_DrawGrid
           break;
      case ExchMsgType_FileTransfer_FileReceived:
           Im.set_state_of_file_transfer_RECEIVED(buf->tag, buf->tag_1, buf->msg);                    //Update Display View:  buf->tag - display index (IM_DrawGrid), buf->tag_1 - file length
         ::PostMessage(MainFormSLS->Handle, CONTROL_MSG, WM_APP_MSG_WPARAM__IM_REPAINT, 0);  //Refresh IM_DrawGrid
           break;
      } //switch(buf->emt){
delete buf;
}//try
catch(Exception& e){exsSstEXCEPTION(ofs->elt,"__Proc_UAC_Msg_READLIST()",e);}
}
//----------------------------------------------------------------------------
//------------------------ Hide DialPad Window -------------------------------
//----------------------------------------------------------------------------
void __fastcall TMainFormSLS::HIDE_DPW(int tag)
{
if(DialPad->Visible)
  if(DialPad->Tag == tag)
     DialPad->Hide_DPW();
}
//----------------------------------------------------------------------------
bool __fastcall TMainFormSLS::IsFileTransfer_INVITE(TSipParsBuf* spb)
{
bool rv=false;
TTransferFileAttrib tfa;
if(exsCheck_OnReceive_FileTransfer(spb->sdp.Sdp,&tfa))
  {
  rv=true;
  TCall_Panel* panel = new TCall_Panel(this);
  if(panel)
    {
    panel->set_call_type(Call_Type_FileTransfer);
    panel->set_leg_type(Lt_In);
    panel->Parent  = this;
    panel->TFP.tfa = tfa;
  //  panel->Top     = MainFormSLS->Panel1->Top + MainFormSLS->Panel1->Height;
    panel->Left    = RIGHT_PANEL->Left;
    panel->Width   = MainFormSLS->Panel1->Width;
    panel->Height  = MainFormSLS->Panel1->Height;///2;
    panel->Color   = (TColor)0x00EEEEEE; //0x00D27842;//0x00FFF2EA; //MainFormSLS->PanelColor;
    panel->BevelInner = bvLowered;
    panel->BevelOuter = bvRaised;
    panel->Tag = Sip->gen_call_tag();
    if(getIntrfStyle() == 0)
       Panel2->Top = panel->Top + panel->Height;
    getBottomCallPanelMargin();
    Sip->Receive_File__Labels(panel,spb,&tfa);
    Sip->Receive_File__Btns(panel);
    Sip->Receive_File__Progress_Bar(panel,tfa.file_size);
    cps.add_panel_tag(panel->Tag,CL_DrawGrid);
  ::PostMessage(Handle, CONTROL_MSG, WM_APP_MSG_WPARAM__IM__DRAWGRID_RESIZE_ON_CHANGE_CALL_COUNT, WM_APP_MSG_LPARAM__NOPARAM);
    }
  }
return rv;
}
//------------------------------------------------------------------------------

void __fastcall TMainFormSLS::Play_Sound(playSoundState pst)
{
if(Sip->pst)
  if(Sip->pst->getPss() == playSoundState_Free)
    {
    Sip->pst->setPss(pst);
    if(Sip->pst->Suspended)
       Sip->pst->Resume_Thread();
    }
}
//-----------------------------------------------------------------------------
bool __fastcall TMainFormSLS::get_at_least_one_conv_panel()
{
for(int i = 0; i < ControlCount; i++)
   {
   TCall_Panel* Panel = dynamic_cast<TCall_Panel*>(Controls[i]);
   if(Panel)
      return true;
   }
return false;
}
//-----------------------------------------------------------------------------
void __fastcall TMainFormSLS::Proc_UAS_Msg_READLIST(TExchBuf* buf)
{
switch(buf->emt){
      case ExchMsgType_INVITE:{
           TForm1* form = NULL;
           if(buf->isAddBuf())
             {
             TSipParsBuf* spb = (TSipParsBuf*)buf->getAddBuf_Reset();
             if(spb->parallel_phone) //Incoming call received from parallel_phone
               {
               if(!spb->ReqStatusLine.empty())
                 {
                 int st = spb->ReqStatusLine.find("sip:");
                 if(st != -1)
                   {
                   int en = spb->ReqStatusLine.find("@",st);
                   if(en != -1)
                     {
                     st += 4;
                     if(st < en)
                       {
                       string s = spb->ReqStatusLine.substr(st, en - st);
                       user_name_to_send = s;
                       ComboBox1->Text   = s.c_str();
                       CalledNameLbl->Caption = s.c_str();
                       string pph_callid = spb->call_id.getcallid();
                       AudioCall_PPH(pph_callid); //call initiated by pph
                       }
                     }
                   }
                 }
               spb->decReferenceCount();
               break;
               }
             form = ICB.new_incoming_call(spb->call_id.getcallid());
             if(form)
               if(!Sip->TestBlock.auto_answer)
                 {
                 string calling_name;
                 TContact Contact(-1);
                 if(MainFormSLS->Sip->Contacts.get_contact_copy_by_user_name(Contact,spb->callingParty))
                   {
                   if(Contact.full_name.empty())
                     calling_name = spb->callingParty;
                   else
                     calling_name = Contact.full_name;
                   }
                 else //Not found TContact with appropriate spb->callingParty
                   {
                   calling_name = spb->callingParty;
                   unsigned st = spb->From.find("<");
                   if(st != -1)
                     {
                     unsigned en = spb->From.find("\"");
                     if(en != -1)
                       {
                       if(en < st)
                         {
                         en++;
                         if(en < spb->From.length())
                           {
                           int en_1 = spb->From.find("\"",en);
                           if(en_1 != -1)
                             {
                             string s = spb->From.substr(en,en_1 - en);
                             if(!s.empty())
                               {
                               calling_name = UTF8_2_ANSI(s.c_str());
                               spb->clngDisplayName = calling_name;
                               }
                             }
                           }
                         }
                       }
                     }
                   }
                 AnsiString caption;
                 switch(lng){
                        case Lang_RU:
                             caption = ("Вызывает" + WS + /*"\"" + */ calling_name /*+ "\""*/).c_str();
                             break;
                        default:
                             caption = ("\"" + calling_name + "\"" + WS +  "Calling").c_str();
                             break;
                       }
                 form->callingName = spb->callingParty;
                 if(!spb->clngDisplayName.empty())
                    form->displayName = spb->clngDisplayName;
                 #ifdef SIP_Video
                 if(!spb->sdp.video.codecs.empty())
                     form->VideoCall();
                 else
                 #endif
                   {
                   if(!spb->sdp.audio.codecs.empty())
                      form->AudioCall();
                   else
                      {
                      if(IsFileTransfer_INVITE(spb))
                        {
                        Play_Sound(playSoundState_FileReceiveNotify);
                        break;
                        }
                      }
                   }
                 int width = form->Label1->Canvas->TextWidth(caption);
                 if(width < form->Width)
                   {
                   if(width > form->Width/2)
                      form->Label1->Left = form->Width/2  - (width/2);
                   }
                 else
                   form->Label1->Left = 2;
                 form->Label1->Caption = caption;
                 }
             if(Sip->TestBlock.auto_answer)
               Sip->send_Create_Session_Req(spb);
             else
               {
               Sip->send_180_Resp(spb);
               PPS->Check_IN_Call_To_ParallelPhone(spb,form);
               }
             spb->decReferenceCount();
             } //if(buf->isAddBuf())

           if(Sip->TestBlock.auto_answer)
              break;

           if(!get_at_least_one_conv_panel())
             Play_Sound(playSoundState_PlayRing);  //Play sound only if no active conversations

           if(form)
             {
             form->FormStyle = fsStayOnTop;
             form->Show();
             }
           break;
           }
      case ExchMsgType_RCVD_REINVITE_WITH_ADD_VIDEO:
           Sip->activate_Remote_Video_OnReInvite_Recv_With_Add_Video(buf, SipUAThreadType_UAS);
           break;
      case ExchMsgType_RCVD_INVITE_ON_CALL_TRANSFER:
           Rcvd_INVITE_ON_CALL_TRANSFER(buf->tag, buf->msg, buf->msg_1); //buf->msg == spb->calingParty, buf->msg_1 == Referred-By
           break;
      case ExchMsgType_200OK_ON_INVITEREQ:{
           if(buf->isAddBuf())
             {
             TRemoteMedia* rm = (TRemoteMedia*)buf->getAddBuf_Reset();
             if(rm)
               {
               TMediaSession* ms = Sip->sss->GetMsIn_by_Callid(rm->callid);
               if(ms)
                 {
                 ms->setRespState(SPS_INVITE200OK_RCVD);
                 TUdpChannel* uc = ms->getSoundChannel();
                 if(uc)
                   {
                   if(!ms->get_200_OK_RCVD())
                     {
                     if(uc->wopt)
                        uc->wopt->startReceivingVoice(rm);
                     if(uc->mic)
                        uc->mic->startSendingVoice();
                     ms->set_200_OK_RCVD(true);
                     }
                   }
                 Answer_On_Outgoing_CallPanel(ms);
                 }
               delete rm;
               }
             }
           break;
           }
      case ExchMsgType_DeleteMediaSession:
           Sip->sss->EraseMediaSession(buf->callid);   //Уже с префиксом in_
           break;
      case ExchMsgType_INVITE_IN_ScreenSharing:
           InitScreenSharing_Viewer(buf);
           break;
      case ExchMsgType_INVITE_AUTO_ANS:{
           TSipParsBuf* spb = (TSipParsBuf*)buf->getAddBuf_Reset();
           if(spb)
             {
             TExchBuf* buf = new TExchBuf(WM_APP_MSG_WPARAM__CALL_IN);
             if(buf)
               {
               buf->emt    = ExchMsgType_Answer;
               buf->callid = spb->call_id.getcallid();
               buf->msg    = spb->callingParty;
               #ifdef SIP_Video
               TVcamPar* vcpar = new TVcamPar;
               if(vcpar)
                 {
                 vcpar->width  = Form4->vcam_width;
                 vcpar->height = Form4->vcam_height;
                 vcpar->fps    = 15;
                 buf->setAddBuf(vcpar);
                 }
               #endif
               callin_exchlst_insert(buf);
               ::PostMessage(Handle, CALL_MSG, WM_APP_MSG_WPARAM__CALL_IN, WM_APP_MSG_LPARAM__READLIST);
               }
             }
           break;
           }
      case ExchMsgType_CANCEL:{
           TMediaSession* ms = Sip->sss->GetMsIn_by_Callid(buf->msg);    //buf->msg == callid
           if(ms)
             {
             TCall_Panel* call_panel = get_Call_Panel_By_Tag(ms->getCallTag());
             if(call_panel)  //Если ошибочно пришел CANCEL в отвеченный канал (вместо BYE)
               {
               if(call_panel->get_call_state() == Call_State__Conference)
                  call_panel->conference_exit(ms);
               if(!ms->get_ms_hstry_written())
                 {
                 ms->set_ms_hstry_written(true);
                 call_panel->tstmps.get_conv_duration();
                 call_panel->incoming_call_disc_out_hstry(ms->get_uniq_username(), ms->get_display_username());
                 }
               }
             else
               {
               if(!ms->get_ms_hstry_written())
                 {
                 ms->set_ms_hstry_written(true);
                 TExchBuf* BUF = new TExchBuf(WM_APP_MSG_WPARAM__CALL_IN);
                 if(BUF)
                   {
                   BUF->emt   = ExchMsgType_Cancel_In;
                   BUF->msg   = ms->get_uniq_username();
                   BUF->msg_5 = ms->get_display_username();
                   callin_exchlst_insert(BUF);
                 ::PostMessage(Handle, CALL_MSG, WM_APP_MSG_WPARAM__CALL_IN, WM_APP_MSG_LPARAM__READLIST);
                   }
                 }
               ICB.req_to_del_in_call_window_on_receiving_CANCEL(buf->msg); //buf->msg == callid
               }
             } //if(ms)
           break;
           }
      case ExchMsgType_SUBSCRIBE_RCVD:{
           TContact contact(-1);
           if(Sip->Contacts.get_contact_copy_by_user_name(contact,buf))
             {
             if(buf->tag == 0) //Expires == 0
                Sip->Contacts.SS.del_subscribed_contact(contact.name);
             else
                {
                bool subscribed_to_me = Sip->Contacts.SS.subscribed_to_me(contact.name, buf->callid);
             //   if(!subscribed_to_me) //not found contact.name or TSubscrPar.callid != callid
             //      Sip->Contacts.SS.del_subscribed_contact(contact.name);
                if(contact.get_my_net_status_visible()) //if(MY NETWORK STATUS visible to CONTACT)
                  {
                  buf->msg_3 = NS.get_my_net_state_comment();
                  if(buf->msg_2.find("tag=") != -1)
                     Sip->send_Uas_NOTIFY_ON_SUBSCRIBE_Rcvd(buf, true);     //In dialog ( NOTIFY must be send without SDP)
                  else
                     Sip->send_Uas_NOTIFY_ON_SUBSCRIBE_Rcvd(buf, false);
                  Sip->Contacts.SS.add_subscribed_contact(contact.name,buf);
                  }
                if(contact.get_contact_net_status_visible()) //if(CONTACT NETWORK STATUS visible to ME)
                  {
                  if(!Sip->Contacts.AS.subscribed(contact.name)) //I not yet subscribed to this Contact
                      Sip->init_SUBSCRIBE_Proc(contact, SUBSCRIPTIONS_EXPIRES_CONST);
                  else{
                      if(!subscribed_to_me)
                        {
                     //  Sip->init_SUBSCRIBE_Proc(contact, SUBSCRIPTIONS_EXPIRES_CONST);
                        TReadyOfRefreshSubsc rrs;
                        rrs.name = contact.name;
                        Sip->Contacts.AS.refresh_subscribe_proc(rrs);
                        }
                      }
                  }
                }
             }
           #ifdef Enterprise_Edition
           else   //В Enterprise_Edition абонент должен отвечать на все запросы SUBSCRIBE независимо от наличия запрашивающего абонента в списке контактов. Запрашивающий абонент посылает SUBSCRIBE только тем, у кого равный или менее приоритетный COS (0 приоритетнее 1-го и т.д.)
             {
             if(buf->tag == 0) //Expires == 0
               Sip->Contacts.SS.del_subscribed_contact(buf->msg);
             else
               {
               bool subscribed_to_me = Sip->Contacts.SS.subscribed_to_me(buf->msg, buf->callid);
               if(!subscribed_to_me) //not found contact.name or TSubscrPar.callid != callid
                   Sip->Contacts.SS.del_subscribed_contact(buf->msg);
               if(contact.get_my_net_status_visible()) //if(MY NETWORK STATUS visible to CONTACT)
                  {
                  buf->msg_3 = NS.get_my_net_state_comment();
                  if(buf->msg_2.find("tag=") != -1)
                     Sip->send_Uas_NOTIFY_ON_SUBSCRIBE_Rcvd(buf, true);     //In dialog ( NOTIFY must be send without SDP)
                  else
                     Sip->send_Uas_NOTIFY_ON_SUBSCRIBE_Rcvd(buf, false);
                  Sip->Contacts.SS.add_subscribed_contact(buf->msg,buf);
                  }
                }
             }
           #endif
           break;
           }
      case ExchMsgType_NEWTWORK_NOTIFY_PARAMETERS:
           Sip->Contacts.SS.add_subscription_parameters(buf);
           break;
      case ExchMsgType_MESSAGE:{
           string s = buf->msg_2;
           string msg_rcvd_from;
           if(!s.empty())
             {
             int st = s.find("?xml version");
             if(st == -1)
               {
               string from;
               TContact contact(-1);
               if(MainFormSLS->Sip->Contacts.get_contact_copy_by_user_name(contact,buf->msg))
                 {
                 from += contact.full_name;
                 msg_rcvd_from = contact.full_name;
                 }
               else
                 {
                 if(!buf->msg_1.empty())
                   {
                   from += buf->msg;    // CallingParty (Sip header From:)
                   msg_rcvd_from = buf->msg;
                   }
                 else
                   {
                   from += buf->msg_1;  //DisplayName (Sip header From:)
                   msg_rcvd_from = buf->msg_1;
                   }
                 }
               if((Im.LMS.get_last_msg_sender() != buf->msg) || (Im.LMS.imtt != IM_TEXT_TYPE_REM_ADDR))
                 {
                 Im.update(from, buf, IM_TEXT_TYPE_REM_ADDR);
                 Im.LMS.set_last_msg_sender(buf->msg, IM_TEXT_TYPE_REM_ADDR);
                 }

               if(!buf->SV) //string not yet dissected in the UAS_Thread
                 {
                 if(buf->msg_3.find("text/html") != -1)
                   Im.dissect_html_text_msg(s,buf);
                 else
                   Im.dissect_plain_text_msg(s,buf);
                 }

               string hint_str = "Сообщение от :\n" + msg_rcvd_from;
               if(Im.get_selected_remote_user() != buf->msg)
                 {
                 if(buf->SV)
                   {
                   if(buf->SV->get_msg_type() == 1)    //Got invitation on file receiving
                     Im.update_IM(buf->SV->v, buf, IM_INVITE_ON_FILE_RECEIVING);
                   else
                     Im.update_IM(buf->SV->v, buf, IM_TEXT_TYPE_REMOTE_IM);
                   }
                 Sip->Contacts.missed_call(buf->msg);
                 DrawGrid1->Repaint();
                 if(Im.MCS.save_im_sender_name(buf->msg))
                    Play_Sound(playSoundState_FileReceiveNotify);
                 DrawMessageMarker();
                 TrayMessage_Ext(NIM_MODIFY,hint_str,1);
                 }
               else
                 {
                 if( MainFormSLS->app_on_tray_only || MainFormSLS->app_minimized ) //Applicattion on tray
                   {
                   if(buf->SV)
                     {
                     if(buf->SV->get_msg_type() == 1)    //Got invitation on file receiving
                        Im.update_IM(buf->SV->v, buf, IM_INVITE_ON_FILE_RECEIVING);
                     else
                        Im.update_IM(buf->SV->v, buf, IM_TEXT_TYPE_REMOTE_IM);
                     }
                   Sip->Contacts.missed_call(buf->msg);
                   if(Im.MCS.save_im_sender_name(buf->msg))
                       Play_Sound(playSoundState_FileReceiveNotify);
                   DrawMessageMarker();
                   Im.clear_selected_remote_user();
                   TrayMessage_Ext(NIM_MODIFY,hint_str,1);
                   }
                 else
                   {
                   if((IM_DrawGrid->TopRow + IM_DrawGrid->VisibleRowCount) <= (IM_DrawGrid->RowCount - 1))
                     {
                     if(buf->SV)
                       {
                       string s = Im.get_selected_remote_user(); //Если последняя строка не видима (абонент просматривает предыдущие записи), то не должно быть и прокрутки (появляется только маркер о пришедшем сообщении)
                       Im.clear_selected_remote_user();
                       if(buf->SV->get_msg_type() == 1)    //Got invitation on file receiving
                         Im.update_IM(buf->SV->v, buf, IM_INVITE_ON_FILE_RECEIVING);
                       else
                         Im.update_IM(buf->SV->v, buf, IM_TEXT_TYPE_REMOTE_IM);
                       Im.set_selected_remote_user(s);
                       }
                     Sip->Contacts.missed_call(buf->msg);
                     DrawGrid1->Repaint();
                     if(Im.MCS.save_im_sender_name(buf->msg))
                        Play_Sound(playSoundState_FileReceiveNotify);
                     DrawMessageMarker();
                     TrayMessage_Ext(NIM_MODIFY,hint_str,1);
                     }
                   else
                     {
                     if(GetForegroundWindow() != Handle)
                       {
                       if(Im.MCS.save_im_sender_name(buf->msg))
                          Play_Sound(playSoundState_FileReceiveNotify);
                       DrawMessageMarker();
                       TrayMessage_Ext(NIM_MODIFY,hint_str,1);
                       }
                     if(buf->SV)
                       {
                       if(buf->SV->get_msg_type() == 1)    //Got invitation on file receiving
                         Im.update_IM(buf->SV->v, buf, IM_INVITE_ON_FILE_RECEIVING);
                       else
                         Im.update_IM(buf->SV->v, buf, IM_TEXT_TYPE_REMOTE_IM);
                       }
                     }
                   } //else
                 } //else
               } // int st = s.find("?xml version"); if(st == -1)
             }
           break;
           }
      case ExchMsgType_Bye:
           Rcvd_ExchMsgType_Bye_IN(buf);
           break;
      case ExchMsgType_Bye_From_Pph:            //BYE Rcvd from parallel_phone
           Rcvd_ExchMsgType_Bye_From_Pph__For_IN_Primary_Call(buf);
           break;
      case ExchMsgType_Call_OnHold:{
           TMediaSession* ms = Sip->sss->GetMsIn_by_Callid(buf->callid);
           if(ms)
              PlaceCall_OnHold(ms);
           break;
           }
      case ExchMsgType_Call_Resume:{
           TMediaSession* ms = Sip->sss->GetMsIn_by_Callid(buf->callid);
           if(ms)
              ResumeCall(ms);
           break;
           }
      case ExchMsgType_REGISTER:
           ProcInRegister(buf); //from parallel phone
           break;
      } // switch(buf->emt){
delete buf;
}
//----------------------------------------------------------------------------
void __fastcall TMainFormSLS::InitScreenSharing_Viewer(TExchBuf* buf)
{
if(!buf->msg.empty())
  {
  rdp_init();    //!!!          //ScreenSharing
  string s = buf->msg;
  #ifdef SCREEN_Sharing_over_rem_server
   SSV.ssv_delete_screen_sharing_structs();
   SSV.sss_rem = new TScreenSharingStruct(SSCT_IN_REMOTE);
   if(SSV.sss_rem)
     {
     Sip->sendUas_Answer_OnSharingInvite(buf);
     SSV.sss_rem->screen_sharing_viewer_call_id = buf->callid;
     SSV.sss_rem->WaitResponce = true;
     SSV.sss_rem->ss_CS_T      = new TScreenSharing__CLIENT_SEND__Thread(true, SSV.sss_rem, &MainFormSLS->ofs->elt, MainFormSLS->Sip );
     SSV.sss_rem->ss_CS_T->Resume();
     SSV.sss_rem->ss_CR_T      = new TScreenSharing__CLIENT_RECV__Thread(true, MainFormSLS->Sip->ScreenSharing.IPAddr, MainFormSLS->Sip->ScreenSharing.Port, SSV.sss_rem, NULL, &MainFormSLS->ofs->elt, MainFormSLS->Sip);
     SSV.sss_rem->ss_CR_T->get_sharing_string(s);
     SSV.sss_rem->ss_CR_T->get_server_session_str(s);
     SSV.sss_rem->ss_CR_T->Resume();
     }
  #else
  int sz = s.length();
  const char* buf = s.c_str();
  rdp_connect(buf, sz);    //ScreenSharing
  //rdp_destroy();         //ScreenSharing
  #endif
  }
}
//----------------------------------------------------------------------------
void __fastcall TMainFormSLS::Proc_UAS_Msg(TMessage& Message)
{
if(Sip)
  {
  string s;
  bool LOG = false;
  if(ofs)
    if(ofs->elt)
      if(ofs->elt->getlog())
         LOG = true;

  switch(Message.LParam){
       case WM_APP_MSG_LPARAM__READLIST:
            if(Sip->uas)
              {
              bool      rcvd = false;
              TExchBuf* buf  = Sip->uas->getExchLst();
              while(buf)
                   {
                   rcvd = true;
                   Proc_UAS_Msg_READLIST(buf);   //delete buf - inside this func
                   buf  = Sip->uas->getExchLst();
                   }
              if(!rcvd)
                if(LOG)
                   s += "\nERROR: TExchBuf* NOT FOUND!";  //Скорее всего по ошибке засунули в другой thread (Sip->uas, PPS->uac_pph ... and so on)
              }
            break;
       case WM_APP_MSG_LPARAM__READLIST_PPH:
            if(PPS)
              if(PPS->uas_pph)
                {
                bool      rcvd = false;
                TExchBuf* buf  = PPS->uas_pph->getExchLst();
                while(buf)
                     {
                     rcvd = true;
                     Proc_UAS_Msg_READLIST(buf);   //delete buf - inside this func
                     buf  = PPS->uas_pph->getExchLst();
                     }
                if(!rcvd)
                  if(LOG)
                    s += "\nERROR: TExchBuf* NOT FOUND!";  //Скорее всего по ошибке засунули в другой thread (Sip->uas, PPS->uac_pph ... and so on)
                }
            break;
       }

  if(LOG)
    if(!s.empty())
      {
      s += "\n";
      ofs->elt->FputEvt(s,1);
      }
  }
}
//-----------------------------------------------------------------------------
void __fastcall TMainFormSLS::PlaySound_Free()
{
try{
if(Sip->pst)
   Sip->pst->setPss(playSoundState_Free);
UINT fuSound = SND_ASYNC;
sndPlaySound(NULL,fuSound);
}//try
catch(Exception& e){exsSstEXCEPTION(ofs->elt,"__PlaySound_Free()",e);}
}
//-----------------------------------------------------------------------------
void __fastcall TMainFormSLS::Proc_UAC_Msg(TMessage& Message)
{
try{
string s;
bool LOG = false;
if(ofs)
  if(ofs->elt)
    if(ofs->elt->getlog())
       LOG = true;
switch(Message.LParam){
       case WM_APP_MSG_LPARAM__READLIST:
            if(Sip)    //имеет значение при выключении приложения
              if(Sip->sss) //имеет значение при выключении приложения (sss удаляется до удаления Sip->uac и Sip->uas)
                 if(Sip->uac)
                   {
                   if(LOG)
                      s = "\n\nTMainFormSLS::Proc_UAC_Msg()::WM_APP_MSG_LPARAM__READLIST";
                   bool      rcvd = false;
                   TExchBuf* buf  = Sip->uac->getExchLst();
                   while(buf)
                        {
                        rcvd = true;
                        Proc_UAC_Msg_READLIST(buf, s);
                        buf  = Sip->uac->getExchLst();
                        }
                   if(!rcvd)
                     if(LOG)
                       s += "\nERROR: TExchBuf* NOT FOUND!";  //Скорее всего по ошибке засунули в другой thread (Sip->uas, PPS->uac_pph ... and so on)
                   }
            break;
       case WM_APP_MSG_LPARAM__READLIST_PPH:
            if(LOG)
               s = "\n\nTMainFormSLS::Proc_UAC_Msg()::WM_APP_MSG_LPARAM__READLIST_PPH";
            if(Sip)     //имеет значение при выключении приложения
              if(Sip->sss) //имеет значение при выключении приложения (sss удаляется до удаления Sip->uac и Sip->uas)
                if(PPS)
                  if(PPS->uac_pph)
                    {
                    bool      rcvd = false;
                    TExchBuf* buf  = PPS->uac_pph->getExchLst();
                    while(buf)
                         {
                         rcvd = true;
                         Proc_UAC_Msg_READLIST(buf, s);
                         buf  = PPS->uac_pph->getExchLst();
                         }
                    if(!rcvd)
                      if(LOG)
                        s += "\nERROR: TExchBuf* NOT FOUND!";  //Comment see above
                    }
            break;
       case WM_APP_MSG_LPARAM__REGISTER_FAILED:
            if(Sip)
               Sip->setRegistered(false);
            if(lng == Lang_RU)
              Caption = baseCaption + (WS + WS + WS).c_str() + "Абонент не зарегистрирован";
            else
              Caption = baseCaption + (WS + WS + WS).c_str() + "Registration Failed";
            cbs = CallBtnState_NotActive;
            SetVoiceCallBtnState(BtnState_INACTIVE);
           // ImageList_CallBtn->Draw(Image3->Canvas,0,0,3,true);
           // Image3->Refresh();
            NS.set_my_network_state(ClientState_Off_Line);
            break;
       case WM_APP_MSG_LPARAM__FINAL_REG_END:
            if(Sip)
               Sip->setRegistered(false);
            break;
       case WM_APP_MSG_LPARAM__CONTACT_LIST_REFRESH:
            DrawGrid1->Repaint();
            break;
       case WM_APP_MSG_LPARAM__END_OF_PLAY_REORDER:
            end_of_playing_reorder();
            break;
       case WM_APP_MSG_LPARAM__END_OF_PLAY_BUSY:
            end_of_playing_busy();
            break;
      } //End of switch(Message.LParam){
if(LOG)
  if(!s.empty())
    {
    s += "\n";
    ofs->elt->FputEvt(s,1);
    }
}//try
catch(Exception& e){exsSstEXCEPTION(ofs->elt,"__Proc_UAC_Msg()",e);}
}
//----------------------------------------------------------------------------
void __fastcall TMainFormSLS::Proc_CALL_IN_Msg_READLIST(TMessage& Message)
{
try{
TExchBuf* buf = get_call_ExchLst(Message);
if(buf)
  {
  switch(buf->emt){
         case ExchMsgType_Answer:    //Amswer or Answer with video  or answer from parallel_phone
              PlaySound_Free();
              ReflectCallingPartyHstry(buf);   //Set personal contact list to calling number position, show calling history og calling party ...
              Sip->sendUas_Answer_OnInvite(buf);
              if(app_on_tray_only)
                 RestoreAppFromTray();
              else if(app_minimized)
                 RestoreAppFromTray();
              break;
         case ExchMsgType_Decline:{
              if(ICB.get_incoming_waiting_ans_calls() < 2)
                 PlaySound_Free();
              Sip->sendUas_Decline_OnInvite(buf);
              string s;
              Im.update(s, buf, IM_CALL_IN_DECLINED);
              break;
              }
         case ExchMsgType_Cancel_In:{
              string s;
              Im.update(s, buf, IM_CALL_IN_MISSED);
              break;
              }
         case ExchMsgType_Bye_In:{
              string s;
              Im.update(s, buf, IM_CALL_IN_ANSWERED);
              break;
              }
        }
  delete buf;
  }
}//try
catch(Exception& e){exsSstEXCEPTION(ofs->elt,"__Proc_CALLIN_Msg_READLIST()",e);}
}
//-----------------------------------------------------------------------------
void __fastcall TMainFormSLS::Proc_CALL_OUT_Msg_READLIST(TMessage& Message)
{
try{
TExchBuf* buf = get_call_ExchLst(Message);
if(buf){
  switch(buf->emt){
        case ExchMsgType_Cancel_Out:{
             string s;
             Im.update(s, buf, IM_CALL_OUT_NO_ANSWER);
             break;
             }
        case ExchMsgType_Busy_Out:{
             string s;
             Im.update(s, buf, IM_CALL_OUT_BUSY);
       //      display_msg();
             break;
             }
        case ExchMsgType_NotAcceptable:{
             string s;
             Im.update(s, buf, IM_CALL_OUT_NOT_ACCEPTABLE);
       //      display_msg();
             break;
             }
        case ExchMsgType_Bye_Out:{
             string s;
             Im.update(s, buf, IM_CALL_OUT_ANSWERED);
         //    display_msg();
             break;
             }
        }
  delete buf;
  }
}//try
catch(Exception& e){exsSstEXCEPTION(ofs->elt,"__Proc_CALL_OUT_Msg_READLIST()",e);}
}
//-----------------------------------------------------------------------------
void __fastcall TMainFormSLS::Proc_FILE_TRANS_INIT_Msg(TMessage& Message)
{
TExchBuf* buf = get_filetrans_ExchLst();
if(buf)
  {
  TCall_Panel* panel = get_Call_Panel_By_Tag(Sip->get_started_transferfile_panel_tag());
  if(panel)
    {
    TTransmitFileThread* ttf = panel->t_trn_f;
    if(ttf)
      {
      ttf->set_sid(buf->tag);
      panel->TFP.tfa.sid = buf->tag;
      Sip->sendInitInvite_OnFileTransfer(panel);
      Sip->transmit_file_init();
      }
    }
  delete buf;
  }
}
//-----------------------------------------------------------------------------
void __fastcall TMainFormSLS::Proc_FILE_TRANS_START_Msg(TMessage& Message)
{
TExchBuf* buf = get_filetrans_ExchLst();
if(buf)
  {
  TCall_Panel* panel = get_Call_Panel_By_Sid(buf->tag);
  if(panel)
     if(panel->lb_2)
        panel->lb_2->Caption = "";
  delete buf;
  }
}
//-----------------------------------------------------------------------------
void __fastcall TMainFormSLS::Proc_FILETRANS_Msg(TMessage& Message)
{
TExchBuf* buf = get_filetrans_ExchLst();
if(buf)
  {
  TCall_Panel* panel = get_Call_Panel_By_Sid(buf->tag);
  if(panel)
    {
    panel->set_file_transfer_complete();
    TMediaSession* ms = Sip->sss->GetMs_by_Call_Tag(panel->Tag);
    if(ms)
      {
      string callid = ms->getCallID();
      if(ofs->elt)
         ofs->elt->FputEvt("\nDISCONNECT callid " + callid);
      Sip->send_call_disc_out(callid,false);
      Sip->sss->EraseMediaSession(out_pref + callid); //ms deleted !!!
      }
    push_req_to_del_call_panel(panel->Tag);
    }
  delete buf;
  }
}
//-----------------------------------------------------------------------------
void __fastcall TMainFormSLS::Proc_FILE_PENDING_Msg(TMessage& Message)
{
TExchBuf* buf = get_filetrans_ExchLst();
if(buf)
  {
  TCall_Panel* panel = get_Call_Panel_By_Sid(buf->tag);
  if(panel)
    if(panel->progbar)
        panel->progbar->Position = buf->tag_1;
  delete buf;
  }
}
//-----------------------------------------------------------------------------
void __fastcall TMainFormSLS::Proc_FILE_RECV_Msg(TMessage& Message)
{
TExchBuf* buf = get_filetrans_ExchLst();
if(buf)
  {
   TCall_Panel* panel = get_Call_Panel_By_Sid(buf->tag);
   if(panel)
     {
     panel->set_file_transfer_complete();
     panel->btn_0->OnMouseUp = panel->Btn_Quit__MouseUp;
     panel->btn_1->OnMouseUp = panel->Btn_OpenFile__MouseUp;
     if(lng == Lang_RU)
        {
        panel->btn_0->Caption = "Выход";
        panel->btn_1->Caption = "Открыть";
        }
     else
        {
        panel->btn_0->Caption = "Quit";
        panel->btn_1->Caption = "Open";
        }
     }
  delete buf;
  }
}
//-----------------------------------------------------------------------------
void __fastcall TMainFormSLS::Proc_CALL_IN_Msg(TMessage& Message)
{
try{
switch(Message.LParam){
           case WM_APP_MSG_LPARAM__READLIST:
           Proc_CALL_IN_Msg_READLIST(Message);
           break;
      }
}//try
catch(Exception& e){exsSstEXCEPTION(ofs->elt,"__Proc_CALL_IN_Msg(TMessage &Message)",e);}
}
//-----------------------------------------------------------------------------
void __fastcall TMainFormSLS::Proc_CALL_OUT_Msg(TMessage& Message)
{
try{
switch(Message.LParam){
           case WM_APP_MSG_LPARAM__READLIST:
           Proc_CALL_OUT_Msg_READLIST(Message);
           break;
      }
}//try
catch(Exception& e){exsSstEXCEPTION(ofs->elt,"__Proc_CALL_OUT_Msg(TMessage &Message)",e);}
}
//-----------------------------------------------------------------------------
#ifdef SIP_Video
void __fastcall TMainFormSLS::Proc_VIDEOOUT_Msg(TMessage& Message)
{
switch(Message.LParam){
           case WM_APP_MSG_LPARAM__READLIST:
           Proc_VIDEOOUT_Msg_READLIST();
           break;
      }
}
#endif
//-----------------------------------------------------------------------------
void __fastcall TMainFormSLS::Proc_CONF_SERV_Msg(TMessage& Message)
{
switch(Message.LParam){
           case WM_APP_MSG_LPARAM__NOPARAM:
                Close_Conf_Panel();
                break;
      }
}
//------------------------------------------------------------------------------
void __fastcall TMainFormSLS::FormCloseQuery(TObject *Sender, bool &CanClose)
{
_CLOSE_REQUEST = true;
if(!term_explicit)
   Log_Start_App_Termination_By_Alt_F4();
Close_All_Open_Window();
if(!Sip->getRegistered())
  {
  CanClose = true;
  return;
  }
Sip->Contacts.SS.set_block_rcv_subscription(true);
Sip->Contacts.SS.clear_time_list();
Sip->Contacts.AS.clear_time_list();
NS.Final_Notify_Proc();
Sip->Contacts.AS.Final_Subscribe_Proc();
Hide();
::Sleep(1000);
TAuthPar auth_par;
auth_par.user_name = Sip->Account.get_user_name();
auth_par.user_pwd  = Sip->Account.get_user_pwd();
auth_par.domain    = Sip->Account.get_domain();
if(!auth_par.user_name.empty())
   Sip->finalRegistrationProc(&auth_par);
::Sleep(2000);
#ifdef TRACE_ALLOC_MEM
#ifdef _DEBUG
 DUMP_UNFREED();
#endif //#ifdef _DEBUG
#endif //#ifdef TRACE_ALLOC_MEM


CanClose = true;
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::logThreadsState()
{
TEventLogThread* elt = ofs->elt;
if(!elt)return;
elt->FputEvt("\n");
TSipSendThread* SST = Sip->getTSipSendThread();
if(SST)
  {
  if(SST->Suspended)
     elt->FputEvt("\nSST->Suspended");
  else
     elt->FputEvt("\nSST->Execute");
  elt->FputEvt(" SST_in_sz " + inttostr(SST->getQueueSize()));
  }
else
 elt->FputEvt("\nSST = NULL");


if(Sip->uac)
  {
  if(Sip->uac->Suspended)
     elt->FputEvt("\nUAC->Suspended");
  else
     elt->FputEvt("\nUAC->Executed");
  elt->FputEvt(" UAC_in_sz " + inttostr(Sip->uac->getQueueSize()) + " UAC_resend_sz " + inttostr(Sip->uac->getRsndSize()) +
               " UAC_LegTrn_sz " + inttostr(Sip->uac->getLegTrnSize()));
  if(Sip->uac->srst)
    {
    if(Sip->uac->srst->Suspended)
       elt->FputEvt("\nUAC->SRST->Suspended");
    else
       elt->FputEvt("\nUAC->SRST->Executed");
    elt->FputEvt(" UAC->SRST_Resend_List_Sz " + inttostr(Sip->uac->srst->getRslSize()));
    }
  #ifdef SIP_PrintAll_Uac_CallID
  Sip->uac->printAllCallId();
  #endif
  }
else
 elt->FputEvt("\nUAC = NULL");


if(Sip->uas)
  {
  if(Sip->uas->Suspended)
     elt->FputEvt("\nUAS->Suspended");
  else
    elt->FputEvt("\nUAS->Executed");
  elt->FputEvt(" UAS_in_sz " + inttostr(Sip->uas->getQueueSize()) + " UAS_resend_sz " + inttostr(Sip->uas->getRsndSize()) +
               " UAS_LegTrn_sz " + inttostr(Sip->uas->getLegTrnSize()));
  if(Sip->uas->srst)
    {
    if(Sip->uas->srst->Suspended)
       elt->FputEvt("\nUAS->SRST->Suspended");
    else
       elt->FputEvt("\nUAS->SRST->Executed");
    elt->FputEvt(" UAC->SRST_Resend_List_Sz " + inttostr(Sip->uas->srst->getRslSize()));
    }
  #ifdef SIP_PrintAll_Uas_CallID
  Sip->uas->printAllCallId();
  #endif
  }
else
 elt->FputEvt("\nUAS = NULL");

if(Sip->spt)
  {
  if(Sip->spt->Suspended)
     elt->FputEvt("\nSPT->Suspended");
  else
     elt->FputEvt("\nSPT->Executed");
  elt->FputEvt(" SPT_in_sz " + inttostr(Sip->spt->getQueueSize()));
  }
else
 elt->FputEvt("\nSPT = NULL");

if(Sip->ucs)
  {
  if(Sip->ucs->Suspended)
     elt->FputEvt("\nUCS->Suspended");
  else
     elt->FputEvt("\nUCS->Executed");
  elt->FputEvt(" UCS_q_req_to_del_sz "  + inttostr(Sip->ucs->reqToDelSize()));
  }
else
 elt->FputEvt("\nUCS = NULL");

TSipRecvThread* SRT = Sip->getTSipRecvThread();
if(SRT)
  {
  if(SRT->Suspended)
    elt->FputEvt("\nSRT->Suspended");
  else
    elt->FputEvt("\nSRT->Executed");
  elt->FputEvt(" SRT_in_sz " + inttostr(SRT->getQueueSize()));
  }
else
 elt->FputEvt("\nSRT = NULL");

int SipSentSize_1 = Sip->getSentSize_1();
string s = "\nSip->sent.size() " + inttostr(SipSentSize_1);
if(SipSentSize_1)
  Sip->printSentBlocks(s);
elt->FputEvt(s);

int NumOfBusiedCh = Sip->ucs->GetSize();
s = "\nNumber Of Busied Channels"+ WS + inttostr(NumOfBusiedCh);
vector<string> v;
Sip->ucs->getAllBusiedChannels(v);
int BusiedChList_Size = v.size();
if(BusiedChList_Size)
  for(int i=0;i < BusiedChList_Size;i++)
     s += "\n" + v[i];
elt->FputEvt(s);

elt->FputEvt("\n",1);
}
//-----------------------------------------------------------------------------
void __fastcall TMainFormSLS::FormKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
try{
    if(Key == 27) //Esc
      {
      if(ContactMenu->Visible)
         ContactMenu->Close();
      if(CC_Panel->Visible)
         CC_Panel->Hide();
      if(DialPad->Visible)
        DialPad->Hide_DPW();
      if(DPP->Visible)
         DPP->Hide();
      close_NSCP();
      if(Panel_Dial->Visible)
        {
        Panel_Dial->Hide();
        return;
        }
        
      }
    if(!Shift.Contains(ssCtrl))
      return;
    if(Key==118) //F7
      {
      logThreadsState();return;
      }
   }
catch(Exception& e){exsSstEXCEPTION(ofs->elt,"__TMainForm::MainForm_FormKeyUp",e);}
}
//---------------------------------------------------------------------------

void __fastcall TMainFormSLS::INIT_CTRL_SET()
{
bot_margin=0;
switch(lng){
      case Lang_EN:
           Client1->Caption       = "Client";
           Status1->Caption       = "Online Status";
           Online1->Caption       = "Online";
           DoNotDisturb1->Caption = "Do Not Disturb";
           Away1->Caption         = "Away";
           Offline1->Caption      = "Offline";
           Tools1->Caption        = "Tools";
           break;
      case Lang_RU:
           Client1->Caption       = "Клиент";
           Status1->Caption       = "Сетевой статус";
           Online1->Caption       = "В сети";
           DoNotDisturb1->Caption = "Не беспокоить";
           Away1->Caption         = "Нет на месте";
           Offline1->Caption      = "Не в сети";
           Tools1->Caption        = "Инструменты";
           break;
      }
istyle_1();
#ifndef SIP_Video
Image2->Visible = false;
#endif
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::istyle_1()
{
Top = initTop = Screen->Height/4;
Left = initLeft = Screen->Width/2;
Width = initWidth = Screen->Width/2 + Screen->Width/10;
Height = 2*Screen->Height/3;
if(Height >= 2*Screen->Height/3)
   Height = 3*Screen->Height/4 - Screen->Height/10;
prev_height        = Height;
prev_height_for_cl = Height;
prev_width         = Width;

//Brand_Image->Stretch = true;
//Brand_Image->Width   = 300;
Brand_Image->Height  = 100;

#ifdef NO_BRAND
Brand_Image->Picture = NULL;
#endif

Panel2->Left  = 0;
Panel2->Top   = Brand_Image->Top + Brand_Image->Height;
Panel2->Width = LEFT_PANEL->Width; //Width/2;
if(Panel2->Width > Screen->Width/4)
   Panel2->Width = Screen->Width/4;
Panel2->BevelInner = bvNone;
Panel2->BevelOuter = bvNone;

Panel1->Color  = (TColor)0xEEEEEE; //0xE0E0E0; //(TColor)0xF0F0F0; // clBtnFace;//(TColor); 0x00C0C0C0(clSilver) //clBtnFace; (TColor)0xFFFFFF;
Panel1->Left   = 0; //Panel2->Left + Panel2->Width;
Panel1->Top    = 0;
     Panel1->Height = 100;
Panel1->Width = Width - Panel1->Left - 8;
Panel1->BevelInner = bvNone; //bvLowered;
Panel1->BevelOuter = bvNone; //bvRaised;
//Image3->Top   =   Panel1->Height/2 - Image3->Height/2;

//ComboBox1->Ctl3D = false;
//ComboBox1->BorderStyle = bsSingle;
ComboBox1->Top     = 10;
ComboBox1->Left    = 10;
ComboBox1->Visible = false;

CalledNameLbl->Top  = 5; //10;
CalledNameLbl->Left = 15;
CalledNameLbl->Font->Name  = "Arial";
CalledNameLbl->Font->Size  = 12;
CalledNameLbl->Font->Color = (TColor)0xFF0000; //clBlue;
//CalledNameLbl->Font->Style = CalledNameLbl->Font->Style << fsBold;
CalledNameLbl->Caption     = "";
//CalledNameLbl->Visible = false;

InitAudioCallBtn();
InitVideoCallBtn();
InitRemoteVideoBtn();
Image_RemoteVideo->Visible = false;
Image_RemoteVideo->Tag     = 0;

Panel_DialPad->Color      = clWhite; //(TColor)0xE0E0E0;//(TColor)0xF0F0F0;
Panel_DialPad->Height     = 45;
Panel_DialPad->BevelInner = bvLowered;
Panel_DialPad->BevelOuter = bvRaised;
Panel_DialPad_Resize();

AddContact_Img->Left = 4;//8;//Image4->Left;
AddContact_Img->Top  = 4;//2; //Image4->Top;
RBitMap::change_color(0xE4AC22, turquoise_color, AddContact_Img);

DialNumber_Img->Left = AddContact_Img->Left; // + 4;
DialNumber_Img->Top  = 4; //6;//10;
RBitMap::change_color(0xC0C0C0, 0xFFFFFE, DialNumber_Img); //Change background color from gray to 0xFFFFFE (on one bit differenced from white)
RBitMap::change_color(0xE4AC22, turquoise_color, DialNumber_Img);

Label2->Color = clWhite; //(TColor)0xE0E0E0;; //(TColor)0xF0F0F0;
Label2->Font->Color = (TColor)turquoise_color;
Label2->Left  = DialNumber_Img->Left + DialNumber_Img->Width + 10;
Label2->Top   = DialNumber_Img->Top  + DialNumber_Img->Height/4;

Panel_AddContact->Color      = clWhite;//(TColor)0xE0E0E0;//(TColor)0xF0F0F0;
Panel_AddContact->Height     = 45;
Panel_AddContact->BevelInner = bvLowered;
Panel_AddContact->BevelOuter = bvRaised;
Panel_AddContact_Resize();

#ifdef IMG_N_Style
color_btns_correction();

AddContact_Img->Visible = true;
DialNumber_Img->Visible = true;

/*
AddContact_Img->Left = 8;//Image4->Left;
AddContact_Img->Top  = 2; //Image4->Top;
RBitMap::change_color(0xE4AC22, turquoise_color, AddContact_Img);

DialNumber_Img->Left = AddContact_Img->Left; // + 4;
DialNumber_Img->Top  = 6;//10;
RBitMap::change_color(0xC0C0C0, 0xFFFFFE, DialNumber_Img); //Change background color from gray to 0xFFFFFE (on one bit differenced from white)
RBitMap::change_color(0xE4AC22, turquoise_color, DialNumber_Img);
*/
#else
Image4->Visible = true;
Image5->Visible = true;
AddContact_Img->Visible = false;
DialNumber_Img->Visible = false;
#endif



Label1->Color      = clWhite; //(TColor)0xE0E0E0;//(TColor)0xF0F0F0;
Label1->Font->Color = (TColor)turquoise_color;
Label1->Font->Size = 10;
Label1->Left       = Label2->Left + 2;
Label1->Top        = AddContact_Img->Top + 2;
Label3->Color      = clWhite; //(TColor)0xE0E0E0;//(TColor)0xF0F0F0;
Label3->Font->Color = (TColor)turquoise_color;
Label3->Font->Size = 10;
Label3->Left       = Label1->Left;
Label3->Top        = Label1->Top + Label1->Height;

Panel2->Height = Panel_AddContact->Top - Panel2->Top;

Create_NSP();   //Network Status Panel for reflect my network status
INIT_NetState_Popup_Menu();
INIT_Comment_NetState_Popup_Menu();
PageControl1->Left = 0;
PageControl1->Top  = NSP->Top + NSP->Height + 2;  //30; //5;
PageControl1_Resize();

Panel3->BevelInner = bvNone;
Panel3->BevelOuter = bvNone;
Panel3->Top    = PageControl1->Top;
Panel3->Color  = clWhite; //clBtnFace;
Panel3->Left   = Panel2->Left;
Panel3->Width  = Panel2->Width; // - 2;
Panel3->Height = 29; //30; //37;

Image9->Top     = 0;
Image9->Left    = 0;
Image9->Height  = Panel3->Height;
Image9->Width   = LEFT_PANEL->Width/2; //Panel3->Width/2;

//TRBitMap rbmp(Image9->Width, Image9->Height,clWhite, clWhite);
//Image9->Canvas->Draw(0,0, rbmp.bmp);

Image9->Canvas->Brush->Color = clWhite;
Image9->Canvas->FillRect(Rect(0,0,Image9->Width,Image9->Height));

Image9->Canvas->Font->Color = clBlack;
Image9->Canvas->Font->Size  = 10;
Image9->Canvas->Font->Name  = _font_name_Arial;
Image9->Canvas->Font->Style = Image9->Canvas->Font->Style << fsBold;
AnsiString S  = "Контакты";
int tw        = Image9->Canvas->TextWidth(S);
int text_left = Image9->Width/2 - tw/2;
Image9->Canvas->TextOut(text_left,5,S);



Image10->Top    = Image9->Top;
Image10->Left   = Image9->Left + Image9->Width;
Image10->Height = Panel3->Height;
Image10->Width  = LEFT_PANEL->Width - Image9->Width;//Panel3->Width - Image9->Width;

Image10->Canvas->Brush->Color = (TColor)0x00E0E0E0;
Image10->Canvas->FillRect(Rect(0,0,Image10->Width,Image10->Height));

Image10->Canvas->Brush->Color = (TColor)0x00E0E0E0;
Image10->Canvas->Font->Color = clBlack;
Image10->Canvas->Font->Size  = 10;
Image10->Canvas->Font->Name  = _font_name_Arial;
Image10->Canvas->Font->Style = Image10->Canvas->Font->Style << fsBold;
S         = "Последние";
tw        = Image10->Canvas->TextWidth(S);
text_left = Image10->Width/2 - tw/2;
Image10->Canvas->TextOut(text_left,5,S);

TabSheet1->Left = 0;
TabSheet1->Top  = 0;
TabSheet1_Resize();
TabSheet1->Visible = true;

TabSheet2->Left = 0;
TabSheet2->Top  = 0;
TabSheet2_Resize();
TabSheet2->Visible = false;

//DrawGrid1->Cursor = crHandPoint;
DrawGrid1->Top    = 5;
DrawGrid1->Left   = 0;
DrawGrid1_Resize();

DG_LastCalls_Init();
DG_LastCall_Resize();

Panel_Chat->Color = (TColor)0xE0E0E0; //(TColor)0xF0F0F0;
Panel_Chat_Resize();
Memo_Chat->Clear();
Memo_Chat->Visible = false; //!!!
Memo1->Clear();
//Image_StartChat->Stretch = true;

TColor cl = Panel_Chat->Color;
RBitMap::change_color(0xFFFFFF, cl, Image_StartChat);

Panel_Dial_Init();
Image_Dig_Init();

IM_DrawGrid_Init();
IM_DrawGrid_Resize();

/*
CL_DrawGrid_Init();
CL_DrawGrid_Resize();
*/

CC_DrawGrid_Init();
Create_DialPag_Panel();

Panel1->Height     = VoiceCallPanel->Top  + VoiceCallPanel->Height + 10;
ComboBox1->Width   = VideoCallPanel->Left + VideoCallPanel->Width  + VideoCallPanel->Width;
//Splitter1->MinSize = VideoCallPanel->Left + VideoCallPanel->Width  + 20;
Width              = RIGHT_PANEL->Left    + Panel1->Left + ComboBox1->Left + ComboBox1->Width + 30;

CL_DrawGrid_Init();
CL_DrawGrid_Resize();

//DrawGrid1->DefaultDrawing = false;
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::CC_DrawGrid_Init()
{
CC_Panel->Left  = 0;    //Panel1->Left;
CC_Panel->Width = RIGHT_PANEL->Width/2; //Panel1->Width/2;
CC_Panel->Height = 300;
CC_Panel->Color  = (TColor)0xC0C0C0; //BtnFace (int, not clBtnFace!!!!! for setAddToConfBtnState())
//CC_Panel->Height = Panel_Chat->Top - Panel1->Top - Panel1->Height;

//CC_Edit->Width  = CC_Panel->Width - 10;
CC_Edit->Top    = 5;
CC_Edit->Left   = 5;

CC_DrawGrid->Left   = CC_Edit->Left;
CC_DrawGrid->Top    = CC_Edit->Top + CC_Edit->Height + 5;
//CC_DrawGrid->Width  = CC_Edit->Width;
CC_DrawGrid->Height = CC_Panel->Height - CC_Edit->Top - CC_Edit->Height - 50;
//CC_DrawGrid->ColWidths[0]  = CC_DrawGrid->Width;
CC_DrawGrid->GridLineWidth = 0;

CC_Img->Height = 30;
CC_Img->Width  = 180;
CC_Img->Top    = CC_DrawGrid->Top  + CC_DrawGrid->Height + 15;
//CC_Img->Left   = CC_Panel->Width/2 - CC_Img->Width/2;
CC_Img->Canvas->Font->Color = clWhite;
CC_Img->Canvas->Font->Size  = 10;
CC_Img->Canvas->Font->Name  = _font_name_Arial;
CC_Img->Canvas->Font->Style = CC_Img->Canvas->Font->Style << fsBold;

CC_Panel->Hide();
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::CL_DrawGrid_Init()
{
CL_DrawGrid->ColCount       = 1;
CL_DrawGrid->RowCount       = 1;
CL_DrawGrid->FixedCols      = 0;
CL_DrawGrid->FixedRows      = 0;
CL_DrawGrid->DefaultDrawing = false;
CL_DrawGrid->GridLineWidth  = 0;
CL_DrawGrid->BorderStyle    = bsNone;
CL_DrawGrid->ScrollBars     = ssNone; //ssVertical;


CL_DrawGrid->Width          = Panel1->Width;
CL_DrawGrid->Left           = 0;
CL_DrawGrid->ColWidths[0]   = CL_DrawGrid->Width;

}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::CL_DrawGrid_Resize()
{
CL_DrawGrid->Width        = Panel1->Width;
CL_DrawGrid->Left         = 0; // RIGHT_PANEL->Left;//Panel1->Left;
CL_DrawGrid->ColWidths[0] = CL_DrawGrid->Width;
if(prev_height > Height)
  {
  prev_height_for_cl = Height;
  if(CL_DrawGrid->Height > (Panel_Chat->Top - Panel1->Top - Panel1->Height))
     CL_DrawGrid->Height =  Panel_Chat->Top - Panel1->Top - Panel1->Height;
  }
else if(prev_height_for_cl < Height)
  {
  prev_height_for_cl = Height;
  if(CL_DrawGrid->VisibleRowCount < CL_DrawGrid->RowCount)
    {
    int client_height = Panel_Chat->Top - Panel1->Top - Panel1->Height;
    int height = 0;
    for(int i = CL_DrawGrid->RowCount - 1; i >= 0; i--)
       {
       if((height + CL_DrawGrid->RowHeights[i]) < client_height)
          height += CL_DrawGrid->RowHeights[i];
       else
          break;
       }
    CL_DrawGrid->Height = height;
    }
  }
CL_DrawGrid->Top  =  Panel1->Top  + Panel1->Height - 20;  //!!! Если не сделать -20 то почему - то не возникает событие  CL_DrawGridDrawCell()
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::IM_DrawGrid_Init()
{
IM_DrawGrid->ColCount    = 2; //1;
IM_DrawGrid->RowCount    = 1;
IM_DrawGrid->FixedCols   = 0;
IM_DrawGrid->FixedRows   = 0;
IM_DrawGrid->GridLineWidth = 0;
IM_DrawGrid->BorderStyle = bsNone;
IM_DrawGrid->ScrollBars  = ssVertical; // ssNone;
IM_DrawGrid->DefaultDrawing = false;   // !!!
IM_DrawGrid->Visible     = false;
}
//---------------------------------------------------------------------------
//---- work in main process thread only !!! ---------------------------------
//--------------------------------------------------------------------------
void __fastcall TIM_Struct::SetRowHeightsForLast_25_HSTRY_Msgs(TDrawGrid* IM_DG)
{
::EnterCriticalSection(&isl_cs);
  int n = IM_DG->RowCount;
  TImStrList::reverse_iterator it = isl.rbegin();
  while((it != isl.rend()) && (n > 0))
       {
       TImStr* imstr = (*it).second;
       if(imstr)
          imstr->SET_ROW_HEIGHT(n - 1);
       it++; n--;
       }
::LeaveCriticalSection(&isl_cs);
}
//---------------------------------------------------------------------------
void __fastcall TIM_Struct::set_state_of_file_transfer_RECEIVED(int index, int file_length, const string& file_id)
{
::EnterCriticalSection(&isl_cs);
  TImStrList::iterator it = isl.find(index);
  if(it != isl.end())
    {
    if((*it).second->get_im_tt() == IM_INVITE_ON_FILE_RECEIVING)
      {
      vector<string> v;
     (*it).second->copy_of_issl_strings(v);
      TExchFileMsg efm(0);
      efm.v = v;
      string is_file_id  = efm.get_substring_by_pattern("id:");
      if(is_file_id == file_id)
        {
        (*it).second->set_file_transfer_state__RECVD();
        (*it).second->set_file_length(file_length);
        }
      }   
    }
::LeaveCriticalSection(&isl_cs);
}
//---------------------------------------------------------------------------
void   __fastcall TIM_Struct::set_state_of_file_transfer_PROGRESS(int index)
{
::EnterCriticalSection(&isl_cs);
  TImStrList::iterator it = isl.find(index);
  if(it != isl.end())
    (*it).second->set_file_transfer_state__PROGRESS();
::LeaveCriticalSection(&isl_cs);
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::IM_DrawGrid_Resize()
{
IM_DrawGrid->Width        = Panel_Chat->Width - 5;
IM_DrawGrid->Left         = Panel_Chat->Left  + 5;
IM_DrawGrid->ColWidths[1] = 50;
IM_DrawGrid->ColWidths[0] = IM_DrawGrid->Width - IM_DrawGrid->ColWidths[1] - 20;//50;
if(prev_height > Height)       //Уменьшение высоты
  {
  prev_height = Height;
  if(IM_DrawGrid->Height > (Panel_Chat->Top - Panel1->Top - Panel1->Height))
     IM_DrawGrid->Height =  Panel_Chat->Top - Panel1->Top - Panel1->Height;
  IM_DrawGrid->Top  =  Panel_Chat->Top - IM_DrawGrid->Height;
  if(IM_DrawGrid->RowCount < 21)
   if(IM_DrawGrid->VisibleRowCount < IM_DrawGrid->RowCount)
     {
     IM_DrawGrid->Top    = Panel1->Top + Panel1->Height;
     IM_DrawGrid->Height = Panel_Chat->Top - Panel1->Top - Panel1->Height;
     int client_height   = Panel_Chat->Top - Panel1->Top - Panel1->Height;
     int height = 0;
     int i = IM_DrawGrid->RowCount - 1;
     if(i > 0)
       {
       for(;i >= 0; i--)
          {
          height += IM_DrawGrid->RowHeights[i];
          if(height > client_height)
            {
            i++;
            break;
            }
          }
       IM_DrawGrid->TopRow = i;
       }
     }
  IM_DrawGrid->Refresh();
  return;
  }
else if(prev_height < Height)     //Увеличение высоты
 {
 prev_height = Height;
 if(IM_DrawGrid->VisibleRowCount < IM_DrawGrid->RowCount)
   {
   IM_DrawGrid->Top    = Panel1->Top + Panel1->Height;
   IM_DrawGrid->Height = Panel_Chat->Top - Panel1->Top - Panel1->Height;
   if(IM_DrawGrid->RowCount < 21)
     {
     int client_height   = Panel_Chat->Top - Panel1->Top - Panel1->Height;
     int height = 0;
     int i = IM_DrawGrid->RowCount - 1;
     if(i > 0)
       {
       for(;i >= 0; i--)
          {
          height += IM_DrawGrid->RowHeights[i];
          if(height > client_height)
            {
            i++;
            break;
            }
          }
       IM_DrawGrid->TopRow = i;
       }
     }
    }
 else
   {
   IM_DrawGrid->Top  =  Panel_Chat->Top - IM_DrawGrid->Height;
   }
 IM_DrawGrid->Refresh();
 return;
 }
else                 //Высота не изменялась
 {
 if(IM_DrawGrid->RowCount < 21)
   {
   int call_panels_height = get_total_call_panels_height();
   int client_height = Panel_Chat->Top - Panel1->Top - Panel1->Height - call_panels_height;
   if(client_height > 0)
     {
     int height = 0;
     for(int i = IM_DrawGrid->RowCount - 1; i >= 0; i--)
        {
        if((height + IM_DrawGrid->RowHeights[i]) < client_height)
           height += IM_DrawGrid->RowHeights[i];
        else
           break;
        }
     IM_DrawGrid->Height = height;
     int draw_gd_top   =  Panel_Chat->Top - IM_DrawGrid->Height;
     if(draw_gd_top > 0)
       {
       IM_DrawGrid->Top  =  Panel_Chat->Top - IM_DrawGrid->Height;
       if(IM_DrawGrid->RowCount < 21)
         if(IM_DrawGrid->VisibleRowCount < IM_DrawGrid->RowCount)
           {
           draw_gd_top = Panel1->Top + Panel1->Height + call_panels_height;
           if(draw_gd_top < Panel_Chat->Top)
             {
             int draw_gd_height  = Panel_Chat->Top - Panel1->Top - Panel1->Height - call_panels_height;
             if(draw_gd_height > 0)
               {
               IM_DrawGrid->Top    = draw_gd_top;
               IM_DrawGrid->Height = draw_gd_height;
               int height = 0;
               int i = IM_DrawGrid->RowCount - 1;
               if(i > 0)
                 {
                 for(;i >= 0; i--)
                    {
                    height += IM_DrawGrid->RowHeights[i];
                    if(height > draw_gd_height) // client_height)
                      {
                      i++;
                      break;
                      }
                    }
                 }
               IM_DrawGrid->TopRow = i;
               }
             }
           }
       }
     } //if(client_height > 0)
   IM_DrawGrid->Refresh();
   return;
   } //if(IM_DrawGrid->RowCount < 21)
 else
   {
   int call_panels_height = get_total_call_panels_height();
   int draw_gd_top        = Panel1->Top + Panel1->Height + call_panels_height;
   if(draw_gd_top < Panel_Chat->Top)
     {
     IM_DrawGrid->Top    = draw_gd_top;
     IM_DrawGrid->Height = Panel_Chat->Top - IM_DrawGrid->Top;
     }
   IM_DrawGrid->Refresh();
   return;                                                        //1.1.24_71
   }
 } //else

/*
IM_DrawGrid->Top  =  Panel_Chat->Top - IM_DrawGrid->Height;
if(IM_DrawGrid->RowCount < 21)
 if(IM_DrawGrid->VisibleRowCount < IM_DrawGrid->RowCount)
   {
   IM_DrawGrid->Top    = Panel1->Top + Panel1->Height;
   IM_DrawGrid->Height = Panel_Chat->Top - Panel1->Top - Panel1->Height;
   int client_height   = Panel_Chat->Top - Panel1->Top - Panel1->Height;
   int height = 0;
   int i = IM_DrawGrid->RowCount - 1;
   if(i > 0)
     {
     for(;i >= 0; i--)
        {
        height += IM_DrawGrid->RowHeights[i];
        if(height > client_height)
          {
          i++;
          break;
          }
        }
     IM_DrawGrid->TopRow = i;
     }
  }
IM_DrawGrid->Refresh();
*/
}
//----------------------------------------------------------------------------
int __fastcall TMainFormSLS::get_total_call_panels_height()
{
int rv = 0;
for(int i = 0; i < MainFormSLS->ControlCount; i++)
   {
   TCall_Panel* Panel = dynamic_cast<TCall_Panel*>(MainFormSLS->Controls[i]);
   if(Panel)
      rv += Panel->Height;
   }
return rv;
}
//-----------------------------------------------------------------------------
void __fastcall TMainFormSLS::Display_Last_Instant_Msg()
{
//if(IM_DrawGrid->RowCount < 21)
//  {
  int client_height = Panel_Chat->Top - Panel1->Top - Panel1->Height;
  int height = 0;
  for(int i = IM_DrawGrid->RowCount - 1; i >= 0; i--)
     {
     if((height + IM_DrawGrid->RowHeights[i]) < client_height)
        height += IM_DrawGrid->RowHeights[i];
     else
        break;
     }
  IM_DrawGrid->Height = height;
  IM_DrawGrid->Top  =  Panel_Chat->Top - IM_DrawGrid->Height;
  if(IM_DrawGrid->VisibleRowCount < IM_DrawGrid->RowCount)
    {
    IM_DrawGrid->Top    = Panel1->Top + Panel1->Height;
    IM_DrawGrid->Height = Panel_Chat->Top - Panel1->Top - Panel1->Height;
    int client_height   = Panel_Chat->Top - Panel1->Top - Panel1->Height;
    int height = 0;
    int i = IM_DrawGrid->RowCount - 1;
    if(i > 0)
      {
      for(;i >= 0; i--)
         {
         height += IM_DrawGrid->RowHeights[i];
         if(height > client_height)
           {
           i++;
           break;
           }
         }
      IM_DrawGrid->TopRow = i;
      }
    }
//  }
//else
//  {
//  Im.SetRowHeightsForLast_25_HSTRY_Msgs(IM_DrawGrid);
//  IM_DrawGrid_Resize();
//  }
}
//----------------------------------------------------------------------------
void __fastcall TMainFormSLS::Display_Last_INVITE_ON_FILE_RECEIVE_Msg()
{
/*
IM_DrawGrid->Canvas->Draw(Rect.Left + 6, Rect.Top + 3, rcv_file_msg->Picture->Bitmap);
string file_name = imstr->get_substr_by_pattern("name:");
if(!file_name.empty())
  IM_DrawGrid->Canvas->TextOut( Rect.Left + 6 + rcv_file_msg->Width + 15, Rect.Top + 10, file_name.c_str());
*/  
}
//----------------------------------------------------------------------------
void __fastcall TMainFormSLS::Image_Dig_Init()
{
/*
Image_Dig_0->Tag     = 10;
Image_Dig_1->Tag     = 11;
Image_Dig_2->Tag     = 12;
Image_Dig_3->Tag     = 13;
Image_Dig_4->Tag     = 14;
Image_Dig_5->Tag     = 15;
Image_Dig_6->Tag     = 16;
Image_Dig_7->Tag     = 17;
Image_Dig_8->Tag     = 18;
Image_Dig_9->Tag     = 19;
Image_Dig_Star->Tag  = 20;
Image_Dig_Pound->Tag = 21;
 */


Image_Dig_1->OnMouseDown     = Image_Dig_MouseDown;
Image_Dig_2->OnMouseDown     = Image_Dig_MouseDown;
Image_Dig_3->OnMouseDown     = Image_Dig_MouseDown;
Image_Dig_4->OnMouseDown     = Image_Dig_MouseDown;
Image_Dig_5->OnMouseDown     = Image_Dig_MouseDown;
Image_Dig_6->OnMouseDown     = Image_Dig_MouseDown;
Image_Dig_7->OnMouseDown     = Image_Dig_MouseDown;
Image_Dig_8->OnMouseDown     = Image_Dig_MouseDown;
Image_Dig_9->OnMouseDown     = Image_Dig_MouseDown;
Image_Dig_0->OnMouseDown     = Image_Dig_MouseDown;
Image_Dig_Star->OnMouseDown  = Image_Dig_MouseDown;
Image_Dig_Pound->OnMouseDown = Image_Dig_MouseDown;


Image_Dig_1->OnMouseUp     = Image_Dig_MouseUp;
Image_Dig_2->OnMouseUp     = Image_Dig_MouseUp;
Image_Dig_3->OnMouseUp     = Image_Dig_MouseUp;
Image_Dig_4->OnMouseUp     = Image_Dig_MouseUp;
Image_Dig_5->OnMouseUp     = Image_Dig_MouseUp;
Image_Dig_6->OnMouseUp     = Image_Dig_MouseUp;
Image_Dig_7->OnMouseUp     = Image_Dig_MouseUp;
Image_Dig_8->OnMouseUp     = Image_Dig_MouseUp;
Image_Dig_9->OnMouseUp     = Image_Dig_MouseUp;
Image_Dig_0->OnMouseUp     = Image_Dig_MouseUp;
Image_Dig_Star->OnMouseUp  = Image_Dig_MouseUp;
Image_Dig_Pound->OnMouseUp = Image_Dig_MouseUp;

Image_Dig_Resize(0);
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::Panel_Dial_Init()
{
Panel_Dial->Top    = Panel1->Top  + Panel1->Height  + 10;
Panel_Dial->Left   = Panel1->Left + ComboBox1->Left;
Panel_Dial->Width  = Screen->Width/5;
Panel_Dial->Height = Screen->Height/5;
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::Image_Dig_Resize(int resize_type)
{
int BtnL  = Panel_Dial->Width/10 + 5;
int BtnT  = 20;
int BtnW  = 57;//init
int BtnH  = 28;
int HorzA = Panel_Dial->Width/50;
int VertA = Panel_Dial->Height/60;
if(resize_type)   //resize type == 0 on init and 1 on resize
  {
  BtnW = Panel_Dial->Width/4;
  BtnH = Panel_Dial->Height/7;
  }
Image_Dig_1->Width  = BtnW; Image_Dig_1->Height = BtnH;
Image_Dig_2->Width  = BtnW; Image_Dig_2->Height = BtnH;
Image_Dig_3->Width  = BtnW; Image_Dig_3->Height = BtnH;
Image_Dig_4->Width  = BtnW; Image_Dig_4->Height = BtnH;
Image_Dig_5->Width  = BtnW; Image_Dig_5->Height = BtnH;
Image_Dig_6->Width  = BtnW; Image_Dig_6->Height = BtnH;
Image_Dig_7->Width  = BtnW; Image_Dig_7->Height = BtnH;
Image_Dig_8->Width  = BtnW; Image_Dig_8->Height = BtnH;
Image_Dig_9->Width  = BtnW; Image_Dig_9->Height = BtnH;
Image_Dig_Star->Width  = BtnW; Image_Dig_Star->Height = BtnH;
Image_Dig_0->Width     = BtnW; Image_Dig_0->Height = BtnH;
Image_Dig_Pound->Width = BtnW; Image_Dig_Pound->Height = BtnH;

Image_Dig_1->Top     = BtnT;
Image_Dig_2->Top     = BtnT;
Image_Dig_3->Top     = BtnT;
Image_Dig_4->Top     = Image_Dig_1->Top + Image_Dig_1->Height + VertA;
Image_Dig_5->Top     = Image_Dig_4->Top;
Image_Dig_6->Top     = Image_Dig_4->Top;
Image_Dig_7->Top     = Image_Dig_4->Top + Image_Dig_1->Height + VertA;
Image_Dig_8->Top     = Image_Dig_7->Top;
Image_Dig_9->Top     = Image_Dig_7->Top;
Image_Dig_Star->Top  = Image_Dig_7->Top + Image_Dig_1->Height + VertA;
Image_Dig_0->Top     = Image_Dig_Star->Top;
Image_Dig_Pound->Top = Image_Dig_Star->Top;

Image_Dig_1->Left = BtnL;
Image_Dig_2->Left = Image_Dig_1->Left + Image_Dig_1->Width + HorzA;
Image_Dig_3->Left = Image_Dig_2->Left + Image_Dig_2->Width + HorzA;
Image_Dig_4->Left = BtnL;
Image_Dig_5->Left = Image_Dig_1->Left + Image_Dig_1->Width + HorzA;
Image_Dig_6->Left = Image_Dig_2->Left + Image_Dig_2->Width + HorzA;
Image_Dig_7->Left = BtnL;
Image_Dig_8->Left = Image_Dig_1->Left + Image_Dig_1->Width + HorzA;
Image_Dig_9->Left = Image_Dig_2->Left + Image_Dig_2->Width + HorzA;
Image_Dig_Star->Left  = BtnL;
Image_Dig_0->Left     = Image_Dig_1->Left + Image_Dig_1->Width + HorzA;
Image_Dig_Pound->Left = Image_Dig_2->Left + Image_Dig_2->Width + HorzA;

if(!resize_type)
   Image_Dig_Draw();   //On Start only download from ImageList
 }
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::Image_Dig_Draw()
{
ImageList_Dial_Btn_Norm->Draw(Image_Dig_1->Canvas,0,0,0,true);
ImageList_Dial_Btn_Norm->Draw(Image_Dig_2->Canvas,0,0,1,true);
ImageList_Dial_Btn_Norm->Draw(Image_Dig_3->Canvas,0,0,2,true);
ImageList_Dial_Btn_Norm->Draw(Image_Dig_4->Canvas,0,0,3,true);
ImageList_Dial_Btn_Norm->Draw(Image_Dig_5->Canvas,0,0,4,true);
ImageList_Dial_Btn_Norm->Draw(Image_Dig_6->Canvas,0,0,5,true);
ImageList_Dial_Btn_Norm->Draw(Image_Dig_7->Canvas,0,0,6,true);
ImageList_Dial_Btn_Norm->Draw(Image_Dig_8->Canvas,0,0,7,true);
ImageList_Dial_Btn_Norm->Draw(Image_Dig_9->Canvas,0,0,8,true);
ImageList_Dial_Btn_Norm->Draw(Image_Dig_Star->Canvas,0,0,9,true);
ImageList_Dial_Btn_Norm->Draw(Image_Dig_0->Canvas,0,0,10,true);
ImageList_Dial_Btn_Norm->Draw(Image_Dig_Pound->Canvas,0,0,11,true);
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::Panel_Dial_Resize()
{
if(bot_margin)
   Panel_Dial->Top = bot_margin;
else
   Panel_Dial->Top = Panel1->Top  + Panel1->Height + bot_margin + 10;
Panel_Dial->Left   = Panel1->Left + ComboBox1->Left;
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::Panel_Chat_Resize()
{
//Panel_Chat->Top    = Panel_AddContact->Top - 10;
Panel_Chat->Left   = 0;//RIGHT_PANEL->Left;//Panel1->Left;
Panel_Chat->Height = Panel_DialPad->Height + Panel_AddContact->Height;
Panel_Chat->Top    = RIGHT_PANEL->Height - Panel_Chat->Height - 4;
Panel_Chat->Width  = Panel1->Width; //RIGHT_PANEL->Width; // Panel1->Width;
if(MM_Img->Visible)
   MM_Img_Resize();
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::Image_StartChat_Resize()
{
Image_StartChat->Top  = Memo_Chat->Top; // + 3;
Image_StartChat->Left = Memo_Chat->Left + Memo_Chat->Width + 3; //5;
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::Memo_Chat_Resize()
{
Memo_Chat->Top    = 5;
Memo_Chat->Left   = 5;
Memo_Chat->Width  = Panel_Chat->Width - 50;
Memo_Chat->Height = Panel_Chat->Height - Memo_Chat->Top - 5;
Memo1->Top    = Memo_Chat->Top;
Memo1->Left   = Memo_Chat->Left;
Memo1->Width  = Memo_Chat->Width;
Memo1->Height = Memo_Chat->Height;
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::DrawGrid1_Resize()
{
DrawGrid1->Width        = TabSheet1->Width;
DrawGrid1->Height       = TabSheet1->Height - 8;
DrawGrid1->ColWidths[0] = DrawGrid1->Width;
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::DG_LastCalls_Init()
{
DG_LastCalls->Top           = 5;
DG_LastCalls->Left          = 0;
DG_LastCalls->ColCount      = 1; //2;
DG_LastCalls->RowCount      = 1;
DG_LastCalls->FixedCols     = 0;
DG_LastCalls->FixedRows     = 0;
DG_LastCalls->GridLineWidth = 0;
DG_LastCalls->BorderStyle   = bsNone;
DG_LastCalls->ScrollBars    = ssVertical; //ssNone;
}
//----------------------------------------------------------------------------
void __fastcall TMainFormSLS::DG_LastCall_Resize()
{
DG_LastCalls->Width        = TabSheet2->Width;
DG_LastCalls->Height       = TabSheet2->Height - 8;
//DG_LastCalls->ColWidths[1] = 100;
DG_LastCalls->ColWidths[0] = DG_LastCalls->Width; // - DG_LastCalls->ColWidths[1];
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::TabSheet1_Resize()
{
TabSheet1->Width  = PageControl1->Width;
TabSheet1->Height = PageControl1->Height;
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::TabSheet2_Resize()
{
TabSheet2->Width  = TabSheet1->Width;
TabSheet2->Height = TabSheet1->Height;
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::PageControl1_Resize()
{
PageControl1->Width  = Panel2->Width + 1;
if(NSP)
  PageControl1->Height = Panel2->Height - NSP->Height + 2;
else
  PageControl1->Height = Panel2->Height - 5;
}
//-------------------------------------------------------------------------------------------------------------------------------------------
//-- TMainFormSLS::FormResize() дублирует в некоторой степени функционал  TMainFormSLS::RIGHT_PANELResize(), т.е. дважды происходит обработка
//-- одних и тех же событий. Это необходимо т.к. при наличии вызова TCall_Panel не всегда приходит событие RIGHT_PANELResize() особенно
//-- при уменьшении размера окна TMainFormSLS -----------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------------------
void __fastcall TMainFormSLS::FormResize(TObject *Sender)
{
if(_CLOSE_REQUEST) return;
int MIN_WIDTH = RIGHT_PANEL->Left + Panel1->Left + VideoCallPanel->Left + VideoCallPanel->Width + 30;
if(Width > MIN_WIDTH + 30)
  {
  Panel1->Width = Width - Splitter1->Left - Splitter1->Width - 16;
  Panel_DialPad_Resize();
  Panel_AddContact_Resize();
  Panel2->Height = Panel_AddContact->Top - Panel2->Top;
  Panel_Chat_Resize();
  IM_DrawGrid->ColWidths[0] = IM_DrawGrid->Width - IM_DrawGrid->ColWidths[1] - 20;
  if(IM_DrawGrid->RowCount > 0)
    {
    TImStr* imstr = Im.getStr(0);
    if(imstr)
       imstr->set_top_row_height();
    }
  IM_DrawGrid_Resize();
  CallPanels_Resize();
  CC_Panel_Resize();
  if(DPP)
    if(DPP->Visible)
       DPP->resize();
  }
else
  {
  Width = MIN_WIDTH;
  Panel1->Width = Width - Splitter1->Left - Splitter1->Width - 16;
  ComboBox1->Width = VideoCallPanel->Left + VideoCallPanel->Width - VoiceCallPanel->Left;
  Panel_Chat_Resize();
  IM_DrawGrid->ColWidths[0] = IM_DrawGrid->Width - IM_DrawGrid->ColWidths[1] - 20;
  if(IM_DrawGrid->RowCount > 0)
    {
    TImStr* imstr = Im.getStr(0);
    if(imstr)
      imstr->set_top_row_height();
    }
  IM_DrawGrid_Resize();
  CallPanels_Resize();
  }

#ifdef Call_Btn_On_The_Middle_Of_The_Field
 //Image_VoiceCall->Left = Panel1->Width/2 - 1.5 * call_btn_width;
 Image_VoiceCall->Left = Panel1->Width/2  - call_btn_width - call_btn_width/2;
 //Image_VoiceCall->Left = Panel1->Width - 3 * call_btn_width;
 //Image_VoiceCall->Top  = Panel1->Height/2 - call_btn_height/2;
 ACBS.crc_img_left     = Image_VoiceCall->Left;     //for circular btn shape
 ACBS.crc_img_top      = Image_VoiceCall->Top;      //for circular btn shape

 Image_VideoCall->Left = Image_VoiceCall->Left + call_btn_width + call_btn_width/2;
 Image_VideoCall->Top  = Image_VoiceCall->Top;
 VCBS.crc_img_left     = Image_VideoCall->Left;
 VCBS.crc_img_top      = Image_VideoCall->Top;

// CalledNameLbl->Top    = Panel1->Height/2 - CalledNameLbl->Height/2;
#endif

if(ConferenceWin)
  if(ConferenceWin->Visible)
    if(ConferenceWin->get_size_CP())
      if(abs(ConferenceWin->Left - (MainFormSLS->Left  + MainFormSLS->Panel2->Left  + MainFormSLS->Panel2->Width + 4)) < 40)
        if(abs(ConferenceWin->Top - (MainFormSLS->Top  + MainFormSLS->Height - MainFormSLS->ClientHeight - 10)) < 40)
           ConferenceWin->ChangeWinLayout_OnResize();
}
//------------------------------------------------------------------------------
void __fastcall TConferenceWin::SetConfWinSize()
{
Left   = MainFormSLS->Left  + MainFormSLS->Panel2->Left  + MainFormSLS->Panel2->Width + 4;
Top    = MainFormSLS->Top   + MainFormSLS->Height - MainFormSLS->ClientHeight - 10; //MainFormSLS->Panel1->Top; //   + MainFormSLS->Panel1->Height;
Width  = MainFormSLS->Left  + MainFormSLS->Width  - Left - 6;
Height = MainFormSLS->Top   + MainFormSLS->Height - Top  - 6;
}
//------------------------------------------------------------------------------
void __fastcall TMainFormSLS::CC_Panel_Resize()
{
if(CC_Panel->Visible)
  {
  for(int i = 0; i < ControlCount; i++)
     {
     TCall_Panel* Panel = dynamic_cast<TCall_Panel*>(Controls[i]);
     if(Panel)
       if(Panel->Tag)
         if(Panel->Tag == CC_DrawGrid->Tag)
           {
           CC_Panel->Top = Panel->Top + Panel->Height;
           CC_Panel->Height = Panel_Chat->Top - CC_Panel->Top;
           }
     }
   }
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::Panel_DialPad_Resize()
{
Panel_DialPad->Left  = 0;
Panel_DialPad->Top   = Height - Panel_DialPad->Height - 60; //54;
//Panel_DialPad->Top   = LEFT_PANEL->Height - Panel_DialPad->Height;
Panel_DialPad->Width = LEFT_PANEL->Width; //Panel2->Width;
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::Panel_AddContact_Resize()
{
Panel_AddContact->Left  = 0;
Panel_AddContact->Top   = Height - Panel_DialPad->Height - Panel_AddContact->Height - 60; //54;
//Panel_AddContact->Top   = LEFT_PANEL->Height - Panel_DialPad->Height - Height - Panel_DialPad->Height - Panel_AddContact->Height;
Panel_AddContact->Width = LEFT_PANEL->Width; //Panel2->Width;
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::Panel1Resize(TObject *Sender)
{
ComboBox1->Width = Panel1->Width - ComboBox1->Left - 20;
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::Panel2Resize(TObject *Sender)
{
NSP->Width = Panel2->Width; // - 2;
PageControl1_Resize();
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::Button1Click(TObject *Sender)
{
TRect Rect = DrawGrid1->CellRect(0, 0);
ImageList1->Draw(DrawGrid1->Canvas,Rect.Left,Rect.Top, 0, true);

Rect = DrawGrid1->CellRect(1, 1);
ImageList1->Draw(DrawGrid1->Canvas,Rect.Left,Rect.Top, 1, true);

Rect = DrawGrid1->CellRect(1, 2);
ImageList1->Draw(DrawGrid1->Canvas,Rect.Left,Rect.Top+ Rect.Height()/2 - 8, 0, true);

Rect = DrawGrid1->CellRect(1, 3);
ImageList1->Draw(DrawGrid1->Canvas,Rect.Left,Rect.Top+ Rect.Height()/2 - 8, 1, true);

Rect = DrawGrid1->CellRect(1, 4);
ImageList1->Draw(DrawGrid1->Canvas,Rect.Left,Rect.Top+ Rect.Height()/2 - 8, 4, true);

Rect = DrawGrid1->CellRect(1, 5);
ImageList1->Draw(DrawGrid1->Canvas,Rect.Left,Rect.Top+ Rect.Height()/2 - 8, 5, true);

Rect = DrawGrid1->CellRect(1, 6);
ImageList1->Draw(DrawGrid1->Canvas,Rect.Left,Rect.Top+ Rect.Height()/2, 5, true);
 // return;
Graphics::TBitmap* Image =  new Graphics::TBitmap();
if(Image)
  {
  ImageList1->GetBitmap(1,Image); //Graphics::TBitmap* Image
  Rect = DrawGrid1->CellRect(0,2);
  DrawGrid1->Canvas->Draw(Rect.Left,Rect.Top,Image);
  delete Image;
  }
Graphics::TIcon* Icon =  new Graphics::TIcon();
if(Icon)
  {
  ImageList2->GetIcon(0,Icon); //Graphics::TBitmap* Image
  Rect = DrawGrid1->CellRect(0,3);
  DrawGrid1->Canvas->Draw(Rect.Left,Rect.Top,Icon);
  delete Icon;
  }

/*

{
  Graphics::TBitmap *pBitmap = new Graphics::TBitmap();
  try
  {
    pBitmap->LoadFromFile("C:\\Program Files\\Common Files\\Borland Shared\\Images\\Splash\\256color\\factory.bmp ");
    pBitmap->Transparent = true;
    pBitmap->TransparentColor = pBitmap->Canvas->Pixels[50,50];
    Form1->Canvas->Draw(0,0,pBitmap);
    pBitmap->TransparentMode = tmAuto;
    Form1->Canvas->Draw(50,50,pBitmap);
  }
  catch (...)

  {
    ShowMessage("Could not load or display bitmap");
  }
  delete pBitmap;
}


    void __fastcall TForm1::DrawGrid1DrawCell(TObject *Sender, long Col, long Row, TRect &Rect, TGridDrawState State)

{
  long index = Row * DrawGrid1->ColCount + Col;
  DrawGrid1->Canvas->Brush->Color = clBackground;
  DrawGrid1->Canvas->FillRect(Rect);
  ImageList1->Draw(DrawGrid1->Canvas,Rect.Left,Rect.Top,index);
  if (State.Contains(gdFocused))
    DrawGrid1->Canvas->DrawFocusRect(Rect);
}
 */
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::DrawGrid1DrawCell(TObject *Sender, int ACol,
      int ARow, TRect &Rect, TGridDrawState State)
{
if(State.Contains(gdFocused))
  {
  DrawGrid1->Canvas->Brush->Color = clActiveCaption;   //clBlue;// clBackground;
  DrawGrid1->Canvas->Font->Color  = clWhite;
  DrawGrid1->Canvas->FillRect(Rect);
  DrawGrid1->Canvas->DrawFocusRect(Rect);
  }
else if(State.Contains(gdSelected))
  {
  DrawGrid1->Canvas->Brush->Color = clActiveCaption;   //clBlue;// clBackground;
  DrawGrid1->Canvas->Font->Color  = clWhite;
  DrawGrid1->Canvas->FillRect(Rect);
  DrawGrid1->Canvas->DrawFocusRect(Rect);
  }
Sip->Contacts.Display(ImageList1, DrawGrid1, DrawGrid1->Canvas, ARow, Rect, State);
}
//---------------------------------------------------------------------------
#ifdef SIP_Video
void __fastcall TMainFormSLS::Proc_VIDEOOUT_Msg_READLIST()
{
TEventLogThread* elt = ofs->elt;
TExchBuf* buf = get_videoout_ExchLst();
if(buf)
  {
   switch(buf->emt){
         case ExchMsgType_VideoOut:{
              TVcamPar* vcpar = (TVcamPar*)buf->getAddBuf_Reset();
              if(vcpar)
                {
                string name = user_name_to_send; //ComboBox1->Text.c_str();
                if(!name.empty())
                  {
                  string callid = Sip->getCallID_CLD_tc(name);
                  if(callid.empty())
                    {
                    if(elt)
                       elt->FputEvt("\nCALL " + (string)"\"" +  name + "\"");
                    TSdpMediaCont smc;
                    smc.video = true;
                    smc.vcpar.width  = vcpar->width;
                    smc.vcpar.height = vcpar->height;
                    smc.vcpar.fps    = vcpar->fps;
                    Sip->sendInitInvite(name,ComboBox1->Text.c_str(),&smc);
                    }
                  }
                delete vcpar;
                }
              break;
              }  //case ExchMsgType_VideoOut:
         case ExchMsgType_VideoOut_REINVITE:{
              TVcamPar* vcpar = (TVcamPar*)buf->getAddBuf_Reset();
              if(vcpar)
                {
                TSdpMediaCont smc;
                smc.video = true;
                smc.vcpar.width  = vcpar->width;
                smc.vcpar.height = vcpar->height;
                smc.vcpar.fps    = vcpar->fps;
                Sip->sendInit_REINVITE_WITH_ADD_VIDEO(buf, &smc);
                delete vcpar;
                }
              break;
              }
         case ExchMsgType_Video_Out_Disconnect:{
              TMediaSession* ms = MainFormSLS->Sip->sss->GetMs_by_Call_Tag(buf->tag);
              if(ms)
                {
                TCall_Panel* call_panel = get_Call_Panel_By_Tag(ms->getCallTag());
                if(call_panel)
                  if(call_panel->get_call_state() == Call_State__Conference)
                     call_panel->conference_exit(ms);
                string callid = ms->getCallID();
                if(elt)
                   elt->FputEvt("\nDISCONNECT callid " + callid);
                MainFormSLS->Sip->send_call_disc_out(callid,false);
                MainFormSLS->Sip->del_CLD_tc(ms->get_uniq_username());
                if(call_panel)
                  {
                  HIDE_DPW(call_panel->Tag);
                  if(!ms->get_ms_hstry_written())
                    {
                    ms->set_ms_hstry_written(true);
                    call_panel->tstmps.get_conv_duration();
                    call_panel->outgoing_call_disc_out_hstry(ms->get_uniq_username(), ms->get_display_username());
                    }
                  call_panel->disconnect_screen_sharing();
                  call_panel->disconnect_parallel_phone();
                  }
                MainFormSLS->Sip->sss->EraseMediaSession(out_pref + callid); //ms deleted !!!
                MainFormSLS->push_req_to_del_call_panel(buf->tag);
                if(Form4->Visible)
                   Form4->Hide();
                if(Form3->Visible)
                   Form3->Hide();
                if(MainFormSLS->Panel_Dial->Visible)
                   MainFormSLS->Panel_Dial->Hide();
                Form4->set_leg_type(Lt_NDef);
                Form3->set_leg_type(Lt_NDef);
                }
              break;
              }
         case ExchMsgType_Video_In_Disconnect:{
              TMediaSession* ms = MainFormSLS->Sip->sss->GetMs_by_Call_Tag(buf->tag);
              if(ms)
                {
                TCall_Panel* call_panel = get_Call_Panel_By_Tag(ms->getCallTag());
                if(call_panel)
                  if(call_panel->get_call_state() == Call_State__Conference)
                     call_panel->conference_exit(ms);
                string callid = ms->getCallID();
                if(elt)
                   elt->FputEvt("\nDISCONNECT callid " + callid);
                MainFormSLS->Sip->send_call_disc_in(callid);
                MainFormSLS->Sip->del_CLD_tc(ms->get_uniq_username());
                if(call_panel)
                  {
                  HIDE_DPW(call_panel->Tag);
                  if(!ms->get_ms_hstry_written())
                    {
                    ms->set_ms_hstry_written(true);
                    call_panel->tstmps.get_conv_duration();
                    call_panel->incoming_call_disc_out_hstry(ms->get_uniq_username(), ms->get_display_username());
                    }
                  call_panel->disconnect_screen_sharing();
                  call_panel->disconnect_parallel_phone();
                  }
                MainFormSLS->Sip->sss->EraseMediaSession(in_pref + callid); //ms deleted !!!
                MainFormSLS->push_req_to_del_call_panel(buf->tag);
                if(Form4->Visible)
                   Form4->Hide();
                if(Form3->Visible)
                   Form3->Hide();
                if(MainFormSLS->Panel_Dial->Visible)
                   MainFormSLS->Panel_Dial->Hide();
                Form4->set_leg_type(Lt_NDef);
                Form3->set_leg_type(Lt_NDef);
                }
              break;
              }
         }
  delete buf;
  }
}
#endif
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::Panel1MouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
SetAudioAndVideoNormalState();
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::FormMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
SetAudioAndVideoNormalState();
if(NSP)
   NSP->Clear_Focus();
if(DialPad->Visible)
   DialPad->Clear_Controls_State();
if(CC_Panel->Visible)
   Refresh_AddToConfBtnState();
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::callin_exchlst_insert(TExchBuf* buf)
{
::EnterCriticalSection(&callin_exchlst_cs);
  call_exchlst.push_back(buf);
::LeaveCriticalSection(&callin_exchlst_cs);
}
//------------------------------------------------------------------------------
TExchBuf* __fastcall TMainFormSLS::get_call_ExchLst(TMessage& Message)
{
TExchBuf* rv = NULL;
::EnterCriticalSection(&callin_exchlst_cs);
  if(!call_exchlst.empty())
    {
    deque<TExchBuf*>::iterator it = call_exchlst.begin();
    while(it != call_exchlst.end())
         {
         if((*it)->WPARAM == Message.WParam)
           {
           rv = (*it);
           call_exchlst.erase(it);
           break;
           }
         it++;
         }
    }
::LeaveCriticalSection(&callin_exchlst_cs);
return rv;
}
//-----------------------------------------------------------------------------
void __fastcall TMainFormSLS::clear_call_ExchLst()
{
::EnterCriticalSection(&callin_exchlst_cs);
  while(!call_exchlst.empty())
       {
       TExchBuf* buf = call_exchlst.front();
       if(buf)delete buf;
       call_exchlst.pop_front();
       }
 ::LeaveCriticalSection(&callin_exchlst_cs);
}
//-----------------------------------------------------------------------------
void __fastcall TMainFormSLS::videoout_exchlst_insert(TExchBuf* buf)
{
::EnterCriticalSection(&videoout_exchlst_cs);
  videoout_exchlst.push(buf);
::LeaveCriticalSection(&videoout_exchlst_cs);
}
//------------------------------------------------------------------------------
TExchBuf* __fastcall TMainFormSLS::get_videoout_ExchLst()
{
TExchBuf* rv=NULL;
::EnterCriticalSection(&videoout_exchlst_cs);
  if(!videoout_exchlst.empty())
    {
    rv = videoout_exchlst.front();
    videoout_exchlst.pop();
    }
::LeaveCriticalSection(&videoout_exchlst_cs);
return rv;
}
//------------------------------------------------------------------------------
void __fastcall TMainFormSLS::clear_videoout_ExchLst()
{
::EnterCriticalSection(&videoout_exchlst_cs);
  while(!videoout_exchlst.empty())
       {
       TExchBuf* buf = videoout_exchlst.front();
       if(buf)delete buf;
       videoout_exchlst.pop();
       }
::LeaveCriticalSection(&videoout_exchlst_cs);
}
//------------------------------------------------------------------------------
void      __fastcall TMainFormSLS::filetrans_exchlst_insert(TExchBuf* buf)
{
::EnterCriticalSection(&filetrans_exchlst_cs);
  filetrans_exchlst.push(buf);
::LeaveCriticalSection(&filetrans_exchlst_cs);
}
//------------------------------------------------------------------------------
TExchBuf* __fastcall TMainFormSLS::get_filetrans_ExchLst()
{
TExchBuf* rv=NULL;
::EnterCriticalSection(&filetrans_exchlst_cs);
  if(!filetrans_exchlst.empty())
    {
    rv = filetrans_exchlst.front();
    filetrans_exchlst.pop();
    }
::LeaveCriticalSection(&filetrans_exchlst_cs);
return rv;
}
//------------------------------------------------------------------------------
void __fastcall TMainFormSLS::clear_filetrans_ExchLst()
{
::EnterCriticalSection(&filetrans_exchlst_cs);
  while(!filetrans_exchlst.empty())
       {
       TExchBuf* buf = filetrans_exchlst.front();
       if(buf)delete buf;
       filetrans_exchlst.pop();
       }
::LeaveCriticalSection(&filetrans_exchlst_cs);
}
//------------------------------------------------------------------------------
inline float tanf( float _X)
        {return ((float)tan((double)_X)); }
//---------------------------------------------------------------------------
/*
void __fastcall setupScreen()
{
 int w, h;

 glfwGetWindowSize( &w, &h );
 float halfFov, theTan, screenFov, aspect;

 screenFov = 60.0f;

 float eyeX = (float)w / 2.0;
 float eyeY = (float)h / 2.0;
 halfFov = PI * screenFov / 360.0;
 theTan = tanf(halfFov);
 float dist = eyeY / theTan;
 float nearDist = dist / 10.0; // near / far clip plane
 float farDist = dist * 10.0;
 aspect = (float)w/(float)h;
 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();
 gluPerspective(screenFov, aspect, nearDist, farDist);
 gluLookAt(eyeX, eyeY, dist,
 eyeX, eyeY, 0.0, 0.0, 1.0, 0.0);
 glMatrixMode(GL_MODELVIEW);
 glLoadIdentity();
}
*/
//-----------------------------------------------------------
void __fastcall TMainFormSLS::StartVideo()
{
#ifdef SIP_Video
if(Form2->Visible)
   Form2->Close();
if(!Form3->Visible)
  if(Form3->call_in_progress)
    {
    Form3->Remote_Video_Show();
    return;
    }
if(Form4->resize_block)
  {
   Form4->BorderStyle = bsSizeable;
   Form4->Panel1->Visible = false;
   if(Form4->bitmap)
     {
     Form4->bitmap->Height = 480;
     Form4->bitmap->Width  = 640;
     Form4->bitmap->Canvas->Rectangle(0,0,Form4->bitmap->Width,Form4->bitmap->Height);
     Form4->Height = Form4->bitmap->Height;
     Form4->Width  = Form4->bitmap->Width;
     }
   Form4->resize_block = false;
  }
Form4->Local_Video_Show();
if(Form3->Visible)
  if(Form3->call_in_progress)
    {
    Form3->FormStyle = fsStayOnTop;
    if((Form3->Width < 400)&&(Form3->Height < 350))
      {
      Form4->Width  = Form3->Width;
      Form4->Height = Form3->Height;
      Form4->Top    = Form3->Top;
      Form4->Left   = Form3->Left - Form3->Width;
      }
    }
#endif
}
//---------------------------------------------------------------------------
int __fastcall TMainFormSLS::Show_Outgoing_CallPanel(const string& nick_name, const string& name, TSdpMediaCont* smc, TConfCont* pConfCont, int tag_conf_creator)
{
int ttag = Sip->gen_call_tag();
TCall_Panel* panel = new TCall_Panel(this);
if(panel)
  {
  panel->Parent = this;
  panel->set_leg_type(Lt_Out);
 // panel->Top  = MainFormSLS->Panel1->Top + MainFormSLS->Panel1->Height;  //Устанавливается в CL_DrawGrid_OnDrawCell()
  panel->Left   = RIGHT_PANEL->Left;
  panel->Width  = MainFormSLS->Panel1->Width;
  panel->Height = MainFormSLS->Panel1->Height;
  panel->Color  = (TColor)0x00EEEEEE; // clSilver;
  panel->BevelInner = bvLowered;
  panel->BevelOuter = bvRaised;
  panel->Tag        = ttag;
  panel->nick_name  = nick_name;

  if(pConfCont)
    {
    panel->setConfCont(pConfCont);
    panel->set_conf_participant(true);
    panel->set_conf_creator(tag_conf_creator);
    pConfCont->call_panel_tag = ttag;
    }

  panel->create_images();
  if(smc)
    if(smc->video)
        panel->draw_active_cam_img();

  panel->create_lb();
  panel->create_lb_1();

  if(lng == Lang_RU)
    panel->lb_1->Caption = " Ожидание ответа ";
  else
    panel->lb_1->Caption = " Waiting For Answer ";
  panel->lb_1->Name = "lb_1";

  //panel->lb->Caption = " " + (AnsiString)"\"" + (AnsiString)name.c_str() + "\"" + " ";
  panel->lb->Caption = " " + (AnsiString)name.c_str() + " ";
  panel->display_name = name;

  getBottomCallPanelMargin();
  panel->disc_img->OnMouseUp    = panel->DiscImg_OutgoingCall_Panel_MouseUp;
  panel->mic_img->OnMouseUp     = panel->Mic_Img__MouseUp;
  panel->cam_img->OnMouseUp     = panel->Cam_Img__MouseUp;
  panel->speak_img->OnMouseUp   = panel->Speak_Img__MouseUp;
  panel->dial_img->OnMouseUp    = panel->Dial_Img__Mouse_Up;
  panel->conf_img->OnMouseUp    = panel->Conf_Img__Mouse_Up;
  panel->refer_img->OnMouseUp   = panel->Refer_img__Mouse_Up;
  panel->refer_img->Visible     = false;
  panel->screen_img->OnMouseUp  = panel->Screen_Img__Mouse_Up;
  panel->chat_img->OnMouseUp    = panel->Chat_Img__Mouse_Up;
  cps.add_panel_tag(panel->Tag,CL_DrawGrid);
  #ifdef Place_OnHold_All_ActiveCalls__OnActivateNewCall
            if(!tag_conf_creator)
              {
               MainFormSLS->Place_AllActiveCalls_OnHold(panel->Tag);
               MainFormSLS->ActivateAllPanels_Placed_OnHold();
              }
            panel->lochold_img->OnMouseUp = panel->LocHold_Img__Mouse_Up;
  #endif
  panel->panel_resize();
  panel->OnResize = panel->Call_Panel_Resize;
::PostMessage(Handle, CONTROL_MSG, WM_APP_MSG_WPARAM__IM__DRAWGRID_RESIZE_ON_CHANGE_CALL_COUNT, WM_APP_MSG_LPARAM__NOPARAM);
  }
return ttag;
}
//------------------------------------------------------------------------------
int __fastcall TMainFormSLS::Show_Outgoing_CallPanel_OnRefer(const string& nick_name, const string& name, TConfCont* pConfCont, int tag_conf_creator, int referred_tag)
{
int ttag = Sip->gen_call_tag();
TCall_Panel* panel = new TCall_Panel(this);
if(panel)
  {
  panel->Parent = this;
  panel->set_call_type(Call_Type_Refer);
  panel->set_leg_type(Lt_Out);
 // panel->Top  = MainFormSLS->Panel1->Top + MainFormSLS->Panel1->Height;  //Устанавливается в CL_DrawGrid_OnDrawCell()
  panel->Left   = RIGHT_PANEL->Left;
  panel->Width  = MainFormSLS->Panel1->Width;
  panel->Height = MainFormSLS->Panel1->Height;
  panel->Color  = (TColor)0x00EEEEEE; // clSilver;
  panel->BevelInner = bvLowered;
  panel->BevelOuter = bvRaised;
  panel->Tag        = ttag;
  panel->nick_name  = nick_name;
  panel->set_referred_call_panel_tag(referred_tag);

  if(pConfCont)
    {
    panel->setConfCont(pConfCont);
    panel->set_conf_participant(true);
    panel->set_conf_creator(tag_conf_creator);
    pConfCont->call_panel_tag = ttag;
    }

  panel->create_images_on_refer();

  panel->create_lb();
  panel->create_lb_1();

  if(lng == Lang_RU)
    panel->lb_1->Caption = " Ожидание ответа (Переадресация)";
  else
    panel->lb_1->Caption = " Waiting For Answer (Refer) ";
  panel->lb_1->Name = "lb_1";

  panel->lb->Caption = " " + (AnsiString)"\"" + (AnsiString)name.c_str() + "\"" + " ";

  getBottomCallPanelMargin();
  panel->disc_img->OnMouseUp    = panel->DiscImg_OutgoingCall_Panel_MouseUp;
  panel->conn_img->OnMouseUp    = panel->Conn_Img_MouseUp;
  panel->conn_img->Visible      = false;
  panel->lochold_img->OnMouseUp = panel->LocHold_Img__Mouse_Up;
  panel->lochold_img->ShowHint  = true;
  panel->lochold_img->Hint      = "Перевести в разговорное состояние";
  cps.add_panel_tag(panel->Tag,CL_DrawGrid);
::PostMessage(Handle, CONTROL_MSG, WM_APP_MSG_WPARAM__IM__DRAWGRID_RESIZE_ON_CHANGE_CALL_COUNT, WM_APP_MSG_LPARAM__NOPARAM);
  }
return ttag;
}
//------------------------------------------------------------------------------
void __fastcall TMainFormSLS::getBottomCallPanelMargin()
{
int bm = 0;
for(int i=0;i < ControlCount;i++)
   {
   TCall_Panel* call_panel =  dynamic_cast<TCall_Panel*>(Controls[i]);
   if(call_panel)
     if(call_panel->Tag)
       {
       int bottom = call_panel->Top + call_panel->Height;
       if(bm < bottom)
          bm = bottom;
       }
   }
bot_margin = bm;
}
//------------------------------------------------------------------------------
void __fastcall TCall_Panel::create_images()
{
create_disc_image();
create_mic_image();
create_speak_image();
create_conf_image();
create_dial_image();
create_refer_image();
create_lochold_image(disc_img->Left + 6*disc_img->Width);
create_remhold_image(disc_img->Left + 6*disc_img->Width + disc_img->Width/2);
create_screen_image();
create_cam_image();
create_chat_image();

MainFormSLS->ImageList3->Draw(disc_img->Canvas,0,0,0,true);     disc_img->Refresh();

mic_img->Picture->Bitmap   = MainFormSLS->mic_img_static->Picture->Bitmap;  mic_img->Refresh();

MainFormSLS->VideoCamImgList->Draw(cam_img->Canvas,0,0,0,true); cam_img->Refresh();

speak_img->Picture->Bitmap = MainFormSLS->speak_img_static->Picture->Bitmap; speak_img->Refresh();

conf_img->Picture->Bitmap  = MainFormSLS->conf_img_static->Picture->Bitmap;  conf_img->Refresh();

dial_img->Picture->Bitmap  = MainFormSLS->dial_img_static->Picture->Bitmap;  dial_img->Refresh();

chat_img->Picture->Bitmap  = MainFormSLS->chat_img_static->Picture->Bitmap;  chat_img->Refresh();

MainFormSLS->ImageList3->Draw(refer_img->Canvas,0,0,7,true);    refer_img->Refresh();
MainFormSLS->ImageList3->Draw(screen_img->Canvas,0,0,6,true);   screen_img->Refresh();

if(MainFormSLS->osv.dwMajorVersion < 6)  //OS < Vista (XP) демонстрация экрана не работает
   screen_img->Visible = false;
}
//------------------------------------------------------------------------------
void __fastcall TCall_Panel::create_images_on_refer()
{
create_disc_image();
create_conn_image(disc_img->Left + 2*disc_img->Width); //Refer connect
create_lochold_image(disc_img->Left + 6*disc_img->Width);
create_remhold_image(disc_img->Left + 6*disc_img->Width + disc_img->Width/2);
MainFormSLS->ImageList3->Draw(disc_img->Canvas,0,0,0,true);   disc_img->Refresh();
}
//-----------------------------------------------------------------------------
void __fastcall TCall_Panel::create_lb()
{
lb = new TLabel(this);
lb->Parent = this;
lb->Left = disc_img->Left; //panel->disc_img->Left + panel->disc_img->Width + 10;
lb->Top  = 2;
//lb->Color = clInactiveCaption;
lb->Font->Color  = (TColor)0xFF0000; //clBlack; //clWhite;
//lb->Font->Height = 8;
lb->Font->Size   = 11;
lb->Font->Name   = "Arial";
}
//-----------------------------------------------------------------------------
void __fastcall TCall_Panel::create_lb_1()
{
lb_1 = new TLabel(this);
lb_1->Parent = this;
lb_1->Left = lb->Left;
lb_1->Top  = lb->Top + lb->Height;
//lb_1->Color = clInactiveCaption;
lb_1->Font->Color = (TColor)0x008000; //clBlack; //clWhite;
//lb_1->Font->Height = 8;
lb_1->Font->Size   = 10;
lb_1->Font->Name = "Arial";
}
//-----------------------------------------------------------------------------
//-- Используется при переадресации из разговора ------------------------------
//-----------------------------------------------------------------------------
void __fastcall TCall_Panel::create_conn_image(int left)
{
conn_img = new TImage(this);
conn_img->Parent = this;
conn_img->Left   = left; //disc_img->Left + disc_img->Width + 30; //60;
conn_img->Width  = 92;
conn_img->Height = 24;
conn_img->Top    = disc_img->Top;
conn_img->Tag    = Tag;
conn_img->Transparent = true;

conn_img->Canvas->Font->Color  = clBlack; //clGrayText;
conn_img->Canvas->Font->Name   = "Arial";
conn_img->Canvas->Font->Size   = 10;
conn_img->Canvas->Font->Style  = conn_img->Canvas->Font->Style << fsBold;
AnsiString S     = "Соединить";
int tw           = conn_img->Canvas->TextWidth(S);
int th           = conn_img->Canvas->TextHeight(S);
int text_left    = conn_img->Width/2  - tw/2 - 1;
int text_top     = conn_img->Height/2 - th/2 - 1;
int w            = conn_img->Width; // - 4;
int h            = conn_img->Height;// - 4;
conn_img->Canvas->Brush->Color = (TColor)0x00EEEEEE;

//conn_img->Canvas->Brush->Color = clWhite;
conn_img->Canvas->FillRect(Rect(0,0,conn_img->Width,conn_img->Height));

TRBitMap rbmp(w, h, (TColor)0x00EEEEEE, clGray, (TColor)0x00DEDEDE);
//TRBitMap rbmp(w, h, (TColor)0x00EEEEEE, clBlue);
conn_img->Canvas->Draw(0,0, rbmp.bmp);
conn_img->Canvas->Brush->Color = (TColor)0x00DEDEDE;
conn_img->Canvas->TextOut(text_left, text_top, S);
}
//----------------------------------------------------------------------------
void __fastcall TCall_Panel::create_disc_image()
{
disc_img = new TImage(this);
disc_img->Parent = this;
disc_img->Left   = 15;
disc_img->Width  = 24;
disc_img->Height = 24;
disc_img->Top    = Height/2;
disc_img->Tag    = Tag;
disc_img->ShowHint     = true;
disc_img->Hint         = "Отбой";
disc_img->Transparent  = true;
disc_img__default_left = disc_img->Left;
}
//-----------------------------------------------------------------------------
void __fastcall TCall_Panel::create_mic_image()
{
mic_img = new TImage(this);
mic_img->Parent = this;
mic_img->Left   = disc_img->Left + disc_img->Width + 60;
mic_img->Width  = 24;
mic_img->Height = 24;
mic_img->Top    = disc_img->Top;
mic_img->Tag    = Tag;
mic_img->ShowHint    = true;
mic_img->Hint        = "Выключить микрофон";
mic_img->Transparent = true;
mic_img__default_left = mic_img->Left;
}
//-----------------------------------------------------------------------------
void __fastcall TCall_Panel::create_cam_image()
{
cam_img = new TImage(this);
cam_img->Parent = this;
cam_img->Width  = 32;
cam_img->Height = 32;
cam_img->Left   = screen_img->Left + screen_img->Width + 10;
cam_img->Top    = disc_img->Top - 4;
cam_img->Tag    = Tag;
cam_img->ShowHint    = true;
cam_img->Hint        = "Включить камеру";
cam_img->Transparent = true;
cam_img__default_left = cam_img->Left;
}
//-----------------------------------------------------------------------------
void __fastcall TCall_Panel::create_speak_image()
{
speak_img = new TImage(this);
speak_img->Parent = this;
speak_img->Left   = mic_img->Left + mic_img->Width + 10;
speak_img->Width  = 24;
speak_img->Height = 24;
speak_img->Top    = disc_img->Top;
speak_img->Tag    = Tag;
speak_img->ShowHint    = true;
speak_img->Hint        = "Громкость";
speak_img->Transparent = true;
speak_img__default_left = speak_img->Left;
}
//-----------------------------------------------------------------------------
void __fastcall TCall_Panel::create_conf_image()
{
conf_img = new TImage(this);
conf_img->Parent = this;
conf_img->Left   = speak_img->Left + speak_img->Width + 10;
conf_img->Width  = 24;
conf_img->Height = 24;
conf_img->Top    = disc_img->Top;
conf_img->Tag    = Tag;
conf_img->ShowHint    = true;
conf_img->Hint        = "Подключить к разговору";
conf_img->Transparent = true;
conf_img__default_left = conf_img->Left;
}
//-----------------------------------------------------------------------------
void __fastcall TCall_Panel::create_dial_image()
{
dial_img = new TImage(this);
dial_img->Parent = this;
dial_img->Left   = conf_img->Left + conf_img->Width + 10;
dial_img->Width  = 24;
dial_img->Height = 24;
dial_img->Top    = disc_img->Top;
dial_img->Tag    = Tag;
dial_img->ShowHint    = true;
dial_img->Hint        = "DTMF Набор";
dial_img->Transparent = true;
dial_img__default_left = dial_img->Left;
}
//-----------------------------------------------------------------------------
void __fastcall TCall_Panel::create_refer_image()
{
refer_img = new TImage(this);
refer_img->Parent = this;
refer_img->Left   = dial_img->Left + dial_img->Width + 10;
refer_img->Width  = 24;
refer_img->Height = 24;
refer_img->Top    = disc_img->Top;
refer_img->Tag    = Tag;
refer_img->ShowHint    = true;
refer_img->Hint        = "Переадресация";
refer_img->Transparent = true;
refer_img__default_left = refer_img->Left;
}
//-----------------------------------------------------------------------------
void __fastcall TCall_Panel::create_lochold_image(int left)
{
int WIDTH = 92, HEIGHT = 24;
lochold_img = new TImage(this);
lochold_img->Parent = this;
lochold_img->Left   = left;
lochold_img->Width  = WIDTH;
lochold_img->Height = HEIGHT;
lochold_img->Top    = disc_img->Top  + disc_img->Height/2 - lochold_img->Height/2;
lochold_img->Tag    = Tag;
lochold_img->ShowHint    = true;
lochold_img->Transparent = true;

//lochold_img->ShowHint    = true;
//lochold_img->Hint        = "Перевести в разговорное состояние";

lochold_img->Canvas->Brush->Color = (TColor)0x00EEEEEE;
lochold_img->Canvas->FillRect(Rect(0, 0, lochold_img->Width, lochold_img->Height));
TRBitMap rbmp(lochold_img->Width, lochold_img->Height, (TColor)0x00EEEEEE, clGray, (TColor)0x00CECECE);
//TRBitMap rbmp(lochold_img->Width, lochold_img->Height, (TColor)0x00EEEEEE, (TColor)0x00CECECE);
lochold_img->Canvas->Draw(0, 0, rbmp.bmp);
lochold_img->Visible = false;

int w = 5, h = HEIGHT - 10;
TRBitMap rbmp_2(w, h, clWhite);
rbmp_2.prepare_line_img();
int left_2 = WIDTH/2 - w - 2;
int top_2  = HEIGHT/2 - h/2;
MainFormSLS->draw_margin_line(lochold_img->Canvas, left_2, top_2, rbmp_2);

TRBitMap rbmp_3(w, h, clWhite);
rbmp_3.prepare_line_img();
int left_3 = WIDTH/2 + 2; //4;
MainFormSLS->draw_margin_line(lochold_img->Canvas, left_3, top_2, rbmp_3);
}
//-----------------------------------------------------------------------------
void __fastcall TCall_Panel::create_remhold_image(int left)
{
int WIDTH = 52, HEIGHT = 52;
remhold_img = new TImage(this);
remhold_img->Parent = this;
remhold_img->Left   = left;
remhold_img->Width  = WIDTH;
remhold_img->Height = HEIGHT;
remhold_img->Top    = Height/2 - HEIGHT/2 + 10;
remhold_img->Tag    = Tag;
//remhold_img->ShowHint    = true;
remhold_img->Transparent = true;

remhold_img->Canvas->Brush->Color = (TColor)0x00EEEEEE;
remhold_img->Canvas->FillRect(Rect(0, 0, remhold_img->Width, remhold_img->Height));
TRBitMap rbmp(remhold_img->Width, remhold_img->Height, (TColor)0x00EEEEEE, (TColor)0x00CECECE);
remhold_img->Canvas->Draw(0, 0, rbmp.bmp);
remhold_img->Visible = false;

int w = 10, h = HEIGHT - 15;
TRBitMap rbmp_2(w, h, clWhite);
rbmp_2.prepare_line_img();
int left_2 = WIDTH/2 - w - 3; //2;
int top_2  = HEIGHT/2 - h/2;
MainFormSLS->draw_margin_line(remhold_img->Canvas, left_2, top_2, rbmp_2);

TRBitMap rbmp_3(w, h, clWhite);
rbmp_3.prepare_line_img();
int left_3 = WIDTH/2 + 3; //2; //4;
MainFormSLS->draw_margin_line(remhold_img->Canvas, left_3, top_2, rbmp_3);
}
//-----------------------------------------------------------------------------
void __fastcall TCall_Panel::create_screen_image()
{
screen_img = new TImage(this);
screen_img->Parent = this;
screen_img->Left   = dial_img->Left + 2*dial_img->Width + 10;
screen_img->Width  = 24;
screen_img->Height = 24;
screen_img->Top    = disc_img->Top;
screen_img->Tag    = Tag;
screen_img->ShowHint    = true;
screen_img->Hint        = "Демонстрация экрана";
screen_img->Transparent = true;
screen_img__default_left = screen_img->Left;
}
//-----------------------------------------------------------------------------
void __fastcall TCall_Panel::create_chat_image()
{
chat_img = new TImage(this);
chat_img->Parent = this;
chat_img->Width  = 32;
chat_img->Height = 32;
chat_img->Left   = Width - chat_img->Width - 15;  //cam_img->Left + 2*dial_img->Width + 10;
chat_img->Top    = disc_img->Top - 5;
chat_img->Tag    = Tag;
chat_img->ShowHint    = true;
chat_img->Hint        = "Отправить сообщение";
chat_img->Transparent = true;
chat_img__default_left = chat_img->Left;
}
//-----------------------------------------------------------------------------
bool  __fastcall TCall_Panel::is_ccl_q_contact(const TConfCont& ConfCont)
{
bool rv = false;
::EnterCriticalSection(&ccl_q_cs);
  if(!ccl_q.empty())
    {
    deque<TConfCont>::iterator it = ccl_q.begin();
    while(it != ccl_q.end())
         {
         if(ConfCont.internal)
           {
           if((*it).internal)
             if((*it).id == ConfCont.id)
               {
               rv = true;
               break;
               }
           }
         else if((*it).name == ConfCont.name)
           {
           rv = true;
           break;
           }
         it++;
         }
    }
::LeaveCriticalSection(&ccl_q_cs);
return rv;
}
//---------------------------------------------------------------------------
void __fastcall TCall_Panel::add_ccl_q_contact(const TConfCont& ConfCont)
{
::EnterCriticalSection(&ccl_q_cs);
  if(ConfCont.internal)
    {
    if(ConfCont.id != -1)
       ccl_q.push_back(ConfCont);
    }
  else if(!ConfCont.name.empty())
       ccl_q.push_back(ConfCont);
  MainFormSLS->CC_DrawGrid->RowCount = ccl_q.size();
::LeaveCriticalSection(&ccl_q_cs);
}
//---------------------------------------------------------------------------
void __fastcall TCall_Panel::del_ccl_q_contact(const TConfCont& ConfCont)
{
::EnterCriticalSection(&ccl_q_cs);
  if(!ccl_q.empty())
    {
      deque<TConfCont>::iterator it = ccl_q.begin();
      while(it != ccl_q.end())
           {
           if(ConfCont.internal)
             {
             if((*it).internal)
               if((*it).id == ConfCont.id)
                 {
                 ccl_q.erase(it);
                 break;
                 }
             }
           else if((*it).name == ConfCont.name)
             {
             ccl_q.erase(it);
             break;
             }
           it++;
           }
    }
  MainFormSLS->CC_DrawGrid->RowCount = ccl_q.size();
::LeaveCriticalSection(&ccl_q_cs);
}
//----------------------------------------------------------------------------
TConfCont __fastcall TCall_Panel::get_conf_contact_by_row(unsigned ROW)
{
TConfCont rv(-1);
::EnterCriticalSection(&ccl_q_cs);
  if(!ccl_q.empty())
    {
    if(ROW < ccl_q.size())
       rv = ccl_q[ROW];
    }
::LeaveCriticalSection(&ccl_q_cs);
return rv;
}
//---------------------------------------------------------------------------
int  __fastcall TCall_Panel::get_ccl_q_size()
{
int rv;
::EnterCriticalSection(&ccl_q_cs);
  rv = ccl_q.size();
::LeaveCriticalSection(&ccl_q_cs);
return rv;
}
//-----------------------------------------------------------------------------
TConfCont  __fastcall TCall_Panel::get_first_ccl_q_contact()
{
TConfCont rv(-1);
::EnterCriticalSection(&ccl_q_cs);
  if(!ccl_q.empty())
    {
    rv = ccl_q.front();
    ccl_q.pop_front();
    MainFormSLS->CC_DrawGrid->RowCount = ccl_q.size();
    }
::LeaveCriticalSection(&ccl_q_cs);
return rv;
}
//-----------------------------------------------------------------------------
bool __fastcall TCall_Panel::is_ccl_contact(const TConfCont& ConfCont)
{
bool rv = false;
::EnterCriticalSection(&ccl_cs);
  if(!ccl.empty())
    {
    deque<TConfCont>::iterator it = ccl.begin();
    while(it != ccl.end())
         {
         if(ConfCont.internal)
           {
           if((*it).internal)
             if((*it).id == ConfCont.id)
               {
               rv = true;
               break;
               }
           }
         else if((*it).name == ConfCont.name)
           {
           rv = true;
           break;
           }
         it++;
         }
    }
::LeaveCriticalSection(&ccl_cs);
return rv;
}
//-----------------------------------------------------------------------------
void  __fastcall TCall_Panel::add_ccl_contact(const TConfCont& ConfCont)
{
::EnterCriticalSection(&ccl_cs);
  if(ConfCont.internal)
    {
    if(ConfCont.id != -1)
      if(!is_ccl_contact(ConfCont))
        ccl.push_back(ConfCont);
    }
  else
    {
    if(!is_ccl_contact(ConfCont))
       ccl.push_back(ConfCont);
    }
::LeaveCriticalSection(&ccl_cs);
}
//-----------------------------------------------------------------------------
void  __fastcall TCall_Panel::del_ccl_contact(const TConfCont& ConfCont)
{
::EnterCriticalSection(&ccl_cs);
  if(!ccl.empty())
    {
    deque<TConfCont>::iterator it = ccl.begin();
    while(it != ccl.end())
         {
         if(ConfCont.internal)
           {
           if((*it).internal)
             if((*it).id == ConfCont.id)
               {
               ccl.erase(it);
               break;
               }
           }
         else if((*it).name == ConfCont.name)
           {
           ccl.erase(it);
           break;
           }
         it++;
         }
    }
::LeaveCriticalSection(&ccl_cs);
}
//-----------------------------------------------------------------------------
bool __fastcall TCall_Panel::ccl_empty()
{
bool rv;
::EnterCriticalSection(&ccl_cs);
  rv = ccl.empty();
::LeaveCriticalSection(&ccl_cs);
return rv;
}
//-----------------------------------------------------------------------------
int __fastcall TCall_Panel::get_ccl_size()
{
int rv;
::EnterCriticalSection(&ccl_cs);
  rv = ccl.size();
::LeaveCriticalSection(&ccl_cs);
return rv;
}
//-----------------------------------------------------------------------------
void __fastcall TCall_Panel::get_ccl_copy(deque<TConfCont>& ccl_t)
{
::EnterCriticalSection(&ccl_cs);
  ccl_t = ccl;
  deque<TConfCont>::iterator it = ccl_t.begin();
  while(it != ccl_t.end())
       (*it++).denied_of_deletion_conf_panel = true;   // в копии удалять указатель запрещено
::LeaveCriticalSection(&ccl_cs);
}
//-----------------------------------------------------------------------------
void __fastcall TCall_Panel::get_ccl_copy__with_clear_screen_sharing_call_ids(deque<TConfCont>& ccl_t)
{
::EnterCriticalSection(&ccl_cs);
  ccl_t = ccl;
  deque<TConfCont>::iterator it = ccl_t.begin();
  while(it != ccl_t.end())
       (*it++).denied_of_deletion_conf_panel = true;   // в копии удалять указатель запрещено
  it = ccl.begin();
  while(it != ccl.end())
       (*it++).screen_sharing_sender_call_id.clear();
::LeaveCriticalSection(&ccl_cs);
}
//-----------------------------------------------------------------------------
void __fastcall TCall_Panel::set_conf_cont_answered(int tag)
{
::EnterCriticalSection(&ccl_cs);
  deque<TConfCont>::iterator it = ccl.begin();
  while(it != ccl.end())
       {
       if((*it).call_panel_tag == tag)
         {
         (*it).cc_call_state = 1; //Answered
         break;
         }
       it++;
       }
::LeaveCriticalSection(&ccl_cs);
}
//-------------------------------------------------------------------------------
void __fastcall TMainFormSLS::Answer_On_Outgoing_CallPanel(TMediaSession* ms)
{
try{
for(int i = 0; i < ControlCount; i++)
   {
   TCall_Panel* Panel = dynamic_cast<TCall_Panel*>(Controls[i]);
   if(Panel)
     if(Panel->Tag)
       if(Panel->Tag == ms->getCallTag())
         {
         int conf_creator = Panel->get_conf_creator();  // Получить Tag панели создателя конференции (не данной панели !!!)
         if(conf_creator != -1)
           {                 //Данная панель является пассивным участником конференции
           TConfCont ConfCont = Panel->getConfCont();
           TCall_Panel* Panel_Conf_Creator = get_Call_Panel_By_Tag(conf_creator);
           if(Panel_Conf_Creator)
             {
             TUdpChannel* uc_creator = NULL;
             TMediaSession* ms_creator = Sip->sss->GetMs_by_Call_Tag(Panel_Conf_Creator->Tag);
             if(ms_creator)
               {
               uc_creator = ms_creator->getSoundChannel();
               if(uc_creator)
                 {
                 TUdpChannel* uc_party = ms->getSoundChannel();
                 if(uc_party)
                   {
                   Sip->sss->Connect_Conference_Channels(uc_creator,uc_party);
                   Panel_Conf_Creator->set_conf_cont_answered(Panel->Tag);
                   deque<TConfCont> ccl_t;
                   Panel_Conf_Creator->get_ccl_copy(ccl_t);
                   if(Panel_Conf_Creator->get_call_state() != Call_State__Conference)
                      change_call_state_to_conference(Panel_Conf_Creator, Panel_Conf_Creator->Tag);
                   change_call_state_to_conference(Panel,Panel_Conf_Creator->Tag);
                   Panel->tstmps.get_conv_start_tstmp();
                   Ans_Participant_To_Conf_Window(Panel->nick_name);  //Ans participant to local ConferenceWin

                   deque<TConfCont> ccl_t_1 = ccl_t;
                   SendConference_INFO_About_ALL_Participants_to_NEW_participant(ms, ccl_t);
                   ConfCont.cc_call_state = 1; //Answered
                   if(ConfCont.user_name.empty())
                      ConfCont.user_name = Panel->nick_name;
                   Exclude_UserName_From_Dest_List(ccl_t_1, ConfCont.user_name); //Исключить из списка рассылки ConfCont.user_name и затем отправить INFO Answer всем остальным участникам конференции
                   SendConference_INFO_About_NEW_Participant_to_ALL_participants(Panel_Conf_Creator->get_leg_type(), Panel_Conf_Creator, ConfCont, ccl_t_1); //Send INFO msg to all answered conference participants (excluding conference_creator and new participant) about new participant
                   }
                 }
               }
             }
           } //if(conf_creator != -1)
         else
           {
          // Panel->lb->Color = clActiveCaption;
           if(Panel->get_call_state() == Call_State__Request_Hold_By_Local_Party)
             {
             Panel->set_call_state(Call_State__Hold_By_Local_Party);
             }
           else
             {
             Panel->lb_1->Hide();
             Panel->set_call_state(Call_State__Answer);
             String S = Panel->lb->Caption;
             if(ms->get_leg_type() == Lt_Out)
               {
               if(!Panel->get_200_OK_RCVD())
                 {
                 Panel->lb->Top += 4;
                 Panel->tstmps.get_conv_start_tstmp();
                 Panel->set_img_visible(Panel->refer_img, true);
                 Panel->set_img_visible(Panel->conn_img, true);
                 if(Panel->get_call_type() == Call_Type_Refer)
                    ActivateAllPanels_Placed_OnHold();
                 Panel->set_200_OK_RCVD(true);
                 }
               else
                 {
                 string s = S.c_str();
                 int st = s.find(":");
                 if(st != -1)
                    s.resize(st);
                 S = s.c_str();
                 }
               }
             else if(ms->get_leg_type() == Lt_In)
               {
                 string s = S.c_str();
                 int st = s.find(":");
                 if(st != -1)
                    s.resize(st);
                 S = s.c_str();
               }
             /*
             if(lng == Lang_RU)
                S += ": Разговор ";
             else
                S += ": Conversation ";
             */
             Panel->lb->Caption = S;
             }
           }
         }
   }
}//try
catch(Exception& e){exsSstEXCEPTION(ofs->elt,"__Answer_On_Outgoing_CallPanelg()",e);}
}
//-----------------------------------------------------------------------------
void __fastcall TMainFormSLS::NotAcceptable_On_Outgoing_CallPanel(TMediaSession* ms)
{
try{
for(int i = 0; i < ControlCount; i++)
   {
   TCall_Panel* Panel = dynamic_cast<TCall_Panel*>(Controls[i]);
   if(Panel)
     if(Panel->Tag)
       {
       if(DialPad->Visible)
         if(Panel->Tag == DialPad->Tag)
            DialPad->Hide_DPW();
       if(Panel->Tag == ms->getCallTag())
         {
         Panel->start_time_play_sound();
         Panel->lb_1->Hide();
         Panel->set_call_state(Call_State__NotAcceptable);
         String S = Panel->lb->Caption;
         if(lng == Lang_RU)
            S += ": Абонент недоступен ";
         else
            S += ": Not Acceptable ";
         Panel->lb->Caption = S;
         Panel->lb->Top += 4;
         if(!Panel->get_hstry_written())
           {
           Panel->set_hstry_written(true);
           TExchBuf* buf = new TExchBuf(WM_APP_MSG_WPARAM__CALL_OUT);
           if(buf)
             {
             buf->emt   = ExchMsgType_NotAcceptable;
             buf->msg   = ms->get_uniq_username();
             buf->msg_5 = ms->get_display_username();
             callin_exchlst_insert(buf);
             ::PostMessage(Handle, CALL_MSG, WM_APP_MSG_WPARAM__CALL_OUT, WM_APP_MSG_LPARAM__READLIST);
             }
           }
         }
       }
   }
}//try
catch(Exception& e){exsSstEXCEPTION(ofs->elt,"__NotAcceptable_On_Outgoing_CallPanel()",e);}
}
//-----------------------------------------------------------------------------
void __fastcall TMainFormSLS::PlaceCall_OnHold(TMediaSession* ms)
{
try{
for(int i = 0; i < ControlCount; i++)
   {
   TCall_Panel* Panel = dynamic_cast<TCall_Panel*>(Controls[i]);
   if(Panel)
     if(Panel->Tag)
      if(Panel->Tag == ms->getCallTag())
        {
        if(Panel->lb)
          {
          string s = Panel->lb->Caption.c_str();
          int st = s.find(":");
          if(st != -1)
            {
            s.resize(st);
            if(MainFormSLS->lng == Lang_RU)
             //  s += ": Вызов поставлен на удержание ";
               s += ": Вызов на удержании ";
            else
               s += ": Call placed on hold ";
            Panel->lb->Caption = s.c_str();
            }
          }
        if(Panel->lb_1)
          if(Panel->lb_1->Visible)
             Panel->lb_1->Visible = false;
        Panel->SetVisible_REM_HOLD();
        }
   }
}//try
catch(Exception& e){exsSstEXCEPTION(ofs->elt,"__PlaceCall_OnHold())",e);}
}
//------------------------------------------------------------------------------
void __fastcall TMainFormSLS::ResumeCall(TMediaSession* ms)
{
try{
for(int i = 0; i < ControlCount; i++)
   {
   TCall_Panel* Panel = dynamic_cast<TCall_Panel*>(Controls[i]);
   if(Panel)
     if(Panel->Tag)
      if(Panel->Tag == ms->getCallTag())
        {
        if(Panel->lb)
          {
          string s = Panel->lb->Caption.c_str();
          int st = s.find(":");
          if(st != -1)
            {
            s.resize(st);
            if(MainFormSLS->lng == Lang_RU)
               s += ": Разговор ";
            else
               s += ": Conversation ";
            Panel->lb->Caption = s.c_str();
            }
          }
        Panel->SetInvisible_REM_HOLD();
        }
   }
}//try
catch(Exception& e){exsSstEXCEPTION(ofs->elt,"__PlaceCall_OnHold())",e);}
}
//------------------------------------------------------------------------------
void __fastcall TMainFormSLS::Busy_On_Outgoing_CallPanel(TMediaSession* ms)
{
try{
for(int i = 0; i < ControlCount; i++)
   {
   TCall_Panel* Panel = dynamic_cast<TCall_Panel*>(Controls[i]);
   if(Panel)
     if(Panel->Tag)
       if(Panel->Tag == ms->getCallTag())
         {
         Panel->start_time_play_sound();
         Panel->lb_1->Hide();
         Panel->set_call_state(Call_State__Busy);
         String S = Panel->lb->Caption;
         if(lng == Lang_RU)
            S += ": Абонент занят ";
         else
            S += ": Busy ";
         Panel->lb->Caption = S;
         Panel->lb->Top += 4;
         if(!Panel->get_hstry_written())
           {
           Panel->set_hstry_written(true);
           TExchBuf* buf = new TExchBuf(WM_APP_MSG_WPARAM__CALL_OUT);
           if(buf)
             {
             buf->emt   = ExchMsgType_Busy_Out;
             buf->msg   = ms->get_uniq_username();
             buf->msg_5 = ms->get_display_username();
             callin_exchlst_insert(buf);
             ::PostMessage(Handle, CALL_MSG, WM_APP_MSG_WPARAM__CALL_OUT, WM_APP_MSG_LPARAM__READLIST);
             }
           }
         }
   }
}//try
catch(Exception& e){exsSstEXCEPTION(ofs->elt,"__Busy_On_Outgoing_CallPanel()",e);}
}
//-----------------------------------------------------------------------------
bool __fastcall TMainFormSLS::get_MMI_AudioDevices()
{

/*
if(!AudioIntDll.HINST)
  {
  ofs->elt->FputEvt("\nERROR: AudioInterface.dll not found\n",1);
  return false;
  }
if(AudioIntDll.pFunc_AIC)
  (*AudioIntDll.pFunc_AIC)(&EvtLogDll);

  */
return true;

}
//----------------------------------------------------------------------------
void __fastcall TMainFormSLS::LogAudioDeviceParameters()
{
if(!ofs->elt)
   return;
int inumDevs = waveInGetNumDevs();
ofs->elt->FputEvt("\nIN Device NUM:" + inttostr(inumDevs) + "\n");

WAVEINCAPS wic;
for (int i = 0; i < inumDevs; i++)
    {
     if(!waveInGetDevCaps(i, &wic, sizeof(WAVEINCAPS)))
       {
       string s = "IN Device ID:" + inttostr(i) + ": " + string(wic.szPname) + "\n";
       ofs->elt->FputEvt(s);
       }
    }

int onumDevs = waveOutGetNumDevs();
ofs->elt->FputEvt("OUT Device NUM:" + inttostr(onumDevs) + "\n");
WAVEOUTCAPS woc;
for (int i = 0; i < onumDevs; i++)
   {
   if (!waveOutGetDevCaps(i, &woc, sizeof(WAVEOUTCAPS)))
      ofs->elt->FputEvt("OUT Device ID:" + inttostr(i) + ": " + string(woc.szPname) + "\n");
   }
}
//-----------------------------------------------------------------------------
void __fastcall TCall_Panel::Mic_Img__MouseUp(TObject *Sender, TMouseButton Button,
                                                  TShiftState Shift, int X, int Y)
{
TEventLogThread* elt = MainFormSLS->ofs->elt;
TImage* img = (TImage*)Sender;
TMediaSession* ms = MainFormSLS->Sip->sss->GetMs_by_Call_Tag(img->Tag);
if(ms)
  {
  TUdpChannel* uc = ms->getSoundChannel();
  if(uc)
    {
    if(uc->mic)
      if(uc->mic->MS == MicrophoneState_Active)
        {
        if(elt)
           elt->FputEvt("\nmic switch off");
        MainFormSLS->ImageList3->Draw(mic_img->Canvas,0,0,5,true); mic_img->Refresh();
        mic_img->Hint = "Включить микрофон";
        uc->mic->MS   =  MicrophoneState_Passive;
        uc->mic->setMute(true);
        if(get_conf_participant())
           ConferenceWin->MIC_SWITCH_OFF();
        }
      else
        {
        if(elt)
           elt->FputEvt("\nmic switch on");
        mic_img->Picture->Bitmap = MainFormSLS->mic_img_static->Picture->Bitmap; mic_img->Refresh();
        mic_img->Hint = "Выключить микрофон";
        uc->mic->MS = MicrophoneState_Active;
        uc->mic->setMute(false);
        if(get_conf_participant())
           ConferenceWin->MIC_SWITCH_ON();
        if(uc->mic->WIS == WaveInputState_ACTIVE)
          if(uc->mic->Suspended)
             uc->mic->Resume_Thread();
        }
    }
  }
}
//------------------------------------------------------------------------------
void __fastcall TCall_Panel::Cam_Img__MouseUp(TObject *Sender, TMouseButton Button,
                                                  TShiftState Shift, int X, int Y)
{
TImage* img = (TImage*)Sender;
TMediaSession* ms = MainFormSLS->Sip->sss->GetMs_by_Call_Tag(img->Tag);
if(ms)
  {
  TUdpChannel* uc = ms->getVideoChannel();
  if(uc)
    {
    if(!ms->get_transmit_video())   //Video channel exists, but video received only
      {
      MainFormSLS->StartVideo();
      ms->set_transmit_video(true); //После того как transmit video установлен, дальнейшие нажатия на cam_img приводят только к остановке трансляции или к возобновлению трансляции пакетов
      Form4->ins_vcl(uc->getChId());  //!!!Local Video. see TForm4::prepare_frame_to_send(). Если vcl empty, то не будет трансляции видео фреймов от локальной камеры
      draw_active_cam_img();
      TExchBuf* buf = new TExchBuf(WM_APP_MSG_WPARAM__NDEF);
      if(buf)
        {
        buf->emt    = ExchMsgType_Show_Remote_Video;
        buf->b1     = true;     //ShowLocalVideo on RemoteVideoScreen
        Form3->ins_exch_buf(buf);
        ::PostMessage(Form3->Handle, REMOTE_VIDEO_MSG, WM_FORM3_MSG_WPARAM__NDEF, WM_FORM3_MSG_LPARAM__NDEF);
        }
      }
    else{
      if(uc->get_video_pause())
        {
        uc->set_video_pause(false); //continue of transmission video packets
        draw_active_cam_img();
        if(uc->vscr)
          {
          if(uc->vscr->video_sending_only)
            {
            if(!Form4->Visible)
               Form4->Local_Video_Show();
            Form4->FormStyle = fsStayOnTop;
            }
          else  //send and receive video
            {
            TExchBuf* buf = new TExchBuf(WM_APP_MSG_WPARAM__NDEF);
            if(buf)
              {
              buf->emt    = ExchMsgType_Update_Remote_Video;
              buf->b1     = true;     //UpdateRemoteVideo on RemoteVideoScreen (Show LocalVideo Panel)
              Form3->ins_exch_buf(buf);
              ::PostMessage(Form3->Handle, REMOTE_VIDEO_MSG, WM_FORM3_MSG_WPARAM__NDEF, WM_FORM3_MSG_LPARAM__NDEF);
              }
            }
          }
        }  //if(uc->get_video_pause())
      else
        {
        uc->set_video_pause(true);  //pause in transmission video packets
        draw_passive_cam_img();
        if(Form4->Visible)
           Form4->Close();
        if(uc->vscr)
          if(!uc->vscr->video_sending_only)
            {
            TExchBuf* buf = new TExchBuf(WM_APP_MSG_WPARAM__NDEF);
            if(buf)
              {
              buf->emt    = ExchMsgType_Update_Remote_Video;  //UpdateRemoteVideo on RemoteVideoScreen (Hide LocalVideo Panel)
              Form3->ins_exch_buf(buf);
              ::PostMessage(Form3->Handle, REMOTE_VIDEO_MSG, WM_FORM3_MSG_WPARAM__NDEF, WM_FORM3_MSG_LPARAM__NDEF);
              }
            }
        }
      }
    }//if(uc)
  else
    Start_REINVITE_With_Video_Transmission(ms);
  } //if(ms)
}
//------------------------------------------------------------------------------
void __fastcall TCall_Panel::Start_REINVITE_With_Video_Transmission(TMediaSession* ms)
{
draw_active_cam_img();
MainFormSLS->StartVideo();
if(Form4->Visible)
   Form4->resize_block = true; 
TExchBuf* buf = new TExchBuf(WM_APP_MSG_WPARAM__VIDEOOUT);
if(buf)
  {
  TVcamPar* vcpar = new TVcamPar;
  if(vcpar)
    {
    vcpar->width  = Form4->vcam_width;
    vcpar->height = Form4->vcam_height;
    vcpar->fps    = 12;
    buf->setAddBuf(vcpar);  //!!!!!reset tag and tag_1  (all assigning after buf->setAddBuf(vcpar), setAddBuf() set tag_1 to 0)
    }
  buf->emt    = ExchMsgType_VideoOut_REINVITE;    
  buf->msg_1  = ms->get_uniq_username();
  buf->callid = ms->getCallID();
  buf->a1     = ms->get_leg_type();
  buf->tag    = Tag;
  ms->set_transmit_video(true);
  MainFormSLS->videoout_exchlst_insert(buf);
  ::PostMessage(MainFormSLS->Handle, VIDEOOUT_MSG, WM_APP_MSG_WPARAM__VIDEOOUT, WM_APP_MSG_LPARAM__READLIST);
  }
}
//------------------------------------------------------------------------------
void __fastcall TCall_Panel::_img_btn_clear(TImage* img)
{
img->Canvas->Brush->Color = clWhite;
img->Canvas->FillRect(Rect(0,0,img->Width,img->Height));
}
//------------------------------------------------------------------------------
void __fastcall TCall_Panel::draw_passive_cam_img()
{
_img_btn_clear(cam_img);
MainFormSLS->VideoCamImgList->Draw(cam_img->Canvas,0,0,0,true);
cam_img->Hint = "Включить камеру";
}
//------------------------------------------------------------------------------
void __fastcall TCall_Panel::draw_active_cam_img()
{
_img_btn_clear(cam_img);
MainFormSLS->VideoCamImgList->Draw(cam_img->Canvas,0,0,1,true);
cam_img->Hint = "Выключить камеру";
}
//------------------------------------------------------------------------------
void __fastcall TCall_Panel::Speak_Img__MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
if(SoundTool->Visible)
  {
  SoundTool->Hide();
  MainFormSLS->sound_tool = false;
  }
else
  {
  SoundTool->Left = MainFormSLS->Left + Left;
  SoundTool->Top  = MainFormSLS->Top + Top + Height + 2*Height/3;
  SoundTool->start_type = 1;
  SoundTool->Show();
  MainFormSLS->sound_tool = true;
  }
}
//------------------------------------------------------------------------------
void __fastcall TCall_Panel::Dial_Img__Mouse_Up(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
TImage* img = (TImage*)Sender;
if(img)
   MainFormSLS->Show_Panel_Dial(2,img->Tag);
          //  MainFormSLS->Show_Panel_Dial(1,img->Tag);
            //  MainFormSLS->Show_Panel_Dial(3,img->Tag);

}
//------------------------------------------------------------------------------
void __fastcall TCall_Panel::Conf_Img__Mouse_Up(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
TImage* img = (TImage*)Sender;
if(img)
  {
  if(get_conf_participant())
    if(!ConferenceWin->Visible)
      {
      ConferenceWin->Show();
      return;
      }
  if(!MainFormSLS->CC_Panel->Visible)
    {
    MainFormSLS->GCS.CC_PANEL_TYPE     = CC_PANEL_TYPE__NDEF;
    MainFormSLS->CC_Panel->Left        = 0;//MainFormSLS->RIGHT_PANEL->Left;
    MainFormSLS->CC_DrawGrid->RowCount = get_ccl_q_size();
    MainFormSLS->CC_DrawGrid->Tag      = img->Tag;
    MainFormSLS->CC_Panel->Top         = Top + Height;
    if((MainFormSLS->Panel_Chat->Top - MainFormSLS->CC_Panel->Top) > 200)
       MainFormSLS->CC_Panel->Height = MainFormSLS->Panel_Chat->Top - MainFormSLS->CC_Panel->Top;
    MainFormSLS->CC_Panel->Width = MainFormSLS->Panel1->Width;
    MainFormSLS->setAddToConfBtnState(BtnState_ACTIVE);
    MainFormSLS->CC_Panel->Show();
    }
  else
    MainFormSLS->CC_Panel->Hide();
  }
}
//------------------------------------------------------------------------------
void __fastcall TCall_Panel::Refer_img__Mouse_Up(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
TImage* img = (TImage*)Sender;
if(img)
  {
  if(!ReferWin->Visible)
    {
    ReferWin->Tag = img->Tag;   //Referred call_panel->Tag -> ReferWin->Tag -> call_panel(Refer)->ReferredCallPanelTag
    ReferWin->Top  = MainFormSLS->Top  + Top + Height + 40;
    ReferWin->Left = MainFormSLS->Left + Left;
    ReferWin->Show();
    }
  else
    {
    ReferWin->Hide();
    ReferWin->Tag = 0;
    }
  }
}
//------------------------------------------------------------------------------
void __fastcall TCall_Panel::Chat_Img__Mouse_Up(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
MainFormSLS->set_user_name_to_send(nick_name);
MainFormSLS->ComboBox1->Text = display_name.c_str();
MainFormSLS->CalledNameLbl->Caption = display_name.c_str();
MainFormSLS->FocusControl(MainFormSLS->Memo1);
MainFormSLS->Im.remote_im_client = nick_name;  //!!!
MainFormSLS->Im.curr_hstry_period = -1;
MainFormSLS->Im.set_selected_remote_user(MainFormSLS->get_user_name_to_send());
MainFormSLS->Im.load_user_history();
}
//------------------------------------------------------------------------------
void __fastcall TCall_Panel::Screen_Img__Mouse_Up(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
TDateTime dt = dt.CurrentDateTime();
if((dt - dt_activate_screen_sharing) < TDateTime(0,0,2,0))
   return;
dt_activate_screen_sharing = dt;
TImage* img = (TImage*)Sender;
if(img)
   screen_sharing_action();
}
//------------------------------------------------------------------------------
void __fastcall TCall_Panel::screen_sharing_action()
{
if(screen_sharing_active)
  {
  rdp_stop_sharing(); //ScreenSharing
  screen_sharing_active = false;
  #ifdef SCREEN_Sharing_over_rem_server
  delete_screen_sharing_structs();
  #endif
  rdp_destroy(); //ScreenSharing
  MainFormSLS->Sip->send_call_disc_out(screen_sharing_sender_call_id, false);
  if(conf_host)
     send_disconnect_screen_sharing_to_all_conf_participants();
  MainFormSLS->ImageList3->Draw(screen_img->Canvas,0,0,6,true); screen_img->Refresh();
  }
else
  {
  rdp_init(); //!!!
  screen_sharing_active = true;
  char buf[2000];
  int length_out = 0;
  rdp_start_sharing( buf, 2000, length_out); //ScreenSharing
  if(length_out >  0)
    {
    string s = string(buf);
    #ifdef SCREEN_Sharing_over_rem_server

    if(conf_host)
      if(!ccl_empty())
        {
        init_conference_screen_sharing(s); //start screen sharing for all conference participants
        MainFormSLS->ImageList3->Draw(screen_img->Canvas,0,0,8,true); screen_img->Refresh();
        return;
        }


    if(sss_rem)
      {
      TScreenSharingStruct* SSS_REM = sss_rem;
      sss_rem = NULL;
      SSS_REM->block = true;
      if(sss_loc)
         sss_loc->block = true;
      delete SSS_REM;
      }
     sss_rem = new TScreenSharingStruct(SSCT_OUT_REMOTE);
     if(sss_rem)
       {
       sss_rem->WaitResponce = true;
       sss_rem->ss_CS_T      = new TScreenSharing__CLIENT_SEND__Thread(true, sss_rem, &MainFormSLS->ofs->elt, MainFormSLS->Sip );
       sss_rem->ss_CS_T->Resume();
       sss_rem->ss_CR_T      = new TScreenSharing__CLIENT_RECV__Thread(true, MainFormSLS->Sip->ScreenSharing.IPAddr, MainFormSLS->Sip->ScreenSharing.Port, sss_rem, NULL, &MainFormSLS->ofs->elt, MainFormSLS->Sip );
       sss_rem->ss_CR_T->tag = Tag; //To find this TCall_Panel
       sss_rem->ss_CR_T->sharing_str = s;
       sss_rem->ss_CR_T->get_ip_list();
       sss_rem->ss_CR_T->modify_sharing_string_OUT();
       sss_rem->ss_CR_T->sss_nick_name   = nick_name;
       sss_rem->ss_CR_T->Resume();
       }
     if(sss_loc)
        sss_loc->block = false;
     MainFormSLS->ImageList3->Draw(screen_img->Canvas,0,0,8,true); screen_img->Refresh();
     return;
    #else
     MainFormSLS->Sip->send_ScreenSharing_INVITE(this, nick_name, s);
    #endif
    }
  }
}
//------------------------------------------------------------------------------
//--  s - ScreenSharing string key  --------------------------------------------
//--  Tag - to found this call_panel -------------------------------------------
//------------------------------------------------------------------------------
void __fastcall TCall_Panel::init_conference_screen_sharing(const string& s)
{
::EnterCriticalSection(&ccl_cs);
  deque<TConfCont>::iterator it = ccl.begin();
  while(it != ccl.end())
       (*it++).init_sss_rem(s,Tag);      //init remote TScreenSharingStruct
::LeaveCriticalSection(&ccl_cs);
}
//------------------------------------------------------------------------------
void __fastcall TConfCont::init_sss_rem(const string& s, unsigned Tag)
{
if(sss_rem)
  {
  TScreenSharingStruct* SSS_REM = sss_rem;
  sss_rem = NULL;
  SSS_REM->block = true;
  if(sss_loc)
     sss_loc->block = true;
  delete SSS_REM;
  }
sss_rem = new TScreenSharingStruct(SSCT_OUT_REMOTE);
if(sss_rem)
  {
  sss_rem->WaitResponce  = true;
  sss_rem->ss_CS_T       = new TScreenSharing__CLIENT_SEND__Thread(true, sss_rem, &MainFormSLS->ofs->elt, MainFormSLS->Sip );
  sss_rem->ss_CS_T->Resume();
  sss_rem->ss_CR_T       = new TScreenSharing__CLIENT_RECV__Thread(true, MainFormSLS->Sip->ScreenSharing.IPAddr, MainFormSLS->Sip->ScreenSharing.Port, sss_rem, NULL, &MainFormSLS->ofs->elt,  MainFormSLS->Sip );
  sss_rem->ss_CR_T->tag  = Tag; //To find this TCall_Panel
  sss_rem->ss_CR_T->conf = 1;  // TScreenSharing__CLIENT_RECV__Thread belongs to conference
  sss_rem->ss_CR_T->sharing_str = s; //string key for ScreenSharing
  sss_rem->ss_CR_T->get_ip_list();
  sss_rem->ss_CR_T->modify_sharing_string_OUT();
  sss_rem->ss_CR_T->sss_nick_name = user_name;  //To find this TConfCont
  sss_rem->ss_CR_T->Resume();
  }
}
//------------------------------------------------------------------------------
void __fastcall TConfCont::delete_screen_sharing_structs()
{
if(sss_loc)
   sss_loc->block = true;
if(sss_rem)
   sss_rem->block = true;
if(sss_loc)
  {
  delete sss_loc;
  sss_loc = NULL;
  }
if(sss_rem)
  {
  delete sss_rem;
  sss_rem = NULL;
  }
}
//---------------------------------------------------------------------------
void __fastcall TConfCont::conf_cont__create_local_connection_for_OUT_screen_sharing(unsigned call_panel_tag)
{
if(sss_loc)
  {
  TScreenSharingStruct* SSS_LOC = sss_loc;
  sss_loc        = NULL;
  SSS_LOC->block = true;
  if(sss_rem)
     sss_rem->block = true;
  delete SSS_LOC;
  }
sss_loc = new TScreenSharingStruct(SSCT_OUT_LOCAL);
if(sss_loc)
  {
  if(sss_rem)
    {
    TIPAddress addr;
    if(sss_rem->get_local_out_addr(addr))
      {
      sss_loc->ss_CS_T = new TScreenSharing__CLIENT_SEND__Thread(true, sss_loc, &MainFormSLS->ofs->elt, MainFormSLS->Sip );
      sss_loc->ss_CS_T->Resume();
      sss_loc->ss_CR_T = new TScreenSharing__CLIENT_RECV__Thread(true, addr.IPAddr, addr.Port, sss_loc, sss_rem, &MainFormSLS->ofs->elt, MainFormSLS->Sip );
      if(sss_rem)
        if(sss_rem->ss_CR_T)
           sss_rem->ss_CR_T->set_opposite_sss(sss_loc);
      sss_loc->ss_CR_T->tag = call_panel_tag; //To find this TCall_Panel
      sss_loc->ss_CR_T->Resume();
      }
    }
  }
}
//----------------------------------------------------------------------------
void __fastcall TCall_Panel::create_local_OUT_conn_and_send_INVITE_to_conference_by_user_name(const string& sdp_str, const string& user_name)
{
::EnterCriticalSection(&ccl_cs);
  if(!ccl.empty())
    {
    deque<TConfCont>::iterator it = ccl.begin();
    while(it != ccl.end())
         {
         if((*it).user_name == user_name)
           {
           (*it).conf_cont__create_local_connection_for_OUT_screen_sharing(Tag);
           MainFormSLS->Sip->send_ScreenSharing_INVITE_ToConference(*it, sdp_str);
           break;
           }
         it++;
         }
    }
::LeaveCriticalSection(&ccl_cs);
}
//------------------------------------------------------------------------------
void __fastcall TCall_Panel::send_disconnect_screen_sharing_to_all_conf_participants()
{
deque<TConfCont> ccl_t;
get_ccl_copy__with_clear_screen_sharing_call_ids(ccl_t);          //get copy of conference participants list before start sending call disconnect
while(!ccl_t.empty())
     {
     TConfCont ConfCont = ccl_t.front();
     ccl_t.pop_front();
     if(!ConfCont.screen_sharing_sender_call_id.empty())
        MainFormSLS->Sip->send_call_disc_out(ConfCont.screen_sharing_sender_call_id, false);
     }
}
//-------------------------------------------------------------------------------
void __fastcall TMainFormSLS::setAddToConfBtnState(BtnState BS)
{
AddToConfBtnState = BS;
int FOREGROUND;
switch(BS){
       case BtnState_ACTIVE:   FOREGROUND = FOREGR_ACTIVE_GREEN;  break;
       case BtnState_FOCUSED:  FOREGROUND = FOREGR_FOCUSED_GREEN; break;
       case BtnState_PRESSED:  FOREGROUND = FOREGR_PRESSED_GREEN; break;
       case BtnState_INACTIVE: FOREGROUND = FOREGR_ACTIVE_GREEN;  break; //надо сменить на FOREGR_INACTIV
       default: FOREGROUND = FOREGR_ACTIVE_GREEN;  break;
       }
TRBitMap rbmp(180, 30, CC_Panel->Color, FOREGROUND);
CC_Img->Canvas->Draw(0,0, rbmp.bmp);
AnsiString S = "Добавить в разговор";
int tw = CC_Img->Canvas->TextWidth(S);
int th = CC_Img->Canvas->TextHeight(S);
int text_left = CC_Img->Width/2 - tw/2;
int text_top  = CC_Img->Height/2   - th/2;
if(BS == BtnState_PRESSED)
   text_top += 1;
CC_Img->Canvas->Brush->Color = (TColor)FOREGROUND;
CC_Img->Canvas->TextOut(text_left, text_top, S);
}
//------------------------------------------------------------------------------
void __fastcall TGroupChatStruct::set_CreateGroupChat_BtnState(TImage* CC_Img, BtnState BS)
{
__CreateGroupChat_BtnState = BS;
int FOREGROUND;
switch(BS){
       case BtnState_ACTIVE:   FOREGROUND = FOREGR_ACTIVE_BLUE;  break;
       case BtnState_FOCUSED:  FOREGROUND = FOREGR_FOCUSED_BLUE; break;
       case BtnState_PRESSED:  FOREGROUND = FOREGR_FOCUSED_BLUE; break;
       case BtnState_INACTIVE: FOREGROUND = FOREGR_ACTIVE_BLUE;  break; //надо сменить на FOREGR_INACTIV
       default: FOREGROUND = FOREGR_ACTIVE_BLUE;  break;
       }
TRBitMap rbmp(180, 30, clSilver, FOREGROUND);
CC_Img->Canvas->Draw(0,0, rbmp.bmp);
AnsiString S = "Создать группу";
int tw = CC_Img->Canvas->TextWidth(S);
int th = CC_Img->Canvas->TextHeight(S);
int text_left = CC_Img->Width/2 - tw/2;
int text_top  = CC_Img->Height/2   - th/2;
if(BS == BtnState_PRESSED)
   text_top += 1;
CC_Img->Canvas->Brush->Color = (TColor)FOREGROUND;
CC_Img->Canvas->TextOut(text_left, text_top, S);
}
//------------------------------------------------------------------------------
void __fastcall TMainFormSLS::Refresh_AddToConfBtnState()
{
if(GCS.CC_PANEL_TYPE == CC_PANEL_TYPE__GROUP_CREATE)
  {
  if(GCS.get_CreateGroupChat_BtnState() != BtnState_ACTIVE)
     GCS.set_CreateGroupChat_BtnState(CC_Img, BtnState_ACTIVE);
  }
else
  {
  if(AddToConfBtnState != BtnState_ACTIVE)
     setAddToConfBtnState(BtnState_ACTIVE);
  }
}
//-----------------------------------------------------------------------------
void __fastcall TCall_Panel::conference_exit(TMediaSession* ms_to_delete)
{
if(conf_creator != Tag) //Conference Creator
  {
  TMediaSession* ms_creator = NULL;
  if(conf_creator != -1)
     ms_creator = MainFormSLS->Sip->sss->GetMs_by_Call_Tag(conf_creator);
  if(ms_creator)
    _delete_conference_participant(ms_to_delete, ms_creator);
  else
    _delete_conference_participant(ms_to_delete);   //Media session of conference CREATOR deleted already. This passsive participant. Operate with ConferenceWin only
  }
else    //if deleted conference creator
  {
  TMediaSession* ms_creator = NULL;
  if(conf_creator != -1)
     ms_creator = MainFormSLS->Sip->sss->GetMs_by_Call_Tag(conf_creator);
  _delete_conference_participant(ms_to_delete, ms_creator);
  }
}
//------------------------------------------------------------------------------
void __fastcall TCall_Panel::_delete_conference_participant(TMediaSession* ms_party,TMediaSession* ms_creator)
{
if(ms_party)
  {
  TUdpChannel* uc_creator = NULL;
  if(ms_creator)
     uc_creator = ms_creator->getSoundChannel();
  TUdpChannel* uc_party   = ms_party->getSoundChannel();
  if(uc_party)
    {
    if(uc_creator)
      {
      if(uc_creator->mic)
        uc_creator->mic->acqs.delete_channel_from_conference(uc_party->getChId());
      uc_creator->Disconnect(uc_party);
      }
    if(uc_party->mic)
       uc_party->mic->setConf(false);
    uc_party->DisconnectAllMyConnections();
    vector<int> v;
    uc_party->getAllConnectionsToMe(v);
    int sz = v.size();
    if(sz)
      for(int i=0;i < sz;i++)
         {
         TUdpChannel* cntd_ch = MainFormSLS->Sip->ucs->getUdpChannel(v[i]);
         if(cntd_ch)
            cntd_ch->Disconnect(uc_party);
         }
    }
  TCall_Panel* panel_conf_creator = MainFormSLS->get_Call_Panel_By_Tag(conf_creator);
  if(panel_conf_creator)
    {
    string user = ms_party->get_uniq_username();
    TContact contact(-1);
    if(MainFormSLS->Sip->Contacts.get_contact_copy_by_user_name(contact,user))
      {
      TConfCont ConfCont(contact.get_id());
      ConfCont.user_name      = contact.name;
      ConfCont.call_panel_tag = ms_party->getCallTag(); //Интересует именно ms_party call_tag. Если ms_party->call_tag == ms_creator->call_tag и соответственно ConferenceWin->Tag, то надо менять ConferenceWin->Tag
      panel_conf_creator->del_ccl_q_contact(ConfCont);
      panel_conf_creator->del_ccl_contact(ConfCont);

      deque<TConfCont> ccl_t;
      panel_conf_creator->get_ccl_copy(ccl_t);          //get copy of conference participants list before add new contact
      MainFormSLS->SendConference_INFO_About_DELETED_Participant_to_ALL_participants(panel_conf_creator->get_leg_type(), ConfCont, ccl_t); //Send INFO msg to all answered conference participants (excluding conference_creator and new participant) about deleted participant
      MainFormSLS->Del_Participant_From_ConfCreator_Window(ConfCont);
      }
    else
      {
      TConfCont ConfCont(user);
      ConfCont.call_panel_tag = ms_party->getCallTag();
      panel_conf_creator->del_ccl_q_contact(ConfCont);
      panel_conf_creator->del_ccl_contact(ConfCont);

      deque<TConfCont> ccl_t;
      panel_conf_creator->get_ccl_copy(ccl_t);          //get copy of conference participants list before add new contact
      MainFormSLS->SendConference_INFO_About_DELETED_Participant_to_ALL_participants(panel_conf_creator->get_leg_type(), ConfCont, ccl_t); //Send INFO msg to all answered conference participants (excluding conference_creator and new participant) about deleted participant
      MainFormSLS->Del_Participant_From_ConfCreator_Window(ConfCont);
      if(!panel_conf_creator->get_ccl_size())
        return;
      }
    if(!panel_conf_creator->get_ccl_size())
      {
      string s = panel_conf_creator->lb->Caption.c_str();
      int st = s.find(": ");
      if(st != -1)
         s.resize(st);
      s += COLON + WS + "Разговор ";
      panel_conf_creator->lb->Caption = s.c_str();
      panel_conf_creator->set_call_state(Call_State__Answer);
      }
    } // if(panel_conf_creator)
  } //  if(ms_party)
}
//------------------------------------------------------------------------------
void __fastcall TCall_Panel::_delete_conference_participant(TMediaSession* ms_party)
{
string user = ms_party->get_uniq_username();
TContact contact(-1);
if(MainFormSLS->Sip->Contacts.get_contact_copy_by_user_name(contact,user))
  {
  TConfCont ConfCont(contact.get_id());
  ConfCont.user_name      = contact.name;
  ConfCont.call_panel_tag = ms_party->getCallTag();
  MainFormSLS->Del_Participant_From_ConfCreator_Window(ConfCont);
  }
else
  {
  TConfCont ConfCont(user);
  ConfCont.call_panel_tag = ms_party->getCallTag();
  MainFormSLS->Del_Participant_From_ConfCreator_Window(ConfCont);
  }
}
//------------------------------------------------------------------------------
void __fastcall TCall_Panel::DiscImg_OutgoingCall_Panel_MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
TImage* img       = (TImage*)Sender;
check_on_conf_participation();
check_hidden_remote_video();
TMediaSession* ms = MainFormSLS->Sip->sss->GetMs_by_Call_Tag(img->Tag);
disconnect_outgoing_call(ms,false);  //check if(ms) inside of func ; false means that  disconnect_incoming_call() initialized not from rcvd Bye fron parallel phone
}
//----------------------------------------------------------------------------
void __fastcall TCall_Panel::DiscImg_IncomingCall_Panel_MouseUp(TObject *Sender, TMouseButton Button,
                                                  TShiftState Shift, int X, int Y)
{
TImage* img       = (TImage*)Sender;
check_on_conf_participation();
check_hidden_remote_video();
TMediaSession* ms = MainFormSLS->Sip->sss->GetMs_by_Call_Tag(img->Tag);
disconnect_incoming_call(ms,false); //check if(ms) inside of func ; false means that  disconnect_incoming_call() initialized not from rcvd Bye from parallel phone
}
//----------------------------------------------------------------------------
void __fastcall TCall_Panel::check_on_conf_participation()
{
if(conf_participant)
  {
  conf_participant = false;
  TConfExchBlock* ExchBlock = new TConfExchBlock;
  if(ExchBlock)
    {
    ExchBlock->conf_evnt = ConfEvnt_DeactivateWindow;
    ConferenceWin->ins_exch_buf(ExchBlock);
    ::PostMessage(ConferenceWin->Handle, CONFERENCE_MSG, WM_CONFERENCE_MSG_WPARAM__NDEF, WM_CONFERENCE_MSG_LPARAM__NDEF);
    }
  }
}
//----------------------------------------------------------------------------
void __fastcall TCall_Panel::check_hidden_remote_video()
{
if(MainFormSLS->Image_RemoteVideo->Visible)
 if(MainFormSLS->Image_RemoteVideo->Tag == Tag)
   {
   MainFormSLS->Image_RemoteVideo->Visible = false;
   MainFormSLS->Image_RemoteVideo->Tag     = 0;
   }
}
//-----------------------------------------------------------------------------
void __fastcall TCall_Panel::disconnect_outgoing_call(TMediaSession* ms, bool rcvd_from_send_to_pph)
{
if(ms)
  {
  switch(call_state){
         case Call_State__Conference:
              conference_exit(ms);
              break;
         case Call_State__NotAcceptable:
              MainFormSLS->PlaySound_Free();
              break;
         case Call_State__Busy:
              MainFormSLS->PlaySound_Free();
              break;
         }

  string callid = ms->getCallID();
  if(MainFormSLS->ofs->elt)
     MainFormSLS->ofs->elt->FputEvt("\nDISCONNECT callid " + callid);
  MainFormSLS->Sip->send_call_disc_out(callid, ms->get_ms_parallel_phone());
  MainFormSLS->Sip->del_CLD_tc(ms->get_uniq_username());
  if(!ms->get_ms_hstry_written())
    {
    tstmps.get_conv_duration();
    outgoing_call_disc_out_hstry(ms->get_uniq_username(), ms->get_display_username());
    }
  MainFormSLS->Sip->sss->EraseMediaSession(out_pref + callid); //ms deleted !!!
  }
MainFormSLS->HIDE_DPW(Tag); // Скрыть DialPad Window
disconnect_screen_sharing();
if(!rcvd_from_send_to_pph)   //!!!!! see comment for disconnect_parallel_phone()
   disconnect_parallel_phone();
MainFormSLS->push_req_to_del_call_panel(Tag);
#ifdef SIP_Video
if(Form4->Visible)
   Form4->Hide();
if(Form3->Visible)
   Form3->Hide();
Form3->call_in_progress = false;
if(Form4->devID != -1)
  {
  vcam_stop_device(Form4->devID);
  Form4->devID = -1;
  }
#endif
if(MainFormSLS->Panel_Dial->Visible)
   MainFormSLS->Panel_Dial->Hide();
}
//----------------------------------------------------------------------------
void __fastcall TCall_Panel::disconnect_screen_sharing()
{
if(screen_sharing_active)
  {
  screen_sharing_active = false;
  rdp_destroy();
  if(!screen_sharing_sender_call_id.empty())
    {
     MainFormSLS->Sip->send_call_disc_out(screen_sharing_sender_call_id, false);
     screen_sharing_sender_call_id.clear();
    }
  if(conf_host)
     send_disconnect_screen_sharing_to_all_conf_participants();
  }
}
//------------------------------------------------------------------------------
//---- !!! Если в  disconnect_outgoing_call() поставить false, то будет --------
//----  бесконечный рекурсивный вызов ------------------------------------------
//---- (disconnect_outgoing_call() вызывает disconnect_parallel_phone()) -------
//------------------------------------------------------------------------------
void __fastcall TCall_Panel::disconnect_parallel_phone()
{
if(connected_to_pph)
  {
  connected_to_pph = false;
  TMediaSession* ms = MainFormSLS->Sip->sss->GetMsOut_by_Callid(callid_pph);
  if(lt == Lt_Out)
    {
    if(ms)
      {
      string callid = ms->getCallID();
      if(MainFormSLS->ofs->elt)
         MainFormSLS->ofs->elt->FputEvt("\nDISCONNECT callid " + callid);
      if(MainFormSLS->PPS)
        if(MainFormSLS->PPS->uac_pph)
          {
          TOutputSipBuf* ospb = MainFormSLS->Sip->prepare_Disc_Out_Req(callid);
          if(ospb)
            {
            ospb->parallel_phone = true;
            MainFormSLS->PPS->uac_pph->setQueue(ospb);
            MainFormSLS->Sip->updateSentQueue_1(ospb);
            }
          }
      }
    }
  else
    disconnect_outgoing_call(ms,true);  //check ms inside this func
  }
}
//------------------------------------------------------------------------------
void __fastcall TCall_Panel::Conn_Img_MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
TSip* Sip = MainFormSLS->Sip;
TMediaSession* ms = Sip->sss->GetMs_by_Call_Tag(Tag); //Get MediaSession of previously sent INVITE
if(ms)
  {
  TOutputSipBuf* ospb = new TOutputSipBuf;
  if(ospb)
    {
    TCall_Panel* call_panel = MainFormSLS->get_Call_Panel_By_Tag(referred_call_panel_tag);
    if(call_panel)
      {
      string s;
      if(MainFormSLS->lng == Lang_RU)
         s = WS + "Переадресация на " + ms->get_uniq_username();
      else
         s = WS + "Call is being transferred to " + ms->get_uniq_username();
      call_panel->lb_1->Top = call_panel->lb->Top + call_panel->lb_1->Height;
      call_panel->lb_1->Caption = s.c_str();
      call_panel->lb_1->Visible = true;
      }

    ospb->setsls(SPS_REFER_REQ);
    ospb->requestline = "REFER"        + WS + "sip:" + ms->get_uniq_username() + "@" + Sip->Account.get_domain() + WS + SipVers + crlf;
    ospb->CallID      = "Call-ID:"     + WS + ms->getCallID() + crlf;
    ospb->ReferredBy  = "Referred-By:" + WS + "<sip:" + Sip->Account.get_user_name() + "@" + Sip->Account.get_domain() + ">" + crlf;
    ospb->ReferTo     = PrepareReferTo_Attendant();
    Prepare_To_From_Contact_CSeq__ForRefer(ospb,ms);
    Sip->Prepare_Via_Header_With_Branch(ospb);
    Sip->prepareMaxForwards(70,ospb);
    Sip->prepareUserAgent(ospb);
    Sip->prepareContentLength_0(ospb);

    ospb->s = ospb->requestline +
    ospb->via                   +
    ospb->maxforwards           +
    ospb->Contact               +
    ospb->To                    +
    ospb->from                  +
    ospb->CallID                +
    ospb->cseq                  +
    ospb->UserAgent             +
    ospb->ReferTo               +
    ospb->ReferredBy            +
    ospb->ContentLength;

    ospb->set_req_to_delete();
    Sip->SetOutQueue(ospb);
    }
   }
}
//----------------------------------------------------------------------------
void __fastcall TCall_Panel::outgoing_call_disc_out_hstry(const string& user_name, const string& user_display_username)
{
if(!hstry_written)
  {
  hstry_written = true;
  TExchBuf* buf = new TExchBuf(WM_APP_MSG_WPARAM__CALL_OUT);
  if(buf)
    {
    if((call_state == Call_State__Answer) || (call_state == Call_State__Conference))
      {
       buf->emt   = ExchMsgType_Bye_Out;
       if(tstmps.conv_duration.get_ready())
          buf->msg_1 = tstmps.conv_duration.s_duration;
      }
    else
       buf->emt = ExchMsgType_Cancel_Out;
    buf->msg   = user_name;
    buf->msg_5 = user_display_username;
    MainFormSLS->callin_exchlst_insert(buf);
    ::PostMessage(MainFormSLS->Handle, CALL_MSG, WM_APP_MSG_WPARAM__CALL_OUT, WM_APP_MSG_LPARAM__READLIST);
    }
  }
}
//------------------------------------------------------------------------------
void __fastcall TCall_Panel::incoming_call_disc_out_hstry(const string& user_name, const string& display_user_name)
{
if(!hstry_written)
  {
  hstry_written = true;
  TExchBuf* buf = new TExchBuf(WM_APP_MSG_WPARAM__CALL_IN);
  if(buf)
    {
    if((call_state == Call_State__Answer) || (call_state == Call_State__Conference))
      {
       buf->emt   = ExchMsgType_Bye_In;
       if(tstmps.conv_duration.get_ready())
          buf->msg_1 = tstmps.conv_duration.s_duration;
      }
    buf->msg   = user_name;
    buf->msg_5 = display_user_name;
    MainFormSLS->callin_exchlst_insert(buf);
    ::PostMessage(MainFormSLS->Handle, CALL_MSG, WM_APP_MSG_WPARAM__CALL_IN, WM_APP_MSG_LPARAM__READLIST);
    }
  }
}
//------------------------------------------------------------------------------
void __fastcall TCall_Panel::disconnect_incoming_call(TMediaSession* ms, bool rcvd_from_send_to_pph)
{
if(ms)
  {
  if(call_state == Call_State__Conference)
     conference_exit(ms);
  string callid = ms->getCallID();
  if(MainFormSLS->ofs->elt)
     MainFormSLS->ofs->elt->FputEvt("\nDISCONNECT callid " + callid);
  MainFormSLS->Sip->send_call_disc_in(callid);
  if(!ms->get_ms_hstry_written())
    {
    tstmps.get_conv_duration();
    incoming_call_disc_out_hstry(ms->get_uniq_username(), ms->get_display_username());
    }
  MainFormSLS->Sip->sss->EraseMediaSession(in_pref + callid); //ms deleted !!!
  }
MainFormSLS->HIDE_DPW(Tag);
disconnect_screen_sharing();
if(!rcvd_from_send_to_pph)  //!!!!!
   disconnect_parallel_phone();
MainFormSLS->push_req_to_del_call_panel(Tag);
#ifdef SIP_Video
if(Form4->Visible)
   Form4->Hide();
if(Form3->Visible)
   Form3->Hide();
Form3->call_in_progress = false;
if(Form4->devID != -1)
  {
  vcam_stop_device(Form4->devID);
  Form4->devID = -1;
  }
#endif
if(MainFormSLS->Panel_Dial->Visible)
   MainFormSLS->Panel_Dial->Hide();
}
//-- --------------------------------------------------------------------------
void __fastcall TMainFormSLS::push_req_to_del_call_panel(int a)
{
if(a) //!!!!!
  cps.req_to_del_panel.push_back(a);
}
//-----------------------------------------------------------------------------
void __fastcall TMainFormSLS::DrawGrid1MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
Im.remote_im_client.clear(); //!!!
if(Button == mbLeft)
  {
  if(ContactMenu->Visible)
     ContactMenu->Hide();
  }
else if(Button == mbRight)
  {
  int ACol,ARow;
  DrawGrid1->MouseToCell(X,Y,ACol,ARow);
  if(ACol==-1)return;
  if(ARow==-1)return;
  DrawGrid1->Row = ARow;
  }
}
//---------------------------------------------------------------------------
/*
void __fastcall TMainFormSLS::prepare_to_show_1(TContactMenu* ContactMenu)
{
TRect Rect = DrawGrid1->CellRect(0,DrawGrid1->Row);
ContactMenu->Left = Left + DrawGrid1->Left + Rect.Left + DrawGrid1->Width/2; //X + 10;//Rect.Width()/2;
int clientTop  = Height - ClientHeight;
int AbsY = Top + clientTop + Panel2->Top + TabSheet1->Top + DrawGrid1->Top + Rect.Top + DrawGrid1->RowHeights[0]/2;
if((AbsY + clientTop/2 + ContactMenu->Height) < Screen->Height)
  ContactMenu->Top = AbsY;
else
  ContactMenu->Top = AbsY - ContactMenu->Height;
if(ContactMenu->Selected_CT == ContactType_CLIENT)
   ContactMenu->DrawGrid1->RowCount = 7;
else if(ContactMenu->Selected_CT == ContactType_DIVISION)
   ContactMenu->DrawGrid1->RowCount = 1;
ContactMenu->DrawGrid1->Height = ContactMenu->DrawGrid1->DefaultRowHeight * ContactMenu->DrawGrid1->RowCount + ContactMenu->DrawGrid1->DefaultRowHeight/2; // - 10;
ContactMenu->Panel1->Height    = ContactMenu->DrawGrid1->Height + 2*ContactMenu->DrawGrid1->DefaultRowHeight;
ContactMenu->Height            = ContactMenu->Panel1->Height - 33;
ContactMenu->Show();
}
*/
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::prepare_to_show(TContactMenu* ContactMenu,int X,int Y,int ACol,int ARow)
{
TRect Rect = DrawGrid1->CellRect(ACol,ARow);
ContactMenu->Left = Left + DrawGrid1->Left + Rect.Left + X + 10;
ContactMenu->Top = DrawGrid1->ClientOrigin.y + Y;

if(ContactMenu->Selected_CT == ContactType_CLIENT)
  ContactMenu->DrawGrid1->RowCount = 10;
else if(ContactMenu->Selected_CT == ContactType_GROUP)
  ContactMenu->DrawGrid1->RowCount = 3;
else if(ContactMenu->Selected_CT == ContactType_DIVISION)
  ContactMenu->DrawGrid1->RowCount = 1;
ContactMenu->DrawGrid1->Height = ContactMenu->DrawGrid1->DefaultRowHeight * ContactMenu->DrawGrid1->RowCount + ContactMenu->DrawGrid1->DefaultRowHeight/2; // - 10;
ContactMenu->Panel1->Height    = ContactMenu->DrawGrid1->Height + 2*ContactMenu->DrawGrid1->DefaultRowHeight;
ContactMenu->Height            = ContactMenu->Panel1->Height - 33;
ContactMenu->Show();
}
//---------------------------------------------------------------------------
/*
bool __fastcall TMainFormSLS::check_contact_unselect(TContactMenu* ContactMenu,TMouseButton Button,int ACol,int ARow)
{
if(ACol==-1)
  {
  if(Button == mbRight)
     prepare_to_show_1(ContactMenu);
  return true;
  }
if(ARow==-1)
  {
  if(Button == mbRight)
     prepare_to_show_1(ContactMenu);
   return true;
  }
return false;
}
*/
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::DrawGrid1MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
if(Panel_Dial->Visible)
   Panel_Dial->Hide();
int ACol,ARow;
DrawGrid1->MouseToCell(X,Y,ACol,ARow);
if(ACol == -1)return;
if(ARow == -1)return;
//if(check_contact_unselect(ContactMenu,Button,ACol,ARow))
//  return;
TContact* Contact = NULL;
if(Button == mbLeft)
  {
  if(Sip->Contacts.get_sorted_by_full_name())
     Contact = Sip->Contacts.get_contact_by_full_name(ARow);
  else
     Contact = Sip->Contacts.get_contact_by_row(ARow,true);
  if(Contact)
    {
    if(Contact->CT == ContactType_DIVISION)
      {
      if(Contact->get_open())
         Sip->Contacts.set_division_visible(Contact->get_id(), DrawGrid1, false);   //Close visible of underlying divisions and clients
      else
         Sip->Contacts.set_division_visible(Contact->get_id(), DrawGrid1, true);
      user_name_to_send.clear();
      set_IM_to_chat_participants(false);
      AnsiString S;
      ComboBox1->Text = S;
      CalledNameLbl->Caption = S;
      DrawGrid1->Repaint();
      return;
      }
    if(Contact->get_missed_calls())
      {
      Sip->Contacts.reset_missed_calls(Contact->name);
      DrawGrid1->Repaint();
      Im.MCS.clear_im_sender_name(Contact->name);
      Sip->Contacts.LCS.DeleteMissedName(Contact->name);
      if(Sip->Contacts.LCS.MissedNameEmpty())
         TrayMessage_Ext(NIM_MODIFY,"Contact",2);
      }
    if(CC_Panel->Visible)
      {
      if(GCS.CC_PANEL_TYPE == CC_PANEL_TYPE__GROUP_CREATE)
        {
        if(Contact->CT == ContactType_CLIENT)
          {
          TGroupName GName;
          GName.name      = Contact->name;
          GName.s_full_name = Contact->full_name;
          if(!GCS.InQueue(GName))
            {
            GCS.Push(GName);
            CC_DrawGrid->RowCount = GCS.Size();
            CC_DrawGrid->Refresh();//Repaint();
            }
          }
        }
      else
        {
        TCall_Panel* Panel = get_Call_Panel_By_Tag(CC_DrawGrid->Tag);
        if(Panel)
          {
          TConfCont ConfCont(Contact->get_id());
          ConfCont.user_name = Contact->name;
          if(!Panel->is_ccl_q_contact(ConfCont)) //not yet in queue to the conference
            {
            Panel->add_ccl_q_contact(ConfCont);
            CC_DrawGrid->Repaint();
            }
          }
        }
      }
    else if((SCP)&&(SCP->Visible))         //TServConf_Panel
      {
      TContact* contact = new TContact(SCP->conf_contacts.get_next_contact_id());
      if(contact)
        {
        contact->copy(*Contact);
        SCP->conf_contacts.add_contact(contact,SCP->dg1,false);
        SCP->dg1->Repaint();
        }
      }
    else if(ReferWin->Visible)
      {
      ReferWin->refer_name          = Contact->name;
      ReferWin->EditBox->Edit->Text = Contact->full_name.c_str();
      }
    else
      {
      user_name_to_send      = Contact->name;
      if(Contact->CT == ContactType_GROUP)
         group_chat_selected(Contact->group_full_name);
       else
        {
        set_IM_to_chat_participants(false);
        ComboBox1->Text        = Contact->full_name.c_str();
        CalledNameLbl->Caption = Contact->full_name.c_str();
        CalledNameLbl->ShowHint = false;
        }
      if(Im.get_selected_remote_user() != user_name_to_send)
        {
        Im.curr_hstry_period = -1;
        Im.set_selected_remote_user(user_name_to_send);
        Im.load_user_history();
        }
      else
        {
        if((IM_DrawGrid->TopRow + IM_DrawGrid->VisibleRowCount) <= (IM_DrawGrid->RowCount - 1))
          {
          Im.curr_hstry_period = -1;
          Im.set_selected_remote_user(user_name_to_send);
          Im.load_user_history();
          }
        }
      if(ProfileForm)
        {
        if(ProfileForm->TYPE == 1)       //View Contact Data
           Open_Profile(false);          //without new TProfileForm
        else if(ProfileForm->TYPE == 3)  //EditProfile
           Edit_Profile(false);       //without new TProfileForm
        }
      }
    } //if(Contact)
  }
else if(Button == mbRight)
  {
  if(Sip->Contacts.get_sorted_by_full_name())
     Contact = Sip->Contacts.get_contact_by_full_name(ARow);
  else
     Contact = Sip->Contacts.get_contact_by_row(ARow,true);
  if(Contact)
    {
    if(Contact->CT == ContactType_DIVISION)
      {
      user_name_to_send.clear();
      set_IM_to_chat_participants(false);
      AnsiString S;
      ComboBox1->Text          = S;
      CalledNameLbl->Caption   = S;
      ContactMenu->Selected_CT = Contact->CT;
      prepare_to_show(ContactMenu,X,Y,ACol,ARow);
      return;
      }
    user_name_to_send        = Contact->name;
    if(Contact->CT == ContactType_GROUP)
      group_chat_selected(Contact->group_full_name);
    else
      {
      set_IM_to_chat_participants(false);
      ComboBox1->Text          = Contact->full_name.c_str();
      CalledNameLbl->Caption   = Contact->full_name.c_str();
      }
   // if(Contact->CT != ContactType_GROUP)
      ContactMenu->Selected_CT = Contact->CT;
    if(Im.get_selected_remote_user() != user_name_to_send)
      {
      Im.curr_hstry_period = -1;
      Im.set_selected_remote_user(user_name_to_send);
      Im.load_user_history();
      }
    }
  prepare_to_show(ContactMenu,X,Y,ACol,ARow);
  }
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::group_chat_selected(const string& group_full_name)
{
set_IM_to_chat_participants(true);
ComboBox1->Text        = group_full_name.c_str();
CalledNameLbl->Caption = group_full_name.c_str();
string hint = create_hint(group_full_name);
CalledNameLbl->Hint = hint.c_str(); //Contact->group_full_name.c_str();
CalledNameLbl->ShowHint = true;
}
//---------------------------------------------------------------------------
string  __fastcall TMainFormSLS::create_hint(const string& str)
{
string s = str;
s += ",";
queue<string> q;
while(!s.empty())
     {
     int len = s.length();
     int st  = s.find(",");
     if(st == 0)
       {
       st++;
       if(st < len)
         {
         s  = s.substr(st,len - st);
         st = s.find(",");
         }
       else
         break;
       }
     if(st != -1)
        q.push(s.substr(0,st) + "\n");
     if(st < len)
        s = s.substr(st,len - st);
     }
s.clear();
while(!q.empty())
     {
     s += q.front();
     q.pop();
     }
return s;
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::ComboBox1KeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
if(Shift.Contains(ssCtrl))
   return;
string s = ComboBox1->Text.c_str();
if(isdigit(Key)||isalpha(Key))
   user_name_to_send = s;
else if(Key == 13)//Enter
 {
 if(check_on_phone_number(s))
   {
   string s = ComboBox1->Text.c_str();
   user_name_to_send = s;
   AudioCall();
   return;
   }

 TContact* Contact = NULL;
 if(Sip->Contacts.get_sorted_by_full_name())
     Contact = Sip->Contacts.get_contact_by_full_name(DrawGrid1->Row);
 else
     Contact = Sip->Contacts.get_contact_by_row(DrawGrid1->Row,false);
 if(Contact)
   {
   user_name_to_send      = Contact->name;
   if(Contact->CT == ContactType_GROUP)
      set_IM_to_chat_participants(true);
   else
      set_IM_to_chat_participants(false);
   ComboBox1->Text        = Contact->full_name.c_str();
   CalledNameLbl->Caption = Contact->full_name.c_str();
   AudioCall();
   }
 }
}
//---------------------------------------------------------------------------
bool __fastcall TMainFormSLS::check_on_phone_number(const string& s)
{
int len = s.length();
if(!len)return false;
for(int i=0;i < len;i++)
    if(!isdigit(s[i]))
      if(s[i] != '*')
        if(s[i] != '#')
          return false;

return true;
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::FormClick(TObject *Sender)
{
if(ContactMenu->Visible)
   ContactMenu->Hide();
}
//---------------------------------------------------------------------------

void __fastcall TMainFormSLS::PageControl1MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
if(ContactMenu->Visible)
   ContactMenu->Hide();
}
//---------------------------------------------------------------------------

void __fastcall TMainFormSLS::TabSheet1MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
if(ContactMenu->Visible)
   ContactMenu->Hide();
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::DrawGrid1KeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
TDrawGrid* DG = (TDrawGrid*)Sender;
if(!DrawGrid1)return;
TContact* Contact = NULL;
switch(Key){
      case 33: //PageUp
      case 34: //PageDown
      case 38: //Up
      case 40:{//Down
              if(Sip->Contacts.get_sorted_by_full_name())
                 Contact = Sip->Contacts.get_contact_by_full_name(DG->Row);
              else
                 Contact = Sip->Contacts.get_contact_by_row(DG->Row,true);
              if(Contact)
                {
                if(Contact->CT == ContactType_DIVISION)
                  {
                  user_name_to_send.clear();
                  set_IM_to_chat_participants(false);
                  AnsiString S;
                  ComboBox1->Text = S;
                  CalledNameLbl->Caption = S;
                  }
                else
                  {
                  user_name_to_send      = Contact->name;
                  if(Contact->CT == ContactType_GROUP)
                    group_chat_selected(Contact->group_full_name);
                  else
                    {
                    set_IM_to_chat_participants(false);
                    ComboBox1->Text        = Contact->full_name.c_str();
                    CalledNameLbl->Caption = Contact->full_name.c_str();
                    }
                  if(ProfileForm)
                    {
                    if(ProfileForm->TYPE == 1)//View Contact Data
                       Open_Profile(false);
                    else if(ProfileForm->TYPE == 3)  //EditProfile
                       Edit_Profile(false);       //without new TProfileForm
                    }
                  }
                }
              break;
              }
      case 35: //End
      case 36:{ //Home
             if(Shift.Contains(ssCtrl))
               {
               if(Sip->Contacts.get_sorted_by_full_name())
                  Contact = Sip->Contacts.get_contact_by_full_name(DG->Row);
               else
                  Contact = Sip->Contacts.get_contact_by_row(DG->Row,true);
               if(Contact)
                 {
                 if(Contact->CT == ContactType_DIVISION)
                   {
                   user_name_to_send.clear();
                   set_IM_to_chat_participants(false);
                   AnsiString S;
                   ComboBox1->Text = S;
                   CalledNameLbl->Caption = S;
                   }
                 else
                   {
                   user_name_to_send      = Contact->name;
                   if(Contact->CT == ContactType_GROUP)
                     group_chat_selected(Contact->group_full_name);
                   else
                     {
                     set_IM_to_chat_participants(false);
                     ComboBox1->Text        = Contact->full_name.c_str();
                     CalledNameLbl->Caption = Contact->full_name.c_str();
                     }
                   if(ProfileForm)
                     {
                     if(ProfileForm->TYPE == 1)//View Contact Data
                        Open_Profile(false);
                     else if(ProfileForm->TYPE == 3)  //EditProfile
                        Edit_Profile(false);       //without new TProfileForm
                     }
                   }
                 }
               }
             break;
             }
      case 13:{ //Enter
              if(Sip->Contacts.get_sorted_by_full_name())
                 Contact = Sip->Contacts.get_contact_by_full_name(DG->Row);
              else
                 Contact = Sip->Contacts.get_contact_by_row(DG->Row,true);
              if(Contact)
                {
                if(Contact->CT == ContactType_DIVISION)
                  {
                  if(Contact->get_open())
                     Sip->Contacts.set_division_visible(Contact->get_id(), DrawGrid1, false);   //Close visible of underlying divisions and clients
                  else
                     Sip->Contacts.set_division_visible(Contact->get_id(), DrawGrid1, true);
                  DrawGrid1->Repaint();
                  }
                else
                  {
                  user_name_to_send      = Contact->name;
                  if(Contact->CT == ContactType_GROUP)
                     set_IM_to_chat_participants(true);
                  else
                     set_IM_to_chat_participants(false);
                  ComboBox1->Text        = Contact->full_name.c_str();
                  CalledNameLbl->Caption = Contact->full_name.c_str();
                  AudioCall();
                  }
                }
              break;
              }
      }
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::AudioCall()
{
TEventLogThread* elt = ofs->elt;
if(Panel_Dial->Visible)
  {
   Panel_Dial->Hide();
   restore_call_hstry();
  }
string name = user_name_to_send;
if(!name.empty())
  {
  TContact ContCopy(-1);
  if(MainFormSLS->Sip->Contacts.get_contact_copy_by_user_name(ContCopy, name))
    if(ContCopy.CT == ContactType_GROUP)
       return;
  string callid = Sip->getCallID_CLD_tc(name);
  if(callid.empty())
    {
    if(elt)
      {
      string timestr;
      TDateTime dt = dt.CurrentTime();
      exsTime(dt,timestr);
      elt->FputEvt("\n" + timestr + " CALL " + (string)"\"" +  name + "\"");
      }
    TSdpMediaCont smc;
    Sip->sendInitInvite(name, ComboBox1->Text.c_str(), &smc);
    bool exists = false;
    for(int i=0;i<ComboBox1->Items->Count;i++)
        if(ComboBox1->Items->Strings[i] == ComboBox1->Text)
          {
          exists = true;
          break;
          }
    if(!exists)
       ComboBox1->Items->Add(ComboBox1->Text);
    }
  }
else
  {
  if(ComboBox1->Items->Count)
    {
    ComboBox1->Text        = ComboBox1->Items->Strings[0];
    CalledNameLbl->Caption = ComboBox1->Text;
    }
  }
}
//---------------------------------------------------------------------------
//--- Вызов поступил от параллельного телефона (не от GUI)
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::AudioCall_PPH(const string& source_callid)
{
TEventLogThread* elt = ofs->elt;
if(Panel_Dial->Visible)
  {
   Panel_Dial->Hide();
   restore_call_hstry();
  }
string name = user_name_to_send;
if(!name.empty())
  {
  TContact ContCopy(-1);
  if(MainFormSLS->Sip->Contacts.get_contact_copy_by_user_name(ContCopy, name))
    if(ContCopy.CT == ContactType_GROUP)
       return;
  string callid = Sip->getCallID_CLD_tc(name);
  if(callid.empty())
    {
    if(elt)
      {
      string timestr;
      TDateTime dt = dt.CurrentTime();
      exsTime(dt,timestr);
      elt->FputEvt("\n" + timestr + " CALL " + (string)"\"" +  name + "\"");
      }
    TSdpMediaCont smc;
    smc.src_of_call = 1;             // Вызов поступил от параллельного телефона (не от GUI)
    smc.src_callid  = source_callid; // callid поступившего вызова
    Sip->sendInitInvite(name, ComboBox1->Text.c_str(), &smc);
    bool exists = false;
    for(int i=0;i<ComboBox1->Items->Count;i++)
        if(ComboBox1->Items->Strings[i] == ComboBox1->Text)
          {
          exists = true;
          break;
          }
    if(!exists)
       ComboBox1->Items->Add(ComboBox1->Text);
    }
  }
else
  {
  if(ComboBox1->Items->Count)
    {
    ComboBox1->Text        = ComboBox1->Items->Strings[0];
    CalledNameLbl->Caption = ComboBox1->Text;
    }
  }
}
//--------------------------------------------------------------------------
void __fastcall TMainFormSLS::Refer_AudioCall(int referred_tag)
{
TEventLogThread* elt = ofs->elt;
if(Panel_Dial->Visible)
  {
   Panel_Dial->Hide();
   restore_call_hstry();
  }
string name = user_name_to_send;
if(!name.empty())
  {
  string callid = Sip->getCallID_CLD_tc(name);
  if(callid.empty())
    {
    if(elt)
       elt->FputEvt("\nCALL " + (string)"\"" +  name + "\"");
    TSdpMediaCont smc;
    Sip->sendInitInvite_OnReferInit(name, ComboBox1->Text.c_str(), &smc, referred_tag);
    bool exists = false;
    for(int i=0;i<ComboBox1->Items->Count;i++)
        if(ComboBox1->Items->Strings[i] == ComboBox1->Text)
          {
          exists = true;
          break;
          }
    if(!exists)
       ComboBox1->Items->Add(ComboBox1->Text);
    }
  }
else
  {
  if(ComboBox1->Items->Count)
    {
    ComboBox1->Text        = ComboBox1->Items->Strings[0];
    CalledNameLbl->Caption = ComboBox1->Text;
    }
  }
}
//----------------------------------------------------------------------------
void __fastcall TMainFormSLS::StartOutgoingCall_OnConferenceCreate(TConfCont* pConfCont, int tag_conf_creator)
{
TEventLogThread* elt = ofs->elt;
if(Panel_Dial->Visible)
   Panel_Dial->Hide();
string name = user_name_to_send;
if(!name.empty())
  {
  string callid = Sip->getCallID_CLD_tc(name);
  if(callid.empty())
    {
    if(elt)
       elt->FputEvt("\nCALL " + (string)"\"" +  name + "\"");
    TSdpMediaCont smc;
    pConfCont->lt = Lt_Out;
    Sip->sendInitInvite_OnConferenceCreate(name,ComboBox1->Text.c_str(), &smc, pConfCont, tag_conf_creator);
    bool exists = false;
    for(int i=0;i<ComboBox1->Items->Count;i++)
        if(ComboBox1->Items->Strings[i] == ComboBox1->Text)
          {
          exists = true;
          break;
          }
    if(!exists)
       ComboBox1->Items->Add(ComboBox1->Text);
    ComboBox1->Text        = ComboBox1->Text.SetLength(0);
    CalledNameLbl->Caption = ComboBox1->Text;
    }
  }
else
  {
  if(ComboBox1->Items->Count)
    {
    ComboBox1->Text        = ComboBox1->Items->Strings[0];
    CalledNameLbl->Caption = ComboBox1->Text;
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::get_client_root(string& client_root)
{
/*
STARTUPINFO stin;
GetStartupInfo (&stin);
string s = string(stin.lpTitle); //Full name to the executed program
*/
string s = Application->ExeName.c_str();
int st = s.rfind("\\");
if(st != -1)
  client_root = s.substr(0,st); //delete of the program name
}
//------------------------------------------------------------------------------
void __fastcall TMainFormSLS::get_client_directories(const string& client_root)
{
#ifdef DEBUG__SIP__CLIENT
log_dir     = client_root + "\\LOG";
contact_dir = client_root + "\\CONT";
#else
char EnvName[] = {"APPDATA"};
char EnvValue[ENV_SZ];
int rv = GetEnvironmentVariable(EnvName,EnvValue,ENV_SZ);
if(!rv)//No such EnvName
  {
  set_client_roots(client_root);
  return;
  }
string rsc_path;
if(rv < ENV_SZ)     //cannot be case rv == ENV_SZ  -- see description GetEnvironmentVariable()
  {
  rsc_path  = string(EnvValue);
  rsc_path += "\\" + client_node+ "\\" + client_name;
  set_client_roots(rsc_path);
  }
else  //rv > ENV_SZ, buf size too small, func return required size of buf, including termination symbol
  {
  char* buf = new char[rv];
  if(GetEnvironmentVariable(EnvName,buf,rv))
    {
    string rsc_path = string(buf);
    rsc_path   += "\\" + client_node+ "\\" + client_name;
    set_client_roots(rsc_path);
    }
  delete [] buf;
  }
#endif
}
//------------------------------------------------------------------------------
void __fastcall TMainFormSLS::set_client_roots(const string& path)
{
ini_dir     = path + "\\INI";
clients_dir = path + "\\CLIENTS";
client_dir  = path + "\\CLIENT";
cont_dir    = path + "\\CONT";
log_dir     = path + "\\LOG";
sound_dir   = path + "\\RES\\Sound";
}
//------------------------------------------------------------------------------
void __fastcall TMainFormSLS::get_media_devices_from_registry()
{
TRegistry& regKey = *new TRegistry();
regKey.RootKey = ROOT_KEY;
bool keyGood = regKey.OpenKey(key_name.c_str(),false);
if(keyGood)
  {
  keyGood = regKey.OpenKey(dev_key_name.c_str(),false);
  if(keyGood)
    {
    keyGood = regKey.OpenKey(sound_key_name.c_str(),false);
    if(keyGood)
      {
      string in_dev   = regKey.ReadString(sound_in_device_name.c_str()).c_str();
      string out_dev  = regKey.ReadString(sound_out_device_name.c_str()).c_str();
      int in_numDevs  = waveInGetNumDevs();  //mic
      int out_numDevs = waveOutGetNumDevs(); //dyn
      WAVEINCAPS  wic;
      WAVEOUTCAPS woc;
      device_list in_dl;
      device_list out_dl;
      for(int i=0; i<in_numDevs; i++)
         if(!waveInGetDevCaps(i, &wic, sizeof(WAVEINCAPS)))
           in_dl.insert(device_list::value_type(string(wic.szPname),i));
      for(int i=0; i<out_numDevs; i++)
         {
         if(!waveOutGetDevCaps(i, &woc, sizeof(WAVEOUTCAPS)))
           out_dl.insert(device_list::value_type(string(woc.szPname),i));
         }
      if(in_dl.size() > 1)   //if <= 1 will be used WAVE_MAPPER  in waveInOpen()
        {
        device_list::iterator it = in_dl.find(in_dev);
        if(it != in_dl.end())
           in_sound_dev.set_media_device(in_dev,(*it).second);
        }
      if(out_dl.size() > 1) //if <= 1 will be used WAVE_MAPPER  in waveOutOpen()
        {
        device_list::iterator it = out_dl.find(out_dev);
        if(it != out_dl.end())
           out_sound_dev.set_media_device(out_dev,(*it).second);
        }
      }
    }
  regKey.CloseKey();
  }
delete &regKey;
}
//------------------------------------------------------------------------------
//---   RFC 3265
//---   3.3.3. Forking
//---   In accordance with the rules for proxying non-INVITE requests as
//---   defined in SIP [1], successful SUBSCRIBE requests will receive only
//---   one 200-class response; however, due to forking, the subscription may
//---   have been accepted by multiple nodes.  The subscriber MUST therefore
//---   be prepared to receive NOTIFY requests with "From:" tags which differ
//---   from the "To:" tag received in the SUBSCRIBE 200-class response.
//---   If multiple NOTIFY messages are received in different dialogs in
//---   response to a single SUBSCRIBE message, each dialog represents a
//---   different destination to which the SUBSCRIBE request was forked.  For
//---   information on subscriber handling in such situations, see section
//---   4.4.9.
//------------------------------------------------------------------------------
void __fastcall TMainFormSLS::PROCESS_NOTIFY_PRESENCE(TEventLogThread* elt, TExchBuf* buf)
{
try{
if(elt)
 if(elt->getlog())
   {
   TDateTime DateTime = DateTime.CurrentDateTime();
   string str;
   exsTime(DateTime,str);
   str = "\n" + str + " PROCESS_NOTIFY_PRESENCE\n";
   elt->FputEvt(str,1);
   }
bool deactivated = false;
ClientState client_state = ClientState_NDef;
if(buf->msg == "active")
  {
  string log = "\nNOTYFY \"active\" rcvd from abonent: " + buf->callid + " number of rcvd from tags: ";
  Sip->Contacts.AS.update_person_lst(buf,log); // buf->callid содержит user_name, buf->msg_6 -- from_tag,  buf->msg_5 -- person_id
  if(elt)
    if(elt->getlog())
      elt->FputEvt(log,1);
  if(!buf->b1)  //Sdp not received
    {
    TDateTime CurrDeateTime = CurrDeateTime.CurrentDateTime();
    if(CurrDeateTime  -  __StartDateTime < TDateTime(0,0,30,0)) //Прошло меньше 30 sec после старта. Если больше, то оставляем предадущее состояние
       client_state = ClientState_On_Line;
    }
  else if(buf->msg_3 == "open")   //tuple->state
    {
    if(buf->msg_4.empty())   //person->activities
       client_state = ClientState_On_Line;
    else{
        if(buf->msg_4 == "away")
           client_state = ClientState_On_Line; //ClientState_Away;
        else if(buf->msg_4 == "busy")
           client_state = ClientState_Busy;
        else if(buf->msg_4 == "unknown")
           client_state = ClientState_On_Line;
        }
    }
  else if(buf->msg_3 == "closed")
     client_state = ClientState_On_Line; //ClientState_Off_Line;  in pj_sip IOS in active state recived "closed"
  }
else if(buf->msg == "terminated")
  {
  string log = "\nNOTYFY \"terminated\" rcvd from abonent: " + buf->callid + " number of rcvd from tags: ";
  int active_notyfy_count = Sip->Contacts.AS.delete_from_person_lst(buf, log); // buf->callid содержит user_name, buf->msg_6 from_tag
  if(elt)
    if(elt->getlog())
      elt->FputEvt(log,1);


  if(buf->msg_2 == "timeout")
    {
    Sip->reset_OLD_init_NEW_SUBSCRIPTION(buf->callid);  //В данном случае callid содержит name
    return; //stay without changing
    }
  else
   {
   if(!active_notyfy_count) //Не осталось ни одного person_id на данном номере
     {
     client_state = ClientState_Off_Line;
     deactivated  = true;
     Sip->reset_SUBSCRIPTION(buf->callid);  //в данном случае buf->callid содержит user_name
     }
   }
  }

if(client_state == ClientState_NDef) //NOTIFY comes without SDP
  return;
Sip->Contacts.set_contact_state(buf->callid, client_state);
Sip->Contacts.set_contact_state_comment(buf->callid, buf->msg_1, buf->b1, deactivated, true); //buf->msg_1 == "note"
DrawGrid1->Repaint();
}//try
catch(Exception& e){exsSstEXCEPTION(ofs->elt,"__PROCESS_NOTIFY_PRESENCE()",e);}
}
//----------------------------------------------------------------------------
void __fastcall TMainFormSLS::ComboBox1Click(TObject *Sender)
{
if(ContactMenu->Visible)
   ContactMenu->Close();
string s = ComboBox1->Text.c_str();
if(check_on_phone_number(s))
  {
  user_name_to_send = s;
  return;
  }
TContact ContCopy(-1);
if(Sip->Contacts.get_contact_copy_by_display_name(ContCopy,s))
  {
  user_name_to_send = ContCopy.name;
  if(ContCopy.CT == ContactType_GROUP)
     set_IM_to_chat_participants(true);
  else
     set_IM_to_chat_participants(false);
  return;
  }
user_name_to_send.clear();
set_IM_to_chat_participants(false);
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::PageControl1Resize(TObject *Sender)
{
TabSheet1_Resize();
TabSheet2_Resize();
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::TabSheet1Resize(TObject *Sender)
{
DrawGrid1_Resize();
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::Panel_ChatResize(TObject *Sender)
{
Memo_Chat_Resize();
Image_StartChat_Resize();
}
//---------------------------------------------------------------------------

void __fastcall TMainFormSLS::Panel_DialPadMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
dial_number_mouse_up();
}
//---------------------------------------------------------------------------

void __fastcall TMainFormSLS::Label2MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
dial_number_mouse_up();
}
//---------------------------------------------------------------------------

void __fastcall TMainFormSLS::assign_dig_btn_owner_tag(int tag)
{
Image_Dig_0->Tag     = tag;
Image_Dig_1->Tag     = tag;
Image_Dig_2->Tag     = tag;
Image_Dig_3->Tag     = tag;
Image_Dig_4->Tag     = tag;
Image_Dig_5->Tag     = tag;
Image_Dig_6->Tag     = tag;
Image_Dig_7->Tag     = tag;
Image_Dig_8->Tag     = tag;
Image_Dig_9->Tag     = tag;
Image_Dig_Star->Tag  = tag;
Image_Dig_Pound->Tag = tag;
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::Show_Panel_Dial(int type,int tag)
{
if(type == 2)      //New DialPad_FORM show
  {
  hide_call_hstry();
  if(DialPad->Visible)
    {
    DialPad->Hide_DPW();
    restore_call_hstry();
    }
  else
    {
    for(int i = 0; i < ControlCount; i++)
      {
      TCall_Panel* Panel = dynamic_cast<TCall_Panel*>(Controls[i]);
      if(Panel)
        if(Panel->Tag)
          if(Panel->Tag == tag)
             DialPad->Show_DPW(InitState_DTMF,tag);
      }
    } 
  return;
  }

if(type == 4)      //New DialPad_Panel show
  {
  hide_call_hstry();
  if(DPP->Visible)
    {
    DPP->Hide();
    restore_call_hstry();
    }
  else
     DPP->ShowDialPad();
  return;
  }


if(type == 3)
  {
  hide_call_hstry();
  if(DialPad->Visible)
    {
    DialPad->Hide_DPW();
    restore_call_hstry();
    }
  else
    DialPad->Show_DPW(InitState_DIAL, -1);
  return;
  }

//------------ Below old type of DialPad

if(type == 1) //small dialpad from call_panel
  {
  hide_call_hstry();
  for(int i = 0; i < ControlCount; i++)
     {
     TCall_Panel* Panel = dynamic_cast<TCall_Panel*>(Controls[i]);
     if(Panel)
        if(Panel->Tag)
          if(Panel->Tag == tag)
            {
            if(!Panel_Dial->Visible)
              {
              Panel_Dial->Width  = Screen->Width/5;
              Panel_Dial->Height = Screen->Height/5;
              Image_Dig_Resize();
              Panel_Dial->Top    = Panel->Top + Panel->Height;
              Panel_Dial->Height -= 30;
              Panel_Dial->Left   = Panel->Left + Panel->Width - Panel_Dial->Width -10;
              Btn_SaveNumber->Visible = false;
              Btn_Call->Visible = false;
              assign_dig_btn_owner_tag(tag);
              Panel_Dial->Show();
              }
            else
              {
              Panel_Dial->Hide();
              restore_call_hstry();
              }
            }

     }
  return;
  }

if(!Panel_Dial->Visible) //normal dialpad
  {
  hide_call_hstry();
  ComboBox1->Text = "";
  CalledNameLbl->Caption = ComboBox1->Text;
  user_name_to_send.clear();
  set_IM_to_chat_participants(false);

  Panel_Dial->Width  = Screen->Width/5;
  Panel_Dial->Height = Screen->Height/5;

  Image_Dig_Resize();
  Btn_SaveNumber->Left  = Image_Dig_1->Left;
  Btn_SaveNumber->Top   = Image_Dig_0->Top + Image_Dig_0->Height + 10;
  Btn_SaveNumber->Width = Image_Dig_2->Left + Image_Dig_2->Width/2 - Btn_SaveNumber->Left - 2;
  Btn_Call->Left  = Image_Dig_2->Left + Image_Dig_2->Width/2 + 2;
  Btn_Call->Top   = Btn_SaveNumber->Top;
  Btn_Call->Width = Image_Dig_3->Left + Image_Dig_3->Width - Btn_Call->Left;
  Btn_SaveNumber->Visible = true;
  Btn_Call->Visible = true;

  Panel_Dial_Resize();
  Panel_Dial->Show();
  }
else
  {
  Panel_Dial->Hide();
  restore_call_hstry();
  }
}
//---------------------------------------------------------------------------
//-- This func MUST be used in main proc thread only  -----------------------
//---------------------------------------------------------------------------  
void __fastcall TMainFormSLS::hide_call_hstry()
{
if(Im.get_raw_count() > 1)
  {
  string s = Im.get_selected_remote_user();
  if(!s.empty())
      selected_remote_user = s;
  Im._clear_im_str_list();
  Im.clear_selected_remote_user();
  }
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::restore_call_hstry()
{
if(Im.get_selected_remote_user().empty())
 if(!selected_remote_user.empty())
   {
   Im.set_selected_remote_user(selected_remote_user);
   Im.load_user_history();
   }
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::draw_dial_btn(int type,int local_tag)
{
TImageList* Dial_Btn = NULL;
if(!type)
   Dial_Btn = ImageList_Dial_Btn_Norm;
else
   Dial_Btn = ImageList_Dial_Btn_Pressed;
if(Dial_Btn)
  {
  switch(local_tag){
       case 10:Dial_Btn->Draw(Image_Dig_0->Canvas,0,0,10,true);
               Image_Dig_0->Refresh();
               break;
       case 11:Dial_Btn->Draw(Image_Dig_1->Canvas,0,0,0,true);
               Image_Dig_1->Refresh();
               break;
       case 12:Dial_Btn->Draw(Image_Dig_2->Canvas,0,0,1,true);
               Image_Dig_2->Refresh();
               break;
       case 13:Dial_Btn->Draw(Image_Dig_3->Canvas,0,0,2,true);
               Image_Dig_3->Refresh();
               break;
       case 14:Dial_Btn->Draw(Image_Dig_4->Canvas,0,0,3,true);
               Image_Dig_4->Refresh();
               break;
       case 15:Dial_Btn->Draw(Image_Dig_5->Canvas,0,0,4,true);
               Image_Dig_5->Refresh();
               break;
       case 16:Dial_Btn->Draw(Image_Dig_6->Canvas,0,0,5,true);
               Image_Dig_6->Refresh();
               break;
       case 17:Dial_Btn->Draw(Image_Dig_7->Canvas,0,0,6,true);
               Image_Dig_7->Refresh();
               break;
       case 18:Dial_Btn->Draw(Image_Dig_8->Canvas,0,0,7,true);
               Image_Dig_8->Refresh();
               break;
       case 19:Dial_Btn->Draw(Image_Dig_9->Canvas,0,0,8,true);
               Image_Dig_9->Refresh();
               break;
       case 20:          //Image_Dig_A should be added to the dialpad
               break;
       case 21:          //Image_Dig_B should be added to the dialpad
               break;
       case 22:          //Image_Dig_C should be added to the dialpad
               break;
       case 23:          //Image_Dig_D should be added to the dialpad
               break;
       case 24:Dial_Btn->Draw(Image_Dig_Star->Canvas,0,0,9,true);
               Image_Dig_Star->Refresh();
               break;
       case 25:Dial_Btn->Draw(Image_Dig_Pound->Canvas,0,0,11,true);
               Image_Dig_Pound->Refresh();
               break;
     }
  }
}
//---------------------------------------------------------------------------
int __fastcall TMainFormSLS::get_pressed_dig(TImage* img)
{  //Возвращаемое значение в соответствии с RFC 2833  3.10 DTMF Events (минус 10)
if(img->Name == "Image_Dig_0")
   return 10;
if(img->Name == "Image_Dig_1")
   return 11;
if(img->Name == "Image_Dig_2")
   return 12;
if(img->Name == "Image_Dig_3")
   return 13;
if(img->Name == "Image_Dig_4")
   return 14;
if(img->Name == "Image_Dig_5")
   return 15;
if(img->Name == "Image_Dig_6")
   return 16;
if(img->Name == "Image_Dig_7")
   return 17;
if(img->Name == "Image_Dig_8")
   return 18;
if(img->Name == "Image_Dig_9")
   return 19;
if(img->Name == "Image_Dig_A") //Should be added to the dialpad
   return 22;
if(img->Name == "Image_Dig_B") //Should be added to the dialpad
   return 23;
if(img->Name == "Image_Dig_C") //Should be added to the dialpad
   return 24;
if(img->Name == "Image_Dig_D") //Should be added to the dialpad
   return 25;
if(img->Name == "Image_Dig_Flash") //Should be added to the dialpad
   return 26;
if(img->Name == "Image_Dig_Star")
   return 20;
if(img->Name == "Image_Dig_Pound")
   return 21;
return 0; //Unknown
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::Image_Dig_MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
TImage* img = (TImage*)Sender;
AnsiString S = ComboBox1->Text;
int local_tag = get_pressed_dig(img);
if((local_tag > 9)&&(local_tag < 20))
  S += inttostr(local_tag - 10).c_str();
else if(local_tag == 20)
  S += "*";
else if(local_tag == 21)
  S += "#";
else if(local_tag == 22)
  S += "A";
else if(local_tag == 23)
  S += "B";
else if(local_tag == 24)
  S += "C";
else if(local_tag == 25)  //26(16) - flash RFC 2833 3.10
  S += "D";
ComboBox1->Text = S;
user_name_to_send = S.c_str();
TMediaSession* ms = MainFormSLS->Sip->sss->GetMs_by_Call_Tag(img->Tag);
if(ms)
  {
  TUdpChannel* uc = ms->getSoundChannel();
  if(uc)
    if(uc->wopt)
      if((uc->wopt->WOS == WaveOutputState_GEN_DTMF_DIGITS_START)||(uc->wopt->WOS == WaveOutputState_GEN_DTMF_DIGITS_CONTINUE))
          uc->wopt->WOS = WaveOutputState_GEN_DTMF_DIGITS_STOP;
  }
draw_dial_btn(0,local_tag);
}
//----------------------------------------------------------------------------
static int dtmf_pktn;
void __fastcall TMainFormSLS::Image_Dig_MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
TImage* img = (TImage*)Sender;
int local_tag = get_pressed_dig(img);

TMediaSession* ms = MainFormSLS->Sip->sss->GetMs_by_Call_Tag(img->Tag);
if(ms)
  {
  TUdpChannel* uc = ms->getSoundChannel();
  if(uc)
    if(uc->wopt)
      if(uc->wopt->WOS == WaveOutputState_RECEIVING_VOICE)
        {
        uc->wopt->dtmf.wos   = uc->wopt->WOS;
        uc->wopt->dtmf.digit = local_tag;
        uc->wopt->WOS = WaveOutputState_GEN_DTMF_DIGITS_START;
        }
  uc = ms->getRtpAudioChannel();
  if(uc)
    if(uc->sendThread)
      {
      int dig = local_tag - 10;
      for(int i=0;i<7;i++)
         switch(i){
               case 0:{
                      TOutPutDtmfBlock* opd = exsCreateOutPutDtmfBlock(dtmf_pktn,START_DTT,16,160,1,101);
                      if(opd)
                        {
                        opd->first_byte(dig);
                        opd->second_byte(false,10); //0 - "end" flag,10 - signal volume
                        opd->dig_duration(160);
                        uc->sendThread->DTS.push_dtmf(uc->sendThread,opd);
                        Sip->updateSentQueue_1(opd);
                        }
                      break;
                      }
               case 1:{
                      TOutPutDtmfBlock* opd = exsCreateOutPutDtmfBlock(dtmf_pktn,CONTINUE_DTT,16,160,0,101);
                      if(opd)
                        {
                        opd->first_byte(dig);
                        opd->second_byte(false,10);
                        opd->dig_duration(320);
                        uc->sendThread->DTS.push_dtmf(uc->sendThread,opd);
                        Sip->updateSentQueue_1(opd);
                        }
                       break;
                      }
               case 2:{
                      TOutPutDtmfBlock* opd = exsCreateOutPutDtmfBlock(dtmf_pktn,CONTINUE_DTT,16,160,0,101);
                      if(opd)
                        {
                        opd->first_byte(dig);
                        opd->second_byte(false,10);
                        opd->dig_duration(480);
                        uc->sendThread->DTS.push_dtmf(uc->sendThread,opd);
                        Sip->updateSentQueue_1(opd);
                        }
                       break;
                      }
               case 3:{
                      TOutPutDtmfBlock* opd = exsCreateOutPutDtmfBlock(dtmf_pktn,CONTINUE_DTT,16,160,0,101);
                      if(opd)
                        {
                        opd->first_byte(dig);
                        opd->second_byte(false,10);
                        opd->dig_duration(640);
                        uc->sendThread->DTS.push_dtmf(uc->sendThread,opd);
                        Sip->updateSentQueue_1(opd);
                        }
                      break;
                      }
               case 4:{
                      TOutPutDtmfBlock* opd = exsCreateOutPutDtmfBlock(dtmf_pktn,STOP_DTT,16,160,0,101);
                      if(opd)
                        {
                        opd->first_byte(dig);
                        opd->second_byte(true,10);
                        opd->dig_duration(800);
                        uc->sendThread->DTS.push_dtmf(uc->sendThread,opd);
                        Sip->updateSentQueue_1(opd);
                        }
                       break;
                      }
               case 5:{
                      TOutPutDtmfBlock* opd = exsCreateOutPutDtmfBlock(dtmf_pktn,PAUSE_DTT,20,0,0,0);
                      if(opd)
                        {
                        uc->sendThread->DTS.push_dtmf(uc->sendThread,opd);
                        Sip->updateSentQueue_1(opd);
                        }
                      break;
                      }
               case 6:{
                      TOutPutDtmfBlock* opd = exsCreateOutPutDtmfBlock(dtmf_pktn,PAUSE_DTT,0,0,0,0);
                      if(opd)
                        {
                        uc->sendThread->DTS.push_dtmf(uc->sendThread,opd);
                        Sip->updateSentQueue_1(opd);
                        }
                      break;
                      }
               }
      }
  }
draw_dial_btn(1,local_tag);
}
//-------------------------------------------------------------------------------

void __fastcall TMainFormSLS::Btn_CallMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
AudioCall();
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::Panel_AddContactMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
add_contact_mouse_up();

/*
if(ContactMenu->Visible)
   ContactMenu->Close();
#ifdef Enterprise_Edition
 EnterpriseSubscList->Show();
#else
 AddContact->M_Show();
#endif
*/
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::Label1MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
add_contact_mouse_up();

/*
if(ContactMenu->Visible)
   ContactMenu->Close();
#ifdef Enterprise_Edition
 EnterpriseSubscList->Show();
#else
 AddContact->M_Show();
#endif
*/
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::Label3MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
if(ContactMenu->Visible)
   ContactMenu->Close();
#ifdef Enterprise_Edition
 EnterpriseSubscList->Show();
#else
 AddContact->M_Show();
#endif
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::VideoCam1Click(TObject *Sender)
{
#ifdef SIP_Video
if(Form4->Visible)
   Form4->Close();
if(Form3->Visible)
   if(Form3->LocalVideoPanel->Visible)
      Form3->LocalVideoPanel->Hide();
Form2->Left = Left;
Form2->Top  = Top;
Form2->Panel1->Top  = 0;
Form2->Panel1->Left = 0;
Form2->Panel1->Width = 640; //160;
Form2->Panel1->Height = 480; //120;
Form2->Width = Form2->Panel1->Width + 10;
Form2->Height = Form2->Panel1->Height + 100;

Form2->ComboBox1->Top  = Form2->Height - 70;//Form2->Panel1->Height + 30;
Form2->ComboBox1->Left = 30;
Form2->Label1->Left    = Form2->ComboBox1->Left;
Form2->Label1->Top     = Form2->ComboBox1->Top - 20;

Form2->Button1->Top  = Form2->Panel1->Height  + 25;
Form2->Button1->Left = Form2->ComboBox1->Left + Form2->ComboBox1->Width + 20;

Form2->Button3->Top  = Form2->Button1->Top;
Form2->Button3->Left = Form2->Button1->Left + Form2->Button1->Width + 20;

Form2->Button2->Top  = Form2->Button3->Top;
Form2->Button2->Left = Form2->Button3->Left + Form2->Button3->Width + 20;

Form2->Button6->Top  = Form2->Button1->Top;
Form2->Button6->Left = Form2->Button1->Left + Form2->Button1->Width + 20;

#ifndef VIDEO_CAP_WITH_WINDOWS_FUNC
Form2->Panel1->Visible = false;
#endif

//Form2->Width = Form2->Panel1->Width + 10;

/*
Form2->hWndC = capCreateCaptureWindow (   "My Own Capture Window",
    WS_CHILD | WS_VISIBLE ,   0, 0, 160, 120, Form2->Handle, 0);
*/


#ifdef VIDEO_CAP_WITH_WINDOWS_FUNC
Form2->hWndC = capCreateCaptureWindow (   "My Own Capture Window",
    WS_CHILD | WS_VISIBLE ,   0, 0, 640, 480, Form2->Panel1->Handle, 1);
#endif

Form2->Show();

/*
if(Form2->hWndC)
  {
  // SendMessage(Form2->hWndC, WM_CAP_DRIVER_CONNECT, 1, 0L);
   SendMessage(Form2->hWndC, WM_CAP_DRIVER_CONNECT, 0, 0L);
   capPreview(Form2->hWndC,true);
  }
 */
//char szName[128];
//capDriverGetName( Form2->hWndC,szName,128);



Form2->Timer1->Enabled = true;


  /*
while(1)
     {
     //if(vcam_is_frame_new(0))
      // {
       SendMessage(Form2->hWndC, WM_CAP_GRAB_FRAME, 1, 0L);
       Sleep(10);
      // }
  //   else
    //   Sleep(1);
     }
  */
//   SendMessage(Form2->hWndC, WM_CAP_GRAB_FRAME, 0, 0);

#endif
}
//---------------------------------------------------------------------------

void __fastcall TMainFormSLS::Memo_ChatKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
if(Key == 13)
   {
   if((Shift.Contains(ssCtrl))||(Shift.Contains(ssAlt)))
     return;
   vector<string> v;
   if(Im.remote_im_client.empty())
     {
     TContact* Contact = read_send_strings__for_client_list_participant(v);
     if(Contact)
       IM_Send(Contact,v);
     }
   else
     {
     read_send_strings__for_non_client_list_participant(v);
     TContact Cont;
     Cont.name = Im.remote_im_client;
     IM_Send(&Cont,v);
     }
   }
if(Key == 113) //F2
   Memo_Chat->Clear();
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::Image_StartChatMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
if(get_IM_to_conf_participants())
  {
  send_IM_to_conference_participants();
  return;
  }
if(get_IM_to_chat_participants())
  {
  send_IM_to_chat_participants();
  return;
  }
vector<string> v;  
if(Im.remote_im_client.empty())
  {
  TContact* Contact = read_send_strings__for_client_list_participant(v);
  if(Contact)
     IM_Send(Contact,v);
  }
else
  {
  read_send_strings__for_non_client_list_participant(v);
  TContact Cont;
  Cont.name = Im.remote_im_client;
  IM_Send(&Cont,v);
  }
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::read_send_strings_to_conference(vector<string>& v)
{
for(int i = 0; i < Memo1->Lines->Count; i++)
   {
   string s = Memo1->Lines->Strings[i].c_str();
   if(s.empty())
     if(i==0)
       continue;
   string utf8_s = ANSI_2_UTF8(s);
   v.push_back(utf8_s);
   }
Memo1->Clear();
}
//------------------------------------------------------------------------------
void __fastcall TMainFormSLS::read_send_strings_to_group_chat(vector<string>& v, const string& group_chat_name)
{
vector<string> vp; //for update() function
for(int i = 0; i < Memo1->Lines->Count; i++)
   {
   string s = Memo1->Lines->Strings[i].c_str();
   if(s.empty())
     if(i==0)
       continue;
   vp.push_back(s);
   string utf8_s = ANSI_2_UTF8(s);
   v.push_back(utf8_s);
   }
Memo1->Clear();
TExchBuf buf(WM_APP_MSG_WPARAM__NDEF);
buf.msg = group_chat_name;
Im.update_IM(vp, &buf, IM_TEXT_TYPE_LOCAL_IM);
}
//------------------------------------------------------------------------------
void __fastcall TMainFormSLS::send_IM_to_conference_participants()
{
vector<string> v;
read_send_strings_to_conference(v);
ConferenceWin->Send_IM_To_All_Conf_Participants(v);
}
//------------------------------------------------------------------------------
void __fastcall TMainFormSLS::send_IM_to_chat_participants()
{
vector<string> v;
read_send_strings_to_group_chat(v, user_name_to_send);
TContact Contact(-1);
if(Sip->Contacts.get_contact_copy_by_user_name(Contact, user_name_to_send))
  {
  deque<TGroupName> q;
  Contact.GRNS.GET_GROUP(q);
  while(!q.empty())
       {
       TGroupName GName = q.front();
       q.pop_front();
       TContact Contact;
       Contact.name = GName.name;
       MainFormSLS->IM_Send(&Contact,v);
       }
  }
}
//------------------------------------------------------------------------------
//--- для клиентов, входящих в список личных контактов -------------------------
//------------------------------------------------------------------------------
TContact* __fastcall TMainFormSLS::read_send_strings__for_client_list_participant(vector<string>& v)
{
TContact* rv = NULL;
TContact* Contact = NULL;
vector<string> vp; //for update() function
if(Sip->Contacts.get_sorted_by_full_name())
   Contact = Sip->Contacts.get_contact_by_full_name(DrawGrid1->Row);
else
   Contact = Sip->Contacts.get_contact_by_row(DrawGrid1->Row, false);
if(Contact)
  {
  if((Im.LMS.get_last_msg_sender() != Sip->Account.get_user_name()) || (Im.LMS.imtt != IM_TEXT_TYPE_LOCAL_ADDR) || (Im.LMS.remote_user_name != Contact->name))
    {
    TExchBuf buf(WM_APP_MSG_WPARAM__NDEF);
    buf.msg = Contact->name;
    Im.update(Sip->Account.get_user_name(), &buf, IM_TEXT_TYPE_LOCAL_ADDR);
    Im.LMS.set_last_msg_sender(Sip->Account.get_user_name(), IM_TEXT_TYPE_LOCAL_ADDR);
    Im.LMS.remote_user_name = Contact->name;
    }
  for(int i=0;i < Memo1->Lines->Count; i++)
     {
     string s = Memo1->Lines->Strings[i].c_str();
     if(s.empty())
       if(i==0)
         continue;
     vp.push_back(s);
     string utf8_s = ANSI_2_UTF8(s);
     v.push_back(utf8_s);
     }
  Memo1->Clear();
  TExchBuf buf(WM_APP_MSG_WPARAM__NDEF);
  buf.msg = Contact->name;
  Im.update_IM(vp, &buf, IM_TEXT_TYPE_LOCAL_IM);
  rv = Contact;
  }
return rv;
}
//------------------------------------------------------------------------------
//--- для клиентов, не входящих в список личных контактов ----------------------
//------------------------------------------------------------------------------
void __fastcall TMainFormSLS::read_send_strings__for_non_client_list_participant(vector<string>& v)
{
vector<string> vp; //for update() function
if((Im.LMS.get_last_msg_sender() != Sip->Account.get_user_name()) || (Im.LMS.imtt != IM_TEXT_TYPE_LOCAL_ADDR) || (Im.LMS.remote_user_name != Im.remote_im_client))
  {
  TExchBuf buf(WM_APP_MSG_WPARAM__NDEF);
  buf.msg = Im.remote_im_client;
  Im.update(Sip->Account.get_user_name(), &buf, IM_TEXT_TYPE_LOCAL_ADDR);
  Im.LMS.set_last_msg_sender(Sip->Account.get_user_name(), IM_TEXT_TYPE_LOCAL_ADDR);
  Im.LMS.remote_user_name = Im.remote_im_client;
  }
for(int i=0;i < Memo1->Lines->Count; i++)
   {
   string s = Memo1->Lines->Strings[i].c_str();
   if(s.empty())
     if(i==0)
       continue;
   vp.push_back(s);
   string utf8_s = ANSI_2_UTF8(s);
   v.push_back(utf8_s);
   }
Memo1->Clear();
TExchBuf buf(WM_APP_MSG_WPARAM__NDEF);
buf.msg = Im.remote_im_client;
Im.update_IM(vp, &buf, IM_TEXT_TYPE_LOCAL_IM);
}
//------------------------------------------------------------------------------
void __fastcall TMainFormSLS::IM_Send(TContact* Contact,const vector<string>& v)
{
if(!v.empty())
   Sip->SendInitMessage(Contact,v);
}
//---------------------------------------------------------------------------
void __fastcall TImStr::HSTRY_SAVE(const vector<string>& v,TExchBuf* buf)
{
if(buf)
  {
  if(!buf->msg.empty())
    {
    string user = get_current_user();
    string s_cl = MainFormSLS->get_clients_dir();
    s_cl += "\\" + user;

    /*

    if(MainFormSLS->Im.LCFT)  //Thread для работы с файлом содержащим последние вызовы (Last Calls)
      {
      TLCSBuf* LCSBuf = new TLCSBuf(HSTRY_WRITE);
      if(LCSBuf)
        {
        LCSBuf->start_time = systime;
        LCSBuf->s = s_cl;
        LCSBuf->v = v;
        MainFormSLS->Im.LCFT->push_lcs_buf(LCSBuf);
        }
      }
     */

    if(::DirectoryExists(s_cl.c_str()))
      {
      s_cl += "\\" + _hstry;
      s_cl += "\\" + buf->msg; //remote_user;
      s_cl += "\\" + inttostr(systime.wYear);
      s_cl += "\\" + inttostr(systime.wMonth);
      s_cl += "\\" + inttostr(systime.wDay);
      if(check_directory_existence(s_cl))
        {
        s_cl += "\\m";
        FILE* f = fopen(s_cl.c_str(),"at");
        if(f)
          {
          string s = _TYPE + inttostr(__im_tt) + _lf;
          fputs(s.c_str(),f);
          switch(__im_tt){
                 case IM_TEXT_TYPE_LOCAL_IM:
                 case IM_TEXT_TYPE_REMOTE_IM:{
                      int sz = v.size();
                      s = "sz:" + inttostr(sz) + _lf;
                      fputs(s.c_str(),f);
                      for(int i=0;i<sz;i++)
                         {
                         s = v[i] + _lf;
                         fputs(s.c_str(),f);
                         }
                      break;
                      }
                 case IM_CALL_OUT_ANSWERED:
                 case IM_CALL_IN_ANSWERED:{
                      write_call_duration(f);
                      break;
                      }
                 }
          write_tmstmp(f);
          fclose(f);
          }
        }
      }
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TImStr::write_tmstmp(FILE* f)
{
switch(__im_tt){
      case IM_TEXT_TYPE_LOCAL_IM:
      case IM_TEXT_TYPE_REMOTE_IM:
      case IM_INVITE_ON_FILE_RECEIVING:
      case IM_INVITE_ON_FILE_SENDING:
      case IM_CALL_IN_DECLINED:
      case IM_CALL_IN_MISSED:
      case IM_CALL_IN_ANSWERED:
      case IM_CALL_OUT_NO_ANSWER:
      case IM_CALL_OUT_ANSWERED:
      case IM_CALL_OUT_BUSY:
      case IM_CALL_OUT_NOT_ACCEPTABLE:
           string s = _tstmp + t_stmp + _lf;
           fputs(s.c_str(),f);
           break;
      }
}
//---------------------------------------------------------------------------
void __fastcall TImStr::set_file_length(int a)
{
int rez = 0;
int rem = 0;
if(a > 1000000000)
  {
  rez = a / 1000000000;
  rem = a % 1000000000;
  rem /= 100000000;
__s_file_length = uint_to_str(rez) + "," + uint_to_str(rem) + WS + "Гбайт";
  }
else if(a > 1000000)
  {
  rez = a / 1000000;
  rem = a % 1000000;
  rem /= 100000;
__s_file_length = uint_to_str(rez) + "," + uint_to_str(rem) + WS + "Mбайт";
  }
else if(a > 1000)
  {
  rez = a / 1000;
  rem = a % 1000;
  rem /= 100;
__s_file_length = uint_to_str(rez) + "," + uint_to_str(rem) + WS + "Кбайт";
  }
else
  __s_file_length = uint_to_str(a) + WS + "байт";
}
//---------------------------------------------------------------------------
void __fastcall TImStr::write_call_duration(FILE* f)
{
if(!t_duration.empty())
  {
  string s = _durtn + t_duration + _lf;
  fputs(s.c_str(),f);
  }
}
//---------------------------------------------------------------------------
 void __fastcall TMainFormSLS::Button4Click(TObject *Sender)
{
#ifdef SIP_Video
/*

 DC := GetDC (GetDesktopWindow) ;
   try
    DestBitmap.Width := GetDeviceCaps (DC, HORZRES) ;
    DestBitmap.Height := GetDeviceCaps (DC, VERTRES) ;
    BitBlt(DestBitmap.Canvas.Handle, 0, 0, DestBitmap.Width, DestBitmap.Height, DC, 0, 0, SRCCOPY) ;
   finally
    ReleaseDC (GetDesktopWindow, DC) ;
   end;
 end;

 */
/*

procedure TForm1.Button1Click(Sender: TObject);
var
         DeskTopDC: HDc;
         DeskTopCanvas: TCanvas;
         DeskTopRect: TRect;
         Bitmap: TBitmap;
begin
         DeskTopDC := GetWindowDC(GetDeskTopWindow);
         DeskTopCanvas := TCanvas.Create;
         DeskTopCanvas.Handle := DeskTopDC;
         DeskTopRect := Rect(0,0,Screen.Width,Screen.Height);
         Bitmap := TBitmap.Create;
         with Bitmap do
             begin
             Width := Screen.Width;
             Height:= Screen.Height;
             PixelFormat := pfDevice;
             end;
         Bitmap.Canvas.CopyRect(DeskTopRect,DeskTopCanvas,DeskTopRect);
         Bitmap.SaveToFile ('sample.bmp');
         Bitmap.Free;
         DesktopCanvas.Free;
         ReleaseDC(GetDeskTopWindow,DeskTopDC);
end;
*/
//HDC hdc = GetWindowDC(GetDeskTopWindow());
//HWND hwnd = ::GetDeskTopWindow();




HDC DeskTopDC = GetWindowDC(0);
TCanvas* DeskTopCanvas = new TCanvas;
DeskTopCanvas->Handle  = DeskTopDC;
TRect DeskTopRect      = Rect(0,0,Screen->Width,Screen->Height);

Form3->Remote_Video_Show();

if(Form3->bitmap)
   delete Form3->bitmap;
Form3->bitmap = new Graphics::TBitmap;
Form3->bitmap->Width       =   640;//Screen->Width;
Form3->bitmap->Height      =    480;//Screen->Height;
//Form3->bitmap->PixelFormat = pfDevice;
Form3->bitmap->Canvas->CopyRect(DeskTopRect,DeskTopCanvas,DeskTopRect);


//BitBlt(Form3->bitmap->Canvas->Handle, 0, 0, Form3->bitmap->Width, Form3->bitmap->Height, DeskTopDC, 0, 0, SRCCOPY) ;


Form3->draw_bitmap_on_screen(640,480);

/*
Graphics::TBitmap* bitmap = new Graphics::TBitmap;
bitmap->Width       = Screen->Width;
bitmap->Height      = Screen->Height;
bitmap->PixelFormat = pfDevice;
//      bitmap->Canvas->Brush->Style = bsSolid;

bitmap->Canvas->CopyRect(DeskTopRect,DeskTopCanvas,DeskTopRect);
*/

ReleaseDC(0,DeskTopDC);
delete DeskTopCanvas;
#endif
}
//---------------------------------------------------------------------------

void __fastcall TMainFormSLS::Button5Click(TObject *Sender)
{
#ifdef SIP_Video
/*
DC := GetDC (GetDesktopWindow) ;
   try
    DestBitmap.Width := GetDeviceCaps (DC, HORZRES) ;
    DestBitmap.Height := GetDeviceCaps (DC, VERTRES) ;
    BitBlt(DestBitmap.Canvas.Handle, 0, 0, DestBitmap.Width, DestBitmap.Height, DC, 0, 0, SRCCOPY) ;
   finally
    ReleaseDC (GetDesktopWindow, DC) ;
   end;
 end;
     */

      char buf[256];

   //HWND H = GetActiveWindow(); // - узнаем текущее активное окно
   HWND H = GetDesktopWindow();
   GetWindowText(H, buf, 256); //- считываем заголовок
   GetClassName(H,buf, 256);

    /*

   HWND hwnd = GetDesktopWindow();//GetTopWindow(0);



   HWND hwnd_1 = GetTopWindow(hwnd);//GetNextWindow(hwnd,GW_HWNDNEXT);
   HWND hwnd_2 = GetNextWindow(hwnd_1,GW_HWNDNEXT);
   HWND hwnd_3 = GetNextWindow(hwnd_2,GW_HWNDNEXT);
    HWND hwnd_4 = GetNextWindow(hwnd_3,GW_HWNDNEXT);


    GetClassName(hwnd,buf, 256);
    GetClassName(hwnd_1,buf, 256);
    GetClassName(hwnd_2,buf, 256);
      GetWindowText(hwnd_2,buf, 256);
    GetClassName(hwnd_3,buf, 256);
      GetWindowText(hwnd_3,buf, 256);
    GetClassName(hwnd_4,buf, 256);
  */
//HDC DC = GetWindowDC(hwnd_4);
HDC DC = GetDC(H);

//Form3->Remote_Video_Show();
int w = GetDeviceCaps (DC, HORZRES);
int h = GetDeviceCaps (DC, VERTRES);

Form3->Width = w;
Form3->Height = h;

Form3->Show();

if(!Form3->bitmap)
   Form3->bitmap = new Graphics::TBitmap;
Form3->bitmap->Width   =  w; //500;//640;//Screen->Width;
Form3->bitmap->Height  =  h;//500;//Screen->Height;

BitBlt(Form3->bitmap->Canvas->Handle, 0, 0, Form3->bitmap->Width, Form3->bitmap->Height, DC, 0, 0, SRCCOPY) ;
Form3->draw_bitmap_on_screen(w,h);
ReleaseDC(0,DC);
#endif
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::AboutClick(TObject *Sender)
{
if(DialPad->Visible)
   DialPad->Hide_DPW();
AboutWin->Label3->Caption = Vers.c_str();
AboutWin->Show();
}
//---------------------------------------------------------------------------

void __fastcall TMainFormSLS::SupportClick(TObject *Sender)
{
open_web_site("http://www.pangeo.ru");
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::open_web_site(const string& s)
{
TCHAR Browser[256];
TCHAR buf[256];
HKEY hKey;
int i;
DWORD Size = 256;
int pos;
int len;
TCHAR *EXE = ".exe";

RegOpenKeyEx (HKEY_CLASSES_ROOT, _TEXT("http\\shell\\open\\command"),
                                                 0, KEY_QUERY_VALUE, &hKey);
RegQueryValueEx (hKey, NULL, NULL, NULL, (LPBYTE)buf, &Size);
RegCloseKey (hKey);

// Отрежем то, что после пути с именем
// Найдем, где кончается путь
if (buf[0] == _TEXT('\"'))
{
        lstrcpy (Browser, &buf[1]);
}
else
{
        lstrcpy (Browser, buf);
}

len = lstrlen (Browser);
pos = len - 4;
for (i = 0; i < len - 3; i++)
{
        if (!strnicmp (&Browser[i], EXE, 4))
        {
                pos = i;
                break;
        }
}
Browser[pos + 4] = _TEXT('\0');

ShellExecute (HWND_DESKTOP, _TEXT("open"), Browser,
                       _TEXT(s.c_str()), NULL, SW_SHOWNORMAL);
}
//----------------------------------------------------------------------------
__fastcall TIM_Struct::~TIM_Struct()
{
_clear_im_str_list_FINALLY();
if(LCFT)
  {
  TLastCallsFileThread* lcft = LCFT;
  LCFT = NULL;
  lcft->Terminate();
  lcft->Resume();
  lcft->WaitFor();
  delete lcft;
  }
::DeleteCriticalSection(&isl_cs);
}
//----------------------------------------------------------------------------
__fastcall TImStr::~TImStr()
{
__clear_ssl();
__clear_issl_m();
::DeleteCriticalSection(&issl_cs);
}
//----------------------------------------------------------------------------
void __fastcall TIM_Struct::clear_show_dir()
{
__show_dir.clear();
}
//-----------------------------------------------------------------------------
void __fastcall TIM_Struct::set_show_dir(const string& s)
{
__show_dir = s;
}
//-----------------------------------------------------------------------------
string __fastcall TIM_Struct::get_show_dir()
{
return  __show_dir;
}
//------------------------------------------------------------------------------
void __fastcall TMainFormSLS::IM_DrawGridDrawCell(TObject *Sender, int ACol,
      int ARow, TRect &Rect, TGridDrawState State)
{
     /*
if(State.Contains(gdSelected))
  {
  IM_DrawGrid->Canvas->Brush->Color = clWhite;//clActiveCaption;//clBlue;// clBackground;
  IM_DrawGrid->Canvas->Font->Color  = clBlack;
  IM_DrawGrid->Canvas->FillRect(Rect);
 // IM_DrawGrid->Canvas->DrawFocusRect(Rect);
  }
  */

IM_DrawGrid->Canvas->Brush->Color = clWhite;//clActiveCaption;//clBlue;// clBackground;
IM_DrawGrid->Canvas->Font->Color  = clBlack;
IM_DrawGrid->Canvas->FillRect(Rect);

string remote_user_name = Im.get_selected_remote_user();
TContact contact(-1);
if(!Sip->Contacts.get_contact_copy_by_user_name(contact, remote_user_name))
  contact.full_name = Im.get_fn();

TImStr* IS = Im.getStr(ARow);
if(IS)
  {
  im_text_type IMTT = IS->get_im_tt();
  if(ACol == 0)
    {
    IS->SET_ROW_HEIGHT(ARow);
    int row_height = IM_DrawGrid->RowHeights[ARow];
    TRect Rect_N  = Rect;
    Rect_N.Bottom = Rect_N.Top + row_height;
    IM_DrawGrid->Canvas->Brush->Color = clWhite;
    IM_DrawGrid->Canvas->FillRect(Rect_N);
    }
  if(IS->single_addition())
    {
    IS->set_single_addition(false);
    IM_DrawGrid_Resize();
    }
  if(ACol == 0)
    {
    TRect Rect_1  = Rect;
    if(IMTT == IM_TEXT_TYPE_LOCAL_IM)
      {
      Rect_1.Left += LOCAL_IM_TEXT__LEFT; //40
      IM_DrawGrid->Canvas->Brush->Color = (TColor)0x00C9FF98;
      if(State.Contains(gdFocused))
        {
        IM_DrawGrid->Canvas->Pen->Color = (TColor)0x00A0A0A0;
        IM_DrawGrid->Canvas->RoundRect(Rect_1.Left, Rect_1.Top + 1, Rect_1.Right, Rect_1.Bottom - 1, 15, 15);
        }
      else
        {
        IM_DrawGrid->Canvas->Pen->Color = (TColor)0x00C9FF98;
        IM_DrawGrid->Canvas->RoundRect(Rect_1.Left, Rect_1.Top + 1, Rect_1.Right, Rect_1.Bottom - 1, 15, 15);
        }
      IS->DRAW_IM_SUBSTRINGS(IM_DrawGrid->Canvas, State, Rect_1);
      }
    else if(IMTT == IM_TEXT_TYPE_REMOTE_IM)
       {
       IM_DrawGrid->Canvas->Brush->Color = (TColor)0x00DEDEDE;
       if(State.Contains(gdFocused))
         {
         IM_DrawGrid->Canvas->Pen->Color = (TColor)0x00A0A0A0;
         IM_DrawGrid->Canvas->RoundRect(Rect_1.Left, Rect_1.Top  + 1, Rect_1.Right, Rect_1.Bottom - 1, 15, 15);
         }
       else
         {
         IM_DrawGrid->Canvas->Pen->Color = (TColor)0x00DEDEDE;
         IM_DrawGrid->Canvas->RoundRect(Rect_1.Left, Rect_1.Top + 1, Rect_1.Right, Rect_1.Bottom - 1, 15, 15);
         }
    IS->DRAW_IM_SUBSTRINGS(IM_DrawGrid->Canvas, State, Rect_1);
    }   //if(IMTT == IM_TEXT_TYPE_HTML)
   else
    {
    queue<TImSubStr> q_iss;
    IS->copy_of_issl_elements(q_iss);
    while(!q_iss.empty())
         {
         TImSubStr iss = q_iss.front();
         q_iss.pop();
         IM_DrawGrid->Canvas->Font->Color = iss.font_color;
         IM_DrawGrid->Canvas->Font->Size  = iss.font_size;
         switch(IMTT){
                case IM_TEXT_TOP_STRING:{
                     TFontStyles fs = TFontStyles();
                     if(Im.curr_hstry_period == iss.coord.period)
                        fs = fs << fsUnderline;
                     IM_DrawGrid->Canvas->Font->Style = fs;
                     IM_DrawGrid->Canvas->Font->Name  = iss.font_name;
                     AnsiString S = iss.s.c_str();
                     int text_top = Rect.Top + iss.coord.top;
                     IM_DrawGrid->Canvas->TextOut(Rect.Left + iss.coord.left, text_top, S);
                     if(iss.coord.period)
                       {
                       int text_width = IM_DrawGrid->Canvas->TextWidth(S);
                       int w = 4; int h = 6;
                       TRBitMap rbmp(w, h, BACKGR_WHITE, 0xC0C0C0);
                       int marker_left;
                       marker_left    = Rect.Left + iss.coord.left + text_width + 9;
                       int marker_top = text_top  + (IM_DrawGrid->Canvas->Font->Size)/2 + 1;
                       IM_DrawGrid->Canvas->Draw(marker_left, marker_top, rbmp.bmp);
                       }
                     break;
                     }
                case IM_TEXT_TYPE_DATE:{
                     AnsiString S = iss.s.c_str();
                     IM_DrawGrid->Canvas->Brush->Color = clWhite; //clWhite; // clActiveCaption;//clBlue;// clBackground;
                     IM_DrawGrid->Canvas->Font->Color  = clBlack;
                     IM_DrawGrid->Canvas->Font->Style  = IM_DrawGrid->Canvas->Font->Style << fsBold << fsUnderline;

                     if(State.Contains(gdFocused))
                       {
                   //    IM_DrawGrid->Canvas->Brush->Color = (TColor)0xE0E0E0;
                   //    IM_DrawGrid->Canvas->FillRect(Rect);

                       IM_DrawGrid->Canvas->Pen->Color = (TColor)0x00A0A0A0;
                       IM_DrawGrid->Canvas->RoundRect(Rect_1.Left, Rect_1.Top, Rect_1.Right, Rect_1.Bottom, 20, 20);
                       }

                     IM_DrawGrid->Canvas->TextOut(Rect.Left + iss.coord.left, Rect.Top + 3, S);
                     break;
                     }
                case IM_TEXT_TYPE_LOCAL_ADDR:{
                     AnsiString S;
                     IM_DrawGrid->Canvas->Font->Name  = _font_name_Arial;
                     /*
                     TFontStyles fs = TFontStyles();
                     if(State.Contains(gdFocused))
                        fs = fs << fsBold;
                     IM_DrawGrid->Canvas->Font->Style = fs;
                     */

                     IM_DrawGrid->Canvas->Font->Style = TFontStyles();
                     if(!Sip->Account.get_displayname().empty())
                        S = Sip->Account.get_displayname().c_str();
                     else
                        S = Sip->Account.get_user_name().c_str();
                     if(State.Contains(gdFocused))
                       {
                      // IM_DrawGrid->Canvas->Brush->Color = (TColor)0xE0E0E0;
                      // IM_DrawGrid->Canvas->FillRect(Rect);

                       IM_DrawGrid->Canvas->Pen->Color = (TColor)0x00A0A0A0;
                       IM_DrawGrid->Canvas->RoundRect(Rect.Left, Rect.Top, Rect.Right, Rect.Bottom, 20, 20);
                       }
                     IM_DrawGrid->Canvas->TextOut(Rect.Left + iss.coord.left, Rect.Top + 3, S);
                     break;
                     }
                case IM_TEXT_TYPE_REM_ADDR:{
                     IM_DrawGrid->Canvas->Font->Name  = _font_name_Arial;
                     //TFontStyles fs = TFontStyles();
                     IM_DrawGrid->Canvas->Font->Style = TFontStyles();

                     /*
                     if(State.Contains(gdFocused))
                        fs = fs << fsBold;
                     */

                     if(State.Contains(gdFocused))
                       {
                   //    IM_DrawGrid->Canvas->Brush->Color = (TColor)0xE0E0E0;
                   //    IM_DrawGrid->Canvas->FillRect(Rect);
                       IM_DrawGrid->Canvas->Pen->Color = (TColor)0x00A0A0A0;
                       IM_DrawGrid->Canvas->RoundRect(Rect_1.Left, Rect_1.Top, Rect_1.Right, Rect_1.Bottom, 20, 20);
                       }

                     if(!contact.full_name.empty())
                        IM_DrawGrid->Canvas->TextOut(Rect.Left + iss.coord.left, Rect.Top + 3, contact.full_name.c_str());
                     else
                        IM_DrawGrid->Canvas->TextOut(Rect.Left + iss.coord.left, Rect.Top + 3, contact.name.c_str());
                     break;
                     }

                case IM_CALL_IN_DECLINED:
                case IM_CALL_IN_MISSED:
                case IM_CALL_IN_ANSWERED:
                case IM_CALL_OUT_NO_ANSWER:
                case IM_CALL_OUT_ANSWERED:
                case IM_CALL_OUT_BUSY:
                case IM_CALL_OUT_NOT_ACCEPTABLE:{
                 //    draw_call_margin_line(Rect);
                     IM_DrawGrid->Canvas->Font->Style = TFontStyles();
                     if(State.Contains(gdFocused))
                       {
                       IM_DrawGrid->Canvas->Pen->Color = (TColor)0x00A0A0A0;
                       Rect_1.Top += 10;
                       IM_DrawGrid->Canvas->RoundRect(Rect_1.Left, Rect_1.Top, Rect_1.Right, Rect_1.Bottom, 20, 20);
                       }
                     call_text_to_cell(Rect, contact, IS);
                     break;
                     }
                case IM_INVITE_ON_FILE_RECEIVING:{
                     IM_INVITE_ON_FILE_RECEIVING__DRAW_CELL(State, Rect, Rect_1, IS, iss, q_iss);
                     return; //!!! Не надо в данном случае проходить три раза  ( see  while(it != imstr->issl.end())
                     }
                case IM_INVITE_ON_FILE_SENDING:{
                     IM_INVITE_ON_FILE_SENDING__DRAW_CELL(State, Rect, Rect_1, IS, iss, q_iss);
                     return;
                     }
               }    //switch(IMTT){
       }        // while(!q_iss.empty())
      }      //else  from if(ACol == 0)
    }   //if(ACol == 0)
  else if(ACol == 1)
    {
    IM_DrawGrid->Canvas->Font->Size  = 9;
    IM_DrawGrid->Canvas->Font->Style = TFontStyles();
    switch(IS->get_im_tt()){
           case IM_TEXT_TYPE_REMOTE_IM:
           case IM_TEXT_TYPE_LOCAL_IM:{
                IM_DrawGrid->Canvas->Font->Color = clGray;
                IM_DrawGrid->Canvas->TextOut(Rect.Left + 3, Rect.Top + 1, IS->get_time_stmp().c_str());
                break;
                }
           case IM_CALL_IN_DECLINED:
           case IM_CALL_IN_MISSED:
           case IM_CALL_IN_ANSWERED:
           case IM_CALL_OUT_NO_ANSWER:
           case IM_CALL_OUT_ANSWERED:
           case IM_CALL_OUT_BUSY:
           case IM_CALL_OUT_NOT_ACCEPTABLE:{
              //  draw_time_margin_line(Rect);
                IM_DrawGrid->Canvas->Font->Color = clGray;
                IM_DrawGrid->Canvas->TextOut(Rect.Left + 3, Rect.Top + 12, IS->get_time_stmp().c_str());
                break;
                }
           case IM_INVITE_ON_FILE_RECEIVING:
                IM_DrawGrid->Canvas->Font->Color = clGray;
                IM_DrawGrid->Canvas->TextOut(Rect.Left + 3, Rect.Top + 12, IS->get_time_stmp().c_str());
                break;
           case IM_INVITE_ON_FILE_SENDING:
                IM_DrawGrid->Canvas->Font->Color = clGray;
                IM_DrawGrid->Canvas->TextOut(Rect.Left + 3, Rect.Top + 12, IS->get_time_stmp().c_str());
                break;
           }
    } //(ACol == 1)

  if(ACol == 0)
    {
    switch(IMTT){
           case IM_TEXT_TOP_STRING:
                if(Im.get_raw_count() > 1)
                  {
                  //if(State.Contains(gdFocused))
                     draw_call_margin_line(Rect);
                  // IM_DrawGrid->Canvas->DrawFocusRect(Rect);
                  }
                break;
           /*
           case IM_TEXT_TYPE_PLAIN:
               // if(State.Contains(gdFocused))
                  //IM_DrawGrid->Canvas->DrawFocusRect(Rect);
                break;
           case IM_TEXT_TYPE_HTML:
               // if(State.Contains(gdFocused))
               //   IM_DrawGrid->Canvas->DrawFocusRect(Rect);
                break;
            */
          }
    }
  } //if(imstr)
}
//------------------------------------------------------------------------------
void __fastcall TMainFormSLS::call_text_to_cell(const TRect& Rect, const TContact& contact,TImStr* ImStr)
{
if(ImStr)
  {
  IM_DrawGrid->Canvas->Font->Size = 9;
  AnsiString s;
  switch(ImStr->get_im_tt()){
      case IM_CALL_IN_DECLINED:
           s = declined_call_from_text();
           if(!contact.full_name.empty())
              s += contact.full_name.c_str();
           else
              s += contact.name.c_str();
           if(lng == Lang_RU)
             s += ",  отклонен";
           IM_DrawGrid->Canvas->Font->Name = _font_name_Arial;
           IM_DrawGrid->Canvas->TextOut(Rect.Left + 5, Rect.Top + 12, s);
           return;
      case IM_CALL_IN_MISSED:{
           s = missed_call_from_text();
           IM_DrawGrid->Canvas->Font->Name = _font_name_Arial;
           IM_DrawGrid->Canvas->TextOut(Rect.Left + 5, Rect.Top + 12, s);
           int txt_width = IM_DrawGrid->Canvas->TextWidth(s);
           IM_DrawGrid->Canvas->Font->Style = IM_DrawGrid->Canvas->Font->Style << fsBold;
           if(!contact.full_name.empty())
             IM_DrawGrid->Canvas->TextOut(Rect.Left + 5 + txt_width, Rect.Top + 12, contact.full_name.c_str());
           else
             IM_DrawGrid->Canvas->TextOut(Rect.Left + 5 + txt_width, Rect.Top + 12, contact.name.c_str());
           return;
           }
      case IM_CALL_IN_ANSWERED:{
           s = call_from_answered();
           if(!contact.full_name.empty())
              s += contact.full_name.c_str();
           else
              s += contact.name.c_str();
           string drt = ImStr->get_duration();
           if(!drt.empty())
             {
             if(lng == Lang_RU)
               s += ",  длительность  ";
             else
               s += ",  duration  ";
             s += drt.c_str();
             }
           IM_DrawGrid->Canvas->Font->Name = _font_name_Arial;
           IM_DrawGrid->Canvas->TextOut(Rect.Left + 5, Rect.Top + 12, s);
           return;
           }
      case IM_CALL_OUT_NO_ANSWER:{
           //s = call_to();
           if(!contact.full_name.empty())
              s = contact.full_name.c_str();
           else
              s = contact.name.c_str();
           if(lng == Lang_RU)
             s += " не отвечает";
           else
             s += ", no answer";
           IM_DrawGrid->Canvas->Font->Name = _font_name_Arial;
           IM_DrawGrid->Canvas->TextOut(Rect.Left + 5, Rect.Top + 12, s);
           return;
           }
      case IM_CALL_OUT_ANSWERED:{
           s = call_to_answered();
           if(!contact.full_name.empty())
              s += contact.full_name.c_str();
           else
              s += contact.name.c_str();
           string drt = ImStr->get_duration();
           if(!drt.empty())
             {
             if(lng == Lang_RU)
               s += ",  длительность  ";
             else
               s += ",  duration  ";
             s += drt.c_str();
             }
           IM_DrawGrid->Canvas->Font->Name = _font_name_Arial;
           IM_DrawGrid->Canvas->TextOut(Rect.Left + 5, Rect.Top + 12, s);
           return;
           }
      case IM_CALL_OUT_BUSY:{
           s = call_to();
           if(!contact.full_name.empty())
              s += contact.full_name.c_str();
           else
              s += contact.name.c_str();
           if(lng == Lang_RU)
             s += "  занят";
           else
             s += ",  busy";
           IM_DrawGrid->Canvas->Font->Name = _font_name_Arial;
           IM_DrawGrid->Canvas->TextOut(Rect.Left + 5, Rect.Top + 12, s);
           return;
           }
      case IM_CALL_OUT_NOT_ACCEPTABLE:{
           s = call_to();
           if(!contact.full_name.empty())
              s += contact.full_name.c_str();
           else
              s += contact.name.c_str();
           if(lng == Lang_RU)
             s += "  недоступен";
           else
             s += ",  not acceptable";
           IM_DrawGrid->Canvas->Font->Name = _font_name_Arial;
           IM_DrawGrid->Canvas->TextOut(Rect.Left + 5, Rect.Top + 12, s);
           return;
           }
      }
  IM_DrawGrid->Canvas->TextOut(Rect.Left + 5, Rect.Top + 12, s);
  int width = IM_DrawGrid->Canvas->TextWidth(s);
  if(!contact.full_name.empty())
     IM_DrawGrid->Canvas->TextOut(Rect.Left + width + 10,  Rect.Top + 12, contact.full_name.c_str());
  else
     IM_DrawGrid->Canvas->TextOut(Rect.Left + width + 10,  Rect.Top + 12, contact.name.c_str());
  }
}
//------------------------------------------------------------------------------
AnsiString __fastcall TMainFormSLS::declined_call_from_text()
{
if(lng == Lang_RU)
   return "Вызов от ";
return "Declined сall from ";
}
//------------------------------------------------------------------------------
AnsiString __fastcall TMainFormSLS::missed_call_from_text()
{
if(lng == Lang_RU)
  return "Пропущенный вызов от  ";
return "Missed call from  ";
}
//------------------------------------------------------------------------------
AnsiString   __fastcall TMainFormSLS::call_to()
{
if(lng == Lang_RU)
  return "Абонент ";
return "Call to ";
}
//------------------------------------------------------------------------------
AnsiString   __fastcall TMainFormSLS::call_to_answered()
{
if(lng == Lang_RU)
  return "Вызов  ";
return "Call to  ";
}
//------------------------------------------------------------------------------
AnsiString   __fastcall TMainFormSLS::call_from_answered()
{
if(lng == Lang_RU)
  return "Вызов от  ";
return "Call from  ";
}
//------------------------------------------------------------------------------
void __fastcall TMainFormSLS::draw_call_margin_line(TRect& Rect)
{
int RectWidth  = Rect.Width();
int RectHeight = Rect.Height();
//Draw horiz lines
int w = RectWidth; int h = 1;
TRBitMap rbmp(w, h, 0xF0F0F0); //0x00FFF2EA;
//TRBitMap rbmp(w, h, 0x00FFF2EA);
rbmp.prepare_line_img();
draw_margin_line(IM_DrawGrid->Canvas, Rect.Left, Rect.Top + 2, rbmp);
draw_margin_line(IM_DrawGrid->Canvas, Rect.Left, Rect.Top + RectHeight - 2, rbmp);
//Draw vert lines
w = 1; h = RectHeight - 6;
TRBitMap rbmp_1(w, h, 0xE0E0E0);
//TRBitMap rbmp_1(w, h, 0x00FFF2EA);
rbmp_1.prepare_line_img();
draw_margin_line(IM_DrawGrid->Canvas, Rect.Left,      Rect.Top + 3, rbmp_1);
draw_margin_line(IM_DrawGrid->Canvas, Rect.Right - 2, Rect.Top + 3, rbmp_1);
}
//------------------------------------------------------------------------------
void __fastcall TMainFormSLS::draw_margin_line(TCanvas* Canvas, int left, int  top, TRBitMap& rbmp)
{
Canvas->Draw(left, top, rbmp.bmp);
}
//------------------------------------------------------------------------------
void __fastcall TMainFormSLS::draw_time_margin_line(TRect& Rect)
{
int RectWidth = Rect.Width();
AnsiString s1;
while(IM_DrawGrid->Canvas->TextWidth(s1) < (RectWidth - 18))
      s1 += "_";
TColor Color = IM_DrawGrid->Canvas->Font->Color;
IM_DrawGrid->Canvas->Font->Color = (TColor)0x00FFF2EA; //turquoise_color; // clSilver;
IM_DrawGrid->Canvas->TextOut(Rect.Left, Rect.Top - 3,  s1);
IM_DrawGrid->Canvas->TextOut(Rect.Left, Rect.Top + 16, s1);
int line_width = IM_DrawGrid->Canvas->TextWidth(s1);
IM_DrawGrid->Canvas->TextOut(Rect.Left + line_width, Rect.Top + 7,  "|");
IM_DrawGrid->Canvas->TextOut(Rect.Left + line_width, Rect.Top + 17, "|");
IM_DrawGrid->Canvas->Font->Color = Color;
}
//------------------------------------------------------------------------------
void __fastcall TMainFormSLS::devide_html_string_on_substrings(vector<TImSubStr>& v, string& s)
{
#ifdef Receive_IM_reference_like_HTML_ref
int len = s.length();
int st = s.find("<a" + WS + "href=");
if(st > 0)
  {
  TImSubStr iss;
  iss.s = s.substr(0,st);
  v.push_back(iss);
  s = s.substr(st);
  return;
  }
if(st == -1)
  {
  st = s.find("<A" + WS + "href=");
  if(st > 0)
    {
    TImSubStr iss;
    iss.s = s.substr(0,st);
    v.push_back(iss);
    s = s.substr(st);
    return;
    }
  }
if(!st)
  {
  TImSubStr iss;
  iss.set_im_element_type(im_element_type_href);
  iss.font_color = (TColor)turquoise_color;
  st += 8;
  if(st < len)
    {
    st = s.find("\"",st);
    if(st != -1)
      {
      st++;
      if(st < len)
        {
        int en = s.find("\"",st);
        if(en != -1)
          if(st < en)
            iss.s = s.substr(st,en-st);
        st = s.find(">",st);
        if(st != -1)
          {
          st++;
          if(st < len)
            {
            en = s.find("</a>");
            if(en != -1)
              iss.href_s = s.substr(st,en-st);
            else
              {
              en = s.find("</A>");
              if(en != -1)
                iss.href_s = s.substr(st,en-st);
              }
            }
          }
        }
      }
    }
  v.push_back(iss);
  int en = s.find("</a>");
  if(en != -1)
    {
    en += 4;
    if(en < len)
      s = s.substr(en);
    else
      s.clear();
    }
  else
    {
    en = s.find("</A>");
    if(en != -1)
      {
      en += 4;
      if(en < len)
        s = s.substr(en);
      else
        s.clear();
      }
    else
      s.clear();
    }
  }
if(!s.empty())
 if(st == -1)
   {
   st = s.find("</span>");
   if(st > 0)
     {
     TImSubStr iss;
     iss.s = s.substr(0,st);
     v.push_back(iss);
     s = s.substr(st);
     }
   s.clear();
   }
#else
int st = s.find(__http__);
if(st > 0)
  {
  TImSubStr iss;
  iss.s = s.substr(0,st);
  v.push_back(iss);
  s = s.substr(st);
  return;
  }
if(st == -1)
  {
  st = s.find(__https__);
  if(st == -1)
    {
    s.clear();
    return;
    }
  if(st > 0)
    {
    TImSubStr iss;
    iss.s = s.substr(0,st);
    v.push_back(iss);
    s = s.substr(st);
    return;
    }
  }
if(!st)
  {
  TImSubStr iss;
  iss.set_im_element_type(im_element_type_href);
  iss.font_color = (TColor)turquoise_color;
  int en = s.find(WS,st);
  if(en != -1)
    {
    iss.s = s.substr(st,en-st);
    iss.href_s = iss.s;
    s = s.substr(en);
    }
  else
    {
    iss.s = s;
    iss.href_s = iss.s;
    s.clear();
    }
  v.push_back(iss);
  }
#endif
}
//------------------------------------------------------------------------------
int  __fastcall TImSubStr::__get_first_inclusion_of_start_ref(const string& s)
{
int st = s.find(__http__);
if(!st)
  return st;
if(st > 0)
  {
  int st_1 = s.substr(0,st).find(__https__);
  if(!st_1)
    return st_1;
  if(st_1 > 0)
    {
    if(st_1 < st)
       st = st_1;
    st_1 = s.substr(0,st).find(__www__);
    if(!st_1)
       return st_1;
    if(st_1 > 0)
      if(st_1 < st)
         st = st_1;
    }
  return st;
  }
if(st == -1)
  {
  st = s.find(__https__);
  if(!st)
     return st;
  if(st > 0)
    {
    int st_1 = s.substr(0,st).find(__www__);
    if(st_1 > 0)
      if(st_1 < st)
         st = st_1;
    return st;
    }
  }
if(st == -1)
   st = s.find(__www__);
return st;
}
//-----------------------------------------------------------------------------
void __fastcall TImSubStr::__devide_plain_string_on_substrings(vector<TImSubStr>& v, string& s, bool& start_of_ref_found)
{
int st = __get_first_inclusion_of_start_ref(s);
if(st > 0)
  {
  start_of_ref_found   = true;
  TImSubStr ISS_REF;
  ISS_REF.s = s.substr(0,st);
  v.push_back(ISS_REF);
  s = s.substr(st);
  return;
  }
if(st == -1)          //not found "http://", "https://", "www."
  {
  if(start_of_ref_found)
    {
    TImSubStr ISS_REF;
    ISS_REF.set_im_element_type(im_element_type_href);
    ISS_REF.font_color = (TColor)turquoise_color;
    ISS_REF.s = s;
    v.push_back(ISS_REF);
    }
  else
    {
    TImSubStr ISS_REF;
    ISS_REF.s = s;
    v.push_back(ISS_REF);
    }
  s.clear();
  return;
  }
if(!st)
  {
  start_of_ref_found = true;
  TImSubStr ISS_REF;
  ISS_REF.set_im_element_type(im_element_type_href);
  ISS_REF.font_color = (TColor)turquoise_color;
  int en = s.find(WS,st);
  if(en != -1)
    {
    ISS_REF.s = s.substr(st,en-st);
    s = s.substr(en);
    start_of_ref_found = false;
    v.push_back(ISS_REF);
    }
  else
    {
    ISS_REF.s = s;
    v.push_back(ISS_REF);
    s.clear();
    }
  }
}
//------------------------------------------------------------------------------
int __fastcall TImStr::__devide_plain_string_on_substrings__ON_MOUSE_UP(TCanvas* Canvas, TImSubStr* ISS, TImSubStr* iss_ref, int top_of_str, int st_x, bool& start_of_ref_found, bool& end_of_ref_found)
{
bool www_found = false;
if(!start_of_ref_found)
  {
  unsigned st = ISS->s.find("http", st_x);
  if(st == -1)
    {
    st = ISS->s.find(__www__, st_x);
    if(st == -1)
       return st;
    else
       www_found = true;
    }
  if(!www_found)
    if(ISS->s.find(__http__, st_x) != st)
      if(ISS->s.find(__https__, st_x) != st)
        return -1;
  start_of_ref_found = true;
  int en = ISS->s.find(WS,st);
  if(en != -1)
    {
    iss_ref->s = ISS->s.substr(st,en-st);
    iss_ref->coord.left   = Canvas->TextWidth(ISS->s.substr(0,st).c_str());
    if(__im_tt == IM_TEXT_TYPE_LOCAL_IM)
       iss_ref->coord.left += LOCAL_IM_TEXT__LEFT + ISS->coord.left;
    iss_ref->coord.width  = Canvas->TextWidth(iss_ref->s.c_str());
    iss_ref->coord.top    = top_of_str;
    iss_ref->coord.height = ISS->font_size + get_v_delta();
    end_of_ref_found      = true;
    }
  else  //WS not found - не найден конец refrence
    {
    iss_ref->s = ISS->s.substr(st);
    iss_ref->coord.left   = Canvas->TextWidth(ISS->s.substr(0,st).c_str());
    if(__im_tt == IM_TEXT_TYPE_LOCAL_IM)
       iss_ref->coord.left += LOCAL_IM_TEXT__LEFT + ISS->coord.left;
    iss_ref->coord.width  = Canvas->TextWidth(iss_ref->s.c_str());
    iss_ref->coord.top    = top_of_str;
    iss_ref->coord.height = ISS->font_size + get_v_delta();
    }
  return en;
  }
else
  {
  int en = ISS->s.find(WS,st_x);
  if(en != -1)
    {
    iss_ref->s += ISS->s.substr(0,en);
    iss_ref->coord.left = 0;
    if(__im_tt == IM_TEXT_TYPE_LOCAL_IM)
       iss_ref->coord.left += LOCAL_IM_TEXT__LEFT + ISS->coord.left;
    int width = Canvas->TextWidth(iss_ref->s.c_str());
    if(iss_ref->coord.width < width)
       iss_ref->coord.width = width;
    iss_ref->coord.height += ISS->font_size + get_v_delta();
    end_of_ref_found = true;
    }
  else
    {
    iss_ref->s += ISS->s;
    int width = Canvas->TextWidth(iss_ref->s.c_str());
    if(iss_ref->coord.width < width)
       iss_ref->coord.width = width;
    iss_ref->coord.height += ISS->font_size + get_v_delta();
    }
  return en;
  }
}
//------------------------------------------------------------------------------
void __fastcall TMainFormSLS::REFRESH_IM_DRAW_GRID()
{
/*
if(IM_DrawGrid->VisibleRowCount < IM_DrawGrid->RowCount)
  {
  int client_height = Panel_Chat->Top - Panel1->Top - Panel1->Height;
  int height = 0;
  for(int i = IM_DrawGrid->RowCount - 1; i >= 0; i--)
     {
     if((height + IM_DrawGrid->RowHeights[i]) < client_height)
        height += IM_DrawGrid->RowHeights[i];
     else
        break;
     }
  IM_DrawGrid->Height = height;
  }

//IM_DrawGrid->Top  =  Panel_Chat->Top - IM_DrawGrid->Height;
//IM_DrawGrid->Top  =  Panel1->Top + Panel1->Height;
if(IM_DrawGrid->VisibleRowCount == IM_DrawGrid->RowCount)
  {
  int height = 0;
  for(int i = IM_DrawGrid->RowCount - 1; i >= 0; i--)
      height += IM_DrawGrid->RowHeights[i];
  IM_DrawGrid->Height = height;
  IM_DrawGrid->Top    = Panel_Chat->Top - IM_DrawGrid->Height;
  }
else
  {
  IM_DrawGrid->Top = Panel1->Top + Panel1->Height;
  IM_DrawGrid->TopRow = IM_DrawGrid->RowCount - IM_DrawGrid->VisibleRowCount;
  }
 */

if(!IM_DrawGrid->Visible)
    IM_DrawGrid->Show();
IM_DrawGrid->Repaint();
}
//-----------------------------------------------------------------------------
void __fastcall TIM_Struct::update(const string& s, TExchBuf* buf, im_text_type imtt)
{
if(buf)
  {
  TImStr* IS = new TImStr(imtt);
  if(IS)
    {
    if(get_selected_remote_user() == buf->msg)  // buf->msg = remote_user
      {
      IS->rem_user_selected = true;
      if(imtt == IM_CALL_IN_MISSED)
        {
        if(MainFormSLS->Sip->Contacts.missed_call(buf->msg))
          {
          MainFormSLS->DrawGrid1->Repaint();
          MainFormSLS->TrayMessage_Ext(NIM_MODIFY,"Contact",3);
          }
        }
      else if(imtt == IM_TEXT_TYPE_REM_ADDR)
        {
        if((MainFormSLS->IM_DrawGrid->TopRow + MainFormSLS->IM_DrawGrid->VisibleRowCount) <= (MainFormSLS->IM_DrawGrid->RowCount - 1)) //Last string is not visible
           IS->rem_user_selected = false;
        }
      }
    else
      {
      if(imtt == IM_CALL_IN_MISSED)
        {
        if(MainFormSLS->Sip->Contacts.missed_call(buf->msg))
          {
          MainFormSLS->DrawGrid1->Repaint();
          MainFormSLS->TrayMessage_Ext(NIM_MODIFY,"Contact",3);
          }
        }
      }
    AddLastCall(buf->msg, buf->msg_5, IS->rem_user_selected, imtt);
    TImSubStr* ISS = new TImSubStr;
    if(ISS)
      {
      switch(imtt){
            case IM_TEXT_TYPE_LOCAL_ADDR:
                 ISS->font_color = clGray;
                 ISS->s = s;
                 break;
            case IM_TEXT_TYPE_REM_ADDR:
                 ISS->font_color = (TColor)turquoise_color;
                 ISS->s = s;
                 break;
            case IM_TEXT_TYPE_LOCAL_IM:
                 ISS->s = s;
                 break;
            case IM_TEXT_TYPE_REMOTE_IM:
                 ISS->s = s;
                 break;
            case IM_CALL_IN_MISSED:
            case IM_CALL_IN_DECLINED:
            case IM_CALL_OUT_BUSY:
            case IM_CALL_OUT_NO_ANSWER:
            case IM_CALL_OUT_NOT_ACCEPTABLE:
                 IS->time_stmp_to_str();
                 ISS->s = " ";
                 break;
            case IM_CALL_IN_ANSWERED:
            case IM_CALL_OUT_ANSWERED:
                 IS->time_stmp_to_str();
                 IS->set_duration(buf->msg_1);
                 ISS->s = " ";
                 break;
            }
      IS->addSubStr(ISS);
      vector<string> v;
      if(!s.empty())
         v.push_back(s);
      HSTRY_SAVE_AND_DISPLAY(buf, IS, v);  //Thread Im.LCFT use
      }
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TIM_Struct::HSTRY_SAVE_AND_DISPLAY(TExchBuf* buf, TImStr* IS, const vector<string>& v)
{
if(MainFormSLS->Im.LCFT)  //Thread для работы с файлом содержащим последние вызовы (Last Calls)
  if(buf)
    if(!buf->msg.empty())
      {
      string user = get_current_user();
      string s_cl = MainFormSLS->get_clients_dir();
      s_cl += "\\" + user;
      TLCSBuf* LCSBuf = new TLCSBuf(HSTRY_WRITE);
      if(LCSBuf)
        {
        LCSBuf->s   = s_cl;
        LCSBuf->s_1 = buf->msg;    //remote user
        if(IS->get_im_tt() == IM_INVITE_ON_FILE_RECEIVING)
          if(buf->SV)
            {
            LCSBuf->s_2 = buf->SV->get_file_id();
            LCSBuf->s_3 = buf->SV->get_file_name();
            LCSBuf->s_4 = buf->SV->get_thumb_id();
            }
        LCSBuf->s_5 = buf->msg_5;  //full_name of remote user
        LCSBuf->IS  = IS;
        LCSBuf->v   = v;
        MainFormSLS->Im.LCFT->push_lcs_buf(LCSBuf);
        return; //!!! delete IS may be in the LCFT (if(!IS->rem_user_selected))
        }
      }
delete IS;
}
//---------------------------------------------------------------------------
void __fastcall TIM_Struct::AddLastCall(const string& username, const string& display_username, bool SELECTED, im_text_type imtt)
{
switch(imtt){
      case IM_CALL_IN_MISSED:
      case IM_CALL_IN_DECLINED:
      case IM_CALL_OUT_BUSY:
      case IM_CALL_OUT_NO_ANSWER:
      case IM_CALL_IN_ANSWERED:
      case IM_CALL_OUT_ANSWERED:
      case IM_CALL_OUT_NOT_ACCEPTABLE:{
           TContact Contact(-1);
           if(!MainFormSLS->Sip->Contacts.get_contact_copy_by_user_name(Contact, username))
             {
             Contact.name      = username;
             if(display_username.empty())
                Contact.full_name = username;
             else
                Contact.full_name = display_username;
             Contact.cs        = ClientState_NDef;
             }
          TDateTime TimeStmp;
          MainFormSLS->Sip->Contacts.LCS.update_last_call_list(Contact, TimeStmp, imtt, SELECTED, MainFormSLS->DG_LastCalls);
          MainFormSLS->DG_LastCalls->Repaint();
          MainFormSLS->Sip->Contacts.LCS.update_last_call_file(Contact, TimeStmp);
          }
      break;
      }
}
//---------------------------------------------------------------------------
void __fastcall TIM_Struct::update_IM(/*const*/ vector<string>& v, TExchBuf* buf, im_text_type imtt)
{
if(!v.empty())
  {
  int sz = v.size();
  TImStr* IS = new TImStr(imtt);
  if(IS)
    {
    if(get_selected_remote_user() == buf->msg) // buf->msg = remote_user
      IS->rem_user_selected = true;
    switch(imtt){
          case IM_TEXT_TYPE_LOCAL_IM:{
               IS->time_stmp_to_str();
               for(int i = 0;i < sz;i++){
                  TImSubStr* ISS = new TImSubStr;
                  if(ISS)
                    {
                    ISS->s = v[i];
                    if(!IS->get_href())
                        IS->check_local_im_substr_on_ref(ISS->s);
                    IS->addSubStr(ISS);
                    }
                  }
               break;
               }
          case IM_TEXT_TYPE_REMOTE_IM:{
               vector<string> vp;
               IS->time_stmp_to_str();
               for(int i = 0;i < sz;i++){
                  TImSubStr* ISS = new TImSubStr;
                  if(ISS)
                    {
                    ISS->s = UTF8_2_ANSI(v[i]);  //Convert UTF8 -> ansi
                    vp.push_back(ISS->s);
                    if(!IS->get_href())
                        IS->check_remote_im_substr_on_ref(ISS->s);
                    IS->addSubStr(ISS);
                    }
                  }
               v = vp;
               break;
               }
          }//switch(IS->im_tt)
    HSTRY_SAVE_AND_DISPLAY(buf, IS, v);   //Thread Im.LCFT use
    } //if(IS)
  } //if(!v.empty())
else
  {
  switch(imtt){
        case IM_INVITE_ON_FILE_RECEIVING:{
             TImStr* IS = new TImStr(imtt);
             if(IS){
               IS->time_stmp_to_str();
               IS->set_contact_name(buf->msg);
             //  IS->set_year_month_day(year_month_day);
               if(get_selected_remote_user() == buf->msg) // buf->msg = remote_user
                  IS->rem_user_selected = true;
               HSTRY_SAVE_AND_DISPLAY(buf, IS, v);   //Delete IS here. Thread Im.LCFT use.
               }
             break;
             }
        }
  }
}
//---------------------------------------------------------------------------
void   __fastcall TImStr::check_local_im_substr_on_ref(const string& s)
{
if(s.find(__http__)!= -1)
   __href = true;
else if(s.find(__https__)!= -1)
   __href = true;
else if(s.find(__www__)!= -1)
   __href = true;
}
//---------------------------------------------------------------------------
void   __fastcall TImStr::check_remote_im_substr_on_ref(const string& s)
{
#ifdef Receive_IM_reference_like_HTML_ref
if(s.find(__href__)!= -1)
  {
  if(s.find(__a_href__)!= -1)
    __href = true;
  else if(s.find(__A_href__) != -1)
    __href = true;
  }
#else
unsigned st = s.find("http");
if(st != -1)
  {
  if(s.find(__http__) == st)
   __href = true;
  else if(s.find(__https__) == st)
   __href = true;
  }
#endif
}
//----------------------------------------------------------------------------
void __fastcall TIM_Struct::devide_html_msg_by_strings(vector<string>& v, string& partial_str)
{
int st = partial_str.find("<br/>");
if(st == -1)
   st = partial_str.find("<BR/>");
if(st == -1)
  {
  st = partial_str.find("</span>");
  if(st == -1)
     st = partial_str.find("</SPAN>");
  if(st > 0)
     v.push_back(partial_str.substr(0,st));
  partial_str.resize(0);
  return;
  }
if(st > 0)
  {
  v.push_back(partial_str.substr(0,st));
  st+=5;
  if(st < (int)partial_str.length())
     partial_str = partial_str.substr(st);
  else
     partial_str.resize(0);
  return;
  }
if(!st)
  {
  st+=5;
  if(st < (int)partial_str.length())
     partial_str = partial_str.substr(st);
  else
     partial_str.resize(0);
  }
}
//-----------------------------------------------------------------------------
void __fastcall TIM_Struct::devide_plain_msg_by_strings(vector<string>& v, string& s)
{
int st = s.find("\n");
if(st == -1)
  {
  v.push_back(s);
  s.clear();
  return;
  }
int len = s.length();
v.push_back(s.substr(0,st));
if(++st < len)
   s = s.substr(st);
else
   s.clear();
}
//-----------------------------------------------------------------------------
void __fastcall TIM_Struct::dissect_html_text_msg(const string& str,TExchBuf* buf)
{
if(buf)
  if(!buf->SV)
    {
    buf->SV = new TStringsVect;
    if(buf->SV)
      {
      bool dissected = false;
      string s = str;
      int len = s.length();
      int st = s.find("<span");
      if(st == -1)
         st = s.find("<SPAN");
      if(st != -1)
        {
        st += 5;
        if(st < len)
          {
          int en = s.find(">",st);
          if(en != -1)
            {
            en++;
            if(en < len)
              {
              s = s.substr(en);
              while(!s.empty())
                   devide_html_msg_by_strings(buf->SV->v, s);
              dissected = true;
              }
            }
          }
        }
      if(!dissected)
         buf->SV->v.push_back(s);
      } //if(buf->SV)
    }
}
//------------------------------------------------------------------------------
void __fastcall TIM_Struct::dissect_plain_text_msg(const string& str,TExchBuf* buf)
{
if(buf)
  if(!buf->SV)
    {
    buf->SV = new TStringsVect;
    if(buf->SV)
      {
      string s = str;
      if(!buf->SV->check_on_file_receiving(s))
        {
        int st = s.rfind(crlf);  // Received normal IM (Not notification about file transfer)
        if(st != -1)
           s.resize(st);
        while(!s.empty())
           devide_plain_msg_by_strings(buf->SV->v,s);
        }
      }
    }
}
//------------------------------------------------------------------------------
bool __fastcall TStringsVect::check_on_file_receiving(const string& s)
{
//string s_start = "<file>";
//string s_end   = "</file>";

string s_start = "<file";
string s_end   = "/>";

bool rv = false;
int st = s.find(s_start);
if(st == 0)
  {
  int len = s.length();
  st += s_start.length();
  if(st < len)
    {
    if(s.rfind(s_end) != -1)
      {
    __parsing_notfy_of_recv_file_msg(s, len);
    __type = 1;  //Received notification about get file
      rv = true;
      }
    }
  }
return rv;
}
//----------------------------------------------------------------------------------------------
void __fastcall TStringsVect::__parsing_notfy_of_recv_file_msg(const string& s, int len)
{
__get_file_id(s,   len);
__get_file_name(s, len);
__get_thumb_id(s,  len);
}
//------------------------------------------------------------------------------
void __fastcall TStringsVect::__get_file_id(const string& s, int len)
{
int st = s.find("id='");
if(st != -1)
  {
  st += 4;
  if(st < len)
    {
    int en = s.find("'", st);
    if(en != -1)
     __file_id = s.substr(st, en - st);
    }
  }
}
//------------------------------------------------------------------------------------------------
void __fastcall TStringsVect::__get_file_name(const string& s, int len)
{
int st = s.find("name='");
if(st != -1)
  {
  st += 6;
  if(st < len)
    {
    int en = s.find("'", st);
    if(en != -1)
       {
       string s_utf_8 = s.substr(st, en - st);
     __file_name = UTF8_2_ANSI(s_utf_8);           //                 s.substr(st, en - st);;
       }
    }
  }
}
//-----------------------------------------------------------------------------
void __fastcall TStringsVect::__get_thumb_id(const string& s, int len)
{
int st = s.find("thumb='");
if(st != -1)
  {
  st += 7;
  if(st < len)
    {
    int en = s.find("'", st);
    if(en != -1)
     __thumb_id = s.substr(st, en - st);
    }
  }
}
//------------------------------------------------------------------------------
//-- This func not directly works with IM_DrawGrid -----------------------------
//-- Can be used in different threads  -----------------------------------------
//------------------------------------------------------------------------------
void __fastcall TIM_Struct::addStr(TImStr* is)
{
::EnterCriticalSection(&isl_cs);
  is->set_arow(_id);
  is->set_single_addition(true);
  isl.insert(TImStrList::value_type(_id++,is));
  if(is->get_im_tt() == IM_TEXT_TYPE_LOCAL_IM)     //отправка Inst Msg
    {
    ::PostMessage(MainFormSLS->Handle, CONTROL_MSG, WM_APP_MSG_WPARAM__IM__DRAWGRID_ROW_COUNT_ON_SEND_TEXT_MSG, isl.size());
    ::PostMessage(MainFormSLS->Handle, CONTROL_MSG, WM_APP_MSG_WPARAM__IM__DRAWGRID_ROW_COUNT_ON_SEND_TEXT_MSG, isl.size());
    }
  else
    {
    ::PostMessage(MainFormSLS->Handle, CONTROL_MSG, WM_APP_MSG_WPARAM__IM__DRAWGRID_ROW_COUNT, isl.size());
    ::PostMessage(MainFormSLS->Handle, CONTROL_MSG, WM_APP_MSG_WPARAM__IM__DRAWGRID_ROW_COUNT, isl.size()); //!!!2-е сообщение для более четкого отображения
    }
::LeaveCriticalSection(&isl_cs);
}
//------------------------------------------------------------------------------
void __fastcall TIM_Struct::addStr_by_read_hstry_block(TImStr* is)
{
::EnterCriticalSection(&isl_cs);
  is->set_arow(_id);
  isl.insert(TImStrList::value_type(_id++,is));
::LeaveCriticalSection(&isl_cs);
}
//------------------------------------------------------------------------------
void __fastcall TIM_Struct::_clear_im_str_list()
{
::EnterCriticalSection(&isl_cs);
  _id = 0;                                          //!!!
  while(!isl.empty())
       {
       TImStrList::iterator it = isl.begin();
       TImStr* is = (*it).second;
       if(is)
          delete is;
       isl.erase(it);
       }
  _set_top_string(); //!!! INSIDE in addStr() ::PostMessage(MainFormSLS->Handle, CONTROL_MSG, WM_APP_MSG_WPARAM__IM__DRAWGRID_ROW_COUNT, isl.size());
::LeaveCriticalSection(&isl_cs);
}
//------------------------------------------------------------------------------
void __fastcall TIM_Struct::_clear_im_str_list_FINALLY()
{
::EnterCriticalSection(&isl_cs);
  while(!isl.empty())
       {
       TImStrList::iterator it = isl.begin();
       TImStr* is = (*it).second;
       if(is)
         delete is;
       isl.erase(it);
       }
::LeaveCriticalSection(&isl_cs);
}
//------------------------------------------------------------------------------
//-- This func not directly works with IM_DrawGrid -----------------------------
//-- addStr(IS) works with isl only   ------------------------------------------
//-- Can be used in different threads ------------------------------------------
//-- _set_top_string used in main thread only ----------------------------------
//------------------------------------------------------------------------------
void __fastcall TIM_Struct::_set_top_string()
{
TImStr* IS = new TImStr(IM_TEXT_TOP_STRING);
if(IS)
  {
  string s;
  TImSubStr* ISS = new TImSubStr;
  if(ISS)
    {
    ISS->begin = true;
    if(MainFormSLS->lng == Lang_RU)
      s = "Показать вызовы: ";
    else
      s = "Show calls from: ";
    ISS->set_top_string_initial_parameters(s, clBlack, 0);
    IS->addSubStr(ISS);
    }

  ISS = new TImSubStr;
  if(ISS)
    {
     if(MainFormSLS->lng == Lang_RU)
       s = "Вчера";
     else
       s = "Yesterday";
     ISS->set_top_string_initial_parameters(s, (TColor)turquoise_color, 1);
     IS->addSubStr(ISS);
    }

  ISS = new TImSubStr;
  if(ISS)
    {
     if(MainFormSLS->lng == Lang_RU)
       s = "7 дней";
     else
       s = "7 days";
     ISS->set_top_string_initial_parameters(s, (TColor)turquoise_color, 2);
     IS->addSubStr(ISS);
    }

  ISS = new TImSubStr;
  if(ISS)
    {
     if(MainFormSLS->lng == Lang_RU)
       s = "30 дней";
     else
       s = "30 days";
     ISS->set_top_string_initial_parameters(s, (TColor)turquoise_color, 3);
     IS->addSubStr(ISS);
    }

  ISS = new TImSubStr;
  if(ISS)
    {
     if(MainFormSLS->lng == Lang_RU)
       s = "3 месяца";
     else
       s = "3 months";
     ISS->set_top_string_initial_parameters(s, (TColor)turquoise_color, 4);
     IS->addSubStr(ISS);
    }

  ISS = new TImSubStr;
  if(ISS)
    {
     if(MainFormSLS->lng == Lang_RU)
       s = "6 месяцев";
     else
       s = "6 months";
     ISS->set_top_string_initial_parameters(s, (TColor)turquoise_color, 5);
     IS->addSubStr(ISS);
    }

  ISS = new TImSubStr;
  if(ISS)
    {
     if(MainFormSLS->lng == Lang_RU)
       s = "1 год";
     else
       s = "1 year";
     ISS->set_top_string_initial_parameters(s, (TColor)turquoise_color, 6);
     IS->addSubStr(ISS);
    }

  ISS = new TImSubStr;
  if(ISS)
    {
     if(MainFormSLS->lng == Lang_RU)
       s = "С начала";
     else
       s = "from beginning";
     ISS->set_top_string_initial_parameters(s, (TColor)turquoise_color, 7);
     IS->addSubStr(ISS);
    }
  addStr(IS);
  }
}
//------------------------------------------------------------------------------
void __fastcall TImSubStr::set_top_string_initial_parameters(const string& S, TColor FONT_COLOR, int PERIOD)
{
s = S;
font_size    =  9;
font_name    = _font_name_Arial;
font_color   =  FONT_COLOR;
coord.period =  PERIOD;
}
//------------------------------------------------------------------------------
void __fastcall TImSubStr::set_top_string_parameters(int TOP, int& LEFT)
{
MainFormSLS->IM_DrawGrid->Canvas->Font->Size = font_size;
MainFormSLS->IM_DrawGrid->Canvas->Font->Name = font_name;
AnsiString S = s.c_str();
coord.top    = TOP;
coord.left   = LEFT;
coord.height = MainFormSLS->IM_DrawGrid->Canvas->TextHeight(S);
coord.width  = MainFormSLS->IM_DrawGrid->Canvas->TextWidth(S);
if(coord.period == 0)
   LEFT = coord.left + coord.width + 2;
else
   LEFT = coord.left + coord.width + text_delta;
}
//------------------------------------------------------------------------------
void __fastcall TImSubStr::check_max_width(TImSubStr** p_prev_trail, queue<TImSubStr*>& q, int max_width)
{
MainFormSLS->IM_DrawGrid->Canvas->Font->Size = font_size;
string cs = s;
bool redstr = false;
if(cs.length() > 1)
  if(cs[0] == ' ')
    redstr = true; //Красная (новая) строка

TImSubStr* prev_trail = *p_prev_trail;
if(prev_trail)
  {
  if(redstr)
    {
    q.push(prev_trail);
   *p_prev_trail = NULL;
    }
  else
    {
    cs = prev_trail->s + cs;
    delete prev_trail;
    *p_prev_trail = NULL;
    }
  }

while(1){
  AnsiString CS = cs.c_str();
  int width = MainFormSLS->IM_DrawGrid->Canvas->TextWidth(CS);
  if(width < (max_width - 10))
    {
    TImSubStr* iss = new TImSubStr;
    if(iss)
      {
      iss->s         = cs;
      iss->font_size = font_size;
      iss->font_name = font_name;
      q.push(iss);
      }
    break;                                 //  (1)
    }
  else    //Длина строки >= ширины Cell
    {
    vector<string> v;
    while(MainFormSLS->IM_DrawGrid->Canvas->TextWidth(CS) >= (max_width - 10))
         {
         int st = cs.rfind(WS);
         if(st != -1)
           {
           string s1 = cs.substr(st);
           v.push_back(s1);
           cs.resize(st);
           CS = cs.c_str();
           }
         else
           {   //!!! Cannot find any WS. Try devide by letter //return - protection against suspending  // (2)
           int S_Length   = cs.length();
           if(S_Length < 15)
              return;
           int text_width = MainFormSLS->IM_DrawGrid->Canvas->TextWidth(CS);
           int width      = max_width - 10;
           int s_len      =  width * S_Length / text_width;
           if(s_len <= 0)
             return;
           if(s_len < S_Length)
             {
             string s1 = cs.substr(s_len);
             v.push_back(s1);
             cs.resize(s_len);
             CS = cs.c_str();
             }
           else
             break;
           }
         }
    TImSubStr* iss = new TImSubStr;        //Substring with length < (max_width - 10)
    if(iss)
      {
      iss->s         = CS.c_str();
      iss->font_size = font_size;
      iss->font_name = font_name;
      q.push(iss);
      }
    string s_1;             //остатки собрать в одну строку
    while(!v.empty())
         {
         s_1 += v.back();
         v.pop_back();
         }
    if(s_1.length() > 1) //delete leading ws
      if(s_1[0] == ' ')
        s_1 = s_1.substr(1);

    cs = s_1;           // отправить собранные остатки на новую проверку. Выход из цикла когда TextWidth(S) < max_width - (1) или не найдено ни одного WS - (2) - TextWidth слова >= max_width
    }
  } //while(1)
}
//------------------------------------------------------------------------------
void __fastcall TImSubStr::draw_string_with_web_refereces(TCanvas* Canvas, TGridDrawState State, TRect& Rect, int v_delta, int& next_top,
                                                          int& current_count, bool& start_of_ref_found)
{
vector<TImSubStr> v;
string partial_str = s;
while(!partial_str.empty())
     {
    // #ifdef Receive_IM_reference_like_HTML_ref
   //  devide_html_string_on_substrings(v, partial_str);
   //  #else
     __devide_plain_string_on_substrings(v, partial_str, start_of_ref_found);
   //  #endif
     }


int sz = v.size();
int x = 0;
for(int i = 0; i < sz; i++)
   {
   Canvas->Font->Color = v[i].font_color;
   if(!i)
      x = v[i].coord.left;
   if(v[i].get_im_element_type() == im_element_type_href)
     {
     TFontStyles fs = TFontStyles() << fsUnderline;
     if(State.Contains(gdFocused))
        fs = fs << fsBold;
     Canvas->Font->Style = fs;
     }
   else
     Canvas->Font->Style = TFontStyles();
   Canvas->TextOut(Rect.Left + x, Rect.Top + next_top, v[i].s.c_str());
   x += Canvas->TextWidth(v[i].s.c_str());
   }
v.clear();

next_top += font_size + v_delta;
current_count++;
}
//------------------------------------------------------------------------------
void __fastcall TImSubStr::draw_string_with_plain_text(TCanvas* Canvas, TRect& Rect, int v_delta, int& next_top, int& current_count)
{
Canvas->Font->Style = TFontStyles();
Canvas->Font->Color = font_color;
Canvas->TextOut(Rect.Left + coord.left, Rect.Top + next_top, s.c_str());
next_top += font_size + v_delta;
current_count++;
}
//------------------------------------------------------------------------------
void __fastcall TMainFormSLS::IM_DrawGridMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
if(ContactMenu->Visible)
   ContactMenu->Close();
int ACol,ARow;
IM_DrawGrid->MouseToCell(X,Y,ACol,ARow);
TImStr* IS = Im.getStr(ARow);
if(IS)
  {
  if(IS->get_im_tt() == IM_TEXT_TOP_STRING)
    {
    Proc_OnMouseUp_IM_TEXT_TOP_STRING(IS, X, Y);
    return; //!!!
    }

  if(IS->get_im_tt() == IM_INVITE_ON_FILE_RECEIVING)
    {
    if(ACol == 0)
     if(ARow != -1)
      {
      if(Button == mbLeft)
        {
        TRect Rect = IM_DrawGrid->CellRect(ACol,ARow);
        if(X > Rect.Left + LEFT_FILE_TRANSFER_ICON_POSITION)
          if(X < Rect.Left + LEFT_FILE_TRANSFER_ICON_POSITION + rcv_file_img->Width)
             if(Y > Rect.Top + TOP_FILE_TRANSFER_ICON_POSITION )
               if(Y < Rect.Top + TOP_FILE_TRANSFER_ICON_POSITION + rcv_file_img->Height)
                 {
                 vector<string> v;
                 IS->copy_of_issl_strings(v);
                 TExchFileMsg efm(0);  //Request on receive file
                 efm.v = v;
                 efm.grid_arow      = IS->get_arow();
                 efm.file_sender    = IS->get_contact_name();
                 efm.year_month_day = IS->get_year_month_day();
                 //по правой кнопке возможно указать "сохранить как ... " где указать из выпавшего диалога конкретную директорию, которую сохранить в __received_file_storage

                 efm.set_parsed(true);
                 FEXCH.fexch_ins(efm);
                 FEXCH.check_file_exch_activity();
                 }
        return;
        }
      }
    }

  if(IS->get_im_tt() == IM_INVITE_ON_FILE_SENDING)
    {
    if(ACol == 0)
     if(ARow != -1)
      {
      if(Button == mbLeft)
        {
        TRect Rect = IM_DrawGrid->CellRect(ACol,ARow);
        if(X < Rect.Right - LEFT_FILE_TRANSFER_ICON_POSITION)
          if(X > Rect.Right - LEFT_FILE_TRANSFER_ICON_POSITION - rcv_file_img->Width)
             if(Y > Rect.Top + TOP_FILE_TRANSFER_ICON_POSITION )
               if(Y < Rect.Top + TOP_FILE_TRANSFER_ICON_POSITION + rcv_file_img->Height)
                 {
                  string dir, name;
                  queue<TImSubStr> q_iss;
                  IS->copy_of_issl_elements(q_iss);
                  if(!q_iss.empty())
                    {
                    TImSubStr iss = q_iss.front();
                    q_iss.pop();
                    dir = iss.get_substr_by_pattern("dir:");
                    }
                  if(!q_iss.empty())
                    {
                    TImSubStr iss = q_iss.front();
                    q_iss.pop();
                    name = iss.get_substr_by_pattern("name:");
                    }
                  string path = dir;
                  if(!name.empty())
                    path += "\\" + name;
                  //ShellExecute(NULL, "open", path.c_str(), NULL, NULL, SW_SHOWMAXIMIZED);
                  ShellExecuteMy(path);
                 }
        return;
        }
      }
    }

  if(ACol == 0)
    if(ARow != -1)
      if(Button == mbRight)
        {
        switch(IS->get_im_tt()){
           case IM_TEXT_TYPE_LOCAL_IM:
           case IM_TEXT_TYPE_REMOTE_IM:{
                POINT MousePos;
              ::GetCursorPos(&MousePos);
                IM_DrawGrid->PopupMenu = PopupMenu_IM;
                IM_DrawGrid->PopupMenu->Popup(MousePos.x, MousePos.y);
                IM_DrawGrid->Row = ARow;  //т.к. правая кнопка не делает  gdFocused
                IM_DrawGrid->PopupMenu = NULL;
                return;
                }
           case IM_INVITE_ON_FILE_RECEIVING:{
                if(IS->get_file_transfer_state() != 3) //3 - файл не загружен
                  {
                  POINT MousePos;
                ::GetCursorPos(&MousePos);
                  IM_DrawGrid->PopupMenu = PopupMenu_IM_FileReceive;
                  IM_DrawGrid->PopupMenu->Popup(MousePos.x, MousePos.y);
                  IM_DrawGrid->Row = ARow;  //т.к. правая кнопка не делает  gdFocused
                  Im.create_file_downloading_path(IS,1);
                  IM_DrawGrid->PopupMenu = NULL;
                  }
                return;
                }
           case IM_INVITE_ON_FILE_SENDING:{
                POINT MousePos;
              ::GetCursorPos(&MousePos);
                IM_DrawGrid->PopupMenu = PopupMenu_IM_FileReceive;
                IM_DrawGrid->PopupMenu->Popup(MousePos.x, MousePos.y);
                IM_DrawGrid->Row = ARow;  //т.к. правая кнопка не делает  gdFocused
                Im.create_file_sending_path(IS);
                IM_DrawGrid->PopupMenu = NULL;
                return;
                }
           default: IM_DrawGrid->PopupMenu = NULL;
           }
        }

  if(ACol == 0)
    if(IS->get_href())  //Данное сообщение имеет в своем составе web references
      IS->SELECT_AND_OPEN_WEB_REFERENCE(IM_DrawGrid, X, Y, ACol, ARow);

  } // if(IS)
}
//------------------------------------------------------------------------------
//-- составдение пути для к дир с загруженными файлами
//-- type 1 - with creating show_dir, 0 - without
//------------------------------------------------------------------------------
bool __fastcall TIM_Struct::create_file_downloading_path(TImStr* IS, int type)
{
bool rv = false;
if(type == 1)
   clear_show_dir();   //Путь для пункта меню "Показать в папке"
string s_cl         = MainFormSLS->get_clients_dir();
string curr_user    = get_current_user();
string file_storage = MainFormSLS->FEXCH.get_default_subdir_of_received_file_storage();
string file_sender  = IS->get_contact_name();
string dir;
if(!s_cl.empty())
  {
  dir = s_cl;
  if(!curr_user.empty())
    {
    dir += "\\" + curr_user;
    if(!file_storage.empty())
      {
      dir += "\\" + file_storage;
      if(!file_sender.empty())
         dir += "\\" + file_sender;
      }
    }
  }
TExchFileMsg efm(0);
vector<string> v;
IS->copy_of_issl_strings(v);
efm.v = v;
string file_name = efm.get_substring_by_pattern("name:");
if(!file_name.empty())
  {
  string file_path = dir + "\\" + file_name;
  if(::FileExists(file_path.c_str()))
    {
    if(type == 1)
       set_show_dir(dir);
    rv = true;
    }
  }
return rv;
}
//------------------------------------------------------------------------------
void __fastcall TIM_Struct::create_file_sending_path(TImStr* IS)
{
clear_show_dir();   //Путь для пункта меню "Показать в папке"
queue<TImSubStr> q_iss;
IS->copy_of_issl_elements(q_iss);
while(!q_iss.empty())
     {
     TImSubStr iss = q_iss.front();
     q_iss.pop();
     string dir = iss.get_substr_by_pattern("dir:");
     if(!dir.empty())
       {
       set_show_dir(dir);
       break;
       }
     }
}
//------------------------------------------------------------------------------
void __fastcall TImStr::DRAW_IM_SUBSTRINGS(TCanvas* Canvas, TGridDrawState State, TRect& Rect_1)
{
Canvas->Font->Size  = 10; //iss->font_size;
int next_top = 2;
int current_count = 0;
bool start_of_ref_found = false; // bool end_of_ref_found = false;
TImSubStrList::iterator it = issl_m.begin();
while(it != issl_m.end())
     {
     TImSubStr* ISS = (*it++).second;
     if(ISS)
       {
        if(start_of_ref_found)
          {
          if(ISS->s.find(WS) == 0)  //след строка начинается с пробела
             start_of_ref_found = false;
          }
       if(get_href())  //В сообщении есть хотя бы одна ссылка
         ISS->draw_string_with_web_refereces(Canvas, State, Rect_1, get_v_delta(), next_top, current_count, start_of_ref_found);
       else
         ISS->draw_string_with_plain_text(Canvas, Rect_1, get_v_delta(), next_top, current_count);
       }
     }
}
//------------------------------------------------------------------------------
void __fastcall TImStr::SELECT_AND_OPEN_WEB_REFERENCE(TDrawGrid* DG, int X, int Y, int ACol, int ARow)
{
TImSubStr* ISS_REF = NULL;
vector<TImSubStr*> v; //list with coordinates of references
int next_top = 0;
bool start_of_ref_found = false; bool end_of_ref_found = false;
TImSubStrList::iterator it = issl_m.begin();
while(it != issl_m.end())
     {
     TImSubStr* ISS = (*it++).second;
     if(ISS)
       {
       if(ISS_REF)
         {
         if(start_of_ref_found)
           if(!end_of_ref_found)
             {
             if(ISS->s.find("http") == 0)  //след строка начинается с http
               {
               start_of_ref_found = false;
               end_of_ref_found   = false;
               v.push_back(ISS_REF);
               ISS_REF = NULL;
               }
             else if(ISS->s.find(__www__) == 0)  //след строка начинается с "www."
               {
               start_of_ref_found = false;
               end_of_ref_found   = false;
               v.push_back(ISS_REF);
               ISS_REF = NULL;
               }
             else if(ISS->s.find(WS) == 0)  //след строка начинается с пробела
               {
               start_of_ref_found = false;
               end_of_ref_found   = false;
               v.push_back(ISS_REF);
               ISS_REF = NULL;
               }
             }
         }
       int st = 0;
       while(st != -1)
            {
            if(!ISS_REF)
                ISS_REF = new TImSubStr;
            st = __devide_plain_string_on_substrings__ON_MOUSE_UP(DG->Canvas, ISS, ISS_REF, next_top, st, start_of_ref_found, end_of_ref_found );
            if(start_of_ref_found)
              if(end_of_ref_found)
                {
                start_of_ref_found = false;
                end_of_ref_found   = false;
                v.push_back(ISS_REF);
                ISS_REF = NULL;
                }
            }
       next_top += ISS->font_size + get_v_delta();
       } //if(ISS)
     } //while(it != IS->issl_m.end())

 if(ISS_REF)
   {
   start_of_ref_found = false;
   end_of_ref_found   = false;
   v.push_back(ISS_REF);
   ISS_REF = NULL;
   }
 int sz = v.size();
 if(ACol != -1)
   if(ARow != -1)
     {
     TRect Rect = DG->CellRect(ACol,ARow);
     for(int i = 0;i < sz; i++)
        {
         int Yd = Y - Rect.Top;
         if(X > v[i]->coord.left)
           if(X < v[i]->coord.left + v[i]->coord.width)
            if(Yd > v[i]->coord.top)
              if(Yd < v[i]->coord.top + v[i]->coord.height)
                {
                 MainFormSLS->open_web_site(v[i]->s);
                 break;
                }
        }
     }
 for(int i = 0;i < sz; i++)
     delete v[i];
}
//------------------------------------------------------------------------------
//-- После любого case ОБЯЗАТЕЛЬНО return --------------------------------------
//-- т.к. load_user_history() содержит очистку isl (_clear_im_str_list() with
//-- IS deletion) --------------------------------------------------------------
//-- Im.load_user_history(start, end) должен быть последним в каждом case !!!---
//------------------------------------------------------------------------------
void __fastcall TMainFormSLS::Proc_OnMouseUp_IM_TEXT_TOP_STRING(TImStr* IS, int X, int Y)
{
queue<TImSubStr> Q_ISS;
IS->copy_of_issl_elements(Q_ISS);
while(!Q_ISS.empty())
     {
     TImSubStr ISS = Q_ISS.front();
     Q_ISS.pop();
     if(X > ISS.coord.left)
      if(X < ISS.coord.left + ISS.coord.width)
        if(Y > ISS.coord.top)
          if(Y < ISS.coord.top + ISS.coord.height)
            {
            if(ISS.coord.period)
              Im.curr_hstry_period = ISS.coord.period;
            TDateTime end = end.CurrentDate();
            switch(ISS.coord.period){
                  case 1: {//вчера
                          TDateTime start = end - 1.0;
                          Im.load_user_history(start, end);
                          return;
                          }
                  case 2: {//7 days
                          TDateTime start = end - 7.0;
                          Im.load_user_history(start, end);
                          return;
                          }
                  case 3: { //30 days
                          TDateTime start = end - 30.0;
                          Im.load_user_history(start, end);
                          return;
                          }
                  case 4: {//3 months
                          TDateTime start = end - 92.0;
                          Im.load_user_history(start, end);
                          return;
                          }
                  case 5: {//6 months
                          TDateTime start = end - 183.0;
                          Im.load_user_history(start, end);
                          return;
                          }
                  case 6: {//1 year
                          TDateTime start = end - 365.0;
                          Im.load_user_history(start, end);
                          return;
                          }
                  case 7: {//from beginning
                          TDateTime start(2013,1,1);
                          Im.load_user_history(start, end);
                          return;
                          }
                  }  //switch(ISS->coord.period){
            }  //if(Y < ISS.coord.top + ISS.coord.height)
       }   //while(!Q_ISS.empty())
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::FormDestroy(TObject *Sender)
{
TrayMessage(NIM_DELETE);
tf_destroy();
::DeleteCriticalSection(&callin_exchlst_cs);
::DeleteCriticalSection(&videoout_exchlst_cs);
::DeleteCriticalSection(&filetrans_exchlst_cs);
}
//---------------------------------------------------------------------------
bool __fastcall TMainFormSLS::TrayMessage(DWORD dwMessage,int type)
{
   NOTIFYICONDATA tnd;
   PSTR pszTip;

  // pszTip = TipText();

   tnd.cbSize          = sizeof(NOTIFYICONDATA);
   tnd.hWnd            = Handle;
   tnd.uID             = IDC_MYICON;
   tnd.uFlags          = NIF_MESSAGE | NIF_ICON | NIF_TIP;
   tnd.uCallbackMessage	= MYWM_NOTIFY;

   tnd.hIcon = NULL;
   tnd.szTip[0] = '\0';

   return (Shell_NotifyIcon(dwMessage, &tnd));
}

//---------------------------------------------------------------------------
bool __fastcall TMainFormSLS::TrayMessage_Ext(DWORD dwMessage,const string& s,int type)
{
   NOTIFYICONDATA tnd;
   PSTR pszTip;

   tnd.cbSize          = sizeof(NOTIFYICONDATA);
   tnd.hWnd            = Handle;
   tnd.uID             = IDC_MYICON;
   tnd.uFlags          = NIF_MESSAGE | NIF_ICON | NIF_TIP;
   tnd.uCallbackMessage	= MYWM_NOTIFY;

   if (dwMessage == NIM_ADD)
      {
       if(type == 1)
           tnd.hIcon		= Image8->Picture->Icon->Handle;
        else if(type == 0)
           tnd.hIcon		= Image7->Picture->Icon->Handle;
        else if(type == 2)
           tnd.hIcon            = TrayIcon_Image->Picture->Icon->Handle;

        TrayIcon_Handle = tnd.hIcon;

        if (!s.empty())
           lstrcpyn(tnd.szTip, s.c_str(), sizeof(tnd.szTip));
	else
           tnd.szTip[0] = '\0';

      }

  else if (dwMessage == NIM_MODIFY)
    {
        if(type == 1)
           tnd.hIcon		= Image8->Picture->Icon->Handle; 
        else if(type == 0)
           tnd.hIcon		= Image7->Picture->Icon->Handle;
        else if(type == 2)
           tnd.hIcon            = TrayIcon_Image->Picture->Icon->Handle;
        else if(type == 3)
           tnd.hIcon            = Image8->Picture->Icon->Handle;
        TrayIcon_Handle = tnd.hIcon;

        if (!s.empty())
           lstrcpyn(tnd.szTip, s.c_str(), sizeof(tnd.szTip));
	else
           tnd.szTip[0] = '\0';
    }
   else
    {
        tnd.hIcon = NULL;
        tnd.szTip[0] = '\0';
    }

   return (Shell_NotifyIcon(dwMessage, &tnd));
}

//---------------------------------------------------------------------------

void __fastcall TMainFormSLS::ExitClick(TObject *Sender)
{
Log_Start_App_Termination_Explicit();
term_explicit = true;
Close();
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::Log_Start_App_Termination_Explicit()
{
if(ofs)
  if(ofs->elt)
    {
    TDateTime DateTime = DateTime.CurrentDateTime();
    string s;
    exsTime(DateTime,s);
    s = "\n" + s + " !!!START APP TERMINATION BY USER EXPLICIT\n";
    ofs->elt->FputEvt(s,1);
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::Log_Start_App_Termination_By_Alt_F4()
{
if(ofs)
  if(ofs->elt)
    {
    TDateTime DateTime = DateTime.CurrentDateTime();
    string s;
    exsTime(DateTime,s);
    s = "\n" + s + " !!!START APP TERMINATION BY ALT_F4\n";
    ofs->elt->FputEvt(s,1);
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::On_Minimize_Application(TObject* Sender)
{
app_minimized = true;
Close_All_Open_Window();
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::On_Restore_Application(TObject* Sender)
{
app_minimized = false;
ShowWindow(Handle,SW_SHOW);
if(ConferenceWin->get_size_CP())
  ConferenceWin->Show();
else
  ShowWindow(ConferenceWin->Handle,SW_HIDE);
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::MY_WND_PROC(TMessage& Msg)
{
if(Msg.Msg == s_uTaskbarRestart)
  TrayMessage_Ext(NIM_ADD,"Contact",2);
WndProc(Msg);   //!!! Call Standard win procedure
}
//----------------------------------------------------------------------------
void __fastcall TMainFormSLS::MyNotify(TMessage& Msg)
{
if(_CLOSE_REQUEST) return;
POINT MousePos;
switch(Msg.LParam)
    {
    case WM_RBUTTONUP:
        if (GetCursorPos(&MousePos))
       {
            PopupMenu1->PopupComponent = Form1;
            SetForegroundWindow(Handle);
            PopupMenu1->Popup(MousePos.x, MousePos.y);
       }
        else
           Show();
        break;
    case WM_LBUTTONUP:
            Close_All_Open_Window();
            if(app_minimized)
              {
              app_minimized    = false;
              app_on_tray_only = false;
              Application->Restore();
              }
            else
              {
              app_minimized = false;
              RestoreAppFromTray();
              }
            SetForegroundWindow(Handle);  
            break;
         /*
    case WM_LBUTTONDBLCLK:
            ShowWindow(Handle,SW_SHOWNA);
            ShowWindow(Application->Handle,SW_SHOWNA);
          break;
          */
    default:
        break;
    }
TForm::Dispatch(&Msg);
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::RestoreAppFromTray()
{
app_minimized    = false;
if(app_on_tray_only)
   Application->Minimize();
app_on_tray_only = false;
Application->Restore();

TCtrlExch CE;
if(Sip->Contacts.LCS.GetFirstMissedName(CE.s1))
  {
  CE.WPARAM = WM_APP_MSG_WPARAM__SELECT_FIRST_MISSED_CALL;
  CES.push(CE);
::PostMessage(MainFormSLS->Handle, CONTROL_MSG, WM_APP_MSG_WPARAM__SELECT_FIRST_MISSED_CALL, WM_APP_MSG_LPARAM__NOPARAM);
  }
}
//---------------------------------------------------------------------------
/*
void __fastcall TMainFormSLS::MyNotify_1(TMessage& Msg)
{
DefWindowProc(Handle,Msg.Msg,Msg.WParam,Msg.LParam);
TForm::Dispatch(&Msg);
}
*/
//--------------------------------------------------------------------------
void __fastcall TMainFormSLS::MyNotify_2(TMessage& Msg)
{ 
switch(Msg.WParam){

      case HTCLOSE:
           Close_All_Open_Window();
           if(ConferenceWin->Visible)
              ConferenceWin->Hide();
           ShowWindow(Handle,SW_HIDE);
           ShowWindow(Application->Handle, SW_HIDE);
           app_on_tray_only = true;
           return;

      case HTMINBUTTON:
           app_minimized = true;
           break;

      case HTMAXBUTTON:
           if(ConferenceWin)
              if(ConferenceWin->Visible)
                if(ConferenceWin->get_size_CP())
                 ::PostMessage(ConferenceWin->Handle, CONFERENCE_PLAIN_MSG, WM_CONFERENCE_PLAIN_MSG_WPARAM__MAXIMIXE, WM_CONFERENCE_PLAIN_MSG_LPARAM__NDEF);
           break;
      }
TForm::Dispatch(&Msg);
}
//--------------------------------------------------------------------------
void __fastcall TMainFormSLS::OpenSipClientClick(TObject *Sender)
{
RestoreAppFromTray();
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::ExitSipClientClick(TObject *Sender)
{
Log_Start_App_Termination_Explicit();
term_explicit = true;
Close();
}
//---------------------------------------------------------------------------
void __fastcall TCallPanelsStruct::add_panel_tag(int a,TDrawGrid* DG)
{
::EnterCriticalSection(&cpl_cs);
  cpl.push_back(a);
  DG->RowCount = cpl.size();
  DG->Height   = DG->RowCount * MainFormSLS->Panel1->Height;//73;
  if(!DG->Visible)
     DG->Show();
  DG->Repaint();
::LeaveCriticalSection(&cpl_cs);
}
//---------------------------------------------------------------------------
int  __fastcall TCallPanelsStruct::get_panel_tag_by_row(int ARow)
{
int rv=-1;
::EnterCriticalSection(&cpl_cs);
  if(!cpl.empty())
    {
    deque<int>::iterator it = cpl.begin();
    int i = 0;
    while(it != cpl.end())
         {
         if(i == ARow)
           {
           rv = (*it);  //CL_Panel->Tag
           break;
           }
         it++; i++;
         }
    }
::LeaveCriticalSection(&cpl_cs);
return rv;
}
//---------------------------------------------------------------------------
void __fastcall TCallPanelsStruct::del_panel_tag(int a,TDrawGrid* DG)
{
::EnterCriticalSection(&cpl_cs);
  if(!cpl.empty())
    {
    deque<int>::iterator it = cpl.begin();
    while(it != cpl.end())
      {
       if((*it) == a)
         {
         cpl.erase(it);
         break;
         }
      it++;
      }
    }
  int sz = cpl.size();
  if(sz)
    {
    DG->RowCount = sz;
    DG->Height   = DG->RowCount * MainFormSLS->Panel1->Height;
    if(!DG->Visible)
       DG->Show();
    DG->Repaint();
    }
  else
   DG->Hide();

::LeaveCriticalSection(&cpl_cs);
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::CL_DrawGridDrawCell(TObject *Sender, int ACol,
      int ARow, TRect &Rect, TGridDrawState State)
{
TCall_Panel* panel = get_Call_Panel_By_Row(ARow);
if(panel)
  {
  panel->Top  = CL_DrawGrid->Top  + Rect.Top;
  panel->Left = RIGHT_PANEL->Left; //Panel1->Left; //CL_DrawGrid->Left + Rect.Left;
  CL_DrawGrid->RowHeights[ARow] = panel->Height;
  }
}
//---------------------------------------------------------------------------
TCall_Panel* __fastcall TMainFormSLS::get_Call_Panel_By_Row(int ARow)
{
int t_tag = cps.get_panel_tag_by_row(ARow);
if(t_tag != -1)
  {
   for(int i = 0; i < ControlCount; i++)
      {
      TCall_Panel* Panel = dynamic_cast<TCall_Panel*>(Controls[i]);
      if(Panel)
        if(Panel->Tag == t_tag)
           return Panel;
       }
  }
return NULL;
}
//----------------------------------------------------------------------------
TCall_Panel* __fastcall TMainFormSLS::get_First_Call_Panel()
{
for(int i = 0; i < ControlCount; i++)
   {
   TCall_Panel* Panel = dynamic_cast<TCall_Panel*>(Controls[i]);
   if(Panel)
      return Panel;
   }
return NULL;
}
//----------------------------------------------------------------------------
TCall_Panel* __fastcall TMainFormSLS::get_Call_Panel_By_Tag(int tag)
{
for(int i = 0; i < ControlCount; i++)
   {
   TCall_Panel* Panel = dynamic_cast<TCall_Panel*>(Controls[i]);
   if(Panel)
    if(Panel->Tag == tag)
      return Panel;
   }
return NULL;
}
//----------------------------------------------------------------------------
TCall_Panel* __fastcall TMainFormSLS::get_Call_Panel_By_Sid(int sid)
{
for(int i = 0; i < ControlCount; i++)
   {
   TCall_Panel* Panel = dynamic_cast<TCall_Panel*>(Controls[i]);
   if(Panel)
    if(Panel->TFP.tfa.sid == sid)
       return Panel;
   }
return NULL;
}
//------------------------------------------------------------------------------
void __fastcall TContacts::CC_Display(TImageList* IL,TCanvas* GC,int row,TRect& Rect)
{
::EnterCriticalSection(&contlist_cs);
TCall_Panel* Panel = MainFormSLS->get_Call_Panel_By_Tag(MainFormSLS->CC_DrawGrid->Tag);
if(Panel)
  {
  TConfCont ConfCont = Panel->get_conf_contact_by_row(row);
  if(ConfCont.internal)
    {
    if(ConfCont.id != -1)
      {
      TContact contact(-1);
      if(get_contact_copy_by_id(contact, ConfCont.id))
        {
        switch(contact.cs){
           case ClientState_On_Line:
                IL->Draw(GC,get_state_left(Rect), get_top(Rect), 1, true);
                break;
           case ClientState_Away:
                IL->Draw(GC,get_state_left(Rect), get_top(Rect), 6, true);
                break;
           case ClientState_Off_Line:
                IL->Draw(GC,get_state_left(Rect), get_top(Rect), 3, true);
                break;
           }
        GC->TextOut(get_fname_left(Rect), get_top(Rect), contact.full_name.c_str());
        }
      }
    }
  else
    {
    GC->TextOut(get_fname_left(Rect), get_top(Rect), ConfCont.name.c_str());
    }
  }
::LeaveCriticalSection(&contlist_cs);
}
//------------------------------------------------------------------------------
void __fastcall TGroupChatStruct::Push(TGroupName& GName)
{
__GROUP_NAMES.push_back(GName);
}
//------------------------------------------------------------------------------
void __fastcall TGroupChatStruct::Delete(int ARow)
{
if(ARow < (int)__GROUP_NAMES.size())
  {
  int i = 0;
  deque<TGroupName>::iterator it = __GROUP_NAMES.begin();
  while(it != __GROUP_NAMES.end())
       {
       if(i == ARow)
         {
       __GROUP_NAMES.erase(it);
         MainFormSLS->CC_DrawGrid->RowCount = __GROUP_NAMES.size();
         break;
         }
       it++; i++;
       }
  }
}
//------------------------------------------------------------------------------
void __fastcall TGroupChatStruct::Display_Group_Chat(TCanvas* GC, int AROW, TRect& Rect)
{
TGroupName GName;
if(__get_chat_member_by_row(GName, AROW))
   GC->TextOut(__get_fname_left(Rect), __get_top(Rect), GName.s_full_name.c_str());
}
//------------------------------------------------------------------------------------
bool __fastcall TGroupChatStruct::InQueue(TGroupName& GName)
{
bool rv = false;
deque<TGroupName>::iterator it = __GROUP_NAMES.begin();
while(it != __GROUP_NAMES.end())
     {
     if((*it++).name == GName.name)
       {
       rv = true;
       break;
       }
     }
return rv;
}
//------------------------------------------------------------------------------------
TGroupName __fastcall TGroupChatStruct::Get()
{
TGroupName GName = __GROUP_NAMES.front();
__GROUP_NAMES.pop_front();
return GName;
}
//------------------------------------------------------------------------------------
deque<TGroupName>& __fastcall TGroupChatStruct::GetGroup()
{
return __GROUP_NAMES;
}
//------------------------------------------------------------------------------------
bool __fastcall TGroupChatStruct::__get_chat_member_by_row(TGroupName& GName, int AROW)
{
bool rv = false;
if(!__GROUP_NAMES.empty())
 if(AROW < (int)__GROUP_NAMES.size())
   {
   GName = __GROUP_NAMES[AROW];
   rv = true;
   }
return rv;
}
//------------------------------------------------------------------------------
bool __fastcall TGroupChatStruct::get_group_names(string& s)
{
bool rv = false;
while(!__GROUP_NAMES.empty())
     {
     TGroupName grn = __GROUP_NAMES.front();
   __GROUP_NAMES.pop_front();

   
     }
return rv;
}
//------------------------------------------------------------------------------
void __fastcall TMainFormSLS::CC_DrawGridDrawCell(TObject *Sender, int ACol,
      int ARow, TRect &Rect, TGridDrawState State)
{
/*
if(State.Contains(gdSelected))
  {
  CC_DrawGrid->Canvas->Brush->Color = (TColor)0x00DBDDBF; //(TColor)0x00DBCDBF;//clInactiveCaption; //clWhite;
  CC_DrawGrid->Canvas->Font->Color  = clWhite; //clBlack;
  CC_DrawGrid->Canvas->FillRect(Rect);

  }
else
*/
  {
//if(State.Contains(gdFocused))
//  {
  CC_DrawGrid->Canvas->Brush->Color = (TColor)0x00DBCDBF;//clWhite; //clInactiveCaption; //clWhite;
  CC_DrawGrid->Canvas->Font->Color  =  clWhite; //clBlack;
  CC_DrawGrid->Canvas->Font->Name = _font_name_Arial;
  CC_DrawGrid->Canvas->Font->Size = 10;
  CC_DrawGrid->Canvas->Font->Style = CC_DrawGrid->Canvas->Font->Style << fsBold;
  CC_DrawGrid->Canvas->FillRect(Rect);
  //CC_DrawGrid->Canvas->DrawFocusRect(Rect);
 // }
   }
if(GCS.CC_PANEL_TYPE == CC_PANEL_TYPE__GROUP_CREATE)
   GCS.Display_Group_Chat(CC_DrawGrid->Canvas, ARow, Rect);
else
  Sip->Contacts.CC_Display(MainFormSLS->ImageList1,CC_DrawGrid->Canvas,ARow,Rect);
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::CC_DrawGridMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
int ACol,ARow;
CC_DrawGrid->MouseToCell(X,Y,ACol,ARow);
if(ACol==-1)return;
if(ARow==-1)return;
CC_DrawGrid->Row = ARow;
Refresh_AddToConfBtnState();
}
//---------------------------------------------------------------------------
void __fastcall TCall_Panel::set_receiving_file_name_label()
{
string S;
if(MainFormSLS->lng == Lang_RU)
  S = "Файл: ";
else
  S = "File: ";
S += TFP.tfa.file_name  + "  ";
int f_size = 0;
string s_size;
if(TFP.tfa.file_size > 10000)
  {
  f_size = TFP.tfa.file_size/1000;
  s_size = " Kbyte";
  }
else
  {
  f_size = TFP.tfa.file_size;
  s_size = " Byte";
  }
S += inttostr(f_size) + s_size;
lb_1->Caption = S.c_str();
}
//----------------------------------------------------------------------------
void __fastcall TMainFormSLS::CC_DrawGridMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
int ACol,ARow;
CC_DrawGrid->MouseToCell(X,Y,ACol,ARow);
if(ACol != -1)
 if(ARow != -1)
   {
   if(GCS.CC_PANEL_TYPE == CC_PANEL_TYPE__GROUP_CREATE)
      GCS.Delete(ARow);
   else
     {
     TCall_Panel* Panel = get_Call_Panel_By_Tag(CC_DrawGrid->Tag);
     if(Panel)
       {
       TConfCont ConfCont = Panel->get_conf_contact_by_row(ARow);
       Panel->del_ccl_q_contact(ConfCont);
       }
     }
   }
MainFormSLS->CC_DrawGrid->Repaint();
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::append_active_call_to_conference(TCall_Panel* Panel_Conf_Creator,TUdpChannel* uc_creator,
                                                            const TConfCont& ConfCont, const string& callid)
{
TUdpChannel* uc_party   = NULL;
TMediaSession* ms_party = Sip->sss->GetMs_by_In_Out_Callid(callid);
if(ms_party)
  {
  uc_party = ms_party->getSoundChannel();
  Sip->sss->Connect_Conference_Channels(uc_creator,uc_party);
  Panel_Conf_Creator->add_ccl_contact(ConfCont);
  if(Panel_Conf_Creator->get_call_state() != Call_State__Conference)
     change_call_state_to_conference(Panel_Conf_Creator, Panel_Conf_Creator->Tag);
  int call_tag =  ms_party->getCallTag();
  TCall_Panel* Panel_Conf_Party = get_Call_Panel_By_Tag(call_tag);
  if(Panel_Conf_Party)
    {
    if(Panel_Conf_Party->get_call_state() != Call_State__Conference)
       change_call_state_to_conference(Panel_Conf_Party,Panel_Conf_Creator->Tag);
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::change_call_state_to_conference(TCall_Panel* call_panel,int conference_owner)
{
if(call_panel->get_call_state() == Call_State__Answer)
  {
  string s = call_panel->lb->Caption.c_str();
  int st = s.find(": ");
  if(st != -1)
     s.resize(st);
 // s += COLON + WS + "Конференция ";
  call_panel->lb->Caption = s.c_str();
  call_panel->lb_1->Caption = " Конференция ";
  call_panel->lb_1->Visible = true;
  }
else
  call_panel->lb_1->Caption = " Конференция ";
call_panel->set_conf_creator(conference_owner);
call_panel->set_call_state(Call_State__Conference);
}
//---------------------------------------------------------------------------
void __fastcall TCall_Panel::Btn_OpenFile__MouseUp(TObject *Sender,
                TMouseButton Button, TShiftState Shift, int X, int Y)
{
btn_1->OnMouseUp = NULL; //protect from double click and open duplicated document instance
//ShellExecute(Handle, "open", TFP.tfa.complete_file_name.c_str(), NULL, NULL, SW_SHOWMAXIMIZED);
ShellExecuteMy(TFP.tfa.complete_file_name.c_str());
MainFormSLS->push_req_to_del_call_panel(Tag);
}
//-----------------------------------------------------------------------------
void __fastcall TCall_Panel::Btn_Quit__MouseUp(TObject *Sender,
                TMouseButton Button, TShiftState Shift, int X, int Y)
{
MainFormSLS->push_req_to_del_call_panel(Tag);
}
//-----------------------------------------------------------------------------
void __fastcall TCall_Panel::transf_to_incoming()
{
lt = Lt_In;
disc_img->OnMouseUp = DiscImg_IncomingCall_Panel_MouseUp;
}
//-----------------------------------------------------------------------------
void __fastcall TCall_Panel::transf_to_outgoing()
{
lt = Lt_Out;
disc_img->OnMouseUp = DiscImg_OutgoingCall_Panel_MouseUp;
}
//-----------------------------------------------------------------------------
void __fastcall TMainFormSLS::OpenFileTransferDialog()
{
if(lng == Lang_RU)
  FileTransfer_Dialog->Title = "Отправить файл";
else
  FileTransfer_Dialog->Title = "File Transfer";
FileTransfer_Dialog->Options.Clear();
FileTransfer_Dialog->Options  << ofFileMustExist;// << ofAllowMultiSelect;
FileTransfer_Dialog->Filter = "All files (*.*)";
if(FileTransfer_Dialog->Execute())
  {
  TContact* Contact = NULL;
  if(Sip->Contacts.get_sorted_by_full_name())
     Contact = Sip->Contacts.get_contact_by_full_name(DrawGrid1->Row);
  else
     Contact = Sip->Contacts.get_contact_by_row(DrawGrid1->Row, false);
  if(Contact)
    {
    for(int i = 0; i < FileTransfer_Dialog->Files->Count; i++)
       {
       TTransferFileStruct tfs;
       tfs.contact = *Contact;
       tfs.path    = FileTransfer_Dialog->Files->Strings[i].c_str();
       Sip->tnl_add(tfs);
       }
    Sip->transmit_file_init();
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::Btn_SaveFileMouseUp(TObject *Sender,
                TMouseButton Button, TShiftState Shift, int X, int Y)
{
TButton* btn = (TButton*)Sender;
TCall_Panel* call_panel = get_Call_Panel_By_Tag(btn->Tag);
if(call_panel)
  {
  FileSave_Dialog->FileName = call_panel->TFP.tfa.file_name.c_str();
  if(FileSave_Dialog->Execute())
    {
    if(!call_panel->t_rcv_f)
       call_panel->t_rcv_f = new TReceiveFileThread(true,&ofs->elt,Sip);
    if(call_panel->t_rcv_f)
      {
      string path = FileSave_Dialog->FileName.c_str();
      int st = path.rfind("\\");
      if(st!=-1)
        {
        st++;
        call_panel->TFP.tfa.file_name = path.substr(st);
        path.resize(st);
        call_panel->TFP.tfa.path = path;
        }
      call_panel->t_rcv_f->set_sid(call_panel->TFP.tfa.sid);
      call_panel->t_rcv_f->set_host(Sip->FileTransfer.IPAddr);
      call_panel->t_rcv_f->set_port(Sip->FileTransfer.Port);
      call_panel->set_receiving_file_name_label();
      if(call_panel->t_rcv_f->Suspended)
         call_panel->t_rcv_f->Resume_Thread();
      }
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::Btn_CancelTransmitFile_MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
TButton* btn = (TButton*)Sender;
TEventLogThread* elt = MainFormSLS->ofs->elt;
TCall_Panel* panel = get_Call_Panel_By_Tag(btn->Tag);
if(panel)
  {
  TTransmitFileThread* ttf = panel->t_trn_f;
  if(ttf)
     ttf->set_cancel_req();
  }
TMediaSession* ms = Sip->sss->GetMs_by_Call_Tag(btn->Tag);
if(ms)
  {
  string callid = ms->getCallID();
  if(elt)
     elt->FputEvt("\nDISCONNECT callid " + callid);
  Sip->send_call_disc_out(callid, false);
  Sip->sss->EraseMediaSession(out_pref + callid); //ms deleted !!!
  }
push_req_to_del_call_panel(btn->Tag);
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::Btn_CancelReceiveFile_MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
TButton* btn = (TButton*)Sender;
TEventLogThread* elt = ofs->elt;
TCall_Panel* panel = get_Call_Panel_By_Tag(btn->Tag);
if(panel)
  {
  TReceiveFileThread* rft = panel->t_rcv_f;
  if(rft)
     rft->set_cancel_req();
  }
TMediaSession* ms = Sip->sss->GetMs_by_Call_Tag(btn->Tag);
if(ms)
  {
  string callid = ms->getCallID();
  if(elt)
     elt->FputEvt("\nDISCONNECT callid " + callid);
  Sip->send_call_disc_in(callid);
  Sip->sss->EraseMediaSession(in_pref + callid); //ms deleted !!!
  }
push_req_to_del_call_panel(btn->Tag);
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::Online1Click(TObject *Sender)
{
NS.init_notify_proc(ClientState_On_Line);
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::Away1Click(TObject *Sender)
{
NS.init_notify_proc(ClientState_Away);
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::DoNotDisturb1Click(TObject *Sender)
{
NS.init_notify_proc(ClientState_DND);
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::Offline1Click(TObject *Sender)
{
NS.init_notify_proc(ClientState_Off_Line);
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::Comment1Click(TObject *Sender)
{
open_NSCP();
}
 //-------------------------------------------------------------------------
void __fastcall TMainFormSLS::CommentClick(TObject *Sender)
{
if(NSP)
  if(!NSP->comment->Caption.IsEmpty())
    {
    AnsiString S;
    NSP->comment->Caption = S;

    NSP->comment->Visible = false;
    NSP->Height        = 20;
    PageControl1->Top  = NSP->Top + NSP->Height + 2;
    Panel3->Top        = PageControl1->Top;
    PageControl1_Resize();
   }
NS.my_net_state_comment_clear();
NS.init_notify_comment_proc(" ");
if(Im.LCFT)
  {
  TLCSBuf* LCSBuf = new TLCSBuf(CLEAR_COMMENT);
  if(LCSBuf)
     Im.LCFT->push_lcs_buf(LCSBuf);
  }
}
//----------------------------------------------------------------------------
void __fastcall TMainFormSLS::N4Click(TObject *Sender)
{
if(sound_tool)
  SoundTool->Hide();
SoundTool->Top  = Top  + Panel1->Top + Panel1->Height + 50;
SoundTool->Left = Left + Width/2 - SoundTool->Width/2;
SoundTool->start_type = 0;
SoundTool->Show();
sound_tool = true;
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::N5Click(TObject *Sender)
{
Sip->open_reg_win();
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::Open_Profile(bool start)
{
TContact* Contact = NULL;
if(Sip->Contacts.get_sorted_by_full_name())
   Contact = Sip->Contacts.get_contact_by_full_name(DrawGrid1->Row);
else
   Contact = Sip->Contacts.get_contact_by_row(DrawGrid1->Row,true);
if(Contact)
  {
  AnsiString Position = "Должность:";
  if(start)
    {
    if(ProfileForm)
       delete ProfileForm;
    ProfileForm = new TProfileForm(this,1);
    ProfileForm->Caption = "Личные данные";
    ProfileForm->Show();
    }
  else
    ProfileForm->Canvas->FillRect(Rect(0,0,ProfileForm->ClientWidth, ProfileForm->ClientHeight));

  ProfileForm->left_1 = 15; ProfileForm->left_2 = 150;  ProfileForm->font_sz = 10;
 // ProfileForm->Caption = " " + (AnsiString)Contact->full_name.c_str();
  ProfileForm->Canvas->Font->Name  = "Arial";
  ProfileForm->Canvas->Font->Size  = ProfileForm->font_sz;
  ProfileForm->Canvas->Font->Style = Canvas->Font->Style << fsBold;
  int top = 20,  height = Canvas->TextHeight(Position);

  int w = ProfileForm->Width - 2*ProfileForm->left_1, h = 1;
  TRBitMap rbmp(w, h, (TColor)0x00D0D0D0);
  rbmp.prepare_line_img();

  ProfileForm->PrintNickName(top, "Номер абонента:", Contact->name);
  ProfileForm->DrawUnderline(top, 2*height, rbmp);

  ProfileForm->PrintFullName(top, height, "Имя:", Contact->full_name.c_str());
  ProfileForm->DrawUnderline(top, height, rbmp);

  ProfileForm->PrintPosition(top, height, Position, Contact->position);
  ProfileForm->DrawUnderline(top, height, rbmp);
  }
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::Edit_Profile(bool start)
{
TContact* Contact = NULL;
if(Sip->Contacts.get_sorted_by_full_name())
   Contact = Sip->Contacts.get_contact_by_full_name(DrawGrid1->Row);
else
   Contact = Sip->Contacts.get_contact_by_row(DrawGrid1->Row,true);
if(Contact)
  {
  if(start)
    {
    if(ProfileForm)
       delete ProfileForm;
    ProfileForm = new TProfileForm(this,3);
    ProfileForm->EditProfile(Contact);
    ProfileForm->Show();
    }
  else
    ProfileForm->EditProfile_OnOpenWindow(Contact);
  }
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::Contact_Delete()
{
TContact* Contact = NULL;
if(Sip->Contacts.get_sorted_by_full_name())
   Contact = Sip->Contacts.get_contact_by_full_name(DrawGrid1->Row);
else
   Contact = Sip->Contacts.get_contact_by_row(DrawGrid1->Row,true);
if(Contact)
  {
  if(Contact->CT == ContactType_GROUP)
    {
    Sip->Contacts.del_group_contact_from_actual_contact_list(Contact);  //Delete from harddisk
    Sip->Contacts.del_contact(Contact->get_id());                       //Delete from memory
    Sip->Contacts.sort_by_full_user_name();
    return;
    }
  Sip->Contacts.del_contact_from_actual_contact_list(Contact);  //Delete from harddisk
  Sip->Contacts.del_contact(Contact->get_id());                 //Delete from memory
  TTransactionData data;
  data.u_1 = 1; //удалить из персонального контакт листа
  data.s_1 = Sip->Account.get_user_name();
  data.s_2 = Contact->name;
  Sip->Contacts.sort_by_full_user_name();
  if(Contact->CL == Location_EXT)
    EnterpriseSubscList->MODIFY_PERSONAL_CITY_PHONE_LIST(data);
  else
    EnterpriseSubscList->MODIFY_PERSONAL_CONTACT_LIST(data);
  }
}
//---------------------------------------------------------------------------

#ifdef SIP_Video
void __fastcall TMainFormSLS::VideoCall()
{
TContact ContCopy(-1);
if(MainFormSLS->Sip->Contacts.get_contact_copy_by_user_name(ContCopy, user_name_to_send))
  if(ContCopy.CT == ContactType_GROUP)
     return;
if(!Form4->Visible)
  {
    //if(Form4->devID == -1)
  //  {
    Form4->devID = -1;    //!!!
    vcam_init();
    Form4->select_vcam();
   // }
  if(Form4->devID != -1)
    {
    vcam_setup_device( Form4->devID,Form4->vcam_width,Form4->vcam_height);
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
    {
    if(Form4->venc_par.rgb24_yuv420_scalerId < 1)
       Form4->venc_par.rgb24_yuv420_scalerId = vencdec_create_scaler();
    if(Form4->venc_par.encoderId < 1)
       Form4->venc_par.encoderId = vencdec_create_encoder(Form4->net_width, Form4->net_height,5,max_video_payload_size);
    if((!Form4->bitmap->Width)||(!Form4->bitmap->Height))
      {
      Form4->set_bitmap_size();
      Form4->bitmap->PixelFormat = pf24bit;
      Form4->bitmap->Canvas->Brush->Style = bsSolid;
      }
    }
  Form3->LocalVideoPanel->Visible = true;
  if(!Form4->Timer1->Enabled)
     Form4->Timer1->Enabled = true;
  }
Form4->start_video_call();
}
#endif
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::Conference_Collect()
{
int width  = 2*Panel1->Width/3; //Panel1->Width - 8;
int height = 2*(Panel_Chat->Top - Panel1->Top - Panel1->Height)/3;  //Panel_Chat->Top - Panel1->Top - Panel1->Height;
if(!SCP)
   {
   SCP = new TServConf_Panel(this,lng,width,height);
   SCP->Parent = this;
   }
SCP->Top    = Panel1->Top  + Panel1->Height;
SCP->Left   = Panel2->Left + Panel2->Width;
SCP->Width  = width;
SCP->Height = height;
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::Close_Conf_Panel()
{
if(SCP)
  {
  delete SCP;
  SCP = NULL;
  }
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::N6Click(TObject *Sender)
{
Transport->Top  = Top  + Panel1->Top + Panel1->Height + 50;
Transport->Left = Left + Width/2 - Transport->Width/2;
switch(Sip->sip_transport){
      case Sip_Transport_UDP:
           if(Sip->Sip_TransportAuto)
             Transport->ComboBox1->ItemIndex = 4;
           else
             Transport->ComboBox1->ItemIndex = 0;
           break;
      case Sip_Transport_TCP:
           Transport->ComboBox1->ItemIndex = 1;
           break;
      case Sip_Transport_TLS:
           Transport->ComboBox1->ItemIndex = 2;
           break;
      case Sip_Transport_TUNNEL:
           Transport->ComboBox1->ItemIndex = 3;
           break;
      }
Transport->Show();
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::FormMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
if(X > (Width - 30))
 if(Button == mbRight)
  if(Shift.Contains(ssCtrl))
    if(Shift.Contains(ssAlt))
      {
      Test->Show();
      return;
      }
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::TestSound1Click(TObject *Sender)
{
TTest_Sound->Show();
}
//---------------------------------------------------------------------------
void __fastcall TOutPutDtmfBlock::first_byte(UBYTE a)
{
v.push_back(a);
}
//---------------------------------------------------------------------------
void __fastcall TOutPutDtmfBlock::second_byte(bool end, int volume)
{
UBYTE a = volume & 0x3F;
if(end)
   a |= 0x80;
v.push_back(a);
}
//---------------------------------------------------------------------------
void __fastcall TOutPutDtmfBlock::dig_duration(XBYTE a)
{
v.push_back(a >> 8);
v.push_back(a);
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
if(Key == 27)
  {
  }
}
//---------------------------------------------------------------------------
TOutPutDtmfBlock* __fastcall TMainFormSLS::exsCreateOutPutDtmfBlock(int& n,DtmfTransmitType DTT,
                                                                    unsigned short DURATION,int EVENT_DURATION,
                                                                    int MARKER,int PAYLOADTYPE)
{
TOutPutDtmfBlock* opd = new TOutPutDtmfBlock(n,DTT,DURATION,EVENT_DURATION,MARKER,PAYLOADTYPE);
#ifdef TOutPutDtmfBlock_Create
if(opd)
   MainFormSLS->Sip->Log("\nCreated TOutPutDtmfBlock #" + inttostr(opd->getBlockCount()));
#endif
return opd;
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::end_of_playing_reorder()
{
for(int i = 0; i < ControlCount; i++)
   {
   TCall_Panel* Panel = dynamic_cast<TCall_Panel*>(Controls[i]);
   if(Panel)
      if(Panel->get_call_state() == Call_State__NotAcceptable)
         {
         TDateTime dt = dt.CurrentDateTime();
         if((dt - Panel->get_start_time_play_sound()) > TDateTime(0,0,3,0))
           {
           TMediaSession* ms = Sip->sss->GetMs_by_Call_Tag(Panel->Tag);
           if(ms)
             {
             string out_callid = out_pref + ms->getCallID(); //Sip->getCallID_CLD_tc(ms->username);
             Sip->del_CLD_tc(ms->get_uniq_username());
             push_req_to_del_call_panel(ms->getCallTag());
             Sip->sss->EraseMediaSession(out_callid);       //ms deleted !!!
             }
           }
         }
   }
}
//------------------------------------------------------------------------------
void __fastcall TMainFormSLS::end_of_playing_busy()
{
for(int i = 0; i < ControlCount; i++)
   {
   TCall_Panel* Panel = dynamic_cast<TCall_Panel*>(Controls[i]);
   if(Panel)
      if(Panel->get_call_state() == Call_State__Busy)
         {
         TDateTime dt = dt.CurrentDateTime();
         if((dt - Panel->get_start_time_play_sound()) > TDateTime(0,0,4,0))
           {
           TMediaSession* ms = Sip->sss->GetMs_by_Call_Tag(Panel->Tag);
           if(ms)
             {
             string out_callid = out_pref + ms->getCallID(); //Sip->getCallID_CLD_tc(ms->username);
             Sip->del_CLD_tc(ms->get_uniq_username());
             push_req_to_del_call_panel(ms->getCallTag());
             Sip->sss->EraseMediaSession(out_callid);       //ms deleted !!!
             }
           }
         }
   }
}
//---------------------------------------------------------------------------
bool __fastcall TSysTimer::day_end()
{
bool rv = false;
TDateTime dt = dt.CurrentTime();
if(dt < time_stamp)
   rv = true;
time_stamp = dt;
return rv;
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::StartOptionsClick(TObject *Sender)
{
StartOptionsWin->Top  = Top  + Panel1->Top + Panel1->Height + 50;
StartOptionsWin->Left = Left + Width/2 - StartOptionsWin->Width/2;
if(lng == Lang_RU)
  {
  StartOptionsWin->Caption = "Старт программы";
  StartOptionsWin->CheckBox1->Caption = "Запускать Contact при старте Windows  ";
  }
else
  {
  StartOptionsWin->Caption = "Start Options";
  StartOptionsWin->CheckBox1->Caption = "Launch Contact with Windows start  ";
  }
StartOptionsWin->Show();
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::Memo1KeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
if(Key == 13)
   {
   if((Shift.Contains(ssCtrl))||(Shift.Contains(ssAlt)))
     return;

   if(get_IM_to_conf_participants())
     {
     send_IM_to_conference_participants();
     return;
     }

   if(get_IM_to_chat_participants())
     {
     send_IM_to_chat_participants();
     return;
     }

   vector<string> v;
   if(Im.remote_im_client.empty())
     {
     TContact* Contact = read_send_strings__for_client_list_participant(v);
     if(Contact)
       IM_Send(Contact,v);
     }
   else
     {
     read_send_strings__for_non_client_list_participant(v);
     TContact Cont;
     Cont.name = Im.remote_im_client;
     IM_Send(&Cont,v);
     }
   }
if(Key == 113) //F2
   Memo_Chat->Clear();
}
//---------------------------------------------------------------------------
void __fastcall TImStr::__clear_issl_m()
{
while(!issl_m.empty())
     {
     TImSubStrList::iterator it = issl_m.begin();
     TImSubStr* iss = (*it).second;
     if(iss)
        delete iss;
     issl_m.erase(it);
     }
__subs_id_m = 0;
}
//---------------------------------------------------------------------------
bool __fastcall TImStr::read_time_stmp(FILE* f)
{
bool rv = false;
char buf[64];
while(fgets(buf,64,f) != NULL)
  {
  string s = string(buf);
  if(s.empty())
     continue;
  int st = s.find(_tstmp);
  if(st == -1)
    {
    st = s.find(_TYPE);
    if(st != -1)
       return false;   //found new Start block
    continue;
    }
  st += _tstmp_len;
  int en = s.find(_lf,st-1); // st-1 - protection from out of range string
  if(st < en)
    {
    s = s.substr(st,en-st);
    en -= st;
    st = s.find(":");
    if(st != -1)
      {
      string hour = s.substr(0,st);
      st++;
      if(st < en)
        {
        string min      = s.substr(st);
        systime.wHour   = strtoint(hour);
        systime.wMinute = strtoint(min);
        time_stmp_to_str();
        rv = true;
        break;
        }
      }
    }
  }
return rv;
}
//--------------------------------------------------------------------------
void __fastcall TImStr::read_time_stmp(string& s)
{
int st = s.find(_tstmp);
if(st == -1)
  {
  st = s.find(_TYPE);
  if(st != -1)
     return;   //found new Start block
  }
st += _tstmp_len;
int en = s.find(_lf,st-1); // st-1 - protection from out of range string
if(st < en)
  {
  s = s.substr(st,en-st);
  en -= st;
  st = s.find(":");
  if(st != -1)
    {
    string hour = s.substr(0,st);
    st++;
    if(st < en)
      {
      string min      = s.substr(st);
      systime.wHour   = strtoint(hour);
      systime.wMinute = strtoint(min);
      time_stmp_to_str();
      }
    }
  }
}
//--------------------------------------------------------------------------
void __fastcall TImStr::time_stmp_to_str()
{
if(systime.wHour < 10)
  {
  t_stmp  = WS + "0";
  t_stmp += inttostr(systime.wHour) + COLON;
  }
else
  t_stmp = WS + inttostr(systime.wHour) + COLON;
if(systime.wMinute < 10)
   t_stmp += "0";
t_stmp += inttostr(systime.wMinute);
}
//--------------------------------------------------------------------------
void __fastcall TImStr::addSubStr(TImSubStr* iss)
{
::EnterCriticalSection(&issl_cs);
  __issl.insert(TImSubStrList::value_type(__subs_id++, iss));
::LeaveCriticalSection(&issl_cs);  
}
//-------------------------------------------------------------------------
void __fastcall TIM_Struct::insert_date_string(const SYSTEMTIME& systime)
{
TImStr* IS = new TImStr(IM_TEXT_TYPE_DATE);
if(IS)
  {
  vector<string> v;
  string s = inttostr(systime.wDay) + WS + month_to_str(systime.wMonth, MainFormSLS->lng) + WS + inttostr(systime.wYear);
  v.push_back(s);
  IS->hstry_substrs(v);
  addStr_by_read_hstry_block(IS);
  }
}
//--------------------------------------------------------------------------
void __fastcall TIM_Struct::read_user_history(FILE* f, const string& contact_name, const string& year_month_day)
{
while(_read_history_block(f, contact_name, year_month_day));
}
//--------------------------------------------------------------------------
bool __fastcall TIM_Struct::_read_history_block(FILE* f, const string& contact_name, const string& year_month_day)
{
bool rv = false;
im_text_type imtt = im_text_type_ndef;
unsigned sz;
if(_find_start_of_block(imtt,f))
  {
  switch(imtt){
        case IM_CALL_IN_MISSED:
        case IM_CALL_IN_DECLINED:
        case IM_CALL_OUT_NO_ANSWER:
        case IM_CALL_OUT_BUSY:
        case IM_CALL_OUT_NOT_ACCEPTABLE:{
             TImStr* IS = new TImStr(imtt);
             if(IS)
               {
               IS->set_contact_name(contact_name);
               IS->set_year_month_day(year_month_day);
               IS->hstry_add_empty_substr();
               IS->hstry_tstmp(f);
               addStr_by_read_hstry_block(IS);
               }
             return true;
             }
            /*
        case IM_INVITE_ON_FILE_RECEIVING:         //Читается ниже, в общем блоке
             {
             TImStr* IS = new TImStr(imtt);
             if(IS)
               {
               IS->set_contact_name(contact_name);
               IS->set_year_month_day(year_month_day);
               if(_get_block_size(sz,f))
                 {
                 vector<string> v;
                 if(_read_block_content(v,sz,f))
                   IS->hstry_substrs(v);
                 }
               IS->hstry_tstmp(f);
               addStr_by_read_hstry_block(IS);
               }
             return true;
             }
             */
             /*
        case IM_INVITE_ON_FILE_SENDING:           //Читаеся ниже, в общем блоке
             {

             int a = 5;
             return true;
             }
             */
        case IM_CALL_IN_ANSWERED:
        case IM_CALL_OUT_ANSWERED:{
             TImStr* IS = new TImStr(imtt);
             if(IS)
               {
               IS->set_contact_name(contact_name);
               IS->set_year_month_day(year_month_day);
               IS->hstry_add_empty_substr();
               string tstmp;
               IS->hstry_call_duration(f,tstmp);
               if(!tstmp.empty())
                 IS->read_time_stmp(tstmp);
               else
                 IS->hstry_tstmp(f);
               addStr_by_read_hstry_block(IS);
               }
             return true;
             }
        case IM_TEXT_TYPE_REM_ADDR:
        case IM_TEXT_TYPE_LOCAL_ADDR:{
             TImStr* IS = new TImStr(imtt);
             if(IS)
               {
               IS->set_contact_name(contact_name);
               IS->set_year_month_day(year_month_day);
               IS->hstry_add_empty_substr();
               addStr_by_read_hstry_block(IS);
               }
             return true;
             }
        }
  if(_get_block_size(sz,f))                              //Здесь загружаютс также IM_INVITE_ON_FILE_RECEIVING, IM_INVITE_ON_FILE_ЫУТВШТП
    {
    if(imtt != im_text_type_ndef)
      {
      vector<string> v;
      if(_read_block_content(v,sz,f))
        {
        if(!v.empty())
          {
          TImStr* IS = new TImStr(imtt);
          if(IS)
            {
            IS->set_contact_name(contact_name);
            IS->set_year_month_day(year_month_day);
            switch(imtt){
                  case IM_TEXT_TYPE_LOCAL_IM:{
                       int sz = v.size();
                       for(int i = 0; i < sz; i++)
                          {
                          if(!IS->get_href())
                              IS->check_local_im_substr_on_ref(v[i]);
                          else
                              break;
                          }
                       break;
                       }
                  case IM_TEXT_TYPE_REMOTE_IM:{
                       int sz = v.size();
                       for(int i = 0; i < sz; i++)
                          {
                          if(!IS->get_href())
                              IS->check_remote_im_substr_on_ref(v[i]);
                          else
                              break;
                          }
                       break;
                       }
                  }
            IS->hstry_substrs(v);
            IS->hstry_tstmp(f);
            addStr_by_read_hstry_block(IS);
            }
          }
        }
      }
    } //if(_get_block_size(sz,f))
  rv = true;
  }
return rv;
}
//------------------------------------------------------------------------------
//-- Применяется только в основном потоке --------------------------------------
//------------------------------------------------------------------------------
void __fastcall TImStr::SET_ROW_HEIGHT(int row)
{
switch(__im_tt){
      case IM_TEXT_TOP_STRING:
           set_top_row_height();
           return;
      case IM_CALL_IN_DECLINED:
      case IM_CALL_IN_MISSED:
      case IM_CALL_IN_ANSWERED:
      case IM_CALL_OUT_NO_ANSWER:
      case IM_CALL_OUT_ANSWERED:
      case IM_CALL_OUT_BUSY:
      case IM_CALL_OUT_NOT_ACCEPTABLE:{
           MainFormSLS->IM_DrawGrid->RowHeights[row] = 32;
           return;
           }
      }

if(__im_tt == IM_TEXT_TYPE_REMOTE_IM)
   MainFormSLS->IM_DrawGrid->RowHeights[row] = __calculate_row_height__INSTANT_MESSAGE(MainFormSLS->IM_DrawGrid->DefaultRowHeight);
else if(__im_tt == IM_TEXT_TYPE_LOCAL_IM)
   MainFormSLS->IM_DrawGrid->RowHeights[row] = __calculate_row_height__INSTANT_MESSAGE(MainFormSLS->IM_DrawGrid->DefaultRowHeight);
else if(__im_tt == IM_INVITE_ON_FILE_RECEIVING)
   MainFormSLS->IM_DrawGrid->RowHeights[row] = 54;
else if(__im_tt == IM_INVITE_ON_FILE_SENDING)
   MainFormSLS->IM_DrawGrid->RowHeights[row] = 54;
else
   MainFormSLS->IM_DrawGrid->RowHeights[row] = __calculate_row_height(MainFormSLS->IM_DrawGrid->DefaultRowHeight);
}
//------------------------------------------------------------------------------
void __fastcall TImStr::hstry_add_empty_substr()
{
vector<string> v;
v.push_back(" ");
hstry_substrs(v);
}
//------------------------------------------------------------------------------
void __fastcall TImStr::hstry_substrs(const vector<string>& v)
{
int sz = v.size();
for(int i = 0;i < sz;i++){
   TImSubStr* ISS = new TImSubStr;
   if(ISS)
     {
     ISS->s = v[i];
     if(__im_tt == IM_TEXT_TYPE_REM_ADDR)
        ISS->font_color = (TColor)turquoise_color;
     else if(__im_tt == IM_TEXT_TYPE_LOCAL_ADDR)
        ISS->font_color = clGray;
     addSubStr(ISS);
     }
   }
}
//--------------------------------------------------------------------------
void __fastcall TImStr::hstry_tstmp(FILE* f)
{
switch(__im_tt){
      case IM_TEXT_TYPE_LOCAL_IM:
      case IM_TEXT_TYPE_REMOTE_IM:
      case IM_INVITE_ON_FILE_RECEIVING:
      case IM_INVITE_ON_FILE_SENDING:      
      case IM_CALL_IN_DECLINED:
      case IM_CALL_IN_MISSED:
      case IM_CALL_IN_ANSWERED:
      case IM_CALL_OUT_NO_ANSWER:
      case IM_CALL_OUT_BUSY:
      case IM_CALL_OUT_ANSWERED:
      case IM_CALL_OUT_NOT_ACCEPTABLE:
           read_time_stmp(f);
           break;
      }
}
//--------------------------------------------------------------------------
void __fastcall TImStr::hstry_call_duration(FILE* f,string& tstmp)
{
char buf[64];
if(fgets(buf,64,f) != NULL)
  {
  string s = string(buf);
  if(!s.empty())
    {
    int st = s.find(_durtn);
    if(st == -1)
      {
      st = s.find(_tstmp);
      if(st != -1)
        tstmp = s;
      return;
      }
    st += _durtn_len;
    int en = s.find(_lf,st-1); // st-1 - protection from out of range string
    if(st < en)
      t_duration = s.substr(st,en-st);
    }
  }
}
//--------------------------------------------------------------------------
bool __fastcall TIM_Struct::_find_start_of_block(im_text_type& type,FILE* f)
{
bool rv = false;
char buf[512];
while(fgets(buf,512,f) != NULL)  // Если буфера не хватает, то будет считано 511 символов, но в конце будет обязательно 0!!!
     {
     string s = string(buf);
     if(!s.empty())
       if(!s.find(_TYPE))  //с позиции 0!!!
         {
         _erase_trail(s);
         int ln = s.length();
         int st = s.find(":");
         if(st != -1)
           {
           st++;
           if(st < ln)
             {
             type = _int_to_im_text_type(strtoint(s.substr(st)));
             rv = true;
             break;
             }
           }
         }
     }
return rv;
}
//------------------------------------------------------------------------------
im_text_type __fastcall TIM_Struct::_int_to_im_text_type(int a)
{
im_text_type rv = im_text_type_ndef;
if(a >= 0)
  if(a < im_text_type_ndef)
     rv = (im_text_type)a;
return rv;
}
//------------------------------------------------------------------------------
bool __fastcall TIM_Struct::_get_block_size(unsigned& block_sz,FILE* f)
{
bool rv = false;
char buf[512];
if(fgets(buf,512,f) != NULL)
  {
  string s = string(buf);
  if(!s.empty())
    if(!s.find("sz:"))  //с позиции 0!!!
      {
      _erase_trail(s);
      int ln = s.length();
      int st = s.find(":");
      if(st != -1)
        {
        st++;
        if(st < ln)
          {
          s = s.substr(st);
          block_sz = strtoint(s);
         // if(block_sz)
          rv = true;
          }
        }
      }
  }
return rv;
}
//-----------------------------------------------------------------------------
bool __fastcall TIM_Struct::_read_block_content(vector<string>& v, unsigned sz, FILE* f)
{
bool rv = true;
char buf[1024];
for(unsigned i = 0; i < sz; i++)
   {
   if(fgets(buf, 1024, f) == NULL)
     {
     rv = false;
     break;
     }
   string s = string(buf);
  _erase_trail(s);
   if(!s.empty())
      v.push_back(s);
   }
return rv;
}
//---------------------------------------------------------------------------
//-- This func MUST be used in main proc thread only  -----------------------
//---------------------------------------------------------------------------
void __fastcall TIM_Struct::_erase_trail(string& s)
{
int st = s.rfind(_lf);
if(st != -1)
   s.resize(st);
}
//---------------------------------------------------------------------------
//-- This func MUST be used in main proc thread only  -----------------------
//---------------------------------------------------------------------------
void __fastcall TIM_Struct::load_user_history()
{
_clear_im_str_list();
if(!selected_remote_user.empty())
  {
  SYSTEMTIME systime;
  ::GetLocalTime(&systime);
  USER_HSTRY_LOAD(systime, systime);
  }
}
//--------------------------------------------------------------------------
void __fastcall TIM_Struct::load_user_history(TDateTime& START, TDateTime& END)
{
_clear_im_str_list();
if(!selected_remote_user.empty())
  {
  SYSTEMTIME start;
  START.DecodeDate(&start.wYear,&start.wMonth,&start.wDay);
  SYSTEMTIME end;
  END.DecodeDate(&end.wYear,&end.wMonth,&end.wDay);
  USER_HSTRY_LOAD(start, end);
  }
}
//--------------------------------------------------------------------------
void __fastcall TCallTstmp::get_tstmp()
{
if(!ready)
  {
  tstmp = tstmp.CurrentDateTime();
  ready = true;
  }
}
//---------------------------------------------------------------------------
void __fastcall TTstmps::get_conv_start_tstmp()
{
conv_start.get_tstmp();
}
//----------------------------------------------------------------------------
void __fastcall TTstmps::get_conv_stop_tstmp()
{
conv_stop.get_tstmp();
}
//----------------------------------------------------------------------------
void __fastcall TTstmps::get_conv_duration()
{
get_conv_stop_tstmp();
if(!conv_duration.get_ready())
  if(conv_stop.get_ready())
    if(conv_start.get_ready())
      {
      conv_duration.duration = conv_stop.tstmp - conv_start.tstmp;
      conv_duration.duration_to_str();
      conv_duration.set_ready();
      }
}
//----------------------------------------------------------------------------
void __fastcall TCallDuration::duration_to_str()
{
unsigned short hour;
unsigned short min;
unsigned short sec;
unsigned short msec;
duration.DecodeTime(&hour,&min,&sec,&msec);
if(hour)
   s_duration += inttostr(hour) + ":";
string s = inttostr(min);
if(s.length() < 2)
   s_duration += "0" + s;
else
   s_duration += s;
s_duration += ":";
s = inttostr(sec);
if(s.length() < 2)
   s_duration += "0" + s;
else
   s_duration += s;
}
//------------------------------------------------------------------------------
TForm1* __fastcall TInCallBlock::new_incoming_call(const string& call_id)
{
TForm1* form = NULL;
if(icl.find(call_id) == icl.end())
  {
  form = new TForm1(MainFormSLS);
  if(form)
    {
    set_new_call_window_coord(form);
    icl_ins(call_id, form);
    }
  }
return form;
}
//------------------------------------------------------------------------------
void __fastcall TInCallBlock::set_new_call_window_coord(TForm1* form)
{
if(ordl.empty())
  form->Position = poScreenCenter;
else
  {
  int top,left = 0;
  get_prev_call_window_coord(top,left);
  form->Top = top + 30; form->Left = left + 20;
  }
}
//------------------------------------------------------------------------------
void __fastcall TInCallBlock::icl_ins(const string& call_id, TForm1* f)
{
ordl.insert(TOrderList::value_type(++order,call_id));
f->set_order(order);
f->callid = call_id;
icl.insert(TInCallList::value_type(call_id,f));
}
//------------------------------------------------------------------------------
void __fastcall TInCallBlock::icl_del(const string& call_id)
{
TInCallList::iterator it = icl.find(call_id);
if(it != icl.end())
  {
  ordl_del((*it).second->get_order());
  icl.erase(it);
  }
}
//-----------------------------------------------------------------------------
void __fastcall TInCallBlock::ordl_del(unsigned ORDER)
{
TOrderList::iterator it = ordl.find(ORDER);
if(it != ordl.end())
   ordl.erase(it);
if(ordl.empty())
   order = 0;
}
//------------------------------------------------------------------------------
void __fastcall TInCallBlock::get_prev_call_window_coord(int& top, int& left)
{
TOrderList::reverse_iterator it = ordl.rbegin();
if(it != ordl.rend())
  {
  TForm1* form = get_form_by_call_id((*it).second);
  if(form)
    {
    top  = form->Top;
    left = form->Left;
    form->Caption = form->Label1->Caption;
    }
  }
}
//------------------------------------------------------------------------------
TForm1* __fastcall TInCallBlock::get_form_by_call_id(const string& call_id)
{
TForm1* rv = NULL;
TInCallList::iterator it = icl.find(call_id);
if(it != icl.end())
   rv = (*it).second;
return rv;
}
//------------------------------------------------------------------------------
void __fastcall TInCallBlock::__get_all_waiting_callids(queue<string>& q)
{
TInCallList::iterator it = icl.begin();
while(it != icl.end())
      q.push((*it++).first);
}
//------------------------------------------------------------------------------
void __fastcall TInCallBlock::req_to_del_in_call_window_on_receiving_CANCEL(const string& call_id)
{
int sz = icl.size();
if(sz < 2)
  MainFormSLS->PlaySound_Free();
TInCallList::iterator it = icl.find(call_id);
if(it != icl.end())
  {
  if((*it).second->connected_to_pph)
    {
    string call_id_pph = (*it).second->callid_pph;
    MainFormSLS->Sip->send_call_disc_out(call_id_pph, true);
    MainFormSLS->Sip->sss->EraseMediaSession(out_pref + call_id_pph);
    }
  (*it).second->closed_by_btn = true;
  (*it).second->Close();
  }
}
//------------------------------------------------------------------------------
void __fastcall TInCallBlock::del_all_waiting_ans_calls()
{
if(MainFormSLS->Sip)
  {
  queue<string> q;
__get_all_waiting_callids(q);
  while(!q.empty())
       {
       string callid = q.front();
       q.pop();
       if(MainFormSLS->Sip->uas)
         {
         TExchBuf* buf = new TExchBuf(WM_APP_MSG_WPARAM__UAS);
         if(buf)
           {
           buf->emt = ExchMsgType_CANCEL;
           buf->msg = callid;
           MainFormSLS->Sip->uas->insertExchLst(buf);
         ::PostMessage(MainFormSLS->Handle, SIP_UA_MSG, WM_APP_MSG_WPARAM__UAS, WM_APP_MSG_LPARAM__READLIST);
           }
         }
       }
  }
}
//------------------------------------------------------------------------------
void __fastcall TMainFormSLS::Btn_SaveNumberMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
if(Panel_Dial->Visible)
  {
   Panel_Dial->Hide();
   restore_call_hstry();
  }
}
//---------------------------------------------------------------------------
//--- Network Status Panel for reflect my network status --------------------
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::Create_NSP()
{
NSP = new TNetStatus_Panel(Panel2);
NSP->Parent = Panel2;
NSP->BorderStyle = bsNone;
NSP->BevelInner  = bvNone;
NSP->BevelOuter  = bvNone;
NSP->Width  = Panel2->Width; // - 2;
NSP->Height = 20;
NSP->Top    = 2;
NSP->Color  = clWhite;
}
//------------------------------------------------------------------------------
void __fastcall TMainFormSLS::Create_DialPag_Panel()
{
DPP = new TDialPad_Panel(this);
DPP->Parent = this;
}
//-----------------------------------------------------------------------------
void __fastcall TMainFormSLS::INIT_NetState_Popup_Menu()
{
NetState_PopupMenu->Items->Items[0]->OnClick = Online1Click;
NetState_PopupMenu->Items->Items[1]->OnClick = Away1Click;
NetState_PopupMenu->Items->Items[2]->OnClick = DoNotDisturb1Click;
NetState_PopupMenu->Items->Items[3]->OnClick = Offline1Click;
NetState_PopupMenu->Items->Items[5]->OnClick = Comment1Click;
switch(lng){
      case Lang_RU: NetState_PopupMenu->Items->Items[0]->Caption = " В сети";
                    NetState_PopupMenu->Items->Items[1]->Caption = " Нет на месте";
                    NetState_PopupMenu->Items->Items[2]->Caption = " Не беспокоить";
                    NetState_PopupMenu->Items->Items[3]->Caption = " Не в сети";
                    NetState_PopupMenu->Items->Items[5]->Caption = "  Комментарий";
                    break;
           default: NetState_PopupMenu->Items->Items[0]->Caption = " Online";
                    NetState_PopupMenu->Items->Items[1]->Caption = " Away";
                    NetState_PopupMenu->Items->Items[2]->Caption = " Do Not Disturb";
                    NetState_PopupMenu->Items->Items[3]->Caption = " Offline";
                    NetState_PopupMenu->Items->Items[5]->Caption = "  Comment";
                    break;
      }
}
//------------------------------------------------------------------------------
void __fastcall TMainFormSLS::INIT_Comment_NetState_Popup_Menu()
{
Comment_NetState_PopupMenu->Items->Items[0]->OnClick = CommentClick;
switch(lng){
      case Lang_RU: Comment_NetState_PopupMenu->Items->Items[0]->Caption = " Удалить комментарий";
                    break;
           default: Comment_NetState_PopupMenu->Items->Items[0]->Caption = " Clear comment";
                    break;
      }              
}
//-----------------------------------------------------------------------------
void __fastcall TNetStatus_Panel::NSI_MouseMove(TObject *Sender, TShiftState Shift,
      int X, int Y)
{
Set_Focus();
}
//-----------------------------------------------------------------------------
void __fastcall TNetStatus_Panel::NSI_MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
if(Button == mbLeft)
   Set_Pressed();
}
//------------------------------------------------------------------------------
void __fastcall TNetStatus_Panel::NSP_MouseMove(TObject *Sender, TShiftState Shift,
      int X, int Y)
{
Clear_Focus();
}
//-----------------------------------------------------------------------------
void __fastcall TNetStatus_Panel::NSI_MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
if(ContactMenu->Visible)
   ContactMenu->Close();
if(Button == mbLeft)
  {
  MainFormSLS->close_NSCP();
  int x = ClientOrigin.x + NSI->Left;
  int y = ClientOrigin.y + Height;
  Clear_Focus();       //Do not replace below because Popup(x,y) is ShowModal process. Process suspended here but no blocking anather proc.(Incoming call processed OK)
  MainFormSLS->NetState_PopupMenu->Popup(x,y);
  }
if(Button == mbRight)
  MainFormSLS->open_NSCP();
}
//------------------------------------------------------------------------------
void __fastcall TNetStatus_Panel::Comment_MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
TLabel* lb = (TLabel*)Sender;
AnsiString S = lb->Caption;
if(!S.IsEmpty())
  {
  int x = ClientOrigin.x + comment->Left;
  int y = ClientOrigin.y + Height;
  MainFormSLS->Comment_NetState_PopupMenu->Popup(x,y);
  }
}
//------------------------------------------------------------------------------
void __fastcall TMainFormSLS::Panel2MouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
if(NSP)
   NSP->Clear_Focus();
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::Brand_ImageMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
if(NSP)
   NSP->Clear_Focus();
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::DrawGrid1MouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
if(NSP)
   NSP->Clear_Focus();

int ACol,ARow;
DrawGrid1->MouseToCell(X,Y,ACol,ARow);
if(ACol==-1)
  {
  DrawGrid1->Cursor = crDefault;
  return;
  }
if(ARow==-1)
  {
  DrawGrid1->Cursor = crDefault;
  return;
  }
DrawGrid1->Cursor = crHandPoint;
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::DG_LastCallsDrawCell(TObject *Sender,
      int ACol, int ARow, TRect &Rect, TGridDrawState State)
{
if(Sip->Contacts.LCS.get_block_repaint())
   return;

   /*
if(State.Contains(gdFocused))
  {
  DG_LastCalls->Canvas->Brush->Color = clActiveCaption; //clWhite; // clActiveCaption;//clBlue;// clBackground;
  DG_LastCalls->Canvas->Font->Color  = clWhite;
  DG_LastCalls->Canvas->FillRect(Rect);
  DG_LastCalls->Canvas->DrawFocusRect(Rect);
  Sip->Contacts.LCS.row_focused = ARow;
  }
else if(State.Contains(gdSelected))
   {
  DG_LastCalls->Canvas->Brush->Color = clWhite;//clActiveCaption; //clWhite; // clActiveCaption;//clBlue;// clBackground;
  DG_LastCalls->Canvas->Font->Color  = clWhite;
  DG_LastCalls->Canvas->FillRect(Rect);
  Sip->Contacts.LCS.row_focused = ARow;
  }
  */

if(State.Contains(gdFocused))
  {
  DG_LastCalls->Canvas->Brush->Color = clActiveCaption;   //clBlue;// clBackground;
  DG_LastCalls->Canvas->Font->Color  = clWhite;
  DG_LastCalls->Canvas->FillRect(Rect);
  DG_LastCalls->Canvas->DrawFocusRect(Rect);
  }

DG_LastCalls->Canvas->Font->Style = MainFormSLS->DG_LastCalls->Canvas->Font->Style << fsBold;  
Sip->Contacts.LCS.Display_LC(MainFormSLS->ImageList1,DG_LastCalls->Canvas,ACol,ARow,Rect,State);
}
//---------------------------------------------------------------------------
void __fastcall TNotifyStruct::Final_Notify_Proc()
{
init_notify_proc(ClientState_Terminated);
notify_subscribed_clients_about_change_network_status();
}
//-----------------------------------------------------------------------------
void __fastcall TMainFormSLS::FormPaint(TObject *Sender)
{
/*
if(DialPad->Visible)
  {
  DialPad->Top  = Panel1->ClientOrigin.y  + Panel1->Height;
  DialPad->Left = Panel1->ClientOrigin.x;
 }
 */
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::Close_All_Open_Window()
{
if(AboutWin)
  if(AboutWin->Visible)
     AboutWin->Hide();

if(DialPad)
  if(DialPad->Visible)
     DialPad->Hide_DPW();

if(SoundTool)
  if(SoundTool->Visible)
     SoundTool->Hide();

if(ContactMenu)
  if(ContactMenu->Visible)
     ContactMenu->Hide();

if(StartOptionsWin)
  if(StartOptionsWin->Visible)
     StartOptionsWin->Hide();

if(Transport)
  if(Transport->Visible)
     Transport->Hide();

if(ProfileForm)
  {
  TProfileForm* PF = ProfileForm;
  ProfileForm = NULL;
  delete PF;
  }

if(Sip)
   Sip->hide_registry_panel();

if(ParallelPhoneWin)
   ::PostMessage(ParallelPhoneWin, CONTROL_MSG, WM_APP_MSG_WPARAM__CLOSE_WINDOW, WM_APP_MSG_LPARAM__NOPARAM);
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::CC_EditKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
if(Key == 13) //Enter
  {
  AnsiString S = CC_Edit->Text;
  string s = S.c_str();
  if(!s.empty())
    {
    if(GCS.CC_PANEL_TYPE == CC_PANEL_TYPE__GROUP_CREATE)
      {
      TGroupName GName;
      GName.name      = s;
      GName.s_full_name = s;
      if(!GCS.InQueue(GName))
        {
        GCS.Push(GName);
        CC_DrawGrid->Repaint();
        }
      }
    else
      {
      add_dial_contact_to_conf_list(s);
      CC_DrawGrid->Repaint();
      }
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::add_dial_contact_to_conf_list(const string& s)
{
TCall_Panel* Panel = get_Call_Panel_By_Tag(CC_DrawGrid->Tag);
if(Panel)
  {
  TContact contact(-1);
  if(MainFormSLS->Sip->Contacts.get_contact_copy_by_user_name(contact,s))
    {
    TConfCont ConfCont(contact.get_id());
    ConfCont.user_name = contact.name;
    if(!Panel->is_ccl_q_contact(ConfCont)) //not yet in queue to the conference
       Panel->add_ccl_q_contact(ConfCont);
    }
  else //not contact from my contact list
    {
    TConfCont ConfCont(s);      //ConfCont.user_name = s inside constructor of TConfCont
    if(!Panel->is_ccl_q_contact(ConfCont)) //not yet in queue to the conference
       Panel->add_ccl_q_contact(ConfCont);
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::CC_ImgMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
if(GCS.CC_PANEL_TYPE == CC_PANEL_TYPE__GROUP_CREATE)
  {
  if(GCS.Size())
    {
    TContact* Contact = new TContact(Sip->Contacts.get_next_contact_id());
    if(Contact)
      {
      char buf[5] = {0xFF,0xFF,0xFF,0xFF,0};
      string pref = string(buf);
      string CLEAR_NAME;                               //without prefix
      Contact->generate_group_name(pref, CLEAR_NAME);  //Here assigned Contact->name
      unsigned ID              = Contact->get_id();
      string NAME              = Contact->name;        //with prefix
      Contact->CT              = ContactType_GROUP;
      Contact->GRNS.SET_GROUP(GCS.GetGroup());
      string full_name;
      while(GCS.Size())
           {
           TGroupName GName = GCS.Get();  //With erase element
           if(full_name.empty())
              full_name = GName.s_full_name;
           else
              full_name += ", " + WS + GName.s_full_name;
           }
      user_name_to_send = NAME;
      Contact->full_name       = pref + full_name;
      Contact->group_full_name = full_name;
      Sip->Contacts.add_group_contact_name_to_actual_directory(Contact);
      Sip->Contacts.add_contact(Contact, DrawGrid1, Sip->Contacts.get_sorted_by_full_name());
      group_chat_selected(Contact->group_full_name);
      Im.curr_hstry_period = -1;
      Im.set_selected_remote_user(user_name_to_send);
      Im.load_user_history();
      TContact ContCopy(-1);
      int row_id = Sip->Contacts.get_row_id_by_contact_name(NAME,ContCopy);
      if(Sip->Contacts.get_sorted_by_full_name())
         row_id = Sip->Contacts.get_row_by_contact_id_in_sorted_contact_list(ID);
      if(row_id != -1)
         if(row_id < DrawGrid1->RowCount)
           if(row_id)
              DrawGrid1->Row = row_id;
      deque<TGroupName> q;
      Contact->GRNS.GET_GROUP(q);
      Send_GroupChat_INFO_INIT(CLEAR_NAME, q);
      }
    }
  }
else
  {
  TCall_Panel* Panel_Conf_Creator = get_Call_Panel_By_Tag(CC_DrawGrid->Tag);
  if(Panel_Conf_Creator)
     AddToConference(Panel_Conf_Creator);
  }
CC_Panel->Hide();
}
//----------------------------------------------------------------------------
void __fastcall TMainFormSLS::AddToConference(TCall_Panel* Panel_Conf_Creator)
{
TUdpChannel* uc_creator = NULL;
SipUAThreadType uatt = SipUAThreadType_UAC;
if(Panel_Conf_Creator->get_leg_type() == Lt_In)
   uatt = SipUAThreadType_UAS;
TMediaSession* ms_creator = Sip->sss->GetMs_by_Call_Tag(Panel_Conf_Creator->Tag);
if(ms_creator)
  {
  uc_creator = ms_creator->getSoundChannel();
  if(uc_creator)
     if(Panel_Conf_Creator->ccl_empty())
        if(uc_creator->mic)
          {
           uc_creator->mic->ch_conference_bridge      = true;
           uc_creator->mic->ch_conference_participant = true;
          }
  }
int conf_q_sz = Panel_Conf_Creator->get_ccl_q_size();
if(!conf_q_sz)
  {
  AnsiString S = CC_Edit->Text;
  string s = S.c_str();
  if(!s.empty())
    {
    add_dial_contact_to_conf_list(s);
    conf_q_sz = Panel_Conf_Creator->get_ccl_q_size();
    }
  }
for(int i = 0; i < conf_q_sz; i++)
  {
  TConfCont ConfCont = Panel_Conf_Creator->get_first_ccl_q_contact();
  if(ConfCont.internal)
    {
    if(ConfCont.id != -1)
      {
      TContact ContCopy(-1);
      if(Sip->Contacts.get_contact_copy_by_id(ContCopy,ConfCont.id))
        {
        string callid = Sip->getCallID_CLD_tc(ContCopy.name);
        if(callid.empty())
          {
          user_name_to_send      = ContCopy.name;
          ComboBox1->Text        = ContCopy.full_name.c_str();
          CalledNameLbl->Caption = ContCopy.full_name.c_str();
          StartOutgoingCall_OnConferenceCreate(&ConfCont, Panel_Conf_Creator->Tag); //send INVITE to new participant. CallID to ConfCont set inside this func
          if(Panel_Conf_Creator->ccl_empty()) //Добавить в созданную конференцию called_party вызова из которого создавалась конференция
            if(!Panel_Conf_Creator->nick_name.empty())
              if(ms_creator)
                {
                TContact ContCopy_0(-1);
                if(Sip->Contacts.get_contact_copy_by_user_name(ContCopy_0, Panel_Conf_Creator->nick_name))
                  {
                  TConfCont ConfCont_0(ContCopy_0.get_id());
                  ConfCont_0.callid             = ms_creator->getCallID();
                  ConfCont_0.user_name          = ContCopy_0.name;
                  ConfCont_0.call_panel_tag     = Panel_Conf_Creator->Tag;
                  if(Panel_Conf_Creator->get_call_state() == Call_State__Answer)
                     ConfCont_0.cc_call_state = 1;
                  Panel_Conf_Creator->add_ccl_contact(ConfCont_0);
                  SendConference_INFO_INIT(Panel_Conf_Creator->get_leg_type(), ConfCont_0); //Send INFO msg to first answered to conference creator contact
                  Add_Participant_To_ConfCreator_Window(ConfCont_0, uatt);
                  }
                else   //Contact with Panel_Conf_Creator->nick_name is absent in  local contact list. This is external contact.
                  {
                  TConfCont ConfCont_0(Panel_Conf_Creator->nick_name);
                  ConfCont_0.callid             = ms_creator->getCallID();
                  ConfCont_0.user_name          = Panel_Conf_Creator->nick_name;
                  ConfCont_0.call_panel_tag     = Panel_Conf_Creator->Tag;
                  if(Panel_Conf_Creator->get_call_state() == Call_State__Answer)
                     ConfCont_0.cc_call_state = 1;
                  Panel_Conf_Creator->add_ccl_contact(ConfCont_0);
                  SendConference_INFO_INIT(Panel_Conf_Creator->get_leg_type(), ConfCont_0); //Send INFO msg to first answered to conference creator contact
                  Add_Participant_To_ConfCreator_Window(ConfCont_0, uatt);
                  }
                } //if(ms_creator)
          deque<TConfCont> ccl_t;
          Panel_Conf_Creator->get_ccl_copy(ccl_t);          //get copy of conference participants list before add new contact
          Panel_Conf_Creator->add_ccl_contact(ConfCont);    //add ConfCont of the new participant
          SendConference_INFO_About_NEW_Participant_to_ALL_participants(Panel_Conf_Creator->get_leg_type(), Panel_Conf_Creator, ConfCont, ccl_t); //Send INFO msg to all answered conference participants (excluding conference_creator and new participant) about new participant
          Add_Participant_To_ConfCreator_Window(ConfCont, SipUAThreadType_UAC);
          } //if(callid.empty())
        else
          append_active_call_to_conference(Panel_Conf_Creator,uc_creator,ConfCont,callid); //add ConfCont of the first called party
        } //if(Sip->Contacts.get_contact_copy_by_id(ContCopy,ConfCont.id))
      }  //if(ConfCont.id != -1)
    } //if(ConfCont.internal)
  else
    {
    string callid = Sip->getCallID_CLD_tc(ConfCont.name);
    if(callid.empty())
      {
      user_name_to_send = ConfCont.name;
      if(ConfCont.from_enterprise_db)
        {
        ComboBox1->Text        = ConfCont.full_name.c_str();
        CalledNameLbl->Caption = ConfCont.full_name.c_str();
        }
      else
        {
        ComboBox1->Text        = ConfCont.name.c_str();
        CalledNameLbl->Caption = ConfCont.name.c_str();
        }
      StartOutgoingCall_OnConferenceCreate(&ConfCont,Panel_Conf_Creator->Tag);
      if(Panel_Conf_Creator->ccl_empty()) //Добавить в созданную конференцию called_party вызова из которого создавалась конференция
         if(!Panel_Conf_Creator->nick_name.empty())
            if(ms_creator)
              {
              TContact ContCopy_0(-1);
              if(Sip->Contacts.get_contact_copy_by_user_name(ContCopy_0, Panel_Conf_Creator->nick_name))
                {
                TConfCont ConfCont_0(ContCopy_0.get_id());
                ConfCont_0.callid             = ms_creator->getCallID();
                ConfCont_0.user_name          = ContCopy_0.name;
                ConfCont_0.call_panel_tag     = Panel_Conf_Creator->Tag;
                if(Panel_Conf_Creator->get_call_state() == Call_State__Answer)
                   ConfCont_0.cc_call_state = 1;
                Panel_Conf_Creator->add_ccl_contact(ConfCont_0);
                SendConference_INFO_INIT(Panel_Conf_Creator->get_leg_type(), ConfCont_0); //Send INFO msg to first answered to conference creator contact
                Add_Participant_To_ConfCreator_Window(ConfCont_0, uatt);
                }
              else   //Contact with Panel_Conf_Creator->nick_name is absent in  local contact list. This is external contact.
                {
                TConfCont ConfCont_0(Panel_Conf_Creator->nick_name);
                ConfCont_0.callid             = ms_creator->getCallID();
                ConfCont_0.user_name          = Panel_Conf_Creator->nick_name;
                ConfCont_0.call_panel_tag     = Panel_Conf_Creator->Tag;
                if(Panel_Conf_Creator->get_call_state() == Call_State__Answer)
                   ConfCont_0.cc_call_state = 1;
                Panel_Conf_Creator->add_ccl_contact(ConfCont_0);
                SendConference_INFO_INIT(Panel_Conf_Creator->get_leg_type(), ConfCont_0); //Send INFO msg to first answered to conference creator contact
                Add_Participant_To_ConfCreator_Window(ConfCont_0, uatt);
                }
              } //if(ms_creator)
      deque<TConfCont> ccl_t;
      Panel_Conf_Creator->get_ccl_copy(ccl_t);          //get copy of conference participants list before add new contact
      Panel_Conf_Creator->add_ccl_contact(ConfCont);    //add ConfCont of the new participant
      SendConference_INFO_About_NEW_Participant_to_ALL_participants(Panel_Conf_Creator->get_leg_type(), Panel_Conf_Creator, ConfCont, ccl_t); //Send INFO msg to all answered conference participants (excluding conference_creator and new participant) about new participant
      Add_Participant_To_ConfCreator_Window(ConfCont, SipUAThreadType_UAC);
      } //if(callid.empty())
    else
      append_active_call_to_conference(Panel_Conf_Creator,uc_creator,ConfCont,callid);
    }
  }
if(!Panel_Conf_Creator->ccl_empty())
  {
  Panel_Conf_Creator->set_conf_participant(true);
  Panel_Conf_Creator->set_conf_host(true);
  }
if(ConferenceWin->Visible)
  {
  TConfExchBlock* ExchBlock = new TConfExchBlock;
  if(ExchBlock)
    {
    ExchBlock->conf_evnt = ConfEvnt_Restore;
    ConferenceWin->ins_exch_buf(ExchBlock);
    ::PostMessage(ConferenceWin->Handle, CONFERENCE_MSG, WM_CONFERENCE_MSG_WPARAM__NDEF, WM_CONFERENCE_MSG_LPARAM__NDEF);
    }
  }
}
//--------------------------------------------------------------------------------------------
void __fastcall TMainFormSLS::Add_Participant_To_ConfCreator_Window(TConfCont& ConfCont, SipUAThreadType uatt)
{
TConfExchBlock* ExchBlock = new TConfExchBlock;
if(ExchBlock)
  {
  ExchBlock->conf_evnt    = ConfEvnt_Add_Participant;
  ExchBlock->Buf_Conf_Creator = true;   //Говорит о том, что TConferenceWin принадлежит создателю конференции (больше управляющих кнопок, чем у пассивного уч конференции )
  ExchBlock->callid       = ConfCont.callid;
  ExchBlock->ttag         = ConfCont.call_panel_tag;
  ExchBlock->user_name    = ConfCont.user_name;
  ExchBlock->uatt         = uatt;
  ExchBlock->lt           = ConfCont.lt;
  ExchBlock->call_state   = ConfCont.cc_call_state;
  ConferenceWin->ins_exch_buf(ExchBlock);
  ::PostMessage(ConferenceWin->Handle, CONFERENCE_MSG, WM_CONFERENCE_MSG_WPARAM__NDEF, WM_CONFERENCE_MSG_LPARAM__NDEF);
  }
}
//--------------------------------------------------------------------------------------------
void __fastcall TMainFormSLS::Del_Participant_From_ConfCreator_Window(TConfCont& ConfCont)
{
TConfExchBlock* ExchBlock = new TConfExchBlock;
if(ExchBlock)
  {
  ExchBlock->conf_evnt = ConfEvnt_Del_Participant;
  ExchBlock->user_name = ConfCont.user_name;
  ExchBlock->ttag      = ConfCont.call_panel_tag;
  ConferenceWin->ins_exch_buf(ExchBlock);
::PostMessage(ConferenceWin->Handle, CONFERENCE_MSG, WM_CONFERENCE_MSG_WPARAM__NDEF, WM_CONFERENCE_MSG_LPARAM__NDEF);
  }
}
//---------------------------------------------------------------------------------------------
void __fastcall TMainFormSLS::Ans_Participant_To_Conf_Window(const string& s)
{
TConfExchBlock* ExchBlock = new TConfExchBlock;
if(ExchBlock)
  {
  ExchBlock->conf_evnt = ConfEvnt_Ans_Participant;
  ExchBlock->user_name = s;
  ConferenceWin->ins_exch_buf(ExchBlock);
::PostMessage(ConferenceWin->Handle, CONFERENCE_MSG, WM_CONFERENCE_MSG_WPARAM__NDEF, WM_CONFERENCE_MSG_LPARAM__NDEF);
  }
}
//---------------------------------------------------------------------------------------------
//--------- chat_id is CLEAR_NAME of Group  ---------------------------------------------------
//---------------------------------------------------------------------------------------------
void __fastcall TMainFormSLS::Send_GroupChat_INFO_INIT(const string& CHAT_ID, deque<TGroupName>& ChatGroup)
{
deque<TGroupName> ChatGroup_DEST = ChatGroup;
while(!ChatGroup_DEST.empty())
     {
     TGroupName Dest_GName = ChatGroup_DEST.front();
     ChatGroup_DEST.pop_front();
     deque<TGroupName> ChatGroup_COPY = ChatGroup;
     Send_GroupChat_INFO_to_Participant(Dest_GName, CHAT_ID, ChatGroup_COPY);
     }
}
//----------------------------------------------------------------------------------------------
//--- сначала из списка участников удаляется участник у которого name == dst_name --------------
//--- chat_id == CLEAR_NAME (name without prefiz FFFFFFFF) of the chat_group      --------------
//----------------------------------------------------------------------------------------------
void __fastcall TMainFormSLS::Send_GroupChat_INFO_to_Participant(TGroupName& Dest_GName,const string& chat_id, deque<TGroupName>& ChatGroup_COPY)
{
deque<TGroupName>::iterator it = ChatGroup_COPY.begin();
while(it != ChatGroup_COPY.end())
     {
     if(Dest_GName.name == (*it).name)
       {
       ChatGroup_COPY.erase(it);
       break;
       }
     it++;
     }
TOutputSipBuf* ospb = new TOutputSipBuf;
if(ospb)
  {
  ospb->setsls(SPS_INFO_GROUP_CHAT_REQ);
  ospb->requestline = "INFO" + WS +"sip:" + Dest_GName.name + "@" + Sip->Account.get_domain() + WS + SipVers + crlf;
  ospb->calledname  = Dest_GName.name;

  Sip->prepareContentType(ospb,"text/plain");
  ospb->sdp.Sdp  = "type:" + WS + "groupchat" + crlf;
  ospb->sdp.Sdp += "id:"   + WS + chat_id + crlf;
  ospb->sdp.Sdp += "adm:"  + WS + Sip->Account.get_user_name() + crlf;
  while(!ChatGroup_COPY.empty())
       {
       TGroupName GName = ChatGroup_COPY.front();
       ChatGroup_COPY.pop_front();
       ospb->sdp.Sdp += "part:" + WS + GName.name + crlf;
       }

  }
}
//---------------------------------------------------------------------------------------------
//--- Example INFO sip: -----------------------------------------------------------------------
//---------------------------------------------------------------------------------------------
  /*
  INFO sip:alice@pc33.example.com SIP/2.0
   Via: SIP/2.0/UDP 192.0.2.2:5060;branch=z9hG4bKnabcdef
   To: Bob <sip:bob@example.com>;tag=a6c85cf
   From: Alice <sip:alice@example.com>;tag=1928301774
   Call-Id: a84b4c76e66710@pc33.example.com
   CSeq: 314333 INFO
   Info-Package: foo
   Content-type: application/foo
   Content-Disposition: Info-Package
   Content-length: 24
  */
//-----------------------------------------------------------------------------------------------
//-- add - send INFO to all answered conference participants about new participant
//-- del - send INFO to all answered conference participants about disconnected participant
//-----------------------------------------------------------------------------------------------
void __fastcall TMainFormSLS::SendConference_INFO_INIT(LegType lt, TConfCont& dest)
{
TOutputSipBuf* ospb = new TOutputSipBuf;
if(ospb)
  {
  dest.lt = lt;
  ospb->setsls(SPS_INFO_REQ);
  ospb->requestline = "INFO" + WS +"sip:" + dest.user_name + "@" + Sip->Account.get_domain() + WS + SipVers + crlf;
  ospb->calledname  = dest.user_name;
  ospb->CallID      = dest.callid;
  ospb->callid      = "Call-ID:" + WS + dest.callid + crlf;
  Sip->prepareContentType(ospb,"text/plain");
  ospb->sdp.Sdp     = "conference" + crlf +
  "add" + WS + Sip->Account.get_user_name() + "," + "1,1" + crlf;   //first 1 - conference creator, second 1 - callstate - answered
  ospb->ContentLength = "Content-Length:" + WS + inttostr(ospb->sdp.Sdp.length()) + sdpboundary;
  if(lt == Lt_Out)
    {
    if(Sip->uac)
      {
      Sip->uac->setQueue(ospb);
      Sip->updateSentQueue_1(ospb);
      }
    else
      delete ospb;
    }
  else if(lt == Lt_In)
    {
    if(Sip->uas)
      {
      Sip->uas->setQueue(ospb);
      Sip->updateSentQueue_1(ospb);
      }
    else
      delete ospb;
    }
  }
}
//-------------------------------------------------------------------------------------------
//--- TConfCont& ConfCont - new participant -------------------------------------------------
//--- deque<TConfCont>& ccl_t list of destinations for send INFO msg  -----------------------
//--- Sending to ALL conference participants on INVITE_REQ of a new conference participant --
//-------------------------------------------------------------------------------------------
void __fastcall TMainFormSLS::SendConference_INFO_About_NEW_Participant_to_ALL_participants(LegType lt, TCall_Panel* Panel_Conf_Creator, TConfCont& new_ConfCont, deque<TConfCont>& destinations)
{
while(!destinations.empty())
     {
     TConfCont Dest_ConfCont = destinations.front();
     destinations.pop_front();
     if(!Dest_ConfCont.cc_call_state)
        continue;
     TOutputSipBuf* ospb = new TOutputSipBuf;
     if(ospb)
       {
       ospb->setsls(SPS_INFO_REQ);
       ospb->requestline = "INFO" + WS +"sip:" + Dest_ConfCont.user_name + "@" + Sip->Account.get_domain() + WS + SipVers + crlf;
       ospb->calledname  = Dest_ConfCont.user_name;
       ospb->CallID      = Dest_ConfCont.callid;
       ospb->callid      = "Call-ID:" + WS + Dest_ConfCont.callid + crlf;
       Sip->prepareContentType(ospb,"text/plain");
       string conf_creator;
       if(new_ConfCont.conference_creator)
          conf_creator = "1";
       else
          conf_creator = "0";
       ospb->sdp.Sdp = "conference" + crlf +
      "add" + WS + new_ConfCont.user_name + "," + conf_creator + "," + inttostr(new_ConfCont.cc_call_state) + crlf;   //first 1 - conference creator, second 1 - callstate - answered
       ospb->ContentLength = "Content-Length:" + WS + inttostr(ospb->sdp.Sdp.length()) + sdpboundary;
       if(lt == Lt_Out)
         {
         if(Sip->uac)
           {
           Sip->uac->setQueue(ospb);
           Sip->updateSentQueue_1(ospb);
           }
         else
           delete ospb;
         }
       else if(lt == Lt_In)
         {
         if(Sip->uas)
           {
           Sip->uas->setQueue(ospb);
           Sip->updateSentQueue_1(ospb);
           }
         else
           delete ospb;
         }
       }
     }
}
//---------------------------------------------------------------------------------------------------------------------
void __fastcall TMainFormSLS::Exclude_UserName_From_Dest_List(deque<TConfCont>& ccl_t, const string& s)
{
deque<TConfCont>::iterator it = ccl_t.begin();
while(it != ccl_t.end())
     {
     if((*it).user_name == s)
       {
       ccl_t.erase(it);
       break;
       }
     it++;
     }
}
//---------------------------------------------------------------------------------------------------------------------
void __fastcall TMainFormSLS::SendConference_INFO_About_DELETED_Participant_to_ALL_participants(LegType lt, TConfCont& del_ConfCont, deque<TConfCont>& destinations)
{
while(!destinations.empty())
     {
     TConfCont Dest_ConfCont = destinations.front();
     destinations.pop_front();
     TOutputSipBuf* ospb = new TOutputSipBuf;
     if(ospb)
       {
       ospb->setsls(SPS_INFO_REQ);
       ospb->requestline = "INFO" + WS +"sip:" + Dest_ConfCont.user_name + "@" + Sip->Account.get_domain() + WS + SipVers + crlf;
       ospb->CallID = Dest_ConfCont.callid;
       ospb->callid = "Call-ID:" + WS + Dest_ConfCont.callid + crlf;
       Sip->prepareContentType(ospb,"text/plain");
       ospb->sdp.Sdp = "conference" + crlf +
      "del" + WS + del_ConfCont.user_name + crlf;
       ospb->ContentLength = "Content-Length:" + WS + inttostr(ospb->sdp.Sdp.length()) + sdpboundary;
       if(lt == Lt_Out)
         {
         if(Sip->uac)
           {
           Sip->uac->setQueue(ospb);
           Sip->updateSentQueue_1(ospb);
           }
         else
           delete ospb;
         }
       else if(lt == Lt_In)
         {
         if(Sip->uas)
           {
           Sip->uas->setQueue(ospb);
           Sip->updateSentQueue_1(ospb);
           }
         else
           delete ospb;
         }
       }
     }
}
//---------------------------------------------------------------------------------------------------------------------
//-- Sending to a new conference participant INFO msg about ALL participants on receiving Answer from a new participant
//---------------------------------------------------------------------------------------------------------------------
void __fastcall TMainFormSLS::SendConference_INFO_About_ALL_Participants_to_NEW_participant(TMediaSession* ms, deque<TConfCont>& participants)
{
if(Sip->uac)
  {
  if(!participants.empty())
    {
    TOutputSipBuf* ospb = new TOutputSipBuf;
    if(ospb)
      {
      string dest_username = ms->get_uniq_username();
      ospb->setsls(SPS_INFO_REQ);
      ospb->requestline = "INFO" + WS +"sip:" + dest_username + "@" + Sip->Account.get_domain() + WS + SipVers + crlf;
      ospb->calledname  = dest_username;
      ospb->CallID      = ms->getCallID();
      ospb->callid      = "Call-ID:" + WS + ospb->CallID + crlf;
      Sip->prepareContentType(ospb,"text/plain");
      ospb->sdp.Sdp = "conference" + crlf +
      "add" + WS + Sip->Account.get_user_name() + "," + "1" + "," + "1" + crlf;
      while(!participants.empty())
           {
           TConfCont Part_ConfCont = participants.front();
           participants.pop_front();
           if(dest_username == Part_ConfCont.user_name)
              continue;
           string conf_creator;
           if(Part_ConfCont.conference_creator)
              conf_creator = "1";
           else
              conf_creator = "0";
           ospb->sdp.Sdp += "add" + WS + Part_ConfCont.user_name + "," + conf_creator + "," + inttostr(Part_ConfCont.cc_call_state) + crlf;   //first 1 - conference creator, second 1 - callstate - answered
           }
      ospb->ContentLength = "Content-Length:" + WS + inttostr(ospb->sdp.Sdp.length()) + sdpboundary;
      Sip->uac->setQueue(ospb);
      Sip->updateSentQueue_1(ospb);
      }
    }
  }
}
//------------------------------------------------------------------------------
void __fastcall TMainFormSLS::CC_ImgMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
if(GCS.CC_PANEL_TYPE == CC_PANEL_TYPE__GROUP_CREATE)
  {
  if(GCS.get_CreateGroupChat_BtnState() == BtnState_PRESSED)
     return;
  if(GCS.get_CreateGroupChat_BtnState() == BtnState_ACTIVE)
     GCS.set_CreateGroupChat_BtnState(CC_Img, BtnState_FOCUSED);
  }
else
  {
  if(AddToConfBtnState == BtnState_PRESSED)
     return;
  if(AddToConfBtnState == BtnState_ACTIVE)
     setAddToConfBtnState(BtnState_FOCUSED);
  }
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::CC_PanelMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
Refresh_AddToConfBtnState();
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::Memo1MouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
if(CC_Panel->Visible)
   Refresh_AddToConfBtnState();
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::CC_ImgMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
if(GCS.CC_PANEL_TYPE == CC_PANEL_TYPE__GROUP_CREATE)
  GCS.set_CreateGroupChat_BtnState(CC_Img, BtnState_PRESSED);
else
  setAddToConfBtnState(BtnState_PRESSED);
}
//---------------------------------------------------------------------------
bool __fastcall TInsMsgMissedStruct::saved(const string& s)
{
bool rv = false;
if(!q.empty())
  {
  deque<string>::iterator it = q.begin();
  while(it != q.end())
       if((*it++) == s)
         {
         rv = true;
         break;
         }
  }
return rv;
}
//---------------------------------------------------------------------------
string __fastcall TInsMsgMissedStruct::back()
{
string s;
if(!q.empty())
  {
  s = q.back();
  q.pop_back();
  }
return s;
}
//---------------------------------------------------------------------------
bool __fastcall TInsMsgMissedStruct::clear(const string& s)
{
bool rv = false;
if(!q.empty())
  {
  deque<string>::iterator it = q.begin();
  while(it != q.end())
       {
       if((*it) == s)
         {
         q.erase(it);
         rv = true;
         break;
         }
       it++;
       }
  }
return rv;
}
//--------------------------------------------------------------------------
bool _fastcall TMissedCallStruct::save_im_sender_name(const string& s)
{
bool rv = false;
if(!IMMS.saved(s))
  {
  IMMS.push(s);
  rv = true;
}
return rv;
}
//--------------------------------------------------------------------------
void _fastcall TMissedCallStruct::clear_im_sender_name(const string& s)
{
IMMS.clear(s);
int sz = IMMS.size();
if(!sz)
   MainFormSLS->MM_Img->Hide();
else
   MainFormSLS->DrawMessageMarker();
}
//---------------------------------------------------------------------
string __fastcall TMissedCallStruct::get_im_last_sender()
{
return IMMS.back();
}
//---------------------------------------------------------------------
void __fastcall TMainFormSLS::MM_Img_Resize()
{
MM_Img->Left   = Image_StartChat->Left + 8;
MM_Img->Top    = Image_StartChat->Top  + Image_StartChat->Height + 5;
}
//--------------------------------------------------------------------------
void __fastcall TMainFormSLS::DrawMessageMarker()
{
int sz = Im.MCS.IMMS.size();
if(sz)
  {
  int w = 20; //Image_StartChat->Width;
  int h = 20; //Image_StartChat->Height;
  int backgr_color = Panel_Chat->Color;
  TRBitMap rbmp(w, h, backgr_color, FOREGR_ACTIVE_YELLOW); //Yellow circle
  MM_Img_Resize();
  MM_Img->Width  = w;
  MM_Img->Height = h;
  TCanvas* CS = MM_Img->Canvas;
  CS->Draw(0,0,rbmp.bmp);
  if(sz > 999)
     sz = 999;
  AnsiString S     = IntToStr(sz);
  CS->Font->Color  = clBlack;
  CS->Font->Size   = 8;
  CS->Font->Style  = CS->Font->Style << fsBold;
  CS->Brush->Color = (TColor)FOREGR_ACTIVE_YELLOW;
  int tw           = CS->TextWidth(S);
  int th           = CS->TextHeight(S);
  int text_left    = MM_Img->Width/2  - tw/2 - 1;
  int text_top     = MM_Img->Height/2 - th/2 - 1;
  CS->TextOut(text_left, text_top, S);
  MM_Img->Show();
  }
}
//---------------------------------------------------------------------------
/*
void __fastcall TMissedCallStruct::update(const string& s)
{
if(!s.empty())
  {
  TMissedCallList::iterator it = mcl.find(s);
  if(it == mcl.end())
    {
    TMissedCall mc(s);
    mcl.insert(TMissedCallList::value_type(mc.name, mc));
    }
  else
    (*it).second.inc_count();
  }
}
//----------------------------------------------------------------------------
void __fastcall TMissedCallStruct::erase(const string& s)
{
TMissedCallList::iterator it = mcl.find(s);
if(it != mcl.end())
   mcl.erase(it);
}
//----------------------------------------------------------------------------
*/
void __fastcall TMainFormSLS::MM_ImgMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
string s = Im.MCS.get_im_last_sender();
if(!s.empty())
  {
  Im.set_selected_remote_user(s);
  Im.load_user_history();
  Sip->Contacts.reset_missed_calls(s);
  TContact ContCopy(-1);
  int row_id = Sip->Contacts.get_row_id_by_contact_name(s,ContCopy);
  if(Sip->Contacts.get_sorted_by_full_name())
     row_id = Sip->Contacts.get_row_by_contact_id_in_sorted_contact_list(ContCopy.get_id());
  if(row_id != -1)
    {
    if(ContCopy.OWNER)
      Sip->Contacts.open_all_above_divisions(ContCopy.OWNER);
    if(row_id < DrawGrid1->RowCount)
      {
      DrawGrid1->Row         = row_id;
      user_name_to_send      = ContCopy.name;
      if(ContCopy.CT == ContactType_GROUP)
         set_IM_to_chat_participants(true);
      else
         set_IM_to_chat_participants(false);
      ComboBox1->Text        = ContCopy.full_name.c_str();
      CalledNameLbl->Caption = ContCopy.full_name.c_str();;
      }
    }
  DrawGrid1->Repaint();
  }
int sz = Im.MCS.IMMS.size();
if(!sz)
  {
   MM_Img->Hide();
   TrayMessage_Ext(NIM_MODIFY,"Contact",2);
   }
else
   DrawMessageMarker();
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::DG_LastCallsMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
//Im.remote_im_client.clear();  //!!!
int ACol,ARow;
DG_LastCalls->MouseToCell(X,Y,ACol,ARow);
if(ARow == -1)return;
if(ACol == -1)return;
//Sip->Contacts.LCS.row_focused = ARow;
DG_LastCalls->Repaint();
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::DG_LastCallsMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
int ACol,ARow;
DG_LastCalls->MouseToCell(X,Y,ACol,ARow);
if(ARow == -1)return;
if(ACol == -1)return;
//Sip->Contacts.LCS.row_focused = ARow;
DG_LastCalls->Repaint();

TLastCallStr lcs;
if(Sip->Contacts.LCS.get_copy_of_last_call_by_row(lcs, ARow))
  {
  TContact ContCopy(-1);
  if(Sip->Contacts.get_contact_copy_by_user_name(ContCopy,lcs.name))
    {
    Im.remote_im_client  = lcs.name;
    if(CC_Panel->Visible)
      {
      TCall_Panel* Panel = get_Call_Panel_By_Tag(CC_DrawGrid->Tag);
      if(Panel)
        {
        TConfCont ConfCont(ContCopy.get_id());
        ConfCont.user_name = ContCopy.name;
        if(!Panel->is_ccl_q_contact(ConfCont)) //not yet in queue to the conference
          {
          Panel->add_ccl_q_contact(ConfCont);
          CC_DrawGrid->Repaint();
          }
        }
      }
    else
      {
      user_name_to_send      = ContCopy.name;
      if(ContCopy.CT == ContactType_GROUP)
         set_IM_to_chat_participants(true);
      else
         set_IM_to_chat_participants(false);
      ComboBox1->Text        = ContCopy.full_name.c_str();
      CalledNameLbl->Caption = ContCopy.full_name.c_str();
      if(Im.get_selected_remote_user() != user_name_to_send)
        {
        Im.curr_hstry_period = -1;
        Im.set_selected_remote_user(user_name_to_send);
        Im.load_user_history();
        }
      }
    } //if(Sip->Contacts.get_contact_copy_by_user_name(ContCopy,lcs.name))
  else
    {
    if(Im.get_selected_remote_user() != lcs.name)
      {
      Im.remote_im_client  = lcs.name;
      Im.curr_hstry_period = -1;
      Im.set_selected_remote_user(lcs.name);
      Im.load_user_history();
      }
    if(CC_Panel->Visible)
      {
      TCall_Panel* Panel = get_Call_Panel_By_Tag(CC_DrawGrid->Tag);
      if(Panel)
        {
        TConfCont ConfCont(lcs.name); //ConfCont.user_name = lcs.name inside constructor of TConfCont
        if(!Panel->is_ccl_q_contact(ConfCont)) //not yet in queue to the conference
          {
           Panel->add_ccl_q_contact(ConfCont);
           CC_DrawGrid->Repaint();
          }
        }
      }
    else
      {
      user_name_to_send      = lcs.name;
      if(lcs.full_name.empty())
        {
        ComboBox1->Text        = lcs.name.c_str();
        CalledNameLbl->Caption = lcs.name.c_str();;
        }
      else
        {
        ComboBox1->Text        = lcs.full_name.c_str();
        CalledNameLbl->Caption = lcs.full_name.c_str();;
        }
      }
    if(lcs.get_missed_calls())
      {
      Sip->Contacts.LCS.ResMissedCalls(lcs.name);
     // DG_LastCalls->Repaint();
      Sip->Contacts.LCS.DeleteMissedName(lcs.name);
      if(Sip->Contacts.LCS.MissedNameEmpty())
         TrayMessage_Ext(NIM_MODIFY,"Contact",2);
      }
    }
  }   //if(Sip->Contacts.LCS.get_copy_of_last_call_by_row(lcs, ARow))
}
//---------------------------------------------------------------------------
//-- Open TCommentPanel -----------------------------------------------------
//---------------------------------------------------------------------------
void  __fastcall TMainFormSLS::open_NSCP()
{
if(NSCP)
  {
  close_NSCP();
  return;
  }
NSCP = new TCommentPanel(this);
if(NSCP)
  {
  NSCP->Parent = this;
  NSCP->edit->SetFocus();
  NSCP->Show();
  }
}
//---------------------------------------------------------------------------
void  __fastcall TMainFormSLS::close_NSCP()
{
if(NSCP)
  {
  ::PostMessage(Handle, CONTROL_MSG, WM_APP_MSG_WPARAM__CLOSE_COMMENT_PANEL, WM_APP_MSG_LPARAM__NOPARAM);
  }
}
//---------------------------------------------------------------------------
string __fastcall TMainFormSLS::get_lst_calls_sub_dir()
{
return _lcs;
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::CC_PanelResize(TObject *Sender)
{
CC_DrawGrid->Height       = CC_Panel->Height - CC_Edit->Top - CC_Edit->Height - 50; //40;
CC_Img->Top               = CC_DrawGrid->Top + CC_DrawGrid->Height + 7;
CC_Edit->Width            = CC_Panel->Width  - 10;
CC_DrawGrid->Width        = CC_Edit->Width;
CC_DrawGrid->ColWidths[0] = CC_DrawGrid->Width;
CC_Img->Left              = CC_Panel->Width/2 - CC_Img->Width/2;
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::CallPanels_Resize()
{
for(int i = 0; i < ControlCount; i++)
   {
   TCall_Panel* Panel = dynamic_cast<TCall_Panel*>(Controls[i]);
   if(Panel)
     {
     Panel->Left   = RIGHT_PANEL->Left;
     Panel->Width  = Panel1->Width;
     }
   }
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::LEFT_PANELResize(TObject *Sender)
{
Panel2->Width = LEFT_PANEL->Width;
Panel3->Width = LEFT_PANEL->Width - 4;
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::SPLITTER()
{
LEFT_PANEL->Color      = clWhite;
LEFT_PANEL->BevelInner = bvNone;
LEFT_PANEL->BevelOuter = bvNone;


Splitter1->Width   = 5;
     // Splitter1->MinSize = 330; //this->ClientWidth/4;
Splitter1->MinSize = MIN_CLIEN_WIDTH;
LEFT_PANEL->Align = alLeft;
LEFT_PANEL->Width = Width/3;
Splitter1->Left   = LEFT_PANEL->Left + LEFT_PANEL->Width + 1;
Splitter1->Align  = alLeft; //LEFT_PANEL->Align;

Brand_Image->Parent = LEFT_PANEL;
Brand_Image->Top    = 0;
Brand_Image->Left   = 20;

Panel2->Parent      = LEFT_PANEL;

Panel_AddContact->Parent = LEFT_PANEL;
Panel_DialPad->Parent    = LEFT_PANEL;

RIGHT_PANEL->Color      = clWhite;
RIGHT_PANEL->BevelInner = bvNone;
RIGHT_PANEL->BevelOuter = bvNone;
RIGHT_PANEL->Align = alClient;
RIGHT_PANEL->Left  = Splitter1->Left + Splitter1->Width;
Panel1->Parent     = RIGHT_PANEL;

IM_DrawGrid->Parent  = RIGHT_PANEL;
CL_DrawGrid->Parent  = RIGHT_PANEL;
Panel_Chat->Parent   = RIGHT_PANEL;
CC_Panel->Parent     = RIGHT_PANEL;
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::RIGHT_PANELResize(TObject *Sender)
{
if(_CLOSE_REQUEST) return;
Panel1->Width     = RIGHT_PANEL->Width;
CallPanels_Resize();
Memo_Chat_Resize();

if(LEFT_PANEL->Width < MIN_CLIEN_WIDTH)
   LEFT_PANEL->Width = MIN_CLIEN_WIDTH;

Panel_AddContact->Width = LEFT_PANEL->Width;
Panel_DialPad->Width    = LEFT_PANEL->Width;
CL_DrawGrid->Left       = 0;// RIGHT_PANEL->Left;
CL_DrawGrid->Top        = Panel1->Top + Panel1->Height - 5;
Panel_Chat->Width       = RIGHT_PANEL->Width;
if(IM_DrawGrid->Width != RIGHT_PANEL->Width)
  {
  IM_DrawGrid->Width = RIGHT_PANEL->Width;
  IM_DrawGrid->ColWidths[0] = IM_DrawGrid->Width - IM_DrawGrid->ColWidths[1] - 20;
  if(IM_DrawGrid->RowCount > 0)
    {
    TImStr* imstr = Im.getStr(0);
    if(imstr)
      imstr->set_top_row_height();
    }
  IM_DrawGrid_Resize();
  }
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::TabSheet2Resize(TObject *Sender)
{
DG_LastCall_Resize();
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::N14Click(TObject *Sender)
{
EnterpriseSubscList->Show();
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::Image9MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
Activate_Contacts_TabSheet();
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::Image10MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
Activate_LastCall_TabSheet();
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::Activate_Contacts_TabSheet()
{
if(ContactMenu->Visible)
   ContactMenu->Close();
TabSheet1->Visible = true;
TabSheet2->Visible = false;
Image9->Canvas->Brush->Color = clWhite;
  Image9->Canvas->FillRect(Rect(0,0,Image9->Width,Image9->Height));
AnsiString S  = "Контакты";
int tw        = Image9->Canvas->TextWidth(S);
int text_left = Image9->Width/2 - tw/2;
Image9->Canvas->TextOut(text_left,5,S);

Image10->Canvas->Brush->Color = (TColor)0x00E0E0E0;
  Image10->Canvas->FillRect(Rect(0,0,Image10->Width,Image10->Height));
S         = "Последние";
tw        = Image10->Canvas->TextWidth(S);
text_left = Image10->Width/2 - tw/2;
Image10->Canvas->TextOut(text_left,5,S);
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::Activate_LastCall_TabSheet()
{
if(ContactMenu->Visible)
   ContactMenu->Close();
TabSheet1->Visible = false;
TabSheet2->Visible = true;
Image9->Canvas->Brush->Color  = (TColor)0x00E0E0E0;
  Image9->Canvas->FillRect(Rect(0,0,Image9->Width,Image9->Height));
AnsiString S = "Контакты";
int tw        = Image9->Canvas->TextWidth(S);
int text_left = Image9->Width/2 - tw/2;
Image9->Canvas->TextOut(text_left,5,S);
Image10->Canvas->Brush->Color = clWhite;
  Image10->Canvas->FillRect(Rect(0,0,Image10->Width,Image10->Height));
S         = "Последние";
tw        = Image10->Canvas->TextWidth(S);
text_left = Image10->Width/2 - tw/2;
Image10->Canvas->TextOut(text_left,5,S);
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::FormMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
if(ContactMenu->Visible)
   ContactMenu->Close();
}
//---------------------------------------------------------------------------
 void __fastcall TMainFormSLS::Memo1MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
if(ContactMenu->Visible)
   ContactMenu->Close();
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::Panel1MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
if(ContactMenu->Visible)
   ContactMenu->Close();
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::RIGHT_PANELMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
if(ContactMenu->Visible)
   ContactMenu->Close();
}
//---------------------------------------------------------------------------
AnsiString __fastcall get_font_name_Arial()
{
return _font_name_Arial;
}
//---------------------------------------------------------------------------
unsigned __fastcall get_turquoise_color()
{
return turquoise_color;
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::InitAudioCallBtn()
{
AnsiString S;
VoiceCallPanel->Caption    = S;
VoiceCallPanel->BevelInner = bvLowered;
VoiceCallPanel->BevelOuter = bvRaised;
VoiceCallPanel->Color      = clWhite;
VoiceCallPanel->Left       = 10;
VoiceCallPanel->Width      = 140; //115;
VoiceCallPanel->Height     = 35; //40;
VoiceCallPanel->Top        = ComboBox1->Top + ComboBox1->Height + 5;

Img_VoiceCall->Transparent = true;
Img_VoiceCall->Stretch     = true;
Img_VoiceCall->Left        = LEFT_IMAGE_MARGIN;
Img_VoiceCall->Top         = VoiceCallPanel->Height/2 - Img_VoiceCall->Height/2;
ACBS.img_left              = Img_VoiceCall->Left;
ACBS.img_top               = Img_VoiceCall->Top;

Image_VoiceCall->Left      = call_btn_width/4 + 4; //10;
Image_VoiceCall->Top       = VoiceCallPanel->Top - 6;

ACBS.crc_img_left          = Image_VoiceCall->Left;     //for circular btn shape
ACBS.crc_img_top           = Image_VoiceCall->Top;      //for circular btn shape

Lbl_VoiceCall->Font->Name  = get_font_name_Arial();
Lbl_VoiceCall->Font->Size  = 10;
Lbl_VoiceCall->Left        = Img_VoiceCall->Left + Img_VoiceCall->Width + 10; //5;
Lbl_VoiceCall->Top         = VoiceCallPanel->Height/2 - Lbl_VoiceCall->Height/2;
Lbl_VoiceCall->Caption     = "Позвонить";
ACBS.lbl_left              = Lbl_VoiceCall->Left;
ACBS.lbl_top               = Lbl_VoiceCall->Top;
Lbl_VoiceCall->Font->Color = (TColor)get_turquoise_color();

//Image_VoiceCall->Visible   = false;
VoiceCallPanel->Visible    = false;

Image_VoiceCall->Hint      = "Аудио вызов";
Image_VoiceCall->ShowHint  = true;
TColor cl = Panel1->Color;
RBitMap::change_color(0xFFFFFF, cl, Image_VoiceCall); //Сменить clWhite контура на фоне панели
}
//----------------------------------------------------------------------------
void __fastcall TMainFormSLS::InitVideoCallBtn()
{
AnsiString S;
VideoCallPanel->Caption    = S;
VideoCallPanel->BevelInner = bvLowered;
VideoCallPanel->BevelOuter = bvRaised;
VideoCallPanel->Color      = clWhite;
VideoCallPanel->Left       = VoiceCallPanel->Left + VoiceCallPanel->Width + 10;
VideoCallPanel->Width      = 140; //125;
VideoCallPanel->Height     = VoiceCallPanel->Height;
VideoCallPanel->Top        = VoiceCallPanel->Top;

Img_VideoCall->Transparent = true;
Img_VideoCall->Stretch     = true;
Img_VideoCall->Left        = LEFT_IMAGE_MARGIN;
Img_VideoCall->Top         = VideoCallPanel->Height/2 - Img_VideoCall->Height/2;
VCBS.img_left              = Img_VideoCall->Left;
VCBS.img_top               = Img_VideoCall->Top;

Image_VideoCall->Left      = Image_VoiceCall->Left + 1.5 * Image_VoiceCall->Width;
//Image_VideoCall->Left      = Image_VoiceCall->Left + Image_VoiceCall->Width + Image_VoiceCall->Width/2;
Image_VideoCall->Top       = Image_VoiceCall->Top;
VCBS.crc_img_left          = Image_VideoCall->Left;
VCBS.crc_img_top           = Image_VideoCall->Top;

Lbl_VideoCall->Font->Name  = get_font_name_Arial();
Lbl_VideoCall->Font->Size  = 10;
Lbl_VideoCall->Left        = Img_VideoCall->Left + Img_VideoCall->Width + 10; //5;
Lbl_VideoCall->Top         = Lbl_VoiceCall->Top;
Lbl_VideoCall->Caption     = "Видеозвонок";
VCBS.lbl_left              = Lbl_VideoCall->Left;
VCBS.lbl_top               = Lbl_VideoCall->Top;

Lbl_VideoCall->Font->Color = (TColor)get_turquoise_color();

//Image_VideoCall->Visible   = false;
VideoCallPanel->Visible    = false;

Image_VideoCall->Hint      = "Видео вызов";
Image_VideoCall->ShowHint  = true;

TColor cl = Panel1->Color;
RBitMap::change_color(0xFFFFFF, cl, Image_VideoCall); //Сменить clWhite контура на фоне панели
}
//----------------------------------------------------------------------------
void __fastcall TMainFormSLS::InitRemoteVideoBtn()
{
TColor cl = Panel1->Color;
Image_RemoteVideo->Left     = Image_VideoCall->Left + call_btn_width + call_btn_width/2;
Image_RemoteVideo->Top      = Image_VoiceCall->Top;
Image_RemoteVideo->Hint     = "Видео удаленного абонента";
Image_RemoteVideo->ShowHint = true;
RBitMap::change_color(0xFFFFFF, cl, Image_RemoteVideo); //Сменить clWhite контура на фоне панели
}
//----------------------------------------------------------------------------
void __fastcall TMainFormSLS::VoiceCallMouseDOWN()
{
VoiceCallPanel->BevelInner = bvLowered;
VoiceCallPanel->BevelOuter = bvLowered;
Img_VoiceCall->Top        += 1;
Lbl_VoiceCall->Top        += 1;
Image_VoiceCall->Top      += 1;
}
//----------------------------------------------------------------------------
void __fastcall TMainFormSLS::VoiceCallMouseUP()
{
VoiceCallPanel->BevelInner = bvLowered;
VoiceCallPanel->BevelOuter = bvRaised;
Img_VoiceCall->Top         = ACBS.img_top;
Lbl_VoiceCall->Top         = ACBS.lbl_top;
Image_VoiceCall->Top       = ACBS.crc_img_top;
}
//----------------------------------------------------------------------------
void __fastcall TMainFormSLS::SetVoiceCallBtnState(BtnState BS)
{
ACBS.BS = BS;
switch(ACBS.BS){
      case BtnState_ACTIVE:
           VoiceCallPanel->Color   = clWhite;
           VoiceCallMouseUP();
           if(!Lbl_VoiceCall->Enabled)
               Lbl_VoiceCall->Enabled = true;
           RBitMap::change_color(get_turquoise_color(), 0xE4AC22, Image_VoiceCall);
           break;
      case BtnState_FOCUSED:
           RBitMap::change_color(0xE4AC22, get_turquoise_color(), Image_VoiceCall);
           VoiceCallPanel->Color  = (TColor)0xF0F0F0;
           VoiceCallMouseUP();
           break;
      case BtnState_PRESSED:
           VoiceCallPanel->Color = (TColor)0xE0E0E0;
           VoiceCallMouseDOWN();
           break;
      case BtnState_INACTIVE:
           Lbl_VoiceCall->Enabled = false;
           break;
      }
}
//------------------------------------------------------------------------------
void __fastcall TMainFormSLS::SetVideoCallBtnState(BtnState BS)
{
VCBS.BS = BS;
switch(VCBS.BS){
      case BtnState_ACTIVE:
           VideoCallPanel->Color   = clWhite;
           VideoCallMouseUP();
           if(!Lbl_VideoCall->Enabled)
               Lbl_VideoCall->Enabled = true;
           RBitMap::change_color(get_turquoise_color(), 0xE4AC22, Image_VideoCall);
           break;
      case BtnState_FOCUSED:
           RBitMap::change_color(0xE4AC22, get_turquoise_color(), Image_VideoCall);
           VideoCallPanel->Color = (TColor)0xF0F0F0;
           VideoCallMouseUP();
           break;
      case BtnState_PRESSED:
           VideoCallPanel->Color = (TColor)0xE0E0E0;
           VideoCallMouseDOWN();
           break;
      case BtnState_INACTIVE:
           Lbl_VideoCall->Enabled = false;
           break;
      }
}
//------------------------------------------------------------------------------
void __fastcall TMainFormSLS::VoiceCallPanelMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
if(ACBS.BS != BtnState_INACTIVE)
  if(ACBS.BS != BtnState_PRESSED)
    if(ACBS.BS != BtnState_FOCUSED)
       SetVoiceCallBtnState(BtnState_FOCUSED);

if(VCBS.BS != BtnState_INACTIVE)
  if(VCBS.BS != BtnState_ACTIVE)
     SetVideoCallBtnState(BtnState_ACTIVE);
}
//------------------------------------------------------------------------------
void __fastcall TMainFormSLS::VoiceCallPanelMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
if(ACBS.BS != BtnState_INACTIVE)
 {
// TDateTime dt = dt.CurrentDateTime();
// if((dt - CallBtnMouseUp_TmStmp) > TDateTime(0,0,1,0))    // Защита от сдвоенного OnMouseUp
//   {
   if(X > 0)
     if(Y > 0)
       if(X < VoiceCallPanel->Width)
         if(Y < VoiceCallPanel->Height)
           {
//           CallBtnMouseUp_TmStmp = dt;
           AudioCall();
           SetVoiceCallBtnState(BtnState_FOCUSED);
           return;
           }
   SetVoiceCallBtnState(BtnState_ACTIVE);
   cbs = CallBtnState_Active;
//   }
 }
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::Lbl_VoiceCallMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
if(ACBS.BS != BtnState_INACTIVE)
  {
//  TDateTime dt = dt.CurrentDateTime();
//  if((dt - CallBtnMouseUp_TmStmp) > TDateTime(0,0,1,0))    // Защита от сдвоенного OnMouseUp
//    {
    if(X > -ACBS.lbl_left)
      if(Y > -ACBS.lbl_top)
        if(X < VoiceCallPanel->Width - ACBS.lbl_left)
          if(Y < VoiceCallPanel->Height - ACBS.lbl_top)
            {
//            CallBtnMouseUp_TmStmp = dt;
            AudioCall();
            SetVoiceCallBtnState(BtnState_FOCUSED);
            return;
          }
    SetVoiceCallBtnState(BtnState_ACTIVE);
    cbs = CallBtnState_Active;
//    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::Img_VoiceCallMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
if(ACBS.BS != BtnState_INACTIVE)
  {
//  TDateTime dt = dt.CurrentDateTime();
//  if((dt - CallBtnMouseUp_TmStmp) > TDateTime(0,0,1,0))    // Защита от сдвоенного OnMouseUp
//    {
    if(X > -ACBS.img_left)
      if(Y > -ACBS.img_top)
        if(X < VoiceCallPanel->Width - ACBS.img_left)
          if(Y < VoiceCallPanel->Height - ACBS.img_top)
            {
//            CallBtnMouseUp_TmStmp = dt;
            AudioCall();
            SetVoiceCallBtnState(BtnState_FOCUSED);
            return;
          }
    SetVoiceCallBtnState(BtnState_ACTIVE);
    cbs = CallBtnState_Active;
    }
//  }
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::VoiceCallPanelMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
TDateTime dt = dt.CurrentDateTime();
if(dt > CallBtnMouseUp_TmStmp)  // Защита от сдвоенных OnMouse_Up_Down
  {
  CallBtnMouseUp_TmStmp = dt + TDateTime(0,0,1,0);
  SetVoiceCallBtn_PRESSED();
  }
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::Lbl_VoiceCallMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
TDateTime dt = dt.CurrentDateTime();
if(dt > CallBtnMouseUp_TmStmp)  // Защита от сдвоенных OnMouse_Up_Down
  {
  CallBtnMouseUp_TmStmp = dt + TDateTime(0,0,1,0);
  SetVoiceCallBtn_PRESSED();
  }
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::Img_VoiceCallMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
TDateTime dt = dt.CurrentDateTime();
if(dt > CallBtnMouseUp_TmStmp)  // Защита от сдвоенных OnMouse_Up_Down
  {
  CallBtnMouseUp_TmStmp = dt + TDateTime(0,0,1,0);
  SetVoiceCallBtn_PRESSED();
  }
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::VideoCallPanelMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
if(VCBS.BS != BtnState_INACTIVE)
 {
 if(X > 0)
   if(Y > 0)
     if(X < VideoCallPanel->Width)
       if(Y < VideoCallPanel->Height)
         {
         SetVideoCallBtnState(BtnState_FOCUSED);
         StartVideo();
         return;
         }
 SetVideoCallBtnState(BtnState_ACTIVE);
 cbsv = CallBtnState_Active;
 }
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::Lbl_VideoCallMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
if(VCBS.BS != BtnState_INACTIVE)
  {
  if(X > -VCBS.lbl_left)
      if(Y > -VCBS.lbl_top)
        if(X < VideoCallPanel->Width - VCBS.lbl_left)
          if(Y < VideoCallPanel->Height - VCBS.lbl_top)
            {
            SetVideoCallBtnState(BtnState_FOCUSED);
            StartVideo();
            return;
          }
    SetVideoCallBtnState(BtnState_ACTIVE);
    cbsv = CallBtnState_Active;
   }
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::Img_VideoCallMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
if(VCBS.BS != BtnState_INACTIVE)
  {
  if(X > -VCBS.img_left)
      if(Y > -VCBS.img_top)
        if(X < VideoCallPanel->Width - VCBS.img_left)
          if(Y < VideoCallPanel->Height - VCBS.img_top)
            {
            SetVideoCallBtnState(BtnState_FOCUSED);
            StartVideo();
            return;
          }
    SetVideoCallBtnState(BtnState_ACTIVE);
    cbsv = CallBtnState_Active;
   }
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::RIGHT_PANELMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
SetAudioAndVideoNormalState();
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::SetAudioAndVideoNormalState()
{
if(ACBS.BS != BtnState_INACTIVE)
  if(ACBS.BS != BtnState_ACTIVE)
     SetVoiceCallBtnState(BtnState_ACTIVE);

if(VCBS.BS != BtnState_INACTIVE)
  if(VCBS.BS != BtnState_ACTIVE)
     SetVideoCallBtnState(BtnState_ACTIVE);
}
//-----------------------------------------------------------------------------
void __fastcall TMainFormSLS::SetVoiceCallBtn_PRESSED()
{
if(ACBS.BS != BtnState_INACTIVE)
   SetVoiceCallBtnState(BtnState_PRESSED);
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::IM_DrawGridMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
SetAudioAndVideoNormalState();
int ACol,ARow;
IM_DrawGrid->MouseToCell(X,Y,ACol,ARow);
if(ACol == 0)
  if(ARow != -1)
    {
    TImStr* IS = Im.getStr(ARow);
    if(IS)
      if(IS->get_im_tt() == IM_INVITE_ON_FILE_RECEIVING)
        {
        TRect Rect = IM_DrawGrid->CellRect(ACol,ARow);
        if(X > Rect.Left + LEFT_FILE_TRANSFER_ICON_POSITION)
          if(X < Rect.Left + LEFT_FILE_TRANSFER_ICON_POSITION + rcv_file_img->Width)
             if(Y > Rect.Top + TOP_FILE_TRANSFER_ICON_POSITION )
               if(Y < Rect.Top + TOP_FILE_TRANSFER_ICON_POSITION + rcv_file_img->Height)
                 {
                 IM_DrawGrid->Cursor = crHandPoint;
                 return;
                 }
        }
    }
IM_DrawGrid->Cursor = crDefault;
}
//----------------------------------------------------------------------------
void __fastcall TMainFormSLS::VideoCallMouseDOWN()
{
VideoCallPanel->BevelInner = bvLowered;
VideoCallPanel->BevelOuter = bvLowered;
Img_VideoCall->Top        += 1;
Lbl_VideoCall->Top        += 1;
Image_VideoCall->Top      += 1;
}
//----------------------------------------------------------------------------
void __fastcall TMainFormSLS::VideoCallMouseUP()
{
VideoCallPanel->BevelInner = bvLowered;
VideoCallPanel->BevelOuter = bvRaised;
Img_VideoCall->Top         = VCBS.img_top;
Lbl_VideoCall->Top         = VCBS.lbl_top;
Image_VideoCall->Top       = VCBS.crc_img_top;
}
//----------------------------------------------------------------------------
void __fastcall TMainFormSLS::VideoCallPanelMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
if(VCBS.BS != BtnState_INACTIVE)
  if(VCBS.BS != BtnState_PRESSED)
    if(VCBS.BS != BtnState_FOCUSED)
       SetVideoCallBtnState(BtnState_FOCUSED);

if(ACBS.BS != BtnState_INACTIVE)
  if(ACBS.BS != BtnState_ACTIVE)
     SetVoiceCallBtnState(BtnState_ACTIVE);
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::SetVideoCallBtn_PRESSED()
{
if(VCBS.BS != BtnState_INACTIVE)
   SetVideoCallBtnState(BtnState_PRESSED);
}
//----------------------------------------------------------------------------
void __fastcall TMainFormSLS::VideoCallPanelMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
TDateTime dt = dt.CurrentDateTime();
if(dt > CallBtnMouseUp_TmStmp)  // Защита от сдвоенных OnMouse_Up_Down
  {
  CallBtnMouseUp_TmStmp = dt + TDateTime(0,0,1,0);
  SetVideoCallBtn_PRESSED();
  }
}
//----------------------------------------------------------------------------
void __fastcall TMainFormSLS::Lbl_VideoCallMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
TDateTime dt = dt.CurrentDateTime();
if(dt > CallBtnMouseUp_TmStmp)  // Защита от сдвоенных OnMouse_Up_Down
  {
  CallBtnMouseUp_TmStmp = dt + TDateTime(0,0,1,0);
  SetVideoCallBtn_PRESSED();
  }
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::Img_VideoCallMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
TDateTime dt = dt.CurrentDateTime();
if(dt > CallBtnMouseUp_TmStmp)  // Защита от сдвоенных OnMouse_Up_Down
  {
  CallBtnMouseUp_TmStmp = dt + TDateTime(0,0,1,0);
  SetVideoCallBtn_PRESSED();
  }
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::ActivateVideoCallBtnState(int dev_id)
{
if(dev_id == -1)
   SetVideoCallBtnState(BtnState_INACTIVE);
else
   SetVideoCallBtnState(BtnState_ACTIVE);
}
//---------------------------------------------------------------------------
/*
void __fastcall TMainFormSLS::LoadLogEventsDll()
{
string events_dll = client_root + "\\" + _events_dll;
EvtLogDll.HINST   = ::LoadLibrary(events_dll.c_str());
typedef  void (*pfinFunc_Init)();
pfinFunc_Init Init = (pfinFunc_Init)GetProcAddress(EvtLogDll.HINST,"Init");
if(Init)
   (*Init)();
EvtLogDll.pFunc_OELF     = (pfinFunc_OpenEvetsLogFile)GetProcAddress(EvtLogDll.HINST,"OpenEvetsLogFile");
EvtLogDll.pFunc_CELF     = (pfinFunc_CloseEvetsLogFile)GetProcAddress(EvtLogDll.HINST,"CloseEvetsLogFile");
EvtLogDll.pFunc_INSERT   = (pfinFunc_INSERT)GetProcAddress(EvtLogDll.HINST,"INSERT");
EvtLogDll.pFunc_INSERT_W = (pfinFunc_INSERT_W)GetProcAddress(EvtLogDll.HINST,"INSERT_W");
EvtLogDll.pFunc_WRITE    = (pfinFunc_WRITE)GetProcAddress(EvtLogDll.HINST,"WRITE");
}
*/
//----------------------------------------------------------------------------
void __fastcall TMainFormSLS::log_result_of_dowloading_dll()
{
if(ofs)
  if(ofs->elt)
    {
    if(AecDll.Initiated)
       ofs->elt->FputEvt("\nAEC: DSPCap Available!\n");
    else
       ofs->elt->FputEvt("\nAEC: DSPCap UNAVAILABLE!!\n");
    }
}
//----------------------------------------------------------------------------
void __fastcall TMainFormSLS::log_OS_Version()
{
if(ofs)
  if(ofs->elt)
    {
    string s = "\nOS_Version: " + inttostr(osv.dwMajorVersion) + "." + inttostr(osv.dwMinorVersion);
    ofs->elt->FputEvt(s);
    }
}
//----------------------------------------------------------------------------
/*
void __fastcall TMainFormSLS::LoadAudioDll()
{
string audio_dll  = client_root + "\\" + _audio_dll;
AudioIntDll.HINST = ::LoadLibrary(audio_dll.c_str());
typedef  bool (*pfinFunc_Init)(TEvtLogDll*);
pfinFunc_Init Init = (pfinFunc_Init)GetProcAddress(AudioIntDll.HINST,"Init");
if(Init)
  if((*Init)(&EvtLogDll))
    {
    AudioIntDll.Initiated = true;
    AudioIntDll.pFunc_AIC = (pfinFunc_AudioInterfaceControl)GetProcAddress(AudioIntDll.HINST,"AudioInterfaceControl");
    }
}
*/
//----------------------------------------------------------------------------
void __fastcall TMainFormSLS::LoadVoiceCaptureDspDll()
{
string voice_capture_dsp_dll = client_root + "\\" + _voice_capture_dsp_dll;
AecDll.HINST = ::LoadLibrary(_voice_capture_dsp_dll.c_str());
if(AecDll.HINST)
  {
  typedef  bool (*pfinFunc_Init)(pFunc_INSERT_S);
  pfinFunc_Init Init = (pfinFunc_Init)GetProcAddress(AecDll.HINST,"Init");
  if(Init)
    {
    (*Init)(INSERT_S);
    AecDll.pFunc_CreateExchStruct      = (pfinFunc_CreateExchStruct)GetProcAddress(AecDll.HINST,"CreateExchStruct");
    if(!AecDll.pFunc_CreateExchStruct) return;
    AecDll.pFunc_FreeExchStruct        = (pfinFunc_FreeExchStruct)GetProcAddress(AecDll.HINST,"FreeExchStruct");
    if(!AecDll.pFunc_FreeExchStruct)   return;
    AecDll.pFunc_CheckCaptureDSP       = (pfinFunc_CheckCaptureDSP)GetProcAddress(AecDll.HINST,"CheckCaptureDSP");
    if(!AecDll.pFunc_CheckCaptureDSP)   return;
    AecDll.pFunc_CaptureDSP            = (pfinFunc_CaptureDSP)GetProcAddress(AecDll.HINST,"CaptureDSP");
    if(!AecDll.pFunc_CaptureDSP)       return;
    AecDll.pFunc_GetAudioPacket        = (pfinFunc_GetAudioPacket)GetProcAddress(AecDll.HINST,"GetAudioPacket");
    if(!AecDll.pFunc_GetAudioPacket)   return;
    AecDll.pFunc_FreeExchBuf           = (pfinFunc_FreeExchBuf)GetProcAddress(AecDll.HINST,"FreeExchBuf");
    if(!AecDll.pFunc_FreeExchBuf)      return;
    AecDll.pFunc_UnInit                = (pfinFunc_UnInit)GetProcAddress(AecDll.HINST,"UnInit");
    if(!AecDll.pFunc_UnInit)           return;
    AecDll.Initiated = (*AecDll.pFunc_CheckCaptureDSP)(); 
    }
  }
}
//-----------------------------------------------------------------------------
const string __fastcall get_hstry()
{
return _hstry;
}
//-----------------------------------------------------------------------------
const string __fastcall get_TYPE()
{
return _TYPE;
}
//-----------------------------------------------------------------------------
const string __fastcall get_lf()
{
return _lf;
}
//-----------------------------------------------------------------------------
void __fastcall TIM_Struct::USER_HSTRY_LOAD(const SYSTEMTIME& start_time, const SYSTEMTIME& end_time)
{
if(MainFormSLS->Im.LCFT)  //Thread для работы с файлом содержащим последние вызовы (Last Calls)
  {
  string user = get_current_user();
  string s_cl = MainFormSLS->get_clients_dir();
  s_cl += "\\" + user;
  TLCSBuf* LCSBuf = new TLCSBuf(LOAD_USER_HSTRY);   // Запрос на чтение Last Calls
  if(LCSBuf)
    {
    LCSBuf->s          = s_cl;
    LCSBuf->s_1        = selected_remote_user;
    LCSBuf->START_TIME = start_time;
    LCSBuf->END_TIME   = end_time;
    MainFormSLS->Im.LCFT->push_lcs_buf(LCSBuf);
    }
  }
}
//------------------------------------------------------------------------------
void __fastcall TDeleteLegTrnStruct::req_to_del(TLegTrn* Lt)
{
::EnterCriticalSection(&del_leg_trn_cs);
  TDateTime dt = dt.CurrentDateTime() + TDateTime(0,0,10,0);  //10 sec
  Lst.insert(TLst::value_type(dt,Lt));
::LeaveCriticalSection(&del_leg_trn_cs);
}
//--------------------------------------------------------------------------------------------------------------------------
//---------- Deletion of LegTrn occurs fter ten second after req to delete. See TDeleteLegTrnStruct::req_to_del(TLegTrn* Lt)
//---------- Do Not call BLOCK_LEG_TRN() and UN_BLOCK_LEG_TRN() after if(Lt).
//---------- It can initiate dead_lock if somewere forgot call UN_BLOCK_LEG_TRN()
//--------------------------------------------------------------------------------------------------------------------------
void __fastcall TDeleteLegTrnStruct::check_to_del()
{
::EnterCriticalSection(&del_leg_trn_cs);
  if(!Lst.empty())
    {
    TDateTime dt = dt.CurrentDateTime();
    TLst::iterator it = Lst.begin();
    while(it != Lst.end())
         {
         if((*it).first < dt)
           {
           TLegTrn* Lt = (*it).second;
           if(Lt)
              delete Lt;
           Lst.erase(it);
           it = Lst.begin();
           }
         else
           break;
         }
    }
::LeaveCriticalSection(&del_leg_trn_cs);
}
//------------------------------------------------------------------------------
void __fastcall TMainFormSLS::Rcvd_ExchMsgType_Bye_IN(TExchBuf* buf)
{
if(buf->b1) //screen_sharing_viewer
  {
  SSV.ssv_delete_screen_sharing_structs();
  rdp_destroy();
  }
TMediaSession* ms = Sip->sss->GetMsIn_by_Callid(buf->msg);
if(ms)
  {
  TCall_Panel* call_panel = get_Call_Panel_By_Tag(ms->getCallTag());
  if(call_panel)
    if(call_panel->get_call_state() == Call_State__Conference)
       call_panel->conference_exit(ms);
    else
      {
      if(!call_panel->get_conf_host())
         call_panel->check_on_conf_participation(); //Проверить, не является ли данная панель ПАССИВНЫМ участником коференции (т.е. панель на SIP клиенте, не являющимся создателем конференции). Если да, то закрыть окно ConferenceWin
      else
        {
        if(call_panel->get_conf_participant())
           call_panel->conference_exit(ms);
        }
      }

  string in_callid = in_pref + ms->getCallID();  //Sip->getCallID_CLNG_tc(ms->username);
  Sip->del_CLD_tc(ms->get_uniq_username());
  if(call_panel)
    {
    HIDE_DPW(call_panel->Tag);
    if(!ms->get_ms_hstry_written())
      {
      call_panel->tstmps.get_conv_duration();
      call_panel->incoming_call_disc_out_hstry(ms->get_uniq_username(), ms->get_display_username());
      }
    call_panel->disconnect_screen_sharing();     //disconeect screen_sharing if active
    call_panel->disconnect_parallel_phone();     //disconeect parallel phone if active
    }
  push_req_to_del_call_panel(ms->getCallTag());
  Sip->sss->EraseMediaSession(in_callid); //ms deleted !!!
  #ifdef SIP_Video
  if(Form4->Visible)
     Form4->Hide();
  if(Form3->Visible)
     Form3->Hide();
  Form3->call_in_progress = false;
  #endif
  if(MainFormSLS->Image_RemoteVideo->Visible)
     {
     MainFormSLS->Image_RemoteVideo->Visible = false;
     MainFormSLS->Image_RemoteVideo->Tag     = 0;
     }
  if(MainFormSLS->Panel_Dial->Visible)
     MainFormSLS->Panel_Dial->Hide();
  Play_Sound(playSoundState_Hangup);
  }
}
//------------------------------------------------------------------------------
void __fastcall TMainFormSLS::Rcvd_ExchMsgType_Bye_OUT(TExchBuf* buf)
{
TMediaSession* ms = Sip->sss->GetMsOut_by_Callid(buf->msg);
if(ms)
  {
  bool parallel_phone = ms->get_ms_parallel_phone();
  TCall_Panel* call_panel = NULL;
  if(!parallel_phone)
    {
    call_panel = get_Call_Panel_By_Tag(ms->getCallTag());
    if(call_panel)
      if(call_panel->get_call_state() == Call_State__Conference)
         call_panel->conference_exit(ms);
      else
        {
        if(!call_panel->get_conf_host())
           call_panel->check_on_conf_participation(); //Проверить, не является ли данная панель ПАССИВНЫМ участником коференции (т.е. панель на SIP клиенте, не являющимся создателем конференции). Если да, то закрыть окно ConferenceWin
        else
          {
          if(call_panel->get_conf_participant())
             call_panel->conference_exit(ms);
          }
        }
    }
  string out_callid = out_pref + ms->getCallID(); //Sip->getCallID_CLD_tc(ms->username);
  if(!parallel_phone)
     Sip->del_CLD_tc(ms->get_uniq_username());
  if(call_panel)
    {
    HIDE_DPW(call_panel->Tag);
    if(!ms->get_ms_hstry_written())
      {
      ms->set_ms_hstry_written(true);
      call_panel->tstmps.get_conv_duration();
      call_panel->outgoing_call_disc_out_hstry(ms->get_uniq_username(), ms->get_display_username());
      }
    call_panel->disconnect_screen_sharing();     //disconeect screen sharing if active
    call_panel->disconnect_parallel_phone();     //disconeect parallel phone if active
    }
  if(!parallel_phone)
     push_req_to_del_call_panel(ms->getCallTag());
  Sip->sss->EraseMediaSession(out_callid); //ms deleted !!!
  #ifdef SIP_Video
  if(Form4->Visible)
     Form4->Hide();
  if(Form3->Visible)
     Form3->Hide();
  Form3->call_in_progress = false;
  #endif
  if(MainFormSLS->Image_RemoteVideo->Visible)
     {
     MainFormSLS->Image_RemoteVideo->Visible = false;
     MainFormSLS->Image_RemoteVideo->Tag     = 0;
     }
  if(MainFormSLS->Panel_Dial->Visible)
     MainFormSLS->Panel_Dial->Hide();
  if(!parallel_phone)
      Play_Sound(playSoundState_Hangup);
  }
}
//------------------------------------------------------------------------------
void __fastcall TMainFormSLS::Rcvd_ExchMsgType_Bye_From_Pph__For_IN_Primary_Call(TExchBuf* buf)
{
TMediaSession* ms = Sip->sss->GetMsIn_by_Callid(buf->msg);
if(ms)
  {
  TCall_Panel* call_panel = get_Call_Panel_By_Tag(ms->getCallTag());
  if(call_panel)
     call_panel->disconnect_incoming_call(ms,true);    // true - Bye rcvd from parallel phone
  }
}
//------------------------------------------------------------------------------
void __fastcall TMainFormSLS::Rcvd_ExchMsgType_Bye_From_Pph__For_OUT_Primary_Call(TExchBuf* buf)
{
TMediaSession* ms = Sip->sss->GetMsOut_by_Callid(buf->msg);
if(ms)
  {
  TCall_Panel* call_panel = get_Call_Panel_By_Tag(ms->getCallTag());
  if(call_panel)
     call_panel->disconnect_outgoing_call(ms,true);
  }
}
//------------------------------------------------------------------------------
//-- Надписи при переадресации на панеле вызова абонента А ---------------------
//------------------------------------------------------------------------------
void __fastcall TMainFormSLS::Rcvd_INVITE_ON_CALL_TRANSFER(int tag, const string& callingParty, const string& referred_by)
{
for(int i=0;i < ControlCount;i++)
   {
   TCall_Panel* call_panel = dynamic_cast<TCall_Panel*>(Controls[i]);
   if(call_panel)
     if(call_panel->Tag)
       if(call_panel->Tag == tag)
         {
         call_transferred_from(call_panel, callingParty, referred_by);
         if(call_panel->get_leg_type() == Lt_Out)
            call_panel->transf_to_incoming();
         }
   }
}
//------------------------------------------------------------------------------
void __fastcall TMainFormSLS::Rcvd_200OK_ON_CALL_TRANSFER(int tag, const string& refer_name,const string& referred_by)
{
for(int i=0;i < ControlCount;i++)
   {
   TCall_Panel* call_panel = dynamic_cast<TCall_Panel*>(Controls[i]);
   if(call_panel)
     if(call_panel->Tag)
       if(call_panel->Tag == tag)
         {
         call_transferred_from(call_panel, refer_name, referred_by);
         if(call_panel->get_leg_type() == Lt_In)
            call_panel->transf_to_outgoing();
         }
   }
}
//------------------------------------------------------------------------------
void __fastcall TMainFormSLS::call_transferred_from(TCall_Panel* call_panel, const string& callingParty, const string& referred_by)
{
AnsiString S;
TContact Contact(-1);
if(MainFormSLS->Sip->Contacts.get_contact_copy_by_user_name(Contact, callingParty))
  {
  if(!Contact.full_name.empty())
    S = /* "\"" +*/ (AnsiString)Contact.full_name.c_str() /* + "\"" */;
  else
    S = "\"" + (AnsiString)Contact.name.c_str() + "\"";
  }
 else
   S = callingParty.c_str();

if(MainFormSLS->lng == Lang_RU)
  S += ": Разговор";
else
  S += ": Conversation";
call_panel->lb->Caption = S;

S = "( ";
if(MainFormSLS->lng == Lang_RU)
  S += "Вызов переадресовал ";
else
  S += "Call transferred from ";

if(MainFormSLS->Sip->Contacts.get_contact_copy_by_user_name(Contact,referred_by))
  {
  if(!Contact.full_name.empty())
   S += (AnsiString)Contact.full_name.c_str();
  else
   S += "\"" + (AnsiString)Contact.name.c_str() + "\"";
  }
else
  S += referred_by.c_str();
S += " )";
call_panel->lb_1->Caption = S;
call_panel->lb_1->Top = call_panel->lb->Top + call_panel->lb->Height;
call_panel->lb_1->Visible = true;
call_panel->SetInvisible_REM_HOLD();
}
//------------------------------------------------------------------------------
string  __fastcall TCall_Panel::PrepareReferTo_Attendant()
{
TSip* Sip = MainFormSLS->Sip;
string rv;
TMediaSession* ms = MainFormSLS->Sip->sss->GetMs_by_Call_Tag(referred_call_panel_tag);
if(ms)
  {
  string replaces;
  string callid = ms->getCallID();
  int len = callid.length();
  int st  = callid.find("@");
  if(st != -1)
    {
    string s1,s2;
    s1  = callid.substr(0,st);
    st++;
    if(st < len)
      s2 = callid.substr(st);
    replaces = s1 += "%40" + s2;
    }
  else
    replaces = callid;
  if(ms->get_leg_type() == Lt_In)
    {
    if(Sip->uas)
      {
      TLegTrn* Lt = Sip->uas->getLegTrn(callid);
      if(Lt)
        {
         Lt->BLOCK_LEG_TRN();
         rv = "Refer-To:" + WS + "<" + ms->get_contact_uri() + "?Replaces=" + replaces + "%3Bto-tag%3D" + Lt->mytag + "%3Bfrom-tag%3D" + Lt->remotetag + ">" + crlf;
         Lt->UN_BLOCK_LEG_TRN();
        }
      }
    }
  else if(ms->get_leg_type() == Lt_Out)
    {
    if(Sip->uac)
      {
      TLegTrn* Lt = Sip->uac->getLegTrn(callid);
      if(Lt)
        {
         Lt->BLOCK_LEG_TRN();
         rv = "Refer-To:" + WS + "<" + ms->get_contact_uri() + "?Replaces=" + replaces + "%3Bto-tag%3D" + Lt->remotetag + "%3Bfrom-tag%3D" + Lt->mytag + ">" + crlf;
         Lt->UN_BLOCK_LEG_TRN();
        }
      }
    }
  }
return rv;
}
//------------------------------------------------------------------------------
void __fastcall TCall_Panel::Prepare_To_From_Contact_CSeq__ForRefer(TOutputSipBuf* ospb, TMediaSession* ms)
{
TSip* Sip = MainFormSLS->Sip;
if(Sip->uac)
  {
  TLegTrn* Lt = Sip->uac->getLegTrn(ms->getCallID());
  if(Lt)
    {
    Lt->BLOCK_LEG_TRN();
    ospb->To   = Lt->to;
    if(ospb->To.rfind(";tag=") == -1)
      {
      int st = ospb->To.rfind(crlf);
      if(st != -1)
        {
        ospb->To.resize(st);
        ospb->To += ";tag=" + Lt->remotetag + crlf;
        }
      }
    ospb->from    = Lt->from;
    ospb->Contact = Lt->out_Contact;
    ospb->cseq    = "CSeq:" + WS + inttostr(++Lt->Current_CSeq) + WS + "REFER" + crlf;
    Lt->UN_BLOCK_LEG_TRN();
    }
  }
}
//----------------------------------------------------------------------------
void __fastcall TMainFormSLS::Place_AllActiveCalls_OnHold(int tag)
{
for(int i=0;i < ControlCount;i++)
   {
   TCall_Panel* call_panel =  dynamic_cast<TCall_Panel*>(Controls[i]);
   if(call_panel)
    if(call_panel->Tag != tag)
     if((call_panel->get_call_type() == Call_Type_Regular) ||(call_panel->get_call_type() == Call_Type_Refer))
       {
        call_panel->set_call_state(Call_State__Request_Hold_By_Local_Party);
        call_panel->SetImgsVisible_ONHOLD();
        if(call_panel->lb)
          {
          string s = call_panel->lb->Caption.c_str();
          int st = s.find(":");
          if(st != -1)
            {
            s.resize(st);
            if(lng == Lang_RU)
               s += ": Вызов на удержании ";
            else
               s += ": Call on hold ";
            call_panel->lb->Caption = s.c_str();
            }
          } //if(call_panel->lb)

          TMediaSession* ms = Sip->sss->GetMs_by_Call_Tag(call_panel->Tag);
          if(ms)
            {
            ms->set_media_channels_OnHold(true);
            TOutputSipBuf* ospb = new TOutputSipBuf;
            if(ospb)
              {
              ospb->setsls(SPS_REINVITE_ONHOLD_REQ);
              ospb->CallID     = ms->getCallID();
              ospb->calledname = ms->get_uniq_username();
              switch(call_panel->get_leg_type()){
                    case Lt_Out: Sip->uac->setQueue(ospb);
                                 Sip->updateSentQueue_1(ospb);
                                 break;
                    case Lt_In:  Sip->uas->setQueue(ospb);
                                 Sip->updateSentQueue_1(ospb);
                                 break;
                    default: delete ospb; break;
                    }
              } //if(ospb)
            } //if(ms)
       }  //if(call_panel->get_call_type() == Call_Type_Regular)
   }  // for(int i=0;i < MainFormSLS->ControlCount;i++)

}
//------------------------------------------------------------------------------
void __fastcall TMainFormSLS::ActivateAllPanels_Placed_OnHold()
{
for(int i=0;i < ControlCount;i++)
   {
   TCall_Panel* call_panel =  dynamic_cast<TCall_Panel*>(Controls[i]);
   if(call_panel)
     {
     Call_State CS = call_panel->get_call_state();
     if((CS == Call_State__Request_Hold_By_Local_Party) || (CS == Call_State__Hold_By_Local_Party))
       {
       call_panel->lochold_img->ShowHint  = true;
       call_panel->lochold_img->Hint      = "Перевести в разговорное состояние";
       call_panel->lochold_img->OnMouseUp = call_panel->LocHold_Img__Mouse_Up;
       }
     }
   }
}
//------------------------------------------------------------------------------
void __fastcall TCall_Panel::LocHold_Img__Mouse_Up(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
if(call_state == Call_State__Hold_By_Local_Party)
  {
  SetImgsVisible_RESUME();
  call_state = Call_State__Answer;
  if(lb)
    {
    string s = lb->Caption.c_str();
    int st = s.find(":");
    if(st != -1)
      {
      s.resize(st);
      if(MainFormSLS->lng == Lang_RU)
         s += ": Переключение в разговор ";
      else
         s += ": Resume ";
      lb->Caption = s.c_str();
      }
    } //if(call_panel->lb)

  MainFormSLS->Place_AllActiveCalls_OnHold(Tag);

  TMediaSession* ms = MainFormSLS->Sip->sss->GetMs_by_Call_Tag(Tag);
  if(ms)
    {
    TOutputSipBuf* ospb = new TOutputSipBuf;
    if(ospb)
      {
      ms->set_media_channels_OnHold(false);
      ospb->setsls(SPS_REINVITE_RESUME_REQ);
      ospb->CallID     = ms->getCallID();
      ospb->calledname = ms->get_uniq_username();
      switch(lt){
            case Lt_Out: MainFormSLS->Sip->uac->setQueue(ospb);
                         MainFormSLS->Sip->updateSentQueue_1(ospb);
                         break;
            case Lt_In:  MainFormSLS->Sip->uas->setQueue(ospb);
                         MainFormSLS->Sip->updateSentQueue_1(ospb);
                         break;
            default: delete ospb; break;
            }
      } //if(ospb)
    } //if(ms)
  }
}
//------------------------------------------------------------------------------
void __fastcall TCall_Panel::set_img_visible(TImage* img, bool a)
{
if(img)
   img->Visible = a;
}
//------------------------------------------------------------------------------
void __fastcall TCall_Panel::set_img_enabled(TImage* img, bool a)
{
if(img)
   img->Enabled = a;
}
//------------------------------------------------------------------------------
void __fastcall TCall_Panel::SetImgsVisible_ONHOLD()
{
set_img_visible(lochold_img, true);
set_img_visible(mic_img,     false);
set_img_visible(speak_img,   false);
set_img_visible(conf_img,    false);
set_img_visible(dial_img,    false);
set_img_visible(refer_img,   false);
set_img_visible(screen_img,  false);
if(cam_img)
  {
  cam_img_visible = cam_img->Visible;
  set_img_visible(cam_img, false);
  }
}
//------------------------------------------------------------------------------
void __fastcall TCall_Panel::SetImgsVisible_RESUME()
{
set_img_visible(lochold_img, false);
set_img_visible(mic_img,     true);
set_img_visible(speak_img,   true);
set_img_visible(conf_img,    true);
set_img_visible(dial_img,    true);
set_img_visible(refer_img,   true);
if(cam_img)
   set_img_visible(cam_img, cam_img_visible);
if(MainFormSLS->osv.dwMajorVersion >= 6)
  set_img_visible(screen_img,  true);
}
//------------------------------------------------------------------------------
void __fastcall TCall_Panel::SetVisible_REM_HOLD()
{
set_img_visible(remhold_img, true);
set_img_visible(conf_img,    false);
set_img_visible(dial_img,    false);
set_img_enabled(speak_img,   false);
set_img_enabled(refer_img,   false);
set_img_enabled(conn_img,    false);
}
//------------------------------------------------------------------------------
void __fastcall TCall_Panel::SetInvisible_REM_HOLD()
{
set_img_visible(remhold_img, false);
set_img_visible(conf_img,    true);
set_img_visible(dial_img,    true);
set_img_enabled(speak_img,   true);
set_img_enabled(refer_img,   true);
set_img_enabled(conn_img,    true);
}
//------------------------------------------------------------------------------
#ifdef Automatic_Out_Calls
void __fastcall TAutomaticOutCalls::activate()
{
clear();
unsigned ph = phone;
for(unsigned i = 0;i < num;i++)
    q.push(inttostr(ph++));
active = true;
}
//------------------------------------------------------------------------------
void __fastcall TAutomaticOutCalls::deactivate()
{
}
//------------------------------------------------------------------------------
void __fastcall TAutomaticOutCalls::makecalls()
{
unsigned i = n;
while(!q.empty() && (i--))
     {
     string s = q.front();
     q.pop();
     MainFormSLS->set_user_name_to_send(s);
     MainFormSLS->ComboBox1->Text = s.c_str();
     MainFormSLS->CalledNameLbl->Caption = s.c_str();
     MainFormSLS->AudioCall();
     }
}
//------------------------------------------------------------------------------
void __fastcall TAutomaticOutCalls::clear()
{
while(!q.empty())
     {
     string s = q.front();
     q.pop();
     }
}
//------------------------------------------------------------------------------
#endif //#ifdef Automatic_Out_Calls
void __fastcall TMainFormSLS::Button9Click(TObject *Sender)
{
#ifdef Automatic_Out_Calls
AOC.activate();
#endif
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::Button10Click(TObject *Sender)
{
#ifdef Automatic_Out_Calls
AOC.deactivate();
#endif
}
//---------------------------------------------------------------------------
void __fastcall TCtrlExchStruct::push(const TCtrlExch& ce)
{
::EnterCriticalSection(&ctrl_exch_cs);
  q.push(ce);
::LeaveCriticalSection(&ctrl_exch_cs);
}
//---------------------------------------------------------------------------
TCtrlExch __fastcall TCtrlExchStruct::get()
{
TCtrlExch rv;
::EnterCriticalSection(&ctrl_exch_cs);
  if(!q.empty())
    {
    rv = q.front();
    q.pop();
    rv.set_actual();
    }
::LeaveCriticalSection(&ctrl_exch_cs);
return rv;
}
//---------------------------------------------------------------------------
/*
bool __fastcall TDBIExch::empty()
{
bool rv = false;
::EnterCriticalSection(&dbiexch_cs);
  rv = q.empty();
::LeaveCriticalSection(&dbiexch_cs);
return rv;
}  */
//--------------------------------------------------------------------------
void __fastcall TMainFormSLS::N16Click(TObject *Sender)
{
if(ParallelPhoneWin)
  ShowWindow(ParallelPhoneWin, SW_RESTORE);
else
  {
  TParallelPhone* pph = new TParallelPhone(Application);
  if(pph)
    {
    ParallelPhoneWin = pph->Handle;
    pph->Show();
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::ProcInRegister(TExchBuf* buf)
{
try{
if(buf->isAddBuf())
  {
  TSipParsBuf* spb = (TSipParsBuf*)buf->getAddBuf_Reset();
  if(spb)
    {
    if(spb->parallel_phone)
      if(PPS->getActive())
        if(PPS->getName() == spb->callingParty)
          {
          PPS->expires_sec = expires_to_int(spb->Expires);
          if(PPS->expires_sec)
            {
            PPS->setRegistered(true);
            PPS->next_reg = PPS->next_reg.CurrentDateTime() + sec_to_date_time(PPS->expires_sec);
            PPS->setRegAddr(spb->FromIP);
            PPS->regUAddr = exsConvStrIpAddrToUnsigned(PPS->getRegAddr());
            PPS->regPort  = spb->FromPort;
            PPS->send_200OK_OnRegister_To_PPH(spb);
            }
          else
            PPS->setRegistered(false);
          }
    spb->decReferenceCount();
    }
  }
}//try
catch(Exception& e){exsSstEXCEPTION(ofs->elt,"__ProcInRegister()",e);}
}
//------------------------------------------------------------------------------
void __fastcall TMainFormSLS::Make_All_Call_Panels_INVISIBLE()
{
for(int i = 0; i < MainFormSLS->ControlCount; i++)
   {
   TCall_Panel* Panel = dynamic_cast<TCall_Panel*>(MainFormSLS->Controls[i]);
   if(Panel)
      Panel->Visible = false;
   }
}
//------------------------------------------------------------------------------
void __fastcall TMainFormSLS::Make_All_Call_Panels_VISIBLE()
{
for(int i = 0; i < MainFormSLS->ControlCount; i++)
   {
   TCall_Panel* Panel = dynamic_cast<TCall_Panel*>(MainFormSLS->Controls[i]);
   if(Panel)
      Panel->Visible = true;
   }
}
//------------------------------------------------------------------------------
void __fastcall TMainFormSLS::AddContact_ImgMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
add_contact_mouse_up();
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::DialNumber_ImgMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
dial_number_mouse_up();
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::add_contact_mouse_up()
{
if(ContactMenu->Visible)
   ContactMenu->Close();
#ifdef Enterprise_Edition
 EnterpriseSubscList->Show();
#else
 AddContact->M_Show();
#endif
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::dial_number_mouse_up()
{
if(ContactMenu->Visible)
   ContactMenu->Close();
//Show_Panel_Dial(0,0);
//Show_Panel_Dial(2,0);
Show_Panel_Dial(3,0);   //New Dial FORM
        //Show_Panel_Dial(4,0);   //New Dial Panel
}
//--------------------------------------------------------------------------
void __fastcall TMainFormSLS::color_btns_correction()
{
//int dst_color = 0xCD8300; //blue
int dst_color = (int)turquoise_color;
RBitMap::change_color(clBlack, dst_color, mic_img_static);
RBitMap::change_color(clBlack, dst_color, speak_img_static);
RBitMap::change_color(clBlack, dst_color, conf_img_static);
RBitMap::change_color(clBlack, dst_color, dial_img_static);
}
//-------------------------------------------------------------------------
string __fastcall TAccount::get_user_name()
{
string rv;
::EnterCriticalSection(&acc_cs);
  rv = user_name;
::LeaveCriticalSection(&acc_cs);
return rv;
}
//---------------------------------------------------------------------------
/*const*/ string __fastcall TAccount::get_user_pwd()
{
string rv;
::EnterCriticalSection(&acc_cs);
  rv = user_pwd;
::LeaveCriticalSection(&acc_cs);
return rv;
}
//----------------------------------------------------------------------------
/*const*/ string __fastcall TAccount::get_domain()
{
string rv;
::EnterCriticalSection(&acc_cs);
  rv = domain;
::LeaveCriticalSection(&acc_cs);
return rv;
}
//----------------------------------------------------------------------------
/*const*/ string __fastcall TAccount::get_displayname()
{
string rv;
::EnterCriticalSection(&acc_cs);
  rv = displayname;
::LeaveCriticalSection(&acc_cs);
return rv;
}
//----------------------------------------------------------------------------
string __fastcall TAccount::get_tuple()
{
string rv;
::EnterCriticalSection(&acc_cs);
  rv = tuple;
::LeaveCriticalSection(&acc_cs);
return rv;
}
//----------------------------------------------------------------------------
string __fastcall TAccount::get_person()
{
string rv;
::EnterCriticalSection(&acc_cs);
  rv = person;
::LeaveCriticalSection(&acc_cs);
return rv;
}
//----------------------------------------------------------------------------
void __fastcall TAccount::set_user_name(const string& s)
{
::EnterCriticalSection(&acc_cs);
  user_name = s;
::LeaveCriticalSection(&acc_cs);
}
//----------------------------------------------------------------------------
void __fastcall TAccount::set_user_pwd(const string& s)
{
::EnterCriticalSection(&acc_cs);
  user_pwd = s;
::LeaveCriticalSection(&acc_cs);
}
//---------------------------------------------------------------------------
void __fastcall TAccount::set_domain(const string& s)
{
::EnterCriticalSection(&acc_cs);
  domain = s;
::LeaveCriticalSection(&acc_cs);
}
//---------------------------------------------------------------------------
void __fastcall TAccount::set_displayname(const string& s)
{
::EnterCriticalSection(&acc_cs);
  displayname = s;
::LeaveCriticalSection(&acc_cs);
}
//--------------------------------------------------------------------------
void __fastcall TAccount::displayname_clear()
{
::EnterCriticalSection(&acc_cs);
  displayname.clear();
::LeaveCriticalSection(&acc_cs);
}
//--------------------------------------------------------------------------
string __fastcall TNotifyStruct::get_my_net_state_comment()
{
string rv;
::EnterCriticalSection(&ns_cs);
  rv = __my_net_state_comment;
::LeaveCriticalSection(&ns_cs);
return rv;
}
//--------------------------------------------------------------------------
void __fastcall TNotifyStruct::set_my_net_state_comment(const string& s)
{
::EnterCriticalSection(&ns_cs);
  __my_net_state_comment = s;
::LeaveCriticalSection(&ns_cs);
}
//-------------------------------------------------------------------------
void __fastcall TNotifyStruct::my_net_state_comment_clear()
{
::EnterCriticalSection(&ns_cs);
  __my_net_state_comment.clear();
::LeaveCriticalSection(&ns_cs);
}
//--------------------------------------------------------------------------
bool __fastcall TNotifyStruct::notify_queue_empty()
{
bool rv;
::EnterCriticalSection(&ns_cs);
  rv = __notify_queue.empty();
::LeaveCriticalSection(&ns_cs);
return rv;
}
//--------------------------------------------------------------------------
bool __fastcall TNotifyStruct::notify_comment_queue_empty()
{
bool rv;
::EnterCriticalSection(&ns_cs);
  rv = __notify_comment_queue.empty();
::LeaveCriticalSection(&ns_cs);
return rv;
}
//--------------------------------------------------------------------------
void __fastcall TNotifyStruct::push_notify_queue(const TSubscribedData& sd)
{
::EnterCriticalSection(&ns_cs);
  __notify_queue.push(sd);
::LeaveCriticalSection(&ns_cs);
}
//--------------------------------------------------------------------------
void __fastcall TNotifyStruct::push_notify_comment_queue(const TSubscribedData& sd)
{
::EnterCriticalSection(&ns_cs);
  __notify_comment_queue.push(sd);
::LeaveCriticalSection(&ns_cs);
}
//-----------------------------------------------------------------------------
void __fastcall TNotifyStruct::proc_notify_comment_queue_element()
{
::EnterCriticalSection(&ns_cs);
  if(!__notify_comment_queue.empty())
    {
    TSubscribedData sd = __notify_comment_queue.front();
  __notify_comment_queue.pop();
    MainFormSLS->Sip->send_Uas_NOTIFY(sd);
    }
::LeaveCriticalSection(&ns_cs);
}
//-----------------------------------------------------------------------------
void __fastcall TNotifyStruct::proc_notify_queue_element()
{
::EnterCriticalSection(&ns_cs);
  if(!__notify_queue.empty())
    {
    TSubscribedData sd = __notify_queue.front();
  __notify_queue.pop();
    MainFormSLS->Sip->send_Uas_NOTIFY(sd);
    }
::LeaveCriticalSection(&ns_cs);
}
//----------------------------------------------------------------------------
void __fastcall TNotifyStruct::clear_notify_queue()
{
::EnterCriticalSection(&ns_cs);
  while(!notify_queue_empty())
       {
       __notify_queue.front();
       __notify_queue.pop();
       }
::LeaveCriticalSection(&ns_cs);
}
//-----------------------------------------------------------------------------
#ifdef TRACE_ALLOC_MEM
#ifdef _DEBUG
void AddTrack(DWORD addr,  DWORD asize,  const char *fname, DWORD lnum)
{
if(!MainFormSLS->AIS.AL_BLOCK)
  {
  ALLOC_INFO info;
  info.address = addr;
  info.file    = string(fname);
  info.line    = lnum;
  info.size    = asize;
  ::EnterCriticalSection(&MainFormSLS->AIS.ais_cs);
    MainFormSLS->AIS.AL.insert(TALLOC_INFO_STRUCT::TAllocList::value_type(info.address, info));
  ::LeaveCriticalSection(&MainFormSLS->AIS.ais_cs);
 // cout << "Save" << endl;
  }
}
//------------------------------------------------------------------------------
void RemoveTrack(DWORD addr)
{
if(MainFormSLS)
if(!MainFormSLS->AIS.AL_BLOCK)
  {
  ::EnterCriticalSection(&MainFormSLS->AIS.ais_cs);
    TALLOC_INFO_STRUCT::TAllocList::iterator it = MainFormSLS->AIS.AL.find(addr);
    if(it != MainFormSLS->AIS.AL.end())
      {
      MainFormSLS->AIS.AL.erase(it);
      // cout << "Remove" << endl;
      }
  ::LeaveCriticalSection(&MainFormSLS->AIS.ais_cs);
  }
}
//------------------------------------------------------------------------------
void DUMP_UNFREED() {
MainFormSLS->AIS.AL_BLOCK = true;
TEventLogThread* elt = MainFormSLS->ofs->elt;
if(elt)
  {
  //cout << "DUMP_UNFREED" << endl;
  if(!MainFormSLS->AIS.AL.empty())
    {
    string s = "\nUhfreedBuffers: " + inttostr(MainFormSLS->AIS.AL.size());
    elt->FputEvt(s,1);
    while(!MainFormSLS->AIS.AL.empty())
         {
         TALLOC_INFO_STRUCT::TAllocList::iterator it = MainFormSLS->AIS.AL.begin();
         s = "\n" + (*it).second.file + " LINE: " + inttostr((*it).second.line)  + " SZ:" + inttostr((*it).second.size) + "  ADDRESS:" + inttostr((*it).second.address);
         /*
         if((*it).second.line == 39)
           if((*it).second.size == 1080)
             {
             TOutPutUdpBlock* opb = (TOutPutUdpBlock*)(*it).second.address;
             if(opb)
                s += "; " + opb->COMMENT + "; pktn " + inttostr(opb->pktn) + "; refCount " + inttostr(opb->getReferenceCount());
             }
          */
         MainFormSLS->AIS.AL.erase(it);
         elt->FputEvt(s,1);
         }
    //cout << "DUMP_UNFREED_EXIT" << endl;
    }
  }
}
//------------------------------------------------------------------------------
#endif //#ifdef _DEBUG
#endif //#ifdef TRACE_ALLOC_MEM
//------------------------------------------------------------------------------
void __fastcall TMainFormSLS::Image_VoiceCallMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
if(ACBS.BS != BtnState_INACTIVE)
 {
 if(X > 0)
   if(Y > 0)
     if(X < Image_VoiceCall->Width)
       if(Y < Image_VoiceCall->Height)
         {
         if((ACBS.dt_mouse_up.CurrentDateTime() - ACBS.dt_mouse_up) > TDateTime(0,0,1,0))  //защита от сдвоенного клика
           {
           AudioCall();
           SetVoiceCallBtnState(BtnState_FOCUSED);
           ACBS.dt_mouse_up = ACBS.dt_mouse_up.CurrentDateTime();
           }
         return;
         }
 SetVoiceCallBtnState(BtnState_ACTIVE);
 cbs = CallBtnState_Active;
 }
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::Image_VideoCallMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
if(VCBS.BS != BtnState_INACTIVE)
 {
 if(X > 0)
   if(Y > 0)
     if(X < Image_VideoCall->Width)
       if(Y < Image_VideoCall->Height)
         {
         SetVideoCallBtnState(BtnState_FOCUSED);
         StartVideo();
         return;
         }
 SetVideoCallBtnState(BtnState_ACTIVE);
 cbsv = CallBtnState_Active;
 }
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::Image_VoiceCallMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
if(ACBS.BS != BtnState_INACTIVE)
  {
  if(ACBS.BS != BtnState_PRESSED)
    if(ACBS.BS != BtnState_FOCUSED)
       SetVoiceCallBtnState(BtnState_FOCUSED);
  set_img_cursor_type((TImage*)Sender);
  }

if(VCBS.BS != BtnState_INACTIVE)
  if(VCBS.BS != BtnState_ACTIVE)
     SetVideoCallBtnState(BtnState_ACTIVE);
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::Image_VideoCallMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
if(VCBS.BS != BtnState_INACTIVE)
  {
  if(VCBS.BS != BtnState_PRESSED)
    if(VCBS.BS != BtnState_FOCUSED)
       SetVideoCallBtnState(BtnState_FOCUSED);
  set_img_cursor_type((TImage*)Sender);     
  }

if(ACBS.BS != BtnState_INACTIVE)
  if(ACBS.BS != BtnState_ACTIVE)
     SetVoiceCallBtnState(BtnState_ACTIVE);
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::Image_VoiceCallMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
TDateTime dt = dt.CurrentDateTime();
if(dt > CallBtnMouseUp_TmStmp)  // Защита от сдвоенных OnMouse_Up_Down
  {
  CallBtnMouseUp_TmStmp = dt + TDateTime(0,0,1,0);
  SetVoiceCallBtn_PRESSED();
  }
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::Image_VideoCallMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
TDateTime dt = dt.CurrentDateTime();
if(dt > CallBtnMouseUp_TmStmp)  // Защита от сдвоенных OnMouse_Up_Down
  {
  CallBtnMouseUp_TmStmp = dt + TDateTime(0,0,1,0);
  SetVideoCallBtn_PRESSED();
  }
}
//---------------------------------------------------------------------------
void __fastcall TContacts::sort_by_full_user_name()
{
::EnterCriticalSection(&contlist_cs);
  __sort_by_full_user_name_unsafe();
::LeaveCriticalSection(&contlist_cs);
}
//---------------------------------------------------------------------------
void __fastcall TContacts::__sort_by_full_user_name_unsafe()
{
__sorted_by_full_name = false;
if(!contact_list.empty())
  {
  multimap < string, unsigned > mp;
  TContactList::iterator it = contact_list.begin();
  while(it != contact_list.end())
       {
       mp.insert(multimap < string, unsigned >::value_type((*it).second->full_name, (*it).second->get_id()));
       it++;
       }
  if(!mp.empty())
    {
    full_name_list.clear();
    unsigned ID = 0;
    multimap < string, unsigned >::iterator it = mp.begin();
    while(it != mp.end())
       {
       full_name_list.insert(TFullNameList::value_type(ID++,(*it).second)); //id->clobal_id
       it++;
       }
  __sorted_by_full_name = true;
    }
  }
}
//---------------------------------------------------------------------------



/*
void __fastcall TMainFormSLS::OnIdleHandler(TObject *Sender, bool &Done)
{
int a = IM_DrawGrid->RowCount;
}
*/
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::FormCreate(TObject *Sender)
{
try{
if(ofs->elt)
 if(ofs->elt->getlog())
   {
   string TimeStr;
   TDateTime DateTime = DateTime.CurrentDateTime();
   exsDateTime(DateTime,TimeStr);
   string str = "\n" + (string)TimeStr + " TMainFormSLS_CREATED! " + "\n";
   ofs->elt->FputEvt(str, 1);
   }
}//try
catch(Exception& e){exsSstEXCEPTION(ofs->elt,"__FormCreate()",e);}
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::IM_COPYClick(TObject *Sender)
{
int row = IM_DrawGrid->Row;
int col = IM_DrawGrid->Col;
if(col == 0)
  {
  RichEdit1->Clear();
  TImStr* imstr = Im.getStr(row);
  if(imstr)
    {
    switch(imstr->get_im_tt()){
           case IM_TEXT_TYPE_LOCAL_IM:
           case IM_TEXT_TYPE_REMOTE_IM:{
                queue<string> q;
                imstr->copy_of_issl_strings(q);
                while(!q.empty())
                     {
                     RichEdit1->Lines->Append(q.front().c_str());
                     q.pop();
                     }
                 break;
                 }
           }
    RichEdit1->SelectAll();
    RichEdit1->CutToClipboard();
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TCall_Panel::Call_Panel_Resize(TObject *Sender)
{
panel_resize();
}
//---------------------------------------------------------------------------
void __fastcall TCall_Panel::panel_resize()
{
if(Width < (6*2*mic_img->Width))
  {
    disc_img->Left   = 2;
    mic_img->Left    = disc_img->Left   + disc_img->Width;
    speak_img->Left  = mic_img->Left    + mic_img->Width;
    conf_img->Left   = speak_img->Left  + speak_img->Width;
    dial_img->Left   = conf_img->Left   + conf_img->Width;
    refer_img->Left  = dial_img->Left   + dial_img->Width;
    screen_img->Left = refer_img->Left  + refer_img->Width;
    cam_img->Left    = screen_img->Left + screen_img->Width;
    chat_img->Left   = cam_img->Left    + cam_img->Width;
    default_left     = false;
    return;
  }

if(Width < (8*2*mic_img->Width))
  {
  mic_img->Left    = disc_img->Left   + disc_img->Width + 10;
  speak_img->Left  = mic_img->Left    + mic_img->Width + 10;
  conf_img->Left   = speak_img->Left  + speak_img->Width + 10;
  dial_img->Left   = conf_img->Left   + conf_img->Width + 10;
  refer_img->Left  = dial_img->Left   + dial_img->Width + 10;
  screen_img->Left = refer_img->Left  + refer_img->Width + 10;
  cam_img->Left    = screen_img->Left + screen_img->Width + 10;
  chat_img->Left   = Width - chat_img->Width - 15;
  if(chat_img->Left < cam_img->Left + cam_img->Width)
    {
    disc_img->Left   = 2;
    mic_img->Left    = disc_img->Left   + disc_img->Width;
    speak_img->Left  = mic_img->Left    + mic_img->Width;
    conf_img->Left   = speak_img->Left  + speak_img->Width;
    dial_img->Left   = conf_img->Left   + conf_img->Width;
    refer_img->Left  = dial_img->Left   + dial_img->Width;
    screen_img->Left = refer_img->Left  + refer_img->Width;
    cam_img->Left    = screen_img->Left + screen_img->Width;
    chat_img->Left   = cam_img->Left    + cam_img->Width;
    }
  default_left     = false;
  }
else
  {
  if(!default_left)
    {
    disc_img->Left   = disc_img__default_left;
    mic_img->Left    = mic_img__default_left;
    speak_img->Left  = speak_img__default_left;
    conf_img->Left   = conf_img__default_left;
    dial_img->Left   = dial_img__default_left;
    refer_img->Left  = refer_img__default_left;
    screen_img->Left = screen_img__default_left;
    cam_img->Left    = cam_img__default_left;
    default_left     = true;
    }
  chat_img->Left = Width - chat_img->Width - 15;
  }
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::Image_RemoteVideoMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
#ifdef SIP_Video
if(X > 0)
   if(Y > 0)
      if(X < Image_RemoteVideo->Width)
         if(Y < Image_RemoteVideo->Height)
           {
           Image_RemoteVideo->Visible = false;
           Image_RemoteVideo->Tag     = 0;
           Form3->Remote_Video_Show();
           }
#endif
}
//---------------------------------------------------------------------------
void INSERT_S(const char* buf, int ffl)
{
if(buf)
  {
  string s = string(buf);
  MainFormSLS->OPB.insert(s,ffl);
  }
}
//----------------------------------------------------------------------------
void __fastcall TMainFormSLS::N18Click(TObject *Sender)
{
if(!CC_Panel->Visible)
  {
  GCS.Clear();
  GCS.CC_PANEL_TYPE             = CC_PANEL_TYPE__GROUP_CREATE;
  CC_Panel->Left                = 0;
  CC_DrawGrid->RowCount         = 1;
  MainFormSLS->CC_Panel->Top    = Panel1->Top + Panel1->Height;
  MainFormSLS->CC_Panel->Height = Panel_Chat->Top - Panel1->Top - Panel1->Height;
  CC_Panel->Width = MainFormSLS->Panel1->Width;
  GCS.set_CreateGroupChat_BtnState(CC_Img, BtnState_ACTIVE);
  CC_Panel->Show();
  }
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::ReflectCallingPartyHstry(TExchBuf* buf)
{
TContact ContCopy(-1);
int row_id = Sip->Contacts.get_row_id_by_contact_name(buf->msg,ContCopy);
if(row_id != -1)
  if(Sip->Contacts.get_sorted_by_full_name())
     row_id = Sip->Contacts.get_row_by_contact_id_in_sorted_contact_list(ContCopy.get_id());
if(row_id != -1)
  {
  if(row_id < DrawGrid1->RowCount)
    {
    DrawGrid1->Row = row_id;
    DrawGrid1->Repaint();
    user_name_to_send      = ContCopy.name;
    if(ContCopy.CT == ContactType_GROUP)
      set_IM_to_chat_participants(true);
    else
      set_IM_to_chat_participants(false);
    ComboBox1->Text        = ContCopy.full_name.c_str();
    CalledNameLbl->Caption = ContCopy.full_name.c_str();
    if(Im.get_selected_remote_user() != user_name_to_send)
      {
      Im.curr_hstry_period = -1;
      Im.set_selected_remote_user(user_name_to_send);
      Im.load_user_history();
      }
    }
  }
else //Not in the personal contact list, external number
  {
  user_name_to_send = buf->msg;
  if(buf->msg_5.empty())
    {
    ComboBox1->Text        = buf->msg.c_str();
    CalledNameLbl->Caption = buf->msg.c_str();
    }
  else
    {
    ComboBox1->Text        = buf->msg_5.c_str();
    CalledNameLbl->Caption = buf->msg_5.c_str();
    }
  }
}
//-----------------------------------------------------------------------------
void __fastcall TMainFormSLS::Button2Click(TObject *Sender)
{
/*
IM_DrawGrid->Refresh();
return;

//string file  = "C:\\wst\\noname.jpg";
//string file  = "C:\\wst\\neg.png";
//string file  = "C:\\wst\\переговоры.png";
string file  = "C:\\wst\\VID-20170118-WA0001.mp4";
ShellExecute(Handle, "open", file.c_str(), NULL, NULL, SW_SHOWMAXIMIZED);
return;

*/

/*
//string url = "www.google.com";
//https://rastel.dyndns-work.com:25070/download/upload_36353…
//http://rastel.dyndns-work.com:25069/download/"+fileId

//<file> id='upload_0eb30a0604d401c39421072215c97c64'  name='noname.JPG' </file>

string URL = "rastel.dyndns-work.com";
//string URL = "eu.vinteo.com";
//string url = "www.rastel.ru";
//string url = "rastel.dyndns-work.com:25070/download/upload_0eb30a0604d401c39421072215c97c64";
//string url = "rastel.dyndns-work.com/rastel/file-uploader/upload_0eb30a0604d401c39421072215c97c64";

//string url = "rastel.dyndns-work.com/uploads/upload_3ba0257a59414894d14a3e96adea0fa1";
//string url = "/download/upload_0eb30a0604d401c39421072215c97c64";
//string url = "/download/upload_3ba0257a59414894d14a3e96adea0fa1";

//string get_http = "GET / HTTP/1.1\r\nHost: " + url + "\r\nConnection: close\r\n\r\n";
//string get_http = "GET / HTTP/1.1 " + url + "\r\nConnection: close\r\n\r\n";
//string get_http = "GET " + url + " HTTP/1.1\r\n";


string url = "/download/upload_3ba0257a59414894d14a3e96adea0fa1";

string get_http  = "GET " + url + " HTTP/1.1\r\n";

//string get_http  = "POST " + url + " HTTP/1.1\r\n";
       get_http += "Host: rastel.dyndns-work.com:25069\r\n";
       get_http += "Connection: Keep-Alive\r\n\r\n";



hostent* sh = gethostbyname(URL.c_str());
if (sh != NULL)
   {
   queue <TIPAddress> q;
   int   i = 0;
   while(sh->h_addr_list[i])
        {
        struct   sockaddr_in   adr;
        memcpy(&adr.sin_addr,sh->h_addr_list[i],sh->h_length);
        string s_ipaddr = string(inet_ntoa(adr.sin_addr));
        TIPAddress ipaddr;
        ipaddr.IPAddr  = s_ipaddr;
        ipaddr.uIPAddr = exsConvStrIpAddrToUnsigned(s_ipaddr);
        q.push(ipaddr);
        i++;
        }
   if(!q.empty())
     {
     FILE* f = fopen("c:\\wst\\noname.JPG","wb");
     if(f)
       {

     SOCKET sck = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

     TIPAddress ipaddr = q.front();
     q.pop();
     struct sockaddr_in dest;
     memset(&dest,0,sizeof(dest));
     dest.sin_family      = AF_INET;
     dest.sin_addr.s_addr = inet_addr(ipaddr.IPAddr.c_str());
     dest.sin_port        = htons(25069); //htons(80);
   /*  while(!Terminated)
          {
          if(NextConnectTime.CurrentDateTime() < NextConnectTime)
            {
           ::Sleep(20);
            continue;
            }  */

          /*
          int  bcnnct = connect(sck,(struct sockaddr *)&dest, sizeof(dest));
          if(bcnnct == SOCKET_ERROR)
            {
          //  int a = 5;

          //  CheckConnError();
          //  sck = exsCreateTCPSocket_ADDR_ANY();  //::closesocket(sck) inside CheckConnError()
          //  continue;
            }

          send(sck, get_http.c_str(), strlen(get_http.c_str()), 0 );

           // recieve html
          int nDataLength = 0;
          char buffer[10000];
          string website_HTML;
          while ((nDataLength = recv(sck, buffer, 10000, 0)) > 0){
                // int i = 0;

                 fwrite(buffer, nDataLength, 1, f);

               //  while (buffer[i] >= 32 || buffer[i] == '\n' || buffer[i] == '\r'){
                        //website_HTML += string(buffer);
               //         i += 1;
               //         }
                }
            /*
          if(MainFormSLS->ofs)
            if(MainFormSLS->ofs->elt)
              if(MainFormSLS->ofs->elt->getlog())
                {
                string TimeStr;
                TDateTime DateTime = DateTime.CurrentDateTime();
                exsDateTime(DateTime,TimeStr);
                string str = "\n" + (string)TimeStr + website_HTML + "\n";
                MainFormSLS->ofs->elt->FputEvt(str, 1);
                }
                */
/*
          fclose(f);
          closesocket(sck);
          }

          }
   }
   */
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::Button8Click(TObject *Sender)
{
   /*
if(SaveDialog1->Execute())
  {

  int a = 5;
  }
   *

/*
if(!BLOCK_SEND_RTP)
    BLOCK_SEND_RTP = true;
else
    BLOCK_SEND_RTP = false;
*/


/*
TExchFileMsg ef;;
ef.s = "<file> id='upload_6b97d1c58d8627cc0735dae8ea89619e'  name='noname.JPG'  thumb='upload_ae94977b52410eadeecf17b8d96d9d3a' </file>";
FEXCH.fexch_ins(ef);


    BIO *sbio = NULL, *out = NULL;
    int i, len, rv;
    char tmpbuf[1024];
    SSL_CTX *ctx = NULL;
    SSL_CONF_CTX *cctx = NULL;
    SSL *ssl = NULL;
    CONF *conf = NULL;
    STACK_OF(CONF_VALUE) *sect = NULL;
    CONF_VALUE *cnf;
    const char *connect_str = "localhost:4433";
    long errline = -1;
   */
  //  conf = NCONF_new(NULL);

}
//---------------------------------------------------------------------------

void __fastcall TMainFormSLS::IM_DrawGridKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
IM_DrawGrid->Repaint();
//IM_DrawGrid->Refresh();
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::AddContact_ImgMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
set_img_cursor_type((TImage*)Sender);
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::DialNumber_ImgMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
set_img_cursor_type((TImage*)Sender);
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::Image_RemoteVideoMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
set_img_cursor_type((TImage*)Sender);
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::Image_StartChatMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
set_img_cursor_type((TImage*)Sender);
}
//---------------------------------------------------------------------------
//const N_SZ = 1500;
void __fastcall TMainFormSLS::Button3Click(TObject *Sender)
{
/*
//string dir       = "c:\\wst";
string file_name = "noname.png";
string dir       = "c:\\A";
//string file_name = "noname.jpg";
//string file_name = "upload_ae0369bf5a92e6445d0f41ff73a80207";
string path      = dir + "\\" + file_name;
int file_sz      = 0;
int block_length = 0;


     UBYTE send_buf[N_SZ];
     FILE* f = fopen(path.c_str(),"rb");
     if(f)
       {
       fseek(f, 0L, SEEK_END);
       file_sz = ftell(f);
       fseek(f, 0L, SEEK_SET);
       }

string URL = "rastel.dyndns-work.com";


string boundary           = "---------------------------7e1169311c0798";
string FirstBoundary      = "--" + boundary + crlf;
string ContentDisposition = "Content-Disposition: form-data; name=\"uploads[]\"; filename=" + (string)"\"" + file_name + "\"" + crlf;
string ContentType        = "Content-Type: image/jpeg\r\n\r\n";
string LastBoundary       = "\r\n-----------------------------7e1169311c0798--\r\n";


int LastBoundary_size = LastBoundary.size();

int content_length  =  FirstBoundary.length()      +
                       ContentDisposition.length() +
                       ContentType.length()        +
                       file_sz                     +
                       LastBoundary_size;



hostent* sh = gethostbyname(URL.c_str());
if (sh != NULL)
   {
   queue <TIPAddress> q;
   int   i = 0;
   while(sh->h_addr_list[i])
        {
        struct   sockaddr_in   adr;
        memcpy(&adr.sin_addr,sh->h_addr_list[i],sh->h_length);
        string s_ipaddr = string(inet_ntoa(adr.sin_addr));
        TIPAddress ipaddr;
        ipaddr.IPAddr  = s_ipaddr;
        ipaddr.uIPAddr = exsConvStrIpAddrToUnsigned(s_ipaddr);
        q.push(ipaddr);
        i++;
        }
   if(!q.empty())
     {
        SOCKET sck = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        TIPAddress ipaddr = q.front();
        q.pop();
        struct sockaddr_in dest;
        memset(&dest,0,sizeof(dest));
        dest.sin_family      = AF_INET;
        dest.sin_addr.s_addr = inet_addr(ipaddr.IPAddr.c_str());
        dest.sin_port        = htons(25069); //htons(80);

        int  bcnnct = connect(sck,(struct sockaddr *)&dest, sizeof(dest));
        if(bcnnct == SOCKET_ERROR)
            {
          //  int a = 5;

            }

*/

//string get_http  = "POST /upload HTTP/1.1\r\n";
//       get_http += "Accept: */*\r\n";
//       get_http += "X-Requested-With: XMLHttpRequest\r\n";
//       get_http += "Content-Type: multipart/form-data; boundary=" + boundary + crlf;
   //    get_http += "Referer: http://rastel.dyndns-work.com:25069/up/\r\n";
//       get_http += "Accept-Language: ru,en-US;q=0.7,en;q=0.3\r\n";
//       get_http += "Accept-Encoding: gzip, deflate\r\n";
    //   get_http += "User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/51.0.2704.79 Safari/537.36 Edge/14.14393\r\n";
//       get_http += "Host: rastel.dyndns-work.com:25069\r\n";
//       get_http += "Content-Length: " + uint_to_str(content_length) + "\r\n";
//       get_http += "Connection: Keep-Alive\r\n";
//       get_http += "Cache-Control: no-cache\r\n\r\n";
//       get_http += FirstBoundary      +
//                   ContentDisposition +
//                   ContentType;

  /*

         int head_sz = get_http.size();
         vector<UBYTE> v(head_sz);
         memcpy(&v[0], get_http.c_str(), head_sz);
         send(sck, &v[0], v.size(), 0);


        while(( block_length = fread(send_buf, 1, N_SZ, f)) == N_SZ)
              send(sck, send_buf, block_length, 0);
        if(block_length)
           send(sck, send_buf, block_length, 0);

        v.resize(LastBoundary_size);
        memcpy(&v[0], LastBoundary.c_str(), LastBoundary_size);
        send(sck, &v[0], v.size(), 0 );



           // receive html
          int nDataLength = 0;
          char buffer[10000];
          string website_HTML;
          while ((nDataLength = recv(sck, buffer, 10000, 0)) > 0){

        //  int a = 5;
          break;
                 //closesocket(sck);
//                fwrite(buffer, nDataLength, 1, f);

                }

          closesocket(sck);

     }
   }
   */
}
//---------------------------------------------------------------------------
void __fastcall TMainFormSLS::N19Click(TObject *Sender)
{
string show_dir = Im.get_show_dir();
if(!show_dir.empty())
  if(::DirectoryExists(show_dir.c_str()))
     ShellExecute(NULL, "explore", show_dir.c_str(), NULL , NULL, SW_SHOWNORMAL);
}
//----------------------------------------------------------------------------
string __fastcall TImSubStr::get_substr_by_pattern(const string& pat)
{
string rv;
int st = s.find(pat);
if(st == 0){
   st += pat.length();
       if(st < (int)s.length())
          rv = s.substr(st);
  }
return rv;
}
//-------------------------------------------------------------------------
 void __fastcall TImStr::__clear_ssl()
{
::EnterCriticalSection(&issl_cs);
  while(!__issl.empty()){
       TImSubStrList::iterator it = __issl.begin();
       TImSubStr* iss = (*it).second;
       if(iss)
          delete iss;
     __issl.erase(it);
       }
::LeaveCriticalSection(&issl_cs);
}
//---------------------------------------------------------------------------
void __fastcall TImStr::copy_of_issl_strings(vector<string>& v)
{
::EnterCriticalSection(&issl_cs);
  TImSubStrList::iterator it = __issl.begin();
  while(it != __issl.end())
        v.push_back((*it++).second->s);
::LeaveCriticalSection(&issl_cs);
}
//------------------------------------------------------------------------------
void __fastcall TImStr::copy_of_issl_strings(queue<string>& q)
{
::EnterCriticalSection(&issl_cs);
  TImSubStrList::iterator it = __issl.begin();
  while(it != __issl.end())
        q.push((*it++).second->s);
::LeaveCriticalSection(&issl_cs);
}
//------------------------------------------------------------------------------
void __fastcall TImStr::copy_of_issl_elements(queue<TImSubStr>& q)
{
::EnterCriticalSection(&issl_cs);
  TImSubStrList::iterator it = __issl.begin();
  while(it != __issl.end())
       q.push(*(*it++).second); //Затолкать в очередь копию содержимого TImSubStr*
::LeaveCriticalSection(&issl_cs);
}
//------------------------------------------------------------------------------
void __fastcall TImStr::set_top_row_height()
{
::EnterCriticalSection(&issl_cs);
  MainFormSLS->IM_DrawGrid->Canvas->Font->Style = TFontStyles();  //!!!
  display_layers = 1;
  int top  = 8;
  int left = 5;
  TImSubStrList::iterator it = __issl.begin();
  while(it != __issl.end())
     {
     TImSubStr* ISS = (*it++).second;
     if(ISS)
       {
       ISS->set_top_string_parameters(top,left);
       if(ISS->coord.period < 2)
         continue;
       if((ISS->coord.left + ISS->coord.width + 16) > MainFormSLS->IM_DrawGrid->ColWidths[0])
         {
         display_layers++;
         left = 5;
         AnsiString S = ISS->s.c_str();
         top += MainFormSLS->IM_DrawGrid->Canvas->TextHeight(S) + 2;
         ISS->set_top_string_parameters(top, left);
         }
       }
     }
  switch(display_layers){
      case  1: MainFormSLS->IM_DrawGrid->RowHeights[0] = 32; break;
      case  2: MainFormSLS->IM_DrawGrid->RowHeights[0] = 48; break;
      case  3: MainFormSLS->IM_DrawGrid->RowHeights[0] = 64; break;
      default: MainFormSLS->IM_DrawGrid->RowHeights[0] = 80; break;
      }
::LeaveCriticalSection(&issl_cs);
}
//------------------------------------------------------------------------------
int __fastcall TImStr::__calculate_row_height(int row_height)
{
int rv = row_height;
::EnterCriticalSection(&issl_cs);
  int sz = __issl.size();
  if(sz > 1)
    {
    rv = 0;
    TImSubStrList::iterator it = __issl.begin();
    while(it != __issl.end())
         {
         TImSubStr* iss = (*it++).second;
         if(iss)
            rv += iss->font_size + v_delta;
         }
    }
  switch(__im_tt){
       case IM_TEXT_TYPE_REM_ADDR:
       case IM_TEXT_TYPE_LOCAL_ADDR:
       case IM_TEXT_TYPE_DATE:
            rv += 5;
            break;
       }
::LeaveCriticalSection(&issl_cs);
return rv;
}
//-----------------------------------------------------------------------------
int __fastcall TImStr::__calculate_row_height__INSTANT_MESSAGE(int row_height_1)
{
int rv = row_height_1;
::EnterCriticalSection(&issl_cs);
  int sz = __issl.size();
  if(sz)
    {
  __clear_issl_m();
    int left, max_width;
    switch(__im_tt){
        case IM_TEXT_TYPE_REMOTE_IM: //remote IM
             left = REMOTE_IM_TEXT__LEFT;  //0
             break;
        case IM_TEXT_TYPE_LOCAL_IM: //local IM
             left = LOCAL_IM_TEXT__LEFT;  //40
             break;
        }
    max_width = MainFormSLS->IM_DrawGrid->ColWidths[0] - left;
    if(max_width >= 1)
      {
      rv = 0;
      TImSubStr* prev_trail_iss = NULL;
      TImSubStrList::iterator it = __issl.begin();
      while(it != __issl.end())
           {
           TImSubStr* ISS = (*it++).second;
           if(ISS)
             {
             queue<TImSubStr*> q;
             ISS->check_max_width(&prev_trail_iss, q, max_width); //Devide string on substrings in vector<TImSubStr*> v if TextWidth(S) > max_width
             if(q.size() == 1)
               {
               TImSubStr* iss = q.front();
               q.pop();
               rv += iss->font_size + v_delta;
               issl_m.insert(TImSubStrList::value_type(__subs_id_m++, iss));
               }
             else
               {
               while(!q.empty())
                    {
                    TImSubStr* iss = q.front();
                    q.pop();
                    if(q.empty())
                      {
                      prev_trail_iss = iss;
                      break;
                      }
                    rv += iss->font_size + v_delta;
                    issl_m.insert(TImSubStrList::value_type(__subs_id_m++, iss));
                    }
               }
             } //if(ISS)
           }  //while(it != issl.end())
      if(prev_trail_iss)
        {
        rv += prev_trail_iss->font_size + v_delta;
        issl_m.insert(TImSubStrList::value_type(__subs_id_m++, prev_trail_iss));
        }
      }  //if(max_width >= 1)
  }   //if(sz)
::LeaveCriticalSection(&issl_cs);
return rv + 5;
}
//------------------------------------------------------------------------------
/*
void __fastcall TImStr::check_on_href()
{
::EnterCriticalSection(&issl_cs);
  TImSubStrList::iterator it = __issl.begin();
  while(it != __issl.end())
       {
        it++;
       }
::LeaveCriticalSection(&issl_cs);
}
*/
//------------------------------------------------------------------------------
void __fastcall TMainFormSLS::IM_INVITE_ON_FILE_RECEIVING__DRAW_CELL(TGridDrawState State, TRect& Rect, TRect& Rect_1, TImStr* IS, TImSubStr& iss, queue<TImSubStr>& q_iss)
{

  /*
 TJPEGImage* examp = new TJPEGImage;
 Graphics::TBitmap* pBitmap = new Graphics::TBitmap();
 examp->Scale = jsEighth; //jsQuarter;
//  examp->LoadFromFile("C:\\A\\noname_jpg.jpg");
 examp->LoadFromFile("C:\\A\\99000000000245226_1920x1080.jpg");
 pBitmap->Assign(examp);

 if(State.Contains(gdFocused))
   {
   IM_DrawGrid->Canvas->Pen->Color = (TColor)0x00A0A0A0;
   IM_DrawGrid->Canvas->RoundRect(Rect_1.Left, Rect_1.Top, Rect_1.Right, Rect_1.Bottom, 20, 20);
   }
IM_DrawGrid->Canvas->Draw(Rect.Left + 6, Rect.Top + 3, pBitmap);
delete examp;
delete pBitmap;
  */



 if(State.Contains(gdFocused))
   {
   IM_DrawGrid->Canvas->Pen->Color = (TColor)0x00A0A0A0;
   IM_DrawGrid->Canvas->RoundRect(Rect_1.Left, Rect_1.Top, Rect_1.Right, Rect_1.Bottom, 20, 20);
   }

 if(IS->get_file_transfer_state() == 2) //file received
   IM_DrawGrid->Canvas->Draw(Rect.Left + LEFT_FILE_TRANSFER_ICON_POSITION, Rect.Top + TOP_FILE_TRANSFER_ICON_POSITION, rcv_file_img_1->Picture->Bitmap);
 else if(IS->get_file_transfer_state() == 3) //Not yet dowmloaded
   {
   if(Im.create_file_downloading_path(IS,0))
     {
     IS->set_file_transfer_state__RECVD();
     IM_DrawGrid->Canvas->Draw(Rect.Left + LEFT_FILE_TRANSFER_ICON_POSITION, Rect.Top + TOP_FILE_TRANSFER_ICON_POSITION, rcv_file_img_1->Picture->Bitmap);
     }
   else
     IM_DrawGrid->Canvas->Draw(Rect.Left + LEFT_FILE_TRANSFER_ICON_POSITION, Rect.Top + TOP_FILE_TRANSFER_ICON_POSITION, rcv_file_img->Picture->Bitmap);
   }
 else if(IS->get_file_transfer_state() == 0) //состояние еще не определено
   {
   if(Im.create_file_downloading_path(IS,0))
     {
     IS->set_file_transfer_state__RECVD();
     IM_DrawGrid->Canvas->Draw(Rect.Left + LEFT_FILE_TRANSFER_ICON_POSITION, Rect.Top + TOP_FILE_TRANSFER_ICON_POSITION, rcv_file_img_1->Picture->Bitmap);
     }
   else
     {
     IS->set_file_transfer_state__NOT_RECVD();
     IM_DrawGrid->Canvas->Draw(Rect.Left + LEFT_FILE_TRANSFER_ICON_POSITION, Rect.Top + TOP_FILE_TRANSFER_ICON_POSITION, rcv_file_img->Picture->Bitmap);
     }
   }
 else
   IM_DrawGrid->Canvas->Draw(Rect.Left + LEFT_FILE_TRANSFER_ICON_POSITION, Rect.Top + TOP_FILE_TRANSFER_ICON_POSITION, rcv_file_img->Picture->Bitmap);


 string file_name = iss.get_substr_by_pattern("name:");
 if(file_name.empty()){
   while(!q_iss.empty()){
         TImSubStr nexr_iss = q_iss.front();
         q_iss.pop();
         file_name = nexr_iss.get_substr_by_pattern("name:");
         if(!file_name.empty()){
           IM_DrawGrid->Canvas->TextOut( Rect.Left + LEFT_FILE_TRANSFER_ICON_POSITION + rcv_file_img->Width + 15, Rect.Top + 10, file_name.c_str());
           break;
           }
         }
   }   //if(file_name.empty()){

 switch(IS->get_file_transfer_state()){
       case 1:{ //file receiving ...
       IM_DrawGrid->Canvas->Font->Color = clGray;
       IM_DrawGrid->Canvas->TextOut( Rect.Left + LEFT_FILE_TRANSFER_ICON_POSITION + rcv_file_img->Width + 15, Rect.Top + 10 + IM_DrawGrid->Canvas->TextHeight(file_name.c_str()), "Загрузка файла ...");
       break;
       }
       case 2:{ //file received
       string s_size = IS->get_file_length();
       if(!s_size.empty())
         {
         IM_DrawGrid->Canvas->Font->Color = clGray; //clSilver; //(TColor)turquoise_color;
         IM_DrawGrid->Canvas->TextOut( Rect.Left + LEFT_FILE_TRANSFER_ICON_POSITION + rcv_file_img->Width + 15, Rect.Top + 10 + IM_DrawGrid->Canvas->TextHeight(file_name.c_str()), s_size.c_str());
         }
       break;
       }
    }  //switch(IS->get_file_transfer_state())
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void __fastcall TMainFormSLS::IM_INVITE_ON_FILE_SENDING__DRAW_CELL(TGridDrawState State, TRect& Rect, TRect& Rect_1, TImStr* IS, TImSubStr& iss, queue<TImSubStr>& q_iss)
{
if(State.Contains(gdFocused))
  {
  IM_DrawGrid->Canvas->Pen->Color = (TColor)0x00A0A0A0;
  IM_DrawGrid->Canvas->RoundRect(Rect_1.Left, Rect_1.Top, Rect_1.Right, Rect_1.Bottom, 20, 20);
  }
IM_DrawGrid->Canvas->Draw(Rect.Right - LEFT_FILE_TRANSFER_ICON_POSITION - rcv_file_img->Width, Rect.Top + TOP_FILE_TRANSFER_ICON_POSITION, rcv_file_img->Picture->Bitmap);

string file_name = iss.get_substr_by_pattern("name:");
if(file_name.empty()){
   while(!q_iss.empty()){
         TImSubStr nexr_iss = q_iss.front();
         q_iss.pop();
         file_name = nexr_iss.get_substr_by_pattern("name:");
         if(!file_name.empty()){
           int text_width = IM_DrawGrid->Canvas->TextWidth(file_name.c_str());
           IM_DrawGrid->Canvas->TextOut(Rect.Right - LEFT_FILE_TRANSFER_ICON_POSITION - rcv_file_img->Width - text_width - 15, Rect.Top + 10, file_name.c_str());
           string rez_text = "Файл отправлен.";
           text_width = IM_DrawGrid->Canvas->TextWidth(rez_text.c_str());
           IM_DrawGrid->Canvas->Font->Color = clGray;
           IM_DrawGrid->Canvas->TextOut(Rect.Right - LEFT_FILE_TRANSFER_ICON_POSITION - rcv_file_img->Width - text_width - 11, Rect.Top + 10 + IM_DrawGrid->Canvas->TextHeight(file_name.c_str()), rez_text.c_str());
           break;
           }
         }
   }   //if(file_name.empty()){
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------



