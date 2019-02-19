//---------------------------------------------------------------------------

#ifndef VideoH
#define VideoH
//---------------------------------------------------------------------------
#include "WinRDefs.h"
#ifdef SIP_Video
#include "BaseThread.h"
#include "vencpar.h"
#include "udp.h"

class TUdpChannel;
//---------------------------------------------------------------------------
typedef enum{
Video_Queue_State__NORMAL,
Video_Queue_State__WAIT_PSC,
Video_Queue_State__PASS_FRAME,
}Video_Queue_State;
//---------------------------------------------------------------------------
class TVideoInputThread : public TBaseThread{  //Receives Packets from vcam and sends to RTP Channel
void* Uc;  //TUdpChannel*
public:
__fastcall TVideoInputThread(bool CS,TEventLogThread** ELTP, TSip* SIP, void* UC):TBaseThread(CS, ELTP, SIP){
                            Uc=UC;
                            }

void  __fastcall Execute();
};
//---------------------------------------------------------------------------
class TVideoOutputThread : public TBaseThread{  //Receives Packets from RTP Channel and sends to Screen
TUdpChannel* Uc;   //TUdpChannel*
void __fastcall proc_Video_TOutPutUdpBlock(TOutPutUdpBlock*);
void __fastcall proc_Video_H263_Packet(TOutPutUdpBlock*,int sz);
void __fastcall proc_Video_H263_A_Mode(TOutPutUdpBlock*,int);
void __fastcall proc_Video_H263_B_C_Mode(TOutPutUdpBlock*,int);
void __fastcall proc_Video_H263_Plus_Packet(TOutPutUdpBlock*,int);
void __fastcall proc_Video_H263_Plus_A_Mode(TOutPutUdpBlock*,int);
void __fastcall proc_Video_H263_Plus_B_C_Mode(TOutPutUdpBlock*,int);
void __fastcall getPictureSize(int,int&,int&);
int decoderId;
int yuv420_rgb24_scalerId;
Video_Queue_State vqs;
public:
bool video_sending_only;   // from video cam to network
TDateTime ReportTime;
int JBD_video_max;
__fastcall TVideoOutputThread(bool CS, TEventLogThread** ELTP, TSip* SIP, TUdpChannel* UC):TBaseThread(CS, ELTP, SIP){
                            Uc = UC;
                            decoderId = vencdec_create_decoder();
                            yuv420_rgb24_scalerId = vencdec_create_scaler();
                            JBD_video_max = jitter_buffer_video_delay_maximum;
                            ReportTime    = ReportTime.CurrentDateTime();
                            vqs = Video_Queue_State__NORMAL;
                            video_sending_only = false;
                            }
__fastcall ~TVideoOutputThread(){
                                if(decoderId != -1)
                                   vencdec_destroy_decoder(decoderId);
                                if(yuv420_rgb24_scalerId != -1)
                                   vencdec_destroy_scaler(yuv420_rgb24_scalerId);
                                }
Video_Queue_State __fastcall get_Video_Queue_State(){return vqs;}
void __fastcall set_Video_Queue_State(Video_Queue_State VQS){vqs = VQS;}
void  __fastcall Execute();
};
#endif //#ifdef SIP_Video
//---------------------------------------------------------------------------
#endif