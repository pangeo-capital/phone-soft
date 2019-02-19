//-----------------------------------------------------------------------------
#ifndef Sip_Tls_H
#define Sip_Tls_H
#include "WinRDefs.h"
#include ".\\tls_sock\\include\\tls_sock.h"
#include "BaseThread.h"
#include "OutPutSipBuf.h"
#include "tcp.h"
#include <map>

using namespace std;
//-----------------------------------------------------------------------------
class TSipRecvTlsThread : public TBaseThread{
public:
void*  r;    //connection reference
string host;
int    port;
__fastcall TSipRecvTlsThread(bool CS, const string& HOST, int PORT, TEventLogThread** ELTP, TSip* SIP):
                             TBaseThread(CS,ELTP,SIP){
                                                     r=(void*)0;
                                                     host = HOST;
                                                     port = PORT;
                                                     }
void __fastcall Execute();
};
//-----------------------------------------------------------------------------
class TSipSendTlsThread : public TBaseThread{
public:
void*  r;     //connection reference (Used for  EXTRN_TCP)
string host;
int    port;
void __fastcall sendbuf(TOutputSipBuf*);
void __fastcall sendbuf(TOutPutUdpBlock*);
void __fastcall sendbuf(TSipParsBuf*);
#ifdef SIP_LogSendPacket
void __fastcall LOG_SendPacket(TDateTime&,TOutPutUdpBlock*,int);
void __fastcall LOG_SendPacket(TDateTime&,TOutPutDtmfBlock*,int);
void __fastcall LOG_SendPacket(TDateTime&,TOutputSipBuf*,int);
void __fastcall LOG_SendPacket(TDateTime&,TSipParsBuf*,int);
#endif
__fastcall TSipSendTlsThread(bool CS, const string& HOST, int PORT, TEventLogThread** ELTP, TSip* SIP):
                              TBaseThread(CS,ELTP,SIP){
                                                      r=(void*)0;
                                                      host = HOST;
                                                      port = PORT;
                                                      }
void __fastcall Execute();
};
//-----------------------------------------------------------------------------
#endif
