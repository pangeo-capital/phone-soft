//---------------------------------------------------------------------------

#ifndef SoundTool_UnitH
#define SoundTool_UnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <map>
#include "WinRDefs.h"
#include <ComCtrls.hpp>
#include <vector>
#include <queue>
#include <string>
#include <ExtCtrls.hpp>

using namespace std;

#ifndef UBYTE
typedef unsigned char UBYTE;
#endif

#ifndef XBYTE
typedef unsigned short XBYTE;
#endif

//---------------------------------------------------------------------------
class TMediaDevice{
::CRITICAL_SECTION md_cs;
public:
string name;
int num;
void __fastcall set_media_device(const string&,int);
     __fastcall TMediaDevice(){
                              ::InitializeCriticalSection(&md_cs);
                              num = -1;
                              }
virtual __fastcall ~TMediaDevice(){
                                 ::DeleteCriticalSection(&md_cs);
                                 }
};
//----------------------------------------------------------------------------
class TIniSound{
bool __fastcall get_device(const string&, string&,string&,int);
bool __fastcall get_level(const string&, int&,string&,int);
bool __fastcall get_parameter(const string&,string&,int);
public:
string in_device;  //microphone
int    in_level;
string out_device; //dynamic
int    out_level;
string ring_device;
int    ring_to_speaker;
     __fastcall TIniSound(){
                      in_level        = 0;
                      out_level       = 0;
                      ring_to_speaker = 0;
                      }
void __fastcall get_user_sound_parameter(string&);                      
};
//----------------------------------------------------------------------------
typedef multimap < string, int, less <string>, allocator<string> > device_list;
//----------------------------------------------------------------------------
class TSoundTool : public TForm
{
device_list in_dev;
device_list out_dev;
int mic_level_corrector;
__published:	// IDE-managed Components
        TButton *Button3;
        TButton *Button4;
        TButton *Button5;
        TLabel *Label3;
        TEdit *Edit1;
        TEdit *Edit2;
        TButton *Button6;
        TLabel *Label8;
        TButton *Button7;
        TLabel *Label9;
        TLabel *Label10;
        TButton *Button8;
        TLabel *Label11;
        TButton *Button9;
        TLabel *Label12;
        TButton *Button10;
        TLabel *Label13;
        TLabel *Label14;
        TButton *Button11;
        TPanel *Panel1;
        TComboBox *ComboBox1;
        TBevel *Bevel1;
        TLabel *Label1;
        TProgressBar *ProgressBar1;
        TTrackBar *TrackBar2;
        TLabel *Label6;
        TLabel *Label7;
        TComboBox *ComboBox2;
        TProgressBar *ProgressBar2;
        TTrackBar *TrackBar1;
        TBevel *Bevel2;
        TLabel *Label2;
        TLabel *Label5;
        TLabel *Label4;
        TComboBox *ComboBox3;
        TBevel *Bevel3;
        TLabel *Label15;
        TButton *Button2;
        TButton *Button1;
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall Button3Click(TObject *Sender);
        void __fastcall Button4Click(TObject *Sender);
        void __fastcall Button5Click(TObject *Sender);
        void __fastcall TrackBar1Change(TObject *Sender);
        void __fastcall TrackBar2Change(TObject *Sender);
        void __fastcall Button6Click(TObject *Sender);
        void __fastcall Button7Click(TObject *Sender);
        void __fastcall Button8Click(TObject *Sender);
        void __fastcall Button9Click(TObject *Sender);
        void __fastcall Button10Click(TObject *Sender);
        void __fastcall Button11Click(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
void   __fastcall read_user_sound_data(const string&, queue<string>&);
void   __fastcall get_user_sound_data(queue<string>&);
public:		// User declarations
     __fastcall TSoundTool(TComponent* Owner);
device_list& __fastcall get_in_dev_list(){return in_dev;}
device_list& __fastcall get_out_dev_list(){return out_dev;}
void __fastcall ins_dev(device_list&,const string&,int);
int  __fastcall get_dev_by_string(device_list&,const string&);
int  __fastcall get_size(device_list&);
void __fastcall clear_dev(device_list&);
void __fastcall read_sound_data();
TIniSound IniSound;
int    start_type;
bool   stop_sound;
bool   echo_suppr;
bool   mic_filter;
bool   mic_silence_suppr;
bool   mic_noise_reduction;
short  mic_track_bar_prev_position;
double mic_pow_coeff;
bool   sound_filter;
bool   sound_silence_suppr;
bool   sound_noise_reduction;
bool   sound_record;
short  sound_track_bar_prev_position;
double sound_pow_coeff;
};
//---------------------------------------------------------------------------
extern PACKAGE TSoundTool *SoundTool;
//---------------------------------------------------------------------------
#endif
