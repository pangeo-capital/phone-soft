//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "WinRDefs.h"
#include "tcp.h"
#include "SipClient_Unit.h"
#include ".\\tls_sock\\include\\tls_sock.h"

#define SIP_TCP_MAX_PACKET 8192
static unsigned tcp_disconnect_count = 0;  //необходим , чтобы уменьшить размер log файла при отсутствии выхода в интернет - постоянный вызов tcp_disconnect_handler()
//-----------------------------------------------------------------------------
#pragma package(smart_init)
//-----------------------------------------------------------------------------
#ifndef INTRN_TCP
void tcp_connect_handler(void* ref) {
try{
if(MainFormSLS->DestroyReq)return;
tcp_disconnect_count = 0;
if(MainFormSLS->ofs->elt)
  {
  TDateTime DateTime = DateTime.CurrentDateTime();
  string time_str;
  exsDateTime(DateTime,time_str);
  string s = "\n" + time_str + WS + "TCP connection" + WS + inttostr((int)ref) + WS + "established";

  ::EnterCriticalSection(&MainFormSLS->Sip->tcp_t_cs);
    if(MainFormSLS->Sip->sr_tcp_t)
       s += WS + "to" + WS + MainFormSLS->Sip->sr_tcp_t->host + ":" + inttostr(MainFormSLS->Sip->sr_tcp_t->port);
  ::LeaveCriticalSection(&MainFormSLS->Sip->tcp_t_cs);

  MainFormSLS->ofs->elt->FputEvt(s,1);
  }
MainFormSLS->Sip->collectLocalHostInterfaces(&MainFormSLS->iniData);
MainFormSLS->Stun.StunClientProc(&MainFormSLS->iniData,MainFormSLS->Sip,MainFormSLS->ofs->elt);

::EnterCriticalSection(&MainFormSLS->Sip->tcp_t_cs);
  if(MainFormSLS->Sip->sr_tcp_t)
   if(MainFormSLS->Sip->ss_tcp_t)
     {
     MainFormSLS->Sip->ss_tcp_t->r = MainFormSLS->Sip->sr_tcp_t->r;
     if(MainFormSLS->Sip->ss_tcp_t->Suspended)
        MainFormSLS->Sip->ss_tcp_t->Resume_Thread();
     }
::LeaveCriticalSection(&MainFormSLS->Sip->tcp_t_cs);

if(MainFormSLS->Sip->TCP_Dropped)
  {
  MainFormSLS->Sip->TCP_Dropped = false;
  MainFormSLS->Sip->initRegistrationProc();
  }
}//try
catch(Exception& e){exsSstEXCEPTION(MainFormSLS->ofs->elt,"__tcp_connect_handler",e);}
}
//-----------------------------------------------------------------------------
void tcp_disconnect_handler(void* ref)
{
try{
if(MainFormSLS->DestroyReq)return;
tcp_disconnect_count++;
if(!MainFormSLS->Sip->TCP_Dropped)
  {
  if(MainFormSLS->lng == Lang_RU)
     MainFormSLS->Caption = "Потеряно соединение с сервером!";
  else
     MainFormSLS->Caption = "Connection Lost!";
  }
MainFormSLS->Sip->TCP_Dropped = true;
if(tcp_disconnect_count < 3)    //Ограничение размера лог файла
  if(MainFormSLS->ofs->elt)
    {
    TDateTime DateTime = DateTime.CurrentDateTime();
    string time_str;
    exsDateTime(DateTime,time_str);
    string s = "\n" + time_str + WS + "TCP link" + WS + inttostr((int)ref) + WS + "disconnected. Try reconnect";
    ::EnterCriticalSection(&MainFormSLS->Sip->tcp_t_cs);
      if(MainFormSLS->Sip->sr_tcp_t)
         s += WS + "to" + WS + MainFormSLS->Sip->sr_tcp_t->host + ":" + inttostr(MainFormSLS->Sip->sr_tcp_t->port);
    ::LeaveCriticalSection(&MainFormSLS->Sip->tcp_t_cs);
    MainFormSLS->ofs->elt->FputEvt(s,1);
    }

::EnterCriticalSection(&MainFormSLS->Sip->tcp_t_cs);
  ::Sleep(1000);
  if(MainFormSLS->Sip->sr_tcp_t)
    if(MainFormSLS->Sip->sr_tcp_t->r==ref)
       MainFormSLS->Sip->sr_tcp_t->r = so_start_client_tcp((char*)MainFormSLS->Sip->sr_tcp_t->host.c_str(),MainFormSLS->Sip->sr_tcp_t->port);
::LeaveCriticalSection(&MainFormSLS->Sip->tcp_t_cs);
}//try
catch(Exception& e){exsSstEXCEPTION(MainFormSLS->ofs->elt,"__tcp_disconnect_handler",e);}
}
//-------------------------------------------------------------------------------
static int pktn;
void tcp_read_handler(const char* rcvbuf, size_t bread, void* ref)
{
try{
if(MainFormSLS->DestroyReq)return;
if(bread)
  {
  TOutPutUdpBlock* opb = new TOutPutUdpBlock(pktn);
  if(opb)
    {
    opb->s.resize(bread);
    memcpy(&opb->s[0],rcvbuf,bread);
    opb->datasize = bread; //for non string content
    opb->getDateTime();
    ::EnterCriticalSection(&MainFormSLS->Sip->tcp_t_cs);
      if((MainFormSLS->Sip->spt)&&(MainFormSLS->Sip->sr_tcp_t))
        {
        opb->FromIP   = MainFormSLS->Sip->sr_tcp_t->host;
        opb->FromPort = MainFormSLS->Sip->sr_tcp_t->port;
        MainFormSLS->Sip->spt->setQueue(opb);
        MainFormSLS->Sip->sr_tcp_t->updateSentQueue(opb);
        }
      else
        delete opb;
    ::LeaveCriticalSection(&MainFormSLS->Sip->tcp_t_cs);
    }
  }
}//try
catch(Exception& e){exsSstEXCEPTION(MainFormSLS->ofs->elt,"__tcp_read_handler",e);}
}
#endif
//-----------------------------------------------------------------------------
void __fastcall TSipRecvTcpThread::Execute()
{
try{
#ifdef INTRN_TCP
Start_INTRN_TCP();
#else
Start_EXTRN_TCP();
#endif
}//try
catch(Exception& e){exsSstEXCEPTION(*eltp,"__TSipRecvTcpThread::Execute",e);}
}
//----------------------------------------------------------------------------
void __fastcall TSipSendTcpThread::Execute()
{
try{
while(!Terminated)
     {
     #ifndef INTRN_TCP
     if(!r)
       {
       Suspend_Thread();
       continue;
       }
     #endif
     BaseExchangeBlock* bb = (BaseExchangeBlock*)getQueue();
     if(!bb)
       {
       Suspend_Thread();
       continue;
       }
     switch(bb->getBlockType()){
           case TOutputSipBuf_BLOCKTYPE:{
           /***** Tyurin *****/
                /*if(bb->__sls == SPS_INFO_REQ)
                  {
                  int a = 5;
                  }*/
                TOutputSipBuf* ospb = (TOutputSipBuf*)bb;
                sendbuf(ospb);
                break;
                }
           case TOutPutUdpBlock_BLOCKTYPE:{
                TOutPutUdpBlock* opb = (TOutPutUdpBlock*)bb;
                sendbuf(opb);
                break;
                }
           case TSipParsBuf_BLOCKTYPE:{
                TSipParsBuf* spb = (TSipParsBuf*)bb;
                sendbuf(spb);
                break;
                }
           }
     if(bb->get_req_to_delete())
       {
       if(bb->getReferenceCount() < 3)
          exsDeleteSentBlock(bb);
       }
     else
       bb->decReferenceCount();
     }
}//try
catch(Exception& e){exsSstEXCEPTION(*eltp,"__TSipSendTcpThread::Execute",e);}
}
//----------------------------------------------------------------------------
void __fastcall TSipSendTcpThread::sendbuf(TOutputSipBuf* ospb)
{
int len = ospb->s.size();
if(len)
  {
  #ifdef SIP_LogSendPacket
  TDateTime DateTime = DateTime.CurrentDateTime();
  #endif

  #ifdef INTRN_TCP
  send_tcp(ospb->s.c_str(), len);
  #else
  so_write_some(r,&ospb->s[0],len);
  #endif

  #ifdef SIP_LogSendPacket
  LOG_SendPacket(DateTime,ospb,len);
  #endif
  }
}
//----------------------------------------------------------------------------
void __fastcall TSipSendTcpThread::sendbuf(TOutPutUdpBlock* opb)
{
int len = opb->s.size();
if(len)
  {
  #ifdef SIP_LogSendPacket
  TDateTime DateTime = DateTime.CurrentDateTime();
  #endif

  #ifdef INTRN_TCP
  send_tcp(opb->s.c_str(), len);
  #else
  so_write_some(r,&opb->s[0],len);
  #endif

  #ifdef SIP_LogSendPacket
  LOG_SendPacket(DateTime,opb,len);
  #endif
  }
}
//----------------------------------------------------------------------------
void __fastcall TSipSendTcpThread::sendbuf(TSipParsBuf* spb)
{
int len = spb->s.size();
if(len)
  {
  #ifdef SIP_LogSendPacket
  TDateTime DateTime = DateTime.CurrentDateTime();
  #endif

  #ifdef INTRN_TCP
  send_tcp(spb->s.c_str(), len);
  #else
  so_write_some(r,&spb->s[0],len);
  #endif
  
  #ifdef SIP_LogSendPacket
  LOG_SendPacket(DateTime,spb,len);
  #endif
  }
}
//----------------------------------------------------------------------------
#ifdef SIP_LogSendPacket
void __fastcall TSipSendTcpThread::LOG_SendPacket(TDateTime& DateTime,TOutPutUdpBlock* opb,int len)
{
TEventLogThread* elt = getLog();
if(elt)
  {
  string str;
  exsTime(DateTime,str);
  str = "\n" + str + " Pckt Sent Len " + inttostr(len) + "\n";
 // for(int i=0;i<len;i++)
 //   str += " " + inttohexstr(opb->v[i],2);
 // str+="\n";
  elt->FputEvt(str + opb->s);
  }
}
//----------------------------------------------------------------------------
void __fastcall TSipSendTcpThread::LOG_SendPacket(TDateTime& DateTime,TOutPutDtmfBlock* opd,int len)
{
TEventLogThread* elt = getLog();
if(elt)
  {
  string str;
  exsTime(DateTime,str);
  str = "\n" + str + " Pckt Sent Len " + inttostr(len) + "\n";
  for(int i=0;i<len;i++)
     str += " " + inttohexstr(opd->v[i],2);
  str+="\n";
  elt->FputEvt(str,1);
  }
}
//----------------------------------------------------------------------------
void __fastcall TSipSendTcpThread::LOG_SendPacket(TDateTime& DateTime,TOutputSipBuf* ospb,int len)
{
TEventLogThread* elt = getLog();
if(elt)
  {
  string str;
  exsTime(DateTime,str);
  str = "\n" + str + " Pckt Sent Len " + inttostr(len) + "\n";
  string s = UTF8_2_ANSI(ospb->s);
  elt->FputEvt(str + s);
  }
}
//----------------------------------------------------------------------------
void __fastcall TSipSendTcpThread::LOG_SendPacket(TDateTime& DateTime,TSipParsBuf* spb,int len)
{
TEventLogThread* elt = getLog();
if(elt)
  {
  string str;
  exsTime(DateTime,str);
  str = "\n" + str + " Pckt Sent Len " + inttostr(len) + "\n";
  elt->FputEvt(str + spb->s);
  }
}
#endif
//----------------------------------------------------------------------------
#ifndef INTRN_TCP
void __fastcall TSipRecvTcpThread::Start_EXTRN_TCP()
{
so_set_start_handler(&tcp_connect_handler);
so_set_destr_handler(&tcp_disconnect_handler);
so_set_read_handler(&tcp_read_handler);
r=so_start_client_tcp((char*)host.c_str(),port);
so_run();
}
#endif
//----------------------------------------------------------------------------
void __fastcall TSipRecvTcpThread::Start_INTRN_TCP()
{
sck = exsCreateTCPSocket_ADDR_ANY();
while(!Terminated)
     {
     Connect();
     if(MainFormSLS->Sip->TCP_Dropped)
       {
       MainFormSLS->Sip->TCP_Dropped = false;
     ::PostMessage(MainFormSLS->Handle, CONTROL_MSG, WM_APP_MSG_WPARAM__INIT_REG_PROC, WM_APP_MSG_LPARAM__NOPARAM);
       }
     Receive();
     }
}
//----------------------------------------------------------------------------
void __fastcall TSipRecvTcpThread::Connect()
{
struct sockaddr_in dest;
memset(&dest,0,sizeof(dest));
dest.sin_family      = AF_INET;
dest.sin_addr.s_addr = inet_addr(host.c_str());
dest.sin_port        = htons(port);
while(!Terminated)
     {
     if(NextConnectTime_TCP.CurrentDateTime() < NextConnectTime_TCP)          //После предыдущей ПОПЫТКМ коннекта времени прошло менее заданного интервала ( see void __fastcall TSipRecvTcpThread::CheckConnError()
       {
     ::Sleep(20);
       continue;
       }
     if((ConnTime_TCP.CurrentDateTime() - ConnTime_TCP) < TDateTime(0,0,10,0)) //После предыдущего УСПЕШНОГО коннекта прошло менее 10 сек 
       {
     ::Sleep(20);
       continue;
       }
     if(sck == INVALID_SOCKET)
        sck = exsCreateTCPSocket_ADDR_ANY();
     log_tcp_socket_action(sck,3);            //log try to CONNECT socket
     int bcnnct = connect(sck,(struct sockaddr *)&dest, sizeof(dest));
     if(bcnnct == SOCKET_ERROR)
       {
       MainFormSLS->Sip->TCP_Dropped = true;
       SOCKET SCK = sck;
       CheckConnError("TSipRecvTcpThread::Connect()");   //::closesocket(sck) and sck = INVALID_SOCKET  inside CheckConnError()
       if(SCK != INVALID_SOCKET)
         if(sck == INVALID_SOCKET) // SOCKET сlosed at this time (in the CheckConnError())
           log_tcp_socket_action(SCK,0);        //log CLOSED socket
       sck = exsCreateTCPSocket_ADDR_ANY();
       log_tcp_socket_action(sck,1);            //log CREATED socket
       if(Sip->spt)
          Sip->spt->set_REQ_TO_CLEAR_INCOMPLETE_SIP_TCP_MSGS();
       continue;
       }
     conn_count = 0;
     log_tcp_socket_action(sck,2);              //log CONNECTED socket
     if(Sip->spt)
         Sip->spt->set_REQ_TO_CLEAR_INCOMPLETE_SIP_TCP_MSGS();
     ConnTime_TCP = ConnTime_TCP.CurrentDateTime();
     break;
     }
}
//----------------------------------------------------------------------------
#ifdef INTRN_TCP
static int pktn;
void __fastcall TSipRecvTcpThread::Receive()
{
while(!Terminated)
     {
     vector<UBYTE> v(SIP_TCP_MAX_PACKET,0);
     int bread = recv(sck,&v[0],SIP_TCP_MAX_PACKET - 1,0);
     if(!bread)              //Remote socket gracefully disconnected
       {
       SOCKET SCK = sck;
       ::closesocket(sck);
       sck = INVALID_SOCKET;     
       log_tcp_socket_action(SCK,6);        //log closed socket
       if(Sip->spt)
          Sip->spt->set_REQ_TO_CLEAR_INCOMPLETE_SIP_TCP_MSGS();
       Sip->TCP_Dropped = true;
     ::PostMessage(MainFormSLS->Handle, CONTROL_MSG, WM_APP_MSG_WPARAM__TCP_CONNECTION_DROPPED, WM_APP_MSG_LPARAM__NOPARAM);
       break;          //Go to new circle of tcp connect (see TSipRecvTcpThread::Start_INTRN_TCP())
       }
     if(MainFormSLS->DestroyReq)break;
     if(bread == SOCKET_ERROR)
       {
       SOCKET SCK = sck;
       int err = WSAGetLastError();
       ::closesocket(sck);
       sck = INVALID_SOCKET;
       lasterr.clear();
       GetLastSocketError(lasterr, err, "SipRecvTcpThread::Receive()");
       sendlasterr();
       log_tcp_socket_action(SCK,0);        //log closed socket
       if(Sip->spt)
          Sip->spt->set_REQ_TO_CLEAR_INCOMPLETE_SIP_TCP_MSGS();
       Sip->TCP_Dropped = true;
     ::PostMessage(MainFormSLS->Handle, CONTROL_MSG, WM_APP_MSG_WPARAM__TCP_CONNECTION_DROPPED, WM_APP_MSG_LPARAM__NOPARAM);
       break;              //Go to new circle of tcp connect (see TSipRecvTcpThread::Start_INTRN_TCP())
       }
     TOutPutUdpBlock* opb = new TOutPutUdpBlock(pktn);
     if(opb)
       {
       opb->setIntrnTcp();
       opb->s.resize(bread);
       memcpy(&opb->s[0],&v[0],bread);
       opb->datasize = bread; //for non string content
       opb->getDateTime();
       ::EnterCriticalSection(&MainFormSLS->Sip->tcp_t_cs);
         if((MainFormSLS->Sip->spt)&&(MainFormSLS->Sip->sr_tcp_t))
           {
           opb->FromIP   = MainFormSLS->Sip->sr_tcp_t->host;
           opb->FromPort = MainFormSLS->Sip->sr_tcp_t->port;
           bool a = false;
           MainFormSLS->Sip->spt->setQueue(opb);
           MainFormSLS->Sip->sr_tcp_t->updateSentQueue(opb, a);
           }
         else
           delete opb;
       ::LeaveCriticalSection(&MainFormSLS->Sip->tcp_t_cs);
       }
     }
}
//----------------------------------------------------------------------------
void __fastcall TSipSendTcpThread::send_tcp(const char* buf, int len)
{
::EnterCriticalSection(&MainFormSLS->Sip->tcp_t_cs);
  if(Sip->sr_tcp_t)
    {
    SOCKET SCK = Sip->sr_tcp_t->get_sck();
    if(SCK != INVALID_SOCKET)
      {
      if(send(SCK, buf, len, 0) == SOCKET_ERROR)
        {
        int err = WSAGetLastError();
        lasterr.clear();
        GetLastSocketError(lasterr, err, "SipSendTcpThread::send_tcp()");
        sendlasterr();
        }
      }
    }
::LeaveCriticalSection(&MainFormSLS->Sip->tcp_t_cs);
}
#endif  //#ifdef INTRN_TCP
//-----------------------------------------------------------------------------
int sock_debug_f(const char* severity, const char* fmt, ...)
{
if(tcp_disconnect_count > 2)
  return 1;
int rv = 0;
if(MainFormSLS->ofs)
 if(MainFormSLS->ofs->elt)
   {
    va_list ap;
    va_start(ap, fmt);
    va_start(ap, fmt);
    AnsiString S;
    S.vprintf(fmt, ap);
    va_end(ap);
    TDateTime DateTime = DateTime.CurrentDateTime();
    string time_str;
    exsDateTime(DateTime,time_str);
   //string s = "\n" + time_str + WS + "tcp_debug_f:" + WS + string(severity) + string(fmt) + S.c_str();
    string s = "\n" + time_str + WS + "\n<TCP_DEBUG>\n" + /*"fmt: " + string(fmt) + "\n" + */ S.c_str() + "</TCP_DEBUG>\n";
    MainFormSLS->ofs->elt->FputEvt(s);
    rv = 1;
   }
return rv;
}
//-----------------------------------------------------------------------------
void __fastcall TSipRecvTcpThread::log_tcp_socket_action(SOCKET socket, int type)
{
lasterr.clear();
TDateTime dt = dt.CurrentDateTime();
exsTime(dt,lasterr);
lasterr = "\n" + lasterr + " TCP SOCKET " + inttostr(socket) + WS;
switch(type){
      case 0: lasterr += "CLOSED\n";  break;
      case 1: lasterr += "CREATED\n"; break;
      case 2: lasterr += "CONNECTED TO " + host + ":" + inttostr(port) + "\n"; break;
      case 3: lasterr += "Try to CONNECT TO " + host + ":" + inttostr(port) + "\n"; break;
      case 6: lasterr += "CLOSED by rcvd 0 bytes (remote socket gracefully disconnected)\n"; break;
      }
sendlasterr();
}
//-----------------------------------------------------------------------------
void __fastcall TSipRecvTcpThread::CheckConnError(const string& proc_name)
{
int err = WSAGetLastError();
::closesocket(sck);
sck = INVALID_SOCKET;
lasterr.clear();
switch(conn_count){
      case 0:
      case 1:
            GetLastSocketError(lasterr, err, proc_name);
            sendlasterr();
            NextConnectTime_TCP = NextConnectTime_TCP.CurrentDateTime() + TDateTime(0,0,5,0);
            break;
      case 2:
            GetLastSocketError(lasterr, err, proc_name);
            lasterr += ".....";
            sendlasterr();
            NextConnectTime_TCP = NextConnectTime_TCP.CurrentDateTime() + TDateTime(0,0,5,0);
            break;
      default:
            GetLastSocketError(lasterr, err, proc_name, 1);
            sendlasterr();
            NextConnectTime_TCP = NextConnectTime_TCP.CurrentDateTime() + TDateTime(0,0,30,0);
            break;
      }
conn_count++;
}
//------------------------------------------------------------------------------

