// SIPIOSBC.cpp :
//

#include "SipiosBC.h"
#include <iostream>


void Endpoint::onTransportState(int state) {
}

void Endpoint::onPreviewVideo(void* window) {
}

void Endpoint::onStop() {
}


void Account::onRegister(int state)
{
  std::cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << "onRegister:" << std::endl;
  Sleep(1000);
}

void Account::onUnregister(int state)
{
  std::cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << "onUnRegister:" << std::endl;
  Sleep(1000);
}

void Account::onIncomingCall(int call_id)
{
}

void Account::onInstantMessage(const std::string & fromuri, const std::string & touri, const std::string & msg, const std::string & info)
{
}

void Account::onInstantMessageStatus(const std::string & uri, const std::string & msg, const std::string & info, int status, int userData)
{
}

int Account::onIncomingSubscribe(const std::string & uri)
{
  return 0;
}

int main1()
{
  Endpoint* endpoint = new Endpoint();
  Sleep(1000);
  Account* account = new Account();
  account->setInfo("2049", "wsx234", "2049", "test", "");
  account->registration("sip", ".dyndns-work.com", "EXCEL-CSP");
  Sleep(2000);
  account->unregistration();
  Sleep(2000);
  delete account;
  delete endpoint;
  Sleep(2000);
  return 0;
}
