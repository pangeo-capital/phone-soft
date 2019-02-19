//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "R_FastFourieTransform_Even.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#ifdef Full_Fourie_Transform
void __fastcall rdft_even(vector<complex<double> >& out,vector<complex<double> >& hh_1,TCoeff_BY_2& c2)
{
int N_2 = c2.N;
vector<complex<double> > CC;
vector<complex<double> > NN;
complex<double> s;

/* CC[0] */ CC.push_back((c2.v[0] + c2.v[40]));
/* CC[1] */ CC.push_back((c2.v[1] + c2.v[41]));
/* CC[2] */ CC.push_back((c2.v[2] + c2.v[42]));
/* CC[3] */ CC.push_back((c2.v[3] + c2.v[43]));
/* CC[4] */ CC.push_back((c2.v[4] + c2.v[44]));
/* CC[5] */ CC.push_back((c2.v[5] + c2.v[45]));
/* CC[6] */ CC.push_back((c2.v[6] + c2.v[46]));
/* CC[7] */ CC.push_back((c2.v[7] + c2.v[47]));
/* CC[8] */ CC.push_back((c2.v[8] + c2.v[48]));
/* CC[9] */ CC.push_back((c2.v[9] + c2.v[49]));
/* CC[10] */ CC.push_back((c2.v[10] + c2.v[50]));
/* CC[11] */ CC.push_back((c2.v[11] + c2.v[51]));
/* CC[12] */ CC.push_back((c2.v[12] + c2.v[52]));
/* CC[13] */ CC.push_back((c2.v[13] + c2.v[53]));
/* CC[14] */ CC.push_back((c2.v[14] + c2.v[54]));
/* CC[15] */ CC.push_back((c2.v[15] + c2.v[55]));
/* CC[16] */ CC.push_back((c2.v[16] + c2.v[56]));
/* CC[17] */ CC.push_back((c2.v[17] + c2.v[57]));
/* CC[18] */ CC.push_back((c2.v[18] + c2.v[58]));
/* CC[19] */ CC.push_back((c2.v[19] + c2.v[59]));
/* CC[20] */ CC.push_back((c2.v[20] + c2.v[60]));
/* CC[21] */ CC.push_back((c2.v[21] + c2.v[61]));
/* CC[22] */ CC.push_back((c2.v[22] + c2.v[62]));
/* CC[23] */ CC.push_back((c2.v[23] + c2.v[63]));
/* CC[24] */ CC.push_back((c2.v[24] + c2.v[64]));
/* CC[25] */ CC.push_back((c2.v[25] + c2.v[65]));
/* CC[26] */ CC.push_back((c2.v[26] + c2.v[66]));
/* CC[27] */ CC.push_back((c2.v[27] + c2.v[67]));
/* CC[28] */ CC.push_back((c2.v[28] + c2.v[68]));
/* CC[29] */ CC.push_back((c2.v[29] + c2.v[69]));
/* CC[30] */ CC.push_back((c2.v[30] + c2.v[70]));
/* CC[31] */ CC.push_back((c2.v[31] + c2.v[71]));
/* CC[32] */ CC.push_back((c2.v[32] + c2.v[72]));
/* CC[33] */ CC.push_back((c2.v[33] + c2.v[73]));
/* CC[34] */ CC.push_back((c2.v[34] + c2.v[74]));
/* CC[35] */ CC.push_back((c2.v[35] + c2.v[75]));
/* CC[36] */ CC.push_back((c2.v[36] + c2.v[76]));
/* CC[37] */ CC.push_back((c2.v[37] + c2.v[77]));
/* CC[38] */ CC.push_back((c2.v[38] + c2.v[78]));
/* CC[39] */ CC.push_back((c2.v[39] + c2.v[79]));
/* CC[40] */ CC.push_back(CC[0] + CC[20]);
/* CC[41] */ CC.push_back(CC[1] + CC[21]);
/* CC[42] */ CC.push_back(CC[2] + CC[22]);
/* CC[43] */ CC.push_back(CC[3] + CC[23]);
/* CC[44] */ CC.push_back(CC[4] + CC[24]);
/* CC[45] */ CC.push_back(CC[5] + CC[25]);
/* CC[46] */ CC.push_back(CC[6] + CC[26]);
/* CC[47] */ CC.push_back(CC[7] + CC[27]);
/* CC[48] */ CC.push_back(CC[8] + CC[28]);
/* CC[49] */ CC.push_back(CC[9] + CC[29]);
/* CC[50] */ CC.push_back(CC[10] + CC[30]);
/* CC[51] */ CC.push_back(CC[11] + CC[31]);
/* CC[52] */ CC.push_back(CC[12] + CC[32]);
/* CC[53] */ CC.push_back(CC[13] + CC[33]);
/* CC[54] */ CC.push_back(CC[14] + CC[34]);
/* CC[55] */ CC.push_back(CC[15] + CC[35]);
/* CC[56] */ CC.push_back(CC[16] + CC[36]);
/* CC[57] */ CC.push_back(CC[17] + CC[37]);
/* CC[58] */ CC.push_back(CC[18] + CC[38]);
/* CC[59] */ CC.push_back(CC[19] + CC[39]);
/* CC[60] */ CC.push_back((c2.v[0] + c2.v[16] + c2.v[32] + c2.v[48] + c2.v[64]));
/* CC[61] */ CC.push_back((c2.v[1] + c2.v[17] + c2.v[33] + c2.v[49] + c2.v[65]));
/* CC[62] */ CC.push_back((c2.v[2] + c2.v[18] + c2.v[34] + c2.v[50] + c2.v[66]));
/* CC[63] */ CC.push_back((c2.v[3] + c2.v[19] + c2.v[35] + c2.v[51] + c2.v[67]));
/* CC[64] */ CC.push_back((c2.v[4] + c2.v[20] + c2.v[36] + c2.v[52] + c2.v[68]));
/* CC[65] */ CC.push_back((c2.v[5] + c2.v[21] + c2.v[37] + c2.v[53] + c2.v[69]));
/* CC[66] */ CC.push_back((c2.v[6] + c2.v[22] + c2.v[38] + c2.v[54] + c2.v[70]));
/* CC[67] */ CC.push_back((c2.v[7] + c2.v[23] + c2.v[39] + c2.v[55] + c2.v[71]));
/* CC[68] */ CC.push_back((c2.v[8] + c2.v[24] + c2.v[40] + c2.v[56] + c2.v[72]));
/* CC[69] */ CC.push_back((c2.v[9] + c2.v[25] + c2.v[41] + c2.v[57] + c2.v[73]));
/* CC[70] */ CC.push_back((c2.v[10] + c2.v[26] + c2.v[42] + c2.v[58] + c2.v[74]));
/* CC[71] */ CC.push_back((c2.v[11] + c2.v[27] + c2.v[43] + c2.v[59] + c2.v[75]));
/* CC[72] */ CC.push_back((c2.v[12] + c2.v[28] + c2.v[44] + c2.v[60] + c2.v[76]));
/* CC[73] */ CC.push_back((c2.v[13] + c2.v[29] + c2.v[45] + c2.v[61] + c2.v[77]));
/* CC[74] */ CC.push_back((c2.v[14] + c2.v[30] + c2.v[46] + c2.v[62] + c2.v[78]));
/* CC[75] */ CC.push_back((c2.v[15] + c2.v[31] + c2.v[47] + c2.v[63] + c2.v[79]));
/* CC[76] */ CC.push_back(CC[0] + CC[10] + CC[20] + CC[30]);
/* CC[77] */ CC.push_back(CC[1] + CC[11] + CC[21] + CC[31]);
/* CC[78] */ CC.push_back(CC[2] + CC[12] + CC[22] + CC[32]);
/* CC[79] */ CC.push_back(CC[3] + CC[13] + CC[23] + CC[33]);
/* CC[80] */ CC.push_back(CC[4] + CC[14] + CC[24] + CC[34]);
/* CC[81] */ CC.push_back(CC[5] + CC[15] + CC[25] + CC[35]);
/* CC[82] */ CC.push_back(CC[6] + CC[16] + CC[26] + CC[36]);
/* CC[83] */ CC.push_back(CC[7] + CC[17] + CC[27] + CC[37]);
/* CC[84] */ CC.push_back(CC[8] + CC[18] + CC[28] + CC[38]);
/* CC[85] */ CC.push_back(CC[9] + CC[19] + CC[29] + CC[39]);
/* CC[86] */ CC.push_back(CC[0] + CC[8] + CC[16] + CC[24] + CC[32]);
/* CC[87] */ CC.push_back(CC[1] + CC[9] + CC[17] + CC[25] + CC[33]);
/* CC[88] */ CC.push_back(CC[2] + CC[10] + CC[18] + CC[26] + CC[34]);
/* CC[89] */ CC.push_back(CC[3] + CC[11] + CC[19] + CC[27] + CC[35]);
/* CC[90] */ CC.push_back(CC[4] + CC[12] + CC[20] + CC[28] + CC[36]);
/* CC[91] */ CC.push_back(CC[5] + CC[13] + CC[21] + CC[29] + CC[37]);
/* CC[92] */ CC.push_back(CC[6] + CC[14] + CC[22] + CC[30] + CC[38]);
/* CC[93] */ CC.push_back(CC[7] + CC[15] + CC[23] + CC[31] + CC[39]);
/* CC[94] */ CC.push_back(CC[0] + CC[5] + CC[10] + CC[15] + CC[20] + CC[25] + CC[30] + CC[35]);
/* CC[95] */ CC.push_back(CC[1] + CC[6] + CC[11] + CC[16] + CC[21] + CC[26] + CC[31] + CC[36]);
/* CC[96] */ CC.push_back(CC[2] + CC[7] + CC[12] + CC[17] + CC[22] + CC[27] + CC[32] + CC[37]);
/* CC[97] */ CC.push_back(CC[3] + CC[8] + CC[13] + CC[18] + CC[23] + CC[28] + CC[33] + CC[38]);
/* CC[98] */ CC.push_back(CC[4] + CC[9] + CC[14] + CC[19] + CC[24] + CC[29] + CC[34] + CC[39]);
/* CC[99] */ CC.push_back(CC[0] + CC[4] + CC[8] + CC[12] + CC[16] + CC[20] + CC[24] + CC[28] + CC[32] + CC[36]);
/* CC[100] */ CC.push_back(CC[1] + CC[5] + CC[9] + CC[13] + CC[17] + CC[21] + CC[25] + CC[29] + CC[33] + CC[37]);
/* CC[101] */ CC.push_back(CC[2] + CC[6] + CC[10] + CC[14] + CC[18] + CC[22] + CC[26] + CC[30] + CC[34] + CC[38]);
/* CC[102] */ CC.push_back(CC[3] + CC[7] + CC[11] + CC[15] + CC[19] + CC[23] + CC[27] + CC[31] + CC[35] + CC[39]);

/* NN[0] */ NN.push_back(c2.v[0]*hh_1[0]);
/* NN[1] */ NN.push_back(c2.v[2]*hh_1[4]);
/* NN[2] */ NN.push_back(c2.v[4]*hh_1[8]);
/* NN[3] */ NN.push_back(c2.v[5]*hh_1[10]);
/* NN[4] */ NN.push_back(c2.v[6]*hh_1[12]);
/* NN[5] */ NN.push_back(c2.v[8]*hh_1[16]);
/* NN[6] */ NN.push_back(c2.v[10]*hh_1[20]);
/* NN[7] */ NN.push_back(c2.v[12]*hh_1[24]);
/* NN[8] */ NN.push_back(c2.v[14]*hh_1[28]);
/* NN[9] */ NN.push_back(c2.v[15]*hh_1[30]);
/* NN[10] */ NN.push_back(c2.v[16]*hh_1[32]);
/* NN[11] */ NN.push_back(c2.v[18]*hh_1[36]);
/* NN[12] */ NN.push_back(c2.v[20]*hh_1[40]);
/* NN[13] */ NN.push_back(c2.v[22]*hh_1[44]);
/* NN[14] */ NN.push_back(c2.v[24]*hh_1[48]);
/* NN[15] */ NN.push_back(c2.v[25]*hh_1[50]);
/* NN[16] */ NN.push_back(c2.v[26]*hh_1[52]);
/* NN[17] */ NN.push_back(c2.v[28]*hh_1[56]);
/* NN[18] */ NN.push_back(c2.v[30]*hh_1[60]);
/* NN[19] */ NN.push_back(c2.v[32]*hh_1[64]);
/* NN[20] */ NN.push_back(c2.v[34]*hh_1[68]);
/* NN[21] */ NN.push_back(c2.v[35]*hh_1[70]);
/* NN[22] */ NN.push_back(c2.v[36]*hh_1[72]);
/* NN[23] */ NN.push_back(c2.v[38]*hh_1[76]);
/* NN[24] */ NN.push_back(c2.v[40]*hh_1[80]);
/* NN[25] */ NN.push_back(c2.v[42]*hh_1[84]);
/* NN[26] */ NN.push_back(c2.v[44]*hh_1[88]);
/* NN[27] */ NN.push_back(c2.v[45]*hh_1[90]);
/* NN[28] */ NN.push_back(c2.v[46]*hh_1[92]);
/* NN[29] */ NN.push_back(c2.v[48]*hh_1[96]);
/* NN[30] */ NN.push_back(c2.v[50]*hh_1[100]);
/* NN[31] */ NN.push_back(c2.v[52]*hh_1[104]);
/* NN[32] */ NN.push_back(c2.v[54]*hh_1[108]);
/* NN[33] */ NN.push_back(c2.v[55]*hh_1[110]);
/* NN[34] */ NN.push_back(c2.v[56]*hh_1[112]);
/* NN[35] */ NN.push_back(c2.v[58]*hh_1[116]);
/* NN[36] */ NN.push_back(c2.v[60]*hh_1[120]);
/* NN[37] */ NN.push_back(c2.v[62]*hh_1[124]);
/* NN[38] */ NN.push_back(c2.v[64]*hh_1[128]);
/* NN[39] */ NN.push_back(c2.v[65]*hh_1[130]);
/* NN[40] */ NN.push_back(c2.v[66]*hh_1[132]);
/* NN[41] */ NN.push_back(c2.v[68]*hh_1[136]);
/* NN[42] */ NN.push_back(c2.v[70]*hh_1[140]);
/* NN[43] */ NN.push_back(c2.v[72]*hh_1[144]);
/* NN[44] */ NN.push_back(c2.v[74]*hh_1[148]);
/* NN[45] */ NN.push_back(c2.v[75]*hh_1[150]);
/* NN[46] */ NN.push_back(c2.v[76]*hh_1[152]);
/* NN[47] */ NN.push_back(c2.v[78]*hh_1[156]);
/* NN[48] */ NN.push_back(CC[0]*hh_1[0]);
/* NN[49] */ NN.push_back(CC[2]*hh_1[8]);
/* NN[50] */ NN.push_back(CC[4]*hh_1[16]);
/* NN[51] */ NN.push_back(CC[5]*hh_1[20]);
/* NN[52] */ NN.push_back(CC[6]*hh_1[24]);
/* NN[53] */ NN.push_back(CC[8]*hh_1[32]);
/* NN[54] */ NN.push_back(CC[10]*hh_1[40]);
/* NN[55] */ NN.push_back(CC[12]*hh_1[48]);
/* NN[56] */ NN.push_back(CC[14]*hh_1[56]);
/* NN[57] */ NN.push_back(CC[15]*hh_1[60]);
/* NN[58] */ NN.push_back(CC[16]*hh_1[64]);
/* NN[59] */ NN.push_back(CC[18]*hh_1[72]);
/* NN[60] */ NN.push_back(CC[20]*hh_1[80]);
/* NN[61] */ NN.push_back(CC[22]*hh_1[88]);
/* NN[62] */ NN.push_back(CC[24]*hh_1[96]);
/* NN[63] */ NN.push_back(CC[25]*hh_1[100]);
/* NN[64] */ NN.push_back(CC[26]*hh_1[104]);
/* NN[65] */ NN.push_back(CC[28]*hh_1[112]);
/* NN[66] */ NN.push_back(CC[30]*hh_1[120]);
/* NN[67] */ NN.push_back(CC[32]*hh_1[128]);
/* NN[68] */ NN.push_back(CC[34]*hh_1[136]);
/* NN[69] */ NN.push_back(CC[35]*hh_1[140]);
/* NN[70] */ NN.push_back(CC[36]*hh_1[144]);
/* NN[71] */ NN.push_back(CC[38]*hh_1[152]);
/* NN[72] */ NN.push_back(c2.v[2]*hh_1[12]);
/* NN[73] */ NN.push_back(c2.v[4]*hh_1[24]);
/* NN[74] */ NN.push_back(c2.v[5]*hh_1[30]);
/* NN[75] */ NN.push_back(c2.v[6]*hh_1[36]);
/* NN[76] */ NN.push_back(c2.v[8]*hh_1[48]);
/* NN[77] */ NN.push_back(c2.v[10]*hh_1[60]);
/* NN[78] */ NN.push_back(c2.v[12]*hh_1[72]);
/* NN[79] */ NN.push_back(c2.v[14]*hh_1[84]);
/* NN[80] */ NN.push_back(c2.v[15]*hh_1[90]);
/* NN[81] */ NN.push_back(c2.v[16]*hh_1[96]);
/* NN[82] */ NN.push_back(c2.v[18]*hh_1[108]);
/* NN[83] */ NN.push_back(c2.v[20]*hh_1[120]);
/* NN[84] */ NN.push_back(c2.v[22]*hh_1[132]);
/* NN[85] */ NN.push_back(c2.v[24]*hh_1[144]);
/* NN[86] */ NN.push_back(c2.v[25]*hh_1[150]);
/* NN[87] */ NN.push_back(c2.v[26]*hh_1[156]);
/* NN[88] */ NN.push_back(c2.v[28]*hh_1[8]);
/* NN[89] */ NN.push_back(c2.v[30]*hh_1[20]);
/* NN[90] */ NN.push_back(c2.v[32]*hh_1[32]);
/* NN[91] */ NN.push_back(c2.v[34]*hh_1[44]);
/* NN[92] */ NN.push_back(c2.v[35]*hh_1[50]);
/* NN[93] */ NN.push_back(c2.v[36]*hh_1[56]);
/* NN[94] */ NN.push_back(c2.v[38]*hh_1[68]);
/* NN[95] */ NN.push_back(c2.v[42]*hh_1[92]);
/* NN[96] */ NN.push_back(c2.v[44]*hh_1[104]);
/* NN[97] */ NN.push_back(c2.v[45]*hh_1[110]);
/* NN[98] */ NN.push_back(c2.v[46]*hh_1[116]);
/* NN[99] */ NN.push_back(c2.v[48]*hh_1[128]);
/* NN[100] */ NN.push_back(c2.v[50]*hh_1[140]);
/* NN[101] */ NN.push_back(c2.v[52]*hh_1[152]);
/* NN[102] */ NN.push_back(c2.v[54]*hh_1[4]);
/* NN[103] */ NN.push_back(c2.v[55]*hh_1[10]);
/* NN[104] */ NN.push_back(c2.v[56]*hh_1[16]);
/* NN[105] */ NN.push_back(c2.v[58]*hh_1[28]);
/* NN[106] */ NN.push_back(c2.v[60]*hh_1[40]);
/* NN[107] */ NN.push_back(c2.v[62]*hh_1[52]);
/* NN[108] */ NN.push_back(c2.v[64]*hh_1[64]);
/* NN[109] */ NN.push_back(c2.v[65]*hh_1[70]);
/* NN[110] */ NN.push_back(c2.v[66]*hh_1[76]);
/* NN[111] */ NN.push_back(c2.v[68]*hh_1[88]);
/* NN[112] */ NN.push_back(c2.v[70]*hh_1[100]);
/* NN[113] */ NN.push_back(c2.v[72]*hh_1[112]);
/* NN[114] */ NN.push_back(c2.v[74]*hh_1[124]);
/* NN[115] */ NN.push_back(c2.v[75]*hh_1[130]);
/* NN[116] */ NN.push_back(c2.v[76]*hh_1[136]);
/* NN[117] */ NN.push_back(c2.v[78]*hh_1[148]);
/* NN[118] */ NN.push_back(CC[40]*hh_1[0]);
/* NN[119] */ NN.push_back(CC[42]*hh_1[16]);
/* NN[120] */ NN.push_back(CC[44]*hh_1[32]);
/* NN[121] */ NN.push_back(CC[45]*hh_1[40]);
/* NN[122] */ NN.push_back(CC[46]*hh_1[48]);
/* NN[123] */ NN.push_back(CC[48]*hh_1[64]);
/* NN[124] */ NN.push_back(CC[50]*hh_1[80]);
/* NN[125] */ NN.push_back(CC[52]*hh_1[96]);
/* NN[126] */ NN.push_back(CC[54]*hh_1[112]);
/* NN[127] */ NN.push_back(CC[55]*hh_1[120]);
/* NN[128] */ NN.push_back(CC[56]*hh_1[128]);
/* NN[129] */ NN.push_back(CC[58]*hh_1[144]);
/* NN[130] */ NN.push_back(CC[60]*hh_1[0]);
/* NN[131] */ NN.push_back(CC[62]*hh_1[20]);
/* NN[132] */ NN.push_back(CC[64]*hh_1[40]);
/* NN[133] */ NN.push_back(CC[66]*hh_1[60]);
/* NN[134] */ NN.push_back(CC[68]*hh_1[80]);
/* NN[135] */ NN.push_back(CC[70]*hh_1[100]);
/* NN[136] */ NN.push_back(CC[72]*hh_1[120]);
/* NN[137] */ NN.push_back(CC[74]*hh_1[140]);
/* NN[138] */ NN.push_back(CC[2]*hh_1[24]);
/* NN[139] */ NN.push_back(CC[4]*hh_1[48]);
/* NN[140] */ NN.push_back(CC[5]*hh_1[60]);
/* NN[141] */ NN.push_back(CC[6]*hh_1[72]);
/* NN[142] */ NN.push_back(CC[8]*hh_1[96]);
/* NN[143] */ NN.push_back(CC[10]*hh_1[120]);
/* NN[144] */ NN.push_back(CC[12]*hh_1[144]);
/* NN[145] */ NN.push_back(CC[14]*hh_1[8]);
/* NN[146] */ NN.push_back(CC[15]*hh_1[20]);
/* NN[147] */ NN.push_back(CC[16]*hh_1[32]);
/* NN[148] */ NN.push_back(CC[18]*hh_1[56]);
/* NN[149] */ NN.push_back(CC[22]*hh_1[104]);
/* NN[150] */ NN.push_back(CC[24]*hh_1[128]);
/* NN[151] */ NN.push_back(CC[25]*hh_1[140]);
/* NN[152] */ NN.push_back(CC[26]*hh_1[152]);
/* NN[153] */ NN.push_back(CC[28]*hh_1[16]);
/* NN[154] */ NN.push_back(CC[30]*hh_1[40]);
/* NN[155] */ NN.push_back(CC[32]*hh_1[64]);
/* NN[156] */ NN.push_back(CC[34]*hh_1[88]);
/* NN[157] */ NN.push_back(CC[35]*hh_1[100]);
/* NN[158] */ NN.push_back(CC[36]*hh_1[112]);
/* NN[159] */ NN.push_back(CC[38]*hh_1[136]);
/* NN[160] */ NN.push_back(c2.v[2]*hh_1[28]);
/* NN[161] */ NN.push_back(c2.v[4]*hh_1[56]);
/* NN[162] */ NN.push_back(c2.v[5]*hh_1[70]);
/* NN[163] */ NN.push_back(c2.v[6]*hh_1[84]);
/* NN[164] */ NN.push_back(c2.v[8]*hh_1[112]);
/* NN[165] */ NN.push_back(c2.v[10]*hh_1[140]);
/* NN[166] */ NN.push_back(c2.v[12]*hh_1[8]);
/* NN[167] */ NN.push_back(c2.v[14]*hh_1[36]);
/* NN[168] */ NN.push_back(c2.v[15]*hh_1[50]);
/* NN[169] */ NN.push_back(c2.v[16]*hh_1[64]);
/* NN[170] */ NN.push_back(c2.v[18]*hh_1[92]);
/* NN[171] */ NN.push_back(c2.v[22]*hh_1[148]);
/* NN[172] */ NN.push_back(c2.v[24]*hh_1[16]);
/* NN[173] */ NN.push_back(c2.v[25]*hh_1[30]);
/* NN[174] */ NN.push_back(c2.v[26]*hh_1[44]);
/* NN[175] */ NN.push_back(c2.v[28]*hh_1[72]);
/* NN[176] */ NN.push_back(c2.v[30]*hh_1[100]);
/* NN[177] */ NN.push_back(c2.v[32]*hh_1[128]);
/* NN[178] */ NN.push_back(c2.v[34]*hh_1[156]);
/* NN[179] */ NN.push_back(c2.v[35]*hh_1[10]);
/* NN[180] */ NN.push_back(c2.v[36]*hh_1[24]);
/* NN[181] */ NN.push_back(c2.v[38]*hh_1[52]);
/* NN[182] */ NN.push_back(c2.v[42]*hh_1[108]);
/* NN[183] */ NN.push_back(c2.v[44]*hh_1[136]);
/* NN[184] */ NN.push_back(c2.v[45]*hh_1[150]);
/* NN[185] */ NN.push_back(c2.v[46]*hh_1[4]);
/* NN[186] */ NN.push_back(c2.v[48]*hh_1[32]);
/* NN[187] */ NN.push_back(c2.v[50]*hh_1[60]);
/* NN[188] */ NN.push_back(c2.v[52]*hh_1[88]);
/* NN[189] */ NN.push_back(c2.v[54]*hh_1[116]);
/* NN[190] */ NN.push_back(c2.v[55]*hh_1[130]);
/* NN[191] */ NN.push_back(c2.v[56]*hh_1[144]);
/* NN[192] */ NN.push_back(c2.v[58]*hh_1[12]);
/* NN[193] */ NN.push_back(c2.v[62]*hh_1[68]);
/* NN[194] */ NN.push_back(c2.v[64]*hh_1[96]);
/* NN[195] */ NN.push_back(c2.v[65]*hh_1[110]);
/* NN[196] */ NN.push_back(c2.v[66]*hh_1[124]);
/* NN[197] */ NN.push_back(c2.v[68]*hh_1[152]);
/* NN[198] */ NN.push_back(c2.v[70]*hh_1[20]);
/* NN[199] */ NN.push_back(c2.v[72]*hh_1[48]);
/* NN[200] */ NN.push_back(c2.v[74]*hh_1[76]);
/* NN[201] */ NN.push_back(c2.v[75]*hh_1[90]);
/* NN[202] */ NN.push_back(c2.v[76]*hh_1[104]);
/* NN[203] */ NN.push_back(c2.v[78]*hh_1[132]);
/* NN[204] */ NN.push_back(CC[76]*hh_1[0]);
/* NN[205] */ NN.push_back(CC[81]*hh_1[80]);
/* NN[206] */ NN.push_back(c2.v[2]*hh_1[36]);
/* NN[207] */ NN.push_back(c2.v[4]*hh_1[72]);
/* NN[208] */ NN.push_back(c2.v[5]*hh_1[90]);
/* NN[209] */ NN.push_back(c2.v[6]*hh_1[108]);
/* NN[210] */ NN.push_back(c2.v[8]*hh_1[144]);
/* NN[211] */ NN.push_back(c2.v[12]*hh_1[56]);
/* NN[212] */ NN.push_back(c2.v[14]*hh_1[92]);
/* NN[213] */ NN.push_back(c2.v[15]*hh_1[110]);
/* NN[214] */ NN.push_back(c2.v[16]*hh_1[128]);
/* NN[215] */ NN.push_back(c2.v[18]*hh_1[4]);
/* NN[216] */ NN.push_back(c2.v[22]*hh_1[76]);
/* NN[217] */ NN.push_back(c2.v[24]*hh_1[112]);
/* NN[218] */ NN.push_back(c2.v[25]*hh_1[130]);
/* NN[219] */ NN.push_back(c2.v[26]*hh_1[148]);
/* NN[220] */ NN.push_back(c2.v[28]*hh_1[24]);
/* NN[221] */ NN.push_back(c2.v[32]*hh_1[96]);
/* NN[222] */ NN.push_back(c2.v[34]*hh_1[132]);
/* NN[223] */ NN.push_back(c2.v[35]*hh_1[150]);
/* NN[224] */ NN.push_back(c2.v[36]*hh_1[8]);
/* NN[225] */ NN.push_back(c2.v[38]*hh_1[44]);
/* NN[226] */ NN.push_back(c2.v[42]*hh_1[116]);
/* NN[227] */ NN.push_back(c2.v[44]*hh_1[152]);
/* NN[228] */ NN.push_back(c2.v[45]*hh_1[10]);
/* NN[229] */ NN.push_back(c2.v[46]*hh_1[28]);
/* NN[230] */ NN.push_back(c2.v[48]*hh_1[64]);
/* NN[231] */ NN.push_back(c2.v[52]*hh_1[136]);
/* NN[232] */ NN.push_back(c2.v[54]*hh_1[12]);
/* NN[233] */ NN.push_back(c2.v[55]*hh_1[30]);
/* NN[234] */ NN.push_back(c2.v[56]*hh_1[48]);
/* NN[235] */ NN.push_back(c2.v[58]*hh_1[84]);
/* NN[236] */ NN.push_back(c2.v[62]*hh_1[156]);
/* NN[237] */ NN.push_back(c2.v[64]*hh_1[32]);
/* NN[238] */ NN.push_back(c2.v[65]*hh_1[50]);
/* NN[239] */ NN.push_back(c2.v[66]*hh_1[68]);
/* NN[240] */ NN.push_back(c2.v[68]*hh_1[104]);
/* NN[241] */ NN.push_back(c2.v[72]*hh_1[16]);
/* NN[242] */ NN.push_back(c2.v[74]*hh_1[52]);
/* NN[243] */ NN.push_back(c2.v[75]*hh_1[70]);
/* NN[244] */ NN.push_back(c2.v[76]*hh_1[88]);
/* NN[245] */ NN.push_back(c2.v[78]*hh_1[124]);
/* NN[246] */ NN.push_back(CC[86]*hh_1[0]);
/* NN[247] */ NN.push_back(CC[88]*hh_1[40]);
/* NN[248] */ NN.push_back(CC[90]*hh_1[80]);
/* NN[249] */ NN.push_back(CC[92]*hh_1[120]);
/* NN[250] */ NN.push_back(c2.v[2]*hh_1[44]);
/* NN[251] */ NN.push_back(c2.v[4]*hh_1[88]);
/* NN[252] */ NN.push_back(c2.v[5]*hh_1[110]);
/* NN[253] */ NN.push_back(c2.v[6]*hh_1[132]);
/* NN[254] */ NN.push_back(c2.v[12]*hh_1[104]);
/* NN[255] */ NN.push_back(c2.v[14]*hh_1[148]);
/* NN[256] */ NN.push_back(c2.v[15]*hh_1[10]);
/* NN[257] */ NN.push_back(c2.v[18]*hh_1[76]);
/* NN[258] */ NN.push_back(c2.v[22]*hh_1[4]);
/* NN[259] */ NN.push_back(c2.v[25]*hh_1[70]);
/* NN[260] */ NN.push_back(c2.v[26]*hh_1[92]);
/* NN[261] */ NN.push_back(c2.v[28]*hh_1[136]);
/* NN[262] */ NN.push_back(c2.v[34]*hh_1[108]);
/* NN[263] */ NN.push_back(c2.v[35]*hh_1[130]);
/* NN[264] */ NN.push_back(c2.v[36]*hh_1[152]);
/* NN[265] */ NN.push_back(c2.v[38]*hh_1[36]);
/* NN[266] */ NN.push_back(c2.v[42]*hh_1[124]);
/* NN[267] */ NN.push_back(c2.v[44]*hh_1[8]);
/* NN[268] */ NN.push_back(c2.v[45]*hh_1[30]);
/* NN[269] */ NN.push_back(c2.v[46]*hh_1[52]);
/* NN[270] */ NN.push_back(c2.v[52]*hh_1[24]);
/* NN[271] */ NN.push_back(c2.v[54]*hh_1[68]);
/* NN[272] */ NN.push_back(c2.v[55]*hh_1[90]);
/* NN[273] */ NN.push_back(c2.v[58]*hh_1[156]);
/* NN[274] */ NN.push_back(c2.v[62]*hh_1[84]);
/* NN[275] */ NN.push_back(c2.v[65]*hh_1[150]);
/* NN[276] */ NN.push_back(c2.v[66]*hh_1[12]);
/* NN[277] */ NN.push_back(c2.v[68]*hh_1[56]);
/* NN[278] */ NN.push_back(c2.v[74]*hh_1[28]);
/* NN[279] */ NN.push_back(c2.v[75]*hh_1[50]);
/* NN[280] */ NN.push_back(c2.v[76]*hh_1[72]);
/* NN[281] */ NN.push_back(c2.v[78]*hh_1[116]);
/* NN[282] */ NN.push_back(CC[42]*hh_1[48]);
/* NN[283] */ NN.push_back(CC[44]*hh_1[96]);
/* NN[284] */ NN.push_back(CC[45]*hh_1[120]);
/* NN[285] */ NN.push_back(CC[46]*hh_1[144]);
/* NN[286] */ NN.push_back(CC[48]*hh_1[32]);
/* NN[287] */ NN.push_back(CC[52]*hh_1[128]);
/* NN[288] */ NN.push_back(CC[54]*hh_1[16]);
/* NN[289] */ NN.push_back(CC[55]*hh_1[40]);
/* NN[290] */ NN.push_back(CC[56]*hh_1[64]);
/* NN[291] */ NN.push_back(CC[58]*hh_1[112]);
/* NN[292] */ NN.push_back(c2.v[2]*hh_1[52]);
/* NN[293] */ NN.push_back(c2.v[4]*hh_1[104]);
/* NN[294] */ NN.push_back(c2.v[5]*hh_1[130]);
/* NN[295] */ NN.push_back(c2.v[6]*hh_1[156]);
/* NN[296] */ NN.push_back(c2.v[10]*hh_1[100]);
/* NN[297] */ NN.push_back(c2.v[12]*hh_1[152]);
/* NN[298] */ NN.push_back(c2.v[14]*hh_1[44]);
/* NN[299] */ NN.push_back(c2.v[15]*hh_1[70]);
/* NN[300] */ NN.push_back(c2.v[18]*hh_1[148]);
/* NN[301] */ NN.push_back(c2.v[22]*hh_1[92]);
/* NN[302] */ NN.push_back(c2.v[25]*hh_1[10]);
/* NN[303] */ NN.push_back(c2.v[26]*hh_1[36]);
/* NN[304] */ NN.push_back(c2.v[28]*hh_1[88]);
/* NN[305] */ NN.push_back(c2.v[30]*hh_1[140]);
/* NN[306] */ NN.push_back(c2.v[34]*hh_1[84]);
/* NN[307] */ NN.push_back(c2.v[35]*hh_1[110]);
/* NN[308] */ NN.push_back(c2.v[36]*hh_1[136]);
/* NN[309] */ NN.push_back(c2.v[38]*hh_1[28]);
/* NN[310] */ NN.push_back(c2.v[42]*hh_1[132]);
/* NN[311] */ NN.push_back(c2.v[44]*hh_1[24]);
/* NN[312] */ NN.push_back(c2.v[45]*hh_1[50]);
/* NN[313] */ NN.push_back(c2.v[46]*hh_1[76]);
/* NN[314] */ NN.push_back(c2.v[50]*hh_1[20]);
/* NN[315] */ NN.push_back(c2.v[52]*hh_1[72]);
/* NN[316] */ NN.push_back(c2.v[54]*hh_1[124]);
/* NN[317] */ NN.push_back(c2.v[55]*hh_1[150]);
/* NN[318] */ NN.push_back(c2.v[58]*hh_1[68]);
/* NN[319] */ NN.push_back(c2.v[62]*hh_1[12]);
/* NN[320] */ NN.push_back(c2.v[65]*hh_1[90]);
/* NN[321] */ NN.push_back(c2.v[66]*hh_1[116]);
/* NN[322] */ NN.push_back(c2.v[68]*hh_1[8]);
/* NN[323] */ NN.push_back(c2.v[70]*hh_1[60]);
/* NN[324] */ NN.push_back(c2.v[74]*hh_1[4]);
/* NN[325] */ NN.push_back(c2.v[75]*hh_1[30]);
/* NN[326] */ NN.push_back(c2.v[76]*hh_1[56]);
/* NN[327] */ NN.push_back(c2.v[78]*hh_1[108]);
/* NN[328] */ NN.push_back(CC[2]*hh_1[56]);
/* NN[329] */ NN.push_back(CC[4]*hh_1[112]);
/* NN[330] */ NN.push_back(CC[5]*hh_1[140]);
/* NN[331] */ NN.push_back(CC[6]*hh_1[8]);
/* NN[332] */ NN.push_back(CC[8]*hh_1[64]);
/* NN[333] */ NN.push_back(CC[12]*hh_1[16]);
/* NN[334] */ NN.push_back(CC[14]*hh_1[72]);
/* NN[335] */ NN.push_back(CC[15]*hh_1[100]);
/* NN[336] */ NN.push_back(CC[16]*hh_1[128]);
/* NN[337] */ NN.push_back(CC[18]*hh_1[24]);
/* NN[338] */ NN.push_back(CC[22]*hh_1[136]);
/* NN[339] */ NN.push_back(CC[24]*hh_1[32]);
/* NN[340] */ NN.push_back(CC[25]*hh_1[60]);
/* NN[341] */ NN.push_back(CC[26]*hh_1[88]);
/* NN[342] */ NN.push_back(CC[28]*hh_1[144]);
/* NN[343] */ NN.push_back(CC[32]*hh_1[96]);
/* NN[344] */ NN.push_back(CC[34]*hh_1[152]);
/* NN[345] */ NN.push_back(CC[35]*hh_1[20]);
/* NN[346] */ NN.push_back(CC[36]*hh_1[48]);
/* NN[347] */ NN.push_back(CC[38]*hh_1[104]);
/* NN[348] */ NN.push_back(CC[62]*hh_1[60]);
/* NN[349] */ NN.push_back(CC[64]*hh_1[120]);
/* NN[350] */ NN.push_back(CC[66]*hh_1[20]);
/* NN[351] */ NN.push_back(CC[70]*hh_1[140]);
/* NN[352] */ NN.push_back(CC[72]*hh_1[40]);
/* NN[353] */ NN.push_back(CC[74]*hh_1[100]);
/* NN[354] */ NN.push_back(CC[94]*hh_1[0]);
/* NN[355] */ NN.push_back(c2.v[2]*hh_1[68]);
/* NN[356] */ NN.push_back(c2.v[4]*hh_1[136]);
/* NN[357] */ NN.push_back(c2.v[6]*hh_1[44]);
/* NN[358] */ NN.push_back(c2.v[12]*hh_1[88]);
/* NN[359] */ NN.push_back(c2.v[14]*hh_1[156]);
/* NN[360] */ NN.push_back(c2.v[18]*hh_1[132]);
/* NN[361] */ NN.push_back(c2.v[22]*hh_1[108]);
/* NN[362] */ NN.push_back(c2.v[26]*hh_1[84]);
/* NN[363] */ NN.push_back(c2.v[28]*hh_1[152]);
/* NN[364] */ NN.push_back(c2.v[34]*hh_1[36]);
/* NN[365] */ NN.push_back(c2.v[36]*hh_1[104]);
/* NN[366] */ NN.push_back(c2.v[38]*hh_1[12]);
/* NN[367] */ NN.push_back(c2.v[42]*hh_1[148]);
/* NN[368] */ NN.push_back(c2.v[44]*hh_1[56]);
/* NN[369] */ NN.push_back(c2.v[46]*hh_1[124]);
/* NN[370] */ NN.push_back(c2.v[52]*hh_1[8]);
/* NN[371] */ NN.push_back(c2.v[54]*hh_1[76]);
/* NN[372] */ NN.push_back(c2.v[58]*hh_1[52]);
/* NN[373] */ NN.push_back(c2.v[62]*hh_1[28]);
/* NN[374] */ NN.push_back(c2.v[66]*hh_1[4]);
/* NN[375] */ NN.push_back(c2.v[68]*hh_1[72]);
/* NN[376] */ NN.push_back(c2.v[74]*hh_1[116]);
/* NN[377] */ NN.push_back(c2.v[76]*hh_1[24]);
/* NN[378] */ NN.push_back(c2.v[78]*hh_1[92]);
/* NN[379] */ NN.push_back(CC[2]*hh_1[72]);
/* NN[380] */ NN.push_back(CC[4]*hh_1[144]);
/* NN[381] */ NN.push_back(CC[6]*hh_1[56]);
/* NN[382] */ NN.push_back(CC[8]*hh_1[128]);
/* NN[383] */ NN.push_back(CC[12]*hh_1[112]);
/* NN[384] */ NN.push_back(CC[14]*hh_1[24]);
/* NN[385] */ NN.push_back(CC[16]*hh_1[96]);
/* NN[386] */ NN.push_back(CC[18]*hh_1[8]);
/* NN[387] */ NN.push_back(CC[22]*hh_1[152]);
/* NN[388] */ NN.push_back(CC[24]*hh_1[64]);
/* NN[389] */ NN.push_back(CC[26]*hh_1[136]);
/* NN[390] */ NN.push_back(CC[28]*hh_1[48]);
/* NN[391] */ NN.push_back(CC[32]*hh_1[32]);
/* NN[392] */ NN.push_back(CC[34]*hh_1[104]);
/* NN[393] */ NN.push_back(CC[36]*hh_1[16]);
/* NN[394] */ NN.push_back(CC[38]*hh_1[88]);
/* NN[395] */ NN.push_back(c2.v[2]*hh_1[76]);
/* NN[396] */ NN.push_back(c2.v[4]*hh_1[152]);
/* NN[397] */ NN.push_back(c2.v[6]*hh_1[68]);
/* NN[398] */ NN.push_back(c2.v[12]*hh_1[136]);
/* NN[399] */ NN.push_back(c2.v[14]*hh_1[52]);
/* NN[400] */ NN.push_back(c2.v[18]*hh_1[44]);
/* NN[401] */ NN.push_back(c2.v[22]*hh_1[36]);
/* NN[402] */ NN.push_back(c2.v[26]*hh_1[28]);
/* NN[403] */ NN.push_back(c2.v[28]*hh_1[104]);
/* NN[404] */ NN.push_back(c2.v[34]*hh_1[12]);
/* NN[405] */ NN.push_back(c2.v[36]*hh_1[88]);
/* NN[406] */ NN.push_back(c2.v[38]*hh_1[4]);
/* NN[407] */ NN.push_back(c2.v[42]*hh_1[156]);
/* NN[408] */ NN.push_back(c2.v[44]*hh_1[72]);
/* NN[409] */ NN.push_back(c2.v[46]*hh_1[148]);
/* NN[410] */ NN.push_back(c2.v[52]*hh_1[56]);
/* NN[411] */ NN.push_back(c2.v[54]*hh_1[132]);
/* NN[412] */ NN.push_back(c2.v[58]*hh_1[124]);
/* NN[413] */ NN.push_back(c2.v[62]*hh_1[116]);
/* NN[414] */ NN.push_back(c2.v[66]*hh_1[108]);
/* NN[415] */ NN.push_back(c2.v[68]*hh_1[24]);
/* NN[416] */ NN.push_back(c2.v[74]*hh_1[92]);
/* NN[417] */ NN.push_back(c2.v[76]*hh_1[8]);
/* NN[418] */ NN.push_back(c2.v[78]*hh_1[84]);
/* NN[419] */ NN.push_back(CC[99]*hh_1[0]);
/* NN[420] */ NN.push_back(CC[101]*hh_1[80]);
/* NN[421] */ NN.push_back(c2.v[2]*hh_1[84]);
/* NN[422] */ NN.push_back(c2.v[5]*hh_1[50]);
/* NN[423] */ NN.push_back(c2.v[6]*hh_1[92]);
/* NN[424] */ NN.push_back(c2.v[14]*hh_1[108]);
/* NN[425] */ NN.push_back(c2.v[15]*hh_1[150]);
/* NN[426] */ NN.push_back(c2.v[18]*hh_1[116]);
/* NN[427] */ NN.push_back(c2.v[22]*hh_1[124]);
/* NN[428] */ NN.push_back(c2.v[25]*hh_1[90]);
/* NN[429] */ NN.push_back(c2.v[26]*hh_1[132]);
/* NN[430] */ NN.push_back(c2.v[34]*hh_1[148]);
/* NN[431] */ NN.push_back(c2.v[35]*hh_1[30]);
/* NN[432] */ NN.push_back(c2.v[38]*hh_1[156]);
/* NN[433] */ NN.push_back(c2.v[42]*hh_1[4]);
/* NN[434] */ NN.push_back(c2.v[45]*hh_1[130]);
/* NN[435] */ NN.push_back(c2.v[46]*hh_1[12]);
/* NN[436] */ NN.push_back(c2.v[54]*hh_1[28]);
/* NN[437] */ NN.push_back(c2.v[55]*hh_1[70]);
/* NN[438] */ NN.push_back(c2.v[58]*hh_1[36]);
/* NN[439] */ NN.push_back(c2.v[62]*hh_1[44]);
/* NN[440] */ NN.push_back(c2.v[65]*hh_1[10]);
/* NN[441] */ NN.push_back(c2.v[66]*hh_1[52]);
/* NN[442] */ NN.push_back(c2.v[74]*hh_1[68]);
/* NN[443] */ NN.push_back(c2.v[75]*hh_1[110]);
/* NN[444] */ NN.push_back(c2.v[78]*hh_1[76]);
/* NN[445] */ NN.push_back(CC[2]*hh_1[88]);
/* NN[446] */ NN.push_back(CC[6]*hh_1[104]);
/* NN[447] */ NN.push_back(CC[14]*hh_1[136]);
/* NN[448] */ NN.push_back(CC[18]*hh_1[152]);
/* NN[449] */ NN.push_back(CC[22]*hh_1[8]);
/* NN[450] */ NN.push_back(CC[26]*hh_1[24]);
/* NN[451] */ NN.push_back(CC[34]*hh_1[56]);
/* NN[452] */ NN.push_back(CC[38]*hh_1[72]);
/* NN[453] */ NN.push_back(c2.v[2]*hh_1[92]);
/* NN[454] */ NN.push_back(c2.v[6]*hh_1[116]);
/* NN[455] */ NN.push_back(c2.v[14]*hh_1[4]);
/* NN[456] */ NN.push_back(c2.v[18]*hh_1[28]);
/* NN[457] */ NN.push_back(c2.v[22]*hh_1[52]);
/* NN[458] */ NN.push_back(c2.v[26]*hh_1[76]);
/* NN[459] */ NN.push_back(c2.v[34]*hh_1[124]);
/* NN[460] */ NN.push_back(c2.v[38]*hh_1[148]);
/* NN[461] */ NN.push_back(c2.v[42]*hh_1[12]);
/* NN[462] */ NN.push_back(c2.v[46]*hh_1[36]);
/* NN[463] */ NN.push_back(c2.v[54]*hh_1[84]);
/* NN[464] */ NN.push_back(c2.v[58]*hh_1[108]);
/* NN[465] */ NN.push_back(c2.v[62]*hh_1[132]);
/* NN[466] */ NN.push_back(c2.v[66]*hh_1[156]);
/* NN[467] */ NN.push_back(c2.v[74]*hh_1[44]);
/* NN[468] */ NN.push_back(c2.v[78]*hh_1[68]);
/* NN[469] */ NN.push_back(CC[62]*hh_1[100]);
/* NN[470] */ NN.push_back(CC[66]*hh_1[140]);
/* NN[471] */ NN.push_back(CC[70]*hh_1[20]);
/* NN[472] */ NN.push_back(CC[74]*hh_1[60]);
/* NN[473] */ NN.push_back(CC[2]*hh_1[104]);
/* NN[474] */ NN.push_back(CC[5]*hh_1[100]);
/* NN[475] */ NN.push_back(CC[6]*hh_1[152]);
/* NN[476] */ NN.push_back(CC[14]*hh_1[88]);
/* NN[477] */ NN.push_back(CC[15]*hh_1[140]);
/* NN[478] */ NN.push_back(CC[18]*hh_1[136]);
/* NN[479] */ NN.push_back(CC[22]*hh_1[24]);
/* NN[480] */ NN.push_back(CC[25]*hh_1[20]);
/* NN[481] */ NN.push_back(CC[26]*hh_1[72]);
/* NN[482] */ NN.push_back(CC[34]*hh_1[8]);
/* NN[483] */ NN.push_back(CC[35]*hh_1[60]);
/* NN[484] */ NN.push_back(CC[38]*hh_1[56]);
/* NN[485] */ NN.push_back(c2.v[2]*hh_1[108]);
/* NN[486] */ NN.push_back(c2.v[6]*hh_1[4]);
/* NN[487] */ NN.push_back(c2.v[14]*hh_1[116]);
/* NN[488] */ NN.push_back(c2.v[18]*hh_1[12]);
/* NN[489] */ NN.push_back(c2.v[22]*hh_1[68]);
/* NN[490] */ NN.push_back(c2.v[26]*hh_1[124]);
/* NN[491] */ NN.push_back(c2.v[34]*hh_1[76]);
/* NN[492] */ NN.push_back(c2.v[38]*hh_1[132]);
/* NN[493] */ NN.push_back(c2.v[42]*hh_1[28]);
/* NN[494] */ NN.push_back(c2.v[46]*hh_1[84]);
/* NN[495] */ NN.push_back(c2.v[54]*hh_1[36]);
/* NN[496] */ NN.push_back(c2.v[58]*hh_1[92]);
/* NN[497] */ NN.push_back(c2.v[62]*hh_1[148]);
/* NN[498] */ NN.push_back(c2.v[66]*hh_1[44]);
/* NN[499] */ NN.push_back(c2.v[74]*hh_1[156]);
/* NN[500] */ NN.push_back(c2.v[78]*hh_1[52]);
/* NN[501] */ NN.push_back(CC[42]*hh_1[112]);
/* NN[502] */ NN.push_back(CC[44]*hh_1[64]);
/* NN[503] */ NN.push_back(CC[46]*hh_1[16]);
/* NN[504] */ NN.push_back(CC[48]*hh_1[128]);
/* NN[505] */ NN.push_back(CC[52]*hh_1[32]);
/* NN[506] */ NN.push_back(CC[54]*hh_1[144]);
/* NN[507] */ NN.push_back(CC[56]*hh_1[96]);
/* NN[508] */ NN.push_back(CC[58]*hh_1[48]);
/* NN[509] */ NN.push_back(c2.v[2]*hh_1[116]);
/* NN[510] */ NN.push_back(c2.v[6]*hh_1[28]);
/* NN[511] */ NN.push_back(c2.v[14]*hh_1[12]);
/* NN[512] */ NN.push_back(c2.v[18]*hh_1[84]);
/* NN[513] */ NN.push_back(c2.v[22]*hh_1[156]);
/* NN[514] */ NN.push_back(c2.v[26]*hh_1[68]);
/* NN[515] */ NN.push_back(c2.v[34]*hh_1[52]);
/* NN[516] */ NN.push_back(c2.v[38]*hh_1[124]);
/* NN[517] */ NN.push_back(c2.v[42]*hh_1[36]);
/* NN[518] */ NN.push_back(c2.v[46]*hh_1[108]);
/* NN[519] */ NN.push_back(c2.v[54]*hh_1[92]);
/* NN[520] */ NN.push_back(c2.v[58]*hh_1[4]);
/* NN[521] */ NN.push_back(c2.v[62]*hh_1[76]);
/* NN[522] */ NN.push_back(c2.v[66]*hh_1[148]);
/* NN[523] */ NN.push_back(c2.v[74]*hh_1[132]);
/* NN[524] */ NN.push_back(c2.v[78]*hh_1[44]);
/* NN[525] */ NN.push_back(CC[88]*hh_1[120]);
/* NN[526] */ NN.push_back(CC[92]*hh_1[40]);
/* NN[527] */ NN.push_back(c2.v[2]*hh_1[124]);
/* NN[528] */ NN.push_back(c2.v[5]*hh_1[150]);
/* NN[529] */ NN.push_back(c2.v[6]*hh_1[52]);
/* NN[530] */ NN.push_back(c2.v[14]*hh_1[68]);
/* NN[531] */ NN.push_back(c2.v[15]*hh_1[130]);
/* NN[532] */ NN.push_back(c2.v[18]*hh_1[156]);
/* NN[533] */ NN.push_back(c2.v[22]*hh_1[84]);
/* NN[534] */ NN.push_back(c2.v[25]*hh_1[110]);
/* NN[535] */ NN.push_back(c2.v[26]*hh_1[12]);
/* NN[536] */ NN.push_back(c2.v[34]*hh_1[28]);
/* NN[537] */ NN.push_back(c2.v[35]*hh_1[90]);
/* NN[538] */ NN.push_back(c2.v[38]*hh_1[116]);
/* NN[539] */ NN.push_back(c2.v[42]*hh_1[44]);
/* NN[540] */ NN.push_back(c2.v[45]*hh_1[70]);
/* NN[541] */ NN.push_back(c2.v[46]*hh_1[132]);
/* NN[542] */ NN.push_back(c2.v[54]*hh_1[148]);
/* NN[543] */ NN.push_back(c2.v[55]*hh_1[50]);
/* NN[544] */ NN.push_back(c2.v[58]*hh_1[76]);
/* NN[545] */ NN.push_back(c2.v[62]*hh_1[4]);
/* NN[546] */ NN.push_back(c2.v[65]*hh_1[30]);
/* NN[547] */ NN.push_back(c2.v[66]*hh_1[92]);
/* NN[548] */ NN.push_back(c2.v[74]*hh_1[108]);
/* NN[549] */ NN.push_back(c2.v[75]*hh_1[10]);
/* NN[550] */ NN.push_back(c2.v[78]*hh_1[36]);
/* NN[551] */ NN.push_back(c2.v[2]*hh_1[132]);
/* NN[552] */ NN.push_back(c2.v[6]*hh_1[76]);
/* NN[553] */ NN.push_back(c2.v[14]*hh_1[124]);
/* NN[554] */ NN.push_back(c2.v[18]*hh_1[68]);
/* NN[555] */ NN.push_back(c2.v[22]*hh_1[12]);
/* NN[556] */ NN.push_back(c2.v[26]*hh_1[116]);
/* NN[557] */ NN.push_back(c2.v[34]*hh_1[4]);
/* NN[558] */ NN.push_back(c2.v[38]*hh_1[108]);
/* NN[559] */ NN.push_back(c2.v[42]*hh_1[52]);
/* NN[560] */ NN.push_back(c2.v[46]*hh_1[156]);
/* NN[561] */ NN.push_back(c2.v[54]*hh_1[44]);
/* NN[562] */ NN.push_back(c2.v[58]*hh_1[148]);
/* NN[563] */ NN.push_back(c2.v[62]*hh_1[92]);
/* NN[564] */ NN.push_back(c2.v[66]*hh_1[36]);
/* NN[565] */ NN.push_back(c2.v[74]*hh_1[84]);
/* NN[566] */ NN.push_back(c2.v[78]*hh_1[28]);
/* NN[567] */ NN.push_back(CC[2]*hh_1[136]);
/* NN[568] */ NN.push_back(CC[6]*hh_1[88]);
/* NN[569] */ NN.push_back(CC[14]*hh_1[152]);
/* NN[570] */ NN.push_back(CC[18]*hh_1[104]);
/* NN[571] */ NN.push_back(CC[22]*hh_1[56]);
/* NN[572] */ NN.push_back(CC[26]*hh_1[8]);
/* NN[573] */ NN.push_back(CC[34]*hh_1[72]);
/* NN[574] */ NN.push_back(CC[38]*hh_1[24]);
/* NN[575] */ NN.push_back(CC[62]*hh_1[140]);
/* NN[576] */ NN.push_back(CC[66]*hh_1[100]);
/* NN[577] */ NN.push_back(CC[70]*hh_1[60]);
/* NN[578] */ NN.push_back(CC[74]*hh_1[20]);
/* NN[579] */ NN.push_back(CC[42]*hh_1[144]);
/* NN[580] */ NN.push_back(CC[44]*hh_1[128]);
/* NN[581] */ NN.push_back(CC[46]*hh_1[112]);
/* NN[582] */ NN.push_back(CC[48]*hh_1[96]);
/* NN[583] */ NN.push_back(CC[52]*hh_1[64]);
/* NN[584] */ NN.push_back(CC[54]*hh_1[48]);
/* NN[585] */ NN.push_back(CC[56]*hh_1[32]);
/* NN[586] */ NN.push_back(CC[58]*hh_1[16]);
/* NN[587] */ NN.push_back(c2.v[2]*hh_1[148]);
/* NN[588] */ NN.push_back(c2.v[6]*hh_1[124]);
/* NN[589] */ NN.push_back(c2.v[14]*hh_1[76]);
/* NN[590] */ NN.push_back(c2.v[18]*hh_1[52]);
/* NN[591] */ NN.push_back(c2.v[22]*hh_1[28]);
/* NN[592] */ NN.push_back(c2.v[26]*hh_1[4]);
/* NN[593] */ NN.push_back(c2.v[34]*hh_1[116]);
/* NN[594] */ NN.push_back(c2.v[38]*hh_1[92]);
/* NN[595] */ NN.push_back(c2.v[42]*hh_1[68]);
/* NN[596] */ NN.push_back(c2.v[46]*hh_1[44]);
/* NN[597] */ NN.push_back(c2.v[54]*hh_1[156]);
/* NN[598] */ NN.push_back(c2.v[58]*hh_1[132]);
/* NN[599] */ NN.push_back(c2.v[62]*hh_1[108]);
/* NN[600] */ NN.push_back(c2.v[66]*hh_1[84]);
/* NN[601] */ NN.push_back(c2.v[74]*hh_1[36]);
/* NN[602] */ NN.push_back(c2.v[78]*hh_1[12]);
/* NN[603] */ NN.push_back(CC[2]*hh_1[152]);
/* NN[604] */ NN.push_back(CC[6]*hh_1[136]);
/* NN[605] */ NN.push_back(CC[14]*hh_1[104]);
/* NN[606] */ NN.push_back(CC[18]*hh_1[88]);
/* NN[607] */ NN.push_back(CC[22]*hh_1[72]);
/* NN[608] */ NN.push_back(CC[26]*hh_1[56]);
/* NN[609] */ NN.push_back(CC[34]*hh_1[24]);
/* NN[610] */ NN.push_back(CC[38]*hh_1[8]);
/* NN[611] */ NN.push_back(c2.v[2]*hh_1[156]);
/* NN[612] */ NN.push_back(c2.v[6]*hh_1[148]);
/* NN[613] */ NN.push_back(c2.v[14]*hh_1[132]);
/* NN[614] */ NN.push_back(c2.v[18]*hh_1[124]);
/* NN[615] */ NN.push_back(c2.v[22]*hh_1[116]);
/* NN[616] */ NN.push_back(c2.v[26]*hh_1[108]);
/* NN[617] */ NN.push_back(c2.v[34]*hh_1[92]);
/* NN[618] */ NN.push_back(c2.v[38]*hh_1[84]);
/* NN[619] */ NN.push_back(c2.v[42]*hh_1[76]);
/* NN[620] */ NN.push_back(c2.v[46]*hh_1[68]);
/* NN[621] */ NN.push_back(c2.v[54]*hh_1[52]);
/* NN[622] */ NN.push_back(c2.v[58]*hh_1[44]);
/* NN[623] */ NN.push_back(c2.v[62]*hh_1[36]);
/* NN[624] */ NN.push_back(c2.v[66]*hh_1[28]);
/* NN[625] */ NN.push_back(c2.v[74]*hh_1[12]);
/* NN[626] */ NN.push_back(c2.v[78]*hh_1[4]);

//отсчет 0
s= (c2.v[0] + c2.v[1] + c2.v[2] + c2.v[3] + c2.v[4] + c2.v[5] + c2.v[6] + c2.v[7] + c2.v[8] + c2.v[9] + c2.v[10] + c2.v[11] + c2.v[12] + c2.v[13] + c2.v[14] + c2.v[15] + c2.v[16] + c2.v[17] + c2.v[18] + c2.v[19] + c2.v[20] + c2.v[21] + c2.v[22] + c2.v[23] + c2.v[24] + c2.v[25] + c2.v[26] + c2.v[27] + c2.v[28] + c2.v[29] + c2.v[30] + c2.v[31] + c2.v[32] + c2.v[33] + c2.v[34] + c2.v[35] + c2.v[36] + c2.v[37] + c2.v[38] + c2.v[39] + c2.v[40] + c2.v[41] + c2.v[42] + c2.v[43] + c2.v[44] + c2.v[45] + c2.v[46] + c2.v[47] + c2.v[48] + c2.v[49] + c2.v[50] + c2.v[51] + c2.v[52] + c2.v[53] + c2.v[54] + c2.v[55] + c2.v[56] + c2.v[57] + c2.v[58] + c2.v[59] + c2.v[60] + c2.v[61] + c2.v[62] + c2.v[63] + c2.v[64] + c2.v[65] + c2.v[66] + c2.v[67] + c2.v[68] + c2.v[69] + c2.v[70] + c2.v[71] + c2.v[72] + c2.v[73] + c2.v[74] + c2.v[75] + c2.v[76] + c2.v[77] + c2.v[78] + c2.v[79])*hh_1[0];
s/=N_2;
out.push_back(s);

//отсчет 1
s= NN[0]
 + c2.v[1]*hh_1[2]
 + NN[1]
 + c2.v[3]*hh_1[6]
 + NN[2]
 + NN[3]
 + NN[4]
 + c2.v[7]*hh_1[14]
 + NN[5]
 + c2.v[9]*hh_1[18]
 + NN[6]
 + c2.v[11]*hh_1[22]
 + NN[7]
 + c2.v[13]*hh_1[26]
 + NN[8]
 + NN[9]
 + NN[10]
 + c2.v[17]*hh_1[34]
 + NN[11]
 + c2.v[19]*hh_1[38]
 + NN[12]
 + c2.v[21]*hh_1[42]
 + NN[13]
 + c2.v[23]*hh_1[46]
 + NN[14]
 + NN[15]
 + NN[16]
 + c2.v[27]*hh_1[54]
 + NN[17]
 + c2.v[29]*hh_1[58]
 + NN[18]
 + c2.v[31]*hh_1[62]
 + NN[19]
 + c2.v[33]*hh_1[66]
 + NN[20]
 + NN[21]
 + NN[22]
 + c2.v[37]*hh_1[74]
 + NN[23]
 + c2.v[39]*hh_1[78]
 + NN[24]
 + c2.v[41]*hh_1[82]
 + NN[25]
 + c2.v[43]*hh_1[86]
 + NN[26]
 + NN[27]
 + NN[28]
 + c2.v[47]*hh_1[94]
 + NN[29]
 + c2.v[49]*hh_1[98]
 + NN[30]
 + c2.v[51]*hh_1[102]
 + NN[31]
 + c2.v[53]*hh_1[106]
 + NN[32]
 + NN[33]
 + NN[34]
 + c2.v[57]*hh_1[114]
 + NN[35]
 + c2.v[59]*hh_1[118]
 + NN[36]
 + c2.v[61]*hh_1[122]
 + NN[37]
 + c2.v[63]*hh_1[126]
 + NN[38]
 + NN[39]
 + NN[40]
 + c2.v[67]*hh_1[134]
 + NN[41]
 + c2.v[69]*hh_1[138]
 + NN[42]
 + c2.v[71]*hh_1[142]
 + NN[43]
 + c2.v[73]*hh_1[146]
 + NN[44]
 + NN[45]
 + NN[46]
 + c2.v[77]*hh_1[154]
 + NN[47]
 + c2.v[79]*hh_1[158];
s/=N_2;
out.push_back(s);

//отсчет 2
s= NN[48]
 + CC[1]*hh_1[4]
 + NN[49]
 + CC[3]*hh_1[12]
 + NN[50]
 + NN[51]
 + NN[52]
 + CC[7]*hh_1[28]
 + NN[53]
 + CC[9]*hh_1[36]
 + NN[54]
 + CC[11]*hh_1[44]
 + NN[55]
 + CC[13]*hh_1[52]
 + NN[56]
 + NN[57]
 + NN[58]
 + CC[17]*hh_1[68]
 + NN[59]
 + CC[19]*hh_1[76]
 + NN[60]
 + CC[21]*hh_1[84]
 + NN[61]
 + CC[23]*hh_1[92]
 + NN[62]
 + NN[63]
 + NN[64]
 + CC[27]*hh_1[108]
 + NN[65]
 + CC[29]*hh_1[116]
 + NN[66]
 + CC[31]*hh_1[124]
 + NN[67]
 + CC[33]*hh_1[132]
 + NN[68]
 + NN[69]
 + NN[70]
 + CC[37]*hh_1[148]
 + NN[71]
 + CC[39]*hh_1[156];
s/=N_2;
out.push_back(s);

//отсчет 3
s= NN[0]
 + c2.v[1]*hh_1[6]
 + NN[72]
 + c2.v[3]*hh_1[18]
 + NN[73]
 + NN[74]
 + NN[75]
 + c2.v[7]*hh_1[42]
 + NN[76]
 + c2.v[9]*hh_1[54]
 + NN[77]
 + c2.v[11]*hh_1[66]
 + NN[78]
 + c2.v[13]*hh_1[78]
 + NN[79]
 + NN[80]
 + NN[81]
 + c2.v[17]*hh_1[102]
 + NN[82]
 + c2.v[19]*hh_1[114]
 + NN[83]
 + c2.v[21]*hh_1[126]
 + NN[84]
 + c2.v[23]*hh_1[138]
 + NN[85]
 + NN[86]
 + NN[87]
 + c2.v[27]*hh_1[2]
 + NN[88]
 + c2.v[29]*hh_1[14]
 + NN[89]
 + c2.v[31]*hh_1[26]
 + NN[90]
 + c2.v[33]*hh_1[38]
 + NN[91]
 + NN[92]
 + NN[93]
 + c2.v[37]*hh_1[62]
 + NN[94]
 + c2.v[39]*hh_1[74]
 + NN[24]
 + c2.v[41]*hh_1[86]
 + NN[95]
 + c2.v[43]*hh_1[98]
 + NN[96]
 + NN[97]
 + NN[98]
 + c2.v[47]*hh_1[122]
 + NN[99]
 + c2.v[49]*hh_1[134]
 + NN[100]
 + c2.v[51]*hh_1[146]
 + NN[101]
 + c2.v[53]*hh_1[158]
 + NN[102]
 + NN[103]
 + NN[104]
 + c2.v[57]*hh_1[22]
 + NN[105]
 + c2.v[59]*hh_1[34]
 + NN[106]
 + c2.v[61]*hh_1[46]
 + NN[107]
 + c2.v[63]*hh_1[58]
 + NN[108]
 + NN[109]
 + NN[110]
 + c2.v[67]*hh_1[82]
 + NN[111]
 + c2.v[69]*hh_1[94]
 + NN[112]
 + c2.v[71]*hh_1[106]
 + NN[113]
 + c2.v[73]*hh_1[118]
 + NN[114]
 + NN[115]
 + NN[116]
 + c2.v[77]*hh_1[142]
 + NN[117]
 + c2.v[79]*hh_1[154];
s/=N_2;
out.push_back(s);

//отсчет 4
s= NN[118]
 + CC[41]*hh_1[8]
 + NN[119]
 + CC[43]*hh_1[24]
 + NN[120]
 + NN[121]
 + NN[122]
 + CC[47]*hh_1[56]
 + NN[123]
 + CC[49]*hh_1[72]
 + NN[124]
 + CC[51]*hh_1[88]
 + NN[125]
 + CC[53]*hh_1[104]
 + NN[126]
 + NN[127]
 + NN[128]
 + CC[57]*hh_1[136]
 + NN[129]
 + CC[59]*hh_1[152];
s/=N_2;
out.push_back(s);

//отсчет 5
s= NN[130]
 + CC[61]*hh_1[10]
 + NN[131]
 + CC[63]*hh_1[30]
 + NN[132]
 + CC[65]*hh_1[50]
 + NN[133]
 + CC[67]*hh_1[70]
 + NN[134]
 + CC[69]*hh_1[90]
 + NN[135]
 + CC[71]*hh_1[110]
 + NN[136]
 + CC[73]*hh_1[130]
 + NN[137]
 + CC[75]*hh_1[150];
s/=N_2;
out.push_back(s);

//отсчет 6
s= NN[48]
 + CC[1]*hh_1[12]
 + NN[138]
 + CC[3]*hh_1[36]
 + NN[139]
 + NN[140]
 + NN[141]
 + CC[7]*hh_1[84]
 + NN[142]
 + CC[9]*hh_1[108]
 + NN[143]
 + CC[11]*hh_1[132]
 + NN[144]
 + CC[13]*hh_1[156]
 + NN[145]
 + NN[146]
 + NN[147]
 + CC[17]*hh_1[44]
 + NN[148]
 + CC[19]*hh_1[68]
 + NN[60]
 + CC[21]*hh_1[92]
 + NN[149]
 + CC[23]*hh_1[116]
 + NN[150]
 + NN[151]
 + NN[152]
 + CC[27]*hh_1[4]
 + NN[153]
 + CC[29]*hh_1[28]
 + NN[154]
 + CC[31]*hh_1[52]
 + NN[155]
 + CC[33]*hh_1[76]
 + NN[156]
 + NN[157]
 + NN[158]
 + CC[37]*hh_1[124]
 + NN[159]
 + CC[39]*hh_1[148];
s/=N_2;
out.push_back(s);

//отсчет 7
s= NN[0]
 + c2.v[1]*hh_1[14]
 + NN[160]
 + c2.v[3]*hh_1[42]
 + NN[161]
 + NN[162]
 + NN[163]
 + c2.v[7]*hh_1[98]
 + NN[164]
 + c2.v[9]*hh_1[126]
 + NN[165]
 + c2.v[11]*hh_1[154]
 + NN[166]
 + c2.v[13]*hh_1[22]
 + NN[167]
 + NN[168]
 + NN[169]
 + c2.v[17]*hh_1[78]
 + NN[170]
 + c2.v[19]*hh_1[106]
 + NN[83]
 + c2.v[21]*hh_1[134]
 + NN[171]
 + c2.v[23]*hh_1[2]
 + NN[172]
 + NN[173]
 + NN[174]
 + c2.v[27]*hh_1[58]
 + NN[175]
 + c2.v[29]*hh_1[86]
 + NN[176]
 + c2.v[31]*hh_1[114]
 + NN[177]
 + c2.v[33]*hh_1[142]
 + NN[178]
 + NN[179]
 + NN[180]
 + c2.v[37]*hh_1[38]
 + NN[181]
 + c2.v[39]*hh_1[66]
 + NN[24]
 + c2.v[41]*hh_1[94]
 + NN[182]
 + c2.v[43]*hh_1[122]
 + NN[183]
 + NN[184]
 + NN[185]
 + c2.v[47]*hh_1[18]
 + NN[186]
 + c2.v[49]*hh_1[46]
 + NN[187]
 + c2.v[51]*hh_1[74]
 + NN[188]
 + c2.v[53]*hh_1[102]
 + NN[189]
 + NN[190]
 + NN[191]
 + c2.v[57]*hh_1[158]
 + NN[192]
 + c2.v[59]*hh_1[26]
 + NN[106]
 + c2.v[61]*hh_1[54]
 + NN[193]
 + c2.v[63]*hh_1[82]
 + NN[194]
 + NN[195]
 + NN[196]
 + c2.v[67]*hh_1[138]
 + NN[197]
 + c2.v[69]*hh_1[6]
 + NN[198]
 + c2.v[71]*hh_1[34]
 + NN[199]
 + c2.v[73]*hh_1[62]
 + NN[200]
 + NN[201]
 + NN[202]
 + c2.v[77]*hh_1[118]
 + NN[203]
 + c2.v[79]*hh_1[146];
s/=N_2;
out.push_back(s);

//отсчет 8
s= NN[204]
 + CC[77]*hh_1[16]
 + CC[78]*hh_1[32]
 + CC[79]*hh_1[48]
 + CC[80]*hh_1[64]
 + NN[205]
 + CC[82]*hh_1[96]
 + CC[83]*hh_1[112]
 + CC[84]*hh_1[128]
 + CC[85]*hh_1[144];
s/=N_2;
out.push_back(s);

//отсчет 9
s= NN[0]
 + c2.v[1]*hh_1[18]
 + NN[206]
 + c2.v[3]*hh_1[54]
 + NN[207]
 + NN[208]
 + NN[209]
 + c2.v[7]*hh_1[126]
 + NN[210]
 + c2.v[9]*hh_1[2]
 + NN[6]
 + c2.v[11]*hh_1[38]
 + NN[211]
 + c2.v[13]*hh_1[74]
 + NN[212]
 + NN[213]
 + NN[214]
 + c2.v[17]*hh_1[146]
 + NN[215]
 + c2.v[19]*hh_1[22]
 + NN[12]
 + c2.v[21]*hh_1[58]
 + NN[216]
 + c2.v[23]*hh_1[94]
 + NN[217]
 + NN[218]
 + NN[219]
 + c2.v[27]*hh_1[6]
 + NN[220]
 + c2.v[29]*hh_1[42]
 + NN[18]
 + c2.v[31]*hh_1[78]
 + NN[221]
 + c2.v[33]*hh_1[114]
 + NN[222]
 + NN[223]
 + NN[224]
 + c2.v[37]*hh_1[26]
 + NN[225]
 + c2.v[39]*hh_1[62]
 + NN[24]
 + c2.v[41]*hh_1[98]
 + NN[226]
 + c2.v[43]*hh_1[134]
 + NN[227]
 + NN[228]
 + NN[229]
 + c2.v[47]*hh_1[46]
 + NN[230]
 + c2.v[49]*hh_1[82]
 + NN[30]
 + c2.v[51]*hh_1[118]
 + NN[231]
 + c2.v[53]*hh_1[154]
 + NN[232]
 + NN[233]
 + NN[234]
 + c2.v[57]*hh_1[66]
 + NN[235]
 + c2.v[59]*hh_1[102]
 + NN[36]
 + c2.v[61]*hh_1[138]
 + NN[236]
 + c2.v[63]*hh_1[14]
 + NN[237]
 + NN[238]
 + NN[239]
 + c2.v[67]*hh_1[86]
 + NN[240]
 + c2.v[69]*hh_1[122]
 + NN[42]
 + c2.v[71]*hh_1[158]
 + NN[241]
 + c2.v[73]*hh_1[34]
 + NN[242]
 + NN[243]
 + NN[244]
 + c2.v[77]*hh_1[106]
 + NN[245]
 + c2.v[79]*hh_1[142];
s/=N_2;
out.push_back(s);

//отсчет 10
s= NN[246]
 + CC[87]*hh_1[20]
 + NN[247]
 + CC[89]*hh_1[60]
 + NN[248]
 + CC[91]*hh_1[100]
 + NN[249]
 + CC[93]*hh_1[140];
s/=N_2;
out.push_back(s);

//отсчет 11
s= NN[0]
 + c2.v[1]*hh_1[22]
 + NN[250]
 + c2.v[3]*hh_1[66]
 + NN[251]
 + NN[252]
 + NN[253]
 + c2.v[7]*hh_1[154]
 + NN[5]
 + c2.v[9]*hh_1[38]
 + NN[77]
 + c2.v[11]*hh_1[82]
 + NN[254]
 + c2.v[13]*hh_1[126]
 + NN[255]
 + NN[256]
 + NN[10]
 + c2.v[17]*hh_1[54]
 + NN[257]
 + c2.v[19]*hh_1[98]
 + NN[83]
 + c2.v[21]*hh_1[142]
 + NN[258]
 + c2.v[23]*hh_1[26]
 + NN[14]
 + NN[259]
 + NN[260]
 + c2.v[27]*hh_1[114]
 + NN[261]
 + c2.v[29]*hh_1[158]
 + NN[89]
 + c2.v[31]*hh_1[42]
 + NN[19]
 + c2.v[33]*hh_1[86]
 + NN[262]
 + NN[263]
 + NN[264]
 + c2.v[37]*hh_1[14]
 + NN[265]
 + c2.v[39]*hh_1[58]
 + NN[24]
 + c2.v[41]*hh_1[102]
 + NN[266]
 + c2.v[43]*hh_1[146]
 + NN[267]
 + NN[268]
 + NN[269]
 + c2.v[47]*hh_1[74]
 + NN[29]
 + c2.v[49]*hh_1[118]
 + NN[100]
 + c2.v[51]*hh_1[2]
 + NN[270]
 + c2.v[53]*hh_1[46]
 + NN[271]
 + NN[272]
 + NN[34]
 + c2.v[57]*hh_1[134]
 + NN[273]
 + c2.v[59]*hh_1[18]
 + NN[106]
 + c2.v[61]*hh_1[62]
 + NN[274]
 + c2.v[63]*hh_1[106]
 + NN[38]
 + NN[275]
 + NN[276]
 + c2.v[67]*hh_1[34]
 + NN[277]
 + c2.v[69]*hh_1[78]
 + NN[112]
 + c2.v[71]*hh_1[122]
 + NN[43]
 + c2.v[73]*hh_1[6]
 + NN[278]
 + NN[279]
 + NN[280]
 + c2.v[77]*hh_1[94]
 + NN[281]
 + c2.v[79]*hh_1[138];
s/=N_2;
out.push_back(s);

//отсчет 12
s= NN[118]
 + CC[41]*hh_1[24]
 + NN[282]
 + CC[43]*hh_1[72]
 + NN[283]
 + NN[284]
 + NN[285]
 + CC[47]*hh_1[8]
 + NN[286]
 + CC[49]*hh_1[56]
 + NN[124]
 + CC[51]*hh_1[104]
 + NN[287]
 + CC[53]*hh_1[152]
 + NN[288]
 + NN[289]
 + NN[290]
 + CC[57]*hh_1[88]
 + NN[291]
 + CC[59]*hh_1[136];
s/=N_2;
out.push_back(s);

//отсчет 13
s= NN[0]
 + c2.v[1]*hh_1[26]
 + NN[292]
 + c2.v[3]*hh_1[78]
 + NN[293]
 + NN[294]
 + NN[295]
 + c2.v[7]*hh_1[22]
 + NN[76]
 + c2.v[9]*hh_1[74]
 + NN[296]
 + c2.v[11]*hh_1[126]
 + NN[297]
 + c2.v[13]*hh_1[18]
 + NN[298]
 + NN[299]
 + NN[81]
 + c2.v[17]*hh_1[122]
 + NN[300]
 + c2.v[19]*hh_1[14]
 + NN[12]
 + c2.v[21]*hh_1[66]
 + NN[301]
 + c2.v[23]*hh_1[118]
 + NN[85]
 + NN[302]
 + NN[303]
 + c2.v[27]*hh_1[62]
 + NN[304]
 + c2.v[29]*hh_1[114]
 + NN[305]
 + c2.v[31]*hh_1[6]
 + NN[90]
 + c2.v[33]*hh_1[58]
 + NN[306]
 + NN[307]
 + NN[308]
 + c2.v[37]*hh_1[2]
 + NN[309]
 + c2.v[39]*hh_1[54]
 + NN[24]
 + c2.v[41]*hh_1[106]
 + NN[310]
 + c2.v[43]*hh_1[158]
 + NN[311]
 + NN[312]
 + NN[313]
 + c2.v[47]*hh_1[102]
 + NN[99]
 + c2.v[49]*hh_1[154]
 + NN[314]
 + c2.v[51]*hh_1[46]
 + NN[315]
 + c2.v[53]*hh_1[98]
 + NN[316]
 + NN[317]
 + NN[104]
 + c2.v[57]*hh_1[42]
 + NN[318]
 + c2.v[59]*hh_1[94]
 + NN[36]
 + c2.v[61]*hh_1[146]
 + NN[319]
 + c2.v[63]*hh_1[38]
 + NN[108]
 + NN[320]
 + NN[321]
 + c2.v[67]*hh_1[142]
 + NN[322]
 + c2.v[69]*hh_1[34]
 + NN[323]
 + c2.v[71]*hh_1[86]
 + NN[113]
 + c2.v[73]*hh_1[138]
 + NN[324]
 + NN[325]
 + NN[326]
 + c2.v[77]*hh_1[82]
 + NN[327]
 + c2.v[79]*hh_1[134];
s/=N_2;
out.push_back(s);

//отсчет 14
s= NN[48]
 + CC[1]*hh_1[28]
 + NN[328]
 + CC[3]*hh_1[84]
 + NN[329]
 + NN[330]
 + NN[331]
 + CC[7]*hh_1[36]
 + NN[332]
 + CC[9]*hh_1[92]
 + NN[143]
 + CC[11]*hh_1[148]
 + NN[333]
 + CC[13]*hh_1[44]
 + NN[334]
 + NN[335]
 + NN[336]
 + CC[17]*hh_1[156]
 + NN[337]
 + CC[19]*hh_1[52]
 + NN[60]
 + CC[21]*hh_1[108]
 + NN[338]
 + CC[23]*hh_1[4]
 + NN[339]
 + NN[340]
 + NN[341]
 + CC[27]*hh_1[116]
 + NN[342]
 + CC[29]*hh_1[12]
 + NN[154]
 + CC[31]*hh_1[68]
 + NN[343]
 + CC[33]*hh_1[124]
 + NN[344]
 + NN[345]
 + NN[346]
 + CC[37]*hh_1[76]
 + NN[347]
 + CC[39]*hh_1[132];
s/=N_2;
out.push_back(s);

//отсчет 15
s= NN[130]
 + CC[61]*hh_1[30]
 + NN[348]
 + CC[63]*hh_1[90]
 + NN[349]
 + CC[65]*hh_1[150]
 + NN[350]
 + CC[67]*hh_1[50]
 + NN[134]
 + CC[69]*hh_1[110]
 + NN[351]
 + CC[71]*hh_1[10]
 + NN[352]
 + CC[73]*hh_1[70]
 + NN[353]
 + CC[75]*hh_1[130];
s/=N_2;
out.push_back(s);

//отсчет 16
s= NN[354]
 + CC[95]*hh_1[32]
 + CC[96]*hh_1[64]
 + CC[97]*hh_1[96]
 + CC[98]*hh_1[128];
s/=N_2;
out.push_back(s);

//отсчет 17
s= NN[0]
 + c2.v[1]*hh_1[34]
 + NN[355]
 + c2.v[3]*hh_1[102]
 + NN[356]
 + NN[3]
 + NN[357]
 + c2.v[7]*hh_1[78]
 + NN[164]
 + c2.v[9]*hh_1[146]
 + NN[6]
 + c2.v[11]*hh_1[54]
 + NN[358]
 + c2.v[13]*hh_1[122]
 + NN[359]
 + NN[9]
 + NN[169]
 + c2.v[17]*hh_1[98]
 + NN[360]
 + c2.v[19]*hh_1[6]
 + NN[12]
 + c2.v[21]*hh_1[74]
 + NN[361]
 + c2.v[23]*hh_1[142]
 + NN[172]
 + NN[15]
 + NN[362]
 + c2.v[27]*hh_1[118]
 + NN[363]
 + c2.v[29]*hh_1[26]
 + NN[18]
 + c2.v[31]*hh_1[94]
 + NN[177]
 + c2.v[33]*hh_1[2]
 + NN[364]
 + NN[21]
 + NN[365]
 + c2.v[37]*hh_1[138]
 + NN[366]
 + c2.v[39]*hh_1[46]
 + NN[24]
 + c2.v[41]*hh_1[114]
 + NN[367]
 + c2.v[43]*hh_1[22]
 + NN[368]
 + NN[27]
 + NN[369]
 + c2.v[47]*hh_1[158]
 + NN[186]
 + c2.v[49]*hh_1[66]
 + NN[30]
 + c2.v[51]*hh_1[134]
 + NN[370]
 + c2.v[53]*hh_1[42]
 + NN[371]
 + NN[33]
 + NN[191]
 + c2.v[57]*hh_1[18]
 + NN[372]
 + c2.v[59]*hh_1[86]
 + NN[36]
 + c2.v[61]*hh_1[154]
 + NN[373]
 + c2.v[63]*hh_1[62]
 + NN[194]
 + NN[39]
 + NN[374]
 + c2.v[67]*hh_1[38]
 + NN[375]
 + c2.v[69]*hh_1[106]
 + NN[42]
 + c2.v[71]*hh_1[14]
 + NN[199]
 + c2.v[73]*hh_1[82]
 + NN[376]
 + NN[45]
 + NN[377]
 + c2.v[77]*hh_1[58]
 + NN[378]
 + c2.v[79]*hh_1[126];
s/=N_2;
out.push_back(s);

//отсчет 18
s= NN[48]
 + CC[1]*hh_1[36]
 + NN[379]
 + CC[3]*hh_1[108]
 + NN[380]
 + NN[51]
 + NN[381]
 + CC[7]*hh_1[92]
 + NN[382]
 + CC[9]*hh_1[4]
 + NN[54]
 + CC[11]*hh_1[76]
 + NN[383]
 + CC[13]*hh_1[148]
 + NN[384]
 + NN[57]
 + NN[385]
 + CC[17]*hh_1[132]
 + NN[386]
 + CC[19]*hh_1[44]
 + NN[60]
 + CC[21]*hh_1[116]
 + NN[387]
 + CC[23]*hh_1[28]
 + NN[388]
 + NN[63]
 + NN[389]
 + CC[27]*hh_1[12]
 + NN[390]
 + CC[29]*hh_1[84]
 + NN[66]
 + CC[31]*hh_1[156]
 + NN[391]
 + CC[33]*hh_1[68]
 + NN[392]
 + NN[69]
 + NN[393]
 + CC[37]*hh_1[52]
 + NN[394]
 + CC[39]*hh_1[124];
s/=N_2;
out.push_back(s);

//отсчет 19
s= NN[0]
 + c2.v[1]*hh_1[38]
 + NN[395]
 + c2.v[3]*hh_1[114]
 + NN[396]
 + NN[74]
 + NN[397]
 + c2.v[7]*hh_1[106]
 + NN[210]
 + c2.v[9]*hh_1[22]
 + NN[77]
 + c2.v[11]*hh_1[98]
 + NN[398]
 + c2.v[13]*hh_1[14]
 + NN[399]
 + NN[80]
 + NN[214]
 + c2.v[17]*hh_1[6]
 + NN[400]
 + c2.v[19]*hh_1[82]
 + NN[83]
 + c2.v[21]*hh_1[158]
 + NN[401]
 + c2.v[23]*hh_1[74]
 + NN[217]
 + NN[86]
 + NN[402]
 + c2.v[27]*hh_1[66]
 + NN[403]
 + c2.v[29]*hh_1[142]
 + NN[89]
 + c2.v[31]*hh_1[58]
 + NN[221]
 + c2.v[33]*hh_1[134]
 + NN[404]
 + NN[92]
 + NN[405]
 + c2.v[37]*hh_1[126]
 + NN[406]
 + c2.v[39]*hh_1[42]
 + NN[24]
 + c2.v[41]*hh_1[118]
 + NN[407]
 + c2.v[43]*hh_1[34]
 + NN[408]
 + NN[97]
 + NN[409]
 + c2.v[47]*hh_1[26]
 + NN[230]
 + c2.v[49]*hh_1[102]
 + NN[100]
 + c2.v[51]*hh_1[18]
 + NN[410]
 + c2.v[53]*hh_1[94]
 + NN[411]
 + NN[103]
 + NN[234]
 + c2.v[57]*hh_1[86]
 + NN[412]
 + c2.v[59]*hh_1[2]
 + NN[106]
 + c2.v[61]*hh_1[78]
 + NN[413]
 + c2.v[63]*hh_1[154]
 + NN[237]
 + NN[109]
 + NN[414]
 + c2.v[67]*hh_1[146]
 + NN[415]
 + c2.v[69]*hh_1[62]
 + NN[112]
 + c2.v[71]*hh_1[138]
 + NN[241]
 + c2.v[73]*hh_1[54]
 + NN[416]
 + NN[115]
 + NN[417]
 + c2.v[77]*hh_1[46]
 + NN[418]
 + c2.v[79]*hh_1[122];
s/=N_2;
out.push_back(s);

//отсчет 20
s= NN[419]
 + CC[100]*hh_1[40]
 + NN[420]
 + CC[102]*hh_1[120];
s/=N_2;
out.push_back(s);

//отсчет 21
s= NN[0]
 + c2.v[1]*hh_1[42]
 + NN[421]
 + c2.v[3]*hh_1[126]
 + NN[2]
 + NN[422]
 + NN[423]
 + c2.v[7]*hh_1[134]
 + NN[5]
 + c2.v[9]*hh_1[58]
 + NN[296]
 + c2.v[11]*hh_1[142]
 + NN[7]
 + c2.v[13]*hh_1[66]
 + NN[424]
 + NN[425]
 + NN[10]
 + c2.v[17]*hh_1[74]
 + NN[426]
 + c2.v[19]*hh_1[158]
 + NN[12]
 + c2.v[21]*hh_1[82]
 + NN[427]
 + c2.v[23]*hh_1[6]
 + NN[14]
 + NN[428]
 + NN[429]
 + c2.v[27]*hh_1[14]
 + NN[17]
 + c2.v[29]*hh_1[98]
 + NN[305]
 + c2.v[31]*hh_1[22]
 + NN[19]
 + c2.v[33]*hh_1[106]
 + NN[430]
 + NN[431]
 + NN[22]
 + c2.v[37]*hh_1[114]
 + NN[432]
 + c2.v[39]*hh_1[38]
 + NN[24]
 + c2.v[41]*hh_1[122]
 + NN[433]
 + c2.v[43]*hh_1[46]
 + NN[26]
 + NN[434]
 + NN[435]
 + c2.v[47]*hh_1[54]
 + NN[29]
 + c2.v[49]*hh_1[138]
 + NN[314]
 + c2.v[51]*hh_1[62]
 + NN[31]
 + c2.v[53]*hh_1[146]
 + NN[436]
 + NN[437]
 + NN[34]
 + c2.v[57]*hh_1[154]
 + NN[438]
 + c2.v[59]*hh_1[78]
 + NN[36]
 + c2.v[61]*hh_1[2]
 + NN[439]
 + c2.v[63]*hh_1[86]
 + NN[38]
 + NN[440]
 + NN[441]
 + c2.v[67]*hh_1[94]
 + NN[41]
 + c2.v[69]*hh_1[18]
 + NN[323]
 + c2.v[71]*hh_1[102]
 + NN[43]
 + c2.v[73]*hh_1[26]
 + NN[442]
 + NN[443]
 + NN[46]
 + c2.v[77]*hh_1[34]
 + NN[444]
 + c2.v[79]*hh_1[118];
s/=N_2;
out.push_back(s);

//отсчет 22
s= NN[48]
 + CC[1]*hh_1[44]
 + NN[445]
 + CC[3]*hh_1[132]
 + NN[50]
 + NN[140]
 + NN[446]
 + CC[7]*hh_1[148]
 + NN[53]
 + CC[9]*hh_1[76]
 + NN[143]
 + CC[11]*hh_1[4]
 + NN[55]
 + CC[13]*hh_1[92]
 + NN[447]
 + NN[146]
 + NN[58]
 + CC[17]*hh_1[108]
 + NN[448]
 + CC[19]*hh_1[36]
 + NN[60]
 + CC[21]*hh_1[124]
 + NN[449]
 + CC[23]*hh_1[52]
 + NN[62]
 + NN[151]
 + NN[450]
 + CC[27]*hh_1[68]
 + NN[65]
 + CC[29]*hh_1[156]
 + NN[154]
 + CC[31]*hh_1[84]
 + NN[67]
 + CC[33]*hh_1[12]
 + NN[451]
 + NN[157]
 + NN[70]
 + CC[37]*hh_1[28]
 + NN[452]
 + CC[39]*hh_1[116];
s/=N_2;
out.push_back(s);

//отсчет 23
s= NN[0]
 + c2.v[1]*hh_1[46]
 + NN[453]
 + c2.v[3]*hh_1[138]
 + NN[73]
 + NN[162]
 + NN[454]
 + c2.v[7]*hh_1[2]
 + NN[76]
 + c2.v[9]*hh_1[94]
 + NN[165]
 + c2.v[11]*hh_1[26]
 + NN[78]
 + c2.v[13]*hh_1[118]
 + NN[455]
 + NN[168]
 + NN[81]
 + c2.v[17]*hh_1[142]
 + NN[456]
 + c2.v[19]*hh_1[74]
 + NN[83]
 + c2.v[21]*hh_1[6]
 + NN[457]
 + c2.v[23]*hh_1[98]
 + NN[85]
 + NN[173]
 + NN[458]
 + c2.v[27]*hh_1[122]
 + NN[88]
 + c2.v[29]*hh_1[54]
 + NN[176]
 + c2.v[31]*hh_1[146]
 + NN[90]
 + c2.v[33]*hh_1[78]
 + NN[459]
 + NN[179]
 + NN[93]
 + c2.v[37]*hh_1[102]
 + NN[460]
 + c2.v[39]*hh_1[34]
 + NN[24]
 + c2.v[41]*hh_1[126]
 + NN[461]
 + c2.v[43]*hh_1[58]
 + NN[96]
 + NN[184]
 + NN[462]
 + c2.v[47]*hh_1[82]
 + NN[99]
 + c2.v[49]*hh_1[14]
 + NN[187]
 + c2.v[51]*hh_1[106]
 + NN[101]
 + c2.v[53]*hh_1[38]
 + NN[463]
 + NN[190]
 + NN[104]
 + c2.v[57]*hh_1[62]
 + NN[464]
 + c2.v[59]*hh_1[154]
 + NN[106]
 + c2.v[61]*hh_1[86]
 + NN[465]
 + c2.v[63]*hh_1[18]
 + NN[108]
 + NN[195]
 + NN[466]
 + c2.v[67]*hh_1[42]
 + NN[111]
 + c2.v[69]*hh_1[134]
 + NN[198]
 + c2.v[71]*hh_1[66]
 + NN[113]
 + c2.v[73]*hh_1[158]
 + NN[467]
 + NN[201]
 + NN[116]
 + c2.v[77]*hh_1[22]
 + NN[468]
 + c2.v[79]*hh_1[114];
s/=N_2;
out.push_back(s);

//отсчет 24
s= NN[204]
 + CC[77]*hh_1[48]
 + CC[78]*hh_1[96]
 + CC[79]*hh_1[144]
 + CC[80]*hh_1[32]
 + NN[205]
 + CC[82]*hh_1[128]
 + CC[83]*hh_1[16]
 + CC[84]*hh_1[64]
 + CC[85]*hh_1[112];
s/=N_2;
out.push_back(s);

//отсчет 25
s= NN[130]
 + CC[61]*hh_1[50]
 + NN[469]
 + CC[63]*hh_1[150]
 + NN[132]
 + CC[65]*hh_1[90]
 + NN[470]
 + CC[67]*hh_1[30]
 + NN[134]
 + CC[69]*hh_1[130]
 + NN[471]
 + CC[71]*hh_1[70]
 + NN[136]
 + CC[73]*hh_1[10]
 + NN[472]
 + CC[75]*hh_1[110];
s/=N_2;
out.push_back(s);

//отсчет 26
s= NN[48]
 + CC[1]*hh_1[52]
 + NN[473]
 + CC[3]*hh_1[156]
 + NN[139]
 + NN[474]
 + NN[475]
 + CC[7]*hh_1[44]
 + NN[142]
 + CC[9]*hh_1[148]
 + NN[54]
 + CC[11]*hh_1[92]
 + NN[144]
 + CC[13]*hh_1[36]
 + NN[476]
 + NN[477]
 + NN[147]
 + CC[17]*hh_1[84]
 + NN[478]
 + CC[19]*hh_1[28]
 + NN[60]
 + CC[21]*hh_1[132]
 + NN[479]
 + CC[23]*hh_1[76]
 + NN[150]
 + NN[480]
 + NN[481]
 + CC[27]*hh_1[124]
 + NN[153]
 + CC[29]*hh_1[68]
 + NN[66]
 + CC[31]*hh_1[12]
 + NN[155]
 + CC[33]*hh_1[116]
 + NN[482]
 + NN[483]
 + NN[158]
 + CC[37]*hh_1[4]
 + NN[484]
 + CC[39]*hh_1[108];
s/=N_2;
out.push_back(s);

//отсчет 27
s= NN[0]
 + c2.v[1]*hh_1[54]
 + NN[485]
 + c2.v[3]*hh_1[2]
 + NN[161]
 + NN[252]
 + NN[486]
 + c2.v[7]*hh_1[58]
 + NN[164]
 + c2.v[9]*hh_1[6]
 + NN[77]
 + c2.v[11]*hh_1[114]
 + NN[166]
 + c2.v[13]*hh_1[62]
 + NN[487]
 + NN[256]
 + NN[169]
 + c2.v[17]*hh_1[118]
 + NN[488]
 + c2.v[19]*hh_1[66]
 + NN[83]
 + c2.v[21]*hh_1[14]
 + NN[489]
 + c2.v[23]*hh_1[122]
 + NN[172]
 + NN[259]
 + NN[490]
 + c2.v[27]*hh_1[18]
 + NN[175]
 + c2.v[29]*hh_1[126]
 + NN[89]
 + c2.v[31]*hh_1[74]
 + NN[177]
 + c2.v[33]*hh_1[22]
 + NN[491]
 + NN[263]
 + NN[180]
 + c2.v[37]*hh_1[78]
 + NN[492]
 + c2.v[39]*hh_1[26]
 + NN[24]
 + c2.v[41]*hh_1[134]
 + NN[493]
 + c2.v[43]*hh_1[82]
 + NN[183]
 + NN[268]
 + NN[494]
 + c2.v[47]*hh_1[138]
 + NN[186]
 + c2.v[49]*hh_1[86]
 + NN[100]
 + c2.v[51]*hh_1[34]
 + NN[188]
 + c2.v[53]*hh_1[142]
 + NN[495]
 + NN[272]
 + NN[191]
 + c2.v[57]*hh_1[38]
 + NN[496]
 + c2.v[59]*hh_1[146]
 + NN[106]
 + c2.v[61]*hh_1[94]
 + NN[497]
 + c2.v[63]*hh_1[42]
 + NN[194]
 + NN[275]
 + NN[498]
 + c2.v[67]*hh_1[98]
 + NN[197]
 + c2.v[69]*hh_1[46]
 + NN[112]
 + c2.v[71]*hh_1[154]
 + NN[199]
 + c2.v[73]*hh_1[102]
 + NN[499]
 + NN[279]
 + NN[202]
 + c2.v[77]*hh_1[158]
 + NN[500]
 + c2.v[79]*hh_1[106];
s/=N_2;
out.push_back(s);

//отсчет 28
s= NN[118]
 + CC[41]*hh_1[56]
 + NN[501]
 + CC[43]*hh_1[8]
 + NN[502]
 + NN[284]
 + NN[503]
 + CC[47]*hh_1[72]
 + NN[504]
 + CC[49]*hh_1[24]
 + NN[124]
 + CC[51]*hh_1[136]
 + NN[505]
 + CC[53]*hh_1[88]
 + NN[506]
 + NN[289]
 + NN[507]
 + CC[57]*hh_1[152]
 + NN[508]
 + CC[59]*hh_1[104];
s/=N_2;
out.push_back(s);

//отсчет 29
s= NN[0]
 + c2.v[1]*hh_1[58]
 + NN[509]
 + c2.v[3]*hh_1[14]
 + NN[207]
 + NN[294]
 + NN[510]
 + c2.v[7]*hh_1[86]
 + NN[210]
 + c2.v[9]*hh_1[42]
 + NN[296]
 + c2.v[11]*hh_1[158]
 + NN[211]
 + c2.v[13]*hh_1[114]
 + NN[511]
 + NN[299]
 + NN[214]
 + c2.v[17]*hh_1[26]
 + NN[512]
 + c2.v[19]*hh_1[142]
 + NN[12]
 + c2.v[21]*hh_1[98]
 + NN[513]
 + c2.v[23]*hh_1[54]
 + NN[217]
 + NN[302]
 + NN[514]
 + c2.v[27]*hh_1[126]
 + NN[220]
 + c2.v[29]*hh_1[82]
 + NN[305]
 + c2.v[31]*hh_1[38]
 + NN[221]
 + c2.v[33]*hh_1[154]
 + NN[515]
 + NN[307]
 + NN[224]
 + c2.v[37]*hh_1[66]
 + NN[516]
 + c2.v[39]*hh_1[22]
 + NN[24]
 + c2.v[41]*hh_1[138]
 + NN[517]
 + c2.v[43]*hh_1[94]
 + NN[227]
 + NN[312]
 + NN[518]
 + c2.v[47]*hh_1[6]
 + NN[230]
 + c2.v[49]*hh_1[122]
 + NN[314]
 + c2.v[51]*hh_1[78]
 + NN[231]
 + c2.v[53]*hh_1[34]
 + NN[519]
 + NN[317]
 + NN[234]
 + c2.v[57]*hh_1[106]
 + NN[520]
 + c2.v[59]*hh_1[62]
 + NN[36]
 + c2.v[61]*hh_1[18]
 + NN[521]
 + c2.v[63]*hh_1[134]
 + NN[237]
 + NN[320]
 + NN[522]
 + c2.v[67]*hh_1[46]
 + NN[240]
 + c2.v[69]*hh_1[2]
 + NN[323]
 + c2.v[71]*hh_1[118]
 + NN[241]
 + c2.v[73]*hh_1[74]
 + NN[523]
 + NN[325]
 + NN[244]
 + c2.v[77]*hh_1[146]
 + NN[524]
 + c2.v[79]*hh_1[102];
s/=N_2;
out.push_back(s);

//отсчет 30
s= NN[246]
 + CC[87]*hh_1[60]
 + NN[525]
 + CC[89]*hh_1[20]
 + NN[248]
 + CC[91]*hh_1[140]
 + NN[526]
 + CC[93]*hh_1[100];
s/=N_2;
out.push_back(s);

//отсчет 31
s= NN[0]
 + c2.v[1]*hh_1[62]
 + NN[527]
 + c2.v[3]*hh_1[26]
 + NN[251]
 + NN[528]
 + NN[529]
 + c2.v[7]*hh_1[114]
 + NN[5]
 + c2.v[9]*hh_1[78]
 + NN[165]
 + c2.v[11]*hh_1[42]
 + NN[254]
 + c2.v[13]*hh_1[6]
 + NN[530]
 + NN[531]
 + NN[10]
 + c2.v[17]*hh_1[94]
 + NN[532]
 + c2.v[19]*hh_1[58]
 + NN[83]
 + c2.v[21]*hh_1[22]
 + NN[533]
 + c2.v[23]*hh_1[146]
 + NN[14]
 + NN[534]
 + NN[535]
 + c2.v[27]*hh_1[74]
 + NN[261]
 + c2.v[29]*hh_1[38]
 + NN[176]
 + c2.v[31]*hh_1[2]
 + NN[19]
 + c2.v[33]*hh_1[126]
 + NN[536]
 + NN[537]
 + NN[264]
 + c2.v[37]*hh_1[54]
 + NN[538]
 + c2.v[39]*hh_1[18]
 + NN[24]
 + c2.v[41]*hh_1[142]
 + NN[539]
 + c2.v[43]*hh_1[106]
 + NN[267]
 + NN[540]
 + NN[541]
 + c2.v[47]*hh_1[34]
 + NN[29]
 + c2.v[49]*hh_1[158]
 + NN[187]
 + c2.v[51]*hh_1[122]
 + NN[270]
 + c2.v[53]*hh_1[86]
 + NN[542]
 + NN[543]
 + NN[34]
 + c2.v[57]*hh_1[14]
 + NN[544]
 + c2.v[59]*hh_1[138]
 + NN[106]
 + c2.v[61]*hh_1[102]
 + NN[545]
 + c2.v[63]*hh_1[66]
 + NN[38]
 + NN[546]
 + NN[547]
 + c2.v[67]*hh_1[154]
 + NN[277]
 + c2.v[69]*hh_1[118]
 + NN[198]
 + c2.v[71]*hh_1[82]
 + NN[43]
 + c2.v[73]*hh_1[46]
 + NN[548]
 + NN[549]
 + NN[280]
 + c2.v[77]*hh_1[134]
 + NN[550]
 + c2.v[79]*hh_1[98];
s/=N_2;
out.push_back(s);

//отсчет 32
s= NN[354]
 + CC[95]*hh_1[64]
 + CC[96]*hh_1[128]
 + CC[97]*hh_1[32]
 + CC[98]*hh_1[96];
s/=N_2;
out.push_back(s);

//отсчет 33
s= NN[0]
 + c2.v[1]*hh_1[66]
 + NN[551]
 + c2.v[3]*hh_1[38]
 + NN[293]
 + NN[3]
 + NN[552]
 + c2.v[7]*hh_1[142]
 + NN[76]
 + c2.v[9]*hh_1[114]
 + NN[6]
 + c2.v[11]*hh_1[86]
 + NN[297]
 + c2.v[13]*hh_1[58]
 + NN[553]
 + NN[9]
 + NN[81]
 + c2.v[17]*hh_1[2]
 + NN[554]
 + c2.v[19]*hh_1[134]
 + NN[12]
 + c2.v[21]*hh_1[106]
 + NN[555]
 + c2.v[23]*hh_1[78]
 + NN[85]
 + NN[15]
 + NN[556]
 + c2.v[27]*hh_1[22]
 + NN[304]
 + c2.v[29]*hh_1[154]
 + NN[18]
 + c2.v[31]*hh_1[126]
 + NN[90]
 + c2.v[33]*hh_1[98]
 + NN[557]
 + NN[21]
 + NN[308]
 + c2.v[37]*hh_1[42]
 + NN[558]
 + c2.v[39]*hh_1[14]
 + NN[24]
 + c2.v[41]*hh_1[146]
 + NN[559]
 + c2.v[43]*hh_1[118]
 + NN[311]
 + NN[27]
 + NN[560]
 + c2.v[47]*hh_1[62]
 + NN[99]
 + c2.v[49]*hh_1[34]
 + NN[30]
 + c2.v[51]*hh_1[6]
 + NN[315]
 + c2.v[53]*hh_1[138]
 + NN[561]
 + NN[33]
 + NN[104]
 + c2.v[57]*hh_1[82]
 + NN[562]
 + c2.v[59]*hh_1[54]
 + NN[36]
 + c2.v[61]*hh_1[26]
 + NN[563]
 + c2.v[63]*hh_1[158]
 + NN[108]
 + NN[39]
 + NN[564]
 + c2.v[67]*hh_1[102]
 + NN[322]
 + c2.v[69]*hh_1[74]
 + NN[42]
 + c2.v[71]*hh_1[46]
 + NN[113]
 + c2.v[73]*hh_1[18]
 + NN[565]
 + NN[45]
 + NN[326]
 + c2.v[77]*hh_1[122]
 + NN[566]
 + c2.v[79]*hh_1[94];
s/=N_2;
out.push_back(s);

//отсчет 34
s= NN[48]
 + CC[1]*hh_1[68]
 + NN[567]
 + CC[3]*hh_1[44]
 + NN[329]
 + NN[51]
 + NN[568]
 + CC[7]*hh_1[156]
 + NN[332]
 + CC[9]*hh_1[132]
 + NN[54]
 + CC[11]*hh_1[108]
 + NN[333]
 + CC[13]*hh_1[84]
 + NN[569]
 + NN[57]
 + NN[336]
 + CC[17]*hh_1[36]
 + NN[570]
 + CC[19]*hh_1[12]
 + NN[60]
 + CC[21]*hh_1[148]
 + NN[571]
 + CC[23]*hh_1[124]
 + NN[339]
 + NN[63]
 + NN[572]
 + CC[27]*hh_1[76]
 + NN[342]
 + CC[29]*hh_1[52]
 + NN[66]
 + CC[31]*hh_1[28]
 + NN[343]
 + CC[33]*hh_1[4]
 + NN[573]
 + NN[69]
 + NN[346]
 + CC[37]*hh_1[116]
 + NN[574]
 + CC[39]*hh_1[92];
s/=N_2;
out.push_back(s);

//отсчет 35
s= NN[130]
 + CC[61]*hh_1[70]
 + NN[575]
 + CC[63]*hh_1[50]
 + NN[349]
 + CC[65]*hh_1[30]
 + NN[576]
 + CC[67]*hh_1[10]
 + NN[134]
 + CC[69]*hh_1[150]
 + NN[577]
 + CC[71]*hh_1[130]
 + NN[352]
 + CC[73]*hh_1[110]
 + NN[578]
 + CC[75]*hh_1[90];
s/=N_2;
out.push_back(s);

//отсчет 36
s= NN[118]
 + CC[41]*hh_1[72]
 + NN[579]
 + CC[43]*hh_1[56]
 + NN[580]
 + NN[121]
 + NN[581]
 + CC[47]*hh_1[24]
 + NN[582]
 + CC[49]*hh_1[8]
 + NN[124]
 + CC[51]*hh_1[152]
 + NN[583]
 + CC[53]*hh_1[136]
 + NN[584]
 + NN[127]
 + NN[585]
 + CC[57]*hh_1[104]
 + NN[586]
 + CC[59]*hh_1[88];
s/=N_2;
out.push_back(s);

//отсчет 37
s= NN[0]
 + c2.v[1]*hh_1[74]
 + NN[587]
 + c2.v[3]*hh_1[62]
 + NN[356]
 + NN[422]
 + NN[588]
 + c2.v[7]*hh_1[38]
 + NN[164]
 + c2.v[9]*hh_1[26]
 + NN[296]
 + c2.v[11]*hh_1[14]
 + NN[358]
 + c2.v[13]*hh_1[2]
 + NN[589]
 + NN[425]
 + NN[169]
 + c2.v[17]*hh_1[138]
 + NN[590]
 + c2.v[19]*hh_1[126]
 + NN[12]
 + c2.v[21]*hh_1[114]
 + NN[591]
 + c2.v[23]*hh_1[102]
 + NN[172]
 + NN[428]
 + NN[592]
 + c2.v[27]*hh_1[78]
 + NN[363]
 + c2.v[29]*hh_1[66]
 + NN[305]
 + c2.v[31]*hh_1[54]
 + NN[177]
 + c2.v[33]*hh_1[42]
 + NN[593]
 + NN[431]
 + NN[365]
 + c2.v[37]*hh_1[18]
 + NN[594]
 + c2.v[39]*hh_1[6]
 + NN[24]
 + c2.v[41]*hh_1[154]
 + NN[595]
 + c2.v[43]*hh_1[142]
 + NN[368]
 + NN[434]
 + NN[596]
 + c2.v[47]*hh_1[118]
 + NN[186]
 + c2.v[49]*hh_1[106]
 + NN[314]
 + c2.v[51]*hh_1[94]
 + NN[370]
 + c2.v[53]*hh_1[82]
 + NN[597]
 + NN[437]
 + NN[191]
 + c2.v[57]*hh_1[58]
 + NN[598]
 + c2.v[59]*hh_1[46]
 + NN[36]
 + c2.v[61]*hh_1[34]
 + NN[599]
 + c2.v[63]*hh_1[22]
 + NN[194]
 + NN[440]
 + NN[600]
 + c2.v[67]*hh_1[158]
 + NN[375]
 + c2.v[69]*hh_1[146]
 + NN[323]
 + c2.v[71]*hh_1[134]
 + NN[199]
 + c2.v[73]*hh_1[122]
 + NN[601]
 + NN[443]
 + NN[377]
 + c2.v[77]*hh_1[98]
 + NN[602]
 + c2.v[79]*hh_1[86];
s/=N_2;
out.push_back(s);

//отсчет 38
s= NN[48]
 + CC[1]*hh_1[76]
 + NN[603]
 + CC[3]*hh_1[68]
 + NN[380]
 + NN[140]
 + NN[604]
 + CC[7]*hh_1[52]
 + NN[382]
 + CC[9]*hh_1[44]
 + NN[143]
 + CC[11]*hh_1[36]
 + NN[383]
 + CC[13]*hh_1[28]
 + NN[605]
 + NN[146]
 + NN[385]
 + CC[17]*hh_1[12]
 + NN[606]
 + CC[19]*hh_1[4]
 + NN[60]
 + CC[21]*hh_1[156]
 + NN[607]
 + CC[23]*hh_1[148]
 + NN[388]
 + NN[151]
 + NN[608]
 + CC[27]*hh_1[132]
 + NN[390]
 + CC[29]*hh_1[124]
 + NN[154]
 + CC[31]*hh_1[116]
 + NN[391]
 + CC[33]*hh_1[108]
 + NN[609]
 + NN[157]
 + NN[393]
 + CC[37]*hh_1[92]
 + NN[610]
 + CC[39]*hh_1[84];
s/=N_2;
out.push_back(s);

//отсчет 39
s= NN[0]
 + c2.v[1]*hh_1[78]
 + NN[611]
 + c2.v[3]*hh_1[74]
 + NN[396]
 + NN[162]
 + NN[612]
 + c2.v[7]*hh_1[66]
 + NN[210]
 + c2.v[9]*hh_1[62]
 + NN[165]
 + c2.v[11]*hh_1[58]
 + NN[398]
 + c2.v[13]*hh_1[54]
 + NN[613]
 + NN[168]
 + NN[214]
 + c2.v[17]*hh_1[46]
 + NN[614]
 + c2.v[19]*hh_1[42]
 + NN[83]
 + c2.v[21]*hh_1[38]
 + NN[615]
 + c2.v[23]*hh_1[34]
 + NN[217]
 + NN[173]
 + NN[616]
 + c2.v[27]*hh_1[26]
 + NN[403]
 + c2.v[29]*hh_1[22]
 + NN[176]
 + c2.v[31]*hh_1[18]
 + NN[221]
 + c2.v[33]*hh_1[14]
 + NN[617]
 + NN[179]
 + NN[405]
 + c2.v[37]*hh_1[6]
 + NN[618]
 + c2.v[39]*hh_1[2]
 + NN[24]
 + c2.v[41]*hh_1[158]
 + NN[619]
 + c2.v[43]*hh_1[154]
 + NN[408]
 + NN[184]
 + NN[620]
 + c2.v[47]*hh_1[146]
 + NN[230]
 + c2.v[49]*hh_1[142]
 + NN[187]
 + c2.v[51]*hh_1[138]
 + NN[410]
 + c2.v[53]*hh_1[134]
 + NN[621]
 + NN[190]
 + NN[234]
 + c2.v[57]*hh_1[126]
 + NN[622]
 + c2.v[59]*hh_1[122]
 + NN[106]
 + c2.v[61]*hh_1[118]
 + NN[623]
 + c2.v[63]*hh_1[114]
 + NN[237]
 + NN[195]
 + NN[624]
 + c2.v[67]*hh_1[106]
 + NN[415]
 + c2.v[69]*hh_1[102]
 + NN[198]
 + c2.v[71]*hh_1[98]
 + NN[241]
 + c2.v[73]*hh_1[94]
 + NN[625]
 + NN[201]
 + NN[417]
 + c2.v[77]*hh_1[86]
 + NN[626]
 + c2.v[79]*hh_1[82];
s/=N_2;
out.push_back(s);

//отсчет 40
s= (c2.v[0] + c2.v[2] + c2.v[4] + c2.v[6] + c2.v[8] + c2.v[10] + c2.v[12] + c2.v[14] + c2.v[16] + c2.v[18] + c2.v[20] + c2.v[22] + c2.v[24] + c2.v[26] + c2.v[28] + c2.v[30] + c2.v[32] + c2.v[34] + c2.v[36] + c2.v[38] + c2.v[40] + c2.v[42] + c2.v[44] + c2.v[46] + c2.v[48] + c2.v[50] + c2.v[52] + c2.v[54] + c2.v[56] + c2.v[58] + c2.v[60] + c2.v[62] + c2.v[64] + c2.v[66] + c2.v[68] + c2.v[70] + c2.v[72] + c2.v[74] + c2.v[76] + c2.v[78])*hh_1[0]
 + (c2.v[1] + c2.v[3] + c2.v[5] + c2.v[7] + c2.v[9] + c2.v[11] + c2.v[13] + c2.v[15] + c2.v[17] + c2.v[19] + c2.v[21] + c2.v[23] + c2.v[25] + c2.v[27] + c2.v[29] + c2.v[31] + c2.v[33] + c2.v[35] + c2.v[37] + c2.v[39] + c2.v[41] + c2.v[43] + c2.v[45] + c2.v[47] + c2.v[49] + c2.v[51] + c2.v[53] + c2.v[55] + c2.v[57] + c2.v[59] + c2.v[61] + c2.v[63] + c2.v[65] + c2.v[67] + c2.v[69] + c2.v[71] + c2.v[73] + c2.v[75] + c2.v[77] + c2.v[79])*hh_1[80];
s/=N_2;
out.push_back(s);

//отсчет 41
s= NN[0]
 + c2.v[1]*hh_1[82]
 + NN[1]
 + c2.v[3]*hh_1[86]
 + NN[2]
 + NN[208]
 + NN[4]
 + c2.v[7]*hh_1[94]
 + NN[5]
 + c2.v[9]*hh_1[98]
 + NN[6]
 + c2.v[11]*hh_1[102]
 + NN[7]
 + c2.v[13]*hh_1[106]
 + NN[8]
 + NN[213]
 + NN[10]
 + c2.v[17]*hh_1[114]
 + NN[11]
 + c2.v[19]*hh_1[118]
 + NN[12]
 + c2.v[21]*hh_1[122]
 + NN[13]
 + c2.v[23]*hh_1[126]
 + NN[14]
 + NN[218]
 + NN[16]
 + c2.v[27]*hh_1[134]
 + NN[17]
 + c2.v[29]*hh_1[138]
 + NN[18]
 + c2.v[31]*hh_1[142]
 + NN[19]
 + c2.v[33]*hh_1[146]
 + NN[20]
 + NN[223]
 + NN[22]
 + c2.v[37]*hh_1[154]
 + NN[23]
 + c2.v[39]*hh_1[158]
 + NN[24]
 + c2.v[41]*hh_1[2]
 + NN[25]
 + c2.v[43]*hh_1[6]
 + NN[26]
 + NN[228]
 + NN[28]
 + c2.v[47]*hh_1[14]
 + NN[29]
 + c2.v[49]*hh_1[18]
 + NN[30]
 + c2.v[51]*hh_1[22]
 + NN[31]
 + c2.v[53]*hh_1[26]
 + NN[32]
 + NN[233]
 + NN[34]
 + c2.v[57]*hh_1[34]
 + NN[35]
 + c2.v[59]*hh_1[38]
 + NN[36]
 + c2.v[61]*hh_1[42]
 + NN[37]
 + c2.v[63]*hh_1[46]
 + NN[38]
 + NN[238]
 + NN[40]
 + c2.v[67]*hh_1[54]
 + NN[41]
 + c2.v[69]*hh_1[58]
 + NN[42]
 + c2.v[71]*hh_1[62]
 + NN[43]
 + c2.v[73]*hh_1[66]
 + NN[44]
 + NN[243]
 + NN[46]
 + c2.v[77]*hh_1[74]
 + NN[47]
 + c2.v[79]*hh_1[78];
s/=N_2;
out.push_back(s);

//отсчет 42
s= NN[48]
 + CC[1]*hh_1[84]
 + NN[49]
 + CC[3]*hh_1[92]
 + NN[50]
 + NN[474]
 + NN[52]
 + CC[7]*hh_1[108]
 + NN[53]
 + CC[9]*hh_1[116]
 + NN[54]
 + CC[11]*hh_1[124]
 + NN[55]
 + CC[13]*hh_1[132]
 + NN[56]
 + NN[477]
 + NN[58]
 + CC[17]*hh_1[148]
 + NN[59]
 + CC[19]*hh_1[156]
 + NN[60]
 + CC[21]*hh_1[4]
 + NN[61]
 + CC[23]*hh_1[12]
 + NN[62]
 + NN[480]
 + NN[64]
 + CC[27]*hh_1[28]
 + NN[65]
 + CC[29]*hh_1[36]
 + NN[66]
 + CC[31]*hh_1[44]
 + NN[67]
 + CC[33]*hh_1[52]
 + NN[68]
 + NN[483]
 + NN[70]
 + CC[37]*hh_1[68]
 + NN[71]
 + CC[39]*hh_1[76];
s/=N_2;
out.push_back(s);

//отсчет 43
s= NN[0]
 + c2.v[1]*hh_1[86]
 + NN[72]
 + c2.v[3]*hh_1[98]
 + NN[73]
 + NN[252]
 + NN[75]
 + c2.v[7]*hh_1[122]
 + NN[76]
 + c2.v[9]*hh_1[134]
 + NN[77]
 + c2.v[11]*hh_1[146]
 + NN[78]
 + c2.v[13]*hh_1[158]
 + NN[79]
 + NN[256]
 + NN[81]
 + c2.v[17]*hh_1[22]
 + NN[82]
 + c2.v[19]*hh_1[34]
 + NN[83]
 + c2.v[21]*hh_1[46]
 + NN[84]
 + c2.v[23]*hh_1[58]
 + NN[85]
 + NN[259]
 + NN[87]
 + c2.v[27]*hh_1[82]
 + NN[88]
 + c2.v[29]*hh_1[94]
 + NN[89]
 + c2.v[31]*hh_1[106]
 + NN[90]
 + c2.v[33]*hh_1[118]
 + NN[91]
 + NN[263]
 + NN[93]
 + c2.v[37]*hh_1[142]
 + NN[94]
 + c2.v[39]*hh_1[154]
 + NN[24]
 + c2.v[41]*hh_1[6]
 + NN[95]
 + c2.v[43]*hh_1[18]
 + NN[96]
 + NN[268]
 + NN[98]
 + c2.v[47]*hh_1[42]
 + NN[99]
 + c2.v[49]*hh_1[54]
 + NN[100]
 + c2.v[51]*hh_1[66]
 + NN[101]
 + c2.v[53]*hh_1[78]
 + NN[102]
 + NN[272]
 + NN[104]
 + c2.v[57]*hh_1[102]
 + NN[105]
 + c2.v[59]*hh_1[114]
 + NN[106]
 + c2.v[61]*hh_1[126]
 + NN[107]
 + c2.v[63]*hh_1[138]
 + NN[108]
 + NN[275]
 + NN[110]
 + c2.v[67]*hh_1[2]
 + NN[111]
 + c2.v[69]*hh_1[14]
 + NN[112]
 + c2.v[71]*hh_1[26]
 + NN[113]
 + c2.v[73]*hh_1[38]
 + NN[114]
 + NN[279]
 + NN[116]
 + c2.v[77]*hh_1[62]
 + NN[117]
 + c2.v[79]*hh_1[74];
s/=N_2;
out.push_back(s);

//отсчет 44
s= NN[118]
 + CC[41]*hh_1[88]
 + NN[119]
 + CC[43]*hh_1[104]
 + NN[120]
 + NN[284]
 + NN[122]
 + CC[47]*hh_1[136]
 + NN[123]
 + CC[49]*hh_1[152]
 + NN[124]
 + CC[51]*hh_1[8]
 + NN[125]
 + CC[53]*hh_1[24]
 + NN[126]
 + NN[289]
 + NN[128]
 + CC[57]*hh_1[56]
 + NN[129]
 + CC[59]*hh_1[72];
s/=N_2;
out.push_back(s);

//отсчет 45
s= NN[130]
 + CC[61]*hh_1[90]
 + NN[131]
 + CC[63]*hh_1[110]
 + NN[132]
 + CC[65]*hh_1[130]
 + NN[133]
 + CC[67]*hh_1[150]
 + NN[134]
 + CC[69]*hh_1[10]
 + NN[135]
 + CC[71]*hh_1[30]
 + NN[136]
 + CC[73]*hh_1[50]
 + NN[137]
 + CC[75]*hh_1[70];
s/=N_2;
out.push_back(s);

//отсчет 46
s= NN[48]
 + CC[1]*hh_1[92]
 + NN[138]
 + CC[3]*hh_1[116]
 + NN[139]
 + NN[330]
 + NN[141]
 + CC[7]*hh_1[4]
 + NN[142]
 + CC[9]*hh_1[28]
 + NN[143]
 + CC[11]*hh_1[52]
 + NN[144]
 + CC[13]*hh_1[76]
 + NN[145]
 + NN[335]
 + NN[147]
 + CC[17]*hh_1[124]
 + NN[148]
 + CC[19]*hh_1[148]
 + NN[60]
 + CC[21]*hh_1[12]
 + NN[149]
 + CC[23]*hh_1[36]
 + NN[150]
 + NN[340]
 + NN[152]
 + CC[27]*hh_1[84]
 + NN[153]
 + CC[29]*hh_1[108]
 + NN[154]
 + CC[31]*hh_1[132]
 + NN[155]
 + CC[33]*hh_1[156]
 + NN[156]
 + NN[345]
 + NN[158]
 + CC[37]*hh_1[44]
 + NN[159]
 + CC[39]*hh_1[68];
s/=N_2;
out.push_back(s);

//отсчет 47
s= NN[0]
 + c2.v[1]*hh_1[94]
 + NN[160]
 + c2.v[3]*hh_1[122]
 + NN[161]
 + NN[528]
 + NN[163]
 + c2.v[7]*hh_1[18]
 + NN[164]
 + c2.v[9]*hh_1[46]
 + NN[165]
 + c2.v[11]*hh_1[74]
 + NN[166]
 + c2.v[13]*hh_1[102]
 + NN[167]
 + NN[531]
 + NN[169]
 + c2.v[17]*hh_1[158]
 + NN[170]
 + c2.v[19]*hh_1[26]
 + NN[83]
 + c2.v[21]*hh_1[54]
 + NN[171]
 + c2.v[23]*hh_1[82]
 + NN[172]
 + NN[534]
 + NN[174]
 + c2.v[27]*hh_1[138]
 + NN[175]
 + c2.v[29]*hh_1[6]
 + NN[176]
 + c2.v[31]*hh_1[34]
 + NN[177]
 + c2.v[33]*hh_1[62]
 + NN[178]
 + NN[537]
 + NN[180]
 + c2.v[37]*hh_1[118]
 + NN[181]
 + c2.v[39]*hh_1[146]
 + NN[24]
 + c2.v[41]*hh_1[14]
 + NN[182]
 + c2.v[43]*hh_1[42]
 + NN[183]
 + NN[540]
 + NN[185]
 + c2.v[47]*hh_1[98]
 + NN[186]
 + c2.v[49]*hh_1[126]
 + NN[187]
 + c2.v[51]*hh_1[154]
 + NN[188]
 + c2.v[53]*hh_1[22]
 + NN[189]
 + NN[543]
 + NN[191]
 + c2.v[57]*hh_1[78]
 + NN[192]
 + c2.v[59]*hh_1[106]
 + NN[106]
 + c2.v[61]*hh_1[134]
 + NN[193]
 + c2.v[63]*hh_1[2]
 + NN[194]
 + NN[546]
 + NN[196]
 + c2.v[67]*hh_1[58]
 + NN[197]
 + c2.v[69]*hh_1[86]
 + NN[198]
 + c2.v[71]*hh_1[114]
 + NN[199]
 + c2.v[73]*hh_1[142]
 + NN[200]
 + NN[549]
 + NN[202]
 + c2.v[77]*hh_1[38]
 + NN[203]
 + c2.v[79]*hh_1[66];
s/=N_2;
out.push_back(s);

//отсчет 48
s= NN[354]
 + CC[95]*hh_1[96]
 + CC[96]*hh_1[32]
 + CC[97]*hh_1[128]
 + CC[98]*hh_1[64];
s/=N_2;
out.push_back(s);

//отсчет 49
s= NN[0]
 + c2.v[1]*hh_1[98]
 + NN[206]
 + c2.v[3]*hh_1[134]
 + NN[207]
 + NN[3]
 + NN[209]
 + c2.v[7]*hh_1[46]
 + NN[210]
 + c2.v[9]*hh_1[82]
 + NN[6]
 + c2.v[11]*hh_1[118]
 + NN[211]
 + c2.v[13]*hh_1[154]
 + NN[212]
 + NN[9]
 + NN[214]
 + c2.v[17]*hh_1[66]
 + NN[215]
 + c2.v[19]*hh_1[102]
 + NN[12]
 + c2.v[21]*hh_1[138]
 + NN[216]
 + c2.v[23]*hh_1[14]
 + NN[217]
 + NN[15]
 + NN[219]
 + c2.v[27]*hh_1[86]
 + NN[220]
 + c2.v[29]*hh_1[122]
 + NN[18]
 + c2.v[31]*hh_1[158]
 + NN[221]
 + c2.v[33]*hh_1[34]
 + NN[222]
 + NN[21]
 + NN[224]
 + c2.v[37]*hh_1[106]
 + NN[225]
 + c2.v[39]*hh_1[142]
 + NN[24]
 + c2.v[41]*hh_1[18]
 + NN[226]
 + c2.v[43]*hh_1[54]
 + NN[227]
 + NN[27]
 + NN[229]
 + c2.v[47]*hh_1[126]
 + NN[230]
 + c2.v[49]*hh_1[2]
 + NN[30]
 + c2.v[51]*hh_1[38]
 + NN[231]
 + c2.v[53]*hh_1[74]
 + NN[232]
 + NN[33]
 + NN[234]
 + c2.v[57]*hh_1[146]
 + NN[235]
 + c2.v[59]*hh_1[22]
 + NN[36]
 + c2.v[61]*hh_1[58]
 + NN[236]
 + c2.v[63]*hh_1[94]
 + NN[237]
 + NN[39]
 + NN[239]
 + c2.v[67]*hh_1[6]
 + NN[240]
 + c2.v[69]*hh_1[42]
 + NN[42]
 + c2.v[71]*hh_1[78]
 + NN[241]
 + c2.v[73]*hh_1[114]
 + NN[242]
 + NN[45]
 + NN[244]
 + c2.v[77]*hh_1[26]
 + NN[245]
 + c2.v[79]*hh_1[62];
s/=N_2;
out.push_back(s);

//отсчет 50
s= NN[246]
 + CC[87]*hh_1[100]
 + NN[247]
 + CC[89]*hh_1[140]
 + NN[248]
 + CC[91]*hh_1[20]
 + NN[249]
 + CC[93]*hh_1[60];
s/=N_2;
out.push_back(s);

//отсчет 51
s= NN[0]
 + c2.v[1]*hh_1[102]
 + NN[250]
 + c2.v[3]*hh_1[146]
 + NN[251]
 + NN[74]
 + NN[253]
 + c2.v[7]*hh_1[74]
 + NN[5]
 + c2.v[9]*hh_1[118]
 + NN[77]
 + c2.v[11]*hh_1[2]
 + NN[254]
 + c2.v[13]*hh_1[46]
 + NN[255]
 + NN[80]
 + NN[10]
 + c2.v[17]*hh_1[134]
 + NN[257]
 + c2.v[19]*hh_1[18]
 + NN[83]
 + c2.v[21]*hh_1[62]
 + NN[258]
 + c2.v[23]*hh_1[106]
 + NN[14]
 + NN[86]
 + NN[260]
 + c2.v[27]*hh_1[34]
 + NN[261]
 + c2.v[29]*hh_1[78]
 + NN[89]
 + c2.v[31]*hh_1[122]
 + NN[19]
 + c2.v[33]*hh_1[6]
 + NN[262]
 + NN[92]
 + NN[264]
 + c2.v[37]*hh_1[94]
 + NN[265]
 + c2.v[39]*hh_1[138]
 + NN[24]
 + c2.v[41]*hh_1[22]
 + NN[266]
 + c2.v[43]*hh_1[66]
 + NN[267]
 + NN[97]
 + NN[269]
 + c2.v[47]*hh_1[154]
 + NN[29]
 + c2.v[49]*hh_1[38]
 + NN[100]
 + c2.v[51]*hh_1[82]
 + NN[270]
 + c2.v[53]*hh_1[126]
 + NN[271]
 + NN[103]
 + NN[34]
 + c2.v[57]*hh_1[54]
 + NN[273]
 + c2.v[59]*hh_1[98]
 + NN[106]
 + c2.v[61]*hh_1[142]
 + NN[274]
 + c2.v[63]*hh_1[26]
 + NN[38]
 + NN[109]
 + NN[276]
 + c2.v[67]*hh_1[114]
 + NN[277]
 + c2.v[69]*hh_1[158]
 + NN[112]
 + c2.v[71]*hh_1[42]
 + NN[43]
 + c2.v[73]*hh_1[86]
 + NN[278]
 + NN[115]
 + NN[280]
 + c2.v[77]*hh_1[14]
 + NN[281]
 + c2.v[79]*hh_1[58];
s/=N_2;
out.push_back(s);

//отсчет 52
s= NN[118]
 + CC[41]*hh_1[104]
 + NN[282]
 + CC[43]*hh_1[152]
 + NN[283]
 + NN[121]
 + NN[285]
 + CC[47]*hh_1[88]
 + NN[286]
 + CC[49]*hh_1[136]
 + NN[124]
 + CC[51]*hh_1[24]
 + NN[287]
 + CC[53]*hh_1[72]
 + NN[288]
 + NN[127]
 + NN[290]
 + CC[57]*hh_1[8]
 + NN[291]
 + CC[59]*hh_1[56];
s/=N_2;
out.push_back(s);

//отсчет 53
s= NN[0]
 + c2.v[1]*hh_1[106]
 + NN[292]
 + c2.v[3]*hh_1[158]
 + NN[293]
 + NN[422]
 + NN[295]
 + c2.v[7]*hh_1[102]
 + NN[76]
 + c2.v[9]*hh_1[154]
 + NN[296]
 + c2.v[11]*hh_1[46]
 + NN[297]
 + c2.v[13]*hh_1[98]
 + NN[298]
 + NN[425]
 + NN[81]
 + c2.v[17]*hh_1[42]
 + NN[300]
 + c2.v[19]*hh_1[94]
 + NN[12]
 + c2.v[21]*hh_1[146]
 + NN[301]
 + c2.v[23]*hh_1[38]
 + NN[85]
 + NN[428]
 + NN[303]
 + c2.v[27]*hh_1[142]
 + NN[304]
 + c2.v[29]*hh_1[34]
 + NN[305]
 + c2.v[31]*hh_1[86]
 + NN[90]
 + c2.v[33]*hh_1[138]
 + NN[306]
 + NN[431]
 + NN[308]
 + c2.v[37]*hh_1[82]
 + NN[309]
 + c2.v[39]*hh_1[134]
 + NN[24]
 + c2.v[41]*hh_1[26]
 + NN[310]
 + c2.v[43]*hh_1[78]
 + NN[311]
 + NN[434]
 + NN[313]
 + c2.v[47]*hh_1[22]
 + NN[99]
 + c2.v[49]*hh_1[74]
 + NN[314]
 + c2.v[51]*hh_1[126]
 + NN[315]
 + c2.v[53]*hh_1[18]
 + NN[316]
 + NN[437]
 + NN[104]
 + c2.v[57]*hh_1[122]
 + NN[318]
 + c2.v[59]*hh_1[14]
 + NN[36]
 + c2.v[61]*hh_1[66]
 + NN[319]
 + c2.v[63]*hh_1[118]
 + NN[108]
 + NN[440]
 + NN[321]
 + c2.v[67]*hh_1[62]
 + NN[322]
 + c2.v[69]*hh_1[114]
 + NN[323]
 + c2.v[71]*hh_1[6]
 + NN[113]
 + c2.v[73]*hh_1[58]
 + NN[324]
 + NN[443]
 + NN[326]
 + c2.v[77]*hh_1[2]
 + NN[327]
 + c2.v[79]*hh_1[54];
s/=N_2;
out.push_back(s);

//отсчет 54
s= NN[48]
 + CC[1]*hh_1[108]
 + NN[328]
 + CC[3]*hh_1[4]
 + NN[329]
 + NN[140]
 + NN[331]
 + CC[7]*hh_1[116]
 + NN[332]
 + CC[9]*hh_1[12]
 + NN[143]
 + CC[11]*hh_1[68]
 + NN[333]
 + CC[13]*hh_1[124]
 + NN[334]
 + NN[146]
 + NN[336]
 + CC[17]*hh_1[76]
 + NN[337]
 + CC[19]*hh_1[132]
 + NN[60]
 + CC[21]*hh_1[28]
 + NN[338]
 + CC[23]*hh_1[84]
 + NN[339]
 + NN[151]
 + NN[341]
 + CC[27]*hh_1[36]
 + NN[342]
 + CC[29]*hh_1[92]
 + NN[154]
 + CC[31]*hh_1[148]
 + NN[343]
 + CC[33]*hh_1[44]
 + NN[344]
 + NN[157]
 + NN[346]
 + CC[37]*hh_1[156]
 + NN[347]
 + CC[39]*hh_1[52];
s/=N_2;
out.push_back(s);

//отсчет 55
s= NN[130]
 + CC[61]*hh_1[110]
 + NN[348]
 + CC[63]*hh_1[10]
 + NN[349]
 + CC[65]*hh_1[70]
 + NN[350]
 + CC[67]*hh_1[130]
 + NN[134]
 + CC[69]*hh_1[30]
 + NN[351]
 + CC[71]*hh_1[90]
 + NN[352]
 + CC[73]*hh_1[150]
 + NN[353]
 + CC[75]*hh_1[50];
s/=N_2;
out.push_back(s);

//отсчет 56
s= NN[204]
 + CC[77]*hh_1[112]
 + CC[78]*hh_1[64]
 + CC[79]*hh_1[16]
 + CC[80]*hh_1[128]
 + NN[205]
 + CC[82]*hh_1[32]
 + CC[83]*hh_1[144]
 + CC[84]*hh_1[96]
 + CC[85]*hh_1[48];
s/=N_2;
out.push_back(s);

//отсчет 57
s= NN[0]
 + c2.v[1]*hh_1[114]
 + NN[355]
 + c2.v[3]*hh_1[22]
 + NN[356]
 + NN[208]
 + NN[357]
 + c2.v[7]*hh_1[158]
 + NN[164]
 + c2.v[9]*hh_1[66]
 + NN[6]
 + c2.v[11]*hh_1[134]
 + NN[358]
 + c2.v[13]*hh_1[42]
 + NN[359]
 + NN[213]
 + NN[169]
 + c2.v[17]*hh_1[18]
 + NN[360]
 + c2.v[19]*hh_1[86]
 + NN[12]
 + c2.v[21]*hh_1[154]
 + NN[361]
 + c2.v[23]*hh_1[62]
 + NN[172]
 + NN[218]
 + NN[362]
 + c2.v[27]*hh_1[38]
 + NN[363]
 + c2.v[29]*hh_1[106]
 + NN[18]
 + c2.v[31]*hh_1[14]
 + NN[177]
 + c2.v[33]*hh_1[82]
 + NN[364]
 + NN[223]
 + NN[365]
 + c2.v[37]*hh_1[58]
 + NN[366]
 + c2.v[39]*hh_1[126]
 + NN[24]
 + c2.v[41]*hh_1[34]
 + NN[367]
 + c2.v[43]*hh_1[102]
 + NN[368]
 + NN[228]
 + NN[369]
 + c2.v[47]*hh_1[78]
 + NN[186]
 + c2.v[49]*hh_1[146]
 + NN[30]
 + c2.v[51]*hh_1[54]
 + NN[370]
 + c2.v[53]*hh_1[122]
 + NN[371]
 + NN[233]
 + NN[191]
 + c2.v[57]*hh_1[98]
 + NN[372]
 + c2.v[59]*hh_1[6]
 + NN[36]
 + c2.v[61]*hh_1[74]
 + NN[373]
 + c2.v[63]*hh_1[142]
 + NN[194]
 + NN[238]
 + NN[374]
 + c2.v[67]*hh_1[118]
 + NN[375]
 + c2.v[69]*hh_1[26]
 + NN[42]
 + c2.v[71]*hh_1[94]
 + NN[199]
 + c2.v[73]*hh_1[2]
 + NN[376]
 + NN[243]
 + NN[377]
 + c2.v[77]*hh_1[138]
 + NN[378]
 + c2.v[79]*hh_1[46];
s/=N_2;
out.push_back(s);

//отсчет 58
s= NN[48]
 + CC[1]*hh_1[116]
 + NN[379]
 + CC[3]*hh_1[28]
 + NN[380]
 + NN[474]
 + NN[381]
 + CC[7]*hh_1[12]
 + NN[382]
 + CC[9]*hh_1[84]
 + NN[54]
 + CC[11]*hh_1[156]
 + NN[383]
 + CC[13]*hh_1[68]
 + NN[384]
 + NN[477]
 + NN[385]
 + CC[17]*hh_1[52]
 + NN[386]
 + CC[19]*hh_1[124]
 + NN[60]
 + CC[21]*hh_1[36]
 + NN[387]
 + CC[23]*hh_1[108]
 + NN[388]
 + NN[480]
 + NN[389]
 + CC[27]*hh_1[92]
 + NN[390]
 + CC[29]*hh_1[4]
 + NN[66]
 + CC[31]*hh_1[76]
 + NN[391]
 + CC[33]*hh_1[148]
 + NN[392]
 + NN[483]
 + NN[393]
 + CC[37]*hh_1[132]
 + NN[394]
 + CC[39]*hh_1[44];
s/=N_2;
out.push_back(s);

//отсчет 59
s= NN[0]
 + c2.v[1]*hh_1[118]
 + NN[395]
 + c2.v[3]*hh_1[34]
 + NN[396]
 + NN[252]
 + NN[397]
 + c2.v[7]*hh_1[26]
 + NN[210]
 + c2.v[9]*hh_1[102]
 + NN[77]
 + c2.v[11]*hh_1[18]
 + NN[398]
 + c2.v[13]*hh_1[94]
 + NN[399]
 + NN[256]
 + NN[214]
 + c2.v[17]*hh_1[86]
 + NN[400]
 + c2.v[19]*hh_1[2]
 + NN[83]
 + c2.v[21]*hh_1[78]
 + NN[401]
 + c2.v[23]*hh_1[154]
 + NN[217]
 + NN[259]
 + NN[402]
 + c2.v[27]*hh_1[146]
 + NN[403]
 + c2.v[29]*hh_1[62]
 + NN[89]
 + c2.v[31]*hh_1[138]
 + NN[221]
 + c2.v[33]*hh_1[54]
 + NN[404]
 + NN[263]
 + NN[405]
 + c2.v[37]*hh_1[46]
 + NN[406]
 + c2.v[39]*hh_1[122]
 + NN[24]
 + c2.v[41]*hh_1[38]
 + NN[407]
 + c2.v[43]*hh_1[114]
 + NN[408]
 + NN[268]
 + NN[409]
 + c2.v[47]*hh_1[106]
 + NN[230]
 + c2.v[49]*hh_1[22]
 + NN[100]
 + c2.v[51]*hh_1[98]
 + NN[410]
 + c2.v[53]*hh_1[14]
 + NN[411]
 + NN[272]
 + NN[234]
 + c2.v[57]*hh_1[6]
 + NN[412]
 + c2.v[59]*hh_1[82]
 + NN[106]
 + c2.v[61]*hh_1[158]
 + NN[413]
 + c2.v[63]*hh_1[74]
 + NN[237]
 + NN[275]
 + NN[414]
 + c2.v[67]*hh_1[66]
 + NN[415]
 + c2.v[69]*hh_1[142]
 + NN[112]
 + c2.v[71]*hh_1[58]
 + NN[241]
 + c2.v[73]*hh_1[134]
 + NN[416]
 + NN[279]
 + NN[417]
 + c2.v[77]*hh_1[126]
 + NN[418]
 + c2.v[79]*hh_1[42];
s/=N_2;
out.push_back(s);

//отсчет 60
s= NN[419]
 + CC[100]*hh_1[120]
 + NN[420]
 + CC[102]*hh_1[40];
s/=N_2;
out.push_back(s);

//отсчет 61
s= NN[0]
 + c2.v[1]*hh_1[122]
 + NN[421]
 + c2.v[3]*hh_1[46]
 + NN[2]
 + NN[294]
 + NN[423]
 + c2.v[7]*hh_1[54]
 + NN[5]
 + c2.v[9]*hh_1[138]
 + NN[296]
 + c2.v[11]*hh_1[62]
 + NN[7]
 + c2.v[13]*hh_1[146]
 + NN[424]
 + NN[299]
 + NN[10]
 + c2.v[17]*hh_1[154]
 + NN[426]
 + c2.v[19]*hh_1[78]
 + NN[12]
 + c2.v[21]*hh_1[2]
 + NN[427]
 + c2.v[23]*hh_1[86]
 + NN[14]
 + NN[302]
 + NN[429]
 + c2.v[27]*hh_1[94]
 + NN[17]
 + c2.v[29]*hh_1[18]
 + NN[305]
 + c2.v[31]*hh_1[102]
 + NN[19]
 + c2.v[33]*hh_1[26]
 + NN[430]
 + NN[307]
 + NN[22]
 + c2.v[37]*hh_1[34]
 + NN[432]
 + c2.v[39]*hh_1[118]
 + NN[24]
 + c2.v[41]*hh_1[42]
 + NN[433]
 + c2.v[43]*hh_1[126]
 + NN[26]
 + NN[312]
 + NN[435]
 + c2.v[47]*hh_1[134]
 + NN[29]
 + c2.v[49]*hh_1[58]
 + NN[314]
 + c2.v[51]*hh_1[142]
 + NN[31]
 + c2.v[53]*hh_1[66]
 + NN[436]
 + NN[317]
 + NN[34]
 + c2.v[57]*hh_1[74]
 + NN[438]
 + c2.v[59]*hh_1[158]
 + NN[36]
 + c2.v[61]*hh_1[82]
 + NN[439]
 + c2.v[63]*hh_1[6]
 + NN[38]
 + NN[320]
 + NN[441]
 + c2.v[67]*hh_1[14]
 + NN[41]
 + c2.v[69]*hh_1[98]
 + NN[323]
 + c2.v[71]*hh_1[22]
 + NN[43]
 + c2.v[73]*hh_1[106]
 + NN[442]
 + NN[325]
 + NN[46]
 + c2.v[77]*hh_1[114]
 + NN[444]
 + c2.v[79]*hh_1[38];
s/=N_2;
out.push_back(s);

//отсчет 62
s= NN[48]
 + CC[1]*hh_1[124]
 + NN[445]
 + CC[3]*hh_1[52]
 + NN[50]
 + NN[330]
 + NN[446]
 + CC[7]*hh_1[68]
 + NN[53]
 + CC[9]*hh_1[156]
 + NN[143]
 + CC[11]*hh_1[84]
 + NN[55]
 + CC[13]*hh_1[12]
 + NN[447]
 + NN[335]
 + NN[58]
 + CC[17]*hh_1[28]
 + NN[448]
 + CC[19]*hh_1[116]
 + NN[60]
 + CC[21]*hh_1[44]
 + NN[449]
 + CC[23]*hh_1[132]
 + NN[62]
 + NN[340]
 + NN[450]
 + CC[27]*hh_1[148]
 + NN[65]
 + CC[29]*hh_1[76]
 + NN[154]
 + CC[31]*hh_1[4]
 + NN[67]
 + CC[33]*hh_1[92]
 + NN[451]
 + NN[345]
 + NN[70]
 + CC[37]*hh_1[108]
 + NN[452]
 + CC[39]*hh_1[36];
s/=N_2;
out.push_back(s);

//отсчет 63
s= NN[0]
 + c2.v[1]*hh_1[126]
 + NN[453]
 + c2.v[3]*hh_1[58]
 + NN[73]
 + NN[528]
 + NN[454]
 + c2.v[7]*hh_1[82]
 + NN[76]
 + c2.v[9]*hh_1[14]
 + NN[165]
 + c2.v[11]*hh_1[106]
 + NN[78]
 + c2.v[13]*hh_1[38]
 + NN[455]
 + NN[531]
 + NN[81]
 + c2.v[17]*hh_1[62]
 + NN[456]
 + c2.v[19]*hh_1[154]
 + NN[83]
 + c2.v[21]*hh_1[86]
 + NN[457]
 + c2.v[23]*hh_1[18]
 + NN[85]
 + NN[534]
 + NN[458]
 + c2.v[27]*hh_1[42]
 + NN[88]
 + c2.v[29]*hh_1[134]
 + NN[176]
 + c2.v[31]*hh_1[66]
 + NN[90]
 + c2.v[33]*hh_1[158]
 + NN[459]
 + NN[537]
 + NN[93]
 + c2.v[37]*hh_1[22]
 + NN[460]
 + c2.v[39]*hh_1[114]
 + NN[24]
 + c2.v[41]*hh_1[46]
 + NN[461]
 + c2.v[43]*hh_1[138]
 + NN[96]
 + NN[540]
 + NN[462]
 + c2.v[47]*hh_1[2]
 + NN[99]
 + c2.v[49]*hh_1[94]
 + NN[187]
 + c2.v[51]*hh_1[26]
 + NN[101]
 + c2.v[53]*hh_1[118]
 + NN[463]
 + NN[543]
 + NN[104]
 + c2.v[57]*hh_1[142]
 + NN[464]
 + c2.v[59]*hh_1[74]
 + NN[106]
 + c2.v[61]*hh_1[6]
 + NN[465]
 + c2.v[63]*hh_1[98]
 + NN[108]
 + NN[546]
 + NN[466]
 + c2.v[67]*hh_1[122]
 + NN[111]
 + c2.v[69]*hh_1[54]
 + NN[198]
 + c2.v[71]*hh_1[146]
 + NN[113]
 + c2.v[73]*hh_1[78]
 + NN[467]
 + NN[549]
 + NN[116]
 + c2.v[77]*hh_1[102]
 + NN[468]
 + c2.v[79]*hh_1[34];
s/=N_2;
out.push_back(s);

//отсчет 64
s= NN[354]
 + CC[95]*hh_1[128]
 + CC[96]*hh_1[96]
 + CC[97]*hh_1[64]
 + CC[98]*hh_1[32];
s/=N_2;
out.push_back(s);

//отсчет 65
s= NN[130]
 + CC[61]*hh_1[130]
 + NN[469]
 + CC[63]*hh_1[70]
 + NN[132]
 + CC[65]*hh_1[10]
 + NN[470]
 + CC[67]*hh_1[110]
 + NN[134]
 + CC[69]*hh_1[50]
 + NN[471]
 + CC[71]*hh_1[150]
 + NN[136]
 + CC[73]*hh_1[90]
 + NN[472]
 + CC[75]*hh_1[30];
s/=N_2;
out.push_back(s);

//отсчет 66
s= NN[48]
 + CC[1]*hh_1[132]
 + NN[473]
 + CC[3]*hh_1[76]
 + NN[139]
 + NN[51]
 + NN[475]
 + CC[7]*hh_1[124]
 + NN[142]
 + CC[9]*hh_1[68]
 + NN[54]
 + CC[11]*hh_1[12]
 + NN[144]
 + CC[13]*hh_1[116]
 + NN[476]
 + NN[57]
 + NN[147]
 + CC[17]*hh_1[4]
 + NN[478]
 + CC[19]*hh_1[108]
 + NN[60]
 + CC[21]*hh_1[52]
 + NN[479]
 + CC[23]*hh_1[156]
 + NN[150]
 + NN[63]
 + NN[481]
 + CC[27]*hh_1[44]
 + NN[153]
 + CC[29]*hh_1[148]
 + NN[66]
 + CC[31]*hh_1[92]
 + NN[155]
 + CC[33]*hh_1[36]
 + NN[482]
 + NN[69]
 + NN[158]
 + CC[37]*hh_1[84]
 + NN[484]
 + CC[39]*hh_1[28];
s/=N_2;
out.push_back(s);

//отсчет 67
s= NN[0]
 + c2.v[1]*hh_1[134]
 + NN[485]
 + c2.v[3]*hh_1[82]
 + NN[161]
 + NN[74]
 + NN[486]
 + c2.v[7]*hh_1[138]
 + NN[164]
 + c2.v[9]*hh_1[86]
 + NN[77]
 + c2.v[11]*hh_1[34]
 + NN[166]
 + c2.v[13]*hh_1[142]
 + NN[487]
 + NN[80]
 + NN[169]
 + c2.v[17]*hh_1[38]
 + NN[488]
 + c2.v[19]*hh_1[146]
 + NN[83]
 + c2.v[21]*hh_1[94]
 + NN[489]
 + c2.v[23]*hh_1[42]
 + NN[172]
 + NN[86]
 + NN[490]
 + c2.v[27]*hh_1[98]
 + NN[175]
 + c2.v[29]*hh_1[46]
 + NN[89]
 + c2.v[31]*hh_1[154]
 + NN[177]
 + c2.v[33]*hh_1[102]
 + NN[491]
 + NN[92]
 + NN[180]
 + c2.v[37]*hh_1[158]
 + NN[492]
 + c2.v[39]*hh_1[106]
 + NN[24]
 + c2.v[41]*hh_1[54]
 + NN[493]
 + c2.v[43]*hh_1[2]
 + NN[183]
 + NN[97]
 + NN[494]
 + c2.v[47]*hh_1[58]
 + NN[186]
 + c2.v[49]*hh_1[6]
 + NN[100]
 + c2.v[51]*hh_1[114]
 + NN[188]
 + c2.v[53]*hh_1[62]
 + NN[495]
 + NN[103]
 + NN[191]
 + c2.v[57]*hh_1[118]
 + NN[496]
 + c2.v[59]*hh_1[66]
 + NN[106]
 + c2.v[61]*hh_1[14]
 + NN[497]
 + c2.v[63]*hh_1[122]
 + NN[194]
 + NN[109]
 + NN[498]
 + c2.v[67]*hh_1[18]
 + NN[197]
 + c2.v[69]*hh_1[126]
 + NN[112]
 + c2.v[71]*hh_1[74]
 + NN[199]
 + c2.v[73]*hh_1[22]
 + NN[499]
 + NN[115]
 + NN[202]
 + c2.v[77]*hh_1[78]
 + NN[500]
 + c2.v[79]*hh_1[26];
s/=N_2;
out.push_back(s);

//отсчет 68
s= NN[118]
 + CC[41]*hh_1[136]
 + NN[501]
 + CC[43]*hh_1[88]
 + NN[502]
 + NN[121]
 + NN[503]
 + CC[47]*hh_1[152]
 + NN[504]
 + CC[49]*hh_1[104]
 + NN[124]
 + CC[51]*hh_1[56]
 + NN[505]
 + CC[53]*hh_1[8]
 + NN[506]
 + NN[127]
 + NN[507]
 + CC[57]*hh_1[72]
 + NN[508]
 + CC[59]*hh_1[24];
s/=N_2;
out.push_back(s);

//отсчет 69
s= NN[0]
 + c2.v[1]*hh_1[138]
 + NN[509]
 + c2.v[3]*hh_1[94]
 + NN[207]
 + NN[422]
 + NN[510]
 + c2.v[7]*hh_1[6]
 + NN[210]
 + c2.v[9]*hh_1[122]
 + NN[296]
 + c2.v[11]*hh_1[78]
 + NN[211]
 + c2.v[13]*hh_1[34]
 + NN[511]
 + NN[425]
 + NN[214]
 + c2.v[17]*hh_1[106]
 + NN[512]
 + c2.v[19]*hh_1[62]
 + NN[12]
 + c2.v[21]*hh_1[18]
 + NN[513]
 + c2.v[23]*hh_1[134]
 + NN[217]
 + NN[428]
 + NN[514]
 + c2.v[27]*hh_1[46]
 + NN[220]
 + c2.v[29]*hh_1[2]
 + NN[305]
 + c2.v[31]*hh_1[118]
 + NN[221]
 + c2.v[33]*hh_1[74]
 + NN[515]
 + NN[431]
 + NN[224]
 + c2.v[37]*hh_1[146]
 + NN[516]
 + c2.v[39]*hh_1[102]
 + NN[24]
 + c2.v[41]*hh_1[58]
 + NN[517]
 + c2.v[43]*hh_1[14]
 + NN[227]
 + NN[434]
 + NN[518]
 + c2.v[47]*hh_1[86]
 + NN[230]
 + c2.v[49]*hh_1[42]
 + NN[314]
 + c2.v[51]*hh_1[158]
 + NN[231]
 + c2.v[53]*hh_1[114]
 + NN[519]
 + NN[437]
 + NN[234]
 + c2.v[57]*hh_1[26]
 + NN[520]
 + c2.v[59]*hh_1[142]
 + NN[36]
 + c2.v[61]*hh_1[98]
 + NN[521]
 + c2.v[63]*hh_1[54]
 + NN[237]
 + NN[440]
 + NN[522]
 + c2.v[67]*hh_1[126]
 + NN[240]
 + c2.v[69]*hh_1[82]
 + NN[323]
 + c2.v[71]*hh_1[38]
 + NN[241]
 + c2.v[73]*hh_1[154]
 + NN[523]
 + NN[443]
 + NN[244]
 + c2.v[77]*hh_1[66]
 + NN[524]
 + c2.v[79]*hh_1[22];
s/=N_2;
out.push_back(s);

//отсчет 70
s= NN[246]
 + CC[87]*hh_1[140]
 + NN[525]
 + CC[89]*hh_1[100]
 + NN[248]
 + CC[91]*hh_1[60]
 + NN[526]
 + CC[93]*hh_1[20];
s/=N_2;
out.push_back(s);

//отсчет 71
s= NN[0]
 + c2.v[1]*hh_1[142]
 + NN[527]
 + c2.v[3]*hh_1[106]
 + NN[251]
 + NN[162]
 + NN[529]
 + c2.v[7]*hh_1[34]
 + NN[5]
 + c2.v[9]*hh_1[158]
 + NN[165]
 + c2.v[11]*hh_1[122]
 + NN[254]
 + c2.v[13]*hh_1[86]
 + NN[530]
 + NN[168]
 + NN[10]
 + c2.v[17]*hh_1[14]
 + NN[532]
 + c2.v[19]*hh_1[138]
 + NN[83]
 + c2.v[21]*hh_1[102]
 + NN[533]
 + c2.v[23]*hh_1[66]
 + NN[14]
 + NN[173]
 + NN[535]
 + c2.v[27]*hh_1[154]
 + NN[261]
 + c2.v[29]*hh_1[118]
 + NN[176]
 + c2.v[31]*hh_1[82]
 + NN[19]
 + c2.v[33]*hh_1[46]
 + NN[536]
 + NN[179]
 + NN[264]
 + c2.v[37]*hh_1[134]
 + NN[538]
 + c2.v[39]*hh_1[98]
 + NN[24]
 + c2.v[41]*hh_1[62]
 + NN[539]
 + c2.v[43]*hh_1[26]
 + NN[267]
 + NN[184]
 + NN[541]
 + c2.v[47]*hh_1[114]
 + NN[29]
 + c2.v[49]*hh_1[78]
 + NN[187]
 + c2.v[51]*hh_1[42]
 + NN[270]
 + c2.v[53]*hh_1[6]
 + NN[542]
 + NN[190]
 + NN[34]
 + c2.v[57]*hh_1[94]
 + NN[544]
 + c2.v[59]*hh_1[58]
 + NN[106]
 + c2.v[61]*hh_1[22]
 + NN[545]
 + c2.v[63]*hh_1[146]
 + NN[38]
 + NN[195]
 + NN[547]
 + c2.v[67]*hh_1[74]
 + NN[277]
 + c2.v[69]*hh_1[38]
 + NN[198]
 + c2.v[71]*hh_1[2]
 + NN[43]
 + c2.v[73]*hh_1[126]
 + NN[548]
 + NN[201]
 + NN[280]
 + c2.v[77]*hh_1[54]
 + NN[550]
 + c2.v[79]*hh_1[18];
s/=N_2;
out.push_back(s);

//отсчет 72
s= NN[204]
 + CC[77]*hh_1[144]
 + CC[78]*hh_1[128]
 + CC[79]*hh_1[112]
 + CC[80]*hh_1[96]
 + NN[205]
 + CC[82]*hh_1[64]
 + CC[83]*hh_1[48]
 + CC[84]*hh_1[32]
 + CC[85]*hh_1[16];
s/=N_2;
out.push_back(s);

//отсчет 73
s= NN[0]
 + c2.v[1]*hh_1[146]
 + NN[551]
 + c2.v[3]*hh_1[118]
 + NN[293]
 + NN[208]
 + NN[552]
 + c2.v[7]*hh_1[62]
 + NN[76]
 + c2.v[9]*hh_1[34]
 + NN[6]
 + c2.v[11]*hh_1[6]
 + NN[297]
 + c2.v[13]*hh_1[138]
 + NN[553]
 + NN[213]
 + NN[81]
 + c2.v[17]*hh_1[82]
 + NN[554]
 + c2.v[19]*hh_1[54]
 + NN[12]
 + c2.v[21]*hh_1[26]
 + NN[555]
 + c2.v[23]*hh_1[158]
 + NN[85]
 + NN[218]
 + NN[556]
 + c2.v[27]*hh_1[102]
 + NN[304]
 + c2.v[29]*hh_1[74]
 + NN[18]
 + c2.v[31]*hh_1[46]
 + NN[90]
 + c2.v[33]*hh_1[18]
 + NN[557]
 + NN[223]
 + NN[308]
 + c2.v[37]*hh_1[122]
 + NN[558]
 + c2.v[39]*hh_1[94]
 + NN[24]
 + c2.v[41]*hh_1[66]
 + NN[559]
 + c2.v[43]*hh_1[38]
 + NN[311]
 + NN[228]
 + NN[560]
 + c2.v[47]*hh_1[142]
 + NN[99]
 + c2.v[49]*hh_1[114]
 + NN[30]
 + c2.v[51]*hh_1[86]
 + NN[315]
 + c2.v[53]*hh_1[58]
 + NN[561]
 + NN[233]
 + NN[104]
 + c2.v[57]*hh_1[2]
 + NN[562]
 + c2.v[59]*hh_1[134]
 + NN[36]
 + c2.v[61]*hh_1[106]
 + NN[563]
 + c2.v[63]*hh_1[78]
 + NN[108]
 + NN[238]
 + NN[564]
 + c2.v[67]*hh_1[22]
 + NN[322]
 + c2.v[69]*hh_1[154]
 + NN[42]
 + c2.v[71]*hh_1[126]
 + NN[113]
 + c2.v[73]*hh_1[98]
 + NN[565]
 + NN[243]
 + NN[326]
 + c2.v[77]*hh_1[42]
 + NN[566]
 + c2.v[79]*hh_1[14];
s/=N_2;
out.push_back(s);

//отсчет 74
s= NN[48]
 + CC[1]*hh_1[148]
 + NN[567]
 + CC[3]*hh_1[124]
 + NN[329]
 + NN[474]
 + NN[568]
 + CC[7]*hh_1[76]
 + NN[332]
 + CC[9]*hh_1[52]
 + NN[54]
 + CC[11]*hh_1[28]
 + NN[333]
 + CC[13]*hh_1[4]
 + NN[569]
 + NN[477]
 + NN[336]
 + CC[17]*hh_1[116]
 + NN[570]
 + CC[19]*hh_1[92]
 + NN[60]
 + CC[21]*hh_1[68]
 + NN[571]
 + CC[23]*hh_1[44]
 + NN[339]
 + NN[480]
 + NN[572]
 + CC[27]*hh_1[156]
 + NN[342]
 + CC[29]*hh_1[132]
 + NN[66]
 + CC[31]*hh_1[108]
 + NN[343]
 + CC[33]*hh_1[84]
 + NN[573]
 + NN[483]
 + NN[346]
 + CC[37]*hh_1[36]
 + NN[574]
 + CC[39]*hh_1[12];
s/=N_2;
out.push_back(s);

//отсчет 75
s= NN[130]
 + CC[61]*hh_1[150]
 + NN[575]
 + CC[63]*hh_1[130]
 + NN[349]
 + CC[65]*hh_1[110]
 + NN[576]
 + CC[67]*hh_1[90]
 + NN[134]
 + CC[69]*hh_1[70]
 + NN[577]
 + CC[71]*hh_1[50]
 + NN[352]
 + CC[73]*hh_1[30]
 + NN[578]
 + CC[75]*hh_1[10];
s/=N_2;
out.push_back(s);

//отсчет 76
s= NN[118]
 + CC[41]*hh_1[152]
 + NN[579]
 + CC[43]*hh_1[136]
 + NN[580]
 + NN[284]
 + NN[581]
 + CC[47]*hh_1[104]
 + NN[582]
 + CC[49]*hh_1[88]
 + NN[124]
 + CC[51]*hh_1[72]
 + NN[583]
 + CC[53]*hh_1[56]
 + NN[584]
 + NN[289]
 + NN[585]
 + CC[57]*hh_1[24]
 + NN[586]
 + CC[59]*hh_1[8];
s/=N_2;
out.push_back(s);

//отсчет 77
s= NN[0]
 + c2.v[1]*hh_1[154]
 + NN[587]
 + c2.v[3]*hh_1[142]
 + NN[356]
 + NN[294]
 + NN[588]
 + c2.v[7]*hh_1[118]
 + NN[164]
 + c2.v[9]*hh_1[106]
 + NN[296]
 + c2.v[11]*hh_1[94]
 + NN[358]
 + c2.v[13]*hh_1[82]
 + NN[589]
 + NN[299]
 + NN[169]
 + c2.v[17]*hh_1[58]
 + NN[590]
 + c2.v[19]*hh_1[46]
 + NN[12]
 + c2.v[21]*hh_1[34]
 + NN[591]
 + c2.v[23]*hh_1[22]
 + NN[172]
 + NN[302]
 + NN[592]
 + c2.v[27]*hh_1[158]
 + NN[363]
 + c2.v[29]*hh_1[146]
 + NN[305]
 + c2.v[31]*hh_1[134]
 + NN[177]
 + c2.v[33]*hh_1[122]
 + NN[593]
 + NN[307]
 + NN[365]
 + c2.v[37]*hh_1[98]
 + NN[594]
 + c2.v[39]*hh_1[86]
 + NN[24]
 + c2.v[41]*hh_1[74]
 + NN[595]
 + c2.v[43]*hh_1[62]
 + NN[368]
 + NN[312]
 + NN[596]
 + c2.v[47]*hh_1[38]
 + NN[186]
 + c2.v[49]*hh_1[26]
 + NN[314]
 + c2.v[51]*hh_1[14]
 + NN[370]
 + c2.v[53]*hh_1[2]
 + NN[597]
 + NN[317]
 + NN[191]
 + c2.v[57]*hh_1[138]
 + NN[598]
 + c2.v[59]*hh_1[126]
 + NN[36]
 + c2.v[61]*hh_1[114]
 + NN[599]
 + c2.v[63]*hh_1[102]
 + NN[194]
 + NN[320]
 + NN[600]
 + c2.v[67]*hh_1[78]
 + NN[375]
 + c2.v[69]*hh_1[66]
 + NN[323]
 + c2.v[71]*hh_1[54]
 + NN[199]
 + c2.v[73]*hh_1[42]
 + NN[601]
 + NN[325]
 + NN[377]
 + c2.v[77]*hh_1[18]
 + NN[602]
 + c2.v[79]*hh_1[6];
s/=N_2;
out.push_back(s);

//отсчет 78
s= NN[48]
 + CC[1]*hh_1[156]
 + NN[603]
 + CC[3]*hh_1[148]
 + NN[380]
 + NN[330]
 + NN[604]
 + CC[7]*hh_1[132]
 + NN[382]
 + CC[9]*hh_1[124]
 + NN[143]
 + CC[11]*hh_1[116]
 + NN[383]
 + CC[13]*hh_1[108]
 + NN[605]
 + NN[335]
 + NN[385]
 + CC[17]*hh_1[92]
 + NN[606]
 + CC[19]*hh_1[84]
 + NN[60]
 + CC[21]*hh_1[76]
 + NN[607]
 + CC[23]*hh_1[68]
 + NN[388]
 + NN[340]
 + NN[608]
 + CC[27]*hh_1[52]
 + NN[390]
 + CC[29]*hh_1[44]
 + NN[154]
 + CC[31]*hh_1[36]
 + NN[391]
 + CC[33]*hh_1[28]
 + NN[609]
 + NN[345]
 + NN[393]
 + CC[37]*hh_1[12]
 + NN[610]
 + CC[39]*hh_1[4];
s/=N_2;
out.push_back(s);

//отсчет 79
s= NN[0]
 + c2.v[1]*hh_1[158]
 + NN[611]
 + c2.v[3]*hh_1[154]
 + NN[396]
 + NN[528]
 + NN[612]
 + c2.v[7]*hh_1[146]
 + NN[210]
 + c2.v[9]*hh_1[142]
 + NN[165]
 + c2.v[11]*hh_1[138]
 + NN[398]
 + c2.v[13]*hh_1[134]
 + NN[613]
 + NN[531]
 + NN[214]
 + c2.v[17]*hh_1[126]
 + NN[614]
 + c2.v[19]*hh_1[122]
 + NN[83]
 + c2.v[21]*hh_1[118]
 + NN[615]
 + c2.v[23]*hh_1[114]
 + NN[217]
 + NN[534]
 + NN[616]
 + c2.v[27]*hh_1[106]
 + NN[403]
 + c2.v[29]*hh_1[102]
 + NN[176]
 + c2.v[31]*hh_1[98]
 + NN[221]
 + c2.v[33]*hh_1[94]
 + NN[617]
 + NN[537]
 + NN[405]
 + c2.v[37]*hh_1[86]
 + NN[618]
 + c2.v[39]*hh_1[82]
 + NN[24]
 + c2.v[41]*hh_1[78]
 + NN[619]
 + c2.v[43]*hh_1[74]
 + NN[408]
 + NN[540]
 + NN[620]
 + c2.v[47]*hh_1[66]
 + NN[230]
 + c2.v[49]*hh_1[62]
 + NN[187]
 + c2.v[51]*hh_1[58]
 + NN[410]
 + c2.v[53]*hh_1[54]
 + NN[621]
 + NN[543]
 + NN[234]
 + c2.v[57]*hh_1[46]
 + NN[622]
 + c2.v[59]*hh_1[42]
 + NN[106]
 + c2.v[61]*hh_1[38]
 + NN[623]
 + c2.v[63]*hh_1[34]
 + NN[237]
 + NN[546]
 + NN[624]
 + c2.v[67]*hh_1[26]
 + NN[415]
 + c2.v[69]*hh_1[22]
 + NN[198]
 + c2.v[71]*hh_1[18]
 + NN[241]
 + c2.v[73]*hh_1[14]
 + NN[625]
 + NN[549]
 + NN[417]
 + c2.v[77]*hh_1[6]
 + NN[626]
 + c2.v[79]*hh_1[2];
s/=N_2;
out.push_back(s);
int sz = out.size();
out.resize(2*sz);
memcpy(&out[sz],&out[0],sz*sizeof(complex<double>));
}
//-----------------------------------------------------------------------------
#endif
