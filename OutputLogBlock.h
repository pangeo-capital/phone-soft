//-----------------------------------------------------------------------------
#ifndef Output_Log_Blocklog_H
#define Output_Log_Blocklog_H
#include <stdio.h>
#include <string>
//----------------------------------------------------------------------------
void INSERT_S(const char*, int);
//----------------------------------------------------------------------------
typedef  void (*pFunc_INSERT_S)(const char*, int);
//---------------------------------------------------------------------------
class TOutStruct{
public:
int  ffl;
std::string wstr;
TOutStruct(){
             ffl = 0;
             }
};
//------------------------------------------------
class TOutPutLogBlock{
CRITICAL_SECTION otfs;
std::queue<TOutStruct*> q;
public:
FILE* f;
void __fastcall insert(const std::string&, int);
bool __fastcall write();
void __fastcall write_finally();
 TOutPutLogBlock(){
	     ::InitializeCriticalSection(&otfs);
	       f = NULL;
               }
virtual ~TOutPutLogBlock(){
             ::DeleteCriticalSection(&otfs);
               }
};
//-----------------------------------------------
#endif  //#ifndef Output_Log_Blocklog_H

