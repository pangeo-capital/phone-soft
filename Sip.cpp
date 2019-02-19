//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <Filectrl.hpp>
#include <Registry.hpp>
#include "WinRDefs.h"
#include "Sip.h"
#include "utils.h"
#include "SipClient_Unit.h"
#include "Unit3.h"
#include "const.h"
#include "digcalc.h"
#include "Unit_EnterpriseSubscList.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

#define LEFT_TIME_MARGIN  60 //100

const commit_packet_size     = 10;
const string BranchMagicCck  = "z9hG4bK";
const string CONTACTS_DIR    = "CONTACTS";
const string CHAT_GROUPS_DIR = "CHATGROUPS";

//---------------------------------------------------------------------------
void __fastcall TSip::log(TEventLogThread* elt,const string& s)
{
if(elt)
   if(elt->getlog())
      elt->FputEvt(s);
}
//------------------------------------------------------------------------------
void __fastcall TSip::Log(const string& s,int fflush)
{
TEventLogThread* elt = *eltp;
if(elt)
   if(elt->getlog())
      elt->FputEvt(s,fflush);
}
//------------------------------------------------------------------------------
__fastcall TLegTrn::TLegTrn(LegType lt)
{
::InitializeCriticalSection(&lt_cs);
dt = dt.CurrentDateTime();
legtype = lt;
state   = SPS_UNKNOWN;
resp    = SPS_UNKNOWN;
resp183SdpRcvd = false;
Current_CSeq=0;
//ocseq=0;
CSeq_NOTIFY = 0;
//CSeq_INFO   = 0;
refNum      = 0;
//application  = false;
block_BYE = false;
remoteport=-1;
Auth        = NULL;
ReferNOTIFY = NULL;
INFO        = NULL;
Subscribe   = NULL;
Mime        = NULL;
Message     = NULL;
//ReplacePar = NULL;
ospb_wait_first_mic_packet = NULL;
remote_in_audio_port = -1;
RtpLocalAddr =  0;
RtpLocalPort = -1;
keepalive    = false;
CryptoKeys   = NULL;
PLACED_ON_HOLD_BY_LOCAL_PARTY  = false;
PLACED_ON_HOLD_BY_REMOTE_PARTY = false;
ch_sound      = -1;
ch_video      = -1;
ch_rtp_audio  = -1;
ch_rtcp_audio = -1;
#ifdef SIP_Video
ch_rtp_video  = -1;
ch_rtcp_video = -1;
#endif
screen_sharing_viewer   = false;
lt_parallel_phone       = false;
source_of_outgoing_call = 0;
primary_legtype_pph     = Lt_NDef;
}
//------------------------------------------------------------------------------
__fastcall TLegTrn::~TLegTrn()
{
if(CryptoKeys)
   delete CryptoKeys;
if(Auth)
   delete Auth;
if(ReferNOTIFY)
   delete ReferNOTIFY;
if(INFO)
   delete INFO;
if(Subscribe)
   delete Subscribe;
if(Mime)
   delete Mime;
if(Message)
   delete Message;
//if(ReplacePar)
//   delete (TReplacePar*)ReplacePar;
if(ospb_wait_first_mic_packet)
  {
  TOutputSipBuf* ospb = ospb_wait_first_mic_packet;
  ospb_wait_first_mic_packet = NULL;
  ospb->decReferenceCount();
  }
::DeleteCriticalSection(&lt_cs);
}
//------------------------------------------------------------------------------
void __fastcall TSip::collectLocalHostInterfaces(void* INIDATA)
{
localIP.clear();
char chInfo[512];
if(!gethostname(chInfo,sizeof(chInfo)))
   {
   hostent* sh = gethostbyname((char*)&chInfo);
   if (sh != NULL)
      {
      Log("\nLocal IP is:");
      int   nAdapter = 0;
      while (sh->h_addr_list[nAdapter])
            {
            struct   sockaddr_in   adr;
            memcpy(&adr.sin_addr,sh->h_addr_list[nAdapter],sh->h_length);
            string s_ipaddr = string(inet_ntoa(adr.sin_addr));
            TIPAddress* ipaddr = new TIPAddress;
            if(ipaddr)
              {
              ipaddr->IPAddr  = s_ipaddr;
              ipaddr->uIPAddr = exsConvStrIpAddrToUnsigned(s_ipaddr);
              localIP.push_back(ipaddr);
              }
            Log("\n" + s_ipaddr);
            nAdapter++;
            }
      }
   selectLocalNetAddr(INIDATA);
   }
}
//---------------------------------------------------------------------------
void __fastcall TSip::selectLocalNetAddr(void* INIDATA)
{
TIniData* IniData = (TIniData*)INIDATA;
if(IniData->StunIniData.Addr.empty())
  {
  if(!localIP.empty())
    {
    unsigned exclor_result_prev = -1;
    deque<TIPAddress*>::iterator it = localIP.begin();
    while(it!=localIP.end())
         {
         TIPAddress* ipaddr = (*it);
         unsigned exclor_result_curr = SipProxy.uIPAddr^ipaddr->uIPAddr;
         if(exclor_result_curr < exclor_result_prev)
           {
           MappedAddress.IPAddr = ipaddr->IPAddr;
           exclor_result_prev = exclor_result_curr;
           }
         it++;
         }
    MappedAddress.uIPAddr = exsConvStrIpAddrToUnsigned(MappedAddress.IPAddr);
    Log("\nSelected Local IP " + MappedAddress.IPAddr);
    }
  return;
  }
stun = true;  
TIPAddress* ipaddr = getLastNIC();
if(ipaddr)
  {
  MappedAddress.IPAddr = ipaddr->IPAddr; //After this will be changed by STUN operation
  MappedAddress.uIPAddr = exsConvStrIpAddrToUnsigned(MappedAddress.IPAddr);
  Log("\nSelected Local IP " + MappedAddress.IPAddr);
  }
}
//---------------------------------------------------------------------------
void __fastcall TSip::getSockName(TEventLogThread* elt)
{
sockaddr name;
memset(&name,0,sizeof(name));
int namelen = sizeof(name);
if(getsockname(sck, &name, &namelen)==SOCKET_ERROR)
  {
  int err = WSAGetLastError();
  lasterr = "TSip::getSockName()";
  GetLastSocketError(lasterr,err);
  if(elt)
    if(elt->getlog())
      elt->FputEvt(lasterr);
  return;
  }
int n=0;
UBYTE* buf = (UBYTE*)name.sa_data; //!!!!!Protection from expansion of the sign bit to the left. Otherwise we have to shall every time produce mask of values with constants 0xFF00 and 0xFF
siphostport = buf[n++] << 8;
siphostport |= buf[n++];
//siphostaddr = inttostr((UBYTE)name.sa_data[n++]) + ".";    will be 0.0.0.0 for bind INADDR_ANY
//siphostaddr+= inttostr((UBYTE)name.sa_data[n++]) + ".";
//siphostaddr+= inttostr((UBYTE)name.sa_data[n++]) + ".";
//siphostaddr+= inttostr((UBYTE)name.sa_data[n++]);
}
//---------------------------------------------------------------------------
TIPAddress* __fastcall TSip::getLastNIC()
{
if(localIP.empty())return NULL;
return localIP.back();
}
//---------------------------------------------------------------------------
void __fastcall TSip::getSipProxyFromIniData(void* INIDATA)
{
TIniData* inidata = (TIniData*)INIDATA;
SipProxy.IPAddr   = inidata->SipProxyData.Addr;
SipProxy.uIPAddr  = exsConvStrIpAddrToUnsigned(SipProxy.IPAddr);
SipProxy.Port     = strtoint(inidata->SipProxyData.Port);
}
//---------------------------------------------------------------------------
void __fastcall TSip::getSipLocalProxyFromIniData(void* INIDATA)
{
TIniData* inidata = (TIniData*)INIDATA;
SipLocalProxy.IPAddr   = inidata->SipLocalProxyData.Addr;
SipLocalProxy.uIPAddr  = exsConvStrIpAddrToUnsigned(SipLocalProxy.IPAddr);
SipLocalProxy.Port     = strtoint(inidata->SipLocalProxyData.Port);
}
//---------------------------------------------------------------------------
void __fastcall TSip::getSipTunnelFromIniData(void* INIDATA)
{
TIniData* inidata = (TIniData*)INIDATA;
SipTunnel.IPAddr  = inidata->SipTunnelData.Addr;
SipTunnel.uIPAddr = exsConvStrIpAddrToUnsigned(SipTunnel.IPAddr);
SipTunnel.Port    = strtoint(inidata->SipTunnelData.Port);
}
//---------------------------------------------------------------------------
void __fastcall TSip::getSipLocalTunnelFromIniData(void* INIDATA)
{
TIniData* inidata      = (TIniData*)INIDATA;
SipLocalTunnel.IPAddr  = inidata->SipLocalTunnelData.Addr;
SipLocalTunnel.uIPAddr = exsConvStrIpAddrToUnsigned(SipLocalTunnel.IPAddr);
SipLocalTunnel.Port    = strtoint(inidata->SipLocalTunnelData.Port);
}
//---------------------------------------------------------------------------
void __fastcall TSip::get_INIDATA(void* INIDATA)
{
TIniData* iniData = (TIniData*)INIDATA;
getSipProxyFromIniData(iniData);
getSipLocalProxyFromIniData(iniData);
getSipTunnelFromIniData(iniData);
getSipLocalTunnelFromIniData(iniData);
getFTransferFromIniData(iniData);
collectLocalHostInterfaces(iniData);
getRegistryIntervalFromIniData(iniData);
getAccountFromIniData(iniData);
getSipTcp(iniData);
getSipTls(iniData);
getTransport(iniData);
getSubscDBData(iniData);
getScreenSharingData(iniData);
getSignalFromIniData(iniData);
#ifndef RTP_exsCreateUDPSocket_ADDR_ANY
getMediaFromIniData(iniData);
#endif
getG729ParFromIniData(iniData);
}
//----------------------------------------------------------------------------
void __fastcall TSip::getFTransferFromIniData(void* INIDATA)
{
TIniData* inidata    = (TIniData*)INIDATA;
if(inidata->FTransferIniData.Addr.empty())
   FileTransfer.IPAddr  = SipProxy.IPAddr; //default
else
   FileTransfer.IPAddr  = inidata->FTransferIniData.Addr;
FileTransfer.uIPAddr = exsConvStrIpAddrToUnsigned(FileTransfer.IPAddr);
if(inidata->FTransferIniData.Port.empty())
  FileTransfer.Port = 5088;               //default
else
  FileTransfer.Port = strtoint(inidata->FTransferIniData.Port);
}
//---------------------------------------------------------------------------
void __fastcall TSip::getRegistryIntervalFromIniData(void* INIDATA)
{
TIniData* inidata = (TIniData*)INIDATA;
regint = strtoint(inidata->SipProxyData.RegInt);
}
//---------------------------------------------------------------------------
void __fastcall TSip::getAccountFromIniData(void* INIDATA)
{
TIniData* inidata   = (TIniData*)INIDATA;
Account.set_user_name(inidata->AccountIniData.UserName);
Account.set_user_pwd(inidata->AccountIniData.Passward);
Account.set_domain(inidata->AccountIniData.Domain);
Account.set_displayname(inidata->AccountIniData.DisplayName);
}
//---------------------------------------------------------------------------
void __fastcall TSip::getSipTcp(void* INIDATA)
{
TIniData* inidata = (TIniData*)INIDATA;
SipTCP.IPAddr     = inidata->SipTcp.Addr;
SipTCP.Port       = strtoint(inidata->SipTcp.Port);
}
//---------------------------------------------------------------------------
void __fastcall TSip::getSipTls(void* INIDATA)
{
TIniData* inidata = (TIniData*)INIDATA;
SipTLS.IPAddr     = inidata->SipTls.Addr;
SipTLS.Port       = strtoint(inidata->SipTls.Port);
}
//---------------------------------------------------------------------------
void __fastcall TSip::getSubscDBData(void* INIDATA)
{
TIniData* inidata = (TIniData*)INIDATA;
SubscDB.IPAddr    = inidata->SubscDB.Addr;
SubscDB.Port      = strtoint(inidata->SubscDB.Port);
}
//----------------------------------------------------------------------------
void __fastcall TSip::getScreenSharingData(void* INIDATA)
{
TIniData* inidata    = (TIniData*)INIDATA;
ScreenSharing.IPAddr = inidata->ScreenSharing.Addr;
ScreenSharing.Port   = strtoint(inidata->ScreenSharing.Port);
}
//-----------------------------------------------------------------------------
void __fastcall TSip::getTransport(void* INIDATA)
{
#ifdef SIP_Transport_TLS
sip_transport = Sip_Transport_TLS;
TRegistry& regKey = *new TRegistry();
regKey.RootKey = ROOT_KEY;
bool keyGood = regKey.OpenKey(key_name.c_str(),false);
if(!keyGood)
  keyGood = regKey.OpenKey(key_name.c_str(),true);
if(keyGood)
  {
  keyGood = regKey.OpenKey(transport_key_name.c_str(),false);
  if(!keyGood)
     keyGood = regKey.OpenKey(transport_key_name.c_str(),true);
  if(keyGood)
    {
    string old_trn = regKey.ReadString(sip_transp_name.c_str()).c_str();
    if(old_trn != sconst_TLS)
      regKey.WriteString(sip_transp_name.c_str(),sconst_TLS.c_str());
    }
  regKey.CloseKey();
  }
delete &regKey;
return;
#else
bool transp_det = false;
TRegistry& regKey = *new TRegistry();
regKey.RootKey = ROOT_KEY;
bool keyGood = regKey.OpenKey(key_name.c_str(),false);
if(keyGood)
  {
  keyGood = regKey.OpenKey(transport_key_name.c_str(),false);
  if(keyGood)
    {
    string transp = regKey.ReadString(sip_transp_name.c_str()).c_str();
    if(!transp.empty())
      {
      if(transp == sconst_UDP)
        {
        sip_transport = Sip_Transport_UDP;
        transp_det = true;
        }
      else if(transp == sconst_TCP)
        {
        sip_transport = Sip_Transport_TCP;
        transp_det = true;
        }
      else if(transp == sconst_TLS)
        {
        sip_transport = Sip_Transport_TLS;
        transp_det = true;
        }
      else if(transp == sconst_TUNNEL)
        {
        sip_transport = Sip_Transport_TUNNEL;
        transp_det = true;
        }
      else if(transp == sconst_AUTO)
        {
        sip_transport     = Sip_Transport_UDP;
        Sip_TransportAuto = true;
        transp_det = true;
        }
      }
    regKey.CloseKey();
    }
  }
delete &regKey;
if(transp_det)return;
TIniData* inidata = (TIniData*)INIDATA;
if(inidata->TransportIniData.SipTransport == sconst_UDP)
   sip_transport = Sip_Transport_UDP;
else if(inidata->TransportIniData.SipTransport == sconst_TCP)
   sip_transport = Sip_Transport_TCP;
else if(inidata->TransportIniData.SipTransport == sconst_TLS)
   sip_transport = Sip_Transport_TLS;
else if(inidata->TransportIniData.SipTransport == sconst_TUNNEL)
   sip_transport = Sip_Transport_TUNNEL;
else if(inidata->TransportIniData.SipTransport == sconst_AUTO)
   {
   sip_transport = Sip_Transport_UDP;
   Sip_TransportAuto = true;
   }
#endif
}
//---------------------------------------------------------------------------
void __fastcall TSip::getSignalFromIniData(void* INIDATA)
{
TIniData* inidata = (TIniData*)INIDATA;
if((inidata->SignalIniData.AlertingType == "us")||(inidata->SignalIniData.AlertingType == "US"))
   Signal.at = AlertingType_US;
else if((inidata->SignalIniData.AlertingType == "ru")||(inidata->SignalIniData.AlertingType == "RU"))
   Signal.at = AlertingType_RU;
}
//---------------------------------------------------------------------------
#ifndef RTP_exsCreateUDPSocket_ADDR_ANY
void __fastcall TSip::getMediaFromIniData(void* INIDATA)
{
TIniData* inidata = (TIniData*)INIDATA;
vmpb.fport = strtoint(inidata->MediaIniData.MStartPort);
vmpb.eport = strtoint(inidata->MediaIniData.MEndPort);
vmpb.step  = strtoint(inidata->MediaIniData.MInt);
if(vmpb.fport > 0xFFFF)
   vmpb.fport = 32032;
if(vmpb.eport > 0xFFFF)
   vmpb.eport = 0xFFFF;
if(vmpb.eport)
  if(vmpb.eport <= vmpb.fport)
     vmpb.eport = 0xFFFF;
if(vmpb.step > 32)
   vmpb.step = 32;
else if(vmpb.step < 4)
   vmpb.step = 4;
vmpb.lbp = vmpb.fport;
}
#endif
//---------------------------------------------------------------------------
void __fastcall TSip::getG729ParFromIniData(void* INIDATA)
{
TIniData* inidata = (TIniData*)INIDATA;
string s = inidata->G729IniData.annexb;
lowercase(s);
if((s == "yes")||(s == "1"))
   CodecsIni.G729Ini.annexb = true;
}
//---------------------------------------------------------------------------
void __fastcall TSip::generateFromTag(TOutputSipBuf* ospb)
{
int a = getInitTag();
if(a < 0)
   a = -a;
ospb->FromTag = inttostr(a);
}
//---------------------------------------------------------------------------
//void __fastcall TSip::generateToTag(TSipParsBuf* spb)
void __fastcall TSip::generateToTag(BaseExchangeBlock* spb)
{
int a = getInitTag();
if(a < 0)
   a = -a;
spb->totag = inttostr(a);
}
//---------------------------------------------------------------------------
void __fastcall TSip::prepareToTag_Final(BaseExchangeBlock* bb)
{
if(bb->To.find("tag=")==-1)
   bb->To += SEMICOLON + "tag=" + bb->totag + crlf;
}
//---------------------------------------------------------------------------
void __fastcall TSip::prepareFromTag_Final(TOutputSipBuf* ospb)
{
if(ospb->from.find("tag=")==-1)
   ospb->from  += SEMICOLON + "tag=" + ospb->totag + crlf;
}
//----------------------------------------------------------------------------
void __fastcall TSip::generateCallID(TOutputSipBuf* ospb)
{
int a = getInitCallID();
if(a<0)
   a = -a;
TDateTime dt=dt.CurrentDateTime();
unsigned short year;
unsigned short month;
unsigned short day;
dt.DecodeDate(&year,&month,&day);
unsigned short hour;
unsigned short min;
unsigned short sec;
unsigned short msec;
string str;
dt.DecodeTime(&hour,&min,&sec,&msec);
char buf[25];
str+=string(itoa(msec,buf,10));
if(sec<10)
  str+="0"+string(itoa(sec,buf,10));
else
  str+=string(itoa(sec,buf,10));
if(day<10)
  str+="0"+string(itoa(day,buf,10));
else
  str+=string(itoa(day,buf,10));
if(month<10)
  str+="0"+string(itoa(month,buf,10));
else
  str+= string(itoa(month,buf,10));
str+= string(itoa(year,buf,10));
if(hour<10)
  str+="0"+string(itoa(hour,buf,10));
else
  str+=string(itoa(hour,buf,10));
if(min<10)
  str+="0"+string(itoa(min,buf,10));
else
  str+=string(itoa(min,buf,10));
int ftaglen = ospb->FromTag.length();
if(ftaglen < 4)
  ospb->CallID = str + ospb->FromTag + inttostr(a);
else
 {
 int h_ftaglen = ftaglen/2;
 string h_str = ospb->FromTag.substr(h_ftaglen,ftaglen-h_ftaglen);
 ospb->CallID = str + h_str + inttostr(a);
 }
}
//---------------------------------------------------------------------------
void __fastcall TSip::prepareRequestLine_REGISTER(TOutputSipBuf* ospb)
{
ospb->requestline = "REGISTER" + WS + "sip:" + SipProxy.IPAddr + WS + SipVers + crlf;
}
//---------------------------------------------------------------------------
void __fastcall TSip::prepareRequestLine_SUBSCRIBE(TOutputSipBuf* ospb,TContact& contact)
{
ospb->requestline = "SUBSCRIBE" + WS + "sip:" + contact.name;
if(contact.name.find("@")==-1)
  ospb->requestline += "@" + Account.get_domain();
ospb->requestline += WS + SipVers + crlf;
}
//---------------------------------------------------------------------------
void __fastcall TSip::prepareRequestLine_MESSAGE(TOutputSipBuf* ospb,TContact* Contact)
{
ospb->requestline = "MESSAGE" + WS + "sip:" + Contact->name;
if(Contact->name.find("@")==-1)
  ospb->requestline += "@" + Account.get_domain();
ospb->requestline += WS + SipVers + crlf;
}
//---------------------------------------------------------------------------
void __fastcall TSip::prepareRequestLine_INVITE(const string& calledname, TOutputSipBuf* ospb)
{
ospb->requestline = "sip:" + calledname;
if(calledname.find("@") == -1)
   ospb->requestline += "@" + Account.get_domain();
ospb->RequestUri = ospb->requestline;  //Необходимо, если потребуется переадресация из разговора
ospb->requestline += WS + SipVers + crlf;
}
//---------------------------------------------------------------------------
void __fastcall TSip::prepareViaHeader(TOutputSipBuf* ospb)
{
::EnterCriticalSection(&tcp_t_cs);
  if(ss_tcp_t)
     ospb->via = "Via:" + WS + SipVersTcp + WS;
  else
     ospb->via = "Via:" + WS + SipVersUdp + WS;
::LeaveCriticalSection(&tcp_t_cs);

TIPAddress* ipaddr = NULL;
if(!isStunAssigned())
   ipaddr = &MappedAddress;
else
   ipaddr = getLastNIC();
if(ipaddr)
   ospb->via += ipaddr->IPAddr;
ospb->via += COLON + inttostr(siphostport) + SEMICOLON + "rport" + crlf;
}
//-----------------------------------------------------------------------------
void __fastcall TSip::Prepare_Via_Header_With_Branch(TOutputSipBuf* ospb)
{
::EnterCriticalSection(&tcp_t_cs);
  if(ss_tcp_t)
     ospb->via = "Via:" + WS + SipVersTcp + WS;
  else
     ospb->via = "Via:" + WS + SipVersUdp + WS;
::LeaveCriticalSection(&tcp_t_cs);

TIPAddress* ipaddr = NULL;
if(!isStunAssigned())
   ipaddr = &MappedAddress;
else
   ipaddr = getLastNIC();
if(ipaddr)
   ospb->via += ipaddr->IPAddr;
ospb->via += COLON + inttostr(siphostport) + SEMICOLON; // + "rport" + crlf;

SYSTEMTIME systime;
::GetSystemTime(&systime);
const string s1 = inttohexstr(prep_sub_branch(&systime,1));
const string s2 = inttohexstr(prep_sub_branch(&systime,2));
ospb->via += "branch=" + BranchMagicCck + "-" + s1 + "-" + s2 + "-" + inttohexstr(getBranch()) + ";rport" + crlf;
}
//------------------------------------------------------------------------------
void __fastcall TSip::prepareCallID_REGISTER(TOutputSipBuf* ospb)
{
ospb->callid = "Call-ID:" + WS;
TIPAddress* ipaddr = NULL;
if(!isStunAssigned())
   ipaddr = &MappedAddress;
else
   ipaddr = getLastNIC();
if(ipaddr)
  {
  ospb->callid += ospb->CallID + "@" + ipaddr->IPAddr;
  ospb->CallID = ospb->CallID + "@" + ipaddr->IPAddr;
  crh.setCurrentCallID(ospb->CallID);
  }
ospb->callid+=crlf;
}
//-----------------------------------------------------------------------------
void __fastcall TSip::prepareCallID_SUBSCRIBE(TOutputSipBuf* ospb)
{
ospb->callid = "Call-ID:" + WS;
TIPAddress* ipaddr = NULL;
if(!isStunAssigned())
   ipaddr = &MappedAddress;
else
   ipaddr = getLastNIC();
if(ipaddr)
  {
  ospb->callid += ospb->CallID + "@" + ipaddr->IPAddr;
  ospb->CallID = ospb->CallID + "@" + ipaddr->IPAddr;
  }
ospb->callid+=crlf;
}
//-----------------------------------------------------------------------------
void __fastcall TSip::prepareCallID_MESSAGE(TOutputSipBuf* ospb)
{
ospb->callid = "Call-ID:" + WS;
TIPAddress* ipaddr = NULL;
if(!isStunAssigned())
   ipaddr = &MappedAddress;
else
   ipaddr = getLastNIC();
if(ipaddr)
  {
  ospb->callid += ospb->CallID + "@" + ipaddr->IPAddr;
  ospb->CallID = ospb->CallID + "@" + ipaddr->IPAddr;
  }
ospb->callid+=crlf;
}
//-----------------------------------------------------------------------------
void __fastcall TSip::prepareCallID_INVITE(TOutputSipBuf* ospb)
{
ospb->callid = "Call-ID:" + WS;
TIPAddress* ipaddr = NULL;
if(!isStunAssigned())
   ipaddr = &MappedAddress;
else
   ipaddr = getLastNIC();
if(ipaddr)
  {
  ospb->callid += ospb->CallID + "@" + ipaddr->IPAddr;
  ospb->CallID = ospb->CallID + "@" + ipaddr->IPAddr;
  }
ospb->callid += crlf;
}
//-----------------------------------------------------------------------------
void __fastcall TSip::prepareCallID_Common(TOutputSipBuf* ospb,const string& S)
{
ospb->callid = "Call-ID:" + WS + S + crlf;
}
//-----------------------------------------------------------------------------
void __fastcall TSip::prepare_Current_REGISTER_CallID(TOutputSipBuf* ospb)
{
ospb->callid = "Call-ID:" + WS + crh.getCurrentCallID() + crlf;
}
//------------------------------------------------------------------------------
void __fastcall TSip::prepareMaxForwards(int a,TOutputSipBuf* ospb)
{
ospb->maxforwards = "Max-Forwards" + COLON + WS + inttostr(a) + crlf;
}
//-----------------------------------------------------------------------------
void __fastcall TSip::prepareAccept(TOutputSipBuf* ospb)
{
ospb->accept = "Accept" + COLON + WS + "multipart/related, application/rlmi+xml, application/pidf+xml" + crlf;
}
//-----------------------------------------------------------------------------
void __fastcall TSip::prepareEvent(TOutputSipBuf* ospb,const string& event)
{
ospb->event = "Event" + COLON + WS + event + crlf;
}
//-----------------------------------------------------------------------------
void __fastcall TSip::prepareAllow(TOutputSipBuf* ospb)
{
ospb->allow = "Allow: INVITE, ACK, CANCEL, OPTIONS, BYE, REFER, NOTIFY, MESSAGE, SUBSCRIBE, INFO" + crlf;
}
//-----------------------------------------------------------------------------
void __fastcall TSip::prepareCSeq(int a,const string& MSG,TOutputSipBuf* ospb)
{
ospb->curr_cseq = a;
ospb->cseq = "CSeq" + COLON + WS + inttostr(a) + WS + MSG + crlf;
}
//-----------------------------------------------------------------------------
void __fastcall TSip::prepareExpires(int a,TOutputSipBuf* ospb)
{
ospb->expires = "Expires" + COLON + WS + inttostr(a) + crlf;
}
//-----------------------------------------------------------------------------
void __fastcall TSip::prepareContentType(TOutputSipBuf* ospb,const string& S)
{
ospb->contenttype = "Content-Type:" + WS + S + crlf;
}
//-----------------------------------------------------------------------------
void __fastcall TSip::prepareUserAgent(BaseExchangeBlock* ospb)
{
ospb->UserAgent = "User-Agent" + COLON + WS + clientname + WS + vers + crlf;
}
//------------------------------------------------------------------------------
void __fastcall TSip::prepareContentLength_0(BaseExchangeBlock* ospb)
{
ospb->ContentLength = "Content-Length" + COLON + WS + "0" + sdpboundary;
}
//------------------------------------------------------------------------------
void __fastcall TSip::prepareContact(BaseExchangeBlock* bb)
{
string username = Account.get_user_name();
int st = username.find("@");
if(st!=-1)
   username.resize(st);
bb->Contact = "Contact: <sip:"+username+"@"+MappedAddress.IPAddr+COLON+inttostr(siphostport);

::EnterCriticalSection(&tcp_t_cs);
  if(ss_tcp_t)
     bb->Contact += ";transport=TCP";
::LeaveCriticalSection(&tcp_t_cs);

bb->Contact += ">"+crlf;
}
//-----------------------------------------------------------------------------
void __fastcall TSip::prepare_Final_REGISTER_Contact(TAuthPar* auth_par, BaseExchangeBlock* ospb)
{
ospb->Contact="Contact: <sip:" + auth_par->user_name + "@" + MappedAddress.IPAddr + COLON + inttostr(siphostport) + ">" + ";expires=0" + crlf;
}
//-----------------------------------------------------------------------------
void __fastcall TSip::prepareInitialTo(const string& user_name,const string& display_user_name,const string& domain,TOutputSipBuf* ospb)
{
string DISP_USER_NAME;
if(!display_user_name.empty())
    DISP_USER_NAME = "\"" + display_user_name  + "\"";
if(domain.empty())
  ospb->To = "To:" + WS + /*DISP_USER_NAME+*/ "<sip:"+user_name+">"+crlf;
else
  ospb->To = "To:" + WS + /*DISP_USER_NAME+*/ "<sip:"+user_name+"@"+domain+">"+crlf;
}
//-----------------------------------------------------------------------------
//-- FN == true - Необходимо вставить DisplayName -----------------------------
//----------------------------------------------------------------------------- 
void __fastcall TSip::prepareFrom_COMMON(TOutputSipBuf* ospb, TAccount* account, bool FN)
{
if(FN)
  {
  string DISPLAY_NAME = account->get_displayname();
  if(!DISPLAY_NAME.empty())
    {
    int st = DISPLAY_NAME.find("@");
    if(st!=-1)
       DISPLAY_NAME.resize(st);
    DISPLAY_NAME = "\"" + DISPLAY_NAME + "\"";
    DISPLAY_NAME = ANSI_2_UTF8(DISPLAY_NAME);
    }
  ospb->from = "From:" + WS + DISPLAY_NAME + "<sip:" + account->get_user_name();
  }
else
  ospb->from = "From:" + WS + "<sip:" + account->get_user_name();
if(account->get_user_name().find("@") == -1)
   ospb->from += "@" + account->get_domain();
ospb->from += ">" + SEMICOLON + "tag=" + ospb->FromTag + crlf;
}
//-----------------------------------------------------------------------------
void __fastcall TSip::prepareFrom_REGISTER(TOutputSipBuf* ospb)
{
prepareFrom_COMMON(ospb, &Account, false);
crh.setFrom(ospb->from);
}
//------------------------------------------------------------------------------
int  __fastcall TCurrentRegisterHeaders::getCSeqRegister()
{
int a = ++CSeq_Register;
if(a > 2000000000)
   a = 1;
return a;
}
//-----------------------------------------------------------------------------
TOutputSipBuf*  __fastcall TSip::prepare_Initial_INVITE_Req(const string& called_name,
                                                            const string& display_called_name,TSdpMediaCont* smc)
{
TEventLogThread* elt = *eltp;
if(elt)
   elt->FputEvt("\nprepare_Initial_INVITE_Req " + (string)"\"" +  called_name + "\"\n",1);
TOutputSipBuf* ospb = new TOutputSipBuf;
if(ospb)
  {
  ospb->calledname             = called_name;
  ospb->cld_DisplayName        = display_called_name;
  ospb->source_of_call         = smc->src_of_call;  //pph
  ospb->source_callid          = smc->src_callid;   //pph
  switch(smc->mcs){
        case MediaCont_Subtype_Regular:
             ospb->setsls(SPS_INVITE_REQ);
             break;
        case MediaCont_Subtype_FileTransfer:
             ospb->setsls(SPS_INVITE_FILETRANSFER_REQ);
             break;
        default:ospb->setsls(SPS_INVITE_REQ);
        }
  generateFromTag(ospb);
  generateCallID(ospb);
  ospb->ToIP   = SipProxy.IPAddr;
  ospb->ToPort = SipProxy.Port;
  prepareRequestLine_INVITE(called_name,ospb);
  prepareViaHeader(ospb);
  prepareMaxForwards(70,ospb);
  prepareContact(ospb);
  int st = called_name.find("@");
  if(st == -1)
     prepareInitialTo(called_name, display_called_name, Account.get_domain(), ospb);
  else
     {
     string s;
     prepareInitialTo(called_name,s,s,ospb);
     }
  prepareFrom_COMMON(ospb,&Account,true);
  prepareCallID_INVITE(ospb);
  prepareCSeq(1,"INVITE",ospb);
  prepareAllow(ospb);
  prepareContentType(ospb,"application/sdp");
  prepareUserAgent(ospb);
  prepare_Sdp_Initial(&ospb->sdp,smc);
  #ifdef SIP_Video
  if(smc->video)
    {
    ospb->vcpar = new TVcamPar;
    if(ospb->vcpar)
      {
      ospb->vcpar->width  = smc->vcpar.width;
      ospb->vcpar->height = smc->vcpar.height;
      ospb->vcpar->fps    = smc->vcpar.fps;
      }
    }
  #endif
  }
return ospb;
}
//------------------------------------------------------------------------------
TOutputSipBuf* __fastcall TSip::prepare_Initial_REINVITE_WITH_ADD_VIDEO_Req(TExchBuf* buf, TSdpMediaCont* smc)
{
TOutputSipBuf* ospb = new TOutputSipBuf;
if(ospb)
  {
  ospb->setsls(SPS_REINVITE_WITH_ADD_VIDEO_REQ);
  ospb->calledname = buf->msg_1;
  ospb->CallID     = buf->callid;
  if(!ospb->vcpar)
      ospb->vcpar = new TVcamPar;
  if(ospb->vcpar)
    {
    ospb->vcpar->width  = smc->vcpar.width;
    ospb->vcpar->height = smc->vcpar.height;
    ospb->vcpar->fps    = smc->vcpar.fps;
    }
  }
return ospb;
}
//----------------------------------------------------------------------------
TOutputSipBuf*  __fastcall TSip::prepare_Initial_ScreenSharing_INVITE(const string& called_name,const string& sdp_str)
{
TOutputSipBuf* ospb = new TOutputSipBuf;
if(ospb)
  {
  ospb->calledname = called_name;
  ospb->setsls(SPS_INVITE_SCREENSHARING_REQ);
  generateFromTag(ospb);
  generateCallID(ospb);
  ospb->ToIP   = SipProxy.IPAddr;
  ospb->ToPort = SipProxy.Port;
  prepareRequestLine_INVITE(called_name,ospb);
  prepareViaHeader(ospb);
  prepareMaxForwards(70,ospb);
  prepareContact(ospb);
  string s;
  prepareInitialTo(called_name,s,s,ospb);
  prepareFrom_COMMON(ospb,&Account,false);
  prepareCallID_INVITE(ospb);
  prepareCSeq(1,"INVITE",ospb);
  prepareAllow(ospb);
  prepareContentType(ospb,"application/pidf+xml");
  prepareUserAgent(ospb);
  ospb->sdp.Sdp = sdp_str;
  }
return ospb;
}
//------------------------------------------------------------------------------
void __fastcall TSip::prepare_Sdp_Initial(TSdp* sdp,TSdpMediaCont* smc)
{
sdp->SdpVersion = "0";
sdp->Owner_UserName    = "sip" + WS;
sdp->SessionID         = "0"   + WS;
sdp->SessionVersion    = "0"   + WS;
sdp->Owner_NeworkType  = "IN"  + WS;
sdp->Owner_AddressType = "IP4" + WS;
sdp->SessionName       = "SIP_Call";
sdp->Connection_NetworkType = "IN"  + WS;
sdp->Connection_AddressType = "IP4" + WS;
sdp->Session_StartTime = "0" + WS;
sdp->Session_StopTime  = "0";
sdp->prepare_media(smc);
sdp->common_connection_addr  = MappedAddress.IPAddr;
sdp->Owner_Address           = MappedAddress.IPAddr;
}
//---------------------------------------------------------------------------
void __fastcall TSip::prepare_Sdp_200OK_Initial(TSdp* sdp,TSdpMediaCont* smc)
{
sdp->SdpVersion = "0";
sdp->Owner_UserName    = "sip" + WS;
sdp->SessionID         = "0"   + WS;
sdp->SessionVersion    = "0"   + WS;
sdp->Owner_NeworkType  = "IN"  + WS;
sdp->Owner_AddressType = "IP4" + WS;
sdp->SessionName       = "SIP_Call";
sdp->Connection_NetworkType = "IN"  + WS;
sdp->Connection_AddressType = "IP4" + WS;
sdp->Session_StartTime = "0" + WS;
sdp->Session_StopTime  = "0";
sdp->prepare_media(smc);
sdp->common_connection_addr  = MappedAddress.IPAddr;
sdp->Owner_Address           = MappedAddress.IPAddr;
}
//---------------------------------------------------------------------------
void __fastcall TSdp::prepare_media(TSdpMediaCont* smc)
{
if(smc)
  {
  switch(smc->mcs){
        case MediaCont_Subtype_Regular:
             if(smc->audio)
                prepare_sdp_audio(smc);
             #ifdef SIP_Video
             if(smc->video)
                prepare_sdp_video(smc);
             #endif  
             break;
        case MediaCont_Subtype_FileTransfer:
             if(!tftp)
                tftp = new TFileTransSDPAttrib;
             if(tftp)
               {
               tftp->message    = "m=message 0 TCP/MSRP *";
               tftp->session_id = "a=session-id:" + inttostr(smc->tfp.tfa.sid);
               tftp->file_name  = "a=file_name:"  + smc->tfp.tfa.file_name;
               tftp->file_size  = "a=file-size:"  + inttostr(smc->tfp.tfa.file_size);
               }
             break;
        }
  }
}
//---------------------------------------------------------------------------
void __fastcall TSdp::prepare_sdp_audio(TSdpMediaCont* smc)
{
audio.media_type     = "audio" + WS;
audio.media_protocol = "RTP/AVP";
prepare_sdp_audio_codec_list();
prepare_sdp_audio_attrib_list(smc);
}
//---------------------------------------------------------------------------
#ifdef SIP_Video
void __fastcall TSdp::prepare_sdp_video(TSdpMediaCont* smc)
{
video.media_type = "video" + WS;
video.media_protocol = "RTP/AVP"; //(m): "RTP/AVP", "image"
prepare_sdp_video_codec_list();
prepare_sdp_video_attrib_list(smc);
}
#endif
//---------------------------------------------------------------------------
void __fastcall TSdp::prepare_sdp_audio_codec_list()
{
MainFormSLS->Sip->copy_supported_audio_codecs(audio.codecs);
}
//---------------------------------------------------------------------------
#ifdef SIP_Video
void __fastcall TSdp::prepare_sdp_video_codec_list()
{
MainFormSLS->Sip->copy_supported_video_codecs(video.codecs);
}
//----------------------------------------------------------------------------
void __fastcall TSdp::select_supported_video_codecs()
{
vector<int> tmp;
vector<int>::iterator it = video.codecs.begin();
while(it != video.codecs.end())
     {
      int a = *it++;
      if(MainFormSLS->Sip->video_codec_supported(a))
        tmp.push_back(a);
     }
video.codecs = tmp;
}
#endif
//----------------------------------------------------------------------------
void __fastcall TSdp::prepare_sdp_audio_attrib_list(TSdpMediaCont* smc)
{
if(!audio.codecs.empty())
  {
  vector<string> fmtp_list;
  vector<int>::iterator it = audio.codecs.begin();
  while(it != audio.codecs.end())
       {
        switch(*it++){
             case   0:
                      break; //by default not include attrib
             case   2:audio.rtp_attr_list.push_back("a=rtpmap:2 G726-32/8000"           + crlf);
                      break;
             case   3:audio.rtp_attr_list.push_back("a=rtpmap:3 GSM/8000"               + crlf);
                      break;
             case   8:
                      break; //by default not include attrib
             case  18:audio.rtp_attr_list.push_back("a=rtpmap:18 G729/8000"             + crlf);
                      if(MainFormSLS->Sip->CodecsIni.G729Ini.annexb)
                         fmtp_list.push_back("a=fmtp:18 annexb=yes"                     + crlf);
                      break;
             case  21:audio.rtp_attr_list.push_back("a=rtpmap:21 G726-40/8000"          + crlf);
                      break;
             case  22:audio.rtp_attr_list.push_back("a=rtpmap:22 G726-24/8000"          + crlf);
                      break;
             case  23:audio.rtp_attr_list.push_back("a=rtpmap:23 G726-16/8000"          + crlf);
                      break;
             case  97:audio.rtp_attr_list.push_back("a=rtpmap:97 SPEEX/8000"            + crlf);
                      break;
             case  98:audio.rtp_attr_list.push_back("a=rtpmap:98 iLBC/8000"             + crlf);
                      break;
             case 100:audio.rtp_attr_list.push_back("a=rtpmap:100 SPEEX/16000"          + crlf);
                      break;
             case 101:audio.rtp_attr_list.push_back("a=rtpmap:101 telephone-event/8000" + crlf);
                      fmtp_list.push_back("a=fmtp:101 0-15"                             + crlf);
                      break;
             case 102:audio.rtp_attr_list.push_back("a=rtpmap:102 L16/16000"            + crlf);
                      break;
             case 105:audio.rtp_attr_list.push_back("a=rtpmap:105 SPEEX-FEC/8000"       + crlf);
                      break;
             case 106:audio.rtp_attr_list.push_back("a=rtpmap:106 SPEEX-FEC/16000"      + crlf);
                      break;
             case 107:audio.rtp_attr_list.push_back("a=rtpmap:107 BV32/16000"           + crlf);
                      break;
             case 119:audio.rtp_attr_list.push_back("a=rtpmap:119 BV32-FEC/16000"       + crlf);
                      break;
             }
       }

  if(!fmtp_list.empty())
    {
    vector<string>::iterator it_1 = fmtp_list.begin();
    while(it_1!=fmtp_list.end())
         audio.rtp_attr_list.push_back(*it_1++);
    }
  }//if(!audio.codecs.empty())
if(!smc->audio_direction.empty())
     audio.rtp_attr_list.push_back("a=" + smc->audio_direction + crlf);
}
//---------------------------------------------------------------------------
#ifdef SIP_Video
void __fastcall TSdp::prepare_sdp_video_attrib_list(TSdpMediaCont* smc)
{
if(!video.codecs.empty())
  {
  vector<string> fmtp_list;
  vector<int>::iterator it = video.codecs.begin();
  while(it != video.codecs.end())
       {
       switch(*it++){
             case  34:video.rtp_attr_list.push_back("a=rtpmap:34 H263/90000" + crlf);
                      fmtp_list.push_back("a=fmtp:34 QCIF=1 CIF=1 MaxBR=4520" + crlf);
                      break;
             case 115:video.rtp_attr_list.push_back("a=rtpmap:115 H263-1998/90000" + crlf);
                      fmtp_list.push_back("a=fmtp:115 QCIF=1 CIF=1 I=1 J=1 T=1 MaxBR=4520" + crlf);
                      break;
             case 125:video.rtp_attr_list.push_back("a=rtpmap:125 H264/90000" + crlf);
                      fmtp_list.push_back("a=fmtp:125 profile-level-id=42e00a; packetization-mode=1; max-br=452; max-mbps=11880" + crlf);
                      break;
             case 126:video.rtp_attr_list.push_back("a=rtpmap:126 H264/90000" + crlf);
                      fmtp_list.push_back("a=fmtp:126 profile-level-id=42801e; packetization-mode=1; max-br=452; max-mbps=11880" + crlf);
                      break;
             }
       }
  if(!fmtp_list.empty())
    {
    vector<string>::iterator it_1 = fmtp_list.begin();
    while(it_1!=fmtp_list.end())
         video.rtp_attr_list.push_back(*it_1++);
    }
  }//if(!video.codecs.empty())
if(!smc->video_direction.empty())
     video.rtp_attr_list.push_back("a=" + smc->video_direction + crlf);
}
#endif
//---------------------------------------------------------------------------

