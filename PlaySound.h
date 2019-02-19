//---------------------------------------------------------------------------

#ifndef PlaySoundH
#define PlaySoundH
//---------------------------------------------------------------------------
#include "WinRDefs.h"
#include "BaseThread.h"
//---------------------------------------------------------------------------
const playReorder_Count = 2;
//---------------------------------------------------------------------------
typedef enum{
playSoundState_PlayRing,
playSoundState_PlayRing_1,
playSoundState_PlayRingPause,
playSoundState_FileReceiveNotify,
playSoundState_Free,
playSoundState_Reorder,
playSoundState_Busy,
playSoundState_Hangup,
}playSoundState;
//---------------------------------------------------------------------------
class TPlaySoundThread : public TBaseThread{
playSoundState pss;
public:
__fastcall TPlaySoundThread(bool CS, TEventLogThread** ELTP, TSip* SIP):TBaseThread(CS, ELTP, SIP){
                           pss = playSoundState_Free;
                           }
void           __fastcall setPss(playSoundState a){pss = a;}
playSoundState __fastcall getPss(){return pss;}
void __fastcall Execute();                           
};
//-----------------------------------------------------------------------------
#endif

                                                                  
