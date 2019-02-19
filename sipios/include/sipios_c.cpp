// sosock.cpp : Defines the exported functions for the DLL application.
//

#include "CommonHeader.h"
#include "stdafx.h"
#include "sipios_c.h"
#include "sip/sipios.hpp"
#include <vector>

class si_Endpoint : public EndpointDelegate {
public:

  static std::shared_ptr<si_Endpoint> _p;
  static si_onTransportState_t _onTransportState;
  static si_onPreviewVideo_t _onPreviewVideo;
  static si_onStop_t _onStop;

  void onTransportState(int state) {
    if (_onTransportState)
      (*_onTransportState)(_p.get(), state);
  }

  void onPreviewVideo(void* window) {
    if (_onPreviewVideo)
      (*_onPreviewVideo)(_p.get(), window);
  }

  void onStop() {
    if (_onStop)
      (*_onStop)(_p.get());
  }

};

std::shared_ptr<si_Endpoint> si_Endpoint::_p(0);
si_onTransportState_t si_Endpoint::_onTransportState = 0;
si_onPreviewVideo_t si_Endpoint::_onPreviewVideo = 0;
si_onStop_t si_Endpoint::_onStop = 0;


SIPIOS_API void si_ep_set_cb(si_onTransportState_t p1, si_onPreviewVideo_t p2, si_onStop_t p3) {
  si_Endpoint::_onTransportState = p1;
  si_Endpoint::_onPreviewVideo = p2;
  si_Endpoint::_onStop = p3;
}

SIPIOS_API si_endpoint_t si_ep_create() {
  si_Endpoint::_p.reset(new si_Endpoint());
  si_Endpoint::_p->start();
  return (si_endpoint_t)si_Endpoint::_p.get();
}

SIPIOS_API void si_ep_drop(si_endpoint_t p) {
  if (si_Endpoint::_p.get() == p) {
    si_Endpoint::_p->stop();
    //si_Endpoint::_p.reset();
  }
}

SIPIOS_API void si_ep_hangup_all(si_endpoint_t  p) {
  auto endpoint = si_Endpoint::_p;
  endpoint->hangup_all();
}



// Account

class si_Account : public AccountDelegate {
public:
  static std::vector<std::shared_ptr<si_Account> > list;
  static si_onRegister_t _onRegister;
  static si_onUnregister_t _onUnregister;
  static si_onIncomingCall_t _onIncomingCall;
  static si_onIncomingSubscribe_t _onIncomingSubscribe;
  static si_onInstantMessage_t _onInstantMessage;
  static si_onInstantMessageStatus_t _onInstantMessageStatus;
  
  void onRegister(int state) {
    if (_onRegister)
      (*_onRegister)(shared_from_this().get(), state);

  }

  void onUnregister(int state) {
    if (_onRegister)
      (*_onRegister)(shared_from_this().get(), state);
  }

  void onIncomingCall(int callId) {
    if (_onIncomingCall)
      (*_onIncomingCall)(shared_from_this().get(), callId);

  }

  int onIncomingSubscribe(const std::string& uri) {
    if (_onIncomingSubscribe)
      return (*_onIncomingSubscribe)(shared_from_this().get(), uri.c_str());
    return 0;
  }

  void onInstantMessage(const std::string& fromuri, const std::string& touri, const std::string& msg, const std::string& info) {
    if (_onInstantMessage)
      (*_onInstantMessage)(shared_from_this().get(), fromuri.c_str(), touri.c_str(), msg.c_str(), info.c_str());
  }

  void onInstantMessageStatus(const std::string& uri, const std::string& msg, const std::string& info, int status, int userData) {
    if (_onInstantMessageStatus)
      (*_onInstantMessageStatus)(shared_from_this().get(), uri.c_str(), msg.c_str(), info.c_str(), status, userData);
  }

};


std::vector<std::shared_ptr<si_Account>> si_Account::list;

si_onRegister_t si_Account::_onRegister;
si_onUnregister_t si_Account::_onUnregister;
si_onIncomingCall_t si_Account::_onIncomingCall;
si_onIncomingSubscribe_t si_Account::_onIncomingSubscribe;
si_onInstantMessage_t si_Account::_onInstantMessage;
si_onInstantMessageStatus_t si_Account::_onInstantMessageStatus;


SIPIOS_API void si_ac_set_cb(si_onRegister_t p1, si_onUnregister_t p2, si_onIncomingCall_t p3, si_onIncomingSubscribe_t p4, si_onInstantMessage_t p5, si_onInstantMessageStatus_t p6) {
  si_Account::_onRegister = p1;
  si_Account::_onUnregister = p2;
  si_Account::_onIncomingCall = p3;
  si_Account::_onIncomingSubscribe = p4;
  si_Account::_onInstantMessage = p5;
  si_Account::_onInstantMessageStatus = p6;

}

SIPIOS_API si_account_t si_ac_create() {
  si_Account::list.push_back(std::shared_ptr<si_Account>(new si_Account()));
  return si_Account::list.back().get();
}

template<class T>
typename std::vector<std::shared_ptr<T>>::iterator getByPointer(void* p) {
  for (auto i = T::list.begin(); i != T::list.end(); ++i)
    if ((*i).get() == p)
      return i;
  return T::list.end();
}

std::vector<std::shared_ptr<si_Account>>::iterator getAccountByPointer(si_account_t p) {
  return getByPointer<si_Account>(p);
}


SIPIOS_API void si_ac_drop(si_account_t p) {
  auto i = getAccountByPointer(p);
  if (i != si_Account::list.end())
    si_Account::list.erase(i);
}

SIPIOS_API void si_ac_registration(si_account_t p, const char* proto, const char* domain, const char* realm) {
  auto i = getAccountByPointer(p);
  if (i != si_Account::list.end()) {
    auto account = *i;
    account->send_registration(proto, domain, realm);
  }
}

