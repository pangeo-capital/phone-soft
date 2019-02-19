#include "SipiosWrap.h"
#include "common\mapRefObj.h"

refs_objs<si_account_t, Sipios_Account*> objs;
bool init = false;

//***************
// Account
//***************

void _onRegister(si_account_t a, int state) {
  objs.getObj(a)->onRegister(state);
}

void _onUnregister(si_account_t a, int state) {
  objs.getObj(a)->onUnregister(state);
}

void _onIncomingCall(si_account_t a, int call_id) {
  objs.getObj(a)->onIncomingCall(call_id);
}

int _onIncomingSubscribe(si_account_t a, const char* uri) {
  return objs.getObj(a)->onIncomingSubscribe(uri);
}

void _onInstantMessage(si_account_t a, const char* fromuri, const char* touri, const char* msg, const char* info) {
  objs.getObj(a)->onInstantMessage(fromuri, touri, msg, info);
}

void _onInstantMessageStatus(si_account_t a, const char* uri, const char* msg, const char* info, int status, int userData) {
  objs.getObj(a)->onInstantMessageStatus(uri, msg, info, status, userData);
}

Sipios_Account::Sipios_Account() {
  if (!init) {
    si_ac_set_cb(_onRegister, _onUnregister, _onIncomingCall, _onIncomingSubscribe, _onInstantMessage, _onInstantMessageStatus);
    init = true;
  }
  objs.setObj(si_ac_create(), this);
}

Sipios_Account::~Sipios_Account() {
  si_ac_drop(objs.getRef(this));
  objs.removeObj(this);
}

void Sipios_Account::setInfo(const std::string& user, const std::string& password, const std::string& displayName, const std::string& userAgent, const std::string& deviceToken) {
  si_ac_setInfo(objs.getRef(this), user.c_str(), password.c_str(), displayName.c_str(), userAgent.c_str(), deviceToken.c_str());
}

void Sipios_Account::registration(const std::string& proto, const std::string& proxy, const std::string& domain) {
  si_ac_registration(objs.getRef(this), proto.c_str(), proxy.c_str(), domain.c_str());
}


void Sipios_Account::setOnlineStatus(int state, int activity, const std::string& note) {
  si_ac_setOnlineStatus(objs.getRef(this), state, activity, note.c_str());
}

void Sipios_Account::setKeepAlive() {
}

void Sipios_Account::keepAlive() {

}
void Sipios_Account::unregistration() {
  si_ac_unregistration(objs.getRef(this));
}

void Sipios_Account::presNotify() {
}

void Sipios_Account::setContactParams(const std::string& params) {
}

void Sipios_Account::ipChangeDetected() {

}

