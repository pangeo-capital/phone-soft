#include <vcl.h>
#pragma hdrstop

#include "WinRDefs.h"
#include "WebUnit.h"
#include "SipClient_Unit.h"
#include "SosockThread.h"
#include "src\win_utils.h"

using namespace std;

const SND_SZ         = 1500; //Send Buffer size
const char ws_char   = ' ';
const string s_start = "<file";
const string s_end   = "/>";

string getFileExt(const string& fn) {
  int idx = fn.rfind('.');

  if(idx != std::string::npos)
  {
    return  fn.substr(idx);
  }
  return ".";
}


//------------------------------------------------------------------------------
void tls_connect_file_transfer_handler(void* ref) {
try{
//tls_disconnect_count = 0;
if(MainFormSLS->ofs->elt)
  {
  TDateTime DateTime = DateTime.CurrentDateTime();
  string time_str;
  exsDateTime(DateTime,time_str);
  string s = "\n" + time_str + WS + "TLS connection" + WS + inttostr((int)ref) + WS + "established";
  if(MainFormSLS->Sip->sr_tls_t)
    s += WS + "to" + WS + MainFormSLS->Sip->sr_tls_t->host + ":" + inttostr(MainFormSLS->Sip->sr_tls_t->port);
  MainFormSLS->ofs->elt->FputEvt(s,1);
  }
/*if(MainFormSLS->FEXCH.WebReq)
  {
  MainFormSLS->FEXCH.WebReq->set_connected(true);
  MainFormSLS->FEXCH.WebReq->set_wait_connect(false);
  if (MainFormSLS->FEXCH.WebReq->sr_tls_ft_t)
    MainFormSLS->FEXCH.WebReq->sr_tls_ft_t->r = ref;
  if (MainFormSLS->FEXCH.WebReq->ss_tls_ft_t)
    MainFormSLS->FEXCH.WebReq->ss_tls_ft_t->r = ref;
  }  */

//MainFormSLS->Sip->collectLocalHostInterfaces(&MainFormSLS->iniData);
//MainFormSLS->Stun.StunClientProc(&MainFormSLS->iniData,MainFormSLS->Sip,MainFormSLS->ofs->elt);
//if(MainFormSLS->Sip->sr_tls_t)
// if(MainFormSLS->Sip->ss_tls_t)

 //if(MainFormSLS->FEXCH.WebReq->ss_tls_ft_t)
//   {
//   MainFormSLS->Sip->ss_tls_t->r = MainFormSLS->Sip->sr_tls_t->r;
//   if(MainFormSLS->Sip->ss_tls_t->Suspended)
//      MainFormSLS->Sip->ss_tls_t->Resume_Thread();
//   }

/*
if(MainFormSLS->Sip->TLS_Dropped)
  {
  MainFormSLS->Sip->TLS_Dropped = false;
  MainFormSLS->Sip->initRegistrationProc();
  }
*/
}//try
catch(Exception& e){exsSstEXCEPTION(MainFormSLS->ofs->elt,"__tls_connect_file_transfer_handler",e);}
}
//-----------------------------------------------------------------------------
void tls_disconnect_file_transfer_handler(void* ref)
{
try{
//tls_disconnect_count++;
if(!MainFormSLS->Sip->TLS_Dropped)
  {
  if(MainFormSLS->lng == Lang_RU)
     MainFormSLS->Caption = "Потеряно соединение с сервером!";
  else
     MainFormSLS->Caption = "Connection Lost!";
  }
//MainFormSLS->Sip->TLS_Dropped = true;

/*
if(tls_disconnect_count < 3)    //Ограничение размера лог файла
 if(MainFormSLS->ofs->elt)
   {
   TDateTime DateTime = DateTime.CurrentDateTime();
   string time_str;
   exsDateTime(DateTime,time_str);
   string s = "\n" + time_str + WS + "TLS link" + WS + inttostr((int)ref) + WS + "disconnected. Try reconnect";
   if(MainFormSLS->Sip->sr_tls_t)
      s += WS + "to" + WS + MainFormSLS->Sip->sr_tls_t->host + ":" + inttostr(MainFormSLS->Sip->sr_tls_t->port);
   MainFormSLS->ofs->elt->FputEvt(s,1);
   }
  //Возможно необходимо добавить CRITICAL_SECTION как и в TCP connection
*/
/*
::Sleep(1000);
if(MainFormSLS->Sip->sr_tls_t)
  if(MainFormSLS->Sip->sr_tls_t->r==ref)
     MainFormSLS->Sip->sr_tls_t->r = so_start_client_tcp_ssl((char*)MainFormSLS->Sip->sr_tls_t->host.c_str(),MainFormSLS->Sip->sr_tls_t->port);
*/

}//try
catch(Exception& e){exsSstEXCEPTION(MainFormSLS->ofs->elt,"__tls_disconnect_file_transfer_handler",e);}
}
//-----------------------------------------------------------------------------
static int pktn;
void tls_read_file_transfer_handler(const char* rcvbuf, size_t bread, void* ref)
{
try{
if(bread)
  {
  TDataWebBlock* dwb = new TDataWebBlock(WEB_REQ_MAX_PACKET);
//  TOutPutUdpBlock* opb = new TOutPutUdpBlock(pktn);

  if(dwb)
    {
    if(MainFormSLS->FEXCH.WebReq)
      {
       if(MainFormSLS->FEXCH.WebReq->get_delete_req())
         {
         delete dwb;
         return;
         }
     dwb->v.resize(bread);
     memcpy(&dwb->v[0], rcvbuf, bread);
     dwb->bread = bread;
     dwb->dt = dwb->dt.CurrentDateTime();

    /*
    if((MainFormSLS->Sip->spt)&&(MainFormSLS->Sip->sr_tls_t))
      {
      opb->FromIP   = MainFormSLS->Sip->sr_tls_t->host;
      opb->FromPort = MainFormSLS->Sip->sr_tls_t->port;
      bool a = false;
      MainFormSLS->Sip->spt->setQueue(opb);
      MainFormSLS->Sip->sr_tls_t->updateSentQueue(opb, a);
      }
    else
      delete opb;
      */


      MainFormSLS->FEXCH.WebReq->PUSH_RCVD_BLOCK(dwb);
      }
    }
  }
}//try
catch(Exception& e){exsSstEXCEPTION(MainFormSLS->ofs->elt,"__tls_read_file_transfer_handler",e);}
}
//-----------------------------------------------------------------------------

