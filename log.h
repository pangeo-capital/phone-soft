//-----------------------------------------------------------------------------
#ifndef log_H
#define log_H
#include "WinRDefs.h"
#include <vector>
#include <map>
#include <queue>
#include "LogExchBuf.h"
#include "OutputLogBlock.h"

using namespace std;
//----------------------------------------------------------------------------
/*
class TOutStruct{
public:
int  ffl;
//std::wstring wstr;
std::string wstr;
TOutStruct(){
             ffl = 0;
             }
};
//------------------------------------------------
class TOutPutBlock{
CRITICAL_SECTION otfs;
std::queue<TOutStruct*> q;
public:
FILE* f;
void __fastcall insert(const string&, int);
//void __fastcall insert_w(const wchar_t*,int);
bool __fastcall write();
void __fastcall write_finally();
 TOutPutBlock(){
	     ::InitializeCriticalSection(&otfs);
	       f = NULL;
               }
~TOutPutBlock(){
             ::DeleteCriticalSection(&otfs);
               }
};
*/
//-----------------------------------------------
class TEventLogThread : public TThread{
int log;
bool term;
int reopenreq;
string logdir;
string progvers;
bool check_files_req;
double event_log_life_time;
//TEvtLogDll* ELD;  //::LoadLibrary EventLogDll
void __fastcall OPEN_EVENTS_LOG_FILE(const string&);
void __fastcall CLOSE_EVENTS_LOG_FILE();
bool __fastcall WRITE_MSG_TO_LOG_FILE();
public:
bool EventsLog;
TOutPutLogBlock* pOPB;   //Do not delete in destructor !!!
void __fastcall FputEvt(const string&,int = 0);
//void __fastcall FputEvtW(const wstring&,int = 0);
void __fastcall setReopenReq(int a){reopenreq = a;}
int  __fastcall getlog(){return log;}
void __fastcall openEvtLogFile();
void __fastcall reOpenEvtLogFile();
void __fastcall closeEvtLogFile();
void __fastcall OpenEventLogOnStart();
void __fastcall set_check_files_req(){check_files_req = true;}
bool __fastcall check_files_time_stamp();
__fastcall TEventLogThread(bool CS, TOutPutLogBlock* p_opb, const string& LogDir, const string& vers, int Log):TThread(CS){
                                                       term      = false;
                                                       reopenreq = 0;
                                                       EventsLog = false;
                                                       pOPB      = p_opb;
                                                       logdir    = LogDir;
                                                       progvers  = vers;
                                                       log       = Log;
                                                       check_files_req = false;
                                                       event_log_life_time = 3; //7; // 14; //days
                                                     //   ELD = eld;
                                                       }
virtual __fastcall ~TEventLogThread(){
                             if(EventsLog)
                               closeEvtLogFile();
                         //    if(ELD)
                         //      delete ELD;
                             }
void  __fastcall Execute();
};
//-----------------------------------------------------------------------------
class TOutputLogFileStruct{
int log;
public:
TEventLogThread* elt; //Thread for output EventsLog
int  __fastcall getLog(){return log;}
void __fastcall sOpenAllLog();
__fastcall  TOutputLogFileStruct(TOutPutLogBlock*, const string&, int,const string&);
virtual __fastcall ~TOutputLogFileStruct();
};
//-----------------------------------------------------------------------------


#endif
