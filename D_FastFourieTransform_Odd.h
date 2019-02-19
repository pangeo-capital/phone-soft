//---------------------------------------------------------------------------

#ifndef D_FastFourieTransform_OddH
#define D_FastFourieTransform_OddH
//---------------------------------------------------------------------------
#include "WinRDefs.h"
#include "D_FastFourieTransform_Even.h"
//----------------------------------------------------------------------------
#ifdef Full_Fourie_Transform
void __fastcall dfft_odd(vector<short>&, vector<complex<double> >&, TCoeff_BY_2&);    //Прямое преобразование Фурье для нечетных отсчетов
#endif
//---------------------------------------------------------------------------
#endif
