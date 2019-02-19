//-----------------------------------------------------------------------------
#ifndef Sip_Tcp_H
#define Sip_Tcp_H
#include "WinRDefs.h"
#include "BaseThread.h"
#include "OutPutSipBuf.h"
#include <map>

using namespace std;
//-----------------------------------------------------------------------------------
//--- TDateTime NextConnectTime_TCP -- определяет интервал через который
//--- инициируется след Connect после получения SOCKET ERROR. (т.е. определяет
//--- периодичность повторных попыток подсоединиться к серверу).
//--- TDateTime ConnTime_TCP  -- определяет интервал между двумя последовательными
//--- попытками сделать Connect. Дело в том, что некоторые провайдеры, в частности
//--- мобильные, сначала пропускают Connect от клиента, затем обращаются к БД и видя
//--- какие-то проблемы тут - же сбрасывают Connect. В результате генерируется большое
//--- количество попыток коннекта.
//------------------------------------------------------------------------------------
class TSipRecvTcpThread : public TBaseThread{
SOCKET sck;
unsigned  conn_count;
TDateTime NextConnectTime_TCP;
TDateTime ConnTime_TCP;            
public:
#ifndef INTRN_TCP
void*  r;     //connection reference (Used for  EXTRN_TCP)
#endif
string host;
int    port;
__fastcall TSipRecvTcpThread(bool CS, const string& HOST, int PORT, TEventLogThread** ELTP, TSip* SIP):
                             TBaseThread(CS,ELTP,SIP){
                                                     #ifndef INTRN_TCP
                                                     r=(void*)0;
                                                     #endif
                                                     sck        = INVALID_SOCKET;
                                                     conn_count = 0;
                                                     host = HOST;
                                                     port = PORT;
                                                     }
#ifndef INTRN_TCP
void   __fastcall Start_EXTRN_TCP();
#endif
void   __fastcall Start_INTRN_TCP();
SOCKET __fastcall get_sck(){return sck;}
void   __fastcall log_tcp_socket_action(SOCKET,int);
void   __fastcall CheckConnError(const string&);
void   __fastcall Connect();
void   __fastcall Receive();
void   __fastcall Execute();
};
//-----------------------------------------------------------------------------
class TSipSendTcpThread : public TBaseThread{
string host;
int    port;
public:
#ifndef INTRN_TCP
void*  r;
#endif
void __fastcall sendbuf(TOutputSipBuf*);
void __fastcall sendbuf(TOutPutUdpBlock*);
void __fastcall sendbuf(TSipParsBuf*);
#ifdef INTRN_TCP
void __fastcall send_tcp(const char*,int);
#endif
#ifdef SIP_LogSendPacket
void __fastcall LOG_SendPacket(TDateTime&,TOutPutUdpBlock*,int);
void __fastcall LOG_SendPacket(TDateTime&,TOutPutDtmfBlock*,int);
void __fastcall LOG_SendPacket(TDateTime&,TOutputSipBuf*,int);
void __fastcall LOG_SendPacket(TDateTime&,TSipParsBuf*,int);
#endif
     __fastcall TSipSendTcpThread(bool CS, const string& HOST, int PORT, TEventLogThread** ELTP, TSip* SIP):
                             TBaseThread(CS,ELTP,SIP){
                                                     #ifndef INTRN_TCP
                                                     r=(void*)0;
                                                     #endif
                                                     host = HOST;
                                                     port = PORT;
                                                     }
void __fastcall Execute();
};
//-----------------------------------------------------------------------------
int sock_debug_f(const char* /*severirty*/, const char* /*fmt*/, ...);
//-----------------------------------------------------------------------------
#endif
