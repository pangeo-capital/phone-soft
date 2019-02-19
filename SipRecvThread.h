//---------------------------------------------------------------------------

#ifndef SipRecvThreadH
#define SipRecvThreadH

#include "WinRDefs.h"
#ifndef _WINSOCK2API_
 #include <winsock2.h>
#endif
#include "BaseThread.h"
#include "log.h"
#include "udp.h"

class TParallelPhoneStruct;
const SIP_MAX_PACKET = 8192;//2048;
//---------------------------------------------------------------------------
class TSipRecvThread : public TBaseThread{
SOCKET sck;
int pktn;
char rcvbuf[SIP_MAX_PACKET];
public:
__fastcall TSipRecvThread(bool CS,TEventLogThread** ELTP,SOCKET SCK,TSip* SIP):TBaseThread(CS,ELTP,SIP){
                                              sck=SCK;
                                              pktn=0;
                                              }
__fastcall ~TSipRecvThread(){
                            #ifdef SIP_Thread_Destruction_Log
                            TEventLogThread* elt = getLog();
                            if(elt)elt->FputEvt("\n~TSipRecvThread()");
                            #endif
                            }
void __fastcall Execute();
};
//---------------------------------------------------------------------------
//------------------- For Parallel Phone ------------------------------------
//---------------------------------------------------------------------------
class TSipRecvThread_PPH : public TBaseThread{
SOCKET sck;
int pktn;
TParallelPhoneStruct* pps;
char rcvbuf[SIP_MAX_PACKET];
public:
__fastcall TSipRecvThread_PPH(bool CS,TEventLogThread** ELTP, SOCKET SCK, TSip* SIP, TParallelPhoneStruct* PPS):TBaseThread(CS,ELTP,SIP){
                                              sck  = SCK;
                                              pktn = 0;
                                              pps  = PPS;
                                              }
virtual __fastcall ~TSipRecvThread_PPH(){
                            #ifdef SIP_Thread_Destruction_Log
                            TEventLogThread* elt = getLog();
                            if(elt)elt->FputEvt("\n~TSipRecvThread_PPH()");
                            #endif
                            }
void __fastcall setsck(SOCKET SCK){sck = SCK;}                            
void __fastcall Execute();
};
//---------------------------------------------------------------------------
#endif

