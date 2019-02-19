//---------------------------------------------------------------------------

#ifndef ParallelPhone_UnitH
#define ParallelPhone_UnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#ifndef _WINSOCK2API_
 #include <winsock2.h>
#endif
#include <string>
#include "wm_def.h"
#include "SipRecvThread.h"
#include "SipUacThread.h"
#include "SipUasThread.h"
#include "SipParsThread.h"
#include "SipSendThread.h"
#include "CallIn_Unit.h"

using namespace std;

class TSip;
//---------------------------------------------------------------------------
class TParallelPhoneStruct{
SOCKET SCK;
TEventLogThread** eltp;
bool     Active;
bool     Registered;
UINT     UasPort;       // Port for UAS (5060)

CRITICAL_SECTION pps_cs;
string pps_Name;        // user name of parallel phone
string reg_Addr;        // address of registered parallel phone

public:
TSip* Sip;
TSipRecvThread_PPH* srt_pph;
TSipUacThread*      uac_pph;
TSipUasThread*      uas_pph;
TSipParsThread*     spt_pph;
TSipSendThread*     sst_pph;


UINT                regUAddr;
UINT                regPort;    //port of registered parallel phone

UINT                expires_sec;  //expiration interval in sec
TDateTime           next_reg;     //Date of the next Registration

void   __fastcall setSCK(SOCKET sck){SCK = sck;}
bool   __fastcall getActive(){return Active;}
bool   __fastcall getRegistered(){return Registered;}
UINT   __fastcall getPort(){return UasPort;}
string __fastcall getName(){
                           string rv;
                           ::EnterCriticalSection(&pps_cs);
                             rv = pps_Name;
                           ::LeaveCriticalSection(&pps_cs);
                           return rv;
                           }
void   __fastcall setName(const string& s){
                            ::EnterCriticalSection(&pps_cs);
                              pps_Name = s;
                            ::LeaveCriticalSection(&pps_cs);
                           }
string __fastcall getRegAddr(){
                           string rv;
                           ::EnterCriticalSection(&pps_cs);
                             rv = reg_Addr;
                           ::LeaveCriticalSection(&pps_cs);
                           return rv;
                           }

void   __fastcall setRegAddr(const string& s){
                           ::EnterCriticalSection(&pps_cs);
                             reg_Addr = s;
                           ::LeaveCriticalSection(&pps_cs);
                           }
void    __fastcall setActive(bool a){Active = a;}
void    __fastcall setRegistered(bool a){Registered = a;}
void    __fastcall setPort(UINT a){UasPort = a;}
void    __fastcall copyData(TParallelPhoneStruct&);
void    __fastcall writeRegistry();
void    __fastcall readRegistry();
SOCKET  __fastcall CreateSock();
void    __fastcall set_eltp(TEventLogThread** p){eltp = p;}

void __fastcall send_200OK_OnRegister_To_PPH(TSipParsBuf*);
void __fastcall prepare_Initial_200OK_OnRegister_To_PPH(TSipParsBuf*);
void __fastcall Check_IN_Call_To_ParallelPhone(TSipParsBuf*, TForm1*);
void __fastcall Check_OUT_Call_To_ParallelPhone(TSipParsBuf*, TMediaSession*);
bool __fastcall check_register_interval();
void __fastcall prepareRequestLine_INVITE_PPH(TOutputSipBuf*);
void __fastcall prepareContact_PPH(BaseExchangeBlock*,const string&);
void __fastcall prepareInitialTo_PPH(TOutputSipBuf*);
void __fastcall prepareFrom_PPH(TOutputSipBuf*,const string&,const string&);
void __fastcall prepareCallID_INVITE_PPH(TOutputSipBuf*, const string&);
void __fastcall prepare_Sdp_Initial_PPH(TSdp*,const string&);

__fastcall TParallelPhoneStruct(){
                                 ::InitializeCriticalSection(&pps_cs);
                                 SCK         = INVALID_SOCKET;
                                 Active      = false;
                                 Registered  = false;
                                 UasPort     = 5060;
                                 Sip         = NULL;
                                 srt_pph     = NULL;
                                 uac_pph     = NULL;
                                 uas_pph     = NULL;
                                 spt_pph     = NULL;
                                 sst_pph     = NULL;
                                 regUAddr    = 0;
                                 regPort     = 0;
                                 expires_sec = 0;
                                 }
virtual __fastcall ~TParallelPhoneStruct();
};
//---------------------------------------------------------------------------
class TParallelPhone : public TForm
{
__published:	// IDE-managed Components
        TEdit *Edit1;
        TLabel *Label1;
        TEdit *Edit2;
        TLabel *Label2;
        TButton *Button1;
        TCheckBox *CheckBox1;
        void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
     __fastcall TParallelPhone(TComponent* Owner);
void __fastcall ReadFormToPPS(TParallelPhoneStruct&);
bool __fastcall Compare(TParallelPhoneStruct*,TParallelPhoneStruct*);
void __fastcall ReadPPSToForm();
void __fastcall Get_PPH_CONTROL_MSG(TMessage &Message);
BEGIN_MESSAGE_MAP
    MESSAGE_HANDLER(CONTROL_MSG,  TMessage, Get_PPH_CONTROL_MSG)
END_MESSAGE_MAP(TForm)
};
//---------------------------------------------------------------------------
extern PACKAGE TParallelPhone *ParallelPhone;
//---------------------------------------------------------------------------
#endif
