//---------------------------------------------------------------------------

#ifndef transmit_fileH
#define transmit_fileH
#include "WinRDefs.h"
#include "BaseThread.h"
#include "transmitFile.h"
#include "contact.h"
//---------------------------------------------------------------------------
typedef enum{
TT__Transmit,
TT__Receive,
}TransferThread_Type;
//---------------------------------------------------------------------------
class TTransferFileThread : public TBaseThread{
int sid;
TransferThread_Type tt;
string file_name;
protected:
string host;
unsigned port;
bool cancel_req;
public:
     __fastcall TTransferFileThread(bool CS, TransferThread_Type TT, TEventLogThread** ELTP, TSip* SIP)
                                   :TBaseThread(CS,ELTP,SIP){
                                                            tt = TT;
                                                            port = 0;
                                                            cancel_req = false;
                                                            }

void     __fastcall set_host(const string& s){host = s;}
string&  __fastcall get_host(){return host;}

void     __fastcall set_port(unsigned a){port = a;}
unsigned __fastcall get_port(){return port;}

void     __fastcall set_file_name(const string& s){file_name = s;}
string&  __fastcall get_file_name(){return file_name;}

void     __fastcall set_sid(int SID){sid=SID;}
int      __fastcall get_sid(){return sid;}

void     __fastcall set_cancel_req(){cancel_req = true;}

TransferThread_Type __fastcall get_transfer_type(){return tt;}
};
//---------------------------------------------------------------------------
class TTransmitFileThread : public TTransferFileThread{
public:
     __fastcall TTransmitFileThread(bool CS, TEventLogThread** ELTP, TSip* SIP)
                :TTransferFileThread(CS, TT__Transmit, ELTP, SIP){}
void __fastcall Execute();
};
//---------------------------------------------------------------------------
class TReceiveFileThread : public TTransferFileThread{
public:
     __fastcall TReceiveFileThread(bool CS, TEventLogThread** ELTP, TSip* SIP)
                :TTransferFileThread(CS, TT__Receive, ELTP, SIP){}
void __fastcall Execute();
};
//---------------------------------------------------------------------------
class TTransferFilePar{   //!!! Do not use pointers
public:
TTransferFileAttrib tfa;
TContact contact;
};
//---------------------------------------------------------------------------
class TTransferFileStruct{
public:
TContact contact;
string path;
};
//---------------------------------------------------------------------------
#endif

