//---------------------------------------------------------------------------

#ifndef SoundH
#define SoundH

#include "WinRDefs.h"
#include <ComCtrls.hpp>
#include "BaseThread.h"
#include "utils.h"
#include "udp.h"
#include <mmsystem.h>
#include "mmreg.h"
#include <complex.h>
#include "Test_Sound.h"
#include "D_FastFourieTransform_Even.h"
#include "AudioInterface.h"
#include <vector>



using namespace std;

#ifndef XBYTE;
typedef unsigned short XBYTE;
#endif

class TWaveInputThread;
class TUdpChannel;
//------------------------------------------------------------------------------
typedef enum{
WaveInputState_PASSIVE,    //before Answer
WaveInputState_ACTIVE,     //after Answer
WaveInputState_DESTROY,
}TWaveInputState;
//------------------------------------------------------------------------------
typedef enum{
MicrophoneState_Passive,
MicrophoneState_Active
}TMicrophoneState;
//------------------------------------------------------------------------------
typedef enum{
WaveOutputState_Unknown,
WaveOutputState_REQUEST_TO_START_ALERTING,
WaveOutputState_START_ALERTING,
WaveOutputState_REQUEST_TO_STOP_ALERTING,
WaveOutputState_STOP_ALERTING,
WaveOutputState_REQUEST_TO_START_RECEIVING_VOICE,
WaveOutputState_RECEIVING_VOICE,
WaveOutputState_GEN_DTMF_DIGITS_START,
WaveOutputState_GEN_DTMF_DIGITS_CONTINUE,
WaveOutputState_GEN_DTMF_DIGITS_STOP,
WaveOutputState_DESTROY,
}TWaveOutputState;    //for playback
//------------------------------------------------------------------------------
typedef enum{
JBD_State_Start,
JBD_State_Stable,
JBD_State_Stable_Down,
JBD_State_Unknown,
}JBD_State;
//-----------------------------------------------------------------------------
typedef enum{
TVolume_Type__Mic,
TVolume_Type__Sound,
TVolume_Type__NDef,
}TVolume_Type;
//-----------------------------------------------------------------------------
class TCoeff_By_2{
public:
complex<double> sum_2;
complex<double> sum_4;
complex<double> sum_6;
complex<double> sum_8;
complex<double> sum_10;
complex<double> sum_12;
complex<double> sum_14;
complex<double> sum_16;
complex<double> sum_18;
complex<double> sum_20;
complex<double> sum_22;
complex<double> sum_24;
complex<double> sum_26;
complex<double> sum_28;
__fastcall TCoeff_By_2(){
                         sum_2 = 0.0;  //100 Hz
                         sum_4 = 0.0;  //200 Hz
                         sum_6 = 0.0;  //300
                         sum_8 = 0.0;  //400
                         sum_10 = 0.0;
                         sum_12 = 0.0; //600
                         sum_14 = 0.0; //700
                         sum_16 = 0.0; //800
                         sum_18 = 0.0; //900
                         sum_20 = 0.0;
                         sum_22 = 0.0; //1100
                         sum_24 = 0.0; //1200
                         sum_26 = 0.0; //1300
                         sum_28 = 0.0; //1400
                        }
public:
};
//-----------------------------------------------------------------------------
class TCoeff_By_5{
public:
complex<double> sum_5;
complex<double> sum_10;
complex<double> sum_15;
complex<double> sum_20;
complex<double> sum_25;
complex<double> sum_30;
complex<double> sum_35;
complex<double> sum_40;
complex<double> sum_45;
complex<double> sum_50;
complex<double> sum_55;
complex<double> sum_60;
complex<double> sum_65;
complex<double> sum_70;
__fastcall TCoeff_By_5(){
                        sum_5  = 0.0; //250  Hz
                        sum_10 = 0.0; //500  Hz
                        sum_15 = 0.0; //750  Hz
                        sum_20 = 0.0; //1000 Hz
                        sum_25 = 0.0; //1250 Hz
                        sum_30 = 0.0; //1500 Hz
                        sum_35 = 0.0; //1750 Hz
                        sum_40 = 0.0; //2000 Hz
                        sum_45 = 0.0; //2250 Hz
                        sum_50 = 0.0; //2500 Hz
                        sum_55 = 0.0; //2750 Hz
                        sum_60 = 0.0; //3000 Hz
                        sum_65 = 0.0; //3250 Hz
                        sum_70 = 0.0; //3000 Hz
                        }
};
//-----------------------------------------------------------------------------
class TWaveOutPutBuf : public BaseExchangeBlock{
public:
TDateTime dt;
vector<UBYTE> v;
__fastcall TWaveOutPutBuf():BaseExchangeBlock(TWaveOutPutBuf_BLOCKTYPE){
                                                                       }
void __fastcall getDateTime(){dt = dt.CurrentDateTime();}
};
//---------------------------------------------------------------------------
class TWaveBaseThread : public TBaseThread{
vector<double> prev_y;
void __fastcall save_previous(vector<short>&,vector<short>&,vector<double>&,int,int);
void __fastcall double_2_short_low_pass(vector<short>&,vector<double>&,int,bool);
void __fastcall get_max_val(vector<double>&,int);
protected:
TUdpChannel* Uc;  //TUdpChannel*
bool  Mute;
bool  Conf;
CRITICAL_SECTION whdr_cs;    //for whdr and hWaveOut
deque<WAVEHDR*> whdr;
WAVEFORMATEX pFormat;
unsigned nAvgBytesPerSec_devby_50;
public:
vector<short> PREV_X;
vector<short> PREV_X_1;
MMRESULT result;
bool record;
string record_file;
FILE* f;
void __fastcall get_sound_average_volume(const vector<UBYTE>&,queue<XBYTE>&,TProgressBar*);
void __fastcall display_on_prog_bar(vector<short>&,queue<XBYTE>&,TProgressBar*);
void __fastcall filter_HPF_K(vector<short>&,vector<UBYTE>&); //High_Pass_Filter Kauer
void __fastcall filter_HPF_K_1(vector<short>&,vector<UBYTE>&); //High_Pass_Filter Kauer
void __fastcall filter_HPF_FIRST_ORDER(vector<short>&,vector<UBYTE>&);
void __fastcall filter_LPF_K(vector<short>&,vector<UBYTE>&); //Low_Pass_Filter Kauer
void __fastcall filter_LPF_B(vector<short>&,vector<UBYTE>&); //Low_Pass_Filter Batterwort
     __fastcall TWaveBaseThread(bool CS, TEventLogThread** ELTP, TSip* SIP, TUdpChannel* UC):TBaseThread(CS, ELTP, SIP){
                            ::InitializeCriticalSection(&whdr_cs);
                            Uc     = UC;
                            Mute   = false;
                            Conf   = false;
                            nAvgBytesPerSec_devby_50 = 320;
                            result = 0;
                            record = false;
                            f      = NULL;
                            }
virtual __fastcall ~TWaveBaseThread(){
                                     ::DeleteCriticalSection(&whdr_cs);
                                     }
void  __fastcall push_whdr(WAVEHDR*);
int   __fastcall get_whdr_size();
bool  __fastcall is_whdr_empty();
int   __fastcall get_whdr_done_count();
void  __fastcall setConf(bool a){Conf = a;}
bool  __fastcall getConf(){return Conf;}
void  __fastcall setMute(bool a){Mute = a;}
//bool  __fastcall getMute(){return Mute;}
void  __fastcall wave_log(const string&);
void  __fastcall wave_error(const string&,MMRESULT);
void  __fastcall set_std_format();
TUdpChannel* __fastcall getUc(){return Uc;}
};
//---------------------------------------------------------------------------
class TSeq_Num_Counter{
unsigned  prev_seq_num;
unsigned  curr_seq_num;
unsigned  rcvd_count;
unsigned  loss_count;
unsigned  dupl_count;
unsigned  discarded;
public:
void __fastcall inc_discarded(){++discarded;}
void __fastcall set_sn(unsigned sn){
                        rcvd_count++;
                        if(!curr_seq_num)
                            curr_seq_num = sn;
                        else{
                            prev_seq_num = curr_seq_num;
                            curr_seq_num = sn;
                            unsigned diff = curr_seq_num - prev_seq_num;
                            if(diff > 1)
                              loss_count += diff - 1;
                            else if(diff == 0)
                              dupl_count++;
                            }
                        }
unsigned __fastcall get_rcvd_count(){return rcvd_count;}
unsigned __fastcall get_loss_count(){return loss_count;}
unsigned __fastcall get_dupl_count(){return dupl_count;}
unsigned __fastcall get_discarded_count(){return discarded;}
__fastcall TSeq_Num_Counter(){
             prev_seq_num = 0;
             curr_seq_num = 0;
             rcvd_count   = 0;
             loss_count   = 0;
             dupl_count   = 0;
             discarded    = 0;
             }
};
//---------------------------------------------------------------------------
class TAverageVol{
//unsigned echo_delay;
unsigned voice_activity_count;
unsigned voice_activity_threshold;
public:
deque<double> xyz;
bool voice;
double av_val; //среднее значение
int __fastcall detect_voice_activity(TWaveBaseThread*,TVolume_Type,int,TEdit*,double);
__fastcall TAverageVol(){
                        voice  = false;
                        av_val = 0.0;
                        voice_activity_count = 0;
                        voice_activity_threshold = 1;//2;  //max количество пакетов подр€д с уровнем больше среднегоб чтобы детектировать голос
                        }

};
//-------------------------------------------------------------------------
class TSilenceSuppressionBlock{
unsigned sil_sz_max;
unsigned sil_sz_cur_tail;
unsigned max_sz_cur_tail;
public:
deque<TOutPutUdpBlock*> sil;   //for silence supression
unsigned __fastcall get_sil_sz_max(){return sil_sz_max;}
unsigned __fastcall get_sil_sz_cur(){return sil_sz_cur_tail;}
unsigned __fastcall get_max_sz_cur_tail(){return max_sz_cur_tail;}
void     __fastcall dec_sil_sz_cur(){--sil_sz_cur_tail;}
void     __fastcall set_sil_sz_cur(){sil_sz_cur_tail = max_sz_cur_tail;}
         __fastcall TSilenceSuppressionBlock(){
                                     sil_sz_max = 10;//6;  //2
                                     max_sz_cur_tail = 40;
                                     }

};
//--------------------------------------------------------------------------
class TFreqComp{
public:
double ampl; //јмплитуда частотной составл€ющей
complex<double> sum_xx; //частотна€ составл€юща€ в комплексном виде
unsigned freq; //„астота (є гармоники 1 - 50 Hz; 10 - 500 Hz;20 - 1000 Hz; 40 - 2000 Hz)
double rs_16_10;
double rs_20_10;
double rs_40_10;
__fastcall TFreqComp(){
                      ampl = 0.0;
                      freq = 0;
                      rs_16_10 = 0.0;
                      rs_20_10 = 0.0;
                      rs_40_10 = 0.0;
                      }
};
//--------------------------------------------------------------------------
typedef multimap<double, TFreqComp, less<double>, allocator<double> > TFreqCompList;
//-------------------------------------------------------------------------
class TSampleFreqImage{  //„астотный имидж отсчета
public:
TDateTime dt;
double sum_pic_val;
double abs_a_max;
double freq_zero;
TFreqCompList fcl;
vector<short> sample;
int zc;              //zero crossing
vector<TFreqComp> v; //примен€етс€ в dft_2
vector<int> imax_ampl;
string smax_ampl;
double gradient; //gradient - разница между текущим значением  sample_value и предыдущим
void __fastcall insert(TFreqComp&);
bool __fastcall compare_by_quadrant(TFreqComp&);
bool __fastcall compare_by_max_ampl(TFreqComp&,int,int);
__fastcall TSampleFreqImage(){
                             //zc = 0;
                             sum_pic_val = 0.0;
                             abs_a_max   = 0.0;
                             freq_zero   = 0.0;
                             dt = dt.CurrentTime();
                             gradient = 0.0;
                             zc = 0;
                             }
};
//---------------------------------------------------------------------------
class TMicQueue{
CRITICAL_SECTION mqcs;
deque<TSampleFreqImage> q;
unsigned max_queue_size;
public:
int convers_state;
double local_max;
bool found;
void __fastcall push_mic_queue(TSampleFreqImage&);
void __fastcall clear_mic_queue();
int  __fastcall get_mic_queue_size();
__fastcall TMicQueue(){
                      ::InitializeCriticalSection(&mqcs);
                        max_queue_size = 7;
                        convers_state  = 0;
                        local_max      = 0.0;
                        found          = true;
                      }
virtual __fastcall ~TMicQueue(){
                               ::DeleteCriticalSection(&mqcs); 
                               }
};
//---------------------------------------------------------------------------
class TSoundQueue{
CRITICAL_SECTION eqcs;
deque<TSampleFreqImage> q;
public:
unsigned max_echo_delay;
int count_block;
void __fastcall push_sound_queue(TSampleFreqImage&);
void __fastcall get_sound_queue(deque<TSampleFreqImage>&);
int  __fastcall get_echo_queue_size();
__fastcall TSoundQueue(){
                       ::InitializeCriticalSection(&eqcs);
                         max_echo_delay = TTest_Sound->MAX_ECHO_DELAY;  //10; //30 * 20 = 600 ms
                         count_block = 0;
                        }
virtual __fastcall ~TSoundQueue(){
                                 ::DeleteCriticalSection(&eqcs);
                                 }
};
//---------------------------------------------------------------------------
class TMinValue{ //used for isertion instead echo in microphone sequence
public:
bool ready;
double min_val;
vector<UBYTE> v;
void __fastcall get_min_value(double,double,TOutPutUdpBlock*);
__fastcall TMinValue(){
                      ready = false;
                      min_val = 0.0;
                      }
};
//---------------------------------------------------------------------------
class TVolume{
TUdpChannel* Uc;
TVolume_Type vt;
bool sil_suppr;
bool noise_reduction;
bool sound_detected;
void __fastcall voice_detect_proc(TWaveBaseThread*,TOutPutUdpBlock*,TEdit*);
public:
//vector<UBYTE> prev;
TAverageVol av;
TSilenceSuppressionBlock ssb;

TSampleFreqImage prv_mic_sfi;
TMicQueue    mq; //ќчередь TSampleFreqImage от микрофона
TSoundQueue  eq; //ќчередь TSampleFreqImage из канала (sound)
TMinValue    mv;
void __fastcall pow_volume(vector<UBYTE>&,double);
void __fastcall pow_volume(TOutPutUdpBlock*,double);
//void __fastcall diff_volume(vector<UBYTE>&,vector<UBYTE>&);
void __fastcall voice_detect(TWaveBaseThread*,TOutPutUdpBlock*,TEdit*);
TOutPutUdpBlock* __fastcall silence_suppression();
int  __fastcall zero_crossing(vector<short>&);
void __fastcall dft(TWaveBaseThread*,TOutPutUdpBlock*,TSampleFreqImage&);
//void __fastcall dft_1(TWaveBaseThread* BT,TOutPutUdpBlock* opb,TSampleFreqImage&);
void __fastcall dft_2(TWaveBaseThread*,TOutPutUdpBlock*,TSampleFreqImage&);
#ifdef Full_Fourie_Transform
void __fastcall dft_full(TWaveBaseThread*,TOutPutUdpBlock*,TSampleFreqImage&);
void __fastcall dft_1_1(TWaveBaseThread*,TOutPutUdpBlock*,TSampleFreqImage&);
#endif
bool __fastcall compare_sfi_by_ampl(TSampleFreqImage&,TSampleFreqImage&);
bool __fastcall compare_sfi_by_ampl_1(TSampleFreqImage&,TSampleFreqImage&);
bool __fastcall compare_sfi_by_freq(TSampleFreqImage&,TSampleFreqImage&);
bool __fastcall compare_sfi_by_freq_full(TSampleFreqImage&,TSampleFreqImage&);
bool __fastcall compare_sfi(TSampleFreqImage&,TSampleFreqImage&);
void __fastcall Detect_Voice_Activity(TWaveBaseThread*,int,TEdit*,double);
void __fastcall set_volume_type(TUdpChannel* UC,TVolume_Type VT){
                                                         Uc = UC;
                                                         vt = VT;
                                                         sil_suppr = false;
                                                         noise_reduction = false;
                                                         sound_detected  = false;
                                                         }
     __fastcall TVolume(){
                         Uc = NULL;
                         vt = TVolume_Type__NDef;
                         sil_suppr = false;
                         noise_reduction = false;
                         sound_detected  = false;
                         }
};
//----------------------------------------------------------------------------
class TGenDTMFdig{
double ampl; //амплитуда каждой из 2-х частот
int N;       //количество отсчетов в однлм sample
public:
vector<UBYTE> out_ubyte;
vector<short> out_short;
int digit;
double w_l;  //начальные фаза сигнала
double w_h;  //начальные фаза сигнала
TWaveOutputState wos;
void __fastcall gen(double,double);
void __fastcall double_2_short(vector<double>&);
void __fastcall short_2_ubyte();
__fastcall TGenDTMFdig(){
                        ampl  = 5000;
                        N     = 160;
                        w_l   = 0.0;
                        w_h   = 0.0;
                        digit = 0;
                        wos = WaveOutputState_Unknown;
                        }
};
//----------------------------------------------------------------------------
class TWaveOutputThread : public TWaveBaseThread{  //Receives UDP(UDP/RTP) Packets and play to Audio Device
void     __fastcall procTWaveOutPutBuf(TWaveOutPutBuf*);
void     __fastcall procTOutPutUdpBlock(TOutPutUdpBlock**,int);
MMRESULT __fastcall WAVE_OUT_PREPARE_HEADER(WAVEHDR*,int);
MMRESULT __fastcall WAVE_OUT_WRITE(WAVEHDR*,int);
void     __fastcall proc_request_to_start_receiving_voice();
void     __fastcall proc_gen_dig_start();
void     __fastcall proc_gen_dig_stop();
void     __fastcall proc_request_to_start_alerting();
void     __fastcall proc_request_to_stop_alerting();
bool     __fastcall proc_stop_alerting();
BaseExchangeBlock* __fastcall get_Voice_Block_JBD_Stable_State();
//int       Req_To_Miss_Packet_Count;
int       JBD_Min;   //Minimum Jitter Buffer Delay
int       JBD_Max;   //Maximum Jitter Buffer Delay
JBD_State JBD_State; //Jitter Buffer Delay State
int       Requested_FormatTag;
TDateTime alerting_pause;
HWAVEOUT  hWaveOut; //used for playback thread. hWaveIn in this case == NULL; Access always via CriticalSection whdr_cs
public:
TSeq_Num_Counter SNC;
TWaveOutputState WOS;
TWaveOutputState STATIC_WOS; // Used for process only ONE WaveOutputState:  WaveOutputState_REQUEST_TO_START_RECEIVING_VOICE for protect from racing condtion with other WOS states
bool             DESTROY_REQUEST; //for protect from race condition with WOS (which is dynamic) - basically for WaveOutputState_DESTROY (some times we here alerting signal after disconnect)
TGenDTMFdig  dtmf;
TDateTime    ReportTime;
queue<XBYTE> xyz_out; //headphone
TVolume      sound_vol;
bool         SQC;     // start_adaptive_queue_correction;
//unsigned     count_after_mark;
MMRESULT __fastcall WAVE_OUT_OPEN(TWaveOutputState);
void     __fastcall WAVE_OUT_SET_VOLUME(int);
int      __fastcall GET_WAVE_FORMAT_TAG();
__fastcall TWaveOutputThread(bool CS, TEventLogThread** ELTP, TSip* SIP, TUdpChannel* UC):TWaveBaseThread(CS,ELTP,SIP,UC){
                            hWaveOut = NULL;
                            Requested_FormatTag = WAVE_FORMAT_ALAW;
                           // Req_To_Miss_Packet_Count = 0;
                            JBD_Min         = jitter_buffer_delay_minimum;
                            JBD_Max         = jitter_buffer_delay_maximum;
                            JBD_State       = JBD_State_Unknown;
                            ReportTime      = ReportTime.CurrentDateTime();
                            WOS             = WaveOutputState_Unknown;
                            STATIC_WOS      = WaveOutputState_Unknown;
                            DESTROY_REQUEST = false;
                            SQC             = false;
                            sound_vol.set_volume_type(UC,TVolume_Type__Sound);
                          //  count_after_mark = 0;
                            }
virtual __fastcall ~TWaveOutputThread(){}
void  __fastcall WAVE_OUT_RESET(TWaveOutputState);
bool  __fastcall try_UnprepareHeader();
void  __fastcall final_Unprepare_Out_Header();
void  __fastcall startAlerting();
void  __fastcall Stop_Alerting_FINALLY();
void  __fastcall startReceivingVoice(TRemoteMedia*);
int   __fastcall get_JBD_Max(){return JBD_Max;}
void  __fastcall Execute();
};
//----------------------------------------------------------------------------
class TMediaQueueStruct{
int chID;
queue<vector<UBYTE> > q;
public:
int  __fastcall get_chid(){return chID;}
int  __fastcall get_size(){return q.size();}
void __fastcall add_media_packet(vector<UBYTE>& v){q.push(v);}
void __fastcall get_first_media_packet(vector<UBYTE>&);
     __fastcall TMediaQueueStruct(int chid){
                               chID = chid;
                               }
};
//----------------------------------------------------------------------------
typedef map <int, TMediaQueueStruct*, less<int>, allocator<int> > TAudioConfQueueList;
//----------------------------------------------------------------------------
class TAudioConfQueueStruct{
CRITICAL_SECTION acql_cs;
TAudioConfQueueList acql;    //ch_Id->TMediaQueueStruct*
int JBD_Max;
public:
TEventLogThread** ELTP;
     __fastcall  TAudioConfQueueStruct(){
                                        ::InitializeCriticalSection(&acql_cs);
                                        JBD_Max = jitter_buffer_delay_audio_conf_maximum;
                                        ELTP = NULL;
                                        }
virtual __fastcall ~TAudioConfQueueStruct();

void __fastcall add_channel_to_conference(int);
void __fastcall delete_channel_from_conference(int);
int  __fastcall add_audio_packet(int,vector<UBYTE>&);
void __fastcall read_all_first_conf_packets(vector< vector<UBYTE> >&, int);
void __fastcall mix_audio_channels(const vector<UBYTE>&, vector<int>&, int);
#ifdef Log_Audio_Conference_Mixed_Packet
void __fastcall Write_ch_id_from_which_packet_mixed(TMediaQueueStruct*, int, const vector<UBYTE>&);
#endif
};
//----------------------------------------------------------------------------
class TCaptureDSPThread : public TThread{
public:
TAecControl* AEC;  //Do not delete in destructor
void*        ES;
bool         ProcComplete;
__fastcall TCaptureDSPThread(bool CS, TAecControl* aec, void* exch_struct):TThread(CS){
                            AEC          = aec;
                            ES           = exch_struct;
                            ProcComplete = false;
                            }
void __fastcall Execute();
};
//----------------------------------------------------------------------------
class TMicPause {
TDateTime   __time_of_last_rcvd_mic_packet;
TDateTime   __time_of_last_log_writing;
TDateTime   __critical_interval;       //врем€ отсутстви€ очередного пакета от микрофона
TDateTime   __writing_interval;        //интервал между запис€ми в лог
public:
void __fastcall set_time_of_last_rcvd_packt(){__time_of_last_rcvd_mic_packet = __time_of_last_rcvd_mic_packet.CurrentDateTime();}
bool __fastcall check_mic_supply_interval(TWaveInputThread*);
__fastcall TMicPause(){
                    __critical_interval = TDateTime(0,0,1,0); // 1 sec
                    __writing_interval  = TDateTime(0,0,2,0); // 2 sec
                      }
};
//----------------------------------------------------------------------------
class TWaveInputThread : public TWaveBaseThread{  //Receives Packets from microphone and sends to RTP Channel
TOutPutUdpBlock* __OPB; //Buffer for waiting next 160 bytes (if receoved only 160 bytes, not 320)
HWAVEIN            hWaveIn;
int                pckn;
unsigned           pckt_cnt;
TDateTime   __start_thread_time;
bool        __first_mic_packet_rcvd;
bool        __reinit_aec_by_timeout_first_mic_packet__done;
bool        __reinit_aec_by_big_samples_interval;
bool        __reinit_aec_by_big_samples_interval__done;
SipLegState __referenced_sls;
string      __referenced_call_id;
bool        __sending_voice_started;
MMRESULT  __fastcall WAVE_IN_OPEN();
MMRESULT  __fastcall WAVE_IN_START();
MMRESULT  __fastcall WAVE_IN_PREPARE_HEADER(WAVEHDR*,int);
MMRESULT  __fastcall WAVE_IN_ADD_BUFFER(WAVEHDR*,int);
void      __fastcall WAVE_IN_RESET(TWaveInputState);
void      __fastcall send_mixed_packet_to_all_conference_participants(TOutPutUdpBlock*,const vector<int>&,int);
void      __fastcall send_mic_packet_to_all_connected_channels(TOutPutUdpBlock*,const vector<int>&,int);
void      __fastcall _log_dsp_vad_event(int);
public:
TWaveInputState       WIS;
TMicrophoneState      MS;
TAudioConfQueueStruct acqs;
TMicPause             MP; //for log pauses in microphone packets rcvd
bool                  ch_conference_participant; //”частник конференции или нет ( в основном используетс€ дл€ обработки VAD)
bool                  ch_conference_bridge;      //ћедиа канал к которому принадлежит данный TWaveInputThread (mic) €вл€етс€ конференционным мостом
queue<XBYTE> xyz_in;  //mic
TVolume mic_vol;      //mic
int AVERAGE_BY_SEC;   //mic
int BYTE_CNT_BY_SEC;  //mic
//queue<short> av;      //mic

TDateTime dt_prev_mic_packet;

//------  for CaptureDSP (voice data from microphone receiving over Media Foundation Programming Interface from Digital Signal Processors on the voice board) --------
TAecControl           AEC; //for AEC DLL  //see Proc CaptureDSP(TAecControl*)
TOutPutUdpBlock* __fastcall ProDspData(TAExchBuf*,int&);
bool             __fastcall BROADCAST_CAPTURE_DSP_MIC_PACKET_TO_ALL_CONNECTED_CHANNELS(TOutPutUdpBlock*);
#ifdef Log_Capture_DSP
void             __fastcall LogCaptureDsp(TAExchBuf*);
#endif
#ifdef Log_Audio_Conference_Mixed_Packet
void __fastcall Write_Audio_Conference_Mixed_Packet(const vector<int>&,int,int);
#endif
//---------------------------------------------------
__fastcall TWaveInputThread(bool CS, TEventLogThread** ELTP, TSip* SIP, TUdpChannel* UC):TWaveBaseThread(CS, ELTP, SIP, UC){
                            pckn     = 0;
                            pckt_cnt = 0;
                            hWaveIn  = NULL;
                          __referenced_sls                               = SPS_UNKNOWN;
                          __first_mic_packet_rcvd                        = false;
                          __reinit_aec_by_timeout_first_mic_packet__done = false;
                          __reinit_aec_by_big_samples_interval           = false;
                          __reinit_aec_by_big_samples_interval__done     = false;
                          __sending_voice_started                        = false;
                            WIS = WaveInputState_PASSIVE;
                            MS  = MicrophoneState_Active;
                            ch_conference_participant = false;
                            ch_conference_bridge      = false;
                            mic_vol.set_volume_type(UC,TVolume_Type__Mic);
                            AVERAGE_BY_SEC  = 0;
                            BYTE_CNT_BY_SEC = 0;
                          __OPB             = NULL;
                            acqs.ELTP       = ELTP;
                            }
TOutPutUdpBlock* __fastcall getWaveData();
int              __fastcall AecDecodeVAD(short*);
void             __fastcall addNewInWaveHdr(int);
void             __fastcall final_Unprepare_In_Header();
void             __fastcall startSendingVoice();
void             __fastcall save_sls(SipLegState);
void             __fastcall save_callid(const string&);

bool             __fastcall first_mic_packet_rcvd(){return __first_mic_packet_rcvd;}
void             __fastcall set_first_mic_packet_rcvd(bool a){__first_mic_packet_rcvd = a;}
bool             __fastcall get_reinit_aec_by_timeout_first_mic_packet__done();

bool             __fastcall get_reinit_aec_by_big_samples_interval();
void             __fastcall set_reinit_aec_request_by_big_samples_interval(bool);

bool             __fastcall get_reinit_aec_by_big_samples_interval__done();

void             __fastcall log_first_received_packet_from_mic(int, int);
void             __fastcall log_aec_packet_count_20(TDateTime&, TDateTime&, int);
void             __fastcall log_packet_count_20(int);

void             __fastcall CALL_CONTINUE();
void             __fastcall RESTART_AEC_PROC(TCaptureDSPThread**, void*, int);
bool             __fastcall BROADCAST_MIC_PACKET_TO_ALL_CONNECTED_CHANNELS(TOutPutUdpBlock*);
void             __fastcall Execute();
};
//---------------------------------------------------------------------------
void __fastcall ddft_11(vector<short>&,complex<double>&);
void __fastcall ddft_22(vector<short>&,complex<double>&);
void __fastcall ddft_44(vector<short>&,complex<double>&);
void __fastcall ddft_by_2(vector<short>&,TCoeff_By_2&);
void __fastcall ddft_by_5(vector<short>&,TCoeff_By_5&);


void __fastcall normalize(TCoeff_BY_2&);
//---------------------------------------------------------------------------
#endif
