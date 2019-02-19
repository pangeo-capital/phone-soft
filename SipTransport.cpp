//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "SipTransport.h"
#include <registry.hpp>
#include "const.h"
#include "SipClient_Unit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TTransport *Transport;
//---------------------------------------------------------------------------
__fastcall TTransport::TTransport(TComponent* Owner)
        : TForm(Owner)
{
Color            = MainFormSLS->PanelColor;
ComboBox1->Style = Stdctrls::csDropDownList;
ComboBox1->Items->Append(sconst_UDP.c_str());
ComboBox1->Items->Append(sconst_TCP.c_str());
ComboBox1->Items->Append(sconst_TLS.c_str());
ComboBox1->Items->Append(sconst_TUNNEL.c_str());
ComboBox1->Items->Append(sconst_AUTO.c_str());
}
//---------------------------------------------------------------------------
void __fastcall TTransport::Button2Click(TObject *Sender)
{
Close();
}
//---------------------------------------------------------------------------
void __fastcall TTransport::Button1Click(TObject *Sender)
{
TRegistry& regKey = *new TRegistry();
regKey.RootKey = ROOT_KEY;
bool keyGood = regKey.OpenKey(key_name.c_str(),false);
if(!keyGood)
  keyGood = regKey.OpenKey(key_name.c_str(),true);
if(keyGood)
  {
  keyGood = regKey.OpenKey(transport_key_name.c_str(),false);
  if(!keyGood)
     keyGood = regKey.OpenKey(transport_key_name.c_str(),true);
  if(keyGood)
    {
    string old_trn = regKey.ReadString(sip_transp_name.c_str()).c_str();
    string s = ComboBox1->Text.c_str();
    Sip_Transport new_sip_transport = Sip_Transport_UNKNOWN;
    if(s == sconst_UDP)
       {
       new_sip_transport = Sip_Transport_UDP;
       MainFormSLS->Sip->Sip_TransportAuto = false;
       }
    else if(s == sconst_TCP)
       {
       new_sip_transport = Sip_Transport_TCP;
       MainFormSLS->Sip->Sip_TransportAuto = false;
       }
    else if(s == sconst_TLS)
       {
       new_sip_transport = Sip_Transport_TLS;
       MainFormSLS->Sip->Sip_TransportAuto = false;
       }
    else if(s == sconst_TUNNEL)
       {
       new_sip_transport = Sip_Transport_TUNNEL;
       MainFormSLS->Sip->Sip_TransportAuto = false;
       }
    else if(s == sconst_AUTO)
       {
       new_sip_transport = Sip_Transport_AUTO;
       MainFormSLS->Sip->Sip_TransportAuto = true;
       }


    if(new_sip_transport != Sip_Transport_UNKNOWN)
      {
      if(old_trn.empty())
         regKey.WriteString(sip_transp_name.c_str(),s.c_str());
      if(new_sip_transport != MainFormSLS->Sip->sip_transport)
        {
        if(!old_trn.empty())
           regKey.WriteString(sip_transp_name.c_str(),s.c_str());
        if(MainFormSLS->Sip->Sip_TransportAuto)
           MainFormSLS->Sip->sip_transport = Sip_Transport_UDP;
        MainFormSLS->Sip->sip_transport = new_sip_transport;
        }
      else
        {
        if(old_trn == sconst_AUTO)
         if(new_sip_transport == Sip_Transport_UDP)
           {
           regKey.WriteString(sip_transp_name.c_str(),s.c_str());
           MainFormSLS->Sip->sip_transport = new_sip_transport;
           }
        }
      }
    }
  regKey.CloseKey();
  }
delete &regKey;
Close();
}
//---------------------------------------------------------------------------


