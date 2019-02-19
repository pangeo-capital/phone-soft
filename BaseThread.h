//---------------------------------------------------------------------------

#ifndef BaseThreadH
#define BaseThreadH

//#include <queue.h>
#include "WinRDefs.h"
#include <Classes.hpp>
#include "log.h"
#include "ExchEvent.h"

class TSip;
//---------------------------------------------------------------------------
class TBaseThread : public TThread{
int    suspend_count;
bool __close_req;
deque<void*> base_q;
deque<void*> base_sent;
protected:
TSip* Sip;
int checkCount;
TEventLogThread** eltp;
string lasterr;
void  __fastcall sendlasterr();
bool thread_block;
void __fastcall __clearBaseQueue();
public:
TDateTime     PrevPacketTime;
CRITICAL_SECTION sc;
void  __fastcall Suspend_Thread();
void  __fastcall Resume_Thread();

CRITICAL_SECTION in_queue;     // for deque<void*> q;
CRITICAL_SECTION base_sent_cs; // for deque<void*> base_sent;
void  __fastcall setQueue_not_suspended(void*);
void  __fastcall setQueue(void*);
void* __fastcall getQueue();
int   __fastcall getQueueSize();
bool  __fastcall QueueEmpty();

void __fastcall set_close_req(bool a){__close_req = a;}

void __fastcall getSent();
void __fastcall checkSent();
int  __fastcall getSentSize();
void __fastcall updateSentQueue(BaseExchangeBlock*, bool&);
string __fastcall get_tag(const string&);
//void __fastcall unknownBlockType();

CRITICAL_SECTION exchlst_cs;
queue<TExchBuf*> exchlst;
void __fastcall insertExchLst(TExchBuf*);
TExchBuf* __fastcall getExchLst();
void __fastcall clearExchLst();

void __fastcall set_thread_block(){thread_block = true;}
bool __fastcall get_thread_block(){return thread_block;}
void __fastcall reset_thread_block(){thread_block = false;}
void __fastcall LOG_SharingPacket(SOCKET sck, unsigned&, int, const string&,const vector<UBYTE>&,int);

TEventLogThread* __fastcall getLog();

__fastcall TBaseThread(bool CS,TEventLogThread** ELTP,TSip* SIP):TThread(CS){
                                                                  ::InitializeCriticalSection(&sc);
                                                                  ::InitializeCriticalSection(&in_queue);
                                                                  ::InitializeCriticalSection(&base_sent_cs);
                                                                  ::InitializeCriticalSection(&exchlst_cs);
                                                                __close_req = false;
                                                                  suspend_count=0;
                                                                  checkCount=0;
                                                                  eltp = ELTP;
                                                                  Sip  = SIP;
                                                                  thread_block = false;
                                                                  }
virtual __fastcall ~TBaseThread();
};
//---------------------------------------------------------------------------
#endif
