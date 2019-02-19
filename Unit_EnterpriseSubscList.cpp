//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Unit_EnterpriseSubscList.h"
#include "SipClient_Unit.h"
#include <Filectrl.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"


#define RESPONCE_RECORD_COUNT  10

using namespace std;

const double k_width = 1.5;
const btn_img_widh   = 42;

TEnterpriseSubscList *EnterpriseSubscList;
//---------------------------------------------------------------------------
__fastcall TEnterpriseSubscList::TEnterpriseSubscList(TComponent* Owner)
        : TForm(Owner)
{
::InitializeCriticalSection(&osl_cs);
::InitializeCriticalSection(&tcp);
SDB_RTT = NULL;
SDB_STT = NULL;
SDB_PT  = NULL;
DBI_CONTACT_LIST_SIZE = 0;
Abonents              = NULL;
DBIContacts.set_contact_list_size_pointer(&DBI_CONTACT_LIST_SIZE);
DBIContacts.set_hwnd(Handle);
send_seq_number = 0;
Width  = MainFormSLS->Panel1->Width + 50; //Screen->Width/2;
Height = Screen->Height/2; // + 50;
//Caption = "Общий список абонентов";//"Список абонентов предприятия";
//LEFT_PANEL->Align = alLeft; //alClient; // С TSpliter LEFT_PANEL->Align необходимо назначить alLeft;
//LEFT_PANEL->Width = Width/2; Do Not Delete. May be used with Splitter

LEFT_PANEL->Width = Width;
LEFT_PANEL->Color = clWhite;

/*  Do Not Delete
Splitter = new TSplitter(this);
Splitter->Parent = this;
Splitter->Left   = LEFT_PANEL->Left + LEFT_PANEL->Width;
Splitter->Align  = alLeft;
*/

/*
RIGHT_PANEL->Left = Splitter->Left + Splitter->Width;
RIGHT_PANEL->Align = alClient;
 */

RIGHT_PANEL->Width   = 0;
RIGHT_PANEL->Visible = false;

Panel1->Color        =   clWhite; //clBtnFace; //
Panel1->Left         =   0;
Panel1->Width        =   Width;
Panel1->Height       =   100;
Panel1->Top          = __set_Panel1_Top();

//Panel_Find->Color    =   clWhite;
Panel_Find->Left     =   0;
Panel_Find->Top      =   0;
Panel_Find->Width    =   Width;
Panel_Find->Height   = __set_Panel_Find_Height();
AnsiString Empty_S;
Panel_Find->Caption  =   Empty_S;
Panel_Find->Visible  =   false;

Edit_Find->Ctl3D     =   false;
Edit_Find->Width     =   Width/2;
Edit_Find->Top       =   8;
Edit_Find->Left      =   10;

Image_Find_21_21->Top  = Edit_Find->Top  - 2;
Image_Find_21_21->Left = Edit_Find->Left + Edit_Find->Width + 10;

Image_Close_Find->Top  = Image_Find_21_21->Top -  1;
Image_Close_Find->Left = Panel_Find->Width     - 51;

DrawGrid_Find->BorderStyle      = bsNone;
DrawGrid_Find->Color            = clWhite;
DrawGrid_Find->DefaultRowHeight = 60;
DrawGrid_Find->DefaultDrawing   = false;
DrawGrid_Find->ScrollBars       = ssVertical;
DrawGrid_Find->FixedCols        = 0;
DrawGrid_Find->FixedRows        = 0;
DrawGrid_Find->ColCount         = 1;
DrawGrid_Find->RowCount         = 1;
DrawGrid_Find->Width            = Panel_Find->Width  - 15;
DrawGrid_Find->ColWidths[0]     = DrawGrid_Find->Width;
DrawGrid_Find->Options          = DrawGrid_Find->Options >> goRangeSelect >> goHorzLine;

//DrawGrid_Find->GridLineWidth = 0;

AudioCall_Img->Left  = 10; //AudioCallPanel2->Left;
VideoCall_Img->Left  = AudioCall_Img->Left  + k_width*AudioCall_Img->Width;
Conference_Img->Left = VideoCall_Img->Left  + k_width*VideoCall_Img->Width;
AddContact_Img->Left = Conference_Img->Left + k_width*Conference_Img->Width;
Find_Img->Left       = 14;


AudioCall_Img->Top   = Panel1->Height - AudioCall_Img->Height - 20;   //Panel1->Height - AudioCallPanel2->Height - 20;      //                  AudioCallPanel2->Top;
VideoCall_Img->Top   = AudioCall_Img->Top;
Conference_Img->Top  = AudioCall_Img->Top;
AddContact_Img->Top  = AudioCall_Img->Top;
Find_Img->Top        = AudioCall_Img->Top + 4;

AddContact_Img->Hint = "Добавить в список личных контактов";
Conference_Img->Hint = "Добавить в конференцию";
VideoCall_Img->Hint  = "Видео вызов";
AudioCall_Img->Hint  = "Аудио вызов";
Find_Img->Hint       = "Поиск";


AddContact_Img->ShowHint = true;
Conference_Img->ShowHint = true;
VideoCall_Img->ShowHint  = true;
AudioCall_Img->ShowHint  = true;
Find_Img->ShowHint       = true;

init_audio_call_btn();
init_video_call_btn();
init_conference_call_btn();
init_add_contact_btn();

AnsiString S;
Label1->Caption     = S;
Label1->Font->Size  = 11;
//Label1->Font->Name  = get_font_name_Arial();
Label1->Font->Color = (TColor)get_turquoise_color();
Label1->Font->Style = Label1->Font->Style << fsBold;
Label1->Top         = 8; //10;//(Panel1->Height - AudioCallPanel2->Top)/2 - Label1->Height;///2;
Label1->Left        = AudioCallPanel2->Left;

DrawGrid1->ColWidths[0] = DrawGrid1->Width;
DrawGrid1->RowCount     = 1;
DrawGrid1->ScrollBars   = ssVertical;

/*
DrawGrid2->ColWidths[0] = DrawGrid2->Width;
DrawGrid2->RowCount     = 1;
DrawGrid2->ColCount     = 1;
DrawGrid2->ScrollBars   = ssVertical;
DrawGrid2->FixedRows    = 0;
DrawGrid2->FixedCols    = 0;
*/

set_audio_call_btn_state(BtnState_INACTIVE);
set_video_call_btn_state(BtnState_INACTIVE);
set_conference_call_btn_state(BtnState_INACTIVE);
set_add_contact_btn_state(BtnState_INACTIVE);

/*
Width = AddContactPanel2->Left + AddContactPanel2->Width + 30;
min_width = Width;

AudioCall_Img->Left  = AudioCallPanel2->Left;
//VideoCall_Img->Left  = VideoCallPanel2->Left;
VideoCall_Img->Left  = AudioCall_Img->Left + 2*AudioCall_Img->Width;
//Conference_Img->Left = ConferenceCallPanel2->Left;
Conference_Img->Left = VideoCall_Img->Left + 2*VideoCall_Img->Width;
//AddContact_Img->Left = AddContactPanel2->Left;
AddContact_Img->Left = Conference_Img->Left + 2*Conference_Img->Width;

AudioCall_Img->Top   = AudioCallPanel2->Top;
VideoCall_Img->Top   = AudioCall_Img->Top;
Conference_Img->Top  = AudioCall_Img->Top;
AddContact_Img->Top  = AudioCall_Img->Top;
  */

AudioCall_Img->Visible  = true;
VideoCall_Img->Visible  = true;
Conference_Img->Visible = true;
AddContact_Img->Visible = true;

AudioCallPanel2->Visible      = false;
//VideoCallPanel2->Visible      = false;
//ConferenceCallPanel2->Visible = false;
//AddContactPanel2->Visible     = false;

MarginLine->Left   = 10;
MarginLine->Top    = 25; //20; //10;
MarginLine->Height = 1;   //Заполнение происходит в void __fastcall TEnterpriseSubscList::Panel1Resize(TObject *Sender)

/*
MarginLine->Width = Width - 40;

int w = MarginLine->Width; int h = 1;
TRBitMap rbmp(w, h, 0xC0C0C0); //0x00FFF2EA;
rbmp.prepare_line_img();
MainFormSLS->draw_margin_line(MarginLine->Canvas, 0, 1, rbmp);
  */

if(AudioCall_Img->Visible)
  min_width = 10 * btn_img_widh; //8 * btn_img_widh;
else
  {
//  Width = AddContactPanel2->Left + AddContactPanel2->Width + 30;
  min_width = Width;
  }

if(MainFormSLS->TIME_STMP_REQUEST)
  {
   MainFormSLS->TIME_STMP_REQUEST = false;
   Create_DBChannel(false,false,true); //Request ContactList TimeStmp
  }
}
//---------------------------------------------------------------------------
void __fastcall TEnterpriseSubscList::FormShow(TObject *Sender)
{
LOG_Window_Actions("DbInterface window open");
SCI.clear();
Left = MainFormSLS->Left + MainFormSLS->Panel2->Left + MainFormSLS->Panel2->Width  + 50;   //10;
Top  = MainFormSLS->Top  + MainFormSLS->Panel1->Top  + MainFormSLS->Panel1->Height + 100;  //50;
AnsiString S;
Label1->Caption = S;

set_audio_call_btn_state(BtnState_INACTIVE);
set_video_call_btn_state(BtnState_INACTIVE);
set_conference_call_btn_state(BtnState_INACTIVE);
set_add_contact_btn_state(BtnState_INACTIVE);

DBIContacts.clear_contact_list();
DrawGrid1->RowCount = 1;
Create_DBChannel(true,false,false);
}
//---------------------------------------------------------------------------
void __fastcall TEnterpriseSubscList::Create_DBChannel(bool OpenWindow, bool ReqStartData, bool ReqTimeStmp)
{
try{
if(!SDB_PT)
  {
  SDB_PT  = new TSubcrDBParsThread(true,&MainFormSLS->ofs->elt, MainFormSLS->Sip, this);
  SDB_RTT = new TSubcrDBRecvTcpThread(true, MainFormSLS->Sip->SubscDB.IPAddr, MainFormSLS->Sip->SubscDB.Port, &MainFormSLS->ofs->elt, MainFormSLS->Sip, this);
  if(SDB_RTT)
    {
    if(OpenWindow)
       SDB_RTT->set_open_window(true);
    if(ReqStartData)
       SDB_RTT->set_req_subsc_start_data(true);
    if(ReqTimeStmp)
       SDB_RTT->set_req_contact_list_time_stmp(true);
    SDB_RTT->Resume_Thread();
    }
  SDB_STT = new TSubcrDBSendTcpThread(true, &MainFormSLS->ofs->elt, MainFormSLS->Sip);
  }
else
  {
  if(OpenWindow)
    {
    TTransactionData data;
    GET_DIVISION_LIST(data,10);
    }
  if(ReqStartData)
     GET_SUBSC_START_DATA(MainFormSLS->Sip->Account.get_user_name());
  if(ReqTimeStmp)
     REQ_CONTACT_LIST_TIME_STMP(MainFormSLS->Sip->Account.get_user_name());
  }
}//try
catch(Exception& e){exsSstEXCEPTION(MainFormSLS->ofs->elt,"__TEnterpriseSubscList::Create_DBChannel()",e);}
}
//-----------------------------------------------------------------------------
void __fastcall TEnterpriseSubscList::Delete_DBChannel()
{
::EnterCriticalSection(&tcp);
  if(SDB_RTT)
    {
    TSubcrDBRecvTcpThread* sdb_rtt = SDB_RTT;
    SDB_RTT = NULL;
    sdb_rtt->set_close_req(true);  //!!! Protection from DeadLock on Delete EnterpriseSubscList Window (::EnterCriticalsection(&tcp)) in call GET_DIVISION_LIST() in the TSubcrDBRecvTcpThread::Receive()
    sdb_rtt->Terminate();
    if(sdb_rtt->get_sck() != INVALID_SOCKET)
      {
      ::closesocket(sdb_rtt->get_sck());
      sdb_rtt->set_sck(INVALID_SOCKET);
      sdb_rtt->set_connected(false);
      //sdb_rtt->set_wait_connect(false);
      }
    sdb_rtt->WaitFor();
    delete sdb_rtt;
    }
  if(SDB_STT)
    {
    TSubcrDBSendTcpThread* sdb_stt = SDB_STT;
    SDB_STT = NULL;
    sdb_stt->Terminate();
    sdb_stt->Resume_Thread();
    sdb_stt->WaitFor();
    delete sdb_stt;
    }
::LeaveCriticalSection(&tcp);
if(SDB_PT)
  {
  TSubcrDBParsThread* sdb_pt = SDB_PT;
  SDB_PT = NULL;
  sdb_pt->Terminate();
  sdb_pt->Resume_Thread();
  sdb_pt->WaitFor();
  delete sdb_pt;
  }
}
//-----------------------------------------------------------------------------
void __fastcall TSubcrDBRecvTcpThread::Execute()
{
sck = exsCreateTCPSocket_ADDR_ANY();
while(!Terminated)
     {
     Connect();
     Receive();
     }
}
//--------------------------------------------------------------------------
void __fastcall TSubcrDBRecvTcpThread::Connect()
{
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
     int  bcnnct = connect(sck,(struct sockaddr *)&dest, sizeof(dest));
     if(bcnnct == SOCKET_ERROR)
       {
       CheckConnError();
       sck = exsCreateTCPSocket_ADDR_ANY();  //::closesocket(sck) inside CheckConnError()
       continue;
       }
     conn_count = 0;
     connected  = true;
     LOG_Connection();
     break;
     }
}
//----------------------------------------------------------------------------
void __fastcall TSubcrDBRecvTcpThread::Receive()
{
try{
if(!__close_req) //!!! Protection from DeadLock on Delete EnterpriseSubscList Window (::EnterCriticalsection(&tcp))
  {
  if(_req_subsc_start_data)
    {
   _req_subsc_start_data = false;
    Esl->GET_SUBSC_START_DATA(MainFormSLS->Sip->Account.get_user_name());
    }
  if(_req_contact_list_time_stmp)
    {
   _req_contact_list_time_stmp = false;
    Esl->REQ_CONTACT_LIST_TIME_STMP(MainFormSLS->Sip->Account.get_user_name());
    }
  if(_open_window)
    {
   _open_window = false;
    TTransactionData data;
    Esl->GET_DIVISION_LIST(data,10);
    }
  }
while(!Terminated)
     {
     TInBlock* inb = new TInBlock(SERV_DB_MAX_PACKET);
     inb->bread = recv(sck,&inb->v[0],SERV_DB_MAX_PACKET ,0);
     if(!inb->bread)              //Remote socket gracefully disconnected
       {
       ::closesocket(sck);
       sck = INVALID_SOCKET;
       connected = false;
       delete inb;
       break;
       }
     if(inb->bread == SOCKET_ERROR)
       {
       if(!Terminated)
         {
         int err = WSAGetLastError();
         ::closesocket(sck);
         sck = INVALID_SOCKET;
         connected = false;
         lasterr.clear();
         lasterr = "SUBSCR_DB ";
         GetLastSocketError(lasterr,err);
         sendlasterr();
         }
       delete inb;
       break;
       }
     inb->dt = inb->dt.CurrentDateTime();  
     if(Esl->SDB_PT)
        Esl->SDB_PT->setQueue(inb);
     }
}//try
catch(Exception& e){exsSstEXCEPTION(*eltp,"__TSubcrDBRecvTcpThread::Execute",e);}
}
//----------------------------------------------------------------------------
void __fastcall TSubcrDBRecvTcpThread::CheckConnError()
{
int err = WSAGetLastError();
::closesocket(sck);
sck = INVALID_SOCKET;
connected = false;
lasterr.clear();
switch(conn_count){
      case 0:
      case 1:
            lasterr = "SUBSCR_DB ";
            GetLastSocketError(lasterr,err);
            sendlasterr();
            NextConnectTime = NextConnectTime.CurrentDateTime() + TDateTime(0,0,5,0);
            break;
      case 2:
            lasterr = "SUBSCR_DB ";
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
void __fastcall TEnterpriseSubscList::FormCloseQuery(TObject *Sender,
      bool &CanClose)
{
Delete_DBChannel();    //Delete all tcp threads
clear_osl();
DBIContacts.clear_contact_list();
SCI.clear();
LOG_Window_Actions("DbInterface window closed");
}
//---------------------------------------------------------------------------
void __fastcall TSubcrDBSendTcpThread::Execute()
{
try{
while(!Terminated)
     {
     TOutBlock* buf = (TOutBlock*)getQueue();
     if(!buf)
       {
       Suspend_Thread();
       continue;
       }
     sendbuf(buf);
     delete buf;
     }
}//try
catch(Exception& e){exsSstEXCEPTION(*eltp,"__TSubcrDBSendTcpThread::Execute",e);}
}
//----------------------------------------------------------------------------
void __fastcall TEnterpriseSubscList::FormDestroy(TObject *Sender)
{
::DeleteCriticalSection(&tcp);
::DeleteCriticalSection(&osl_cs);
}
//---------------------------------------------------------------------------
void __fastcall TSubcrDBSendTcpThread::sendbuf(TOutBlock* buf)
{
int len = buf->v.size();
if(len)
  {
  #ifdef SubscDB_LogSendPacket
  TDateTime DateTime = DateTime.CurrentDateTime();
  #endif
  send_tcp(&buf->v[0], len);
  #ifdef SubscDB_LogSendPacket
  LOG_SendPacket(DateTime,buf);
  #endif
  }
}
//----------------------------------------------------------------------------
void __fastcall TSubcrDBSendTcpThread::send_tcp(const char* buf, int len)
{
::EnterCriticalSection(&EnterpriseSubscList->tcp);
  if(EnterpriseSubscList->SDB_RTT)
    {
    SOCKET SCK = EnterpriseSubscList->SDB_RTT->get_sck();
    if(SCK != INVALID_SOCKET)
      {
      if(EnterpriseSubscList->SDB_RTT->get_connected())
       if(send(SCK, buf, len, 0) == SOCKET_ERROR)
         {
         int err = WSAGetLastError();
         lasterr.clear();
         lasterr = "SUBSCR_DB ";
         GetLastSocketError(lasterr,err);
         sendlasterr();
         }
      }
    }
::LeaveCriticalSection(&EnterpriseSubscList->tcp);
}
//-----------------------------------------------------------------------------
void __fastcall TSubcrDBRecvTcpThread::LOG_Connection()
{
TEventLogThread* elt = getLog();
if(elt)
  {
  TDateTime dt = dt.CurrentDateTime();
  string s;
  exsDateTime(dt,s);
  s = "\n" + s + " Connected to subscriber's DB " + host + ":" + inttostr(port) + "\n";
  elt->FputEvt(s);
  }
}
//---------------------------------------------------------------------------
#ifdef SubscDB_LogSendPacket
void __fastcall TSubcrDBSendTcpThread::LOG_SendPacket(TDateTime& DateTime,TOutBlock* buf)
{
TEventLogThread* elt = getLog();
if(elt)
  {
  int len = buf->v.size();
  if(len)
    {
    string str;
    exsDateTime(DateTime,str);
    str = "\n" + str + " Pckt Sent To DbInterface Len " + inttostr(len) + "\n";
    for(int i=0;i < len;i++)
       {
       if(i)str += " ";
       str += inttohexstr(buf->v[i],2);
       }
    str += "\n";
    elt->FputEvt(str);
    }
  }
}
#endif
//----------------------------------------------------------------------------
#ifdef SubscDB_LogRecvPacket
void __fastcall TSubcrDBParsThread::LOG_RecvPacket(TInBlock* buf)
{
TEventLogThread* elt = getLog();
if(elt)
  {
  if(buf->bread > 0)
    {
    string str;
    exsDateTime(buf->dt,str);
    str = "\n" + str + " Pckt Received From DBInterface Len " + inttostr(buf->bread) + "\n";
    for(int i=0;i < buf->bread;i++)
       {
       if(i)str += " ";
       str += inttohexstr(buf->v[i],2);
       }
    str += "\n";
    elt->FputEvt(str);
    }
  }
}
#endif
//----------------------------------------------------------------------------
void __fastcall TEnterpriseSubscList::UPDATE_TRANSACTION_TIME_STMP(const TServDBMsg& sdbm)
{
::EnterCriticalSection(&osl_cs);
  TOutSeqList::iterator it = osl.find(sdbm.seq_number);
  if(it != osl.end())
    (*it).second.dt = (*it).second.dt.CurrentDateTime();
::LeaveCriticalSection(&osl_cs);
}
//----------------------------------------------------------------------------
unsigned __fastcall TEnterpriseSubscList::get_contact_list_seq_number(unsigned seq_num)
{
unsigned rv = 0;
::EnterCriticalSection(&osl_cs);
  TOutSeqList::iterator it = osl.find(seq_num);
  if(it != osl.end())
     rv = (*it).second.get_seq_num_1();
::LeaveCriticalSection(&osl_cs);
return rv;
}
//-----------------------------------------------------------------------------
string __fastcall TEnterpriseSubscList::get_trans_user(unsigned seq_num)
{
string rv;
::EnterCriticalSection(&osl_cs);
  TOutSeqList::iterator it = osl.find(seq_num);
  if(it != osl.end())
     rv = (*it).second.s_1;
::LeaveCriticalSection(&osl_cs);
return rv;
}
//-----------------------------------------------------------------------------
bool __fastcall TEnterpriseSubscList::exists(unsigned seq_num)
{
bool rv = false;
::EnterCriticalSection(&osl_cs);
  if(osl.find(seq_num) != osl.end())
    rv = true; 
::LeaveCriticalSection(&osl_cs);
return rv;
}
//-----------------------------------------------------------------------------
void __fastcall TEnterpriseSubscList::ins_osl(unsigned seq_num, const TTransactionData& data, queue<unsigned>& q)
{
::EnterCriticalSection(&osl_cs);
  if(!osl.empty())
    {
    TDateTime dt = dt.CurrentDateTime();
    TOutSeqList::iterator it = osl.begin();
    while(it != osl.end())
         {
         if((dt - (*it).second.dt) > TDateTime(0,3,0,0)) //Ack on this seq_number not received more than 1 min
           {
           q.push((*it).first);    //queue with values of deleted seq_number (for log)
           osl.erase(it);
           it = osl.begin();
           continue;
           }
         it++;
         }
    }
  osl.insert(TOutSeqList::value_type(seq_num, data));
::LeaveCriticalSection(&osl_cs);
}
//-----------------------------------------------------------------------------
TTransactionData __fastcall TEnterpriseSubscList::get_osl(unsigned seq_num)
{
TTransactionData rv;
::EnterCriticalSection(&osl_cs);
  TOutSeqList::iterator it = osl.find(seq_num);
  if(it != osl.end())
    {
    rv = (*it).second;
    rv.set_actual(true);
    }
::LeaveCriticalSection(&osl_cs);
return rv;
}
//-----------------------------------------------------------------------------
void __fastcall TEnterpriseSubscList::del_osl(unsigned seq_num, queue<unsigned>& q)
{
::EnterCriticalSection(&osl_cs);
  TOutSeqList::iterator it = osl.find(seq_num);
  if(it != osl.end())
    {
    q.push(seq_num);            //queue with values of deleted seq_number (for log)
    osl.erase(it);
    }
  if(!osl.empty())
    {
    TDateTime dt = dt.CurrentDateTime();
    it = osl.begin();
    while(it != osl.end())
         {
         if((dt - (*it).second.dt) > TDateTime(0,1,0,0)) //Ack on this seq_number not received more than 1 min
           {
           q.push((*it).first);    //queue with values of deleted seq_number (for log)
           osl.erase(it);
           it = osl.begin();
           continue;
           }
         it++;
         }
    }
::LeaveCriticalSection(&osl_cs);
}
//-----------------------------------------------------------------------------
void __fastcall TEnterpriseSubscList::clear_osl()
{
::EnterCriticalSection(&osl_cs);
  osl.clear();
::LeaveCriticalSection(&osl_cs);
}
//-----------------------------------------------------------------------------
bool __fastcall TEnterpriseSubscList::empty_osl()
{
bool rv = false;
::EnterCriticalSection(&osl_cs);
  rv = osl.empty();
::LeaveCriticalSection(&osl_cs);
return rv;
}
//-----------------------------------------------------------------------------
TOutBlock* __fastcall TEnterpriseSubscList::create_start_request_block(const TTransactionData& data, ServDbMsgType SDMT)
{
TOutBlock* ob = new TOutBlock(ExhangeType__req, SDMT, ++send_seq_number);
if(ob)
  {
  queue<unsigned> deleted_seq_number;
  ins_osl(ob->get_seq_number(), data, deleted_seq_number);
  log_deleted_seq_numbers(deleted_seq_number);
  }
return ob;
}
//------------------------------------------------------------------------------
TOutBlock* __fastcall TEnterpriseSubscList::create_next_request_block(ServDbMsgType SDMT, unsigned current_seq_number)
{
TOutBlock* ob = NULL;
if(exists(current_seq_number)) // Транзакция с таким seq_number существует?
   ob = new TOutBlock(ExhangeType__req, SDMT, current_seq_number);
return ob;
}
//------------------------------------------------------------------------------
void __fastcall TEnterpriseSubscList::SEND_REQUEST(TOutBlock* ob)
{
::EnterCriticalSection(&tcp);
  if(SDB_STT)
     SDB_STT->setQueue(ob);
::LeaveCriticalSection(&tcp);
}
//-----------------------------------------------------------------------------
void __fastcall TEnterpriseSubscList::LOG_Window_Actions(const string& str)
{
if(MainFormSLS->ofs->elt)
  {
  TDateTime DateTime = DateTime.CurrentDateTime();
  string s;
  exsDateTime(DateTime,s);
  s = "\n" + s + WS + str;
  MainFormSLS->ofs->elt->FputEvt(s);
  }
}
//----------------------------------------------------------------------------
void __fastcall TOutBlock::pack_header_REQ()
{
pack_pref();
pack_length();
pack_seq();
pack_msg_type();
pack_et();
pack_prms_req();
}
//------------------------------------------------------------------------------
void __fastcall TOutBlock::pack_pref()
{
v[0] = DATABASE_NET_PREF;
}
//-----------------------------------------------------------------------------
void __fastcall TOutBlock::pack_length()
{
int sz = v.size();
sz-=3;
v[1] = sz >> 8;
v[2] = sz;
}
//-----------------------------------------------------------------------------
void __fastcall TOutBlock::pack_seq()
{
v[3] = seq_number >> 24;
v[4] = seq_number >> 16;
v[5] = seq_number >> 8;
v[6] = seq_number;
}
//-----------------------------------------------------------------------------
void __fastcall TOutBlock::pack_msg_type()
{
v[7] = msg_type >> 8;
v[8] = msg_type;
}
//-----------------------------------------------------------------------------
void __fastcall TOutBlock::pack_et()
{
v[9] = et;
}
//-----------------------------------------------------------------------------
void __fastcall TOutBlock::pack_prms_req()
{
v[10] = prms;
}
//------------------------------------------------------------------------------
void __fastcall TPackBlock::pack_fixed_type(int par_name,IapDataType data_type,unsigned value)
{
v.push_back(par_name >> 8);
v.push_back(par_name);
v.push_back(data_type);
switch(data_type)
 {
 case IapDataType_Int1:         // 1 Byte
      v.push_back(value);
      break;
 case IapDataType_Int2:         // 2 Bytes
      v.push_back(value >> 8);
      v.push_back(value);
      break;
 case IapDataType_Int4:         // 4 bytes
      v.push_back(value >> 24);
      v.push_back(value >> 16);
      v.push_back(value >> 8);
      v.push_back(value);
      break;
 }
prms++;
}
//-----------------------------------------------------------------------------
void __fastcall TPackBlock::pack_string_type(int par_name, const string& s)
{
int sz = s.length();
if(sz)
  {
  v.push_back(par_name >> 8);
  v.push_back(par_name);
  v.push_back(IapDataType_String);
  v.push_back((sz >> 8) & 0xFF);  //MSB Param length
  v.push_back(sz);                //LSB Param length
  const char* buf = s.c_str();
  for(int i = 0; i < sz; i++)
      v.push_back(buf[i]);
  prms++;
  }
}
//------------------------------------------------------------------------------
void __fastcall TPackBlock::pack_other_type(int par_name, const vector<UBYTE>& src)
{
int sz = src.size();
if(sz)
  {
  v.push_back(par_name >> 8);
  v.push_back(par_name);
  v.push_back(IapDataType_Other);
  v.push_back((sz >> 8) & 0xFF);  //MSB Param length
  v.push_back(sz);                //LSB Param length
  for(int i = 0; i < sz; i++)
      v.push_back(src[i]);
  prms++;
  }
}
//------------------------------------------------------------------------------
//--- минимальная длина фрейма == 10. Проверяется в get_single_msg() -----------
//------------------------------------------------------------------------------
void __fastcall TSubcrDBParsThread::Execute()
{
try{
   while(!Terminated)
        {
        TInBlock* inb = (TInBlock*)getQueue();
        if(!inb)
          {
          Suspend_Thread();
          continue;
          }
        #ifdef SubscDB_LogRecvPacket
        LOG_RecvPacket(inb);
        #endif
        vector<UBYTE> v;
        copy(v,inb->v,inb->bread);
        if(check_prefix(v))
          {
          vector<UBYTE> frame;
          while(get_single_msg(frame,v))      //check if(v.size() < 10) inside
               {
               switch(frame[9]){
                      case 0: get_req(frame);     break;
                      case 1: get_ack(frame);     break;
                      case 2: get_evt(frame);     break;
                      case 3: get_evt_ack(frame); break;
                     }
               }
          }
        delete inb;
        }
}//try
catch(Exception& e){exsSstEXCEPTION(NULL,"__TSubcrDBParsThread::Execute",e);}
}
//-----------------------------------------------------------------------------
void __fastcall TSubcrDBParsThread::copy(vector<UBYTE>& dst, vector<UBYTE>& src, int sz_2)
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
bool __fastcall TSubcrDBParsThread::check_prefix(vector<UBYTE>& v)
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
bool __fastcall TSubcrDBParsThread::get_single_msg(vector<UBYTE>& frame, vector<UBYTE>& v)
{
bool rv = false;
if(v.size() < 10)  //!!!!
  BUF = v;    //save incomplete msg and wait for a new packet
else
  rv = get_frame(frame,v);
return rv;
}
//-----------------------------------------------------------------------------
//--- //checkin  if(v.size() < 10)  before calling get_ack() ------------------
//-----------------------------------------------------------------------------
bool __fastcall TSubcrDBParsThread::get_frame(vector<UBYTE>& frame, vector<UBYTE>& v)
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
void __fastcall TSubcrDBParsThread::get_req(vector<UBYTE>& frame)
{
;
}
//-----------------------------------------------------------------------------
void __fastcall TSubcrDBParsThread::get_ack(const vector<UBYTE>& v)
{
try{
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
      case ServDbMsgType_GET_TIMESTAMP:
           Proc_Ack__GET_TIMESTAMP(sdbm);
           break;
      case ServDbMsgType_GET_PERSONAL_CONTACT_LIST:
           Proc_Ack__GET_CONTACT_LIST(sdbm);
           break;
      case ServDbMsgType_GET_PERSONAL_CITY_PHONE_LIST:
           Proc_Ack__GET_CITY_PHONE_LIST(sdbm);
           break;
      case ServDbMsgType_MODIFY_CONTACT_LIST:
           Proc_Ack__MODIFY_CONTACT_LIST(sdbm);
           break;
      case ServDbMsgType_GET_DIVISION_LIST:
           Proc_Ack__GET_DIVISION_LIST(sdbm);
           break;
      case ServDbMsgType_GET_DIVISION_CONTACT_LIST:
           Proc_Ack__GET_DIVISION_CONTACT_LIST(sdbm);
           break;
      case ServDbMsgType_REQ_START_SUBSCR_DATA:
           Proc_Ack__REQ_START_SUBSCR_DATA(sdbm);
           break;
      case ServDbMsgType_FIND:
           Proc_Ack__FIND(sdbm);
           break;
      }
 }//try
catch(Exception& e){exsSstEXCEPTION(MainFormSLS->ofs->elt,"__TSubcrDBParsThread::get_ack()",e);}
}
//-----------------------------------------------------------------------------
void __fastcall TServDBMsg::get_parameters(const vector<UBYTE>& v)
{
unsigned sz = v.size();
if(sz > 10)
  {
  status = v[10];
  if(sz > 11)
    {
    int prms = v[11];
    unsigned n = 12;
    for(int i=0;i<prms;i++)
        get_parameter(v,n,sz);
    }
  }
}
//-----------------------------------------------------------------------------
void __fastcall TServDBMsg::get_parameter(const vector<UBYTE>& v,unsigned& n,unsigned sz)
{
TServDBPar sdbp;
if((n + 3) <= sz)
  {
  sdbp.prm_type  = v[n++] << 8;
  sdbp.prm_type |= v[n++];
  sdbp.idt       = (IapDataType)v[n++];
  if(sdbp.get_par(v,n,sz))
     q.push(sdbp);
  }
}
//------------------------------------------------------------------------------
bool __fastcall TServDBPar::get_par(const vector<UBYTE>& v,unsigned& n,unsigned sz)
{
bool rv = false;
switch(idt){
      case IapDataType_Bool:
      case IapDataType_Int1: if((n + 1) <= sz)
                               {
                               u = v[n++];
                               rv = true;
                               }
                             break;
      case IapDataType_Int2: if((n + 2) <= sz)
                               {
                               u  = v[n++] << 8;
                               u |= v[n++];
                               rv  = true;
                               }
                             break;
      case IapDataType_Int4: if((n + 4) <= sz)
                               {
                               u  = v[n++] << 24;
                               u |= v[n++] << 16;
                               u |= v[n++] << 8;
                               u |= v[n++];
                               rv = true;
                               }
                             break;
      case IapDataType_Int8: if((n + 8) <= sz)
                               {
                               unsigned msb  = v[n++] << 24;
                                        msb |= v[n++] << 16;
                                        msb |= v[n++] << 8;
                                        msb |= v[n++];
                               unsigned lsb  = v[n++] << 24;
                                        lsb |= v[n++] << 16;
                                        lsb |= v[n++] << 8;
                                        lsb |= v[n++];
                               i64 = ((__int64)msb << 32)|(lsb & 0xFFFFFFFF);
                               rv = true;
                               }
                             break;
      case IapDataType_String: if((n + 2) <= sz)
                                 {
                                 unsigned len = _par_len(v,n);
                                 if(len)
                                  if((n + len) <= sz)
                                    {
                                    vector<char> vc(len + 1,0);
                                    memcpy(&vc[0],&v[n],len);
                                    s = string(&vc[0]);
                                    n += len;
                                    rv = true;
                                    }
                                 }
                              break;
      case IapDataType_Other: if((n + 2) <= sz)
                                {
                                 unsigned len = _par_len(v,n);
                                 if(len)
                                  if((n + len) <= sz)
                                    {
                                    vu.resize(len);
                                    memcpy(&vu[0],&v[n],len);
                                    n += len;
                                    rv = true;
                                    }
                                }
                              break;
      case IapDataType_Nested:if((n + 1) <= sz)
                                {
                                unsigned prms = v[n++];
                                for(unsigned i=0;i<prms;i++)
                                   {
                                   TServDBPar sdbp;
                                   if((n + 3) <= sz)
                                     {
                                     sdbp.prm_type  = v[n++] << 8;
                                     sdbp.prm_type |= v[n++];
                                     sdbp.idt       = (IapDataType)v[n++];
                                     if(sdbp.get_par(v,n,sz))
                                        q_nested.push(sdbp);
                                     }
                                   }
                                rv = true;
                                }
                              break;

      }
return rv;
}
//------------------------------------------------------------------------------
unsigned __fastcall TServDBPar::_par_len(const vector<UBYTE>& v,unsigned& n)
{
unsigned rv  = v[n++] << 8;
         rv |= v[n++];
return rv;
}
//-----------------------------------------------------------------------------
void __fastcall TSubcrDBParsThread::get_evt(vector<UBYTE>& v)
{
;
}
//-----------------------------------------------------------------------------
void __fastcall TSubcrDBParsThread::get_evt_ack(vector<UBYTE>& frame)
{
;
}
//-----------------------------------------------------------------------------
unsigned __fastcall TSubcrDBParsThread::get_length(const vector<UBYTE>& v)
{
unsigned rv  = v[1] << 8;
         rv |= v[2];
return rv;
}
//-----------------------------------------------------------------------------
unsigned __fastcall TSubcrDBParsThread::get_prm_type(const vector<UBYTE>& v, unsigned& n)
{
unsigned rv  = v[n++] << 8;
         rv |= v[n++];
return   rv;
}
//-----------------------------------------------------------------------------
unsigned __fastcall TSubcrDBParsThread::get_data_type(const vector<UBYTE>& v, unsigned& n)
{
return v[n++];
}
//-----------------------------------------------------------------------------
void __fastcall TEnterpriseSubscList::LEFT_PANELResize(TObject *Sender)
{
DrawGrid1->ColWidths[0] = DrawGrid1->Width;
}
//---------------------------------------------------------------------------
void __fastcall TSubcrDBParsThread::Proc_Ack__GET_DIVISION_LIST(TServDBMsg& sdbm)
{
#ifdef SubscDB_LogParsedPacket
string log;
#endif
TTempContList tcl;
if(sdbm.status == 0x10)
  {
  esl->UPDATE_TRANSACTION_TIME_STMP(sdbm);
  while(!sdbm.q.empty())
       {
       TServDBPar sdbp = sdbm.q.front();
       sdbm.q.pop();
       switch(sdbp.prm_type){
             case 1:if(sdbp.idt == IapDataType_Nested)
                      {
                      TContact* Contact = new TContact;
                      while(!sdbp.q_nested.empty())
                           {
                           TServDBPar sdbp_1 = sdbp.q_nested.front();
                           sdbp.q_nested.pop();
                           switch(sdbp_1.prm_type){
                                  case 1: Contact->full_name = sdbp_1.s;
                                          break;
                                  case 2: Contact->DBI.ID = sdbp_1.u;
                                          Contact->set_id(sdbp_1.u + DBI_SHIFT); //10000000);  // + 10000000 чтобы не совпадало с внутренним ID
                                          Contact->name = inttostr(Contact->get_id());
                                          break;
                                  case 3: Contact->DBI.ParentID     = sdbp_1.u;
                                          break;
                                  case 4: Contact->DBI.HasSubgroups = sdbp_1.u;
                                          break;
                                  case 5: Contact->DBI.HasContacts  = sdbp_1.u;
                                          break;
                                  }
                           #ifdef SubscDB_LogParsedPacket
                           switch(sdbp_1.prm_type){
                                  case 1: log = "\"" + sdbp_1.s + "\"";                          break;
                                  case 2: log += " ID = " + inttostr(sdbp_1.u);                  break;
                                  case 3: log += " ParentID = "     + inttostr(sdbp_1.u) + "\n"; break;
                                  case 4: log += " HasSubgroups = " + inttostr(sdbp_1.u) + "\n"; break;
                                  case 5: log += " HasContacts  = " + inttostr(sdbp_1.u) + "\n"; break;
                                  }
                           #endif
                           }
                      tcl.ins_contact(Contact);
                      #ifdef SubscDB_LogParsedPacket
                      LOG_ParsPacket(log);
                      #endif
                      }
                    break;
             case 2:
                    if(sdbp.idt == IapDataType_Int1)
                     __get_end_of_list(tcl, sdbp, log);
                    break;
             }
       }  //  while(!sdbm.q.empty())

  TContact* cont;
  while((cont = tcl.get_contact()) != NULL )
       {
       cont->CT = ContactType_DIVISION;
       esl->DBIContacts.add_contact(cont,esl->DrawGrid1,false);
       }


  } //if(sdbm.status == 0x10)

if(tcl.get_end_of_list())
   update_out_seq_list(sdbm);
}
//-----------------------------------------------------------------------------
void __fastcall TSubcrDBParsThread::Proc_Ack__GET_DIVISION_CONTACT_LIST(TServDBMsg& sdbm)
{
#ifdef SubscDB_LogParsedPacket
string log;
#endif
TTempContList tcl;
if(sdbm.status == 0x10)
  {
  esl->UPDATE_TRANSACTION_TIME_STMP(sdbm);
  while(!sdbm.q.empty())
       {
       TServDBPar sdbp = sdbm.q.front();
       sdbm.q.pop();
       switch(sdbp.prm_type){
             case 1:if(sdbp.idt == IapDataType_Nested)
                      {
                      TContact* Contact = new TContact;
                      while(!sdbp.q_nested.empty())
                           {
                           TServDBPar sdbp_1 = sdbp.q_nested.front();
                           sdbp.q_nested.pop();
                           switch(sdbp_1.prm_type){
                                  case 1: Contact->DBI.ID = sdbp_1.u;
                                          Contact->set_id(sdbp_1.u + DBI_SHIFT); //10000000);  // + 10000000 чтобы не совпадало с внутренним ID
                                          Contact->name = inttostr(Contact->get_id());
                                          break;
                                  case 2: Contact->name      = sdbp_1.s;
                                          break;
                                  case 3: Contact->full_name = sdbp_1.s;   //Erase liders white spaces
                                          break;
                                  case 5: Contact->position  = sdbp_1.s;
                                          break;
                                  case 6: Contact->cos       = sdbp_1.u;
                                          break;
                                  }
                           #ifdef SubscDB_LogParsedPacket
                           switch(sdbp_1.prm_type){
                                  case 1: log  = "\nID = " + inttostr(sdbp_1.u) + "\n";     break;
                                  case 2: log += "nickname = \"" + sdbp_1.s + "\"" + "\n";  break;
                                  case 3: log += "full_name = \"" + sdbp_1.s + "\"" + "\n"; break;
                                  case 5: log += "position = \"" + sdbp_1.s + "\"" + "\n";  break;
                                  case 6: log += "cos = " + inttostr(sdbp_1.u) + "\n";      break;
                                  }
                           #endif
                           }
                      #ifdef SubscDB_LogParsedPacket
                      LOG_ParsPacket(log);
                      #endif
                      left_trim_string(Contact->full_name);
                      tcl.ins_contact(Contact);
                      }
                    break;
             case 2:
                    if(sdbp.idt == IapDataType_Int1)
                     __get_end_of_list(tcl, sdbp, log);
                    break;
             }
       }  //  while(!sdbm.q.empty())

  if(!tcl.empty())
    {
    TTransactionData td = esl->get_osl(sdbm.seq_number);
    if(td.get_actual())
      if(td.u_1)
        {
        TContact* ParentContact = esl->DBIContacts.get_contact_by_id(td.u_1  + DBI_SHIFT);
        if(ParentContact)
          {
          TContact* Cont;
          while((Cont = tcl.get_contact()) != NULL)
               {
               Cont->CT = ContactType_CLIENT;
               if(!ParentContact->Abonents)
                 {
                 ParentContact->Abonents = new TAbonents;
                 ParentContact->Abonents->set_contact_list_size_pointer(esl->get_contact_list_size_pointer());
                 ParentContact->Abonents->set_hwnd(esl->Handle);
                 }
               ParentContact->Abonents->add_abonent_contact(ParentContact,Cont);
               }
          }
        }
      else //root division
        {
        TContact* Cont;
        while((Cont = tcl.get_contact()) != NULL )
             {
             Cont->CT = ContactType_CLIENT;
             if(!esl->Abonents)
                {
                esl->Abonents = new TAbonents;
                esl->Abonents->set_contact_list_size_pointer(esl->get_contact_list_size_pointer());
                esl->Abonents->set_hwnd(esl->Handle);
                }
             esl->Abonents->add_abonent_contact(NULL,Cont);
             }
        }
    }
  }  //if(sdbm.status == 0x10)
if(tcl.get_end_of_list())
   update_out_seq_list(sdbm);
}
//-----------------------------------------------------------------------------
void __fastcall TSubcrDBParsThread::Proc_Ack__GET_CONTACT_LIST(TServDBMsg& sdbm)
{
#ifdef SubscDB_LogParsedPacket
string log;
#endif
TTempContList tcl;
if(sdbm.status == 0x10)
  {
  esl->UPDATE_TRANSACTION_TIME_STMP(sdbm);
  while(!sdbm.q.empty())
       {
       TServDBPar sdbp = sdbm.q.front();
       sdbm.q.pop();
       switch(sdbp.prm_type){
             case 1:if(sdbp.idt == IapDataType_Nested)
                       __get_contact_list(sdbp, sdbm.seq_number, ServDbMsgType_GET_PERSONAL_CONTACT_LIST, log);
                    break;
             case 2:
                    if(sdbp.idt == IapDataType_Int1)
                      __get_end_of_list(tcl, sdbp, log);
                    break;
             }
       }
  }
if(tcl.get_end_of_list())
  {
  end_of_client_contact_list(sdbm.seq_number);
  update_out_seq_list(sdbm);    //delete this seq number
  }
}
//------------------------------------------------------------------------------
void __fastcall TSubcrDBParsThread::Proc_Ack__GET_CITY_PHONE_LIST(TServDBMsg& sdbm)
{
#ifdef SubscDB_LogParsedPacket
string log;
#endif
TTempContList tcl;
if(sdbm.status == 0x10)
  {
  esl->UPDATE_TRANSACTION_TIME_STMP(sdbm);
  while(!sdbm.q.empty())
       {
       TServDBPar sdbp = sdbm.q.front();
       sdbm.q.pop();
       switch(sdbp.prm_type){
             case 1:if(sdbp.idt == IapDataType_Nested)
                       __get_contact_list(sdbp, sdbm.seq_number, ServDbMsgType_GET_PERSONAL_CITY_PHONE_LIST, log);
                    break;
             case 2:
                    if(sdbp.idt == IapDataType_Int1)
                      __get_end_of_list(tcl, sdbp, log);
                    break;
             }
       }
  }
if(tcl.get_end_of_list())
  {
  end_of_client_city_phone_list(sdbm.seq_number);
  update_out_seq_list(sdbm);    //delete this seq number
  }
}
//------------------------------------------------------------------------------
void __fastcall TSubcrDBParsThread::Proc_Ack__FIND(TServDBMsg&  sdbm)
{
string log;
if(sdbm.status == 0x10)
  {
  esl->UPDATE_TRANSACTION_TIME_STMP(sdbm);
  while(!sdbm.q.empty())
       {
       TServDBPar sdbp = sdbm.q.front();
       sdbm.q.pop();
       switch(sdbp.prm_type){
             case 1:if(sdbp.idt == IapDataType_Nested)
                     __get_contact_list(sdbp, sdbm.seq_number, ServDbMsgType_FIND, log);
                    break;
             }
       }
  }
//Работаем без end_of_list. Если принято записей ( found_mathes ) меньше чем заказано в запросе, то считается что это end_of_list
unsigned found_mathes = esl->SearchStruct.get_new_arrivals_count();
if(found_mathes)
  {
  esl->SearchStruct.copy_search_result();
::PostMessage(esl->Handle, CONTROL_MSG, WM_APP_MSG_WPARAM__DRAWGRID_FIND_ROW_COUNT, esl->SearchStruct.get_list_size());
  }
else
  {
 ::PostMessage(esl->Handle, CONTROL_MSG, WM_APP_MSG_WPARAM__DRAWGRID_FIND_REPAINT, 0); 
  }
queue<unsigned> deleted_seq_number;
esl->check_end_of_search_transaction(sdbm.seq_number, found_mathes, deleted_seq_number);
esl->log_deleted_seq_numbers(deleted_seq_number);
}
//------------------------------------------------------------------------------
void __fastcall TSubcrDBParsThread::__get_contact_list(TServDBPar& SDBP, unsigned seq_num, ServDbMsgType sdmt, string& log)
{
while(!SDBP.q_nested.empty())
     {
     TServDBPar sdbp = SDBP.q_nested.front();
     SDBP.q_nested.pop();
     switch(sdbp.prm_type){   //All parameters with msg #1 - ContactData, type - Nested
           case 1:if(sdbp.idt == IapDataType_Nested)
                     __get_contact_data(sdbp, seq_num, sdmt, log);
                  break;
           }
     }
#ifdef SubscDB_LogParsedPacket
LOG_ParsPacket(log);
#endif
}
//-----------------------------------------------------------------------------
void __fastcall TSubcrDBParsThread::__get_contact_data(TServDBPar& SDBP, unsigned seq_num, ServDbMsgType sdmt, string& log)
{
TDBData dbd;
dbd.u_2 = seq_num;
while(!SDBP.q_nested.empty()){
     TServDBPar sdbp = SDBP.q_nested.front();
     SDBP.q_nested.pop();
          switch(sdbp.prm_type){
           case 0:dbd.u_0 = sdbp.u; // RecordID
                  break;
           case 1:dbd.s_1 = sdbp.s; //nick_name
                  break;
           case 2:dbd.s_2 = sdbp.s; //db_name
                  break;
           case 3:dbd.s_3 = sdbp.s; //job_position
                  break;
           case 4:dbd.s_4 = sdbp.s; //db_second_name
                  break;
           case 5:dbd.s_5 = sdbp.s; //db_family
                  break;
           case 6:dbd.s_6 = sdbp.s; //db_local_name
                  break;
           } // switch(sdbp.prm_type)
     } // while(!SDBP.q_nested.empty())

if(sdmt != ServDbMsgType_FIND)
  {
  if(dbd.s_6.empty())
    {
    if(dbd.s_5.empty())
      if(dbd.s_2.empty())
        if(dbd.s_2.empty())
           dbd.s_7 = dbd.s_1;
    if(dbd.s_7.empty())
       dbd.s_7 = dbd.s_5 + WS + dbd.s_2 + WS + dbd.s_4;
    }
  else
    dbd.s_7 = dbd.s_6;
  }

#ifdef SubscDB_LogParsedPacket
log += "\nnickname     = \"" + dbd.s_1 + "\"\n" +
        "first_name   = \"" + dbd.s_2 + "\"\n" +
        "second_name  = \"" + dbd.s_4 + "\"\n" +
        "family       = \"" + dbd.s_5 + "\"\n";
         if(sdmt != ServDbMsgType_FIND)
            log += "full_name    = \"" + dbd.s_7 + "\"\n";
         log += "local_name   = \"" + dbd.s_6 + "\"\n" +
        "job_position = \"" + dbd.s_3 + "\"\n";
#endif

if(sdmt != ServDbMsgType_FIND)
  left_trim_string(dbd.s_7);

dbd.SDMT = sdmt;
if(sdmt == ServDbMsgType_FIND)
  esl->SearchStruct.push_new_arrival(dbd);
else
  {
  esl->DBIExch.push(dbd);
::PostMessage(MainFormSLS->Handle, CONTROL_MSG, WM_APP_MSG_WPARAM__DBI_DATA, WM_APP_MSG_LPARAM__NOPARAM);
  }
}
//----------------------------------------------------------------------------
void __fastcall TSubcrDBParsThread::__get_end_of_list(TTempContList& tcl, TServDBPar& sdbp, string& log)
{
tcl.set_end_of_list(sdbp.u);
#ifdef SubscDB_LogParsedPacket
log = "\nend_of_list " + inttostr(sdbp.u) + "\n";
LOG_ParsPacket(log);
#endif
}
//------------------------------------------------------------------------------
void __fastcall TSubcrDBParsThread::__get_subscr_data(TServDBPar& SDBP)
{
TDBData dbd;
while(!SDBP.q_nested.empty()){
     TServDBPar sdbp = SDBP.q_nested.front();
     SDBP.q_nested.pop();
     switch(sdbp.prm_type){
            case 1:dbd.s_1 = sdbp.s; //full_user_name
                   break;
           }
     }
}
//------------------------------------------------------------------------------
void __fastcall TEnterpriseSubscList::log_deleted_seq_numbers(queue<unsigned>& q)
{
try{
if(!q.empty())
  if(MainFormSLS->ofs)
    if(MainFormSLS->ofs->elt)
      {
      string s = "\nEnterpriseSubsc::Listdeleted sequens numbers: ";
      while(!q.empty())
           {
           unsigned u = q.front();
           q.pop();
           s += inttostr(u) + WS;
           }
      s += "\n";
      MainFormSLS->ofs->elt->FputEvt(s,1);
      }
 }//try
catch(Exception& e){exsSstEXCEPTION(MainFormSLS->ofs->elt,"__TEnterpriseSubscList::log_deleted_seq_numbers()",e);}
}
//-----------------------------------------------------------------------------
void __fastcall TEnterpriseSubscList::DrawGrid1DrawCell(TObject *Sender,
      int ACol, int ARow, TRect &Rect, TGridDrawState State)
{
if(State.Contains(gdFocused))
  {
  DrawGrid1->Canvas->Brush->Color = clActiveCaption;   //clBlue;// clBackground;
  DrawGrid1->Canvas->Font->Color  = clWhite;
  DrawGrid1->Canvas->FillRect(Rect);
  DrawGrid1->Canvas->DrawFocusRect(Rect);
  }
DBIContacts.Display(MainFormSLS->ImageList1, DrawGrid1, DrawGrid1->Canvas, ARow, Rect, State); //MainFormSLS->ImageList1,DrawGrid1 need only for virtual
}
//-----------------------------------------------------------------------------
void __fastcall TDBIContacts::add_contact(TContact* Contact, TDrawGrid* DrawGrid, bool Sort)
{
::EnterCriticalSection(&contlist_cs);
  int id = Contact->get_id();
  if(contact_list.find(id) == contact_list.end())
     if(name_list.find(Contact->name) == name_list.end())
       {
      _insert_contact_in_contact_list(Contact, Sort);
       if(!Contact->DBI.ParentID)
           (*pContact_list_size)++;
       else
         {
         TContact* ParentContact = get_contact_by_id(Contact->DBI.ParentID + DBI_SHIFT); //10000000);
         if(ParentContact)
           {
           Contact->OWNER = ParentContact;
           if(ParentContact->get_open())
              (*pContact_list_size)++;
           if(!ParentContact->find_underlying_id(ParentContact->underlying_ids, id))
               ParentContact->underlying_ids.push_back(id);
           if(Contact->CT == ContactType_DIVISION)
             if(!ParentContact->find_underlying_id(ParentContact->underlying_division_ids, id))
               ParentContact->underlying_division_ids.push_back(id);
           }
         }
       if(!*pContact_list_size)
          ::PostMessage(hwnd, CONTROL_MSG, WM_APP_MSG_WPARAM__DRAWGRID_ROW_COUNT, 1);
       else
          ::PostMessage(hwnd, CONTROL_MSG, WM_APP_MSG_WPARAM__DRAWGRID_ROW_COUNT, *pContact_list_size);
       }
::LeaveCriticalSection(&contlist_cs);
}
//-----------------------------------------------------------------------------
void __fastcall TAbonents::add_abonent_contact(TContact* ParentContact, TContact* Contact/*,TDrawGrid* DrawGrid*/)
{
::EnterCriticalSection(&contlist_cs);
  int id = Contact->get_id();
  if(contact_list.find(id) == contact_list.end())
     if(name_list.find(Contact->name) == name_list.end())
       {
      _insert_contact_in_contact_list(Contact,false);
       if(!ParentContact)
           (*pContact_list_size)++;
       else
          {
          Contact->DBI.ParentID = ParentContact->DBI.ID;
          Contact->OWNER        = ParentContact;
          if(ParentContact->get_open())
             (*pContact_list_size)++;
          }
       if(!*pContact_list_size)
          ::PostMessage(hwnd, CONTROL_MSG, WM_APP_MSG_WPARAM__DRAWGRID_ROW_COUNT, 1);
       else
          ::PostMessage(hwnd, CONTROL_MSG, WM_APP_MSG_WPARAM__DRAWGRID_ROW_COUNT, *pContact_list_size);
       }
::LeaveCriticalSection(&contlist_cs);
}
//------------------------------------------------------------------------------
void __fastcall TAbonents::make_actual_division_directory(string& s_cl, vector<TContact*>& v)
{
vector<TContact*>::reverse_iterator it = v.rbegin();
while(it != v.rend())
     {
     TContact* Contact = *it++;
     s_cl += "\\" + Contact->name;
     }
}
//------------------------------------------------------------------------------
void __fastcall TAbonents::add_abonents_to_actual_directory()
{
::EnterCriticalSection(&contlist_cs);
  TContactList::iterator it = contact_list.begin();
  while(it != contact_list.end())
       {
       TContact* Contact = (*it).second;
       if(Contact)
          add_contact_name_to_actual_directory(Contact);
       it++;
       }
::LeaveCriticalSection(&contlist_cs);
}
//-----------------------------------------------------------------------------
void  __fastcall TAbonents::add_abonents_from_external_db_to_personal_contact_list()
{
::EnterCriticalSection(&contlist_cs);
  string user = get_current_user();
  string s_cl = MainFormSLS->get_clients_dir();
  s_cl += "\\" + user + "\\" + get_CONTACTS_DIR();
  TContactList::iterator it = contact_list.begin();
  while(it != contact_list.end())
       {
       TContact* Contact = (*it).second;
       if(Contact)
         {
         vector<TContact*> v;
         get_all_parent_divisions(v, Contact);
         MainFormSLS->Sip->Contacts.add_contact_from_external_db_to_personal_contact_list(v, Contact, MainFormSLS->DrawGrid1);
         }
       it++;
       }
::LeaveCriticalSection(&contlist_cs);
}
//-----------------------------------------------------------------------------
TContact* __fastcall TAbonents::get_abonent_by_row(int& i,int Row)
{
TContact* rv = NULL;
::EnterCriticalSection(&contlist_cs);
  int sz = contact_list.size();
  if((i + sz) >= Row)
    {
    i++;
    TContactList::iterator it = contact_list.begin();
    while(it != contact_list.end())
         {
         if(i == Row)
           {
           rv = (*it).second;
           break;
           }
         i++;it++;
         }
    }
  else
    i += sz;
::LeaveCriticalSection(&contlist_cs);
return rv;
}
//------------------------------------------------------------------------------
void __fastcall TEnterpriseSubscList::Get_DBI_CONTROL_MSG(TMessage &Message)
{
try{
switch(Message.WParam){
       case WM_APP_MSG_WPARAM__DRAWGRID_ROW_COUNT:
            DrawGrid1->RowCount = Message.LParam;
            DrawGrid1->Repaint();
            break;
       case WM_APP_MSG_WPARAM__DRAWGRID_FIND_ROW_COUNT:
            DrawGrid_Find->RowCount = Message.LParam;
            if(Message.LParam > 0){
              set_audio_call_btn_state(BtnState_ACTIVE);
              set_video_call_btn_state(BtnState_ACTIVE);
              set_conference_call_btn_state(BtnState_ACTIVE);
              set_add_contact_btn_state(BtnState_ACTIVE);
              }
            DrawGrid_Find->Repaint();
            break;
       case WM_APP_MSG_WPARAM__DRAWGRID_FIND_REPAINT:
            DrawGrid_Find->Repaint();
            break;
       case WM_APP_MSG_WPARAM__CLOSE_DB_CHANNEL:
            if(!Visible)
              if(empty_osl())
                 Delete_DBChannel();
            break;
      }
}//try
catch(Exception& e){exsSstEXCEPTION(MainFormSLS->ofs->elt,"__Get_DBI_CONTROL_MSG(TMessage &Message)",e);}
}
//---------------------------------------------------------------------------
void __fastcall TEnterpriseSubscList::DrawGrid1MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
int ACol,ARow;
DrawGrid1->MouseToCell(X,Y,ACol,ARow);
SCI.clear();
//if(Button == mbLeft)      //Пока правая кнопка не используется для каких-то целей, использовать ее так же как правую
//  {
  TContact* Contact = DBIContacts.get_dbi_contact_by_row(ARow);
  if(Contact)
    {
    SCI.set(*Contact);
    Label1->Caption = Contact->full_name.c_str();
    if(Contact->CT == ContactType_DIVISION)
      {
      set_audio_call_btn_state(BtnState_INACTIVE);
      set_video_call_btn_state(BtnState_INACTIVE);
      set_conference_call_btn_state(BtnState_INACTIVE);
      set_add_contact_btn_state(BtnState_ACTIVE);

      if(Contact->get_open())
         DBIContacts.set_division_visible(Contact->get_id(), DrawGrid1, false);   //Close visible of underlying divisions and clients
      else
         {
         DBIContacts.set_division_visible(Contact->get_id(), DrawGrid1, true);
         if(Contact->DBI.HasContacts)
          if(!Contact->DBI.RequestedContacts)
            {
            TTransactionData data;
            data.u_1 = Contact->DBI.ID;
            GET_DIVISION_CONTACT_LIST(data, 0, 10);
            }
         if(Contact->DBI.HasSubgroups)
           if(!Contact->DBI.RequestedSubgroups)
             {
             TTransactionData data;
             data.u_1 = Contact->DBI.ID;
             GET_DIVISION_LIST(data, 10);
             }
         }
      //user_name_to_send.clear();
      //AnsiString S;
      //ComboBox1->Text = S;
      DrawGrid1->Repaint();
    //return;
      }
    else //if(ContCopy.CT == ContactType_DIVISION)
      {
      set_audio_call_btn_state(BtnState_ACTIVE);
      set_video_call_btn_state(BtnState_ACTIVE);
      set_conference_call_btn_state(BtnState_ACTIVE);
      set_add_contact_btn_state(BtnState_ACTIVE);
      }
    } //if(DBIContacts.get_contact_copy_by_row(ContCopy,ARow))
//  }  if(Button == mbLeft)
}
//---------------------------------------------------------------------------
void __fastcall TEnterpriseSubscList::GET_SUBSC_START_DATA(const string& name)
{
TTransactionData data;
data.s_1 = name;
TOutBlock* ob = create_start_request_block(data, ServDbMsgType_REQ_START_SUBSCR_DATA);
if(ob)
  {
  ob->pack_string_type(1,name);
  ob->pack_header_REQ();
  SEND_REQUEST(ob);
  }
}
//---------------------------------------------------------------------------
void __fastcall TEnterpriseSubscList::REQ_CONTACT_LIST_TIME_STMP(const string& name)
{
try{
if(!name.empty())
  {
  TTransactionData data;
  data.s_1 = name;
  TOutBlock* ob = create_start_request_block(data, ServDbMsgType_GET_TIMESTAMP);
  if(ob)
    {
    ob->pack_string_type(1,name);
    ob->pack_header_REQ();
    SEND_REQUEST(ob);
    }
  }
}//try
catch(Exception& e){exsSstEXCEPTION(MainFormSLS->ofs->elt,"__TEnterpriseSubscList::REQ_CONTACT_LIST_TIME_STMP()",e);}
}
//----------------------------------------------------------------------------
void __fastcall TEnterpriseSubscList::GET_DIVISION_LIST(const TTransactionData& data, unsigned count)
{
TOutBlock* ob = create_start_request_block(data, ServDbMsgType_GET_DIVISION_LIST);
if(ob)
  {
  ob->pack_fixed_type(1, IapDataType_Int4, data.u_1); //Parent Group ID
  ob->pack_fixed_type(2, IapDataType_Int4, 0);        //Last Group ID
  ob->pack_fixed_type(3, IapDataType_Int1, count);
  ob->pack_header_REQ();
  SEND_REQUEST(ob);
  }
}
//------------------------------------------------------------------------------
void __fastcall TEnterpriseSubscList::GET_DIVISION_CONTACT_LIST(const TTransactionData& data, unsigned last_contactID, unsigned count)
{
TOutBlock* ob = create_start_request_block(data, ServDbMsgType_GET_DIVISION_CONTACT_LIST);
if(ob)
  {
  ob->pack_fixed_type(1, IapDataType_Int4, data.u_1);    //Parent Group ID
  ob->pack_fixed_type(2, IapDataType_Int4, last_contactID);
  ob->pack_fixed_type(3, IapDataType_Int1, count);
  ob->pack_header_REQ();
  SEND_REQUEST(ob);
  }
}
//------------------------------------------------------------------------------
void __fastcall TEnterpriseSubscList::MODIFY_PERSONAL_CONTACT_LIST(const TTransactionData& data)
{
TOutBlock* ob = create_start_request_block(data, ServDbMsgType_MODIFY_CONTACT_LIST);
if(ob)
  {
  ob->pack_fixed_type(1, IapDataType_Int1, data.u_1);
  ob->pack_string_type(2, data.s_1);   //my user name
  ob->pack_string_type(3, data.s_2);   //contact user name
  if(!data.s_3.empty())
     ob->pack_string_type(4, data.s_3); //full_name
  ob->pack_header_REQ();
  SEND_REQUEST(ob);
  }
}
//-----------------------------------------------------------------------------
void __fastcall TEnterpriseSubscList::MODIFY_PERSONAL_CITY_PHONE_LIST(const TTransactionData& data)
{
TOutBlock* ob = create_start_request_block(data, ServDbMsgType_MODIFY_PERSONAL_CITY_PHONE_LIST);
if(ob)
  {
  ob->pack_fixed_type(1, IapDataType_Int1, data.u_1);
  ob->pack_string_type(2, data.s_1);   //my user name
  ob->pack_string_type(3, data.s_2);   //contact user name
  if(!data.s_3.empty())
     ob->pack_string_type(4, data.s_3); //full_name
  ob->pack_header_REQ();
  SEND_REQUEST(ob);
  }
}
//-----------------------------------------------------------------------------
bool __fastcall TDBIContacts::get_contact_copy_by_row(TContact& Contact, int Row)
{
bool rv = false;
::EnterCriticalSection(&contlist_cs);
  int i=0;
  TContactList::iterator it = contact_list.begin();
  while(it!=contact_list.end())
       {               /*
                       TContact* test_cont = (*it).second;
                       int aids_sz = test_cont->underlying_division_ids.size();
                       int ais_sz  = test_cont->underlying_ids.size();
                       */
       if((*it).second->CT == ContactType_DIVISION)
         {
         if(!(*it).second->DBI.ParentID)
           {
           if(i == Row)
             {
             Contact.dbi_copy((*it).second);
             rv = true;
             break;
             }
           if(!(*it).second->get_open())
             {
             i++;it++;  //Do not i++.  Данный клиент, DIVISION, видим. Нижележащие невидимы Список ДАННОГО подразделения в данный момент закрыт)
             continue;
             }
           TContact* contact = (*it).second->proc_underlying_division_DBI_ids_for_cell_display(this,i,Row);
           if(contact)
             {
             Contact.dbi_copy(contact);
             rv = true;
             break;
             }
           contact = (*it).second->proc_underlying_DBI_abonents_for_cell_display(i,Row);
           if(contact)
             {
             Contact.dbi_copy(contact);
             rv = true;
             break;
             }
           else
             {
             it++;
             continue;
             }
           }
         else
           {       //Данный контакт  входит  в одно из подразделений ((*it).second->DBI.ParentID !=  0)
           TContact* OwnerContact = get_contact_by_id((*it).second->DBI.ParentID);
           if(OwnerContact)
             {
             if(OwnerContact->get_open())
               {
               if(i == Row)
                 {
                 Contact.dbi_copy((*it).second);
                 rv = true;
                 break;
                 }
               TContact* contact = (*it).second->proc_underlying_division_DBI_ids_for_cell_display(this,i,Row);
               if(contact)
                 {
                 Contact.dbi_copy(contact);
                 rv = true;
                 break;
                 }
               contact = (*it).second->proc_underlying_DBI_abonents_for_cell_display(i,Row);
               if(contact)
                 {
                 Contact.dbi_copy(contact);
                 rv = true;
                 break;
                 }
               else
                 {
                 it++;
                 continue;
                 }
               }
             }
           it++;
           continue;
           }
         }  //if((*it).second->CT == ContactType_DIVISION)
       i++; it++;
       }   //while(it!=contact_list.end())
::LeaveCriticalSection(&contlist_cs);
return rv;
}
//------------------------------------------------------------------------------
TContact* __fastcall TDBIContacts::get_dbi_contact_by_row(int Row, bool OnControl)
{
TContact* contact = NULL;
::EnterCriticalSection(&contlist_cs);
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
       if((*it).second->DBI.ParentID)
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
         contact = (*it).second->proc_underlying_division_DBI_ids_for_cell_display(this,i,Row);
         if(contact)
            break;
         contact = (*it).second->proc_underlying_DBI_abonents_for_cell_display(i,Row);
         if(contact)
            break;
         } //if((*it).second->CT == ContactType_DIVISION)
       i++;it++;
       } //while
  }
