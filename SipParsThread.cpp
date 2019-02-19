//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "WinRDefs.h"
#include "SipClient_Unit.h"
#include "SipParsThread.h"
#include "Sip.h"

#pragma package(smart_init)

extern TMainFormSLS* MainFormSLS;
//------------------------------------------------------------------------------
void __fastcall TSipParsThread::Execute()
{
try{
while(!Terminated){
     TOutPutUdpBlock* opb = (TOutPutUdpBlock*)getQueue();
     if(!opb)
       {
       Suspend_Thread();
       continue;
       }
     if(get_thread_block())
       {
       opb->decReferenceCount();
       continue;
       }
     #ifdef SIP_LogSendPacket
     LOG_RecvdPacket(opb);
     #endif

     #ifdef INTRN_TCP
     if(opb->getIntrnTcp())     //Используется внутренний TCP стек (приходят "склееные" сообщения)
       {
       proc_rcvd_sip_tcp_msg(opb);
       opb->decReferenceCount();
       continue;
       }
     #endif

     ParsingSipMsg(opb);       //Используется UDP транспорт или внешний TCP (ссобщения получаем уже "расцепленными")
     opb->decReferenceCount();
     }
 }//try
catch(Exception& e){exsSstEXCEPTION(*eltp,"__TSipParsThread::Execute",e);}
}
//---------------------------------------------------------------------------
void __fastcall TSipParsThread::proc_rcvd_sip_tcp_msg(TOutPutUdpBlock* opb)
{
if(REQ_TO_CLEAR_INCOMPLETE_SIP_TCP_MSGS)
  {
  incomplete_sip_tcp_msgs.clear();
  REQ_TO_CLEAR_INCOMPLETE_SIP_TCP_MSGS = false;
  }
incomplete_sip_tcp_msgs += opb->s;
queue <TOutPutUdpBlock*> q_tcp;
log_start_stop_splitting(0);
while(split_sip_tcp_msg(q_tcp));
log_start_stop_splitting(1);
TEventLogThread* elt = getLog();
if(elt)
  {
  string s = "TCP msgs rcvd: " + inttostr(q_tcp.size()) + "\n";
  elt->FputEvt(s);
  }
int i = 0;
while(!q_tcp.empty())
     {
     TOutPutUdpBlock* opb_tcp = q_tcp.front();
     q_tcp.pop();
     opb_tcp->FromIP   = opb->FromIP;
     opb_tcp->FromPort = opb->FromPort;
     if(elt)
       {
       string s_i = inttostr(++i);
       string s   = "\n<SPLIT_MSG " + s_i + ">\n" + opb_tcp->s;
       int len = s.length();
       if(s[len - 1] != '\n')
          s += "\n";
       s += "</SPLIT_MSG "  + s_i + ">\n";
       elt->FputEvt(s);
       }
     ParsingSipMsg(opb_tcp);
     delete opb_tcp;
     }
}
//----------------------------------------------------------------------------
bool __fastcall TSipParsThread::split_sip_tcp_msg(queue<TOutPutUdpBlock*>& q_tcp)
{
clear_top_of_msg(); //Clear if begin of msg contain waste.
unsigned len = incomplete_sip_tcp_msgs.length();
if(!len)return false;
unsigned st = incomplete_sip_tcp_msgs.find(sdpboundary);
if(st == -1)
  {
  if(len > 3000)
    {
    incomplete_sip_tcp_msgs.clear();  //мусор
    lasterr = "\nWASTE ONLY RCVD\n";
    sendlasterr();
    }
  else
    {
    lasterr = "\n<INCOMPLETE MSG>\n" + incomplete_sip_tcp_msgs + "\n</INCOMPLETE MSG>\n";
    sendlasterr();
    }
  return false; //only part of msg header received. exit
  }

unsigned start = 0;
unsigned n     = st + 4;
if(n <= len)
   {
   st = incomplete_sip_tcp_msgs.rfind("Content-Length:",st);
   if(st != -1)
     {
     st += 15;
     if(st < n)
       {
       unsigned en = incomplete_sip_tcp_msgs.find(crlf,st);
       if(en != -1)
         {
          st = incomplete_sip_tcp_msgs.find_first_of("0123456789",st);
          if(st < en)
            {
            int cont_len = strtoint(incomplete_sip_tcp_msgs.substr(st,en-st));
            if(!cont_len) //without sdp
              {
              TOutPutUdpBlock* opb = new TOutPutUdpBlock;
              if(opb)
                {
                opb->s = incomplete_sip_tcp_msgs.substr(start,n - start);
                q_tcp.push(opb);
                }
              incomplete_sip_tcp_msgs = incomplete_sip_tcp_msgs.substr(n);
              return true;
              }
            else
              {
              if((n + cont_len) <= len)
                {
                TOutPutUdpBlock* opb = new TOutPutUdpBlock;
                if(opb)
                  {
                  n += cont_len;
                  opb->s = incomplete_sip_tcp_msgs.substr(start,n - start);
                  q_tcp.push(opb);
                  incomplete_sip_tcp_msgs = incomplete_sip_tcp_msgs.substr(n);
                  }
                return true; //следующий проход
                }
              else  //n + cont_len > len -- ждать следующих сообщений, т.к. Sdp не полный
                {
                lasterr = "\n<INCOMPLETE MSG>\n" + incomplete_sip_tcp_msgs + "\n</INCOMPLETE MSG>\n";
                sendlasterr();
                return false;
                }
              }
            }
         }
       }
     }
   }
return false;
}
//---------------------------------------------------------------------------
void __fastcall TSipParsThread::log_start_stop_splitting(int type)
{
TEventLogThread* elt = getLog();
if(elt)
  {
  TDateTime DateTime = DateTime.CurrentDateTime();
  string s;
  exsTime(DateTime,s);
  if(type == 0)
    s = "\n" + s + " split msg start";
  else
    s = "\n" + s + " split msg end\n";
  elt->FputEvt(s);
  }
}
//----------------------------------------------------------------------------
void __fastcall TSipParsThread::clear_top_of_msg()
{
int st = find_top_of_msg();
if(st)
  incomplete_sip_tcp_msgs = incomplete_sip_tcp_msgs.substr(st, incomplete_sip_tcp_msgs.length() - st);
}
//---------------------------------------------------------------------------
int __fastcall TSipParsThread::find_top_of_msg()
{
string SipVers_CRLF = SipVers + crlf;
int en = incomplete_sip_tcp_msgs.find(SipVers_CRLF);
if(en != -1)   //Request
  {
  
  string SipVers_WS = SipVers + WS;
  int st = incomplete_sip_tcp_msgs.find(SipVers_WS);
  if(st != -1)
    if(st < en)
       return st; //Responce в пакете встречается раньше найденного реквеста

  string s = "INVITE" + WS + "sip:";
  st = incomplete_sip_tcp_msgs.find(s);
  if(st != -1)
    if(st < en)
       return st;
  s = "ACK" + WS + "sip:";
  st = incomplete_sip_tcp_msgs.find(s);
  if(st != -1)
    if(st < en)
       return st;
  s = "BYE" + WS + "sip:";
  st = incomplete_sip_tcp_msgs.find(s);
  if(st != -1)
    if(st < en)
       return st;
  s = "CANCEL" + WS + "sip:";
  st = incomplete_sip_tcp_msgs.find(s);
  if(st != -1)
    if(st < en)
       return st;
  s = "SUBSCRIBE" + WS + "sip:";
  st = incomplete_sip_tcp_msgs.find(s);
  if(st != -1)
    if(st < en)
       return st;
  s = "NOTIFY" + WS + "sip:";
  st = incomplete_sip_tcp_msgs.find(s);
  if(st != -1)
    if(st < en)
       return st;
  s = "REFER" + WS + "sip:";
  st = incomplete_sip_tcp_msgs.find(s);
  if(st != -1)
    if(st < en)
       return st;
  s = "MESSAGE" + WS + "sip:";
  st = incomplete_sip_tcp_msgs.find(s);
  if(st != -1)
    if(st < en)
       return st;
  return 0;
  }
else   //ни одного реквеста не найдено, ищем responce
  {
  string SipVers_WS = SipVers + WS;
  int st = incomplete_sip_tcp_msgs.find(SipVers_WS);
  if(st != -1) //Responce
    return st;
  return 0;
  }
}
//---------------------------------------------------------------------------
__fastcall TSipParsThread::~TSipParsThread()
{
#ifdef SIP_Thread_Destruction_Log
TEventLogThread* elt = getLog();
if(elt)elt->FputEvt("\n~TSipParsThread()");
#endif
}
//---------------------------------------------------------------------------
bool __fastcall TSipParsThread::CheckCommand(const string& com,TSipParsBuf* spb)
{
if(spb->s.find(com,0) == 0)
  return true;
return false;
}
//------------------------------------------------------------------------------
TSipParsBuf* __fastcall TSipParsThread::CreateSipParsBuf()
{
TSipParsBuf* spb = new TSipParsBuf();
#ifdef BaseExchBlock_Create
if(spb)
   MainFormSLS->Sip->Log("\nCreated SipParsBuf #" + inttostr(spb->getBlockCount()));
#endif
return spb;
}
//------------------------------------------------------------------------------
void __fastcall TSipParsThread::ParsingSipMsg(TOutPutUdpBlock* opb)
{
try{
TSipParsBuf* spb = CreateSipParsBuf();
if(!spb)return;
spb->s = opb->s;
spb->FromIP   = opb->FromIP;
spb->FromPort = opb->FromPort;
if(CheckCommand("INVITE",spb))
   return PreProcINVITE(spb);
if(CheckCommand("SIP",spb))
   return PreProcResp(spb);
if(CheckCommand("ACK",spb))
   return PreProcACK(spb);
if(CheckCommand("BYE",spb))
   return PreProcBYE(spb);
if(CheckCommand("CANCEL",spb))
   return PreProcCANCEL(spb);
if(CheckCommand("SUBSCRIBE",spb))
   return PreProcSUBSCRIBE(spb);
if(CheckCommand("NOTIFY",spb))
   return PreProcNOTIFY(spb);
if(CheckCommand("REFER",spb))
   return PreProcREFER(spb);

 /*
if(CheckCommand("OPTIONS"))
   return ProcOPTIONS(buf);
*/
if(CheckCommand("MESSAGE",spb))
   return PreProcMESSAGE(spb);
if(CheckCommand("INFO",spb))
   return PreProcINFO(spb);
if(opb->parallel_phone)
  {
  spb->parallel_phone = opb->parallel_phone;
  if(CheckCommand("REGISTER",spb))
     return PreProcREGISTER(spb);
  }
if(spb)
   delete spb;
}//try
catch(Exception& e){exsSstEXCEPTION(*eltp,"__ParsingSipMsg()",e);}
}
//---------------------------------------------------------------------------
void  __fastcall TSipParsThread::getToComponentsFromReqLine(TSipParsBuf* spb,void* p)
{
TRfsd* sipbf = (TRfsd*)p;
int st = spb->ReqStatusLine.find(":");
if(st!=-1)
  {
  int en = spb->ReqStatusLine.find("@",st);
  if(en!=-1)
    {
    st++;
    if(st<en)
      {
      sipbf->ToUserName = spb->ReqStatusLine.substr(st,en-st).c_str();
      st=en;
      en=spb->ReqStatusLine.find(":",st);
      if(en==-1)
        {
        en=spb->ReqStatusLine.find(";",st);
        if(en==-1)
           en=spb->ReqStatusLine.find(WS,st);
        }
      if(en!=-1)
        {
        st++;
        if(st<en)
          sipbf->ToHostName = spb->ReqStatusLine.substr(st,en-st).c_str();
        }
      }
    }
  }
}
//------------------------------------------------------------------------------
int  __fastcall TSipParsThread::getHostName(AnsiString& host,const string& s,int st)
{
int retval=0;
if(!st)
  {
  st = s.find("sip:");
  if(st==-1)return 0;
  st+=4;
  st = s.find_first_of("1234567890",st);
  if(st==-1)return 0;
  int en = s.find(":",st);
  if(en==-1)
    {
    en = s.find(">",st);
    if(en==-1)
       en = s.find(";",st);
    }
  else
    retval=en;
  if(en==-1)return 0;
  int len = en-st;
  if(len<2)return 0;
  host = s.substr(st,len).c_str();
  return retval;
  }
int en = s.find(":",st);
if(en==-1)
   {
   en = s.find(">",st);
   if(en==-1)
      en = s.find(";",st);
   }
else
  retval=en;
if(en==-1)return 0;
int len = en-st;
if(len<2)return 0;
host = s.substr(st+1,len-1).c_str();
return retval;
}
//------------------------------------------------------------------------------
int  __fastcall TSipParsThread::getHostName(string& host,const string& s,int st)
{
if(!st)return 0;
int retval=0;
int en = s.find(":",st);
if(en==-1)
   {
   en = s.find(">",st);
   if(en==-1)
      en = s.find(";",st);
   }
else
  retval=en;
if(en==-1)return 0;
int len = en-st;
if(len<2)return 0;
host = s.substr(st+1,len-1);
return retval;
}
//------------------------------------------------------------------------------

