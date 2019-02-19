//---------------------------------------------------------------------------

#ifndef SosockThreadH
#define SosockThreadH

#include <vcl.h>
#include <map>
#include <string>
//---------------------------------------------------------------------------

class Sosock_Client {
private:

  void* ref;
  friend class Sosock_Thread;

public:
  virtual ~Sosock_Client();

  virtual void onConnect() = 0;
  virtual void onDisconnect() = 0;
  virtual void onRead(const char* buf, size_t size) = 0;
  virtual void onError(const char* msg) = 0;

public:

  void* get_ref() {return ref;};
  void write(const char* buf, size_t size);
  
};

class Sosock_Thread : public TThread {
private:

  static Sosock_Thread* _object;

protected:

  virtual  void __fastcall Execute();
  virtual  void __fastcall DoTerminate();

public:

  Sosock_Thread();
  virtual __fastcall ~Sosock_Thread();

  static Sosock_Thread& instance() {
    if (!_object)
      _object = new Sosock_Thread();
    return *_object;
  };

  Sosock_Client* create_client(Sosock_Client* cli, const std::string& host, int port);
  
};

#endif