::LeaveCriticalSection(&contlist_cs);
if(contact)
   contact->pContact = contact;
return contact;
}
//------------------------------------------------------------------------------
bool __fastcall TDBIContacts::contact_visible(TContact* Contact)
{
bool rv = true;
if(Contact->DBI.ParentID)
  {
  TContact* OwnerContact = get_contact_by_id(Contact->DBI.ParentID);
  if(OwnerContact)
   if(!OwnerContact->get_open())
      rv = false;
  }
return rv;
}
//-----------------------------------------------------------------------------
void __fastcall TEnterpriseSubscList::RIGHT_PANELResize(TObject *Sender)
{
//DrawGrid2->ColWidths[0] = DrawGrid2->Width;
}
//---------------------------------------------------------------------------
void __fastcall TDBIContacts::draw_division(TCanvas* GC, const TRect& Rect, TContact* Contact)
{
TContact* ParentContact = NULL;
Contact->x_pos = get_state_left(Rect);
if(Contact->DBI.ParentID)
  {
  ParentContact = get_contact_by_id(Contact->DBI.ParentID + DBI_SHIFT); //10000000);
  if(ParentContact)
     Contact->x_pos = ParentContact->x_pos + 20;
  }
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

if(ParentContact)
   text_left = Contact->x_pos;

GC->Brush->Color = clSilver; //(TColor)get_turquoise_color(); //clGray;     //(TColor)FOREGR_ACTIVE_YELLOW;
GC->Font->Color  = clWhite;
GC->Font->Size   = 10; //12;
GC->Font->Style  = GC->Font->Style << fsBold;

GC->TextOut(text_left, text_top, S);

GC->Brush->Color = brush_color;
GC->Font->Color  = font_color;
GC->Font->Size   = 10;

   GC->Font->Color = (TColor)get_turquoise_color();

if(ParentContact)
  GC->TextOut(Contact->x_pos + 25, get_top(Rect), Contact->full_name.c_str());
else
  GC->TextOut(get_fname_left(Rect), get_top(Rect), Contact->full_name.c_str());

GC->Font->Size  = font_size;
GC->Font->Style = font_style;
}
//---------------------------------------------------------------------------------
void __fastcall TDBIContacts::set_division_visible(int id, TDrawGrid* DG, bool a)
{
::EnterCriticalSection(&contlist_cs);
  TContactList::iterator it = contact_list.find(id);
  if(it != contact_list.end())
    {
    (*it).second->set_open(a);
    if(!a)       //Close all underlying divisions
      {
       TContact* Contact = (*it).second;
      *pContact_list_size -= Contact->underlying_division_ids.size();
       if(Contact->Abonents)
          *pContact_list_size -= Contact->Abonents->contact_list.size();

      if(!Contact->underlying_division_ids.empty()) //Если имеются underlying divisions
        {
        vector<int>::iterator it_v = Contact->underlying_division_ids.begin();
        while(it_v != Contact->underlying_division_ids.end())
             {
             it = contact_list.find(*it_v++);
             if(it != contact_list.end())
               {
               if((*it).second->get_open())
                  {
                  set_division_visible((*it).second->get_id(), DG, a);
                  /*
                  *pContact_list_size -= (*it).second->underlying_ids.size();
                  if((*it).second->Abonents)
                    *pContact_list_size -= (*it).second->Abonents->contact_list.size();
                   */
                  }
               (*it).second->set_open(a);
               }
             }
        }
      if(*pContact_list_size < 0)
        *pContact_list_size = 0;
      Update_DrawGrid_RowCount(DG);
      } //if(!a)
    else     //Open underlying division (only underliying !!!)
      {
      *pContact_list_size += (*it).second->underlying_division_ids.size();
      if((*it).second->Abonents)
         *pContact_list_size += (*it).second->Abonents->contact_list.size();
      Update_DrawGrid_RowCount(DG);
      }
    }
::LeaveCriticalSection(&contlist_cs);
}
//------------------------------------------------------------------------------
void __fastcall TDBIContacts::Display(TImageList* IL,TDrawGrid* DG,TCanvas* GC,int row,const TRect& Rect, TGridDrawState State)
{
::EnterCriticalSection(&contlist_cs);
  TContact* Contact = get_dbi_contact_by_row(row);
  if(Contact)
    {
    if(contact_visible(Contact))
      {
      if(Contact->CT == ContactType_DIVISION)
         draw_division(GC, Rect, Contact);
      else
        {
        int fname_left = get_fname_left(Rect);
        if(Contact->DBI.ParentID)
          {
          TContact* ParentContact = get_contact_by_id(Contact->DBI.ParentID + DBI_SHIFT); //10000000);
          if(ParentContact)
             fname_left = ParentContact->x_pos + 25;
          }
        GC->Font->Name  = "Arial";
        GC->Font->Size  = 10;
        GC->Font->Color = (TColor)get_turquoise_color();
        GC->Font->Style  = GC->Font->Style << fsBold;
        string s;
        if(!Contact->position.empty())
           s = Contact->position + ":" + WS + WS;
        if(s.empty())
           s = Contact->full_name;
        else
           s += Contact->full_name;
        GC->TextOut(fname_left, get_top(Rect), s.c_str());
        }
      }
    }
::LeaveCriticalSection(&contlist_cs);
}
//------------------------------------------------------------------------------
int __fastcall TEnterpriseSubscList::__set_Panel1_Top()
{
return  Height - Panel1->Height - 30;
}
//------------------------------------------------------------------------------
void __fastcall TEnterpriseSubscList::FormResize(TObject *Sender)
{
Panel1->Top   = __set_Panel1_Top();
Panel1->Width =   Width;
if(AudioCall_Img->Visible)
  {
  double left_margin   = Width/2 - 2.75 * btn_img_widh;
  AudioCall_Img->Left  = left_margin;
  VideoCall_Img->Left  = AudioCall_Img->Left  + k_width*AudioCall_Img->Width;
  Conference_Img->Left = VideoCall_Img->Left  + k_width*VideoCall_Img->Width;
  AddContact_Img->Left = Conference_Img->Left + k_width*Conference_Img->Width;
  }
if(Width < min_width)
   Width = min_width;
LEFT_PANEL->Width = Width;
if(Panel_Find->Visible)
  {
  Panel_Find->Width  = Width;
  Panel_Find->Height = __set_Panel_Find_Height();
  }
}
//---------------------------------------------------------------------------
void __fastcall TDBIContacts::make_actual_division_directory(string& s_cl, vector<TContact*>& v)
{
vector<TContact*>::reverse_iterator it = v.rbegin();
while(it != v.rend())
     {
     TContact* Contact = *it++;
     s_cl += "\\" + Contact->name;
     }
}
//------------------------------------------------------------------------------
bool __fastcall TDBIContacts::check_actual_directory_existence(const string& directory)
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
       string division_name;
       int st = dir.rfind("\\");
       if(++st < (int)dir.length())
         {
         division_name = dir.substr(st);
         if(!division_name.empty())
           {
           TContact Contact;
           if(get_contact_copy_by_user_name(Contact,division_name))
             {
             string file_name = dir + "\\" + (string)"!" + division_name + ".!nm";
             if(!FileExists(file_name.c_str()))
               {
               FILE* f = fopen(file_name.c_str(),"wt");
               if(f)
                 {
                 string s = inttostr(Contact.DBI.ID) + ";" + Contact.full_name + ";";
                 fputs(s.c_str(),f);
                 fclose(f);
                 }
             }
           }
          }
         }
       it++;
       }
  }
