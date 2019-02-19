#ifndef SIP_CONST__H
#define SIP_CONST__H
#include <map>
#include <string>

using namespace std;
//------------------------------------------------------------------------------
const string __http__           = "http://";
const string __https__          = "https://";
const string __www__            = "www.";
const string __href__           = "href=";
const string __a_href__         = "<a href=";
const string __A_href__         = "<A href=";
//------------------------------------------------------------------------------
const string auto_run_key_name = "Software\\Microsoft\\Windows\\CurrentVersion\\Run";
const string key_name       = "SOFTWARE\\Pangeo\\RSC";
const string dev_key_name   = "Dev";
const string parallel_phone = "PPh";
const string pph_active     = "Active";
const string pph_port       = "Port";
const string pph_name       = "Name";
const string acc_key_name   = "Acc";
const string acc_pwd        = "1";
const string acc_name       = "2";
const string acc_dname      = "3";
const string pid            = "Pid";
const string local_display_name = "&&&"; //if SipClient.ini contains DisplayName = &&&, DisplayName read from RegPanel
const string sound_key_name        = "S";
const string video_key_name        = "V";
const string sound_in_device_name  = "in_s_dev";
const string sound_out_device_name = "out_s_dev";
const string video_in_device_name  = "in_v_dev";
const string transport_key_name    = "Transp";
const string sip_transp_name       = "Sip";
const string pid_value             = "a";

//------------------------------------------------------------------------------
const string sconst_UDP    = "UDP";
const string sconst_TCP    = "TCP";
const string sconst_TLS    = "TLS";
const string sconst_TUNNEL = "TUNNEL";
const string sconst_AUTO   = "AUTO";
//------------------------------------------------------------------------------
typedef enum{
Sip_Transport_UDP,
Sip_Transport_TCP,
Sip_Transport_TLS,
Sip_Transport_TUNNEL,
Sip_Transport_AUTO,
Sip_Transport_UNKNOWN,
}Sip_Transport;
//------------------------------------------------------------------------------
#endif
