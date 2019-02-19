// test.cpp : Defines the entry point for the console application.
//
#pragma once

#include "sip\sipios_c.h"
#include "sip\SipiosWrap.h"


class Endpoint : public Sipios_Endpoint {
  virtual void onTransportState(int state);
  virtual void onPreviewVideo(void* window);
  virtual void onStop();
};


class Account : public Sipios_Account {
  // Inherited via Sipios_Account
  virtual void onRegister(int state);
  virtual void onUnregister(int state);
  virtual void onIncomingCall(int call_id);
  virtual void onInstantMessage(const std::string & fromuri, const std::string & touri, const std::string & msg, const std::string & info);
  virtual void onInstantMessageStatus(const std::string & uri, const std::string & msg, const std::string & info, int status, int userData);
  virtual int onIncomingSubscribe(const std::string & uri);
};

