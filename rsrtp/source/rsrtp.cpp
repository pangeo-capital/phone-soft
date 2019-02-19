// sosock.cpp : Defines the exported functions for the DLL application.
//


#include "CommonHeader.h"
#include <boost/thread.hpp>

#include "rsrtp.h"

#include "stdafx.h"
#include "srtp.h"
#include "rtp.h"
#include "datatypes.h"
#include "common/Base64.h"

#define ERR_RETURN(exp) {err_status_t err=exp; if (err!=err_status_ok) return err;}

#define ERR_RETURN1(exp, exp_then) {err_status_t err=exp; if (err!=err_status_ok) {exp_then; \
  return err;}}

struct rtp_session {
  srtp_t protect_session;
  srtp_t unprotect_session;
  srtp_policy_t protect_policy;
  srtp_policy_t unprotect_policy;
  uint8_t protect_key[80];
  uint8_t unprotect_key[80];
  rtp_session () : protect_session(0), unprotect_session(0) {}
};

RSRTP_API void rsrtp_init() {
  srtp_init();
}

static boost::mutex _mutex;

err_status_t _rsrtp_random_key(char* buffer, unsigned char length) {
  err_status_t err=crypto_get_random((unsigned char*)buffer, length);
  if (err==err_status_terminus) {
    crypto_kernel_shutdown();
    crypto_kernel_init();
    return crypto_get_random((unsigned char*)buffer, length);
  }
  return err;
}


RSRTP_API int rsrtp_random_base64key(char* buffer, size_t* sz, unsigned char length) {
  boost::unique_lock<boost::mutex> l(_mutex);
  char buf[255];
  ERR_RETURN(_rsrtp_random_key(buf, length));
  Mail::Base64Code b64;
  std::string key_out;
  b64.encode(std::string(buf, (int)length), key_out);
  if (*sz<key_out.size())
    return err_status_fail;
  *sz=key_out.size();
  memcpy(buffer, key_out.c_str(), *sz);
  return err_status_ok;
}

RSRTP_API int rsrtp_create_session(void** ses_out, int method) {
  boost::unique_lock<boost::mutex> l(_mutex);
  rtp_session* ses=new rtp_session();
  ERR_RETURN1(_rsrtp_random_key((char*)ses->protect_key, 30), delete ses);
  crypto_policy_set_rtp_default(&ses->protect_policy.rtp);
  crypto_policy_set_rtcp_default(&ses->protect_policy.rtcp);
  ses->protect_policy.ssrc.type  = ssrc_any_outbound;
  ses->protect_policy.key = ses->protect_key;
  ses->protect_policy.next = NULL;
  ERR_RETURN1(srtp_create(&ses->protect_session, &ses->protect_policy), delete ses);
  *ses_out=ses;
  return err_status_ok;
}

RSRTP_API int rsrtp_drop_session(void* ses1) {
  rtp_session* ses=(rtp_session*)ses1;
  srtp_dealloc(ses->protect_session);
  if (ses->unprotect_session)
    srtp_dealloc(ses->unprotect_session);
  delete ses;
  return err_status_ok;
}

RSRTP_API int rsrtp_set_unprotect_base64key(void* ses1, const char* key, const size_t sz) {
  boost::unique_lock<boost::mutex> l(_mutex);
  rtp_session* ses=(rtp_session*)ses1;
  Mail::Base64Code b64;
  size_t szout;
  b64.decode((char*)key, sz, (char*)ses->unprotect_key, sz, (int&)szout);
  crypto_policy_set_rtp_default(&ses->unprotect_policy.rtp);
  crypto_policy_set_rtcp_default(&ses->unprotect_policy.rtcp);
  ses->unprotect_policy.ssrc.type  = ssrc_any_inbound;
  ses->unprotect_policy.key = ses->unprotect_key;
  ses->unprotect_policy.next = NULL;
  ERR_RETURN(srtp_create(&ses->unprotect_session, &ses->unprotect_policy));
  return err_status_ok;
}

RSRTP_API int rsrtp_get_protect_base64key(void* ses1, char* key, size_t* sz) {
  rtp_session* ses=(rtp_session*)ses1;
  std::string k;
  Mail::Base64Code b64;
  b64.encode(std::string((char*)ses->protect_key, 30 ), k);
  if (*sz<k.size())
    return err_status_fail;
  *sz=k.size();
  memcpy(key, k.c_str(), *sz);
  return err_status_ok;
}

RSRTP_API int rsrtp_protect(void* ses1, char* packet, size_t* sz) {
  rtp_session* ses=(rtp_session*)ses1;
  ERR_RETURN(srtp_protect(ses->protect_session, packet, (int*)sz));
  return err_status_ok;
}

RSRTP_API int rsrtp_unprotect(void* ses1, char* packet, size_t* sz) {
  rtp_session* ses=(rtp_session*)ses1;
  ERR_RETURN(srtp_unprotect(ses->unprotect_session, packet, (int*)sz));
  return err_status_ok;
}

RSRTP_API const char* rsrtp_error_text(int err) {
  switch (err) {
  case err_status_ok      : return "nothing to report";
  case err_status_fail         : return "unspecified failure";
  case err_status_bad_param    : return "unsupported parameter";
  case err_status_alloc_fail   : return "couldn't allocate memory";
  case err_status_dealloc_fail : return "couldn't deallocate properly";
  case err_status_init_fail    : return "couldn't initialize";
  case err_status_terminus     : return "can't process as much data as requested";
  case err_status_auth_fail    : return "authentication failure";
  case err_status_cipher_fail  : return "cipher failure";
  case err_status_replay_fail  : return "replay check failed (bad index)";
  case err_status_replay_old   : return "replay check failed (index too old)";
  case err_status_algo_fail    : return "algorithm failed test routine";
  case err_status_no_such_op   : return "unsupported operation";
  case err_status_no_ctx       : return "no appropriate context found";
  case err_status_cant_check   : return "unable to perform desired validation";
  case err_status_key_expired  : return "can't use key any more";
  case err_status_socket_err   : return "error in use of socket";
  case err_status_signal_err   : return "error in use POSIX signals";
  case err_status_nonce_bad    : return "nonce check failed";
  case err_status_read_fail    : return "couldn't read data";
  case err_status_write_fail   : return "couldn't write data";
  case err_status_parse_err    : return "error pasring data";
  case err_status_encode_err   : return "error encoding data";
  case err_status_semaphore_err :return "error while using semaphores";
  case err_status_pfkey_err    : return "error while using pfkey";
  default                      : return "unknown err";
  }
}


