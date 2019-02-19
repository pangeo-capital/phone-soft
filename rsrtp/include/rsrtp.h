#ifndef SipClient_RSRTP_H
#define SipClient_RSRTP_H
// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the SOSOCK_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// SOSOCK_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.

#ifdef RSRTP_EXPORTS
#define RSRTP_API __declspec(dllexport)
#else
#define RSRTP_API __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif

RSRTP_API void rsrtp_init();

RSRTP_API int rsrtp_random_base64key(char* buffer, size_t* sz, unsigned char len=30);

RSRTP_API int rsrtp_create_session(void** ses, int method=0);
RSRTP_API int rsrtp_drop_session(void* ses);

RSRTP_API int rsrtp_get_protect_base64key(void* ses, char* key, size_t* sz);

RSRTP_API int rsrtp_set_unprotect_base64key(void* ses, const char* key, const size_t sz);

RSRTP_API int rsrtp_protect(void* ses, char* packet, size_t* sz);

RSRTP_API int rsrtp_unprotect(void* ses, char* packet, size_t* sz);

RSRTP_API const char* rsrtp_error_text(int err);

#ifdef __cplusplus
}
#endif
#endif //#ifndef SipClient_RSRTP_H
