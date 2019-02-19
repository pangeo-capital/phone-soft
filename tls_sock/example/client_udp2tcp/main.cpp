#include <windows.h>
#include <iostream>
#include "..\..\sosock.h"
#include <string>
#include <vector>
#include <algorithm>
#include  <boost/thread.hpp>


void connect_handler(void* ref) {
  //std::cout << "connect:" << ref << so_socket(ref) << std::endl;
  so_write_some(ref, "xxx\r\n\r\n", 7);
}

std::vector<void*> r;
bool flagExit=false;
boost::shared_mutex r_mutex;

void disconnect_handler(void* ref) {
  //std::cout << "disconnect:" << ref << std::endl;
  boost::shared_lock<boost::shared_mutex> l(r_mutex);
  std::vector<void*>::iterator it=std::find(r.begin(), r.end(), ref);
  if (it!=r.end()) {
    if (rand()%2==1)
      *it=so_start_client_tcp("localhost", 5060);
    else
      *it=so_start_client_tcp_ssl("localhost", 5061);

  }
}

void read_handler(const char* buf, size_t size, void* ref) {
  //std::cout << "read:" << ref << std::string(buf, size) << std::endl;
  so_write_some(ref, "yyyy\r\n\r\n", 8);
  if(rand()%3==1)
    so_destr_client_tcp(ref);
}

void error_handler(void* ref, const char* err) {
  //std::cout << "err:" << ref << std::string(err) << std::endl;
}

void tunnel_connect_handler(void* ref) {
  //std::cout << "connect:" << ref << so_socket(ref) << std::endl;
  so_tunnel_write_some(ref, "GGG\r\n\r\n", 7, DT_SIP);
  so_tunnel_write_some(ref, "RRR\r\n\r\n", 7, DT_RTP, "VOICE", 5);
}

void tunnel_disconnect_handler(void* ref) {
  //std::cout << "disconnect:" << ref << std::endl;
  boost::shared_lock<boost::shared_mutex> l(r_mutex);
  std::vector<void*>::iterator it=std::find(r.begin(), r.end(), ref);
  if (it!=r.end()) {
    *it=so_start_tunnel_tcp("localhost", 5062);
  }
}

void tunnel_read_handler(const char* buf, size_t size, unsigned int data_type, void* ref, char* name_, unsigned char name_sz) {
  std::cout << "read:" << ref << std::string(buf, size) << std::endl;
  if(rand()%2==1)
    so_tunnel_write_some(ref, "DDDDDDD\r\n\r\n", 11, DT_SIP);
  else
    so_tunnel_write_some(ref, "RRRRRRR\r\n\r\n", 11, DT_RTP, "VOICE", 5);
  if(rand()%3==1)
    so_destr_client_tcp(ref);
}

void daemon () {
  while (!flagExit)
  {
    void* z=r[rand()%r.size()];
    so_destr_client_tcp(z);
    Sleep(100);
  }
}

void main(int argc, char* argv[]) {
  if (argc!=2) {
    std::cout << "Usage: <port>\n" ;
    return;
  }
  setlocale(LC_ALL, "English");
  
  so_debug(true);

  so_set_start_handler(&connect_handler);
  so_set_destr_handler(&disconnect_handler);
  so_set_read_handler(&read_handler);
  so_set_error_handler(&error_handler);
  so_set_tunnel_read_handler(&tunnel_read_handler);
  so_set_tunnel_start_handler(&tunnel_connect_handler);
  so_set_tunnel_destr_handler(&tunnel_disconnect_handler);

  /*so_set_ssl_pem("", "cacert83.pem");

  so_start_client_tcp("10.10.10.85", atoi(argv[1])+1);

  so_run();

  return ;*/

  void* a=so_start_server_tcp(atoi(argv[1]));
  void* b=so_start_server_tcp_ssl(atoi(argv[1])+1);
  void* c=so_start_tunnel_server_tcp(atoi(argv[1])+2);

  {
    boost::unique_lock<boost::shared_mutex> l(r_mutex);
    for (int i=0;i<1;i++) {
      r.push_back(so_start_client_tcp("localhost", atoi(argv[1])));
      r.push_back(so_start_client_tcp_ssl("localhost", atoi(argv[1])+1));
      r.push_back(so_start_tunnel_tcp("localhost", atoi(argv[1])+2));
    }
  }

  boost::thread t(&daemon);

  so_run_no_wait(1);

  std::cout << "wait>";
  int k; std::cin >> k;
  std::cout << "exit, please wait...\n";
  flagExit=true;
  t.join();

  so_destr_server_tcp(a);
  so_destr_server_tcp_ssl(b);
  so_destr_server_tcp(c);
  so_stop();
  std::cout << "stop\n";
  std::cout << "end.\n";
}