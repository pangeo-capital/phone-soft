#ifndef VENCPAR_H
#define VENCPAR_H
#include "utils.h"
#include "vencdec.h"
//------------------------------------------------------------------------------
class TVcamPar : public BaseExchangeBlock{
public:
int width;
int height;
int frame_size;
int fps;
__fastcall TVcamPar():BaseExchangeBlock(TVcamPar_BLOCKTYPE){width=0,height=0;frame_size;fps=0;}
};
//------------------------------------------------------------------------------
class TVencPar{
public:
int rgb24_yuv420_scalerId;
int encoderId;
TVcamPar vcp;
__fastcall TVencPar(){
                     rgb24_yuv420_scalerId = -1;
                     encoderId = -1;
                     }
__fastcall ~TVencPar(){
                      if(rgb24_yuv420_scalerId > 0)
                        vencdec_destroy_scaler(rgb24_yuv420_scalerId);
                      if(encoderId > 0)
                         vencdec_destroy_encoder(encoderId);
                      }
};
//----------------------------------------------------------------------------
#endif
