#ifndef SIP_CLIENT_AUDIO_INTERFACE_H
#define SIP_CLIENT_AUDIO_INTERFACE_H

#include "LogExchBuf.h"
#include "AecControl.h"
//-----------------------------------------------------------------------
typedef  bool  (*pfinFunc_AudioInterfaceControl)(TEvtLogDll*);
//------------------------------------------------------------------------
class TAudioIntDll{
public:
bool Initiated;
HINSTANCE HINST;
pfinFunc_AudioInterfaceControl pFunc_AIC;
TAudioIntDll(){
           Initiated = false;
           HINST     = NULL;
           pFunc_AIC = NULL;
           }
};
//-------------------------------------------------------------------------
typedef  void*      (*pfinFunc_CreateExchStruct)();
typedef  void       (*pfinFunc_FreeExchStruct)(void*);
typedef  bool       (*pfinFunc_CheckCaptureDSP)();
typedef  bool       (*pfinFunc_CaptureDSP)(TAecControl*,void*);
typedef  TAExchBuf* (*pfinFunc_GetAudioPacket)(void*);
typedef  void       (*pfinFunc_FreeExchBuf)(TAExchBuf*);
typedef  bool       (*pfinFunc_UnInit)();
//----------------------------------------------------------------------
class TAecDll{
public:
bool Initiated;
HINSTANCE HINST;
pfinFunc_CreateExchStruct pFunc_CreateExchStruct;
pfinFunc_FreeExchStruct   pFunc_FreeExchStruct;
pfinFunc_CheckCaptureDSP  pFunc_CheckCaptureDSP;
pfinFunc_CaptureDSP       pFunc_CaptureDSP;
pfinFunc_GetAudioPacket   pFunc_GetAudioPacket;
pfinFunc_FreeExchBuf      pFunc_FreeExchBuf;
pfinFunc_UnInit           pFunc_UnInit;
TAecDll(){
         Initiated              = false;
         HINST                  = NULL;
         pFunc_CreateExchStruct = NULL;
         pFunc_FreeExchStruct   = NULL;
         pFunc_CheckCaptureDSP  = NULL;
         pFunc_CaptureDSP       = NULL;
         pFunc_GetAudioPacket   = NULL;
         pFunc_FreeExchBuf      = NULL;
         pFunc_UnInit           = NULL;
         }
};
//------------------------------------------------------------------------
#endif
 