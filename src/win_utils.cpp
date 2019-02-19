//---------------------------------------------------------------------------


#pragma hdrstop

#include "win_utils.h"
#include "windows.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

void ShellExecuteMy(const std::string& fn, int cmd_show) {
  SHELLEXECUTEINFO ShExecInfo = {0};
  ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
  ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
  ShExecInfo.hwnd = NULL;
  ShExecInfo.lpVerb = NULL;
  ShExecInfo.lpFile = fn.c_str();
  ShExecInfo.lpParameters = "";   
  ShExecInfo.lpDirectory = NULL;
  ShExecInfo.nShow = cmd_show;         //SW_SHOW
  ShExecInfo.hInstApp = NULL; 
  ShellExecuteEx(&ShExecInfo);
}
