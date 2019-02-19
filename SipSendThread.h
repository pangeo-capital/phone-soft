//---------------------------------------------------------------------------

#ifndef SipSendThreadH
#define SipSendThreadH

#include "WinRDefs.h"
#ifndef _WINSOCK2API_
 #include <winsock2.h>
#endif
#include "BaseThread.h"
#include "log.h"
#include "udp.h"
#include "OutPutSipBuf.h"
//---------------------------------------------------------------------------
class TSipSendThread : public TBaseThread{
SOCKET sck;
void __fastcall LOG_SendPacket(TDateTime&,TOutPutUdpBlock*,int);
void __fastcall LOG_SendPacket(TDateTime&,TOutputSipBuf*,int);
void __fastcall LOG_SendPacket(TDateTime&,TSipParsBuf*,int);
void __fastcall Error(const string&);
public:
void __fastcall sendbuf(TOutputSipBuf*);
void __fastcall sendbuf(TOutPutUdpBlock*);
void __fastcall sendbuf(TSipParsBuf*);
__fastcall TSipSendThread(bool CS, TEventLogThread** ELTP, SOCKET SCK, TSip* SIP):TBaseThread(CS, ELTP, SIP){
                                              sck = SCK;
                                              }
__fastcall ~TSipSendThread();
void __fastcall Execute();
};
//---------------------------------------------------------------------------
#endif
