#ifndef LastCallsFileThread_UnitH
#define LastCallsFileThread_UnitH

#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include "WinRDefs.h"
#include <queue>
#include <map>
#include <string>
#include <stdio.h>

using namespace std;

#ifndef UBYTE
typedef unsigned char UBYTE;
#endif

#define LAST_CALL_NAME_LENGTH  65
#define LAST_CALL_DATE_LENGTH  8

class TImStr;
class TIM_Struct;
//------------------------------------------------------------------------------
typedef enum{
WRITE,
READ,
SAVE_COMMENT,
CLEAR_COMMENT,
SAVE_CONTACT_COMMENT,
CLEAR_CONTACT_COMMENT,
LOAD_USER_HSTRY,
HSTRY_WRITE,
}LCS_TYPE;
//------------------------------------------------------------------------------
class TLCSBuf{
public:
LCS_TYPE type;
UBYTE name[LAST_CALL_NAME_LENGTH];
UBYTE date[LAST_CALL_DATE_LENGTH];
SYSTEMTIME START_TIME;
SYSTEMTIME END_TIME;
string s;
string s_1;
string s_2;
string s_3;
string s_4;
string s_5;
vector<string> v;
bool new_registration;
TImStr* IS;    //!!!Do not delete in destructor
__fastcall TLCSBuf(LCS_TYPE);
};
//------------------------------------------------------------------------------
class TLastCallFileStruct{
typedef map < string, unsigned > TLC_ContactFile_List; //name -> Position in the LastCall file
public:
unsigned             id;                   // Position in the Last Call contact file (0 - нулевая строка 1- первая и т.д.)
TLC_ContactFile_List lc_contact_file_list; // Last Call contact name -> id.
queue<unsigned>      free_ids;             // свободные id. Получаются после удаления из списка LastCalls после превышения лимита по количеству.
int       __fastcall get_name_id(const string&);
int       __fastcall get_free_id(const string&);
unsigned  __fastcall calculate_file_position(unsigned);
__fastcall TLastCallFileStruct(){
                                 id = 0;
                                }
};
//------------------------------------------------------------------------------
class TLastCallsFileThread : public TThread{
CRITICAL_SECTION lcs_cs;
queue<TLCSBuf*> q;
int __sz;
int __pos1;
int __pos2;
int __elem_sz;
void __fastcall _write(TLCSBuf*);
void __fastcall _read(TLCSBuf*);
void __fastcall _save_comment(TLCSBuf*);
void __fastcall _clear_comment();
void __fastcall _save_contact_comment(TLCSBuf*);
void __fastcall _clear_contact_comment(TLCSBuf*);
void __fastcall _hstry_load(TLCSBuf*);
void __fastcall _hstry_display_and_write(TLCSBuf*);
void __fastcall _hstry_display(TLCSBuf*);
void __fastcall _hstry_write_to_file(TLCSBuf*);
void __fastcall _check_to_delete_str(TLCSBuf*);
bool __fastcall _check_preliminary_time_interval(TLCSBuf*);
bool __fastcall _check_complete_time_interval(TLCSBuf*);
void __fastcall __read_mtd_file(TIM_Struct*,const string&);
void __fastcall __modify_mtd_file(const string&,TLCSBuf*);
void __fastcall __separate_dir_name(const string&, string&, string&);
void __fastcall __check_on_file_existence(TLCSBuf*);
TLastCallFileStruct LCFS;
bool  __fastcall open_last_calls_file();
FILE* __fastcall open_comment_file();
FILE* LCF;
public:
         __fastcall TLastCallsFileThread::TLastCallsFileThread(bool CS)
                  : TThread(CS){
                      ::InitializeCriticalSection(&lcs_cs);
                        LCF     = NULL;
                      __elem_sz = sizeof(UBYTE);      //first byte - 0xFF - buzy string; 0x00 - free
                      __pos1    = __elem_sz;
                      __pos2    = __pos1 + LAST_CALL_NAME_LENGTH;
                      __sz      = __pos2 + LAST_CALL_DATE_LENGTH;
                      }
virtual  __fastcall ~TLastCallsFileThread(){
                        if(LCF)
                          fclose(LCF);
                      ::DeleteCriticalSection(&lcs_cs);
                      }
void     __fastcall Execute();
void     __fastcall push_lcs_buf(TLCSBuf*);
TLCSBuf* __fastcall get_lcs_buf();
void     __fastcall PROC_LCS(TLCSBuf*);
};
//------------------------------------------------------------------------------
#endif