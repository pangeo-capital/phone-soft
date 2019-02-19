#include <vcl.h>
#pragma hdrstop


#include "WinRDefs.h"
#include "SipClient_Unit.h"
#include "utils.h"
#include "udp.h"
#include "sound.h"
#include "outputsipbuf.h"
#include "G711.h"
#include "md5.h"
#include "process.h"
#include "FileCtrl.hpp"
#include <stdlib.h>

#define MD_CTX MD5_CTX
#define MDInit MD5Init
#define MDUpdate MD5Update
#define MDFinal MD5Final

const char ws_char = ' ';
const char SST_DotChar = '.';
const string emptystr = "";
//-----------------------------------------------------------------------------
/*
std::wstring s2ws(const std::string& s)
{

string orig = "123";
 int sz = strlen(s.c_str());

    // newsize describes the length of the
    // wchar_t string called wcstring in terms of the number
    // of wide characters, not the number of bytes.
    size_t newsize = sz + 1;
     size_t convertedChars = 0;
    mbstowcs_s(&convertedChars, wcstring, newsize, orig, _TRUNCATE);


  //  string ss = "ќткрыть";

/*
    int len;
    int slength = (int)ss.length() + 1;
    len = MultiByteToWideChar(CP_ACP, 0, ss.c_str(), slength, 0, 0);
    std::wstring r(len, L'\0');
    MultiByteToWideChar(CP_ACP, 0, ss.c_str(), slength, &r[0], len);
    return r;
 */

      /*
    int len;
    int slength = (int)s.length() + 1;
    len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
    wchar_t* buf = new wchar_t[len];
    MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
    std::wstring r(buf);
    delete[] buf;
    return r;
   
}
 */

//----------------------------------------------------------------------------
std::string ws2s(const std::wstring& s)
{
    int len;
    int slength = (int)s.length() + 1;
    len = WideCharToMultiByte(CP_ACP, 0, s.c_str(), slength, 0, 0, 0, 0);
    std::string r(len, '\0');
    WideCharToMultiByte(CP_ACP, 0, s.c_str(), slength, &r[0], len, 0, 0);
    return r;
}
//----------------------------------------------------------------------------
string __fastcall uint_to_str(unsigned a)
{
char str[25];
return string(ultoa(a,str,10));
}
//----------------------------------------------------------------------------
string  __fastcall inttostr(int a)
{
char str[25];
return string(itoa(a,str,10));
}
//-----------------------------------------------------------------------------
string  __fastcall inttohexstr(int a)
{
char str[25];
return string(itoa(a,str,16));
}
//----------------------------------------------------------------------------
/*
wstring __fastcall inttowstr(int a)
{
string s = inttostr(a);
//wstring wstr(s.begin(), s.end());
return s2ws(s);
}
*/
//--------------------------------------------------------------------
string  __fastcall inttohexstr(int a,int len)
{
char str[25];
string s = string(itoa(a,str,16));
int length = s.length();
if(len > length)
  {
  int dif = len - length;
  for(int i=0;i < dif;i++)
      s = "0" + s;
  }
return s;
}
//----------------------------------------------------------------------------
/*
wstring  __fastcall inttowhexstr(int a,int len)
{
string s = inttohexstr(a,len);
//wstring wstr(s.begin(), s.end());
return s2ws(s);
}
*/
//----------------------------------------------------------------------------
int __fastcall strtoint(const string& s)
{
return atoi(s.c_str());
}
//-----------------------------------------------------------------------------
UBYTE __fastcall hex_str_to_int(const string& s,int i)
{
switch (s[i]){
       case '0': return 0;
       case '1': return 1;
       case '2': return 2;
       case '3': return 3;
       case '4': return 4;
       case '5': return 5;
       case '6': return 6;
       case '7': return 7;
       case '8': return 8;
       case '9': return 9;
       case 'a': return 10;
       case 'b': return 11;
       case 'c': return 12;
       case 'd': return 13;
       case 'e': return 14;
       case 'f': return 15;
       case 'A': return 10;
       case 'B': return 11;
       case 'C': return 12;
       case 'D': return 13;
       case 'E': return 14;
       case 'F': return 15;
       }
return 0;
}
//-----------------------------------------------------------------------------
string __fastcall bigendian_to_dot_str(unsigned a)
{
unsigned char* b = (unsigned char*)&a;
string s;
for(int i=0;i<4;i++)
   {
   if(i)
      s+=".";
   s+=inttostr(b[i]);
   }
return s;
}
//-----------------------------------------------------------------------------
string __fastcall littleendian_to_dot_str(unsigned a)
{
string s = inttostr((a>>24)&0xFF)+ "." +
           inttostr((a>>16)&0xFF)+ "." +
           inttostr((a>>8)&0xFF) + "." +
           inttostr(a & 0xFF);
return s;           
}
//-----------------------------------------------------------------------------
void __fastcall exsTime(TDateTime& dt,string& str)
{
unsigned short hour;
unsigned short min;
unsigned short sec;
unsigned short msec;
dt.DecodeTime(&hour,&min,&sec,&msec);
char buf[25];
if(hour<10)
  str+="0"+string(itoa(hour,buf,10))+":";
else
  str+=string(itoa(hour,buf,10))+":";
if(min<10)
  str+="0"+string(itoa(min,buf,10))+":";
else
  str+=string(itoa(min,buf,10))+":";
if(sec<10)
  str+="0"+string(itoa(sec,buf,10))+".";
else
  str += string(itoa(sec,buf,10))+".";
if(msec < 100)
   str += "0";
if(msec < 10)
   str += "0";
str += string(itoa(msec,buf,10));
}
//----------------------------------------------------------------------------
void __fastcall exsDateTime(TDateTime& dt,string& str)
{
unsigned short year;
unsigned short month;
unsigned short day;
dt.DecodeDate(&year,&month,&day);
unsigned short hour;
unsigned short min;
unsigned short sec;
unsigned short msec;
dt.DecodeTime(&hour,&min,&sec,&msec);
char buf[25];
if(day<10)
  str = "0"+string(itoa(day,buf,10))+"-";
else
  str = string(itoa(day,buf,10))+"-";
if(month<10)
  str+="0"+string(itoa(month,buf,10));
else
  str+= string(itoa(month,buf,10));
str+= "-"+string(itoa(year,buf,10))+" ";
if(hour<10)
  str+="0"+string(itoa(hour,buf,10))+":";
else
  str+=string(itoa(hour,buf,10))+":";
if(min<10)
  str+="0"+string(itoa(min,buf,10))+":";
else
  str+=string(itoa(min,buf,10))+":";
if(sec<10)
  str+="0"+string(itoa(sec,buf,10))+".";
else
  str+=string(itoa(sec,buf,10))+".";
str+=string(itoa(msec,buf,10));
}
//----------------------------------------------------------------------------
void __fastcall exsDateTime_FileName(TDateTime& dt,string& str)
{
unsigned short year;
unsigned short month;
unsigned short day;
dt.DecodeDate(&year,&month,&day);
unsigned short hour;
unsigned short min;
unsigned short sec;
unsigned short msec;
dt.DecodeTime(&hour,&min,&sec,&msec);
char buf[25];

str = string(itoa(year,buf,10));
if(month<10)
  str+="0"+string(itoa(month,buf,10));
else
  str+= string(itoa(month,buf,10));
if(day<10)
  str += "0"+string(itoa(day,buf,10));
else
  str += string(itoa(day,buf,10));
str+="_";

if(hour<10)
  str+="0"+string(itoa(hour,buf,10));
else
  str+=string(itoa(hour,buf,10));
if(min<10)
  str+="0"+string(itoa(min,buf,10));
else
  str+=string(itoa(min,buf,10));
if(sec<10)
  str+="0"+string(itoa(sec,buf,10));
else
  str+=string(itoa(sec,buf,10));
str+="_";
str+=string(itoa(msec,buf,10));
}
//----------------------------------------------------------------------------
int __fastcall exsWSAStartUp(TEventLogThread* elt)
{
WORD wVersionRequested;
WSADATA wsaData;
int err;
wVersionRequested = MAKEWORD( 2, 2 );
err = WSAStartup( wVersionRequested, &wsaData );
if ( err != 0 ) {
    if(elt)
      {
   /* Tell the user that we could not find a usable */
   /* WinSock DLL.                                  */
      }
   return 1;
   }
if(elt)
 if(elt->getlog())
   {
   string TimeStr;
   TDateTime DateTime = DateTime.CurrentDateTime();
   exsDateTime(DateTime,TimeStr);
   string str = "\n" + (string)TimeStr + " WSAStartup() " + wsaData.szDescription + " Version " +
   inttostr(wsaData.wVersion >> 8) + "." + inttostr(wsaData.wVersion & 0xFF);
   elt->FputEvt(str);
   }
return 0;
}
//----------------------------------------------------------------------------
SOCKET __fastcall exsCreateUDPSocket(const string& LocalIP,int LocalPort)
{
SOCKET sck;
struct sockaddr_in local;
memset(&local,0,sizeof(local));
local.sin_addr.s_addr = inet_addr(LocalIP.c_str());
local.sin_family = AF_INET;
local.sin_port = htons(LocalPort);
sck = socket(AF_INET,SOCK_DGRAM,IPPROTO_IP);
if(sck == INVALID_SOCKET)
  return sck;
if(bind(sck,(struct sockaddr*)&local,sizeof(local))==SOCKET_ERROR)
  {
  closesocket(sck);
  sck = INVALID_SOCKET;
  }
return sck;
}
//----------------------------------------------------------------------------
SOCKET __fastcall exsCreateUDPSocket_ADDR_ANY(UINT Port)
{
SOCKET sck;
struct sockaddr_in local;
memset(&local,0,sizeof(local));
local.sin_addr.s_addr = ADDR_ANY;
local.sin_family = AF_INET;
local.sin_port = htons(Port);
sck = socket(AF_INET,SOCK_DGRAM,IPPROTO_IP);
if(sck == INVALID_SOCKET)
  return sck;
if(bind(sck,(struct sockaddr*)&local,sizeof(local))==SOCKET_ERROR)
  {
  closesocket(sck);
  sck = INVALID_SOCKET;
  }
return sck;
}