TOutputSipBuf* __fastcall TSip::prepare_Initial_REGISTERReq()
{
string user_name    =  Account.get_user_name();
if(user_name.empty())
   return NULL;
TOutputSipBuf* ospb = new TOutputSipBuf;
if(ospb)
  {
  ospb->calledname   = user_name;
  ospb->ac_user_name = user_name;
  ospb->ac_user_pwd  = Account.get_user_pwd();
  ospb->ac_domain    = Account.get_domain();

  ospb->setsls(SPS_INIT_REGISTER_REQ);
  generateFromTag(ospb);
  generateCallID(ospb);
  ospb->ToIP   = SipProxy.IPAddr;
  ospb->ToPort = SipProxy.Port;
  prepareRequestLine_REGISTER(ospb);
  prepareViaHeader(ospb);
  prepareMaxForwards(70,ospb);
  prepareContact(ospb);
  prepareInitialTo(Account.get_user_name(), strempty, Account.get_domain(), ospb);
  prepareFrom_REGISTER(ospb);
  prepareCallID_REGISTER(ospb);
  prepareCSeq(crh.getCSeqRegister(),"REGISTER",ospb);
  prepareExpires(regint,ospb);
  prepareAllow(ospb);
  prepareUserAgent(ospb);
  prepareContentLength_0(ospb);
  }
return ospb;
}
//---------------------------------------------------------------------------
TOutputSipBuf* __fastcall TSip::prepare_Initial_SUBSCRIBE_Req(TContact& contact,int Expires)
{
TOutputSipBuf* ospb = new TOutputSipBuf;
if(ospb)
  {
  ospb->setsls(SPS_INIT_SUBSCRIBE_REQ);
  generateFromTag(ospb);
  generateCallID(ospb);
  ospb->ToIP   = SipProxy.IPAddr;
  ospb->ToPort = SipProxy.Port;
  prepareRequestLine_SUBSCRIBE(ospb,contact);
  Prepare_Via_Header_With_Branch(ospb);
  prepareMaxForwards(70,ospb);
  prepareContact(ospb);
  int st = contact.name.find("@");
  if(st == -1)
     prepareInitialTo(contact.name, contact.full_name, Account.get_domain(), ospb);
  else
     prepareInitialTo(contact.name,contact.full_name,strempty,ospb);
  ospb->ac_user_name = contact.name;
  prepareFrom_COMMON(ospb,&Account,false);
  prepareCallID_SUBSCRIBE(ospb);
  prepareCSeq(1,"SUBSCRIBE",ospb);
  prepareExpires(Expires,ospb);
  prepareAccept(ospb);
  prepareAllow(ospb);
  prepareUserAgent(ospb);
  prepareEvent(ospb,"presence");
  prepareContentLength_0(ospb);
  }
return ospb;
}
//---------------------------------------------------------------------------
TOutputSipBuf* __fastcall TSip::prepare_Initial_Refreshing_SUBSCRIBE_Req(const TSubscrPar& sp)
{
TOutputSipBuf* ospb = new TOutputSipBuf;
if(ospb)
  {
  ospb->setsls(SPS_INIT_SUBSCRIBE_REQ);
  ospb->ToIP        = sp.ToIP;
  ospb->ToPort      = sp.ToPort;
  Prepare_Via_Header_With_Branch(ospb);
  prepareMaxForwards(70,ospb);
  prepareContact(ospb);
  prepareCSeq(sp.get_cseq(), "SUBSCRIBE", ospb);
  prepareExpires(sp.expires,ospb);
  prepareEvent(ospb,"presence");
  prepareUserAgent(ospb);
  prepareContentLength_0(ospb);
  ospb->ac_user_name = sp.name;
  ospb->requestline  = sp.RequestLine;
  ospb->To           = sp.To;
  ospb->from         = sp.From;
  ospb->callid       = "Call-ID:" + WS + sp.callid + crlf;
  }
return ospb;
}
//----------------------------------------------------------------------------
TOutputSipBuf* __fastcall TSip::prepare_regular_REGISTERReq(SipLegState sls)
{
string user_name = Account.get_user_name();
if(user_name.empty())
   return NULL;
TOutputSipBuf* ospb = new TOutputSipBuf;
if(ospb)
  {
  ospb->setsls(SPS_REGISTER_REQ);
  ospb->ToIP   = SipProxy.IPAddr;
  ospb->ToPort = SipProxy.Port;

  ospb->ac_user_name = user_name;
  ospb->ac_user_pwd  = Account.get_user_pwd();
  ospb->ac_domain    = Account.get_domain();

  prepareRequestLine_REGISTER(ospb);
  prepareViaHeader(ospb);
  prepareMaxForwards(70,ospb);
  prepareContact(ospb);
  prepareInitialTo(Account.get_user_name(), strempty, Account.get_domain(), ospb);
  ospb->from = crh.getFrom();
  prepare_Current_REGISTER_CallID(ospb);
  prepareCSeq(crh.getCSeqRegister(),"REGISTER",ospb);
  prepareExpires(regint,ospb);
  prepareAllow(ospb);
  prepareUserAgent(ospb);
  prepareContentLength_0(ospb);
  }
return ospb;
}
//---------------------------------------------------------------------------
TOutputSipBuf* __fastcall TSip::prepare_Final_REGISTERReq(TAuthPar* auth_par)
{
TOutputSipBuf* ospb = new TOutputSipBuf;
if(ospb)
  {
  ospb->setsls(SPS_FINAL_REGISTER_REQ);
  ospb->ToIP   = SipProxy.IPAddr;
  ospb->ToPort = SipProxy.Port;

  ospb->ac_user_name = auth_par->user_name;
  ospb->ac_user_pwd  = auth_par->user_pwd;
  ospb->ac_domain    = auth_par->domain;

  prepareRequestLine_REGISTER(ospb);
  prepareViaHeader(ospb);
  prepareMaxForwards(70,ospb);
  prepare_Final_REGISTER_Contact(auth_par,ospb);
  prepareInitialTo(auth_par->user_name, strempty, auth_par->domain, ospb);
  ospb->from = crh.getFrom();
  prepare_Current_REGISTER_CallID(ospb);
  prepareCSeq(crh.getCSeqRegister(),"REGISTER",ospb);
  prepareAllow(ospb);
  prepareUserAgent(ospb);
  prepareContentLength_0(ospb);
  }
return ospb;
}
//---------------------------------------------------------------------------
void __fastcall TSip::sendInitInvite(const string& name,const string& display_name,TSdpMediaCont* smc)
{
if(uac)
  {
  TOutputSipBuf* ospb = prepare_Initial_INVITE_Req(name, display_name, smc);
  if(ospb)
    {
    ospb->set_tag(MainFormSLS->Show_Outgoing_CallPanel(name, display_name, smc, NULL, 0));
    #ifdef SIP_Video
    if(smc->video)
      {
      Form4->set_video_call_tag(ospb->get_tag());
      Form4->set_leg_type(Lt_Out);
      Form3->set_video_call_tag(ospb->get_tag());
      Form3->set_leg_type(Lt_Out);
      }
    #endif
    uac->setQueue(ospb);
    updateSentQueue_1(ospb);
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TSip::sendInit_REINVITE_WITH_ADD_VIDEO(TExchBuf* buf, TSdpMediaCont* smc)
{
LegType lt = (LegType)buf->a1;
if(lt == Lt_Out)
  {
  if(uac)
    {
    TOutputSipBuf* ospb = prepare_Initial_REINVITE_WITH_ADD_VIDEO_Req(buf, smc);
    if(ospb)
      {
      ospb->set_tag(buf->tag);
      Form4->set_video_call_tag(buf->tag);
      Form4->set_leg_type(Lt_Out);
      uac->setQueue(ospb);
      updateSentQueue_1(ospb);
      }
    }
  }
else if(lt == Lt_In)
  {
  if(uas)
    {
    TOutputSipBuf* ospb = prepare_Initial_REINVITE_WITH_ADD_VIDEO_Req(buf, smc);
    if(ospb)
      {
      ospb->set_tag(buf->tag);
      Form4->set_video_call_tag(buf->tag);
      Form4->set_leg_type(Lt_Out);
      uas->setQueue(ospb);
      updateSentQueue_1(ospb);
      }
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TSip::sendInitInvite_OnReferInit(const string& name,const string& display_name,TSdpMediaCont* smc, int referred_tag)
{
if(uac)
  {
  TOutputSipBuf* ospb = prepare_Initial_INVITE_Req(name,display_name,smc);
  if(ospb)
    {
    ospb->set_tag(MainFormSLS->Show_Outgoing_CallPanel_OnRefer(name, display_name, NULL ,0, referred_tag)); //параметры -1,0 связаны с конференцией. На данный момент не определено, может ли совмещаться и как коференция и переадресация. 
    #ifdef SIP_Video
    if(smc->video)
      {
      Form4->set_video_call_tag(ospb->get_tag());
      Form4->set_leg_type(Lt_Out);
      Form3->set_video_call_tag(ospb->get_tag());
      Form3->set_leg_type(Lt_Out);
      }
    #endif
    uac->setQueue(ospb);
    updateSentQueue_1(ospb);
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TSip::send_ScreenSharing_INVITE(TCall_Panel* panel, const string& name, const string& sdp_str)
{
if(uac)
  {
  TOutputSipBuf* ospb = prepare_Initial_ScreenSharing_INVITE(name, sdp_str);
  if(ospb)
    {
    panel->screen_sharing_sender_call_id = ospb->CallID;
    uac->setQueue(ospb);
    updateSentQueue_1(ospb);
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TSip::send_ScreenSharing_INVITE_ToConference(TConfCont& ConfCont, const string& sdp_str)
{
if(uac)
  {
  TOutputSipBuf* ospb = prepare_Initial_ScreenSharing_INVITE(ConfCont.user_name, sdp_str);
  if(ospb)
    {
    ConfCont.screen_sharing_sender_call_id = ospb->CallID;
    uac->setQueue(ospb);
    updateSentQueue_1(ospb);
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TSip::sendInitInvite_OnConferenceCreate(const string& name,const string& display_name,TSdpMediaCont* smc,
                                                        TConfCont* pConfCont, int tag_conf_creator)
{
if(uac)
  {
  TOutputSipBuf* ospb = prepare_Initial_INVITE_Req(name,display_name,smc);
  if(ospb)
    {
    ospb->set_tag(MainFormSLS->Show_Outgoing_CallPanel(name, display_name, smc, pConfCont, tag_conf_creator));
    ospb->conference_participant = true;
    if(pConfCont)
       pConfCont->callid = ospb->CallID;
    #ifdef SIP_Video
    if(smc->video)
      {
      Form4->set_video_call_tag(ospb->get_tag());
      Form4->set_leg_type(Lt_Out);
      Form3->set_video_call_tag(ospb->get_tag());
      Form3->set_leg_type(Lt_Out);
      }
    #endif
    uac->setQueue(ospb);
    updateSentQueue_1(ospb);
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TSip::sendInitInvite_OnFileTransfer(void* CALL_PANEL)
{
TCall_Panel* panel = (TCall_Panel*)CALL_PANEL;
if(uac)
  {
  TSdpMediaCont smc;
  smc.mcs = MediaCont_Subtype_FileTransfer;
  smc.tfp = panel->TFP; 
  TOutputSipBuf* ospb = prepare_Initial_INVITE_Req(smc.tfp.contact.name,smc.tfp.contact.full_name,&smc);
  if(ospb)
    {
    ospb->set_tag(panel->Tag);
    uac->setQueue(ospb);
    updateSentQueue_1(ospb);
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TSip::send_180_Resp(TSipParsBuf* spb)
{
if(uas)
  {
  prepare_Initial_180Resp(spb);
  uas->setQueue(spb);
  }
}
//---------------------------------------------------------------------------
//-- implement in case auto_ans ---------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TSip::send_Create_Session_Req(TSipParsBuf* spb)
{
if(uas)
  {
  prepare_Initial_Create_Session_Req(spb);
  uas->setQueue(spb);
  }
}
//---------------------------------------------------------------------------
//-- implement in case auto_ans ---------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TSip::prepare_Initial_Create_Session_Req(TSipParsBuf* spb)
{
if(spb)
  {
  spb->sps = SPS_CREATE_SESSION_REQ;
  generateToTag(spb);
  }
}
//---------------------------------------------------------------------------
void __fastcall TSip::prepare_Initial_180Resp(TSipParsBuf* spb)
{
if(spb)
  {
  spb->sps = SPS_RINGING180_REQ;
  spb->ReqStatusLine = SipVers + WS + "180 Ringing" + crlf;
  generateToTag(spb);
  }
}
//---------------------------------------------------------------------------
TOutputSipBuf* __fastcall TSip::prepare_Disc_Out_Req(const string& callid)
{
TOutputSipBuf* ospb = new TOutputSipBuf;
if(ospb)
  {
  ospb->setsls(SPS_DISC_OUT_REQ);
  ospb->CallID = callid;
  prepareViaHeader(ospb);
  prepareUserAgent(ospb);
  prepareContentLength_0(ospb);
  }
return ospb;
}
//---------------------------------------------------------------------------
TOutputSipBuf* __fastcall TSip::prepare_Disc_In_Req(const string& callid)
{
TOutputSipBuf* ospb = new TOutputSipBuf;
if(ospb)
  {
  ospb->setsls(SPS_DISC_IN_REQ);
  ospb->CallID = callid;
  prepareViaHeader(ospb);
  prepareUserAgent(ospb);
  prepareContentLength_0(ospb);
  }
return ospb;
}
//---------------------------------------------------------------------------
TOutputSipBuf* __fastcall TSip::Prepare_202_Resp_OnSubscribe(TSipParsBuf* spb,TLegTrn* Lt)
{
TOutputSipBuf* ospb = new TOutputSipBuf;
if(ospb)
  {
  ospb->setsls(SPS_202OK_SUBSCRIBE_REQ);   //For Debug only
  ospb->ToIP   = spb->FromIP;
  ospb->ToPort = spb->FromPort;
  ospb->CallID = spb->call_id.getcallid();
  prepareContact(ospb);

  int st = spb->To.rfind(";tag=");
  if(st == -1)
    {
    st = spb->To.rfind(crlf);
    if(st != -1)
       spb->To.resize(st);
    if(Lt->mytag.empty())
      {
      TSipParsBuf temp;
      generateToTag(&temp);
      Lt->mytag = temp.totag;
      spb->To += ";tag=" + temp.totag + crlf;
      }
    else
      spb->To += ";tag=" + Lt->mytag + crlf;
    Lt->to = spb->To;
    }
  prepareUserAgent(ospb);
  prepareContentLength_0(ospb);

  ospb->s = SipVers + WS + "202" + WS + "Accepted" + crlf;
  spb->ViaSt.InsertHeaders(ospb->s);ospb->s +=
  ospb->Contact   +
  spb->To         +
  spb->From       +
  spb->CallID     +
  spb->CSeq       +
  spb->Expires    +
  ospb->UserAgent +
  ospb->ContentLength;
  }
return ospb;
}
//------------------------------------------------------------------------------
TOutputSipBuf* __fastcall TSip::Prepare_603_Resp_OnSubscribe(TSipParsBuf* spb,TLegTrn* Lt)
{
TOutputSipBuf* ospb = new TOutputSipBuf;
if(ospb)
  {
  ospb->setsls(SPS_202OK_SUBSCRIBE_REQ);   //For Debug only
  ospb->ToIP   = spb->FromIP;
  ospb->ToPort = spb->FromPort;
  ospb->CallID = spb->call_id.getcallid();
  prepareContact(ospb);

  int st = spb->To.rfind(";tag=");
  if(st == -1)
    {
    st = spb->To.rfind(crlf);
    if(st != -1)
       spb->To.resize(st);
    if(Lt->mytag.empty())
      {
      TSipParsBuf temp;
      generateToTag(&temp);
      Lt->mytag = temp.totag;
      spb->To += ";tag=" + temp.totag + crlf;
      }
    else
      spb->To += ";tag=" + Lt->mytag + crlf;
    Lt->to = spb->To;
    }
  prepareUserAgent(ospb);
  prepareContentLength_0(ospb);

  ospb->s = SipVers + WS + "603" + WS + "Decline" + crlf;
  spb->ViaSt.InsertHeaders(ospb->s);ospb->s +=
  ospb->Contact   +
  spb->To         +
  spb->From       +
  spb->CallID     +
  spb->CSeq       +
  spb->Expires    +
  ospb->UserAgent +
  ospb->ContentLength;
  }
return ospb;
}
//------------------------------------------------------------------------------
//--- pph - disc send to parallel phone ----------------------------------------
//------------------------------------------------------------------------------
void __fastcall TSip::send_call_disc_out(const string& callid, bool pph)
{
TOutputSipBuf* ospb = prepare_Disc_Out_Req(callid);
if(ospb)
  {
  if(pph)
     ospb->parallel_phone = true;
  uac->setQueue(ospb);
  updateSentQueue_1(ospb);
  }
}
//---------------------------------------------------------------------------
void __fastcall TSip::send_call_disc_in(const string& callid)
{
TOutputSipBuf* ospb = prepare_Disc_In_Req(callid);
if(ospb)
  {
  uas->setQueue(ospb);
  updateSentQueue_1(ospb);
  }
}
//---------------------------------------------------------------------------
void __fastcall TSip::sendCallDisc_In(const string& callid_in)
{
int st=callid_in.find(in_pref);
if(!st)
  {
  int len = in_pref.length();
  int Len = callid_in.length();
  if(Len > len)
    {
    string callid = callid_in.substr(len,Len-len);
    if(uas)
      {
      TOutputSipBuf* ospb = prepare_Disc_In_Req(callid);
      if(ospb)
        {
        uas->setQueue(ospb);
        updateSentQueue_1(ospb);
        }
      }
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TSip::sendInitial_Uac_Rtp_Sequence(MediaPacketType mpt,TRemoteMedia* rm)
{
TOutputSipBuf* ospb = NULL;
TOutputSipBuf* ospb_rtcp = NULL;
if(mpt == RTP_AUDIO_MPT)
  {
  ospb      = prepare_init_rtp_audio_seq__uac(rm);
  ospb_rtcp = prepare_init_rtcp_audio_seq__uac(rm);
  }
#ifdef SIP_Video
else if(mpt == RTP_VIDEO_MPT)
  ospb = prepare_init_rtp_video_seq(rm);
#endif
if(ospb)
  {
  if(uac)
    {
    uac->setQueue(ospb);
    updateSentQueue_1(ospb);
    if(ospb_rtcp)
      {
      uac->setQueue(ospb_rtcp);
      updateSentQueue_1(ospb_rtcp);
      }
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TSip::sendInitial_Uas_Rtp_Sequence(MediaPacketType mpt,TLegTrn* Lt)
{
if(Lt)
  {
   Lt->prepare_init_rtp_seq__uas(this,mpt);
   if(uas)
     {
     if(mpt == RTP_AUDIO_MPT)
       {
       TOutputSipBuf* ospb = new TOutputSipBuf;
       if(ospb)
         {
         ospb->setsls(SPS_INIT_RTP_AUDIO_SEQ);
         ospb->CallID = Lt->call_id.getcallid();
         uas->setQueue(ospb);
         updateSentQueue_1(ospb);
         }
       Lt->prepare_init_rtcp_audio_seq__uas(this);
       ospb = new TOutputSipBuf;
       if(ospb)
         {
         ospb->setsls(SPS_INIT_RTCP_AUDIO_SEQ);
         ospb->CallID = Lt->call_id.getcallid();
         uas->setQueue(ospb);
         updateSentQueue_1(ospb);
         }
       } //if(mpt == RTP_AUDIO_MPT)
     else if(mpt == RTP_VIDEO_MPT)
       {
       TOutputSipBuf* ospb = new TOutputSipBuf;
       if(ospb)
         {
         ospb->setsls(SPS_INIT_RTP_VIDEO_SEQ);
         ospb->CallID = Lt->call_id.getcallid();
         uas->setQueue(ospb);
         updateSentQueue_1(ospb);
         }
       }
     }
  }
}
//---------------------------------------------------------------------------
TOutputSipBuf* __fastcall TSip::prepare_init_rtp_audio_seq__uac(TRemoteMedia* rm)
{
TOutputSipBuf* ospb = new TOutputSipBuf;
if(ospb)
  if(rm)
    {
    ospb->setsls(SPS_INIT_RTP_AUDIO_SEQ);
    ospb->ToIP             = rm->audio_ipaddr;
    ospb->ToPort           = rm->audio_port;
    ospb->sdp.audio.codecs = rm->audio_codecs;
    ospb->CallID           = rm->callid;
    if(!ospb->irp)
        ospb->irp = new TInitRtpPacket;
    if(ospb->irp)
      {
      ospb->irp->initTimeStamp = GetTickCount();
      ospb->irp->initSeqNumber = get_random32(0) & 0xFFFF;
      ospb->irp->sourceId      = get_random32(1);
      }
    }
return ospb;
}
//---------------------------------------------------------------------------
TOutputSipBuf* __fastcall TSip::prepare_init_rtcp_audio_seq__uac(TRemoteMedia* rm)
{
TOutputSipBuf* ospb = new TOutputSipBuf;
if(ospb)
  if(rm)
    {
    ospb->setsls(SPS_INIT_RTCP_AUDIO_SEQ);
    ospb->ToIP             = rm->audio_ipaddr;
    ospb->ToPort           = rm->audio_port + 1;
    ospb->CallID           = rm->callid;
    }
return ospb;    
}
//----------------------------------------------------------------------------
#ifdef SIP_Video
TOutputSipBuf* __fastcall TSip::prepare_init_rtp_video_seq(TRemoteMedia* rm)
{
TOutputSipBuf* ospb = new TOutputSipBuf;
if(ospb)
  {
  if(rm)
    {
    ospb->setsls(SPS_INIT_RTP_VIDEO_SEQ);
    ospb->ToIP             = rm->video_ipaddr;
    ospb->ToPort           = rm->video_port;
    ospb->sdp.video.codecs = rm->video_codecs;
    ospb->CallID           = rm->callid;
    if(!ospb->irp)
        ospb->irp = new TInitRtpPacket;
    if(ospb->irp)
      {
      ospb->irp->initTimeStamp = GetTickCount();
      ospb->irp->initSeqNumber = get_random32(2) & 0xFFFF;
      ospb->irp->sourceId      = get_random32(3);
      }
    }
  }
return ospb;
}
#endif
//---------------------------------------------------------------------------
void __fastcall TSip::initRegistrationProc()
{
TOutputSipBuf* ospb = prepare_Initial_REGISTERReq();
if(ospb)
  {
  ospb->s = ospb->requestline +
            ospb->via         +
            ospb->maxforwards +
            ospb->Contact     +
            ospb->To          +
            ospb->from        +
            ospb->callid      +
            ospb->cseq        +
            ospb->expires     +
            ospb->allow       +
            ospb->UserAgent   +
            ospb->ContentLength;
  if(uac)
    {
    uac->setQueue(ospb);
    updateSentQueue_1(ospb);
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TSip::init_SUBSCRIBE_Proc(TContact& contact,int Expires)
{
if(uac)
  {
  TOutputSipBuf* ospb = prepare_Initial_SUBSCRIBE_Req(contact, Expires);
  if(ospb)
    {
    ospb->s = ospb->requestline +
              ospb->via         +
              ospb->maxforwards +
              ospb->Contact     +
              ospb->To          +
              ospb->from        +
              ospb->callid      +
              ospb->cseq        +
              ospb->expires     +
              ospb->accept      +
              ospb->allow       +
              ospb->UserAgent   +
              ospb->event       +
              ospb->ContentLength;
    uac->setQueue(ospb);
    updateSentQueue_1(ospb);
    } //if(ospb)
  } //if(uac)
}
//---------------------------------------------------------------------------
void __fastcall TSip::init_Refreshing_SUBSCRIBE_Proc(const TSubscrPar& sp)
{
if(uac)
  {
  TOutputSipBuf* ospb = prepare_Initial_Refreshing_SUBSCRIBE_Req(sp);
  if(ospb)
    {
    ospb->s = ospb->requestline +
              ospb->via         +
              ospb->maxforwards +
              ospb->Contact     +
              ospb->To          +
              ospb->from        +
              ospb->callid      +
              ospb->cseq        +
              ospb->expires     +
              ospb->UserAgent   +
              ospb->event       +
              ospb->ContentLength;

    TLegTrn* Lt = new TLegTrn(Lt_Out);
    if(Lt)
      {
      Lt->state        = ospb->getsls();
      Lt->tousername   = ospb->ac_user_name;
      Lt->ac_user_name = ospb->ac_user_name;
      Lt->remoteip   = ospb->ToIP;
      Lt->remoteport = ospb->ToPort;
      Lt->mytag      = ospb->FromTag;
      Lt->call_id.setprimcallid(sp.callid);
      ospb->CallID   = sp.callid;
      if(uac->insertLegTrn(ospb->CallID,Lt))
         uac->InitResendProc(ospb,Lt);
      else
         delete Lt;                  // This dialog already exists
      }

    uac->setQueue(ospb);
    updateSentQueue_1(ospb);
    } //if(ospb)
  }  //if(uac)
}
//---------------------------------------------------------------------------
void __fastcall TSip::reset_SUBSCRIPTION(const string& name)
{
string s = "\nreset_SUBSCRIPTION(): delete subscription to " + name;
Log(s);
Contacts.SS.del_subscribed_contact(name);
Contacts.AS.del_subscribed_contact(name);
}
//---------------------------------------------------------------------------
void __fastcall TSip::reset_OLD_init_NEW_SUBSCRIPTION(const string& name)
{
string s = "\nreset_OLD_init_NEW_SUBSCRIPTION(): delete subscription to " + name;
Log(s);
Contacts.SS.del_subscribed_contact(name);
Contacts.AS.del_subscribed_contact(name);
TContact contact(-1);
if(Contacts.get_contact_copy_by_user_name(contact, name))
   init_SUBSCRIBE_Proc(contact, contact.subscription_expires);
}
//---------------------------------------------------------------------------
void __fastcall TSip::regularRegistrationProc(SipLegState sls)
{
TOutputSipBuf* ospb = prepare_regular_REGISTERReq(sls);
if(ospb)
  {
  ospb->s = ospb->requestline +
            ospb->via         +
            ospb->maxforwards +
            ospb->Contact     +
            ospb->To          +
            ospb->from        +
            ospb->callid      +
            ospb->cseq        +
            ospb->expires     +
            ospb->allow       +
            ospb->UserAgent   +
            ospb->ContentLength;
  if(uac)
    {
    uac->setQueue(ospb);
    updateSentQueue_1(ospb);
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TSip::finalRegistrationProc(TAuthPar* auth_par)
{
TOutputSipBuf* ospb = prepare_Final_REGISTERReq(auth_par);
if(ospb)
  {
  ospb->s = ospb->requestline +
            ospb->via         +
            ospb->maxforwards +
            ospb->Contact     +
            ospb->To          +
            ospb->from        +
            ospb->callid      +
            ospb->cseq        +
            ospb->allow       +
            ospb->UserAgent   +
            ospb->ContentLength;
  if(uac)
    {
    uac->setQueue(ospb);
    updateSentQueue_1(ospb);
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TSip::updateSentQueue_1(void* opb)
{
::EnterCriticalSection(&sip_sent_cs);
  sip_sent.push_back(opb);
::LeaveCriticalSection(&sip_sent_cs);
getSent_1();
}
//------------------------------------------------------------------------------
void __fastcall TSip::getSent_1()
{ //delete begin with end because fist element SPS_KEEP_ALIVE  getReferenceCount() always > 0
::EnterCriticalSection(&sip_sent_cs);
  deque<void*>::iterator it = sip_sent.begin();
  while(it != sip_sent.end())
       {
       BaseExchangeBlock* opb = (BaseExchangeBlock*)(*it);
       if(opb->getReferenceCount() < 1)
         {
         exsDeleteSentBlock(opb);
         sip_sent.erase(it);   //with reverse_iterator must be --
         it = sip_sent.begin();
         }
       else
         it++;
       }
::LeaveCriticalSection(&sip_sent_cs);
}
//------------------------------------------------------------------------------
/*
void __fastcall TSip::getSent_1()
{ //delete begin with end because fist element SPS_KEEP_ALIVE  getReferenceCount() always > 0
::EnterCriticalSection(&sip_sent_cs);
  deque<void*>::reverse_iterator it = sip_sent.rbegin();
  while(it != sip_sent.rend())
       {
       BaseExchangeBlock* opb = (BaseExchangeBlock*)(*it);
       if(opb->getReferenceCount() < 1)
         {
         exsDeleteSentBlock(opb);
         sip_sent.erase(--it.base());   //with reverse_iterator must be --
         it = sip_sent.rbegin();
         }
       else
         it++;
       }
::LeaveCriticalSection(&sip_sent_cs);
}
*/
//------------------------------------------------------------------------------
int __fastcall TSip::getSentSize_1()
{
int rv;
::EnterCriticalSection(&sip_sent_cs);
  rv = sip_sent.size();
::LeaveCriticalSection(&sip_sent_cs);
return rv;
}
//------------------------------------------------------------------------------
void __fastcall TSip::printSentBlocks(string& s)
{
::EnterCriticalSection(&sip_sent_cs);
  deque<void*>::iterator it = sip_sent.begin();
  while(it != sip_sent.end())
       {
       BaseExchangeBlock* opb = (BaseExchangeBlock*)(*it);
       switch(opb->getBlockType()){
            case TOutputSipBuf_BLOCKTYPE:{
                 s+="\nTOutputSipBuf ";
                 TOutputSipBuf* ospb = (TOutputSipBuf*)opb;
                 SipLegStateToStr(s,ospb->getsls());
                 break;
                 }
            case TSipParsBuf_BLOCKTYPE:
                 s+="\nTSipParsBuf ";
                 break;
            case TOutPutUdpBlock_BLOCKTYPE:
                 s+= "\nTOutPutUdpBlock ";
                 break;
            case TWaveOutPutBuf_BLOCKTYPE:
                 s+="\nTWaveOutPutBuf ";
                 break;
            }
       s += WS + "ReferenceCount" + WS + inttostr(opb->getReferenceCount());
       it++;
       }
::LeaveCriticalSection(&sip_sent_cs);
}
//------------------------------------------------------------------------------
void __fastcall TSip::delete_SipRecvTunnelThread()
{
::EnterCriticalSection(&ch_transp_cs);
if(sr_tunnel_t)
  {
  so_stop();
  TSipRecvTunnelThread* SRTT = sr_tunnel_t;
  sr_tunnel_t = NULL;
  SRTT->Terminate();
  SRTT->Resume_Thread();
  SRTT->WaitFor();
  delete SRTT;
  }
else if(standby_sr_tunnel_t)
  {
  so_stop();
  TSipRecvTunnelThread* SRTT = standby_sr_tunnel_t;
  standby_sr_tunnel_t = NULL;
  SRTT->Terminate();
  SRTT->Resume_Thread();
  SRTT->WaitFor();
  delete SRTT;
  }
::LeaveCriticalSection(&ch_transp_cs);
}
//------------------------------------------------------------------------------
void __fastcall TSip::delete_SipSendTunnelThread()
{
::EnterCriticalSection(&ch_transp_cs);
if(ss_tunnel_t)
  {
  TSipSendTunnelThread* SSTT = ss_tunnel_t;
  ss_tunnel_t = NULL;
  SSTT->Terminate();
  SSTT->Resume_Thread();
  SSTT->WaitFor();
  delete SSTT;
  }
else if(standby_ss_tunnel_t)
  {
  TSipSendTunnelThread* SSTT = standby_ss_tunnel_t;
  standby_ss_tunnel_t = NULL;
  SSTT->Terminate();
  SSTT->Resume_Thread();
  SSTT->WaitFor();
  delete SSTT;
  }
::LeaveCriticalSection(&ch_transp_cs);
}
//------------------------------------------------------------------------------
void __fastcall TSip::delete_SipSendThread()
{
::EnterCriticalSection(&ch_transp_cs);
if(sst)
  {
  TSipSendThread* ST = sst;
  sst = NULL;
  ST->Terminate();
  ST->Resume_Thread();
  ST->WaitFor();
  delete ST;
  }
else if(standby_sst)
  {
  TSipSendThread* ST = standby_sst;
  standby_sst = NULL;
  ST->Terminate();
  ST->Resume_Thread();
  ST->WaitFor();
  delete ST;
  }
::LeaveCriticalSection(&ch_transp_cs);
}
//------------------------------------------------------------------------------
void __fastcall TSip::delete_SipRecvThread()
{
::EnterCriticalSection(&ch_transp_cs);
if(srt)
  {
  TSipRecvThread* RT = srt;
  srt = NULL;
  RT->Terminate();
  if(sck != INVALID_SOCKET)
    {
    closesocket(sck);
    sck = INVALID_SOCKET;
    }
  RT->Resume_Thread();
  RT->WaitFor();
  delete RT;
  }
else if(standby_srt)
  {
  TSipRecvThread* RT = standby_srt;
  standby_srt = NULL;
  RT->Terminate();
  if(sck != INVALID_SOCKET)
    {
    closesocket(sck);
    sck = INVALID_SOCKET;
    }
  RT->Resume_Thread();
  RT->WaitFor();
  delete RT;
  }
::LeaveCriticalSection(&ch_transp_cs);
}
//------------------------------------------------------------------------------
__fastcall TSip::~TSip()
{
destroy_req = true;
MainFormSLS->DestroyReq = true;
delete_SipRecvTunnelThread();
delete_SipSendTunnelThread();
if(sss)
  {
  delete sss;
  sss=NULL;
  }
delete_SipSendThread();
if(uas)
  {
  TSipUasThread* UAS = uas;
  uas=NULL;
  UAS->Terminate();
  UAS->Resume_Thread();
  UAS->WaitFor();
  delete UAS;
  }
if(uac)
  {
  TSipUacThread* UAC = uac;
  uac=NULL;
  UAC->Terminate();
  UAC->Resume_Thread();
  UAC->WaitFor();
  delete UAC;
  }
if(spt)
  {
  TSipParsThread* SPT = spt;
  spt = NULL;
  SPT->Terminate();
  SPT->Resume_Thread();
  SPT->WaitFor();
  delete SPT;
  }
if(ucs)
  {
  TUdpChannelStruct* UCS = ucs;
  ucs = NULL;
  UCS->Terminate();
  UCS->Resume_Thread();
  UCS->WaitFor();
  delete UCS;
  }
if(pst)
  {
  TPlaySoundThread* PST = pst;
  pst = NULL;
  PST->Terminate();
  PST->Resume_Thread();
  PST->WaitFor();
  delete PST;
  }

Delete_SS_TCP_T();
Delete_SR_TCP_T();

if(ss_tls_t)
  {
  TSipSendTlsThread* SS_TLS_T = ss_tls_t;
  ss_tls_t = NULL;
  SS_TLS_T->Terminate();
  SS_TLS_T->Resume_Thread();
  SS_TLS_T->WaitFor();
  delete SS_TLS_T;
  }
if(sr_tls_t)
  {
  TSipRecvTlsThread* SR_TLS_T = sr_tls_t;
  sr_tls_t = NULL;
  SR_TLS_T->Terminate();
  SR_TLS_T->Resume_Thread();
  SR_TLS_T->WaitFor();
  delete SR_TLS_T;
  }
delete_SipRecvThread();
if(sck != INVALID_SOCKET)
  {
  closesocket(sck);
  sck = INVALID_SOCKET;
  }
while(!localIP.empty())
     {
      TIPAddress* ipaddr = localIP.front();
      if(ipaddr)delete ipaddr;
      localIP.pop_front();
     }
getSent_1();
::DeleteCriticalSection(&sam_cs);
::DeleteCriticalSection(&svm_cs);
::DeleteCriticalSection(&sip_sent_cs);
::DeleteCriticalSection(&cldtc_cs);
::DeleteCriticalSection(&req_tfl_cs);
::DeleteCriticalSection(&ch_transp_cs);
::DeleteCriticalSection(&tcp_t_cs);
}
//------------------------------------------------------------------------------
void __fastcall TSip::Delete_SS_TCP_T()
{
::EnterCriticalSection(&tcp_t_cs);
if(ss_tcp_t)
  {
  TSipSendTcpThread* SS_TCP_T = ss_tcp_t;
  ss_tcp_t = NULL;
  SS_TCP_T->Terminate();
  SS_TCP_T->Resume_Thread();
  SS_TCP_T->WaitFor();
  delete SS_TCP_T;
  }
::LeaveCriticalSection(&tcp_t_cs);
}
//------------------------------------------------------------------------------
void __fastcall TSip::Delete_SR_TCP_T()
{
::EnterCriticalSection(&tcp_t_cs);
if(sr_tcp_t)
  {
  #ifdef INTRN_TCP
   TSipRecvTcpThread* SR_TCP_T = sr_tcp_t;
   sr_tcp_t = NULL;
   SR_TCP_T->Terminate();
   SOCKET SCK  = SR_TCP_T->get_sck();
   ::closesocket(SCK);
   SCK = INVALID_SOCKET;
   SR_TCP_T->WaitFor();
   delete SR_TCP_T;
  #else
  so_stop();   //Do not delete SR_TCP_T -- SUSPENDED
  TSipRecvTcpThread* SR_TCP_T = sr_tcp_t;
  sr_tcp_t = NULL;
  SR_TCP_T->Terminate();
  SR_TCP_T->WaitFor();
  delete SR_TCP_T;
  #endif
  }
::LeaveCriticalSection(&tcp_t_cs);
}
//------------------------------------------------------------------------------
void __fastcall TSip::init_default_audio_codecs()
{
::EnterCriticalSection(&sam_cs);
    supported_audio_media.push_back(0);    //G.711 ULaw
    supported_audio_media.push_back(8);    //G.711 ALaw
    supported_audio_media.push_back(18);   //G.729          работает нормально без annexb !!!
    supported_audio_media.push_back(101);  //DTMF
::LeaveCriticalSection(&sam_cs);
}
//------------------------------------------------------------------------------
void __fastcall TSip::copy_supported_audio_codecs(vector<int>& audio_codecs)
{
::EnterCriticalSection(&sam_cs);
  deque<int>::iterator it = supported_audio_media.begin();
  while(it!=supported_audio_media.end())
        audio_codecs.push_back(*it++);
::LeaveCriticalSection(&sam_cs);
}
//------------------------------------------------------------------------------
void __fastcall TSip::copy_supported_video_codecs(vector<int>& video_codecs)
{
::EnterCriticalSection(&svm_cs);
  deque<int>::iterator it = supported_video_media.begin();
  while(it != supported_video_media.end())
        video_codecs.push_back(*it++);
::LeaveCriticalSection(&svm_cs);
}
//------------------------------------------------------------------------------
bool __fastcall TSip::video_codec_supported(int a)
{
bool rv;
::EnterCriticalSection(&svm_cs);
  rv = find(supported_video_media.begin(),supported_video_media.end(),a) != supported_video_media.end() ? true : false;
::LeaveCriticalSection(&svm_cs);
return rv;
}
//-----------------------------------------------------------------------------
void __fastcall TSip::init_default_video_codecs()
{
//supported_video_media.push_back(34);    //H.263
supported_video_media.push_back(115);    //H.263+
}
//------------------------------------------------------------------------------
void __fastcall TSip::ins_CLD_tc(const string& calledname,const string& callid)
{
::EnterCriticalSection(&cldtc_cs);
cldtc.insert(TCldUserNameToCallID::value_type(calledname,out_pref + callid));
::LeaveCriticalSection(&cldtc_cs);
}
//-----------------------------------------------------------------------------
string __fastcall TSip::getCallID_CLD_tc(const string& calledname)
{
string rv;
::EnterCriticalSection(&cldtc_cs);
TCldUserNameToCallID::iterator it = cldtc.find(calledname);
if(it!=cldtc.end())
   rv=(*it).second;
::LeaveCriticalSection(&cldtc_cs);
return rv;
}
//-----------------------------------------------------------------------------
void __fastcall TSip::del_CLD_tc(const string& calledname)
{
::EnterCriticalSection(&cldtc_cs);
  TCldUserNameToCallID::iterator it = cldtc.find(calledname);
  if(it!=cldtc.end())
     cldtc.erase(it);
::LeaveCriticalSection(&cldtc_cs);
}
//-----------------------------------------------------------------------------
/*
void __fastcall TSip::ins_CLNG_tc(const string& callingname,const string& callid)
{
::EnterCriticalSection(&clngtc_cs);
  clngtc.insert(TClngUserNameToCallID::value_type(callingname,in_pref + callid));
::LeaveCriticalSection(&clngtc_cs);
}
*/
//-----------------------------------------------------------------------------
/*
void __fastcall TSip::del_CLNG_tc(const string& callingname,const string& callid)
{
::EnterCriticalSection(&clngtc_cs);
  TClngUserNameToCallID::iterator it = clngtc.find(callingname);
  while(it!=clngtc.end())
       {
       if((*it).first == callingname)
         if((*it).second == callid)
           {
           clngtc.erase(it);
           it = clngtc.begin();
           continue;
           }
       it++;
       }
::LeaveCriticalSection(&clngtc_cs);
}
*/
//-----------------------------------------------------------------------------
/*
string  __fastcall TSip::getCallID_CLNG_tc(const string& callingname)
{
string rv;
::EnterCriticalSection(&clngtc_cs);
  TClngUserNameToCallID::iterator it = clngtc.find(callingname);
  if(it!=clngtc.end())
     rv = (*it).second;
::LeaveCriticalSection(&clngtc_cs);
return rv;
}
*/
//-----------------------------------------------------------------------------
/*
void __fastcall TSip::getCallID_CLNG_tc_Erase(const string& callingname,vector<string>& v)
{
::EnterCriticalSection(&clngtc_cs);
  TClngUserNameToCallID::iterator it = clngtc.begin();
  while(it!=clngtc.end())
       {
       if((*it).first == callingname)
         {
         v.push_back((*it).second);
         clngtc.erase(it);
         it = clngtc.begin();
         }
       else
         it++;
       }
::LeaveCriticalSection(&clngtc_cs);
}
*/
//-----------------------------------------------------------------------------
/*
void __fastcall TSip::unknownBlockType()
{
TEventLogThread* elt = *eltp;
if(elt)
  if(elt->getlog())
     log(elt,"\nError: try to delete block with unknown BLOCKTYPE ");
}
*/
//-----------------------------------------------------------------------------
void __fastcall TSip::sendUas_Decline_OnInvite(TExchBuf* buf)
{
//getCallID_CLNG_tc_Erase(buf->msg,v);
if(!buf->callid.empty())
  {
  string in_callid = in_pref + buf->callid;
  TOutputSipBuf* ospb = new TOutputSipBuf;
  if(ospb)
    {
    TMediaSession* ms = sss->GetMs_by_In_Out_Callid(in_callid);
    if(ms)
       {
       TCall_Panel* call_panel = MainFormSLS->get_Call_Panel_By_Tag(ms->getCallTag());
       if(call_panel)
         if(call_panel->get_call_state() == Call_State__Conference)
            call_panel->conference_exit(ms);
       log(*eltp,"\nDECLINE incoming callid " + ms->getCallID());
       ospb->CallID = ms->getCallID();
       }
    sss->EraseMediaSession(in_callid); //CLNG_tc erased above (in the getCallID_CLNG_tc_Erase())
    ospb->setsls(SPS_DECLINE_REQ);
    if(uas)
       uas->setQueue(ospb);
    updateSentQueue_1(ospb);
    }
  }
}
//-----------------------------------------------------------------------------
TOutputSipBuf* __fastcall TSip::prepare_Initial_ANSWER_Req(TExchBuf* buf,int call_tag)
{
TOutputSipBuf* ospb = NULL;
if(!buf->callid.empty())
  {
  string in_callid = in_pref + buf->callid;
  ospb = new TOutputSipBuf;
  if(ospb)
    {
    ospb->setsls(SPS_ANSWER_REQ);
    if(buf->parallel_phone)
      {
      ospb->parallel_phone = true;
      ospb->parallel_phone_call_id = buf->msg_1;   //parallel_phone callid
      }
    TMediaSession* ms = sss->GetMs_by_In_Out_Callid(in_callid);
    if(ms)
       {
       ms->setCallTag(call_tag);
       ospb->CallID = ms->getCallID();
       ospb->callid = in_callid;
       }
    TSdpMediaCont smc;
    #ifdef SIP_Video
    TVcamPar* vcampar = (TVcamPar*)buf->getAddBuf_Reset();
    if(vcampar)
      {
       ospb->vcpar = vcampar;
       smc.video = true;
      }
    #endif
    prepareContact(ospb);
    prepareAllow(ospb);
    prepareUserAgent(ospb);
    prepareContentType(ospb,"application/sdp");
    prepare_Sdp_Initial(&ospb->sdp,&smc);
    }
  }
return ospb;
}
//------------------------------------------------------------------------------
TOutputSipBuf* __fastcall TSip::prepare_Initial_ANSWER_OnSharingInvite_Req(TExchBuf* buf)
{
TOutputSipBuf* ospb = new TOutputSipBuf;
if(ospb)
  {
  ospb->setsls(SPS_ANSWER_ON_SHARING_INVITE_REQ);
  ospb->CallID = buf->callid;
  generateToTag(ospb);
  ospb->To     = buf->msg_1;
  prepareToTag_Final(ospb);
  prepareContact(ospb);
  prepareUserAgent(ospb);
  prepareContentLength_0(ospb);
  }
return ospb;
}
//------------------------------------------------------------------------------
TOutputSipBuf* __fastcall TSip::prepare_Initial_PRESENCE_NOTIFY_Req(TExchBuf* buf, SipLegState SLS, bool subscribed)
{
TOutputSipBuf* ospb = new TOutputSipBuf;
if(ospb)
  {
  ClientState cs = MainFormSLS->NS.get_my_network_state();
  ospb->setsls(SLS);
  ospb->calledname = buf->msg;
  ospb->CallID     = buf->callid;
  ospb->callid     = "Call-ID:" + WS + buf->callid + crlf;   //Тот же callid который был получен в сообщении SUBSCRIBE
  ospb->curr_cseq  = buf->tag_1;
  Prepare_Via_Header_With_Branch(ospb);
  prepareContact(ospb);
  if( cs != ClientState_Terminated )
    if( !subscribed )
      prepareContentType(ospb,"application/pidf+xml");
  prepareUserAgent(ospb);
  if(SLS == SPS_PRESENCE_NOTIFY_REQ)   //For SPS_PRESENCE_NOTIFY_ON_SUBSCRIBE_RCVD_REQ  next elements will be prepared in the prep_Final_Presence_Notify_Req() proc
    {
    TOutputSipBuf* add_buf = (TOutputSipBuf*)buf->getAddBuf_Reset();
    if(add_buf)
      {
      ospb->ToIP        = add_buf->ToIP;
      ospb->ToPort      = add_buf->ToPort;
      ospb->requestline = add_buf->requestline;
      ospb->To          = add_buf->To;
      ospb->from        = add_buf->from;
      delete add_buf;  //!!!!!
      }
    }

  switch(cs){
         case ClientState_Off_Line:
              ospb->subscriptionstate = "Subscription-State: active;expires=" + inttostr(buf->tag) + crlf;
           //   ospb->subscriptionstate = "Subscription-State: terminated;reason=deactivated" + crlf;
              break;
         case ClientState_Away:
              ospb->subscriptionstate = "Subscription-State: active;expires=" + inttostr(buf->tag) + crlf;
              break;
         case ClientState_DND:
              ospb->subscriptionstate = "Subscription-State: active;expires=" + inttostr(buf->tag) + crlf;
              break;
         case ClientState_Terminated:
             // ospb->subscriptionstate = "Subscription-State: terminated;reason=deactivated" + crlf;
              ospb->subscriptionstate = "Subscription-State: terminated;reason=noresource" + crlf;
              break;
         default:
              ospb->subscriptionstate = "Subscription-State: active;expires=" + inttostr(buf->tag) + crlf;
              break;
        }
  ospb->event = "Event: presence" + crlf;

  if(!subscribed)
    {
    string tuple_id;
    string person_id;
    if(cs != ClientState_Terminated)
      {
      ospb->sdp.Sdp = "<?xml version='1.0' encoding='UTF-8'?>"   +
  //    ospb->sdp.Sdp = "<?xml version='1.0' encoding='WINDOWS-1251'?>"       +
     (string)"<presence xmlns='urn:ietf:params:xml:ns:pidf' "    +
            "xmlns:dm='urn:ietf:params:xml:ns:pidf:data-model' " +
            "xmlns:rpid='urn:ietf:params:xml:ns:pidf:rpid' "     +
            "xmlns:c='urn:ietf:params:xml:ns:pidf:cipid' "       +
            "entity='sip:"  + Account.get_user_name()  + "'>";

      tuple_id  = "<tuple id="     + Account.get_tuple()  + ">";
      person_id = "<dm:person id=" + Account.get_person() + ">";
      }
    switch(cs){
       case ClientState_On_Line:
            ospb->sdp.Sdp +=  tuple_id                           +
                     (string)"<status><basic>open</basic>"       +
                             "</status>"                         +
                             "</tuple>"                          +
                              person_id;
                             if(!buf->msg_3.empty())
                                 ospb->sdp.Sdp += "<dm:note>" + buf->msg_3 + "</dm:note>";
                             else
                                 ospb->sdp.Sdp +=  (string)"<dm:note>Available</dm:note>";
                             ospb->sdp.Sdp += "</dm:person>";
                             break;
       case ClientState_Away:
            ospb->sdp.Sdp +=  tuple_id                           +
                     (string)"<status><basic>open</basic>"       +
                             "</status>"                         +
                             "</tuple>"                          +
                              person_id                          +
                             "<rpid:activities><rpid:away/></rpid:activities>";
                             if(!buf->msg_3.empty())
                                 ospb->sdp.Sdp += "<dm:note>" + buf->msg_3 + "</dm:note>";
                             else
                                 ospb->sdp.Sdp += "<dm:note>Away</dm:note>" ;
                             ospb->sdp.Sdp += "</dm:person>";
                             break;
       case ClientState_DND:
            ospb->sdp.Sdp +=  tuple_id                           +
                     (string)"<status><basic>open</basic>"       +
                             "</status>"                         +
                             "</tuple>"                          +
                              person_id                          +
                             "<rpid:activities><rpid:busy/></rpid:activities>";
                             if(!buf->msg_3.empty())
                                ospb->sdp.Sdp += "<dm:note>" + buf->msg_3 + "</dm:note>";
                              else
                                ospb->sdp.Sdp += "<dm:note>Do Not Disturb</dm:note>";
                             ospb->sdp.Sdp += "</dm:person>";
                             break;
       case ClientState_Off_Line:
            ospb->sdp.Sdp +=  tuple_id                           +
                     (string)"<status><basic>closed</basic>"     +        //!!! "closed"
                             "</status>"                         +
                             "</tuple>"                          +
                              person_id                          +
                             "<dm:note>Offline</dm:note>"        +
                             "</dm:person>";
                             break;
       case ClientState_Terminated:
         /*   ospb->sdp.Sdp +=  tuple_id                           +
                     (string)"<status><basic>open</basic>"       +
                             "</status>"                         +
                             "</tuple>"                          +
                              person_id;
                             if(!buf->msg_3.empty())
                                 ospb->sdp.Sdp += "<dm:note>" + buf->msg_3 + "</dm:note>";
                             else
                                 ospb->sdp.Sdp +=  (string)"<dm:note>Available</dm:note>";
                             ospb->sdp.Sdp += "</dm:person>"; */
                             break; 

       default:
           ospb->sdp.Sdp +=  person_id                     +
                     (string)"<dm:note>Available</dm:note>" +
                             "</dm:person>";
                             break;
       }
    if(cs != ClientState_Terminated)
       ospb->sdp.Sdp += "</presence>"; // + lf; // + crlf;
    string utf8_s = ANSI_2_UTF8(ospb->sdp.Sdp);
    ospb->sdp.Sdp = utf8_s;
    } //if(!subscribed)
  }
return ospb;
}
//-------------------------------------------------------------------------------//
//-----  Process send_Uas_NOTIFY_ON_SUBSCRIBE_Rcvd at onece after receiving SUBSCRIBE -//
//-----  from remote sip abonent ------------------------------------------------//
//-------------------------------------------------------------------------------//
void __fastcall TSip::send_Uas_NOTIFY_ON_SUBSCRIBE_Rcvd(TExchBuf* buf, bool subscribed)
{
if(uas)
  {
  TOutputSipBuf* ospb = prepare_Initial_PRESENCE_NOTIFY_Req(buf, SPS_PRESENCE_NOTIFY_ON_SUBSCRIBE_RCVD_REQ, subscribed);
  if(ospb)
    {
    uas->setQueue(ospb);
    updateSentQueue_1(ospb);
    }
  }
}
//------------------------------------------------------------------------------
void __fastcall TSip::send_Uas_NOTIFY(TSubscribedData& sd)
{
if(uas)
  {
  TExchBuf buf(WM_APP_MSG_WPARAM__NDEF);
  buf.callid = sd.callid;
  TOutputSipBuf* add_buf = new TOutputSipBuf;
  if(add_buf)
    {
    add_buf->ToIP        = sd.ToIP;
    add_buf->ToPort      = sd.ToPort;
    add_buf->requestline = sd.RequestLine;
    add_buf->To          = sd.To;
    add_buf->from        = sd.From;
    buf.setAddBuf(add_buf);
    buf.tag_1  = sd.get_cseq(); //After buf.setAddBuf(add_buf); !!!!!  setAddBuf() set tag_1 to 0
    TDateTime dt;
    dt = dt.CurrentDateTime();
    dt = sd.get_subscr_next() - dt;
    if((double)dt > 0.0)
       buf.tag = DateTimeToSec(dt);
    else
       buf.tag = 0;
    if(!sd.state_note.empty())
        buf.msg_3 = sd.state_note;
    TOutputSipBuf* ospb = prepare_Initial_PRESENCE_NOTIFY_Req(&buf, SPS_PRESENCE_NOTIFY_REQ);
    if(ospb)
      {
      TLegTrn* Lt = new TLegTrn(Lt_In);
      if(Lt)
        {
        Lt->tousername = sd.name;
        Lt->call_id.setprimcallid(sd.callid);
        if(!uas->insertLegTrn(sd.callid,Lt))
           delete Lt;                  // This dialog already exists
        }
      uas->setQueue(ospb);
      updateSentQueue_1(ospb);
      }
    }
  }
}
//----------------------------------------------------------------------------
void __fastcall TSip::sendUas_Answer_OnInvite(TExchBuf* buf)
{
try{
if(uas)
  {
  TCall_Panel* panel = new TCall_Panel(MainFormSLS);
  if(panel)
    {
    panel->Parent = MainFormSLS;
    panel->set_leg_type(Lt_In);
   // panel->Top    = MainFormSLS->Panel1->Top + MainFormSLS->Panel1->Height;
    panel->Left   = MainFormSLS->RIGHT_PANEL->Left;
    panel->Width  = MainFormSLS->Panel1->Width;
    panel->Height = MainFormSLS->Panel1->Height;///2;
    panel->Color  = (TColor)0x00EEEEEE; //clSilver;
    panel->BevelInner = bvLowered;
    panel->BevelOuter = bvRaised;
    panel->Tag        = gen_call_tag();
    panel->nick_name  = buf->msg;   //from whom received call

    panel->create_images();

    panel->create_lb();
    panel->create_lb_1();

 //   panel->lb->Color = clActiveCaption;
 //   panel->lb->Font->Color = clBlack;
    panel->lb_1->Hide();
    panel->set_call_state(Call_State__Answer);
    if(buf->parallel_phone)
      {
      panel->connected_to_pph = true;
      panel->callid_pph       = buf->msg_1;   //parallel_phone callid
      if(buf->b1)                     // Answer comes from desktop - req to delete parallel call_id !!!
        {
        panel->connected_to_pph = false;
        TMediaSession* ms = MainFormSLS->Sip->sss->GetMsOut_by_Callid(buf->msg_1);
        if(ms)
          {
          string callid = ms->getCallID();
          if(MainFormSLS->ofs->elt)
             MainFormSLS->ofs->elt->FputEvt("\nDISCONNECT callid " + callid);
          MainFormSLS->Sip->send_call_disc_out(callid, ms->get_ms_parallel_phone());
          MainFormSLS->Sip->sss->EraseMediaSession(out_pref + callid); //ms deleted !!!
          }
        buf->parallel_phone = false;  
        }
      }
    String S;
    // AnsiString S;
    try{
    TContact contact(-1);
    if(Contacts.get_contact_copy_by_user_name(contact,buf->msg))
      {
      if(!contact.full_name.empty())
         S = /* "\"" +*/ (AnsiString)contact.full_name.c_str() /* + "\"" */;
      else
         S = "\"" + (AnsiString)contact.name.c_str() + "\"";
      }
    else
      {
      if(buf->msg_5.empty())
         S = "\"" +  (AnsiString)buf->msg.c_str() + "\"";
      else
         S = (AnsiString)buf->msg_5.c_str();
      }
     }//try
    catch(Exception& e){exsSstEXCEPTION(*eltp,"__sendUas_Answer_OnInvite get_contact_copy_by_user_name()",e);}


    panel->display_name = S.c_str();
    panel->lb->Caption  = S;
    panel->lb->Top += 4;
    panel->tstmps.get_conv_start_tstmp();

    if(MainFormSLS->getIntrfStyle() == 0)
      MainFormSLS->Panel2->Top = panel->Top + panel->Height;

    #ifdef Place_OnHold_All_ActiveCalls__OnActivateNewCall
            MainFormSLS->Place_AllActiveCalls_OnHold(panel->Tag);
            MainFormSLS->ActivateAllPanels_Placed_OnHold();
            panel->lochold_img->OnMouseUp = panel->LocHold_Img__Mouse_Up;
    #endif

    TOutputSipBuf* ospb = prepare_Initial_ANSWER_Req(buf,panel->Tag);
    if(ospb)
      {
      #ifdef SIP_Video
      try{
        if(ospb->vcpar)
          {
          Form4->set_video_call_tag(panel->Tag);
          Form4->set_leg_type(Lt_In);
          Form4->Close();

          Form3->set_video_call_tag(panel->Tag);
          Form3->set_leg_type(Lt_In);
          Form3->Width  = SC_default_Remote_ScreenWidth;
          Form3->Height = SC_default_Remote_ScreenHeight;
          Form3->call_in_progress = true;
          Form3->LocalVideoPanel->Hide();
          if(!Form3->Visible)
             Form3->Remote_Video_Show();
          Form3->FormStyle = fsStayOnTop;

          Form4->Prepare_Form4_Show();

          panel->draw_active_cam_img();
          }
        }//try
       catch(Exception& e){exsSstEXCEPTION(*eltp,"__sendUas_Answer_OnInvite _Video",e);}
      #endif
      try{
      uas->setQueue(ospb);
      updateSentQueue_1(ospb);
      }//try
      catch(Exception& e){exsSstEXCEPTION(*eltp,"__sendUas_Answer_OnInvite uas->setQueue",e);}
      }
    MainFormSLS->getBottomCallPanelMargin();
    panel->disc_img->OnMouseUp    = panel->DiscImg_IncomingCall_Panel_MouseUp;
    panel->mic_img->OnMouseUp     = panel->Mic_Img__MouseUp;
    panel->cam_img->OnMouseUp     = panel->Cam_Img__MouseUp;
    panel->speak_img->OnMouseUp   = panel->Speak_Img__MouseUp;
    panel->dial_img->OnMouseUp    = panel->Dial_Img__Mouse_Up;
    panel->conf_img->OnMouseUp    = panel->Conf_Img__Mouse_Up;
    panel->refer_img->OnMouseUp   = panel->Refer_img__Mouse_Up;
    panel->screen_img->OnMouseUp  = panel->Screen_Img__Mouse_Up;
    panel->chat_img->OnMouseUp    = panel->Chat_Img__Mouse_Up;
    MainFormSLS->cps.add_panel_tag(panel->Tag,MainFormSLS->CL_DrawGrid);

    panel->panel_resize();
    panel->OnResize = panel->Call_Panel_Resize;
  ::PostMessage(MainFormSLS->Handle, CONTROL_MSG, WM_APP_MSG_WPARAM__IM__DRAWGRID_RESIZE_ON_CHANGE_CALL_COUNT, WM_APP_MSG_LPARAM__NOPARAM);
    }
  }
}//try
catch(Exception& e){exsSstEXCEPTION(*eltp,"__sendUas_Answer_OnInvite(TExchBuf* buf)",e);}
}
//-----------------------------------------------------------------------------
void __fastcall TSip::activate_Remote_Video_OnReInvite_Recv_With_Add_Video(TExchBuf* buf, SipUAThreadType uatt)
{
if(buf->isAddBuf())
  {
  TSipParsBuf* spb = (TSipParsBuf*)buf->getAddBuf_Reset();
  TMediaSession* ms = NULL;
  if(uatt == SipUAThreadType_UAC)
     ms = sss->GetMsOut_by_Callid(buf->callid);
  else if(uatt == SipUAThreadType_UAS)
     ms = sss->GetMsIn_by_Callid(buf->callid);
  if(ms)
    {
    Form3->set_video_call_tag(ms->getCallTag());
    if(uatt == SipUAThreadType_UAS)
       Form3->set_leg_type(Lt_In);
    else if(uatt == SipUAThreadType_UAC)
       Form3->set_leg_type(Lt_Out);
    Form3->Width  = SC_default_Remote_ScreenWidth;
    Form3->Height = SC_default_Remote_ScreenHeight;
  //  Form3->call_in_progress = true;
    Form3->LocalVideoPanel->Hide();
    if(!Form3->Visible)
       Form3->Remote_Video_Show();
    Form3->FormStyle = fsStayOnTop;

    spb->sps = SPS_200OK_ON_REINVITE_WITH_ADD_VIDEO_REQ;  //Используем полученный в TExchBuf TSipParsBuf* для отправки 200OK
    prepareContact(spb);
    prepareUserAgent(spb);
    TSdpMediaCont smc;
//    spb->sdp.prepare_sdp_video(&smc);
    spb->sdp.video.media_type = "video" + WS;
    spb->sdp.video.media_protocol = "RTP/AVP"; //(m): "RTP/AVP", "image"
    spb->sdp.select_supported_video_codecs();  //spb->sdp.prepare_sdp_video_codec_list();
    spb->sdp.prepare_sdp_video_attrib_list(&smc);

    if(uatt == SipUAThreadType_UAS)
      {
      if(uas)
         uas->setQueue(spb);
      }
    else if(uatt == SipUAThreadType_UAC)
      {
      if(uac)
         uac->setQueue(spb);
      }                                    //do not call updateSentQueue_1(spb);
    }
  spb->decReferenceCount();
  }
}
//-----------------------------------------------------------------------------
void __fastcall TSip::sendUas_Answer_OnSharingInvite(TExchBuf* buf)
{
try{
if(uas)
  {
  TOutputSipBuf* ospb = prepare_Initial_ANSWER_OnSharingInvite_Req(buf);
  if(ospb)
    {
    uas->setQueue(ospb);
    updateSentQueue_1(ospb);
    }
  }
}//try
catch(Exception& e){exsSstEXCEPTION(*eltp,"__sendUas_Answer_OnSharingInvite(TExchBuf* buf)",e);}
}
//------------------------------------------------------------------------------
void __fastcall TContacts::select_full_name(const string& s,int& st, int len, TContact* Cont)
{
if(st < len)
  {
  int en = s.find(";",st);
  if(en > st)
     Cont->full_name = s.substr(st,en-st);
  else
    {
    st++;
    if(st < len)
      {
      Cont->full_name = s.substr(st);
      int st = Cont->full_name.find("\n");
      if(st!=-1)
         Cont->full_name.resize(st);
      }
    }
  }
}
//-----------------------------------------------------------------------------
bool __fastcall TContacts::is_account_user_name(const string& s, int& st, int len, TAccount* Account, TContact* Cont)
{
bool rv = false;
if(Account)
 if(Cont->name == Account->get_user_name())
   {
   Account->in_contact_list = true;
   st++;
   if(st<len)
     {
     int en = s.find(";",st);
     if(en > st)
        Account->set_displayname(s.substr(st,en-st));
     }
   rv = true;
   }
return rv;
}
//-----------------------------------------------------------------------------
//--- !!!!!Used inside
//--- ::EnterCriticalSection(&contlist_cs);
//--- ::LeaveCriticalSection(&contlist_cs);
//--- only !!!!!
//-----------------------------------------------------------------------------
void __fastcall TContacts::_insert_contact_in_contact_list(TContact* Contact, bool sort)
{
contact_list.insert(TContactList::value_type(Contact->get_id(),Contact));
name_list.insert(TNameList::value_type(Contact->name,Contact->get_id()));
Contact->inc_ref_num();
if(sort)
 __sort_by_full_user_name_unsafe(); //Must be unsafe, because_insert_contact_in_contact_list() always inside CriticalSection(&contlist_cs)
}
//-----------------------------------------------------------------------------
void __fastcall TContacts::set_state_for_all_contacts(ClientState CS)
{
::EnterCriticalSection(&contlist_cs);
  TContactList::iterator it = contact_list.begin();
  while(it != contact_list.end())
       (*it++).second->cs = CS;
::LeaveCriticalSection(&contlist_cs);
}
//-----------------------------------------------------------------------------
void __fastcall TContacts::add_contact(TContact* contact,TDrawGrid* DrawGrid, bool Sort)
{
::EnterCriticalSection(&contlist_cs);
  if(contact_list.find(contact->get_id()) == contact_list.end())
     if(name_list.find(contact->name) == name_list.end())
       {
      _insert_contact_in_contact_list(contact, Sort);
       if(!contact->OWNER)
           (*pContact_list_size)++;
       else if(contact->OWNER->get_open())
           (*pContact_list_size)++;
       Update_DrawGrid_RowCount(DrawGrid);
       }
::LeaveCriticalSection(&contlist_cs);
}
//------------------------------------------------------------------------------
//-- Если удаляемый из списка контакт принадлежит нескольким подразделениям ----
//-- то удалять сконтакт можно только если get_ref_num() == 0 ------------------
//------------------------------------------------------------------------------
void __fastcall TContacts::del_contact(unsigned global_id)
{
::EnterCriticalSection(&contlist_cs);
  TContact* contact = NULL;
  TContactList::iterator it = contact_list.find(global_id);
  if(it != contact_list.end())
    {
    contact = (*it).second;
    contact->dec_ref_num();  //decrement ref_num
    if(contact->OWNER)
      {
      if(contact->OWNER->get_open())
        (*pContact_list_size)--;
      if(contact->CT == ContactType_CLIENT)
        contact->OWNER->delete_underlying_id(contact->OWNER->underlying_ids, contact->get_id());
      else if(contact->CT == ContactType_DIVISION)
        {
        contact->OWNER->delete_underlying_id(contact->OWNER->underlying_division_ids, contact->get_id());
        contact->OWNER->delete_underlying_id(contact->OWNER->underlying_ids, contact->get_id());
        }
      }
    else
      (*pContact_list_size)--;
    if(!contact->get_ref_num())
       contact_list.erase(it);
    }
  if(contact)
   if(!contact->get_ref_num())
     {
     TNameList::iterator it_name = name_list.find(contact->name);
     if(it_name != name_list.end())
        name_list.erase(it_name);
     delete contact;
     }
  if(contact_list.empty())
    {
    contact_id = 0;
    MainFormSLS->DrawGrid1->RowCount = 1;
    }
  else
    MainFormSLS->DrawGrid1->RowCount = *pContact_list_size;
::LeaveCriticalSection(&contlist_cs);
}
//------------------------------------------------------------------------------
void __fastcall TContacts::del_contact_from_actual_contact_list(TContact* Contact)
{
string user = get_current_user();
string s_cl = MainFormSLS->get_clients_dir();
s_cl += "\\" + user + "\\" + get_CONTACTS_DIR();
vector<TContact*> v;
get_all_parent_divisions(v, Contact);
make_actual_division_directory(s_cl, v);
if(::DirectoryExists(s_cl.c_str()))
  {
  s_cl += "\\" + Contact->name + ".cnt";
  if(::FileExists(s_cl.c_str()))
     ::DeleteFile(s_cl.c_str());
  }
}
//------------------------------------------------------------------------------
void __fastcall TContacts::del_group_contact_from_actual_contact_list(TContact* Contact)
{
string user = get_current_user();
string s_cl = MainFormSLS->get_clients_dir();
s_cl += "\\" + user + "\\" + get_CONTACTS_DIR() + "\\" + CHAT_GROUPS_DIR;
if(::DirectoryExists(s_cl.c_str()))
  {
  string s = Contact->name;
  int len = s.length();
  if(len > 4)
    {
    s = s.substr(4,len - 4);
    if(!s.empty())
      {
      s_cl += "\\" + s + ".gr";
      if(::FileExists(s_cl.c_str()))
         ::DeleteFile(s_cl.c_str());
      }
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TContacts::clear_contact_list()
{
::EnterCriticalSection(&contlist_cs);
  TContactList::iterator it = contact_list.begin();
  while(it != contact_list.end())
       {
       TContact* contact = (*it++).second;
       if(contact)
         delete contact;
       }
  contact_list.clear();
  name_list.clear();
  *pContact_list_size = 0;
::LeaveCriticalSection(&contlist_cs);
}
//------------------------------------------------------------------------------
unsigned __fastcall TContacts::get_next_contact_id()
{
unsigned rv;
::EnterCriticalSection(&contlist_cs);
  rv = ++contact_id;
::LeaveCriticalSection(&contlist_cs);
return rv;
}
//------------------------------------------------------------------------------
int __fastcall TContacts::get_size()
{
int rv;
::EnterCriticalSection(&contlist_cs);
  rv = contact_list.size();
::LeaveCriticalSection(&contlist_cs);
return rv;
}
//------------------------------------------------------------------------------
void __fastcall TSip::readContacts()
{
Contacts.clear_contact_list();
Contacts.Update_DrawGrid_RowCount(MainFormSLS->DrawGrid1);
MainFormSLS->DrawGrid1->Repaint();
string user = get_current_user();
string s_cl = MainFormSLS->get_clients_dir();
s_cl += "\\" + user + "\\" + CONTACTS_DIR;
AnsiString S_CL = s_cl.c_str();
if(readActualClientContacts(S_CL, NULL))
  {
  display_full_ser_name();
  return;
  }
char buf[256];     //first time after installation
FILE* f = fopen((contact_dir + "\\" + contact_file).c_str(),"rt");
if(f)
  {
  while(fgets( buf,sizeof(buf), f))
       {
       TContact* Cont = new TContact(Contacts.get_next_contact_id());
       string s = string(buf);
       int len  = s.length();
       int st   = s.find(";");
       if(st!=-1)
          {
          Cont->name = s.substr(0,st);
          if(!Account.in_contact_list)
            if(Contacts.is_account_user_name(s, st, len, &Account, Cont))
              {
              delete Cont;
              continue;
              }
          st++;
          Contacts.select_full_name(s, st, len, Cont);
          }
       if(Cont->full_name.empty())
          Cont->full_name = Cont->name;
       if(!Cont->name.empty())
         {
         Contacts.check_on_division(Cont,f);
         Contacts.add_contact(Cont,MainFormSLS->DrawGrid1,false);
         Contacts.add_to_actual_directory(Cont);
         }
       }//while
  fclose(f);
  }
display_full_ser_name();
Contacts.sort_by_full_user_name();
}
//------------------------------------------------------------------------------
void __fastcall TSip::read_contacts_time_stmp(AnsiString& file_name)
{
char buf[1024];
FILE* f = fopen(file_name.c_str(),"rt");
if(f)
  {
  if(fgets(buf,sizeof(buf),f));
    {
    string s = string(buf);
    Contacts.time_stmp = s;
    }
  fclose(f);
  }
}
//-----------------------------------------------------------------------------
void __fastcall TSip::read_contact_metadata(AnsiString& file_name,TContactData& cd)
{
char buf[1024];
int en = 0;
FILE* f = fopen(file_name.c_str(),"rt");
if(f)
  {
  if(fgets(buf,sizeof(buf),f))
    {
    string s = string(buf);
    s += ";";
    int length = s.length();
    int st = s.find(";");
    if(st != -1)
      {
      if(st)
         cd.ext_db_id = strtoint(s.substr(0,st));
      st++;
      if(st < length)
        {
        en = s.find(";",st);
        if(en != -1)
           cd.full_name = s.substr(st,en-st);
        }
      if(en > 0)
        {
        st = en;
        st++;
        if(st < length)
          {
          en = s.find(";",st);
          if(en != -1)
             cd.location = strtoint(s.substr(st,en-st));
          }
        }
       st = en;
       st++;
       if(st < length)
         {
         en = s.find(";",st);
         if(en != -1)
            cd.position = s.substr(st,en-st);
         }
       st = en;
       st++;
       if(st < length)
         {
         en = s.find(";",st);
         if(en != -1)
            cd.cos = strtoint(s.substr(st,en-st));
         }
      }
    }
  fclose(f);
  }
}
//-----------------------------------------------------------------------------
bool __fastcall TSip::readActualClientContacts(AnsiString& s_cl, TContact* ParentContact)
{
bool rv = false;
AnsiString enter_dir = s_cl;
if(::DirectoryExists(s_cl))
  {
  queue<TContactData> ext_contacts;
  int iAttributes = faAnyFile;
  TSearchRec sr;
  int retVal = FindFirst(s_cl.c_str() + (AnsiString)"\\*.*", iAttributes, sr);
  if(!retVal)
    {
    if((sr.Attr & faDirectory) == faDirectory)
      {
      if((sr.Name != ".")&&(sr.Name != ".."))
        {
        s_cl += "\\" + sr.Name;
        readActualClientContacts(s_cl,ParentContact);
        }
      }
    else
      {
      AnsiString Ext = ExtractFileExt(sr.Name);
      }
    while(FindNext(sr) == 0)
         {
         if((sr.Attr & faDirectory) == faDirectory)
           {
           if((sr.Name != ".")&&(sr.Name != ".."))
             {
             if(sr.Name.c_str() == CHAT_GROUPS_DIR)
                continue;
             TContact* Contact = new TContact(Contacts.get_next_contact_id());
             Contact->name = sr.Name.c_str();
             Contact->CT   = ContactType_DIVISION;
             if(ParentContact)
               {
               Contact->OWNER = ParentContact;
               Contact->OWNER->underlying_division_ids.push_back(Contact->get_id());
               Contact->OWNER->underlying_ids.push_back(Contact->get_id());
               }
             Contacts.add_contact(Contact, MainFormSLS->DrawGrid1, false);
             AnsiString file_name = s_cl + "\\" + sr.Name;
             readActualClientContacts(file_name, Contact);
             }
           }
         else
           {
           sr.Name = sr.Name.LowerCase();
           AnsiString Ext = ExtractFileExt(sr.Name);
           string ext  = Ext.c_str();
           string name = sr.Name.c_str();
           AnsiString file_name = s_cl + "\\" + sr.Name;
           if(ext == ".tsp") //time_stmp file
             {
             read_contacts_time_stmp(file_name);
             continue;
             }
           TContactData ContactData;
           read_contact_metadata(file_name, ContactData);
           if(ext == ".!nm")
             {
             int en = name.find(ext);
             if(en != -1)
                name.resize(en);
             int st = name.find("!");
             st++;
             if(st < en)
               {
               name = name.substr(st);
               TContact ContactCopy;
               if(Contacts.get_contact_copy_by_user_name(ContactCopy, name))
                 {
                 ContactCopy.pContact->DBI.ID    = ContactData.ext_db_id;
                 ContactCopy.pContact->full_name = ContactData.full_name;
                 }
               }
             }
           else
             {
             int st = name.find(ext);
             if(st != -1)
                name.resize(st);
             ContactData.name = name;
             if(name == MainFormSLS->Sip->Account.get_user_name())
               {
               MainFormSLS->Sip->Account.set_displayname(ContactData.full_name);
               MainFormSLS->Sip->display_full_ser_name();
               }
             else
               {
               if(!Contacts.is_contact_exists(name))  //!!!Убрать если абонент может принадлежать нескольким подразделениям
                 {
                 if(!ContactData.location)
                   {
                   TContact* Contact  = new TContact(Contacts.get_next_contact_id());
                   Contact->name      = ContactData.name;
                   Contact->DBI.ID    = ContactData.ext_db_id;
                   Contact->full_name = ContactData.full_name;
                   Contact->CL        = (TContactLocation)ContactData.location;
                   Contact->position  = ContactData.position;
                   Contact->cos       = ContactData.cos;
                   if(ParentContact)
                     {
                     Contact->OWNER = ParentContact;
                     Contact->OWNER->underlying_ids.push_back(Contact->get_id());
                     }
                   Contacts.add_contact(Contact, MainFormSLS->DrawGrid1, false);
                   }
                 else
                   ext_contacts.push(ContactData);
                 }
               }
             }
           }
         } //While(FindNext(sr) == 0)
    FindClose(sr);
    }
    while(!ext_contacts.empty())
         {
         TContactData ContactData = ext_contacts.front();
         ext_contacts.pop();
         TContact* Contact  = new TContact(Contacts.get_next_contact_id());
         Contact->name      = ContactData.name;
         Contact->DBI.ID    = ContactData.ext_db_id;
         Contact->full_name = ContactData.full_name;
         Contact->CL        = (TContactLocation)ContactData.location;
         if(ParentContact)
           {
           Contact->OWNER = ParentContact;
           Contact->OWNER->underlying_ids.push_back(Contact->get_id());
           }
         Contacts.add_contact(Contact, MainFormSLS->DrawGrid1, false);
         }

  enter_dir = enter_dir + "\\" + CHAT_GROUPS_DIR.c_str();
  readActualChatGroups(enter_dir);
  rv = true;
  }
Contacts.sort_by_full_user_name();
return rv;
}
//------------------------------------------------------------------------------
void __fastcall TSip::readActualChatGroups(AnsiString& s_cl)
{
if(::DirectoryExists(s_cl))
  {
  char buf[5] = {0xFF,0xFF,0xFF,0xFF,0};
  string pref = string(buf);
  int iAttributes = faAnyFile;
  TSearchRec sr;
  int retVal = FindFirst(s_cl.c_str() + (AnsiString)"\\*.*", iAttributes, sr);
  if(!retVal)
    {
    while(FindNext(sr) == 0)
         {
         if((sr.Attr & faDirectory) == faDirectory)
            continue;
         sr.Name          = sr.Name.LowerCase();
         string file_name = sr.Name.c_str();
         string ext       = ExtractFileExt(sr.Name).c_str();
         string name_only;
         int st = file_name.rfind(ext);
         if(st != -1)
            name_only = file_name.substr(0,st);
         if(!name_only.empty())
           {
           FILE* f = fopen((s_cl + "\\" + sr.Name).c_str(),"rt");
           if(f)
             {
             queue<string> q;
             char buf[1024];
             while(fgets(buf,sizeof(buf),f))
                   q.push(string(buf));
             fclose(f);
             if(!q.empty())
               {
               TContact* Contact = new TContact(Contacts.get_next_contact_id());
               if(Contact)
                 {
                 Contact->CT   = ContactType_GROUP;
                 Contact->name = pref + name_only;
                 string s      = q.front();
                 q.pop();
                 if(!s.empty()) //first string is the list of chat participant
                   {
                   Contact->group_full_name = s;
                   Contact->full_name       = pref + s;
                   }
                 while(!q.empty())
                      {
                      string s = q.front();
                      q.pop();
                      if(!s.empty())
                        {
                        int st = s.rfind("\n");
                        if(st != -1)
                          s.resize(st);
                        if(!s.empty())
                          {
                          TGroupName GName;
                          GName.name = s;
                          Contact->GRNS.INS_GROUP(GName);
                          }
                        }
                      }
                 Contacts.add_contact(Contact, MainFormSLS->DrawGrid1, false);
                 }
               }
             }
           }
         }
    }
  }
}
//------------------------------------------------------------------------------
bool __fastcall TSip::readPresenceComment()
{
bool rv = false;
string user = get_current_user();
string s_cl = MainFormSLS->get_clients_dir();
s_cl += "\\" + user;
if(::DirectoryExists(s_cl.c_str()))
  {
  string file_name = s_cl + "\\comment";
  FILE* F = fopen(file_name.c_str(),"rt");
  if(F){
    char buf[1024];
    if(fgets(buf,1023,F))
      {
      string s = string(buf);
      if(!s.empty())
        {
        MainFormSLS->NS.set_my_net_state_comment(s);
        AnsiString S = s.c_str();
        MainFormSLS->NSP->comment->Font->Color = (TColor)0x00E37506;
      //  MainFormSLS->NSP->comment->Caption     = "<< " + S + " >>";
        MainFormSLS->NSP->comment->Caption     = "\" " + S + " \"";
        MainFormSLS->NSP->comment->Visible     = true;
        MainFormSLS->NSP->comment->Hint        = S;
        MainFormSLS->NSP->comment->ShowHint    = true;

        MainFormSLS->NSP->Height        = 40;
        MainFormSLS->PageControl1->Top  = MainFormSLS->NSP->Top + MainFormSLS->NSP->Height + 2;
        MainFormSLS->Panel3->Top        = MainFormSLS->PageControl1->Top;

        rv = true;
        }
      }
    fclose(F);
    }
  }
return rv;
}
//------------------------------------------------------------------------------
void __fastcall TSip::readPresenceContactComment()
{
string user = get_current_user();
string s_cl = MainFormSLS->get_clients_dir();
s_cl += "\\" + user + "\\COMMENTS";
AnsiString Path = s_cl.c_str();
if(::DirectoryExists(Path))
  {
  queue<string> q;
  int iAttributes = faAnyFile;
  TSearchRec sr;
  int retVal = FindFirst(Path + "\\*.*",iAttributes,sr);    //First found directory, specified in the Path
  if(!retVal)
    {
     while(FindNext(sr) == 0)
          {
          if(sr.Name == ".")continue;
          if(sr.Name == "..")continue;
          q.push(sr.Name.c_str());
          }
    FindClose(sr);
    }
  while(!q.empty())
       {
       string s = q.front();
       q.pop();
       AnsiString file_name = Path + "\\" + s.c_str();
       FILE* f = fopen(file_name.c_str(),"rt");
       if(f)
         {
         char buf[1024];
         if(fgets(buf,sizeof(buf)-1,f))
           {
           string comment = string(buf);
           Contacts.set_contact_state_comment(s, comment, true, false, false); 
           }
         fclose(f);
         }
       }
  }
}
//------------------------------------------------------------------------------
void __fastcall TContacts::check_on_division(TContact* Contact, FILE* f)
{
int st = Contact->name.find("<");
if(st != -1)
  if(st < 3) //поправка на ошибку в размещении в списке
    if(Contact->name.find(">",st) != -1)
      {
      st++;
      int len = Contact->name.length();
      if(st < len)
        {
        if(Contact->OWNER)
          {
          Contact->OWNER->underlying_division_ids.push_back(Contact->get_id());
          Contact->OWNER->underlying_ids.push_back(Contact->get_id());
          }
        string ss = Contact->name.substr(st);
        ss = "</" + ss;
        get_division_clients(ss,Contact,f);
        }
      }
if(Contact->CT == ContactType_CLIENT)
  if(Contact->OWNER)
     Contact->OWNER->underlying_ids.push_back(Contact->get_id());
}
//-----------------------------------------------------------------------------
void __fastcall TContacts::add_to_actual_directory(TContact* Contact)
{
if(Contact->CT == ContactType_DIVISION)
   add_division_name_to_actual_directory(Contact);
else if(Contact->CT == ContactType_CLIENT)
   add_contact_name_to_actual_directory(Contact);
}
//-----------------------------------------------------------------------------
void __fastcall TContacts::get_division_clients(const string& ss, TContact* OwnerContact, FILE* f)
{
if(f)
  {
  OwnerContact->CT = ContactType_DIVISION;
  char buf[256];
  while(fgets( buf,sizeof(buf), f))
       {
       string s = string(buf);
       if(s.find(ss) != -1)       //Found end of Division. Do not include this record in ContactList
         break;
       TContact* DivCont = new TContact(get_next_contact_id());   //DivCont - member of Division Contact List
       int len  = s.length();
       int st   = s.find(";");
       if(st!=-1)
          {
          DivCont->name = s.substr(0,st);
          if(!MainFormSLS->Sip->Account.in_contact_list)
            if(is_account_user_name(s, st, len, &MainFormSLS->Sip->Account, DivCont))
              {
              delete DivCont;
              continue;
              }
          st++;
          select_full_name(s, st, len, DivCont);
          }
       if(DivCont->full_name.empty())
          DivCont->full_name = DivCont->name;
       if(!DivCont->name.empty())
         {
         DivCont->OWNER = OwnerContact; // OwnerContact - владелец DivContact - a
         check_on_division(DivCont,f);
         add_contact(DivCont,MainFormSLS->DrawGrid1,false); //Sort will be at the end load 
         add_to_actual_directory(DivCont);
         }
       } //while
  } //if(f)
}
//-----------------------------------------------------------------------------
string __fastcall TContacts::get_division_name_without_angle_brackets(const string& division_name, string& s_cl)
{
string rv;
int st = division_name.find("<");
if(st != -1)
  {
  int en = division_name.find(">");
  if(en != -1)
    {
    st++;
    if(st < en)
      rv = division_name.substr(st,en-st);
    }
  }
if(!rv.empty())
   s_cl += "\\" + rv;
return rv;
}
//-----------------------------------------------------------------------------
void __fastcall TContacts::add_division_name_to_actual_directory(TContact* Contact)
{
string user = get_current_user();
string s_cl = MainFormSLS->get_clients_dir();
s_cl += "\\" + user + "\\" + CONTACTS_DIR;
vector<TContact*> v;
get_all_parent_divisions(v, Contact);
make_actual_division_directory(s_cl,v);
string division_name = get_division_name_without_angle_brackets(Contact->name, s_cl);
if(check_directory_existence(s_cl))
  {
  s_cl += "\\" + (string)"!" + division_name + ".!nm";
  FILE* f = fopen(s_cl.c_str(),"wt");
  if(f)
    {
    string s = inttostr(Contact->DBI.ID) + ";" + Contact->full_name + ";";
    fputs(s.c_str(),f);
    fclose(f);
    }
  }
}
//------------------------------------------------------------------------------
void __fastcall TContacts::add_contact_name_to_actual_directory(TContact* Contact)
{
string user = get_current_user();
string s_cl = MainFormSLS->get_clients_dir();
s_cl += "\\" + user + "\\" + CONTACTS_DIR;

#ifdef StructuralContactsImport
vector<TContact*> v;
get_all_parent_divisions(v, Contact);
make_actual_division_directory(s_cl,v);
#endif

if(check_directory_existence(s_cl))
  {
  s_cl += "\\" + Contact->name + ".cnt";
  FILE* f = fopen(s_cl.c_str(),"wt");
  if(f)
    {
    string s = inttostr(Contact->DBI.ID) + ";" + Contact->full_name + ";";
    if(Contact->CL == Location_EXT)
      s += "1;";
    else
      s += "0;";
    s += Contact->position + ";";
    s += inttostr(Contact->cos) + ";";
    fputs(s.c_str(),f);
    fclose(f);
    }
  }
}
//-----------------------------------------------------------------------------
void __fastcall TContacts::add_group_contact_name_to_actual_directory(TContact* Contact)
{
string user = get_current_user();
string s_cl = MainFormSLS->get_clients_dir();
s_cl += "\\" + user + "\\" + CONTACTS_DIR + "\\" + CHAT_GROUPS_DIR;
if(check_directory_existence(s_cl))
  {
  string s;
  int len = Contact->name.length();
  if(len > 4) //убрать "яяяя"
    {
    s = Contact->name.substr(4, len - 4);
    s_cl += "\\" + s + ".gr";
    FILE* f = fopen(s_cl.c_str(),"wt");
    if(f)
      {
      string gr_full_name = Contact->group_full_name + "\n";
      fputs(gr_full_name.c_str(),f);
      deque<TGroupName> q;
      Contact->GRNS.GET_GROUP(q);
      while(!q.empty())
           {
           TGroupName GName = q.front();
           q.pop_front();
           string s = GName.name + "\n";
           fputs(s.c_str(),f);
           }
      fclose(f);
      }
    }
  }
}
//-----------------------------------------------------------------------------
void __fastcall TContacts::get_all_parent_divisions(vector<TContact*>& v, TContact* Contact)
{
int i = 0;
TContact* OWNER = Contact->OWNER;
while(OWNER)
     {
     v.push_back(OWNER);
     OWNER = OWNER->OWNER;
     i++;
     if(i > 100) //protection from circle
        break;
     }
}
//-----------------------------------------------------------------------------
void __fastcall TContacts::make_actual_division_directory(string& s_cl, vector<TContact*>& v)
{
vector<TContact*>::reverse_iterator it = v.rbegin();
while(it != v.rend())
     {
     TContact* Contact = *it++;
     if(Contact->name.find("<") != -1)
       get_division_name_without_angle_brackets(Contact->name, s_cl);
     else
       s_cl += "\\" + Contact->name; 
     }
}
//-----------------------------------------------------------------------------
void __fastcall TSip::display_full_ser_name()
{
if(MainFormSLS->NSP)
  if(MainFormSLS->NSP->full_user_name)
   {
   if(!Account.get_displayname().empty())
     MainFormSLS->NSP->full_user_name->Caption = Account.get_displayname().c_str();
   else
     {
     if(!Account.get_user_name().empty())
        MainFormSLS->NSP->full_user_name->Caption = Account.get_user_name().c_str();
     }
   AnsiString Name  = MainFormSLS->NSP->full_user_name->Caption;
   TCanvas* CS      = MainFormSLS->NSP->full_user_name->Canvas;
   //int comment_left = MainFormSLS->NSP->full_user_name->Left + CS->TextWidth(Name);
   //MainFormSLS->NSP->comment->Left = comment_left + 2;

   MainFormSLS->NSP->comment->Left = MainFormSLS->NSP->full_user_name->Left - 5;
   MainFormSLS->NSP->comment->Top  = MainFormSLS->NSP->full_user_name->Top + CS->TextHeight(Name) + 2;
   AnsiString S = MainFormSLS->NSP->comment->Caption;

   if(S.IsEmpty())
      MainFormSLS->NSP->comment->Visible = false;
   else
      MainFormSLS->NSP->comment->Visible = true;
   }
}
//------------------------------------------------------------------------------
//-- if OnControl == true, this func used on DrawGrid MousUp, KeyUp and so on --
//-- if OnControl == false, this func used on DrawGrid DrawCell ----------------
//------------------------------------------------------------------------------
TContact* __fastcall TContacts::get_contact_by_row(int Row, bool OnControl)
{
TContact* contact = NULL;
::EnterCriticalSection(&contlist_cs);
  contact = __get_contact_by_row_unsafe(Row, OnControl);
::LeaveCriticalSection(&contlist_cs);
return contact;
}
//------------------------------------------------------------------------------
//-----------------------  without CriticalSection  ----------------------------
//------------------------------------------------------------------------------
TContact* __fastcall TContacts::__get_contact_by_row_unsafe(int Row, bool OnControl)
{
TContact* contact = NULL;
int list_size = contact_list.size();
if(list_size)
  {
  int i=0;
  TContactList::iterator it = contact_list.begin();
  while(it != contact_list.end())
       {                /*
                       TContact* test_cont = (*it).second;
                       int aids_sz = test_cont->underlying_division_ids.size();
                       int ais_sz  = test_cont->underlying_ids.size();
                        */
       if((*it).second->OWNER)
         {
         it++;
         continue;
         }
       if(i == Row)
         {
         contact = (*it).second;
         break;
         }
       if((*it).second->CT == ContactType_DIVISION)
         {
         if(!(*it).second->get_open())
           {
           if(i == Row)
             {
             contact = (*it).second;
             break;
             }
           i++;it++;  //Do not i++.  Данный клиент, DIVISION, видим. Нижележащие невидимы Список ДАННОГО подразделения в данный момент закрыт)
           continue;
           }
         contact = (*it).second->proc_underlying_division_ids_for_cell_display(this,i,Row,OnControl);
         if(contact)
            break;
         contact = (*it).second->proc_underlying_abonents_for_cell_display(this,i,Row);
         if(contact)
           {
           if(OnControl)
             contact->CURRENT_OWNER_ID = (*it).second->get_id(); //it is important if abonent belongs to different divisions
           break;
           }
         } //if((*it).second->CT == ContactType_DIVISION)
       i++;it++;
       } //while
  }
return contact;
}
//------------------------------------------------------------------------------
TContact* __fastcall TContacts::get_contact_by_full_name(unsigned Row)
{
TContact* contact = NULL;
::EnterCriticalSection(&contlist_cs);
  contact = __get_contact_by_full_user_name_unsafe(Row);
::LeaveCriticalSection(&contlist_cs);
return contact;
}
//------------------------------------------------------------------------------
TContact* __fastcall TContacts::__get_contact_by_full_user_name_unsafe(unsigned Row)
{
TContact* contact = NULL;
unsigned list_size = full_name_list.size();
if(Row < list_size)
  {
  unsigned global_id = full_name_list[Row];
  TContactList::iterator it = contact_list.find(global_id);
  if(it != contact_list.end())
     contact = (*it).second;
  }
return contact;
}
//------------------------------------------------------------------------------
TContact* __fastcall TContact::proc_underlying_division_ids_for_cell_display(TContacts* Contacts, int& i, int Row, bool OnControl)
{
TContact* rv = NULL;
if(!underlying_division_ids.empty())
  {
  vector<int>::iterator it = underlying_division_ids.begin();
  while(it != underlying_division_ids.end())
       {
       TContact* Contact = Contacts->get_contact_by_id(*it);
       if(Contact)
         {
         i++;
         if(i == Row)
            return Contact;
         if(Contact->get_open())
           {
           rv = Contact->proc_underlying_division_ids_for_cell_display(Contacts, i, Row, OnControl);
           if(rv)
               return rv;
           rv = Contact->proc_underlying_abonents_for_cell_display(Contacts, i, Row);
           if(rv)
             {
             if(OnControl)
                rv->CURRENT_OWNER_ID = Contact->get_id(); //it is important if abonent belongs to different divisions
             return rv;
             }
           }
         }
       it++;
       }
  }
return rv;
}
//------------------------------------------------------------------------------
TContact* __fastcall TContact::proc_underlying_abonents_for_cell_display(TContacts* Contacts, int& i, int Row)
{
TContact* rv = NULL;
int sz = underlying_ids.size() - underlying_division_ids.size();
if((i + sz) >= Row)
  {
  i++;
  vector<int>::iterator it = underlying_ids.begin();
  while(it != underlying_ids.end())
       {
       if(find_underlying_id(underlying_division_ids, *it))   //Данный контакт является подразделением, и уже посчитан в proc_underlying_division_ids_for_cell_display()
         {
         it++;
         continue;
         }
       if(i == Row)
         {
         rv = Contacts->get_contact_by_id(*it);
         break;
         }
       i++;it++;
       }
  }
else
  i += sz;
return rv;
}
 //-----------------------------------------------------------------------------------

                                  //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

/*
bool __fastcall TContacts::get_contact_copy_by_row(TContact& Contact, int Row)
{
bool rv = false;
::EnterCriticalSection(&contlist_cs);
  int i=0;
  TContactList::iterator it = contact_list.begin();
  while(it!=contact_list.end())
       {
       if(!(*it).second->OWNER)  //Данный контакт не входит ни в одно из подразделений
         {
         if(i == Row)
           {
            Contact.set_id((*it).second->get_id());
            Contact.cs        = (*it).second->cs;    //ContactState
            Contact.name      = (*it).second->name;
            Contact.full_name = (*it).second->full_name;
            Contact.set_missed_calls((*it).second->get_missed_calls());
            Contact.CT        = (*it).second->CT;   //ContactType
            Contact.pContact  = (*it).second;
            if(Contact.CT == ContactType_DIVISION)
               Contact.set_open((*it).second->get_open());
           rv = true;
           break;
           }
         }
       else
         {
         if(!(*it).second->OWNER->get_open())
           {
           it++;  //Do not i++.  Данный клиент не видим (Список подразделения в данный момент закрыт)
           continue;
           }
         else
           {
           if(i == Row)
             {
             Contact.set_id((*it).second->get_id());
             Contact.cs        = (*it).second->cs;    //ContactState
             Contact.name      = (*it).second->name;
             Contact.full_name = (*it).second->full_name;
             Contact.set_missed_calls((*it).second->get_missed_calls());
             Contact.CT        = (*it).second->CT;   //ContactType
             Contact.pContact  = (*it).second;
             if(Contact.CT == ContactType_DIVISION)
                Contact.set_open((*it).second->get_open());
             Contact.OWNER = (*it).second->OWNER;
             rv = true;
             break;
             }
           }
         }
       i++; it++;
       }
::LeaveCriticalSection(&contlist_cs);
return rv;
}
*/
//------------------------------------------------------------------------------
int __fastcall TContacts::get_row_id_by_contact_name(const string& s,TContact& contact)
{
int rv = -1;
::EnterCriticalSection(&contlist_cs);
  int i = 0;
  TContactList::iterator it = contact_list.begin();
  while(it != contact_list.end())
       {
       TContact* Contact = (*it).second;
       if(Contact->name == s)
         {
         rv = i;
         contact.set_id(Contact->get_id());
         contact.name                 = Contact->name;
         contact.full_name            = Contact->full_name;
         contact.subscription_expires = Contact->subscription_expires;
         contact.OWNER                = Contact->OWNER;
         break;
         }
       it++; i++;
       }
::LeaveCriticalSection(&contlist_cs);
return rv;
}
//------------------------------------------------------------------------------
int __fastcall TContacts::get_row_by_contact_id_in_sorted_contact_list(unsigned contact_id)
{
int rv = -1;
::EnterCriticalSection(&contlist_cs);
  TFullNameList::iterator it = full_name_list.begin();
  while(it != full_name_list.end())
       {
       if((*it).second == contact_id)
         {
         rv = (*it).first;
         break;
         }
       it++;
       }
::LeaveCriticalSection(&contlist_cs);
return rv;
}
//------------------------------------------------------------------------------
void __fastcall TBaseContact::draw_contact_state(TContact* Contact, TImageList* IL, TCanvas* GC, const TRect& Rect)
{
Contact->x_pos = get_state_left(Rect);
if(Contact->OWNER)
  Contact->x_pos = Contact->OWNER->x_pos + 20;
switch(Contact->cs){
       case ClientState_On_Line:
            IL->Draw(GC, Contact->x_pos, get_top(Rect), 1, true);
            break;
       case ClientState_Away:
            IL->Draw(GC, Contact->x_pos, get_top(Rect), 6, true);
            break;
       case ClientState_Off_Line:
            IL->Draw(GC, Contact->x_pos, get_top(Rect), 3, true);
            break;
       }
}
//------------------------------------------------------------------------------
void __fastcall TBaseContact::draw_group_img(TContact* Contact, TCanvas* GC, const TRect& Rect)
{
GC->Draw(Rect.left + 5, Rect.Top + 3, MainFormSLS->group_img_static->Picture->Bitmap);
}
//------------------------------------------------------------------------------
void __fastcall TContacts::draw_division(TCanvas* GC, const TRect& Rect, TContact* Contact)
{
Contact->x_pos = get_state_left(Rect);
if(Contact->OWNER)
   Contact->x_pos = Contact->OWNER->x_pos + 20;

TColor brush_color     = GC->Brush->Color;
int font_size          = GC->Font->Size;
TColor font_color      = GC->Font->Color;
TFontStyles font_style = GC->Font->Style;

int marker_left =  get_state_left(Rect) - 2; // Rect.Left + 10;
int marker_top  =  get_top(Rect)        - 2; // Rect.Top + Rect.Height()/2 - h/2;

AnsiString S;
if(Contact->get_open())
   S = " > ";
else
   S = " + ";

//int tw = GC->TextWidth(S);
//int th = GC->TextHeight(S);
int text_left = marker_left;
int text_top  = marker_top;

if(Contact->OWNER)
  text_left = Contact->x_pos;

GC->Brush->Color = clSilver; //clGray; //(TColor)FOREGR_ACTIVE_YELLOW;
GC->Font->Color  = clWhite;
GC->Font->Size   = 10; //12;
GC->Font->Style  = GC->Font->Style << fsBold;

GC->TextOut(text_left, text_top, S);

GC->Brush->Color = brush_color;
GC->Font->Color  = font_color;
GC->Font->Size   = 10;

if(Contact->OWNER)
  GC->TextOut(Contact->x_pos + 25, get_top(Rect), Contact->full_name.c_str());
else
  GC->TextOut(get_fname_left(Rect), get_top(Rect), Contact->full_name.c_str());

GC->Font->Size  = font_size;
GC->Font->Style = font_style;
}
//---------------------------------------------------------------------------------
//---- Если абонент в корневом списке, то у него OWNER == NULL и он всегда виден --
//---- Ecли OWNER != NULL и get_open() == true, то абонет виден  ------------------
//---------------------------------------------------------------------------------
bool __fastcall TContacts::contact_visible(TContact* Contact)
{
bool rv = true;
if(Contact->OWNER)  //абонент в корневом списке
  if(!Contact->OWNER->get_open())
      rv = false;
return rv;
}
//-----------------------------------------------------------------------------
void __fastcall TContacts::Display(TImageList* IL, TDrawGrid* DG, TCanvas* GC, int row, const TRect& Rect, TGridDrawState State)
{
::EnterCriticalSection(&contlist_cs);
  TContact* Contact = NULL;
  if(__sorted_by_full_name)
    Contact = __get_contact_by_full_user_name_unsafe(row);
  else
    Contact = __get_contact_by_row_unsafe(row, false);   //called unsafe func because critical section activated already(Protection from dead lock)
  if(Contact)
    {
    if(contact_visible(Contact))
      {
      if(Contact->CT == ContactType_DIVISION)
         draw_division(GC, Rect, Contact);
      else
        {
        if(Contact->CL == Location_INT)
          {
           if(Contact->CT == ContactType_GROUP)
             draw_group_img(Contact, GC, Rect);
           else
            {
            #ifdef Enterprise_Edition   //В Enterprise_Edition сетевое сосотояние абонента отображается в зависимости от cos абонента
            #ifdef NET_STATE_DISPLAY_DEPEND_OF_COS
              if(MainFormSLS->Sip->Account.cos <= Contact->cos)
            #endif  //#ifdef NET_STATE_DISPLAY_DEPEND_OF_COS
              draw_contact_state(Contact, IL, GC, Rect);
            #else  //#ifdef Enterprise_Edition
            draw_contact_state(Contact, IL, GC, Rect);
            #endif //#ifdef Enterprise_Edition
            }
          }
        int fname_left = get_fname_left(Rect);
        if(Contact->OWNER)
           fname_left = Contact->x_pos + 25;
        GC->Font->Name = "Arial";
        GC->Font->Size   = 10;

        if(State.Contains(gdSelected))
          GC->Font->Color  = clWhite;
        else
          GC->Font->Color  = (TColor)get_turquoise_color(); //(TColor)0x6D6D6D;
          
        GC->Font->Style  = GC->Font->Style << fsBold;
        if(!Contact->state_note.empty())
          {
          GC->TextOut(fname_left, get_top(Rect), Contact->full_name.c_str());
          AnsiString S = Contact->full_name.c_str();
          int left_comment = fname_left + GC->TextWidth(S) + 5;
          AnsiString Note  = (AnsiString)"<< " + Contact->state_note.c_str() + " >>";
          GC->Font->Color  = (TColor)0x6D6D6D; //(TColor)get_turquoise_color(); //(TColor)0x6D6D6D;
          GC->Font->Style  = GC->Font->Style << fsItalic;
          int total_length = left_comment + GC->TextWidth(Note);
          if(total_length > DG->Width)
            {
            int top_comment  = get_top(Rect) + GC->TextHeight(S) - 2;
            DG->RowHeights[row] = 44;
            GC->TextOut(fname_left,top_comment, Note);
            }
          else
            {
            Note = " - " + Note;
            GC->TextOut(left_comment, get_top(Rect), Note);
            }
          }
        else
          {
          DG->RowHeights[row] = 32;
          if(Contact->CT == ContactType_GROUP)
            GC->TextOut(fname_left, get_top(Rect), Contact->group_full_name.c_str()); 
          else
            GC->TextOut(fname_left, get_top(Rect), Contact->full_name.c_str());
          }
        int mc = Contact->get_missed_calls();
        if(mc)
          {
          //int w = 10; int h = 10;
          //int w = 12; int h = 12;
          //int w = 14; int h = 14;
          int w = 8; int h = 8;
          TRBitMap rbmp(w, h, BACKGR_WHITE, FOREGR_ACTIVE_YELLOW); //Yellow circle
          int marker_left = 0;
          if(Contact->CL == Location_INT)
             marker_left = Contact->x_pos + 4; //Rect.Right - 40;
          else
             marker_left = 13;
          int marker_top = Rect.Top + Rect.Height()/2 - h/2;
          GC->Draw(marker_left, marker_top, rbmp.bmp);
         // GC->Draw(fname_left - 15, marker_top, rbmp.bmp);
          }
        }
      }
    }
::LeaveCriticalSection(&contlist_cs);
}
//------------------------------------------------------------------------------
void __fastcall TLastCallStruct::Display_LC(TImageList* IL,TCanvas* GC,int Col, int Row,const TRect& Rect, TGridDrawState State)
{
::EnterCriticalSection(&lc_contlist_cs);
  _proc_display_lc(IL, GC, Col, Row, Rect, State);
::LeaveCriticalSection(&lc_contlist_cs);
}
//------------------------------------------------------------------------------
void __fastcall TLastCallStruct::_proc_display_lc(TImageList* IL,TCanvas* GC,int Col, int Row,const TRect& Rect, TGridDrawState State)
{
TLastCallStr lcs;
if(get_copy_of_last_call_by_row(lcs, Row))
  {
   if(Col == 0)
     {
     if(lcs.LCST == LastCallStrType_DateTime)
       {
       GC->Brush->Color = clWhite; //clWhite; // clActiveCaption;//clBlue;// clBackground;
       GC->Font->Color = clBlack;
       GC->Font->Style = GC->Font->Style << fsUnderline;
       GC->FillRect(Rect);
       TDateTime dt;
       dt = dt.CurrentDate();
       dt = dt - lcs.dt;
       if((double)dt == -1.0)
          GC->TextOut(get_fname_left(Rect), get_top(Rect), "Сегодня");
       else if((double)dt == 0.0)
          GC->TextOut(get_fname_left(Rect), get_top(Rect), "Вчера");
       else
          {
          USHORT year, month, day;
          lcs.dt.DecodeDate(&year, &month, &day);
          AnsiString S = IntToStr(day) + " " + month_to_str(month, MainFormSLS->lng).c_str() + " " + IntToStr(year);
          GC->TextOut(get_fname_left(Rect), get_top(Rect), S);
          }
       return;
       }
     if(State.Contains(gdFocused))
       {
       if(lcs.LCST == LastCallStrType_ContactInt)
         {
         TContact ContCopy(-1);
         if(MainFormSLS->Sip->Contacts.get_contact_copy_by_user_name(ContCopy,lcs.name))
           draw_contact_state(&ContCopy, IL, GC, Rect);
         }
       GC->TextOut(get_fname_left(Rect), get_top(Rect), lcs.full_name.c_str());
       if(Rect.Right > 250)
         {
         AnsiString S = AWS + lcs.s_time + AWS + AWS + AWS + AWS + AWS + AWS;
         GC->TextOut(Rect.Right - LEFT_TIME_MARGIN, get_top(Rect), S);
         }
       return;
       }   //if(State.Contains(gdFocused))
     //if(Row == row_focused)
     if(State.Contains(gdFocused))
       {
       GC->Brush->Color = clActiveCaption; //clWhite; // clActiveCaption;//clBlue;// clBackground;
       GC->Font->Color  = clWhite;
       GC->Font->Style  = GC->Font->Style << fsBold;
       }
     else
       {
       GC->Brush->Color = clWhite; //clWhite; // clActiveCaption;//clBlue;// clBackground;
       GC->Font->Color = clBlack;
       }
     GC->FillRect(Rect);
     if(lcs.LCST == LastCallStrType_ContactInt)
       {
       TContact ContCopy(-1);
       if(MainFormSLS->Sip->Contacts.get_contact_copy_by_user_name(ContCopy,lcs.name))
         draw_contact_state(&ContCopy, IL, GC, Rect);
       }
     GC->TextOut(get_fname_left(Rect), get_top(Rect), lcs.full_name.c_str());
     if(Rect.Right > 250)
       {
       AnsiString S = AWS + lcs.s_time + AWS + AWS + AWS + AWS + AWS + AWS;
       GC->TextOut(Rect.Right - LEFT_TIME_MARGIN, get_top(Rect), S);
       }
     int mc = lcs.get_missed_calls();
     if(mc)
       {
       //int w = 10; int h = 10;
       //int w = 12; int h = 12;
       //int w = 14; int h = 14;
       int w = 10; int h = 10;
       TRBitMap rbmp(w, h, BACKGR_WHITE, FOREGR_ACTIVE_YELLOW); //Yellow circle
       int marker_left = 13; //Contact->x_pos + 4; //Rect.Right - 40;
       int marker_top  = Rect.Top + Rect.Height()/2 - h/2;
       GC->Draw(marker_left, marker_top, rbmp.bmp);
       // GC->Draw(fname_left - 15, marker_top, rbmp.bmp);
       }
     } //if(Col == 0)
  }
}
//------------------------------------------------------------------------------
void __fastcall TContacts::set_division_visible(int id, TDrawGrid* DG, bool a)
{
::EnterCriticalSection(&contlist_cs);
  TContactList::iterator it = contact_list.find(id);
  if(it != contact_list.end())
    {
    (*it).second->set_open(a);
    if(!a)       //Close all underlying divisions
      {
      TContact* Contact = (*it).second;
      *pContact_list_size -= Contact->underlying_ids.size();
      if(!Contact->underlying_division_ids.empty()) //Если имеются underlying divisions
        {
        vector<int>::iterator it_v = Contact->underlying_division_ids.begin();
        while(it_v != Contact->underlying_division_ids.end())
             {
             it = contact_list.find(*it_v++);
             if(it != contact_list.end())
               {
               if((*it).second->get_open())
                  set_division_visible((*it).second->get_id(), DG, a);
               (*it).second->set_open(a);
               }
             }
        }
      if(*pContact_list_size < 0)
        *pContact_list_size = 0;
      Update_DrawGrid_RowCount(DG);
      }
    else     //Open underlying division (only underliying !!!)
      {
      *pContact_list_size += (*it).second->underlying_ids.size();
      Update_DrawGrid_RowCount(DG);
      }
    }
::LeaveCriticalSection(&contlist_cs);
}
//------------------------------------------------------------------------------
void __fastcall TContacts::open_all_above_divisions(TContact* OWNER)
{
while(OWNER){
      if(OWNER->get_open())
        return;           //this division already open
      OWNER->set_open(true);
      *pContact_list_size += OWNER->underlying_ids.size();
      Update_DrawGrid_RowCount(MainFormSLS->DrawGrid1);
      OWNER = OWNER->OWNER;   
      }
}
//------------------------------------------------------------------------------
TContact* __fastcall TContacts::get_contact_by_id(int id)
{
TContact* rv = NULL;
::EnterCriticalSection(&contlist_cs);
  TContactList::iterator it = contact_list.find(id);
  if(it != contact_list.end())
     rv = (*it).second;
::LeaveCriticalSection(&contlist_cs);
return rv;
}
//-----------------------------------------------------------------------------
bool __fastcall TContacts::get_contact_copy_by_id(TContact& Contact, int id)
{
bool rv = false;
::EnterCriticalSection(&contlist_cs);
  TContactList::iterator it = contact_list.find(id);
  if(it != contact_list.end())
    {
    Contact.cs        = (*it).second->cs;
    Contact.name      = (*it).second->name;
    Contact.full_name = (*it).second->full_name;
    rv = true;
    }
::LeaveCriticalSection(&contlist_cs);
return rv;
}
//------------------------------------------------------------------------------
bool __fastcall TContacts::get_contact_copy_by_display_name(TContact& Contact, const string& display_name)
{
bool rv = false;
::EnterCriticalSection(&contlist_cs);
  int i=0;
  TContactList::iterator it = contact_list.begin();
  while(it!=contact_list.end())
       {
       if((*it).second->full_name == display_name)
         {
         Contact.cs        = (*it).second->cs;
         Contact.name      = (*it).second->name;
         Contact.full_name = (*it).second->full_name;
         rv = true;
         break;
         }
       i++; it++;
       }
::LeaveCriticalSection(&contlist_cs);
return rv;
}
//------------------------------------------------------------------------------
bool __fastcall TContacts::get_contact_copy_by_user_name(TContact& Contact, TExchBuf* buf)
{
bool rv = false;
::EnterCriticalSection(&contlist_cs);
  TNameList::iterator it = name_list.find(buf->msg);
  if(it != name_list.end())
    {
    TContactList::iterator it_1 = contact_list.find((*it).second);
    if(it_1 != contact_list.end())
      {
      TContact* contact = (*it_1).second;
      if(contact)
        {
        Contact.name                 = contact->name;
        Contact.full_name            = contact->full_name;
        Contact.subscription_expires = contact->subscription_expires;
        rv = true;
        }
      }
    }
  it = name_list.find(buf->msg + "@" + buf->msg_1);
  if(it != name_list.end())
    {
    TContactList::iterator it_1 = contact_list.find((*it).second);
    if(it_1 != contact_list.end())
      {
      TContact* contact = (*it_1).second;
      if(contact)
        {
        Contact.name                 = contact->name;
        Contact.full_name            = contact->full_name;
        Contact.subscription_expires = contact->subscription_expires;
        rv = true;
        }
      }
    }
::LeaveCriticalSection(&contlist_cs);
return rv;
}
//------------------------------------------------------------------------------
bool __fastcall TContacts::get_contact_copy_by_user_name(TContact& Contact, const string& username)
{
bool rv = false;
::EnterCriticalSection(&contlist_cs);
TNameList::iterator it = name_list.find(username);
if(it != name_list.end())
  {
  TContactList::iterator it_1 = contact_list.find((*it).second);
  if(it_1 != contact_list.end())
    {
    TContact* contact = (*it_1).second;
    if(contact)
      {
      Contact.set_id(contact->get_id());
      Contact.name                 = contact->name;
      Contact.full_name            = contact->full_name;
      if(contact->CT == ContactType_GROUP)
        {
        Contact.CT = contact->CT;
        deque<TGroupName> q;
        contact->GRNS.GET_GROUP(q);
        Contact.GRNS.SET_GROUP(q);
        }
      Contact.subscription_expires = contact->subscription_expires;
      Contact.cs                   = contact->cs;
      Contact.DBI                  = contact->DBI;
      Contact.pContact             = contact;
      rv = true;
      }
    }
  }
::LeaveCriticalSection(&contlist_cs);
return rv;
}
//------------------------------------------------------------------------------
void __fastcall TContacts::commit_contact_list(FILE* f)
{
::EnterCriticalSection(&contlist_cs);
  string s;
  int i=0;
  TContactList::iterator it = contact_list.begin();
  while(it != contact_list.end())
       {
       TContact* contact = (*it++).second;
       if(contact)
         {
         s += contact->name + SEMICOLON + contact->full_name + SEMICOLON;
         if(i < commit_packet_size)
           {
           s += "\n";
           i++;
           }
         else
           {
           s += "\n";
           fputs(s.c_str(),f);
           i = 0;
           s.clear();
           }
         }
       }
  if(!s.empty())
     fputs(s.c_str(),f);
::LeaveCriticalSection(&contlist_cs);
}
//-----------------------------------------------------------------------------
void   __fastcall TSip::init_on_registration_subscribe_proc()
{
init_subscribe = true;
Contacts.push_subscr_queue();
MainFormSLS->RS.set_subscr_proc_active(true);
}
//------------------------------------------------------------------------------
void   __fastcall TContacts::push_subscr_queue()
{
::EnterCriticalSection(&contlist_cs);
  TContactList::iterator it = contact_list.begin();
  while(it != contact_list.end())
       {
       if((*it).second->CT == ContactType_CLIENT)
         {
         TContact contact(-1);
         contact.name      = (*it).second->name;
         contact.full_name = (*it).second->full_name;
         MainFormSLS->RS.push_contact(contact);
         }
       it++;
       }
::LeaveCriticalSection(&contlist_cs);
}
//------------------------------------------------------------------------------
void __fastcall TContacts::set_contact_state(const string& name,ClientState client_state)
{
::EnterCriticalSection(&contlist_cs);
  TNameList::iterator it = name_list.find(name);
  if(it != name_list.end())
    {
    TContactList::iterator it_1 = contact_list.find((*it).second);
    if(it_1 != contact_list.end())
      {
      TContact* contact = (*it_1).second;
      if(contact)
         contact->cs = client_state;
      }
    }
    /*
  else
    {
    string s = name;
    int st = s.find("@");
    if(st != -1)
      {
      s.resize(st);
      TNameList::iterator it = name_list.find(s);
      TContactList::iterator it_1 = contact_list.find((*it).second);
      if(it_1 != contact_list.end())
        {
        TContact* contact = (*it_1).second;
        if(contact)
           contact->cs = client_state;
        }
      }
    }
    */
::LeaveCriticalSection(&contlist_cs);
}
//------------------------------------------------------------------------------
void __fastcall TContacts::set_contact_state_comment(const string& name, string& comment, bool sdp_rcvd, bool deactivated, bool SaveComment)
{
if(comment == "Available")
   comment.clear();
else if(comment == "Offline")
   comment.clear();
else if(comment == "Away")
   comment.clear();

::EnterCriticalSection(&contlist_cs);
  TNameList::iterator it = name_list.find(name);
  if(it != name_list.end())
    {
    TContactList::iterator it_1 = contact_list.find((*it).second);
    if(it_1 != contact_list.end())
      {
      TContact* contact = (*it_1).second;
      if(contact)
        {
        if(comment == " ")
          {
          contact->state_note.clear();
          if(SaveComment)
             clear_contact_comment(name);
          }
        else
          {
          if(!comment.empty())
            {
            contact->state_note = comment;
            if(SaveComment)
               save_contact_comment(name,comment);
            }
          else
            {
            if(!deactivated)    //check for stay comment on NOTIFY terminated,deactivated
             if(sdp_rcvd)
               {
               contact->state_note = comment;
               if(SaveComment)
                  clear_contact_comment(name);
               }
            }
          }
        }
      }
    }
::LeaveCriticalSection(&contlist_cs);
}
//------------------------------------------------------------------------------
bool __fastcall TContacts::missed_call(const string& name)
{
bool rv = false;
::EnterCriticalSection(&contlist_cs);
  TNameList::iterator it = name_list.find(name);
  if(it != name_list.end())
    {
    rv = true;
    TContactList::iterator it_1 = contact_list.find((*it).second);
    if(it_1 != contact_list.end())
      {
      TContact* contact = (*it_1).second;
      if(contact)
         contact->inc_missed_calls();
      }
    }
::LeaveCriticalSection(&contlist_cs);
return rv;
}
//-----------------------------------------------------------------------------
void __fastcall TContacts::reset_missed_calls(const string& name)
{
::EnterCriticalSection(&contlist_cs);
  TNameList::iterator it = name_list.find(name);
  if(it != name_list.end())
    {
    TContactList::iterator it_1 = contact_list.find((*it).second);
    if(it_1 != contact_list.end())
      {
      TContact* contact = (*it_1).second;
      if(contact)
         contact->res_missed_calls();
      }
    }
::LeaveCriticalSection(&contlist_cs);
}
//-----------------------------------------------------------------------------
bool __fastcall TContacts::is_contact_exists(const string& name)
{
bool rv = false;
::EnterCriticalSection(&contlist_cs);
  rv = (name_list.find(name) != name_list.end()) ? true : false;
::LeaveCriticalSection(&contlist_cs);
return rv;
}
//------------------------------------------------------------------------------
void __fastcall TContacts::update_personal_contact_list(TDBData* dbd)
{
::EnterCriticalSection(&contlist_cs);
  TNameList::iterator it = name_list.find(dbd->s_1);
  if(it != name_list.end())
    {                     //update Contact data
    TContactList::iterator it_1 = contact_list.find((*it).second);
    if(it_1 != contact_list.end())
      {
      bool change = false;
      (*it_1).second->db_ref       = dbd->u_2;
      if((*it_1).second->position != dbd->s_3)  // job_position
        {
        change = true;
        (*it_1).second->position = dbd->s_3;
        }
      if((*it_1).second->full_name != dbd->s_7) // full_name
        {
        change = true;
        (*it_1).second->full_name = dbd->s_7;
        }
      if(change)
         add_contact_name_to_actual_directory((*it_1).second);
      }
    }
  else
    {
     TContact* Cont = new TContact(get_next_contact_id());
     if(Cont)
       {
       if(dbd->SDMT == ServDbMsgType_GET_PERSONAL_CITY_PHONE_LIST)
          Cont->CL = Location_EXT;
       Cont->db_ref    = dbd->u_2;
       Cont->name      = dbd->s_1;
       Cont->full_name = dbd->s_7;
       Cont->position  = dbd->s_3;
      _insert_contact_in_contact_list(Cont,true);
       inc_contact_list_size();
       Update_DrawGrid_RowCount(MainFormSLS->DrawGrid1);
       add_to_actual_directory(Cont);
       if(Cont->CT == ContactType_CLIENT)
         {
         TContact contact(-1);
         contact.name      = Cont->name;
         contact.full_name = Cont->full_name;
         MainFormSLS->RS.push_contact(contact);
         MainFormSLS->RS.set_subscr_proc_active(true);
         }
       }
    }
::LeaveCriticalSection(&contlist_cs);
}
//------------------------------------------------------------------------------------
//-- Delete from contact_list all contacts which havn't db_ref == dbd->u_1 or dbd->u_2
//------------------------------------------------------------------------------------
void __fastcall TContacts::end_of_personal_contact_list(TDBData* dbd)
{
::EnterCriticalSection(&contlist_cs);
  queue<string> q;
  TContactList::iterator it = contact_list.begin();
  while(it != contact_list.end())
       {
       if((*it).second->db_ref != dbd->u_1)
          if((*it).second->db_ref != dbd->u_2)
             q.push((*it).second->name);
       it++;
       }
  while(!q.empty())
       {
       string s = q.front();
       q.pop();
       if(!s.empty())
         {
         TNameList::iterator it = name_list.find(s);
         if(it != name_list.end())
           {
           TContactList::iterator it_1 = contact_list.find((*it).second);
           if(it_1 != contact_list.end())
             {
             del_contact_from_actual_contact_list((*it_1).second);  //Delete from harddisk
             del_contact((*it_1).second->get_id());                 //Delete from memory
             }
           }
         }
       }
if(__sorted_by_full_name)
   __sort_by_full_user_name_unsafe();
::LeaveCriticalSection(&contlist_cs);
}
//------------------------------------------------------------------------------
void __fastcall TSip::SendInitMessage(TContact* Contact,const vector<string>& message)
{
if(uac)
  {
  TOutputSipBuf* ospb = prepare_Initial_MESSAGE_Req(Contact,message);
  if(ospb)
    {
    uac->setQueue(ospb);
    updateSentQueue_1(ospb);
    }
  }
}
//-----------------------------------------------------------------------------
//--- Send Instant Message in existing Dialog - with To Tag and From Tag ------
//-----------------------------------------------------------------------------
/*
void __fastcall TSip::SendInstantMessage_IN_DIALOG(LegType Lt, const string& callid, const vector<string>& message)
{
if(Lt == Lt_Out)
  __send_instant_message_IN_DIALOG__UAC(callid, message);
else if(Lt == Lt_In)
  __send_instant_message_IN_DIALOG__UAS(callid, message);
}
//------------------------------------------------------------------------------
void __fastcall TSip::__send_instant_message_IN_DIALOG__UAC(const string& callid, const vector<string>& message)
{
}
//-----------------------------------------------------------------------------
void __fastcall TSip::__send_instant_message_IN_DIALOG__UAS(const string& callid, const vector<string>& message)
{
}
*/
//-----------------------------------------------------------------------------
TOutputSipBuf*  __fastcall TSip::prepare_Initial_MESSAGE_Req(TContact* Contact,const vector<string>& message)
{
TOutputSipBuf* ospb = new TOutputSipBuf;
if(ospb)
  {
  ospb->setsls(SPS_MESSAGE_REQ);
  generateFromTag(ospb);
  generateCallID(ospb);
  ospb->ToIP   = SipProxy.IPAddr;
  ospb->ToPort = SipProxy.Port;
  prepareSdp_MESSAGE(ospb,message);
  prepareRequestLine_MESSAGE(ospb,Contact);
  prepareViaHeader(ospb);
  prepareMaxForwards(70,ospb);
  int st = Contact->name.find("@");
  if(st == -1)
     prepareInitialTo(Contact->name, Contact->full_name, Account.get_domain(), ospb);
  else
     prepareInitialTo(Contact->name, Contact->full_name, strempty, ospb);
  prepareFrom_COMMON(ospb,&Account,true);
  prepareCallID_MESSAGE(ospb);
  prepareCSeq(++MESSAGE_CSeq,"MESSAGE",ospb);
  prepareAllow(ospb);
  #ifdef Send_Msg_Text__html
   prepareContentType(ospb,"text/html");
  #else
   prepareContentType(ospb,"text/plain");
  #endif
  prepareUserAgent(ospb);
  }
return ospb;
}
//------------------------------------------------------------------------------
void __fastcall TSip::prepareSdp_MESSAGE(TOutputSipBuf* ospb,const vector<string>& msg)
{
int sz = msg.size();
if(sz)
  {
  #ifdef Send_Msg_Text__html
    ospb->sdp.Sdp = "<span style=" + (string)"\"" + "font-family: Arial; font-size: 10pt; color: #000000"  + "\"" + ">";
    for(int i=0; i < sz; i++)
       {
       if(i)
          {
          string out_str;
          check_im_out_str(msg,i,out_str);
          ospb->sdp.Sdp += "<br/>" + out_str;
          }
       else
          {
          string out_str;
          check_im_out_str(msg,i,out_str);
          ospb->sdp.Sdp += out_str;
          }
       }
    ospb->sdp.Sdp += "</span>"; 
  #else
    for(int i=0; i < sz; i++)
       {
       if(i)
          {
          string out_str;
          check_im_out_str(msg,i,out_str);
          ospb->sdp.Sdp += "\n" + out_str;
          }
       else
          {
          string out_str;
          check_im_out_str(msg,i,out_str);
          ospb->sdp.Sdp = out_str;
          }
       }
    ospb->sdp.Sdp += crlf;
  #endif
  }
}
//-----------------------------------------------------------------------------
void __fastcall TSip::check_im_out_str(const vector<string>& msg,int i,string& out)
{
#ifdef Send_IM_reference_like_HTML_ref
int st = msg[i].find("http://");
if(st == -1)
  {
  st = msg[i].find("https://");
  if(st == -1)
    {
    out = msg[i];
    return;
    }
  }
vector<string> v;
string partial_str = msg[i];
while(!partial_str.empty())
     devide_plain_text_on_substrings(v,partial_str);
int sz = v.size();
for(int i=0; i < sz; i++)
   {
   st = v[i].find("http://");
   if(st==-1)
     {
     st = v[i].find("https://");
     if(st == -1)
       {
       out += v[i];
       continue;
       }
     }
   out += "<a href=" + (string)"\"" + v[i] + "\"" + ">" + v[i] + "</a>";
   }
#else
out = msg[i];
return;
#endif
}
//-----------------------------------------------------------------------------
void __fastcall TSip::devide_plain_text_on_substrings(vector<string>& v,string& partial_str)
{
int st = partial_str.find("http://");
if(st == -1)
  {
  st = partial_str.find("https://");
  if(st == -1)
    {
    v.push_back(partial_str);
    partial_str.resize(0);
    return;
    }
  }
if(!st)
  {
  int en = partial_str.find(WS);
  if(st < en)
    {
    v.push_back(partial_str.substr(st,en-st));
    partial_str = partial_str.substr(en);
    }
  else
    {
    v.push_back(partial_str);
    partial_str.resize(0);
    }
  }
else
  {
  v.push_back(partial_str.substr(0,st));
  partial_str = partial_str.substr(st);
  }
}
//-----------------------------------------------------------------------------
void __fastcall TSip::tnl_add(TTransferFileStruct& s)
{
::EnterCriticalSection(&req_tfl_cs);
  req_tfl.push(s);
::LeaveCriticalSection(&req_tfl_cs);
}
//---------------------------------------------------------------------------
bool __fastcall TSip::tnl_get(TTransferFileStruct& tfs)
{
bool rv = false;
::EnterCriticalSection(&req_tfl_cs);
  if(!req_tfl.empty())
    {
    tfs = req_tfl.front();
    req_tfl.pop();
    rv = true;
    }
::LeaveCriticalSection(&req_tfl_cs);
return rv;
}
//---------------------------------------------------------------------------
void __fastcall TSip::transmit_file_init()
{
#ifdef Contact_HTTP_FileTransfer
TTransferFileStruct tfs;
while(tnl_get(tfs)) {
     TExchFileMsg efm(1); //Request on send file
     efm.sending_file_path = tfs.path;
     efm.q_cont.push(tfs.contact.name);

     if(MainFormSLS->Im.LCFT)  //Thread для работы с файлом содержащим последние вызовы (Last Calls)
       {
       TImStr* IS = new TImStr(IM_INVITE_ON_FILE_SENDING);      //Сохранить в истории данный реквест
       if(IS){
         IS->time_stmp_to_str();
         IS->set_contact_name(tfs.contact.name);
         //  IS->set_year_month_day(year_month_day);
         if(MainFormSLS->Im.get_selected_remote_user() == tfs.contact.name) // tfs.contact.name = remote_user
            IS->rem_user_selected = true;           //if false IS will be deleted in the MainFormSLS->Im.LCFT. Only writing in the file will be made
         string user = get_current_user();          //Далее - аналог HSTRY_SAVE_AND_DISPLAY()
         string s_cl = MainFormSLS->get_clients_dir();
         s_cl += "\\" + user;
         TLCSBuf* LCSBuf = new TLCSBuf(HSTRY_WRITE);
         if(LCSBuf)
           {
           LCSBuf->s   = s_cl;
           LCSBuf->s_1 = tfs.contact.name;    //remote user
           LCSBuf->s_3 = tfs.path;            //full path + filename
           LCSBuf->IS  = IS;
           MainFormSLS->Im.LCFT->push_lcs_buf(LCSBuf);
           } // if(LCSBuf)
         }  // if(IS){
       }  // if(MainFormSLS->Im.LCFT)
     MainFormSLS->FEXCH.fexch_ins(efm);
     }  // while(tnl_get(tfs)) {
MainFormSLS->FEXCH.check_file_exch_activity();
#else
TTransferFileStruct tfs;
if(tnl_get(tfs))
  {
  unsigned file_size = get_file_size(tfs.path);
  string file_name;
  int st = tfs.path.rfind("\\");
  if(st!=-1)
    {
    st++;  // "\\" - one position (not two)
    int en = tfs.path.length();
    if(st < en)
      file_name = tfs.path.substr(st,en-st);
    }

  TCall_Panel* panel = new TCall_Panel(MainFormSLS);
  if(panel)
    {
    panel->Parent    = MainFormSLS;
    panel->set_call_type(Call_Type_FileTransfer);
    panel->set_leg_type(Lt_Out);
    // panel->Top        = MainFormSLS->Panel1->Top + MainFormSLS->Panel1->Height;
    panel->Left       = MainFormSLS->RIGHT_PANEL->Left;
    panel->Width      = MainFormSLS->Panel1->Width;
    panel->Height     = MainFormSLS->Panel1->Height;
    panel->Color      =(TColor)0xEEEEEE; //clSilver;
    panel->BevelInner = bvLowered;
    panel->BevelOuter = bvRaised;
    panel->Tag        = gen_call_tag();

    MainFormSLS->getBottomCallPanelMargin();

    Transmit_File__Labels(panel, &tfs, file_name, file_size);
    Transmit_File__Cancel_Btn(panel);
    Transmit_File__Progress_Bar(panel,file_size);
    Transmit_File__Label_Waiting(panel);

    TTransmitFileThread* ttf = new TTransmitFileThread(true,&MainFormSLS->ofs->elt,this);
    if(ttf)
      {
      ttf->set_file_name(file_name);
      ttf->set_host(FileTransfer.IPAddr);
      ttf->set_port(FileTransfer.Port);
      panel->TFP.contact       = tfs.contact;
      panel->TFP.tfa.file_name = file_name;
      panel->TFP.tfa.file_size = file_size;
      panel->TFP.tfa.path      = tfs.path;
      panel->t_trn_f = ttf;
      started_transferfile_panel_tag = panel->Tag;
      MainFormSLS->cps.add_panel_tag(panel->Tag,MainFormSLS->CL_DrawGrid);
      ttf->Resume_Thread();
      }//if(ttf)
  ::PostMessage(MainFormSLS->Handle, CONTROL_MSG, WM_APP_MSG_WPARAM__IM__DRAWGRID_RESIZE_ON_CHANGE_CALL_COUNT, WM_APP_MSG_LPARAM__NOPARAM);
    }  //if(panel)
  } // if(tnl_get(tfs))
#endif // #ifdef Contact_HTTP_FileTransfer  #else
}
//----------------------------------------------------------------------------
unsigned __fastcall TSip::get_file_size(const string& s)
{
unsigned rv=0;
FILE* f = fopen(s.c_str(),"r");
if(f)
  {
  fseek(f, 0L, SEEK_END);
  rv = ftell(f);
  fclose(f);
  }
return rv;
}
//----------------------------------------------------------------------------
void __fastcall TSip::Receive_File__Labels(void* Panel,TSipParsBuf* spb,TTransferFileAttrib* tfa)
{
TCall_Panel* panel = (TCall_Panel*)Panel;
panel->lb = new TLabel(panel);
if(panel->lb)
  {
  panel->lb->Parent = panel;
  panel->lb->Left   = 15;
  panel->lb->Top    = 2;
 // panel->lb->Color = clInactiveCaption;
  panel->lb->Font->Color = clBlack; //clWhite;
  panel->lb->Font->Height = 8;
  panel->lb->Font->Size   = 10;
  panel->lb->Caption = "\"" + (AnsiString)spb->callingParty.c_str() + "\"";

  panel->lb_1 = new TLabel(panel);
  if(panel->lb_1)
    {
    panel->lb_1->Parent = panel;
    panel->lb_1->Left   = panel->lb->Left;
    panel->lb_1->Top    = panel->lb->Top + 20;
    panel->lb_1->Font->Height = 8;
    panel->lb_1->Font->Size   = 10;
    panel->set_receiving_file_name_label();
    }
  }
}
//----------------------------------------------------------------------------
void __fastcall TSip::Receive_File__Btns(void* Panel)
{
TCall_Panel* panel = (TCall_Panel*)Panel;
int btn_height = 20;
panel->btn_0 = new TButton(panel);
if(panel->btn_0)
  {
  panel->btn_0->Parent = panel;
  panel->btn_0->Tag    = panel->Tag; //!!!
  panel->btn_0->Height = btn_height;
  panel->btn_0->Top    = panel->Height - panel->btn_0->Height - 10 ;
  panel->btn_0->Left   = panel->Width - panel->btn_0->Width - 20;
  if(MainFormSLS->lng == Lang_RU)
     panel->btn_0->Caption = "Отменить";
  else
     panel->btn_0->Caption = "Cancel";
  panel->btn_0->OnMouseUp  = MainFormSLS->Btn_CancelReceiveFile_MouseUp;

  panel->btn_1 = new TButton(panel);
  if(panel->btn_1)
    {
    panel->btn_1->Parent = panel;
    panel->btn_1->Tag    = panel->Tag;//!!!
    panel->btn_1->Height = btn_height;
    panel->btn_1->Top    = panel->btn_0->Top;
    panel->btn_1->Left   = panel->btn_0->Left - panel->btn_1->Width - 20;
    if(MainFormSLS->lng == Lang_RU)
      panel->btn_1->Caption = "Сохранить";
    else
      panel->btn_1->Caption = "Save as";
    panel->btn_1->OnMouseUp = MainFormSLS->Btn_SaveFileMouseUp;
    }
  }
}
//----------------------------------------------------------------------------
void __fastcall TSip::Transmit_File__Labels(void* Panel, TTransferFileStruct* tfs,
                                            const string& file_name, unsigned file_size)
{
TCall_Panel* panel = (TCall_Panel*)Panel;
panel->lb = new TLabel(panel);
if(panel->lb)
  {
  panel->lb->Parent = panel;
  panel->lb->Left   = 15;
  panel->lb->Top    = 2;
 // panel->lb->Color = clInactiveCaption;
  panel->lb->Font->Color = clBlack;
 // panel->lb->Font->Height = 8;
 // panel->lb->Font->Size   = 10;
  panel->lb->Caption = "\"" + (AnsiString)tfs->contact.full_name.c_str() + "\"";

  panel->lb_1 = new TLabel(panel);
  if(panel->lb_1)
    {
    panel->lb_1->Parent = panel;
    panel->lb_1->Left   = panel->lb->Left;
    panel->lb_1->Top    = panel->lb->Top + 20;
   // panel->lb_1->Font->Height = 8;
   // panel->lb_1->Font->Size   = 10;

    string S;

    if(MainFormSLS->lng == Lang_RU)
       S = "Файл: ";
    else
       S = "File: ";
    S += file_name + "\n";
    int f_size = 0;
    string s_size;
    if(file_size > 10000)
      {
      f_size = file_size/1000;
      s_size = " Kbyte";
      }
    else
      {
      f_size = file_size;
      s_size = " Byte";
      }
    S += inttostr(f_size) + s_size;
    panel->lb_1->Caption = S.c_str();
    }
  }
}
//----------------------------------------------------------------------------
void __fastcall TSip::Transmit_File__Cancel_Btn(void* Panel)
{
TCall_Panel* panel = (TCall_Panel*)Panel;
panel->btn_0 = new TButton(panel);  //!!! Owner TTransferFile_Panel
if(panel->btn_0)
  {
  panel->btn_0->Parent = panel;
  panel->btn_0->Tag    = panel->Tag;
  panel->btn_0->Top    = panel->Height - panel->btn_0->Height - 10;
  panel->btn_0->Left   = panel->Width/2 + panel->Width/4;
  panel->btn_0->Height = 20;
  if(MainFormSLS->lng == Lang_RU)
     panel->btn_0->Caption = "Отменить";
  else
     panel->btn_0->Caption = "Cancel";
  panel->btn_0->OnMouseUp = MainFormSLS->Btn_CancelTransmitFile_MouseUp;
  }
}
//----------------------------------------------------------------------------
void __fastcall TSip::Transmit_File__Progress_Bar(void* Panel,unsigned max)
{
TCall_Panel* panel = (TCall_Panel*)Panel;
panel->progbar = new TProgressBar(panel);
if(panel->progbar)
  {
  panel->progbar->Parent = panel;
  panel->progbar->Height = 8;
  panel->progbar->Width  = panel->Width/3;
  if(panel->btn_0)
    {
    panel->progbar->Top  = panel->btn_0->Top + panel->btn_0->Height/2 - panel->progbar->Height/2;
    panel->progbar->Left = panel->btn_0->Left - panel->progbar->Width - 10;
    }
  else
    panel->progbar->Left = panel->Width/2 - panel->progbar->Width/2;
  panel->progbar->Min = 0;
  panel->progbar->Max = max;
  }
}
//----------------------------------------------------------------------------
void __fastcall TSip::Transmit_File__Label_Waiting(void* Panel)
{
TCall_Panel* panel = (TCall_Panel*)Panel;
if(panel->progbar)
  {
  panel->lb_2 = new TLabel(panel);
  if(panel->lb_2)
    {
    panel->lb_2->Parent  = panel;
    panel->lb_2->Left    = panel->progbar->Left;
    panel->lb_2->Top     = panel->progbar->Top + panel->progbar->Height;// + 15;
    if(MainFormSLS->lng == Lang_RU)
       panel->lb_2->Caption = "Ожидание...";
    else
       panel->lb_2->Caption = "Waiting...";
    }
  }
}
//----------------------------------------------------------------------------
void __fastcall TSip::Receive_File__Progress_Bar(void* Panel,unsigned max)
{
TCall_Panel* panel = (TCall_Panel*)Panel;
panel->progbar = new TProgressBar(panel);
if(panel->progbar)
  {
  panel->progbar->Parent = panel;
  panel->progbar->Height = 8;
  panel->progbar->Width  = panel->Width/3;
  if(panel->btn_1)
    {
    panel->progbar->Top  = panel->btn_1->Top + panel->btn_1->Height/2 - panel->progbar->Height/2;
    panel->progbar->Left = panel->btn_1->Left - panel->progbar->Width - 10;
    }
  else
    panel->progbar->Left = panel->Width/2 - panel->progbar->Width/2;
  panel->progbar->Min = 0;
  panel->progbar->Max = max;
  }
}
//----------------------------------------------------------------------------
/*
void __fastcall TSip::Tunnel_Connect()
{
if(localIP.empty())return;
 if(!Try_Tunnel_Connect(&SipTunnel))
    Try_Tunnel_Connect(&SipLocalTunnel);
}
//----------------------------------------------------------------------------
int __fastcall TSip::Try_Tunnel_Connect(TIPAddress* remote_addr)
{
if(!remote_addr->uIPAddr) return 0;
deque<TIPAddress*>::iterator it = localIP.begin();
while(it != localIP.end())                         // !!! Must be executed in differend Threads
     {
     TIPAddress* ip_addr = (*it++);
     if(ip_addr)
       {
       TMfswIpAddrStruct sa;
       sa.LocalAddr = ip_addr->IPAddr;
       SOCKET socket = exsCreateTCPSocket(&sa);
       if(socket != INVALID_SOCKET)
         {
         struct sockaddr_in dest;
         memset(&dest,0,sizeof(dest));
         dest.sin_family = AF_INET;
         dest.sin_addr.s_addr = inet_addr(remote_addr->IPAddr.c_str());
         dest.sin_port = htons(remote_addr->Port);
         int cnt = connect(socket,(struct sockaddr *)&dest, sizeof(dest));
         if(cnt == SOCKET_ERROR)
           {
           int err = WSAGetLastError();
           lasterr = "\nSipTunnel connect";
           GetLastSocketError(lasterr,err);
           Log(lasterr);
           closesocket(socket);
           continue;
           }
         else
           {
           tunnel_sck = socket;
           return 1; //OK
           }
         }
       }
     }
return 0; //Failed
}
*/
//------------------------------------------------------------------------------
void __fastcall TSubscrPar::set_delta_and_next_sabscr_date(unsigned sec)
{
expires        = sec;
subscr_delta   = sec_to_date_time(sec);
subscr_next    = subscr_next.CurrentDateTime() + subscr_delta;
}
//------------------------------------------------------------------------------
void __fastcall TSubscribedData::set_delta_and_next_sabscr_date(unsigned sec)
{
expires        = sec;
subscr_delta   = sec_to_date_time(sec);
subscr_next    = subscr_next.CurrentDateTime() + subscr_delta;
}
//------------------------------------------------------------------------------
void __fastcall TSubscrPar::update_timer(TDateTime& next_init_time)
{
subscr_next    = subscr_next.CurrentDateTime() + subscr_delta;
next_init_time = subscr_next;
}
//------------------------------------------------------------------------------
void __fastcall TSubscribedStruct::add_subscribed_contact(const string& name,TExchBuf* buf)
{
::EnterCriticalSection(&ss_subscrlist_cs);
  TSubscribedData sd;
  sd.name   = name;
  sd.callid = buf->callid;
  sd.set_cseq(buf->tag_1);
  sd.set_delta_and_next_sabscr_date(buf->tag);
  sd.set_real_subscr_next(sd.get_subscr_next());
  TSubscribedList::iterator it = ss_subscribed_list.find(name);
  if(it == ss_subscribed_list.end())
    {
    TSubscribedPar sp;
    sp.add_subscribed_data_by_callid(sd);
    ss_subscribed_list.insert(TSubscribedList::value_type(name, sp));
    }
  else
    (*it).second.update_subscribed_data_by_callid(sd, buf->tag);
::LeaveCriticalSection(&ss_subscrlist_cs);
}
//------------------------------------------------------------------------------
void __fastcall TSubscribedPar::add_subscribed_data_by_callid(TSubscribedData& sd)
{
lst.insert(TSubscriptionList::value_type(sd.callid, sd));
}
//------------------------------------------------------------------------------
bool __fastcall TSubscribedPar::find(const string& callid)
{
return lst.find(callid) == lst.end() ? false : true;
}
//------------------------------------------------------------------------------
void __fastcall TSubscribedPar::apply_network_parameters(const string& callid, TOutputSipBuf* buf)
{
TSubscriptionList::iterator it = lst.find(callid);
if(it != lst.end())
  {
  (*it).second.ToIP        = buf->ToIP;
  (*it).second.ToPort      = buf->ToPort;
  (*it).second.RequestLine = buf->requestline;
  (*it).second.To          = buf->To;
  (*it).second.From        = buf->from;
  (*it).second.set_cseq(buf->curr_cseq);
  }
}
//------------------------------------------------------------------------------
void __fastcall TSubscribedPar::inc_cseq(const string& callid)
{
TSubscriptionList::iterator it = lst.find(callid);
if(it != lst.end())
  (*it).second.inc_cseq();
}
//------------------------------------------------------------------------------
void __fastcall TSubscribedPar::update_subscribed_data_by_callid(TSubscribedData& sd, unsigned sec)
{
TSubscriptionList::iterator it = lst.find(sd.callid);
if(it == lst.end())
  lst.insert(TSubscriptionList::value_type(sd.callid, sd));
else
  {
  (*it).second.set_delta_and_next_sabscr_date(sec);
  (*it).second.set_real_subscr_next((*it).second.get_subscr_next());
  }
}
//-----------------------------------------------------------------------------
bool __fastcall TSubscribedPar::get_subscribed_data_by_callid(TSubscribedData& sd, const string& callid)
{
bool rv = false;
TSubscriptionList::iterator it = lst.find(callid);
if(it != lst.end())
  {
  sd = (*it).second;
  rv = true;
  }
return rv;
}
//------------------------------------------------------------------------------
void __fastcall TSubscribedPar::get_lst_copy_with_inc_cseq(queue<TSubscribedData>& q)
{
TSubscriptionList::iterator it = lst.begin();
while(it != lst.end())
     {
     (*it).second.inc_cseq();
     q.push((*it++).second);
     }
}
//------------------------------------------------------------------------------
void __fastcall TSubscribedPar::get_lst_copy_with_inc_cseq_and_store_comment(queue<TSubscribedData>& q, const string& comment)
{
TSubscriptionList::iterator it = lst.begin();
while(it != lst.end())
     {
     (*it).second.inc_cseq();
     (*it).second.state_note = comment;
     q.push((*it++).second);
     }
}
//------------------------------------------------------------------------------
void __fastcall TAcceptedStruct::add_subscribed_contact(const string& name,TExchBuf* buf, TDateTime& next_init_time)
{
::EnterCriticalSection(&accepted_list_cs);
  TAcceptedList::iterator it = accepted_list.find(name);
  if(it == accepted_list.end())
    {
    TSubscrPar sp;
    sp.name   = name;
    sp.callid = buf->callid;
    sp.set_cseq(buf->tag_1);
    sp.set_delta_and_next_sabscr_date(buf->tag);
    next_init_time = sp.get_subscr_next();
    accepted_list.insert(TAcceptedList::value_type(name,sp));
    }
  else
    {
    (*it).second.set_delta_and_next_sabscr_date(buf->tag);
     next_init_time = (*it).second.get_subscr_next();
    }
::LeaveCriticalSection(&accepted_list_cs);
}
//------------------------------------------------------------------------------
void __fastcall TSubscribedStruct::del_subscribed_contact(const string& name)
{
::EnterCriticalSection(&ss_subscrlist_cs);
  TSubscribedList::iterator it = ss_subscribed_list.find(name);
  if(it != ss_subscribed_list.end())
     ss_subscribed_list.erase(it);
::LeaveCriticalSection(&ss_subscrlist_cs);
delete_from_time_list__by_NAME(name);
}
//------------------------------------------------------------------------------
void __fastcall TAcceptedStruct::del_subscribed_contact(const string& name)
{
bool subsc_name_found = false;
TDateTime dt;
::EnterCriticalSection(&accepted_list_cs);
  TAcceptedList::iterator it = accepted_list.find(name);
  if(it != accepted_list.end())
    {
     dt = (*it).second.get_real_subscr_next();
     subsc_name_found = true;
     accepted_list.erase(it);
    }
::LeaveCriticalSection(&accepted_list_cs);
if(subsc_name_found)
  delete_from_time_list(dt, name);
}
//------------------------------------------------------------------------------
bool __fastcall TSubscribedStruct::subscribed_to_me(const string& name, const string& callid)
{
bool rv = false;
::EnterCriticalSection(&ss_subscrlist_cs);
  TSubscribedList::iterator it = ss_subscribed_list.find(name);
  if(it != ss_subscribed_list.end())
    if((*it).second.find(callid))
       rv = true;
::LeaveCriticalSection(&ss_subscrlist_cs);
return rv;
}
//------------------------------------------------------------------------------
bool __fastcall TAcceptedStruct::subscribed(const string& name)
{
bool rv = false;
::EnterCriticalSection(&accepted_list_cs);
  TAcceptedList::iterator it = accepted_list.find(name);
  if(it != accepted_list.end())
     rv = true;
::LeaveCriticalSection(&accepted_list_cs);
return rv;
}
//------------------------------------------------------------------------------
void __fastcall TSubscribedStruct::add_subscription_parameters(TExchBuf* buf)
{
::EnterCriticalSection(&ss_subscrlist_cs);
  TOutputSipBuf* add_buf = (TOutputSipBuf*)buf->getAddBuf_Reset();
  if(add_buf)
    {
    TSubscribedList::iterator it = ss_subscribed_list.find(buf->msg);  // buf->msg содержит called name, т.е. кому посылаем NOTIFY
    if(it != ss_subscribed_list.end())
      (*it).second.apply_network_parameters(buf->callid, add_buf);   //по имени и callid (т.к. на одном аккаунте может быть несколько абонентов)
    delete add_buf; //!!!!!
    }
::LeaveCriticalSection(&ss_subscrlist_cs);
}
//------------------------------------------------------------------------------
void __fastcall TAcceptedStruct::add_subscription_parameters(TExchBuf* buf)
{
::EnterCriticalSection(&accepted_list_cs);
  TOutputSipBuf* add_buf = (TOutputSipBuf*)buf->getAddBuf_Reset();
  if(add_buf)
    {
    TAcceptedList::iterator it = accepted_list.find(buf->msg);
    if(it != accepted_list.end())
      {
      (*it).second.ToIP        = add_buf->ToIP;
      (*it).second.ToPort      = add_buf->ToPort;
      (*it).second.RequestLine = add_buf->requestline;
      (*it).second.To          = add_buf->To;
      (*it).second.From        = add_buf->from;
      (*it).second.set_cseq(add_buf->curr_cseq);
      }
    delete add_buf; //!!!!!
    }
::LeaveCriticalSection(&accepted_list_cs);
}
//------------------------------------------------------------------------------
/*
void __fastcall TBaseSubscribeStruct::update_refreshing_time(const string& name, TDateTime& next_init_time)
{
::EnterCriticalSection(&subscrlist_cs);
  TSubscribedList::iterator it = subscribed_list.find(name);
  if(it != subscribed_list.end())
     (*it).second.update_timer(next_init_time);
::LeaveCriticalSection(&subscrlist_cs);
}
*/
//------------------------------------------------------------------------------
void __fastcall TAcceptedStruct::update_refreshing_time(const string& name, TDateTime& next_init_time)
{
::EnterCriticalSection(&accepted_list_cs);
  TAcceptedList::iterator it = accepted_list.find(name);
  if(it != accepted_list.end())
     (*it).second.update_timer(next_init_time);
::LeaveCriticalSection(&accepted_list_cs);
}
//------------------------------------------------------------------------------
bool __fastcall TSubscribedStruct::get_copy_of_subscribed_data(TSubscribedData& sd, const string& name, const string& callid, bool inc_cseq)
{
bool rv = false;
::EnterCriticalSection(&ss_subscrlist_cs);
  TSubscribedList::iterator it = ss_subscribed_list.find(name);
  if(it != ss_subscribed_list.end())
    {
     if(inc_cseq)
       (*it).second.inc_cseq(callid);
    if((*it).second.get_subscribed_data_by_callid(sd, callid))
       rv = true;
    }
::LeaveCriticalSection(&ss_subscrlist_cs);
return rv;
}
//------------------------------------------------------------------------------
bool __fastcall TAcceptedStruct::get_copy_of_subscrpar(TSubscrPar& sp, const TReadyOfRefreshSubsc& rrs)
{
bool rv = false;
::EnterCriticalSection(&accepted_list_cs);
  TAcceptedList::iterator it = accepted_list.find(rrs.name);
  if(it != accepted_list.end())
    {
    if(rrs.check_real_subscr_next)
      {
      if(rrs.dt == (*it).second.get_real_subscr_next())
        {
        (*it).second.inc_cseq();
        sp = (*it).second;
        rv = true;
        }
      }
    else
      {
      (*it).second.inc_cseq();
      sp = (*it).second;
      rv = true;
      }
    }
::LeaveCriticalSection(&accepted_list_cs);
return rv;
}
//------------------------------------------------------------------------------
bool __fastcall TAcceptedStruct::refresh_subscribe_proc(const TReadyOfRefreshSubsc& rrs)
{
bool rv = false;
TSubscrPar sp;
if(get_copy_of_subscrpar(sp, rrs))
  {
  MainFormSLS->Sip->init_Refreshing_SUBSCRIBE_Proc(sp);
  rv = true;
  }
return rv;
}
//------------------------------------------------------------------------------
void __fastcall TSubscribedStruct::get_temp_subscribed_list(TNotifyStruct* NS)
{
::EnterCriticalSection(&ss_subscrlist_cs);
  TSubscribedList::iterator it = ss_subscribed_list.begin();
  while(it != ss_subscribed_list.end())
       {
       queue<TSubscribedData> q;
       (*it++).second.get_lst_copy_with_inc_cseq(q);
       while(!q.empty())
            {
            NS->push_notify_queue(q.front());
            q.pop();
            }
       }
 ::LeaveCriticalSection(&ss_subscrlist_cs);
}
//------------------------------------------------------------------------------
void __fastcall TSubscribedStruct::get_temp_subscribed_list_for_send_comment(TNotifyStruct* NS, const string& comment)
{
::EnterCriticalSection(&ss_subscrlist_cs);
  TSubscribedList::iterator it = ss_subscribed_list.begin();
  while(it != ss_subscribed_list.end())
       {
       queue<TSubscribedData> q;
       (*it++).second.get_lst_copy_with_inc_cseq_and_store_comment(q, comment);
       while(!q.empty())
            {
            NS->push_notify_comment_queue(q.front());
            q.pop();
            }
       }
::LeaveCriticalSection(&ss_subscrlist_cs);
}
//------------------------------------------------------------------------------
bool __fastcall TSip::checkAccount()
{
if(!Account.get_user_name().empty())
    return true;
bool rv = false;
TRegistry& regKey = *new TRegistry();
regKey.RootKey = ROOT_KEY;
bool keyGood = regKey.OpenKey(key_name.c_str(),false);
if(!keyGood)
   keyGood = regKey.OpenKey(key_name.c_str(),true);
if(keyGood)
  {
  keyGood = regKey.OpenKey(acc_key_name.c_str(),false);
  if(!keyGood)
      keyGood = regKey.OpenKey(acc_key_name.c_str(),true);
  if(keyGood)
    {
    string pwd = regKey.ReadString(acc_pwd.c_str()).c_str();
    string user_name = regKey.ReadString(acc_name.c_str()).c_str();
    if(user_name.empty())
      {
      if(!rp)
          rp = new TRegistryPanel(Application);
      if(rp)
        {
        resize_reg_win();
        rp->FormStyle = fsStayOnTop;
        rp->Position  = poScreenCenter;
        rp->Show();
        }
      }
    else
      {
      vector<UBYTE> v_name;
      vector<UBYTE> v_pwd;
      TClientReg cr;
      cr.dig_str_to_vect(v_name,user_name);
      cr.dig_str_to_vect(v_pwd,pwd);
      Account.set_user_name(cr.decrypt(v_name));
      Account.set_user_pwd(cr.decrypt(v_pwd));
      rv = true;
      }
    }
  regKey.CloseKey();
  }
delete &regKey;
return rv;
}
//------------------------------------------------------------------------------
void __fastcall TSip::resize_reg_win()
{
if(rp)
 if(Account.get_displayname() == local_display_name)
   {
   rp->Edit3->Visible  = true;
   rp->Label3->Visible = true;
   rp->Button1->Top    = rp->Edit3->Top + rp->Edit3->Height + 20;
   rp->Button2->Top    = rp->Button1->Top;
   rp->Height          = rp->Button1->Top + rp->Button1->Height + 40 + 20;
   }
 else
   {
   rp->Edit3->Visible  = false;
   rp->Label3->Visible = false;
   rp->Button1->Top    = rp->Edit2->Top + rp->Edit2->Height + 20;
   rp->Button2->Top    = rp->Button1->Top;
   rp->Height          = rp->Button1->Top + rp->Button1->Height + 40 + 20;
   }
}
//------------------------------------------------------------------------------
void __fastcall TSip::open_reg_win()
{
if(!rp)
   rp = new TRegistryPanel(Application);
if(rp)
  {
  resize_reg_win();
  rp->Edit1->Clear();
  rp->FormStyle = fsStayOnTop;
  rp->Position  = poScreenCenter;
  rp->read_account();
  rp->read_client_accounts();
  rp->Show();
  }
}
//------------------------------------------------------------------------------
void __fastcall TSip::hide_registry_panel()
{
if(rp)
  if(rp->Visible)
     rp->Hide();
}
//-----------------------------------------------------------------------------
void __fastcall TSip::prepare_auth_responce(TAuthPar* auth_par,const string& method)
{
char * pszNonce      = (char*)auth_par->rcvdnonce.c_str();
char * pszCNonce     = "";
char * pszUser       = (char*)auth_par->user_name.c_str();
char * pszRealm      = (char*)auth_par->rcvdrealm.c_str();
char * pszPass       = (char*)auth_par->user_pwd.c_str();
char * pszAlg        = "MD5";
char szNonceCount[9] = "00000001";
char * pszMethod     = (char*)method.c_str();
char * pszQop        = "";
string uri = "sip:"  + auth_par->domain;   //!!!do not make char * pszURI = (char*)("sip:" + Account.domain).c_str() at once
char * pszURI        = (char*)uri.c_str();
HASHHEX HA1;
HASHHEX HA2 = "";
HASHHEX Response;
/*
string s = "\npassw=" + string(pszPass) + "!\n" +
"user_name=" + string(pszUser) + "!\n" +
"realm=" + string(pszRealm) + "!\n" +
"method=" + string(pszMethod)+ "!\n" +
"uri=" + string(pszURI) + "!\n";
Log(s);
*/
DigestCalcHA1(pszAlg, pszUser, pszRealm, pszPass, pszNonce,pszCNonce, HA1);
DigestCalcResponse(HA1,pszNonce,szNonceCount,pszCNonce,pszQop,pszMethod,pszURI,HA2,Response);
auth_par->calc_response = string(Response);
}
//------------------------------------------------------------------------------
void __fastcall TSip::prepare_authorization_header(TOutputSipBuf* ospb,TAuthPar* auth_par)
{
/*
ospb->authorization = "Authorization: Digest username=" + (string)"\"" + Account.get_user_name() + "\",realm=" +
                      "\"" + auth_par->rcvdrealm + "\",nonce=" + "\"" + auth_par->rcvdnonce + "\",uri="  +
                      "\"" + "sip:" + Account.get_domain() + "\",response=" + "\"" + auth_par->calc_response + "\","  +
                      "algorithm=MD5,opaque=" + "\"" +  auth_par->rcvdopaque + "\"" + crlf;
*/

ospb->authorization = "Authorization: Digest username=" + (string)"\"" + auth_par->user_name + "\",realm=" +
                      "\"" + auth_par->rcvdrealm + "\",nonce=" + "\"" + auth_par->rcvdnonce + "\",uri="  +
                      "\"" + "sip:" + auth_par->domain + "\",response=" + "\"" + auth_par->calc_response + "\","  +
                      "algorithm=MD5,opaque=" + "\"" +  auth_par->rcvdopaque + "\"" + crlf;
}
//------------------------------------------------------------------------------
void __fastcall TSip::sendAuthRegistration(TAuthPar* auth_par)
{
TOutputSipBuf* ospb = prepare_Auth_REGISTER_Req(auth_par);
if(ospb)
 if(uac)
   {
   uac->setQueue(ospb);
   updateSentQueue_1(ospb);
   }
}
//------------------------------------------------------------------------------
void __fastcall TSip::sendAuthInvite(TAuthPar* auth_par,const string& callid)
{
TOutputSipBuf* ospb = prepare_Auth_INVITE_Req(auth_par,callid);
if(ospb)
 if(uac)
   {
   uac->setQueue(ospb);
   updateSentQueue_1(ospb);
   }
}
//------------------------------------------------------------------------------
void __fastcall TSip::sendAuthMessage(TAuthPar* auth_par,const string& callid)
{
TOutputSipBuf* ospb = prepare_Auth_MESSAGE_Req(auth_par,callid);
if(ospb)
 if(uac)
   {
   uac->setQueue(ospb);
   updateSentQueue_1(ospb);
   }
}
//------------------------------------------------------------------------------
TOutputSipBuf* __fastcall TSip::prepare_Auth_REGISTER_Req(TAuthPar* auth_par)
{
TOutputSipBuf* ospb = new TOutputSipBuf;
if(ospb)
  {
  ospb->setsls(SPS_AUTH_REGISTER_REQ);
  ospb->ToIP   = SipProxy.IPAddr;
  ospb->ToPort = SipProxy.Port;
  ospb->callid = auth_par->callid;
  prepareRequestLine_REGISTER(ospb);
  prepareMaxForwards(70,ospb);
  if(auth_par->sls == SPS_FINAL_REGISTER_REQ)
     prepare_Final_REGISTER_Contact(auth_par, ospb);
  else
     prepareContact(ospb);
  prepareInitialTo(auth_par->user_name, strempty, auth_par->domain, ospb);
  prepareCSeq(crh.getCSeqRegister(),"REGISTER",ospb);
  if(auth_par->sls != SPS_FINAL_REGISTER_REQ)
     prepareExpires(regint,ospb);
  prepareAllow(ospb);
  prepareUserAgent(ospb);
  prepare_authorization_header(ospb,auth_par);
  prepareContentLength_0(ospb);
  }
return ospb;
}
//------------------------------------------------------------------------------
TOutputSipBuf* __fastcall TSip::prepare_Auth_INVITE_Req(TAuthPar* auth_par,const string& callid)
{
TOutputSipBuf* ospb = new TOutputSipBuf;
if(ospb)
  {
  ospb->setsls(SPS_AUTH_INVITE_REQ);
  ospb->ToIP   = SipProxy.IPAddr;
  ospb->ToPort = SipProxy.Port;
  prepareViaHeader(ospb);
  prepareMaxForwards(70,ospb);
  prepareContact(ospb);
  ospb->callid = callid;
  prepareAllow(ospb);
  prepareUserAgent(ospb);
  prepare_authorization_header(ospb,auth_par);
  }
return ospb;
}
//------------------------------------------------------------------------------
TOutputSipBuf* __fastcall TSip::prepare_Auth_MESSAGE_Req(TAuthPar* auth_par,const string& callid)
{
TOutputSipBuf* ospb = new TOutputSipBuf;
if(ospb)
  {
  ospb->setsls(SPS_AUTH_MESSAGE_REQ);
  ospb->ToIP   = SipProxy.IPAddr;
  ospb->ToPort = SipProxy.Port;
  prepareViaHeader(ospb);
  prepareMaxForwards(70,ospb);
  prepareContact(ospb);
  ospb->callid = callid;
  prepareAllow(ospb);
  prepareUserAgent(ospb);
  prepare_authorization_header(ospb,auth_par);
  }
return ospb;
}
//-------------------------------------------------------------------------------
void __fastcall TSip::update_contact_file()
{
FILE* f = fopen((contact_dir + "\\" + contact_file).c_str(),"wt");
if(f)
  {
  Contacts.commit_contact_list(f);
  fclose(f);
  }
}
//------------------------------------------------------------------------------
/*
bool __fastcall TSip::update_contact_file_with_own_account()
{
bool rv = false;
TContact* Cont = new TContact(Contacts.get_next_contact_id());
if(Cont)
  {
  Cont->name      = Account.user_name;
  Cont->full_name = Account.displayname;
  Contacts.add_contact(Cont,MainFormSLS->DrawGrid1);
  update_contact_file();
  Contacts.del_contact(Cont->get_id());
  rv = true;
  }
return rv;
}
*/
//------------------------------------------------------------------------------
void __fastcall TSip::SetOutQueue(void* opb)
{
bool rv = false;
TSipSendThread* SST              = getTSipSendThread();
TSipSendTunnelThread* SS_TUNNELT = getTSipSendTunnelThread();
if(SST)
  {
  SST->setQueue(opb);
  return;
  }
if(ss_tls_t)
  {
  ss_tls_t->setQueue(opb);
  return;
  }

::EnterCriticalSection(&tcp_t_cs);
  if(ss_tcp_t)
    {
    ss_tcp_t->setQueue(opb);
    rv = true;
    }
::LeaveCriticalSection(&tcp_t_cs);
if(rv)return;

if(SS_TUNNELT)
  {
  SS_TUNNELT->setQueue(opb);
  return;
  }
}
//------------------------------------------------------------------------------
void __fastcall TSip::create_work_threads()
{
switch(sip_transport){
       case Sip_Transport_TCP:{
            checkAccount();
            if(!SipTCP.IPAddr.empty())
              if(SipTCP.Port)
                {
                ::EnterCriticalSection(&tcp_t_cs);
                  sr_tcp_t   = new TSipRecvTcpThread(true,SipTCP.IPAddr,SipTCP.Port,eltp,this);
                  if(sr_tcp_t)
                    sr_tcp_t->Resume_Thread();
                  ss_tcp_t = new TSipSendTcpThread(true,SipTCP.IPAddr,SipTCP.Port,eltp,this); //Resume after connect
                ::LeaveCriticalSection(&tcp_t_cs);
                }
            break;
            }
       case Sip_Transport_TLS:{
            checkAccount();
            if(!SipTLS.IPAddr.empty())
              if(SipTLS.Port)
                {
                sr_tls_t = new TSipRecvTlsThread(true,SipTLS.IPAddr,SipTLS.Port,eltp,this);
                if(sr_tls_t)
                   sr_tls_t->Resume_Thread();
                ss_tls_t = new TSipSendTlsThread(true,SipTLS.IPAddr,SipTLS.Port,eltp,this); //Resume after connect
                }
            break;
            }
       case Sip_Transport_TUNNEL:{
            checkAccount();
            if(!SipTunnel.IPAddr.empty())
              if(SipTunnel.Port)
                {
                sr_tunnel_t = new TSipRecvTunnelThread(true,SipTunnel.IPAddr,SipTunnel.Port,eltp,this);
                if(sr_tunnel_t)
                   sr_tunnel_t->Resume_Thread();
                ss_tunnel_t = new TSipSendTunnelThread(true,SipTunnel.IPAddr,SipTunnel.Port,eltp,this); //Resume after connect
                }
            break;
            }
       case Sip_Transport_UDP:{
            sst = new TSipSendThread(true,eltp,sck,this);
            if(Sip_TransportAuto)
              {
              if(!standby_ss_tunnel_t)
                {
                standby_ss_tunnel_t = new TSipSendTunnelThread(true,SipTunnel.IPAddr,SipTunnel.Port,eltp,this);
                if(standby_ss_tunnel_t)
                   standby_ss_tunnel_t->set_thread_block();
                }
              }
            break;
            }
       }

uas  = new TSipUasThread(true,eltp,this,0);
uac  = new TSipUacThread(true,eltp,this,0);
spt  = new TSipParsThread(true,eltp,this,0);
ucs  = new TUdpChannelStruct(true,eltp,this);
pst  = new TPlaySoundThread(true,eltp,this);
if(sip_transport == Sip_Transport_UDP)
  {
  srt  = new TSipRecvThread(true,eltp,sck,this);
  if(Sip_TransportAuto)
    {
    if(!standby_sr_tunnel_t)
      {
      standby_sr_tunnel_t = new TSipRecvTunnelThread(true,SipTunnel.IPAddr,SipTunnel.Port,eltp,this);
      if(standby_sr_tunnel_t)
         standby_sr_tunnel_t->set_thread_block();
      }
    }
  }
sss  = new TMediaSessionStruct();
}
//------------------------------------------------------------------------------
void __fastcall TSip::sip_active_2_standby(TSipRecvThread* SRT, TSipSendThread* SST)
{
SRT->set_thread_block();
SST->set_thread_block();
standby_srt = SRT;
standby_sst = SST;
srt         = NULL;
sst         = NULL;
}
//------------------------------------------------------------------------------
void __fastcall TSip::sip_tunnel_standby_2_active(TSipRecvTunnelThread* SR_STANDBY_TUNNEL_T,TSipSendTunnelThread* SS_STANDBY_TUNNEL_T)
{
sr_tunnel_t         = SR_STANDBY_TUNNEL_T;
ss_tunnel_t         = SS_STANDBY_TUNNEL_T;
standby_sr_tunnel_t = NULL;
standby_ss_tunnel_t = NULL;
sr_tunnel_t->reset_thread_block();
ss_tunnel_t->reset_thread_block();
}
//------------------------------------------------------------------------------
void __fastcall TSip::sip_udp_tunnel(
                                     TSipRecvThread* SRT, TSipSendThread* SST,
                                     TSipRecvTunnelThread* SR_STANDBY_TUNNEL_T,TSipSendTunnelThread* SS_STANDBY_TUNNEL_T
                                    )
{
sip_active_2_standby(SRT, SST);
sip_tunnel_standby_2_active(SR_STANDBY_TUNNEL_T, SS_STANDBY_TUNNEL_T);
sip_transport = Sip_Transport_TUNNEL;
TSipRecvTunnelThread* SR_TUNNEL_T = getTSipRecvTunnelThread();
if(SR_TUNNEL_T)
  if(SR_TUNNEL_T->Suspended)
     SR_TUNNEL_T->Resume_Thread();
}
//------------------------------------------------------------------------------
void __fastcall TSip::change_sip_transport()
{
if(sip_transport == Sip_Transport_UDP)
   change_sip_transport_UDP_TUNNEL();
else if(sip_transport == Sip_Transport_TUNNEL)
   change_sip_transport_TUNNEL_UDP();
}
//------------------------------------------------------------------------------
void __fastcall TSip::change_sip_transport_UDP_TUNNEL()
{
::EnterCriticalSection(&ch_transp_cs);
  TSipRecvThread* SRT = getTSipRecvThread();
  TSipSendThread* SST = getTSipSendThread();
  TSipRecvTunnelThread* SR_STANDBY_TUNNEL_T = getStandbyTSipRecvTunnelThread();
  TSipSendTunnelThread* SS_STANDBY_TUNNEL_T = getStandbyTSipSendTunnelThread();
  if(SRT)
    if(SST)
      if(SR_STANDBY_TUNNEL_T)
        if(SS_STANDBY_TUNNEL_T)
           sip_udp_tunnel(SRT, SST, SR_STANDBY_TUNNEL_T, SS_STANDBY_TUNNEL_T);
::LeaveCriticalSection(&ch_transp_cs);
}
//------------------------------------------------------------------------------
void __fastcall TSip::change_sip_transport_TUNNEL_UDP()
{
::EnterCriticalSection(&ch_transp_cs);
  TSipRecvTunnelThread* SR_TUNNEL_T = getTSipRecvTunnelThread();
  TSipSendTunnelThread* SS_TUNNEL_T = getTSipSendTunnelThread();
  TSipRecvThread* STANDBY_SRT       = getStandbyTSipRecvThread();
  TSipSendThread* STANDBY_SST       = getStandbyTSipSendThread();
  if(SR_TUNNEL_T)
    if(SS_TUNNEL_T)
      if(STANDBY_SRT)
        if(STANDBY_SST)
           sip_tunnel_udp(SR_TUNNEL_T, SS_TUNNEL_T, STANDBY_SRT, STANDBY_SST);
::LeaveCriticalSection(&ch_transp_cs);
}
//------------------------------------------------------------------------------
void __fastcall TSip::sip_tunnel_udp(
                                    TSipRecvTunnelThread* SR_TUNNEL_T, TSipSendTunnelThread* SS_TUNNEL_T,
                                    TSipRecvThread* STANDBY_SRT, TSipSendThread* STANDBY_SST
                                    )
{
sip_tunnel_active_2_standby(SR_TUNNEL_T, SS_TUNNEL_T);
sip_standby_2_active(STANDBY_SRT, STANDBY_SST);
sip_transport = Sip_Transport_UDP;
}
//------------------------------------------------------------------------------
void __fastcall TSip::sip_tunnel_active_2_standby(TSipRecvTunnelThread* SR_TUNNEL_T, TSipSendTunnelThread* SS_TUNNEL_T)
{
SR_TUNNEL_T->set_thread_block();
SS_TUNNEL_T->set_thread_block();
standby_sr_tunnel_t = SR_TUNNEL_T;
standby_ss_tunnel_t = SS_TUNNEL_T;
sr_tunnel_t = NULL;
ss_tunnel_t = NULL;
}
//------------------------------------------------------------------------------
void __fastcall TSip::sip_standby_2_active(TSipRecvThread* STANDBY_SRT, TSipSendThread* STANDBY_SST)
{
srt = STANDBY_SRT;
sst = STANDBY_SST;
standby_srt = NULL;
standby_sst = NULL;
srt->reset_thread_block();
sst->reset_thread_block();
}
//------------------------------------------------------------------------------
void __fastcall TSip::log_selected_transport()
{
string s = "\nTransport: ";
switch(sip_transport){
       case Sip_Transport_UDP:
            s += "UDP";
            break;
       case Sip_Transport_TCP:
            s += "TCP";
            break;
       case Sip_Transport_TLS:
            s += "TLS";
            break;
       case Sip_Transport_TUNNEL:
            s += "TUNNEL";
            break;
       default: s += "UNKNOWN";
       }
if(Sip_TransportAuto)
  s += " AUTO";
Log(s);
}
//------------------------------------------------------------------------------
/*
void __fastcall TBaseSubscribeStruct::insert_in_time_list(TDateTime dt, const string& name)
{
bool subsc_name_found = false;
::EnterCriticalSection(&subscrlist_cs);
  TSubscribedList::iterator it = subscribed_list.find(name);
  if(it != subscribed_list.end())
    {
    (*it).second.set_real_subscr_next(dt);
    subsc_name_found = true;
    }
::LeaveCriticalSection(&subscrlist_cs);
if(subsc_name_found)
  {
  ::EnterCriticalSection(&tl_cs);
    tl.insert(TTimeList::value_type(dt,name));
  ::LeaveCriticalSection(&tl_cs);
  }
}
*/
//------------------------------------------------------------------------------
void __fastcall TAcceptedStruct::insert_in_time_list(TDateTime dt, const string& name)
{
bool subsc_name_found = false;
::EnterCriticalSection(&accepted_list_cs);
  TAcceptedList::iterator it = accepted_list.find(name);
  if(it != accepted_list.end())
    {
    (*it).second.set_real_subscr_next(dt);
    subsc_name_found = true;
    }
::LeaveCriticalSection(&accepted_list_cs);
if(subsc_name_found)
  {
  ::EnterCriticalSection(&as_tl_cs);
    as_tl.insert(TTimeList::value_type(dt,name));
  ::LeaveCriticalSection(&as_tl_cs);
  }
}
//------------------------------------------------------------------------------
//-- сначала удаляются все просроченные записи у которых Current datetime > (*it).first + TDateTime(0,0,20,0)
//-- затем удаляются все записи у которых (*it).second.name == name независимо от (*it).second.callid
//------------------------------------------------------------------------------
void __fastcall TSubscribedStruct::delete_from_time_list__by_NAME(const string& name)
{
::EnterCriticalSection(&ss_tl_cs);
  TDateTime cdt = cdt.CurrentDateTime() + TDateTime(0,0,20,0); //CurrentDateTime + 20 sec
  TTimeList::iterator it = ss_tl.begin();
  while(it != ss_tl.end())
       {
       if((*it).first < cdt)
          break;   //not yet expires
       else
         {         //данная запись к настоящему моменту уже должна быть отработана и заменена на другую, более позднюю. Если нет, то удаляем без сожаления !!!
         ss_tl.erase(it);
         it = ss_tl.begin();
         continue;
         }
       }
  if(!ss_tl.empty())
    {
    TTimeList temp_ss_tl;       //Переносим все записи, у которых (*it).second.name != name в temp_ss_tl
    it = ss_tl.begin();
    while(it != ss_tl.end())
         {
         if((*it).second.name != name)
            temp_ss_tl.insert(TTimeList::value_type((*it).first, (*it).second));
         it++;
         }
    ss_tl = temp_ss_tl;
    }
::LeaveCriticalSection(&ss_tl_cs);
}
//-----------------------------------------------------------------------------
void __fastcall TAcceptedStruct::delete_from_time_list(TDateTime dt, const string& name)
{
::EnterCriticalSection(&as_tl_cs);
  TTimeList::iterator it = as_tl.find(dt);
  while(it != as_tl.end())
       {
       if((*it).first == dt)
         if((*it).second == name)
           {
           as_tl.erase(it);
           break;
           }
       it++;
       }
::LeaveCriticalSection(&as_tl_cs);
}
//-----------------------------------------------------------------------------
void __fastcall TSubscribedStruct::clear_time_list()
{
::EnterCriticalSection(&ss_tl_cs);
  ss_tl.clear();
::LeaveCriticalSection(&ss_tl_cs);
}
//-----------------------------------------------------------------------------
void __fastcall TAcceptedStruct::clear_time_list()
{
::EnterCriticalSection(&as_tl_cs);
  as_tl.clear();
::LeaveCriticalSection(&as_tl_cs);
}
//-----------------------------------------------------------------------------
void __fastcall TAcceptedStruct::get_ready_to_subscribe_list(queue<TReadyOfRefreshSubsc>& q)
{
::EnterCriticalSection(&as_tl_cs);
  TDateTime dt;
  dt = dt.CurrentDateTime();
  TTimeList::iterator it = as_tl.begin();
  while(it != as_tl.end())
       {
       if((*it).first <= dt)
         {
         TReadyOfRefreshSubsc rrs;
         rrs.check_real_subscr_next = true;
         rrs.dt   = (*it).first;
         rrs.name = (*it).second;
         q.push(rrs);
         as_tl.erase(it);
         it = as_tl.begin();
         }
       else
         break;
       }
::LeaveCriticalSection(&as_tl_cs);
}
//------------------------------------------------------------------------------
void __fastcall TContacts::Refresh_Presence_Subscribe()
{
try{
queue<TReadyOfRefreshSubsc> q;
AS.get_ready_to_subscribe_list(q);
while(!q.empty())
  {
  TReadyOfRefreshSubsc rrs = q.front();
  q.pop();
  if(AS.refresh_subscribe_proc(rrs))
    {
    TDateTime next_subcr_time;
    AS.update_refreshing_time(rrs.name, next_subcr_time);
    TDateTime adv = TDateTime(0,0,15,0);
    next_subcr_time -= adv;
    if(adv.CurrentDateTime() < next_subcr_time)
       AS.insert_in_time_list(next_subcr_time, rrs.name);
    }
  }
}
catch(Exception& e){exsSstEXCEPTION(MainFormSLS->ofs->elt,"__Refresh_Presence_Subscribe()",e);}
}
//------------------------------------------------------------------------------
/*
void __fastcall TBaseSubscribeStruct::get_full_subscribe_list(queue<TSubscrPar>& q)
{
::EnterCriticalSection(&subscrlist_cs);
  TSubscribedList::iterator it = subscribed_list.begin();
  while(it != subscribed_list.end())
       q.push((*it++).second);
::LeaveCriticalSection(&subscrlist_cs);
}
*/
//------------------------------------------------------------------------------
void __fastcall TAcceptedStruct::get_full_subscribe_list(queue<TSubscrPar>& q)
{
::EnterCriticalSection(&accepted_list_cs);
  TAcceptedList::iterator it = accepted_list.begin();
  while(it != accepted_list.end())
       q.push((*it++).second);
::LeaveCriticalSection(&accepted_list_cs);
}
//------------------------------------------------------------------------------
void __fastcall TAcceptedStruct::update_person_lst(TExchBuf* buf, string& log)
{
::EnterCriticalSection(&accepted_list_cs);
  TAcceptedList::iterator it = accepted_list.find(buf->callid); //buf->callid contains client name from which was received 202 Responce
  if(it != accepted_list.end())
    (*it).second.update_notify_list(buf, log); // добавить новый person_id или проапдейтить существующий
  else
    log += "\naccepted_list does not contain user_name \"" + buf->callid + "\"";
::LeaveCriticalSection(&accepted_list_cs);
}
//------------------------------------------------------------------------------
int __fastcall TAcceptedStruct::delete_from_person_lst(TExchBuf* buf, string& log)
{
int rv = -1;
::EnterCriticalSection(&accepted_list_cs);
  TAcceptedList::iterator it = accepted_list.find(buf->callid); //buf->callid contains client name from which was received 202 Responce
  if(it != accepted_list.end())
    {
    rv = (*it).second.delete_from_notify_list(buf, log); // Удалить person_id из списка
    if(!rv) //нет больше ни одного personal_id с таким user_name
      accepted_list.erase(it);
    }
  else
    log += "\naccepted_list does not contain user_name \"" + buf->callid + "\"";
::LeaveCriticalSection(&accepted_list_cs);
return rv;
}
//------------------------------------------------------------------------------
void __fastcall TSubscrPar::update_notify_list(TExchBuf* buf, string& log)
{
log += "\nbefore " + inttostr(lst.size());
TNotifyList::iterator it = lst.begin();
while(it != lst.end())
      log += " " + (*it++).first;

while(lst.size() > 5)  //Проверить список, если длина > 10, то убрать первые (не совсем корректно - первые - не значит самые старые (map <string tag>))
     {
     log += "\nlst.size() == " + inttostr(lst.size()) + "( > 5)";
     TNotifyList::iterator it = lst.begin();
     log += " erased " + (*it).first;
     lst.erase(it);
     }

if(!buf->msg_6.empty()) //msg_6 contains  from_tag
  {
  check_person_id(buf->msg_6, buf->msg_5);         //  buf->msg_6 contains  from_tag,  buf->msg_5 contains person_id
  TNotifyList::iterator it = lst.find(buf->msg_6); //  from_tag
  if(it == lst.end())
    {
    TNotifyData nd;
    nd.person_id = buf->msg_5;                       // person_id
    lst.insert(TNotifyList::value_type(buf->msg_6, nd)); //новый from_tag.
    }
  else
    {
    if(!buf->msg_5.empty())
      (*it).second.person_id = buf->msg_5;
    }
  }
log += "\nafter  " + inttostr(lst.size());
it = lst.begin();
while(it != lst.end())
     log += " " + (*it++).first;
log += "\n";
}
//-------------------------------------------------------------------------------------
//-- Небходимо удалить из списка все nd, у которых тот-же person-id но другой from_tag.
//-- Если такие есть -- это свидетельствует о том что был перезапущен switch,
//-- а данные клиенты оставались активны.
//-------------------------------------------------------------------------------------
void __fastcall TSubscrPar::check_person_id(const string& from_tag, const string& person_id)
{
TNotifyList::iterator it = lst.begin();
while(it != lst.end())
     {
     if((*it).second.person_id == person_id)
       if((*it).first != from_tag)
         {
         lst.erase(it);
         break;
         }
     it++;
     }
}
//-----------------------------------------------------------------------------
int __fastcall TSubscrPar::delete_from_notify_list(TExchBuf* buf, string& log)
{
int lst_sz_before = lst.size();
log += "\nbefore " + inttostr(lst_sz_before);
TNotifyList::iterator it = lst.begin();
while(it != lst.end())
      log += " " + (*it++).first;
if(lst_sz_before < 2)
  {
  lst.clear();
  log += " lst.size() < 2, cleared";
  }
else
  {
  if(!buf->msg_6.empty()) //msg_6 contains  from_tag
    {
    TNotifyList::iterator it = lst.find(buf->msg_6);
    if(it != lst.end())
      lst.erase(it);
    }
  }
int rv = lst.size();;
log += "\nafter  " + inttostr(rv);
it = lst.begin();
while(it != lst.end())
     log += " " + (*it++).first;
log += "\n";
return rv;
}
//------------------------------------------------------------------------------
//------------------------- OnCloseQwery() -------------------------------------
//------------------------------------------------------------------------------
void __fastcall TAcceptedStruct::Final_Subscribe_Proc()
{
queue<TSubscrPar> q;
get_full_subscribe_list(q);
while(!q.empty())
     {
     TSubscrPar sp = q.front();
     q.pop();
     sp.inc_cseq();
     sp.expires = 0; //!!!
     MainFormSLS->Sip->init_Refreshing_SUBSCRIBE_Proc(sp);
     }
}
//------------------------------------------------------------------------------
void __fastcall TLastCallStruct::update_last_call_list(TContact& contact, TDateTime& TimeStmp,im_text_type imtt, bool SELECTED, TDrawGrid* DrawGrid)
{
block_repaint = true;
::EnterCriticalSection(&lc_contlist_cs);
  TimeStmp = TimeStmp.CurrentDateTime();
  TLists::TLC_Contact_List::iterator it = Lists->lcl.find(contact.name);
  if(it != Lists->lcl.end())
    {
    TDateTime old_dt = (*it).second;
    Lists->lcl.erase(it);
    TLists::TLC_DateTime_List::iterator it_dt = Lists->ldl.find(old_dt);
    while(it_dt != Lists->ldl.end())
         {
         if((*it_dt).first != old_dt)
            break;
         if((*it_dt).second.name == contact.name)
           {
           Lists->ldl.erase(it_dt);
           break;
           }
         it_dt++;
         }
    }
  if(ceil(TimeStmp) > Lists->today)
    {
    Lists->today = ceil(TimeStmp);
    TLastCallStr lcs(LastCallStrType_DateTime, Lists->today);
    Lists->ldl.insert(TLists::TLC_DateTime_List::value_type(lcs.dt,lcs));
    }
  if(contact.get_id() == -1)    //Contact is NOT from ContactList (External)
    {
    TLastCallStr lcs(LastCallStrType_ContactExt, TimeStmp);
    lcs.name      = contact.name;
    lcs.full_name = contact.full_name;
    if(imtt == IM_CALL_IN_MISSED)
      {
      lcs.inc_missed_calls();                  //для того чтобы нарисовать желтый знак о пропущенном вызове по конкретному звонившему абоненту
      Lists->update_missed_name(contact.name); //update общий список абонентов от которых пропущены вызовы
      MainFormSLS->TrayMessage_Ext(NIM_MODIFY,"Contact",3);
      }
    Lists->ldl.insert(TLists::TLC_DateTime_List::value_type(lcs.dt, lcs));
    Lists->lcl.insert(TLists::TLC_Contact_List::value_type(lcs.name, lcs.dt));
    }
  else                          //Contact is from ContactList (Internal)
    {
    TLastCallStr lcs(LastCallStrType_ContactInt, TimeStmp);
    lcs.name      = contact.name;
    lcs.full_name = contact.full_name;
    Lists->ldl.insert(TLists::TLC_DateTime_List::value_type(lcs.dt,lcs));
    Lists->lcl.insert(TLists::TLC_Contact_List::value_type(lcs.name, lcs.dt));
    if(imtt == IM_CALL_IN_MISSED)
    //  if(!SELECTED)
         Lists->update_missed_name(contact.name); //update общий список абонентов от которых пропущены вызовы
    }
  DrawGrid->RowCount = Lists->ldl.size();
::LeaveCriticalSection(&lc_contlist_cs);
block_repaint = false;
}
//------------------------------------------------------------------------------
void __fastcall TLastCallStruct::update_last_call_file(TContact& contact, TDateTime TimeStmp)
{
if(MainFormSLS->Im.LCFT)
  {
  TLCSBuf* LCSBuf = new TLCSBuf(WRITE);
  if(LCSBuf)
    {
    int length = contact.name.length();
    if(length)
      if(length < (sizeof(LCSBuf->name) - 1))
        {
        memcpy(&LCSBuf->name[0], contact.name.c_str(), length);
        memcpy(&LCSBuf->date[0], (UBYTE*)&TimeStmp, LAST_CALL_DATE_LENGTH);
        MainFormSLS->Im.LCFT->push_lcs_buf(LCSBuf);
        return;
        }
    delete LCSBuf;  // contact.name.length() >= sizeof(LCSBuf->name)
    }
  }
}
//------------------------------------------------------------------------------
bool __fastcall TLastCallStruct::get_copy_of_last_call_by_row(TLastCallStr& lcs, int Row)
{
bool rv = false;
::EnterCriticalSection(&lc_contlist_cs);
  int i=0;
  TLists::TLC_DateTime_List::reverse_iterator it = Lists->ldl.rbegin();
  while(it != Lists->ldl.rend())
       {
       if(Row == i)
         {
         lcs = (*it).second;
         rv = true;
         break;
         }
       it++, i++;
       }
::LeaveCriticalSection(&lc_contlist_cs);
return rv;
}
//------------------------------------------------------------------------------
void __fastcall TLastCallStruct::ResMissedCalls(const string& name)
{
::EnterCriticalSection(&lc_contlist_cs);
  if(Lists)
    {
    TLists::TLC_DateTime_List::iterator it = Lists->ldl.begin();
    while(it != Lists->ldl.end())
         {
         if((*it).second.name == name)
           {
           (*it).second.res_missed_calls();
           break;
           }
         it++;
         }
    }
::LeaveCriticalSection(&lc_contlist_cs);
}
//------------------------------------------------------------------------------
void __fastcall TLastCallStruct::DeleteMissedName(const string& s)
{
::EnterCriticalSection(&lc_contlist_cs);
  if(Lists)
     Lists->delete_missed_name(s);
::LeaveCriticalSection(&lc_contlist_cs);
}
//------------------------------------------------------------------------------
bool __fastcall TLastCallStruct::MissedNameEmpty()
{
bool rv = false;
::EnterCriticalSection(&lc_contlist_cs);
  if(Lists)
    if(Lists->empty())
       rv = true;
::LeaveCriticalSection(&lc_contlist_cs);
return rv;
}
//------------------------------------------------------------------------------
bool __fastcall TLastCallStruct::GetFirstMissedName(string& s)
{
bool rv = false;
::EnterCriticalSection(&lc_contlist_cs);
  rv = Lists->get_first_missed_name(s);
::LeaveCriticalSection(&lc_contlist_cs);
return rv;
}
//------------------------------------------------------------------------------
void __fastcall TLastCallStruct::CHANGE_LISTS(TLists* NewLists)
{
::EnterCriticalSection(&lc_contlist_cs);
  TLists* L = Lists;
  Lists = NULL;
  if(L)
     delete L;
  Lists = NewLists;
   //MainFormSLS->DG_LastCalls->RowCount = Lists->ldl.size(); //!!! Нельзя этого делать (Только PostMessage)
  ::PostMessage(MainFormSLS->Handle, CONTROL_MSG, WM_APP_MSG_WPARAM__LAST_CALLS__DRAWGRID_ROW_COUNT, Lists->ldl.size());
::LeaveCriticalSection(&lc_contlist_cs);
}
//------------------------------------------------------------------------------
//----- Saved comment FROM contact ---------------------------------------------
//------------------------------------------------------------------------------
void __fastcall TContacts::save_contact_comment(const string& name, const string& comment)
{
if(MainFormSLS->Im.LCFT)  //Thread для работы с файлом содержащим последние вызовы (Last Calls)
  {
  TLCSBuf* LCSBuf = new TLCSBuf(SAVE_CONTACT_COMMENT);
  if(LCSBuf)
    {
    LCSBuf->s   = name;
    LCSBuf->s_1 = comment;
    MainFormSLS->Im.LCFT->push_lcs_buf(LCSBuf);
    }
  }
}
//------------------------------------------------------------------------------
void __fastcall TContacts::clear_contact_comment(const string& name)
{
if(MainFormSLS->Im.LCFT)  //Thread для работы с файлом содержащим последние вызовы (Last Calls)
  {
  TLCSBuf* LCSBuf = new TLCSBuf(CLEAR_CONTACT_COMMENT);
  if(LCSBuf)
    {
    LCSBuf->s = name;
    MainFormSLS->Im.LCFT->push_lcs_buf(LCSBuf);
    }
  }
}
//------------------------------------------------------------------------------
void __fastcall TContacts::Update_DrawGrid_RowCount(TDrawGrid* DrawGrid)
{
if(!*pContact_list_size)
  DrawGrid->RowCount = 1;
else
  DrawGrid->RowCount = *pContact_list_size;
}
//------------------------------------------------------------------------------
bool __fastcall TContact::find_underlying_id(vector<int>& v, int id)
{
bool rv = false;
if(!v.empty())
  {
  vector<int>::iterator it = v.begin();
  while(it != v.end())
       {
       if((*it++) == id)
         {
         rv = true;
         break;
         }
       }
  }
return rv;
}
//------------------------------------------------------------------------------
void __fastcall TContact::delete_underlying_id(vector<int>& v,int id)
{
if(!v.empty())
  {
  vector<int>::iterator it = v.begin();
  while(it != v.end())
       {
       if(*it == id)
         {
         v.erase(it);
         break;
         }
       it++;
       }
  }
}
//------------------------------------------------------------------------------
//--- clear_name -- rezult without prefix FFFFFFFF -----------------------------------
//------------------------------------------------------------------------------
void __fastcall TContact::generate_group_name(const string& pref, string& clear_name)
{
name = GRNS.gen_group_name(pref, clear_name);
}
//------------------------------------------------------------------------------
const string __fastcall get_CONTACTS_DIR()
{
return CONTACTS_DIR;
}
//------------------------------------------------------------------------------
//--  TContact* - из TEnterpriseSubscList ---------------------------------------
//--  (vector<TContact*>& v содержит список родительских подразделений ---------
//--  полученных в ответ на запрос в TEnterpriseSubscList              ---------
//------------------------------------------------------------------------------
void __fastcall TContacts::add_contact_from_external_db_to_personal_contact_list(vector<TContact*>& v, TContact* Contact, TDrawGrid* DrawGrid)
{
::EnterCriticalSection(&contlist_cs);
  #ifdef StructuralContactsImport
  vector<TContact*>::reverse_iterator it = v.rbegin();
  while(it != v.rend())
       {
       TContact* ParentContact = *it++;
       if(ParentContact)
         {
         if(name_list.find(ParentContact->name) == name_list.end())
           {
           TContact* CONT  = new TContact(get_next_contact_id());
           CONT->CT        = ParentContact->CT;
           CONT->name      = ParentContact->name;
           CONT->full_name = ParentContact->full_name;
           CONT->DBI       = ParentContact->DBI;
           if(ParentContact->OWNER)
             {
             TContact ContactCopy;
             if(get_contact_copy_by_user_name(ContactCopy, ParentContact->OWNER->name))
               {
               CONT->OWNER = ContactCopy.pContact;
               if(!CONT->OWNER->find_underlying_id(CONT->OWNER->underlying_division_ids, CONT->get_id()))
                   CONT->OWNER->underlying_division_ids.push_back(CONT->get_id());
               if(!CONT->OWNER->find_underlying_id(CONT->OWNER->underlying_ids, CONT->get_id()))
                   CONT->OWNER->underlying_ids.push_back(CONT->get_id());
               }
             }

          _insert_contact_in_contact_list(CONT);

           if(CONT->CT == ContactType_DIVISION)
              CONT->set_open(true);

           if(!CONT->OWNER)
             (*pContact_list_size)++;
           else if(CONT->OWNER->get_open())
             (*pContact_list_size)++;
           Update_DrawGrid_RowCount(DrawGrid);
          }
         }
       }//while(it != v.rend())
  #endif
  if(Contact->name == MainFormSLS->Sip->Account.get_user_name())
    {
    MainFormSLS->Sip->Account.set_displayname(Contact->full_name);
    MainFormSLS->Sip->display_full_ser_name();
    }
  else if(name_list.find(Contact->name) == name_list.end())
    {
    TContact* CONT  = new TContact(get_next_contact_id());
    CONT->CT        = Contact->CT;
    CONT->name      = Contact->name;
    CONT->full_name = Contact->full_name;
    CONT->DBI       = Contact->DBI;
    CONT->position  = Contact->position;

    #ifdef StructuralContactsImport
    if(Contact->OWNER)
      {
      TContact ContactCopy;
      if(get_contact_copy_by_user_name(ContactCopy, Contact->OWNER->name))
        {
        CONT->OWNER = ContactCopy.pContact;
        if(CONT->CT == ContactType_CLIENT)
          {
          if(!CONT->OWNER->find_underlying_id(CONT->OWNER->underlying_ids, CONT->get_id()))
              CONT->OWNER->underlying_ids.push_back(CONT->get_id());
          }
        else if(CONT->CT == ContactType_DIVISION)
          {
          if(!CONT->OWNER->find_underlying_id(CONT->OWNER->underlying_division_ids, CONT->get_id()))
              CONT->OWNER->underlying_division_ids.push_back(CONT->get_id());
          if(!CONT->OWNER->find_underlying_id(CONT->OWNER->underlying_ids, CONT->get_id()))
              CONT->OWNER->underlying_ids.push_back(CONT->get_id());
          }
        _insert_contact_in_contact_list(CONT);
        if(CONT->CT == ContactType_CLIENT)
          {
          MainFormSLS->RS.push_contact(*CONT);
          MainFormSLS->RS.set_subscr_proc_active(true);
          }
        if(!CONT->OWNER)
          (*pContact_list_size)++;
        else if(CONT->OWNER->get_open())
          (*pContact_list_size)++;
        Update_DrawGrid_RowCount(DrawGrid);
        }
      } //if(Contact->OWNER)
    #else
    if(CONT->CT == ContactType_CLIENT)   //включать в список только клиентов (не подразделения)
      {
     _insert_contact_in_contact_list(CONT,true);
      (*pContact_list_size)++;
      Update_DrawGrid_RowCount(DrawGrid);
      #ifdef NET_STATE_DISPLAY_DEPEND_OF_COS
      if(MainFormSLS->Sip->Account.cos <= CONT->cos)   //Если мой класс сервиса ниже или равен cos добавляемого клиента, то SUBSCRIBE request посылается данному абоненту
        {
      #endif
        MainFormSLS->RS.push_contact(*CONT);
        MainFormSLS->RS.set_subscr_proc_active(true);
      #ifdef NET_STATE_DISPLAY_DEPEND_OF_COS
        }
      #endif
      }
    else
      delete CONT;
    #endif
    } //else if(name_list.find(Contact->name) == name_list.end())
::LeaveCriticalSection(&contlist_cs);
}
//------------------------------------------------------------------------------
string   __fastcall TGroupNameStruct::gen_group_name(const string& pref, string& out)
{
string s = inttohexstr(random(0x7FFFFFFF)) + "-";
TDateTime dt = dt.CurrentDateTime();
unsigned short year;
unsigned short month;
unsigned short day;
dt.DecodeDate(&year,&month,&day);
unsigned short hour;
unsigned short min;
unsigned short sec;
unsigned short msec;
string str;
dt.DecodeTime(&hour,&min,&sec,&msec);
s += inttohexstr(year) + inttohexstr(month) + inttohexstr(day) + inttohexstr(hour) + inttohexstr(min) + inttohexstr(sec) + inttohexstr(msec);
out = s;
s = pref + s;
return s;
}
//------------------------------------------------------------------------------
void __fastcall TGroupNameStruct::SET_GROUP(deque<TGroupName>& q)
{
GroupNameList = q;
}
//------------------------------------------------------------------------------
void __fastcall TGroupNameStruct::GET_GROUP(deque<TGroupName>& q)
{
q = GroupNameList;
}
//------------------------------------------------------------------------------
void __fastcall TGroupNameStruct::INS_GROUP(TGroupName& GName)
{
GroupNameList.push_back(GName);
}
//------------------------------------------------------------------------------

