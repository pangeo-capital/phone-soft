//---------------------------------------------------------------------------
#ifndef Unit3H
#define Unit3H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ImgList.hpp>
#include <ExtCtrls.hpp>
#include "WinRDefs.h"

#ifdef SIP_Video
#include "Unit4.h"

const SC_vert_addition_F3 = 100;

const SC_default_Remote_ScreenWidth = 352;//1280;//640;//352;
const SC_default_Remote_ScreenHeight = 288;//1024;//480;//288;
//---------------------------------------------------------------------------
typedef enum{
WM_FORM3_MSG_WPARAM__NDEF,
}WM_FORM3_MSG_WPARAM;
//---------------------------------------------------------------------------
typedef enum{
WM_FORM3_MSG_LPARAM__NDEF,
}WM_FORM3_MSG_LPARAM;
//---------------------------------------------------------------------------
class TForm3 : public TForm
{
HWND MF_Handle;
bool resize_block;
vector<UBYTE> screen_frame;
Lang lng;
int curWidth;
int curHeight;
passiveScreenSizeType psst;
bool ResizeReq;

int video_call_tag;
LegType leg_type;

TDateTime PrevVFrameTime;
TDateTime dt_1_sec;
int frame_count;

TDateTime ResizeTime;

bool block_hide_panel1;     //Если курсор над img1, то блокировать (block_hide_panel1 = true) выполнение Panel1->Hide()
TDateTime Prev_Start_Video_Show;
TDateTime Hide_Start_Video_Delay;
int prev_X;
int prev_Y;

CRITICAL_SECTION      f3_exch_list_cs;
queue<TExchBuf*>      f3_exch_list;      //queue for exchage of control msgs
TExchBuf* __fastcall _get_exch_buf();
void      __fastcall _clear_f3_exch_list();

CRITICAL_SECTION q_cs;
queue<TOutPutUdpBlock*> q;          //queue for received video packets (очередь на отображение)
TOutPutUdpBlock* __fastcall get_first_vblock();
void             __fastcall clear_q();

void __fastcall img1_size_position();
void __fastcall check_on_corrective_resize_req();
void __fastcall corrective_resize();
void __fastcall LocalVideoPanel_TopLeftCorn();
void __fastcall panel1_initsize();

__published:	// IDE-managed Components
        TImageList *ImageList1;
        TTimer *Timer1;
        TPanel *LocalVideoPanel;
        TImage *LocalVideoImage;
        void __fastcall FormResize(TObject *Sender);
        void __fastcall FormMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall FormHide(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall FormMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
        void __fastcall LocalVideoImageMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall FormDestroy(TObject *Sender);
private:	// User declarations
public:		// User declarations
Graphics::TBitmap* bitmap;
TPanel* Panel1;
TImage* img1;
bool call_in_progress;
bool close_request;
     __fastcall TForm3(TComponent* Owner);
void __fastcall Panel1Resize(TObject *Sender);
void __fastcall Img1MouseMove(TObject *Sender,TShiftState Shift, int X, int Y);
void __fastcall Img1MouseUp(TObject *Sender,TMouseButton Button, TShiftState Shift, int X, int Y);
void __fastcall panel1_resize();
void __fastcall set_video_call_tag(int a){video_call_tag = a;}
int  __fastcall get_video_call_tag(){return video_call_tag;}
void __fastcall set_leg_type(LegType a){leg_type = a;}
LegType __fastcall get_leg_type(){return leg_type;}
void __fastcall Prepare_Form3_Show();
void __fastcall Remote_Video_Show();
void __fastcall set_bitmap_size(TOutPutUdpBlock*);
void __fastcall load_rcvd_frame_to_bitmap(TOutPutUdpBlock*);
void __fastcall draw_bitmap_on_screen(int,int);

void __fastcall Get_REMOTE_VIDEO_MSG(TMessage &Message);
void __fastcall proc_remote_video_event(TExchBuf*);

int  __fastcall getSize();
void __fastcall push_block(TOutPutUdpBlock*);

void __fastcall ins_exch_buf(TExchBuf*);
void __fastcall show_remote_video(TExchBuf*);
void __fastcall update_remote_video(TExchBuf*);

BEGIN_MESSAGE_MAP
MESSAGE_HANDLER(REMOTE_VIDEO_MSG, TMessage, Get_REMOTE_VIDEO_MSG)
END_MESSAGE_MAP(TForm)
};
//---------------------------------------------------------------------------
extern PACKAGE TForm3 *Form3;
//---------------------------------------------------------------------------
#endif //#ifdef SIP_Video
#endif
