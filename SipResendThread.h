//---------------------------------------------------------------------------

#ifndef SipResendThreadH
#define SipResendThreadH

#include "WinRDefs.h"
#include "BaseThread.h"
#include "LegTrn.h"
#include "UserAgent_defs.h"
//---------------------------------------------------------------------------
class TResendReqData{
public:
string callid;
TDateTime dt;
int iStatus;
__fastcall TResendReqData(){iStatus=0;}
};
//---------------------------------------------------------------------------
typedef multimap < TDateTime, string, less<TDateTime>, allocator<TDateTime> > TResendList;
//----------------------------------------------------------------------------
class TSipResendThread : public TBaseThread{
SipUAThreadType uatt;
TResendList rsl;
void __fastcall logResendListSize(const string&);
void __fastcall log_Erase_Resend_Req(const TResendReqData&);
public:
CRITICAL_SECTION srst_cs;
void __fastcall insertResendList(const TResendReqData&);
void __fastcall eraseResendReq(const TResendReqData&);
int  __fastcall procResendBlock(TResendReqData&);
int  __fastcall getRslSize();
__fastcall TSipResendThread(bool CS, TEventLogThread** ELTP, SipUAThreadType UATT, TSip* SIP):TBaseThread(CS, ELTP, SIP){
                            ::InitializeCriticalSection(&srst_cs);
                            uatt = UATT;
                            }
virtual __fastcall ~TSipResendThread();
void __fastcall Execute();
};
//----------------------------------------------------------------------------
#endif