__fastcall TWebReq::~TWebReq()
{
__delete_req = true;
CLOSE_SOCKET();
if(wit)
  {
  TWebPlannerTcpThread* TT = wit;
  wit = NULL;
  TT->Terminate();
  TT->Resume_Thread();
  TT->WaitFor();
  delete TT;
  }
if(wrt)
  {
  TWebRecvTcpThread* TT = wrt;
  wrt = NULL;
  TT->Terminate();
  TT->Resume_Thread();
  TT->WaitFor();
  delete TT;
  }
if(wpt)
  {
  TWebParsThread*    TT = wpt;
  wpt = NULL;
  TT->Terminate();
  TT->Resume_Thread();
  TT->WaitFor();
  delete TT;
  }
if(wst)
  {
  TWebSendTcpThread* TT = wst;
  wst = NULL;
  TT->Terminate();
  TT->Resume_Thread();
  TT->WaitFor();
  delete TT;
  }

if(sr_tls_ft_t)
  {
  TSipRecvTls_FileTransfer_Thread* TT = sr_tls_ft_t;
  sr_tls_ft_t = NULL;
  TT->Terminate();
  //so_stop();   //Do not delete SR_TCP_T -- SUSPENDED
  TT->Resume_Thread();
  TT->WaitFor();
  void* r =  TT->get_r();
  so_destr_client_tcp(r);
  delete TT;
  }
if(ss_tls_ft_t)
  {
  TSipSendTls_FileTransfer_Thread* TT = ss_tls_ft_t;
  ss_tls_ft_t = NULL;
  TT->Terminate();
  TT->Resume_Thread();
  TT->WaitFor();
  delete TT;
  }
CLEAR_RCVD_QUEUE();
CLEAR_SEND_QUEUE();
::DeleteCriticalSection(&__q_rcvd_cs);
::DeleteCriticalSection(&__q_send_cs);
}
//------------------------------------------------------------------------------
void __fastcall TWebReq::INIT()
{
wit = new TWebPlannerTcpThread(true, &MainFormSLS->ofs->elt, this);
if(wit)
   wit->Resume();
}
//------------------------------------------------------------------------------
void    __fastcall TWebReq::CLOSE_SOCKET()
{
::closesocket(__sck);
__sck = INVALID_SOCKET;
}
//------------------------------------------------------------------------------
string  __fastcall  TWebReq::get_first_dest_ip_addr()
{
string rv;
if(!__q.empty())
   rv = __q.front().IPAddr;  // !!! Do not make __q.pop()
return rv;
}
//---------------------------------------------------------------------------
void __fastcall TWebReq::PUSH_RCVD_BLOCK(TDataWebBlock* a)
{
::EnterCriticalSection(&__q_rcvd_cs);
__q_rcvd.push(a);
::LeaveCriticalSection(&__q_rcvd_cs);
}
//---------------------------------------------------------------------------
TDataWebBlock* __fastcall TWebReq::GET_RCVD_BLOCK()
{
TDataWebBlock* rv = NULL;
::EnterCriticalSection(&__q_rcvd_cs);
  if(!__q_rcvd.empty())
    {
    rv = __q_rcvd.front();
  __q_rcvd.pop();
    }
::LeaveCriticalSection(&__q_rcvd_cs);
return rv;
}
//------------------------------------------------------------------------------
void __fastcall TWebReq::CLEAR_RCVD_QUEUE()
{
::EnterCriticalSection(&__q_rcvd_cs);
  while(!__q_rcvd.empty())
       {
       TDataWebBlock* dwb = __q_rcvd.front();
     __q_rcvd.pop();
       delete dwb;
       }
::LeaveCriticalSection(&__q_rcvd_cs);
}
//------------------------------------------------------------------------------
void __fastcall TWebReq::PUSH_SEND_BLOCK(TDataWebBlock* a)
{
::EnterCriticalSection(&__q_send_cs);
__q_send.push(a);
::LeaveCriticalSection(&__q_send_cs);
}
//-----------------------------------------------------------------------------
TDataWebBlock* __fastcall TWebReq::GET_SEND_BLOCK()
{
TDataWebBlock* rv = NULL;
::EnterCriticalSection(&__q_send_cs);
  if(!__q_send.empty())
    {
    rv = __q_send.front();
  __q_send.pop();
    }
::LeaveCriticalSection(&__q_send_cs);
return rv;
}
//------------------------------------------------------------------------------
int  __fastcall TWebReq::SIZE_OF_SEND_QUEUE()
{
int rv;
::EnterCriticalSection(&__q_send_cs);
  rv = __q_send.size();
::LeaveCriticalSection(&__q_send_cs);
return rv;
}
//-----------------------------------------------------------------------------
void __fastcall TWebReq::CLEAR_SEND_QUEUE()
{
::EnterCriticalSection(&__q_send_cs);
  while(!__q_send.empty())
       {
       TDataWebBlock* dwb  = __q_send.front();
     __q_send.pop();
       delete dwb;
       }
::LeaveCriticalSection(&__q_send_cs);
}
//-----------------------------------------------------------------------------
void __fastcall TWebBaseThread::sendlasterr()
{
TEventLogThread* elt = getLog();
if(elt)
   elt->FputEvt(__lasterr,1);
}
//---------------------------------------------------------------------------
TEventLogThread* __fastcall TWebBaseThread::getLog()
{
TEventLogThread* elt = *__eltp;
if(elt)
 if(elt->getlog())
    return elt;
return NULL;
}
//---------------------------------------------------------------------------
void __fastcall TWebBaseThread::Suspend_Thread()
{
::EnterCriticalSection(&__cs);
__suspend_count++;
::LeaveCriticalSection(&__cs);
Suspend();
}
//-----------------------------------------------------------------------------
void __fastcall TWebBaseThread::Resume_Thread()
{
::EnterCriticalSection(&__cs);
  if(__suspend_count < 1)   //Important for critical Resume in the Timer1Timer()
    {
  __suspend_count = 0;
    Resume();
    }
  else
    {
    while(__suspend_count)
         {
       __suspend_count--;
         Resume();
         }
    }
::LeaveCriticalSection(&__cs);
}
//-----------------------------------------------------------------------------
void __fastcall TWebPlannerTcpThread::__get_dest_ip_addr_by_dns_host()
{
hostent* sh = gethostbyname(__WR->get_dns_host().c_str());
if(sh)
  {
  int   i = 0;
  while(sh->h_addr_list[i])
       {
       struct   sockaddr_in   adr;
       memcpy(&adr.sin_addr,sh->h_addr_list[i],sh->h_length);
       string s_ipaddr = string(inet_ntoa(adr.sin_addr));
       TIPAddress ipaddr;
       ipaddr.IPAddr  = s_ipaddr;
       ipaddr.uIPAddr = exsConvStrIpAddrToUnsigned(s_ipaddr);
     __WR->dest_ip_push(ipaddr);
       i++;
       }
  }
}
//------------------------------------------------------------------------------
void __fastcall TWebPlannerTcpThread::select_dns_host(const string& s, string& dns_host, unsigned& port)
{
int st = s.rfind(":");
if(st != -1)
  {
  dns_host = s.substr(0,st);
  int len  = s.length();
  st++;
  if(st < len)
    {
    string s_port = s.substr(st);
    port          = strtoint(s_port);
    }
  else
    {
    if(!__WR->get_transport())
      port = 80;        //default http port
    else
      port = 443;       //default https port
    }
  }
else
  {
  dns_host = s;
  if(!__WR->get_transport())
     port = 80;        //default http port
  else
     port = 443;       //default https port
  }
}
//------------------------------------------------------------------------------
string __fastcall TWebPlannerTcpThread::__get_content_type(const string& file_name)
{
int st = file_name.rfind(".png");
if(st != -1)
  return "image/png";
st = file_name.rfind(".jpg");
if(st != -1)
  return "image/jpeg";
st = file_name.rfind(".jpeg");
if(st != -1)
  return "image/jpeg";
st = file_name.rfind(".bmp");
if(st != -1)
  return "image/bmp";
st = file_name.rfind(".ico");
if(st != -1)
  return "image/ico";
st = file_name.rfind(".mp4");
if(st != -1)
   return "video/mp4";
return "application/octet-stream";
}
//------------------------------------------------------------------------------
void __fastcall TFileExch::fexch_ins(TExchFileMsg& ef)
{
::EnterCriticalSection(&fexch_cs);
  q.push(ef);
::LeaveCriticalSection(&fexch_cs);
}
//------------------------------------------------------------------------------
bool __fastcall TFileExch::fexch_empty()
{
bool rv = false;
::EnterCriticalSection(&fexch_cs);
  rv = q.empty();
::LeaveCriticalSection(&fexch_cs);
return rv;
}
//------------------------------------------------------------------------------
bool __fastcall TFileExch::fexch_get(TExchFileMsg& ef)
{
bool rv = false;
::EnterCriticalSection(&fexch_cs);
  if(!q.empty())
    {
    ef = q.front();
    q.pop();
    rv = true;
    }
::LeaveCriticalSection(&fexch_cs);
return rv;
}
//------------------------------------------------------------------------------
void __fastcall TFileExch::check_file_exch_activity()
{
if(!fexch_empty())
  {
  if(!WebReq)
     WebReq = new TWebReq(1, this); // 0 - TCP web request, 1 - TLS web req
  }
//else
  {
  if(WebReq)
    if(WebReq->request_list_empty()) //т.е. старые заявки выполнеы (state == 3) и новых нет (fexch_empty())
      {
      TWebReq* WEB_REQ = WebReq;
      WebReq           = NULL;
      delete WEB_REQ;
      }
  }
}
//-----------------------------------------------------------------------------
int __fastcall TWebParsThread::__GET_HTTP_RESPONCE(const string& http_header)
{
int rv = 0;
int st = http_header.find("HTTP");
if(st != -1)
  {
  rv = 1; //Принят HTTP responce
  st += 4;
  int en = http_header.find(crlf);
  if(en != -1)
    {
     if(st < en)
       {
       st = http_header.find("200", st);
       if(st != -1)
        if(st < en)
           rv = 2;      //Принят HTTP 200 Responcre 
       }
    }
  }
return rv;
}
//------------------------------------------------------------------------------
bool __fastcall TWebParsThread::__get_http_content_length(const string& s, int* content_length)
{
bool rv = false;
int len = s.length();
int st  = s.find("Content-Length:");
if(st != -1)
  {
  st += 15;
  while(st < len)
       {
       if(s[st] != ws_char)
          break;
       st++;
       }
  if(st < len)
    {
    int en = s.find(crlf, st);
    if(en != -1)
      {
     *content_length = strtoint(s.substr(st, en - st));
      rv = true;
      }
    }
  }
return rv;
}
//---------------------------------------------------------------------------------------
void __fastcall TWebParsThread::assign_hstry_subdir(const string& year_month_day)
{
::EnterCriticalSection(&sd_cs);
__year_month_day_hstry_subdir = year_month_day;
::LeaveCriticalSection(&sd_cs);
}
//---------------------------------------------------------------------------------------
void __fastcall TWebParsThread::assign_FILE(FILE* F)
{
::EnterCriticalSection(&sd_cs);
  __F = F;
::LeaveCriticalSection(&sd_cs);
}
//------------------------------------------------------------------------------
void __fastcall TWebParsThread::__WRITE_FILE(TDataWebBlock* ib, int st, int sz)
{
::EnterCriticalSection(&sd_cs);
  if(__F)
     fwrite(&ib->v[st], sz, 1, __F);
::LeaveCriticalSection(&sd_cs);
}
//------------------------------------------------------------------------------
void __fastcall TWebParsThread::__CLOSE_FILE()
{
::EnterCriticalSection(&sd_cs);
  if(__F){
    fclose(__F);
  __F = NULL;
    }
::LeaveCriticalSection(&sd_cs);
}
//------------------------------------------------------------------------------
void   __fastcall TWebParsThread::assign_display_and_htry_index(int a)
{
__display_index = a;
}
//------------------------------------------------------------------------------
void   __fastcall TWebParsThread::assign_file_id(const string& file_id)
{
::EnterCriticalSection(&sd_cs);
  __file_id = file_id;
::LeaveCriticalSection(&sd_cs);
}
//-----------------------------------------------------------------------------
void __fastcall TWebParsThread::assign_file_storage(const string& dir, const string& file)
{
::EnterCriticalSection(&sd_cs);
__storage_dir  = dir;
__storage_file = file;
::LeaveCriticalSection(&sd_cs);
}
//---------------------------------------------------------------------------------------
string __fastcall TWebParsThread::__get_file_storage()
{
string rv;
::EnterCriticalSection(&sd_cs);
  rv = __storage_dir;
::LeaveCriticalSection(&sd_cs);
return rv;
}
//-----------------------------------------------------------------------------
string __fastcall TWebParsThread::__get_rcvd_file_name()
{
string rv;
::EnterCriticalSection(&sd_cs);
  rv = __storage_file;
::LeaveCriticalSection(&sd_cs);
return rv;
}
//------------------------------------------------------------------------------
string   __fastcall TWebParsThread::__get_file_id()
{
string rv;
::EnterCriticalSection(&sd_cs);
  rv = __file_id;
::LeaveCriticalSection(&sd_cs);
return rv;
}
//-----------------------------------------------------------------------------
void   __fastcall TWebParsThread::__clear_address_of_file_storage()
{
::EnterCriticalSection(&sd_cs);
  __storage_dir.clear();
  __storage_file.clear();
::LeaveCriticalSection(&sd_cs);
}
//-----------------------------------------------------------------------------
void   __fastcall TWebParsThread::__clear_file_id()
{
::EnterCriticalSection(&sd_cs);
  __file_id.clear();
::LeaveCriticalSection(&sd_cs);
}
//------------------------------------------------------------------------------
void  __fastcall TWebParsThread::__clear_year_month_day_hstry_subdir()
{
::EnterCriticalSection(&sd_cs);
__year_month_day_hstry_subdir.clear();
::LeaveCriticalSection(&sd_cs);
}
//-----------------------------------------------------------------------------
void  __fastcall TWebParsThread::assign_dest_list(const queue<string>& dst_lst)
{
::EnterCriticalSection(&sd_cs);
  __dest_list = dst_lst;
::LeaveCriticalSection(&sd_cs);
}
//-----------------------------------------------------------------------------
void __fastcall TWebParsThread::__clear_dest_list()
{
::EnterCriticalSection(&sd_cs);
  while(!__dest_list.empty())
         __dest_list.pop();
::LeaveCriticalSection(&sd_cs);
}
//-----------------------------------------------------------------------------
bool __fastcall TWebParsThread::get_dest(string& dest_contact)
{
bool rv = false;
::EnterCriticalSection(&sd_cs);
  if(!__dest_list.empty())
    {
    dest_contact = __dest_list.front();
  __dest_list.pop();
    rv = true;
    }
::LeaveCriticalSection(&sd_cs);
return rv;
}
//-----------------------------------------------------------------------------
void   __fastcall TWebParsThread::assign_thumb(const string& s)
{
::EnterCriticalSection(&sd_cs);
  __thumb = s;
::LeaveCriticalSection(&sd_cs);
}
//-----------------------------------------------------------------------------
string __fastcall TWebParsThread::get_thumb()
{
string rv;
::EnterCriticalSection(&sd_cs);
  rv = __thumb;
::LeaveCriticalSection(&sd_cs);
return rv;
}
//-----------------------------------------------------------------------------
void   __fastcall TWebParsThread::assign_sending_file_name(const string& s)
{
::EnterCriticalSection(&sd_cs);
  __sending_file_name = s;
::LeaveCriticalSection(&sd_cs);
}
//-----------------------------------------------------------------------------
string __fastcall TWebParsThread::get_sending_file_name()
{
string rv;
::EnterCriticalSection(&sd_cs);
  rv = __sending_file_name;
::LeaveCriticalSection(&sd_cs);
return rv;
}
//-----------------------------------------------------------------------------
void __fastcall TWebRecvTcpThread::CheckConnError()
{
int err = WSAGetLastError();
__WR->CLOSE_SOCKET();
__lasterr.clear();
switch(__conn_count){
      case 0:
      case 1:
          __lasterr = "FILE_TRANSFER ";
            GetLastSocketError(__lasterr,err);
            sendlasterr();
          __NextConnectTime = __NextConnectTime.CurrentDateTime() + TDateTime(0,0,5,0);
            break;
      case 2:
          __lasterr = "FILE_TRANSFER ";
            GetLastSocketError(__lasterr,err);
          __lasterr += ".....";
            sendlasterr();
          __NextConnectTime = __NextConnectTime.CurrentDateTime() + TDateTime(0,0,5,0);
            break;
      default:
          __NextConnectTime = __NextConnectTime.CurrentDateTime() + TDateTime(0,0,30,0);
            break;
      }
__conn_count++;
}
//------------------------------------------------------------------------------
void __fastcall TWebRecvTcpThread::LOG_Connection(const string& host, unsigned port)
{
TEventLogThread* elt = getLog();
if(elt)
  {
  TDateTime dt = dt.CurrentDateTime();
  string s;
  exsDateTime(dt,s);
  s = "\n" + s + " Connected to File_Exchange_Server " + host + ":" + inttostr(port) + "\n";
  elt->FputEvt(s);
  }
}
//---------------------------------------------------------------------------
void __fastcall TWebParsThread::Execute()
{
try{
while(!Terminated){
     TDataWebBlock* ib = __WR->GET_RCVD_BLOCK();
     if(!ib)
       {
     ::Sleep(1);
       continue;
       }
     if(!__WR->file_transfer_in_progress())
       {
       delete ib;
       continue;
       }
     if(__WR->get_req_type() == 0) //req type - receive file
       {
       if(!__first_packet_rcvd)
         {
       __first_packet_rcvd = true;
         ib->v.push_back(0);
         string h;
         string s = string((char*)&ib->v[0]);
         int st = s.find(sdpboundary);
         if(st != -1)
           {
           h = s.substr(0,st);
           if(!h.empty())
             {
             int resp = __GET_HTTP_RESPONCE(h);
             switch(resp){
                    case 0:{ //received not HTTP msg
                         __total_content_length = __current_content_length;
                           break;
                           }
                    case 1:{//received not 200 OK responce - Close file
                         __total_content_length = __current_content_length;
                         __lasterr = "\nError: Receive file \"" + __get_rcvd_file_name() + "\"\n";
                           int st = h.find(crlf);
                           if(st != -1)
                           __lasterr += h.substr(0, st) + "\n";
                           sendlasterr();
                           break;
                           }
                    case 2:{ //received 200 OK
                           int total_content_length;
                           if(__get_http_content_length(h, &total_content_length))
                             {
                             if(total_content_length)
                               {
                             __total_content_length = total_content_length;
                               st += 4;
                               if(st < ib->bread)
                                 {
                                 int sz = ib->bread - st;
                               __WRITE_FILE(ib, st, sz);
                               __current_content_length = sz;
                                 }
                               }
                             }
                           break;
                           }
                    } //switch
             }    //if(!h.empty())
           }   //if(st != -1)
         }   //if(!__first_packet_rcvd)
       else
         {
       __WRITE_FILE(ib, 0, ib->bread);
       __current_content_length += ib->bread;
         }
       delete ib;
       if(__total_content_length <= __current_content_length)
         {
       __first_packet_rcvd      = false;
       __current_content_length = 0;
       __clear_address_of_file_storage();
       __clear_year_month_day_hstry_subdir();
       __CLOSE_FILE();
       __FILE_RECEIVED();
       __clear_file_id();            //!!!After file rcvd
       __total_content_length   = 0; //!!!After file rcvd
       __WR->set_idle_state_of_file_transfer(); //idle, file receiving complete, we can get next file transfer request
         }
       }  // if(__WR->get_req_type() == 0) //req type - receive file
     else if(__WR->get_req_type() == 1)    //req type - send file
       {
       ib->v.push_back(0);
       string s = string((char*)&ib->v[0]);
       bool proc_req = true;
       if(RCS.get_received_200_OK())
         if(RCS.transfer_encoding_chuncked)
           if(!RCS.get_received_end_chunk())
             {
             RCS.chunks += s;
             s = RCS.chunks;
             RCS.chunks.clear();
             RCS.get_received_chunks( s, 0, s.length());
             proc_req    = false;
             TChunk chunk;
             while(RCS.get_chunk_from_received_list(chunk))
                  {
                  if(!chunk.s.empty())
                  __proc_received_chunks(s_start, s_end, chunk.s);
                  }
             }
       if(proc_req){
       int resp = __GET_HTTP_RESPONCE(s);
       switch(resp){
              case 0: //received not HTTP msg
                     break;
              case 1: //received not 200 OK responce - Close file
                     break;
              case 2: //received 200 OK
                   __proc_200_ok_resp_on_send_file(s);
                     break;
              }
           } //if(proc_req)

       delete ib;
       if(RCS.get_received_end_chunk())
         {
       __display_index = -1;
       __clear_dest_list();
       __WR->set_idle_state_of_file_transfer(); //idle, file receiving complete, we can get next file transfer request
         }
       }  //else if(__WR->get_req_type() == 1) //req type - send file
     }   //while(!Terminated)

__display_index = -1;
__clear_address_of_file_storage();
__clear_year_month_day_hstry_subdir();
__clear_file_id();;
__total_content_length   = 0;
__current_content_length = 0;
__clear_dest_list();
__CLOSE_FILE();
__WR->CLEAR_RCVD_QUEUE();
}//try
catch(Exception& e){exsSstEXCEPTION(getLog(),"__TWebParsThread::Execute()",e);}
}
//-----------------------------------------------------------------------------
void __fastcall TWebRecvTcpThread::Execute()
{
try{
while(!Terminated){
     if(__WR->get_delete_req())
       {
     ::Sleep(1);
       continue; //Wait for thread termination
       }
     Connect();
     Receive();
     }
}//try
catch(Exception& e){exsSstEXCEPTION(getLog(),"__TWebRecvTcpThread::Execute()",e);}
}
//------------------------------------------------------------------------------
void __fastcall TWebRecvTcpThread::Connect()
{
try{
  __WR->set_connected(false);
string   host = __WR->get_host();
unsigned port = __WR->get_port();
struct sockaddr_in dest;
memset(&dest,0,sizeof(dest));
dest.sin_family      = AF_INET;
dest.sin_addr.s_addr = inet_addr(host.c_str());
dest.sin_port        = htons(port);
while(!Terminated)
     {
    if(__WR->get_delete_req())
       {
     ::Sleep(1);
       continue; //Wait for thread termination
       }
     if(__NextConnectTime.CurrentDateTime() < __NextConnectTime)
       {
     ::Sleep(100);
       continue;
       }
     if(connect(__WR->getsck(),(struct sockaddr *)&dest, sizeof(dest)) == SOCKET_ERROR)
       {
       CheckConnError();
     __WR->set_socket(exsCreateTCPSocket_ADDR_ANY());  //::closesocket(sck) inside CheckConnError()
       continue;
       }
   __conn_count = 0;
   __WR->set_connected(true);
     LOG_Connection(host, port);
     break;
     }
}//try
catch(Exception& e){exsSstEXCEPTION(getLog(),"__TWebRecvTcpThread::Connect()",e);}
   __WR->set_wait_connect(false);
}
//----------------------------------------------------------------------------
void __fastcall TWebRecvTcpThread::Receive()
{
try{
while(!Terminated){
     TDataWebBlock* dwb = new TDataWebBlock(WEB_REQ_MAX_PACKET);
     dwb->bread = recv(__WR->getsck(), &dwb->v[0], WEB_REQ_MAX_PACKET, 0);
     if(__WR->get_delete_req())
       {
       delete dwb;
     ::Sleep(1);
       continue; //Wait for thread termination
       }
     if(dwb->bread == SOCKET_ERROR)
       {
       if(!Terminated)
         {
         int err = WSAGetLastError();
       __WR->CLOSE_SOCKET();
       __lasterr.clear();
       __lasterr = "TWebRecvTcpThread::Receive() ";
         GetLastSocketError(__lasterr,err);
         sendlasterr();
         }
       delete dwb;
       break;
       }
     dwb->dt = dwb->dt.CurrentDateTime();
   __WR->PUSH_RCVD_BLOCK(dwb);
     }
}//try
catch(Exception& e){exsSstEXCEPTION(getLog(),"__TWebRecvTcpThread::Receive()",e);}
}
//----------------------------------------------------------------------------
void __fastcall TWebSendTcpThread::Execute()
{
try{
while(!Terminated){
     TDataWebBlock* dwb = __WR->GET_SEND_BLOCK();
     if(!dwb)
       {
       Suspend_Thread();
       continue;
       }
     if(__WR->get_delete_req())
       {
       delete dwb;
     ::Sleep(1);
       continue; //Wait for thread termination
       }
   __sendbuf(dwb);
     delete dwb;
     }
__WR->CLEAR_SEND_QUEUE();
}//try
catch(Exception& e){exsSstEXCEPTION(getLog(),"__TWebSendTcpThread::Execute",e);}
}
//----------------------------------------------------------------------------
void __fastcall TSipSendTls_FileTransfer_Thread::Execute()
{
try{
while(!Terminated){
     TDataWebBlock* dwb = __WR->GET_SEND_BLOCK();
     if(!dwb)
       {
       Suspend_Thread();
       continue;
       }
     if(__WR->get_delete_req())
       {
       delete dwb;
     ::Sleep(1);
       continue; //Wait for thread termination
       }
   __sendbuf(dwb);
     delete dwb;
     }
__WR->CLEAR_SEND_QUEUE();
}//try
catch(Exception& e){exsSstEXCEPTION(getLog(),"__TSipSendTls_FileTransfer_Thread::Execute",e);}

}
//----------------------------------------------------------------------------
void __fastcall TWebSendTcpThread::__sendbuf(TDataWebBlock* dwb)
{
SOCKET SCK = __WR->getsck();
if(SCK != INVALID_SOCKET)
  {
  int len = dwb->v.size();
  if(len)
    while(send(SCK, &dwb->v[0], len, 0) == SOCKET_ERROR)
         {
         int err = WSAGetLastError();
       __lasterr.clear();
       __lasterr = "WebSendTcpThread::__sendbuf() ";
         GetLastSocketError(__lasterr,err);
         sendlasterr();
         }
  }
}
//-----------------------------------------------------------------------------
void __fastcall TSipSendTls_FileTransfer_Thread::__sendbuf(TDataWebBlock* dwb)
{

int len = dwb->v.size();
if(len)
  {
//  #ifdef SIP_LogSendPacket
//  TDateTime DateTime = DateTime.CurrentDateTime();
//  #endif

  //so_write_some(r,&dwb->v[0],len);
  if (r)
    ((Sosock_Client*)r)->write(&dwb->v[0],len);

//  #ifdef SIP_LogSendPacket
//  LOG_SendPacket(DateTime,ospb,len);
//  #endif

 
  }

}
//----------------------------------------------------------------------------
string __fastcall TExchFileMsg::get_substring_by_pattern(const string& s)
{
string rv;
if(!v.empty())
  {
  vector<string>::iterator it = v.begin();
  while(it != v.end())
       {
       int st = (*it).find(s);
       if(st != -1)
         {
         int ln = s.length();
         st += ln;
         if(st < (int)(*it).length())
           {
           rv = (*it).substr(st);
           break;
           }
         }
       it++;
       }
  }
return rv;
}
//------------------------------------------------------------------------------
void __fastcall TExchFileMsg::parsing_notfy_msg(TExchNotifyMsg& enm)
{
int len = s.length();
__get_file_id(enm,len);
__get_file_name(enm,len);
__get_thumb_id(enm,len);
}
//-----------------------------------------------------------------------------
void __fastcall TExchFileMsg::__get_file_id(TExchNotifyMsg& enm, int len)
{
int st = s.find("id='");
if(st != -1)
  {
  st += 4;
  if(st < len)
    {
    int en = s.find("'", st);
    if(en != -1)
       enm.file_id = s.substr(st, en - st);
    }
  }
}
//-----------------------------------------------------------------------------
void __fastcall TExchFileMsg::__get_file_name(TExchNotifyMsg& enm, int len)
{
int st = s.find("name='");
if(st != -1)
  {
  st += 6;
  if(st < len)
    {
    int en = s.find("'", st);
    if(en != -1)
       enm.file_name = s.substr(st, en - st);
    }
  }
}
//-----------------------------------------------------------------------------
void __fastcall TExchFileMsg::__get_thumb_id(TExchNotifyMsg& enm, int len)
{
int st = s.find("thumb='");
if(st != -1)
  {
  st += 7;
  if(st < len)
    {
    int en = s.find("'", st);
    if(en != -1)
       enm.thumb_id = s.substr(st, en - st);
    }
  }
}
//-----------------------------------------------------------------------------
string __fastcall TWebPlannerTcpThread::__get_default_file_storage(const string& file_sender)
{
string s = MainFormSLS->get_clients_dir();
if(!get_current_user().empty())
   s += "\\" + get_current_user();
s += "\\" + __WR->get_fexch()->get_default_subdir_of_received_file_storage();
if(!file_sender.empty())
   s += "\\" + file_sender;
return s;
}
//-----------------------------------------------------------------------------
void __fastcall TWebPlannerTcpThread::Execute()
{
if(!__WR->get_transport())
  __resource = __WR->get_tcp_resource();
else
  __resource = __WR->get_tls_resource();
if(!__resource.empty())
  {
    string   dns_host;
    unsigned port;
    select_dns_host(__resource, dns_host, port);
  __WR->set_dns_host(dns_host);
  __WR->set_port(port);
  __get_dest_ip_addr_by_dns_host();                //получение ip адресов web сервера
  __WR->set_host(__WR->get_first_dest_ip_addr());  //взять первый адрес из списка (остальные пока не используем, если используем, делаем последовательные коннекты и проверяем на каждом наличие файла с данным ID)

  if(!__WR->get_transport())
    {
    /*
    string   dns_host;
    unsigned port;
    select_dns_host(__resource, dns_host, port);
  __WR->set_dns_host(dns_host);
  __WR->set_port(port);
  __get_dest_ip_addr_by_dns_host();                //получение ip адресов web сервера
  __WR->set_host(__WR->get_first_dest_ip_addr());  //взять первый адрес из списка (остальные пока не используем, если используем, делаем последовательные коннекты и проверяем на каждом наличие файла с данным ID)
    */
  __WR->set_socket(exsCreateTCPSocket_ADDR_ANY());
  __WR->wpt = new TWebParsThread(true,    &MainFormSLS->ofs->elt, __WR);
  __WR->wrt = new TWebRecvTcpThread(true, &MainFormSLS->ofs->elt, __WR);
  __WR->wst = new TWebSendTcpThread(true, &MainFormSLS->ofs->elt, __WR);
    }
  else
    {
    __WR->wpt         = new TWebParsThread(true,    &MainFormSLS->ofs->elt, __WR);
    __WR->sr_tls_ft_t = new TSipRecvTls_FileTransfer_Thread( true, __WR->get_host(), port, &MainFormSLS->ofs->elt, MainFormSLS->Sip, __WR );
    __WR->ss_tls_ft_t = new TSipSendTls_FileTransfer_Thread(true, __WR->get_host(),  port, &MainFormSLS->ofs->elt, MainFormSLS->Sip, __WR ); //Resume after connect

    __WR->sr_tls_ft_t->Resume_Thread();
    }
  while(!Terminated)
       {
       if(__WR->get_delete_req())
         {
       ::Sleep(1);
         continue; //Wait for thread termination
         }
       if(__WR->get_fexch()->fexch_empty())
         {
       __WR->set_state_of_file_transfer(3);  //received all requested list (Setting value 3 may be at this only). Waiting for delete TWebReq (in the Timer1Timer() check_file_exch_activity())
         Suspend_Thread();
         continue;
         }
       TExchFileMsg efm(0);
       while(__WR->get_fexch()->fexch_get(efm))  //Получение всех заявленных запросов на прием файлов из FEXCH
            {
            if(Terminated)
               break;
            if(efm.get_req_type() == 1)  // Request on send file
              {
              PROC_OF_FILE_SENDING_REQUEST(efm); //!!!
              while(__WR->file_transfer_in_progress()){
                 ::Sleep(100);
                   if(Terminated)
                      break;
                   }
              continue;
              }
            string file_storage = efm.get_received_file_storage(); //Директория, указанная при старте скачивания по правой кнопке. Если не указана, то директория формируется по умолчанию из FEXCH.__default_subdir_of_received_file_storage
            if(file_storage.empty())
               file_storage = __get_default_file_storage(efm.file_sender);

            TExchNotifyMsg enm;
            if(efm.parsed())
              {
              enm.file_id   = efm.get_substring_by_pattern("id:");
              enm.file_name = efm.get_substring_by_pattern("name:");
              enm.thumb_id  = efm.get_substring_by_pattern("thumb:");
              }
            else
              efm.parsing_notfy_msg(enm);

            string file_name = file_storage + "\\" + enm.file_name;
            if(::FileExists(file_name.c_str()))
              {
              //ShellExecute(MainFormSLS->Handle, "open", file_name.c_str(), NULL, NULL, SW_SHOWMAXIMIZED);
              ShellExecuteMy(file_name);
              break;
              }

            bool RECV_FILE_OPEN = false;
            if(__WR->wpt)
              if(check_directory_existence(file_storage))
                {
                FILE* F = fopen(file_name.c_str(), "wb");
                if(F)
                  {
                __WR->wpt->assign_display_and_htry_index(efm.grid_arow);   //for display end of downloading  and write to htry that file is downloaded
                __WR->wpt->assign_file_id(enm.file_id);
                __WR->wpt->assign_file_storage(file_storage, enm.file_name);
                __WR->wpt->assign_hstry_subdir(efm.year_month_day);
                __WR->wpt->assign_FILE(F);
                  RECV_FILE_OPEN = true;
                __lasterr = "\nOpen file: \"" + file_name + "\"\n";
                  sendlasterr();
                  }
                }
            if(!RECV_FILE_OPEN)
              {
            __lasterr = "\nError: TWebPlannerTcpThread: can't open file \"" + file_name + "\"\n";
              sendlasterr();
              continue;    //Не могу открыть файл для сохранения. Переход в начало цикла.
              }

          __FILE_RECEIVE_IN_PROGRESS(efm.grid_arow);   //State in IM_DrawGrid

            if(__WR->wpt)
               __WR->wpt->Resume();
            if(__WR->wrt)
               __WR->wrt->Resume();

              if(!enm.file_id.empty())
                {
                string url       = "/download/" + enm.file_id;  //enm.thumb_id;
                string get_http  = "GET " + url + " HTTP/1.1\r\n";
                get_http        += "Host:" + WS + __resource + crlf;
                get_http        += "Connection: Keep-Alive\r\n\r\n";
                int sz           = get_http.size();
                while(__WR->is_wait_connect())
                     {
                     if(Terminated)
                       break;
                     ::Sleep(20);
                     }
                if(Terminated || !__WR->connected())
                    break;
                TDataWebBlock* dwb = new TDataWebBlock(sz);
                if(dwb)
                  {
                  memcpy(&dwb->v[0], get_http.c_str(), sz);
                __WR->set_state_of_file_transfer(1);
                __WR->PUSH_SEND_BLOCK(dwb);
                if(__WR->ss_tls_ft_t) {
                    __WR->ss_tls_ft_t->Resume_Thread();
                    while(__WR->file_transfer_in_progress()){
                          ::Sleep(100);
                          if(Terminated)
                             break;
                    }
                  }
                  }

                }
           } //while(__WR->get_fexch()->fexch_get(efm))
       }
  }
}
//------------------------------------------------------------------------------
void __fastcall TWebPlannerTcpThread::PROC_OF_FILE_SENDING_REQUEST(TExchFileMsg& efm)
{
int TRANSPORT = __WR->get_transport();
__WR->set_req_type(1); //req type - Send file
int st = efm.sending_file_path.rfind("\\");
if(st != -1)
  {
  st++;
  if(st < (int)efm.sending_file_path.length())
    {
    efm.file_name = efm.sending_file_path.substr(st);
    int file_sz      = 0;
    UBYTE send_buf[SND_SZ];
    FILE* f = fopen(efm.sending_file_path.c_str(),"rb");
    if(f)
      {
      fseek(f, 0L, SEEK_END);
      file_sz = ftell(f);
      fseek(f, 0L, SEEK_SET);

      string boundary           = "---------------------------7e1169311c0798";
      string FirstBoundary      = "--" + boundary + crlf;
      string ContentDisposition = "Content-Disposition: form-data; name=\"uploads[]\"; filename=" + (string)"\"" + "desktop" + getFileExt(efm.file_name) + "\"" + crlf;
      string ContentType        = "Content-Type:" + WS + __get_content_type(efm.file_name) + sdpboundary;
      string LastBoundary       = "\r\n-----------------------------7e1169311c0798--\r\n";

      int LastBoundary_size = LastBoundary.size();

      int content_length    = FirstBoundary.length()      +
                              ContentDisposition.length() +
                              ContentType.length()        +
                              file_sz                     +
                              LastBoundary_size;

      string post_http  = "POST /upload HTTP/1.1\r\n";
             post_http += "Accept: */*\r\n";
             post_http += "X-Requested-With: XMLHttpRequest\r\n";
             post_http += "Content-Type: multipart/form-data; boundary=" + boundary + crlf;
          //   post_http += "Referer: http://rastel.dyndns-work.com:25069/up/\r\n";
             post_http += "Accept-Language: ru,en-US;q=0.7,en;q=0.3\r\n";
             post_http += "Accept-Encoding: gzip, deflate\r\n";
          //   post_http += "User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/51.0.2704.79 Safari/537.36 Edge/14.14393\r\n";
             post_http += "Host:" + WS + __resource + crlf;
             post_http += "Content-Length: " + uint_to_str(content_length) + "\r\n";
             post_http += "Connection: Keep-Alive\r\n";
             post_http += "Cache-Control: no-cache\r\n\r\n";
             post_http += FirstBoundary      +
                          ContentDisposition +
                          ContentType;


             if(__WR->wpt)
               {
               __WR->wpt->assign_dest_list(efm.q_cont); //List of destination Contacs (most commonly - one element)
               __WR->wpt->assign_sending_file_name(efm.file_name);
               __WR->wpt->Resume();
               }

             if(TRANSPORT == 0){      // TCP
               if(__WR->wrt)
                  __WR->wrt->Resume();
               }
             else if(TRANSPORT == 1){ // TLS
               if(__WR->sr_tls_ft_t)
                  __WR->sr_tls_ft_t->Resume();
               }

             while(!__WR->connected())   //Ожидание коннекта
                  {
                  if(Terminated)
                     break;
                   ::Sleep(20);
                  }
             if(Terminated)
                 return;


    __WR->set_state_of_file_transfer(1);
      int sz = post_http.size();
      TDataWebBlock* dwb = new TDataWebBlock(sz);
      if(dwb)
        {
        memcpy(&dwb->v[0], post_http.c_str(), sz);
      __WR->PUSH_SEND_BLOCK(dwb);
        if(TRANSPORT == 0){      // TCP
           if(__WR->wst)
              __WR->wst->Resume_Thread();
          }
        else if(TRANSPORT == 1){ // TLS
           if(__WR->ss_tls_ft_t)
              __WR->ss_tls_ft_t->Resume_Thread();
          }
        }

      int block_length = 0;
      while(( block_length = fread(send_buf, 1, SND_SZ, f)) == SND_SZ)
           {
           while(__WR->SIZE_OF_SEND_QUEUE() > 20){
                ::Sleep(1);                     //Притормозить, не создавать большую очередь
                }
           dwb = new TDataWebBlock(block_length);
           if(dwb){
             memcpy(&dwb->v[0], send_buf, block_length);
           __WR->PUSH_SEND_BLOCK(dwb);
             if(TRANSPORT == 0){      // TCP
                if(__WR->wst)
                   __WR->wst->Resume_Thread();
                }
             else if(TRANSPORT == 1){ // TLS
                if(__WR->ss_tls_ft_t)
                   __WR->ss_tls_ft_t->Resume_Thread();
                }
             }
           }
      if(block_length)
        {
        dwb = new TDataWebBlock(block_length);
        if(dwb)
          {
          memcpy(&dwb->v[0], send_buf, block_length);
        __WR->PUSH_SEND_BLOCK(dwb);
          if(TRANSPORT == 0){      // TCP
             if(__WR->wst)
               __WR->wst->Resume_Thread();
             }
          else if(TRANSPORT == 1){ // TLS
             if(__WR->ss_tls_ft_t)
                __WR->ss_tls_ft_t->Resume_Thread();
             }
          }
        }  //if(block_length)

      dwb = new TDataWebBlock(LastBoundary_size);
      if(dwb)
        {
        memcpy(&dwb->v[0], LastBoundary.c_str(), LastBoundary_size);
      __WR->PUSH_SEND_BLOCK(dwb);
        if(TRANSPORT == 0){      // TCP
           if(__WR->wst)
              __WR->wst->Resume_Thread();
           }
        else if(TRANSPORT == 1){ // TLS
           if(__WR->ss_tls_ft_t)
              __WR->ss_tls_ft_t->Resume_Thread();
           }
        }  //if(dwb)
      fclose(f);
      } //if(f)
    }
  }
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
//--- Chunked transfer encoding - механизм передачи данных в протоколе передачи гипертекста (HTTP), позволяющий надёжно доставлять данные от сервера клиенту
//--- (чаще всего клиентскому web-браузеру) без необходимости заранее знать точный размер всего тела HTTP-сообщения.
//--- Это достигается разбиением сообщения на небольшие части (chunks), а затем передачей каждой части с указанием только её размера (в шестнадцатеричном виде).
//--- Окончание передачи сообщения определяется наличием последней части с нулевой длиной. Такой механизм позволяет передать динамически сформированные объекты,
//--- для которых нельзя заранее определить размер. Он стал доступен только начиная с HTTP версии 1.1 (HTTP/1.1).
//--- Без механизма сhunked transfer encoding с каждым HTTP-пакетом необходимо указывать заголовок Content-Length, чтобы клиент мог найти конец передаваемого сообщения.

//--- Для отделения записей размеров блоков (частей) от их содержания используется разделитель CRLF (как строка: "\r\n"; как байты в формате HEX: 0x0D, 0x0A).
//--- Длина блока - это размер содержания блока, разделители CRLF не учитываются.
//--- Схематическое представление: <длина блока в HEX><CRLF><содержание блока><CRLF>
//--- Последний блок строится по той же схеме, потому имеет следующий вид по причине отсутствия содержания: 0<CRLF><CRLF>

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
void __fastcall TWebParsThread::__proc_200_ok_resp_on_send_file(const string& s)
{
//string s_start = "<file";
//string s_end   = "/>";

RCS.set_received_200_OK(true);
RCS.clear_chunks_queue();
//int length_of_file_id = 0;
int len = s.length();
int st  = s.find(sdpboundary);
if(st != -1)
  {
  RCS.transfer_encoding_chuncked = __transfer_encoding_chancked(s, st);   // Если transfer_encoding_chancked == false?, то надо искать "Content-Length:"
  st += 4;
  if(RCS.transfer_encoding_chuncked)
     RCS.get_received_chunks(s, st, len);

  if(RCS.get_received_end_chunk())
    {
    TChunk chunk;
    while(RCS.get_chunk_from_received_list(chunk))
         {
         if(!chunk.s.empty())
           {
          __proc_received_chunks(s_start, s_end, chunk.s);


           /*
           string thumb      = get_thumb();     //thumb (preview) may be absent
           string file_id    = chunk.s;
           string file_name  = get_sending_file_name();
           string notify_msg = s_start + WS + "id='" + file_id + "'" + WS + WS + "\n";
           if(!file_name.empty())
              notify_msg   += "name='" + file_name + "'" + WS + WS + "\n";
           if(!thumb.empty())
              notify_msg   += "thumb='" + thumb + "'" + WS;
           notify_msg       += s_end; // + crlf;
           string dest_contact;
           while(get_dest(dest_contact))    //После окончания загрузки на сервер отравляем сообщение абоненту (или группе абонентов) о возмлжности принять файл
                {
                if(MainFormSLS->Sip)
                  if(MainFormSLS->Sip->uac)
                   {
                   TExchBuf* buf = new TExchBuf(WM_APP_MSG_WPARAM__UAC);
                   if(buf)
                     {
                     buf->emt   = ExchMsgType_FileTransfer_Notification;
                     buf->msg   = notify_msg;
                     buf->msg_1 = dest_contact;
                     MainFormSLS->Sip->uac->insertExchLst(buf);
                   ::PostMessage(MainFormSLS->Handle, SIP_UA_MSG, WM_APP_MSG_WPARAM__UAC, WM_APP_MSG_LPARAM__READLIST);
                     }
                   }
               }
              */

           return;
           }   //if(!chunk.s.empty())
         }
    }

  if(st < len)
    {
    int en = s.find(crlf, st);
    if(en != -1)
      {
  //    length_of_file_id = strtoint(s.substr(st, en - st));
      st  = en;
      st += 2;
      if(st < len)
        {
        en = s.find(crlf, st);
        if(en != -1)
          {
          string thumb      = get_thumb();     //thumb (preview) may be absent
          string file_id    = s.substr(st, en - st);
          string file_name  = get_sending_file_name();
          string notify_msg = s_start + WS + "id='" + file_id + "'" + WS + WS + "\n";
          if(!file_name.empty())
              notify_msg   += "name='" + file_name + "'" + WS + WS + "\n";
          if(!thumb.empty())
              notify_msg   += "thumb='" + thumb + "'" + WS;
          notify_msg       += s_end; // + crlf;
          string dest_contact;
          while(get_dest(dest_contact))    //После окончания загрузки на сервер отравляем сообщение абоненту (или группе абонентов) о возмлжности принять файл
               {
               if(MainFormSLS->Sip)
                 if(MainFormSLS->Sip->uac)
                   {
                   TExchBuf* buf = new TExchBuf(WM_APP_MSG_WPARAM__UAC);
                   if(buf)
                     {
                     buf->emt   = ExchMsgType_FileTransfer_Notification;
                     buf->msg   = notify_msg;
                     buf->msg_1 = dest_contact;
                     MainFormSLS->Sip->uac->insertExchLst(buf);
                   ::PostMessage(MainFormSLS->Handle, SIP_UA_MSG, WM_APP_MSG_WPARAM__UAC, WM_APP_MSG_LPARAM__READLIST);
                     }
                   }
               }
          }
        }
      }
    }
  }
}
//----------------------------------------------------------------------------------
void __fastcall TWebParsThread::__proc_received_chunks(const string& s_start, const string& s_end, const string& s)
{
string thumb      = get_thumb();     //thumb (preview) may be absent
string file_id    = s;
string file_name  = get_sending_file_name();
string notify_msg = s_start + WS + "id='" + file_id + "'" + WS + WS + "\n";
if(!file_name.empty())
   notify_msg   += "name='" + file_name + "'" + WS + WS + "\n";
if(!thumb.empty())
   notify_msg   += "thumb='" + thumb + "'" + WS;
notify_msg       += s_end; // + crlf;
string dest_contact;
while(get_dest(dest_contact))    //После окончания загрузки на сервер отравляем сообщение абоненту (или группе абонентов) о возмлжности принять файл
     {
     if(MainFormSLS->Sip)
       if(MainFormSLS->Sip->uac)
        {
        TExchBuf* buf = new TExchBuf(WM_APP_MSG_WPARAM__UAC);
        if(buf)
          {
          buf->emt   = ExchMsgType_FileTransfer_Notification;
          buf->msg   = notify_msg;
          buf->msg_1 = dest_contact;
          MainFormSLS->Sip->uac->insertExchLst(buf);
        ::PostMessage(MainFormSLS->Handle, SIP_UA_MSG, WM_APP_MSG_WPARAM__UAC, WM_APP_MSG_LPARAM__READLIST);
          }
        }
    }
}
//-----------------------------------------------------------------------------------
bool __fastcall TWebParsThread::__transfer_encoding_chancked(const string& s, int end)
{
bool rv = false;
int st = s.find("Transfer-Encoding:");
if(st != -1)
  {
  st += 18;
  if(st < end)
    {
    int en = s.find(crlf, st);
    if(en < end)
      {
      st = s.find("chunked", st);
      if(st < en)
         rv = true;
      }
    }
  }
return rv;
}
//----------------------------------------------------------------------------------------
//--- start - position after sdpboundary. len - full length of the received responce
//----------------------------------------------------------------------------------------
void __fastcall TReceivedChunkStruct::get_received_chunks(const string& s, int start, int len)
{
int st = start;
while(st < len){
      if(__get_chunk(s, st, len)){
      __received_end_chunk = true;  //end chunk (with length == 0) received
        break;
        }                                                                                                              
     }
}
//-----------------------------------------------------------------------------------------
bool __fastcall TReceivedChunkStruct::__get_chunk(const string& s, int& start, int len)
{
bool rv             = false;
bool chunk_received = false;
TChunk chunk;
int st = s.find(crlf, start);
if(st != -1){
  if(st + 2 < len)
    {
    int st_1 = s.find(crlf, st + 2);
    if(st_1 != -1){
      string len_s = s.substr(start, st - start);
      len_s = "0x" + len_s;
      chunk.len = StrToIntDef(len_s.c_str(), 0);
      st += 2;
      chunk.s   = s.substr(st, st_1 - st);
      chunk_received = true;
      if(chunk.len == 0)
         rv = true;
      start = st_1 + 2;
   __update_chunks_queue(chunk);
      }
    }
  }
if(!chunk_received)
   chunks = s.substr(start); // сохранить частично принятый chunk
return rv;
}
//-----------------------------------------------------------------------------------------
void __fastcall TReceivedChunkStruct::__update_chunks_queue(const TChunk& chunk)
{
::EnterCriticalSection(&__rs_cs);
__chunk_list.push(chunk);
::LeaveCriticalSection(&__rs_cs);
}
//-----------------------------------------------------------------------------------------
void __fastcall TReceivedChunkStruct::clear_chunks_queue()
{
::EnterCriticalSection(&__rs_cs);
  while(!__chunk_list.empty())
         __chunk_list.pop();
__received_end_chunk = false;
::LeaveCriticalSection(&__rs_cs);
}
//-----------------------------------------------------------------------------------
bool __fastcall TReceivedChunkStruct::get_chunk_from_received_list(TChunk& chunk)
{
bool rv = false;
::EnterCriticalSection(&__rs_cs);
  if(!__chunk_list.empty())
    {
    chunk = __chunk_list.front();
  __chunk_list.pop();
    rv = true;
    }
::LeaveCriticalSection(&__rs_cs);
return rv;
}
//-----------------------------------------------------------------------------------
void __fastcall TWebParsThread::__FILE_RECEIVED()
{
if(MainFormSLS->Sip)
  if(MainFormSLS->Sip->uac)
    {
    TExchBuf* buf = new TExchBuf(WM_APP_MSG_WPARAM__UAC);
    if(buf)
      {
      buf->emt   = ExchMsgType_FileTransfer_FileReceived;
      buf->tag   = __display_index;
      buf->tag_1 = __total_content_length;
      buf->msg   = __get_file_id();
      MainFormSLS->Sip->uac->insertExchLst(buf);
    ::PostMessage(MainFormSLS->Handle, SIP_UA_MSG, WM_APP_MSG_WPARAM__UAC, WM_APP_MSG_LPARAM__READLIST);
      }
    }
__display_index = -1;
}
//----------------------------------------------------------------------------------
void __fastcall TWebPlannerTcpThread::__FILE_RECEIVE_IN_PROGRESS(int display_index)
{
if(MainFormSLS->Sip)
  if(MainFormSLS->Sip->uac)
    {
    TExchBuf* buf = new TExchBuf(WM_APP_MSG_WPARAM__UAC);
    if(buf)
      {
      buf->emt = ExchMsgType_FileTransfer_InProgress;
      buf->tag = display_index;
      MainFormSLS->Sip->uac->insertExchLst(buf);
    ::PostMessage(MainFormSLS->Handle, SIP_UA_MSG, WM_APP_MSG_WPARAM__UAC, WM_APP_MSG_LPARAM__READLIST);
      }
    }
}

void sosock_error_handler(void* ref, const char* err) {
  std::cout << "err:" << ref << std::string(err) << std::endl;
}


TDataWebBlock::TDataWebBlock(const char* buf, int size) {
    v.resize(size);
    memcpy(&v[0], buf, size);
    bread = size;
    dt = dt.CurrentDateTime();
}

struct FileTransfer_Sosock : public Sosock_Client {
  TWebReq* webReq;

  FileTransfer_Sosock(TWebReq* wr)
    : webReq(wr) {
  }
  ~FileTransfer_Sosock() {
  }

  void onConnect() {
    tls_connect_file_transfer_handler(this);

    webReq->set_connected(true);
    webReq->set_wait_connect(false);
    if (webReq->sr_tls_ft_t)
      webReq->sr_tls_ft_t->r = this;
    if (webReq->ss_tls_ft_t)
      webReq->ss_tls_ft_t->r = this;
  };

  void onDisconnect() {
    webReq->set_connected(false);
    webReq->set_wait_connect(false);
    webReq->set_state_of_file_transfer(3);
    tls_disconnect_file_transfer_handler(this);
    delete this;
  };

  void onRead(const char* buf, size_t size) {
    //tls_read_file_transfer_handler(buf, size, this);
    if (webReq->get_delete_req())
      return;
    TDataWebBlock* dwb = new TDataWebBlock(buf, size);
    webReq->PUSH_RCVD_BLOCK(dwb);
  };

  virtual void onError(const char* msg){
  };
  
};

//-----------------------------------------------------------------------------------
void __fastcall TSipRecvTls_FileTransfer_Thread::Execute()
{
__WR->set_wait_connect(true);
FileTransfer_Sosock* sock = new FileTransfer_Sosock(__WR);
r = Sosock_Thread::instance().create_client(sock, host, port);
if(__WR->ss_tls_ft_t)
   __WR->ss_tls_ft_t->r = r;
}
//-----------------------------------------------------------------------------------


