//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "RegistryPanel_Unit.h"
#include <Registry.hpp>
#include <Filectrl.hpp>
#include "SipClient_Unit.h"
#include "const.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

const string pwd_mask = "**********";
TRegistryPanel *RegistryPanel;
//---------------------------------------------------------------------------
__fastcall TRegistryPanel::TRegistryPanel(TComponent* Owner)
        : TForm(Owner)
{
Color = clWhite;
Edit1->MaxLength = 32;
Edit2->MaxLength = 32;
Edit3->MaxLength = 128;
Edit1->Ctl3D     = false;
Edit2->Ctl3D     = false;
Edit3->Ctl3D     = false;
Edit2->Top       = Edit1->Top + Edit1->Height + 3;
Label2->Top      = Edit2->Top + 2;
Edit3->Top       = Edit2->Top + Edit2->Height;
Label3->Top      = Edit3->Top + 2;
Button1->Left    = Edit1->Left;
Button1->Width   = Edit1->Width;
Button1->Caption = "Зарегистрироваться";
Button2->Visible = false;
NewRegistration  = false;
}
//---------------------------------------------------------------------------
__fastcall TClientReg::TClientReg()
{
crypt_len = 40;
base = 3;
b0   = 7;
b1   = 11;
b2   = 15;
b3   = 23;
pwd_chngd = false;
}
//---------------------------------------------------------------------------
void __fastcall TClientReg::init(vector<UBYTE>& v)
{
v.assign(crypt_len,0);
for(int i=0;i<crypt_len;i++)
     v[i] = random(255);
}
//---------------------------------------------------------------------------
void __fastcall TClientReg::encrypt(vector<UBYTE>& v,const string& s)
{
int len = s.length();
if(len < (crypt_len - 4))
  {
  for(int i=0,j=base;i<len;i++,j++)
     {
     if(j == b0)
        j++;
     else if(j == b1)
        j++;
     else if(j == b2)
        j++;
     else if(j == b3)
        j++;
     v[j] = s[i];
     }
  }
v[23] = len;
UBYTE x1 = v[b0];
UBYTE x2 = v[b1];
UBYTE x3 = v[b2];
for(int i = 0;i < crypt_len;i++)
   {
   if(i==b0)continue;
   if(i==b1)continue;
   if(i==b2)continue;
   v[i] = v[i]^x1^(~x2)^(x3);
   }
}
//---------------------------------------------------------------------------
void __fastcall TClientReg::vect_to_dig_str(string& s,vector<UBYTE>& v)
{
int sz = v.size();
for(int i=0;i<sz;i++)
   {
   s += inttohexstr(((v[i]>>4)&0xF),1);
   s += inttohexstr((v[i]&0xF),1);
   }
}
//---------------------------------------------------------------------------
void __fastcall TClientReg::dig_str_to_vect(vector<UBYTE>& v,string& s)
{
UBYTE x1,x2;
int len = s.length();
for(int i=0;i<len;i++)
    {
    if(i&1)
      {
      x2 = hex_str_to_int(s,i);
      UBYTE a = x1<<4;
      a &= 0xF0;
      a |= x2&0xF;
      v.push_back(a);
      }
    else
       x1 = hex_str_to_int(s,i);
    }
}
//---------------------------------------------------------------------------
void __fastcall TClientReg::registry_name(const string& s,const string& acc_elem)
{
TRegistry& regKey = *new TRegistry();
regKey.RootKey = ROOT_KEY;
bool keyGood = regKey.OpenKey(key_name.c_str(),false);
if(keyGood)
  {
  keyGood = regKey.OpenKey(acc_key_name.c_str(),false);
  if(keyGood)
     regKey.WriteString(acc_elem.c_str(),s.c_str());
  regKey.CloseKey();
  }
delete &regKey;
}
//---------------------------------------------------------------------------
void __fastcall TClientReg::to_app_data(const string& user_name,const string& pwd_enc)
{
if(check_directory_existence(MainFormSLS->get_clients_dir()))
  {
  string s = MainFormSLS->get_clients_dir() + "\\" + user_name;
  if(check_directory_existence(s))
    {
    string file_name = s + "\\" + "s";
    FILE* f = fopen(file_name.c_str(),"wt");
    if(f)
      {
      fputs(pwd_enc.c_str(),f);
      fclose(f);
      }
    }
  }
string s_cl = MainFormSLS->get_client_dir();
if(check_directory_existence(s_cl))
  {
  s_cl += "\\cl.rst";
  FILE* f = fopen(s_cl.c_str(),"wt");
  if(f)
    {
    fputs(user_name.c_str(),f);
    fclose(f);
    }
  }
 }