SIPIOS_API void si_ac_reregistration(si_account_t p) {
  auto i = getAccountByPointer(p);
  if (i != si_Account::list.end()) {
    auto account = *i;
    account->send_reregistration();
  }
}

SIPIOS_API void si_ac_setOnlineStatus(si_account_t p, int state, int activity, const char* text) {
  auto i = getAccountByPointer(p);
  if (i != si_Account::list.end()) {
    auto account = *i;
    account->setOnlineStatus(state, activity, text);
  }
}

SIPIOS_API void si_ac_playFile(si_account_t p, const char* file) {
  auto i = getAccountByPointer(p);
  if (i != si_Account::list.end()) {
    auto account = *i;
    account->playFile(file);
  }
}

SIPIOS_API void si_ac_setInfo(si_account_t p, const char* user, const char* password, const char* displayName, const char* userAgent, const char* deviceToken) {
  auto i = getAccountByPointer(p);
  if (i != si_Account::list.end()) {
    auto account = *i;
    account->setInfo(user, password, displayName, userAgent, deviceToken);
  }
}

SIPIOS_API void si_ac_unregistration(si_account_t p) {
  auto i = getAccountByPointer(p);
  if (i != si_Account::list.end()) {
    auto account = *i;
    account->unregistration();
  }
}

// Call class

class si_Call : public CallDelegate {
public:
  static std::vector<std::shared_ptr<si_Call> > list;
  static si_onCallState_t _onCallState;
  static si_onMediaState_t _onMediaState;
  static si_onVideoState_t _onVideoState;
  static si_onMicState_t _onMicState;
public:
  si_Call(account_api_ptr_t ac, const std::string& number) : CallDelegate(ac, number) {

  }
  virtual void onCallState(int status) {
    if (_onCallState)
      (*_onCallState)(shared_from_this().get(), status);
  }
  virtual void onMediaState(int dir, int status) {
    if (_onMediaState)
      (*_onMediaState)(shared_from_this().get(), dir, status);
  }
  virtual void onVideoState(int dir, int status, void* window) {
    if (_onVideoState)
      (*_onVideoState)(shared_from_this().get(), dir, status, window);
  };
  virtual void onMicState(int status) {
    if (_onMicState)
      (*_onMicState)(shared_from_this().get(), status);
  }
};

std::vector<std::shared_ptr<si_Call>> si_Call::list;
si_onCallState_t si_Call::_onCallState = 0;
si_onMediaState_t si_Call::_onMediaState = 0;
si_onVideoState_t si_Call::_onVideoState = 0;
si_onMicState_t si_Call::_onMicState = 0;

std::vector<std::shared_ptr<si_Call>>::iterator getCallByPointer(si_call_t p) {
  return getByPointer<si_Call>(p);
}


SIPIOS_API si_call_t si_ca_create(si_account_t a, const char* p) {
  si_Call::list.push_back(std::shared_ptr<si_Call>(new si_Call(*getAccountByPointer(a), p)));
  return si_Call::list.back().get();
}

SIPIOS_API void si_ca_drop(si_call_t p) {
  auto i = getCallByPointer(p);
  if (i != si_Call::list.end())
    si_Call::list.erase(i);
}

SIPIOS_API void si_ca_make_call(si_call_t p) {
  auto i = getCallByPointer(p);
  if (i != si_Call::list.end())
    (*i)->make_call();
}

SIPIOS_API void si_ca_answer(si_call_t p) {
  auto i = getCallByPointer(p);
  if (i != si_Call::list.end())
    (*i)->answer();
}

SIPIOS_API void si_ca_ringing(si_call_t c) {
  auto i = getCallByPointer(c);
  if (i != si_Call::list.end())
    (*i)->ringing();
}

SIPIOS_API void si_ca_hangup(si_call_t c) {
  auto i = getCallByPointer(c);
  if (i != si_Call::list.end())
    (*i)->hangup();
}

SIPIOS_API void si_ca_toggleMic(si_call_t c) {
  auto i = getCallByPointer(c);
  if (i != si_Call::list.end())
    (*i)->toggleMic();
}

SIPIOS_API bool si_ca_isMicOn(si_call_t c) {
  return true;
}

SIPIOS_API bool si_ca_isVideoOn(si_call_t c) {
  return false;
}

SIPIOS_API void si_ca_dialDtmf(si_call_t c, const char*) {

}


SIPIOS_API void si_ca_reset(si_call_t c) {

}

SIPIOS_API void si_ca_hold(si_call_t c) {

}

SIPIOS_API void si_ca_unhold(si_call_t c) {

}

SIPIOS_API void si_ca_setVideoEnabled(si_call_t c, bool flag) {

}

SIPIOS_API void si_ca_connectAudio(si_call_t c) {

}

SIPIOS_API void si_ca_startVideo(si_call_t c) {

}

SIPIOS_API void si_ca_stopVideo(si_call_t c) {

}

SIPIOS_API void si_ca_changeCameraVideo(si_call_t c) {

}


SIPIOS_API const char* si_ca_getRemoteUri(si_call_t c) {
  auto i = getCallByPointer(c);
  if (i != si_Call::list.end())
    return (*i)->getRemoteUri().c_str();
  return "";
}

SIPIOS_API const char* si_ca_getCallIdString(si_call_t c) {
  auto i = getCallByPointer(c);
  if (i != si_Call::list.end())
    (*i)->getCallIdString().c_str();
  return "";
}


SIPIOS_API void si_ca_startPreview(si_call_t c, int x, int y, int w, int h) {

}

SIPIOS_API void si_ca_stopPreview(si_call_t c) {

}




