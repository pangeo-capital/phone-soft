#include <vcl.h>
#pragma hdrstop

#include "LastCallsFileThread_Unit.h"
#include "SipClient_Unit.h"
#include <Filectrl.hpp>

#pragma package(smart_init)
//------------------------------------------------------------------------------
void _fastcall TLastCallsFileThread::Execute()
{
while(!Terminated)
     {
     TLCSBuf* buf = get_lcs_buf();
     if(buf)
       {
       PROC_LCS(buf);
       delete buf;
       continue;
       }
     Suspend();
     }
}
//------------------------------------------------------------------------------
__fastcall TLCSBuf::TLCSBuf(LCS_TYPE TYPE)
{
type    = TYPE;
setmem(&name[0],sizeof(name),0);
setmem(&date[0],sizeof(date),0);
new_registration = false;
IS = NULL;
}
//----------------------------------------------------------------------------
void __fastcall TLastCallsFileThread::push_lcs_buf(TLCSBuf* buf)
{
::EnterCriticalSection(&lcs_cs);
  q.push(buf);
  if(Suspended)
     Resume();
::LeaveCriticalSection(&lcs_cs);
}
//------------------------------------------------------------------------------
TLCSBuf* __fastcall TLastCallsFileThread::get_lcs_buf()
{
TLCSBuf* rv = NULL;
::EnterCriticalSection(&lcs_cs);
  if(!q.empty())
    {
    rv = q.front();
    q.pop();
    }
::LeaveCriticalSection(&lcs_cs);
return rv;
}
//------------------------------------------------------------------------------
void __fastcall TLastCallsFileThread::PROC_LCS(TLCSBuf* buf)
{
switch(buf->type){
      case WRITE:                 _write(buf);                   break;
      case READ:                  _read(buf);                    break;
      case SAVE_COMMENT:          _save_comment(buf);            break;
      case CLEAR_COMMENT:         _clear_comment();              break;
      case SAVE_CONTACT_COMMENT:  _save_contact_comment(buf);    break;
      case CLEAR_CONTACT_COMMENT: _clear_contact_comment(buf);   break;
      case LOAD_USER_HSTRY:       _hstry_load(buf);              break;
      case HSTRY_WRITE:           _hstry_display_and_write(buf); break;
      }
}
//------------------------------------------------------------------------------
FILE* __fastcall TLastCallsFileThread::open_comment_file()
{
FILE* rv = NULL;
string user = get_current_user();
string s_cl = MainFormSLS->get_clients_dir();
s_cl += "\\" + user;
if(::DirectoryExists(s_cl.c_str()))
  {
  string file_name = s_cl + "\\comment";
  rv = fopen(file_name.c_str(),"wt");
  }
return rv;
}
//------------------------------------------------------------------------------
bool __fastcall TLastCallsFileThread::open_last_calls_file()
{
bool rv = false;
string user = get_current_user();
string s_cl = MainFormSLS->get_clients_dir();
s_cl += "\\" + user;
if(::DirectoryExists(s_cl.c_str()))
  {
  s_cl += "\\" + MainFormSLS->get_lst_calls_sub_dir();
  if(check_directory_existence(s_cl))
    {
    string file_name = s_cl + "\\lcs";
    LCF = fopen(file_name.c_str(),"r+b");
    if(!LCF)
      {
      LCF = fopen(file_name.c_str(),"w+b");
      rv = true; //Open empty file
      }
    }
  }
return rv;
}
//------------------------------------------------------------------------------
int __fastcall TLastCallFileStruct::get_name_id(const string& s)
{
int rv = -1;
TLC_ContactFile_List::iterator it = lc_contact_file_list.find(s);
if(it != lc_contact_file_list.end())
  rv = (*it).second;
return rv;
}
//------------------------------------------------------------------------------
int  __fastcall TLastCallFileStruct::get_free_id(const string& name)
{
int rv = -1;
if(!free_ids.empty())
  {
  rv = free_ids.front();
  free_ids.pop();
  }
else
  rv = id++;
lc_contact_file_list.insert(TLC_ContactFile_List::value_type(name,rv));
return rv;
}
//-----------------------------------------------------------------------------
unsigned  __fastcall TLastCallFileStruct::calculate_file_position(unsigned ID)
{
return ID*(1 + LAST_CALL_NAME_LENGTH + LAST_CALL_DATE_LENGTH);
}
//----------------------------------------------------------------------------
void __fastcall TLastCallsFileThread::_write(TLCSBuf* buf)
{
if(!LCF)
   open_last_calls_file();
if(LCF)
  {
  string name = string((char*)&buf->name[0]);
  int ID = LCFS.get_name_id(name);
  if(ID == -1)
     ID = LCFS.get_free_id(name);
  unsigned POS = LCFS.calculate_file_position(ID);
  UBYTE* tbuf = new UBYTE[__sz];
  if(tbuf)
    {
    tbuf[0] = 0xFF;
    memcpy(&tbuf[__pos1], buf->name, LAST_CALL_NAME_LENGTH);
    memcpy(&tbuf[__pos2], buf->date, LAST_CALL_DATE_LENGTH);
    fseek(LCF, POS, SEEK_SET);
    fwrite(tbuf, __elem_sz, __sz, LCF);
    delete [] tbuf;
    }
  }
}
//------------------------------------------------------------------------------
void __fastcall TLastCallsFileThread::_read(TLCSBuf* buf)
{
bool empty_file = false;
if(buf->new_registration)
  {
  if(LCF)
    {
    fclose(LCF);
    LCF = NULL;
    }
  }
if(!LCF)
   empty_file = open_last_calls_file();
if(LCF)
  {
  TLists* L = new TLists;
  if(L)
    {
    if(!empty_file)
      {
      UBYTE* tbuf = new UBYTE[__sz];
      if(tbuf)
        {
        unsigned i = 0;
        size_t rv = 0;
        while((rv = fread(tbuf, __elem_sz, __sz, LCF)) != EOF)
             {
             if(rv != (size_t)__sz)
                break;
             if(tbuf[0] == 0x00)
               {
               LCFS.free_ids.push(i);
               LCFS.id = ++i;
               continue;
               }
             char name_buf[LAST_CALL_NAME_LENGTH];
             memcpy(name_buf, &tbuf[__pos1], LAST_CALL_NAME_LENGTH);
             if(name_buf[LAST_CALL_NAME_LENGTH - 1] == 0)
               {
               string name = string(name_buf);
               LCFS.lc_contact_file_list.insert(TLastCallFileStruct::TLC_ContactFile_List::value_type(name,i));
               UBYTE date_buf[LAST_CALL_DATE_LENGTH];
               memcpy(date_buf, &tbuf[__pos2], LAST_CALL_DATE_LENGTH);
               TDateTime* ts = (TDateTime*)date_buf;
               TDateTime TimeStmp = *ts;
               TLastCallStr lcs(LastCallStrType_ContactInt, TimeStmp);
               lcs.name = name;
               TContact Contact(-1);
               if(MainFormSLS->Sip->Contacts.get_contact_copy_by_user_name(Contact,name))
                 lcs.full_name = Contact.full_name;
               else
                 {
                 lcs.LCST      = LastCallStrType_ContactExt;
                 lcs.full_name = lcs.name;
                 }
               L->ldl.insert(TLists::TLC_DateTime_List::value_type(lcs.dt, lcs));
               L->lcl.insert(TLists::TLC_Contact_List::value_type(lcs.name,lcs.dt));
               }
             LCFS.id = ++i;
             }    //while((rv = fread(tbuf, elem_sz, sz, f)) != EOF)
          L->arrange_date_times();
          MainFormSLS->Sip->Contacts.LCS.CHANGE_LISTS(L);
        }  // if(tbuf)
      } // if(!empty_file)
    else
      {
      MainFormSLS->Sip->Contacts.LCS.CHANGE_LISTS(L);
      }
    } //if(L)
  } //if(LCF)
}
//------------------------------------------------------------------------------
void __fastcall TLists::arrange_date_times()
{
TDateTime Last_TmStmp;
TLC_DateTime_List T_LDL;
TLC_DateTime_List::reverse_iterator r_it = ldl.rbegin();
while(r_it != ldl.rend())
     {
     TDateTime Curr_TmStmp = ceil((*r_it).second.dt);
     if(Last_TmStmp != Curr_TmStmp)
       {
       TLastCallStr lcs(LastCallStrType_DateTime, Curr_TmStmp);
       T_LDL.insert(TLists::TLC_DateTime_List::value_type(lcs.dt,lcs));
       Last_TmStmp = Curr_TmStmp;
       }
     r_it++;
     }
TLC_DateTime_List::reverse_iterator it = T_LDL.rbegin();
while(it != T_LDL.rend())
     {
     if(it == T_LDL.rbegin())
        if(ceil(Last_TmStmp.CurrentDateTime()) == (*it).first)
           today = (*it).first;
     TLastCallStr lcs = (*it).second;
     ldl.insert(TLists::TLC_DateTime_List::value_type(lcs.dt,lcs));
     it++;
     }
}
//------------------------------------------------------------------------------
void __fastcall TLists::delete_missed_name(const string& name)
{
deque<string>::iterator it = missed.begin();
while(it != missed.end())
     {
     if((*it) == name)
       {
       missed.erase(it);
       break;
       }
     it++;
     }
}
//------------------------------------------------------------------------------
void __fastcall TLists::update_missed_name(const string& name)
{
if(!find_missed_name(name))
    add_missed_name(name);
}
//------------------------------------------------------------------------------
bool __fastcall TLists::get_first_missed_name(string& s)
{
bool rv = false;
if(!missed.empty())
  {
  s  = missed.front();
  rv = true;
  }
return rv;  
}
//------------------------------------------------------------------------------
bool __fastcall TLists::find_missed_name(const string& name)
{
bool rv = false;
deque<string>::iterator it = missed.begin();
while(it != missed.end())
     {
     if((*it) == name)
       {
       rv = true;
       break;
       }
     it++;
     }
return rv;
}
//------------------------------------------------------------------------------
void __fastcall TLists::add_missed_name(const string& name)
{
missed.push_back(name);
}
//------------------------------------------------------------------------------
void __fastcall TLastCallsFileThread::_save_comment(TLCSBuf* buf)
{
if(!buf->s.empty())
  {
  FILE* f = open_comment_file();
  if(f)
    {
    fputs(buf->s.c_str(),f);
    fclose(f);
    }
  }
}
//------------------------------------------------------------------------------
void __fastcall TLastCallsFileThread::_clear_comment()
{
string user = get_current_user();
string s_cl = MainFormSLS->get_clients_dir();
s_cl += "\\" + user;
if(::DirectoryExists(s_cl.c_str()))
  {
  string file_name = s_cl + "\\comment";
  if(FileExists(file_name.c_str()))
     DeleteFile(file_name.c_str());
  }
}
//------------------------------------------------------------------------------
void __fastcall TLastCallsFileThread::_save_contact_comment(TLCSBuf* buf)
{
string user = get_current_user();
string s_cl = MainFormSLS->get_clients_dir();
s_cl += "\\" + user;
if(::DirectoryExists(s_cl.c_str()))
  {
  s_cl += "\\COMMENTS";
  if(check_directory_existence(s_cl))
    {
    s_cl += "\\" + buf->s;
    FILE* f = fopen(s_cl.c_str(),"wt");
    if(f)
      {
      fputs(buf->s_1.c_str(),f);
      fclose(f);
      }
    }
  }
}
//------------------------------------------------------------------------------
void __fastcall TLastCallsFileThread::_clear_contact_comment(TLCSBuf* buf)
{
string user = get_current_user();
string s_cl = MainFormSLS->get_clients_dir();
s_cl += "\\" + user + "\\COMMENTS";
if(::DirectoryExists(s_cl.c_str()))
  {
  s_cl += "\\" + buf->s;
  if(::FileExists(s_cl.c_str()))
     ::DeleteFile(s_cl.c_str());
  }
}
//------------------------------------------------------------------------------
void __fastcall TLastCallsFileThread::_hstry_display_and_write(TLCSBuf* buf)
{
_hstry_display(buf);
_hstry_write_to_file(buf);
_check_to_delete_str(buf);
}
//------------------------------------------------------------------------------
void __fastcall TLastCallsFileThread::_hstry_display(TLCSBuf* buf)
{
TImStr* IS = buf->IS;
if(IS)
  if(IS->rem_user_selected)
     MainFormSLS->Im.addStr(IS);
}
//------------------------------------------------------------------------------
void __fastcall TLastCallsFileThread::_hstry_write_to_file(TLCSBuf* buf)
{
TImStr* IS = buf->IS;
if(IS)
  {
  const SYSTEMTIME& systime = IS->get_systemtime();
  string s_cl = buf->s;
  if(::DirectoryExists(s_cl.c_str()))
    {
    s_cl += "\\" + get_hstry();
    if(!buf->s_1.empty())
       s_cl += "\\" + buf->s_1;   //remote_user;
    if(!buf->s_5.empty())
       __modify_mtd_file(s_cl, buf);   //Проверить вспомогательный файл __mtd, в частности с строку __fn: (full_name), т.к. remote_user не содержится в личном сптске контактов и полное имя надо брать из файла __fn:
    s_cl += "\\" + inttostr(systime.wYear);
    s_cl += "\\" + inttostr(systime.wMonth);
    s_cl += "\\" + inttostr(systime.wDay);
    if(check_directory_existence(s_cl))
      {
      //string hstry_dir = s_cl;
      s_cl += "\\m";
      FILE* f = fopen(s_cl.c_str(),"at");
      if(f)
        {
        im_text_type im_tt = IS->get_im_tt();
        string s = get_TYPE() + inttostr(im_tt) + get_lf();
        fputs(s.c_str(),f);
        switch(im_tt){
               case IM_TEXT_TYPE_LOCAL_IM:
               case IM_TEXT_TYPE_REMOTE_IM:{
                    int sz = buf->v.size();
                    s = "sz:" + inttostr(sz) + get_lf();
                    fputs(s.c_str(),f);
                    for(int i = 0; i < sz; i++)
                       {
                       s = buf->v[i] + get_lf();
                       fputs(s.c_str(),f);
                       }
                    break;
                    }

               case IM_INVITE_ON_FILE_RECEIVING:{
                    string ss;
                    vector<string> v;
                    s.clear();
                    int sz = 0;
                    if(!buf->s_2.empty())
                      {
                      ss = "id:" + buf->s_2;
                      v.push_back(ss);
                      s += ss + get_lf();
                      sz++;
                      }
                    if(!buf->s_3.empty())
                      {
                    __check_on_file_existence(buf);
                      ss = "name:" + buf->s_3;
                      v.push_back(ss);
                      s += ss + get_lf();
                      sz++;
                      }
                    if(!buf->s_4.empty())
                      {
                      ss  = "thumb:" + buf->s_4;
                      v.push_back(ss);
                      s  += ss + get_lf();
                      sz++;
                      }
                    IS->hstry_substrs(v);
                    string s_sz = "sz:" + inttostr(sz) + get_lf();
                    fputs(s_sz.c_str(),f);
                    if(!s.empty())
                       fputs(s.c_str(),f);
                    break;
                    }
               case IM_INVITE_ON_FILE_SENDING:{
                    string ss;
                    vector<string> v;
                    s.clear();
                    int sz = 0;
                    if(!buf->s_3.empty())
                      {
                      string dir, name;
                    __separate_dir_name(buf->s_3, dir, name);
                      if(!dir.empty())
                        {
                        dir = "dir:" + dir;
                        v.push_back(dir);
                        s += dir + get_lf();
                        sz++;
                        }
                      if(!name.empty())
                        {
                        name = "name:" + name;
                        v.push_back(name);
                        s += name + get_lf();
                        sz++;
                        }
                      }
                    IS->hstry_substrs(v);  
                    string s_sz = "sz:" + inttostr(sz) + get_lf();
                    fputs(s_sz.c_str(),f);
                    if(!s.empty())
                       fputs(s.c_str(),f);
                    break;
                    }
               case IM_CALL_OUT_ANSWERED:
               case IM_CALL_IN_ANSWERED:{
                    IS->write_call_duration(f);
                    break;
                    }
               }
        IS->write_tmstmp(f);
        fclose(f);
        }
      }
    }
  }
}
//------------------------------------------------------------------------------
void __fastcall TLastCallsFileThread::_check_to_delete_str(TLCSBuf* buf)
{
TImStr* IS = buf->IS;
if(IS)
  {
  if(!IS->rem_user_selected)
     delete IS;  //!!! //if(rem_user_selected), то IS вставляется в список isl ( MainFormSLS->Im.addStr(IS);)
  buf->IS = NULL; // На всякий случай
  }
}
//------------------------------------------------------------------------------
//--- checking if(!buf->s_5.empty())  -  before calling of this func  ----------
//------------------------------------------------------------------------------
void __fastcall TLastCallsFileThread::__modify_mtd_file(const string& s_cl, TLCSBuf* buf)
{
FILE* f = NULL;
if(check_directory_existence(s_cl))
  {
  string s = s_cl + "\\" + "__mtd";
  f = fopen(s.c_str(),"rt");
  if(f)
    {
    char bf[256];
    if(fgets(bf,sizeof(bf)-1,f))
      {
      fclose(f);
      f = NULL;
      string fn = string(bf);
      int len = fn.length();
      int st = fn.find("__fn:");
      if(st != -1)
        {
        st += 5;
        if(st < len)
           {
           fn = fn.substr(st);
           if(fn != buf->s_5)
             {
             f = fopen(s.c_str(),"wt");
             if(f)
               {
               string out = "__fn:" + buf->s_5;
               fputs(out.c_str(),f);
               }
             }
           }
        }
      }
    }
  else
    {
    f = fopen(s.c_str(),"wt");
    if(f)
      {
      string out = "__fn:" + buf->s_5;
      fputs(out.c_str(),f);
      }
    }
  }
if(f)
  fclose(f);
}
//------------------------------------------------------------------------------
void __fastcall TLastCallsFileThread::__read_mtd_file(TIM_Struct* im, const string& s_cl)
{
FILE* f = NULL;
if(check_directory_existence(s_cl))
  {
  string s = s_cl + "\\" + "__mtd";
  f = fopen(s.c_str(),"rt");
  if(f)
    {
    char bf[256];
    if(fgets(bf,sizeof(bf)-1,f))
      {
      string fn = string(bf);
      int len   = fn.length();
      int st    = fn.find("__fn:");
      if(st != -1)
        {
        st += 5;
        if(st < len)
           {
           fn = fn.substr(st);
           im->set_fn(fn);
           }
        }
      }
    }
  }
if(f)
  fclose(f);
}
//------------------------------------------------------------------------------
//-- In this thread functions does not work directly with IM_DrawGrid  ---------
//-- propeties(Canvas, Canvas->TextWidth etc.) ---------------------------------
//------------------------------------------------------------------------------
void __fastcall TLastCallsFileThread::_hstry_load(TLCSBuf* buf)
{
bool ins_date_str = false;
MainFormSLS->Im.clear_fn();
if(_check_preliminary_time_interval(buf))
  ins_date_str = true;
do{
  string s_cl = buf->s;
  if(::DirectoryExists(s_cl.c_str()))
    {
    s_cl += "\\" + get_hstry();
    s_cl += "\\" + buf->s_1;   //Selected user name
  __read_mtd_file(&MainFormSLS->Im, s_cl);
    string ymd = inttostr(buf->START_TIME.wYear) + "\\" + inttostr(buf->START_TIME.wMonth) + "\\" + inttostr(buf->START_TIME.wDay);

    /*
    s_cl += "\\" + inttostr(buf->START_TIME.wYear);
    s_cl += "\\" + inttostr(buf->START_TIME.wMonth);
    s_cl += "\\" + inttostr(buf->START_TIME.wDay);
     */

    s_cl += "\\" + ymd;
    if(::DirectoryExists(s_cl.c_str()))
      {
      s_cl += "\\m";
      FILE* f = fopen(s_cl.c_str(),"rt");
      if(f)
        {
        if(ins_date_str)
          MainFormSLS->Im.insert_date_string(buf->START_TIME);
        MainFormSLS->Im.read_user_history(f, buf->s_1, ymd);
        fclose(f);
        }
      }
    }
  }
while(_check_complete_time_interval(buf));
int isl_sz = MainFormSLS->Im.get_raw_count();
if(isl_sz > 20) //вверху таблицы будет нулевая строка
  ::PostMessage(MainFormSLS->Handle, CONTROL_MSG, WM_APP_MSG_WPARAM__IM_READBLOCK__ONTOP_DRAWGRID_ROW_COUNT, isl_sz);
else
  ::PostMessage(MainFormSLS->Handle, CONTROL_MSG, WM_APP_MSG_WPARAM__IM_READBLOCK__DRAWGRID_ROW_COUNT, isl_sz);
}
//------------------------------------------------------------------------------
//-- Return value = true -- continue hstry loading (open next hstry file) ------
//------------------------------------------------------------------------------
bool __fastcall TLastCallsFileThread::_check_complete_time_interval(TLCSBuf* buf)
{
bool rv = false;
if(buf->START_TIME.wYear < buf->END_TIME.wYear)
  {
  buf->START_TIME.wDay++;
  if(buf->START_TIME.wDay > 31)
    {
    buf->START_TIME.wDay = 1;
    buf->START_TIME.wMonth++;
    if(buf->START_TIME.wMonth > 12)
      {
      buf->START_TIME.wMonth = 1;
      buf->START_TIME.wYear++;
      }
    }
  if(buf->START_TIME.wYear == 0) //переполнение (контроль только из-за возможной ошибки, чтобы предупредить зацикливание)
     rv = false;
  else
     rv = true;
  }
else if(buf->START_TIME.wMonth < buf->END_TIME.wMonth)
  {
  buf->START_TIME.wDay++;
  if(buf->START_TIME.wDay > 31)
    {
    buf->START_TIME.wDay = 1;
    buf->START_TIME.wMonth++;
    }
  if(buf->START_TIME.wMonth > 12)
     rv = false;
  else
     rv = true;
  }
else if(buf->START_TIME.wDay < buf->END_TIME.wDay)
  {
  buf->START_TIME.wDay++;
  if(buf->START_TIME.wDay > 31)
     rv = false;
  else
     rv = true;
  }
return rv;
}
//------------------------------------------------------------------------------
bool __fastcall TLastCallsFileThread::_check_preliminary_time_interval(TLCSBuf* buf)
{
bool rv = false;
if(buf->START_TIME.wYear < buf->END_TIME.wYear)
   rv = true;
else if(buf->START_TIME.wMonth < buf->END_TIME.wMonth)
   rv = true;
else if(buf->START_TIME.wDay < buf->END_TIME.wDay)
   rv = true;
return rv;
}
//------------------------------------------------------------------------------
void __fastcall TLastCallsFileThread::__separate_dir_name(const string& s, string& dir, string& name)
{
int st = s.rfind("\\");
if(st != -1)
  {
  dir  = s.substr(0,st);
  st++;
  if(st < (int)s.length())
    name = s.substr(st);
  }
}
//------------------------------------------------------------------------------
void __fastcall TLastCallsFileThread::__check_on_file_existence(TLCSBuf* buf)
{
string s = MainFormSLS->get_clients_dir();
if(!get_current_user().empty())
   s += "\\" + get_current_user();

string indx_dir = s + "\\" + "INDX";

s += "\\" + MainFormSLS->FEXCH.get_default_subdir_of_received_file_storage();  //"FILES"
if(!buf->s_1.empty())  //remote_user;
   {
   s += "\\" + buf->s_1;
   indx_dir += "\\" + buf->s_1;
   }
s += "\\" +  buf->s_3;    //file name

string basic_file_name = buf->s_3;

if(FileExists(s.c_str()))  // Если файл с именем принятого файла уже существует
  {
  string name;
  string ext;
  int st = buf->s_3.rfind(".");
  if(st != -1)
    {
    name = buf->s_3.substr(0, st);
    ext  = buf->s_3.substr(st);
    }
  else //имя файла без расширения
    name = buf->s_3;

  unsigned last_index = 0;
  //string dir = hstry_dir + "\\" + "RCVD_FILES";
  if(check_directory_existence(indx_dir))
    {
    string indx_file_name = indx_dir + "\\" + basic_file_name + ".idx";
    if(FileExists(indx_file_name.c_str()))
      {
      FILE* F  = fopen(indx_file_name.c_str(),"rt");
      if(F){
        char str_buf[256];
        if(fgets( str_buf, sizeof(str_buf), F))
          {
          string indx = string(str_buf);
          if(!indx.empty())
            {
            int st = indx.find("indx:");
            if(st != -1)
              {
              st += 5;
              if(st < (int)indx.length())
                {
                last_index = strtoint(indx.substr(st));
                buf->s_3 = name + "(" + uint_to_str(++last_index) + ")" + ext;
                fclose(F);
                F  = fopen(indx_file_name.c_str(),"wt");
                if(F){
                  string indx = "indx:" + uint_to_str(last_index);
                  fputs(indx.c_str(), F);
                  fclose(F);
                  F = NULL;
                  }
                }
              }
            }
          }
        if(F)
           fclose(F);
        }
      }
    else
      {
      buf->s_3 = name + "(" + uint_to_str(++last_index) + ")" + ext;
      FILE* F  = fopen(indx_file_name.c_str(),"wt");
      if(F){
        string indx = "indx:" + uint_to_str(last_index);
        fputs(indx.c_str(), F);
        fclose(F);
        }
      }
    }
  } //if(FileExists(s.c_str()))
}
//------------------------------------------------------------------------------
