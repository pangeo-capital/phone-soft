//---------------------------------------------------------------------------

#ifndef R_FastFourieTransform_EvenH
#define R_FastFourieTransform_EvenH
//---------------------------------------------------------------------------
#include "WinRDefs.h"
#include "D_FastFourieTransform_Even.h"
//----------------------------------------------------------------------------
#ifdef Full_Fourie_Transform
void __fastcall rdft_even(vector<complex<double> >&, vector<complex<double> >&, TCoeff_BY_2&);
//----------------------------------------------------------------------------
#endif
#endif
