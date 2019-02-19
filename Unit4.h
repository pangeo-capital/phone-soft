//---------------------------------------------------------------------------

#ifndef Unit4H
#define Unit4H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include "WinRDefs.h"
#include <ImgList.hpp>
#include <Graphics.hpp>

#ifdef SIP_Video
#include "SipClient_Unit.h"
#include <vector>
#include <map>
#include <Menus.hpp>
#include <ImgList.hpp>

#define H263P_HEADER_SIZE       2
#define H263_HEADER_MODE_A_SIZE 4
#define H263_HEADER_MODE_B_SIZE 8
#define H263_HEADER_MODE_C_SIZE 12

using namespace std;

const SC_defaultCamWidth     = 352; //640;//704;//352;//176;////704;////160;//176;//320;//640; //176;  //640;
const SC_defaultCamHeight    = 288; //480;//576;//288;// ;// 576;////120;//144;// 240;//480; //144;  //480;

const SC_defaultNetWidth     = 352; //176;//704;//352;//
const SC_defaultNetHeight    = 288; //144;//576;//288;//

const SC_default_Local_ScreenWidth  = 352;   //640; 704;
const SC_default_Local_ScreenHeight = 288;  //480;  576;

//---------------------------------------------------------------------------
typedef enum{
passiveScreenSizeType_Width,
passiveScreenSizeType_Height,
passiveScreenSizeType_Unknown
}passiveScreenSizeType;
//---------------------------------------------------------------------------
typedef map <int,string,less <int>,allocator <int> > TVCam_List;
//---------------------------------------------------------------------------
class TForm4 : public TForm
{
HWND MF_Handle;
TEventLogThread** eltp;
bool vc_user_selected; //VCam has been selected by user in the Tools dialog
TVCam_List vc_list;
int video_call_tag;
LegType leg_type;
int prevTop;
int prevLeft;
int prevWidth;
int prevHeight;
int prevWinState;
bool ResizeReq;
bool FormIsFullScreen;
TDateTime ResizeTime;

bool block_hide_panel1;
TDateTime Prev_Start_Video_Show;
TDateTime Hide_Start_Video_Delay;
int prev_X;
int prev_Y;

int send_video_pckn;
passiveScreenSizeType psst;
CRITICAL_SECTION vcl_cs;
deque<int> video_ch_id_list;
deque<TOutPutUdpBlock*> sent;
void __fastcall updateSentQueue_2(TOutPutUdpBlock*);
void __fastcall getSent_2();
bool __fastcall check_brand_name(TVCam_List::iterator&);
bool __fastcall check_usb_device(TVCam_List::iterator&);
void __fastcall corrective_resize();
void __fastcall check_on_corrective_resize_req();
void __fastcall panel1_initsize();
void __fastcall panel1_resize();
void __fastcall top_left_btn_init_position();
void __fastcall img1_size_position();
void __fastcall prepare_frame_to_send(vector<UCHAR>&);
void __fastcall load_vcam_frame_to_bitmap();
void __fastcall draw_bitmap_on_screen();
void __fastcall __read_registry_video_dev();
__published:	// IDE-managed Components
        TTimer *Timer1;
        TButton *Button1;
        TButton *Button2;
        TImageList *ImageList1;
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormResize(TObject *Sender);
        void __fastcall FormMouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall Button1MouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall FormMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
        void __fastcall FormDestroy(TObject *Sender);
private:	// User declarations
public:		// User declarations
TVencPar venc_par;
int      devID;
bool     vcam_reinit_req;
string vcam_selected_auto;    // used in Form2 only (for reference only - initial filling Form2->CheckBox1)
string vcam_user_selected;    // used if(vc_user_selected == true)
bool resize_block;
int vcam_width;
int vcam_height;
int vcam_size;
int net_width;
int net_height;
vector<UBYTE> vcam_frame;
vector<UBYTE> screen_frame;
int curWidth;
int curHeight;
unsigned rtp_hdr;
Graphics::TBitmap* bitmap;
TPanel* Panel1;
TImage* img1;
//TImage* FullScreen1;
TDateTime BtnUpTmStmp;
void __fastcall Img1MouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
void __fastcall Img1MouseUp(TObject *Sender,TMouseButton Button, TShiftState Shift, int X, int Y);
void __fastcall Panel1Resize(TObject *Sender);
void __fastcall ins_vcl(int);
void __fastcall del_vcl(int);
bool __fastcall is_vcl_empty();
void __fastcall get_all_vcl(deque<int>&);
void __fastcall send_frame(UCHAR*,int,int);
void __fastcall set_video_call_tag(int a){video_call_tag = a;}
int  __fastcall get_video_call_tag(){return video_call_tag;}
void __fastcall set_leg_type(LegType a){leg_type = a;}
LegType __fastcall get_leg_type(){return leg_type;}
void __fastcall set_bitmap_size();
//void __fastcall full_screen_img__size_position();
//void __fastcall OnForm3Resize();
void __fastcall log_selected_vcam();
void __fastcall select_vcam_by_name();
void __fastcall select_first_active_vc();
bool __fastcall get_vc_user_selected(){return vc_user_selected;}
void __fastcall set_vc_user_selected(bool a){vc_user_selected = a;}
void __fastcall start_video_call();
void __fastcall Prepare_Form4_Show();
void __fastcall Local_Video_Show();
void __fastcall select_vcam();
int  __fastcall create_vcam_list();
void __fastcall get_all_device_name(queue<string>&);
void __fastcall select_vcam_by_appr_name(const string&);
void __fastcall deactivate_selected_video_camera();
     __fastcall TForm4(TComponent* Owner);
};
//---------------------------------------------------------------------------
void rtpCallBack ( int encoderId, UCHAR* data, int size, int mb_nb );
//---------------------------------------------------------------------------
extern PACKAGE TForm4 *Form4;
//---------------------------------------------------------------------------
#endif //#ifdef SIP_Video
#endif
