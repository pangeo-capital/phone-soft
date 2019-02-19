//---------------------------------------------------------------------------

#ifndef RegistryPanel_UnitH
#define RegistryPanel_UnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <map>
#include <vector>
#include <string>
//#include <queue.h>
#include "WinRDefs.h"
#include <Mask.hpp>

using namespace std;

#ifndef UBYTE
typedef unsigned char UBYTE;
#endif
//---------------------------------------------------------------------------
class TUserAccount{
public:
string user_name;
string user_pwd;
string user_displayname;
void __fastcall clear(){
                       user_name.clear();
                       user_pwd.clear();
                       user_displayname.clear();
                       }
};
//---------------------------------------------------------------------------
class TClientReg{
int crypt_len;
int base;
int b0,b1,b2,b3;
public:
bool pwd_chngd;
        __fastcall TClientReg();
void    __fastcall init(vector<UBYTE>&);
void    __fastcall encrypt(vector<UBYTE>&,const string&);
void    __fastcall vect_to_dig_str(string&,vector<UBYTE>&);
void    __fastcall dig_str_to_vect(vector<UBYTE>&,string&);
void    __fastcall encrypt_string(string&,const string&);
void    __fastcall registry_name(const string&,const string&);
void    __fastcall to_app_data(const string&,const string&);
string  __fastcall decrypt(vector<UBYTE>&);
bool    __fastcall is_wildcard(const string&);
};
//---------------------------------------------------------------------------
class TCryptoAccount{
public:
string user_name;
string s_crypto; //pwd + user_name
};
//-------------------------------------------------------------------------------
class TRegistryPanel : public TForm
{
TUserAccount ua;
TClientReg   cr;
vector<string> v;
map < string, TCryptoAccount > m;
bool NewRegistration;
__published:	// IDE-managed Components
        TEdit *Edit1;
        TEdit *Edit2;
        TLabel *Label1;
        TLabel *Label2;
        TButton *Button1;
        TButton *Button2;
        TEdit *Edit3;
        TLabel *Label3;
    TLabel *Label4;
    TImage *Image1;
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall Edit2Change(TObject *Sender);
        void __fastcall Edit2KeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall Edit1KeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
private:	// User declarations
public:		// User declarations
        __fastcall TRegistryPanel(TComponent* Owner);
bool    __fastcall getNewRegistration(){return NewRegistration;}
void    __fastcall setNewRegistration(bool a){NewRegistration = a;}
void    __fastcall read_client_accounts();
void    __fastcall read_account();
void    __fastcall SaveAccount();
};
//---------------------------------------------------------------------------
extern PACKAGE TRegistryPanel *RegistryPanel;
//---------------------------------------------------------------------------
#endif
