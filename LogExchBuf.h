#ifndef SIP_CLIENT_LOG_EXCH_BUF_H
#define SIP_CLIENT_LOG_EXCH_BUF_H
//---------------------------------------------------------
typedef  bool  (*pfinFunc_OpenEvetsLogFile)(const char*);
typedef  void  (*pfinFunc_CloseEvetsLogFile)();
typedef  void  (*pfinFunc_INSERT)(const char*,int);
typedef  void  (*pfinFunc_INSERT_W)(const wchar_t*,int);
typedef  bool  (*pfinFunc_WRITE)();
//----------------------------------------------------------------------------
class TEvtLogDll{
public:
HINSTANCE HINST;
pfinFunc_OpenEvetsLogFile  pFunc_OELF;
pfinFunc_CloseEvetsLogFile pFunc_CELF;
pfinFunc_INSERT            pFunc_INSERT;
pfinFunc_INSERT_W          pFunc_INSERT_W;
pfinFunc_WRITE             pFunc_WRITE;
TEvtLogDll(){
            HINST          = NULL;
            pFunc_OELF     = NULL;
            pFunc_CELF     = NULL;
            pFunc_INSERT   = NULL;
            pFunc_INSERT_W = NULL;
            pFunc_WRITE    = NULL;
            }
};
//-----------------------------------------------------------------------------
#endif
