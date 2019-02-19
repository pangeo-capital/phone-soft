//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "WinRDefs.h"
#include "ParallelPhone_Unit.h"
#include "SipClient_Unit.h"
//#include "Iphlpapi.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//#pragma comment(lib, "IPHLPAPI.lib")

TParallelPhone *ParallelPhone;
//---------------------------------------------------------------------------
__fastcall TParallelPhone::TParallelPhone(TComponent* Owner)
        : TForm(Owner)
{
BorderStyle = bsDialog;
Color  = clWhite;
Top    = MainFormSLS->Top  + 80;
Left   = MainFormSLS->Left + 10;
Width  = 400;
Height = 300;

Edit1->Ctl3D      = false;
Edit1->Font->Size = 10;
Edit1->Width      = Width/3;
Edit1->Left       = Width/2 - Edit1->Width/2;
Edit1->Text       = IntToStr(MainFormSLS->PPS->getPort());  

AnsiString S = "Порт";
Label1->Caption = S;
int w = Label1->Canvas->TextWidth(S);
Label1->Left = Edit1->Left - w - 20;
Label1->Top  = Edit1->Top  + 5;

Edit2->Ctl3D      = false;
Edit2->Font->Size = 10;
Edit2->Width      = Edit1->Width;      
Edit2->Left       = Edit1->Left;
Edit2->Top        = Edit1->Top + Edit1->Height + Edit1->Height/2;

S = "Имя";
Label2->Caption = S;
w = Label2->Canvas->TextWidth(S);
Label2->Left = Edit2->Left - w - 20;
Label2->Top  = Edit2->Top  + 5;

Button1->Caption = "Сохранить";
Button1->Top     = Edit2->Top + Edit2->Height + Edit2->Height/2;
Button1->Left    = Edit2->Left + Edit2->Width + (Width - (Edit2->Left + Edit2->Width))/2 - Button1->Width/2;

Height = Button1->Top + Button1->Height + 40;

ReadPPSToForm();
}
//---------------------------------------------------------------------------
__fastcall TParallelPhoneStruct::~TParallelPhoneStruct()
{
setActive(false);
if(srt_pph)
   srt_pph->set_thread_block();
if(uac_pph)
   uac_pph->set_thread_block();
if(uas_pph)
   uas_pph->set_thread_block();
if(spt_pph)
   spt_pph->set_thread_block();
if(sst_pph)
   sst_pph->set_thread_block();

if(SCK != INVALID_SOCKET)
  {
  ::closesocket(SCK);
  SCK = INVALID_SOCKET;
  }
if(srt_pph)
  {
  TSipRecvThread_PPH* SRT = srt_pph;
  srt_pph = NULL;
  SRT->setsck(INVALID_SOCKET);
  SRT->Terminate();
  SRT->Resume_Thread();
  SRT->WaitFor();
  delete SRT;
  }
if(spt_pph)
  {
  TSipParsThread* SPT = spt_pph;
  spt_pph = NULL;
  SPT->Terminate();
  SPT->Resume_Thread();
  SPT->WaitFor();
  delete SPT;
  }
if(uac_pph)
  {
  TSipUacThread* UAC = uac_pph;
  uac_pph = NULL;
  UAC->Terminate();
  UAC->Resume_Thread();
  UAC->WaitFor();
  delete UAC;
  }
if(uas_pph)
  {
  TSipUasThread* UAS = uas_pph;
  uas_pph = NULL;
  UAS->Terminate();
  UAS->Resume_Thread();
  UAS->WaitFor();
  delete UAS;
  }
if(sst_pph)
  {
  TSipSendThread* SST = sst_pph;
  sst_pph = NULL;
  SST->Terminate();
  SST->Resume_Thread();
  SST->WaitFor();
  delete SST;
  }
::DeleteCriticalSection(&pps_cs);  
}
//---------------------------------------------------------------------------
void __fastcall TParallelPhone::FormCloseQuery(TObject *Sender,
      bool &CanClose)
{
MainFormSLS->ParallelPhoneWin = NULL;
}
//---------------------------------------------------------------------------
void __fastcall TParallelPhone::FormClose(TObject *Sender,
      TCloseAction &Action)
{
Action = caFree;
}
//---------------------------------------------------------------------------
void __fastcall TParallelPhone::ReadPPSToForm()
{
if(!MainFormSLS->PPS->getActive())
  {
  CheckBox1->Checked = false;
  CheckBox1->Caption = "Активировать";
  Caption = "Параллельный телефон (Сервис не активен)";
  }
else
  {
  CheckBox1->Checked = true;
  AnsiString S;
  CheckBox1->Caption = S;
  if(!MainFormSLS->PPS->getRegistered())
     Caption = "Параллельный телефон (Не зарегистрирован)";
  else
     Caption = "Параллельный телефон (Подключен)";
  }
Edit1->Text = IntToStr(MainFormSLS->PPS->getPort());
Edit2->Text = MainFormSLS->PPS->getName().c_str();
}
//---------------------------------------------------------------------------
void __fastcall TParallelPhone::ReadFormToPPS(TParallelPhoneStruct& pps)
{
if(CheckBox1->Checked)
   pps.setActive(true);

AnsiString S = Edit1->Text;
pps.setPort(StrToIntDef(S,5060));

S = Edit2->Text;
pps.setName(S.c_str());
}
//---------------------------------------------------------------------------
bool __fastcall TParallelPhone::Compare(TParallelPhoneStruct* old_pps, TParallelPhoneStruct* new_pps)
{
if(old_pps->getActive() != new_pps->getActive())
   return true;
if(old_pps->getPort() != new_pps->getPort())
   return true;
if(old_pps->getName() != new_pps->getName())
   return true;
return false;
}
//---------------------------------------------------------------------------
void __fastcall TParallelPhoneStruct::copyData(TParallelPhoneStruct& new_pps)
{
Active  = new_pps.getActive();
UasPort = new_pps.getPort();
setName(new_pps.getName());
}
//----------------------------------------------------------------------------
void __fastcall TParallelPhoneStruct::writeRegistry()
{
TRegistry& regKey = *new TRegistry();
regKey.RootKey = ROOT_KEY;
bool keyGood = regKey.OpenKey(key_name.c_str(),false);
if(keyGood)
  {
  keyGood = regKey.OpenKey(parallel_phone.c_str(),false);
  if(!keyGood)
     keyGood = regKey.OpenKey(parallel_phone.c_str(),true);
  if(keyGood)
    {
    if(MainFormSLS->PPS->getActive())
       regKey.WriteString(pph_active.c_str(),"1");
    else
       regKey.WriteString(pph_active.c_str(),"0");
    regKey.WriteString(pph_port.c_str(),IntToStr(UasPort));
    regKey.WriteString(pph_name.c_str(),getName().c_str());
    }
  regKey.CloseKey();
  }
delete &regKey;
}
//----------------------------------------------------------------------------
void __fastcall TParallelPhoneStruct::readRegistry()
{
TRegistry& regKey = *new TRegistry();
regKey.RootKey = ROOT_KEY;
bool keyGood = regKey.OpenKey(key_name.c_str(),false);
if(keyGood)
  {
  keyGood = regKey.OpenKey(parallel_phone.c_str(),false);
  if(keyGood)
    {
    AnsiString S = regKey.ReadString(pph_active.c_str());
    if(!S.IsEmpty())
      {
      int a = StrToIntDef(S,0);
      if(a)
         Active = true;
      else
         Active = false; 
      }
    S = regKey.ReadString(pph_port.c_str());
    if(!S.IsEmpty())
        UasPort = StrToIntDef(S,5060);
    S = regKey.ReadString(pph_name.c_str());
    setName(S.c_str());
    }
  regKey.CloseKey();
  }
delete &regKey;
}
//-----------------------------------------------------------------------------
void __fastcall TParallelPhone::Button1Click(TObject *Sender)
{
TParallelPhoneStruct new_pps;
ReadFormToPPS(new_pps);
if(Compare(MainFormSLS->PPS,&new_pps)){
  MainFormSLS->PPS->copyData(new_pps);
  MainFormSLS->PPS->writeRegistry();
  }
Close();
}
//---------------------------------------------------------------------------
void __fastcall TParallelPhone::Get_PPH_CONTROL_MSG(TMessage &Message)
{
switch(Message.WParam){
       case WM_APP_MSG_WPARAM__CLOSE_WINDOW:
            Close();
            break;
      }
}
//----------------------------------------------------------------------------
SOCKET __fastcall TParallelPhoneStruct::CreateSock()
{
return exsCreateUDPSocket_ADDR_ANY(UasPort);
}
//----------------------------------------------------------------------------
//-- used in main thread only ------------------------------------------------
//----------------------------------------------------------------------------
void __fastcall TParallelPhoneStruct::send_200OK_OnRegister_To_PPH(TSipParsBuf* spb)
{
try{
if(Sip->uas)
  {
  prepare_Initial_200OK_OnRegister_To_PPH(spb);
  Sip->uas->setQueue(spb);
  }
}//try
catch(Exception& e){exsSstEXCEPTION(*eltp,"__send_200OK_OnRegister_To_PPH()",e);}
}
//-----------------------------------------------------------------------------
void __fastcall TParallelPhoneStruct::prepare_Initial_200OK_OnRegister_To_PPH(TSipParsBuf* spb)
{
spb->sps = SPS_REGISTER200OK_REQ;
spb->ToIP   = spb->FromIP;
spb->ToPort = spb->FromPort;
if(spb->To.find("tag=") == -1)
  {
  Sip->generateToTag(spb);
  spb->To += ";tag=" + spb->totag + crlf;
  }
string selected_local_ip = select_local_ip_addr(regUAddr);
int st = spb->Contact.find("@");
if(st != -1)
  {
  spb->Contact.resize(st);
  spb->Contact += "@" + selected_local_ip + ":" + inttostr(UasPort) + ">" + crlf;
  }
spb->s.clear();
spb->s = "SIP/2.0 200 OK" + crlf;
spb->ViaSt.InsertHeaders(spb->s); spb->s +=
spb->To         +
spb->From       +
spb->CallID     +
spb->CSeq       +
spb->Contact    +
spb->Expires    +
"Content-Length: 0" + sdpboundary;
}
//-----------------------------------------------------------------------------
bool __fastcall TParallelPhoneStruct::check_register_interval()
{
bool rv = true;
if(next_reg.CurrentDateTime() > next_reg)
  {
  rv = false;
  Registered = false;
  }
return rv;
}
//-----------------------------------------------------------------------------
void __fastcall TParallelPhoneStruct::prepareRequestLine_INVITE_PPH(TOutputSipBuf* ospb)
{
ospb->requestline = "sip:" + getName() + "@" + getRegAddr();
ospb->RequestUri = ospb->requestline;  //Необходимо, если потребуется переадресация из разговора
ospb->requestline += WS + SipVers + crlf;
}
//---------------------------------------------------------------------------
void __fastcall TParallelPhoneStruct::prepareContact_PPH(BaseExchangeBlock* bb, const string& selected_local_ip)
{
bb->Contact = "Contact: <sip:" + Sip->Account.get_user_name() + "@" + selected_local_ip + ":" + inttostr(UasPort) + ">" + crlf;
}
//-----------------------------------------------------------------------------
void __fastcall TParallelPhoneStruct::prepareInitialTo_PPH(TOutputSipBuf* ospb)
{
ospb->To = "To:" + WS + "<sip:" + getName() + "@" + getRegAddr() + ">" + crlf;
}
//-----------------------------------------------------------------------------
void __fastcall TParallelPhoneStruct::prepareFrom_PPH(TOutputSipBuf* ospb, const string& user_name, const string& selected_local_ip)
{
ospb->from = "From:" + WS + "<sip:" + user_name + "@" + selected_local_ip + ">;tag=" + ospb->FromTag + crlf;
}
//-----------------------------------------------------------------------------
void __fastcall TParallelPhoneStruct::prepareCallID_INVITE_PPH(TOutputSipBuf* ospb, const string& selected_local_ip)
{
ospb->callid = "Call-ID:" + WS + ospb->CallID + "@" + selected_local_ip + crlf;
ospb->CallID = ospb->CallID + "@" + selected_local_ip;
}
//------------------------------------------------------------------------------
void __fastcall TParallelPhoneStruct::prepare_Sdp_Initial_PPH(TSdp* sdp, const string& selected_local_ip)
{
sdp->SdpVersion             = "0";
sdp->Owner_UserName         = "sip" + WS;
sdp->SessionID              = "0"   + WS;
sdp->SessionVersion         = "0"   + WS;
sdp->Owner_NeworkType       = "IN"  + WS;
sdp->Owner_AddressType      = "IP4" + WS;
sdp->SessionName            = "SIP_Call";
sdp->Connection_NetworkType = "IN"  + WS;
sdp->Connection_AddressType = "IP4" + WS;
sdp->Session_StartTime      = "0" + WS;
sdp->Session_StopTime       = "0";
sdp->common_connection_addr = selected_local_ip;
sdp->Owner_Address          = selected_local_ip;
}
//------------------------------------------------------------------------------
//--- Выполняется только в MainFormSLS основном потоке !!! ---------------------
//--- осуществляет ИСХ вызов к параллельному телефону при основном ВХОДЯЩЕМ
//------------------------------------------------------------------------------
void __fastcall TParallelPhoneStruct::Check_IN_Call_To_ParallelPhone(TSipParsBuf* spb, TForm1* form)
{
if(Active)
  if(Registered)
   if(check_register_interval()) //If interval expires Registered discarded
     if(Sip->uac)
       {
       TOutputSipBuf* ospb = new TOutputSipBuf;
       if(ospb)
         {
         ospb->parallel_phone             = true;
         ospb->primary_call_direction_pph = 0;  //Incoming Call
         ospb->parallel_phone_call_id     = spb->call_id.getcallid();
         ospb->setsls(SPS_INVITE_REQ);
         string selected_local_ip = select_local_ip_addr(regUAddr);
         Sip->generateFromTag(ospb);
         Sip->generateCallID(ospb);
         ospb->ToIP   = getRegAddr();
         ospb->ToPort = regPort;
         prepareRequestLine_INVITE_PPH(ospb);
         Sip->prepareViaHeader(ospb);
         Sip->prepareMaxForwards(70,ospb);
         prepareContact_PPH(ospb, selected_local_ip);
         prepareInitialTo_PPH(ospb);
         prepareFrom_PPH(ospb, Sip->Account.get_user_name(), selected_local_ip);
         prepareCallID_INVITE_PPH(ospb, selected_local_ip);
         Sip->prepareCSeq(1,"INVITE",ospb);
         Sip->prepareAllow(ospb);
         Sip->prepareContentType(ospb,"application/sdp");
         Sip->prepareUserAgent(ospb);
         prepare_Sdp_Initial_PPH(&ospb->sdp, selected_local_ip);
         ospb->sdp.Sdp = spb->sdp.Sdp; //Копируется полностью принятый SDP для последующей модификации в TSipUacThread
         if(form)
           {
           form->connected_to_pph = true;
           form->callid_pph       = ospb->CallID;
           }
         Sip->uac->setQueue(ospb);
         Sip->updateSentQueue_1(ospb);
         }
       }
}
//-----------------------------------------------------------------------------
//--- осуществляет ИСХ вызов к параллельному телефону при основном ИСХОДЯЩЕМ
//-----------------------------------------------------------------------------
void __fastcall TParallelPhoneStruct::Check_OUT_Call_To_ParallelPhone(TSipParsBuf* spb, TMediaSession* ms)
{
if(Registered)
 if(check_register_interval()) //If interval expires Registered discarded
   if(uac_pph)
     {
     TOutputSipBuf* ospb = new TOutputSipBuf;
     if(ospb)
       {
       ospb->parallel_phone             = true;
       ospb->primary_call_direction_pph = 1;  //Outgoing Call
       ospb->parallel_phone_call_id     = spb->call_id.getcallid();
       ospb->setsls(SPS_INVITE_REQ);
       string selected_local_ip = select_local_ip_addr(regUAddr);
       Sip->generateFromTag(ospb);
       Sip->generateCallID(ospb);
       ospb->ToIP   = getRegAddr();
       ospb->ToPort = regPort;
       prepareRequestLine_INVITE_PPH(ospb);
       Sip->prepareViaHeader(ospb);
       Sip->prepareMaxForwards(70,ospb);
       prepareContact_PPH(ospb, selected_local_ip);
       prepareInitialTo_PPH(ospb);
       prepareFrom_PPH(ospb, Sip->Account.get_user_name(), selected_local_ip);
       prepareCallID_INVITE_PPH(ospb, selected_local_ip);
       Sip->prepareCSeq(1,"INVITE",ospb);
       Sip->prepareAllow(ospb);
       Sip->prepareContentType(ospb,"application/sdp");
       Sip->prepareUserAgent(ospb);
       prepare_Sdp_Initial_PPH(&ospb->sdp, selected_local_ip);
       ospb->sdp.Sdp = spb->sdp.Sdp; //Копируется полностью принятый SDP для последующей модификации в TSipUacThread
       if(ms)
         {
         ms->set_pph_session_created(true);
         int tag = ms->getCallTag();
         for(int i = 0; i < MainFormSLS->ControlCount; i++)
            {
            TCall_Panel* Panel = dynamic_cast<TCall_Panel*>(MainFormSLS->Controls[i]);
            if(Panel)
              {
               if(Panel->Tag == tag)
                 {
                  Panel->connected_to_pph = true;
                  Panel->callid_pph       = ospb->CallID;
                  break;
                 }
              }
            }
         }
       uac_pph->setQueue(ospb);
       Sip->updateSentQueue_1(ospb);
       }
     }
}
//------------------------------------------------------------------------------
