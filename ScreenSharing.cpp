#include <vcl.h>
#pragma hdrstop

#include "WinRDefs.h"
#include "ScreenSharing.h"
#include "SipClient_Unit.h"

//------------------------------------------------------------------------------
void __fastcall TScreenSharing__CLIENT_SEND__Thread::Execute()
{
try{
while(!Terminated)
     {
     TOutBlock* ob = (TOutBlock*)getQueue();
     if(!ob)
       {
        //Suspend_Thread();
        ::Sleep(1);
        continue;
       }
     ScreenShConnectType ssct = sss->ssct;
     if((ssct == SSCT_OUT_LOCAL) || (ssct == SSCT_IN_LOCAL))
       {
       #ifdef SCREEN_Sharing_frame
       unsigned sz1 = partial.size();
       unsigned sz2 = ob->v.size();
       if(sz2)
         {
         partial.resize(sz1 + sz2);
         memcpy(&partial[sz1], &ob->v[0], sz2);
         }
       queue< vector<UBYTE> > dst;
       unframe_source(dst, partial);
       while(!dst.empty())
            {
            vector<UBYTE> v = dst.front();
            dst.pop();
            TOutBlock* opb = new TOutBlock(ExhangeType__notdef, 0, 0);
            if(opb)
              {
              opb->v = v;
              if(sendbuf(opb))
                {
                #ifdef ScreenSharing_Loc_OUT_Send_Log
                if(ssct == SSCT_OUT_LOCAL)
                   LOG_SharingPacket(get_socket(),out_sh_pckt,ssct,"SND_OUT_LOCAL",v,v.size());
                #endif   
                #ifdef ScreenSharing_Loc_IN_Send_Log
                if(ssct == SSCT_IN_LOCAL)
                   LOG_SharingPacket(get_socket(),out_sh_pckt,ssct,"SND_IN_LOCAL",v,v.size());
                #endif
                }
              delete opb;
              }
            }
       #else
       sendbuf(ob);
       #endif
       }
     else
       {
       if(sendbuf(ob))
         {
         #ifdef ScreenSharing_Rem_OUT_Send_Log
         if(ssct == SSCT_OUT_REMOTE)
            LOG_SharingPacket(get_socket(),out_sh_pckt,ssct,"SND_OUT_REMOTE",ob->v,ob->v.size());
         #endif
         #ifdef ScreenSharing_Rem_IN_Send_Log
         if(ssct == SSCT_IN_REMOTE)
            LOG_SharingPacket(get_socket(),out_sh_pckt,ssct,"SND_IN_REMOTE",ob->v,ob->v.size()); 
         #endif
         }
       }
     delete ob;
     }
}//try
catch(Exception& e){exsSstEXCEPTION(*eltp,"__TScreenSharing__CLIENT_SEND__Thread::Execute",e);}
}
//------------------------------------------------------------------------------
void __fastcall TScreenSharing__CLIENT_RECV__Thread::Execute()
{
if(sss->ssct == SSCT_IN_LOCAL)
  {
  slisten = exsCreateSrvTCPSocket_ADDR_ANY();
  if(slisten != INVALID_SOCKET)
    {
    TDBData dbd;;
    if(get_TCP_server_port(slisten, dbd.u_2))
      {
      if(::listen(slisten, SOMAXCONN)!= SOCKET_ERROR)
        {
        log_tcp_socket_action(slisten,5);        //"LISTEN"
        dbd.SDMT = (ServDbMsgType)3;
        MainFormSLS->ScreenSh.push(dbd);
        ::PostMessage(MainFormSLS->Handle, CONTROL_MSG, WM_APP_MSG_WPARAM__SCREEN_SHARING_IN_DATA, WM_APP_MSG_LPARAM__NOPARAM);

        SOCKADDR_IN acc_sin;   // Accept socket address - internet style
        int acc_sin_len;        // Accept socket address length
        acc_sin_len = sizeof(acc_sin);
        while(!Terminated)
             {
             SOCKET sAcpt = accept(slisten,(struct sockaddr FAR*)&acc_sin,(int FAR*)&acc_sin_len );
             if(sAcpt == INVALID_SOCKET)
               {
           //    int err = WSAGetLastError();
         // exsGetLastSocketError(lasterr,err);
          // sendlasterr();
          //return;
               }
             sck = sAcpt;
             log_tcp_socket_action(sck,4);     //"ACCEPTED"
             Receive();

             /*
             dbd.SDMT = (ServDbMsgType)4;
             MainFormSLS->ScreenSh.push(dbd);
             ::PostMessage(MainFormSLS->Handle, CONTROL_MSG, WM_APP_MSG_WPARAM__SCREEN_SHARING_IN_DATA, WM_APP_MSG_LPARAM__NOPARAM);
             */
             
             }
        }
      }
    }
  }
else
  {
  sck = exsCreateTCPSocket_ADDR_ANY();
  while(!Terminated)
       {
       if(!Connect())
          continue;
       if(sss->ssct == SSCT_OUT_REMOTE)
          sss->PrepareStart_OUT_ServerRequest();
       else if(sss->ssct == SSCT_IN_REMOTE)
          sss->PrepareStart_IN_ServerRequest(server_session_str);
       Receive();
       }
  }
}
//------------------------------------------------------------------------------
bool __fastcall TScreenSharing__CLIENT_RECV__Thread::Connect()
{
bool rv = false;
struct sockaddr_in dest;
memset(&dest,0,sizeof(dest));
dest.sin_family      = AF_INET;
dest.sin_addr.s_addr = inet_addr(host.c_str());
dest.sin_port        = htons(port);
while(!Terminated)
     {
     if(NextConnectTime.CurrentDateTime() < NextConnectTime)
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
       rv = false;
       SOCKET SCK = sck;
       CheckConnError();   //::closesocket(sck) and sck = INVALID_SOCKET  inside CheckConnError()
       if(SCK != INVALID_SOCKET)
         if(sck == INVALID_SOCKET) // SOCKET сlosed at this time (in the CheckConnError())
           log_tcp_socket_action(SCK,0);
       sck = exsCreateTCPSocket_ADDR_ANY();
       log_tcp_socket_action(sck,1);            //log CREATED socket
       continue;
       }
     conn_count = 0;
     log_tcp_socket_action(sck,2);              //log CONNECTED socket
     rv = true;
     break;
     }
