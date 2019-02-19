//---------------------------------------------------------------------------
#ifndef D_FastFourieTransform_EvenH
#define D_FastFourieTransform_EvenH

#include "WinRDefs.h"
#include <vector>
#include <complex.h>
#include <map>

using namespace std;
//-----------------------------------------------------------------------------
class TCoeff_BY_2{
public:
int N;
vector<complex<double> > v; //спектр в комплексном виде
__fastcall TCoeff_BY_2(int N_2){
                               v.resize(N_2,complex<double>(0,0));
                               N = 160;
                               }
};
//----------------------------------------------------------------------------
#ifdef Full_Fourie_Transform
void __fastcall dfft_even(vector<short>&, vector<complex<double> >&, TCoeff_BY_2&);   //Прямое преобразование Фурье для четных отсчетов
#endif
//----------------------------------------------------------------------------
#endif
