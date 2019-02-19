//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "PlaySound.h"
#include "SipClient_Unit.h"
#include "utils.h"

#pragma package(smart_init)
//---------------------------------------------------------------------------
void __fastcall TPlaySoundThread::Execute()
{
try{
while(!Terminated)
     {
     switch(pss){
           case playSoundState_Free:
                Suspend_Thread();
                break;
           case playSoundState_PlayRing:{
                string filename = MainFormSLS->getSoundDir() + "\\ring.wav";
                LPCSTR lpszSound = filename.c_str();
                UINT fuSound = SND_ASYNC;
                sndPlaySound(lpszSound,fuSound); //as fuSound == SND_SYNC, playSoundState may be changed
                Sleep(300);//Sleep(1000);
                if(pss == playSoundState_PlayRing)
                   pss = playSoundState_PlayRing_1;
                break;
                }
           case playSoundState_PlayRing_1:{
                string filename = MainFormSLS->getSoundDir() + "\\ring.wav";
                LPCSTR lpszSound = filename.c_str();
                UINT fuSound = SND_ASYNC;
                sndPlaySound(lpszSound,fuSound); //as fuSound == SND_SYNC, playSoundState may be changed
                Sleep(300);
                if(pss == playSoundState_PlayRing_1)
                   pss = playSoundState_PlayRingPause;
                break;
                }
           case playSoundState_PlayRingPause:
                Sleep(3000);
                if(pss == playSoundState_PlayRingPause)
                   pss = playSoundState_PlayRing;
                break;
           case playSoundState_FileReceiveNotify:{
                string filename = MainFormSLS->getSoundDir() + "\\file_notify.wav";
                LPCSTR lpszSound = filename.c_str();
                UINT fuSound = SND_ASYNC;
                //auxSetVolume(WAVE_MAPPER, 0x1FFF1FFF);
                sndPlaySound(lpszSound,fuSound); //as fuSound == SND_SYNC, playSoundState may be changed
                pss = playSoundState_Free;
                break;
                }
           case playSoundState_Reorder:{
                string filename = MainFormSLS->getSoundDir() + "\\reorder.wav";
                LPCSTR lpszSound = filename.c_str();
                UINT fuSound = SND_ASYNC;
                for(int i=0;i<playReorder_Count;i++)
                   {
                   if(pss == playSoundState_Free)
                     {
                      sndPlaySound(NULL,fuSound);
                      break;
                     }
                   sndPlaySound(lpszSound,fuSound); //as fuSound == SND_SYNC, playSoundState may be changed
                   Sleep(2000);
                   }
                ::PostMessage(MainFormSLS->Sip->getMFHandle(), SIP_UA_MSG, WM_APP_MSG_WPARAM__UAC, WM_APP_MSG_LPARAM__END_OF_PLAY_REORDER);
                pss = playSoundState_Free;
                break;
                }
           case playSoundState_Busy:{
                string filename = MainFormSLS->getSoundDir() + "\\busy.wav";
                LPCSTR lpszSound = filename.c_str();
                UINT fuSound = SND_ASYNC;
                sndPlaySound(lpszSound,fuSound); //as fuSound == SND_SYNC, playSoundState may be changed
                ::Sleep(6000); //6  sec
                ::PostMessage(MainFormSLS->Sip->getMFHandle(), SIP_UA_MSG, WM_APP_MSG_WPARAM__UAC, WM_APP_MSG_LPARAM__END_OF_PLAY_BUSY);
                pss = playSoundState_Free;
                break;
                }
           case playSoundState_Hangup:{
                string filename = MainFormSLS->getSoundDir() + "\\hangup.wav";
                LPCSTR lpszSound = filename.c_str();
                UINT fuSound = SND_ASYNC;
                sndPlaySound(lpszSound,fuSound);
                pss = playSoundState_Free;
                break;
                }
           }
     }
}//try
catch(Exception& e){exsSstEXCEPTION(*eltp,"__TPlaySoundThread::Execute",e);}
}
//---------------------------------------------------------------------------

