// tf_server.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "transmitFile.h"

int fsz=0;
int psz=0;

std::string patch;

void send_call_back(const tf_common_event& Event) {
  switch (Event.tag) {
    case TF_TAG_ERROR_EVENT: 
      std::cout << "***call_back*** " << Event.id <<" : "<< Event.tag << std::endl;
      break;
    case TF_TAG_DOWNLOAD_INIT_EVENT: 
    {
      tf_download_init_event& e=(tf_download_init_event&)Event;
      std::cout << std::string(e.file_name, e.fn_len) << " " << e.file_size << std::endl;
      fsz=e.file_size;
      std::string f=patch;
      if (*(--patch.end())=='\\')
        f.append(e.file_name, e.fn_len);
      tf_receive_file(Event.id, f.c_str(), f.size());
      break;
    }
    case TF_TAG_DOWNLOAD_START_EVENT: 
      std::cout << "***call_back*** id : tag" << Event.id <<" : "<< Event.tag << std::endl;
      break;
                                      
    case TF_TAG_DOWNLOAD_PENDING_EVENT: {
      /*tf_download_pending_event& e=(tf_download_pending_event&)Event;
      int szn=e.offset/double(fsz)*10.;
      while (szn>psz) psz++, std::cout << ".";
      //tf_receive_file_cancel(e.id);
      */
      std::cout << ".";
      break;
    }
                                        
    case TF_TAG_DOWNLOAD_COMPLETE_EVENT: 
      std::cout << "***call_back*** id : tag" << Event.id <<" : "<< Event.tag << std::endl;
      //tf_destroy();
      break;

    default:
      std::cout << "***call_back*** id : tag" << Event.id <<" : "<< Event.tag << std::endl;
                                         
  }
};

bool fInit=true;

BOOL WINAPI consoleHandler(DWORD dwCtrlType) {
  tf_destroy();
  fInit=false;
  return TRUE;
}

int _tmain(int argc, _TCHAR* argv[])
{
  SetConsoleCtrlHandler(consoleHandler, true);
  std::string name="tf_client_receiver:"+str_utils::intToStr(GetCurrentThreadId())+" ";
  SetConsoleTitle(name.c_str());

  tf_init();

  tf_set_handler(send_call_back);

  int id=1;

  if (argc>1)
    id=strToInt(argv[1]);

  patch=argv[0];
  patch=patch.substr(0, patch.find_last_of("\\/")+1)+"output\\";
  if (argc>2)
    patch=argv[2];

  std::cout << "session_id=" << id << " patch=" << patch << std::endl;

  #define WM_THREAD_COMMAND WM_USER+66


  BOOL bRet;
  MSG msg;
  while (1) {
    tf_rcvAndDisp();
    while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
      try {
        if (msg.message==WM_THREAD_COMMAND) {
          tf_prepare_receive_file(msg.wParam-128);
        }
        TranslateMessage(&msg); 
        DispatchMessage(&msg); 
      }
      catch (std::exception& E) {
        std::cout << E.what() << std::endl;
      }
    }
    if (!fInit)
      break;
    Sleep(1);
  }
	return 0;
}

