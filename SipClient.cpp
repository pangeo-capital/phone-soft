//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
USEFORM("SipClient_Unit.cpp", MainFormSLS);
USEFORM("CallIn_Unit.cpp", Form1);
USEFORM("Unit_Video_Cap.cpp", Form2);
USEFORM("Unit4.cpp", Form4);
USEFORM("Unit3.cpp", Form3);
USEFORM("ContactMenu_Unit.cpp", ContactMenu);
USEFORM("AddContact_Unit.cpp", AddContact);
USEFORM("Test_Unit.cpp", Test);
USEFORM("About_Unit.cpp", AboutWin);
USEFORM("SoundTool_Unit.cpp", SoundTool);
USEFORM("RegistryPanel_Unit.cpp", RegistryPanel);
USEFORM("SipTransport.cpp", Transport);
USEFORM("Test_Sound.cpp", TTest_Sound);
USEFORM("StartOptions_Unit.cpp", StartOptionsWin);
USEFORM("DialPad_FORM.cpp", DialPad);
USEFORM("Unit_EnterpriseSubscList.cpp", EnterpriseSubscList);
USEFORM("Refer_Unit.cpp", ReferWin);
USEFORM("ParallelPhone_Unit.cpp", ParallelPhone);
USEFORM("Conference_Unit.cpp", ConferenceWin);

#pragma comment(lib, "cache_db_lib.lib")
#pragma comment(lib, "rstrdp.lib")
#pragma comment(lib, "videoCam.lib")
#pragma comment(lib, "vencdec.lib")
#pragma comment(lib, "transmit_file_lib.lib")
#pragma comment(lib, "tls_sock.lib")
#pragma comment(lib, "rsrtp.lib")
#pragma comment(lib, "ipps-8.0.lib")
#pragma comment(lib, "ippsc-8.0.lib")

//[Linker Error] Unresolved external 'ippsIIR16sLow_G729_16s' referenced from D:\ANDREY\RASTEL\BC\SIPCLIENTDESKTOP\IPP\G729\ENCG7291.OBJ
//---------------------------------------------------------------------------
#include "WinRDefs.h"
#include "utils.h"
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    const string app_class    = "TApplication";
    const string app_name     =  "Contact"; //From Project->Options->Application->Title or Application->Title (Must be identical for INNO installer "MyAppName")
    const string win_class    = "TMainFormSLS";
    const string gl_atom_name = "h70fgt_contact_sip_client_x0sf3mrty7qzw";
    bool rv = false;
    try{
       rv = exs_app_runnig(gl_atom_name,app_class,app_name,win_class);
       if(rv)
          return 0;
       try{
           Application->Initialize();
           Application->Title = "Contact";
                 Application->CreateForm(__classid(TMainFormSLS), &MainFormSLS);
         Application->CreateForm(__classid(TForm2), &Form2);
         Application->CreateForm(__classid(TForm4), &Form4);
         Application->CreateForm(__classid(TForm3), &Form3);
         Application->CreateForm(__classid(TContactMenu), &ContactMenu);
         Application->CreateForm(__classid(TAddContact), &AddContact);
         Application->CreateForm(__classid(TTest), &Test);
         Application->CreateForm(__classid(TAboutWin), &AboutWin);
         Application->CreateForm(__classid(TSoundTool), &SoundTool);
         Application->CreateForm(__classid(TTransport), &Transport);
         Application->CreateForm(__classid(TTTest_Sound), &TTest_Sound);
         Application->CreateForm(__classid(TStartOptionsWin), &StartOptionsWin);
         Application->CreateForm(__classid(TDialPad), &DialPad);
         Application->CreateForm(__classid(TEnterpriseSubscList), &EnterpriseSubscList);
         Application->CreateForm(__classid(TReferWin), &ReferWin);
         Application->CreateForm(__classid(TConferenceWin), &ConferenceWin);
         Application->Run();
          }
       catch (Exception &exception)
        {
          Application->ShowException(&exception);
        }
       }
__finally
        {
        if(!rv)
           GlobalDeleteAtom(GlobalFindAtom(gl_atom_name.c_str()));
        }
return 0;
}
//---------------------------------------------------------------------------
