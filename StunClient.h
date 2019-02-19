//---------------------------------------------------------------------------

#ifndef StunClientH
#define StunClientH

#include "WinRDefs.h"
#include <map>
#include "stun.h"
#include "log.h"
#include "sip.h"

using namespace std;
//---------------------------------------------------------------------------
typedef int socklen_t;

#define EWOULDBLOCK             WSAEWOULDBLOCK
#define EINPROGRESS             WSAEINPROGRESS
#define EALREADY                WSAEALREADY
#define ENOTSOCK                WSAENOTSOCK
#define EDESTADDRREQ            WSAEDESTADDRREQ
#define EMSGSIZE                WSAEMSGSIZE
#define EPROTOTYPE              WSAEPROTOTYPE
#define ENOPROTOOPT             WSAENOPROTOOPT
#define EPROTONOSUPPORT         WSAEPROTONOSUPPORT
#define ESOCKTNOSUPPORT         WSAESOCKTNOSUPPORT
#define EOPNOTSUPP              WSAEOPNOTSUPP
#define EPFNOSUPPORT            WSAEPFNOSUPPORT
#define EAFNOSUPPORT            WSAEAFNOSUPPORT
#define EADDRINUSE              WSAEADDRINUSE
#define EADDRNOTAVAIL           WSAEADDRNOTAVAIL
#define ENETDOWN                WSAENETDOWN
#define ENETUNREACH             WSAENETUNREACH
#define ENETRESET               WSAENETRESET
#define ECONNABORTED            WSAECONNABORTED
#define ECONNRESET              WSAECONNRESET
#define ENOBUFS                 WSAENOBUFS
#define EISCONN                 WSAEISCONN
#define ENOTCONN                WSAENOTCONN
#define ESHUTDOWN               WSAESHUTDOWN
#define ETOOMANYREFS            WSAETOOMANYREFS
#define ETIMEDOUT               WSAETIMEDOUT
#define ECONNREFUSED            WSAECONNREFUSED
#define ELOOP                   WSAELOOP
#define EHOSTDOWN               WSAEHOSTDOWN
#define EHOSTUNREACH            WSAEHOSTUNREACH
#define EPROCLIM                WSAEPROCLIM
#define EUSERS                  WSAEUSERS
#define EDQUOT                  WSAEDQUOT
#define ESTALE                  WSAESTALE
#define EREMOTE                 WSAEREMOTE
//----------------------------------------------------------------------------
class TSipIniBase{
public:
string Addr;
string Port;
};
//----------------------------------------------------------------------------
class TSipCommonData : public TSipIniBase{
public:
};
//---------------------------------------------------------------------------
class TSipProxyData : public TSipIniBase{
public:
string RegInt;
};
//---------------------------------------------------------------------------
class TAccountIniData{
public:
string UserName;
string Domain;
string DisplayName;
string Passward;
__fastcall TAccountIniData(){Passward = "123";}
};
//---------------------------------------------------------------------------
class TSignalIniData{
public:
string AlertingType;
};
//---------------------------------------------------------------------------
class TMediaIniData{
public:
string MStartPort;
string MEndPort;
string MInt;
};
//---------------------------------------------------------------------------
class TTransportIniData{
public:
string SipTransport;
};
//---------------------------------------------------------------------------
class TG729IniData{
public:
string annexb;
};
//---------------------------------------------------------------------------
class TStun{
bool sendMessage( Socket, char*, int,unsigned int, unsigned short,TEventLogThread*);
void __fastcall log(TEventLogThread*,const string&);
char* encode(char* buf, const char* data, unsigned int length);
char* encode16(char* buf, UInt16 data);
char* encode32(char* buf, UInt32 data);
char* encodeAtrString(char* ptr, UInt16 type, const StunAtrString& atr);
char* encodeAtrError(char* ptr, const StunAtrError& atr);
char* encodeAtrAddress4(char* ptr, UInt16 type, const StunAtrAddress4& atr);
char* encodeAtrChangeRequest(char* ptr, const StunAtrChangeRequest& atr);
char* encodeAtrUnknown(char* ptr, const StunAtrUnknown& atr);
char* encodeXorOnly(char* ptr);
char* encodeAtrIntegrity(char* ptr, const StunAtrIntegrity& atr);
void computeHmac(char* hmac, const char* input, int length, const char* key, int sizeKey);
NatType stunNatType( StunAddress4&,bool*,bool*,int,StunAddress4*,TSip*,TEventLogThread*);
bool getMessage( Socket fd, char* buf, int* len,unsigned int* srcIp, unsigned short* srcPort,TEventLogThread* elt);
bool __fastcall stunParseHostName( char*,UInt32&, UInt16&,UInt16,TEventLogThread*);
bool __fastcall stunParseServerName( char*,StunAddress4&,TEventLogThread*);
int __fastcall stunRandomPort();
bool stunParseMessage( char* buf, unsigned int bufLen, StunMessage& msg,TSip* Sip,TEventLogThread* elt);
Socket openPort( unsigned short, unsigned int,TEventLogThread*);
bool stunParseAtrAddress( char* body, unsigned int hdrLen,  StunAtrAddress4& result,TEventLogThread* elt );
bool stunParseAtrChangeRequest( char* body, unsigned int hdrLen,  StunAtrChangeRequest& result,TEventLogThread* elt );
bool stunParseAtrString( char* body, unsigned int hdrLen,  StunAtrString& result, TEventLogThread* elt );
bool stunParseAtrIntegrity( char* body, unsigned int hdrLen,  StunAtrIntegrity& result,TEventLogThread* elt );
bool stunParseAtrError( char* body, unsigned int hdrLen,  StunAtrError& result, TEventLogThread* elt );
bool stunParseAtrUnknown( char* body, unsigned int hdrLen,  StunAtrUnknown& result,TEventLogThread* elt );
void stunTest( StunAddress4& dest, int testNum, StunAddress4* sAddr,TSip* sip,TEventLogThread* elt );
void __fastcall stunSendTest( Socket myFd, StunAddress4& dest,
              const StunAtrString& username, const StunAtrString& password,
              int testNum, TEventLogThread* elt );
unsigned int __fastcall stunEncodeMessage( const StunMessage& message,
                   char* buf,
                   unsigned int bufLen,
                   const StunAtrString& password,
                   TEventLogThread* elt);
void stunBuildReqSimple( StunMessage* msg,
                    const StunAtrString& username,
                    bool changePort, bool changeIp, unsigned int id );
int stunOpenSocket( StunAddress4& dest, StunAddress4* mapAddr,
                int port, StunAddress4* srcAddr,TSip* sip,TEventLogThread* elt);
bool stunOpenSocketPair( StunAddress4& dest, StunAddress4* mapAddr,
                    int* fd1, int* fd2,
                    int port, StunAddress4* srcAddr,
                    TSip* sip,TEventLogThread* elt );

public:
void __fastcall StunClientProc(void*,TSip*,TEventLogThread*);
inline int getErrno() { return WSAGetLastError(); }
};
//---------------------------------------------------------------------------
int stunRand();
#endif
