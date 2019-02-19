#ifndef SIP_USER_AGENT_H
#define SIP_USER_AGENT_H
#include <string>

using namespace std;
//------------------------------------------------------------------------------
const string AES_CM_128_HMAC_SHA1_80 = "AES_CM_128_HMAC_SHA1_80";
//------------------------------------------------------------------------------
const MAX_CRYPTO_SESS_LOG_ERROR = 100;
//------------------------------------------------------------------------------
typedef enum{
SipUAThreadType_UAC,
SipUAThreadType_UAS,
SipUAThreadType_NDef,
}SipUAThreadType;
//------------------------------------------------------------------------------
#endif //#ifndef SIP_USER_AGENT_H