void  __fastcall TSipParsThread::getFromComponents(TSipParsBuf* spb,void* p)
{
TRfsd* sipbf = (TRfsd*)p;
int nextpos = getUserName(sipbf->FromUserName,spb->From);
if(!nextpos)
    nextpos = getAltUserName(sipbf->FromUserName,spb->From);
getHostName(sipbf->FromHostName,spb->From,nextpos);
}
//------------------------------------------------------------------------------
int  __fastcall TSipParsThread::getUserName(AnsiString& name,const string& s)
{
int st = s.find("sip:");
if(st == -1)return 0;
st += 4;
int en = s.find("@",st);
if(en==-1)return 0;
int len=en-st;
if(len<1)return 0;
name = s.substr(st,len).c_str();
return en;
}
//-----------------------------------------------------------------------------
int  __fastcall TSipParsThread::getUserName(string& name,const string& s)
{
int st = s.find("sip:");
if(st == -1)return 0;
st += 4;
int en = s.find("@",st);
if(en==-1)return 0;
int len=en-st;
if(len<1)return 0;
name = s.substr(st,len);
return en;
}
//-----------------------------------------------------------------------------
int   __fastcall TSipParsThread::getAltUserName(AnsiString& name,const string& s)
{
int st = s.find("sip:");
if(st==-1)return 0;
st+=4;
int en = s.find("@",st);
if(en==-1)return 0;
int len=en-st;
if(len<1)return 0;
name = s.substr(st,len).c_str();
return en;
}
//-----------------------------------------------------------------------------
int   __fastcall TSipParsThread::getAltUserName(string& name,const string& s)
{
int st = s.find("sip:");
if(st==-1)return 0;
st+=4;
int en = s.find("@",st);
if(en==-1)return 0;
int len=en-st;
if(len<1)return 0;
name = s.substr(st,len);
return en;
}
//-----------------------------------------------------------------------------
void  __fastcall TSipParsThread::getPort(int& port,const string& s,int st)
{
if(!st)return;
int en = s.find(";",st);
if(en==-1)
   {
   en = s.find(">",st);
   if(en==-1)
     {
     en = s.find_first_of("\r\n",st);
     if(en==-1)
       return;
     }
   }
int len = en-st;
if(len<2)return;
port = atoi(s.substr(st+1,len-1).c_str());
}
//------------------------------------------------------------------------------
void  __fastcall TSipParsThread::getPort(string& dest,const string& s,int st)
{
if(!st)return;
int en = s.find(";",st);
if(en==-1)
   {
   en = s.find(">",st);
   if(en==-1)
     {
     en = s.find_first_of("\r\n",st);
     if(en==-1)
       return;
     }
   }
int len = en-st;
if(len<2)return;
dest = s.substr(st+1,len-1).c_str();
}
//-----------------------------------------------------------------------------
void __fastcall TSipParsThread::getContactComponents(TSipParsBuf* spb,void* RFSD)
{
TRfsd* sipbf = (TRfsd*)RFSD;
int nextpos = getUserName(sipbf->ContactUserName,spb->Contact); //<sip:user@host:port>
if(!nextpos)
   nextpos = getAltUserName(sipbf->ContactUserName,spb->Contact);  // sip:user@host:port
nextpos = getHostName(sipbf->ContactHostName,spb->Contact,nextpos);
getPort(sipbf->ContactPort,spb->Contact,nextpos);
}
//------------------------------------------------------------------------------
void  __fastcall TSipParsThread::getToComponents(TSipParsBuf* spb,void* p)
{
TRfsd* sipbf = (TRfsd*)p;
int nextpos = getUserName(sipbf->ToUserName,spb->To);
if(!nextpos)
    nextpos = getAltUserName(sipbf->ToUserName,spb->To);
getHostName(sipbf->ToHostName,spb->To,nextpos);
}
//------------------------------------------------------------------------------
void  __fastcall TSipParsThread::unpackcomp(TSipParsBuf* spb)
{
if(spb->sipbf)return;
spb->sipbf = new TRfsd;
if(!spb->sipbf)return;
getToComponents(spb,spb->sipbf);
getFromComponents(spb,spb->sipbf);
getContactComponents(spb,spb->sipbf);
}
//------------------------------------------------------------------------------
void __fastcall TSipParsThread::unpackcomp_1(TSipParsBuf* spb)
{
if(!spb->sipbf)
  spb->sipbf = new TRfsd;
if(!spb->sipbf)return;
getContactComponents(spb,spb->sipbf);
}
//------------------------------------------------------------------------------
void  __fastcall TSipParsThread::unpackcomp_2(TSipParsBuf* spb)
{
if(spb->sipbf)return;
spb->sipbf = new TRfsd;
if(!spb->sipbf)return;
getToComponentsFromReqLine(spb,spb->sipbf);
getFromComponents(spb,spb->sipbf);
getContactComponents(spb,spb->sipbf);
}
//------------------------------------------------------------------------------
void  __fastcall TSipParsThread::setQUEUES_INVITE(TSipParsBuf* spb)
{
try{
bool a = false;
if(Sip->uac)
 if(Sip->uac->isLegTrn(spb->call_id.getcallid()))
   {
   Sip->uac->setQueue(spb);
   updateSentQueue(spb, a);
   return;
   }
if(Sip->uas)
   Sip->uas->setQueue(spb);
updateSentQueue(spb, a);
}//try
catch(Exception& e){exsSstEXCEPTION(*eltp,"__setQUEUES_INVITE()",e);}
}
//------------------------------------------------------------------------------
void  __fastcall TSipParsThread::setQUEUES_NOTIFY(TSipParsBuf* spb)
{
try{
bool a = false;
if(Sip->uas)
  if(Sip->uas->isLegTrn(spb->call_id.getcallid()))
    {
    Sip->uas->setQueue(spb);
    updateSentQueue(spb, a);
    return;
    }
if(Sip->uac)
   Sip->uac->setQueue(spb);
updateSentQueue(spb, a);
}//try
catch(Exception& e){exsSstEXCEPTION(*eltp,"__setQUEUES_NOTIFY()",e);}
}
//------------------------------------------------------------------------------
void  __fastcall TSipParsThread::setQUEUES_INFO(TSipParsBuf* spb)
{
try{
bool a = false;
if(Sip->uas)
  if(Sip->uas->isLegTrn(spb->call_id.getcallid()))
    {
    Sip->uas->setQueue(spb);
    updateSentQueue(spb, a);
    return;
    }
if(Sip->uac)
  if(Sip->uac->isLegTrn(spb->call_id.getcallid()))
     Sip->uac->setQueue(spb);
updateSentQueue(spb, a);
}//try
catch(Exception& e){exsSstEXCEPTION(*eltp,"__setQUEUES_INFO()",e);}
}
//------------------------------------------------------------------------------
void  __fastcall TSipParsThread::setQUEUES_MESSAGE(TSipParsBuf* spb)
{
try{
bool a = false;
if(Sip->uas)
   Sip->uas->setQueue(spb);
updateSentQueue(spb, a);
}//try
catch(Exception& e){exsSstEXCEPTION(*eltp,"__setQUEUES_MESSAGE()",e);}
}
//------------------------------------------------------------------------------
void  __fastcall TSipParsThread::setQUEUES_REGISTER(TSipParsBuf* spb)
{
try{
bool a = false;
if(Sip->uas)
   Sip->uas->setQueue(spb);
updateSentQueue(spb, a);
}//try
catch(Exception& e){exsSstEXCEPTION(*eltp,"__setQUEUES_REGISTER()",e);}
}
//------------------------------------------------------------------------------
void  __fastcall TSipParsThread::setQUEUES_SUBSCRIBE(TSipParsBuf* spb)
{
try{
bool a = false;
if(Sip->uas)
   Sip->uas->setQueue(spb);
updateSentQueue(spb, a);
}//try
catch(Exception& e){exsSstEXCEPTION(*eltp,"__setQUEUES_SUBSCRIBE()",e);}
}
//-------------------- ----------------------------------------------------------
void  __fastcall TSipParsThread::setQUEUES_REFER(TSipParsBuf* spb)
{
try{
bool a = false;
spb->to_tag   = get_tag(spb->To);
spb->from_tag = get_tag(spb->From);
if(!spb->to_tag.empty()) //in-dialog
  {
  if(Sip->uas)
    {
    TLegTrn* Lt = Sip->uas->getLegTrn(spb->call_id.getcallid());
    if(Lt)
      {
      Lt->BLOCK_LEG_TRN();
      if(Lt->mytag == spb->to_tag)
        if(Lt->remotetag == spb->from_tag)
          {
          Sip->uas->setQueue(spb);
          updateSentQueue(spb, a);
          Lt->UN_BLOCK_LEG_TRN();
          return;
          }
      if(Lt->mytag == spb->from_tag)
        if(Lt->remotetag == spb->to_tag)
          {
          Sip->uas->setQueue(spb);
          updateSentQueue(spb, a);
          Lt->UN_BLOCK_LEG_TRN();
          return;
          }
      Lt->UN_BLOCK_LEG_TRN();
      }
    }
  if(Sip->uac)
    {
    TLegTrn* Lt = Sip->uac->getLegTrn(spb->call_id.getcallid());
    if(Lt)
      {
      Lt->BLOCK_LEG_TRN();
      if(Lt->mytag == spb->to_tag)
        if(Lt->remotetag == spb->from_tag)
          {
          Sip->uac->setQueue(spb);
          updateSentQueue(spb, a);
          Lt->UN_BLOCK_LEG_TRN();
          return;
          }
      if(Lt->mytag == spb->from_tag)
        if(Lt->remotetag == spb->to_tag)
          {
          Sip->uac->setQueue(spb);
          updateSentQueue(spb, a);
          Lt->UN_BLOCK_LEG_TRN();
          return;
          }
      Lt->UN_BLOCK_LEG_TRN();
      }
    }
  }
}//try
catch(Exception& e){exsSstEXCEPTION(*eltp,"__setQUEUES_REFER()",e);}
}
//------------------------------------------------------------------------------
void __fastcall TSipParsThread::setQUEUES(TSipParsBuf* spb)
{
bool a = false;
if(Sip->uac)
 if(Sip->uac->isLegTrn(spb->call_id.getcallid()))
   {
   Sip->uac->setQueue(spb);
   updateSentQueue(spb, a);
   return;
   }
if(Sip->uas)
  if(Sip->uas->isLegTrn(spb->call_id.getcallid()))
    Sip->uas->setQueue(spb);
updateSentQueue(spb, a);
}
//------------------------------------------------------------------------------
bool  __fastcall TSipParsThread::setQUEUES_PPH(TSipParsBuf* spb)
{
bool a = false;
if(MainFormSLS->PPS->uac_pph)
   if(MainFormSLS->PPS->uac_pph->isLegTrn(spb->call_id.getcallid()))
     {
     MainFormSLS->PPS->uac_pph->setQueue(spb);
     updateSentQueue(spb, a);
     return true;
     }
if(MainFormSLS->PPS->uas_pph)
  if(MainFormSLS->PPS->uas_pph->isLegTrn(spb->call_id.getcallid()))
    {
    MainFormSLS->PPS->uas_pph->setQueue(spb);
    updateSentQueue(spb, a);
    return true;
    }
return false;    
}
//-----------------------------------------------------------------------------
void __fastcall TSipParsThread::PreProcINVITE(TSipParsBuf* spb)
{
try{
spb->sps = SPS_INVITE_RCVD;
unpack_h(spb);
unpackcomp_2(spb);
if(__thread_type == 1)   //TSipParsThread for PPH (Parallel_phone)
  {
  bool a = false;
  if(MainFormSLS->PPS)
     MainFormSLS->PPS->uas_pph->setQueue(spb);
  updateSentQueue(spb, a);
  }
else
  setQUEUES_INVITE(spb);
}//try
catch(Exception& e){exsSstEXCEPTION(*eltp,"__PreProcINVITE()",e);}
}
//---------------------------------------------------------------------------
void __fastcall TSipParsThread::PreProcResp(TSipParsBuf* spb)
{
spb->sps = SPS_RESP_RCVD;
unpack_h(spb);
if(__thread_type == 1)
   if(setQUEUES_PPH(spb))
      return;
setQUEUES(spb);
}
//---------------------------------------------------------------------------
void __fastcall TSipParsThread::PreProcACK(TSipParsBuf* spb)
{
spb->sps = SPS_ACK_RCVD;
unpack_h(spb);
setQUEUES(spb);}
//------------------------------------------------------------------------------
void __fastcall TSipParsThread::PreProcBYE(TSipParsBuf* spb)
{
spb->sps = spb->sps = SPS_BYE_RCVD;
unpack_h(spb);
if(__thread_type == 1)
   if(setQUEUES_PPH(spb))
      return;
setQUEUES(spb);
}
//------------------------------------------------------------------------------
void __fastcall TSipParsThread::PreProcCANCEL(TSipParsBuf* spb)
{
spb->sps = SPS_CANCEL_RCVD;
unpack_h(spb);
unpackcomp_1(spb);
setQUEUES(spb);
}
//------------------------------------------------------------------------------
void  __fastcall TSipParsThread::PreProcNOTIFY(TSipParsBuf* spb)
{
spb->sps = SPS_NOTIFY_RCVD;
if(!unpack_h(spb))
  {
  delete spb;
  return;
  }
setQUEUES_NOTIFY(spb);
}
//------------------------------------------------------------------------------
void  __fastcall TSipParsThread::PreProcSUBSCRIBE(TSipParsBuf* spb)
{
spb->sps = SPS_SUBSCRIBE_RCVD;
unpack_h(spb);
setQUEUES_SUBSCRIBE(spb);
}
//------------------------------------------------------------------------------
void  __fastcall TSipParsThread::PreProcREFER(TSipParsBuf* spb)
{
spb->sps = SPS_REFER_RCVD;
unpack_h(spb);
setQUEUES_REFER(spb);
}
//------------------------------------------------------------------------------
void  __fastcall TSipParsThread::PreProcMESSAGE(TSipParsBuf* spb)
{
spb->sps = SPS_MESSAGE_RCVD;
unpack_h(spb);
unpackcomp(spb);
setQUEUES_MESSAGE(spb);
}
//------------------------------------------------------------------------------
void  __fastcall TSipParsThread::PreProcINFO(TSipParsBuf* spb)
{
spb->sps = SPS_INFO_RCVD;
unpack_h(spb);
setQUEUES_INFO(spb);
}
///-----------------------------------------------------------------------------
void  __fastcall TSipParsThread::PreProcREGISTER(TSipParsBuf* spb)
{
spb->sps = SPS_REGISTER_RCVD;
unpack_h(spb);
setQUEUES_REGISTER(spb);
}
//-----------------------------------------------------------------------------
void  __fastcall TSipParsThread::getReqStatusLine(TSipParsBuf* spb)
{
int en = spb->s.find(crlf,0);
if(en==-1)return;
spb->ReqStatusLine = spb->s.substr(0,en);
}
//------------------------------------------------------------------------------
void __fastcall TSipParsThread::getheader(string& dest,const string& name,TSipParsBuf* spb,int enl)
{
int st = spb->s.find(name);
if(st==-1)return;
int en = spb->s.find(crlf,st);
if(en==-1)return;
if(st<en)
  dest=spb->s.substr(st,en-st+enl);
}
//------------------------------------------------------------------------------
void  __fastcall TSipParsThread::getcallid(TSipParsBuf* spb)
{
int st = spb->CallID.find(":");
if(st==-1)return;
int en = spb->CallID.find(crlf);
if(en==-1)return;
if(spb->CallID[++st]==' ')
   ++st;
int len = en-st;
if(len<1)return;
spb->call_id.setprimcallid(spb->CallID.substr(st,len));
}
//------------------------------------------------------------------------------
void __fastcall TSipParsThread::getsdp(TSipParsBuf* spb)
{
int st = spb->s.find(sdpboundary);
if(st==-1)return;
int en = spb->s.length();
st+=4;
if(st<en)
  spb->sdp.Sdp = spb->s.substr(st,en-st);
}
//------------------------------------------------------------------------------
__fastcall TSdp::TSdp()
{
t38  = NULL;
tftp = NULL;
}
//------------------------------------------------------------------------------
__fastcall TSdp::~TSdp()
{
if(t38)
   delete t38;
if(tftp)
   delete tftp;
}
//------------------------------------------------------------------------------
void  __fastcall TSipParsThread::getStatus(TSipParsBuf* spb)
{
string s = spb->ReqStatusLine;
int st = s.find(WS);
if(st==-1)return;
st = s.find_first_of("123456",st);
if(st==-1)return;
int en = s.find(WS,st);
if(en==-1)return;
int len = en-st;
if(len < 3)return;
spb->sStatus = s.substr(st,len);
spb->iStatus = atoi(spb->sStatus.c_str());
}
//------------------------------------------------------------------------------
void  __fastcall TSipParsThread::getouttag(TSipParsBuf* spb)
{
int st = spb->To.find(">");
if(st==-1)return;
st = spb->To.find("tag=",st);
if(st==-1)return;
st+=4;
int en = spb->To.find(crlf,st);
if(en==-1)return;
int len = en-st;
if(len < 1)return;
spb->totag = spb->To.substr(st,len);
}
//------------------------------------------------------------------------------
void  __fastcall TSipParsThread::getRespHeaders(TSipParsBuf* spb)
{
getReqStatusLine(spb);
getStatus(spb);
switch(spb->iStatus){
 case 100:
 getheader(spb->To,"To:",spb);
 getheader(spb->CallID,"Call-ID:",spb);
 getouttag(spb);
 getcallid(spb);
 break;
 case 180:
 getheader(spb->From,"From:",spb);
 getheader(spb->To,"To:",spb);
 spb->ViaSt.CollectHeaders(spb->s,const_Via);
 spb->RrSt.CollectHeaders(spb->s,const_RecordRoute);
 getheader(spb->CallID,"Call-ID:",spb);
 getheader(spb->CSeq,"CSeq:",spb);
 getheader(spb->Contact,"Contact:",spb);
 getheader(spb->Server,"Server:",spb);
 getheader(spb->Allow,"Allow:",spb);
 getheader(spb->ContentLength,"Content-Length:",spb);
 getouttag(spb);
 getcallid(spb);
 break;
 case 183:
 getheader(spb->From,"From:",spb);
 getheader(spb->To,"To:",spb);
 spb->ViaSt.CollectHeaders(spb->s,const_Via);
 spb->RrSt.CollectHeaders(spb->s,const_RecordRoute);
 getheader(spb->CallID,"Call-ID:",spb);
 getheader(spb->CSeq,"CSeq:",spb);
 getheader(spb->Contact,"Contact:",spb);
 getheader(spb->Server,"Server:",spb);
 getheader(spb->Expires,"Expires:",spb);
 getheader(spb->Allow,"Allow:",spb);
 getheader(spb->Supported,"Supported:",spb);
 getheader(spb->ContentLength,"Content-Length:",spb);
 getheader(spb->ContentType,"Content-Type:",spb);
 getouttag(spb);
 getsdp(spb);
 getcallid(spb);
 break;
 case 200:
 getheader(spb->From,"From:",spb);
 getheader(spb->To,"To:",spb);
 spb->ViaSt.CollectHeaders(spb->s,const_Via);
 spb->RrSt.CollectHeaders(spb->s,const_RecordRoute);
 getheader(spb->CallID,"Call-ID:",spb);
 getheader(spb->CSeq,"CSeq:",spb);
 getheader(spb->Contact,"Contact:",spb);
 getheader(spb->Server,"Server:",spb);
 getheader(spb->Expires,"Expires:",spb);
 getheader(spb->Allow,"Allow:",spb);
 getheader(spb->Supported,"Supported:",spb);
 getheader(spb->ContentLength,"Content-Length:",spb);
 getheader(spb->ContentType,"Content-Type:",spb);
 getsdp(spb);
 getcallid(spb);
 break;
 case 202:
 getheader(spb->From,"From:",spb);
 getheader(spb->To,"To:",spb);
 spb->ViaSt.CollectHeaders(spb->s,const_Via);
 getheader(spb->Contact,"Contact:",spb);
 getheader(spb->CallID,"Call-ID:",spb);
 getheader(spb->CSeq,"CSeq:",spb);
 getheader(spb->Expires,"Expires:",spb);
 getcallid(spb); 
 break;
 case 301:
 spb->ViaSt.CollectHeaders(spb->s,const_Via);
 getheader(spb->From,"From:",spb);
 getheader(spb->To,"To:",spb);
 getheader(spb->CallID,"Call-ID:",spb);
 getheader(spb->CSeq,"CSeq:",spb);
 getheader(spb->Warning,"Warning:",spb);
 getcallid(spb);
 break;
 case 302:
 spb->ViaSt.CollectHeaders(spb->s,const_Via);
 getheader(spb->From,"From:",spb);
 getheader(spb->To,"To:",spb);
 getheader(spb->CallID,"Call-ID:",spb);
 getheader(spb->CSeq,"CSeq:",spb);
 getheader(spb->Warning,"Warning:",spb);
 getcallid(spb);
 break;
 case 401: //Unauthorized
 getheader(spb->From,"From:",spb);
 getheader(spb->To,"To:",spb);
 spb->ViaSt.CollectHeaders(spb->s,const_Via);
 getheader(spb->CallID,"Call-ID:",spb);
 getheader(spb->WWWAuthenticate,"WWW-Authenticate:",spb);
 getheader(spb->CSeq,"CSeq:",spb);
 getcallid(spb);
 break;
 case 402: //Payment Required
 case 403: //Forbidden
 case 404: //Not Found
 case 405: //Method Not Allowed
 case 406: //Not Acceptable
 spb->ViaSt.CollectHeaders(spb->s,const_Via);
 getheader(spb->From,"From:",spb);
 getheader(spb->To,"To:",spb);
 getheader(spb->CallID,"Call-ID:",spb);
 getheader(spb->CSeq,"CSeq:",spb);
 getheader(spb->Warning,"Warning:",spb);
 getcallid(spb);
 break;
 case 407: //Proxy authentication required
 getheader(spb->From,"From:",spb);
 getheader(spb->To,"To:",spb);
 spb->ViaSt.CollectHeaders(spb->s,const_Via);
 getheader(spb->CallID,"Call-ID:",spb);
 getheader(spb->ProxyAuthenticate,"Proxy-Authenticate:",spb);
 getheader(spb->CSeq,"CSeq:",spb);
 getcallid(spb);
 break;
 case 408: //Request timeout
 spb->ViaSt.CollectHeaders(spb->s,const_Via);
 getheader(spb->From,"From:",spb);
 getheader(spb->To,"To:",spb);
 getheader(spb->CallID,"Call-ID:",spb);
 getheader(spb->CSeq,"CSeq:",spb);
 getheader(spb->Warning,"Warning:",spb);
 getcallid(spb);
 break;
 case 410: //Gone
 spb->ViaSt.CollectHeaders(spb->s,const_Via);
 getheader(spb->From,"From:",spb);
 getheader(spb->To,"To:",spb);
 getheader(spb->CallID,"Call-ID:",spb);
 getheader(spb->CSeq,"CSeq:",spb);
 getcallid(spb);
 break;
 case 415: //Unsupported Media Type
 case 480: //Temporarily Unavailable
 case 481: //Call/Transaction Does Not Exist
 case 482: //Merged Request
 case 484: //Address incomplete
 case 603: //Decline
 spb->ViaSt.CollectHeaders(spb->s,const_Via);
 getheader(spb->From,"From:",spb);
 getheader(spb->To,"To:",spb);
 getheader(spb->CallID,"Call-ID:",spb);
 getheader(spb->CSeq,"CSeq:",spb);
 getcallid(spb);
 break;
 case 486: //Busy Here
 spb->ViaSt.CollectHeaders(spb->s,const_Via);
 getheader(spb->From,"From:",spb);
 getheader(spb->To,"To:",spb);
 getheader(spb->CallID,"Call-ID:",spb);
 getheader(spb->CSeq,"CSeq:",spb);
 getheader(spb->Warning,"Warning:",spb);
 getcallid(spb);
 break;
 case 487:
 spb->ViaSt.CollectHeaders(spb->s,const_Via);
 getheader(spb->From,"From:",spb);
 getheader(spb->To,"To:",spb);
 getheader(spb->CallID,"Call-ID:",spb);
 getheader(spb->CSeq,"CSeq:",spb);
 getcallid(spb);
 break;
 case 488: //Not acceptable Here
 spb->ViaSt.CollectHeaders(spb->s,const_Via);
 getheader(spb->From,"From:",spb);
 getheader(spb->To,"To:",spb);
 getheader(spb->CallID,"Call-ID:",spb);
 getheader(spb->CSeq,"CSeq:",spb);
 getcallid(spb);
 break;
 case 500:  //Server internal error
 spb->ViaSt.CollectHeaders(spb->s,const_Via);
 getheader(spb->From,"From:",spb);
 getheader(spb->To,"To:",spb);
 getheader(spb->CallID,"Call-ID:",spb);
 getheader(spb->CSeq,"CSeq:",spb);
 getcallid(spb);
 break;
 case 501:  //Not implemented
 spb->ViaSt.CollectHeaders(spb->s,const_Via);
 getheader(spb->From,"From:",spb);
 getheader(spb->To,"To:",spb);
 getheader(spb->CallID,"Call-ID:",spb);
 getheader(spb->CSeq,"CSeq:",spb);
 getcallid(spb);
 break;
 case 503:
 spb->ViaSt.CollectHeaders(spb->s,const_Via);
 getheader(spb->From,"From:",spb);
 getheader(spb->To,"To:",spb);
 getheader(spb->CallID,"Call-ID:",spb);
 getheader(spb->CSeq,"CSeq:",spb);
 getheader(spb->Warning,"Warning:",spb);
 getcallid(spb);
 break;
 }
}
//------------------------------------------------------------------------------
bool __fastcall TSipParsThread::unpack_h(TSipParsBuf* spb)
{
bool rv = true;
switch(spb->sps){
 case SPS_INVITE_RCVD:
 getReqStatusLine(spb);
 getheader(spb->From,"From:",spb);
 getheader(spb->To,"To:",spb,0);
 getheader(spb->CallID,"Call-ID:",spb);
 getheader(spb->CSeq,"CSeq:",spb);
 getheader(spb->Contact,"Contact:",spb);
 getheader(spb->UserAgent,"User-Agent:",spb);
 getheader(spb->Expires,"Expires:",spb);
 getheader(spb->Allow,"Allow:",spb);
 getheader(spb->Supported,"Supported:",spb);
 getheader(spb->ContentLength,"Content-Length:",spb);
 getheader(spb->ContentType,"Content-Type:",spb);
 getheader(spb->ReferredBy,"Referred-By:",spb);
 getheader(spb->Replaces,"Replaces:",spb);
 spb->ViaSt.CollectHeaders(spb->s,const_Via);
 getcallid(spb);
 getsdp(spb);
 if(spb->CSeq.rfind("INVITE") == -1)
   {
   lasterr = "\n RCVD BAD SIP MESSAGE: INVITE -> " + spb->CSeq + "\n";
   sendlasterr();
   rv = false;
   }
 break;
 case SPS_ACK_RCVD:
 getReqStatusLine(spb);
 getheader(spb->From,"From:",spb);
 getheader(spb->To,"To:",spb);
 getheader(spb->CallID,"Call-ID:",spb);
 getheader(spb->CSeq,"CSeq:",spb);
 getheader(spb->UserAgent,"User-Agent:",spb);
 getheader(spb->ContentLength,"Content-Length:",spb);
 spb->ViaSt.CollectHeaders(spb->s,const_Via);
 getcallid(spb);
 if(spb->CSeq.rfind("ACK") == -1)
   {
   lasterr = "\n RCVD BAD SIP MESSAGE: ACK -> " + spb->CSeq + "\n";
   sendlasterr();
   rv = false;
   }
 break;
 case SPS_BYE_RCVD:
 getReqStatusLine(spb);
 getheader(spb->From,"From:",spb);
 getheader(spb->To,"To:",spb);
 getheader(spb->CallID,"Call-ID:",spb);
 getheader(spb->CSeq,"CSeq:",spb);
 getheader(spb->UserAgent,"User-Agent:",spb);
 getheader(spb->ContentLength,"Content-Length:",spb);
 spb->ViaSt.CollectHeaders(spb->s,const_Via);
 spb->RrSt.CollectHeaders(spb->s,const_RecordRoute);
 getcallid(spb);
 if(spb->CSeq.rfind("BYE") == -1)
   {
   lasterr = "\n RCVD BAD SIP MESSAGE: BYE -> " + spb->CSeq + "\n";
   sendlasterr();
   rv = false;
   }
 break;
 case SPS_CANCEL_RCVD:
 getReqStatusLine(spb);
 getheader(spb->From,"From:",spb);
 getheader(spb->To,"To:",spb,0);
 getheader(spb->Contact,"Contact:",spb);
 getheader(spb->CallID,"Call-ID:",spb);
 getheader(spb->CSeq,"CSeq:",spb);
 getheader(spb->UserAgent,"User-Agent:",spb);
 getheader(spb->ContentLength,"Content-Length:",spb);
 spb->ViaSt.CollectHeaders(spb->s,const_Via);
 getcallid(spb);
 if(spb->CSeq.rfind("CANCEL") == -1)
   {
   lasterr = "\n RCVD BAD SIP MESSAGE: CANCEL -> " + spb->CSeq + "\n";
   sendlasterr();
   rv = false;
   }
 break;
 case SPS_RESP_RCVD:
 getRespHeaders(spb);
 break;
 case SPS_MESSAGE_RCVD:
 getReqStatusLine(spb);
 getheader(spb->From,"From:",spb);
 getheader(spb->To,"To:",spb);       //To: get with crlf (not getheader(spb->To,"To:",spb,0);
 getheader(spb->CallID,"Call-ID:",spb);
 getheader(spb->CSeq,"CSeq:",spb);
 getheader(spb->Contact,"Contact:",spb);
 getheader(spb->UserAgent,"User-Agent:",spb);
 getheader(spb->Expires,"Expires:",spb);
 getheader(spb->Allow,"Allow:",spb);
 getheader(spb->Supported,"Supported:",spb);
 getheader(spb->ContentLength,"Content-Length:",spb);
 getheader(spb->ContentType,"Content-Type:",spb);
 spb->ViaSt.CollectHeaders(spb->s,const_Via);
 getcallid(spb);
 getsdp(spb);
 if(spb->CSeq.rfind("MESSAGE") == -1)
   {
   lasterr = "\n RCVD BAD SIP MESSAGE: MESSAGE -> " + spb->CSeq + "\n";
   sendlasterr();
   rv = false;
   }
 break;
 case SPS_SUBSCRIBE_RCVD:
 getReqStatusLine(spb);
 getheader(spb->From,"From:",spb);
 getheader(spb->To,"To:",spb);
 getheader(spb->CallID,"Call-ID:",spb);
 getheader(spb->CSeq,"CSeq:",spb);
 getheader(spb->Contact,"Contact:",spb);
 getheader(spb->Accept,"Accept:",spb);
 getheader(spb->Allow,"Allow:",spb);
 getheader(spb->Event,"Event:",spb);
 getheader(spb->Expires,"Expires:",spb);
 getheader(spb->UserAgent,"User-Agent:",spb);
 spb->ViaSt.CollectHeaders(spb->s,const_Via);
 getcallid(spb);
 if(spb->CSeq.rfind("SUBSCRIBE") == -1)
   {
   lasterr = "\n RCVD BAD SIP MESSAGE: SUBSCRIBE -> " + spb->CSeq + "\n";
   sendlasterr();
   rv = false;
   }
 break;
 case SPS_NOTIFY_RCVD:
 getReqStatusLine(spb);
 getheader(spb->From,"From:",spb);
 getheader(spb->To,"To:",spb);
 getheader(spb->CallID,"Call-ID:",spb);
 getheader(spb->CSeq,"CSeq:",spb);
 getheader(spb->Contact,"Contact:",spb);
 getheader(spb->MaxForwards,"Max-Forwards:",spb);
 getheader(spb->SubscriptionState,"Subscription-State:",spb);
 getheader(spb->Event,"Event:",spb);
 getheader(spb->UserAgent,"User-Agent:",spb);
 getheader(spb->ContentLength,"Content-Length:",spb);
 getheader(spb->ContentType,"Content-Type:",spb);
 spb->ViaSt.CollectHeaders(spb->s,const_Via);
 getcallid(spb);
 getsdp(spb);
 if(spb->CSeq.rfind("NOTIFY") == -1)
   {
   lasterr = "\n RCVD BAD SIP MESSAGE: NOTIFY -> " + spb->CSeq + "\n";
   sendlasterr();
   rv = false;
   }
 break;
 case SPS_REFER_RCVD:
 getReqStatusLine(spb);
 getheader(spb->From,"From:",spb);
 getheader(spb->To,"To:",spb);
 getheader(spb->CallID,"Call-ID:",spb);
 getheader(spb->CSeq,"CSeq:",spb);
 getheader(spb->Contact,"Contact:",spb);
 getheader(spb->MaxForwards,"Max-Forwards:",spb);
 getheader(spb->UserAgent,"User-Agent:",spb);
 getheader(spb->Allow,"Allow:",spb);
 getheader(spb->ReferTo,"Refer-To:",spb);
 getheader(spb->ReferredBy,"Referred-By:",spb);
 getheader(spb->ContentLength,"Content-Length:",spb);
 spb->ViaSt.CollectHeaders(spb->s,const_Via);
 getcallid(spb);
 getsdp(spb);
 if(spb->CSeq.rfind("REFER") == -1)
   {
   lasterr = "\n RCVD BAD SIP MESSAGE: REFER -> " + spb->CSeq + "\n";
   sendlasterr();
   rv = false;
   }
 break;
 case SPS_INFO_RCVD:
 getReqStatusLine(spb);
 getheader(spb->From,"From:",spb);
 getheader(spb->To,"To:",spb,2);
 getheader(spb->CallID,"Call-ID:",spb);
 getheader(spb->CSeq,"CSeq:",spb);
 getheader(spb->Contact,"Contact:",spb);
 getheader(spb->MaxForwards,"Max-Forwards:",spb);
 getheader(spb->UserAgent,"User-Agent:",spb);
 getheader(spb->Allow,"Allow:",spb);
 getheader(spb->Supported,"Supported:",spb);
 getheader(spb->ContentLength,"Content-Length:",spb);
 getheader(spb->ContentType,"Content-Type:",spb);
 spb->ViaSt.CollectHeaders(spb->s,const_Via);
 getcallid(spb);
 getsdp(spb);
 if(spb->CSeq.rfind("INFO") == -1)
   {
   lasterr = "\n RCVD BAD SIP MESSAGE: INFO -> " + spb->CSeq + "\n";
   sendlasterr();
   rv = false;
   }
 break;
 case SPS_OPTIONS_RCVD:
 getReqStatusLine(spb);
 getheader(spb->From,"From:",spb);
 getheader(spb->To,"To:",spb,0);
 getheader(spb->CallID,"Call-ID:",spb);
 getheader(spb->CSeq,"CSeq:",spb);
 getheader(spb->Contact,"Contact:",spb);
 getheader(spb->UserAgent,"User-Agent:",spb);
 getheader(spb->Allow,"Allow:",spb);
 if(spb->CSeq.rfind("OPTIONS") == -1)
   {
   lasterr = "\n RCVD BAD SIP MESSAGE: OPTIONS -> " + spb->CSeq + "\n";
   sendlasterr();
   rv = false;
   }
 break;
 case SPS_REGISTER_RCVD:
 /*
 #ifdef Sst_Rtp_Proxy
 ConvStrIPtoUIP(spb);
 #elif defined Sst_Sip_IP_Behind_FW
 ConvStrIPtoUIP(spb);
 #endif
 */
 getReqStatusLine(spb);
 getheader(spb->From,"From:",spb);
 getheader(spb->To,"To:",spb,0);
 getheader(spb->CallID,"Call-ID:",spb);
 getheader(spb->CSeq,"CSeq:",spb);
 getheader(spb->Contact,"Contact:",spb);
 getheader(spb->MaxForwards,"Max-Forwards:",spb);
// getheader(spb->RcvdUserAgent,"User-Agent:",spb);
 getheader(spb->Expires,"Expires:",spb);
// getheader(spb->Authorization,"Authorization:",spb);
 spb->ViaSt.CollectHeaders(spb->s,const_Via);
 getcallid(spb);
 if(spb->CSeq.rfind("REGISTER") == -1)
   {
   lasterr = "\n RCVD BAD SIP MESSAGE: REGISTER -> " + spb->CSeq + "\n";
   sendlasterr();
   rv = false;
   }
 break;
 }
return rv;
}
//------------------------------------------------------------------------------

 /*

 __fastcall TSipParsBuf::~TSipParsBuf()
{
if(sipbf)
  delete (TRfsd*)sipbf;
#ifdef Sst_Rtp_Proxy
if(ReplaceLanToWanCall200OKRcvd)
  delete ReplaceLanToWanCall200OKRcvd;
#endif
}
*/

