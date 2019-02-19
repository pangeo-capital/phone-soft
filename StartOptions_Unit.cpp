//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "StartOptions_Unit.h"
#include "SipClient_Unit.h"
#include <Registry.hpp>
#include <string>
#include "const.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)
#pragma resource "*.dfm"

TStartOptionsWin *StartOptionsWin;
//---------------------------------------------------------------------------
__fastcall TStartOptionsWin::TStartOptionsWin(TComponent* Owner)
        : TForm(Owner)
{
Color = MainFormSLS->PanelColor;
OnChowChecked = false;
}
//---------------------------------------------------------------------------
std::string __fastcall TStartOptionsWin::get_app_name(const std::string& s)
{
string app_name;
int st = s.rfind("\\");
if(st != -1)
  {
  string part_s = s.substr(0,st);
  app_name = s.substr(++st);
  st = app_name.find(".");
  if(st != -1)
    app_name.resize(st);
  }
return app_name;
}
//---------------------------------------------------------------------------
bool __fastcall TStartOptionsWin::not_changed()
{
bool rv = false;
if((OnChowChecked)&&(CheckBox1->Checked))
  {
  rv = true;
  Close();
  }
if((!OnChowChecked)&&(!CheckBox1->Checked))
  {
  rv = true;
  Close();
  }
return rv;
}
//---------------------------------------------------------------------------
void __fastcall TStartOptionsWin::Button1Click(TObject *Sender)
{
if(not_changed())return;
std::string full_app_name = Application->ExeName.c_str();
string app_name = get_app_name(full_app_name);
if(app_name.empty())
  {
  Close();
  return;
  }
AnsiString AppName = app_name.c_str();
TRegistry* regKey = new TRegistry();
regKey->RootKey = HKEY_CURRENT_USER;
bool keyGood = regKey->OpenKey(auto_run_key_name.c_str(),false);
if(keyGood)
  {
  if(CheckBox1->Checked)
    {
    if(!regKey->ValueExists(AppName))
       regKey->WriteString(AppName,full_app_name.c_str());
    }
  else
    {
    if(regKey->ValueExists(AppName))
      {
      TRegDataType RegDataType = regKey->GetDataType(AppName);
      if(RegDataType == rdString)
        {
        string value_data = regKey->ReadString(AppName).c_str();
        if(value_data == full_app_name)
           regKey->DeleteValue(AppName);
        }
      }
    }
  }
delete regKey;
Close();
}
//---------------------------------------------------------------------------
void __fastcall TStartOptionsWin::Button2Click(TObject *Sender)
{
Close();
}
//---------------------------------------------------------------------------
void __fastcall TStartOptionsWin::FormShow(TObject *Sender)
{
std::string full_app_name = Application->ExeName.c_str();
string app_name = get_app_name(full_app_name);
if(!app_name.empty())
  {
  AnsiString AppName = app_name.c_str();
  TRegistry* regKey = new TRegistry();
  regKey->RootKey = HKEY_CURRENT_USER;
  bool keyGood = regKey->OpenKey(auto_run_key_name.c_str(),false);
  if(keyGood)
    if(regKey->ValueExists(AppName))
      CheckBox1->Checked = true;
    else
      CheckBox1->Checked = false;
  delete regKey;
  }
OnChowChecked = CheckBox1->Checked;
}
//---------------------------------------------------------------------------

void __fastcall TStartOptionsWin::FormCreate(TObject *Sender)
{
if(MainFormSLS->ofs)
  if(MainFormSLS->ofs->elt)
    if(MainFormSLS->ofs->elt->getlog())
      {
      string TimeStr;
      TDateTime DateTime = DateTime.CurrentDateTime();
      exsDateTime(DateTime,TimeStr);
      string str = "\n" + (string)TimeStr + " TStartOptionsWin_CREATED! " + "\n";
      MainFormSLS->ofs->elt->FputEvt(str, 1);
      }
}
//---------------------------------------------------------------------------

