//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "WinRDefs.h"
#include "log.h"
#include "utils.h"
#include <Filectrl.hpp>
#include <wstring.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
//----------------------------------------------------------------------------
void __fastcall TEventLogThread::FputEvt(const string& s,int ffl)
{
if(!s.empty())
  {
  pOPB->insert(s, ffl);

  /*
  if(ELD->pFunc_INSERT)
     (*ELD->pFunc_INSERT)(str.c_str(),ffl);
  */
  }
}
//---------------------------------------------------------------------------
void __fastcall TEventLogThread::openEvtLogFile()
{
if(!log)return;
TDateTime DateTime = DateTime.CurrentDateTime();
string time_str;
exsDateTime(DateTime,time_str);
string str = "\nEvents.log started " + time_str + "  SipClient v." + progvers;
if(!check_directory_existence(logdir))
   return;
string oldName;
string newName;
CLOSE_EVENTS_LOG_FILE();
string NewID = DateTime.FormatString("yyyymmdd_hhnnss").c_str();
oldName = logdir + "\\Events.log";
newName = logdir + "\\Events_" + NewID + ".log";
rename(oldName.c_str(),newName.c_str());
OPEN_EVENTS_LOG_FILE(oldName);
FputEvt(str,1);
}
//---------------------------------------------------------------------------
void __fastcall TEventLogThread::reOpenEvtLogFile()
{
if(!log)return;
TDateTime DateTime = DateTime.CurrentDateTime();
string startTime = DateTime.FormatString("dd-mm-yyyy hh:nn:ss").c_str();
string str = "\nEvents.log started " + startTime + "  SipClient v." + progvers;
string oldName;
string newName;
string NewID = DateTime.FormatString("yyyymmdd_hhnnss").c_str();
CLOSE_EVENTS_LOG_FILE();
oldName = logdir + "\\Events.log";
newName = logdir + "\\Events_" + NewID + ".log";
rename(oldName.c_str(),newName.c_str());
OPEN_EVENTS_LOG_FILE(oldName);
FputEvt(str,1);
}
//-----------------------------------------------------------------------------
void __fastcall TEventLogThread::OPEN_EVENTS_LOG_FILE(const string& filename)
{
if(pOPB->f)
  fclose(pOPB->f);
pOPB->f = fopen(filename.c_str(),"a+t");
if(pOPB->f)
   EventsLog = true;


/*
if(ELD->pFunc_OELF) //OpenLogFile
   EventsLog = (FILE*)(*ELD->pFunc_OELF)(filename.c_str());
 */
 }
