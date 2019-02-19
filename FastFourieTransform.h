//---------------------------------------------------------------------------
#ifndef FastFourieTransformH
#define FastFourieTransformH

#include "WinRDefs.h"
#include <vector>
#include <complex.h>

using namespace std;
//-----------------------------------------------------------------------------
class TCoeff_BY_2{
public:
int N;
vector<complex<double> > v;
__fastcall TCoeff_BY_2(int N_2){
                               v.resize(N_2,complex<double>(0,0));
                               N = 160;
                               }
};
//----------------------------------------------------------------------------
void __fastcall dfft_even(vector<short>&,TCoeff_BY_2&);   //Прямое преобразование Фурье для четных отсчетов
void __fastcall rdft_even(vector<complex<double> >&,TCoeff_BY_2&); //Обратное преобразование Фурье для четных гармоник
//----------------------------------------------------------------------------
#endif
