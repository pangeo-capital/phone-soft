//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "WinRDefs.h"

#include "SipClient_Unit.h"
#include "transmit_file.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

//int fsz_send=0;
//int psz_send=0;
//----------------------------------------------------------------------------
void send_call_back(const tf_common_event& Event) {
try{
string TimeStr;
TDateTime DateTime = DateTime.CurrentDateTime();
exsTime(DateTime,TimeStr);
string s = "\n" + TimeStr;
switch (Event.tag) {
    case TF_TAG_ERROR_EVENT:
      s +=  " ***send_call_back*** id : tag " + inttostr(Event.id) + " : " + inttostr(Event.tag) + " TF_TAG_ERROR_EVENT";
      break;
    case TF_TAG_UPLOAD_INIT_EVENT:
    {
      s += " ***send_call_back*** id : tag " + inttostr(Event.id) + " : " + inttostr(Event.tag) + " TF_TAG_UPLOAD_INIT_EVENT";
      tf_upload_init_event& e=(tf_upload_init_event&)Event;
      TExchBuf* buf = new TExchBuf(WM_APP_MSG_WPARAM__FILE_TRANS_INIT_MSG);
      if(buf)
        {
        buf->tag = e.id;
        MainFormSLS->filetrans_exchlst_insert(buf);
        ::PostMessage(MainFormSLS->Sip->getMFHandle(), FILE_TRANSFER_MSG, WM_APP_MSG_WPARAM__FILE_TRANS_INIT_MSG, WM_APP_MSG_LPARAM__READLIST);
        }
      break;
    }
    case TF_TAG_UPLOAD_START_EVENT:{
      s += " ***send_call_back*** id : tag " + inttostr(Event.id) + " : " + inttostr(Event.tag) + " TF_TAG_UPLOAD_START_EVENT";
      TExchBuf* buf = new TExchBuf(WM_APP_MSG_WPARAM__FILE_TRANS_START_MSG);
      if(buf)
        {
        buf->tag = Event.id;
        ::PostMessage(MainFormSLS->Sip->getMFHandle(), FILE_TRANSFER_MSG, WM_APP_MSG_WPARAM__FILE_TRANS_START_MSG, WM_APP_MSG_LPARAM__READLIST);
        }
      break;
      }
    case TF_TAG_UPLOAD_PENDING_EVENT:
    {
      s += " ***send_call_back*** id : tag " + inttostr(Event.id) + " : " + inttostr(Event.tag) + " TF_TAG_UPLOAD_PENDING_EVENT";
      tf_upload_pending_event& e=(tf_upload_pending_event&)Event;
      s += " offset: " + inttostr(e.offset);
      TExchBuf* buf = new TExchBuf(WM_APP_MSG_WPARAM__FILE_PENDING_MSG);
      if(buf)
        {
        buf->tag   = Event.id;
        buf->tag_1 = e.offset;
        MainFormSLS->filetrans_exchlst_insert(buf);
        ::PostMessage(MainFormSLS->Sip->getMFHandle(), FILE_TRANSFER_MSG, WM_APP_MSG_WPARAM__FILE_PENDING_MSG, WM_APP_MSG_LPARAM__READLIST);
        }
      break;
    }
    case TF_TAG_UPLOAD_COMPLETE_EVENT:{
      s += " ***send_call_back*** id : tag " + inttostr(Event.id) + " : " + inttostr(Event.tag) + " TF_TAG_UPLOAD_COMPLETE_EVENT";
      TExchBuf* buf = new TExchBuf(WM_APP_MSG_WPARAM__FILE_TRANS_END);
      if(buf)
        {
        buf->tag = Event.id;
        MainFormSLS->filetrans_exchlst_insert(buf);
        ::PostMessage(MainFormSLS->Sip->getMFHandle(), FILE_TRANSFER_MSG, WM_APP_MSG_WPARAM__FILE_TRANS_END, WM_APP_MSG_LPARAM__READLIST);
        }
      break;
      }
    default:
      s += " ***send_call_back*** id : tag " + inttostr(Event.id) + " : " + inttostr(Event.tag) + " default";
      break;
  }
if(!s.empty())
  MainFormSLS->Sip->Log(s);
}
catch(Exception& e){exsSstEXCEPTION(MainFormSLS->ofs->elt,"__send_call_back::Execute",e);}
};
//----------------------------------------------------------------

