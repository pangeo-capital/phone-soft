#ifndef SIP_CLIENT_AEC_CONTROL_H
#define SIP_CLIENT_AEC_CONTROL_H

//----------------------------------------------------------------------
//-- ������ Header ������������ ����� � SipClent Project (Borland).
//-- ���������� ������ ����������� ����� !!!
//-- TAecControl ��������� ��� ���������� ������ ����� � ��������� 
//-- CaptureDSP()
//----------------------------------------------------------------------
class TAecControl{
public:
bool TerminateReq;
TAecControl(){
               TerminateReq = false;
             } 
~TAecControl(){
               }
};
//-----------------------------------------------------------------------
class TAExchBuf{
public:
unsigned char* buf;
unsigned int n;
TAExchBuf(){
	   buf = NULL;
           n   = 0;
           }
~TAExchBuf(){
	    if(buf)
              delete [] buf;
            } 
};
//-----------------------------------------------------------------------
#endif

 