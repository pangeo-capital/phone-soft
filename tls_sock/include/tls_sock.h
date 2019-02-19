// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the SOSOCK_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// SOSOCK_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.

#ifndef Sip_Tls_SOCK_H
#define Sip_Tls_SOCK_H

#ifdef SOSOCK_EXPORTS
#define SOSOCK_API __declspec(dllexport)
#else
#define SOSOCK_API __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif

SOSOCK_API void* so_start_client_tcp(char* /*host*/, int /*port*/);
SOSOCK_API void* so_start_client_tcp_ssl(char* /*host*/, int /*port*/);
SOSOCK_API void so_destr_client_tcp(void* /*client_*/);


SOSOCK_API void* so_start_server_tcp(int /*port*/);
SOSOCK_API void* so_start_server_tcp_ssl(int /*port*/);
SOSOCK_API void so_destr_server_tcp(void* /*client_*/);
SOSOCK_API void so_destr_server_tcp_ssl(void* /*client_*/);


typedef void (*ReadHandler) (const char* /*data_*/, size_t /*size_*/, void* /*client_*/);
typedef void (*StartHandler) (void* /*client_*/);
typedef void (*DestrHandler) (void* /*client_*/);
typedef void (*ErrorHandler) (void* /*client_*/, const char* /*what*/);

SOSOCK_API void so_set_start_handler(StartHandler /*handler*/);
SOSOCK_API void so_set_read_handler(ReadHandler /*handler*/);
SOSOCK_API void so_set_destr_handler(DestrHandler /*handler*/);
SOSOCK_API void so_set_error_handler(ErrorHandler /*handler*/);

SOSOCK_API bool so_write_some(void* /*ref*/, const char* /*data_*/, size_t /*size_*/);

SOSOCK_API void so_run();
SOSOCK_API void so_run_no_wait(int /*number_of_threads*/);

SOSOCK_API void so_poll();

SOSOCK_API void so_stop();

SOSOCK_API void so_set_ssl_pem(char* priv_key, char* ca);

//Debug
//DEBUG SEVERITY
#define SOSOCK_INFO "INFO"
#define SOSOCK_WARN "WARN"
#define SOSOCK_ERROR "ERROR"
typedef int (*sosock_debug_f)(const char* /*severirty*/, const char* /*fmt*/, ...);
SOSOCK_API void so_debug_set_log_cb(sosock_debug_f );

//undeclared functions
SOSOCK_API void* so_socket(void* ref);


//tunnel functions
//data_type values
const unsigned int DT_SIP=0xFE|'S'<<8|'I'<<16|'P'<<24;
const unsigned int DT_RTP=0xFE|'R'<<8|'T'<<16|'P'<<24;

SOSOCK_API void* so_start_tunnel_tcp(char* /*host*/, int /*port*/);

typedef void (*TunnelReadHandler) (const char* /*data_*/, size_t /*size_*/, unsigned int /*data_type*/, void* /*client_*/, char* /*name_*/, unsigned char /*name_sz*/);
SOSOCK_API void so_set_tunnel_start_handler(StartHandler /*handler*/);
SOSOCK_API void so_set_tunnel_destr_handler(DestrHandler /*handler*/);
SOSOCK_API void so_set_tunnel_read_handler(TunnelReadHandler /*handler*/);

SOSOCK_API bool so_tunnel_write_some(void* /*ref*/, const char* /*data_*/, size_t /*size_*/, unsigned int /*data_type*/, const char* name_=0, unsigned char name_sz=0);

SOSOCK_API void* so_start_tunnel_server_tcp(int port);

#ifdef __cplusplus
}
#endif
#endif //#ifndef Sip_Tls_SOCK_H