return true;
}
//---------------------------------------------------------------------------
void __fastcall TEnterpriseSubscList::Button2Click(TObject *Sender)
{
if(SCI.selected_Contact)
  {
  if(SCI.selected_Contact->name == MainFormSLS->Sip->Account.get_user_name())
     return;
  string user = get_current_user();
  string s_cl = MainFormSLS->get_clients_dir();
  s_cl += "\\" + user + "\\" + get_CONTACTS_DIR();
  vector<TContact*> v;
  #ifdef StructuralContactsImport
  DBIContacts.get_all_parent_divisions(v, SCI.selected_Contact);
  DBIContacts.make_actual_division_directory(s_cl, v);
  #endif
  if(DBIContacts.check_actual_directory_existence(s_cl))
    {
    if(SCI.selected_Contact->CT == ContactType_CLIENT)
      {
       DBIContacts.add_contact_name_to_actual_directory(SCI.selected_Contact);
       MainFormSLS->Sip->Contacts.add_contact_from_external_db_to_personal_contact_list(v, SCI.selected_Contact, MainFormSLS->DrawGrid1);
      }
    else if(SCI.selected_Contact->CT == ContactType_DIVISION)
      DBIContacts.add_division_name_to_actual_directory(SCI.selected_Contact);
    }
  }
else //contact in the root directory
  {
  }
MainFormSLS->DrawGrid1->Repaint();
}
//---------------------------------------------------------------------------
void __fastcall TDBIContacts::add_division_name_to_actual_directory(TContact* Contact)
{
string user = get_current_user();
string s_cl = MainFormSLS->get_clients_dir();
s_cl += "\\" + user + "\\" + get_CONTACTS_DIR();
vector<TContact*> v;
#ifdef StructuralContactsImport
get_all_parent_divisions(v, Contact);
make_actual_division_directory(s_cl, v);
s_cl += "\\" + Contact->name;
#endif
if(check_directory_existence(s_cl))
  {
  #ifdef StructuralContactsImport
  s_cl += "\\" + (string)"!" + Contact->name + ".!nm";
  FILE* f = fopen(s_cl.c_str(),"wt");
  if(f)
    {
    string s = inttostr(Contact->DBI.ID) + ";" + Contact->full_name + ";";
    fputs(s.c_str(),f);
    fclose(f);
    }
  #endif  
  if(!Contact->underlying_division_ids.empty())
    {
    vector<int>::iterator it = Contact->underlying_division_ids.begin();
    while(it != Contact->underlying_division_ids.end())
         {
         TContact* ChildContact = get_contact_by_id(*it);
         if(ChildContact)
           add_division_name_to_actual_directory(ChildContact);
         it++;
         }
    }
  if(Contact->Abonents)
    {
     Contact->Abonents->add_abonents_to_actual_directory();
     Contact->Abonents->add_abonents_from_external_db_to_personal_contact_list();
    }
  else
    MainFormSLS->Sip->Contacts.add_contact_from_external_db_to_personal_contact_list(v, Contact, MainFormSLS->DrawGrid1); // "1.1.24_31";
  }
}
//------------------------------------------------------------------------------
TContact* __fastcall TContact::proc_underlying_division_DBI_ids_for_cell_display(TDBIContacts* DBIC, int& i, int Row)
{
TContact* rv = NULL;
if(!underlying_division_ids.empty())
  {
//  i++;
  vector<int>::iterator it = underlying_division_ids.begin();
  while(it != underlying_division_ids.end())
       {
       TContact* Contact = DBIC->get_contact_by_id(*it);
       if(Contact)
         {
         i++;
         if(i == Row)
           return Contact;
         if(Contact->get_open())
           {
           rv = Contact->proc_underlying_division_DBI_ids_for_cell_display(DBIC, i, Row);
           if(rv)
             return rv;
           rv = Contact->proc_underlying_DBI_abonents_for_cell_display(i, Row);
           if(rv)
             return rv;
           }
         }
       /*i++;*/ it++;
       }
  }
return rv;
}
//------------------------------------------------------------------------------
TContact* __fastcall TContact::proc_underlying_DBI_abonents_for_cell_display(int& i, int Row)
{
TContact* rv = NULL;
if(Abonents)
   rv = Abonents->get_abonent_by_row(i,Row);
return rv;
}
//------------------------------------------------------------------------------
void __fastcall TEnterpriseSubscList::DrawGrid1KeyUp(TObject *Sender,
      WORD &Key, TShiftState Shift)
{
TDrawGrid* DG = (TDrawGrid*)Sender;
if(!DrawGrid1)return;
switch(Key){
      case 33: //PageUp
      case 34: //PageDown
      case 38: //Up
      case 40:{//Down
              TContact* Contact = DBIContacts.get_dbi_contact_by_row(DG->Row);
              if(Contact)
                {
                SCI.set(*Contact);
                Label1->Caption = Contact->full_name.c_str();
                if(Contact->CT == ContactType_DIVISION)
                  {
                  set_audio_call_btn_state(BtnState_INACTIVE);
                  set_video_call_btn_state(BtnState_INACTIVE);
                  set_conference_call_btn_state(BtnState_INACTIVE);
                  set_add_contact_btn_state(BtnState_ACTIVE);
                  }
                else //if(ContCopy.CT == ContactType_DIVISION)
                  {
                  set_audio_call_btn_state(BtnState_ACTIVE);
                  set_video_call_btn_state(BtnState_ACTIVE);
                  set_conference_call_btn_state(BtnState_ACTIVE);
                  set_add_contact_btn_state(BtnState_ACTIVE);
                  }
                }
              break;
              }   //case 40:
      case 35: //End
      case 36:{ //Home
              if(Shift.Contains(ssCtrl))
                {
                TContact* Contact = DBIContacts.get_dbi_contact_by_row(DG->Row);
                if(Contact)
                  {
                  SCI.set(*Contact);
                  Label1->Caption = Contact->full_name.c_str();
                  if(Contact->CT == ContactType_DIVISION)
                    {
                    set_audio_call_btn_state(BtnState_INACTIVE);
                    set_video_call_btn_state(BtnState_INACTIVE);
                    set_conference_call_btn_state(BtnState_INACTIVE);
                    set_add_contact_btn_state(BtnState_ACTIVE);
                    }
                  else //if(ContCopy.CT == ContactType_DIVISION)
                    {
                    set_audio_call_btn_state(BtnState_ACTIVE);
                    set_video_call_btn_state(BtnState_ACTIVE);
                    set_conference_call_btn_state(BtnState_ACTIVE);
                    set_add_contact_btn_state(BtnState_ACTIVE);
                    }
                 }
                }
              break;
              }
      case 13:{ //Enter
//              TContact ContCopy(-1);
//              if(DBIContacts.get_contact_copy_by_row(ContCopy,DG->Row))
              TContact* Contact = DBIContacts.get_dbi_contact_by_row(DG->Row);
              if(Contact)
                {
                SCI.set(*Contact);
                Label1->Caption = Contact->full_name.c_str();
                if(Contact->CT == ContactType_DIVISION)
                  {
                   set_audio_call_btn_state(BtnState_INACTIVE);
                   set_video_call_btn_state(BtnState_INACTIVE);
                   set_conference_call_btn_state(BtnState_INACTIVE);
                   set_add_contact_btn_state(BtnState_ACTIVE);
                   if(Contact->get_open())
                      DBIContacts.set_division_visible(Contact->get_id(), DrawGrid1, false);   //Close visible of underlying divisions and clients
                   else
                      {
                      DBIContacts.set_division_visible(Contact->get_id(), DrawGrid1, true);
                      if(Contact->DBI.HasContacts)
                        if(!Contact->DBI.RequestedContacts)
                          {
                          TTransactionData data;
                          data.u_1 = Contact->DBI.ID;
                          GET_DIVISION_CONTACT_LIST(data, 0, 10);
                          }
                      if(Contact->DBI.HasSubgroups)
                        if(!Contact->DBI.RequestedSubgroups)
                          {
                          TTransactionData data;
                          data.u_1 = Contact->DBI.ID;
                          GET_DIVISION_LIST(data, 10);
                          }
                      } //else
                  //user_name_to_send.clear();
                  //AnsiString S;
                  //ComboBox1->Text = S;
                  DrawGrid1->Repaint();
                  }
                else //if(ContCopy.CT == ContactType_DIVISION)
                  {
                  MainFormSLS->set_user_name_to_send(SCI.selected_name);
                  MainFormSLS->ComboBox1->Text        = Label1->Caption;
                  MainFormSLS->CalledNameLbl->Caption = Label1->Caption;
                  MainFormSLS->AudioCall();
                  set_audio_call_btn_state(BtnState_ACTIVE);
                  set_video_call_btn_state(BtnState_ACTIVE);
                  set_conference_call_btn_state(BtnState_ACTIVE);
                  set_add_contact_btn_state(BtnState_ACTIVE);
                  }
                } //if(DBIContacts.get_contact_copy_by_row(ContCopy,DG->Row))
              break;
              }

    }  //switch(Key){
}
//---------------------------------------------------------------------------
void __fastcall TDBIExch::push(const TDBData& dbd)
{
::EnterCriticalSection(&dbiexch_cs);
  q.push(dbd);
::LeaveCriticalSection(&dbiexch_cs);
}
//---------------------------------------------------------------------------
TDBData __fastcall TDBIExch::get()
{
TDBData rv;
::EnterCriticalSection(&dbiexch_cs);
  if(!q.empty())
    {
    rv = q.front();
    q.pop();
    rv.actual = true;
    }
::LeaveCriticalSection(&dbiexch_cs);
return rv;
}
//---------------------------------------------------------------------------
bool __fastcall TDBIExch::empty()
{
bool rv = false;
::EnterCriticalSection(&dbiexch_cs);
  rv = q.empty();
::LeaveCriticalSection(&dbiexch_cs);
return rv;
}
//--------------------------------------------------------------------------
void __fastcall TEnterpriseSubscList::DrawGrid1MouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
int ACol,ARow;
DrawGrid1->MouseToCell(X,Y,ACol,ARow);
if(ACol == -1)
  {
  DrawGrid1->Cursor = crDefault;
  return;
  }
