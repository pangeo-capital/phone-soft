#ifndef SIPIOSWRAP_H
#define SIPIOSWRAP_H

#include "sip/sipios_c.h"
#include <string>

class Sipios_Endpoint {
public:
  Sipios_Endpoint();
  ~Sipios_Endpoint();

  virtual void onTransportState(int state) = 0;
  virtual void onPreviewVideo(void* window) = 0;
  virtual void onStop() = 0;

  void hangup_all();
  void setSndDev(const std::string& dev);
  
  void startPreview(int dev, int x, int y, int w, int h);
  void stopPreview(int dev);
};


class Sipios_Call;

class Sipios_Account {

public:
  Sipios_Account();
  ~Sipios_Account();

  void setInfo (const std::string& user, const std::string& password, const std::string& displayName, const std::string& userAgent, const std::string& deviceToken);

  void registration(const std::string& proto, const std::string& proxy, const std::string& domain);

  virtual void onRegister(int state) = 0;
  virtual void onUnregister(int state) = 0;
  virtual void onIncomingCall(int call_id) = 0;
  virtual void onInstantMessage(const std::string& fromuri, const std::string& touri, const std::string& msg, const std::string& info) = 0;
  virtual void onInstantMessageStatus(const std::string& uri, const std::string& msg, const std::string& info, int status, int userData) = 0;
  virtual int onIncomingSubscribe(const std::string& uri) = 0;

  void setOnlineStatus(int state, int activity, const std::string& note);

  void setKeepAlive();
  void keepAlive();
  void unregistration();

  void presNotify();

  void setContactParams(const std::string& params);

  void ipChangeDetected();
};

class Sipios_Call {

  Sipios_Call(Sipios_Account* account_wrap, const std::string& uri, int call_id);

  void calling();

  virtual void onCallState(int state) = 0;
  virtual void onMediaState(int dir, int state) = 0;
  virtual void onVideoState(int dir, int state, void* window) = 0;
  virtual void onMicState(int state) = 0;
  virtual void onIncomingCall() = 0;

  void hangup();


  void answer();

  void ringing();

  void toggleMic();
  void startVideo();
  void stopVideo();
  void changeCameraVideo();

  void dialDtmf(const std::string& digits);

  void hold();
  void unhold();
  void reset();

  bool isMicOn();
  bool isVideoOn();
  void setVideoEnabled(bool isVideo);
  void connectAudio();
  const std::string& getRemoteUri();
  const std::string& getCallIdString();

  void startPreview(int x, int y, int w, int h);
  void stopPreview();

};


class sipiosBuddyWrapper {

  sipiosBuddyWrapper(Sipios_Account* account_wrap);

  void subscribe(const std::string& contact);

  virtual void onSubscribe(int state, const std::string& contact, int code, int termCode) = 0;

  void sendInstantMessage(const std::string&msg, int userData);

  void updatePresence();

  void getInfo();

};


class Sipios_AudPlayer {

  Sipios_AudPlayer();
  void playFile(const std::string&file);
  void stopPlayFile();
  void startKPV();
  void stopKPV();
  void playDigit(const std::string&digit);
  void startHoldTone();
};


#endif