//-----------------------------------------------------------------------------
SOCKET __fastcall exsCreateUDPSocket_ADDR_PORT_ANY()
{
SOCKET sck;
struct sockaddr_in local;
memset(&local,0,sizeof(local));
local.sin_addr.s_addr = ADDR_ANY;
local.sin_family = AF_INET;
local.sin_port = htons(0);
sck = socket(AF_INET,SOCK_DGRAM,IPPROTO_IP);
if(sck == INVALID_SOCKET)
  return sck;
if(bind(sck,(struct sockaddr*)&local,sizeof(local))==SOCKET_ERROR)
  {
  closesocket(sck);
  sck = INVALID_SOCKET;
  }
return sck;
}

//-----------------------------------------------------------------------------
SOCKET __fastcall exsCreateTCPSocket_ADDR_ANY()
{
struct sockaddr_in local;
memset(&local,0,sizeof(local));
local.sin_addr.s_addr = ADDR_ANY;
local.sin_family      = AF_INET;
local.sin_port        = htons(0);
return socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
}
//-----------------------------------------------------------------------------
SOCKET __fastcall exsCreateSrvTCPSocket_ADDR_ANY()
{
SOCKET sck = INVALID_SOCKET;
struct sockaddr_in local;
memset(&local,0,sizeof(local));
string localAddrErrStr;
local.sin_addr.s_addr = ADDR_ANY;
local.sin_family      = AF_INET;
local.sin_port        = htons(0);
sck = ::socket(AF_INET,SOCK_STREAM,IPPROTO_IP);
if(sck != INVALID_SOCKET)
  if(::bind(sck,(struct sockaddr*)&local,sizeof(local))!= 0)
    {
     closesocket(sck);
     sck = INVALID_SOCKET;
    }
return sck;
}
//-----------------------------------------------------------------------------
//-- Used with exsCreateSrvTCPSocket_ADDR_ANY() --------------------------------
//------------------------------------------------------------------------------
bool __fastcall get_TCP_server_port(SOCKET sck, unsigned& LocalPort)
{
bool rv = false;
sockaddr name;
memset(&name,0,sizeof(name));
int namelen = sizeof(name);
if(getsockname(sck, &name, &namelen)!= SOCKET_ERROR)
  {
    int n = 0;
    string LocalAddr;
    UBYTE* buf = (UBYTE*)name.sa_data; //!!!!!Protection from expansion of the sign bit to the left. Otherwise we have to shall every time produce mask of values with constants 0xFF00 and 0xFF
    LocalPort |= buf[n++] << 8;
    LocalPort |= buf[n++];
    rv = true;
  }
return rv;
}
//------------------------------------------------------------------------------
SOCKET __fastcall exsCreateTCPSocket(TMfswIpAddrStruct* sa)
{
/* if((sa->LocalPort!=0)&&(sa->LocalPort!=-1)) LocalAddr and LocalPort will be selected       */
/* from  TMfswIpAddrStruct* sa and socket will be binding to this values                      */
/*                                                                                            */
/* if((sa->LocalPort==-1) LocalAddr and LocalPort will be selected by Operation System        */
/* (we not use function bind())                                                               */
/*                                                                                            */
/* if((sa->LocalPort==0) LocalAddr will be selected from  TMfswIpAddrStruct* sa and LocalPort */
/* will be selected by Operation System */
SOCKET sck;
struct sockaddr_in local;
memset(&local,0,sizeof(local));
local.sin_addr.s_addr = inet_addr(sa->LocalAddr.c_str());
local.sin_family = AF_INET;
local.sin_port = htons(sa->LocalPort);
sck = socket(AF_INET,SOCK_STREAM,IPPROTO_IP);
if(sck == INVALID_SOCKET)
  return sck;
if(sa->LocalPort!=-1)
   bind(sck,(struct sockaddr*)&local,sizeof(local));
return sck;
}
//-----------------------------------------------------------------------------
void __fastcall GetLastSocketError(string& es, int errcode, int short_note)
{
string TimeStr;
TDateTime DateTime = DateTime.CurrentDateTime();
exsTime(DateTime,TimeStr);
es = "\n" + (string)TimeStr + " ERROR: "+ es + " ";
resolve_error_code(es, errcode, short_note);
}
//------------------------------------------------------------------------------
void __fastcall GetLastSocketError(string& es, int errcode, const string& ThreadName, int short_note)
{
string TimeStr;
TDateTime DateTime = DateTime.CurrentDateTime();
exsTime(DateTime,TimeStr);
es = "\n" + (string)TimeStr + WS + ThreadName + WS + "ERROR:" + WS + es + " ";
resolve_error_code(es, errcode, short_note); 
}
//------------------------------------------------------------------------------
void __fastcall resolve_error_code(string& es, int errcode, int short_note)
{
switch(errcode){
case WSANOTINITIALISED:
     es += "WSANOTINITIALISED: A successful WSAStartup must occur before using this function.";
     break;
case WSAENETDOWN:
     es += "WSAENETDOWN: The network subsystem or the associated service provider has failed.";
     break;
case WSAEAFNOSUPPORT:
     es += "WSAEAFNOSUPPORT: The specified address family is not supported.";
     break;
case WSAEINPROGRESS:
     es += "WSAEINPROGRESS: A blocking Windows Sockets 1.1 call is in progress, or the service provider is still processing a callback function.";
     break;
case WSAEMFILE:
     es += "WSAEMFILE: No more socket descriptors are available.";
     break;
case WSAENOBUFS:
     es += "WSAENOBUFS: No buffer space is available.";
     break;
case WSAEPROTONOSUPPORT:
     es += "WSAEPROTONOSUPPORT: The specified protocol is not supported.";
     break;
case WSAEPROTOTYPE:
     es += "WSAEPROTOTYPE: The specified protocol is the wrong type for this socket.";
     break;
case WSAESOCKTNOSUPPORT:
     es += "WSAESOCKTNOSUPPORT: The specified socket type is not supported in this address family.";
     break;
case WSAEFAULT:
     es += "WSAEFAULT:	The name or the namelen argument is not a valid part of the user address space, or the namelen argument is too small.";
     break;
case WSAENOTSOCK:
     es += "WSAENOTSOCK: The descriptor is not a socket.";
     break;
case WSAEINVAL:
     es += "WSAEINVAL: The socket has not been bound to an address with bind, or ADDR_ANY is specified in bind but connection has not yet occurs.";
     break;
case WSAENOPROTOOPT:
     es += "WSAENOPROTOOPT: The option is unknown or unsupported by the indicated protocol family.";
     break;
case WSAEADDRINUSE:
     es += "WSAEADDRINUSE: The specified address is already in use. (See the SO_REUSEADDR socket option under setsockopt.)";
     break;
case WSAEACCES:
     es += "WSAEACCES: The requested address is a broadcast address, but the appropriate flag was not set.";
     break;
case WSAEINTR:
     es += "WSAEINTR: The (blocking) call was canceled through WSACancelBlockingCall.";
     break;
case WSAENETRESET:
     es += "WSAENETRESET: The connection has been broken due to the remote host resetting.";
     break;
case WSAENOTCONN:
     es += "WSAENOTCONN: The socket is not connected (connection-oriented sockets only).";
     break;
case WSAEOPNOTSUPP:
     es += "WSAEOPNOTSUPP: MSG_OOB was specified, but the socket is not stream style such as type SOCK_STREAM, out-of-band data is not supported in the communication domain associated with this socket, or the socket is unidirectional and supports only receive operations.";
     break;
case WSAESHUTDOWN:
     es += "WSAESHUTDOWN: The socket has been shut down; it is not possible to sendto on a socket after shutdown has been invoked with how set to SD_SEND or SD_BOTH.";
     break;
case WSAEWOULDBLOCK:
     es += "WSAEWOULDBLOCK: The socket is marked as nonblocking and the requested operation would block.";
     break;
case WSAEMSGSIZE:
     es += "WSAEMSGSIZE: The socket is message oriented, and the message is larger than the maximum supported by the underlying transport.";
     break;
case WSAEHOSTUNREACH:
     if(short_note == 1)
        es += "WSAEHOSTUNREACH";
     else
        es += "WSAEHOSTUNREACH: The remote host cannot be reached from this host at this time.";
     break;
case WSAECONNABORTED:
     es += "WSAECONNABORTED: The virtual circuit was terminated due to a time-out or other failure. The application should close the socket as it is no longer usable.";
     break;
case WSAECONNRESET:
     if(short_note == 1)
        es += "WSAECONNRESET";
     else
        es += "WSAECONNRESET: The virtual circuit was reset by the remote side executing a " + (string)"\"" + "hard" "\"" + "or" + "\"" + "abortive" + "\"" +
            "close. For UPD sockets, the remote host was unable to deliver a previously sent UDP datagram and responded with a " + "\"" +
            "Port Unreachable" + "\"" + "ICMP packet. The application should close the socket as it is no longer usable.";
     break;
case WSAEADDRNOTAVAIL:
     es += "WSAEADDRNOTAVAIL: The specified address is not available from the local machine.";
     break;
case WSAEDESTADDRREQ:
     es += "WSAEDESTADDRREQ: A destination address is required.";
     break;
case WSAENETUNREACH:
     if(short_note == 1)
        es += "WSAENETUNREACH";
     else
        es += "WSAENETUNREACH: The network cannot be reached from this host at this time.";
     break;
case WSAETIMEDOUT:
     if(short_note == 1)
       es += "WSAETIMEDOUT";
     else
       es += "WSAETIMEDOUT: The connection has been dropped, because of a network failure or because the system on the other end went down without notice.";
     break;
case WSAECONNREFUSED:
     es += "WSAECONNREFUSED:";
     break;
case WSAELOOP:
     es += "WSAELOOP:";
     break;
case WSAENAMETOOLONG:
     es += "WSAENAMETOOLONG:";
     break;
case WSAEHOSTDOWN:
     es += "WSAEHOSTDOWN:";
     break;
case WSAENOTEMPTY:
     es += "WSAENOTEMPTY:";
     break;
case WSAEPROCLIM:
     es += "WSAEPROCLIM:";
     break;
case WSAEUSERS:
     es += "WSAEUSERS:";
     break;
case WSAEDQUOT:
     es += "WSAEDQUOT:";
     break;
case WSAESTALE:
     es += "WSAESTALE:";
     break;
case WSAEREMOTE:
     es += "WSAEREMOTE:";
     break;
default: es += "UNRESOLVED: " + inttostr(errcode);
}
}
//------------------------------------------------------------------------------
void __fastcall exsSstEXCEPTION(TEventLogThread* elt,const string& StrLocation,Exception& e)
{
if(elt)
 if(elt->getlog())
   {
   TDateTime DateTime = DateTime.CurrentDateTime();
   string str;
   exsDateTime(DateTime,str);
   str += "  EXCEPTION: " + StrLocation;
   string Str = "\n\n\n\n" + str + "\n";
   elt->FputEvt(Str,1);
   str = "Message: " + (string)e.Message.c_str() + ",  HelpContext: " + inttostr(e.HelpContext) + "\n";
   elt->FputEvt(str,1);
   }
throw;
}
//----------------------------------------------------------------------------
void __fastcall PackFixedParameter(UBYTE* buf,int data,int DataType,int& n)
{
switch(DataType)
 {
 case 1:  // 1 Byte
      buf[n++] = data & 0xFF;
      break;
 case 2:   // 2 Bytes
      buf[n++] = (data >> 8) & 0xFF;    //MSB data
      buf[n++] =  data & 0xFF;           //LSB data
      break;
 case 4:   // 4 bytes
      buf[n++] = (data >> 24) & 0xFF;   //MSB data
      buf[n++] = (data >> 16) & 0xFF;   //    data
      buf[n++] = (data >> 8) & 0xFF;    //    data
      buf[n++] =  data & 0xFF;           //LSB data
      break;
 }
}
//----------------------------------------------------------------------------
int __fastcall findTerminationSymbol(string& s)
{
int st=-1;
st = s.find("#");
if(st==-1)
   {
   st = s.find("//");
   if(st==-1)
     {
     st=s.find("\\");
     if(st==-1)
       return s.find(";");
     }
   }
return st;
}
//----------------------------------------------------------------------------
void __fastcall trimString(string& s,int st)
{
if(s.empty())return;
const char* buf = s.c_str();
int i=st-1;
for(;i>0;i--)
   if(buf[i] != ws_char)
      break;
if(i)
  s.resize(i+1);
}
//----------------------------------------------------------------------------
//--- delete left white spaces -----------------------------------------------
//----------------------------------------------------------------------------
void __fastcall left_trim_string(string& s)
{
int len = s.length();
if(len)
  {
  int i = 0;
  while(i < len)
       {
       if(s[i] != ws_char)
         break;
       i++;
       }
  if(i)
    s = s.substr(i);
  }
}
//----------------------------------------------------------------------------
void __fastcall CheckIniData(string& s)
{
int st = findTerminationSymbol(s);
if(st==-1)return;
trimString(s,st);
}
//------------------------------------------------------------------------------
int __fastcall getIpSubAddr(string& src,string& result,int& curPos,int& length)
{
result = "";
if(curPos >= length)
   return -1;
int p = src.find(SST_DotChar,curPos);
if(p != -1)
  {
   result = src.substr(curPos,p-curPos);
   curPos = p+1;
   return atoi(result.c_str());
  }
return -1;
}
//------------------------------------------------------------------------------
unsigned __fastcall StrIpToInt(string& src_str)
{
unsigned a = 0;
string s = src_str;
s += SST_DotChar;
string res;
int curPos = 0;
int length = s.length();
for(int i=0;i<4;i++)
   {
   int b = getIpSubAddr(s,res,curPos,length);
   if(b != -1)
      a = a | (b << (24 - i*8));
   }
return a;
}
//------------------------------------------------------------------------------
void __fastcall exsConvByteStrToUnsigned(unsigned& dest,const string& s,int& st,int& st_1,int len,int i)
{
st = s.find_first_of("1234567890",st_1);
if(st!=-1)
  {
  st_1 = s.find(DOTSTRING,st);
  if(st<st_1)
    if(st_1<len)
      dest |= atoi((s.substr(st,st_1-st)).c_str())<<(24 - 8*i);
  }
}
//------------------------------------------------------------------------------
unsigned __fastcall exsConvStrIpAddrToUnsigned(const string& str)
{
unsigned rv=0;
string s  = str + DOTSTRING;
int len   = s.length();
int st    = 0;
int st_1  = 0;
for(int i=0;i<4;i++)
    exsConvByteStrToUnsigned(rv,s,st,st_1,len,i);
return rv;
}
//------------------------------------------------------------------------------
void __fastcall SipLegStateToStr(string& s,SipLegState sls)
{
s+=WS;
switch(sls){
      case SPS_INVITE_REQ:
           s+="SPS_INVITE_REQ";
           break;
      case SPS_INVITE_FILETRANSFER_REQ:
           s+="SPS_INVITE_FILETRANSFER_REQ";
           break;
      case SPS_INVITE_SCREENSHARING_REQ:
           s+="SPS_INVITE_SCREENSHARING_REQ";
           break;
      case SPS_INIT_REGISTER_REQ:
           s+="SPS_INIT_REGISTER_REQ";
           break;
      case SPS_REGISTER_REQ:
           s+="SPS_REGISTER_REQ";
           break;
      case SPS_FINAL_REGISTER_REQ:
           s+="SPS_FINAL_REGISTER_REQ";
           break;
      case SPS_INIT_SUBSCRIBE_REQ:
           s+="SPS_INIT_SUBSCRIBE_REQ";
           break;
      case SPS_PRESENCE_NOTIFY_REQ:
           s+="SPS_PRESENCE_NOTIFY_REQ";
           break;
      case SPS_MESSAGE_REQ:
           s+="SPS_MESSAGE_REQ";
           break;
      case SPS_DISC_OUT_REQ:
           s+="SPS_DISC_OUT_REQ";
           break;
      case SPS_INIT_RTP_AUDIO_SEQ:
           s+="SPS_INIT_RTP_AUDIO_SEQ";
           break;
      #ifdef SIP_Video
      case SPS_INIT_RTP_VIDEO_SEQ:
           s+="SPS_INIT_RTP_VIDEO_SEQ";
           break;
      #endif
      case SPS_DECLINE_REQ:
           s+="SPS_DECLINE_REQ";
           break;
      case SPS_KEEP_ALIVE:
           s+="SPS_KEEP_ALIVE";
           break;
      default:s+="UNKNOWN";
      }
}
//------------------------------------------------------------------------------
void __fastcall exsDeleteSentBlock(void* block)
{
BaseExchangeBlock* bb = (BaseExchangeBlock*)block;
switch(bb->getBlockType()){
      case TOutPutDtmf_BLOCKTYPE:{
           #ifdef TOutPutDtmfBlock_Create
           TOutPutDtmfBlock* opd = (TOutPutDtmfBlock*)bb;
           MainFormSLS->Sip->Log("\nDeleted TOutPutDtmfBlock #" + inttostr(opd->getBlockCount()),1);
           #endif
           break;
           }
      case TSipParsBuf_BLOCKTYPE:{
           #ifdef BaseExchBlock_Create
           TSipParsBuf* spb = (TSipParsBuf*)bb;
           MainFormSLS->Sip->Log("\nDeleted SipParsBuf #" + inttostr(spb->getBlockCount()));
           #endif
           break;
           }
      case TRemoteMedia_BLOCKTYPE:
      case TVcamPar_BLOCKTYPE:
      case TAuthPar_BLOCKTYPE:
      case TOutPutUdpBlock_BLOCKTYPE:
      case TWaveOutPutBuf_BLOCKTYPE:
      case TOutputSipBuf_BLOCKTYPE:
           break;
      default: MainFormSLS->Sip->Log("\nError: try to delete block with unknown BLOCKTYPE " + inttostr(bb->getBlockCount()));
     }
delete bb;
}
//---------------------------------------------------------------------------
bool __fastcall exsCheck_OnReceive_FileTransfer(const string& s,TTransferFileAttrib* tfa)
{
bool rv=false;
int st = s.find("m=message");
if(st!=-1)
  {
  int en = s.find(crlf,st);
  if(en!=-1)
    {
    st = s.find("MSRP",st);
    if(st!=-1)
      if(st < en)
        {
        exsGet_FileTransfer_Attributes(s,st,tfa);
        rv=true;
        }
    }
  }
return rv;
}
//---------------------------------------------------------------------------
void __fastcall exsGet_Attrib(const string& s, const string& pattern, string& out, int& st)
{
out.clear();
st = s.find(pattern,st);
if(st!=-1)
  {
  st = s.find(COLON,st);
  if(st!=-1)
    {
    st++;
    int en = s.find(crlf,st);
    if(en!=-1)
      if(st < en)
        {
        out = s.substr(st,en-st);
        st = en;
        }
    }
  }
}
//------------------------------------------------------------------------------
void __fastcall exsGet_FileTransfer_Attributes(const string& s,int ST,TTransferFileAttrib* tfa)
{
int st = ST;
string result;

exsGet_Attrib(s, "a=session-id", result, st);
if(!result.empty())
    tfa->sid = strtoint(result);

exsGet_Attrib(s, "a=file_name", result, st);
if(!result.empty())
    tfa->file_name = result;

exsGet_Attrib(s, "a=file-size", result, st);
if(!result.empty())
    tfa->file_size = strtoint(result);
}
//------------------------------------------------------------------------------
bool __fastcall isVideoPacketPSC(vector<UBYTE>& v)
{
bool rv=false;
if(v.size() > 12)
  if((v[1] & 0x7F) == 115) //H.263+
    if(!(v[12] & 0x80))   // RFC2190 bit F  of H263header
      if(v[12] & 0x4) //PSC
         rv = true;
return rv;
}
//------------------------------------------------------------------------------
string __fastcall getauthel(const string& s,const string& el)
{
int st = s.find(el);
if(st==-1)return emptystr;
st+=el.length();
int en = s.find(",",st);
if(en==-1)
  {
  en=s.find(crlf,st);
  if(en==-1)
     return emptystr;
  }
int len=en-st;
if(len<1)return emptystr;
string ret = s.substr(st,len);
st=ret.find("\"");
if(st==-1)
  return ret;
if(len-st>1)
  ret=ret.substr(st+1,len-1);
st=ret.find("\"");
if(st==-1)
  return ret;
if(st)
  ret=ret.substr(0,st);
return ret;
}
//------------------------------------------------------------------------------
unsigned long __fastcall get_reg_process_id()
{
unsigned long rv = 0;
TRegistry& regKey = *new TRegistry();
regKey.RootKey = ROOT_KEY;
bool keyGood = regKey.OpenKey(key_name.c_str(),false);
if(keyGood)
  {
  keyGood = regKey.OpenKey(pid.c_str(),false);
  if(keyGood)
     rv = regKey.ReadInteger(pid_value.c_str());
  }
delete &regKey;
return rv;
}
//------------------------------------------------------------------------------
bool __fastcall exs_app_runnig(const string& Gl_Atom_Name,
                               const string& App_Class,const string& App_Name,
                               const string& Win_Class)
{
#ifdef DEBUG__START__CLIENT
FILE* f = fopen("C:\\debug__start__sstsip__client.txt","wt");
if(f)
  fputs("exs_app_runnig()\n",f);
#endif
bool rv = false;
ATOM a =  GlobalFindAtom(Gl_Atom_Name.c_str());
if(a)
  {
  #ifdef DEBUG__START__CLIENT
  fputs("found Gl_Atom_Name\n",f);
  string s = "Try to get Application with name: \"" + App_Name + "\"\n";
  fputs(s.c_str(),f);
  #endif
  HWND hwnd_app = FindWindow(App_Class.c_str(),App_Name.c_str());
  if(hwnd_app)
    {
     #ifdef DEBUG__START__CLIENT
     fputs("found window with App_Class, App_Name\n",f);
     #endif
     int i=0;
     unsigned long reg_process_id = get_reg_process_id();
     HWND hwnd = FindWindow(Win_Class.c_str(),NULL);
     while(hwnd)
          {
          if(i++ > 10000)break;
          if(IsWindow(hwnd))
            {
            unsigned long mProcessID = 0;
            GetWindowThreadProcessId(hwnd,&mProcessID);
            if(reg_process_id == mProcessID)
              {
              char buf[128];
              if(GetClassName(hwnd,buf,128))
                {
                string class_name = string(buf);
                if(class_name == Win_Class)
                  {
                  ShowWindowAsync(hwnd, SW_SHOWNA);
                  rv = true;
                  break;
                  }
                }
              }
            }
          hwnd = GetNextWindow(hwnd,GW_HWNDNEXT);
          }
    } //if(hwnd_app)
  } //if(a)
else
  GlobalAddAtom(Gl_Atom_Name.c_str());
#ifdef DEBUG__START__CLIENT
if(f)
  fclose(f);
#endif
return rv;
}
//------------------------------------------------------------------------------
double __fastcall abs_max_value(vector<double>& y)
{
double max = 0.0;
int sz_y = y.size();
for(int i=0;i<sz_y;i++)
   {
   double abs_a = abs(y[i]);
   if(max < abs_a)
      max = abs_a;
   }
return max;   
}
//------------------------------------------------------------------------------
void __fastcall ubyte_2_short(vector<short>& x,vector<UBYTE>& v,int sz)
{
for(int i=0;i<sz;i+=2)
   {
   if(i+1 < sz)
     {
     XBYTE a = v[i];   //LSB
     a |= v[i+1] << 8; //MSB with sign
     x.push_back(a);
     }
   }
}
//-------------------------------------------------------------------------------
void __fastcall short_2_double(vector<double>& y,vector<short>& x)
{
int sz_x = x.size();
for(int i=0;i<sz_x;i++)
    y.push_back(x[i]);
}
//-------------------------------------------------------------------------------
void __fastcall double_2_short(vector<short>& x,vector<double>& y,int sz,bool type)
{
x.clear();
for(int i=0; i<sz; i++)
   {
   if(type)
     y[i] *= 5000.0;
   round_up(y,i);
   x.push_back(y[i]);
   }
}
//------------------------------------------------------------------------------
//-- ќкругление до целого чисел с плавающей зап€той ----------------------------
//------------------------------------------------------------------------------ 
void __fastcall round_up(vector<double>& y,int i)
{
if(y.empty())
  return;
if(y[i] < 0)
  {
  if((-y[i] - floor(-y[i])) < 0.5)
     y[i] = ceil(y[i]);
  else
     y[i] = floor(y[i]);
  }
else
  {
  if((y[i] - floor(y[i])) < 0.5)
     y[i] = floor(y[i]);
  else
     y[i] = ceil(y[i]);
  }
}
//------------------------------------------------------------------------------
void __fastcall short_2_ubyte(vector<UBYTE>& v,vector<short>& x,int sz)
{
v.clear();
for(int i=0; i<sz; i++)
   {
   UBYTE a = x[i] & 0xFF;
   v.push_back(a);
   a = x[i] >> 8;
   v.push_back(a);
   }
}
//------------------------------------------------------------------------------
//-- SZ - размер вектора, в котором хран€тс€ значени€ int ----------------------
//-- ѕередаютс€ только два младших байта. ѕеред использованием данной ф-ии -----
//-- должна быть проведена нориализаци€ значений  хран€щихс€ в векторе int -----
//-- (т.е. приведение значений  в диапазон от 32000 > x[i] > -32000 - max  -----
//-- амплитуда аудио сигнала) -- ф-€ NORMALIZE()  ------------------------------
//------------------------------------------------------------------------------
void __fastcall INT_2_UBYTE(vector<UBYTE>& v, const vector<int>& x, int SZ)
{
for(int i=0;i<SZ;i++){
   v.push_back(x[i]);
   v.push_back(x[i] >> 8);
   }
}
//------------------------------------------------------------------------------
//-- SZ - размер вектора, в котором хран€тс€ значени€ UBYTE --------------------
//------------------------------------------------------------------------------
void __fastcall UBYTE_2_INT(vector<int>& v_mix, const vector<UBYTE>& v, int SZ_UBYTE)
{
for(int i=0;i<SZ_UBYTE;i+=2)
   {
   if(i+1 < SZ_UBYTE)
     {
     short a = v[i] & 0xFF;
     a |= v[i+1] << 8;
     v_mix.push_back(a);
     }
   }
}
//------------------------------------------------------------------------------
void __fastcall MIX_UBYTE_2_INT(vector<int>& v_mix, const vector<UBYTE>& v, int SZ_UBYTE)
{
int SZ_INT = v_mix.size();
for(int i=0,y=0;i < SZ_UBYTE,y < SZ_INT;i+=2,y++)
   {
   if(i+1 < SZ_UBYTE)
     {
     short a = v[i] & 0xFF;
     a |= v[i+1] << 8;
     v_mix[y] += a;
     }
   }
}
//------------------------------------------------------------------------------
void __fastcall NORMALIZE(vector<int>& v_mix, int SZ)
{
vector<double> y;
for(int i=0;i<SZ;i++)
    y.push_back((double)v_mix[i]);
double abs_max = abs_max_value(y);
if(abs_max > 32000.0)
  {
  double p_coeff = 32000.0/abs_max;
  for(int i=0;i<SZ;i++)
      y[i] *= p_coeff;
  for(int i=0;i<SZ;i++)
     {
     round_up(y,i); //округлить до целого
     v_mix[i] = (int)y[i];
     }
  }
}
//------------------------------------------------------------------------------
int __fastcall get_payload_type(UBYTE a)
{
return (a & 0x7F);
}
//-----------------------------------------------------------------------------
void __fastcall G711_To_Linear(vector<UBYTE>& dst_v,vector<UBYTE>& src_v,int pt)
{
int size = src_v.size();
for(int i=0;i<size;i++)
  {
  short b = 0;
  switch(pt){
         case 0: b = ulaw2linear(src_v[i]);
                 break;
         case 8: b = alaw2linear(src_v[i]);
                 break;
        }
  UBYTE a = UBYTE(b & 0xFF);
  dst_v.push_back(a);
  a = UBYTE((b >> 8) & 0xFF);
  dst_v.push_back(a);
  }
}
//-----------------------------------------------------------------------------
unsigned __fastcall get_seq_number(UBYTE msb,UBYTE lsb)
{
return (msb << 8) | lsb;
}
//-----------------------------------------------------------------------------
UINT __fastcall md_32(char *string, int length)
{
MD_CTX context;
union{
     char   c[16];
     u_long x[4];
     } digest;
u_long r;
int i;
MDInit (&context);
MDUpdate (&context, string, length);
MDFinal ((unsigned char *)&digest, &context);
r = 0;
for(i = 0; i < 3; i++) {
   r ^= digest.x[i];
   }
return r;
}
//------------------------------------------------------------------------------
UINT __fastcall random32(int type, int pid, UINT hostid, char* host_name, UINT hostnamelength)
{
struct {
    int     type;
    SYSTEMTIME st;
    clock_t cpu;
    int     pid;
    UINT    hid;
    char    hostname[32];
    } s;

  s.type = type;
  ::GetLocalTime(&s.st);
  s.cpu  = clock(); //since the start time
  s.pid  = pid;
  s.hid  = hostid;
  memcpy(&s.hostname[0],host_name,min(sizeof(s.hostname),hostnamelength));
return md_32((char *)&s, sizeof(s));
}
//----------------------------------------------------------------------------
UINT __fastcall get_random32(int type)
{
char hostname[32];
gethostname(hostname,sizeof(hostname));
unsigned hostid = 0;
hostent* sh = gethostbyname((char*)&hostname);
if(sh->h_addr_list[0])
  {
  struct sockaddr_in adr;
  memcpy(&adr.sin_addr,sh->h_addr_list[0],sh->h_length);
  hostid = adr.sin_addr.S_un.S_addr;
  }
return random32(type,getpid(),hostid,hostname,sizeof(hostname));
}
//----------------------------------------------------------------------------
void __fastcall lowercase(string& s)   //дл€ русск не действует
{
for(string::iterator it = s.begin(); it != s.end(); it++ )
   *it = tolower(*it);
}
//----------------------------------------------------------------------------
void __fastcall uppercase(string& s)
{
for(string::iterator it = s.begin(); it != s.end(); it++ )
   *it = toupper(*it);
}
//----------------------------------------------------------------------------
string __fastcall get_current_user()
{
string rv;
string s_cl = MainFormSLS->get_client_dir();
if(::DirectoryExists(s_cl.c_str()))
  {
  s_cl += "\\cl.rst";
  FILE* f = fopen(s_cl.c_str(),"rt");
  if(f)
    {
    char buf[256];
    if(fgets( buf,sizeof(buf), f))
       rv = string(buf);
    fclose(f);
    }
  }
return rv;
}
//---------------------------------------------------------------------------
bool __fastcall check_directory_existence(const string& directory)
{
string dir = directory;
vector<string> v;
while(!::DirectoryExists(dir.c_str()))
     {
     int st = dir.rfind("\\");
     if(st == -1)
        return false;
     string s = dir.substr(st);
     v.push_back(s);
     dir.resize(st);
     }
if(!v.empty())
  {
  vector<string>::reverse_iterator it = v.rbegin();
  while(it != v.rend())
       {
       dir += (*it);
       if(!::CreateDir(dir.c_str()))
          return false;
       it++;
       }
  }
return true;
}
//---------------------------------------------------------------------------
void __fastcall copy_dir(const AnsiString& myTempDir, AnsiString& currentRemoteDir)
{       /*
int iAttributes = faAnyFile;
AnsiString  myNewDir;
TSearchRec sr;
int retVal = FindFirst(currentRemoteDir + "\\*.*", iAttributes, sr);
if(!retVal)
   {
    if((sr.Attr & faDirectory) == faDirectory)
       {
       if((sr.Name != ".")&&(sr.Name != ".."))
         {
         myNewDir = myTempDir + "\\" + sr.Name;
         ::CreateDir(myNewDir);
         copy_dir(myNewDir,currentRemoteDir + "\\" + sr.Name);
         }
       if(rdt)
         {
         if((rdt->getTsa())&&(rdt->getTsa()->tdr))
            rdt->getTsa()->tdr->pb->Position++;
         }
       }
    else
       {
       AnsiString Ext = ExtractFileExt(sr.Name);
       Ext = Ext.LowerCase();
       if(Ext != ".lck")     //22911_14
         {
         if(!::CopyFile((currentRemoteDir + "\\" + sr.Name).c_str(),(myTempDir + "\\" + sr.Name).c_str(),false))
            retVal = 1;
         }
       }
     while (FindNext(sr) == 0)
         {
         if((sr.Attr & faDirectory) == faDirectory)
           {
           if((sr.Name != ".")&&(sr.Name != ".."))
             {
             myNewDir = myTempDir + "\\" + sr.Name;
             ::CreateDir(myNewDir);
             if(copyDb(myNewDir,currentRemoteDir + "\\" + sr.Name))
               retVal = 1;
             if(rdt)
               {
               if((rdt->getTsa())&&(rdt->getTsa()->tdr))
                  rdt->getTsa()->tdr->pb->Position++;
               }
             }
           }
         else
           {
           AnsiString Ext = ExtractFileExt(sr.Name);
           Ext = Ext.LowerCase();
           if(Ext != ".lck")     //22911_14
             {
             if(!::CopyFile((currentRemoteDir + "\\" + sr.Name).c_str(),(myTempDir + "\\" + sr.Name).c_str(),false))
                retVal = 1;
             }
           }
         }
   FindClose(sr);
   } //if(!retVal)   */
}
//------------------------------------------------------------------------------//
//------------------------ For interval in sec < 24 hours ----------------------//
//------------------------------------------------------------------------------//
/*
void __fastcall secToTDateTime(unsigned a,USHORT& hour,USHORT& min,USHORT& sec)
{
sec=0;
min=0;
hour=0;

sec = a%60;
a-=sec;
a/=60;
if(a<60)
  {
  min=a;
  return;
  }
min = a%60;
a-=min;
a/=60;
if(a<24)
  {
  hour=a;
  return;
  }
hour=23;    //interval > 24 hours
min=59;
sec=59;
}
*/
//-----------------------------------------------------------------------------//
//--------------- For any intervals in sec  -----------------------------------//
//-----------------------------------------------------------------------------//
TDateTime __fastcall sec_to_date_time(unsigned a)
{
int    gl_min  = a/60;       //делить на кол-во секунд в минуте
int    gl_hour = gl_min/60;  //делить на кол-во минут в часе
USHORT gl_day  = gl_hour/24; //делить на кол-во часов в дне
int sec        = a%60;
int min        = gl_min%60;  //кол-во минут в последнем часе
int hour       = gl_hour%24; //кол-во часов в последнем дне
return TDateTime(gl_day) + TDateTime(hour, min, sec, 0);
}
//------------------------------------------------------------------------------
unsigned __fastcall prep_sub_branch(SYSTEMTIME* s,int type)
{
unsigned a = 0;
switch(type){
      case 0:a = s->wMonth;
             break;
      case 1:a  = s->wMinute;
             a |= s->wHour  << 6;
             a |= s->wDay   << 11;
             break;
      case 2:a  = s->wMilliseconds;
             a |= s->wSecond << 10;
             break;
      }
return a;
}
//------------------------------------------------------------------------------
unsigned __fastcall DateTimeToSec(const TDateTime& dt)
{
unsigned short hour;
unsigned short min;
unsigned short sec;
unsigned short msec;
dt.DecodeTime(&hour,&min,&sec,&msec);
unsigned days = floor((double)dt);
if(msec)
   sec++;
return days*24*60*60 + hour*60*60 + min*60 + sec;
}
//------------------------------------------------------------------------------
string __fastcall month_to_str(int month, Lang lng)
{
string s;
if(lng == Lang_RU)
  {
  switch(month){
         case 1:  s = "€нвар€";   break;
         case 2:  s = "феврал€";  break;
         case 3:  s = "марта";    break;
         case 4:  s = "апрел€";   break;
         case 5:  s = "ма€";      break;
         case 6:  s = "июн€";     break;
         case 7:  s = "июл€";     break;
         case 8:  s = "августа";  break;
         case 9:  s = "сент€бр€"; break;
         case 10: s = "окт€бр€";  break;
         case 11: s = "но€бр€";   break;
         case 12: s = "декабр€";  break;
        }
  }
else
  {
  switch(month){
         case 1:  s = "january";  break;
         case 2:  s = "february"; break;
         case 3:  s = "march";    break;
         case 4:  s = "апрел€";   break;
         case 5:  s = "may";      break;
         case 6:  s = "june";     break;
         case 7:  s = "july";     break;
         case 8:  s = "august";   break;
         case 9:  s = "september";break;
         case 10: s = "october";  break;
         case 11: s = "november"; break;
         case 12: s = "december"; break;
      }
  }
return s;  
}
//------------------------------------------------------------------------------
void __fastcall Get_OS_Version(OSVERSIONINFO* posv)
{
 posv->dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
 posv->dwMajorVersion = 0;
 posv->dwMinorVersion = 0;
 posv->dwBuildNumber  = 0;
 posv->dwPlatformId   = 0;
 GetVersionEx(posv);
}
//---------------------------------------------------------------------------
void __fastcall scale_volume(vector<UBYTE>& v,double p_coeff)
{
vector<short> x;
vector<double> y;
int sz = v.size();
ubyte_2_short(x,v,sz);
short_2_double(y,x);
double abs_max = abs_max_value(y);
if(p_coeff == 1.0)
  {
  if(abs_max > 32000.0)
     {
     int sz_y = y.size();
     if(sz_y)
       {
       p_coeff = 32000.0/abs_max;
       for(int i=0;i<sz_y;i++)
           y[i] *= p_coeff;
       double_2_short(x,y,sz_y,false);
       short_2_ubyte(v,x,sz_y);
       }
     }
  return;
  }

if(abs_max > 0.1)
   if(abs_max * p_coeff > 32000.0)
     p_coeff = 32000.0/abs_max;
int sz_y = y.size();
for(int i=0;i<sz_y;i++)
    y[i] *= p_coeff;
double_2_short(x,y,sz_y,false);
short_2_ubyte(v,x,sz_y);
}
//---------------------------------------------------------------------------
int __fastcall expires_to_int(const string& exp_s)
{
int rv = 0;
int en = exp_s.rfind(crlf);
int st = exp_s.find("Expires:");
if(st != -1)
  {
  st += 8;
  if(st < en)
    {
    st = exp_s.find_first_of("1234567890",st);
    if(st != -1)
      if(st < en)
        rv = strtoint(exp_s.substr(st,en-st));
    }
  }
return rv;  
}
//------------------------------------------------------------------------------
//-- выбирает наиболее подход€щий IP дл€ локальной сети (Contact Addr fo parallel phone)
//-- »спользуетс€ вместо точного определени€ с использоввнием GetIpNetTable() и получением
//-- dwMask (see HELP -> How_To_Get_Mask) --------------------------------------
//------------------------------------------------------------------------------
string __fastcall select_local_ip_addr(UINT from_ip)
{
UINT min = -1;
string rez;
queue<TIPAddress> iplst;
char chInfo[512];
if(!gethostname(chInfo,sizeof(chInfo)))
  {
  hostent* sh = gethostbyname((char*)&chInfo);
  if(sh != NULL)
    {
    int nAdapter = 0;
    while(sh->h_addr_list[nAdapter])
         {
         struct sockaddr_in adr;
         memcpy(&adr.sin_addr,sh->h_addr_list[nAdapter],sh->h_length);
         string s_ipaddr = string(inet_ntoa(adr.sin_addr));
         TIPAddress ip;
         ip.IPAddr  = s_ipaddr;
         ip.uIPAddr = exsConvStrIpAddrToUnsigned(s_ipaddr);
         iplst.push(ip);
         nAdapter++;
         }
    }
  }
while(!iplst.empty())
     {
     TIPAddress ip = iplst.front();
     iplst.pop();
     UINT a = ip.uIPAddr ^ from_ip;
     if(min > a)
       {
       min = a;
       rez = ip.IPAddr;
       }
     }
return rez;
}
//-----------------------------------------------------------------------------
void __fastcall dissect_sdp_str(queue<string>& qs, const string& s)
{
int n = 0;
int len = s.length();
while(get_sdp_substr(qs,s,n,len));
}
//----------------------------------------------------------------------------
bool __fastcall get_sdp_substr(queue<string>& qs, const string& s, int& n, int len)
{
bool rv = false;
if(n < len)
  {
  int st  = s.find(crlf,n);
  if(st != -1)
    {
    st += 2;
    qs.push(s.substr(n,st-n));
    n = st;
    rv = true;
    }
  }
return rv;
}
//-----------------------------------------------------------------------------
bool __fastcall get_digit_substr(const string& s, int& rezult, int st)
{
bool rv = false;
int len = s.length();
if(st < len)
  {
  st = s.find_first_of("123456789", st);
  if(st == -1)    return rv;
  int en = s.find(WS,st);
  if(en == -1)    return rv;
  if((en-st) < 1) return rv;
  rezult = atoi(s.substr(st,(en-st)).c_str());
  rv = true;
  }
return rv;
}
//------------------------------------------------------------------------------
int Utf8Code_calculateEnBufferSize (const char* inputBuff, int inputSize)
{
  if ( inputSize == 0 )
    return 0;
  int ws = ::MultiByteToWideChar( CP_ACP, 0, inputBuff, inputSize, NULL, 0 );
  std::vector<wchar_t> unicodeBuff( ws );
  ::MultiByteToWideChar( CP_ACP, 0, inputBuff, inputSize, &*unicodeBuff.begin(), ws );
  return ::WideCharToMultiByte( CP_UTF8, 0, &*unicodeBuff.begin(), ws, NULL, 0, NULL, NULL);
}

