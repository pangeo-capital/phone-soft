//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "WinRDefs.h"
#include "MediaChannels.h"
#include "Sip.h"
#include "g711.h"
#include <ws2tcpip.h> //for define IP_TOS
#include "usc.h"
#include "SipClient_Unit.h"
#include "Conference_Unit.h"

extern USC_Fxns USC_G7291_Fxns;
extern USC_Fxns USC_G729I_Fxns;
extern USC_Fxns USC_G729A_Fxns;
extern USC_Fxns USC_G729IFP_Fxns;


#define PCMDATA_LEN  320 //10000

#pragma package(smart_init)
const string wsp = " ";
const dtmf_start_end_transm_count = 3;

//---------------------------------------------------------------------------
void __fastcall TRecvThread::Execute()
{
try{
while(!Terminated)
     {
     SOCKET SCK = Uc->getSocket();
     if(SCK == INVALID_SOCKET)
       {
       ::Sleep(200);
         continue;
       }
     TOutPutUdpBlock* opb = new TOutPutUdpBlock(pktn);
     if(opb)
       {
       struct sockaddr_in from;
       int fromlen = sizeof(from);
       memset(&from,0,sizeof(from));
       int bread = recvfrom(SCK, rcvbuf, MFSW_MAX_PACKET, 0, (struct sockaddr*)&from, &fromlen);
       if(!opb)
         {
         lasterr = " Error: opb = NULL";
         sendlasterr();
         continue;
         }
       if(thread_block)
         {
         delete opb;
         continue;
         }

       if(bread == SOCKET_ERROR)
         {
         if(Terminated)
           {
           delete opb;
           return;
           }
         PROC_SOCKET_ERROR();
         delete opb;
         continue;
         }      

       char* pAddr = inet_ntoa(from.sin_addr);
       if(pAddr)
          opb->FromIP = string(pAddr);
       opb->FromPort = htons(from.sin_port);
       opb->v.resize(bread);
       if(opb->v.size() < (unsigned)bread)
         {
         lasterr = " Allocated buf < bread";
         sendlasterr();
         delete opb;
         continue;
         }
       memcpy(&opb->v[0],rcvbuf,bread);
       opb->getDateTime();
       #ifdef RTP_LogSendPacket
       LOG_RecvdPacket(opb,bread);
       #endif
       if(Uc->delayToTransmitPacketCount)
         {
         Uc->delayToTransmitPacketCount = 0;
         FirstPacketReceived = true;
         LOG_InitialPacketReceived(opb,0);
         }
       else
         {
         if(!FirstPacketReceived)
           {
           FirstPacketReceived = true;
           LOG_InitialPacketReceived(opb,1);
           }
         }
       if(!RemotePortAssigned)
        {
        if(Uc->sendThread)
          {
          if(Uc->sendThread->getRemotePort() != opb->FromPort)
            {
            TEventLogThread* elt = getLog();
            if(elt)
              {
              string s = "\nSUSPICIOUS MEDIA SOURCE: Received remote port " + inttostr(opb->FromPort) + " != Remote Port got from Sdp " + inttostr(Uc->sendThread->getRemotePort()) + "\n";
              elt->FputEvt(s);
              }
            }
          if(Uc->sendThread->getRemoteAddr() != opb->FromIP)
            {
            TEventLogThread* elt = getLog();
            if(elt)
              {
              string s = "\nSUSPICIOUS MEDIA SOURCE: Received remote host " + opb->FromIP + " != Remote Hoat got from Sdp " + Uc->sendThread->getRemoteAddr() + "\n";
              elt->FputEvt(s);
              }
            }
          Uc->sendThread->setRemoteAddress(opb->FromIP,opb->FromPort); //(  этому времени RemotePort and ReoteHost Already assigned, но если NAT на RtpServ назначит внешний порт != внутреннему то setRemoteAddress() может спасти ситуацию, назначив правильный Remote Port
          RemotePortAssigned = true;
          }
        }

       #ifdef SIP_Video
       #ifdef Client_Test_Block
       if(Uc->test_block.local_video_rtp_loop)
         {
         if(Uc->getMpt() == RTP_VIDEO_MPT)
           {
           delete opb;
           continue;
           }
         }
       #endif
       #endif

         if(Uc->chDispThread)
             Uc->chDispThread->pushToSend(opb);
         else
            delete opb;
       }
     }
 }//try
catch(Exception& e){exsSstEXCEPTION(*eltp,"__TRecvThread::Execute",e);}
}
//------------------------------------------------------------------------------
void __fastcall TRecvThread::PROC_SOCKET_ERROR()
{
SOCKET SCK = Uc->getSocket();
int err = WSAGetLastError();
lasterr = "TRecvThread::Execute(): ch_"  + inttostr(Uc->getChId()) +  " bread == SOCKET_ERROR\n" +
          "sck = " + inttostr(SCK) + " LocalPort: " + inttostr(Uc->localport);
           if(Uc->sendThread)
              lasterr += " RemoteAddr: " + Uc->sendThread->getRemoteAddr() + ":" + inttostr(Uc->sendThread->getRemotePort());
GetLastSocketError(lasterr,err);
sendlasterr();
switch(err){
      case WSAECONNRESET:{
           WSAECONNRESET_PROC(SCK);
           break;
      case WSAENOTSOCK: //This event can rise when TRecvThread terminate proc started  and setsocket(INVALID_SOCKET) (see ~TUdpChannel()) but Terminate not yet true  
           ::Sleep(500);
           break;
           } // case WSAECONNRESET:{
      }    //switch(err)
}
//------------------------------------------------------------------------------
void __fastcall TRecvThread::WSAECONNRESET_PROC(SOCKET SCK)
{
::closesocket(SCK);
Uc->setSocket(INVALID_SOCKET);
if(Uc->get_re_create_sck_count())
  {
   if(Uc->localport != -1)
     {
     ::Sleep(500);  //::Sleep(1000);
     string TimeStr;
     TDateTime DateTime = DateTime.CurrentDateTime();
     exsTime(DateTime,TimeStr);
     lasterr = "\n\n" + TimeStr + WS + "ch_" + inttostr(Uc->getChId()) + " Try to re_create SOCKET with same localport: " + inttostr(Uc->localport);
     SOCKET sck = exsCreateUDPSocket_ADDR_ANY(Uc->localport);
     if(sck != INVALID_SOCKET)
       {
       Uc->setSocket(sck);
       lasterr += "\n" + (string)"SOCKET " + inttostr(sck) + WS + "with local port" + WS + inttostr(Uc->localport) + WS + "successfuly created\n";
       if(Uc->sendThread)
         {
         lasterr += "Prepare Initial ";
         switch(Uc->getMpt()){
                  case RTP_AUDIO_MPT:{
                       lasterr += "RTP AUDIO";
                       TOutPutUdpBlock* n_opb = new TOutPutUdpBlock;
                       if(n_opb)
                         {
                         n_opb->mpt = INIT_MPT; //must be deleted after use in the TSendThread
                         int sz = sdpboundary.length();
                         for(int i = 0;i < sz; i++)
                             n_opb->v.push_back(sdpboundary[i]);
                         Uc->sendThread->setQueue(n_opb);
                         }
                       break;
                       }
                  case RTCP_AUDIO_MPT:{
                       lasterr += "RTCP AUDIO";
                       TOutPutUdpBlock* n_opb = new TOutPutUdpBlock;
                       if(n_opb)
                         {
                         n_opb->mpt = INIT_RTCP_MPT; //must be deleted after use in the TSendThread
                         int sz   = crlf.length();
                         for(int i = 0;i < sz; i++)
                             n_opb->v.push_back(crlf[i]);
                         Uc->sendThread->setQueue(n_opb);
                         }
                       break;
                       }
                  case RTP_VIDEO_MPT:{
                       lasterr += "RTP VIDEO";
                       TOutPutUdpBlock* n_opb = new TOutPutUdpBlock;
                       if(n_opb)
                         {
                         n_opb->mpt = INIT_MPT; //must be deleted after use in the TSendThread
                         int sz = sdpboundary.length();
                         for(int i = 0;i < sz; i++)
                             n_opb->v.push_back(sdpboundary[i]);
                         Uc->sendThread->setQueue(n_opb);
                         }
                       break;
                       }
                  case RTCP_VIDEO_MPT:{
                       lasterr += "RTCP VIDEO";
                       TOutPutUdpBlock* n_opb = new TOutPutUdpBlock;
                       if(n_opb)
                         {
                         n_opb->mpt = INIT_RTCP_MPT; //must be deleted after use in the TSendThread
                         int sz   = crlf.length();
                         for(int i = 0;i < sz; i++)
                             n_opb->v.push_back(crlf[i]);
                         Uc->sendThread->setQueue(n_opb);
                         }
                       break;
                       }
                  }
          lasterr += " Seq to RemoteAddr: " + Uc->sendThread->getRemoteAddr() + ":" + inttostr(Uc->sendThread->getRemotePort()) + "\n";
          } //if(Uc->sendThread)
       }
     else
       lasterr += ". FAILED!\n";
     sendlasterr();
     } //if(Uc->localport != -1)
  } //if(Uc->get_assign_sck_count())
else
  {
  if(Uc->sendThread)
    if(Uc->sendThread->getRemotePort() != -1)
       Uc->sendThread->setRemoteAddress("0.0.0.0",-1);
  ::Sleep(100);
  }
}
//------------------------------------------------------------------------------
void __fastcall TUdpChannel::_log_uc(const string& s_in)
{
TEventLogThread* elt = *eltp;
if(!elt)return;
string timestr;
TDateTime dt = dt.CurrentTime();
exsTime( dt,timestr);
string ch_id = inttostr(chID);
string s = "\n" + timestr + " ch_" + ch_id;
getMediaPacketType(s);
s += WS + s_in;
elt->FputEvt(s);
}
//------------------------------------------------------------------------------
void  __fastcall TUdpChannel::printStartDeleteChannel()
{
TEventLogThread* elt = getLogThread();
if(!elt)return;
string timestr;
TDateTime dt = dt.CurrentTime();
exsTime( dt,timestr);
string ch_id = inttostr(chID);
string s = "\n" + timestr + " ch_" + ch_id;
getMediaPacketType(s);
s += " start to delete";
elt->FputEvt(s);
}
//-----------------------------------------------------------------------------
void  __fastcall TUdpChannel::printChannelDeleted()
{
TEventLogThread* elt = getLogThread();
if(!elt)return;
string timestr;
TDateTime dt = dt.CurrentTime();
exsTime( dt,timestr);
string ch_id = inttostr(chID);
string s = "\n" + timestr + " ch_" + ch_id;
getMediaPacketType(s);
s += " deleted";
if(mpt == SOUND_MPT)
  {
  s += "\nch_" + ch_id + " Rtp packets rcvd "       + uint_to_str(rtp_packet_rcvd) +
       "\nch_" + ch_id + " Rtp packets lost "       + uint_to_str(rtp_packet_lost) +
       "\nch_" + ch_id + " Rtp packets discarded "  + uint_to_str(rtp_packet_discarded) +
       "\nch_" + ch_id + " Rtp packets duplicated " + uint_to_str(rtp_packet_duplicated);
  }
elt->FputEvt(s);
}
//------------------------------------------------------------------------------
void  __fastcall TUdpChannel::printCryptoError(int Err,int Type)
{
TEventLogThread* elt = getLogThread();
if(!elt)return;
string err = string(rsrtp_error_text(Err));
string timestr;
TDateTime dt = dt.CurrentTime();
exsTime( dt,timestr);
string ch_id = inttostr(chID);
string s = "\n" + timestr + " ch_" + ch_id;
getMediaPacketType(s);
switch(Type){
      case 0: s += ": DECRYPTION_ERROR: " + err;        break;
      case 1: s += ": ENCRYPTION_ERROR: " + err;        break;
      case 2: s += ": ERROR LOG THRESHOLD IS REACHED!"; break;
      }
elt->FputEvt(s);
}
//------------------------------------------------------------------------------
TEventLogThread* __fastcall TUdpChannel::getLogThread()
{
TEventLogThread* elt = *eltp;
if(!elt)return NULL;
if(!elt->getlog())return NULL;
return elt;
}
//------------------------------------------------------------------------------
void __fastcall TUdpChannel::getMediaPacketType(string& s)
{
switch(mpt){
       case SOUND_MPT:
            s+=" SOUND";break;
       #ifdef SIP_Video
       case VIDEO_MPT:
            s+=" VIDEO";break;
       case RTP_VIDEO_MPT:
            s+=" RTP_VIDEO";break;
       case RTCP_VIDEO_MPT:
            s+=" RTCP_VIDEO";break;
       #endif
       case RTP_AUDIO_MPT:
            s+=" RTP_AUDIO";break;
       case RTCP_AUDIO_MPT:
            s+=" RTCP_AUDIO";break;
       }
}
//-----------------------------------------------------------------------------
void __fastcall TUdpChannelStruct::Execute()
{
try{
while(!Terminated){
     int a = getReqToDel();
     if(!a)
       {
       FFlash();
       Suspend_Thread();
       continue;
       }
     Remove(a);
     }
 }//try
catch(Exception& e){exsSstEXCEPTION(*eltp,"__TUdpChannelStruct::Execute",e);}
}
//------------------------------------------------------------------------------
void __fastcall TUdpChannelStruct::FFlash()
{
TEventLogThread* elt = getLog();
if(elt)elt->FputEvt("\n",1);
}
//------------------------------------------------------------------------------
int __fastcall TUdpChannel::CreateUdpSocket()
{
#ifdef RTP_exsCreateUDPSocket_ADDR_ANY
sck = exsCreateUDPSocket_ADDR_PORT_ANY();
if((mpt == RTP_AUDIO_MPT) || (mpt == RTP_VIDEO_MPT))
   _try_to_get_EVEN_port();
#else
sck = exsCreateUDPSocket(localhost,localport);
#endif
if(sck == INVALID_SOCKET)
  {
  TEventLogThread* elt = getLogThread();
  if(elt)
    {
    int err = WSAGetLastError();
    lasterr = "CreateUdpSocket()";
    GetLastSocketError(lasterr,err);
    lasterr+= " host " + localhost + " port " + inttostr(localport);
    sendlasterr();
    }
  return 1;
  }
return 0;
}
//----------------------------------------------------------------------------
void __fastcall TUdpChannel::_try_to_get_EVEN_port()
{
unsigned port = getLocalSocketParameters(false);
if((port & 1) == 1) //Selected EVEN port!  Stop searching.
  {
  string s;
  for(int i=0; i < 10; i++)
     {
     TEventLogThread* elt = getLogThread();
     if(elt)
       {
       s  = "\nAllocated Port: " + inttostr(port) + "." + " Try to get EVEN port";
       s += "\nclosesocket " + inttostr(sck);
       elt->FputEvt(s);
       }
     closesocket(sck);
     sck = INVALID_SOCKET;
     sck = exsCreateUDPSocket_ADDR_PORT_ANY();
     port = getLocalSocketParameters(false);
     if((port & 1) == 0) //Selected EVEN port!  Stop searching.
        break;
    }
  }
}
//----------------------------------------------------------------------------
void __fastcall TSip::getLocalMediaPort(TUdpChannel* uc)
{
#ifdef RTP_exsCreateUDPSocket_ADDR_ANY
uc->CreateUdpSocket();
#else
if(!vmpb.fport)
  {
  uc->CreateUdpSocket();
  return;
  }
int port = vmpb.lbp + vmpb.step;
if(port >= vmpb.eport)
   port = vmpb.fport;
for(int i=0; i<2048; i++)
   {
   if(vmpb.isPortFree(port))
     {
     vmpb.lbp = port;
     uc->localport = vmpb.lbp;
     if(!uc->CreateUdpSocket())
       {
       vmpb.insertPort(vmpb.lbp);
       return;
       }
     }
   port += vmpb.step;
   if(port >= vmpb.eport)
      port  = vmpb.fport;
   }
#endif
}
//----------------------------------------------------------------------------
void  __fastcall TSip::getLocalMedia(TUdpChannel* uc)
{
TIPAddress* addr = NULL;
if(!isStunAssigned())
   addr = &MappedAddress;
else
   addr = getLastNIC();
if(addr)
  uc->localhost = addr->IPAddr;
getLocalMediaPort(uc);
}
//-----------------------------------------------------------------------------
void __fastcall TUdpChannel::sendlasterr(int type)
{
TEventLogThread* elt = getLogThread();
if(!elt)return;
elt->FputEvt(lasterr,type);
}
//----------------------------------------------------------------------------
bool __fastcall TUdpChannel::SetSockOpt(int OPTS,char Value)
{
char value = Value;
if(::setsockopt(sck,IPPROTO_IP,OPTS,&value,sizeof(value))== SOCKET_ERROR)
  {
  TEventLogThread* elt = getLogThread();
  if(elt)
    {
    int err = WSAGetLastError();
    lasterr = "setsockopt()";
    GetLastSocketError(lasterr,err);
    lasterr+= " host " + localhost + " port " + inttostr(localport);
    sendlasterr();
    }
  return false;
  }
return true;
}
//------------------------------------------------------------------------------
void __fastcall TUdpChannel::CreateNetworkThreads(unsigned remotehost, unsigned remoteport, TSip* SIP)
{
string RemoteHost = inttostr((remotehost >> 24) & 0xFF) + ".";
RemoteHost += inttostr((remotehost >> 16) & 0xFF) + ".";
RemoteHost += inttostr((remotehost >> 8) & 0xFF)  + ".";
RemoteHost += inttostr(remotehost & 0xFF);
recvThread   = new TRecvThread(true,this,eltp);
chDispThread = new TChannelDispThread(true,this,eltp);
sendThread   = new TSendThread(true,this,RemoteHost,remoteport,SIP,eltp);
if(recvThread)
   recvThread->Resume();  //Do not use Resume_Thread() !!!
if(mpt == RTP_VIDEO_MPT)
  if(sendThread)
     sendThread->Resume();
}
//------------------------------------------------------------------------------
void __fastcall TUdpChannelStruct::Create_RTP_SoundTestCh(TUdpChannel** uc_rtpp)
{
TUdpChannel* uc_rtp =  new TUdpChannel(SOUND_MPT,eltp);
if(uc_rtp)
  {
  *uc_rtpp = uc_rtp;
  uc_rtp->wopt = new TWaveOutputThread(true,eltp,Sip,uc_rtp);
  if(uc_rtp->wopt)
     uc_rtp->wopt->Priority = tpHigher;
  }
}
//------------------------------------------------------------------------------
void __fastcall TUdpChannelStruct::Create_RTP_PairCh(MediaPacketType MPT,TUdpChannel** uc_rtpp,TUdpChannel** uc_rtcpp,
                                                     void* LT,unsigned val_1,unsigned val_2,
                                                     BaseExchangeBlock* ospb)
{
TLegTrn* Lt = (TLegTrn*)LT;
char tosvalue = 0xb8;
TUdpChannel* uc_rtp =  new TUdpChannel(MPT,eltp);
if(uc_rtp)
  {
 *uc_rtpp = uc_rtp;
  uc_rtp->setCallID(ospb->CallID);
  Insert(uc_rtp);
  if(MPT == SOUND_MPT)
    {
    if(Lt->legtype == Lt_Out)
      uc_rtp->setInOutCallID(out_pref + ospb->CallID);
    else if(Lt->legtype == Lt_In)
      uc_rtp->setInOutCallID(in_pref + ospb->CallID);
    Lt->ch_sound = uc_rtp->getChId();
    if(val_1 == 1)                                                 //val_1 == 1 - Microphone - yes (local speaker -> out)
      {
      uc_rtp->mic  = new TWaveInputThread(true,eltp,Sip,uc_rtp);
      if(uc_rtp->mic)
        {
        uc_rtp->mic->save_sls(ospb->getsls());
        uc_rtp->mic->save_callid(ospb->CallID);
        uc_rtp->mic->ch_conference_participant = ospb->conference_participant;
        uc_rtp->mic->Resume();   //!!!
        }
      }
    if(val_2 == 1)
      {                                              //val_2 == 1 - PlayBack yes (can hear remote speakers in headphones)
      uc_rtp->wopt = new TWaveOutputThread(true,eltp,Sip,uc_rtp);
      if(uc_rtp->wopt)
        {
        uc_rtp->wopt->Priority = tpHighest; //tpNormal;//tpHighest; //tpHigher; //
        uc_rtp->wopt->Resume();   //!!!
        }
      }
    return;
    }
  #ifdef  SIP_Video
  if(MPT == VIDEO_MPT)
    {
    if(Lt->legtype == Lt_Out)
      uc_rtp->setInOutCallID(out_pref + ospb->CallID);
    else if(Lt->legtype == Lt_In)
      uc_rtp->setInOutCallID(in_pref + ospb->CallID);
    Lt->ch_video = uc_rtp->getChId();
   /* if(val_1 == 1)                                                 //val_1 == 1 - VCam - yes (local video -> out)
      uc_rtp->vcam = new TVideoInputThread(true,eltp,Sip,uc_rtp);    */
    if(val_2 == 1)
      {
      //val_2 == 1 - VScreen - yes (remote video)
      uc_rtp->vscr = new TVideoOutputThread(true,eltp,Sip,uc_rtp);
      if(uc_rtp->vscr)
         uc_rtp->vscr->Priority = tpHigher;
      }
    return;
    }
  #endif
  Sip->getLocalMedia(uc_rtp);         //with CreateUdpSocket() in getLocalMediaPort()  !!!
  if(uc_rtp->getSocket()!= INVALID_SOCKET)
    {
    #ifdef  SIP_Video
    if(MPT == RTP_VIDEO_MPT)
      {
      Lt->ch_rtp_video = uc_rtp->getChId();
      if(val_2!=-1)
         uc_rtp->CreateNetworkThreads(val_1,val_2,Sip);  //val_1 - RemoteHost, val_2 - RemotePort
      else
         uc_rtp->CreateNetworkThreads(-1,-1,Sip);
      #ifdef Client_Test_Block
      uc_rtp->test_block = Sip->TestBlock;
      #endif
      if(uc_rtp->sendThread)
       if(ospb->vcpar)
         {
         uc_rtp->sendThread->vencpar.vcp.width      = ospb->vcpar->width;
         uc_rtp->sendThread->vencpar.vcp.height     = ospb->vcpar->height;
         uc_rtp->sendThread->vencpar.vcp.frame_size = vencdec_get_yuv420p_buff_size( ospb->vcpar->width, ospb->vcpar->height);
         uc_rtp->sendThread->vencpar.vcp.fps        = ospb->vcpar->fps;
         }
      if(!uc_rtp->rtcp_s)
        uc_rtp->rtcp_s = new TClass_pjmedia_rtcp_session;
      }
    else
    #endif
      {
      Lt->ch_rtp_audio = uc_rtp->getChId();
      if(uc_rtp->SetSockOpt(IP_TOS,tosvalue))
        {
        if(val_2!=-1)
          uc_rtp->CreateNetworkThreads(val_1,val_2,Sip); //val_1 - RemoteHost, val_2 - RemotePort
        else
          uc_rtp->CreateNetworkThreads(-1,-1,Sip);
        }
      }
    uc_rtp->getLocalSocketParameters(true);
    if(!uc_rtp->rtcp_s)
        uc_rtp->rtcp_s = new TClass_pjmedia_rtcp_session;
    } //if(uc_rtp->getSocket()!= INVALID_SOCKET)
  } //if(uc_rtp)

TUdpChannel* uc_rtcp = NULL;
#ifdef  SIP_Video
if(MPT == RTP_VIDEO_MPT)
  {
  uc_rtcp = new TUdpChannel(RTCP_VIDEO_MPT,eltp);
  if(uc_rtcp)
    {
   *uc_rtcpp = uc_rtcp;
    Insert(uc_rtcp);
    Lt->ch_rtcp_video = uc_rtcp->getChId();
    }
  }
else
#endif
  {
  uc_rtcp = new TUdpChannel(RTCP_AUDIO_MPT,eltp);
  if(uc_rtcp)
    {
   *uc_rtcpp = uc_rtcp;
    Insert(uc_rtcp);
    Lt->ch_rtcp_audio = uc_rtcp->getChId();
    }
  }
if(uc_rtcp)
  {
  uc_rtcp->localhost = uc_rtp->localhost;
  uc_rtcp->localport = uc_rtp->localport + 1;
  uc_rtcp->CreateUdpSocket();
  if(uc_rtcp->getSocket()!= INVALID_SOCKET)
    {
    if(uc_rtcp->SetSockOpt(IP_TOS,tosvalue))
      {
      if(val_2!=-1)
        uc_rtcp->CreateNetworkThreads(val_1,val_2+1,Sip); //val_1 - RemoteHost, val_2 - RemotePort
      else
        uc_rtcp->CreateNetworkThreads(-1,-1,Sip);
      }
    uc_rtcp->setCallID(ospb->CallID);

    if(Lt->legtype == Lt_Out)
       uc_rtcp->setInOutCallID(out_pref + ospb->CallID);
    else if(Lt->legtype == Lt_In)
       uc_rtcp->setInOutCallID(in_pref + ospb->CallID);

    uc_rtcp->getLocalSocketParameters(true);
    if(!uc_rtcp->rtcp_s)
      if(uc_rtp->rtcp_s)
        {
        uc_rtcp->rtcp_s = uc_rtp->rtcp_s;
        uc_rtp->rtcp_s->INC_REFERENCE_COUNT();
        }
    }
  }
}
//------------------------------------------------------------------------------
void __fastcall TRecvThread::sendlasterr()
{
TEventLogThread* elt = *eltp;
if(!elt)return;
if(!elt->getlog())return;
elt->FputEvt(lasterr);
}
//----------------------------------------------------------------------------
void __fastcall TRecvThread::LOG_RecvdPacket(TOutPutUdpBlock* opb,int bread)
{
TEventLogThread* elt = getLog();
if(elt)
  {
  string str;
  exsTime(opb->dt, str);
  string s_sck = inttostr(Uc->getSocket());
  str = "\n" + str + " sck " + s_sck + " ch_" + inttostr(Uc->getChId());
  Uc->getMediaPacketType(str);
  str += " Pckt# " + inttostr(opb->pktn) + " Len " + inttostr(bread) + " ";
  TDateTime difftime = opb->dt - PrevPacketTime;
  PrevPacketTime = opb->dt;
  unsigned short hour;
  unsigned short min;
  unsigned short sec;
  unsigned short msec;
  difftime.DecodeTime(&hour,&min,&sec,&msec);
  str += "dt=" + inttostr(hour) + "." + inttostr(min) + "." + inttostr(sec) + "." + inttostr(msec) + " RcvFrom "
         + opb->FromIP + ":" + inttostr(opb->FromPort) + "\n";
  for(int i=0;i<bread;i++)
     str += " " + inttohexstr(opb->v[i],2);
  str+="\n";
  elt->FputEvt(str);
 }
}
//------------------------------------------------------------------------------
TEventLogThread* __fastcall TRecvThread::getLog()
{
TEventLogThread* elt = *eltp;
if(elt)
 if(elt->getlog())
    return elt;
return NULL;
}
//----------------------------------------------------------------------------
void __fastcall TRecvThread::LOG_InitialPacketReceived(TOutPutUdpBlock* opb,int type)
{
TEventLogThread* elt = getLog();
if(elt)
  {
  TDateTime DateTime = DateTime.CurrentDateTime();
  string str;
  exsTime(DateTime,str);
  string s_sck = inttostr(Uc->getSocket());
  str = "\n" + str + " sck " + s_sck + " ch_" + inttostr(Uc->getChId());
  Uc->getMediaPacketType(str);
  if(!type)
     str+= " Initial ";
  else
     str+= " First Media ";
  str += "Packet Received From " + opb->FromIP + ":" + inttostr(opb->FromPort) + (string)"\n";
  elt->FputEvt(str);
  }
}
//----------------------------------------------------------------------------
void __fastcall TSendThread::LOG_InitialPacketSent(TOutPutUdpBlock* opb)
{
TEventLogThread* elt = getLog();
if(elt)
  {
  TDateTime DateTime = DateTime.CurrentDateTime();
  string str;
  exsTime(DateTime,str);
  str = "\n" + str + " sck " + inttostr(Uc->getSocket()) + " ch_" + inttostr(Uc->getChId());
  Uc->getMediaPacketType(str);
  if(opb->mpt == INIT_MPT)
     str += " INIT Packet Sent To ";
  else
     str += " First Media Packet Sent To ";
  str += getRemoteAddr() + ":" + inttostr(RemotePort) + "\n";
  elt->FputEvt(str);
  }
}
//----------------------------------------------------------------------------
/*
void __fastcall TSipUacThread::Log_PrepareInitialRtpSeq(TUdpChannel* uc)
{
TEventLogThread* elt = getLog();
if(elt)
  {
  TDateTime DateTime = DateTime.CurrentDateTime();
  string str;
  exsTime(DateTime,str);
  str = "\n" + str + " sck " + " ch_" + inttostr(uc->getChId());
  uc->getMediaPacketType(str);
  str += " Prepare Initial Rtp Seq To Remote Addr\n";
  elt->FputEvt(str);
  }
}
*/
//-----------------------------------------------------------------------------
void __fastcall TChannelDispThread::Execute()
{
try{
while(!Terminated)
     {
     TOutPutUdpBlock* opb = getToSend();
     if(opb == NULL)
       {
       if(Uc->getMpt() == RTP_AUDIO_MPT)
         {
         Uc->checkWoptQueue();
         ::Sleep(1);
         continue;
         }
       else
         {
         Suspend_Thread();
         continue;
         }
       }
     if(!thread_block)
       {
       if(Uc->getMpt() == RTCP_AUDIO_MPT)
          Uc->proc_RTCP_PCKT(opb);
       else
          Uc->pushBufToSend(opb);
       }
     updateSentQueue(opb);
     }
}//try
catch(Exception& e){exsSstEXCEPTION(*eltp,"__TChannelDispThread::Execute",e);}
}
//------------------------------------------------------------------------------
void __fastcall TChannelDispThread::updateSentQueue(TOutPutUdpBlock* opb)
{
if(opb)
   sent.push_back(opb);
if((++checkCount & 0xFF) == 0xFF)
   checkSent();
else
   getSent();
}
//------------------------------------------------------------------------------
void __fastcall TChannelDispThread::pushToSend(TOutPutUdpBlock* opb)
{
::EnterCriticalSection(&cs_tosend);
  tosend.push(opb);
  if(Suspended)
     Resume_Thread();
::LeaveCriticalSection(&cs_tosend);
}
//------------------------------------------------------------------------------
TOutPutUdpBlock* __fastcall TChannelDispThread::getToSend()
{
TOutPutUdpBlock* opb = NULL;
::EnterCriticalSection(&cs_tosend);
if(!tosend.empty())
  {
  opb = tosend.front();
  tosend.pop();
  }
::LeaveCriticalSection(&cs_tosend);
return opb;
}
//------------------------------------------------------------------------------
int __fastcall TChannelDispThread::getSizeToSend()
{
int rv;
::EnterCriticalSection(&cs_tosend);
  rv = tosend.size();
::LeaveCriticalSection(&cs_tosend);
return rv;
}
//------------------------------------------------------------------------------
void __fastcall TUdpChannel::pushBufToConf(TOutPutUdpBlock* opb)
{
try{
//lasterr = "\n::E_CS(&mycnts) chID " + inttostr(chID);
//sendlasterr();

::EnterCriticalSection(&mycnts);
deque<TUdpChannel*>::iterator it = myCtns.begin();
while(it!=myCtns.end())
     {
     TUdpChannel* cntd_uc = (*it++);
     if(cntd_uc)
       {
       if(mpt == SOUND_MPT)
         if(cntd_uc->mpt == SOUND_MPT)   //MPT of connected channel
           {
           if(cntd_uc->mic)
             {
             int rez = cntd_uc->mic->acqs.add_audio_packet(chID,opb->v);
             if(rez)
               {
               string timestr;
               TDateTime dt = dt.CurrentTime();
               exsTime( dt,timestr);
               lasterr = "\n" + timestr + " conf queue_size > JBD_Max = " + inttostr(rez)+  " RESET audio packet";
               sendlasterr(1);
               }
             }
           }
       }
     }
::LeaveCriticalSection(&mycnts);

//lasterr = "\n::L_CS(&mycnts) chID " + inttostr(chID);
//sendlasterr();

 }//try
catch(Exception& e){exsSstEXCEPTION(*eltp,"__TUdpChannel::pushBufToConf(TOutPutUdpBlock* opb)",e);}

}
//------------------------------------------------------------------------------
void __fastcall TUdpChannel::decompress_sound_packet(TUdpChannel* cntd_uc,TOutPutUdpBlock* opb)
{
if(cntd_uc->wopt)
  if(cntd_uc->wopt->GET_WAVE_FORMAT_TAG() == WAVE_FORMAT_PCM)
    {
    int size = opb->v.size();
    if(size > 12)
      {
      int pdt      = get_payload_type(opb->v[1]);
      if(opb->v[1] & 0x80)
         opb->mark = true;
      opb->seq_num = get_seq_number(opb->v[2],opb->v[3]);
      memcpy(&opb->v[0],&opb->v[12],size-12);
      opb->v.resize(size-12);
      vector<UBYTE> v;
      switch(pdt){
        case  0:
        case  8: G711_To_Linear(v,opb->v,pdt);
                 opb->v = v;
                 SoundPacketToDouble(opb);
                 opb->decompressed = true;
                 break;
        case 18: if(G729DEC)
                   {
                   G729DEC->G729_To_Linear(opb);
                   SoundPacketToDouble(opb);
                   opb->decompressed = true;
                   }
                 break;
        default: break;
        }
      }
    }
}
//------------------------------------------------------------------------------
void __fastcall TUdpChannel::SoundPacketToDouble(TOutPutUdpBlock* opb)
{
if(TTest_Sound->ChDispToDouble->Checked)
  {
  if(!opb->vd.empty())
      opb->vd.clear();
  sound_packet_to_double(opb);
  }
}
//------------------------------------------------------------------------------
void __fastcall TUdpChannel::sound_packet_to_double(TOutPutUdpBlock* opb)
{
vector<short> x;
int sz = opb->v.size();
ubyte_2_short(x,opb->v,sz);
short_2_double(opb->vd,x);
opb->abs_max = abs_max_value(opb->vd);
}
//------------------------------------------------------------------------------
void __fastcall TUdpChannel::sound_jbd_min_proc(int wopt_queue_sz,TUdpChannel* cntd_uc,TOutPutUdpBlock* opb)
{
if(rtp_audio_packet_count > 100)  // 200
  {
  if(wopt_queue_sz < 1)
    TTest_Sound->JBD_Min->Checked = true;
  if(TTest_Sound->JBD_Min->Checked)
    {
    if(wopt_queue_sz < 2)
      {
      TOutPutUdpBlock* dupl_opb = new TOutPutUdpBlock;
      dupl_opb->duplicated   = true;
      dupl_opb->decompressed = opb->decompressed;
      dupl_opb->v            = opb->v;
      cntd_uc->wopt->setQueue(dupl_opb);
      }
    else
      TTest_Sound->JBD_Min->Checked = false;
    }
  }
}
//------------------------------------------------------------------------------
/*
void __fastcall TUdpChannel::sound_jbd_min_proc_1(int wopt_queue_sz,TUdpChannel* cntd_uc,TOutPutUdpBlock* opb)
{
if(wopt_queue_sz < 1)
  TTest_Sound->JBD_Min->Checked = true;
if(TTest_Sound->JBD_Min->Checked)
  {
  if(wopt_queue_sz < 2)
    {
    TOutPutUdpBlock* dupl_opb = new TOutPutUdpBlock;
    dupl_opb->duplicated = true;
    vector<UBYTE> vv = opb->v;
    for(int i=0;i<12;i++)
       dupl_opb->v.push_back(vv[i]);
    for(int i=12;i<92;i++)
       {
       dupl_opb->v.push_back(vv[i]);
       dupl_opb->v.push_back(vv[i]);
       }
    opb->v.resize(12);
    for(int i=92;i<172;i++)
       {
       opb->v.push_back(vv[i]);
       opb->v.push_back(vv[i]);
       }
    cntd_uc->wopt->setQueue(dupl_opb);
    }
  else
    TTest_Sound->JBD_Min->Checked = false;
  }
}
*/
//------------------------------------------------------------------------------
bool __fastcall TSendThread::ENCRYPT(TOutPutUdpBlock* opb)
{
if(SRTP)
  {
   unsigned sz = opb->v.size();
   opb->v.resize(sz + 10);
   int err = rsrtp_protect(SRTP->ses, &opb->v[0], &sz);
   if(err)
     {
     SRTP->printEncryptionError(Uc,err);
     return false;
     }
  }
return true;
}
//------------------------------------------------------------------------------
bool __fastcall TUdpChannel::DECRYPT(TOutPutUdpBlock* opb)
{
if(chDispThread)
  {
  TSRTPCrypto* src = chDispThread->getSRTP();
  if(src)
    {
    unsigned sz = opb->v.size();
    int err = rsrtp_unprotect(src->ses, &opb->v[0], &sz);
    if(err)
      {
      src->printDecryptionError(this,err);
      return false; //!!!
      }
    opb->v.resize(sz);
    }
  }
return true;
}
//------------------------------------------------------------------------------
//------------- Sets empty buf, чтобы работала передача пакетов, когда на приеме
//------------- пакеты отсутствуют ---------------------------------------------
//------------------------------------------------------------------------------
void __fastcall TUdpChannel::checkWoptQueue()
{
::EnterCriticalSection(&mycnts);
deque<TUdpChannel*>::iterator it = myCtns.begin();
while(it != myCtns.end())
     {
     TUdpChannel* cntd_uc = (*it++);
     if(cntd_uc)
       {
       if(cntd_uc->mpt == SOUND_MPT)
         {
         if(cntd_uc->wopt->QueueEmpty())
           {
           for(int i = 0; i < 3; i++)
              {
              TOutPutUdpBlock* opb = new TOutPutUdpBlock;
              opb->v.resize(320,0);
              opb->decompressed = true;
              opb->queue_filler = true;
              cntd_uc->wopt->setQueue(opb);
              }
           }
         }
       }
     }
::LeaveCriticalSection(&mycnts);
}
//------------------------------------------------------------------------------
void __fastcall TUdpChannel::pushBufToSend(TOutPutUdpBlock* opb)
{
::EnterCriticalSection(&mycnts);
deque<TUdpChannel*>::iterator it = myCtns.begin();
while(it != myCtns.end())
     {
     TUdpChannel* cntd_uc = (*it++);
     if(cntd_uc)
       {
       if(mpt == RTP_AUDIO_MPT)   //MPT of recived channel
         {
         rtp_audio_packet_count++;
         if(cntd_uc->mpt == SOUND_MPT)   //MPT of connected channel
           {
           if(cntd_uc->wopt)
             if(cntd_uc->wopt->WOS == WaveOutputState_RECEIVING_VOICE)
               {
               int wopt_queue_sz = cntd_uc->wopt->getQueueSize();
               if(cntd_uc->wopt->ReportTime < cntd_uc->wopt->ReportTime.CurrentDateTime())
                 {
                 lasterr = "\nwopt ch_" + inttostr(cntd_uc->getChId());
                 cntd_uc->getMediaPacketType(lasterr);
                 int whdr_size  = cntd_uc->wopt->get_whdr_size();
                 int done_count = cntd_uc->wopt->get_whdr_done_count();
                 lasterr += " whdr_queue " + inttostr(whdr_size) + " done " + inttostr(done_count) + " wopt_queue " + inttostr(wopt_queue_sz);
                 if(chDispThread)
                   {
                   int size_to_send = chDispThread->getSizeToSend();
                   lasterr += " ch_disp_queue " + inttostr(size_to_send);
                   }
                 sendlasterr(1);
                 cntd_uc->wopt->ReportTime += TDateTime(0,0,audio_report_interval,0); //10 sec
                 }
               bool decrypt_ok = true;
               if(!opb->v.empty())
                  decrypt_ok = DECRYPT(opb);  //true if either no encryption or decryption OK
               int jbd_max = cntd_uc->wopt->get_JBD_Max();
               if(wopt_queue_sz > jbd_max)
                 {   //Will be reset in the updateSentQueue()
                 cntd_uc->wopt->SQC = true;         //start_adaptive_queue_correction
                         //  lasterr = "\nSTART_adaptive_queue_correction\n";
                        //   sendlasterr(1);
                 mid_cnt_thresh = 0;
                 cntd_uc->wopt->SNC.inc_discarded();
                 if(cntd_uc->wopt->Suspended)
                    cntd_uc->wopt->Resume_Thread();

            //     /*
                 string timestr;
                 TDateTime dt = dt.CurrentTime();
                 exsTime( dt,timestr);
                 lasterr = "\n" + timestr + " wopt queue_size > JBD_Max = " + inttostr(jbd_max)+  " RESET audio packet";
                 sendlasterr(1);
          //       */

                 }
               else if((wopt_queue_sz > 10) && (cntd_uc->wopt->SQC) && (!(++mid_cnt_thresh & 0x3F))) // but <  jbd_max примерно раз в 1.3 sec сбрасываетс€ пвкет
                 {
                  cntd_uc->wopt->SNC.inc_discarded();
                  if(cntd_uc->wopt->Suspended)
                    cntd_uc->wopt->Resume_Thread();

               //     /*
                   string timestr;
                   TDateTime dt = dt.CurrentTime();
                   exsTime( dt,timestr);
                   lasterr = "\n" + timestr + " wopt queue_size > 10 and < JBD_Max = " + inttostr(jbd_max)+  " RESET audio packet";
                   sendlasterr(1);
              //     */

                 }
               else
                 {
                // mid_cnt_thresh = 0;
                 if(cntd_uc->wopt->SQC)
                   if(wopt_queue_sz < 10)
                     {
                  //   lasterr = "\n RESET_adaptive_queue_correction\n";
                  //   sendlasterr(1);
                     cntd_uc->wopt->SQC = false; // сброс start_adaptive_queue_correction;
                     }
                 if(!opb->v.empty())
                   {
                   if(decrypt_ok) //true if either no encryption or decryption OK
                     {
                     if(TTest_Sound->ChDispUnpackRtpPacket->Checked)
                        decompress_sound_packet(cntd_uc, opb);

                     /*
                     if(TTest_Sound->JBD_Min_Control->Checked)
                        {
                        sound_jbd_min_proc(wopt_queue_sz, cntd_uc, opb); !!! не удал€ть
                        }
                      */
                      /*
                     if(opb->mark)
                        cntd_uc->wopt->count_after_mark = 0;
                     else
                        cntd_uc->wopt->count_after_mark++;
                      */

                     cntd_uc->wopt->setQueue(opb);
                     }
                   }
                 }
               }
           }
         else if(cntd_uc->mpt == RTP_AUDIO_MPT)
           {
           if(cntd_uc->sendThread)
             {
             opb->tunnel_name = "a" + inttostr(cntd_uc->getChId());
             cntd_uc->sendThread->setQueue(opb);
             }
           }
         }
       #ifdef SIP_Video
       else if(mpt == RTP_VIDEO_MPT)
         {
         if(cntd_uc->mpt == VIDEO_MPT)
           {
           if(cntd_uc->vscr)
             {
             if(opb->local_loop)
               {
               opb->local_loop = false;
               if(opb->getReferenceCount() > 0)
                 {
                 cntd_uc->vscr->setQueue(opb);  //do not replace
                 opb->decReferenceCount();
                 }
               else
                 cntd_uc->vscr->setQueue(opb);  //do not replace
               }
             else
               {
               int vscr_queue_sz = cntd_uc->vscr->getQueueSize();
               if(cntd_uc->vscr->ReportTime < cntd_uc->vscr->ReportTime.CurrentDateTime())
                 {
                 #ifdef PCS_Trace
                 lasterr = "\nvscr ch_" + inttostr(cntd_uc->getChId());
                 cntd_uc->getMediaPacketType(lasterr);
                 lasterr += " queue_size " + inttostr(vscr_queue_sz);
                 sendlasterr(1);
                 #endif
                 cntd_uc->vscr->ReportTime += TDateTime(0,0,video_report_interval,0); //10 sec
                 }
               if(vscr_queue_sz > cntd_uc->vscr->JBD_video_max)
                 {
                 lasterr = "\nvscr queue_size > JBD_video_max = " + inttostr(cntd_uc->vscr->JBD_video_max) + " size " + inttostr(vscr_queue_sz);
                 if(isVideoPacketPSC(opb->v))
                   {
                   #ifdef PCS_Trace
                   lasterr += " PSC packet reject";
                   #endif
                   switch(cntd_uc->vscr->get_Video_Queue_State()){
                         case Video_Queue_State__NORMAL:      //reject packet
                              #ifdef PCS_Trace
                              lasterr += " State NORMAL";
                              #endif
                              cntd_uc->vscr->set_Video_Queue_State(Video_Queue_State__PASS_FRAME);
                              break;
                         case Video_Queue_State__WAIT_PSC:
                              #ifdef PCS_Trace
                              lasterr += " State WAIT_PSC";
                              #endif
                              cntd_uc->vscr->set_Video_Queue_State(Video_Queue_State__PASS_FRAME);
                              break;
                         case Video_Queue_State__PASS_FRAME:   //Reject packet
                              #ifdef PCS_Trace
                              lasterr += " State PASS_FRAME";
                              #endif
                              break;
                         }
                   } //if(isVideoPacketPSC(opb->v))
                 else
                   {
                   #ifdef PCS_Trace
                   lasterr += " regular packet";
                   #endif
                   switch(cntd_uc->vscr->get_Video_Queue_State()){
                         case Video_Queue_State__NORMAL:
                              #ifdef PCS_Trace
                              lasterr += " setQueue State NORMAL";
                              #endif
                              DECRYPT(opb);
                              cntd_uc->vscr->setQueue(opb);
                              cntd_uc->vscr->set_Video_Queue_State(Video_Queue_State__WAIT_PSC);
                              break;
                         case Video_Queue_State__WAIT_PSC:
                              #ifdef PCS_Trace
                              lasterr += " setQueue State WAIT_PSC";
                              #endif
                              DECRYPT(opb);
                              cntd_uc->vscr->setQueue(opb);
                              break;
                         case Video_Queue_State__PASS_FRAME:   //Reject packet
                              #ifdef PCS_Trace
                              lasterr += " rejected State PASS_FRAME";
                              #endif
                              break;
                         }

                   }
                  #ifdef PCS_Trace
                  sendlasterr(1);
                  #endif
 //                cntd_uc->vscr->clearQueue();
                 } //if(vscr_queue_sz > cntd_uc->vscr->JBD_video_max)
               else //vscr_queue_sz <= cntd_uc->vscr->JBD_video_max
                 {
                 #ifdef PCS_Trace
                 lasterr = "\nvscr queue_size " + inttostr(vscr_queue_sz);
                 #endif
                 if(isVideoPacketPSC(opb->v))
                   {
                   #ifdef PCS_Trace
                   lasterr += " PSC ";
                   #endif
                   switch(cntd_uc->vscr->get_Video_Queue_State()){
                          case Video_Queue_State__NORMAL:
                               #ifdef PCS_Trace
                               lasterr += " State NORMAL setQueue";
                               #endif
                               DECRYPT(opb);
                               cntd_uc->vscr->setQueue(opb);
                               break;
                          case Video_Queue_State__WAIT_PSC:
                               #ifdef PCS_Trace
                               lasterr += " State WAIT_PSC --> PASS_FRAME rejected";
                               #endif
                               cntd_uc->vscr->set_Video_Queue_State(Video_Queue_State__PASS_FRAME);
                               break;
                          case Video_Queue_State__PASS_FRAME:
                               #ifdef PCS_Trace
                               lasterr += " State PASS_FRAME";
                               #endif
                               if(!vscr_queue_sz)
                                 {
                                 #ifdef PCS_Trace
                                 lasterr += " --> NORMAL setQueue";
                                 #endif
                                 DECRYPT(opb);
                                 cntd_uc->vscr->setQueue(opb);
                                 cntd_uc->vscr->set_Video_Queue_State(Video_Queue_State__NORMAL);
                                 }
                               else
                                 lasterr += " rejected";
                               break;
                           }
                   }   //if(isVideoPacketPSC(opb->v))
                 else
                   {
                   #ifdef PCS_Trace
                   lasterr += " !PSC ";
                   #endif
                   switch(cntd_uc->vscr->get_Video_Queue_State()){
                         case Video_Queue_State__NORMAL:
                              #ifdef PCS_Trace
                              lasterr += " State NORMAL setQueue";
                              #endif
                              DECRYPT(opb);
                              cntd_uc->vscr->setQueue(opb);
                              break;
                         default:
                                lasterr += "rejected";
                                break;
                         }
                   }
                 sendlasterr(1);
                 }
               }
             } //if(cntd_uc->vscr)
           }//if(cntd_uc->mpt == VIDEO_MPT)
          else if(cntd_uc->mpt == RTP_VIDEO_MPT)
           {
           if(cntd_uc->sendThread)
             {
             opb->tunnel_name = "v" + inttostr(cntd_uc->getChId());
             cntd_uc->sendThread->setQueue(opb);
             }
           } // if(cntd_uc->mpt == VIDEO_MPT)
         } //else if(mpt == RTP_VIDEO_MPT)
       #endif //#ifdef SIP_Video
       }  //if(cntd_uc)
     }    //while(it!=myCtns.end())
::LeaveCriticalSection(&mycnts);
}
//------------------------------------------------------------------------------
void __fastcall TUdpChannel::proc_RTCP_PCKT(TOutPutUdpBlock* opb)
{
int sz = opb->v.size();
if(sz == 2)
  {
  if(opb->v[0] == 0x00)
    if(opb->v[1] == 0x01) //ordinary VAD received
      {
      TMediaSession* ms = MainFormSLS->Sip->sss->GetMs_by_In_Out_Callid(in_out__callid);
      if(ms)
        {
        TConfExchBlock* ExchBlock = new TConfExchBlock;
        if(ExchBlock)
          {
          ExchBlock->conf_evnt = ConfEvnt_VAD_Received;
          ExchBlock->user_name = ms->get_uniq_username();
          ConferenceWin->ins_exch_buf(ExchBlock);
          ::PostMessage(ConferenceWin->Handle, CONFERENCE_MSG, WM_CONFERENCE_MSG_WPARAM__NDEF, WM_CONFERENCE_MSG_LPARAM__NDEF);
          }
        }
      }
  }
else if(sz > 2)
  {
  if(opb->v[0] == 0x00)
    if(opb->v[1] == 0x02) //distributed VAD received from conference creator
      if(opb->v[sz-1] == 0x00) //end of string user_name
        {
        TConfExchBlock* ExchBlock = new TConfExchBlock;
        if(ExchBlock)
          {
          ExchBlock->conf_evnt = ConfEvnt_VAD_DISTR_Received;
          ExchBlock->user_name = string((char*)&opb->v[2]);
          ConferenceWin->ins_exch_buf(ExchBlock);
          ::PostMessage(ConferenceWin->Handle, CONFERENCE_MSG, WM_CONFERENCE_MSG_WPARAM__NDEF, WM_CONFERENCE_MSG_LPARAM__NDEF);
          }
        }
  }
}
//------------------------------------------------------------------------------
void  __fastcall TSendThread::clearQueue()
{
::EnterCriticalSection(&optudp);
  while(!q.empty())
       {
       TOutPutUdpBlock* opb = q.front();
       q.pop();
       if(opb->get_req_to_delete())
         {
         if(opb->getReferenceCount() < 3)
             exsDeleteSentBlock((BaseExchangeBlock*)opb);
         }
       else
         opb->decReferenceCount();
       }
::LeaveCriticalSection(&optudp);
}
//------------------------------------------------------------------------------
TOutPutUdpBlock* __fastcall TSendThread::getQueue()
{
TOutPutUdpBlock* rv = NULL;
::EnterCriticalSection(&optudp);
  if(!q.empty())
    {
    rv = q.front();
    q.pop();
    }
::LeaveCriticalSection(&optudp);
return rv;
}
//----------------------------------------------------------------------------
void  __fastcall TSendThread::setQueue(TOutPutUdpBlock* opb)
{
::EnterCriticalSection(&optudp);
  opb->incReferenceCount();
  q.push(opb);
  if(Suspended)
     Resume_Thread();
::LeaveCriticalSection(&optudp);
}
//----------------------------------------------------------------------------
int __fastcall TSendThread::getQueueSize()
{
int rv = 0;
::EnterCriticalSection(&optudp);
  rv = q.size();
::LeaveCriticalSection(&optudp);
return rv;
}
//----------------------------------------------------------------------------
__fastcall TSendThread::~TSendThread()
{
clearQueue();
if(G729ENC)
  delete G729ENC;
if(SRTP)
  delete SRTP;
::DeleteCriticalSection(&optudp);
::DeleteCriticalSection(&st_sc);
::DeleteCriticalSection(&rhost_cs);
}
//----------------------------------------------------------------------------
void __fastcall TSendThread::Execute()
{
try{
//TDateTime PrevTime = PrevTime.CurrentDateTime();
//TDateTime Phase_1  = TDateTime(0,0,0,15);
while(!Terminated)
 {

   /*
   if(delay)
     {
     TDateTime CurrDateTime = CurrDateTime.CurrentDateTime();
     TDateTime difftime = CurrDateTime - PrevTime;
       #ifdef RTP_Send_Trace
       TEventLogThread* elt = *eltp;
       if(elt)
        if(elt->getlog())
          {
          string str = "\nTSendThread: Current Time < nextdt ";
          unsigned short hour;
          unsigned short min;
          unsigned short sec;
          unsigned short msec;
          difftime.DecodeTime(&hour,&min,&sec,&msec);
          str += " - " + inttostr(hour) + "." + inttostr(min) + "." + inttostr(sec) + "." + inttostr(msec);
          str = str + "\n";
          elt->FputEvt(str);
          }
       #endif
       if(difftime < Phase_1)
         {
         #ifdef RTP_Send_Trace
         TEventLogThread* elt = *eltp;
         if(elt)
           if(elt->getlog())
            elt->FputEvt("\n::Sleep(1)");
         #endif
         ::Sleep(1);
         continue;
         }
       else
        {
        PrevTime = CurrDateTime;
        }
     }
     */


   if(DTS.digit_transmission(this))
      continue;
   TOutPutUdpBlock* opb = getQueue();
   if(!opb)
     {
     if(Uc->getMpt() == RTP_AUDIO_MPT)
       {
       if(!FirstMediaPacketSent)
         {             //Send init audio packets while not get fist mic packet (mic packets depends of receiving packets)
          TOutPutUdpBlock* opb_1 = new TOutPutUdpBlock;
          opb_1->mpt = SOUND_MPT_INIT;
          opb_1->v.resize(320,0);
          setQueue(opb_1);
        ::Sleep(100);
          continue;
         }
       }
     else if(Uc->getMpt() == RTP_VIDEO_MPT)
       {
       if(Uc->recvThread)
         if(!Uc->recvThread->first_packet_rcvd())
           {
           TOutPutUdpBlock* opb_1 = new TOutPutUdpBlock;
           opb_1->mpt = VIDEO_MPT;
           opb_1->v.resize(4,0);
           setQueue(opb_1);
         ::Sleep(100);
           continue;
           }
       }
     Suspend_Thread();
     continue;
     }
   if(OnHold){
     int sz = opb->v.size();
     for(int i=0;i<sz;i++)
         opb->v[i] = 0;
     }
   if(opb->mpt == UNKNOWN_MPT)
     {
     int bwrote = sendbuf(opb);
     if(bwrote == SOCKET_ERROR)
      {
      int err = WSAGetLastError();
      lasterr = "TSendThread::Execute()";
      GetLastSocketError(lasterr,err);
      sendlasterr();
      }
     if(Uc->getMpt() == RTP_AUDIO_MPT)
       if(!FirstMediaPacketSent)
           FirstMediaPacketSent = true;
     opb->decReferenceCount();
     continue;
     }

   TOutPutUdpBlock work_opb;

   switch(opb->mpt){
         #ifdef SIP_Video
     case VIDEO_MPT:{
          prepare_video_RtpPacket(&work_opb,opb);
          ENCRYPT(&work_opb);
          break;
          }
         #endif
     case SOUND_MPT:{
          switch(remoteCodec){
                 case  0:LinearToULaw(opb->v);break;
                 case  8:LinearToALaw(opb->v);break;
                 case 18:if(G729ENC)
                            G729ENC->LinearToG729(opb);
                         break;
                 }//switch(remoteCodec){
          prepare_audio_RtpPacket(opb);
          ENCRYPT(opb);
          work_opb.tunnel_name = opb->tunnel_name;
          work_opb.v = opb->v;
          FirstMediaPacketSent = true;   //!!! only at this place
          break;
          } //case SOUND_MPT

     case SOUND_MPT_INIT:{
          switch(remoteCodec){
                 case  0:LinearToULaw(opb->v);break;
                 case  8:LinearToALaw(opb->v);break;
                 case 18:if(G729ENC)
                            G729ENC->LinearToG729(opb);
                         break;
                 }//switch(remoteCodec){
          prepare_audio_RtpPacket(opb);
          ENCRYPT(opb);
          work_opb.tunnel_name = opb->tunnel_name;
          work_opb.v = opb->v;
          break;
          } //case SOUND_MPT

     case INIT_MPT:{
          work_opb.mpt = opb->mpt;
          work_opb.v   = opb->v;
          break;
          }
     case INIT_RTCP_MPT:{
          work_opb.mpt = opb->mpt;
          work_opb.v   = opb->v;
          break;
          }
     case RTCP_VAD:{
          work_opb.mpt = opb->mpt;
          work_opb.v   = opb->v;
          break;
          }
     } //switch(opb->mpt)

    #ifdef SIP_Video
    #ifdef Client_Test_Block
    if( Uc->test_block.local_video_rtp_loop)
      {
      if(opb->mpt == VIDEO_MPT)
        if(Uc->chDispThread)
          {
          opb->local_loop = true;
          Uc->chDispThread->pushToSend(opb);
          continue;
          }
       }
    #endif
    #endif
   SEND_RTP_PACKET(&work_opb,opb);
   if(opb->mpt == INIT_MPT)
      delete opb;
   else if(opb->mpt == INIT_RTCP_MPT)
      delete opb;
   else if(opb->mpt == SOUND_MPT_INIT)
      delete opb;
   else if(opb->mpt == RTCP_VAD)
      delete opb;
   else
     opb->decReferenceCount();
 }
}//try
catch(Exception& e){exsSstEXCEPTION(*eltp,"__TSendThread::Execute",e);}

}
//----------------------------------------------------------------------------
int __fastcall TSendThread::sendbuf(TOutPutUdpBlock* opb)
{
int len = opb->v.size();
if(!len)return 0;
int retval = 0;
if(RemotePort == -1)
  {
  #ifdef RTP_LogSendBufPacket
  if(not_assigned_count < 4)
    {
    TEventLogThread* elt = *eltp;
    if(elt)
      if(elt->getlog())
        {
        string s_sck = inttostr(Uc->getSocket());
        TDateTime DateTime = DateTime.CurrentDateTime();
        string str;
        exsTime(DateTime,str);
        if(not_assigned_count == 3)
           str = "\n" + str + " sck " + s_sck + " ch_" + inttostr(Uc->getChId()) + " Remote addres not yet assigned ..." + "\n";
        else
           str = "\n" + str + " sck " + s_sck + " ch_" + inttostr(Uc->getChId()) + " Remote addres not yet assigned" + "\n";
        elt->FputEvt(str);
        }
    not_assigned_count++;
    }
  #endif
  }
else
  {
 // if(MainFormSLS->BLOCK_SEND_RTP)
 //     return 0;
  if(!Uc->delayToTransmitPacketCount)
    {
    struct sockaddr_in dest;
    memset(&dest,0,sizeof(dest));
    dest.sin_family = AF_INET;
    dest.sin_addr.s_addr = inet_addr(getRemoteAddr().c_str());
    dest.sin_port = htons(RemotePort);
    TDateTime DateTime = DateTime.CurrentDateTime();
    SOCKET s_c_k = Uc->getSocket();
    if(s_c_k != INVALID_SOCKET)
       retval = sendto(s_c_k, &opb->v[0], len, 0, (struct sockaddr*)&dest, sizeof(dest));
    #ifdef RTP_LogSendPacket
    LOG_SendPacket(DateTime,opb,len);
    #else
    if(!FirstPacketSent)
      {
      if(opb->mpt != INIT_MPT)
        {
         FirstPacketSent = true;
       __sent_packet_count++;
        }
      LOG_InitialPacketSent(opb);
      }
    else
      {
      if(opb->mpt == UNKNOWN_MPT)
        {
        if(++__sent_packet_count < 20)
          {
          int sz = opb->v.size();
          LOG_first_20_sent_packets(sz);
          }
        }
      }
    #endif
    }
  else
    {
    --Uc->delayToTransmitPacketCount;
    #ifdef RTP_LogSendPacket
    TEventLogThread* elt = *eltp;
    if(elt)
    if(elt->getlog())
      {
      TDateTime DateTime = DateTime.CurrentDateTime();
      string str;
      exsTime(DateTime,str);
      str = "\n" + str + " sck " + inttostr(sck) + " ch_" + inttostr(UC->getChId()) + " Delay To transmit Packet count " + inttostr(UC->delayToTransmitPacketCount) + "\n";
      elt->FputEvt(str);
      }
    #endif
    }
  }
return retval;
}
//----------------------------------------------------------------------------
void __fastcall TSendThread::LOG_first_20_sent_packets(int len)
{
TEventLogThread* elt = getLog();
if(elt)
  {
  TDateTime DateTime  = DateTime.CurrentDateTime();
  TDateTime dt_diff   = DateTime - __dt_prev_sent_packet;
__dt_prev_sent_packet = DateTime;
  string s;
  exsTime(DateTime,s);
  s = "\n" + s + " sck " + inttostr(Uc->getSocket()) + " ch_" + inttostr(Uc->getChId()) + " rtp packet " + inttostr(__sent_packet_count) + " length " + inttostr(len);
  string dt;
  exsTime(dt_diff, dt);
  s += " dt " + dt + " Sent To " + getRemoteAddr() + ":" + inttostr(RemotePort) + "\n";
  elt->FputEvt(s);
  }
}
//------------------------------------------------------------------------------
void __fastcall TSendThread::LOG_SendPacket(TDateTime& DateTime,TOutPutUdpBlock* opb,int len)
{
TEventLogThread* elt = getLog();
if(elt)
  {
  string str;
  exsTime(DateTime,str);
  string s_sck = inttostr(Uc->getSocket());
  str = "\n" + str + " sck " + s_sck + " ch_" + inttostr(Uc->getChId());
  Uc->getMediaPacketType(str);
  str += " Pckt# " + inttostr(opb->pktn) + " SendTo " + getRemoteAddr() + ":" + inttostr(RemotePort) + " Len " + inttostr(len) + "\n";
  for(int i=0;i<len;i++)
    str += " " + inttohexstr(opb->v[i],2);
  str+="\n";
  elt->FputEvt(str);
  }
}
//----------------------------------------------------------------------------
TEventLogThread* __fastcall TSendThread::getLog()
{
TEventLogThread* elt = *eltp;
if(elt)
 if(elt->getlog())
    return elt;
return NULL;
}
//----------------------------------------------------------------------------
void __fastcall TSendThread::sendlasterr()
{
TEventLogThread* elt = *eltp;
if(!elt)return;
if(!elt->getlog())return;
elt->FputEvt(lasterr);
}
//----------------------------------------------------------------------------
void __fastcall TChannelDispThread::checkSent()
{
if(!sent.empty())
  {
  deque<TOutPutUdpBlock*>::iterator it = sent.begin();
  while(it!=sent.end())
       {
       BaseExchangeBlock* opb = (BaseExchangeBlock*)(*it);
       if(opb->getReferenceCount() < 1)
         {
         sent.erase(it);
         exsDeleteSentBlock(opb);
         it = sent.begin();
         }
       else
         it++;
       }
  }
}
//------------------------------------------------------------------------------
void __fastcall TChannelDispThread::getSent()
{
while(!sent.empty())
     {
     BaseExchangeBlock* opb = (BaseExchangeBlock*)sent.front();
     if(opb->getReferenceCount() < 1)
       {
       sent.pop_front();
       exsDeleteSentBlock(opb);
       }
     else
       break;
     }
}
//------------------------------------------------------------------------------
unsigned  __fastcall TUdpChannel::getLocalSocketParameters(bool LOG)
{
unsigned LocalPort = 0;
TEventLogThread* elt = getLogThread();
if(!elt)return LocalPort;
sockaddr name;
memset(&name,0,sizeof(name));
int namelen = sizeof(name);
if(getsockname(sck, &name, &namelen)==SOCKET_ERROR)
  {
  int err = WSAGetLastError();
  lasterr = "getsockname()";
  GetLastSocketError(lasterr,err);
  sendlasterr();
  return LocalPort;
  }
int n=0;
string LocalAddr;
UBYTE* buf = (UBYTE*)name.sa_data; //!!!!!Protection from expansion of the sign bit to the left. Otherwise we have to shall every time produce mask of values with constants 0xFF00 and 0xFF
LocalPort |= buf[n++] << 8;
LocalPort |= buf[n++];
LocalAddr+= inttostr((UBYTE)name.sa_data[n++]) + ".";
LocalAddr+= inttostr((UBYTE)name.sa_data[n++]) + ".";
LocalAddr+= inttostr((UBYTE)name.sa_data[n++]) + ".";
LocalAddr+= inttostr((UBYTE)name.sa_data[n++]);
localport = LocalPort;
localhost = LocalAddr;
if(LOG)
  elt->FputEvt("\nUDPSocketCreated: sck " + inttostr(sck ) + " LocalAddr " + LocalAddr + ":" + inttostr(LocalPort),1);
int optVal;
int optLen = sizeof(int);
if(getsockopt(sck,SOL_SOCKET,SO_MAX_MSG_SIZE,(char*)&optVal,&optLen) == SOCKET_ERROR)
  {
  int err = WSAGetLastError();
  lasterr = "getsockopt()";
  GetLastSocketError(lasterr,err);
  sendlasterr();
  return LocalPort;
  }
if(LOG)
  elt->FputEvt("\nSO_MAX_MSG_SIZE: " + inttostr(optVal),1);
return LocalPort;
}
//-----------------------------------------------------------------------------
void __fastcall TUdpChannel::Connect(TUdpChannel* pch)
{
if(!pch)return;
pch->cntdToMe_Add(chID);
::EnterCriticalSection(&mycnts);
  myCtns.push_back(pch);
::LeaveCriticalSection(&mycnts);
}
//-----------------------------------------------------------------------------
void __fastcall TUdpChannel::Disconnect(TUdpChannel* pch)
{
if(!pch)return;
pch->cntdToMe_Remove(chID);
::EnterCriticalSection(&mycnts);
  if(!myCtns.empty())
    {
    for(deque<TUdpChannel*>::iterator it = myCtns.begin();it < myCtns.end();it++)
       {
       if(pch == (*it))
         {
         myCtns.erase(it);
         break;
         }
       }
    }
::LeaveCriticalSection(&mycnts);
}
//------------------------------------------------------------------------------
bool   __fastcall TUdpChannel::IsConnected(TUdpChannel* pch)
{
bool rv=false;
::EnterCriticalSection(&mycnts);
  if(!myCtns.empty())
    {
    for(deque<TUdpChannel*>::iterator it = myCtns.begin();it < myCtns.end();it++)
       {
       if(pch == (*it))
         {
         rv=true;
         break;
         }
       }
    }
::LeaveCriticalSection(&mycnts);
return rv;
}
//------------------------------------------------------------------------------
void __fastcall TUdpChannel::cntdToMe_Add(int a)
{
::EnterCriticalSection(&cntdtome);
  cntdToMe.push_back(a);
::LeaveCriticalSection(&cntdtome);
}
//------------------------------------------------------------------------------
void __fastcall TUdpChannel::cntdToMe_Remove(int a)
{
::EnterCriticalSection(&cntdtome);
for(deque<int>::iterator it=cntdToMe.begin();it<cntdToMe.end();it++)
   {
   if(a==(*it))
     {
     cntdToMe.erase(it);
     break;
     }
   }
::LeaveCriticalSection(&cntdtome);
}
//------------------------------------------------------------------------------
void  __fastcall TUdpChannel::printAllMyConnections(int type)
{
TEventLogThread* elt = getLogThread();
if(!elt)return;
string s;
vector<int> v;
getAllMyConnections(v);
if(!v.empty())
  {
  if(type == 1)
    s = "\nConference Connections of channel #" + inttostr(chID) + ":";
  else
    s = "\nConnections of channel #" + inttostr(chID) + ":";
  getMediaPacketType(s);
  s += " ch_" + inttostr(chID) + "->";
  for(unsigned i=0;i<v.size();i++)
     {
     if(i)s+=",";
     s+="ch_" + inttostr(v[i]);
     }
  elt->FputEvt(s);
  }
v.resize(0);
getAllConnectionsToMe(v);
if(!v.empty())
  {
  if(type == 1)
    s = "\nConference Connections to channel #" + inttostr(chID) + ":";
  else
    s = "\nConnections to channel #" + inttostr(chID) + ":";
  getMediaPacketType(s);
  s += " ch_" + inttostr(chID) + "<-";
  for(unsigned i=0;i<v.size();i++)
     {
     if(i)s+=",";
     s+="ch_" + inttostr(v[i]);
     }
  elt->FputEvt(s);
  }
}
//------------------------------------------------------------------------------
void __fastcall TUdpChannel::getAllMyConnections(vector<int>& v)
{
deque<TUdpChannel*>::iterator it;
::EnterCriticalSection(&mycnts);
  for(it = myCtns.begin(); it < myCtns.end(); it++)
      v.push_back((*it)->chID);
::LeaveCriticalSection(&mycnts);
}
//------------------------------------------------------------------------------
void __fastcall TUdpChannel::getAllConnectionsToMe(vector<int>& v)
{
deque<int>::iterator it;
::EnterCriticalSection(&cntdtome);
for(it=cntdToMe.begin();it<cntdToMe.end();it++)
    v.push_back(*it);
::LeaveCriticalSection(&cntdtome);
}
//------------------------------------------------------------------------------
void __fastcall TUdpChannel::DisconnectAllMyConnections()
{
int ret=1;
while(ret)
     {
     TUdpChannel* uc=NULL;
     ::EnterCriticalSection(&mycnts);
       if(myCtns.empty())
          ret=0;
       else
          {
          uc = myCtns.front();
          myCtns.pop_front();
          }
     ::LeaveCriticalSection(&mycnts);
     if(uc)
        uc->cntdToMe_Remove(chID);
     }
}
//------------------------------------------------------------------------------
bool __fastcall TUdpChannel::myCtns_Empty()
{
bool rv=false;
::EnterCriticalSection(&mycnts);
  if(myCtns.empty())
     rv=true;
::LeaveCriticalSection(&mycnts);
return rv;
}
//------------------------------------------------------------------------------
bool __fastcall TUdpChannel::cntdToMe_Empty()
{
bool rv=false;
::EnterCriticalSection(&cntdtome);
  if(cntdToMe.empty())
     rv=true;
::LeaveCriticalSection(&cntdtome);
return rv;
}
//------------------------------------------------------------------------------
void   __fastcall TUdpChannel::INIT_Sdp_For_SRTP_Session(TSdpMedia* sdp_media, SipUAThreadType uatt)
{
if(sendThread)
  {
  TSRTPCrypto* crypto = sendThread->getSRTP();
  if(crypto)
    {
    string s = "a=crypto:1" + wsp + AES_CM_128_HMAC_SHA1_80 + wsp + "inline:" + crypto->protect_key + crlf;
    sdp_media->crypto_keys.push_back(s);
    sdp_media->media_protocol = "RTP/SAVP";
    }
  }
}
//------------------------------------------------------------------------------
void __fastcall TSRTPCrypto::create_egress_srtp_session()
{
if(ses)
  {
  rsrtp_drop_session(ses);
  ses = NULL;
  }
rsrtp_create_session(&ses);
char key[128] = {0};
rsrtp_get_protect_base64key(ses,key,&protect_key_sz);
protect_key = string(key);
}
//------------------------------------------------------------------------------
void __fastcall TSRTPCrypto::create_ingress_srtp_session(vector<string>& v)
{
string s;
if(get_AES_CM_128_HMAC_SHA1_80(v,s))
  {
  if(ses)
    {
    rsrtp_drop_session(ses);
    ses = NULL;
    }
  protect_key_sz = s.length();
  rsrtp_create_session(&ses);
  rsrtp_set_unprotect_base64key(ses, s.c_str(), protect_key_sz);
  }
}
//------------------------------------------------------------------------------
bool __fastcall TSRTPCrypto::get_AES_CM_128_HMAC_SHA1_80(vector<string>& v,string& s)
{
bool rv = false;
vector<string>::iterator it = v.begin();
while(it != v.end())
     {
     if((*it).find(AES_CM_128_HMAC_SHA1_80) != -1)
       {
       s = get_remote_key(*it);
       rv = true;
       break;
       }
     it++;
     }
return rv;
}
//------------------------------------------------------------------------------
string __fastcall TSRTPCrypto::get_remote_key(const string& S)
{
string s = S;
int st  = s.find("inline:");
if(st != -1)
  {
  st+=7;
  if(st < (int)s.length())
    {
    s = s.substr(st);
    int en = s.find(crlf);
    if(en != -1)
       s.resize(en);
    en = s.find(":");
    if(en != -1)
      s.resize(en);
    en = s.find(";");
        if(en != -1)
    s.resize(en);
    }
  }
return s;
}
//------------------------------------------------------------------------------
void __fastcall TSRTPCrypto::printDecryptionError(TUdpChannel* uc,int err)
{
if(!err_threshold)
  {
  if(++err_count < MAX_CRYPTO_SESS_LOG_ERROR)
     uc->printCryptoError(err,0);  // 0 - Decryption Error
  else
     {
     err_threshold = true;
     uc->printCryptoError(err,2);  // "threshold is reached"
     }
  }
}
//-----------------------------------------------------------------------------
void __fastcall TSRTPCrypto::printEncryptionError(TUdpChannel* uc,int err)
{
if(!err_threshold)
  {
  if(++err_count < MAX_CRYPTO_SESS_LOG_ERROR)
     uc->printCryptoError(err,1);  // 1 - Encryption Error
  else
     {
     err_threshold = true;
     uc->printCryptoError(err,2);  // "threshold is reached"
     }
  }
}
//-----------------------------------------------------------------------------
#ifndef RTP_exsCreateUDPSocket_ADDR_ANY
void __fastcall TVoipMediaPortBlock::freePort(int port)
{
::EnterCriticalSection(&mpl_cs);
  TMediaPortList::iterator it = mpl->find(port);
  if(it != mpl->end())
     mpl->erase(it);
::LeaveCriticalSection(&mpl_cs);
}
//------------------------------------------------------------------------------
void __fastcall TVoipMediaPortBlock::insertPort(int port)
{
::EnterCriticalSection(&mpl_cs);
  mpl->insert(TMediaPortList::value_type(port,0));
::LeaveCriticalSection(&mpl_cs);
}
//------------------------------------------------------------------------------
bool __fastcall TVoipMediaPortBlock::isPortFree(int port)
{
bool rv=false;
::EnterCriticalSection(&mpl_cs);
  if(mpl->find(port) == mpl->end())
     rv=true;
::LeaveCriticalSection(&mpl_cs);
return rv;
}
#endif //#ifndef RTP_exsCreateUDPSocket_ADDR_ANY
//------------------------------------------------------------------------------
void __fastcall TSendThread::setFirstRtpByte(vector<UBYTE>& v,int version,bool padding,bool extention,int csic)
{
UBYTE bt = (version & 0x3) << 6;
if(padding)
  bt|=0x20;
if(extention)
  bt|=0x10;
bt|=csic & 0xF;
v.push_back(bt);
}
//------------------------------------------------------------------------------
void __fastcall TSendThread::setSecondRtpByte(vector<UBYTE>& v,bool marker,int PayLoadType)
{
UBYTE bt = PayLoadType & 0x7F;
if(marker)
  bt|=0x80;
v.push_back(bt);
}
//------------------------------------------------------------------------------
void __fastcall TSendThread::setSeqNumber(vector<UBYTE>& v)
{
v.push_back((currentSeqNumber >> 8 )& 0xFF);
v.push_back(currentSeqNumber & 0xFF);
currentSeqNumber++;
}
//------------------------------------------------------------------------------
void __fastcall TSendThread::setTimeStamp(vector<UBYTE>& v)
{
v.push_back((currentTimeStamp >> 24) & 0xFF);
v.push_back((currentTimeStamp >> 16) & 0xFF);
v.push_back((currentTimeStamp >>  8) & 0xFF);
v.push_back(currentTimeStamp & 0xFF);
switch(remoteCodec){
      case 0:currentTimeStamp+=160;     //  g711 ulaw
             break;
      case 8:currentTimeStamp+=160;     //  g711 alaw
             break;
      default:currentTimeStamp+=160;
      }
}
//-----------------------------------------------------------------------------
void __fastcall TSendThread::set_2833_TimeStamp(vector<UBYTE>& v,TOutPutDtmfBlock* opd)
{
v.push_back((currentTimeStamp >> 24) & 0xFF);
v.push_back((currentTimeStamp >> 16) & 0xFF);
v.push_back((currentTimeStamp >>  8) & 0xFF);
v.push_back(currentTimeStamp & 0xFF);
currentTimeStamp += opd->event_duration;
DTS.current_2833_timestamp = currentTimeStamp;
}
//-----------------------------------------------------------------------------
void __fastcall TSendThread::set_2833_DuplicatedTimeStamp(vector<UBYTE>& v,TOutPutDtmfBlock* opd)
{
v.push_back((currentTimeStamp >> 24) & 0xFF);
v.push_back((currentTimeStamp >> 16) & 0xFF);
v.push_back((currentTimeStamp >>  8) & 0xFF);
v.push_back(currentTimeStamp & 0xFF);
DTS.current_2833_timestamp += opd->event_duration;
}
//-----------------------------------------------------------------------------
void __fastcall TSendThread::setTimeStamp_Video(vector<UBYTE>& v)
{
unsigned a = ::GetTickCount();
v.push_back((a >> 24) & 0xFF);
v.push_back((a >> 16) & 0xFF);
v.push_back((a >>  8) & 0xFF);
v.push_back(a & 0xFF);
}
//-----------------------------------------------------------------------------
void __fastcall TSendThread::setSourceId(vector<UBYTE>& v)
{
v.push_back((sourceId >> 24) & 0xFF);
v.push_back((sourceId >> 16) & 0xFF);
v.push_back((sourceId >>  8) & 0xFF);
v.push_back(sourceId & 0xFF);
}
//------------------------------------------------------------------------------
void __fastcall TSendThread::LinearToALaw(vector<UBYTE>& src_v)
{
vector<UBYTE> v;
int size = src_v.size();
for(int i=0;i<size;i+=2)
  {
  short a = src_v[i] & 0xFF;
        a |= ((src_v[i+1] << 8)&0xFF00);
  UBYTE b = linear2alaw(a);
  v.push_back(b);
  }
src_v = v;
}
//--------------------------------------------------------------------------------
void __fastcall TSendThread::LinearToULaw(vector<UBYTE>& src_v)
{
vector<UBYTE> v;
int size = src_v.size();
for(int i=0;i<size;i+=2)
  {
  short a = src_v[i] & 0xFF;
        a |= ((src_v[i+1] << 8)&0xFF00);
  UBYTE b = linear2ulaw(a);
  v.push_back(b);
  }
src_v = v;
}
//----------------------------------------------------------------------------
void __fastcall TG729ENC::LinearToG729(TOutPutUdpBlock* opb)
{
USC_PCMStream in;
USC_Bitstream out;
/* Set input stream parameters */
in.nbytes                   = opb->v.size();
in.pBuffer                  = &opb->v[0];
in.bitrate                  = pInfo->params.modes.bitrate;
in.pcmType.bitPerSample     = pInfo->params.pcmType.bitPerSample;
in.pcmType.nChannels        = pInfo->params.pcmType.nChannels;
in.pcmType.sample_frequency = pInfo->params.pcmType.sample_frequency;
/* Set the output buffer */
out.pBuffer = OutputBuffer;
/* Encode a frame */
if(USC_NoError == USC_Gxxx_Fnxs->Encode (hUSCEncoder, &in, &out))
  {
  opb->v.clear();
  for(int i=0;i<lenDst;i++)
      opb->v.push_back(out.pBuffer[i]);
  }
}
//------------------------------------------------------------------------------
void __fastcall TG729DEC::G729_To_Linear(TOutPutUdpBlock* opb)
{
USC_Bitstream in;
USC_PCMStream out;
/* Set input stream parameters */
in.nbytes    = opb->v.size();
in.pBuffer   = &opb->v[0];
in.frametype = 0;
in.bitrate   = 8000;
/* Set the output buffer */
out.pBuffer = OutputBuffer;
if(USC_NoError == USC_Gxxx_Fnxs->Decode (hUSCDecoder, &in, &out))
  {
  opb->v.clear();
  for(int i=0;i<lenDst;i++)
      opb->v.push_back(out.pBuffer[i]);
  }
}
//------------------------------------------------------------------------------
void __fastcall TSendThread::prepare_2833_RtpPacket(TOutPutUdpBlock* work_opb,TOutPutDtmfBlock* opd)
{
vector<UBYTE> v;
int version    = 2;
bool padding   = false;
bool extention = false;
int csic = 0;       //Contributing source identifiers count
setFirstRtpByte(v,version,padding,extention,csic);
setSecondRtpByte(v,opd->marker,opd->payloadtype);
set2833SeqNumber(v);
set2833TimeStamp(v,opd);
setSourceId(v);
int sz = opd->v.size();
for(int i=0;i<sz;i++)
   v.push_back(opd->v[i]);
work_opb->v = v;
}
//------------------------------------------------------------------------------
void __fastcall TSendThread::set2833SeqNumber(vector<UBYTE>& v)
{
v.push_back((currentSeqNumber >> 8 )& 0xFF);
v.push_back(currentSeqNumber & 0xFF);
}
//------------------------------------------------------------------------------
void __fastcall TSendThread::set2833TimeStamp(vector<UBYTE>& v,TOutPutDtmfBlock* opd)
{
if(opd->dtt == START_DTT)
   set_2833_TimeStamp(v,opd);
else
   set_2833_DuplicatedTimeStamp(v,opd);
}
//------------------------------------------------------------------------------
void __fastcall TSendThread::prepare_audio_RtpPacket(TOutPutUdpBlock* opb)
{
vector<UBYTE> v;
int version    = 2;
bool padding   = false;
bool extention = false;
int csic       = 0; //Contributing source identifiers count
bool marker    = false;
setFirstRtpByte(v,version,padding,extention,csic);
setSecondRtpByte(v,marker,remoteCodec);
setSeqNumber(v);
setTimeStamp(v);
setSourceId(v);
int sz = opb->v.size();
for(int i=0;i<sz;i++)
    v.push_back(opb->v[i]);
opb->v = v;
}
//------------------------------------------------------------------------------
void __fastcall TSendThread::prepare_video_RtpPacket(TOutPutUdpBlock* work_opb,TOutPutUdpBlock* opb)
{
try{
vector<UBYTE> v;
int version = 2;
bool padding = false;
bool extention = false;
int csic = 0; //Contributing source identifiers count
bool marker = false;
if(opb->mb_nb)
   marker = true;
setFirstRtpByte(v,version,padding,extention,csic);
setSecondRtpByte(v,marker,remoteCodec);
setSeqNumber(v);
setTimeStamp_Video(v);
setSourceId(v);
switch(remoteCodec){
      case 34:{
              int sz = opb->v.size();
              for(int i=0;i<sz;i++)
                 v.push_back(opb->v[i]);
              break;
              }
      case 115: //H.263+
              {
              int sz = opb->v.size();
              for(int i=0;i<sz;i++)
                 v.push_back(opb->v[i]);
              break;
              }
      default:break;
      }
work_opb->tunnel_name = opb->tunnel_name;
work_opb->v = v;
}//try
catch(Exception& e){exsSstEXCEPTION(*eltp,"__TSendThread::Execute():prepare_video_RtpPacket()",e);}
}
//------------------------------------------------------------------------------
void __fastcall TChannelDispThread::Suspend_Thread()
{
::EnterCriticalSection(&cdt_sc);
  suspend_count++;
::LeaveCriticalSection(&cdt_sc);
Suspend();
}
//-----------------------------------------------------------------------------
void __fastcall TChannelDispThread::Resume_Thread()
{
::EnterCriticalSection(&cdt_sc);
  if(!suspend_count)   //Important for critical Resume in the Timer1Timer()
      Resume();
  while(suspend_count)
       {
       suspend_count--;
       Resume();
       }
::LeaveCriticalSection(&cdt_sc);
}
//-----------------------------------------------------------------------------
void __fastcall TSendThread::Suspend_Thread()
{
::EnterCriticalSection(&st_sc);
  suspend_count++;
::LeaveCriticalSection(&st_sc);
Suspend();
}
//-----------------------------------------------------------------------------
void __fastcall TSendThread::Resume_Thread()
{
::EnterCriticalSection(&st_sc);
  if(!suspend_count)   //Important for critical Resume in the Timer1Timer()
      Resume();
  while(suspend_count)
       {
       suspend_count--;
       Resume();
       }
::LeaveCriticalSection(&st_sc);
}
//-----------------------------------------------------------------------------
void __fastcall TUdpChannelStruct::getAllBusiedChannels(vector<string>& v)
{
::EnterCriticalSection(&udpcs);
  TUdpChannelList::iterator it = ucl.begin();
  while(it != ucl.end())
       {
       TUdpChannel* uc = (*it++).second;
       if(uc)
         {
         string s = "ch_" + inttostr(uc->getChId());
         uc->getMediaPacketType(s);
         vector<int> v_v;
         uc->getAllConnectionsToMe(v_v);
         int sz = v_v.size();
         if(sz)
           {
           s += " CntdToMe ";
           for(int i=0;i < sz;i++)
               s += WS + inttostr(v_v[i]);
           }
         v.push_back(s);
         }
       }
::LeaveCriticalSection(&udpcs);
}
//-----------------------------------------------------------------------------
void __fastcall TDigitTransmitSection::push_dtmf(void* st,TOutPutDtmfBlock* opd)
{
::EnterCriticalSection(&dts_cs);
  TSendThread* ST = (TSendThread*)st;
  opd->incReferenceCount();
  q.push_back(opd);
  if(ST->Suspended)
     ST->Resume_Thread();
::LeaveCriticalSection(&dts_cs);
}
//-----------------------------------------------------------------------------
bool __fastcall TDigitTransmitSection::dtmf_queue_empty()
{
bool rv = false;
::EnterCriticalSection(&dts_cs);
  if(q.empty())
     rv = true;
::LeaveCriticalSection(&dts_cs);
return rv;
}
//-----------------------------------------------------------------------------
TOutPutDtmfBlock* __fastcall TDigitTransmitSection::get_dtmf()
{
TOutPutDtmfBlock* rv = NULL;
::EnterCriticalSection(&dts_cs);
  if(!q.empty())
    {
    rv = q.front();
    if(rv)
      {
      TDateTime dt = dt.CurrentDateTime();
      if((dt - last_dtmf_sent) > last_dtmf_duration)
        {
        last_dtmf_sent = dt;
        last_dtmf_duration = rv->duration;
        q.pop_front();
        }
      else
        rv = NULL;
      }
    }
::LeaveCriticalSection(&dts_cs);
return rv;
}
//-----------------------------------------------------------------------------
bool __fastcall TDigitTransmitSection::digit_transmission(void* st)
{
TSendThread* ST = (TSendThread*)st;
TUdpChannel* uc = (TUdpChannel*)ST->getUc();
bool rv = false;
if(!dtmf_queue_empty())
  {
  ST->clearQueue();
  TOutPutDtmfBlock* opd = get_dtmf();
  if(opd)
    {
    switch(opd->dtt){
          case START_DTT:{
                         TOutPutUdpBlock work_opb;
                         work_opb.subtype = TOutPutDtmf_BLOCKTYPE;
                         if(uc)
                           {
                           work_opb.tunnel_name = "a" + inttostr(uc->getChId());
                           opd->tunnel_name     = work_opb.tunnel_name;
                           }
                         ST->prepare_2833_RtpPacket(&work_opb,opd);
                         work_opb.dtmf_transmission_count = dtmf_start_end_transm_count;
                         opd->dtmf_transmission_count     = dtmf_start_end_transm_count;
                         ST->ENCRYPT(&work_opb);
                         ST->SEND_RTP_PACKET(&work_opb,opd);
                         ST->currentSeqNumber++;
                         break;
                         }
          case CONTINUE_DTT:{
                         TOutPutUdpBlock work_opb;
                         work_opb.subtype = TOutPutDtmf_BLOCKTYPE;
                         if(uc)
                           {
                           work_opb.tunnel_name = "a" + inttostr(uc->getChId());
                           opd->tunnel_name     = work_opb.tunnel_name;
                           }
                         ST->prepare_2833_RtpPacket(&work_opb,opd);
                         ST->ENCRYPT(&work_opb);
                         ST->SEND_RTP_PACKET(&work_opb,opd);
                         ST->currentSeqNumber++;
                         break;
                         }
          case STOP_DTT: {
                         TOutPutUdpBlock work_opb;
                         work_opb.subtype = TOutPutDtmf_BLOCKTYPE;
                         if(uc)
                           {
                           work_opb.tunnel_name = "a" + inttostr(uc->getChId());
                           opd->tunnel_name     = work_opb.tunnel_name;
                           }
                         ST->prepare_2833_RtpPacket(&work_opb,opd);
                         work_opb.dtmf_transmission_count = dtmf_start_end_transm_count;
                         opd->dtmf_transmission_count     = dtmf_start_end_transm_count;
                         ST->ENCRYPT(&work_opb);
                         ST->SEND_RTP_PACKET(&work_opb,opd);
                         ST->currentSeqNumber++;
                         break;
                         }
          case PAUSE_DTT:            //Do not remove
                         break;
          case END_DTT:  last_dtmf_duration   = TDateTime(0,0,0,0);
                         ST->currentTimeStamp = current_2833_timestamp;
                         break;
          }
    opd->decReferenceCount();
    rv = true;
    }
  if(!dtmf_queue_empty())
    {
    ::Sleep(1);
    rv = true;
    }
  }
return rv;
}
//-----------------------------------------------------------------------------
void __fastcall TSendThread::SEND_RTP_PACKET(TOutPutUdpBlock* work_opb,BaseExchangeBlock* bb)
{
TSipSendTunnelThread* ss_tunnelt = Sip->getTSipSendTunnelThread();
if(ss_tunnelt)
  {
  switch(bb->getBlockType()){
                case TOutPutUdpBlock_BLOCKTYPE:{
                     TOutPutUdpBlock* opb = (TOutPutUdpBlock*)bb;
                     opb->v = work_opb->v;
                     SEND_TUNNEL_RTP_PACKET(opb);
                     break;
                     }
                case TOutPutDtmf_BLOCKTYPE:
                     TOutPutDtmfBlock* opd = (TOutPutDtmfBlock*)bb;
                     opd->v = work_opb->v;
                     SEND_TUNNEL_RTP_PACKET(opd);
                     break;
                }
  return;
  }
if(work_opb->subtype == TOutPutDtmf_BLOCKTYPE)
  {
  for(int i=0;i<work_opb->dtmf_transmission_count;i++)
     {
     int bwrote = sendbuf(work_opb);
     if(bwrote == SOCKET_ERROR)
       {
       int err = WSAGetLastError();
       lasterr = "TSendThread::Execute()";
       GetLastSocketError(lasterr,err);
       sendlasterr();
       }
     }
  return;
  }
int bwrote = sendbuf(work_opb);
if(bwrote == SOCKET_ERROR)
  {
  int err = WSAGetLastError();
  lasterr = "TSendThread::Execute()";
  GetLastSocketError(lasterr,err);
  sendlasterr();
  }
}
//-----------------------------------------------------------------------------
void __fastcall TSendThread::SEND_TUNNEL_RTP_PACKET(void* opb)
{
TSipSendTunnelThread* ss_tunnelt = Sip->getTSipSendTunnelThread();
if(ss_tunnelt)
   ss_tunnelt->setQueue(opb);
}
//-----------------------------------------------------------------------------
bool __fastcall TG729ENC::init_encoder(USC_Fxns* usc_fxns, int source_frame_length)
{
USC_Gxxx_Fnxs = usc_fxns;
int infoSize;
/* Get the size of the Gxxx codec status structure */
if(USC_NoError != USC_Gxxx_Fnxs->std.GetInfoSize(&infoSize))
   return false;
pInfo = (USC_CodecInfo *)malloc(infoSize);
/* Get the Gxxx codec status */
if(USC_NoError != USC_Gxxx_Fnxs->std.GetInfo((USC_Handle)NULL, pInfo))
   return false;
/*  creation of an encoder instance */
pInfo->params.direction     = USC_ENCODE; /* Direction: encode */
pInfo->params.modes.vad     = 0; /* Suppress silence compression */
pInfo->params.law           = 0; /* Linear PCM input */
pInfo->params.modes.bitrate = pInfo->pRateTbl[pInfo->nRates-1].bitrate; /*For example, set the highest bitrate*/
/* Determine how many memory blocks the encoder needs */
if(USC_NoError != USC_Gxxx_Fnxs->std.NumAlloc(&pInfo->params,&nbanks))
   return false;
/* allocate memory for the memory bank table */
pBanks = (USC_MemBank*)malloc(sizeof(USC_MemBank)*nbanks);
/* Determine the size of each block */
if(USC_NoError != USC_Gxxx_Fnxs->std.MemAlloc(&pInfo->params, pBanks))
   return false;
/* allocate memory for each block */
for(int i=0; i<nbanks; i++) {
    pBanks[i].pMem = (unsigned char*)malloc(pBanks[i].nbytes);
    }
/* Create the encoder instance */
if(USC_NoError != USC_Gxxx_Fnxs->std.Init(&pInfo->params, pBanks, &hUSCEncoder))
   return false;
/* Get the status of the encoder instance */
if(USC_NoError != USC_Gxxx_Fnxs->std.GetInfo(hUSCEncoder, pInfo))
   return false;
/* Determine the size of the maximum output bitstream */
if(USC_NoError != USC_Gxxx_Fnxs->GetOutStreamSize(&pInfo->params,
   pInfo->params.modes.bitrate, source_frame_length, &lenDst))
   return false;
/* allocate the output bitstream buffer */
OutputBuffer = (char*)malloc(lenDst); //20 bytes  G729
return true;
}
//------------------------------------------------------------------------------
bool __fastcall TG729DEC::init_decoder(USC_Fxns* usc_fxns,int dest_frame_length)
{
USC_Gxxx_Fnxs = usc_fxns;
int infoSize;
/* Get the size of the Gxxx codec status structure */
if(USC_NoError != USC_Gxxx_Fnxs->std.GetInfoSize(&infoSize))
   return false;
pInfo = (USC_CodecInfo *)malloc(infoSize);
/* Get the Gxxx codec status */
if(USC_NoError != USC_Gxxx_Fnxs->std.GetInfo((USC_Handle)NULL, pInfo))
   return false;
/*  creation of an decoder instance */
pInfo->params.direction     = USC_DECODE; /* Direction: encode */
pInfo->params.modes.vad     = 0; /* Suppress silence compression */
pInfo->params.law           = 0; /* Linear PCM input */
pInfo->params.modes.bitrate = pInfo->pRateTbl[pInfo->nRates-1].bitrate; /*For example, set the highest bitrate*/
/* Determine how many memory blocks the decoder needs */
if(USC_NoError != USC_Gxxx_Fnxs->std.NumAlloc(&pInfo->params,&nbanks))
   return false;
/* allocate memory for the memory bank table */
pBanks = (USC_MemBank*)malloc(sizeof(USC_MemBank)*nbanks);
/* Determine the size of each block */
if(USC_NoError != USC_Gxxx_Fnxs->std.MemAlloc(&pInfo->params, pBanks))
   return false;
/* allocate memory for each block */
for(int i=0; i<nbanks; i++) {
        pBanks[i].pMem = (unsigned char*)malloc(pBanks[i].nbytes);
   }
/* Create the decoder instance */
if(USC_NoError != USC_Gxxx_Fnxs->std.Init(&pInfo->params, pBanks, &hUSCDecoder))
  return false;
/* allocate the output bitstream buffer */
lenDst       = dest_frame_length;
OutputBuffer = (char*)malloc(lenDst); //320 bytes  Linear_PCM
return true;
}
//------------------------------------------------------------------------------
TG729ENC* __fastcall TSendThread::CREATE_G729_IPP_ENCODER()
{
if(!G729ENC)
    G729ENC = new TG729ENC;
return G729ENC;
}
//------------------------------------------------------------------------------
TG729DEC* __fastcall TUdpChannel::CREATE_G729_IPP_DECODER()
{
if(!G729DEC)
    G729DEC = new TG729DEC;
return G729DEC;
}
//------------------------------------------------------------------------------
void __fastcall TChannelDispThread::__deleteAllToSend()
{
try{
::EnterCriticalSection(&cs_tosend);
  while(!tosend.empty())
     {
     TOutPutUdpBlock* opb = tosend.front();
     tosend.pop();
     if(opb)
       delete opb;
     }
::LeaveCriticalSection(&cs_tosend);
}//try
catch(Exception& e){exsSstEXCEPTION(*eltp,"__TChannelDispThread::deleteAllToSend()",e);}
}
//------------------------------------------------------------------------------
void __fastcall TChannelDispThread::__deleteAllSent()
{
try{
while(!sent.empty())
     {
     TOutPutUdpBlock* opb = sent.front();
     sent.pop_front();
     if(opb)
       {
       if(opb->getReferenceCount() < 1)
          delete opb;
       else
          opb->set_req_to_delete();
       }
     }
}//try
catch(Exception& e){exsSstEXCEPTION(*eltp,"__TChannelDispThread::deleteAllSent()",e);}
}
//------------------------------------------------------------------------------
void  __fastcall TUdpChannel::Send_VAD_EVENT()
{
if(sendThread)
  {
  TOutPutUdpBlock* opb = new TOutPutUdpBlock;
  if(opb)
    {
    opb->mpt = RTCP_VAD;
    opb->v.push_back(0);
    opb->v.push_back(1);
    sendThread->setQueue(opb);
    }
  }
}
//------------------------------------------------------------------------------
void   __fastcall TUdpChannel::Send_Complex_VAD_EVENT(const string& s)
{
if(sendThread)
  {
  int len = s.length();
  if(len)
    {
    TOutPutUdpBlock* opb = new TOutPutUdpBlock;
    if(opb)
      {
      opb->mpt = RTCP_VAD;
      opb->v.push_back(0);
      opb->v.push_back(2);
      for(int i = 0; i < len; i++)
          opb->v.push_back(s[i]);
      opb->v.push_back(0);  //end of string
      sendThread->setQueue(opb);
      }
    }
  }
}
//-----------------------------------------------------------------------------
__fastcall TG729CODEC::~TG729CODEC()
{
if(pBanks)
  {
  for(int i=0; i<nbanks; i++) {
      free(pBanks[i].pMem);
     }
  free(pBanks);
  }
if(pInfo)
   free(pInfo);
if(OutputBuffer)
   free(OutputBuffer);
}
//-----------------------------------------------------------------------------
string __fastcall TSendThread::getRemoteAddr()
{
string rv;
::EnterCriticalSection(&rhost_cs);
  rv = sRemoteHost;
::LeaveCriticalSection(&rhost_cs);
return rv;
}
//----------------------------------------------------------------------------
void __fastcall TUdpChannelStruct::clear_ucl()
{
::EnterCriticalSection(&udpcs);
  TUdpChannelList::iterator it = ucl.begin();
  while(it != ucl.end())
       {
       TUdpChannel* uc = (*it++).second;
       if(uc)
          delete uc;
       }
::LeaveCriticalSection(&udpcs);
}
//----------------------------------------------------------------------------
TUdpChannel* __fastcall TUdpChannelStruct::get_First_RtpAudioChannel(){
TUdpChannel* uc = NULL;
::EnterCriticalSection(&udpcs);
  TUdpChannelList::iterator it = ucl.begin();
  while(it != ucl.end())
       {
       if((*it).second)
         if((*it).second->getMpt() == RTP_AUDIO_MPT)
           {
           uc = (*it).second;
           break;
           }
       it++;
       }
::LeaveCriticalSection(&udpcs);
return uc;
}
//------------------------------------------------------------------------------
#ifdef SIP_Video
TUdpChannel* __fastcall TUdpChannelStruct::get_First_RtpVideoChannel(){
TUdpChannel* uc = NULL;
::EnterCriticalSection(&udpcs);
  TUdpChannelList::iterator it = ucl.begin();
  while(it != ucl.end())
       {
       if((*it).second)
         if((*it).second->getMpt() == RTP_VIDEO_MPT)
           {
           uc = (*it).second;
           break;
           }
       it++;
       }
::LeaveCriticalSection(&udpcs);
return uc;
}
#endif
//------------------------------------------------------------------------------

