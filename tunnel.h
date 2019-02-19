//---------------------------------------------------------------------------
#ifndef tunnelH
#define tunnelH
//---------------------------------------------------------------------------
#include "WinRDefs.h"
#include ".\\tls_sock\\include\\tls_sock.h"
#include "BaseThread.h"
#include "OutPutSipBuf.h"
#include "tcp.h"
#include <map>

using namespace std;
//---------------------------------------------------------------------------
class TSipRecvTunnelThread : public TBaseThread{
public:
void*  r;
string host;
int    port;
__fastcall TSipRecvTunnelThread(bool CS, const string& HOST, int PORT, TEventLogThread** ELTP, TSip* SIP):
                             TBaseThread(CS,ELTP,SIP){
                                                     r=(void*)0;
                                                     host = HOST;
                                                     port = PORT;
                                                     }
void __fastcall Execute();
};
//-----------------------------------------------------------------------------
class TSipSendTunnelThread : public TBaseThread{
public:
void*  r;
string host;
int    port;
__fastcall TSipSendTunnelThread(bool CS, const string& HOST, int PORT, TEventLogThread** ELTP, TSip* SIP):
                             TBaseThread(CS,ELTP,SIP){
                                                     r=(void*)0;
                                                     host = HOST;
                                                     port = PORT;
                                                     }
void __fastcall sendbuf(TOutputSipBuf*,unsigned);
void __fastcall sendbuf(TOutPutUdpBlock*,unsigned,const string&);
void __fastcall sendbuf(TOutPutDtmfBlock*,unsigned,const string&);
void __fastcall sendbuf(TSipParsBuf*,unsigned);
#ifdef SIP_LogSendPacket
void __fastcall LOG_SendPacket(TDateTime&,TOutPutUdpBlock*,int);
void __fastcall LOG_SendPacket(TDateTime&,TOutPutDtmfBlock*,int);
void __fastcall LOG_SendPacket(TDateTime&,TOutputSipBuf*,int);
void __fastcall LOG_SendPacket(TDateTime&,TSipParsBuf*,int);
#endif
void __fastcall Execute();
};
//-----------------------------------------------------------------------------
#endif