if(ARow == -1)
  {
  DrawGrid1->Cursor = crDefault;
  return;
  }
DrawGrid1->Cursor = crHandPoint;
}
//-----------------------------------------------------------------------------
void __fastcall TEnterpriseSubscList::Make_AudioCall()
{
if(Panel_Find->Visible)
  {
  TDBData dbd;
  if(SearchStruct.get_db_data_by_row(dbd, DrawGrid_Find->Row))
    {
    SCI.selected_name = dbd.s_1;
    string full_name  = dbd.s_5 + WS + dbd.s_2 + WS + dbd.s_4;
    Label1->Caption   = full_name.c_str();
    }
  else
     return;
  }
if(SCI.selected_name == MainFormSLS->Sip->Account.get_user_name())
   return;
MainFormSLS->set_user_name_to_send(SCI.selected_name);
MainFormSLS->ComboBox1->Text        = Label1->Caption;
MainFormSLS->CalledNameLbl->Caption = Label1->Caption;
MainFormSLS->AudioCall();
}
//-----------------------------------------------------------------------------
void __fastcall TEnterpriseSubscList::AudioCallPanel2MouseMove(
      TObject *Sender, TShiftState Shift, int X, int Y)
{
if(ACBS.BS != BtnState_INACTIVE)
  if(ACBS.BS != BtnState_PRESSED)
    if(ACBS.BS != BtnState_FOCUSED)
       set_audio_call_btn_state(BtnState_FOCUSED);

if(VCBS.BS != BtnState_INACTIVE)
  if(VCBS.BS != BtnState_ACTIVE)
     set_video_call_btn_state(BtnState_ACTIVE);

if(CCBS.BS != BtnState_INACTIVE)               //Conference Call
  if(CCBS.BS != BtnState_ACTIVE)
     set_conference_call_btn_state(BtnState_ACTIVE);

if(ADCBS.BS != BtnState_INACTIVE)
  if(ADCBS.BS != BtnState_ACTIVE)
     set_add_contact_btn_state(BtnState_ACTIVE);
}
//---------------------------------------------------------------------------
void __fastcall TEnterpriseSubscList::Panel1MouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
if(ACBS.BS != BtnState_INACTIVE)
  if(ACBS.BS != BtnState_ACTIVE)
     set_audio_call_btn_state(BtnState_ACTIVE);