return rv;
}
//------------------------------------------------------------------------------
void __fastcall TScreenSharing__CLIENT_RECV__Thread::Receive()
{
while(!Terminated)
     {
     vector<UBYTE> v(SCREEN_SH_TCP_MAX_PACKET,0);
     int bread = recv(sck,&v[0],SCREEN_SH_TCP_MAX_PACKET,0);
     if(!bread)              //Remote socket gracefully disconnected
       {
       SOCKET SCK = sck;
       ::closesocket(sck);
       sck = INVALID_SOCKET;
       log_tcp_socket_action(SCK,6);        //log closed socket
       break;               //Go to new circle of tcp connect
       }
     if(sss->block) //block before disconnect
       {
       ::Sleep(100);
       v.clear();
       continue;
       }
     if(bread == SOCKET_ERROR)
       {
       SOCKET SCK = sck;
       int err    = WSAGetLastError();
       ::closesocket(sck);
       sck = INVALID_SOCKET;
       lasterr.clear();
       GetLastSocketError(lasterr,err);
       sendlasterr();
       log_tcp_socket_action(SCK,0); //log closed socket
       break;                        //Go to new circle of tcp connect
       }
     if(sss->WaitResponce)
       {
       sss->WaitResponce = false;
       vector<UBYTE> V;
       copy(V, v, bread);
       parsing_responce(V);
       }
     else
       {
       if(opposite_sss){
         switch(sss->ssct){
              case SSCT_OUT_LOCAL: {
                                   TOutBlock* ob = new TOutBlock(ExhangeType__notdef, 0, 0);
                                   if(ob)
                                     {
                                     #ifdef SCREEN_Sharing_frame
                                     source_framing(ob->v,v,bread);
                                     #else
                                     ob->v.resize(bread);
                                     memcpy(&ob->v[0], &v[0], bread);
                                     #endif
                                     opposite_sss->SEND_REQUEST(ob);     //check if(ss_CS_T) inside this func
                                     #ifdef ScreenSharing_Loc_OUT_Rcv_Log
                                     LOG_SharingPacket(sck, in_sh_pckt, sss->ssct, "RCV_OUT_LOCAL", v, bread);
                                     #endif
                                     }
                                    break;
                                   }
              case SSCT_OUT_REMOTE: {
                                    TOutBlock* ob = new TOutBlock(ExhangeType__notdef, 0, 0);
                                    if(ob)
                                      {
                                      ob->v.resize(bread);
                                      memcpy(&ob->v[0], &v[0], bread);
                                      opposite_sss->SEND_REQUEST(ob);    //check if(ss_CS_T) inside this func
                                      #ifdef ScreenSharing_Rem_OUT_Rcv_Log
                                      LOG_SharingPacket(sck, in_sh_pckt, sss->ssct, "RCV_OUT_REMOTE", v, bread);
                                      #endif
                                      }
                                    break;
                                    }
              case SSCT_IN_LOCAL:   {
                                    TOutBlock* ob = new TOutBlock(ExhangeType__notdef, 0, 0);
                                    if(ob)
                                      {
                                      #ifdef SCREEN_Sharing_frame
                                      source_framing(ob->v,v,bread);
                                      #else
                                      ob->v.resize(bread);
                                      memcpy(&ob->v[0], &v[0], bread);
                                      #endif
                                      opposite_sss->SEND_REQUEST(ob);               //check if(ss_CS_T) inside this func
                                      #ifdef ScreenSharing_Loc_IN_Rcv_Log
                                      LOG_SharingPacket(sck, in_sh_pckt, sss->ssct, "RCV_IN_LOCAL", v, bread);
                                      #endif
                                      }
                                    break;
                                    }
              case SSCT_IN_REMOTE:  {
                                    TOutBlock* ob = new TOutBlock(ExhangeType__notdef, 0, 0);
                                    if(ob)
                                      {
                                      ob->v.resize(bread);
                                      memcpy(&ob->v[0], &v[0], bread);
                                      opposite_sss->SEND_REQUEST(ob);               //check if(ss_CS_T) inside this func
                                      #ifdef ScreenSharing_Rem_IN_Rcv_Log
                                      LOG_SharingPacket(sck, in_sh_pckt, sss->ssct, "RCV_IN_REMOTE", v, bread);
                                      #endif
                                      }
                                    break;
                                    }
             } //switch(sss->ssct)
          } //if(opposite_sss){
         }
     }
}
//------------------------------------------------------------------------------
void __fastcall TScreenSharing__CLIENT_RECV__Thread::source_framing(vector<UBYTE>& dst, const vector<UBYTE>& src, unsigned bread)
{
dst.push_back(0xFE);
unsigned i = 0;
while(i < bread)
     {
     if(src[i] == 0xFE)
       {
       dst.push_back(0xFD);
       dst.push_back(0x01);
       i++;
       continue;
       }
     else if(src[i] == 0xFD)
       {
       dst.push_back(0xFD);
       dst.push_back(0x02);
       i++;
       continue;
       }
     else
       dst.push_back(src[i]);
     i++;
     }
dst.push_back(0xFE);
}
//------------------------------------------------------------------------------
void __fastcall TScreenSharing__CLIENT_SEND__Thread::unframe_source(queue< vector<UBYTE> >& dst, vector<UBYTE>& src)
{
unsigned sz = src.size();
vector<UBYTE> v;
bool start = false;
unsigned start_pos = 0;
unsigned i = 0;
while(i < sz)
     {
     if(src[i] == 0xFE)
       {
       if(!start)
         {
         start = true;      //start of frame is found
         i++;
         start_pos = i;
         }
       else
         {
         start = false;     //end of frame is found
         i++;
         dst.push(v);     //save unframed packet
         v.clear();
         if(i == sz)
           {
           src.clear();
           break;          //весь анализируемый фрейм оканчивается 0xFE - выход
           }
         }
       continue;
       }

     if(src[i] == 0xFD)
       {
       i++;
       if(i < sz)
         {
         if(src[i] == 0x01)
           {
           v.push_back(0xFE);
           i++;
           continue;
           }
         if(src[i] == 0x02)
           {
           v.push_back(0xFD);
           i++;
           continue;
           }
         }   //if(i < sz)
       }  //if(src[i] == 0xFD)
     else
       {
       v.push_back(src[i]);
       i++;
       }

     if(i == sz)
       if(start_pos)     //стартовый 0xFE на не нулевой позиции
           if(start_pos < i) //сдвинуть влево и модифицировать длину
             {
             unsigned remind = i - start_pos;
             memcpy(&src[0], &src[start_pos], remind);
             src.resize(remind);
             break;
             }

     } //while
}
//------------------------------------------------------------------------------
void __fastcall TScreenSharing__CLIENT_RECV__Thread::LOG_RecvPacket(vector<UBYTE>& v)
{
TEventLogThread* elt = getLog();
if(elt)
  {
  int len = v.size();
  if(len > 0)
    {
    TDateTime dt = dt.CurrentDateTime();
    string str;
    exsDateTime(dt,str);
    str = "\n" + str + " Pckt Received From ScreenSharing Server Len " + inttostr(len) + "\n";
    for(int i=0;i < len;i++)
       {
       if(i)str += " ";
       str += inttohexstr(v[i],2);
       }
    str += "\n";
    elt->FputEvt(str);
    }
  }
}
//------------------------------------------------------------------------------
void __fastcall TScreenSharing__CLIENT_RECV__Thread::parsing_responce(vector<UBYTE>& v)
{
try{
LOG_RecvPacket(v);
if(check_prefix(v))
  {
  vector<UBYTE> frame;
  while(get_single_msg(frame,v))      //check if(v.size() < 10) inside
       {
       switch(frame[9]){
              case 1: get_ack(frame);break;
             }
       }
  }
}//try
catch(Exception& e){exsSstEXCEPTION(NULL,"__TScreenSharing__CLIENT_RECV__Thread::Execute",e);}
}
//------------------------------------------------------------------------------
void __fastcall TScreenSharing__CLIENT_RECV__Thread::get_ack(const vector<UBYTE>& v)
{
TServDBMsg sdbm;
int n = 3;
sdbm.seq_number     = v[n++] << 24;
sdbm.seq_number    |= v[n++] << 16;
sdbm.seq_number    |= v[n++] << 8;
sdbm.seq_number    |= v[n++];
unsigned  msg_type  = v[n++] << 8;
          msg_type |= v[n++];
sdbm.get_parameters(v);
switch((ServDbMsgType)msg_type){
       case 1: Proc_Ack__Connect_To_Server_OUT(sdbm);
               break;
       case 2: Proc_Ack__Connect_To_Server_IN(sdbm);
               break;
      }
}
//-----------------------------------------------------------------------------
void __fastcall TScreenSharing__CLIENT_RECV__Thread::get_ip_list()
{
unsigned n = 0;
string s;
while(get_single_ip(n,s))
      ip_list.push_back(s);
}
//-----------------------------------------------------------------------------
bool __fastcall TScreenSharing__CLIENT_RECV__Thread::get_single_ip(unsigned& n, string& s)
{
bool rv = false;
int st = sharing_str.find("<L",n);
if(st != -1)
  {
  int en = sharing_str.find("/>",st);
  st += 2;
  if(st < en)
    {
    s  = sharing_str.substr(st,en-st);
    n  = en;
    rv = true;
    }
  }
return rv;
}
//------------------------------------------------------------------------------
void __fastcall TScreenSharing__CLIENT_RECV__Thread::modify_sharing_string_OUT()
{
string s1,s2;
int len = sharing_str.length();
int st = sharing_str.find("<T");
if(st != -1)
  {
  st = sharing_str.find(">",st);
  if(st != -1)
    {
    st++;
    if(st < len)
      {
      s1 = sharing_str.substr(0,st);
      int en = sharing_str.find("</T>",st);
      if(en != -1)
        {
        s2 = sharing_str.substr(en);
        sharing_str = s1 + "<L" + WS + "P=\"" + inttostr(MainFormSLS->Sip->ScreenSharing.Port) + "\"" + WS + "N=\"" + MainFormSLS->Sip->ScreenSharing.IPAddr + "\"" + "/>" + s2;
        }
      }
    }
  }
}
//------------------------------------------------------------------------------
void __fastcall TScreenSharing__CLIENT_RECV__Thread::modify_sharing_string_IN()
{
}
//------------------------------------------------------------------------------
void __fastcall TScreenSharing__CLIENT_RECV__Thread::get_sharing_string(const string& s)
{
int st  = s.find(crlf);
if(st != -1)
  {
  st += 2;
  sharing_str =  s.substr(0,st);
  }
}
//------------------------------------------------------------------------------
void __fastcall TScreenSharing__CLIENT_RECV__Thread::get_server_session_str(const string& s)
{
int len = s.length();
int st  = s.rfind("<E1>");
if(st != -1)
  {
  st += 4;
  if(st < len)
    {
    int en = s.find("</E1>",st);
    if(st < en)
       server_session_str = s.substr(st,en-st);
    }
  }
}
//------------------------------------------------------------------------------
void __fastcall TScreenSharing__CLIENT_RECV__Thread::Proc_Ack__Connect_To_Server_OUT(TServDBMsg& sdbm)
{
TDBData dbd;
if(sdbm.status == 0x10)
  {
  while(!sdbm.q.empty())
       {
       TServDBPar sdbp = sdbm.q.front();
       sdbm.q.pop();
       switch(sdbp.prm_type){
              case 1:if(sdbp.idt == IapDataType_Int4)
                      {
                      dbd.u_1 = sdbp.u; //conn id on server
                      dbd.u_2 = tag;
                      dbd.u_3 = conf;  // in case: WM_APP_MSG_WPARAM__SCREEN_SHARING_OUT_DATA check first dbd.u_3(conf) then dbd.u_2(tag)
                      dbd.s_1 = sharing_str;
                      dbd.s_2 = sss_nick_name;
                      }
                    break;
             }
       }
  dbd.SDMT = (ServDbMsgType)1;
  MainFormSLS->ScreenSh.push(dbd);
::PostMessage(MainFormSLS->Handle, CONTROL_MSG, WM_APP_MSG_WPARAM__SCREEN_SHARING_OUT_DATA, WM_APP_MSG_LPARAM__NOPARAM);
  }
}
//-----------------------------------------------------------------------------
void __fastcall TScreenSharing__CLIENT_RECV__Thread::Proc_Ack__Connect_To_Server_IN(TServDBMsg& sdbm)
{
TDBData dbd;
dbd.SDMT = (ServDbMsgType)2;
MainFormSLS->ScreenSh.push(dbd);
::PostMessage(MainFormSLS->Handle, CONTROL_MSG, WM_APP_MSG_WPARAM__SCREEN_SHARING_IN_DATA, WM_APP_MSG_LPARAM__NOPARAM);
}
//-----------------------------------------------------------------------------
bool __fastcall TScreenSharing__CLIENT_RECV__Thread::check_prefix(vector<UBYTE>& v)
{
bool rv = false;
if(!v.empty())
  {
  if(v[0] == DATABASE_NET_PREF)
    rv = true;
  else
    {
    int sz = v.size();
    for(int i=0;i<sz;i++)
       {
       if(v[i] == DATABASE_NET_PREF)
         {
         int part_sz = sz - i;
         memcpy(&v[0],&v[i],part_sz);
         v.resize(part_sz);
         rv = true;
         break;
         }
       }
    }
  }
return rv;
}
//-----------------------------------------------------------------------------
bool __fastcall TScreenSharing__CLIENT_RECV__Thread::get_single_msg(vector<UBYTE>& frame, vector<UBYTE>& v)
{
bool rv = false;
if(v.size() < 10)  //!!!!
  BUF = v;    //save incomplete msg and wait for a new packet
else
  rv = get_frame(frame,v);
return rv;
}
//-----------------------------------------------------------------------------
bool __fastcall TScreenSharing__CLIENT_RECV__Thread::get_frame(vector<UBYTE>& frame, vector<UBYTE>& v)
{
bool rv = false;
unsigned len = (v[1] << 8) & 0xFF00;
len |= v[2];
len += 3;  //0xFE + Length_MSB + Length_LSB
unsigned total_length = v.size();
if(total_length < len)
   BUF = v;  //save incomplete msg and wait for a new packet
else
   {
   frame.resize(len);
   memcpy(&frame[0],&v[0],len);
   if(len == total_length)
     v.clear();
   else if(len < total_length)
     {
     memcpy(&v[0],&v[len],total_length - len);
     v.resize(total_length - len);
     }
   rv = true;
   }
return rv;
}
//-----------------------------------------------------------------------------
void __fastcall TScreenSharing__CLIENT_RECV__Thread::copy(vector<UBYTE>& dst, vector<UBYTE>& src, int sz_2)
{
int sz_1 = BUF.size();
int sz   = sz_1 + sz_2;
dst.resize(sz);
if(sz_1)
   memcpy(&dst[0], &BUF[0], sz_1);
memcpy(&dst[sz_1],&src[0],sz_2);
BUF.clear();
}
//-----------------------------------------------------------------------------
void __fastcall TScreenSharing__CLIENT_RECV__Thread::CheckConnError()
{
int err = WSAGetLastError();
::closesocket(sck);
sck = INVALID_SOCKET;
lasterr.clear();
switch(conn_count){
      case 0:
      case 1:
            GetLastSocketError(lasterr,err);
            sendlasterr();
            NextConnectTime = NextConnectTime.CurrentDateTime() + TDateTime(0,0,5,0);
            break;
      case 2:
            GetLastSocketError(lasterr,err);
            lasterr += ".....";
            sendlasterr();
            NextConnectTime = NextConnectTime.CurrentDateTime() + TDateTime(0,0,5,0);
            break;
      default:
            NextConnectTime = NextConnectTime.CurrentDateTime() + TDateTime(0,0,30,0);
            break;
      }
conn_count++;
}
//------------------------------------------------------------------------------
void __fastcall TScreenSharing__CLIENT_RECV__Thread::log_tcp_socket_action(SOCKET socket, int type)
{
lasterr.clear();
TDateTime dt = dt.CurrentDateTime();
exsTime(dt,lasterr);
lasterr = "\n" + lasterr + " SCREEN SHARING TCP SOCKET " + inttostr(socket) + WS;
switch(type){
      case 0: lasterr += "CLOSED\n";   break;
      case 1: lasterr += "CREATED\n";  break;
      case 2: lasterr += "CONNECTED TO " + host + ":" + inttostr(port) + "\n";      break;
      case 3: lasterr += "Try to CONNECT TO " + host + ":" + inttostr(port) + "\n"; break;
      case 4: lasterr += "ACCEPTED\n"; break;
      case 5: lasterr += "LISTEN\n";   break;
      case 6: lasterr += "CLOSED by rcvd 0 bytes (remote socket gracefully disconnected)\n";   break;
      }
sendlasterr();
}
//-----------------------------------------------------------------------------
bool __fastcall TScreenSharing__CLIENT_SEND__Thread::sendbuf(TOutBlock* ob)
{
bool rv = false;
int len = ob->v.size();
if(len)
   rv = send_tcp(&ob->v[0],len);
return rv;
}
//------------------------------------------------------------------------------
bool __fastcall TScreenSharing__CLIENT_SEND__Thread::send_tcp(const char* buf, int len)
{
bool rv = false;
::EnterCriticalSection(&sss->tcp);
  if(sss->ss_CR_T)
    {
    SOCKET SCK = sss->ss_CR_T->get_sck();
    if(SCK != INVALID_SOCKET)
      {
       if(send(SCK, buf, len, 0) == SOCKET_ERROR)
         {
         int err = WSAGetLastError();
         lasterr.clear();
         GetLastSocketError(lasterr,err);
         sendlasterr();
         }
       else
         rv = true;
      }
    }
::LeaveCriticalSection(&sss->tcp);
return rv;
}
//------------------------------------------------------------------------------
//-- Used only for log goals ---------------------------------------------------
//------------------------------------------------------------------------------
SOCKET __fastcall TScreenSharing__CLIENT_SEND__Thread::get_socket()
{
SOCKET SCK = INVALID_SOCKET;
::EnterCriticalSection(&sss->tcp);
  if(sss->ss_CR_T)
     SCK = sss->ss_CR_T->get_sck();
::LeaveCriticalSection(&sss->tcp);
return SCK;
}
//------------------------------------------------------------------------------
__fastcall TScreenSharingStruct::~TScreenSharingStruct(){
::EnterCriticalSection(&tcp);
  block = true;
  TScreenSharing__CLIENT_SEND__Thread* SSCST = ss_CS_T;
  if(SSCST){
    ss_CS_T = NULL;
    SSCST->Terminate();
    SSCST->Resume();
    SSCST->WaitFor();
    delete SSCST;
    }
  TScreenSharing__CLIENT_RECV__Thread* SSCRT = ss_CR_T;
  if(SSCRT){
    ss_CR_T = NULL;
    SSCRT->Terminate();
    SSCRT->CloseSocket();
    SSCRT->Resume();
    SSCRT->WaitFor();
    delete SSCRT;
    }
::LeaveCriticalSection(&tcp);
::DeleteCriticalSection(&tcp);  
}
//------------------------------------------------------------------------------
void _fastcall TScreenSharing__CLIENT_RECV__Thread::CloseSocket()
{
if(slisten != INVALID_SOCKET)
  {
  closesocket(slisten);
  slisten = INVALID_SOCKET;
  }
if(sck != INVALID_SOCKET)
  {
  closesocket(sck);
  sck = INVALID_SOCKET;
  }
}
//------------------------------------------------------------------------------
void __fastcall TScreenSharingStruct::SEND_REQUEST(TOutBlock* ob)
{
::EnterCriticalSection(&tcp);
  if(ss_CS_T)
     ss_CS_T->setQueue_not_suspended(ob);
  else
     delete ob;
::LeaveCriticalSection(&tcp);
}
//-----------------------------------------------------------------------------
void __fastcall TScreenSharingStruct::PrepareStart_OUT_ServerRequest()
{
TOutBlock* ob = new TOutBlock(ExhangeType__req, 1, ++send_seq_number);
if(ob)
  {
  ob->pack_header_REQ();
  SEND_REQUEST(ob);     //check if(ss_CS_T) inside this func
  }
}
//-----------------------------------------------------------------------------
void __fastcall TScreenSharingStruct::PrepareStart_IN_ServerRequest(const string& s)
{
if(!s.empty())
  {
  TOutBlock* ob = new TOutBlock(ExhangeType__req, 2, ++send_seq_number);
  if(ob)
    {
    unsigned a = strtoint(s);
    ob->pack_fixed_type(1, IapDataType_Int4, a);
    ob->pack_header_REQ();
    SEND_REQUEST(ob);     //check if(ss_CS_T) inside this func
    }
  }
}
//-----------------------------------------------------------------------------
bool __fastcall TScreenSharingStruct::get_local_out_addr(TIPAddress& addr)
{
bool rv = false;
::EnterCriticalSection(&tcp);
 if(ss_CR_T)
   {
   if(!ss_CR_T->ip_list.empty())
     {
     vector<string>::iterator it = ss_CR_T->ip_list.begin();
     while(it != ss_CR_T->ip_list.end())
          {
          string s = (*it++);
          if(s.find(".") != -1)
            {
            int len = s.length();
            int st = s.find("P=\"");
            if(st != -1)
              {
              st += 3;
              if(st < len)
                {
                int en = s.find("\"",st);
                if(st < en)
                  {
                  addr.Port = strtoint(s.substr(st,en-st));
                  st = s.find("N=\"",en);
                  if(st != -1)
                    {
                    st += 3;
                    if(st < len)
                      {
                      en = s.find("\"",st);
                      if(st < en)
                        {
                        addr.IPAddr = s.substr(st,en-st);
                        rv = true;
                        break;
                        }
                      }
                    }
                  }
                }
              }
            }
          }
     }
   }
::LeaveCriticalSection(&tcp);
return rv;
}
//------------------------------------------------------------------------------
void __fastcall TScreenSharingStruct::modify_local_addr_for_rdp_connect(TIPAddress& addr, string& s)
{
::EnterCriticalSection(&tcp);
  if(ss_CR_T)
    if(!ss_CR_T->sharing_str.empty())
      {
      string s1,s2,s3;
      int len = ss_CR_T->sharing_str.length();
      int st  = ss_CR_T->sharing_str.find("P=\"");
      if(st != -1)
        {
        st += 3;
        if(st < len)
          {
          s1 = ss_CR_T->sharing_str.substr(0,st);
          st = ss_CR_T->sharing_str.find("\"",st);
          if(st != -1)
            {
            s2  = ss_CR_T->sharing_str.substr(st);
            len = s2.length();
            st = s2.find("N=\"");
            if(st != -1)
              {
              st += 3;
              if(st < len)
                {
                int en = s2.find("\"",st);
                if(en != -1)
                  {
                  s3 = s2.substr(en);
                  s2.resize(st);
                  ss_CR_T->sharing_str = s1 + inttostr(addr.Port) + s2 + addr.IPAddr + s3;
                  s = ss_CR_T->sharing_str;
                  }
                }
              }
            }
          }
        }
      }
::LeaveCriticalSection(&tcp);
}
//-----------------------------------------------------------------------------
string __fastcall TScreenSharingStruct::get_sharing_string()
{
string s;
::EnterCriticalSection(&tcp);
  if(ss_CR_T)
     s = ss_CR_T->sharing_str;
::LeaveCriticalSection(&tcp);
return s;
}
//-----------------------------------------------------------------------------
void __fastcall TBaseThread::LOG_SharingPacket(SOCKET sck, unsigned& sharing_pckt, int ssct, const string& S,const vector<UBYTE>& v, int bread)
{
TEventLogThread* elt = getLog();
if(elt)
  {
  ScreenShConnectType SSCT = (ScreenShConnectType)ssct;
  string str;
  TDateTime dt = dt.CurrentDateTime();
  exsTime(dt,str);
  str = "\n" + str + " sck " + inttostr(sck) + " Len " + inttostr(bread) + " ";
  TDateTime difftime = dt - PrevPacketTime;
  PrevPacketTime     = dt;
  unsigned short hour;
  unsigned short min;
  unsigned short sec;
  unsigned short msec;
  difftime.DecodeTime(&hour,&min,&sec,&msec);
  str += "dt = " + inttostr(hour) + "." + inttostr(min) + "." + inttostr(sec) + "." + inttostr(msec) + " pckt " + inttostr(++sharing_pckt) + WS + S;
  if((SSCT == SSCT_OUT_LOCAL) || (SSCT == SSCT_IN_LOCAL))
    {
    string data;
    unsigned ks = 0;
    for(int i=0;i < bread;i++)
       {
       ks += v[i];
       if(i)
         data += " ";
       data += inttohexstr(v[i],2);
       }
    str += WS + "ks = " + inttostr(ks) + "\n";
    str += data;
    }
  else if((SSCT == SSCT_OUT_REMOTE) || (SSCT == SSCT_IN_REMOTE))
    {
    string data;
    for(int i=0;i < bread;i++)
       {
       if(i)
         data += " ";
       data += inttohexstr(v[i],2);
       }
    str += "\n";
    str += data;
    }
  str += "\n";
  elt->FputEvt(str);
 }
}
//------------------------------------------------------------------------------



