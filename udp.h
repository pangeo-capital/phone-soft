#ifndef SIP_CLIENT_Udp_H
#define SIP_CLIENT_Udp_H

#include "WinRDefs.h"
#include "utils.h"

#ifndef XBYTE;
typedef unsigned short XBYTE;
#endif

//------------------------------------------------------------------------------
typedef enum{
UDP_MPT,
RTP_AUDIO_MPT,
RTCP_AUDIO_MPT,
#ifdef SIP_Video
RTP_VIDEO_MPT,
RTCP_VIDEO_MPT,
VIDEO_MPT,
#endif
SOUND_MPT,
SOUND_MPT_INIT,
INIT_MPT,
INIT_RTCP_MPT,
RTCP_VAD,
UNKNOWN_MPT,
}MediaPacketType;
//------------------------------------------------------------------------------
typedef enum{
START_DTT,
CONTINUE_DTT,
STOP_DTT,
PAUSE_DTT,
END_DTT,
}DtmfTransmitType;
//------------------------------------------------------------------------------
class TOutPutUdpBlock : public BaseExchangeBlock{
bool IntrnTcp;
public:
int pktn;
TDateTime dt;
BLOCKTYPE subtype;
MediaPacketType mpt;
unsigned seq_num;
bool decompressed;
bool duplicated;
int datasize;
bool local_loop;
int mb_nb;
string s;
string tunnel_name;
int remote_yuv420_width;
int remote_yuv420_height;
bool silence_suppr_queue;
bool mark;
bool discard;
double abs_max;
int dtmf_transmission_count;
vector<UBYTE> v;
vector<double> vd;
__fastcall TOutPutUdpBlock():BaseExchangeBlock(TOutPutUdpBlock_BLOCKTYPE){
                            mpt          = UNKNOWN_MPT;
                            subtype      = TOutPutUdpBlock_BLOCKTYPE;
                            IntrnTcp     = false;
                            seq_num      = 0;
                            decompressed = false;
                            duplicated   = false;
                            datasize=0;
                            local_loop   = false;
                            mb_nb=0;
                            remote_yuv420_width  = 0;
                            remote_yuv420_height = 0;
                            silence_suppr_queue  = false;
                            mark                 = false;
                            discard              = false;
                            abs_max = 0.0;
                            dtmf_transmission_count = 1;
                            }
__fastcall TOutPutUdpBlock(int& n):BaseExchangeBlock(TOutPutUdpBlock_BLOCKTYPE){
                            pktn = ++n;
                            mpt  = UNKNOWN_MPT;
                            IntrnTcp      = false;
                            seq_num       = 0;
                            decompressed  = false;
                            duplicated    = false;
                            datasize=0;
                            local_loop = false;
                            mb_nb=0;
                            remote_yuv420_width  = 0;
                            remote_yuv420_height = 0;
                            silence_suppr_queue  = false;
                            mark                 = false;
                            discard              = false;
                            abs_max = 0.0;
                            dtmf_transmission_count = 1;
                            }
virtual __fastcall ~TOutPutUdpBlock(){}
void __fastcall getDateTime(){dt = dt.CurrentDateTime();}
void __fastcall setIntrnTcp(){IntrnTcp = true;}
bool __fastcall getIntrnTcp(){return IntrnTcp;}
};
//----------------------------------------------------------------------------
class TOutPutDtmfBlock : public BaseExchangeBlock{
public:
int pktn;
DtmfTransmitType dtt;
TDateTime duration;
int event_duration; //standard 160
int marker;
int payloadtype;    //standard 101
string tunnel_name;
int dtmf_transmission_count;
vector<UBYTE> v;
void __fastcall first_byte(UBYTE);
void __fastcall second_byte(bool,int);
void __fastcall dig_duration(XBYTE);
__fastcall TOutPutDtmfBlock(int& n,DtmfTransmitType DTT,unsigned short DURATION,int EVENT_DURATION,int MARKER,int PAYLOADTYPE)
                           :BaseExchangeBlock(TOutPutDtmf_BLOCKTYPE){
                            pktn           = ++n;
                            marker         = MARKER;
                            payloadtype    = PAYLOADTYPE;
                            dtt            = DTT;
                            event_duration = EVENT_DURATION;
                            dtmf_transmission_count = 1;
                            if(DURATION > 999)
                               duration = TDateTime(0,0,0,999);
                            else
                               duration = TDateTime(0,0,0,DURATION);
                            }
};
//-----------------------------------------------------------------------------
#endif