if(VCBS.BS != BtnState_INACTIVE)
  if(VCBS.BS != BtnState_ACTIVE)
     set_video_call_btn_state(BtnState_ACTIVE);

if(CCBS.BS != BtnState_INACTIVE)               //Conference Call
  if(CCBS.BS != BtnState_ACTIVE)
     set_conference_call_btn_state(BtnState_ACTIVE);

if(ADCBS.BS != BtnState_INACTIVE)
  if(ADCBS.BS != BtnState_ACTIVE)
     set_add_contact_btn_state(BtnState_ACTIVE);
}
//---------------------------------------------------------------------------
void __fastcall TEnterpriseSubscList::AudioCallPanel2MouseDown(
      TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
if(ACBS.BS != BtnState_INACTIVE)
   set_audio_call_btn_state(BtnState_PRESSED);
}
//---------------------------------------------------------------------------
void __fastcall TEnterpriseSubscList::Label_AudioCallMouseDown(
      TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
if(ACBS.BS != BtnState_INACTIVE)
   set_audio_call_btn_state(BtnState_PRESSED);
}
//---------------------------------------------------------------------------
void __fastcall TEnterpriseSubscList::Img_AudioCallMouseDown(
      TObject *Sender, TMouseButton Button, TShiftState Shift, int X,
      int Y)
{
if(ACBS.BS != BtnState_INACTIVE)
   set_audio_call_btn_state(BtnState_PRESSED);
}
//---------------------------------------------------------------------------
void __fastcall TEnterpriseSubscList::AudioCallPanel2MouseUp(
      TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
if(ACBS.BS != BtnState_INACTIVE)
 {
 if(X > 0)
   if(Y > 0)
     if(X < AudioCallPanel2->Width)
       if(Y < AudioCallPanel2->Height)
         {
         Make_AudioCall();
         set_audio_call_btn_state(BtnState_FOCUSED);
         return;
         }
 set_audio_call_btn_state(BtnState_ACTIVE);
 }
}
//---------------------------------------------------------------------------
void __fastcall TEnterpriseSubscList::Label_AudioCallMouseUp(
      TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
if(ACBS.BS != BtnState_INACTIVE)
  {
  if(X > -ACBS.lbl_left)
    if(Y > -ACBS.lbl_top)
      if(X < AudioCallPanel2->Width - ACBS.lbl_left)
        if(Y < AudioCallPanel2->Height - ACBS.lbl_top)
          {
          Make_AudioCall();
          set_audio_call_btn_state(BtnState_FOCUSED);
          return;
          }
  set_audio_call_btn_state(BtnState_ACTIVE);
  }
}
//---------------------------------------------------------------------------
void __fastcall TEnterpriseSubscList::Img_AudioCallMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
if(ACBS.BS != BtnState_INACTIVE)
  {
  if(X > -ACBS.img_left)
    if(Y > -ACBS.img_top)
      if(X < AudioCallPanel2->Width - ACBS.img_left)
        if(Y < AudioCallPanel2->Height - ACBS.img_top)
          {
          Make_AudioCall();
          set_audio_call_btn_state(BtnState_FOCUSED);
          return;
          }
  set_audio_call_btn_state(BtnState_ACTIVE);
  }
}
//------------------------------------------------------------------------------
void __fastcall TEnterpriseSubscList::Make_VideoCall()
{
if(Panel_Find->Visible)
  {
  TDBData dbd;
  if(SearchStruct.get_db_data_by_row(dbd, DrawGrid_Find->Row))
    {
    SCI.selected_name = dbd.s_1;
    string full_name  = dbd.s_5 + WS + dbd.s_2 + WS + dbd.s_4;
    Label1->Caption   = full_name.c_str();
    }
  else
     return;
  }
if(SCI.selected_name == MainFormSLS->Sip->Account.get_user_name())
  return;
MainFormSLS->set_user_name_to_send(SCI.selected_name);
MainFormSLS->ComboBox1->Text        = Label1->Caption;
MainFormSLS->CalledNameLbl->Caption = Label1->Caption;
MainFormSLS->VideoCall();
}
//-----------------------------------------------------------------------------
void __fastcall TEnterpriseSubscList::VideoCallPanel2MouseMove(
      TObject *Sender, TShiftState Shift, int X, int Y)
{
if(VCBS.BS != BtnState_INACTIVE)
  if(VCBS.BS != BtnState_PRESSED)
    if(VCBS.BS != BtnState_FOCUSED)
       set_video_call_btn_state(BtnState_FOCUSED);

if(ACBS.BS != BtnState_INACTIVE)
  if(ACBS.BS != BtnState_ACTIVE)
     set_audio_call_btn_state(BtnState_ACTIVE);

if(CCBS.BS != BtnState_INACTIVE)               //Conference Call
  if(CCBS.BS != BtnState_ACTIVE)
     set_conference_call_btn_state(BtnState_ACTIVE);

if(ADCBS.BS != BtnState_INACTIVE)
  if(ADCBS.BS != BtnState_ACTIVE)
     set_add_contact_btn_state(BtnState_ACTIVE);
}
//---------------------------------------------------------------------------
void __fastcall TEnterpriseSubscList::VideoCallPanel2MouseDown(
      TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
if(VCBS.BS != BtnState_INACTIVE)
   set_video_call_btn_state(BtnState_PRESSED);
}
//---------------------------------------------------------------------------
void __fastcall TEnterpriseSubscList::Label_VideoCallMouseDown(
      TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
if(VCBS.BS != BtnState_INACTIVE)
   set_video_call_btn_state(BtnState_PRESSED);
}
//---------------------------------------------------------------------------
void __fastcall TEnterpriseSubscList::Img_VideoCallMouseDown(
      TObject *Sender, TMouseButton Button, TShiftState Shift, int X,
      int Y)
{
if(VCBS.BS != BtnState_INACTIVE)
   set_video_call_btn_state(BtnState_PRESSED);
}
//---------------------------------------------------------------------------  AUDIO CALL ------------------------------------------------
void __fastcall TEnterpriseSubscList::init_audio_call_btn()
{
AnsiString S;
AudioCallPanel2->Caption     = S;
AudioCallPanel2->BevelInner  = bvLowered;//bvNone; //bvLowered; //bvNone; //bvRaised; ////
AudioCallPanel2->BevelOuter  = bvRaised; //bvNone;// bvRaised; //bvLowered; //bvNone;
AudioCallPanel2->Color       = clWhite;
AudioCallPanel2->Left        = 10;
AudioCallPanel2->Width       = 100;
AudioCallPanel2->Height      = 40;
AudioCallPanel2->Top         = Panel1->Height - AudioCallPanel2->Height - 20;

/*
Img_AudioCall->Transparent   = true;
Img_AudioCall->Stretch       = true;
Img_AudioCall->Left          = LEFT_IMAGE_MARGIN;
Img_AudioCall->Top           = AudioCallPanel2->Height/2 - Img_AudioCall->Height/2;
ACBS.img_left                = Img_AudioCall->Left;
ACBS.img_top                 = Img_AudioCall->Top;  */

ACBS.crc_img_left            = AudioCall_Img->Left;
ACBS.crc_img_top             = AudioCall_Img->Top;

/*
Label_AudioCall->Font->Name  = get_font_name_Arial();
Label_AudioCall->Font->Size  = 10;
Label_AudioCall->Left        = Img_AudioCall->Left + Img_AudioCall->Width + 10;
Label_AudioCall->Top         = AudioCallPanel2->Height/2 - Label_AudioCall->Height/2;
Label_AudioCall->Caption     = "Вызов";
ACBS.lbl_left                = Label_AudioCall->Left;
ACBS.lbl_top                 = Label_AudioCall->Top;
Label_AudioCall->Font->Color = (TColor)get_turquoise_color();//clBlue; //clActiveCaption;
*/
}
//------------------- VIDEO CALL -----------------------------------------------
void __fastcall TEnterpriseSubscList::init_video_call_btn()
{
/*
AnsiString S;
VideoCallPanel2->Caption     = S;
VideoCallPanel2->BevelInner  = bvLowered;
VideoCallPanel2->BevelOuter  = bvRaised;
VideoCallPanel2->Color       = clWhite;
VideoCallPanel2->Left        = AudioCallPanel2->Left + AudioCallPanel2->Width + HORIZONTAL_BTN_INTERVAL;
VideoCallPanel2->Width       = 130;
VideoCallPanel2->Height      = AudioCallPanel2->Height;
VideoCallPanel2->Top         = AudioCallPanel2->Top;
*/
/*
Img_VideoCall->Transparent   = true;
Img_VideoCall->Stretch       = true;
Img_VideoCall->Left          = LEFT_IMAGE_MARGIN;
Img_VideoCall->Top           = VideoCallPanel2->Height/2 - Img_VideoCall->Height/2;
VCBS.img_left                = Img_VideoCall->Left;
VCBS.img_top                 = Img_VideoCall->Top; */

VCBS.crc_img_left            = VideoCall_Img->Left;
VCBS.crc_img_top             = VideoCall_Img->Top;

/*
Label_VideoCall->Font->Name  = get_font_name_Arial();
Label_VideoCall->Font->Size  = 10;
Label_VideoCall->Left        = Img_VideoCall->Left + Img_VideoCall->Width + 10;
Label_VideoCall->Top         = Label_AudioCall->Top; //VideoCallPanel2->Height/2 - Label_VideoCall->Height/2;
Label_VideoCall->Caption     = "Видео вызов";
VCBS.lbl_left                = Label_VideoCall->Left;
VCBS.lbl_top                 = Label_VideoCall->Top;
Label_VideoCall->Font->Color = (TColor)get_turquoise_color();//clBlue; //clActiveCaption;
*/
}
//------------------- ADD TO CONFERENCE ----------------------------------------
void __fastcall TEnterpriseSubscList::init_conference_call_btn()
{
/*
AnsiString S;
ConferenceCallPanel2->Caption     = S;
ConferenceCallPanel2->BevelInner  = bvLowered;
ConferenceCallPanel2->BevelOuter  = bvRaised;
ConferenceCallPanel2->Color       = clWhite;
ConferenceCallPanel2->Left        = VideoCallPanel2->Left + VideoCallPanel2->Width + HORIZONTAL_BTN_INTERVAL;
ConferenceCallPanel2->Width       = 205;
ConferenceCallPanel2->Height      = AudioCallPanel2->Height;
ConferenceCallPanel2->Top         = AudioCallPanel2->Top;
*/
/*
Img_ConferenceCall->Transparent   = true;
Img_ConferenceCall->Stretch       = true;
Img_ConferenceCall->Left          = LEFT_IMAGE_MARGIN;
Img_ConferenceCall->Top           = ConferenceCallPanel2->Height/2 - Img_ConferenceCall->Height/2;
CCBS.img_left                     = Img_ConferenceCall->Left;
CCBS.img_top                      = Img_ConferenceCall->Top; */

CCBS.crc_img_left                 = Conference_Img->Left;
CCBS.crc_img_top                  = Conference_Img->Top;

/*
Label_ConferenceCall->Font->Name  = get_font_name_Arial();
Label_ConferenceCall->Font->Size  = 10;
Label_ConferenceCall->Left        = Img_ConferenceCall->Left + Img_ConferenceCall->Width + 10;
Label_ConferenceCall->Top         = Label_AudioCall->Top; //ConferenceCallPanel2->Height/2 - Label_ConferenceCall->Height/2;
Label_ConferenceCall->Caption     = "Добавить в конференцию";
CCBS.lbl_left                     = Label_ConferenceCall->Left;
CCBS.lbl_top                      = Label_ConferenceCall->Top;
Label_ConferenceCall->Font->Color = (TColor)get_turquoise_color();//clBlue; //clActiveCaption;
*/
}
//--------------------- ADD CONTACT  ----------------------------------------------------------
void __fastcall TEnterpriseSubscList::init_add_contact_btn()
{
/*
AnsiString S;
AddContactPanel2->Caption     = S;
AddContactPanel2->BevelInner  = bvLowered;
AddContactPanel2->BevelOuter  = bvRaised;
AddContactPanel2->Color       = clWhite;
AddContactPanel2->Left        = ConferenceCallPanel2->Left + ConferenceCallPanel2->Width + HORIZONTAL_BTN_INTERVAL;
AddContactPanel2->Width       = 180;
AddContactPanel2->Height      = AudioCallPanel2->Height;
AddContactPanel2->Top         = AudioCallPanel2->Top;
*/
/*
Img_AddContact->Transparent   = true;
Img_AddContact->Stretch       = true;
Img_AddContact->Left          = LEFT_IMAGE_MARGIN;
Img_AddContact->Top           = AddContactPanel2->Height/2 - Img_AddContact->Height/2;
ADCBS.img_left                = Img_AddContact->Left;
ADCBS.img_top                 = Img_AddContact->Top;  */

ADCBS.crc_img_left            = AddContact_Img->Left;
ADCBS.crc_img_top             = AddContact_Img->Top;

/*
Label_AddContact->Font->Name  = get_font_name_Arial();
Label_AddContact->Font->Size  = 10;
Label_AddContact->Left        = Img_AddContact->Left + Img_AddContact->Width + 10;
Label_AddContact->Top         = Label_AudioCall->Top; //ConferenceCallPanel2->Height/2 - Label_ConferenceCall->Height/2;
Label_AddContact->Caption     = "Добавить в контакты";
ADCBS.lbl_left                = Label_ConferenceCall->Left;
ADCBS.lbl_top                 = Label_ConferenceCall->Top;
Label_AddContact->Font->Color = (TColor)get_turquoise_color();//clBlue; //clActiveCaption;
*/
}
//-----------------------------------------------------------------------------
void __fastcall TEnterpriseSubscList::add_to_contact_list()
{
if(Panel_Find->Visible)
  {
  TDBData dbd;
  if(SearchStruct.get_db_data_by_row(dbd, DrawGrid_Find->Row))
    {
    if(dbd.s_1 == MainFormSLS->Sip->Account.get_user_name())
       return;
    string user = get_current_user();
    string s_cl = MainFormSLS->get_clients_dir();
    s_cl += "\\" + user + "\\" + get_CONTACTS_DIR();
    if(DBIContacts.check_actual_directory_existence(s_cl))
      {
      TContact Contact;
      Contact.name      = dbd.s_1;
      Contact.full_name = dbd.s_5 + WS + dbd.s_2 + WS + dbd.s_4;
      Contact.position  = dbd.s_3;
      vector<TContact*> v; //dummy
      DBIContacts.add_contact_name_to_actual_directory(&Contact);
      MainFormSLS->Sip->Contacts.add_contact_from_external_db_to_personal_contact_list(v, &Contact, MainFormSLS->DrawGrid1);
      TTransactionData data;
      data.u_1 = 0; //добавить в персональный контакт лист
      data.s_1 = MainFormSLS->Sip->Account.get_user_name();
      data.s_2 = Contact.name;
      MODIFY_PERSONAL_CONTACT_LIST(data);
      MainFormSLS->DrawGrid1->Repaint();
      }
    }
  return;
  }
if(SCI.selected_Contact)
  {
  if(SCI.selected_Contact->name == MainFormSLS->Sip->Account.get_user_name())
     return;
  string user = get_current_user();
  string s_cl = MainFormSLS->get_clients_dir();
  s_cl += "\\" + user + "\\" + get_CONTACTS_DIR();
  vector<TContact*> v;
  #ifdef StructuralContactsImport
  DBIContacts.get_all_parent_divisions(v, SCI.selected_Contact);
  DBIContacts.make_actual_division_directory(s_cl, v);
  #endif
  if(DBIContacts.check_actual_directory_existence(s_cl))
    {
    if(SCI.selected_Contact->CT == ContactType_CLIENT)
      {
       DBIContacts.add_contact_name_to_actual_directory(SCI.selected_Contact);
       MainFormSLS->Sip->Contacts.add_contact_from_external_db_to_personal_contact_list(v, SCI.selected_Contact, MainFormSLS->DrawGrid1);
      }
    else if(SCI.selected_Contact->CT == ContactType_DIVISION)
      DBIContacts.add_division_name_to_actual_directory(SCI.selected_Contact);
    }
  TTransactionData data;
  data.u_1 = 0; //добавить в персональный контакт лист
  data.s_1 = MainFormSLS->Sip->Account.get_user_name();
  data.s_2 = SCI.selected_Contact->name;
  MODIFY_PERSONAL_CONTACT_LIST(data);
  }
else //contact in the root directory
  {
  }
MainFormSLS->DrawGrid1->Repaint();
}
//---------------------------------------------------------------------------
void __fastcall TEnterpriseSubscList::set_audio_call_btn_state(BtnState BS)
{
ACBS.BS = BS;
switch(ACBS.BS){
      case BtnState_ACTIVE:
           AudioCallPanel2->Color   = clWhite;
           audio_call_mouse_UP();
          // if(!Label_AudioCall->Enabled)
         //     Label_AudioCall->Enabled = true;
           RBitMap::change_color(get_turquoise_color(), 0xE4AC22, AudioCall_Img);
           break;
      case BtnState_FOCUSED:
           AudioCallPanel2->Color = (TColor)0xF0F0F0;
           audio_call_mouse_UP();
           RBitMap::change_color(0xE4AC22, get_turquoise_color(), AudioCall_Img);
           break;
      case BtnState_PRESSED:
           AudioCallPanel2->Color = (TColor)0xE0E0E0;
           audio_call_mouse_DOWN();
           break;
      case BtnState_INACTIVE:
         //  Label_AudioCall->Enabled = false;
           break;
      }
}
//------------------------------------------------------------------------------
void __fastcall TEnterpriseSubscList::set_video_call_btn_state(BtnState BS)
{
VCBS.BS = BS;
switch(VCBS.BS){
      case BtnState_ACTIVE:
         //  VideoCallPanel2->Color   = clWhite;
           video_call_mouse_UP();
         //  if(!Label_VideoCall->Enabled)
         //     Label_VideoCall->Enabled = true;
           RBitMap::change_color(get_turquoise_color(), 0xE4AC22, VideoCall_Img);
           break;
      case BtnState_FOCUSED:
       //    VideoCallPanel2->Color = (TColor)0xF0F0F0;
           video_call_mouse_UP();
           RBitMap::change_color(0xE4AC22, get_turquoise_color(), VideoCall_Img);
           break;
      case BtnState_PRESSED:
       //    VideoCallPanel2->Color = (TColor)0xE0E0E0;
           video_call_mouse_DOWN();
           break;
      case BtnState_INACTIVE:
         //  Label_VideoCall->Enabled = false;
           break;
      }
}
//------------------------------------------------------------------------------
void __fastcall TEnterpriseSubscList::set_conference_call_btn_state(BtnState BS)
{
CCBS.BS = BS;
switch(CCBS.BS){
      case BtnState_ACTIVE:
       //    ConferenceCallPanel2->Color = clWhite;
           conf_call_mouse_UP();
        //   if(!Label_ConferenceCall->Enabled)
        //       Label_ConferenceCall->Enabled = true;
           RBitMap::change_color(get_turquoise_color(), 0xE4AC22, Conference_Img);
           break;
      case BtnState_FOCUSED:
        //   ConferenceCallPanel2->Color = (TColor)0xF0F0F0;
           conf_call_mouse_UP();
           RBitMap::change_color(0xE4AC22, get_turquoise_color(), Conference_Img);
           break;
      case BtnState_PRESSED:
       //    ConferenceCallPanel2->Color = (TColor)0xE0E0E0;
           conf_call_mouse_DOWN();
           break;
      case BtnState_INACTIVE:
       //    Label_ConferenceCall->Enabled = false;
           break;
      }
}
//------------------------------------------------------------------------------
void __fastcall TEnterpriseSubscList::set_add_contact_btn_state(BtnState BS)
{
ADCBS.BS = BS;
switch(ADCBS.BS){
      case BtnState_ACTIVE:
       //    AddContactPanel2->Color = clWhite;
           add_contact_mouse_UP();
         //  if(!Label_AddContact->Enabled)
         //      Label_AddContact->Enabled = true;
           RBitMap::change_color(get_turquoise_color(), 0xE4AC22, AddContact_Img);
           break;
      case BtnState_FOCUSED:
      //     AddContactPanel2->Color = (TColor)0xF0F0F0;
           add_contact_mouse_UP();
           RBitMap::change_color(0xE4AC22, get_turquoise_color(), AddContact_Img);
           break;
      case BtnState_PRESSED:
       //    AddContactPanel2->Color = (TColor)0xE0E0E0;
           add_contact_mouse_DOWN();
           break;
      case BtnState_INACTIVE:
        //   Label_AddContact->Enabled = false;
           break;
      }
}
//------------------------------------------------------------------------------

