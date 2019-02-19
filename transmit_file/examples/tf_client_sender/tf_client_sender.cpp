// tf_server.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "transmitFile.h"
#include "win_file_utils.h"

int fsz=0;
int psz=0;

void send_call_back(const tf_common_event& Event) {
  switch (Event.tag) {
    case TF_TAG_ERROR_EVENT: 
      std::cout << "***call_back*** " << Event.id <<" : "<< Event.tag << std::endl;
      break;
    case TF_TAG_UPLOAD_INIT_EVENT:
    {
      tf_upload_init_event& e=(tf_upload_init_event&)Event;
      fsz=e.file_size;
      WinExec(std::string("c:\\ntutils\\0\\ptm.exe -p \"tf_client_receiver:\" -m 1090 -w "+intToStr(128+Event.id)).c_str(), SW_HIDE); 
      break;
    }
    case TF_TAG_UPLOAD_START_EVENT: 
      std::cout << "***call_back*** id : tag" << Event.id <<" : "<< Event.tag << std::endl;
      break;
    case TF_TAG_UPLOAD_PENDING_EVENT: 
    {
      /*tf_upload_pending_event& e=(tf_upload_pending_event&)Event;
      int szn=e.offset/double(fsz)*10.;
      while (szn>psz) psz++, std::cout << ".";*/
      std::cout << ".";
      break;
    }
    case TF_TAG_UPLOAD_COMPLETE_EVENT:
      std::cout << "***call_back*** id : tag" << Event.id <<" : "<< Event.tag << std::endl;
      break;
    default:
      std::cout << "***call_back*** id : tag" << Event.id <<" : "<< Event.tag << std::endl;
      break;
  }
};

BOOL WINAPI consoleHandler(DWORD dwCtrlType) {
  tf_destroy();
  return TRUE;
}

int _tmain(int argc, _TCHAR* argv[])
{

  SetConsoleCtrlHandler(consoleHandler, true);

  tf_init();
  
  tf_set_handler(send_call_back);

  std::string s=".";
  std::string opt="";
  if (argc>1)
    s=argv[1];
  if (argc>2)
    opt=argv[2];

  std::vector<std::string> v;
  get_file_list(s, "*.*", v, opt);

  for (std::vector<std::string>::iterator i=v.begin(), e=v.end(); i!=e; ++i) {
    std::cout << *i << " ";
    bool f=tf_send_file((*i).c_str(), (*i).size());
  }

  while (tf_rcvAndDisp()) {
    Sleep(1);
  }
	return 0;
}

