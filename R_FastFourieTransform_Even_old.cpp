//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "R_FastFourieTransform_Even.h"
#include "SipClient_Unit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
void __fastcall rdft_even(vector<complex<double> >& out,TCoeff_BY_2& c2)
{
int N_2 = c2.N;
vector<complex<double> > nn;
complex<double> s;

/* nn[0] */ nn.push_back(c2.v[0]*MainFormSLS->hh_1[0]);
/* nn[1] */ nn.push_back(c2.v[2]*MainFormSLS->hh_1[4]);
/* nn[2] */ nn.push_back(c2.v[4]*MainFormSLS->hh_1[8]);
/* nn[3] */ nn.push_back(c2.v[5]*MainFormSLS->hh_1[10]);
/* nn[4] */ nn.push_back(c2.v[6]*MainFormSLS->hh_1[12]);
/* nn[5] */ nn.push_back(c2.v[8]*MainFormSLS->hh_1[16]);
/* nn[6] */ nn.push_back(c2.v[10]*MainFormSLS->hh_1[20]);
/* nn[7] */ nn.push_back(c2.v[12]*MainFormSLS->hh_1[24]);
/* nn[8] */ nn.push_back(c2.v[14]*MainFormSLS->hh_1[28]);
/* nn[9] */ nn.push_back(c2.v[15]*MainFormSLS->hh_1[30]);
/* nn[10] */ nn.push_back(c2.v[16]*MainFormSLS->hh_1[32]);
/* nn[11] */ nn.push_back(c2.v[18]*MainFormSLS->hh_1[36]);
/* nn[12] */ nn.push_back(c2.v[20]*MainFormSLS->hh_1[40]);
/* nn[13] */ nn.push_back(c2.v[22]*MainFormSLS->hh_1[44]);
/* nn[14] */ nn.push_back(c2.v[24]*MainFormSLS->hh_1[48]);
/* nn[15] */ nn.push_back(c2.v[25]*MainFormSLS->hh_1[50]);
/* nn[16] */ nn.push_back(c2.v[26]*MainFormSLS->hh_1[52]);
/* nn[17] */ nn.push_back(c2.v[28]*MainFormSLS->hh_1[56]);
/* nn[18] */ nn.push_back(c2.v[30]*MainFormSLS->hh_1[60]);
/* nn[19] */ nn.push_back(c2.v[32]*MainFormSLS->hh_1[64]);
/* nn[20] */ nn.push_back(c2.v[34]*MainFormSLS->hh_1[68]);
/* nn[21] */ nn.push_back(c2.v[35]*MainFormSLS->hh_1[70]);
/* nn[22] */ nn.push_back(c2.v[36]*MainFormSLS->hh_1[72]);
/* nn[23] */ nn.push_back(c2.v[38]*MainFormSLS->hh_1[76]);
/* nn[24] */ nn.push_back(c2.v[40]*MainFormSLS->hh_1[80]);
/* nn[25] */ nn.push_back(c2.v[42]*MainFormSLS->hh_1[84]);
/* nn[26] */ nn.push_back(c2.v[44]*MainFormSLS->hh_1[88]);
/* nn[27] */ nn.push_back(c2.v[45]*MainFormSLS->hh_1[90]);
/* nn[28] */ nn.push_back(c2.v[46]*MainFormSLS->hh_1[92]);
/* nn[29] */ nn.push_back(c2.v[48]*MainFormSLS->hh_1[96]);
/* nn[30] */ nn.push_back(c2.v[50]*MainFormSLS->hh_1[100]);
/* nn[31] */ nn.push_back(c2.v[52]*MainFormSLS->hh_1[104]);
/* nn[32] */ nn.push_back(c2.v[54]*MainFormSLS->hh_1[108]);
/* nn[33] */ nn.push_back(c2.v[55]*MainFormSLS->hh_1[110]);
/* nn[34] */ nn.push_back(c2.v[56]*MainFormSLS->hh_1[112]);
/* nn[35] */ nn.push_back(c2.v[58]*MainFormSLS->hh_1[116]);
/* nn[36] */ nn.push_back(c2.v[60]*MainFormSLS->hh_1[120]);
/* nn[37] */ nn.push_back(c2.v[62]*MainFormSLS->hh_1[124]);
/* nn[38] */ nn.push_back(c2.v[64]*MainFormSLS->hh_1[128]);
/* nn[39] */ nn.push_back(c2.v[65]*MainFormSLS->hh_1[130]);
/* nn[40] */ nn.push_back(c2.v[66]*MainFormSLS->hh_1[132]);
/* nn[41] */ nn.push_back(c2.v[68]*MainFormSLS->hh_1[136]);
/* nn[42] */ nn.push_back(c2.v[70]*MainFormSLS->hh_1[140]);
/* nn[43] */ nn.push_back(c2.v[72]*MainFormSLS->hh_1[144]);
/* nn[44] */ nn.push_back(c2.v[74]*MainFormSLS->hh_1[148]);
/* nn[45] */ nn.push_back(c2.v[75]*MainFormSLS->hh_1[150]);
/* nn[46] */ nn.push_back(c2.v[76]*MainFormSLS->hh_1[152]);
/* nn[47] */ nn.push_back(c2.v[78]*MainFormSLS->hh_1[156]);
/* nn[48] */ nn.push_back((c2.v[0] + c2.v[40])*MainFormSLS->hh_1[0]);
/* nn[49] */ nn.push_back((c2.v[2] + c2.v[42])*MainFormSLS->hh_1[8]);
/* nn[50] */ nn.push_back((c2.v[4] + c2.v[44])*MainFormSLS->hh_1[16]);
/* nn[51] */ nn.push_back((c2.v[5] + c2.v[45])*MainFormSLS->hh_1[20]);
/* nn[52] */ nn.push_back((c2.v[6] + c2.v[46])*MainFormSLS->hh_1[24]);
/* nn[53] */ nn.push_back((c2.v[8] + c2.v[48])*MainFormSLS->hh_1[32]);
/* nn[54] */ nn.push_back((c2.v[10] + c2.v[50])*MainFormSLS->hh_1[40]);
/* nn[55] */ nn.push_back((c2.v[12] + c2.v[52])*MainFormSLS->hh_1[48]);
/* nn[56] */ nn.push_back((c2.v[14] + c2.v[54])*MainFormSLS->hh_1[56]);
/* nn[57] */ nn.push_back((c2.v[15] + c2.v[55])*MainFormSLS->hh_1[60]);
/* nn[58] */ nn.push_back((c2.v[16] + c2.v[56])*MainFormSLS->hh_1[64]);
/* nn[59] */ nn.push_back((c2.v[18] + c2.v[58])*MainFormSLS->hh_1[72]);
/* nn[60] */ nn.push_back((c2.v[20] + c2.v[60])*MainFormSLS->hh_1[80]);
/* nn[61] */ nn.push_back((c2.v[22] + c2.v[62])*MainFormSLS->hh_1[88]);
/* nn[62] */ nn.push_back((c2.v[24] + c2.v[64])*MainFormSLS->hh_1[96]);
/* nn[63] */ nn.push_back((c2.v[25] + c2.v[65])*MainFormSLS->hh_1[100]);
/* nn[64] */ nn.push_back((c2.v[26] + c2.v[66])*MainFormSLS->hh_1[104]);
/* nn[65] */ nn.push_back((c2.v[28] + c2.v[68])*MainFormSLS->hh_1[112]);
/* nn[66] */ nn.push_back((c2.v[30] + c2.v[70])*MainFormSLS->hh_1[120]);
/* nn[67] */ nn.push_back((c2.v[32] + c2.v[72])*MainFormSLS->hh_1[128]);
/* nn[68] */ nn.push_back((c2.v[34] + c2.v[74])*MainFormSLS->hh_1[136]);
/* nn[69] */ nn.push_back((c2.v[35] + c2.v[75])*MainFormSLS->hh_1[140]);
/* nn[70] */ nn.push_back((c2.v[36] + c2.v[76])*MainFormSLS->hh_1[144]);
/* nn[71] */ nn.push_back((c2.v[38] + c2.v[78])*MainFormSLS->hh_1[152]);
/* nn[72] */ nn.push_back(c2.v[2]*MainFormSLS->hh_1[12]);
/* nn[73] */ nn.push_back(c2.v[4]*MainFormSLS->hh_1[24]);
/* nn[74] */ nn.push_back(c2.v[5]*MainFormSLS->hh_1[30]);
/* nn[75] */ nn.push_back(c2.v[6]*MainFormSLS->hh_1[36]);
/* nn[76] */ nn.push_back(c2.v[8]*MainFormSLS->hh_1[48]);
/* nn[77] */ nn.push_back(c2.v[10]*MainFormSLS->hh_1[60]);
/* nn[78] */ nn.push_back(c2.v[12]*MainFormSLS->hh_1[72]);
/* nn[79] */ nn.push_back(c2.v[14]*MainFormSLS->hh_1[84]);
/* nn[80] */ nn.push_back(c2.v[15]*MainFormSLS->hh_1[90]);
/* nn[81] */ nn.push_back(c2.v[16]*MainFormSLS->hh_1[96]);
/* nn[82] */ nn.push_back(c2.v[18]*MainFormSLS->hh_1[108]);
/* nn[83] */ nn.push_back(c2.v[20]*MainFormSLS->hh_1[120]);
/* nn[84] */ nn.push_back(c2.v[22]*MainFormSLS->hh_1[132]);
/* nn[85] */ nn.push_back(c2.v[24]*MainFormSLS->hh_1[144]);
/* nn[86] */ nn.push_back(c2.v[25]*MainFormSLS->hh_1[150]);
/* nn[87] */ nn.push_back(c2.v[26]*MainFormSLS->hh_1[156]);
/* nn[88] */ nn.push_back(c2.v[28]*MainFormSLS->hh_1[8]);
/* nn[89] */ nn.push_back(c2.v[30]*MainFormSLS->hh_1[20]);
/* nn[90] */ nn.push_back(c2.v[32]*MainFormSLS->hh_1[32]);
/* nn[91] */ nn.push_back(c2.v[34]*MainFormSLS->hh_1[44]);
/* nn[92] */ nn.push_back(c2.v[35]*MainFormSLS->hh_1[50]);
/* nn[93] */ nn.push_back(c2.v[36]*MainFormSLS->hh_1[56]);
/* nn[94] */ nn.push_back(c2.v[38]*MainFormSLS->hh_1[68]);
/* nn[95] */ nn.push_back(c2.v[42]*MainFormSLS->hh_1[92]);
/* nn[96] */ nn.push_back(c2.v[44]*MainFormSLS->hh_1[104]);
/* nn[97] */ nn.push_back(c2.v[45]*MainFormSLS->hh_1[110]);
/* nn[98] */ nn.push_back(c2.v[46]*MainFormSLS->hh_1[116]);
/* nn[99] */ nn.push_back(c2.v[48]*MainFormSLS->hh_1[128]);
/* nn[100] */ nn.push_back(c2.v[50]*MainFormSLS->hh_1[140]);
/* nn[101] */ nn.push_back(c2.v[52]*MainFormSLS->hh_1[152]);
/* nn[102] */ nn.push_back(c2.v[54]*MainFormSLS->hh_1[4]);
/* nn[103] */ nn.push_back(c2.v[55]*MainFormSLS->hh_1[10]);
/* nn[104] */ nn.push_back(c2.v[56]*MainFormSLS->hh_1[16]);
/* nn[105] */ nn.push_back(c2.v[58]*MainFormSLS->hh_1[28]);
/* nn[106] */ nn.push_back(c2.v[60]*MainFormSLS->hh_1[40]);
/* nn[107] */ nn.push_back(c2.v[62]*MainFormSLS->hh_1[52]);
/* nn[108] */ nn.push_back(c2.v[64]*MainFormSLS->hh_1[64]);
/* nn[109] */ nn.push_back(c2.v[65]*MainFormSLS->hh_1[70]);
/* nn[110] */ nn.push_back(c2.v[66]*MainFormSLS->hh_1[76]);
/* nn[111] */ nn.push_back(c2.v[68]*MainFormSLS->hh_1[88]);
/* nn[112] */ nn.push_back(c2.v[70]*MainFormSLS->hh_1[100]);
/* nn[113] */ nn.push_back(c2.v[72]*MainFormSLS->hh_1[112]);
/* nn[114] */ nn.push_back(c2.v[74]*MainFormSLS->hh_1[124]);
/* nn[115] */ nn.push_back(c2.v[75]*MainFormSLS->hh_1[130]);
/* nn[116] */ nn.push_back(c2.v[76]*MainFormSLS->hh_1[136]);
/* nn[117] */ nn.push_back(c2.v[78]*MainFormSLS->hh_1[148]);
/* nn[118] */ nn.push_back((c2.v[0] + c2.v[20] + c2.v[40] + c2.v[60])*MainFormSLS->hh_1[0]);
/* nn[119] */ nn.push_back((c2.v[2] + c2.v[22] + c2.v[42] + c2.v[62])*MainFormSLS->hh_1[16]);
/* nn[120] */ nn.push_back((c2.v[4] + c2.v[24] + c2.v[44] + c2.v[64])*MainFormSLS->hh_1[32]);
/* nn[121] */ nn.push_back((c2.v[5] + c2.v[25] + c2.v[45] + c2.v[65])*MainFormSLS->hh_1[40]);
/* nn[122] */ nn.push_back((c2.v[6] + c2.v[26] + c2.v[46] + c2.v[66])*MainFormSLS->hh_1[48]);
/* nn[123] */ nn.push_back((c2.v[8] + c2.v[28] + c2.v[48] + c2.v[68])*MainFormSLS->hh_1[64]);
/* nn[124] */ nn.push_back((c2.v[10] + c2.v[30] + c2.v[50] + c2.v[70])*MainFormSLS->hh_1[80]);
/* nn[125] */ nn.push_back((c2.v[12] + c2.v[32] + c2.v[52] + c2.v[72])*MainFormSLS->hh_1[96]);
/* nn[126] */ nn.push_back((c2.v[14] + c2.v[34] + c2.v[54] + c2.v[74])*MainFormSLS->hh_1[112]);
/* nn[127] */ nn.push_back((c2.v[15] + c2.v[35] + c2.v[55] + c2.v[75])*MainFormSLS->hh_1[120]);
/* nn[128] */ nn.push_back((c2.v[16] + c2.v[36] + c2.v[56] + c2.v[76])*MainFormSLS->hh_1[128]);
/* nn[129] */ nn.push_back((c2.v[18] + c2.v[38] + c2.v[58] + c2.v[78])*MainFormSLS->hh_1[144]);
/* nn[130] */ nn.push_back((c2.v[0] + c2.v[16] + c2.v[32] + c2.v[48] + c2.v[64])*MainFormSLS->hh_1[0]);
/* nn[131] */ nn.push_back((c2.v[2] + c2.v[18] + c2.v[34] + c2.v[50] + c2.v[66])*MainFormSLS->hh_1[20]);
/* nn[132] */ nn.push_back((c2.v[4] + c2.v[20] + c2.v[36] + c2.v[52] + c2.v[68])*MainFormSLS->hh_1[40]);
/* nn[133] */ nn.push_back((c2.v[6] + c2.v[22] + c2.v[38] + c2.v[54] + c2.v[70])*MainFormSLS->hh_1[60]);
/* nn[134] */ nn.push_back((c2.v[8] + c2.v[24] + c2.v[40] + c2.v[56] + c2.v[72])*MainFormSLS->hh_1[80]);
/* nn[135] */ nn.push_back((c2.v[10] + c2.v[26] + c2.v[42] + c2.v[58] + c2.v[74])*MainFormSLS->hh_1[100]);
/* nn[136] */ nn.push_back((c2.v[12] + c2.v[28] + c2.v[44] + c2.v[60] + c2.v[76])*MainFormSLS->hh_1[120]);
/* nn[137] */ nn.push_back((c2.v[14] + c2.v[30] + c2.v[46] + c2.v[62] + c2.v[78])*MainFormSLS->hh_1[140]);
/* nn[138] */ nn.push_back((c2.v[2] + c2.v[42])*MainFormSLS->hh_1[24]);
/* nn[139] */ nn.push_back((c2.v[4] + c2.v[44])*MainFormSLS->hh_1[48]);
/* nn[140] */ nn.push_back((c2.v[5] + c2.v[45])*MainFormSLS->hh_1[60]);
/* nn[141] */ nn.push_back((c2.v[6] + c2.v[46])*MainFormSLS->hh_1[72]);
/* nn[142] */ nn.push_back((c2.v[8] + c2.v[48])*MainFormSLS->hh_1[96]);
/* nn[143] */ nn.push_back((c2.v[10] + c2.v[50])*MainFormSLS->hh_1[120]);
/* nn[144] */ nn.push_back((c2.v[12] + c2.v[52])*MainFormSLS->hh_1[144]);
/* nn[145] */ nn.push_back((c2.v[14] + c2.v[54])*MainFormSLS->hh_1[8]);
/* nn[146] */ nn.push_back((c2.v[15] + c2.v[55])*MainFormSLS->hh_1[20]);
/* nn[147] */ nn.push_back((c2.v[16] + c2.v[56])*MainFormSLS->hh_1[32]);
/* nn[148] */ nn.push_back((c2.v[18] + c2.v[58])*MainFormSLS->hh_1[56]);
/* nn[149] */ nn.push_back((c2.v[22] + c2.v[62])*MainFormSLS->hh_1[104]);
/* nn[150] */ nn.push_back((c2.v[24] + c2.v[64])*MainFormSLS->hh_1[128]);
/* nn[151] */ nn.push_back((c2.v[25] + c2.v[65])*MainFormSLS->hh_1[140]);
/* nn[152] */ nn.push_back((c2.v[26] + c2.v[66])*MainFormSLS->hh_1[152]);
/* nn[153] */ nn.push_back((c2.v[28] + c2.v[68])*MainFormSLS->hh_1[16]);
/* nn[154] */ nn.push_back((c2.v[30] + c2.v[70])*MainFormSLS->hh_1[40]);
/* nn[155] */ nn.push_back((c2.v[32] + c2.v[72])*MainFormSLS->hh_1[64]);
/* nn[156] */ nn.push_back((c2.v[34] + c2.v[74])*MainFormSLS->hh_1[88]);
/* nn[157] */ nn.push_back((c2.v[35] + c2.v[75])*MainFormSLS->hh_1[100]);
/* nn[158] */ nn.push_back((c2.v[36] + c2.v[76])*MainFormSLS->hh_1[112]);
/* nn[159] */ nn.push_back((c2.v[38] + c2.v[78])*MainFormSLS->hh_1[136]);
/* nn[160] */ nn.push_back(c2.v[2]*MainFormSLS->hh_1[28]);
/* nn[161] */ nn.push_back(c2.v[4]*MainFormSLS->hh_1[56]);
/* nn[162] */ nn.push_back(c2.v[5]*MainFormSLS->hh_1[70]);
/* nn[163] */ nn.push_back(c2.v[6]*MainFormSLS->hh_1[84]);
/* nn[164] */ nn.push_back(c2.v[8]*MainFormSLS->hh_1[112]);
/* nn[165] */ nn.push_back(c2.v[10]*MainFormSLS->hh_1[140]);
/* nn[166] */ nn.push_back(c2.v[12]*MainFormSLS->hh_1[8]);
/* nn[167] */ nn.push_back(c2.v[14]*MainFormSLS->hh_1[36]);
/* nn[168] */ nn.push_back(c2.v[15]*MainFormSLS->hh_1[50]);
/* nn[169] */ nn.push_back(c2.v[16]*MainFormSLS->hh_1[64]);
/* nn[170] */ nn.push_back(c2.v[18]*MainFormSLS->hh_1[92]);
/* nn[171] */ nn.push_back(c2.v[22]*MainFormSLS->hh_1[148]);
/* nn[172] */ nn.push_back(c2.v[24]*MainFormSLS->hh_1[16]);
/* nn[173] */ nn.push_back(c2.v[25]*MainFormSLS->hh_1[30]);
/* nn[174] */ nn.push_back(c2.v[26]*MainFormSLS->hh_1[44]);
/* nn[175] */ nn.push_back(c2.v[28]*MainFormSLS->hh_1[72]);
/* nn[176] */ nn.push_back(c2.v[30]*MainFormSLS->hh_1[100]);
/* nn[177] */ nn.push_back(c2.v[32]*MainFormSLS->hh_1[128]);
/* nn[178] */ nn.push_back(c2.v[34]*MainFormSLS->hh_1[156]);
/* nn[179] */ nn.push_back(c2.v[35]*MainFormSLS->hh_1[10]);
/* nn[180] */ nn.push_back(c2.v[36]*MainFormSLS->hh_1[24]);
/* nn[181] */ nn.push_back(c2.v[38]*MainFormSLS->hh_1[52]);
/* nn[182] */ nn.push_back(c2.v[42]*MainFormSLS->hh_1[108]);
/* nn[183] */ nn.push_back(c2.v[44]*MainFormSLS->hh_1[136]);
/* nn[184] */ nn.push_back(c2.v[45]*MainFormSLS->hh_1[150]);
/* nn[185] */ nn.push_back(c2.v[46]*MainFormSLS->hh_1[4]);
/* nn[186] */ nn.push_back(c2.v[48]*MainFormSLS->hh_1[32]);
/* nn[187] */ nn.push_back(c2.v[50]*MainFormSLS->hh_1[60]);
/* nn[188] */ nn.push_back(c2.v[52]*MainFormSLS->hh_1[88]);
/* nn[189] */ nn.push_back(c2.v[54]*MainFormSLS->hh_1[116]);
/* nn[190] */ nn.push_back(c2.v[55]*MainFormSLS->hh_1[130]);
/* nn[191] */ nn.push_back(c2.v[56]*MainFormSLS->hh_1[144]);
/* nn[192] */ nn.push_back(c2.v[58]*MainFormSLS->hh_1[12]);
/* nn[193] */ nn.push_back(c2.v[62]*MainFormSLS->hh_1[68]);
/* nn[194] */ nn.push_back(c2.v[64]*MainFormSLS->hh_1[96]);
/* nn[195] */ nn.push_back(c2.v[65]*MainFormSLS->hh_1[110]);
/* nn[196] */ nn.push_back(c2.v[66]*MainFormSLS->hh_1[124]);
/* nn[197] */ nn.push_back(c2.v[68]*MainFormSLS->hh_1[152]);
/* nn[198] */ nn.push_back(c2.v[70]*MainFormSLS->hh_1[20]);
/* nn[199] */ nn.push_back(c2.v[72]*MainFormSLS->hh_1[48]);
/* nn[200] */ nn.push_back(c2.v[74]*MainFormSLS->hh_1[76]);
/* nn[201] */ nn.push_back(c2.v[75]*MainFormSLS->hh_1[90]);
/* nn[202] */ nn.push_back(c2.v[76]*MainFormSLS->hh_1[104]);
/* nn[203] */ nn.push_back(c2.v[78]*MainFormSLS->hh_1[132]);
/* nn[204] */ nn.push_back((c2.v[0] + c2.v[10] + c2.v[20] + c2.v[30] + c2.v[40] + c2.v[50] + c2.v[60] + c2.v[70])*MainFormSLS->hh_1[0]);
/* nn[205] */ nn.push_back((c2.v[5] + c2.v[15] + c2.v[25] + c2.v[35] + c2.v[45] + c2.v[55] + c2.v[65] + c2.v[75])*MainFormSLS->hh_1[80]);
/* nn[206] */ nn.push_back(c2.v[2]*MainFormSLS->hh_1[36]);
/* nn[207] */ nn.push_back(c2.v[4]*MainFormSLS->hh_1[72]);
/* nn[208] */ nn.push_back(c2.v[5]*MainFormSLS->hh_1[90]);
/* nn[209] */ nn.push_back(c2.v[6]*MainFormSLS->hh_1[108]);
/* nn[210] */ nn.push_back(c2.v[8]*MainFormSLS->hh_1[144]);
/* nn[211] */ nn.push_back(c2.v[12]*MainFormSLS->hh_1[56]);
/* nn[212] */ nn.push_back(c2.v[14]*MainFormSLS->hh_1[92]);
/* nn[213] */ nn.push_back(c2.v[15]*MainFormSLS->hh_1[110]);
/* nn[214] */ nn.push_back(c2.v[16]*MainFormSLS->hh_1[128]);
/* nn[215] */ nn.push_back(c2.v[18]*MainFormSLS->hh_1[4]);
/* nn[216] */ nn.push_back(c2.v[22]*MainFormSLS->hh_1[76]);
/* nn[217] */ nn.push_back(c2.v[24]*MainFormSLS->hh_1[112]);
/* nn[218] */ nn.push_back(c2.v[25]*MainFormSLS->hh_1[130]);
/* nn[219] */ nn.push_back(c2.v[26]*MainFormSLS->hh_1[148]);
/* nn[220] */ nn.push_back(c2.v[28]*MainFormSLS->hh_1[24]);
/* nn[221] */ nn.push_back(c2.v[32]*MainFormSLS->hh_1[96]);
/* nn[222] */ nn.push_back(c2.v[34]*MainFormSLS->hh_1[132]);
/* nn[223] */ nn.push_back(c2.v[35]*MainFormSLS->hh_1[150]);
/* nn[224] */ nn.push_back(c2.v[36]*MainFormSLS->hh_1[8]);
/* nn[225] */ nn.push_back(c2.v[38]*MainFormSLS->hh_1[44]);
/* nn[226] */ nn.push_back(c2.v[42]*MainFormSLS->hh_1[116]);
/* nn[227] */ nn.push_back(c2.v[44]*MainFormSLS->hh_1[152]);
/* nn[228] */ nn.push_back(c2.v[45]*MainFormSLS->hh_1[10]);
/* nn[229] */ nn.push_back(c2.v[46]*MainFormSLS->hh_1[28]);
/* nn[230] */ nn.push_back(c2.v[48]*MainFormSLS->hh_1[64]);
/* nn[231] */ nn.push_back(c2.v[52]*MainFormSLS->hh_1[136]);
/* nn[232] */ nn.push_back(c2.v[54]*MainFormSLS->hh_1[12]);
/* nn[233] */ nn.push_back(c2.v[55]*MainFormSLS->hh_1[30]);
/* nn[234] */ nn.push_back(c2.v[56]*MainFormSLS->hh_1[48]);
/* nn[235] */ nn.push_back(c2.v[58]*MainFormSLS->hh_1[84]);
/* nn[236] */ nn.push_back(c2.v[62]*MainFormSLS->hh_1[156]);
/* nn[237] */ nn.push_back(c2.v[64]*MainFormSLS->hh_1[32]);
/* nn[238] */ nn.push_back(c2.v[65]*MainFormSLS->hh_1[50]);
/* nn[239] */ nn.push_back(c2.v[66]*MainFormSLS->hh_1[68]);
/* nn[240] */ nn.push_back(c2.v[68]*MainFormSLS->hh_1[104]);
/* nn[241] */ nn.push_back(c2.v[72]*MainFormSLS->hh_1[16]);
/* nn[242] */ nn.push_back(c2.v[74]*MainFormSLS->hh_1[52]);
/* nn[243] */ nn.push_back(c2.v[75]*MainFormSLS->hh_1[70]);
/* nn[244] */ nn.push_back(c2.v[76]*MainFormSLS->hh_1[88]);
/* nn[245] */ nn.push_back(c2.v[78]*MainFormSLS->hh_1[124]);
/* nn[246] */ nn.push_back((c2.v[0] + c2.v[8] + c2.v[16] + c2.v[24] + c2.v[32] + c2.v[40] + c2.v[48] + c2.v[56] + c2.v[64] + c2.v[72])*MainFormSLS->hh_1[0]);
/* nn[247] */ nn.push_back((c2.v[2] + c2.v[10] + c2.v[18] + c2.v[26] + c2.v[34] + c2.v[42] + c2.v[50] + c2.v[58] + c2.v[66] + c2.v[74])*MainFormSLS->hh_1[40]);
/* nn[248] */ nn.push_back((c2.v[4] + c2.v[12] + c2.v[20] + c2.v[28] + c2.v[36] + c2.v[44] + c2.v[52] + c2.v[60] + c2.v[68] + c2.v[76])*MainFormSLS->hh_1[80]);
/* nn[249] */ nn.push_back((c2.v[6] + c2.v[14] + c2.v[22] + c2.v[30] + c2.v[38] + c2.v[46] + c2.v[54] + c2.v[62] + c2.v[70] + c2.v[78])*MainFormSLS->hh_1[120]);
/* nn[250] */ nn.push_back(c2.v[2]*MainFormSLS->hh_1[44]);
/* nn[251] */ nn.push_back(c2.v[4]*MainFormSLS->hh_1[88]);
/* nn[252] */ nn.push_back(c2.v[5]*MainFormSLS->hh_1[110]);
/* nn[253] */ nn.push_back(c2.v[6]*MainFormSLS->hh_1[132]);
/* nn[254] */ nn.push_back(c2.v[12]*MainFormSLS->hh_1[104]);
/* nn[255] */ nn.push_back(c2.v[14]*MainFormSLS->hh_1[148]);
/* nn[256] */ nn.push_back(c2.v[15]*MainFormSLS->hh_1[10]);
/* nn[257] */ nn.push_back(c2.v[18]*MainFormSLS->hh_1[76]);
/* nn[258] */ nn.push_back(c2.v[22]*MainFormSLS->hh_1[4]);
/* nn[259] */ nn.push_back(c2.v[25]*MainFormSLS->hh_1[70]);
/* nn[260] */ nn.push_back(c2.v[26]*MainFormSLS->hh_1[92]);
/* nn[261] */ nn.push_back(c2.v[28]*MainFormSLS->hh_1[136]);
/* nn[262] */ nn.push_back(c2.v[34]*MainFormSLS->hh_1[108]);
/* nn[263] */ nn.push_back(c2.v[35]*MainFormSLS->hh_1[130]);
/* nn[264] */ nn.push_back(c2.v[36]*MainFormSLS->hh_1[152]);
/* nn[265] */ nn.push_back(c2.v[38]*MainFormSLS->hh_1[36]);
/* nn[266] */ nn.push_back(c2.v[42]*MainFormSLS->hh_1[124]);
/* nn[267] */ nn.push_back(c2.v[44]*MainFormSLS->hh_1[8]);
/* nn[268] */ nn.push_back(c2.v[45]*MainFormSLS->hh_1[30]);
/* nn[269] */ nn.push_back(c2.v[46]*MainFormSLS->hh_1[52]);
/* nn[270] */ nn.push_back(c2.v[52]*MainFormSLS->hh_1[24]);
/* nn[271] */ nn.push_back(c2.v[54]*MainFormSLS->hh_1[68]);
/* nn[272] */ nn.push_back(c2.v[55]*MainFormSLS->hh_1[90]);
/* nn[273] */ nn.push_back(c2.v[58]*MainFormSLS->hh_1[156]);
/* nn[274] */ nn.push_back(c2.v[62]*MainFormSLS->hh_1[84]);
/* nn[275] */ nn.push_back(c2.v[65]*MainFormSLS->hh_1[150]);
/* nn[276] */ nn.push_back(c2.v[66]*MainFormSLS->hh_1[12]);
/* nn[277] */ nn.push_back(c2.v[68]*MainFormSLS->hh_1[56]);
/* nn[278] */ nn.push_back(c2.v[74]*MainFormSLS->hh_1[28]);
/* nn[279] */ nn.push_back(c2.v[75]*MainFormSLS->hh_1[50]);
/* nn[280] */ nn.push_back(c2.v[76]*MainFormSLS->hh_1[72]);
/* nn[281] */ nn.push_back(c2.v[78]*MainFormSLS->hh_1[116]);
/* nn[282] */ nn.push_back((c2.v[2] + c2.v[22] + c2.v[42] + c2.v[62])*MainFormSLS->hh_1[48]);
/* nn[283] */ nn.push_back((c2.v[4] + c2.v[24] + c2.v[44] + c2.v[64])*MainFormSLS->hh_1[96]);
/* nn[284] */ nn.push_back((c2.v[5] + c2.v[25] + c2.v[45] + c2.v[65])*MainFormSLS->hh_1[120]);
/* nn[285] */ nn.push_back((c2.v[6] + c2.v[26] + c2.v[46] + c2.v[66])*MainFormSLS->hh_1[144]);
/* nn[286] */ nn.push_back((c2.v[8] + c2.v[28] + c2.v[48] + c2.v[68])*MainFormSLS->hh_1[32]);
/* nn[287] */ nn.push_back((c2.v[12] + c2.v[32] + c2.v[52] + c2.v[72])*MainFormSLS->hh_1[128]);
/* nn[288] */ nn.push_back((c2.v[14] + c2.v[34] + c2.v[54] + c2.v[74])*MainFormSLS->hh_1[16]);
/* nn[289] */ nn.push_back((c2.v[15] + c2.v[35] + c2.v[55] + c2.v[75])*MainFormSLS->hh_1[40]);
/* nn[290] */ nn.push_back((c2.v[16] + c2.v[36] + c2.v[56] + c2.v[76])*MainFormSLS->hh_1[64]);
/* nn[291] */ nn.push_back((c2.v[18] + c2.v[38] + c2.v[58] + c2.v[78])*MainFormSLS->hh_1[112]);
/* nn[292] */ nn.push_back(c2.v[2]*MainFormSLS->hh_1[52]);
/* nn[293] */ nn.push_back(c2.v[4]*MainFormSLS->hh_1[104]);
/* nn[294] */ nn.push_back(c2.v[5]*MainFormSLS->hh_1[130]);
/* nn[295] */ nn.push_back(c2.v[6]*MainFormSLS->hh_1[156]);
/* nn[296] */ nn.push_back(c2.v[10]*MainFormSLS->hh_1[100]);
/* nn[297] */ nn.push_back(c2.v[12]*MainFormSLS->hh_1[152]);
/* nn[298] */ nn.push_back(c2.v[14]*MainFormSLS->hh_1[44]);
/* nn[299] */ nn.push_back(c2.v[15]*MainFormSLS->hh_1[70]);
/* nn[300] */ nn.push_back(c2.v[18]*MainFormSLS->hh_1[148]);
/* nn[301] */ nn.push_back(c2.v[22]*MainFormSLS->hh_1[92]);
/* nn[302] */ nn.push_back(c2.v[25]*MainFormSLS->hh_1[10]);
/* nn[303] */ nn.push_back(c2.v[26]*MainFormSLS->hh_1[36]);
/* nn[304] */ nn.push_back(c2.v[28]*MainFormSLS->hh_1[88]);
/* nn[305] */ nn.push_back(c2.v[30]*MainFormSLS->hh_1[140]);
/* nn[306] */ nn.push_back(c2.v[34]*MainFormSLS->hh_1[84]);
/* nn[307] */ nn.push_back(c2.v[35]*MainFormSLS->hh_1[110]);
/* nn[308] */ nn.push_back(c2.v[36]*MainFormSLS->hh_1[136]);
/* nn[309] */ nn.push_back(c2.v[38]*MainFormSLS->hh_1[28]);
/* nn[310] */ nn.push_back(c2.v[42]*MainFormSLS->hh_1[132]);
/* nn[311] */ nn.push_back(c2.v[44]*MainFormSLS->hh_1[24]);
/* nn[312] */ nn.push_back(c2.v[45]*MainFormSLS->hh_1[50]);
/* nn[313] */ nn.push_back(c2.v[46]*MainFormSLS->hh_1[76]);
/* nn[314] */ nn.push_back(c2.v[50]*MainFormSLS->hh_1[20]);
/* nn[315] */ nn.push_back(c2.v[52]*MainFormSLS->hh_1[72]);
/* nn[316] */ nn.push_back(c2.v[54]*MainFormSLS->hh_1[124]);
/* nn[317] */ nn.push_back(c2.v[55]*MainFormSLS->hh_1[150]);
/* nn[318] */ nn.push_back(c2.v[58]*MainFormSLS->hh_1[68]);
/* nn[319] */ nn.push_back(c2.v[62]*MainFormSLS->hh_1[12]);
/* nn[320] */ nn.push_back(c2.v[65]*MainFormSLS->hh_1[90]);
/* nn[321] */ nn.push_back(c2.v[66]*MainFormSLS->hh_1[116]);
/* nn[322] */ nn.push_back(c2.v[68]*MainFormSLS->hh_1[8]);
/* nn[323] */ nn.push_back(c2.v[70]*MainFormSLS->hh_1[60]);
/* nn[324] */ nn.push_back(c2.v[74]*MainFormSLS->hh_1[4]);
/* nn[325] */ nn.push_back(c2.v[75]*MainFormSLS->hh_1[30]);
/* nn[326] */ nn.push_back(c2.v[76]*MainFormSLS->hh_1[56]);
/* nn[327] */ nn.push_back(c2.v[78]*MainFormSLS->hh_1[108]);
/* nn[328] */ nn.push_back((c2.v[2] + c2.v[42])*MainFormSLS->hh_1[56]);
/* nn[329] */ nn.push_back((c2.v[4] + c2.v[44])*MainFormSLS->hh_1[112]);
/* nn[330] */ nn.push_back((c2.v[5] + c2.v[45])*MainFormSLS->hh_1[140]);
/* nn[331] */ nn.push_back((c2.v[6] + c2.v[46])*MainFormSLS->hh_1[8]);
/* nn[332] */ nn.push_back((c2.v[8] + c2.v[48])*MainFormSLS->hh_1[64]);
/* nn[333] */ nn.push_back((c2.v[12] + c2.v[52])*MainFormSLS->hh_1[16]);
/* nn[334] */ nn.push_back((c2.v[14] + c2.v[54])*MainFormSLS->hh_1[72]);
/* nn[335] */ nn.push_back((c2.v[15] + c2.v[55])*MainFormSLS->hh_1[100]);
/* nn[336] */ nn.push_back((c2.v[16] + c2.v[56])*MainFormSLS->hh_1[128]);
/* nn[337] */ nn.push_back((c2.v[18] + c2.v[58])*MainFormSLS->hh_1[24]);
/* nn[338] */ nn.push_back((c2.v[22] + c2.v[62])*MainFormSLS->hh_1[136]);
/* nn[339] */ nn.push_back((c2.v[24] + c2.v[64])*MainFormSLS->hh_1[32]);
/* nn[340] */ nn.push_back((c2.v[25] + c2.v[65])*MainFormSLS->hh_1[60]);
/* nn[341] */ nn.push_back((c2.v[26] + c2.v[66])*MainFormSLS->hh_1[88]);
/* nn[342] */ nn.push_back((c2.v[28] + c2.v[68])*MainFormSLS->hh_1[144]);
/* nn[343] */ nn.push_back((c2.v[32] + c2.v[72])*MainFormSLS->hh_1[96]);
/* nn[344] */ nn.push_back((c2.v[34] + c2.v[74])*MainFormSLS->hh_1[152]);
/* nn[345] */ nn.push_back((c2.v[35] + c2.v[75])*MainFormSLS->hh_1[20]);
/* nn[346] */ nn.push_back((c2.v[36] + c2.v[76])*MainFormSLS->hh_1[48]);
/* nn[347] */ nn.push_back((c2.v[38] + c2.v[78])*MainFormSLS->hh_1[104]);
/* nn[348] */ nn.push_back((c2.v[2] + c2.v[18] + c2.v[34] + c2.v[50] + c2.v[66])*MainFormSLS->hh_1[60]);
/* nn[349] */ nn.push_back((c2.v[4] + c2.v[20] + c2.v[36] + c2.v[52] + c2.v[68])*MainFormSLS->hh_1[120]);
/* nn[350] */ nn.push_back((c2.v[6] + c2.v[22] + c2.v[38] + c2.v[54] + c2.v[70])*MainFormSLS->hh_1[20]);
/* nn[351] */ nn.push_back((c2.v[10] + c2.v[26] + c2.v[42] + c2.v[58] + c2.v[74])*MainFormSLS->hh_1[140]);
/* nn[352] */ nn.push_back((c2.v[12] + c2.v[28] + c2.v[44] + c2.v[60] + c2.v[76])*MainFormSLS->hh_1[40]);
/* nn[353] */ nn.push_back((c2.v[14] + c2.v[30] + c2.v[46] + c2.v[62] + c2.v[78])*MainFormSLS->hh_1[100]);
/* nn[354] */ nn.push_back((c2.v[0] + c2.v[5] + c2.v[10] + c2.v[15] + c2.v[20] + c2.v[25] + c2.v[30] + c2.v[35] + c2.v[40] + c2.v[45] + c2.v[50] + c2.v[55] + c2.v[60] + c2.v[65] + c2.v[70] + c2.v[75])*MainFormSLS->hh_1[0]);
/* nn[355] */ nn.push_back(c2.v[2]*MainFormSLS->hh_1[68]);
/* nn[356] */ nn.push_back(c2.v[4]*MainFormSLS->hh_1[136]);
/* nn[357] */ nn.push_back(c2.v[6]*MainFormSLS->hh_1[44]);
/* nn[358] */ nn.push_back(c2.v[12]*MainFormSLS->hh_1[88]);
/* nn[359] */ nn.push_back(c2.v[14]*MainFormSLS->hh_1[156]);
/* nn[360] */ nn.push_back(c2.v[18]*MainFormSLS->hh_1[132]);
/* nn[361] */ nn.push_back(c2.v[22]*MainFormSLS->hh_1[108]);
/* nn[362] */ nn.push_back(c2.v[26]*MainFormSLS->hh_1[84]);
/* nn[363] */ nn.push_back(c2.v[28]*MainFormSLS->hh_1[152]);
/* nn[364] */ nn.push_back(c2.v[34]*MainFormSLS->hh_1[36]);
/* nn[365] */ nn.push_back(c2.v[36]*MainFormSLS->hh_1[104]);
/* nn[366] */ nn.push_back(c2.v[38]*MainFormSLS->hh_1[12]);
/* nn[367] */ nn.push_back(c2.v[42]*MainFormSLS->hh_1[148]);
/* nn[368] */ nn.push_back(c2.v[44]*MainFormSLS->hh_1[56]);
/* nn[369] */ nn.push_back(c2.v[46]*MainFormSLS->hh_1[124]);
/* nn[370] */ nn.push_back(c2.v[52]*MainFormSLS->hh_1[8]);
/* nn[371] */ nn.push_back(c2.v[54]*MainFormSLS->hh_1[76]);
/* nn[372] */ nn.push_back(c2.v[58]*MainFormSLS->hh_1[52]);
/* nn[373] */ nn.push_back(c2.v[62]*MainFormSLS->hh_1[28]);
/* nn[374] */ nn.push_back(c2.v[66]*MainFormSLS->hh_1[4]);
/* nn[375] */ nn.push_back(c2.v[68]*MainFormSLS->hh_1[72]);
/* nn[376] */ nn.push_back(c2.v[74]*MainFormSLS->hh_1[116]);
/* nn[377] */ nn.push_back(c2.v[76]*MainFormSLS->hh_1[24]);
/* nn[378] */ nn.push_back(c2.v[78]*MainFormSLS->hh_1[92]);
/* nn[379] */ nn.push_back((c2.v[2] + c2.v[42])*MainFormSLS->hh_1[72]);
/* nn[380] */ nn.push_back((c2.v[4] + c2.v[44])*MainFormSLS->hh_1[144]);
/* nn[381] */ nn.push_back((c2.v[6] + c2.v[46])*MainFormSLS->hh_1[56]);
/* nn[382] */ nn.push_back((c2.v[8] + c2.v[48])*MainFormSLS->hh_1[128]);
/* nn[383] */ nn.push_back((c2.v[12] + c2.v[52])*MainFormSLS->hh_1[112]);
/* nn[384] */ nn.push_back((c2.v[14] + c2.v[54])*MainFormSLS->hh_1[24]);
/* nn[385] */ nn.push_back((c2.v[16] + c2.v[56])*MainFormSLS->hh_1[96]);
/* nn[386] */ nn.push_back((c2.v[18] + c2.v[58])*MainFormSLS->hh_1[8]);
/* nn[387] */ nn.push_back((c2.v[22] + c2.v[62])*MainFormSLS->hh_1[152]);
/* nn[388] */ nn.push_back((c2.v[24] + c2.v[64])*MainFormSLS->hh_1[64]);
/* nn[389] */ nn.push_back((c2.v[26] + c2.v[66])*MainFormSLS->hh_1[136]);
/* nn[390] */ nn.push_back((c2.v[28] + c2.v[68])*MainFormSLS->hh_1[48]);
/* nn[391] */ nn.push_back((c2.v[32] + c2.v[72])*MainFormSLS->hh_1[32]);
/* nn[392] */ nn.push_back((c2.v[34] + c2.v[74])*MainFormSLS->hh_1[104]);
/* nn[393] */ nn.push_back((c2.v[36] + c2.v[76])*MainFormSLS->hh_1[16]);
/* nn[394] */ nn.push_back((c2.v[38] + c2.v[78])*MainFormSLS->hh_1[88]);
/* nn[395] */ nn.push_back(c2.v[2]*MainFormSLS->hh_1[76]);
/* nn[396] */ nn.push_back(c2.v[4]*MainFormSLS->hh_1[152]);
/* nn[397] */ nn.push_back(c2.v[6]*MainFormSLS->hh_1[68]);
/* nn[398] */ nn.push_back(c2.v[12]*MainFormSLS->hh_1[136]);
/* nn[399] */ nn.push_back(c2.v[14]*MainFormSLS->hh_1[52]);
/* nn[400] */ nn.push_back(c2.v[18]*MainFormSLS->hh_1[44]);
/* nn[401] */ nn.push_back(c2.v[22]*MainFormSLS->hh_1[36]);
/* nn[402] */ nn.push_back(c2.v[26]*MainFormSLS->hh_1[28]);
/* nn[403] */ nn.push_back(c2.v[28]*MainFormSLS->hh_1[104]);
/* nn[404] */ nn.push_back(c2.v[34]*MainFormSLS->hh_1[12]);
/* nn[405] */ nn.push_back(c2.v[36]*MainFormSLS->hh_1[88]);
/* nn[406] */ nn.push_back(c2.v[38]*MainFormSLS->hh_1[4]);
/* nn[407] */ nn.push_back(c2.v[42]*MainFormSLS->hh_1[156]);
/* nn[408] */ nn.push_back(c2.v[44]*MainFormSLS->hh_1[72]);
/* nn[409] */ nn.push_back(c2.v[46]*MainFormSLS->hh_1[148]);
/* nn[410] */ nn.push_back(c2.v[52]*MainFormSLS->hh_1[56]);
/* nn[411] */ nn.push_back(c2.v[54]*MainFormSLS->hh_1[132]);
/* nn[412] */ nn.push_back(c2.v[58]*MainFormSLS->hh_1[124]);
/* nn[413] */ nn.push_back(c2.v[62]*MainFormSLS->hh_1[116]);
/* nn[414] */ nn.push_back(c2.v[66]*MainFormSLS->hh_1[108]);
/* nn[415] */ nn.push_back(c2.v[68]*MainFormSLS->hh_1[24]);
/* nn[416] */ nn.push_back(c2.v[74]*MainFormSLS->hh_1[92]);
/* nn[417] */ nn.push_back(c2.v[76]*MainFormSLS->hh_1[8]);
/* nn[418] */ nn.push_back(c2.v[78]*MainFormSLS->hh_1[84]);
/* nn[419] */ nn.push_back((c2.v[0] + c2.v[4] + c2.v[8] + c2.v[12] + c2.v[16] + c2.v[20] + c2.v[24] + c2.v[28] + c2.v[32] + c2.v[36] + c2.v[40] + c2.v[44] + c2.v[48] + c2.v[52] + c2.v[56] + c2.v[60] + c2.v[64] + c2.v[68] + c2.v[72] + c2.v[76])*MainFormSLS->hh_1[0]);
/* nn[420] */ nn.push_back((c2.v[2] + c2.v[6] + c2.v[10] + c2.v[14] + c2.v[18] + c2.v[22] + c2.v[26] + c2.v[30] + c2.v[34] + c2.v[38] + c2.v[42] + c2.v[46] + c2.v[50] + c2.v[54] + c2.v[58] + c2.v[62] + c2.v[66] + c2.v[70] + c2.v[74] + c2.v[78])*MainFormSLS->hh_1[80]);
/* nn[421] */ nn.push_back(c2.v[2]*MainFormSLS->hh_1[84]);
/* nn[422] */ nn.push_back(c2.v[5]*MainFormSLS->hh_1[50]);
/* nn[423] */ nn.push_back(c2.v[6]*MainFormSLS->hh_1[92]);
/* nn[424] */ nn.push_back(c2.v[14]*MainFormSLS->hh_1[108]);
/* nn[425] */ nn.push_back(c2.v[15]*MainFormSLS->hh_1[150]);
/* nn[426] */ nn.push_back(c2.v[18]*MainFormSLS->hh_1[116]);
/* nn[427] */ nn.push_back(c2.v[22]*MainFormSLS->hh_1[124]);
/* nn[428] */ nn.push_back(c2.v[25]*MainFormSLS->hh_1[90]);
/* nn[429] */ nn.push_back(c2.v[26]*MainFormSLS->hh_1[132]);
/* nn[430] */ nn.push_back(c2.v[34]*MainFormSLS->hh_1[148]);
/* nn[431] */ nn.push_back(c2.v[35]*MainFormSLS->hh_1[30]);
/* nn[432] */ nn.push_back(c2.v[38]*MainFormSLS->hh_1[156]);
/* nn[433] */ nn.push_back(c2.v[42]*MainFormSLS->hh_1[4]);
/* nn[434] */ nn.push_back(c2.v[45]*MainFormSLS->hh_1[130]);
/* nn[435] */ nn.push_back(c2.v[46]*MainFormSLS->hh_1[12]);
/* nn[436] */ nn.push_back(c2.v[54]*MainFormSLS->hh_1[28]);
/* nn[437] */ nn.push_back(c2.v[55]*MainFormSLS->hh_1[70]);
/* nn[438] */ nn.push_back(c2.v[58]*MainFormSLS->hh_1[36]);
/* nn[439] */ nn.push_back(c2.v[62]*MainFormSLS->hh_1[44]);
/* nn[440] */ nn.push_back(c2.v[65]*MainFormSLS->hh_1[10]);
/* nn[441] */ nn.push_back(c2.v[66]*MainFormSLS->hh_1[52]);
/* nn[442] */ nn.push_back(c2.v[74]*MainFormSLS->hh_1[68]);
/* nn[443] */ nn.push_back(c2.v[75]*MainFormSLS->hh_1[110]);
/* nn[444] */ nn.push_back(c2.v[78]*MainFormSLS->hh_1[76]);
/* nn[445] */ nn.push_back((c2.v[2] + c2.v[42])*MainFormSLS->hh_1[88]);
/* nn[446] */ nn.push_back((c2.v[6] + c2.v[46])*MainFormSLS->hh_1[104]);
/* nn[447] */ nn.push_back((c2.v[14] + c2.v[54])*MainFormSLS->hh_1[136]);
/* nn[448] */ nn.push_back((c2.v[18] + c2.v[58])*MainFormSLS->hh_1[152]);
/* nn[449] */ nn.push_back((c2.v[22] + c2.v[62])*MainFormSLS->hh_1[8]);
/* nn[450] */ nn.push_back((c2.v[26] + c2.v[66])*MainFormSLS->hh_1[24]);
/* nn[451] */ nn.push_back((c2.v[34] + c2.v[74])*MainFormSLS->hh_1[56]);
/* nn[452] */ nn.push_back((c2.v[38] + c2.v[78])*MainFormSLS->hh_1[72]);
/* nn[453] */ nn.push_back(c2.v[2]*MainFormSLS->hh_1[92]);
/* nn[454] */ nn.push_back(c2.v[6]*MainFormSLS->hh_1[116]);
/* nn[455] */ nn.push_back(c2.v[14]*MainFormSLS->hh_1[4]);
/* nn[456] */ nn.push_back(c2.v[18]*MainFormSLS->hh_1[28]);
/* nn[457] */ nn.push_back(c2.v[22]*MainFormSLS->hh_1[52]);
/* nn[458] */ nn.push_back(c2.v[26]*MainFormSLS->hh_1[76]);
/* nn[459] */ nn.push_back(c2.v[34]*MainFormSLS->hh_1[124]);
/* nn[460] */ nn.push_back(c2.v[38]*MainFormSLS->hh_1[148]);
/* nn[461] */ nn.push_back(c2.v[42]*MainFormSLS->hh_1[12]);
/* nn[462] */ nn.push_back(c2.v[46]*MainFormSLS->hh_1[36]);
/* nn[463] */ nn.push_back(c2.v[54]*MainFormSLS->hh_1[84]);
/* nn[464] */ nn.push_back(c2.v[58]*MainFormSLS->hh_1[108]);
/* nn[465] */ nn.push_back(c2.v[62]*MainFormSLS->hh_1[132]);
/* nn[466] */ nn.push_back(c2.v[66]*MainFormSLS->hh_1[156]);
/* nn[467] */ nn.push_back(c2.v[74]*MainFormSLS->hh_1[44]);
/* nn[468] */ nn.push_back(c2.v[78]*MainFormSLS->hh_1[68]);
/* nn[469] */ nn.push_back((c2.v[2] + c2.v[18] + c2.v[34] + c2.v[50] + c2.v[66])*MainFormSLS->hh_1[100]);
/* nn[470] */ nn.push_back((c2.v[6] + c2.v[22] + c2.v[38] + c2.v[54] + c2.v[70])*MainFormSLS->hh_1[140]);
/* nn[471] */ nn.push_back((c2.v[10] + c2.v[26] + c2.v[42] + c2.v[58] + c2.v[74])*MainFormSLS->hh_1[20]);
/* nn[472] */ nn.push_back((c2.v[14] + c2.v[30] + c2.v[46] + c2.v[62] + c2.v[78])*MainFormSLS->hh_1[60]);
/* nn[473] */ nn.push_back((c2.v[2] + c2.v[42])*MainFormSLS->hh_1[104]);
/* nn[474] */ nn.push_back((c2.v[5] + c2.v[45])*MainFormSLS->hh_1[100]);
/* nn[475] */ nn.push_back((c2.v[6] + c2.v[46])*MainFormSLS->hh_1[152]);
/* nn[476] */ nn.push_back((c2.v[14] + c2.v[54])*MainFormSLS->hh_1[88]);
/* nn[477] */ nn.push_back((c2.v[15] + c2.v[55])*MainFormSLS->hh_1[140]);
/* nn[478] */ nn.push_back((c2.v[18] + c2.v[58])*MainFormSLS->hh_1[136]);
/* nn[479] */ nn.push_back((c2.v[22] + c2.v[62])*MainFormSLS->hh_1[24]);
/* nn[480] */ nn.push_back((c2.v[25] + c2.v[65])*MainFormSLS->hh_1[20]);
/* nn[481] */ nn.push_back((c2.v[26] + c2.v[66])*MainFormSLS->hh_1[72]);
/* nn[482] */ nn.push_back((c2.v[34] + c2.v[74])*MainFormSLS->hh_1[8]);
/* nn[483] */ nn.push_back((c2.v[35] + c2.v[75])*MainFormSLS->hh_1[60]);
/* nn[484] */ nn.push_back((c2.v[38] + c2.v[78])*MainFormSLS->hh_1[56]);
/* nn[485] */ nn.push_back(c2.v[2]*MainFormSLS->hh_1[108]);
/* nn[486] */ nn.push_back(c2.v[6]*MainFormSLS->hh_1[4]);
/* nn[487] */ nn.push_back(c2.v[14]*MainFormSLS->hh_1[116]);
/* nn[488] */ nn.push_back(c2.v[18]*MainFormSLS->hh_1[12]);
/* nn[489] */ nn.push_back(c2.v[22]*MainFormSLS->hh_1[68]);
/* nn[490] */ nn.push_back(c2.v[26]*MainFormSLS->hh_1[124]);
/* nn[491] */ nn.push_back(c2.v[34]*MainFormSLS->hh_1[76]);
/* nn[492] */ nn.push_back(c2.v[38]*MainFormSLS->hh_1[132]);
/* nn[493] */ nn.push_back(c2.v[42]*MainFormSLS->hh_1[28]);
/* nn[494] */ nn.push_back(c2.v[46]*MainFormSLS->hh_1[84]);
/* nn[495] */ nn.push_back(c2.v[54]*MainFormSLS->hh_1[36]);
/* nn[496] */ nn.push_back(c2.v[58]*MainFormSLS->hh_1[92]);
/* nn[497] */ nn.push_back(c2.v[62]*MainFormSLS->hh_1[148]);
/* nn[498] */ nn.push_back(c2.v[66]*MainFormSLS->hh_1[44]);
/* nn[499] */ nn.push_back(c2.v[74]*MainFormSLS->hh_1[156]);
/* nn[500] */ nn.push_back(c2.v[78]*MainFormSLS->hh_1[52]);
/* nn[501] */ nn.push_back((c2.v[2] + c2.v[22] + c2.v[42] + c2.v[62])*MainFormSLS->hh_1[112]);
/* nn[502] */ nn.push_back((c2.v[4] + c2.v[24] + c2.v[44] + c2.v[64])*MainFormSLS->hh_1[64]);
/* nn[503] */ nn.push_back((c2.v[6] + c2.v[26] + c2.v[46] + c2.v[66])*MainFormSLS->hh_1[16]);
/* nn[504] */ nn.push_back((c2.v[8] + c2.v[28] + c2.v[48] + c2.v[68])*MainFormSLS->hh_1[128]);
/* nn[505] */ nn.push_back((c2.v[12] + c2.v[32] + c2.v[52] + c2.v[72])*MainFormSLS->hh_1[32]);
/* nn[506] */ nn.push_back((c2.v[14] + c2.v[34] + c2.v[54] + c2.v[74])*MainFormSLS->hh_1[144]);
/* nn[507] */ nn.push_back((c2.v[16] + c2.v[36] + c2.v[56] + c2.v[76])*MainFormSLS->hh_1[96]);
/* nn[508] */ nn.push_back((c2.v[18] + c2.v[38] + c2.v[58] + c2.v[78])*MainFormSLS->hh_1[48]);
/* nn[509] */ nn.push_back(c2.v[2]*MainFormSLS->hh_1[116]);
/* nn[510] */ nn.push_back(c2.v[6]*MainFormSLS->hh_1[28]);
/* nn[511] */ nn.push_back(c2.v[14]*MainFormSLS->hh_1[12]);
/* nn[512] */ nn.push_back(c2.v[18]*MainFormSLS->hh_1[84]);
/* nn[513] */ nn.push_back(c2.v[22]*MainFormSLS->hh_1[156]);
/* nn[514] */ nn.push_back(c2.v[26]*MainFormSLS->hh_1[68]);
/* nn[515] */ nn.push_back(c2.v[34]*MainFormSLS->hh_1[52]);
/* nn[516] */ nn.push_back(c2.v[38]*MainFormSLS->hh_1[124]);
/* nn[517] */ nn.push_back(c2.v[42]*MainFormSLS->hh_1[36]);
/* nn[518] */ nn.push_back(c2.v[46]*MainFormSLS->hh_1[108]);
/* nn[519] */ nn.push_back(c2.v[54]*MainFormSLS->hh_1[92]);
/* nn[520] */ nn.push_back(c2.v[58]*MainFormSLS->hh_1[4]);
/* nn[521] */ nn.push_back(c2.v[62]*MainFormSLS->hh_1[76]);
/* nn[522] */ nn.push_back(c2.v[66]*MainFormSLS->hh_1[148]);
/* nn[523] */ nn.push_back(c2.v[74]*MainFormSLS->hh_1[132]);
/* nn[524] */ nn.push_back(c2.v[78]*MainFormSLS->hh_1[44]);
/* nn[525] */ nn.push_back((c2.v[2] + c2.v[10] + c2.v[18] + c2.v[26] + c2.v[34] + c2.v[42] + c2.v[50] + c2.v[58] + c2.v[66] + c2.v[74])*MainFormSLS->hh_1[120]);
/* nn[526] */ nn.push_back((c2.v[6] + c2.v[14] + c2.v[22] + c2.v[30] + c2.v[38] + c2.v[46] + c2.v[54] + c2.v[62] + c2.v[70] + c2.v[78])*MainFormSLS->hh_1[40]);
/* nn[527] */ nn.push_back(c2.v[2]*MainFormSLS->hh_1[124]);
/* nn[528] */ nn.push_back(c2.v[5]*MainFormSLS->hh_1[150]);
/* nn[529] */ nn.push_back(c2.v[6]*MainFormSLS->hh_1[52]);
/* nn[530] */ nn.push_back(c2.v[14]*MainFormSLS->hh_1[68]);
/* nn[531] */ nn.push_back(c2.v[15]*MainFormSLS->hh_1[130]);
/* nn[532] */ nn.push_back(c2.v[18]*MainFormSLS->hh_1[156]);
/* nn[533] */ nn.push_back(c2.v[22]*MainFormSLS->hh_1[84]);
/* nn[534] */ nn.push_back(c2.v[25]*MainFormSLS->hh_1[110]);
/* nn[535] */ nn.push_back(c2.v[26]*MainFormSLS->hh_1[12]);
/* nn[536] */ nn.push_back(c2.v[34]*MainFormSLS->hh_1[28]);
/* nn[537] */ nn.push_back(c2.v[35]*MainFormSLS->hh_1[90]);
/* nn[538] */ nn.push_back(c2.v[38]*MainFormSLS->hh_1[116]);
/* nn[539] */ nn.push_back(c2.v[42]*MainFormSLS->hh_1[44]);
/* nn[540] */ nn.push_back(c2.v[45]*MainFormSLS->hh_1[70]);
/* nn[541] */ nn.push_back(c2.v[46]*MainFormSLS->hh_1[132]);
/* nn[542] */ nn.push_back(c2.v[54]*MainFormSLS->hh_1[148]);
/* nn[543] */ nn.push_back(c2.v[55]*MainFormSLS->hh_1[50]);
/* nn[544] */ nn.push_back(c2.v[58]*MainFormSLS->hh_1[76]);
/* nn[545] */ nn.push_back(c2.v[62]*MainFormSLS->hh_1[4]);
/* nn[546] */ nn.push_back(c2.v[65]*MainFormSLS->hh_1[30]);
/* nn[547] */ nn.push_back(c2.v[66]*MainFormSLS->hh_1[92]);
/* nn[548] */ nn.push_back(c2.v[74]*MainFormSLS->hh_1[108]);
/* nn[549] */ nn.push_back(c2.v[75]*MainFormSLS->hh_1[10]);
/* nn[550] */ nn.push_back(c2.v[78]*MainFormSLS->hh_1[36]);
/* nn[551] */ nn.push_back(c2.v[2]*MainFormSLS->hh_1[132]);
/* nn[552] */ nn.push_back(c2.v[6]*MainFormSLS->hh_1[76]);
/* nn[553] */ nn.push_back(c2.v[14]*MainFormSLS->hh_1[124]);
/* nn[554] */ nn.push_back(c2.v[18]*MainFormSLS->hh_1[68]);
/* nn[555] */ nn.push_back(c2.v[22]*MainFormSLS->hh_1[12]);
/* nn[556] */ nn.push_back(c2.v[26]*MainFormSLS->hh_1[116]);
/* nn[557] */ nn.push_back(c2.v[34]*MainFormSLS->hh_1[4]);
/* nn[558] */ nn.push_back(c2.v[38]*MainFormSLS->hh_1[108]);
/* nn[559] */ nn.push_back(c2.v[42]*MainFormSLS->hh_1[52]);
/* nn[560] */ nn.push_back(c2.v[46]*MainFormSLS->hh_1[156]);
/* nn[561] */ nn.push_back(c2.v[54]*MainFormSLS->hh_1[44]);
/* nn[562] */ nn.push_back(c2.v[58]*MainFormSLS->hh_1[148]);
/* nn[563] */ nn.push_back(c2.v[62]*MainFormSLS->hh_1[92]);
/* nn[564] */ nn.push_back(c2.v[66]*MainFormSLS->hh_1[36]);
/* nn[565] */ nn.push_back(c2.v[74]*MainFormSLS->hh_1[84]);
/* nn[566] */ nn.push_back(c2.v[78]*MainFormSLS->hh_1[28]);
/* nn[567] */ nn.push_back((c2.v[2] + c2.v[42])*MainFormSLS->hh_1[136]);
/* nn[568] */ nn.push_back((c2.v[6] + c2.v[46])*MainFormSLS->hh_1[88]);
/* nn[569] */ nn.push_back((c2.v[14] + c2.v[54])*MainFormSLS->hh_1[152]);
/* nn[570] */ nn.push_back((c2.v[18] + c2.v[58])*MainFormSLS->hh_1[104]);
/* nn[571] */ nn.push_back((c2.v[22] + c2.v[62])*MainFormSLS->hh_1[56]);
/* nn[572] */ nn.push_back((c2.v[26] + c2.v[66])*MainFormSLS->hh_1[8]);
/* nn[573] */ nn.push_back((c2.v[34] + c2.v[74])*MainFormSLS->hh_1[72]);
/* nn[574] */ nn.push_back((c2.v[38] + c2.v[78])*MainFormSLS->hh_1[24]);
/* nn[575] */ nn.push_back((c2.v[2] + c2.v[18] + c2.v[34] + c2.v[50] + c2.v[66])*MainFormSLS->hh_1[140]);
/* nn[576] */ nn.push_back((c2.v[6] + c2.v[22] + c2.v[38] + c2.v[54] + c2.v[70])*MainFormSLS->hh_1[100]);
/* nn[577] */ nn.push_back((c2.v[10] + c2.v[26] + c2.v[42] + c2.v[58] + c2.v[74])*MainFormSLS->hh_1[60]);
/* nn[578] */ nn.push_back((c2.v[14] + c2.v[30] + c2.v[46] + c2.v[62] + c2.v[78])*MainFormSLS->hh_1[20]);
/* nn[579] */ nn.push_back((c2.v[2] + c2.v[22] + c2.v[42] + c2.v[62])*MainFormSLS->hh_1[144]);
/* nn[580] */ nn.push_back((c2.v[4] + c2.v[24] + c2.v[44] + c2.v[64])*MainFormSLS->hh_1[128]);
/* nn[581] */ nn.push_back((c2.v[6] + c2.v[26] + c2.v[46] + c2.v[66])*MainFormSLS->hh_1[112]);
/* nn[582] */ nn.push_back((c2.v[8] + c2.v[28] + c2.v[48] + c2.v[68])*MainFormSLS->hh_1[96]);
/* nn[583] */ nn.push_back((c2.v[12] + c2.v[32] + c2.v[52] + c2.v[72])*MainFormSLS->hh_1[64]);
/* nn[584] */ nn.push_back((c2.v[14] + c2.v[34] + c2.v[54] + c2.v[74])*MainFormSLS->hh_1[48]);
/* nn[585] */ nn.push_back((c2.v[16] + c2.v[36] + c2.v[56] + c2.v[76])*MainFormSLS->hh_1[32]);
/* nn[586] */ nn.push_back((c2.v[18] + c2.v[38] + c2.v[58] + c2.v[78])*MainFormSLS->hh_1[16]);
/* nn[587] */ nn.push_back(c2.v[2]*MainFormSLS->hh_1[148]);
/* nn[588] */ nn.push_back(c2.v[6]*MainFormSLS->hh_1[124]);
/* nn[589] */ nn.push_back(c2.v[14]*MainFormSLS->hh_1[76]);
/* nn[590] */ nn.push_back(c2.v[18]*MainFormSLS->hh_1[52]);
/* nn[591] */ nn.push_back(c2.v[22]*MainFormSLS->hh_1[28]);
/* nn[592] */ nn.push_back(c2.v[26]*MainFormSLS->hh_1[4]);
/* nn[593] */ nn.push_back(c2.v[34]*MainFormSLS->hh_1[116]);
/* nn[594] */ nn.push_back(c2.v[38]*MainFormSLS->hh_1[92]);
/* nn[595] */ nn.push_back(c2.v[42]*MainFormSLS->hh_1[68]);
/* nn[596] */ nn.push_back(c2.v[46]*MainFormSLS->hh_1[44]);
/* nn[597] */ nn.push_back(c2.v[54]*MainFormSLS->hh_1[156]);
/* nn[598] */ nn.push_back(c2.v[58]*MainFormSLS->hh_1[132]);
/* nn[599] */ nn.push_back(c2.v[62]*MainFormSLS->hh_1[108]);
/* nn[600] */ nn.push_back(c2.v[66]*MainFormSLS->hh_1[84]);
/* nn[601] */ nn.push_back(c2.v[74]*MainFormSLS->hh_1[36]);
/* nn[602] */ nn.push_back(c2.v[78]*MainFormSLS->hh_1[12]);
/* nn[603] */ nn.push_back((c2.v[2] + c2.v[42])*MainFormSLS->hh_1[152]);
/* nn[604] */ nn.push_back((c2.v[6] + c2.v[46])*MainFormSLS->hh_1[136]);
/* nn[605] */ nn.push_back((c2.v[14] + c2.v[54])*MainFormSLS->hh_1[104]);
/* nn[606] */ nn.push_back((c2.v[18] + c2.v[58])*MainFormSLS->hh_1[88]);
/* nn[607] */ nn.push_back((c2.v[22] + c2.v[62])*MainFormSLS->hh_1[72]);
/* nn[608] */ nn.push_back((c2.v[26] + c2.v[66])*MainFormSLS->hh_1[56]);
/* nn[609] */ nn.push_back((c2.v[34] + c2.v[74])*MainFormSLS->hh_1[24]);
/* nn[610] */ nn.push_back((c2.v[38] + c2.v[78])*MainFormSLS->hh_1[8]);
/* nn[611] */ nn.push_back(c2.v[2]*MainFormSLS->hh_1[156]);
/* nn[612] */ nn.push_back(c2.v[6]*MainFormSLS->hh_1[148]);
/* nn[613] */ nn.push_back(c2.v[14]*MainFormSLS->hh_1[132]);
/* nn[614] */ nn.push_back(c2.v[18]*MainFormSLS->hh_1[124]);
/* nn[615] */ nn.push_back(c2.v[22]*MainFormSLS->hh_1[116]);
/* nn[616] */ nn.push_back(c2.v[26]*MainFormSLS->hh_1[108]);
/* nn[617] */ nn.push_back(c2.v[34]*MainFormSLS->hh_1[92]);
/* nn[618] */ nn.push_back(c2.v[38]*MainFormSLS->hh_1[84]);
/* nn[619] */ nn.push_back(c2.v[42]*MainFormSLS->hh_1[76]);
/* nn[620] */ nn.push_back(c2.v[46]*MainFormSLS->hh_1[68]);
/* nn[621] */ nn.push_back(c2.v[54]*MainFormSLS->hh_1[52]);
/* nn[622] */ nn.push_back(c2.v[58]*MainFormSLS->hh_1[44]);
/* nn[623] */ nn.push_back(c2.v[62]*MainFormSLS->hh_1[36]);
/* nn[624] */ nn.push_back(c2.v[66]*MainFormSLS->hh_1[28]);
/* nn[625] */ nn.push_back(c2.v[74]*MainFormSLS->hh_1[12]);
/* nn[626] */ nn.push_back(c2.v[78]*MainFormSLS->hh_1[4]);

//отсчет 0
s= (c2.v[0] + c2.v[1] + c2.v[2] + c2.v[3] + c2.v[4] + c2.v[5] + c2.v[6] + c2.v[7] + c2.v[8] + c2.v[9] + c2.v[10] + c2.v[11] + c2.v[12] + c2.v[13] + c2.v[14] + c2.v[15] + c2.v[16] + c2.v[17] + c2.v[18] + c2.v[19] + c2.v[20] + c2.v[21] + c2.v[22] + c2.v[23] + c2.v[24] + c2.v[25] + c2.v[26] + c2.v[27] + c2.v[28] + c2.v[29] + c2.v[30] + c2.v[31] + c2.v[32] + c2.v[33] + c2.v[34] + c2.v[35] + c2.v[36] + c2.v[37] + c2.v[38] + c2.v[39]
 + c2.v[40] + c2.v[41] + c2.v[42] + c2.v[43] + c2.v[44] + c2.v[45] + c2.v[46] + c2.v[47] + c2.v[48] + c2.v[49] + c2.v[50] + c2.v[51] + c2.v[52] + c2.v[53] + c2.v[54] + c2.v[55] + c2.v[56] + c2.v[57] + c2.v[58] + c2.v[59] + c2.v[60] + c2.v[61] + c2.v[62] + c2.v[63] + c2.v[64] + c2.v[65] + c2.v[66] + c2.v[67] + c2.v[68] + c2.v[69] + c2.v[70] + c2.v[71] + c2.v[72] + c2.v[73] + c2.v[74] + c2.v[75] + c2.v[76] + c2.v[77] + c2.v[78] + c2.v[79])*MainFormSLS->hh_1[0];
s/=N_2;
out.push_back(s);

//отсчет 1
s= nn[0]
 + c2.v[1]*MainFormSLS->hh_1[2]
 + nn[1]
 + c2.v[3]*MainFormSLS->hh_1[6]
 + nn[2]
 + nn[3]
 + nn[4]
 + c2.v[7]*MainFormSLS->hh_1[14]
 + nn[5]
 + c2.v[9]*MainFormSLS->hh_1[18]
 + nn[6]
 + c2.v[11]*MainFormSLS->hh_1[22]
 + nn[7]
 + c2.v[13]*MainFormSLS->hh_1[26]
 + nn[8]
 + nn[9]
 + nn[10]
 + c2.v[17]*MainFormSLS->hh_1[34]
 + nn[11]
 + c2.v[19]*MainFormSLS->hh_1[38]
 + nn[12]
 + c2.v[21]*MainFormSLS->hh_1[42]
 + nn[13]
 + c2.v[23]*MainFormSLS->hh_1[46]
 + nn[14]
 + nn[15]
 + nn[16]
 + c2.v[27]*MainFormSLS->hh_1[54]
 + nn[17]
 + c2.v[29]*MainFormSLS->hh_1[58]
 + nn[18]
 + c2.v[31]*MainFormSLS->hh_1[62]
 + nn[19]
 + c2.v[33]*MainFormSLS->hh_1[66]
 + nn[20]
 + nn[21]
 + nn[22]
 + c2.v[37]*MainFormSLS->hh_1[74]
 + nn[23]
 + c2.v[39]*MainFormSLS->hh_1[78]
 + nn[24]
 + c2.v[41]*MainFormSLS->hh_1[82]
 + nn[25]
 + c2.v[43]*MainFormSLS->hh_1[86]
 + nn[26]
 + nn[27]
 + nn[28]
 + c2.v[47]*MainFormSLS->hh_1[94]
 + nn[29]
 + c2.v[49]*MainFormSLS->hh_1[98]
 + nn[30]
 + c2.v[51]*MainFormSLS->hh_1[102]
 + nn[31]
 + c2.v[53]*MainFormSLS->hh_1[106]
 + nn[32]
 + nn[33]
 + nn[34]
 + c2.v[57]*MainFormSLS->hh_1[114]
 + nn[35]
 + c2.v[59]*MainFormSLS->hh_1[118]
 + nn[36]
 + c2.v[61]*MainFormSLS->hh_1[122]
 + nn[37]
 + c2.v[63]*MainFormSLS->hh_1[126]
 + nn[38]
 + nn[39]
 + nn[40]
 + c2.v[67]*MainFormSLS->hh_1[134]
 + nn[41]
 + c2.v[69]*MainFormSLS->hh_1[138]
 + nn[42]
 + c2.v[71]*MainFormSLS->hh_1[142]
 + nn[43]
 + c2.v[73]*MainFormSLS->hh_1[146]
 + nn[44]
 + nn[45]
 + nn[46]
 + c2.v[77]*MainFormSLS->hh_1[154]
 + nn[47]
 + c2.v[79]*MainFormSLS->hh_1[158];
s/=N_2;
out.push_back(s);

//отсчет 2
s= nn[48]
 + (c2.v[1] + c2.v[41])*MainFormSLS->hh_1[4]
 + nn[49]
 + (c2.v[3] + c2.v[43])*MainFormSLS->hh_1[12]
 + nn[50]
 + nn[51]
 + nn[52]
 + (c2.v[7] + c2.v[47])*MainFormSLS->hh_1[28]
 + nn[53]
 + (c2.v[9] + c2.v[49])*MainFormSLS->hh_1[36]
 + nn[54]
 + (c2.v[11] + c2.v[51])*MainFormSLS->hh_1[44]
 + nn[55]
 + (c2.v[13] + c2.v[53])*MainFormSLS->hh_1[52]
 + nn[56]
 + nn[57]
 + nn[58]
 + (c2.v[17] + c2.v[57])*MainFormSLS->hh_1[68]
 + nn[59]
 + (c2.v[19] + c2.v[59])*MainFormSLS->hh_1[76]
 + nn[60]
 + (c2.v[21] + c2.v[61])*MainFormSLS->hh_1[84]
 + nn[61]
 + (c2.v[23] + c2.v[63])*MainFormSLS->hh_1[92]
 + nn[62]
 + nn[63]
 + nn[64]
 + (c2.v[27] + c2.v[67])*MainFormSLS->hh_1[108]
 + nn[65]
 + (c2.v[29] + c2.v[69])*MainFormSLS->hh_1[116]
 + nn[66]
 + (c2.v[31] + c2.v[71])*MainFormSLS->hh_1[124]
 + nn[67]
 + (c2.v[33] + c2.v[73])*MainFormSLS->hh_1[132]
 + nn[68]
 + nn[69]
 + nn[70]
 + (c2.v[37] + c2.v[77])*MainFormSLS->hh_1[148]
 + nn[71]
 + (c2.v[39] + c2.v[79])*MainFormSLS->hh_1[156];
s/=N_2;
out.push_back(s);

//отсчет 3
s= nn[0]
 + c2.v[1]*MainFormSLS->hh_1[6]
 + nn[72]
 + c2.v[3]*MainFormSLS->hh_1[18]
 + nn[73]
 + nn[74]
 + nn[75]
 + c2.v[7]*MainFormSLS->hh_1[42]
 + nn[76]
 + c2.v[9]*MainFormSLS->hh_1[54]
 + nn[77]
 + c2.v[11]*MainFormSLS->hh_1[66]
 + nn[78]
 + c2.v[13]*MainFormSLS->hh_1[78]
 + nn[79]
 + nn[80]
 + nn[81]
 + c2.v[17]*MainFormSLS->hh_1[102]
 + nn[82]
 + c2.v[19]*MainFormSLS->hh_1[114]
 + nn[83]
 + c2.v[21]*MainFormSLS->hh_1[126]
 + nn[84]
 + c2.v[23]*MainFormSLS->hh_1[138]
 + nn[85]
 + nn[86]
 + nn[87]
 + c2.v[27]*MainFormSLS->hh_1[2]
 + nn[88]
 + c2.v[29]*MainFormSLS->hh_1[14]
 + nn[89]
 + c2.v[31]*MainFormSLS->hh_1[26]
 + nn[90]
 + c2.v[33]*MainFormSLS->hh_1[38]
 + nn[91]
 + nn[92]
 + nn[93]
 + c2.v[37]*MainFormSLS->hh_1[62]
 + nn[94]
 + c2.v[39]*MainFormSLS->hh_1[74]
 + nn[24]
 + c2.v[41]*MainFormSLS->hh_1[86]
 + nn[95]
 + c2.v[43]*MainFormSLS->hh_1[98]
 + nn[96]
 + nn[97]
 + nn[98]
 + c2.v[47]*MainFormSLS->hh_1[122]
 + nn[99]
 + c2.v[49]*MainFormSLS->hh_1[134]
 + nn[100]
 + c2.v[51]*MainFormSLS->hh_1[146]
 + nn[101]
 + c2.v[53]*MainFormSLS->hh_1[158]
 + nn[102]
 + nn[103]
 + nn[104]
 + c2.v[57]*MainFormSLS->hh_1[22]
 + nn[105]
 + c2.v[59]*MainFormSLS->hh_1[34]
 + nn[106]
 + c2.v[61]*MainFormSLS->hh_1[46]
 + nn[107]
 + c2.v[63]*MainFormSLS->hh_1[58]
 + nn[108]
 + nn[109]
 + nn[110]
 + c2.v[67]*MainFormSLS->hh_1[82]
 + nn[111]
 + c2.v[69]*MainFormSLS->hh_1[94]
 + nn[112]
 + c2.v[71]*MainFormSLS->hh_1[106]
 + nn[113]
 + c2.v[73]*MainFormSLS->hh_1[118]
 + nn[114]
 + nn[115]
 + nn[116]
 + c2.v[77]*MainFormSLS->hh_1[142]
 + nn[117]
 + c2.v[79]*MainFormSLS->hh_1[154];
s/=N_2;
out.push_back(s);

//отсчет 4
s= nn[118]
 + (c2.v[1] + c2.v[21] + c2.v[41] + c2.v[61])*MainFormSLS->hh_1[8]
 + nn[119]
 + (c2.v[3] + c2.v[23] + c2.v[43] + c2.v[63])*MainFormSLS->hh_1[24]
 + nn[120]
 + nn[121]
 + nn[122]
 + (c2.v[7] + c2.v[27] + c2.v[47] + c2.v[67])*MainFormSLS->hh_1[56]
 + nn[123]
 + (c2.v[9] + c2.v[29] + c2.v[49] + c2.v[69])*MainFormSLS->hh_1[72]
 + nn[124]
 + (c2.v[11] + c2.v[31] + c2.v[51] + c2.v[71])*MainFormSLS->hh_1[88]
 + nn[125]
 + (c2.v[13] + c2.v[33] + c2.v[53] + c2.v[73])*MainFormSLS->hh_1[104]
 + nn[126]
 + nn[127]
 + nn[128]
 + (c2.v[17] + c2.v[37] + c2.v[57] + c2.v[77])*MainFormSLS->hh_1[136]
 + nn[129]
 + (c2.v[19] + c2.v[39] + c2.v[59] + c2.v[79])*MainFormSLS->hh_1[152];
s/=N_2;
out.push_back(s);

//отсчет 5
s= nn[130]
 + (c2.v[1] + c2.v[17] + c2.v[33] + c2.v[49] + c2.v[65])*MainFormSLS->hh_1[10]
 + nn[131]
 + (c2.v[3] + c2.v[19] + c2.v[35] + c2.v[51] + c2.v[67])*MainFormSLS->hh_1[30]
 + nn[132]
 + (c2.v[5] + c2.v[21] + c2.v[37] + c2.v[53] + c2.v[69])*MainFormSLS->hh_1[50]
 + nn[133]
 + (c2.v[7] + c2.v[23] + c2.v[39] + c2.v[55] + c2.v[71])*MainFormSLS->hh_1[70]
 + nn[134]
 + (c2.v[9] + c2.v[25] + c2.v[41] + c2.v[57] + c2.v[73])*MainFormSLS->hh_1[90]
 + nn[135]
 + (c2.v[11] + c2.v[27] + c2.v[43] + c2.v[59] + c2.v[75])*MainFormSLS->hh_1[110]
 + nn[136]
 + (c2.v[13] + c2.v[29] + c2.v[45] + c2.v[61] + c2.v[77])*MainFormSLS->hh_1[130]
 + nn[137]
 + (c2.v[15] + c2.v[31] + c2.v[47] + c2.v[63] + c2.v[79])*MainFormSLS->hh_1[150];
s/=N_2;
out.push_back(s);

//отсчет 6
s= nn[48]
 + (c2.v[1] + c2.v[41])*MainFormSLS->hh_1[12]
 + nn[138]
 + (c2.v[3] + c2.v[43])*MainFormSLS->hh_1[36]
 + nn[139]
 + nn[140]
 + nn[141]
 + (c2.v[7] + c2.v[47])*MainFormSLS->hh_1[84]
 + nn[142]
 + (c2.v[9] + c2.v[49])*MainFormSLS->hh_1[108]
 + nn[143]
 + (c2.v[11] + c2.v[51])*MainFormSLS->hh_1[132]
 + nn[144]
 + (c2.v[13] + c2.v[53])*MainFormSLS->hh_1[156]
 + nn[145]
 + nn[146]
 + nn[147]
 + (c2.v[17] + c2.v[57])*MainFormSLS->hh_1[44]
 + nn[148]
 + (c2.v[19] + c2.v[59])*MainFormSLS->hh_1[68]
 + nn[60]
 + (c2.v[21] + c2.v[61])*MainFormSLS->hh_1[92]
 + nn[149]
 + (c2.v[23] + c2.v[63])*MainFormSLS->hh_1[116]
 + nn[150]
 + nn[151]
 + nn[152]
 + (c2.v[27] + c2.v[67])*MainFormSLS->hh_1[4]
 + nn[153]
 + (c2.v[29] + c2.v[69])*MainFormSLS->hh_1[28]
 + nn[154]
 + (c2.v[31] + c2.v[71])*MainFormSLS->hh_1[52]
 + nn[155]
 + (c2.v[33] + c2.v[73])*MainFormSLS->hh_1[76]
 + nn[156]
 + nn[157]
 + nn[158]
 + (c2.v[37] + c2.v[77])*MainFormSLS->hh_1[124]
 + nn[159]
 + (c2.v[39] + c2.v[79])*MainFormSLS->hh_1[148];
s/=N_2;
out.push_back(s);

//отсчет 7
s= nn[0]
 + c2.v[1]*MainFormSLS->hh_1[14]
 + nn[160]
 + c2.v[3]*MainFormSLS->hh_1[42]
 + nn[161]
 + nn[162]
 + nn[163]
 + c2.v[7]*MainFormSLS->hh_1[98]
 + nn[164]
 + c2.v[9]*MainFormSLS->hh_1[126]
 + nn[165]
 + c2.v[11]*MainFormSLS->hh_1[154]
 + nn[166]
 + c2.v[13]*MainFormSLS->hh_1[22]
 + nn[167]
 + nn[168]
 + nn[169]
 + c2.v[17]*MainFormSLS->hh_1[78]
 + nn[170]
 + c2.v[19]*MainFormSLS->hh_1[106]
 + nn[83]
 + c2.v[21]*MainFormSLS->hh_1[134]
 + nn[171]
 + c2.v[23]*MainFormSLS->hh_1[2]
 + nn[172]
 + nn[173]
 + nn[174]
 + c2.v[27]*MainFormSLS->hh_1[58]
 + nn[175]
 + c2.v[29]*MainFormSLS->hh_1[86]
 + nn[176]
 + c2.v[31]*MainFormSLS->hh_1[114]
 + nn[177]
 + c2.v[33]*MainFormSLS->hh_1[142]
 + nn[178]
 + nn[179]
 + nn[180]
 + c2.v[37]*MainFormSLS->hh_1[38]
 + nn[181]
 + c2.v[39]*MainFormSLS->hh_1[66]
 + nn[24]
 + c2.v[41]*MainFormSLS->hh_1[94]
 + nn[182]
 + c2.v[43]*MainFormSLS->hh_1[122]
 + nn[183]
 + nn[184]
 + nn[185]
 + c2.v[47]*MainFormSLS->hh_1[18]
 + nn[186]
 + c2.v[49]*MainFormSLS->hh_1[46]
 + nn[187]
 + c2.v[51]*MainFormSLS->hh_1[74]
 + nn[188]
 + c2.v[53]*MainFormSLS->hh_1[102]
 + nn[189]
 + nn[190]
 + nn[191]
 + c2.v[57]*MainFormSLS->hh_1[158]
 + nn[192]
 + c2.v[59]*MainFormSLS->hh_1[26]
 + nn[106]
 + c2.v[61]*MainFormSLS->hh_1[54]
 + nn[193]
 + c2.v[63]*MainFormSLS->hh_1[82]
 + nn[194]
 + nn[195]
 + nn[196]
 + c2.v[67]*MainFormSLS->hh_1[138]
 + nn[197]
 + c2.v[69]*MainFormSLS->hh_1[6]
 + nn[198]
 + c2.v[71]*MainFormSLS->hh_1[34]
 + nn[199]
 + c2.v[73]*MainFormSLS->hh_1[62]
 + nn[200]
 + nn[201]
 + nn[202]
 + c2.v[77]*MainFormSLS->hh_1[118]
 + nn[203]
 + c2.v[79]*MainFormSLS->hh_1[146];
s/=N_2;
out.push_back(s);

//отсчет 8
s= nn[204]
 + (c2.v[1] + c2.v[11] + c2.v[21] + c2.v[31] + c2.v[41] + c2.v[51] + c2.v[61] + c2.v[71])*MainFormSLS->hh_1[16]
 + (c2.v[2] + c2.v[12] + c2.v[22] + c2.v[32] + c2.v[42] + c2.v[52] + c2.v[62] + c2.v[72])*MainFormSLS->hh_1[32]
 + (c2.v[3] + c2.v[13] + c2.v[23] + c2.v[33] + c2.v[43] + c2.v[53] + c2.v[63] + c2.v[73])*MainFormSLS->hh_1[48]
 + (c2.v[4] + c2.v[14] + c2.v[24] + c2.v[34] + c2.v[44] + c2.v[54] + c2.v[64] + c2.v[74])*MainFormSLS->hh_1[64]
 + nn[205]
 + (c2.v[6] + c2.v[16] + c2.v[26] + c2.v[36] + c2.v[46] + c2.v[56] + c2.v[66] + c2.v[76])*MainFormSLS->hh_1[96]
 + (c2.v[7] + c2.v[17] + c2.v[27] + c2.v[37] + c2.v[47] + c2.v[57] + c2.v[67] + c2.v[77])*MainFormSLS->hh_1[112]
 + (c2.v[8] + c2.v[18] + c2.v[28] + c2.v[38] + c2.v[48] + c2.v[58] + c2.v[68] + c2.v[78])*MainFormSLS->hh_1[128]
 + (c2.v[9] + c2.v[19] + c2.v[29] + c2.v[39] + c2.v[49] + c2.v[59] + c2.v[69] + c2.v[79])*MainFormSLS->hh_1[144];
s/=N_2;
out.push_back(s);

//отсчет 9
s= nn[0]
 + c2.v[1]*MainFormSLS->hh_1[18]
 + nn[206]
 + c2.v[3]*MainFormSLS->hh_1[54]
 + nn[207]
 + nn[208]
 + nn[209]
 + c2.v[7]*MainFormSLS->hh_1[126]
 + nn[210]
 + c2.v[9]*MainFormSLS->hh_1[2]
 + nn[6]
 + c2.v[11]*MainFormSLS->hh_1[38]
 + nn[211]
 + c2.v[13]*MainFormSLS->hh_1[74]
 + nn[212]
 + nn[213]
 + nn[214]
 + c2.v[17]*MainFormSLS->hh_1[146]
 + nn[215]
 + c2.v[19]*MainFormSLS->hh_1[22]
 + nn[12]
 + c2.v[21]*MainFormSLS->hh_1[58]
 + nn[216]
 + c2.v[23]*MainFormSLS->hh_1[94]
 + nn[217]
 + nn[218]
 + nn[219]
 + c2.v[27]*MainFormSLS->hh_1[6]
 + nn[220]
 + c2.v[29]*MainFormSLS->hh_1[42]
 + nn[18]
 + c2.v[31]*MainFormSLS->hh_1[78]
 + nn[221]
 + c2.v[33]*MainFormSLS->hh_1[114]
 + nn[222]
 + nn[223]
 + nn[224]
 + c2.v[37]*MainFormSLS->hh_1[26]
 + nn[225]
 + c2.v[39]*MainFormSLS->hh_1[62]
 + nn[24]
 + c2.v[41]*MainFormSLS->hh_1[98]
 + nn[226]
 + c2.v[43]*MainFormSLS->hh_1[134]
 + nn[227]
 + nn[228]
 + nn[229]
 + c2.v[47]*MainFormSLS->hh_1[46]
 + nn[230]
 + c2.v[49]*MainFormSLS->hh_1[82]
 + nn[30]
 + c2.v[51]*MainFormSLS->hh_1[118]
 + nn[231]
 + c2.v[53]*MainFormSLS->hh_1[154]
 + nn[232]
 + nn[233]
 + nn[234]
 + c2.v[57]*MainFormSLS->hh_1[66]
 + nn[235]
 + c2.v[59]*MainFormSLS->hh_1[102]
 + nn[36]
 + c2.v[61]*MainFormSLS->hh_1[138]
 + nn[236]
 + c2.v[63]*MainFormSLS->hh_1[14]
 + nn[237]
 + nn[238]
 + nn[239]
 + c2.v[67]*MainFormSLS->hh_1[86]
 + nn[240]
 + c2.v[69]*MainFormSLS->hh_1[122]
 + nn[42]
 + c2.v[71]*MainFormSLS->hh_1[158]
 + nn[241]
 + c2.v[73]*MainFormSLS->hh_1[34]
 + nn[242]
 + nn[243]
 + nn[244]
 + c2.v[77]*MainFormSLS->hh_1[106]
 + nn[245]
 + c2.v[79]*MainFormSLS->hh_1[142];
s/=N_2;
out.push_back(s);

//отсчет 10
s= nn[246]
 + (c2.v[1] + c2.v[9] + c2.v[17] + c2.v[25] + c2.v[33] + c2.v[41] + c2.v[49] + c2.v[57] + c2.v[65] + c2.v[73])*MainFormSLS->hh_1[20]
 + nn[247]
 + (c2.v[3] + c2.v[11] + c2.v[19] + c2.v[27] + c2.v[35] + c2.v[43] + c2.v[51] + c2.v[59] + c2.v[67] + c2.v[75])*MainFormSLS->hh_1[60]
 + nn[248]
 + (c2.v[5] + c2.v[13] + c2.v[21] + c2.v[29] + c2.v[37] + c2.v[45] + c2.v[53] + c2.v[61] + c2.v[69] + c2.v[77])*MainFormSLS->hh_1[100]
 + nn[249]
 + (c2.v[7] + c2.v[15] + c2.v[23] + c2.v[31] + c2.v[39] + c2.v[47] + c2.v[55] + c2.v[63] + c2.v[71] + c2.v[79])*MainFormSLS->hh_1[140];
s/=N_2;
out.push_back(s);

//отсчет 11
s= nn[0]
 + c2.v[1]*MainFormSLS->hh_1[22]
 + nn[250]
 + c2.v[3]*MainFormSLS->hh_1[66]
 + nn[251]
 + nn[252]
 + nn[253]
 + c2.v[7]*MainFormSLS->hh_1[154]
 + nn[5]
 + c2.v[9]*MainFormSLS->hh_1[38]
 + nn[77]
 + c2.v[11]*MainFormSLS->hh_1[82]
 + nn[254]
 + c2.v[13]*MainFormSLS->hh_1[126]
 + nn[255]
 + nn[256]
 + nn[10]
 + c2.v[17]*MainFormSLS->hh_1[54]
 + nn[257]
 + c2.v[19]*MainFormSLS->hh_1[98]
 + nn[83]
 + c2.v[21]*MainFormSLS->hh_1[142]
 + nn[258]
 + c2.v[23]*MainFormSLS->hh_1[26]
 + nn[14]
 + nn[259]
 + nn[260]
 + c2.v[27]*MainFormSLS->hh_1[114]
 + nn[261]
 + c2.v[29]*MainFormSLS->hh_1[158]
 + nn[89]
 + c2.v[31]*MainFormSLS->hh_1[42]
 + nn[19]
 + c2.v[33]*MainFormSLS->hh_1[86]
 + nn[262]
 + nn[263]
 + nn[264]
 + c2.v[37]*MainFormSLS->hh_1[14]
 + nn[265]
 + c2.v[39]*MainFormSLS->hh_1[58]
 + nn[24]
 + c2.v[41]*MainFormSLS->hh_1[102]
 + nn[266]
 + c2.v[43]*MainFormSLS->hh_1[146]
 + nn[267]
 + nn[268]
 + nn[269]
 + c2.v[47]*MainFormSLS->hh_1[74]
 + nn[29]
 + c2.v[49]*MainFormSLS->hh_1[118]
 + nn[100]
 + c2.v[51]*MainFormSLS->hh_1[2]
 + nn[270]
 + c2.v[53]*MainFormSLS->hh_1[46]
 + nn[271]
 + nn[272]
 + nn[34]
 + c2.v[57]*MainFormSLS->hh_1[134]
 + nn[273]
 + c2.v[59]*MainFormSLS->hh_1[18]
 + nn[106]
 + c2.v[61]*MainFormSLS->hh_1[62]
 + nn[274]
 + c2.v[63]*MainFormSLS->hh_1[106]
 + nn[38]
 + nn[275]
 + nn[276]
 + c2.v[67]*MainFormSLS->hh_1[34]
 + nn[277]
 + c2.v[69]*MainFormSLS->hh_1[78]
 + nn[112]
 + c2.v[71]*MainFormSLS->hh_1[122]
 + nn[43]
 + c2.v[73]*MainFormSLS->hh_1[6]
 + nn[278]
 + nn[279]
 + nn[280]
 + c2.v[77]*MainFormSLS->hh_1[94]
 + nn[281]
 + c2.v[79]*MainFormSLS->hh_1[138];
s/=N_2;
out.push_back(s);

//отсчет 12
s= nn[118]
 + (c2.v[1] + c2.v[21] + c2.v[41] + c2.v[61])*MainFormSLS->hh_1[24]
 + nn[282]
 + (c2.v[3] + c2.v[23] + c2.v[43] + c2.v[63])*MainFormSLS->hh_1[72]
 + nn[283]
 + nn[284]
 + nn[285]
 + (c2.v[7] + c2.v[27] + c2.v[47] + c2.v[67])*MainFormSLS->hh_1[8]
 + nn[286]
 + (c2.v[9] + c2.v[29] + c2.v[49] + c2.v[69])*MainFormSLS->hh_1[56]
 + nn[124]
 + (c2.v[11] + c2.v[31] + c2.v[51] + c2.v[71])*MainFormSLS->hh_1[104]
 + nn[287]
 + (c2.v[13] + c2.v[33] + c2.v[53] + c2.v[73])*MainFormSLS->hh_1[152]
 + nn[288]
 + nn[289]
 + nn[290]
 + (c2.v[17] + c2.v[37] + c2.v[57] + c2.v[77])*MainFormSLS->hh_1[88]
 + nn[291]
 + (c2.v[19] + c2.v[39] + c2.v[59] + c2.v[79])*MainFormSLS->hh_1[136];
s/=N_2;
out.push_back(s);

//отсчет 13
s= nn[0]
 + c2.v[1]*MainFormSLS->hh_1[26]
 + nn[292]
 + c2.v[3]*MainFormSLS->hh_1[78]
 + nn[293]
 + nn[294]
 + nn[295]
 + c2.v[7]*MainFormSLS->hh_1[22]
 + nn[76]
 + c2.v[9]*MainFormSLS->hh_1[74]
 + nn[296]
 + c2.v[11]*MainFormSLS->hh_1[126]
 + nn[297]
 + c2.v[13]*MainFormSLS->hh_1[18]
 + nn[298]
 + nn[299]
 + nn[81]
 + c2.v[17]*MainFormSLS->hh_1[122]
 + nn[300]
 + c2.v[19]*MainFormSLS->hh_1[14]
 + nn[12]
 + c2.v[21]*MainFormSLS->hh_1[66]
 + nn[301]
 + c2.v[23]*MainFormSLS->hh_1[118]
 + nn[85]
 + nn[302]
 + nn[303]
 + c2.v[27]*MainFormSLS->hh_1[62]
 + nn[304]
 + c2.v[29]*MainFormSLS->hh_1[114]
 + nn[305]
 + c2.v[31]*MainFormSLS->hh_1[6]
 + nn[90]
 + c2.v[33]*MainFormSLS->hh_1[58]
 + nn[306]
 + nn[307]
 + nn[308]
 + c2.v[37]*MainFormSLS->hh_1[2]
 + nn[309]
 + c2.v[39]*MainFormSLS->hh_1[54]
 + nn[24]
 + c2.v[41]*MainFormSLS->hh_1[106]
 + nn[310]
 + c2.v[43]*MainFormSLS->hh_1[158]
 + nn[311]
 + nn[312]
 + nn[313]
 + c2.v[47]*MainFormSLS->hh_1[102]
 + nn[99]
 + c2.v[49]*MainFormSLS->hh_1[154]
 + nn[314]
 + c2.v[51]*MainFormSLS->hh_1[46]
 + nn[315]
 + c2.v[53]*MainFormSLS->hh_1[98]
 + nn[316]
 + nn[317]
 + nn[104]
 + c2.v[57]*MainFormSLS->hh_1[42]
 + nn[318]
 + c2.v[59]*MainFormSLS->hh_1[94]
 + nn[36]
 + c2.v[61]*MainFormSLS->hh_1[146]
 + nn[319]
 + c2.v[63]*MainFormSLS->hh_1[38]
 + nn[108]
 + nn[320]
 + nn[321]
 + c2.v[67]*MainFormSLS->hh_1[142]
 + nn[322]
 + c2.v[69]*MainFormSLS->hh_1[34]
 + nn[323]
 + c2.v[71]*MainFormSLS->hh_1[86]
 + nn[113]
 + c2.v[73]*MainFormSLS->hh_1[138]
 + nn[324]
 + nn[325]
 + nn[326]
 + c2.v[77]*MainFormSLS->hh_1[82]
 + nn[327]
 + c2.v[79]*MainFormSLS->hh_1[134];
s/=N_2;
out.push_back(s);

//отсчет 14
s= nn[48]
 + (c2.v[1] + c2.v[41])*MainFormSLS->hh_1[28]
 + nn[328]
 + (c2.v[3] + c2.v[43])*MainFormSLS->hh_1[84]
 + nn[329]
 + nn[330]
 + nn[331]
 + (c2.v[7] + c2.v[47])*MainFormSLS->hh_1[36]
 + nn[332]
 + (c2.v[9] + c2.v[49])*MainFormSLS->hh_1[92]
 + nn[143]
 + (c2.v[11] + c2.v[51])*MainFormSLS->hh_1[148]
 + nn[333]
 + (c2.v[13] + c2.v[53])*MainFormSLS->hh_1[44]
 + nn[334]
 + nn[335]
 + nn[336]
 + (c2.v[17] + c2.v[57])*MainFormSLS->hh_1[156]
 + nn[337]
 + (c2.v[19] + c2.v[59])*MainFormSLS->hh_1[52]
 + nn[60]
 + (c2.v[21] + c2.v[61])*MainFormSLS->hh_1[108]
 + nn[338]
 + (c2.v[23] + c2.v[63])*MainFormSLS->hh_1[4]
 + nn[339]
 + nn[340]
 + nn[341]
 + (c2.v[27] + c2.v[67])*MainFormSLS->hh_1[116]
 + nn[342]
 + (c2.v[29] + c2.v[69])*MainFormSLS->hh_1[12]
 + nn[154]
 + (c2.v[31] + c2.v[71])*MainFormSLS->hh_1[68]
 + nn[343]
 + (c2.v[33] + c2.v[73])*MainFormSLS->hh_1[124]
 + nn[344]
 + nn[345]
 + nn[346]
 + (c2.v[37] + c2.v[77])*MainFormSLS->hh_1[76]
 + nn[347]
 + (c2.v[39] + c2.v[79])*MainFormSLS->hh_1[132];
s/=N_2;
out.push_back(s);

//отсчет 15
s= nn[130]
 + (c2.v[1] + c2.v[17] + c2.v[33] + c2.v[49] + c2.v[65])*MainFormSLS->hh_1[30]
 + nn[348]
 + (c2.v[3] + c2.v[19] + c2.v[35] + c2.v[51] + c2.v[67])*MainFormSLS->hh_1[90]
 + nn[349]
 + (c2.v[5] + c2.v[21] + c2.v[37] + c2.v[53] + c2.v[69])*MainFormSLS->hh_1[150]
 + nn[350]
 + (c2.v[7] + c2.v[23] + c2.v[39] + c2.v[55] + c2.v[71])*MainFormSLS->hh_1[50]
 + nn[134]
 + (c2.v[9] + c2.v[25] + c2.v[41] + c2.v[57] + c2.v[73])*MainFormSLS->hh_1[110]
 + nn[351]
 + (c2.v[11] + c2.v[27] + c2.v[43] + c2.v[59] + c2.v[75])*MainFormSLS->hh_1[10]
 + nn[352]
 + (c2.v[13] + c2.v[29] + c2.v[45] + c2.v[61] + c2.v[77])*MainFormSLS->hh_1[70]
 + nn[353]
 + (c2.v[15] + c2.v[31] + c2.v[47] + c2.v[63] + c2.v[79])*MainFormSLS->hh_1[130];
s/=N_2;
out.push_back(s);

//отсчет 16
s= nn[354]
 + (c2.v[1] + c2.v[6] + c2.v[11] + c2.v[16] + c2.v[21] + c2.v[26] + c2.v[31] + c2.v[36] + c2.v[41] + c2.v[46] + c2.v[51] + c2.v[56] + c2.v[61] + c2.v[66] + c2.v[71] + c2.v[76])*MainFormSLS->hh_1[32]
 + (c2.v[2] + c2.v[7] + c2.v[12] + c2.v[17] + c2.v[22] + c2.v[27] + c2.v[32] + c2.v[37] + c2.v[42] + c2.v[47] + c2.v[52] + c2.v[57] + c2.v[62] + c2.v[67] + c2.v[72] + c2.v[77])*MainFormSLS->hh_1[64]
 + (c2.v[3] + c2.v[8] + c2.v[13] + c2.v[18] + c2.v[23] + c2.v[28] + c2.v[33] + c2.v[38] + c2.v[43] + c2.v[48] + c2.v[53] + c2.v[58] + c2.v[63] + c2.v[68] + c2.v[73] + c2.v[78])*MainFormSLS->hh_1[96]
 + (c2.v[4] + c2.v[9] + c2.v[14] + c2.v[19] + c2.v[24] + c2.v[29] + c2.v[34] + c2.v[39] + c2.v[44] + c2.v[49] + c2.v[54] + c2.v[59] + c2.v[64] + c2.v[69] + c2.v[74] + c2.v[79])*MainFormSLS->hh_1[128];
s/=N_2;
out.push_back(s);

//отсчет 17
s= nn[0]
 + c2.v[1]*MainFormSLS->hh_1[34]
 + nn[355]
 + c2.v[3]*MainFormSLS->hh_1[102]
 + nn[356]
 + nn[3]
 + nn[357]
 + c2.v[7]*MainFormSLS->hh_1[78]
 + nn[164]
 + c2.v[9]*MainFormSLS->hh_1[146]
 + nn[6]
 + c2.v[11]*MainFormSLS->hh_1[54]
 + nn[358]
 + c2.v[13]*MainFormSLS->hh_1[122]
 + nn[359]
 + nn[9]
 + nn[169]
 + c2.v[17]*MainFormSLS->hh_1[98]
 + nn[360]
 + c2.v[19]*MainFormSLS->hh_1[6]
 + nn[12]
 + c2.v[21]*MainFormSLS->hh_1[74]
 + nn[361]
 + c2.v[23]*MainFormSLS->hh_1[142]
 + nn[172]
 + nn[15]
 + nn[362]
 + c2.v[27]*MainFormSLS->hh_1[118]
 + nn[363]
 + c2.v[29]*MainFormSLS->hh_1[26]
 + nn[18]
 + c2.v[31]*MainFormSLS->hh_1[94]
 + nn[177]
 + c2.v[33]*MainFormSLS->hh_1[2]
 + nn[364]
 + nn[21]
 + nn[365]
 + c2.v[37]*MainFormSLS->hh_1[138]
 + nn[366]
 + c2.v[39]*MainFormSLS->hh_1[46]
 + nn[24]
 + c2.v[41]*MainFormSLS->hh_1[114]
 + nn[367]
 + c2.v[43]*MainFormSLS->hh_1[22]
 + nn[368]
 + nn[27]
 + nn[369]
 + c2.v[47]*MainFormSLS->hh_1[158]
 + nn[186]
 + c2.v[49]*MainFormSLS->hh_1[66]
 + nn[30]
 + c2.v[51]*MainFormSLS->hh_1[134]
 + nn[370]
 + c2.v[53]*MainFormSLS->hh_1[42]
 + nn[371]
 + nn[33]
 + nn[191]
 + c2.v[57]*MainFormSLS->hh_1[18]
 + nn[372]
 + c2.v[59]*MainFormSLS->hh_1[86]
 + nn[36]
 + c2.v[61]*MainFormSLS->hh_1[154]
 + nn[373]
 + c2.v[63]*MainFormSLS->hh_1[62]
 + nn[194]
 + nn[39]
 + nn[374]
 + c2.v[67]*MainFormSLS->hh_1[38]
 + nn[375]
 + c2.v[69]*MainFormSLS->hh_1[106]
 + nn[42]
 + c2.v[71]*MainFormSLS->hh_1[14]
 + nn[199]
 + c2.v[73]*MainFormSLS->hh_1[82]
 + nn[376]
 + nn[45]
 + nn[377]
 + c2.v[77]*MainFormSLS->hh_1[58]
 + nn[378]
 + c2.v[79]*MainFormSLS->hh_1[126];
s/=N_2;
out.push_back(s);

//отсчет 18
s= nn[48]
 + (c2.v[1] + c2.v[41])*MainFormSLS->hh_1[36]
 + nn[379]
 + (c2.v[3] + c2.v[43])*MainFormSLS->hh_1[108]
 + nn[380]
 + nn[51]
 + nn[381]
 + (c2.v[7] + c2.v[47])*MainFormSLS->hh_1[92]
 + nn[382]
 + (c2.v[9] + c2.v[49])*MainFormSLS->hh_1[4]
 + nn[54]
 + (c2.v[11] + c2.v[51])*MainFormSLS->hh_1[76]
 + nn[383]
 + (c2.v[13] + c2.v[53])*MainFormSLS->hh_1[148]
 + nn[384]
 + nn[57]
 + nn[385]
 + (c2.v[17] + c2.v[57])*MainFormSLS->hh_1[132]
 + nn[386]
 + (c2.v[19] + c2.v[59])*MainFormSLS->hh_1[44]
 + nn[60]
 + (c2.v[21] + c2.v[61])*MainFormSLS->hh_1[116]
 + nn[387]
 + (c2.v[23] + c2.v[63])*MainFormSLS->hh_1[28]
 + nn[388]
 + nn[63]
 + nn[389]
 + (c2.v[27] + c2.v[67])*MainFormSLS->hh_1[12]
 + nn[390]
 + (c2.v[29] + c2.v[69])*MainFormSLS->hh_1[84]
 + nn[66]
 + (c2.v[31] + c2.v[71])*MainFormSLS->hh_1[156]
 + nn[391]
 + (c2.v[33] + c2.v[73])*MainFormSLS->hh_1[68]
 + nn[392]
 + nn[69]
 + nn[393]
 + (c2.v[37] + c2.v[77])*MainFormSLS->hh_1[52]
 + nn[394]
 + (c2.v[39] + c2.v[79])*MainFormSLS->hh_1[124];
s/=N_2;
out.push_back(s);

//отсчет 19
s= nn[0]
 + c2.v[1]*MainFormSLS->hh_1[38]
 + nn[395]
 + c2.v[3]*MainFormSLS->hh_1[114]
 + nn[396]
 + nn[74]
 + nn[397]
 + c2.v[7]*MainFormSLS->hh_1[106]
 + nn[210]
 + c2.v[9]*MainFormSLS->hh_1[22]
 + nn[77]
 + c2.v[11]*MainFormSLS->hh_1[98]
 + nn[398]
 + c2.v[13]*MainFormSLS->hh_1[14]
 + nn[399]
 + nn[80]
 + nn[214]
 + c2.v[17]*MainFormSLS->hh_1[6]
 + nn[400]
 + c2.v[19]*MainFormSLS->hh_1[82]
 + nn[83]
 + c2.v[21]*MainFormSLS->hh_1[158]
 + nn[401]
 + c2.v[23]*MainFormSLS->hh_1[74]
 + nn[217]
 + nn[86]
 + nn[402]
 + c2.v[27]*MainFormSLS->hh_1[66]
 + nn[403]
 + c2.v[29]*MainFormSLS->hh_1[142]
 + nn[89]
 + c2.v[31]*MainFormSLS->hh_1[58]
 + nn[221]
 + c2.v[33]*MainFormSLS->hh_1[134]
 + nn[404]
 + nn[92]
 + nn[405]
 + c2.v[37]*MainFormSLS->hh_1[126]
 + nn[406]
 + c2.v[39]*MainFormSLS->hh_1[42]
 + nn[24]
 + c2.v[41]*MainFormSLS->hh_1[118]
 + nn[407]
 + c2.v[43]*MainFormSLS->hh_1[34]
 + nn[408]
 + nn[97]
 + nn[409]
 + c2.v[47]*MainFormSLS->hh_1[26]
 + nn[230]
 + c2.v[49]*MainFormSLS->hh_1[102]
 + nn[100]
 + c2.v[51]*MainFormSLS->hh_1[18]
 + nn[410]
 + c2.v[53]*MainFormSLS->hh_1[94]
 + nn[411]
 + nn[103]
 + nn[234]
 + c2.v[57]*MainFormSLS->hh_1[86]
 + nn[412]
 + c2.v[59]*MainFormSLS->hh_1[2]
 + nn[106]
 + c2.v[61]*MainFormSLS->hh_1[78]
 + nn[413]
 + c2.v[63]*MainFormSLS->hh_1[154]
 + nn[237]
 + nn[109]
 + nn[414]
 + c2.v[67]*MainFormSLS->hh_1[146]
 + nn[415]
 + c2.v[69]*MainFormSLS->hh_1[62]
 + nn[112]
 + c2.v[71]*MainFormSLS->hh_1[138]
 + nn[241]
 + c2.v[73]*MainFormSLS->hh_1[54]
 + nn[416]
 + nn[115]
 + nn[417]
 + c2.v[77]*MainFormSLS->hh_1[46]
 + nn[418]
 + c2.v[79]*MainFormSLS->hh_1[122];
s/=N_2;
out.push_back(s);

//отсчет 20
s= nn[419]
 + (c2.v[1] + c2.v[5] + c2.v[9] + c2.v[13] + c2.v[17] + c2.v[21] + c2.v[25] + c2.v[29] + c2.v[33] + c2.v[37] + c2.v[41] + c2.v[45] + c2.v[49] + c2.v[53] + c2.v[57] + c2.v[61] + c2.v[65] + c2.v[69] + c2.v[73] + c2.v[77])*MainFormSLS->hh_1[40]
 + nn[420]
 + (c2.v[3] + c2.v[7] + c2.v[11] + c2.v[15] + c2.v[19] + c2.v[23] + c2.v[27] + c2.v[31] + c2.v[35] + c2.v[39] + c2.v[43] + c2.v[47] + c2.v[51] + c2.v[55] + c2.v[59] + c2.v[63] + c2.v[67] + c2.v[71] + c2.v[75] + c2.v[79])*MainFormSLS->hh_1[120];
s/=N_2;
out.push_back(s);

//отсчет 21
s= nn[0]
 + c2.v[1]*MainFormSLS->hh_1[42]
 + nn[421]
 + c2.v[3]*MainFormSLS->hh_1[126]
 + nn[2]
 + nn[422]
 + nn[423]
 + c2.v[7]*MainFormSLS->hh_1[134]
 + nn[5]
 + c2.v[9]*MainFormSLS->hh_1[58]
 + nn[296]
 + c2.v[11]*MainFormSLS->hh_1[142]
 + nn[7]
 + c2.v[13]*MainFormSLS->hh_1[66]
 + nn[424]
 + nn[425]
 + nn[10]
 + c2.v[17]*MainFormSLS->hh_1[74]
 + nn[426]
 + c2.v[19]*MainFormSLS->hh_1[158]
 + nn[12]
 + c2.v[21]*MainFormSLS->hh_1[82]
 + nn[427]
 + c2.v[23]*MainFormSLS->hh_1[6]
 + nn[14]
 + nn[428]
 + nn[429]
 + c2.v[27]*MainFormSLS->hh_1[14]
 + nn[17]
 + c2.v[29]*MainFormSLS->hh_1[98]
 + nn[305]
 + c2.v[31]*MainFormSLS->hh_1[22]
 + nn[19]
 + c2.v[33]*MainFormSLS->hh_1[106]
 + nn[430]
 + nn[431]
 + nn[22]
 + c2.v[37]*MainFormSLS->hh_1[114]
 + nn[432]
 + c2.v[39]*MainFormSLS->hh_1[38]
 + nn[24]
 + c2.v[41]*MainFormSLS->hh_1[122]
 + nn[433]
 + c2.v[43]*MainFormSLS->hh_1[46]
 + nn[26]
 + nn[434]
 + nn[435]
 + c2.v[47]*MainFormSLS->hh_1[54]
 + nn[29]
 + c2.v[49]*MainFormSLS->hh_1[138]
 + nn[314]
 + c2.v[51]*MainFormSLS->hh_1[62]
 + nn[31]
 + c2.v[53]*MainFormSLS->hh_1[146]
 + nn[436]
 + nn[437]
 + nn[34]
 + c2.v[57]*MainFormSLS->hh_1[154]
 + nn[438]
 + c2.v[59]*MainFormSLS->hh_1[78]
 + nn[36]
 + c2.v[61]*MainFormSLS->hh_1[2]
 + nn[439]
 + c2.v[63]*MainFormSLS->hh_1[86]
 + nn[38]
 + nn[440]
 + nn[441]
 + c2.v[67]*MainFormSLS->hh_1[94]
 + nn[41]
 + c2.v[69]*MainFormSLS->hh_1[18]
 + nn[323]
 + c2.v[71]*MainFormSLS->hh_1[102]
 + nn[43]
 + c2.v[73]*MainFormSLS->hh_1[26]
 + nn[442]
 + nn[443]
 + nn[46]
 + c2.v[77]*MainFormSLS->hh_1[34]
 + nn[444]
 + c2.v[79]*MainFormSLS->hh_1[118];
s/=N_2;
out.push_back(s);

//отсчет 22
s= nn[48]
 + (c2.v[1] + c2.v[41])*MainFormSLS->hh_1[44]
 + nn[445]
 + (c2.v[3] + c2.v[43])*MainFormSLS->hh_1[132]
 + nn[50]
 + nn[140]
 + nn[446]
 + (c2.v[7] + c2.v[47])*MainFormSLS->hh_1[148]
 + nn[53]
 + (c2.v[9] + c2.v[49])*MainFormSLS->hh_1[76]
 + nn[143]
 + (c2.v[11] + c2.v[51])*MainFormSLS->hh_1[4]
 + nn[55]
 + (c2.v[13] + c2.v[53])*MainFormSLS->hh_1[92]
 + nn[447]
 + nn[146]
 + nn[58]
 + (c2.v[17] + c2.v[57])*MainFormSLS->hh_1[108]
 + nn[448]
 + (c2.v[19] + c2.v[59])*MainFormSLS->hh_1[36]
 + nn[60]
 + (c2.v[21] + c2.v[61])*MainFormSLS->hh_1[124]
 + nn[449]
 + (c2.v[23] + c2.v[63])*MainFormSLS->hh_1[52]
 + nn[62]
 + nn[151]
 + nn[450]
 + (c2.v[27] + c2.v[67])*MainFormSLS->hh_1[68]
 + nn[65]
 + (c2.v[29] + c2.v[69])*MainFormSLS->hh_1[156]
 + nn[154]
 + (c2.v[31] + c2.v[71])*MainFormSLS->hh_1[84]
 + nn[67]
 + (c2.v[33] + c2.v[73])*MainFormSLS->hh_1[12]
 + nn[451]
 + nn[157]
 + nn[70]
 + (c2.v[37] + c2.v[77])*MainFormSLS->hh_1[28]
 + nn[452]
 + (c2.v[39] + c2.v[79])*MainFormSLS->hh_1[116];
s/=N_2;
out.push_back(s);

//отсчет 23
s= nn[0]
 + c2.v[1]*MainFormSLS->hh_1[46]
 + nn[453]
 + c2.v[3]*MainFormSLS->hh_1[138]
 + nn[73]
 + nn[162]
 + nn[454]
 + c2.v[7]*MainFormSLS->hh_1[2]
 + nn[76]
 + c2.v[9]*MainFormSLS->hh_1[94]
 + nn[165]
 + c2.v[11]*MainFormSLS->hh_1[26]
 + nn[78]
 + c2.v[13]*MainFormSLS->hh_1[118]
 + nn[455]
 + nn[168]
 + nn[81]
 + c2.v[17]*MainFormSLS->hh_1[142]
 + nn[456]
 + c2.v[19]*MainFormSLS->hh_1[74]
 + nn[83]
 + c2.v[21]*MainFormSLS->hh_1[6]
 + nn[457]
 + c2.v[23]*MainFormSLS->hh_1[98]
 + nn[85]
 + nn[173]
 + nn[458]
 + c2.v[27]*MainFormSLS->hh_1[122]
 + nn[88]
 + c2.v[29]*MainFormSLS->hh_1[54]
 + nn[176]
 + c2.v[31]*MainFormSLS->hh_1[146]
 + nn[90]
 + c2.v[33]*MainFormSLS->hh_1[78]
 + nn[459]
 + nn[179]
 + nn[93]
 + c2.v[37]*MainFormSLS->hh_1[102]
 + nn[460]
 + c2.v[39]*MainFormSLS->hh_1[34]
 + nn[24]
 + c2.v[41]*MainFormSLS->hh_1[126]
 + nn[461]
 + c2.v[43]*MainFormSLS->hh_1[58]
 + nn[96]
 + nn[184]
 + nn[462]
 + c2.v[47]*MainFormSLS->hh_1[82]
 + nn[99]
 + c2.v[49]*MainFormSLS->hh_1[14]
 + nn[187]
 + c2.v[51]*MainFormSLS->hh_1[106]
 + nn[101]
 + c2.v[53]*MainFormSLS->hh_1[38]
 + nn[463]
 + nn[190]
 + nn[104]
 + c2.v[57]*MainFormSLS->hh_1[62]
 + nn[464]
 + c2.v[59]*MainFormSLS->hh_1[154]
 + nn[106]
 + c2.v[61]*MainFormSLS->hh_1[86]
 + nn[465]
 + c2.v[63]*MainFormSLS->hh_1[18]
 + nn[108]
 + nn[195]
 + nn[466]
 + c2.v[67]*MainFormSLS->hh_1[42]
 + nn[111]
 + c2.v[69]*MainFormSLS->hh_1[134]
 + nn[198]
 + c2.v[71]*MainFormSLS->hh_1[66]
 + nn[113]
 + c2.v[73]*MainFormSLS->hh_1[158]
 + nn[467]
 + nn[201]
 + nn[116]
 + c2.v[77]*MainFormSLS->hh_1[22]
 + nn[468]
 + c2.v[79]*MainFormSLS->hh_1[114];
s/=N_2;
out.push_back(s);

//отсчет 24
s= nn[204]
 + (c2.v[1] + c2.v[11] + c2.v[21] + c2.v[31] + c2.v[41] + c2.v[51] + c2.v[61] + c2.v[71])*MainFormSLS->hh_1[48]
 + (c2.v[2] + c2.v[12] + c2.v[22] + c2.v[32] + c2.v[42] + c2.v[52] + c2.v[62] + c2.v[72])*MainFormSLS->hh_1[96]
 + (c2.v[3] + c2.v[13] + c2.v[23] + c2.v[33] + c2.v[43] + c2.v[53] + c2.v[63] + c2.v[73])*MainFormSLS->hh_1[144]
 + (c2.v[4] + c2.v[14] + c2.v[24] + c2.v[34] + c2.v[44] + c2.v[54] + c2.v[64] + c2.v[74])*MainFormSLS->hh_1[32]
 + nn[205]
 + (c2.v[6] + c2.v[16] + c2.v[26] + c2.v[36] + c2.v[46] + c2.v[56] + c2.v[66] + c2.v[76])*MainFormSLS->hh_1[128]
 + (c2.v[7] + c2.v[17] + c2.v[27] + c2.v[37] + c2.v[47] + c2.v[57] + c2.v[67] + c2.v[77])*MainFormSLS->hh_1[16]
 + (c2.v[8] + c2.v[18] + c2.v[28] + c2.v[38] + c2.v[48] + c2.v[58] + c2.v[68] + c2.v[78])*MainFormSLS->hh_1[64]
 + (c2.v[9] + c2.v[19] + c2.v[29] + c2.v[39] + c2.v[49] + c2.v[59] + c2.v[69] + c2.v[79])*MainFormSLS->hh_1[112];
s/=N_2;
out.push_back(s);

//отсчет 25
s= nn[130]
 + (c2.v[1] + c2.v[17] + c2.v[33] + c2.v[49] + c2.v[65])*MainFormSLS->hh_1[50]
 + nn[469]
 + (c2.v[3] + c2.v[19] + c2.v[35] + c2.v[51] + c2.v[67])*MainFormSLS->hh_1[150]
 + nn[132]
 + (c2.v[5] + c2.v[21] + c2.v[37] + c2.v[53] + c2.v[69])*MainFormSLS->hh_1[90]
 + nn[470]
 + (c2.v[7] + c2.v[23] + c2.v[39] + c2.v[55] + c2.v[71])*MainFormSLS->hh_1[30]
 + nn[134]
 + (c2.v[9] + c2.v[25] + c2.v[41] + c2.v[57] + c2.v[73])*MainFormSLS->hh_1[130]
 + nn[471]
 + (c2.v[11] + c2.v[27] + c2.v[43] + c2.v[59] + c2.v[75])*MainFormSLS->hh_1[70]
 + nn[136]
 + (c2.v[13] + c2.v[29] + c2.v[45] + c2.v[61] + c2.v[77])*MainFormSLS->hh_1[10]
 + nn[472]
 + (c2.v[15] + c2.v[31] + c2.v[47] + c2.v[63] + c2.v[79])*MainFormSLS->hh_1[110];
s/=N_2;
out.push_back(s);

//отсчет 26
s= nn[48]
 + (c2.v[1] + c2.v[41])*MainFormSLS->hh_1[52]
 + nn[473]
 + (c2.v[3] + c2.v[43])*MainFormSLS->hh_1[156]
 + nn[139]
 + nn[474]
 + nn[475]
 + (c2.v[7] + c2.v[47])*MainFormSLS->hh_1[44]
 + nn[142]
 + (c2.v[9] + c2.v[49])*MainFormSLS->hh_1[148]
 + nn[54]
 + (c2.v[11] + c2.v[51])*MainFormSLS->hh_1[92]
 + nn[144]
 + (c2.v[13] + c2.v[53])*MainFormSLS->hh_1[36]
 + nn[476]
 + nn[477]
 + nn[147]
 + (c2.v[17] + c2.v[57])*MainFormSLS->hh_1[84]
 + nn[478]
 + (c2.v[19] + c2.v[59])*MainFormSLS->hh_1[28]
 + nn[60]
 + (c2.v[21] + c2.v[61])*MainFormSLS->hh_1[132]
 + nn[479]
 + (c2.v[23] + c2.v[63])*MainFormSLS->hh_1[76]
 + nn[150]
 + nn[480]
 + nn[481]
 + (c2.v[27] + c2.v[67])*MainFormSLS->hh_1[124]
 + nn[153]
 + (c2.v[29] + c2.v[69])*MainFormSLS->hh_1[68]
 + nn[66]
 + (c2.v[31] + c2.v[71])*MainFormSLS->hh_1[12]
 + nn[155]
 + (c2.v[33] + c2.v[73])*MainFormSLS->hh_1[116]
 + nn[482]
 + nn[483]
 + nn[158]
 + (c2.v[37] + c2.v[77])*MainFormSLS->hh_1[4]
 + nn[484]
 + (c2.v[39] + c2.v[79])*MainFormSLS->hh_1[108];
s/=N_2;
out.push_back(s);

//отсчет 27
s= nn[0]
 + c2.v[1]*MainFormSLS->hh_1[54]
 + nn[485]
 + c2.v[3]*MainFormSLS->hh_1[2]
 + nn[161]
 + nn[252]
 + nn[486]
 + c2.v[7]*MainFormSLS->hh_1[58]
 + nn[164]
 + c2.v[9]*MainFormSLS->hh_1[6]
 + nn[77]
 + c2.v[11]*MainFormSLS->hh_1[114]
 + nn[166]
 + c2.v[13]*MainFormSLS->hh_1[62]
 + nn[487]
 + nn[256]
 + nn[169]
 + c2.v[17]*MainFormSLS->hh_1[118]
 + nn[488]
 + c2.v[19]*MainFormSLS->hh_1[66]
 + nn[83]
 + c2.v[21]*MainFormSLS->hh_1[14]
 + nn[489]
 + c2.v[23]*MainFormSLS->hh_1[122]
 + nn[172]
 + nn[259]
 + nn[490]
 + c2.v[27]*MainFormSLS->hh_1[18]
 + nn[175]
 + c2.v[29]*MainFormSLS->hh_1[126]
 + nn[89]
 + c2.v[31]*MainFormSLS->hh_1[74]
 + nn[177]
 + c2.v[33]*MainFormSLS->hh_1[22]
 + nn[491]
 + nn[263]
 + nn[180]
 + c2.v[37]*MainFormSLS->hh_1[78]
 + nn[492]
 + c2.v[39]*MainFormSLS->hh_1[26]
 + nn[24]
 + c2.v[41]*MainFormSLS->hh_1[134]
 + nn[493]
 + c2.v[43]*MainFormSLS->hh_1[82]
 + nn[183]
 + nn[268]
 + nn[494]
 + c2.v[47]*MainFormSLS->hh_1[138]
 + nn[186]
 + c2.v[49]*MainFormSLS->hh_1[86]
 + nn[100]
 + c2.v[51]*MainFormSLS->hh_1[34]
 + nn[188]
 + c2.v[53]*MainFormSLS->hh_1[142]
 + nn[495]
 + nn[272]
 + nn[191]
 + c2.v[57]*MainFormSLS->hh_1[38]
 + nn[496]
 + c2.v[59]*MainFormSLS->hh_1[146]
 + nn[106]
 + c2.v[61]*MainFormSLS->hh_1[94]
 + nn[497]
 + c2.v[63]*MainFormSLS->hh_1[42]
 + nn[194]
 + nn[275]
 + nn[498]
 + c2.v[67]*MainFormSLS->hh_1[98]
 + nn[197]
 + c2.v[69]*MainFormSLS->hh_1[46]
 + nn[112]
 + c2.v[71]*MainFormSLS->hh_1[154]
 + nn[199]
 + c2.v[73]*MainFormSLS->hh_1[102]
 + nn[499]
 + nn[279]
 + nn[202]
 + c2.v[77]*MainFormSLS->hh_1[158]
 + nn[500]
 + c2.v[79]*MainFormSLS->hh_1[106];
s/=N_2;
out.push_back(s);

//отсчет 28
s= nn[118]
 + (c2.v[1] + c2.v[21] + c2.v[41] + c2.v[61])*MainFormSLS->hh_1[56]
 + nn[501]
 + (c2.v[3] + c2.v[23] + c2.v[43] + c2.v[63])*MainFormSLS->hh_1[8]
 + nn[502]
 + nn[284]
 + nn[503]
 + (c2.v[7] + c2.v[27] + c2.v[47] + c2.v[67])*MainFormSLS->hh_1[72]
 + nn[504]
 + (c2.v[9] + c2.v[29] + c2.v[49] + c2.v[69])*MainFormSLS->hh_1[24]
 + nn[124]
 + (c2.v[11] + c2.v[31] + c2.v[51] + c2.v[71])*MainFormSLS->hh_1[136]
 + nn[505]
 + (c2.v[13] + c2.v[33] + c2.v[53] + c2.v[73])*MainFormSLS->hh_1[88]
 + nn[506]
 + nn[289]
 + nn[507]
 + (c2.v[17] + c2.v[37] + c2.v[57] + c2.v[77])*MainFormSLS->hh_1[152]
 + nn[508]
 + (c2.v[19] + c2.v[39] + c2.v[59] + c2.v[79])*MainFormSLS->hh_1[104];
s/=N_2;
out.push_back(s);

//отсчет 29
s= nn[0]
 + c2.v[1]*MainFormSLS->hh_1[58]
 + nn[509]
 + c2.v[3]*MainFormSLS->hh_1[14]
 + nn[207]
 + nn[294]
 + nn[510]
 + c2.v[7]*MainFormSLS->hh_1[86]
 + nn[210]
 + c2.v[9]*MainFormSLS->hh_1[42]
 + nn[296]
 + c2.v[11]*MainFormSLS->hh_1[158]
 + nn[211]
 + c2.v[13]*MainFormSLS->hh_1[114]
 + nn[511]
 + nn[299]
 + nn[214]
 + c2.v[17]*MainFormSLS->hh_1[26]
 + nn[512]
 + c2.v[19]*MainFormSLS->hh_1[142]
 + nn[12]
 + c2.v[21]*MainFormSLS->hh_1[98]
 + nn[513]
 + c2.v[23]*MainFormSLS->hh_1[54]
 + nn[217]
 + nn[302]
 + nn[514]
 + c2.v[27]*MainFormSLS->hh_1[126]
 + nn[220]
 + c2.v[29]*MainFormSLS->hh_1[82]
 + nn[305]
 + c2.v[31]*MainFormSLS->hh_1[38]
 + nn[221]
 + c2.v[33]*MainFormSLS->hh_1[154]
 + nn[515]
 + nn[307]
 + nn[224]
 + c2.v[37]*MainFormSLS->hh_1[66]
 + nn[516]
 + c2.v[39]*MainFormSLS->hh_1[22]
 + nn[24]
 + c2.v[41]*MainFormSLS->hh_1[138]
 + nn[517]
 + c2.v[43]*MainFormSLS->hh_1[94]
 + nn[227]
 + nn[312]
 + nn[518]
 + c2.v[47]*MainFormSLS->hh_1[6]
 + nn[230]
 + c2.v[49]*MainFormSLS->hh_1[122]
 + nn[314]
 + c2.v[51]*MainFormSLS->hh_1[78]
 + nn[231]
 + c2.v[53]*MainFormSLS->hh_1[34]
 + nn[519]
 + nn[317]
 + nn[234]
 + c2.v[57]*MainFormSLS->hh_1[106]
 + nn[520]
 + c2.v[59]*MainFormSLS->hh_1[62]
 + nn[36]
 + c2.v[61]*MainFormSLS->hh_1[18]
 + nn[521]
 + c2.v[63]*MainFormSLS->hh_1[134]
 + nn[237]
 + nn[320]
 + nn[522]
 + c2.v[67]*MainFormSLS->hh_1[46]
 + nn[240]
 + c2.v[69]*MainFormSLS->hh_1[2]
 + nn[323]
 + c2.v[71]*MainFormSLS->hh_1[118]
 + nn[241]
 + c2.v[73]*MainFormSLS->hh_1[74]
 + nn[523]
 + nn[325]
 + nn[244]
 + c2.v[77]*MainFormSLS->hh_1[146]
 + nn[524]
 + c2.v[79]*MainFormSLS->hh_1[102];
s/=N_2;
out.push_back(s);

//отсчет 30
s= nn[246]
 + (c2.v[1] + c2.v[9] + c2.v[17] + c2.v[25] + c2.v[33] + c2.v[41] + c2.v[49] + c2.v[57] + c2.v[65] + c2.v[73])*MainFormSLS->hh_1[60]
 + nn[525]
 + (c2.v[3] + c2.v[11] + c2.v[19] + c2.v[27] + c2.v[35] + c2.v[43] + c2.v[51] + c2.v[59] + c2.v[67] + c2.v[75])*MainFormSLS->hh_1[20]
 + nn[248]
 + (c2.v[5] + c2.v[13] + c2.v[21] + c2.v[29] + c2.v[37] + c2.v[45] + c2.v[53] + c2.v[61] + c2.v[69] + c2.v[77])*MainFormSLS->hh_1[140]
 + nn[526]
 + (c2.v[7] + c2.v[15] + c2.v[23] + c2.v[31] + c2.v[39] + c2.v[47] + c2.v[55] + c2.v[63] + c2.v[71] + c2.v[79])*MainFormSLS->hh_1[100];
s/=N_2;
out.push_back(s);

//отсчет 31
s= nn[0]
 + c2.v[1]*MainFormSLS->hh_1[62]
 + nn[527]
 + c2.v[3]*MainFormSLS->hh_1[26]
 + nn[251]
 + nn[528]
 + nn[529]
 + c2.v[7]*MainFormSLS->hh_1[114]
 + nn[5]
 + c2.v[9]*MainFormSLS->hh_1[78]
 + nn[165]
 + c2.v[11]*MainFormSLS->hh_1[42]
 + nn[254]
 + c2.v[13]*MainFormSLS->hh_1[6]
 + nn[530]
 + nn[531]
 + nn[10]
 + c2.v[17]*MainFormSLS->hh_1[94]
 + nn[532]
 + c2.v[19]*MainFormSLS->hh_1[58]
 + nn[83]
 + c2.v[21]*MainFormSLS->hh_1[22]
 + nn[533]
 + c2.v[23]*MainFormSLS->hh_1[146]
 + nn[14]
 + nn[534]
 + nn[535]
 + c2.v[27]*MainFormSLS->hh_1[74]
 + nn[261]
 + c2.v[29]*MainFormSLS->hh_1[38]
 + nn[176]
 + c2.v[31]*MainFormSLS->hh_1[2]
 + nn[19]
 + c2.v[33]*MainFormSLS->hh_1[126]
 + nn[536]
 + nn[537]
 + nn[264]
 + c2.v[37]*MainFormSLS->hh_1[54]
 + nn[538]
 + c2.v[39]*MainFormSLS->hh_1[18]
 + nn[24]
 + c2.v[41]*MainFormSLS->hh_1[142]
 + nn[539]
 + c2.v[43]*MainFormSLS->hh_1[106]
 + nn[267]
 + nn[540]
 + nn[541]
 + c2.v[47]*MainFormSLS->hh_1[34]
 + nn[29]
 + c2.v[49]*MainFormSLS->hh_1[158]
 + nn[187]
 + c2.v[51]*MainFormSLS->hh_1[122]
 + nn[270]
 + c2.v[53]*MainFormSLS->hh_1[86]
 + nn[542]
 + nn[543]
 + nn[34]
 + c2.v[57]*MainFormSLS->hh_1[14]
 + nn[544]
 + c2.v[59]*MainFormSLS->hh_1[138]
 + nn[106]
 + c2.v[61]*MainFormSLS->hh_1[102]
 + nn[545]
 + c2.v[63]*MainFormSLS->hh_1[66]
 + nn[38]
 + nn[546]
 + nn[547]
 + c2.v[67]*MainFormSLS->hh_1[154]
 + nn[277]
 + c2.v[69]*MainFormSLS->hh_1[118]
 + nn[198]
 + c2.v[71]*MainFormSLS->hh_1[82]
 + nn[43]
 + c2.v[73]*MainFormSLS->hh_1[46]
 + nn[548]
 + nn[549]
 + nn[280]
 + c2.v[77]*MainFormSLS->hh_1[134]
 + nn[550]
 + c2.v[79]*MainFormSLS->hh_1[98];
s/=N_2;
out.push_back(s);

//отсчет 32
s= nn[354]
 + (c2.v[1] + c2.v[6] + c2.v[11] + c2.v[16] + c2.v[21] + c2.v[26] + c2.v[31] + c2.v[36] + c2.v[41] + c2.v[46] + c2.v[51] + c2.v[56] + c2.v[61] + c2.v[66] + c2.v[71] + c2.v[76])*MainFormSLS->hh_1[64]
 + (c2.v[2] + c2.v[7] + c2.v[12] + c2.v[17] + c2.v[22] + c2.v[27] + c2.v[32] + c2.v[37] + c2.v[42] + c2.v[47] + c2.v[52] + c2.v[57] + c2.v[62] + c2.v[67] + c2.v[72] + c2.v[77])*MainFormSLS->hh_1[128]
 + (c2.v[3] + c2.v[8] + c2.v[13] + c2.v[18] + c2.v[23] + c2.v[28] + c2.v[33] + c2.v[38] + c2.v[43] + c2.v[48] + c2.v[53] + c2.v[58] + c2.v[63] + c2.v[68] + c2.v[73] + c2.v[78])*MainFormSLS->hh_1[32]
 + (c2.v[4] + c2.v[9] + c2.v[14] + c2.v[19] + c2.v[24] + c2.v[29] + c2.v[34] + c2.v[39] + c2.v[44] + c2.v[49] + c2.v[54] + c2.v[59] + c2.v[64] + c2.v[69] + c2.v[74] + c2.v[79])*MainFormSLS->hh_1[96];
s/=N_2;
out.push_back(s);

//отсчет 33
s= nn[0]
 + c2.v[1]*MainFormSLS->hh_1[66]
 + nn[551]
 + c2.v[3]*MainFormSLS->hh_1[38]
 + nn[293]
 + nn[3]
 + nn[552]
 + c2.v[7]*MainFormSLS->hh_1[142]
 + nn[76]
 + c2.v[9]*MainFormSLS->hh_1[114]
 + nn[6]
 + c2.v[11]*MainFormSLS->hh_1[86]
 + nn[297]
 + c2.v[13]*MainFormSLS->hh_1[58]
 + nn[553]
 + nn[9]
 + nn[81]
 + c2.v[17]*MainFormSLS->hh_1[2]
 + nn[554]
 + c2.v[19]*MainFormSLS->hh_1[134]
 + nn[12]
 + c2.v[21]*MainFormSLS->hh_1[106]
 + nn[555]
 + c2.v[23]*MainFormSLS->hh_1[78]
 + nn[85]
 + nn[15]
 + nn[556]
 + c2.v[27]*MainFormSLS->hh_1[22]
 + nn[304]
 + c2.v[29]*MainFormSLS->hh_1[154]
 + nn[18]
 + c2.v[31]*MainFormSLS->hh_1[126]
 + nn[90]
 + c2.v[33]*MainFormSLS->hh_1[98]
 + nn[557]
 + nn[21]
 + nn[308]
 + c2.v[37]*MainFormSLS->hh_1[42]
 + nn[558]
 + c2.v[39]*MainFormSLS->hh_1[14]
 + nn[24]
 + c2.v[41]*MainFormSLS->hh_1[146]
 + nn[559]
 + c2.v[43]*MainFormSLS->hh_1[118]
 + nn[311]
 + nn[27]
 + nn[560]
 + c2.v[47]*MainFormSLS->hh_1[62]
 + nn[99]
 + c2.v[49]*MainFormSLS->hh_1[34]
 + nn[30]
 + c2.v[51]*MainFormSLS->hh_1[6]
 + nn[315]
 + c2.v[53]*MainFormSLS->hh_1[138]
 + nn[561]
 + nn[33]
 + nn[104]
 + c2.v[57]*MainFormSLS->hh_1[82]
 + nn[562]
 + c2.v[59]*MainFormSLS->hh_1[54]
 + nn[36]
 + c2.v[61]*MainFormSLS->hh_1[26]
 + nn[563]
 + c2.v[63]*MainFormSLS->hh_1[158]
 + nn[108]
 + nn[39]
 + nn[564]
 + c2.v[67]*MainFormSLS->hh_1[102]
 + nn[322]
 + c2.v[69]*MainFormSLS->hh_1[74]
 + nn[42]
 + c2.v[71]*MainFormSLS->hh_1[46]
 + nn[113]
 + c2.v[73]*MainFormSLS->hh_1[18]
 + nn[565]
 + nn[45]
 + nn[326]
 + c2.v[77]*MainFormSLS->hh_1[122]
 + nn[566]
 + c2.v[79]*MainFormSLS->hh_1[94];
s/=N_2;
out.push_back(s);

//отсчет 34
s= nn[48]
 + (c2.v[1] + c2.v[41])*MainFormSLS->hh_1[68]
 + nn[567]
 + (c2.v[3] + c2.v[43])*MainFormSLS->hh_1[44]
 + nn[329]
 + nn[51]
 + nn[568]
 + (c2.v[7] + c2.v[47])*MainFormSLS->hh_1[156]
 + nn[332]
 + (c2.v[9] + c2.v[49])*MainFormSLS->hh_1[132]
 + nn[54]
 + (c2.v[11] + c2.v[51])*MainFormSLS->hh_1[108]
 + nn[333]
 + (c2.v[13] + c2.v[53])*MainFormSLS->hh_1[84]
 + nn[569]
 + nn[57]
 + nn[336]
 + (c2.v[17] + c2.v[57])*MainFormSLS->hh_1[36]
 + nn[570]
 + (c2.v[19] + c2.v[59])*MainFormSLS->hh_1[12]
 + nn[60]
 + (c2.v[21] + c2.v[61])*MainFormSLS->hh_1[148]
 + nn[571]
 + (c2.v[23] + c2.v[63])*MainFormSLS->hh_1[124]
 + nn[339]
 + nn[63]
 + nn[572]
 + (c2.v[27] + c2.v[67])*MainFormSLS->hh_1[76]
 + nn[342]
 + (c2.v[29] + c2.v[69])*MainFormSLS->hh_1[52]
 + nn[66]
 + (c2.v[31] + c2.v[71])*MainFormSLS->hh_1[28]
 + nn[343]
 + (c2.v[33] + c2.v[73])*MainFormSLS->hh_1[4]
 + nn[573]
 + nn[69]
 + nn[346]
 + (c2.v[37] + c2.v[77])*MainFormSLS->hh_1[116]
 + nn[574]
 + (c2.v[39] + c2.v[79])*MainFormSLS->hh_1[92];
s/=N_2;
out.push_back(s);

//отсчет 35
s= nn[130]
 + (c2.v[1] + c2.v[17] + c2.v[33] + c2.v[49] + c2.v[65])*MainFormSLS->hh_1[70]
 + nn[575]
 + (c2.v[3] + c2.v[19] + c2.v[35] + c2.v[51] + c2.v[67])*MainFormSLS->hh_1[50]
 + nn[349]
 + (c2.v[5] + c2.v[21] + c2.v[37] + c2.v[53] + c2.v[69])*MainFormSLS->hh_1[30]
 + nn[576]
 + (c2.v[7] + c2.v[23] + c2.v[39] + c2.v[55] + c2.v[71])*MainFormSLS->hh_1[10]
 + nn[134]
 + (c2.v[9] + c2.v[25] + c2.v[41] + c2.v[57] + c2.v[73])*MainFormSLS->hh_1[150]
 + nn[577]
 + (c2.v[11] + c2.v[27] + c2.v[43] + c2.v[59] + c2.v[75])*MainFormSLS->hh_1[130]
 + nn[352]
 + (c2.v[13] + c2.v[29] + c2.v[45] + c2.v[61] + c2.v[77])*MainFormSLS->hh_1[110]
 + nn[578]
 + (c2.v[15] + c2.v[31] + c2.v[47] + c2.v[63] + c2.v[79])*MainFormSLS->hh_1[90];
s/=N_2;
out.push_back(s);

//отсчет 36
s= nn[118]
 + (c2.v[1] + c2.v[21] + c2.v[41] + c2.v[61])*MainFormSLS->hh_1[72]
 + nn[579]
 + (c2.v[3] + c2.v[23] + c2.v[43] + c2.v[63])*MainFormSLS->hh_1[56]
 + nn[580]
 + nn[121]
 + nn[581]
 + (c2.v[7] + c2.v[27] + c2.v[47] + c2.v[67])*MainFormSLS->hh_1[24]
 + nn[582]
 + (c2.v[9] + c2.v[29] + c2.v[49] + c2.v[69])*MainFormSLS->hh_1[8]
 + nn[124]
 + (c2.v[11] + c2.v[31] + c2.v[51] + c2.v[71])*MainFormSLS->hh_1[152]
 + nn[583]
 + (c2.v[13] + c2.v[33] + c2.v[53] + c2.v[73])*MainFormSLS->hh_1[136]
 + nn[584]
 + nn[127]
 + nn[585]
 + (c2.v[17] + c2.v[37] + c2.v[57] + c2.v[77])*MainFormSLS->hh_1[104]
 + nn[586]
 + (c2.v[19] + c2.v[39] + c2.v[59] + c2.v[79])*MainFormSLS->hh_1[88];
s/=N_2;
out.push_back(s);

//отсчет 37
s= nn[0]
 + c2.v[1]*MainFormSLS->hh_1[74]
 + nn[587]
 + c2.v[3]*MainFormSLS->hh_1[62]
 + nn[356]
 + nn[422]
 + nn[588]
 + c2.v[7]*MainFormSLS->hh_1[38]
 + nn[164]
 + c2.v[9]*MainFormSLS->hh_1[26]
 + nn[296]
 + c2.v[11]*MainFormSLS->hh_1[14]
 + nn[358]
 + c2.v[13]*MainFormSLS->hh_1[2]
 + nn[589]
 + nn[425]
 + nn[169]
 + c2.v[17]*MainFormSLS->hh_1[138]
 + nn[590]
 + c2.v[19]*MainFormSLS->hh_1[126]
 + nn[12]
 + c2.v[21]*MainFormSLS->hh_1[114]
 + nn[591]
 + c2.v[23]*MainFormSLS->hh_1[102]
 + nn[172]
 + nn[428]
 + nn[592]
 + c2.v[27]*MainFormSLS->hh_1[78]
 + nn[363]
 + c2.v[29]*MainFormSLS->hh_1[66]
 + nn[305]
 + c2.v[31]*MainFormSLS->hh_1[54]
 + nn[177]
 + c2.v[33]*MainFormSLS->hh_1[42]
 + nn[593]
 + nn[431]
 + nn[365]
 + c2.v[37]*MainFormSLS->hh_1[18]
 + nn[594]
 + c2.v[39]*MainFormSLS->hh_1[6]
 + nn[24]
 + c2.v[41]*MainFormSLS->hh_1[154]
 + nn[595]
 + c2.v[43]*MainFormSLS->hh_1[142]
 + nn[368]
 + nn[434]
 + nn[596]
 + c2.v[47]*MainFormSLS->hh_1[118]
 + nn[186]
 + c2.v[49]*MainFormSLS->hh_1[106]
 + nn[314]
 + c2.v[51]*MainFormSLS->hh_1[94]
 + nn[370]
 + c2.v[53]*MainFormSLS->hh_1[82]
 + nn[597]
 + nn[437]
 + nn[191]
 + c2.v[57]*MainFormSLS->hh_1[58]
 + nn[598]
 + c2.v[59]*MainFormSLS->hh_1[46]
 + nn[36]
 + c2.v[61]*MainFormSLS->hh_1[34]
 + nn[599]
 + c2.v[63]*MainFormSLS->hh_1[22]
 + nn[194]
 + nn[440]
 + nn[600]
 + c2.v[67]*MainFormSLS->hh_1[158]
 + nn[375]
 + c2.v[69]*MainFormSLS->hh_1[146]
 + nn[323]
 + c2.v[71]*MainFormSLS->hh_1[134]
 + nn[199]
 + c2.v[73]*MainFormSLS->hh_1[122]
 + nn[601]
 + nn[443]
 + nn[377]
 + c2.v[77]*MainFormSLS->hh_1[98]
 + nn[602]
 + c2.v[79]*MainFormSLS->hh_1[86];
s/=N_2;
out.push_back(s);

//отсчет 38
s= nn[48]
 + (c2.v[1] + c2.v[41])*MainFormSLS->hh_1[76]
 + nn[603]
 + (c2.v[3] + c2.v[43])*MainFormSLS->hh_1[68]
 + nn[380]
 + nn[140]
 + nn[604]
 + (c2.v[7] + c2.v[47])*MainFormSLS->hh_1[52]
 + nn[382]
 + (c2.v[9] + c2.v[49])*MainFormSLS->hh_1[44]
 + nn[143]
 + (c2.v[11] + c2.v[51])*MainFormSLS->hh_1[36]
 + nn[383]
 + (c2.v[13] + c2.v[53])*MainFormSLS->hh_1[28]
 + nn[605]
 + nn[146]
 + nn[385]
 + (c2.v[17] + c2.v[57])*MainFormSLS->hh_1[12]
 + nn[606]
 + (c2.v[19] + c2.v[59])*MainFormSLS->hh_1[4]
 + nn[60]
 + (c2.v[21] + c2.v[61])*MainFormSLS->hh_1[156]
 + nn[607]
 + (c2.v[23] + c2.v[63])*MainFormSLS->hh_1[148]
 + nn[388]
 + nn[151]
 + nn[608]
 + (c2.v[27] + c2.v[67])*MainFormSLS->hh_1[132]
 + nn[390]
 + (c2.v[29] + c2.v[69])*MainFormSLS->hh_1[124]
 + nn[154]
 + (c2.v[31] + c2.v[71])*MainFormSLS->hh_1[116]
 + nn[391]
 + (c2.v[33] + c2.v[73])*MainFormSLS->hh_1[108]
 + nn[609]
 + nn[157]
 + nn[393]
 + (c2.v[37] + c2.v[77])*MainFormSLS->hh_1[92]
 + nn[610]
 + (c2.v[39] + c2.v[79])*MainFormSLS->hh_1[84];
s/=N_2;
out.push_back(s);

//отсчет 39
s= nn[0]
 + c2.v[1]*MainFormSLS->hh_1[78]
 + nn[611]
 + c2.v[3]*MainFormSLS->hh_1[74]
 + nn[396]
 + nn[162]
 + nn[612]
 + c2.v[7]*MainFormSLS->hh_1[66]
 + nn[210]
 + c2.v[9]*MainFormSLS->hh_1[62]
 + nn[165]
 + c2.v[11]*MainFormSLS->hh_1[58]
 + nn[398]
 + c2.v[13]*MainFormSLS->hh_1[54]
 + nn[613]
 + nn[168]
 + nn[214]
 + c2.v[17]*MainFormSLS->hh_1[46]
 + nn[614]
 + c2.v[19]*MainFormSLS->hh_1[42]
 + nn[83]
 + c2.v[21]*MainFormSLS->hh_1[38]
 + nn[615]
 + c2.v[23]*MainFormSLS->hh_1[34]
 + nn[217]
 + nn[173]
 + nn[616]
 + c2.v[27]*MainFormSLS->hh_1[26]
 + nn[403]
 + c2.v[29]*MainFormSLS->hh_1[22]
 + nn[176]
 + c2.v[31]*MainFormSLS->hh_1[18]
 + nn[221]
 + c2.v[33]*MainFormSLS->hh_1[14]
 + nn[617]
 + nn[179]
 + nn[405]
 + c2.v[37]*MainFormSLS->hh_1[6]
 + nn[618]
 + c2.v[39]*MainFormSLS->hh_1[2]
 + nn[24]
 + c2.v[41]*MainFormSLS->hh_1[158]
 + nn[619]
 + c2.v[43]*MainFormSLS->hh_1[154]
 + nn[408]
 + nn[184]
 + nn[620]
 + c2.v[47]*MainFormSLS->hh_1[146]
 + nn[230]
 + c2.v[49]*MainFormSLS->hh_1[142]
 + nn[187]
 + c2.v[51]*MainFormSLS->hh_1[138]
 + nn[410]
 + c2.v[53]*MainFormSLS->hh_1[134]
 + nn[621]
 + nn[190]
 + nn[234]
 + c2.v[57]*MainFormSLS->hh_1[126]
 + nn[622]
 + c2.v[59]*MainFormSLS->hh_1[122]
 + nn[106]
 + c2.v[61]*MainFormSLS->hh_1[118]
 + nn[623]
 + c2.v[63]*MainFormSLS->hh_1[114]
 + nn[237]
 + nn[195]
 + nn[624]
 + c2.v[67]*MainFormSLS->hh_1[106]
 + nn[415]
 + c2.v[69]*MainFormSLS->hh_1[102]
 + nn[198]
 + c2.v[71]*MainFormSLS->hh_1[98]
 + nn[241]
 + c2.v[73]*MainFormSLS->hh_1[94]
 + nn[625]
 + nn[201]
 + nn[417]
 + c2.v[77]*MainFormSLS->hh_1[86]
 + nn[626]
 + c2.v[79]*MainFormSLS->hh_1[82];
s/=N_2;
out.push_back(s);

//отсчет 40
s= (c2.v[0] + c2.v[2] + c2.v[4] + c2.v[6] + c2.v[8] + c2.v[10] + c2.v[12] + c2.v[14] + c2.v[16] + c2.v[18] + c2.v[20] + c2.v[22] + c2.v[24] + c2.v[26] + c2.v[28] + c2.v[30] + c2.v[32] + c2.v[34] + c2.v[36] + c2.v[38] + c2.v[40] + c2.v[42] + c2.v[44] + c2.v[46] + c2.v[48] + c2.v[50] + c2.v[52] + c2.v[54] + c2.v[56] + c2.v[58] + c2.v[60] + c2.v[62] + c2.v[64] + c2.v[66] + c2.v[68] + c2.v[70] + c2.v[72] + c2.v[74] + c2.v[76] + c2.v[78])*MainFormSLS->hh_1[0]
 + (c2.v[1] + c2.v[3] + c2.v[5] + c2.v[7] + c2.v[9] + c2.v[11] + c2.v[13] + c2.v[15] + c2.v[17] + c2.v[19] + c2.v[21] + c2.v[23] + c2.v[25] + c2.v[27] + c2.v[29] + c2.v[31] + c2.v[33] + c2.v[35] + c2.v[37] + c2.v[39] + c2.v[41] + c2.v[43] + c2.v[45] + c2.v[47] + c2.v[49] + c2.v[51] + c2.v[53] + c2.v[55] + c2.v[57] + c2.v[59] + c2.v[61] + c2.v[63] + c2.v[65] + c2.v[67] + c2.v[69] + c2.v[71] + c2.v[73] + c2.v[75] + c2.v[77] + c2.v[79])*MainFormSLS->hh_1[80];
s/=N_2;
out.push_back(s);

//отсчет 41
s= nn[0]
 + c2.v[1]*MainFormSLS->hh_1[82]
 + nn[1]
 + c2.v[3]*MainFormSLS->hh_1[86]
 + nn[2]
 + nn[208]
 + nn[4]
 + c2.v[7]*MainFormSLS->hh_1[94]
 + nn[5]
 + c2.v[9]*MainFormSLS->hh_1[98]
 + nn[6]
 + c2.v[11]*MainFormSLS->hh_1[102]
 + nn[7]
 + c2.v[13]*MainFormSLS->hh_1[106]
 + nn[8]
 + nn[213]
 + nn[10]
 + c2.v[17]*MainFormSLS->hh_1[114]
 + nn[11]
 + c2.v[19]*MainFormSLS->hh_1[118]
 + nn[12]
 + c2.v[21]*MainFormSLS->hh_1[122]
 + nn[13]
 + c2.v[23]*MainFormSLS->hh_1[126]
 + nn[14]
 + nn[218]
 + nn[16]
 + c2.v[27]*MainFormSLS->hh_1[134]
 + nn[17]
 + c2.v[29]*MainFormSLS->hh_1[138]
 + nn[18]
 + c2.v[31]*MainFormSLS->hh_1[142]
 + nn[19]
 + c2.v[33]*MainFormSLS->hh_1[146]
 + nn[20]
 + nn[223]
 + nn[22]
 + c2.v[37]*MainFormSLS->hh_1[154]
 + nn[23]
 + c2.v[39]*MainFormSLS->hh_1[158]
 + nn[24]
 + c2.v[41]*MainFormSLS->hh_1[2]
 + nn[25]
 + c2.v[43]*MainFormSLS->hh_1[6]
 + nn[26]
 + nn[228]
 + nn[28]
 + c2.v[47]*MainFormSLS->hh_1[14]
 + nn[29]
 + c2.v[49]*MainFormSLS->hh_1[18]
 + nn[30]
 + c2.v[51]*MainFormSLS->hh_1[22]
 + nn[31]
 + c2.v[53]*MainFormSLS->hh_1[26]
 + nn[32]
 + nn[233]
 + nn[34]
 + c2.v[57]*MainFormSLS->hh_1[34]
 + nn[35]
 + c2.v[59]*MainFormSLS->hh_1[38]
 + nn[36]
 + c2.v[61]*MainFormSLS->hh_1[42]
 + nn[37]
 + c2.v[63]*MainFormSLS->hh_1[46]
 + nn[38]
 + nn[238]
 + nn[40]
 + c2.v[67]*MainFormSLS->hh_1[54]
 + nn[41]
 + c2.v[69]*MainFormSLS->hh_1[58]
 + nn[42]
 + c2.v[71]*MainFormSLS->hh_1[62]
 + nn[43]
 + c2.v[73]*MainFormSLS->hh_1[66]
 + nn[44]
 + nn[243]
 + nn[46]
 + c2.v[77]*MainFormSLS->hh_1[74]
 + nn[47]
 + c2.v[79]*MainFormSLS->hh_1[78];
s/=N_2;
out.push_back(s);

//отсчет 42
s= nn[48]
 + (c2.v[1] + c2.v[41])*MainFormSLS->hh_1[84]
 + nn[49]
 + (c2.v[3] + c2.v[43])*MainFormSLS->hh_1[92]
 + nn[50]
 + nn[474]
 + nn[52]
 + (c2.v[7] + c2.v[47])*MainFormSLS->hh_1[108]
 + nn[53]
 + (c2.v[9] + c2.v[49])*MainFormSLS->hh_1[116]
 + nn[54]
 + (c2.v[11] + c2.v[51])*MainFormSLS->hh_1[124]
 + nn[55]
 + (c2.v[13] + c2.v[53])*MainFormSLS->hh_1[132]
 + nn[56]
 + nn[477]
 + nn[58]
 + (c2.v[17] + c2.v[57])*MainFormSLS->hh_1[148]
 + nn[59]
 + (c2.v[19] + c2.v[59])*MainFormSLS->hh_1[156]
 + nn[60]
 + (c2.v[21] + c2.v[61])*MainFormSLS->hh_1[4]
 + nn[61]
 + (c2.v[23] + c2.v[63])*MainFormSLS->hh_1[12]
 + nn[62]
 + nn[480]
 + nn[64]
 + (c2.v[27] + c2.v[67])*MainFormSLS->hh_1[28]
 + nn[65]
 + (c2.v[29] + c2.v[69])*MainFormSLS->hh_1[36]
 + nn[66]
 + (c2.v[31] + c2.v[71])*MainFormSLS->hh_1[44]
 + nn[67]
 + (c2.v[33] + c2.v[73])*MainFormSLS->hh_1[52]
 + nn[68]
 + nn[483]
 + nn[70]
 + (c2.v[37] + c2.v[77])*MainFormSLS->hh_1[68]
 + nn[71]
 + (c2.v[39] + c2.v[79])*MainFormSLS->hh_1[76];
s/=N_2;
out.push_back(s);

//отсчет 43
s= nn[0]
 + c2.v[1]*MainFormSLS->hh_1[86]
 + nn[72]
 + c2.v[3]*MainFormSLS->hh_1[98]
 + nn[73]
 + nn[252]
 + nn[75]
 + c2.v[7]*MainFormSLS->hh_1[122]
 + nn[76]
 + c2.v[9]*MainFormSLS->hh_1[134]
 + nn[77]
 + c2.v[11]*MainFormSLS->hh_1[146]
 + nn[78]
 + c2.v[13]*MainFormSLS->hh_1[158]
 + nn[79]
 + nn[256]
 + nn[81]
 + c2.v[17]*MainFormSLS->hh_1[22]
 + nn[82]
 + c2.v[19]*MainFormSLS->hh_1[34]
 + nn[83]
 + c2.v[21]*MainFormSLS->hh_1[46]
 + nn[84]
 + c2.v[23]*MainFormSLS->hh_1[58]
 + nn[85]
 + nn[259]
 + nn[87]
 + c2.v[27]*MainFormSLS->hh_1[82]
 + nn[88]
 + c2.v[29]*MainFormSLS->hh_1[94]
 + nn[89]
 + c2.v[31]*MainFormSLS->hh_1[106]
 + nn[90]
 + c2.v[33]*MainFormSLS->hh_1[118]
 + nn[91]
 + nn[263]
 + nn[93]
 + c2.v[37]*MainFormSLS->hh_1[142]
 + nn[94]
 + c2.v[39]*MainFormSLS->hh_1[154]
 + nn[24]
 + c2.v[41]*MainFormSLS->hh_1[6]
 + nn[95]
 + c2.v[43]*MainFormSLS->hh_1[18]
 + nn[96]
 + nn[268]
 + nn[98]
 + c2.v[47]*MainFormSLS->hh_1[42]
 + nn[99]
 + c2.v[49]*MainFormSLS->hh_1[54]
 + nn[100]
 + c2.v[51]*MainFormSLS->hh_1[66]
 + nn[101]
 + c2.v[53]*MainFormSLS->hh_1[78]
 + nn[102]
 + nn[272]
 + nn[104]
 + c2.v[57]*MainFormSLS->hh_1[102]
 + nn[105]
 + c2.v[59]*MainFormSLS->hh_1[114]
 + nn[106]
 + c2.v[61]*MainFormSLS->hh_1[126]
 + nn[107]
 + c2.v[63]*MainFormSLS->hh_1[138]
 + nn[108]
 + nn[275]
 + nn[110]
 + c2.v[67]*MainFormSLS->hh_1[2]
 + nn[111]
 + c2.v[69]*MainFormSLS->hh_1[14]
 + nn[112]
 + c2.v[71]*MainFormSLS->hh_1[26]
 + nn[113]
 + c2.v[73]*MainFormSLS->hh_1[38]
 + nn[114]
 + nn[279]
 + nn[116]
 + c2.v[77]*MainFormSLS->hh_1[62]
 + nn[117]
 + c2.v[79]*MainFormSLS->hh_1[74];
s/=N_2;
out.push_back(s);

//отсчет 44
s= nn[118]
 + (c2.v[1] + c2.v[21] + c2.v[41] + c2.v[61])*MainFormSLS->hh_1[88]
 + nn[119]
 + (c2.v[3] + c2.v[23] + c2.v[43] + c2.v[63])*MainFormSLS->hh_1[104]
 + nn[120]
 + nn[284]
 + nn[122]
 + (c2.v[7] + c2.v[27] + c2.v[47] + c2.v[67])*MainFormSLS->hh_1[136]
 + nn[123]
 + (c2.v[9] + c2.v[29] + c2.v[49] + c2.v[69])*MainFormSLS->hh_1[152]
 + nn[124]
 + (c2.v[11] + c2.v[31] + c2.v[51] + c2.v[71])*MainFormSLS->hh_1[8]
 + nn[125]
 + (c2.v[13] + c2.v[33] + c2.v[53] + c2.v[73])*MainFormSLS->hh_1[24]
 + nn[126]
 + nn[289]
 + nn[128]
 + (c2.v[17] + c2.v[37] + c2.v[57] + c2.v[77])*MainFormSLS->hh_1[56]
 + nn[129]
 + (c2.v[19] + c2.v[39] + c2.v[59] + c2.v[79])*MainFormSLS->hh_1[72];
s/=N_2;
out.push_back(s);

//отсчет 45
s= nn[130]
 + (c2.v[1] + c2.v[17] + c2.v[33] + c2.v[49] + c2.v[65])*MainFormSLS->hh_1[90]
 + nn[131]
 + (c2.v[3] + c2.v[19] + c2.v[35] + c2.v[51] + c2.v[67])*MainFormSLS->hh_1[110]
 + nn[132]
 + (c2.v[5] + c2.v[21] + c2.v[37] + c2.v[53] + c2.v[69])*MainFormSLS->hh_1[130]
 + nn[133]
 + (c2.v[7] + c2.v[23] + c2.v[39] + c2.v[55] + c2.v[71])*MainFormSLS->hh_1[150]
 + nn[134]
 + (c2.v[9] + c2.v[25] + c2.v[41] + c2.v[57] + c2.v[73])*MainFormSLS->hh_1[10]
 + nn[135]
 + (c2.v[11] + c2.v[27] + c2.v[43] + c2.v[59] + c2.v[75])*MainFormSLS->hh_1[30]
 + nn[136]
 + (c2.v[13] + c2.v[29] + c2.v[45] + c2.v[61] + c2.v[77])*MainFormSLS->hh_1[50]
 + nn[137]
 + (c2.v[15] + c2.v[31] + c2.v[47] + c2.v[63] + c2.v[79])*MainFormSLS->hh_1[70];
s/=N_2;
out.push_back(s);

//отсчет 46
s= nn[48]
 + (c2.v[1] + c2.v[41])*MainFormSLS->hh_1[92]
 + nn[138]
 + (c2.v[3] + c2.v[43])*MainFormSLS->hh_1[116]
 + nn[139]
 + nn[330]
 + nn[141]
 + (c2.v[7] + c2.v[47])*MainFormSLS->hh_1[4]
 + nn[142]
 + (c2.v[9] + c2.v[49])*MainFormSLS->hh_1[28]
 + nn[143]
 + (c2.v[11] + c2.v[51])*MainFormSLS->hh_1[52]
 + nn[144]
 + (c2.v[13] + c2.v[53])*MainFormSLS->hh_1[76]
 + nn[145]
 + nn[335]
 + nn[147]
 + (c2.v[17] + c2.v[57])*MainFormSLS->hh_1[124]
 + nn[148]
 + (c2.v[19] + c2.v[59])*MainFormSLS->hh_1[148]
 + nn[60]
 + (c2.v[21] + c2.v[61])*MainFormSLS->hh_1[12]
 + nn[149]
 + (c2.v[23] + c2.v[63])*MainFormSLS->hh_1[36]
 + nn[150]
 + nn[340]
 + nn[152]
 + (c2.v[27] + c2.v[67])*MainFormSLS->hh_1[84]
 + nn[153]
 + (c2.v[29] + c2.v[69])*MainFormSLS->hh_1[108]
 + nn[154]
 + (c2.v[31] + c2.v[71])*MainFormSLS->hh_1[132]
 + nn[155]
 + (c2.v[33] + c2.v[73])*MainFormSLS->hh_1[156]
 + nn[156]
 + nn[345]
 + nn[158]
 + (c2.v[37] + c2.v[77])*MainFormSLS->hh_1[44]
 + nn[159]
 + (c2.v[39] + c2.v[79])*MainFormSLS->hh_1[68];
s/=N_2;
out.push_back(s);

//отсчет 47
s= nn[0]
 + c2.v[1]*MainFormSLS->hh_1[94]
 + nn[160]
 + c2.v[3]*MainFormSLS->hh_1[122]
 + nn[161]
 + nn[528]
 + nn[163]
 + c2.v[7]*MainFormSLS->hh_1[18]
 + nn[164]
 + c2.v[9]*MainFormSLS->hh_1[46]
 + nn[165]
 + c2.v[11]*MainFormSLS->hh_1[74]
 + nn[166]
 + c2.v[13]*MainFormSLS->hh_1[102]
 + nn[167]
 + nn[531]
 + nn[169]
 + c2.v[17]*MainFormSLS->hh_1[158]
 + nn[170]
 + c2.v[19]*MainFormSLS->hh_1[26]
 + nn[83]
 + c2.v[21]*MainFormSLS->hh_1[54]
 + nn[171]
 + c2.v[23]*MainFormSLS->hh_1[82]
 + nn[172]
 + nn[534]
 + nn[174]
 + c2.v[27]*MainFormSLS->hh_1[138]
 + nn[175]
 + c2.v[29]*MainFormSLS->hh_1[6]
 + nn[176]
 + c2.v[31]*MainFormSLS->hh_1[34]
 + nn[177]
 + c2.v[33]*MainFormSLS->hh_1[62]
 + nn[178]
 + nn[537]
 + nn[180]
 + c2.v[37]*MainFormSLS->hh_1[118]
 + nn[181]
 + c2.v[39]*MainFormSLS->hh_1[146]
 + nn[24]
 + c2.v[41]*MainFormSLS->hh_1[14]
 + nn[182]
 + c2.v[43]*MainFormSLS->hh_1[42]
 + nn[183]
 + nn[540]
 + nn[185]
 + c2.v[47]*MainFormSLS->hh_1[98]
 + nn[186]
 + c2.v[49]*MainFormSLS->hh_1[126]
 + nn[187]
 + c2.v[51]*MainFormSLS->hh_1[154]
 + nn[188]
 + c2.v[53]*MainFormSLS->hh_1[22]
 + nn[189]
 + nn[543]
 + nn[191]
 + c2.v[57]*MainFormSLS->hh_1[78]
 + nn[192]
 + c2.v[59]*MainFormSLS->hh_1[106]
 + nn[106]
 + c2.v[61]*MainFormSLS->hh_1[134]
 + nn[193]
 + c2.v[63]*MainFormSLS->hh_1[2]
 + nn[194]
 + nn[546]
 + nn[196]
 + c2.v[67]*MainFormSLS->hh_1[58]
 + nn[197]
 + c2.v[69]*MainFormSLS->hh_1[86]
 + nn[198]
 + c2.v[71]*MainFormSLS->hh_1[114]
 + nn[199]
 + c2.v[73]*MainFormSLS->hh_1[142]
 + nn[200]
 + nn[549]
 + nn[202]
 + c2.v[77]*MainFormSLS->hh_1[38]
 + nn[203]
 + c2.v[79]*MainFormSLS->hh_1[66];
s/=N_2;
out.push_back(s);

//отсчет 48
s= nn[354]
 + (c2.v[1] + c2.v[6] + c2.v[11] + c2.v[16] + c2.v[21] + c2.v[26] + c2.v[31] + c2.v[36] + c2.v[41] + c2.v[46] + c2.v[51] + c2.v[56] + c2.v[61] + c2.v[66] + c2.v[71] + c2.v[76])*MainFormSLS->hh_1[96]
 + (c2.v[2] + c2.v[7] + c2.v[12] + c2.v[17] + c2.v[22] + c2.v[27] + c2.v[32] + c2.v[37] + c2.v[42] + c2.v[47] + c2.v[52] + c2.v[57] + c2.v[62] + c2.v[67] + c2.v[72] + c2.v[77])*MainFormSLS->hh_1[32]
 + (c2.v[3] + c2.v[8] + c2.v[13] + c2.v[18] + c2.v[23] + c2.v[28] + c2.v[33] + c2.v[38] + c2.v[43] + c2.v[48] + c2.v[53] + c2.v[58] + c2.v[63] + c2.v[68] + c2.v[73] + c2.v[78])*MainFormSLS->hh_1[128]
 + (c2.v[4] + c2.v[9] + c2.v[14] + c2.v[19] + c2.v[24] + c2.v[29] + c2.v[34] + c2.v[39] + c2.v[44] + c2.v[49] + c2.v[54] + c2.v[59] + c2.v[64] + c2.v[69] + c2.v[74] + c2.v[79])*MainFormSLS->hh_1[64];
s/=N_2;
out.push_back(s);

//отсчет 49
s= nn[0]
 + c2.v[1]*MainFormSLS->hh_1[98]
 + nn[206]
 + c2.v[3]*MainFormSLS->hh_1[134]
 + nn[207]
 + nn[3]
 + nn[209]
 + c2.v[7]*MainFormSLS->hh_1[46]
 + nn[210]
 + c2.v[9]*MainFormSLS->hh_1[82]
 + nn[6]
 + c2.v[11]*MainFormSLS->hh_1[118]
 + nn[211]
 + c2.v[13]*MainFormSLS->hh_1[154]
 + nn[212]
 + nn[9]
 + nn[214]
 + c2.v[17]*MainFormSLS->hh_1[66]
 + nn[215]
 + c2.v[19]*MainFormSLS->hh_1[102]
 + nn[12]
 + c2.v[21]*MainFormSLS->hh_1[138]
 + nn[216]
 + c2.v[23]*MainFormSLS->hh_1[14]
 + nn[217]
 + nn[15]
 + nn[219]
 + c2.v[27]*MainFormSLS->hh_1[86]
 + nn[220]
 + c2.v[29]*MainFormSLS->hh_1[122]
 + nn[18]
 + c2.v[31]*MainFormSLS->hh_1[158]
 + nn[221]
 + c2.v[33]*MainFormSLS->hh_1[34]
 + nn[222]
 + nn[21]
 + nn[224]
 + c2.v[37]*MainFormSLS->hh_1[106]
 + nn[225]
 + c2.v[39]*MainFormSLS->hh_1[142]
 + nn[24]
 + c2.v[41]*MainFormSLS->hh_1[18]
 + nn[226]
 + c2.v[43]*MainFormSLS->hh_1[54]
 + nn[227]
 + nn[27]
 + nn[229]
 + c2.v[47]*MainFormSLS->hh_1[126]
 + nn[230]
 + c2.v[49]*MainFormSLS->hh_1[2]
 + nn[30]
 + c2.v[51]*MainFormSLS->hh_1[38]
 + nn[231]
 + c2.v[53]*MainFormSLS->hh_1[74]
 + nn[232]
 + nn[33]
 + nn[234]
 + c2.v[57]*MainFormSLS->hh_1[146]
 + nn[235]
 + c2.v[59]*MainFormSLS->hh_1[22]
 + nn[36]
 + c2.v[61]*MainFormSLS->hh_1[58]
 + nn[236]
 + c2.v[63]*MainFormSLS->hh_1[94]
 + nn[237]
 + nn[39]
 + nn[239]
 + c2.v[67]*MainFormSLS->hh_1[6]
 + nn[240]
 + c2.v[69]*MainFormSLS->hh_1[42]
 + nn[42]
 + c2.v[71]*MainFormSLS->hh_1[78]
 + nn[241]
 + c2.v[73]*MainFormSLS->hh_1[114]
 + nn[242]
 + nn[45]
 + nn[244]
 + c2.v[77]*MainFormSLS->hh_1[26]
 + nn[245]
 + c2.v[79]*MainFormSLS->hh_1[62];
s/=N_2;
out.push_back(s);

//отсчет 50
s= nn[246]
 + (c2.v[1] + c2.v[9] + c2.v[17] + c2.v[25] + c2.v[33] + c2.v[41] + c2.v[49] + c2.v[57] + c2.v[65] + c2.v[73])*MainFormSLS->hh_1[100]
 + nn[247]
 + (c2.v[3] + c2.v[11] + c2.v[19] + c2.v[27] + c2.v[35] + c2.v[43] + c2.v[51] + c2.v[59] + c2.v[67] + c2.v[75])*MainFormSLS->hh_1[140]
 + nn[248]
 + (c2.v[5] + c2.v[13] + c2.v[21] + c2.v[29] + c2.v[37] + c2.v[45] + c2.v[53] + c2.v[61] + c2.v[69] + c2.v[77])*MainFormSLS->hh_1[20]
 + nn[249]
 + (c2.v[7] + c2.v[15] + c2.v[23] + c2.v[31] + c2.v[39] + c2.v[47] + c2.v[55] + c2.v[63] + c2.v[71] + c2.v[79])*MainFormSLS->hh_1[60];
s/=N_2;
out.push_back(s);

//отсчет 51
s= nn[0]
 + c2.v[1]*MainFormSLS->hh_1[102]
 + nn[250]
 + c2.v[3]*MainFormSLS->hh_1[146]
 + nn[251]
 + nn[74]
 + nn[253]
 + c2.v[7]*MainFormSLS->hh_1[74]
 + nn[5]
 + c2.v[9]*MainFormSLS->hh_1[118]
 + nn[77]
 + c2.v[11]*MainFormSLS->hh_1[2]
 + nn[254]
 + c2.v[13]*MainFormSLS->hh_1[46]
 + nn[255]
 + nn[80]
 + nn[10]
 + c2.v[17]*MainFormSLS->hh_1[134]
 + nn[257]
 + c2.v[19]*MainFormSLS->hh_1[18]
 + nn[83]
 + c2.v[21]*MainFormSLS->hh_1[62]
 + nn[258]
 + c2.v[23]*MainFormSLS->hh_1[106]
 + nn[14]
 + nn[86]
 + nn[260]
 + c2.v[27]*MainFormSLS->hh_1[34]
 + nn[261]
 + c2.v[29]*MainFormSLS->hh_1[78]
 + nn[89]
 + c2.v[31]*MainFormSLS->hh_1[122]
 + nn[19]
 + c2.v[33]*MainFormSLS->hh_1[6]
 + nn[262]
 + nn[92]
 + nn[264]
 + c2.v[37]*MainFormSLS->hh_1[94]
 + nn[265]
 + c2.v[39]*MainFormSLS->hh_1[138]
 + nn[24]
 + c2.v[41]*MainFormSLS->hh_1[22]
 + nn[266]
 + c2.v[43]*MainFormSLS->hh_1[66]
 + nn[267]
 + nn[97]
 + nn[269]
 + c2.v[47]*MainFormSLS->hh_1[154]
 + nn[29]
 + c2.v[49]*MainFormSLS->hh_1[38]
 + nn[100]
 + c2.v[51]*MainFormSLS->hh_1[82]
 + nn[270]
 + c2.v[53]*MainFormSLS->hh_1[126]
 + nn[271]
 + nn[103]
 + nn[34]
 + c2.v[57]*MainFormSLS->hh_1[54]
 + nn[273]
 + c2.v[59]*MainFormSLS->hh_1[98]
 + nn[106]
 + c2.v[61]*MainFormSLS->hh_1[142]
 + nn[274]
 + c2.v[63]*MainFormSLS->hh_1[26]
 + nn[38]
 + nn[109]
 + nn[276]
 + c2.v[67]*MainFormSLS->hh_1[114]
 + nn[277]
 + c2.v[69]*MainFormSLS->hh_1[158]
 + nn[112]
 + c2.v[71]*MainFormSLS->hh_1[42]
 + nn[43]
 + c2.v[73]*MainFormSLS->hh_1[86]
 + nn[278]
 + nn[115]
 + nn[280]
 + c2.v[77]*MainFormSLS->hh_1[14]
 + nn[281]
 + c2.v[79]*MainFormSLS->hh_1[58];
s/=N_2;
out.push_back(s);

//отсчет 52
s= nn[118]
 + (c2.v[1] + c2.v[21] + c2.v[41] + c2.v[61])*MainFormSLS->hh_1[104]
 + nn[282]
 + (c2.v[3] + c2.v[23] + c2.v[43] + c2.v[63])*MainFormSLS->hh_1[152]
 + nn[283]
 + nn[121]
 + nn[285]
 + (c2.v[7] + c2.v[27] + c2.v[47] + c2.v[67])*MainFormSLS->hh_1[88]
 + nn[286]
 + (c2.v[9] + c2.v[29] + c2.v[49] + c2.v[69])*MainFormSLS->hh_1[136]
 + nn[124]
 + (c2.v[11] + c2.v[31] + c2.v[51] + c2.v[71])*MainFormSLS->hh_1[24]
 + nn[287]
 + (c2.v[13] + c2.v[33] + c2.v[53] + c2.v[73])*MainFormSLS->hh_1[72]
 + nn[288]
 + nn[127]
 + nn[290]
 + (c2.v[17] + c2.v[37] + c2.v[57] + c2.v[77])*MainFormSLS->hh_1[8]
 + nn[291]
 + (c2.v[19] + c2.v[39] + c2.v[59] + c2.v[79])*MainFormSLS->hh_1[56];
s/=N_2;
out.push_back(s);

//отсчет 53
s= nn[0]
 + c2.v[1]*MainFormSLS->hh_1[106]
 + nn[292]
 + c2.v[3]*MainFormSLS->hh_1[158]
 + nn[293]
 + nn[422]
 + nn[295]
 + c2.v[7]*MainFormSLS->hh_1[102]
 + nn[76]
 + c2.v[9]*MainFormSLS->hh_1[154]
 + nn[296]
 + c2.v[11]*MainFormSLS->hh_1[46]
 + nn[297]
 + c2.v[13]*MainFormSLS->hh_1[98]
 + nn[298]
 + nn[425]
 + nn[81]
 + c2.v[17]*MainFormSLS->hh_1[42]
 + nn[300]
 + c2.v[19]*MainFormSLS->hh_1[94]
 + nn[12]
 + c2.v[21]*MainFormSLS->hh_1[146]
 + nn[301]
 + c2.v[23]*MainFormSLS->hh_1[38]
 + nn[85]
 + nn[428]
 + nn[303]
 + c2.v[27]*MainFormSLS->hh_1[142]
 + nn[304]
 + c2.v[29]*MainFormSLS->hh_1[34]
 + nn[305]
 + c2.v[31]*MainFormSLS->hh_1[86]
 + nn[90]
 + c2.v[33]*MainFormSLS->hh_1[138]
 + nn[306]
 + nn[431]
 + nn[308]
 + c2.v[37]*MainFormSLS->hh_1[82]
 + nn[309]
 + c2.v[39]*MainFormSLS->hh_1[134]
 + nn[24]
 + c2.v[41]*MainFormSLS->hh_1[26]
 + nn[310]
 + c2.v[43]*MainFormSLS->hh_1[78]
 + nn[311]
 + nn[434]
 + nn[313]
 + c2.v[47]*MainFormSLS->hh_1[22]
 + nn[99]
 + c2.v[49]*MainFormSLS->hh_1[74]
 + nn[314]
 + c2.v[51]*MainFormSLS->hh_1[126]
 + nn[315]
 + c2.v[53]*MainFormSLS->hh_1[18]
 + nn[316]
 + nn[437]
 + nn[104]
 + c2.v[57]*MainFormSLS->hh_1[122]
 + nn[318]
 + c2.v[59]*MainFormSLS->hh_1[14]
 + nn[36]
 + c2.v[61]*MainFormSLS->hh_1[66]
 + nn[319]
 + c2.v[63]*MainFormSLS->hh_1[118]
 + nn[108]
 + nn[440]
 + nn[321]
 + c2.v[67]*MainFormSLS->hh_1[62]
 + nn[322]
 + c2.v[69]*MainFormSLS->hh_1[114]
 + nn[323]
 + c2.v[71]*MainFormSLS->hh_1[6]
 + nn[113]
 + c2.v[73]*MainFormSLS->hh_1[58]
 + nn[324]
 + nn[443]
 + nn[326]
 + c2.v[77]*MainFormSLS->hh_1[2]
 + nn[327]
 + c2.v[79]*MainFormSLS->hh_1[54];
s/=N_2;
out.push_back(s);

//отсчет 54
s= nn[48]
 + (c2.v[1] + c2.v[41])*MainFormSLS->hh_1[108]
 + nn[328]
 + (c2.v[3] + c2.v[43])*MainFormSLS->hh_1[4]
 + nn[329]
 + nn[140]
 + nn[331]
 + (c2.v[7] + c2.v[47])*MainFormSLS->hh_1[116]
 + nn[332]
 + (c2.v[9] + c2.v[49])*MainFormSLS->hh_1[12]
 + nn[143]
 + (c2.v[11] + c2.v[51])*MainFormSLS->hh_1[68]
 + nn[333]
 + (c2.v[13] + c2.v[53])*MainFormSLS->hh_1[124]
 + nn[334]
 + nn[146]
 + nn[336]
 + (c2.v[17] + c2.v[57])*MainFormSLS->hh_1[76]
 + nn[337]
 + (c2.v[19] + c2.v[59])*MainFormSLS->hh_1[132]
 + nn[60]
 + (c2.v[21] + c2.v[61])*MainFormSLS->hh_1[28]
 + nn[338]
 + (c2.v[23] + c2.v[63])*MainFormSLS->hh_1[84]
 + nn[339]
 + nn[151]
 + nn[341]
 + (c2.v[27] + c2.v[67])*MainFormSLS->hh_1[36]
 + nn[342]
 + (c2.v[29] + c2.v[69])*MainFormSLS->hh_1[92]
 + nn[154]
 + (c2.v[31] + c2.v[71])*MainFormSLS->hh_1[148]
 + nn[343]
 + (c2.v[33] + c2.v[73])*MainFormSLS->hh_1[44]
 + nn[344]
 + nn[157]
 + nn[346]
 + (c2.v[37] + c2.v[77])*MainFormSLS->hh_1[156]
 + nn[347]
 + (c2.v[39] + c2.v[79])*MainFormSLS->hh_1[52];
s/=N_2;
out.push_back(s);

//отсчет 55
s= nn[130]
 + (c2.v[1] + c2.v[17] + c2.v[33] + c2.v[49] + c2.v[65])*MainFormSLS->hh_1[110]
 + nn[348]
 + (c2.v[3] + c2.v[19] + c2.v[35] + c2.v[51] + c2.v[67])*MainFormSLS->hh_1[10]
 + nn[349]
 + (c2.v[5] + c2.v[21] + c2.v[37] + c2.v[53] + c2.v[69])*MainFormSLS->hh_1[70]
 + nn[350]
 + (c2.v[7] + c2.v[23] + c2.v[39] + c2.v[55] + c2.v[71])*MainFormSLS->hh_1[130]
 + nn[134]
 + (c2.v[9] + c2.v[25] + c2.v[41] + c2.v[57] + c2.v[73])*MainFormSLS->hh_1[30]
 + nn[351]
 + (c2.v[11] + c2.v[27] + c2.v[43] + c2.v[59] + c2.v[75])*MainFormSLS->hh_1[90]
 + nn[352]
 + (c2.v[13] + c2.v[29] + c2.v[45] + c2.v[61] + c2.v[77])*MainFormSLS->hh_1[150]
 + nn[353]
 + (c2.v[15] + c2.v[31] + c2.v[47] + c2.v[63] + c2.v[79])*MainFormSLS->hh_1[50];
s/=N_2;
out.push_back(s);

//отсчет 56
s= nn[204]
 + (c2.v[1] + c2.v[11] + c2.v[21] + c2.v[31] + c2.v[41] + c2.v[51] + c2.v[61] + c2.v[71])*MainFormSLS->hh_1[112]
 + (c2.v[2] + c2.v[12] + c2.v[22] + c2.v[32] + c2.v[42] + c2.v[52] + c2.v[62] + c2.v[72])*MainFormSLS->hh_1[64]
 + (c2.v[3] + c2.v[13] + c2.v[23] + c2.v[33] + c2.v[43] + c2.v[53] + c2.v[63] + c2.v[73])*MainFormSLS->hh_1[16]
 + (c2.v[4] + c2.v[14] + c2.v[24] + c2.v[34] + c2.v[44] + c2.v[54] + c2.v[64] + c2.v[74])*MainFormSLS->hh_1[128]
 + nn[205]
 + (c2.v[6] + c2.v[16] + c2.v[26] + c2.v[36] + c2.v[46] + c2.v[56] + c2.v[66] + c2.v[76])*MainFormSLS->hh_1[32]
 + (c2.v[7] + c2.v[17] + c2.v[27] + c2.v[37] + c2.v[47] + c2.v[57] + c2.v[67] + c2.v[77])*MainFormSLS->hh_1[144]
 + (c2.v[8] + c2.v[18] + c2.v[28] + c2.v[38] + c2.v[48] + c2.v[58] + c2.v[68] + c2.v[78])*MainFormSLS->hh_1[96]
 + (c2.v[9] + c2.v[19] + c2.v[29] + c2.v[39] + c2.v[49] + c2.v[59] + c2.v[69] + c2.v[79])*MainFormSLS->hh_1[48];
s/=N_2;
out.push_back(s);

//отсчет 57
s= nn[0]
 + c2.v[1]*MainFormSLS->hh_1[114]
 + nn[355]
 + c2.v[3]*MainFormSLS->hh_1[22]
 + nn[356]
 + nn[208]
 + nn[357]
 + c2.v[7]*MainFormSLS->hh_1[158]
 + nn[164]
 + c2.v[9]*MainFormSLS->hh_1[66]
 + nn[6]
 + c2.v[11]*MainFormSLS->hh_1[134]
 + nn[358]
 + c2.v[13]*MainFormSLS->hh_1[42]
 + nn[359]
 + nn[213]
 + nn[169]
 + c2.v[17]*MainFormSLS->hh_1[18]
 + nn[360]
 + c2.v[19]*MainFormSLS->hh_1[86]
 + nn[12]
 + c2.v[21]*MainFormSLS->hh_1[154]
 + nn[361]
 + c2.v[23]*MainFormSLS->hh_1[62]
 + nn[172]
 + nn[218]
 + nn[362]
 + c2.v[27]*MainFormSLS->hh_1[38]
 + nn[363]
 + c2.v[29]*MainFormSLS->hh_1[106]
 + nn[18]
 + c2.v[31]*MainFormSLS->hh_1[14]
 + nn[177]
 + c2.v[33]*MainFormSLS->hh_1[82]
 + nn[364]
 + nn[223]
 + nn[365]
 + c2.v[37]*MainFormSLS->hh_1[58]
 + nn[366]
 + c2.v[39]*MainFormSLS->hh_1[126]
 + nn[24]
 + c2.v[41]*MainFormSLS->hh_1[34]
 + nn[367]
 + c2.v[43]*MainFormSLS->hh_1[102]
 + nn[368]
 + nn[228]
 + nn[369]
 + c2.v[47]*MainFormSLS->hh_1[78]
 + nn[186]
 + c2.v[49]*MainFormSLS->hh_1[146]
 + nn[30]
 + c2.v[51]*MainFormSLS->hh_1[54]
 + nn[370]
 + c2.v[53]*MainFormSLS->hh_1[122]
 + nn[371]
 + nn[233]
 + nn[191]
 + c2.v[57]*MainFormSLS->hh_1[98]
 + nn[372]
 + c2.v[59]*MainFormSLS->hh_1[6]
 + nn[36]
 + c2.v[61]*MainFormSLS->hh_1[74]
 + nn[373]
 + c2.v[63]*MainFormSLS->hh_1[142]
 + nn[194]
 + nn[238]
 + nn[374]
 + c2.v[67]*MainFormSLS->hh_1[118]
 + nn[375]
 + c2.v[69]*MainFormSLS->hh_1[26]
 + nn[42]
 + c2.v[71]*MainFormSLS->hh_1[94]
 + nn[199]
 + c2.v[73]*MainFormSLS->hh_1[2]
 + nn[376]
 + nn[243]
 + nn[377]
 + c2.v[77]*MainFormSLS->hh_1[138]
 + nn[378]
 + c2.v[79]*MainFormSLS->hh_1[46];
s/=N_2;
out.push_back(s);

//отсчет 58
s= nn[48]
 + (c2.v[1] + c2.v[41])*MainFormSLS->hh_1[116]
 + nn[379]
 + (c2.v[3] + c2.v[43])*MainFormSLS->hh_1[28]
 + nn[380]
 + nn[474]
 + nn[381]
 + (c2.v[7] + c2.v[47])*MainFormSLS->hh_1[12]
 + nn[382]
 + (c2.v[9] + c2.v[49])*MainFormSLS->hh_1[84]
 + nn[54]
 + (c2.v[11] + c2.v[51])*MainFormSLS->hh_1[156]
 + nn[383]
 + (c2.v[13] + c2.v[53])*MainFormSLS->hh_1[68]
 + nn[384]
 + nn[477]
 + nn[385]
 + (c2.v[17] + c2.v[57])*MainFormSLS->hh_1[52]
 + nn[386]
 + (c2.v[19] + c2.v[59])*MainFormSLS->hh_1[124]
 + nn[60]
 + (c2.v[21] + c2.v[61])*MainFormSLS->hh_1[36]
 + nn[387]
 + (c2.v[23] + c2.v[63])*MainFormSLS->hh_1[108]
 + nn[388]
 + nn[480]
 + nn[389]
 + (c2.v[27] + c2.v[67])*MainFormSLS->hh_1[92]
 + nn[390]
 + (c2.v[29] + c2.v[69])*MainFormSLS->hh_1[4]
 + nn[66]
 + (c2.v[31] + c2.v[71])*MainFormSLS->hh_1[76]
 + nn[391]
 + (c2.v[33] + c2.v[73])*MainFormSLS->hh_1[148]
 + nn[392]
 + nn[483]
 + nn[393]
 + (c2.v[37] + c2.v[77])*MainFormSLS->hh_1[132]
 + nn[394]
 + (c2.v[39] + c2.v[79])*MainFormSLS->hh_1[44];
s/=N_2;
out.push_back(s);

//отсчет 59
s= nn[0]
 + c2.v[1]*MainFormSLS->hh_1[118]
 + nn[395]
 + c2.v[3]*MainFormSLS->hh_1[34]
 + nn[396]
 + nn[252]
 + nn[397]
 + c2.v[7]*MainFormSLS->hh_1[26]
 + nn[210]
 + c2.v[9]*MainFormSLS->hh_1[102]
 + nn[77]
 + c2.v[11]*MainFormSLS->hh_1[18]
 + nn[398]
 + c2.v[13]*MainFormSLS->hh_1[94]
 + nn[399]
 + nn[256]
 + nn[214]
 + c2.v[17]*MainFormSLS->hh_1[86]
 + nn[400]
 + c2.v[19]*MainFormSLS->hh_1[2]
 + nn[83]
 + c2.v[21]*MainFormSLS->hh_1[78]
 + nn[401]
 + c2.v[23]*MainFormSLS->hh_1[154]
 + nn[217]
 + nn[259]
 + nn[402]
 + c2.v[27]*MainFormSLS->hh_1[146]
 + nn[403]
 + c2.v[29]*MainFormSLS->hh_1[62]
 + nn[89]
 + c2.v[31]*MainFormSLS->hh_1[138]
 + nn[221]
 + c2.v[33]*MainFormSLS->hh_1[54]
 + nn[404]
 + nn[263]
 + nn[405]
 + c2.v[37]*MainFormSLS->hh_1[46]
 + nn[406]
 + c2.v[39]*MainFormSLS->hh_1[122]
 + nn[24]
 + c2.v[41]*MainFormSLS->hh_1[38]
 + nn[407]
 + c2.v[43]*MainFormSLS->hh_1[114]
 + nn[408]
 + nn[268]
 + nn[409]
 + c2.v[47]*MainFormSLS->hh_1[106]
 + nn[230]
 + c2.v[49]*MainFormSLS->hh_1[22]
 + nn[100]
 + c2.v[51]*MainFormSLS->hh_1[98]
 + nn[410]
 + c2.v[53]*MainFormSLS->hh_1[14]
 + nn[411]
 + nn[272]
 + nn[234]
 + c2.v[57]*MainFormSLS->hh_1[6]
 + nn[412]
 + c2.v[59]*MainFormSLS->hh_1[82]
 + nn[106]
 + c2.v[61]*MainFormSLS->hh_1[158]
 + nn[413]
 + c2.v[63]*MainFormSLS->hh_1[74]
 + nn[237]
 + nn[275]
 + nn[414]
 + c2.v[67]*MainFormSLS->hh_1[66]
 + nn[415]
 + c2.v[69]*MainFormSLS->hh_1[142]
 + nn[112]
 + c2.v[71]*MainFormSLS->hh_1[58]
 + nn[241]
 + c2.v[73]*MainFormSLS->hh_1[134]
 + nn[416]
 + nn[279]
 + nn[417]
 + c2.v[77]*MainFormSLS->hh_1[126]
 + nn[418]
 + c2.v[79]*MainFormSLS->hh_1[42];
s/=N_2;
out.push_back(s);

//отсчет 60
s= nn[419]
 + (c2.v[1] + c2.v[5] + c2.v[9] + c2.v[13] + c2.v[17] + c2.v[21] + c2.v[25] + c2.v[29] + c2.v[33] + c2.v[37] + c2.v[41] + c2.v[45] + c2.v[49] + c2.v[53] + c2.v[57] + c2.v[61] + c2.v[65] + c2.v[69] + c2.v[73] + c2.v[77])*MainFormSLS->hh_1[120]
 + nn[420]
 + (c2.v[3] + c2.v[7] + c2.v[11] + c2.v[15] + c2.v[19] + c2.v[23] + c2.v[27] + c2.v[31] + c2.v[35] + c2.v[39] + c2.v[43] + c2.v[47] + c2.v[51] + c2.v[55] + c2.v[59] + c2.v[63] + c2.v[67] + c2.v[71] + c2.v[75] + c2.v[79])*MainFormSLS->hh_1[40];
s/=N_2;
out.push_back(s);

//отсчет 61
s= nn[0]
 + c2.v[1]*MainFormSLS->hh_1[122]
 + nn[421]
 + c2.v[3]*MainFormSLS->hh_1[46]
 + nn[2]
 + nn[294]
 + nn[423]
 + c2.v[7]*MainFormSLS->hh_1[54]
 + nn[5]
 + c2.v[9]*MainFormSLS->hh_1[138]
 + nn[296]
 + c2.v[11]*MainFormSLS->hh_1[62]
 + nn[7]
 + c2.v[13]*MainFormSLS->hh_1[146]
 + nn[424]
 + nn[299]
 + nn[10]
 + c2.v[17]*MainFormSLS->hh_1[154]
 + nn[426]
 + c2.v[19]*MainFormSLS->hh_1[78]
 + nn[12]
 + c2.v[21]*MainFormSLS->hh_1[2]
 + nn[427]
 + c2.v[23]*MainFormSLS->hh_1[86]
 + nn[14]
 + nn[302]
 + nn[429]
 + c2.v[27]*MainFormSLS->hh_1[94]
 + nn[17]
 + c2.v[29]*MainFormSLS->hh_1[18]
 + nn[305]
 + c2.v[31]*MainFormSLS->hh_1[102]
 + nn[19]
 + c2.v[33]*MainFormSLS->hh_1[26]
 + nn[430]
 + nn[307]
 + nn[22]
 + c2.v[37]*MainFormSLS->hh_1[34]
 + nn[432]
 + c2.v[39]*MainFormSLS->hh_1[118]
 + nn[24]
 + c2.v[41]*MainFormSLS->hh_1[42]
 + nn[433]
 + c2.v[43]*MainFormSLS->hh_1[126]
 + nn[26]
 + nn[312]
 + nn[435]
 + c2.v[47]*MainFormSLS->hh_1[134]
 + nn[29]
 + c2.v[49]*MainFormSLS->hh_1[58]
 + nn[314]
 + c2.v[51]*MainFormSLS->hh_1[142]
 + nn[31]
 + c2.v[53]*MainFormSLS->hh_1[66]
 + nn[436]
 + nn[317]
 + nn[34]
 + c2.v[57]*MainFormSLS->hh_1[74]
 + nn[438]
 + c2.v[59]*MainFormSLS->hh_1[158]
 + nn[36]
 + c2.v[61]*MainFormSLS->hh_1[82]
 + nn[439]
 + c2.v[63]*MainFormSLS->hh_1[6]
 + nn[38]
 + nn[320]
 + nn[441]
 + c2.v[67]*MainFormSLS->hh_1[14]
 + nn[41]
 + c2.v[69]*MainFormSLS->hh_1[98]
 + nn[323]
 + c2.v[71]*MainFormSLS->hh_1[22]
 + nn[43]
 + c2.v[73]*MainFormSLS->hh_1[106]
 + nn[442]
 + nn[325]
 + nn[46]
 + c2.v[77]*MainFormSLS->hh_1[114]
 + nn[444]
 + c2.v[79]*MainFormSLS->hh_1[38];
s/=N_2;
out.push_back(s);

//отсчет 62
s= nn[48]
 + (c2.v[1] + c2.v[41])*MainFormSLS->hh_1[124]
 + nn[445]
 + (c2.v[3] + c2.v[43])*MainFormSLS->hh_1[52]
 + nn[50]
 + nn[330]
 + nn[446]
 + (c2.v[7] + c2.v[47])*MainFormSLS->hh_1[68]
 + nn[53]
 + (c2.v[9] + c2.v[49])*MainFormSLS->hh_1[156]
 + nn[143]
 + (c2.v[11] + c2.v[51])*MainFormSLS->hh_1[84]
 + nn[55]
 + (c2.v[13] + c2.v[53])*MainFormSLS->hh_1[12]
 + nn[447]
 + nn[335]
 + nn[58]
 + (c2.v[17] + c2.v[57])*MainFormSLS->hh_1[28]
 + nn[448]
 + (c2.v[19] + c2.v[59])*MainFormSLS->hh_1[116]
 + nn[60]
 + (c2.v[21] + c2.v[61])*MainFormSLS->hh_1[44]
 + nn[449]
 + (c2.v[23] + c2.v[63])*MainFormSLS->hh_1[132]
 + nn[62]
 + nn[340]
 + nn[450]
 + (c2.v[27] + c2.v[67])*MainFormSLS->hh_1[148]
 + nn[65]
 + (c2.v[29] + c2.v[69])*MainFormSLS->hh_1[76]
 + nn[154]
 + (c2.v[31] + c2.v[71])*MainFormSLS->hh_1[4]
 + nn[67]
 + (c2.v[33] + c2.v[73])*MainFormSLS->hh_1[92]
 + nn[451]
 + nn[345]
 + nn[70]
 + (c2.v[37] + c2.v[77])*MainFormSLS->hh_1[108]
 + nn[452]
 + (c2.v[39] + c2.v[79])*MainFormSLS->hh_1[36];
s/=N_2;
out.push_back(s);

//отсчет 63
s= nn[0]
 + c2.v[1]*MainFormSLS->hh_1[126]
 + nn[453]
 + c2.v[3]*MainFormSLS->hh_1[58]
 + nn[73]
 + nn[528]
 + nn[454]
 + c2.v[7]*MainFormSLS->hh_1[82]
 + nn[76]
 + c2.v[9]*MainFormSLS->hh_1[14]
 + nn[165]
 + c2.v[11]*MainFormSLS->hh_1[106]
 + nn[78]
 + c2.v[13]*MainFormSLS->hh_1[38]
 + nn[455]
 + nn[531]
 + nn[81]
 + c2.v[17]*MainFormSLS->hh_1[62]
 + nn[456]
 + c2.v[19]*MainFormSLS->hh_1[154]
 + nn[83]
 + c2.v[21]*MainFormSLS->hh_1[86]
 + nn[457]
 + c2.v[23]*MainFormSLS->hh_1[18]
 + nn[85]
 + nn[534]
 + nn[458]
 + c2.v[27]*MainFormSLS->hh_1[42]
 + nn[88]
 + c2.v[29]*MainFormSLS->hh_1[134]
 + nn[176]
 + c2.v[31]*MainFormSLS->hh_1[66]
 + nn[90]
 + c2.v[33]*MainFormSLS->hh_1[158]
 + nn[459]
 + nn[537]
 + nn[93]
 + c2.v[37]*MainFormSLS->hh_1[22]
 + nn[460]
 + c2.v[39]*MainFormSLS->hh_1[114]
 + nn[24]
 + c2.v[41]*MainFormSLS->hh_1[46]
 + nn[461]
 + c2.v[43]*MainFormSLS->hh_1[138]
 + nn[96]
 + nn[540]
 + nn[462]
 + c2.v[47]*MainFormSLS->hh_1[2]
 + nn[99]
 + c2.v[49]*MainFormSLS->hh_1[94]
 + nn[187]
 + c2.v[51]*MainFormSLS->hh_1[26]
 + nn[101]
 + c2.v[53]*MainFormSLS->hh_1[118]
 + nn[463]
 + nn[543]
 + nn[104]
 + c2.v[57]*MainFormSLS->hh_1[142]
 + nn[464]
 + c2.v[59]*MainFormSLS->hh_1[74]
 + nn[106]
 + c2.v[61]*MainFormSLS->hh_1[6]
 + nn[465]
 + c2.v[63]*MainFormSLS->hh_1[98]
 + nn[108]
 + nn[546]
 + nn[466]
 + c2.v[67]*MainFormSLS->hh_1[122]
 + nn[111]
 + c2.v[69]*MainFormSLS->hh_1[54]
 + nn[198]
 + c2.v[71]*MainFormSLS->hh_1[146]
 + nn[113]
 + c2.v[73]*MainFormSLS->hh_1[78]
 + nn[467]
 + nn[549]
 + nn[116]
 + c2.v[77]*MainFormSLS->hh_1[102]
 + nn[468]
 + c2.v[79]*MainFormSLS->hh_1[34];
s/=N_2;
out.push_back(s);

//отсчет 64
s= nn[354]
 + (c2.v[1] + c2.v[6] + c2.v[11] + c2.v[16] + c2.v[21] + c2.v[26] + c2.v[31] + c2.v[36] + c2.v[41] + c2.v[46] + c2.v[51] + c2.v[56] + c2.v[61] + c2.v[66] + c2.v[71] + c2.v[76])*MainFormSLS->hh_1[128]
 + (c2.v[2] + c2.v[7] + c2.v[12] + c2.v[17] + c2.v[22] + c2.v[27] + c2.v[32] + c2.v[37] + c2.v[42] + c2.v[47] + c2.v[52] + c2.v[57] + c2.v[62] + c2.v[67] + c2.v[72] + c2.v[77])*MainFormSLS->hh_1[96]
 + (c2.v[3] + c2.v[8] + c2.v[13] + c2.v[18] + c2.v[23] + c2.v[28] + c2.v[33] + c2.v[38] + c2.v[43] + c2.v[48] + c2.v[53] + c2.v[58] + c2.v[63] + c2.v[68] + c2.v[73] + c2.v[78])*MainFormSLS->hh_1[64]
 + (c2.v[4] + c2.v[9] + c2.v[14] + c2.v[19] + c2.v[24] + c2.v[29] + c2.v[34] + c2.v[39] + c2.v[44] + c2.v[49] + c2.v[54] + c2.v[59] + c2.v[64] + c2.v[69] + c2.v[74] + c2.v[79])*MainFormSLS->hh_1[32];
s/=N_2;
out.push_back(s);

//отсчет 65
s= nn[130]
 + (c2.v[1] + c2.v[17] + c2.v[33] + c2.v[49] + c2.v[65])*MainFormSLS->hh_1[130]
 + nn[469]
 + (c2.v[3] + c2.v[19] + c2.v[35] + c2.v[51] + c2.v[67])*MainFormSLS->hh_1[70]
 + nn[132]
 + (c2.v[5] + c2.v[21] + c2.v[37] + c2.v[53] + c2.v[69])*MainFormSLS->hh_1[10]
 + nn[470]
 + (c2.v[7] + c2.v[23] + c2.v[39] + c2.v[55] + c2.v[71])*MainFormSLS->hh_1[110]
 + nn[134]
 + (c2.v[9] + c2.v[25] + c2.v[41] + c2.v[57] + c2.v[73])*MainFormSLS->hh_1[50]
 + nn[471]
 + (c2.v[11] + c2.v[27] + c2.v[43] + c2.v[59] + c2.v[75])*MainFormSLS->hh_1[150]
 + nn[136]
 + (c2.v[13] + c2.v[29] + c2.v[45] + c2.v[61] + c2.v[77])*MainFormSLS->hh_1[90]
 + nn[472]
 + (c2.v[15] + c2.v[31] + c2.v[47] + c2.v[63] + c2.v[79])*MainFormSLS->hh_1[30];
s/=N_2;
out.push_back(s);

//отсчет 66
s= nn[48]
 + (c2.v[1] + c2.v[41])*MainFormSLS->hh_1[132]
 + nn[473]
 + (c2.v[3] + c2.v[43])*MainFormSLS->hh_1[76]
 + nn[139]
 + nn[51]
 + nn[475]
 + (c2.v[7] + c2.v[47])*MainFormSLS->hh_1[124]
 + nn[142]
 + (c2.v[9] + c2.v[49])*MainFormSLS->hh_1[68]
 + nn[54]
 + (c2.v[11] + c2.v[51])*MainFormSLS->hh_1[12]
 + nn[144]
 + (c2.v[13] + c2.v[53])*MainFormSLS->hh_1[116]
 + nn[476]
 + nn[57]
 + nn[147]
 + (c2.v[17] + c2.v[57])*MainFormSLS->hh_1[4]
 + nn[478]
 + (c2.v[19] + c2.v[59])*MainFormSLS->hh_1[108]
 + nn[60]
 + (c2.v[21] + c2.v[61])*MainFormSLS->hh_1[52]
 + nn[479]
 + (c2.v[23] + c2.v[63])*MainFormSLS->hh_1[156]
 + nn[150]
 + nn[63]
 + nn[481]
 + (c2.v[27] + c2.v[67])*MainFormSLS->hh_1[44]
 + nn[153]
 + (c2.v[29] + c2.v[69])*MainFormSLS->hh_1[148]
 + nn[66]
 + (c2.v[31] + c2.v[71])*MainFormSLS->hh_1[92]
 + nn[155]
 + (c2.v[33] + c2.v[73])*MainFormSLS->hh_1[36]
 + nn[482]
 + nn[69]
 + nn[158]
 + (c2.v[37] + c2.v[77])*MainFormSLS->hh_1[84]
 + nn[484]
 + (c2.v[39] + c2.v[79])*MainFormSLS->hh_1[28];
s/=N_2;
out.push_back(s);

//отсчет 67
s= nn[0]
 + c2.v[1]*MainFormSLS->hh_1[134]
 + nn[485]
 + c2.v[3]*MainFormSLS->hh_1[82]
 + nn[161]
 + nn[74]
 + nn[486]
 + c2.v[7]*MainFormSLS->hh_1[138]
 + nn[164]
 + c2.v[9]*MainFormSLS->hh_1[86]
 + nn[77]
 + c2.v[11]*MainFormSLS->hh_1[34]
 + nn[166]
 + c2.v[13]*MainFormSLS->hh_1[142]
 + nn[487]
 + nn[80]
 + nn[169]
 + c2.v[17]*MainFormSLS->hh_1[38]
 + nn[488]
 + c2.v[19]*MainFormSLS->hh_1[146]
 + nn[83]
 + c2.v[21]*MainFormSLS->hh_1[94]
 + nn[489]
 + c2.v[23]*MainFormSLS->hh_1[42]
 + nn[172]
 + nn[86]
 + nn[490]
 + c2.v[27]*MainFormSLS->hh_1[98]
 + nn[175]
 + c2.v[29]*MainFormSLS->hh_1[46]
 + nn[89]
 + c2.v[31]*MainFormSLS->hh_1[154]
 + nn[177]
 + c2.v[33]*MainFormSLS->hh_1[102]
 + nn[491]
 + nn[92]
 + nn[180]
 + c2.v[37]*MainFormSLS->hh_1[158]
 + nn[492]
 + c2.v[39]*MainFormSLS->hh_1[106]
 + nn[24]
 + c2.v[41]*MainFormSLS->hh_1[54]
 + nn[493]
 + c2.v[43]*MainFormSLS->hh_1[2]
 + nn[183]
 + nn[97]
 + nn[494]
 + c2.v[47]*MainFormSLS->hh_1[58]
 + nn[186]
 + c2.v[49]*MainFormSLS->hh_1[6]
 + nn[100]
 + c2.v[51]*MainFormSLS->hh_1[114]
 + nn[188]
 + c2.v[53]*MainFormSLS->hh_1[62]
 + nn[495]
 + nn[103]
 + nn[191]
 + c2.v[57]*MainFormSLS->hh_1[118]
 + nn[496]
 + c2.v[59]*MainFormSLS->hh_1[66]
 + nn[106]
 + c2.v[61]*MainFormSLS->hh_1[14]
 + nn[497]
 + c2.v[63]*MainFormSLS->hh_1[122]
 + nn[194]
 + nn[109]
 + nn[498]
 + c2.v[67]*MainFormSLS->hh_1[18]
 + nn[197]
 + c2.v[69]*MainFormSLS->hh_1[126]
 + nn[112]
 + c2.v[71]*MainFormSLS->hh_1[74]
 + nn[199]
 + c2.v[73]*MainFormSLS->hh_1[22]
 + nn[499]
 + nn[115]
 + nn[202]
 + c2.v[77]*MainFormSLS->hh_1[78]
 + nn[500]
 + c2.v[79]*MainFormSLS->hh_1[26];
s/=N_2;
out.push_back(s);

//отсчет 68
s= nn[118]
 + (c2.v[1] + c2.v[21] + c2.v[41] + c2.v[61])*MainFormSLS->hh_1[136]
 + nn[501]
 + (c2.v[3] + c2.v[23] + c2.v[43] + c2.v[63])*MainFormSLS->hh_1[88]
 + nn[502]
 + nn[121]
 + nn[503]
 + (c2.v[7] + c2.v[27] + c2.v[47] + c2.v[67])*MainFormSLS->hh_1[152]
 + nn[504]
 + (c2.v[9] + c2.v[29] + c2.v[49] + c2.v[69])*MainFormSLS->hh_1[104]
 + nn[124]
 + (c2.v[11] + c2.v[31] + c2.v[51] + c2.v[71])*MainFormSLS->hh_1[56]
 + nn[505]
 + (c2.v[13] + c2.v[33] + c2.v[53] + c2.v[73])*MainFormSLS->hh_1[8]
 + nn[506]
 + nn[127]
 + nn[507]
 + (c2.v[17] + c2.v[37] + c2.v[57] + c2.v[77])*MainFormSLS->hh_1[72]
 + nn[508]
 + (c2.v[19] + c2.v[39] + c2.v[59] + c2.v[79])*MainFormSLS->hh_1[24];
s/=N_2;
out.push_back(s);

//отсчет 69
s= nn[0]
 + c2.v[1]*MainFormSLS->hh_1[138]
 + nn[509]
 + c2.v[3]*MainFormSLS->hh_1[94]
 + nn[207]
 + nn[422]
 + nn[510]
 + c2.v[7]*MainFormSLS->hh_1[6]
 + nn[210]
 + c2.v[9]*MainFormSLS->hh_1[122]
 + nn[296]
 + c2.v[11]*MainFormSLS->hh_1[78]
 + nn[211]
 + c2.v[13]*MainFormSLS->hh_1[34]
 + nn[511]
 + nn[425]
 + nn[214]
 + c2.v[17]*MainFormSLS->hh_1[106]
 + nn[512]
 + c2.v[19]*MainFormSLS->hh_1[62]
 + nn[12]
 + c2.v[21]*MainFormSLS->hh_1[18]
 + nn[513]
 + c2.v[23]*MainFormSLS->hh_1[134]
 + nn[217]
 + nn[428]
 + nn[514]
 + c2.v[27]*MainFormSLS->hh_1[46]
 + nn[220]
 + c2.v[29]*MainFormSLS->hh_1[2]
 + nn[305]
 + c2.v[31]*MainFormSLS->hh_1[118]
 + nn[221]
 + c2.v[33]*MainFormSLS->hh_1[74]
 + nn[515]
 + nn[431]
 + nn[224]
 + c2.v[37]*MainFormSLS->hh_1[146]
 + nn[516]
 + c2.v[39]*MainFormSLS->hh_1[102]
 + nn[24]
 + c2.v[41]*MainFormSLS->hh_1[58]
 + nn[517]
 + c2.v[43]*MainFormSLS->hh_1[14]
 + nn[227]
 + nn[434]
 + nn[518]
 + c2.v[47]*MainFormSLS->hh_1[86]
 + nn[230]
 + c2.v[49]*MainFormSLS->hh_1[42]
 + nn[314]
 + c2.v[51]*MainFormSLS->hh_1[158]
 + nn[231]
 + c2.v[53]*MainFormSLS->hh_1[114]
 + nn[519]
 + nn[437]
 + nn[234]
 + c2.v[57]*MainFormSLS->hh_1[26]
 + nn[520]
 + c2.v[59]*MainFormSLS->hh_1[142]
 + nn[36]
 + c2.v[61]*MainFormSLS->hh_1[98]
 + nn[521]
 + c2.v[63]*MainFormSLS->hh_1[54]
 + nn[237]
 + nn[440]
 + nn[522]
 + c2.v[67]*MainFormSLS->hh_1[126]
 + nn[240]
 + c2.v[69]*MainFormSLS->hh_1[82]
 + nn[323]
 + c2.v[71]*MainFormSLS->hh_1[38]
 + nn[241]
 + c2.v[73]*MainFormSLS->hh_1[154]
 + nn[523]
 + nn[443]
 + nn[244]
 + c2.v[77]*MainFormSLS->hh_1[66]
 + nn[524]
 + c2.v[79]*MainFormSLS->hh_1[22];
s/=N_2;
out.push_back(s);

//отсчет 70
s= nn[246]
 + (c2.v[1] + c2.v[9] + c2.v[17] + c2.v[25] + c2.v[33] + c2.v[41] + c2.v[49] + c2.v[57] + c2.v[65] + c2.v[73])*MainFormSLS->hh_1[140]
 + nn[525]
 + (c2.v[3] + c2.v[11] + c2.v[19] + c2.v[27] + c2.v[35] + c2.v[43] + c2.v[51] + c2.v[59] + c2.v[67] + c2.v[75])*MainFormSLS->hh_1[100]
 + nn[248]
 + (c2.v[5] + c2.v[13] + c2.v[21] + c2.v[29] + c2.v[37] + c2.v[45] + c2.v[53] + c2.v[61] + c2.v[69] + c2.v[77])*MainFormSLS->hh_1[60]
 + nn[526]
 + (c2.v[7] + c2.v[15] + c2.v[23] + c2.v[31] + c2.v[39] + c2.v[47] + c2.v[55] + c2.v[63] + c2.v[71] + c2.v[79])*MainFormSLS->hh_1[20];
s/=N_2;
out.push_back(s);

//отсчет 71
s= nn[0]
 + c2.v[1]*MainFormSLS->hh_1[142]
 + nn[527]
 + c2.v[3]*MainFormSLS->hh_1[106]
 + nn[251]
 + nn[162]
 + nn[529]
 + c2.v[7]*MainFormSLS->hh_1[34]
 + nn[5]
 + c2.v[9]*MainFormSLS->hh_1[158]
 + nn[165]
 + c2.v[11]*MainFormSLS->hh_1[122]
 + nn[254]
 + c2.v[13]*MainFormSLS->hh_1[86]
 + nn[530]
 + nn[168]
 + nn[10]
 + c2.v[17]*MainFormSLS->hh_1[14]
 + nn[532]
 + c2.v[19]*MainFormSLS->hh_1[138]
 + nn[83]
 + c2.v[21]*MainFormSLS->hh_1[102]
 + nn[533]
 + c2.v[23]*MainFormSLS->hh_1[66]
 + nn[14]
 + nn[173]
 + nn[535]
 + c2.v[27]*MainFormSLS->hh_1[154]
 + nn[261]
 + c2.v[29]*MainFormSLS->hh_1[118]
 + nn[176]
 + c2.v[31]*MainFormSLS->hh_1[82]
 + nn[19]
 + c2.v[33]*MainFormSLS->hh_1[46]
 + nn[536]
 + nn[179]
 + nn[264]
 + c2.v[37]*MainFormSLS->hh_1[134]
 + nn[538]
 + c2.v[39]*MainFormSLS->hh_1[98]
 + nn[24]
 + c2.v[41]*MainFormSLS->hh_1[62]
 + nn[539]
 + c2.v[43]*MainFormSLS->hh_1[26]
 + nn[267]
 + nn[184]
 + nn[541]
 + c2.v[47]*MainFormSLS->hh_1[114]
 + nn[29]
 + c2.v[49]*MainFormSLS->hh_1[78]
 + nn[187]
 + c2.v[51]*MainFormSLS->hh_1[42]
 + nn[270]
 + c2.v[53]*MainFormSLS->hh_1[6]
 + nn[542]
 + nn[190]
 + nn[34]
 + c2.v[57]*MainFormSLS->hh_1[94]
 + nn[544]
 + c2.v[59]*MainFormSLS->hh_1[58]
 + nn[106]
 + c2.v[61]*MainFormSLS->hh_1[22]
 + nn[545]
 + c2.v[63]*MainFormSLS->hh_1[146]
 + nn[38]
 + nn[195]
 + nn[547]
 + c2.v[67]*MainFormSLS->hh_1[74]
 + nn[277]
 + c2.v[69]*MainFormSLS->hh_1[38]
 + nn[198]
 + c2.v[71]*MainFormSLS->hh_1[2]
 + nn[43]
 + c2.v[73]*MainFormSLS->hh_1[126]
 + nn[548]
 + nn[201]
 + nn[280]
 + c2.v[77]*MainFormSLS->hh_1[54]
 + nn[550]
 + c2.v[79]*MainFormSLS->hh_1[18];
s/=N_2;
out.push_back(s);

//отсчет 72
s= nn[204]
 + (c2.v[1] + c2.v[11] + c2.v[21] + c2.v[31] + c2.v[41] + c2.v[51] + c2.v[61] + c2.v[71])*MainFormSLS->hh_1[144]
 + (c2.v[2] + c2.v[12] + c2.v[22] + c2.v[32] + c2.v[42] + c2.v[52] + c2.v[62] + c2.v[72])*MainFormSLS->hh_1[128]
 + (c2.v[3] + c2.v[13] + c2.v[23] + c2.v[33] + c2.v[43] + c2.v[53] + c2.v[63] + c2.v[73])*MainFormSLS->hh_1[112]
 + (c2.v[4] + c2.v[14] + c2.v[24] + c2.v[34] + c2.v[44] + c2.v[54] + c2.v[64] + c2.v[74])*MainFormSLS->hh_1[96]
 + nn[205]
 + (c2.v[6] + c2.v[16] + c2.v[26] + c2.v[36] + c2.v[46] + c2.v[56] + c2.v[66] + c2.v[76])*MainFormSLS->hh_1[64]
 + (c2.v[7] + c2.v[17] + c2.v[27] + c2.v[37] + c2.v[47] + c2.v[57] + c2.v[67] + c2.v[77])*MainFormSLS->hh_1[48]
 + (c2.v[8] + c2.v[18] + c2.v[28] + c2.v[38] + c2.v[48] + c2.v[58] + c2.v[68] + c2.v[78])*MainFormSLS->hh_1[32]
 + (c2.v[9] + c2.v[19] + c2.v[29] + c2.v[39] + c2.v[49] + c2.v[59] + c2.v[69] + c2.v[79])*MainFormSLS->hh_1[16];
s/=N_2;
out.push_back(s);

//отсчет 73
s= nn[0]
 + c2.v[1]*MainFormSLS->hh_1[146]
 + nn[551]
 + c2.v[3]*MainFormSLS->hh_1[118]
 + nn[293]
 + nn[208]
 + nn[552]
 + c2.v[7]*MainFormSLS->hh_1[62]
 + nn[76]
 + c2.v[9]*MainFormSLS->hh_1[34]
 + nn[6]
 + c2.v[11]*MainFormSLS->hh_1[6]
 + nn[297]
 + c2.v[13]*MainFormSLS->hh_1[138]
 + nn[553]
 + nn[213]
 + nn[81]
 + c2.v[17]*MainFormSLS->hh_1[82]
 + nn[554]
 + c2.v[19]*MainFormSLS->hh_1[54]
 + nn[12]
 + c2.v[21]*MainFormSLS->hh_1[26]
 + nn[555]
 + c2.v[23]*MainFormSLS->hh_1[158]
 + nn[85]
 + nn[218]
 + nn[556]
 + c2.v[27]*MainFormSLS->hh_1[102]
 + nn[304]
 + c2.v[29]*MainFormSLS->hh_1[74]
 + nn[18]
 + c2.v[31]*MainFormSLS->hh_1[46]
 + nn[90]
 + c2.v[33]*MainFormSLS->hh_1[18]
 + nn[557]
 + nn[223]
 + nn[308]
 + c2.v[37]*MainFormSLS->hh_1[122]
 + nn[558]
 + c2.v[39]*MainFormSLS->hh_1[94]
 + nn[24]
 + c2.v[41]*MainFormSLS->hh_1[66]
 + nn[559]
 + c2.v[43]*MainFormSLS->hh_1[38]
 + nn[311]
 + nn[228]
 + nn[560]
 + c2.v[47]*MainFormSLS->hh_1[142]
 + nn[99]
 + c2.v[49]*MainFormSLS->hh_1[114]
 + nn[30]
 + c2.v[51]*MainFormSLS->hh_1[86]
 + nn[315]
 + c2.v[53]*MainFormSLS->hh_1[58]
 + nn[561]
 + nn[233]
 + nn[104]
 + c2.v[57]*MainFormSLS->hh_1[2]
 + nn[562]
 + c2.v[59]*MainFormSLS->hh_1[134]
 + nn[36]
 + c2.v[61]*MainFormSLS->hh_1[106]
 + nn[563]
 + c2.v[63]*MainFormSLS->hh_1[78]
 + nn[108]
 + nn[238]
 + nn[564]
 + c2.v[67]*MainFormSLS->hh_1[22]
 + nn[322]
 + c2.v[69]*MainFormSLS->hh_1[154]
 + nn[42]
 + c2.v[71]*MainFormSLS->hh_1[126]
 + nn[113]
 + c2.v[73]*MainFormSLS->hh_1[98]
 + nn[565]
 + nn[243]
 + nn[326]
 + c2.v[77]*MainFormSLS->hh_1[42]
 + nn[566]
 + c2.v[79]*MainFormSLS->hh_1[14];
s/=N_2;
out.push_back(s);

//отсчет 74
s= nn[48]
 + (c2.v[1] + c2.v[41])*MainFormSLS->hh_1[148]
 + nn[567]
 + (c2.v[3] + c2.v[43])*MainFormSLS->hh_1[124]
 + nn[329]
 + nn[474]
 + nn[568]
 + (c2.v[7] + c2.v[47])*MainFormSLS->hh_1[76]
 + nn[332]
 + (c2.v[9] + c2.v[49])*MainFormSLS->hh_1[52]
 + nn[54]
 + (c2.v[11] + c2.v[51])*MainFormSLS->hh_1[28]
 + nn[333]
 + (c2.v[13] + c2.v[53])*MainFormSLS->hh_1[4]
 + nn[569]
 + nn[477]
 + nn[336]
 + (c2.v[17] + c2.v[57])*MainFormSLS->hh_1[116]
 + nn[570]
 + (c2.v[19] + c2.v[59])*MainFormSLS->hh_1[92]
 + nn[60]
 + (c2.v[21] + c2.v[61])*MainFormSLS->hh_1[68]
 + nn[571]
 + (c2.v[23] + c2.v[63])*MainFormSLS->hh_1[44]
 + nn[339]
 + nn[480]
 + nn[572]
 + (c2.v[27] + c2.v[67])*MainFormSLS->hh_1[156]
 + nn[342]
 + (c2.v[29] + c2.v[69])*MainFormSLS->hh_1[132]
 + nn[66]
 + (c2.v[31] + c2.v[71])*MainFormSLS->hh_1[108]
 + nn[343]
 + (c2.v[33] + c2.v[73])*MainFormSLS->hh_1[84]
 + nn[573]
 + nn[483]
 + nn[346]
 + (c2.v[37] + c2.v[77])*MainFormSLS->hh_1[36]
 + nn[574]
 + (c2.v[39] + c2.v[79])*MainFormSLS->hh_1[12];
s/=N_2;
out.push_back(s);

//отсчет 75
s= nn[130]
 + (c2.v[1] + c2.v[17] + c2.v[33] + c2.v[49] + c2.v[65])*MainFormSLS->hh_1[150]
 + nn[575]
 + (c2.v[3] + c2.v[19] + c2.v[35] + c2.v[51] + c2.v[67])*MainFormSLS->hh_1[130]
 + nn[349]
 + (c2.v[5] + c2.v[21] + c2.v[37] + c2.v[53] + c2.v[69])*MainFormSLS->hh_1[110]
 + nn[576]
 + (c2.v[7] + c2.v[23] + c2.v[39] + c2.v[55] + c2.v[71])*MainFormSLS->hh_1[90]
 + nn[134]
 + (c2.v[9] + c2.v[25] + c2.v[41] + c2.v[57] + c2.v[73])*MainFormSLS->hh_1[70]
 + nn[577]
 + (c2.v[11] + c2.v[27] + c2.v[43] + c2.v[59] + c2.v[75])*MainFormSLS->hh_1[50]
 + nn[352]
 + (c2.v[13] + c2.v[29] + c2.v[45] + c2.v[61] + c2.v[77])*MainFormSLS->hh_1[30]
 + nn[578]
 + (c2.v[15] + c2.v[31] + c2.v[47] + c2.v[63] + c2.v[79])*MainFormSLS->hh_1[10];
s/=N_2;
out.push_back(s);

//отсчет 76
s= nn[118]
 + (c2.v[1] + c2.v[21] + c2.v[41] + c2.v[61])*MainFormSLS->hh_1[152]
 + nn[579]
 + (c2.v[3] + c2.v[23] + c2.v[43] + c2.v[63])*MainFormSLS->hh_1[136]
 + nn[580]
 + nn[284]
 + nn[581]
 + (c2.v[7] + c2.v[27] + c2.v[47] + c2.v[67])*MainFormSLS->hh_1[104]
 + nn[582]
 + (c2.v[9] + c2.v[29] + c2.v[49] + c2.v[69])*MainFormSLS->hh_1[88]
 + nn[124]
 + (c2.v[11] + c2.v[31] + c2.v[51] + c2.v[71])*MainFormSLS->hh_1[72]
 + nn[583]
 + (c2.v[13] + c2.v[33] + c2.v[53] + c2.v[73])*MainFormSLS->hh_1[56]
 + nn[584]
 + nn[289]
 + nn[585]
 + (c2.v[17] + c2.v[37] + c2.v[57] + c2.v[77])*MainFormSLS->hh_1[24]
 + nn[586]
 + (c2.v[19] + c2.v[39] + c2.v[59] + c2.v[79])*MainFormSLS->hh_1[8];
s/=N_2;
out.push_back(s);

//отсчет 77
s= nn[0]
 + c2.v[1]*MainFormSLS->hh_1[154]
 + nn[587]
 + c2.v[3]*MainFormSLS->hh_1[142]
 + nn[356]
 + nn[294]
 + nn[588]
 + c2.v[7]*MainFormSLS->hh_1[118]
 + nn[164]
 + c2.v[9]*MainFormSLS->hh_1[106]
 + nn[296]
 + c2.v[11]*MainFormSLS->hh_1[94]
 + nn[358]
 + c2.v[13]*MainFormSLS->hh_1[82]
 + nn[589]
 + nn[299]
 + nn[169]
 + c2.v[17]*MainFormSLS->hh_1[58]
 + nn[590]
 + c2.v[19]*MainFormSLS->hh_1[46]
 + nn[12]
 + c2.v[21]*MainFormSLS->hh_1[34]
 + nn[591]
 + c2.v[23]*MainFormSLS->hh_1[22]
 + nn[172]
 + nn[302]
 + nn[592]
 + c2.v[27]*MainFormSLS->hh_1[158]
 + nn[363]
 + c2.v[29]*MainFormSLS->hh_1[146]
 + nn[305]
 + c2.v[31]*MainFormSLS->hh_1[134]
 + nn[177]
 + c2.v[33]*MainFormSLS->hh_1[122]
 + nn[593]
 + nn[307]
 + nn[365]
 + c2.v[37]*MainFormSLS->hh_1[98]
 + nn[594]
 + c2.v[39]*MainFormSLS->hh_1[86]
 + nn[24]
 + c2.v[41]*MainFormSLS->hh_1[74]
 + nn[595]
 + c2.v[43]*MainFormSLS->hh_1[62]
 + nn[368]
 + nn[312]
 + nn[596]
 + c2.v[47]*MainFormSLS->hh_1[38]
 + nn[186]
 + c2.v[49]*MainFormSLS->hh_1[26]
 + nn[314]
 + c2.v[51]*MainFormSLS->hh_1[14]
 + nn[370]
 + c2.v[53]*MainFormSLS->hh_1[2]
 + nn[597]
 + nn[317]
 + nn[191]
 + c2.v[57]*MainFormSLS->hh_1[138]
 + nn[598]
 + c2.v[59]*MainFormSLS->hh_1[126]
 + nn[36]
 + c2.v[61]*MainFormSLS->hh_1[114]
 + nn[599]
 + c2.v[63]*MainFormSLS->hh_1[102]
 + nn[194]
 + nn[320]
 + nn[600]
 + c2.v[67]*MainFormSLS->hh_1[78]
 + nn[375]
 + c2.v[69]*MainFormSLS->hh_1[66]
 + nn[323]
 + c2.v[71]*MainFormSLS->hh_1[54]
 + nn[199]
 + c2.v[73]*MainFormSLS->hh_1[42]
 + nn[601]
 + nn[325]
 + nn[377]
 + c2.v[77]*MainFormSLS->hh_1[18]
 + nn[602]
 + c2.v[79]*MainFormSLS->hh_1[6];
s/=N_2;
out.push_back(s);

//отсчет 78
s= nn[48]
 + (c2.v[1] + c2.v[41])*MainFormSLS->hh_1[156]
 + nn[603]
 + (c2.v[3] + c2.v[43])*MainFormSLS->hh_1[148]
 + nn[380]
 + nn[330]
 + nn[604]
 + (c2.v[7] + c2.v[47])*MainFormSLS->hh_1[132]
 + nn[382]
 + (c2.v[9] + c2.v[49])*MainFormSLS->hh_1[124]
 + nn[143]
 + (c2.v[11] + c2.v[51])*MainFormSLS->hh_1[116]
 + nn[383]
 + (c2.v[13] + c2.v[53])*MainFormSLS->hh_1[108]
 + nn[605]
 + nn[335]
 + nn[385]
 + (c2.v[17] + c2.v[57])*MainFormSLS->hh_1[92]
 + nn[606]
 + (c2.v[19] + c2.v[59])*MainFormSLS->hh_1[84]
 + nn[60]
 + (c2.v[21] + c2.v[61])*MainFormSLS->hh_1[76]
 + nn[607]
 + (c2.v[23] + c2.v[63])*MainFormSLS->hh_1[68]
 + nn[388]
 + nn[340]
 + nn[608]
 + (c2.v[27] + c2.v[67])*MainFormSLS->hh_1[52]
 + nn[390]
 + (c2.v[29] + c2.v[69])*MainFormSLS->hh_1[44]
 + nn[154]
 + (c2.v[31] + c2.v[71])*MainFormSLS->hh_1[36]
 + nn[391]
 + (c2.v[33] + c2.v[73])*MainFormSLS->hh_1[28]
 + nn[609]
 + nn[345]
 + nn[393]
 + (c2.v[37] + c2.v[77])*MainFormSLS->hh_1[12]
 + nn[610]
 + (c2.v[39] + c2.v[79])*MainFormSLS->hh_1[4];
s/=N_2;
out.push_back(s);

//отсчет 79
s= nn[0]
 + c2.v[1]*MainFormSLS->hh_1[158]
 + nn[611]
 + c2.v[3]*MainFormSLS->hh_1[154]
 + nn[396]
 + nn[528]
 + nn[612]
 + c2.v[7]*MainFormSLS->hh_1[146]
 + nn[210]
 + c2.v[9]*MainFormSLS->hh_1[142]
 + nn[165]
 + c2.v[11]*MainFormSLS->hh_1[138]
 + nn[398]
 + c2.v[13]*MainFormSLS->hh_1[134]
 + nn[613]
 + nn[531]
 + nn[214]
 + c2.v[17]*MainFormSLS->hh_1[126]
 + nn[614]
 + c2.v[19]*MainFormSLS->hh_1[122]
 + nn[83]
 + c2.v[21]*MainFormSLS->hh_1[118]
 + nn[615]
 + c2.v[23]*MainFormSLS->hh_1[114]
 + nn[217]
 + nn[534]
 + nn[616]
 + c2.v[27]*MainFormSLS->hh_1[106]
 + nn[403]
 + c2.v[29]*MainFormSLS->hh_1[102]
 + nn[176]
 + c2.v[31]*MainFormSLS->hh_1[98]
 + nn[221]
 + c2.v[33]*MainFormSLS->hh_1[94]
 + nn[617]
 + nn[537]
 + nn[405]
 + c2.v[37]*MainFormSLS->hh_1[86]
 + nn[618]
 + c2.v[39]*MainFormSLS->hh_1[82]
 + nn[24]
 + c2.v[41]*MainFormSLS->hh_1[78]
 + nn[619]
 + c2.v[43]*MainFormSLS->hh_1[74]
 + nn[408]
 + nn[540]
 + nn[620]
 + c2.v[47]*MainFormSLS->hh_1[66]
 + nn[230]
 + c2.v[49]*MainFormSLS->hh_1[62]
 + nn[187]
 + c2.v[51]*MainFormSLS->hh_1[58]
 + nn[410]
 + c2.v[53]*MainFormSLS->hh_1[54]
 + nn[621]
 + nn[543]
 + nn[234]
 + c2.v[57]*MainFormSLS->hh_1[46]
 + nn[622]
 + c2.v[59]*MainFormSLS->hh_1[42]
 + nn[106]
 + c2.v[61]*MainFormSLS->hh_1[38]
 + nn[623]
 + c2.v[63]*MainFormSLS->hh_1[34]
 + nn[237]
 + nn[546]
 + nn[624]
 + c2.v[67]*MainFormSLS->hh_1[26]
 + nn[415]
 + c2.v[69]*MainFormSLS->hh_1[22]
 + nn[198]
 + c2.v[71]*MainFormSLS->hh_1[18]
 + nn[241]
 + c2.v[73]*MainFormSLS->hh_1[14]
 + nn[625]
 + nn[549]
 + nn[417]
 + c2.v[77]*MainFormSLS->hh_1[6]
 + nn[626]
 + c2.v[79]*MainFormSLS->hh_1[2];
s/=N_2;
out.push_back(s);
int sz = out.size();
out.resize(2*sz);
memcpy(&out[sz],&out[0],sz*sizeof(complex<double>));
}
//-----------------------------------------------------------------------------

