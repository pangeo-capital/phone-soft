// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the SIPIOS_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// SIPIOS_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef SIPIOS_EXPORTS
#define SIPIOS_API __declspec(dllexport)
#else
#ifdef SIPIOS_EXPORTS_NONE
#define SIPIOS_API 
#else
#define SIPIOS_API __declspec(dllimport)
#endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

//***********************
// Endpoint class
//***********************
typedef void* si_endpoint_t;

typedef void(*si_onTransportState_t)(si_endpoint_t/*e*/, int/*state*/);
typedef void(*si_onPreviewVideo_t)(si_endpoint_t/*e*/, void* /*window*/);
typedef void(*si_onStop_t)(si_endpoint_t/*e*/);

SIPIOS_API void si_ep_set_cb(si_onTransportState_t, si_onPreviewVideo_t, si_onStop_t);
SIPIOS_API si_endpoint_t si_ep_create();
SIPIOS_API void si_ep_drop(si_endpoint_t p);
SIPIOS_API void si_ep_hangup_all(si_endpoint_t p);


//***********************
// Account class
//***********************
typedef void* si_account_t;

typedef void(*si_onRegister_t)(si_account_t a, int status);
typedef void(*si_onUnregister_t)(si_account_t a, int status);
typedef void(*si_onIncomingCall_t)(si_account_t a, int callId);
typedef int(*si_onIncomingSubscribe_t)(si_account_t a, const char* uri);
typedef void(*si_onInstantMessage_t)(si_account_t a, const char* fromuri, const char* touri, const char* msg, const char* info);
typedef void(*si_onInstantMessageStatus_t)(si_account_t a, const char* uri, const char* msg, const char* info, int status, int userData);

SIPIOS_API void si_ac_set_cb(si_onRegister_t, si_onUnregister_t, si_onIncomingCall_t, si_onIncomingSubscribe_t, si_onInstantMessage_t, si_onInstantMessageStatus_t);
SIPIOS_API si_account_t si_ac_create();
SIPIOS_API void si_ac_drop(si_account_t p);

SIPIOS_API void si_ac_registration(si_account_t p, const char* proto, const char* domain, const char* realm);
SIPIOS_API void si_ac_reregistration(si_account_t );

SIPIOS_API void si_ac_setOnlineStatus(si_account_t p, int state, int activity, const char* text);
SIPIOS_API void si_ac_playFile(si_account_t p, const char* file);
SIPIOS_API void si_ac_setInfo(si_account_t p, const char* user, const char* password, const char* displayName, const char* userAgent, const char* deviceToken);
SIPIOS_API void si_ac_unregistration(si_account_t p);


//***********************
// Call class
//***********************

typedef void* si_call_t;

typedef void(*si_onCallState_t)(si_call_t c, int status);
typedef void(*si_onMediaState_t)(si_call_t c, int dir, int status);
typedef void(*si_onVideoState_t)(si_call_t c, int dir, int status, void* window);
typedef int(*si_onMicState_t)(si_call_t c, int status);

SIPIOS_API void si_ca_set_cb(si_onCallState_t, si_onMediaState_t, si_onVideoState_t, si_onMicState_t);

SIPIOS_API si_call_t si_ca_create(si_account_t, const char*);
SIPIOS_API void si_ca_make_call(si_call_t c);
SIPIOS_API void si_ca_answer(si_call_t c);
SIPIOS_API void si_ca_ringing(si_call_t c);
SIPIOS_API void si_ca_hangup(si_call_t c);
SIPIOS_API void si_ca_toggleMic(si_call_t c);
SIPIOS_API bool si_ca_isMicOn(si_call_t c);
SIPIOS_API bool si_ca_isVideoOn(si_call_t c);
SIPIOS_API void si_ca_dialDtmf(si_call_t c, const char*);

SIPIOS_API void si_ca_reset(si_call_t c);
SIPIOS_API void si_ca_hold(si_call_t c);
SIPIOS_API void si_ca_unhold(si_call_t c);
SIPIOS_API void si_ca_setVideoEnabled(si_call_t c, bool flag);
SIPIOS_API void si_ca_connectAudio(si_call_t c);
SIPIOS_API void si_ca_startVideo(si_call_t c);
SIPIOS_API void si_ca_stopVideo(si_call_t c);
SIPIOS_API void si_ca_changeCameraVideo(si_call_t c);

SIPIOS_API const char* si_ca_getRemoteUri(si_call_t c);
SIPIOS_API const char* si_ca_getCallIdString(si_call_t c);

SIPIOS_API void si_ca_startPreview(si_call_t c, int x, int y, int w, int h);
SIPIOS_API void si_ca_stopPreview(si_call_t c);



#ifdef __cplusplus
}
#endif