//------------------------------------------------------------------------------
__fastcall TSipParsBuf::TSipParsBuf():BaseExchangeBlock(TSipParsBuf_BLOCKTYPE)
{
iStatus = 0;
sipbf = NULL;
}
//------------------------------------------------------------------------------
__fastcall TSipParsBuf::~TSipParsBuf()
{
}
//------------------------------------------------------------------------------
void __fastcall TBaseHeaderListStruct::CollectHeaders(const string& s,const string& patt)
{
int st=0;
while(find_subsequent_via_header(s,st,patt)!=-1);
}
//------------------------------------------------------------------------------
int __fastcall TBaseHeaderListStruct::find_subsequent_via_header(const string& s,int& st,const string& patt)
{
st = s.find(patt,st);
if(st==-1)return -1;
int en = s.find(crlf,st);
if(en==-1)return -1;
ins(s.substr(st,en-st+2));  //2 - length of crlf
st=en;
return en;
}
//------------------------------------------------------------------------------
void __fastcall TBaseHeaderListStruct::ins(const string& s)
{
lst.insert(map< int, string, less<int>, allocator<int> >::value_type(++ind,s));
}
//------------------------------------------------------------------------------
string __fastcall TCallID::getcallid()
{
switch(type){
      case CallID_Type_Prim:
           return callid;
      case CallID_Type_Constr:
           return callidcmpx;
      }
return strempty;
}
//------------------------------------------------------------------------------
string __fastcall TCallID::getprimcallid()
{
return callid;
}
//------------------------------------------------------------------------------
void __fastcall TCallID::setprimcallid(const string& s)
{
callid = s;
}
//------------------------------------------------------------------------------
void __fastcall TSipParsThread::LOG_RecvdPacket(TOutPutUdpBlock* opb)
{
TEventLogThread* elt = getLog();
if(elt)
  {
  string str;
  exsTime( opb->dt,str);
  str = "\n" + str + // + " sck " + inttostr(sck);
        " PcktLen " + inttostr(opb->datasize) + " " +
        " RcvFrom " + opb->FromIP + ":" + inttostr(opb->FromPort) + "\n";
  elt->FputEvt(str + opb->s);
 }
}
//------------------------------------------------------------------------------
void __fastcall TSdp::prepSdpStr()
{
Sdp = "v=" + SdpVersion + crlf +
"o=" + Owner_UserName + SessionID + SessionVersion  + Owner_NeworkType  + Owner_AddressType + Owner_Address + crlf + //Owner
"s=" + SessionName + crlf +
"c=" + Connection_NetworkType + Connection_AddressType + common_connection_addr + crlf + //Connection
"t=" + Session_StartTime + Session_StopTime  + crlf;
if(tftp) //File Transfer
  {
  Sdp += tftp->message    + crlf +
         tftp->session_id + crlf +
         tftp->file_name  + crlf +
         tftp->file_size  + crlf;
  }
else
  Sdp += "m=" + audio.media_type + inttostr(audio.localrtpport) + WS + audio.media_protocol;
prep_final_media(audio.codecs, audio.crypto_keys, audio.rtp_attr_list);
#ifdef SIP_Video
if(!video.codecs.empty())
  {
  Sdp += "m=" + video.media_type + inttostr(video.localrtpport) + WS + video.media_protocol;
  prep_final_media(video.codecs, video.crypto_keys, video.rtp_attr_list);
  }
#endif  
}
//------------------------------------------------------------------------------
void __fastcall TSdp::addVideoToSdpStr()
{
if(!video.codecs.empty())
  {
  Sdp += "m=" + video.media_type + inttostr(video.localrtpport) + WS + video.media_protocol;
  prep_final_media(video.codecs, video.crypto_keys, video.rtp_attr_list);
  }
}
//------------------------------------------------------------------------------
void __fastcall TSdp::prep_final_media(vector<int>& codec_list, vector<string>& crypto_keys, vector<string>& attr_list)
{
if(!codec_list.empty())
  {
  vector<int>::iterator it = codec_list.begin();
  while(it != codec_list.end())
       Sdp += WS + inttostr(*it++);
  Sdp+=crlf;
  if(!crypto_keys.empty())
    {
    vector<string>::iterator it = crypto_keys.begin();
    while(it != crypto_keys.end())
          Sdp += (*it++);
    }
  vector<string>::iterator it_s = attr_list.begin();
  while(it_s != attr_list.end())
       Sdp += (*it_s++);
  }
}
//------------------------------------------------------------------------------
void __fastcall TBaseHeaderListStruct::InsertHeaders(string& s)
{
map < int, string, less<int>, allocator<int> >::iterator it = lst.begin();
while(it!=lst.end())
      s+=(*it++).second;
}
//------------------------------------------------------------------------------