void __fastcall TEnterpriseSubscList::audio_call_mouse_DOWN()
{
AudioCallPanel2->BevelInner = bvLowered;
AudioCallPanel2->BevelOuter = bvLowered;
//Img_AudioCall->Top         += 1;
//Label_AudioCall->Top       += 1;

AudioCall_Img->Top         += 1;
}
//---------------------------------------------------------------------------
void __fastcall TEnterpriseSubscList::video_call_mouse_DOWN()
{
//VideoCallPanel2->BevelInner = bvLowered;
//VideoCallPanel2->BevelOuter = bvLowered;
//Img_VideoCall->Top         += 1;
//Label_VideoCall->Top       += 1;

VideoCall_Img->Top         += 1;
}
//---------------------------------------------------------------------------
void __fastcall TEnterpriseSubscList::conf_call_mouse_DOWN()
{
//ConferenceCallPanel2->BevelInner = bvLowered;
//ConferenceCallPanel2->BevelOuter = bvLowered;
//Img_ConferenceCall->Top         += 1;
//Label_ConferenceCall->Top       += 1;

Conference_Img->Top             += 1;
}
//---------------------------------------------------------------------------
void __fastcall TEnterpriseSubscList::add_contact_mouse_DOWN()
{
//AddContactPanel2->BevelInner = bvLowered;
//AddContactPanel2->BevelOuter = bvLowered;
//Img_AddContact->Top         += 1;
//Label_AddContact->Top       += 1;

AddContact_Img->Top         += 1;
}
//---------------------------------------------------------------------------
void __fastcall TEnterpriseSubscList::audio_call_mouse_UP()
{
AudioCallPanel2->BevelInner = bvLowered;
AudioCallPanel2->BevelOuter = bvRaised;
//Img_AudioCall->Top          = ACBS.img_top;
//Label_AudioCall->Top        = ACBS.lbl_top;

AudioCall_Img->Top          = ACBS.crc_img_top;
}
//----------------------------------------------------------------------------
void __fastcall TEnterpriseSubscList::video_call_mouse_UP()
{
//VideoCallPanel2->BevelInner = bvLowered;
//VideoCallPanel2->BevelOuter = bvRaised;
//Img_VideoCall->Top          = VCBS.img_top;
//Label_VideoCall->Top        = VCBS.lbl_top;

VideoCall_Img->Top          = VCBS.crc_img_top;
}
//----------------------------------------------------------------------------
void __fastcall TEnterpriseSubscList::conf_call_mouse_UP()
{
//ConferenceCallPanel2->BevelInner = bvLowered;
//ConferenceCallPanel2->BevelOuter = bvRaised;
//Img_ConferenceCall->Top          = CCBS.img_top;
//Label_ConferenceCall->Top        = CCBS.lbl_top;

Conference_Img->Top              = CCBS.crc_img_top;
}
//----------------------------------------------------------------------------
void __fastcall TEnterpriseSubscList::add_contact_mouse_UP()
{
//AddContactPanel2->BevelInner = bvLowered;
//AddContactPanel2->BevelOuter = bvRaised;
//Img_AddContact->Top          = ADCBS.img_top;
//Label_AddContact->Top        = ADCBS.lbl_top;

AddContact_Img->Top          = ADCBS.crc_img_top;
}
//---------------------------------------------------------------------------
void __fastcall TEnterpriseSubscList::AddContactPanel2MouseMove(
      TObject *Sender, TShiftState Shift, int X, int Y)
{
if(ADCBS.BS != BtnState_INACTIVE)              //Add Contact
  if(ADCBS.BS != BtnState_PRESSED)
    if(ADCBS.BS != BtnState_FOCUSED)
       set_add_contact_btn_state(BtnState_FOCUSED);

if(ACBS.BS != BtnState_INACTIVE)               //Audio Call
  if(ACBS.BS != BtnState_ACTIVE)
     set_audio_call_btn_state(BtnState_ACTIVE);

if(VCBS.BS != BtnState_INACTIVE)               //Video Call
  if(VCBS.BS != BtnState_ACTIVE)
     set_video_call_btn_state(BtnState_ACTIVE);

if(CCBS.BS != BtnState_INACTIVE)               //Conference Call
  if(CCBS.BS != BtnState_ACTIVE)
     set_conference_call_btn_state(BtnState_ACTIVE);
}
//---------------------------------------------------------------------------
void __fastcall TEnterpriseSubscList::AddContactPanel2MouseDown(
      TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
if(ADCBS.BS != BtnState_INACTIVE)
   set_add_contact_btn_state(BtnState_PRESSED);
}
//---------------------------------------------------------------------------
void __fastcall TEnterpriseSubscList::Label_AddContactMouseDown(
      TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
if(ADCBS.BS != BtnState_INACTIVE)
   set_add_contact_btn_state(BtnState_PRESSED);
}
//---------------------------------------------------------------------------
void __fastcall TEnterpriseSubscList::Img_AddContactMouseDown(
      TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
if(ADCBS.BS != BtnState_INACTIVE)
   set_add_contact_btn_state(BtnState_PRESSED);
}
//---------------------------------------------------------------------------
void __fastcall TEnterpriseSubscList::ConferenceCallPanel2MouseMove(
      TObject *Sender, TShiftState Shift, int X, int Y)
{
if(CCBS.BS != BtnState_INACTIVE)
  if(CCBS.BS != BtnState_PRESSED)
    if(CCBS.BS != BtnState_FOCUSED)
       set_conference_call_btn_state(BtnState_FOCUSED);

if(ACBS.BS != BtnState_INACTIVE)
  if(ACBS.BS != BtnState_ACTIVE)
     set_audio_call_btn_state(BtnState_ACTIVE);

if(VCBS.BS != BtnState_INACTIVE)
  if(VCBS.BS != BtnState_ACTIVE)
     set_video_call_btn_state(BtnState_ACTIVE);

if(ADCBS.BS != BtnState_INACTIVE)
  if(ADCBS.BS != BtnState_ACTIVE)
     set_add_contact_btn_state(BtnState_ACTIVE);
}
//---------------------------------------------------------------------------
void __fastcall TEnterpriseSubscList::Make_ConferenceCall()
{
if(Panel_Find->Visible)
  {
  TDBData dbd;
  if(SearchStruct.get_db_data_by_row(dbd, DrawGrid_Find->Row))
    {
    SCI.selected_name = dbd.s_1;
    string full_name  = dbd.s_5 + WS + dbd.s_2 + WS + dbd.s_4;
    Label1->Caption   = full_name.c_str();
    }
  else
     return;
  }
if(SCI.selected_name != MainFormSLS->Sip->Account.get_user_name())
  {
  if(MainFormSLS->CC_Panel->Visible)
    {
    TCall_Panel* Panel = MainFormSLS->get_Call_Panel_By_Tag(MainFormSLS->CC_DrawGrid->Tag);
    if(Panel)
      {
      TContact Contact;
      if(MainFormSLS->Sip->Contacts.get_contact_copy_by_user_name(Contact, SCI.selected_name))
        {
        TConfCont ConfCont(Contact.get_id());
        ConfCont.user_name = Contact.name;
        if(!Panel->is_ccl_q_contact(ConfCont)) //not yet in queue to the conference
          {
           Panel->add_ccl_q_contact(ConfCont);
           MainFormSLS->CC_DrawGrid->Repaint();
          }
        }
      }
    }
  else
    {
    TCall_Panel* Call_Panel = MainFormSLS->get_First_Call_Panel();
    if(Call_Panel)
      {
      TContact Contact;
      if(MainFormSLS->Sip->Contacts.get_contact_copy_by_user_name(Contact, SCI.selected_name))
        {
        TConfCont ConfCont(Contact.get_id());
        ConfCont.user_name = Contact.name;
        if(!Call_Panel->is_ccl_q_contact(ConfCont)) //not yet in queue to the conference
          {
          Call_Panel->add_ccl_q_contact(ConfCont);
          MainFormSLS->AddToConference(Call_Panel);
          }
        }
      else //not contact from my contact list
        {
        TConfCont ConfCont(SCI.selected_name);  //ConfCont.user_name = SCI.selected_name inside constructor of TConfCont
        ConfCont.from_enterprise_db = true;
        ConfCont.full_name          = SCI.selected_full_name;
        if(!Call_Panel->is_ccl_q_contact(ConfCont)) //not yet in queue to the conference
          {
          Call_Panel->add_ccl_q_contact(ConfCont);
          MainFormSLS->AddToConference(Call_Panel);
          }
        }
      }
    else
      Make_AudioCall();
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TEnterpriseSubscList::ConferenceCallPanel2MouseDown(
      TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
if(CCBS.BS != BtnState_INACTIVE)
   set_conference_call_btn_state(BtnState_PRESSED);
}
//---------------------------------------------------------------------------
void __fastcall TEnterpriseSubscList::Label_ConferenceCallMouseDown(
      TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
if(CCBS.BS != BtnState_INACTIVE)
   set_conference_call_btn_state(BtnState_PRESSED);
}
//---------------------------------------------------------------------------
void __fastcall TEnterpriseSubscList::Img_ConferenceCallMouseDown(
      TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
if(CCBS.BS != BtnState_INACTIVE)
   set_conference_call_btn_state(BtnState_PRESSED);
}
//---------------------------------------------------------------------------
void __fastcall TSubcrDBParsThread::Proc_Ack__REQ_START_SUBSCR_DATA(TServDBMsg& sdbm)
{
#ifdef SubscDB_LogParsedPacket
string log;
#endif
TDBData dbd;
if(sdbm.status == 0x10)
  {
  esl->UPDATE_TRANSACTION_TIME_STMP(sdbm);
  while(!sdbm.q.empty())
       {
       TServDBPar sdbp = sdbm.q.front();
       sdbm.q.pop();
       switch(sdbp.prm_type){
              case 1:if(sdbp.idt == IapDataType_String)
                       {
                       dbd.s_2 = sdbp.s;   //full_name
                       #ifdef SubscDB_LogParsedPacket
                       log += "\nfull_name: \"" + sdbp.s + "\"";
                       #endif
                       }
                     break;
              case 2:if(sdbp.idt == IapDataType_Int4)
                       {
                       dbd.u_1 = sdbp.u;
                       #ifdef SubscDB_LogParsedPacket
                       log += "\ncos:" + inttostr(sdbp.u) + "\n";
                       #endif
                       }
                     break;
              case 3:if(sdbp.idt == IapDataType_Nested)
                       __get_subscr_data(sdbp);
                     break;
             }
       }
  }
#ifdef SubscDB_LogParsedPacket
LOG_ParsPacket(log);
#endif
TTransactionData td = esl->get_osl(sdbm.seq_number);
if(td.get_actual())
  {
  dbd.SDMT = ServDbMsgType_REQ_START_SUBSCR_DATA;
  dbd.s_1  = td.s_1;         //name
  esl->DBIExch.push(dbd);    //full_name for NSP ready
  ::PostMessage(MainFormSLS->Handle, CONTROL_MSG, WM_APP_MSG_WPARAM__DBI_DATA, WM_APP_MSG_LPARAM__NOPARAM); // Отобразить full_name -- сообщение окну MainFormSLS
  }
update_out_seq_list(sdbm);
::PostMessage(EnterpriseSubscList->DBIContacts.get_hwnd(), CONTROL_MSG, WM_APP_MSG_WPARAM__CLOSE_DB_CHANNEL, WM_APP_MSG_LPARAM__NOPARAM); //Закрыть DBI канал -- сообщение окну EnterpriseSubscList
}
//-----------------------------------------------------------------------------
void __fastcall TSubcrDBParsThread::Proc_Ack__MODIFY_CONTACT_LIST(TServDBMsg& sdbm)
{
#ifdef SubscDB_LogParsedPacket
string log;
#endif
TDBData dbd;
if(sdbm.status == 0x10)
  {
  esl->UPDATE_TRANSACTION_TIME_STMP(sdbm);
  while(!sdbm.q.empty())
       {
       TServDBPar sdbp = sdbm.q.front();
       sdbm.q.pop();
       switch(sdbp.prm_type){
             case 1:if(sdbp.idt == IapDataType_String)
                      {
                      dbd.s_1 = sdbp.s;
                      #ifdef SubscDB_LogParsedPacket
                      log += "\ntime_stmp: \"" + sdbp.s + "\"\n";
                      #endif
                      }
                    break;
             }
       }
  dbd.SDMT = ServDbMsgType_MODIFY_CONTACT_LIST;
  esl->DBIExch.push(dbd);    //time_stmp for contact list
  ::PostMessage(MainFormSLS->Handle, CONTROL_MSG, WM_APP_MSG_WPARAM__DBI_DATA, WM_APP_MSG_LPARAM__NOPARAM);
  }
#ifdef SubscDB_LogParsedPacket
LOG_ParsPacket(log);
#endif
update_out_seq_list(sdbm);
}
//------------------------------------------------------------------------------
void __fastcall TSubcrDBParsThread::Proc_Ack__GET_TIMESTAMP(TServDBMsg& sdbm)
{
#ifdef SubscDB_LogParsedPacket
string log;
#endif
TDBData dbd;
if(sdbm.status == 0x10)
  {
  esl->UPDATE_TRANSACTION_TIME_STMP(sdbm);
  while(!sdbm.q.empty())
       {
       TServDBPar sdbp = sdbm.q.front();
       sdbm.q.pop();
       switch(sdbp.prm_type){
             case 1:if(sdbp.idt == IapDataType_String)
                      {
                      dbd.s_1 = sdbp.s;
                      #ifdef SubscDB_LogParsedPacket
                      log += "\ntime_stmp: \"" + sdbp.s + "\"\n";
                      #endif
                      }
                    break;
             }
       }
  dbd.SDMT = ServDbMsgType_GET_TIMESTAMP;
  esl->DBIExch.push(dbd);    //time_stmp for contact list
::PostMessage(MainFormSLS->Handle, CONTROL_MSG, WM_APP_MSG_WPARAM__DBI_DATA, WM_APP_MSG_LPARAM__NOPARAM);
  }
#ifdef SubscDB_LogParsedPacket
LOG_ParsPacket(log);
#endif
update_out_seq_list(sdbm);
}
//-----------------------------------------------------------------------------
void __fastcall TSubcrDBParsThread::update_out_seq_list(const TServDBMsg& sdbm)
{
queue<unsigned> deleted_seq_number;
esl->del_osl(sdbm.seq_number, deleted_seq_number);
esl->log_deleted_seq_numbers(deleted_seq_number);
}
//-----------------------------------------------------------------------------
#ifdef SubscDB_LogParsedPacket
void __fastcall TSubcrDBParsThread::LOG_ParsPacket(const string& log)
{
TEventLogThread* elt = getLog();
if(elt)
  {
  if(!log.empty())
     elt->FputEvt(log,1);
  }
}
#endif
//-----------------------------------------------------------------------------
void __fastcall TEnterpriseSubscList::GET_PERSONAL_CONTACT_LIST(const string& name)
{
TTransactionData data;
data.s_1 = name;
TOutBlock* ob = create_start_request_block(data, ServDbMsgType_GET_PERSONAL_CONTACT_LIST);
if(ob)
  {
  ob->pack_string_type(1,name);
//  ob->pack_fixed_type(2,IapDataType_Int1,10);
  ob->pack_fixed_type(2,IapDataType_Int1,3);
  ob->pack_header_REQ();
  SEND_REQUEST(ob);
  }
}
//-----------------------------------------------------------------------------
void __fastcall TEnterpriseSubscList::GET_PERSONAL_CITY_PHONE_LIST(const string& name, unsigned seq_number_1)
{
TTransactionData data;
data.set_seq_num_1(seq_number_1);   //this is seq_num of  get_personal_contact_list
data.s_1       = name;
TOutBlock* ob  = create_start_request_block(data, ServDbMsgType_GET_PERSONAL_CITY_PHONE_LIST);
if(ob)
  {
  ob->pack_string_type(1,name);
  ob->pack_fixed_type(2,IapDataType_Int1,3);
  ob->pack_header_REQ();
  SEND_REQUEST(ob);
  }
}
//-----------------------------------------------------------------------------
void __fastcall TTempContList::__clear()
{
while(!__q.empty())
     {
     TContact* contact = __q.front();
   __q.pop();
     delete contact;
     }
}
//-----------------------------------------------------------------------------
void __fastcall TSubcrDBParsThread::end_of_client_contact_list(unsigned seq_num)
{
string name = esl->get_trans_user(seq_num);
if(!name.empty())
   esl->GET_PERSONAL_CITY_PHONE_LIST(name, seq_num);
}
//------------------------------------------------------------------------------
void __fastcall TSubcrDBParsThread::end_of_client_city_phone_list(unsigned seq_num)
{
TDBData dbd;
dbd.u_1  = seq_num;
dbd.u_2  = esl->get_contact_list_seq_number(seq_num);
dbd.u_3  = 1;  //end of list
dbd.SDMT = ServDbMsgType_GET_PERSONAL_CITY_PHONE_LIST;
esl->DBIExch.push(dbd);
::PostMessage(MainFormSLS->Handle, CONTROL_MSG, WM_APP_MSG_WPARAM__DBI_DATA, WM_APP_MSG_LPARAM__NOPARAM);
}
//------------------------------------------------------------------------------



void __fastcall TEnterpriseSubscList::AudioCall_ImgMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
if(ACBS.BS != BtnState_INACTIVE)
 {
 if(X > 0)
   if(Y > 0)
     if(X < AudioCall_Img->Width)
       if(Y < AudioCall_Img->Height)
         {
         Make_AudioCall();
         set_audio_call_btn_state(BtnState_FOCUSED);
         return;
         }
 set_audio_call_btn_state(BtnState_ACTIVE);
 }
}
//---------------------------------------------------------------------------
void __fastcall TEnterpriseSubscList::VideoCall_ImgMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
if(VCBS.BS != BtnState_INACTIVE)
  {
  if(X > 0)
    if(Y > 0)
      if(X < VideoCall_Img->Width)
        if(Y < VideoCall_Img->Height)
          {
          set_video_call_btn_state(BtnState_FOCUSED);
          Make_VideoCall();
          return;
          }
  set_video_call_btn_state(BtnState_ACTIVE);
  }
}
//---------------------------------------------------------------------------
void __fastcall TEnterpriseSubscList::Conference_ImgMouseUp(
      TObject *Sender, TMouseButton Button, TShiftState Shift, int X,
      int Y)
{
if(CCBS.BS != BtnState_INACTIVE)
 {
 if(X > 0)
   if(Y > 0)
     if(X < Conference_Img->Width)
       if(Y < Conference_Img->Height)
         {
         Make_ConferenceCall();
         set_conference_call_btn_state(BtnState_FOCUSED);
         return;
         }
 set_conference_call_btn_state(BtnState_ACTIVE);
 }
}
//---------------------------------------------------------------------------
void __fastcall TEnterpriseSubscList::AddContact_ImgMouseUp(
      TObject *Sender, TMouseButton Button, TShiftState Shift, int X,
      int Y)
{
if(ADCBS.BS != BtnState_INACTIVE)
 {
 if(X > 0)
   if(Y > 0)
     if(X < AddContact_Img->Width)
       if(Y < AddContact_Img->Height)
         {
         set_add_contact_btn_state(BtnState_FOCUSED);
         add_to_contact_list();
         return;
         }
 set_add_contact_btn_state(BtnState_ACTIVE);
 }
}
//---------------------------------------------------------------------------
void __fastcall TEnterpriseSubscList::AddContact_ImgMouseDown(
      TObject *Sender, TMouseButton Button, TShiftState Shift, int X,
      int Y)
{
if(ADCBS.BS != BtnState_INACTIVE)
   set_add_contact_btn_state(BtnState_PRESSED);
}
//---------------------------------------------------------------------------
void __fastcall TEnterpriseSubscList::AddContact_ImgMouseMove(
      TObject *Sender, TShiftState Shift, int X, int Y)
{
if(ADCBS.BS != BtnState_INACTIVE)              //Add Contact
  {
  if(ADCBS.BS != BtnState_PRESSED)
    if(ADCBS.BS != BtnState_FOCUSED)
       set_add_contact_btn_state(BtnState_FOCUSED);
  set_img_cursor_type((TImage*)Sender);
  }

if(ACBS.BS != BtnState_INACTIVE)               //Audio Call
  if(ACBS.BS != BtnState_ACTIVE)
     set_audio_call_btn_state(BtnState_ACTIVE);

if(VCBS.BS != BtnState_INACTIVE)               //Video Call
  if(VCBS.BS != BtnState_ACTIVE)
     set_video_call_btn_state(BtnState_ACTIVE);

if(CCBS.BS != BtnState_INACTIVE)               //Conference Call
  if(CCBS.BS != BtnState_ACTIVE)
     set_conference_call_btn_state(BtnState_ACTIVE);
}
//---------------------------------------------------------------------------

void __fastcall TEnterpriseSubscList::Conference_ImgMouseMove(
      TObject *Sender, TShiftState Shift, int X, int Y)
{
if(CCBS.BS != BtnState_INACTIVE)
  {
  if(CCBS.BS != BtnState_PRESSED)
    if(CCBS.BS != BtnState_FOCUSED)
       set_conference_call_btn_state(BtnState_FOCUSED);
  set_img_cursor_type((TImage*)Sender);
  }
  
if(ACBS.BS != BtnState_INACTIVE)
  if(ACBS.BS != BtnState_ACTIVE)
     set_audio_call_btn_state(BtnState_ACTIVE);

if(VCBS.BS != BtnState_INACTIVE)
  if(VCBS.BS != BtnState_ACTIVE)
     set_video_call_btn_state(BtnState_ACTIVE);

if(ADCBS.BS != BtnState_INACTIVE)
  if(ADCBS.BS != BtnState_ACTIVE)
     set_add_contact_btn_state(BtnState_ACTIVE);
}
//---------------------------------------------------------------------------
void __fastcall TEnterpriseSubscList::Conference_ImgMouseDown(
      TObject *Sender, TMouseButton Button, TShiftState Shift, int X,
      int Y)
{
if(CCBS.BS != BtnState_INACTIVE)
   set_conference_call_btn_state(BtnState_PRESSED);
}
//---------------------------------------------------------------------------
void __fastcall TEnterpriseSubscList::VideoCall_ImgMouseDown(
      TObject *Sender, TMouseButton Button, TShiftState Shift, int X,
      int Y)
{
if(VCBS.BS != BtnState_INACTIVE)
   set_video_call_btn_state(BtnState_PRESSED);
}
//---------------------------------------------------------------------------

void __fastcall TEnterpriseSubscList::VideoCall_ImgMouseMove(
      TObject *Sender, TShiftState Shift, int X, int Y)
{
if(VCBS.BS != BtnState_INACTIVE)
  {
  if(VCBS.BS != BtnState_PRESSED)
    if(VCBS.BS != BtnState_FOCUSED)
       set_video_call_btn_state(BtnState_FOCUSED);
  set_img_cursor_type((TImage*)Sender);
  }
  
if(ACBS.BS != BtnState_INACTIVE)
  if(ACBS.BS != BtnState_ACTIVE)
     set_audio_call_btn_state(BtnState_ACTIVE);

if(CCBS.BS != BtnState_INACTIVE)               //Conference Call
  if(CCBS.BS != BtnState_ACTIVE)
     set_conference_call_btn_state(BtnState_ACTIVE);

if(ADCBS.BS != BtnState_INACTIVE)
  if(ADCBS.BS != BtnState_ACTIVE)
     set_add_contact_btn_state(BtnState_ACTIVE);
}
//---------------------------------------------------------------------------
void __fastcall TEnterpriseSubscList::AudioCall_ImgMouseDown(
      TObject *Sender, TMouseButton Button, TShiftState Shift, int X,
      int Y)
{
if(ACBS.BS != BtnState_INACTIVE)
   set_audio_call_btn_state(BtnState_PRESSED);
}
//---------------------------------------------------------------------------
void __fastcall TEnterpriseSubscList::AudioCall_ImgMouseMove(
      TObject *Sender, TShiftState Shift, int X, int Y)
{
if(ACBS.BS != BtnState_INACTIVE)
  {
  if(ACBS.BS != BtnState_PRESSED)
    if(ACBS.BS != BtnState_FOCUSED)
       set_audio_call_btn_state(BtnState_FOCUSED);
  set_img_cursor_type((TImage*)Sender);
  }

if(VCBS.BS != BtnState_INACTIVE)
  if(VCBS.BS != BtnState_ACTIVE)
     set_video_call_btn_state(BtnState_ACTIVE);

if(CCBS.BS != BtnState_INACTIVE)               //Conference Call
  if(CCBS.BS != BtnState_ACTIVE)
     set_conference_call_btn_state(BtnState_ACTIVE);

if(ADCBS.BS != BtnState_INACTIVE)
  if(ADCBS.BS != BtnState_ACTIVE)
     set_add_contact_btn_state(BtnState_ACTIVE);
}
//---------------------------------------------------------------------------
void __fastcall TEnterpriseSubscList::Panel1Resize(TObject *Sender)
{
  MarginLine->Canvas->Brush->Color = clWhite;
  MarginLine->Width    = Width - 40;
  int w = MarginLine->Width; int h = 1;
  TRBitMap rbmp(w, h, 0xC0C0C0); //0x00FFF2EA;
  rbmp.prepare_line_img();
  MarginLine->Picture->Bitmap = rbmp.bmp;
}
//---------------------------------------------------------------------------
__fastcall TBaseDataBlock::TBaseDataBlock(DbReqTypeBlockType DBT,ExhangeType ET){
dbt          = DBT;
et           = ET;
prms         = 0;
seq_number   = 0;
msg_type     = 0;
status       = 0x10;
switch(et){
      case ExhangeType__req:
           v.resize(11,0);
           break;
      case ExhangeType__evtack:
           v.resize(12,0);
           break;
      case ExhangeType__nested_par:
           v.resize(4,0);
           break;
      }
}
//------------------------------------------------------------------------------
__fastcall TNestedParameter::~TNestedParameter(){
while(!q.empty())
     {
     TSimpleParameter* sp = q.front();
     q.pop();
     if(sp)
       delete sp;
     }
}
//------------------------------------------------------------------------------
void __fastcall TEnterpriseSubscList::FormCreate(TObject *Sender)
{
if(MainFormSLS->ofs)
  if(MainFormSLS->ofs->elt)
    if(MainFormSLS->ofs->elt->getlog())
      {
      string TimeStr;
      TDateTime DateTime = DateTime.CurrentDateTime();
      exsDateTime(DateTime,TimeStr);
      string str = "\n" + (string)TimeStr + " TEnterpriseSubscList_CREATED! " + "\n";
      MainFormSLS->ofs->elt->FputEvt(str, 1);
      }
}
//---------------------------------------------------------------------------
int  __fastcall TEnterpriseSubscList::__set_Panel_Find_Height()
{
return  Height - 100;
}
//------------------------------------------------------------------------------
void __fastcall TEnterpriseSubscList::Find_ImgMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
if( Panel_Find->Visible )
   close_find_panel();
else
   {
   MarginLine->Visible  = false;
   Panel_Find->Width    = Width;
   Panel_Find->Height   = __set_Panel_Find_Height();
   Panel_Find->Visible  = true;
   SearchStruct.deactivate_close_btn();
   Edit_Find->SetFocus();
   }
}
//---------------------------------------------------------------------------
void __fastcall TEnterpriseSubscList::close_find_panel()
{
Panel_Find->Visible = false;
MarginLine->Visible = true;
SearchStruct.last_request_clear();
SearchStruct.set_last_send_seq_number(0);
}
//---------------------------------------------------------------------------
void __fastcall TEnterpriseSubscList::Panel_FindResize(TObject *Sender)
{
Image_Find_21_21->Left = Edit_Find->Left   + Edit_Find->Width + 10;
Image_Close_Find->Left = Panel_Find->Width - 51; 
DrawGrid_Find->Top     = 35;
DrawGrid_Find->Left    = 0;
DrawGrid_Find->Width   = Panel_Find->Width  - 15;
DrawGrid_Find->Height  = Panel_Find->Height - 35;
DrawGrid_Find->ColWidths[0] = DrawGrid_Find->Width;
}
//---------------------------------------------------------------------------
//-- Без перевода Ansi в UTF8
//---------------------------------------------------------------------------
void __fastcall TEnterpriseSubscList::Image_Find_21_21MouseUp(
      TObject *Sender, TMouseButton Button, TShiftState Shift, int X,
      int Y)
{
Create_Start_SearchRequest();
}
//---------------------------------------------------------------------------
void __fastcall TSearchStruct::push_new_arrival(TDBData& dbd)
{
::EnterCriticalSection(&__fdl_cs);
  __new_arrivals.push_back(dbd);
::LeaveCriticalSection(&__fdl_cs);
}
//-----------------------------------------------------------------------------
unsigned __fastcall TSearchStruct::get_new_arrivals_count()
{
unsigned rv;
::EnterCriticalSection(&__fdl_cs);
  rv = __new_arrivals.size();
::LeaveCriticalSection(&__fdl_cs);
return rv;
}
//-----------------------------------------------------------------------------
void __fastcall TSearchStruct::__add_subsc_data(TDBData& sd)
{
::EnterCriticalSection(&__fdl_cs);
  __fdl.insert(TFoundDataList::value_type(__id++, sd));
::LeaveCriticalSection(&__fdl_cs);
}
//---------------------------------------------------------------------------
void __fastcall TSearchStruct::search_rezult_clear()
{
::EnterCriticalSection(&__fdl_cs);
  __new_arrivals.clear();
  __fdl.clear();
  __id = 0;
::LeaveCriticalSection(&__fdl_cs);
}
//----------------------------------------------------------------------------
void __fastcall TEnterpriseSubscList::DrawGrid_FindKeyDown(TObject *Sender,
      WORD &Key, TShiftState Shift)
{
if(Key == 38) //Up
 if(DrawGrid_Find->RowCount > 0)
   if(DrawGrid_Find->Row == 0)
      Edit_Find->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TEnterpriseSubscList::Edit_FindKeyDown(TObject *Sender,
      WORD &Key, TShiftState Shift)
{
if(Key == 40) //Down
  DrawGrid_Find->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TEnterpriseSubscList::Edit_FindKeyUp(TObject *Sender,
      WORD &Key, TShiftState Shift)
{
if(Key == 13)//Enter
  Create_Start_SearchRequest();
}
//---------------------------------------------------------------------------
void __fastcall TEnterpriseSubscList::Create_Start_SearchRequest()
{
AnsiString S = Edit_Find->Text;
if(!S.IsEmpty())
  {
  string req = S.c_str();
  if(SearchStruct.get_last_request() != req)
    {
    SearchStruct.search_rezult_clear();
    SearchStruct.set_last_request(req);
    SearchStruct.set_transaction_complete(false);
    TTransactionData data;
    data.u_2 = RESPONCE_RECORD_COUNT;
    TOutBlock* ob = create_start_request_block(data, ServDbMsgType_FIND);
    if(ob)
      {
      SearchStruct.set_last_send_seq_number( ob->get_seq_number() );
      ob->pack_string_type(1, req);
      ob->pack_fixed_type(2, IapDataType_Int4, 0); // 0 -  LastRcvdId
      ob->pack_fixed_type(3, IapDataType_Int1, RESPONCE_RECORD_COUNT); //count = 10
      ob->pack_header_REQ();
      SEND_REQUEST(ob);
      }
    }
  }
}
//---------------------------------------------------------------------------------------------------------------
void __fastcall TEnterpriseSubscList::check_end_of_search_transaction(unsigned seq_num, unsigned found_mathes, queue<unsigned>& q)
{
::EnterCriticalSection(&osl_cs);
  TOutSeqList::iterator it = osl.find(seq_num);
  if(it != osl.end())
    {
    if(found_mathes < (*it).second.u_2)  // Найдено соответствий меньше, чем заказано в одном запросе, следовательно транзакция завершена
      {
      q.push(seq_num);                  //queue with values of deleted seq_number (for log)
      osl.erase(it);
      SearchStruct.set_transaction_complete(true);
      SearchStruct.set_last_send_seq_number(0);
      }
    }
::LeaveCriticalSection(&osl_cs);
}
//---------------------------------------------------------------------------------------------------------------
unsigned __fastcall TSearchStruct::get_list_size()
{
unsigned rv;
::EnterCriticalSection(&__fdl_cs);
  rv = __fdl.size();
::LeaveCriticalSection(&__fdl_cs);
return rv;
}
//---------------------------------------------------------------------------------------------------------------
void __fastcall TSearchStruct::copy_search_result()
{
::EnterCriticalSection(&__fdl_cs);
  while(!__new_arrivals.empty()){
        TDBData dbd = __new_arrivals.front();
      __new_arrivals.pop_front();
      __add_subsc_data(dbd);
       }
::LeaveCriticalSection(&__fdl_cs);
}
//---------------------------------------------------------------------------------------------------------------
bool __fastcall TSearchStruct::get_db_data_by_row(TDBData& dbd, int Row)
{
bool rv = false;
::EnterCriticalSection(&__fdl_cs);
  TFoundDataList::iterator it = __fdl.find(Row);
  if(it != __fdl.end())
    {
    dbd = (*it).second;
    rv = true;
    }
::LeaveCriticalSection(&__fdl_cs);
return rv;
}
//------------------------------------------------------------------------------
void __fastcall TSearchStruct::set_next_requested(int Row)
{
::EnterCriticalSection(&__fdl_cs);
  TFoundDataList::iterator it = __fdl.find(Row);
  if(it != __fdl.end())
    (*it).second.next_rows_requested = true;
::LeaveCriticalSection(&__fdl_cs);
}
//------------------------------------------------------------------------------
void __fastcall TEnterpriseSubscList::DrawGrid_FindDrawCell(
      TObject *Sender, int ACol, int ARow, TRect &Rect,
      TGridDrawState State)
{
string last_req = SearchStruct.get_last_request();
DrawGrid_Find->Canvas->Font->Size = 10;
if(SearchStruct.get_list_size())
  {
  if(State.Contains(gdSelected))
    {
    DrawGrid_Find->Canvas->Brush->Color = clActiveCaption;   //clBlue;// clBackground;
    DrawGrid_Find->Canvas->Font->Color  = clWhite;
    DrawGrid_Find->Canvas->FillRect(Rect);
  //  DrawGrid_Find->Canvas->DrawFocusRect(Rect);
    }
  else
    {
    DrawGrid_Find->Canvas->Brush->Color = clWhite;
    DrawGrid_Find->Canvas->Font->Color  = (TColor)get_turquoise_color(); //(TColor)0x6D6D6D;
    DrawGrid_Find->Canvas->FillRect(Rect);
  //  DrawGrid_Find->Canvas->DrawFocusRect(Rect);
    }
  }
TDBData dbd;
if(SearchStruct.get_db_data_by_row(dbd, ARow))
  {
  int TOP_0    = Rect.Top + 5; // For NickName
  int TOP_1    = TOP_0 + 15;   // For FullName
  int TOP_2    = TOP_1 + 15;   // For JobPosition
//  int TOP_1    = Rect.Top + 5;
  int INTERVAL = 10;
  int ST_1     = 5;

  AnsiString NickName    = dbd.s_1.c_str();
  AnsiString Family      = dbd.s_5.c_str();
  AnsiString FirstName   = dbd.s_2.c_str();
  AnsiString SecondName  = dbd.s_4.c_str();
  AnsiString JobPosition = dbd.s_3.c_str();

  unsigned last_req_len  = last_req.length();
  AnsiString Last_Req    = last_req.c_str();

  DrawGrid_Find->Canvas->TextOut( ST_1, TOP_0, NickName);

  bool printed_1 = false;
  if(dbd.s_5.find(last_req) == 0)         // Family
    {
    if(last_req_len < dbd.s_5.length()){
      string end_s = dbd.s_5.substr(last_req_len);
      DrawGrid_Find->Canvas->Font->Style = DrawGrid_Find->Canvas->Font->Style << fsBold << fsUnderline;
      DrawGrid_Find->Canvas->TextOut( ST_1, TOP_1, Last_Req);
      int W = DrawGrid_Find->Canvas->TextWidth(Last_Req);
      DrawGrid_Find->Canvas->Font->Style = DrawGrid_Find->Canvas->Font->Style >> fsBold >> fsUnderline;
      DrawGrid_Find->Canvas->TextOut( ST_1 + W, TOP_1, end_s.c_str());
      printed_1 = true;
      }
    }
  if(!printed_1)
     DrawGrid_Find->Canvas->TextOut( ST_1, TOP_1, Family );
  int W_1  = DrawGrid_Find->Canvas->TextWidth(Family);
  int ST_2 = ST_1 + W_1 + INTERVAL;


  bool printed_2 = false;
  if(dbd.s_2.find(last_req) == 0){         // FirstName
    string end_s = dbd.s_2.substr(last_req_len);
    DrawGrid_Find->Canvas->Font->Style = DrawGrid_Find->Canvas->Font->Style << fsBold << fsUnderline;
    DrawGrid_Find->Canvas->TextOut( ST_2, TOP_1, Last_Req);
    int W = DrawGrid_Find->Canvas->TextWidth(Last_Req);
    DrawGrid_Find->Canvas->Font->Style = DrawGrid_Find->Canvas->Font->Style >> fsBold >> fsUnderline;
    DrawGrid_Find->Canvas->TextOut( ST_2 + W, TOP_1, end_s.c_str());
    printed_2 = true;
    }
  if(!printed_2)
     DrawGrid_Find->Canvas->TextOut( ST_2, TOP_1, FirstName );
  int W_2  = DrawGrid_Find->Canvas->TextWidth(FirstName);
  int ST_3 = ST_2 + W_2 + INTERVAL;


  bool printed_3 = false;
  if(dbd.s_4.find(last_req) == 0){         // SecondName
     string end_s = dbd.s_4.substr(last_req_len);
     DrawGrid_Find->Canvas->Font->Style = DrawGrid_Find->Canvas->Font->Style << fsBold << fsUnderline;
     DrawGrid_Find->Canvas->TextOut( ST_3, TOP_1, Last_Req);
     int W = DrawGrid_Find->Canvas->TextWidth(Last_Req);
     DrawGrid_Find->Canvas->Font->Style = DrawGrid_Find->Canvas->Font->Style >> fsBold >> fsUnderline;
     DrawGrid_Find->Canvas->TextOut( ST_3 + W, TOP_1, end_s.c_str());
     printed_3 = true;
    }
  if(!printed_3)
     DrawGrid_Find->Canvas->TextOut( ST_3, TOP_1, SecondName );

  bool printed_4 = false;
  if(dbd.s_3.find(last_req) == 0){         // JobPosition
    string end_s = dbd.s_3.substr(last_req_len);
    DrawGrid_Find->Canvas->Font->Style = DrawGrid_Find->Canvas->Font->Style << fsBold << fsUnderline;
    DrawGrid_Find->Canvas->TextOut( ST_1, TOP_2, Last_Req);
    int W = DrawGrid_Find->Canvas->TextWidth(Last_Req);
    DrawGrid_Find->Canvas->Font->Style = DrawGrid_Find->Canvas->Font->Style >> fsBold >> fsUnderline;
    DrawGrid_Find->Canvas->TextOut( ST_1 + W, TOP_2, end_s.c_str());
    printed_4 = true;
    }
  if(!printed_4)
     DrawGrid_Find->Canvas->TextOut( ST_1, TOP_2, JobPosition );


  if(ARow == DrawGrid_Find->RowCount - 1)   //Последняя строка ?
    if(!SearchStruct.transaction_completed())
      {
      unsigned current_seq_number = SearchStruct.get_last_send_seq_number();
      if(current_seq_number)
        {
        unsigned LastRcvdRecordId   =  dbd.u_0;
        if(!dbd.next_rows_requested)
          {
          SearchStruct.set_next_requested(ARow);
          TOutBlock* ob = create_next_request_block(ServDbMsgType_FIND, current_seq_number);
          if(ob){
             ob->pack_string_type(1, SearchStruct.get_last_request());
             ob->pack_fixed_type(2,  IapDataType_Int4, ++LastRcvdRecordId);
             ob->pack_fixed_type(3,  IapDataType_Int1, RESPONCE_RECORD_COUNT); //count = 10
             ob->pack_header_REQ();
             SEND_REQUEST(ob);
             }
          }
        }
      }
  } // if(SearchStruct.get_db_data_by_row(dbd, ARow))
else
  {
  if(!SearchStruct.get_list_size())
    {
    DrawGrid_Find->RowCount = 1;
    DrawGrid_Find->Canvas->Brush->Color = clWhite;
    DrawGrid_Find->Canvas->FillRect(Rect);
    }
  }
}
//------------------------------------------------------------------------------
void __fastcall TEnterpriseSubscList::DrawGrid_FindMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
set_audio_call_btn_state(BtnState_ACTIVE);
set_video_call_btn_state(BtnState_ACTIVE);
set_conference_call_btn_state(BtnState_ACTIVE);
set_add_contact_btn_state(BtnState_ACTIVE);
}
//---------------------------------------------------------------------------
void __fastcall TEnterpriseSubscList::Image_Close_FindMouseUp(
      TObject *Sender, TMouseButton Button, TShiftState Shift, int X,
      int Y)
{
close_find_panel();
}
//---------------------------------------------------------------------------
void __fastcall TEnterpriseSubscList::Image_Close_FindMouseMove(
      TObject *Sender, TShiftState Shift, int X, int Y)
{
SearchStruct.CSS.BS = BtnState_FOCUSED;
RBitMap::change_color(0x808080, 0xFFFFFF, Image_Close_Find);
RBitMap::change_color(0xF0F0F0, 0x0000F0, Image_Close_Find);
}
//---------------------------------------------------------------------------
void __fastcall TSearchStruct::deactivate_close_btn()
{
if(CSS.BS == BtnState_FOCUSED){
   CSS.BS = BtnState_ACTIVE;
   RBitMap::change_color( 0xFFFFFF, 0x808080, EnterpriseSubscList->Image_Close_Find);
   RBitMap::change_color( 0x0000F0, 0xF0F0F0, EnterpriseSubscList->Image_Close_Find);
  }
}
//---------------------------------------------------------------------------
void __fastcall TEnterpriseSubscList::Panel_FindMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
SearchStruct.deactivate_close_btn();
}
//---------------------------------------------------------------------------
void __fastcall TEnterpriseSubscList::DrawGrid_FindMouseMove(
      TObject *Sender, TShiftState Shift, int X, int Y)
{
SearchStruct.deactivate_close_btn();
}
//---------------------------------------------------------------------------