int fsz_recv=0;
int psz_recv=0;
//-----------------------------------------------------------------
void recv_call_back(const tf_common_event& Event) {
try{
string TimeStr;
TDateTime DateTime = DateTime.CurrentDateTime();
exsTime(DateTime,TimeStr);
string s = "\n" + TimeStr;
switch (Event.tag) {
    case TF_TAG_ERROR_EVENT:
      s += " ***recv_call_back*** id : tag " + inttostr(Event.id) + " : " + inttostr(Event.tag) + " TF_TAG_ERROR_EVENT";
      break;
    case TF_TAG_DOWNLOAD_INIT_EVENT:
    {
      s += " ***recv_call_back*** id : tag " + inttostr(Event.id) + " : " + inttostr(Event.tag) + " TF_TAG_DOWNLOAD_INIT_EVENT";
      tf_download_init_event& e=(tf_download_init_event&)Event;
      fsz_recv=e.file_size;
      TCall_Panel* panel = MainFormSLS->get_Call_Panel_By_Sid(Event.id);
      if(panel)
        {
        std::string f = panel->TFP.tfa.path;
        if(panel->TFP.tfa.file_name.empty())
           f.append(e.file_name, e.fn_len);
        else
           f.append(panel->TFP.tfa.file_name);
        panel->TFP.tfa.complete_file_name = f;
        tf_receive_file(Event.id, f.c_str(), f.size());
        }
      break;
    }
    case TF_TAG_DOWNLOAD_START_EVENT:
      s += " ***recv_call_back*** id : tag " + inttostr(Event.id) + " : " + inttostr(Event.tag) + " TF_TAG_DOWNLOAD_START_EVENT";
      break;

    case TF_TAG_DOWNLOAD_PENDING_EVENT: {
      s += " ***recv_call_back*** id : tag " + inttostr(Event.id) + " : " + inttostr(Event.tag) + " TF_TAG_DOWNLOAD_PENDING_EVENT";
      tf_download_pending_event& e=(tf_download_pending_event&)Event;
      s += " offset: " + inttostr(e.offset);
      TExchBuf* buf = new TExchBuf(WM_APP_MSG_WPARAM__FILE_PENDING_MSG);
      if(buf)
        {
        buf->tag   = Event.id;
        buf->tag_1 = e.offset;
        MainFormSLS->filetrans_exchlst_insert(buf);
        ::PostMessage(MainFormSLS->Sip->getMFHandle(), FILE_TRANSFER_MSG, WM_APP_MSG_WPARAM__FILE_PENDING_MSG, WM_APP_MSG_LPARAM__READLIST);
        }
      break;
    }

    case TF_TAG_DOWNLOAD_COMPLETE_EVENT:{
      s += " ***recv_call_back*** id : tag " + inttostr(Event.id) + " : " + inttostr(Event.tag) + " TF_TAG_DOWNLOAD_COMPLETE_EVENT";
      TExchBuf* buf = new TExchBuf(WM_APP_MSG_WPARAM__FILE_RECV_END);
      if(buf)
        {
        buf->tag = Event.id;
        MainFormSLS->filetrans_exchlst_insert(buf);
        ::PostMessage(MainFormSLS->Sip->getMFHandle(), FILE_TRANSFER_MSG, WM_APP_MSG_WPARAM__FILE_RECV_END, WM_APP_MSG_LPARAM__READLIST);
        }
      break;
      }
    default:
      s += " ***recv_call_back*** id : tag " + inttostr(Event.id) + " : " + inttostr(Event.tag) + " default";
  }
if(!s.empty())
  MainFormSLS->Sip->Log(s);
}
catch(Exception& e){exsSstEXCEPTION(MainFormSLS->ofs->elt,"__recv_call_back::Execute",e);}
};
//------------------------------------------------------------------------------
void __fastcall TTransmitFileThread::Execute()
{
try{
tf_set_handler(send_call_back);
int len = host.length();
string s = get_file_name();
tf_set_params(host.c_str(), len, port);
bool a =tf_send_file(s.c_str(), s.size());
if(a)
while(!Terminated)
     {
     if(cancel_req)
       {
       cancel_req = false;
       tf_send_file_cancel(get_sid());
       }
     tf_rcvAndDisp();
     Sleep(1);
     }
}
catch(Exception& e){exsSstEXCEPTION(*eltp,"__TTransmitFileThread::Execute",e);}
}
//----------------------------------------------------------------------------
void __fastcall TReceiveFileThread::Execute()
{
try{
tf_set_handler(recv_call_back);
int len = host.length();
tf_set_params(host.c_str(), len, port);
tf_prepare_receive_file(get_sid());
while(!Terminated)
     {
     if(cancel_req)
       {
       cancel_req = false;
       tf_receive_file_cancel(get_sid());
       }
     tf_rcvAndDisp();
     Sleep(1);
     }
}
catch(Exception& e){exsSstEXCEPTION(*eltp,"__TReceiveFileThread::Execute",e);}
}
//----------------------------------------------------------------------------

