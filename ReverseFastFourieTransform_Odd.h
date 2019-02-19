//---------------------------------------------------------------------------

#ifndef ReverseFastFourieTransform_OddH
#define ReverseFastFourieTransform_OddH
//---------------------------------------------------------------------------
#include "WinRDefs.h"
#include "FastFourieTransform.h"
//----------------------------------------------------------------------------
void __fastcall rdft_odd(vector<complex<double> >&,TCoeff_BY_2&); //Прямое преобразование Фурье для нечетных гармоник
//----------------------------------------------------------------------------
#endif
