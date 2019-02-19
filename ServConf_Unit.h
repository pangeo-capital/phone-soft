//---------------------------------------------------------------------------
#ifndef ServConf_UnitH
#define ServConf_UnitH

#include <Grids.hpp>
#include "WinRDefs.h"
#include "utils.h"
#include "Sip.h"
//---------------------------------------------------------------------------
class TServConf_Panel : public TPanel{
Lang lng;
int ServConfPanel1_CONTACT_LIST_SIZE;
public:
TContacts conf_contacts;
TDrawGrid* dg1; TLabel* lb1;
TButton* btn_ok;
TButton* btn_cancel;
     __fastcall TServConf_Panel(TComponent*,Lang,int,int);
void __fastcall OK_OnClick(TObject* Sender);
void __fastcall Cancel_OnClick(TObject* Sender);
void __fastcall DG1DrawCell(TObject *Sender, int ACol, int ARow, const TRect &Rect, TGridDrawState State);
};
//---------------------------------------------------------------------------
#endif
