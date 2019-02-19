//---------------------------------------------------------------------------
#pragma hdrstop
#include "SosockThread.h"

#include "./src/locker.h"
#include "./tls_sock/include/tls_sock.h"
//---------------------------------------------------------------------------

//#pragma package(smart_init)

using namespace std;

Sosock_Thread* Sosock_Thread::_object = 0;
std::map<void*, Sosock_Client*> refs;
CRITICAL_SECTION cs;

void connect_handler(void* ref) {
  locker_cs lock(cs);
  if (refs.find(ref) == refs.end()) {
    return;
  }
  Sosock_Client* cl = refs[ref];
  lock.unlock();
  cl->onConnect();
}

void disconnect_handler(void* ref) {
  locker_cs lock(cs);
  if (refs.find(ref) == refs.end()) {
    return;
  }
  Sosock_Client* cl = refs[ref];
  refs.erase(ref);
  lock.unlock();
  cl->onDisconnect();
}

void read_handler(const char* buf, size_t size, void* ref) {
  locker_cs lock(cs);
  if (refs.find(ref) == refs.end()) {
    return;
  }
  Sosock_Client* cl = refs[ref];
  lock.unlock();
  cl->onRead(buf, size);
}

void error_handler(void* ref, const char* err) {
  locker_cs lock(cs);
  if (refs.find(ref) == refs.end()) {
    return;
  }
  Sosock_Client* cl = refs[ref];
  lock.unlock();
  cl->onError(err);
}

Sosock_Thread::Sosock_Thread() : TThread(false) {
  ::InitializeCriticalSection(&cs);
  Resume();
};

__fastcall Sosock_Thread::~Sosock_Thread() {
  ::DeleteCriticalSection(&cs);
}


void __fastcall Sosock_Thread::Execute() {
  so_set_start_handler(&connect_handler);
  so_set_destr_handler(&disconnect_handler);
  so_set_read_handler(&read_handler);
  so_set_error_handler(&error_handler);
  //so_set_tunnel_read_handler(&tunnel_read_handler);
  //so_set_tunnel_start_handler(&tunnel_connect_handler);
  //so_set_tunnel_destr_handler(&tunnel_disconnect_handler);
  so_run();
};

void __fastcall Sosock_Thread::DoTerminate() {
  so_stop();
};

Sosock_Client* Sosock_Thread::create_client(Sosock_Client* cli, const std::string& host, int port) {
  void* ref = so_start_client_tcp_ssl((char*)host.c_str(), port);
  locker_cs lock(cs);
  refs[ref] = cli;
  lock.unlock();
  cli->ref = ref;
  return cli;
}


Sosock_Client::~Sosock_Client() {
  locker_cs lock(cs);
  refs.erase(ref);
}

void Sosock_Client::write(const char* buf, size_t size) {
  so_write_some(ref, buf, size);
}







