#ifndef OutPutSipBuf_H
#define OutPutSipBuf_H

#include "WinRDefs.h"
#include "SipParsThread.h"
#include "const.h"
//------------------------------------------------------------------------------
class TInitRtpPacket{
public:
USHORT   initSeqNumber;
int      initTimeStamp;
int      sourceId;
__fastcall TInitRtpPacket(){initSeqNumber=0;initTimeStamp=0;sourceId=0;}
};
//------------------------------------------------------------------------------
class TOutputSipBuf : public BaseExchangeBlock{
unsigned tag;
public:
TDateTime dt;
string calledname;
string cld_DisplayName;
string FromTag;
string requestline;
string via;
string maxforwards;
string from;
string callid;
int    curr_cseq;
string cseq;
string expires;
string allow;
string accept;
string authorization;
string event;
string subscriptionstate;
string contenttype;
string ReferTo;
string ReferredBy;
string Replaces;
string Referred_CallID;
string RequestUri;

string ac_user_name;
string ac_user_pwd;
string ac_domain;

TInitRtpPacket* irp;
__fastcall TOutputSipBuf():BaseExchangeBlock(TOutputSipBuf_BLOCKTYPE){
                                            tag = 0;
                                            curr_cseq = 0;
                                            irp = NULL;
                                            }
virtual __fastcall ~TOutputSipBuf(){
                           if(irp)
                             delete irp;
                           }

void        __fastcall set_tag(unsigned a){tag=a;}
unsigned    __fastcall get_tag(){return tag;}

};
//---------------------------------------------------------------------------
#endif

