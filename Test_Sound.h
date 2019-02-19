//---------------------------------------------------------------------------

#ifndef Test_SoundH
#define Test_SoundH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TTTest_Sound : public TForm
{
__published:	// IDE-managed Components
        TButton *Button1;
        TOpenDialog *OpenDialog1;
        TCheckBox *MicLog;
        TCheckBox *SoundLog;
        TButton *Button5;
        TLabel *Noise_Suppression;
        TCheckBox *sqrt;
        TButton *Button6;
        TEdit *Edit1;
        TLabel *Label4;
        TLabel *Label5;
        TCheckBox *First_Block_Only;
        TLabel *Label1;
        TCheckBox *Echo_Log;
        TEdit *Edit2;
        TLabel *Label2;
        TEdit *Edit3;
        TLabel *Label6;
        TButton *Button2;
        TButton *Button3;
        TCheckBox *Subst_For_Echo;
        TLabel *Label7;
        TCheckBox *Freq_Check;
        TGroupBox *GroupBox1;
        TRadioButton *Normal;
        TRadioButton *Sin;
        TRadioButton *RadioButton3;
        TRadioButton *Blackman;
        TRadioButton *Hann;
        TCheckBox *kih;
        TCheckBox *Log_In_Out;
        TCheckBox *HF_Suppr;
        TCheckBox *LF_Suppr;
        TButton *Button4;
        TEdit *Edit4;
        TCheckBox *ec_mic;
        TCheckBox *ec_sound;
        TCheckBox *Left_Half_Spect;
        TCheckBox *dft_full;
        TCheckBox *mic_dft_full_log;
        TCheckBox *sound_dft_full_log;
        TCheckBox *dft_full_freq;
        TButton *Button7;
        TEdit *Edit5;
        TLabel *Label3;
        TButton *Button8;
        TEdit *Edit6;
        TCheckBox *FourieTransform;
        TEdit *Edit7;
        TEdit *Edit8;
        TButton *Button9;
        TEdit *Edit9;
        TLabel *Label8;
        TLabel *Label9;
        TLabel *Label10;
        TButton *Button10;
        TEdit *Edit10;
        TLabel *Label11;
        TButton *Button11;
        TCheckBox *JBD_Min;
        TCheckBox *JBD_Min_Control;
        TCheckBox *ChDispUnpackRtpPacket;
        TLabel *Label12;
        TCheckBox *ChDispToDouble;
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Button5Click(TObject *Sender);
        void __fastcall Button6Click(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall Button3Click(TObject *Sender);
        void __fastcall Button4Click(TObject *Sender);
        void __fastcall Button7Click(TObject *Sender);
        void __fastcall Button8Click(TObject *Sender);
        void __fastcall Button9Click(TObject *Sender);
        void __fastcall Button10Click(TObject *Sender);
        void __fastcall Button11Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TTTest_Sound(TComponent* Owner);
bool echo_compensation;
int MAX_ECHO_DELAY;
double MIC_LEVEL;
double SOUND_LEVEL;
int LF_Suppr_Freq;
int freq_number;
bool Bound;
int voice_count;
int FGC; //First Garmonic Component
int Left_Margin;
};
//---------------------------------------------------------------------------
extern PACKAGE TTTest_Sound *TTest_Sound;
//---------------------------------------------------------------------------
#endif
