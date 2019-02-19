//---------------------------------------------------------------------------

#ifndef R_FastFourieTransform_OddH
#define R_FastFourieTransform_OddH
//---------------------------------------------------------------------------
#include "WinRDefs.h"
#include "D_FastFourieTransform_Even.h"
//----------------------------------------------------------------------------
#ifdef Full_Fourie_Transform
void __fastcall rdft_odd(vector<complex<double> >&, vector<complex<double> >&, TCoeff_BY_2&); //Прямое преобразование Фурье для нечетных гармоник
#endif
//----------------------------------------------------------------------------
#endif
