#ifndef SIP_CLIENT_Ip_H
#define SIP_CLIENT_Ip_H

#include "WinRDefs.h"
#include <string>

using namespace std;
//------------------------------------------------------------------------------
class TIPAddress{
public:
string   IPAddr;
unsigned uIPAddr;
int      Port;
__fastcall TIPAddress(){uIPAddr=0,Port=0;}
};
//----------------------------------------------------------------------------
#endif