//-----------------------------------------------------------------------------
void __fastcall TEventLogThread::CLOSE_EVENTS_LOG_FILE()
{
if(pOPB->f)
  {
  pOPB->write_finally();
  fclose(pOPB->f);
  pOPB->f = NULL;
  }
EventsLog = false;

  
/*
if(ELD->pFunc_CELF)
  {
  (*ELD->pFunc_CELF)(); //fclose(EventsLog);
  EventsLog = false;
  }
 */
}
//-----------------------------------------------------------------------------
void __fastcall TEventLogThread::closeEvtLogFile()
{
TDateTime DateTime;
string startTime = DateTime.CurrentDateTime().FormatString("dd-mm-yyyy hh:nn:ss").c_str();
string str = "\n\nFile closed " + startTime;
FputEvt(str,1);
CLOSE_EVENTS_LOG_FILE();
}
//---------------------------------------------------------------------------
void __fastcall TEventLogThread::OpenEventLogOnStart()
{
if(!log)return;
if(EventsLog)
   setReopenReq(2);
else
   setReopenReq(1);
}
//-----------------------------------------------------------------------------
void __fastcall TEventLogThread::Execute()
{
bool closereq = false;
try{
while(1)
 {
  if(reopenreq){
    switch(reopenreq){//open request
            case 1:
                   openEvtLogFile();
                   break;
            case 2: //reopen request
                   reOpenEvtLogFile();
                   break;
            case 3: //close req
                   closereq = true;
                   break;
            }
    reopenreq = 0;
    }
 /*
 TOutStruct* buf = opb->GetBuf();
 if(buf)
   {
   if(EventsLog)
     {
     if(buf->unicode)
       {
       wchar_t* s = L"Open\n";
       //fputws(buf->wstr.c_str(),EventsLog);
       fputws(s,EventsLog);
       fflush(EventsLog);
       }
     else
       {
       //std::string s = string(&buf->bf[0]);
       //wstring wstr = s2ws(s);
       wchar_t* s = L"Open\n";
       //fputws(wstr.c_str(),EventsLog);
       fputws(s,EventsLog);
       fflush(EventsLog);
       }
     //if(buf->ffl)
     //   fflush(EventsLog);
     }
   delete buf;
   }
   */
 if(!WRITE_MSG_TO_LOG_FILE())
   {
   if(closereq)
     {
     closereq = false;
     closeEvtLogFile();
     }
   if(Terminated)
     {
     if(term)
       {
       closeEvtLogFile();
       return;
       }
     else
       {
       term = true;
       continue;
       }
     }
   if(check_files_req)
      if(check_files_time_stamp())
         check_files_req = false;
   ::Sleep(1000);
   }

/*
   #ifdef RTP_Print_EventLogQueue
   if(EventsLog)
     {
     int sz  = opb->GetSize();
     if(sz)
        {
        wstring wstr = L"\n\nEvtLog queue : " + inttowstr(sz);
        fputws(wstr.c_str(),EventsLog);
        }
     }
   #endif
   */
 }  //while
}//try
catch ( ... ){
             // handler for any C++ exception
             //cout << "A C++ exception was thrown.";
             return;
             }
}
//----------------------------------------------------------------------------
__fastcall TOutputLogFileStruct::TOutputLogFileStruct(TOutPutLogBlock* p_OPB, const string& LogDir,int LogReq,const string& vers)
{
log = LogReq;
elt = new TEventLogThread(true, p_OPB, LogDir, vers, LogReq);
}
//-----------------------------------------------------------------------------
__fastcall TOutputLogFileStruct::~TOutputLogFileStruct()
{
if(elt)
  {
  TEventLogThread* ELT = elt;
  elt = NULL;
  ELT->Terminate();
  if(ELT->Suspended)
     ELT->Resume();
  ELT->WaitFor(); //Maybe delay for ::Sleep in the TEventLogThread
  delete ELT;
  }
}
//-----------------------------------------------------------------------------
void __fastcall TOutputLogFileStruct::sOpenAllLog()
{
if(elt)
  {
  elt->OpenEventLogOnStart();
  if(elt->Suspended)
     elt->Resume();
  }
}
//----------------------------------------------------------------------------
bool __fastcall TEventLogThread::check_files_time_stamp()
{
bool rv = true;
AnsiString Path = logdir.c_str();
if(::DirectoryExists(Path))
  {
  TDateTime curr_date = curr_date.CurrentDateTime();
  int iAttributes = faAnyFile;
  TSearchRec sr;
  int retVal = FindFirst(Path + "\\*.*",iAttributes,sr);    //First found directory, specified in the Path
  if(!retVal)
    {
     while(FindNext(sr) == 0)
          {
          if(sr.Name == "..")
             continue;
          if((double)(curr_date - FileDateToDateTime(sr.Time)) > event_log_life_time)
            {
            string name = sr.Name.LowerCase().c_str();
            AnsiString Ext = ExtractFileExt(sr.Name);
            Ext = Ext.LowerCase();
            if(Ext == ".log")
              {
              int st = name.find("events_");
              if(st == 0)
                if(DeleteFile(Path + "\\" + sr.Name))
                  {
                  rv = false;
                  break;
                  }
              }
            }
          }
    FindClose(sr);
    }
  }
return rv;
}
//----------------------------------------------------------------------------
bool __fastcall TEventLogThread::WRITE_MSG_TO_LOG_FILE()
{
return pOPB->write();

/*
bool rv = false;
if(ELD->pFunc_WRITE)
   rv = (*ELD->pFunc_WRITE)();
return rv;
*/
}
//----------------------------------------------------------------------------
bool __fastcall TOutPutLogBlock::write()
{
bool rv = false;
::EnterCriticalSection(&otfs);
  if(!q.empty())
    {
    TOutStruct* os = q.front();
    q.pop();
    if(f)
      {
      fputs(os->wstr.c_str(),f);
      if(os->ffl)
         fflush(f);
      }
    delete os;
    rv = true;
    }
::LeaveCriticalSection(&otfs);
return rv;
}
//-----------------------------------------------------------------------------
void __fastcall TOutPutLogBlock::write_finally()
{
::EnterCriticalSection(&otfs);
  while(!q.empty())
       {
       TOutStruct* os = q.front();
       q.pop();
       fputs(os->wstr.c_str(),f);
       delete os;
       }
::LeaveCriticalSection(&otfs);
}
//----------------------------------------------------------------------------
void __fastcall TOutPutLogBlock::insert(const string& s, int ffl)
{
TOutStruct* os = new TOutStruct;

/*
std::string s = std::string(buf);
int len;
int slength = (int)s.length() + 1;
len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
std::wstring wstr(len, L'\0');
MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, &wstr[0], len);
*/

os->wstr = s;
os->ffl  = ffl;
::EnterCriticalSection(&otfs);
  q.push(os);
::LeaveCriticalSection(&otfs);
}
//----------------------------------------------------------------