//---------------------------------------------------------------------------
void __fastcall TRegistryPanel::read_client_accounts()
{
v.clear();
AnsiString Path = MainFormSLS->get_clients_dir().c_str();
if(::DirectoryExists(Path))
  {
  int iAttributes = faDirectory; //	faAnyFile;
  TSearchRec sr;
  int retVal = FindFirst(Path + "\\*.*",iAttributes,sr);    //First found directory, specified in the Path
  if(!retVal)
    {
     while(FindNext(sr) == 0)
          {
          if(sr.Name == ".")continue;
          if(sr.Name == "..")continue;
          v.push_back(sr.Name.c_str());
          }
    FindClose(sr);
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TRegistryPanel::read_account()
{
ua.clear();
cr.pwd_chngd = false;
TRegistry& regKey = *new TRegistry();
regKey.RootKey = ROOT_KEY;
bool keyGood = regKey.OpenKey(key_name.c_str(),false);
if(keyGood)
  {
  keyGood = regKey.OpenKey(acc_key_name.c_str(),false);
  if(keyGood)
    {
    string user_name    = regKey.ReadString(acc_name.c_str()).c_str();
    string pwd          = regKey.ReadString(acc_pwd.c_str()).c_str();
    ua.user_displayname = regKey.ReadString(acc_dname.c_str()).c_str();
    vector<UBYTE> v_name;
    vector<UBYTE> v_pwd;
    cr.dig_str_to_vect(v_name,user_name);
    cr.dig_str_to_vect(v_pwd,pwd);
    ua.user_name = cr.decrypt(v_name);
    ua.user_pwd  = cr.decrypt(v_pwd);
    if(!ua.user_name.empty())
        Edit1->Text = ua.user_name.c_str();
    if(!ua.user_pwd.empty())
        Edit2->Text = pwd_mask.c_str();
    if(Edit3->Visible)
       if(!ua.user_displayname.empty())
         Edit3->Text = ua.user_displayname.c_str();
    }
  regKey.CloseKey();
  }
delete &regKey;
}
//---------------------------------------------------------------------------
string __fastcall TClientReg::decrypt(vector<UBYTE>& v)
{
string rv;
if(v.size() == (unsigned)crypt_len)
  {
  UBYTE x1  = v[b0];
  UBYTE x2  = v[b1];
  UBYTE x3  = v[b2];
  UBYTE len = v[b3]^x1^(~x2)^(x3);
  for(int i = 0;i < crypt_len;i++)
     v[i] = v[i]^x1^(~x2)^(x3);
  vector<UBYTE> v_out;
  for(int i = 0;i < crypt_len;i++)
     {
     if(i==b0) continue;
     if(i==b1)continue;
     if(i==b2)continue;
     if(i==b3)continue;
     v_out.push_back(v[i]);
     }
  v_out.resize(base + len);
  v_out.push_back(0);
  rv = string((char*)&v_out[base]);
  }
return rv;
}
//---------------------------------------------------------------------------
void __fastcall TClientReg::encrypt_string(string& out,const string& in)
{
out.clear();
vector<UBYTE> v;
init(v);
encrypt(v,in);
vect_to_dig_str(out,v);
}
//---------------------------------------------------------------------------
bool __fastcall TClientReg::is_wildcard(const string& s)
{
if(s == pwd_mask)
   return true;
return false;
}
//--------------------------------------------------------------------------
void __fastcall TRegistryPanel::Button1Click(TObject *Sender)
{
SaveAccount();
}
//---------------------------------------------------------------------------
void __fastcall TRegistryPanel::Button2Click(TObject *Sender)
{
Close();
}
//---------------------------------------------------------------------------
void __fastcall TRegistryPanel::Edit2Change(TObject *Sender)
{
int pwd_mask_length = pwd_mask.length();
string s = Edit2->Text.c_str();
if(s.length() == 1)
  {
  cr.pwd_chngd = true;
  return;
  }
bool templ = true;
if(!cr.pwd_chngd)
  {
  int len = s.length();
  if((len > (pwd_mask_length - 2)) && (len > (pwd_mask_length + 1)))
    {
    for(int i=0;i<len;i++)
       {
       if(s[i] != '*')
         {
         templ = false;
         break;
         }
       }
    }
  if(templ)
    {
    if(len == pwd_mask_length)
      return;
    cr.pwd_chngd = true;
    Edit2->Clear();
    }
  return;
  }
}
//---------------------------------------------------------------------------
void __fastcall TRegistryPanel::SaveAccount()
{
bool req_to_change  = false;

AnsiString NAME = Edit1->Text.Trim();
AnsiString PWD  = Edit2->Text.Trim();

string user_name    = NAME.c_str();
string pwd          = PWD.c_str();
string display_name = Edit3->Text.c_str();
bool wildcard    = cr.is_wildcard(pwd);
if(user_name != ua.user_name)
   req_to_change = true;
if(pwd != ua.user_pwd)
  if(!wildcard)
     req_to_change = true;
if(display_name != ua.user_displayname)
   req_to_change = true;
if(req_to_change)
  {
  MainFormSLS->Sip->Contacts.SS.clear_time_list();
  MainFormSLS->Sip->Contacts.AS.clear_time_list();
  MainFormSLS->NS.Final_Notify_Proc();
  MainFormSLS->Sip->Contacts.AS.Final_Subscribe_Proc();
  if(!MainFormSLS->Sip->Account.get_user_name().empty())
    {
    TAuthPar auth_par;
    auth_par.user_name = MainFormSLS->Sip->Account.get_user_name();
    auth_par.user_pwd  = MainFormSLS->Sip->Account.get_user_pwd();
    auth_par.domain    = MainFormSLS->Sip->Account.get_domain();
    MainFormSLS->Sip->finalRegistrationProc(&auth_par);
    }
  if(wildcard)
     pwd = ua.user_pwd;
  string name_enc;
  string pwd_enc;
  randomize();
  cr.encrypt_string(name_enc,user_name);
  cr.encrypt_string(pwd_enc,pwd);
  cr.registry_name(name_enc,acc_name);
  cr.registry_name(pwd_enc,acc_pwd);
  cr.to_app_data(user_name,pwd_enc);
  MainFormSLS->Sip->Account.set_user_name(user_name);
  MainFormSLS->Sip->Account.set_user_pwd(pwd);
  MainFormSLS->Sip->Account.in_contact_list = false;
  MainFormSLS->Sip->Account.displayname_clear();
  if(Edit3->Visible)
     {
     cr.registry_name(display_name,acc_dname);
     MainFormSLS->Sip->Account.set_displayname(display_name);
     }
  if(MainFormSLS->Sip->SubscDB.Port) //т.е. если работаем с внешней БД
     setNewRegistration(true);
  MainFormSLS->Sip->display_full_ser_name();
  if(!MainFormSLS->Sip->readPresenceComment())
    {
    MainFormSLS->NS.my_net_state_comment_clear();
    AnsiString S;
    MainFormSLS->NSP->comment->Caption = S;

    MainFormSLS->NSP->comment->Visible = false;
    MainFormSLS->NSP->Height           = 20;
    MainFormSLS->PageControl1->Top     = MainFormSLS->NSP->Top + MainFormSLS->NSP->Height + 2;
    MainFormSLS->Panel3->Top           = MainFormSLS->PageControl1->Top;
    MainFormSLS->PageControl1_Resize();
    }
  MainFormSLS->Sip->set_init_subscribe(false);
  MainFormSLS->Sip->initRegistrationProc();
  MainFormSLS->Sip->readContacts();
  }
MainFormSLS->Sip->readPresenceContactComment();
Close();
}
//------------------------------------------------------------------------------
void __fastcall TRegistryPanel::Edit2KeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
if(Key == 13) //Enter
   SaveAccount();
}
//---------------------------------------------------------------------------
void __fastcall TRegistryPanel::Edit1KeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
if(Key == 13) //Enter
   SaveAccount();
}
//---------------------------------------------------------------------------

