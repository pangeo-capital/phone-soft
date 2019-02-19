#include <iostream>
#include "..\sosock\sosock.h"
#include <string.h>
#include <boost/thread.hpp>
#include "common.hpp"
#include <boost/lexical_cast.hpp>

bool isconnect=false;

void tunnel_connect_handler(void* ref) {
  std::cout << "connect:" << ref << std::endl;
  isconnect=true;
}

void tunnel_read_handler(const char* data, size_t size, unsigned int data_type, void* ref, char* name, unsigned char name_sz) {
  std::cout << "read:" << std::string(name,name_sz) << "\n";
}

void tcp_read_handler(const char* data, size_t size, void* ref) {
  std::cout << "read:" << std::string(data, size) << "\n";
}

void tunnel_connect_error(void* ref, const char* err) {
  std::cout << "err:" << err;
}

template <typename ElemT>
struct HexTo {
    ElemT value;
    operator ElemT() const {return value;}
    friend std::istream& operator>>(std::istream& in, HexTo& out) {
        in >> std::hex >> out.value;
        return in;
    }
};

void run () {
  so_run();
}

int main() {
  std::cout << "main:" << std::endl;
  //so_set_tunnel_start_handler(&tunnel_connect_handler);
  //so_set_tunnel_read_handler(&tunnel_read_handler);
  so_set_error_handler(&tunnel_connect_error);
  so_set_start_handler(&tunnel_connect_handler);
  so_set_read_handler(&tcp_read_handler);
  //so_start_server_tcp_ssl(23961);
  //void* hserver=so_start_tunnel_server_tcp(23955);
  boost::thread th(boost::bind(&run));
  while (1) {
    isconnect=false;
    void* tcp=so_start_client_tcp("rastel.dyndns-work.com", 5060);
    while (isconnect!=true) {
      int k=0;
      std::cout << ".";
      Sleep(100);
    }
    std::cout << "connect ok\n";
  
    std::string d=loadFromFile(".\\sip.in");
    std::string s=d;
    while(1) {
      if (!so_write_some(tcp, s.c_str(), s.size()))
        break;
      Sleep(100);
    }
    Sleep(5000);
  }
  th.join();
  return 0;
}