int Utf8Code_calculateDecBufferSize (const char* inputBuff, int inputSize)
{
  if ( inputSize == 0 )
  {
      return 0;
  }
  int ws = ::MultiByteToWideChar( CP_UTF8, 0, inputBuff, inputSize, 0, 0 );
  std::vector<wchar_t> unicodeBuff( ws );
  ::MultiByteToWideChar( CP_UTF8, 0, inputBuff, inputSize, &*unicodeBuff.begin(), ws );
  return ::WideCharToMultiByte( CP_ACP, 0, &*unicodeBuff.begin(), ws, NULL, 0, NULL, NULL);
}

void Utf8Code_encode (const char* inputBuff, int inputSize, char* outputBuff, int outputSize)
{
  std::vector<wchar_t> unicodeBuff( inputSize );
              //::MultiByteToWideChar( CP_ACP, 0, inputBuff, inputSize, &unicodeBuff[0], inputSize );
  ::MultiByteToWideChar( CP_ACP, 0, inputBuff, inputSize, &unicodeBuff[0], outputSize );
  ::WideCharToMultiByte( CP_UTF8, 0, &*unicodeBuff.begin(), inputSize, outputBuff, outputSize, NULL, NULL );
}

string ANSI_2_UTF8(const string& src) {
  if (src.length()==0)
    return std::string("");
  std::vector<wchar_t> in(src.length());
  ::MultiByteToWideChar( CP_ACP, 0, src.c_str(), src.length(), &*in.begin(), in.size() );
  std::vector<std::string::value_type> out(Utf8Code_calculateEnBufferSize(&*src.begin(), src.size()));
  ::WideCharToMultiByte( CP_UTF8, 0, &*in.begin(), in.size(), &*out.begin(), out.size(), NULL, NULL );
  return std::string(&*out.begin(), out.size());
}

string UTF8_2_ANSI(const string& src)
{
  if (src.length()==0)
    return std::string("");
  std::vector<wchar_t> in(src.length());
  ::MultiByteToWideChar( CP_UTF8, 0, src.c_str(), src.length(), &*in.begin(), in.size() );
  std::vector<std::string::value_type> out(Utf8Code_calculateDecBufferSize(&*src.begin(), src.size()));
//  ::WideCharToMultiByte( 1251, 0, &*in.begin(), in.size(), &*out.begin(), out.size(), NULL, NULL );
  ::WideCharToMultiByte( CP_ACP, 0, &*in.begin(), in.size(), &*out.begin(), out.size(), NULL, NULL );
  return std::string(&*out.begin(), out.size());
}
//----------------------------------------------------------------------------------------------------
void __fastcall set_img_cursor_type(TImage* img)
{
img->Cursor = crHandPoint;
}
//---------------------------------------------------------------------------

