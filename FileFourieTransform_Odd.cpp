//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "FileFourieTransform_Odd.h"
#include "SipClient_Unit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
void __fastcall dfft_odd(vector<short>& x,TCoeff_BY_2& c2)
{
//C���� ������������� �������� ���� ��� ���
//��� 160 ��� id 1 (50 Hz)
double sum_160_1_000 = (double)x[0];
double sum_160_1_001 = (double)x[1];
double sum_160_1_002 = (double)x[2];
double sum_160_1_003 = (double)x[3];
double sum_160_1_004 = (double)x[4];
double sum_160_1_005 = (double)x[5];
double sum_160_1_006 = (double)x[6];
double sum_160_1_007 = (double)x[7];
double sum_160_1_008 = (double)x[8];
double sum_160_1_009 = (double)x[9];
double sum_160_1_010 = (double)x[10];
double sum_160_1_011 = (double)x[11];
double sum_160_1_012 = (double)x[12];
double sum_160_1_013 = (double)x[13];
double sum_160_1_014 = (double)x[14];
double sum_160_1_015 = (double)x[15];
double sum_160_1_016 = (double)x[16];
double sum_160_1_017 = (double)x[17];
double sum_160_1_018 = (double)x[18];
double sum_160_1_019 = (double)x[19];
double sum_160_1_020 = (double)x[20];
double sum_160_1_021 = (double)x[21];
double sum_160_1_022 = (double)x[22];
double sum_160_1_023 = (double)x[23];
double sum_160_1_024 = (double)x[24];
double sum_160_1_025 = (double)x[25];
double sum_160_1_026 = (double)x[26];
double sum_160_1_027 = (double)x[27];
double sum_160_1_028 = (double)x[28];
double sum_160_1_029 = (double)x[29];
double sum_160_1_030 = (double)x[30];
double sum_160_1_031 = (double)x[31];
double sum_160_1_032 = (double)x[32];
double sum_160_1_033 = (double)x[33];
double sum_160_1_034 = (double)x[34];
double sum_160_1_035 = (double)x[35];
double sum_160_1_036 = (double)x[36];
double sum_160_1_037 = (double)x[37];
double sum_160_1_038 = (double)x[38];
double sum_160_1_039 = (double)x[39];
double sum_160_1_040 = (double)x[40];
double sum_160_1_041 = (double)x[41];
double sum_160_1_042 = (double)x[42];
double sum_160_1_043 = (double)x[43];
double sum_160_1_044 = (double)x[44];
double sum_160_1_045 = (double)x[45];
double sum_160_1_046 = (double)x[46];
double sum_160_1_047 = (double)x[47];
double sum_160_1_048 = (double)x[48];
double sum_160_1_049 = (double)x[49];
double sum_160_1_050 = (double)x[50];
double sum_160_1_051 = (double)x[51];
double sum_160_1_052 = (double)x[52];
double sum_160_1_053 = (double)x[53];
double sum_160_1_054 = (double)x[54];
double sum_160_1_055 = (double)x[55];
double sum_160_1_056 = (double)x[56];
double sum_160_1_057 = (double)x[57];
double sum_160_1_058 = (double)x[58];
double sum_160_1_059 = (double)x[59];
double sum_160_1_060 = (double)x[60];
double sum_160_1_061 = (double)x[61];
double sum_160_1_062 = (double)x[62];
double sum_160_1_063 = (double)x[63];
double sum_160_1_064 = (double)x[64];
double sum_160_1_065 = (double)x[65];
double sum_160_1_066 = (double)x[66];
double sum_160_1_067 = (double)x[67];
double sum_160_1_068 = (double)x[68];
double sum_160_1_069 = (double)x[69];
double sum_160_1_070 = (double)x[70];
double sum_160_1_071 = (double)x[71];
double sum_160_1_072 = (double)x[72];
double sum_160_1_073 = (double)x[73];
double sum_160_1_074 = (double)x[74];
double sum_160_1_075 = (double)x[75];
double sum_160_1_076 = (double)x[76];
double sum_160_1_077 = (double)x[77];
double sum_160_1_078 = (double)x[78];
double sum_160_1_079 = (double)x[79];
double sum_160_1_080 = (double)x[80];
double sum_160_1_081 = (double)x[81];
double sum_160_1_082 = (double)x[82];
double sum_160_1_083 = (double)x[83];
double sum_160_1_084 = (double)x[84];
double sum_160_1_085 = (double)x[85];
double sum_160_1_086 = (double)x[86];
double sum_160_1_087 = (double)x[87];
double sum_160_1_088 = (double)x[88];
double sum_160_1_089 = (double)x[89];
double sum_160_1_090 = (double)x[90];
double sum_160_1_091 = (double)x[91];
double sum_160_1_092 = (double)x[92];
double sum_160_1_093 = (double)x[93];
double sum_160_1_094 = (double)x[94];
double sum_160_1_095 = (double)x[95];
double sum_160_1_096 = (double)x[96];
double sum_160_1_097 = (double)x[97];
double sum_160_1_098 = (double)x[98];
double sum_160_1_099 = (double)x[99];
double sum_160_1_100 = (double)x[100];
double sum_160_1_101 = (double)x[101];
double sum_160_1_102 = (double)x[102];
double sum_160_1_103 = (double)x[103];
double sum_160_1_104 = (double)x[104];
double sum_160_1_105 = (double)x[105];
double sum_160_1_106 = (double)x[106];
double sum_160_1_107 = (double)x[107];
double sum_160_1_108 = (double)x[108];
double sum_160_1_109 = (double)x[109];
double sum_160_1_110 = (double)x[110];
double sum_160_1_111 = (double)x[111];
double sum_160_1_112 = (double)x[112];
double sum_160_1_113 = (double)x[113];
double sum_160_1_114 = (double)x[114];
double sum_160_1_115 = (double)x[115];
double sum_160_1_116 = (double)x[116];
double sum_160_1_117 = (double)x[117];
double sum_160_1_118 = (double)x[118];
double sum_160_1_119 = (double)x[119];
double sum_160_1_120 = (double)x[120];
double sum_160_1_121 = (double)x[121];
double sum_160_1_122 = (double)x[122];
double sum_160_1_123 = (double)x[123];
double sum_160_1_124 = (double)x[124];
double sum_160_1_125 = (double)x[125];
double sum_160_1_126 = (double)x[126];
double sum_160_1_127 = (double)x[127];
double sum_160_1_128 = (double)x[128];
double sum_160_1_129 = (double)x[129];
double sum_160_1_130 = (double)x[130];
double sum_160_1_131 = (double)x[131];
double sum_160_1_132 = (double)x[132];
double sum_160_1_133 = (double)x[133];
double sum_160_1_134 = (double)x[134];
double sum_160_1_135 = (double)x[135];
double sum_160_1_136 = (double)x[136];
double sum_160_1_137 = (double)x[137];
double sum_160_1_138 = (double)x[138];
double sum_160_1_139 = (double)x[139];
double sum_160_1_140 = (double)x[140];
double sum_160_1_141 = (double)x[141];
double sum_160_1_142 = (double)x[142];
double sum_160_1_143 = (double)x[143];
double sum_160_1_144 = (double)x[144];
double sum_160_1_145 = (double)x[145];
double sum_160_1_146 = (double)x[146];
double sum_160_1_147 = (double)x[147];
double sum_160_1_148 = (double)x[148];
double sum_160_1_149 = (double)x[149];
double sum_160_1_150 = (double)x[150];
double sum_160_1_151 = (double)x[151];
double sum_160_1_152 = (double)x[152];
double sum_160_1_153 = (double)x[153];
double sum_160_1_154 = (double)x[154];
double sum_160_1_155 = (double)x[155];
double sum_160_1_156 = (double)x[156];
double sum_160_1_157 = (double)x[157];
double sum_160_1_158 = (double)x[158];
double sum_160_1_159 = (double)x[159];

//��� 53 ��� id 3 (150 Hz) Printable
double sum_53_3_000 = sum_160_1_000;
double sum_53_3_001 = sum_160_1_001;
double sum_53_3_002 = sum_160_1_002;
double sum_53_3_003 = sum_160_1_003;
double sum_53_3_004 = sum_160_1_004;
double sum_53_3_005 = sum_160_1_005;
double sum_53_3_006 = sum_160_1_006;
double sum_53_3_007 = sum_160_1_007;
double sum_53_3_008 = sum_160_1_008;
double sum_53_3_009 = sum_160_1_009;
double sum_53_3_010 = sum_160_1_010;
double sum_53_3_011 = sum_160_1_011;
double sum_53_3_012 = sum_160_1_012;
double sum_53_3_013 = sum_160_1_013;
double sum_53_3_014 = sum_160_1_014;
double sum_53_3_015 = sum_160_1_015;
double sum_53_3_016 = sum_160_1_016;
double sum_53_3_017 = sum_160_1_017;
double sum_53_3_018 = sum_160_1_018;
double sum_53_3_019 = sum_160_1_019;
double sum_53_3_020 = sum_160_1_020;
double sum_53_3_021 = sum_160_1_021;
double sum_53_3_022 = sum_160_1_022;
double sum_53_3_023 = sum_160_1_023;
double sum_53_3_024 = sum_160_1_024;
double sum_53_3_025 = sum_160_1_025;
double sum_53_3_026 = sum_160_1_026;
double sum_53_3_027 = sum_160_1_027;
double sum_53_3_028 = sum_160_1_028;
double sum_53_3_029 = sum_160_1_029;
double sum_53_3_030 = sum_160_1_030;
double sum_53_3_031 = sum_160_1_031;
double sum_53_3_032 = sum_160_1_032;
double sum_53_3_033 = sum_160_1_033;
double sum_53_3_034 = sum_160_1_034;
double sum_53_3_035 = sum_160_1_035;
double sum_53_3_036 = sum_160_1_036;
double sum_53_3_037 = sum_160_1_037;
double sum_53_3_038 = sum_160_1_038;
double sum_53_3_039 = sum_160_1_039;
double sum_53_3_040 = sum_160_1_040;
double sum_53_3_041 = sum_160_1_041;
double sum_53_3_042 = sum_160_1_042;
double sum_53_3_043 = sum_160_1_043;
double sum_53_3_044 = sum_160_1_044;
double sum_53_3_045 = sum_160_1_045;
double sum_53_3_046 = sum_160_1_046;
double sum_53_3_047 = sum_160_1_047;
double sum_53_3_048 = sum_160_1_048;
double sum_53_3_049 = sum_160_1_049;
double sum_53_3_050 = sum_160_1_050;
double sum_53_3_051 = sum_160_1_051;
double sum_53_3_052 = sum_160_1_052;
double sum_53_3_053 = sum_160_1_053;
double sum_53_3_054 = sum_160_1_054;
double sum_53_3_055 = sum_160_1_055;
double sum_53_3_056 = sum_160_1_056;
double sum_53_3_057 = sum_160_1_057;
double sum_53_3_058 = sum_160_1_058;
double sum_53_3_059 = sum_160_1_059;
double sum_53_3_060 = sum_160_1_060;
double sum_53_3_061 = sum_160_1_061;
double sum_53_3_062 = sum_160_1_062;
double sum_53_3_063 = sum_160_1_063;
double sum_53_3_064 = sum_160_1_064;
double sum_53_3_065 = sum_160_1_065;
double sum_53_3_066 = sum_160_1_066;
double sum_53_3_067 = sum_160_1_067;
double sum_53_3_068 = sum_160_1_068;
double sum_53_3_069 = sum_160_1_069;
double sum_53_3_070 = sum_160_1_070;
double sum_53_3_071 = sum_160_1_071;
double sum_53_3_072 = sum_160_1_072;
double sum_53_3_073 = sum_160_1_073;
double sum_53_3_074 = sum_160_1_074;
double sum_53_3_075 = sum_160_1_075;
double sum_53_3_076 = sum_160_1_076;
double sum_53_3_077 = sum_160_1_077;
double sum_53_3_078 = sum_160_1_078;
double sum_53_3_079 = sum_160_1_079;
double sum_53_3_080 = sum_160_1_080;
double sum_53_3_081 = sum_160_1_081;
double sum_53_3_082 = sum_160_1_082;
double sum_53_3_083 = sum_160_1_083;
double sum_53_3_084 = sum_160_1_084;
double sum_53_3_085 = sum_160_1_085;
double sum_53_3_086 = sum_160_1_086;
double sum_53_3_087 = sum_160_1_087;
double sum_53_3_088 = sum_160_1_088;
double sum_53_3_089 = sum_160_1_089;
double sum_53_3_090 = sum_160_1_090;
double sum_53_3_091 = sum_160_1_091;
double sum_53_3_092 = sum_160_1_092;
double sum_53_3_093 = sum_160_1_093;
double sum_53_3_094 = sum_160_1_094;
double sum_53_3_095 = sum_160_1_095;
double sum_53_3_096 = sum_160_1_096;
double sum_53_3_097 = sum_160_1_097;
double sum_53_3_098 = sum_160_1_098;
double sum_53_3_099 = sum_160_1_099;
double sum_53_3_100 = sum_160_1_100;
double sum_53_3_101 = sum_160_1_101;
double sum_53_3_102 = sum_160_1_102;
double sum_53_3_103 = sum_160_1_103;
double sum_53_3_104 = sum_160_1_104;
double sum_53_3_105 = sum_160_1_105;
double sum_53_3_106 = sum_160_1_106;
double sum_53_3_107 = sum_160_1_107;
double sum_53_3_108 = sum_160_1_108;
double sum_53_3_109 = sum_160_1_109;
double sum_53_3_110 = sum_160_1_110;
double sum_53_3_111 = sum_160_1_111;
double sum_53_3_112 = sum_160_1_112;
double sum_53_3_113 = sum_160_1_113;
double sum_53_3_114 = sum_160_1_114;
double sum_53_3_115 = sum_160_1_115;
double sum_53_3_116 = sum_160_1_116;
double sum_53_3_117 = sum_160_1_117;
double sum_53_3_118 = sum_160_1_118;
double sum_53_3_119 = sum_160_1_119;
double sum_53_3_120 = sum_160_1_120;
double sum_53_3_121 = sum_160_1_121;
double sum_53_3_122 = sum_160_1_122;
double sum_53_3_123 = sum_160_1_123;
double sum_53_3_124 = sum_160_1_124;
double sum_53_3_125 = sum_160_1_125;
double sum_53_3_126 = sum_160_1_126;
double sum_53_3_127 = sum_160_1_127;
double sum_53_3_128 = sum_160_1_128;
double sum_53_3_129 = sum_160_1_129;
double sum_53_3_130 = sum_160_1_130;
double sum_53_3_131 = sum_160_1_131;
double sum_53_3_132 = sum_160_1_132;
double sum_53_3_133 = sum_160_1_133;
double sum_53_3_134 = sum_160_1_134;
double sum_53_3_135 = sum_160_1_135;
double sum_53_3_136 = sum_160_1_136;
double sum_53_3_137 = sum_160_1_137;
double sum_53_3_138 = sum_160_1_138;
double sum_53_3_139 = sum_160_1_139;
double sum_53_3_140 = sum_160_1_140;
double sum_53_3_141 = sum_160_1_141;
double sum_53_3_142 = sum_160_1_142;
double sum_53_3_143 = sum_160_1_143;
double sum_53_3_144 = sum_160_1_144;
double sum_53_3_145 = sum_160_1_145;
double sum_53_3_146 = sum_160_1_146;
double sum_53_3_147 = sum_160_1_147;
double sum_53_3_148 = sum_160_1_148;
double sum_53_3_149 = sum_160_1_149;
double sum_53_3_150 = sum_160_1_150;
double sum_53_3_151 = sum_160_1_151;
double sum_53_3_152 = sum_160_1_152;
double sum_53_3_153 = sum_160_1_153;
double sum_53_3_154 = sum_160_1_154;
double sum_53_3_155 = sum_160_1_155;
double sum_53_3_156 = sum_160_1_156;
double sum_53_3_157 = sum_160_1_157;
double sum_53_3_158 = sum_160_1_158;
double sum_53_3_159 = sum_160_1_159;

//��� 32 ��� id 5 (250 Hz) Printable
double sum_32_5_000 = sum_53_3_000 + sum_53_3_032 + sum_53_3_064 + sum_53_3_096 + sum_53_3_128;
double sum_32_5_001 = sum_53_3_001 + sum_53_3_033 + sum_53_3_065 + sum_53_3_097 + sum_53_3_129;
double sum_32_5_002 = sum_53_3_002 + sum_53_3_034 + sum_53_3_066 + sum_53_3_098 + sum_53_3_130;
double sum_32_5_003 = sum_53_3_003 + sum_53_3_035 + sum_53_3_067 + sum_53_3_099 + sum_53_3_131;
double sum_32_5_004 = sum_53_3_004 + sum_53_3_036 + sum_53_3_068 + sum_53_3_100 + sum_53_3_132;
double sum_32_5_005 = sum_53_3_005 + sum_53_3_037 + sum_53_3_069 + sum_53_3_101 + sum_53_3_133;
double sum_32_5_006 = sum_53_3_006 + sum_53_3_038 + sum_53_3_070 + sum_53_3_102 + sum_53_3_134;
double sum_32_5_007 = sum_53_3_007 + sum_53_3_039 + sum_53_3_071 + sum_53_3_103 + sum_53_3_135;
double sum_32_5_008 = sum_53_3_008 + sum_53_3_040 + sum_53_3_072 + sum_53_3_104 + sum_53_3_136;
double sum_32_5_009 = sum_53_3_009 + sum_53_3_041 + sum_53_3_073 + sum_53_3_105 + sum_53_3_137;
double sum_32_5_010 = sum_53_3_010 + sum_53_3_042 + sum_53_3_074 + sum_53_3_106 + sum_53_3_138;
double sum_32_5_011 = sum_53_3_011 + sum_53_3_043 + sum_53_3_075 + sum_53_3_107 + sum_53_3_139;
double sum_32_5_012 = sum_53_3_012 + sum_53_3_044 + sum_53_3_076 + sum_53_3_108 + sum_53_3_140;
double sum_32_5_013 = sum_53_3_013 + sum_53_3_045 + sum_53_3_077 + sum_53_3_109 + sum_53_3_141;
double sum_32_5_014 = sum_53_3_014 + sum_53_3_046 + sum_53_3_078 + sum_53_3_110 + sum_53_3_142;
double sum_32_5_015 = sum_53_3_015 + sum_53_3_047 + sum_53_3_079 + sum_53_3_111 + sum_53_3_143;
double sum_32_5_016 = sum_53_3_016 + sum_53_3_048 + sum_53_3_080 + sum_53_3_112 + sum_53_3_144;
double sum_32_5_017 = sum_53_3_017 + sum_53_3_049 + sum_53_3_081 + sum_53_3_113 + sum_53_3_145;
double sum_32_5_018 = sum_53_3_018 + sum_53_3_050 + sum_53_3_082 + sum_53_3_114 + sum_53_3_146;
double sum_32_5_019 = sum_53_3_019 + sum_53_3_051 + sum_53_3_083 + sum_53_3_115 + sum_53_3_147;
double sum_32_5_020 = sum_53_3_020 + sum_53_3_052 + sum_53_3_084 + sum_53_3_116 + sum_53_3_148;
double sum_32_5_021 = sum_53_3_021 + sum_53_3_053 + sum_53_3_085 + sum_53_3_117 + sum_53_3_149;
double sum_32_5_022 = sum_53_3_022 + sum_53_3_054 + sum_53_3_086 + sum_53_3_118 + sum_53_3_150;
double sum_32_5_023 = sum_53_3_023 + sum_53_3_055 + sum_53_3_087 + sum_53_3_119 + sum_53_3_151;
double sum_32_5_024 = sum_53_3_024 + sum_53_3_056 + sum_53_3_088 + sum_53_3_120 + sum_53_3_152;
double sum_32_5_025 = sum_53_3_025 + sum_53_3_057 + sum_53_3_089 + sum_53_3_121 + sum_53_3_153;
double sum_32_5_026 = sum_53_3_026 + sum_53_3_058 + sum_53_3_090 + sum_53_3_122 + sum_53_3_154;
double sum_32_5_027 = sum_53_3_027 + sum_53_3_059 + sum_53_3_091 + sum_53_3_123 + sum_53_3_155;
double sum_32_5_028 = sum_53_3_028 + sum_53_3_060 + sum_53_3_092 + sum_53_3_124 + sum_53_3_156;
double sum_32_5_029 = sum_53_3_029 + sum_53_3_061 + sum_53_3_093 + sum_53_3_125 + sum_53_3_157;
double sum_32_5_030 = sum_53_3_030 + sum_53_3_062 + sum_53_3_094 + sum_53_3_126 + sum_53_3_158;
double sum_32_5_031 = sum_53_3_031 + sum_53_3_063 + sum_53_3_095 + sum_53_3_127 + sum_53_3_159;

/////////////////////////////////////////////////////////////////////////////////////

//frequency level id 1
c2.v[0] += (sum_160_1_000)*MainFormSLS->hh[0];
c2.v[0] += (sum_160_1_001)*MainFormSLS->hh[1];
c2.v[0] += (sum_160_1_002)*MainFormSLS->hh[2];
c2.v[0] += (sum_160_1_003)*MainFormSLS->hh[3];
c2.v[0] += (sum_160_1_004)*MainFormSLS->hh[4];
c2.v[0] += (sum_160_1_005)*MainFormSLS->hh[5];
c2.v[0] += (sum_160_1_006)*MainFormSLS->hh[6];
c2.v[0] += (sum_160_1_007)*MainFormSLS->hh[7];
c2.v[0] += (sum_160_1_008)*MainFormSLS->hh[8];
c2.v[0] += (sum_160_1_009)*MainFormSLS->hh[9];
c2.v[0] += (sum_160_1_010)*MainFormSLS->hh[10];
c2.v[0] += (sum_160_1_011)*MainFormSLS->hh[11];
c2.v[0] += (sum_160_1_012)*MainFormSLS->hh[12];
c2.v[0] += (sum_160_1_013)*MainFormSLS->hh[13];
c2.v[0] += (sum_160_1_014)*MainFormSLS->hh[14];
c2.v[0] += (sum_160_1_015)*MainFormSLS->hh[15];
c2.v[0] += (sum_160_1_016)*MainFormSLS->hh[16];
c2.v[0] += (sum_160_1_017)*MainFormSLS->hh[17];
c2.v[0] += (sum_160_1_018)*MainFormSLS->hh[18];
c2.v[0] += (sum_160_1_019)*MainFormSLS->hh[19];
c2.v[0] += (sum_160_1_020)*MainFormSLS->hh[20];
c2.v[0] += (sum_160_1_021)*MainFormSLS->hh[21];
c2.v[0] += (sum_160_1_022)*MainFormSLS->hh[22];
c2.v[0] += (sum_160_1_023)*MainFormSLS->hh[23];
c2.v[0] += (sum_160_1_024)*MainFormSLS->hh[24];
c2.v[0] += (sum_160_1_025)*MainFormSLS->hh[25];
c2.v[0] += (sum_160_1_026)*MainFormSLS->hh[26];
c2.v[0] += (sum_160_1_027)*MainFormSLS->hh[27];
c2.v[0] += (sum_160_1_028)*MainFormSLS->hh[28];
c2.v[0] += (sum_160_1_029)*MainFormSLS->hh[29];
c2.v[0] += (sum_160_1_030)*MainFormSLS->hh[30];
c2.v[0] += (sum_160_1_031)*MainFormSLS->hh[31];
c2.v[0] += (sum_160_1_032)*MainFormSLS->hh[32];
c2.v[0] += (sum_160_1_033)*MainFormSLS->hh[33];
c2.v[0] += (sum_160_1_034)*MainFormSLS->hh[34];
c2.v[0] += (sum_160_1_035)*MainFormSLS->hh[35];
c2.v[0] += (sum_160_1_036)*MainFormSLS->hh[36];
c2.v[0] += (sum_160_1_037)*MainFormSLS->hh[37];
c2.v[0] += (sum_160_1_038)*MainFormSLS->hh[38];
c2.v[0] += (sum_160_1_039)*MainFormSLS->hh[39];
c2.v[0] += (sum_160_1_040)*MainFormSLS->hh[40];
c2.v[0] += (sum_160_1_041)*MainFormSLS->hh[41];
c2.v[0] += (sum_160_1_042)*MainFormSLS->hh[42];
c2.v[0] += (sum_160_1_043)*MainFormSLS->hh[43];
c2.v[0] += (sum_160_1_044)*MainFormSLS->hh[44];
c2.v[0] += (sum_160_1_045)*MainFormSLS->hh[45];
c2.v[0] += (sum_160_1_046)*MainFormSLS->hh[46];
c2.v[0] += (sum_160_1_047)*MainFormSLS->hh[47];
c2.v[0] += (sum_160_1_048)*MainFormSLS->hh[48];
c2.v[0] += (sum_160_1_049)*MainFormSLS->hh[49];
c2.v[0] += (sum_160_1_050)*MainFormSLS->hh[50];
c2.v[0] += (sum_160_1_051)*MainFormSLS->hh[51];
c2.v[0] += (sum_160_1_052)*MainFormSLS->hh[52];
c2.v[0] += (sum_160_1_053)*MainFormSLS->hh[53];
c2.v[0] += (sum_160_1_054)*MainFormSLS->hh[54];
c2.v[0] += (sum_160_1_055)*MainFormSLS->hh[55];
c2.v[0] += (sum_160_1_056)*MainFormSLS->hh[56];
c2.v[0] += (sum_160_1_057)*MainFormSLS->hh[57];
c2.v[0] += (sum_160_1_058)*MainFormSLS->hh[58];
c2.v[0] += (sum_160_1_059)*MainFormSLS->hh[59];
c2.v[0] += (sum_160_1_060)*MainFormSLS->hh[60];
c2.v[0] += (sum_160_1_061)*MainFormSLS->hh[61];
c2.v[0] += (sum_160_1_062)*MainFormSLS->hh[62];
c2.v[0] += (sum_160_1_063)*MainFormSLS->hh[63];
c2.v[0] += (sum_160_1_064)*MainFormSLS->hh[64];
c2.v[0] += (sum_160_1_065)*MainFormSLS->hh[65];
c2.v[0] += (sum_160_1_066)*MainFormSLS->hh[66];
c2.v[0] += (sum_160_1_067)*MainFormSLS->hh[67];
c2.v[0] += (sum_160_1_068)*MainFormSLS->hh[68];
c2.v[0] += (sum_160_1_069)*MainFormSLS->hh[69];
c2.v[0] += (sum_160_1_070)*MainFormSLS->hh[70];
c2.v[0] += (sum_160_1_071)*MainFormSLS->hh[71];
c2.v[0] += (sum_160_1_072)*MainFormSLS->hh[72];
c2.v[0] += (sum_160_1_073)*MainFormSLS->hh[73];
c2.v[0] += (sum_160_1_074)*MainFormSLS->hh[74];
c2.v[0] += (sum_160_1_075)*MainFormSLS->hh[75];
c2.v[0] += (sum_160_1_076)*MainFormSLS->hh[76];
c2.v[0] += (sum_160_1_077)*MainFormSLS->hh[77];
c2.v[0] += (sum_160_1_078)*MainFormSLS->hh[78];
c2.v[0] += (sum_160_1_079)*MainFormSLS->hh[79];
c2.v[0] += (sum_160_1_080)*MainFormSLS->hh[80];
c2.v[0] += (sum_160_1_081)*MainFormSLS->hh[81];
c2.v[0] += (sum_160_1_082)*MainFormSLS->hh[82];
c2.v[0] += (sum_160_1_083)*MainFormSLS->hh[83];
c2.v[0] += (sum_160_1_084)*MainFormSLS->hh[84];
c2.v[0] += (sum_160_1_085)*MainFormSLS->hh[85];
c2.v[0] += (sum_160_1_086)*MainFormSLS->hh[86];
c2.v[0] += (sum_160_1_087)*MainFormSLS->hh[87];
c2.v[0] += (sum_160_1_088)*MainFormSLS->hh[88];
c2.v[0] += (sum_160_1_089)*MainFormSLS->hh[89];
c2.v[0] += (sum_160_1_090)*MainFormSLS->hh[90];
c2.v[0] += (sum_160_1_091)*MainFormSLS->hh[91];
c2.v[0] += (sum_160_1_092)*MainFormSLS->hh[92];
c2.v[0] += (sum_160_1_093)*MainFormSLS->hh[93];
c2.v[0] += (sum_160_1_094)*MainFormSLS->hh[94];
c2.v[0] += (sum_160_1_095)*MainFormSLS->hh[95];
c2.v[0] += (sum_160_1_096)*MainFormSLS->hh[96];
c2.v[0] += (sum_160_1_097)*MainFormSLS->hh[97];
c2.v[0] += (sum_160_1_098)*MainFormSLS->hh[98];
c2.v[0] += (sum_160_1_099)*MainFormSLS->hh[99];
c2.v[0] += (sum_160_1_100)*MainFormSLS->hh[100];
c2.v[0] += (sum_160_1_101)*MainFormSLS->hh[101];
c2.v[0] += (sum_160_1_102)*MainFormSLS->hh[102];
c2.v[0] += (sum_160_1_103)*MainFormSLS->hh[103];
c2.v[0] += (sum_160_1_104)*MainFormSLS->hh[104];
c2.v[0] += (sum_160_1_105)*MainFormSLS->hh[105];
c2.v[0] += (sum_160_1_106)*MainFormSLS->hh[106];
c2.v[0] += (sum_160_1_107)*MainFormSLS->hh[107];
c2.v[0] += (sum_160_1_108)*MainFormSLS->hh[108];
c2.v[0] += (sum_160_1_109)*MainFormSLS->hh[109];
c2.v[0] += (sum_160_1_110)*MainFormSLS->hh[110];
c2.v[0] += (sum_160_1_111)*MainFormSLS->hh[111];
c2.v[0] += (sum_160_1_112)*MainFormSLS->hh[112];
c2.v[0] += (sum_160_1_113)*MainFormSLS->hh[113];
c2.v[0] += (sum_160_1_114)*MainFormSLS->hh[114];
c2.v[0] += (sum_160_1_115)*MainFormSLS->hh[115];
c2.v[0] += (sum_160_1_116)*MainFormSLS->hh[116];
c2.v[0] += (sum_160_1_117)*MainFormSLS->hh[117];
c2.v[0] += (sum_160_1_118)*MainFormSLS->hh[118];
c2.v[0] += (sum_160_1_119)*MainFormSLS->hh[119];
c2.v[0] += (sum_160_1_120)*MainFormSLS->hh[120];
c2.v[0] += (sum_160_1_121)*MainFormSLS->hh[121];
c2.v[0] += (sum_160_1_122)*MainFormSLS->hh[122];
c2.v[0] += (sum_160_1_123)*MainFormSLS->hh[123];
c2.v[0] += (sum_160_1_124)*MainFormSLS->hh[124];
c2.v[0] += (sum_160_1_125)*MainFormSLS->hh[125];
c2.v[0] += (sum_160_1_126)*MainFormSLS->hh[126];
c2.v[0] += (sum_160_1_127)*MainFormSLS->hh[127];
c2.v[0] += (sum_160_1_128)*MainFormSLS->hh[128];
c2.v[0] += (sum_160_1_129)*MainFormSLS->hh[129];
c2.v[0] += (sum_160_1_130)*MainFormSLS->hh[130];
c2.v[0] += (sum_160_1_131)*MainFormSLS->hh[131];
c2.v[0] += (sum_160_1_132)*MainFormSLS->hh[132];
c2.v[0] += (sum_160_1_133)*MainFormSLS->hh[133];
c2.v[0] += (sum_160_1_134)*MainFormSLS->hh[134];
c2.v[0] += (sum_160_1_135)*MainFormSLS->hh[135];
c2.v[0] += (sum_160_1_136)*MainFormSLS->hh[136];
c2.v[0] += (sum_160_1_137)*MainFormSLS->hh[137];
c2.v[0] += (sum_160_1_138)*MainFormSLS->hh[138];
c2.v[0] += (sum_160_1_139)*MainFormSLS->hh[139];
c2.v[0] += (sum_160_1_140)*MainFormSLS->hh[140];
c2.v[0] += (sum_160_1_141)*MainFormSLS->hh[141];
c2.v[0] += (sum_160_1_142)*MainFormSLS->hh[142];
c2.v[0] += (sum_160_1_143)*MainFormSLS->hh[143];
c2.v[0] += (sum_160_1_144)*MainFormSLS->hh[144];
c2.v[0] += (sum_160_1_145)*MainFormSLS->hh[145];
c2.v[0] += (sum_160_1_146)*MainFormSLS->hh[146];
c2.v[0] += (sum_160_1_147)*MainFormSLS->hh[147];
c2.v[0] += (sum_160_1_148)*MainFormSLS->hh[148];
c2.v[0] += (sum_160_1_149)*MainFormSLS->hh[149];
c2.v[0] += (sum_160_1_150)*MainFormSLS->hh[150];
c2.v[0] += (sum_160_1_151)*MainFormSLS->hh[151];
c2.v[0] += (sum_160_1_152)*MainFormSLS->hh[152];
c2.v[0] += (sum_160_1_153)*MainFormSLS->hh[153];
c2.v[0] += (sum_160_1_154)*MainFormSLS->hh[154];
c2.v[0] += (sum_160_1_155)*MainFormSLS->hh[155];
c2.v[0] += (sum_160_1_156)*MainFormSLS->hh[156];
c2.v[0] += (sum_160_1_157)*MainFormSLS->hh[157];
c2.v[0] += (sum_160_1_158)*MainFormSLS->hh[158];
c2.v[0] += (sum_160_1_159)*MainFormSLS->hh[159];

//frequency level id 3
c2.v[1] += (sum_160_1_000)*MainFormSLS->hh[0];
c2.v[1] += (sum_160_1_001)*MainFormSLS->hh[3];
c2.v[1] += (sum_160_1_002)*MainFormSLS->hh[6];
c2.v[1] += (sum_160_1_003)*MainFormSLS->hh[9];
c2.v[1] += (sum_160_1_004)*MainFormSLS->hh[12];
c2.v[1] += (sum_160_1_005)*MainFormSLS->hh[15];
c2.v[1] += (sum_160_1_006)*MainFormSLS->hh[18];
c2.v[1] += (sum_160_1_007)*MainFormSLS->hh[21];
c2.v[1] += (sum_160_1_008)*MainFormSLS->hh[24];
c2.v[1] += (sum_160_1_009)*MainFormSLS->hh[27];
c2.v[1] += (sum_160_1_010)*MainFormSLS->hh[30];
c2.v[1] += (sum_160_1_011)*MainFormSLS->hh[33];
c2.v[1] += (sum_160_1_012)*MainFormSLS->hh[36];
c2.v[1] += (sum_160_1_013)*MainFormSLS->hh[39];
c2.v[1] += (sum_160_1_014)*MainFormSLS->hh[42];
c2.v[1] += (sum_160_1_015)*MainFormSLS->hh[45];
c2.v[1] += (sum_160_1_016)*MainFormSLS->hh[48];
c2.v[1] += (sum_160_1_017)*MainFormSLS->hh[51];
c2.v[1] += (sum_160_1_018)*MainFormSLS->hh[54];
c2.v[1] += (sum_160_1_019)*MainFormSLS->hh[57];
c2.v[1] += (sum_160_1_020)*MainFormSLS->hh[60];
c2.v[1] += (sum_160_1_021)*MainFormSLS->hh[63];
c2.v[1] += (sum_160_1_022)*MainFormSLS->hh[66];
c2.v[1] += (sum_160_1_023)*MainFormSLS->hh[69];
c2.v[1] += (sum_160_1_024)*MainFormSLS->hh[72];
c2.v[1] += (sum_160_1_025)*MainFormSLS->hh[75];
c2.v[1] += (sum_160_1_026)*MainFormSLS->hh[78];
c2.v[1] += (sum_160_1_027)*MainFormSLS->hh[81];
c2.v[1] += (sum_160_1_028)*MainFormSLS->hh[84];
c2.v[1] += (sum_160_1_029)*MainFormSLS->hh[87];
c2.v[1] += (sum_160_1_030)*MainFormSLS->hh[90];
c2.v[1] += (sum_160_1_031)*MainFormSLS->hh[93];
c2.v[1] += (sum_160_1_032)*MainFormSLS->hh[96];
c2.v[1] += (sum_160_1_033)*MainFormSLS->hh[99];
c2.v[1] += (sum_160_1_034)*MainFormSLS->hh[102];
c2.v[1] += (sum_160_1_035)*MainFormSLS->hh[105];
c2.v[1] += (sum_160_1_036)*MainFormSLS->hh[108];
c2.v[1] += (sum_160_1_037)*MainFormSLS->hh[111];
c2.v[1] += (sum_160_1_038)*MainFormSLS->hh[114];
c2.v[1] += (sum_160_1_039)*MainFormSLS->hh[117];
c2.v[1] += (sum_160_1_040)*MainFormSLS->hh[120];
c2.v[1] += (sum_160_1_041)*MainFormSLS->hh[123];
c2.v[1] += (sum_160_1_042)*MainFormSLS->hh[126];
c2.v[1] += (sum_160_1_043)*MainFormSLS->hh[129];
c2.v[1] += (sum_160_1_044)*MainFormSLS->hh[132];
c2.v[1] += (sum_160_1_045)*MainFormSLS->hh[135];
c2.v[1] += (sum_160_1_046)*MainFormSLS->hh[138];
c2.v[1] += (sum_160_1_047)*MainFormSLS->hh[141];
c2.v[1] += (sum_160_1_048)*MainFormSLS->hh[144];
c2.v[1] += (sum_160_1_049)*MainFormSLS->hh[147];
c2.v[1] += (sum_160_1_050)*MainFormSLS->hh[150];
c2.v[1] += (sum_160_1_051)*MainFormSLS->hh[153];
c2.v[1] += (sum_160_1_052)*MainFormSLS->hh[156];
c2.v[1] += (sum_160_1_053)*MainFormSLS->hh[159];
c2.v[1] += (sum_160_1_054)*MainFormSLS->hh[2];
c2.v[1] += (sum_160_1_055)*MainFormSLS->hh[5];
c2.v[1] += (sum_160_1_056)*MainFormSLS->hh[8];
c2.v[1] += (sum_160_1_057)*MainFormSLS->hh[11];
c2.v[1] += (sum_160_1_058)*MainFormSLS->hh[14];
c2.v[1] += (sum_160_1_059)*MainFormSLS->hh[17];
c2.v[1] += (sum_160_1_060)*MainFormSLS->hh[20];
c2.v[1] += (sum_160_1_061)*MainFormSLS->hh[23];
c2.v[1] += (sum_160_1_062)*MainFormSLS->hh[26];
c2.v[1] += (sum_160_1_063)*MainFormSLS->hh[29];
c2.v[1] += (sum_160_1_064)*MainFormSLS->hh[32];
c2.v[1] += (sum_160_1_065)*MainFormSLS->hh[35];
c2.v[1] += (sum_160_1_066)*MainFormSLS->hh[38];
c2.v[1] += (sum_160_1_067)*MainFormSLS->hh[41];
c2.v[1] += (sum_160_1_068)*MainFormSLS->hh[44];
c2.v[1] += (sum_160_1_069)*MainFormSLS->hh[47];
c2.v[1] += (sum_160_1_070)*MainFormSLS->hh[50];
c2.v[1] += (sum_160_1_071)*MainFormSLS->hh[53];
c2.v[1] += (sum_160_1_072)*MainFormSLS->hh[56];
c2.v[1] += (sum_160_1_073)*MainFormSLS->hh[59];
c2.v[1] += (sum_160_1_074)*MainFormSLS->hh[62];
c2.v[1] += (sum_160_1_075)*MainFormSLS->hh[65];
c2.v[1] += (sum_160_1_076)*MainFormSLS->hh[68];
c2.v[1] += (sum_160_1_077)*MainFormSLS->hh[71];
c2.v[1] += (sum_160_1_078)*MainFormSLS->hh[74];
c2.v[1] += (sum_160_1_079)*MainFormSLS->hh[77];
c2.v[1] += (sum_160_1_080)*MainFormSLS->hh[80];
c2.v[1] += (sum_160_1_081)*MainFormSLS->hh[83];
c2.v[1] += (sum_160_1_082)*MainFormSLS->hh[86];
c2.v[1] += (sum_160_1_083)*MainFormSLS->hh[89];
c2.v[1] += (sum_160_1_084)*MainFormSLS->hh[92];
c2.v[1] += (sum_160_1_085)*MainFormSLS->hh[95];
c2.v[1] += (sum_160_1_086)*MainFormSLS->hh[98];
c2.v[1] += (sum_160_1_087)*MainFormSLS->hh[101];
c2.v[1] += (sum_160_1_088)*MainFormSLS->hh[104];
c2.v[1] += (sum_160_1_089)*MainFormSLS->hh[107];
c2.v[1] += (sum_160_1_090)*MainFormSLS->hh[110];
c2.v[1] += (sum_160_1_091)*MainFormSLS->hh[113];
c2.v[1] += (sum_160_1_092)*MainFormSLS->hh[116];
c2.v[1] += (sum_160_1_093)*MainFormSLS->hh[119];
c2.v[1] += (sum_160_1_094)*MainFormSLS->hh[122];
c2.v[1] += (sum_160_1_095)*MainFormSLS->hh[125];
c2.v[1] += (sum_160_1_096)*MainFormSLS->hh[128];
c2.v[1] += (sum_160_1_097)*MainFormSLS->hh[131];
c2.v[1] += (sum_160_1_098)*MainFormSLS->hh[134];
c2.v[1] += (sum_160_1_099)*MainFormSLS->hh[137];
c2.v[1] += (sum_160_1_100)*MainFormSLS->hh[140];
c2.v[1] += (sum_160_1_101)*MainFormSLS->hh[143];
c2.v[1] += (sum_160_1_102)*MainFormSLS->hh[146];
c2.v[1] += (sum_160_1_103)*MainFormSLS->hh[149];
c2.v[1] += (sum_160_1_104)*MainFormSLS->hh[152];
c2.v[1] += (sum_160_1_105)*MainFormSLS->hh[155];
c2.v[1] += (sum_160_1_106)*MainFormSLS->hh[158];
c2.v[1] += (sum_160_1_107)*MainFormSLS->hh[1];
c2.v[1] += (sum_160_1_108)*MainFormSLS->hh[4];
c2.v[1] += (sum_160_1_109)*MainFormSLS->hh[7];
c2.v[1] += (sum_160_1_110)*MainFormSLS->hh[10];
c2.v[1] += (sum_160_1_111)*MainFormSLS->hh[13];
c2.v[1] += (sum_160_1_112)*MainFormSLS->hh[16];
c2.v[1] += (sum_160_1_113)*MainFormSLS->hh[19];
c2.v[1] += (sum_160_1_114)*MainFormSLS->hh[22];
c2.v[1] += (sum_160_1_115)*MainFormSLS->hh[25];
c2.v[1] += (sum_160_1_116)*MainFormSLS->hh[28];
c2.v[1] += (sum_160_1_117)*MainFormSLS->hh[31];
c2.v[1] += (sum_160_1_118)*MainFormSLS->hh[34];
c2.v[1] += (sum_160_1_119)*MainFormSLS->hh[37];
c2.v[1] += (sum_160_1_120)*MainFormSLS->hh[40];
c2.v[1] += (sum_160_1_121)*MainFormSLS->hh[43];
c2.v[1] += (sum_160_1_122)*MainFormSLS->hh[46];
c2.v[1] += (sum_160_1_123)*MainFormSLS->hh[49];
c2.v[1] += (sum_160_1_124)*MainFormSLS->hh[52];
c2.v[1] += (sum_160_1_125)*MainFormSLS->hh[55];
c2.v[1] += (sum_160_1_126)*MainFormSLS->hh[58];
c2.v[1] += (sum_160_1_127)*MainFormSLS->hh[61];
c2.v[1] += (sum_160_1_128)*MainFormSLS->hh[64];
c2.v[1] += (sum_160_1_129)*MainFormSLS->hh[67];
c2.v[1] += (sum_160_1_130)*MainFormSLS->hh[70];
c2.v[1] += (sum_160_1_131)*MainFormSLS->hh[73];
c2.v[1] += (sum_160_1_132)*MainFormSLS->hh[76];
c2.v[1] += (sum_160_1_133)*MainFormSLS->hh[79];
c2.v[1] += (sum_160_1_134)*MainFormSLS->hh[82];
c2.v[1] += (sum_160_1_135)*MainFormSLS->hh[85];
c2.v[1] += (sum_160_1_136)*MainFormSLS->hh[88];
c2.v[1] += (sum_160_1_137)*MainFormSLS->hh[91];
c2.v[1] += (sum_160_1_138)*MainFormSLS->hh[94];
c2.v[1] += (sum_160_1_139)*MainFormSLS->hh[97];
c2.v[1] += (sum_160_1_140)*MainFormSLS->hh[100];
c2.v[1] += (sum_160_1_141)*MainFormSLS->hh[103];
c2.v[1] += (sum_160_1_142)*MainFormSLS->hh[106];
c2.v[1] += (sum_160_1_143)*MainFormSLS->hh[109];
c2.v[1] += (sum_160_1_144)*MainFormSLS->hh[112];
c2.v[1] += (sum_160_1_145)*MainFormSLS->hh[115];
c2.v[1] += (sum_160_1_146)*MainFormSLS->hh[118];
c2.v[1] += (sum_160_1_147)*MainFormSLS->hh[121];
c2.v[1] += (sum_160_1_148)*MainFormSLS->hh[124];
c2.v[1] += (sum_160_1_149)*MainFormSLS->hh[127];
c2.v[1] += (sum_160_1_150)*MainFormSLS->hh[130];
c2.v[1] += (sum_160_1_151)*MainFormSLS->hh[133];
c2.v[1] += (sum_160_1_152)*MainFormSLS->hh[136];
c2.v[1] += (sum_160_1_153)*MainFormSLS->hh[139];
c2.v[1] += (sum_160_1_154)*MainFormSLS->hh[142];
c2.v[1] += (sum_160_1_155)*MainFormSLS->hh[145];
c2.v[1] += (sum_160_1_156)*MainFormSLS->hh[148];
c2.v[1] += (sum_160_1_157)*MainFormSLS->hh[151];
c2.v[1] += (sum_160_1_158)*MainFormSLS->hh[154];
c2.v[1] += (sum_160_1_159)*MainFormSLS->hh[157];

//frequency level id 5
c2.v[2] += (sum_32_5_000)*MainFormSLS->hh[0];
c2.v[2] += (sum_32_5_001)*MainFormSLS->hh[5];
c2.v[2] += (sum_32_5_002)*MainFormSLS->hh[10];
c2.v[2] += (sum_32_5_003)*MainFormSLS->hh[15];
c2.v[2] += (sum_32_5_004)*MainFormSLS->hh[20];
c2.v[2] += (sum_32_5_005)*MainFormSLS->hh[25];
c2.v[2] += (sum_32_5_006)*MainFormSLS->hh[30];
c2.v[2] += (sum_32_5_007)*MainFormSLS->hh[35];
c2.v[2] += (sum_32_5_008)*MainFormSLS->hh[40];
c2.v[2] += (sum_32_5_009)*MainFormSLS->hh[45];
c2.v[2] += (sum_32_5_010)*MainFormSLS->hh[50];
c2.v[2] += (sum_32_5_011)*MainFormSLS->hh[55];
c2.v[2] += (sum_32_5_012)*MainFormSLS->hh[60];
c2.v[2] += (sum_32_5_013)*MainFormSLS->hh[65];
c2.v[2] += (sum_32_5_014)*MainFormSLS->hh[70];
c2.v[2] += (sum_32_5_015)*MainFormSLS->hh[75];
c2.v[2] += (sum_32_5_016)*MainFormSLS->hh[80];
c2.v[2] += (sum_32_5_017)*MainFormSLS->hh[85];
c2.v[2] += (sum_32_5_018)*MainFormSLS->hh[90];
c2.v[2] += (sum_32_5_019)*MainFormSLS->hh[95];
c2.v[2] += (sum_32_5_020)*MainFormSLS->hh[100];
c2.v[2] += (sum_32_5_021)*MainFormSLS->hh[105];
c2.v[2] += (sum_32_5_022)*MainFormSLS->hh[110];
c2.v[2] += (sum_32_5_023)*MainFormSLS->hh[115];
c2.v[2] += (sum_32_5_024)*MainFormSLS->hh[120];
c2.v[2] += (sum_32_5_025)*MainFormSLS->hh[125];
c2.v[2] += (sum_32_5_026)*MainFormSLS->hh[130];
c2.v[2] += (sum_32_5_027)*MainFormSLS->hh[135];
c2.v[2] += (sum_32_5_028)*MainFormSLS->hh[140];
c2.v[2] += (sum_32_5_029)*MainFormSLS->hh[145];
c2.v[2] += (sum_32_5_030)*MainFormSLS->hh[150];
c2.v[2] += (sum_32_5_031)*MainFormSLS->hh[155];

//frequency level id 7
c2.v[3] += (sum_160_1_000)*MainFormSLS->hh[0];
c2.v[3] += (sum_160_1_001)*MainFormSLS->hh[7];
c2.v[3] += (sum_160_1_002)*MainFormSLS->hh[14];
c2.v[3] += (sum_160_1_003)*MainFormSLS->hh[21];
c2.v[3] += (sum_160_1_004)*MainFormSLS->hh[28];
c2.v[3] += (sum_160_1_005)*MainFormSLS->hh[35];
c2.v[3] += (sum_160_1_006)*MainFormSLS->hh[42];
c2.v[3] += (sum_160_1_007)*MainFormSLS->hh[49];
c2.v[3] += (sum_160_1_008)*MainFormSLS->hh[56];
c2.v[3] += (sum_160_1_009)*MainFormSLS->hh[63];
c2.v[3] += (sum_160_1_010)*MainFormSLS->hh[70];
c2.v[3] += (sum_160_1_011)*MainFormSLS->hh[77];
c2.v[3] += (sum_160_1_012)*MainFormSLS->hh[84];
c2.v[3] += (sum_160_1_013)*MainFormSLS->hh[91];
c2.v[3] += (sum_160_1_014)*MainFormSLS->hh[98];
c2.v[3] += (sum_160_1_015)*MainFormSLS->hh[105];
c2.v[3] += (sum_160_1_016)*MainFormSLS->hh[112];
c2.v[3] += (sum_160_1_017)*MainFormSLS->hh[119];
c2.v[3] += (sum_160_1_018)*MainFormSLS->hh[126];
c2.v[3] += (sum_160_1_019)*MainFormSLS->hh[133];
c2.v[3] += (sum_160_1_020)*MainFormSLS->hh[140];
c2.v[3] += (sum_160_1_021)*MainFormSLS->hh[147];
c2.v[3] += (sum_160_1_022)*MainFormSLS->hh[154];
c2.v[3] += (sum_160_1_023)*MainFormSLS->hh[1];
c2.v[3] += (sum_160_1_024)*MainFormSLS->hh[8];
c2.v[3] += (sum_160_1_025)*MainFormSLS->hh[15];
c2.v[3] += (sum_160_1_026)*MainFormSLS->hh[22];
c2.v[3] += (sum_160_1_027)*MainFormSLS->hh[29];
c2.v[3] += (sum_160_1_028)*MainFormSLS->hh[36];
c2.v[3] += (sum_160_1_029)*MainFormSLS->hh[43];
c2.v[3] += (sum_160_1_030)*MainFormSLS->hh[50];
c2.v[3] += (sum_160_1_031)*MainFormSLS->hh[57];
c2.v[3] += (sum_160_1_032)*MainFormSLS->hh[64];
c2.v[3] += (sum_160_1_033)*MainFormSLS->hh[71];
c2.v[3] += (sum_160_1_034)*MainFormSLS->hh[78];
c2.v[3] += (sum_160_1_035)*MainFormSLS->hh[85];
c2.v[3] += (sum_160_1_036)*MainFormSLS->hh[92];
c2.v[3] += (sum_160_1_037)*MainFormSLS->hh[99];
c2.v[3] += (sum_160_1_038)*MainFormSLS->hh[106];
c2.v[3] += (sum_160_1_039)*MainFormSLS->hh[113];
c2.v[3] += (sum_160_1_040)*MainFormSLS->hh[120];
c2.v[3] += (sum_160_1_041)*MainFormSLS->hh[127];
c2.v[3] += (sum_160_1_042)*MainFormSLS->hh[134];
c2.v[3] += (sum_160_1_043)*MainFormSLS->hh[141];
c2.v[3] += (sum_160_1_044)*MainFormSLS->hh[148];
c2.v[3] += (sum_160_1_045)*MainFormSLS->hh[155];
c2.v[3] += (sum_160_1_046)*MainFormSLS->hh[2];
c2.v[3] += (sum_160_1_047)*MainFormSLS->hh[9];
c2.v[3] += (sum_160_1_048)*MainFormSLS->hh[16];
c2.v[3] += (sum_160_1_049)*MainFormSLS->hh[23];
c2.v[3] += (sum_160_1_050)*MainFormSLS->hh[30];
c2.v[3] += (sum_160_1_051)*MainFormSLS->hh[37];
c2.v[3] += (sum_160_1_052)*MainFormSLS->hh[44];
c2.v[3] += (sum_160_1_053)*MainFormSLS->hh[51];
c2.v[3] += (sum_160_1_054)*MainFormSLS->hh[58];
c2.v[3] += (sum_160_1_055)*MainFormSLS->hh[65];
c2.v[3] += (sum_160_1_056)*MainFormSLS->hh[72];
c2.v[3] += (sum_160_1_057)*MainFormSLS->hh[79];
c2.v[3] += (sum_160_1_058)*MainFormSLS->hh[86];
c2.v[3] += (sum_160_1_059)*MainFormSLS->hh[93];
c2.v[3] += (sum_160_1_060)*MainFormSLS->hh[100];
c2.v[3] += (sum_160_1_061)*MainFormSLS->hh[107];
c2.v[3] += (sum_160_1_062)*MainFormSLS->hh[114];
c2.v[3] += (sum_160_1_063)*MainFormSLS->hh[121];
c2.v[3] += (sum_160_1_064)*MainFormSLS->hh[128];
c2.v[3] += (sum_160_1_065)*MainFormSLS->hh[135];
c2.v[3] += (sum_160_1_066)*MainFormSLS->hh[142];
c2.v[3] += (sum_160_1_067)*MainFormSLS->hh[149];
c2.v[3] += (sum_160_1_068)*MainFormSLS->hh[156];
c2.v[3] += (sum_160_1_069)*MainFormSLS->hh[3];
c2.v[3] += (sum_160_1_070)*MainFormSLS->hh[10];
c2.v[3] += (sum_160_1_071)*MainFormSLS->hh[17];
c2.v[3] += (sum_160_1_072)*MainFormSLS->hh[24];
c2.v[3] += (sum_160_1_073)*MainFormSLS->hh[31];
c2.v[3] += (sum_160_1_074)*MainFormSLS->hh[38];
c2.v[3] += (sum_160_1_075)*MainFormSLS->hh[45];
c2.v[3] += (sum_160_1_076)*MainFormSLS->hh[52];
c2.v[3] += (sum_160_1_077)*MainFormSLS->hh[59];
c2.v[3] += (sum_160_1_078)*MainFormSLS->hh[66];
c2.v[3] += (sum_160_1_079)*MainFormSLS->hh[73];
c2.v[3] += (sum_160_1_080)*MainFormSLS->hh[80];
c2.v[3] += (sum_160_1_081)*MainFormSLS->hh[87];
c2.v[3] += (sum_160_1_082)*MainFormSLS->hh[94];
c2.v[3] += (sum_160_1_083)*MainFormSLS->hh[101];
c2.v[3] += (sum_160_1_084)*MainFormSLS->hh[108];
c2.v[3] += (sum_160_1_085)*MainFormSLS->hh[115];
c2.v[3] += (sum_160_1_086)*MainFormSLS->hh[122];
c2.v[3] += (sum_160_1_087)*MainFormSLS->hh[129];
c2.v[3] += (sum_160_1_088)*MainFormSLS->hh[136];
c2.v[3] += (sum_160_1_089)*MainFormSLS->hh[143];
c2.v[3] += (sum_160_1_090)*MainFormSLS->hh[150];
c2.v[3] += (sum_160_1_091)*MainFormSLS->hh[157];
c2.v[3] += (sum_160_1_092)*MainFormSLS->hh[4];
c2.v[3] += (sum_160_1_093)*MainFormSLS->hh[11];
c2.v[3] += (sum_160_1_094)*MainFormSLS->hh[18];
c2.v[3] += (sum_160_1_095)*MainFormSLS->hh[25];
c2.v[3] += (sum_160_1_096)*MainFormSLS->hh[32];
c2.v[3] += (sum_160_1_097)*MainFormSLS->hh[39];
c2.v[3] += (sum_160_1_098)*MainFormSLS->hh[46];
c2.v[3] += (sum_160_1_099)*MainFormSLS->hh[53];
c2.v[3] += (sum_160_1_100)*MainFormSLS->hh[60];
c2.v[3] += (sum_160_1_101)*MainFormSLS->hh[67];
c2.v[3] += (sum_160_1_102)*MainFormSLS->hh[74];
c2.v[3] += (sum_160_1_103)*MainFormSLS->hh[81];
c2.v[3] += (sum_160_1_104)*MainFormSLS->hh[88];
c2.v[3] += (sum_160_1_105)*MainFormSLS->hh[95];
c2.v[3] += (sum_160_1_106)*MainFormSLS->hh[102];
c2.v[3] += (sum_160_1_107)*MainFormSLS->hh[109];
c2.v[3] += (sum_160_1_108)*MainFormSLS->hh[116];
c2.v[3] += (sum_160_1_109)*MainFormSLS->hh[123];
c2.v[3] += (sum_160_1_110)*MainFormSLS->hh[130];
c2.v[3] += (sum_160_1_111)*MainFormSLS->hh[137];
c2.v[3] += (sum_160_1_112)*MainFormSLS->hh[144];
c2.v[3] += (sum_160_1_113)*MainFormSLS->hh[151];
c2.v[3] += (sum_160_1_114)*MainFormSLS->hh[158];
c2.v[3] += (sum_160_1_115)*MainFormSLS->hh[5];
c2.v[3] += (sum_160_1_116)*MainFormSLS->hh[12];
c2.v[3] += (sum_160_1_117)*MainFormSLS->hh[19];
c2.v[3] += (sum_160_1_118)*MainFormSLS->hh[26];
c2.v[3] += (sum_160_1_119)*MainFormSLS->hh[33];
c2.v[3] += (sum_160_1_120)*MainFormSLS->hh[40];
c2.v[3] += (sum_160_1_121)*MainFormSLS->hh[47];
c2.v[3] += (sum_160_1_122)*MainFormSLS->hh[54];
c2.v[3] += (sum_160_1_123)*MainFormSLS->hh[61];
c2.v[3] += (sum_160_1_124)*MainFormSLS->hh[68];
c2.v[3] += (sum_160_1_125)*MainFormSLS->hh[75];
c2.v[3] += (sum_160_1_126)*MainFormSLS->hh[82];
c2.v[3] += (sum_160_1_127)*MainFormSLS->hh[89];
c2.v[3] += (sum_160_1_128)*MainFormSLS->hh[96];
c2.v[3] += (sum_160_1_129)*MainFormSLS->hh[103];
c2.v[3] += (sum_160_1_130)*MainFormSLS->hh[110];
c2.v[3] += (sum_160_1_131)*MainFormSLS->hh[117];
c2.v[3] += (sum_160_1_132)*MainFormSLS->hh[124];
c2.v[3] += (sum_160_1_133)*MainFormSLS->hh[131];
c2.v[3] += (sum_160_1_134)*MainFormSLS->hh[138];
c2.v[3] += (sum_160_1_135)*MainFormSLS->hh[145];
c2.v[3] += (sum_160_1_136)*MainFormSLS->hh[152];
c2.v[3] += (sum_160_1_137)*MainFormSLS->hh[159];
c2.v[3] += (sum_160_1_138)*MainFormSLS->hh[6];
c2.v[3] += (sum_160_1_139)*MainFormSLS->hh[13];
c2.v[3] += (sum_160_1_140)*MainFormSLS->hh[20];
c2.v[3] += (sum_160_1_141)*MainFormSLS->hh[27];
c2.v[3] += (sum_160_1_142)*MainFormSLS->hh[34];
c2.v[3] += (sum_160_1_143)*MainFormSLS->hh[41];
c2.v[3] += (sum_160_1_144)*MainFormSLS->hh[48];
c2.v[3] += (sum_160_1_145)*MainFormSLS->hh[55];
c2.v[3] += (sum_160_1_146)*MainFormSLS->hh[62];
c2.v[3] += (sum_160_1_147)*MainFormSLS->hh[69];
c2.v[3] += (sum_160_1_148)*MainFormSLS->hh[76];
c2.v[3] += (sum_160_1_149)*MainFormSLS->hh[83];
c2.v[3] += (sum_160_1_150)*MainFormSLS->hh[90];
c2.v[3] += (sum_160_1_151)*MainFormSLS->hh[97];
c2.v[3] += (sum_160_1_152)*MainFormSLS->hh[104];
c2.v[3] += (sum_160_1_153)*MainFormSLS->hh[111];
c2.v[3] += (sum_160_1_154)*MainFormSLS->hh[118];
c2.v[3] += (sum_160_1_155)*MainFormSLS->hh[125];
c2.v[3] += (sum_160_1_156)*MainFormSLS->hh[132];
c2.v[3] += (sum_160_1_157)*MainFormSLS->hh[139];
c2.v[3] += (sum_160_1_158)*MainFormSLS->hh[146];
c2.v[3] += (sum_160_1_159)*MainFormSLS->hh[153];

//frequency level id 9
c2.v[4] += (sum_160_1_000)*MainFormSLS->hh[0];
c2.v[4] += (sum_160_1_001)*MainFormSLS->hh[9];
c2.v[4] += (sum_160_1_002)*MainFormSLS->hh[18];
c2.v[4] += (sum_160_1_003)*MainFormSLS->hh[27];
c2.v[4] += (sum_160_1_004)*MainFormSLS->hh[36];
c2.v[4] += (sum_160_1_005)*MainFormSLS->hh[45];
c2.v[4] += (sum_160_1_006)*MainFormSLS->hh[54];
c2.v[4] += (sum_160_1_007)*MainFormSLS->hh[63];
c2.v[4] += (sum_160_1_008)*MainFormSLS->hh[72];
c2.v[4] += (sum_160_1_009)*MainFormSLS->hh[81];
c2.v[4] += (sum_160_1_010)*MainFormSLS->hh[90];
c2.v[4] += (sum_160_1_011)*MainFormSLS->hh[99];
c2.v[4] += (sum_160_1_012)*MainFormSLS->hh[108];
c2.v[4] += (sum_160_1_013)*MainFormSLS->hh[117];
c2.v[4] += (sum_160_1_014)*MainFormSLS->hh[126];
c2.v[4] += (sum_160_1_015)*MainFormSLS->hh[135];
c2.v[4] += (sum_160_1_016)*MainFormSLS->hh[144];
c2.v[4] += (sum_160_1_017)*MainFormSLS->hh[153];
c2.v[4] += (sum_160_1_018)*MainFormSLS->hh[2];
c2.v[4] += (sum_160_1_019)*MainFormSLS->hh[11];
c2.v[4] += (sum_160_1_020)*MainFormSLS->hh[20];
c2.v[4] += (sum_160_1_021)*MainFormSLS->hh[29];
c2.v[4] += (sum_160_1_022)*MainFormSLS->hh[38];
c2.v[4] += (sum_160_1_023)*MainFormSLS->hh[47];
c2.v[4] += (sum_160_1_024)*MainFormSLS->hh[56];
c2.v[4] += (sum_160_1_025)*MainFormSLS->hh[65];
c2.v[4] += (sum_160_1_026)*MainFormSLS->hh[74];
c2.v[4] += (sum_160_1_027)*MainFormSLS->hh[83];
c2.v[4] += (sum_160_1_028)*MainFormSLS->hh[92];
c2.v[4] += (sum_160_1_029)*MainFormSLS->hh[101];
c2.v[4] += (sum_160_1_030)*MainFormSLS->hh[110];
c2.v[4] += (sum_160_1_031)*MainFormSLS->hh[119];
c2.v[4] += (sum_160_1_032)*MainFormSLS->hh[128];
c2.v[4] += (sum_160_1_033)*MainFormSLS->hh[137];
c2.v[4] += (sum_160_1_034)*MainFormSLS->hh[146];
c2.v[4] += (sum_160_1_035)*MainFormSLS->hh[155];
c2.v[4] += (sum_160_1_036)*MainFormSLS->hh[4];
c2.v[4] += (sum_160_1_037)*MainFormSLS->hh[13];
c2.v[4] += (sum_160_1_038)*MainFormSLS->hh[22];
c2.v[4] += (sum_160_1_039)*MainFormSLS->hh[31];
c2.v[4] += (sum_160_1_040)*MainFormSLS->hh[40];
c2.v[4] += (sum_160_1_041)*MainFormSLS->hh[49];
c2.v[4] += (sum_160_1_042)*MainFormSLS->hh[58];
c2.v[4] += (sum_160_1_043)*MainFormSLS->hh[67];
c2.v[4] += (sum_160_1_044)*MainFormSLS->hh[76];
c2.v[4] += (sum_160_1_045)*MainFormSLS->hh[85];
c2.v[4] += (sum_160_1_046)*MainFormSLS->hh[94];
c2.v[4] += (sum_160_1_047)*MainFormSLS->hh[103];
c2.v[4] += (sum_160_1_048)*MainFormSLS->hh[112];
c2.v[4] += (sum_160_1_049)*MainFormSLS->hh[121];
c2.v[4] += (sum_160_1_050)*MainFormSLS->hh[130];
c2.v[4] += (sum_160_1_051)*MainFormSLS->hh[139];
c2.v[4] += (sum_160_1_052)*MainFormSLS->hh[148];
c2.v[4] += (sum_160_1_053)*MainFormSLS->hh[157];
c2.v[4] += (sum_160_1_054)*MainFormSLS->hh[6];
c2.v[4] += (sum_160_1_055)*MainFormSLS->hh[15];
c2.v[4] += (sum_160_1_056)*MainFormSLS->hh[24];
c2.v[4] += (sum_160_1_057)*MainFormSLS->hh[33];
c2.v[4] += (sum_160_1_058)*MainFormSLS->hh[42];
c2.v[4] += (sum_160_1_059)*MainFormSLS->hh[51];
c2.v[4] += (sum_160_1_060)*MainFormSLS->hh[60];
c2.v[4] += (sum_160_1_061)*MainFormSLS->hh[69];
c2.v[4] += (sum_160_1_062)*MainFormSLS->hh[78];
c2.v[4] += (sum_160_1_063)*MainFormSLS->hh[87];
c2.v[4] += (sum_160_1_064)*MainFormSLS->hh[96];
c2.v[4] += (sum_160_1_065)*MainFormSLS->hh[105];
c2.v[4] += (sum_160_1_066)*MainFormSLS->hh[114];
c2.v[4] += (sum_160_1_067)*MainFormSLS->hh[123];
c2.v[4] += (sum_160_1_068)*MainFormSLS->hh[132];
c2.v[4] += (sum_160_1_069)*MainFormSLS->hh[141];
c2.v[4] += (sum_160_1_070)*MainFormSLS->hh[150];
c2.v[4] += (sum_160_1_071)*MainFormSLS->hh[159];
c2.v[4] += (sum_160_1_072)*MainFormSLS->hh[8];
c2.v[4] += (sum_160_1_073)*MainFormSLS->hh[17];
c2.v[4] += (sum_160_1_074)*MainFormSLS->hh[26];
c2.v[4] += (sum_160_1_075)*MainFormSLS->hh[35];
c2.v[4] += (sum_160_1_076)*MainFormSLS->hh[44];
c2.v[4] += (sum_160_1_077)*MainFormSLS->hh[53];
c2.v[4] += (sum_160_1_078)*MainFormSLS->hh[62];
c2.v[4] += (sum_160_1_079)*MainFormSLS->hh[71];
c2.v[4] += (sum_160_1_080)*MainFormSLS->hh[80];
c2.v[4] += (sum_160_1_081)*MainFormSLS->hh[89];
c2.v[4] += (sum_160_1_082)*MainFormSLS->hh[98];
c2.v[4] += (sum_160_1_083)*MainFormSLS->hh[107];
c2.v[4] += (sum_160_1_084)*MainFormSLS->hh[116];
c2.v[4] += (sum_160_1_085)*MainFormSLS->hh[125];
c2.v[4] += (sum_160_1_086)*MainFormSLS->hh[134];
c2.v[4] += (sum_160_1_087)*MainFormSLS->hh[143];
c2.v[4] += (sum_160_1_088)*MainFormSLS->hh[152];
c2.v[4] += (sum_160_1_089)*MainFormSLS->hh[1];
c2.v[4] += (sum_160_1_090)*MainFormSLS->hh[10];
c2.v[4] += (sum_160_1_091)*MainFormSLS->hh[19];
c2.v[4] += (sum_160_1_092)*MainFormSLS->hh[28];
c2.v[4] += (sum_160_1_093)*MainFormSLS->hh[37];
c2.v[4] += (sum_160_1_094)*MainFormSLS->hh[46];
c2.v[4] += (sum_160_1_095)*MainFormSLS->hh[55];
c2.v[4] += (sum_160_1_096)*MainFormSLS->hh[64];
c2.v[4] += (sum_160_1_097)*MainFormSLS->hh[73];
c2.v[4] += (sum_160_1_098)*MainFormSLS->hh[82];
c2.v[4] += (sum_160_1_099)*MainFormSLS->hh[91];
c2.v[4] += (sum_160_1_100)*MainFormSLS->hh[100];
c2.v[4] += (sum_160_1_101)*MainFormSLS->hh[109];
c2.v[4] += (sum_160_1_102)*MainFormSLS->hh[118];
c2.v[4] += (sum_160_1_103)*MainFormSLS->hh[127];
c2.v[4] += (sum_160_1_104)*MainFormSLS->hh[136];
c2.v[4] += (sum_160_1_105)*MainFormSLS->hh[145];
c2.v[4] += (sum_160_1_106)*MainFormSLS->hh[154];
c2.v[4] += (sum_160_1_107)*MainFormSLS->hh[3];
c2.v[4] += (sum_160_1_108)*MainFormSLS->hh[12];
c2.v[4] += (sum_160_1_109)*MainFormSLS->hh[21];
c2.v[4] += (sum_160_1_110)*MainFormSLS->hh[30];
c2.v[4] += (sum_160_1_111)*MainFormSLS->hh[39];
c2.v[4] += (sum_160_1_112)*MainFormSLS->hh[48];
c2.v[4] += (sum_160_1_113)*MainFormSLS->hh[57];
c2.v[4] += (sum_160_1_114)*MainFormSLS->hh[66];
c2.v[4] += (sum_160_1_115)*MainFormSLS->hh[75];
c2.v[4] += (sum_160_1_116)*MainFormSLS->hh[84];
c2.v[4] += (sum_160_1_117)*MainFormSLS->hh[93];
c2.v[4] += (sum_160_1_118)*MainFormSLS->hh[102];
c2.v[4] += (sum_160_1_119)*MainFormSLS->hh[111];
c2.v[4] += (sum_160_1_120)*MainFormSLS->hh[120];
c2.v[4] += (sum_160_1_121)*MainFormSLS->hh[129];
c2.v[4] += (sum_160_1_122)*MainFormSLS->hh[138];
c2.v[4] += (sum_160_1_123)*MainFormSLS->hh[147];
c2.v[4] += (sum_160_1_124)*MainFormSLS->hh[156];
c2.v[4] += (sum_160_1_125)*MainFormSLS->hh[5];
c2.v[4] += (sum_160_1_126)*MainFormSLS->hh[14];
c2.v[4] += (sum_160_1_127)*MainFormSLS->hh[23];
c2.v[4] += (sum_160_1_128)*MainFormSLS->hh[32];
c2.v[4] += (sum_160_1_129)*MainFormSLS->hh[41];
c2.v[4] += (sum_160_1_130)*MainFormSLS->hh[50];
c2.v[4] += (sum_160_1_131)*MainFormSLS->hh[59];
c2.v[4] += (sum_160_1_132)*MainFormSLS->hh[68];
c2.v[4] += (sum_160_1_133)*MainFormSLS->hh[77];
c2.v[4] += (sum_160_1_134)*MainFormSLS->hh[86];
c2.v[4] += (sum_160_1_135)*MainFormSLS->hh[95];
c2.v[4] += (sum_160_1_136)*MainFormSLS->hh[104];
c2.v[4] += (sum_160_1_137)*MainFormSLS->hh[113];
c2.v[4] += (sum_160_1_138)*MainFormSLS->hh[122];
c2.v[4] += (sum_160_1_139)*MainFormSLS->hh[131];
c2.v[4] += (sum_160_1_140)*MainFormSLS->hh[140];
c2.v[4] += (sum_160_1_141)*MainFormSLS->hh[149];
c2.v[4] += (sum_160_1_142)*MainFormSLS->hh[158];
c2.v[4] += (sum_160_1_143)*MainFormSLS->hh[7];
c2.v[4] += (sum_160_1_144)*MainFormSLS->hh[16];
c2.v[4] += (sum_160_1_145)*MainFormSLS->hh[25];
c2.v[4] += (sum_160_1_146)*MainFormSLS->hh[34];
c2.v[4] += (sum_160_1_147)*MainFormSLS->hh[43];
c2.v[4] += (sum_160_1_148)*MainFormSLS->hh[52];
c2.v[4] += (sum_160_1_149)*MainFormSLS->hh[61];
c2.v[4] += (sum_160_1_150)*MainFormSLS->hh[70];
c2.v[4] += (sum_160_1_151)*MainFormSLS->hh[79];
c2.v[4] += (sum_160_1_152)*MainFormSLS->hh[88];
c2.v[4] += (sum_160_1_153)*MainFormSLS->hh[97];
c2.v[4] += (sum_160_1_154)*MainFormSLS->hh[106];
c2.v[4] += (sum_160_1_155)*MainFormSLS->hh[115];
c2.v[4] += (sum_160_1_156)*MainFormSLS->hh[124];
c2.v[4] += (sum_160_1_157)*MainFormSLS->hh[133];
c2.v[4] += (sum_160_1_158)*MainFormSLS->hh[142];
c2.v[4] += (sum_160_1_159)*MainFormSLS->hh[151];

//frequency level id 11
c2.v[5] += (sum_160_1_000)*MainFormSLS->hh[0];
c2.v[5] += (sum_160_1_001)*MainFormSLS->hh[11];
c2.v[5] += (sum_160_1_002)*MainFormSLS->hh[22];
c2.v[5] += (sum_160_1_003)*MainFormSLS->hh[33];
c2.v[5] += (sum_160_1_004)*MainFormSLS->hh[44];
c2.v[5] += (sum_160_1_005)*MainFormSLS->hh[55];
c2.v[5] += (sum_160_1_006)*MainFormSLS->hh[66];
c2.v[5] += (sum_160_1_007)*MainFormSLS->hh[77];
c2.v[5] += (sum_160_1_008)*MainFormSLS->hh[88];
c2.v[5] += (sum_160_1_009)*MainFormSLS->hh[99];
c2.v[5] += (sum_160_1_010)*MainFormSLS->hh[110];
c2.v[5] += (sum_160_1_011)*MainFormSLS->hh[121];
c2.v[5] += (sum_160_1_012)*MainFormSLS->hh[132];
c2.v[5] += (sum_160_1_013)*MainFormSLS->hh[143];
c2.v[5] += (sum_160_1_014)*MainFormSLS->hh[154];
c2.v[5] += (sum_160_1_015)*MainFormSLS->hh[5];
c2.v[5] += (sum_160_1_016)*MainFormSLS->hh[16];
c2.v[5] += (sum_160_1_017)*MainFormSLS->hh[27];
c2.v[5] += (sum_160_1_018)*MainFormSLS->hh[38];
c2.v[5] += (sum_160_1_019)*MainFormSLS->hh[49];
c2.v[5] += (sum_160_1_020)*MainFormSLS->hh[60];
c2.v[5] += (sum_160_1_021)*MainFormSLS->hh[71];
c2.v[5] += (sum_160_1_022)*MainFormSLS->hh[82];
c2.v[5] += (sum_160_1_023)*MainFormSLS->hh[93];
c2.v[5] += (sum_160_1_024)*MainFormSLS->hh[104];
c2.v[5] += (sum_160_1_025)*MainFormSLS->hh[115];
c2.v[5] += (sum_160_1_026)*MainFormSLS->hh[126];
c2.v[5] += (sum_160_1_027)*MainFormSLS->hh[137];
c2.v[5] += (sum_160_1_028)*MainFormSLS->hh[148];
c2.v[5] += (sum_160_1_029)*MainFormSLS->hh[159];
c2.v[5] += (sum_160_1_030)*MainFormSLS->hh[10];
c2.v[5] += (sum_160_1_031)*MainFormSLS->hh[21];
c2.v[5] += (sum_160_1_032)*MainFormSLS->hh[32];
c2.v[5] += (sum_160_1_033)*MainFormSLS->hh[43];
c2.v[5] += (sum_160_1_034)*MainFormSLS->hh[54];
c2.v[5] += (sum_160_1_035)*MainFormSLS->hh[65];
c2.v[5] += (sum_160_1_036)*MainFormSLS->hh[76];
c2.v[5] += (sum_160_1_037)*MainFormSLS->hh[87];
c2.v[5] += (sum_160_1_038)*MainFormSLS->hh[98];
c2.v[5] += (sum_160_1_039)*MainFormSLS->hh[109];
c2.v[5] += (sum_160_1_040)*MainFormSLS->hh[120];
c2.v[5] += (sum_160_1_041)*MainFormSLS->hh[131];
c2.v[5] += (sum_160_1_042)*MainFormSLS->hh[142];
c2.v[5] += (sum_160_1_043)*MainFormSLS->hh[153];
c2.v[5] += (sum_160_1_044)*MainFormSLS->hh[4];
c2.v[5] += (sum_160_1_045)*MainFormSLS->hh[15];
c2.v[5] += (sum_160_1_046)*MainFormSLS->hh[26];
c2.v[5] += (sum_160_1_047)*MainFormSLS->hh[37];
c2.v[5] += (sum_160_1_048)*MainFormSLS->hh[48];
c2.v[5] += (sum_160_1_049)*MainFormSLS->hh[59];
c2.v[5] += (sum_160_1_050)*MainFormSLS->hh[70];
c2.v[5] += (sum_160_1_051)*MainFormSLS->hh[81];
c2.v[5] += (sum_160_1_052)*MainFormSLS->hh[92];
c2.v[5] += (sum_160_1_053)*MainFormSLS->hh[103];
c2.v[5] += (sum_160_1_054)*MainFormSLS->hh[114];
c2.v[5] += (sum_160_1_055)*MainFormSLS->hh[125];
c2.v[5] += (sum_160_1_056)*MainFormSLS->hh[136];
c2.v[5] += (sum_160_1_057)*MainFormSLS->hh[147];
c2.v[5] += (sum_160_1_058)*MainFormSLS->hh[158];
c2.v[5] += (sum_160_1_059)*MainFormSLS->hh[9];
c2.v[5] += (sum_160_1_060)*MainFormSLS->hh[20];
c2.v[5] += (sum_160_1_061)*MainFormSLS->hh[31];
c2.v[5] += (sum_160_1_062)*MainFormSLS->hh[42];
c2.v[5] += (sum_160_1_063)*MainFormSLS->hh[53];
c2.v[5] += (sum_160_1_064)*MainFormSLS->hh[64];
c2.v[5] += (sum_160_1_065)*MainFormSLS->hh[75];
c2.v[5] += (sum_160_1_066)*MainFormSLS->hh[86];
c2.v[5] += (sum_160_1_067)*MainFormSLS->hh[97];
c2.v[5] += (sum_160_1_068)*MainFormSLS->hh[108];
c2.v[5] += (sum_160_1_069)*MainFormSLS->hh[119];
c2.v[5] += (sum_160_1_070)*MainFormSLS->hh[130];
c2.v[5] += (sum_160_1_071)*MainFormSLS->hh[141];
c2.v[5] += (sum_160_1_072)*MainFormSLS->hh[152];
c2.v[5] += (sum_160_1_073)*MainFormSLS->hh[3];
c2.v[5] += (sum_160_1_074)*MainFormSLS->hh[14];
c2.v[5] += (sum_160_1_075)*MainFormSLS->hh[25];
c2.v[5] += (sum_160_1_076)*MainFormSLS->hh[36];
c2.v[5] += (sum_160_1_077)*MainFormSLS->hh[47];
c2.v[5] += (sum_160_1_078)*MainFormSLS->hh[58];
c2.v[5] += (sum_160_1_079)*MainFormSLS->hh[69];
c2.v[5] += (sum_160_1_080)*MainFormSLS->hh[80];
c2.v[5] += (sum_160_1_081)*MainFormSLS->hh[91];
c2.v[5] += (sum_160_1_082)*MainFormSLS->hh[102];
c2.v[5] += (sum_160_1_083)*MainFormSLS->hh[113];
c2.v[5] += (sum_160_1_084)*MainFormSLS->hh[124];
c2.v[5] += (sum_160_1_085)*MainFormSLS->hh[135];
c2.v[5] += (sum_160_1_086)*MainFormSLS->hh[146];
c2.v[5] += (sum_160_1_087)*MainFormSLS->hh[157];
c2.v[5] += (sum_160_1_088)*MainFormSLS->hh[8];
c2.v[5] += (sum_160_1_089)*MainFormSLS->hh[19];
c2.v[5] += (sum_160_1_090)*MainFormSLS->hh[30];
c2.v[5] += (sum_160_1_091)*MainFormSLS->hh[41];
c2.v[5] += (sum_160_1_092)*MainFormSLS->hh[52];
c2.v[5] += (sum_160_1_093)*MainFormSLS->hh[63];
c2.v[5] += (sum_160_1_094)*MainFormSLS->hh[74];
c2.v[5] += (sum_160_1_095)*MainFormSLS->hh[85];
c2.v[5] += (sum_160_1_096)*MainFormSLS->hh[96];
c2.v[5] += (sum_160_1_097)*MainFormSLS->hh[107];
c2.v[5] += (sum_160_1_098)*MainFormSLS->hh[118];
c2.v[5] += (sum_160_1_099)*MainFormSLS->hh[129];
c2.v[5] += (sum_160_1_100)*MainFormSLS->hh[140];
c2.v[5] += (sum_160_1_101)*MainFormSLS->hh[151];
c2.v[5] += (sum_160_1_102)*MainFormSLS->hh[2];
c2.v[5] += (sum_160_1_103)*MainFormSLS->hh[13];
c2.v[5] += (sum_160_1_104)*MainFormSLS->hh[24];
c2.v[5] += (sum_160_1_105)*MainFormSLS->hh[35];
c2.v[5] += (sum_160_1_106)*MainFormSLS->hh[46];
c2.v[5] += (sum_160_1_107)*MainFormSLS->hh[57];
c2.v[5] += (sum_160_1_108)*MainFormSLS->hh[68];
c2.v[5] += (sum_160_1_109)*MainFormSLS->hh[79];
c2.v[5] += (sum_160_1_110)*MainFormSLS->hh[90];
c2.v[5] += (sum_160_1_111)*MainFormSLS->hh[101];
c2.v[5] += (sum_160_1_112)*MainFormSLS->hh[112];
c2.v[5] += (sum_160_1_113)*MainFormSLS->hh[123];
c2.v[5] += (sum_160_1_114)*MainFormSLS->hh[134];
c2.v[5] += (sum_160_1_115)*MainFormSLS->hh[145];
c2.v[5] += (sum_160_1_116)*MainFormSLS->hh[156];
c2.v[5] += (sum_160_1_117)*MainFormSLS->hh[7];
c2.v[5] += (sum_160_1_118)*MainFormSLS->hh[18];
c2.v[5] += (sum_160_1_119)*MainFormSLS->hh[29];
c2.v[5] += (sum_160_1_120)*MainFormSLS->hh[40];
c2.v[5] += (sum_160_1_121)*MainFormSLS->hh[51];
c2.v[5] += (sum_160_1_122)*MainFormSLS->hh[62];
c2.v[5] += (sum_160_1_123)*MainFormSLS->hh[73];
c2.v[5] += (sum_160_1_124)*MainFormSLS->hh[84];
c2.v[5] += (sum_160_1_125)*MainFormSLS->hh[95];
c2.v[5] += (sum_160_1_126)*MainFormSLS->hh[106];
c2.v[5] += (sum_160_1_127)*MainFormSLS->hh[117];
c2.v[5] += (sum_160_1_128)*MainFormSLS->hh[128];
c2.v[5] += (sum_160_1_129)*MainFormSLS->hh[139];
c2.v[5] += (sum_160_1_130)*MainFormSLS->hh[150];
c2.v[5] += (sum_160_1_131)*MainFormSLS->hh[1];
c2.v[5] += (sum_160_1_132)*MainFormSLS->hh[12];
c2.v[5] += (sum_160_1_133)*MainFormSLS->hh[23];
c2.v[5] += (sum_160_1_134)*MainFormSLS->hh[34];
c2.v[5] += (sum_160_1_135)*MainFormSLS->hh[45];
c2.v[5] += (sum_160_1_136)*MainFormSLS->hh[56];
c2.v[5] += (sum_160_1_137)*MainFormSLS->hh[67];
c2.v[5] += (sum_160_1_138)*MainFormSLS->hh[78];
c2.v[5] += (sum_160_1_139)*MainFormSLS->hh[89];
c2.v[5] += (sum_160_1_140)*MainFormSLS->hh[100];
c2.v[5] += (sum_160_1_141)*MainFormSLS->hh[111];
c2.v[5] += (sum_160_1_142)*MainFormSLS->hh[122];
c2.v[5] += (sum_160_1_143)*MainFormSLS->hh[133];
c2.v[5] += (sum_160_1_144)*MainFormSLS->hh[144];
c2.v[5] += (sum_160_1_145)*MainFormSLS->hh[155];
c2.v[5] += (sum_160_1_146)*MainFormSLS->hh[6];
c2.v[5] += (sum_160_1_147)*MainFormSLS->hh[17];
c2.v[5] += (sum_160_1_148)*MainFormSLS->hh[28];
c2.v[5] += (sum_160_1_149)*MainFormSLS->hh[39];
c2.v[5] += (sum_160_1_150)*MainFormSLS->hh[50];
c2.v[5] += (sum_160_1_151)*MainFormSLS->hh[61];
c2.v[5] += (sum_160_1_152)*MainFormSLS->hh[72];
c2.v[5] += (sum_160_1_153)*MainFormSLS->hh[83];
c2.v[5] += (sum_160_1_154)*MainFormSLS->hh[94];
c2.v[5] += (sum_160_1_155)*MainFormSLS->hh[105];
c2.v[5] += (sum_160_1_156)*MainFormSLS->hh[116];
c2.v[5] += (sum_160_1_157)*MainFormSLS->hh[127];
c2.v[5] += (sum_160_1_158)*MainFormSLS->hh[138];
c2.v[5] += (sum_160_1_159)*MainFormSLS->hh[149];

//frequency level id 13
c2.v[6] += (sum_160_1_000)*MainFormSLS->hh[0];
c2.v[6] += (sum_160_1_001)*MainFormSLS->hh[13];
c2.v[6] += (sum_160_1_002)*MainFormSLS->hh[26];
c2.v[6] += (sum_160_1_003)*MainFormSLS->hh[39];
c2.v[6] += (sum_160_1_004)*MainFormSLS->hh[52];
c2.v[6] += (sum_160_1_005)*MainFormSLS->hh[65];
c2.v[6] += (sum_160_1_006)*MainFormSLS->hh[78];
c2.v[6] += (sum_160_1_007)*MainFormSLS->hh[91];
c2.v[6] += (sum_160_1_008)*MainFormSLS->hh[104];
c2.v[6] += (sum_160_1_009)*MainFormSLS->hh[117];
c2.v[6] += (sum_160_1_010)*MainFormSLS->hh[130];
c2.v[6] += (sum_160_1_011)*MainFormSLS->hh[143];
c2.v[6] += (sum_160_1_012)*MainFormSLS->hh[156];
c2.v[6] += (sum_160_1_013)*MainFormSLS->hh[9];
c2.v[6] += (sum_160_1_014)*MainFormSLS->hh[22];
c2.v[6] += (sum_160_1_015)*MainFormSLS->hh[35];
c2.v[6] += (sum_160_1_016)*MainFormSLS->hh[48];
c2.v[6] += (sum_160_1_017)*MainFormSLS->hh[61];
c2.v[6] += (sum_160_1_018)*MainFormSLS->hh[74];
c2.v[6] += (sum_160_1_019)*MainFormSLS->hh[87];
c2.v[6] += (sum_160_1_020)*MainFormSLS->hh[100];
c2.v[6] += (sum_160_1_021)*MainFormSLS->hh[113];
c2.v[6] += (sum_160_1_022)*MainFormSLS->hh[126];
c2.v[6] += (sum_160_1_023)*MainFormSLS->hh[139];
c2.v[6] += (sum_160_1_024)*MainFormSLS->hh[152];
c2.v[6] += (sum_160_1_025)*MainFormSLS->hh[5];
c2.v[6] += (sum_160_1_026)*MainFormSLS->hh[18];
c2.v[6] += (sum_160_1_027)*MainFormSLS->hh[31];
c2.v[6] += (sum_160_1_028)*MainFormSLS->hh[44];
c2.v[6] += (sum_160_1_029)*MainFormSLS->hh[57];
c2.v[6] += (sum_160_1_030)*MainFormSLS->hh[70];
c2.v[6] += (sum_160_1_031)*MainFormSLS->hh[83];
c2.v[6] += (sum_160_1_032)*MainFormSLS->hh[96];
c2.v[6] += (sum_160_1_033)*MainFormSLS->hh[109];
c2.v[6] += (sum_160_1_034)*MainFormSLS->hh[122];
c2.v[6] += (sum_160_1_035)*MainFormSLS->hh[135];
c2.v[6] += (sum_160_1_036)*MainFormSLS->hh[148];
c2.v[6] += (sum_160_1_037)*MainFormSLS->hh[1];
c2.v[6] += (sum_160_1_038)*MainFormSLS->hh[14];
c2.v[6] += (sum_160_1_039)*MainFormSLS->hh[27];
c2.v[6] += (sum_160_1_040)*MainFormSLS->hh[40];
c2.v[6] += (sum_160_1_041)*MainFormSLS->hh[53];
c2.v[6] += (sum_160_1_042)*MainFormSLS->hh[66];
c2.v[6] += (sum_160_1_043)*MainFormSLS->hh[79];
c2.v[6] += (sum_160_1_044)*MainFormSLS->hh[92];
c2.v[6] += (sum_160_1_045)*MainFormSLS->hh[105];
c2.v[6] += (sum_160_1_046)*MainFormSLS->hh[118];
c2.v[6] += (sum_160_1_047)*MainFormSLS->hh[131];
c2.v[6] += (sum_160_1_048)*MainFormSLS->hh[144];
c2.v[6] += (sum_160_1_049)*MainFormSLS->hh[157];
c2.v[6] += (sum_160_1_050)*MainFormSLS->hh[10];
c2.v[6] += (sum_160_1_051)*MainFormSLS->hh[23];
c2.v[6] += (sum_160_1_052)*MainFormSLS->hh[36];
c2.v[6] += (sum_160_1_053)*MainFormSLS->hh[49];
c2.v[6] += (sum_160_1_054)*MainFormSLS->hh[62];
c2.v[6] += (sum_160_1_055)*MainFormSLS->hh[75];
c2.v[6] += (sum_160_1_056)*MainFormSLS->hh[88];
c2.v[6] += (sum_160_1_057)*MainFormSLS->hh[101];
c2.v[6] += (sum_160_1_058)*MainFormSLS->hh[114];
c2.v[6] += (sum_160_1_059)*MainFormSLS->hh[127];
c2.v[6] += (sum_160_1_060)*MainFormSLS->hh[140];
c2.v[6] += (sum_160_1_061)*MainFormSLS->hh[153];
c2.v[6] += (sum_160_1_062)*MainFormSLS->hh[6];
c2.v[6] += (sum_160_1_063)*MainFormSLS->hh[19];
c2.v[6] += (sum_160_1_064)*MainFormSLS->hh[32];
c2.v[6] += (sum_160_1_065)*MainFormSLS->hh[45];
c2.v[6] += (sum_160_1_066)*MainFormSLS->hh[58];
c2.v[6] += (sum_160_1_067)*MainFormSLS->hh[71];
c2.v[6] += (sum_160_1_068)*MainFormSLS->hh[84];
c2.v[6] += (sum_160_1_069)*MainFormSLS->hh[97];
c2.v[6] += (sum_160_1_070)*MainFormSLS->hh[110];
c2.v[6] += (sum_160_1_071)*MainFormSLS->hh[123];
c2.v[6] += (sum_160_1_072)*MainFormSLS->hh[136];
c2.v[6] += (sum_160_1_073)*MainFormSLS->hh[149];
c2.v[6] += (sum_160_1_074)*MainFormSLS->hh[2];
c2.v[6] += (sum_160_1_075)*MainFormSLS->hh[15];
c2.v[6] += (sum_160_1_076)*MainFormSLS->hh[28];
c2.v[6] += (sum_160_1_077)*MainFormSLS->hh[41];
c2.v[6] += (sum_160_1_078)*MainFormSLS->hh[54];
c2.v[6] += (sum_160_1_079)*MainFormSLS->hh[67];
c2.v[6] += (sum_160_1_080)*MainFormSLS->hh[80];
c2.v[6] += (sum_160_1_081)*MainFormSLS->hh[93];
c2.v[6] += (sum_160_1_082)*MainFormSLS->hh[106];
c2.v[6] += (sum_160_1_083)*MainFormSLS->hh[119];
c2.v[6] += (sum_160_1_084)*MainFormSLS->hh[132];
c2.v[6] += (sum_160_1_085)*MainFormSLS->hh[145];
c2.v[6] += (sum_160_1_086)*MainFormSLS->hh[158];
c2.v[6] += (sum_160_1_087)*MainFormSLS->hh[11];
c2.v[6] += (sum_160_1_088)*MainFormSLS->hh[24];
c2.v[6] += (sum_160_1_089)*MainFormSLS->hh[37];
c2.v[6] += (sum_160_1_090)*MainFormSLS->hh[50];
c2.v[6] += (sum_160_1_091)*MainFormSLS->hh[63];
c2.v[6] += (sum_160_1_092)*MainFormSLS->hh[76];
c2.v[6] += (sum_160_1_093)*MainFormSLS->hh[89];
c2.v[6] += (sum_160_1_094)*MainFormSLS->hh[102];
c2.v[6] += (sum_160_1_095)*MainFormSLS->hh[115];
c2.v[6] += (sum_160_1_096)*MainFormSLS->hh[128];
c2.v[6] += (sum_160_1_097)*MainFormSLS->hh[141];
c2.v[6] += (sum_160_1_098)*MainFormSLS->hh[154];
c2.v[6] += (sum_160_1_099)*MainFormSLS->hh[7];
c2.v[6] += (sum_160_1_100)*MainFormSLS->hh[20];
c2.v[6] += (sum_160_1_101)*MainFormSLS->hh[33];
c2.v[6] += (sum_160_1_102)*MainFormSLS->hh[46];
c2.v[6] += (sum_160_1_103)*MainFormSLS->hh[59];
c2.v[6] += (sum_160_1_104)*MainFormSLS->hh[72];
c2.v[6] += (sum_160_1_105)*MainFormSLS->hh[85];
c2.v[6] += (sum_160_1_106)*MainFormSLS->hh[98];
c2.v[6] += (sum_160_1_107)*MainFormSLS->hh[111];
c2.v[6] += (sum_160_1_108)*MainFormSLS->hh[124];
c2.v[6] += (sum_160_1_109)*MainFormSLS->hh[137];
c2.v[6] += (sum_160_1_110)*MainFormSLS->hh[150];
c2.v[6] += (sum_160_1_111)*MainFormSLS->hh[3];
c2.v[6] += (sum_160_1_112)*MainFormSLS->hh[16];
c2.v[6] += (sum_160_1_113)*MainFormSLS->hh[29];
c2.v[6] += (sum_160_1_114)*MainFormSLS->hh[42];
c2.v[6] += (sum_160_1_115)*MainFormSLS->hh[55];
c2.v[6] += (sum_160_1_116)*MainFormSLS->hh[68];
c2.v[6] += (sum_160_1_117)*MainFormSLS->hh[81];
c2.v[6] += (sum_160_1_118)*MainFormSLS->hh[94];
c2.v[6] += (sum_160_1_119)*MainFormSLS->hh[107];
c2.v[6] += (sum_160_1_120)*MainFormSLS->hh[120];
c2.v[6] += (sum_160_1_121)*MainFormSLS->hh[133];
c2.v[6] += (sum_160_1_122)*MainFormSLS->hh[146];
c2.v[6] += (sum_160_1_123)*MainFormSLS->hh[159];
c2.v[6] += (sum_160_1_124)*MainFormSLS->hh[12];
c2.v[6] += (sum_160_1_125)*MainFormSLS->hh[25];
c2.v[6] += (sum_160_1_126)*MainFormSLS->hh[38];
c2.v[6] += (sum_160_1_127)*MainFormSLS->hh[51];
c2.v[6] += (sum_160_1_128)*MainFormSLS->hh[64];
c2.v[6] += (sum_160_1_129)*MainFormSLS->hh[77];
c2.v[6] += (sum_160_1_130)*MainFormSLS->hh[90];
c2.v[6] += (sum_160_1_131)*MainFormSLS->hh[103];
c2.v[6] += (sum_160_1_132)*MainFormSLS->hh[116];
c2.v[6] += (sum_160_1_133)*MainFormSLS->hh[129];
c2.v[6] += (sum_160_1_134)*MainFormSLS->hh[142];
c2.v[6] += (sum_160_1_135)*MainFormSLS->hh[155];
c2.v[6] += (sum_160_1_136)*MainFormSLS->hh[8];
c2.v[6] += (sum_160_1_137)*MainFormSLS->hh[21];
c2.v[6] += (sum_160_1_138)*MainFormSLS->hh[34];
c2.v[6] += (sum_160_1_139)*MainFormSLS->hh[47];
c2.v[6] += (sum_160_1_140)*MainFormSLS->hh[60];
c2.v[6] += (sum_160_1_141)*MainFormSLS->hh[73];
c2.v[6] += (sum_160_1_142)*MainFormSLS->hh[86];
c2.v[6] += (sum_160_1_143)*MainFormSLS->hh[99];
c2.v[6] += (sum_160_1_144)*MainFormSLS->hh[112];
c2.v[6] += (sum_160_1_145)*MainFormSLS->hh[125];
c2.v[6] += (sum_160_1_146)*MainFormSLS->hh[138];
c2.v[6] += (sum_160_1_147)*MainFormSLS->hh[151];
c2.v[6] += (sum_160_1_148)*MainFormSLS->hh[4];
c2.v[6] += (sum_160_1_149)*MainFormSLS->hh[17];
c2.v[6] += (sum_160_1_150)*MainFormSLS->hh[30];
c2.v[6] += (sum_160_1_151)*MainFormSLS->hh[43];
c2.v[6] += (sum_160_1_152)*MainFormSLS->hh[56];
c2.v[6] += (sum_160_1_153)*MainFormSLS->hh[69];
c2.v[6] += (sum_160_1_154)*MainFormSLS->hh[82];
c2.v[6] += (sum_160_1_155)*MainFormSLS->hh[95];
c2.v[6] += (sum_160_1_156)*MainFormSLS->hh[108];
c2.v[6] += (sum_160_1_157)*MainFormSLS->hh[121];
c2.v[6] += (sum_160_1_158)*MainFormSLS->hh[134];
c2.v[6] += (sum_160_1_159)*MainFormSLS->hh[147];

//frequency level id 15
c2.v[7] += (sum_32_5_000)*MainFormSLS->hh[0];
c2.v[7] += (sum_32_5_001)*MainFormSLS->hh[15];
c2.v[7] += (sum_32_5_002)*MainFormSLS->hh[30];
c2.v[7] += (sum_32_5_003)*MainFormSLS->hh[45];
c2.v[7] += (sum_32_5_004)*MainFormSLS->hh[60];
c2.v[7] += (sum_32_5_005)*MainFormSLS->hh[75];
c2.v[7] += (sum_32_5_006)*MainFormSLS->hh[90];
c2.v[7] += (sum_32_5_007)*MainFormSLS->hh[105];
c2.v[7] += (sum_32_5_008)*MainFormSLS->hh[120];
c2.v[7] += (sum_32_5_009)*MainFormSLS->hh[135];
c2.v[7] += (sum_32_5_010)*MainFormSLS->hh[150];
c2.v[7] += (sum_32_5_011)*MainFormSLS->hh[5];
c2.v[7] += (sum_32_5_012)*MainFormSLS->hh[20];
c2.v[7] += (sum_32_5_013)*MainFormSLS->hh[35];
c2.v[7] += (sum_32_5_014)*MainFormSLS->hh[50];
c2.v[7] += (sum_32_5_015)*MainFormSLS->hh[65];
c2.v[7] += (sum_32_5_016)*MainFormSLS->hh[80];
c2.v[7] += (sum_32_5_017)*MainFormSLS->hh[95];
c2.v[7] += (sum_32_5_018)*MainFormSLS->hh[110];
c2.v[7] += (sum_32_5_019)*MainFormSLS->hh[125];
c2.v[7] += (sum_32_5_020)*MainFormSLS->hh[140];
c2.v[7] += (sum_32_5_021)*MainFormSLS->hh[155];
c2.v[7] += (sum_32_5_022)*MainFormSLS->hh[10];
c2.v[7] += (sum_32_5_023)*MainFormSLS->hh[25];
c2.v[7] += (sum_32_5_024)*MainFormSLS->hh[40];
c2.v[7] += (sum_32_5_025)*MainFormSLS->hh[55];
c2.v[7] += (sum_32_5_026)*MainFormSLS->hh[70];
c2.v[7] += (sum_32_5_027)*MainFormSLS->hh[85];
c2.v[7] += (sum_32_5_028)*MainFormSLS->hh[100];
c2.v[7] += (sum_32_5_029)*MainFormSLS->hh[115];
c2.v[7] += (sum_32_5_030)*MainFormSLS->hh[130];
c2.v[7] += (sum_32_5_031)*MainFormSLS->hh[145];

//frequency level id 17
c2.v[8] += (sum_160_1_000)*MainFormSLS->hh[0];
c2.v[8] += (sum_160_1_001)*MainFormSLS->hh[17];
c2.v[8] += (sum_160_1_002)*MainFormSLS->hh[34];
c2.v[8] += (sum_160_1_003)*MainFormSLS->hh[51];
c2.v[8] += (sum_160_1_004)*MainFormSLS->hh[68];
c2.v[8] += (sum_160_1_005)*MainFormSLS->hh[85];
c2.v[8] += (sum_160_1_006)*MainFormSLS->hh[102];
c2.v[8] += (sum_160_1_007)*MainFormSLS->hh[119];
c2.v[8] += (sum_160_1_008)*MainFormSLS->hh[136];
c2.v[8] += (sum_160_1_009)*MainFormSLS->hh[153];
c2.v[8] += (sum_160_1_010)*MainFormSLS->hh[10];
c2.v[8] += (sum_160_1_011)*MainFormSLS->hh[27];
c2.v[8] += (sum_160_1_012)*MainFormSLS->hh[44];
c2.v[8] += (sum_160_1_013)*MainFormSLS->hh[61];
c2.v[8] += (sum_160_1_014)*MainFormSLS->hh[78];
c2.v[8] += (sum_160_1_015)*MainFormSLS->hh[95];
c2.v[8] += (sum_160_1_016)*MainFormSLS->hh[112];
c2.v[8] += (sum_160_1_017)*MainFormSLS->hh[129];
c2.v[8] += (sum_160_1_018)*MainFormSLS->hh[146];
c2.v[8] += (sum_160_1_019)*MainFormSLS->hh[3];
c2.v[8] += (sum_160_1_020)*MainFormSLS->hh[20];
c2.v[8] += (sum_160_1_021)*MainFormSLS->hh[37];
c2.v[8] += (sum_160_1_022)*MainFormSLS->hh[54];
c2.v[8] += (sum_160_1_023)*MainFormSLS->hh[71];
c2.v[8] += (sum_160_1_024)*MainFormSLS->hh[88];
c2.v[8] += (sum_160_1_025)*MainFormSLS->hh[105];
c2.v[8] += (sum_160_1_026)*MainFormSLS->hh[122];
c2.v[8] += (sum_160_1_027)*MainFormSLS->hh[139];
c2.v[8] += (sum_160_1_028)*MainFormSLS->hh[156];
c2.v[8] += (sum_160_1_029)*MainFormSLS->hh[13];
c2.v[8] += (sum_160_1_030)*MainFormSLS->hh[30];
c2.v[8] += (sum_160_1_031)*MainFormSLS->hh[47];
c2.v[8] += (sum_160_1_032)*MainFormSLS->hh[64];
c2.v[8] += (sum_160_1_033)*MainFormSLS->hh[81];
c2.v[8] += (sum_160_1_034)*MainFormSLS->hh[98];
c2.v[8] += (sum_160_1_035)*MainFormSLS->hh[115];
c2.v[8] += (sum_160_1_036)*MainFormSLS->hh[132];
c2.v[8] += (sum_160_1_037)*MainFormSLS->hh[149];
c2.v[8] += (sum_160_1_038)*MainFormSLS->hh[6];
c2.v[8] += (sum_160_1_039)*MainFormSLS->hh[23];
c2.v[8] += (sum_160_1_040)*MainFormSLS->hh[40];
c2.v[8] += (sum_160_1_041)*MainFormSLS->hh[57];
c2.v[8] += (sum_160_1_042)*MainFormSLS->hh[74];
c2.v[8] += (sum_160_1_043)*MainFormSLS->hh[91];
c2.v[8] += (sum_160_1_044)*MainFormSLS->hh[108];
c2.v[8] += (sum_160_1_045)*MainFormSLS->hh[125];
c2.v[8] += (sum_160_1_046)*MainFormSLS->hh[142];
c2.v[8] += (sum_160_1_047)*MainFormSLS->hh[159];
c2.v[8] += (sum_160_1_048)*MainFormSLS->hh[16];
c2.v[8] += (sum_160_1_049)*MainFormSLS->hh[33];
c2.v[8] += (sum_160_1_050)*MainFormSLS->hh[50];
c2.v[8] += (sum_160_1_051)*MainFormSLS->hh[67];
c2.v[8] += (sum_160_1_052)*MainFormSLS->hh[84];
c2.v[8] += (sum_160_1_053)*MainFormSLS->hh[101];
c2.v[8] += (sum_160_1_054)*MainFormSLS->hh[118];
c2.v[8] += (sum_160_1_055)*MainFormSLS->hh[135];
c2.v[8] += (sum_160_1_056)*MainFormSLS->hh[152];
c2.v[8] += (sum_160_1_057)*MainFormSLS->hh[9];
c2.v[8] += (sum_160_1_058)*MainFormSLS->hh[26];
c2.v[8] += (sum_160_1_059)*MainFormSLS->hh[43];
c2.v[8] += (sum_160_1_060)*MainFormSLS->hh[60];
c2.v[8] += (sum_160_1_061)*MainFormSLS->hh[77];
c2.v[8] += (sum_160_1_062)*MainFormSLS->hh[94];
c2.v[8] += (sum_160_1_063)*MainFormSLS->hh[111];
c2.v[8] += (sum_160_1_064)*MainFormSLS->hh[128];
c2.v[8] += (sum_160_1_065)*MainFormSLS->hh[145];
c2.v[8] += (sum_160_1_066)*MainFormSLS->hh[2];
c2.v[8] += (sum_160_1_067)*MainFormSLS->hh[19];
c2.v[8] += (sum_160_1_068)*MainFormSLS->hh[36];
c2.v[8] += (sum_160_1_069)*MainFormSLS->hh[53];
c2.v[8] += (sum_160_1_070)*MainFormSLS->hh[70];
c2.v[8] += (sum_160_1_071)*MainFormSLS->hh[87];
c2.v[8] += (sum_160_1_072)*MainFormSLS->hh[104];
c2.v[8] += (sum_160_1_073)*MainFormSLS->hh[121];
c2.v[8] += (sum_160_1_074)*MainFormSLS->hh[138];
c2.v[8] += (sum_160_1_075)*MainFormSLS->hh[155];
c2.v[8] += (sum_160_1_076)*MainFormSLS->hh[12];
c2.v[8] += (sum_160_1_077)*MainFormSLS->hh[29];
c2.v[8] += (sum_160_1_078)*MainFormSLS->hh[46];
c2.v[8] += (sum_160_1_079)*MainFormSLS->hh[63];
c2.v[8] += (sum_160_1_080)*MainFormSLS->hh[80];
c2.v[8] += (sum_160_1_081)*MainFormSLS->hh[97];
c2.v[8] += (sum_160_1_082)*MainFormSLS->hh[114];
c2.v[8] += (sum_160_1_083)*MainFormSLS->hh[131];
c2.v[8] += (sum_160_1_084)*MainFormSLS->hh[148];
c2.v[8] += (sum_160_1_085)*MainFormSLS->hh[5];
c2.v[8] += (sum_160_1_086)*MainFormSLS->hh[22];
c2.v[8] += (sum_160_1_087)*MainFormSLS->hh[39];
c2.v[8] += (sum_160_1_088)*MainFormSLS->hh[56];
c2.v[8] += (sum_160_1_089)*MainFormSLS->hh[73];
c2.v[8] += (sum_160_1_090)*MainFormSLS->hh[90];
c2.v[8] += (sum_160_1_091)*MainFormSLS->hh[107];
c2.v[8] += (sum_160_1_092)*MainFormSLS->hh[124];
c2.v[8] += (sum_160_1_093)*MainFormSLS->hh[141];
c2.v[8] += (sum_160_1_094)*MainFormSLS->hh[158];
c2.v[8] += (sum_160_1_095)*MainFormSLS->hh[15];
c2.v[8] += (sum_160_1_096)*MainFormSLS->hh[32];
c2.v[8] += (sum_160_1_097)*MainFormSLS->hh[49];
c2.v[8] += (sum_160_1_098)*MainFormSLS->hh[66];
c2.v[8] += (sum_160_1_099)*MainFormSLS->hh[83];
c2.v[8] += (sum_160_1_100)*MainFormSLS->hh[100];
c2.v[8] += (sum_160_1_101)*MainFormSLS->hh[117];
c2.v[8] += (sum_160_1_102)*MainFormSLS->hh[134];
c2.v[8] += (sum_160_1_103)*MainFormSLS->hh[151];
c2.v[8] += (sum_160_1_104)*MainFormSLS->hh[8];
c2.v[8] += (sum_160_1_105)*MainFormSLS->hh[25];
c2.v[8] += (sum_160_1_106)*MainFormSLS->hh[42];
c2.v[8] += (sum_160_1_107)*MainFormSLS->hh[59];
c2.v[8] += (sum_160_1_108)*MainFormSLS->hh[76];
c2.v[8] += (sum_160_1_109)*MainFormSLS->hh[93];
c2.v[8] += (sum_160_1_110)*MainFormSLS->hh[110];
c2.v[8] += (sum_160_1_111)*MainFormSLS->hh[127];
c2.v[8] += (sum_160_1_112)*MainFormSLS->hh[144];
c2.v[8] += (sum_160_1_113)*MainFormSLS->hh[1];
c2.v[8] += (sum_160_1_114)*MainFormSLS->hh[18];
c2.v[8] += (sum_160_1_115)*MainFormSLS->hh[35];
c2.v[8] += (sum_160_1_116)*MainFormSLS->hh[52];
c2.v[8] += (sum_160_1_117)*MainFormSLS->hh[69];
c2.v[8] += (sum_160_1_118)*MainFormSLS->hh[86];
c2.v[8] += (sum_160_1_119)*MainFormSLS->hh[103];
c2.v[8] += (sum_160_1_120)*MainFormSLS->hh[120];
c2.v[8] += (sum_160_1_121)*MainFormSLS->hh[137];
c2.v[8] += (sum_160_1_122)*MainFormSLS->hh[154];
c2.v[8] += (sum_160_1_123)*MainFormSLS->hh[11];
c2.v[8] += (sum_160_1_124)*MainFormSLS->hh[28];
c2.v[8] += (sum_160_1_125)*MainFormSLS->hh[45];
c2.v[8] += (sum_160_1_126)*MainFormSLS->hh[62];
c2.v[8] += (sum_160_1_127)*MainFormSLS->hh[79];
c2.v[8] += (sum_160_1_128)*MainFormSLS->hh[96];
c2.v[8] += (sum_160_1_129)*MainFormSLS->hh[113];
c2.v[8] += (sum_160_1_130)*MainFormSLS->hh[130];
c2.v[8] += (sum_160_1_131)*MainFormSLS->hh[147];
c2.v[8] += (sum_160_1_132)*MainFormSLS->hh[4];
c2.v[8] += (sum_160_1_133)*MainFormSLS->hh[21];
c2.v[8] += (sum_160_1_134)*MainFormSLS->hh[38];
c2.v[8] += (sum_160_1_135)*MainFormSLS->hh[55];
c2.v[8] += (sum_160_1_136)*MainFormSLS->hh[72];
c2.v[8] += (sum_160_1_137)*MainFormSLS->hh[89];
c2.v[8] += (sum_160_1_138)*MainFormSLS->hh[106];
c2.v[8] += (sum_160_1_139)*MainFormSLS->hh[123];
c2.v[8] += (sum_160_1_140)*MainFormSLS->hh[140];
c2.v[8] += (sum_160_1_141)*MainFormSLS->hh[157];
c2.v[8] += (sum_160_1_142)*MainFormSLS->hh[14];
c2.v[8] += (sum_160_1_143)*MainFormSLS->hh[31];
c2.v[8] += (sum_160_1_144)*MainFormSLS->hh[48];
c2.v[8] += (sum_160_1_145)*MainFormSLS->hh[65];
c2.v[8] += (sum_160_1_146)*MainFormSLS->hh[82];
c2.v[8] += (sum_160_1_147)*MainFormSLS->hh[99];
c2.v[8] += (sum_160_1_148)*MainFormSLS->hh[116];
c2.v[8] += (sum_160_1_149)*MainFormSLS->hh[133];
c2.v[8] += (sum_160_1_150)*MainFormSLS->hh[150];
c2.v[8] += (sum_160_1_151)*MainFormSLS->hh[7];
c2.v[8] += (sum_160_1_152)*MainFormSLS->hh[24];
c2.v[8] += (sum_160_1_153)*MainFormSLS->hh[41];
c2.v[8] += (sum_160_1_154)*MainFormSLS->hh[58];
c2.v[8] += (sum_160_1_155)*MainFormSLS->hh[75];
c2.v[8] += (sum_160_1_156)*MainFormSLS->hh[92];
c2.v[8] += (sum_160_1_157)*MainFormSLS->hh[109];
c2.v[8] += (sum_160_1_158)*MainFormSLS->hh[126];
c2.v[8] += (sum_160_1_159)*MainFormSLS->hh[143];

//frequency level id 19
c2.v[9] += (sum_160_1_000)*MainFormSLS->hh[0];
c2.v[9] += (sum_160_1_001)*MainFormSLS->hh[19];
c2.v[9] += (sum_160_1_002)*MainFormSLS->hh[38];
c2.v[9] += (sum_160_1_003)*MainFormSLS->hh[57];
c2.v[9] += (sum_160_1_004)*MainFormSLS->hh[76];
c2.v[9] += (sum_160_1_005)*MainFormSLS->hh[95];
c2.v[9] += (sum_160_1_006)*MainFormSLS->hh[114];
c2.v[9] += (sum_160_1_007)*MainFormSLS->hh[133];
c2.v[9] += (sum_160_1_008)*MainFormSLS->hh[152];
c2.v[9] += (sum_160_1_009)*MainFormSLS->hh[11];
c2.v[9] += (sum_160_1_010)*MainFormSLS->hh[30];
c2.v[9] += (sum_160_1_011)*MainFormSLS->hh[49];
c2.v[9] += (sum_160_1_012)*MainFormSLS->hh[68];
c2.v[9] += (sum_160_1_013)*MainFormSLS->hh[87];
c2.v[9] += (sum_160_1_014)*MainFormSLS->hh[106];
c2.v[9] += (sum_160_1_015)*MainFormSLS->hh[125];
c2.v[9] += (sum_160_1_016)*MainFormSLS->hh[144];
c2.v[9] += (sum_160_1_017)*MainFormSLS->hh[3];
c2.v[9] += (sum_160_1_018)*MainFormSLS->hh[22];
c2.v[9] += (sum_160_1_019)*MainFormSLS->hh[41];
c2.v[9] += (sum_160_1_020)*MainFormSLS->hh[60];
c2.v[9] += (sum_160_1_021)*MainFormSLS->hh[79];
c2.v[9] += (sum_160_1_022)*MainFormSLS->hh[98];
c2.v[9] += (sum_160_1_023)*MainFormSLS->hh[117];
c2.v[9] += (sum_160_1_024)*MainFormSLS->hh[136];
c2.v[9] += (sum_160_1_025)*MainFormSLS->hh[155];
c2.v[9] += (sum_160_1_026)*MainFormSLS->hh[14];
c2.v[9] += (sum_160_1_027)*MainFormSLS->hh[33];
c2.v[9] += (sum_160_1_028)*MainFormSLS->hh[52];
c2.v[9] += (sum_160_1_029)*MainFormSLS->hh[71];
c2.v[9] += (sum_160_1_030)*MainFormSLS->hh[90];
c2.v[9] += (sum_160_1_031)*MainFormSLS->hh[109];
c2.v[9] += (sum_160_1_032)*MainFormSLS->hh[128];
c2.v[9] += (sum_160_1_033)*MainFormSLS->hh[147];
c2.v[9] += (sum_160_1_034)*MainFormSLS->hh[6];
c2.v[9] += (sum_160_1_035)*MainFormSLS->hh[25];
c2.v[9] += (sum_160_1_036)*MainFormSLS->hh[44];
c2.v[9] += (sum_160_1_037)*MainFormSLS->hh[63];
c2.v[9] += (sum_160_1_038)*MainFormSLS->hh[82];
c2.v[9] += (sum_160_1_039)*MainFormSLS->hh[101];
c2.v[9] += (sum_160_1_040)*MainFormSLS->hh[120];
c2.v[9] += (sum_160_1_041)*MainFormSLS->hh[139];
c2.v[9] += (sum_160_1_042)*MainFormSLS->hh[158];
c2.v[9] += (sum_160_1_043)*MainFormSLS->hh[17];
c2.v[9] += (sum_160_1_044)*MainFormSLS->hh[36];
c2.v[9] += (sum_160_1_045)*MainFormSLS->hh[55];
c2.v[9] += (sum_160_1_046)*MainFormSLS->hh[74];
c2.v[9] += (sum_160_1_047)*MainFormSLS->hh[93];
c2.v[9] += (sum_160_1_048)*MainFormSLS->hh[112];
c2.v[9] += (sum_160_1_049)*MainFormSLS->hh[131];
c2.v[9] += (sum_160_1_050)*MainFormSLS->hh[150];
c2.v[9] += (sum_160_1_051)*MainFormSLS->hh[9];
c2.v[9] += (sum_160_1_052)*MainFormSLS->hh[28];
c2.v[9] += (sum_160_1_053)*MainFormSLS->hh[47];
c2.v[9] += (sum_160_1_054)*MainFormSLS->hh[66];
c2.v[9] += (sum_160_1_055)*MainFormSLS->hh[85];
c2.v[9] += (sum_160_1_056)*MainFormSLS->hh[104];
c2.v[9] += (sum_160_1_057)*MainFormSLS->hh[123];
c2.v[9] += (sum_160_1_058)*MainFormSLS->hh[142];
c2.v[9] += (sum_160_1_059)*MainFormSLS->hh[1];
c2.v[9] += (sum_160_1_060)*MainFormSLS->hh[20];
c2.v[9] += (sum_160_1_061)*MainFormSLS->hh[39];
c2.v[9] += (sum_160_1_062)*MainFormSLS->hh[58];
c2.v[9] += (sum_160_1_063)*MainFormSLS->hh[77];
c2.v[9] += (sum_160_1_064)*MainFormSLS->hh[96];
c2.v[9] += (sum_160_1_065)*MainFormSLS->hh[115];
c2.v[9] += (sum_160_1_066)*MainFormSLS->hh[134];
c2.v[9] += (sum_160_1_067)*MainFormSLS->hh[153];
c2.v[9] += (sum_160_1_068)*MainFormSLS->hh[12];
c2.v[9] += (sum_160_1_069)*MainFormSLS->hh[31];
c2.v[9] += (sum_160_1_070)*MainFormSLS->hh[50];
c2.v[9] += (sum_160_1_071)*MainFormSLS->hh[69];
c2.v[9] += (sum_160_1_072)*MainFormSLS->hh[88];
c2.v[9] += (sum_160_1_073)*MainFormSLS->hh[107];
c2.v[9] += (sum_160_1_074)*MainFormSLS->hh[126];
c2.v[9] += (sum_160_1_075)*MainFormSLS->hh[145];
c2.v[9] += (sum_160_1_076)*MainFormSLS->hh[4];
c2.v[9] += (sum_160_1_077)*MainFormSLS->hh[23];
c2.v[9] += (sum_160_1_078)*MainFormSLS->hh[42];
c2.v[9] += (sum_160_1_079)*MainFormSLS->hh[61];
c2.v[9] += (sum_160_1_080)*MainFormSLS->hh[80];
c2.v[9] += (sum_160_1_081)*MainFormSLS->hh[99];
c2.v[9] += (sum_160_1_082)*MainFormSLS->hh[118];
c2.v[9] += (sum_160_1_083)*MainFormSLS->hh[137];
c2.v[9] += (sum_160_1_084)*MainFormSLS->hh[156];
c2.v[9] += (sum_160_1_085)*MainFormSLS->hh[15];
c2.v[9] += (sum_160_1_086)*MainFormSLS->hh[34];
c2.v[9] += (sum_160_1_087)*MainFormSLS->hh[53];
c2.v[9] += (sum_160_1_088)*MainFormSLS->hh[72];
c2.v[9] += (sum_160_1_089)*MainFormSLS->hh[91];
c2.v[9] += (sum_160_1_090)*MainFormSLS->hh[110];
c2.v[9] += (sum_160_1_091)*MainFormSLS->hh[129];
c2.v[9] += (sum_160_1_092)*MainFormSLS->hh[148];
c2.v[9] += (sum_160_1_093)*MainFormSLS->hh[7];
c2.v[9] += (sum_160_1_094)*MainFormSLS->hh[26];
c2.v[9] += (sum_160_1_095)*MainFormSLS->hh[45];
c2.v[9] += (sum_160_1_096)*MainFormSLS->hh[64];
c2.v[9] += (sum_160_1_097)*MainFormSLS->hh[83];
c2.v[9] += (sum_160_1_098)*MainFormSLS->hh[102];
c2.v[9] += (sum_160_1_099)*MainFormSLS->hh[121];
c2.v[9] += (sum_160_1_100)*MainFormSLS->hh[140];
c2.v[9] += (sum_160_1_101)*MainFormSLS->hh[159];
c2.v[9] += (sum_160_1_102)*MainFormSLS->hh[18];
c2.v[9] += (sum_160_1_103)*MainFormSLS->hh[37];
c2.v[9] += (sum_160_1_104)*MainFormSLS->hh[56];
c2.v[9] += (sum_160_1_105)*MainFormSLS->hh[75];
c2.v[9] += (sum_160_1_106)*MainFormSLS->hh[94];
c2.v[9] += (sum_160_1_107)*MainFormSLS->hh[113];
c2.v[9] += (sum_160_1_108)*MainFormSLS->hh[132];
c2.v[9] += (sum_160_1_109)*MainFormSLS->hh[151];
c2.v[9] += (sum_160_1_110)*MainFormSLS->hh[10];
c2.v[9] += (sum_160_1_111)*MainFormSLS->hh[29];
c2.v[9] += (sum_160_1_112)*MainFormSLS->hh[48];
c2.v[9] += (sum_160_1_113)*MainFormSLS->hh[67];
c2.v[9] += (sum_160_1_114)*MainFormSLS->hh[86];
c2.v[9] += (sum_160_1_115)*MainFormSLS->hh[105];
c2.v[9] += (sum_160_1_116)*MainFormSLS->hh[124];
c2.v[9] += (sum_160_1_117)*MainFormSLS->hh[143];
c2.v[9] += (sum_160_1_118)*MainFormSLS->hh[2];
c2.v[9] += (sum_160_1_119)*MainFormSLS->hh[21];
c2.v[9] += (sum_160_1_120)*MainFormSLS->hh[40];
c2.v[9] += (sum_160_1_121)*MainFormSLS->hh[59];
c2.v[9] += (sum_160_1_122)*MainFormSLS->hh[78];
c2.v[9] += (sum_160_1_123)*MainFormSLS->hh[97];
c2.v[9] += (sum_160_1_124)*MainFormSLS->hh[116];
c2.v[9] += (sum_160_1_125)*MainFormSLS->hh[135];
c2.v[9] += (sum_160_1_126)*MainFormSLS->hh[154];
c2.v[9] += (sum_160_1_127)*MainFormSLS->hh[13];
c2.v[9] += (sum_160_1_128)*MainFormSLS->hh[32];
c2.v[9] += (sum_160_1_129)*MainFormSLS->hh[51];
c2.v[9] += (sum_160_1_130)*MainFormSLS->hh[70];
c2.v[9] += (sum_160_1_131)*MainFormSLS->hh[89];
c2.v[9] += (sum_160_1_132)*MainFormSLS->hh[108];
c2.v[9] += (sum_160_1_133)*MainFormSLS->hh[127];
c2.v[9] += (sum_160_1_134)*MainFormSLS->hh[146];
c2.v[9] += (sum_160_1_135)*MainFormSLS->hh[5];
c2.v[9] += (sum_160_1_136)*MainFormSLS->hh[24];
c2.v[9] += (sum_160_1_137)*MainFormSLS->hh[43];
c2.v[9] += (sum_160_1_138)*MainFormSLS->hh[62];
c2.v[9] += (sum_160_1_139)*MainFormSLS->hh[81];
c2.v[9] += (sum_160_1_140)*MainFormSLS->hh[100];
c2.v[9] += (sum_160_1_141)*MainFormSLS->hh[119];
c2.v[9] += (sum_160_1_142)*MainFormSLS->hh[138];
c2.v[9] += (sum_160_1_143)*MainFormSLS->hh[157];
c2.v[9] += (sum_160_1_144)*MainFormSLS->hh[16];
c2.v[9] += (sum_160_1_145)*MainFormSLS->hh[35];
c2.v[9] += (sum_160_1_146)*MainFormSLS->hh[54];
c2.v[9] += (sum_160_1_147)*MainFormSLS->hh[73];
c2.v[9] += (sum_160_1_148)*MainFormSLS->hh[92];
c2.v[9] += (sum_160_1_149)*MainFormSLS->hh[111];
c2.v[9] += (sum_160_1_150)*MainFormSLS->hh[130];
c2.v[9] += (sum_160_1_151)*MainFormSLS->hh[149];
c2.v[9] += (sum_160_1_152)*MainFormSLS->hh[8];
c2.v[9] += (sum_160_1_153)*MainFormSLS->hh[27];
c2.v[9] += (sum_160_1_154)*MainFormSLS->hh[46];
c2.v[9] += (sum_160_1_155)*MainFormSLS->hh[65];
c2.v[9] += (sum_160_1_156)*MainFormSLS->hh[84];
c2.v[9] += (sum_160_1_157)*MainFormSLS->hh[103];
c2.v[9] += (sum_160_1_158)*MainFormSLS->hh[122];
c2.v[9] += (sum_160_1_159)*MainFormSLS->hh[141];

//frequency level id 21
c2.v[10] += (sum_160_1_000)*MainFormSLS->hh[0];
c2.v[10] += (sum_160_1_001)*MainFormSLS->hh[21];
c2.v[10] += (sum_160_1_002)*MainFormSLS->hh[42];
c2.v[10] += (sum_160_1_003)*MainFormSLS->hh[63];
c2.v[10] += (sum_160_1_004)*MainFormSLS->hh[84];
c2.v[10] += (sum_160_1_005)*MainFormSLS->hh[105];
c2.v[10] += (sum_160_1_006)*MainFormSLS->hh[126];
c2.v[10] += (sum_160_1_007)*MainFormSLS->hh[147];
c2.v[10] += (sum_160_1_008)*MainFormSLS->hh[8];
c2.v[10] += (sum_160_1_009)*MainFormSLS->hh[29];
c2.v[10] += (sum_160_1_010)*MainFormSLS->hh[50];
c2.v[10] += (sum_160_1_011)*MainFormSLS->hh[71];
c2.v[10] += (sum_160_1_012)*MainFormSLS->hh[92];
c2.v[10] += (sum_160_1_013)*MainFormSLS->hh[113];
c2.v[10] += (sum_160_1_014)*MainFormSLS->hh[134];
c2.v[10] += (sum_160_1_015)*MainFormSLS->hh[155];
c2.v[10] += (sum_160_1_016)*MainFormSLS->hh[16];
c2.v[10] += (sum_160_1_017)*MainFormSLS->hh[37];
c2.v[10] += (sum_160_1_018)*MainFormSLS->hh[58];
c2.v[10] += (sum_160_1_019)*MainFormSLS->hh[79];
c2.v[10] += (sum_160_1_020)*MainFormSLS->hh[100];
c2.v[10] += (sum_160_1_021)*MainFormSLS->hh[121];
c2.v[10] += (sum_160_1_022)*MainFormSLS->hh[142];
c2.v[10] += (sum_160_1_023)*MainFormSLS->hh[3];
c2.v[10] += (sum_160_1_024)*MainFormSLS->hh[24];
c2.v[10] += (sum_160_1_025)*MainFormSLS->hh[45];
c2.v[10] += (sum_160_1_026)*MainFormSLS->hh[66];
c2.v[10] += (sum_160_1_027)*MainFormSLS->hh[87];
c2.v[10] += (sum_160_1_028)*MainFormSLS->hh[108];
c2.v[10] += (sum_160_1_029)*MainFormSLS->hh[129];
c2.v[10] += (sum_160_1_030)*MainFormSLS->hh[150];
c2.v[10] += (sum_160_1_031)*MainFormSLS->hh[11];
c2.v[10] += (sum_160_1_032)*MainFormSLS->hh[32];
c2.v[10] += (sum_160_1_033)*MainFormSLS->hh[53];
c2.v[10] += (sum_160_1_034)*MainFormSLS->hh[74];
c2.v[10] += (sum_160_1_035)*MainFormSLS->hh[95];
c2.v[10] += (sum_160_1_036)*MainFormSLS->hh[116];
c2.v[10] += (sum_160_1_037)*MainFormSLS->hh[137];
c2.v[10] += (sum_160_1_038)*MainFormSLS->hh[158];
c2.v[10] += (sum_160_1_039)*MainFormSLS->hh[19];
c2.v[10] += (sum_160_1_040)*MainFormSLS->hh[40];
c2.v[10] += (sum_160_1_041)*MainFormSLS->hh[61];
c2.v[10] += (sum_160_1_042)*MainFormSLS->hh[82];
c2.v[10] += (sum_160_1_043)*MainFormSLS->hh[103];
c2.v[10] += (sum_160_1_044)*MainFormSLS->hh[124];
c2.v[10] += (sum_160_1_045)*MainFormSLS->hh[145];
c2.v[10] += (sum_160_1_046)*MainFormSLS->hh[6];
c2.v[10] += (sum_160_1_047)*MainFormSLS->hh[27];
c2.v[10] += (sum_160_1_048)*MainFormSLS->hh[48];
c2.v[10] += (sum_160_1_049)*MainFormSLS->hh[69];
c2.v[10] += (sum_160_1_050)*MainFormSLS->hh[90];
c2.v[10] += (sum_160_1_051)*MainFormSLS->hh[111];
c2.v[10] += (sum_160_1_052)*MainFormSLS->hh[132];
c2.v[10] += (sum_160_1_053)*MainFormSLS->hh[153];
c2.v[10] += (sum_160_1_054)*MainFormSLS->hh[14];
c2.v[10] += (sum_160_1_055)*MainFormSLS->hh[35];
c2.v[10] += (sum_160_1_056)*MainFormSLS->hh[56];
c2.v[10] += (sum_160_1_057)*MainFormSLS->hh[77];
c2.v[10] += (sum_160_1_058)*MainFormSLS->hh[98];
c2.v[10] += (sum_160_1_059)*MainFormSLS->hh[119];
c2.v[10] += (sum_160_1_060)*MainFormSLS->hh[140];
c2.v[10] += (sum_160_1_061)*MainFormSLS->hh[1];
c2.v[10] += (sum_160_1_062)*MainFormSLS->hh[22];
c2.v[10] += (sum_160_1_063)*MainFormSLS->hh[43];
c2.v[10] += (sum_160_1_064)*MainFormSLS->hh[64];
c2.v[10] += (sum_160_1_065)*MainFormSLS->hh[85];
c2.v[10] += (sum_160_1_066)*MainFormSLS->hh[106];
c2.v[10] += (sum_160_1_067)*MainFormSLS->hh[127];
c2.v[10] += (sum_160_1_068)*MainFormSLS->hh[148];
c2.v[10] += (sum_160_1_069)*MainFormSLS->hh[9];
c2.v[10] += (sum_160_1_070)*MainFormSLS->hh[30];
c2.v[10] += (sum_160_1_071)*MainFormSLS->hh[51];
c2.v[10] += (sum_160_1_072)*MainFormSLS->hh[72];
c2.v[10] += (sum_160_1_073)*MainFormSLS->hh[93];
c2.v[10] += (sum_160_1_074)*MainFormSLS->hh[114];
c2.v[10] += (sum_160_1_075)*MainFormSLS->hh[135];
c2.v[10] += (sum_160_1_076)*MainFormSLS->hh[156];
c2.v[10] += (sum_160_1_077)*MainFormSLS->hh[17];
c2.v[10] += (sum_160_1_078)*MainFormSLS->hh[38];
c2.v[10] += (sum_160_1_079)*MainFormSLS->hh[59];
c2.v[10] += (sum_160_1_080)*MainFormSLS->hh[80];
c2.v[10] += (sum_160_1_081)*MainFormSLS->hh[101];
c2.v[10] += (sum_160_1_082)*MainFormSLS->hh[122];
c2.v[10] += (sum_160_1_083)*MainFormSLS->hh[143];
c2.v[10] += (sum_160_1_084)*MainFormSLS->hh[4];
c2.v[10] += (sum_160_1_085)*MainFormSLS->hh[25];
c2.v[10] += (sum_160_1_086)*MainFormSLS->hh[46];
c2.v[10] += (sum_160_1_087)*MainFormSLS->hh[67];
c2.v[10] += (sum_160_1_088)*MainFormSLS->hh[88];
c2.v[10] += (sum_160_1_089)*MainFormSLS->hh[109];
c2.v[10] += (sum_160_1_090)*MainFormSLS->hh[130];
c2.v[10] += (sum_160_1_091)*MainFormSLS->hh[151];
c2.v[10] += (sum_160_1_092)*MainFormSLS->hh[12];
c2.v[10] += (sum_160_1_093)*MainFormSLS->hh[33];
c2.v[10] += (sum_160_1_094)*MainFormSLS->hh[54];
c2.v[10] += (sum_160_1_095)*MainFormSLS->hh[75];
c2.v[10] += (sum_160_1_096)*MainFormSLS->hh[96];
c2.v[10] += (sum_160_1_097)*MainFormSLS->hh[117];
c2.v[10] += (sum_160_1_098)*MainFormSLS->hh[138];
c2.v[10] += (sum_160_1_099)*MainFormSLS->hh[159];
c2.v[10] += (sum_160_1_100)*MainFormSLS->hh[20];
c2.v[10] += (sum_160_1_101)*MainFormSLS->hh[41];
c2.v[10] += (sum_160_1_102)*MainFormSLS->hh[62];
c2.v[10] += (sum_160_1_103)*MainFormSLS->hh[83];
c2.v[10] += (sum_160_1_104)*MainFormSLS->hh[104];
c2.v[10] += (sum_160_1_105)*MainFormSLS->hh[125];
c2.v[10] += (sum_160_1_106)*MainFormSLS->hh[146];
c2.v[10] += (sum_160_1_107)*MainFormSLS->hh[7];
c2.v[10] += (sum_160_1_108)*MainFormSLS->hh[28];
c2.v[10] += (sum_160_1_109)*MainFormSLS->hh[49];
c2.v[10] += (sum_160_1_110)*MainFormSLS->hh[70];
c2.v[10] += (sum_160_1_111)*MainFormSLS->hh[91];
c2.v[10] += (sum_160_1_112)*MainFormSLS->hh[112];
c2.v[10] += (sum_160_1_113)*MainFormSLS->hh[133];
c2.v[10] += (sum_160_1_114)*MainFormSLS->hh[154];
c2.v[10] += (sum_160_1_115)*MainFormSLS->hh[15];
c2.v[10] += (sum_160_1_116)*MainFormSLS->hh[36];
c2.v[10] += (sum_160_1_117)*MainFormSLS->hh[57];
c2.v[10] += (sum_160_1_118)*MainFormSLS->hh[78];
c2.v[10] += (sum_160_1_119)*MainFormSLS->hh[99];
c2.v[10] += (sum_160_1_120)*MainFormSLS->hh[120];
c2.v[10] += (sum_160_1_121)*MainFormSLS->hh[141];
c2.v[10] += (sum_160_1_122)*MainFormSLS->hh[2];
c2.v[10] += (sum_160_1_123)*MainFormSLS->hh[23];
c2.v[10] += (sum_160_1_124)*MainFormSLS->hh[44];
c2.v[10] += (sum_160_1_125)*MainFormSLS->hh[65];
c2.v[10] += (sum_160_1_126)*MainFormSLS->hh[86];
c2.v[10] += (sum_160_1_127)*MainFormSLS->hh[107];
c2.v[10] += (sum_160_1_128)*MainFormSLS->hh[128];
c2.v[10] += (sum_160_1_129)*MainFormSLS->hh[149];
c2.v[10] += (sum_160_1_130)*MainFormSLS->hh[10];
c2.v[10] += (sum_160_1_131)*MainFormSLS->hh[31];
c2.v[10] += (sum_160_1_132)*MainFormSLS->hh[52];
c2.v[10] += (sum_160_1_133)*MainFormSLS->hh[73];
c2.v[10] += (sum_160_1_134)*MainFormSLS->hh[94];
c2.v[10] += (sum_160_1_135)*MainFormSLS->hh[115];
c2.v[10] += (sum_160_1_136)*MainFormSLS->hh[136];
c2.v[10] += (sum_160_1_137)*MainFormSLS->hh[157];
c2.v[10] += (sum_160_1_138)*MainFormSLS->hh[18];
c2.v[10] += (sum_160_1_139)*MainFormSLS->hh[39];
c2.v[10] += (sum_160_1_140)*MainFormSLS->hh[60];
c2.v[10] += (sum_160_1_141)*MainFormSLS->hh[81];
c2.v[10] += (sum_160_1_142)*MainFormSLS->hh[102];
c2.v[10] += (sum_160_1_143)*MainFormSLS->hh[123];
c2.v[10] += (sum_160_1_144)*MainFormSLS->hh[144];
c2.v[10] += (sum_160_1_145)*MainFormSLS->hh[5];
c2.v[10] += (sum_160_1_146)*MainFormSLS->hh[26];
c2.v[10] += (sum_160_1_147)*MainFormSLS->hh[47];
c2.v[10] += (sum_160_1_148)*MainFormSLS->hh[68];
c2.v[10] += (sum_160_1_149)*MainFormSLS->hh[89];
c2.v[10] += (sum_160_1_150)*MainFormSLS->hh[110];
c2.v[10] += (sum_160_1_151)*MainFormSLS->hh[131];
c2.v[10] += (sum_160_1_152)*MainFormSLS->hh[152];
c2.v[10] += (sum_160_1_153)*MainFormSLS->hh[13];
c2.v[10] += (sum_160_1_154)*MainFormSLS->hh[34];
c2.v[10] += (sum_160_1_155)*MainFormSLS->hh[55];
c2.v[10] += (sum_160_1_156)*MainFormSLS->hh[76];
c2.v[10] += (sum_160_1_157)*MainFormSLS->hh[97];
c2.v[10] += (sum_160_1_158)*MainFormSLS->hh[118];
c2.v[10] += (sum_160_1_159)*MainFormSLS->hh[139];

//frequency level id 23
c2.v[11] += (sum_160_1_000)*MainFormSLS->hh[0];
c2.v[11] += (sum_160_1_001)*MainFormSLS->hh[23];
c2.v[11] += (sum_160_1_002)*MainFormSLS->hh[46];
c2.v[11] += (sum_160_1_003)*MainFormSLS->hh[69];
c2.v[11] += (sum_160_1_004)*MainFormSLS->hh[92];
c2.v[11] += (sum_160_1_005)*MainFormSLS->hh[115];
c2.v[11] += (sum_160_1_006)*MainFormSLS->hh[138];
c2.v[11] += (sum_160_1_007)*MainFormSLS->hh[1];
c2.v[11] += (sum_160_1_008)*MainFormSLS->hh[24];
c2.v[11] += (sum_160_1_009)*MainFormSLS->hh[47];
c2.v[11] += (sum_160_1_010)*MainFormSLS->hh[70];
c2.v[11] += (sum_160_1_011)*MainFormSLS->hh[93];
c2.v[11] += (sum_160_1_012)*MainFormSLS->hh[116];
c2.v[11] += (sum_160_1_013)*MainFormSLS->hh[139];
c2.v[11] += (sum_160_1_014)*MainFormSLS->hh[2];
c2.v[11] += (sum_160_1_015)*MainFormSLS->hh[25];
c2.v[11] += (sum_160_1_016)*MainFormSLS->hh[48];
c2.v[11] += (sum_160_1_017)*MainFormSLS->hh[71];
c2.v[11] += (sum_160_1_018)*MainFormSLS->hh[94];
c2.v[11] += (sum_160_1_019)*MainFormSLS->hh[117];
c2.v[11] += (sum_160_1_020)*MainFormSLS->hh[140];
c2.v[11] += (sum_160_1_021)*MainFormSLS->hh[3];
c2.v[11] += (sum_160_1_022)*MainFormSLS->hh[26];
c2.v[11] += (sum_160_1_023)*MainFormSLS->hh[49];
c2.v[11] += (sum_160_1_024)*MainFormSLS->hh[72];
c2.v[11] += (sum_160_1_025)*MainFormSLS->hh[95];
c2.v[11] += (sum_160_1_026)*MainFormSLS->hh[118];
c2.v[11] += (sum_160_1_027)*MainFormSLS->hh[141];
c2.v[11] += (sum_160_1_028)*MainFormSLS->hh[4];
c2.v[11] += (sum_160_1_029)*MainFormSLS->hh[27];
c2.v[11] += (sum_160_1_030)*MainFormSLS->hh[50];
c2.v[11] += (sum_160_1_031)*MainFormSLS->hh[73];
c2.v[11] += (sum_160_1_032)*MainFormSLS->hh[96];
c2.v[11] += (sum_160_1_033)*MainFormSLS->hh[119];
c2.v[11] += (sum_160_1_034)*MainFormSLS->hh[142];
c2.v[11] += (sum_160_1_035)*MainFormSLS->hh[5];
c2.v[11] += (sum_160_1_036)*MainFormSLS->hh[28];
c2.v[11] += (sum_160_1_037)*MainFormSLS->hh[51];
c2.v[11] += (sum_160_1_038)*MainFormSLS->hh[74];
c2.v[11] += (sum_160_1_039)*MainFormSLS->hh[97];
c2.v[11] += (sum_160_1_040)*MainFormSLS->hh[120];
c2.v[11] += (sum_160_1_041)*MainFormSLS->hh[143];
c2.v[11] += (sum_160_1_042)*MainFormSLS->hh[6];
c2.v[11] += (sum_160_1_043)*MainFormSLS->hh[29];
c2.v[11] += (sum_160_1_044)*MainFormSLS->hh[52];
c2.v[11] += (sum_160_1_045)*MainFormSLS->hh[75];
c2.v[11] += (sum_160_1_046)*MainFormSLS->hh[98];
c2.v[11] += (sum_160_1_047)*MainFormSLS->hh[121];
c2.v[11] += (sum_160_1_048)*MainFormSLS->hh[144];
c2.v[11] += (sum_160_1_049)*MainFormSLS->hh[7];
c2.v[11] += (sum_160_1_050)*MainFormSLS->hh[30];
c2.v[11] += (sum_160_1_051)*MainFormSLS->hh[53];
c2.v[11] += (sum_160_1_052)*MainFormSLS->hh[76];
c2.v[11] += (sum_160_1_053)*MainFormSLS->hh[99];
c2.v[11] += (sum_160_1_054)*MainFormSLS->hh[122];
c2.v[11] += (sum_160_1_055)*MainFormSLS->hh[145];
c2.v[11] += (sum_160_1_056)*MainFormSLS->hh[8];
c2.v[11] += (sum_160_1_057)*MainFormSLS->hh[31];
c2.v[11] += (sum_160_1_058)*MainFormSLS->hh[54];
c2.v[11] += (sum_160_1_059)*MainFormSLS->hh[77];
c2.v[11] += (sum_160_1_060)*MainFormSLS->hh[100];
c2.v[11] += (sum_160_1_061)*MainFormSLS->hh[123];
c2.v[11] += (sum_160_1_062)*MainFormSLS->hh[146];
c2.v[11] += (sum_160_1_063)*MainFormSLS->hh[9];
c2.v[11] += (sum_160_1_064)*MainFormSLS->hh[32];
c2.v[11] += (sum_160_1_065)*MainFormSLS->hh[55];
c2.v[11] += (sum_160_1_066)*MainFormSLS->hh[78];
c2.v[11] += (sum_160_1_067)*MainFormSLS->hh[101];
c2.v[11] += (sum_160_1_068)*MainFormSLS->hh[124];
c2.v[11] += (sum_160_1_069)*MainFormSLS->hh[147];
c2.v[11] += (sum_160_1_070)*MainFormSLS->hh[10];
c2.v[11] += (sum_160_1_071)*MainFormSLS->hh[33];
c2.v[11] += (sum_160_1_072)*MainFormSLS->hh[56];
c2.v[11] += (sum_160_1_073)*MainFormSLS->hh[79];
c2.v[11] += (sum_160_1_074)*MainFormSLS->hh[102];
c2.v[11] += (sum_160_1_075)*MainFormSLS->hh[125];
c2.v[11] += (sum_160_1_076)*MainFormSLS->hh[148];
c2.v[11] += (sum_160_1_077)*MainFormSLS->hh[11];
c2.v[11] += (sum_160_1_078)*MainFormSLS->hh[34];
c2.v[11] += (sum_160_1_079)*MainFormSLS->hh[57];
c2.v[11] += (sum_160_1_080)*MainFormSLS->hh[80];
c2.v[11] += (sum_160_1_081)*MainFormSLS->hh[103];
c2.v[11] += (sum_160_1_082)*MainFormSLS->hh[126];
c2.v[11] += (sum_160_1_083)*MainFormSLS->hh[149];
c2.v[11] += (sum_160_1_084)*MainFormSLS->hh[12];
c2.v[11] += (sum_160_1_085)*MainFormSLS->hh[35];
c2.v[11] += (sum_160_1_086)*MainFormSLS->hh[58];
c2.v[11] += (sum_160_1_087)*MainFormSLS->hh[81];
c2.v[11] += (sum_160_1_088)*MainFormSLS->hh[104];
c2.v[11] += (sum_160_1_089)*MainFormSLS->hh[127];
c2.v[11] += (sum_160_1_090)*MainFormSLS->hh[150];
c2.v[11] += (sum_160_1_091)*MainFormSLS->hh[13];
c2.v[11] += (sum_160_1_092)*MainFormSLS->hh[36];
c2.v[11] += (sum_160_1_093)*MainFormSLS->hh[59];
c2.v[11] += (sum_160_1_094)*MainFormSLS->hh[82];
c2.v[11] += (sum_160_1_095)*MainFormSLS->hh[105];
c2.v[11] += (sum_160_1_096)*MainFormSLS->hh[128];
c2.v[11] += (sum_160_1_097)*MainFormSLS->hh[151];
c2.v[11] += (sum_160_1_098)*MainFormSLS->hh[14];
c2.v[11] += (sum_160_1_099)*MainFormSLS->hh[37];
c2.v[11] += (sum_160_1_100)*MainFormSLS->hh[60];
c2.v[11] += (sum_160_1_101)*MainFormSLS->hh[83];
c2.v[11] += (sum_160_1_102)*MainFormSLS->hh[106];
c2.v[11] += (sum_160_1_103)*MainFormSLS->hh[129];
c2.v[11] += (sum_160_1_104)*MainFormSLS->hh[152];
c2.v[11] += (sum_160_1_105)*MainFormSLS->hh[15];
c2.v[11] += (sum_160_1_106)*MainFormSLS->hh[38];
c2.v[11] += (sum_160_1_107)*MainFormSLS->hh[61];
c2.v[11] += (sum_160_1_108)*MainFormSLS->hh[84];
c2.v[11] += (sum_160_1_109)*MainFormSLS->hh[107];
c2.v[11] += (sum_160_1_110)*MainFormSLS->hh[130];
c2.v[11] += (sum_160_1_111)*MainFormSLS->hh[153];
c2.v[11] += (sum_160_1_112)*MainFormSLS->hh[16];
c2.v[11] += (sum_160_1_113)*MainFormSLS->hh[39];
c2.v[11] += (sum_160_1_114)*MainFormSLS->hh[62];
c2.v[11] += (sum_160_1_115)*MainFormSLS->hh[85];
c2.v[11] += (sum_160_1_116)*MainFormSLS->hh[108];
c2.v[11] += (sum_160_1_117)*MainFormSLS->hh[131];
c2.v[11] += (sum_160_1_118)*MainFormSLS->hh[154];
c2.v[11] += (sum_160_1_119)*MainFormSLS->hh[17];
c2.v[11] += (sum_160_1_120)*MainFormSLS->hh[40];
c2.v[11] += (sum_160_1_121)*MainFormSLS->hh[63];
c2.v[11] += (sum_160_1_122)*MainFormSLS->hh[86];
c2.v[11] += (sum_160_1_123)*MainFormSLS->hh[109];
c2.v[11] += (sum_160_1_124)*MainFormSLS->hh[132];
c2.v[11] += (sum_160_1_125)*MainFormSLS->hh[155];
c2.v[11] += (sum_160_1_126)*MainFormSLS->hh[18];
c2.v[11] += (sum_160_1_127)*MainFormSLS->hh[41];
c2.v[11] += (sum_160_1_128)*MainFormSLS->hh[64];
c2.v[11] += (sum_160_1_129)*MainFormSLS->hh[87];
c2.v[11] += (sum_160_1_130)*MainFormSLS->hh[110];
c2.v[11] += (sum_160_1_131)*MainFormSLS->hh[133];
c2.v[11] += (sum_160_1_132)*MainFormSLS->hh[156];
c2.v[11] += (sum_160_1_133)*MainFormSLS->hh[19];
c2.v[11] += (sum_160_1_134)*MainFormSLS->hh[42];
c2.v[11] += (sum_160_1_135)*MainFormSLS->hh[65];
c2.v[11] += (sum_160_1_136)*MainFormSLS->hh[88];
c2.v[11] += (sum_160_1_137)*MainFormSLS->hh[111];
c2.v[11] += (sum_160_1_138)*MainFormSLS->hh[134];
c2.v[11] += (sum_160_1_139)*MainFormSLS->hh[157];
c2.v[11] += (sum_160_1_140)*MainFormSLS->hh[20];
c2.v[11] += (sum_160_1_141)*MainFormSLS->hh[43];
c2.v[11] += (sum_160_1_142)*MainFormSLS->hh[66];
c2.v[11] += (sum_160_1_143)*MainFormSLS->hh[89];
c2.v[11] += (sum_160_1_144)*MainFormSLS->hh[112];
c2.v[11] += (sum_160_1_145)*MainFormSLS->hh[135];
c2.v[11] += (sum_160_1_146)*MainFormSLS->hh[158];
c2.v[11] += (sum_160_1_147)*MainFormSLS->hh[21];
c2.v[11] += (sum_160_1_148)*MainFormSLS->hh[44];
c2.v[11] += (sum_160_1_149)*MainFormSLS->hh[67];
c2.v[11] += (sum_160_1_150)*MainFormSLS->hh[90];
c2.v[11] += (sum_160_1_151)*MainFormSLS->hh[113];
c2.v[11] += (sum_160_1_152)*MainFormSLS->hh[136];
c2.v[11] += (sum_160_1_153)*MainFormSLS->hh[159];
c2.v[11] += (sum_160_1_154)*MainFormSLS->hh[22];
c2.v[11] += (sum_160_1_155)*MainFormSLS->hh[45];
c2.v[11] += (sum_160_1_156)*MainFormSLS->hh[68];
c2.v[11] += (sum_160_1_157)*MainFormSLS->hh[91];
c2.v[11] += (sum_160_1_158)*MainFormSLS->hh[114];
c2.v[11] += (sum_160_1_159)*MainFormSLS->hh[137];

//frequency level id 25
c2.v[12] += (sum_32_5_000)*MainFormSLS->hh[0];
c2.v[12] += (sum_32_5_001)*MainFormSLS->hh[25];
c2.v[12] += (sum_32_5_002)*MainFormSLS->hh[50];
c2.v[12] += (sum_32_5_003)*MainFormSLS->hh[75];
c2.v[12] += (sum_32_5_004)*MainFormSLS->hh[100];
c2.v[12] += (sum_32_5_005)*MainFormSLS->hh[125];
c2.v[12] += (sum_32_5_006)*MainFormSLS->hh[150];
c2.v[12] += (sum_32_5_007)*MainFormSLS->hh[15];
c2.v[12] += (sum_32_5_008)*MainFormSLS->hh[40];
c2.v[12] += (sum_32_5_009)*MainFormSLS->hh[65];
c2.v[12] += (sum_32_5_010)*MainFormSLS->hh[90];
c2.v[12] += (sum_32_5_011)*MainFormSLS->hh[115];
c2.v[12] += (sum_32_5_012)*MainFormSLS->hh[140];
c2.v[12] += (sum_32_5_013)*MainFormSLS->hh[5];
c2.v[12] += (sum_32_5_014)*MainFormSLS->hh[30];
c2.v[12] += (sum_32_5_015)*MainFormSLS->hh[55];
c2.v[12] += (sum_32_5_016)*MainFormSLS->hh[80];
c2.v[12] += (sum_32_5_017)*MainFormSLS->hh[105];
c2.v[12] += (sum_32_5_018)*MainFormSLS->hh[130];
c2.v[12] += (sum_32_5_019)*MainFormSLS->hh[155];
c2.v[12] += (sum_32_5_020)*MainFormSLS->hh[20];
c2.v[12] += (sum_32_5_021)*MainFormSLS->hh[45];
c2.v[12] += (sum_32_5_022)*MainFormSLS->hh[70];
c2.v[12] += (sum_32_5_023)*MainFormSLS->hh[95];
c2.v[12] += (sum_32_5_024)*MainFormSLS->hh[120];
c2.v[12] += (sum_32_5_025)*MainFormSLS->hh[145];
c2.v[12] += (sum_32_5_026)*MainFormSLS->hh[10];
c2.v[12] += (sum_32_5_027)*MainFormSLS->hh[35];
c2.v[12] += (sum_32_5_028)*MainFormSLS->hh[60];
c2.v[12] += (sum_32_5_029)*MainFormSLS->hh[85];
c2.v[12] += (sum_32_5_030)*MainFormSLS->hh[110];
c2.v[12] += (sum_32_5_031)*MainFormSLS->hh[135];

//frequency level id 27
c2.v[13] += (sum_160_1_000)*MainFormSLS->hh[0];
c2.v[13] += (sum_160_1_001)*MainFormSLS->hh[27];
c2.v[13] += (sum_160_1_002)*MainFormSLS->hh[54];
c2.v[13] += (sum_160_1_003)*MainFormSLS->hh[81];
c2.v[13] += (sum_160_1_004)*MainFormSLS->hh[108];
c2.v[13] += (sum_160_1_005)*MainFormSLS->hh[135];
c2.v[13] += (sum_160_1_006)*MainFormSLS->hh[2];
c2.v[13] += (sum_160_1_007)*MainFormSLS->hh[29];
c2.v[13] += (sum_160_1_008)*MainFormSLS->hh[56];
c2.v[13] += (sum_160_1_009)*MainFormSLS->hh[83];
c2.v[13] += (sum_160_1_010)*MainFormSLS->hh[110];
c2.v[13] += (sum_160_1_011)*MainFormSLS->hh[137];
c2.v[13] += (sum_160_1_012)*MainFormSLS->hh[4];
c2.v[13] += (sum_160_1_013)*MainFormSLS->hh[31];
c2.v[13] += (sum_160_1_014)*MainFormSLS->hh[58];
c2.v[13] += (sum_160_1_015)*MainFormSLS->hh[85];
c2.v[13] += (sum_160_1_016)*MainFormSLS->hh[112];
c2.v[13] += (sum_160_1_017)*MainFormSLS->hh[139];
c2.v[13] += (sum_160_1_018)*MainFormSLS->hh[6];
c2.v[13] += (sum_160_1_019)*MainFormSLS->hh[33];
c2.v[13] += (sum_160_1_020)*MainFormSLS->hh[60];
c2.v[13] += (sum_160_1_021)*MainFormSLS->hh[87];
c2.v[13] += (sum_160_1_022)*MainFormSLS->hh[114];
c2.v[13] += (sum_160_1_023)*MainFormSLS->hh[141];
c2.v[13] += (sum_160_1_024)*MainFormSLS->hh[8];
c2.v[13] += (sum_160_1_025)*MainFormSLS->hh[35];
c2.v[13] += (sum_160_1_026)*MainFormSLS->hh[62];
c2.v[13] += (sum_160_1_027)*MainFormSLS->hh[89];
c2.v[13] += (sum_160_1_028)*MainFormSLS->hh[116];
c2.v[13] += (sum_160_1_029)*MainFormSLS->hh[143];
c2.v[13] += (sum_160_1_030)*MainFormSLS->hh[10];
c2.v[13] += (sum_160_1_031)*MainFormSLS->hh[37];
c2.v[13] += (sum_160_1_032)*MainFormSLS->hh[64];
c2.v[13] += (sum_160_1_033)*MainFormSLS->hh[91];
c2.v[13] += (sum_160_1_034)*MainFormSLS->hh[118];
c2.v[13] += (sum_160_1_035)*MainFormSLS->hh[145];
c2.v[13] += (sum_160_1_036)*MainFormSLS->hh[12];
c2.v[13] += (sum_160_1_037)*MainFormSLS->hh[39];
c2.v[13] += (sum_160_1_038)*MainFormSLS->hh[66];
c2.v[13] += (sum_160_1_039)*MainFormSLS->hh[93];
c2.v[13] += (sum_160_1_040)*MainFormSLS->hh[120];
c2.v[13] += (sum_160_1_041)*MainFormSLS->hh[147];
c2.v[13] += (sum_160_1_042)*MainFormSLS->hh[14];
c2.v[13] += (sum_160_1_043)*MainFormSLS->hh[41];
c2.v[13] += (sum_160_1_044)*MainFormSLS->hh[68];
c2.v[13] += (sum_160_1_045)*MainFormSLS->hh[95];
c2.v[13] += (sum_160_1_046)*MainFormSLS->hh[122];
c2.v[13] += (sum_160_1_047)*MainFormSLS->hh[149];
c2.v[13] += (sum_160_1_048)*MainFormSLS->hh[16];
c2.v[13] += (sum_160_1_049)*MainFormSLS->hh[43];
c2.v[13] += (sum_160_1_050)*MainFormSLS->hh[70];
c2.v[13] += (sum_160_1_051)*MainFormSLS->hh[97];
c2.v[13] += (sum_160_1_052)*MainFormSLS->hh[124];
c2.v[13] += (sum_160_1_053)*MainFormSLS->hh[151];
c2.v[13] += (sum_160_1_054)*MainFormSLS->hh[18];
c2.v[13] += (sum_160_1_055)*MainFormSLS->hh[45];
c2.v[13] += (sum_160_1_056)*MainFormSLS->hh[72];
c2.v[13] += (sum_160_1_057)*MainFormSLS->hh[99];
c2.v[13] += (sum_160_1_058)*MainFormSLS->hh[126];
c2.v[13] += (sum_160_1_059)*MainFormSLS->hh[153];
c2.v[13] += (sum_160_1_060)*MainFormSLS->hh[20];
c2.v[13] += (sum_160_1_061)*MainFormSLS->hh[47];
c2.v[13] += (sum_160_1_062)*MainFormSLS->hh[74];
c2.v[13] += (sum_160_1_063)*MainFormSLS->hh[101];
c2.v[13] += (sum_160_1_064)*MainFormSLS->hh[128];
c2.v[13] += (sum_160_1_065)*MainFormSLS->hh[155];
c2.v[13] += (sum_160_1_066)*MainFormSLS->hh[22];
c2.v[13] += (sum_160_1_067)*MainFormSLS->hh[49];
c2.v[13] += (sum_160_1_068)*MainFormSLS->hh[76];
c2.v[13] += (sum_160_1_069)*MainFormSLS->hh[103];
c2.v[13] += (sum_160_1_070)*MainFormSLS->hh[130];
c2.v[13] += (sum_160_1_071)*MainFormSLS->hh[157];
c2.v[13] += (sum_160_1_072)*MainFormSLS->hh[24];
c2.v[13] += (sum_160_1_073)*MainFormSLS->hh[51];
c2.v[13] += (sum_160_1_074)*MainFormSLS->hh[78];
c2.v[13] += (sum_160_1_075)*MainFormSLS->hh[105];
c2.v[13] += (sum_160_1_076)*MainFormSLS->hh[132];
c2.v[13] += (sum_160_1_077)*MainFormSLS->hh[159];
c2.v[13] += (sum_160_1_078)*MainFormSLS->hh[26];
c2.v[13] += (sum_160_1_079)*MainFormSLS->hh[53];
c2.v[13] += (sum_160_1_080)*MainFormSLS->hh[80];
c2.v[13] += (sum_160_1_081)*MainFormSLS->hh[107];
c2.v[13] += (sum_160_1_082)*MainFormSLS->hh[134];
c2.v[13] += (sum_160_1_083)*MainFormSLS->hh[1];
c2.v[13] += (sum_160_1_084)*MainFormSLS->hh[28];
c2.v[13] += (sum_160_1_085)*MainFormSLS->hh[55];
c2.v[13] += (sum_160_1_086)*MainFormSLS->hh[82];
c2.v[13] += (sum_160_1_087)*MainFormSLS->hh[109];
c2.v[13] += (sum_160_1_088)*MainFormSLS->hh[136];
c2.v[13] += (sum_160_1_089)*MainFormSLS->hh[3];
c2.v[13] += (sum_160_1_090)*MainFormSLS->hh[30];
c2.v[13] += (sum_160_1_091)*MainFormSLS->hh[57];
c2.v[13] += (sum_160_1_092)*MainFormSLS->hh[84];
c2.v[13] += (sum_160_1_093)*MainFormSLS->hh[111];
c2.v[13] += (sum_160_1_094)*MainFormSLS->hh[138];
c2.v[13] += (sum_160_1_095)*MainFormSLS->hh[5];
c2.v[13] += (sum_160_1_096)*MainFormSLS->hh[32];
c2.v[13] += (sum_160_1_097)*MainFormSLS->hh[59];
c2.v[13] += (sum_160_1_098)*MainFormSLS->hh[86];
c2.v[13] += (sum_160_1_099)*MainFormSLS->hh[113];
c2.v[13] += (sum_160_1_100)*MainFormSLS->hh[140];
c2.v[13] += (sum_160_1_101)*MainFormSLS->hh[7];
c2.v[13] += (sum_160_1_102)*MainFormSLS->hh[34];
c2.v[13] += (sum_160_1_103)*MainFormSLS->hh[61];
c2.v[13] += (sum_160_1_104)*MainFormSLS->hh[88];
c2.v[13] += (sum_160_1_105)*MainFormSLS->hh[115];
c2.v[13] += (sum_160_1_106)*MainFormSLS->hh[142];
c2.v[13] += (sum_160_1_107)*MainFormSLS->hh[9];
c2.v[13] += (sum_160_1_108)*MainFormSLS->hh[36];
c2.v[13] += (sum_160_1_109)*MainFormSLS->hh[63];
c2.v[13] += (sum_160_1_110)*MainFormSLS->hh[90];
c2.v[13] += (sum_160_1_111)*MainFormSLS->hh[117];
c2.v[13] += (sum_160_1_112)*MainFormSLS->hh[144];
c2.v[13] += (sum_160_1_113)*MainFormSLS->hh[11];
c2.v[13] += (sum_160_1_114)*MainFormSLS->hh[38];
c2.v[13] += (sum_160_1_115)*MainFormSLS->hh[65];
c2.v[13] += (sum_160_1_116)*MainFormSLS->hh[92];
c2.v[13] += (sum_160_1_117)*MainFormSLS->hh[119];
c2.v[13] += (sum_160_1_118)*MainFormSLS->hh[146];
c2.v[13] += (sum_160_1_119)*MainFormSLS->hh[13];
c2.v[13] += (sum_160_1_120)*MainFormSLS->hh[40];
c2.v[13] += (sum_160_1_121)*MainFormSLS->hh[67];
c2.v[13] += (sum_160_1_122)*MainFormSLS->hh[94];
c2.v[13] += (sum_160_1_123)*MainFormSLS->hh[121];
c2.v[13] += (sum_160_1_124)*MainFormSLS->hh[148];
c2.v[13] += (sum_160_1_125)*MainFormSLS->hh[15];
c2.v[13] += (sum_160_1_126)*MainFormSLS->hh[42];
c2.v[13] += (sum_160_1_127)*MainFormSLS->hh[69];
c2.v[13] += (sum_160_1_128)*MainFormSLS->hh[96];
c2.v[13] += (sum_160_1_129)*MainFormSLS->hh[123];
c2.v[13] += (sum_160_1_130)*MainFormSLS->hh[150];
c2.v[13] += (sum_160_1_131)*MainFormSLS->hh[17];
c2.v[13] += (sum_160_1_132)*MainFormSLS->hh[44];
c2.v[13] += (sum_160_1_133)*MainFormSLS->hh[71];
c2.v[13] += (sum_160_1_134)*MainFormSLS->hh[98];
c2.v[13] += (sum_160_1_135)*MainFormSLS->hh[125];
c2.v[13] += (sum_160_1_136)*MainFormSLS->hh[152];
c2.v[13] += (sum_160_1_137)*MainFormSLS->hh[19];
c2.v[13] += (sum_160_1_138)*MainFormSLS->hh[46];
c2.v[13] += (sum_160_1_139)*MainFormSLS->hh[73];
c2.v[13] += (sum_160_1_140)*MainFormSLS->hh[100];
c2.v[13] += (sum_160_1_141)*MainFormSLS->hh[127];
c2.v[13] += (sum_160_1_142)*MainFormSLS->hh[154];
c2.v[13] += (sum_160_1_143)*MainFormSLS->hh[21];
c2.v[13] += (sum_160_1_144)*MainFormSLS->hh[48];
c2.v[13] += (sum_160_1_145)*MainFormSLS->hh[75];
c2.v[13] += (sum_160_1_146)*MainFormSLS->hh[102];
c2.v[13] += (sum_160_1_147)*MainFormSLS->hh[129];
c2.v[13] += (sum_160_1_148)*MainFormSLS->hh[156];
c2.v[13] += (sum_160_1_149)*MainFormSLS->hh[23];
c2.v[13] += (sum_160_1_150)*MainFormSLS->hh[50];
c2.v[13] += (sum_160_1_151)*MainFormSLS->hh[77];
c2.v[13] += (sum_160_1_152)*MainFormSLS->hh[104];
c2.v[13] += (sum_160_1_153)*MainFormSLS->hh[131];
c2.v[13] += (sum_160_1_154)*MainFormSLS->hh[158];
c2.v[13] += (sum_160_1_155)*MainFormSLS->hh[25];
c2.v[13] += (sum_160_1_156)*MainFormSLS->hh[52];
c2.v[13] += (sum_160_1_157)*MainFormSLS->hh[79];
c2.v[13] += (sum_160_1_158)*MainFormSLS->hh[106];
c2.v[13] += (sum_160_1_159)*MainFormSLS->hh[133];

//frequency level id 29
c2.v[14] += (sum_160_1_000)*MainFormSLS->hh[0];
c2.v[14] += (sum_160_1_001)*MainFormSLS->hh[29];
c2.v[14] += (sum_160_1_002)*MainFormSLS->hh[58];
c2.v[14] += (sum_160_1_003)*MainFormSLS->hh[87];
c2.v[14] += (sum_160_1_004)*MainFormSLS->hh[116];
c2.v[14] += (sum_160_1_005)*MainFormSLS->hh[145];
c2.v[14] += (sum_160_1_006)*MainFormSLS->hh[14];
c2.v[14] += (sum_160_1_007)*MainFormSLS->hh[43];
c2.v[14] += (sum_160_1_008)*MainFormSLS->hh[72];
c2.v[14] += (sum_160_1_009)*MainFormSLS->hh[101];
c2.v[14] += (sum_160_1_010)*MainFormSLS->hh[130];
c2.v[14] += (sum_160_1_011)*MainFormSLS->hh[159];
c2.v[14] += (sum_160_1_012)*MainFormSLS->hh[28];
c2.v[14] += (sum_160_1_013)*MainFormSLS->hh[57];
c2.v[14] += (sum_160_1_014)*MainFormSLS->hh[86];
c2.v[14] += (sum_160_1_015)*MainFormSLS->hh[115];
c2.v[14] += (sum_160_1_016)*MainFormSLS->hh[144];
c2.v[14] += (sum_160_1_017)*MainFormSLS->hh[13];
c2.v[14] += (sum_160_1_018)*MainFormSLS->hh[42];
c2.v[14] += (sum_160_1_019)*MainFormSLS->hh[71];
c2.v[14] += (sum_160_1_020)*MainFormSLS->hh[100];
c2.v[14] += (sum_160_1_021)*MainFormSLS->hh[129];
c2.v[14] += (sum_160_1_022)*MainFormSLS->hh[158];
c2.v[14] += (sum_160_1_023)*MainFormSLS->hh[27];
c2.v[14] += (sum_160_1_024)*MainFormSLS->hh[56];
c2.v[14] += (sum_160_1_025)*MainFormSLS->hh[85];
c2.v[14] += (sum_160_1_026)*MainFormSLS->hh[114];
c2.v[14] += (sum_160_1_027)*MainFormSLS->hh[143];
c2.v[14] += (sum_160_1_028)*MainFormSLS->hh[12];
c2.v[14] += (sum_160_1_029)*MainFormSLS->hh[41];
c2.v[14] += (sum_160_1_030)*MainFormSLS->hh[70];
c2.v[14] += (sum_160_1_031)*MainFormSLS->hh[99];
c2.v[14] += (sum_160_1_032)*MainFormSLS->hh[128];
c2.v[14] += (sum_160_1_033)*MainFormSLS->hh[157];
c2.v[14] += (sum_160_1_034)*MainFormSLS->hh[26];
c2.v[14] += (sum_160_1_035)*MainFormSLS->hh[55];
c2.v[14] += (sum_160_1_036)*MainFormSLS->hh[84];
c2.v[14] += (sum_160_1_037)*MainFormSLS->hh[113];
c2.v[14] += (sum_160_1_038)*MainFormSLS->hh[142];
c2.v[14] += (sum_160_1_039)*MainFormSLS->hh[11];
c2.v[14] += (sum_160_1_040)*MainFormSLS->hh[40];
c2.v[14] += (sum_160_1_041)*MainFormSLS->hh[69];
c2.v[14] += (sum_160_1_042)*MainFormSLS->hh[98];
c2.v[14] += (sum_160_1_043)*MainFormSLS->hh[127];
c2.v[14] += (sum_160_1_044)*MainFormSLS->hh[156];
c2.v[14] += (sum_160_1_045)*MainFormSLS->hh[25];
c2.v[14] += (sum_160_1_046)*MainFormSLS->hh[54];
c2.v[14] += (sum_160_1_047)*MainFormSLS->hh[83];
c2.v[14] += (sum_160_1_048)*MainFormSLS->hh[112];
c2.v[14] += (sum_160_1_049)*MainFormSLS->hh[141];
c2.v[14] += (sum_160_1_050)*MainFormSLS->hh[10];
c2.v[14] += (sum_160_1_051)*MainFormSLS->hh[39];
c2.v[14] += (sum_160_1_052)*MainFormSLS->hh[68];
c2.v[14] += (sum_160_1_053)*MainFormSLS->hh[97];
c2.v[14] += (sum_160_1_054)*MainFormSLS->hh[126];
c2.v[14] += (sum_160_1_055)*MainFormSLS->hh[155];
c2.v[14] += (sum_160_1_056)*MainFormSLS->hh[24];
c2.v[14] += (sum_160_1_057)*MainFormSLS->hh[53];
c2.v[14] += (sum_160_1_058)*MainFormSLS->hh[82];
c2.v[14] += (sum_160_1_059)*MainFormSLS->hh[111];
c2.v[14] += (sum_160_1_060)*MainFormSLS->hh[140];
c2.v[14] += (sum_160_1_061)*MainFormSLS->hh[9];
c2.v[14] += (sum_160_1_062)*MainFormSLS->hh[38];
c2.v[14] += (sum_160_1_063)*MainFormSLS->hh[67];
c2.v[14] += (sum_160_1_064)*MainFormSLS->hh[96];
c2.v[14] += (sum_160_1_065)*MainFormSLS->hh[125];
c2.v[14] += (sum_160_1_066)*MainFormSLS->hh[154];
c2.v[14] += (sum_160_1_067)*MainFormSLS->hh[23];
c2.v[14] += (sum_160_1_068)*MainFormSLS->hh[52];
c2.v[14] += (sum_160_1_069)*MainFormSLS->hh[81];
c2.v[14] += (sum_160_1_070)*MainFormSLS->hh[110];
c2.v[14] += (sum_160_1_071)*MainFormSLS->hh[139];
c2.v[14] += (sum_160_1_072)*MainFormSLS->hh[8];
c2.v[14] += (sum_160_1_073)*MainFormSLS->hh[37];
c2.v[14] += (sum_160_1_074)*MainFormSLS->hh[66];
c2.v[14] += (sum_160_1_075)*MainFormSLS->hh[95];
c2.v[14] += (sum_160_1_076)*MainFormSLS->hh[124];
c2.v[14] += (sum_160_1_077)*MainFormSLS->hh[153];
c2.v[14] += (sum_160_1_078)*MainFormSLS->hh[22];
c2.v[14] += (sum_160_1_079)*MainFormSLS->hh[51];
c2.v[14] += (sum_160_1_080)*MainFormSLS->hh[80];
c2.v[14] += (sum_160_1_081)*MainFormSLS->hh[109];
c2.v[14] += (sum_160_1_082)*MainFormSLS->hh[138];
c2.v[14] += (sum_160_1_083)*MainFormSLS->hh[7];
c2.v[14] += (sum_160_1_084)*MainFormSLS->hh[36];
c2.v[14] += (sum_160_1_085)*MainFormSLS->hh[65];
c2.v[14] += (sum_160_1_086)*MainFormSLS->hh[94];
c2.v[14] += (sum_160_1_087)*MainFormSLS->hh[123];
c2.v[14] += (sum_160_1_088)*MainFormSLS->hh[152];
c2.v[14] += (sum_160_1_089)*MainFormSLS->hh[21];
c2.v[14] += (sum_160_1_090)*MainFormSLS->hh[50];
c2.v[14] += (sum_160_1_091)*MainFormSLS->hh[79];
c2.v[14] += (sum_160_1_092)*MainFormSLS->hh[108];
c2.v[14] += (sum_160_1_093)*MainFormSLS->hh[137];
c2.v[14] += (sum_160_1_094)*MainFormSLS->hh[6];
c2.v[14] += (sum_160_1_095)*MainFormSLS->hh[35];
c2.v[14] += (sum_160_1_096)*MainFormSLS->hh[64];
c2.v[14] += (sum_160_1_097)*MainFormSLS->hh[93];
c2.v[14] += (sum_160_1_098)*MainFormSLS->hh[122];
c2.v[14] += (sum_160_1_099)*MainFormSLS->hh[151];
c2.v[14] += (sum_160_1_100)*MainFormSLS->hh[20];
c2.v[14] += (sum_160_1_101)*MainFormSLS->hh[49];
c2.v[14] += (sum_160_1_102)*MainFormSLS->hh[78];
c2.v[14] += (sum_160_1_103)*MainFormSLS->hh[107];
c2.v[14] += (sum_160_1_104)*MainFormSLS->hh[136];
c2.v[14] += (sum_160_1_105)*MainFormSLS->hh[5];
c2.v[14] += (sum_160_1_106)*MainFormSLS->hh[34];
c2.v[14] += (sum_160_1_107)*MainFormSLS->hh[63];
c2.v[14] += (sum_160_1_108)*MainFormSLS->hh[92];
c2.v[14] += (sum_160_1_109)*MainFormSLS->hh[121];
c2.v[14] += (sum_160_1_110)*MainFormSLS->hh[150];
c2.v[14] += (sum_160_1_111)*MainFormSLS->hh[19];
c2.v[14] += (sum_160_1_112)*MainFormSLS->hh[48];
c2.v[14] += (sum_160_1_113)*MainFormSLS->hh[77];
c2.v[14] += (sum_160_1_114)*MainFormSLS->hh[106];
c2.v[14] += (sum_160_1_115)*MainFormSLS->hh[135];
c2.v[14] += (sum_160_1_116)*MainFormSLS->hh[4];
c2.v[14] += (sum_160_1_117)*MainFormSLS->hh[33];
c2.v[14] += (sum_160_1_118)*MainFormSLS->hh[62];
c2.v[14] += (sum_160_1_119)*MainFormSLS->hh[91];
c2.v[14] += (sum_160_1_120)*MainFormSLS->hh[120];
c2.v[14] += (sum_160_1_121)*MainFormSLS->hh[149];
c2.v[14] += (sum_160_1_122)*MainFormSLS->hh[18];
c2.v[14] += (sum_160_1_123)*MainFormSLS->hh[47];
c2.v[14] += (sum_160_1_124)*MainFormSLS->hh[76];
c2.v[14] += (sum_160_1_125)*MainFormSLS->hh[105];
c2.v[14] += (sum_160_1_126)*MainFormSLS->hh[134];
c2.v[14] += (sum_160_1_127)*MainFormSLS->hh[3];
c2.v[14] += (sum_160_1_128)*MainFormSLS->hh[32];
c2.v[14] += (sum_160_1_129)*MainFormSLS->hh[61];
c2.v[14] += (sum_160_1_130)*MainFormSLS->hh[90];
c2.v[14] += (sum_160_1_131)*MainFormSLS->hh[119];
c2.v[14] += (sum_160_1_132)*MainFormSLS->hh[148];
c2.v[14] += (sum_160_1_133)*MainFormSLS->hh[17];
c2.v[14] += (sum_160_1_134)*MainFormSLS->hh[46];
c2.v[14] += (sum_160_1_135)*MainFormSLS->hh[75];
c2.v[14] += (sum_160_1_136)*MainFormSLS->hh[104];
c2.v[14] += (sum_160_1_137)*MainFormSLS->hh[133];
c2.v[14] += (sum_160_1_138)*MainFormSLS->hh[2];
c2.v[14] += (sum_160_1_139)*MainFormSLS->hh[31];
c2.v[14] += (sum_160_1_140)*MainFormSLS->hh[60];
c2.v[14] += (sum_160_1_141)*MainFormSLS->hh[89];
c2.v[14] += (sum_160_1_142)*MainFormSLS->hh[118];
c2.v[14] += (sum_160_1_143)*MainFormSLS->hh[147];
c2.v[14] += (sum_160_1_144)*MainFormSLS->hh[16];
c2.v[14] += (sum_160_1_145)*MainFormSLS->hh[45];
c2.v[14] += (sum_160_1_146)*MainFormSLS->hh[74];
c2.v[14] += (sum_160_1_147)*MainFormSLS->hh[103];
c2.v[14] += (sum_160_1_148)*MainFormSLS->hh[132];
c2.v[14] += (sum_160_1_149)*MainFormSLS->hh[1];
c2.v[14] += (sum_160_1_150)*MainFormSLS->hh[30];
c2.v[14] += (sum_160_1_151)*MainFormSLS->hh[59];
c2.v[14] += (sum_160_1_152)*MainFormSLS->hh[88];
c2.v[14] += (sum_160_1_153)*MainFormSLS->hh[117];
c2.v[14] += (sum_160_1_154)*MainFormSLS->hh[146];
c2.v[14] += (sum_160_1_155)*MainFormSLS->hh[15];
c2.v[14] += (sum_160_1_156)*MainFormSLS->hh[44];
c2.v[14] += (sum_160_1_157)*MainFormSLS->hh[73];
c2.v[14] += (sum_160_1_158)*MainFormSLS->hh[102];
c2.v[14] += (sum_160_1_159)*MainFormSLS->hh[131];

//frequency level id 31
c2.v[15] += (sum_160_1_000)*MainFormSLS->hh[0];
c2.v[15] += (sum_160_1_001)*MainFormSLS->hh[31];
c2.v[15] += (sum_160_1_002)*MainFormSLS->hh[62];
c2.v[15] += (sum_160_1_003)*MainFormSLS->hh[93];
c2.v[15] += (sum_160_1_004)*MainFormSLS->hh[124];
c2.v[15] += (sum_160_1_005)*MainFormSLS->hh[155];
c2.v[15] += (sum_160_1_006)*MainFormSLS->hh[26];
c2.v[15] += (sum_160_1_007)*MainFormSLS->hh[57];
c2.v[15] += (sum_160_1_008)*MainFormSLS->hh[88];
c2.v[15] += (sum_160_1_009)*MainFormSLS->hh[119];
c2.v[15] += (sum_160_1_010)*MainFormSLS->hh[150];
c2.v[15] += (sum_160_1_011)*MainFormSLS->hh[21];
c2.v[15] += (sum_160_1_012)*MainFormSLS->hh[52];
c2.v[15] += (sum_160_1_013)*MainFormSLS->hh[83];
c2.v[15] += (sum_160_1_014)*MainFormSLS->hh[114];
c2.v[15] += (sum_160_1_015)*MainFormSLS->hh[145];
c2.v[15] += (sum_160_1_016)*MainFormSLS->hh[16];
c2.v[15] += (sum_160_1_017)*MainFormSLS->hh[47];
c2.v[15] += (sum_160_1_018)*MainFormSLS->hh[78];
c2.v[15] += (sum_160_1_019)*MainFormSLS->hh[109];
c2.v[15] += (sum_160_1_020)*MainFormSLS->hh[140];
c2.v[15] += (sum_160_1_021)*MainFormSLS->hh[11];
c2.v[15] += (sum_160_1_022)*MainFormSLS->hh[42];
c2.v[15] += (sum_160_1_023)*MainFormSLS->hh[73];
c2.v[15] += (sum_160_1_024)*MainFormSLS->hh[104];
c2.v[15] += (sum_160_1_025)*MainFormSLS->hh[135];
c2.v[15] += (sum_160_1_026)*MainFormSLS->hh[6];
c2.v[15] += (sum_160_1_027)*MainFormSLS->hh[37];
c2.v[15] += (sum_160_1_028)*MainFormSLS->hh[68];
c2.v[15] += (sum_160_1_029)*MainFormSLS->hh[99];
c2.v[15] += (sum_160_1_030)*MainFormSLS->hh[130];
c2.v[15] += (sum_160_1_031)*MainFormSLS->hh[1];
c2.v[15] += (sum_160_1_032)*MainFormSLS->hh[32];
c2.v[15] += (sum_160_1_033)*MainFormSLS->hh[63];
c2.v[15] += (sum_160_1_034)*MainFormSLS->hh[94];
c2.v[15] += (sum_160_1_035)*MainFormSLS->hh[125];
c2.v[15] += (sum_160_1_036)*MainFormSLS->hh[156];
c2.v[15] += (sum_160_1_037)*MainFormSLS->hh[27];
c2.v[15] += (sum_160_1_038)*MainFormSLS->hh[58];
c2.v[15] += (sum_160_1_039)*MainFormSLS->hh[89];
c2.v[15] += (sum_160_1_040)*MainFormSLS->hh[120];
c2.v[15] += (sum_160_1_041)*MainFormSLS->hh[151];
c2.v[15] += (sum_160_1_042)*MainFormSLS->hh[22];
c2.v[15] += (sum_160_1_043)*MainFormSLS->hh[53];
c2.v[15] += (sum_160_1_044)*MainFormSLS->hh[84];
c2.v[15] += (sum_160_1_045)*MainFormSLS->hh[115];
c2.v[15] += (sum_160_1_046)*MainFormSLS->hh[146];
c2.v[15] += (sum_160_1_047)*MainFormSLS->hh[17];
c2.v[15] += (sum_160_1_048)*MainFormSLS->hh[48];
c2.v[15] += (sum_160_1_049)*MainFormSLS->hh[79];
c2.v[15] += (sum_160_1_050)*MainFormSLS->hh[110];
c2.v[15] += (sum_160_1_051)*MainFormSLS->hh[141];
c2.v[15] += (sum_160_1_052)*MainFormSLS->hh[12];
c2.v[15] += (sum_160_1_053)*MainFormSLS->hh[43];
c2.v[15] += (sum_160_1_054)*MainFormSLS->hh[74];
c2.v[15] += (sum_160_1_055)*MainFormSLS->hh[105];
c2.v[15] += (sum_160_1_056)*MainFormSLS->hh[136];
c2.v[15] += (sum_160_1_057)*MainFormSLS->hh[7];
c2.v[15] += (sum_160_1_058)*MainFormSLS->hh[38];
c2.v[15] += (sum_160_1_059)*MainFormSLS->hh[69];
c2.v[15] += (sum_160_1_060)*MainFormSLS->hh[100];
c2.v[15] += (sum_160_1_061)*MainFormSLS->hh[131];
c2.v[15] += (sum_160_1_062)*MainFormSLS->hh[2];
c2.v[15] += (sum_160_1_063)*MainFormSLS->hh[33];
c2.v[15] += (sum_160_1_064)*MainFormSLS->hh[64];
c2.v[15] += (sum_160_1_065)*MainFormSLS->hh[95];
c2.v[15] += (sum_160_1_066)*MainFormSLS->hh[126];
c2.v[15] += (sum_160_1_067)*MainFormSLS->hh[157];
c2.v[15] += (sum_160_1_068)*MainFormSLS->hh[28];
c2.v[15] += (sum_160_1_069)*MainFormSLS->hh[59];
c2.v[15] += (sum_160_1_070)*MainFormSLS->hh[90];
c2.v[15] += (sum_160_1_071)*MainFormSLS->hh[121];
c2.v[15] += (sum_160_1_072)*MainFormSLS->hh[152];
c2.v[15] += (sum_160_1_073)*MainFormSLS->hh[23];
c2.v[15] += (sum_160_1_074)*MainFormSLS->hh[54];
c2.v[15] += (sum_160_1_075)*MainFormSLS->hh[85];
c2.v[15] += (sum_160_1_076)*MainFormSLS->hh[116];
c2.v[15] += (sum_160_1_077)*MainFormSLS->hh[147];
c2.v[15] += (sum_160_1_078)*MainFormSLS->hh[18];
c2.v[15] += (sum_160_1_079)*MainFormSLS->hh[49];
c2.v[15] += (sum_160_1_080)*MainFormSLS->hh[80];
c2.v[15] += (sum_160_1_081)*MainFormSLS->hh[111];
c2.v[15] += (sum_160_1_082)*MainFormSLS->hh[142];
c2.v[15] += (sum_160_1_083)*MainFormSLS->hh[13];
c2.v[15] += (sum_160_1_084)*MainFormSLS->hh[44];
c2.v[15] += (sum_160_1_085)*MainFormSLS->hh[75];
c2.v[15] += (sum_160_1_086)*MainFormSLS->hh[106];
c2.v[15] += (sum_160_1_087)*MainFormSLS->hh[137];
c2.v[15] += (sum_160_1_088)*MainFormSLS->hh[8];
c2.v[15] += (sum_160_1_089)*MainFormSLS->hh[39];
c2.v[15] += (sum_160_1_090)*MainFormSLS->hh[70];
c2.v[15] += (sum_160_1_091)*MainFormSLS->hh[101];
c2.v[15] += (sum_160_1_092)*MainFormSLS->hh[132];
c2.v[15] += (sum_160_1_093)*MainFormSLS->hh[3];
c2.v[15] += (sum_160_1_094)*MainFormSLS->hh[34];
c2.v[15] += (sum_160_1_095)*MainFormSLS->hh[65];
c2.v[15] += (sum_160_1_096)*MainFormSLS->hh[96];
c2.v[15] += (sum_160_1_097)*MainFormSLS->hh[127];
c2.v[15] += (sum_160_1_098)*MainFormSLS->hh[158];
c2.v[15] += (sum_160_1_099)*MainFormSLS->hh[29];
c2.v[15] += (sum_160_1_100)*MainFormSLS->hh[60];
c2.v[15] += (sum_160_1_101)*MainFormSLS->hh[91];
c2.v[15] += (sum_160_1_102)*MainFormSLS->hh[122];
c2.v[15] += (sum_160_1_103)*MainFormSLS->hh[153];
c2.v[15] += (sum_160_1_104)*MainFormSLS->hh[24];
c2.v[15] += (sum_160_1_105)*MainFormSLS->hh[55];
c2.v[15] += (sum_160_1_106)*MainFormSLS->hh[86];
c2.v[15] += (sum_160_1_107)*MainFormSLS->hh[117];
c2.v[15] += (sum_160_1_108)*MainFormSLS->hh[148];
c2.v[15] += (sum_160_1_109)*MainFormSLS->hh[19];
c2.v[15] += (sum_160_1_110)*MainFormSLS->hh[50];
c2.v[15] += (sum_160_1_111)*MainFormSLS->hh[81];
c2.v[15] += (sum_160_1_112)*MainFormSLS->hh[112];
c2.v[15] += (sum_160_1_113)*MainFormSLS->hh[143];
c2.v[15] += (sum_160_1_114)*MainFormSLS->hh[14];
c2.v[15] += (sum_160_1_115)*MainFormSLS->hh[45];
c2.v[15] += (sum_160_1_116)*MainFormSLS->hh[76];
c2.v[15] += (sum_160_1_117)*MainFormSLS->hh[107];
c2.v[15] += (sum_160_1_118)*MainFormSLS->hh[138];
c2.v[15] += (sum_160_1_119)*MainFormSLS->hh[9];
c2.v[15] += (sum_160_1_120)*MainFormSLS->hh[40];
c2.v[15] += (sum_160_1_121)*MainFormSLS->hh[71];
c2.v[15] += (sum_160_1_122)*MainFormSLS->hh[102];
c2.v[15] += (sum_160_1_123)*MainFormSLS->hh[133];
c2.v[15] += (sum_160_1_124)*MainFormSLS->hh[4];
c2.v[15] += (sum_160_1_125)*MainFormSLS->hh[35];
c2.v[15] += (sum_160_1_126)*MainFormSLS->hh[66];
c2.v[15] += (sum_160_1_127)*MainFormSLS->hh[97];
c2.v[15] += (sum_160_1_128)*MainFormSLS->hh[128];
c2.v[15] += (sum_160_1_129)*MainFormSLS->hh[159];
c2.v[15] += (sum_160_1_130)*MainFormSLS->hh[30];
c2.v[15] += (sum_160_1_131)*MainFormSLS->hh[61];
c2.v[15] += (sum_160_1_132)*MainFormSLS->hh[92];
c2.v[15] += (sum_160_1_133)*MainFormSLS->hh[123];
c2.v[15] += (sum_160_1_134)*MainFormSLS->hh[154];
c2.v[15] += (sum_160_1_135)*MainFormSLS->hh[25];
c2.v[15] += (sum_160_1_136)*MainFormSLS->hh[56];
c2.v[15] += (sum_160_1_137)*MainFormSLS->hh[87];
c2.v[15] += (sum_160_1_138)*MainFormSLS->hh[118];
c2.v[15] += (sum_160_1_139)*MainFormSLS->hh[149];
c2.v[15] += (sum_160_1_140)*MainFormSLS->hh[20];
c2.v[15] += (sum_160_1_141)*MainFormSLS->hh[51];
c2.v[15] += (sum_160_1_142)*MainFormSLS->hh[82];
c2.v[15] += (sum_160_1_143)*MainFormSLS->hh[113];
c2.v[15] += (sum_160_1_144)*MainFormSLS->hh[144];
c2.v[15] += (sum_160_1_145)*MainFormSLS->hh[15];
c2.v[15] += (sum_160_1_146)*MainFormSLS->hh[46];
c2.v[15] += (sum_160_1_147)*MainFormSLS->hh[77];
c2.v[15] += (sum_160_1_148)*MainFormSLS->hh[108];
c2.v[15] += (sum_160_1_149)*MainFormSLS->hh[139];
c2.v[15] += (sum_160_1_150)*MainFormSLS->hh[10];
c2.v[15] += (sum_160_1_151)*MainFormSLS->hh[41];
c2.v[15] += (sum_160_1_152)*MainFormSLS->hh[72];
c2.v[15] += (sum_160_1_153)*MainFormSLS->hh[103];
c2.v[15] += (sum_160_1_154)*MainFormSLS->hh[134];
c2.v[15] += (sum_160_1_155)*MainFormSLS->hh[5];
c2.v[15] += (sum_160_1_156)*MainFormSLS->hh[36];
c2.v[15] += (sum_160_1_157)*MainFormSLS->hh[67];
c2.v[15] += (sum_160_1_158)*MainFormSLS->hh[98];
c2.v[15] += (sum_160_1_159)*MainFormSLS->hh[129];

//frequency level id 33
c2.v[16] += (sum_160_1_000)*MainFormSLS->hh[0];
c2.v[16] += (sum_160_1_001)*MainFormSLS->hh[33];
c2.v[16] += (sum_160_1_002)*MainFormSLS->hh[66];
c2.v[16] += (sum_160_1_003)*MainFormSLS->hh[99];
c2.v[16] += (sum_160_1_004)*MainFormSLS->hh[132];
c2.v[16] += (sum_160_1_005)*MainFormSLS->hh[5];
c2.v[16] += (sum_160_1_006)*MainFormSLS->hh[38];
c2.v[16] += (sum_160_1_007)*MainFormSLS->hh[71];
c2.v[16] += (sum_160_1_008)*MainFormSLS->hh[104];
c2.v[16] += (sum_160_1_009)*MainFormSLS->hh[137];
c2.v[16] += (sum_160_1_010)*MainFormSLS->hh[10];
c2.v[16] += (sum_160_1_011)*MainFormSLS->hh[43];
c2.v[16] += (sum_160_1_012)*MainFormSLS->hh[76];
c2.v[16] += (sum_160_1_013)*MainFormSLS->hh[109];
c2.v[16] += (sum_160_1_014)*MainFormSLS->hh[142];
c2.v[16] += (sum_160_1_015)*MainFormSLS->hh[15];
c2.v[16] += (sum_160_1_016)*MainFormSLS->hh[48];
c2.v[16] += (sum_160_1_017)*MainFormSLS->hh[81];
c2.v[16] += (sum_160_1_018)*MainFormSLS->hh[114];
c2.v[16] += (sum_160_1_019)*MainFormSLS->hh[147];
c2.v[16] += (sum_160_1_020)*MainFormSLS->hh[20];
c2.v[16] += (sum_160_1_021)*MainFormSLS->hh[53];
c2.v[16] += (sum_160_1_022)*MainFormSLS->hh[86];
c2.v[16] += (sum_160_1_023)*MainFormSLS->hh[119];
c2.v[16] += (sum_160_1_024)*MainFormSLS->hh[152];
c2.v[16] += (sum_160_1_025)*MainFormSLS->hh[25];
c2.v[16] += (sum_160_1_026)*MainFormSLS->hh[58];
c2.v[16] += (sum_160_1_027)*MainFormSLS->hh[91];
c2.v[16] += (sum_160_1_028)*MainFormSLS->hh[124];
c2.v[16] += (sum_160_1_029)*MainFormSLS->hh[157];
c2.v[16] += (sum_160_1_030)*MainFormSLS->hh[30];
c2.v[16] += (sum_160_1_031)*MainFormSLS->hh[63];
c2.v[16] += (sum_160_1_032)*MainFormSLS->hh[96];
c2.v[16] += (sum_160_1_033)*MainFormSLS->hh[129];
c2.v[16] += (sum_160_1_034)*MainFormSLS->hh[2];
c2.v[16] += (sum_160_1_035)*MainFormSLS->hh[35];
c2.v[16] += (sum_160_1_036)*MainFormSLS->hh[68];
c2.v[16] += (sum_160_1_037)*MainFormSLS->hh[101];
c2.v[16] += (sum_160_1_038)*MainFormSLS->hh[134];
c2.v[16] += (sum_160_1_039)*MainFormSLS->hh[7];
c2.v[16] += (sum_160_1_040)*MainFormSLS->hh[40];
c2.v[16] += (sum_160_1_041)*MainFormSLS->hh[73];
c2.v[16] += (sum_160_1_042)*MainFormSLS->hh[106];
c2.v[16] += (sum_160_1_043)*MainFormSLS->hh[139];
c2.v[16] += (sum_160_1_044)*MainFormSLS->hh[12];
c2.v[16] += (sum_160_1_045)*MainFormSLS->hh[45];
c2.v[16] += (sum_160_1_046)*MainFormSLS->hh[78];
c2.v[16] += (sum_160_1_047)*MainFormSLS->hh[111];
c2.v[16] += (sum_160_1_048)*MainFormSLS->hh[144];
c2.v[16] += (sum_160_1_049)*MainFormSLS->hh[17];
c2.v[16] += (sum_160_1_050)*MainFormSLS->hh[50];
c2.v[16] += (sum_160_1_051)*MainFormSLS->hh[83];
c2.v[16] += (sum_160_1_052)*MainFormSLS->hh[116];
c2.v[16] += (sum_160_1_053)*MainFormSLS->hh[149];
c2.v[16] += (sum_160_1_054)*MainFormSLS->hh[22];
c2.v[16] += (sum_160_1_055)*MainFormSLS->hh[55];
c2.v[16] += (sum_160_1_056)*MainFormSLS->hh[88];
c2.v[16] += (sum_160_1_057)*MainFormSLS->hh[121];
c2.v[16] += (sum_160_1_058)*MainFormSLS->hh[154];
c2.v[16] += (sum_160_1_059)*MainFormSLS->hh[27];
c2.v[16] += (sum_160_1_060)*MainFormSLS->hh[60];
c2.v[16] += (sum_160_1_061)*MainFormSLS->hh[93];
c2.v[16] += (sum_160_1_062)*MainFormSLS->hh[126];
c2.v[16] += (sum_160_1_063)*MainFormSLS->hh[159];
c2.v[16] += (sum_160_1_064)*MainFormSLS->hh[32];
c2.v[16] += (sum_160_1_065)*MainFormSLS->hh[65];
c2.v[16] += (sum_160_1_066)*MainFormSLS->hh[98];
c2.v[16] += (sum_160_1_067)*MainFormSLS->hh[131];
c2.v[16] += (sum_160_1_068)*MainFormSLS->hh[4];
c2.v[16] += (sum_160_1_069)*MainFormSLS->hh[37];
c2.v[16] += (sum_160_1_070)*MainFormSLS->hh[70];
c2.v[16] += (sum_160_1_071)*MainFormSLS->hh[103];
c2.v[16] += (sum_160_1_072)*MainFormSLS->hh[136];
c2.v[16] += (sum_160_1_073)*MainFormSLS->hh[9];
c2.v[16] += (sum_160_1_074)*MainFormSLS->hh[42];
c2.v[16] += (sum_160_1_075)*MainFormSLS->hh[75];
c2.v[16] += (sum_160_1_076)*MainFormSLS->hh[108];
c2.v[16] += (sum_160_1_077)*MainFormSLS->hh[141];
c2.v[16] += (sum_160_1_078)*MainFormSLS->hh[14];
c2.v[16] += (sum_160_1_079)*MainFormSLS->hh[47];
c2.v[16] += (sum_160_1_080)*MainFormSLS->hh[80];
c2.v[16] += (sum_160_1_081)*MainFormSLS->hh[113];
c2.v[16] += (sum_160_1_082)*MainFormSLS->hh[146];
c2.v[16] += (sum_160_1_083)*MainFormSLS->hh[19];
c2.v[16] += (sum_160_1_084)*MainFormSLS->hh[52];
c2.v[16] += (sum_160_1_085)*MainFormSLS->hh[85];
c2.v[16] += (sum_160_1_086)*MainFormSLS->hh[118];
c2.v[16] += (sum_160_1_087)*MainFormSLS->hh[151];
c2.v[16] += (sum_160_1_088)*MainFormSLS->hh[24];
c2.v[16] += (sum_160_1_089)*MainFormSLS->hh[57];
c2.v[16] += (sum_160_1_090)*MainFormSLS->hh[90];
c2.v[16] += (sum_160_1_091)*MainFormSLS->hh[123];
c2.v[16] += (sum_160_1_092)*MainFormSLS->hh[156];
c2.v[16] += (sum_160_1_093)*MainFormSLS->hh[29];
c2.v[16] += (sum_160_1_094)*MainFormSLS->hh[62];
c2.v[16] += (sum_160_1_095)*MainFormSLS->hh[95];
c2.v[16] += (sum_160_1_096)*MainFormSLS->hh[128];
c2.v[16] += (sum_160_1_097)*MainFormSLS->hh[1];
c2.v[16] += (sum_160_1_098)*MainFormSLS->hh[34];
c2.v[16] += (sum_160_1_099)*MainFormSLS->hh[67];
c2.v[16] += (sum_160_1_100)*MainFormSLS->hh[100];
c2.v[16] += (sum_160_1_101)*MainFormSLS->hh[133];
c2.v[16] += (sum_160_1_102)*MainFormSLS->hh[6];
c2.v[16] += (sum_160_1_103)*MainFormSLS->hh[39];
c2.v[16] += (sum_160_1_104)*MainFormSLS->hh[72];
c2.v[16] += (sum_160_1_105)*MainFormSLS->hh[105];
c2.v[16] += (sum_160_1_106)*MainFormSLS->hh[138];
c2.v[16] += (sum_160_1_107)*MainFormSLS->hh[11];
c2.v[16] += (sum_160_1_108)*MainFormSLS->hh[44];
c2.v[16] += (sum_160_1_109)*MainFormSLS->hh[77];
c2.v[16] += (sum_160_1_110)*MainFormSLS->hh[110];
c2.v[16] += (sum_160_1_111)*MainFormSLS->hh[143];
c2.v[16] += (sum_160_1_112)*MainFormSLS->hh[16];
c2.v[16] += (sum_160_1_113)*MainFormSLS->hh[49];
c2.v[16] += (sum_160_1_114)*MainFormSLS->hh[82];
c2.v[16] += (sum_160_1_115)*MainFormSLS->hh[115];
c2.v[16] += (sum_160_1_116)*MainFormSLS->hh[148];
c2.v[16] += (sum_160_1_117)*MainFormSLS->hh[21];
c2.v[16] += (sum_160_1_118)*MainFormSLS->hh[54];
c2.v[16] += (sum_160_1_119)*MainFormSLS->hh[87];
c2.v[16] += (sum_160_1_120)*MainFormSLS->hh[120];
c2.v[16] += (sum_160_1_121)*MainFormSLS->hh[153];
c2.v[16] += (sum_160_1_122)*MainFormSLS->hh[26];
c2.v[16] += (sum_160_1_123)*MainFormSLS->hh[59];
c2.v[16] += (sum_160_1_124)*MainFormSLS->hh[92];
c2.v[16] += (sum_160_1_125)*MainFormSLS->hh[125];
c2.v[16] += (sum_160_1_126)*MainFormSLS->hh[158];
c2.v[16] += (sum_160_1_127)*MainFormSLS->hh[31];
c2.v[16] += (sum_160_1_128)*MainFormSLS->hh[64];
c2.v[16] += (sum_160_1_129)*MainFormSLS->hh[97];
c2.v[16] += (sum_160_1_130)*MainFormSLS->hh[130];
c2.v[16] += (sum_160_1_131)*MainFormSLS->hh[3];
c2.v[16] += (sum_160_1_132)*MainFormSLS->hh[36];
c2.v[16] += (sum_160_1_133)*MainFormSLS->hh[69];
c2.v[16] += (sum_160_1_134)*MainFormSLS->hh[102];
c2.v[16] += (sum_160_1_135)*MainFormSLS->hh[135];
c2.v[16] += (sum_160_1_136)*MainFormSLS->hh[8];
c2.v[16] += (sum_160_1_137)*MainFormSLS->hh[41];
c2.v[16] += (sum_160_1_138)*MainFormSLS->hh[74];
c2.v[16] += (sum_160_1_139)*MainFormSLS->hh[107];
c2.v[16] += (sum_160_1_140)*MainFormSLS->hh[140];
c2.v[16] += (sum_160_1_141)*MainFormSLS->hh[13];
c2.v[16] += (sum_160_1_142)*MainFormSLS->hh[46];
c2.v[16] += (sum_160_1_143)*MainFormSLS->hh[79];
c2.v[16] += (sum_160_1_144)*MainFormSLS->hh[112];
c2.v[16] += (sum_160_1_145)*MainFormSLS->hh[145];
c2.v[16] += (sum_160_1_146)*MainFormSLS->hh[18];
c2.v[16] += (sum_160_1_147)*MainFormSLS->hh[51];
c2.v[16] += (sum_160_1_148)*MainFormSLS->hh[84];
c2.v[16] += (sum_160_1_149)*MainFormSLS->hh[117];
c2.v[16] += (sum_160_1_150)*MainFormSLS->hh[150];
c2.v[16] += (sum_160_1_151)*MainFormSLS->hh[23];
c2.v[16] += (sum_160_1_152)*MainFormSLS->hh[56];
c2.v[16] += (sum_160_1_153)*MainFormSLS->hh[89];
c2.v[16] += (sum_160_1_154)*MainFormSLS->hh[122];
c2.v[16] += (sum_160_1_155)*MainFormSLS->hh[155];
c2.v[16] += (sum_160_1_156)*MainFormSLS->hh[28];
c2.v[16] += (sum_160_1_157)*MainFormSLS->hh[61];
c2.v[16] += (sum_160_1_158)*MainFormSLS->hh[94];
c2.v[16] += (sum_160_1_159)*MainFormSLS->hh[127];

//frequency level id 35
c2.v[17] += (sum_32_5_000)*MainFormSLS->hh[0];
c2.v[17] += (sum_32_5_001)*MainFormSLS->hh[35];
c2.v[17] += (sum_32_5_002)*MainFormSLS->hh[70];
c2.v[17] += (sum_32_5_003)*MainFormSLS->hh[105];
c2.v[17] += (sum_32_5_004)*MainFormSLS->hh[140];
c2.v[17] += (sum_32_5_005)*MainFormSLS->hh[15];
c2.v[17] += (sum_32_5_006)*MainFormSLS->hh[50];
c2.v[17] += (sum_32_5_007)*MainFormSLS->hh[85];
c2.v[17] += (sum_32_5_008)*MainFormSLS->hh[120];
c2.v[17] += (sum_32_5_009)*MainFormSLS->hh[155];
c2.v[17] += (sum_32_5_010)*MainFormSLS->hh[30];
c2.v[17] += (sum_32_5_011)*MainFormSLS->hh[65];
c2.v[17] += (sum_32_5_012)*MainFormSLS->hh[100];
c2.v[17] += (sum_32_5_013)*MainFormSLS->hh[135];
c2.v[17] += (sum_32_5_014)*MainFormSLS->hh[10];
c2.v[17] += (sum_32_5_015)*MainFormSLS->hh[45];
c2.v[17] += (sum_32_5_016)*MainFormSLS->hh[80];
c2.v[17] += (sum_32_5_017)*MainFormSLS->hh[115];
c2.v[17] += (sum_32_5_018)*MainFormSLS->hh[150];
c2.v[17] += (sum_32_5_019)*MainFormSLS->hh[25];
c2.v[17] += (sum_32_5_020)*MainFormSLS->hh[60];
c2.v[17] += (sum_32_5_021)*MainFormSLS->hh[95];
c2.v[17] += (sum_32_5_022)*MainFormSLS->hh[130];
c2.v[17] += (sum_32_5_023)*MainFormSLS->hh[5];
c2.v[17] += (sum_32_5_024)*MainFormSLS->hh[40];
c2.v[17] += (sum_32_5_025)*MainFormSLS->hh[75];
c2.v[17] += (sum_32_5_026)*MainFormSLS->hh[110];
c2.v[17] += (sum_32_5_027)*MainFormSLS->hh[145];
c2.v[17] += (sum_32_5_028)*MainFormSLS->hh[20];
c2.v[17] += (sum_32_5_029)*MainFormSLS->hh[55];
c2.v[17] += (sum_32_5_030)*MainFormSLS->hh[90];
c2.v[17] += (sum_32_5_031)*MainFormSLS->hh[125];

//frequency level id 37
c2.v[18] += (sum_160_1_000)*MainFormSLS->hh[0];
c2.v[18] += (sum_160_1_001)*MainFormSLS->hh[37];
c2.v[18] += (sum_160_1_002)*MainFormSLS->hh[74];
c2.v[18] += (sum_160_1_003)*MainFormSLS->hh[111];
c2.v[18] += (sum_160_1_004)*MainFormSLS->hh[148];
c2.v[18] += (sum_160_1_005)*MainFormSLS->hh[25];
c2.v[18] += (sum_160_1_006)*MainFormSLS->hh[62];
c2.v[18] += (sum_160_1_007)*MainFormSLS->hh[99];
c2.v[18] += (sum_160_1_008)*MainFormSLS->hh[136];
c2.v[18] += (sum_160_1_009)*MainFormSLS->hh[13];
c2.v[18] += (sum_160_1_010)*MainFormSLS->hh[50];
c2.v[18] += (sum_160_1_011)*MainFormSLS->hh[87];
c2.v[18] += (sum_160_1_012)*MainFormSLS->hh[124];
c2.v[18] += (sum_160_1_013)*MainFormSLS->hh[1];
c2.v[18] += (sum_160_1_014)*MainFormSLS->hh[38];
c2.v[18] += (sum_160_1_015)*MainFormSLS->hh[75];
c2.v[18] += (sum_160_1_016)*MainFormSLS->hh[112];
c2.v[18] += (sum_160_1_017)*MainFormSLS->hh[149];
c2.v[18] += (sum_160_1_018)*MainFormSLS->hh[26];
c2.v[18] += (sum_160_1_019)*MainFormSLS->hh[63];
c2.v[18] += (sum_160_1_020)*MainFormSLS->hh[100];
c2.v[18] += (sum_160_1_021)*MainFormSLS->hh[137];
c2.v[18] += (sum_160_1_022)*MainFormSLS->hh[14];
c2.v[18] += (sum_160_1_023)*MainFormSLS->hh[51];
c2.v[18] += (sum_160_1_024)*MainFormSLS->hh[88];
c2.v[18] += (sum_160_1_025)*MainFormSLS->hh[125];
c2.v[18] += (sum_160_1_026)*MainFormSLS->hh[2];
c2.v[18] += (sum_160_1_027)*MainFormSLS->hh[39];
c2.v[18] += (sum_160_1_028)*MainFormSLS->hh[76];
c2.v[18] += (sum_160_1_029)*MainFormSLS->hh[113];
c2.v[18] += (sum_160_1_030)*MainFormSLS->hh[150];
c2.v[18] += (sum_160_1_031)*MainFormSLS->hh[27];
c2.v[18] += (sum_160_1_032)*MainFormSLS->hh[64];
c2.v[18] += (sum_160_1_033)*MainFormSLS->hh[101];
c2.v[18] += (sum_160_1_034)*MainFormSLS->hh[138];
c2.v[18] += (sum_160_1_035)*MainFormSLS->hh[15];
c2.v[18] += (sum_160_1_036)*MainFormSLS->hh[52];
c2.v[18] += (sum_160_1_037)*MainFormSLS->hh[89];
c2.v[18] += (sum_160_1_038)*MainFormSLS->hh[126];
c2.v[18] += (sum_160_1_039)*MainFormSLS->hh[3];
c2.v[18] += (sum_160_1_040)*MainFormSLS->hh[40];
c2.v[18] += (sum_160_1_041)*MainFormSLS->hh[77];
c2.v[18] += (sum_160_1_042)*MainFormSLS->hh[114];
c2.v[18] += (sum_160_1_043)*MainFormSLS->hh[151];
c2.v[18] += (sum_160_1_044)*MainFormSLS->hh[28];
c2.v[18] += (sum_160_1_045)*MainFormSLS->hh[65];
c2.v[18] += (sum_160_1_046)*MainFormSLS->hh[102];
c2.v[18] += (sum_160_1_047)*MainFormSLS->hh[139];
c2.v[18] += (sum_160_1_048)*MainFormSLS->hh[16];
c2.v[18] += (sum_160_1_049)*MainFormSLS->hh[53];
c2.v[18] += (sum_160_1_050)*MainFormSLS->hh[90];
c2.v[18] += (sum_160_1_051)*MainFormSLS->hh[127];
c2.v[18] += (sum_160_1_052)*MainFormSLS->hh[4];
c2.v[18] += (sum_160_1_053)*MainFormSLS->hh[41];
c2.v[18] += (sum_160_1_054)*MainFormSLS->hh[78];
c2.v[18] += (sum_160_1_055)*MainFormSLS->hh[115];
c2.v[18] += (sum_160_1_056)*MainFormSLS->hh[152];
c2.v[18] += (sum_160_1_057)*MainFormSLS->hh[29];
c2.v[18] += (sum_160_1_058)*MainFormSLS->hh[66];
c2.v[18] += (sum_160_1_059)*MainFormSLS->hh[103];
c2.v[18] += (sum_160_1_060)*MainFormSLS->hh[140];
c2.v[18] += (sum_160_1_061)*MainFormSLS->hh[17];
c2.v[18] += (sum_160_1_062)*MainFormSLS->hh[54];
c2.v[18] += (sum_160_1_063)*MainFormSLS->hh[91];
c2.v[18] += (sum_160_1_064)*MainFormSLS->hh[128];
c2.v[18] += (sum_160_1_065)*MainFormSLS->hh[5];
c2.v[18] += (sum_160_1_066)*MainFormSLS->hh[42];
c2.v[18] += (sum_160_1_067)*MainFormSLS->hh[79];
c2.v[18] += (sum_160_1_068)*MainFormSLS->hh[116];
c2.v[18] += (sum_160_1_069)*MainFormSLS->hh[153];
c2.v[18] += (sum_160_1_070)*MainFormSLS->hh[30];
c2.v[18] += (sum_160_1_071)*MainFormSLS->hh[67];
c2.v[18] += (sum_160_1_072)*MainFormSLS->hh[104];
c2.v[18] += (sum_160_1_073)*MainFormSLS->hh[141];
c2.v[18] += (sum_160_1_074)*MainFormSLS->hh[18];
c2.v[18] += (sum_160_1_075)*MainFormSLS->hh[55];
c2.v[18] += (sum_160_1_076)*MainFormSLS->hh[92];
c2.v[18] += (sum_160_1_077)*MainFormSLS->hh[129];
c2.v[18] += (sum_160_1_078)*MainFormSLS->hh[6];
c2.v[18] += (sum_160_1_079)*MainFormSLS->hh[43];
c2.v[18] += (sum_160_1_080)*MainFormSLS->hh[80];
c2.v[18] += (sum_160_1_081)*MainFormSLS->hh[117];
c2.v[18] += (sum_160_1_082)*MainFormSLS->hh[154];
c2.v[18] += (sum_160_1_083)*MainFormSLS->hh[31];
c2.v[18] += (sum_160_1_084)*MainFormSLS->hh[68];
c2.v[18] += (sum_160_1_085)*MainFormSLS->hh[105];
c2.v[18] += (sum_160_1_086)*MainFormSLS->hh[142];
c2.v[18] += (sum_160_1_087)*MainFormSLS->hh[19];
c2.v[18] += (sum_160_1_088)*MainFormSLS->hh[56];
c2.v[18] += (sum_160_1_089)*MainFormSLS->hh[93];
c2.v[18] += (sum_160_1_090)*MainFormSLS->hh[130];
c2.v[18] += (sum_160_1_091)*MainFormSLS->hh[7];
c2.v[18] += (sum_160_1_092)*MainFormSLS->hh[44];
c2.v[18] += (sum_160_1_093)*MainFormSLS->hh[81];
c2.v[18] += (sum_160_1_094)*MainFormSLS->hh[118];
c2.v[18] += (sum_160_1_095)*MainFormSLS->hh[155];
c2.v[18] += (sum_160_1_096)*MainFormSLS->hh[32];
c2.v[18] += (sum_160_1_097)*MainFormSLS->hh[69];
c2.v[18] += (sum_160_1_098)*MainFormSLS->hh[106];
c2.v[18] += (sum_160_1_099)*MainFormSLS->hh[143];
c2.v[18] += (sum_160_1_100)*MainFormSLS->hh[20];
c2.v[18] += (sum_160_1_101)*MainFormSLS->hh[57];
c2.v[18] += (sum_160_1_102)*MainFormSLS->hh[94];
c2.v[18] += (sum_160_1_103)*MainFormSLS->hh[131];
c2.v[18] += (sum_160_1_104)*MainFormSLS->hh[8];
c2.v[18] += (sum_160_1_105)*MainFormSLS->hh[45];
c2.v[18] += (sum_160_1_106)*MainFormSLS->hh[82];
c2.v[18] += (sum_160_1_107)*MainFormSLS->hh[119];
c2.v[18] += (sum_160_1_108)*MainFormSLS->hh[156];
c2.v[18] += (sum_160_1_109)*MainFormSLS->hh[33];
c2.v[18] += (sum_160_1_110)*MainFormSLS->hh[70];
c2.v[18] += (sum_160_1_111)*MainFormSLS->hh[107];
c2.v[18] += (sum_160_1_112)*MainFormSLS->hh[144];
c2.v[18] += (sum_160_1_113)*MainFormSLS->hh[21];
c2.v[18] += (sum_160_1_114)*MainFormSLS->hh[58];
c2.v[18] += (sum_160_1_115)*MainFormSLS->hh[95];
c2.v[18] += (sum_160_1_116)*MainFormSLS->hh[132];
c2.v[18] += (sum_160_1_117)*MainFormSLS->hh[9];
c2.v[18] += (sum_160_1_118)*MainFormSLS->hh[46];
c2.v[18] += (sum_160_1_119)*MainFormSLS->hh[83];
c2.v[18] += (sum_160_1_120)*MainFormSLS->hh[120];
c2.v[18] += (sum_160_1_121)*MainFormSLS->hh[157];
c2.v[18] += (sum_160_1_122)*MainFormSLS->hh[34];
c2.v[18] += (sum_160_1_123)*MainFormSLS->hh[71];
c2.v[18] += (sum_160_1_124)*MainFormSLS->hh[108];
c2.v[18] += (sum_160_1_125)*MainFormSLS->hh[145];
c2.v[18] += (sum_160_1_126)*MainFormSLS->hh[22];
c2.v[18] += (sum_160_1_127)*MainFormSLS->hh[59];
c2.v[18] += (sum_160_1_128)*MainFormSLS->hh[96];
c2.v[18] += (sum_160_1_129)*MainFormSLS->hh[133];
c2.v[18] += (sum_160_1_130)*MainFormSLS->hh[10];
c2.v[18] += (sum_160_1_131)*MainFormSLS->hh[47];
c2.v[18] += (sum_160_1_132)*MainFormSLS->hh[84];
c2.v[18] += (sum_160_1_133)*MainFormSLS->hh[121];
c2.v[18] += (sum_160_1_134)*MainFormSLS->hh[158];
c2.v[18] += (sum_160_1_135)*MainFormSLS->hh[35];
c2.v[18] += (sum_160_1_136)*MainFormSLS->hh[72];
c2.v[18] += (sum_160_1_137)*MainFormSLS->hh[109];
c2.v[18] += (sum_160_1_138)*MainFormSLS->hh[146];
c2.v[18] += (sum_160_1_139)*MainFormSLS->hh[23];
c2.v[18] += (sum_160_1_140)*MainFormSLS->hh[60];
c2.v[18] += (sum_160_1_141)*MainFormSLS->hh[97];
c2.v[18] += (sum_160_1_142)*MainFormSLS->hh[134];
c2.v[18] += (sum_160_1_143)*MainFormSLS->hh[11];
c2.v[18] += (sum_160_1_144)*MainFormSLS->hh[48];
c2.v[18] += (sum_160_1_145)*MainFormSLS->hh[85];
c2.v[18] += (sum_160_1_146)*MainFormSLS->hh[122];
c2.v[18] += (sum_160_1_147)*MainFormSLS->hh[159];
c2.v[18] += (sum_160_1_148)*MainFormSLS->hh[36];
c2.v[18] += (sum_160_1_149)*MainFormSLS->hh[73];
c2.v[18] += (sum_160_1_150)*MainFormSLS->hh[110];
c2.v[18] += (sum_160_1_151)*MainFormSLS->hh[147];
c2.v[18] += (sum_160_1_152)*MainFormSLS->hh[24];
c2.v[18] += (sum_160_1_153)*MainFormSLS->hh[61];
c2.v[18] += (sum_160_1_154)*MainFormSLS->hh[98];
c2.v[18] += (sum_160_1_155)*MainFormSLS->hh[135];
c2.v[18] += (sum_160_1_156)*MainFormSLS->hh[12];
c2.v[18] += (sum_160_1_157)*MainFormSLS->hh[49];
c2.v[18] += (sum_160_1_158)*MainFormSLS->hh[86];
c2.v[18] += (sum_160_1_159)*MainFormSLS->hh[123];

//frequency level id 39
c2.v[19] += (sum_160_1_000)*MainFormSLS->hh[0];
c2.v[19] += (sum_160_1_001)*MainFormSLS->hh[39];
c2.v[19] += (sum_160_1_002)*MainFormSLS->hh[78];
c2.v[19] += (sum_160_1_003)*MainFormSLS->hh[117];
c2.v[19] += (sum_160_1_004)*MainFormSLS->hh[156];
c2.v[19] += (sum_160_1_005)*MainFormSLS->hh[35];
c2.v[19] += (sum_160_1_006)*MainFormSLS->hh[74];
c2.v[19] += (sum_160_1_007)*MainFormSLS->hh[113];
c2.v[19] += (sum_160_1_008)*MainFormSLS->hh[152];
c2.v[19] += (sum_160_1_009)*MainFormSLS->hh[31];
c2.v[19] += (sum_160_1_010)*MainFormSLS->hh[70];
c2.v[19] += (sum_160_1_011)*MainFormSLS->hh[109];
c2.v[19] += (sum_160_1_012)*MainFormSLS->hh[148];
c2.v[19] += (sum_160_1_013)*MainFormSLS->hh[27];
c2.v[19] += (sum_160_1_014)*MainFormSLS->hh[66];
c2.v[19] += (sum_160_1_015)*MainFormSLS->hh[105];
c2.v[19] += (sum_160_1_016)*MainFormSLS->hh[144];
c2.v[19] += (sum_160_1_017)*MainFormSLS->hh[23];
c2.v[19] += (sum_160_1_018)*MainFormSLS->hh[62];
c2.v[19] += (sum_160_1_019)*MainFormSLS->hh[101];
c2.v[19] += (sum_160_1_020)*MainFormSLS->hh[140];
c2.v[19] += (sum_160_1_021)*MainFormSLS->hh[19];
c2.v[19] += (sum_160_1_022)*MainFormSLS->hh[58];
c2.v[19] += (sum_160_1_023)*MainFormSLS->hh[97];
c2.v[19] += (sum_160_1_024)*MainFormSLS->hh[136];
c2.v[19] += (sum_160_1_025)*MainFormSLS->hh[15];
c2.v[19] += (sum_160_1_026)*MainFormSLS->hh[54];
c2.v[19] += (sum_160_1_027)*MainFormSLS->hh[93];
c2.v[19] += (sum_160_1_028)*MainFormSLS->hh[132];
c2.v[19] += (sum_160_1_029)*MainFormSLS->hh[11];
c2.v[19] += (sum_160_1_030)*MainFormSLS->hh[50];
c2.v[19] += (sum_160_1_031)*MainFormSLS->hh[89];
c2.v[19] += (sum_160_1_032)*MainFormSLS->hh[128];
c2.v[19] += (sum_160_1_033)*MainFormSLS->hh[7];
c2.v[19] += (sum_160_1_034)*MainFormSLS->hh[46];
c2.v[19] += (sum_160_1_035)*MainFormSLS->hh[85];
c2.v[19] += (sum_160_1_036)*MainFormSLS->hh[124];
c2.v[19] += (sum_160_1_037)*MainFormSLS->hh[3];
c2.v[19] += (sum_160_1_038)*MainFormSLS->hh[42];
c2.v[19] += (sum_160_1_039)*MainFormSLS->hh[81];
c2.v[19] += (sum_160_1_040)*MainFormSLS->hh[120];
c2.v[19] += (sum_160_1_041)*MainFormSLS->hh[159];
c2.v[19] += (sum_160_1_042)*MainFormSLS->hh[38];
c2.v[19] += (sum_160_1_043)*MainFormSLS->hh[77];
c2.v[19] += (sum_160_1_044)*MainFormSLS->hh[116];
c2.v[19] += (sum_160_1_045)*MainFormSLS->hh[155];
c2.v[19] += (sum_160_1_046)*MainFormSLS->hh[34];
c2.v[19] += (sum_160_1_047)*MainFormSLS->hh[73];
c2.v[19] += (sum_160_1_048)*MainFormSLS->hh[112];
c2.v[19] += (sum_160_1_049)*MainFormSLS->hh[151];
c2.v[19] += (sum_160_1_050)*MainFormSLS->hh[30];
c2.v[19] += (sum_160_1_051)*MainFormSLS->hh[69];
c2.v[19] += (sum_160_1_052)*MainFormSLS->hh[108];
c2.v[19] += (sum_160_1_053)*MainFormSLS->hh[147];
c2.v[19] += (sum_160_1_054)*MainFormSLS->hh[26];
c2.v[19] += (sum_160_1_055)*MainFormSLS->hh[65];
c2.v[19] += (sum_160_1_056)*MainFormSLS->hh[104];
c2.v[19] += (sum_160_1_057)*MainFormSLS->hh[143];
c2.v[19] += (sum_160_1_058)*MainFormSLS->hh[22];
c2.v[19] += (sum_160_1_059)*MainFormSLS->hh[61];
c2.v[19] += (sum_160_1_060)*MainFormSLS->hh[100];
c2.v[19] += (sum_160_1_061)*MainFormSLS->hh[139];
c2.v[19] += (sum_160_1_062)*MainFormSLS->hh[18];
c2.v[19] += (sum_160_1_063)*MainFormSLS->hh[57];
c2.v[19] += (sum_160_1_064)*MainFormSLS->hh[96];
c2.v[19] += (sum_160_1_065)*MainFormSLS->hh[135];
c2.v[19] += (sum_160_1_066)*MainFormSLS->hh[14];
c2.v[19] += (sum_160_1_067)*MainFormSLS->hh[53];
c2.v[19] += (sum_160_1_068)*MainFormSLS->hh[92];
c2.v[19] += (sum_160_1_069)*MainFormSLS->hh[131];
c2.v[19] += (sum_160_1_070)*MainFormSLS->hh[10];
c2.v[19] += (sum_160_1_071)*MainFormSLS->hh[49];
c2.v[19] += (sum_160_1_072)*MainFormSLS->hh[88];
c2.v[19] += (sum_160_1_073)*MainFormSLS->hh[127];
c2.v[19] += (sum_160_1_074)*MainFormSLS->hh[6];
c2.v[19] += (sum_160_1_075)*MainFormSLS->hh[45];
c2.v[19] += (sum_160_1_076)*MainFormSLS->hh[84];
c2.v[19] += (sum_160_1_077)*MainFormSLS->hh[123];
c2.v[19] += (sum_160_1_078)*MainFormSLS->hh[2];
c2.v[19] += (sum_160_1_079)*MainFormSLS->hh[41];
c2.v[19] += (sum_160_1_080)*MainFormSLS->hh[80];
c2.v[19] += (sum_160_1_081)*MainFormSLS->hh[119];
c2.v[19] += (sum_160_1_082)*MainFormSLS->hh[158];
c2.v[19] += (sum_160_1_083)*MainFormSLS->hh[37];
c2.v[19] += (sum_160_1_084)*MainFormSLS->hh[76];
c2.v[19] += (sum_160_1_085)*MainFormSLS->hh[115];
c2.v[19] += (sum_160_1_086)*MainFormSLS->hh[154];
c2.v[19] += (sum_160_1_087)*MainFormSLS->hh[33];
c2.v[19] += (sum_160_1_088)*MainFormSLS->hh[72];
c2.v[19] += (sum_160_1_089)*MainFormSLS->hh[111];
c2.v[19] += (sum_160_1_090)*MainFormSLS->hh[150];
c2.v[19] += (sum_160_1_091)*MainFormSLS->hh[29];
c2.v[19] += (sum_160_1_092)*MainFormSLS->hh[68];
c2.v[19] += (sum_160_1_093)*MainFormSLS->hh[107];
c2.v[19] += (sum_160_1_094)*MainFormSLS->hh[146];
c2.v[19] += (sum_160_1_095)*MainFormSLS->hh[25];
c2.v[19] += (sum_160_1_096)*MainFormSLS->hh[64];
c2.v[19] += (sum_160_1_097)*MainFormSLS->hh[103];
c2.v[19] += (sum_160_1_098)*MainFormSLS->hh[142];
c2.v[19] += (sum_160_1_099)*MainFormSLS->hh[21];
c2.v[19] += (sum_160_1_100)*MainFormSLS->hh[60];
c2.v[19] += (sum_160_1_101)*MainFormSLS->hh[99];
c2.v[19] += (sum_160_1_102)*MainFormSLS->hh[138];
c2.v[19] += (sum_160_1_103)*MainFormSLS->hh[17];
c2.v[19] += (sum_160_1_104)*MainFormSLS->hh[56];
c2.v[19] += (sum_160_1_105)*MainFormSLS->hh[95];
c2.v[19] += (sum_160_1_106)*MainFormSLS->hh[134];
c2.v[19] += (sum_160_1_107)*MainFormSLS->hh[13];
c2.v[19] += (sum_160_1_108)*MainFormSLS->hh[52];
c2.v[19] += (sum_160_1_109)*MainFormSLS->hh[91];
c2.v[19] += (sum_160_1_110)*MainFormSLS->hh[130];
c2.v[19] += (sum_160_1_111)*MainFormSLS->hh[9];
c2.v[19] += (sum_160_1_112)*MainFormSLS->hh[48];
c2.v[19] += (sum_160_1_113)*MainFormSLS->hh[87];
c2.v[19] += (sum_160_1_114)*MainFormSLS->hh[126];
c2.v[19] += (sum_160_1_115)*MainFormSLS->hh[5];
c2.v[19] += (sum_160_1_116)*MainFormSLS->hh[44];
c2.v[19] += (sum_160_1_117)*MainFormSLS->hh[83];
c2.v[19] += (sum_160_1_118)*MainFormSLS->hh[122];
c2.v[19] += (sum_160_1_119)*MainFormSLS->hh[1];
c2.v[19] += (sum_160_1_120)*MainFormSLS->hh[40];
c2.v[19] += (sum_160_1_121)*MainFormSLS->hh[79];
c2.v[19] += (sum_160_1_122)*MainFormSLS->hh[118];
c2.v[19] += (sum_160_1_123)*MainFormSLS->hh[157];
c2.v[19] += (sum_160_1_124)*MainFormSLS->hh[36];
c2.v[19] += (sum_160_1_125)*MainFormSLS->hh[75];
c2.v[19] += (sum_160_1_126)*MainFormSLS->hh[114];
c2.v[19] += (sum_160_1_127)*MainFormSLS->hh[153];
c2.v[19] += (sum_160_1_128)*MainFormSLS->hh[32];
c2.v[19] += (sum_160_1_129)*MainFormSLS->hh[71];
c2.v[19] += (sum_160_1_130)*MainFormSLS->hh[110];
c2.v[19] += (sum_160_1_131)*MainFormSLS->hh[149];
c2.v[19] += (sum_160_1_132)*MainFormSLS->hh[28];
c2.v[19] += (sum_160_1_133)*MainFormSLS->hh[67];
c2.v[19] += (sum_160_1_134)*MainFormSLS->hh[106];
c2.v[19] += (sum_160_1_135)*MainFormSLS->hh[145];
c2.v[19] += (sum_160_1_136)*MainFormSLS->hh[24];
c2.v[19] += (sum_160_1_137)*MainFormSLS->hh[63];
c2.v[19] += (sum_160_1_138)*MainFormSLS->hh[102];
c2.v[19] += (sum_160_1_139)*MainFormSLS->hh[141];
c2.v[19] += (sum_160_1_140)*MainFormSLS->hh[20];
c2.v[19] += (sum_160_1_141)*MainFormSLS->hh[59];
c2.v[19] += (sum_160_1_142)*MainFormSLS->hh[98];
c2.v[19] += (sum_160_1_143)*MainFormSLS->hh[137];
c2.v[19] += (sum_160_1_144)*MainFormSLS->hh[16];
c2.v[19] += (sum_160_1_145)*MainFormSLS->hh[55];
c2.v[19] += (sum_160_1_146)*MainFormSLS->hh[94];
c2.v[19] += (sum_160_1_147)*MainFormSLS->hh[133];
c2.v[19] += (sum_160_1_148)*MainFormSLS->hh[12];
c2.v[19] += (sum_160_1_149)*MainFormSLS->hh[51];
c2.v[19] += (sum_160_1_150)*MainFormSLS->hh[90];
c2.v[19] += (sum_160_1_151)*MainFormSLS->hh[129];
c2.v[19] += (sum_160_1_152)*MainFormSLS->hh[8];
c2.v[19] += (sum_160_1_153)*MainFormSLS->hh[47];
c2.v[19] += (sum_160_1_154)*MainFormSLS->hh[86];
c2.v[19] += (sum_160_1_155)*MainFormSLS->hh[125];
c2.v[19] += (sum_160_1_156)*MainFormSLS->hh[4];
c2.v[19] += (sum_160_1_157)*MainFormSLS->hh[43];
c2.v[19] += (sum_160_1_158)*MainFormSLS->hh[82];
c2.v[19] += (sum_160_1_159)*MainFormSLS->hh[121];

//frequency level id 41
c2.v[20] += (sum_160_1_000)*MainFormSLS->hh[0];
c2.v[20] += (sum_160_1_001)*MainFormSLS->hh[41];
c2.v[20] += (sum_160_1_002)*MainFormSLS->hh[82];
c2.v[20] += (sum_160_1_003)*MainFormSLS->hh[123];
c2.v[20] += (sum_160_1_004)*MainFormSLS->hh[4];
c2.v[20] += (sum_160_1_005)*MainFormSLS->hh[45];
c2.v[20] += (sum_160_1_006)*MainFormSLS->hh[86];
c2.v[20] += (sum_160_1_007)*MainFormSLS->hh[127];
c2.v[20] += (sum_160_1_008)*MainFormSLS->hh[8];
c2.v[20] += (sum_160_1_009)*MainFormSLS->hh[49];
c2.v[20] += (sum_160_1_010)*MainFormSLS->hh[90];
c2.v[20] += (sum_160_1_011)*MainFormSLS->hh[131];
c2.v[20] += (sum_160_1_012)*MainFormSLS->hh[12];
c2.v[20] += (sum_160_1_013)*MainFormSLS->hh[53];
c2.v[20] += (sum_160_1_014)*MainFormSLS->hh[94];
c2.v[20] += (sum_160_1_015)*MainFormSLS->hh[135];
c2.v[20] += (sum_160_1_016)*MainFormSLS->hh[16];
c2.v[20] += (sum_160_1_017)*MainFormSLS->hh[57];
c2.v[20] += (sum_160_1_018)*MainFormSLS->hh[98];
c2.v[20] += (sum_160_1_019)*MainFormSLS->hh[139];
c2.v[20] += (sum_160_1_020)*MainFormSLS->hh[20];
c2.v[20] += (sum_160_1_021)*MainFormSLS->hh[61];
c2.v[20] += (sum_160_1_022)*MainFormSLS->hh[102];
c2.v[20] += (sum_160_1_023)*MainFormSLS->hh[143];
c2.v[20] += (sum_160_1_024)*MainFormSLS->hh[24];
c2.v[20] += (sum_160_1_025)*MainFormSLS->hh[65];
c2.v[20] += (sum_160_1_026)*MainFormSLS->hh[106];
c2.v[20] += (sum_160_1_027)*MainFormSLS->hh[147];
c2.v[20] += (sum_160_1_028)*MainFormSLS->hh[28];
c2.v[20] += (sum_160_1_029)*MainFormSLS->hh[69];
c2.v[20] += (sum_160_1_030)*MainFormSLS->hh[110];
c2.v[20] += (sum_160_1_031)*MainFormSLS->hh[151];
c2.v[20] += (sum_160_1_032)*MainFormSLS->hh[32];
c2.v[20] += (sum_160_1_033)*MainFormSLS->hh[73];
c2.v[20] += (sum_160_1_034)*MainFormSLS->hh[114];
c2.v[20] += (sum_160_1_035)*MainFormSLS->hh[155];
c2.v[20] += (sum_160_1_036)*MainFormSLS->hh[36];
c2.v[20] += (sum_160_1_037)*MainFormSLS->hh[77];
c2.v[20] += (sum_160_1_038)*MainFormSLS->hh[118];
c2.v[20] += (sum_160_1_039)*MainFormSLS->hh[159];
c2.v[20] += (sum_160_1_040)*MainFormSLS->hh[40];
c2.v[20] += (sum_160_1_041)*MainFormSLS->hh[81];
c2.v[20] += (sum_160_1_042)*MainFormSLS->hh[122];
c2.v[20] += (sum_160_1_043)*MainFormSLS->hh[3];
c2.v[20] += (sum_160_1_044)*MainFormSLS->hh[44];
c2.v[20] += (sum_160_1_045)*MainFormSLS->hh[85];
c2.v[20] += (sum_160_1_046)*MainFormSLS->hh[126];
c2.v[20] += (sum_160_1_047)*MainFormSLS->hh[7];
c2.v[20] += (sum_160_1_048)*MainFormSLS->hh[48];
c2.v[20] += (sum_160_1_049)*MainFormSLS->hh[89];
c2.v[20] += (sum_160_1_050)*MainFormSLS->hh[130];
c2.v[20] += (sum_160_1_051)*MainFormSLS->hh[11];
c2.v[20] += (sum_160_1_052)*MainFormSLS->hh[52];
c2.v[20] += (sum_160_1_053)*MainFormSLS->hh[93];
c2.v[20] += (sum_160_1_054)*MainFormSLS->hh[134];
c2.v[20] += (sum_160_1_055)*MainFormSLS->hh[15];
c2.v[20] += (sum_160_1_056)*MainFormSLS->hh[56];
c2.v[20] += (sum_160_1_057)*MainFormSLS->hh[97];
c2.v[20] += (sum_160_1_058)*MainFormSLS->hh[138];
c2.v[20] += (sum_160_1_059)*MainFormSLS->hh[19];
c2.v[20] += (sum_160_1_060)*MainFormSLS->hh[60];
c2.v[20] += (sum_160_1_061)*MainFormSLS->hh[101];
c2.v[20] += (sum_160_1_062)*MainFormSLS->hh[142];
c2.v[20] += (sum_160_1_063)*MainFormSLS->hh[23];
c2.v[20] += (sum_160_1_064)*MainFormSLS->hh[64];
c2.v[20] += (sum_160_1_065)*MainFormSLS->hh[105];
c2.v[20] += (sum_160_1_066)*MainFormSLS->hh[146];
c2.v[20] += (sum_160_1_067)*MainFormSLS->hh[27];
c2.v[20] += (sum_160_1_068)*MainFormSLS->hh[68];
c2.v[20] += (sum_160_1_069)*MainFormSLS->hh[109];
c2.v[20] += (sum_160_1_070)*MainFormSLS->hh[150];
c2.v[20] += (sum_160_1_071)*MainFormSLS->hh[31];
c2.v[20] += (sum_160_1_072)*MainFormSLS->hh[72];
c2.v[20] += (sum_160_1_073)*MainFormSLS->hh[113];
c2.v[20] += (sum_160_1_074)*MainFormSLS->hh[154];
c2.v[20] += (sum_160_1_075)*MainFormSLS->hh[35];
c2.v[20] += (sum_160_1_076)*MainFormSLS->hh[76];
c2.v[20] += (sum_160_1_077)*MainFormSLS->hh[117];
c2.v[20] += (sum_160_1_078)*MainFormSLS->hh[158];
c2.v[20] += (sum_160_1_079)*MainFormSLS->hh[39];
c2.v[20] += (sum_160_1_080)*MainFormSLS->hh[80];
c2.v[20] += (sum_160_1_081)*MainFormSLS->hh[121];
c2.v[20] += (sum_160_1_082)*MainFormSLS->hh[2];
c2.v[20] += (sum_160_1_083)*MainFormSLS->hh[43];
c2.v[20] += (sum_160_1_084)*MainFormSLS->hh[84];
c2.v[20] += (sum_160_1_085)*MainFormSLS->hh[125];
c2.v[20] += (sum_160_1_086)*MainFormSLS->hh[6];
c2.v[20] += (sum_160_1_087)*MainFormSLS->hh[47];
c2.v[20] += (sum_160_1_088)*MainFormSLS->hh[88];
c2.v[20] += (sum_160_1_089)*MainFormSLS->hh[129];
c2.v[20] += (sum_160_1_090)*MainFormSLS->hh[10];
c2.v[20] += (sum_160_1_091)*MainFormSLS->hh[51];
c2.v[20] += (sum_160_1_092)*MainFormSLS->hh[92];
c2.v[20] += (sum_160_1_093)*MainFormSLS->hh[133];
c2.v[20] += (sum_160_1_094)*MainFormSLS->hh[14];
c2.v[20] += (sum_160_1_095)*MainFormSLS->hh[55];
c2.v[20] += (sum_160_1_096)*MainFormSLS->hh[96];
c2.v[20] += (sum_160_1_097)*MainFormSLS->hh[137];
c2.v[20] += (sum_160_1_098)*MainFormSLS->hh[18];
c2.v[20] += (sum_160_1_099)*MainFormSLS->hh[59];
c2.v[20] += (sum_160_1_100)*MainFormSLS->hh[100];
c2.v[20] += (sum_160_1_101)*MainFormSLS->hh[141];
c2.v[20] += (sum_160_1_102)*MainFormSLS->hh[22];
c2.v[20] += (sum_160_1_103)*MainFormSLS->hh[63];
c2.v[20] += (sum_160_1_104)*MainFormSLS->hh[104];
c2.v[20] += (sum_160_1_105)*MainFormSLS->hh[145];
c2.v[20] += (sum_160_1_106)*MainFormSLS->hh[26];
c2.v[20] += (sum_160_1_107)*MainFormSLS->hh[67];
c2.v[20] += (sum_160_1_108)*MainFormSLS->hh[108];
c2.v[20] += (sum_160_1_109)*MainFormSLS->hh[149];
c2.v[20] += (sum_160_1_110)*MainFormSLS->hh[30];
c2.v[20] += (sum_160_1_111)*MainFormSLS->hh[71];
c2.v[20] += (sum_160_1_112)*MainFormSLS->hh[112];
c2.v[20] += (sum_160_1_113)*MainFormSLS->hh[153];
c2.v[20] += (sum_160_1_114)*MainFormSLS->hh[34];
c2.v[20] += (sum_160_1_115)*MainFormSLS->hh[75];
c2.v[20] += (sum_160_1_116)*MainFormSLS->hh[116];
c2.v[20] += (sum_160_1_117)*MainFormSLS->hh[157];
c2.v[20] += (sum_160_1_118)*MainFormSLS->hh[38];
c2.v[20] += (sum_160_1_119)*MainFormSLS->hh[79];
c2.v[20] += (sum_160_1_120)*MainFormSLS->hh[120];
c2.v[20] += (sum_160_1_121)*MainFormSLS->hh[1];
c2.v[20] += (sum_160_1_122)*MainFormSLS->hh[42];
c2.v[20] += (sum_160_1_123)*MainFormSLS->hh[83];
c2.v[20] += (sum_160_1_124)*MainFormSLS->hh[124];
c2.v[20] += (sum_160_1_125)*MainFormSLS->hh[5];
c2.v[20] += (sum_160_1_126)*MainFormSLS->hh[46];
c2.v[20] += (sum_160_1_127)*MainFormSLS->hh[87];
c2.v[20] += (sum_160_1_128)*MainFormSLS->hh[128];
c2.v[20] += (sum_160_1_129)*MainFormSLS->hh[9];
c2.v[20] += (sum_160_1_130)*MainFormSLS->hh[50];
c2.v[20] += (sum_160_1_131)*MainFormSLS->hh[91];
c2.v[20] += (sum_160_1_132)*MainFormSLS->hh[132];
c2.v[20] += (sum_160_1_133)*MainFormSLS->hh[13];
c2.v[20] += (sum_160_1_134)*MainFormSLS->hh[54];
c2.v[20] += (sum_160_1_135)*MainFormSLS->hh[95];
c2.v[20] += (sum_160_1_136)*MainFormSLS->hh[136];
c2.v[20] += (sum_160_1_137)*MainFormSLS->hh[17];
c2.v[20] += (sum_160_1_138)*MainFormSLS->hh[58];
c2.v[20] += (sum_160_1_139)*MainFormSLS->hh[99];
c2.v[20] += (sum_160_1_140)*MainFormSLS->hh[140];
c2.v[20] += (sum_160_1_141)*MainFormSLS->hh[21];
c2.v[20] += (sum_160_1_142)*MainFormSLS->hh[62];
c2.v[20] += (sum_160_1_143)*MainFormSLS->hh[103];
c2.v[20] += (sum_160_1_144)*MainFormSLS->hh[144];
c2.v[20] += (sum_160_1_145)*MainFormSLS->hh[25];
c2.v[20] += (sum_160_1_146)*MainFormSLS->hh[66];
c2.v[20] += (sum_160_1_147)*MainFormSLS->hh[107];
c2.v[20] += (sum_160_1_148)*MainFormSLS->hh[148];
c2.v[20] += (sum_160_1_149)*MainFormSLS->hh[29];
c2.v[20] += (sum_160_1_150)*MainFormSLS->hh[70];
c2.v[20] += (sum_160_1_151)*MainFormSLS->hh[111];
c2.v[20] += (sum_160_1_152)*MainFormSLS->hh[152];
c2.v[20] += (sum_160_1_153)*MainFormSLS->hh[33];
c2.v[20] += (sum_160_1_154)*MainFormSLS->hh[74];
c2.v[20] += (sum_160_1_155)*MainFormSLS->hh[115];
c2.v[20] += (sum_160_1_156)*MainFormSLS->hh[156];
c2.v[20] += (sum_160_1_157)*MainFormSLS->hh[37];
c2.v[20] += (sum_160_1_158)*MainFormSLS->hh[78];
c2.v[20] += (sum_160_1_159)*MainFormSLS->hh[119];

//frequency level id 43
c2.v[21] += (sum_160_1_000)*MainFormSLS->hh[0];
c2.v[21] += (sum_160_1_001)*MainFormSLS->hh[43];
c2.v[21] += (sum_160_1_002)*MainFormSLS->hh[86];
c2.v[21] += (sum_160_1_003)*MainFormSLS->hh[129];
c2.v[21] += (sum_160_1_004)*MainFormSLS->hh[12];
c2.v[21] += (sum_160_1_005)*MainFormSLS->hh[55];
c2.v[21] += (sum_160_1_006)*MainFormSLS->hh[98];
c2.v[21] += (sum_160_1_007)*MainFormSLS->hh[141];
c2.v[21] += (sum_160_1_008)*MainFormSLS->hh[24];
c2.v[21] += (sum_160_1_009)*MainFormSLS->hh[67];
c2.v[21] += (sum_160_1_010)*MainFormSLS->hh[110];
c2.v[21] += (sum_160_1_011)*MainFormSLS->hh[153];
c2.v[21] += (sum_160_1_012)*MainFormSLS->hh[36];
c2.v[21] += (sum_160_1_013)*MainFormSLS->hh[79];
c2.v[21] += (sum_160_1_014)*MainFormSLS->hh[122];
c2.v[21] += (sum_160_1_015)*MainFormSLS->hh[5];
c2.v[21] += (sum_160_1_016)*MainFormSLS->hh[48];
c2.v[21] += (sum_160_1_017)*MainFormSLS->hh[91];
c2.v[21] += (sum_160_1_018)*MainFormSLS->hh[134];
c2.v[21] += (sum_160_1_019)*MainFormSLS->hh[17];
c2.v[21] += (sum_160_1_020)*MainFormSLS->hh[60];
c2.v[21] += (sum_160_1_021)*MainFormSLS->hh[103];
c2.v[21] += (sum_160_1_022)*MainFormSLS->hh[146];
c2.v[21] += (sum_160_1_023)*MainFormSLS->hh[29];
c2.v[21] += (sum_160_1_024)*MainFormSLS->hh[72];
c2.v[21] += (sum_160_1_025)*MainFormSLS->hh[115];
c2.v[21] += (sum_160_1_026)*MainFormSLS->hh[158];
c2.v[21] += (sum_160_1_027)*MainFormSLS->hh[41];
c2.v[21] += (sum_160_1_028)*MainFormSLS->hh[84];
c2.v[21] += (sum_160_1_029)*MainFormSLS->hh[127];
c2.v[21] += (sum_160_1_030)*MainFormSLS->hh[10];
c2.v[21] += (sum_160_1_031)*MainFormSLS->hh[53];
c2.v[21] += (sum_160_1_032)*MainFormSLS->hh[96];
c2.v[21] += (sum_160_1_033)*MainFormSLS->hh[139];
c2.v[21] += (sum_160_1_034)*MainFormSLS->hh[22];
c2.v[21] += (sum_160_1_035)*MainFormSLS->hh[65];
c2.v[21] += (sum_160_1_036)*MainFormSLS->hh[108];
c2.v[21] += (sum_160_1_037)*MainFormSLS->hh[151];
c2.v[21] += (sum_160_1_038)*MainFormSLS->hh[34];
c2.v[21] += (sum_160_1_039)*MainFormSLS->hh[77];
c2.v[21] += (sum_160_1_040)*MainFormSLS->hh[120];
c2.v[21] += (sum_160_1_041)*MainFormSLS->hh[3];
c2.v[21] += (sum_160_1_042)*MainFormSLS->hh[46];
c2.v[21] += (sum_160_1_043)*MainFormSLS->hh[89];
c2.v[21] += (sum_160_1_044)*MainFormSLS->hh[132];
c2.v[21] += (sum_160_1_045)*MainFormSLS->hh[15];
c2.v[21] += (sum_160_1_046)*MainFormSLS->hh[58];
c2.v[21] += (sum_160_1_047)*MainFormSLS->hh[101];
c2.v[21] += (sum_160_1_048)*MainFormSLS->hh[144];
c2.v[21] += (sum_160_1_049)*MainFormSLS->hh[27];
c2.v[21] += (sum_160_1_050)*MainFormSLS->hh[70];
c2.v[21] += (sum_160_1_051)*MainFormSLS->hh[113];
c2.v[21] += (sum_160_1_052)*MainFormSLS->hh[156];
c2.v[21] += (sum_160_1_053)*MainFormSLS->hh[39];
c2.v[21] += (sum_160_1_054)*MainFormSLS->hh[82];
c2.v[21] += (sum_160_1_055)*MainFormSLS->hh[125];
c2.v[21] += (sum_160_1_056)*MainFormSLS->hh[8];
c2.v[21] += (sum_160_1_057)*MainFormSLS->hh[51];
c2.v[21] += (sum_160_1_058)*MainFormSLS->hh[94];
c2.v[21] += (sum_160_1_059)*MainFormSLS->hh[137];
c2.v[21] += (sum_160_1_060)*MainFormSLS->hh[20];
c2.v[21] += (sum_160_1_061)*MainFormSLS->hh[63];
c2.v[21] += (sum_160_1_062)*MainFormSLS->hh[106];
c2.v[21] += (sum_160_1_063)*MainFormSLS->hh[149];
c2.v[21] += (sum_160_1_064)*MainFormSLS->hh[32];
c2.v[21] += (sum_160_1_065)*MainFormSLS->hh[75];
c2.v[21] += (sum_160_1_066)*MainFormSLS->hh[118];
c2.v[21] += (sum_160_1_067)*MainFormSLS->hh[1];
c2.v[21] += (sum_160_1_068)*MainFormSLS->hh[44];
c2.v[21] += (sum_160_1_069)*MainFormSLS->hh[87];
c2.v[21] += (sum_160_1_070)*MainFormSLS->hh[130];
c2.v[21] += (sum_160_1_071)*MainFormSLS->hh[13];
c2.v[21] += (sum_160_1_072)*MainFormSLS->hh[56];
c2.v[21] += (sum_160_1_073)*MainFormSLS->hh[99];
c2.v[21] += (sum_160_1_074)*MainFormSLS->hh[142];
c2.v[21] += (sum_160_1_075)*MainFormSLS->hh[25];
c2.v[21] += (sum_160_1_076)*MainFormSLS->hh[68];
c2.v[21] += (sum_160_1_077)*MainFormSLS->hh[111];
c2.v[21] += (sum_160_1_078)*MainFormSLS->hh[154];
c2.v[21] += (sum_160_1_079)*MainFormSLS->hh[37];
c2.v[21] += (sum_160_1_080)*MainFormSLS->hh[80];
c2.v[21] += (sum_160_1_081)*MainFormSLS->hh[123];
c2.v[21] += (sum_160_1_082)*MainFormSLS->hh[6];
c2.v[21] += (sum_160_1_083)*MainFormSLS->hh[49];
c2.v[21] += (sum_160_1_084)*MainFormSLS->hh[92];
c2.v[21] += (sum_160_1_085)*MainFormSLS->hh[135];
c2.v[21] += (sum_160_1_086)*MainFormSLS->hh[18];
c2.v[21] += (sum_160_1_087)*MainFormSLS->hh[61];
c2.v[21] += (sum_160_1_088)*MainFormSLS->hh[104];
c2.v[21] += (sum_160_1_089)*MainFormSLS->hh[147];
c2.v[21] += (sum_160_1_090)*MainFormSLS->hh[30];
c2.v[21] += (sum_160_1_091)*MainFormSLS->hh[73];
c2.v[21] += (sum_160_1_092)*MainFormSLS->hh[116];
c2.v[21] += (sum_160_1_093)*MainFormSLS->hh[159];
c2.v[21] += (sum_160_1_094)*MainFormSLS->hh[42];
c2.v[21] += (sum_160_1_095)*MainFormSLS->hh[85];
c2.v[21] += (sum_160_1_096)*MainFormSLS->hh[128];
c2.v[21] += (sum_160_1_097)*MainFormSLS->hh[11];
c2.v[21] += (sum_160_1_098)*MainFormSLS->hh[54];
c2.v[21] += (sum_160_1_099)*MainFormSLS->hh[97];
c2.v[21] += (sum_160_1_100)*MainFormSLS->hh[140];
c2.v[21] += (sum_160_1_101)*MainFormSLS->hh[23];
c2.v[21] += (sum_160_1_102)*MainFormSLS->hh[66];
c2.v[21] += (sum_160_1_103)*MainFormSLS->hh[109];
c2.v[21] += (sum_160_1_104)*MainFormSLS->hh[152];
c2.v[21] += (sum_160_1_105)*MainFormSLS->hh[35];
c2.v[21] += (sum_160_1_106)*MainFormSLS->hh[78];
c2.v[21] += (sum_160_1_107)*MainFormSLS->hh[121];
c2.v[21] += (sum_160_1_108)*MainFormSLS->hh[4];
c2.v[21] += (sum_160_1_109)*MainFormSLS->hh[47];
c2.v[21] += (sum_160_1_110)*MainFormSLS->hh[90];
c2.v[21] += (sum_160_1_111)*MainFormSLS->hh[133];
c2.v[21] += (sum_160_1_112)*MainFormSLS->hh[16];
c2.v[21] += (sum_160_1_113)*MainFormSLS->hh[59];
c2.v[21] += (sum_160_1_114)*MainFormSLS->hh[102];
c2.v[21] += (sum_160_1_115)*MainFormSLS->hh[145];
c2.v[21] += (sum_160_1_116)*MainFormSLS->hh[28];
c2.v[21] += (sum_160_1_117)*MainFormSLS->hh[71];
c2.v[21] += (sum_160_1_118)*MainFormSLS->hh[114];
c2.v[21] += (sum_160_1_119)*MainFormSLS->hh[157];
c2.v[21] += (sum_160_1_120)*MainFormSLS->hh[40];
c2.v[21] += (sum_160_1_121)*MainFormSLS->hh[83];
c2.v[21] += (sum_160_1_122)*MainFormSLS->hh[126];
c2.v[21] += (sum_160_1_123)*MainFormSLS->hh[9];
c2.v[21] += (sum_160_1_124)*MainFormSLS->hh[52];
c2.v[21] += (sum_160_1_125)*MainFormSLS->hh[95];
c2.v[21] += (sum_160_1_126)*MainFormSLS->hh[138];
c2.v[21] += (sum_160_1_127)*MainFormSLS->hh[21];
c2.v[21] += (sum_160_1_128)*MainFormSLS->hh[64];
c2.v[21] += (sum_160_1_129)*MainFormSLS->hh[107];
c2.v[21] += (sum_160_1_130)*MainFormSLS->hh[150];
c2.v[21] += (sum_160_1_131)*MainFormSLS->hh[33];
c2.v[21] += (sum_160_1_132)*MainFormSLS->hh[76];
c2.v[21] += (sum_160_1_133)*MainFormSLS->hh[119];
c2.v[21] += (sum_160_1_134)*MainFormSLS->hh[2];
c2.v[21] += (sum_160_1_135)*MainFormSLS->hh[45];
c2.v[21] += (sum_160_1_136)*MainFormSLS->hh[88];
c2.v[21] += (sum_160_1_137)*MainFormSLS->hh[131];
c2.v[21] += (sum_160_1_138)*MainFormSLS->hh[14];
c2.v[21] += (sum_160_1_139)*MainFormSLS->hh[57];
c2.v[21] += (sum_160_1_140)*MainFormSLS->hh[100];
c2.v[21] += (sum_160_1_141)*MainFormSLS->hh[143];
c2.v[21] += (sum_160_1_142)*MainFormSLS->hh[26];
c2.v[21] += (sum_160_1_143)*MainFormSLS->hh[69];
c2.v[21] += (sum_160_1_144)*MainFormSLS->hh[112];
c2.v[21] += (sum_160_1_145)*MainFormSLS->hh[155];
c2.v[21] += (sum_160_1_146)*MainFormSLS->hh[38];
c2.v[21] += (sum_160_1_147)*MainFormSLS->hh[81];
c2.v[21] += (sum_160_1_148)*MainFormSLS->hh[124];
c2.v[21] += (sum_160_1_149)*MainFormSLS->hh[7];
c2.v[21] += (sum_160_1_150)*MainFormSLS->hh[50];
c2.v[21] += (sum_160_1_151)*MainFormSLS->hh[93];
c2.v[21] += (sum_160_1_152)*MainFormSLS->hh[136];
c2.v[21] += (sum_160_1_153)*MainFormSLS->hh[19];
c2.v[21] += (sum_160_1_154)*MainFormSLS->hh[62];
c2.v[21] += (sum_160_1_155)*MainFormSLS->hh[105];
c2.v[21] += (sum_160_1_156)*MainFormSLS->hh[148];
c2.v[21] += (sum_160_1_157)*MainFormSLS->hh[31];
c2.v[21] += (sum_160_1_158)*MainFormSLS->hh[74];
c2.v[21] += (sum_160_1_159)*MainFormSLS->hh[117];

//frequency level id 45
c2.v[22] += (sum_32_5_000)*MainFormSLS->hh[0];
c2.v[22] += (sum_32_5_001)*MainFormSLS->hh[45];
c2.v[22] += (sum_32_5_002)*MainFormSLS->hh[90];
c2.v[22] += (sum_32_5_003)*MainFormSLS->hh[135];
c2.v[22] += (sum_32_5_004)*MainFormSLS->hh[20];
c2.v[22] += (sum_32_5_005)*MainFormSLS->hh[65];
c2.v[22] += (sum_32_5_006)*MainFormSLS->hh[110];
c2.v[22] += (sum_32_5_007)*MainFormSLS->hh[155];
c2.v[22] += (sum_32_5_008)*MainFormSLS->hh[40];
c2.v[22] += (sum_32_5_009)*MainFormSLS->hh[85];
c2.v[22] += (sum_32_5_010)*MainFormSLS->hh[130];
c2.v[22] += (sum_32_5_011)*MainFormSLS->hh[15];
c2.v[22] += (sum_32_5_012)*MainFormSLS->hh[60];
c2.v[22] += (sum_32_5_013)*MainFormSLS->hh[105];
c2.v[22] += (sum_32_5_014)*MainFormSLS->hh[150];
c2.v[22] += (sum_32_5_015)*MainFormSLS->hh[35];
c2.v[22] += (sum_32_5_016)*MainFormSLS->hh[80];
c2.v[22] += (sum_32_5_017)*MainFormSLS->hh[125];
c2.v[22] += (sum_32_5_018)*MainFormSLS->hh[10];
c2.v[22] += (sum_32_5_019)*MainFormSLS->hh[55];
c2.v[22] += (sum_32_5_020)*MainFormSLS->hh[100];
c2.v[22] += (sum_32_5_021)*MainFormSLS->hh[145];
c2.v[22] += (sum_32_5_022)*MainFormSLS->hh[30];
c2.v[22] += (sum_32_5_023)*MainFormSLS->hh[75];
c2.v[22] += (sum_32_5_024)*MainFormSLS->hh[120];
c2.v[22] += (sum_32_5_025)*MainFormSLS->hh[5];
c2.v[22] += (sum_32_5_026)*MainFormSLS->hh[50];
c2.v[22] += (sum_32_5_027)*MainFormSLS->hh[95];
c2.v[22] += (sum_32_5_028)*MainFormSLS->hh[140];
c2.v[22] += (sum_32_5_029)*MainFormSLS->hh[25];
c2.v[22] += (sum_32_5_030)*MainFormSLS->hh[70];
c2.v[22] += (sum_32_5_031)*MainFormSLS->hh[115];

//frequency level id 47
c2.v[23] += (sum_160_1_000)*MainFormSLS->hh[0];
c2.v[23] += (sum_160_1_001)*MainFormSLS->hh[47];
c2.v[23] += (sum_160_1_002)*MainFormSLS->hh[94];
c2.v[23] += (sum_160_1_003)*MainFormSLS->hh[141];
c2.v[23] += (sum_160_1_004)*MainFormSLS->hh[28];
c2.v[23] += (sum_160_1_005)*MainFormSLS->hh[75];
c2.v[23] += (sum_160_1_006)*MainFormSLS->hh[122];
c2.v[23] += (sum_160_1_007)*MainFormSLS->hh[9];
c2.v[23] += (sum_160_1_008)*MainFormSLS->hh[56];
c2.v[23] += (sum_160_1_009)*MainFormSLS->hh[103];
c2.v[23] += (sum_160_1_010)*MainFormSLS->hh[150];
c2.v[23] += (sum_160_1_011)*MainFormSLS->hh[37];
c2.v[23] += (sum_160_1_012)*MainFormSLS->hh[84];
c2.v[23] += (sum_160_1_013)*MainFormSLS->hh[131];
c2.v[23] += (sum_160_1_014)*MainFormSLS->hh[18];
c2.v[23] += (sum_160_1_015)*MainFormSLS->hh[65];
c2.v[23] += (sum_160_1_016)*MainFormSLS->hh[112];
c2.v[23] += (sum_160_1_017)*MainFormSLS->hh[159];
c2.v[23] += (sum_160_1_018)*MainFormSLS->hh[46];
c2.v[23] += (sum_160_1_019)*MainFormSLS->hh[93];
c2.v[23] += (sum_160_1_020)*MainFormSLS->hh[140];
c2.v[23] += (sum_160_1_021)*MainFormSLS->hh[27];
c2.v[23] += (sum_160_1_022)*MainFormSLS->hh[74];
c2.v[23] += (sum_160_1_023)*MainFormSLS->hh[121];
c2.v[23] += (sum_160_1_024)*MainFormSLS->hh[8];
c2.v[23] += (sum_160_1_025)*MainFormSLS->hh[55];
c2.v[23] += (sum_160_1_026)*MainFormSLS->hh[102];
c2.v[23] += (sum_160_1_027)*MainFormSLS->hh[149];
c2.v[23] += (sum_160_1_028)*MainFormSLS->hh[36];
c2.v[23] += (sum_160_1_029)*MainFormSLS->hh[83];
c2.v[23] += (sum_160_1_030)*MainFormSLS->hh[130];
c2.v[23] += (sum_160_1_031)*MainFormSLS->hh[17];
c2.v[23] += (sum_160_1_032)*MainFormSLS->hh[64];
c2.v[23] += (sum_160_1_033)*MainFormSLS->hh[111];
c2.v[23] += (sum_160_1_034)*MainFormSLS->hh[158];
c2.v[23] += (sum_160_1_035)*MainFormSLS->hh[45];
c2.v[23] += (sum_160_1_036)*MainFormSLS->hh[92];
c2.v[23] += (sum_160_1_037)*MainFormSLS->hh[139];
c2.v[23] += (sum_160_1_038)*MainFormSLS->hh[26];
c2.v[23] += (sum_160_1_039)*MainFormSLS->hh[73];
c2.v[23] += (sum_160_1_040)*MainFormSLS->hh[120];
c2.v[23] += (sum_160_1_041)*MainFormSLS->hh[7];
c2.v[23] += (sum_160_1_042)*MainFormSLS->hh[54];
c2.v[23] += (sum_160_1_043)*MainFormSLS->hh[101];
c2.v[23] += (sum_160_1_044)*MainFormSLS->hh[148];
c2.v[23] += (sum_160_1_045)*MainFormSLS->hh[35];
c2.v[23] += (sum_160_1_046)*MainFormSLS->hh[82];
c2.v[23] += (sum_160_1_047)*MainFormSLS->hh[129];
c2.v[23] += (sum_160_1_048)*MainFormSLS->hh[16];
c2.v[23] += (sum_160_1_049)*MainFormSLS->hh[63];
c2.v[23] += (sum_160_1_050)*MainFormSLS->hh[110];
c2.v[23] += (sum_160_1_051)*MainFormSLS->hh[157];
c2.v[23] += (sum_160_1_052)*MainFormSLS->hh[44];
c2.v[23] += (sum_160_1_053)*MainFormSLS->hh[91];
c2.v[23] += (sum_160_1_054)*MainFormSLS->hh[138];
c2.v[23] += (sum_160_1_055)*MainFormSLS->hh[25];
c2.v[23] += (sum_160_1_056)*MainFormSLS->hh[72];
c2.v[23] += (sum_160_1_057)*MainFormSLS->hh[119];
c2.v[23] += (sum_160_1_058)*MainFormSLS->hh[6];
c2.v[23] += (sum_160_1_059)*MainFormSLS->hh[53];
c2.v[23] += (sum_160_1_060)*MainFormSLS->hh[100];
c2.v[23] += (sum_160_1_061)*MainFormSLS->hh[147];
c2.v[23] += (sum_160_1_062)*MainFormSLS->hh[34];
c2.v[23] += (sum_160_1_063)*MainFormSLS->hh[81];
c2.v[23] += (sum_160_1_064)*MainFormSLS->hh[128];
c2.v[23] += (sum_160_1_065)*MainFormSLS->hh[15];
c2.v[23] += (sum_160_1_066)*MainFormSLS->hh[62];
c2.v[23] += (sum_160_1_067)*MainFormSLS->hh[109];
c2.v[23] += (sum_160_1_068)*MainFormSLS->hh[156];
c2.v[23] += (sum_160_1_069)*MainFormSLS->hh[43];
c2.v[23] += (sum_160_1_070)*MainFormSLS->hh[90];
c2.v[23] += (sum_160_1_071)*MainFormSLS->hh[137];
c2.v[23] += (sum_160_1_072)*MainFormSLS->hh[24];
c2.v[23] += (sum_160_1_073)*MainFormSLS->hh[71];
c2.v[23] += (sum_160_1_074)*MainFormSLS->hh[118];
c2.v[23] += (sum_160_1_075)*MainFormSLS->hh[5];
c2.v[23] += (sum_160_1_076)*MainFormSLS->hh[52];
c2.v[23] += (sum_160_1_077)*MainFormSLS->hh[99];
c2.v[23] += (sum_160_1_078)*MainFormSLS->hh[146];
c2.v[23] += (sum_160_1_079)*MainFormSLS->hh[33];
c2.v[23] += (sum_160_1_080)*MainFormSLS->hh[80];
c2.v[23] += (sum_160_1_081)*MainFormSLS->hh[127];
c2.v[23] += (sum_160_1_082)*MainFormSLS->hh[14];
c2.v[23] += (sum_160_1_083)*MainFormSLS->hh[61];
c2.v[23] += (sum_160_1_084)*MainFormSLS->hh[108];
c2.v[23] += (sum_160_1_085)*MainFormSLS->hh[155];
c2.v[23] += (sum_160_1_086)*MainFormSLS->hh[42];
c2.v[23] += (sum_160_1_087)*MainFormSLS->hh[89];
c2.v[23] += (sum_160_1_088)*MainFormSLS->hh[136];
c2.v[23] += (sum_160_1_089)*MainFormSLS->hh[23];
c2.v[23] += (sum_160_1_090)*MainFormSLS->hh[70];
c2.v[23] += (sum_160_1_091)*MainFormSLS->hh[117];
c2.v[23] += (sum_160_1_092)*MainFormSLS->hh[4];
c2.v[23] += (sum_160_1_093)*MainFormSLS->hh[51];
c2.v[23] += (sum_160_1_094)*MainFormSLS->hh[98];
c2.v[23] += (sum_160_1_095)*MainFormSLS->hh[145];
c2.v[23] += (sum_160_1_096)*MainFormSLS->hh[32];
c2.v[23] += (sum_160_1_097)*MainFormSLS->hh[79];
c2.v[23] += (sum_160_1_098)*MainFormSLS->hh[126];
c2.v[23] += (sum_160_1_099)*MainFormSLS->hh[13];
c2.v[23] += (sum_160_1_100)*MainFormSLS->hh[60];
c2.v[23] += (sum_160_1_101)*MainFormSLS->hh[107];
c2.v[23] += (sum_160_1_102)*MainFormSLS->hh[154];
c2.v[23] += (sum_160_1_103)*MainFormSLS->hh[41];
c2.v[23] += (sum_160_1_104)*MainFormSLS->hh[88];
c2.v[23] += (sum_160_1_105)*MainFormSLS->hh[135];
c2.v[23] += (sum_160_1_106)*MainFormSLS->hh[22];
c2.v[23] += (sum_160_1_107)*MainFormSLS->hh[69];
c2.v[23] += (sum_160_1_108)*MainFormSLS->hh[116];
c2.v[23] += (sum_160_1_109)*MainFormSLS->hh[3];
c2.v[23] += (sum_160_1_110)*MainFormSLS->hh[50];
c2.v[23] += (sum_160_1_111)*MainFormSLS->hh[97];
c2.v[23] += (sum_160_1_112)*MainFormSLS->hh[144];
c2.v[23] += (sum_160_1_113)*MainFormSLS->hh[31];
c2.v[23] += (sum_160_1_114)*MainFormSLS->hh[78];
c2.v[23] += (sum_160_1_115)*MainFormSLS->hh[125];
c2.v[23] += (sum_160_1_116)*MainFormSLS->hh[12];
c2.v[23] += (sum_160_1_117)*MainFormSLS->hh[59];
c2.v[23] += (sum_160_1_118)*MainFormSLS->hh[106];
c2.v[23] += (sum_160_1_119)*MainFormSLS->hh[153];
c2.v[23] += (sum_160_1_120)*MainFormSLS->hh[40];
c2.v[23] += (sum_160_1_121)*MainFormSLS->hh[87];
c2.v[23] += (sum_160_1_122)*MainFormSLS->hh[134];
c2.v[23] += (sum_160_1_123)*MainFormSLS->hh[21];
c2.v[23] += (sum_160_1_124)*MainFormSLS->hh[68];
c2.v[23] += (sum_160_1_125)*MainFormSLS->hh[115];
c2.v[23] += (sum_160_1_126)*MainFormSLS->hh[2];
c2.v[23] += (sum_160_1_127)*MainFormSLS->hh[49];
c2.v[23] += (sum_160_1_128)*MainFormSLS->hh[96];
c2.v[23] += (sum_160_1_129)*MainFormSLS->hh[143];
c2.v[23] += (sum_160_1_130)*MainFormSLS->hh[30];
c2.v[23] += (sum_160_1_131)*MainFormSLS->hh[77];
c2.v[23] += (sum_160_1_132)*MainFormSLS->hh[124];
c2.v[23] += (sum_160_1_133)*MainFormSLS->hh[11];
c2.v[23] += (sum_160_1_134)*MainFormSLS->hh[58];
c2.v[23] += (sum_160_1_135)*MainFormSLS->hh[105];
c2.v[23] += (sum_160_1_136)*MainFormSLS->hh[152];
c2.v[23] += (sum_160_1_137)*MainFormSLS->hh[39];
c2.v[23] += (sum_160_1_138)*MainFormSLS->hh[86];
c2.v[23] += (sum_160_1_139)*MainFormSLS->hh[133];
c2.v[23] += (sum_160_1_140)*MainFormSLS->hh[20];
c2.v[23] += (sum_160_1_141)*MainFormSLS->hh[67];
c2.v[23] += (sum_160_1_142)*MainFormSLS->hh[114];
c2.v[23] += (sum_160_1_143)*MainFormSLS->hh[1];
c2.v[23] += (sum_160_1_144)*MainFormSLS->hh[48];
c2.v[23] += (sum_160_1_145)*MainFormSLS->hh[95];
c2.v[23] += (sum_160_1_146)*MainFormSLS->hh[142];
c2.v[23] += (sum_160_1_147)*MainFormSLS->hh[29];
c2.v[23] += (sum_160_1_148)*MainFormSLS->hh[76];
c2.v[23] += (sum_160_1_149)*MainFormSLS->hh[123];
c2.v[23] += (sum_160_1_150)*MainFormSLS->hh[10];
c2.v[23] += (sum_160_1_151)*MainFormSLS->hh[57];
c2.v[23] += (sum_160_1_152)*MainFormSLS->hh[104];
c2.v[23] += (sum_160_1_153)*MainFormSLS->hh[151];
c2.v[23] += (sum_160_1_154)*MainFormSLS->hh[38];
c2.v[23] += (sum_160_1_155)*MainFormSLS->hh[85];
c2.v[23] += (sum_160_1_156)*MainFormSLS->hh[132];
c2.v[23] += (sum_160_1_157)*MainFormSLS->hh[19];
c2.v[23] += (sum_160_1_158)*MainFormSLS->hh[66];
c2.v[23] += (sum_160_1_159)*MainFormSLS->hh[113];

//frequency level id 49
c2.v[24] += (sum_160_1_000)*MainFormSLS->hh[0];
c2.v[24] += (sum_160_1_001)*MainFormSLS->hh[49];
c2.v[24] += (sum_160_1_002)*MainFormSLS->hh[98];
c2.v[24] += (sum_160_1_003)*MainFormSLS->hh[147];
c2.v[24] += (sum_160_1_004)*MainFormSLS->hh[36];
c2.v[24] += (sum_160_1_005)*MainFormSLS->hh[85];
c2.v[24] += (sum_160_1_006)*MainFormSLS->hh[134];
c2.v[24] += (sum_160_1_007)*MainFormSLS->hh[23];
c2.v[24] += (sum_160_1_008)*MainFormSLS->hh[72];
c2.v[24] += (sum_160_1_009)*MainFormSLS->hh[121];
c2.v[24] += (sum_160_1_010)*MainFormSLS->hh[10];
c2.v[24] += (sum_160_1_011)*MainFormSLS->hh[59];
c2.v[24] += (sum_160_1_012)*MainFormSLS->hh[108];
c2.v[24] += (sum_160_1_013)*MainFormSLS->hh[157];
c2.v[24] += (sum_160_1_014)*MainFormSLS->hh[46];
c2.v[24] += (sum_160_1_015)*MainFormSLS->hh[95];
c2.v[24] += (sum_160_1_016)*MainFormSLS->hh[144];
c2.v[24] += (sum_160_1_017)*MainFormSLS->hh[33];
c2.v[24] += (sum_160_1_018)*MainFormSLS->hh[82];
c2.v[24] += (sum_160_1_019)*MainFormSLS->hh[131];
c2.v[24] += (sum_160_1_020)*MainFormSLS->hh[20];
c2.v[24] += (sum_160_1_021)*MainFormSLS->hh[69];
c2.v[24] += (sum_160_1_022)*MainFormSLS->hh[118];
c2.v[24] += (sum_160_1_023)*MainFormSLS->hh[7];
c2.v[24] += (sum_160_1_024)*MainFormSLS->hh[56];
c2.v[24] += (sum_160_1_025)*MainFormSLS->hh[105];
c2.v[24] += (sum_160_1_026)*MainFormSLS->hh[154];
c2.v[24] += (sum_160_1_027)*MainFormSLS->hh[43];
c2.v[24] += (sum_160_1_028)*MainFormSLS->hh[92];
c2.v[24] += (sum_160_1_029)*MainFormSLS->hh[141];
c2.v[24] += (sum_160_1_030)*MainFormSLS->hh[30];
c2.v[24] += (sum_160_1_031)*MainFormSLS->hh[79];
c2.v[24] += (sum_160_1_032)*MainFormSLS->hh[128];
c2.v[24] += (sum_160_1_033)*MainFormSLS->hh[17];
c2.v[24] += (sum_160_1_034)*MainFormSLS->hh[66];
c2.v[24] += (sum_160_1_035)*MainFormSLS->hh[115];
c2.v[24] += (sum_160_1_036)*MainFormSLS->hh[4];
c2.v[24] += (sum_160_1_037)*MainFormSLS->hh[53];
c2.v[24] += (sum_160_1_038)*MainFormSLS->hh[102];
c2.v[24] += (sum_160_1_039)*MainFormSLS->hh[151];
c2.v[24] += (sum_160_1_040)*MainFormSLS->hh[40];
c2.v[24] += (sum_160_1_041)*MainFormSLS->hh[89];
c2.v[24] += (sum_160_1_042)*MainFormSLS->hh[138];
c2.v[24] += (sum_160_1_043)*MainFormSLS->hh[27];
c2.v[24] += (sum_160_1_044)*MainFormSLS->hh[76];
c2.v[24] += (sum_160_1_045)*MainFormSLS->hh[125];
c2.v[24] += (sum_160_1_046)*MainFormSLS->hh[14];
c2.v[24] += (sum_160_1_047)*MainFormSLS->hh[63];
c2.v[24] += (sum_160_1_048)*MainFormSLS->hh[112];
c2.v[24] += (sum_160_1_049)*MainFormSLS->hh[1];
c2.v[24] += (sum_160_1_050)*MainFormSLS->hh[50];
c2.v[24] += (sum_160_1_051)*MainFormSLS->hh[99];
c2.v[24] += (sum_160_1_052)*MainFormSLS->hh[148];
c2.v[24] += (sum_160_1_053)*MainFormSLS->hh[37];
c2.v[24] += (sum_160_1_054)*MainFormSLS->hh[86];
c2.v[24] += (sum_160_1_055)*MainFormSLS->hh[135];
c2.v[24] += (sum_160_1_056)*MainFormSLS->hh[24];
c2.v[24] += (sum_160_1_057)*MainFormSLS->hh[73];
c2.v[24] += (sum_160_1_058)*MainFormSLS->hh[122];
c2.v[24] += (sum_160_1_059)*MainFormSLS->hh[11];
c2.v[24] += (sum_160_1_060)*MainFormSLS->hh[60];
c2.v[24] += (sum_160_1_061)*MainFormSLS->hh[109];
c2.v[24] += (sum_160_1_062)*MainFormSLS->hh[158];
c2.v[24] += (sum_160_1_063)*MainFormSLS->hh[47];
c2.v[24] += (sum_160_1_064)*MainFormSLS->hh[96];
c2.v[24] += (sum_160_1_065)*MainFormSLS->hh[145];
c2.v[24] += (sum_160_1_066)*MainFormSLS->hh[34];
c2.v[24] += (sum_160_1_067)*MainFormSLS->hh[83];
c2.v[24] += (sum_160_1_068)*MainFormSLS->hh[132];
c2.v[24] += (sum_160_1_069)*MainFormSLS->hh[21];
c2.v[24] += (sum_160_1_070)*MainFormSLS->hh[70];
c2.v[24] += (sum_160_1_071)*MainFormSLS->hh[119];
c2.v[24] += (sum_160_1_072)*MainFormSLS->hh[8];
c2.v[24] += (sum_160_1_073)*MainFormSLS->hh[57];
c2.v[24] += (sum_160_1_074)*MainFormSLS->hh[106];
c2.v[24] += (sum_160_1_075)*MainFormSLS->hh[155];
c2.v[24] += (sum_160_1_076)*MainFormSLS->hh[44];
c2.v[24] += (sum_160_1_077)*MainFormSLS->hh[93];
c2.v[24] += (sum_160_1_078)*MainFormSLS->hh[142];
c2.v[24] += (sum_160_1_079)*MainFormSLS->hh[31];
c2.v[24] += (sum_160_1_080)*MainFormSLS->hh[80];
c2.v[24] += (sum_160_1_081)*MainFormSLS->hh[129];
c2.v[24] += (sum_160_1_082)*MainFormSLS->hh[18];
c2.v[24] += (sum_160_1_083)*MainFormSLS->hh[67];
c2.v[24] += (sum_160_1_084)*MainFormSLS->hh[116];
c2.v[24] += (sum_160_1_085)*MainFormSLS->hh[5];
c2.v[24] += (sum_160_1_086)*MainFormSLS->hh[54];
c2.v[24] += (sum_160_1_087)*MainFormSLS->hh[103];
c2.v[24] += (sum_160_1_088)*MainFormSLS->hh[152];
c2.v[24] += (sum_160_1_089)*MainFormSLS->hh[41];
c2.v[24] += (sum_160_1_090)*MainFormSLS->hh[90];
c2.v[24] += (sum_160_1_091)*MainFormSLS->hh[139];
c2.v[24] += (sum_160_1_092)*MainFormSLS->hh[28];
c2.v[24] += (sum_160_1_093)*MainFormSLS->hh[77];
c2.v[24] += (sum_160_1_094)*MainFormSLS->hh[126];
c2.v[24] += (sum_160_1_095)*MainFormSLS->hh[15];
c2.v[24] += (sum_160_1_096)*MainFormSLS->hh[64];
c2.v[24] += (sum_160_1_097)*MainFormSLS->hh[113];
c2.v[24] += (sum_160_1_098)*MainFormSLS->hh[2];
c2.v[24] += (sum_160_1_099)*MainFormSLS->hh[51];
c2.v[24] += (sum_160_1_100)*MainFormSLS->hh[100];
c2.v[24] += (sum_160_1_101)*MainFormSLS->hh[149];
c2.v[24] += (sum_160_1_102)*MainFormSLS->hh[38];
c2.v[24] += (sum_160_1_103)*MainFormSLS->hh[87];
c2.v[24] += (sum_160_1_104)*MainFormSLS->hh[136];
c2.v[24] += (sum_160_1_105)*MainFormSLS->hh[25];
c2.v[24] += (sum_160_1_106)*MainFormSLS->hh[74];
c2.v[24] += (sum_160_1_107)*MainFormSLS->hh[123];
c2.v[24] += (sum_160_1_108)*MainFormSLS->hh[12];
c2.v[24] += (sum_160_1_109)*MainFormSLS->hh[61];
c2.v[24] += (sum_160_1_110)*MainFormSLS->hh[110];
c2.v[24] += (sum_160_1_111)*MainFormSLS->hh[159];
c2.v[24] += (sum_160_1_112)*MainFormSLS->hh[48];
c2.v[24] += (sum_160_1_113)*MainFormSLS->hh[97];
c2.v[24] += (sum_160_1_114)*MainFormSLS->hh[146];
c2.v[24] += (sum_160_1_115)*MainFormSLS->hh[35];
c2.v[24] += (sum_160_1_116)*MainFormSLS->hh[84];
c2.v[24] += (sum_160_1_117)*MainFormSLS->hh[133];
c2.v[24] += (sum_160_1_118)*MainFormSLS->hh[22];
c2.v[24] += (sum_160_1_119)*MainFormSLS->hh[71];
c2.v[24] += (sum_160_1_120)*MainFormSLS->hh[120];
c2.v[24] += (sum_160_1_121)*MainFormSLS->hh[9];
c2.v[24] += (sum_160_1_122)*MainFormSLS->hh[58];
c2.v[24] += (sum_160_1_123)*MainFormSLS->hh[107];
c2.v[24] += (sum_160_1_124)*MainFormSLS->hh[156];
c2.v[24] += (sum_160_1_125)*MainFormSLS->hh[45];
c2.v[24] += (sum_160_1_126)*MainFormSLS->hh[94];
c2.v[24] += (sum_160_1_127)*MainFormSLS->hh[143];
c2.v[24] += (sum_160_1_128)*MainFormSLS->hh[32];
c2.v[24] += (sum_160_1_129)*MainFormSLS->hh[81];
c2.v[24] += (sum_160_1_130)*MainFormSLS->hh[130];
c2.v[24] += (sum_160_1_131)*MainFormSLS->hh[19];
c2.v[24] += (sum_160_1_132)*MainFormSLS->hh[68];
c2.v[24] += (sum_160_1_133)*MainFormSLS->hh[117];
c2.v[24] += (sum_160_1_134)*MainFormSLS->hh[6];
c2.v[24] += (sum_160_1_135)*MainFormSLS->hh[55];
c2.v[24] += (sum_160_1_136)*MainFormSLS->hh[104];
c2.v[24] += (sum_160_1_137)*MainFormSLS->hh[153];
c2.v[24] += (sum_160_1_138)*MainFormSLS->hh[42];
c2.v[24] += (sum_160_1_139)*MainFormSLS->hh[91];
c2.v[24] += (sum_160_1_140)*MainFormSLS->hh[140];
c2.v[24] += (sum_160_1_141)*MainFormSLS->hh[29];
c2.v[24] += (sum_160_1_142)*MainFormSLS->hh[78];
c2.v[24] += (sum_160_1_143)*MainFormSLS->hh[127];
c2.v[24] += (sum_160_1_144)*MainFormSLS->hh[16];
c2.v[24] += (sum_160_1_145)*MainFormSLS->hh[65];
c2.v[24] += (sum_160_1_146)*MainFormSLS->hh[114];
c2.v[24] += (sum_160_1_147)*MainFormSLS->hh[3];
c2.v[24] += (sum_160_1_148)*MainFormSLS->hh[52];
c2.v[24] += (sum_160_1_149)*MainFormSLS->hh[101];
c2.v[24] += (sum_160_1_150)*MainFormSLS->hh[150];
c2.v[24] += (sum_160_1_151)*MainFormSLS->hh[39];
c2.v[24] += (sum_160_1_152)*MainFormSLS->hh[88];
c2.v[24] += (sum_160_1_153)*MainFormSLS->hh[137];
c2.v[24] += (sum_160_1_154)*MainFormSLS->hh[26];
c2.v[24] += (sum_160_1_155)*MainFormSLS->hh[75];
c2.v[24] += (sum_160_1_156)*MainFormSLS->hh[124];
c2.v[24] += (sum_160_1_157)*MainFormSLS->hh[13];
c2.v[24] += (sum_160_1_158)*MainFormSLS->hh[62];
c2.v[24] += (sum_160_1_159)*MainFormSLS->hh[111];

//frequency level id 51
c2.v[25] += (sum_160_1_000)*MainFormSLS->hh[0];
c2.v[25] += (sum_160_1_001)*MainFormSLS->hh[51];
c2.v[25] += (sum_160_1_002)*MainFormSLS->hh[102];
c2.v[25] += (sum_160_1_003)*MainFormSLS->hh[153];
c2.v[25] += (sum_160_1_004)*MainFormSLS->hh[44];
c2.v[25] += (sum_160_1_005)*MainFormSLS->hh[95];
c2.v[25] += (sum_160_1_006)*MainFormSLS->hh[146];
c2.v[25] += (sum_160_1_007)*MainFormSLS->hh[37];
c2.v[25] += (sum_160_1_008)*MainFormSLS->hh[88];
c2.v[25] += (sum_160_1_009)*MainFormSLS->hh[139];
c2.v[25] += (sum_160_1_010)*MainFormSLS->hh[30];
c2.v[25] += (sum_160_1_011)*MainFormSLS->hh[81];
c2.v[25] += (sum_160_1_012)*MainFormSLS->hh[132];
c2.v[25] += (sum_160_1_013)*MainFormSLS->hh[23];
c2.v[25] += (sum_160_1_014)*MainFormSLS->hh[74];
c2.v[25] += (sum_160_1_015)*MainFormSLS->hh[125];
c2.v[25] += (sum_160_1_016)*MainFormSLS->hh[16];
c2.v[25] += (sum_160_1_017)*MainFormSLS->hh[67];
c2.v[25] += (sum_160_1_018)*MainFormSLS->hh[118];
c2.v[25] += (sum_160_1_019)*MainFormSLS->hh[9];
c2.v[25] += (sum_160_1_020)*MainFormSLS->hh[60];
c2.v[25] += (sum_160_1_021)*MainFormSLS->hh[111];
c2.v[25] += (sum_160_1_022)*MainFormSLS->hh[2];
c2.v[25] += (sum_160_1_023)*MainFormSLS->hh[53];
c2.v[25] += (sum_160_1_024)*MainFormSLS->hh[104];
c2.v[25] += (sum_160_1_025)*MainFormSLS->hh[155];
c2.v[25] += (sum_160_1_026)*MainFormSLS->hh[46];
c2.v[25] += (sum_160_1_027)*MainFormSLS->hh[97];
c2.v[25] += (sum_160_1_028)*MainFormSLS->hh[148];
c2.v[25] += (sum_160_1_029)*MainFormSLS->hh[39];
c2.v[25] += (sum_160_1_030)*MainFormSLS->hh[90];
c2.v[25] += (sum_160_1_031)*MainFormSLS->hh[141];
c2.v[25] += (sum_160_1_032)*MainFormSLS->hh[32];
c2.v[25] += (sum_160_1_033)*MainFormSLS->hh[83];
c2.v[25] += (sum_160_1_034)*MainFormSLS->hh[134];
c2.v[25] += (sum_160_1_035)*MainFormSLS->hh[25];
c2.v[25] += (sum_160_1_036)*MainFormSLS->hh[76];
c2.v[25] += (sum_160_1_037)*MainFormSLS->hh[127];
c2.v[25] += (sum_160_1_038)*MainFormSLS->hh[18];
c2.v[25] += (sum_160_1_039)*MainFormSLS->hh[69];
c2.v[25] += (sum_160_1_040)*MainFormSLS->hh[120];
c2.v[25] += (sum_160_1_041)*MainFormSLS->hh[11];
c2.v[25] += (sum_160_1_042)*MainFormSLS->hh[62];
c2.v[25] += (sum_160_1_043)*MainFormSLS->hh[113];
c2.v[25] += (sum_160_1_044)*MainFormSLS->hh[4];
c2.v[25] += (sum_160_1_045)*MainFormSLS->hh[55];
c2.v[25] += (sum_160_1_046)*MainFormSLS->hh[106];
c2.v[25] += (sum_160_1_047)*MainFormSLS->hh[157];
c2.v[25] += (sum_160_1_048)*MainFormSLS->hh[48];
c2.v[25] += (sum_160_1_049)*MainFormSLS->hh[99];
c2.v[25] += (sum_160_1_050)*MainFormSLS->hh[150];
c2.v[25] += (sum_160_1_051)*MainFormSLS->hh[41];
c2.v[25] += (sum_160_1_052)*MainFormSLS->hh[92];
c2.v[25] += (sum_160_1_053)*MainFormSLS->hh[143];
c2.v[25] += (sum_160_1_054)*MainFormSLS->hh[34];
c2.v[25] += (sum_160_1_055)*MainFormSLS->hh[85];
c2.v[25] += (sum_160_1_056)*MainFormSLS->hh[136];
c2.v[25] += (sum_160_1_057)*MainFormSLS->hh[27];
c2.v[25] += (sum_160_1_058)*MainFormSLS->hh[78];
c2.v[25] += (sum_160_1_059)*MainFormSLS->hh[129];
c2.v[25] += (sum_160_1_060)*MainFormSLS->hh[20];
c2.v[25] += (sum_160_1_061)*MainFormSLS->hh[71];
c2.v[25] += (sum_160_1_062)*MainFormSLS->hh[122];
c2.v[25] += (sum_160_1_063)*MainFormSLS->hh[13];
c2.v[25] += (sum_160_1_064)*MainFormSLS->hh[64];
c2.v[25] += (sum_160_1_065)*MainFormSLS->hh[115];
c2.v[25] += (sum_160_1_066)*MainFormSLS->hh[6];
c2.v[25] += (sum_160_1_067)*MainFormSLS->hh[57];
c2.v[25] += (sum_160_1_068)*MainFormSLS->hh[108];
c2.v[25] += (sum_160_1_069)*MainFormSLS->hh[159];
c2.v[25] += (sum_160_1_070)*MainFormSLS->hh[50];
c2.v[25] += (sum_160_1_071)*MainFormSLS->hh[101];
c2.v[25] += (sum_160_1_072)*MainFormSLS->hh[152];
c2.v[25] += (sum_160_1_073)*MainFormSLS->hh[43];
c2.v[25] += (sum_160_1_074)*MainFormSLS->hh[94];
c2.v[25] += (sum_160_1_075)*MainFormSLS->hh[145];
c2.v[25] += (sum_160_1_076)*MainFormSLS->hh[36];
c2.v[25] += (sum_160_1_077)*MainFormSLS->hh[87];
c2.v[25] += (sum_160_1_078)*MainFormSLS->hh[138];
c2.v[25] += (sum_160_1_079)*MainFormSLS->hh[29];
c2.v[25] += (sum_160_1_080)*MainFormSLS->hh[80];
c2.v[25] += (sum_160_1_081)*MainFormSLS->hh[131];
c2.v[25] += (sum_160_1_082)*MainFormSLS->hh[22];
c2.v[25] += (sum_160_1_083)*MainFormSLS->hh[73];
c2.v[25] += (sum_160_1_084)*MainFormSLS->hh[124];
c2.v[25] += (sum_160_1_085)*MainFormSLS->hh[15];
c2.v[25] += (sum_160_1_086)*MainFormSLS->hh[66];
c2.v[25] += (sum_160_1_087)*MainFormSLS->hh[117];
c2.v[25] += (sum_160_1_088)*MainFormSLS->hh[8];
c2.v[25] += (sum_160_1_089)*MainFormSLS->hh[59];
c2.v[25] += (sum_160_1_090)*MainFormSLS->hh[110];
c2.v[25] += (sum_160_1_091)*MainFormSLS->hh[1];
c2.v[25] += (sum_160_1_092)*MainFormSLS->hh[52];
c2.v[25] += (sum_160_1_093)*MainFormSLS->hh[103];
c2.v[25] += (sum_160_1_094)*MainFormSLS->hh[154];
c2.v[25] += (sum_160_1_095)*MainFormSLS->hh[45];
c2.v[25] += (sum_160_1_096)*MainFormSLS->hh[96];
c2.v[25] += (sum_160_1_097)*MainFormSLS->hh[147];
c2.v[25] += (sum_160_1_098)*MainFormSLS->hh[38];
c2.v[25] += (sum_160_1_099)*MainFormSLS->hh[89];
c2.v[25] += (sum_160_1_100)*MainFormSLS->hh[140];
c2.v[25] += (sum_160_1_101)*MainFormSLS->hh[31];
c2.v[25] += (sum_160_1_102)*MainFormSLS->hh[82];
c2.v[25] += (sum_160_1_103)*MainFormSLS->hh[133];
c2.v[25] += (sum_160_1_104)*MainFormSLS->hh[24];
c2.v[25] += (sum_160_1_105)*MainFormSLS->hh[75];
c2.v[25] += (sum_160_1_106)*MainFormSLS->hh[126];
c2.v[25] += (sum_160_1_107)*MainFormSLS->hh[17];
c2.v[25] += (sum_160_1_108)*MainFormSLS->hh[68];
c2.v[25] += (sum_160_1_109)*MainFormSLS->hh[119];
c2.v[25] += (sum_160_1_110)*MainFormSLS->hh[10];
c2.v[25] += (sum_160_1_111)*MainFormSLS->hh[61];
c2.v[25] += (sum_160_1_112)*MainFormSLS->hh[112];
c2.v[25] += (sum_160_1_113)*MainFormSLS->hh[3];
c2.v[25] += (sum_160_1_114)*MainFormSLS->hh[54];
c2.v[25] += (sum_160_1_115)*MainFormSLS->hh[105];
c2.v[25] += (sum_160_1_116)*MainFormSLS->hh[156];
c2.v[25] += (sum_160_1_117)*MainFormSLS->hh[47];
c2.v[25] += (sum_160_1_118)*MainFormSLS->hh[98];
c2.v[25] += (sum_160_1_119)*MainFormSLS->hh[149];
c2.v[25] += (sum_160_1_120)*MainFormSLS->hh[40];
c2.v[25] += (sum_160_1_121)*MainFormSLS->hh[91];
c2.v[25] += (sum_160_1_122)*MainFormSLS->hh[142];
c2.v[25] += (sum_160_1_123)*MainFormSLS->hh[33];
c2.v[25] += (sum_160_1_124)*MainFormSLS->hh[84];
c2.v[25] += (sum_160_1_125)*MainFormSLS->hh[135];
c2.v[25] += (sum_160_1_126)*MainFormSLS->hh[26];
c2.v[25] += (sum_160_1_127)*MainFormSLS->hh[77];
c2.v[25] += (sum_160_1_128)*MainFormSLS->hh[128];
c2.v[25] += (sum_160_1_129)*MainFormSLS->hh[19];
c2.v[25] += (sum_160_1_130)*MainFormSLS->hh[70];
c2.v[25] += (sum_160_1_131)*MainFormSLS->hh[121];
c2.v[25] += (sum_160_1_132)*MainFormSLS->hh[12];
c2.v[25] += (sum_160_1_133)*MainFormSLS->hh[63];
c2.v[25] += (sum_160_1_134)*MainFormSLS->hh[114];
c2.v[25] += (sum_160_1_135)*MainFormSLS->hh[5];
c2.v[25] += (sum_160_1_136)*MainFormSLS->hh[56];
c2.v[25] += (sum_160_1_137)*MainFormSLS->hh[107];
c2.v[25] += (sum_160_1_138)*MainFormSLS->hh[158];
c2.v[25] += (sum_160_1_139)*MainFormSLS->hh[49];
c2.v[25] += (sum_160_1_140)*MainFormSLS->hh[100];
c2.v[25] += (sum_160_1_141)*MainFormSLS->hh[151];
c2.v[25] += (sum_160_1_142)*MainFormSLS->hh[42];
c2.v[25] += (sum_160_1_143)*MainFormSLS->hh[93];
c2.v[25] += (sum_160_1_144)*MainFormSLS->hh[144];
c2.v[25] += (sum_160_1_145)*MainFormSLS->hh[35];
c2.v[25] += (sum_160_1_146)*MainFormSLS->hh[86];
c2.v[25] += (sum_160_1_147)*MainFormSLS->hh[137];
c2.v[25] += (sum_160_1_148)*MainFormSLS->hh[28];
c2.v[25] += (sum_160_1_149)*MainFormSLS->hh[79];
c2.v[25] += (sum_160_1_150)*MainFormSLS->hh[130];
c2.v[25] += (sum_160_1_151)*MainFormSLS->hh[21];
c2.v[25] += (sum_160_1_152)*MainFormSLS->hh[72];
c2.v[25] += (sum_160_1_153)*MainFormSLS->hh[123];
c2.v[25] += (sum_160_1_154)*MainFormSLS->hh[14];
c2.v[25] += (sum_160_1_155)*MainFormSLS->hh[65];
c2.v[25] += (sum_160_1_156)*MainFormSLS->hh[116];
c2.v[25] += (sum_160_1_157)*MainFormSLS->hh[7];
c2.v[25] += (sum_160_1_158)*MainFormSLS->hh[58];
c2.v[25] += (sum_160_1_159)*MainFormSLS->hh[109];

//frequency level id 53
c2.v[26] += (sum_160_1_000)*MainFormSLS->hh[0];
c2.v[26] += (sum_160_1_001)*MainFormSLS->hh[53];
c2.v[26] += (sum_160_1_002)*MainFormSLS->hh[106];
c2.v[26] += (sum_160_1_003)*MainFormSLS->hh[159];
c2.v[26] += (sum_160_1_004)*MainFormSLS->hh[52];
c2.v[26] += (sum_160_1_005)*MainFormSLS->hh[105];
c2.v[26] += (sum_160_1_006)*MainFormSLS->hh[158];
c2.v[26] += (sum_160_1_007)*MainFormSLS->hh[51];
c2.v[26] += (sum_160_1_008)*MainFormSLS->hh[104];
c2.v[26] += (sum_160_1_009)*MainFormSLS->hh[157];
c2.v[26] += (sum_160_1_010)*MainFormSLS->hh[50];
c2.v[26] += (sum_160_1_011)*MainFormSLS->hh[103];
c2.v[26] += (sum_160_1_012)*MainFormSLS->hh[156];
c2.v[26] += (sum_160_1_013)*MainFormSLS->hh[49];
c2.v[26] += (sum_160_1_014)*MainFormSLS->hh[102];
c2.v[26] += (sum_160_1_015)*MainFormSLS->hh[155];
c2.v[26] += (sum_160_1_016)*MainFormSLS->hh[48];
c2.v[26] += (sum_160_1_017)*MainFormSLS->hh[101];
c2.v[26] += (sum_160_1_018)*MainFormSLS->hh[154];
c2.v[26] += (sum_160_1_019)*MainFormSLS->hh[47];
c2.v[26] += (sum_160_1_020)*MainFormSLS->hh[100];
c2.v[26] += (sum_160_1_021)*MainFormSLS->hh[153];
c2.v[26] += (sum_160_1_022)*MainFormSLS->hh[46];
c2.v[26] += (sum_160_1_023)*MainFormSLS->hh[99];
c2.v[26] += (sum_160_1_024)*MainFormSLS->hh[152];
c2.v[26] += (sum_160_1_025)*MainFormSLS->hh[45];
c2.v[26] += (sum_160_1_026)*MainFormSLS->hh[98];
c2.v[26] += (sum_160_1_027)*MainFormSLS->hh[151];
c2.v[26] += (sum_160_1_028)*MainFormSLS->hh[44];
c2.v[26] += (sum_160_1_029)*MainFormSLS->hh[97];
c2.v[26] += (sum_160_1_030)*MainFormSLS->hh[150];
c2.v[26] += (sum_160_1_031)*MainFormSLS->hh[43];
c2.v[26] += (sum_160_1_032)*MainFormSLS->hh[96];
c2.v[26] += (sum_160_1_033)*MainFormSLS->hh[149];
c2.v[26] += (sum_160_1_034)*MainFormSLS->hh[42];
c2.v[26] += (sum_160_1_035)*MainFormSLS->hh[95];
c2.v[26] += (sum_160_1_036)*MainFormSLS->hh[148];
c2.v[26] += (sum_160_1_037)*MainFormSLS->hh[41];
c2.v[26] += (sum_160_1_038)*MainFormSLS->hh[94];
c2.v[26] += (sum_160_1_039)*MainFormSLS->hh[147];
c2.v[26] += (sum_160_1_040)*MainFormSLS->hh[40];
c2.v[26] += (sum_160_1_041)*MainFormSLS->hh[93];
c2.v[26] += (sum_160_1_042)*MainFormSLS->hh[146];
c2.v[26] += (sum_160_1_043)*MainFormSLS->hh[39];
c2.v[26] += (sum_160_1_044)*MainFormSLS->hh[92];
c2.v[26] += (sum_160_1_045)*MainFormSLS->hh[145];
c2.v[26] += (sum_160_1_046)*MainFormSLS->hh[38];
c2.v[26] += (sum_160_1_047)*MainFormSLS->hh[91];
c2.v[26] += (sum_160_1_048)*MainFormSLS->hh[144];
c2.v[26] += (sum_160_1_049)*MainFormSLS->hh[37];
c2.v[26] += (sum_160_1_050)*MainFormSLS->hh[90];
c2.v[26] += (sum_160_1_051)*MainFormSLS->hh[143];
c2.v[26] += (sum_160_1_052)*MainFormSLS->hh[36];
c2.v[26] += (sum_160_1_053)*MainFormSLS->hh[89];
c2.v[26] += (sum_160_1_054)*MainFormSLS->hh[142];
c2.v[26] += (sum_160_1_055)*MainFormSLS->hh[35];
c2.v[26] += (sum_160_1_056)*MainFormSLS->hh[88];
c2.v[26] += (sum_160_1_057)*MainFormSLS->hh[141];
c2.v[26] += (sum_160_1_058)*MainFormSLS->hh[34];
c2.v[26] += (sum_160_1_059)*MainFormSLS->hh[87];
c2.v[26] += (sum_160_1_060)*MainFormSLS->hh[140];
c2.v[26] += (sum_160_1_061)*MainFormSLS->hh[33];
c2.v[26] += (sum_160_1_062)*MainFormSLS->hh[86];
c2.v[26] += (sum_160_1_063)*MainFormSLS->hh[139];
c2.v[26] += (sum_160_1_064)*MainFormSLS->hh[32];
c2.v[26] += (sum_160_1_065)*MainFormSLS->hh[85];
c2.v[26] += (sum_160_1_066)*MainFormSLS->hh[138];
c2.v[26] += (sum_160_1_067)*MainFormSLS->hh[31];
c2.v[26] += (sum_160_1_068)*MainFormSLS->hh[84];
c2.v[26] += (sum_160_1_069)*MainFormSLS->hh[137];
c2.v[26] += (sum_160_1_070)*MainFormSLS->hh[30];
c2.v[26] += (sum_160_1_071)*MainFormSLS->hh[83];
c2.v[26] += (sum_160_1_072)*MainFormSLS->hh[136];
c2.v[26] += (sum_160_1_073)*MainFormSLS->hh[29];
c2.v[26] += (sum_160_1_074)*MainFormSLS->hh[82];
c2.v[26] += (sum_160_1_075)*MainFormSLS->hh[135];
c2.v[26] += (sum_160_1_076)*MainFormSLS->hh[28];
c2.v[26] += (sum_160_1_077)*MainFormSLS->hh[81];
c2.v[26] += (sum_160_1_078)*MainFormSLS->hh[134];
c2.v[26] += (sum_160_1_079)*MainFormSLS->hh[27];
c2.v[26] += (sum_160_1_080)*MainFormSLS->hh[80];
c2.v[26] += (sum_160_1_081)*MainFormSLS->hh[133];
c2.v[26] += (sum_160_1_082)*MainFormSLS->hh[26];
c2.v[26] += (sum_160_1_083)*MainFormSLS->hh[79];
c2.v[26] += (sum_160_1_084)*MainFormSLS->hh[132];
c2.v[26] += (sum_160_1_085)*MainFormSLS->hh[25];
c2.v[26] += (sum_160_1_086)*MainFormSLS->hh[78];
c2.v[26] += (sum_160_1_087)*MainFormSLS->hh[131];
c2.v[26] += (sum_160_1_088)*MainFormSLS->hh[24];
c2.v[26] += (sum_160_1_089)*MainFormSLS->hh[77];
c2.v[26] += (sum_160_1_090)*MainFormSLS->hh[130];
c2.v[26] += (sum_160_1_091)*MainFormSLS->hh[23];
c2.v[26] += (sum_160_1_092)*MainFormSLS->hh[76];
c2.v[26] += (sum_160_1_093)*MainFormSLS->hh[129];
c2.v[26] += (sum_160_1_094)*MainFormSLS->hh[22];
c2.v[26] += (sum_160_1_095)*MainFormSLS->hh[75];
c2.v[26] += (sum_160_1_096)*MainFormSLS->hh[128];
c2.v[26] += (sum_160_1_097)*MainFormSLS->hh[21];
c2.v[26] += (sum_160_1_098)*MainFormSLS->hh[74];
c2.v[26] += (sum_160_1_099)*MainFormSLS->hh[127];
c2.v[26] += (sum_160_1_100)*MainFormSLS->hh[20];
c2.v[26] += (sum_160_1_101)*MainFormSLS->hh[73];
c2.v[26] += (sum_160_1_102)*MainFormSLS->hh[126];
c2.v[26] += (sum_160_1_103)*MainFormSLS->hh[19];
c2.v[26] += (sum_160_1_104)*MainFormSLS->hh[72];
c2.v[26] += (sum_160_1_105)*MainFormSLS->hh[125];
c2.v[26] += (sum_160_1_106)*MainFormSLS->hh[18];
c2.v[26] += (sum_160_1_107)*MainFormSLS->hh[71];
c2.v[26] += (sum_160_1_108)*MainFormSLS->hh[124];
c2.v[26] += (sum_160_1_109)*MainFormSLS->hh[17];
c2.v[26] += (sum_160_1_110)*MainFormSLS->hh[70];
c2.v[26] += (sum_160_1_111)*MainFormSLS->hh[123];
c2.v[26] += (sum_160_1_112)*MainFormSLS->hh[16];
c2.v[26] += (sum_160_1_113)*MainFormSLS->hh[69];
c2.v[26] += (sum_160_1_114)*MainFormSLS->hh[122];
c2.v[26] += (sum_160_1_115)*MainFormSLS->hh[15];
c2.v[26] += (sum_160_1_116)*MainFormSLS->hh[68];
c2.v[26] += (sum_160_1_117)*MainFormSLS->hh[121];
c2.v[26] += (sum_160_1_118)*MainFormSLS->hh[14];
c2.v[26] += (sum_160_1_119)*MainFormSLS->hh[67];
c2.v[26] += (sum_160_1_120)*MainFormSLS->hh[120];
c2.v[26] += (sum_160_1_121)*MainFormSLS->hh[13];
c2.v[26] += (sum_160_1_122)*MainFormSLS->hh[66];
c2.v[26] += (sum_160_1_123)*MainFormSLS->hh[119];
c2.v[26] += (sum_160_1_124)*MainFormSLS->hh[12];
c2.v[26] += (sum_160_1_125)*MainFormSLS->hh[65];
c2.v[26] += (sum_160_1_126)*MainFormSLS->hh[118];
c2.v[26] += (sum_160_1_127)*MainFormSLS->hh[11];
c2.v[26] += (sum_160_1_128)*MainFormSLS->hh[64];
c2.v[26] += (sum_160_1_129)*MainFormSLS->hh[117];
c2.v[26] += (sum_160_1_130)*MainFormSLS->hh[10];
c2.v[26] += (sum_160_1_131)*MainFormSLS->hh[63];
c2.v[26] += (sum_160_1_132)*MainFormSLS->hh[116];
c2.v[26] += (sum_160_1_133)*MainFormSLS->hh[9];
c2.v[26] += (sum_160_1_134)*MainFormSLS->hh[62];
c2.v[26] += (sum_160_1_135)*MainFormSLS->hh[115];
c2.v[26] += (sum_160_1_136)*MainFormSLS->hh[8];
c2.v[26] += (sum_160_1_137)*MainFormSLS->hh[61];
c2.v[26] += (sum_160_1_138)*MainFormSLS->hh[114];
c2.v[26] += (sum_160_1_139)*MainFormSLS->hh[7];
c2.v[26] += (sum_160_1_140)*MainFormSLS->hh[60];
c2.v[26] += (sum_160_1_141)*MainFormSLS->hh[113];
c2.v[26] += (sum_160_1_142)*MainFormSLS->hh[6];
c2.v[26] += (sum_160_1_143)*MainFormSLS->hh[59];
c2.v[26] += (sum_160_1_144)*MainFormSLS->hh[112];
c2.v[26] += (sum_160_1_145)*MainFormSLS->hh[5];
c2.v[26] += (sum_160_1_146)*MainFormSLS->hh[58];
c2.v[26] += (sum_160_1_147)*MainFormSLS->hh[111];
c2.v[26] += (sum_160_1_148)*MainFormSLS->hh[4];
c2.v[26] += (sum_160_1_149)*MainFormSLS->hh[57];
c2.v[26] += (sum_160_1_150)*MainFormSLS->hh[110];
c2.v[26] += (sum_160_1_151)*MainFormSLS->hh[3];
c2.v[26] += (sum_160_1_152)*MainFormSLS->hh[56];
c2.v[26] += (sum_160_1_153)*MainFormSLS->hh[109];
c2.v[26] += (sum_160_1_154)*MainFormSLS->hh[2];
c2.v[26] += (sum_160_1_155)*MainFormSLS->hh[55];
c2.v[26] += (sum_160_1_156)*MainFormSLS->hh[108];
c2.v[26] += (sum_160_1_157)*MainFormSLS->hh[1];
c2.v[26] += (sum_160_1_158)*MainFormSLS->hh[54];
c2.v[26] += (sum_160_1_159)*MainFormSLS->hh[107];

//frequency level id 55
c2.v[27] += (sum_32_5_000)*MainFormSLS->hh[0];
c2.v[27] += (sum_32_5_001)*MainFormSLS->hh[55];
c2.v[27] += (sum_32_5_002)*MainFormSLS->hh[110];
c2.v[27] += (sum_32_5_003)*MainFormSLS->hh[5];
c2.v[27] += (sum_32_5_004)*MainFormSLS->hh[60];
c2.v[27] += (sum_32_5_005)*MainFormSLS->hh[115];
c2.v[27] += (sum_32_5_006)*MainFormSLS->hh[10];
c2.v[27] += (sum_32_5_007)*MainFormSLS->hh[65];
c2.v[27] += (sum_32_5_008)*MainFormSLS->hh[120];
c2.v[27] += (sum_32_5_009)*MainFormSLS->hh[15];
c2.v[27] += (sum_32_5_010)*MainFormSLS->hh[70];
c2.v[27] += (sum_32_5_011)*MainFormSLS->hh[125];
c2.v[27] += (sum_32_5_012)*MainFormSLS->hh[20];
c2.v[27] += (sum_32_5_013)*MainFormSLS->hh[75];
c2.v[27] += (sum_32_5_014)*MainFormSLS->hh[130];
c2.v[27] += (sum_32_5_015)*MainFormSLS->hh[25];
c2.v[27] += (sum_32_5_016)*MainFormSLS->hh[80];
c2.v[27] += (sum_32_5_017)*MainFormSLS->hh[135];
c2.v[27] += (sum_32_5_018)*MainFormSLS->hh[30];
c2.v[27] += (sum_32_5_019)*MainFormSLS->hh[85];
c2.v[27] += (sum_32_5_020)*MainFormSLS->hh[140];
c2.v[27] += (sum_32_5_021)*MainFormSLS->hh[35];
c2.v[27] += (sum_32_5_022)*MainFormSLS->hh[90];
c2.v[27] += (sum_32_5_023)*MainFormSLS->hh[145];
c2.v[27] += (sum_32_5_024)*MainFormSLS->hh[40];
c2.v[27] += (sum_32_5_025)*MainFormSLS->hh[95];
c2.v[27] += (sum_32_5_026)*MainFormSLS->hh[150];
c2.v[27] += (sum_32_5_027)*MainFormSLS->hh[45];
c2.v[27] += (sum_32_5_028)*MainFormSLS->hh[100];
c2.v[27] += (sum_32_5_029)*MainFormSLS->hh[155];
c2.v[27] += (sum_32_5_030)*MainFormSLS->hh[50];
c2.v[27] += (sum_32_5_031)*MainFormSLS->hh[105];

//frequency level id 57
c2.v[28] += (sum_160_1_000)*MainFormSLS->hh[0];
c2.v[28] += (sum_160_1_001)*MainFormSLS->hh[57];
c2.v[28] += (sum_160_1_002)*MainFormSLS->hh[114];
c2.v[28] += (sum_160_1_003)*MainFormSLS->hh[11];
c2.v[28] += (sum_160_1_004)*MainFormSLS->hh[68];
c2.v[28] += (sum_160_1_005)*MainFormSLS->hh[125];
c2.v[28] += (sum_160_1_006)*MainFormSLS->hh[22];
c2.v[28] += (sum_160_1_007)*MainFormSLS->hh[79];
c2.v[28] += (sum_160_1_008)*MainFormSLS->hh[136];
c2.v[28] += (sum_160_1_009)*MainFormSLS->hh[33];
c2.v[28] += (sum_160_1_010)*MainFormSLS->hh[90];
c2.v[28] += (sum_160_1_011)*MainFormSLS->hh[147];
c2.v[28] += (sum_160_1_012)*MainFormSLS->hh[44];
c2.v[28] += (sum_160_1_013)*MainFormSLS->hh[101];
c2.v[28] += (sum_160_1_014)*MainFormSLS->hh[158];
c2.v[28] += (sum_160_1_015)*MainFormSLS->hh[55];
c2.v[28] += (sum_160_1_016)*MainFormSLS->hh[112];
c2.v[28] += (sum_160_1_017)*MainFormSLS->hh[9];
c2.v[28] += (sum_160_1_018)*MainFormSLS->hh[66];
c2.v[28] += (sum_160_1_019)*MainFormSLS->hh[123];
c2.v[28] += (sum_160_1_020)*MainFormSLS->hh[20];
c2.v[28] += (sum_160_1_021)*MainFormSLS->hh[77];
c2.v[28] += (sum_160_1_022)*MainFormSLS->hh[134];
c2.v[28] += (sum_160_1_023)*MainFormSLS->hh[31];
c2.v[28] += (sum_160_1_024)*MainFormSLS->hh[88];
c2.v[28] += (sum_160_1_025)*MainFormSLS->hh[145];
c2.v[28] += (sum_160_1_026)*MainFormSLS->hh[42];
c2.v[28] += (sum_160_1_027)*MainFormSLS->hh[99];
c2.v[28] += (sum_160_1_028)*MainFormSLS->hh[156];
c2.v[28] += (sum_160_1_029)*MainFormSLS->hh[53];
c2.v[28] += (sum_160_1_030)*MainFormSLS->hh[110];
c2.v[28] += (sum_160_1_031)*MainFormSLS->hh[7];
c2.v[28] += (sum_160_1_032)*MainFormSLS->hh[64];
c2.v[28] += (sum_160_1_033)*MainFormSLS->hh[121];
c2.v[28] += (sum_160_1_034)*MainFormSLS->hh[18];
c2.v[28] += (sum_160_1_035)*MainFormSLS->hh[75];
c2.v[28] += (sum_160_1_036)*MainFormSLS->hh[132];
c2.v[28] += (sum_160_1_037)*MainFormSLS->hh[29];
c2.v[28] += (sum_160_1_038)*MainFormSLS->hh[86];
c2.v[28] += (sum_160_1_039)*MainFormSLS->hh[143];
c2.v[28] += (sum_160_1_040)*MainFormSLS->hh[40];
c2.v[28] += (sum_160_1_041)*MainFormSLS->hh[97];
c2.v[28] += (sum_160_1_042)*MainFormSLS->hh[154];
c2.v[28] += (sum_160_1_043)*MainFormSLS->hh[51];
c2.v[28] += (sum_160_1_044)*MainFormSLS->hh[108];
c2.v[28] += (sum_160_1_045)*MainFormSLS->hh[5];
c2.v[28] += (sum_160_1_046)*MainFormSLS->hh[62];
c2.v[28] += (sum_160_1_047)*MainFormSLS->hh[119];
c2.v[28] += (sum_160_1_048)*MainFormSLS->hh[16];
c2.v[28] += (sum_160_1_049)*MainFormSLS->hh[73];
c2.v[28] += (sum_160_1_050)*MainFormSLS->hh[130];
c2.v[28] += (sum_160_1_051)*MainFormSLS->hh[27];
c2.v[28] += (sum_160_1_052)*MainFormSLS->hh[84];
c2.v[28] += (sum_160_1_053)*MainFormSLS->hh[141];
c2.v[28] += (sum_160_1_054)*MainFormSLS->hh[38];
c2.v[28] += (sum_160_1_055)*MainFormSLS->hh[95];
c2.v[28] += (sum_160_1_056)*MainFormSLS->hh[152];
c2.v[28] += (sum_160_1_057)*MainFormSLS->hh[49];
c2.v[28] += (sum_160_1_058)*MainFormSLS->hh[106];
c2.v[28] += (sum_160_1_059)*MainFormSLS->hh[3];
c2.v[28] += (sum_160_1_060)*MainFormSLS->hh[60];
c2.v[28] += (sum_160_1_061)*MainFormSLS->hh[117];
c2.v[28] += (sum_160_1_062)*MainFormSLS->hh[14];
c2.v[28] += (sum_160_1_063)*MainFormSLS->hh[71];
c2.v[28] += (sum_160_1_064)*MainFormSLS->hh[128];
c2.v[28] += (sum_160_1_065)*MainFormSLS->hh[25];
c2.v[28] += (sum_160_1_066)*MainFormSLS->hh[82];
c2.v[28] += (sum_160_1_067)*MainFormSLS->hh[139];
c2.v[28] += (sum_160_1_068)*MainFormSLS->hh[36];
c2.v[28] += (sum_160_1_069)*MainFormSLS->hh[93];
c2.v[28] += (sum_160_1_070)*MainFormSLS->hh[150];
c2.v[28] += (sum_160_1_071)*MainFormSLS->hh[47];
c2.v[28] += (sum_160_1_072)*MainFormSLS->hh[104];
c2.v[28] += (sum_160_1_073)*MainFormSLS->hh[1];
c2.v[28] += (sum_160_1_074)*MainFormSLS->hh[58];
c2.v[28] += (sum_160_1_075)*MainFormSLS->hh[115];
c2.v[28] += (sum_160_1_076)*MainFormSLS->hh[12];
c2.v[28] += (sum_160_1_077)*MainFormSLS->hh[69];
c2.v[28] += (sum_160_1_078)*MainFormSLS->hh[126];
c2.v[28] += (sum_160_1_079)*MainFormSLS->hh[23];
c2.v[28] += (sum_160_1_080)*MainFormSLS->hh[80];
c2.v[28] += (sum_160_1_081)*MainFormSLS->hh[137];
c2.v[28] += (sum_160_1_082)*MainFormSLS->hh[34];
c2.v[28] += (sum_160_1_083)*MainFormSLS->hh[91];
c2.v[28] += (sum_160_1_084)*MainFormSLS->hh[148];
c2.v[28] += (sum_160_1_085)*MainFormSLS->hh[45];
c2.v[28] += (sum_160_1_086)*MainFormSLS->hh[102];
c2.v[28] += (sum_160_1_087)*MainFormSLS->hh[159];
c2.v[28] += (sum_160_1_088)*MainFormSLS->hh[56];
c2.v[28] += (sum_160_1_089)*MainFormSLS->hh[113];
c2.v[28] += (sum_160_1_090)*MainFormSLS->hh[10];
c2.v[28] += (sum_160_1_091)*MainFormSLS->hh[67];
c2.v[28] += (sum_160_1_092)*MainFormSLS->hh[124];
c2.v[28] += (sum_160_1_093)*MainFormSLS->hh[21];
c2.v[28] += (sum_160_1_094)*MainFormSLS->hh[78];
c2.v[28] += (sum_160_1_095)*MainFormSLS->hh[135];
c2.v[28] += (sum_160_1_096)*MainFormSLS->hh[32];
c2.v[28] += (sum_160_1_097)*MainFormSLS->hh[89];
c2.v[28] += (sum_160_1_098)*MainFormSLS->hh[146];
c2.v[28] += (sum_160_1_099)*MainFormSLS->hh[43];
c2.v[28] += (sum_160_1_100)*MainFormSLS->hh[100];
c2.v[28] += (sum_160_1_101)*MainFormSLS->hh[157];
c2.v[28] += (sum_160_1_102)*MainFormSLS->hh[54];
c2.v[28] += (sum_160_1_103)*MainFormSLS->hh[111];
c2.v[28] += (sum_160_1_104)*MainFormSLS->hh[8];
c2.v[28] += (sum_160_1_105)*MainFormSLS->hh[65];
c2.v[28] += (sum_160_1_106)*MainFormSLS->hh[122];
c2.v[28] += (sum_160_1_107)*MainFormSLS->hh[19];
c2.v[28] += (sum_160_1_108)*MainFormSLS->hh[76];
c2.v[28] += (sum_160_1_109)*MainFormSLS->hh[133];
c2.v[28] += (sum_160_1_110)*MainFormSLS->hh[30];
c2.v[28] += (sum_160_1_111)*MainFormSLS->hh[87];
c2.v[28] += (sum_160_1_112)*MainFormSLS->hh[144];
c2.v[28] += (sum_160_1_113)*MainFormSLS->hh[41];
c2.v[28] += (sum_160_1_114)*MainFormSLS->hh[98];
c2.v[28] += (sum_160_1_115)*MainFormSLS->hh[155];
c2.v[28] += (sum_160_1_116)*MainFormSLS->hh[52];
c2.v[28] += (sum_160_1_117)*MainFormSLS->hh[109];
c2.v[28] += (sum_160_1_118)*MainFormSLS->hh[6];
c2.v[28] += (sum_160_1_119)*MainFormSLS->hh[63];
c2.v[28] += (sum_160_1_120)*MainFormSLS->hh[120];
c2.v[28] += (sum_160_1_121)*MainFormSLS->hh[17];
c2.v[28] += (sum_160_1_122)*MainFormSLS->hh[74];
c2.v[28] += (sum_160_1_123)*MainFormSLS->hh[131];
c2.v[28] += (sum_160_1_124)*MainFormSLS->hh[28];
c2.v[28] += (sum_160_1_125)*MainFormSLS->hh[85];
c2.v[28] += (sum_160_1_126)*MainFormSLS->hh[142];
c2.v[28] += (sum_160_1_127)*MainFormSLS->hh[39];
c2.v[28] += (sum_160_1_128)*MainFormSLS->hh[96];
c2.v[28] += (sum_160_1_129)*MainFormSLS->hh[153];
c2.v[28] += (sum_160_1_130)*MainFormSLS->hh[50];
c2.v[28] += (sum_160_1_131)*MainFormSLS->hh[107];
c2.v[28] += (sum_160_1_132)*MainFormSLS->hh[4];
c2.v[28] += (sum_160_1_133)*MainFormSLS->hh[61];
c2.v[28] += (sum_160_1_134)*MainFormSLS->hh[118];
c2.v[28] += (sum_160_1_135)*MainFormSLS->hh[15];
c2.v[28] += (sum_160_1_136)*MainFormSLS->hh[72];
c2.v[28] += (sum_160_1_137)*MainFormSLS->hh[129];
c2.v[28] += (sum_160_1_138)*MainFormSLS->hh[26];
c2.v[28] += (sum_160_1_139)*MainFormSLS->hh[83];
c2.v[28] += (sum_160_1_140)*MainFormSLS->hh[140];
c2.v[28] += (sum_160_1_141)*MainFormSLS->hh[37];
c2.v[28] += (sum_160_1_142)*MainFormSLS->hh[94];
c2.v[28] += (sum_160_1_143)*MainFormSLS->hh[151];
c2.v[28] += (sum_160_1_144)*MainFormSLS->hh[48];
c2.v[28] += (sum_160_1_145)*MainFormSLS->hh[105];
c2.v[28] += (sum_160_1_146)*MainFormSLS->hh[2];
c2.v[28] += (sum_160_1_147)*MainFormSLS->hh[59];
c2.v[28] += (sum_160_1_148)*MainFormSLS->hh[116];
c2.v[28] += (sum_160_1_149)*MainFormSLS->hh[13];
c2.v[28] += (sum_160_1_150)*MainFormSLS->hh[70];
c2.v[28] += (sum_160_1_151)*MainFormSLS->hh[127];
c2.v[28] += (sum_160_1_152)*MainFormSLS->hh[24];
c2.v[28] += (sum_160_1_153)*MainFormSLS->hh[81];
c2.v[28] += (sum_160_1_154)*MainFormSLS->hh[138];
c2.v[28] += (sum_160_1_155)*MainFormSLS->hh[35];
c2.v[28] += (sum_160_1_156)*MainFormSLS->hh[92];
c2.v[28] += (sum_160_1_157)*MainFormSLS->hh[149];
c2.v[28] += (sum_160_1_158)*MainFormSLS->hh[46];
c2.v[28] += (sum_160_1_159)*MainFormSLS->hh[103];

//frequency level id 59
c2.v[29] += (sum_160_1_000)*MainFormSLS->hh[0];
c2.v[29] += (sum_160_1_001)*MainFormSLS->hh[59];
c2.v[29] += (sum_160_1_002)*MainFormSLS->hh[118];
c2.v[29] += (sum_160_1_003)*MainFormSLS->hh[17];
c2.v[29] += (sum_160_1_004)*MainFormSLS->hh[76];
c2.v[29] += (sum_160_1_005)*MainFormSLS->hh[135];
c2.v[29] += (sum_160_1_006)*MainFormSLS->hh[34];
c2.v[29] += (sum_160_1_007)*MainFormSLS->hh[93];
c2.v[29] += (sum_160_1_008)*MainFormSLS->hh[152];
c2.v[29] += (sum_160_1_009)*MainFormSLS->hh[51];
c2.v[29] += (sum_160_1_010)*MainFormSLS->hh[110];
c2.v[29] += (sum_160_1_011)*MainFormSLS->hh[9];
c2.v[29] += (sum_160_1_012)*MainFormSLS->hh[68];
c2.v[29] += (sum_160_1_013)*MainFormSLS->hh[127];
c2.v[29] += (sum_160_1_014)*MainFormSLS->hh[26];
c2.v[29] += (sum_160_1_015)*MainFormSLS->hh[85];
c2.v[29] += (sum_160_1_016)*MainFormSLS->hh[144];
c2.v[29] += (sum_160_1_017)*MainFormSLS->hh[43];
c2.v[29] += (sum_160_1_018)*MainFormSLS->hh[102];
c2.v[29] += (sum_160_1_019)*MainFormSLS->hh[1];
c2.v[29] += (sum_160_1_020)*MainFormSLS->hh[60];
c2.v[29] += (sum_160_1_021)*MainFormSLS->hh[119];
c2.v[29] += (sum_160_1_022)*MainFormSLS->hh[18];
c2.v[29] += (sum_160_1_023)*MainFormSLS->hh[77];
c2.v[29] += (sum_160_1_024)*MainFormSLS->hh[136];
c2.v[29] += (sum_160_1_025)*MainFormSLS->hh[35];
c2.v[29] += (sum_160_1_026)*MainFormSLS->hh[94];
c2.v[29] += (sum_160_1_027)*MainFormSLS->hh[153];
c2.v[29] += (sum_160_1_028)*MainFormSLS->hh[52];
c2.v[29] += (sum_160_1_029)*MainFormSLS->hh[111];
c2.v[29] += (sum_160_1_030)*MainFormSLS->hh[10];
c2.v[29] += (sum_160_1_031)*MainFormSLS->hh[69];
c2.v[29] += (sum_160_1_032)*MainFormSLS->hh[128];
c2.v[29] += (sum_160_1_033)*MainFormSLS->hh[27];
c2.v[29] += (sum_160_1_034)*MainFormSLS->hh[86];
c2.v[29] += (sum_160_1_035)*MainFormSLS->hh[145];
c2.v[29] += (sum_160_1_036)*MainFormSLS->hh[44];
c2.v[29] += (sum_160_1_037)*MainFormSLS->hh[103];
c2.v[29] += (sum_160_1_038)*MainFormSLS->hh[2];
c2.v[29] += (sum_160_1_039)*MainFormSLS->hh[61];
c2.v[29] += (sum_160_1_040)*MainFormSLS->hh[120];
c2.v[29] += (sum_160_1_041)*MainFormSLS->hh[19];
c2.v[29] += (sum_160_1_042)*MainFormSLS->hh[78];
c2.v[29] += (sum_160_1_043)*MainFormSLS->hh[137];
c2.v[29] += (sum_160_1_044)*MainFormSLS->hh[36];
c2.v[29] += (sum_160_1_045)*MainFormSLS->hh[95];
c2.v[29] += (sum_160_1_046)*MainFormSLS->hh[154];
c2.v[29] += (sum_160_1_047)*MainFormSLS->hh[53];
c2.v[29] += (sum_160_1_048)*MainFormSLS->hh[112];
c2.v[29] += (sum_160_1_049)*MainFormSLS->hh[11];
c2.v[29] += (sum_160_1_050)*MainFormSLS->hh[70];
c2.v[29] += (sum_160_1_051)*MainFormSLS->hh[129];
c2.v[29] += (sum_160_1_052)*MainFormSLS->hh[28];
c2.v[29] += (sum_160_1_053)*MainFormSLS->hh[87];
c2.v[29] += (sum_160_1_054)*MainFormSLS->hh[146];
c2.v[29] += (sum_160_1_055)*MainFormSLS->hh[45];
c2.v[29] += (sum_160_1_056)*MainFormSLS->hh[104];
c2.v[29] += (sum_160_1_057)*MainFormSLS->hh[3];
c2.v[29] += (sum_160_1_058)*MainFormSLS->hh[62];
c2.v[29] += (sum_160_1_059)*MainFormSLS->hh[121];
c2.v[29] += (sum_160_1_060)*MainFormSLS->hh[20];
c2.v[29] += (sum_160_1_061)*MainFormSLS->hh[79];
c2.v[29] += (sum_160_1_062)*MainFormSLS->hh[138];
c2.v[29] += (sum_160_1_063)*MainFormSLS->hh[37];
c2.v[29] += (sum_160_1_064)*MainFormSLS->hh[96];
c2.v[29] += (sum_160_1_065)*MainFormSLS->hh[155];
c2.v[29] += (sum_160_1_066)*MainFormSLS->hh[54];
c2.v[29] += (sum_160_1_067)*MainFormSLS->hh[113];
c2.v[29] += (sum_160_1_068)*MainFormSLS->hh[12];
c2.v[29] += (sum_160_1_069)*MainFormSLS->hh[71];
c2.v[29] += (sum_160_1_070)*MainFormSLS->hh[130];
c2.v[29] += (sum_160_1_071)*MainFormSLS->hh[29];
c2.v[29] += (sum_160_1_072)*MainFormSLS->hh[88];
c2.v[29] += (sum_160_1_073)*MainFormSLS->hh[147];
c2.v[29] += (sum_160_1_074)*MainFormSLS->hh[46];
c2.v[29] += (sum_160_1_075)*MainFormSLS->hh[105];
c2.v[29] += (sum_160_1_076)*MainFormSLS->hh[4];
c2.v[29] += (sum_160_1_077)*MainFormSLS->hh[63];
c2.v[29] += (sum_160_1_078)*MainFormSLS->hh[122];
c2.v[29] += (sum_160_1_079)*MainFormSLS->hh[21];
c2.v[29] += (sum_160_1_080)*MainFormSLS->hh[80];
c2.v[29] += (sum_160_1_081)*MainFormSLS->hh[139];
c2.v[29] += (sum_160_1_082)*MainFormSLS->hh[38];
c2.v[29] += (sum_160_1_083)*MainFormSLS->hh[97];
c2.v[29] += (sum_160_1_084)*MainFormSLS->hh[156];
c2.v[29] += (sum_160_1_085)*MainFormSLS->hh[55];
c2.v[29] += (sum_160_1_086)*MainFormSLS->hh[114];
c2.v[29] += (sum_160_1_087)*MainFormSLS->hh[13];
c2.v[29] += (sum_160_1_088)*MainFormSLS->hh[72];
c2.v[29] += (sum_160_1_089)*MainFormSLS->hh[131];
c2.v[29] += (sum_160_1_090)*MainFormSLS->hh[30];
c2.v[29] += (sum_160_1_091)*MainFormSLS->hh[89];
c2.v[29] += (sum_160_1_092)*MainFormSLS->hh[148];
c2.v[29] += (sum_160_1_093)*MainFormSLS->hh[47];
c2.v[29] += (sum_160_1_094)*MainFormSLS->hh[106];
c2.v[29] += (sum_160_1_095)*MainFormSLS->hh[5];
c2.v[29] += (sum_160_1_096)*MainFormSLS->hh[64];
c2.v[29] += (sum_160_1_097)*MainFormSLS->hh[123];
c2.v[29] += (sum_160_1_098)*MainFormSLS->hh[22];
c2.v[29] += (sum_160_1_099)*MainFormSLS->hh[81];
c2.v[29] += (sum_160_1_100)*MainFormSLS->hh[140];
c2.v[29] += (sum_160_1_101)*MainFormSLS->hh[39];
c2.v[29] += (sum_160_1_102)*MainFormSLS->hh[98];
c2.v[29] += (sum_160_1_103)*MainFormSLS->hh[157];
c2.v[29] += (sum_160_1_104)*MainFormSLS->hh[56];
c2.v[29] += (sum_160_1_105)*MainFormSLS->hh[115];
c2.v[29] += (sum_160_1_106)*MainFormSLS->hh[14];
c2.v[29] += (sum_160_1_107)*MainFormSLS->hh[73];
c2.v[29] += (sum_160_1_108)*MainFormSLS->hh[132];
c2.v[29] += (sum_160_1_109)*MainFormSLS->hh[31];
c2.v[29] += (sum_160_1_110)*MainFormSLS->hh[90];
c2.v[29] += (sum_160_1_111)*MainFormSLS->hh[149];
c2.v[29] += (sum_160_1_112)*MainFormSLS->hh[48];
c2.v[29] += (sum_160_1_113)*MainFormSLS->hh[107];
c2.v[29] += (sum_160_1_114)*MainFormSLS->hh[6];
c2.v[29] += (sum_160_1_115)*MainFormSLS->hh[65];
c2.v[29] += (sum_160_1_116)*MainFormSLS->hh[124];
c2.v[29] += (sum_160_1_117)*MainFormSLS->hh[23];
c2.v[29] += (sum_160_1_118)*MainFormSLS->hh[82];
c2.v[29] += (sum_160_1_119)*MainFormSLS->hh[141];
c2.v[29] += (sum_160_1_120)*MainFormSLS->hh[40];
c2.v[29] += (sum_160_1_121)*MainFormSLS->hh[99];
c2.v[29] += (sum_160_1_122)*MainFormSLS->hh[158];
c2.v[29] += (sum_160_1_123)*MainFormSLS->hh[57];
c2.v[29] += (sum_160_1_124)*MainFormSLS->hh[116];
c2.v[29] += (sum_160_1_125)*MainFormSLS->hh[15];
c2.v[29] += (sum_160_1_126)*MainFormSLS->hh[74];
c2.v[29] += (sum_160_1_127)*MainFormSLS->hh[133];
c2.v[29] += (sum_160_1_128)*MainFormSLS->hh[32];
c2.v[29] += (sum_160_1_129)*MainFormSLS->hh[91];
c2.v[29] += (sum_160_1_130)*MainFormSLS->hh[150];
c2.v[29] += (sum_160_1_131)*MainFormSLS->hh[49];
c2.v[29] += (sum_160_1_132)*MainFormSLS->hh[108];
c2.v[29] += (sum_160_1_133)*MainFormSLS->hh[7];
c2.v[29] += (sum_160_1_134)*MainFormSLS->hh[66];
c2.v[29] += (sum_160_1_135)*MainFormSLS->hh[125];
c2.v[29] += (sum_160_1_136)*MainFormSLS->hh[24];
c2.v[29] += (sum_160_1_137)*MainFormSLS->hh[83];
c2.v[29] += (sum_160_1_138)*MainFormSLS->hh[142];
c2.v[29] += (sum_160_1_139)*MainFormSLS->hh[41];
c2.v[29] += (sum_160_1_140)*MainFormSLS->hh[100];
c2.v[29] += (sum_160_1_141)*MainFormSLS->hh[159];
c2.v[29] += (sum_160_1_142)*MainFormSLS->hh[58];
c2.v[29] += (sum_160_1_143)*MainFormSLS->hh[117];
c2.v[29] += (sum_160_1_144)*MainFormSLS->hh[16];
c2.v[29] += (sum_160_1_145)*MainFormSLS->hh[75];
c2.v[29] += (sum_160_1_146)*MainFormSLS->hh[134];
c2.v[29] += (sum_160_1_147)*MainFormSLS->hh[33];
c2.v[29] += (sum_160_1_148)*MainFormSLS->hh[92];
c2.v[29] += (sum_160_1_149)*MainFormSLS->hh[151];
c2.v[29] += (sum_160_1_150)*MainFormSLS->hh[50];
c2.v[29] += (sum_160_1_151)*MainFormSLS->hh[109];
c2.v[29] += (sum_160_1_152)*MainFormSLS->hh[8];
c2.v[29] += (sum_160_1_153)*MainFormSLS->hh[67];
c2.v[29] += (sum_160_1_154)*MainFormSLS->hh[126];
c2.v[29] += (sum_160_1_155)*MainFormSLS->hh[25];
c2.v[29] += (sum_160_1_156)*MainFormSLS->hh[84];
c2.v[29] += (sum_160_1_157)*MainFormSLS->hh[143];
c2.v[29] += (sum_160_1_158)*MainFormSLS->hh[42];
c2.v[29] += (sum_160_1_159)*MainFormSLS->hh[101];

//frequency level id 61
c2.v[30] += (sum_160_1_000)*MainFormSLS->hh[0];
c2.v[30] += (sum_160_1_001)*MainFormSLS->hh[61];
c2.v[30] += (sum_160_1_002)*MainFormSLS->hh[122];
c2.v[30] += (sum_160_1_003)*MainFormSLS->hh[23];
c2.v[30] += (sum_160_1_004)*MainFormSLS->hh[84];
c2.v[30] += (sum_160_1_005)*MainFormSLS->hh[145];
c2.v[30] += (sum_160_1_006)*MainFormSLS->hh[46];
c2.v[30] += (sum_160_1_007)*MainFormSLS->hh[107];
c2.v[30] += (sum_160_1_008)*MainFormSLS->hh[8];
c2.v[30] += (sum_160_1_009)*MainFormSLS->hh[69];
c2.v[30] += (sum_160_1_010)*MainFormSLS->hh[130];
c2.v[30] += (sum_160_1_011)*MainFormSLS->hh[31];
c2.v[30] += (sum_160_1_012)*MainFormSLS->hh[92];
c2.v[30] += (sum_160_1_013)*MainFormSLS->hh[153];
c2.v[30] += (sum_160_1_014)*MainFormSLS->hh[54];
c2.v[30] += (sum_160_1_015)*MainFormSLS->hh[115];
c2.v[30] += (sum_160_1_016)*MainFormSLS->hh[16];
c2.v[30] += (sum_160_1_017)*MainFormSLS->hh[77];
c2.v[30] += (sum_160_1_018)*MainFormSLS->hh[138];
c2.v[30] += (sum_160_1_019)*MainFormSLS->hh[39];
c2.v[30] += (sum_160_1_020)*MainFormSLS->hh[100];
c2.v[30] += (sum_160_1_021)*MainFormSLS->hh[1];
c2.v[30] += (sum_160_1_022)*MainFormSLS->hh[62];
c2.v[30] += (sum_160_1_023)*MainFormSLS->hh[123];
c2.v[30] += (sum_160_1_024)*MainFormSLS->hh[24];
c2.v[30] += (sum_160_1_025)*MainFormSLS->hh[85];
c2.v[30] += (sum_160_1_026)*MainFormSLS->hh[146];
c2.v[30] += (sum_160_1_027)*MainFormSLS->hh[47];
c2.v[30] += (sum_160_1_028)*MainFormSLS->hh[108];
c2.v[30] += (sum_160_1_029)*MainFormSLS->hh[9];
c2.v[30] += (sum_160_1_030)*MainFormSLS->hh[70];
c2.v[30] += (sum_160_1_031)*MainFormSLS->hh[131];
c2.v[30] += (sum_160_1_032)*MainFormSLS->hh[32];
c2.v[30] += (sum_160_1_033)*MainFormSLS->hh[93];
c2.v[30] += (sum_160_1_034)*MainFormSLS->hh[154];
c2.v[30] += (sum_160_1_035)*MainFormSLS->hh[55];
c2.v[30] += (sum_160_1_036)*MainFormSLS->hh[116];
c2.v[30] += (sum_160_1_037)*MainFormSLS->hh[17];
c2.v[30] += (sum_160_1_038)*MainFormSLS->hh[78];
c2.v[30] += (sum_160_1_039)*MainFormSLS->hh[139];
c2.v[30] += (sum_160_1_040)*MainFormSLS->hh[40];
c2.v[30] += (sum_160_1_041)*MainFormSLS->hh[101];
c2.v[30] += (sum_160_1_042)*MainFormSLS->hh[2];
c2.v[30] += (sum_160_1_043)*MainFormSLS->hh[63];
c2.v[30] += (sum_160_1_044)*MainFormSLS->hh[124];
c2.v[30] += (sum_160_1_045)*MainFormSLS->hh[25];
c2.v[30] += (sum_160_1_046)*MainFormSLS->hh[86];
c2.v[30] += (sum_160_1_047)*MainFormSLS->hh[147];
c2.v[30] += (sum_160_1_048)*MainFormSLS->hh[48];
c2.v[30] += (sum_160_1_049)*MainFormSLS->hh[109];
c2.v[30] += (sum_160_1_050)*MainFormSLS->hh[10];
c2.v[30] += (sum_160_1_051)*MainFormSLS->hh[71];
c2.v[30] += (sum_160_1_052)*MainFormSLS->hh[132];
c2.v[30] += (sum_160_1_053)*MainFormSLS->hh[33];
c2.v[30] += (sum_160_1_054)*MainFormSLS->hh[94];
c2.v[30] += (sum_160_1_055)*MainFormSLS->hh[155];
c2.v[30] += (sum_160_1_056)*MainFormSLS->hh[56];
c2.v[30] += (sum_160_1_057)*MainFormSLS->hh[117];
c2.v[30] += (sum_160_1_058)*MainFormSLS->hh[18];
c2.v[30] += (sum_160_1_059)*MainFormSLS->hh[79];
c2.v[30] += (sum_160_1_060)*MainFormSLS->hh[140];
c2.v[30] += (sum_160_1_061)*MainFormSLS->hh[41];
c2.v[30] += (sum_160_1_062)*MainFormSLS->hh[102];
c2.v[30] += (sum_160_1_063)*MainFormSLS->hh[3];
c2.v[30] += (sum_160_1_064)*MainFormSLS->hh[64];
c2.v[30] += (sum_160_1_065)*MainFormSLS->hh[125];
c2.v[30] += (sum_160_1_066)*MainFormSLS->hh[26];
c2.v[30] += (sum_160_1_067)*MainFormSLS->hh[87];
c2.v[30] += (sum_160_1_068)*MainFormSLS->hh[148];
c2.v[30] += (sum_160_1_069)*MainFormSLS->hh[49];
c2.v[30] += (sum_160_1_070)*MainFormSLS->hh[110];
c2.v[30] += (sum_160_1_071)*MainFormSLS->hh[11];
c2.v[30] += (sum_160_1_072)*MainFormSLS->hh[72];
c2.v[30] += (sum_160_1_073)*MainFormSLS->hh[133];
c2.v[30] += (sum_160_1_074)*MainFormSLS->hh[34];
c2.v[30] += (sum_160_1_075)*MainFormSLS->hh[95];
c2.v[30] += (sum_160_1_076)*MainFormSLS->hh[156];
c2.v[30] += (sum_160_1_077)*MainFormSLS->hh[57];
c2.v[30] += (sum_160_1_078)*MainFormSLS->hh[118];
c2.v[30] += (sum_160_1_079)*MainFormSLS->hh[19];
c2.v[30] += (sum_160_1_080)*MainFormSLS->hh[80];
c2.v[30] += (sum_160_1_081)*MainFormSLS->hh[141];
c2.v[30] += (sum_160_1_082)*MainFormSLS->hh[42];
c2.v[30] += (sum_160_1_083)*MainFormSLS->hh[103];
c2.v[30] += (sum_160_1_084)*MainFormSLS->hh[4];
c2.v[30] += (sum_160_1_085)*MainFormSLS->hh[65];
c2.v[30] += (sum_160_1_086)*MainFormSLS->hh[126];
c2.v[30] += (sum_160_1_087)*MainFormSLS->hh[27];
c2.v[30] += (sum_160_1_088)*MainFormSLS->hh[88];
c2.v[30] += (sum_160_1_089)*MainFormSLS->hh[149];
c2.v[30] += (sum_160_1_090)*MainFormSLS->hh[50];
c2.v[30] += (sum_160_1_091)*MainFormSLS->hh[111];
c2.v[30] += (sum_160_1_092)*MainFormSLS->hh[12];
c2.v[30] += (sum_160_1_093)*MainFormSLS->hh[73];
c2.v[30] += (sum_160_1_094)*MainFormSLS->hh[134];
c2.v[30] += (sum_160_1_095)*MainFormSLS->hh[35];
c2.v[30] += (sum_160_1_096)*MainFormSLS->hh[96];
c2.v[30] += (sum_160_1_097)*MainFormSLS->hh[157];
c2.v[30] += (sum_160_1_098)*MainFormSLS->hh[58];
c2.v[30] += (sum_160_1_099)*MainFormSLS->hh[119];
c2.v[30] += (sum_160_1_100)*MainFormSLS->hh[20];
c2.v[30] += (sum_160_1_101)*MainFormSLS->hh[81];
c2.v[30] += (sum_160_1_102)*MainFormSLS->hh[142];
c2.v[30] += (sum_160_1_103)*MainFormSLS->hh[43];
c2.v[30] += (sum_160_1_104)*MainFormSLS->hh[104];
c2.v[30] += (sum_160_1_105)*MainFormSLS->hh[5];
c2.v[30] += (sum_160_1_106)*MainFormSLS->hh[66];
c2.v[30] += (sum_160_1_107)*MainFormSLS->hh[127];
c2.v[30] += (sum_160_1_108)*MainFormSLS->hh[28];
c2.v[30] += (sum_160_1_109)*MainFormSLS->hh[89];
c2.v[30] += (sum_160_1_110)*MainFormSLS->hh[150];
c2.v[30] += (sum_160_1_111)*MainFormSLS->hh[51];
c2.v[30] += (sum_160_1_112)*MainFormSLS->hh[112];
c2.v[30] += (sum_160_1_113)*MainFormSLS->hh[13];
c2.v[30] += (sum_160_1_114)*MainFormSLS->hh[74];
c2.v[30] += (sum_160_1_115)*MainFormSLS->hh[135];
c2.v[30] += (sum_160_1_116)*MainFormSLS->hh[36];
c2.v[30] += (sum_160_1_117)*MainFormSLS->hh[97];
c2.v[30] += (sum_160_1_118)*MainFormSLS->hh[158];
c2.v[30] += (sum_160_1_119)*MainFormSLS->hh[59];
c2.v[30] += (sum_160_1_120)*MainFormSLS->hh[120];
c2.v[30] += (sum_160_1_121)*MainFormSLS->hh[21];
c2.v[30] += (sum_160_1_122)*MainFormSLS->hh[82];
c2.v[30] += (sum_160_1_123)*MainFormSLS->hh[143];
c2.v[30] += (sum_160_1_124)*MainFormSLS->hh[44];
c2.v[30] += (sum_160_1_125)*MainFormSLS->hh[105];
c2.v[30] += (sum_160_1_126)*MainFormSLS->hh[6];
c2.v[30] += (sum_160_1_127)*MainFormSLS->hh[67];
c2.v[30] += (sum_160_1_128)*MainFormSLS->hh[128];
c2.v[30] += (sum_160_1_129)*MainFormSLS->hh[29];
c2.v[30] += (sum_160_1_130)*MainFormSLS->hh[90];
c2.v[30] += (sum_160_1_131)*MainFormSLS->hh[151];
c2.v[30] += (sum_160_1_132)*MainFormSLS->hh[52];
c2.v[30] += (sum_160_1_133)*MainFormSLS->hh[113];
c2.v[30] += (sum_160_1_134)*MainFormSLS->hh[14];
c2.v[30] += (sum_160_1_135)*MainFormSLS->hh[75];
c2.v[30] += (sum_160_1_136)*MainFormSLS->hh[136];
c2.v[30] += (sum_160_1_137)*MainFormSLS->hh[37];
c2.v[30] += (sum_160_1_138)*MainFormSLS->hh[98];
c2.v[30] += (sum_160_1_139)*MainFormSLS->hh[159];
c2.v[30] += (sum_160_1_140)*MainFormSLS->hh[60];
c2.v[30] += (sum_160_1_141)*MainFormSLS->hh[121];
c2.v[30] += (sum_160_1_142)*MainFormSLS->hh[22];
c2.v[30] += (sum_160_1_143)*MainFormSLS->hh[83];
c2.v[30] += (sum_160_1_144)*MainFormSLS->hh[144];
c2.v[30] += (sum_160_1_145)*MainFormSLS->hh[45];
c2.v[30] += (sum_160_1_146)*MainFormSLS->hh[106];
c2.v[30] += (sum_160_1_147)*MainFormSLS->hh[7];
c2.v[30] += (sum_160_1_148)*MainFormSLS->hh[68];
c2.v[30] += (sum_160_1_149)*MainFormSLS->hh[129];
c2.v[30] += (sum_160_1_150)*MainFormSLS->hh[30];
c2.v[30] += (sum_160_1_151)*MainFormSLS->hh[91];
c2.v[30] += (sum_160_1_152)*MainFormSLS->hh[152];
c2.v[30] += (sum_160_1_153)*MainFormSLS->hh[53];
c2.v[30] += (sum_160_1_154)*MainFormSLS->hh[114];
c2.v[30] += (sum_160_1_155)*MainFormSLS->hh[15];
c2.v[30] += (sum_160_1_156)*MainFormSLS->hh[76];
c2.v[30] += (sum_160_1_157)*MainFormSLS->hh[137];
c2.v[30] += (sum_160_1_158)*MainFormSLS->hh[38];
c2.v[30] += (sum_160_1_159)*MainFormSLS->hh[99];

//frequency level id 63
c2.v[31] += (sum_160_1_000)*MainFormSLS->hh[0];
c2.v[31] += (sum_160_1_001)*MainFormSLS->hh[63];
c2.v[31] += (sum_160_1_002)*MainFormSLS->hh[126];
c2.v[31] += (sum_160_1_003)*MainFormSLS->hh[29];
c2.v[31] += (sum_160_1_004)*MainFormSLS->hh[92];
c2.v[31] += (sum_160_1_005)*MainFormSLS->hh[155];
c2.v[31] += (sum_160_1_006)*MainFormSLS->hh[58];
c2.v[31] += (sum_160_1_007)*MainFormSLS->hh[121];
c2.v[31] += (sum_160_1_008)*MainFormSLS->hh[24];
c2.v[31] += (sum_160_1_009)*MainFormSLS->hh[87];
c2.v[31] += (sum_160_1_010)*MainFormSLS->hh[150];
c2.v[31] += (sum_160_1_011)*MainFormSLS->hh[53];
c2.v[31] += (sum_160_1_012)*MainFormSLS->hh[116];
c2.v[31] += (sum_160_1_013)*MainFormSLS->hh[19];
c2.v[31] += (sum_160_1_014)*MainFormSLS->hh[82];
c2.v[31] += (sum_160_1_015)*MainFormSLS->hh[145];
c2.v[31] += (sum_160_1_016)*MainFormSLS->hh[48];
c2.v[31] += (sum_160_1_017)*MainFormSLS->hh[111];
c2.v[31] += (sum_160_1_018)*MainFormSLS->hh[14];
c2.v[31] += (sum_160_1_019)*MainFormSLS->hh[77];
c2.v[31] += (sum_160_1_020)*MainFormSLS->hh[140];
c2.v[31] += (sum_160_1_021)*MainFormSLS->hh[43];
c2.v[31] += (sum_160_1_022)*MainFormSLS->hh[106];
c2.v[31] += (sum_160_1_023)*MainFormSLS->hh[9];
c2.v[31] += (sum_160_1_024)*MainFormSLS->hh[72];
c2.v[31] += (sum_160_1_025)*MainFormSLS->hh[135];
c2.v[31] += (sum_160_1_026)*MainFormSLS->hh[38];
c2.v[31] += (sum_160_1_027)*MainFormSLS->hh[101];
c2.v[31] += (sum_160_1_028)*MainFormSLS->hh[4];
c2.v[31] += (sum_160_1_029)*MainFormSLS->hh[67];
c2.v[31] += (sum_160_1_030)*MainFormSLS->hh[130];
c2.v[31] += (sum_160_1_031)*MainFormSLS->hh[33];
c2.v[31] += (sum_160_1_032)*MainFormSLS->hh[96];
c2.v[31] += (sum_160_1_033)*MainFormSLS->hh[159];
c2.v[31] += (sum_160_1_034)*MainFormSLS->hh[62];
c2.v[31] += (sum_160_1_035)*MainFormSLS->hh[125];
c2.v[31] += (sum_160_1_036)*MainFormSLS->hh[28];
c2.v[31] += (sum_160_1_037)*MainFormSLS->hh[91];
c2.v[31] += (sum_160_1_038)*MainFormSLS->hh[154];
c2.v[31] += (sum_160_1_039)*MainFormSLS->hh[57];
c2.v[31] += (sum_160_1_040)*MainFormSLS->hh[120];
c2.v[31] += (sum_160_1_041)*MainFormSLS->hh[23];
c2.v[31] += (sum_160_1_042)*MainFormSLS->hh[86];
c2.v[31] += (sum_160_1_043)*MainFormSLS->hh[149];
c2.v[31] += (sum_160_1_044)*MainFormSLS->hh[52];
c2.v[31] += (sum_160_1_045)*MainFormSLS->hh[115];
c2.v[31] += (sum_160_1_046)*MainFormSLS->hh[18];
c2.v[31] += (sum_160_1_047)*MainFormSLS->hh[81];
c2.v[31] += (sum_160_1_048)*MainFormSLS->hh[144];
c2.v[31] += (sum_160_1_049)*MainFormSLS->hh[47];
c2.v[31] += (sum_160_1_050)*MainFormSLS->hh[110];
c2.v[31] += (sum_160_1_051)*MainFormSLS->hh[13];
c2.v[31] += (sum_160_1_052)*MainFormSLS->hh[76];
c2.v[31] += (sum_160_1_053)*MainFormSLS->hh[139];
c2.v[31] += (sum_160_1_054)*MainFormSLS->hh[42];
c2.v[31] += (sum_160_1_055)*MainFormSLS->hh[105];
c2.v[31] += (sum_160_1_056)*MainFormSLS->hh[8];
c2.v[31] += (sum_160_1_057)*MainFormSLS->hh[71];
c2.v[31] += (sum_160_1_058)*MainFormSLS->hh[134];
c2.v[31] += (sum_160_1_059)*MainFormSLS->hh[37];
c2.v[31] += (sum_160_1_060)*MainFormSLS->hh[100];
c2.v[31] += (sum_160_1_061)*MainFormSLS->hh[3];
c2.v[31] += (sum_160_1_062)*MainFormSLS->hh[66];
c2.v[31] += (sum_160_1_063)*MainFormSLS->hh[129];
c2.v[31] += (sum_160_1_064)*MainFormSLS->hh[32];
c2.v[31] += (sum_160_1_065)*MainFormSLS->hh[95];
c2.v[31] += (sum_160_1_066)*MainFormSLS->hh[158];
c2.v[31] += (sum_160_1_067)*MainFormSLS->hh[61];
c2.v[31] += (sum_160_1_068)*MainFormSLS->hh[124];
c2.v[31] += (sum_160_1_069)*MainFormSLS->hh[27];
c2.v[31] += (sum_160_1_070)*MainFormSLS->hh[90];
c2.v[31] += (sum_160_1_071)*MainFormSLS->hh[153];
c2.v[31] += (sum_160_1_072)*MainFormSLS->hh[56];
c2.v[31] += (sum_160_1_073)*MainFormSLS->hh[119];
c2.v[31] += (sum_160_1_074)*MainFormSLS->hh[22];
c2.v[31] += (sum_160_1_075)*MainFormSLS->hh[85];
c2.v[31] += (sum_160_1_076)*MainFormSLS->hh[148];
c2.v[31] += (sum_160_1_077)*MainFormSLS->hh[51];
c2.v[31] += (sum_160_1_078)*MainFormSLS->hh[114];
c2.v[31] += (sum_160_1_079)*MainFormSLS->hh[17];
c2.v[31] += (sum_160_1_080)*MainFormSLS->hh[80];
c2.v[31] += (sum_160_1_081)*MainFormSLS->hh[143];
c2.v[31] += (sum_160_1_082)*MainFormSLS->hh[46];
c2.v[31] += (sum_160_1_083)*MainFormSLS->hh[109];
c2.v[31] += (sum_160_1_084)*MainFormSLS->hh[12];
c2.v[31] += (sum_160_1_085)*MainFormSLS->hh[75];
c2.v[31] += (sum_160_1_086)*MainFormSLS->hh[138];
c2.v[31] += (sum_160_1_087)*MainFormSLS->hh[41];
c2.v[31] += (sum_160_1_088)*MainFormSLS->hh[104];
c2.v[31] += (sum_160_1_089)*MainFormSLS->hh[7];
c2.v[31] += (sum_160_1_090)*MainFormSLS->hh[70];
c2.v[31] += (sum_160_1_091)*MainFormSLS->hh[133];
c2.v[31] += (sum_160_1_092)*MainFormSLS->hh[36];
c2.v[31] += (sum_160_1_093)*MainFormSLS->hh[99];
c2.v[31] += (sum_160_1_094)*MainFormSLS->hh[2];
c2.v[31] += (sum_160_1_095)*MainFormSLS->hh[65];
c2.v[31] += (sum_160_1_096)*MainFormSLS->hh[128];
c2.v[31] += (sum_160_1_097)*MainFormSLS->hh[31];
c2.v[31] += (sum_160_1_098)*MainFormSLS->hh[94];
c2.v[31] += (sum_160_1_099)*MainFormSLS->hh[157];
c2.v[31] += (sum_160_1_100)*MainFormSLS->hh[60];
c2.v[31] += (sum_160_1_101)*MainFormSLS->hh[123];
c2.v[31] += (sum_160_1_102)*MainFormSLS->hh[26];
c2.v[31] += (sum_160_1_103)*MainFormSLS->hh[89];
c2.v[31] += (sum_160_1_104)*MainFormSLS->hh[152];
c2.v[31] += (sum_160_1_105)*MainFormSLS->hh[55];
c2.v[31] += (sum_160_1_106)*MainFormSLS->hh[118];
c2.v[31] += (sum_160_1_107)*MainFormSLS->hh[21];
c2.v[31] += (sum_160_1_108)*MainFormSLS->hh[84];
c2.v[31] += (sum_160_1_109)*MainFormSLS->hh[147];
c2.v[31] += (sum_160_1_110)*MainFormSLS->hh[50];
c2.v[31] += (sum_160_1_111)*MainFormSLS->hh[113];
c2.v[31] += (sum_160_1_112)*MainFormSLS->hh[16];
c2.v[31] += (sum_160_1_113)*MainFormSLS->hh[79];
c2.v[31] += (sum_160_1_114)*MainFormSLS->hh[142];
c2.v[31] += (sum_160_1_115)*MainFormSLS->hh[45];
c2.v[31] += (sum_160_1_116)*MainFormSLS->hh[108];
c2.v[31] += (sum_160_1_117)*MainFormSLS->hh[11];
c2.v[31] += (sum_160_1_118)*MainFormSLS->hh[74];
c2.v[31] += (sum_160_1_119)*MainFormSLS->hh[137];
c2.v[31] += (sum_160_1_120)*MainFormSLS->hh[40];
c2.v[31] += (sum_160_1_121)*MainFormSLS->hh[103];
c2.v[31] += (sum_160_1_122)*MainFormSLS->hh[6];
c2.v[31] += (sum_160_1_123)*MainFormSLS->hh[69];
c2.v[31] += (sum_160_1_124)*MainFormSLS->hh[132];
c2.v[31] += (sum_160_1_125)*MainFormSLS->hh[35];
c2.v[31] += (sum_160_1_126)*MainFormSLS->hh[98];
c2.v[31] += (sum_160_1_127)*MainFormSLS->hh[1];
c2.v[31] += (sum_160_1_128)*MainFormSLS->hh[64];
c2.v[31] += (sum_160_1_129)*MainFormSLS->hh[127];
c2.v[31] += (sum_160_1_130)*MainFormSLS->hh[30];
c2.v[31] += (sum_160_1_131)*MainFormSLS->hh[93];
c2.v[31] += (sum_160_1_132)*MainFormSLS->hh[156];
c2.v[31] += (sum_160_1_133)*MainFormSLS->hh[59];
c2.v[31] += (sum_160_1_134)*MainFormSLS->hh[122];
c2.v[31] += (sum_160_1_135)*MainFormSLS->hh[25];
c2.v[31] += (sum_160_1_136)*MainFormSLS->hh[88];
c2.v[31] += (sum_160_1_137)*MainFormSLS->hh[151];
c2.v[31] += (sum_160_1_138)*MainFormSLS->hh[54];
c2.v[31] += (sum_160_1_139)*MainFormSLS->hh[117];
c2.v[31] += (sum_160_1_140)*MainFormSLS->hh[20];
c2.v[31] += (sum_160_1_141)*MainFormSLS->hh[83];
c2.v[31] += (sum_160_1_142)*MainFormSLS->hh[146];
c2.v[31] += (sum_160_1_143)*MainFormSLS->hh[49];
c2.v[31] += (sum_160_1_144)*MainFormSLS->hh[112];
c2.v[31] += (sum_160_1_145)*MainFormSLS->hh[15];
c2.v[31] += (sum_160_1_146)*MainFormSLS->hh[78];
c2.v[31] += (sum_160_1_147)*MainFormSLS->hh[141];
c2.v[31] += (sum_160_1_148)*MainFormSLS->hh[44];
c2.v[31] += (sum_160_1_149)*MainFormSLS->hh[107];
c2.v[31] += (sum_160_1_150)*MainFormSLS->hh[10];
c2.v[31] += (sum_160_1_151)*MainFormSLS->hh[73];
c2.v[31] += (sum_160_1_152)*MainFormSLS->hh[136];
c2.v[31] += (sum_160_1_153)*MainFormSLS->hh[39];
c2.v[31] += (sum_160_1_154)*MainFormSLS->hh[102];
c2.v[31] += (sum_160_1_155)*MainFormSLS->hh[5];
c2.v[31] += (sum_160_1_156)*MainFormSLS->hh[68];
c2.v[31] += (sum_160_1_157)*MainFormSLS->hh[131];
c2.v[31] += (sum_160_1_158)*MainFormSLS->hh[34];
c2.v[31] += (sum_160_1_159)*MainFormSLS->hh[97];

//frequency level id 65
c2.v[32] += (sum_32_5_000)*MainFormSLS->hh[0];
c2.v[32] += (sum_32_5_001)*MainFormSLS->hh[65];
c2.v[32] += (sum_32_5_002)*MainFormSLS->hh[130];
c2.v[32] += (sum_32_5_003)*MainFormSLS->hh[35];
c2.v[32] += (sum_32_5_004)*MainFormSLS->hh[100];
c2.v[32] += (sum_32_5_005)*MainFormSLS->hh[5];
c2.v[32] += (sum_32_5_006)*MainFormSLS->hh[70];
c2.v[32] += (sum_32_5_007)*MainFormSLS->hh[135];
c2.v[32] += (sum_32_5_008)*MainFormSLS->hh[40];
c2.v[32] += (sum_32_5_009)*MainFormSLS->hh[105];
c2.v[32] += (sum_32_5_010)*MainFormSLS->hh[10];
c2.v[32] += (sum_32_5_011)*MainFormSLS->hh[75];
c2.v[32] += (sum_32_5_012)*MainFormSLS->hh[140];
c2.v[32] += (sum_32_5_013)*MainFormSLS->hh[45];
c2.v[32] += (sum_32_5_014)*MainFormSLS->hh[110];
c2.v[32] += (sum_32_5_015)*MainFormSLS->hh[15];
c2.v[32] += (sum_32_5_016)*MainFormSLS->hh[80];
c2.v[32] += (sum_32_5_017)*MainFormSLS->hh[145];
c2.v[32] += (sum_32_5_018)*MainFormSLS->hh[50];
c2.v[32] += (sum_32_5_019)*MainFormSLS->hh[115];
c2.v[32] += (sum_32_5_020)*MainFormSLS->hh[20];
c2.v[32] += (sum_32_5_021)*MainFormSLS->hh[85];
c2.v[32] += (sum_32_5_022)*MainFormSLS->hh[150];
c2.v[32] += (sum_32_5_023)*MainFormSLS->hh[55];
c2.v[32] += (sum_32_5_024)*MainFormSLS->hh[120];
c2.v[32] += (sum_32_5_025)*MainFormSLS->hh[25];
c2.v[32] += (sum_32_5_026)*MainFormSLS->hh[90];
c2.v[32] += (sum_32_5_027)*MainFormSLS->hh[155];
c2.v[32] += (sum_32_5_028)*MainFormSLS->hh[60];
c2.v[32] += (sum_32_5_029)*MainFormSLS->hh[125];
c2.v[32] += (sum_32_5_030)*MainFormSLS->hh[30];
c2.v[32] += (sum_32_5_031)*MainFormSLS->hh[95];

//frequency level id 67
c2.v[33] += (sum_160_1_000)*MainFormSLS->hh[0];
c2.v[33] += (sum_160_1_001)*MainFormSLS->hh[67];
c2.v[33] += (sum_160_1_002)*MainFormSLS->hh[134];
c2.v[33] += (sum_160_1_003)*MainFormSLS->hh[41];
c2.v[33] += (sum_160_1_004)*MainFormSLS->hh[108];
c2.v[33] += (sum_160_1_005)*MainFormSLS->hh[15];
c2.v[33] += (sum_160_1_006)*MainFormSLS->hh[82];
c2.v[33] += (sum_160_1_007)*MainFormSLS->hh[149];
c2.v[33] += (sum_160_1_008)*MainFormSLS->hh[56];
c2.v[33] += (sum_160_1_009)*MainFormSLS->hh[123];
c2.v[33] += (sum_160_1_010)*MainFormSLS->hh[30];
c2.v[33] += (sum_160_1_011)*MainFormSLS->hh[97];
c2.v[33] += (sum_160_1_012)*MainFormSLS->hh[4];
c2.v[33] += (sum_160_1_013)*MainFormSLS->hh[71];
c2.v[33] += (sum_160_1_014)*MainFormSLS->hh[138];
c2.v[33] += (sum_160_1_015)*MainFormSLS->hh[45];
c2.v[33] += (sum_160_1_016)*MainFormSLS->hh[112];
c2.v[33] += (sum_160_1_017)*MainFormSLS->hh[19];
c2.v[33] += (sum_160_1_018)*MainFormSLS->hh[86];
c2.v[33] += (sum_160_1_019)*MainFormSLS->hh[153];
c2.v[33] += (sum_160_1_020)*MainFormSLS->hh[60];
c2.v[33] += (sum_160_1_021)*MainFormSLS->hh[127];
c2.v[33] += (sum_160_1_022)*MainFormSLS->hh[34];
c2.v[33] += (sum_160_1_023)*MainFormSLS->hh[101];
c2.v[33] += (sum_160_1_024)*MainFormSLS->hh[8];
c2.v[33] += (sum_160_1_025)*MainFormSLS->hh[75];
c2.v[33] += (sum_160_1_026)*MainFormSLS->hh[142];
c2.v[33] += (sum_160_1_027)*MainFormSLS->hh[49];
c2.v[33] += (sum_160_1_028)*MainFormSLS->hh[116];
c2.v[33] += (sum_160_1_029)*MainFormSLS->hh[23];
c2.v[33] += (sum_160_1_030)*MainFormSLS->hh[90];
c2.v[33] += (sum_160_1_031)*MainFormSLS->hh[157];
c2.v[33] += (sum_160_1_032)*MainFormSLS->hh[64];
c2.v[33] += (sum_160_1_033)*MainFormSLS->hh[131];
c2.v[33] += (sum_160_1_034)*MainFormSLS->hh[38];
c2.v[33] += (sum_160_1_035)*MainFormSLS->hh[105];
c2.v[33] += (sum_160_1_036)*MainFormSLS->hh[12];
c2.v[33] += (sum_160_1_037)*MainFormSLS->hh[79];
c2.v[33] += (sum_160_1_038)*MainFormSLS->hh[146];
c2.v[33] += (sum_160_1_039)*MainFormSLS->hh[53];
c2.v[33] += (sum_160_1_040)*MainFormSLS->hh[120];
c2.v[33] += (sum_160_1_041)*MainFormSLS->hh[27];
c2.v[33] += (sum_160_1_042)*MainFormSLS->hh[94];
c2.v[33] += (sum_160_1_043)*MainFormSLS->hh[1];
c2.v[33] += (sum_160_1_044)*MainFormSLS->hh[68];
c2.v[33] += (sum_160_1_045)*MainFormSLS->hh[135];
c2.v[33] += (sum_160_1_046)*MainFormSLS->hh[42];
c2.v[33] += (sum_160_1_047)*MainFormSLS->hh[109];
c2.v[33] += (sum_160_1_048)*MainFormSLS->hh[16];
c2.v[33] += (sum_160_1_049)*MainFormSLS->hh[83];
c2.v[33] += (sum_160_1_050)*MainFormSLS->hh[150];
c2.v[33] += (sum_160_1_051)*MainFormSLS->hh[57];
c2.v[33] += (sum_160_1_052)*MainFormSLS->hh[124];
c2.v[33] += (sum_160_1_053)*MainFormSLS->hh[31];
c2.v[33] += (sum_160_1_054)*MainFormSLS->hh[98];
c2.v[33] += (sum_160_1_055)*MainFormSLS->hh[5];
c2.v[33] += (sum_160_1_056)*MainFormSLS->hh[72];
c2.v[33] += (sum_160_1_057)*MainFormSLS->hh[139];
c2.v[33] += (sum_160_1_058)*MainFormSLS->hh[46];
c2.v[33] += (sum_160_1_059)*MainFormSLS->hh[113];
c2.v[33] += (sum_160_1_060)*MainFormSLS->hh[20];
c2.v[33] += (sum_160_1_061)*MainFormSLS->hh[87];
c2.v[33] += (sum_160_1_062)*MainFormSLS->hh[154];
c2.v[33] += (sum_160_1_063)*MainFormSLS->hh[61];
c2.v[33] += (sum_160_1_064)*MainFormSLS->hh[128];
c2.v[33] += (sum_160_1_065)*MainFormSLS->hh[35];
c2.v[33] += (sum_160_1_066)*MainFormSLS->hh[102];
c2.v[33] += (sum_160_1_067)*MainFormSLS->hh[9];
c2.v[33] += (sum_160_1_068)*MainFormSLS->hh[76];
c2.v[33] += (sum_160_1_069)*MainFormSLS->hh[143];
c2.v[33] += (sum_160_1_070)*MainFormSLS->hh[50];
c2.v[33] += (sum_160_1_071)*MainFormSLS->hh[117];
c2.v[33] += (sum_160_1_072)*MainFormSLS->hh[24];
c2.v[33] += (sum_160_1_073)*MainFormSLS->hh[91];
c2.v[33] += (sum_160_1_074)*MainFormSLS->hh[158];
c2.v[33] += (sum_160_1_075)*MainFormSLS->hh[65];
c2.v[33] += (sum_160_1_076)*MainFormSLS->hh[132];
c2.v[33] += (sum_160_1_077)*MainFormSLS->hh[39];
c2.v[33] += (sum_160_1_078)*MainFormSLS->hh[106];
c2.v[33] += (sum_160_1_079)*MainFormSLS->hh[13];
c2.v[33] += (sum_160_1_080)*MainFormSLS->hh[80];
c2.v[33] += (sum_160_1_081)*MainFormSLS->hh[147];
c2.v[33] += (sum_160_1_082)*MainFormSLS->hh[54];
c2.v[33] += (sum_160_1_083)*MainFormSLS->hh[121];
c2.v[33] += (sum_160_1_084)*MainFormSLS->hh[28];
c2.v[33] += (sum_160_1_085)*MainFormSLS->hh[95];
c2.v[33] += (sum_160_1_086)*MainFormSLS->hh[2];
c2.v[33] += (sum_160_1_087)*MainFormSLS->hh[69];
c2.v[33] += (sum_160_1_088)*MainFormSLS->hh[136];
c2.v[33] += (sum_160_1_089)*MainFormSLS->hh[43];
c2.v[33] += (sum_160_1_090)*MainFormSLS->hh[110];
c2.v[33] += (sum_160_1_091)*MainFormSLS->hh[17];
c2.v[33] += (sum_160_1_092)*MainFormSLS->hh[84];
c2.v[33] += (sum_160_1_093)*MainFormSLS->hh[151];
c2.v[33] += (sum_160_1_094)*MainFormSLS->hh[58];
c2.v[33] += (sum_160_1_095)*MainFormSLS->hh[125];
c2.v[33] += (sum_160_1_096)*MainFormSLS->hh[32];
c2.v[33] += (sum_160_1_097)*MainFormSLS->hh[99];
c2.v[33] += (sum_160_1_098)*MainFormSLS->hh[6];
c2.v[33] += (sum_160_1_099)*MainFormSLS->hh[73];
c2.v[33] += (sum_160_1_100)*MainFormSLS->hh[140];
c2.v[33] += (sum_160_1_101)*MainFormSLS->hh[47];
c2.v[33] += (sum_160_1_102)*MainFormSLS->hh[114];
c2.v[33] += (sum_160_1_103)*MainFormSLS->hh[21];
c2.v[33] += (sum_160_1_104)*MainFormSLS->hh[88];
c2.v[33] += (sum_160_1_105)*MainFormSLS->hh[155];
c2.v[33] += (sum_160_1_106)*MainFormSLS->hh[62];
c2.v[33] += (sum_160_1_107)*MainFormSLS->hh[129];
c2.v[33] += (sum_160_1_108)*MainFormSLS->hh[36];
c2.v[33] += (sum_160_1_109)*MainFormSLS->hh[103];
c2.v[33] += (sum_160_1_110)*MainFormSLS->hh[10];
c2.v[33] += (sum_160_1_111)*MainFormSLS->hh[77];
c2.v[33] += (sum_160_1_112)*MainFormSLS->hh[144];
c2.v[33] += (sum_160_1_113)*MainFormSLS->hh[51];
c2.v[33] += (sum_160_1_114)*MainFormSLS->hh[118];
c2.v[33] += (sum_160_1_115)*MainFormSLS->hh[25];
c2.v[33] += (sum_160_1_116)*MainFormSLS->hh[92];
c2.v[33] += (sum_160_1_117)*MainFormSLS->hh[159];
c2.v[33] += (sum_160_1_118)*MainFormSLS->hh[66];
c2.v[33] += (sum_160_1_119)*MainFormSLS->hh[133];
c2.v[33] += (sum_160_1_120)*MainFormSLS->hh[40];
c2.v[33] += (sum_160_1_121)*MainFormSLS->hh[107];
c2.v[33] += (sum_160_1_122)*MainFormSLS->hh[14];
c2.v[33] += (sum_160_1_123)*MainFormSLS->hh[81];
c2.v[33] += (sum_160_1_124)*MainFormSLS->hh[148];
c2.v[33] += (sum_160_1_125)*MainFormSLS->hh[55];
c2.v[33] += (sum_160_1_126)*MainFormSLS->hh[122];
c2.v[33] += (sum_160_1_127)*MainFormSLS->hh[29];
c2.v[33] += (sum_160_1_128)*MainFormSLS->hh[96];
c2.v[33] += (sum_160_1_129)*MainFormSLS->hh[3];
c2.v[33] += (sum_160_1_130)*MainFormSLS->hh[70];
c2.v[33] += (sum_160_1_131)*MainFormSLS->hh[137];
c2.v[33] += (sum_160_1_132)*MainFormSLS->hh[44];
c2.v[33] += (sum_160_1_133)*MainFormSLS->hh[111];
c2.v[33] += (sum_160_1_134)*MainFormSLS->hh[18];
c2.v[33] += (sum_160_1_135)*MainFormSLS->hh[85];
c2.v[33] += (sum_160_1_136)*MainFormSLS->hh[152];
c2.v[33] += (sum_160_1_137)*MainFormSLS->hh[59];
c2.v[33] += (sum_160_1_138)*MainFormSLS->hh[126];
c2.v[33] += (sum_160_1_139)*MainFormSLS->hh[33];
c2.v[33] += (sum_160_1_140)*MainFormSLS->hh[100];
c2.v[33] += (sum_160_1_141)*MainFormSLS->hh[7];
c2.v[33] += (sum_160_1_142)*MainFormSLS->hh[74];
c2.v[33] += (sum_160_1_143)*MainFormSLS->hh[141];
c2.v[33] += (sum_160_1_144)*MainFormSLS->hh[48];
c2.v[33] += (sum_160_1_145)*MainFormSLS->hh[115];
c2.v[33] += (sum_160_1_146)*MainFormSLS->hh[22];
c2.v[33] += (sum_160_1_147)*MainFormSLS->hh[89];
c2.v[33] += (sum_160_1_148)*MainFormSLS->hh[156];
c2.v[33] += (sum_160_1_149)*MainFormSLS->hh[63];
c2.v[33] += (sum_160_1_150)*MainFormSLS->hh[130];
c2.v[33] += (sum_160_1_151)*MainFormSLS->hh[37];
c2.v[33] += (sum_160_1_152)*MainFormSLS->hh[104];
c2.v[33] += (sum_160_1_153)*MainFormSLS->hh[11];
c2.v[33] += (sum_160_1_154)*MainFormSLS->hh[78];
c2.v[33] += (sum_160_1_155)*MainFormSLS->hh[145];
c2.v[33] += (sum_160_1_156)*MainFormSLS->hh[52];
c2.v[33] += (sum_160_1_157)*MainFormSLS->hh[119];
c2.v[33] += (sum_160_1_158)*MainFormSLS->hh[26];
c2.v[33] += (sum_160_1_159)*MainFormSLS->hh[93];

//frequency level id 69
c2.v[34] += (sum_160_1_000)*MainFormSLS->hh[0];
c2.v[34] += (sum_160_1_001)*MainFormSLS->hh[69];
c2.v[34] += (sum_160_1_002)*MainFormSLS->hh[138];
c2.v[34] += (sum_160_1_003)*MainFormSLS->hh[47];
c2.v[34] += (sum_160_1_004)*MainFormSLS->hh[116];
c2.v[34] += (sum_160_1_005)*MainFormSLS->hh[25];
c2.v[34] += (sum_160_1_006)*MainFormSLS->hh[94];
c2.v[34] += (sum_160_1_007)*MainFormSLS->hh[3];
c2.v[34] += (sum_160_1_008)*MainFormSLS->hh[72];
c2.v[34] += (sum_160_1_009)*MainFormSLS->hh[141];
c2.v[34] += (sum_160_1_010)*MainFormSLS->hh[50];
c2.v[34] += (sum_160_1_011)*MainFormSLS->hh[119];
c2.v[34] += (sum_160_1_012)*MainFormSLS->hh[28];
c2.v[34] += (sum_160_1_013)*MainFormSLS->hh[97];
c2.v[34] += (sum_160_1_014)*MainFormSLS->hh[6];
c2.v[34] += (sum_160_1_015)*MainFormSLS->hh[75];
c2.v[34] += (sum_160_1_016)*MainFormSLS->hh[144];
c2.v[34] += (sum_160_1_017)*MainFormSLS->hh[53];
c2.v[34] += (sum_160_1_018)*MainFormSLS->hh[122];
c2.v[34] += (sum_160_1_019)*MainFormSLS->hh[31];
c2.v[34] += (sum_160_1_020)*MainFormSLS->hh[100];
c2.v[34] += (sum_160_1_021)*MainFormSLS->hh[9];
c2.v[34] += (sum_160_1_022)*MainFormSLS->hh[78];
c2.v[34] += (sum_160_1_023)*MainFormSLS->hh[147];
c2.v[34] += (sum_160_1_024)*MainFormSLS->hh[56];
c2.v[34] += (sum_160_1_025)*MainFormSLS->hh[125];
c2.v[34] += (sum_160_1_026)*MainFormSLS->hh[34];
c2.v[34] += (sum_160_1_027)*MainFormSLS->hh[103];
c2.v[34] += (sum_160_1_028)*MainFormSLS->hh[12];
c2.v[34] += (sum_160_1_029)*MainFormSLS->hh[81];
c2.v[34] += (sum_160_1_030)*MainFormSLS->hh[150];
c2.v[34] += (sum_160_1_031)*MainFormSLS->hh[59];
c2.v[34] += (sum_160_1_032)*MainFormSLS->hh[128];
c2.v[34] += (sum_160_1_033)*MainFormSLS->hh[37];
c2.v[34] += (sum_160_1_034)*MainFormSLS->hh[106];
c2.v[34] += (sum_160_1_035)*MainFormSLS->hh[15];
c2.v[34] += (sum_160_1_036)*MainFormSLS->hh[84];
c2.v[34] += (sum_160_1_037)*MainFormSLS->hh[153];
c2.v[34] += (sum_160_1_038)*MainFormSLS->hh[62];
c2.v[34] += (sum_160_1_039)*MainFormSLS->hh[131];
c2.v[34] += (sum_160_1_040)*MainFormSLS->hh[40];
c2.v[34] += (sum_160_1_041)*MainFormSLS->hh[109];
c2.v[34] += (sum_160_1_042)*MainFormSLS->hh[18];
c2.v[34] += (sum_160_1_043)*MainFormSLS->hh[87];
c2.v[34] += (sum_160_1_044)*MainFormSLS->hh[156];
c2.v[34] += (sum_160_1_045)*MainFormSLS->hh[65];
c2.v[34] += (sum_160_1_046)*MainFormSLS->hh[134];
c2.v[34] += (sum_160_1_047)*MainFormSLS->hh[43];
c2.v[34] += (sum_160_1_048)*MainFormSLS->hh[112];
c2.v[34] += (sum_160_1_049)*MainFormSLS->hh[21];
c2.v[34] += (sum_160_1_050)*MainFormSLS->hh[90];
c2.v[34] += (sum_160_1_051)*MainFormSLS->hh[159];
c2.v[34] += (sum_160_1_052)*MainFormSLS->hh[68];
c2.v[34] += (sum_160_1_053)*MainFormSLS->hh[137];
c2.v[34] += (sum_160_1_054)*MainFormSLS->hh[46];
c2.v[34] += (sum_160_1_055)*MainFormSLS->hh[115];
c2.v[34] += (sum_160_1_056)*MainFormSLS->hh[24];
c2.v[34] += (sum_160_1_057)*MainFormSLS->hh[93];
c2.v[34] += (sum_160_1_058)*MainFormSLS->hh[2];
c2.v[34] += (sum_160_1_059)*MainFormSLS->hh[71];
c2.v[34] += (sum_160_1_060)*MainFormSLS->hh[140];
c2.v[34] += (sum_160_1_061)*MainFormSLS->hh[49];
c2.v[34] += (sum_160_1_062)*MainFormSLS->hh[118];
c2.v[34] += (sum_160_1_063)*MainFormSLS->hh[27];
c2.v[34] += (sum_160_1_064)*MainFormSLS->hh[96];
c2.v[34] += (sum_160_1_065)*MainFormSLS->hh[5];
c2.v[34] += (sum_160_1_066)*MainFormSLS->hh[74];
c2.v[34] += (sum_160_1_067)*MainFormSLS->hh[143];
c2.v[34] += (sum_160_1_068)*MainFormSLS->hh[52];
c2.v[34] += (sum_160_1_069)*MainFormSLS->hh[121];
c2.v[34] += (sum_160_1_070)*MainFormSLS->hh[30];
c2.v[34] += (sum_160_1_071)*MainFormSLS->hh[99];
c2.v[34] += (sum_160_1_072)*MainFormSLS->hh[8];
c2.v[34] += (sum_160_1_073)*MainFormSLS->hh[77];
c2.v[34] += (sum_160_1_074)*MainFormSLS->hh[146];
c2.v[34] += (sum_160_1_075)*MainFormSLS->hh[55];
c2.v[34] += (sum_160_1_076)*MainFormSLS->hh[124];
c2.v[34] += (sum_160_1_077)*MainFormSLS->hh[33];
c2.v[34] += (sum_160_1_078)*MainFormSLS->hh[102];
c2.v[34] += (sum_160_1_079)*MainFormSLS->hh[11];
c2.v[34] += (sum_160_1_080)*MainFormSLS->hh[80];
c2.v[34] += (sum_160_1_081)*MainFormSLS->hh[149];
c2.v[34] += (sum_160_1_082)*MainFormSLS->hh[58];
c2.v[34] += (sum_160_1_083)*MainFormSLS->hh[127];
c2.v[34] += (sum_160_1_084)*MainFormSLS->hh[36];
c2.v[34] += (sum_160_1_085)*MainFormSLS->hh[105];
c2.v[34] += (sum_160_1_086)*MainFormSLS->hh[14];
c2.v[34] += (sum_160_1_087)*MainFormSLS->hh[83];
c2.v[34] += (sum_160_1_088)*MainFormSLS->hh[152];
c2.v[34] += (sum_160_1_089)*MainFormSLS->hh[61];
c2.v[34] += (sum_160_1_090)*MainFormSLS->hh[130];
c2.v[34] += (sum_160_1_091)*MainFormSLS->hh[39];
c2.v[34] += (sum_160_1_092)*MainFormSLS->hh[108];
c2.v[34] += (sum_160_1_093)*MainFormSLS->hh[17];
c2.v[34] += (sum_160_1_094)*MainFormSLS->hh[86];
c2.v[34] += (sum_160_1_095)*MainFormSLS->hh[155];
c2.v[34] += (sum_160_1_096)*MainFormSLS->hh[64];
c2.v[34] += (sum_160_1_097)*MainFormSLS->hh[133];
c2.v[34] += (sum_160_1_098)*MainFormSLS->hh[42];
c2.v[34] += (sum_160_1_099)*MainFormSLS->hh[111];
c2.v[34] += (sum_160_1_100)*MainFormSLS->hh[20];
c2.v[34] += (sum_160_1_101)*MainFormSLS->hh[89];
c2.v[34] += (sum_160_1_102)*MainFormSLS->hh[158];
c2.v[34] += (sum_160_1_103)*MainFormSLS->hh[67];
c2.v[34] += (sum_160_1_104)*MainFormSLS->hh[136];
c2.v[34] += (sum_160_1_105)*MainFormSLS->hh[45];
c2.v[34] += (sum_160_1_106)*MainFormSLS->hh[114];
c2.v[34] += (sum_160_1_107)*MainFormSLS->hh[23];
c2.v[34] += (sum_160_1_108)*MainFormSLS->hh[92];
c2.v[34] += (sum_160_1_109)*MainFormSLS->hh[1];
c2.v[34] += (sum_160_1_110)*MainFormSLS->hh[70];
c2.v[34] += (sum_160_1_111)*MainFormSLS->hh[139];
c2.v[34] += (sum_160_1_112)*MainFormSLS->hh[48];
c2.v[34] += (sum_160_1_113)*MainFormSLS->hh[117];
c2.v[34] += (sum_160_1_114)*MainFormSLS->hh[26];
c2.v[34] += (sum_160_1_115)*MainFormSLS->hh[95];
c2.v[34] += (sum_160_1_116)*MainFormSLS->hh[4];
c2.v[34] += (sum_160_1_117)*MainFormSLS->hh[73];
c2.v[34] += (sum_160_1_118)*MainFormSLS->hh[142];
c2.v[34] += (sum_160_1_119)*MainFormSLS->hh[51];
c2.v[34] += (sum_160_1_120)*MainFormSLS->hh[120];
c2.v[34] += (sum_160_1_121)*MainFormSLS->hh[29];
c2.v[34] += (sum_160_1_122)*MainFormSLS->hh[98];
c2.v[34] += (sum_160_1_123)*MainFormSLS->hh[7];
c2.v[34] += (sum_160_1_124)*MainFormSLS->hh[76];
c2.v[34] += (sum_160_1_125)*MainFormSLS->hh[145];
c2.v[34] += (sum_160_1_126)*MainFormSLS->hh[54];
c2.v[34] += (sum_160_1_127)*MainFormSLS->hh[123];
c2.v[34] += (sum_160_1_128)*MainFormSLS->hh[32];
c2.v[34] += (sum_160_1_129)*MainFormSLS->hh[101];
c2.v[34] += (sum_160_1_130)*MainFormSLS->hh[10];
c2.v[34] += (sum_160_1_131)*MainFormSLS->hh[79];
c2.v[34] += (sum_160_1_132)*MainFormSLS->hh[148];
c2.v[34] += (sum_160_1_133)*MainFormSLS->hh[57];
c2.v[34] += (sum_160_1_134)*MainFormSLS->hh[126];
c2.v[34] += (sum_160_1_135)*MainFormSLS->hh[35];
c2.v[34] += (sum_160_1_136)*MainFormSLS->hh[104];
c2.v[34] += (sum_160_1_137)*MainFormSLS->hh[13];
c2.v[34] += (sum_160_1_138)*MainFormSLS->hh[82];
c2.v[34] += (sum_160_1_139)*MainFormSLS->hh[151];
c2.v[34] += (sum_160_1_140)*MainFormSLS->hh[60];
c2.v[34] += (sum_160_1_141)*MainFormSLS->hh[129];
c2.v[34] += (sum_160_1_142)*MainFormSLS->hh[38];
c2.v[34] += (sum_160_1_143)*MainFormSLS->hh[107];
c2.v[34] += (sum_160_1_144)*MainFormSLS->hh[16];
c2.v[34] += (sum_160_1_145)*MainFormSLS->hh[85];
c2.v[34] += (sum_160_1_146)*MainFormSLS->hh[154];
c2.v[34] += (sum_160_1_147)*MainFormSLS->hh[63];
c2.v[34] += (sum_160_1_148)*MainFormSLS->hh[132];
c2.v[34] += (sum_160_1_149)*MainFormSLS->hh[41];
c2.v[34] += (sum_160_1_150)*MainFormSLS->hh[110];
c2.v[34] += (sum_160_1_151)*MainFormSLS->hh[19];
c2.v[34] += (sum_160_1_152)*MainFormSLS->hh[88];
c2.v[34] += (sum_160_1_153)*MainFormSLS->hh[157];
c2.v[34] += (sum_160_1_154)*MainFormSLS->hh[66];
c2.v[34] += (sum_160_1_155)*MainFormSLS->hh[135];
c2.v[34] += (sum_160_1_156)*MainFormSLS->hh[44];
c2.v[34] += (sum_160_1_157)*MainFormSLS->hh[113];
c2.v[34] += (sum_160_1_158)*MainFormSLS->hh[22];
c2.v[34] += (sum_160_1_159)*MainFormSLS->hh[91];

//frequency level id 71
c2.v[35] += (sum_160_1_000)*MainFormSLS->hh[0];
c2.v[35] += (sum_160_1_001)*MainFormSLS->hh[71];
c2.v[35] += (sum_160_1_002)*MainFormSLS->hh[142];
c2.v[35] += (sum_160_1_003)*MainFormSLS->hh[53];
c2.v[35] += (sum_160_1_004)*MainFormSLS->hh[124];
c2.v[35] += (sum_160_1_005)*MainFormSLS->hh[35];
c2.v[35] += (sum_160_1_006)*MainFormSLS->hh[106];
c2.v[35] += (sum_160_1_007)*MainFormSLS->hh[17];
c2.v[35] += (sum_160_1_008)*MainFormSLS->hh[88];
c2.v[35] += (sum_160_1_009)*MainFormSLS->hh[159];
c2.v[35] += (sum_160_1_010)*MainFormSLS->hh[70];
c2.v[35] += (sum_160_1_011)*MainFormSLS->hh[141];
c2.v[35] += (sum_160_1_012)*MainFormSLS->hh[52];
c2.v[35] += (sum_160_1_013)*MainFormSLS->hh[123];
c2.v[35] += (sum_160_1_014)*MainFormSLS->hh[34];
c2.v[35] += (sum_160_1_015)*MainFormSLS->hh[105];
c2.v[35] += (sum_160_1_016)*MainFormSLS->hh[16];
c2.v[35] += (sum_160_1_017)*MainFormSLS->hh[87];
c2.v[35] += (sum_160_1_018)*MainFormSLS->hh[158];
c2.v[35] += (sum_160_1_019)*MainFormSLS->hh[69];
c2.v[35] += (sum_160_1_020)*MainFormSLS->hh[140];
c2.v[35] += (sum_160_1_021)*MainFormSLS->hh[51];
c2.v[35] += (sum_160_1_022)*MainFormSLS->hh[122];
c2.v[35] += (sum_160_1_023)*MainFormSLS->hh[33];
c2.v[35] += (sum_160_1_024)*MainFormSLS->hh[104];
c2.v[35] += (sum_160_1_025)*MainFormSLS->hh[15];
c2.v[35] += (sum_160_1_026)*MainFormSLS->hh[86];
c2.v[35] += (sum_160_1_027)*MainFormSLS->hh[157];
c2.v[35] += (sum_160_1_028)*MainFormSLS->hh[68];
c2.v[35] += (sum_160_1_029)*MainFormSLS->hh[139];
c2.v[35] += (sum_160_1_030)*MainFormSLS->hh[50];
c2.v[35] += (sum_160_1_031)*MainFormSLS->hh[121];
c2.v[35] += (sum_160_1_032)*MainFormSLS->hh[32];
c2.v[35] += (sum_160_1_033)*MainFormSLS->hh[103];
c2.v[35] += (sum_160_1_034)*MainFormSLS->hh[14];
c2.v[35] += (sum_160_1_035)*MainFormSLS->hh[85];
c2.v[35] += (sum_160_1_036)*MainFormSLS->hh[156];
c2.v[35] += (sum_160_1_037)*MainFormSLS->hh[67];
c2.v[35] += (sum_160_1_038)*MainFormSLS->hh[138];
c2.v[35] += (sum_160_1_039)*MainFormSLS->hh[49];
c2.v[35] += (sum_160_1_040)*MainFormSLS->hh[120];
c2.v[35] += (sum_160_1_041)*MainFormSLS->hh[31];
c2.v[35] += (sum_160_1_042)*MainFormSLS->hh[102];
c2.v[35] += (sum_160_1_043)*MainFormSLS->hh[13];
c2.v[35] += (sum_160_1_044)*MainFormSLS->hh[84];
c2.v[35] += (sum_160_1_045)*MainFormSLS->hh[155];
c2.v[35] += (sum_160_1_046)*MainFormSLS->hh[66];
c2.v[35] += (sum_160_1_047)*MainFormSLS->hh[137];
c2.v[35] += (sum_160_1_048)*MainFormSLS->hh[48];
c2.v[35] += (sum_160_1_049)*MainFormSLS->hh[119];
c2.v[35] += (sum_160_1_050)*MainFormSLS->hh[30];
c2.v[35] += (sum_160_1_051)*MainFormSLS->hh[101];
c2.v[35] += (sum_160_1_052)*MainFormSLS->hh[12];
c2.v[35] += (sum_160_1_053)*MainFormSLS->hh[83];
c2.v[35] += (sum_160_1_054)*MainFormSLS->hh[154];
c2.v[35] += (sum_160_1_055)*MainFormSLS->hh[65];
c2.v[35] += (sum_160_1_056)*MainFormSLS->hh[136];
c2.v[35] += (sum_160_1_057)*MainFormSLS->hh[47];
c2.v[35] += (sum_160_1_058)*MainFormSLS->hh[118];
c2.v[35] += (sum_160_1_059)*MainFormSLS->hh[29];
c2.v[35] += (sum_160_1_060)*MainFormSLS->hh[100];
c2.v[35] += (sum_160_1_061)*MainFormSLS->hh[11];
c2.v[35] += (sum_160_1_062)*MainFormSLS->hh[82];
c2.v[35] += (sum_160_1_063)*MainFormSLS->hh[153];
c2.v[35] += (sum_160_1_064)*MainFormSLS->hh[64];
c2.v[35] += (sum_160_1_065)*MainFormSLS->hh[135];
c2.v[35] += (sum_160_1_066)*MainFormSLS->hh[46];
c2.v[35] += (sum_160_1_067)*MainFormSLS->hh[117];
c2.v[35] += (sum_160_1_068)*MainFormSLS->hh[28];
c2.v[35] += (sum_160_1_069)*MainFormSLS->hh[99];
c2.v[35] += (sum_160_1_070)*MainFormSLS->hh[10];
c2.v[35] += (sum_160_1_071)*MainFormSLS->hh[81];
c2.v[35] += (sum_160_1_072)*MainFormSLS->hh[152];
c2.v[35] += (sum_160_1_073)*MainFormSLS->hh[63];
c2.v[35] += (sum_160_1_074)*MainFormSLS->hh[134];
c2.v[35] += (sum_160_1_075)*MainFormSLS->hh[45];
c2.v[35] += (sum_160_1_076)*MainFormSLS->hh[116];
c2.v[35] += (sum_160_1_077)*MainFormSLS->hh[27];
c2.v[35] += (sum_160_1_078)*MainFormSLS->hh[98];
c2.v[35] += (sum_160_1_079)*MainFormSLS->hh[9];
c2.v[35] += (sum_160_1_080)*MainFormSLS->hh[80];
c2.v[35] += (sum_160_1_081)*MainFormSLS->hh[151];
c2.v[35] += (sum_160_1_082)*MainFormSLS->hh[62];
c2.v[35] += (sum_160_1_083)*MainFormSLS->hh[133];
c2.v[35] += (sum_160_1_084)*MainFormSLS->hh[44];
c2.v[35] += (sum_160_1_085)*MainFormSLS->hh[115];
c2.v[35] += (sum_160_1_086)*MainFormSLS->hh[26];
c2.v[35] += (sum_160_1_087)*MainFormSLS->hh[97];
c2.v[35] += (sum_160_1_088)*MainFormSLS->hh[8];
c2.v[35] += (sum_160_1_089)*MainFormSLS->hh[79];
c2.v[35] += (sum_160_1_090)*MainFormSLS->hh[150];
c2.v[35] += (sum_160_1_091)*MainFormSLS->hh[61];
c2.v[35] += (sum_160_1_092)*MainFormSLS->hh[132];
c2.v[35] += (sum_160_1_093)*MainFormSLS->hh[43];
c2.v[35] += (sum_160_1_094)*MainFormSLS->hh[114];
c2.v[35] += (sum_160_1_095)*MainFormSLS->hh[25];
c2.v[35] += (sum_160_1_096)*MainFormSLS->hh[96];
c2.v[35] += (sum_160_1_097)*MainFormSLS->hh[7];
c2.v[35] += (sum_160_1_098)*MainFormSLS->hh[78];
c2.v[35] += (sum_160_1_099)*MainFormSLS->hh[149];
c2.v[35] += (sum_160_1_100)*MainFormSLS->hh[60];
c2.v[35] += (sum_160_1_101)*MainFormSLS->hh[131];
c2.v[35] += (sum_160_1_102)*MainFormSLS->hh[42];
c2.v[35] += (sum_160_1_103)*MainFormSLS->hh[113];
c2.v[35] += (sum_160_1_104)*MainFormSLS->hh[24];
c2.v[35] += (sum_160_1_105)*MainFormSLS->hh[95];
c2.v[35] += (sum_160_1_106)*MainFormSLS->hh[6];
c2.v[35] += (sum_160_1_107)*MainFormSLS->hh[77];
c2.v[35] += (sum_160_1_108)*MainFormSLS->hh[148];
c2.v[35] += (sum_160_1_109)*MainFormSLS->hh[59];
c2.v[35] += (sum_160_1_110)*MainFormSLS->hh[130];
c2.v[35] += (sum_160_1_111)*MainFormSLS->hh[41];
c2.v[35] += (sum_160_1_112)*MainFormSLS->hh[112];
c2.v[35] += (sum_160_1_113)*MainFormSLS->hh[23];
c2.v[35] += (sum_160_1_114)*MainFormSLS->hh[94];
c2.v[35] += (sum_160_1_115)*MainFormSLS->hh[5];
c2.v[35] += (sum_160_1_116)*MainFormSLS->hh[76];
c2.v[35] += (sum_160_1_117)*MainFormSLS->hh[147];
c2.v[35] += (sum_160_1_118)*MainFormSLS->hh[58];
c2.v[35] += (sum_160_1_119)*MainFormSLS->hh[129];
c2.v[35] += (sum_160_1_120)*MainFormSLS->hh[40];
c2.v[35] += (sum_160_1_121)*MainFormSLS->hh[111];
c2.v[35] += (sum_160_1_122)*MainFormSLS->hh[22];
c2.v[35] += (sum_160_1_123)*MainFormSLS->hh[93];
c2.v[35] += (sum_160_1_124)*MainFormSLS->hh[4];
c2.v[35] += (sum_160_1_125)*MainFormSLS->hh[75];
c2.v[35] += (sum_160_1_126)*MainFormSLS->hh[146];
c2.v[35] += (sum_160_1_127)*MainFormSLS->hh[57];
c2.v[35] += (sum_160_1_128)*MainFormSLS->hh[128];
c2.v[35] += (sum_160_1_129)*MainFormSLS->hh[39];
c2.v[35] += (sum_160_1_130)*MainFormSLS->hh[110];
c2.v[35] += (sum_160_1_131)*MainFormSLS->hh[21];
c2.v[35] += (sum_160_1_132)*MainFormSLS->hh[92];
c2.v[35] += (sum_160_1_133)*MainFormSLS->hh[3];
c2.v[35] += (sum_160_1_134)*MainFormSLS->hh[74];
c2.v[35] += (sum_160_1_135)*MainFormSLS->hh[145];
c2.v[35] += (sum_160_1_136)*MainFormSLS->hh[56];
c2.v[35] += (sum_160_1_137)*MainFormSLS->hh[127];
c2.v[35] += (sum_160_1_138)*MainFormSLS->hh[38];
c2.v[35] += (sum_160_1_139)*MainFormSLS->hh[109];
c2.v[35] += (sum_160_1_140)*MainFormSLS->hh[20];
c2.v[35] += (sum_160_1_141)*MainFormSLS->hh[91];
c2.v[35] += (sum_160_1_142)*MainFormSLS->hh[2];
c2.v[35] += (sum_160_1_143)*MainFormSLS->hh[73];
c2.v[35] += (sum_160_1_144)*MainFormSLS->hh[144];
c2.v[35] += (sum_160_1_145)*MainFormSLS->hh[55];
c2.v[35] += (sum_160_1_146)*MainFormSLS->hh[126];
c2.v[35] += (sum_160_1_147)*MainFormSLS->hh[37];
c2.v[35] += (sum_160_1_148)*MainFormSLS->hh[108];
c2.v[35] += (sum_160_1_149)*MainFormSLS->hh[19];
c2.v[35] += (sum_160_1_150)*MainFormSLS->hh[90];
c2.v[35] += (sum_160_1_151)*MainFormSLS->hh[1];
c2.v[35] += (sum_160_1_152)*MainFormSLS->hh[72];
c2.v[35] += (sum_160_1_153)*MainFormSLS->hh[143];
c2.v[35] += (sum_160_1_154)*MainFormSLS->hh[54];
c2.v[35] += (sum_160_1_155)*MainFormSLS->hh[125];
c2.v[35] += (sum_160_1_156)*MainFormSLS->hh[36];
c2.v[35] += (sum_160_1_157)*MainFormSLS->hh[107];
c2.v[35] += (sum_160_1_158)*MainFormSLS->hh[18];
c2.v[35] += (sum_160_1_159)*MainFormSLS->hh[89];

//frequency level id 73
c2.v[36] += (sum_160_1_000)*MainFormSLS->hh[0];
c2.v[36] += (sum_160_1_001)*MainFormSLS->hh[73];
c2.v[36] += (sum_160_1_002)*MainFormSLS->hh[146];
c2.v[36] += (sum_160_1_003)*MainFormSLS->hh[59];
c2.v[36] += (sum_160_1_004)*MainFormSLS->hh[132];
c2.v[36] += (sum_160_1_005)*MainFormSLS->hh[45];
c2.v[36] += (sum_160_1_006)*MainFormSLS->hh[118];
c2.v[36] += (sum_160_1_007)*MainFormSLS->hh[31];
c2.v[36] += (sum_160_1_008)*MainFormSLS->hh[104];
c2.v[36] += (sum_160_1_009)*MainFormSLS->hh[17];
c2.v[36] += (sum_160_1_010)*MainFormSLS->hh[90];
c2.v[36] += (sum_160_1_011)*MainFormSLS->hh[3];
c2.v[36] += (sum_160_1_012)*MainFormSLS->hh[76];
c2.v[36] += (sum_160_1_013)*MainFormSLS->hh[149];
c2.v[36] += (sum_160_1_014)*MainFormSLS->hh[62];
c2.v[36] += (sum_160_1_015)*MainFormSLS->hh[135];
c2.v[36] += (sum_160_1_016)*MainFormSLS->hh[48];
c2.v[36] += (sum_160_1_017)*MainFormSLS->hh[121];
c2.v[36] += (sum_160_1_018)*MainFormSLS->hh[34];
c2.v[36] += (sum_160_1_019)*MainFormSLS->hh[107];
c2.v[36] += (sum_160_1_020)*MainFormSLS->hh[20];
c2.v[36] += (sum_160_1_021)*MainFormSLS->hh[93];
c2.v[36] += (sum_160_1_022)*MainFormSLS->hh[6];
c2.v[36] += (sum_160_1_023)*MainFormSLS->hh[79];
c2.v[36] += (sum_160_1_024)*MainFormSLS->hh[152];
c2.v[36] += (sum_160_1_025)*MainFormSLS->hh[65];
c2.v[36] += (sum_160_1_026)*MainFormSLS->hh[138];
c2.v[36] += (sum_160_1_027)*MainFormSLS->hh[51];
c2.v[36] += (sum_160_1_028)*MainFormSLS->hh[124];
c2.v[36] += (sum_160_1_029)*MainFormSLS->hh[37];
c2.v[36] += (sum_160_1_030)*MainFormSLS->hh[110];
c2.v[36] += (sum_160_1_031)*MainFormSLS->hh[23];
c2.v[36] += (sum_160_1_032)*MainFormSLS->hh[96];
c2.v[36] += (sum_160_1_033)*MainFormSLS->hh[9];
c2.v[36] += (sum_160_1_034)*MainFormSLS->hh[82];
c2.v[36] += (sum_160_1_035)*MainFormSLS->hh[155];
c2.v[36] += (sum_160_1_036)*MainFormSLS->hh[68];
c2.v[36] += (sum_160_1_037)*MainFormSLS->hh[141];
c2.v[36] += (sum_160_1_038)*MainFormSLS->hh[54];
c2.v[36] += (sum_160_1_039)*MainFormSLS->hh[127];
c2.v[36] += (sum_160_1_040)*MainFormSLS->hh[40];
c2.v[36] += (sum_160_1_041)*MainFormSLS->hh[113];
c2.v[36] += (sum_160_1_042)*MainFormSLS->hh[26];
c2.v[36] += (sum_160_1_043)*MainFormSLS->hh[99];
c2.v[36] += (sum_160_1_044)*MainFormSLS->hh[12];
c2.v[36] += (sum_160_1_045)*MainFormSLS->hh[85];
c2.v[36] += (sum_160_1_046)*MainFormSLS->hh[158];
c2.v[36] += (sum_160_1_047)*MainFormSLS->hh[71];
c2.v[36] += (sum_160_1_048)*MainFormSLS->hh[144];
c2.v[36] += (sum_160_1_049)*MainFormSLS->hh[57];
c2.v[36] += (sum_160_1_050)*MainFormSLS->hh[130];
c2.v[36] += (sum_160_1_051)*MainFormSLS->hh[43];
c2.v[36] += (sum_160_1_052)*MainFormSLS->hh[116];
c2.v[36] += (sum_160_1_053)*MainFormSLS->hh[29];
c2.v[36] += (sum_160_1_054)*MainFormSLS->hh[102];
c2.v[36] += (sum_160_1_055)*MainFormSLS->hh[15];
c2.v[36] += (sum_160_1_056)*MainFormSLS->hh[88];
c2.v[36] += (sum_160_1_057)*MainFormSLS->hh[1];
c2.v[36] += (sum_160_1_058)*MainFormSLS->hh[74];
c2.v[36] += (sum_160_1_059)*MainFormSLS->hh[147];
c2.v[36] += (sum_160_1_060)*MainFormSLS->hh[60];
c2.v[36] += (sum_160_1_061)*MainFormSLS->hh[133];
c2.v[36] += (sum_160_1_062)*MainFormSLS->hh[46];
c2.v[36] += (sum_160_1_063)*MainFormSLS->hh[119];
c2.v[36] += (sum_160_1_064)*MainFormSLS->hh[32];
c2.v[36] += (sum_160_1_065)*MainFormSLS->hh[105];
c2.v[36] += (sum_160_1_066)*MainFormSLS->hh[18];
c2.v[36] += (sum_160_1_067)*MainFormSLS->hh[91];
c2.v[36] += (sum_160_1_068)*MainFormSLS->hh[4];
c2.v[36] += (sum_160_1_069)*MainFormSLS->hh[77];
c2.v[36] += (sum_160_1_070)*MainFormSLS->hh[150];
c2.v[36] += (sum_160_1_071)*MainFormSLS->hh[63];
c2.v[36] += (sum_160_1_072)*MainFormSLS->hh[136];
c2.v[36] += (sum_160_1_073)*MainFormSLS->hh[49];
c2.v[36] += (sum_160_1_074)*MainFormSLS->hh[122];
c2.v[36] += (sum_160_1_075)*MainFormSLS->hh[35];
c2.v[36] += (sum_160_1_076)*MainFormSLS->hh[108];
c2.v[36] += (sum_160_1_077)*MainFormSLS->hh[21];
c2.v[36] += (sum_160_1_078)*MainFormSLS->hh[94];
c2.v[36] += (sum_160_1_079)*MainFormSLS->hh[7];
c2.v[36] += (sum_160_1_080)*MainFormSLS->hh[80];
c2.v[36] += (sum_160_1_081)*MainFormSLS->hh[153];
c2.v[36] += (sum_160_1_082)*MainFormSLS->hh[66];
c2.v[36] += (sum_160_1_083)*MainFormSLS->hh[139];
c2.v[36] += (sum_160_1_084)*MainFormSLS->hh[52];
c2.v[36] += (sum_160_1_085)*MainFormSLS->hh[125];
c2.v[36] += (sum_160_1_086)*MainFormSLS->hh[38];
c2.v[36] += (sum_160_1_087)*MainFormSLS->hh[111];
c2.v[36] += (sum_160_1_088)*MainFormSLS->hh[24];
c2.v[36] += (sum_160_1_089)*MainFormSLS->hh[97];
c2.v[36] += (sum_160_1_090)*MainFormSLS->hh[10];
c2.v[36] += (sum_160_1_091)*MainFormSLS->hh[83];
c2.v[36] += (sum_160_1_092)*MainFormSLS->hh[156];
c2.v[36] += (sum_160_1_093)*MainFormSLS->hh[69];
c2.v[36] += (sum_160_1_094)*MainFormSLS->hh[142];
c2.v[36] += (sum_160_1_095)*MainFormSLS->hh[55];
c2.v[36] += (sum_160_1_096)*MainFormSLS->hh[128];
c2.v[36] += (sum_160_1_097)*MainFormSLS->hh[41];
c2.v[36] += (sum_160_1_098)*MainFormSLS->hh[114];
c2.v[36] += (sum_160_1_099)*MainFormSLS->hh[27];
c2.v[36] += (sum_160_1_100)*MainFormSLS->hh[100];
c2.v[36] += (sum_160_1_101)*MainFormSLS->hh[13];
c2.v[36] += (sum_160_1_102)*MainFormSLS->hh[86];
c2.v[36] += (sum_160_1_103)*MainFormSLS->hh[159];
c2.v[36] += (sum_160_1_104)*MainFormSLS->hh[72];
c2.v[36] += (sum_160_1_105)*MainFormSLS->hh[145];
c2.v[36] += (sum_160_1_106)*MainFormSLS->hh[58];
c2.v[36] += (sum_160_1_107)*MainFormSLS->hh[131];
c2.v[36] += (sum_160_1_108)*MainFormSLS->hh[44];
c2.v[36] += (sum_160_1_109)*MainFormSLS->hh[117];
c2.v[36] += (sum_160_1_110)*MainFormSLS->hh[30];
c2.v[36] += (sum_160_1_111)*MainFormSLS->hh[103];
c2.v[36] += (sum_160_1_112)*MainFormSLS->hh[16];
c2.v[36] += (sum_160_1_113)*MainFormSLS->hh[89];
c2.v[36] += (sum_160_1_114)*MainFormSLS->hh[2];
c2.v[36] += (sum_160_1_115)*MainFormSLS->hh[75];
c2.v[36] += (sum_160_1_116)*MainFormSLS->hh[148];
c2.v[36] += (sum_160_1_117)*MainFormSLS->hh[61];
c2.v[36] += (sum_160_1_118)*MainFormSLS->hh[134];
c2.v[36] += (sum_160_1_119)*MainFormSLS->hh[47];
c2.v[36] += (sum_160_1_120)*MainFormSLS->hh[120];
c2.v[36] += (sum_160_1_121)*MainFormSLS->hh[33];
c2.v[36] += (sum_160_1_122)*MainFormSLS->hh[106];
c2.v[36] += (sum_160_1_123)*MainFormSLS->hh[19];
c2.v[36] += (sum_160_1_124)*MainFormSLS->hh[92];
c2.v[36] += (sum_160_1_125)*MainFormSLS->hh[5];
c2.v[36] += (sum_160_1_126)*MainFormSLS->hh[78];
c2.v[36] += (sum_160_1_127)*MainFormSLS->hh[151];
c2.v[36] += (sum_160_1_128)*MainFormSLS->hh[64];
c2.v[36] += (sum_160_1_129)*MainFormSLS->hh[137];
c2.v[36] += (sum_160_1_130)*MainFormSLS->hh[50];
c2.v[36] += (sum_160_1_131)*MainFormSLS->hh[123];
c2.v[36] += (sum_160_1_132)*MainFormSLS->hh[36];
c2.v[36] += (sum_160_1_133)*MainFormSLS->hh[109];
c2.v[36] += (sum_160_1_134)*MainFormSLS->hh[22];
c2.v[36] += (sum_160_1_135)*MainFormSLS->hh[95];
c2.v[36] += (sum_160_1_136)*MainFormSLS->hh[8];
c2.v[36] += (sum_160_1_137)*MainFormSLS->hh[81];
c2.v[36] += (sum_160_1_138)*MainFormSLS->hh[154];
c2.v[36] += (sum_160_1_139)*MainFormSLS->hh[67];
c2.v[36] += (sum_160_1_140)*MainFormSLS->hh[140];
c2.v[36] += (sum_160_1_141)*MainFormSLS->hh[53];
c2.v[36] += (sum_160_1_142)*MainFormSLS->hh[126];
c2.v[36] += (sum_160_1_143)*MainFormSLS->hh[39];
c2.v[36] += (sum_160_1_144)*MainFormSLS->hh[112];
c2.v[36] += (sum_160_1_145)*MainFormSLS->hh[25];
c2.v[36] += (sum_160_1_146)*MainFormSLS->hh[98];
c2.v[36] += (sum_160_1_147)*MainFormSLS->hh[11];
c2.v[36] += (sum_160_1_148)*MainFormSLS->hh[84];
c2.v[36] += (sum_160_1_149)*MainFormSLS->hh[157];
c2.v[36] += (sum_160_1_150)*MainFormSLS->hh[70];
c2.v[36] += (sum_160_1_151)*MainFormSLS->hh[143];
c2.v[36] += (sum_160_1_152)*MainFormSLS->hh[56];
c2.v[36] += (sum_160_1_153)*MainFormSLS->hh[129];
c2.v[36] += (sum_160_1_154)*MainFormSLS->hh[42];
c2.v[36] += (sum_160_1_155)*MainFormSLS->hh[115];
c2.v[36] += (sum_160_1_156)*MainFormSLS->hh[28];
c2.v[36] += (sum_160_1_157)*MainFormSLS->hh[101];
c2.v[36] += (sum_160_1_158)*MainFormSLS->hh[14];
c2.v[36] += (sum_160_1_159)*MainFormSLS->hh[87];

//frequency level id 75
c2.v[37] += (sum_32_5_000)*MainFormSLS->hh[0];
c2.v[37] += (sum_32_5_001)*MainFormSLS->hh[75];
c2.v[37] += (sum_32_5_002)*MainFormSLS->hh[150];
c2.v[37] += (sum_32_5_003)*MainFormSLS->hh[65];
c2.v[37] += (sum_32_5_004)*MainFormSLS->hh[140];
c2.v[37] += (sum_32_5_005)*MainFormSLS->hh[55];
c2.v[37] += (sum_32_5_006)*MainFormSLS->hh[130];
c2.v[37] += (sum_32_5_007)*MainFormSLS->hh[45];
c2.v[37] += (sum_32_5_008)*MainFormSLS->hh[120];
c2.v[37] += (sum_32_5_009)*MainFormSLS->hh[35];
c2.v[37] += (sum_32_5_010)*MainFormSLS->hh[110];
c2.v[37] += (sum_32_5_011)*MainFormSLS->hh[25];
c2.v[37] += (sum_32_5_012)*MainFormSLS->hh[100];
c2.v[37] += (sum_32_5_013)*MainFormSLS->hh[15];
c2.v[37] += (sum_32_5_014)*MainFormSLS->hh[90];
c2.v[37] += (sum_32_5_015)*MainFormSLS->hh[5];
c2.v[37] += (sum_32_5_016)*MainFormSLS->hh[80];
c2.v[37] += (sum_32_5_017)*MainFormSLS->hh[155];
c2.v[37] += (sum_32_5_018)*MainFormSLS->hh[70];
c2.v[37] += (sum_32_5_019)*MainFormSLS->hh[145];
c2.v[37] += (sum_32_5_020)*MainFormSLS->hh[60];
c2.v[37] += (sum_32_5_021)*MainFormSLS->hh[135];
c2.v[37] += (sum_32_5_022)*MainFormSLS->hh[50];
c2.v[37] += (sum_32_5_023)*MainFormSLS->hh[125];
c2.v[37] += (sum_32_5_024)*MainFormSLS->hh[40];
c2.v[37] += (sum_32_5_025)*MainFormSLS->hh[115];
c2.v[37] += (sum_32_5_026)*MainFormSLS->hh[30];
c2.v[37] += (sum_32_5_027)*MainFormSLS->hh[105];
c2.v[37] += (sum_32_5_028)*MainFormSLS->hh[20];
c2.v[37] += (sum_32_5_029)*MainFormSLS->hh[95];
c2.v[37] += (sum_32_5_030)*MainFormSLS->hh[10];
c2.v[37] += (sum_32_5_031)*MainFormSLS->hh[85];

//frequency level id 77
c2.v[38] += (sum_160_1_000)*MainFormSLS->hh[0];
c2.v[38] += (sum_160_1_001)*MainFormSLS->hh[77];
c2.v[38] += (sum_160_1_002)*MainFormSLS->hh[154];
c2.v[38] += (sum_160_1_003)*MainFormSLS->hh[71];
c2.v[38] += (sum_160_1_004)*MainFormSLS->hh[148];
c2.v[38] += (sum_160_1_005)*MainFormSLS->hh[65];
c2.v[38] += (sum_160_1_006)*MainFormSLS->hh[142];
c2.v[38] += (sum_160_1_007)*MainFormSLS->hh[59];
c2.v[38] += (sum_160_1_008)*MainFormSLS->hh[136];
c2.v[38] += (sum_160_1_009)*MainFormSLS->hh[53];
c2.v[38] += (sum_160_1_010)*MainFormSLS->hh[130];
c2.v[38] += (sum_160_1_011)*MainFormSLS->hh[47];
c2.v[38] += (sum_160_1_012)*MainFormSLS->hh[124];
c2.v[38] += (sum_160_1_013)*MainFormSLS->hh[41];
c2.v[38] += (sum_160_1_014)*MainFormSLS->hh[118];
c2.v[38] += (sum_160_1_015)*MainFormSLS->hh[35];
c2.v[38] += (sum_160_1_016)*MainFormSLS->hh[112];
c2.v[38] += (sum_160_1_017)*MainFormSLS->hh[29];
c2.v[38] += (sum_160_1_018)*MainFormSLS->hh[106];
c2.v[38] += (sum_160_1_019)*MainFormSLS->hh[23];
c2.v[38] += (sum_160_1_020)*MainFormSLS->hh[100];
c2.v[38] += (sum_160_1_021)*MainFormSLS->hh[17];
c2.v[38] += (sum_160_1_022)*MainFormSLS->hh[94];
c2.v[38] += (sum_160_1_023)*MainFormSLS->hh[11];
c2.v[38] += (sum_160_1_024)*MainFormSLS->hh[88];
c2.v[38] += (sum_160_1_025)*MainFormSLS->hh[5];
c2.v[38] += (sum_160_1_026)*MainFormSLS->hh[82];
c2.v[38] += (sum_160_1_027)*MainFormSLS->hh[159];
c2.v[38] += (sum_160_1_028)*MainFormSLS->hh[76];
c2.v[38] += (sum_160_1_029)*MainFormSLS->hh[153];
c2.v[38] += (sum_160_1_030)*MainFormSLS->hh[70];
c2.v[38] += (sum_160_1_031)*MainFormSLS->hh[147];
c2.v[38] += (sum_160_1_032)*MainFormSLS->hh[64];
c2.v[38] += (sum_160_1_033)*MainFormSLS->hh[141];
c2.v[38] += (sum_160_1_034)*MainFormSLS->hh[58];
c2.v[38] += (sum_160_1_035)*MainFormSLS->hh[135];
c2.v[38] += (sum_160_1_036)*MainFormSLS->hh[52];
c2.v[38] += (sum_160_1_037)*MainFormSLS->hh[129];
c2.v[38] += (sum_160_1_038)*MainFormSLS->hh[46];
c2.v[38] += (sum_160_1_039)*MainFormSLS->hh[123];
c2.v[38] += (sum_160_1_040)*MainFormSLS->hh[40];
c2.v[38] += (sum_160_1_041)*MainFormSLS->hh[117];
c2.v[38] += (sum_160_1_042)*MainFormSLS->hh[34];
c2.v[38] += (sum_160_1_043)*MainFormSLS->hh[111];
c2.v[38] += (sum_160_1_044)*MainFormSLS->hh[28];
c2.v[38] += (sum_160_1_045)*MainFormSLS->hh[105];
c2.v[38] += (sum_160_1_046)*MainFormSLS->hh[22];
c2.v[38] += (sum_160_1_047)*MainFormSLS->hh[99];
c2.v[38] += (sum_160_1_048)*MainFormSLS->hh[16];
c2.v[38] += (sum_160_1_049)*MainFormSLS->hh[93];
c2.v[38] += (sum_160_1_050)*MainFormSLS->hh[10];
c2.v[38] += (sum_160_1_051)*MainFormSLS->hh[87];
c2.v[38] += (sum_160_1_052)*MainFormSLS->hh[4];
c2.v[38] += (sum_160_1_053)*MainFormSLS->hh[81];
c2.v[38] += (sum_160_1_054)*MainFormSLS->hh[158];
c2.v[38] += (sum_160_1_055)*MainFormSLS->hh[75];
c2.v[38] += (sum_160_1_056)*MainFormSLS->hh[152];
c2.v[38] += (sum_160_1_057)*MainFormSLS->hh[69];
c2.v[38] += (sum_160_1_058)*MainFormSLS->hh[146];
c2.v[38] += (sum_160_1_059)*MainFormSLS->hh[63];
c2.v[38] += (sum_160_1_060)*MainFormSLS->hh[140];
c2.v[38] += (sum_160_1_061)*MainFormSLS->hh[57];
c2.v[38] += (sum_160_1_062)*MainFormSLS->hh[134];
c2.v[38] += (sum_160_1_063)*MainFormSLS->hh[51];
c2.v[38] += (sum_160_1_064)*MainFormSLS->hh[128];
c2.v[38] += (sum_160_1_065)*MainFormSLS->hh[45];
c2.v[38] += (sum_160_1_066)*MainFormSLS->hh[122];
c2.v[38] += (sum_160_1_067)*MainFormSLS->hh[39];
c2.v[38] += (sum_160_1_068)*MainFormSLS->hh[116];
c2.v[38] += (sum_160_1_069)*MainFormSLS->hh[33];
c2.v[38] += (sum_160_1_070)*MainFormSLS->hh[110];
c2.v[38] += (sum_160_1_071)*MainFormSLS->hh[27];
c2.v[38] += (sum_160_1_072)*MainFormSLS->hh[104];
c2.v[38] += (sum_160_1_073)*MainFormSLS->hh[21];
c2.v[38] += (sum_160_1_074)*MainFormSLS->hh[98];
c2.v[38] += (sum_160_1_075)*MainFormSLS->hh[15];
c2.v[38] += (sum_160_1_076)*MainFormSLS->hh[92];
c2.v[38] += (sum_160_1_077)*MainFormSLS->hh[9];
c2.v[38] += (sum_160_1_078)*MainFormSLS->hh[86];
c2.v[38] += (sum_160_1_079)*MainFormSLS->hh[3];
c2.v[38] += (sum_160_1_080)*MainFormSLS->hh[80];
c2.v[38] += (sum_160_1_081)*MainFormSLS->hh[157];
c2.v[38] += (sum_160_1_082)*MainFormSLS->hh[74];
c2.v[38] += (sum_160_1_083)*MainFormSLS->hh[151];
c2.v[38] += (sum_160_1_084)*MainFormSLS->hh[68];
c2.v[38] += (sum_160_1_085)*MainFormSLS->hh[145];
c2.v[38] += (sum_160_1_086)*MainFormSLS->hh[62];
c2.v[38] += (sum_160_1_087)*MainFormSLS->hh[139];
c2.v[38] += (sum_160_1_088)*MainFormSLS->hh[56];
c2.v[38] += (sum_160_1_089)*MainFormSLS->hh[133];
c2.v[38] += (sum_160_1_090)*MainFormSLS->hh[50];
c2.v[38] += (sum_160_1_091)*MainFormSLS->hh[127];
c2.v[38] += (sum_160_1_092)*MainFormSLS->hh[44];
c2.v[38] += (sum_160_1_093)*MainFormSLS->hh[121];
c2.v[38] += (sum_160_1_094)*MainFormSLS->hh[38];
c2.v[38] += (sum_160_1_095)*MainFormSLS->hh[115];
c2.v[38] += (sum_160_1_096)*MainFormSLS->hh[32];
c2.v[38] += (sum_160_1_097)*MainFormSLS->hh[109];
c2.v[38] += (sum_160_1_098)*MainFormSLS->hh[26];
c2.v[38] += (sum_160_1_099)*MainFormSLS->hh[103];
c2.v[38] += (sum_160_1_100)*MainFormSLS->hh[20];
c2.v[38] += (sum_160_1_101)*MainFormSLS->hh[97];
c2.v[38] += (sum_160_1_102)*MainFormSLS->hh[14];
c2.v[38] += (sum_160_1_103)*MainFormSLS->hh[91];
c2.v[38] += (sum_160_1_104)*MainFormSLS->hh[8];
c2.v[38] += (sum_160_1_105)*MainFormSLS->hh[85];
c2.v[38] += (sum_160_1_106)*MainFormSLS->hh[2];
c2.v[38] += (sum_160_1_107)*MainFormSLS->hh[79];
c2.v[38] += (sum_160_1_108)*MainFormSLS->hh[156];
c2.v[38] += (sum_160_1_109)*MainFormSLS->hh[73];
c2.v[38] += (sum_160_1_110)*MainFormSLS->hh[150];
c2.v[38] += (sum_160_1_111)*MainFormSLS->hh[67];
c2.v[38] += (sum_160_1_112)*MainFormSLS->hh[144];
c2.v[38] += (sum_160_1_113)*MainFormSLS->hh[61];
c2.v[38] += (sum_160_1_114)*MainFormSLS->hh[138];
c2.v[38] += (sum_160_1_115)*MainFormSLS->hh[55];
c2.v[38] += (sum_160_1_116)*MainFormSLS->hh[132];
c2.v[38] += (sum_160_1_117)*MainFormSLS->hh[49];
c2.v[38] += (sum_160_1_118)*MainFormSLS->hh[126];
c2.v[38] += (sum_160_1_119)*MainFormSLS->hh[43];
c2.v[38] += (sum_160_1_120)*MainFormSLS->hh[120];
c2.v[38] += (sum_160_1_121)*MainFormSLS->hh[37];
c2.v[38] += (sum_160_1_122)*MainFormSLS->hh[114];
c2.v[38] += (sum_160_1_123)*MainFormSLS->hh[31];
c2.v[38] += (sum_160_1_124)*MainFormSLS->hh[108];
c2.v[38] += (sum_160_1_125)*MainFormSLS->hh[25];
c2.v[38] += (sum_160_1_126)*MainFormSLS->hh[102];
c2.v[38] += (sum_160_1_127)*MainFormSLS->hh[19];
c2.v[38] += (sum_160_1_128)*MainFormSLS->hh[96];
c2.v[38] += (sum_160_1_129)*MainFormSLS->hh[13];
c2.v[38] += (sum_160_1_130)*MainFormSLS->hh[90];
c2.v[38] += (sum_160_1_131)*MainFormSLS->hh[7];
c2.v[38] += (sum_160_1_132)*MainFormSLS->hh[84];
c2.v[38] += (sum_160_1_133)*MainFormSLS->hh[1];
c2.v[38] += (sum_160_1_134)*MainFormSLS->hh[78];
c2.v[38] += (sum_160_1_135)*MainFormSLS->hh[155];
c2.v[38] += (sum_160_1_136)*MainFormSLS->hh[72];
c2.v[38] += (sum_160_1_137)*MainFormSLS->hh[149];
c2.v[38] += (sum_160_1_138)*MainFormSLS->hh[66];
c2.v[38] += (sum_160_1_139)*MainFormSLS->hh[143];
c2.v[38] += (sum_160_1_140)*MainFormSLS->hh[60];
c2.v[38] += (sum_160_1_141)*MainFormSLS->hh[137];
c2.v[38] += (sum_160_1_142)*MainFormSLS->hh[54];
c2.v[38] += (sum_160_1_143)*MainFormSLS->hh[131];
c2.v[38] += (sum_160_1_144)*MainFormSLS->hh[48];
c2.v[38] += (sum_160_1_145)*MainFormSLS->hh[125];
c2.v[38] += (sum_160_1_146)*MainFormSLS->hh[42];
c2.v[38] += (sum_160_1_147)*MainFormSLS->hh[119];
c2.v[38] += (sum_160_1_148)*MainFormSLS->hh[36];
c2.v[38] += (sum_160_1_149)*MainFormSLS->hh[113];
c2.v[38] += (sum_160_1_150)*MainFormSLS->hh[30];
c2.v[38] += (sum_160_1_151)*MainFormSLS->hh[107];
c2.v[38] += (sum_160_1_152)*MainFormSLS->hh[24];
c2.v[38] += (sum_160_1_153)*MainFormSLS->hh[101];
c2.v[38] += (sum_160_1_154)*MainFormSLS->hh[18];
c2.v[38] += (sum_160_1_155)*MainFormSLS->hh[95];
c2.v[38] += (sum_160_1_156)*MainFormSLS->hh[12];
c2.v[38] += (sum_160_1_157)*MainFormSLS->hh[89];
c2.v[38] += (sum_160_1_158)*MainFormSLS->hh[6];
c2.v[38] += (sum_160_1_159)*MainFormSLS->hh[83];

//frequency level id 79
c2.v[39] += (sum_160_1_000)*MainFormSLS->hh[0];
c2.v[39] += (sum_160_1_001)*MainFormSLS->hh[79];
c2.v[39] += (sum_160_1_002)*MainFormSLS->hh[158];
c2.v[39] += (sum_160_1_003)*MainFormSLS->hh[77];
c2.v[39] += (sum_160_1_004)*MainFormSLS->hh[156];
c2.v[39] += (sum_160_1_005)*MainFormSLS->hh[75];
c2.v[39] += (sum_160_1_006)*MainFormSLS->hh[154];
c2.v[39] += (sum_160_1_007)*MainFormSLS->hh[73];
c2.v[39] += (sum_160_1_008)*MainFormSLS->hh[152];
c2.v[39] += (sum_160_1_009)*MainFormSLS->hh[71];
c2.v[39] += (sum_160_1_010)*MainFormSLS->hh[150];
c2.v[39] += (sum_160_1_011)*MainFormSLS->hh[69];
c2.v[39] += (sum_160_1_012)*MainFormSLS->hh[148];
c2.v[39] += (sum_160_1_013)*MainFormSLS->hh[67];
c2.v[39] += (sum_160_1_014)*MainFormSLS->hh[146];
c2.v[39] += (sum_160_1_015)*MainFormSLS->hh[65];
c2.v[39] += (sum_160_1_016)*MainFormSLS->hh[144];
c2.v[39] += (sum_160_1_017)*MainFormSLS->hh[63];
c2.v[39] += (sum_160_1_018)*MainFormSLS->hh[142];
c2.v[39] += (sum_160_1_019)*MainFormSLS->hh[61];
c2.v[39] += (sum_160_1_020)*MainFormSLS->hh[140];
c2.v[39] += (sum_160_1_021)*MainFormSLS->hh[59];
c2.v[39] += (sum_160_1_022)*MainFormSLS->hh[138];
c2.v[39] += (sum_160_1_023)*MainFormSLS->hh[57];
c2.v[39] += (sum_160_1_024)*MainFormSLS->hh[136];
c2.v[39] += (sum_160_1_025)*MainFormSLS->hh[55];
c2.v[39] += (sum_160_1_026)*MainFormSLS->hh[134];
c2.v[39] += (sum_160_1_027)*MainFormSLS->hh[53];
c2.v[39] += (sum_160_1_028)*MainFormSLS->hh[132];
c2.v[39] += (sum_160_1_029)*MainFormSLS->hh[51];
c2.v[39] += (sum_160_1_030)*MainFormSLS->hh[130];
c2.v[39] += (sum_160_1_031)*MainFormSLS->hh[49];
c2.v[39] += (sum_160_1_032)*MainFormSLS->hh[128];
c2.v[39] += (sum_160_1_033)*MainFormSLS->hh[47];
c2.v[39] += (sum_160_1_034)*MainFormSLS->hh[126];
c2.v[39] += (sum_160_1_035)*MainFormSLS->hh[45];
c2.v[39] += (sum_160_1_036)*MainFormSLS->hh[124];
c2.v[39] += (sum_160_1_037)*MainFormSLS->hh[43];
c2.v[39] += (sum_160_1_038)*MainFormSLS->hh[122];
c2.v[39] += (sum_160_1_039)*MainFormSLS->hh[41];
c2.v[39] += (sum_160_1_040)*MainFormSLS->hh[120];
c2.v[39] += (sum_160_1_041)*MainFormSLS->hh[39];
c2.v[39] += (sum_160_1_042)*MainFormSLS->hh[118];
c2.v[39] += (sum_160_1_043)*MainFormSLS->hh[37];
c2.v[39] += (sum_160_1_044)*MainFormSLS->hh[116];
c2.v[39] += (sum_160_1_045)*MainFormSLS->hh[35];
c2.v[39] += (sum_160_1_046)*MainFormSLS->hh[114];
c2.v[39] += (sum_160_1_047)*MainFormSLS->hh[33];
c2.v[39] += (sum_160_1_048)*MainFormSLS->hh[112];
c2.v[39] += (sum_160_1_049)*MainFormSLS->hh[31];
c2.v[39] += (sum_160_1_050)*MainFormSLS->hh[110];
c2.v[39] += (sum_160_1_051)*MainFormSLS->hh[29];
c2.v[39] += (sum_160_1_052)*MainFormSLS->hh[108];
c2.v[39] += (sum_160_1_053)*MainFormSLS->hh[27];
c2.v[39] += (sum_160_1_054)*MainFormSLS->hh[106];
c2.v[39] += (sum_160_1_055)*MainFormSLS->hh[25];
c2.v[39] += (sum_160_1_056)*MainFormSLS->hh[104];
c2.v[39] += (sum_160_1_057)*MainFormSLS->hh[23];
c2.v[39] += (sum_160_1_058)*MainFormSLS->hh[102];
c2.v[39] += (sum_160_1_059)*MainFormSLS->hh[21];
c2.v[39] += (sum_160_1_060)*MainFormSLS->hh[100];
c2.v[39] += (sum_160_1_061)*MainFormSLS->hh[19];
c2.v[39] += (sum_160_1_062)*MainFormSLS->hh[98];
c2.v[39] += (sum_160_1_063)*MainFormSLS->hh[17];
c2.v[39] += (sum_160_1_064)*MainFormSLS->hh[96];
c2.v[39] += (sum_160_1_065)*MainFormSLS->hh[15];
c2.v[39] += (sum_160_1_066)*MainFormSLS->hh[94];
c2.v[39] += (sum_160_1_067)*MainFormSLS->hh[13];
c2.v[39] += (sum_160_1_068)*MainFormSLS->hh[92];
c2.v[39] += (sum_160_1_069)*MainFormSLS->hh[11];
c2.v[39] += (sum_160_1_070)*MainFormSLS->hh[90];
c2.v[39] += (sum_160_1_071)*MainFormSLS->hh[9];
c2.v[39] += (sum_160_1_072)*MainFormSLS->hh[88];
c2.v[39] += (sum_160_1_073)*MainFormSLS->hh[7];
c2.v[39] += (sum_160_1_074)*MainFormSLS->hh[86];
c2.v[39] += (sum_160_1_075)*MainFormSLS->hh[5];
c2.v[39] += (sum_160_1_076)*MainFormSLS->hh[84];
c2.v[39] += (sum_160_1_077)*MainFormSLS->hh[3];
c2.v[39] += (sum_160_1_078)*MainFormSLS->hh[82];
c2.v[39] += (sum_160_1_079)*MainFormSLS->hh[1];
c2.v[39] += (sum_160_1_080)*MainFormSLS->hh[80];
c2.v[39] += (sum_160_1_081)*MainFormSLS->hh[159];
c2.v[39] += (sum_160_1_082)*MainFormSLS->hh[78];
c2.v[39] += (sum_160_1_083)*MainFormSLS->hh[157];
c2.v[39] += (sum_160_1_084)*MainFormSLS->hh[76];
c2.v[39] += (sum_160_1_085)*MainFormSLS->hh[155];
c2.v[39] += (sum_160_1_086)*MainFormSLS->hh[74];
c2.v[39] += (sum_160_1_087)*MainFormSLS->hh[153];
c2.v[39] += (sum_160_1_088)*MainFormSLS->hh[72];
c2.v[39] += (sum_160_1_089)*MainFormSLS->hh[151];
c2.v[39] += (sum_160_1_090)*MainFormSLS->hh[70];
c2.v[39] += (sum_160_1_091)*MainFormSLS->hh[149];
c2.v[39] += (sum_160_1_092)*MainFormSLS->hh[68];
c2.v[39] += (sum_160_1_093)*MainFormSLS->hh[147];
c2.v[39] += (sum_160_1_094)*MainFormSLS->hh[66];
c2.v[39] += (sum_160_1_095)*MainFormSLS->hh[145];
c2.v[39] += (sum_160_1_096)*MainFormSLS->hh[64];
c2.v[39] += (sum_160_1_097)*MainFormSLS->hh[143];
c2.v[39] += (sum_160_1_098)*MainFormSLS->hh[62];
c2.v[39] += (sum_160_1_099)*MainFormSLS->hh[141];
c2.v[39] += (sum_160_1_100)*MainFormSLS->hh[60];
c2.v[39] += (sum_160_1_101)*MainFormSLS->hh[139];
c2.v[39] += (sum_160_1_102)*MainFormSLS->hh[58];
c2.v[39] += (sum_160_1_103)*MainFormSLS->hh[137];
c2.v[39] += (sum_160_1_104)*MainFormSLS->hh[56];
c2.v[39] += (sum_160_1_105)*MainFormSLS->hh[135];
c2.v[39] += (sum_160_1_106)*MainFormSLS->hh[54];
c2.v[39] += (sum_160_1_107)*MainFormSLS->hh[133];
c2.v[39] += (sum_160_1_108)*MainFormSLS->hh[52];
c2.v[39] += (sum_160_1_109)*MainFormSLS->hh[131];
c2.v[39] += (sum_160_1_110)*MainFormSLS->hh[50];
c2.v[39] += (sum_160_1_111)*MainFormSLS->hh[129];
c2.v[39] += (sum_160_1_112)*MainFormSLS->hh[48];
c2.v[39] += (sum_160_1_113)*MainFormSLS->hh[127];
c2.v[39] += (sum_160_1_114)*MainFormSLS->hh[46];
c2.v[39] += (sum_160_1_115)*MainFormSLS->hh[125];
c2.v[39] += (sum_160_1_116)*MainFormSLS->hh[44];
c2.v[39] += (sum_160_1_117)*MainFormSLS->hh[123];
c2.v[39] += (sum_160_1_118)*MainFormSLS->hh[42];
c2.v[39] += (sum_160_1_119)*MainFormSLS->hh[121];
c2.v[39] += (sum_160_1_120)*MainFormSLS->hh[40];
c2.v[39] += (sum_160_1_121)*MainFormSLS->hh[119];
c2.v[39] += (sum_160_1_122)*MainFormSLS->hh[38];
c2.v[39] += (sum_160_1_123)*MainFormSLS->hh[117];
c2.v[39] += (sum_160_1_124)*MainFormSLS->hh[36];
c2.v[39] += (sum_160_1_125)*MainFormSLS->hh[115];
c2.v[39] += (sum_160_1_126)*MainFormSLS->hh[34];
c2.v[39] += (sum_160_1_127)*MainFormSLS->hh[113];
c2.v[39] += (sum_160_1_128)*MainFormSLS->hh[32];
c2.v[39] += (sum_160_1_129)*MainFormSLS->hh[111];
c2.v[39] += (sum_160_1_130)*MainFormSLS->hh[30];
c2.v[39] += (sum_160_1_131)*MainFormSLS->hh[109];
c2.v[39] += (sum_160_1_132)*MainFormSLS->hh[28];
c2.v[39] += (sum_160_1_133)*MainFormSLS->hh[107];
c2.v[39] += (sum_160_1_134)*MainFormSLS->hh[26];
c2.v[39] += (sum_160_1_135)*MainFormSLS->hh[105];
c2.v[39] += (sum_160_1_136)*MainFormSLS->hh[24];
c2.v[39] += (sum_160_1_137)*MainFormSLS->hh[103];
c2.v[39] += (sum_160_1_138)*MainFormSLS->hh[22];
c2.v[39] += (sum_160_1_139)*MainFormSLS->hh[101];
c2.v[39] += (sum_160_1_140)*MainFormSLS->hh[20];
c2.v[39] += (sum_160_1_141)*MainFormSLS->hh[99];
c2.v[39] += (sum_160_1_142)*MainFormSLS->hh[18];
c2.v[39] += (sum_160_1_143)*MainFormSLS->hh[97];
c2.v[39] += (sum_160_1_144)*MainFormSLS->hh[16];
c2.v[39] += (sum_160_1_145)*MainFormSLS->hh[95];
c2.v[39] += (sum_160_1_146)*MainFormSLS->hh[14];
c2.v[39] += (sum_160_1_147)*MainFormSLS->hh[93];
c2.v[39] += (sum_160_1_148)*MainFormSLS->hh[12];
c2.v[39] += (sum_160_1_149)*MainFormSLS->hh[91];
c2.v[39] += (sum_160_1_150)*MainFormSLS->hh[10];
c2.v[39] += (sum_160_1_151)*MainFormSLS->hh[89];
c2.v[39] += (sum_160_1_152)*MainFormSLS->hh[8];
c2.v[39] += (sum_160_1_153)*MainFormSLS->hh[87];
c2.v[39] += (sum_160_1_154)*MainFormSLS->hh[6];
c2.v[39] += (sum_160_1_155)*MainFormSLS->hh[85];
c2.v[39] += (sum_160_1_156)*MainFormSLS->hh[4];
c2.v[39] += (sum_160_1_157)*MainFormSLS->hh[83];
c2.v[39] += (sum_160_1_158)*MainFormSLS->hh[2];
c2.v[39] += (sum_160_1_159)*MainFormSLS->hh[81];

//frequency level id 81
c2.v[40] += (sum_160_1_000)*MainFormSLS->hh[0];
c2.v[40] += (sum_160_1_001)*MainFormSLS->hh[81];
c2.v[40] += (sum_160_1_002)*MainFormSLS->hh[2];
c2.v[40] += (sum_160_1_003)*MainFormSLS->hh[83];
c2.v[40] += (sum_160_1_004)*MainFormSLS->hh[4];
c2.v[40] += (sum_160_1_005)*MainFormSLS->hh[85];
c2.v[40] += (sum_160_1_006)*MainFormSLS->hh[6];
c2.v[40] += (sum_160_1_007)*MainFormSLS->hh[87];
c2.v[40] += (sum_160_1_008)*MainFormSLS->hh[8];
c2.v[40] += (sum_160_1_009)*MainFormSLS->hh[89];
c2.v[40] += (sum_160_1_010)*MainFormSLS->hh[10];
c2.v[40] += (sum_160_1_011)*MainFormSLS->hh[91];
c2.v[40] += (sum_160_1_012)*MainFormSLS->hh[12];
c2.v[40] += (sum_160_1_013)*MainFormSLS->hh[93];
c2.v[40] += (sum_160_1_014)*MainFormSLS->hh[14];
c2.v[40] += (sum_160_1_015)*MainFormSLS->hh[95];
c2.v[40] += (sum_160_1_016)*MainFormSLS->hh[16];
c2.v[40] += (sum_160_1_017)*MainFormSLS->hh[97];
c2.v[40] += (sum_160_1_018)*MainFormSLS->hh[18];
c2.v[40] += (sum_160_1_019)*MainFormSLS->hh[99];
c2.v[40] += (sum_160_1_020)*MainFormSLS->hh[20];
c2.v[40] += (sum_160_1_021)*MainFormSLS->hh[101];
c2.v[40] += (sum_160_1_022)*MainFormSLS->hh[22];
c2.v[40] += (sum_160_1_023)*MainFormSLS->hh[103];
c2.v[40] += (sum_160_1_024)*MainFormSLS->hh[24];
c2.v[40] += (sum_160_1_025)*MainFormSLS->hh[105];
c2.v[40] += (sum_160_1_026)*MainFormSLS->hh[26];
c2.v[40] += (sum_160_1_027)*MainFormSLS->hh[107];
c2.v[40] += (sum_160_1_028)*MainFormSLS->hh[28];
c2.v[40] += (sum_160_1_029)*MainFormSLS->hh[109];
c2.v[40] += (sum_160_1_030)*MainFormSLS->hh[30];
c2.v[40] += (sum_160_1_031)*MainFormSLS->hh[111];
c2.v[40] += (sum_160_1_032)*MainFormSLS->hh[32];
c2.v[40] += (sum_160_1_033)*MainFormSLS->hh[113];
c2.v[40] += (sum_160_1_034)*MainFormSLS->hh[34];
c2.v[40] += (sum_160_1_035)*MainFormSLS->hh[115];
c2.v[40] += (sum_160_1_036)*MainFormSLS->hh[36];
c2.v[40] += (sum_160_1_037)*MainFormSLS->hh[117];
c2.v[40] += (sum_160_1_038)*MainFormSLS->hh[38];
c2.v[40] += (sum_160_1_039)*MainFormSLS->hh[119];
c2.v[40] += (sum_160_1_040)*MainFormSLS->hh[40];
c2.v[40] += (sum_160_1_041)*MainFormSLS->hh[121];
c2.v[40] += (sum_160_1_042)*MainFormSLS->hh[42];
c2.v[40] += (sum_160_1_043)*MainFormSLS->hh[123];
c2.v[40] += (sum_160_1_044)*MainFormSLS->hh[44];
c2.v[40] += (sum_160_1_045)*MainFormSLS->hh[125];
c2.v[40] += (sum_160_1_046)*MainFormSLS->hh[46];
c2.v[40] += (sum_160_1_047)*MainFormSLS->hh[127];
c2.v[40] += (sum_160_1_048)*MainFormSLS->hh[48];
c2.v[40] += (sum_160_1_049)*MainFormSLS->hh[129];
c2.v[40] += (sum_160_1_050)*MainFormSLS->hh[50];
c2.v[40] += (sum_160_1_051)*MainFormSLS->hh[131];
c2.v[40] += (sum_160_1_052)*MainFormSLS->hh[52];
c2.v[40] += (sum_160_1_053)*MainFormSLS->hh[133];
c2.v[40] += (sum_160_1_054)*MainFormSLS->hh[54];
c2.v[40] += (sum_160_1_055)*MainFormSLS->hh[135];
c2.v[40] += (sum_160_1_056)*MainFormSLS->hh[56];
c2.v[40] += (sum_160_1_057)*MainFormSLS->hh[137];
c2.v[40] += (sum_160_1_058)*MainFormSLS->hh[58];
c2.v[40] += (sum_160_1_059)*MainFormSLS->hh[139];
c2.v[40] += (sum_160_1_060)*MainFormSLS->hh[60];
c2.v[40] += (sum_160_1_061)*MainFormSLS->hh[141];
c2.v[40] += (sum_160_1_062)*MainFormSLS->hh[62];
c2.v[40] += (sum_160_1_063)*MainFormSLS->hh[143];
c2.v[40] += (sum_160_1_064)*MainFormSLS->hh[64];
c2.v[40] += (sum_160_1_065)*MainFormSLS->hh[145];
c2.v[40] += (sum_160_1_066)*MainFormSLS->hh[66];
c2.v[40] += (sum_160_1_067)*MainFormSLS->hh[147];
c2.v[40] += (sum_160_1_068)*MainFormSLS->hh[68];
c2.v[40] += (sum_160_1_069)*MainFormSLS->hh[149];
c2.v[40] += (sum_160_1_070)*MainFormSLS->hh[70];
c2.v[40] += (sum_160_1_071)*MainFormSLS->hh[151];
c2.v[40] += (sum_160_1_072)*MainFormSLS->hh[72];
c2.v[40] += (sum_160_1_073)*MainFormSLS->hh[153];
c2.v[40] += (sum_160_1_074)*MainFormSLS->hh[74];
c2.v[40] += (sum_160_1_075)*MainFormSLS->hh[155];
c2.v[40] += (sum_160_1_076)*MainFormSLS->hh[76];
c2.v[40] += (sum_160_1_077)*MainFormSLS->hh[157];
c2.v[40] += (sum_160_1_078)*MainFormSLS->hh[78];
c2.v[40] += (sum_160_1_079)*MainFormSLS->hh[159];
c2.v[40] += (sum_160_1_080)*MainFormSLS->hh[80];
c2.v[40] += (sum_160_1_081)*MainFormSLS->hh[1];
c2.v[40] += (sum_160_1_082)*MainFormSLS->hh[82];
c2.v[40] += (sum_160_1_083)*MainFormSLS->hh[3];
c2.v[40] += (sum_160_1_084)*MainFormSLS->hh[84];
c2.v[40] += (sum_160_1_085)*MainFormSLS->hh[5];
c2.v[40] += (sum_160_1_086)*MainFormSLS->hh[86];
c2.v[40] += (sum_160_1_087)*MainFormSLS->hh[7];
c2.v[40] += (sum_160_1_088)*MainFormSLS->hh[88];
c2.v[40] += (sum_160_1_089)*MainFormSLS->hh[9];
c2.v[40] += (sum_160_1_090)*MainFormSLS->hh[90];
c2.v[40] += (sum_160_1_091)*MainFormSLS->hh[11];
c2.v[40] += (sum_160_1_092)*MainFormSLS->hh[92];
c2.v[40] += (sum_160_1_093)*MainFormSLS->hh[13];
c2.v[40] += (sum_160_1_094)*MainFormSLS->hh[94];
c2.v[40] += (sum_160_1_095)*MainFormSLS->hh[15];
c2.v[40] += (sum_160_1_096)*MainFormSLS->hh[96];
c2.v[40] += (sum_160_1_097)*MainFormSLS->hh[17];
c2.v[40] += (sum_160_1_098)*MainFormSLS->hh[98];
c2.v[40] += (sum_160_1_099)*MainFormSLS->hh[19];
c2.v[40] += (sum_160_1_100)*MainFormSLS->hh[100];
c2.v[40] += (sum_160_1_101)*MainFormSLS->hh[21];
c2.v[40] += (sum_160_1_102)*MainFormSLS->hh[102];
c2.v[40] += (sum_160_1_103)*MainFormSLS->hh[23];
c2.v[40] += (sum_160_1_104)*MainFormSLS->hh[104];
c2.v[40] += (sum_160_1_105)*MainFormSLS->hh[25];
c2.v[40] += (sum_160_1_106)*MainFormSLS->hh[106];
c2.v[40] += (sum_160_1_107)*MainFormSLS->hh[27];
c2.v[40] += (sum_160_1_108)*MainFormSLS->hh[108];
c2.v[40] += (sum_160_1_109)*MainFormSLS->hh[29];
c2.v[40] += (sum_160_1_110)*MainFormSLS->hh[110];
c2.v[40] += (sum_160_1_111)*MainFormSLS->hh[31];
c2.v[40] += (sum_160_1_112)*MainFormSLS->hh[112];
c2.v[40] += (sum_160_1_113)*MainFormSLS->hh[33];
c2.v[40] += (sum_160_1_114)*MainFormSLS->hh[114];
c2.v[40] += (sum_160_1_115)*MainFormSLS->hh[35];
c2.v[40] += (sum_160_1_116)*MainFormSLS->hh[116];
c2.v[40] += (sum_160_1_117)*MainFormSLS->hh[37];
c2.v[40] += (sum_160_1_118)*MainFormSLS->hh[118];
c2.v[40] += (sum_160_1_119)*MainFormSLS->hh[39];
c2.v[40] += (sum_160_1_120)*MainFormSLS->hh[120];
c2.v[40] += (sum_160_1_121)*MainFormSLS->hh[41];
c2.v[40] += (sum_160_1_122)*MainFormSLS->hh[122];
c2.v[40] += (sum_160_1_123)*MainFormSLS->hh[43];
c2.v[40] += (sum_160_1_124)*MainFormSLS->hh[124];
c2.v[40] += (sum_160_1_125)*MainFormSLS->hh[45];
c2.v[40] += (sum_160_1_126)*MainFormSLS->hh[126];
c2.v[40] += (sum_160_1_127)*MainFormSLS->hh[47];
c2.v[40] += (sum_160_1_128)*MainFormSLS->hh[128];
c2.v[40] += (sum_160_1_129)*MainFormSLS->hh[49];
c2.v[40] += (sum_160_1_130)*MainFormSLS->hh[130];
c2.v[40] += (sum_160_1_131)*MainFormSLS->hh[51];
c2.v[40] += (sum_160_1_132)*MainFormSLS->hh[132];
c2.v[40] += (sum_160_1_133)*MainFormSLS->hh[53];
c2.v[40] += (sum_160_1_134)*MainFormSLS->hh[134];
c2.v[40] += (sum_160_1_135)*MainFormSLS->hh[55];
c2.v[40] += (sum_160_1_136)*MainFormSLS->hh[136];
c2.v[40] += (sum_160_1_137)*MainFormSLS->hh[57];
c2.v[40] += (sum_160_1_138)*MainFormSLS->hh[138];
c2.v[40] += (sum_160_1_139)*MainFormSLS->hh[59];
c2.v[40] += (sum_160_1_140)*MainFormSLS->hh[140];
c2.v[40] += (sum_160_1_141)*MainFormSLS->hh[61];
c2.v[40] += (sum_160_1_142)*MainFormSLS->hh[142];
c2.v[40] += (sum_160_1_143)*MainFormSLS->hh[63];
c2.v[40] += (sum_160_1_144)*MainFormSLS->hh[144];
c2.v[40] += (sum_160_1_145)*MainFormSLS->hh[65];
c2.v[40] += (sum_160_1_146)*MainFormSLS->hh[146];
c2.v[40] += (sum_160_1_147)*MainFormSLS->hh[67];
c2.v[40] += (sum_160_1_148)*MainFormSLS->hh[148];
c2.v[40] += (sum_160_1_149)*MainFormSLS->hh[69];
c2.v[40] += (sum_160_1_150)*MainFormSLS->hh[150];
c2.v[40] += (sum_160_1_151)*MainFormSLS->hh[71];
c2.v[40] += (sum_160_1_152)*MainFormSLS->hh[152];
c2.v[40] += (sum_160_1_153)*MainFormSLS->hh[73];
c2.v[40] += (sum_160_1_154)*MainFormSLS->hh[154];
c2.v[40] += (sum_160_1_155)*MainFormSLS->hh[75];
c2.v[40] += (sum_160_1_156)*MainFormSLS->hh[156];
c2.v[40] += (sum_160_1_157)*MainFormSLS->hh[77];
c2.v[40] += (sum_160_1_158)*MainFormSLS->hh[158];
c2.v[40] += (sum_160_1_159)*MainFormSLS->hh[79];

//frequency level id 83
c2.v[41] += (sum_160_1_000)*MainFormSLS->hh[0];
c2.v[41] += (sum_160_1_001)*MainFormSLS->hh[83];
c2.v[41] += (sum_160_1_002)*MainFormSLS->hh[6];
c2.v[41] += (sum_160_1_003)*MainFormSLS->hh[89];
c2.v[41] += (sum_160_1_004)*MainFormSLS->hh[12];
c2.v[41] += (sum_160_1_005)*MainFormSLS->hh[95];
c2.v[41] += (sum_160_1_006)*MainFormSLS->hh[18];
c2.v[41] += (sum_160_1_007)*MainFormSLS->hh[101];
c2.v[41] += (sum_160_1_008)*MainFormSLS->hh[24];
c2.v[41] += (sum_160_1_009)*MainFormSLS->hh[107];
c2.v[41] += (sum_160_1_010)*MainFormSLS->hh[30];
c2.v[41] += (sum_160_1_011)*MainFormSLS->hh[113];
c2.v[41] += (sum_160_1_012)*MainFormSLS->hh[36];
c2.v[41] += (sum_160_1_013)*MainFormSLS->hh[119];
c2.v[41] += (sum_160_1_014)*MainFormSLS->hh[42];
c2.v[41] += (sum_160_1_015)*MainFormSLS->hh[125];
c2.v[41] += (sum_160_1_016)*MainFormSLS->hh[48];
c2.v[41] += (sum_160_1_017)*MainFormSLS->hh[131];
c2.v[41] += (sum_160_1_018)*MainFormSLS->hh[54];
c2.v[41] += (sum_160_1_019)*MainFormSLS->hh[137];
c2.v[41] += (sum_160_1_020)*MainFormSLS->hh[60];
c2.v[41] += (sum_160_1_021)*MainFormSLS->hh[143];
c2.v[41] += (sum_160_1_022)*MainFormSLS->hh[66];
c2.v[41] += (sum_160_1_023)*MainFormSLS->hh[149];
c2.v[41] += (sum_160_1_024)*MainFormSLS->hh[72];
c2.v[41] += (sum_160_1_025)*MainFormSLS->hh[155];
c2.v[41] += (sum_160_1_026)*MainFormSLS->hh[78];
c2.v[41] += (sum_160_1_027)*MainFormSLS->hh[1];
c2.v[41] += (sum_160_1_028)*MainFormSLS->hh[84];
c2.v[41] += (sum_160_1_029)*MainFormSLS->hh[7];
c2.v[41] += (sum_160_1_030)*MainFormSLS->hh[90];
c2.v[41] += (sum_160_1_031)*MainFormSLS->hh[13];
c2.v[41] += (sum_160_1_032)*MainFormSLS->hh[96];
c2.v[41] += (sum_160_1_033)*MainFormSLS->hh[19];
c2.v[41] += (sum_160_1_034)*MainFormSLS->hh[102];
c2.v[41] += (sum_160_1_035)*MainFormSLS->hh[25];
c2.v[41] += (sum_160_1_036)*MainFormSLS->hh[108];
c2.v[41] += (sum_160_1_037)*MainFormSLS->hh[31];
c2.v[41] += (sum_160_1_038)*MainFormSLS->hh[114];
c2.v[41] += (sum_160_1_039)*MainFormSLS->hh[37];
c2.v[41] += (sum_160_1_040)*MainFormSLS->hh[120];
c2.v[41] += (sum_160_1_041)*MainFormSLS->hh[43];
c2.v[41] += (sum_160_1_042)*MainFormSLS->hh[126];
c2.v[41] += (sum_160_1_043)*MainFormSLS->hh[49];
c2.v[41] += (sum_160_1_044)*MainFormSLS->hh[132];
c2.v[41] += (sum_160_1_045)*MainFormSLS->hh[55];
c2.v[41] += (sum_160_1_046)*MainFormSLS->hh[138];
c2.v[41] += (sum_160_1_047)*MainFormSLS->hh[61];
c2.v[41] += (sum_160_1_048)*MainFormSLS->hh[144];
c2.v[41] += (sum_160_1_049)*MainFormSLS->hh[67];
c2.v[41] += (sum_160_1_050)*MainFormSLS->hh[150];
c2.v[41] += (sum_160_1_051)*MainFormSLS->hh[73];
c2.v[41] += (sum_160_1_052)*MainFormSLS->hh[156];
c2.v[41] += (sum_160_1_053)*MainFormSLS->hh[79];
c2.v[41] += (sum_160_1_054)*MainFormSLS->hh[2];
c2.v[41] += (sum_160_1_055)*MainFormSLS->hh[85];
c2.v[41] += (sum_160_1_056)*MainFormSLS->hh[8];
c2.v[41] += (sum_160_1_057)*MainFormSLS->hh[91];
c2.v[41] += (sum_160_1_058)*MainFormSLS->hh[14];
c2.v[41] += (sum_160_1_059)*MainFormSLS->hh[97];
c2.v[41] += (sum_160_1_060)*MainFormSLS->hh[20];
c2.v[41] += (sum_160_1_061)*MainFormSLS->hh[103];
c2.v[41] += (sum_160_1_062)*MainFormSLS->hh[26];
c2.v[41] += (sum_160_1_063)*MainFormSLS->hh[109];
c2.v[41] += (sum_160_1_064)*MainFormSLS->hh[32];
c2.v[41] += (sum_160_1_065)*MainFormSLS->hh[115];
c2.v[41] += (sum_160_1_066)*MainFormSLS->hh[38];
c2.v[41] += (sum_160_1_067)*MainFormSLS->hh[121];
c2.v[41] += (sum_160_1_068)*MainFormSLS->hh[44];
c2.v[41] += (sum_160_1_069)*MainFormSLS->hh[127];
c2.v[41] += (sum_160_1_070)*MainFormSLS->hh[50];
c2.v[41] += (sum_160_1_071)*MainFormSLS->hh[133];
c2.v[41] += (sum_160_1_072)*MainFormSLS->hh[56];
c2.v[41] += (sum_160_1_073)*MainFormSLS->hh[139];
c2.v[41] += (sum_160_1_074)*MainFormSLS->hh[62];
c2.v[41] += (sum_160_1_075)*MainFormSLS->hh[145];
c2.v[41] += (sum_160_1_076)*MainFormSLS->hh[68];
c2.v[41] += (sum_160_1_077)*MainFormSLS->hh[151];
c2.v[41] += (sum_160_1_078)*MainFormSLS->hh[74];
c2.v[41] += (sum_160_1_079)*MainFormSLS->hh[157];
c2.v[41] += (sum_160_1_080)*MainFormSLS->hh[80];
c2.v[41] += (sum_160_1_081)*MainFormSLS->hh[3];
c2.v[41] += (sum_160_1_082)*MainFormSLS->hh[86];
c2.v[41] += (sum_160_1_083)*MainFormSLS->hh[9];
c2.v[41] += (sum_160_1_084)*MainFormSLS->hh[92];
c2.v[41] += (sum_160_1_085)*MainFormSLS->hh[15];
c2.v[41] += (sum_160_1_086)*MainFormSLS->hh[98];
c2.v[41] += (sum_160_1_087)*MainFormSLS->hh[21];
c2.v[41] += (sum_160_1_088)*MainFormSLS->hh[104];
c2.v[41] += (sum_160_1_089)*MainFormSLS->hh[27];
c2.v[41] += (sum_160_1_090)*MainFormSLS->hh[110];
c2.v[41] += (sum_160_1_091)*MainFormSLS->hh[33];
c2.v[41] += (sum_160_1_092)*MainFormSLS->hh[116];
c2.v[41] += (sum_160_1_093)*MainFormSLS->hh[39];
c2.v[41] += (sum_160_1_094)*MainFormSLS->hh[122];
c2.v[41] += (sum_160_1_095)*MainFormSLS->hh[45];
c2.v[41] += (sum_160_1_096)*MainFormSLS->hh[128];
c2.v[41] += (sum_160_1_097)*MainFormSLS->hh[51];
c2.v[41] += (sum_160_1_098)*MainFormSLS->hh[134];
c2.v[41] += (sum_160_1_099)*MainFormSLS->hh[57];
c2.v[41] += (sum_160_1_100)*MainFormSLS->hh[140];
c2.v[41] += (sum_160_1_101)*MainFormSLS->hh[63];
c2.v[41] += (sum_160_1_102)*MainFormSLS->hh[146];
c2.v[41] += (sum_160_1_103)*MainFormSLS->hh[69];
c2.v[41] += (sum_160_1_104)*MainFormSLS->hh[152];
c2.v[41] += (sum_160_1_105)*MainFormSLS->hh[75];
c2.v[41] += (sum_160_1_106)*MainFormSLS->hh[158];
c2.v[41] += (sum_160_1_107)*MainFormSLS->hh[81];
c2.v[41] += (sum_160_1_108)*MainFormSLS->hh[4];
c2.v[41] += (sum_160_1_109)*MainFormSLS->hh[87];
c2.v[41] += (sum_160_1_110)*MainFormSLS->hh[10];
c2.v[41] += (sum_160_1_111)*MainFormSLS->hh[93];
c2.v[41] += (sum_160_1_112)*MainFormSLS->hh[16];
c2.v[41] += (sum_160_1_113)*MainFormSLS->hh[99];
c2.v[41] += (sum_160_1_114)*MainFormSLS->hh[22];
c2.v[41] += (sum_160_1_115)*MainFormSLS->hh[105];
c2.v[41] += (sum_160_1_116)*MainFormSLS->hh[28];
c2.v[41] += (sum_160_1_117)*MainFormSLS->hh[111];
c2.v[41] += (sum_160_1_118)*MainFormSLS->hh[34];
c2.v[41] += (sum_160_1_119)*MainFormSLS->hh[117];
c2.v[41] += (sum_160_1_120)*MainFormSLS->hh[40];
c2.v[41] += (sum_160_1_121)*MainFormSLS->hh[123];
c2.v[41] += (sum_160_1_122)*MainFormSLS->hh[46];
c2.v[41] += (sum_160_1_123)*MainFormSLS->hh[129];
c2.v[41] += (sum_160_1_124)*MainFormSLS->hh[52];
c2.v[41] += (sum_160_1_125)*MainFormSLS->hh[135];
c2.v[41] += (sum_160_1_126)*MainFormSLS->hh[58];
c2.v[41] += (sum_160_1_127)*MainFormSLS->hh[141];
c2.v[41] += (sum_160_1_128)*MainFormSLS->hh[64];
c2.v[41] += (sum_160_1_129)*MainFormSLS->hh[147];
c2.v[41] += (sum_160_1_130)*MainFormSLS->hh[70];
c2.v[41] += (sum_160_1_131)*MainFormSLS->hh[153];
c2.v[41] += (sum_160_1_132)*MainFormSLS->hh[76];
c2.v[41] += (sum_160_1_133)*MainFormSLS->hh[159];
c2.v[41] += (sum_160_1_134)*MainFormSLS->hh[82];
c2.v[41] += (sum_160_1_135)*MainFormSLS->hh[5];
c2.v[41] += (sum_160_1_136)*MainFormSLS->hh[88];
c2.v[41] += (sum_160_1_137)*MainFormSLS->hh[11];
c2.v[41] += (sum_160_1_138)*MainFormSLS->hh[94];
c2.v[41] += (sum_160_1_139)*MainFormSLS->hh[17];
c2.v[41] += (sum_160_1_140)*MainFormSLS->hh[100];
c2.v[41] += (sum_160_1_141)*MainFormSLS->hh[23];
c2.v[41] += (sum_160_1_142)*MainFormSLS->hh[106];
c2.v[41] += (sum_160_1_143)*MainFormSLS->hh[29];
c2.v[41] += (sum_160_1_144)*MainFormSLS->hh[112];
c2.v[41] += (sum_160_1_145)*MainFormSLS->hh[35];
c2.v[41] += (sum_160_1_146)*MainFormSLS->hh[118];
c2.v[41] += (sum_160_1_147)*MainFormSLS->hh[41];
c2.v[41] += (sum_160_1_148)*MainFormSLS->hh[124];
c2.v[41] += (sum_160_1_149)*MainFormSLS->hh[47];
c2.v[41] += (sum_160_1_150)*MainFormSLS->hh[130];
c2.v[41] += (sum_160_1_151)*MainFormSLS->hh[53];
c2.v[41] += (sum_160_1_152)*MainFormSLS->hh[136];
c2.v[41] += (sum_160_1_153)*MainFormSLS->hh[59];
c2.v[41] += (sum_160_1_154)*MainFormSLS->hh[142];
c2.v[41] += (sum_160_1_155)*MainFormSLS->hh[65];
c2.v[41] += (sum_160_1_156)*MainFormSLS->hh[148];
c2.v[41] += (sum_160_1_157)*MainFormSLS->hh[71];
c2.v[41] += (sum_160_1_158)*MainFormSLS->hh[154];
c2.v[41] += (sum_160_1_159)*MainFormSLS->hh[77];

//frequency level id 85
c2.v[42] += (sum_32_5_000)*MainFormSLS->hh[0];
c2.v[42] += (sum_32_5_001)*MainFormSLS->hh[85];
c2.v[42] += (sum_32_5_002)*MainFormSLS->hh[10];
c2.v[42] += (sum_32_5_003)*MainFormSLS->hh[95];
c2.v[42] += (sum_32_5_004)*MainFormSLS->hh[20];
c2.v[42] += (sum_32_5_005)*MainFormSLS->hh[105];
c2.v[42] += (sum_32_5_006)*MainFormSLS->hh[30];
c2.v[42] += (sum_32_5_007)*MainFormSLS->hh[115];
c2.v[42] += (sum_32_5_008)*MainFormSLS->hh[40];
c2.v[42] += (sum_32_5_009)*MainFormSLS->hh[125];
c2.v[42] += (sum_32_5_010)*MainFormSLS->hh[50];
c2.v[42] += (sum_32_5_011)*MainFormSLS->hh[135];
c2.v[42] += (sum_32_5_012)*MainFormSLS->hh[60];
c2.v[42] += (sum_32_5_013)*MainFormSLS->hh[145];
c2.v[42] += (sum_32_5_014)*MainFormSLS->hh[70];
c2.v[42] += (sum_32_5_015)*MainFormSLS->hh[155];
c2.v[42] += (sum_32_5_016)*MainFormSLS->hh[80];
c2.v[42] += (sum_32_5_017)*MainFormSLS->hh[5];
c2.v[42] += (sum_32_5_018)*MainFormSLS->hh[90];
c2.v[42] += (sum_32_5_019)*MainFormSLS->hh[15];
c2.v[42] += (sum_32_5_020)*MainFormSLS->hh[100];
c2.v[42] += (sum_32_5_021)*MainFormSLS->hh[25];
c2.v[42] += (sum_32_5_022)*MainFormSLS->hh[110];
c2.v[42] += (sum_32_5_023)*MainFormSLS->hh[35];
c2.v[42] += (sum_32_5_024)*MainFormSLS->hh[120];
c2.v[42] += (sum_32_5_025)*MainFormSLS->hh[45];
c2.v[42] += (sum_32_5_026)*MainFormSLS->hh[130];
c2.v[42] += (sum_32_5_027)*MainFormSLS->hh[55];
c2.v[42] += (sum_32_5_028)*MainFormSLS->hh[140];
c2.v[42] += (sum_32_5_029)*MainFormSLS->hh[65];
c2.v[42] += (sum_32_5_030)*MainFormSLS->hh[150];
c2.v[42] += (sum_32_5_031)*MainFormSLS->hh[75];

//frequency level id 87
c2.v[43] += (sum_160_1_000)*MainFormSLS->hh[0];
c2.v[43] += (sum_160_1_001)*MainFormSLS->hh[87];
c2.v[43] += (sum_160_1_002)*MainFormSLS->hh[14];
c2.v[43] += (sum_160_1_003)*MainFormSLS->hh[101];
c2.v[43] += (sum_160_1_004)*MainFormSLS->hh[28];
c2.v[43] += (sum_160_1_005)*MainFormSLS->hh[115];
c2.v[43] += (sum_160_1_006)*MainFormSLS->hh[42];
c2.v[43] += (sum_160_1_007)*MainFormSLS->hh[129];
c2.v[43] += (sum_160_1_008)*MainFormSLS->hh[56];
c2.v[43] += (sum_160_1_009)*MainFormSLS->hh[143];
c2.v[43] += (sum_160_1_010)*MainFormSLS->hh[70];
c2.v[43] += (sum_160_1_011)*MainFormSLS->hh[157];
c2.v[43] += (sum_160_1_012)*MainFormSLS->hh[84];
c2.v[43] += (sum_160_1_013)*MainFormSLS->hh[11];
c2.v[43] += (sum_160_1_014)*MainFormSLS->hh[98];
c2.v[43] += (sum_160_1_015)*MainFormSLS->hh[25];
c2.v[43] += (sum_160_1_016)*MainFormSLS->hh[112];
c2.v[43] += (sum_160_1_017)*MainFormSLS->hh[39];
c2.v[43] += (sum_160_1_018)*MainFormSLS->hh[126];
c2.v[43] += (sum_160_1_019)*MainFormSLS->hh[53];
c2.v[43] += (sum_160_1_020)*MainFormSLS->hh[140];
c2.v[43] += (sum_160_1_021)*MainFormSLS->hh[67];
c2.v[43] += (sum_160_1_022)*MainFormSLS->hh[154];
c2.v[43] += (sum_160_1_023)*MainFormSLS->hh[81];
c2.v[43] += (sum_160_1_024)*MainFormSLS->hh[8];
c2.v[43] += (sum_160_1_025)*MainFormSLS->hh[95];
c2.v[43] += (sum_160_1_026)*MainFormSLS->hh[22];
c2.v[43] += (sum_160_1_027)*MainFormSLS->hh[109];
c2.v[43] += (sum_160_1_028)*MainFormSLS->hh[36];
c2.v[43] += (sum_160_1_029)*MainFormSLS->hh[123];
c2.v[43] += (sum_160_1_030)*MainFormSLS->hh[50];
c2.v[43] += (sum_160_1_031)*MainFormSLS->hh[137];
c2.v[43] += (sum_160_1_032)*MainFormSLS->hh[64];
c2.v[43] += (sum_160_1_033)*MainFormSLS->hh[151];
c2.v[43] += (sum_160_1_034)*MainFormSLS->hh[78];
c2.v[43] += (sum_160_1_035)*MainFormSLS->hh[5];
c2.v[43] += (sum_160_1_036)*MainFormSLS->hh[92];
c2.v[43] += (sum_160_1_037)*MainFormSLS->hh[19];
c2.v[43] += (sum_160_1_038)*MainFormSLS->hh[106];
c2.v[43] += (sum_160_1_039)*MainFormSLS->hh[33];
c2.v[43] += (sum_160_1_040)*MainFormSLS->hh[120];
c2.v[43] += (sum_160_1_041)*MainFormSLS->hh[47];
c2.v[43] += (sum_160_1_042)*MainFormSLS->hh[134];
c2.v[43] += (sum_160_1_043)*MainFormSLS->hh[61];
c2.v[43] += (sum_160_1_044)*MainFormSLS->hh[148];
c2.v[43] += (sum_160_1_045)*MainFormSLS->hh[75];
c2.v[43] += (sum_160_1_046)*MainFormSLS->hh[2];
c2.v[43] += (sum_160_1_047)*MainFormSLS->hh[89];
c2.v[43] += (sum_160_1_048)*MainFormSLS->hh[16];
c2.v[43] += (sum_160_1_049)*MainFormSLS->hh[103];
c2.v[43] += (sum_160_1_050)*MainFormSLS->hh[30];
c2.v[43] += (sum_160_1_051)*MainFormSLS->hh[117];
c2.v[43] += (sum_160_1_052)*MainFormSLS->hh[44];
c2.v[43] += (sum_160_1_053)*MainFormSLS->hh[131];
c2.v[43] += (sum_160_1_054)*MainFormSLS->hh[58];
c2.v[43] += (sum_160_1_055)*MainFormSLS->hh[145];
c2.v[43] += (sum_160_1_056)*MainFormSLS->hh[72];
c2.v[43] += (sum_160_1_057)*MainFormSLS->hh[159];
c2.v[43] += (sum_160_1_058)*MainFormSLS->hh[86];
c2.v[43] += (sum_160_1_059)*MainFormSLS->hh[13];
c2.v[43] += (sum_160_1_060)*MainFormSLS->hh[100];
c2.v[43] += (sum_160_1_061)*MainFormSLS->hh[27];
c2.v[43] += (sum_160_1_062)*MainFormSLS->hh[114];
c2.v[43] += (sum_160_1_063)*MainFormSLS->hh[41];
c2.v[43] += (sum_160_1_064)*MainFormSLS->hh[128];
c2.v[43] += (sum_160_1_065)*MainFormSLS->hh[55];
c2.v[43] += (sum_160_1_066)*MainFormSLS->hh[142];
c2.v[43] += (sum_160_1_067)*MainFormSLS->hh[69];
c2.v[43] += (sum_160_1_068)*MainFormSLS->hh[156];
c2.v[43] += (sum_160_1_069)*MainFormSLS->hh[83];
c2.v[43] += (sum_160_1_070)*MainFormSLS->hh[10];
c2.v[43] += (sum_160_1_071)*MainFormSLS->hh[97];
c2.v[43] += (sum_160_1_072)*MainFormSLS->hh[24];
c2.v[43] += (sum_160_1_073)*MainFormSLS->hh[111];
c2.v[43] += (sum_160_1_074)*MainFormSLS->hh[38];
c2.v[43] += (sum_160_1_075)*MainFormSLS->hh[125];
c2.v[43] += (sum_160_1_076)*MainFormSLS->hh[52];
c2.v[43] += (sum_160_1_077)*MainFormSLS->hh[139];
c2.v[43] += (sum_160_1_078)*MainFormSLS->hh[66];
c2.v[43] += (sum_160_1_079)*MainFormSLS->hh[153];
c2.v[43] += (sum_160_1_080)*MainFormSLS->hh[80];
c2.v[43] += (sum_160_1_081)*MainFormSLS->hh[7];
c2.v[43] += (sum_160_1_082)*MainFormSLS->hh[94];
c2.v[43] += (sum_160_1_083)*MainFormSLS->hh[21];
c2.v[43] += (sum_160_1_084)*MainFormSLS->hh[108];
c2.v[43] += (sum_160_1_085)*MainFormSLS->hh[35];
c2.v[43] += (sum_160_1_086)*MainFormSLS->hh[122];
c2.v[43] += (sum_160_1_087)*MainFormSLS->hh[49];
c2.v[43] += (sum_160_1_088)*MainFormSLS->hh[136];
c2.v[43] += (sum_160_1_089)*MainFormSLS->hh[63];
c2.v[43] += (sum_160_1_090)*MainFormSLS->hh[150];
c2.v[43] += (sum_160_1_091)*MainFormSLS->hh[77];
c2.v[43] += (sum_160_1_092)*MainFormSLS->hh[4];
c2.v[43] += (sum_160_1_093)*MainFormSLS->hh[91];
c2.v[43] += (sum_160_1_094)*MainFormSLS->hh[18];
c2.v[43] += (sum_160_1_095)*MainFormSLS->hh[105];
c2.v[43] += (sum_160_1_096)*MainFormSLS->hh[32];
c2.v[43] += (sum_160_1_097)*MainFormSLS->hh[119];
c2.v[43] += (sum_160_1_098)*MainFormSLS->hh[46];
c2.v[43] += (sum_160_1_099)*MainFormSLS->hh[133];
c2.v[43] += (sum_160_1_100)*MainFormSLS->hh[60];
c2.v[43] += (sum_160_1_101)*MainFormSLS->hh[147];
c2.v[43] += (sum_160_1_102)*MainFormSLS->hh[74];
c2.v[43] += (sum_160_1_103)*MainFormSLS->hh[1];
c2.v[43] += (sum_160_1_104)*MainFormSLS->hh[88];
c2.v[43] += (sum_160_1_105)*MainFormSLS->hh[15];
c2.v[43] += (sum_160_1_106)*MainFormSLS->hh[102];
c2.v[43] += (sum_160_1_107)*MainFormSLS->hh[29];
c2.v[43] += (sum_160_1_108)*MainFormSLS->hh[116];
c2.v[43] += (sum_160_1_109)*MainFormSLS->hh[43];
c2.v[43] += (sum_160_1_110)*MainFormSLS->hh[130];
c2.v[43] += (sum_160_1_111)*MainFormSLS->hh[57];
c2.v[43] += (sum_160_1_112)*MainFormSLS->hh[144];
c2.v[43] += (sum_160_1_113)*MainFormSLS->hh[71];
c2.v[43] += (sum_160_1_114)*MainFormSLS->hh[158];
c2.v[43] += (sum_160_1_115)*MainFormSLS->hh[85];
c2.v[43] += (sum_160_1_116)*MainFormSLS->hh[12];
c2.v[43] += (sum_160_1_117)*MainFormSLS->hh[99];
c2.v[43] += (sum_160_1_118)*MainFormSLS->hh[26];
c2.v[43] += (sum_160_1_119)*MainFormSLS->hh[113];
c2.v[43] += (sum_160_1_120)*MainFormSLS->hh[40];
c2.v[43] += (sum_160_1_121)*MainFormSLS->hh[127];
c2.v[43] += (sum_160_1_122)*MainFormSLS->hh[54];
c2.v[43] += (sum_160_1_123)*MainFormSLS->hh[141];
c2.v[43] += (sum_160_1_124)*MainFormSLS->hh[68];
c2.v[43] += (sum_160_1_125)*MainFormSLS->hh[155];
c2.v[43] += (sum_160_1_126)*MainFormSLS->hh[82];
c2.v[43] += (sum_160_1_127)*MainFormSLS->hh[9];
c2.v[43] += (sum_160_1_128)*MainFormSLS->hh[96];
c2.v[43] += (sum_160_1_129)*MainFormSLS->hh[23];
c2.v[43] += (sum_160_1_130)*MainFormSLS->hh[110];
c2.v[43] += (sum_160_1_131)*MainFormSLS->hh[37];
c2.v[43] += (sum_160_1_132)*MainFormSLS->hh[124];
c2.v[43] += (sum_160_1_133)*MainFormSLS->hh[51];
c2.v[43] += (sum_160_1_134)*MainFormSLS->hh[138];
c2.v[43] += (sum_160_1_135)*MainFormSLS->hh[65];
c2.v[43] += (sum_160_1_136)*MainFormSLS->hh[152];
c2.v[43] += (sum_160_1_137)*MainFormSLS->hh[79];
c2.v[43] += (sum_160_1_138)*MainFormSLS->hh[6];
c2.v[43] += (sum_160_1_139)*MainFormSLS->hh[93];
c2.v[43] += (sum_160_1_140)*MainFormSLS->hh[20];
c2.v[43] += (sum_160_1_141)*MainFormSLS->hh[107];
c2.v[43] += (sum_160_1_142)*MainFormSLS->hh[34];
c2.v[43] += (sum_160_1_143)*MainFormSLS->hh[121];
c2.v[43] += (sum_160_1_144)*MainFormSLS->hh[48];
c2.v[43] += (sum_160_1_145)*MainFormSLS->hh[135];
c2.v[43] += (sum_160_1_146)*MainFormSLS->hh[62];
c2.v[43] += (sum_160_1_147)*MainFormSLS->hh[149];
c2.v[43] += (sum_160_1_148)*MainFormSLS->hh[76];
c2.v[43] += (sum_160_1_149)*MainFormSLS->hh[3];
c2.v[43] += (sum_160_1_150)*MainFormSLS->hh[90];
c2.v[43] += (sum_160_1_151)*MainFormSLS->hh[17];
c2.v[43] += (sum_160_1_152)*MainFormSLS->hh[104];
c2.v[43] += (sum_160_1_153)*MainFormSLS->hh[31];
c2.v[43] += (sum_160_1_154)*MainFormSLS->hh[118];
c2.v[43] += (sum_160_1_155)*MainFormSLS->hh[45];
c2.v[43] += (sum_160_1_156)*MainFormSLS->hh[132];
c2.v[43] += (sum_160_1_157)*MainFormSLS->hh[59];
c2.v[43] += (sum_160_1_158)*MainFormSLS->hh[146];
c2.v[43] += (sum_160_1_159)*MainFormSLS->hh[73];

//frequency level id 89
c2.v[44] += (sum_160_1_000)*MainFormSLS->hh[0];
c2.v[44] += (sum_160_1_001)*MainFormSLS->hh[89];
c2.v[44] += (sum_160_1_002)*MainFormSLS->hh[18];
c2.v[44] += (sum_160_1_003)*MainFormSLS->hh[107];
c2.v[44] += (sum_160_1_004)*MainFormSLS->hh[36];
c2.v[44] += (sum_160_1_005)*MainFormSLS->hh[125];
c2.v[44] += (sum_160_1_006)*MainFormSLS->hh[54];
c2.v[44] += (sum_160_1_007)*MainFormSLS->hh[143];
c2.v[44] += (sum_160_1_008)*MainFormSLS->hh[72];
c2.v[44] += (sum_160_1_009)*MainFormSLS->hh[1];
c2.v[44] += (sum_160_1_010)*MainFormSLS->hh[90];
c2.v[44] += (sum_160_1_011)*MainFormSLS->hh[19];
c2.v[44] += (sum_160_1_012)*MainFormSLS->hh[108];
c2.v[44] += (sum_160_1_013)*MainFormSLS->hh[37];
c2.v[44] += (sum_160_1_014)*MainFormSLS->hh[126];
c2.v[44] += (sum_160_1_015)*MainFormSLS->hh[55];
c2.v[44] += (sum_160_1_016)*MainFormSLS->hh[144];
c2.v[44] += (sum_160_1_017)*MainFormSLS->hh[73];
c2.v[44] += (sum_160_1_018)*MainFormSLS->hh[2];
c2.v[44] += (sum_160_1_019)*MainFormSLS->hh[91];
c2.v[44] += (sum_160_1_020)*MainFormSLS->hh[20];
c2.v[44] += (sum_160_1_021)*MainFormSLS->hh[109];
c2.v[44] += (sum_160_1_022)*MainFormSLS->hh[38];
c2.v[44] += (sum_160_1_023)*MainFormSLS->hh[127];
c2.v[44] += (sum_160_1_024)*MainFormSLS->hh[56];
c2.v[44] += (sum_160_1_025)*MainFormSLS->hh[145];
c2.v[44] += (sum_160_1_026)*MainFormSLS->hh[74];
c2.v[44] += (sum_160_1_027)*MainFormSLS->hh[3];
c2.v[44] += (sum_160_1_028)*MainFormSLS->hh[92];
c2.v[44] += (sum_160_1_029)*MainFormSLS->hh[21];
c2.v[44] += (sum_160_1_030)*MainFormSLS->hh[110];
c2.v[44] += (sum_160_1_031)*MainFormSLS->hh[39];
c2.v[44] += (sum_160_1_032)*MainFormSLS->hh[128];
c2.v[44] += (sum_160_1_033)*MainFormSLS->hh[57];
c2.v[44] += (sum_160_1_034)*MainFormSLS->hh[146];
c2.v[44] += (sum_160_1_035)*MainFormSLS->hh[75];
c2.v[44] += (sum_160_1_036)*MainFormSLS->hh[4];
c2.v[44] += (sum_160_1_037)*MainFormSLS->hh[93];
c2.v[44] += (sum_160_1_038)*MainFormSLS->hh[22];
c2.v[44] += (sum_160_1_039)*MainFormSLS->hh[111];
c2.v[44] += (sum_160_1_040)*MainFormSLS->hh[40];
c2.v[44] += (sum_160_1_041)*MainFormSLS->hh[129];
c2.v[44] += (sum_160_1_042)*MainFormSLS->hh[58];
c2.v[44] += (sum_160_1_043)*MainFormSLS->hh[147];
c2.v[44] += (sum_160_1_044)*MainFormSLS->hh[76];
c2.v[44] += (sum_160_1_045)*MainFormSLS->hh[5];
c2.v[44] += (sum_160_1_046)*MainFormSLS->hh[94];
c2.v[44] += (sum_160_1_047)*MainFormSLS->hh[23];
c2.v[44] += (sum_160_1_048)*MainFormSLS->hh[112];
c2.v[44] += (sum_160_1_049)*MainFormSLS->hh[41];
c2.v[44] += (sum_160_1_050)*MainFormSLS->hh[130];
c2.v[44] += (sum_160_1_051)*MainFormSLS->hh[59];
c2.v[44] += (sum_160_1_052)*MainFormSLS->hh[148];
c2.v[44] += (sum_160_1_053)*MainFormSLS->hh[77];
c2.v[44] += (sum_160_1_054)*MainFormSLS->hh[6];
c2.v[44] += (sum_160_1_055)*MainFormSLS->hh[95];
c2.v[44] += (sum_160_1_056)*MainFormSLS->hh[24];
c2.v[44] += (sum_160_1_057)*MainFormSLS->hh[113];
c2.v[44] += (sum_160_1_058)*MainFormSLS->hh[42];
c2.v[44] += (sum_160_1_059)*MainFormSLS->hh[131];
c2.v[44] += (sum_160_1_060)*MainFormSLS->hh[60];
c2.v[44] += (sum_160_1_061)*MainFormSLS->hh[149];
c2.v[44] += (sum_160_1_062)*MainFormSLS->hh[78];
c2.v[44] += (sum_160_1_063)*MainFormSLS->hh[7];
c2.v[44] += (sum_160_1_064)*MainFormSLS->hh[96];
c2.v[44] += (sum_160_1_065)*MainFormSLS->hh[25];
c2.v[44] += (sum_160_1_066)*MainFormSLS->hh[114];
c2.v[44] += (sum_160_1_067)*MainFormSLS->hh[43];
c2.v[44] += (sum_160_1_068)*MainFormSLS->hh[132];
c2.v[44] += (sum_160_1_069)*MainFormSLS->hh[61];
c2.v[44] += (sum_160_1_070)*MainFormSLS->hh[150];
c2.v[44] += (sum_160_1_071)*MainFormSLS->hh[79];
c2.v[44] += (sum_160_1_072)*MainFormSLS->hh[8];
c2.v[44] += (sum_160_1_073)*MainFormSLS->hh[97];
c2.v[44] += (sum_160_1_074)*MainFormSLS->hh[26];
c2.v[44] += (sum_160_1_075)*MainFormSLS->hh[115];
c2.v[44] += (sum_160_1_076)*MainFormSLS->hh[44];
c2.v[44] += (sum_160_1_077)*MainFormSLS->hh[133];
c2.v[44] += (sum_160_1_078)*MainFormSLS->hh[62];
c2.v[44] += (sum_160_1_079)*MainFormSLS->hh[151];
c2.v[44] += (sum_160_1_080)*MainFormSLS->hh[80];
c2.v[44] += (sum_160_1_081)*MainFormSLS->hh[9];
c2.v[44] += (sum_160_1_082)*MainFormSLS->hh[98];
c2.v[44] += (sum_160_1_083)*MainFormSLS->hh[27];
c2.v[44] += (sum_160_1_084)*MainFormSLS->hh[116];
c2.v[44] += (sum_160_1_085)*MainFormSLS->hh[45];
c2.v[44] += (sum_160_1_086)*MainFormSLS->hh[134];
c2.v[44] += (sum_160_1_087)*MainFormSLS->hh[63];
c2.v[44] += (sum_160_1_088)*MainFormSLS->hh[152];
c2.v[44] += (sum_160_1_089)*MainFormSLS->hh[81];
c2.v[44] += (sum_160_1_090)*MainFormSLS->hh[10];
c2.v[44] += (sum_160_1_091)*MainFormSLS->hh[99];
c2.v[44] += (sum_160_1_092)*MainFormSLS->hh[28];
c2.v[44] += (sum_160_1_093)*MainFormSLS->hh[117];
c2.v[44] += (sum_160_1_094)*MainFormSLS->hh[46];
c2.v[44] += (sum_160_1_095)*MainFormSLS->hh[135];
c2.v[44] += (sum_160_1_096)*MainFormSLS->hh[64];
c2.v[44] += (sum_160_1_097)*MainFormSLS->hh[153];
c2.v[44] += (sum_160_1_098)*MainFormSLS->hh[82];
c2.v[44] += (sum_160_1_099)*MainFormSLS->hh[11];
c2.v[44] += (sum_160_1_100)*MainFormSLS->hh[100];
c2.v[44] += (sum_160_1_101)*MainFormSLS->hh[29];
c2.v[44] += (sum_160_1_102)*MainFormSLS->hh[118];
c2.v[44] += (sum_160_1_103)*MainFormSLS->hh[47];
c2.v[44] += (sum_160_1_104)*MainFormSLS->hh[136];
c2.v[44] += (sum_160_1_105)*MainFormSLS->hh[65];
c2.v[44] += (sum_160_1_106)*MainFormSLS->hh[154];
c2.v[44] += (sum_160_1_107)*MainFormSLS->hh[83];
c2.v[44] += (sum_160_1_108)*MainFormSLS->hh[12];
c2.v[44] += (sum_160_1_109)*MainFormSLS->hh[101];
c2.v[44] += (sum_160_1_110)*MainFormSLS->hh[30];
c2.v[44] += (sum_160_1_111)*MainFormSLS->hh[119];
c2.v[44] += (sum_160_1_112)*MainFormSLS->hh[48];
c2.v[44] += (sum_160_1_113)*MainFormSLS->hh[137];
c2.v[44] += (sum_160_1_114)*MainFormSLS->hh[66];
c2.v[44] += (sum_160_1_115)*MainFormSLS->hh[155];
c2.v[44] += (sum_160_1_116)*MainFormSLS->hh[84];
c2.v[44] += (sum_160_1_117)*MainFormSLS->hh[13];
c2.v[44] += (sum_160_1_118)*MainFormSLS->hh[102];
c2.v[44] += (sum_160_1_119)*MainFormSLS->hh[31];
c2.v[44] += (sum_160_1_120)*MainFormSLS->hh[120];
c2.v[44] += (sum_160_1_121)*MainFormSLS->hh[49];
c2.v[44] += (sum_160_1_122)*MainFormSLS->hh[138];
c2.v[44] += (sum_160_1_123)*MainFormSLS->hh[67];
c2.v[44] += (sum_160_1_124)*MainFormSLS->hh[156];
c2.v[44] += (sum_160_1_125)*MainFormSLS->hh[85];
c2.v[44] += (sum_160_1_126)*MainFormSLS->hh[14];
c2.v[44] += (sum_160_1_127)*MainFormSLS->hh[103];
c2.v[44] += (sum_160_1_128)*MainFormSLS->hh[32];
c2.v[44] += (sum_160_1_129)*MainFormSLS->hh[121];
c2.v[44] += (sum_160_1_130)*MainFormSLS->hh[50];
c2.v[44] += (sum_160_1_131)*MainFormSLS->hh[139];
c2.v[44] += (sum_160_1_132)*MainFormSLS->hh[68];
c2.v[44] += (sum_160_1_133)*MainFormSLS->hh[157];
c2.v[44] += (sum_160_1_134)*MainFormSLS->hh[86];
c2.v[44] += (sum_160_1_135)*MainFormSLS->hh[15];
c2.v[44] += (sum_160_1_136)*MainFormSLS->hh[104];
c2.v[44] += (sum_160_1_137)*MainFormSLS->hh[33];
c2.v[44] += (sum_160_1_138)*MainFormSLS->hh[122];
c2.v[44] += (sum_160_1_139)*MainFormSLS->hh[51];
c2.v[44] += (sum_160_1_140)*MainFormSLS->hh[140];
c2.v[44] += (sum_160_1_141)*MainFormSLS->hh[69];
c2.v[44] += (sum_160_1_142)*MainFormSLS->hh[158];
c2.v[44] += (sum_160_1_143)*MainFormSLS->hh[87];
c2.v[44] += (sum_160_1_144)*MainFormSLS->hh[16];
c2.v[44] += (sum_160_1_145)*MainFormSLS->hh[105];
c2.v[44] += (sum_160_1_146)*MainFormSLS->hh[34];
c2.v[44] += (sum_160_1_147)*MainFormSLS->hh[123];
c2.v[44] += (sum_160_1_148)*MainFormSLS->hh[52];
c2.v[44] += (sum_160_1_149)*MainFormSLS->hh[141];
c2.v[44] += (sum_160_1_150)*MainFormSLS->hh[70];
c2.v[44] += (sum_160_1_151)*MainFormSLS->hh[159];
c2.v[44] += (sum_160_1_152)*MainFormSLS->hh[88];
c2.v[44] += (sum_160_1_153)*MainFormSLS->hh[17];
c2.v[44] += (sum_160_1_154)*MainFormSLS->hh[106];
c2.v[44] += (sum_160_1_155)*MainFormSLS->hh[35];
c2.v[44] += (sum_160_1_156)*MainFormSLS->hh[124];
c2.v[44] += (sum_160_1_157)*MainFormSLS->hh[53];
c2.v[44] += (sum_160_1_158)*MainFormSLS->hh[142];
c2.v[44] += (sum_160_1_159)*MainFormSLS->hh[71];

//frequency level id 91
c2.v[45] += (sum_160_1_000)*MainFormSLS->hh[0];
c2.v[45] += (sum_160_1_001)*MainFormSLS->hh[91];
c2.v[45] += (sum_160_1_002)*MainFormSLS->hh[22];
c2.v[45] += (sum_160_1_003)*MainFormSLS->hh[113];
c2.v[45] += (sum_160_1_004)*MainFormSLS->hh[44];
c2.v[45] += (sum_160_1_005)*MainFormSLS->hh[135];
c2.v[45] += (sum_160_1_006)*MainFormSLS->hh[66];
c2.v[45] += (sum_160_1_007)*MainFormSLS->hh[157];
c2.v[45] += (sum_160_1_008)*MainFormSLS->hh[88];
c2.v[45] += (sum_160_1_009)*MainFormSLS->hh[19];
c2.v[45] += (sum_160_1_010)*MainFormSLS->hh[110];
c2.v[45] += (sum_160_1_011)*MainFormSLS->hh[41];
c2.v[45] += (sum_160_1_012)*MainFormSLS->hh[132];
c2.v[45] += (sum_160_1_013)*MainFormSLS->hh[63];
c2.v[45] += (sum_160_1_014)*MainFormSLS->hh[154];
c2.v[45] += (sum_160_1_015)*MainFormSLS->hh[85];
c2.v[45] += (sum_160_1_016)*MainFormSLS->hh[16];
c2.v[45] += (sum_160_1_017)*MainFormSLS->hh[107];
c2.v[45] += (sum_160_1_018)*MainFormSLS->hh[38];
c2.v[45] += (sum_160_1_019)*MainFormSLS->hh[129];
c2.v[45] += (sum_160_1_020)*MainFormSLS->hh[60];
c2.v[45] += (sum_160_1_021)*MainFormSLS->hh[151];
c2.v[45] += (sum_160_1_022)*MainFormSLS->hh[82];
c2.v[45] += (sum_160_1_023)*MainFormSLS->hh[13];
c2.v[45] += (sum_160_1_024)*MainFormSLS->hh[104];
c2.v[45] += (sum_160_1_025)*MainFormSLS->hh[35];
c2.v[45] += (sum_160_1_026)*MainFormSLS->hh[126];
c2.v[45] += (sum_160_1_027)*MainFormSLS->hh[57];
c2.v[45] += (sum_160_1_028)*MainFormSLS->hh[148];
c2.v[45] += (sum_160_1_029)*MainFormSLS->hh[79];
c2.v[45] += (sum_160_1_030)*MainFormSLS->hh[10];
c2.v[45] += (sum_160_1_031)*MainFormSLS->hh[101];
c2.v[45] += (sum_160_1_032)*MainFormSLS->hh[32];
c2.v[45] += (sum_160_1_033)*MainFormSLS->hh[123];
c2.v[45] += (sum_160_1_034)*MainFormSLS->hh[54];
c2.v[45] += (sum_160_1_035)*MainFormSLS->hh[145];
c2.v[45] += (sum_160_1_036)*MainFormSLS->hh[76];
c2.v[45] += (sum_160_1_037)*MainFormSLS->hh[7];
c2.v[45] += (sum_160_1_038)*MainFormSLS->hh[98];
c2.v[45] += (sum_160_1_039)*MainFormSLS->hh[29];
c2.v[45] += (sum_160_1_040)*MainFormSLS->hh[120];
c2.v[45] += (sum_160_1_041)*MainFormSLS->hh[51];
c2.v[45] += (sum_160_1_042)*MainFormSLS->hh[142];
c2.v[45] += (sum_160_1_043)*MainFormSLS->hh[73];
c2.v[45] += (sum_160_1_044)*MainFormSLS->hh[4];
c2.v[45] += (sum_160_1_045)*MainFormSLS->hh[95];
c2.v[45] += (sum_160_1_046)*MainFormSLS->hh[26];
c2.v[45] += (sum_160_1_047)*MainFormSLS->hh[117];
c2.v[45] += (sum_160_1_048)*MainFormSLS->hh[48];
c2.v[45] += (sum_160_1_049)*MainFormSLS->hh[139];
c2.v[45] += (sum_160_1_050)*MainFormSLS->hh[70];
c2.v[45] += (sum_160_1_051)*MainFormSLS->hh[1];
c2.v[45] += (sum_160_1_052)*MainFormSLS->hh[92];
c2.v[45] += (sum_160_1_053)*MainFormSLS->hh[23];
c2.v[45] += (sum_160_1_054)*MainFormSLS->hh[114];
c2.v[45] += (sum_160_1_055)*MainFormSLS->hh[45];
c2.v[45] += (sum_160_1_056)*MainFormSLS->hh[136];
c2.v[45] += (sum_160_1_057)*MainFormSLS->hh[67];
c2.v[45] += (sum_160_1_058)*MainFormSLS->hh[158];
c2.v[45] += (sum_160_1_059)*MainFormSLS->hh[89];
c2.v[45] += (sum_160_1_060)*MainFormSLS->hh[20];
c2.v[45] += (sum_160_1_061)*MainFormSLS->hh[111];
c2.v[45] += (sum_160_1_062)*MainFormSLS->hh[42];
c2.v[45] += (sum_160_1_063)*MainFormSLS->hh[133];
c2.v[45] += (sum_160_1_064)*MainFormSLS->hh[64];
c2.v[45] += (sum_160_1_065)*MainFormSLS->hh[155];
c2.v[45] += (sum_160_1_066)*MainFormSLS->hh[86];
c2.v[45] += (sum_160_1_067)*MainFormSLS->hh[17];
c2.v[45] += (sum_160_1_068)*MainFormSLS->hh[108];
c2.v[45] += (sum_160_1_069)*MainFormSLS->hh[39];
c2.v[45] += (sum_160_1_070)*MainFormSLS->hh[130];
c2.v[45] += (sum_160_1_071)*MainFormSLS->hh[61];
c2.v[45] += (sum_160_1_072)*MainFormSLS->hh[152];
c2.v[45] += (sum_160_1_073)*MainFormSLS->hh[83];
c2.v[45] += (sum_160_1_074)*MainFormSLS->hh[14];
c2.v[45] += (sum_160_1_075)*MainFormSLS->hh[105];
c2.v[45] += (sum_160_1_076)*MainFormSLS->hh[36];
c2.v[45] += (sum_160_1_077)*MainFormSLS->hh[127];
c2.v[45] += (sum_160_1_078)*MainFormSLS->hh[58];
c2.v[45] += (sum_160_1_079)*MainFormSLS->hh[149];
c2.v[45] += (sum_160_1_080)*MainFormSLS->hh[80];
c2.v[45] += (sum_160_1_081)*MainFormSLS->hh[11];
c2.v[45] += (sum_160_1_082)*MainFormSLS->hh[102];
c2.v[45] += (sum_160_1_083)*MainFormSLS->hh[33];
c2.v[45] += (sum_160_1_084)*MainFormSLS->hh[124];
c2.v[45] += (sum_160_1_085)*MainFormSLS->hh[55];
c2.v[45] += (sum_160_1_086)*MainFormSLS->hh[146];
c2.v[45] += (sum_160_1_087)*MainFormSLS->hh[77];
c2.v[45] += (sum_160_1_088)*MainFormSLS->hh[8];
c2.v[45] += (sum_160_1_089)*MainFormSLS->hh[99];
c2.v[45] += (sum_160_1_090)*MainFormSLS->hh[30];
c2.v[45] += (sum_160_1_091)*MainFormSLS->hh[121];
c2.v[45] += (sum_160_1_092)*MainFormSLS->hh[52];
c2.v[45] += (sum_160_1_093)*MainFormSLS->hh[143];
c2.v[45] += (sum_160_1_094)*MainFormSLS->hh[74];
c2.v[45] += (sum_160_1_095)*MainFormSLS->hh[5];
c2.v[45] += (sum_160_1_096)*MainFormSLS->hh[96];
c2.v[45] += (sum_160_1_097)*MainFormSLS->hh[27];
c2.v[45] += (sum_160_1_098)*MainFormSLS->hh[118];
c2.v[45] += (sum_160_1_099)*MainFormSLS->hh[49];
c2.v[45] += (sum_160_1_100)*MainFormSLS->hh[140];
c2.v[45] += (sum_160_1_101)*MainFormSLS->hh[71];
c2.v[45] += (sum_160_1_102)*MainFormSLS->hh[2];
c2.v[45] += (sum_160_1_103)*MainFormSLS->hh[93];
c2.v[45] += (sum_160_1_104)*MainFormSLS->hh[24];
c2.v[45] += (sum_160_1_105)*MainFormSLS->hh[115];
c2.v[45] += (sum_160_1_106)*MainFormSLS->hh[46];
c2.v[45] += (sum_160_1_107)*MainFormSLS->hh[137];
c2.v[45] += (sum_160_1_108)*MainFormSLS->hh[68];
c2.v[45] += (sum_160_1_109)*MainFormSLS->hh[159];
c2.v[45] += (sum_160_1_110)*MainFormSLS->hh[90];
c2.v[45] += (sum_160_1_111)*MainFormSLS->hh[21];
c2.v[45] += (sum_160_1_112)*MainFormSLS->hh[112];
c2.v[45] += (sum_160_1_113)*MainFormSLS->hh[43];
c2.v[45] += (sum_160_1_114)*MainFormSLS->hh[134];
c2.v[45] += (sum_160_1_115)*MainFormSLS->hh[65];
c2.v[45] += (sum_160_1_116)*MainFormSLS->hh[156];
c2.v[45] += (sum_160_1_117)*MainFormSLS->hh[87];
c2.v[45] += (sum_160_1_118)*MainFormSLS->hh[18];
c2.v[45] += (sum_160_1_119)*MainFormSLS->hh[109];
c2.v[45] += (sum_160_1_120)*MainFormSLS->hh[40];
c2.v[45] += (sum_160_1_121)*MainFormSLS->hh[131];
c2.v[45] += (sum_160_1_122)*MainFormSLS->hh[62];
c2.v[45] += (sum_160_1_123)*MainFormSLS->hh[153];
c2.v[45] += (sum_160_1_124)*MainFormSLS->hh[84];
c2.v[45] += (sum_160_1_125)*MainFormSLS->hh[15];
c2.v[45] += (sum_160_1_126)*MainFormSLS->hh[106];
c2.v[45] += (sum_160_1_127)*MainFormSLS->hh[37];
c2.v[45] += (sum_160_1_128)*MainFormSLS->hh[128];
c2.v[45] += (sum_160_1_129)*MainFormSLS->hh[59];
c2.v[45] += (sum_160_1_130)*MainFormSLS->hh[150];
c2.v[45] += (sum_160_1_131)*MainFormSLS->hh[81];
c2.v[45] += (sum_160_1_132)*MainFormSLS->hh[12];
c2.v[45] += (sum_160_1_133)*MainFormSLS->hh[103];
c2.v[45] += (sum_160_1_134)*MainFormSLS->hh[34];
c2.v[45] += (sum_160_1_135)*MainFormSLS->hh[125];
c2.v[45] += (sum_160_1_136)*MainFormSLS->hh[56];
c2.v[45] += (sum_160_1_137)*MainFormSLS->hh[147];
c2.v[45] += (sum_160_1_138)*MainFormSLS->hh[78];
c2.v[45] += (sum_160_1_139)*MainFormSLS->hh[9];
c2.v[45] += (sum_160_1_140)*MainFormSLS->hh[100];
c2.v[45] += (sum_160_1_141)*MainFormSLS->hh[31];
c2.v[45] += (sum_160_1_142)*MainFormSLS->hh[122];
c2.v[45] += (sum_160_1_143)*MainFormSLS->hh[53];
c2.v[45] += (sum_160_1_144)*MainFormSLS->hh[144];
c2.v[45] += (sum_160_1_145)*MainFormSLS->hh[75];
c2.v[45] += (sum_160_1_146)*MainFormSLS->hh[6];
c2.v[45] += (sum_160_1_147)*MainFormSLS->hh[97];
c2.v[45] += (sum_160_1_148)*MainFormSLS->hh[28];
c2.v[45] += (sum_160_1_149)*MainFormSLS->hh[119];
c2.v[45] += (sum_160_1_150)*MainFormSLS->hh[50];
c2.v[45] += (sum_160_1_151)*MainFormSLS->hh[141];
c2.v[45] += (sum_160_1_152)*MainFormSLS->hh[72];
c2.v[45] += (sum_160_1_153)*MainFormSLS->hh[3];
c2.v[45] += (sum_160_1_154)*MainFormSLS->hh[94];
c2.v[45] += (sum_160_1_155)*MainFormSLS->hh[25];
c2.v[45] += (sum_160_1_156)*MainFormSLS->hh[116];
c2.v[45] += (sum_160_1_157)*MainFormSLS->hh[47];
c2.v[45] += (sum_160_1_158)*MainFormSLS->hh[138];
c2.v[45] += (sum_160_1_159)*MainFormSLS->hh[69];

//frequency level id 93
c2.v[46] += (sum_160_1_000)*MainFormSLS->hh[0];
c2.v[46] += (sum_160_1_001)*MainFormSLS->hh[93];
c2.v[46] += (sum_160_1_002)*MainFormSLS->hh[26];
c2.v[46] += (sum_160_1_003)*MainFormSLS->hh[119];
c2.v[46] += (sum_160_1_004)*MainFormSLS->hh[52];
c2.v[46] += (sum_160_1_005)*MainFormSLS->hh[145];
c2.v[46] += (sum_160_1_006)*MainFormSLS->hh[78];
c2.v[46] += (sum_160_1_007)*MainFormSLS->hh[11];
c2.v[46] += (sum_160_1_008)*MainFormSLS->hh[104];
c2.v[46] += (sum_160_1_009)*MainFormSLS->hh[37];
c2.v[46] += (sum_160_1_010)*MainFormSLS->hh[130];
c2.v[46] += (sum_160_1_011)*MainFormSLS->hh[63];
c2.v[46] += (sum_160_1_012)*MainFormSLS->hh[156];
c2.v[46] += (sum_160_1_013)*MainFormSLS->hh[89];
c2.v[46] += (sum_160_1_014)*MainFormSLS->hh[22];
c2.v[46] += (sum_160_1_015)*MainFormSLS->hh[115];
c2.v[46] += (sum_160_1_016)*MainFormSLS->hh[48];
c2.v[46] += (sum_160_1_017)*MainFormSLS->hh[141];
c2.v[46] += (sum_160_1_018)*MainFormSLS->hh[74];
c2.v[46] += (sum_160_1_019)*MainFormSLS->hh[7];
c2.v[46] += (sum_160_1_020)*MainFormSLS->hh[100];
c2.v[46] += (sum_160_1_021)*MainFormSLS->hh[33];
c2.v[46] += (sum_160_1_022)*MainFormSLS->hh[126];
c2.v[46] += (sum_160_1_023)*MainFormSLS->hh[59];
c2.v[46] += (sum_160_1_024)*MainFormSLS->hh[152];
c2.v[46] += (sum_160_1_025)*MainFormSLS->hh[85];
c2.v[46] += (sum_160_1_026)*MainFormSLS->hh[18];
c2.v[46] += (sum_160_1_027)*MainFormSLS->hh[111];
c2.v[46] += (sum_160_1_028)*MainFormSLS->hh[44];
c2.v[46] += (sum_160_1_029)*MainFormSLS->hh[137];
c2.v[46] += (sum_160_1_030)*MainFormSLS->hh[70];
c2.v[46] += (sum_160_1_031)*MainFormSLS->hh[3];
c2.v[46] += (sum_160_1_032)*MainFormSLS->hh[96];
c2.v[46] += (sum_160_1_033)*MainFormSLS->hh[29];
c2.v[46] += (sum_160_1_034)*MainFormSLS->hh[122];
c2.v[46] += (sum_160_1_035)*MainFormSLS->hh[55];
c2.v[46] += (sum_160_1_036)*MainFormSLS->hh[148];
c2.v[46] += (sum_160_1_037)*MainFormSLS->hh[81];
c2.v[46] += (sum_160_1_038)*MainFormSLS->hh[14];
c2.v[46] += (sum_160_1_039)*MainFormSLS->hh[107];
c2.v[46] += (sum_160_1_040)*MainFormSLS->hh[40];
c2.v[46] += (sum_160_1_041)*MainFormSLS->hh[133];
c2.v[46] += (sum_160_1_042)*MainFormSLS->hh[66];
c2.v[46] += (sum_160_1_043)*MainFormSLS->hh[159];
c2.v[46] += (sum_160_1_044)*MainFormSLS->hh[92];
c2.v[46] += (sum_160_1_045)*MainFormSLS->hh[25];
c2.v[46] += (sum_160_1_046)*MainFormSLS->hh[118];
c2.v[46] += (sum_160_1_047)*MainFormSLS->hh[51];
c2.v[46] += (sum_160_1_048)*MainFormSLS->hh[144];
c2.v[46] += (sum_160_1_049)*MainFormSLS->hh[77];
c2.v[46] += (sum_160_1_050)*MainFormSLS->hh[10];
c2.v[46] += (sum_160_1_051)*MainFormSLS->hh[103];
c2.v[46] += (sum_160_1_052)*MainFormSLS->hh[36];
c2.v[46] += (sum_160_1_053)*MainFormSLS->hh[129];
c2.v[46] += (sum_160_1_054)*MainFormSLS->hh[62];
c2.v[46] += (sum_160_1_055)*MainFormSLS->hh[155];
c2.v[46] += (sum_160_1_056)*MainFormSLS->hh[88];
c2.v[46] += (sum_160_1_057)*MainFormSLS->hh[21];
c2.v[46] += (sum_160_1_058)*MainFormSLS->hh[114];
c2.v[46] += (sum_160_1_059)*MainFormSLS->hh[47];
c2.v[46] += (sum_160_1_060)*MainFormSLS->hh[140];
c2.v[46] += (sum_160_1_061)*MainFormSLS->hh[73];
c2.v[46] += (sum_160_1_062)*MainFormSLS->hh[6];
c2.v[46] += (sum_160_1_063)*MainFormSLS->hh[99];
c2.v[46] += (sum_160_1_064)*MainFormSLS->hh[32];
c2.v[46] += (sum_160_1_065)*MainFormSLS->hh[125];
c2.v[46] += (sum_160_1_066)*MainFormSLS->hh[58];
c2.v[46] += (sum_160_1_067)*MainFormSLS->hh[151];
c2.v[46] += (sum_160_1_068)*MainFormSLS->hh[84];
c2.v[46] += (sum_160_1_069)*MainFormSLS->hh[17];
c2.v[46] += (sum_160_1_070)*MainFormSLS->hh[110];
c2.v[46] += (sum_160_1_071)*MainFormSLS->hh[43];
c2.v[46] += (sum_160_1_072)*MainFormSLS->hh[136];
c2.v[46] += (sum_160_1_073)*MainFormSLS->hh[69];
c2.v[46] += (sum_160_1_074)*MainFormSLS->hh[2];
c2.v[46] += (sum_160_1_075)*MainFormSLS->hh[95];
c2.v[46] += (sum_160_1_076)*MainFormSLS->hh[28];
c2.v[46] += (sum_160_1_077)*MainFormSLS->hh[121];
c2.v[46] += (sum_160_1_078)*MainFormSLS->hh[54];
c2.v[46] += (sum_160_1_079)*MainFormSLS->hh[147];
c2.v[46] += (sum_160_1_080)*MainFormSLS->hh[80];
c2.v[46] += (sum_160_1_081)*MainFormSLS->hh[13];
c2.v[46] += (sum_160_1_082)*MainFormSLS->hh[106];
c2.v[46] += (sum_160_1_083)*MainFormSLS->hh[39];
c2.v[46] += (sum_160_1_084)*MainFormSLS->hh[132];
c2.v[46] += (sum_160_1_085)*MainFormSLS->hh[65];
c2.v[46] += (sum_160_1_086)*MainFormSLS->hh[158];
c2.v[46] += (sum_160_1_087)*MainFormSLS->hh[91];
c2.v[46] += (sum_160_1_088)*MainFormSLS->hh[24];
c2.v[46] += (sum_160_1_089)*MainFormSLS->hh[117];
c2.v[46] += (sum_160_1_090)*MainFormSLS->hh[50];
c2.v[46] += (sum_160_1_091)*MainFormSLS->hh[143];
c2.v[46] += (sum_160_1_092)*MainFormSLS->hh[76];
c2.v[46] += (sum_160_1_093)*MainFormSLS->hh[9];
c2.v[46] += (sum_160_1_094)*MainFormSLS->hh[102];
c2.v[46] += (sum_160_1_095)*MainFormSLS->hh[35];
c2.v[46] += (sum_160_1_096)*MainFormSLS->hh[128];
c2.v[46] += (sum_160_1_097)*MainFormSLS->hh[61];
c2.v[46] += (sum_160_1_098)*MainFormSLS->hh[154];
c2.v[46] += (sum_160_1_099)*MainFormSLS->hh[87];
c2.v[46] += (sum_160_1_100)*MainFormSLS->hh[20];
c2.v[46] += (sum_160_1_101)*MainFormSLS->hh[113];
c2.v[46] += (sum_160_1_102)*MainFormSLS->hh[46];
c2.v[46] += (sum_160_1_103)*MainFormSLS->hh[139];
c2.v[46] += (sum_160_1_104)*MainFormSLS->hh[72];
c2.v[46] += (sum_160_1_105)*MainFormSLS->hh[5];
c2.v[46] += (sum_160_1_106)*MainFormSLS->hh[98];
c2.v[46] += (sum_160_1_107)*MainFormSLS->hh[31];
c2.v[46] += (sum_160_1_108)*MainFormSLS->hh[124];
c2.v[46] += (sum_160_1_109)*MainFormSLS->hh[57];
c2.v[46] += (sum_160_1_110)*MainFormSLS->hh[150];
c2.v[46] += (sum_160_1_111)*MainFormSLS->hh[83];
c2.v[46] += (sum_160_1_112)*MainFormSLS->hh[16];
c2.v[46] += (sum_160_1_113)*MainFormSLS->hh[109];
c2.v[46] += (sum_160_1_114)*MainFormSLS->hh[42];
c2.v[46] += (sum_160_1_115)*MainFormSLS->hh[135];
c2.v[46] += (sum_160_1_116)*MainFormSLS->hh[68];
c2.v[46] += (sum_160_1_117)*MainFormSLS->hh[1];
c2.v[46] += (sum_160_1_118)*MainFormSLS->hh[94];
c2.v[46] += (sum_160_1_119)*MainFormSLS->hh[27];
c2.v[46] += (sum_160_1_120)*MainFormSLS->hh[120];
c2.v[46] += (sum_160_1_121)*MainFormSLS->hh[53];
c2.v[46] += (sum_160_1_122)*MainFormSLS->hh[146];
c2.v[46] += (sum_160_1_123)*MainFormSLS->hh[79];
c2.v[46] += (sum_160_1_124)*MainFormSLS->hh[12];
c2.v[46] += (sum_160_1_125)*MainFormSLS->hh[105];
c2.v[46] += (sum_160_1_126)*MainFormSLS->hh[38];
c2.v[46] += (sum_160_1_127)*MainFormSLS->hh[131];
c2.v[46] += (sum_160_1_128)*MainFormSLS->hh[64];
c2.v[46] += (sum_160_1_129)*MainFormSLS->hh[157];
c2.v[46] += (sum_160_1_130)*MainFormSLS->hh[90];
c2.v[46] += (sum_160_1_131)*MainFormSLS->hh[23];
c2.v[46] += (sum_160_1_132)*MainFormSLS->hh[116];
c2.v[46] += (sum_160_1_133)*MainFormSLS->hh[49];
c2.v[46] += (sum_160_1_134)*MainFormSLS->hh[142];
c2.v[46] += (sum_160_1_135)*MainFormSLS->hh[75];
c2.v[46] += (sum_160_1_136)*MainFormSLS->hh[8];
c2.v[46] += (sum_160_1_137)*MainFormSLS->hh[101];
c2.v[46] += (sum_160_1_138)*MainFormSLS->hh[34];
c2.v[46] += (sum_160_1_139)*MainFormSLS->hh[127];
c2.v[46] += (sum_160_1_140)*MainFormSLS->hh[60];
c2.v[46] += (sum_160_1_141)*MainFormSLS->hh[153];
c2.v[46] += (sum_160_1_142)*MainFormSLS->hh[86];
c2.v[46] += (sum_160_1_143)*MainFormSLS->hh[19];
c2.v[46] += (sum_160_1_144)*MainFormSLS->hh[112];
c2.v[46] += (sum_160_1_145)*MainFormSLS->hh[45];
c2.v[46] += (sum_160_1_146)*MainFormSLS->hh[138];
c2.v[46] += (sum_160_1_147)*MainFormSLS->hh[71];
c2.v[46] += (sum_160_1_148)*MainFormSLS->hh[4];
c2.v[46] += (sum_160_1_149)*MainFormSLS->hh[97];
c2.v[46] += (sum_160_1_150)*MainFormSLS->hh[30];
c2.v[46] += (sum_160_1_151)*MainFormSLS->hh[123];
c2.v[46] += (sum_160_1_152)*MainFormSLS->hh[56];
c2.v[46] += (sum_160_1_153)*MainFormSLS->hh[149];
c2.v[46] += (sum_160_1_154)*MainFormSLS->hh[82];
c2.v[46] += (sum_160_1_155)*MainFormSLS->hh[15];
c2.v[46] += (sum_160_1_156)*MainFormSLS->hh[108];
c2.v[46] += (sum_160_1_157)*MainFormSLS->hh[41];
c2.v[46] += (sum_160_1_158)*MainFormSLS->hh[134];
c2.v[46] += (sum_160_1_159)*MainFormSLS->hh[67];

//frequency level id 95
c2.v[47] += (sum_32_5_000)*MainFormSLS->hh[0];
c2.v[47] += (sum_32_5_001)*MainFormSLS->hh[95];
c2.v[47] += (sum_32_5_002)*MainFormSLS->hh[30];
c2.v[47] += (sum_32_5_003)*MainFormSLS->hh[125];
c2.v[47] += (sum_32_5_004)*MainFormSLS->hh[60];
c2.v[47] += (sum_32_5_005)*MainFormSLS->hh[155];
c2.v[47] += (sum_32_5_006)*MainFormSLS->hh[90];
c2.v[47] += (sum_32_5_007)*MainFormSLS->hh[25];
c2.v[47] += (sum_32_5_008)*MainFormSLS->hh[120];
c2.v[47] += (sum_32_5_009)*MainFormSLS->hh[55];
c2.v[47] += (sum_32_5_010)*MainFormSLS->hh[150];
c2.v[47] += (sum_32_5_011)*MainFormSLS->hh[85];
c2.v[47] += (sum_32_5_012)*MainFormSLS->hh[20];
c2.v[47] += (sum_32_5_013)*MainFormSLS->hh[115];
c2.v[47] += (sum_32_5_014)*MainFormSLS->hh[50];
c2.v[47] += (sum_32_5_015)*MainFormSLS->hh[145];
c2.v[47] += (sum_32_5_016)*MainFormSLS->hh[80];
c2.v[47] += (sum_32_5_017)*MainFormSLS->hh[15];
c2.v[47] += (sum_32_5_018)*MainFormSLS->hh[110];
c2.v[47] += (sum_32_5_019)*MainFormSLS->hh[45];
c2.v[47] += (sum_32_5_020)*MainFormSLS->hh[140];
c2.v[47] += (sum_32_5_021)*MainFormSLS->hh[75];
c2.v[47] += (sum_32_5_022)*MainFormSLS->hh[10];
c2.v[47] += (sum_32_5_023)*MainFormSLS->hh[105];
c2.v[47] += (sum_32_5_024)*MainFormSLS->hh[40];
c2.v[47] += (sum_32_5_025)*MainFormSLS->hh[135];
c2.v[47] += (sum_32_5_026)*MainFormSLS->hh[70];
c2.v[47] += (sum_32_5_027)*MainFormSLS->hh[5];
c2.v[47] += (sum_32_5_028)*MainFormSLS->hh[100];
c2.v[47] += (sum_32_5_029)*MainFormSLS->hh[35];
c2.v[47] += (sum_32_5_030)*MainFormSLS->hh[130];
c2.v[47] += (sum_32_5_031)*MainFormSLS->hh[65];

//frequency level id 97
c2.v[48] += (sum_160_1_000)*MainFormSLS->hh[0];
c2.v[48] += (sum_160_1_001)*MainFormSLS->hh[97];
c2.v[48] += (sum_160_1_002)*MainFormSLS->hh[34];
c2.v[48] += (sum_160_1_003)*MainFormSLS->hh[131];
c2.v[48] += (sum_160_1_004)*MainFormSLS->hh[68];
c2.v[48] += (sum_160_1_005)*MainFormSLS->hh[5];
c2.v[48] += (sum_160_1_006)*MainFormSLS->hh[102];
c2.v[48] += (sum_160_1_007)*MainFormSLS->hh[39];
c2.v[48] += (sum_160_1_008)*MainFormSLS->hh[136];
c2.v[48] += (sum_160_1_009)*MainFormSLS->hh[73];
c2.v[48] += (sum_160_1_010)*MainFormSLS->hh[10];
c2.v[48] += (sum_160_1_011)*MainFormSLS->hh[107];
c2.v[48] += (sum_160_1_012)*MainFormSLS->hh[44];
c2.v[48] += (sum_160_1_013)*MainFormSLS->hh[141];
c2.v[48] += (sum_160_1_014)*MainFormSLS->hh[78];
c2.v[48] += (sum_160_1_015)*MainFormSLS->hh[15];
c2.v[48] += (sum_160_1_016)*MainFormSLS->hh[112];
c2.v[48] += (sum_160_1_017)*MainFormSLS->hh[49];
c2.v[48] += (sum_160_1_018)*MainFormSLS->hh[146];
c2.v[48] += (sum_160_1_019)*MainFormSLS->hh[83];
c2.v[48] += (sum_160_1_020)*MainFormSLS->hh[20];
c2.v[48] += (sum_160_1_021)*MainFormSLS->hh[117];
c2.v[48] += (sum_160_1_022)*MainFormSLS->hh[54];
c2.v[48] += (sum_160_1_023)*MainFormSLS->hh[151];
c2.v[48] += (sum_160_1_024)*MainFormSLS->hh[88];
c2.v[48] += (sum_160_1_025)*MainFormSLS->hh[25];
c2.v[48] += (sum_160_1_026)*MainFormSLS->hh[122];
c2.v[48] += (sum_160_1_027)*MainFormSLS->hh[59];
c2.v[48] += (sum_160_1_028)*MainFormSLS->hh[156];
c2.v[48] += (sum_160_1_029)*MainFormSLS->hh[93];
c2.v[48] += (sum_160_1_030)*MainFormSLS->hh[30];
c2.v[48] += (sum_160_1_031)*MainFormSLS->hh[127];
c2.v[48] += (sum_160_1_032)*MainFormSLS->hh[64];
c2.v[48] += (sum_160_1_033)*MainFormSLS->hh[1];
c2.v[48] += (sum_160_1_034)*MainFormSLS->hh[98];
c2.v[48] += (sum_160_1_035)*MainFormSLS->hh[35];
c2.v[48] += (sum_160_1_036)*MainFormSLS->hh[132];
c2.v[48] += (sum_160_1_037)*MainFormSLS->hh[69];
c2.v[48] += (sum_160_1_038)*MainFormSLS->hh[6];
c2.v[48] += (sum_160_1_039)*MainFormSLS->hh[103];
c2.v[48] += (sum_160_1_040)*MainFormSLS->hh[40];
c2.v[48] += (sum_160_1_041)*MainFormSLS->hh[137];
c2.v[48] += (sum_160_1_042)*MainFormSLS->hh[74];
c2.v[48] += (sum_160_1_043)*MainFormSLS->hh[11];
c2.v[48] += (sum_160_1_044)*MainFormSLS->hh[108];
c2.v[48] += (sum_160_1_045)*MainFormSLS->hh[45];
c2.v[48] += (sum_160_1_046)*MainFormSLS->hh[142];
c2.v[48] += (sum_160_1_047)*MainFormSLS->hh[79];
c2.v[48] += (sum_160_1_048)*MainFormSLS->hh[16];
c2.v[48] += (sum_160_1_049)*MainFormSLS->hh[113];
c2.v[48] += (sum_160_1_050)*MainFormSLS->hh[50];
c2.v[48] += (sum_160_1_051)*MainFormSLS->hh[147];
c2.v[48] += (sum_160_1_052)*MainFormSLS->hh[84];
c2.v[48] += (sum_160_1_053)*MainFormSLS->hh[21];
c2.v[48] += (sum_160_1_054)*MainFormSLS->hh[118];
c2.v[48] += (sum_160_1_055)*MainFormSLS->hh[55];
c2.v[48] += (sum_160_1_056)*MainFormSLS->hh[152];
c2.v[48] += (sum_160_1_057)*MainFormSLS->hh[89];
c2.v[48] += (sum_160_1_058)*MainFormSLS->hh[26];
c2.v[48] += (sum_160_1_059)*MainFormSLS->hh[123];
c2.v[48] += (sum_160_1_060)*MainFormSLS->hh[60];
c2.v[48] += (sum_160_1_061)*MainFormSLS->hh[157];
c2.v[48] += (sum_160_1_062)*MainFormSLS->hh[94];
c2.v[48] += (sum_160_1_063)*MainFormSLS->hh[31];
c2.v[48] += (sum_160_1_064)*MainFormSLS->hh[128];
c2.v[48] += (sum_160_1_065)*MainFormSLS->hh[65];
c2.v[48] += (sum_160_1_066)*MainFormSLS->hh[2];
c2.v[48] += (sum_160_1_067)*MainFormSLS->hh[99];
c2.v[48] += (sum_160_1_068)*MainFormSLS->hh[36];
c2.v[48] += (sum_160_1_069)*MainFormSLS->hh[133];
c2.v[48] += (sum_160_1_070)*MainFormSLS->hh[70];
c2.v[48] += (sum_160_1_071)*MainFormSLS->hh[7];
c2.v[48] += (sum_160_1_072)*MainFormSLS->hh[104];
c2.v[48] += (sum_160_1_073)*MainFormSLS->hh[41];
c2.v[48] += (sum_160_1_074)*MainFormSLS->hh[138];
c2.v[48] += (sum_160_1_075)*MainFormSLS->hh[75];
c2.v[48] += (sum_160_1_076)*MainFormSLS->hh[12];
c2.v[48] += (sum_160_1_077)*MainFormSLS->hh[109];
c2.v[48] += (sum_160_1_078)*MainFormSLS->hh[46];
c2.v[48] += (sum_160_1_079)*MainFormSLS->hh[143];
c2.v[48] += (sum_160_1_080)*MainFormSLS->hh[80];
c2.v[48] += (sum_160_1_081)*MainFormSLS->hh[17];
c2.v[48] += (sum_160_1_082)*MainFormSLS->hh[114];
c2.v[48] += (sum_160_1_083)*MainFormSLS->hh[51];
c2.v[48] += (sum_160_1_084)*MainFormSLS->hh[148];
c2.v[48] += (sum_160_1_085)*MainFormSLS->hh[85];
c2.v[48] += (sum_160_1_086)*MainFormSLS->hh[22];
c2.v[48] += (sum_160_1_087)*MainFormSLS->hh[119];
c2.v[48] += (sum_160_1_088)*MainFormSLS->hh[56];
c2.v[48] += (sum_160_1_089)*MainFormSLS->hh[153];
c2.v[48] += (sum_160_1_090)*MainFormSLS->hh[90];
c2.v[48] += (sum_160_1_091)*MainFormSLS->hh[27];
c2.v[48] += (sum_160_1_092)*MainFormSLS->hh[124];
c2.v[48] += (sum_160_1_093)*MainFormSLS->hh[61];
c2.v[48] += (sum_160_1_094)*MainFormSLS->hh[158];
c2.v[48] += (sum_160_1_095)*MainFormSLS->hh[95];
c2.v[48] += (sum_160_1_096)*MainFormSLS->hh[32];
c2.v[48] += (sum_160_1_097)*MainFormSLS->hh[129];
c2.v[48] += (sum_160_1_098)*MainFormSLS->hh[66];
c2.v[48] += (sum_160_1_099)*MainFormSLS->hh[3];
c2.v[48] += (sum_160_1_100)*MainFormSLS->hh[100];
c2.v[48] += (sum_160_1_101)*MainFormSLS->hh[37];
c2.v[48] += (sum_160_1_102)*MainFormSLS->hh[134];
c2.v[48] += (sum_160_1_103)*MainFormSLS->hh[71];
c2.v[48] += (sum_160_1_104)*MainFormSLS->hh[8];
c2.v[48] += (sum_160_1_105)*MainFormSLS->hh[105];
c2.v[48] += (sum_160_1_106)*MainFormSLS->hh[42];
c2.v[48] += (sum_160_1_107)*MainFormSLS->hh[139];
c2.v[48] += (sum_160_1_108)*MainFormSLS->hh[76];
c2.v[48] += (sum_160_1_109)*MainFormSLS->hh[13];
c2.v[48] += (sum_160_1_110)*MainFormSLS->hh[110];
c2.v[48] += (sum_160_1_111)*MainFormSLS->hh[47];
c2.v[48] += (sum_160_1_112)*MainFormSLS->hh[144];
c2.v[48] += (sum_160_1_113)*MainFormSLS->hh[81];
c2.v[48] += (sum_160_1_114)*MainFormSLS->hh[18];
c2.v[48] += (sum_160_1_115)*MainFormSLS->hh[115];
c2.v[48] += (sum_160_1_116)*MainFormSLS->hh[52];
c2.v[48] += (sum_160_1_117)*MainFormSLS->hh[149];
c2.v[48] += (sum_160_1_118)*MainFormSLS->hh[86];
c2.v[48] += (sum_160_1_119)*MainFormSLS->hh[23];
c2.v[48] += (sum_160_1_120)*MainFormSLS->hh[120];
c2.v[48] += (sum_160_1_121)*MainFormSLS->hh[57];
c2.v[48] += (sum_160_1_122)*MainFormSLS->hh[154];
c2.v[48] += (sum_160_1_123)*MainFormSLS->hh[91];
c2.v[48] += (sum_160_1_124)*MainFormSLS->hh[28];
c2.v[48] += (sum_160_1_125)*MainFormSLS->hh[125];
c2.v[48] += (sum_160_1_126)*MainFormSLS->hh[62];
c2.v[48] += (sum_160_1_127)*MainFormSLS->hh[159];
c2.v[48] += (sum_160_1_128)*MainFormSLS->hh[96];
c2.v[48] += (sum_160_1_129)*MainFormSLS->hh[33];
c2.v[48] += (sum_160_1_130)*MainFormSLS->hh[130];
c2.v[48] += (sum_160_1_131)*MainFormSLS->hh[67];
c2.v[48] += (sum_160_1_132)*MainFormSLS->hh[4];
c2.v[48] += (sum_160_1_133)*MainFormSLS->hh[101];
c2.v[48] += (sum_160_1_134)*MainFormSLS->hh[38];
c2.v[48] += (sum_160_1_135)*MainFormSLS->hh[135];
c2.v[48] += (sum_160_1_136)*MainFormSLS->hh[72];
c2.v[48] += (sum_160_1_137)*MainFormSLS->hh[9];
c2.v[48] += (sum_160_1_138)*MainFormSLS->hh[106];
c2.v[48] += (sum_160_1_139)*MainFormSLS->hh[43];
c2.v[48] += (sum_160_1_140)*MainFormSLS->hh[140];
c2.v[48] += (sum_160_1_141)*MainFormSLS->hh[77];
c2.v[48] += (sum_160_1_142)*MainFormSLS->hh[14];
c2.v[48] += (sum_160_1_143)*MainFormSLS->hh[111];
c2.v[48] += (sum_160_1_144)*MainFormSLS->hh[48];
c2.v[48] += (sum_160_1_145)*MainFormSLS->hh[145];
c2.v[48] += (sum_160_1_146)*MainFormSLS->hh[82];
c2.v[48] += (sum_160_1_147)*MainFormSLS->hh[19];
c2.v[48] += (sum_160_1_148)*MainFormSLS->hh[116];
c2.v[48] += (sum_160_1_149)*MainFormSLS->hh[53];
c2.v[48] += (sum_160_1_150)*MainFormSLS->hh[150];
c2.v[48] += (sum_160_1_151)*MainFormSLS->hh[87];
c2.v[48] += (sum_160_1_152)*MainFormSLS->hh[24];
c2.v[48] += (sum_160_1_153)*MainFormSLS->hh[121];
c2.v[48] += (sum_160_1_154)*MainFormSLS->hh[58];
c2.v[48] += (sum_160_1_155)*MainFormSLS->hh[155];
c2.v[48] += (sum_160_1_156)*MainFormSLS->hh[92];
c2.v[48] += (sum_160_1_157)*MainFormSLS->hh[29];
c2.v[48] += (sum_160_1_158)*MainFormSLS->hh[126];
c2.v[48] += (sum_160_1_159)*MainFormSLS->hh[63];

//frequency level id 99
c2.v[49] += (sum_160_1_000)*MainFormSLS->hh[0];
c2.v[49] += (sum_160_1_001)*MainFormSLS->hh[99];
c2.v[49] += (sum_160_1_002)*MainFormSLS->hh[38];
c2.v[49] += (sum_160_1_003)*MainFormSLS->hh[137];
c2.v[49] += (sum_160_1_004)*MainFormSLS->hh[76];
c2.v[49] += (sum_160_1_005)*MainFormSLS->hh[15];
c2.v[49] += (sum_160_1_006)*MainFormSLS->hh[114];
c2.v[49] += (sum_160_1_007)*MainFormSLS->hh[53];
c2.v[49] += (sum_160_1_008)*MainFormSLS->hh[152];
c2.v[49] += (sum_160_1_009)*MainFormSLS->hh[91];
c2.v[49] += (sum_160_1_010)*MainFormSLS->hh[30];
c2.v[49] += (sum_160_1_011)*MainFormSLS->hh[129];
c2.v[49] += (sum_160_1_012)*MainFormSLS->hh[68];
c2.v[49] += (sum_160_1_013)*MainFormSLS->hh[7];
c2.v[49] += (sum_160_1_014)*MainFormSLS->hh[106];
c2.v[49] += (sum_160_1_015)*MainFormSLS->hh[45];
c2.v[49] += (sum_160_1_016)*MainFormSLS->hh[144];
c2.v[49] += (sum_160_1_017)*MainFormSLS->hh[83];
c2.v[49] += (sum_160_1_018)*MainFormSLS->hh[22];
c2.v[49] += (sum_160_1_019)*MainFormSLS->hh[121];
c2.v[49] += (sum_160_1_020)*MainFormSLS->hh[60];
c2.v[49] += (sum_160_1_021)*MainFormSLS->hh[159];
c2.v[49] += (sum_160_1_022)*MainFormSLS->hh[98];
c2.v[49] += (sum_160_1_023)*MainFormSLS->hh[37];
c2.v[49] += (sum_160_1_024)*MainFormSLS->hh[136];
c2.v[49] += (sum_160_1_025)*MainFormSLS->hh[75];
c2.v[49] += (sum_160_1_026)*MainFormSLS->hh[14];
c2.v[49] += (sum_160_1_027)*MainFormSLS->hh[113];
c2.v[49] += (sum_160_1_028)*MainFormSLS->hh[52];
c2.v[49] += (sum_160_1_029)*MainFormSLS->hh[151];
c2.v[49] += (sum_160_1_030)*MainFormSLS->hh[90];
c2.v[49] += (sum_160_1_031)*MainFormSLS->hh[29];
c2.v[49] += (sum_160_1_032)*MainFormSLS->hh[128];
c2.v[49] += (sum_160_1_033)*MainFormSLS->hh[67];
c2.v[49] += (sum_160_1_034)*MainFormSLS->hh[6];
c2.v[49] += (sum_160_1_035)*MainFormSLS->hh[105];
c2.v[49] += (sum_160_1_036)*MainFormSLS->hh[44];
c2.v[49] += (sum_160_1_037)*MainFormSLS->hh[143];
c2.v[49] += (sum_160_1_038)*MainFormSLS->hh[82];
c2.v[49] += (sum_160_1_039)*MainFormSLS->hh[21];
c2.v[49] += (sum_160_1_040)*MainFormSLS->hh[120];
c2.v[49] += (sum_160_1_041)*MainFormSLS->hh[59];
c2.v[49] += (sum_160_1_042)*MainFormSLS->hh[158];
c2.v[49] += (sum_160_1_043)*MainFormSLS->hh[97];
c2.v[49] += (sum_160_1_044)*MainFormSLS->hh[36];
c2.v[49] += (sum_160_1_045)*MainFormSLS->hh[135];
c2.v[49] += (sum_160_1_046)*MainFormSLS->hh[74];
c2.v[49] += (sum_160_1_047)*MainFormSLS->hh[13];
c2.v[49] += (sum_160_1_048)*MainFormSLS->hh[112];
c2.v[49] += (sum_160_1_049)*MainFormSLS->hh[51];
c2.v[49] += (sum_160_1_050)*MainFormSLS->hh[150];
c2.v[49] += (sum_160_1_051)*MainFormSLS->hh[89];
c2.v[49] += (sum_160_1_052)*MainFormSLS->hh[28];
c2.v[49] += (sum_160_1_053)*MainFormSLS->hh[127];
c2.v[49] += (sum_160_1_054)*MainFormSLS->hh[66];
c2.v[49] += (sum_160_1_055)*MainFormSLS->hh[5];
c2.v[49] += (sum_160_1_056)*MainFormSLS->hh[104];
c2.v[49] += (sum_160_1_057)*MainFormSLS->hh[43];
c2.v[49] += (sum_160_1_058)*MainFormSLS->hh[142];
c2.v[49] += (sum_160_1_059)*MainFormSLS->hh[81];
c2.v[49] += (sum_160_1_060)*MainFormSLS->hh[20];
c2.v[49] += (sum_160_1_061)*MainFormSLS->hh[119];
c2.v[49] += (sum_160_1_062)*MainFormSLS->hh[58];
c2.v[49] += (sum_160_1_063)*MainFormSLS->hh[157];
c2.v[49] += (sum_160_1_064)*MainFormSLS->hh[96];
c2.v[49] += (sum_160_1_065)*MainFormSLS->hh[35];
c2.v[49] += (sum_160_1_066)*MainFormSLS->hh[134];
c2.v[49] += (sum_160_1_067)*MainFormSLS->hh[73];
c2.v[49] += (sum_160_1_068)*MainFormSLS->hh[12];
c2.v[49] += (sum_160_1_069)*MainFormSLS->hh[111];
c2.v[49] += (sum_160_1_070)*MainFormSLS->hh[50];
c2.v[49] += (sum_160_1_071)*MainFormSLS->hh[149];
c2.v[49] += (sum_160_1_072)*MainFormSLS->hh[88];
c2.v[49] += (sum_160_1_073)*MainFormSLS->hh[27];
c2.v[49] += (sum_160_1_074)*MainFormSLS->hh[126];
c2.v[49] += (sum_160_1_075)*MainFormSLS->hh[65];
c2.v[49] += (sum_160_1_076)*MainFormSLS->hh[4];
c2.v[49] += (sum_160_1_077)*MainFormSLS->hh[103];
c2.v[49] += (sum_160_1_078)*MainFormSLS->hh[42];
c2.v[49] += (sum_160_1_079)*MainFormSLS->hh[141];
c2.v[49] += (sum_160_1_080)*MainFormSLS->hh[80];
c2.v[49] += (sum_160_1_081)*MainFormSLS->hh[19];
c2.v[49] += (sum_160_1_082)*MainFormSLS->hh[118];
c2.v[49] += (sum_160_1_083)*MainFormSLS->hh[57];
c2.v[49] += (sum_160_1_084)*MainFormSLS->hh[156];
c2.v[49] += (sum_160_1_085)*MainFormSLS->hh[95];
c2.v[49] += (sum_160_1_086)*MainFormSLS->hh[34];
c2.v[49] += (sum_160_1_087)*MainFormSLS->hh[133];
c2.v[49] += (sum_160_1_088)*MainFormSLS->hh[72];
c2.v[49] += (sum_160_1_089)*MainFormSLS->hh[11];
c2.v[49] += (sum_160_1_090)*MainFormSLS->hh[110];
c2.v[49] += (sum_160_1_091)*MainFormSLS->hh[49];
c2.v[49] += (sum_160_1_092)*MainFormSLS->hh[148];
c2.v[49] += (sum_160_1_093)*MainFormSLS->hh[87];
c2.v[49] += (sum_160_1_094)*MainFormSLS->hh[26];
c2.v[49] += (sum_160_1_095)*MainFormSLS->hh[125];
c2.v[49] += (sum_160_1_096)*MainFormSLS->hh[64];
c2.v[49] += (sum_160_1_097)*MainFormSLS->hh[3];
c2.v[49] += (sum_160_1_098)*MainFormSLS->hh[102];
c2.v[49] += (sum_160_1_099)*MainFormSLS->hh[41];
c2.v[49] += (sum_160_1_100)*MainFormSLS->hh[140];
c2.v[49] += (sum_160_1_101)*MainFormSLS->hh[79];
c2.v[49] += (sum_160_1_102)*MainFormSLS->hh[18];
c2.v[49] += (sum_160_1_103)*MainFormSLS->hh[117];
c2.v[49] += (sum_160_1_104)*MainFormSLS->hh[56];
c2.v[49] += (sum_160_1_105)*MainFormSLS->hh[155];
c2.v[49] += (sum_160_1_106)*MainFormSLS->hh[94];
c2.v[49] += (sum_160_1_107)*MainFormSLS->hh[33];
c2.v[49] += (sum_160_1_108)*MainFormSLS->hh[132];
c2.v[49] += (sum_160_1_109)*MainFormSLS->hh[71];
c2.v[49] += (sum_160_1_110)*MainFormSLS->hh[10];
c2.v[49] += (sum_160_1_111)*MainFormSLS->hh[109];
c2.v[49] += (sum_160_1_112)*MainFormSLS->hh[48];
c2.v[49] += (sum_160_1_113)*MainFormSLS->hh[147];
c2.v[49] += (sum_160_1_114)*MainFormSLS->hh[86];
c2.v[49] += (sum_160_1_115)*MainFormSLS->hh[25];
c2.v[49] += (sum_160_1_116)*MainFormSLS->hh[124];
c2.v[49] += (sum_160_1_117)*MainFormSLS->hh[63];
c2.v[49] += (sum_160_1_118)*MainFormSLS->hh[2];
c2.v[49] += (sum_160_1_119)*MainFormSLS->hh[101];
c2.v[49] += (sum_160_1_120)*MainFormSLS->hh[40];
c2.v[49] += (sum_160_1_121)*MainFormSLS->hh[139];
c2.v[49] += (sum_160_1_122)*MainFormSLS->hh[78];
c2.v[49] += (sum_160_1_123)*MainFormSLS->hh[17];
c2.v[49] += (sum_160_1_124)*MainFormSLS->hh[116];
c2.v[49] += (sum_160_1_125)*MainFormSLS->hh[55];
c2.v[49] += (sum_160_1_126)*MainFormSLS->hh[154];
c2.v[49] += (sum_160_1_127)*MainFormSLS->hh[93];
c2.v[49] += (sum_160_1_128)*MainFormSLS->hh[32];
c2.v[49] += (sum_160_1_129)*MainFormSLS->hh[131];
c2.v[49] += (sum_160_1_130)*MainFormSLS->hh[70];
c2.v[49] += (sum_160_1_131)*MainFormSLS->hh[9];
c2.v[49] += (sum_160_1_132)*MainFormSLS->hh[108];
c2.v[49] += (sum_160_1_133)*MainFormSLS->hh[47];
c2.v[49] += (sum_160_1_134)*MainFormSLS->hh[146];
c2.v[49] += (sum_160_1_135)*MainFormSLS->hh[85];
c2.v[49] += (sum_160_1_136)*MainFormSLS->hh[24];
c2.v[49] += (sum_160_1_137)*MainFormSLS->hh[123];
c2.v[49] += (sum_160_1_138)*MainFormSLS->hh[62];
c2.v[49] += (sum_160_1_139)*MainFormSLS->hh[1];
c2.v[49] += (sum_160_1_140)*MainFormSLS->hh[100];
c2.v[49] += (sum_160_1_141)*MainFormSLS->hh[39];
c2.v[49] += (sum_160_1_142)*MainFormSLS->hh[138];
c2.v[49] += (sum_160_1_143)*MainFormSLS->hh[77];
c2.v[49] += (sum_160_1_144)*MainFormSLS->hh[16];
c2.v[49] += (sum_160_1_145)*MainFormSLS->hh[115];
c2.v[49] += (sum_160_1_146)*MainFormSLS->hh[54];
c2.v[49] += (sum_160_1_147)*MainFormSLS->hh[153];
c2.v[49] += (sum_160_1_148)*MainFormSLS->hh[92];
c2.v[49] += (sum_160_1_149)*MainFormSLS->hh[31];
c2.v[49] += (sum_160_1_150)*MainFormSLS->hh[130];
c2.v[49] += (sum_160_1_151)*MainFormSLS->hh[69];
c2.v[49] += (sum_160_1_152)*MainFormSLS->hh[8];
c2.v[49] += (sum_160_1_153)*MainFormSLS->hh[107];
c2.v[49] += (sum_160_1_154)*MainFormSLS->hh[46];
c2.v[49] += (sum_160_1_155)*MainFormSLS->hh[145];
c2.v[49] += (sum_160_1_156)*MainFormSLS->hh[84];
c2.v[49] += (sum_160_1_157)*MainFormSLS->hh[23];
c2.v[49] += (sum_160_1_158)*MainFormSLS->hh[122];
c2.v[49] += (sum_160_1_159)*MainFormSLS->hh[61];

//frequency level id 101
c2.v[50] += (sum_160_1_000)*MainFormSLS->hh[0];
c2.v[50] += (sum_160_1_001)*MainFormSLS->hh[101];
c2.v[50] += (sum_160_1_002)*MainFormSLS->hh[42];
c2.v[50] += (sum_160_1_003)*MainFormSLS->hh[143];
c2.v[50] += (sum_160_1_004)*MainFormSLS->hh[84];
c2.v[50] += (sum_160_1_005)*MainFormSLS->hh[25];
c2.v[50] += (sum_160_1_006)*MainFormSLS->hh[126];
c2.v[50] += (sum_160_1_007)*MainFormSLS->hh[67];
c2.v[50] += (sum_160_1_008)*MainFormSLS->hh[8];
c2.v[50] += (sum_160_1_009)*MainFormSLS->hh[109];
c2.v[50] += (sum_160_1_010)*MainFormSLS->hh[50];
c2.v[50] += (sum_160_1_011)*MainFormSLS->hh[151];
c2.v[50] += (sum_160_1_012)*MainFormSLS->hh[92];
c2.v[50] += (sum_160_1_013)*MainFormSLS->hh[33];
c2.v[50] += (sum_160_1_014)*MainFormSLS->hh[134];
c2.v[50] += (sum_160_1_015)*MainFormSLS->hh[75];
c2.v[50] += (sum_160_1_016)*MainFormSLS->hh[16];
c2.v[50] += (sum_160_1_017)*MainFormSLS->hh[117];
c2.v[50] += (sum_160_1_018)*MainFormSLS->hh[58];
c2.v[50] += (sum_160_1_019)*MainFormSLS->hh[159];
c2.v[50] += (sum_160_1_020)*MainFormSLS->hh[100];
c2.v[50] += (sum_160_1_021)*MainFormSLS->hh[41];
c2.v[50] += (sum_160_1_022)*MainFormSLS->hh[142];
c2.v[50] += (sum_160_1_023)*MainFormSLS->hh[83];
c2.v[50] += (sum_160_1_024)*MainFormSLS->hh[24];
c2.v[50] += (sum_160_1_025)*MainFormSLS->hh[125];
c2.v[50] += (sum_160_1_026)*MainFormSLS->hh[66];
c2.v[50] += (sum_160_1_027)*MainFormSLS->hh[7];
c2.v[50] += (sum_160_1_028)*MainFormSLS->hh[108];
c2.v[50] += (sum_160_1_029)*MainFormSLS->hh[49];
c2.v[50] += (sum_160_1_030)*MainFormSLS->hh[150];
c2.v[50] += (sum_160_1_031)*MainFormSLS->hh[91];
c2.v[50] += (sum_160_1_032)*MainFormSLS->hh[32];
c2.v[50] += (sum_160_1_033)*MainFormSLS->hh[133];
c2.v[50] += (sum_160_1_034)*MainFormSLS->hh[74];
c2.v[50] += (sum_160_1_035)*MainFormSLS->hh[15];
c2.v[50] += (sum_160_1_036)*MainFormSLS->hh[116];
c2.v[50] += (sum_160_1_037)*MainFormSLS->hh[57];
c2.v[50] += (sum_160_1_038)*MainFormSLS->hh[158];
c2.v[50] += (sum_160_1_039)*MainFormSLS->hh[99];
c2.v[50] += (sum_160_1_040)*MainFormSLS->hh[40];
c2.v[50] += (sum_160_1_041)*MainFormSLS->hh[141];
c2.v[50] += (sum_160_1_042)*MainFormSLS->hh[82];
c2.v[50] += (sum_160_1_043)*MainFormSLS->hh[23];
c2.v[50] += (sum_160_1_044)*MainFormSLS->hh[124];
c2.v[50] += (sum_160_1_045)*MainFormSLS->hh[65];
c2.v[50] += (sum_160_1_046)*MainFormSLS->hh[6];
c2.v[50] += (sum_160_1_047)*MainFormSLS->hh[107];
c2.v[50] += (sum_160_1_048)*MainFormSLS->hh[48];
c2.v[50] += (sum_160_1_049)*MainFormSLS->hh[149];
c2.v[50] += (sum_160_1_050)*MainFormSLS->hh[90];
c2.v[50] += (sum_160_1_051)*MainFormSLS->hh[31];
c2.v[50] += (sum_160_1_052)*MainFormSLS->hh[132];
c2.v[50] += (sum_160_1_053)*MainFormSLS->hh[73];
c2.v[50] += (sum_160_1_054)*MainFormSLS->hh[14];
c2.v[50] += (sum_160_1_055)*MainFormSLS->hh[115];
c2.v[50] += (sum_160_1_056)*MainFormSLS->hh[56];
c2.v[50] += (sum_160_1_057)*MainFormSLS->hh[157];
c2.v[50] += (sum_160_1_058)*MainFormSLS->hh[98];
c2.v[50] += (sum_160_1_059)*MainFormSLS->hh[39];
c2.v[50] += (sum_160_1_060)*MainFormSLS->hh[140];
c2.v[50] += (sum_160_1_061)*MainFormSLS->hh[81];
c2.v[50] += (sum_160_1_062)*MainFormSLS->hh[22];
c2.v[50] += (sum_160_1_063)*MainFormSLS->hh[123];
c2.v[50] += (sum_160_1_064)*MainFormSLS->hh[64];
c2.v[50] += (sum_160_1_065)*MainFormSLS->hh[5];
c2.v[50] += (sum_160_1_066)*MainFormSLS->hh[106];
c2.v[50] += (sum_160_1_067)*MainFormSLS->hh[47];
c2.v[50] += (sum_160_1_068)*MainFormSLS->hh[148];
c2.v[50] += (sum_160_1_069)*MainFormSLS->hh[89];
c2.v[50] += (sum_160_1_070)*MainFormSLS->hh[30];
c2.v[50] += (sum_160_1_071)*MainFormSLS->hh[131];
c2.v[50] += (sum_160_1_072)*MainFormSLS->hh[72];
c2.v[50] += (sum_160_1_073)*MainFormSLS->hh[13];
c2.v[50] += (sum_160_1_074)*MainFormSLS->hh[114];
c2.v[50] += (sum_160_1_075)*MainFormSLS->hh[55];
c2.v[50] += (sum_160_1_076)*MainFormSLS->hh[156];
c2.v[50] += (sum_160_1_077)*MainFormSLS->hh[97];
c2.v[50] += (sum_160_1_078)*MainFormSLS->hh[38];
c2.v[50] += (sum_160_1_079)*MainFormSLS->hh[139];
c2.v[50] += (sum_160_1_080)*MainFormSLS->hh[80];
c2.v[50] += (sum_160_1_081)*MainFormSLS->hh[21];
c2.v[50] += (sum_160_1_082)*MainFormSLS->hh[122];
c2.v[50] += (sum_160_1_083)*MainFormSLS->hh[63];
c2.v[50] += (sum_160_1_084)*MainFormSLS->hh[4];
c2.v[50] += (sum_160_1_085)*MainFormSLS->hh[105];
c2.v[50] += (sum_160_1_086)*MainFormSLS->hh[46];
c2.v[50] += (sum_160_1_087)*MainFormSLS->hh[147];
c2.v[50] += (sum_160_1_088)*MainFormSLS->hh[88];
c2.v[50] += (sum_160_1_089)*MainFormSLS->hh[29];
c2.v[50] += (sum_160_1_090)*MainFormSLS->hh[130];
c2.v[50] += (sum_160_1_091)*MainFormSLS->hh[71];
c2.v[50] += (sum_160_1_092)*MainFormSLS->hh[12];
c2.v[50] += (sum_160_1_093)*MainFormSLS->hh[113];
c2.v[50] += (sum_160_1_094)*MainFormSLS->hh[54];
c2.v[50] += (sum_160_1_095)*MainFormSLS->hh[155];
c2.v[50] += (sum_160_1_096)*MainFormSLS->hh[96];
c2.v[50] += (sum_160_1_097)*MainFormSLS->hh[37];
c2.v[50] += (sum_160_1_098)*MainFormSLS->hh[138];
c2.v[50] += (sum_160_1_099)*MainFormSLS->hh[79];
c2.v[50] += (sum_160_1_100)*MainFormSLS->hh[20];
c2.v[50] += (sum_160_1_101)*MainFormSLS->hh[121];
c2.v[50] += (sum_160_1_102)*MainFormSLS->hh[62];
c2.v[50] += (sum_160_1_103)*MainFormSLS->hh[3];
c2.v[50] += (sum_160_1_104)*MainFormSLS->hh[104];
c2.v[50] += (sum_160_1_105)*MainFormSLS->hh[45];
c2.v[50] += (sum_160_1_106)*MainFormSLS->hh[146];
c2.v[50] += (sum_160_1_107)*MainFormSLS->hh[87];
c2.v[50] += (sum_160_1_108)*MainFormSLS->hh[28];
c2.v[50] += (sum_160_1_109)*MainFormSLS->hh[129];
c2.v[50] += (sum_160_1_110)*MainFormSLS->hh[70];
c2.v[50] += (sum_160_1_111)*MainFormSLS->hh[11];
c2.v[50] += (sum_160_1_112)*MainFormSLS->hh[112];
c2.v[50] += (sum_160_1_113)*MainFormSLS->hh[53];
c2.v[50] += (sum_160_1_114)*MainFormSLS->hh[154];
c2.v[50] += (sum_160_1_115)*MainFormSLS->hh[95];
c2.v[50] += (sum_160_1_116)*MainFormSLS->hh[36];
c2.v[50] += (sum_160_1_117)*MainFormSLS->hh[137];
c2.v[50] += (sum_160_1_118)*MainFormSLS->hh[78];
c2.v[50] += (sum_160_1_119)*MainFormSLS->hh[19];
c2.v[50] += (sum_160_1_120)*MainFormSLS->hh[120];
c2.v[50] += (sum_160_1_121)*MainFormSLS->hh[61];
c2.v[50] += (sum_160_1_122)*MainFormSLS->hh[2];
c2.v[50] += (sum_160_1_123)*MainFormSLS->hh[103];
c2.v[50] += (sum_160_1_124)*MainFormSLS->hh[44];
c2.v[50] += (sum_160_1_125)*MainFormSLS->hh[145];
c2.v[50] += (sum_160_1_126)*MainFormSLS->hh[86];
c2.v[50] += (sum_160_1_127)*MainFormSLS->hh[27];
c2.v[50] += (sum_160_1_128)*MainFormSLS->hh[128];
c2.v[50] += (sum_160_1_129)*MainFormSLS->hh[69];
c2.v[50] += (sum_160_1_130)*MainFormSLS->hh[10];
c2.v[50] += (sum_160_1_131)*MainFormSLS->hh[111];
c2.v[50] += (sum_160_1_132)*MainFormSLS->hh[52];
c2.v[50] += (sum_160_1_133)*MainFormSLS->hh[153];
c2.v[50] += (sum_160_1_134)*MainFormSLS->hh[94];
c2.v[50] += (sum_160_1_135)*MainFormSLS->hh[35];
c2.v[50] += (sum_160_1_136)*MainFormSLS->hh[136];
c2.v[50] += (sum_160_1_137)*MainFormSLS->hh[77];
c2.v[50] += (sum_160_1_138)*MainFormSLS->hh[18];
c2.v[50] += (sum_160_1_139)*MainFormSLS->hh[119];
c2.v[50] += (sum_160_1_140)*MainFormSLS->hh[60];
c2.v[50] += (sum_160_1_141)*MainFormSLS->hh[1];
c2.v[50] += (sum_160_1_142)*MainFormSLS->hh[102];
c2.v[50] += (sum_160_1_143)*MainFormSLS->hh[43];
c2.v[50] += (sum_160_1_144)*MainFormSLS->hh[144];
c2.v[50] += (sum_160_1_145)*MainFormSLS->hh[85];
c2.v[50] += (sum_160_1_146)*MainFormSLS->hh[26];
c2.v[50] += (sum_160_1_147)*MainFormSLS->hh[127];
c2.v[50] += (sum_160_1_148)*MainFormSLS->hh[68];
c2.v[50] += (sum_160_1_149)*MainFormSLS->hh[9];
c2.v[50] += (sum_160_1_150)*MainFormSLS->hh[110];
c2.v[50] += (sum_160_1_151)*MainFormSLS->hh[51];
c2.v[50] += (sum_160_1_152)*MainFormSLS->hh[152];
c2.v[50] += (sum_160_1_153)*MainFormSLS->hh[93];
c2.v[50] += (sum_160_1_154)*MainFormSLS->hh[34];
c2.v[50] += (sum_160_1_155)*MainFormSLS->hh[135];
c2.v[50] += (sum_160_1_156)*MainFormSLS->hh[76];
c2.v[50] += (sum_160_1_157)*MainFormSLS->hh[17];
c2.v[50] += (sum_160_1_158)*MainFormSLS->hh[118];
c2.v[50] += (sum_160_1_159)*MainFormSLS->hh[59];

//frequency level id 103
c2.v[51] += (sum_160_1_000)*MainFormSLS->hh[0];
c2.v[51] += (sum_160_1_001)*MainFormSLS->hh[103];
c2.v[51] += (sum_160_1_002)*MainFormSLS->hh[46];
c2.v[51] += (sum_160_1_003)*MainFormSLS->hh[149];
c2.v[51] += (sum_160_1_004)*MainFormSLS->hh[92];
c2.v[51] += (sum_160_1_005)*MainFormSLS->hh[35];
c2.v[51] += (sum_160_1_006)*MainFormSLS->hh[138];
c2.v[51] += (sum_160_1_007)*MainFormSLS->hh[81];
c2.v[51] += (sum_160_1_008)*MainFormSLS->hh[24];
c2.v[51] += (sum_160_1_009)*MainFormSLS->hh[127];
c2.v[51] += (sum_160_1_010)*MainFormSLS->hh[70];
c2.v[51] += (sum_160_1_011)*MainFormSLS->hh[13];
c2.v[51] += (sum_160_1_012)*MainFormSLS->hh[116];
c2.v[51] += (sum_160_1_013)*MainFormSLS->hh[59];
c2.v[51] += (sum_160_1_014)*MainFormSLS->hh[2];
c2.v[51] += (sum_160_1_015)*MainFormSLS->hh[105];
c2.v[51] += (sum_160_1_016)*MainFormSLS->hh[48];
c2.v[51] += (sum_160_1_017)*MainFormSLS->hh[151];
c2.v[51] += (sum_160_1_018)*MainFormSLS->hh[94];
c2.v[51] += (sum_160_1_019)*MainFormSLS->hh[37];
c2.v[51] += (sum_160_1_020)*MainFormSLS->hh[140];
c2.v[51] += (sum_160_1_021)*MainFormSLS->hh[83];
c2.v[51] += (sum_160_1_022)*MainFormSLS->hh[26];
c2.v[51] += (sum_160_1_023)*MainFormSLS->hh[129];
c2.v[51] += (sum_160_1_024)*MainFormSLS->hh[72];
c2.v[51] += (sum_160_1_025)*MainFormSLS->hh[15];
c2.v[51] += (sum_160_1_026)*MainFormSLS->hh[118];
c2.v[51] += (sum_160_1_027)*MainFormSLS->hh[61];
c2.v[51] += (sum_160_1_028)*MainFormSLS->hh[4];
c2.v[51] += (sum_160_1_029)*MainFormSLS->hh[107];
c2.v[51] += (sum_160_1_030)*MainFormSLS->hh[50];
c2.v[51] += (sum_160_1_031)*MainFormSLS->hh[153];
c2.v[51] += (sum_160_1_032)*MainFormSLS->hh[96];
c2.v[51] += (sum_160_1_033)*MainFormSLS->hh[39];
c2.v[51] += (sum_160_1_034)*MainFormSLS->hh[142];
c2.v[51] += (sum_160_1_035)*MainFormSLS->hh[85];
c2.v[51] += (sum_160_1_036)*MainFormSLS->hh[28];
c2.v[51] += (sum_160_1_037)*MainFormSLS->hh[131];
c2.v[51] += (sum_160_1_038)*MainFormSLS->hh[74];
c2.v[51] += (sum_160_1_039)*MainFormSLS->hh[17];
c2.v[51] += (sum_160_1_040)*MainFormSLS->hh[120];
c2.v[51] += (sum_160_1_041)*MainFormSLS->hh[63];
c2.v[51] += (sum_160_1_042)*MainFormSLS->hh[6];
c2.v[51] += (sum_160_1_043)*MainFormSLS->hh[109];
c2.v[51] += (sum_160_1_044)*MainFormSLS->hh[52];
c2.v[51] += (sum_160_1_045)*MainFormSLS->hh[155];
c2.v[51] += (sum_160_1_046)*MainFormSLS->hh[98];
c2.v[51] += (sum_160_1_047)*MainFormSLS->hh[41];
c2.v[51] += (sum_160_1_048)*MainFormSLS->hh[144];
c2.v[51] += (sum_160_1_049)*MainFormSLS->hh[87];
c2.v[51] += (sum_160_1_050)*MainFormSLS->hh[30];
c2.v[51] += (sum_160_1_051)*MainFormSLS->hh[133];
c2.v[51] += (sum_160_1_052)*MainFormSLS->hh[76];
c2.v[51] += (sum_160_1_053)*MainFormSLS->hh[19];
c2.v[51] += (sum_160_1_054)*MainFormSLS->hh[122];
c2.v[51] += (sum_160_1_055)*MainFormSLS->hh[65];
c2.v[51] += (sum_160_1_056)*MainFormSLS->hh[8];
c2.v[51] += (sum_160_1_057)*MainFormSLS->hh[111];
c2.v[51] += (sum_160_1_058)*MainFormSLS->hh[54];
c2.v[51] += (sum_160_1_059)*MainFormSLS->hh[157];
c2.v[51] += (sum_160_1_060)*MainFormSLS->hh[100];
c2.v[51] += (sum_160_1_061)*MainFormSLS->hh[43];
c2.v[51] += (sum_160_1_062)*MainFormSLS->hh[146];
c2.v[51] += (sum_160_1_063)*MainFormSLS->hh[89];
c2.v[51] += (sum_160_1_064)*MainFormSLS->hh[32];
c2.v[51] += (sum_160_1_065)*MainFormSLS->hh[135];
c2.v[51] += (sum_160_1_066)*MainFormSLS->hh[78];
c2.v[51] += (sum_160_1_067)*MainFormSLS->hh[21];
c2.v[51] += (sum_160_1_068)*MainFormSLS->hh[124];
c2.v[51] += (sum_160_1_069)*MainFormSLS->hh[67];
c2.v[51] += (sum_160_1_070)*MainFormSLS->hh[10];
c2.v[51] += (sum_160_1_071)*MainFormSLS->hh[113];
c2.v[51] += (sum_160_1_072)*MainFormSLS->hh[56];
c2.v[51] += (sum_160_1_073)*MainFormSLS->hh[159];
c2.v[51] += (sum_160_1_074)*MainFormSLS->hh[102];
c2.v[51] += (sum_160_1_075)*MainFormSLS->hh[45];
c2.v[51] += (sum_160_1_076)*MainFormSLS->hh[148];
c2.v[51] += (sum_160_1_077)*MainFormSLS->hh[91];
c2.v[51] += (sum_160_1_078)*MainFormSLS->hh[34];
c2.v[51] += (sum_160_1_079)*MainFormSLS->hh[137];
c2.v[51] += (sum_160_1_080)*MainFormSLS->hh[80];
c2.v[51] += (sum_160_1_081)*MainFormSLS->hh[23];
c2.v[51] += (sum_160_1_082)*MainFormSLS->hh[126];
c2.v[51] += (sum_160_1_083)*MainFormSLS->hh[69];
c2.v[51] += (sum_160_1_084)*MainFormSLS->hh[12];
c2.v[51] += (sum_160_1_085)*MainFormSLS->hh[115];
c2.v[51] += (sum_160_1_086)*MainFormSLS->hh[58];
c2.v[51] += (sum_160_1_087)*MainFormSLS->hh[1];
c2.v[51] += (sum_160_1_088)*MainFormSLS->hh[104];
c2.v[51] += (sum_160_1_089)*MainFormSLS->hh[47];
c2.v[51] += (sum_160_1_090)*MainFormSLS->hh[150];
c2.v[51] += (sum_160_1_091)*MainFormSLS->hh[93];
c2.v[51] += (sum_160_1_092)*MainFormSLS->hh[36];
c2.v[51] += (sum_160_1_093)*MainFormSLS->hh[139];
c2.v[51] += (sum_160_1_094)*MainFormSLS->hh[82];
c2.v[51] += (sum_160_1_095)*MainFormSLS->hh[25];
c2.v[51] += (sum_160_1_096)*MainFormSLS->hh[128];
c2.v[51] += (sum_160_1_097)*MainFormSLS->hh[71];
c2.v[51] += (sum_160_1_098)*MainFormSLS->hh[14];
c2.v[51] += (sum_160_1_099)*MainFormSLS->hh[117];
c2.v[51] += (sum_160_1_100)*MainFormSLS->hh[60];
c2.v[51] += (sum_160_1_101)*MainFormSLS->hh[3];
c2.v[51] += (sum_160_1_102)*MainFormSLS->hh[106];
c2.v[51] += (sum_160_1_103)*MainFormSLS->hh[49];
c2.v[51] += (sum_160_1_104)*MainFormSLS->hh[152];
c2.v[51] += (sum_160_1_105)*MainFormSLS->hh[95];
c2.v[51] += (sum_160_1_106)*MainFormSLS->hh[38];
c2.v[51] += (sum_160_1_107)*MainFormSLS->hh[141];
c2.v[51] += (sum_160_1_108)*MainFormSLS->hh[84];
c2.v[51] += (sum_160_1_109)*MainFormSLS->hh[27];
c2.v[51] += (sum_160_1_110)*MainFormSLS->hh[130];
c2.v[51] += (sum_160_1_111)*MainFormSLS->hh[73];
c2.v[51] += (sum_160_1_112)*MainFormSLS->hh[16];
c2.v[51] += (sum_160_1_113)*MainFormSLS->hh[119];
c2.v[51] += (sum_160_1_114)*MainFormSLS->hh[62];
c2.v[51] += (sum_160_1_115)*MainFormSLS->hh[5];
c2.v[51] += (sum_160_1_116)*MainFormSLS->hh[108];
c2.v[51] += (sum_160_1_117)*MainFormSLS->hh[51];
c2.v[51] += (sum_160_1_118)*MainFormSLS->hh[154];
c2.v[51] += (sum_160_1_119)*MainFormSLS->hh[97];
c2.v[51] += (sum_160_1_120)*MainFormSLS->hh[40];
c2.v[51] += (sum_160_1_121)*MainFormSLS->hh[143];
c2.v[51] += (sum_160_1_122)*MainFormSLS->hh[86];
c2.v[51] += (sum_160_1_123)*MainFormSLS->hh[29];
c2.v[51] += (sum_160_1_124)*MainFormSLS->hh[132];
c2.v[51] += (sum_160_1_125)*MainFormSLS->hh[75];
c2.v[51] += (sum_160_1_126)*MainFormSLS->hh[18];
c2.v[51] += (sum_160_1_127)*MainFormSLS->hh[121];
c2.v[51] += (sum_160_1_128)*MainFormSLS->hh[64];
c2.v[51] += (sum_160_1_129)*MainFormSLS->hh[7];
c2.v[51] += (sum_160_1_130)*MainFormSLS->hh[110];
c2.v[51] += (sum_160_1_131)*MainFormSLS->hh[53];
c2.v[51] += (sum_160_1_132)*MainFormSLS->hh[156];
c2.v[51] += (sum_160_1_133)*MainFormSLS->hh[99];
c2.v[51] += (sum_160_1_134)*MainFormSLS->hh[42];
c2.v[51] += (sum_160_1_135)*MainFormSLS->hh[145];
c2.v[51] += (sum_160_1_136)*MainFormSLS->hh[88];
c2.v[51] += (sum_160_1_137)*MainFormSLS->hh[31];
c2.v[51] += (sum_160_1_138)*MainFormSLS->hh[134];
c2.v[51] += (sum_160_1_139)*MainFormSLS->hh[77];
c2.v[51] += (sum_160_1_140)*MainFormSLS->hh[20];
c2.v[51] += (sum_160_1_141)*MainFormSLS->hh[123];
c2.v[51] += (sum_160_1_142)*MainFormSLS->hh[66];
c2.v[51] += (sum_160_1_143)*MainFormSLS->hh[9];
c2.v[51] += (sum_160_1_144)*MainFormSLS->hh[112];
c2.v[51] += (sum_160_1_145)*MainFormSLS->hh[55];
c2.v[51] += (sum_160_1_146)*MainFormSLS->hh[158];
c2.v[51] += (sum_160_1_147)*MainFormSLS->hh[101];
c2.v[51] += (sum_160_1_148)*MainFormSLS->hh[44];
c2.v[51] += (sum_160_1_149)*MainFormSLS->hh[147];
c2.v[51] += (sum_160_1_150)*MainFormSLS->hh[90];
c2.v[51] += (sum_160_1_151)*MainFormSLS->hh[33];
c2.v[51] += (sum_160_1_152)*MainFormSLS->hh[136];
c2.v[51] += (sum_160_1_153)*MainFormSLS->hh[79];
c2.v[51] += (sum_160_1_154)*MainFormSLS->hh[22];
c2.v[51] += (sum_160_1_155)*MainFormSLS->hh[125];
c2.v[51] += (sum_160_1_156)*MainFormSLS->hh[68];
c2.v[51] += (sum_160_1_157)*MainFormSLS->hh[11];
c2.v[51] += (sum_160_1_158)*MainFormSLS->hh[114];
c2.v[51] += (sum_160_1_159)*MainFormSLS->hh[57];

//frequency level id 105
c2.v[52] += (sum_32_5_000)*MainFormSLS->hh[0];
c2.v[52] += (sum_32_5_001)*MainFormSLS->hh[105];
c2.v[52] += (sum_32_5_002)*MainFormSLS->hh[50];
c2.v[52] += (sum_32_5_003)*MainFormSLS->hh[155];
c2.v[52] += (sum_32_5_004)*MainFormSLS->hh[100];
c2.v[52] += (sum_32_5_005)*MainFormSLS->hh[45];
c2.v[52] += (sum_32_5_006)*MainFormSLS->hh[150];
c2.v[52] += (sum_32_5_007)*MainFormSLS->hh[95];
c2.v[52] += (sum_32_5_008)*MainFormSLS->hh[40];
c2.v[52] += (sum_32_5_009)*MainFormSLS->hh[145];
c2.v[52] += (sum_32_5_010)*MainFormSLS->hh[90];
c2.v[52] += (sum_32_5_011)*MainFormSLS->hh[35];
c2.v[52] += (sum_32_5_012)*MainFormSLS->hh[140];
c2.v[52] += (sum_32_5_013)*MainFormSLS->hh[85];
c2.v[52] += (sum_32_5_014)*MainFormSLS->hh[30];
c2.v[52] += (sum_32_5_015)*MainFormSLS->hh[135];
c2.v[52] += (sum_32_5_016)*MainFormSLS->hh[80];
c2.v[52] += (sum_32_5_017)*MainFormSLS->hh[25];
c2.v[52] += (sum_32_5_018)*MainFormSLS->hh[130];
c2.v[52] += (sum_32_5_019)*MainFormSLS->hh[75];
c2.v[52] += (sum_32_5_020)*MainFormSLS->hh[20];
c2.v[52] += (sum_32_5_021)*MainFormSLS->hh[125];
c2.v[52] += (sum_32_5_022)*MainFormSLS->hh[70];
c2.v[52] += (sum_32_5_023)*MainFormSLS->hh[15];
c2.v[52] += (sum_32_5_024)*MainFormSLS->hh[120];
c2.v[52] += (sum_32_5_025)*MainFormSLS->hh[65];
c2.v[52] += (sum_32_5_026)*MainFormSLS->hh[10];
c2.v[52] += (sum_32_5_027)*MainFormSLS->hh[115];
c2.v[52] += (sum_32_5_028)*MainFormSLS->hh[60];
c2.v[52] += (sum_32_5_029)*MainFormSLS->hh[5];
c2.v[52] += (sum_32_5_030)*MainFormSLS->hh[110];
c2.v[52] += (sum_32_5_031)*MainFormSLS->hh[55];

//frequency level id 107
c2.v[53] += (sum_160_1_000)*MainFormSLS->hh[0];
c2.v[53] += (sum_160_1_001)*MainFormSLS->hh[107];
c2.v[53] += (sum_160_1_002)*MainFormSLS->hh[54];
c2.v[53] += (sum_160_1_003)*MainFormSLS->hh[1];
c2.v[53] += (sum_160_1_004)*MainFormSLS->hh[108];
c2.v[53] += (sum_160_1_005)*MainFormSLS->hh[55];
c2.v[53] += (sum_160_1_006)*MainFormSLS->hh[2];
c2.v[53] += (sum_160_1_007)*MainFormSLS->hh[109];
c2.v[53] += (sum_160_1_008)*MainFormSLS->hh[56];
c2.v[53] += (sum_160_1_009)*MainFormSLS->hh[3];
c2.v[53] += (sum_160_1_010)*MainFormSLS->hh[110];
c2.v[53] += (sum_160_1_011)*MainFormSLS->hh[57];
c2.v[53] += (sum_160_1_012)*MainFormSLS->hh[4];
c2.v[53] += (sum_160_1_013)*MainFormSLS->hh[111];
c2.v[53] += (sum_160_1_014)*MainFormSLS->hh[58];
c2.v[53] += (sum_160_1_015)*MainFormSLS->hh[5];
c2.v[53] += (sum_160_1_016)*MainFormSLS->hh[112];
c2.v[53] += (sum_160_1_017)*MainFormSLS->hh[59];
c2.v[53] += (sum_160_1_018)*MainFormSLS->hh[6];
c2.v[53] += (sum_160_1_019)*MainFormSLS->hh[113];
c2.v[53] += (sum_160_1_020)*MainFormSLS->hh[60];
c2.v[53] += (sum_160_1_021)*MainFormSLS->hh[7];
c2.v[53] += (sum_160_1_022)*MainFormSLS->hh[114];
c2.v[53] += (sum_160_1_023)*MainFormSLS->hh[61];
c2.v[53] += (sum_160_1_024)*MainFormSLS->hh[8];
c2.v[53] += (sum_160_1_025)*MainFormSLS->hh[115];
c2.v[53] += (sum_160_1_026)*MainFormSLS->hh[62];
c2.v[53] += (sum_160_1_027)*MainFormSLS->hh[9];
c2.v[53] += (sum_160_1_028)*MainFormSLS->hh[116];
c2.v[53] += (sum_160_1_029)*MainFormSLS->hh[63];
c2.v[53] += (sum_160_1_030)*MainFormSLS->hh[10];
c2.v[53] += (sum_160_1_031)*MainFormSLS->hh[117];
c2.v[53] += (sum_160_1_032)*MainFormSLS->hh[64];
c2.v[53] += (sum_160_1_033)*MainFormSLS->hh[11];
c2.v[53] += (sum_160_1_034)*MainFormSLS->hh[118];
c2.v[53] += (sum_160_1_035)*MainFormSLS->hh[65];
c2.v[53] += (sum_160_1_036)*MainFormSLS->hh[12];
c2.v[53] += (sum_160_1_037)*MainFormSLS->hh[119];
c2.v[53] += (sum_160_1_038)*MainFormSLS->hh[66];
c2.v[53] += (sum_160_1_039)*MainFormSLS->hh[13];
c2.v[53] += (sum_160_1_040)*MainFormSLS->hh[120];
c2.v[53] += (sum_160_1_041)*MainFormSLS->hh[67];
c2.v[53] += (sum_160_1_042)*MainFormSLS->hh[14];
c2.v[53] += (sum_160_1_043)*MainFormSLS->hh[121];
c2.v[53] += (sum_160_1_044)*MainFormSLS->hh[68];
c2.v[53] += (sum_160_1_045)*MainFormSLS->hh[15];
c2.v[53] += (sum_160_1_046)*MainFormSLS->hh[122];
c2.v[53] += (sum_160_1_047)*MainFormSLS->hh[69];
c2.v[53] += (sum_160_1_048)*MainFormSLS->hh[16];
c2.v[53] += (sum_160_1_049)*MainFormSLS->hh[123];
c2.v[53] += (sum_160_1_050)*MainFormSLS->hh[70];
c2.v[53] += (sum_160_1_051)*MainFormSLS->hh[17];
c2.v[53] += (sum_160_1_052)*MainFormSLS->hh[124];
c2.v[53] += (sum_160_1_053)*MainFormSLS->hh[71];
c2.v[53] += (sum_160_1_054)*MainFormSLS->hh[18];
c2.v[53] += (sum_160_1_055)*MainFormSLS->hh[125];
c2.v[53] += (sum_160_1_056)*MainFormSLS->hh[72];
c2.v[53] += (sum_160_1_057)*MainFormSLS->hh[19];
c2.v[53] += (sum_160_1_058)*MainFormSLS->hh[126];
c2.v[53] += (sum_160_1_059)*MainFormSLS->hh[73];
c2.v[53] += (sum_160_1_060)*MainFormSLS->hh[20];
c2.v[53] += (sum_160_1_061)*MainFormSLS->hh[127];
c2.v[53] += (sum_160_1_062)*MainFormSLS->hh[74];
c2.v[53] += (sum_160_1_063)*MainFormSLS->hh[21];
c2.v[53] += (sum_160_1_064)*MainFormSLS->hh[128];
c2.v[53] += (sum_160_1_065)*MainFormSLS->hh[75];
c2.v[53] += (sum_160_1_066)*MainFormSLS->hh[22];
c2.v[53] += (sum_160_1_067)*MainFormSLS->hh[129];
c2.v[53] += (sum_160_1_068)*MainFormSLS->hh[76];
c2.v[53] += (sum_160_1_069)*MainFormSLS->hh[23];
c2.v[53] += (sum_160_1_070)*MainFormSLS->hh[130];
c2.v[53] += (sum_160_1_071)*MainFormSLS->hh[77];
c2.v[53] += (sum_160_1_072)*MainFormSLS->hh[24];
c2.v[53] += (sum_160_1_073)*MainFormSLS->hh[131];
c2.v[53] += (sum_160_1_074)*MainFormSLS->hh[78];
c2.v[53] += (sum_160_1_075)*MainFormSLS->hh[25];
c2.v[53] += (sum_160_1_076)*MainFormSLS->hh[132];
c2.v[53] += (sum_160_1_077)*MainFormSLS->hh[79];
c2.v[53] += (sum_160_1_078)*MainFormSLS->hh[26];
c2.v[53] += (sum_160_1_079)*MainFormSLS->hh[133];
c2.v[53] += (sum_160_1_080)*MainFormSLS->hh[80];
c2.v[53] += (sum_160_1_081)*MainFormSLS->hh[27];
c2.v[53] += (sum_160_1_082)*MainFormSLS->hh[134];
c2.v[53] += (sum_160_1_083)*MainFormSLS->hh[81];
c2.v[53] += (sum_160_1_084)*MainFormSLS->hh[28];
c2.v[53] += (sum_160_1_085)*MainFormSLS->hh[135];
c2.v[53] += (sum_160_1_086)*MainFormSLS->hh[82];
c2.v[53] += (sum_160_1_087)*MainFormSLS->hh[29];
c2.v[53] += (sum_160_1_088)*MainFormSLS->hh[136];
c2.v[53] += (sum_160_1_089)*MainFormSLS->hh[83];
c2.v[53] += (sum_160_1_090)*MainFormSLS->hh[30];
c2.v[53] += (sum_160_1_091)*MainFormSLS->hh[137];
c2.v[53] += (sum_160_1_092)*MainFormSLS->hh[84];
c2.v[53] += (sum_160_1_093)*MainFormSLS->hh[31];
c2.v[53] += (sum_160_1_094)*MainFormSLS->hh[138];
c2.v[53] += (sum_160_1_095)*MainFormSLS->hh[85];
c2.v[53] += (sum_160_1_096)*MainFormSLS->hh[32];
c2.v[53] += (sum_160_1_097)*MainFormSLS->hh[139];
c2.v[53] += (sum_160_1_098)*MainFormSLS->hh[86];
c2.v[53] += (sum_160_1_099)*MainFormSLS->hh[33];
c2.v[53] += (sum_160_1_100)*MainFormSLS->hh[140];
c2.v[53] += (sum_160_1_101)*MainFormSLS->hh[87];
c2.v[53] += (sum_160_1_102)*MainFormSLS->hh[34];
c2.v[53] += (sum_160_1_103)*MainFormSLS->hh[141];
c2.v[53] += (sum_160_1_104)*MainFormSLS->hh[88];
c2.v[53] += (sum_160_1_105)*MainFormSLS->hh[35];
c2.v[53] += (sum_160_1_106)*MainFormSLS->hh[142];
c2.v[53] += (sum_160_1_107)*MainFormSLS->hh[89];
c2.v[53] += (sum_160_1_108)*MainFormSLS->hh[36];
c2.v[53] += (sum_160_1_109)*MainFormSLS->hh[143];
c2.v[53] += (sum_160_1_110)*MainFormSLS->hh[90];
c2.v[53] += (sum_160_1_111)*MainFormSLS->hh[37];
c2.v[53] += (sum_160_1_112)*MainFormSLS->hh[144];
c2.v[53] += (sum_160_1_113)*MainFormSLS->hh[91];
c2.v[53] += (sum_160_1_114)*MainFormSLS->hh[38];
c2.v[53] += (sum_160_1_115)*MainFormSLS->hh[145];
c2.v[53] += (sum_160_1_116)*MainFormSLS->hh[92];
c2.v[53] += (sum_160_1_117)*MainFormSLS->hh[39];
c2.v[53] += (sum_160_1_118)*MainFormSLS->hh[146];
c2.v[53] += (sum_160_1_119)*MainFormSLS->hh[93];
c2.v[53] += (sum_160_1_120)*MainFormSLS->hh[40];
c2.v[53] += (sum_160_1_121)*MainFormSLS->hh[147];
c2.v[53] += (sum_160_1_122)*MainFormSLS->hh[94];
c2.v[53] += (sum_160_1_123)*MainFormSLS->hh[41];
c2.v[53] += (sum_160_1_124)*MainFormSLS->hh[148];
c2.v[53] += (sum_160_1_125)*MainFormSLS->hh[95];
c2.v[53] += (sum_160_1_126)*MainFormSLS->hh[42];
c2.v[53] += (sum_160_1_127)*MainFormSLS->hh[149];
c2.v[53] += (sum_160_1_128)*MainFormSLS->hh[96];
c2.v[53] += (sum_160_1_129)*MainFormSLS->hh[43];
c2.v[53] += (sum_160_1_130)*MainFormSLS->hh[150];
c2.v[53] += (sum_160_1_131)*MainFormSLS->hh[97];
c2.v[53] += (sum_160_1_132)*MainFormSLS->hh[44];
c2.v[53] += (sum_160_1_133)*MainFormSLS->hh[151];
c2.v[53] += (sum_160_1_134)*MainFormSLS->hh[98];
c2.v[53] += (sum_160_1_135)*MainFormSLS->hh[45];
c2.v[53] += (sum_160_1_136)*MainFormSLS->hh[152];
c2.v[53] += (sum_160_1_137)*MainFormSLS->hh[99];
c2.v[53] += (sum_160_1_138)*MainFormSLS->hh[46];
c2.v[53] += (sum_160_1_139)*MainFormSLS->hh[153];
c2.v[53] += (sum_160_1_140)*MainFormSLS->hh[100];
c2.v[53] += (sum_160_1_141)*MainFormSLS->hh[47];
c2.v[53] += (sum_160_1_142)*MainFormSLS->hh[154];
c2.v[53] += (sum_160_1_143)*MainFormSLS->hh[101];
c2.v[53] += (sum_160_1_144)*MainFormSLS->hh[48];
c2.v[53] += (sum_160_1_145)*MainFormSLS->hh[155];
c2.v[53] += (sum_160_1_146)*MainFormSLS->hh[102];
c2.v[53] += (sum_160_1_147)*MainFormSLS->hh[49];
c2.v[53] += (sum_160_1_148)*MainFormSLS->hh[156];
c2.v[53] += (sum_160_1_149)*MainFormSLS->hh[103];
c2.v[53] += (sum_160_1_150)*MainFormSLS->hh[50];
c2.v[53] += (sum_160_1_151)*MainFormSLS->hh[157];
c2.v[53] += (sum_160_1_152)*MainFormSLS->hh[104];
c2.v[53] += (sum_160_1_153)*MainFormSLS->hh[51];
c2.v[53] += (sum_160_1_154)*MainFormSLS->hh[158];
c2.v[53] += (sum_160_1_155)*MainFormSLS->hh[105];
c2.v[53] += (sum_160_1_156)*MainFormSLS->hh[52];
c2.v[53] += (sum_160_1_157)*MainFormSLS->hh[159];
c2.v[53] += (sum_160_1_158)*MainFormSLS->hh[106];
c2.v[53] += (sum_160_1_159)*MainFormSLS->hh[53];

//frequency level id 109
c2.v[54] += (sum_160_1_000)*MainFormSLS->hh[0];
c2.v[54] += (sum_160_1_001)*MainFormSLS->hh[109];
c2.v[54] += (sum_160_1_002)*MainFormSLS->hh[58];
c2.v[54] += (sum_160_1_003)*MainFormSLS->hh[7];
c2.v[54] += (sum_160_1_004)*MainFormSLS->hh[116];
c2.v[54] += (sum_160_1_005)*MainFormSLS->hh[65];
c2.v[54] += (sum_160_1_006)*MainFormSLS->hh[14];
c2.v[54] += (sum_160_1_007)*MainFormSLS->hh[123];
c2.v[54] += (sum_160_1_008)*MainFormSLS->hh[72];
c2.v[54] += (sum_160_1_009)*MainFormSLS->hh[21];
c2.v[54] += (sum_160_1_010)*MainFormSLS->hh[130];
c2.v[54] += (sum_160_1_011)*MainFormSLS->hh[79];
c2.v[54] += (sum_160_1_012)*MainFormSLS->hh[28];
c2.v[54] += (sum_160_1_013)*MainFormSLS->hh[137];
c2.v[54] += (sum_160_1_014)*MainFormSLS->hh[86];
c2.v[54] += (sum_160_1_015)*MainFormSLS->hh[35];
c2.v[54] += (sum_160_1_016)*MainFormSLS->hh[144];
c2.v[54] += (sum_160_1_017)*MainFormSLS->hh[93];
c2.v[54] += (sum_160_1_018)*MainFormSLS->hh[42];
c2.v[54] += (sum_160_1_019)*MainFormSLS->hh[151];
c2.v[54] += (sum_160_1_020)*MainFormSLS->hh[100];
c2.v[54] += (sum_160_1_021)*MainFormSLS->hh[49];
c2.v[54] += (sum_160_1_022)*MainFormSLS->hh[158];
c2.v[54] += (sum_160_1_023)*MainFormSLS->hh[107];
c2.v[54] += (sum_160_1_024)*MainFormSLS->hh[56];
c2.v[54] += (sum_160_1_025)*MainFormSLS->hh[5];
c2.v[54] += (sum_160_1_026)*MainFormSLS->hh[114];
c2.v[54] += (sum_160_1_027)*MainFormSLS->hh[63];
c2.v[54] += (sum_160_1_028)*MainFormSLS->hh[12];
c2.v[54] += (sum_160_1_029)*MainFormSLS->hh[121];
c2.v[54] += (sum_160_1_030)*MainFormSLS->hh[70];
c2.v[54] += (sum_160_1_031)*MainFormSLS->hh[19];
c2.v[54] += (sum_160_1_032)*MainFormSLS->hh[128];
c2.v[54] += (sum_160_1_033)*MainFormSLS->hh[77];
c2.v[54] += (sum_160_1_034)*MainFormSLS->hh[26];
c2.v[54] += (sum_160_1_035)*MainFormSLS->hh[135];
c2.v[54] += (sum_160_1_036)*MainFormSLS->hh[84];
c2.v[54] += (sum_160_1_037)*MainFormSLS->hh[33];
c2.v[54] += (sum_160_1_038)*MainFormSLS->hh[142];
c2.v[54] += (sum_160_1_039)*MainFormSLS->hh[91];
c2.v[54] += (sum_160_1_040)*MainFormSLS->hh[40];
c2.v[54] += (sum_160_1_041)*MainFormSLS->hh[149];
c2.v[54] += (sum_160_1_042)*MainFormSLS->hh[98];
c2.v[54] += (sum_160_1_043)*MainFormSLS->hh[47];
c2.v[54] += (sum_160_1_044)*MainFormSLS->hh[156];
c2.v[54] += (sum_160_1_045)*MainFormSLS->hh[105];
c2.v[54] += (sum_160_1_046)*MainFormSLS->hh[54];
c2.v[54] += (sum_160_1_047)*MainFormSLS->hh[3];
c2.v[54] += (sum_160_1_048)*MainFormSLS->hh[112];
c2.v[54] += (sum_160_1_049)*MainFormSLS->hh[61];
c2.v[54] += (sum_160_1_050)*MainFormSLS->hh[10];
c2.v[54] += (sum_160_1_051)*MainFormSLS->hh[119];
c2.v[54] += (sum_160_1_052)*MainFormSLS->hh[68];
c2.v[54] += (sum_160_1_053)*MainFormSLS->hh[17];
c2.v[54] += (sum_160_1_054)*MainFormSLS->hh[126];
c2.v[54] += (sum_160_1_055)*MainFormSLS->hh[75];
c2.v[54] += (sum_160_1_056)*MainFormSLS->hh[24];
c2.v[54] += (sum_160_1_057)*MainFormSLS->hh[133];
c2.v[54] += (sum_160_1_058)*MainFormSLS->hh[82];
c2.v[54] += (sum_160_1_059)*MainFormSLS->hh[31];
c2.v[54] += (sum_160_1_060)*MainFormSLS->hh[140];
c2.v[54] += (sum_160_1_061)*MainFormSLS->hh[89];
c2.v[54] += (sum_160_1_062)*MainFormSLS->hh[38];
c2.v[54] += (sum_160_1_063)*MainFormSLS->hh[147];
c2.v[54] += (sum_160_1_064)*MainFormSLS->hh[96];
c2.v[54] += (sum_160_1_065)*MainFormSLS->hh[45];
c2.v[54] += (sum_160_1_066)*MainFormSLS->hh[154];
c2.v[54] += (sum_160_1_067)*MainFormSLS->hh[103];
c2.v[54] += (sum_160_1_068)*MainFormSLS->hh[52];
c2.v[54] += (sum_160_1_069)*MainFormSLS->hh[1];
c2.v[54] += (sum_160_1_070)*MainFormSLS->hh[110];
c2.v[54] += (sum_160_1_071)*MainFormSLS->hh[59];
c2.v[54] += (sum_160_1_072)*MainFormSLS->hh[8];
c2.v[54] += (sum_160_1_073)*MainFormSLS->hh[117];
c2.v[54] += (sum_160_1_074)*MainFormSLS->hh[66];
c2.v[54] += (sum_160_1_075)*MainFormSLS->hh[15];
c2.v[54] += (sum_160_1_076)*MainFormSLS->hh[124];
c2.v[54] += (sum_160_1_077)*MainFormSLS->hh[73];
c2.v[54] += (sum_160_1_078)*MainFormSLS->hh[22];
c2.v[54] += (sum_160_1_079)*MainFormSLS->hh[131];
c2.v[54] += (sum_160_1_080)*MainFormSLS->hh[80];
c2.v[54] += (sum_160_1_081)*MainFormSLS->hh[29];
c2.v[54] += (sum_160_1_082)*MainFormSLS->hh[138];
c2.v[54] += (sum_160_1_083)*MainFormSLS->hh[87];
c2.v[54] += (sum_160_1_084)*MainFormSLS->hh[36];
c2.v[54] += (sum_160_1_085)*MainFormSLS->hh[145];
c2.v[54] += (sum_160_1_086)*MainFormSLS->hh[94];
c2.v[54] += (sum_160_1_087)*MainFormSLS->hh[43];
c2.v[54] += (sum_160_1_088)*MainFormSLS->hh[152];
c2.v[54] += (sum_160_1_089)*MainFormSLS->hh[101];
c2.v[54] += (sum_160_1_090)*MainFormSLS->hh[50];
c2.v[54] += (sum_160_1_091)*MainFormSLS->hh[159];
c2.v[54] += (sum_160_1_092)*MainFormSLS->hh[108];
c2.v[54] += (sum_160_1_093)*MainFormSLS->hh[57];
c2.v[54] += (sum_160_1_094)*MainFormSLS->hh[6];
c2.v[54] += (sum_160_1_095)*MainFormSLS->hh[115];
c2.v[54] += (sum_160_1_096)*MainFormSLS->hh[64];
c2.v[54] += (sum_160_1_097)*MainFormSLS->hh[13];
c2.v[54] += (sum_160_1_098)*MainFormSLS->hh[122];
c2.v[54] += (sum_160_1_099)*MainFormSLS->hh[71];
c2.v[54] += (sum_160_1_100)*MainFormSLS->hh[20];
c2.v[54] += (sum_160_1_101)*MainFormSLS->hh[129];
c2.v[54] += (sum_160_1_102)*MainFormSLS->hh[78];
c2.v[54] += (sum_160_1_103)*MainFormSLS->hh[27];
c2.v[54] += (sum_160_1_104)*MainFormSLS->hh[136];
c2.v[54] += (sum_160_1_105)*MainFormSLS->hh[85];
c2.v[54] += (sum_160_1_106)*MainFormSLS->hh[34];
c2.v[54] += (sum_160_1_107)*MainFormSLS->hh[143];
c2.v[54] += (sum_160_1_108)*MainFormSLS->hh[92];
c2.v[54] += (sum_160_1_109)*MainFormSLS->hh[41];
c2.v[54] += (sum_160_1_110)*MainFormSLS->hh[150];
c2.v[54] += (sum_160_1_111)*MainFormSLS->hh[99];
c2.v[54] += (sum_160_1_112)*MainFormSLS->hh[48];
c2.v[54] += (sum_160_1_113)*MainFormSLS->hh[157];
c2.v[54] += (sum_160_1_114)*MainFormSLS->hh[106];
c2.v[54] += (sum_160_1_115)*MainFormSLS->hh[55];
c2.v[54] += (sum_160_1_116)*MainFormSLS->hh[4];
c2.v[54] += (sum_160_1_117)*MainFormSLS->hh[113];
c2.v[54] += (sum_160_1_118)*MainFormSLS->hh[62];
c2.v[54] += (sum_160_1_119)*MainFormSLS->hh[11];
c2.v[54] += (sum_160_1_120)*MainFormSLS->hh[120];
c2.v[54] += (sum_160_1_121)*MainFormSLS->hh[69];
c2.v[54] += (sum_160_1_122)*MainFormSLS->hh[18];
c2.v[54] += (sum_160_1_123)*MainFormSLS->hh[127];
c2.v[54] += (sum_160_1_124)*MainFormSLS->hh[76];
c2.v[54] += (sum_160_1_125)*MainFormSLS->hh[25];
c2.v[54] += (sum_160_1_126)*MainFormSLS->hh[134];
c2.v[54] += (sum_160_1_127)*MainFormSLS->hh[83];
c2.v[54] += (sum_160_1_128)*MainFormSLS->hh[32];
c2.v[54] += (sum_160_1_129)*MainFormSLS->hh[141];
c2.v[54] += (sum_160_1_130)*MainFormSLS->hh[90];
c2.v[54] += (sum_160_1_131)*MainFormSLS->hh[39];
c2.v[54] += (sum_160_1_132)*MainFormSLS->hh[148];
c2.v[54] += (sum_160_1_133)*MainFormSLS->hh[97];
c2.v[54] += (sum_160_1_134)*MainFormSLS->hh[46];
c2.v[54] += (sum_160_1_135)*MainFormSLS->hh[155];
c2.v[54] += (sum_160_1_136)*MainFormSLS->hh[104];
c2.v[54] += (sum_160_1_137)*MainFormSLS->hh[53];
c2.v[54] += (sum_160_1_138)*MainFormSLS->hh[2];
c2.v[54] += (sum_160_1_139)*MainFormSLS->hh[111];
c2.v[54] += (sum_160_1_140)*MainFormSLS->hh[60];
c2.v[54] += (sum_160_1_141)*MainFormSLS->hh[9];
c2.v[54] += (sum_160_1_142)*MainFormSLS->hh[118];
c2.v[54] += (sum_160_1_143)*MainFormSLS->hh[67];
c2.v[54] += (sum_160_1_144)*MainFormSLS->hh[16];
c2.v[54] += (sum_160_1_145)*MainFormSLS->hh[125];
c2.v[54] += (sum_160_1_146)*MainFormSLS->hh[74];
c2.v[54] += (sum_160_1_147)*MainFormSLS->hh[23];
c2.v[54] += (sum_160_1_148)*MainFormSLS->hh[132];
c2.v[54] += (sum_160_1_149)*MainFormSLS->hh[81];
c2.v[54] += (sum_160_1_150)*MainFormSLS->hh[30];
c2.v[54] += (sum_160_1_151)*MainFormSLS->hh[139];
c2.v[54] += (sum_160_1_152)*MainFormSLS->hh[88];
c2.v[54] += (sum_160_1_153)*MainFormSLS->hh[37];
c2.v[54] += (sum_160_1_154)*MainFormSLS->hh[146];
c2.v[54] += (sum_160_1_155)*MainFormSLS->hh[95];
c2.v[54] += (sum_160_1_156)*MainFormSLS->hh[44];
c2.v[54] += (sum_160_1_157)*MainFormSLS->hh[153];
c2.v[54] += (sum_160_1_158)*MainFormSLS->hh[102];
c2.v[54] += (sum_160_1_159)*MainFormSLS->hh[51];

//frequency level id 111
c2.v[55] += (sum_160_1_000)*MainFormSLS->hh[0];
c2.v[55] += (sum_160_1_001)*MainFormSLS->hh[111];
c2.v[55] += (sum_160_1_002)*MainFormSLS->hh[62];
c2.v[55] += (sum_160_1_003)*MainFormSLS->hh[13];
c2.v[55] += (sum_160_1_004)*MainFormSLS->hh[124];
c2.v[55] += (sum_160_1_005)*MainFormSLS->hh[75];
c2.v[55] += (sum_160_1_006)*MainFormSLS->hh[26];
c2.v[55] += (sum_160_1_007)*MainFormSLS->hh[137];
c2.v[55] += (sum_160_1_008)*MainFormSLS->hh[88];
c2.v[55] += (sum_160_1_009)*MainFormSLS->hh[39];
c2.v[55] += (sum_160_1_010)*MainFormSLS->hh[150];
c2.v[55] += (sum_160_1_011)*MainFormSLS->hh[101];
c2.v[55] += (sum_160_1_012)*MainFormSLS->hh[52];
c2.v[55] += (sum_160_1_013)*MainFormSLS->hh[3];
c2.v[55] += (sum_160_1_014)*MainFormSLS->hh[114];
c2.v[55] += (sum_160_1_015)*MainFormSLS->hh[65];
c2.v[55] += (sum_160_1_016)*MainFormSLS->hh[16];
c2.v[55] += (sum_160_1_017)*MainFormSLS->hh[127];
c2.v[55] += (sum_160_1_018)*MainFormSLS->hh[78];
c2.v[55] += (sum_160_1_019)*MainFormSLS->hh[29];
c2.v[55] += (sum_160_1_020)*MainFormSLS->hh[140];
c2.v[55] += (sum_160_1_021)*MainFormSLS->hh[91];
c2.v[55] += (sum_160_1_022)*MainFormSLS->hh[42];
c2.v[55] += (sum_160_1_023)*MainFormSLS->hh[153];
c2.v[55] += (sum_160_1_024)*MainFormSLS->hh[104];
c2.v[55] += (sum_160_1_025)*MainFormSLS->hh[55];
c2.v[55] += (sum_160_1_026)*MainFormSLS->hh[6];
c2.v[55] += (sum_160_1_027)*MainFormSLS->hh[117];
c2.v[55] += (sum_160_1_028)*MainFormSLS->hh[68];
c2.v[55] += (sum_160_1_029)*MainFormSLS->hh[19];
c2.v[55] += (sum_160_1_030)*MainFormSLS->hh[130];
c2.v[55] += (sum_160_1_031)*MainFormSLS->hh[81];
c2.v[55] += (sum_160_1_032)*MainFormSLS->hh[32];
c2.v[55] += (sum_160_1_033)*MainFormSLS->hh[143];
c2.v[55] += (sum_160_1_034)*MainFormSLS->hh[94];
c2.v[55] += (sum_160_1_035)*MainFormSLS->hh[45];
c2.v[55] += (sum_160_1_036)*MainFormSLS->hh[156];
c2.v[55] += (sum_160_1_037)*MainFormSLS->hh[107];
c2.v[55] += (sum_160_1_038)*MainFormSLS->hh[58];
c2.v[55] += (sum_160_1_039)*MainFormSLS->hh[9];
c2.v[55] += (sum_160_1_040)*MainFormSLS->hh[120];
c2.v[55] += (sum_160_1_041)*MainFormSLS->hh[71];
c2.v[55] += (sum_160_1_042)*MainFormSLS->hh[22];
c2.v[55] += (sum_160_1_043)*MainFormSLS->hh[133];
c2.v[55] += (sum_160_1_044)*MainFormSLS->hh[84];
c2.v[55] += (sum_160_1_045)*MainFormSLS->hh[35];
c2.v[55] += (sum_160_1_046)*MainFormSLS->hh[146];
c2.v[55] += (sum_160_1_047)*MainFormSLS->hh[97];
c2.v[55] += (sum_160_1_048)*MainFormSLS->hh[48];
c2.v[55] += (sum_160_1_049)*MainFormSLS->hh[159];
c2.v[55] += (sum_160_1_050)*MainFormSLS->hh[110];
c2.v[55] += (sum_160_1_051)*MainFormSLS->hh[61];
c2.v[55] += (sum_160_1_052)*MainFormSLS->hh[12];
c2.v[55] += (sum_160_1_053)*MainFormSLS->hh[123];
c2.v[55] += (sum_160_1_054)*MainFormSLS->hh[74];
c2.v[55] += (sum_160_1_055)*MainFormSLS->hh[25];
c2.v[55] += (sum_160_1_056)*MainFormSLS->hh[136];
c2.v[55] += (sum_160_1_057)*MainFormSLS->hh[87];
c2.v[55] += (sum_160_1_058)*MainFormSLS->hh[38];
c2.v[55] += (sum_160_1_059)*MainFormSLS->hh[149];
c2.v[55] += (sum_160_1_060)*MainFormSLS->hh[100];
c2.v[55] += (sum_160_1_061)*MainFormSLS->hh[51];
c2.v[55] += (sum_160_1_062)*MainFormSLS->hh[2];
c2.v[55] += (sum_160_1_063)*MainFormSLS->hh[113];
c2.v[55] += (sum_160_1_064)*MainFormSLS->hh[64];
c2.v[55] += (sum_160_1_065)*MainFormSLS->hh[15];
c2.v[55] += (sum_160_1_066)*MainFormSLS->hh[126];
c2.v[55] += (sum_160_1_067)*MainFormSLS->hh[77];
c2.v[55] += (sum_160_1_068)*MainFormSLS->hh[28];
c2.v[55] += (sum_160_1_069)*MainFormSLS->hh[139];
c2.v[55] += (sum_160_1_070)*MainFormSLS->hh[90];
c2.v[55] += (sum_160_1_071)*MainFormSLS->hh[41];
c2.v[55] += (sum_160_1_072)*MainFormSLS->hh[152];
c2.v[55] += (sum_160_1_073)*MainFormSLS->hh[103];
c2.v[55] += (sum_160_1_074)*MainFormSLS->hh[54];
c2.v[55] += (sum_160_1_075)*MainFormSLS->hh[5];
c2.v[55] += (sum_160_1_076)*MainFormSLS->hh[116];
c2.v[55] += (sum_160_1_077)*MainFormSLS->hh[67];
c2.v[55] += (sum_160_1_078)*MainFormSLS->hh[18];
c2.v[55] += (sum_160_1_079)*MainFormSLS->hh[129];
c2.v[55] += (sum_160_1_080)*MainFormSLS->hh[80];
c2.v[55] += (sum_160_1_081)*MainFormSLS->hh[31];
c2.v[55] += (sum_160_1_082)*MainFormSLS->hh[142];
c2.v[55] += (sum_160_1_083)*MainFormSLS->hh[93];
c2.v[55] += (sum_160_1_084)*MainFormSLS->hh[44];
c2.v[55] += (sum_160_1_085)*MainFormSLS->hh[155];
c2.v[55] += (sum_160_1_086)*MainFormSLS->hh[106];
c2.v[55] += (sum_160_1_087)*MainFormSLS->hh[57];
c2.v[55] += (sum_160_1_088)*MainFormSLS->hh[8];
c2.v[55] += (sum_160_1_089)*MainFormSLS->hh[119];
c2.v[55] += (sum_160_1_090)*MainFormSLS->hh[70];
c2.v[55] += (sum_160_1_091)*MainFormSLS->hh[21];
c2.v[55] += (sum_160_1_092)*MainFormSLS->hh[132];
c2.v[55] += (sum_160_1_093)*MainFormSLS->hh[83];
c2.v[55] += (sum_160_1_094)*MainFormSLS->hh[34];
c2.v[55] += (sum_160_1_095)*MainFormSLS->hh[145];
c2.v[55] += (sum_160_1_096)*MainFormSLS->hh[96];
c2.v[55] += (sum_160_1_097)*MainFormSLS->hh[47];
c2.v[55] += (sum_160_1_098)*MainFormSLS->hh[158];
c2.v[55] += (sum_160_1_099)*MainFormSLS->hh[109];
c2.v[55] += (sum_160_1_100)*MainFormSLS->hh[60];
c2.v[55] += (sum_160_1_101)*MainFormSLS->hh[11];
c2.v[55] += (sum_160_1_102)*MainFormSLS->hh[122];
c2.v[55] += (sum_160_1_103)*MainFormSLS->hh[73];
c2.v[55] += (sum_160_1_104)*MainFormSLS->hh[24];
c2.v[55] += (sum_160_1_105)*MainFormSLS->hh[135];
c2.v[55] += (sum_160_1_106)*MainFormSLS->hh[86];
c2.v[55] += (sum_160_1_107)*MainFormSLS->hh[37];
c2.v[55] += (sum_160_1_108)*MainFormSLS->hh[148];
c2.v[55] += (sum_160_1_109)*MainFormSLS->hh[99];
c2.v[55] += (sum_160_1_110)*MainFormSLS->hh[50];
c2.v[55] += (sum_160_1_111)*MainFormSLS->hh[1];
c2.v[55] += (sum_160_1_112)*MainFormSLS->hh[112];
c2.v[55] += (sum_160_1_113)*MainFormSLS->hh[63];
c2.v[55] += (sum_160_1_114)*MainFormSLS->hh[14];
c2.v[55] += (sum_160_1_115)*MainFormSLS->hh[125];
c2.v[55] += (sum_160_1_116)*MainFormSLS->hh[76];
c2.v[55] += (sum_160_1_117)*MainFormSLS->hh[27];
c2.v[55] += (sum_160_1_118)*MainFormSLS->hh[138];
c2.v[55] += (sum_160_1_119)*MainFormSLS->hh[89];
c2.v[55] += (sum_160_1_120)*MainFormSLS->hh[40];
c2.v[55] += (sum_160_1_121)*MainFormSLS->hh[151];
c2.v[55] += (sum_160_1_122)*MainFormSLS->hh[102];
c2.v[55] += (sum_160_1_123)*MainFormSLS->hh[53];
c2.v[55] += (sum_160_1_124)*MainFormSLS->hh[4];
c2.v[55] += (sum_160_1_125)*MainFormSLS->hh[115];
c2.v[55] += (sum_160_1_126)*MainFormSLS->hh[66];
c2.v[55] += (sum_160_1_127)*MainFormSLS->hh[17];
c2.v[55] += (sum_160_1_128)*MainFormSLS->hh[128];
c2.v[55] += (sum_160_1_129)*MainFormSLS->hh[79];
c2.v[55] += (sum_160_1_130)*MainFormSLS->hh[30];
c2.v[55] += (sum_160_1_131)*MainFormSLS->hh[141];
c2.v[55] += (sum_160_1_132)*MainFormSLS->hh[92];
c2.v[55] += (sum_160_1_133)*MainFormSLS->hh[43];
c2.v[55] += (sum_160_1_134)*MainFormSLS->hh[154];
c2.v[55] += (sum_160_1_135)*MainFormSLS->hh[105];
c2.v[55] += (sum_160_1_136)*MainFormSLS->hh[56];
c2.v[55] += (sum_160_1_137)*MainFormSLS->hh[7];
c2.v[55] += (sum_160_1_138)*MainFormSLS->hh[118];
c2.v[55] += (sum_160_1_139)*MainFormSLS->hh[69];
c2.v[55] += (sum_160_1_140)*MainFormSLS->hh[20];
c2.v[55] += (sum_160_1_141)*MainFormSLS->hh[131];
c2.v[55] += (sum_160_1_142)*MainFormSLS->hh[82];
c2.v[55] += (sum_160_1_143)*MainFormSLS->hh[33];
c2.v[55] += (sum_160_1_144)*MainFormSLS->hh[144];
c2.v[55] += (sum_160_1_145)*MainFormSLS->hh[95];
c2.v[55] += (sum_160_1_146)*MainFormSLS->hh[46];
c2.v[55] += (sum_160_1_147)*MainFormSLS->hh[157];
c2.v[55] += (sum_160_1_148)*MainFormSLS->hh[108];
c2.v[55] += (sum_160_1_149)*MainFormSLS->hh[59];
c2.v[55] += (sum_160_1_150)*MainFormSLS->hh[10];
c2.v[55] += (sum_160_1_151)*MainFormSLS->hh[121];
c2.v[55] += (sum_160_1_152)*MainFormSLS->hh[72];
c2.v[55] += (sum_160_1_153)*MainFormSLS->hh[23];
c2.v[55] += (sum_160_1_154)*MainFormSLS->hh[134];
c2.v[55] += (sum_160_1_155)*MainFormSLS->hh[85];
c2.v[55] += (sum_160_1_156)*MainFormSLS->hh[36];
c2.v[55] += (sum_160_1_157)*MainFormSLS->hh[147];
c2.v[55] += (sum_160_1_158)*MainFormSLS->hh[98];
c2.v[55] += (sum_160_1_159)*MainFormSLS->hh[49];

//frequency level id 113
c2.v[56] += (sum_160_1_000)*MainFormSLS->hh[0];
c2.v[56] += (sum_160_1_001)*MainFormSLS->hh[113];
c2.v[56] += (sum_160_1_002)*MainFormSLS->hh[66];
c2.v[56] += (sum_160_1_003)*MainFormSLS->hh[19];
c2.v[56] += (sum_160_1_004)*MainFormSLS->hh[132];
c2.v[56] += (sum_160_1_005)*MainFormSLS->hh[85];
c2.v[56] += (sum_160_1_006)*MainFormSLS->hh[38];
c2.v[56] += (sum_160_1_007)*MainFormSLS->hh[151];
c2.v[56] += (sum_160_1_008)*MainFormSLS->hh[104];
c2.v[56] += (sum_160_1_009)*MainFormSLS->hh[57];
c2.v[56] += (sum_160_1_010)*MainFormSLS->hh[10];
c2.v[56] += (sum_160_1_011)*MainFormSLS->hh[123];
c2.v[56] += (sum_160_1_012)*MainFormSLS->hh[76];
c2.v[56] += (sum_160_1_013)*MainFormSLS->hh[29];
c2.v[56] += (sum_160_1_014)*MainFormSLS->hh[142];
c2.v[56] += (sum_160_1_015)*MainFormSLS->hh[95];
c2.v[56] += (sum_160_1_016)*MainFormSLS->hh[48];
c2.v[56] += (sum_160_1_017)*MainFormSLS->hh[1];
c2.v[56] += (sum_160_1_018)*MainFormSLS->hh[114];
c2.v[56] += (sum_160_1_019)*MainFormSLS->hh[67];
c2.v[56] += (sum_160_1_020)*MainFormSLS->hh[20];
c2.v[56] += (sum_160_1_021)*MainFormSLS->hh[133];
c2.v[56] += (sum_160_1_022)*MainFormSLS->hh[86];
c2.v[56] += (sum_160_1_023)*MainFormSLS->hh[39];
c2.v[56] += (sum_160_1_024)*MainFormSLS->hh[152];
c2.v[56] += (sum_160_1_025)*MainFormSLS->hh[105];
c2.v[56] += (sum_160_1_026)*MainFormSLS->hh[58];
c2.v[56] += (sum_160_1_027)*MainFormSLS->hh[11];
c2.v[56] += (sum_160_1_028)*MainFormSLS->hh[124];
c2.v[56] += (sum_160_1_029)*MainFormSLS->hh[77];
c2.v[56] += (sum_160_1_030)*MainFormSLS->hh[30];
c2.v[56] += (sum_160_1_031)*MainFormSLS->hh[143];
c2.v[56] += (sum_160_1_032)*MainFormSLS->hh[96];
c2.v[56] += (sum_160_1_033)*MainFormSLS->hh[49];
c2.v[56] += (sum_160_1_034)*MainFormSLS->hh[2];
c2.v[56] += (sum_160_1_035)*MainFormSLS->hh[115];
c2.v[56] += (sum_160_1_036)*MainFormSLS->hh[68];
c2.v[56] += (sum_160_1_037)*MainFormSLS->hh[21];
c2.v[56] += (sum_160_1_038)*MainFormSLS->hh[134];
c2.v[56] += (sum_160_1_039)*MainFormSLS->hh[87];
c2.v[56] += (sum_160_1_040)*MainFormSLS->hh[40];
c2.v[56] += (sum_160_1_041)*MainFormSLS->hh[153];
c2.v[56] += (sum_160_1_042)*MainFormSLS->hh[106];
c2.v[56] += (sum_160_1_043)*MainFormSLS->hh[59];
c2.v[56] += (sum_160_1_044)*MainFormSLS->hh[12];
c2.v[56] += (sum_160_1_045)*MainFormSLS->hh[125];
c2.v[56] += (sum_160_1_046)*MainFormSLS->hh[78];
c2.v[56] += (sum_160_1_047)*MainFormSLS->hh[31];
c2.v[56] += (sum_160_1_048)*MainFormSLS->hh[144];
c2.v[56] += (sum_160_1_049)*MainFormSLS->hh[97];
c2.v[56] += (sum_160_1_050)*MainFormSLS->hh[50];
c2.v[56] += (sum_160_1_051)*MainFormSLS->hh[3];
c2.v[56] += (sum_160_1_052)*MainFormSLS->hh[116];
c2.v[56] += (sum_160_1_053)*MainFormSLS->hh[69];
c2.v[56] += (sum_160_1_054)*MainFormSLS->hh[22];
c2.v[56] += (sum_160_1_055)*MainFormSLS->hh[135];
c2.v[56] += (sum_160_1_056)*MainFormSLS->hh[88];
c2.v[56] += (sum_160_1_057)*MainFormSLS->hh[41];
c2.v[56] += (sum_160_1_058)*MainFormSLS->hh[154];
c2.v[56] += (sum_160_1_059)*MainFormSLS->hh[107];
c2.v[56] += (sum_160_1_060)*MainFormSLS->hh[60];
c2.v[56] += (sum_160_1_061)*MainFormSLS->hh[13];
c2.v[56] += (sum_160_1_062)*MainFormSLS->hh[126];
c2.v[56] += (sum_160_1_063)*MainFormSLS->hh[79];
c2.v[56] += (sum_160_1_064)*MainFormSLS->hh[32];
c2.v[56] += (sum_160_1_065)*MainFormSLS->hh[145];
c2.v[56] += (sum_160_1_066)*MainFormSLS->hh[98];
c2.v[56] += (sum_160_1_067)*MainFormSLS->hh[51];
c2.v[56] += (sum_160_1_068)*MainFormSLS->hh[4];
c2.v[56] += (sum_160_1_069)*MainFormSLS->hh[117];
c2.v[56] += (sum_160_1_070)*MainFormSLS->hh[70];
c2.v[56] += (sum_160_1_071)*MainFormSLS->hh[23];
c2.v[56] += (sum_160_1_072)*MainFormSLS->hh[136];
c2.v[56] += (sum_160_1_073)*MainFormSLS->hh[89];
c2.v[56] += (sum_160_1_074)*MainFormSLS->hh[42];
c2.v[56] += (sum_160_1_075)*MainFormSLS->hh[155];
c2.v[56] += (sum_160_1_076)*MainFormSLS->hh[108];
c2.v[56] += (sum_160_1_077)*MainFormSLS->hh[61];
c2.v[56] += (sum_160_1_078)*MainFormSLS->hh[14];
c2.v[56] += (sum_160_1_079)*MainFormSLS->hh[127];
c2.v[56] += (sum_160_1_080)*MainFormSLS->hh[80];
c2.v[56] += (sum_160_1_081)*MainFormSLS->hh[33];
c2.v[56] += (sum_160_1_082)*MainFormSLS->hh[146];
c2.v[56] += (sum_160_1_083)*MainFormSLS->hh[99];
c2.v[56] += (sum_160_1_084)*MainFormSLS->hh[52];
c2.v[56] += (sum_160_1_085)*MainFormSLS->hh[5];
c2.v[56] += (sum_160_1_086)*MainFormSLS->hh[118];
c2.v[56] += (sum_160_1_087)*MainFormSLS->hh[71];
c2.v[56] += (sum_160_1_088)*MainFormSLS->hh[24];
c2.v[56] += (sum_160_1_089)*MainFormSLS->hh[137];
c2.v[56] += (sum_160_1_090)*MainFormSLS->hh[90];
c2.v[56] += (sum_160_1_091)*MainFormSLS->hh[43];
c2.v[56] += (sum_160_1_092)*MainFormSLS->hh[156];
c2.v[56] += (sum_160_1_093)*MainFormSLS->hh[109];
c2.v[56] += (sum_160_1_094)*MainFormSLS->hh[62];
c2.v[56] += (sum_160_1_095)*MainFormSLS->hh[15];
c2.v[56] += (sum_160_1_096)*MainFormSLS->hh[128];
c2.v[56] += (sum_160_1_097)*MainFormSLS->hh[81];
c2.v[56] += (sum_160_1_098)*MainFormSLS->hh[34];
c2.v[56] += (sum_160_1_099)*MainFormSLS->hh[147];
c2.v[56] += (sum_160_1_100)*MainFormSLS->hh[100];
c2.v[56] += (sum_160_1_101)*MainFormSLS->hh[53];
c2.v[56] += (sum_160_1_102)*MainFormSLS->hh[6];
c2.v[56] += (sum_160_1_103)*MainFormSLS->hh[119];
c2.v[56] += (sum_160_1_104)*MainFormSLS->hh[72];
c2.v[56] += (sum_160_1_105)*MainFormSLS->hh[25];
c2.v[56] += (sum_160_1_106)*MainFormSLS->hh[138];
c2.v[56] += (sum_160_1_107)*MainFormSLS->hh[91];
c2.v[56] += (sum_160_1_108)*MainFormSLS->hh[44];
c2.v[56] += (sum_160_1_109)*MainFormSLS->hh[157];
c2.v[56] += (sum_160_1_110)*MainFormSLS->hh[110];
c2.v[56] += (sum_160_1_111)*MainFormSLS->hh[63];
c2.v[56] += (sum_160_1_112)*MainFormSLS->hh[16];
c2.v[56] += (sum_160_1_113)*MainFormSLS->hh[129];
c2.v[56] += (sum_160_1_114)*MainFormSLS->hh[82];
c2.v[56] += (sum_160_1_115)*MainFormSLS->hh[35];
c2.v[56] += (sum_160_1_116)*MainFormSLS->hh[148];
c2.v[56] += (sum_160_1_117)*MainFormSLS->hh[101];
c2.v[56] += (sum_160_1_118)*MainFormSLS->hh[54];
c2.v[56] += (sum_160_1_119)*MainFormSLS->hh[7];
c2.v[56] += (sum_160_1_120)*MainFormSLS->hh[120];
c2.v[56] += (sum_160_1_121)*MainFormSLS->hh[73];
c2.v[56] += (sum_160_1_122)*MainFormSLS->hh[26];
c2.v[56] += (sum_160_1_123)*MainFormSLS->hh[139];
c2.v[56] += (sum_160_1_124)*MainFormSLS->hh[92];
c2.v[56] += (sum_160_1_125)*MainFormSLS->hh[45];
c2.v[56] += (sum_160_1_126)*MainFormSLS->hh[158];
c2.v[56] += (sum_160_1_127)*MainFormSLS->hh[111];
c2.v[56] += (sum_160_1_128)*MainFormSLS->hh[64];
c2.v[56] += (sum_160_1_129)*MainFormSLS->hh[17];
c2.v[56] += (sum_160_1_130)*MainFormSLS->hh[130];
c2.v[56] += (sum_160_1_131)*MainFormSLS->hh[83];
c2.v[56] += (sum_160_1_132)*MainFormSLS->hh[36];
c2.v[56] += (sum_160_1_133)*MainFormSLS->hh[149];
c2.v[56] += (sum_160_1_134)*MainFormSLS->hh[102];
c2.v[56] += (sum_160_1_135)*MainFormSLS->hh[55];
c2.v[56] += (sum_160_1_136)*MainFormSLS->hh[8];
c2.v[56] += (sum_160_1_137)*MainFormSLS->hh[121];
c2.v[56] += (sum_160_1_138)*MainFormSLS->hh[74];
c2.v[56] += (sum_160_1_139)*MainFormSLS->hh[27];
c2.v[56] += (sum_160_1_140)*MainFormSLS->hh[140];
c2.v[56] += (sum_160_1_141)*MainFormSLS->hh[93];
c2.v[56] += (sum_160_1_142)*MainFormSLS->hh[46];
c2.v[56] += (sum_160_1_143)*MainFormSLS->hh[159];
c2.v[56] += (sum_160_1_144)*MainFormSLS->hh[112];
c2.v[56] += (sum_160_1_145)*MainFormSLS->hh[65];
c2.v[56] += (sum_160_1_146)*MainFormSLS->hh[18];
c2.v[56] += (sum_160_1_147)*MainFormSLS->hh[131];
c2.v[56] += (sum_160_1_148)*MainFormSLS->hh[84];
c2.v[56] += (sum_160_1_149)*MainFormSLS->hh[37];
c2.v[56] += (sum_160_1_150)*MainFormSLS->hh[150];
c2.v[56] += (sum_160_1_151)*MainFormSLS->hh[103];
c2.v[56] += (sum_160_1_152)*MainFormSLS->hh[56];
c2.v[56] += (sum_160_1_153)*MainFormSLS->hh[9];
c2.v[56] += (sum_160_1_154)*MainFormSLS->hh[122];
c2.v[56] += (sum_160_1_155)*MainFormSLS->hh[75];
c2.v[56] += (sum_160_1_156)*MainFormSLS->hh[28];
c2.v[56] += (sum_160_1_157)*MainFormSLS->hh[141];
c2.v[56] += (sum_160_1_158)*MainFormSLS->hh[94];
c2.v[56] += (sum_160_1_159)*MainFormSLS->hh[47];

//frequency level id 115
c2.v[57] += (sum_32_5_000)*MainFormSLS->hh[0];
c2.v[57] += (sum_32_5_001)*MainFormSLS->hh[115];
c2.v[57] += (sum_32_5_002)*MainFormSLS->hh[70];
c2.v[57] += (sum_32_5_003)*MainFormSLS->hh[25];
c2.v[57] += (sum_32_5_004)*MainFormSLS->hh[140];
c2.v[57] += (sum_32_5_005)*MainFormSLS->hh[95];
c2.v[57] += (sum_32_5_006)*MainFormSLS->hh[50];
c2.v[57] += (sum_32_5_007)*MainFormSLS->hh[5];
c2.v[57] += (sum_32_5_008)*MainFormSLS->hh[120];
c2.v[57] += (sum_32_5_009)*MainFormSLS->hh[75];
c2.v[57] += (sum_32_5_010)*MainFormSLS->hh[30];
c2.v[57] += (sum_32_5_011)*MainFormSLS->hh[145];
c2.v[57] += (sum_32_5_012)*MainFormSLS->hh[100];
c2.v[57] += (sum_32_5_013)*MainFormSLS->hh[55];
c2.v[57] += (sum_32_5_014)*MainFormSLS->hh[10];
c2.v[57] += (sum_32_5_015)*MainFormSLS->hh[125];
c2.v[57] += (sum_32_5_016)*MainFormSLS->hh[80];
c2.v[57] += (sum_32_5_017)*MainFormSLS->hh[35];
c2.v[57] += (sum_32_5_018)*MainFormSLS->hh[150];
c2.v[57] += (sum_32_5_019)*MainFormSLS->hh[105];
c2.v[57] += (sum_32_5_020)*MainFormSLS->hh[60];
c2.v[57] += (sum_32_5_021)*MainFormSLS->hh[15];
c2.v[57] += (sum_32_5_022)*MainFormSLS->hh[130];
c2.v[57] += (sum_32_5_023)*MainFormSLS->hh[85];
c2.v[57] += (sum_32_5_024)*MainFormSLS->hh[40];
c2.v[57] += (sum_32_5_025)*MainFormSLS->hh[155];
c2.v[57] += (sum_32_5_026)*MainFormSLS->hh[110];
c2.v[57] += (sum_32_5_027)*MainFormSLS->hh[65];
c2.v[57] += (sum_32_5_028)*MainFormSLS->hh[20];
c2.v[57] += (sum_32_5_029)*MainFormSLS->hh[135];
c2.v[57] += (sum_32_5_030)*MainFormSLS->hh[90];
c2.v[57] += (sum_32_5_031)*MainFormSLS->hh[45];

//frequency level id 117
c2.v[58] += (sum_160_1_000)*MainFormSLS->hh[0];
c2.v[58] += (sum_160_1_001)*MainFormSLS->hh[117];
c2.v[58] += (sum_160_1_002)*MainFormSLS->hh[74];
c2.v[58] += (sum_160_1_003)*MainFormSLS->hh[31];
c2.v[58] += (sum_160_1_004)*MainFormSLS->hh[148];
c2.v[58] += (sum_160_1_005)*MainFormSLS->hh[105];
c2.v[58] += (sum_160_1_006)*MainFormSLS->hh[62];
c2.v[58] += (sum_160_1_007)*MainFormSLS->hh[19];
c2.v[58] += (sum_160_1_008)*MainFormSLS->hh[136];
c2.v[58] += (sum_160_1_009)*MainFormSLS->hh[93];
c2.v[58] += (sum_160_1_010)*MainFormSLS->hh[50];
c2.v[58] += (sum_160_1_011)*MainFormSLS->hh[7];
c2.v[58] += (sum_160_1_012)*MainFormSLS->hh[124];
c2.v[58] += (sum_160_1_013)*MainFormSLS->hh[81];
c2.v[58] += (sum_160_1_014)*MainFormSLS->hh[38];
c2.v[58] += (sum_160_1_015)*MainFormSLS->hh[155];
c2.v[58] += (sum_160_1_016)*MainFormSLS->hh[112];
c2.v[58] += (sum_160_1_017)*MainFormSLS->hh[69];
c2.v[58] += (sum_160_1_018)*MainFormSLS->hh[26];
c2.v[58] += (sum_160_1_019)*MainFormSLS->hh[143];
c2.v[58] += (sum_160_1_020)*MainFormSLS->hh[100];
c2.v[58] += (sum_160_1_021)*MainFormSLS->hh[57];
c2.v[58] += (sum_160_1_022)*MainFormSLS->hh[14];
c2.v[58] += (sum_160_1_023)*MainFormSLS->hh[131];
c2.v[58] += (sum_160_1_024)*MainFormSLS->hh[88];
c2.v[58] += (sum_160_1_025)*MainFormSLS->hh[45];
c2.v[58] += (sum_160_1_026)*MainFormSLS->hh[2];
c2.v[58] += (sum_160_1_027)*MainFormSLS->hh[119];
c2.v[58] += (sum_160_1_028)*MainFormSLS->hh[76];
c2.v[58] += (sum_160_1_029)*MainFormSLS->hh[33];
c2.v[58] += (sum_160_1_030)*MainFormSLS->hh[150];
c2.v[58] += (sum_160_1_031)*MainFormSLS->hh[107];
c2.v[58] += (sum_160_1_032)*MainFormSLS->hh[64];
c2.v[58] += (sum_160_1_033)*MainFormSLS->hh[21];
c2.v[58] += (sum_160_1_034)*MainFormSLS->hh[138];
c2.v[58] += (sum_160_1_035)*MainFormSLS->hh[95];
c2.v[58] += (sum_160_1_036)*MainFormSLS->hh[52];
c2.v[58] += (sum_160_1_037)*MainFormSLS->hh[9];
c2.v[58] += (sum_160_1_038)*MainFormSLS->hh[126];
c2.v[58] += (sum_160_1_039)*MainFormSLS->hh[83];
c2.v[58] += (sum_160_1_040)*MainFormSLS->hh[40];
c2.v[58] += (sum_160_1_041)*MainFormSLS->hh[157];
c2.v[58] += (sum_160_1_042)*MainFormSLS->hh[114];
c2.v[58] += (sum_160_1_043)*MainFormSLS->hh[71];
c2.v[58] += (sum_160_1_044)*MainFormSLS->hh[28];
c2.v[58] += (sum_160_1_045)*MainFormSLS->hh[145];
c2.v[58] += (sum_160_1_046)*MainFormSLS->hh[102];
c2.v[58] += (sum_160_1_047)*MainFormSLS->hh[59];
c2.v[58] += (sum_160_1_048)*MainFormSLS->hh[16];
c2.v[58] += (sum_160_1_049)*MainFormSLS->hh[133];
c2.v[58] += (sum_160_1_050)*MainFormSLS->hh[90];
c2.v[58] += (sum_160_1_051)*MainFormSLS->hh[47];
c2.v[58] += (sum_160_1_052)*MainFormSLS->hh[4];
c2.v[58] += (sum_160_1_053)*MainFormSLS->hh[121];
c2.v[58] += (sum_160_1_054)*MainFormSLS->hh[78];
c2.v[58] += (sum_160_1_055)*MainFormSLS->hh[35];
c2.v[58] += (sum_160_1_056)*MainFormSLS->hh[152];
c2.v[58] += (sum_160_1_057)*MainFormSLS->hh[109];
c2.v[58] += (sum_160_1_058)*MainFormSLS->hh[66];
c2.v[58] += (sum_160_1_059)*MainFormSLS->hh[23];
c2.v[58] += (sum_160_1_060)*MainFormSLS->hh[140];
c2.v[58] += (sum_160_1_061)*MainFormSLS->hh[97];
c2.v[58] += (sum_160_1_062)*MainFormSLS->hh[54];
c2.v[58] += (sum_160_1_063)*MainFormSLS->hh[11];
c2.v[58] += (sum_160_1_064)*MainFormSLS->hh[128];
c2.v[58] += (sum_160_1_065)*MainFormSLS->hh[85];
c2.v[58] += (sum_160_1_066)*MainFormSLS->hh[42];
c2.v[58] += (sum_160_1_067)*MainFormSLS->hh[159];
c2.v[58] += (sum_160_1_068)*MainFormSLS->hh[116];
c2.v[58] += (sum_160_1_069)*MainFormSLS->hh[73];
c2.v[58] += (sum_160_1_070)*MainFormSLS->hh[30];
c2.v[58] += (sum_160_1_071)*MainFormSLS->hh[147];
c2.v[58] += (sum_160_1_072)*MainFormSLS->hh[104];
c2.v[58] += (sum_160_1_073)*MainFormSLS->hh[61];
c2.v[58] += (sum_160_1_074)*MainFormSLS->hh[18];
c2.v[58] += (sum_160_1_075)*MainFormSLS->hh[135];
c2.v[58] += (sum_160_1_076)*MainFormSLS->hh[92];
c2.v[58] += (sum_160_1_077)*MainFormSLS->hh[49];
c2.v[58] += (sum_160_1_078)*MainFormSLS->hh[6];
c2.v[58] += (sum_160_1_079)*MainFormSLS->hh[123];
c2.v[58] += (sum_160_1_080)*MainFormSLS->hh[80];
c2.v[58] += (sum_160_1_081)*MainFormSLS->hh[37];
c2.v[58] += (sum_160_1_082)*MainFormSLS->hh[154];
c2.v[58] += (sum_160_1_083)*MainFormSLS->hh[111];
c2.v[58] += (sum_160_1_084)*MainFormSLS->hh[68];
c2.v[58] += (sum_160_1_085)*MainFormSLS->hh[25];
c2.v[58] += (sum_160_1_086)*MainFormSLS->hh[142];
c2.v[58] += (sum_160_1_087)*MainFormSLS->hh[99];
c2.v[58] += (sum_160_1_088)*MainFormSLS->hh[56];
c2.v[58] += (sum_160_1_089)*MainFormSLS->hh[13];
c2.v[58] += (sum_160_1_090)*MainFormSLS->hh[130];
c2.v[58] += (sum_160_1_091)*MainFormSLS->hh[87];
c2.v[58] += (sum_160_1_092)*MainFormSLS->hh[44];
c2.v[58] += (sum_160_1_093)*MainFormSLS->hh[1];
c2.v[58] += (sum_160_1_094)*MainFormSLS->hh[118];
c2.v[58] += (sum_160_1_095)*MainFormSLS->hh[75];
c2.v[58] += (sum_160_1_096)*MainFormSLS->hh[32];
c2.v[58] += (sum_160_1_097)*MainFormSLS->hh[149];
c2.v[58] += (sum_160_1_098)*MainFormSLS->hh[106];
c2.v[58] += (sum_160_1_099)*MainFormSLS->hh[63];
c2.v[58] += (sum_160_1_100)*MainFormSLS->hh[20];
c2.v[58] += (sum_160_1_101)*MainFormSLS->hh[137];
c2.v[58] += (sum_160_1_102)*MainFormSLS->hh[94];
c2.v[58] += (sum_160_1_103)*MainFormSLS->hh[51];
c2.v[58] += (sum_160_1_104)*MainFormSLS->hh[8];
c2.v[58] += (sum_160_1_105)*MainFormSLS->hh[125];
c2.v[58] += (sum_160_1_106)*MainFormSLS->hh[82];
c2.v[58] += (sum_160_1_107)*MainFormSLS->hh[39];
c2.v[58] += (sum_160_1_108)*MainFormSLS->hh[156];
c2.v[58] += (sum_160_1_109)*MainFormSLS->hh[113];
c2.v[58] += (sum_160_1_110)*MainFormSLS->hh[70];
c2.v[58] += (sum_160_1_111)*MainFormSLS->hh[27];
c2.v[58] += (sum_160_1_112)*MainFormSLS->hh[144];
c2.v[58] += (sum_160_1_113)*MainFormSLS->hh[101];
c2.v[58] += (sum_160_1_114)*MainFormSLS->hh[58];
c2.v[58] += (sum_160_1_115)*MainFormSLS->hh[15];
c2.v[58] += (sum_160_1_116)*MainFormSLS->hh[132];
c2.v[58] += (sum_160_1_117)*MainFormSLS->hh[89];
c2.v[58] += (sum_160_1_118)*MainFormSLS->hh[46];
c2.v[58] += (sum_160_1_119)*MainFormSLS->hh[3];
c2.v[58] += (sum_160_1_120)*MainFormSLS->hh[120];
c2.v[58] += (sum_160_1_121)*MainFormSLS->hh[77];
c2.v[58] += (sum_160_1_122)*MainFormSLS->hh[34];
c2.v[58] += (sum_160_1_123)*MainFormSLS->hh[151];
c2.v[58] += (sum_160_1_124)*MainFormSLS->hh[108];
c2.v[58] += (sum_160_1_125)*MainFormSLS->hh[65];
c2.v[58] += (sum_160_1_126)*MainFormSLS->hh[22];
c2.v[58] += (sum_160_1_127)*MainFormSLS->hh[139];
c2.v[58] += (sum_160_1_128)*MainFormSLS->hh[96];
c2.v[58] += (sum_160_1_129)*MainFormSLS->hh[53];
c2.v[58] += (sum_160_1_130)*MainFormSLS->hh[10];
c2.v[58] += (sum_160_1_131)*MainFormSLS->hh[127];
c2.v[58] += (sum_160_1_132)*MainFormSLS->hh[84];
c2.v[58] += (sum_160_1_133)*MainFormSLS->hh[41];
c2.v[58] += (sum_160_1_134)*MainFormSLS->hh[158];
c2.v[58] += (sum_160_1_135)*MainFormSLS->hh[115];
c2.v[58] += (sum_160_1_136)*MainFormSLS->hh[72];
c2.v[58] += (sum_160_1_137)*MainFormSLS->hh[29];
c2.v[58] += (sum_160_1_138)*MainFormSLS->hh[146];
c2.v[58] += (sum_160_1_139)*MainFormSLS->hh[103];
c2.v[58] += (sum_160_1_140)*MainFormSLS->hh[60];
c2.v[58] += (sum_160_1_141)*MainFormSLS->hh[17];
c2.v[58] += (sum_160_1_142)*MainFormSLS->hh[134];
c2.v[58] += (sum_160_1_143)*MainFormSLS->hh[91];
c2.v[58] += (sum_160_1_144)*MainFormSLS->hh[48];
c2.v[58] += (sum_160_1_145)*MainFormSLS->hh[5];
c2.v[58] += (sum_160_1_146)*MainFormSLS->hh[122];
c2.v[58] += (sum_160_1_147)*MainFormSLS->hh[79];
c2.v[58] += (sum_160_1_148)*MainFormSLS->hh[36];
c2.v[58] += (sum_160_1_149)*MainFormSLS->hh[153];
c2.v[58] += (sum_160_1_150)*MainFormSLS->hh[110];
c2.v[58] += (sum_160_1_151)*MainFormSLS->hh[67];
c2.v[58] += (sum_160_1_152)*MainFormSLS->hh[24];
c2.v[58] += (sum_160_1_153)*MainFormSLS->hh[141];
c2.v[58] += (sum_160_1_154)*MainFormSLS->hh[98];
c2.v[58] += (sum_160_1_155)*MainFormSLS->hh[55];
c2.v[58] += (sum_160_1_156)*MainFormSLS->hh[12];
c2.v[58] += (sum_160_1_157)*MainFormSLS->hh[129];
c2.v[58] += (sum_160_1_158)*MainFormSLS->hh[86];
c2.v[58] += (sum_160_1_159)*MainFormSLS->hh[43];

//frequency level id 119
c2.v[59] += (sum_160_1_000)*MainFormSLS->hh[0];
c2.v[59] += (sum_160_1_001)*MainFormSLS->hh[119];
c2.v[59] += (sum_160_1_002)*MainFormSLS->hh[78];
c2.v[59] += (sum_160_1_003)*MainFormSLS->hh[37];
c2.v[59] += (sum_160_1_004)*MainFormSLS->hh[156];
c2.v[59] += (sum_160_1_005)*MainFormSLS->hh[115];
c2.v[59] += (sum_160_1_006)*MainFormSLS->hh[74];
c2.v[59] += (sum_160_1_007)*MainFormSLS->hh[33];
c2.v[59] += (sum_160_1_008)*MainFormSLS->hh[152];
c2.v[59] += (sum_160_1_009)*MainFormSLS->hh[111];
c2.v[59] += (sum_160_1_010)*MainFormSLS->hh[70];
c2.v[59] += (sum_160_1_011)*MainFormSLS->hh[29];
c2.v[59] += (sum_160_1_012)*MainFormSLS->hh[148];
c2.v[59] += (sum_160_1_013)*MainFormSLS->hh[107];
c2.v[59] += (sum_160_1_014)*MainFormSLS->hh[66];
c2.v[59] += (sum_160_1_015)*MainFormSLS->hh[25];
c2.v[59] += (sum_160_1_016)*MainFormSLS->hh[144];
c2.v[59] += (sum_160_1_017)*MainFormSLS->hh[103];
c2.v[59] += (sum_160_1_018)*MainFormSLS->hh[62];
c2.v[59] += (sum_160_1_019)*MainFormSLS->hh[21];
c2.v[59] += (sum_160_1_020)*MainFormSLS->hh[140];
c2.v[59] += (sum_160_1_021)*MainFormSLS->hh[99];
c2.v[59] += (sum_160_1_022)*MainFormSLS->hh[58];
c2.v[59] += (sum_160_1_023)*MainFormSLS->hh[17];
c2.v[59] += (sum_160_1_024)*MainFormSLS->hh[136];
c2.v[59] += (sum_160_1_025)*MainFormSLS->hh[95];
c2.v[59] += (sum_160_1_026)*MainFormSLS->hh[54];
c2.v[59] += (sum_160_1_027)*MainFormSLS->hh[13];
c2.v[59] += (sum_160_1_028)*MainFormSLS->hh[132];
c2.v[59] += (sum_160_1_029)*MainFormSLS->hh[91];
c2.v[59] += (sum_160_1_030)*MainFormSLS->hh[50];
c2.v[59] += (sum_160_1_031)*MainFormSLS->hh[9];
c2.v[59] += (sum_160_1_032)*MainFormSLS->hh[128];
c2.v[59] += (sum_160_1_033)*MainFormSLS->hh[87];
c2.v[59] += (sum_160_1_034)*MainFormSLS->hh[46];
c2.v[59] += (sum_160_1_035)*MainFormSLS->hh[5];
c2.v[59] += (sum_160_1_036)*MainFormSLS->hh[124];
c2.v[59] += (sum_160_1_037)*MainFormSLS->hh[83];
c2.v[59] += (sum_160_1_038)*MainFormSLS->hh[42];
c2.v[59] += (sum_160_1_039)*MainFormSLS->hh[1];
c2.v[59] += (sum_160_1_040)*MainFormSLS->hh[120];
c2.v[59] += (sum_160_1_041)*MainFormSLS->hh[79];
c2.v[59] += (sum_160_1_042)*MainFormSLS->hh[38];
c2.v[59] += (sum_160_1_043)*MainFormSLS->hh[157];
c2.v[59] += (sum_160_1_044)*MainFormSLS->hh[116];
c2.v[59] += (sum_160_1_045)*MainFormSLS->hh[75];
c2.v[59] += (sum_160_1_046)*MainFormSLS->hh[34];
c2.v[59] += (sum_160_1_047)*MainFormSLS->hh[153];
c2.v[59] += (sum_160_1_048)*MainFormSLS->hh[112];
c2.v[59] += (sum_160_1_049)*MainFormSLS->hh[71];
c2.v[59] += (sum_160_1_050)*MainFormSLS->hh[30];
c2.v[59] += (sum_160_1_051)*MainFormSLS->hh[149];
c2.v[59] += (sum_160_1_052)*MainFormSLS->hh[108];
c2.v[59] += (sum_160_1_053)*MainFormSLS->hh[67];
c2.v[59] += (sum_160_1_054)*MainFormSLS->hh[26];
c2.v[59] += (sum_160_1_055)*MainFormSLS->hh[145];
c2.v[59] += (sum_160_1_056)*MainFormSLS->hh[104];
c2.v[59] += (sum_160_1_057)*MainFormSLS->hh[63];
c2.v[59] += (sum_160_1_058)*MainFormSLS->hh[22];
c2.v[59] += (sum_160_1_059)*MainFormSLS->hh[141];
c2.v[59] += (sum_160_1_060)*MainFormSLS->hh[100];
c2.v[59] += (sum_160_1_061)*MainFormSLS->hh[59];
c2.v[59] += (sum_160_1_062)*MainFormSLS->hh[18];
c2.v[59] += (sum_160_1_063)*MainFormSLS->hh[137];
c2.v[59] += (sum_160_1_064)*MainFormSLS->hh[96];
c2.v[59] += (sum_160_1_065)*MainFormSLS->hh[55];
c2.v[59] += (sum_160_1_066)*MainFormSLS->hh[14];
c2.v[59] += (sum_160_1_067)*MainFormSLS->hh[133];
c2.v[59] += (sum_160_1_068)*MainFormSLS->hh[92];
c2.v[59] += (sum_160_1_069)*MainFormSLS->hh[51];
c2.v[59] += (sum_160_1_070)*MainFormSLS->hh[10];
c2.v[59] += (sum_160_1_071)*MainFormSLS->hh[129];
c2.v[59] += (sum_160_1_072)*MainFormSLS->hh[88];
c2.v[59] += (sum_160_1_073)*MainFormSLS->hh[47];
c2.v[59] += (sum_160_1_074)*MainFormSLS->hh[6];
c2.v[59] += (sum_160_1_075)*MainFormSLS->hh[125];
c2.v[59] += (sum_160_1_076)*MainFormSLS->hh[84];
c2.v[59] += (sum_160_1_077)*MainFormSLS->hh[43];
c2.v[59] += (sum_160_1_078)*MainFormSLS->hh[2];
c2.v[59] += (sum_160_1_079)*MainFormSLS->hh[121];
c2.v[59] += (sum_160_1_080)*MainFormSLS->hh[80];
c2.v[59] += (sum_160_1_081)*MainFormSLS->hh[39];
c2.v[59] += (sum_160_1_082)*MainFormSLS->hh[158];
c2.v[59] += (sum_160_1_083)*MainFormSLS->hh[117];
c2.v[59] += (sum_160_1_084)*MainFormSLS->hh[76];
c2.v[59] += (sum_160_1_085)*MainFormSLS->hh[35];
c2.v[59] += (sum_160_1_086)*MainFormSLS->hh[154];
c2.v[59] += (sum_160_1_087)*MainFormSLS->hh[113];
c2.v[59] += (sum_160_1_088)*MainFormSLS->hh[72];
c2.v[59] += (sum_160_1_089)*MainFormSLS->hh[31];
c2.v[59] += (sum_160_1_090)*MainFormSLS->hh[150];
c2.v[59] += (sum_160_1_091)*MainFormSLS->hh[109];
c2.v[59] += (sum_160_1_092)*MainFormSLS->hh[68];
c2.v[59] += (sum_160_1_093)*MainFormSLS->hh[27];
c2.v[59] += (sum_160_1_094)*MainFormSLS->hh[146];
c2.v[59] += (sum_160_1_095)*MainFormSLS->hh[105];
c2.v[59] += (sum_160_1_096)*MainFormSLS->hh[64];
c2.v[59] += (sum_160_1_097)*MainFormSLS->hh[23];
c2.v[59] += (sum_160_1_098)*MainFormSLS->hh[142];
c2.v[59] += (sum_160_1_099)*MainFormSLS->hh[101];
c2.v[59] += (sum_160_1_100)*MainFormSLS->hh[60];
c2.v[59] += (sum_160_1_101)*MainFormSLS->hh[19];
c2.v[59] += (sum_160_1_102)*MainFormSLS->hh[138];
c2.v[59] += (sum_160_1_103)*MainFormSLS->hh[97];
c2.v[59] += (sum_160_1_104)*MainFormSLS->hh[56];
c2.v[59] += (sum_160_1_105)*MainFormSLS->hh[15];
c2.v[59] += (sum_160_1_106)*MainFormSLS->hh[134];
c2.v[59] += (sum_160_1_107)*MainFormSLS->hh[93];
c2.v[59] += (sum_160_1_108)*MainFormSLS->hh[52];
c2.v[59] += (sum_160_1_109)*MainFormSLS->hh[11];
c2.v[59] += (sum_160_1_110)*MainFormSLS->hh[130];
c2.v[59] += (sum_160_1_111)*MainFormSLS->hh[89];
c2.v[59] += (sum_160_1_112)*MainFormSLS->hh[48];
c2.v[59] += (sum_160_1_113)*MainFormSLS->hh[7];
c2.v[59] += (sum_160_1_114)*MainFormSLS->hh[126];
c2.v[59] += (sum_160_1_115)*MainFormSLS->hh[85];
c2.v[59] += (sum_160_1_116)*MainFormSLS->hh[44];
c2.v[59] += (sum_160_1_117)*MainFormSLS->hh[3];
c2.v[59] += (sum_160_1_118)*MainFormSLS->hh[122];
c2.v[59] += (sum_160_1_119)*MainFormSLS->hh[81];
c2.v[59] += (sum_160_1_120)*MainFormSLS->hh[40];
c2.v[59] += (sum_160_1_121)*MainFormSLS->hh[159];
c2.v[59] += (sum_160_1_122)*MainFormSLS->hh[118];
c2.v[59] += (sum_160_1_123)*MainFormSLS->hh[77];
c2.v[59] += (sum_160_1_124)*MainFormSLS->hh[36];
c2.v[59] += (sum_160_1_125)*MainFormSLS->hh[155];
c2.v[59] += (sum_160_1_126)*MainFormSLS->hh[114];
c2.v[59] += (sum_160_1_127)*MainFormSLS->hh[73];
c2.v[59] += (sum_160_1_128)*MainFormSLS->hh[32];
c2.v[59] += (sum_160_1_129)*MainFormSLS->hh[151];
c2.v[59] += (sum_160_1_130)*MainFormSLS->hh[110];
c2.v[59] += (sum_160_1_131)*MainFormSLS->hh[69];
c2.v[59] += (sum_160_1_132)*MainFormSLS->hh[28];
c2.v[59] += (sum_160_1_133)*MainFormSLS->hh[147];
c2.v[59] += (sum_160_1_134)*MainFormSLS->hh[106];
c2.v[59] += (sum_160_1_135)*MainFormSLS->hh[65];
c2.v[59] += (sum_160_1_136)*MainFormSLS->hh[24];
c2.v[59] += (sum_160_1_137)*MainFormSLS->hh[143];
c2.v[59] += (sum_160_1_138)*MainFormSLS->hh[102];
c2.v[59] += (sum_160_1_139)*MainFormSLS->hh[61];
c2.v[59] += (sum_160_1_140)*MainFormSLS->hh[20];
c2.v[59] += (sum_160_1_141)*MainFormSLS->hh[139];
c2.v[59] += (sum_160_1_142)*MainFormSLS->hh[98];
c2.v[59] += (sum_160_1_143)*MainFormSLS->hh[57];
c2.v[59] += (sum_160_1_144)*MainFormSLS->hh[16];
c2.v[59] += (sum_160_1_145)*MainFormSLS->hh[135];
c2.v[59] += (sum_160_1_146)*MainFormSLS->hh[94];
c2.v[59] += (sum_160_1_147)*MainFormSLS->hh[53];
c2.v[59] += (sum_160_1_148)*MainFormSLS->hh[12];
c2.v[59] += (sum_160_1_149)*MainFormSLS->hh[131];
c2.v[59] += (sum_160_1_150)*MainFormSLS->hh[90];
c2.v[59] += (sum_160_1_151)*MainFormSLS->hh[49];
c2.v[59] += (sum_160_1_152)*MainFormSLS->hh[8];
c2.v[59] += (sum_160_1_153)*MainFormSLS->hh[127];
c2.v[59] += (sum_160_1_154)*MainFormSLS->hh[86];
c2.v[59] += (sum_160_1_155)*MainFormSLS->hh[45];
c2.v[59] += (sum_160_1_156)*MainFormSLS->hh[4];
c2.v[59] += (sum_160_1_157)*MainFormSLS->hh[123];
c2.v[59] += (sum_160_1_158)*MainFormSLS->hh[82];
c2.v[59] += (sum_160_1_159)*MainFormSLS->hh[41];

//frequency level id 121
c2.v[60] += (sum_160_1_000)*MainFormSLS->hh[0];
c2.v[60] += (sum_160_1_001)*MainFormSLS->hh[121];
c2.v[60] += (sum_160_1_002)*MainFormSLS->hh[82];
c2.v[60] += (sum_160_1_003)*MainFormSLS->hh[43];
c2.v[60] += (sum_160_1_004)*MainFormSLS->hh[4];
c2.v[60] += (sum_160_1_005)*MainFormSLS->hh[125];
c2.v[60] += (sum_160_1_006)*MainFormSLS->hh[86];
c2.v[60] += (sum_160_1_007)*MainFormSLS->hh[47];
c2.v[60] += (sum_160_1_008)*MainFormSLS->hh[8];
c2.v[60] += (sum_160_1_009)*MainFormSLS->hh[129];
c2.v[60] += (sum_160_1_010)*MainFormSLS->hh[90];
c2.v[60] += (sum_160_1_011)*MainFormSLS->hh[51];
c2.v[60] += (sum_160_1_012)*MainFormSLS->hh[12];
c2.v[60] += (sum_160_1_013)*MainFormSLS->hh[133];
c2.v[60] += (sum_160_1_014)*MainFormSLS->hh[94];
c2.v[60] += (sum_160_1_015)*MainFormSLS->hh[55];
c2.v[60] += (sum_160_1_016)*MainFormSLS->hh[16];
c2.v[60] += (sum_160_1_017)*MainFormSLS->hh[137];
c2.v[60] += (sum_160_1_018)*MainFormSLS->hh[98];
c2.v[60] += (sum_160_1_019)*MainFormSLS->hh[59];
c2.v[60] += (sum_160_1_020)*MainFormSLS->hh[20];
c2.v[60] += (sum_160_1_021)*MainFormSLS->hh[141];
c2.v[60] += (sum_160_1_022)*MainFormSLS->hh[102];
c2.v[60] += (sum_160_1_023)*MainFormSLS->hh[63];
c2.v[60] += (sum_160_1_024)*MainFormSLS->hh[24];
c2.v[60] += (sum_160_1_025)*MainFormSLS->hh[145];
c2.v[60] += (sum_160_1_026)*MainFormSLS->hh[106];
c2.v[60] += (sum_160_1_027)*MainFormSLS->hh[67];
c2.v[60] += (sum_160_1_028)*MainFormSLS->hh[28];
c2.v[60] += (sum_160_1_029)*MainFormSLS->hh[149];
c2.v[60] += (sum_160_1_030)*MainFormSLS->hh[110];
c2.v[60] += (sum_160_1_031)*MainFormSLS->hh[71];
c2.v[60] += (sum_160_1_032)*MainFormSLS->hh[32];
c2.v[60] += (sum_160_1_033)*MainFormSLS->hh[153];
c2.v[60] += (sum_160_1_034)*MainFormSLS->hh[114];
c2.v[60] += (sum_160_1_035)*MainFormSLS->hh[75];
c2.v[60] += (sum_160_1_036)*MainFormSLS->hh[36];
c2.v[60] += (sum_160_1_037)*MainFormSLS->hh[157];
c2.v[60] += (sum_160_1_038)*MainFormSLS->hh[118];
c2.v[60] += (sum_160_1_039)*MainFormSLS->hh[79];
c2.v[60] += (sum_160_1_040)*MainFormSLS->hh[40];
c2.v[60] += (sum_160_1_041)*MainFormSLS->hh[1];
c2.v[60] += (sum_160_1_042)*MainFormSLS->hh[122];
c2.v[60] += (sum_160_1_043)*MainFormSLS->hh[83];
c2.v[60] += (sum_160_1_044)*MainFormSLS->hh[44];
c2.v[60] += (sum_160_1_045)*MainFormSLS->hh[5];
c2.v[60] += (sum_160_1_046)*MainFormSLS->hh[126];
c2.v[60] += (sum_160_1_047)*MainFormSLS->hh[87];
c2.v[60] += (sum_160_1_048)*MainFormSLS->hh[48];
c2.v[60] += (sum_160_1_049)*MainFormSLS->hh[9];
c2.v[60] += (sum_160_1_050)*MainFormSLS->hh[130];
c2.v[60] += (sum_160_1_051)*MainFormSLS->hh[91];
c2.v[60] += (sum_160_1_052)*MainFormSLS->hh[52];
c2.v[60] += (sum_160_1_053)*MainFormSLS->hh[13];
c2.v[60] += (sum_160_1_054)*MainFormSLS->hh[134];
c2.v[60] += (sum_160_1_055)*MainFormSLS->hh[95];
c2.v[60] += (sum_160_1_056)*MainFormSLS->hh[56];
c2.v[60] += (sum_160_1_057)*MainFormSLS->hh[17];
c2.v[60] += (sum_160_1_058)*MainFormSLS->hh[138];
c2.v[60] += (sum_160_1_059)*MainFormSLS->hh[99];
c2.v[60] += (sum_160_1_060)*MainFormSLS->hh[60];
c2.v[60] += (sum_160_1_061)*MainFormSLS->hh[21];
c2.v[60] += (sum_160_1_062)*MainFormSLS->hh[142];
c2.v[60] += (sum_160_1_063)*MainFormSLS->hh[103];
c2.v[60] += (sum_160_1_064)*MainFormSLS->hh[64];
c2.v[60] += (sum_160_1_065)*MainFormSLS->hh[25];
c2.v[60] += (sum_160_1_066)*MainFormSLS->hh[146];
c2.v[60] += (sum_160_1_067)*MainFormSLS->hh[107];
c2.v[60] += (sum_160_1_068)*MainFormSLS->hh[68];
c2.v[60] += (sum_160_1_069)*MainFormSLS->hh[29];
c2.v[60] += (sum_160_1_070)*MainFormSLS->hh[150];
c2.v[60] += (sum_160_1_071)*MainFormSLS->hh[111];
c2.v[60] += (sum_160_1_072)*MainFormSLS->hh[72];
c2.v[60] += (sum_160_1_073)*MainFormSLS->hh[33];
c2.v[60] += (sum_160_1_074)*MainFormSLS->hh[154];
c2.v[60] += (sum_160_1_075)*MainFormSLS->hh[115];
c2.v[60] += (sum_160_1_076)*MainFormSLS->hh[76];
c2.v[60] += (sum_160_1_077)*MainFormSLS->hh[37];
c2.v[60] += (sum_160_1_078)*MainFormSLS->hh[158];
c2.v[60] += (sum_160_1_079)*MainFormSLS->hh[119];
c2.v[60] += (sum_160_1_080)*MainFormSLS->hh[80];
c2.v[60] += (sum_160_1_081)*MainFormSLS->hh[41];
c2.v[60] += (sum_160_1_082)*MainFormSLS->hh[2];
c2.v[60] += (sum_160_1_083)*MainFormSLS->hh[123];
c2.v[60] += (sum_160_1_084)*MainFormSLS->hh[84];
c2.v[60] += (sum_160_1_085)*MainFormSLS->hh[45];
c2.v[60] += (sum_160_1_086)*MainFormSLS->hh[6];
c2.v[60] += (sum_160_1_087)*MainFormSLS->hh[127];
c2.v[60] += (sum_160_1_088)*MainFormSLS->hh[88];
c2.v[60] += (sum_160_1_089)*MainFormSLS->hh[49];
c2.v[60] += (sum_160_1_090)*MainFormSLS->hh[10];
c2.v[60] += (sum_160_1_091)*MainFormSLS->hh[131];
c2.v[60] += (sum_160_1_092)*MainFormSLS->hh[92];
c2.v[60] += (sum_160_1_093)*MainFormSLS->hh[53];
c2.v[60] += (sum_160_1_094)*MainFormSLS->hh[14];
c2.v[60] += (sum_160_1_095)*MainFormSLS->hh[135];
c2.v[60] += (sum_160_1_096)*MainFormSLS->hh[96];
c2.v[60] += (sum_160_1_097)*MainFormSLS->hh[57];
c2.v[60] += (sum_160_1_098)*MainFormSLS->hh[18];
c2.v[60] += (sum_160_1_099)*MainFormSLS->hh[139];
c2.v[60] += (sum_160_1_100)*MainFormSLS->hh[100];
c2.v[60] += (sum_160_1_101)*MainFormSLS->hh[61];
c2.v[60] += (sum_160_1_102)*MainFormSLS->hh[22];
c2.v[60] += (sum_160_1_103)*MainFormSLS->hh[143];
c2.v[60] += (sum_160_1_104)*MainFormSLS->hh[104];
c2.v[60] += (sum_160_1_105)*MainFormSLS->hh[65];
c2.v[60] += (sum_160_1_106)*MainFormSLS->hh[26];
c2.v[60] += (sum_160_1_107)*MainFormSLS->hh[147];
c2.v[60] += (sum_160_1_108)*MainFormSLS->hh[108];
c2.v[60] += (sum_160_1_109)*MainFormSLS->hh[69];
c2.v[60] += (sum_160_1_110)*MainFormSLS->hh[30];
c2.v[60] += (sum_160_1_111)*MainFormSLS->hh[151];
c2.v[60] += (sum_160_1_112)*MainFormSLS->hh[112];
c2.v[60] += (sum_160_1_113)*MainFormSLS->hh[73];
c2.v[60] += (sum_160_1_114)*MainFormSLS->hh[34];
c2.v[60] += (sum_160_1_115)*MainFormSLS->hh[155];
c2.v[60] += (sum_160_1_116)*MainFormSLS->hh[116];
c2.v[60] += (sum_160_1_117)*MainFormSLS->hh[77];
c2.v[60] += (sum_160_1_118)*MainFormSLS->hh[38];
c2.v[60] += (sum_160_1_119)*MainFormSLS->hh[159];
c2.v[60] += (sum_160_1_120)*MainFormSLS->hh[120];
c2.v[60] += (sum_160_1_121)*MainFormSLS->hh[81];
c2.v[60] += (sum_160_1_122)*MainFormSLS->hh[42];
c2.v[60] += (sum_160_1_123)*MainFormSLS->hh[3];
c2.v[60] += (sum_160_1_124)*MainFormSLS->hh[124];
c2.v[60] += (sum_160_1_125)*MainFormSLS->hh[85];
c2.v[60] += (sum_160_1_126)*MainFormSLS->hh[46];
c2.v[60] += (sum_160_1_127)*MainFormSLS->hh[7];
c2.v[60] += (sum_160_1_128)*MainFormSLS->hh[128];
c2.v[60] += (sum_160_1_129)*MainFormSLS->hh[89];
c2.v[60] += (sum_160_1_130)*MainFormSLS->hh[50];
c2.v[60] += (sum_160_1_131)*MainFormSLS->hh[11];
c2.v[60] += (sum_160_1_132)*MainFormSLS->hh[132];
c2.v[60] += (sum_160_1_133)*MainFormSLS->hh[93];
c2.v[60] += (sum_160_1_134)*MainFormSLS->hh[54];
c2.v[60] += (sum_160_1_135)*MainFormSLS->hh[15];
c2.v[60] += (sum_160_1_136)*MainFormSLS->hh[136];
c2.v[60] += (sum_160_1_137)*MainFormSLS->hh[97];
c2.v[60] += (sum_160_1_138)*MainFormSLS->hh[58];
c2.v[60] += (sum_160_1_139)*MainFormSLS->hh[19];
c2.v[60] += (sum_160_1_140)*MainFormSLS->hh[140];
c2.v[60] += (sum_160_1_141)*MainFormSLS->hh[101];
c2.v[60] += (sum_160_1_142)*MainFormSLS->hh[62];
c2.v[60] += (sum_160_1_143)*MainFormSLS->hh[23];
c2.v[60] += (sum_160_1_144)*MainFormSLS->hh[144];
c2.v[60] += (sum_160_1_145)*MainFormSLS->hh[105];
c2.v[60] += (sum_160_1_146)*MainFormSLS->hh[66];
c2.v[60] += (sum_160_1_147)*MainFormSLS->hh[27];
c2.v[60] += (sum_160_1_148)*MainFormSLS->hh[148];
c2.v[60] += (sum_160_1_149)*MainFormSLS->hh[109];
c2.v[60] += (sum_160_1_150)*MainFormSLS->hh[70];
c2.v[60] += (sum_160_1_151)*MainFormSLS->hh[31];
c2.v[60] += (sum_160_1_152)*MainFormSLS->hh[152];
c2.v[60] += (sum_160_1_153)*MainFormSLS->hh[113];
c2.v[60] += (sum_160_1_154)*MainFormSLS->hh[74];
c2.v[60] += (sum_160_1_155)*MainFormSLS->hh[35];
c2.v[60] += (sum_160_1_156)*MainFormSLS->hh[156];
c2.v[60] += (sum_160_1_157)*MainFormSLS->hh[117];
c2.v[60] += (sum_160_1_158)*MainFormSLS->hh[78];
c2.v[60] += (sum_160_1_159)*MainFormSLS->hh[39];

//frequency level id 123
c2.v[61] += (sum_160_1_000)*MainFormSLS->hh[0];
c2.v[61] += (sum_160_1_001)*MainFormSLS->hh[123];
c2.v[61] += (sum_160_1_002)*MainFormSLS->hh[86];
c2.v[61] += (sum_160_1_003)*MainFormSLS->hh[49];
c2.v[61] += (sum_160_1_004)*MainFormSLS->hh[12];
c2.v[61] += (sum_160_1_005)*MainFormSLS->hh[135];
c2.v[61] += (sum_160_1_006)*MainFormSLS->hh[98];
c2.v[61] += (sum_160_1_007)*MainFormSLS->hh[61];
c2.v[61] += (sum_160_1_008)*MainFormSLS->hh[24];
c2.v[61] += (sum_160_1_009)*MainFormSLS->hh[147];
c2.v[61] += (sum_160_1_010)*MainFormSLS->hh[110];
c2.v[61] += (sum_160_1_011)*MainFormSLS->hh[73];
c2.v[61] += (sum_160_1_012)*MainFormSLS->hh[36];
c2.v[61] += (sum_160_1_013)*MainFormSLS->hh[159];
c2.v[61] += (sum_160_1_014)*MainFormSLS->hh[122];
c2.v[61] += (sum_160_1_015)*MainFormSLS->hh[85];
c2.v[61] += (sum_160_1_016)*MainFormSLS->hh[48];
c2.v[61] += (sum_160_1_017)*MainFormSLS->hh[11];
c2.v[61] += (sum_160_1_018)*MainFormSLS->hh[134];
c2.v[61] += (sum_160_1_019)*MainFormSLS->hh[97];
c2.v[61] += (sum_160_1_020)*MainFormSLS->hh[60];
c2.v[61] += (sum_160_1_021)*MainFormSLS->hh[23];
c2.v[61] += (sum_160_1_022)*MainFormSLS->hh[146];
c2.v[61] += (sum_160_1_023)*MainFormSLS->hh[109];
c2.v[61] += (sum_160_1_024)*MainFormSLS->hh[72];
c2.v[61] += (sum_160_1_025)*MainFormSLS->hh[35];
c2.v[61] += (sum_160_1_026)*MainFormSLS->hh[158];
c2.v[61] += (sum_160_1_027)*MainFormSLS->hh[121];
c2.v[61] += (sum_160_1_028)*MainFormSLS->hh[84];
c2.v[61] += (sum_160_1_029)*MainFormSLS->hh[47];
c2.v[61] += (sum_160_1_030)*MainFormSLS->hh[10];
c2.v[61] += (sum_160_1_031)*MainFormSLS->hh[133];
c2.v[61] += (sum_160_1_032)*MainFormSLS->hh[96];
c2.v[61] += (sum_160_1_033)*MainFormSLS->hh[59];
c2.v[61] += (sum_160_1_034)*MainFormSLS->hh[22];
c2.v[61] += (sum_160_1_035)*MainFormSLS->hh[145];
c2.v[61] += (sum_160_1_036)*MainFormSLS->hh[108];
c2.v[61] += (sum_160_1_037)*MainFormSLS->hh[71];
c2.v[61] += (sum_160_1_038)*MainFormSLS->hh[34];
c2.v[61] += (sum_160_1_039)*MainFormSLS->hh[157];
c2.v[61] += (sum_160_1_040)*MainFormSLS->hh[120];
c2.v[61] += (sum_160_1_041)*MainFormSLS->hh[83];
c2.v[61] += (sum_160_1_042)*MainFormSLS->hh[46];
c2.v[61] += (sum_160_1_043)*MainFormSLS->hh[9];
c2.v[61] += (sum_160_1_044)*MainFormSLS->hh[132];
c2.v[61] += (sum_160_1_045)*MainFormSLS->hh[95];
c2.v[61] += (sum_160_1_046)*MainFormSLS->hh[58];
c2.v[61] += (sum_160_1_047)*MainFormSLS->hh[21];
c2.v[61] += (sum_160_1_048)*MainFormSLS->hh[144];
c2.v[61] += (sum_160_1_049)*MainFormSLS->hh[107];
c2.v[61] += (sum_160_1_050)*MainFormSLS->hh[70];
c2.v[61] += (sum_160_1_051)*MainFormSLS->hh[33];
c2.v[61] += (sum_160_1_052)*MainFormSLS->hh[156];
c2.v[61] += (sum_160_1_053)*MainFormSLS->hh[119];
c2.v[61] += (sum_160_1_054)*MainFormSLS->hh[82];
c2.v[61] += (sum_160_1_055)*MainFormSLS->hh[45];
c2.v[61] += (sum_160_1_056)*MainFormSLS->hh[8];
c2.v[61] += (sum_160_1_057)*MainFormSLS->hh[131];
c2.v[61] += (sum_160_1_058)*MainFormSLS->hh[94];
c2.v[61] += (sum_160_1_059)*MainFormSLS->hh[57];
c2.v[61] += (sum_160_1_060)*MainFormSLS->hh[20];
c2.v[61] += (sum_160_1_061)*MainFormSLS->hh[143];
c2.v[61] += (sum_160_1_062)*MainFormSLS->hh[106];
c2.v[61] += (sum_160_1_063)*MainFormSLS->hh[69];
c2.v[61] += (sum_160_1_064)*MainFormSLS->hh[32];
c2.v[61] += (sum_160_1_065)*MainFormSLS->hh[155];
c2.v[61] += (sum_160_1_066)*MainFormSLS->hh[118];
c2.v[61] += (sum_160_1_067)*MainFormSLS->hh[81];
c2.v[61] += (sum_160_1_068)*MainFormSLS->hh[44];
c2.v[61] += (sum_160_1_069)*MainFormSLS->hh[7];
c2.v[61] += (sum_160_1_070)*MainFormSLS->hh[130];
c2.v[61] += (sum_160_1_071)*MainFormSLS->hh[93];
c2.v[61] += (sum_160_1_072)*MainFormSLS->hh[56];
c2.v[61] += (sum_160_1_073)*MainFormSLS->hh[19];
c2.v[61] += (sum_160_1_074)*MainFormSLS->hh[142];
c2.v[61] += (sum_160_1_075)*MainFormSLS->hh[105];
c2.v[61] += (sum_160_1_076)*MainFormSLS->hh[68];
c2.v[61] += (sum_160_1_077)*MainFormSLS->hh[31];
c2.v[61] += (sum_160_1_078)*MainFormSLS->hh[154];
c2.v[61] += (sum_160_1_079)*MainFormSLS->hh[117];
c2.v[61] += (sum_160_1_080)*MainFormSLS->hh[80];
c2.v[61] += (sum_160_1_081)*MainFormSLS->hh[43];
c2.v[61] += (sum_160_1_082)*MainFormSLS->hh[6];
c2.v[61] += (sum_160_1_083)*MainFormSLS->hh[129];
c2.v[61] += (sum_160_1_084)*MainFormSLS->hh[92];
c2.v[61] += (sum_160_1_085)*MainFormSLS->hh[55];
c2.v[61] += (sum_160_1_086)*MainFormSLS->hh[18];
c2.v[61] += (sum_160_1_087)*MainFormSLS->hh[141];
c2.v[61] += (sum_160_1_088)*MainFormSLS->hh[104];
c2.v[61] += (sum_160_1_089)*MainFormSLS->hh[67];
c2.v[61] += (sum_160_1_090)*MainFormSLS->hh[30];
c2.v[61] += (sum_160_1_091)*MainFormSLS->hh[153];
c2.v[61] += (sum_160_1_092)*MainFormSLS->hh[116];
c2.v[61] += (sum_160_1_093)*MainFormSLS->hh[79];
c2.v[61] += (sum_160_1_094)*MainFormSLS->hh[42];
c2.v[61] += (sum_160_1_095)*MainFormSLS->hh[5];
c2.v[61] += (sum_160_1_096)*MainFormSLS->hh[128];
c2.v[61] += (sum_160_1_097)*MainFormSLS->hh[91];
c2.v[61] += (sum_160_1_098)*MainFormSLS->hh[54];
c2.v[61] += (sum_160_1_099)*MainFormSLS->hh[17];
c2.v[61] += (sum_160_1_100)*MainFormSLS->hh[140];
c2.v[61] += (sum_160_1_101)*MainFormSLS->hh[103];
c2.v[61] += (sum_160_1_102)*MainFormSLS->hh[66];
c2.v[61] += (sum_160_1_103)*MainFormSLS->hh[29];
c2.v[61] += (sum_160_1_104)*MainFormSLS->hh[152];
c2.v[61] += (sum_160_1_105)*MainFormSLS->hh[115];
c2.v[61] += (sum_160_1_106)*MainFormSLS->hh[78];
c2.v[61] += (sum_160_1_107)*MainFormSLS->hh[41];
c2.v[61] += (sum_160_1_108)*MainFormSLS->hh[4];
c2.v[61] += (sum_160_1_109)*MainFormSLS->hh[127];
c2.v[61] += (sum_160_1_110)*MainFormSLS->hh[90];
c2.v[61] += (sum_160_1_111)*MainFormSLS->hh[53];
c2.v[61] += (sum_160_1_112)*MainFormSLS->hh[16];
c2.v[61] += (sum_160_1_113)*MainFormSLS->hh[139];
c2.v[61] += (sum_160_1_114)*MainFormSLS->hh[102];
c2.v[61] += (sum_160_1_115)*MainFormSLS->hh[65];
c2.v[61] += (sum_160_1_116)*MainFormSLS->hh[28];
c2.v[61] += (sum_160_1_117)*MainFormSLS->hh[151];
c2.v[61] += (sum_160_1_118)*MainFormSLS->hh[114];
c2.v[61] += (sum_160_1_119)*MainFormSLS->hh[77];
c2.v[61] += (sum_160_1_120)*MainFormSLS->hh[40];
c2.v[61] += (sum_160_1_121)*MainFormSLS->hh[3];
c2.v[61] += (sum_160_1_122)*MainFormSLS->hh[126];
c2.v[61] += (sum_160_1_123)*MainFormSLS->hh[89];
c2.v[61] += (sum_160_1_124)*MainFormSLS->hh[52];
c2.v[61] += (sum_160_1_125)*MainFormSLS->hh[15];
c2.v[61] += (sum_160_1_126)*MainFormSLS->hh[138];
c2.v[61] += (sum_160_1_127)*MainFormSLS->hh[101];
c2.v[61] += (sum_160_1_128)*MainFormSLS->hh[64];
c2.v[61] += (sum_160_1_129)*MainFormSLS->hh[27];
c2.v[61] += (sum_160_1_130)*MainFormSLS->hh[150];
c2.v[61] += (sum_160_1_131)*MainFormSLS->hh[113];
c2.v[61] += (sum_160_1_132)*MainFormSLS->hh[76];
c2.v[61] += (sum_160_1_133)*MainFormSLS->hh[39];
c2.v[61] += (sum_160_1_134)*MainFormSLS->hh[2];
c2.v[61] += (sum_160_1_135)*MainFormSLS->hh[125];
c2.v[61] += (sum_160_1_136)*MainFormSLS->hh[88];
c2.v[61] += (sum_160_1_137)*MainFormSLS->hh[51];
c2.v[61] += (sum_160_1_138)*MainFormSLS->hh[14];
c2.v[61] += (sum_160_1_139)*MainFormSLS->hh[137];
c2.v[61] += (sum_160_1_140)*MainFormSLS->hh[100];
c2.v[61] += (sum_160_1_141)*MainFormSLS->hh[63];
c2.v[61] += (sum_160_1_142)*MainFormSLS->hh[26];
c2.v[61] += (sum_160_1_143)*MainFormSLS->hh[149];
c2.v[61] += (sum_160_1_144)*MainFormSLS->hh[112];
c2.v[61] += (sum_160_1_145)*MainFormSLS->hh[75];
c2.v[61] += (sum_160_1_146)*MainFormSLS->hh[38];
c2.v[61] += (sum_160_1_147)*MainFormSLS->hh[1];
c2.v[61] += (sum_160_1_148)*MainFormSLS->hh[124];
c2.v[61] += (sum_160_1_149)*MainFormSLS->hh[87];
c2.v[61] += (sum_160_1_150)*MainFormSLS->hh[50];
c2.v[61] += (sum_160_1_151)*MainFormSLS->hh[13];
c2.v[61] += (sum_160_1_152)*MainFormSLS->hh[136];
c2.v[61] += (sum_160_1_153)*MainFormSLS->hh[99];
c2.v[61] += (sum_160_1_154)*MainFormSLS->hh[62];
c2.v[61] += (sum_160_1_155)*MainFormSLS->hh[25];
c2.v[61] += (sum_160_1_156)*MainFormSLS->hh[148];
c2.v[61] += (sum_160_1_157)*MainFormSLS->hh[111];
c2.v[61] += (sum_160_1_158)*MainFormSLS->hh[74];
c2.v[61] += (sum_160_1_159)*MainFormSLS->hh[37];

//frequency level id 125
c2.v[62] += (sum_32_5_000)*MainFormSLS->hh[0];
c2.v[62] += (sum_32_5_001)*MainFormSLS->hh[125];
c2.v[62] += (sum_32_5_002)*MainFormSLS->hh[90];
c2.v[62] += (sum_32_5_003)*MainFormSLS->hh[55];
c2.v[62] += (sum_32_5_004)*MainFormSLS->hh[20];
c2.v[62] += (sum_32_5_005)*MainFormSLS->hh[145];
c2.v[62] += (sum_32_5_006)*MainFormSLS->hh[110];
c2.v[62] += (sum_32_5_007)*MainFormSLS->hh[75];
c2.v[62] += (sum_32_5_008)*MainFormSLS->hh[40];
c2.v[62] += (sum_32_5_009)*MainFormSLS->hh[5];
c2.v[62] += (sum_32_5_010)*MainFormSLS->hh[130];
c2.v[62] += (sum_32_5_011)*MainFormSLS->hh[95];
c2.v[62] += (sum_32_5_012)*MainFormSLS->hh[60];
c2.v[62] += (sum_32_5_013)*MainFormSLS->hh[25];
c2.v[62] += (sum_32_5_014)*MainFormSLS->hh[150];
c2.v[62] += (sum_32_5_015)*MainFormSLS->hh[115];
c2.v[62] += (sum_32_5_016)*MainFormSLS->hh[80];
c2.v[62] += (sum_32_5_017)*MainFormSLS->hh[45];
c2.v[62] += (sum_32_5_018)*MainFormSLS->hh[10];
c2.v[62] += (sum_32_5_019)*MainFormSLS->hh[135];
c2.v[62] += (sum_32_5_020)*MainFormSLS->hh[100];
c2.v[62] += (sum_32_5_021)*MainFormSLS->hh[65];
c2.v[62] += (sum_32_5_022)*MainFormSLS->hh[30];
c2.v[62] += (sum_32_5_023)*MainFormSLS->hh[155];
c2.v[62] += (sum_32_5_024)*MainFormSLS->hh[120];
c2.v[62] += (sum_32_5_025)*MainFormSLS->hh[85];
c2.v[62] += (sum_32_5_026)*MainFormSLS->hh[50];
c2.v[62] += (sum_32_5_027)*MainFormSLS->hh[15];
c2.v[62] += (sum_32_5_028)*MainFormSLS->hh[140];
c2.v[62] += (sum_32_5_029)*MainFormSLS->hh[105];
c2.v[62] += (sum_32_5_030)*MainFormSLS->hh[70];
c2.v[62] += (sum_32_5_031)*MainFormSLS->hh[35];

//frequency level id 127
c2.v[63] += (sum_160_1_000)*MainFormSLS->hh[0];
c2.v[63] += (sum_160_1_001)*MainFormSLS->hh[127];
c2.v[63] += (sum_160_1_002)*MainFormSLS->hh[94];
c2.v[63] += (sum_160_1_003)*MainFormSLS->hh[61];
c2.v[63] += (sum_160_1_004)*MainFormSLS->hh[28];
c2.v[63] += (sum_160_1_005)*MainFormSLS->hh[155];
c2.v[63] += (sum_160_1_006)*MainFormSLS->hh[122];
c2.v[63] += (sum_160_1_007)*MainFormSLS->hh[89];
c2.v[63] += (sum_160_1_008)*MainFormSLS->hh[56];
c2.v[63] += (sum_160_1_009)*MainFormSLS->hh[23];
c2.v[63] += (sum_160_1_010)*MainFormSLS->hh[150];
c2.v[63] += (sum_160_1_011)*MainFormSLS->hh[117];
c2.v[63] += (sum_160_1_012)*MainFormSLS->hh[84];
c2.v[63] += (sum_160_1_013)*MainFormSLS->hh[51];
c2.v[63] += (sum_160_1_014)*MainFormSLS->hh[18];
c2.v[63] += (sum_160_1_015)*MainFormSLS->hh[145];
c2.v[63] += (sum_160_1_016)*MainFormSLS->hh[112];
c2.v[63] += (sum_160_1_017)*MainFormSLS->hh[79];
c2.v[63] += (sum_160_1_018)*MainFormSLS->hh[46];
c2.v[63] += (sum_160_1_019)*MainFormSLS->hh[13];
c2.v[63] += (sum_160_1_020)*MainFormSLS->hh[140];
c2.v[63] += (sum_160_1_021)*MainFormSLS->hh[107];
c2.v[63] += (sum_160_1_022)*MainFormSLS->hh[74];
c2.v[63] += (sum_160_1_023)*MainFormSLS->hh[41];
c2.v[63] += (sum_160_1_024)*MainFormSLS->hh[8];
c2.v[63] += (sum_160_1_025)*MainFormSLS->hh[135];
c2.v[63] += (sum_160_1_026)*MainFormSLS->hh[102];
c2.v[63] += (sum_160_1_027)*MainFormSLS->hh[69];
c2.v[63] += (sum_160_1_028)*MainFormSLS->hh[36];
c2.v[63] += (sum_160_1_029)*MainFormSLS->hh[3];
c2.v[63] += (sum_160_1_030)*MainFormSLS->hh[130];
c2.v[63] += (sum_160_1_031)*MainFormSLS->hh[97];
c2.v[63] += (sum_160_1_032)*MainFormSLS->hh[64];
c2.v[63] += (sum_160_1_033)*MainFormSLS->hh[31];
c2.v[63] += (sum_160_1_034)*MainFormSLS->hh[158];
c2.v[63] += (sum_160_1_035)*MainFormSLS->hh[125];
c2.v[63] += (sum_160_1_036)*MainFormSLS->hh[92];
c2.v[63] += (sum_160_1_037)*MainFormSLS->hh[59];
c2.v[63] += (sum_160_1_038)*MainFormSLS->hh[26];
c2.v[63] += (sum_160_1_039)*MainFormSLS->hh[153];
c2.v[63] += (sum_160_1_040)*MainFormSLS->hh[120];
c2.v[63] += (sum_160_1_041)*MainFormSLS->hh[87];
c2.v[63] += (sum_160_1_042)*MainFormSLS->hh[54];
c2.v[63] += (sum_160_1_043)*MainFormSLS->hh[21];
c2.v[63] += (sum_160_1_044)*MainFormSLS->hh[148];
c2.v[63] += (sum_160_1_045)*MainFormSLS->hh[115];
c2.v[63] += (sum_160_1_046)*MainFormSLS->hh[82];
c2.v[63] += (sum_160_1_047)*MainFormSLS->hh[49];
c2.v[63] += (sum_160_1_048)*MainFormSLS->hh[16];
c2.v[63] += (sum_160_1_049)*MainFormSLS->hh[143];
c2.v[63] += (sum_160_1_050)*MainFormSLS->hh[110];
c2.v[63] += (sum_160_1_051)*MainFormSLS->hh[77];
c2.v[63] += (sum_160_1_052)*MainFormSLS->hh[44];
c2.v[63] += (sum_160_1_053)*MainFormSLS->hh[11];
c2.v[63] += (sum_160_1_054)*MainFormSLS->hh[138];
c2.v[63] += (sum_160_1_055)*MainFormSLS->hh[105];
c2.v[63] += (sum_160_1_056)*MainFormSLS->hh[72];
c2.v[63] += (sum_160_1_057)*MainFormSLS->hh[39];
c2.v[63] += (sum_160_1_058)*MainFormSLS->hh[6];
c2.v[63] += (sum_160_1_059)*MainFormSLS->hh[133];
c2.v[63] += (sum_160_1_060)*MainFormSLS->hh[100];
c2.v[63] += (sum_160_1_061)*MainFormSLS->hh[67];
c2.v[63] += (sum_160_1_062)*MainFormSLS->hh[34];
c2.v[63] += (sum_160_1_063)*MainFormSLS->hh[1];
c2.v[63] += (sum_160_1_064)*MainFormSLS->hh[128];
c2.v[63] += (sum_160_1_065)*MainFormSLS->hh[95];
c2.v[63] += (sum_160_1_066)*MainFormSLS->hh[62];
c2.v[63] += (sum_160_1_067)*MainFormSLS->hh[29];
c2.v[63] += (sum_160_1_068)*MainFormSLS->hh[156];
c2.v[63] += (sum_160_1_069)*MainFormSLS->hh[123];
c2.v[63] += (sum_160_1_070)*MainFormSLS->hh[90];
c2.v[63] += (sum_160_1_071)*MainFormSLS->hh[57];
c2.v[63] += (sum_160_1_072)*MainFormSLS->hh[24];
c2.v[63] += (sum_160_1_073)*MainFormSLS->hh[151];
c2.v[63] += (sum_160_1_074)*MainFormSLS->hh[118];
c2.v[63] += (sum_160_1_075)*MainFormSLS->hh[85];
c2.v[63] += (sum_160_1_076)*MainFormSLS->hh[52];
c2.v[63] += (sum_160_1_077)*MainFormSLS->hh[19];
c2.v[63] += (sum_160_1_078)*MainFormSLS->hh[146];
c2.v[63] += (sum_160_1_079)*MainFormSLS->hh[113];
c2.v[63] += (sum_160_1_080)*MainFormSLS->hh[80];
c2.v[63] += (sum_160_1_081)*MainFormSLS->hh[47];
c2.v[63] += (sum_160_1_082)*MainFormSLS->hh[14];
c2.v[63] += (sum_160_1_083)*MainFormSLS->hh[141];
c2.v[63] += (sum_160_1_084)*MainFormSLS->hh[108];
c2.v[63] += (sum_160_1_085)*MainFormSLS->hh[75];
c2.v[63] += (sum_160_1_086)*MainFormSLS->hh[42];
c2.v[63] += (sum_160_1_087)*MainFormSLS->hh[9];
c2.v[63] += (sum_160_1_088)*MainFormSLS->hh[136];
c2.v[63] += (sum_160_1_089)*MainFormSLS->hh[103];
c2.v[63] += (sum_160_1_090)*MainFormSLS->hh[70];
c2.v[63] += (sum_160_1_091)*MainFormSLS->hh[37];
c2.v[63] += (sum_160_1_092)*MainFormSLS->hh[4];
c2.v[63] += (sum_160_1_093)*MainFormSLS->hh[131];
c2.v[63] += (sum_160_1_094)*MainFormSLS->hh[98];
c2.v[63] += (sum_160_1_095)*MainFormSLS->hh[65];
c2.v[63] += (sum_160_1_096)*MainFormSLS->hh[32];
c2.v[63] += (sum_160_1_097)*MainFormSLS->hh[159];
c2.v[63] += (sum_160_1_098)*MainFormSLS->hh[126];
c2.v[63] += (sum_160_1_099)*MainFormSLS->hh[93];
c2.v[63] += (sum_160_1_100)*MainFormSLS->hh[60];
c2.v[63] += (sum_160_1_101)*MainFormSLS->hh[27];
c2.v[63] += (sum_160_1_102)*MainFormSLS->hh[154];
c2.v[63] += (sum_160_1_103)*MainFormSLS->hh[121];
c2.v[63] += (sum_160_1_104)*MainFormSLS->hh[88];
c2.v[63] += (sum_160_1_105)*MainFormSLS->hh[55];
c2.v[63] += (sum_160_1_106)*MainFormSLS->hh[22];
c2.v[63] += (sum_160_1_107)*MainFormSLS->hh[149];
c2.v[63] += (sum_160_1_108)*MainFormSLS->hh[116];
c2.v[63] += (sum_160_1_109)*MainFormSLS->hh[83];
c2.v[63] += (sum_160_1_110)*MainFormSLS->hh[50];
c2.v[63] += (sum_160_1_111)*MainFormSLS->hh[17];
c2.v[63] += (sum_160_1_112)*MainFormSLS->hh[144];
c2.v[63] += (sum_160_1_113)*MainFormSLS->hh[111];
c2.v[63] += (sum_160_1_114)*MainFormSLS->hh[78];
c2.v[63] += (sum_160_1_115)*MainFormSLS->hh[45];
c2.v[63] += (sum_160_1_116)*MainFormSLS->hh[12];
c2.v[63] += (sum_160_1_117)*MainFormSLS->hh[139];
c2.v[63] += (sum_160_1_118)*MainFormSLS->hh[106];
c2.v[63] += (sum_160_1_119)*MainFormSLS->hh[73];
c2.v[63] += (sum_160_1_120)*MainFormSLS->hh[40];
c2.v[63] += (sum_160_1_121)*MainFormSLS->hh[7];
c2.v[63] += (sum_160_1_122)*MainFormSLS->hh[134];
c2.v[63] += (sum_160_1_123)*MainFormSLS->hh[101];
c2.v[63] += (sum_160_1_124)*MainFormSLS->hh[68];
c2.v[63] += (sum_160_1_125)*MainFormSLS->hh[35];
c2.v[63] += (sum_160_1_126)*MainFormSLS->hh[2];
c2.v[63] += (sum_160_1_127)*MainFormSLS->hh[129];
c2.v[63] += (sum_160_1_128)*MainFormSLS->hh[96];
c2.v[63] += (sum_160_1_129)*MainFormSLS->hh[63];
c2.v[63] += (sum_160_1_130)*MainFormSLS->hh[30];
c2.v[63] += (sum_160_1_131)*MainFormSLS->hh[157];
c2.v[63] += (sum_160_1_132)*MainFormSLS->hh[124];
c2.v[63] += (sum_160_1_133)*MainFormSLS->hh[91];
c2.v[63] += (sum_160_1_134)*MainFormSLS->hh[58];
c2.v[63] += (sum_160_1_135)*MainFormSLS->hh[25];
c2.v[63] += (sum_160_1_136)*MainFormSLS->hh[152];
c2.v[63] += (sum_160_1_137)*MainFormSLS->hh[119];
c2.v[63] += (sum_160_1_138)*MainFormSLS->hh[86];
c2.v[63] += (sum_160_1_139)*MainFormSLS->hh[53];
c2.v[63] += (sum_160_1_140)*MainFormSLS->hh[20];
c2.v[63] += (sum_160_1_141)*MainFormSLS->hh[147];
c2.v[63] += (sum_160_1_142)*MainFormSLS->hh[114];
c2.v[63] += (sum_160_1_143)*MainFormSLS->hh[81];
c2.v[63] += (sum_160_1_144)*MainFormSLS->hh[48];
c2.v[63] += (sum_160_1_145)*MainFormSLS->hh[15];
c2.v[63] += (sum_160_1_146)*MainFormSLS->hh[142];
c2.v[63] += (sum_160_1_147)*MainFormSLS->hh[109];
c2.v[63] += (sum_160_1_148)*MainFormSLS->hh[76];
c2.v[63] += (sum_160_1_149)*MainFormSLS->hh[43];
c2.v[63] += (sum_160_1_150)*MainFormSLS->hh[10];
c2.v[63] += (sum_160_1_151)*MainFormSLS->hh[137];
c2.v[63] += (sum_160_1_152)*MainFormSLS->hh[104];
c2.v[63] += (sum_160_1_153)*MainFormSLS->hh[71];
c2.v[63] += (sum_160_1_154)*MainFormSLS->hh[38];
c2.v[63] += (sum_160_1_155)*MainFormSLS->hh[5];
c2.v[63] += (sum_160_1_156)*MainFormSLS->hh[132];
c2.v[63] += (sum_160_1_157)*MainFormSLS->hh[99];
c2.v[63] += (sum_160_1_158)*MainFormSLS->hh[66];
c2.v[63] += (sum_160_1_159)*MainFormSLS->hh[33];

//frequency level id 129
c2.v[64] += (sum_160_1_000)*MainFormSLS->hh[0];
c2.v[64] += (sum_160_1_001)*MainFormSLS->hh[129];
c2.v[64] += (sum_160_1_002)*MainFormSLS->hh[98];
c2.v[64] += (sum_160_1_003)*MainFormSLS->hh[67];
c2.v[64] += (sum_160_1_004)*MainFormSLS->hh[36];
c2.v[64] += (sum_160_1_005)*MainFormSLS->hh[5];
c2.v[64] += (sum_160_1_006)*MainFormSLS->hh[134];
c2.v[64] += (sum_160_1_007)*MainFormSLS->hh[103];
c2.v[64] += (sum_160_1_008)*MainFormSLS->hh[72];
c2.v[64] += (sum_160_1_009)*MainFormSLS->hh[41];
c2.v[64] += (sum_160_1_010)*MainFormSLS->hh[10];
c2.v[64] += (sum_160_1_011)*MainFormSLS->hh[139];
c2.v[64] += (sum_160_1_012)*MainFormSLS->hh[108];
c2.v[64] += (sum_160_1_013)*MainFormSLS->hh[77];
c2.v[64] += (sum_160_1_014)*MainFormSLS->hh[46];
c2.v[64] += (sum_160_1_015)*MainFormSLS->hh[15];
c2.v[64] += (sum_160_1_016)*MainFormSLS->hh[144];
c2.v[64] += (sum_160_1_017)*MainFormSLS->hh[113];
c2.v[64] += (sum_160_1_018)*MainFormSLS->hh[82];
c2.v[64] += (sum_160_1_019)*MainFormSLS->hh[51];
c2.v[64] += (sum_160_1_020)*MainFormSLS->hh[20];
c2.v[64] += (sum_160_1_021)*MainFormSLS->hh[149];
c2.v[64] += (sum_160_1_022)*MainFormSLS->hh[118];
c2.v[64] += (sum_160_1_023)*MainFormSLS->hh[87];
c2.v[64] += (sum_160_1_024)*MainFormSLS->hh[56];
c2.v[64] += (sum_160_1_025)*MainFormSLS->hh[25];
c2.v[64] += (sum_160_1_026)*MainFormSLS->hh[154];
c2.v[64] += (sum_160_1_027)*MainFormSLS->hh[123];
c2.v[64] += (sum_160_1_028)*MainFormSLS->hh[92];
c2.v[64] += (sum_160_1_029)*MainFormSLS->hh[61];
c2.v[64] += (sum_160_1_030)*MainFormSLS->hh[30];
c2.v[64] += (sum_160_1_031)*MainFormSLS->hh[159];
c2.v[64] += (sum_160_1_032)*MainFormSLS->hh[128];
c2.v[64] += (sum_160_1_033)*MainFormSLS->hh[97];
c2.v[64] += (sum_160_1_034)*MainFormSLS->hh[66];
c2.v[64] += (sum_160_1_035)*MainFormSLS->hh[35];
c2.v[64] += (sum_160_1_036)*MainFormSLS->hh[4];
c2.v[64] += (sum_160_1_037)*MainFormSLS->hh[133];
c2.v[64] += (sum_160_1_038)*MainFormSLS->hh[102];
c2.v[64] += (sum_160_1_039)*MainFormSLS->hh[71];
c2.v[64] += (sum_160_1_040)*MainFormSLS->hh[40];
c2.v[64] += (sum_160_1_041)*MainFormSLS->hh[9];
c2.v[64] += (sum_160_1_042)*MainFormSLS->hh[138];
c2.v[64] += (sum_160_1_043)*MainFormSLS->hh[107];
c2.v[64] += (sum_160_1_044)*MainFormSLS->hh[76];
c2.v[64] += (sum_160_1_045)*MainFormSLS->hh[45];
c2.v[64] += (sum_160_1_046)*MainFormSLS->hh[14];
c2.v[64] += (sum_160_1_047)*MainFormSLS->hh[143];
c2.v[64] += (sum_160_1_048)*MainFormSLS->hh[112];
c2.v[64] += (sum_160_1_049)*MainFormSLS->hh[81];
c2.v[64] += (sum_160_1_050)*MainFormSLS->hh[50];
c2.v[64] += (sum_160_1_051)*MainFormSLS->hh[19];
c2.v[64] += (sum_160_1_052)*MainFormSLS->hh[148];
c2.v[64] += (sum_160_1_053)*MainFormSLS->hh[117];
c2.v[64] += (sum_160_1_054)*MainFormSLS->hh[86];
c2.v[64] += (sum_160_1_055)*MainFormSLS->hh[55];
c2.v[64] += (sum_160_1_056)*MainFormSLS->hh[24];
c2.v[64] += (sum_160_1_057)*MainFormSLS->hh[153];
c2.v[64] += (sum_160_1_058)*MainFormSLS->hh[122];
c2.v[64] += (sum_160_1_059)*MainFormSLS->hh[91];
c2.v[64] += (sum_160_1_060)*MainFormSLS->hh[60];
c2.v[64] += (sum_160_1_061)*MainFormSLS->hh[29];
c2.v[64] += (sum_160_1_062)*MainFormSLS->hh[158];
c2.v[64] += (sum_160_1_063)*MainFormSLS->hh[127];
c2.v[64] += (sum_160_1_064)*MainFormSLS->hh[96];
c2.v[64] += (sum_160_1_065)*MainFormSLS->hh[65];
c2.v[64] += (sum_160_1_066)*MainFormSLS->hh[34];
c2.v[64] += (sum_160_1_067)*MainFormSLS->hh[3];
c2.v[64] += (sum_160_1_068)*MainFormSLS->hh[132];
c2.v[64] += (sum_160_1_069)*MainFormSLS->hh[101];
c2.v[64] += (sum_160_1_070)*MainFormSLS->hh[70];
c2.v[64] += (sum_160_1_071)*MainFormSLS->hh[39];
c2.v[64] += (sum_160_1_072)*MainFormSLS->hh[8];
c2.v[64] += (sum_160_1_073)*MainFormSLS->hh[137];
c2.v[64] += (sum_160_1_074)*MainFormSLS->hh[106];
c2.v[64] += (sum_160_1_075)*MainFormSLS->hh[75];
c2.v[64] += (sum_160_1_076)*MainFormSLS->hh[44];
c2.v[64] += (sum_160_1_077)*MainFormSLS->hh[13];
c2.v[64] += (sum_160_1_078)*MainFormSLS->hh[142];
c2.v[64] += (sum_160_1_079)*MainFormSLS->hh[111];
c2.v[64] += (sum_160_1_080)*MainFormSLS->hh[80];
c2.v[64] += (sum_160_1_081)*MainFormSLS->hh[49];
c2.v[64] += (sum_160_1_082)*MainFormSLS->hh[18];
c2.v[64] += (sum_160_1_083)*MainFormSLS->hh[147];
c2.v[64] += (sum_160_1_084)*MainFormSLS->hh[116];
c2.v[64] += (sum_160_1_085)*MainFormSLS->hh[85];
c2.v[64] += (sum_160_1_086)*MainFormSLS->hh[54];
c2.v[64] += (sum_160_1_087)*MainFormSLS->hh[23];
c2.v[64] += (sum_160_1_088)*MainFormSLS->hh[152];
c2.v[64] += (sum_160_1_089)*MainFormSLS->hh[121];
c2.v[64] += (sum_160_1_090)*MainFormSLS->hh[90];
c2.v[64] += (sum_160_1_091)*MainFormSLS->hh[59];
c2.v[64] += (sum_160_1_092)*MainFormSLS->hh[28];
c2.v[64] += (sum_160_1_093)*MainFormSLS->hh[157];
c2.v[64] += (sum_160_1_094)*MainFormSLS->hh[126];
c2.v[64] += (sum_160_1_095)*MainFormSLS->hh[95];
c2.v[64] += (sum_160_1_096)*MainFormSLS->hh[64];
c2.v[64] += (sum_160_1_097)*MainFormSLS->hh[33];
c2.v[64] += (sum_160_1_098)*MainFormSLS->hh[2];
c2.v[64] += (sum_160_1_099)*MainFormSLS->hh[131];
c2.v[64] += (sum_160_1_100)*MainFormSLS->hh[100];
c2.v[64] += (sum_160_1_101)*MainFormSLS->hh[69];
c2.v[64] += (sum_160_1_102)*MainFormSLS->hh[38];
c2.v[64] += (sum_160_1_103)*MainFormSLS->hh[7];
c2.v[64] += (sum_160_1_104)*MainFormSLS->hh[136];
c2.v[64] += (sum_160_1_105)*MainFormSLS->hh[105];
c2.v[64] += (sum_160_1_106)*MainFormSLS->hh[74];
c2.v[64] += (sum_160_1_107)*MainFormSLS->hh[43];
c2.v[64] += (sum_160_1_108)*MainFormSLS->hh[12];
c2.v[64] += (sum_160_1_109)*MainFormSLS->hh[141];
c2.v[64] += (sum_160_1_110)*MainFormSLS->hh[110];
c2.v[64] += (sum_160_1_111)*MainFormSLS->hh[79];
c2.v[64] += (sum_160_1_112)*MainFormSLS->hh[48];
c2.v[64] += (sum_160_1_113)*MainFormSLS->hh[17];
c2.v[64] += (sum_160_1_114)*MainFormSLS->hh[146];
c2.v[64] += (sum_160_1_115)*MainFormSLS->hh[115];
c2.v[64] += (sum_160_1_116)*MainFormSLS->hh[84];
c2.v[64] += (sum_160_1_117)*MainFormSLS->hh[53];
c2.v[64] += (sum_160_1_118)*MainFormSLS->hh[22];
c2.v[64] += (sum_160_1_119)*MainFormSLS->hh[151];
c2.v[64] += (sum_160_1_120)*MainFormSLS->hh[120];
c2.v[64] += (sum_160_1_121)*MainFormSLS->hh[89];
c2.v[64] += (sum_160_1_122)*MainFormSLS->hh[58];
c2.v[64] += (sum_160_1_123)*MainFormSLS->hh[27];
c2.v[64] += (sum_160_1_124)*MainFormSLS->hh[156];
c2.v[64] += (sum_160_1_125)*MainFormSLS->hh[125];
c2.v[64] += (sum_160_1_126)*MainFormSLS->hh[94];
c2.v[64] += (sum_160_1_127)*MainFormSLS->hh[63];
c2.v[64] += (sum_160_1_128)*MainFormSLS->hh[32];
c2.v[64] += (sum_160_1_129)*MainFormSLS->hh[1];
c2.v[64] += (sum_160_1_130)*MainFormSLS->hh[130];
c2.v[64] += (sum_160_1_131)*MainFormSLS->hh[99];
c2.v[64] += (sum_160_1_132)*MainFormSLS->hh[68];
c2.v[64] += (sum_160_1_133)*MainFormSLS->hh[37];
c2.v[64] += (sum_160_1_134)*MainFormSLS->hh[6];
c2.v[64] += (sum_160_1_135)*MainFormSLS->hh[135];
c2.v[64] += (sum_160_1_136)*MainFormSLS->hh[104];
c2.v[64] += (sum_160_1_137)*MainFormSLS->hh[73];
c2.v[64] += (sum_160_1_138)*MainFormSLS->hh[42];
c2.v[64] += (sum_160_1_139)*MainFormSLS->hh[11];
c2.v[64] += (sum_160_1_140)*MainFormSLS->hh[140];
c2.v[64] += (sum_160_1_141)*MainFormSLS->hh[109];
c2.v[64] += (sum_160_1_142)*MainFormSLS->hh[78];
c2.v[64] += (sum_160_1_143)*MainFormSLS->hh[47];
c2.v[64] += (sum_160_1_144)*MainFormSLS->hh[16];
c2.v[64] += (sum_160_1_145)*MainFormSLS->hh[145];
c2.v[64] += (sum_160_1_146)*MainFormSLS->hh[114];
c2.v[64] += (sum_160_1_147)*MainFormSLS->hh[83];
c2.v[64] += (sum_160_1_148)*MainFormSLS->hh[52];
c2.v[64] += (sum_160_1_149)*MainFormSLS->hh[21];
c2.v[64] += (sum_160_1_150)*MainFormSLS->hh[150];
c2.v[64] += (sum_160_1_151)*MainFormSLS->hh[119];
c2.v[64] += (sum_160_1_152)*MainFormSLS->hh[88];
c2.v[64] += (sum_160_1_153)*MainFormSLS->hh[57];
c2.v[64] += (sum_160_1_154)*MainFormSLS->hh[26];
c2.v[64] += (sum_160_1_155)*MainFormSLS->hh[155];
c2.v[64] += (sum_160_1_156)*MainFormSLS->hh[124];
c2.v[64] += (sum_160_1_157)*MainFormSLS->hh[93];
c2.v[64] += (sum_160_1_158)*MainFormSLS->hh[62];
c2.v[64] += (sum_160_1_159)*MainFormSLS->hh[31];

//frequency level id 131
c2.v[65] += (sum_160_1_000)*MainFormSLS->hh[0];
c2.v[65] += (sum_160_1_001)*MainFormSLS->hh[131];
c2.v[65] += (sum_160_1_002)*MainFormSLS->hh[102];
c2.v[65] += (sum_160_1_003)*MainFormSLS->hh[73];
c2.v[65] += (sum_160_1_004)*MainFormSLS->hh[44];
c2.v[65] += (sum_160_1_005)*MainFormSLS->hh[15];
c2.v[65] += (sum_160_1_006)*MainFormSLS->hh[146];
c2.v[65] += (sum_160_1_007)*MainFormSLS->hh[117];
c2.v[65] += (sum_160_1_008)*MainFormSLS->hh[88];
c2.v[65] += (sum_160_1_009)*MainFormSLS->hh[59];
c2.v[65] += (sum_160_1_010)*MainFormSLS->hh[30];
c2.v[65] += (sum_160_1_011)*MainFormSLS->hh[1];
c2.v[65] += (sum_160_1_012)*MainFormSLS->hh[132];
c2.v[65] += (sum_160_1_013)*MainFormSLS->hh[103];
c2.v[65] += (sum_160_1_014)*MainFormSLS->hh[74];
c2.v[65] += (sum_160_1_015)*MainFormSLS->hh[45];
c2.v[65] += (sum_160_1_016)*MainFormSLS->hh[16];
c2.v[65] += (sum_160_1_017)*MainFormSLS->hh[147];
c2.v[65] += (sum_160_1_018)*MainFormSLS->hh[118];
c2.v[65] += (sum_160_1_019)*MainFormSLS->hh[89];
c2.v[65] += (sum_160_1_020)*MainFormSLS->hh[60];
c2.v[65] += (sum_160_1_021)*MainFormSLS->hh[31];
c2.v[65] += (sum_160_1_022)*MainFormSLS->hh[2];
c2.v[65] += (sum_160_1_023)*MainFormSLS->hh[133];
c2.v[65] += (sum_160_1_024)*MainFormSLS->hh[104];
c2.v[65] += (sum_160_1_025)*MainFormSLS->hh[75];
c2.v[65] += (sum_160_1_026)*MainFormSLS->hh[46];
c2.v[65] += (sum_160_1_027)*MainFormSLS->hh[17];
c2.v[65] += (sum_160_1_028)*MainFormSLS->hh[148];
c2.v[65] += (sum_160_1_029)*MainFormSLS->hh[119];
c2.v[65] += (sum_160_1_030)*MainFormSLS->hh[90];
c2.v[65] += (sum_160_1_031)*MainFormSLS->hh[61];
c2.v[65] += (sum_160_1_032)*MainFormSLS->hh[32];
c2.v[65] += (sum_160_1_033)*MainFormSLS->hh[3];
c2.v[65] += (sum_160_1_034)*MainFormSLS->hh[134];
c2.v[65] += (sum_160_1_035)*MainFormSLS->hh[105];
c2.v[65] += (sum_160_1_036)*MainFormSLS->hh[76];
c2.v[65] += (sum_160_1_037)*MainFormSLS->hh[47];
c2.v[65] += (sum_160_1_038)*MainFormSLS->hh[18];
c2.v[65] += (sum_160_1_039)*MainFormSLS->hh[149];
c2.v[65] += (sum_160_1_040)*MainFormSLS->hh[120];
c2.v[65] += (sum_160_1_041)*MainFormSLS->hh[91];
c2.v[65] += (sum_160_1_042)*MainFormSLS->hh[62];
c2.v[65] += (sum_160_1_043)*MainFormSLS->hh[33];
c2.v[65] += (sum_160_1_044)*MainFormSLS->hh[4];
c2.v[65] += (sum_160_1_045)*MainFormSLS->hh[135];
c2.v[65] += (sum_160_1_046)*MainFormSLS->hh[106];
c2.v[65] += (sum_160_1_047)*MainFormSLS->hh[77];
c2.v[65] += (sum_160_1_048)*MainFormSLS->hh[48];
c2.v[65] += (sum_160_1_049)*MainFormSLS->hh[19];
c2.v[65] += (sum_160_1_050)*MainFormSLS->hh[150];
c2.v[65] += (sum_160_1_051)*MainFormSLS->hh[121];
c2.v[65] += (sum_160_1_052)*MainFormSLS->hh[92];
c2.v[65] += (sum_160_1_053)*MainFormSLS->hh[63];
c2.v[65] += (sum_160_1_054)*MainFormSLS->hh[34];
c2.v[65] += (sum_160_1_055)*MainFormSLS->hh[5];
c2.v[65] += (sum_160_1_056)*MainFormSLS->hh[136];
c2.v[65] += (sum_160_1_057)*MainFormSLS->hh[107];
c2.v[65] += (sum_160_1_058)*MainFormSLS->hh[78];
c2.v[65] += (sum_160_1_059)*MainFormSLS->hh[49];
c2.v[65] += (sum_160_1_060)*MainFormSLS->hh[20];
c2.v[65] += (sum_160_1_061)*MainFormSLS->hh[151];
c2.v[65] += (sum_160_1_062)*MainFormSLS->hh[122];
c2.v[65] += (sum_160_1_063)*MainFormSLS->hh[93];
c2.v[65] += (sum_160_1_064)*MainFormSLS->hh[64];
c2.v[65] += (sum_160_1_065)*MainFormSLS->hh[35];
c2.v[65] += (sum_160_1_066)*MainFormSLS->hh[6];
c2.v[65] += (sum_160_1_067)*MainFormSLS->hh[137];
c2.v[65] += (sum_160_1_068)*MainFormSLS->hh[108];
c2.v[65] += (sum_160_1_069)*MainFormSLS->hh[79];
c2.v[65] += (sum_160_1_070)*MainFormSLS->hh[50];
c2.v[65] += (sum_160_1_071)*MainFormSLS->hh[21];
c2.v[65] += (sum_160_1_072)*MainFormSLS->hh[152];
c2.v[65] += (sum_160_1_073)*MainFormSLS->hh[123];
c2.v[65] += (sum_160_1_074)*MainFormSLS->hh[94];
c2.v[65] += (sum_160_1_075)*MainFormSLS->hh[65];
c2.v[65] += (sum_160_1_076)*MainFormSLS->hh[36];
c2.v[65] += (sum_160_1_077)*MainFormSLS->hh[7];
c2.v[65] += (sum_160_1_078)*MainFormSLS->hh[138];
c2.v[65] += (sum_160_1_079)*MainFormSLS->hh[109];
c2.v[65] += (sum_160_1_080)*MainFormSLS->hh[80];
c2.v[65] += (sum_160_1_081)*MainFormSLS->hh[51];
c2.v[65] += (sum_160_1_082)*MainFormSLS->hh[22];
c2.v[65] += (sum_160_1_083)*MainFormSLS->hh[153];
c2.v[65] += (sum_160_1_084)*MainFormSLS->hh[124];
c2.v[65] += (sum_160_1_085)*MainFormSLS->hh[95];
c2.v[65] += (sum_160_1_086)*MainFormSLS->hh[66];
c2.v[65] += (sum_160_1_087)*MainFormSLS->hh[37];
c2.v[65] += (sum_160_1_088)*MainFormSLS->hh[8];
c2.v[65] += (sum_160_1_089)*MainFormSLS->hh[139];
c2.v[65] += (sum_160_1_090)*MainFormSLS->hh[110];
c2.v[65] += (sum_160_1_091)*MainFormSLS->hh[81];
c2.v[65] += (sum_160_1_092)*MainFormSLS->hh[52];
c2.v[65] += (sum_160_1_093)*MainFormSLS->hh[23];
c2.v[65] += (sum_160_1_094)*MainFormSLS->hh[154];
c2.v[65] += (sum_160_1_095)*MainFormSLS->hh[125];
c2.v[65] += (sum_160_1_096)*MainFormSLS->hh[96];
c2.v[65] += (sum_160_1_097)*MainFormSLS->hh[67];
c2.v[65] += (sum_160_1_098)*MainFormSLS->hh[38];
c2.v[65] += (sum_160_1_099)*MainFormSLS->hh[9];
c2.v[65] += (sum_160_1_100)*MainFormSLS->hh[140];
c2.v[65] += (sum_160_1_101)*MainFormSLS->hh[111];
c2.v[65] += (sum_160_1_102)*MainFormSLS->hh[82];
c2.v[65] += (sum_160_1_103)*MainFormSLS->hh[53];
c2.v[65] += (sum_160_1_104)*MainFormSLS->hh[24];
c2.v[65] += (sum_160_1_105)*MainFormSLS->hh[155];
c2.v[65] += (sum_160_1_106)*MainFormSLS->hh[126];
c2.v[65] += (sum_160_1_107)*MainFormSLS->hh[97];
c2.v[65] += (sum_160_1_108)*MainFormSLS->hh[68];
c2.v[65] += (sum_160_1_109)*MainFormSLS->hh[39];
c2.v[65] += (sum_160_1_110)*MainFormSLS->hh[10];
c2.v[65] += (sum_160_1_111)*MainFormSLS->hh[141];
c2.v[65] += (sum_160_1_112)*MainFormSLS->hh[112];
c2.v[65] += (sum_160_1_113)*MainFormSLS->hh[83];
c2.v[65] += (sum_160_1_114)*MainFormSLS->hh[54];
c2.v[65] += (sum_160_1_115)*MainFormSLS->hh[25];
c2.v[65] += (sum_160_1_116)*MainFormSLS->hh[156];
c2.v[65] += (sum_160_1_117)*MainFormSLS->hh[127];
c2.v[65] += (sum_160_1_118)*MainFormSLS->hh[98];
c2.v[65] += (sum_160_1_119)*MainFormSLS->hh[69];
c2.v[65] += (sum_160_1_120)*MainFormSLS->hh[40];
c2.v[65] += (sum_160_1_121)*MainFormSLS->hh[11];
c2.v[65] += (sum_160_1_122)*MainFormSLS->hh[142];
c2.v[65] += (sum_160_1_123)*MainFormSLS->hh[113];
c2.v[65] += (sum_160_1_124)*MainFormSLS->hh[84];
c2.v[65] += (sum_160_1_125)*MainFormSLS->hh[55];
c2.v[65] += (sum_160_1_126)*MainFormSLS->hh[26];
c2.v[65] += (sum_160_1_127)*MainFormSLS->hh[157];
c2.v[65] += (sum_160_1_128)*MainFormSLS->hh[128];
c2.v[65] += (sum_160_1_129)*MainFormSLS->hh[99];
c2.v[65] += (sum_160_1_130)*MainFormSLS->hh[70];
c2.v[65] += (sum_160_1_131)*MainFormSLS->hh[41];
c2.v[65] += (sum_160_1_132)*MainFormSLS->hh[12];
c2.v[65] += (sum_160_1_133)*MainFormSLS->hh[143];
c2.v[65] += (sum_160_1_134)*MainFormSLS->hh[114];
c2.v[65] += (sum_160_1_135)*MainFormSLS->hh[85];
c2.v[65] += (sum_160_1_136)*MainFormSLS->hh[56];
c2.v[65] += (sum_160_1_137)*MainFormSLS->hh[27];
c2.v[65] += (sum_160_1_138)*MainFormSLS->hh[158];
c2.v[65] += (sum_160_1_139)*MainFormSLS->hh[129];
c2.v[65] += (sum_160_1_140)*MainFormSLS->hh[100];
c2.v[65] += (sum_160_1_141)*MainFormSLS->hh[71];
c2.v[65] += (sum_160_1_142)*MainFormSLS->hh[42];
c2.v[65] += (sum_160_1_143)*MainFormSLS->hh[13];
c2.v[65] += (sum_160_1_144)*MainFormSLS->hh[144];
c2.v[65] += (sum_160_1_145)*MainFormSLS->hh[115];
c2.v[65] += (sum_160_1_146)*MainFormSLS->hh[86];
c2.v[65] += (sum_160_1_147)*MainFormSLS->hh[57];
c2.v[65] += (sum_160_1_148)*MainFormSLS->hh[28];
c2.v[65] += (sum_160_1_149)*MainFormSLS->hh[159];
c2.v[65] += (sum_160_1_150)*MainFormSLS->hh[130];
c2.v[65] += (sum_160_1_151)*MainFormSLS->hh[101];
c2.v[65] += (sum_160_1_152)*MainFormSLS->hh[72];
c2.v[65] += (sum_160_1_153)*MainFormSLS->hh[43];
c2.v[65] += (sum_160_1_154)*MainFormSLS->hh[14];
c2.v[65] += (sum_160_1_155)*MainFormSLS->hh[145];
c2.v[65] += (sum_160_1_156)*MainFormSLS->hh[116];
c2.v[65] += (sum_160_1_157)*MainFormSLS->hh[87];
c2.v[65] += (sum_160_1_158)*MainFormSLS->hh[58];
c2.v[65] += (sum_160_1_159)*MainFormSLS->hh[29];

//frequency level id 133
c2.v[66] += (sum_160_1_000)*MainFormSLS->hh[0];
c2.v[66] += (sum_160_1_001)*MainFormSLS->hh[133];
c2.v[66] += (sum_160_1_002)*MainFormSLS->hh[106];
c2.v[66] += (sum_160_1_003)*MainFormSLS->hh[79];
c2.v[66] += (sum_160_1_004)*MainFormSLS->hh[52];
c2.v[66] += (sum_160_1_005)*MainFormSLS->hh[25];
c2.v[66] += (sum_160_1_006)*MainFormSLS->hh[158];
c2.v[66] += (sum_160_1_007)*MainFormSLS->hh[131];
c2.v[66] += (sum_160_1_008)*MainFormSLS->hh[104];
c2.v[66] += (sum_160_1_009)*MainFormSLS->hh[77];
c2.v[66] += (sum_160_1_010)*MainFormSLS->hh[50];
c2.v[66] += (sum_160_1_011)*MainFormSLS->hh[23];
c2.v[66] += (sum_160_1_012)*MainFormSLS->hh[156];
c2.v[66] += (sum_160_1_013)*MainFormSLS->hh[129];
c2.v[66] += (sum_160_1_014)*MainFormSLS->hh[102];
c2.v[66] += (sum_160_1_015)*MainFormSLS->hh[75];
c2.v[66] += (sum_160_1_016)*MainFormSLS->hh[48];
c2.v[66] += (sum_160_1_017)*MainFormSLS->hh[21];
c2.v[66] += (sum_160_1_018)*MainFormSLS->hh[154];
c2.v[66] += (sum_160_1_019)*MainFormSLS->hh[127];
c2.v[66] += (sum_160_1_020)*MainFormSLS->hh[100];
c2.v[66] += (sum_160_1_021)*MainFormSLS->hh[73];
c2.v[66] += (sum_160_1_022)*MainFormSLS->hh[46];
c2.v[66] += (sum_160_1_023)*MainFormSLS->hh[19];
c2.v[66] += (sum_160_1_024)*MainFormSLS->hh[152];
c2.v[66] += (sum_160_1_025)*MainFormSLS->hh[125];
c2.v[66] += (sum_160_1_026)*MainFormSLS->hh[98];
c2.v[66] += (sum_160_1_027)*MainFormSLS->hh[71];
c2.v[66] += (sum_160_1_028)*MainFormSLS->hh[44];
c2.v[66] += (sum_160_1_029)*MainFormSLS->hh[17];
c2.v[66] += (sum_160_1_030)*MainFormSLS->hh[150];
c2.v[66] += (sum_160_1_031)*MainFormSLS->hh[123];
c2.v[66] += (sum_160_1_032)*MainFormSLS->hh[96];
c2.v[66] += (sum_160_1_033)*MainFormSLS->hh[69];
c2.v[66] += (sum_160_1_034)*MainFormSLS->hh[42];
c2.v[66] += (sum_160_1_035)*MainFormSLS->hh[15];
c2.v[66] += (sum_160_1_036)*MainFormSLS->hh[148];
c2.v[66] += (sum_160_1_037)*MainFormSLS->hh[121];
c2.v[66] += (sum_160_1_038)*MainFormSLS->hh[94];
c2.v[66] += (sum_160_1_039)*MainFormSLS->hh[67];
c2.v[66] += (sum_160_1_040)*MainFormSLS->hh[40];
c2.v[66] += (sum_160_1_041)*MainFormSLS->hh[13];
c2.v[66] += (sum_160_1_042)*MainFormSLS->hh[146];
c2.v[66] += (sum_160_1_043)*MainFormSLS->hh[119];
c2.v[66] += (sum_160_1_044)*MainFormSLS->hh[92];
c2.v[66] += (sum_160_1_045)*MainFormSLS->hh[65];
c2.v[66] += (sum_160_1_046)*MainFormSLS->hh[38];
c2.v[66] += (sum_160_1_047)*MainFormSLS->hh[11];
c2.v[66] += (sum_160_1_048)*MainFormSLS->hh[144];
c2.v[66] += (sum_160_1_049)*MainFormSLS->hh[117];
c2.v[66] += (sum_160_1_050)*MainFormSLS->hh[90];
c2.v[66] += (sum_160_1_051)*MainFormSLS->hh[63];
c2.v[66] += (sum_160_1_052)*MainFormSLS->hh[36];
c2.v[66] += (sum_160_1_053)*MainFormSLS->hh[9];
c2.v[66] += (sum_160_1_054)*MainFormSLS->hh[142];
c2.v[66] += (sum_160_1_055)*MainFormSLS->hh[115];
c2.v[66] += (sum_160_1_056)*MainFormSLS->hh[88];
c2.v[66] += (sum_160_1_057)*MainFormSLS->hh[61];
c2.v[66] += (sum_160_1_058)*MainFormSLS->hh[34];
c2.v[66] += (sum_160_1_059)*MainFormSLS->hh[7];
c2.v[66] += (sum_160_1_060)*MainFormSLS->hh[140];
c2.v[66] += (sum_160_1_061)*MainFormSLS->hh[113];
c2.v[66] += (sum_160_1_062)*MainFormSLS->hh[86];
c2.v[66] += (sum_160_1_063)*MainFormSLS->hh[59];
c2.v[66] += (sum_160_1_064)*MainFormSLS->hh[32];
c2.v[66] += (sum_160_1_065)*MainFormSLS->hh[5];
c2.v[66] += (sum_160_1_066)*MainFormSLS->hh[138];
c2.v[66] += (sum_160_1_067)*MainFormSLS->hh[111];
c2.v[66] += (sum_160_1_068)*MainFormSLS->hh[84];
c2.v[66] += (sum_160_1_069)*MainFormSLS->hh[57];
c2.v[66] += (sum_160_1_070)*MainFormSLS->hh[30];
c2.v[66] += (sum_160_1_071)*MainFormSLS->hh[3];
c2.v[66] += (sum_160_1_072)*MainFormSLS->hh[136];
c2.v[66] += (sum_160_1_073)*MainFormSLS->hh[109];
c2.v[66] += (sum_160_1_074)*MainFormSLS->hh[82];
c2.v[66] += (sum_160_1_075)*MainFormSLS->hh[55];
c2.v[66] += (sum_160_1_076)*MainFormSLS->hh[28];
c2.v[66] += (sum_160_1_077)*MainFormSLS->hh[1];
c2.v[66] += (sum_160_1_078)*MainFormSLS->hh[134];
c2.v[66] += (sum_160_1_079)*MainFormSLS->hh[107];
c2.v[66] += (sum_160_1_080)*MainFormSLS->hh[80];
c2.v[66] += (sum_160_1_081)*MainFormSLS->hh[53];
c2.v[66] += (sum_160_1_082)*MainFormSLS->hh[26];
c2.v[66] += (sum_160_1_083)*MainFormSLS->hh[159];
c2.v[66] += (sum_160_1_084)*MainFormSLS->hh[132];
c2.v[66] += (sum_160_1_085)*MainFormSLS->hh[105];
c2.v[66] += (sum_160_1_086)*MainFormSLS->hh[78];
c2.v[66] += (sum_160_1_087)*MainFormSLS->hh[51];
c2.v[66] += (sum_160_1_088)*MainFormSLS->hh[24];
c2.v[66] += (sum_160_1_089)*MainFormSLS->hh[157];
c2.v[66] += (sum_160_1_090)*MainFormSLS->hh[130];
c2.v[66] += (sum_160_1_091)*MainFormSLS->hh[103];
c2.v[66] += (sum_160_1_092)*MainFormSLS->hh[76];
c2.v[66] += (sum_160_1_093)*MainFormSLS->hh[49];
c2.v[66] += (sum_160_1_094)*MainFormSLS->hh[22];
c2.v[66] += (sum_160_1_095)*MainFormSLS->hh[155];
c2.v[66] += (sum_160_1_096)*MainFormSLS->hh[128];
c2.v[66] += (sum_160_1_097)*MainFormSLS->hh[101];
c2.v[66] += (sum_160_1_098)*MainFormSLS->hh[74];
c2.v[66] += (sum_160_1_099)*MainFormSLS->hh[47];
c2.v[66] += (sum_160_1_100)*MainFormSLS->hh[20];
c2.v[66] += (sum_160_1_101)*MainFormSLS->hh[153];
c2.v[66] += (sum_160_1_102)*MainFormSLS->hh[126];
c2.v[66] += (sum_160_1_103)*MainFormSLS->hh[99];
c2.v[66] += (sum_160_1_104)*MainFormSLS->hh[72];
c2.v[66] += (sum_160_1_105)*MainFormSLS->hh[45];
c2.v[66] += (sum_160_1_106)*MainFormSLS->hh[18];
c2.v[66] += (sum_160_1_107)*MainFormSLS->hh[151];
c2.v[66] += (sum_160_1_108)*MainFormSLS->hh[124];
c2.v[66] += (sum_160_1_109)*MainFormSLS->hh[97];
c2.v[66] += (sum_160_1_110)*MainFormSLS->hh[70];
c2.v[66] += (sum_160_1_111)*MainFormSLS->hh[43];
c2.v[66] += (sum_160_1_112)*MainFormSLS->hh[16];
c2.v[66] += (sum_160_1_113)*MainFormSLS->hh[149];
c2.v[66] += (sum_160_1_114)*MainFormSLS->hh[122];
c2.v[66] += (sum_160_1_115)*MainFormSLS->hh[95];
c2.v[66] += (sum_160_1_116)*MainFormSLS->hh[68];
c2.v[66] += (sum_160_1_117)*MainFormSLS->hh[41];
c2.v[66] += (sum_160_1_118)*MainFormSLS->hh[14];
c2.v[66] += (sum_160_1_119)*MainFormSLS->hh[147];
c2.v[66] += (sum_160_1_120)*MainFormSLS->hh[120];
c2.v[66] += (sum_160_1_121)*MainFormSLS->hh[93];
c2.v[66] += (sum_160_1_122)*MainFormSLS->hh[66];
c2.v[66] += (sum_160_1_123)*MainFormSLS->hh[39];
c2.v[66] += (sum_160_1_124)*MainFormSLS->hh[12];
c2.v[66] += (sum_160_1_125)*MainFormSLS->hh[145];
c2.v[66] += (sum_160_1_126)*MainFormSLS->hh[118];
c2.v[66] += (sum_160_1_127)*MainFormSLS->hh[91];
c2.v[66] += (sum_160_1_128)*MainFormSLS->hh[64];
c2.v[66] += (sum_160_1_129)*MainFormSLS->hh[37];
c2.v[66] += (sum_160_1_130)*MainFormSLS->hh[10];
c2.v[66] += (sum_160_1_131)*MainFormSLS->hh[143];
c2.v[66] += (sum_160_1_132)*MainFormSLS->hh[116];
c2.v[66] += (sum_160_1_133)*MainFormSLS->hh[89];
c2.v[66] += (sum_160_1_134)*MainFormSLS->hh[62];
c2.v[66] += (sum_160_1_135)*MainFormSLS->hh[35];
c2.v[66] += (sum_160_1_136)*MainFormSLS->hh[8];
c2.v[66] += (sum_160_1_137)*MainFormSLS->hh[141];
c2.v[66] += (sum_160_1_138)*MainFormSLS->hh[114];
c2.v[66] += (sum_160_1_139)*MainFormSLS->hh[87];
c2.v[66] += (sum_160_1_140)*MainFormSLS->hh[60];
c2.v[66] += (sum_160_1_141)*MainFormSLS->hh[33];
c2.v[66] += (sum_160_1_142)*MainFormSLS->hh[6];
c2.v[66] += (sum_160_1_143)*MainFormSLS->hh[139];
c2.v[66] += (sum_160_1_144)*MainFormSLS->hh[112];
c2.v[66] += (sum_160_1_145)*MainFormSLS->hh[85];
c2.v[66] += (sum_160_1_146)*MainFormSLS->hh[58];
c2.v[66] += (sum_160_1_147)*MainFormSLS->hh[31];
c2.v[66] += (sum_160_1_148)*MainFormSLS->hh[4];
c2.v[66] += (sum_160_1_149)*MainFormSLS->hh[137];
c2.v[66] += (sum_160_1_150)*MainFormSLS->hh[110];
c2.v[66] += (sum_160_1_151)*MainFormSLS->hh[83];
c2.v[66] += (sum_160_1_152)*MainFormSLS->hh[56];
c2.v[66] += (sum_160_1_153)*MainFormSLS->hh[29];
c2.v[66] += (sum_160_1_154)*MainFormSLS->hh[2];
c2.v[66] += (sum_160_1_155)*MainFormSLS->hh[135];
c2.v[66] += (sum_160_1_156)*MainFormSLS->hh[108];
c2.v[66] += (sum_160_1_157)*MainFormSLS->hh[81];
c2.v[66] += (sum_160_1_158)*MainFormSLS->hh[54];
c2.v[66] += (sum_160_1_159)*MainFormSLS->hh[27];

//frequency level id 135
c2.v[67] += (sum_32_5_000)*MainFormSLS->hh[0];
c2.v[67] += (sum_32_5_001)*MainFormSLS->hh[135];
c2.v[67] += (sum_32_5_002)*MainFormSLS->hh[110];
c2.v[67] += (sum_32_5_003)*MainFormSLS->hh[85];
c2.v[67] += (sum_32_5_004)*MainFormSLS->hh[60];
c2.v[67] += (sum_32_5_005)*MainFormSLS->hh[35];
c2.v[67] += (sum_32_5_006)*MainFormSLS->hh[10];
c2.v[67] += (sum_32_5_007)*MainFormSLS->hh[145];
c2.v[67] += (sum_32_5_008)*MainFormSLS->hh[120];
c2.v[67] += (sum_32_5_009)*MainFormSLS->hh[95];
c2.v[67] += (sum_32_5_010)*MainFormSLS->hh[70];
c2.v[67] += (sum_32_5_011)*MainFormSLS->hh[45];
c2.v[67] += (sum_32_5_012)*MainFormSLS->hh[20];
c2.v[67] += (sum_32_5_013)*MainFormSLS->hh[155];
c2.v[67] += (sum_32_5_014)*MainFormSLS->hh[130];
c2.v[67] += (sum_32_5_015)*MainFormSLS->hh[105];
c2.v[67] += (sum_32_5_016)*MainFormSLS->hh[80];
c2.v[67] += (sum_32_5_017)*MainFormSLS->hh[55];
c2.v[67] += (sum_32_5_018)*MainFormSLS->hh[30];
c2.v[67] += (sum_32_5_019)*MainFormSLS->hh[5];
c2.v[67] += (sum_32_5_020)*MainFormSLS->hh[140];
c2.v[67] += (sum_32_5_021)*MainFormSLS->hh[115];
c2.v[67] += (sum_32_5_022)*MainFormSLS->hh[90];
c2.v[67] += (sum_32_5_023)*MainFormSLS->hh[65];
c2.v[67] += (sum_32_5_024)*MainFormSLS->hh[40];
c2.v[67] += (sum_32_5_025)*MainFormSLS->hh[15];
c2.v[67] += (sum_32_5_026)*MainFormSLS->hh[150];
c2.v[67] += (sum_32_5_027)*MainFormSLS->hh[125];
c2.v[67] += (sum_32_5_028)*MainFormSLS->hh[100];
c2.v[67] += (sum_32_5_029)*MainFormSLS->hh[75];
c2.v[67] += (sum_32_5_030)*MainFormSLS->hh[50];
c2.v[67] += (sum_32_5_031)*MainFormSLS->hh[25];

//frequency level id 137
c2.v[68] += (sum_160_1_000)*MainFormSLS->hh[0];
c2.v[68] += (sum_160_1_001)*MainFormSLS->hh[137];
c2.v[68] += (sum_160_1_002)*MainFormSLS->hh[114];
c2.v[68] += (sum_160_1_003)*MainFormSLS->hh[91];
c2.v[68] += (sum_160_1_004)*MainFormSLS->hh[68];
c2.v[68] += (sum_160_1_005)*MainFormSLS->hh[45];
c2.v[68] += (sum_160_1_006)*MainFormSLS->hh[22];
c2.v[68] += (sum_160_1_007)*MainFormSLS->hh[159];
c2.v[68] += (sum_160_1_008)*MainFormSLS->hh[136];
c2.v[68] += (sum_160_1_009)*MainFormSLS->hh[113];
c2.v[68] += (sum_160_1_010)*MainFormSLS->hh[90];
c2.v[68] += (sum_160_1_011)*MainFormSLS->hh[67];
c2.v[68] += (sum_160_1_012)*MainFormSLS->hh[44];
c2.v[68] += (sum_160_1_013)*MainFormSLS->hh[21];
c2.v[68] += (sum_160_1_014)*MainFormSLS->hh[158];
c2.v[68] += (sum_160_1_015)*MainFormSLS->hh[135];
c2.v[68] += (sum_160_1_016)*MainFormSLS->hh[112];
c2.v[68] += (sum_160_1_017)*MainFormSLS->hh[89];
c2.v[68] += (sum_160_1_018)*MainFormSLS->hh[66];
c2.v[68] += (sum_160_1_019)*MainFormSLS->hh[43];
c2.v[68] += (sum_160_1_020)*MainFormSLS->hh[20];
c2.v[68] += (sum_160_1_021)*MainFormSLS->hh[157];
c2.v[68] += (sum_160_1_022)*MainFormSLS->hh[134];
c2.v[68] += (sum_160_1_023)*MainFormSLS->hh[111];
c2.v[68] += (sum_160_1_024)*MainFormSLS->hh[88];
c2.v[68] += (sum_160_1_025)*MainFormSLS->hh[65];
c2.v[68] += (sum_160_1_026)*MainFormSLS->hh[42];
c2.v[68] += (sum_160_1_027)*MainFormSLS->hh[19];
c2.v[68] += (sum_160_1_028)*MainFormSLS->hh[156];
c2.v[68] += (sum_160_1_029)*MainFormSLS->hh[133];
c2.v[68] += (sum_160_1_030)*MainFormSLS->hh[110];
c2.v[68] += (sum_160_1_031)*MainFormSLS->hh[87];
c2.v[68] += (sum_160_1_032)*MainFormSLS->hh[64];
c2.v[68] += (sum_160_1_033)*MainFormSLS->hh[41];
c2.v[68] += (sum_160_1_034)*MainFormSLS->hh[18];
c2.v[68] += (sum_160_1_035)*MainFormSLS->hh[155];
c2.v[68] += (sum_160_1_036)*MainFormSLS->hh[132];
c2.v[68] += (sum_160_1_037)*MainFormSLS->hh[109];
c2.v[68] += (sum_160_1_038)*MainFormSLS->hh[86];
c2.v[68] += (sum_160_1_039)*MainFormSLS->hh[63];
c2.v[68] += (sum_160_1_040)*MainFormSLS->hh[40];
c2.v[68] += (sum_160_1_041)*MainFormSLS->hh[17];
c2.v[68] += (sum_160_1_042)*MainFormSLS->hh[154];
c2.v[68] += (sum_160_1_043)*MainFormSLS->hh[131];
c2.v[68] += (sum_160_1_044)*MainFormSLS->hh[108];
c2.v[68] += (sum_160_1_045)*MainFormSLS->hh[85];
c2.v[68] += (sum_160_1_046)*MainFormSLS->hh[62];
c2.v[68] += (sum_160_1_047)*MainFormSLS->hh[39];
c2.v[68] += (sum_160_1_048)*MainFormSLS->hh[16];
c2.v[68] += (sum_160_1_049)*MainFormSLS->hh[153];
c2.v[68] += (sum_160_1_050)*MainFormSLS->hh[130];
c2.v[68] += (sum_160_1_051)*MainFormSLS->hh[107];
c2.v[68] += (sum_160_1_052)*MainFormSLS->hh[84];
c2.v[68] += (sum_160_1_053)*MainFormSLS->hh[61];
c2.v[68] += (sum_160_1_054)*MainFormSLS->hh[38];
c2.v[68] += (sum_160_1_055)*MainFormSLS->hh[15];
c2.v[68] += (sum_160_1_056)*MainFormSLS->hh[152];
c2.v[68] += (sum_160_1_057)*MainFormSLS->hh[129];
c2.v[68] += (sum_160_1_058)*MainFormSLS->hh[106];
c2.v[68] += (sum_160_1_059)*MainFormSLS->hh[83];
c2.v[68] += (sum_160_1_060)*MainFormSLS->hh[60];
c2.v[68] += (sum_160_1_061)*MainFormSLS->hh[37];
c2.v[68] += (sum_160_1_062)*MainFormSLS->hh[14];
c2.v[68] += (sum_160_1_063)*MainFormSLS->hh[151];
c2.v[68] += (sum_160_1_064)*MainFormSLS->hh[128];
c2.v[68] += (sum_160_1_065)*MainFormSLS->hh[105];
c2.v[68] += (sum_160_1_066)*MainFormSLS->hh[82];
c2.v[68] += (sum_160_1_067)*MainFormSLS->hh[59];
c2.v[68] += (sum_160_1_068)*MainFormSLS->hh[36];
c2.v[68] += (sum_160_1_069)*MainFormSLS->hh[13];
c2.v[68] += (sum_160_1_070)*MainFormSLS->hh[150];
c2.v[68] += (sum_160_1_071)*MainFormSLS->hh[127];
c2.v[68] += (sum_160_1_072)*MainFormSLS->hh[104];
c2.v[68] += (sum_160_1_073)*MainFormSLS->hh[81];
c2.v[68] += (sum_160_1_074)*MainFormSLS->hh[58];
c2.v[68] += (sum_160_1_075)*MainFormSLS->hh[35];
c2.v[68] += (sum_160_1_076)*MainFormSLS->hh[12];
c2.v[68] += (sum_160_1_077)*MainFormSLS->hh[149];
c2.v[68] += (sum_160_1_078)*MainFormSLS->hh[126];
c2.v[68] += (sum_160_1_079)*MainFormSLS->hh[103];
c2.v[68] += (sum_160_1_080)*MainFormSLS->hh[80];
c2.v[68] += (sum_160_1_081)*MainFormSLS->hh[57];
c2.v[68] += (sum_160_1_082)*MainFormSLS->hh[34];
c2.v[68] += (sum_160_1_083)*MainFormSLS->hh[11];
c2.v[68] += (sum_160_1_084)*MainFormSLS->hh[148];
c2.v[68] += (sum_160_1_085)*MainFormSLS->hh[125];
c2.v[68] += (sum_160_1_086)*MainFormSLS->hh[102];
c2.v[68] += (sum_160_1_087)*MainFormSLS->hh[79];
c2.v[68] += (sum_160_1_088)*MainFormSLS->hh[56];
c2.v[68] += (sum_160_1_089)*MainFormSLS->hh[33];
c2.v[68] += (sum_160_1_090)*MainFormSLS->hh[10];
c2.v[68] += (sum_160_1_091)*MainFormSLS->hh[147];
c2.v[68] += (sum_160_1_092)*MainFormSLS->hh[124];
c2.v[68] += (sum_160_1_093)*MainFormSLS->hh[101];
c2.v[68] += (sum_160_1_094)*MainFormSLS->hh[78];
c2.v[68] += (sum_160_1_095)*MainFormSLS->hh[55];
c2.v[68] += (sum_160_1_096)*MainFormSLS->hh[32];
c2.v[68] += (sum_160_1_097)*MainFormSLS->hh[9];
c2.v[68] += (sum_160_1_098)*MainFormSLS->hh[146];
c2.v[68] += (sum_160_1_099)*MainFormSLS->hh[123];
c2.v[68] += (sum_160_1_100)*MainFormSLS->hh[100];
c2.v[68] += (sum_160_1_101)*MainFormSLS->hh[77];
c2.v[68] += (sum_160_1_102)*MainFormSLS->hh[54];
c2.v[68] += (sum_160_1_103)*MainFormSLS->hh[31];
c2.v[68] += (sum_160_1_104)*MainFormSLS->hh[8];
c2.v[68] += (sum_160_1_105)*MainFormSLS->hh[145];
c2.v[68] += (sum_160_1_106)*MainFormSLS->hh[122];
c2.v[68] += (sum_160_1_107)*MainFormSLS->hh[99];
c2.v[68] += (sum_160_1_108)*MainFormSLS->hh[76];
c2.v[68] += (sum_160_1_109)*MainFormSLS->hh[53];
c2.v[68] += (sum_160_1_110)*MainFormSLS->hh[30];
c2.v[68] += (sum_160_1_111)*MainFormSLS->hh[7];
c2.v[68] += (sum_160_1_112)*MainFormSLS->hh[144];
c2.v[68] += (sum_160_1_113)*MainFormSLS->hh[121];
c2.v[68] += (sum_160_1_114)*MainFormSLS->hh[98];
c2.v[68] += (sum_160_1_115)*MainFormSLS->hh[75];
c2.v[68] += (sum_160_1_116)*MainFormSLS->hh[52];
c2.v[68] += (sum_160_1_117)*MainFormSLS->hh[29];
c2.v[68] += (sum_160_1_118)*MainFormSLS->hh[6];
c2.v[68] += (sum_160_1_119)*MainFormSLS->hh[143];
c2.v[68] += (sum_160_1_120)*MainFormSLS->hh[120];
c2.v[68] += (sum_160_1_121)*MainFormSLS->hh[97];
c2.v[68] += (sum_160_1_122)*MainFormSLS->hh[74];
c2.v[68] += (sum_160_1_123)*MainFormSLS->hh[51];
c2.v[68] += (sum_160_1_124)*MainFormSLS->hh[28];
c2.v[68] += (sum_160_1_125)*MainFormSLS->hh[5];
c2.v[68] += (sum_160_1_126)*MainFormSLS->hh[142];
c2.v[68] += (sum_160_1_127)*MainFormSLS->hh[119];
c2.v[68] += (sum_160_1_128)*MainFormSLS->hh[96];
c2.v[68] += (sum_160_1_129)*MainFormSLS->hh[73];
c2.v[68] += (sum_160_1_130)*MainFormSLS->hh[50];
c2.v[68] += (sum_160_1_131)*MainFormSLS->hh[27];
c2.v[68] += (sum_160_1_132)*MainFormSLS->hh[4];
c2.v[68] += (sum_160_1_133)*MainFormSLS->hh[141];
c2.v[68] += (sum_160_1_134)*MainFormSLS->hh[118];
c2.v[68] += (sum_160_1_135)*MainFormSLS->hh[95];
c2.v[68] += (sum_160_1_136)*MainFormSLS->hh[72];
c2.v[68] += (sum_160_1_137)*MainFormSLS->hh[49];
c2.v[68] += (sum_160_1_138)*MainFormSLS->hh[26];
c2.v[68] += (sum_160_1_139)*MainFormSLS->hh[3];
c2.v[68] += (sum_160_1_140)*MainFormSLS->hh[140];
c2.v[68] += (sum_160_1_141)*MainFormSLS->hh[117];
c2.v[68] += (sum_160_1_142)*MainFormSLS->hh[94];
c2.v[68] += (sum_160_1_143)*MainFormSLS->hh[71];
c2.v[68] += (sum_160_1_144)*MainFormSLS->hh[48];
c2.v[68] += (sum_160_1_145)*MainFormSLS->hh[25];
c2.v[68] += (sum_160_1_146)*MainFormSLS->hh[2];
c2.v[68] += (sum_160_1_147)*MainFormSLS->hh[139];
c2.v[68] += (sum_160_1_148)*MainFormSLS->hh[116];
c2.v[68] += (sum_160_1_149)*MainFormSLS->hh[93];
c2.v[68] += (sum_160_1_150)*MainFormSLS->hh[70];
c2.v[68] += (sum_160_1_151)*MainFormSLS->hh[47];
c2.v[68] += (sum_160_1_152)*MainFormSLS->hh[24];
c2.v[68] += (sum_160_1_153)*MainFormSLS->hh[1];
c2.v[68] += (sum_160_1_154)*MainFormSLS->hh[138];
c2.v[68] += (sum_160_1_155)*MainFormSLS->hh[115];
c2.v[68] += (sum_160_1_156)*MainFormSLS->hh[92];
c2.v[68] += (sum_160_1_157)*MainFormSLS->hh[69];
c2.v[68] += (sum_160_1_158)*MainFormSLS->hh[46];
c2.v[68] += (sum_160_1_159)*MainFormSLS->hh[23];

//frequency level id 139
c2.v[69] += (sum_160_1_000)*MainFormSLS->hh[0];
c2.v[69] += (sum_160_1_001)*MainFormSLS->hh[139];
c2.v[69] += (sum_160_1_002)*MainFormSLS->hh[118];
c2.v[69] += (sum_160_1_003)*MainFormSLS->hh[97];
c2.v[69] += (sum_160_1_004)*MainFormSLS->hh[76];
c2.v[69] += (sum_160_1_005)*MainFormSLS->hh[55];
c2.v[69] += (sum_160_1_006)*MainFormSLS->hh[34];
c2.v[69] += (sum_160_1_007)*MainFormSLS->hh[13];
c2.v[69] += (sum_160_1_008)*MainFormSLS->hh[152];
c2.v[69] += (sum_160_1_009)*MainFormSLS->hh[131];
c2.v[69] += (sum_160_1_010)*MainFormSLS->hh[110];
c2.v[69] += (sum_160_1_011)*MainFormSLS->hh[89];
c2.v[69] += (sum_160_1_012)*MainFormSLS->hh[68];
c2.v[69] += (sum_160_1_013)*MainFormSLS->hh[47];
c2.v[69] += (sum_160_1_014)*MainFormSLS->hh[26];
c2.v[69] += (sum_160_1_015)*MainFormSLS->hh[5];
c2.v[69] += (sum_160_1_016)*MainFormSLS->hh[144];
c2.v[69] += (sum_160_1_017)*MainFormSLS->hh[123];
c2.v[69] += (sum_160_1_018)*MainFormSLS->hh[102];
c2.v[69] += (sum_160_1_019)*MainFormSLS->hh[81];
c2.v[69] += (sum_160_1_020)*MainFormSLS->hh[60];
c2.v[69] += (sum_160_1_021)*MainFormSLS->hh[39];
c2.v[69] += (sum_160_1_022)*MainFormSLS->hh[18];
c2.v[69] += (sum_160_1_023)*MainFormSLS->hh[157];
c2.v[69] += (sum_160_1_024)*MainFormSLS->hh[136];
c2.v[69] += (sum_160_1_025)*MainFormSLS->hh[115];
c2.v[69] += (sum_160_1_026)*MainFormSLS->hh[94];
c2.v[69] += (sum_160_1_027)*MainFormSLS->hh[73];
c2.v[69] += (sum_160_1_028)*MainFormSLS->hh[52];
c2.v[69] += (sum_160_1_029)*MainFormSLS->hh[31];
c2.v[69] += (sum_160_1_030)*MainFormSLS->hh[10];
c2.v[69] += (sum_160_1_031)*MainFormSLS->hh[149];
c2.v[69] += (sum_160_1_032)*MainFormSLS->hh[128];
c2.v[69] += (sum_160_1_033)*MainFormSLS->hh[107];
c2.v[69] += (sum_160_1_034)*MainFormSLS->hh[86];
c2.v[69] += (sum_160_1_035)*MainFormSLS->hh[65];
c2.v[69] += (sum_160_1_036)*MainFormSLS->hh[44];
c2.v[69] += (sum_160_1_037)*MainFormSLS->hh[23];
c2.v[69] += (sum_160_1_038)*MainFormSLS->hh[2];
c2.v[69] += (sum_160_1_039)*MainFormSLS->hh[141];
c2.v[69] += (sum_160_1_040)*MainFormSLS->hh[120];
c2.v[69] += (sum_160_1_041)*MainFormSLS->hh[99];
c2.v[69] += (sum_160_1_042)*MainFormSLS->hh[78];
c2.v[69] += (sum_160_1_043)*MainFormSLS->hh[57];
c2.v[69] += (sum_160_1_044)*MainFormSLS->hh[36];
c2.v[69] += (sum_160_1_045)*MainFormSLS->hh[15];
c2.v[69] += (sum_160_1_046)*MainFormSLS->hh[154];
c2.v[69] += (sum_160_1_047)*MainFormSLS->hh[133];
c2.v[69] += (sum_160_1_048)*MainFormSLS->hh[112];
c2.v[69] += (sum_160_1_049)*MainFormSLS->hh[91];
c2.v[69] += (sum_160_1_050)*MainFormSLS->hh[70];
c2.v[69] += (sum_160_1_051)*MainFormSLS->hh[49];
c2.v[69] += (sum_160_1_052)*MainFormSLS->hh[28];
c2.v[69] += (sum_160_1_053)*MainFormSLS->hh[7];
c2.v[69] += (sum_160_1_054)*MainFormSLS->hh[146];
c2.v[69] += (sum_160_1_055)*MainFormSLS->hh[125];
c2.v[69] += (sum_160_1_056)*MainFormSLS->hh[104];
c2.v[69] += (sum_160_1_057)*MainFormSLS->hh[83];
c2.v[69] += (sum_160_1_058)*MainFormSLS->hh[62];
c2.v[69] += (sum_160_1_059)*MainFormSLS->hh[41];
c2.v[69] += (sum_160_1_060)*MainFormSLS->hh[20];
c2.v[69] += (sum_160_1_061)*MainFormSLS->hh[159];
c2.v[69] += (sum_160_1_062)*MainFormSLS->hh[138];
c2.v[69] += (sum_160_1_063)*MainFormSLS->hh[117];
c2.v[69] += (sum_160_1_064)*MainFormSLS->hh[96];
c2.v[69] += (sum_160_1_065)*MainFormSLS->hh[75];
c2.v[69] += (sum_160_1_066)*MainFormSLS->hh[54];
c2.v[69] += (sum_160_1_067)*MainFormSLS->hh[33];
c2.v[69] += (sum_160_1_068)*MainFormSLS->hh[12];
c2.v[69] += (sum_160_1_069)*MainFormSLS->hh[151];
c2.v[69] += (sum_160_1_070)*MainFormSLS->hh[130];
c2.v[69] += (sum_160_1_071)*MainFormSLS->hh[109];
c2.v[69] += (sum_160_1_072)*MainFormSLS->hh[88];
c2.v[69] += (sum_160_1_073)*MainFormSLS->hh[67];
c2.v[69] += (sum_160_1_074)*MainFormSLS->hh[46];
c2.v[69] += (sum_160_1_075)*MainFormSLS->hh[25];
c2.v[69] += (sum_160_1_076)*MainFormSLS->hh[4];
c2.v[69] += (sum_160_1_077)*MainFormSLS->hh[143];
c2.v[69] += (sum_160_1_078)*MainFormSLS->hh[122];
c2.v[69] += (sum_160_1_079)*MainFormSLS->hh[101];
c2.v[69] += (sum_160_1_080)*MainFormSLS->hh[80];
c2.v[69] += (sum_160_1_081)*MainFormSLS->hh[59];
c2.v[69] += (sum_160_1_082)*MainFormSLS->hh[38];
c2.v[69] += (sum_160_1_083)*MainFormSLS->hh[17];
c2.v[69] += (sum_160_1_084)*MainFormSLS->hh[156];
c2.v[69] += (sum_160_1_085)*MainFormSLS->hh[135];
c2.v[69] += (sum_160_1_086)*MainFormSLS->hh[114];
c2.v[69] += (sum_160_1_087)*MainFormSLS->hh[93];
c2.v[69] += (sum_160_1_088)*MainFormSLS->hh[72];
c2.v[69] += (sum_160_1_089)*MainFormSLS->hh[51];
c2.v[69] += (sum_160_1_090)*MainFormSLS->hh[30];
c2.v[69] += (sum_160_1_091)*MainFormSLS->hh[9];
c2.v[69] += (sum_160_1_092)*MainFormSLS->hh[148];
c2.v[69] += (sum_160_1_093)*MainFormSLS->hh[127];
c2.v[69] += (sum_160_1_094)*MainFormSLS->hh[106];
c2.v[69] += (sum_160_1_095)*MainFormSLS->hh[85];
c2.v[69] += (sum_160_1_096)*MainFormSLS->hh[64];
c2.v[69] += (sum_160_1_097)*MainFormSLS->hh[43];
c2.v[69] += (sum_160_1_098)*MainFormSLS->hh[22];
c2.v[69] += (sum_160_1_099)*MainFormSLS->hh[1];
c2.v[69] += (sum_160_1_100)*MainFormSLS->hh[140];
c2.v[69] += (sum_160_1_101)*MainFormSLS->hh[119];
c2.v[69] += (sum_160_1_102)*MainFormSLS->hh[98];
c2.v[69] += (sum_160_1_103)*MainFormSLS->hh[77];
c2.v[69] += (sum_160_1_104)*MainFormSLS->hh[56];
c2.v[69] += (sum_160_1_105)*MainFormSLS->hh[35];
c2.v[69] += (sum_160_1_106)*MainFormSLS->hh[14];
c2.v[69] += (sum_160_1_107)*MainFormSLS->hh[153];
c2.v[69] += (sum_160_1_108)*MainFormSLS->hh[132];
c2.v[69] += (sum_160_1_109)*MainFormSLS->hh[111];
c2.v[69] += (sum_160_1_110)*MainFormSLS->hh[90];
c2.v[69] += (sum_160_1_111)*MainFormSLS->hh[69];
c2.v[69] += (sum_160_1_112)*MainFormSLS->hh[48];
c2.v[69] += (sum_160_1_113)*MainFormSLS->hh[27];
c2.v[69] += (sum_160_1_114)*MainFormSLS->hh[6];
c2.v[69] += (sum_160_1_115)*MainFormSLS->hh[145];
c2.v[69] += (sum_160_1_116)*MainFormSLS->hh[124];
c2.v[69] += (sum_160_1_117)*MainFormSLS->hh[103];
c2.v[69] += (sum_160_1_118)*MainFormSLS->hh[82];
c2.v[69] += (sum_160_1_119)*MainFormSLS->hh[61];
c2.v[69] += (sum_160_1_120)*MainFormSLS->hh[40];
c2.v[69] += (sum_160_1_121)*MainFormSLS->hh[19];
c2.v[69] += (sum_160_1_122)*MainFormSLS->hh[158];
c2.v[69] += (sum_160_1_123)*MainFormSLS->hh[137];
c2.v[69] += (sum_160_1_124)*MainFormSLS->hh[116];
c2.v[69] += (sum_160_1_125)*MainFormSLS->hh[95];
c2.v[69] += (sum_160_1_126)*MainFormSLS->hh[74];
c2.v[69] += (sum_160_1_127)*MainFormSLS->hh[53];
c2.v[69] += (sum_160_1_128)*MainFormSLS->hh[32];
c2.v[69] += (sum_160_1_129)*MainFormSLS->hh[11];
c2.v[69] += (sum_160_1_130)*MainFormSLS->hh[150];
c2.v[69] += (sum_160_1_131)*MainFormSLS->hh[129];
c2.v[69] += (sum_160_1_132)*MainFormSLS->hh[108];
c2.v[69] += (sum_160_1_133)*MainFormSLS->hh[87];
c2.v[69] += (sum_160_1_134)*MainFormSLS->hh[66];
c2.v[69] += (sum_160_1_135)*MainFormSLS->hh[45];
c2.v[69] += (sum_160_1_136)*MainFormSLS->hh[24];
c2.v[69] += (sum_160_1_137)*MainFormSLS->hh[3];
c2.v[69] += (sum_160_1_138)*MainFormSLS->hh[142];
c2.v[69] += (sum_160_1_139)*MainFormSLS->hh[121];
c2.v[69] += (sum_160_1_140)*MainFormSLS->hh[100];
c2.v[69] += (sum_160_1_141)*MainFormSLS->hh[79];
c2.v[69] += (sum_160_1_142)*MainFormSLS->hh[58];
c2.v[69] += (sum_160_1_143)*MainFormSLS->hh[37];
c2.v[69] += (sum_160_1_144)*MainFormSLS->hh[16];
c2.v[69] += (sum_160_1_145)*MainFormSLS->hh[155];
c2.v[69] += (sum_160_1_146)*MainFormSLS->hh[134];
c2.v[69] += (sum_160_1_147)*MainFormSLS->hh[113];
c2.v[69] += (sum_160_1_148)*MainFormSLS->hh[92];
c2.v[69] += (sum_160_1_149)*MainFormSLS->hh[71];
c2.v[69] += (sum_160_1_150)*MainFormSLS->hh[50];
c2.v[69] += (sum_160_1_151)*MainFormSLS->hh[29];
c2.v[69] += (sum_160_1_152)*MainFormSLS->hh[8];
c2.v[69] += (sum_160_1_153)*MainFormSLS->hh[147];
c2.v[69] += (sum_160_1_154)*MainFormSLS->hh[126];
c2.v[69] += (sum_160_1_155)*MainFormSLS->hh[105];
c2.v[69] += (sum_160_1_156)*MainFormSLS->hh[84];
c2.v[69] += (sum_160_1_157)*MainFormSLS->hh[63];
c2.v[69] += (sum_160_1_158)*MainFormSLS->hh[42];
c2.v[69] += (sum_160_1_159)*MainFormSLS->hh[21];

//frequency level id 141
c2.v[70] += (sum_160_1_000)*MainFormSLS->hh[0];
c2.v[70] += (sum_160_1_001)*MainFormSLS->hh[141];
c2.v[70] += (sum_160_1_002)*MainFormSLS->hh[122];
c2.v[70] += (sum_160_1_003)*MainFormSLS->hh[103];
c2.v[70] += (sum_160_1_004)*MainFormSLS->hh[84];
c2.v[70] += (sum_160_1_005)*MainFormSLS->hh[65];
c2.v[70] += (sum_160_1_006)*MainFormSLS->hh[46];
c2.v[70] += (sum_160_1_007)*MainFormSLS->hh[27];
c2.v[70] += (sum_160_1_008)*MainFormSLS->hh[8];
c2.v[70] += (sum_160_1_009)*MainFormSLS->hh[149];
c2.v[70] += (sum_160_1_010)*MainFormSLS->hh[130];
c2.v[70] += (sum_160_1_011)*MainFormSLS->hh[111];
c2.v[70] += (sum_160_1_012)*MainFormSLS->hh[92];
c2.v[70] += (sum_160_1_013)*MainFormSLS->hh[73];
c2.v[70] += (sum_160_1_014)*MainFormSLS->hh[54];
c2.v[70] += (sum_160_1_015)*MainFormSLS->hh[35];
c2.v[70] += (sum_160_1_016)*MainFormSLS->hh[16];
c2.v[70] += (sum_160_1_017)*MainFormSLS->hh[157];
c2.v[70] += (sum_160_1_018)*MainFormSLS->hh[138];
c2.v[70] += (sum_160_1_019)*MainFormSLS->hh[119];
c2.v[70] += (sum_160_1_020)*MainFormSLS->hh[100];
c2.v[70] += (sum_160_1_021)*MainFormSLS->hh[81];
c2.v[70] += (sum_160_1_022)*MainFormSLS->hh[62];
c2.v[70] += (sum_160_1_023)*MainFormSLS->hh[43];
c2.v[70] += (sum_160_1_024)*MainFormSLS->hh[24];
c2.v[70] += (sum_160_1_025)*MainFormSLS->hh[5];
c2.v[70] += (sum_160_1_026)*MainFormSLS->hh[146];
c2.v[70] += (sum_160_1_027)*MainFormSLS->hh[127];
c2.v[70] += (sum_160_1_028)*MainFormSLS->hh[108];
c2.v[70] += (sum_160_1_029)*MainFormSLS->hh[89];
c2.v[70] += (sum_160_1_030)*MainFormSLS->hh[70];
c2.v[70] += (sum_160_1_031)*MainFormSLS->hh[51];
c2.v[70] += (sum_160_1_032)*MainFormSLS->hh[32];
c2.v[70] += (sum_160_1_033)*MainFormSLS->hh[13];
c2.v[70] += (sum_160_1_034)*MainFormSLS->hh[154];
c2.v[70] += (sum_160_1_035)*MainFormSLS->hh[135];
c2.v[70] += (sum_160_1_036)*MainFormSLS->hh[116];
c2.v[70] += (sum_160_1_037)*MainFormSLS->hh[97];
c2.v[70] += (sum_160_1_038)*MainFormSLS->hh[78];
c2.v[70] += (sum_160_1_039)*MainFormSLS->hh[59];
c2.v[70] += (sum_160_1_040)*MainFormSLS->hh[40];
c2.v[70] += (sum_160_1_041)*MainFormSLS->hh[21];
c2.v[70] += (sum_160_1_042)*MainFormSLS->hh[2];
c2.v[70] += (sum_160_1_043)*MainFormSLS->hh[143];
c2.v[70] += (sum_160_1_044)*MainFormSLS->hh[124];
c2.v[70] += (sum_160_1_045)*MainFormSLS->hh[105];
c2.v[70] += (sum_160_1_046)*MainFormSLS->hh[86];
c2.v[70] += (sum_160_1_047)*MainFormSLS->hh[67];
c2.v[70] += (sum_160_1_048)*MainFormSLS->hh[48];
c2.v[70] += (sum_160_1_049)*MainFormSLS->hh[29];
c2.v[70] += (sum_160_1_050)*MainFormSLS->hh[10];
c2.v[70] += (sum_160_1_051)*MainFormSLS->hh[151];
c2.v[70] += (sum_160_1_052)*MainFormSLS->hh[132];
c2.v[70] += (sum_160_1_053)*MainFormSLS->hh[113];
c2.v[70] += (sum_160_1_054)*MainFormSLS->hh[94];
c2.v[70] += (sum_160_1_055)*MainFormSLS->hh[75];
c2.v[70] += (sum_160_1_056)*MainFormSLS->hh[56];
c2.v[70] += (sum_160_1_057)*MainFormSLS->hh[37];
c2.v[70] += (sum_160_1_058)*MainFormSLS->hh[18];
c2.v[70] += (sum_160_1_059)*MainFormSLS->hh[159];
c2.v[70] += (sum_160_1_060)*MainFormSLS->hh[140];
c2.v[70] += (sum_160_1_061)*MainFormSLS->hh[121];
c2.v[70] += (sum_160_1_062)*MainFormSLS->hh[102];
c2.v[70] += (sum_160_1_063)*MainFormSLS->hh[83];
c2.v[70] += (sum_160_1_064)*MainFormSLS->hh[64];
c2.v[70] += (sum_160_1_065)*MainFormSLS->hh[45];
c2.v[70] += (sum_160_1_066)*MainFormSLS->hh[26];
c2.v[70] += (sum_160_1_067)*MainFormSLS->hh[7];
c2.v[70] += (sum_160_1_068)*MainFormSLS->hh[148];
c2.v[70] += (sum_160_1_069)*MainFormSLS->hh[129];
c2.v[70] += (sum_160_1_070)*MainFormSLS->hh[110];
c2.v[70] += (sum_160_1_071)*MainFormSLS->hh[91];
c2.v[70] += (sum_160_1_072)*MainFormSLS->hh[72];
c2.v[70] += (sum_160_1_073)*MainFormSLS->hh[53];
c2.v[70] += (sum_160_1_074)*MainFormSLS->hh[34];
c2.v[70] += (sum_160_1_075)*MainFormSLS->hh[15];
c2.v[70] += (sum_160_1_076)*MainFormSLS->hh[156];
c2.v[70] += (sum_160_1_077)*MainFormSLS->hh[137];
c2.v[70] += (sum_160_1_078)*MainFormSLS->hh[118];
c2.v[70] += (sum_160_1_079)*MainFormSLS->hh[99];
c2.v[70] += (sum_160_1_080)*MainFormSLS->hh[80];
c2.v[70] += (sum_160_1_081)*MainFormSLS->hh[61];
c2.v[70] += (sum_160_1_082)*MainFormSLS->hh[42];
c2.v[70] += (sum_160_1_083)*MainFormSLS->hh[23];
c2.v[70] += (sum_160_1_084)*MainFormSLS->hh[4];
c2.v[70] += (sum_160_1_085)*MainFormSLS->hh[145];
c2.v[70] += (sum_160_1_086)*MainFormSLS->hh[126];
c2.v[70] += (sum_160_1_087)*MainFormSLS->hh[107];
c2.v[70] += (sum_160_1_088)*MainFormSLS->hh[88];
c2.v[70] += (sum_160_1_089)*MainFormSLS->hh[69];
c2.v[70] += (sum_160_1_090)*MainFormSLS->hh[50];
c2.v[70] += (sum_160_1_091)*MainFormSLS->hh[31];
c2.v[70] += (sum_160_1_092)*MainFormSLS->hh[12];
c2.v[70] += (sum_160_1_093)*MainFormSLS->hh[153];
c2.v[70] += (sum_160_1_094)*MainFormSLS->hh[134];
c2.v[70] += (sum_160_1_095)*MainFormSLS->hh[115];
c2.v[70] += (sum_160_1_096)*MainFormSLS->hh[96];
c2.v[70] += (sum_160_1_097)*MainFormSLS->hh[77];
c2.v[70] += (sum_160_1_098)*MainFormSLS->hh[58];
c2.v[70] += (sum_160_1_099)*MainFormSLS->hh[39];
c2.v[70] += (sum_160_1_100)*MainFormSLS->hh[20];
c2.v[70] += (sum_160_1_101)*MainFormSLS->hh[1];
c2.v[70] += (sum_160_1_102)*MainFormSLS->hh[142];
c2.v[70] += (sum_160_1_103)*MainFormSLS->hh[123];
c2.v[70] += (sum_160_1_104)*MainFormSLS->hh[104];
c2.v[70] += (sum_160_1_105)*MainFormSLS->hh[85];
c2.v[70] += (sum_160_1_106)*MainFormSLS->hh[66];
c2.v[70] += (sum_160_1_107)*MainFormSLS->hh[47];
c2.v[70] += (sum_160_1_108)*MainFormSLS->hh[28];
c2.v[70] += (sum_160_1_109)*MainFormSLS->hh[9];
c2.v[70] += (sum_160_1_110)*MainFormSLS->hh[150];
c2.v[70] += (sum_160_1_111)*MainFormSLS->hh[131];
c2.v[70] += (sum_160_1_112)*MainFormSLS->hh[112];
c2.v[70] += (sum_160_1_113)*MainFormSLS->hh[93];
c2.v[70] += (sum_160_1_114)*MainFormSLS->hh[74];
c2.v[70] += (sum_160_1_115)*MainFormSLS->hh[55];
c2.v[70] += (sum_160_1_116)*MainFormSLS->hh[36];
c2.v[70] += (sum_160_1_117)*MainFormSLS->hh[17];
c2.v[70] += (sum_160_1_118)*MainFormSLS->hh[158];
c2.v[70] += (sum_160_1_119)*MainFormSLS->hh[139];
c2.v[70] += (sum_160_1_120)*MainFormSLS->hh[120];
c2.v[70] += (sum_160_1_121)*MainFormSLS->hh[101];
c2.v[70] += (sum_160_1_122)*MainFormSLS->hh[82];
c2.v[70] += (sum_160_1_123)*MainFormSLS->hh[63];
c2.v[70] += (sum_160_1_124)*MainFormSLS->hh[44];
c2.v[70] += (sum_160_1_125)*MainFormSLS->hh[25];
c2.v[70] += (sum_160_1_126)*MainFormSLS->hh[6];
c2.v[70] += (sum_160_1_127)*MainFormSLS->hh[147];
c2.v[70] += (sum_160_1_128)*MainFormSLS->hh[128];
c2.v[70] += (sum_160_1_129)*MainFormSLS->hh[109];
c2.v[70] += (sum_160_1_130)*MainFormSLS->hh[90];
c2.v[70] += (sum_160_1_131)*MainFormSLS->hh[71];
c2.v[70] += (sum_160_1_132)*MainFormSLS->hh[52];
c2.v[70] += (sum_160_1_133)*MainFormSLS->hh[33];
c2.v[70] += (sum_160_1_134)*MainFormSLS->hh[14];
c2.v[70] += (sum_160_1_135)*MainFormSLS->hh[155];
c2.v[70] += (sum_160_1_136)*MainFormSLS->hh[136];
c2.v[70] += (sum_160_1_137)*MainFormSLS->hh[117];
c2.v[70] += (sum_160_1_138)*MainFormSLS->hh[98];
c2.v[70] += (sum_160_1_139)*MainFormSLS->hh[79];
c2.v[70] += (sum_160_1_140)*MainFormSLS->hh[60];
c2.v[70] += (sum_160_1_141)*MainFormSLS->hh[41];
c2.v[70] += (sum_160_1_142)*MainFormSLS->hh[22];
c2.v[70] += (sum_160_1_143)*MainFormSLS->hh[3];
c2.v[70] += (sum_160_1_144)*MainFormSLS->hh[144];
c2.v[70] += (sum_160_1_145)*MainFormSLS->hh[125];
c2.v[70] += (sum_160_1_146)*MainFormSLS->hh[106];
c2.v[70] += (sum_160_1_147)*MainFormSLS->hh[87];
c2.v[70] += (sum_160_1_148)*MainFormSLS->hh[68];
c2.v[70] += (sum_160_1_149)*MainFormSLS->hh[49];
c2.v[70] += (sum_160_1_150)*MainFormSLS->hh[30];
c2.v[70] += (sum_160_1_151)*MainFormSLS->hh[11];
c2.v[70] += (sum_160_1_152)*MainFormSLS->hh[152];
c2.v[70] += (sum_160_1_153)*MainFormSLS->hh[133];
c2.v[70] += (sum_160_1_154)*MainFormSLS->hh[114];
c2.v[70] += (sum_160_1_155)*MainFormSLS->hh[95];
c2.v[70] += (sum_160_1_156)*MainFormSLS->hh[76];
c2.v[70] += (sum_160_1_157)*MainFormSLS->hh[57];
c2.v[70] += (sum_160_1_158)*MainFormSLS->hh[38];
c2.v[70] += (sum_160_1_159)*MainFormSLS->hh[19];

//frequency level id 143
c2.v[71] += (sum_160_1_000)*MainFormSLS->hh[0];
c2.v[71] += (sum_160_1_001)*MainFormSLS->hh[143];
c2.v[71] += (sum_160_1_002)*MainFormSLS->hh[126];
c2.v[71] += (sum_160_1_003)*MainFormSLS->hh[109];
c2.v[71] += (sum_160_1_004)*MainFormSLS->hh[92];
c2.v[71] += (sum_160_1_005)*MainFormSLS->hh[75];
c2.v[71] += (sum_160_1_006)*MainFormSLS->hh[58];
c2.v[71] += (sum_160_1_007)*MainFormSLS->hh[41];
c2.v[71] += (sum_160_1_008)*MainFormSLS->hh[24];
c2.v[71] += (sum_160_1_009)*MainFormSLS->hh[7];
c2.v[71] += (sum_160_1_010)*MainFormSLS->hh[150];
c2.v[71] += (sum_160_1_011)*MainFormSLS->hh[133];
c2.v[71] += (sum_160_1_012)*MainFormSLS->hh[116];
c2.v[71] += (sum_160_1_013)*MainFormSLS->hh[99];
c2.v[71] += (sum_160_1_014)*MainFormSLS->hh[82];
c2.v[71] += (sum_160_1_015)*MainFormSLS->hh[65];
c2.v[71] += (sum_160_1_016)*MainFormSLS->hh[48];
c2.v[71] += (sum_160_1_017)*MainFormSLS->hh[31];
c2.v[71] += (sum_160_1_018)*MainFormSLS->hh[14];
c2.v[71] += (sum_160_1_019)*MainFormSLS->hh[157];
c2.v[71] += (sum_160_1_020)*MainFormSLS->hh[140];
c2.v[71] += (sum_160_1_021)*MainFormSLS->hh[123];
c2.v[71] += (sum_160_1_022)*MainFormSLS->hh[106];
c2.v[71] += (sum_160_1_023)*MainFormSLS->hh[89];
c2.v[71] += (sum_160_1_024)*MainFormSLS->hh[72];
c2.v[71] += (sum_160_1_025)*MainFormSLS->hh[55];
c2.v[71] += (sum_160_1_026)*MainFormSLS->hh[38];
c2.v[71] += (sum_160_1_027)*MainFormSLS->hh[21];
c2.v[71] += (sum_160_1_028)*MainFormSLS->hh[4];
c2.v[71] += (sum_160_1_029)*MainFormSLS->hh[147];
c2.v[71] += (sum_160_1_030)*MainFormSLS->hh[130];
c2.v[71] += (sum_160_1_031)*MainFormSLS->hh[113];
c2.v[71] += (sum_160_1_032)*MainFormSLS->hh[96];
c2.v[71] += (sum_160_1_033)*MainFormSLS->hh[79];
c2.v[71] += (sum_160_1_034)*MainFormSLS->hh[62];
c2.v[71] += (sum_160_1_035)*MainFormSLS->hh[45];
c2.v[71] += (sum_160_1_036)*MainFormSLS->hh[28];
c2.v[71] += (sum_160_1_037)*MainFormSLS->hh[11];
c2.v[71] += (sum_160_1_038)*MainFormSLS->hh[154];
c2.v[71] += (sum_160_1_039)*MainFormSLS->hh[137];
c2.v[71] += (sum_160_1_040)*MainFormSLS->hh[120];
c2.v[71] += (sum_160_1_041)*MainFormSLS->hh[103];
c2.v[71] += (sum_160_1_042)*MainFormSLS->hh[86];
c2.v[71] += (sum_160_1_043)*MainFormSLS->hh[69];
c2.v[71] += (sum_160_1_044)*MainFormSLS->hh[52];
c2.v[71] += (sum_160_1_045)*MainFormSLS->hh[35];
c2.v[71] += (sum_160_1_046)*MainFormSLS->hh[18];
c2.v[71] += (sum_160_1_047)*MainFormSLS->hh[1];
c2.v[71] += (sum_160_1_048)*MainFormSLS->hh[144];
c2.v[71] += (sum_160_1_049)*MainFormSLS->hh[127];
c2.v[71] += (sum_160_1_050)*MainFormSLS->hh[110];
c2.v[71] += (sum_160_1_051)*MainFormSLS->hh[93];
c2.v[71] += (sum_160_1_052)*MainFormSLS->hh[76];
c2.v[71] += (sum_160_1_053)*MainFormSLS->hh[59];
c2.v[71] += (sum_160_1_054)*MainFormSLS->hh[42];
c2.v[71] += (sum_160_1_055)*MainFormSLS->hh[25];
c2.v[71] += (sum_160_1_056)*MainFormSLS->hh[8];
c2.v[71] += (sum_160_1_057)*MainFormSLS->hh[151];
c2.v[71] += (sum_160_1_058)*MainFormSLS->hh[134];
c2.v[71] += (sum_160_1_059)*MainFormSLS->hh[117];
c2.v[71] += (sum_160_1_060)*MainFormSLS->hh[100];
c2.v[71] += (sum_160_1_061)*MainFormSLS->hh[83];
c2.v[71] += (sum_160_1_062)*MainFormSLS->hh[66];
c2.v[71] += (sum_160_1_063)*MainFormSLS->hh[49];
c2.v[71] += (sum_160_1_064)*MainFormSLS->hh[32];
c2.v[71] += (sum_160_1_065)*MainFormSLS->hh[15];
c2.v[71] += (sum_160_1_066)*MainFormSLS->hh[158];
c2.v[71] += (sum_160_1_067)*MainFormSLS->hh[141];
c2.v[71] += (sum_160_1_068)*MainFormSLS->hh[124];
c2.v[71] += (sum_160_1_069)*MainFormSLS->hh[107];
c2.v[71] += (sum_160_1_070)*MainFormSLS->hh[90];
c2.v[71] += (sum_160_1_071)*MainFormSLS->hh[73];
c2.v[71] += (sum_160_1_072)*MainFormSLS->hh[56];
c2.v[71] += (sum_160_1_073)*MainFormSLS->hh[39];
c2.v[71] += (sum_160_1_074)*MainFormSLS->hh[22];
c2.v[71] += (sum_160_1_075)*MainFormSLS->hh[5];
c2.v[71] += (sum_160_1_076)*MainFormSLS->hh[148];
c2.v[71] += (sum_160_1_077)*MainFormSLS->hh[131];
c2.v[71] += (sum_160_1_078)*MainFormSLS->hh[114];
c2.v[71] += (sum_160_1_079)*MainFormSLS->hh[97];
c2.v[71] += (sum_160_1_080)*MainFormSLS->hh[80];
c2.v[71] += (sum_160_1_081)*MainFormSLS->hh[63];
c2.v[71] += (sum_160_1_082)*MainFormSLS->hh[46];
c2.v[71] += (sum_160_1_083)*MainFormSLS->hh[29];
c2.v[71] += (sum_160_1_084)*MainFormSLS->hh[12];
c2.v[71] += (sum_160_1_085)*MainFormSLS->hh[155];
c2.v[71] += (sum_160_1_086)*MainFormSLS->hh[138];
c2.v[71] += (sum_160_1_087)*MainFormSLS->hh[121];
c2.v[71] += (sum_160_1_088)*MainFormSLS->hh[104];
c2.v[71] += (sum_160_1_089)*MainFormSLS->hh[87];
c2.v[71] += (sum_160_1_090)*MainFormSLS->hh[70];
c2.v[71] += (sum_160_1_091)*MainFormSLS->hh[53];
c2.v[71] += (sum_160_1_092)*MainFormSLS->hh[36];
c2.v[71] += (sum_160_1_093)*MainFormSLS->hh[19];
c2.v[71] += (sum_160_1_094)*MainFormSLS->hh[2];
c2.v[71] += (sum_160_1_095)*MainFormSLS->hh[145];
c2.v[71] += (sum_160_1_096)*MainFormSLS->hh[128];
c2.v[71] += (sum_160_1_097)*MainFormSLS->hh[111];
c2.v[71] += (sum_160_1_098)*MainFormSLS->hh[94];
c2.v[71] += (sum_160_1_099)*MainFormSLS->hh[77];
c2.v[71] += (sum_160_1_100)*MainFormSLS->hh[60];
c2.v[71] += (sum_160_1_101)*MainFormSLS->hh[43];
c2.v[71] += (sum_160_1_102)*MainFormSLS->hh[26];
c2.v[71] += (sum_160_1_103)*MainFormSLS->hh[9];
c2.v[71] += (sum_160_1_104)*MainFormSLS->hh[152];
c2.v[71] += (sum_160_1_105)*MainFormSLS->hh[135];
c2.v[71] += (sum_160_1_106)*MainFormSLS->hh[118];
c2.v[71] += (sum_160_1_107)*MainFormSLS->hh[101];
c2.v[71] += (sum_160_1_108)*MainFormSLS->hh[84];
c2.v[71] += (sum_160_1_109)*MainFormSLS->hh[67];
c2.v[71] += (sum_160_1_110)*MainFormSLS->hh[50];
c2.v[71] += (sum_160_1_111)*MainFormSLS->hh[33];
c2.v[71] += (sum_160_1_112)*MainFormSLS->hh[16];
c2.v[71] += (sum_160_1_113)*MainFormSLS->hh[159];
c2.v[71] += (sum_160_1_114)*MainFormSLS->hh[142];
c2.v[71] += (sum_160_1_115)*MainFormSLS->hh[125];
c2.v[71] += (sum_160_1_116)*MainFormSLS->hh[108];
c2.v[71] += (sum_160_1_117)*MainFormSLS->hh[91];
c2.v[71] += (sum_160_1_118)*MainFormSLS->hh[74];
c2.v[71] += (sum_160_1_119)*MainFormSLS->hh[57];
c2.v[71] += (sum_160_1_120)*MainFormSLS->hh[40];
c2.v[71] += (sum_160_1_121)*MainFormSLS->hh[23];
c2.v[71] += (sum_160_1_122)*MainFormSLS->hh[6];
c2.v[71] += (sum_160_1_123)*MainFormSLS->hh[149];
c2.v[71] += (sum_160_1_124)*MainFormSLS->hh[132];
c2.v[71] += (sum_160_1_125)*MainFormSLS->hh[115];
c2.v[71] += (sum_160_1_126)*MainFormSLS->hh[98];
c2.v[71] += (sum_160_1_127)*MainFormSLS->hh[81];
c2.v[71] += (sum_160_1_128)*MainFormSLS->hh[64];
c2.v[71] += (sum_160_1_129)*MainFormSLS->hh[47];
c2.v[71] += (sum_160_1_130)*MainFormSLS->hh[30];
c2.v[71] += (sum_160_1_131)*MainFormSLS->hh[13];
c2.v[71] += (sum_160_1_132)*MainFormSLS->hh[156];
c2.v[71] += (sum_160_1_133)*MainFormSLS->hh[139];
c2.v[71] += (sum_160_1_134)*MainFormSLS->hh[122];
c2.v[71] += (sum_160_1_135)*MainFormSLS->hh[105];
c2.v[71] += (sum_160_1_136)*MainFormSLS->hh[88];
c2.v[71] += (sum_160_1_137)*MainFormSLS->hh[71];
c2.v[71] += (sum_160_1_138)*MainFormSLS->hh[54];
c2.v[71] += (sum_160_1_139)*MainFormSLS->hh[37];
c2.v[71] += (sum_160_1_140)*MainFormSLS->hh[20];
c2.v[71] += (sum_160_1_141)*MainFormSLS->hh[3];
c2.v[71] += (sum_160_1_142)*MainFormSLS->hh[146];
c2.v[71] += (sum_160_1_143)*MainFormSLS->hh[129];
c2.v[71] += (sum_160_1_144)*MainFormSLS->hh[112];
c2.v[71] += (sum_160_1_145)*MainFormSLS->hh[95];
c2.v[71] += (sum_160_1_146)*MainFormSLS->hh[78];
c2.v[71] += (sum_160_1_147)*MainFormSLS->hh[61];
c2.v[71] += (sum_160_1_148)*MainFormSLS->hh[44];
c2.v[71] += (sum_160_1_149)*MainFormSLS->hh[27];
c2.v[71] += (sum_160_1_150)*MainFormSLS->hh[10];
c2.v[71] += (sum_160_1_151)*MainFormSLS->hh[153];
c2.v[71] += (sum_160_1_152)*MainFormSLS->hh[136];
c2.v[71] += (sum_160_1_153)*MainFormSLS->hh[119];
c2.v[71] += (sum_160_1_154)*MainFormSLS->hh[102];
c2.v[71] += (sum_160_1_155)*MainFormSLS->hh[85];
c2.v[71] += (sum_160_1_156)*MainFormSLS->hh[68];
c2.v[71] += (sum_160_1_157)*MainFormSLS->hh[51];
c2.v[71] += (sum_160_1_158)*MainFormSLS->hh[34];
c2.v[71] += (sum_160_1_159)*MainFormSLS->hh[17];

//frequency level id 145
c2.v[72] += (sum_32_5_000)*MainFormSLS->hh[0];
c2.v[72] += (sum_32_5_001)*MainFormSLS->hh[145];
c2.v[72] += (sum_32_5_002)*MainFormSLS->hh[130];
c2.v[72] += (sum_32_5_003)*MainFormSLS->hh[115];
c2.v[72] += (sum_32_5_004)*MainFormSLS->hh[100];
c2.v[72] += (sum_32_5_005)*MainFormSLS->hh[85];
c2.v[72] += (sum_32_5_006)*MainFormSLS->hh[70];
c2.v[72] += (sum_32_5_007)*MainFormSLS->hh[55];
c2.v[72] += (sum_32_5_008)*MainFormSLS->hh[40];
c2.v[72] += (sum_32_5_009)*MainFormSLS->hh[25];
c2.v[72] += (sum_32_5_010)*MainFormSLS->hh[10];
c2.v[72] += (sum_32_5_011)*MainFormSLS->hh[155];
c2.v[72] += (sum_32_5_012)*MainFormSLS->hh[140];
c2.v[72] += (sum_32_5_013)*MainFormSLS->hh[125];
c2.v[72] += (sum_32_5_014)*MainFormSLS->hh[110];
c2.v[72] += (sum_32_5_015)*MainFormSLS->hh[95];
c2.v[72] += (sum_32_5_016)*MainFormSLS->hh[80];
c2.v[72] += (sum_32_5_017)*MainFormSLS->hh[65];
c2.v[72] += (sum_32_5_018)*MainFormSLS->hh[50];
c2.v[72] += (sum_32_5_019)*MainFormSLS->hh[35];
c2.v[72] += (sum_32_5_020)*MainFormSLS->hh[20];
c2.v[72] += (sum_32_5_021)*MainFormSLS->hh[5];
c2.v[72] += (sum_32_5_022)*MainFormSLS->hh[150];
c2.v[72] += (sum_32_5_023)*MainFormSLS->hh[135];
c2.v[72] += (sum_32_5_024)*MainFormSLS->hh[120];
c2.v[72] += (sum_32_5_025)*MainFormSLS->hh[105];
c2.v[72] += (sum_32_5_026)*MainFormSLS->hh[90];
c2.v[72] += (sum_32_5_027)*MainFormSLS->hh[75];
c2.v[72] += (sum_32_5_028)*MainFormSLS->hh[60];
c2.v[72] += (sum_32_5_029)*MainFormSLS->hh[45];
c2.v[72] += (sum_32_5_030)*MainFormSLS->hh[30];
c2.v[72] += (sum_32_5_031)*MainFormSLS->hh[15];

//frequency level id 147
c2.v[73] += (sum_160_1_000)*MainFormSLS->hh[0];
c2.v[73] += (sum_160_1_001)*MainFormSLS->hh[147];
c2.v[73] += (sum_160_1_002)*MainFormSLS->hh[134];
c2.v[73] += (sum_160_1_003)*MainFormSLS->hh[121];
c2.v[73] += (sum_160_1_004)*MainFormSLS->hh[108];
c2.v[73] += (sum_160_1_005)*MainFormSLS->hh[95];
c2.v[73] += (sum_160_1_006)*MainFormSLS->hh[82];
c2.v[73] += (sum_160_1_007)*MainFormSLS->hh[69];
c2.v[73] += (sum_160_1_008)*MainFormSLS->hh[56];
c2.v[73] += (sum_160_1_009)*MainFormSLS->hh[43];
c2.v[73] += (sum_160_1_010)*MainFormSLS->hh[30];
c2.v[73] += (sum_160_1_011)*MainFormSLS->hh[17];
c2.v[73] += (sum_160_1_012)*MainFormSLS->hh[4];
c2.v[73] += (sum_160_1_013)*MainFormSLS->hh[151];
c2.v[73] += (sum_160_1_014)*MainFormSLS->hh[138];
c2.v[73] += (sum_160_1_015)*MainFormSLS->hh[125];
c2.v[73] += (sum_160_1_016)*MainFormSLS->hh[112];
c2.v[73] += (sum_160_1_017)*MainFormSLS->hh[99];
c2.v[73] += (sum_160_1_018)*MainFormSLS->hh[86];
c2.v[73] += (sum_160_1_019)*MainFormSLS->hh[73];
c2.v[73] += (sum_160_1_020)*MainFormSLS->hh[60];
c2.v[73] += (sum_160_1_021)*MainFormSLS->hh[47];
c2.v[73] += (sum_160_1_022)*MainFormSLS->hh[34];
c2.v[73] += (sum_160_1_023)*MainFormSLS->hh[21];
c2.v[73] += (sum_160_1_024)*MainFormSLS->hh[8];
c2.v[73] += (sum_160_1_025)*MainFormSLS->hh[155];
c2.v[73] += (sum_160_1_026)*MainFormSLS->hh[142];
c2.v[73] += (sum_160_1_027)*MainFormSLS->hh[129];
c2.v[73] += (sum_160_1_028)*MainFormSLS->hh[116];
c2.v[73] += (sum_160_1_029)*MainFormSLS->hh[103];
c2.v[73] += (sum_160_1_030)*MainFormSLS->hh[90];
c2.v[73] += (sum_160_1_031)*MainFormSLS->hh[77];
c2.v[73] += (sum_160_1_032)*MainFormSLS->hh[64];
c2.v[73] += (sum_160_1_033)*MainFormSLS->hh[51];
c2.v[73] += (sum_160_1_034)*MainFormSLS->hh[38];
c2.v[73] += (sum_160_1_035)*MainFormSLS->hh[25];
c2.v[73] += (sum_160_1_036)*MainFormSLS->hh[12];
c2.v[73] += (sum_160_1_037)*MainFormSLS->hh[159];
c2.v[73] += (sum_160_1_038)*MainFormSLS->hh[146];
c2.v[73] += (sum_160_1_039)*MainFormSLS->hh[133];
c2.v[73] += (sum_160_1_040)*MainFormSLS->hh[120];
c2.v[73] += (sum_160_1_041)*MainFormSLS->hh[107];
c2.v[73] += (sum_160_1_042)*MainFormSLS->hh[94];
c2.v[73] += (sum_160_1_043)*MainFormSLS->hh[81];
c2.v[73] += (sum_160_1_044)*MainFormSLS->hh[68];
c2.v[73] += (sum_160_1_045)*MainFormSLS->hh[55];
c2.v[73] += (sum_160_1_046)*MainFormSLS->hh[42];
c2.v[73] += (sum_160_1_047)*MainFormSLS->hh[29];
c2.v[73] += (sum_160_1_048)*MainFormSLS->hh[16];
c2.v[73] += (sum_160_1_049)*MainFormSLS->hh[3];
c2.v[73] += (sum_160_1_050)*MainFormSLS->hh[150];
c2.v[73] += (sum_160_1_051)*MainFormSLS->hh[137];
c2.v[73] += (sum_160_1_052)*MainFormSLS->hh[124];
c2.v[73] += (sum_160_1_053)*MainFormSLS->hh[111];
c2.v[73] += (sum_160_1_054)*MainFormSLS->hh[98];
c2.v[73] += (sum_160_1_055)*MainFormSLS->hh[85];
c2.v[73] += (sum_160_1_056)*MainFormSLS->hh[72];
c2.v[73] += (sum_160_1_057)*MainFormSLS->hh[59];
c2.v[73] += (sum_160_1_058)*MainFormSLS->hh[46];
c2.v[73] += (sum_160_1_059)*MainFormSLS->hh[33];
c2.v[73] += (sum_160_1_060)*MainFormSLS->hh[20];
c2.v[73] += (sum_160_1_061)*MainFormSLS->hh[7];
c2.v[73] += (sum_160_1_062)*MainFormSLS->hh[154];
c2.v[73] += (sum_160_1_063)*MainFormSLS->hh[141];
c2.v[73] += (sum_160_1_064)*MainFormSLS->hh[128];
c2.v[73] += (sum_160_1_065)*MainFormSLS->hh[115];
c2.v[73] += (sum_160_1_066)*MainFormSLS->hh[102];
c2.v[73] += (sum_160_1_067)*MainFormSLS->hh[89];
c2.v[73] += (sum_160_1_068)*MainFormSLS->hh[76];
c2.v[73] += (sum_160_1_069)*MainFormSLS->hh[63];
c2.v[73] += (sum_160_1_070)*MainFormSLS->hh[50];
c2.v[73] += (sum_160_1_071)*MainFormSLS->hh[37];
c2.v[73] += (sum_160_1_072)*MainFormSLS->hh[24];
c2.v[73] += (sum_160_1_073)*MainFormSLS->hh[11];
c2.v[73] += (sum_160_1_074)*MainFormSLS->hh[158];
c2.v[73] += (sum_160_1_075)*MainFormSLS->hh[145];
c2.v[73] += (sum_160_1_076)*MainFormSLS->hh[132];
c2.v[73] += (sum_160_1_077)*MainFormSLS->hh[119];
c2.v[73] += (sum_160_1_078)*MainFormSLS->hh[106];
c2.v[73] += (sum_160_1_079)*MainFormSLS->hh[93];
c2.v[73] += (sum_160_1_080)*MainFormSLS->hh[80];
c2.v[73] += (sum_160_1_081)*MainFormSLS->hh[67];
c2.v[73] += (sum_160_1_082)*MainFormSLS->hh[54];
c2.v[73] += (sum_160_1_083)*MainFormSLS->hh[41];
c2.v[73] += (sum_160_1_084)*MainFormSLS->hh[28];
c2.v[73] += (sum_160_1_085)*MainFormSLS->hh[15];
c2.v[73] += (sum_160_1_086)*MainFormSLS->hh[2];
c2.v[73] += (sum_160_1_087)*MainFormSLS->hh[149];
c2.v[73] += (sum_160_1_088)*MainFormSLS->hh[136];
c2.v[73] += (sum_160_1_089)*MainFormSLS->hh[123];
c2.v[73] += (sum_160_1_090)*MainFormSLS->hh[110];
c2.v[73] += (sum_160_1_091)*MainFormSLS->hh[97];
c2.v[73] += (sum_160_1_092)*MainFormSLS->hh[84];
c2.v[73] += (sum_160_1_093)*MainFormSLS->hh[71];
c2.v[73] += (sum_160_1_094)*MainFormSLS->hh[58];
c2.v[73] += (sum_160_1_095)*MainFormSLS->hh[45];
c2.v[73] += (sum_160_1_096)*MainFormSLS->hh[32];
c2.v[73] += (sum_160_1_097)*MainFormSLS->hh[19];
c2.v[73] += (sum_160_1_098)*MainFormSLS->hh[6];
c2.v[73] += (sum_160_1_099)*MainFormSLS->hh[153];
c2.v[73] += (sum_160_1_100)*MainFormSLS->hh[140];
c2.v[73] += (sum_160_1_101)*MainFormSLS->hh[127];
c2.v[73] += (sum_160_1_102)*MainFormSLS->hh[114];
c2.v[73] += (sum_160_1_103)*MainFormSLS->hh[101];
c2.v[73] += (sum_160_1_104)*MainFormSLS->hh[88];
c2.v[73] += (sum_160_1_105)*MainFormSLS->hh[75];
c2.v[73] += (sum_160_1_106)*MainFormSLS->hh[62];
c2.v[73] += (sum_160_1_107)*MainFormSLS->hh[49];
c2.v[73] += (sum_160_1_108)*MainFormSLS->hh[36];
c2.v[73] += (sum_160_1_109)*MainFormSLS->hh[23];
c2.v[73] += (sum_160_1_110)*MainFormSLS->hh[10];
c2.v[73] += (sum_160_1_111)*MainFormSLS->hh[157];
c2.v[73] += (sum_160_1_112)*MainFormSLS->hh[144];
c2.v[73] += (sum_160_1_113)*MainFormSLS->hh[131];
c2.v[73] += (sum_160_1_114)*MainFormSLS->hh[118];
c2.v[73] += (sum_160_1_115)*MainFormSLS->hh[105];
c2.v[73] += (sum_160_1_116)*MainFormSLS->hh[92];
c2.v[73] += (sum_160_1_117)*MainFormSLS->hh[79];
c2.v[73] += (sum_160_1_118)*MainFormSLS->hh[66];
c2.v[73] += (sum_160_1_119)*MainFormSLS->hh[53];
c2.v[73] += (sum_160_1_120)*MainFormSLS->hh[40];
c2.v[73] += (sum_160_1_121)*MainFormSLS->hh[27];
c2.v[73] += (sum_160_1_122)*MainFormSLS->hh[14];
c2.v[73] += (sum_160_1_123)*MainFormSLS->hh[1];
c2.v[73] += (sum_160_1_124)*MainFormSLS->hh[148];
c2.v[73] += (sum_160_1_125)*MainFormSLS->hh[135];
c2.v[73] += (sum_160_1_126)*MainFormSLS->hh[122];
c2.v[73] += (sum_160_1_127)*MainFormSLS->hh[109];
c2.v[73] += (sum_160_1_128)*MainFormSLS->hh[96];
c2.v[73] += (sum_160_1_129)*MainFormSLS->hh[83];
c2.v[73] += (sum_160_1_130)*MainFormSLS->hh[70];
c2.v[73] += (sum_160_1_131)*MainFormSLS->hh[57];
c2.v[73] += (sum_160_1_132)*MainFormSLS->hh[44];
c2.v[73] += (sum_160_1_133)*MainFormSLS->hh[31];
c2.v[73] += (sum_160_1_134)*MainFormSLS->hh[18];
c2.v[73] += (sum_160_1_135)*MainFormSLS->hh[5];
c2.v[73] += (sum_160_1_136)*MainFormSLS->hh[152];
c2.v[73] += (sum_160_1_137)*MainFormSLS->hh[139];
c2.v[73] += (sum_160_1_138)*MainFormSLS->hh[126];
c2.v[73] += (sum_160_1_139)*MainFormSLS->hh[113];
c2.v[73] += (sum_160_1_140)*MainFormSLS->hh[100];
c2.v[73] += (sum_160_1_141)*MainFormSLS->hh[87];
c2.v[73] += (sum_160_1_142)*MainFormSLS->hh[74];
c2.v[73] += (sum_160_1_143)*MainFormSLS->hh[61];
c2.v[73] += (sum_160_1_144)*MainFormSLS->hh[48];
c2.v[73] += (sum_160_1_145)*MainFormSLS->hh[35];
c2.v[73] += (sum_160_1_146)*MainFormSLS->hh[22];
c2.v[73] += (sum_160_1_147)*MainFormSLS->hh[9];
c2.v[73] += (sum_160_1_148)*MainFormSLS->hh[156];
c2.v[73] += (sum_160_1_149)*MainFormSLS->hh[143];
c2.v[73] += (sum_160_1_150)*MainFormSLS->hh[130];
c2.v[73] += (sum_160_1_151)*MainFormSLS->hh[117];
c2.v[73] += (sum_160_1_152)*MainFormSLS->hh[104];
c2.v[73] += (sum_160_1_153)*MainFormSLS->hh[91];
c2.v[73] += (sum_160_1_154)*MainFormSLS->hh[78];
c2.v[73] += (sum_160_1_155)*MainFormSLS->hh[65];
c2.v[73] += (sum_160_1_156)*MainFormSLS->hh[52];
c2.v[73] += (sum_160_1_157)*MainFormSLS->hh[39];
c2.v[73] += (sum_160_1_158)*MainFormSLS->hh[26];
c2.v[73] += (sum_160_1_159)*MainFormSLS->hh[13];

//frequency level id 149
c2.v[74] += (sum_160_1_000)*MainFormSLS->hh[0];
c2.v[74] += (sum_160_1_001)*MainFormSLS->hh[149];
c2.v[74] += (sum_160_1_002)*MainFormSLS->hh[138];
c2.v[74] += (sum_160_1_003)*MainFormSLS->hh[127];
c2.v[74] += (sum_160_1_004)*MainFormSLS->hh[116];
c2.v[74] += (sum_160_1_005)*MainFormSLS->hh[105];
c2.v[74] += (sum_160_1_006)*MainFormSLS->hh[94];
c2.v[74] += (sum_160_1_007)*MainFormSLS->hh[83];
c2.v[74] += (sum_160_1_008)*MainFormSLS->hh[72];
c2.v[74] += (sum_160_1_009)*MainFormSLS->hh[61];
c2.v[74] += (sum_160_1_010)*MainFormSLS->hh[50];
c2.v[74] += (sum_160_1_011)*MainFormSLS->hh[39];
c2.v[74] += (sum_160_1_012)*MainFormSLS->hh[28];
c2.v[74] += (sum_160_1_013)*MainFormSLS->hh[17];
c2.v[74] += (sum_160_1_014)*MainFormSLS->hh[6];
c2.v[74] += (sum_160_1_015)*MainFormSLS->hh[155];
c2.v[74] += (sum_160_1_016)*MainFormSLS->hh[144];
c2.v[74] += (sum_160_1_017)*MainFormSLS->hh[133];
c2.v[74] += (sum_160_1_018)*MainFormSLS->hh[122];
c2.v[74] += (sum_160_1_019)*MainFormSLS->hh[111];
c2.v[74] += (sum_160_1_020)*MainFormSLS->hh[100];
c2.v[74] += (sum_160_1_021)*MainFormSLS->hh[89];
c2.v[74] += (sum_160_1_022)*MainFormSLS->hh[78];
c2.v[74] += (sum_160_1_023)*MainFormSLS->hh[67];
c2.v[74] += (sum_160_1_024)*MainFormSLS->hh[56];
c2.v[74] += (sum_160_1_025)*MainFormSLS->hh[45];
c2.v[74] += (sum_160_1_026)*MainFormSLS->hh[34];
c2.v[74] += (sum_160_1_027)*MainFormSLS->hh[23];
c2.v[74] += (sum_160_1_028)*MainFormSLS->hh[12];
c2.v[74] += (sum_160_1_029)*MainFormSLS->hh[1];
c2.v[74] += (sum_160_1_030)*MainFormSLS->hh[150];
c2.v[74] += (sum_160_1_031)*MainFormSLS->hh[139];
c2.v[74] += (sum_160_1_032)*MainFormSLS->hh[128];
c2.v[74] += (sum_160_1_033)*MainFormSLS->hh[117];
c2.v[74] += (sum_160_1_034)*MainFormSLS->hh[106];
c2.v[74] += (sum_160_1_035)*MainFormSLS->hh[95];
c2.v[74] += (sum_160_1_036)*MainFormSLS->hh[84];
c2.v[74] += (sum_160_1_037)*MainFormSLS->hh[73];
c2.v[74] += (sum_160_1_038)*MainFormSLS->hh[62];
c2.v[74] += (sum_160_1_039)*MainFormSLS->hh[51];
c2.v[74] += (sum_160_1_040)*MainFormSLS->hh[40];
c2.v[74] += (sum_160_1_041)*MainFormSLS->hh[29];
c2.v[74] += (sum_160_1_042)*MainFormSLS->hh[18];
c2.v[74] += (sum_160_1_043)*MainFormSLS->hh[7];
c2.v[74] += (sum_160_1_044)*MainFormSLS->hh[156];
c2.v[74] += (sum_160_1_045)*MainFormSLS->hh[145];
c2.v[74] += (sum_160_1_046)*MainFormSLS->hh[134];
c2.v[74] += (sum_160_1_047)*MainFormSLS->hh[123];
c2.v[74] += (sum_160_1_048)*MainFormSLS->hh[112];
c2.v[74] += (sum_160_1_049)*MainFormSLS->hh[101];
c2.v[74] += (sum_160_1_050)*MainFormSLS->hh[90];
c2.v[74] += (sum_160_1_051)*MainFormSLS->hh[79];
c2.v[74] += (sum_160_1_052)*MainFormSLS->hh[68];
c2.v[74] += (sum_160_1_053)*MainFormSLS->hh[57];
c2.v[74] += (sum_160_1_054)*MainFormSLS->hh[46];
c2.v[74] += (sum_160_1_055)*MainFormSLS->hh[35];
c2.v[74] += (sum_160_1_056)*MainFormSLS->hh[24];
c2.v[74] += (sum_160_1_057)*MainFormSLS->hh[13];
c2.v[74] += (sum_160_1_058)*MainFormSLS->hh[2];
c2.v[74] += (sum_160_1_059)*MainFormSLS->hh[151];
c2.v[74] += (sum_160_1_060)*MainFormSLS->hh[140];
c2.v[74] += (sum_160_1_061)*MainFormSLS->hh[129];
c2.v[74] += (sum_160_1_062)*MainFormSLS->hh[118];
c2.v[74] += (sum_160_1_063)*MainFormSLS->hh[107];
c2.v[74] += (sum_160_1_064)*MainFormSLS->hh[96];
c2.v[74] += (sum_160_1_065)*MainFormSLS->hh[85];
c2.v[74] += (sum_160_1_066)*MainFormSLS->hh[74];
c2.v[74] += (sum_160_1_067)*MainFormSLS->hh[63];
c2.v[74] += (sum_160_1_068)*MainFormSLS->hh[52];
c2.v[74] += (sum_160_1_069)*MainFormSLS->hh[41];
c2.v[74] += (sum_160_1_070)*MainFormSLS->hh[30];
c2.v[74] += (sum_160_1_071)*MainFormSLS->hh[19];
c2.v[74] += (sum_160_1_072)*MainFormSLS->hh[8];
c2.v[74] += (sum_160_1_073)*MainFormSLS->hh[157];
c2.v[74] += (sum_160_1_074)*MainFormSLS->hh[146];
c2.v[74] += (sum_160_1_075)*MainFormSLS->hh[135];
c2.v[74] += (sum_160_1_076)*MainFormSLS->hh[124];
c2.v[74] += (sum_160_1_077)*MainFormSLS->hh[113];
c2.v[74] += (sum_160_1_078)*MainFormSLS->hh[102];
c2.v[74] += (sum_160_1_079)*MainFormSLS->hh[91];
c2.v[74] += (sum_160_1_080)*MainFormSLS->hh[80];
c2.v[74] += (sum_160_1_081)*MainFormSLS->hh[69];
c2.v[74] += (sum_160_1_082)*MainFormSLS->hh[58];
c2.v[74] += (sum_160_1_083)*MainFormSLS->hh[47];
c2.v[74] += (sum_160_1_084)*MainFormSLS->hh[36];
c2.v[74] += (sum_160_1_085)*MainFormSLS->hh[25];
c2.v[74] += (sum_160_1_086)*MainFormSLS->hh[14];
c2.v[74] += (sum_160_1_087)*MainFormSLS->hh[3];
c2.v[74] += (sum_160_1_088)*MainFormSLS->hh[152];
c2.v[74] += (sum_160_1_089)*MainFormSLS->hh[141];
c2.v[74] += (sum_160_1_090)*MainFormSLS->hh[130];
c2.v[74] += (sum_160_1_091)*MainFormSLS->hh[119];
c2.v[74] += (sum_160_1_092)*MainFormSLS->hh[108];
c2.v[74] += (sum_160_1_093)*MainFormSLS->hh[97];
c2.v[74] += (sum_160_1_094)*MainFormSLS->hh[86];
c2.v[74] += (sum_160_1_095)*MainFormSLS->hh[75];
c2.v[74] += (sum_160_1_096)*MainFormSLS->hh[64];
c2.v[74] += (sum_160_1_097)*MainFormSLS->hh[53];
c2.v[74] += (sum_160_1_098)*MainFormSLS->hh[42];
c2.v[74] += (sum_160_1_099)*MainFormSLS->hh[31];
c2.v[74] += (sum_160_1_100)*MainFormSLS->hh[20];
c2.v[74] += (sum_160_1_101)*MainFormSLS->hh[9];
c2.v[74] += (sum_160_1_102)*MainFormSLS->hh[158];
c2.v[74] += (sum_160_1_103)*MainFormSLS->hh[147];
c2.v[74] += (sum_160_1_104)*MainFormSLS->hh[136];
c2.v[74] += (sum_160_1_105)*MainFormSLS->hh[125];
c2.v[74] += (sum_160_1_106)*MainFormSLS->hh[114];
c2.v[74] += (sum_160_1_107)*MainFormSLS->hh[103];
c2.v[74] += (sum_160_1_108)*MainFormSLS->hh[92];
c2.v[74] += (sum_160_1_109)*MainFormSLS->hh[81];
c2.v[74] += (sum_160_1_110)*MainFormSLS->hh[70];
c2.v[74] += (sum_160_1_111)*MainFormSLS->hh[59];
c2.v[74] += (sum_160_1_112)*MainFormSLS->hh[48];
c2.v[74] += (sum_160_1_113)*MainFormSLS->hh[37];
c2.v[74] += (sum_160_1_114)*MainFormSLS->hh[26];
c2.v[74] += (sum_160_1_115)*MainFormSLS->hh[15];
c2.v[74] += (sum_160_1_116)*MainFormSLS->hh[4];
c2.v[74] += (sum_160_1_117)*MainFormSLS->hh[153];
c2.v[74] += (sum_160_1_118)*MainFormSLS->hh[142];
c2.v[74] += (sum_160_1_119)*MainFormSLS->hh[131];
c2.v[74] += (sum_160_1_120)*MainFormSLS->hh[120];
c2.v[74] += (sum_160_1_121)*MainFormSLS->hh[109];
c2.v[74] += (sum_160_1_122)*MainFormSLS->hh[98];
c2.v[74] += (sum_160_1_123)*MainFormSLS->hh[87];
c2.v[74] += (sum_160_1_124)*MainFormSLS->hh[76];
c2.v[74] += (sum_160_1_125)*MainFormSLS->hh[65];
c2.v[74] += (sum_160_1_126)*MainFormSLS->hh[54];
c2.v[74] += (sum_160_1_127)*MainFormSLS->hh[43];
c2.v[74] += (sum_160_1_128)*MainFormSLS->hh[32];
c2.v[74] += (sum_160_1_129)*MainFormSLS->hh[21];
c2.v[74] += (sum_160_1_130)*MainFormSLS->hh[10];
c2.v[74] += (sum_160_1_131)*MainFormSLS->hh[159];
c2.v[74] += (sum_160_1_132)*MainFormSLS->hh[148];
c2.v[74] += (sum_160_1_133)*MainFormSLS->hh[137];
c2.v[74] += (sum_160_1_134)*MainFormSLS->hh[126];
c2.v[74] += (sum_160_1_135)*MainFormSLS->hh[115];
c2.v[74] += (sum_160_1_136)*MainFormSLS->hh[104];
c2.v[74] += (sum_160_1_137)*MainFormSLS->hh[93];
c2.v[74] += (sum_160_1_138)*MainFormSLS->hh[82];
c2.v[74] += (sum_160_1_139)*MainFormSLS->hh[71];
c2.v[74] += (sum_160_1_140)*MainFormSLS->hh[60];
c2.v[74] += (sum_160_1_141)*MainFormSLS->hh[49];
c2.v[74] += (sum_160_1_142)*MainFormSLS->hh[38];
c2.v[74] += (sum_160_1_143)*MainFormSLS->hh[27];
c2.v[74] += (sum_160_1_144)*MainFormSLS->hh[16];
c2.v[74] += (sum_160_1_145)*MainFormSLS->hh[5];
c2.v[74] += (sum_160_1_146)*MainFormSLS->hh[154];
c2.v[74] += (sum_160_1_147)*MainFormSLS->hh[143];
c2.v[74] += (sum_160_1_148)*MainFormSLS->hh[132];
c2.v[74] += (sum_160_1_149)*MainFormSLS->hh[121];
c2.v[74] += (sum_160_1_150)*MainFormSLS->hh[110];
c2.v[74] += (sum_160_1_151)*MainFormSLS->hh[99];
c2.v[74] += (sum_160_1_152)*MainFormSLS->hh[88];
c2.v[74] += (sum_160_1_153)*MainFormSLS->hh[77];
c2.v[74] += (sum_160_1_154)*MainFormSLS->hh[66];
c2.v[74] += (sum_160_1_155)*MainFormSLS->hh[55];
c2.v[74] += (sum_160_1_156)*MainFormSLS->hh[44];
c2.v[74] += (sum_160_1_157)*MainFormSLS->hh[33];
c2.v[74] += (sum_160_1_158)*MainFormSLS->hh[22];
c2.v[74] += (sum_160_1_159)*MainFormSLS->hh[11];

//frequency level id 151
c2.v[75] += (sum_160_1_000)*MainFormSLS->hh[0];
c2.v[75] += (sum_160_1_001)*MainFormSLS->hh[151];
c2.v[75] += (sum_160_1_002)*MainFormSLS->hh[142];
c2.v[75] += (sum_160_1_003)*MainFormSLS->hh[133];
c2.v[75] += (sum_160_1_004)*MainFormSLS->hh[124];
c2.v[75] += (sum_160_1_005)*MainFormSLS->hh[115];
c2.v[75] += (sum_160_1_006)*MainFormSLS->hh[106];
c2.v[75] += (sum_160_1_007)*MainFormSLS->hh[97];
c2.v[75] += (sum_160_1_008)*MainFormSLS->hh[88];
c2.v[75] += (sum_160_1_009)*MainFormSLS->hh[79];
c2.v[75] += (sum_160_1_010)*MainFormSLS->hh[70];
c2.v[75] += (sum_160_1_011)*MainFormSLS->hh[61];
c2.v[75] += (sum_160_1_012)*MainFormSLS->hh[52];
c2.v[75] += (sum_160_1_013)*MainFormSLS->hh[43];
c2.v[75] += (sum_160_1_014)*MainFormSLS->hh[34];
c2.v[75] += (sum_160_1_015)*MainFormSLS->hh[25];
c2.v[75] += (sum_160_1_016)*MainFormSLS->hh[16];
c2.v[75] += (sum_160_1_017)*MainFormSLS->hh[7];
c2.v[75] += (sum_160_1_018)*MainFormSLS->hh[158];
c2.v[75] += (sum_160_1_019)*MainFormSLS->hh[149];
c2.v[75] += (sum_160_1_020)*MainFormSLS->hh[140];
c2.v[75] += (sum_160_1_021)*MainFormSLS->hh[131];
c2.v[75] += (sum_160_1_022)*MainFormSLS->hh[122];
c2.v[75] += (sum_160_1_023)*MainFormSLS->hh[113];
c2.v[75] += (sum_160_1_024)*MainFormSLS->hh[104];
c2.v[75] += (sum_160_1_025)*MainFormSLS->hh[95];
c2.v[75] += (sum_160_1_026)*MainFormSLS->hh[86];
c2.v[75] += (sum_160_1_027)*MainFormSLS->hh[77];
c2.v[75] += (sum_160_1_028)*MainFormSLS->hh[68];
c2.v[75] += (sum_160_1_029)*MainFormSLS->hh[59];
c2.v[75] += (sum_160_1_030)*MainFormSLS->hh[50];
c2.v[75] += (sum_160_1_031)*MainFormSLS->hh[41];
c2.v[75] += (sum_160_1_032)*MainFormSLS->hh[32];
c2.v[75] += (sum_160_1_033)*MainFormSLS->hh[23];
c2.v[75] += (sum_160_1_034)*MainFormSLS->hh[14];
c2.v[75] += (sum_160_1_035)*MainFormSLS->hh[5];
c2.v[75] += (sum_160_1_036)*MainFormSLS->hh[156];
c2.v[75] += (sum_160_1_037)*MainFormSLS->hh[147];
c2.v[75] += (sum_160_1_038)*MainFormSLS->hh[138];
c2.v[75] += (sum_160_1_039)*MainFormSLS->hh[129];
c2.v[75] += (sum_160_1_040)*MainFormSLS->hh[120];
c2.v[75] += (sum_160_1_041)*MainFormSLS->hh[111];
c2.v[75] += (sum_160_1_042)*MainFormSLS->hh[102];
c2.v[75] += (sum_160_1_043)*MainFormSLS->hh[93];
c2.v[75] += (sum_160_1_044)*MainFormSLS->hh[84];
c2.v[75] += (sum_160_1_045)*MainFormSLS->hh[75];
c2.v[75] += (sum_160_1_046)*MainFormSLS->hh[66];
c2.v[75] += (sum_160_1_047)*MainFormSLS->hh[57];
c2.v[75] += (sum_160_1_048)*MainFormSLS->hh[48];
c2.v[75] += (sum_160_1_049)*MainFormSLS->hh[39];
c2.v[75] += (sum_160_1_050)*MainFormSLS->hh[30];
c2.v[75] += (sum_160_1_051)*MainFormSLS->hh[21];
c2.v[75] += (sum_160_1_052)*MainFormSLS->hh[12];
c2.v[75] += (sum_160_1_053)*MainFormSLS->hh[3];
c2.v[75] += (sum_160_1_054)*MainFormSLS->hh[154];
c2.v[75] += (sum_160_1_055)*MainFormSLS->hh[145];
c2.v[75] += (sum_160_1_056)*MainFormSLS->hh[136];
c2.v[75] += (sum_160_1_057)*MainFormSLS->hh[127];
c2.v[75] += (sum_160_1_058)*MainFormSLS->hh[118];
c2.v[75] += (sum_160_1_059)*MainFormSLS->hh[109];
c2.v[75] += (sum_160_1_060)*MainFormSLS->hh[100];
c2.v[75] += (sum_160_1_061)*MainFormSLS->hh[91];
c2.v[75] += (sum_160_1_062)*MainFormSLS->hh[82];
c2.v[75] += (sum_160_1_063)*MainFormSLS->hh[73];
c2.v[75] += (sum_160_1_064)*MainFormSLS->hh[64];
c2.v[75] += (sum_160_1_065)*MainFormSLS->hh[55];
c2.v[75] += (sum_160_1_066)*MainFormSLS->hh[46];
c2.v[75] += (sum_160_1_067)*MainFormSLS->hh[37];
c2.v[75] += (sum_160_1_068)*MainFormSLS->hh[28];
c2.v[75] += (sum_160_1_069)*MainFormSLS->hh[19];
c2.v[75] += (sum_160_1_070)*MainFormSLS->hh[10];
c2.v[75] += (sum_160_1_071)*MainFormSLS->hh[1];
c2.v[75] += (sum_160_1_072)*MainFormSLS->hh[152];
c2.v[75] += (sum_160_1_073)*MainFormSLS->hh[143];
c2.v[75] += (sum_160_1_074)*MainFormSLS->hh[134];
c2.v[75] += (sum_160_1_075)*MainFormSLS->hh[125];
c2.v[75] += (sum_160_1_076)*MainFormSLS->hh[116];
c2.v[75] += (sum_160_1_077)*MainFormSLS->hh[107];
c2.v[75] += (sum_160_1_078)*MainFormSLS->hh[98];
c2.v[75] += (sum_160_1_079)*MainFormSLS->hh[89];
c2.v[75] += (sum_160_1_080)*MainFormSLS->hh[80];
c2.v[75] += (sum_160_1_081)*MainFormSLS->hh[71];
c2.v[75] += (sum_160_1_082)*MainFormSLS->hh[62];
c2.v[75] += (sum_160_1_083)*MainFormSLS->hh[53];
c2.v[75] += (sum_160_1_084)*MainFormSLS->hh[44];
c2.v[75] += (sum_160_1_085)*MainFormSLS->hh[35];
c2.v[75] += (sum_160_1_086)*MainFormSLS->hh[26];
c2.v[75] += (sum_160_1_087)*MainFormSLS->hh[17];
c2.v[75] += (sum_160_1_088)*MainFormSLS->hh[8];
c2.v[75] += (sum_160_1_089)*MainFormSLS->hh[159];
c2.v[75] += (sum_160_1_090)*MainFormSLS->hh[150];
c2.v[75] += (sum_160_1_091)*MainFormSLS->hh[141];
c2.v[75] += (sum_160_1_092)*MainFormSLS->hh[132];
c2.v[75] += (sum_160_1_093)*MainFormSLS->hh[123];
c2.v[75] += (sum_160_1_094)*MainFormSLS->hh[114];
c2.v[75] += (sum_160_1_095)*MainFormSLS->hh[105];
c2.v[75] += (sum_160_1_096)*MainFormSLS->hh[96];
c2.v[75] += (sum_160_1_097)*MainFormSLS->hh[87];
c2.v[75] += (sum_160_1_098)*MainFormSLS->hh[78];
c2.v[75] += (sum_160_1_099)*MainFormSLS->hh[69];
c2.v[75] += (sum_160_1_100)*MainFormSLS->hh[60];
c2.v[75] += (sum_160_1_101)*MainFormSLS->hh[51];
c2.v[75] += (sum_160_1_102)*MainFormSLS->hh[42];
c2.v[75] += (sum_160_1_103)*MainFormSLS->hh[33];
c2.v[75] += (sum_160_1_104)*MainFormSLS->hh[24];
c2.v[75] += (sum_160_1_105)*MainFormSLS->hh[15];
c2.v[75] += (sum_160_1_106)*MainFormSLS->hh[6];
c2.v[75] += (sum_160_1_107)*MainFormSLS->hh[157];
c2.v[75] += (sum_160_1_108)*MainFormSLS->hh[148];
c2.v[75] += (sum_160_1_109)*MainFormSLS->hh[139];
c2.v[75] += (sum_160_1_110)*MainFormSLS->hh[130];
c2.v[75] += (sum_160_1_111)*MainFormSLS->hh[121];
c2.v[75] += (sum_160_1_112)*MainFormSLS->hh[112];
c2.v[75] += (sum_160_1_113)*MainFormSLS->hh[103];
c2.v[75] += (sum_160_1_114)*MainFormSLS->hh[94];
c2.v[75] += (sum_160_1_115)*MainFormSLS->hh[85];
c2.v[75] += (sum_160_1_116)*MainFormSLS->hh[76];
c2.v[75] += (sum_160_1_117)*MainFormSLS->hh[67];
c2.v[75] += (sum_160_1_118)*MainFormSLS->hh[58];
c2.v[75] += (sum_160_1_119)*MainFormSLS->hh[49];
c2.v[75] += (sum_160_1_120)*MainFormSLS->hh[40];
c2.v[75] += (sum_160_1_121)*MainFormSLS->hh[31];
c2.v[75] += (sum_160_1_122)*MainFormSLS->hh[22];
c2.v[75] += (sum_160_1_123)*MainFormSLS->hh[13];
c2.v[75] += (sum_160_1_124)*MainFormSLS->hh[4];
c2.v[75] += (sum_160_1_125)*MainFormSLS->hh[155];
c2.v[75] += (sum_160_1_126)*MainFormSLS->hh[146];
c2.v[75] += (sum_160_1_127)*MainFormSLS->hh[137];
c2.v[75] += (sum_160_1_128)*MainFormSLS->hh[128];
c2.v[75] += (sum_160_1_129)*MainFormSLS->hh[119];
c2.v[75] += (sum_160_1_130)*MainFormSLS->hh[110];
c2.v[75] += (sum_160_1_131)*MainFormSLS->hh[101];
c2.v[75] += (sum_160_1_132)*MainFormSLS->hh[92];
c2.v[75] += (sum_160_1_133)*MainFormSLS->hh[83];
c2.v[75] += (sum_160_1_134)*MainFormSLS->hh[74];
c2.v[75] += (sum_160_1_135)*MainFormSLS->hh[65];
c2.v[75] += (sum_160_1_136)*MainFormSLS->hh[56];
c2.v[75] += (sum_160_1_137)*MainFormSLS->hh[47];
c2.v[75] += (sum_160_1_138)*MainFormSLS->hh[38];
c2.v[75] += (sum_160_1_139)*MainFormSLS->hh[29];
c2.v[75] += (sum_160_1_140)*MainFormSLS->hh[20];
c2.v[75] += (sum_160_1_141)*MainFormSLS->hh[11];
c2.v[75] += (sum_160_1_142)*MainFormSLS->hh[2];
c2.v[75] += (sum_160_1_143)*MainFormSLS->hh[153];
c2.v[75] += (sum_160_1_144)*MainFormSLS->hh[144];
c2.v[75] += (sum_160_1_145)*MainFormSLS->hh[135];
c2.v[75] += (sum_160_1_146)*MainFormSLS->hh[126];
c2.v[75] += (sum_160_1_147)*MainFormSLS->hh[117];
c2.v[75] += (sum_160_1_148)*MainFormSLS->hh[108];
c2.v[75] += (sum_160_1_149)*MainFormSLS->hh[99];
c2.v[75] += (sum_160_1_150)*MainFormSLS->hh[90];
c2.v[75] += (sum_160_1_151)*MainFormSLS->hh[81];
c2.v[75] += (sum_160_1_152)*MainFormSLS->hh[72];
c2.v[75] += (sum_160_1_153)*MainFormSLS->hh[63];
c2.v[75] += (sum_160_1_154)*MainFormSLS->hh[54];
c2.v[75] += (sum_160_1_155)*MainFormSLS->hh[45];
c2.v[75] += (sum_160_1_156)*MainFormSLS->hh[36];
c2.v[75] += (sum_160_1_157)*MainFormSLS->hh[27];
c2.v[75] += (sum_160_1_158)*MainFormSLS->hh[18];
c2.v[75] += (sum_160_1_159)*MainFormSLS->hh[9];

//frequency level id 153
c2.v[76] += (sum_160_1_000)*MainFormSLS->hh[0];
c2.v[76] += (sum_160_1_001)*MainFormSLS->hh[153];
c2.v[76] += (sum_160_1_002)*MainFormSLS->hh[146];
c2.v[76] += (sum_160_1_003)*MainFormSLS->hh[139];
c2.v[76] += (sum_160_1_004)*MainFormSLS->hh[132];
c2.v[76] += (sum_160_1_005)*MainFormSLS->hh[125];
c2.v[76] += (sum_160_1_006)*MainFormSLS->hh[118];
c2.v[76] += (sum_160_1_007)*MainFormSLS->hh[111];
c2.v[76] += (sum_160_1_008)*MainFormSLS->hh[104];
c2.v[76] += (sum_160_1_009)*MainFormSLS->hh[97];
c2.v[76] += (sum_160_1_010)*MainFormSLS->hh[90];
c2.v[76] += (sum_160_1_011)*MainFormSLS->hh[83];
c2.v[76] += (sum_160_1_012)*MainFormSLS->hh[76];
c2.v[76] += (sum_160_1_013)*MainFormSLS->hh[69];
c2.v[76] += (sum_160_1_014)*MainFormSLS->hh[62];
c2.v[76] += (sum_160_1_015)*MainFormSLS->hh[55];
c2.v[76] += (sum_160_1_016)*MainFormSLS->hh[48];
c2.v[76] += (sum_160_1_017)*MainFormSLS->hh[41];
c2.v[76] += (sum_160_1_018)*MainFormSLS->hh[34];
c2.v[76] += (sum_160_1_019)*MainFormSLS->hh[27];
c2.v[76] += (sum_160_1_020)*MainFormSLS->hh[20];
c2.v[76] += (sum_160_1_021)*MainFormSLS->hh[13];
c2.v[76] += (sum_160_1_022)*MainFormSLS->hh[6];
c2.v[76] += (sum_160_1_023)*MainFormSLS->hh[159];
c2.v[76] += (sum_160_1_024)*MainFormSLS->hh[152];
c2.v[76] += (sum_160_1_025)*MainFormSLS->hh[145];
c2.v[76] += (sum_160_1_026)*MainFormSLS->hh[138];
c2.v[76] += (sum_160_1_027)*MainFormSLS->hh[131];
c2.v[76] += (sum_160_1_028)*MainFormSLS->hh[124];
c2.v[76] += (sum_160_1_029)*MainFormSLS->hh[117];
c2.v[76] += (sum_160_1_030)*MainFormSLS->hh[110];
c2.v[76] += (sum_160_1_031)*MainFormSLS->hh[103];
c2.v[76] += (sum_160_1_032)*MainFormSLS->hh[96];
c2.v[76] += (sum_160_1_033)*MainFormSLS->hh[89];
c2.v[76] += (sum_160_1_034)*MainFormSLS->hh[82];
c2.v[76] += (sum_160_1_035)*MainFormSLS->hh[75];
c2.v[76] += (sum_160_1_036)*MainFormSLS->hh[68];
c2.v[76] += (sum_160_1_037)*MainFormSLS->hh[61];
c2.v[76] += (sum_160_1_038)*MainFormSLS->hh[54];
c2.v[76] += (sum_160_1_039)*MainFormSLS->hh[47];
c2.v[76] += (sum_160_1_040)*MainFormSLS->hh[40];
c2.v[76] += (sum_160_1_041)*MainFormSLS->hh[33];
c2.v[76] += (sum_160_1_042)*MainFormSLS->hh[26];
c2.v[76] += (sum_160_1_043)*MainFormSLS->hh[19];
c2.v[76] += (sum_160_1_044)*MainFormSLS->hh[12];
c2.v[76] += (sum_160_1_045)*MainFormSLS->hh[5];
c2.v[76] += (sum_160_1_046)*MainFormSLS->hh[158];
c2.v[76] += (sum_160_1_047)*MainFormSLS->hh[151];
c2.v[76] += (sum_160_1_048)*MainFormSLS->hh[144];
c2.v[76] += (sum_160_1_049)*MainFormSLS->hh[137];
c2.v[76] += (sum_160_1_050)*MainFormSLS->hh[130];
c2.v[76] += (sum_160_1_051)*MainFormSLS->hh[123];
c2.v[76] += (sum_160_1_052)*MainFormSLS->hh[116];
c2.v[76] += (sum_160_1_053)*MainFormSLS->hh[109];
c2.v[76] += (sum_160_1_054)*MainFormSLS->hh[102];
c2.v[76] += (sum_160_1_055)*MainFormSLS->hh[95];
c2.v[76] += (sum_160_1_056)*MainFormSLS->hh[88];
c2.v[76] += (sum_160_1_057)*MainFormSLS->hh[81];
c2.v[76] += (sum_160_1_058)*MainFormSLS->hh[74];
c2.v[76] += (sum_160_1_059)*MainFormSLS->hh[67];
c2.v[76] += (sum_160_1_060)*MainFormSLS->hh[60];
c2.v[76] += (sum_160_1_061)*MainFormSLS->hh[53];
c2.v[76] += (sum_160_1_062)*MainFormSLS->hh[46];
c2.v[76] += (sum_160_1_063)*MainFormSLS->hh[39];
c2.v[76] += (sum_160_1_064)*MainFormSLS->hh[32];
c2.v[76] += (sum_160_1_065)*MainFormSLS->hh[25];
c2.v[76] += (sum_160_1_066)*MainFormSLS->hh[18];
c2.v[76] += (sum_160_1_067)*MainFormSLS->hh[11];
c2.v[76] += (sum_160_1_068)*MainFormSLS->hh[4];
c2.v[76] += (sum_160_1_069)*MainFormSLS->hh[157];
c2.v[76] += (sum_160_1_070)*MainFormSLS->hh[150];
c2.v[76] += (sum_160_1_071)*MainFormSLS->hh[143];
c2.v[76] += (sum_160_1_072)*MainFormSLS->hh[136];
c2.v[76] += (sum_160_1_073)*MainFormSLS->hh[129];
c2.v[76] += (sum_160_1_074)*MainFormSLS->hh[122];
c2.v[76] += (sum_160_1_075)*MainFormSLS->hh[115];
c2.v[76] += (sum_160_1_076)*MainFormSLS->hh[108];
c2.v[76] += (sum_160_1_077)*MainFormSLS->hh[101];
c2.v[76] += (sum_160_1_078)*MainFormSLS->hh[94];
c2.v[76] += (sum_160_1_079)*MainFormSLS->hh[87];
c2.v[76] += (sum_160_1_080)*MainFormSLS->hh[80];
c2.v[76] += (sum_160_1_081)*MainFormSLS->hh[73];
c2.v[76] += (sum_160_1_082)*MainFormSLS->hh[66];
c2.v[76] += (sum_160_1_083)*MainFormSLS->hh[59];
c2.v[76] += (sum_160_1_084)*MainFormSLS->hh[52];
c2.v[76] += (sum_160_1_085)*MainFormSLS->hh[45];
c2.v[76] += (sum_160_1_086)*MainFormSLS->hh[38];
c2.v[76] += (sum_160_1_087)*MainFormSLS->hh[31];
c2.v[76] += (sum_160_1_088)*MainFormSLS->hh[24];
c2.v[76] += (sum_160_1_089)*MainFormSLS->hh[17];
c2.v[76] += (sum_160_1_090)*MainFormSLS->hh[10];
c2.v[76] += (sum_160_1_091)*MainFormSLS->hh[3];
c2.v[76] += (sum_160_1_092)*MainFormSLS->hh[156];
c2.v[76] += (sum_160_1_093)*MainFormSLS->hh[149];
c2.v[76] += (sum_160_1_094)*MainFormSLS->hh[142];
c2.v[76] += (sum_160_1_095)*MainFormSLS->hh[135];
c2.v[76] += (sum_160_1_096)*MainFormSLS->hh[128];
c2.v[76] += (sum_160_1_097)*MainFormSLS->hh[121];
c2.v[76] += (sum_160_1_098)*MainFormSLS->hh[114];
c2.v[76] += (sum_160_1_099)*MainFormSLS->hh[107];
c2.v[76] += (sum_160_1_100)*MainFormSLS->hh[100];
c2.v[76] += (sum_160_1_101)*MainFormSLS->hh[93];
c2.v[76] += (sum_160_1_102)*MainFormSLS->hh[86];
c2.v[76] += (sum_160_1_103)*MainFormSLS->hh[79];
c2.v[76] += (sum_160_1_104)*MainFormSLS->hh[72];
c2.v[76] += (sum_160_1_105)*MainFormSLS->hh[65];
c2.v[76] += (sum_160_1_106)*MainFormSLS->hh[58];
c2.v[76] += (sum_160_1_107)*MainFormSLS->hh[51];
c2.v[76] += (sum_160_1_108)*MainFormSLS->hh[44];
c2.v[76] += (sum_160_1_109)*MainFormSLS->hh[37];
c2.v[76] += (sum_160_1_110)*MainFormSLS->hh[30];
c2.v[76] += (sum_160_1_111)*MainFormSLS->hh[23];
c2.v[76] += (sum_160_1_112)*MainFormSLS->hh[16];
c2.v[76] += (sum_160_1_113)*MainFormSLS->hh[9];
c2.v[76] += (sum_160_1_114)*MainFormSLS->hh[2];
c2.v[76] += (sum_160_1_115)*MainFormSLS->hh[155];
c2.v[76] += (sum_160_1_116)*MainFormSLS->hh[148];
c2.v[76] += (sum_160_1_117)*MainFormSLS->hh[141];
c2.v[76] += (sum_160_1_118)*MainFormSLS->hh[134];
c2.v[76] += (sum_160_1_119)*MainFormSLS->hh[127];
c2.v[76] += (sum_160_1_120)*MainFormSLS->hh[120];
c2.v[76] += (sum_160_1_121)*MainFormSLS->hh[113];
c2.v[76] += (sum_160_1_122)*MainFormSLS->hh[106];
c2.v[76] += (sum_160_1_123)*MainFormSLS->hh[99];
c2.v[76] += (sum_160_1_124)*MainFormSLS->hh[92];
c2.v[76] += (sum_160_1_125)*MainFormSLS->hh[85];
c2.v[76] += (sum_160_1_126)*MainFormSLS->hh[78];
c2.v[76] += (sum_160_1_127)*MainFormSLS->hh[71];
c2.v[76] += (sum_160_1_128)*MainFormSLS->hh[64];
c2.v[76] += (sum_160_1_129)*MainFormSLS->hh[57];
c2.v[76] += (sum_160_1_130)*MainFormSLS->hh[50];
c2.v[76] += (sum_160_1_131)*MainFormSLS->hh[43];
c2.v[76] += (sum_160_1_132)*MainFormSLS->hh[36];
c2.v[76] += (sum_160_1_133)*MainFormSLS->hh[29];
c2.v[76] += (sum_160_1_134)*MainFormSLS->hh[22];
c2.v[76] += (sum_160_1_135)*MainFormSLS->hh[15];
c2.v[76] += (sum_160_1_136)*MainFormSLS->hh[8];
c2.v[76] += (sum_160_1_137)*MainFormSLS->hh[1];
c2.v[76] += (sum_160_1_138)*MainFormSLS->hh[154];
c2.v[76] += (sum_160_1_139)*MainFormSLS->hh[147];
c2.v[76] += (sum_160_1_140)*MainFormSLS->hh[140];
c2.v[76] += (sum_160_1_141)*MainFormSLS->hh[133];
c2.v[76] += (sum_160_1_142)*MainFormSLS->hh[126];
c2.v[76] += (sum_160_1_143)*MainFormSLS->hh[119];
c2.v[76] += (sum_160_1_144)*MainFormSLS->hh[112];
c2.v[76] += (sum_160_1_145)*MainFormSLS->hh[105];
c2.v[76] += (sum_160_1_146)*MainFormSLS->hh[98];
c2.v[76] += (sum_160_1_147)*MainFormSLS->hh[91];
c2.v[76] += (sum_160_1_148)*MainFormSLS->hh[84];
c2.v[76] += (sum_160_1_149)*MainFormSLS->hh[77];
c2.v[76] += (sum_160_1_150)*MainFormSLS->hh[70];
c2.v[76] += (sum_160_1_151)*MainFormSLS->hh[63];
c2.v[76] += (sum_160_1_152)*MainFormSLS->hh[56];
c2.v[76] += (sum_160_1_153)*MainFormSLS->hh[49];
c2.v[76] += (sum_160_1_154)*MainFormSLS->hh[42];
c2.v[76] += (sum_160_1_155)*MainFormSLS->hh[35];
c2.v[76] += (sum_160_1_156)*MainFormSLS->hh[28];
c2.v[76] += (sum_160_1_157)*MainFormSLS->hh[21];
c2.v[76] += (sum_160_1_158)*MainFormSLS->hh[14];
c2.v[76] += (sum_160_1_159)*MainFormSLS->hh[7];

//frequency level id 155
c2.v[77] += (sum_32_5_000)*MainFormSLS->hh[0];
c2.v[77] += (sum_32_5_001)*MainFormSLS->hh[155];
c2.v[77] += (sum_32_5_002)*MainFormSLS->hh[150];
c2.v[77] += (sum_32_5_003)*MainFormSLS->hh[145];
c2.v[77] += (sum_32_5_004)*MainFormSLS->hh[140];
c2.v[77] += (sum_32_5_005)*MainFormSLS->hh[135];
c2.v[77] += (sum_32_5_006)*MainFormSLS->hh[130];
c2.v[77] += (sum_32_5_007)*MainFormSLS->hh[125];
c2.v[77] += (sum_32_5_008)*MainFormSLS->hh[120];
c2.v[77] += (sum_32_5_009)*MainFormSLS->hh[115];
c2.v[77] += (sum_32_5_010)*MainFormSLS->hh[110];
c2.v[77] += (sum_32_5_011)*MainFormSLS->hh[105];
c2.v[77] += (sum_32_5_012)*MainFormSLS->hh[100];
c2.v[77] += (sum_32_5_013)*MainFormSLS->hh[95];
c2.v[77] += (sum_32_5_014)*MainFormSLS->hh[90];
c2.v[77] += (sum_32_5_015)*MainFormSLS->hh[85];
c2.v[77] += (sum_32_5_016)*MainFormSLS->hh[80];
c2.v[77] += (sum_32_5_017)*MainFormSLS->hh[75];
c2.v[77] += (sum_32_5_018)*MainFormSLS->hh[70];
c2.v[77] += (sum_32_5_019)*MainFormSLS->hh[65];
c2.v[77] += (sum_32_5_020)*MainFormSLS->hh[60];
c2.v[77] += (sum_32_5_021)*MainFormSLS->hh[55];
c2.v[77] += (sum_32_5_022)*MainFormSLS->hh[50];
c2.v[77] += (sum_32_5_023)*MainFormSLS->hh[45];
c2.v[77] += (sum_32_5_024)*MainFormSLS->hh[40];
c2.v[77] += (sum_32_5_025)*MainFormSLS->hh[35];
c2.v[77] += (sum_32_5_026)*MainFormSLS->hh[30];
c2.v[77] += (sum_32_5_027)*MainFormSLS->hh[25];
c2.v[77] += (sum_32_5_028)*MainFormSLS->hh[20];
c2.v[77] += (sum_32_5_029)*MainFormSLS->hh[15];
c2.v[77] += (sum_32_5_030)*MainFormSLS->hh[10];
c2.v[77] += (sum_32_5_031)*MainFormSLS->hh[5];

//frequency level id 157
c2.v[78] += (sum_160_1_000)*MainFormSLS->hh[0];
c2.v[78] += (sum_160_1_001)*MainFormSLS->hh[157];
c2.v[78] += (sum_160_1_002)*MainFormSLS->hh[154];
c2.v[78] += (sum_160_1_003)*MainFormSLS->hh[151];
c2.v[78] += (sum_160_1_004)*MainFormSLS->hh[148];
c2.v[78] += (sum_160_1_005)*MainFormSLS->hh[145];
c2.v[78] += (sum_160_1_006)*MainFormSLS->hh[142];
c2.v[78] += (sum_160_1_007)*MainFormSLS->hh[139];
c2.v[78] += (sum_160_1_008)*MainFormSLS->hh[136];
c2.v[78] += (sum_160_1_009)*MainFormSLS->hh[133];
c2.v[78] += (sum_160_1_010)*MainFormSLS->hh[130];
c2.v[78] += (sum_160_1_011)*MainFormSLS->hh[127];
c2.v[78] += (sum_160_1_012)*MainFormSLS->hh[124];
c2.v[78] += (sum_160_1_013)*MainFormSLS->hh[121];
c2.v[78] += (sum_160_1_014)*MainFormSLS->hh[118];
c2.v[78] += (sum_160_1_015)*MainFormSLS->hh[115];
c2.v[78] += (sum_160_1_016)*MainFormSLS->hh[112];
c2.v[78] += (sum_160_1_017)*MainFormSLS->hh[109];
c2.v[78] += (sum_160_1_018)*MainFormSLS->hh[106];
c2.v[78] += (sum_160_1_019)*MainFormSLS->hh[103];
c2.v[78] += (sum_160_1_020)*MainFormSLS->hh[100];
c2.v[78] += (sum_160_1_021)*MainFormSLS->hh[97];
c2.v[78] += (sum_160_1_022)*MainFormSLS->hh[94];
c2.v[78] += (sum_160_1_023)*MainFormSLS->hh[91];
c2.v[78] += (sum_160_1_024)*MainFormSLS->hh[88];
c2.v[78] += (sum_160_1_025)*MainFormSLS->hh[85];
c2.v[78] += (sum_160_1_026)*MainFormSLS->hh[82];
c2.v[78] += (sum_160_1_027)*MainFormSLS->hh[79];
c2.v[78] += (sum_160_1_028)*MainFormSLS->hh[76];
c2.v[78] += (sum_160_1_029)*MainFormSLS->hh[73];
c2.v[78] += (sum_160_1_030)*MainFormSLS->hh[70];
c2.v[78] += (sum_160_1_031)*MainFormSLS->hh[67];
c2.v[78] += (sum_160_1_032)*MainFormSLS->hh[64];
c2.v[78] += (sum_160_1_033)*MainFormSLS->hh[61];
c2.v[78] += (sum_160_1_034)*MainFormSLS->hh[58];
c2.v[78] += (sum_160_1_035)*MainFormSLS->hh[55];
c2.v[78] += (sum_160_1_036)*MainFormSLS->hh[52];
c2.v[78] += (sum_160_1_037)*MainFormSLS->hh[49];
c2.v[78] += (sum_160_1_038)*MainFormSLS->hh[46];
c2.v[78] += (sum_160_1_039)*MainFormSLS->hh[43];
c2.v[78] += (sum_160_1_040)*MainFormSLS->hh[40];
c2.v[78] += (sum_160_1_041)*MainFormSLS->hh[37];
c2.v[78] += (sum_160_1_042)*MainFormSLS->hh[34];
c2.v[78] += (sum_160_1_043)*MainFormSLS->hh[31];
c2.v[78] += (sum_160_1_044)*MainFormSLS->hh[28];
c2.v[78] += (sum_160_1_045)*MainFormSLS->hh[25];
c2.v[78] += (sum_160_1_046)*MainFormSLS->hh[22];
c2.v[78] += (sum_160_1_047)*MainFormSLS->hh[19];
c2.v[78] += (sum_160_1_048)*MainFormSLS->hh[16];
c2.v[78] += (sum_160_1_049)*MainFormSLS->hh[13];
c2.v[78] += (sum_160_1_050)*MainFormSLS->hh[10];
c2.v[78] += (sum_160_1_051)*MainFormSLS->hh[7];
c2.v[78] += (sum_160_1_052)*MainFormSLS->hh[4];
c2.v[78] += (sum_160_1_053)*MainFormSLS->hh[1];
c2.v[78] += (sum_160_1_054)*MainFormSLS->hh[158];
c2.v[78] += (sum_160_1_055)*MainFormSLS->hh[155];
c2.v[78] += (sum_160_1_056)*MainFormSLS->hh[152];
c2.v[78] += (sum_160_1_057)*MainFormSLS->hh[149];
c2.v[78] += (sum_160_1_058)*MainFormSLS->hh[146];
c2.v[78] += (sum_160_1_059)*MainFormSLS->hh[143];
c2.v[78] += (sum_160_1_060)*MainFormSLS->hh[140];
c2.v[78] += (sum_160_1_061)*MainFormSLS->hh[137];
c2.v[78] += (sum_160_1_062)*MainFormSLS->hh[134];
c2.v[78] += (sum_160_1_063)*MainFormSLS->hh[131];
c2.v[78] += (sum_160_1_064)*MainFormSLS->hh[128];
c2.v[78] += (sum_160_1_065)*MainFormSLS->hh[125];
c2.v[78] += (sum_160_1_066)*MainFormSLS->hh[122];
c2.v[78] += (sum_160_1_067)*MainFormSLS->hh[119];
c2.v[78] += (sum_160_1_068)*MainFormSLS->hh[116];
c2.v[78] += (sum_160_1_069)*MainFormSLS->hh[113];
c2.v[78] += (sum_160_1_070)*MainFormSLS->hh[110];
c2.v[78] += (sum_160_1_071)*MainFormSLS->hh[107];
c2.v[78] += (sum_160_1_072)*MainFormSLS->hh[104];
c2.v[78] += (sum_160_1_073)*MainFormSLS->hh[101];
c2.v[78] += (sum_160_1_074)*MainFormSLS->hh[98];
c2.v[78] += (sum_160_1_075)*MainFormSLS->hh[95];
c2.v[78] += (sum_160_1_076)*MainFormSLS->hh[92];
c2.v[78] += (sum_160_1_077)*MainFormSLS->hh[89];
c2.v[78] += (sum_160_1_078)*MainFormSLS->hh[86];
c2.v[78] += (sum_160_1_079)*MainFormSLS->hh[83];
c2.v[78] += (sum_160_1_080)*MainFormSLS->hh[80];
c2.v[78] += (sum_160_1_081)*MainFormSLS->hh[77];
c2.v[78] += (sum_160_1_082)*MainFormSLS->hh[74];
c2.v[78] += (sum_160_1_083)*MainFormSLS->hh[71];
c2.v[78] += (sum_160_1_084)*MainFormSLS->hh[68];
c2.v[78] += (sum_160_1_085)*MainFormSLS->hh[65];
c2.v[78] += (sum_160_1_086)*MainFormSLS->hh[62];
c2.v[78] += (sum_160_1_087)*MainFormSLS->hh[59];
c2.v[78] += (sum_160_1_088)*MainFormSLS->hh[56];
c2.v[78] += (sum_160_1_089)*MainFormSLS->hh[53];
c2.v[78] += (sum_160_1_090)*MainFormSLS->hh[50];
c2.v[78] += (sum_160_1_091)*MainFormSLS->hh[47];
c2.v[78] += (sum_160_1_092)*MainFormSLS->hh[44];
c2.v[78] += (sum_160_1_093)*MainFormSLS->hh[41];
c2.v[78] += (sum_160_1_094)*MainFormSLS->hh[38];
c2.v[78] += (sum_160_1_095)*MainFormSLS->hh[35];
c2.v[78] += (sum_160_1_096)*MainFormSLS->hh[32];
c2.v[78] += (sum_160_1_097)*MainFormSLS->hh[29];
c2.v[78] += (sum_160_1_098)*MainFormSLS->hh[26];
c2.v[78] += (sum_160_1_099)*MainFormSLS->hh[23];
c2.v[78] += (sum_160_1_100)*MainFormSLS->hh[20];
c2.v[78] += (sum_160_1_101)*MainFormSLS->hh[17];
c2.v[78] += (sum_160_1_102)*MainFormSLS->hh[14];
c2.v[78] += (sum_160_1_103)*MainFormSLS->hh[11];
c2.v[78] += (sum_160_1_104)*MainFormSLS->hh[8];
c2.v[78] += (sum_160_1_105)*MainFormSLS->hh[5];
c2.v[78] += (sum_160_1_106)*MainFormSLS->hh[2];
c2.v[78] += (sum_160_1_107)*MainFormSLS->hh[159];
c2.v[78] += (sum_160_1_108)*MainFormSLS->hh[156];
c2.v[78] += (sum_160_1_109)*MainFormSLS->hh[153];
c2.v[78] += (sum_160_1_110)*MainFormSLS->hh[150];
c2.v[78] += (sum_160_1_111)*MainFormSLS->hh[147];
c2.v[78] += (sum_160_1_112)*MainFormSLS->hh[144];
c2.v[78] += (sum_160_1_113)*MainFormSLS->hh[141];
c2.v[78] += (sum_160_1_114)*MainFormSLS->hh[138];
c2.v[78] += (sum_160_1_115)*MainFormSLS->hh[135];
c2.v[78] += (sum_160_1_116)*MainFormSLS->hh[132];
c2.v[78] += (sum_160_1_117)*MainFormSLS->hh[129];
c2.v[78] += (sum_160_1_118)*MainFormSLS->hh[126];
c2.v[78] += (sum_160_1_119)*MainFormSLS->hh[123];
c2.v[78] += (sum_160_1_120)*MainFormSLS->hh[120];
c2.v[78] += (sum_160_1_121)*MainFormSLS->hh[117];
c2.v[78] += (sum_160_1_122)*MainFormSLS->hh[114];
c2.v[78] += (sum_160_1_123)*MainFormSLS->hh[111];
c2.v[78] += (sum_160_1_124)*MainFormSLS->hh[108];
c2.v[78] += (sum_160_1_125)*MainFormSLS->hh[105];
c2.v[78] += (sum_160_1_126)*MainFormSLS->hh[102];
c2.v[78] += (sum_160_1_127)*MainFormSLS->hh[99];
c2.v[78] += (sum_160_1_128)*MainFormSLS->hh[96];
c2.v[78] += (sum_160_1_129)*MainFormSLS->hh[93];
c2.v[78] += (sum_160_1_130)*MainFormSLS->hh[90];
c2.v[78] += (sum_160_1_131)*MainFormSLS->hh[87];
c2.v[78] += (sum_160_1_132)*MainFormSLS->hh[84];
c2.v[78] += (sum_160_1_133)*MainFormSLS->hh[81];
c2.v[78] += (sum_160_1_134)*MainFormSLS->hh[78];
c2.v[78] += (sum_160_1_135)*MainFormSLS->hh[75];
c2.v[78] += (sum_160_1_136)*MainFormSLS->hh[72];
c2.v[78] += (sum_160_1_137)*MainFormSLS->hh[69];
c2.v[78] += (sum_160_1_138)*MainFormSLS->hh[66];
c2.v[78] += (sum_160_1_139)*MainFormSLS->hh[63];
c2.v[78] += (sum_160_1_140)*MainFormSLS->hh[60];
c2.v[78] += (sum_160_1_141)*MainFormSLS->hh[57];
c2.v[78] += (sum_160_1_142)*MainFormSLS->hh[54];
c2.v[78] += (sum_160_1_143)*MainFormSLS->hh[51];
c2.v[78] += (sum_160_1_144)*MainFormSLS->hh[48];
c2.v[78] += (sum_160_1_145)*MainFormSLS->hh[45];
c2.v[78] += (sum_160_1_146)*MainFormSLS->hh[42];
c2.v[78] += (sum_160_1_147)*MainFormSLS->hh[39];
c2.v[78] += (sum_160_1_148)*MainFormSLS->hh[36];
c2.v[78] += (sum_160_1_149)*MainFormSLS->hh[33];
c2.v[78] += (sum_160_1_150)*MainFormSLS->hh[30];
c2.v[78] += (sum_160_1_151)*MainFormSLS->hh[27];
c2.v[78] += (sum_160_1_152)*MainFormSLS->hh[24];
c2.v[78] += (sum_160_1_153)*MainFormSLS->hh[21];
c2.v[78] += (sum_160_1_154)*MainFormSLS->hh[18];
c2.v[78] += (sum_160_1_155)*MainFormSLS->hh[15];
c2.v[78] += (sum_160_1_156)*MainFormSLS->hh[12];
c2.v[78] += (sum_160_1_157)*MainFormSLS->hh[9];
c2.v[78] += (sum_160_1_158)*MainFormSLS->hh[6];
c2.v[78] += (sum_160_1_159)*MainFormSLS->hh[3];

//frequency level id 159
c2.v[79] += (sum_160_1_000)*MainFormSLS->hh[0];
c2.v[79] += (sum_160_1_001)*MainFormSLS->hh[159];
c2.v[79] += (sum_160_1_002)*MainFormSLS->hh[158];
c2.v[79] += (sum_160_1_003)*MainFormSLS->hh[157];
c2.v[79] += (sum_160_1_004)*MainFormSLS->hh[156];
c2.v[79] += (sum_160_1_005)*MainFormSLS->hh[155];
c2.v[79] += (sum_160_1_006)*MainFormSLS->hh[154];
c2.v[79] += (sum_160_1_007)*MainFormSLS->hh[153];
c2.v[79] += (sum_160_1_008)*MainFormSLS->hh[152];
c2.v[79] += (sum_160_1_009)*MainFormSLS->hh[151];
c2.v[79] += (sum_160_1_010)*MainFormSLS->hh[150];
c2.v[79] += (sum_160_1_011)*MainFormSLS->hh[149];
c2.v[79] += (sum_160_1_012)*MainFormSLS->hh[148];
c2.v[79] += (sum_160_1_013)*MainFormSLS->hh[147];
c2.v[79] += (sum_160_1_014)*MainFormSLS->hh[146];
c2.v[79] += (sum_160_1_015)*MainFormSLS->hh[145];
c2.v[79] += (sum_160_1_016)*MainFormSLS->hh[144];
c2.v[79] += (sum_160_1_017)*MainFormSLS->hh[143];
c2.v[79] += (sum_160_1_018)*MainFormSLS->hh[142];
c2.v[79] += (sum_160_1_019)*MainFormSLS->hh[141];
c2.v[79] += (sum_160_1_020)*MainFormSLS->hh[140];
c2.v[79] += (sum_160_1_021)*MainFormSLS->hh[139];
c2.v[79] += (sum_160_1_022)*MainFormSLS->hh[138];
c2.v[79] += (sum_160_1_023)*MainFormSLS->hh[137];
c2.v[79] += (sum_160_1_024)*MainFormSLS->hh[136];
c2.v[79] += (sum_160_1_025)*MainFormSLS->hh[135];
c2.v[79] += (sum_160_1_026)*MainFormSLS->hh[134];
c2.v[79] += (sum_160_1_027)*MainFormSLS->hh[133];
c2.v[79] += (sum_160_1_028)*MainFormSLS->hh[132];
c2.v[79] += (sum_160_1_029)*MainFormSLS->hh[131];
c2.v[79] += (sum_160_1_030)*MainFormSLS->hh[130];
c2.v[79] += (sum_160_1_031)*MainFormSLS->hh[129];
c2.v[79] += (sum_160_1_032)*MainFormSLS->hh[128];
c2.v[79] += (sum_160_1_033)*MainFormSLS->hh[127];
c2.v[79] += (sum_160_1_034)*MainFormSLS->hh[126];
c2.v[79] += (sum_160_1_035)*MainFormSLS->hh[125];
c2.v[79] += (sum_160_1_036)*MainFormSLS->hh[124];
c2.v[79] += (sum_160_1_037)*MainFormSLS->hh[123];
c2.v[79] += (sum_160_1_038)*MainFormSLS->hh[122];
c2.v[79] += (sum_160_1_039)*MainFormSLS->hh[121];
c2.v[79] += (sum_160_1_040)*MainFormSLS->hh[120];
c2.v[79] += (sum_160_1_041)*MainFormSLS->hh[119];
c2.v[79] += (sum_160_1_042)*MainFormSLS->hh[118];
c2.v[79] += (sum_160_1_043)*MainFormSLS->hh[117];
c2.v[79] += (sum_160_1_044)*MainFormSLS->hh[116];
c2.v[79] += (sum_160_1_045)*MainFormSLS->hh[115];
c2.v[79] += (sum_160_1_046)*MainFormSLS->hh[114];
c2.v[79] += (sum_160_1_047)*MainFormSLS->hh[113];
c2.v[79] += (sum_160_1_048)*MainFormSLS->hh[112];
c2.v[79] += (sum_160_1_049)*MainFormSLS->hh[111];
c2.v[79] += (sum_160_1_050)*MainFormSLS->hh[110];
c2.v[79] += (sum_160_1_051)*MainFormSLS->hh[109];
c2.v[79] += (sum_160_1_052)*MainFormSLS->hh[108];
c2.v[79] += (sum_160_1_053)*MainFormSLS->hh[107];
c2.v[79] += (sum_160_1_054)*MainFormSLS->hh[106];
c2.v[79] += (sum_160_1_055)*MainFormSLS->hh[105];
c2.v[79] += (sum_160_1_056)*MainFormSLS->hh[104];
c2.v[79] += (sum_160_1_057)*MainFormSLS->hh[103];
c2.v[79] += (sum_160_1_058)*MainFormSLS->hh[102];
c2.v[79] += (sum_160_1_059)*MainFormSLS->hh[101];
c2.v[79] += (sum_160_1_060)*MainFormSLS->hh[100];
c2.v[79] += (sum_160_1_061)*MainFormSLS->hh[99];
c2.v[79] += (sum_160_1_062)*MainFormSLS->hh[98];
c2.v[79] += (sum_160_1_063)*MainFormSLS->hh[97];
c2.v[79] += (sum_160_1_064)*MainFormSLS->hh[96];
c2.v[79] += (sum_160_1_065)*MainFormSLS->hh[95];
c2.v[79] += (sum_160_1_066)*MainFormSLS->hh[94];
c2.v[79] += (sum_160_1_067)*MainFormSLS->hh[93];
c2.v[79] += (sum_160_1_068)*MainFormSLS->hh[92];
c2.v[79] += (sum_160_1_069)*MainFormSLS->hh[91];
c2.v[79] += (sum_160_1_070)*MainFormSLS->hh[90];
c2.v[79] += (sum_160_1_071)*MainFormSLS->hh[89];
c2.v[79] += (sum_160_1_072)*MainFormSLS->hh[88];
c2.v[79] += (sum_160_1_073)*MainFormSLS->hh[87];
c2.v[79] += (sum_160_1_074)*MainFormSLS->hh[86];
c2.v[79] += (sum_160_1_075)*MainFormSLS->hh[85];
c2.v[79] += (sum_160_1_076)*MainFormSLS->hh[84];
c2.v[79] += (sum_160_1_077)*MainFormSLS->hh[83];
c2.v[79] += (sum_160_1_078)*MainFormSLS->hh[82];
c2.v[79] += (sum_160_1_079)*MainFormSLS->hh[81];
c2.v[79] += (sum_160_1_080)*MainFormSLS->hh[80];
c2.v[79] += (sum_160_1_081)*MainFormSLS->hh[79];
c2.v[79] += (sum_160_1_082)*MainFormSLS->hh[78];
c2.v[79] += (sum_160_1_083)*MainFormSLS->hh[77];
c2.v[79] += (sum_160_1_084)*MainFormSLS->hh[76];
c2.v[79] += (sum_160_1_085)*MainFormSLS->hh[75];
c2.v[79] += (sum_160_1_086)*MainFormSLS->hh[74];
c2.v[79] += (sum_160_1_087)*MainFormSLS->hh[73];
c2.v[79] += (sum_160_1_088)*MainFormSLS->hh[72];
c2.v[79] += (sum_160_1_089)*MainFormSLS->hh[71];
c2.v[79] += (sum_160_1_090)*MainFormSLS->hh[70];
c2.v[79] += (sum_160_1_091)*MainFormSLS->hh[69];
c2.v[79] += (sum_160_1_092)*MainFormSLS->hh[68];
c2.v[79] += (sum_160_1_093)*MainFormSLS->hh[67];
c2.v[79] += (sum_160_1_094)*MainFormSLS->hh[66];
c2.v[79] += (sum_160_1_095)*MainFormSLS->hh[65];
c2.v[79] += (sum_160_1_096)*MainFormSLS->hh[64];
c2.v[79] += (sum_160_1_097)*MainFormSLS->hh[63];
c2.v[79] += (sum_160_1_098)*MainFormSLS->hh[62];
c2.v[79] += (sum_160_1_099)*MainFormSLS->hh[61];
c2.v[79] += (sum_160_1_100)*MainFormSLS->hh[60];
c2.v[79] += (sum_160_1_101)*MainFormSLS->hh[59];
c2.v[79] += (sum_160_1_102)*MainFormSLS->hh[58];
c2.v[79] += (sum_160_1_103)*MainFormSLS->hh[57];
c2.v[79] += (sum_160_1_104)*MainFormSLS->hh[56];
c2.v[79] += (sum_160_1_105)*MainFormSLS->hh[55];
c2.v[79] += (sum_160_1_106)*MainFormSLS->hh[54];
c2.v[79] += (sum_160_1_107)*MainFormSLS->hh[53];
c2.v[79] += (sum_160_1_108)*MainFormSLS->hh[52];
c2.v[79] += (sum_160_1_109)*MainFormSLS->hh[51];
c2.v[79] += (sum_160_1_110)*MainFormSLS->hh[50];
c2.v[79] += (sum_160_1_111)*MainFormSLS->hh[49];
c2.v[79] += (sum_160_1_112)*MainFormSLS->hh[48];
c2.v[79] += (sum_160_1_113)*MainFormSLS->hh[47];
c2.v[79] += (sum_160_1_114)*MainFormSLS->hh[46];
c2.v[79] += (sum_160_1_115)*MainFormSLS->hh[45];
c2.v[79] += (sum_160_1_116)*MainFormSLS->hh[44];
c2.v[79] += (sum_160_1_117)*MainFormSLS->hh[43];
c2.v[79] += (sum_160_1_118)*MainFormSLS->hh[42];
c2.v[79] += (sum_160_1_119)*MainFormSLS->hh[41];
c2.v[79] += (sum_160_1_120)*MainFormSLS->hh[40];
c2.v[79] += (sum_160_1_121)*MainFormSLS->hh[39];
c2.v[79] += (sum_160_1_122)*MainFormSLS->hh[38];
c2.v[79] += (sum_160_1_123)*MainFormSLS->hh[37];
c2.v[79] += (sum_160_1_124)*MainFormSLS->hh[36];
c2.v[79] += (sum_160_1_125)*MainFormSLS->hh[35];
c2.v[79] += (sum_160_1_126)*MainFormSLS->hh[34];
c2.v[79] += (sum_160_1_127)*MainFormSLS->hh[33];
c2.v[79] += (sum_160_1_128)*MainFormSLS->hh[32];
c2.v[79] += (sum_160_1_129)*MainFormSLS->hh[31];
c2.v[79] += (sum_160_1_130)*MainFormSLS->hh[30];
c2.v[79] += (sum_160_1_131)*MainFormSLS->hh[29];
c2.v[79] += (sum_160_1_132)*MainFormSLS->hh[28];
c2.v[79] += (sum_160_1_133)*MainFormSLS->hh[27];
c2.v[79] += (sum_160_1_134)*MainFormSLS->hh[26];
c2.v[79] += (sum_160_1_135)*MainFormSLS->hh[25];
c2.v[79] += (sum_160_1_136)*MainFormSLS->hh[24];
c2.v[79] += (sum_160_1_137)*MainFormSLS->hh[23];
c2.v[79] += (sum_160_1_138)*MainFormSLS->hh[22];
c2.v[79] += (sum_160_1_139)*MainFormSLS->hh[21];
c2.v[79] += (sum_160_1_140)*MainFormSLS->hh[20];
c2.v[79] += (sum_160_1_141)*MainFormSLS->hh[19];
c2.v[79] += (sum_160_1_142)*MainFormSLS->hh[18];
c2.v[79] += (sum_160_1_143)*MainFormSLS->hh[17];
c2.v[79] += (sum_160_1_144)*MainFormSLS->hh[16];
c2.v[79] += (sum_160_1_145)*MainFormSLS->hh[15];
c2.v[79] += (sum_160_1_146)*MainFormSLS->hh[14];
c2.v[79] += (sum_160_1_147)*MainFormSLS->hh[13];
c2.v[79] += (sum_160_1_148)*MainFormSLS->hh[12];
c2.v[79] += (sum_160_1_149)*MainFormSLS->hh[11];
c2.v[79] += (sum_160_1_150)*MainFormSLS->hh[10];
c2.v[79] += (sum_160_1_151)*MainFormSLS->hh[9];
c2.v[79] += (sum_160_1_152)*MainFormSLS->hh[8];
c2.v[79] += (sum_160_1_153)*MainFormSLS->hh[7];
c2.v[79] += (sum_160_1_154)*MainFormSLS->hh[6];
c2.v[79] += (sum_160_1_155)*MainFormSLS->hh[5];
c2.v[79] += (sum_160_1_156)*MainFormSLS->hh[4];
c2.v[79] += (sum_160_1_157)*MainFormSLS->hh[3];
c2.v[79] += (sum_160_1_158)*MainFormSLS->hh[2];
c2.v[79] += (sum_160_1_159)*MainFormSLS->hh[1];
}
//---------------------------------------------------------------------------
void __fastcall rdft_odd(vector<complex<double> >& out,TCoeff_BY_2& c2)
{
int N_2 = c2.N;
complex<double> s;
//������ 0
s =c2.v[0]*MainFormSLS->hh_1[0]
 + c2.v[1]*MainFormSLS->hh_1[0]
 + c2.v[2]*MainFormSLS->hh_1[0]
 + c2.v[3]*MainFormSLS->hh_1[0]
 + c2.v[4]*MainFormSLS->hh_1[0]
 + c2.v[5]*MainFormSLS->hh_1[0]
 + c2.v[6]*MainFormSLS->hh_1[0]
 + c2.v[7]*MainFormSLS->hh_1[0]
 + c2.v[8]*MainFormSLS->hh_1[0]
 + c2.v[9]*MainFormSLS->hh_1[0]
 + c2.v[10]*MainFormSLS->hh_1[0]
 + c2.v[11]*MainFormSLS->hh_1[0]
 + c2.v[12]*MainFormSLS->hh_1[0]
 + c2.v[13]*MainFormSLS->hh_1[0]
 + c2.v[14]*MainFormSLS->hh_1[0]
 + c2.v[15]*MainFormSLS->hh_1[0]
 + c2.v[16]*MainFormSLS->hh_1[0]
 + c2.v[17]*MainFormSLS->hh_1[0]
 + c2.v[18]*MainFormSLS->hh_1[0]
 + c2.v[19]*MainFormSLS->hh_1[0]
 + c2.v[20]*MainFormSLS->hh_1[0]
 + c2.v[21]*MainFormSLS->hh_1[0]
 + c2.v[22]*MainFormSLS->hh_1[0]
 + c2.v[23]*MainFormSLS->hh_1[0]
 + c2.v[24]*MainFormSLS->hh_1[0]
 + c2.v[25]*MainFormSLS->hh_1[0]
 + c2.v[26]*MainFormSLS->hh_1[0]
 + c2.v[27]*MainFormSLS->hh_1[0]
 + c2.v[28]*MainFormSLS->hh_1[0]
 + c2.v[29]*MainFormSLS->hh_1[0]
 + c2.v[30]*MainFormSLS->hh_1[0]
 + c2.v[31]*MainFormSLS->hh_1[0]
 + c2.v[32]*MainFormSLS->hh_1[0]
 + c2.v[33]*MainFormSLS->hh_1[0]
 + c2.v[34]*MainFormSLS->hh_1[0]
 + c2.v[35]*MainFormSLS->hh_1[0]
 + c2.v[36]*MainFormSLS->hh_1[0]
 + c2.v[37]*MainFormSLS->hh_1[0]
 + c2.v[38]*MainFormSLS->hh_1[0]
 + c2.v[39]*MainFormSLS->hh_1[0]
 + c2.v[40]*MainFormSLS->hh_1[0]
 + c2.v[41]*MainFormSLS->hh_1[0]
 + c2.v[42]*MainFormSLS->hh_1[0]
 + c2.v[43]*MainFormSLS->hh_1[0]
 + c2.v[44]*MainFormSLS->hh_1[0]
 + c2.v[45]*MainFormSLS->hh_1[0]
 + c2.v[46]*MainFormSLS->hh_1[0]
 + c2.v[47]*MainFormSLS->hh_1[0]
 + c2.v[48]*MainFormSLS->hh_1[0]
 + c2.v[49]*MainFormSLS->hh_1[0]
 + c2.v[50]*MainFormSLS->hh_1[0]
 + c2.v[51]*MainFormSLS->hh_1[0]
 + c2.v[52]*MainFormSLS->hh_1[0]
 + c2.v[53]*MainFormSLS->hh_1[0]
 + c2.v[54]*MainFormSLS->hh_1[0]
 + c2.v[55]*MainFormSLS->hh_1[0]
 + c2.v[56]*MainFormSLS->hh_1[0]
 + c2.v[57]*MainFormSLS->hh_1[0]
 + c2.v[58]*MainFormSLS->hh_1[0]
 + c2.v[59]*MainFormSLS->hh_1[0]
 + c2.v[60]*MainFormSLS->hh_1[0]
 + c2.v[61]*MainFormSLS->hh_1[0]
 + c2.v[62]*MainFormSLS->hh_1[0]
 + c2.v[63]*MainFormSLS->hh_1[0]
 + c2.v[64]*MainFormSLS->hh_1[0]
 + c2.v[65]*MainFormSLS->hh_1[0]
 + c2.v[66]*MainFormSLS->hh_1[0]
 + c2.v[67]*MainFormSLS->hh_1[0]
 + c2.v[68]*MainFormSLS->hh_1[0]
 + c2.v[69]*MainFormSLS->hh_1[0]
 + c2.v[70]*MainFormSLS->hh_1[0]
 + c2.v[71]*MainFormSLS->hh_1[0]
 + c2.v[72]*MainFormSLS->hh_1[0]
 + c2.v[73]*MainFormSLS->hh_1[0]
 + c2.v[74]*MainFormSLS->hh_1[0]
 + c2.v[75]*MainFormSLS->hh_1[0]
 + c2.v[76]*MainFormSLS->hh_1[0]
 + c2.v[77]*MainFormSLS->hh_1[0]
 + c2.v[78]*MainFormSLS->hh_1[0]
 + c2.v[79]*MainFormSLS->hh_1[0];
s/=N_2;
out.push_back(s);
//������ 1
s =c2.v[0]*MainFormSLS->hh_1[1]
 + c2.v[1]*MainFormSLS->hh_1[3]
 + c2.v[2]*MainFormSLS->hh_1[5]
 + c2.v[3]*MainFormSLS->hh_1[7]
 + c2.v[4]*MainFormSLS->hh_1[9]
 + c2.v[5]*MainFormSLS->hh_1[11]
 + c2.v[6]*MainFormSLS->hh_1[13]
 + c2.v[7]*MainFormSLS->hh_1[15]
 + c2.v[8]*MainFormSLS->hh_1[17]
 + c2.v[9]*MainFormSLS->hh_1[19]
 + c2.v[10]*MainFormSLS->hh_1[21]
 + c2.v[11]*MainFormSLS->hh_1[23]
 + c2.v[12]*MainFormSLS->hh_1[25]
 + c2.v[13]*MainFormSLS->hh_1[27]
 + c2.v[14]*MainFormSLS->hh_1[29]
 + c2.v[15]*MainFormSLS->hh_1[31]
 + c2.v[16]*MainFormSLS->hh_1[33]
 + c2.v[17]*MainFormSLS->hh_1[35]
 + c2.v[18]*MainFormSLS->hh_1[37]
 + c2.v[19]*MainFormSLS->hh_1[39]
 + c2.v[20]*MainFormSLS->hh_1[41]
 + c2.v[21]*MainFormSLS->hh_1[43]
 + c2.v[22]*MainFormSLS->hh_1[45]
 + c2.v[23]*MainFormSLS->hh_1[47]
 + c2.v[24]*MainFormSLS->hh_1[49]
 + c2.v[25]*MainFormSLS->hh_1[51]
 + c2.v[26]*MainFormSLS->hh_1[53]
 + c2.v[27]*MainFormSLS->hh_1[55]
 + c2.v[28]*MainFormSLS->hh_1[57]
 + c2.v[29]*MainFormSLS->hh_1[59]
 + c2.v[30]*MainFormSLS->hh_1[61]
 + c2.v[31]*MainFormSLS->hh_1[63]
 + c2.v[32]*MainFormSLS->hh_1[65]
 + c2.v[33]*MainFormSLS->hh_1[67]
 + c2.v[34]*MainFormSLS->hh_1[69]
 + c2.v[35]*MainFormSLS->hh_1[71]
 + c2.v[36]*MainFormSLS->hh_1[73]
 + c2.v[37]*MainFormSLS->hh_1[75]
 + c2.v[38]*MainFormSLS->hh_1[77]
 + c2.v[39]*MainFormSLS->hh_1[79]
 + c2.v[40]*MainFormSLS->hh_1[81]
 + c2.v[41]*MainFormSLS->hh_1[83]
 + c2.v[42]*MainFormSLS->hh_1[85]
 + c2.v[43]*MainFormSLS->hh_1[87]
 + c2.v[44]*MainFormSLS->hh_1[89]
 + c2.v[45]*MainFormSLS->hh_1[91]
 + c2.v[46]*MainFormSLS->hh_1[93]
 + c2.v[47]*MainFormSLS->hh_1[95]
 + c2.v[48]*MainFormSLS->hh_1[97]
 + c2.v[49]*MainFormSLS->hh_1[99]
 + c2.v[50]*MainFormSLS->hh_1[101]
 + c2.v[51]*MainFormSLS->hh_1[103]
 + c2.v[52]*MainFormSLS->hh_1[105]
 + c2.v[53]*MainFormSLS->hh_1[107]
 + c2.v[54]*MainFormSLS->hh_1[109]
 + c2.v[55]*MainFormSLS->hh_1[111]
 + c2.v[56]*MainFormSLS->hh_1[113]
 + c2.v[57]*MainFormSLS->hh_1[115]
 + c2.v[58]*MainFormSLS->hh_1[117]
 + c2.v[59]*MainFormSLS->hh_1[119]
 + c2.v[60]*MainFormSLS->hh_1[121]
 + c2.v[61]*MainFormSLS->hh_1[123]
 + c2.v[62]*MainFormSLS->hh_1[125]
 + c2.v[63]*MainFormSLS->hh_1[127]
 + c2.v[64]*MainFormSLS->hh_1[129]
 + c2.v[65]*MainFormSLS->hh_1[131]
 + c2.v[66]*MainFormSLS->hh_1[133]
 + c2.v[67]*MainFormSLS->hh_1[135]
 + c2.v[68]*MainFormSLS->hh_1[137]
 + c2.v[69]*MainFormSLS->hh_1[139]
 + c2.v[70]*MainFormSLS->hh_1[141]
 + c2.v[71]*MainFormSLS->hh_1[143]
 + c2.v[72]*MainFormSLS->hh_1[145]
 + c2.v[73]*MainFormSLS->hh_1[147]
 + c2.v[74]*MainFormSLS->hh_1[149]
 + c2.v[75]*MainFormSLS->hh_1[151]
 + c2.v[76]*MainFormSLS->hh_1[153]
 + c2.v[77]*MainFormSLS->hh_1[155]
 + c2.v[78]*MainFormSLS->hh_1[157]
 + c2.v[79]*MainFormSLS->hh_1[159];
s/=N_2;
out.push_back(s);
//������ 2
s =c2.v[0]*MainFormSLS->hh_1[2]
 + c2.v[1]*MainFormSLS->hh_1[6]
 + c2.v[2]*MainFormSLS->hh_1[10]
 + c2.v[3]*MainFormSLS->hh_1[14]
 + c2.v[4]*MainFormSLS->hh_1[18]
 + c2.v[5]*MainFormSLS->hh_1[22]
 + c2.v[6]*MainFormSLS->hh_1[26]
 + c2.v[7]*MainFormSLS->hh_1[30]
 + c2.v[8]*MainFormSLS->hh_1[34]
 + c2.v[9]*MainFormSLS->hh_1[38]
 + c2.v[10]*MainFormSLS->hh_1[42]
 + c2.v[11]*MainFormSLS->hh_1[46]
 + c2.v[12]*MainFormSLS->hh_1[50]
 + c2.v[13]*MainFormSLS->hh_1[54]
 + c2.v[14]*MainFormSLS->hh_1[58]
 + c2.v[15]*MainFormSLS->hh_1[62]
 + c2.v[16]*MainFormSLS->hh_1[66]
 + c2.v[17]*MainFormSLS->hh_1[70]
 + c2.v[18]*MainFormSLS->hh_1[74]
 + c2.v[19]*MainFormSLS->hh_1[78]
 + c2.v[20]*MainFormSLS->hh_1[82]
 + c2.v[21]*MainFormSLS->hh_1[86]
 + c2.v[22]*MainFormSLS->hh_1[90]
 + c2.v[23]*MainFormSLS->hh_1[94]
 + c2.v[24]*MainFormSLS->hh_1[98]
 + c2.v[25]*MainFormSLS->hh_1[102]
 + c2.v[26]*MainFormSLS->hh_1[106]
 + c2.v[27]*MainFormSLS->hh_1[110]
 + c2.v[28]*MainFormSLS->hh_1[114]
 + c2.v[29]*MainFormSLS->hh_1[118]
 + c2.v[30]*MainFormSLS->hh_1[122]
 + c2.v[31]*MainFormSLS->hh_1[126]
 + c2.v[32]*MainFormSLS->hh_1[130]
 + c2.v[33]*MainFormSLS->hh_1[134]
 + c2.v[34]*MainFormSLS->hh_1[138]
 + c2.v[35]*MainFormSLS->hh_1[142]
 + c2.v[36]*MainFormSLS->hh_1[146]
 + c2.v[37]*MainFormSLS->hh_1[150]
 + c2.v[38]*MainFormSLS->hh_1[154]
 + c2.v[39]*MainFormSLS->hh_1[158]
 + c2.v[40]*MainFormSLS->hh_1[2]
 + c2.v[41]*MainFormSLS->hh_1[6]
 + c2.v[42]*MainFormSLS->hh_1[10]
 + c2.v[43]*MainFormSLS->hh_1[14]
 + c2.v[44]*MainFormSLS->hh_1[18]
 + c2.v[45]*MainFormSLS->hh_1[22]
 + c2.v[46]*MainFormSLS->hh_1[26]
 + c2.v[47]*MainFormSLS->hh_1[30]
 + c2.v[48]*MainFormSLS->hh_1[34]
 + c2.v[49]*MainFormSLS->hh_1[38]
 + c2.v[50]*MainFormSLS->hh_1[42]
 + c2.v[51]*MainFormSLS->hh_1[46]
 + c2.v[52]*MainFormSLS->hh_1[50]
 + c2.v[53]*MainFormSLS->hh_1[54]
 + c2.v[54]*MainFormSLS->hh_1[58]
 + c2.v[55]*MainFormSLS->hh_1[62]
 + c2.v[56]*MainFormSLS->hh_1[66]
 + c2.v[57]*MainFormSLS->hh_1[70]
 + c2.v[58]*MainFormSLS->hh_1[74]
 + c2.v[59]*MainFormSLS->hh_1[78]
 + c2.v[60]*MainFormSLS->hh_1[82]
 + c2.v[61]*MainFormSLS->hh_1[86]
 + c2.v[62]*MainFormSLS->hh_1[90]
 + c2.v[63]*MainFormSLS->hh_1[94]
 + c2.v[64]*MainFormSLS->hh_1[98]
 + c2.v[65]*MainFormSLS->hh_1[102]
 + c2.v[66]*MainFormSLS->hh_1[106]
 + c2.v[67]*MainFormSLS->hh_1[110]
 + c2.v[68]*MainFormSLS->hh_1[114]
 + c2.v[69]*MainFormSLS->hh_1[118]
 + c2.v[70]*MainFormSLS->hh_1[122]
 + c2.v[71]*MainFormSLS->hh_1[126]
 + c2.v[72]*MainFormSLS->hh_1[130]
 + c2.v[73]*MainFormSLS->hh_1[134]
 + c2.v[74]*MainFormSLS->hh_1[138]
 + c2.v[75]*MainFormSLS->hh_1[142]
 + c2.v[76]*MainFormSLS->hh_1[146]
 + c2.v[77]*MainFormSLS->hh_1[150]
 + c2.v[78]*MainFormSLS->hh_1[154]
 + c2.v[79]*MainFormSLS->hh_1[158];
s/=N_2;
out.push_back(s);
//������ 3
s =c2.v[0]*MainFormSLS->hh_1[3]
 + c2.v[1]*MainFormSLS->hh_1[9]
 + c2.v[2]*MainFormSLS->hh_1[15]
 + c2.v[3]*MainFormSLS->hh_1[21]
 + c2.v[4]*MainFormSLS->hh_1[27]
 + c2.v[5]*MainFormSLS->hh_1[33]
 + c2.v[6]*MainFormSLS->hh_1[39]
 + c2.v[7]*MainFormSLS->hh_1[45]
 + c2.v[8]*MainFormSLS->hh_1[51]
 + c2.v[9]*MainFormSLS->hh_1[57]
 + c2.v[10]*MainFormSLS->hh_1[63]
 + c2.v[11]*MainFormSLS->hh_1[69]
 + c2.v[12]*MainFormSLS->hh_1[75]
 + c2.v[13]*MainFormSLS->hh_1[81]
 + c2.v[14]*MainFormSLS->hh_1[87]
 + c2.v[15]*MainFormSLS->hh_1[93]
 + c2.v[16]*MainFormSLS->hh_1[99]
 + c2.v[17]*MainFormSLS->hh_1[105]
 + c2.v[18]*MainFormSLS->hh_1[111]
 + c2.v[19]*MainFormSLS->hh_1[117]
 + c2.v[20]*MainFormSLS->hh_1[123]
 + c2.v[21]*MainFormSLS->hh_1[129]
 + c2.v[22]*MainFormSLS->hh_1[135]
 + c2.v[23]*MainFormSLS->hh_1[141]
 + c2.v[24]*MainFormSLS->hh_1[147]
 + c2.v[25]*MainFormSLS->hh_1[153]
 + c2.v[26]*MainFormSLS->hh_1[159]
 + c2.v[27]*MainFormSLS->hh_1[5]
 + c2.v[28]*MainFormSLS->hh_1[11]
 + c2.v[29]*MainFormSLS->hh_1[17]
 + c2.v[30]*MainFormSLS->hh_1[23]
 + c2.v[31]*MainFormSLS->hh_1[29]
 + c2.v[32]*MainFormSLS->hh_1[35]
 + c2.v[33]*MainFormSLS->hh_1[41]
 + c2.v[34]*MainFormSLS->hh_1[47]
 + c2.v[35]*MainFormSLS->hh_1[53]
 + c2.v[36]*MainFormSLS->hh_1[59]
 + c2.v[37]*MainFormSLS->hh_1[65]
 + c2.v[38]*MainFormSLS->hh_1[71]
 + c2.v[39]*MainFormSLS->hh_1[77]
 + c2.v[40]*MainFormSLS->hh_1[83]
 + c2.v[41]*MainFormSLS->hh_1[89]
 + c2.v[42]*MainFormSLS->hh_1[95]
 + c2.v[43]*MainFormSLS->hh_1[101]
 + c2.v[44]*MainFormSLS->hh_1[107]
 + c2.v[45]*MainFormSLS->hh_1[113]
 + c2.v[46]*MainFormSLS->hh_1[119]
 + c2.v[47]*MainFormSLS->hh_1[125]
 + c2.v[48]*MainFormSLS->hh_1[131]
 + c2.v[49]*MainFormSLS->hh_1[137]
 + c2.v[50]*MainFormSLS->hh_1[143]
 + c2.v[51]*MainFormSLS->hh_1[149]
 + c2.v[52]*MainFormSLS->hh_1[155]
 + c2.v[53]*MainFormSLS->hh_1[1]
 + c2.v[54]*MainFormSLS->hh_1[7]
 + c2.v[55]*MainFormSLS->hh_1[13]
 + c2.v[56]*MainFormSLS->hh_1[19]
 + c2.v[57]*MainFormSLS->hh_1[25]
 + c2.v[58]*MainFormSLS->hh_1[31]
 + c2.v[59]*MainFormSLS->hh_1[37]
 + c2.v[60]*MainFormSLS->hh_1[43]
 + c2.v[61]*MainFormSLS->hh_1[49]
 + c2.v[62]*MainFormSLS->hh_1[55]
 + c2.v[63]*MainFormSLS->hh_1[61]
 + c2.v[64]*MainFormSLS->hh_1[67]
 + c2.v[65]*MainFormSLS->hh_1[73]
 + c2.v[66]*MainFormSLS->hh_1[79]
 + c2.v[67]*MainFormSLS->hh_1[85]
 + c2.v[68]*MainFormSLS->hh_1[91]
 + c2.v[69]*MainFormSLS->hh_1[97]
 + c2.v[70]*MainFormSLS->hh_1[103]
 + c2.v[71]*MainFormSLS->hh_1[109]
 + c2.v[72]*MainFormSLS->hh_1[115]
 + c2.v[73]*MainFormSLS->hh_1[121]
 + c2.v[74]*MainFormSLS->hh_1[127]
 + c2.v[75]*MainFormSLS->hh_1[133]
 + c2.v[76]*MainFormSLS->hh_1[139]
 + c2.v[77]*MainFormSLS->hh_1[145]
 + c2.v[78]*MainFormSLS->hh_1[151]
 + c2.v[79]*MainFormSLS->hh_1[157];
s/=N_2;
out.push_back(s);
//������ 4
s =c2.v[0]*MainFormSLS->hh_1[4]
 + c2.v[1]*MainFormSLS->hh_1[12]
 + c2.v[2]*MainFormSLS->hh_1[20]
 + c2.v[3]*MainFormSLS->hh_1[28]
 + c2.v[4]*MainFormSLS->hh_1[36]
 + c2.v[5]*MainFormSLS->hh_1[44]
 + c2.v[6]*MainFormSLS->hh_1[52]
 + c2.v[7]*MainFormSLS->hh_1[60]
 + c2.v[8]*MainFormSLS->hh_1[68]
 + c2.v[9]*MainFormSLS->hh_1[76]
 + c2.v[10]*MainFormSLS->hh_1[84]
 + c2.v[11]*MainFormSLS->hh_1[92]
 + c2.v[12]*MainFormSLS->hh_1[100]
 + c2.v[13]*MainFormSLS->hh_1[108]
 + c2.v[14]*MainFormSLS->hh_1[116]
 + c2.v[15]*MainFormSLS->hh_1[124]
 + c2.v[16]*MainFormSLS->hh_1[132]
 + c2.v[17]*MainFormSLS->hh_1[140]
 + c2.v[18]*MainFormSLS->hh_1[148]
 + c2.v[19]*MainFormSLS->hh_1[156]
 + c2.v[20]*MainFormSLS->hh_1[4]
 + c2.v[21]*MainFormSLS->hh_1[12]
 + c2.v[22]*MainFormSLS->hh_1[20]
 + c2.v[23]*MainFormSLS->hh_1[28]
 + c2.v[24]*MainFormSLS->hh_1[36]
 + c2.v[25]*MainFormSLS->hh_1[44]
 + c2.v[26]*MainFormSLS->hh_1[52]
 + c2.v[27]*MainFormSLS->hh_1[60]
 + c2.v[28]*MainFormSLS->hh_1[68]
 + c2.v[29]*MainFormSLS->hh_1[76]
 + c2.v[30]*MainFormSLS->hh_1[84]
 + c2.v[31]*MainFormSLS->hh_1[92]
 + c2.v[32]*MainFormSLS->hh_1[100]
 + c2.v[33]*MainFormSLS->hh_1[108]
 + c2.v[34]*MainFormSLS->hh_1[116]
 + c2.v[35]*MainFormSLS->hh_1[124]
 + c2.v[36]*MainFormSLS->hh_1[132]
 + c2.v[37]*MainFormSLS->hh_1[140]
 + c2.v[38]*MainFormSLS->hh_1[148]
 + c2.v[39]*MainFormSLS->hh_1[156]
 + c2.v[40]*MainFormSLS->hh_1[4]
 + c2.v[41]*MainFormSLS->hh_1[12]
 + c2.v[42]*MainFormSLS->hh_1[20]
 + c2.v[43]*MainFormSLS->hh_1[28]
 + c2.v[44]*MainFormSLS->hh_1[36]
 + c2.v[45]*MainFormSLS->hh_1[44]
 + c2.v[46]*MainFormSLS->hh_1[52]
 + c2.v[47]*MainFormSLS->hh_1[60]
 + c2.v[48]*MainFormSLS->hh_1[68]
 + c2.v[49]*MainFormSLS->hh_1[76]
 + c2.v[50]*MainFormSLS->hh_1[84]
 + c2.v[51]*MainFormSLS->hh_1[92]
 + c2.v[52]*MainFormSLS->hh_1[100]
 + c2.v[53]*MainFormSLS->hh_1[108]
 + c2.v[54]*MainFormSLS->hh_1[116]
 + c2.v[55]*MainFormSLS->hh_1[124]
 + c2.v[56]*MainFormSLS->hh_1[132]
 + c2.v[57]*MainFormSLS->hh_1[140]
 + c2.v[58]*MainFormSLS->hh_1[148]
 + c2.v[59]*MainFormSLS->hh_1[156]
 + c2.v[60]*MainFormSLS->hh_1[4]
 + c2.v[61]*MainFormSLS->hh_1[12]
 + c2.v[62]*MainFormSLS->hh_1[20]
 + c2.v[63]*MainFormSLS->hh_1[28]
 + c2.v[64]*MainFormSLS->hh_1[36]
 + c2.v[65]*MainFormSLS->hh_1[44]
 + c2.v[66]*MainFormSLS->hh_1[52]
 + c2.v[67]*MainFormSLS->hh_1[60]
 + c2.v[68]*MainFormSLS->hh_1[68]
 + c2.v[69]*MainFormSLS->hh_1[76]
 + c2.v[70]*MainFormSLS->hh_1[84]
 + c2.v[71]*MainFormSLS->hh_1[92]
 + c2.v[72]*MainFormSLS->hh_1[100]
 + c2.v[73]*MainFormSLS->hh_1[108]
 + c2.v[74]*MainFormSLS->hh_1[116]
 + c2.v[75]*MainFormSLS->hh_1[124]
 + c2.v[76]*MainFormSLS->hh_1[132]
 + c2.v[77]*MainFormSLS->hh_1[140]
 + c2.v[78]*MainFormSLS->hh_1[148]
 + c2.v[79]*MainFormSLS->hh_1[156];
s/=N_2;
out.push_back(s);
//������ 5
s =c2.v[0]*MainFormSLS->hh_1[5]
 + c2.v[1]*MainFormSLS->hh_1[15]
 + c2.v[2]*MainFormSLS->hh_1[25]
 + c2.v[3]*MainFormSLS->hh_1[35]
 + c2.v[4]*MainFormSLS->hh_1[45]
 + c2.v[5]*MainFormSLS->hh_1[55]
 + c2.v[6]*MainFormSLS->hh_1[65]
 + c2.v[7]*MainFormSLS->hh_1[75]
 + c2.v[8]*MainFormSLS->hh_1[85]
 + c2.v[9]*MainFormSLS->hh_1[95]
 + c2.v[10]*MainFormSLS->hh_1[105]
 + c2.v[11]*MainFormSLS->hh_1[115]
 + c2.v[12]*MainFormSLS->hh_1[125]
 + c2.v[13]*MainFormSLS->hh_1[135]
 + c2.v[14]*MainFormSLS->hh_1[145]
 + c2.v[15]*MainFormSLS->hh_1[155]
 + c2.v[16]*MainFormSLS->hh_1[5]
 + c2.v[17]*MainFormSLS->hh_1[15]
 + c2.v[18]*MainFormSLS->hh_1[25]
 + c2.v[19]*MainFormSLS->hh_1[35]
 + c2.v[20]*MainFormSLS->hh_1[45]
 + c2.v[21]*MainFormSLS->hh_1[55]
 + c2.v[22]*MainFormSLS->hh_1[65]
 + c2.v[23]*MainFormSLS->hh_1[75]
 + c2.v[24]*MainFormSLS->hh_1[85]
 + c2.v[25]*MainFormSLS->hh_1[95]
 + c2.v[26]*MainFormSLS->hh_1[105]
 + c2.v[27]*MainFormSLS->hh_1[115]
 + c2.v[28]*MainFormSLS->hh_1[125]
 + c2.v[29]*MainFormSLS->hh_1[135]
 + c2.v[30]*MainFormSLS->hh_1[145]
 + c2.v[31]*MainFormSLS->hh_1[155]
 + c2.v[32]*MainFormSLS->hh_1[5]
 + c2.v[33]*MainFormSLS->hh_1[15]
 + c2.v[34]*MainFormSLS->hh_1[25]
 + c2.v[35]*MainFormSLS->hh_1[35]
 + c2.v[36]*MainFormSLS->hh_1[45]
 + c2.v[37]*MainFormSLS->hh_1[55]
 + c2.v[38]*MainFormSLS->hh_1[65]
 + c2.v[39]*MainFormSLS->hh_1[75]
 + c2.v[40]*MainFormSLS->hh_1[85]
 + c2.v[41]*MainFormSLS->hh_1[95]
 + c2.v[42]*MainFormSLS->hh_1[105]
 + c2.v[43]*MainFormSLS->hh_1[115]
 + c2.v[44]*MainFormSLS->hh_1[125]
 + c2.v[45]*MainFormSLS->hh_1[135]
 + c2.v[46]*MainFormSLS->hh_1[145]
 + c2.v[47]*MainFormSLS->hh_1[155]
 + c2.v[48]*MainFormSLS->hh_1[5]
 + c2.v[49]*MainFormSLS->hh_1[15]
 + c2.v[50]*MainFormSLS->hh_1[25]
 + c2.v[51]*MainFormSLS->hh_1[35]
 + c2.v[52]*MainFormSLS->hh_1[45]
 + c2.v[53]*MainFormSLS->hh_1[55]
 + c2.v[54]*MainFormSLS->hh_1[65]
 + c2.v[55]*MainFormSLS->hh_1[75]
 + c2.v[56]*MainFormSLS->hh_1[85]
 + c2.v[57]*MainFormSLS->hh_1[95]
 + c2.v[58]*MainFormSLS->hh_1[105]
 + c2.v[59]*MainFormSLS->hh_1[115]
 + c2.v[60]*MainFormSLS->hh_1[125]
 + c2.v[61]*MainFormSLS->hh_1[135]
 + c2.v[62]*MainFormSLS->hh_1[145]
 + c2.v[63]*MainFormSLS->hh_1[155]
 + c2.v[64]*MainFormSLS->hh_1[5]
 + c2.v[65]*MainFormSLS->hh_1[15]
 + c2.v[66]*MainFormSLS->hh_1[25]
 + c2.v[67]*MainFormSLS->hh_1[35]
 + c2.v[68]*MainFormSLS->hh_1[45]
 + c2.v[69]*MainFormSLS->hh_1[55]
 + c2.v[70]*MainFormSLS->hh_1[65]
 + c2.v[71]*MainFormSLS->hh_1[75]
 + c2.v[72]*MainFormSLS->hh_1[85]
 + c2.v[73]*MainFormSLS->hh_1[95]
 + c2.v[74]*MainFormSLS->hh_1[105]
 + c2.v[75]*MainFormSLS->hh_1[115]
 + c2.v[76]*MainFormSLS->hh_1[125]
 + c2.v[77]*MainFormSLS->hh_1[135]
 + c2.v[78]*MainFormSLS->hh_1[145]
 + c2.v[79]*MainFormSLS->hh_1[155];
s/=N_2;
out.push_back(s);
//������ 6
s =c2.v[0]*MainFormSLS->hh_1[6]
 + c2.v[1]*MainFormSLS->hh_1[18]
 + c2.v[2]*MainFormSLS->hh_1[30]
 + c2.v[3]*MainFormSLS->hh_1[42]
 + c2.v[4]*MainFormSLS->hh_1[54]
 + c2.v[5]*MainFormSLS->hh_1[66]
 + c2.v[6]*MainFormSLS->hh_1[78]
 + c2.v[7]*MainFormSLS->hh_1[90]
 + c2.v[8]*MainFormSLS->hh_1[102]
 + c2.v[9]*MainFormSLS->hh_1[114]
 + c2.v[10]*MainFormSLS->hh_1[126]
 + c2.v[11]*MainFormSLS->hh_1[138]
 + c2.v[12]*MainFormSLS->hh_1[150]
 + c2.v[13]*MainFormSLS->hh_1[2]
 + c2.v[14]*MainFormSLS->hh_1[14]
 + c2.v[15]*MainFormSLS->hh_1[26]
 + c2.v[16]*MainFormSLS->hh_1[38]
 + c2.v[17]*MainFormSLS->hh_1[50]
 + c2.v[18]*MainFormSLS->hh_1[62]
 + c2.v[19]*MainFormSLS->hh_1[74]
 + c2.v[20]*MainFormSLS->hh_1[86]
 + c2.v[21]*MainFormSLS->hh_1[98]
 + c2.v[22]*MainFormSLS->hh_1[110]
 + c2.v[23]*MainFormSLS->hh_1[122]
 + c2.v[24]*MainFormSLS->hh_1[134]
 + c2.v[25]*MainFormSLS->hh_1[146]
 + c2.v[26]*MainFormSLS->hh_1[158]
 + c2.v[27]*MainFormSLS->hh_1[10]
 + c2.v[28]*MainFormSLS->hh_1[22]
 + c2.v[29]*MainFormSLS->hh_1[34]
 + c2.v[30]*MainFormSLS->hh_1[46]
 + c2.v[31]*MainFormSLS->hh_1[58]
 + c2.v[32]*MainFormSLS->hh_1[70]
 + c2.v[33]*MainFormSLS->hh_1[82]
 + c2.v[34]*MainFormSLS->hh_1[94]
 + c2.v[35]*MainFormSLS->hh_1[106]
 + c2.v[36]*MainFormSLS->hh_1[118]
 + c2.v[37]*MainFormSLS->hh_1[130]
 + c2.v[38]*MainFormSLS->hh_1[142]
 + c2.v[39]*MainFormSLS->hh_1[154]
 + c2.v[40]*MainFormSLS->hh_1[6]
 + c2.v[41]*MainFormSLS->hh_1[18]
 + c2.v[42]*MainFormSLS->hh_1[30]
 + c2.v[43]*MainFormSLS->hh_1[42]
 + c2.v[44]*MainFormSLS->hh_1[54]
 + c2.v[45]*MainFormSLS->hh_1[66]
 + c2.v[46]*MainFormSLS->hh_1[78]
 + c2.v[47]*MainFormSLS->hh_1[90]
 + c2.v[48]*MainFormSLS->hh_1[102]
 + c2.v[49]*MainFormSLS->hh_1[114]
 + c2.v[50]*MainFormSLS->hh_1[126]
 + c2.v[51]*MainFormSLS->hh_1[138]
 + c2.v[52]*MainFormSLS->hh_1[150]
 + c2.v[53]*MainFormSLS->hh_1[2]
 + c2.v[54]*MainFormSLS->hh_1[14]
 + c2.v[55]*MainFormSLS->hh_1[26]
 + c2.v[56]*MainFormSLS->hh_1[38]
 + c2.v[57]*MainFormSLS->hh_1[50]
 + c2.v[58]*MainFormSLS->hh_1[62]
 + c2.v[59]*MainFormSLS->hh_1[74]
 + c2.v[60]*MainFormSLS->hh_1[86]
 + c2.v[61]*MainFormSLS->hh_1[98]
 + c2.v[62]*MainFormSLS->hh_1[110]
 + c2.v[63]*MainFormSLS->hh_1[122]
 + c2.v[64]*MainFormSLS->hh_1[134]
 + c2.v[65]*MainFormSLS->hh_1[146]
 + c2.v[66]*MainFormSLS->hh_1[158]
 + c2.v[67]*MainFormSLS->hh_1[10]
 + c2.v[68]*MainFormSLS->hh_1[22]
 + c2.v[69]*MainFormSLS->hh_1[34]
 + c2.v[70]*MainFormSLS->hh_1[46]
 + c2.v[71]*MainFormSLS->hh_1[58]
 + c2.v[72]*MainFormSLS->hh_1[70]
 + c2.v[73]*MainFormSLS->hh_1[82]
 + c2.v[74]*MainFormSLS->hh_1[94]
 + c2.v[75]*MainFormSLS->hh_1[106]
 + c2.v[76]*MainFormSLS->hh_1[118]
 + c2.v[77]*MainFormSLS->hh_1[130]
 + c2.v[78]*MainFormSLS->hh_1[142]
 + c2.v[79]*MainFormSLS->hh_1[154];
s/=N_2;
out.push_back(s);
//������ 7
s =c2.v[0]*MainFormSLS->hh_1[7]
 + c2.v[1]*MainFormSLS->hh_1[21]
 + c2.v[2]*MainFormSLS->hh_1[35]
 + c2.v[3]*MainFormSLS->hh_1[49]
 + c2.v[4]*MainFormSLS->hh_1[63]
 + c2.v[5]*MainFormSLS->hh_1[77]
 + c2.v[6]*MainFormSLS->hh_1[91]
 + c2.v[7]*MainFormSLS->hh_1[105]
 + c2.v[8]*MainFormSLS->hh_1[119]
 + c2.v[9]*MainFormSLS->hh_1[133]
 + c2.v[10]*MainFormSLS->hh_1[147]
 + c2.v[11]*MainFormSLS->hh_1[1]
 + c2.v[12]*MainFormSLS->hh_1[15]
 + c2.v[13]*MainFormSLS->hh_1[29]
 + c2.v[14]*MainFormSLS->hh_1[43]
 + c2.v[15]*MainFormSLS->hh_1[57]
 + c2.v[16]*MainFormSLS->hh_1[71]
 + c2.v[17]*MainFormSLS->hh_1[85]
 + c2.v[18]*MainFormSLS->hh_1[99]
 + c2.v[19]*MainFormSLS->hh_1[113]
 + c2.v[20]*MainFormSLS->hh_1[127]
 + c2.v[21]*MainFormSLS->hh_1[141]
 + c2.v[22]*MainFormSLS->hh_1[155]
 + c2.v[23]*MainFormSLS->hh_1[9]
 + c2.v[24]*MainFormSLS->hh_1[23]
 + c2.v[25]*MainFormSLS->hh_1[37]
 + c2.v[26]*MainFormSLS->hh_1[51]
 + c2.v[27]*MainFormSLS->hh_1[65]
 + c2.v[28]*MainFormSLS->hh_1[79]
 + c2.v[29]*MainFormSLS->hh_1[93]
 + c2.v[30]*MainFormSLS->hh_1[107]
 + c2.v[31]*MainFormSLS->hh_1[121]
 + c2.v[32]*MainFormSLS->hh_1[135]
 + c2.v[33]*MainFormSLS->hh_1[149]
 + c2.v[34]*MainFormSLS->hh_1[3]
 + c2.v[35]*MainFormSLS->hh_1[17]
 + c2.v[36]*MainFormSLS->hh_1[31]
 + c2.v[37]*MainFormSLS->hh_1[45]
 + c2.v[38]*MainFormSLS->hh_1[59]
 + c2.v[39]*MainFormSLS->hh_1[73]
 + c2.v[40]*MainFormSLS->hh_1[87]
 + c2.v[41]*MainFormSLS->hh_1[101]
 + c2.v[42]*MainFormSLS->hh_1[115]
 + c2.v[43]*MainFormSLS->hh_1[129]
 + c2.v[44]*MainFormSLS->hh_1[143]
 + c2.v[45]*MainFormSLS->hh_1[157]
 + c2.v[46]*MainFormSLS->hh_1[11]
 + c2.v[47]*MainFormSLS->hh_1[25]
 + c2.v[48]*MainFormSLS->hh_1[39]
 + c2.v[49]*MainFormSLS->hh_1[53]
 + c2.v[50]*MainFormSLS->hh_1[67]
 + c2.v[51]*MainFormSLS->hh_1[81]
 + c2.v[52]*MainFormSLS->hh_1[95]
 + c2.v[53]*MainFormSLS->hh_1[109]
 + c2.v[54]*MainFormSLS->hh_1[123]
 + c2.v[55]*MainFormSLS->hh_1[137]
 + c2.v[56]*MainFormSLS->hh_1[151]
 + c2.v[57]*MainFormSLS->hh_1[5]
 + c2.v[58]*MainFormSLS->hh_1[19]
 + c2.v[59]*MainFormSLS->hh_1[33]
 + c2.v[60]*MainFormSLS->hh_1[47]
 + c2.v[61]*MainFormSLS->hh_1[61]
 + c2.v[62]*MainFormSLS->hh_1[75]
 + c2.v[63]*MainFormSLS->hh_1[89]
 + c2.v[64]*MainFormSLS->hh_1[103]
 + c2.v[65]*MainFormSLS->hh_1[117]
 + c2.v[66]*MainFormSLS->hh_1[131]
 + c2.v[67]*MainFormSLS->hh_1[145]
 + c2.v[68]*MainFormSLS->hh_1[159]
 + c2.v[69]*MainFormSLS->hh_1[13]
 + c2.v[70]*MainFormSLS->hh_1[27]
 + c2.v[71]*MainFormSLS->hh_1[41]
 + c2.v[72]*MainFormSLS->hh_1[55]
 + c2.v[73]*MainFormSLS->hh_1[69]
 + c2.v[74]*MainFormSLS->hh_1[83]
 + c2.v[75]*MainFormSLS->hh_1[97]
 + c2.v[76]*MainFormSLS->hh_1[111]
 + c2.v[77]*MainFormSLS->hh_1[125]
 + c2.v[78]*MainFormSLS->hh_1[139]
 + c2.v[79]*MainFormSLS->hh_1[153];
s/=N_2;
out.push_back(s);
//������ 8
s =c2.v[0]*MainFormSLS->hh_1[8]
 + c2.v[1]*MainFormSLS->hh_1[24]
 + c2.v[2]*MainFormSLS->hh_1[40]
 + c2.v[3]*MainFormSLS->hh_1[56]
 + c2.v[4]*MainFormSLS->hh_1[72]
 + c2.v[5]*MainFormSLS->hh_1[88]
 + c2.v[6]*MainFormSLS->hh_1[104]
 + c2.v[7]*MainFormSLS->hh_1[120]
 + c2.v[8]*MainFormSLS->hh_1[136]
 + c2.v[9]*MainFormSLS->hh_1[152]
 + c2.v[10]*MainFormSLS->hh_1[8]
 + c2.v[11]*MainFormSLS->hh_1[24]
 + c2.v[12]*MainFormSLS->hh_1[40]
 + c2.v[13]*MainFormSLS->hh_1[56]
 + c2.v[14]*MainFormSLS->hh_1[72]
 + c2.v[15]*MainFormSLS->hh_1[88]
 + c2.v[16]*MainFormSLS->hh_1[104]
 + c2.v[17]*MainFormSLS->hh_1[120]
 + c2.v[18]*MainFormSLS->hh_1[136]
 + c2.v[19]*MainFormSLS->hh_1[152]
 + c2.v[20]*MainFormSLS->hh_1[8]
 + c2.v[21]*MainFormSLS->hh_1[24]
 + c2.v[22]*MainFormSLS->hh_1[40]
 + c2.v[23]*MainFormSLS->hh_1[56]
 + c2.v[24]*MainFormSLS->hh_1[72]
 + c2.v[25]*MainFormSLS->hh_1[88]
 + c2.v[26]*MainFormSLS->hh_1[104]
 + c2.v[27]*MainFormSLS->hh_1[120]
 + c2.v[28]*MainFormSLS->hh_1[136]
 + c2.v[29]*MainFormSLS->hh_1[152]
 + c2.v[30]*MainFormSLS->hh_1[8]
 + c2.v[31]*MainFormSLS->hh_1[24]
 + c2.v[32]*MainFormSLS->hh_1[40]
 + c2.v[33]*MainFormSLS->hh_1[56]
 + c2.v[34]*MainFormSLS->hh_1[72]
 + c2.v[35]*MainFormSLS->hh_1[88]
 + c2.v[36]*MainFormSLS->hh_1[104]
 + c2.v[37]*MainFormSLS->hh_1[120]
 + c2.v[38]*MainFormSLS->hh_1[136]
 + c2.v[39]*MainFormSLS->hh_1[152]
 + c2.v[40]*MainFormSLS->hh_1[8]
 + c2.v[41]*MainFormSLS->hh_1[24]
 + c2.v[42]*MainFormSLS->hh_1[40]
 + c2.v[43]*MainFormSLS->hh_1[56]
 + c2.v[44]*MainFormSLS->hh_1[72]
 + c2.v[45]*MainFormSLS->hh_1[88]
 + c2.v[46]*MainFormSLS->hh_1[104]
 + c2.v[47]*MainFormSLS->hh_1[120]
 + c2.v[48]*MainFormSLS->hh_1[136]
 + c2.v[49]*MainFormSLS->hh_1[152]
 + c2.v[50]*MainFormSLS->hh_1[8]
 + c2.v[51]*MainFormSLS->hh_1[24]
 + c2.v[52]*MainFormSLS->hh_1[40]
 + c2.v[53]*MainFormSLS->hh_1[56]
 + c2.v[54]*MainFormSLS->hh_1[72]
 + c2.v[55]*MainFormSLS->hh_1[88]
 + c2.v[56]*MainFormSLS->hh_1[104]
 + c2.v[57]*MainFormSLS->hh_1[120]
 + c2.v[58]*MainFormSLS->hh_1[136]
 + c2.v[59]*MainFormSLS->hh_1[152]
 + c2.v[60]*MainFormSLS->hh_1[8]
 + c2.v[61]*MainFormSLS->hh_1[24]
 + c2.v[62]*MainFormSLS->hh_1[40]
 + c2.v[63]*MainFormSLS->hh_1[56]
 + c2.v[64]*MainFormSLS->hh_1[72]
 + c2.v[65]*MainFormSLS->hh_1[88]
 + c2.v[66]*MainFormSLS->hh_1[104]
 + c2.v[67]*MainFormSLS->hh_1[120]
 + c2.v[68]*MainFormSLS->hh_1[136]
 + c2.v[69]*MainFormSLS->hh_1[152]
 + c2.v[70]*MainFormSLS->hh_1[8]
 + c2.v[71]*MainFormSLS->hh_1[24]
 + c2.v[72]*MainFormSLS->hh_1[40]
 + c2.v[73]*MainFormSLS->hh_1[56]
 + c2.v[74]*MainFormSLS->hh_1[72]
 + c2.v[75]*MainFormSLS->hh_1[88]
 + c2.v[76]*MainFormSLS->hh_1[104]
 + c2.v[77]*MainFormSLS->hh_1[120]
 + c2.v[78]*MainFormSLS->hh_1[136]
 + c2.v[79]*MainFormSLS->hh_1[152];
s/=N_2;
out.push_back(s);
//������ 9
s =c2.v[0]*MainFormSLS->hh_1[9]
 + c2.v[1]*MainFormSLS->hh_1[27]
 + c2.v[2]*MainFormSLS->hh_1[45]
 + c2.v[3]*MainFormSLS->hh_1[63]
 + c2.v[4]*MainFormSLS->hh_1[81]
 + c2.v[5]*MainFormSLS->hh_1[99]
 + c2.v[6]*MainFormSLS->hh_1[117]
 + c2.v[7]*MainFormSLS->hh_1[135]
 + c2.v[8]*MainFormSLS->hh_1[153]
 + c2.v[9]*MainFormSLS->hh_1[11]
 + c2.v[10]*MainFormSLS->hh_1[29]
 + c2.v[11]*MainFormSLS->hh_1[47]
 + c2.v[12]*MainFormSLS->hh_1[65]
 + c2.v[13]*MainFormSLS->hh_1[83]
 + c2.v[14]*MainFormSLS->hh_1[101]
 + c2.v[15]*MainFormSLS->hh_1[119]
 + c2.v[16]*MainFormSLS->hh_1[137]
 + c2.v[17]*MainFormSLS->hh_1[155]
 + c2.v[18]*MainFormSLS->hh_1[13]
 + c2.v[19]*MainFormSLS->hh_1[31]
 + c2.v[20]*MainFormSLS->hh_1[49]
 + c2.v[21]*MainFormSLS->hh_1[67]
 + c2.v[22]*MainFormSLS->hh_1[85]
 + c2.v[23]*MainFormSLS->hh_1[103]
 + c2.v[24]*MainFormSLS->hh_1[121]
 + c2.v[25]*MainFormSLS->hh_1[139]
 + c2.v[26]*MainFormSLS->hh_1[157]
 + c2.v[27]*MainFormSLS->hh_1[15]
 + c2.v[28]*MainFormSLS->hh_1[33]
 + c2.v[29]*MainFormSLS->hh_1[51]
 + c2.v[30]*MainFormSLS->hh_1[69]
 + c2.v[31]*MainFormSLS->hh_1[87]
 + c2.v[32]*MainFormSLS->hh_1[105]
 + c2.v[33]*MainFormSLS->hh_1[123]
 + c2.v[34]*MainFormSLS->hh_1[141]
 + c2.v[35]*MainFormSLS->hh_1[159]
 + c2.v[36]*MainFormSLS->hh_1[17]
 + c2.v[37]*MainFormSLS->hh_1[35]
 + c2.v[38]*MainFormSLS->hh_1[53]
 + c2.v[39]*MainFormSLS->hh_1[71]
 + c2.v[40]*MainFormSLS->hh_1[89]
 + c2.v[41]*MainFormSLS->hh_1[107]
 + c2.v[42]*MainFormSLS->hh_1[125]
 + c2.v[43]*MainFormSLS->hh_1[143]
 + c2.v[44]*MainFormSLS->hh_1[1]
 + c2.v[45]*MainFormSLS->hh_1[19]
 + c2.v[46]*MainFormSLS->hh_1[37]
 + c2.v[47]*MainFormSLS->hh_1[55]
 + c2.v[48]*MainFormSLS->hh_1[73]
 + c2.v[49]*MainFormSLS->hh_1[91]
 + c2.v[50]*MainFormSLS->hh_1[109]
 + c2.v[51]*MainFormSLS->hh_1[127]
 + c2.v[52]*MainFormSLS->hh_1[145]
 + c2.v[53]*MainFormSLS->hh_1[3]
 + c2.v[54]*MainFormSLS->hh_1[21]
 + c2.v[55]*MainFormSLS->hh_1[39]
 + c2.v[56]*MainFormSLS->hh_1[57]
 + c2.v[57]*MainFormSLS->hh_1[75]
 + c2.v[58]*MainFormSLS->hh_1[93]
 + c2.v[59]*MainFormSLS->hh_1[111]
 + c2.v[60]*MainFormSLS->hh_1[129]
 + c2.v[61]*MainFormSLS->hh_1[147]
 + c2.v[62]*MainFormSLS->hh_1[5]
 + c2.v[63]*MainFormSLS->hh_1[23]
 + c2.v[64]*MainFormSLS->hh_1[41]
 + c2.v[65]*MainFormSLS->hh_1[59]
 + c2.v[66]*MainFormSLS->hh_1[77]
 + c2.v[67]*MainFormSLS->hh_1[95]
 + c2.v[68]*MainFormSLS->hh_1[113]
 + c2.v[69]*MainFormSLS->hh_1[131]
 + c2.v[70]*MainFormSLS->hh_1[149]
 + c2.v[71]*MainFormSLS->hh_1[7]
 + c2.v[72]*MainFormSLS->hh_1[25]
 + c2.v[73]*MainFormSLS->hh_1[43]
 + c2.v[74]*MainFormSLS->hh_1[61]
 + c2.v[75]*MainFormSLS->hh_1[79]
 + c2.v[76]*MainFormSLS->hh_1[97]
 + c2.v[77]*MainFormSLS->hh_1[115]
 + c2.v[78]*MainFormSLS->hh_1[133]
 + c2.v[79]*MainFormSLS->hh_1[151];
s/=N_2;
out.push_back(s);
//������ 10
s =c2.v[0]*MainFormSLS->hh_1[10]
 + c2.v[1]*MainFormSLS->hh_1[30]
 + c2.v[2]*MainFormSLS->hh_1[50]
 + c2.v[3]*MainFormSLS->hh_1[70]
 + c2.v[4]*MainFormSLS->hh_1[90]
 + c2.v[5]*MainFormSLS->hh_1[110]
 + c2.v[6]*MainFormSLS->hh_1[130]
 + c2.v[7]*MainFormSLS->hh_1[150]
 + c2.v[8]*MainFormSLS->hh_1[10]
 + c2.v[9]*MainFormSLS->hh_1[30]
 + c2.v[10]*MainFormSLS->hh_1[50]
 + c2.v[11]*MainFormSLS->hh_1[70]
 + c2.v[12]*MainFormSLS->hh_1[90]
 + c2.v[13]*MainFormSLS->hh_1[110]
 + c2.v[14]*MainFormSLS->hh_1[130]
 + c2.v[15]*MainFormSLS->hh_1[150]
 + c2.v[16]*MainFormSLS->hh_1[10]
 + c2.v[17]*MainFormSLS->hh_1[30]
 + c2.v[18]*MainFormSLS->hh_1[50]
 + c2.v[19]*MainFormSLS->hh_1[70]
 + c2.v[20]*MainFormSLS->hh_1[90]
 + c2.v[21]*MainFormSLS->hh_1[110]
 + c2.v[22]*MainFormSLS->hh_1[130]
 + c2.v[23]*MainFormSLS->hh_1[150]
 + c2.v[24]*MainFormSLS->hh_1[10]
 + c2.v[25]*MainFormSLS->hh_1[30]
 + c2.v[26]*MainFormSLS->hh_1[50]
 + c2.v[27]*MainFormSLS->hh_1[70]
 + c2.v[28]*MainFormSLS->hh_1[90]
 + c2.v[29]*MainFormSLS->hh_1[110]
 + c2.v[30]*MainFormSLS->hh_1[130]
 + c2.v[31]*MainFormSLS->hh_1[150]
 + c2.v[32]*MainFormSLS->hh_1[10]
 + c2.v[33]*MainFormSLS->hh_1[30]
 + c2.v[34]*MainFormSLS->hh_1[50]
 + c2.v[35]*MainFormSLS->hh_1[70]
 + c2.v[36]*MainFormSLS->hh_1[90]
 + c2.v[37]*MainFormSLS->hh_1[110]
 + c2.v[38]*MainFormSLS->hh_1[130]
 + c2.v[39]*MainFormSLS->hh_1[150]
 + c2.v[40]*MainFormSLS->hh_1[10]
 + c2.v[41]*MainFormSLS->hh_1[30]
 + c2.v[42]*MainFormSLS->hh_1[50]
 + c2.v[43]*MainFormSLS->hh_1[70]
 + c2.v[44]*MainFormSLS->hh_1[90]
 + c2.v[45]*MainFormSLS->hh_1[110]
 + c2.v[46]*MainFormSLS->hh_1[130]
 + c2.v[47]*MainFormSLS->hh_1[150]
 + c2.v[48]*MainFormSLS->hh_1[10]
 + c2.v[49]*MainFormSLS->hh_1[30]
 + c2.v[50]*MainFormSLS->hh_1[50]
 + c2.v[51]*MainFormSLS->hh_1[70]
 + c2.v[52]*MainFormSLS->hh_1[90]
 + c2.v[53]*MainFormSLS->hh_1[110]
 + c2.v[54]*MainFormSLS->hh_1[130]
 + c2.v[55]*MainFormSLS->hh_1[150]
 + c2.v[56]*MainFormSLS->hh_1[10]
 + c2.v[57]*MainFormSLS->hh_1[30]
 + c2.v[58]*MainFormSLS->hh_1[50]
 + c2.v[59]*MainFormSLS->hh_1[70]
 + c2.v[60]*MainFormSLS->hh_1[90]
 + c2.v[61]*MainFormSLS->hh_1[110]
 + c2.v[62]*MainFormSLS->hh_1[130]
 + c2.v[63]*MainFormSLS->hh_1[150]
 + c2.v[64]*MainFormSLS->hh_1[10]
 + c2.v[65]*MainFormSLS->hh_1[30]
 + c2.v[66]*MainFormSLS->hh_1[50]
 + c2.v[67]*MainFormSLS->hh_1[70]
 + c2.v[68]*MainFormSLS->hh_1[90]
 + c2.v[69]*MainFormSLS->hh_1[110]
 + c2.v[70]*MainFormSLS->hh_1[130]
 + c2.v[71]*MainFormSLS->hh_1[150]
 + c2.v[72]*MainFormSLS->hh_1[10]
 + c2.v[73]*MainFormSLS->hh_1[30]
 + c2.v[74]*MainFormSLS->hh_1[50]
 + c2.v[75]*MainFormSLS->hh_1[70]
 + c2.v[76]*MainFormSLS->hh_1[90]
 + c2.v[77]*MainFormSLS->hh_1[110]
 + c2.v[78]*MainFormSLS->hh_1[130]
 + c2.v[79]*MainFormSLS->hh_1[150];
s/=N_2;
out.push_back(s);
//������ 11
s =c2.v[0]*MainFormSLS->hh_1[11]
 + c2.v[1]*MainFormSLS->hh_1[33]
 + c2.v[2]*MainFormSLS->hh_1[55]
 + c2.v[3]*MainFormSLS->hh_1[77]
 + c2.v[4]*MainFormSLS->hh_1[99]
 + c2.v[5]*MainFormSLS->hh_1[121]
 + c2.v[6]*MainFormSLS->hh_1[143]
 + c2.v[7]*MainFormSLS->hh_1[5]
 + c2.v[8]*MainFormSLS->hh_1[27]
 + c2.v[9]*MainFormSLS->hh_1[49]
 + c2.v[10]*MainFormSLS->hh_1[71]
 + c2.v[11]*MainFormSLS->hh_1[93]
 + c2.v[12]*MainFormSLS->hh_1[115]
 + c2.v[13]*MainFormSLS->hh_1[137]
 + c2.v[14]*MainFormSLS->hh_1[159]
 + c2.v[15]*MainFormSLS->hh_1[21]
 + c2.v[16]*MainFormSLS->hh_1[43]
 + c2.v[17]*MainFormSLS->hh_1[65]
 + c2.v[18]*MainFormSLS->hh_1[87]
 + c2.v[19]*MainFormSLS->hh_1[109]
 + c2.v[20]*MainFormSLS->hh_1[131]
 + c2.v[21]*MainFormSLS->hh_1[153]
 + c2.v[22]*MainFormSLS->hh_1[15]
 + c2.v[23]*MainFormSLS->hh_1[37]
 + c2.v[24]*MainFormSLS->hh_1[59]
 + c2.v[25]*MainFormSLS->hh_1[81]
 + c2.v[26]*MainFormSLS->hh_1[103]
 + c2.v[27]*MainFormSLS->hh_1[125]
 + c2.v[28]*MainFormSLS->hh_1[147]
 + c2.v[29]*MainFormSLS->hh_1[9]
 + c2.v[30]*MainFormSLS->hh_1[31]
 + c2.v[31]*MainFormSLS->hh_1[53]
 + c2.v[32]*MainFormSLS->hh_1[75]
 + c2.v[33]*MainFormSLS->hh_1[97]
 + c2.v[34]*MainFormSLS->hh_1[119]
 + c2.v[35]*MainFormSLS->hh_1[141]
 + c2.v[36]*MainFormSLS->hh_1[3]
 + c2.v[37]*MainFormSLS->hh_1[25]
 + c2.v[38]*MainFormSLS->hh_1[47]
 + c2.v[39]*MainFormSLS->hh_1[69]
 + c2.v[40]*MainFormSLS->hh_1[91]
 + c2.v[41]*MainFormSLS->hh_1[113]
 + c2.v[42]*MainFormSLS->hh_1[135]
 + c2.v[43]*MainFormSLS->hh_1[157]
 + c2.v[44]*MainFormSLS->hh_1[19]
 + c2.v[45]*MainFormSLS->hh_1[41]
 + c2.v[46]*MainFormSLS->hh_1[63]
 + c2.v[47]*MainFormSLS->hh_1[85]
 + c2.v[48]*MainFormSLS->hh_1[107]
 + c2.v[49]*MainFormSLS->hh_1[129]
 + c2.v[50]*MainFormSLS->hh_1[151]
 + c2.v[51]*MainFormSLS->hh_1[13]
 + c2.v[52]*MainFormSLS->hh_1[35]
 + c2.v[53]*MainFormSLS->hh_1[57]
 + c2.v[54]*MainFormSLS->hh_1[79]
 + c2.v[55]*MainFormSLS->hh_1[101]
 + c2.v[56]*MainFormSLS->hh_1[123]
 + c2.v[57]*MainFormSLS->hh_1[145]
 + c2.v[58]*MainFormSLS->hh_1[7]
 + c2.v[59]*MainFormSLS->hh_1[29]
 + c2.v[60]*MainFormSLS->hh_1[51]
 + c2.v[61]*MainFormSLS->hh_1[73]
 + c2.v[62]*MainFormSLS->hh_1[95]
 + c2.v[63]*MainFormSLS->hh_1[117]
 + c2.v[64]*MainFormSLS->hh_1[139]
 + c2.v[65]*MainFormSLS->hh_1[1]
 + c2.v[66]*MainFormSLS->hh_1[23]
 + c2.v[67]*MainFormSLS->hh_1[45]
 + c2.v[68]*MainFormSLS->hh_1[67]
 + c2.v[69]*MainFormSLS->hh_1[89]
 + c2.v[70]*MainFormSLS->hh_1[111]
 + c2.v[71]*MainFormSLS->hh_1[133]
 + c2.v[72]*MainFormSLS->hh_1[155]
 + c2.v[73]*MainFormSLS->hh_1[17]
 + c2.v[74]*MainFormSLS->hh_1[39]
 + c2.v[75]*MainFormSLS->hh_1[61]
 + c2.v[76]*MainFormSLS->hh_1[83]
 + c2.v[77]*MainFormSLS->hh_1[105]
 + c2.v[78]*MainFormSLS->hh_1[127]
 + c2.v[79]*MainFormSLS->hh_1[149];
s/=N_2;
out.push_back(s);
//������ 12
s =c2.v[0]*MainFormSLS->hh_1[12]
 + c2.v[1]*MainFormSLS->hh_1[36]
 + c2.v[2]*MainFormSLS->hh_1[60]
 + c2.v[3]*MainFormSLS->hh_1[84]
 + c2.v[4]*MainFormSLS->hh_1[108]
 + c2.v[5]*MainFormSLS->hh_1[132]
 + c2.v[6]*MainFormSLS->hh_1[156]
 + c2.v[7]*MainFormSLS->hh_1[20]
 + c2.v[8]*MainFormSLS->hh_1[44]
 + c2.v[9]*MainFormSLS->hh_1[68]
 + c2.v[10]*MainFormSLS->hh_1[92]
 + c2.v[11]*MainFormSLS->hh_1[116]
 + c2.v[12]*MainFormSLS->hh_1[140]
 + c2.v[13]*MainFormSLS->hh_1[4]
 + c2.v[14]*MainFormSLS->hh_1[28]
 + c2.v[15]*MainFormSLS->hh_1[52]
 + c2.v[16]*MainFormSLS->hh_1[76]
 + c2.v[17]*MainFormSLS->hh_1[100]
 + c2.v[18]*MainFormSLS->hh_1[124]
 + c2.v[19]*MainFormSLS->hh_1[148]
 + c2.v[20]*MainFormSLS->hh_1[12]
 + c2.v[21]*MainFormSLS->hh_1[36]
 + c2.v[22]*MainFormSLS->hh_1[60]
 + c2.v[23]*MainFormSLS->hh_1[84]
 + c2.v[24]*MainFormSLS->hh_1[108]
 + c2.v[25]*MainFormSLS->hh_1[132]
 + c2.v[26]*MainFormSLS->hh_1[156]
 + c2.v[27]*MainFormSLS->hh_1[20]
 + c2.v[28]*MainFormSLS->hh_1[44]
 + c2.v[29]*MainFormSLS->hh_1[68]
 + c2.v[30]*MainFormSLS->hh_1[92]
 + c2.v[31]*MainFormSLS->hh_1[116]
 + c2.v[32]*MainFormSLS->hh_1[140]
 + c2.v[33]*MainFormSLS->hh_1[4]
 + c2.v[34]*MainFormSLS->hh_1[28]
 + c2.v[35]*MainFormSLS->hh_1[52]
 + c2.v[36]*MainFormSLS->hh_1[76]
 + c2.v[37]*MainFormSLS->hh_1[100]
 + c2.v[38]*MainFormSLS->hh_1[124]
 + c2.v[39]*MainFormSLS->hh_1[148]
 + c2.v[40]*MainFormSLS->hh_1[12]
 + c2.v[41]*MainFormSLS->hh_1[36]
 + c2.v[42]*MainFormSLS->hh_1[60]
 + c2.v[43]*MainFormSLS->hh_1[84]
 + c2.v[44]*MainFormSLS->hh_1[108]
 + c2.v[45]*MainFormSLS->hh_1[132]
 + c2.v[46]*MainFormSLS->hh_1[156]
 + c2.v[47]*MainFormSLS->hh_1[20]
 + c2.v[48]*MainFormSLS->hh_1[44]
 + c2.v[49]*MainFormSLS->hh_1[68]
 + c2.v[50]*MainFormSLS->hh_1[92]
 + c2.v[51]*MainFormSLS->hh_1[116]
 + c2.v[52]*MainFormSLS->hh_1[140]
 + c2.v[53]*MainFormSLS->hh_1[4]
 + c2.v[54]*MainFormSLS->hh_1[28]
 + c2.v[55]*MainFormSLS->hh_1[52]
 + c2.v[56]*MainFormSLS->hh_1[76]
 + c2.v[57]*MainFormSLS->hh_1[100]
 + c2.v[58]*MainFormSLS->hh_1[124]
 + c2.v[59]*MainFormSLS->hh_1[148]
 + c2.v[60]*MainFormSLS->hh_1[12]
 + c2.v[61]*MainFormSLS->hh_1[36]
 + c2.v[62]*MainFormSLS->hh_1[60]
 + c2.v[63]*MainFormSLS->hh_1[84]
 + c2.v[64]*MainFormSLS->hh_1[108]
 + c2.v[65]*MainFormSLS->hh_1[132]
 + c2.v[66]*MainFormSLS->hh_1[156]
 + c2.v[67]*MainFormSLS->hh_1[20]
 + c2.v[68]*MainFormSLS->hh_1[44]
 + c2.v[69]*MainFormSLS->hh_1[68]
 + c2.v[70]*MainFormSLS->hh_1[92]
 + c2.v[71]*MainFormSLS->hh_1[116]
 + c2.v[72]*MainFormSLS->hh_1[140]
 + c2.v[73]*MainFormSLS->hh_1[4]
 + c2.v[74]*MainFormSLS->hh_1[28]
 + c2.v[75]*MainFormSLS->hh_1[52]
 + c2.v[76]*MainFormSLS->hh_1[76]
 + c2.v[77]*MainFormSLS->hh_1[100]
 + c2.v[78]*MainFormSLS->hh_1[124]
 + c2.v[79]*MainFormSLS->hh_1[148];
s/=N_2;
out.push_back(s);
//������ 13
s =c2.v[0]*MainFormSLS->hh_1[13]
 + c2.v[1]*MainFormSLS->hh_1[39]
 + c2.v[2]*MainFormSLS->hh_1[65]
 + c2.v[3]*MainFormSLS->hh_1[91]
 + c2.v[4]*MainFormSLS->hh_1[117]
 + c2.v[5]*MainFormSLS->hh_1[143]
 + c2.v[6]*MainFormSLS->hh_1[9]
 + c2.v[7]*MainFormSLS->hh_1[35]
 + c2.v[8]*MainFormSLS->hh_1[61]
 + c2.v[9]*MainFormSLS->hh_1[87]
 + c2.v[10]*MainFormSLS->hh_1[113]
 + c2.v[11]*MainFormSLS->hh_1[139]
 + c2.v[12]*MainFormSLS->hh_1[5]
 + c2.v[13]*MainFormSLS->hh_1[31]
 + c2.v[14]*MainFormSLS->hh_1[57]
 + c2.v[15]*MainFormSLS->hh_1[83]
 + c2.v[16]*MainFormSLS->hh_1[109]
 + c2.v[17]*MainFormSLS->hh_1[135]
 + c2.v[18]*MainFormSLS->hh_1[1]
 + c2.v[19]*MainFormSLS->hh_1[27]
 + c2.v[20]*MainFormSLS->hh_1[53]
 + c2.v[21]*MainFormSLS->hh_1[79]
 + c2.v[22]*MainFormSLS->hh_1[105]
 + c2.v[23]*MainFormSLS->hh_1[131]
 + c2.v[24]*MainFormSLS->hh_1[157]
 + c2.v[25]*MainFormSLS->hh_1[23]
 + c2.v[26]*MainFormSLS->hh_1[49]
 + c2.v[27]*MainFormSLS->hh_1[75]
 + c2.v[28]*MainFormSLS->hh_1[101]
 + c2.v[29]*MainFormSLS->hh_1[127]
 + c2.v[30]*MainFormSLS->hh_1[153]
 + c2.v[31]*MainFormSLS->hh_1[19]
 + c2.v[32]*MainFormSLS->hh_1[45]
 + c2.v[33]*MainFormSLS->hh_1[71]
 + c2.v[34]*MainFormSLS->hh_1[97]
 + c2.v[35]*MainFormSLS->hh_1[123]
 + c2.v[36]*MainFormSLS->hh_1[149]
 + c2.v[37]*MainFormSLS->hh_1[15]
 + c2.v[38]*MainFormSLS->hh_1[41]
 + c2.v[39]*MainFormSLS->hh_1[67]
 + c2.v[40]*MainFormSLS->hh_1[93]
 + c2.v[41]*MainFormSLS->hh_1[119]
 + c2.v[42]*MainFormSLS->hh_1[145]
 + c2.v[43]*MainFormSLS->hh_1[11]
 + c2.v[44]*MainFormSLS->hh_1[37]
 + c2.v[45]*MainFormSLS->hh_1[63]
 + c2.v[46]*MainFormSLS->hh_1[89]
 + c2.v[47]*MainFormSLS->hh_1[115]
 + c2.v[48]*MainFormSLS->hh_1[141]
 + c2.v[49]*MainFormSLS->hh_1[7]
 + c2.v[50]*MainFormSLS->hh_1[33]
 + c2.v[51]*MainFormSLS->hh_1[59]
 + c2.v[52]*MainFormSLS->hh_1[85]
 + c2.v[53]*MainFormSLS->hh_1[111]
 + c2.v[54]*MainFormSLS->hh_1[137]
 + c2.v[55]*MainFormSLS->hh_1[3]
 + c2.v[56]*MainFormSLS->hh_1[29]
 + c2.v[57]*MainFormSLS->hh_1[55]
 + c2.v[58]*MainFormSLS->hh_1[81]
 + c2.v[59]*MainFormSLS->hh_1[107]
 + c2.v[60]*MainFormSLS->hh_1[133]
 + c2.v[61]*MainFormSLS->hh_1[159]
 + c2.v[62]*MainFormSLS->hh_1[25]
 + c2.v[63]*MainFormSLS->hh_1[51]
 + c2.v[64]*MainFormSLS->hh_1[77]
 + c2.v[65]*MainFormSLS->hh_1[103]
 + c2.v[66]*MainFormSLS->hh_1[129]
 + c2.v[67]*MainFormSLS->hh_1[155]
 + c2.v[68]*MainFormSLS->hh_1[21]
 + c2.v[69]*MainFormSLS->hh_1[47]
 + c2.v[70]*MainFormSLS->hh_1[73]
 + c2.v[71]*MainFormSLS->hh_1[99]
 + c2.v[72]*MainFormSLS->hh_1[125]
 + c2.v[73]*MainFormSLS->hh_1[151]
 + c2.v[74]*MainFormSLS->hh_1[17]
 + c2.v[75]*MainFormSLS->hh_1[43]
 + c2.v[76]*MainFormSLS->hh_1[69]
 + c2.v[77]*MainFormSLS->hh_1[95]
 + c2.v[78]*MainFormSLS->hh_1[121]
 + c2.v[79]*MainFormSLS->hh_1[147];
s/=N_2;
out.push_back(s);
//������ 14
s =c2.v[0]*MainFormSLS->hh_1[14]
 + c2.v[1]*MainFormSLS->hh_1[42]
 + c2.v[2]*MainFormSLS->hh_1[70]
 + c2.v[3]*MainFormSLS->hh_1[98]
 + c2.v[4]*MainFormSLS->hh_1[126]
 + c2.v[5]*MainFormSLS->hh_1[154]
 + c2.v[6]*MainFormSLS->hh_1[22]
 + c2.v[7]*MainFormSLS->hh_1[50]
 + c2.v[8]*MainFormSLS->hh_1[78]
 + c2.v[9]*MainFormSLS->hh_1[106]
 + c2.v[10]*MainFormSLS->hh_1[134]
 + c2.v[11]*MainFormSLS->hh_1[2]
 + c2.v[12]*MainFormSLS->hh_1[30]
 + c2.v[13]*MainFormSLS->hh_1[58]
 + c2.v[14]*MainFormSLS->hh_1[86]
 + c2.v[15]*MainFormSLS->hh_1[114]
 + c2.v[16]*MainFormSLS->hh_1[142]
 + c2.v[17]*MainFormSLS->hh_1[10]
 + c2.v[18]*MainFormSLS->hh_1[38]
 + c2.v[19]*MainFormSLS->hh_1[66]
 + c2.v[20]*MainFormSLS->hh_1[94]
 + c2.v[21]*MainFormSLS->hh_1[122]
 + c2.v[22]*MainFormSLS->hh_1[150]
 + c2.v[23]*MainFormSLS->hh_1[18]
 + c2.v[24]*MainFormSLS->hh_1[46]
 + c2.v[25]*MainFormSLS->hh_1[74]
 + c2.v[26]*MainFormSLS->hh_1[102]
 + c2.v[27]*MainFormSLS->hh_1[130]
 + c2.v[28]*MainFormSLS->hh_1[158]
 + c2.v[29]*MainFormSLS->hh_1[26]
 + c2.v[30]*MainFormSLS->hh_1[54]
 + c2.v[31]*MainFormSLS->hh_1[82]
 + c2.v[32]*MainFormSLS->hh_1[110]
 + c2.v[33]*MainFormSLS->hh_1[138]
 + c2.v[34]*MainFormSLS->hh_1[6]
 + c2.v[35]*MainFormSLS->hh_1[34]
 + c2.v[36]*MainFormSLS->hh_1[62]
 + c2.v[37]*MainFormSLS->hh_1[90]
 + c2.v[38]*MainFormSLS->hh_1[118]
 + c2.v[39]*MainFormSLS->hh_1[146]
 + c2.v[40]*MainFormSLS->hh_1[14]
 + c2.v[41]*MainFormSLS->hh_1[42]
 + c2.v[42]*MainFormSLS->hh_1[70]
 + c2.v[43]*MainFormSLS->hh_1[98]
 + c2.v[44]*MainFormSLS->hh_1[126]
 + c2.v[45]*MainFormSLS->hh_1[154]
 + c2.v[46]*MainFormSLS->hh_1[22]
 + c2.v[47]*MainFormSLS->hh_1[50]
 + c2.v[48]*MainFormSLS->hh_1[78]
 + c2.v[49]*MainFormSLS->hh_1[106]
 + c2.v[50]*MainFormSLS->hh_1[134]
 + c2.v[51]*MainFormSLS->hh_1[2]
 + c2.v[52]*MainFormSLS->hh_1[30]
 + c2.v[53]*MainFormSLS->hh_1[58]
 + c2.v[54]*MainFormSLS->hh_1[86]
 + c2.v[55]*MainFormSLS->hh_1[114]
 + c2.v[56]*MainFormSLS->hh_1[142]
 + c2.v[57]*MainFormSLS->hh_1[10]
 + c2.v[58]*MainFormSLS->hh_1[38]
 + c2.v[59]*MainFormSLS->hh_1[66]
 + c2.v[60]*MainFormSLS->hh_1[94]
 + c2.v[61]*MainFormSLS->hh_1[122]
 + c2.v[62]*MainFormSLS->hh_1[150]
 + c2.v[63]*MainFormSLS->hh_1[18]
 + c2.v[64]*MainFormSLS->hh_1[46]
 + c2.v[65]*MainFormSLS->hh_1[74]
 + c2.v[66]*MainFormSLS->hh_1[102]
 + c2.v[67]*MainFormSLS->hh_1[130]
 + c2.v[68]*MainFormSLS->hh_1[158]
 + c2.v[69]*MainFormSLS->hh_1[26]
 + c2.v[70]*MainFormSLS->hh_1[54]
 + c2.v[71]*MainFormSLS->hh_1[82]
 + c2.v[72]*MainFormSLS->hh_1[110]
 + c2.v[73]*MainFormSLS->hh_1[138]
 + c2.v[74]*MainFormSLS->hh_1[6]
 + c2.v[75]*MainFormSLS->hh_1[34]
 + c2.v[76]*MainFormSLS->hh_1[62]
 + c2.v[77]*MainFormSLS->hh_1[90]
 + c2.v[78]*MainFormSLS->hh_1[118]
 + c2.v[79]*MainFormSLS->hh_1[146];
s/=N_2;
out.push_back(s);
//������ 15
s =c2.v[0]*MainFormSLS->hh_1[15]
 + c2.v[1]*MainFormSLS->hh_1[45]
 + c2.v[2]*MainFormSLS->hh_1[75]
 + c2.v[3]*MainFormSLS->hh_1[105]
 + c2.v[4]*MainFormSLS->hh_1[135]
 + c2.v[5]*MainFormSLS->hh_1[5]
 + c2.v[6]*MainFormSLS->hh_1[35]
 + c2.v[7]*MainFormSLS->hh_1[65]
 + c2.v[8]*MainFormSLS->hh_1[95]
 + c2.v[9]*MainFormSLS->hh_1[125]
 + c2.v[10]*MainFormSLS->hh_1[155]
 + c2.v[11]*MainFormSLS->hh_1[25]
 + c2.v[12]*MainFormSLS->hh_1[55]
 + c2.v[13]*MainFormSLS->hh_1[85]
 + c2.v[14]*MainFormSLS->hh_1[115]
 + c2.v[15]*MainFormSLS->hh_1[145]
 + c2.v[16]*MainFormSLS->hh_1[15]
 + c2.v[17]*MainFormSLS->hh_1[45]
 + c2.v[18]*MainFormSLS->hh_1[75]
 + c2.v[19]*MainFormSLS->hh_1[105]
 + c2.v[20]*MainFormSLS->hh_1[135]
 + c2.v[21]*MainFormSLS->hh_1[5]
 + c2.v[22]*MainFormSLS->hh_1[35]
 + c2.v[23]*MainFormSLS->hh_1[65]
 + c2.v[24]*MainFormSLS->hh_1[95]
 + c2.v[25]*MainFormSLS->hh_1[125]
 + c2.v[26]*MainFormSLS->hh_1[155]
 + c2.v[27]*MainFormSLS->hh_1[25]
 + c2.v[28]*MainFormSLS->hh_1[55]
 + c2.v[29]*MainFormSLS->hh_1[85]
 + c2.v[30]*MainFormSLS->hh_1[115]
 + c2.v[31]*MainFormSLS->hh_1[145]
 + c2.v[32]*MainFormSLS->hh_1[15]
 + c2.v[33]*MainFormSLS->hh_1[45]
 + c2.v[34]*MainFormSLS->hh_1[75]
 + c2.v[35]*MainFormSLS->hh_1[105]
 + c2.v[36]*MainFormSLS->hh_1[135]
 + c2.v[37]*MainFormSLS->hh_1[5]
 + c2.v[38]*MainFormSLS->hh_1[35]
 + c2.v[39]*MainFormSLS->hh_1[65]
 + c2.v[40]*MainFormSLS->hh_1[95]
 + c2.v[41]*MainFormSLS->hh_1[125]
 + c2.v[42]*MainFormSLS->hh_1[155]
 + c2.v[43]*MainFormSLS->hh_1[25]
 + c2.v[44]*MainFormSLS->hh_1[55]
 + c2.v[45]*MainFormSLS->hh_1[85]
 + c2.v[46]*MainFormSLS->hh_1[115]
 + c2.v[47]*MainFormSLS->hh_1[145]
 + c2.v[48]*MainFormSLS->hh_1[15]
 + c2.v[49]*MainFormSLS->hh_1[45]
 + c2.v[50]*MainFormSLS->hh_1[75]
 + c2.v[51]*MainFormSLS->hh_1[105]
 + c2.v[52]*MainFormSLS->hh_1[135]
 + c2.v[53]*MainFormSLS->hh_1[5]
 + c2.v[54]*MainFormSLS->hh_1[35]
 + c2.v[55]*MainFormSLS->hh_1[65]
 + c2.v[56]*MainFormSLS->hh_1[95]
 + c2.v[57]*MainFormSLS->hh_1[125]
 + c2.v[58]*MainFormSLS->hh_1[155]
 + c2.v[59]*MainFormSLS->hh_1[25]
 + c2.v[60]*MainFormSLS->hh_1[55]
 + c2.v[61]*MainFormSLS->hh_1[85]
 + c2.v[62]*MainFormSLS->hh_1[115]
 + c2.v[63]*MainFormSLS->hh_1[145]
 + c2.v[64]*MainFormSLS->hh_1[15]
 + c2.v[65]*MainFormSLS->hh_1[45]
 + c2.v[66]*MainFormSLS->hh_1[75]
 + c2.v[67]*MainFormSLS->hh_1[105]
 + c2.v[68]*MainFormSLS->hh_1[135]
 + c2.v[69]*MainFormSLS->hh_1[5]
 + c2.v[70]*MainFormSLS->hh_1[35]
 + c2.v[71]*MainFormSLS->hh_1[65]
 + c2.v[72]*MainFormSLS->hh_1[95]
 + c2.v[73]*MainFormSLS->hh_1[125]
 + c2.v[74]*MainFormSLS->hh_1[155]
 + c2.v[75]*MainFormSLS->hh_1[25]
 + c2.v[76]*MainFormSLS->hh_1[55]
 + c2.v[77]*MainFormSLS->hh_1[85]
 + c2.v[78]*MainFormSLS->hh_1[115]
 + c2.v[79]*MainFormSLS->hh_1[145];
s/=N_2;
out.push_back(s);
//������ 16
s =c2.v[0]*MainFormSLS->hh_1[16]
 + c2.v[1]*MainFormSLS->hh_1[48]
 + c2.v[2]*MainFormSLS->hh_1[80]
 + c2.v[3]*MainFormSLS->hh_1[112]
 + c2.v[4]*MainFormSLS->hh_1[144]
 + c2.v[5]*MainFormSLS->hh_1[16]
 + c2.v[6]*MainFormSLS->hh_1[48]
 + c2.v[7]*MainFormSLS->hh_1[80]
 + c2.v[8]*MainFormSLS->hh_1[112]
 + c2.v[9]*MainFormSLS->hh_1[144]
 + c2.v[10]*MainFormSLS->hh_1[16]
 + c2.v[11]*MainFormSLS->hh_1[48]
 + c2.v[12]*MainFormSLS->hh_1[80]
 + c2.v[13]*MainFormSLS->hh_1[112]
 + c2.v[14]*MainFormSLS->hh_1[144]
 + c2.v[15]*MainFormSLS->hh_1[16]
 + c2.v[16]*MainFormSLS->hh_1[48]
 + c2.v[17]*MainFormSLS->hh_1[80]
 + c2.v[18]*MainFormSLS->hh_1[112]
 + c2.v[19]*MainFormSLS->hh_1[144]
 + c2.v[20]*MainFormSLS->hh_1[16]
 + c2.v[21]*MainFormSLS->hh_1[48]
 + c2.v[22]*MainFormSLS->hh_1[80]
 + c2.v[23]*MainFormSLS->hh_1[112]
 + c2.v[24]*MainFormSLS->hh_1[144]
 + c2.v[25]*MainFormSLS->hh_1[16]
 + c2.v[26]*MainFormSLS->hh_1[48]
 + c2.v[27]*MainFormSLS->hh_1[80]
 + c2.v[28]*MainFormSLS->hh_1[112]
 + c2.v[29]*MainFormSLS->hh_1[144]
 + c2.v[30]*MainFormSLS->hh_1[16]
 + c2.v[31]*MainFormSLS->hh_1[48]
 + c2.v[32]*MainFormSLS->hh_1[80]
 + c2.v[33]*MainFormSLS->hh_1[112]
 + c2.v[34]*MainFormSLS->hh_1[144]
 + c2.v[35]*MainFormSLS->hh_1[16]
 + c2.v[36]*MainFormSLS->hh_1[48]
 + c2.v[37]*MainFormSLS->hh_1[80]
 + c2.v[38]*MainFormSLS->hh_1[112]
 + c2.v[39]*MainFormSLS->hh_1[144]
 + c2.v[40]*MainFormSLS->hh_1[16]
 + c2.v[41]*MainFormSLS->hh_1[48]
 + c2.v[42]*MainFormSLS->hh_1[80]
 + c2.v[43]*MainFormSLS->hh_1[112]
 + c2.v[44]*MainFormSLS->hh_1[144]
 + c2.v[45]*MainFormSLS->hh_1[16]
 + c2.v[46]*MainFormSLS->hh_1[48]
 + c2.v[47]*MainFormSLS->hh_1[80]
 + c2.v[48]*MainFormSLS->hh_1[112]
 + c2.v[49]*MainFormSLS->hh_1[144]
 + c2.v[50]*MainFormSLS->hh_1[16]
 + c2.v[51]*MainFormSLS->hh_1[48]
 + c2.v[52]*MainFormSLS->hh_1[80]
 + c2.v[53]*MainFormSLS->hh_1[112]
 + c2.v[54]*MainFormSLS->hh_1[144]
 + c2.v[55]*MainFormSLS->hh_1[16]
 + c2.v[56]*MainFormSLS->hh_1[48]
 + c2.v[57]*MainFormSLS->hh_1[80]
 + c2.v[58]*MainFormSLS->hh_1[112]
 + c2.v[59]*MainFormSLS->hh_1[144]
 + c2.v[60]*MainFormSLS->hh_1[16]
 + c2.v[61]*MainFormSLS->hh_1[48]
 + c2.v[62]*MainFormSLS->hh_1[80]
 + c2.v[63]*MainFormSLS->hh_1[112]
 + c2.v[64]*MainFormSLS->hh_1[144]
 + c2.v[65]*MainFormSLS->hh_1[16]
 + c2.v[66]*MainFormSLS->hh_1[48]
 + c2.v[67]*MainFormSLS->hh_1[80]
 + c2.v[68]*MainFormSLS->hh_1[112]
 + c2.v[69]*MainFormSLS->hh_1[144]
 + c2.v[70]*MainFormSLS->hh_1[16]
 + c2.v[71]*MainFormSLS->hh_1[48]
 + c2.v[72]*MainFormSLS->hh_1[80]
 + c2.v[73]*MainFormSLS->hh_1[112]
 + c2.v[74]*MainFormSLS->hh_1[144]
 + c2.v[75]*MainFormSLS->hh_1[16]
 + c2.v[76]*MainFormSLS->hh_1[48]
 + c2.v[77]*MainFormSLS->hh_1[80]
 + c2.v[78]*MainFormSLS->hh_1[112]
 + c2.v[79]*MainFormSLS->hh_1[144];
s/=N_2;
out.push_back(s);
//������ 17
s =c2.v[0]*MainFormSLS->hh_1[17]
 + c2.v[1]*MainFormSLS->hh_1[51]
 + c2.v[2]*MainFormSLS->hh_1[85]
 + c2.v[3]*MainFormSLS->hh_1[119]
 + c2.v[4]*MainFormSLS->hh_1[153]
 + c2.v[5]*MainFormSLS->hh_1[27]
 + c2.v[6]*MainFormSLS->hh_1[61]
 + c2.v[7]*MainFormSLS->hh_1[95]
 + c2.v[8]*MainFormSLS->hh_1[129]
 + c2.v[9]*MainFormSLS->hh_1[3]
 + c2.v[10]*MainFormSLS->hh_1[37]
 + c2.v[11]*MainFormSLS->hh_1[71]
 + c2.v[12]*MainFormSLS->hh_1[105]
 + c2.v[13]*MainFormSLS->hh_1[139]
 + c2.v[14]*MainFormSLS->hh_1[13]
 + c2.v[15]*MainFormSLS->hh_1[47]
 + c2.v[16]*MainFormSLS->hh_1[81]
 + c2.v[17]*MainFormSLS->hh_1[115]
 + c2.v[18]*MainFormSLS->hh_1[149]
 + c2.v[19]*MainFormSLS->hh_1[23]
 + c2.v[20]*MainFormSLS->hh_1[57]
 + c2.v[21]*MainFormSLS->hh_1[91]
 + c2.v[22]*MainFormSLS->hh_1[125]
 + c2.v[23]*MainFormSLS->hh_1[159]
 + c2.v[24]*MainFormSLS->hh_1[33]
 + c2.v[25]*MainFormSLS->hh_1[67]
 + c2.v[26]*MainFormSLS->hh_1[101]
 + c2.v[27]*MainFormSLS->hh_1[135]
 + c2.v[28]*MainFormSLS->hh_1[9]
 + c2.v[29]*MainFormSLS->hh_1[43]
 + c2.v[30]*MainFormSLS->hh_1[77]
 + c2.v[31]*MainFormSLS->hh_1[111]
 + c2.v[32]*MainFormSLS->hh_1[145]
 + c2.v[33]*MainFormSLS->hh_1[19]
 + c2.v[34]*MainFormSLS->hh_1[53]
 + c2.v[35]*MainFormSLS->hh_1[87]
 + c2.v[36]*MainFormSLS->hh_1[121]
 + c2.v[37]*MainFormSLS->hh_1[155]
 + c2.v[38]*MainFormSLS->hh_1[29]
 + c2.v[39]*MainFormSLS->hh_1[63]
 + c2.v[40]*MainFormSLS->hh_1[97]
 + c2.v[41]*MainFormSLS->hh_1[131]
 + c2.v[42]*MainFormSLS->hh_1[5]
 + c2.v[43]*MainFormSLS->hh_1[39]
 + c2.v[44]*MainFormSLS->hh_1[73]
 + c2.v[45]*MainFormSLS->hh_1[107]
 + c2.v[46]*MainFormSLS->hh_1[141]
 + c2.v[47]*MainFormSLS->hh_1[15]
 + c2.v[48]*MainFormSLS->hh_1[49]
 + c2.v[49]*MainFormSLS->hh_1[83]
 + c2.v[50]*MainFormSLS->hh_1[117]
 + c2.v[51]*MainFormSLS->hh_1[151]
 + c2.v[52]*MainFormSLS->hh_1[25]
 + c2.v[53]*MainFormSLS->hh_1[59]
 + c2.v[54]*MainFormSLS->hh_1[93]
 + c2.v[55]*MainFormSLS->hh_1[127]
 + c2.v[56]*MainFormSLS->hh_1[1]
 + c2.v[57]*MainFormSLS->hh_1[35]
 + c2.v[58]*MainFormSLS->hh_1[69]
 + c2.v[59]*MainFormSLS->hh_1[103]
 + c2.v[60]*MainFormSLS->hh_1[137]
 + c2.v[61]*MainFormSLS->hh_1[11]
 + c2.v[62]*MainFormSLS->hh_1[45]
 + c2.v[63]*MainFormSLS->hh_1[79]
 + c2.v[64]*MainFormSLS->hh_1[113]
 + c2.v[65]*MainFormSLS->hh_1[147]
 + c2.v[66]*MainFormSLS->hh_1[21]
 + c2.v[67]*MainFormSLS->hh_1[55]
 + c2.v[68]*MainFormSLS->hh_1[89]
 + c2.v[69]*MainFormSLS->hh_1[123]
 + c2.v[70]*MainFormSLS->hh_1[157]
 + c2.v[71]*MainFormSLS->hh_1[31]
 + c2.v[72]*MainFormSLS->hh_1[65]
 + c2.v[73]*MainFormSLS->hh_1[99]
 + c2.v[74]*MainFormSLS->hh_1[133]
 + c2.v[75]*MainFormSLS->hh_1[7]
 + c2.v[76]*MainFormSLS->hh_1[41]
 + c2.v[77]*MainFormSLS->hh_1[75]
 + c2.v[78]*MainFormSLS->hh_1[109]
 + c2.v[79]*MainFormSLS->hh_1[143];
s/=N_2;
out.push_back(s);
//������ 18
s =c2.v[0]*MainFormSLS->hh_1[18]
 + c2.v[1]*MainFormSLS->hh_1[54]
 + c2.v[2]*MainFormSLS->hh_1[90]
 + c2.v[3]*MainFormSLS->hh_1[126]
 + c2.v[4]*MainFormSLS->hh_1[2]
 + c2.v[5]*MainFormSLS->hh_1[38]
 + c2.v[6]*MainFormSLS->hh_1[74]
 + c2.v[7]*MainFormSLS->hh_1[110]
 + c2.v[8]*MainFormSLS->hh_1[146]
 + c2.v[9]*MainFormSLS->hh_1[22]
 + c2.v[10]*MainFormSLS->hh_1[58]
 + c2.v[11]*MainFormSLS->hh_1[94]
 + c2.v[12]*MainFormSLS->hh_1[130]
 + c2.v[13]*MainFormSLS->hh_1[6]
 + c2.v[14]*MainFormSLS->hh_1[42]
 + c2.v[15]*MainFormSLS->hh_1[78]
 + c2.v[16]*MainFormSLS->hh_1[114]
 + c2.v[17]*MainFormSLS->hh_1[150]
 + c2.v[18]*MainFormSLS->hh_1[26]
 + c2.v[19]*MainFormSLS->hh_1[62]
 + c2.v[20]*MainFormSLS->hh_1[98]
 + c2.v[21]*MainFormSLS->hh_1[134]
 + c2.v[22]*MainFormSLS->hh_1[10]
 + c2.v[23]*MainFormSLS->hh_1[46]
 + c2.v[24]*MainFormSLS->hh_1[82]
 + c2.v[25]*MainFormSLS->hh_1[118]
 + c2.v[26]*MainFormSLS->hh_1[154]
 + c2.v[27]*MainFormSLS->hh_1[30]
 + c2.v[28]*MainFormSLS->hh_1[66]
 + c2.v[29]*MainFormSLS->hh_1[102]
 + c2.v[30]*MainFormSLS->hh_1[138]
 + c2.v[31]*MainFormSLS->hh_1[14]
 + c2.v[32]*MainFormSLS->hh_1[50]
 + c2.v[33]*MainFormSLS->hh_1[86]
 + c2.v[34]*MainFormSLS->hh_1[122]
 + c2.v[35]*MainFormSLS->hh_1[158]
 + c2.v[36]*MainFormSLS->hh_1[34]
 + c2.v[37]*MainFormSLS->hh_1[70]
 + c2.v[38]*MainFormSLS->hh_1[106]
 + c2.v[39]*MainFormSLS->hh_1[142]
 + c2.v[40]*MainFormSLS->hh_1[18]
 + c2.v[41]*MainFormSLS->hh_1[54]
 + c2.v[42]*MainFormSLS->hh_1[90]
 + c2.v[43]*MainFormSLS->hh_1[126]
 + c2.v[44]*MainFormSLS->hh_1[2]
 + c2.v[45]*MainFormSLS->hh_1[38]
 + c2.v[46]*MainFormSLS->hh_1[74]
 + c2.v[47]*MainFormSLS->hh_1[110]
 + c2.v[48]*MainFormSLS->hh_1[146]
 + c2.v[49]*MainFormSLS->hh_1[22]
 + c2.v[50]*MainFormSLS->hh_1[58]
 + c2.v[51]*MainFormSLS->hh_1[94]
 + c2.v[52]*MainFormSLS->hh_1[130]
 + c2.v[53]*MainFormSLS->hh_1[6]
 + c2.v[54]*MainFormSLS->hh_1[42]
 + c2.v[55]*MainFormSLS->hh_1[78]
 + c2.v[56]*MainFormSLS->hh_1[114]
 + c2.v[57]*MainFormSLS->hh_1[150]
 + c2.v[58]*MainFormSLS->hh_1[26]
 + c2.v[59]*MainFormSLS->hh_1[62]
 + c2.v[60]*MainFormSLS->hh_1[98]
 + c2.v[61]*MainFormSLS->hh_1[134]
 + c2.v[62]*MainFormSLS->hh_1[10]
 + c2.v[63]*MainFormSLS->hh_1[46]
 + c2.v[64]*MainFormSLS->hh_1[82]
 + c2.v[65]*MainFormSLS->hh_1[118]
 + c2.v[66]*MainFormSLS->hh_1[154]
 + c2.v[67]*MainFormSLS->hh_1[30]
 + c2.v[68]*MainFormSLS->hh_1[66]
 + c2.v[69]*MainFormSLS->hh_1[102]
 + c2.v[70]*MainFormSLS->hh_1[138]
 + c2.v[71]*MainFormSLS->hh_1[14]
 + c2.v[72]*MainFormSLS->hh_1[50]
 + c2.v[73]*MainFormSLS->hh_1[86]
 + c2.v[74]*MainFormSLS->hh_1[122]
 + c2.v[75]*MainFormSLS->hh_1[158]
 + c2.v[76]*MainFormSLS->hh_1[34]
 + c2.v[77]*MainFormSLS->hh_1[70]
 + c2.v[78]*MainFormSLS->hh_1[106]
 + c2.v[79]*MainFormSLS->hh_1[142];
s/=N_2;
out.push_back(s);
//������ 19
s =c2.v[0]*MainFormSLS->hh_1[19]
 + c2.v[1]*MainFormSLS->hh_1[57]
 + c2.v[2]*MainFormSLS->hh_1[95]
 + c2.v[3]*MainFormSLS->hh_1[133]
 + c2.v[4]*MainFormSLS->hh_1[11]
 + c2.v[5]*MainFormSLS->hh_1[49]
 + c2.v[6]*MainFormSLS->hh_1[87]
 + c2.v[7]*MainFormSLS->hh_1[125]
 + c2.v[8]*MainFormSLS->hh_1[3]
 + c2.v[9]*MainFormSLS->hh_1[41]
 + c2.v[10]*MainFormSLS->hh_1[79]
 + c2.v[11]*MainFormSLS->hh_1[117]
 + c2.v[12]*MainFormSLS->hh_1[155]
 + c2.v[13]*MainFormSLS->hh_1[33]
 + c2.v[14]*MainFormSLS->hh_1[71]
 + c2.v[15]*MainFormSLS->hh_1[109]
 + c2.v[16]*MainFormSLS->hh_1[147]
 + c2.v[17]*MainFormSLS->hh_1[25]
 + c2.v[18]*MainFormSLS->hh_1[63]
 + c2.v[19]*MainFormSLS->hh_1[101]
 + c2.v[20]*MainFormSLS->hh_1[139]
 + c2.v[21]*MainFormSLS->hh_1[17]
 + c2.v[22]*MainFormSLS->hh_1[55]
 + c2.v[23]*MainFormSLS->hh_1[93]
 + c2.v[24]*MainFormSLS->hh_1[131]
 + c2.v[25]*MainFormSLS->hh_1[9]
 + c2.v[26]*MainFormSLS->hh_1[47]
 + c2.v[27]*MainFormSLS->hh_1[85]
 + c2.v[28]*MainFormSLS->hh_1[123]
 + c2.v[29]*MainFormSLS->hh_1[1]
 + c2.v[30]*MainFormSLS->hh_1[39]
 + c2.v[31]*MainFormSLS->hh_1[77]
 + c2.v[32]*MainFormSLS->hh_1[115]
 + c2.v[33]*MainFormSLS->hh_1[153]
 + c2.v[34]*MainFormSLS->hh_1[31]
 + c2.v[35]*MainFormSLS->hh_1[69]
 + c2.v[36]*MainFormSLS->hh_1[107]
 + c2.v[37]*MainFormSLS->hh_1[145]
 + c2.v[38]*MainFormSLS->hh_1[23]
 + c2.v[39]*MainFormSLS->hh_1[61]
 + c2.v[40]*MainFormSLS->hh_1[99]
 + c2.v[41]*MainFormSLS->hh_1[137]
 + c2.v[42]*MainFormSLS->hh_1[15]
 + c2.v[43]*MainFormSLS->hh_1[53]
 + c2.v[44]*MainFormSLS->hh_1[91]
 + c2.v[45]*MainFormSLS->hh_1[129]
 + c2.v[46]*MainFormSLS->hh_1[7]
 + c2.v[47]*MainFormSLS->hh_1[45]
 + c2.v[48]*MainFormSLS->hh_1[83]
 + c2.v[49]*MainFormSLS->hh_1[121]
 + c2.v[50]*MainFormSLS->hh_1[159]
 + c2.v[51]*MainFormSLS->hh_1[37]
 + c2.v[52]*MainFormSLS->hh_1[75]
 + c2.v[53]*MainFormSLS->hh_1[113]
 + c2.v[54]*MainFormSLS->hh_1[151]
 + c2.v[55]*MainFormSLS->hh_1[29]
 + c2.v[56]*MainFormSLS->hh_1[67]
 + c2.v[57]*MainFormSLS->hh_1[105]
 + c2.v[58]*MainFormSLS->hh_1[143]
 + c2.v[59]*MainFormSLS->hh_1[21]
 + c2.v[60]*MainFormSLS->hh_1[59]
 + c2.v[61]*MainFormSLS->hh_1[97]
 + c2.v[62]*MainFormSLS->hh_1[135]
 + c2.v[63]*MainFormSLS->hh_1[13]
 + c2.v[64]*MainFormSLS->hh_1[51]
 + c2.v[65]*MainFormSLS->hh_1[89]
 + c2.v[66]*MainFormSLS->hh_1[127]
 + c2.v[67]*MainFormSLS->hh_1[5]
 + c2.v[68]*MainFormSLS->hh_1[43]
 + c2.v[69]*MainFormSLS->hh_1[81]
 + c2.v[70]*MainFormSLS->hh_1[119]
 + c2.v[71]*MainFormSLS->hh_1[157]
 + c2.v[72]*MainFormSLS->hh_1[35]
 + c2.v[73]*MainFormSLS->hh_1[73]
 + c2.v[74]*MainFormSLS->hh_1[111]
 + c2.v[75]*MainFormSLS->hh_1[149]
 + c2.v[76]*MainFormSLS->hh_1[27]
 + c2.v[77]*MainFormSLS->hh_1[65]
 + c2.v[78]*MainFormSLS->hh_1[103]
 + c2.v[79]*MainFormSLS->hh_1[141];
s/=N_2;
out.push_back(s);
//������ 20
s =c2.v[0]*MainFormSLS->hh_1[20]
 + c2.v[1]*MainFormSLS->hh_1[60]
 + c2.v[2]*MainFormSLS->hh_1[100]
 + c2.v[3]*MainFormSLS->hh_1[140]
 + c2.v[4]*MainFormSLS->hh_1[20]
 + c2.v[5]*MainFormSLS->hh_1[60]
 + c2.v[6]*MainFormSLS->hh_1[100]
 + c2.v[7]*MainFormSLS->hh_1[140]
 + c2.v[8]*MainFormSLS->hh_1[20]
 + c2.v[9]*MainFormSLS->hh_1[60]
 + c2.v[10]*MainFormSLS->hh_1[100]
 + c2.v[11]*MainFormSLS->hh_1[140]
 + c2.v[12]*MainFormSLS->hh_1[20]
 + c2.v[13]*MainFormSLS->hh_1[60]
 + c2.v[14]*MainFormSLS->hh_1[100]
 + c2.v[15]*MainFormSLS->hh_1[140]
 + c2.v[16]*MainFormSLS->hh_1[20]
 + c2.v[17]*MainFormSLS->hh_1[60]
 + c2.v[18]*MainFormSLS->hh_1[100]
 + c2.v[19]*MainFormSLS->hh_1[140]
 + c2.v[20]*MainFormSLS->hh_1[20]
 + c2.v[21]*MainFormSLS->hh_1[60]
 + c2.v[22]*MainFormSLS->hh_1[100]
 + c2.v[23]*MainFormSLS->hh_1[140]
 + c2.v[24]*MainFormSLS->hh_1[20]
 + c2.v[25]*MainFormSLS->hh_1[60]
 + c2.v[26]*MainFormSLS->hh_1[100]
 + c2.v[27]*MainFormSLS->hh_1[140]
 + c2.v[28]*MainFormSLS->hh_1[20]
 + c2.v[29]*MainFormSLS->hh_1[60]
 + c2.v[30]*MainFormSLS->hh_1[100]
 + c2.v[31]*MainFormSLS->hh_1[140]
 + c2.v[32]*MainFormSLS->hh_1[20]
 + c2.v[33]*MainFormSLS->hh_1[60]
 + c2.v[34]*MainFormSLS->hh_1[100]
 + c2.v[35]*MainFormSLS->hh_1[140]
 + c2.v[36]*MainFormSLS->hh_1[20]
 + c2.v[37]*MainFormSLS->hh_1[60]
 + c2.v[38]*MainFormSLS->hh_1[100]
 + c2.v[39]*MainFormSLS->hh_1[140]
 + c2.v[40]*MainFormSLS->hh_1[20]
 + c2.v[41]*MainFormSLS->hh_1[60]
 + c2.v[42]*MainFormSLS->hh_1[100]
 + c2.v[43]*MainFormSLS->hh_1[140]
 + c2.v[44]*MainFormSLS->hh_1[20]
 + c2.v[45]*MainFormSLS->hh_1[60]
 + c2.v[46]*MainFormSLS->hh_1[100]
 + c2.v[47]*MainFormSLS->hh_1[140]
 + c2.v[48]*MainFormSLS->hh_1[20]
 + c2.v[49]*MainFormSLS->hh_1[60]
 + c2.v[50]*MainFormSLS->hh_1[100]
 + c2.v[51]*MainFormSLS->hh_1[140]
 + c2.v[52]*MainFormSLS->hh_1[20]
 + c2.v[53]*MainFormSLS->hh_1[60]
 + c2.v[54]*MainFormSLS->hh_1[100]
 + c2.v[55]*MainFormSLS->hh_1[140]
 + c2.v[56]*MainFormSLS->hh_1[20]
 + c2.v[57]*MainFormSLS->hh_1[60]
 + c2.v[58]*MainFormSLS->hh_1[100]
 + c2.v[59]*MainFormSLS->hh_1[140]
 + c2.v[60]*MainFormSLS->hh_1[20]
 + c2.v[61]*MainFormSLS->hh_1[60]
 + c2.v[62]*MainFormSLS->hh_1[100]
 + c2.v[63]*MainFormSLS->hh_1[140]
 + c2.v[64]*MainFormSLS->hh_1[20]
 + c2.v[65]*MainFormSLS->hh_1[60]
 + c2.v[66]*MainFormSLS->hh_1[100]
 + c2.v[67]*MainFormSLS->hh_1[140]
 + c2.v[68]*MainFormSLS->hh_1[20]
 + c2.v[69]*MainFormSLS->hh_1[60]
 + c2.v[70]*MainFormSLS->hh_1[100]
 + c2.v[71]*MainFormSLS->hh_1[140]
 + c2.v[72]*MainFormSLS->hh_1[20]
 + c2.v[73]*MainFormSLS->hh_1[60]
 + c2.v[74]*MainFormSLS->hh_1[100]
 + c2.v[75]*MainFormSLS->hh_1[140]
 + c2.v[76]*MainFormSLS->hh_1[20]
 + c2.v[77]*MainFormSLS->hh_1[60]
 + c2.v[78]*MainFormSLS->hh_1[100]
 + c2.v[79]*MainFormSLS->hh_1[140];
s/=N_2;
out.push_back(s);
//������ 21
s =c2.v[0]*MainFormSLS->hh_1[21]
 + c2.v[1]*MainFormSLS->hh_1[63]
 + c2.v[2]*MainFormSLS->hh_1[105]
 + c2.v[3]*MainFormSLS->hh_1[147]
 + c2.v[4]*MainFormSLS->hh_1[29]
 + c2.v[5]*MainFormSLS->hh_1[71]
 + c2.v[6]*MainFormSLS->hh_1[113]
 + c2.v[7]*MainFormSLS->hh_1[155]
 + c2.v[8]*MainFormSLS->hh_1[37]
 + c2.v[9]*MainFormSLS->hh_1[79]
 + c2.v[10]*MainFormSLS->hh_1[121]
 + c2.v[11]*MainFormSLS->hh_1[3]
 + c2.v[12]*MainFormSLS->hh_1[45]
 + c2.v[13]*MainFormSLS->hh_1[87]
 + c2.v[14]*MainFormSLS->hh_1[129]
 + c2.v[15]*MainFormSLS->hh_1[11]
 + c2.v[16]*MainFormSLS->hh_1[53]
 + c2.v[17]*MainFormSLS->hh_1[95]
 + c2.v[18]*MainFormSLS->hh_1[137]
 + c2.v[19]*MainFormSLS->hh_1[19]
 + c2.v[20]*MainFormSLS->hh_1[61]
 + c2.v[21]*MainFormSLS->hh_1[103]
 + c2.v[22]*MainFormSLS->hh_1[145]
 + c2.v[23]*MainFormSLS->hh_1[27]
 + c2.v[24]*MainFormSLS->hh_1[69]
 + c2.v[25]*MainFormSLS->hh_1[111]
 + c2.v[26]*MainFormSLS->hh_1[153]
 + c2.v[27]*MainFormSLS->hh_1[35]
 + c2.v[28]*MainFormSLS->hh_1[77]
 + c2.v[29]*MainFormSLS->hh_1[119]
 + c2.v[30]*MainFormSLS->hh_1[1]
 + c2.v[31]*MainFormSLS->hh_1[43]
 + c2.v[32]*MainFormSLS->hh_1[85]
 + c2.v[33]*MainFormSLS->hh_1[127]
 + c2.v[34]*MainFormSLS->hh_1[9]
 + c2.v[35]*MainFormSLS->hh_1[51]
 + c2.v[36]*MainFormSLS->hh_1[93]
 + c2.v[37]*MainFormSLS->hh_1[135]
 + c2.v[38]*MainFormSLS->hh_1[17]
 + c2.v[39]*MainFormSLS->hh_1[59]
 + c2.v[40]*MainFormSLS->hh_1[101]
 + c2.v[41]*MainFormSLS->hh_1[143]
 + c2.v[42]*MainFormSLS->hh_1[25]
 + c2.v[43]*MainFormSLS->hh_1[67]
 + c2.v[44]*MainFormSLS->hh_1[109]
 + c2.v[45]*MainFormSLS->hh_1[151]
 + c2.v[46]*MainFormSLS->hh_1[33]
 + c2.v[47]*MainFormSLS->hh_1[75]
 + c2.v[48]*MainFormSLS->hh_1[117]
 + c2.v[49]*MainFormSLS->hh_1[159]
 + c2.v[50]*MainFormSLS->hh_1[41]
 + c2.v[51]*MainFormSLS->hh_1[83]
 + c2.v[52]*MainFormSLS->hh_1[125]
 + c2.v[53]*MainFormSLS->hh_1[7]
 + c2.v[54]*MainFormSLS->hh_1[49]
 + c2.v[55]*MainFormSLS->hh_1[91]
 + c2.v[56]*MainFormSLS->hh_1[133]
 + c2.v[57]*MainFormSLS->hh_1[15]
 + c2.v[58]*MainFormSLS->hh_1[57]
 + c2.v[59]*MainFormSLS->hh_1[99]
 + c2.v[60]*MainFormSLS->hh_1[141]
 + c2.v[61]*MainFormSLS->hh_1[23]
 + c2.v[62]*MainFormSLS->hh_1[65]
 + c2.v[63]*MainFormSLS->hh_1[107]
 + c2.v[64]*MainFormSLS->hh_1[149]
 + c2.v[65]*MainFormSLS->hh_1[31]
 + c2.v[66]*MainFormSLS->hh_1[73]
 + c2.v[67]*MainFormSLS->hh_1[115]
 + c2.v[68]*MainFormSLS->hh_1[157]
 + c2.v[69]*MainFormSLS->hh_1[39]
 + c2.v[70]*MainFormSLS->hh_1[81]
 + c2.v[71]*MainFormSLS->hh_1[123]
 + c2.v[72]*MainFormSLS->hh_1[5]
 + c2.v[73]*MainFormSLS->hh_1[47]
 + c2.v[74]*MainFormSLS->hh_1[89]
 + c2.v[75]*MainFormSLS->hh_1[131]
 + c2.v[76]*MainFormSLS->hh_1[13]
 + c2.v[77]*MainFormSLS->hh_1[55]
 + c2.v[78]*MainFormSLS->hh_1[97]
 + c2.v[79]*MainFormSLS->hh_1[139];
s/=N_2;
out.push_back(s);
//������ 22
s =c2.v[0]*MainFormSLS->hh_1[22]
 + c2.v[1]*MainFormSLS->hh_1[66]
 + c2.v[2]*MainFormSLS->hh_1[110]
 + c2.v[3]*MainFormSLS->hh_1[154]
 + c2.v[4]*MainFormSLS->hh_1[38]
 + c2.v[5]*MainFormSLS->hh_1[82]
 + c2.v[6]*MainFormSLS->hh_1[126]
 + c2.v[7]*MainFormSLS->hh_1[10]
 + c2.v[8]*MainFormSLS->hh_1[54]
 + c2.v[9]*MainFormSLS->hh_1[98]
 + c2.v[10]*MainFormSLS->hh_1[142]
 + c2.v[11]*MainFormSLS->hh_1[26]
 + c2.v[12]*MainFormSLS->hh_1[70]
 + c2.v[13]*MainFormSLS->hh_1[114]
 + c2.v[14]*MainFormSLS->hh_1[158]
 + c2.v[15]*MainFormSLS->hh_1[42]
 + c2.v[16]*MainFormSLS->hh_1[86]
 + c2.v[17]*MainFormSLS->hh_1[130]
 + c2.v[18]*MainFormSLS->hh_1[14]
 + c2.v[19]*MainFormSLS->hh_1[58]
 + c2.v[20]*MainFormSLS->hh_1[102]
 + c2.v[21]*MainFormSLS->hh_1[146]
 + c2.v[22]*MainFormSLS->hh_1[30]
 + c2.v[23]*MainFormSLS->hh_1[74]
 + c2.v[24]*MainFormSLS->hh_1[118]
 + c2.v[25]*MainFormSLS->hh_1[2]
 + c2.v[26]*MainFormSLS->hh_1[46]
 + c2.v[27]*MainFormSLS->hh_1[90]
 + c2.v[28]*MainFormSLS->hh_1[134]
 + c2.v[29]*MainFormSLS->hh_1[18]
 + c2.v[30]*MainFormSLS->hh_1[62]
 + c2.v[31]*MainFormSLS->hh_1[106]
 + c2.v[32]*MainFormSLS->hh_1[150]
 + c2.v[33]*MainFormSLS->hh_1[34]
 + c2.v[34]*MainFormSLS->hh_1[78]
 + c2.v[35]*MainFormSLS->hh_1[122]
 + c2.v[36]*MainFormSLS->hh_1[6]
 + c2.v[37]*MainFormSLS->hh_1[50]
 + c2.v[38]*MainFormSLS->hh_1[94]
 + c2.v[39]*MainFormSLS->hh_1[138]
 + c2.v[40]*MainFormSLS->hh_1[22]
 + c2.v[41]*MainFormSLS->hh_1[66]
 + c2.v[42]*MainFormSLS->hh_1[110]
 + c2.v[43]*MainFormSLS->hh_1[154]
 + c2.v[44]*MainFormSLS->hh_1[38]
 + c2.v[45]*MainFormSLS->hh_1[82]
 + c2.v[46]*MainFormSLS->hh_1[126]
 + c2.v[47]*MainFormSLS->hh_1[10]
 + c2.v[48]*MainFormSLS->hh_1[54]
 + c2.v[49]*MainFormSLS->hh_1[98]
 + c2.v[50]*MainFormSLS->hh_1[142]
 + c2.v[51]*MainFormSLS->hh_1[26]
 + c2.v[52]*MainFormSLS->hh_1[70]
 + c2.v[53]*MainFormSLS->hh_1[114]
 + c2.v[54]*MainFormSLS->hh_1[158]
 + c2.v[55]*MainFormSLS->hh_1[42]
 + c2.v[56]*MainFormSLS->hh_1[86]
 + c2.v[57]*MainFormSLS->hh_1[130]
 + c2.v[58]*MainFormSLS->hh_1[14]
 + c2.v[59]*MainFormSLS->hh_1[58]
 + c2.v[60]*MainFormSLS->hh_1[102]
 + c2.v[61]*MainFormSLS->hh_1[146]
 + c2.v[62]*MainFormSLS->hh_1[30]
 + c2.v[63]*MainFormSLS->hh_1[74]
 + c2.v[64]*MainFormSLS->hh_1[118]
 + c2.v[65]*MainFormSLS->hh_1[2]
 + c2.v[66]*MainFormSLS->hh_1[46]
 + c2.v[67]*MainFormSLS->hh_1[90]
 + c2.v[68]*MainFormSLS->hh_1[134]
 + c2.v[69]*MainFormSLS->hh_1[18]
 + c2.v[70]*MainFormSLS->hh_1[62]
 + c2.v[71]*MainFormSLS->hh_1[106]
 + c2.v[72]*MainFormSLS->hh_1[150]
 + c2.v[73]*MainFormSLS->hh_1[34]
 + c2.v[74]*MainFormSLS->hh_1[78]
 + c2.v[75]*MainFormSLS->hh_1[122]
 + c2.v[76]*MainFormSLS->hh_1[6]
 + c2.v[77]*MainFormSLS->hh_1[50]
 + c2.v[78]*MainFormSLS->hh_1[94]
 + c2.v[79]*MainFormSLS->hh_1[138];
s/=N_2;
out.push_back(s);
//������ 23
s =c2.v[0]*MainFormSLS->hh_1[23]
 + c2.v[1]*MainFormSLS->hh_1[69]
 + c2.v[2]*MainFormSLS->hh_1[115]
 + c2.v[3]*MainFormSLS->hh_1[1]
 + c2.v[4]*MainFormSLS->hh_1[47]
 + c2.v[5]*MainFormSLS->hh_1[93]
 + c2.v[6]*MainFormSLS->hh_1[139]
 + c2.v[7]*MainFormSLS->hh_1[25]
 + c2.v[8]*MainFormSLS->hh_1[71]
 + c2.v[9]*MainFormSLS->hh_1[117]
 + c2.v[10]*MainFormSLS->hh_1[3]
 + c2.v[11]*MainFormSLS->hh_1[49]
 + c2.v[12]*MainFormSLS->hh_1[95]
 + c2.v[13]*MainFormSLS->hh_1[141]
 + c2.v[14]*MainFormSLS->hh_1[27]
 + c2.v[15]*MainFormSLS->hh_1[73]
 + c2.v[16]*MainFormSLS->hh_1[119]
 + c2.v[17]*MainFormSLS->hh_1[5]
 + c2.v[18]*MainFormSLS->hh_1[51]
 + c2.v[19]*MainFormSLS->hh_1[97]
 + c2.v[20]*MainFormSLS->hh_1[143]
 + c2.v[21]*MainFormSLS->hh_1[29]
 + c2.v[22]*MainFormSLS->hh_1[75]
 + c2.v[23]*MainFormSLS->hh_1[121]
 + c2.v[24]*MainFormSLS->hh_1[7]
 + c2.v[25]*MainFormSLS->hh_1[53]
 + c2.v[26]*MainFormSLS->hh_1[99]
 + c2.v[27]*MainFormSLS->hh_1[145]
 + c2.v[28]*MainFormSLS->hh_1[31]
 + c2.v[29]*MainFormSLS->hh_1[77]
 + c2.v[30]*MainFormSLS->hh_1[123]
 + c2.v[31]*MainFormSLS->hh_1[9]
 + c2.v[32]*MainFormSLS->hh_1[55]
 + c2.v[33]*MainFormSLS->hh_1[101]
 + c2.v[34]*MainFormSLS->hh_1[147]
 + c2.v[35]*MainFormSLS->hh_1[33]
 + c2.v[36]*MainFormSLS->hh_1[79]
 + c2.v[37]*MainFormSLS->hh_1[125]
 + c2.v[38]*MainFormSLS->hh_1[11]
 + c2.v[39]*MainFormSLS->hh_1[57]
 + c2.v[40]*MainFormSLS->hh_1[103]
 + c2.v[41]*MainFormSLS->hh_1[149]
 + c2.v[42]*MainFormSLS->hh_1[35]
 + c2.v[43]*MainFormSLS->hh_1[81]
 + c2.v[44]*MainFormSLS->hh_1[127]
 + c2.v[45]*MainFormSLS->hh_1[13]
 + c2.v[46]*MainFormSLS->hh_1[59]
 + c2.v[47]*MainFormSLS->hh_1[105]
 + c2.v[48]*MainFormSLS->hh_1[151]
 + c2.v[49]*MainFormSLS->hh_1[37]
 + c2.v[50]*MainFormSLS->hh_1[83]
 + c2.v[51]*MainFormSLS->hh_1[129]
 + c2.v[52]*MainFormSLS->hh_1[15]
 + c2.v[53]*MainFormSLS->hh_1[61]
 + c2.v[54]*MainFormSLS->hh_1[107]
 + c2.v[55]*MainFormSLS->hh_1[153]
 + c2.v[56]*MainFormSLS->hh_1[39]
 + c2.v[57]*MainFormSLS->hh_1[85]
 + c2.v[58]*MainFormSLS->hh_1[131]
 + c2.v[59]*MainFormSLS->hh_1[17]
 + c2.v[60]*MainFormSLS->hh_1[63]
 + c2.v[61]*MainFormSLS->hh_1[109]
 + c2.v[62]*MainFormSLS->hh_1[155]
 + c2.v[63]*MainFormSLS->hh_1[41]
 + c2.v[64]*MainFormSLS->hh_1[87]
 + c2.v[65]*MainFormSLS->hh_1[133]
 + c2.v[66]*MainFormSLS->hh_1[19]
 + c2.v[67]*MainFormSLS->hh_1[65]
 + c2.v[68]*MainFormSLS->hh_1[111]
 + c2.v[69]*MainFormSLS->hh_1[157]
 + c2.v[70]*MainFormSLS->hh_1[43]
 + c2.v[71]*MainFormSLS->hh_1[89]
 + c2.v[72]*MainFormSLS->hh_1[135]
 + c2.v[73]*MainFormSLS->hh_1[21]
 + c2.v[74]*MainFormSLS->hh_1[67]
 + c2.v[75]*MainFormSLS->hh_1[113]
 + c2.v[76]*MainFormSLS->hh_1[159]
 + c2.v[77]*MainFormSLS->hh_1[45]
 + c2.v[78]*MainFormSLS->hh_1[91]
 + c2.v[79]*MainFormSLS->hh_1[137];
s/=N_2;
out.push_back(s);
//������ 24
s =c2.v[0]*MainFormSLS->hh_1[24]
 + c2.v[1]*MainFormSLS->hh_1[72]
 + c2.v[2]*MainFormSLS->hh_1[120]
 + c2.v[3]*MainFormSLS->hh_1[8]
 + c2.v[4]*MainFormSLS->hh_1[56]
 + c2.v[5]*MainFormSLS->hh_1[104]
 + c2.v[6]*MainFormSLS->hh_1[152]
 + c2.v[7]*MainFormSLS->hh_1[40]
 + c2.v[8]*MainFormSLS->hh_1[88]
 + c2.v[9]*MainFormSLS->hh_1[136]
 + c2.v[10]*MainFormSLS->hh_1[24]
 + c2.v[11]*MainFormSLS->hh_1[72]
 + c2.v[12]*MainFormSLS->hh_1[120]
 + c2.v[13]*MainFormSLS->hh_1[8]
 + c2.v[14]*MainFormSLS->hh_1[56]
 + c2.v[15]*MainFormSLS->hh_1[104]
 + c2.v[16]*MainFormSLS->hh_1[152]
 + c2.v[17]*MainFormSLS->hh_1[40]
 + c2.v[18]*MainFormSLS->hh_1[88]
 + c2.v[19]*MainFormSLS->hh_1[136]
 + c2.v[20]*MainFormSLS->hh_1[24]
 + c2.v[21]*MainFormSLS->hh_1[72]
 + c2.v[22]*MainFormSLS->hh_1[120]
 + c2.v[23]*MainFormSLS->hh_1[8]
 + c2.v[24]*MainFormSLS->hh_1[56]
 + c2.v[25]*MainFormSLS->hh_1[104]
 + c2.v[26]*MainFormSLS->hh_1[152]
 + c2.v[27]*MainFormSLS->hh_1[40]
 + c2.v[28]*MainFormSLS->hh_1[88]
 + c2.v[29]*MainFormSLS->hh_1[136]
 + c2.v[30]*MainFormSLS->hh_1[24]
 + c2.v[31]*MainFormSLS->hh_1[72]
 + c2.v[32]*MainFormSLS->hh_1[120]
 + c2.v[33]*MainFormSLS->hh_1[8]
 + c2.v[34]*MainFormSLS->hh_1[56]
 + c2.v[35]*MainFormSLS->hh_1[104]
 + c2.v[36]*MainFormSLS->hh_1[152]
 + c2.v[37]*MainFormSLS->hh_1[40]
 + c2.v[38]*MainFormSLS->hh_1[88]
 + c2.v[39]*MainFormSLS->hh_1[136]
 + c2.v[40]*MainFormSLS->hh_1[24]
 + c2.v[41]*MainFormSLS->hh_1[72]
 + c2.v[42]*MainFormSLS->hh_1[120]
 + c2.v[43]*MainFormSLS->hh_1[8]
 + c2.v[44]*MainFormSLS->hh_1[56]
 + c2.v[45]*MainFormSLS->hh_1[104]
 + c2.v[46]*MainFormSLS->hh_1[152]
 + c2.v[47]*MainFormSLS->hh_1[40]
 + c2.v[48]*MainFormSLS->hh_1[88]
 + c2.v[49]*MainFormSLS->hh_1[136]
 + c2.v[50]*MainFormSLS->hh_1[24]
 + c2.v[51]*MainFormSLS->hh_1[72]
 + c2.v[52]*MainFormSLS->hh_1[120]
 + c2.v[53]*MainFormSLS->hh_1[8]
 + c2.v[54]*MainFormSLS->hh_1[56]
 + c2.v[55]*MainFormSLS->hh_1[104]
 + c2.v[56]*MainFormSLS->hh_1[152]
 + c2.v[57]*MainFormSLS->hh_1[40]
 + c2.v[58]*MainFormSLS->hh_1[88]
 + c2.v[59]*MainFormSLS->hh_1[136]
 + c2.v[60]*MainFormSLS->hh_1[24]
 + c2.v[61]*MainFormSLS->hh_1[72]
 + c2.v[62]*MainFormSLS->hh_1[120]
 + c2.v[63]*MainFormSLS->hh_1[8]
 + c2.v[64]*MainFormSLS->hh_1[56]
 + c2.v[65]*MainFormSLS->hh_1[104]
 + c2.v[66]*MainFormSLS->hh_1[152]
 + c2.v[67]*MainFormSLS->hh_1[40]
 + c2.v[68]*MainFormSLS->hh_1[88]
 + c2.v[69]*MainFormSLS->hh_1[136]
 + c2.v[70]*MainFormSLS->hh_1[24]
 + c2.v[71]*MainFormSLS->hh_1[72]
 + c2.v[72]*MainFormSLS->hh_1[120]
 + c2.v[73]*MainFormSLS->hh_1[8]
 + c2.v[74]*MainFormSLS->hh_1[56]
 + c2.v[75]*MainFormSLS->hh_1[104]
 + c2.v[76]*MainFormSLS->hh_1[152]
 + c2.v[77]*MainFormSLS->hh_1[40]
 + c2.v[78]*MainFormSLS->hh_1[88]
 + c2.v[79]*MainFormSLS->hh_1[136];
s/=N_2;
out.push_back(s);
//������ 25
s =c2.v[0]*MainFormSLS->hh_1[25]
 + c2.v[1]*MainFormSLS->hh_1[75]
 + c2.v[2]*MainFormSLS->hh_1[125]
 + c2.v[3]*MainFormSLS->hh_1[15]
 + c2.v[4]*MainFormSLS->hh_1[65]
 + c2.v[5]*MainFormSLS->hh_1[115]
 + c2.v[6]*MainFormSLS->hh_1[5]
 + c2.v[7]*MainFormSLS->hh_1[55]
 + c2.v[8]*MainFormSLS->hh_1[105]
 + c2.v[9]*MainFormSLS->hh_1[155]
 + c2.v[10]*MainFormSLS->hh_1[45]
 + c2.v[11]*MainFormSLS->hh_1[95]
 + c2.v[12]*MainFormSLS->hh_1[145]
 + c2.v[13]*MainFormSLS->hh_1[35]
 + c2.v[14]*MainFormSLS->hh_1[85]
 + c2.v[15]*MainFormSLS->hh_1[135]
 + c2.v[16]*MainFormSLS->hh_1[25]
 + c2.v[17]*MainFormSLS->hh_1[75]
 + c2.v[18]*MainFormSLS->hh_1[125]
 + c2.v[19]*MainFormSLS->hh_1[15]
 + c2.v[20]*MainFormSLS->hh_1[65]
 + c2.v[21]*MainFormSLS->hh_1[115]
 + c2.v[22]*MainFormSLS->hh_1[5]
 + c2.v[23]*MainFormSLS->hh_1[55]
 + c2.v[24]*MainFormSLS->hh_1[105]
 + c2.v[25]*MainFormSLS->hh_1[155]
 + c2.v[26]*MainFormSLS->hh_1[45]
 + c2.v[27]*MainFormSLS->hh_1[95]
 + c2.v[28]*MainFormSLS->hh_1[145]
 + c2.v[29]*MainFormSLS->hh_1[35]
 + c2.v[30]*MainFormSLS->hh_1[85]
 + c2.v[31]*MainFormSLS->hh_1[135]
 + c2.v[32]*MainFormSLS->hh_1[25]
 + c2.v[33]*MainFormSLS->hh_1[75]
 + c2.v[34]*MainFormSLS->hh_1[125]
 + c2.v[35]*MainFormSLS->hh_1[15]
 + c2.v[36]*MainFormSLS->hh_1[65]
 + c2.v[37]*MainFormSLS->hh_1[115]
 + c2.v[38]*MainFormSLS->hh_1[5]
 + c2.v[39]*MainFormSLS->hh_1[55]
 + c2.v[40]*MainFormSLS->hh_1[105]
 + c2.v[41]*MainFormSLS->hh_1[155]
 + c2.v[42]*MainFormSLS->hh_1[45]
 + c2.v[43]*MainFormSLS->hh_1[95]
 + c2.v[44]*MainFormSLS->hh_1[145]
 + c2.v[45]*MainFormSLS->hh_1[35]
 + c2.v[46]*MainFormSLS->hh_1[85]
 + c2.v[47]*MainFormSLS->hh_1[135]
 + c2.v[48]*MainFormSLS->hh_1[25]
 + c2.v[49]*MainFormSLS->hh_1[75]
 + c2.v[50]*MainFormSLS->hh_1[125]
 + c2.v[51]*MainFormSLS->hh_1[15]
 + c2.v[52]*MainFormSLS->hh_1[65]
 + c2.v[53]*MainFormSLS->hh_1[115]
 + c2.v[54]*MainFormSLS->hh_1[5]
 + c2.v[55]*MainFormSLS->hh_1[55]
 + c2.v[56]*MainFormSLS->hh_1[105]
 + c2.v[57]*MainFormSLS->hh_1[155]
 + c2.v[58]*MainFormSLS->hh_1[45]
 + c2.v[59]*MainFormSLS->hh_1[95]
 + c2.v[60]*MainFormSLS->hh_1[145]
 + c2.v[61]*MainFormSLS->hh_1[35]
 + c2.v[62]*MainFormSLS->hh_1[85]
 + c2.v[63]*MainFormSLS->hh_1[135]
 + c2.v[64]*MainFormSLS->hh_1[25]
 + c2.v[65]*MainFormSLS->hh_1[75]
 + c2.v[66]*MainFormSLS->hh_1[125]
 + c2.v[67]*MainFormSLS->hh_1[15]
 + c2.v[68]*MainFormSLS->hh_1[65]
 + c2.v[69]*MainFormSLS->hh_1[115]
 + c2.v[70]*MainFormSLS->hh_1[5]
 + c2.v[71]*MainFormSLS->hh_1[55]
 + c2.v[72]*MainFormSLS->hh_1[105]
 + c2.v[73]*MainFormSLS->hh_1[155]
 + c2.v[74]*MainFormSLS->hh_1[45]
 + c2.v[75]*MainFormSLS->hh_1[95]
 + c2.v[76]*MainFormSLS->hh_1[145]
 + c2.v[77]*MainFormSLS->hh_1[35]
 + c2.v[78]*MainFormSLS->hh_1[85]
 + c2.v[79]*MainFormSLS->hh_1[135];
s/=N_2;
out.push_back(s);
//������ 26
s =c2.v[0]*MainFormSLS->hh_1[26]
 + c2.v[1]*MainFormSLS->hh_1[78]
 + c2.v[2]*MainFormSLS->hh_1[130]
 + c2.v[3]*MainFormSLS->hh_1[22]
 + c2.v[4]*MainFormSLS->hh_1[74]
 + c2.v[5]*MainFormSLS->hh_1[126]
 + c2.v[6]*MainFormSLS->hh_1[18]
 + c2.v[7]*MainFormSLS->hh_1[70]
 + c2.v[8]*MainFormSLS->hh_1[122]
 + c2.v[9]*MainFormSLS->hh_1[14]
 + c2.v[10]*MainFormSLS->hh_1[66]
 + c2.v[11]*MainFormSLS->hh_1[118]
 + c2.v[12]*MainFormSLS->hh_1[10]
 + c2.v[13]*MainFormSLS->hh_1[62]
 + c2.v[14]*MainFormSLS->hh_1[114]
 + c2.v[15]*MainFormSLS->hh_1[6]
 + c2.v[16]*MainFormSLS->hh_1[58]
 + c2.v[17]*MainFormSLS->hh_1[110]
 + c2.v[18]*MainFormSLS->hh_1[2]
 + c2.v[19]*MainFormSLS->hh_1[54]
 + c2.v[20]*MainFormSLS->hh_1[106]
 + c2.v[21]*MainFormSLS->hh_1[158]
 + c2.v[22]*MainFormSLS->hh_1[50]
 + c2.v[23]*MainFormSLS->hh_1[102]
 + c2.v[24]*MainFormSLS->hh_1[154]
 + c2.v[25]*MainFormSLS->hh_1[46]
 + c2.v[26]*MainFormSLS->hh_1[98]
 + c2.v[27]*MainFormSLS->hh_1[150]
 + c2.v[28]*MainFormSLS->hh_1[42]
 + c2.v[29]*MainFormSLS->hh_1[94]
 + c2.v[30]*MainFormSLS->hh_1[146]
 + c2.v[31]*MainFormSLS->hh_1[38]
 + c2.v[32]*MainFormSLS->hh_1[90]
 + c2.v[33]*MainFormSLS->hh_1[142]
 + c2.v[34]*MainFormSLS->hh_1[34]
 + c2.v[35]*MainFormSLS->hh_1[86]
 + c2.v[36]*MainFormSLS->hh_1[138]
 + c2.v[37]*MainFormSLS->hh_1[30]
 + c2.v[38]*MainFormSLS->hh_1[82]
 + c2.v[39]*MainFormSLS->hh_1[134]
 + c2.v[40]*MainFormSLS->hh_1[26]
 + c2.v[41]*MainFormSLS->hh_1[78]
 + c2.v[42]*MainFormSLS->hh_1[130]
 + c2.v[43]*MainFormSLS->hh_1[22]
 + c2.v[44]*MainFormSLS->hh_1[74]
 + c2.v[45]*MainFormSLS->hh_1[126]
 + c2.v[46]*MainFormSLS->hh_1[18]
 + c2.v[47]*MainFormSLS->hh_1[70]
 + c2.v[48]*MainFormSLS->hh_1[122]
 + c2.v[49]*MainFormSLS->hh_1[14]
 + c2.v[50]*MainFormSLS->hh_1[66]
 + c2.v[51]*MainFormSLS->hh_1[118]
 + c2.v[52]*MainFormSLS->hh_1[10]
 + c2.v[53]*MainFormSLS->hh_1[62]
 + c2.v[54]*MainFormSLS->hh_1[114]
 + c2.v[55]*MainFormSLS->hh_1[6]
 + c2.v[56]*MainFormSLS->hh_1[58]
 + c2.v[57]*MainFormSLS->hh_1[110]
 + c2.v[58]*MainFormSLS->hh_1[2]
 + c2.v[59]*MainFormSLS->hh_1[54]
 + c2.v[60]*MainFormSLS->hh_1[106]
 + c2.v[61]*MainFormSLS->hh_1[158]
 + c2.v[62]*MainFormSLS->hh_1[50]
 + c2.v[63]*MainFormSLS->hh_1[102]
 + c2.v[64]*MainFormSLS->hh_1[154]
 + c2.v[65]*MainFormSLS->hh_1[46]
 + c2.v[66]*MainFormSLS->hh_1[98]
 + c2.v[67]*MainFormSLS->hh_1[150]
 + c2.v[68]*MainFormSLS->hh_1[42]
 + c2.v[69]*MainFormSLS->hh_1[94]
 + c2.v[70]*MainFormSLS->hh_1[146]
 + c2.v[71]*MainFormSLS->hh_1[38]
 + c2.v[72]*MainFormSLS->hh_1[90]
 + c2.v[73]*MainFormSLS->hh_1[142]
 + c2.v[74]*MainFormSLS->hh_1[34]
 + c2.v[75]*MainFormSLS->hh_1[86]
 + c2.v[76]*MainFormSLS->hh_1[138]
 + c2.v[77]*MainFormSLS->hh_1[30]
 + c2.v[78]*MainFormSLS->hh_1[82]
 + c2.v[79]*MainFormSLS->hh_1[134];
s/=N_2;
out.push_back(s);
//������ 27
s =c2.v[0]*MainFormSLS->hh_1[27]
 + c2.v[1]*MainFormSLS->hh_1[81]
 + c2.v[2]*MainFormSLS->hh_1[135]
 + c2.v[3]*MainFormSLS->hh_1[29]
 + c2.v[4]*MainFormSLS->hh_1[83]
 + c2.v[5]*MainFormSLS->hh_1[137]
 + c2.v[6]*MainFormSLS->hh_1[31]
 + c2.v[7]*MainFormSLS->hh_1[85]
 + c2.v[8]*MainFormSLS->hh_1[139]
 + c2.v[9]*MainFormSLS->hh_1[33]
 + c2.v[10]*MainFormSLS->hh_1[87]
 + c2.v[11]*MainFormSLS->hh_1[141]
 + c2.v[12]*MainFormSLS->hh_1[35]
 + c2.v[13]*MainFormSLS->hh_1[89]
 + c2.v[14]*MainFormSLS->hh_1[143]
 + c2.v[15]*MainFormSLS->hh_1[37]
 + c2.v[16]*MainFormSLS->hh_1[91]
 + c2.v[17]*MainFormSLS->hh_1[145]
 + c2.v[18]*MainFormSLS->hh_1[39]
 + c2.v[19]*MainFormSLS->hh_1[93]
 + c2.v[20]*MainFormSLS->hh_1[147]
 + c2.v[21]*MainFormSLS->hh_1[41]
 + c2.v[22]*MainFormSLS->hh_1[95]
 + c2.v[23]*MainFormSLS->hh_1[149]
 + c2.v[24]*MainFormSLS->hh_1[43]
 + c2.v[25]*MainFormSLS->hh_1[97]
 + c2.v[26]*MainFormSLS->hh_1[151]
 + c2.v[27]*MainFormSLS->hh_1[45]
 + c2.v[28]*MainFormSLS->hh_1[99]
 + c2.v[29]*MainFormSLS->hh_1[153]
 + c2.v[30]*MainFormSLS->hh_1[47]
 + c2.v[31]*MainFormSLS->hh_1[101]
 + c2.v[32]*MainFormSLS->hh_1[155]
 + c2.v[33]*MainFormSLS->hh_1[49]
 + c2.v[34]*MainFormSLS->hh_1[103]
 + c2.v[35]*MainFormSLS->hh_1[157]
 + c2.v[36]*MainFormSLS->hh_1[51]
 + c2.v[37]*MainFormSLS->hh_1[105]
 + c2.v[38]*MainFormSLS->hh_1[159]
 + c2.v[39]*MainFormSLS->hh_1[53]
 + c2.v[40]*MainFormSLS->hh_1[107]
 + c2.v[41]*MainFormSLS->hh_1[1]
 + c2.v[42]*MainFormSLS->hh_1[55]
 + c2.v[43]*MainFormSLS->hh_1[109]
 + c2.v[44]*MainFormSLS->hh_1[3]
 + c2.v[45]*MainFormSLS->hh_1[57]
 + c2.v[46]*MainFormSLS->hh_1[111]
 + c2.v[47]*MainFormSLS->hh_1[5]
 + c2.v[48]*MainFormSLS->hh_1[59]
 + c2.v[49]*MainFormSLS->hh_1[113]
 + c2.v[50]*MainFormSLS->hh_1[7]
 + c2.v[51]*MainFormSLS->hh_1[61]
 + c2.v[52]*MainFormSLS->hh_1[115]
 + c2.v[53]*MainFormSLS->hh_1[9]
 + c2.v[54]*MainFormSLS->hh_1[63]
 + c2.v[55]*MainFormSLS->hh_1[117]
 + c2.v[56]*MainFormSLS->hh_1[11]
 + c2.v[57]*MainFormSLS->hh_1[65]
 + c2.v[58]*MainFormSLS->hh_1[119]
 + c2.v[59]*MainFormSLS->hh_1[13]
 + c2.v[60]*MainFormSLS->hh_1[67]
 + c2.v[61]*MainFormSLS->hh_1[121]
 + c2.v[62]*MainFormSLS->hh_1[15]
 + c2.v[63]*MainFormSLS->hh_1[69]
 + c2.v[64]*MainFormSLS->hh_1[123]
 + c2.v[65]*MainFormSLS->hh_1[17]
 + c2.v[66]*MainFormSLS->hh_1[71]
 + c2.v[67]*MainFormSLS->hh_1[125]
 + c2.v[68]*MainFormSLS->hh_1[19]
 + c2.v[69]*MainFormSLS->hh_1[73]
 + c2.v[70]*MainFormSLS->hh_1[127]
 + c2.v[71]*MainFormSLS->hh_1[21]
 + c2.v[72]*MainFormSLS->hh_1[75]
 + c2.v[73]*MainFormSLS->hh_1[129]
 + c2.v[74]*MainFormSLS->hh_1[23]
 + c2.v[75]*MainFormSLS->hh_1[77]
 + c2.v[76]*MainFormSLS->hh_1[131]
 + c2.v[77]*MainFormSLS->hh_1[25]
 + c2.v[78]*MainFormSLS->hh_1[79]
 + c2.v[79]*MainFormSLS->hh_1[133];
s/=N_2;
out.push_back(s);
//������ 28
s =c2.v[0]*MainFormSLS->hh_1[28]
 + c2.v[1]*MainFormSLS->hh_1[84]
 + c2.v[2]*MainFormSLS->hh_1[140]
 + c2.v[3]*MainFormSLS->hh_1[36]
 + c2.v[4]*MainFormSLS->hh_1[92]
 + c2.v[5]*MainFormSLS->hh_1[148]
 + c2.v[6]*MainFormSLS->hh_1[44]
 + c2.v[7]*MainFormSLS->hh_1[100]
 + c2.v[8]*MainFormSLS->hh_1[156]
 + c2.v[9]*MainFormSLS->hh_1[52]
 + c2.v[10]*MainFormSLS->hh_1[108]
 + c2.v[11]*MainFormSLS->hh_1[4]
 + c2.v[12]*MainFormSLS->hh_1[60]
 + c2.v[13]*MainFormSLS->hh_1[116]
 + c2.v[14]*MainFormSLS->hh_1[12]
 + c2.v[15]*MainFormSLS->hh_1[68]
 + c2.v[16]*MainFormSLS->hh_1[124]
 + c2.v[17]*MainFormSLS->hh_1[20]
 + c2.v[18]*MainFormSLS->hh_1[76]
 + c2.v[19]*MainFormSLS->hh_1[132]
 + c2.v[20]*MainFormSLS->hh_1[28]
 + c2.v[21]*MainFormSLS->hh_1[84]
 + c2.v[22]*MainFormSLS->hh_1[140]
 + c2.v[23]*MainFormSLS->hh_1[36]
 + c2.v[24]*MainFormSLS->hh_1[92]
 + c2.v[25]*MainFormSLS->hh_1[148]
 + c2.v[26]*MainFormSLS->hh_1[44]
 + c2.v[27]*MainFormSLS->hh_1[100]
 + c2.v[28]*MainFormSLS->hh_1[156]
 + c2.v[29]*MainFormSLS->hh_1[52]
 + c2.v[30]*MainFormSLS->hh_1[108]
 + c2.v[31]*MainFormSLS->hh_1[4]
 + c2.v[32]*MainFormSLS->hh_1[60]
 + c2.v[33]*MainFormSLS->hh_1[116]
 + c2.v[34]*MainFormSLS->hh_1[12]
 + c2.v[35]*MainFormSLS->hh_1[68]
 + c2.v[36]*MainFormSLS->hh_1[124]
 + c2.v[37]*MainFormSLS->hh_1[20]
 + c2.v[38]*MainFormSLS->hh_1[76]
 + c2.v[39]*MainFormSLS->hh_1[132]
 + c2.v[40]*MainFormSLS->hh_1[28]
 + c2.v[41]*MainFormSLS->hh_1[84]
 + c2.v[42]*MainFormSLS->hh_1[140]
 + c2.v[43]*MainFormSLS->hh_1[36]
 + c2.v[44]*MainFormSLS->hh_1[92]
 + c2.v[45]*MainFormSLS->hh_1[148]
 + c2.v[46]*MainFormSLS->hh_1[44]
 + c2.v[47]*MainFormSLS->hh_1[100]
 + c2.v[48]*MainFormSLS->hh_1[156]
 + c2.v[49]*MainFormSLS->hh_1[52]
 + c2.v[50]*MainFormSLS->hh_1[108]
 + c2.v[51]*MainFormSLS->hh_1[4]
 + c2.v[52]*MainFormSLS->hh_1[60]
 + c2.v[53]*MainFormSLS->hh_1[116]
 + c2.v[54]*MainFormSLS->hh_1[12]
 + c2.v[55]*MainFormSLS->hh_1[68]
 + c2.v[56]*MainFormSLS->hh_1[124]
 + c2.v[57]*MainFormSLS->hh_1[20]
 + c2.v[58]*MainFormSLS->hh_1[76]
 + c2.v[59]*MainFormSLS->hh_1[132]
 + c2.v[60]*MainFormSLS->hh_1[28]
 + c2.v[61]*MainFormSLS->hh_1[84]
 + c2.v[62]*MainFormSLS->hh_1[140]
 + c2.v[63]*MainFormSLS->hh_1[36]
 + c2.v[64]*MainFormSLS->hh_1[92]
 + c2.v[65]*MainFormSLS->hh_1[148]
 + c2.v[66]*MainFormSLS->hh_1[44]
 + c2.v[67]*MainFormSLS->hh_1[100]
 + c2.v[68]*MainFormSLS->hh_1[156]
 + c2.v[69]*MainFormSLS->hh_1[52]
 + c2.v[70]*MainFormSLS->hh_1[108]
 + c2.v[71]*MainFormSLS->hh_1[4]
 + c2.v[72]*MainFormSLS->hh_1[60]
 + c2.v[73]*MainFormSLS->hh_1[116]
 + c2.v[74]*MainFormSLS->hh_1[12]
 + c2.v[75]*MainFormSLS->hh_1[68]
 + c2.v[76]*MainFormSLS->hh_1[124]
 + c2.v[77]*MainFormSLS->hh_1[20]
 + c2.v[78]*MainFormSLS->hh_1[76]
 + c2.v[79]*MainFormSLS->hh_1[132];
s/=N_2;
out.push_back(s);
//������ 29
s =c2.v[0]*MainFormSLS->hh_1[29]
 + c2.v[1]*MainFormSLS->hh_1[87]
 + c2.v[2]*MainFormSLS->hh_1[145]
 + c2.v[3]*MainFormSLS->hh_1[43]
 + c2.v[4]*MainFormSLS->hh_1[101]
 + c2.v[5]*MainFormSLS->hh_1[159]
 + c2.v[6]*MainFormSLS->hh_1[57]
 + c2.v[7]*MainFormSLS->hh_1[115]
 + c2.v[8]*MainFormSLS->hh_1[13]
 + c2.v[9]*MainFormSLS->hh_1[71]
 + c2.v[10]*MainFormSLS->hh_1[129]
 + c2.v[11]*MainFormSLS->hh_1[27]
 + c2.v[12]*MainFormSLS->hh_1[85]
 + c2.v[13]*MainFormSLS->hh_1[143]
 + c2.v[14]*MainFormSLS->hh_1[41]
 + c2.v[15]*MainFormSLS->hh_1[99]
 + c2.v[16]*MainFormSLS->hh_1[157]
 + c2.v[17]*MainFormSLS->hh_1[55]
 + c2.v[18]*MainFormSLS->hh_1[113]
 + c2.v[19]*MainFormSLS->hh_1[11]
 + c2.v[20]*MainFormSLS->hh_1[69]
 + c2.v[21]*MainFormSLS->hh_1[127]
 + c2.v[22]*MainFormSLS->hh_1[25]
 + c2.v[23]*MainFormSLS->hh_1[83]
 + c2.v[24]*MainFormSLS->hh_1[141]
 + c2.v[25]*MainFormSLS->hh_1[39]
 + c2.v[26]*MainFormSLS->hh_1[97]
 + c2.v[27]*MainFormSLS->hh_1[155]
 + c2.v[28]*MainFormSLS->hh_1[53]
 + c2.v[29]*MainFormSLS->hh_1[111]
 + c2.v[30]*MainFormSLS->hh_1[9]
 + c2.v[31]*MainFormSLS->hh_1[67]
 + c2.v[32]*MainFormSLS->hh_1[125]
 + c2.v[33]*MainFormSLS->hh_1[23]
 + c2.v[34]*MainFormSLS->hh_1[81]
 + c2.v[35]*MainFormSLS->hh_1[139]
 + c2.v[36]*MainFormSLS->hh_1[37]
 + c2.v[37]*MainFormSLS->hh_1[95]
 + c2.v[38]*MainFormSLS->hh_1[153]
 + c2.v[39]*MainFormSLS->hh_1[51]
 + c2.v[40]*MainFormSLS->hh_1[109]
 + c2.v[41]*MainFormSLS->hh_1[7]
 + c2.v[42]*MainFormSLS->hh_1[65]
 + c2.v[43]*MainFormSLS->hh_1[123]
 + c2.v[44]*MainFormSLS->hh_1[21]
 + c2.v[45]*MainFormSLS->hh_1[79]
 + c2.v[46]*MainFormSLS->hh_1[137]
 + c2.v[47]*MainFormSLS->hh_1[35]
 + c2.v[48]*MainFormSLS->hh_1[93]
 + c2.v[49]*MainFormSLS->hh_1[151]
 + c2.v[50]*MainFormSLS->hh_1[49]
 + c2.v[51]*MainFormSLS->hh_1[107]
 + c2.v[52]*MainFormSLS->hh_1[5]
 + c2.v[53]*MainFormSLS->hh_1[63]
 + c2.v[54]*MainFormSLS->hh_1[121]
 + c2.v[55]*MainFormSLS->hh_1[19]
 + c2.v[56]*MainFormSLS->hh_1[77]
 + c2.v[57]*MainFormSLS->hh_1[135]
 + c2.v[58]*MainFormSLS->hh_1[33]
 + c2.v[59]*MainFormSLS->hh_1[91]
 + c2.v[60]*MainFormSLS->hh_1[149]
 + c2.v[61]*MainFormSLS->hh_1[47]
 + c2.v[62]*MainFormSLS->hh_1[105]
 + c2.v[63]*MainFormSLS->hh_1[3]
 + c2.v[64]*MainFormSLS->hh_1[61]
 + c2.v[65]*MainFormSLS->hh_1[119]
 + c2.v[66]*MainFormSLS->hh_1[17]
 + c2.v[67]*MainFormSLS->hh_1[75]
 + c2.v[68]*MainFormSLS->hh_1[133]
 + c2.v[69]*MainFormSLS->hh_1[31]
 + c2.v[70]*MainFormSLS->hh_1[89]
 + c2.v[71]*MainFormSLS->hh_1[147]
 + c2.v[72]*MainFormSLS->hh_1[45]
 + c2.v[73]*MainFormSLS->hh_1[103]
 + c2.v[74]*MainFormSLS->hh_1[1]
 + c2.v[75]*MainFormSLS->hh_1[59]
 + c2.v[76]*MainFormSLS->hh_1[117]
 + c2.v[77]*MainFormSLS->hh_1[15]
 + c2.v[78]*MainFormSLS->hh_1[73]
 + c2.v[79]*MainFormSLS->hh_1[131];
s/=N_2;
out.push_back(s);
//������ 30
s =c2.v[0]*MainFormSLS->hh_1[30]
 + c2.v[1]*MainFormSLS->hh_1[90]
 + c2.v[2]*MainFormSLS->hh_1[150]
 + c2.v[3]*MainFormSLS->hh_1[50]
 + c2.v[4]*MainFormSLS->hh_1[110]
 + c2.v[5]*MainFormSLS->hh_1[10]
 + c2.v[6]*MainFormSLS->hh_1[70]
 + c2.v[7]*MainFormSLS->hh_1[130]
 + c2.v[8]*MainFormSLS->hh_1[30]
 + c2.v[9]*MainFormSLS->hh_1[90]
 + c2.v[10]*MainFormSLS->hh_1[150]
 + c2.v[11]*MainFormSLS->hh_1[50]
 + c2.v[12]*MainFormSLS->hh_1[110]
 + c2.v[13]*MainFormSLS->hh_1[10]
 + c2.v[14]*MainFormSLS->hh_1[70]
 + c2.v[15]*MainFormSLS->hh_1[130]
 + c2.v[16]*MainFormSLS->hh_1[30]
 + c2.v[17]*MainFormSLS->hh_1[90]
 + c2.v[18]*MainFormSLS->hh_1[150]
 + c2.v[19]*MainFormSLS->hh_1[50]
 + c2.v[20]*MainFormSLS->hh_1[110]
 + c2.v[21]*MainFormSLS->hh_1[10]
 + c2.v[22]*MainFormSLS->hh_1[70]
 + c2.v[23]*MainFormSLS->hh_1[130]
 + c2.v[24]*MainFormSLS->hh_1[30]
 + c2.v[25]*MainFormSLS->hh_1[90]
 + c2.v[26]*MainFormSLS->hh_1[150]
 + c2.v[27]*MainFormSLS->hh_1[50]
 + c2.v[28]*MainFormSLS->hh_1[110]
 + c2.v[29]*MainFormSLS->hh_1[10]
 + c2.v[30]*MainFormSLS->hh_1[70]
 + c2.v[31]*MainFormSLS->hh_1[130]
 + c2.v[32]*MainFormSLS->hh_1[30]
 + c2.v[33]*MainFormSLS->hh_1[90]
 + c2.v[34]*MainFormSLS->hh_1[150]
 + c2.v[35]*MainFormSLS->hh_1[50]
 + c2.v[36]*MainFormSLS->hh_1[110]
 + c2.v[37]*MainFormSLS->hh_1[10]
 + c2.v[38]*MainFormSLS->hh_1[70]
 + c2.v[39]*MainFormSLS->hh_1[130]
 + c2.v[40]*MainFormSLS->hh_1[30]
 + c2.v[41]*MainFormSLS->hh_1[90]
 + c2.v[42]*MainFormSLS->hh_1[150]
 + c2.v[43]*MainFormSLS->hh_1[50]
 + c2.v[44]*MainFormSLS->hh_1[110]
 + c2.v[45]*MainFormSLS->hh_1[10]
 + c2.v[46]*MainFormSLS->hh_1[70]
 + c2.v[47]*MainFormSLS->hh_1[130]
 + c2.v[48]*MainFormSLS->hh_1[30]
 + c2.v[49]*MainFormSLS->hh_1[90]
 + c2.v[50]*MainFormSLS->hh_1[150]
 + c2.v[51]*MainFormSLS->hh_1[50]
 + c2.v[52]*MainFormSLS->hh_1[110]
 + c2.v[53]*MainFormSLS->hh_1[10]
 + c2.v[54]*MainFormSLS->hh_1[70]
 + c2.v[55]*MainFormSLS->hh_1[130]
 + c2.v[56]*MainFormSLS->hh_1[30]
 + c2.v[57]*MainFormSLS->hh_1[90]
 + c2.v[58]*MainFormSLS->hh_1[150]
 + c2.v[59]*MainFormSLS->hh_1[50]
 + c2.v[60]*MainFormSLS->hh_1[110]
 + c2.v[61]*MainFormSLS->hh_1[10]
 + c2.v[62]*MainFormSLS->hh_1[70]
 + c2.v[63]*MainFormSLS->hh_1[130]
 + c2.v[64]*MainFormSLS->hh_1[30]
 + c2.v[65]*MainFormSLS->hh_1[90]
 + c2.v[66]*MainFormSLS->hh_1[150]
 + c2.v[67]*MainFormSLS->hh_1[50]
 + c2.v[68]*MainFormSLS->hh_1[110]
 + c2.v[69]*MainFormSLS->hh_1[10]
 + c2.v[70]*MainFormSLS->hh_1[70]
 + c2.v[71]*MainFormSLS->hh_1[130]
 + c2.v[72]*MainFormSLS->hh_1[30]
 + c2.v[73]*MainFormSLS->hh_1[90]
 + c2.v[74]*MainFormSLS->hh_1[150]
 + c2.v[75]*MainFormSLS->hh_1[50]
 + c2.v[76]*MainFormSLS->hh_1[110]
 + c2.v[77]*MainFormSLS->hh_1[10]
 + c2.v[78]*MainFormSLS->hh_1[70]
 + c2.v[79]*MainFormSLS->hh_1[130];
s/=N_2;
out.push_back(s);
//������ 31
s =c2.v[0]*MainFormSLS->hh_1[31]
 + c2.v[1]*MainFormSLS->hh_1[93]
 + c2.v[2]*MainFormSLS->hh_1[155]
 + c2.v[3]*MainFormSLS->hh_1[57]
 + c2.v[4]*MainFormSLS->hh_1[119]
 + c2.v[5]*MainFormSLS->hh_1[21]
 + c2.v[6]*MainFormSLS->hh_1[83]
 + c2.v[7]*MainFormSLS->hh_1[145]
 + c2.v[8]*MainFormSLS->hh_1[47]
 + c2.v[9]*MainFormSLS->hh_1[109]
 + c2.v[10]*MainFormSLS->hh_1[11]
 + c2.v[11]*MainFormSLS->hh_1[73]
 + c2.v[12]*MainFormSLS->hh_1[135]
 + c2.v[13]*MainFormSLS->hh_1[37]
 + c2.v[14]*MainFormSLS->hh_1[99]
 + c2.v[15]*MainFormSLS->hh_1[1]
 + c2.v[16]*MainFormSLS->hh_1[63]
 + c2.v[17]*MainFormSLS->hh_1[125]
 + c2.v[18]*MainFormSLS->hh_1[27]
 + c2.v[19]*MainFormSLS->hh_1[89]
 + c2.v[20]*MainFormSLS->hh_1[151]
 + c2.v[21]*MainFormSLS->hh_1[53]
 + c2.v[22]*MainFormSLS->hh_1[115]
 + c2.v[23]*MainFormSLS->hh_1[17]
 + c2.v[24]*MainFormSLS->hh_1[79]
 + c2.v[25]*MainFormSLS->hh_1[141]
 + c2.v[26]*MainFormSLS->hh_1[43]
 + c2.v[27]*MainFormSLS->hh_1[105]
 + c2.v[28]*MainFormSLS->hh_1[7]
 + c2.v[29]*MainFormSLS->hh_1[69]
 + c2.v[30]*MainFormSLS->hh_1[131]
 + c2.v[31]*MainFormSLS->hh_1[33]
 + c2.v[32]*MainFormSLS->hh_1[95]
 + c2.v[33]*MainFormSLS->hh_1[157]
 + c2.v[34]*MainFormSLS->hh_1[59]
 + c2.v[35]*MainFormSLS->hh_1[121]
 + c2.v[36]*MainFormSLS->hh_1[23]
 + c2.v[37]*MainFormSLS->hh_1[85]
 + c2.v[38]*MainFormSLS->hh_1[147]
 + c2.v[39]*MainFormSLS->hh_1[49]
 + c2.v[40]*MainFormSLS->hh_1[111]
 + c2.v[41]*MainFormSLS->hh_1[13]
 + c2.v[42]*MainFormSLS->hh_1[75]
 + c2.v[43]*MainFormSLS->hh_1[137]
 + c2.v[44]*MainFormSLS->hh_1[39]
 + c2.v[45]*MainFormSLS->hh_1[101]
 + c2.v[46]*MainFormSLS->hh_1[3]
 + c2.v[47]*MainFormSLS->hh_1[65]
 + c2.v[48]*MainFormSLS->hh_1[127]
 + c2.v[49]*MainFormSLS->hh_1[29]
 + c2.v[50]*MainFormSLS->hh_1[91]
 + c2.v[51]*MainFormSLS->hh_1[153]
 + c2.v[52]*MainFormSLS->hh_1[55]
 + c2.v[53]*MainFormSLS->hh_1[117]
 + c2.v[54]*MainFormSLS->hh_1[19]
 + c2.v[55]*MainFormSLS->hh_1[81]
 + c2.v[56]*MainFormSLS->hh_1[143]
 + c2.v[57]*MainFormSLS->hh_1[45]
 + c2.v[58]*MainFormSLS->hh_1[107]
 + c2.v[59]*MainFormSLS->hh_1[9]
 + c2.v[60]*MainFormSLS->hh_1[71]
 + c2.v[61]*MainFormSLS->hh_1[133]
 + c2.v[62]*MainFormSLS->hh_1[35]
 + c2.v[63]*MainFormSLS->hh_1[97]
 + c2.v[64]*MainFormSLS->hh_1[159]
 + c2.v[65]*MainFormSLS->hh_1[61]
 + c2.v[66]*MainFormSLS->hh_1[123]
 + c2.v[67]*MainFormSLS->hh_1[25]
 + c2.v[68]*MainFormSLS->hh_1[87]
 + c2.v[69]*MainFormSLS->hh_1[149]
 + c2.v[70]*MainFormSLS->hh_1[51]
 + c2.v[71]*MainFormSLS->hh_1[113]
 + c2.v[72]*MainFormSLS->hh_1[15]
 + c2.v[73]*MainFormSLS->hh_1[77]
 + c2.v[74]*MainFormSLS->hh_1[139]
 + c2.v[75]*MainFormSLS->hh_1[41]
 + c2.v[76]*MainFormSLS->hh_1[103]
 + c2.v[77]*MainFormSLS->hh_1[5]
 + c2.v[78]*MainFormSLS->hh_1[67]
 + c2.v[79]*MainFormSLS->hh_1[129];
s/=N_2;
out.push_back(s);
//������ 32
s =c2.v[0]*MainFormSLS->hh_1[32]
 + c2.v[1]*MainFormSLS->hh_1[96]
 + c2.v[2]*MainFormSLS->hh_1[0]
 + c2.v[3]*MainFormSLS->hh_1[64]
 + c2.v[4]*MainFormSLS->hh_1[128]
 + c2.v[5]*MainFormSLS->hh_1[32]
 + c2.v[6]*MainFormSLS->hh_1[96]
 + c2.v[7]*MainFormSLS->hh_1[0]
 + c2.v[8]*MainFormSLS->hh_1[64]
 + c2.v[9]*MainFormSLS->hh_1[128]
 + c2.v[10]*MainFormSLS->hh_1[32]
 + c2.v[11]*MainFormSLS->hh_1[96]
 + c2.v[12]*MainFormSLS->hh_1[0]
 + c2.v[13]*MainFormSLS->hh_1[64]
 + c2.v[14]*MainFormSLS->hh_1[128]
 + c2.v[15]*MainFormSLS->hh_1[32]
 + c2.v[16]*MainFormSLS->hh_1[96]
 + c2.v[17]*MainFormSLS->hh_1[0]
 + c2.v[18]*MainFormSLS->hh_1[64]
 + c2.v[19]*MainFormSLS->hh_1[128]
 + c2.v[20]*MainFormSLS->hh_1[32]
 + c2.v[21]*MainFormSLS->hh_1[96]
 + c2.v[22]*MainFormSLS->hh_1[0]
 + c2.v[23]*MainFormSLS->hh_1[64]
 + c2.v[24]*MainFormSLS->hh_1[128]
 + c2.v[25]*MainFormSLS->hh_1[32]
 + c2.v[26]*MainFormSLS->hh_1[96]
 + c2.v[27]*MainFormSLS->hh_1[0]
 + c2.v[28]*MainFormSLS->hh_1[64]
 + c2.v[29]*MainFormSLS->hh_1[128]
 + c2.v[30]*MainFormSLS->hh_1[32]
 + c2.v[31]*MainFormSLS->hh_1[96]
 + c2.v[32]*MainFormSLS->hh_1[0]
 + c2.v[33]*MainFormSLS->hh_1[64]
 + c2.v[34]*MainFormSLS->hh_1[128]
 + c2.v[35]*MainFormSLS->hh_1[32]
 + c2.v[36]*MainFormSLS->hh_1[96]
 + c2.v[37]*MainFormSLS->hh_1[0]
 + c2.v[38]*MainFormSLS->hh_1[64]
 + c2.v[39]*MainFormSLS->hh_1[128]
 + c2.v[40]*MainFormSLS->hh_1[32]
 + c2.v[41]*MainFormSLS->hh_1[96]
 + c2.v[42]*MainFormSLS->hh_1[0]
 + c2.v[43]*MainFormSLS->hh_1[64]
 + c2.v[44]*MainFormSLS->hh_1[128]
 + c2.v[45]*MainFormSLS->hh_1[32]
 + c2.v[46]*MainFormSLS->hh_1[96]
 + c2.v[47]*MainFormSLS->hh_1[0]
 + c2.v[48]*MainFormSLS->hh_1[64]
 + c2.v[49]*MainFormSLS->hh_1[128]
 + c2.v[50]*MainFormSLS->hh_1[32]
 + c2.v[51]*MainFormSLS->hh_1[96]
 + c2.v[52]*MainFormSLS->hh_1[0]
 + c2.v[53]*MainFormSLS->hh_1[64]
 + c2.v[54]*MainFormSLS->hh_1[128]
 + c2.v[55]*MainFormSLS->hh_1[32]
 + c2.v[56]*MainFormSLS->hh_1[96]
 + c2.v[57]*MainFormSLS->hh_1[0]
 + c2.v[58]*MainFormSLS->hh_1[64]
 + c2.v[59]*MainFormSLS->hh_1[128]
 + c2.v[60]*MainFormSLS->hh_1[32]
 + c2.v[61]*MainFormSLS->hh_1[96]
 + c2.v[62]*MainFormSLS->hh_1[0]
 + c2.v[63]*MainFormSLS->hh_1[64]
 + c2.v[64]*MainFormSLS->hh_1[128]
 + c2.v[65]*MainFormSLS->hh_1[32]
 + c2.v[66]*MainFormSLS->hh_1[96]
 + c2.v[67]*MainFormSLS->hh_1[0]
 + c2.v[68]*MainFormSLS->hh_1[64]
 + c2.v[69]*MainFormSLS->hh_1[128]
 + c2.v[70]*MainFormSLS->hh_1[32]
 + c2.v[71]*MainFormSLS->hh_1[96]
 + c2.v[72]*MainFormSLS->hh_1[0]
 + c2.v[73]*MainFormSLS->hh_1[64]
 + c2.v[74]*MainFormSLS->hh_1[128]
 + c2.v[75]*MainFormSLS->hh_1[32]
 + c2.v[76]*MainFormSLS->hh_1[96]
 + c2.v[77]*MainFormSLS->hh_1[0]
 + c2.v[78]*MainFormSLS->hh_1[64]
 + c2.v[79]*MainFormSLS->hh_1[128];
s/=N_2;
out.push_back(s);
//������ 33
s =c2.v[0]*MainFormSLS->hh_1[33]
 + c2.v[1]*MainFormSLS->hh_1[99]
 + c2.v[2]*MainFormSLS->hh_1[5]
 + c2.v[3]*MainFormSLS->hh_1[71]
 + c2.v[4]*MainFormSLS->hh_1[137]
 + c2.v[5]*MainFormSLS->hh_1[43]
 + c2.v[6]*MainFormSLS->hh_1[109]
 + c2.v[7]*MainFormSLS->hh_1[15]
 + c2.v[8]*MainFormSLS->hh_1[81]
 + c2.v[9]*MainFormSLS->hh_1[147]
 + c2.v[10]*MainFormSLS->hh_1[53]
 + c2.v[11]*MainFormSLS->hh_1[119]
 + c2.v[12]*MainFormSLS->hh_1[25]
 + c2.v[13]*MainFormSLS->hh_1[91]
 + c2.v[14]*MainFormSLS->hh_1[157]
 + c2.v[15]*MainFormSLS->hh_1[63]
 + c2.v[16]*MainFormSLS->hh_1[129]
 + c2.v[17]*MainFormSLS->hh_1[35]
 + c2.v[18]*MainFormSLS->hh_1[101]
 + c2.v[19]*MainFormSLS->hh_1[7]
 + c2.v[20]*MainFormSLS->hh_1[73]
 + c2.v[21]*MainFormSLS->hh_1[139]
 + c2.v[22]*MainFormSLS->hh_1[45]
 + c2.v[23]*MainFormSLS->hh_1[111]
 + c2.v[24]*MainFormSLS->hh_1[17]
 + c2.v[25]*MainFormSLS->hh_1[83]
 + c2.v[26]*MainFormSLS->hh_1[149]
 + c2.v[27]*MainFormSLS->hh_1[55]
 + c2.v[28]*MainFormSLS->hh_1[121]
 + c2.v[29]*MainFormSLS->hh_1[27]
 + c2.v[30]*MainFormSLS->hh_1[93]
 + c2.v[31]*MainFormSLS->hh_1[159]
 + c2.v[32]*MainFormSLS->hh_1[65]
 + c2.v[33]*MainFormSLS->hh_1[131]
 + c2.v[34]*MainFormSLS->hh_1[37]
 + c2.v[35]*MainFormSLS->hh_1[103]
 + c2.v[36]*MainFormSLS->hh_1[9]
 + c2.v[37]*MainFormSLS->hh_1[75]
 + c2.v[38]*MainFormSLS->hh_1[141]
 + c2.v[39]*MainFormSLS->hh_1[47]
 + c2.v[40]*MainFormSLS->hh_1[113]
 + c2.v[41]*MainFormSLS->hh_1[19]
 + c2.v[42]*MainFormSLS->hh_1[85]
 + c2.v[43]*MainFormSLS->hh_1[151]
 + c2.v[44]*MainFormSLS->hh_1[57]
 + c2.v[45]*MainFormSLS->hh_1[123]
 + c2.v[46]*MainFormSLS->hh_1[29]
 + c2.v[47]*MainFormSLS->hh_1[95]
 + c2.v[48]*MainFormSLS->hh_1[1]
 + c2.v[49]*MainFormSLS->hh_1[67]
 + c2.v[50]*MainFormSLS->hh_1[133]
 + c2.v[51]*MainFormSLS->hh_1[39]
 + c2.v[52]*MainFormSLS->hh_1[105]
 + c2.v[53]*MainFormSLS->hh_1[11]
 + c2.v[54]*MainFormSLS->hh_1[77]
 + c2.v[55]*MainFormSLS->hh_1[143]
 + c2.v[56]*MainFormSLS->hh_1[49]
 + c2.v[57]*MainFormSLS->hh_1[115]
 + c2.v[58]*MainFormSLS->hh_1[21]
 + c2.v[59]*MainFormSLS->hh_1[87]
 + c2.v[60]*MainFormSLS->hh_1[153]
 + c2.v[61]*MainFormSLS->hh_1[59]
 + c2.v[62]*MainFormSLS->hh_1[125]
 + c2.v[63]*MainFormSLS->hh_1[31]
 + c2.v[64]*MainFormSLS->hh_1[97]
 + c2.v[65]*MainFormSLS->hh_1[3]
 + c2.v[66]*MainFormSLS->hh_1[69]
 + c2.v[67]*MainFormSLS->hh_1[135]
 + c2.v[68]*MainFormSLS->hh_1[41]
 + c2.v[69]*MainFormSLS->hh_1[107]
 + c2.v[70]*MainFormSLS->hh_1[13]
 + c2.v[71]*MainFormSLS->hh_1[79]
 + c2.v[72]*MainFormSLS->hh_1[145]
 + c2.v[73]*MainFormSLS->hh_1[51]
 + c2.v[74]*MainFormSLS->hh_1[117]
 + c2.v[75]*MainFormSLS->hh_1[23]
 + c2.v[76]*MainFormSLS->hh_1[89]
 + c2.v[77]*MainFormSLS->hh_1[155]
 + c2.v[78]*MainFormSLS->hh_1[61]
 + c2.v[79]*MainFormSLS->hh_1[127];
s/=N_2;
out.push_back(s);
//������ 34
s =c2.v[0]*MainFormSLS->hh_1[34]
 + c2.v[1]*MainFormSLS->hh_1[102]
 + c2.v[2]*MainFormSLS->hh_1[10]
 + c2.v[3]*MainFormSLS->hh_1[78]
 + c2.v[4]*MainFormSLS->hh_1[146]
 + c2.v[5]*MainFormSLS->hh_1[54]
 + c2.v[6]*MainFormSLS->hh_1[122]
 + c2.v[7]*MainFormSLS->hh_1[30]
 + c2.v[8]*MainFormSLS->hh_1[98]
 + c2.v[9]*MainFormSLS->hh_1[6]
 + c2.v[10]*MainFormSLS->hh_1[74]
 + c2.v[11]*MainFormSLS->hh_1[142]
 + c2.v[12]*MainFormSLS->hh_1[50]
 + c2.v[13]*MainFormSLS->hh_1[118]
 + c2.v[14]*MainFormSLS->hh_1[26]
 + c2.v[15]*MainFormSLS->hh_1[94]
 + c2.v[16]*MainFormSLS->hh_1[2]
 + c2.v[17]*MainFormSLS->hh_1[70]
 + c2.v[18]*MainFormSLS->hh_1[138]
 + c2.v[19]*MainFormSLS->hh_1[46]
 + c2.v[20]*MainFormSLS->hh_1[114]
 + c2.v[21]*MainFormSLS->hh_1[22]
 + c2.v[22]*MainFormSLS->hh_1[90]
 + c2.v[23]*MainFormSLS->hh_1[158]
 + c2.v[24]*MainFormSLS->hh_1[66]
 + c2.v[25]*MainFormSLS->hh_1[134]
 + c2.v[26]*MainFormSLS->hh_1[42]
 + c2.v[27]*MainFormSLS->hh_1[110]
 + c2.v[28]*MainFormSLS->hh_1[18]
 + c2.v[29]*MainFormSLS->hh_1[86]
 + c2.v[30]*MainFormSLS->hh_1[154]
 + c2.v[31]*MainFormSLS->hh_1[62]
 + c2.v[32]*MainFormSLS->hh_1[130]
 + c2.v[33]*MainFormSLS->hh_1[38]
 + c2.v[34]*MainFormSLS->hh_1[106]
 + c2.v[35]*MainFormSLS->hh_1[14]
 + c2.v[36]*MainFormSLS->hh_1[82]
 + c2.v[37]*MainFormSLS->hh_1[150]
 + c2.v[38]*MainFormSLS->hh_1[58]
 + c2.v[39]*MainFormSLS->hh_1[126]
 + c2.v[40]*MainFormSLS->hh_1[34]
 + c2.v[41]*MainFormSLS->hh_1[102]
 + c2.v[42]*MainFormSLS->hh_1[10]
 + c2.v[43]*MainFormSLS->hh_1[78]
 + c2.v[44]*MainFormSLS->hh_1[146]
 + c2.v[45]*MainFormSLS->hh_1[54]
 + c2.v[46]*MainFormSLS->hh_1[122]
 + c2.v[47]*MainFormSLS->hh_1[30]
 + c2.v[48]*MainFormSLS->hh_1[98]
 + c2.v[49]*MainFormSLS->hh_1[6]
 + c2.v[50]*MainFormSLS->hh_1[74]
 + c2.v[51]*MainFormSLS->hh_1[142]
 + c2.v[52]*MainFormSLS->hh_1[50]
 + c2.v[53]*MainFormSLS->hh_1[118]
 + c2.v[54]*MainFormSLS->hh_1[26]
 + c2.v[55]*MainFormSLS->hh_1[94]
 + c2.v[56]*MainFormSLS->hh_1[2]
 + c2.v[57]*MainFormSLS->hh_1[70]
 + c2.v[58]*MainFormSLS->hh_1[138]
 + c2.v[59]*MainFormSLS->hh_1[46]
 + c2.v[60]*MainFormSLS->hh_1[114]
 + c2.v[61]*MainFormSLS->hh_1[22]
 + c2.v[62]*MainFormSLS->hh_1[90]
 + c2.v[63]*MainFormSLS->hh_1[158]
 + c2.v[64]*MainFormSLS->hh_1[66]
 + c2.v[65]*MainFormSLS->hh_1[134]
 + c2.v[66]*MainFormSLS->hh_1[42]
 + c2.v[67]*MainFormSLS->hh_1[110]
 + c2.v[68]*MainFormSLS->hh_1[18]
 + c2.v[69]*MainFormSLS->hh_1[86]
 + c2.v[70]*MainFormSLS->hh_1[154]
 + c2.v[71]*MainFormSLS->hh_1[62]
 + c2.v[72]*MainFormSLS->hh_1[130]
 + c2.v[73]*MainFormSLS->hh_1[38]
 + c2.v[74]*MainFormSLS->hh_1[106]
 + c2.v[75]*MainFormSLS->hh_1[14]
 + c2.v[76]*MainFormSLS->hh_1[82]
 + c2.v[77]*MainFormSLS->hh_1[150]
 + c2.v[78]*MainFormSLS->hh_1[58]
 + c2.v[79]*MainFormSLS->hh_1[126];
s/=N_2;
out.push_back(s);
//������ 35
s =c2.v[0]*MainFormSLS->hh_1[35]
 + c2.v[1]*MainFormSLS->hh_1[105]
 + c2.v[2]*MainFormSLS->hh_1[15]
 + c2.v[3]*MainFormSLS->hh_1[85]
 + c2.v[4]*MainFormSLS->hh_1[155]
 + c2.v[5]*MainFormSLS->hh_1[65]
 + c2.v[6]*MainFormSLS->hh_1[135]
 + c2.v[7]*MainFormSLS->hh_1[45]
 + c2.v[8]*MainFormSLS->hh_1[115]
 + c2.v[9]*MainFormSLS->hh_1[25]
 + c2.v[10]*MainFormSLS->hh_1[95]
 + c2.v[11]*MainFormSLS->hh_1[5]
 + c2.v[12]*MainFormSLS->hh_1[75]
 + c2.v[13]*MainFormSLS->hh_1[145]
 + c2.v[14]*MainFormSLS->hh_1[55]
 + c2.v[15]*MainFormSLS->hh_1[125]
 + c2.v[16]*MainFormSLS->hh_1[35]
 + c2.v[17]*MainFormSLS->hh_1[105]
 + c2.v[18]*MainFormSLS->hh_1[15]
 + c2.v[19]*MainFormSLS->hh_1[85]
 + c2.v[20]*MainFormSLS->hh_1[155]
 + c2.v[21]*MainFormSLS->hh_1[65]
 + c2.v[22]*MainFormSLS->hh_1[135]
 + c2.v[23]*MainFormSLS->hh_1[45]
 + c2.v[24]*MainFormSLS->hh_1[115]
 + c2.v[25]*MainFormSLS->hh_1[25]
 + c2.v[26]*MainFormSLS->hh_1[95]
 + c2.v[27]*MainFormSLS->hh_1[5]
 + c2.v[28]*MainFormSLS->hh_1[75]
 + c2.v[29]*MainFormSLS->hh_1[145]
 + c2.v[30]*MainFormSLS->hh_1[55]
 + c2.v[31]*MainFormSLS->hh_1[125]
 + c2.v[32]*MainFormSLS->hh_1[35]
 + c2.v[33]*MainFormSLS->hh_1[105]
 + c2.v[34]*MainFormSLS->hh_1[15]
 + c2.v[35]*MainFormSLS->hh_1[85]
 + c2.v[36]*MainFormSLS->hh_1[155]
 + c2.v[37]*MainFormSLS->hh_1[65]
 + c2.v[38]*MainFormSLS->hh_1[135]
 + c2.v[39]*MainFormSLS->hh_1[45]
 + c2.v[40]*MainFormSLS->hh_1[115]
 + c2.v[41]*MainFormSLS->hh_1[25]
 + c2.v[42]*MainFormSLS->hh_1[95]
 + c2.v[43]*MainFormSLS->hh_1[5]
 + c2.v[44]*MainFormSLS->hh_1[75]
 + c2.v[45]*MainFormSLS->hh_1[145]
 + c2.v[46]*MainFormSLS->hh_1[55]
 + c2.v[47]*MainFormSLS->hh_1[125]
 + c2.v[48]*MainFormSLS->hh_1[35]
 + c2.v[49]*MainFormSLS->hh_1[105]
 + c2.v[50]*MainFormSLS->hh_1[15]
 + c2.v[51]*MainFormSLS->hh_1[85]
 + c2.v[52]*MainFormSLS->hh_1[155]
 + c2.v[53]*MainFormSLS->hh_1[65]
 + c2.v[54]*MainFormSLS->hh_1[135]
 + c2.v[55]*MainFormSLS->hh_1[45]
 + c2.v[56]*MainFormSLS->hh_1[115]
 + c2.v[57]*MainFormSLS->hh_1[25]
 + c2.v[58]*MainFormSLS->hh_1[95]
 + c2.v[59]*MainFormSLS->hh_1[5]
 + c2.v[60]*MainFormSLS->hh_1[75]
 + c2.v[61]*MainFormSLS->hh_1[145]
 + c2.v[62]*MainFormSLS->hh_1[55]
 + c2.v[63]*MainFormSLS->hh_1[125]
 + c2.v[64]*MainFormSLS->hh_1[35]
 + c2.v[65]*MainFormSLS->hh_1[105]
 + c2.v[66]*MainFormSLS->hh_1[15]
 + c2.v[67]*MainFormSLS->hh_1[85]
 + c2.v[68]*MainFormSLS->hh_1[155]
 + c2.v[69]*MainFormSLS->hh_1[65]
 + c2.v[70]*MainFormSLS->hh_1[135]
 + c2.v[71]*MainFormSLS->hh_1[45]
 + c2.v[72]*MainFormSLS->hh_1[115]
 + c2.v[73]*MainFormSLS->hh_1[25]
 + c2.v[74]*MainFormSLS->hh_1[95]
 + c2.v[75]*MainFormSLS->hh_1[5]
 + c2.v[76]*MainFormSLS->hh_1[75]
 + c2.v[77]*MainFormSLS->hh_1[145]
 + c2.v[78]*MainFormSLS->hh_1[55]
 + c2.v[79]*MainFormSLS->hh_1[125];
s/=N_2;
out.push_back(s);
//������ 36
s =c2.v[0]*MainFormSLS->hh_1[36]
 + c2.v[1]*MainFormSLS->hh_1[108]
 + c2.v[2]*MainFormSLS->hh_1[20]
 + c2.v[3]*MainFormSLS->hh_1[92]
 + c2.v[4]*MainFormSLS->hh_1[4]
 + c2.v[5]*MainFormSLS->hh_1[76]
 + c2.v[6]*MainFormSLS->hh_1[148]
 + c2.v[7]*MainFormSLS->hh_1[60]
 + c2.v[8]*MainFormSLS->hh_1[132]
 + c2.v[9]*MainFormSLS->hh_1[44]
 + c2.v[10]*MainFormSLS->hh_1[116]
 + c2.v[11]*MainFormSLS->hh_1[28]
 + c2.v[12]*MainFormSLS->hh_1[100]
 + c2.v[13]*MainFormSLS->hh_1[12]
 + c2.v[14]*MainFormSLS->hh_1[84]
 + c2.v[15]*MainFormSLS->hh_1[156]
 + c2.v[16]*MainFormSLS->hh_1[68]
 + c2.v[17]*MainFormSLS->hh_1[140]
 + c2.v[18]*MainFormSLS->hh_1[52]
 + c2.v[19]*MainFormSLS->hh_1[124]
 + c2.v[20]*MainFormSLS->hh_1[36]
 + c2.v[21]*MainFormSLS->hh_1[108]
 + c2.v[22]*MainFormSLS->hh_1[20]
 + c2.v[23]*MainFormSLS->hh_1[92]
 + c2.v[24]*MainFormSLS->hh_1[4]
 + c2.v[25]*MainFormSLS->hh_1[76]
 + c2.v[26]*MainFormSLS->hh_1[148]
 + c2.v[27]*MainFormSLS->hh_1[60]
 + c2.v[28]*MainFormSLS->hh_1[132]
 + c2.v[29]*MainFormSLS->hh_1[44]
 + c2.v[30]*MainFormSLS->hh_1[116]
 + c2.v[31]*MainFormSLS->hh_1[28]
 + c2.v[32]*MainFormSLS->hh_1[100]
 + c2.v[33]*MainFormSLS->hh_1[12]
 + c2.v[34]*MainFormSLS->hh_1[84]
 + c2.v[35]*MainFormSLS->hh_1[156]
 + c2.v[36]*MainFormSLS->hh_1[68]
 + c2.v[37]*MainFormSLS->hh_1[140]
 + c2.v[38]*MainFormSLS->hh_1[52]
 + c2.v[39]*MainFormSLS->hh_1[124]
 + c2.v[40]*MainFormSLS->hh_1[36]
 + c2.v[41]*MainFormSLS->hh_1[108]
 + c2.v[42]*MainFormSLS->hh_1[20]
 + c2.v[43]*MainFormSLS->hh_1[92]
 + c2.v[44]*MainFormSLS->hh_1[4]
 + c2.v[45]*MainFormSLS->hh_1[76]
 + c2.v[46]*MainFormSLS->hh_1[148]
 + c2.v[47]*MainFormSLS->hh_1[60]
 + c2.v[48]*MainFormSLS->hh_1[132]
 + c2.v[49]*MainFormSLS->hh_1[44]
 + c2.v[50]*MainFormSLS->hh_1[116]
 + c2.v[51]*MainFormSLS->hh_1[28]
 + c2.v[52]*MainFormSLS->hh_1[100]
 + c2.v[53]*MainFormSLS->hh_1[12]
 + c2.v[54]*MainFormSLS->hh_1[84]
 + c2.v[55]*MainFormSLS->hh_1[156]
 + c2.v[56]*MainFormSLS->hh_1[68]
 + c2.v[57]*MainFormSLS->hh_1[140]
 + c2.v[58]*MainFormSLS->hh_1[52]
 + c2.v[59]*MainFormSLS->hh_1[124]
 + c2.v[60]*MainFormSLS->hh_1[36]
 + c2.v[61]*MainFormSLS->hh_1[108]
 + c2.v[62]*MainFormSLS->hh_1[20]
 + c2.v[63]*MainFormSLS->hh_1[92]
 + c2.v[64]*MainFormSLS->hh_1[4]
 + c2.v[65]*MainFormSLS->hh_1[76]
 + c2.v[66]*MainFormSLS->hh_1[148]
 + c2.v[67]*MainFormSLS->hh_1[60]
 + c2.v[68]*MainFormSLS->hh_1[132]
 + c2.v[69]*MainFormSLS->hh_1[44]
 + c2.v[70]*MainFormSLS->hh_1[116]
 + c2.v[71]*MainFormSLS->hh_1[28]
 + c2.v[72]*MainFormSLS->hh_1[100]
 + c2.v[73]*MainFormSLS->hh_1[12]
 + c2.v[74]*MainFormSLS->hh_1[84]
 + c2.v[75]*MainFormSLS->hh_1[156]
 + c2.v[76]*MainFormSLS->hh_1[68]
 + c2.v[77]*MainFormSLS->hh_1[140]
 + c2.v[78]*MainFormSLS->hh_1[52]
 + c2.v[79]*MainFormSLS->hh_1[124];
s/=N_2;
out.push_back(s);
//������ 37
s =c2.v[0]*MainFormSLS->hh_1[37]
 + c2.v[1]*MainFormSLS->hh_1[111]
 + c2.v[2]*MainFormSLS->hh_1[25]
 + c2.v[3]*MainFormSLS->hh_1[99]
 + c2.v[4]*MainFormSLS->hh_1[13]
 + c2.v[5]*MainFormSLS->hh_1[87]
 + c2.v[6]*MainFormSLS->hh_1[1]
 + c2.v[7]*MainFormSLS->hh_1[75]
 + c2.v[8]*MainFormSLS->hh_1[149]
 + c2.v[9]*MainFormSLS->hh_1[63]
 + c2.v[10]*MainFormSLS->hh_1[137]
 + c2.v[11]*MainFormSLS->hh_1[51]
 + c2.v[12]*MainFormSLS->hh_1[125]
 + c2.v[13]*MainFormSLS->hh_1[39]
 + c2.v[14]*MainFormSLS->hh_1[113]
 + c2.v[15]*MainFormSLS->hh_1[27]
 + c2.v[16]*MainFormSLS->hh_1[101]
 + c2.v[17]*MainFormSLS->hh_1[15]
 + c2.v[18]*MainFormSLS->hh_1[89]
 + c2.v[19]*MainFormSLS->hh_1[3]
 + c2.v[20]*MainFormSLS->hh_1[77]
 + c2.v[21]*MainFormSLS->hh_1[151]
 + c2.v[22]*MainFormSLS->hh_1[65]
 + c2.v[23]*MainFormSLS->hh_1[139]
 + c2.v[24]*MainFormSLS->hh_1[53]
 + c2.v[25]*MainFormSLS->hh_1[127]
 + c2.v[26]*MainFormSLS->hh_1[41]
 + c2.v[27]*MainFormSLS->hh_1[115]
 + c2.v[28]*MainFormSLS->hh_1[29]
 + c2.v[29]*MainFormSLS->hh_1[103]
 + c2.v[30]*MainFormSLS->hh_1[17]
 + c2.v[31]*MainFormSLS->hh_1[91]
 + c2.v[32]*MainFormSLS->hh_1[5]
 + c2.v[33]*MainFormSLS->hh_1[79]
 + c2.v[34]*MainFormSLS->hh_1[153]
 + c2.v[35]*MainFormSLS->hh_1[67]
 + c2.v[36]*MainFormSLS->hh_1[141]
 + c2.v[37]*MainFormSLS->hh_1[55]
 + c2.v[38]*MainFormSLS->hh_1[129]
 + c2.v[39]*MainFormSLS->hh_1[43]
 + c2.v[40]*MainFormSLS->hh_1[117]
 + c2.v[41]*MainFormSLS->hh_1[31]
 + c2.v[42]*MainFormSLS->hh_1[105]
 + c2.v[43]*MainFormSLS->hh_1[19]
 + c2.v[44]*MainFormSLS->hh_1[93]
 + c2.v[45]*MainFormSLS->hh_1[7]
 + c2.v[46]*MainFormSLS->hh_1[81]
 + c2.v[47]*MainFormSLS->hh_1[155]
 + c2.v[48]*MainFormSLS->hh_1[69]
 + c2.v[49]*MainFormSLS->hh_1[143]
 + c2.v[50]*MainFormSLS->hh_1[57]
 + c2.v[51]*MainFormSLS->hh_1[131]
 + c2.v[52]*MainFormSLS->hh_1[45]
 + c2.v[53]*MainFormSLS->hh_1[119]
 + c2.v[54]*MainFormSLS->hh_1[33]
 + c2.v[55]*MainFormSLS->hh_1[107]
 + c2.v[56]*MainFormSLS->hh_1[21]
 + c2.v[57]*MainFormSLS->hh_1[95]
 + c2.v[58]*MainFormSLS->hh_1[9]
 + c2.v[59]*MainFormSLS->hh_1[83]
 + c2.v[60]*MainFormSLS->hh_1[157]
 + c2.v[61]*MainFormSLS->hh_1[71]
 + c2.v[62]*MainFormSLS->hh_1[145]
 + c2.v[63]*MainFormSLS->hh_1[59]
 + c2.v[64]*MainFormSLS->hh_1[133]
 + c2.v[65]*MainFormSLS->hh_1[47]
 + c2.v[66]*MainFormSLS->hh_1[121]
 + c2.v[67]*MainFormSLS->hh_1[35]
 + c2.v[68]*MainFormSLS->hh_1[109]
 + c2.v[69]*MainFormSLS->hh_1[23]
 + c2.v[70]*MainFormSLS->hh_1[97]
 + c2.v[71]*MainFormSLS->hh_1[11]
 + c2.v[72]*MainFormSLS->hh_1[85]
 + c2.v[73]*MainFormSLS->hh_1[159]
 + c2.v[74]*MainFormSLS->hh_1[73]
 + c2.v[75]*MainFormSLS->hh_1[147]
 + c2.v[76]*MainFormSLS->hh_1[61]
 + c2.v[77]*MainFormSLS->hh_1[135]
 + c2.v[78]*MainFormSLS->hh_1[49]
 + c2.v[79]*MainFormSLS->hh_1[123];
s/=N_2;
out.push_back(s);
//������ 38
s =c2.v[0]*MainFormSLS->hh_1[38]
 + c2.v[1]*MainFormSLS->hh_1[114]
 + c2.v[2]*MainFormSLS->hh_1[30]
 + c2.v[3]*MainFormSLS->hh_1[106]
 + c2.v[4]*MainFormSLS->hh_1[22]
 + c2.v[5]*MainFormSLS->hh_1[98]
 + c2.v[6]*MainFormSLS->hh_1[14]
 + c2.v[7]*MainFormSLS->hh_1[90]
 + c2.v[8]*MainFormSLS->hh_1[6]
 + c2.v[9]*MainFormSLS->hh_1[82]
 + c2.v[10]*MainFormSLS->hh_1[158]
 + c2.v[11]*MainFormSLS->hh_1[74]
 + c2.v[12]*MainFormSLS->hh_1[150]
 + c2.v[13]*MainFormSLS->hh_1[66]
 + c2.v[14]*MainFormSLS->hh_1[142]
 + c2.v[15]*MainFormSLS->hh_1[58]
 + c2.v[16]*MainFormSLS->hh_1[134]
 + c2.v[17]*MainFormSLS->hh_1[50]
 + c2.v[18]*MainFormSLS->hh_1[126]
 + c2.v[19]*MainFormSLS->hh_1[42]
 + c2.v[20]*MainFormSLS->hh_1[118]
 + c2.v[21]*MainFormSLS->hh_1[34]
 + c2.v[22]*MainFormSLS->hh_1[110]
 + c2.v[23]*MainFormSLS->hh_1[26]
 + c2.v[24]*MainFormSLS->hh_1[102]
 + c2.v[25]*MainFormSLS->hh_1[18]
 + c2.v[26]*MainFormSLS->hh_1[94]
 + c2.v[27]*MainFormSLS->hh_1[10]
 + c2.v[28]*MainFormSLS->hh_1[86]
 + c2.v[29]*MainFormSLS->hh_1[2]
 + c2.v[30]*MainFormSLS->hh_1[78]
 + c2.v[31]*MainFormSLS->hh_1[154]
 + c2.v[32]*MainFormSLS->hh_1[70]
 + c2.v[33]*MainFormSLS->hh_1[146]
 + c2.v[34]*MainFormSLS->hh_1[62]
 + c2.v[35]*MainFormSLS->hh_1[138]
 + c2.v[36]*MainFormSLS->hh_1[54]
 + c2.v[37]*MainFormSLS->hh_1[130]
 + c2.v[38]*MainFormSLS->hh_1[46]
 + c2.v[39]*MainFormSLS->hh_1[122]
 + c2.v[40]*MainFormSLS->hh_1[38]
 + c2.v[41]*MainFormSLS->hh_1[114]
 + c2.v[42]*MainFormSLS->hh_1[30]
 + c2.v[43]*MainFormSLS->hh_1[106]
 + c2.v[44]*MainFormSLS->hh_1[22]
 + c2.v[45]*MainFormSLS->hh_1[98]
 + c2.v[46]*MainFormSLS->hh_1[14]
 + c2.v[47]*MainFormSLS->hh_1[90]
 + c2.v[48]*MainFormSLS->hh_1[6]
 + c2.v[49]*MainFormSLS->hh_1[82]
 + c2.v[50]*MainFormSLS->hh_1[158]
 + c2.v[51]*MainFormSLS->hh_1[74]
 + c2.v[52]*MainFormSLS->hh_1[150]
 + c2.v[53]*MainFormSLS->hh_1[66]
 + c2.v[54]*MainFormSLS->hh_1[142]
 + c2.v[55]*MainFormSLS->hh_1[58]
 + c2.v[56]*MainFormSLS->hh_1[134]
 + c2.v[57]*MainFormSLS->hh_1[50]
 + c2.v[58]*MainFormSLS->hh_1[126]
 + c2.v[59]*MainFormSLS->hh_1[42]
 + c2.v[60]*MainFormSLS->hh_1[118]
 + c2.v[61]*MainFormSLS->hh_1[34]
 + c2.v[62]*MainFormSLS->hh_1[110]
 + c2.v[63]*MainFormSLS->hh_1[26]
 + c2.v[64]*MainFormSLS->hh_1[102]
 + c2.v[65]*MainFormSLS->hh_1[18]
 + c2.v[66]*MainFormSLS->hh_1[94]
 + c2.v[67]*MainFormSLS->hh_1[10]
 + c2.v[68]*MainFormSLS->hh_1[86]
 + c2.v[69]*MainFormSLS->hh_1[2]
 + c2.v[70]*MainFormSLS->hh_1[78]
 + c2.v[71]*MainFormSLS->hh_1[154]
 + c2.v[72]*MainFormSLS->hh_1[70]
 + c2.v[73]*MainFormSLS->hh_1[146]
 + c2.v[74]*MainFormSLS->hh_1[62]
 + c2.v[75]*MainFormSLS->hh_1[138]
 + c2.v[76]*MainFormSLS->hh_1[54]
 + c2.v[77]*MainFormSLS->hh_1[130]
 + c2.v[78]*MainFormSLS->hh_1[46]
 + c2.v[79]*MainFormSLS->hh_1[122];
s/=N_2;
out.push_back(s);
//������ 39
s =c2.v[0]*MainFormSLS->hh_1[39]
 + c2.v[1]*MainFormSLS->hh_1[117]
 + c2.v[2]*MainFormSLS->hh_1[35]
 + c2.v[3]*MainFormSLS->hh_1[113]
 + c2.v[4]*MainFormSLS->hh_1[31]
 + c2.v[5]*MainFormSLS->hh_1[109]
 + c2.v[6]*MainFormSLS->hh_1[27]
 + c2.v[7]*MainFormSLS->hh_1[105]
 + c2.v[8]*MainFormSLS->hh_1[23]
 + c2.v[9]*MainFormSLS->hh_1[101]
 + c2.v[10]*MainFormSLS->hh_1[19]
 + c2.v[11]*MainFormSLS->hh_1[97]
 + c2.v[12]*MainFormSLS->hh_1[15]
 + c2.v[13]*MainFormSLS->hh_1[93]
 + c2.v[14]*MainFormSLS->hh_1[11]
 + c2.v[15]*MainFormSLS->hh_1[89]
 + c2.v[16]*MainFormSLS->hh_1[7]
 + c2.v[17]*MainFormSLS->hh_1[85]
 + c2.v[18]*MainFormSLS->hh_1[3]
 + c2.v[19]*MainFormSLS->hh_1[81]
 + c2.v[20]*MainFormSLS->hh_1[159]
 + c2.v[21]*MainFormSLS->hh_1[77]
 + c2.v[22]*MainFormSLS->hh_1[155]
 + c2.v[23]*MainFormSLS->hh_1[73]
 + c2.v[24]*MainFormSLS->hh_1[151]
 + c2.v[25]*MainFormSLS->hh_1[69]
 + c2.v[26]*MainFormSLS->hh_1[147]
 + c2.v[27]*MainFormSLS->hh_1[65]
 + c2.v[28]*MainFormSLS->hh_1[143]
 + c2.v[29]*MainFormSLS->hh_1[61]
 + c2.v[30]*MainFormSLS->hh_1[139]
 + c2.v[31]*MainFormSLS->hh_1[57]
 + c2.v[32]*MainFormSLS->hh_1[135]
 + c2.v[33]*MainFormSLS->hh_1[53]
 + c2.v[34]*MainFormSLS->hh_1[131]
 + c2.v[35]*MainFormSLS->hh_1[49]
 + c2.v[36]*MainFormSLS->hh_1[127]
 + c2.v[37]*MainFormSLS->hh_1[45]
 + c2.v[38]*MainFormSLS->hh_1[123]
 + c2.v[39]*MainFormSLS->hh_1[41]
 + c2.v[40]*MainFormSLS->hh_1[119]
 + c2.v[41]*MainFormSLS->hh_1[37]
 + c2.v[42]*MainFormSLS->hh_1[115]
 + c2.v[43]*MainFormSLS->hh_1[33]
 + c2.v[44]*MainFormSLS->hh_1[111]
 + c2.v[45]*MainFormSLS->hh_1[29]
 + c2.v[46]*MainFormSLS->hh_1[107]
 + c2.v[47]*MainFormSLS->hh_1[25]
 + c2.v[48]*MainFormSLS->hh_1[103]
 + c2.v[49]*MainFormSLS->hh_1[21]
 + c2.v[50]*MainFormSLS->hh_1[99]
 + c2.v[51]*MainFormSLS->hh_1[17]
 + c2.v[52]*MainFormSLS->hh_1[95]
 + c2.v[53]*MainFormSLS->hh_1[13]
 + c2.v[54]*MainFormSLS->hh_1[91]
 + c2.v[55]*MainFormSLS->hh_1[9]
 + c2.v[56]*MainFormSLS->hh_1[87]
 + c2.v[57]*MainFormSLS->hh_1[5]
 + c2.v[58]*MainFormSLS->hh_1[83]
 + c2.v[59]*MainFormSLS->hh_1[1]
 + c2.v[60]*MainFormSLS->hh_1[79]
 + c2.v[61]*MainFormSLS->hh_1[157]
 + c2.v[62]*MainFormSLS->hh_1[75]
 + c2.v[63]*MainFormSLS->hh_1[153]
 + c2.v[64]*MainFormSLS->hh_1[71]
 + c2.v[65]*MainFormSLS->hh_1[149]
 + c2.v[66]*MainFormSLS->hh_1[67]
 + c2.v[67]*MainFormSLS->hh_1[145]
 + c2.v[68]*MainFormSLS->hh_1[63]
 + c2.v[69]*MainFormSLS->hh_1[141]
 + c2.v[70]*MainFormSLS->hh_1[59]
 + c2.v[71]*MainFormSLS->hh_1[137]
 + c2.v[72]*MainFormSLS->hh_1[55]
 + c2.v[73]*MainFormSLS->hh_1[133]
 + c2.v[74]*MainFormSLS->hh_1[51]
 + c2.v[75]*MainFormSLS->hh_1[129]
 + c2.v[76]*MainFormSLS->hh_1[47]
 + c2.v[77]*MainFormSLS->hh_1[125]
 + c2.v[78]*MainFormSLS->hh_1[43]
 + c2.v[79]*MainFormSLS->hh_1[121];
s/=N_2;
out.push_back(s);
//������ 40
s =c2.v[0]*MainFormSLS->hh_1[40]
 + c2.v[1]*MainFormSLS->hh_1[120]
 + c2.v[2]*MainFormSLS->hh_1[40]
 + c2.v[3]*MainFormSLS->hh_1[120]
 + c2.v[4]*MainFormSLS->hh_1[40]
 + c2.v[5]*MainFormSLS->hh_1[120]
 + c2.v[6]*MainFormSLS->hh_1[40]
 + c2.v[7]*MainFormSLS->hh_1[120]
 + c2.v[8]*MainFormSLS->hh_1[40]
 + c2.v[9]*MainFormSLS->hh_1[120]
 + c2.v[10]*MainFormSLS->hh_1[40]
 + c2.v[11]*MainFormSLS->hh_1[120]
 + c2.v[12]*MainFormSLS->hh_1[40]
 + c2.v[13]*MainFormSLS->hh_1[120]
 + c2.v[14]*MainFormSLS->hh_1[40]
 + c2.v[15]*MainFormSLS->hh_1[120]
 + c2.v[16]*MainFormSLS->hh_1[40]
 + c2.v[17]*MainFormSLS->hh_1[120]
 + c2.v[18]*MainFormSLS->hh_1[40]
 + c2.v[19]*MainFormSLS->hh_1[120]
 + c2.v[20]*MainFormSLS->hh_1[40]
 + c2.v[21]*MainFormSLS->hh_1[120]
 + c2.v[22]*MainFormSLS->hh_1[40]
 + c2.v[23]*MainFormSLS->hh_1[120]
 + c2.v[24]*MainFormSLS->hh_1[40]
 + c2.v[25]*MainFormSLS->hh_1[120]
 + c2.v[26]*MainFormSLS->hh_1[40]
 + c2.v[27]*MainFormSLS->hh_1[120]
 + c2.v[28]*MainFormSLS->hh_1[40]
 + c2.v[29]*MainFormSLS->hh_1[120]
 + c2.v[30]*MainFormSLS->hh_1[40]
 + c2.v[31]*MainFormSLS->hh_1[120]
 + c2.v[32]*MainFormSLS->hh_1[40]
 + c2.v[33]*MainFormSLS->hh_1[120]
 + c2.v[34]*MainFormSLS->hh_1[40]
 + c2.v[35]*MainFormSLS->hh_1[120]
 + c2.v[36]*MainFormSLS->hh_1[40]
 + c2.v[37]*MainFormSLS->hh_1[120]
 + c2.v[38]*MainFormSLS->hh_1[40]
 + c2.v[39]*MainFormSLS->hh_1[120]
 + c2.v[40]*MainFormSLS->hh_1[40]
 + c2.v[41]*MainFormSLS->hh_1[120]
 + c2.v[42]*MainFormSLS->hh_1[40]
 + c2.v[43]*MainFormSLS->hh_1[120]
 + c2.v[44]*MainFormSLS->hh_1[40]
 + c2.v[45]*MainFormSLS->hh_1[120]
 + c2.v[46]*MainFormSLS->hh_1[40]
 + c2.v[47]*MainFormSLS->hh_1[120]
 + c2.v[48]*MainFormSLS->hh_1[40]
 + c2.v[49]*MainFormSLS->hh_1[120]
 + c2.v[50]*MainFormSLS->hh_1[40]
 + c2.v[51]*MainFormSLS->hh_1[120]
 + c2.v[52]*MainFormSLS->hh_1[40]
 + c2.v[53]*MainFormSLS->hh_1[120]
 + c2.v[54]*MainFormSLS->hh_1[40]
 + c2.v[55]*MainFormSLS->hh_1[120]
 + c2.v[56]*MainFormSLS->hh_1[40]
 + c2.v[57]*MainFormSLS->hh_1[120]
 + c2.v[58]*MainFormSLS->hh_1[40]
 + c2.v[59]*MainFormSLS->hh_1[120]
 + c2.v[60]*MainFormSLS->hh_1[40]
 + c2.v[61]*MainFormSLS->hh_1[120]
 + c2.v[62]*MainFormSLS->hh_1[40]
 + c2.v[63]*MainFormSLS->hh_1[120]
 + c2.v[64]*MainFormSLS->hh_1[40]
 + c2.v[65]*MainFormSLS->hh_1[120]
 + c2.v[66]*MainFormSLS->hh_1[40]
 + c2.v[67]*MainFormSLS->hh_1[120]
 + c2.v[68]*MainFormSLS->hh_1[40]
 + c2.v[69]*MainFormSLS->hh_1[120]
 + c2.v[70]*MainFormSLS->hh_1[40]
 + c2.v[71]*MainFormSLS->hh_1[120]
 + c2.v[72]*MainFormSLS->hh_1[40]
 + c2.v[73]*MainFormSLS->hh_1[120]
 + c2.v[74]*MainFormSLS->hh_1[40]
 + c2.v[75]*MainFormSLS->hh_1[120]
 + c2.v[76]*MainFormSLS->hh_1[40]
 + c2.v[77]*MainFormSLS->hh_1[120]
 + c2.v[78]*MainFormSLS->hh_1[40]
 + c2.v[79]*MainFormSLS->hh_1[120];
s/=N_2;
out.push_back(s);
//������ 41
s =c2.v[0]*MainFormSLS->hh_1[41]
 + c2.v[1]*MainFormSLS->hh_1[123]
 + c2.v[2]*MainFormSLS->hh_1[45]
 + c2.v[3]*MainFormSLS->hh_1[127]
 + c2.v[4]*MainFormSLS->hh_1[49]
 + c2.v[5]*MainFormSLS->hh_1[131]
 + c2.v[6]*MainFormSLS->hh_1[53]
 + c2.v[7]*MainFormSLS->hh_1[135]
 + c2.v[8]*MainFormSLS->hh_1[57]
 + c2.v[9]*MainFormSLS->hh_1[139]
 + c2.v[10]*MainFormSLS->hh_1[61]
 + c2.v[11]*MainFormSLS->hh_1[143]
 + c2.v[12]*MainFormSLS->hh_1[65]
 + c2.v[13]*MainFormSLS->hh_1[147]
 + c2.v[14]*MainFormSLS->hh_1[69]
 + c2.v[15]*MainFormSLS->hh_1[151]
 + c2.v[16]*MainFormSLS->hh_1[73]
 + c2.v[17]*MainFormSLS->hh_1[155]
 + c2.v[18]*MainFormSLS->hh_1[77]
 + c2.v[19]*MainFormSLS->hh_1[159]
 + c2.v[20]*MainFormSLS->hh_1[81]
 + c2.v[21]*MainFormSLS->hh_1[3]
 + c2.v[22]*MainFormSLS->hh_1[85]
 + c2.v[23]*MainFormSLS->hh_1[7]
 + c2.v[24]*MainFormSLS->hh_1[89]
 + c2.v[25]*MainFormSLS->hh_1[11]
 + c2.v[26]*MainFormSLS->hh_1[93]
 + c2.v[27]*MainFormSLS->hh_1[15]
 + c2.v[28]*MainFormSLS->hh_1[97]
 + c2.v[29]*MainFormSLS->hh_1[19]
 + c2.v[30]*MainFormSLS->hh_1[101]
 + c2.v[31]*MainFormSLS->hh_1[23]
 + c2.v[32]*MainFormSLS->hh_1[105]
 + c2.v[33]*MainFormSLS->hh_1[27]
 + c2.v[34]*MainFormSLS->hh_1[109]
 + c2.v[35]*MainFormSLS->hh_1[31]
 + c2.v[36]*MainFormSLS->hh_1[113]
 + c2.v[37]*MainFormSLS->hh_1[35]
 + c2.v[38]*MainFormSLS->hh_1[117]
 + c2.v[39]*MainFormSLS->hh_1[39]
 + c2.v[40]*MainFormSLS->hh_1[121]
 + c2.v[41]*MainFormSLS->hh_1[43]
 + c2.v[42]*MainFormSLS->hh_1[125]
 + c2.v[43]*MainFormSLS->hh_1[47]
 + c2.v[44]*MainFormSLS->hh_1[129]
 + c2.v[45]*MainFormSLS->hh_1[51]
 + c2.v[46]*MainFormSLS->hh_1[133]
 + c2.v[47]*MainFormSLS->hh_1[55]
 + c2.v[48]*MainFormSLS->hh_1[137]
 + c2.v[49]*MainFormSLS->hh_1[59]
 + c2.v[50]*MainFormSLS->hh_1[141]
 + c2.v[51]*MainFormSLS->hh_1[63]
 + c2.v[52]*MainFormSLS->hh_1[145]
 + c2.v[53]*MainFormSLS->hh_1[67]
 + c2.v[54]*MainFormSLS->hh_1[149]
 + c2.v[55]*MainFormSLS->hh_1[71]
 + c2.v[56]*MainFormSLS->hh_1[153]
 + c2.v[57]*MainFormSLS->hh_1[75]
 + c2.v[58]*MainFormSLS->hh_1[157]
 + c2.v[59]*MainFormSLS->hh_1[79]
 + c2.v[60]*MainFormSLS->hh_1[1]
 + c2.v[61]*MainFormSLS->hh_1[83]
 + c2.v[62]*MainFormSLS->hh_1[5]
 + c2.v[63]*MainFormSLS->hh_1[87]
 + c2.v[64]*MainFormSLS->hh_1[9]
 + c2.v[65]*MainFormSLS->hh_1[91]
 + c2.v[66]*MainFormSLS->hh_1[13]
 + c2.v[67]*MainFormSLS->hh_1[95]
 + c2.v[68]*MainFormSLS->hh_1[17]
 + c2.v[69]*MainFormSLS->hh_1[99]
 + c2.v[70]*MainFormSLS->hh_1[21]
 + c2.v[71]*MainFormSLS->hh_1[103]
 + c2.v[72]*MainFormSLS->hh_1[25]
 + c2.v[73]*MainFormSLS->hh_1[107]
 + c2.v[74]*MainFormSLS->hh_1[29]
 + c2.v[75]*MainFormSLS->hh_1[111]
 + c2.v[76]*MainFormSLS->hh_1[33]
 + c2.v[77]*MainFormSLS->hh_1[115]
 + c2.v[78]*MainFormSLS->hh_1[37]
 + c2.v[79]*MainFormSLS->hh_1[119];
s/=N_2;
out.push_back(s);
//������ 42
s =c2.v[0]*MainFormSLS->hh_1[42]
 + c2.v[1]*MainFormSLS->hh_1[126]
 + c2.v[2]*MainFormSLS->hh_1[50]
 + c2.v[3]*MainFormSLS->hh_1[134]
 + c2.v[4]*MainFormSLS->hh_1[58]
 + c2.v[5]*MainFormSLS->hh_1[142]
 + c2.v[6]*MainFormSLS->hh_1[66]
 + c2.v[7]*MainFormSLS->hh_1[150]
 + c2.v[8]*MainFormSLS->hh_1[74]
 + c2.v[9]*MainFormSLS->hh_1[158]
 + c2.v[10]*MainFormSLS->hh_1[82]
 + c2.v[11]*MainFormSLS->hh_1[6]
 + c2.v[12]*MainFormSLS->hh_1[90]
 + c2.v[13]*MainFormSLS->hh_1[14]
 + c2.v[14]*MainFormSLS->hh_1[98]
 + c2.v[15]*MainFormSLS->hh_1[22]
 + c2.v[16]*MainFormSLS->hh_1[106]
 + c2.v[17]*MainFormSLS->hh_1[30]
 + c2.v[18]*MainFormSLS->hh_1[114]
 + c2.v[19]*MainFormSLS->hh_1[38]
 + c2.v[20]*MainFormSLS->hh_1[122]
 + c2.v[21]*MainFormSLS->hh_1[46]
 + c2.v[22]*MainFormSLS->hh_1[130]
 + c2.v[23]*MainFormSLS->hh_1[54]
 + c2.v[24]*MainFormSLS->hh_1[138]
 + c2.v[25]*MainFormSLS->hh_1[62]
 + c2.v[26]*MainFormSLS->hh_1[146]
 + c2.v[27]*MainFormSLS->hh_1[70]
 + c2.v[28]*MainFormSLS->hh_1[154]
 + c2.v[29]*MainFormSLS->hh_1[78]
 + c2.v[30]*MainFormSLS->hh_1[2]
 + c2.v[31]*MainFormSLS->hh_1[86]
 + c2.v[32]*MainFormSLS->hh_1[10]
 + c2.v[33]*MainFormSLS->hh_1[94]
 + c2.v[34]*MainFormSLS->hh_1[18]
 + c2.v[35]*MainFormSLS->hh_1[102]
 + c2.v[36]*MainFormSLS->hh_1[26]
 + c2.v[37]*MainFormSLS->hh_1[110]
 + c2.v[38]*MainFormSLS->hh_1[34]
 + c2.v[39]*MainFormSLS->hh_1[118]
 + c2.v[40]*MainFormSLS->hh_1[42]
 + c2.v[41]*MainFormSLS->hh_1[126]
 + c2.v[42]*MainFormSLS->hh_1[50]
 + c2.v[43]*MainFormSLS->hh_1[134]
 + c2.v[44]*MainFormSLS->hh_1[58]
 + c2.v[45]*MainFormSLS->hh_1[142]
 + c2.v[46]*MainFormSLS->hh_1[66]
 + c2.v[47]*MainFormSLS->hh_1[150]
 + c2.v[48]*MainFormSLS->hh_1[74]
 + c2.v[49]*MainFormSLS->hh_1[158]
 + c2.v[50]*MainFormSLS->hh_1[82]
 + c2.v[51]*MainFormSLS->hh_1[6]
 + c2.v[52]*MainFormSLS->hh_1[90]
 + c2.v[53]*MainFormSLS->hh_1[14]
 + c2.v[54]*MainFormSLS->hh_1[98]
 + c2.v[55]*MainFormSLS->hh_1[22]
 + c2.v[56]*MainFormSLS->hh_1[106]
 + c2.v[57]*MainFormSLS->hh_1[30]
 + c2.v[58]*MainFormSLS->hh_1[114]
 + c2.v[59]*MainFormSLS->hh_1[38]
 + c2.v[60]*MainFormSLS->hh_1[122]
 + c2.v[61]*MainFormSLS->hh_1[46]
 + c2.v[62]*MainFormSLS->hh_1[130]
 + c2.v[63]*MainFormSLS->hh_1[54]
 + c2.v[64]*MainFormSLS->hh_1[138]
 + c2.v[65]*MainFormSLS->hh_1[62]
 + c2.v[66]*MainFormSLS->hh_1[146]
 + c2.v[67]*MainFormSLS->hh_1[70]
 + c2.v[68]*MainFormSLS->hh_1[154]
 + c2.v[69]*MainFormSLS->hh_1[78]
 + c2.v[70]*MainFormSLS->hh_1[2]
 + c2.v[71]*MainFormSLS->hh_1[86]
 + c2.v[72]*MainFormSLS->hh_1[10]
 + c2.v[73]*MainFormSLS->hh_1[94]
 + c2.v[74]*MainFormSLS->hh_1[18]
 + c2.v[75]*MainFormSLS->hh_1[102]
 + c2.v[76]*MainFormSLS->hh_1[26]
 + c2.v[77]*MainFormSLS->hh_1[110]
 + c2.v[78]*MainFormSLS->hh_1[34]
 + c2.v[79]*MainFormSLS->hh_1[118];
s/=N_2;
out.push_back(s);
//������ 43
s =c2.v[0]*MainFormSLS->hh_1[43]
 + c2.v[1]*MainFormSLS->hh_1[129]
 + c2.v[2]*MainFormSLS->hh_1[55]
 + c2.v[3]*MainFormSLS->hh_1[141]
 + c2.v[4]*MainFormSLS->hh_1[67]
 + c2.v[5]*MainFormSLS->hh_1[153]
 + c2.v[6]*MainFormSLS->hh_1[79]
 + c2.v[7]*MainFormSLS->hh_1[5]
 + c2.v[8]*MainFormSLS->hh_1[91]
 + c2.v[9]*MainFormSLS->hh_1[17]
 + c2.v[10]*MainFormSLS->hh_1[103]
 + c2.v[11]*MainFormSLS->hh_1[29]
 + c2.v[12]*MainFormSLS->hh_1[115]
 + c2.v[13]*MainFormSLS->hh_1[41]
 + c2.v[14]*MainFormSLS->hh_1[127]
 + c2.v[15]*MainFormSLS->hh_1[53]
 + c2.v[16]*MainFormSLS->hh_1[139]
 + c2.v[17]*MainFormSLS->hh_1[65]
 + c2.v[18]*MainFormSLS->hh_1[151]
 + c2.v[19]*MainFormSLS->hh_1[77]
 + c2.v[20]*MainFormSLS->hh_1[3]
 + c2.v[21]*MainFormSLS->hh_1[89]
 + c2.v[22]*MainFormSLS->hh_1[15]
 + c2.v[23]*MainFormSLS->hh_1[101]
 + c2.v[24]*MainFormSLS->hh_1[27]
 + c2.v[25]*MainFormSLS->hh_1[113]
 + c2.v[26]*MainFormSLS->hh_1[39]
 + c2.v[27]*MainFormSLS->hh_1[125]
 + c2.v[28]*MainFormSLS->hh_1[51]
 + c2.v[29]*MainFormSLS->hh_1[137]
 + c2.v[30]*MainFormSLS->hh_1[63]
 + c2.v[31]*MainFormSLS->hh_1[149]
 + c2.v[32]*MainFormSLS->hh_1[75]
 + c2.v[33]*MainFormSLS->hh_1[1]
 + c2.v[34]*MainFormSLS->hh_1[87]
 + c2.v[35]*MainFormSLS->hh_1[13]
 + c2.v[36]*MainFormSLS->hh_1[99]
 + c2.v[37]*MainFormSLS->hh_1[25]
 + c2.v[38]*MainFormSLS->hh_1[111]
 + c2.v[39]*MainFormSLS->hh_1[37]
 + c2.v[40]*MainFormSLS->hh_1[123]
 + c2.v[41]*MainFormSLS->hh_1[49]
 + c2.v[42]*MainFormSLS->hh_1[135]
 + c2.v[43]*MainFormSLS->hh_1[61]
 + c2.v[44]*MainFormSLS->hh_1[147]
 + c2.v[45]*MainFormSLS->hh_1[73]
 + c2.v[46]*MainFormSLS->hh_1[159]
 + c2.v[47]*MainFormSLS->hh_1[85]
 + c2.v[48]*MainFormSLS->hh_1[11]
 + c2.v[49]*MainFormSLS->hh_1[97]
 + c2.v[50]*MainFormSLS->hh_1[23]
 + c2.v[51]*MainFormSLS->hh_1[109]
 + c2.v[52]*MainFormSLS->hh_1[35]
 + c2.v[53]*MainFormSLS->hh_1[121]
 + c2.v[54]*MainFormSLS->hh_1[47]
 + c2.v[55]*MainFormSLS->hh_1[133]
 + c2.v[56]*MainFormSLS->hh_1[59]
 + c2.v[57]*MainFormSLS->hh_1[145]
 + c2.v[58]*MainFormSLS->hh_1[71]
 + c2.v[59]*MainFormSLS->hh_1[157]
 + c2.v[60]*MainFormSLS->hh_1[83]
 + c2.v[61]*MainFormSLS->hh_1[9]
 + c2.v[62]*MainFormSLS->hh_1[95]
 + c2.v[63]*MainFormSLS->hh_1[21]
 + c2.v[64]*MainFormSLS->hh_1[107]
 + c2.v[65]*MainFormSLS->hh_1[33]
 + c2.v[66]*MainFormSLS->hh_1[119]
 + c2.v[67]*MainFormSLS->hh_1[45]
 + c2.v[68]*MainFormSLS->hh_1[131]
 + c2.v[69]*MainFormSLS->hh_1[57]
 + c2.v[70]*MainFormSLS->hh_1[143]
 + c2.v[71]*MainFormSLS->hh_1[69]
 + c2.v[72]*MainFormSLS->hh_1[155]
 + c2.v[73]*MainFormSLS->hh_1[81]
 + c2.v[74]*MainFormSLS->hh_1[7]
 + c2.v[75]*MainFormSLS->hh_1[93]
 + c2.v[76]*MainFormSLS->hh_1[19]
 + c2.v[77]*MainFormSLS->hh_1[105]
 + c2.v[78]*MainFormSLS->hh_1[31]
 + c2.v[79]*MainFormSLS->hh_1[117];
s/=N_2;
out.push_back(s);
//������ 44
s =c2.v[0]*MainFormSLS->hh_1[44]
 + c2.v[1]*MainFormSLS->hh_1[132]
 + c2.v[2]*MainFormSLS->hh_1[60]
 + c2.v[3]*MainFormSLS->hh_1[148]
 + c2.v[4]*MainFormSLS->hh_1[76]
 + c2.v[5]*MainFormSLS->hh_1[4]
 + c2.v[6]*MainFormSLS->hh_1[92]
 + c2.v[7]*MainFormSLS->hh_1[20]
 + c2.v[8]*MainFormSLS->hh_1[108]
 + c2.v[9]*MainFormSLS->hh_1[36]
 + c2.v[10]*MainFormSLS->hh_1[124]
 + c2.v[11]*MainFormSLS->hh_1[52]
 + c2.v[12]*MainFormSLS->hh_1[140]
 + c2.v[13]*MainFormSLS->hh_1[68]
 + c2.v[14]*MainFormSLS->hh_1[156]
 + c2.v[15]*MainFormSLS->hh_1[84]
 + c2.v[16]*MainFormSLS->hh_1[12]
 + c2.v[17]*MainFormSLS->hh_1[100]
 + c2.v[18]*MainFormSLS->hh_1[28]
 + c2.v[19]*MainFormSLS->hh_1[116]
 + c2.v[20]*MainFormSLS->hh_1[44]
 + c2.v[21]*MainFormSLS->hh_1[132]
 + c2.v[22]*MainFormSLS->hh_1[60]
 + c2.v[23]*MainFormSLS->hh_1[148]
 + c2.v[24]*MainFormSLS->hh_1[76]
 + c2.v[25]*MainFormSLS->hh_1[4]
 + c2.v[26]*MainFormSLS->hh_1[92]
 + c2.v[27]*MainFormSLS->hh_1[20]
 + c2.v[28]*MainFormSLS->hh_1[108]
 + c2.v[29]*MainFormSLS->hh_1[36]
 + c2.v[30]*MainFormSLS->hh_1[124]
 + c2.v[31]*MainFormSLS->hh_1[52]
 + c2.v[32]*MainFormSLS->hh_1[140]
 + c2.v[33]*MainFormSLS->hh_1[68]
 + c2.v[34]*MainFormSLS->hh_1[156]
 + c2.v[35]*MainFormSLS->hh_1[84]
 + c2.v[36]*MainFormSLS->hh_1[12]
 + c2.v[37]*MainFormSLS->hh_1[100]
 + c2.v[38]*MainFormSLS->hh_1[28]
 + c2.v[39]*MainFormSLS->hh_1[116]
 + c2.v[40]*MainFormSLS->hh_1[44]
 + c2.v[41]*MainFormSLS->hh_1[132]
 + c2.v[42]*MainFormSLS->hh_1[60]
 + c2.v[43]*MainFormSLS->hh_1[148]
 + c2.v[44]*MainFormSLS->hh_1[76]
 + c2.v[45]*MainFormSLS->hh_1[4]
 + c2.v[46]*MainFormSLS->hh_1[92]
 + c2.v[47]*MainFormSLS->hh_1[20]
 + c2.v[48]*MainFormSLS->hh_1[108]
 + c2.v[49]*MainFormSLS->hh_1[36]
 + c2.v[50]*MainFormSLS->hh_1[124]
 + c2.v[51]*MainFormSLS->hh_1[52]
 + c2.v[52]*MainFormSLS->hh_1[140]
 + c2.v[53]*MainFormSLS->hh_1[68]
 + c2.v[54]*MainFormSLS->hh_1[156]
 + c2.v[55]*MainFormSLS->hh_1[84]
 + c2.v[56]*MainFormSLS->hh_1[12]
 + c2.v[57]*MainFormSLS->hh_1[100]
 + c2.v[58]*MainFormSLS->hh_1[28]
 + c2.v[59]*MainFormSLS->hh_1[116]
 + c2.v[60]*MainFormSLS->hh_1[44]
 + c2.v[61]*MainFormSLS->hh_1[132]
 + c2.v[62]*MainFormSLS->hh_1[60]
 + c2.v[63]*MainFormSLS->hh_1[148]
 + c2.v[64]*MainFormSLS->hh_1[76]
 + c2.v[65]*MainFormSLS->hh_1[4]
 + c2.v[66]*MainFormSLS->hh_1[92]
 + c2.v[67]*MainFormSLS->hh_1[20]
 + c2.v[68]*MainFormSLS->hh_1[108]
 + c2.v[69]*MainFormSLS->hh_1[36]
 + c2.v[70]*MainFormSLS->hh_1[124]
 + c2.v[71]*MainFormSLS->hh_1[52]
 + c2.v[72]*MainFormSLS->hh_1[140]
 + c2.v[73]*MainFormSLS->hh_1[68]
 + c2.v[74]*MainFormSLS->hh_1[156]
 + c2.v[75]*MainFormSLS->hh_1[84]
 + c2.v[76]*MainFormSLS->hh_1[12]
 + c2.v[77]*MainFormSLS->hh_1[100]
 + c2.v[78]*MainFormSLS->hh_1[28]
 + c2.v[79]*MainFormSLS->hh_1[116];
s/=N_2;
out.push_back(s);
//������ 45
s =c2.v[0]*MainFormSLS->hh_1[45]
 + c2.v[1]*MainFormSLS->hh_1[135]
 + c2.v[2]*MainFormSLS->hh_1[65]
 + c2.v[3]*MainFormSLS->hh_1[155]
 + c2.v[4]*MainFormSLS->hh_1[85]
 + c2.v[5]*MainFormSLS->hh_1[15]
 + c2.v[6]*MainFormSLS->hh_1[105]
 + c2.v[7]*MainFormSLS->hh_1[35]
 + c2.v[8]*MainFormSLS->hh_1[125]
 + c2.v[9]*MainFormSLS->hh_1[55]
 + c2.v[10]*MainFormSLS->hh_1[145]
 + c2.v[11]*MainFormSLS->hh_1[75]
 + c2.v[12]*MainFormSLS->hh_1[5]
 + c2.v[13]*MainFormSLS->hh_1[95]
 + c2.v[14]*MainFormSLS->hh_1[25]
 + c2.v[15]*MainFormSLS->hh_1[115]
 + c2.v[16]*MainFormSLS->hh_1[45]
 + c2.v[17]*MainFormSLS->hh_1[135]
 + c2.v[18]*MainFormSLS->hh_1[65]
 + c2.v[19]*MainFormSLS->hh_1[155]
 + c2.v[20]*MainFormSLS->hh_1[85]
 + c2.v[21]*MainFormSLS->hh_1[15]
 + c2.v[22]*MainFormSLS->hh_1[105]
 + c2.v[23]*MainFormSLS->hh_1[35]
 + c2.v[24]*MainFormSLS->hh_1[125]
 + c2.v[25]*MainFormSLS->hh_1[55]
 + c2.v[26]*MainFormSLS->hh_1[145]
 + c2.v[27]*MainFormSLS->hh_1[75]
 + c2.v[28]*MainFormSLS->hh_1[5]
 + c2.v[29]*MainFormSLS->hh_1[95]
 + c2.v[30]*MainFormSLS->hh_1[25]
 + c2.v[31]*MainFormSLS->hh_1[115]
 + c2.v[32]*MainFormSLS->hh_1[45]
 + c2.v[33]*MainFormSLS->hh_1[135]
 + c2.v[34]*MainFormSLS->hh_1[65]
 + c2.v[35]*MainFormSLS->hh_1[155]
 + c2.v[36]*MainFormSLS->hh_1[85]
 + c2.v[37]*MainFormSLS->hh_1[15]
 + c2.v[38]*MainFormSLS->hh_1[105]
 + c2.v[39]*MainFormSLS->hh_1[35]
 + c2.v[40]*MainFormSLS->hh_1[125]
 + c2.v[41]*MainFormSLS->hh_1[55]
 + c2.v[42]*MainFormSLS->hh_1[145]
 + c2.v[43]*MainFormSLS->hh_1[75]
 + c2.v[44]*MainFormSLS->hh_1[5]
 + c2.v[45]*MainFormSLS->hh_1[95]
 + c2.v[46]*MainFormSLS->hh_1[25]
 + c2.v[47]*MainFormSLS->hh_1[115]
 + c2.v[48]*MainFormSLS->hh_1[45]
 + c2.v[49]*MainFormSLS->hh_1[135]
 + c2.v[50]*MainFormSLS->hh_1[65]
 + c2.v[51]*MainFormSLS->hh_1[155]
 + c2.v[52]*MainFormSLS->hh_1[85]
 + c2.v[53]*MainFormSLS->hh_1[15]
 + c2.v[54]*MainFormSLS->hh_1[105]
 + c2.v[55]*MainFormSLS->hh_1[35]
 + c2.v[56]*MainFormSLS->hh_1[125]
 + c2.v[57]*MainFormSLS->hh_1[55]
 + c2.v[58]*MainFormSLS->hh_1[145]
 + c2.v[59]*MainFormSLS->hh_1[75]
 + c2.v[60]*MainFormSLS->hh_1[5]
 + c2.v[61]*MainFormSLS->hh_1[95]
 + c2.v[62]*MainFormSLS->hh_1[25]
 + c2.v[63]*MainFormSLS->hh_1[115]
 + c2.v[64]*MainFormSLS->hh_1[45]
 + c2.v[65]*MainFormSLS->hh_1[135]
 + c2.v[66]*MainFormSLS->hh_1[65]
 + c2.v[67]*MainFormSLS->hh_1[155]
 + c2.v[68]*MainFormSLS->hh_1[85]
 + c2.v[69]*MainFormSLS->hh_1[15]
 + c2.v[70]*MainFormSLS->hh_1[105]
 + c2.v[71]*MainFormSLS->hh_1[35]
 + c2.v[72]*MainFormSLS->hh_1[125]
 + c2.v[73]*MainFormSLS->hh_1[55]
 + c2.v[74]*MainFormSLS->hh_1[145]
 + c2.v[75]*MainFormSLS->hh_1[75]
 + c2.v[76]*MainFormSLS->hh_1[5]
 + c2.v[77]*MainFormSLS->hh_1[95]
 + c2.v[78]*MainFormSLS->hh_1[25]
 + c2.v[79]*MainFormSLS->hh_1[115];
s/=N_2;
out.push_back(s);
//������ 46
s =c2.v[0]*MainFormSLS->hh_1[46]
 + c2.v[1]*MainFormSLS->hh_1[138]
 + c2.v[2]*MainFormSLS->hh_1[70]
 + c2.v[3]*MainFormSLS->hh_1[2]
 + c2.v[4]*MainFormSLS->hh_1[94]
 + c2.v[5]*MainFormSLS->hh_1[26]
 + c2.v[6]*MainFormSLS->hh_1[118]
 + c2.v[7]*MainFormSLS->hh_1[50]
 + c2.v[8]*MainFormSLS->hh_1[142]
 + c2.v[9]*MainFormSLS->hh_1[74]
 + c2.v[10]*MainFormSLS->hh_1[6]
 + c2.v[11]*MainFormSLS->hh_1[98]
 + c2.v[12]*MainFormSLS->hh_1[30]
 + c2.v[13]*MainFormSLS->hh_1[122]
 + c2.v[14]*MainFormSLS->hh_1[54]
 + c2.v[15]*MainFormSLS->hh_1[146]
 + c2.v[16]*MainFormSLS->hh_1[78]
 + c2.v[17]*MainFormSLS->hh_1[10]
 + c2.v[18]*MainFormSLS->hh_1[102]
 + c2.v[19]*MainFormSLS->hh_1[34]
 + c2.v[20]*MainFormSLS->hh_1[126]
 + c2.v[21]*MainFormSLS->hh_1[58]
 + c2.v[22]*MainFormSLS->hh_1[150]
 + c2.v[23]*MainFormSLS->hh_1[82]
 + c2.v[24]*MainFormSLS->hh_1[14]
 + c2.v[25]*MainFormSLS->hh_1[106]
 + c2.v[26]*MainFormSLS->hh_1[38]
 + c2.v[27]*MainFormSLS->hh_1[130]
 + c2.v[28]*MainFormSLS->hh_1[62]
 + c2.v[29]*MainFormSLS->hh_1[154]
 + c2.v[30]*MainFormSLS->hh_1[86]
 + c2.v[31]*MainFormSLS->hh_1[18]
 + c2.v[32]*MainFormSLS->hh_1[110]
 + c2.v[33]*MainFormSLS->hh_1[42]
 + c2.v[34]*MainFormSLS->hh_1[134]
 + c2.v[35]*MainFormSLS->hh_1[66]
 + c2.v[36]*MainFormSLS->hh_1[158]
 + c2.v[37]*MainFormSLS->hh_1[90]
 + c2.v[38]*MainFormSLS->hh_1[22]
 + c2.v[39]*MainFormSLS->hh_1[114]
 + c2.v[40]*MainFormSLS->hh_1[46]
 + c2.v[41]*MainFormSLS->hh_1[138]
 + c2.v[42]*MainFormSLS->hh_1[70]
 + c2.v[43]*MainFormSLS->hh_1[2]
 + c2.v[44]*MainFormSLS->hh_1[94]
 + c2.v[45]*MainFormSLS->hh_1[26]
 + c2.v[46]*MainFormSLS->hh_1[118]
 + c2.v[47]*MainFormSLS->hh_1[50]
 + c2.v[48]*MainFormSLS->hh_1[142]
 + c2.v[49]*MainFormSLS->hh_1[74]
 + c2.v[50]*MainFormSLS->hh_1[6]
 + c2.v[51]*MainFormSLS->hh_1[98]
 + c2.v[52]*MainFormSLS->hh_1[30]
 + c2.v[53]*MainFormSLS->hh_1[122]
 + c2.v[54]*MainFormSLS->hh_1[54]
 + c2.v[55]*MainFormSLS->hh_1[146]
 + c2.v[56]*MainFormSLS->hh_1[78]
 + c2.v[57]*MainFormSLS->hh_1[10]
 + c2.v[58]*MainFormSLS->hh_1[102]
 + c2.v[59]*MainFormSLS->hh_1[34]
 + c2.v[60]*MainFormSLS->hh_1[126]
 + c2.v[61]*MainFormSLS->hh_1[58]
 + c2.v[62]*MainFormSLS->hh_1[150]
 + c2.v[63]*MainFormSLS->hh_1[82]
 + c2.v[64]*MainFormSLS->hh_1[14]
 + c2.v[65]*MainFormSLS->hh_1[106]
 + c2.v[66]*MainFormSLS->hh_1[38]
 + c2.v[67]*MainFormSLS->hh_1[130]
 + c2.v[68]*MainFormSLS->hh_1[62]
 + c2.v[69]*MainFormSLS->hh_1[154]
 + c2.v[70]*MainFormSLS->hh_1[86]
 + c2.v[71]*MainFormSLS->hh_1[18]
 + c2.v[72]*MainFormSLS->hh_1[110]
 + c2.v[73]*MainFormSLS->hh_1[42]
 + c2.v[74]*MainFormSLS->hh_1[134]
 + c2.v[75]*MainFormSLS->hh_1[66]
 + c2.v[76]*MainFormSLS->hh_1[158]
 + c2.v[77]*MainFormSLS->hh_1[90]
 + c2.v[78]*MainFormSLS->hh_1[22]
 + c2.v[79]*MainFormSLS->hh_1[114];
s/=N_2;
out.push_back(s);
//������ 47
s =c2.v[0]*MainFormSLS->hh_1[47]
 + c2.v[1]*MainFormSLS->hh_1[141]
 + c2.v[2]*MainFormSLS->hh_1[75]
 + c2.v[3]*MainFormSLS->hh_1[9]
 + c2.v[4]*MainFormSLS->hh_1[103]
 + c2.v[5]*MainFormSLS->hh_1[37]
 + c2.v[6]*MainFormSLS->hh_1[131]
 + c2.v[7]*MainFormSLS->hh_1[65]
 + c2.v[8]*MainFormSLS->hh_1[159]
 + c2.v[9]*MainFormSLS->hh_1[93]
 + c2.v[10]*MainFormSLS->hh_1[27]
 + c2.v[11]*MainFormSLS->hh_1[121]
 + c2.v[12]*MainFormSLS->hh_1[55]
 + c2.v[13]*MainFormSLS->hh_1[149]
 + c2.v[14]*MainFormSLS->hh_1[83]
 + c2.v[15]*MainFormSLS->hh_1[17]
 + c2.v[16]*MainFormSLS->hh_1[111]
 + c2.v[17]*MainFormSLS->hh_1[45]
 + c2.v[18]*MainFormSLS->hh_1[139]
 + c2.v[19]*MainFormSLS->hh_1[73]
 + c2.v[20]*MainFormSLS->hh_1[7]
 + c2.v[21]*MainFormSLS->hh_1[101]
 + c2.v[22]*MainFormSLS->hh_1[35]
 + c2.v[23]*MainFormSLS->hh_1[129]
 + c2.v[24]*MainFormSLS->hh_1[63]
 + c2.v[25]*MainFormSLS->hh_1[157]
 + c2.v[26]*MainFormSLS->hh_1[91]
 + c2.v[27]*MainFormSLS->hh_1[25]
 + c2.v[28]*MainFormSLS->hh_1[119]
 + c2.v[29]*MainFormSLS->hh_1[53]
 + c2.v[30]*MainFormSLS->hh_1[147]
 + c2.v[31]*MainFormSLS->hh_1[81]
 + c2.v[32]*MainFormSLS->hh_1[15]
 + c2.v[33]*MainFormSLS->hh_1[109]
 + c2.v[34]*MainFormSLS->hh_1[43]
 + c2.v[35]*MainFormSLS->hh_1[137]
 + c2.v[36]*MainFormSLS->hh_1[71]
 + c2.v[37]*MainFormSLS->hh_1[5]
 + c2.v[38]*MainFormSLS->hh_1[99]
 + c2.v[39]*MainFormSLS->hh_1[33]
 + c2.v[40]*MainFormSLS->hh_1[127]
 + c2.v[41]*MainFormSLS->hh_1[61]
 + c2.v[42]*MainFormSLS->hh_1[155]
 + c2.v[43]*MainFormSLS->hh_1[89]
 + c2.v[44]*MainFormSLS->hh_1[23]
 + c2.v[45]*MainFormSLS->hh_1[117]
 + c2.v[46]*MainFormSLS->hh_1[51]
 + c2.v[47]*MainFormSLS->hh_1[145]
 + c2.v[48]*MainFormSLS->hh_1[79]
 + c2.v[49]*MainFormSLS->hh_1[13]
 + c2.v[50]*MainFormSLS->hh_1[107]
 + c2.v[51]*MainFormSLS->hh_1[41]
 + c2.v[52]*MainFormSLS->hh_1[135]
 + c2.v[53]*MainFormSLS->hh_1[69]
 + c2.v[54]*MainFormSLS->hh_1[3]
 + c2.v[55]*MainFormSLS->hh_1[97]
 + c2.v[56]*MainFormSLS->hh_1[31]
 + c2.v[57]*MainFormSLS->hh_1[125]
 + c2.v[58]*MainFormSLS->hh_1[59]
 + c2.v[59]*MainFormSLS->hh_1[153]
 + c2.v[60]*MainFormSLS->hh_1[87]
 + c2.v[61]*MainFormSLS->hh_1[21]
 + c2.v[62]*MainFormSLS->hh_1[115]
 + c2.v[63]*MainFormSLS->hh_1[49]
 + c2.v[64]*MainFormSLS->hh_1[143]
 + c2.v[65]*MainFormSLS->hh_1[77]
 + c2.v[66]*MainFormSLS->hh_1[11]
 + c2.v[67]*MainFormSLS->hh_1[105]
 + c2.v[68]*MainFormSLS->hh_1[39]
 + c2.v[69]*MainFormSLS->hh_1[133]
 + c2.v[70]*MainFormSLS->hh_1[67]
 + c2.v[71]*MainFormSLS->hh_1[1]
 + c2.v[72]*MainFormSLS->hh_1[95]
 + c2.v[73]*MainFormSLS->hh_1[29]
 + c2.v[74]*MainFormSLS->hh_1[123]
 + c2.v[75]*MainFormSLS->hh_1[57]
 + c2.v[76]*MainFormSLS->hh_1[151]
 + c2.v[77]*MainFormSLS->hh_1[85]
 + c2.v[78]*MainFormSLS->hh_1[19]
 + c2.v[79]*MainFormSLS->hh_1[113];
s/=N_2;
out.push_back(s);
//������ 48
s =c2.v[0]*MainFormSLS->hh_1[48]
 + c2.v[1]*MainFormSLS->hh_1[144]
 + c2.v[2]*MainFormSLS->hh_1[80]
 + c2.v[3]*MainFormSLS->hh_1[16]
 + c2.v[4]*MainFormSLS->hh_1[112]
 + c2.v[5]*MainFormSLS->hh_1[48]
 + c2.v[6]*MainFormSLS->hh_1[144]
 + c2.v[7]*MainFormSLS->hh_1[80]
 + c2.v[8]*MainFormSLS->hh_1[16]
 + c2.v[9]*MainFormSLS->hh_1[112]
 + c2.v[10]*MainFormSLS->hh_1[48]
 + c2.v[11]*MainFormSLS->hh_1[144]
 + c2.v[12]*MainFormSLS->hh_1[80]
 + c2.v[13]*MainFormSLS->hh_1[16]
 + c2.v[14]*MainFormSLS->hh_1[112]
 + c2.v[15]*MainFormSLS->hh_1[48]
 + c2.v[16]*MainFormSLS->hh_1[144]
 + c2.v[17]*MainFormSLS->hh_1[80]
 + c2.v[18]*MainFormSLS->hh_1[16]
 + c2.v[19]*MainFormSLS->hh_1[112]
 + c2.v[20]*MainFormSLS->hh_1[48]
 + c2.v[21]*MainFormSLS->hh_1[144]
 + c2.v[22]*MainFormSLS->hh_1[80]
 + c2.v[23]*MainFormSLS->hh_1[16]
 + c2.v[24]*MainFormSLS->hh_1[112]
 + c2.v[25]*MainFormSLS->hh_1[48]
 + c2.v[26]*MainFormSLS->hh_1[144]
 + c2.v[27]*MainFormSLS->hh_1[80]
 + c2.v[28]*MainFormSLS->hh_1[16]
 + c2.v[29]*MainFormSLS->hh_1[112]
 + c2.v[30]*MainFormSLS->hh_1[48]
 + c2.v[31]*MainFormSLS->hh_1[144]
 + c2.v[32]*MainFormSLS->hh_1[80]
 + c2.v[33]*MainFormSLS->hh_1[16]
 + c2.v[34]*MainFormSLS->hh_1[112]
 + c2.v[35]*MainFormSLS->hh_1[48]
 + c2.v[36]*MainFormSLS->hh_1[144]
 + c2.v[37]*MainFormSLS->hh_1[80]
 + c2.v[38]*MainFormSLS->hh_1[16]
 + c2.v[39]*MainFormSLS->hh_1[112]
 + c2.v[40]*MainFormSLS->hh_1[48]
 + c2.v[41]*MainFormSLS->hh_1[144]
 + c2.v[42]*MainFormSLS->hh_1[80]
 + c2.v[43]*MainFormSLS->hh_1[16]
 + c2.v[44]*MainFormSLS->hh_1[112]
 + c2.v[45]*MainFormSLS->hh_1[48]
 + c2.v[46]*MainFormSLS->hh_1[144]
 + c2.v[47]*MainFormSLS->hh_1[80]
 + c2.v[48]*MainFormSLS->hh_1[16]
 + c2.v[49]*MainFormSLS->hh_1[112]
 + c2.v[50]*MainFormSLS->hh_1[48]
 + c2.v[51]*MainFormSLS->hh_1[144]
 + c2.v[52]*MainFormSLS->hh_1[80]
 + c2.v[53]*MainFormSLS->hh_1[16]
 + c2.v[54]*MainFormSLS->hh_1[112]
 + c2.v[55]*MainFormSLS->hh_1[48]
 + c2.v[56]*MainFormSLS->hh_1[144]
 + c2.v[57]*MainFormSLS->hh_1[80]
 + c2.v[58]*MainFormSLS->hh_1[16]
 + c2.v[59]*MainFormSLS->hh_1[112]
 + c2.v[60]*MainFormSLS->hh_1[48]
 + c2.v[61]*MainFormSLS->hh_1[144]
 + c2.v[62]*MainFormSLS->hh_1[80]
 + c2.v[63]*MainFormSLS->hh_1[16]
 + c2.v[64]*MainFormSLS->hh_1[112]
 + c2.v[65]*MainFormSLS->hh_1[48]
 + c2.v[66]*MainFormSLS->hh_1[144]
 + c2.v[67]*MainFormSLS->hh_1[80]
 + c2.v[68]*MainFormSLS->hh_1[16]
 + c2.v[69]*MainFormSLS->hh_1[112]
 + c2.v[70]*MainFormSLS->hh_1[48]
 + c2.v[71]*MainFormSLS->hh_1[144]
 + c2.v[72]*MainFormSLS->hh_1[80]
 + c2.v[73]*MainFormSLS->hh_1[16]
 + c2.v[74]*MainFormSLS->hh_1[112]
 + c2.v[75]*MainFormSLS->hh_1[48]
 + c2.v[76]*MainFormSLS->hh_1[144]
 + c2.v[77]*MainFormSLS->hh_1[80]
 + c2.v[78]*MainFormSLS->hh_1[16]
 + c2.v[79]*MainFormSLS->hh_1[112];
s/=N_2;
out.push_back(s);
//������ 49
s =c2.v[0]*MainFormSLS->hh_1[49]
 + c2.v[1]*MainFormSLS->hh_1[147]
 + c2.v[2]*MainFormSLS->hh_1[85]
 + c2.v[3]*MainFormSLS->hh_1[23]
 + c2.v[4]*MainFormSLS->hh_1[121]
 + c2.v[5]*MainFormSLS->hh_1[59]
 + c2.v[6]*MainFormSLS->hh_1[157]
 + c2.v[7]*MainFormSLS->hh_1[95]
 + c2.v[8]*MainFormSLS->hh_1[33]
 + c2.v[9]*MainFormSLS->hh_1[131]
 + c2.v[10]*MainFormSLS->hh_1[69]
 + c2.v[11]*MainFormSLS->hh_1[7]
 + c2.v[12]*MainFormSLS->hh_1[105]
 + c2.v[13]*MainFormSLS->hh_1[43]
 + c2.v[14]*MainFormSLS->hh_1[141]
 + c2.v[15]*MainFormSLS->hh_1[79]
 + c2.v[16]*MainFormSLS->hh_1[17]
 + c2.v[17]*MainFormSLS->hh_1[115]
 + c2.v[18]*MainFormSLS->hh_1[53]
 + c2.v[19]*MainFormSLS->hh_1[151]
 + c2.v[20]*MainFormSLS->hh_1[89]
 + c2.v[21]*MainFormSLS->hh_1[27]
 + c2.v[22]*MainFormSLS->hh_1[125]
 + c2.v[23]*MainFormSLS->hh_1[63]
 + c2.v[24]*MainFormSLS->hh_1[1]
 + c2.v[25]*MainFormSLS->hh_1[99]
 + c2.v[26]*MainFormSLS->hh_1[37]
 + c2.v[27]*MainFormSLS->hh_1[135]
 + c2.v[28]*MainFormSLS->hh_1[73]
 + c2.v[29]*MainFormSLS->hh_1[11]
 + c2.v[30]*MainFormSLS->hh_1[109]
 + c2.v[31]*MainFormSLS->hh_1[47]
 + c2.v[32]*MainFormSLS->hh_1[145]
 + c2.v[33]*MainFormSLS->hh_1[83]
 + c2.v[34]*MainFormSLS->hh_1[21]
 + c2.v[35]*MainFormSLS->hh_1[119]
 + c2.v[36]*MainFormSLS->hh_1[57]
 + c2.v[37]*MainFormSLS->hh_1[155]
 + c2.v[38]*MainFormSLS->hh_1[93]
 + c2.v[39]*MainFormSLS->hh_1[31]
 + c2.v[40]*MainFormSLS->hh_1[129]
 + c2.v[41]*MainFormSLS->hh_1[67]
 + c2.v[42]*MainFormSLS->hh_1[5]
 + c2.v[43]*MainFormSLS->hh_1[103]
 + c2.v[44]*MainFormSLS->hh_1[41]
 + c2.v[45]*MainFormSLS->hh_1[139]
 + c2.v[46]*MainFormSLS->hh_1[77]
 + c2.v[47]*MainFormSLS->hh_1[15]
 + c2.v[48]*MainFormSLS->hh_1[113]
 + c2.v[49]*MainFormSLS->hh_1[51]
 + c2.v[50]*MainFormSLS->hh_1[149]
 + c2.v[51]*MainFormSLS->hh_1[87]
 + c2.v[52]*MainFormSLS->hh_1[25]
 + c2.v[53]*MainFormSLS->hh_1[123]
 + c2.v[54]*MainFormSLS->hh_1[61]
 + c2.v[55]*MainFormSLS->hh_1[159]
 + c2.v[56]*MainFormSLS->hh_1[97]
 + c2.v[57]*MainFormSLS->hh_1[35]
 + c2.v[58]*MainFormSLS->hh_1[133]
 + c2.v[59]*MainFormSLS->hh_1[71]
 + c2.v[60]*MainFormSLS->hh_1[9]
 + c2.v[61]*MainFormSLS->hh_1[107]
 + c2.v[62]*MainFormSLS->hh_1[45]
 + c2.v[63]*MainFormSLS->hh_1[143]
 + c2.v[64]*MainFormSLS->hh_1[81]
 + c2.v[65]*MainFormSLS->hh_1[19]
 + c2.v[66]*MainFormSLS->hh_1[117]
 + c2.v[67]*MainFormSLS->hh_1[55]
 + c2.v[68]*MainFormSLS->hh_1[153]
 + c2.v[69]*MainFormSLS->hh_1[91]
 + c2.v[70]*MainFormSLS->hh_1[29]
 + c2.v[71]*MainFormSLS->hh_1[127]
 + c2.v[72]*MainFormSLS->hh_1[65]
 + c2.v[73]*MainFormSLS->hh_1[3]
 + c2.v[74]*MainFormSLS->hh_1[101]
 + c2.v[75]*MainFormSLS->hh_1[39]
 + c2.v[76]*MainFormSLS->hh_1[137]
 + c2.v[77]*MainFormSLS->hh_1[75]
 + c2.v[78]*MainFormSLS->hh_1[13]
 + c2.v[79]*MainFormSLS->hh_1[111];
s/=N_2;
out.push_back(s);
//������ 50
s =c2.v[0]*MainFormSLS->hh_1[50]
 + c2.v[1]*MainFormSLS->hh_1[150]
 + c2.v[2]*MainFormSLS->hh_1[90]
 + c2.v[3]*MainFormSLS->hh_1[30]
 + c2.v[4]*MainFormSLS->hh_1[130]
 + c2.v[5]*MainFormSLS->hh_1[70]
 + c2.v[6]*MainFormSLS->hh_1[10]
 + c2.v[7]*MainFormSLS->hh_1[110]
 + c2.v[8]*MainFormSLS->hh_1[50]
 + c2.v[9]*MainFormSLS->hh_1[150]
 + c2.v[10]*MainFormSLS->hh_1[90]
 + c2.v[11]*MainFormSLS->hh_1[30]
 + c2.v[12]*MainFormSLS->hh_1[130]
 + c2.v[13]*MainFormSLS->hh_1[70]
 + c2.v[14]*MainFormSLS->hh_1[10]
 + c2.v[15]*MainFormSLS->hh_1[110]
 + c2.v[16]*MainFormSLS->hh_1[50]
 + c2.v[17]*MainFormSLS->hh_1[150]
 + c2.v[18]*MainFormSLS->hh_1[90]
 + c2.v[19]*MainFormSLS->hh_1[30]
 + c2.v[20]*MainFormSLS->hh_1[130]
 + c2.v[21]*MainFormSLS->hh_1[70]
 + c2.v[22]*MainFormSLS->hh_1[10]
 + c2.v[23]*MainFormSLS->hh_1[110]
 + c2.v[24]*MainFormSLS->hh_1[50]
 + c2.v[25]*MainFormSLS->hh_1[150]
 + c2.v[26]*MainFormSLS->hh_1[90]
 + c2.v[27]*MainFormSLS->hh_1[30]
 + c2.v[28]*MainFormSLS->hh_1[130]
 + c2.v[29]*MainFormSLS->hh_1[70]
 + c2.v[30]*MainFormSLS->hh_1[10]
 + c2.v[31]*MainFormSLS->hh_1[110]
 + c2.v[32]*MainFormSLS->hh_1[50]
 + c2.v[33]*MainFormSLS->hh_1[150]
 + c2.v[34]*MainFormSLS->hh_1[90]
 + c2.v[35]*MainFormSLS->hh_1[30]
 + c2.v[36]*MainFormSLS->hh_1[130]
 + c2.v[37]*MainFormSLS->hh_1[70]
 + c2.v[38]*MainFormSLS->hh_1[10]
 + c2.v[39]*MainFormSLS->hh_1[110]
 + c2.v[40]*MainFormSLS->hh_1[50]
 + c2.v[41]*MainFormSLS->hh_1[150]
 + c2.v[42]*MainFormSLS->hh_1[90]
 + c2.v[43]*MainFormSLS->hh_1[30]
 + c2.v[44]*MainFormSLS->hh_1[130]
 + c2.v[45]*MainFormSLS->hh_1[70]
 + c2.v[46]*MainFormSLS->hh_1[10]
 + c2.v[47]*MainFormSLS->hh_1[110]
 + c2.v[48]*MainFormSLS->hh_1[50]
 + c2.v[49]*MainFormSLS->hh_1[150]
 + c2.v[50]*MainFormSLS->hh_1[90]
 + c2.v[51]*MainFormSLS->hh_1[30]
 + c2.v[52]*MainFormSLS->hh_1[130]
 + c2.v[53]*MainFormSLS->hh_1[70]
 + c2.v[54]*MainFormSLS->hh_1[10]
 + c2.v[55]*MainFormSLS->hh_1[110]
 + c2.v[56]*MainFormSLS->hh_1[50]
 + c2.v[57]*MainFormSLS->hh_1[150]
 + c2.v[58]*MainFormSLS->hh_1[90]
 + c2.v[59]*MainFormSLS->hh_1[30]
 + c2.v[60]*MainFormSLS->hh_1[130]
 + c2.v[61]*MainFormSLS->hh_1[70]
 + c2.v[62]*MainFormSLS->hh_1[10]
 + c2.v[63]*MainFormSLS->hh_1[110]
 + c2.v[64]*MainFormSLS->hh_1[50]
 + c2.v[65]*MainFormSLS->hh_1[150]
 + c2.v[66]*MainFormSLS->hh_1[90]
 + c2.v[67]*MainFormSLS->hh_1[30]
 + c2.v[68]*MainFormSLS->hh_1[130]
 + c2.v[69]*MainFormSLS->hh_1[70]
 + c2.v[70]*MainFormSLS->hh_1[10]
 + c2.v[71]*MainFormSLS->hh_1[110]
 + c2.v[72]*MainFormSLS->hh_1[50]
 + c2.v[73]*MainFormSLS->hh_1[150]
 + c2.v[74]*MainFormSLS->hh_1[90]
 + c2.v[75]*MainFormSLS->hh_1[30]
 + c2.v[76]*MainFormSLS->hh_1[130]
 + c2.v[77]*MainFormSLS->hh_1[70]
 + c2.v[78]*MainFormSLS->hh_1[10]
 + c2.v[79]*MainFormSLS->hh_1[110];
s/=N_2;
out.push_back(s);
//������ 51
s =c2.v[0]*MainFormSLS->hh_1[51]
 + c2.v[1]*MainFormSLS->hh_1[153]
 + c2.v[2]*MainFormSLS->hh_1[95]
 + c2.v[3]*MainFormSLS->hh_1[37]
 + c2.v[4]*MainFormSLS->hh_1[139]
 + c2.v[5]*MainFormSLS->hh_1[81]
 + c2.v[6]*MainFormSLS->hh_1[23]
 + c2.v[7]*MainFormSLS->hh_1[125]
 + c2.v[8]*MainFormSLS->hh_1[67]
 + c2.v[9]*MainFormSLS->hh_1[9]
 + c2.v[10]*MainFormSLS->hh_1[111]
 + c2.v[11]*MainFormSLS->hh_1[53]
 + c2.v[12]*MainFormSLS->hh_1[155]
 + c2.v[13]*MainFormSLS->hh_1[97]
 + c2.v[14]*MainFormSLS->hh_1[39]
 + c2.v[15]*MainFormSLS->hh_1[141]
 + c2.v[16]*MainFormSLS->hh_1[83]
 + c2.v[17]*MainFormSLS->hh_1[25]
 + c2.v[18]*MainFormSLS->hh_1[127]
 + c2.v[19]*MainFormSLS->hh_1[69]
 + c2.v[20]*MainFormSLS->hh_1[11]
 + c2.v[21]*MainFormSLS->hh_1[113]
 + c2.v[22]*MainFormSLS->hh_1[55]
 + c2.v[23]*MainFormSLS->hh_1[157]
 + c2.v[24]*MainFormSLS->hh_1[99]
 + c2.v[25]*MainFormSLS->hh_1[41]
 + c2.v[26]*MainFormSLS->hh_1[143]
 + c2.v[27]*MainFormSLS->hh_1[85]
 + c2.v[28]*MainFormSLS->hh_1[27]
 + c2.v[29]*MainFormSLS->hh_1[129]
 + c2.v[30]*MainFormSLS->hh_1[71]
 + c2.v[31]*MainFormSLS->hh_1[13]
 + c2.v[32]*MainFormSLS->hh_1[115]
 + c2.v[33]*MainFormSLS->hh_1[57]
 + c2.v[34]*MainFormSLS->hh_1[159]
 + c2.v[35]*MainFormSLS->hh_1[101]
 + c2.v[36]*MainFormSLS->hh_1[43]
 + c2.v[37]*MainFormSLS->hh_1[145]
 + c2.v[38]*MainFormSLS->hh_1[87]
 + c2.v[39]*MainFormSLS->hh_1[29]
 + c2.v[40]*MainFormSLS->hh_1[131]
 + c2.v[41]*MainFormSLS->hh_1[73]
 + c2.v[42]*MainFormSLS->hh_1[15]
 + c2.v[43]*MainFormSLS->hh_1[117]
 + c2.v[44]*MainFormSLS->hh_1[59]
 + c2.v[45]*MainFormSLS->hh_1[1]
 + c2.v[46]*MainFormSLS->hh_1[103]
 + c2.v[47]*MainFormSLS->hh_1[45]
 + c2.v[48]*MainFormSLS->hh_1[147]
 + c2.v[49]*MainFormSLS->hh_1[89]
 + c2.v[50]*MainFormSLS->hh_1[31]
 + c2.v[51]*MainFormSLS->hh_1[133]
 + c2.v[52]*MainFormSLS->hh_1[75]
 + c2.v[53]*MainFormSLS->hh_1[17]
 + c2.v[54]*MainFormSLS->hh_1[119]
 + c2.v[55]*MainFormSLS->hh_1[61]
 + c2.v[56]*MainFormSLS->hh_1[3]
 + c2.v[57]*MainFormSLS->hh_1[105]
 + c2.v[58]*MainFormSLS->hh_1[47]
 + c2.v[59]*MainFormSLS->hh_1[149]
 + c2.v[60]*MainFormSLS->hh_1[91]
 + c2.v[61]*MainFormSLS->hh_1[33]
 + c2.v[62]*MainFormSLS->hh_1[135]
 + c2.v[63]*MainFormSLS->hh_1[77]
 + c2.v[64]*MainFormSLS->hh_1[19]
 + c2.v[65]*MainFormSLS->hh_1[121]
 + c2.v[66]*MainFormSLS->hh_1[63]
 + c2.v[67]*MainFormSLS->hh_1[5]
 + c2.v[68]*MainFormSLS->hh_1[107]
 + c2.v[69]*MainFormSLS->hh_1[49]
 + c2.v[70]*MainFormSLS->hh_1[151]
 + c2.v[71]*MainFormSLS->hh_1[93]
 + c2.v[72]*MainFormSLS->hh_1[35]
 + c2.v[73]*MainFormSLS->hh_1[137]
 + c2.v[74]*MainFormSLS->hh_1[79]
 + c2.v[75]*MainFormSLS->hh_1[21]
 + c2.v[76]*MainFormSLS->hh_1[123]
 + c2.v[77]*MainFormSLS->hh_1[65]
 + c2.v[78]*MainFormSLS->hh_1[7]
 + c2.v[79]*MainFormSLS->hh_1[109];
s/=N_2;
out.push_back(s);
//������ 52
s =c2.v[0]*MainFormSLS->hh_1[52]
 + c2.v[1]*MainFormSLS->hh_1[156]
 + c2.v[2]*MainFormSLS->hh_1[100]
 + c2.v[3]*MainFormSLS->hh_1[44]
 + c2.v[4]*MainFormSLS->hh_1[148]
 + c2.v[5]*MainFormSLS->hh_1[92]
 + c2.v[6]*MainFormSLS->hh_1[36]
 + c2.v[7]*MainFormSLS->hh_1[140]
 + c2.v[8]*MainFormSLS->hh_1[84]
 + c2.v[9]*MainFormSLS->hh_1[28]
 + c2.v[10]*MainFormSLS->hh_1[132]
 + c2.v[11]*MainFormSLS->hh_1[76]
 + c2.v[12]*MainFormSLS->hh_1[20]
 + c2.v[13]*MainFormSLS->hh_1[124]
 + c2.v[14]*MainFormSLS->hh_1[68]
 + c2.v[15]*MainFormSLS->hh_1[12]
 + c2.v[16]*MainFormSLS->hh_1[116]
 + c2.v[17]*MainFormSLS->hh_1[60]
 + c2.v[18]*MainFormSLS->hh_1[4]
 + c2.v[19]*MainFormSLS->hh_1[108]
 + c2.v[20]*MainFormSLS->hh_1[52]
 + c2.v[21]*MainFormSLS->hh_1[156]
 + c2.v[22]*MainFormSLS->hh_1[100]
 + c2.v[23]*MainFormSLS->hh_1[44]
 + c2.v[24]*MainFormSLS->hh_1[148]
 + c2.v[25]*MainFormSLS->hh_1[92]
 + c2.v[26]*MainFormSLS->hh_1[36]
 + c2.v[27]*MainFormSLS->hh_1[140]
 + c2.v[28]*MainFormSLS->hh_1[84]
 + c2.v[29]*MainFormSLS->hh_1[28]
 + c2.v[30]*MainFormSLS->hh_1[132]
 + c2.v[31]*MainFormSLS->hh_1[76]
 + c2.v[32]*MainFormSLS->hh_1[20]
 + c2.v[33]*MainFormSLS->hh_1[124]
 + c2.v[34]*MainFormSLS->hh_1[68]
 + c2.v[35]*MainFormSLS->hh_1[12]
 + c2.v[36]*MainFormSLS->hh_1[116]
 + c2.v[37]*MainFormSLS->hh_1[60]
 + c2.v[38]*MainFormSLS->hh_1[4]
 + c2.v[39]*MainFormSLS->hh_1[108]
 + c2.v[40]*MainFormSLS->hh_1[52]
 + c2.v[41]*MainFormSLS->hh_1[156]
 + c2.v[42]*MainFormSLS->hh_1[100]
 + c2.v[43]*MainFormSLS->hh_1[44]
 + c2.v[44]*MainFormSLS->hh_1[148]
 + c2.v[45]*MainFormSLS->hh_1[92]
 + c2.v[46]*MainFormSLS->hh_1[36]
 + c2.v[47]*MainFormSLS->hh_1[140]
 + c2.v[48]*MainFormSLS->hh_1[84]
 + c2.v[49]*MainFormSLS->hh_1[28]
 + c2.v[50]*MainFormSLS->hh_1[132]
 + c2.v[51]*MainFormSLS->hh_1[76]
 + c2.v[52]*MainFormSLS->hh_1[20]
 + c2.v[53]*MainFormSLS->hh_1[124]
 + c2.v[54]*MainFormSLS->hh_1[68]
 + c2.v[55]*MainFormSLS->hh_1[12]
 + c2.v[56]*MainFormSLS->hh_1[116]
 + c2.v[57]*MainFormSLS->hh_1[60]
 + c2.v[58]*MainFormSLS->hh_1[4]
 + c2.v[59]*MainFormSLS->hh_1[108]
 + c2.v[60]*MainFormSLS->hh_1[52]
 + c2.v[61]*MainFormSLS->hh_1[156]
 + c2.v[62]*MainFormSLS->hh_1[100]
 + c2.v[63]*MainFormSLS->hh_1[44]
 + c2.v[64]*MainFormSLS->hh_1[148]
 + c2.v[65]*MainFormSLS->hh_1[92]
 + c2.v[66]*MainFormSLS->hh_1[36]
 + c2.v[67]*MainFormSLS->hh_1[140]
 + c2.v[68]*MainFormSLS->hh_1[84]
 + c2.v[69]*MainFormSLS->hh_1[28]
 + c2.v[70]*MainFormSLS->hh_1[132]
 + c2.v[71]*MainFormSLS->hh_1[76]
 + c2.v[72]*MainFormSLS->hh_1[20]
 + c2.v[73]*MainFormSLS->hh_1[124]
 + c2.v[74]*MainFormSLS->hh_1[68]
 + c2.v[75]*MainFormSLS->hh_1[12]
 + c2.v[76]*MainFormSLS->hh_1[116]
 + c2.v[77]*MainFormSLS->hh_1[60]
 + c2.v[78]*MainFormSLS->hh_1[4]
 + c2.v[79]*MainFormSLS->hh_1[108];
s/=N_2;
out.push_back(s);
//������ 53
s =c2.v[0]*MainFormSLS->hh_1[53]
 + c2.v[1]*MainFormSLS->hh_1[159]
 + c2.v[2]*MainFormSLS->hh_1[105]
 + c2.v[3]*MainFormSLS->hh_1[51]
 + c2.v[4]*MainFormSLS->hh_1[157]
 + c2.v[5]*MainFormSLS->hh_1[103]
 + c2.v[6]*MainFormSLS->hh_1[49]
 + c2.v[7]*MainFormSLS->hh_1[155]
 + c2.v[8]*MainFormSLS->hh_1[101]
 + c2.v[9]*MainFormSLS->hh_1[47]
 + c2.v[10]*MainFormSLS->hh_1[153]
 + c2.v[11]*MainFormSLS->hh_1[99]
 + c2.v[12]*MainFormSLS->hh_1[45]
 + c2.v[13]*MainFormSLS->hh_1[151]
 + c2.v[14]*MainFormSLS->hh_1[97]
 + c2.v[15]*MainFormSLS->hh_1[43]
 + c2.v[16]*MainFormSLS->hh_1[149]
 + c2.v[17]*MainFormSLS->hh_1[95]
 + c2.v[18]*MainFormSLS->hh_1[41]
 + c2.v[19]*MainFormSLS->hh_1[147]
 + c2.v[20]*MainFormSLS->hh_1[93]
 + c2.v[21]*MainFormSLS->hh_1[39]
 + c2.v[22]*MainFormSLS->hh_1[145]
 + c2.v[23]*MainFormSLS->hh_1[91]
 + c2.v[24]*MainFormSLS->hh_1[37]
 + c2.v[25]*MainFormSLS->hh_1[143]
 + c2.v[26]*MainFormSLS->hh_1[89]
 + c2.v[27]*MainFormSLS->hh_1[35]
 + c2.v[28]*MainFormSLS->hh_1[141]
 + c2.v[29]*MainFormSLS->hh_1[87]
 + c2.v[30]*MainFormSLS->hh_1[33]
 + c2.v[31]*MainFormSLS->hh_1[139]
 + c2.v[32]*MainFormSLS->hh_1[85]
 + c2.v[33]*MainFormSLS->hh_1[31]
 + c2.v[34]*MainFormSLS->hh_1[137]
 + c2.v[35]*MainFormSLS->hh_1[83]
 + c2.v[36]*MainFormSLS->hh_1[29]
 + c2.v[37]*MainFormSLS->hh_1[135]
 + c2.v[38]*MainFormSLS->hh_1[81]
 + c2.v[39]*MainFormSLS->hh_1[27]
 + c2.v[40]*MainFormSLS->hh_1[133]
 + c2.v[41]*MainFormSLS->hh_1[79]
 + c2.v[42]*MainFormSLS->hh_1[25]
 + c2.v[43]*MainFormSLS->hh_1[131]
 + c2.v[44]*MainFormSLS->hh_1[77]
 + c2.v[45]*MainFormSLS->hh_1[23]
 + c2.v[46]*MainFormSLS->hh_1[129]
 + c2.v[47]*MainFormSLS->hh_1[75]
 + c2.v[48]*MainFormSLS->hh_1[21]
 + c2.v[49]*MainFormSLS->hh_1[127]
 + c2.v[50]*MainFormSLS->hh_1[73]
 + c2.v[51]*MainFormSLS->hh_1[19]
 + c2.v[52]*MainFormSLS->hh_1[125]
 + c2.v[53]*MainFormSLS->hh_1[71]
 + c2.v[54]*MainFormSLS->hh_1[17]
 + c2.v[55]*MainFormSLS->hh_1[123]
 + c2.v[56]*MainFormSLS->hh_1[69]
 + c2.v[57]*MainFormSLS->hh_1[15]
 + c2.v[58]*MainFormSLS->hh_1[121]
 + c2.v[59]*MainFormSLS->hh_1[67]
 + c2.v[60]*MainFormSLS->hh_1[13]
 + c2.v[61]*MainFormSLS->hh_1[119]
 + c2.v[62]*MainFormSLS->hh_1[65]
 + c2.v[63]*MainFormSLS->hh_1[11]
 + c2.v[64]*MainFormSLS->hh_1[117]
 + c2.v[65]*MainFormSLS->hh_1[63]
 + c2.v[66]*MainFormSLS->hh_1[9]
 + c2.v[67]*MainFormSLS->hh_1[115]
 + c2.v[68]*MainFormSLS->hh_1[61]
 + c2.v[69]*MainFormSLS->hh_1[7]
 + c2.v[70]*MainFormSLS->hh_1[113]
 + c2.v[71]*MainFormSLS->hh_1[59]
 + c2.v[72]*MainFormSLS->hh_1[5]
 + c2.v[73]*MainFormSLS->hh_1[111]
 + c2.v[74]*MainFormSLS->hh_1[57]
 + c2.v[75]*MainFormSLS->hh_1[3]
 + c2.v[76]*MainFormSLS->hh_1[109]
 + c2.v[77]*MainFormSLS->hh_1[55]
 + c2.v[78]*MainFormSLS->hh_1[1]
 + c2.v[79]*MainFormSLS->hh_1[107];
s/=N_2;
out.push_back(s);
//������ 54
s =c2.v[0]*MainFormSLS->hh_1[54]
 + c2.v[1]*MainFormSLS->hh_1[2]
 + c2.v[2]*MainFormSLS->hh_1[110]
 + c2.v[3]*MainFormSLS->hh_1[58]
 + c2.v[4]*MainFormSLS->hh_1[6]
 + c2.v[5]*MainFormSLS->hh_1[114]
 + c2.v[6]*MainFormSLS->hh_1[62]
 + c2.v[7]*MainFormSLS->hh_1[10]
 + c2.v[8]*MainFormSLS->hh_1[118]
 + c2.v[9]*MainFormSLS->hh_1[66]
 + c2.v[10]*MainFormSLS->hh_1[14]
 + c2.v[11]*MainFormSLS->hh_1[122]
 + c2.v[12]*MainFormSLS->hh_1[70]
 + c2.v[13]*MainFormSLS->hh_1[18]
 + c2.v[14]*MainFormSLS->hh_1[126]
 + c2.v[15]*MainFormSLS->hh_1[74]
 + c2.v[16]*MainFormSLS->hh_1[22]
 + c2.v[17]*MainFormSLS->hh_1[130]
 + c2.v[18]*MainFormSLS->hh_1[78]
 + c2.v[19]*MainFormSLS->hh_1[26]
 + c2.v[20]*MainFormSLS->hh_1[134]
 + c2.v[21]*MainFormSLS->hh_1[82]
 + c2.v[22]*MainFormSLS->hh_1[30]
 + c2.v[23]*MainFormSLS->hh_1[138]
 + c2.v[24]*MainFormSLS->hh_1[86]
 + c2.v[25]*MainFormSLS->hh_1[34]
 + c2.v[26]*MainFormSLS->hh_1[142]
 + c2.v[27]*MainFormSLS->hh_1[90]
 + c2.v[28]*MainFormSLS->hh_1[38]
 + c2.v[29]*MainFormSLS->hh_1[146]
 + c2.v[30]*MainFormSLS->hh_1[94]
 + c2.v[31]*MainFormSLS->hh_1[42]
 + c2.v[32]*MainFormSLS->hh_1[150]
 + c2.v[33]*MainFormSLS->hh_1[98]
 + c2.v[34]*MainFormSLS->hh_1[46]
 + c2.v[35]*MainFormSLS->hh_1[154]
 + c2.v[36]*MainFormSLS->hh_1[102]
 + c2.v[37]*MainFormSLS->hh_1[50]
 + c2.v[38]*MainFormSLS->hh_1[158]
 + c2.v[39]*MainFormSLS->hh_1[106]
 + c2.v[40]*MainFormSLS->hh_1[54]
 + c2.v[41]*MainFormSLS->hh_1[2]
 + c2.v[42]*MainFormSLS->hh_1[110]
 + c2.v[43]*MainFormSLS->hh_1[58]
 + c2.v[44]*MainFormSLS->hh_1[6]
 + c2.v[45]*MainFormSLS->hh_1[114]
 + c2.v[46]*MainFormSLS->hh_1[62]
 + c2.v[47]*MainFormSLS->hh_1[10]
 + c2.v[48]*MainFormSLS->hh_1[118]
 + c2.v[49]*MainFormSLS->hh_1[66]
 + c2.v[50]*MainFormSLS->hh_1[14]
 + c2.v[51]*MainFormSLS->hh_1[122]
 + c2.v[52]*MainFormSLS->hh_1[70]
 + c2.v[53]*MainFormSLS->hh_1[18]
 + c2.v[54]*MainFormSLS->hh_1[126]
 + c2.v[55]*MainFormSLS->hh_1[74]
 + c2.v[56]*MainFormSLS->hh_1[22]
 + c2.v[57]*MainFormSLS->hh_1[130]
 + c2.v[58]*MainFormSLS->hh_1[78]
 + c2.v[59]*MainFormSLS->hh_1[26]
 + c2.v[60]*MainFormSLS->hh_1[134]
 + c2.v[61]*MainFormSLS->hh_1[82]
 + c2.v[62]*MainFormSLS->hh_1[30]
 + c2.v[63]*MainFormSLS->hh_1[138]
 + c2.v[64]*MainFormSLS->hh_1[86]
 + c2.v[65]*MainFormSLS->hh_1[34]
 + c2.v[66]*MainFormSLS->hh_1[142]
 + c2.v[67]*MainFormSLS->hh_1[90]
 + c2.v[68]*MainFormSLS->hh_1[38]
 + c2.v[69]*MainFormSLS->hh_1[146]
 + c2.v[70]*MainFormSLS->hh_1[94]
 + c2.v[71]*MainFormSLS->hh_1[42]
 + c2.v[72]*MainFormSLS->hh_1[150]
 + c2.v[73]*MainFormSLS->hh_1[98]
 + c2.v[74]*MainFormSLS->hh_1[46]
 + c2.v[75]*MainFormSLS->hh_1[154]
 + c2.v[76]*MainFormSLS->hh_1[102]
 + c2.v[77]*MainFormSLS->hh_1[50]
 + c2.v[78]*MainFormSLS->hh_1[158]
 + c2.v[79]*MainFormSLS->hh_1[106];
s/=N_2;
out.push_back(s);
//������ 55
s =c2.v[0]*MainFormSLS->hh_1[55]
 + c2.v[1]*MainFormSLS->hh_1[5]
 + c2.v[2]*MainFormSLS->hh_1[115]
 + c2.v[3]*MainFormSLS->hh_1[65]
 + c2.v[4]*MainFormSLS->hh_1[15]
 + c2.v[5]*MainFormSLS->hh_1[125]
 + c2.v[6]*MainFormSLS->hh_1[75]
 + c2.v[7]*MainFormSLS->hh_1[25]
 + c2.v[8]*MainFormSLS->hh_1[135]
 + c2.v[9]*MainFormSLS->hh_1[85]
 + c2.v[10]*MainFormSLS->hh_1[35]
 + c2.v[11]*MainFormSLS->hh_1[145]
 + c2.v[12]*MainFormSLS->hh_1[95]
 + c2.v[13]*MainFormSLS->hh_1[45]
 + c2.v[14]*MainFormSLS->hh_1[155]
 + c2.v[15]*MainFormSLS->hh_1[105]
 + c2.v[16]*MainFormSLS->hh_1[55]
 + c2.v[17]*MainFormSLS->hh_1[5]
 + c2.v[18]*MainFormSLS->hh_1[115]
 + c2.v[19]*MainFormSLS->hh_1[65]
 + c2.v[20]*MainFormSLS->hh_1[15]
 + c2.v[21]*MainFormSLS->hh_1[125]
 + c2.v[22]*MainFormSLS->hh_1[75]
 + c2.v[23]*MainFormSLS->hh_1[25]
 + c2.v[24]*MainFormSLS->hh_1[135]
 + c2.v[25]*MainFormSLS->hh_1[85]
 + c2.v[26]*MainFormSLS->hh_1[35]
 + c2.v[27]*MainFormSLS->hh_1[145]
 + c2.v[28]*MainFormSLS->hh_1[95]
 + c2.v[29]*MainFormSLS->hh_1[45]
 + c2.v[30]*MainFormSLS->hh_1[155]
 + c2.v[31]*MainFormSLS->hh_1[105]
 + c2.v[32]*MainFormSLS->hh_1[55]
 + c2.v[33]*MainFormSLS->hh_1[5]
 + c2.v[34]*MainFormSLS->hh_1[115]
 + c2.v[35]*MainFormSLS->hh_1[65]
 + c2.v[36]*MainFormSLS->hh_1[15]
 + c2.v[37]*MainFormSLS->hh_1[125]
 + c2.v[38]*MainFormSLS->hh_1[75]
 + c2.v[39]*MainFormSLS->hh_1[25]
 + c2.v[40]*MainFormSLS->hh_1[135]
 + c2.v[41]*MainFormSLS->hh_1[85]
 + c2.v[42]*MainFormSLS->hh_1[35]
 + c2.v[43]*MainFormSLS->hh_1[145]
 + c2.v[44]*MainFormSLS->hh_1[95]
 + c2.v[45]*MainFormSLS->hh_1[45]
 + c2.v[46]*MainFormSLS->hh_1[155]
 + c2.v[47]*MainFormSLS->hh_1[105]
 + c2.v[48]*MainFormSLS->hh_1[55]
 + c2.v[49]*MainFormSLS->hh_1[5]
 + c2.v[50]*MainFormSLS->hh_1[115]
 + c2.v[51]*MainFormSLS->hh_1[65]
 + c2.v[52]*MainFormSLS->hh_1[15]
 + c2.v[53]*MainFormSLS->hh_1[125]
 + c2.v[54]*MainFormSLS->hh_1[75]
 + c2.v[55]*MainFormSLS->hh_1[25]
 + c2.v[56]*MainFormSLS->hh_1[135]
 + c2.v[57]*MainFormSLS->hh_1[85]
 + c2.v[58]*MainFormSLS->hh_1[35]
 + c2.v[59]*MainFormSLS->hh_1[145]
 + c2.v[60]*MainFormSLS->hh_1[95]
 + c2.v[61]*MainFormSLS->hh_1[45]
 + c2.v[62]*MainFormSLS->hh_1[155]
 + c2.v[63]*MainFormSLS->hh_1[105]
 + c2.v[64]*MainFormSLS->hh_1[55]
 + c2.v[65]*MainFormSLS->hh_1[5]
 + c2.v[66]*MainFormSLS->hh_1[115]
 + c2.v[67]*MainFormSLS->hh_1[65]
 + c2.v[68]*MainFormSLS->hh_1[15]
 + c2.v[69]*MainFormSLS->hh_1[125]
 + c2.v[70]*MainFormSLS->hh_1[75]
 + c2.v[71]*MainFormSLS->hh_1[25]
 + c2.v[72]*MainFormSLS->hh_1[135]
 + c2.v[73]*MainFormSLS->hh_1[85]
 + c2.v[74]*MainFormSLS->hh_1[35]
 + c2.v[75]*MainFormSLS->hh_1[145]
 + c2.v[76]*MainFormSLS->hh_1[95]
 + c2.v[77]*MainFormSLS->hh_1[45]
 + c2.v[78]*MainFormSLS->hh_1[155]
 + c2.v[79]*MainFormSLS->hh_1[105];
s/=N_2;
out.push_back(s);
//������ 56
s =c2.v[0]*MainFormSLS->hh_1[56]
 + c2.v[1]*MainFormSLS->hh_1[8]
 + c2.v[2]*MainFormSLS->hh_1[120]
 + c2.v[3]*MainFormSLS->hh_1[72]
 + c2.v[4]*MainFormSLS->hh_1[24]
 + c2.v[5]*MainFormSLS->hh_1[136]
 + c2.v[6]*MainFormSLS->hh_1[88]
 + c2.v[7]*MainFormSLS->hh_1[40]
 + c2.v[8]*MainFormSLS->hh_1[152]
 + c2.v[9]*MainFormSLS->hh_1[104]
 + c2.v[10]*MainFormSLS->hh_1[56]
 + c2.v[11]*MainFormSLS->hh_1[8]
 + c2.v[12]*MainFormSLS->hh_1[120]
 + c2.v[13]*MainFormSLS->hh_1[72]
 + c2.v[14]*MainFormSLS->hh_1[24]
 + c2.v[15]*MainFormSLS->hh_1[136]
 + c2.v[16]*MainFormSLS->hh_1[88]
 + c2.v[17]*MainFormSLS->hh_1[40]
 + c2.v[18]*MainFormSLS->hh_1[152]
 + c2.v[19]*MainFormSLS->hh_1[104]
 + c2.v[20]*MainFormSLS->hh_1[56]
 + c2.v[21]*MainFormSLS->hh_1[8]
 + c2.v[22]*MainFormSLS->hh_1[120]
 + c2.v[23]*MainFormSLS->hh_1[72]
 + c2.v[24]*MainFormSLS->hh_1[24]
 + c2.v[25]*MainFormSLS->hh_1[136]
 + c2.v[26]*MainFormSLS->hh_1[88]
 + c2.v[27]*MainFormSLS->hh_1[40]
 + c2.v[28]*MainFormSLS->hh_1[152]
 + c2.v[29]*MainFormSLS->hh_1[104]
 + c2.v[30]*MainFormSLS->hh_1[56]
 + c2.v[31]*MainFormSLS->hh_1[8]
 + c2.v[32]*MainFormSLS->hh_1[120]
 + c2.v[33]*MainFormSLS->hh_1[72]
 + c2.v[34]*MainFormSLS->hh_1[24]
 + c2.v[35]*MainFormSLS->hh_1[136]
 + c2.v[36]*MainFormSLS->hh_1[88]
 + c2.v[37]*MainFormSLS->hh_1[40]
 + c2.v[38]*MainFormSLS->hh_1[152]
 + c2.v[39]*MainFormSLS->hh_1[104]
 + c2.v[40]*MainFormSLS->hh_1[56]
 + c2.v[41]*MainFormSLS->hh_1[8]
 + c2.v[42]*MainFormSLS->hh_1[120]
 + c2.v[43]*MainFormSLS->hh_1[72]
 + c2.v[44]*MainFormSLS->hh_1[24]
 + c2.v[45]*MainFormSLS->hh_1[136]
 + c2.v[46]*MainFormSLS->hh_1[88]
 + c2.v[47]*MainFormSLS->hh_1[40]
 + c2.v[48]*MainFormSLS->hh_1[152]
 + c2.v[49]*MainFormSLS->hh_1[104]
 + c2.v[50]*MainFormSLS->hh_1[56]
 + c2.v[51]*MainFormSLS->hh_1[8]
 + c2.v[52]*MainFormSLS->hh_1[120]
 + c2.v[53]*MainFormSLS->hh_1[72]
 + c2.v[54]*MainFormSLS->hh_1[24]
 + c2.v[55]*MainFormSLS->hh_1[136]
 + c2.v[56]*MainFormSLS->hh_1[88]
 + c2.v[57]*MainFormSLS->hh_1[40]
 + c2.v[58]*MainFormSLS->hh_1[152]
 + c2.v[59]*MainFormSLS->hh_1[104]
 + c2.v[60]*MainFormSLS->hh_1[56]
 + c2.v[61]*MainFormSLS->hh_1[8]
 + c2.v[62]*MainFormSLS->hh_1[120]
 + c2.v[63]*MainFormSLS->hh_1[72]
 + c2.v[64]*MainFormSLS->hh_1[24]
 + c2.v[65]*MainFormSLS->hh_1[136]
 + c2.v[66]*MainFormSLS->hh_1[88]
 + c2.v[67]*MainFormSLS->hh_1[40]
 + c2.v[68]*MainFormSLS->hh_1[152]
 + c2.v[69]*MainFormSLS->hh_1[104]
 + c2.v[70]*MainFormSLS->hh_1[56]
 + c2.v[71]*MainFormSLS->hh_1[8]
 + c2.v[72]*MainFormSLS->hh_1[120]
 + c2.v[73]*MainFormSLS->hh_1[72]
 + c2.v[74]*MainFormSLS->hh_1[24]
 + c2.v[75]*MainFormSLS->hh_1[136]
 + c2.v[76]*MainFormSLS->hh_1[88]
 + c2.v[77]*MainFormSLS->hh_1[40]
 + c2.v[78]*MainFormSLS->hh_1[152]
 + c2.v[79]*MainFormSLS->hh_1[104];
s/=N_2;
out.push_back(s);
//������ 57
s =c2.v[0]*MainFormSLS->hh_1[57]
 + c2.v[1]*MainFormSLS->hh_1[11]
 + c2.v[2]*MainFormSLS->hh_1[125]
 + c2.v[3]*MainFormSLS->hh_1[79]
 + c2.v[4]*MainFormSLS->hh_1[33]
 + c2.v[5]*MainFormSLS->hh_1[147]
 + c2.v[6]*MainFormSLS->hh_1[101]
 + c2.v[7]*MainFormSLS->hh_1[55]
 + c2.v[8]*MainFormSLS->hh_1[9]
 + c2.v[9]*MainFormSLS->hh_1[123]
 + c2.v[10]*MainFormSLS->hh_1[77]
 + c2.v[11]*MainFormSLS->hh_1[31]
 + c2.v[12]*MainFormSLS->hh_1[145]
 + c2.v[13]*MainFormSLS->hh_1[99]
 + c2.v[14]*MainFormSLS->hh_1[53]
 + c2.v[15]*MainFormSLS->hh_1[7]
 + c2.v[16]*MainFormSLS->hh_1[121]
 + c2.v[17]*MainFormSLS->hh_1[75]
 + c2.v[18]*MainFormSLS->hh_1[29]
 + c2.v[19]*MainFormSLS->hh_1[143]
 + c2.v[20]*MainFormSLS->hh_1[97]
 + c2.v[21]*MainFormSLS->hh_1[51]
 + c2.v[22]*MainFormSLS->hh_1[5]
 + c2.v[23]*MainFormSLS->hh_1[119]
 + c2.v[24]*MainFormSLS->hh_1[73]
 + c2.v[25]*MainFormSLS->hh_1[27]
 + c2.v[26]*MainFormSLS->hh_1[141]
 + c2.v[27]*MainFormSLS->hh_1[95]
 + c2.v[28]*MainFormSLS->hh_1[49]
 + c2.v[29]*MainFormSLS->hh_1[3]
 + c2.v[30]*MainFormSLS->hh_1[117]
 + c2.v[31]*MainFormSLS->hh_1[71]
 + c2.v[32]*MainFormSLS->hh_1[25]
 + c2.v[33]*MainFormSLS->hh_1[139]
 + c2.v[34]*MainFormSLS->hh_1[93]
 + c2.v[35]*MainFormSLS->hh_1[47]
 + c2.v[36]*MainFormSLS->hh_1[1]
 + c2.v[37]*MainFormSLS->hh_1[115]
 + c2.v[38]*MainFormSLS->hh_1[69]
 + c2.v[39]*MainFormSLS->hh_1[23]
 + c2.v[40]*MainFormSLS->hh_1[137]
 + c2.v[41]*MainFormSLS->hh_1[91]
 + c2.v[42]*MainFormSLS->hh_1[45]
 + c2.v[43]*MainFormSLS->hh_1[159]
 + c2.v[44]*MainFormSLS->hh_1[113]
 + c2.v[45]*MainFormSLS->hh_1[67]
 + c2.v[46]*MainFormSLS->hh_1[21]
 + c2.v[47]*MainFormSLS->hh_1[135]
 + c2.v[48]*MainFormSLS->hh_1[89]
 + c2.v[49]*MainFormSLS->hh_1[43]
 + c2.v[50]*MainFormSLS->hh_1[157]
 + c2.v[51]*MainFormSLS->hh_1[111]
 + c2.v[52]*MainFormSLS->hh_1[65]
 + c2.v[53]*MainFormSLS->hh_1[19]
 + c2.v[54]*MainFormSLS->hh_1[133]
 + c2.v[55]*MainFormSLS->hh_1[87]
 + c2.v[56]*MainFormSLS->hh_1[41]
 + c2.v[57]*MainFormSLS->hh_1[155]
 + c2.v[58]*MainFormSLS->hh_1[109]
 + c2.v[59]*MainFormSLS->hh_1[63]
 + c2.v[60]*MainFormSLS->hh_1[17]
 + c2.v[61]*MainFormSLS->hh_1[131]
 + c2.v[62]*MainFormSLS->hh_1[85]
 + c2.v[63]*MainFormSLS->hh_1[39]
 + c2.v[64]*MainFormSLS->hh_1[153]
 + c2.v[65]*MainFormSLS->hh_1[107]
 + c2.v[66]*MainFormSLS->hh_1[61]
 + c2.v[67]*MainFormSLS->hh_1[15]
 + c2.v[68]*MainFormSLS->hh_1[129]
 + c2.v[69]*MainFormSLS->hh_1[83]
 + c2.v[70]*MainFormSLS->hh_1[37]
 + c2.v[71]*MainFormSLS->hh_1[151]
 + c2.v[72]*MainFormSLS->hh_1[105]
 + c2.v[73]*MainFormSLS->hh_1[59]
 + c2.v[74]*MainFormSLS->hh_1[13]
 + c2.v[75]*MainFormSLS->hh_1[127]
 + c2.v[76]*MainFormSLS->hh_1[81]
 + c2.v[77]*MainFormSLS->hh_1[35]
 + c2.v[78]*MainFormSLS->hh_1[149]
 + c2.v[79]*MainFormSLS->hh_1[103];
s/=N_2;
out.push_back(s);
//������ 58
s =c2.v[0]*MainFormSLS->hh_1[58]
 + c2.v[1]*MainFormSLS->hh_1[14]
 + c2.v[2]*MainFormSLS->hh_1[130]
 + c2.v[3]*MainFormSLS->hh_1[86]
 + c2.v[4]*MainFormSLS->hh_1[42]
 + c2.v[5]*MainFormSLS->hh_1[158]
 + c2.v[6]*MainFormSLS->hh_1[114]
 + c2.v[7]*MainFormSLS->hh_1[70]
 + c2.v[8]*MainFormSLS->hh_1[26]
 + c2.v[9]*MainFormSLS->hh_1[142]
 + c2.v[10]*MainFormSLS->hh_1[98]
 + c2.v[11]*MainFormSLS->hh_1[54]
 + c2.v[12]*MainFormSLS->hh_1[10]
 + c2.v[13]*MainFormSLS->hh_1[126]
 + c2.v[14]*MainFormSLS->hh_1[82]
 + c2.v[15]*MainFormSLS->hh_1[38]
 + c2.v[16]*MainFormSLS->hh_1[154]
 + c2.v[17]*MainFormSLS->hh_1[110]
 + c2.v[18]*MainFormSLS->hh_1[66]
 + c2.v[19]*MainFormSLS->hh_1[22]
 + c2.v[20]*MainFormSLS->hh_1[138]
 + c2.v[21]*MainFormSLS->hh_1[94]
 + c2.v[22]*MainFormSLS->hh_1[50]
 + c2.v[23]*MainFormSLS->hh_1[6]
 + c2.v[24]*MainFormSLS->hh_1[122]
 + c2.v[25]*MainFormSLS->hh_1[78]
 + c2.v[26]*MainFormSLS->hh_1[34]
 + c2.v[27]*MainFormSLS->hh_1[150]
 + c2.v[28]*MainFormSLS->hh_1[106]
 + c2.v[29]*MainFormSLS->hh_1[62]
 + c2.v[30]*MainFormSLS->hh_1[18]
 + c2.v[31]*MainFormSLS->hh_1[134]
 + c2.v[32]*MainFormSLS->hh_1[90]
 + c2.v[33]*MainFormSLS->hh_1[46]
 + c2.v[34]*MainFormSLS->hh_1[2]
 + c2.v[35]*MainFormSLS->hh_1[118]
 + c2.v[36]*MainFormSLS->hh_1[74]
 + c2.v[37]*MainFormSLS->hh_1[30]
 + c2.v[38]*MainFormSLS->hh_1[146]
 + c2.v[39]*MainFormSLS->hh_1[102]
 + c2.v[40]*MainFormSLS->hh_1[58]
 + c2.v[41]*MainFormSLS->hh_1[14]
 + c2.v[42]*MainFormSLS->hh_1[130]
 + c2.v[43]*MainFormSLS->hh_1[86]
 + c2.v[44]*MainFormSLS->hh_1[42]
 + c2.v[45]*MainFormSLS->hh_1[158]
 + c2.v[46]*MainFormSLS->hh_1[114]
 + c2.v[47]*MainFormSLS->hh_1[70]
 + c2.v[48]*MainFormSLS->hh_1[26]
 + c2.v[49]*MainFormSLS->hh_1[142]
 + c2.v[50]*MainFormSLS->hh_1[98]
 + c2.v[51]*MainFormSLS->hh_1[54]
 + c2.v[52]*MainFormSLS->hh_1[10]
 + c2.v[53]*MainFormSLS->hh_1[126]
 + c2.v[54]*MainFormSLS->hh_1[82]
 + c2.v[55]*MainFormSLS->hh_1[38]
 + c2.v[56]*MainFormSLS->hh_1[154]
 + c2.v[57]*MainFormSLS->hh_1[110]
 + c2.v[58]*MainFormSLS->hh_1[66]
 + c2.v[59]*MainFormSLS->hh_1[22]
 + c2.v[60]*MainFormSLS->hh_1[138]
 + c2.v[61]*MainFormSLS->hh_1[94]
 + c2.v[62]*MainFormSLS->hh_1[50]
 + c2.v[63]*MainFormSLS->hh_1[6]
 + c2.v[64]*MainFormSLS->hh_1[122]
 + c2.v[65]*MainFormSLS->hh_1[78]
 + c2.v[66]*MainFormSLS->hh_1[34]
 + c2.v[67]*MainFormSLS->hh_1[150]
 + c2.v[68]*MainFormSLS->hh_1[106]
 + c2.v[69]*MainFormSLS->hh_1[62]
 + c2.v[70]*MainFormSLS->hh_1[18]
 + c2.v[71]*MainFormSLS->hh_1[134]
 + c2.v[72]*MainFormSLS->hh_1[90]
 + c2.v[73]*MainFormSLS->hh_1[46]
 + c2.v[74]*MainFormSLS->hh_1[2]
 + c2.v[75]*MainFormSLS->hh_1[118]
 + c2.v[76]*MainFormSLS->hh_1[74]
 + c2.v[77]*MainFormSLS->hh_1[30]
 + c2.v[78]*MainFormSLS->hh_1[146]
 + c2.v[79]*MainFormSLS->hh_1[102];
s/=N_2;
out.push_back(s);
//������ 59
s =c2.v[0]*MainFormSLS->hh_1[59]
 + c2.v[1]*MainFormSLS->hh_1[17]
 + c2.v[2]*MainFormSLS->hh_1[135]
 + c2.v[3]*MainFormSLS->hh_1[93]
 + c2.v[4]*MainFormSLS->hh_1[51]
 + c2.v[5]*MainFormSLS->hh_1[9]
 + c2.v[6]*MainFormSLS->hh_1[127]
 + c2.v[7]*MainFormSLS->hh_1[85]
 + c2.v[8]*MainFormSLS->hh_1[43]
 + c2.v[9]*MainFormSLS->hh_1[1]
 + c2.v[10]*MainFormSLS->hh_1[119]
 + c2.v[11]*MainFormSLS->hh_1[77]
 + c2.v[12]*MainFormSLS->hh_1[35]
 + c2.v[13]*MainFormSLS->hh_1[153]
 + c2.v[14]*MainFormSLS->hh_1[111]
 + c2.v[15]*MainFormSLS->hh_1[69]
 + c2.v[16]*MainFormSLS->hh_1[27]
 + c2.v[17]*MainFormSLS->hh_1[145]
 + c2.v[18]*MainFormSLS->hh_1[103]
 + c2.v[19]*MainFormSLS->hh_1[61]
 + c2.v[20]*MainFormSLS->hh_1[19]
 + c2.v[21]*MainFormSLS->hh_1[137]
 + c2.v[22]*MainFormSLS->hh_1[95]
 + c2.v[23]*MainFormSLS->hh_1[53]
 + c2.v[24]*MainFormSLS->hh_1[11]
 + c2.v[25]*MainFormSLS->hh_1[129]
 + c2.v[26]*MainFormSLS->hh_1[87]
 + c2.v[27]*MainFormSLS->hh_1[45]
 + c2.v[28]*MainFormSLS->hh_1[3]
 + c2.v[29]*MainFormSLS->hh_1[121]
 + c2.v[30]*MainFormSLS->hh_1[79]
 + c2.v[31]*MainFormSLS->hh_1[37]
 + c2.v[32]*MainFormSLS->hh_1[155]
 + c2.v[33]*MainFormSLS->hh_1[113]
 + c2.v[34]*MainFormSLS->hh_1[71]
 + c2.v[35]*MainFormSLS->hh_1[29]
 + c2.v[36]*MainFormSLS->hh_1[147]
 + c2.v[37]*MainFormSLS->hh_1[105]
 + c2.v[38]*MainFormSLS->hh_1[63]
 + c2.v[39]*MainFormSLS->hh_1[21]
 + c2.v[40]*MainFormSLS->hh_1[139]
 + c2.v[41]*MainFormSLS->hh_1[97]
 + c2.v[42]*MainFormSLS->hh_1[55]
 + c2.v[43]*MainFormSLS->hh_1[13]
 + c2.v[44]*MainFormSLS->hh_1[131]
 + c2.v[45]*MainFormSLS->hh_1[89]
 + c2.v[46]*MainFormSLS->hh_1[47]
 + c2.v[47]*MainFormSLS->hh_1[5]
 + c2.v[48]*MainFormSLS->hh_1[123]
 + c2.v[49]*MainFormSLS->hh_1[81]
 + c2.v[50]*MainFormSLS->hh_1[39]
 + c2.v[51]*MainFormSLS->hh_1[157]
 + c2.v[52]*MainFormSLS->hh_1[115]
 + c2.v[53]*MainFormSLS->hh_1[73]
 + c2.v[54]*MainFormSLS->hh_1[31]
 + c2.v[55]*MainFormSLS->hh_1[149]
 + c2.v[56]*MainFormSLS->hh_1[107]
 + c2.v[57]*MainFormSLS->hh_1[65]
 + c2.v[58]*MainFormSLS->hh_1[23]
 + c2.v[59]*MainFormSLS->hh_1[141]
 + c2.v[60]*MainFormSLS->hh_1[99]
 + c2.v[61]*MainFormSLS->hh_1[57]
 + c2.v[62]*MainFormSLS->hh_1[15]
 + c2.v[63]*MainFormSLS->hh_1[133]
 + c2.v[64]*MainFormSLS->hh_1[91]
 + c2.v[65]*MainFormSLS->hh_1[49]
 + c2.v[66]*MainFormSLS->hh_1[7]
 + c2.v[67]*MainFormSLS->hh_1[125]
 + c2.v[68]*MainFormSLS->hh_1[83]
 + c2.v[69]*MainFormSLS->hh_1[41]
 + c2.v[70]*MainFormSLS->hh_1[159]
 + c2.v[71]*MainFormSLS->hh_1[117]
 + c2.v[72]*MainFormSLS->hh_1[75]
 + c2.v[73]*MainFormSLS->hh_1[33]
 + c2.v[74]*MainFormSLS->hh_1[151]
 + c2.v[75]*MainFormSLS->hh_1[109]
 + c2.v[76]*MainFormSLS->hh_1[67]
 + c2.v[77]*MainFormSLS->hh_1[25]
 + c2.v[78]*MainFormSLS->hh_1[143]
 + c2.v[79]*MainFormSLS->hh_1[101];
s/=N_2;
out.push_back(s);
//������ 60
s =c2.v[0]*MainFormSLS->hh_1[60]
 + c2.v[1]*MainFormSLS->hh_1[20]
 + c2.v[2]*MainFormSLS->hh_1[140]
 + c2.v[3]*MainFormSLS->hh_1[100]
 + c2.v[4]*MainFormSLS->hh_1[60]
 + c2.v[5]*MainFormSLS->hh_1[20]
 + c2.v[6]*MainFormSLS->hh_1[140]
 + c2.v[7]*MainFormSLS->hh_1[100]
 + c2.v[8]*MainFormSLS->hh_1[60]
 + c2.v[9]*MainFormSLS->hh_1[20]
 + c2.v[10]*MainFormSLS->hh_1[140]
 + c2.v[11]*MainFormSLS->hh_1[100]
 + c2.v[12]*MainFormSLS->hh_1[60]
 + c2.v[13]*MainFormSLS->hh_1[20]
 + c2.v[14]*MainFormSLS->hh_1[140]
 + c2.v[15]*MainFormSLS->hh_1[100]
 + c2.v[16]*MainFormSLS->hh_1[60]
 + c2.v[17]*MainFormSLS->hh_1[20]
 + c2.v[18]*MainFormSLS->hh_1[140]
 + c2.v[19]*MainFormSLS->hh_1[100]
 + c2.v[20]*MainFormSLS->hh_1[60]
 + c2.v[21]*MainFormSLS->hh_1[20]
 + c2.v[22]*MainFormSLS->hh_1[140]
 + c2.v[23]*MainFormSLS->hh_1[100]
 + c2.v[24]*MainFormSLS->hh_1[60]
 + c2.v[25]*MainFormSLS->hh_1[20]
 + c2.v[26]*MainFormSLS->hh_1[140]
 + c2.v[27]*MainFormSLS->hh_1[100]
 + c2.v[28]*MainFormSLS->hh_1[60]
 + c2.v[29]*MainFormSLS->hh_1[20]
 + c2.v[30]*MainFormSLS->hh_1[140]
 + c2.v[31]*MainFormSLS->hh_1[100]
 + c2.v[32]*MainFormSLS->hh_1[60]
 + c2.v[33]*MainFormSLS->hh_1[20]
 + c2.v[34]*MainFormSLS->hh_1[140]
 + c2.v[35]*MainFormSLS->hh_1[100]
 + c2.v[36]*MainFormSLS->hh_1[60]
 + c2.v[37]*MainFormSLS->hh_1[20]
 + c2.v[38]*MainFormSLS->hh_1[140]
 + c2.v[39]*MainFormSLS->hh_1[100]
 + c2.v[40]*MainFormSLS->hh_1[60]
 + c2.v[41]*MainFormSLS->hh_1[20]
 + c2.v[42]*MainFormSLS->hh_1[140]
 + c2.v[43]*MainFormSLS->hh_1[100]
 + c2.v[44]*MainFormSLS->hh_1[60]
 + c2.v[45]*MainFormSLS->hh_1[20]
 + c2.v[46]*MainFormSLS->hh_1[140]
 + c2.v[47]*MainFormSLS->hh_1[100]
 + c2.v[48]*MainFormSLS->hh_1[60]
 + c2.v[49]*MainFormSLS->hh_1[20]
 + c2.v[50]*MainFormSLS->hh_1[140]
 + c2.v[51]*MainFormSLS->hh_1[100]
 + c2.v[52]*MainFormSLS->hh_1[60]
 + c2.v[53]*MainFormSLS->hh_1[20]
 + c2.v[54]*MainFormSLS->hh_1[140]
 + c2.v[55]*MainFormSLS->hh_1[100]
 + c2.v[56]*MainFormSLS->hh_1[60]
 + c2.v[57]*MainFormSLS->hh_1[20]
 + c2.v[58]*MainFormSLS->hh_1[140]
 + c2.v[59]*MainFormSLS->hh_1[100]
 + c2.v[60]*MainFormSLS->hh_1[60]
 + c2.v[61]*MainFormSLS->hh_1[20]
 + c2.v[62]*MainFormSLS->hh_1[140]
 + c2.v[63]*MainFormSLS->hh_1[100]
 + c2.v[64]*MainFormSLS->hh_1[60]
 + c2.v[65]*MainFormSLS->hh_1[20]
 + c2.v[66]*MainFormSLS->hh_1[140]
 + c2.v[67]*MainFormSLS->hh_1[100]
 + c2.v[68]*MainFormSLS->hh_1[60]
 + c2.v[69]*MainFormSLS->hh_1[20]
 + c2.v[70]*MainFormSLS->hh_1[140]
 + c2.v[71]*MainFormSLS->hh_1[100]
 + c2.v[72]*MainFormSLS->hh_1[60]
 + c2.v[73]*MainFormSLS->hh_1[20]
 + c2.v[74]*MainFormSLS->hh_1[140]
 + c2.v[75]*MainFormSLS->hh_1[100]
 + c2.v[76]*MainFormSLS->hh_1[60]
 + c2.v[77]*MainFormSLS->hh_1[20]
 + c2.v[78]*MainFormSLS->hh_1[140]
 + c2.v[79]*MainFormSLS->hh_1[100];
s/=N_2;
out.push_back(s);
//������ 61
s =c2.v[0]*MainFormSLS->hh_1[61]
 + c2.v[1]*MainFormSLS->hh_1[23]
 + c2.v[2]*MainFormSLS->hh_1[145]
 + c2.v[3]*MainFormSLS->hh_1[107]
 + c2.v[4]*MainFormSLS->hh_1[69]
 + c2.v[5]*MainFormSLS->hh_1[31]
 + c2.v[6]*MainFormSLS->hh_1[153]
 + c2.v[7]*MainFormSLS->hh_1[115]
 + c2.v[8]*MainFormSLS->hh_1[77]
 + c2.v[9]*MainFormSLS->hh_1[39]
 + c2.v[10]*MainFormSLS->hh_1[1]
 + c2.v[11]*MainFormSLS->hh_1[123]
 + c2.v[12]*MainFormSLS->hh_1[85]
 + c2.v[13]*MainFormSLS->hh_1[47]
 + c2.v[14]*MainFormSLS->hh_1[9]
 + c2.v[15]*MainFormSLS->hh_1[131]
 + c2.v[16]*MainFormSLS->hh_1[93]
 + c2.v[17]*MainFormSLS->hh_1[55]
 + c2.v[18]*MainFormSLS->hh_1[17]
 + c2.v[19]*MainFormSLS->hh_1[139]
 + c2.v[20]*MainFormSLS->hh_1[101]
 + c2.v[21]*MainFormSLS->hh_1[63]
 + c2.v[22]*MainFormSLS->hh_1[25]
 + c2.v[23]*MainFormSLS->hh_1[147]
 + c2.v[24]*MainFormSLS->hh_1[109]
 + c2.v[25]*MainFormSLS->hh_1[71]
 + c2.v[26]*MainFormSLS->hh_1[33]
 + c2.v[27]*MainFormSLS->hh_1[155]
 + c2.v[28]*MainFormSLS->hh_1[117]
 + c2.v[29]*MainFormSLS->hh_1[79]
 + c2.v[30]*MainFormSLS->hh_1[41]
 + c2.v[31]*MainFormSLS->hh_1[3]
 + c2.v[32]*MainFormSLS->hh_1[125]
 + c2.v[33]*MainFormSLS->hh_1[87]
 + c2.v[34]*MainFormSLS->hh_1[49]
 + c2.v[35]*MainFormSLS->hh_1[11]
 + c2.v[36]*MainFormSLS->hh_1[133]
 + c2.v[37]*MainFormSLS->hh_1[95]
 + c2.v[38]*MainFormSLS->hh_1[57]
 + c2.v[39]*MainFormSLS->hh_1[19]
 + c2.v[40]*MainFormSLS->hh_1[141]
 + c2.v[41]*MainFormSLS->hh_1[103]
 + c2.v[42]*MainFormSLS->hh_1[65]
 + c2.v[43]*MainFormSLS->hh_1[27]
 + c2.v[44]*MainFormSLS->hh_1[149]
 + c2.v[45]*MainFormSLS->hh_1[111]
 + c2.v[46]*MainFormSLS->hh_1[73]
 + c2.v[47]*MainFormSLS->hh_1[35]
 + c2.v[48]*MainFormSLS->hh_1[157]
 + c2.v[49]*MainFormSLS->hh_1[119]
 + c2.v[50]*MainFormSLS->hh_1[81]
 + c2.v[51]*MainFormSLS->hh_1[43]
 + c2.v[52]*MainFormSLS->hh_1[5]
 + c2.v[53]*MainFormSLS->hh_1[127]
 + c2.v[54]*MainFormSLS->hh_1[89]
 + c2.v[55]*MainFormSLS->hh_1[51]
 + c2.v[56]*MainFormSLS->hh_1[13]
 + c2.v[57]*MainFormSLS->hh_1[135]
 + c2.v[58]*MainFormSLS->hh_1[97]
 + c2.v[59]*MainFormSLS->hh_1[59]
 + c2.v[60]*MainFormSLS->hh_1[21]
 + c2.v[61]*MainFormSLS->hh_1[143]
 + c2.v[62]*MainFormSLS->hh_1[105]
 + c2.v[63]*MainFormSLS->hh_1[67]
 + c2.v[64]*MainFormSLS->hh_1[29]
 + c2.v[65]*MainFormSLS->hh_1[151]
 + c2.v[66]*MainFormSLS->hh_1[113]
 + c2.v[67]*MainFormSLS->hh_1[75]
 + c2.v[68]*MainFormSLS->hh_1[37]
 + c2.v[69]*MainFormSLS->hh_1[159]
 + c2.v[70]*MainFormSLS->hh_1[121]
 + c2.v[71]*MainFormSLS->hh_1[83]
 + c2.v[72]*MainFormSLS->hh_1[45]
 + c2.v[73]*MainFormSLS->hh_1[7]
 + c2.v[74]*MainFormSLS->hh_1[129]
 + c2.v[75]*MainFormSLS->hh_1[91]
 + c2.v[76]*MainFormSLS->hh_1[53]
 + c2.v[77]*MainFormSLS->hh_1[15]
 + c2.v[78]*MainFormSLS->hh_1[137]
 + c2.v[79]*MainFormSLS->hh_1[99];
s/=N_2;
out.push_back(s);
//������ 62
s =c2.v[0]*MainFormSLS->hh_1[62]
 + c2.v[1]*MainFormSLS->hh_1[26]
 + c2.v[2]*MainFormSLS->hh_1[150]
 + c2.v[3]*MainFormSLS->hh_1[114]
 + c2.v[4]*MainFormSLS->hh_1[78]
 + c2.v[5]*MainFormSLS->hh_1[42]
 + c2.v[6]*MainFormSLS->hh_1[6]
 + c2.v[7]*MainFormSLS->hh_1[130]
 + c2.v[8]*MainFormSLS->hh_1[94]
 + c2.v[9]*MainFormSLS->hh_1[58]
 + c2.v[10]*MainFormSLS->hh_1[22]
 + c2.v[11]*MainFormSLS->hh_1[146]
 + c2.v[12]*MainFormSLS->hh_1[110]
 + c2.v[13]*MainFormSLS->hh_1[74]
 + c2.v[14]*MainFormSLS->hh_1[38]
 + c2.v[15]*MainFormSLS->hh_1[2]
 + c2.v[16]*MainFormSLS->hh_1[126]
 + c2.v[17]*MainFormSLS->hh_1[90]
 + c2.v[18]*MainFormSLS->hh_1[54]
 + c2.v[19]*MainFormSLS->hh_1[18]
 + c2.v[20]*MainFormSLS->hh_1[142]
 + c2.v[21]*MainFormSLS->hh_1[106]
 + c2.v[22]*MainFormSLS->hh_1[70]
 + c2.v[23]*MainFormSLS->hh_1[34]
 + c2.v[24]*MainFormSLS->hh_1[158]
 + c2.v[25]*MainFormSLS->hh_1[122]
 + c2.v[26]*MainFormSLS->hh_1[86]
 + c2.v[27]*MainFormSLS->hh_1[50]
 + c2.v[28]*MainFormSLS->hh_1[14]
 + c2.v[29]*MainFormSLS->hh_1[138]
 + c2.v[30]*MainFormSLS->hh_1[102]
 + c2.v[31]*MainFormSLS->hh_1[66]
 + c2.v[32]*MainFormSLS->hh_1[30]
 + c2.v[33]*MainFormSLS->hh_1[154]
 + c2.v[34]*MainFormSLS->hh_1[118]
 + c2.v[35]*MainFormSLS->hh_1[82]
 + c2.v[36]*MainFormSLS->hh_1[46]
 + c2.v[37]*MainFormSLS->hh_1[10]
 + c2.v[38]*MainFormSLS->hh_1[134]
 + c2.v[39]*MainFormSLS->hh_1[98]
 + c2.v[40]*MainFormSLS->hh_1[62]
 + c2.v[41]*MainFormSLS->hh_1[26]
 + c2.v[42]*MainFormSLS->hh_1[150]
 + c2.v[43]*MainFormSLS->hh_1[114]
 + c2.v[44]*MainFormSLS->hh_1[78]
 + c2.v[45]*MainFormSLS->hh_1[42]
 + c2.v[46]*MainFormSLS->hh_1[6]
 + c2.v[47]*MainFormSLS->hh_1[130]
 + c2.v[48]*MainFormSLS->hh_1[94]
 + c2.v[49]*MainFormSLS->hh_1[58]
 + c2.v[50]*MainFormSLS->hh_1[22]
 + c2.v[51]*MainFormSLS->hh_1[146]
 + c2.v[52]*MainFormSLS->hh_1[110]
 + c2.v[53]*MainFormSLS->hh_1[74]
 + c2.v[54]*MainFormSLS->hh_1[38]
 + c2.v[55]*MainFormSLS->hh_1[2]
 + c2.v[56]*MainFormSLS->hh_1[126]
 + c2.v[57]*MainFormSLS->hh_1[90]
 + c2.v[58]*MainFormSLS->hh_1[54]
 + c2.v[59]*MainFormSLS->hh_1[18]
 + c2.v[60]*MainFormSLS->hh_1[142]
 + c2.v[61]*MainFormSLS->hh_1[106]
 + c2.v[62]*MainFormSLS->hh_1[70]
 + c2.v[63]*MainFormSLS->hh_1[34]
 + c2.v[64]*MainFormSLS->hh_1[158]
 + c2.v[65]*MainFormSLS->hh_1[122]
 + c2.v[66]*MainFormSLS->hh_1[86]
 + c2.v[67]*MainFormSLS->hh_1[50]
 + c2.v[68]*MainFormSLS->hh_1[14]
 + c2.v[69]*MainFormSLS->hh_1[138]
 + c2.v[70]*MainFormSLS->hh_1[102]
 + c2.v[71]*MainFormSLS->hh_1[66]
 + c2.v[72]*MainFormSLS->hh_1[30]
 + c2.v[73]*MainFormSLS->hh_1[154]
 + c2.v[74]*MainFormSLS->hh_1[118]
 + c2.v[75]*MainFormSLS->hh_1[82]
 + c2.v[76]*MainFormSLS->hh_1[46]
 + c2.v[77]*MainFormSLS->hh_1[10]
 + c2.v[78]*MainFormSLS->hh_1[134]
 + c2.v[79]*MainFormSLS->hh_1[98];
s/=N_2;
out.push_back(s);
//������ 63
s =c2.v[0]*MainFormSLS->hh_1[63]
 + c2.v[1]*MainFormSLS->hh_1[29]
 + c2.v[2]*MainFormSLS->hh_1[155]
 + c2.v[3]*MainFormSLS->hh_1[121]
 + c2.v[4]*MainFormSLS->hh_1[87]
 + c2.v[5]*MainFormSLS->hh_1[53]
 + c2.v[6]*MainFormSLS->hh_1[19]
 + c2.v[7]*MainFormSLS->hh_1[145]
 + c2.v[8]*MainFormSLS->hh_1[111]
 + c2.v[9]*MainFormSLS->hh_1[77]
 + c2.v[10]*MainFormSLS->hh_1[43]
 + c2.v[11]*MainFormSLS->hh_1[9]
 + c2.v[12]*MainFormSLS->hh_1[135]
 + c2.v[13]*MainFormSLS->hh_1[101]
 + c2.v[14]*MainFormSLS->hh_1[67]
 + c2.v[15]*MainFormSLS->hh_1[33]
 + c2.v[16]*MainFormSLS->hh_1[159]
 + c2.v[17]*MainFormSLS->hh_1[125]
 + c2.v[18]*MainFormSLS->hh_1[91]
 + c2.v[19]*MainFormSLS->hh_1[57]
 + c2.v[20]*MainFormSLS->hh_1[23]
 + c2.v[21]*MainFormSLS->hh_1[149]
 + c2.v[22]*MainFormSLS->hh_1[115]
 + c2.v[23]*MainFormSLS->hh_1[81]
 + c2.v[24]*MainFormSLS->hh_1[47]
 + c2.v[25]*MainFormSLS->hh_1[13]
 + c2.v[26]*MainFormSLS->hh_1[139]
 + c2.v[27]*MainFormSLS->hh_1[105]
 + c2.v[28]*MainFormSLS->hh_1[71]
 + c2.v[29]*MainFormSLS->hh_1[37]
 + c2.v[30]*MainFormSLS->hh_1[3]
 + c2.v[31]*MainFormSLS->hh_1[129]
 + c2.v[32]*MainFormSLS->hh_1[95]
 + c2.v[33]*MainFormSLS->hh_1[61]
 + c2.v[34]*MainFormSLS->hh_1[27]
 + c2.v[35]*MainFormSLS->hh_1[153]
 + c2.v[36]*MainFormSLS->hh_1[119]
 + c2.v[37]*MainFormSLS->hh_1[85]
 + c2.v[38]*MainFormSLS->hh_1[51]
 + c2.v[39]*MainFormSLS->hh_1[17]
 + c2.v[40]*MainFormSLS->hh_1[143]
 + c2.v[41]*MainFormSLS->hh_1[109]
 + c2.v[42]*MainFormSLS->hh_1[75]
 + c2.v[43]*MainFormSLS->hh_1[41]
 + c2.v[44]*MainFormSLS->hh_1[7]
 + c2.v[45]*MainFormSLS->hh_1[133]
 + c2.v[46]*MainFormSLS->hh_1[99]
 + c2.v[47]*MainFormSLS->hh_1[65]
 + c2.v[48]*MainFormSLS->hh_1[31]
 + c2.v[49]*MainFormSLS->hh_1[157]
 + c2.v[50]*MainFormSLS->hh_1[123]
 + c2.v[51]*MainFormSLS->hh_1[89]
 + c2.v[52]*MainFormSLS->hh_1[55]
 + c2.v[53]*MainFormSLS->hh_1[21]
 + c2.v[54]*MainFormSLS->hh_1[147]
 + c2.v[55]*MainFormSLS->hh_1[113]
 + c2.v[56]*MainFormSLS->hh_1[79]
 + c2.v[57]*MainFormSLS->hh_1[45]
 + c2.v[58]*MainFormSLS->hh_1[11]
 + c2.v[59]*MainFormSLS->hh_1[137]
 + c2.v[60]*MainFormSLS->hh_1[103]
 + c2.v[61]*MainFormSLS->hh_1[69]
 + c2.v[62]*MainFormSLS->hh_1[35]
 + c2.v[63]*MainFormSLS->hh_1[1]
 + c2.v[64]*MainFormSLS->hh_1[127]
 + c2.v[65]*MainFormSLS->hh_1[93]
 + c2.v[66]*MainFormSLS->hh_1[59]
 + c2.v[67]*MainFormSLS->hh_1[25]
 + c2.v[68]*MainFormSLS->hh_1[151]
 + c2.v[69]*MainFormSLS->hh_1[117]
 + c2.v[70]*MainFormSLS->hh_1[83]
 + c2.v[71]*MainFormSLS->hh_1[49]
 + c2.v[72]*MainFormSLS->hh_1[15]
 + c2.v[73]*MainFormSLS->hh_1[141]
 + c2.v[74]*MainFormSLS->hh_1[107]
 + c2.v[75]*MainFormSLS->hh_1[73]
 + c2.v[76]*MainFormSLS->hh_1[39]
 + c2.v[77]*MainFormSLS->hh_1[5]
 + c2.v[78]*MainFormSLS->hh_1[131]
 + c2.v[79]*MainFormSLS->hh_1[97];
s/=N_2;
out.push_back(s);
//������ 64
s =c2.v[0]*MainFormSLS->hh_1[64]
 + c2.v[1]*MainFormSLS->hh_1[32]
 + c2.v[2]*MainFormSLS->hh_1[0]
 + c2.v[3]*MainFormSLS->hh_1[128]
 + c2.v[4]*MainFormSLS->hh_1[96]
 + c2.v[5]*MainFormSLS->hh_1[64]
 + c2.v[6]*MainFormSLS->hh_1[32]
 + c2.v[7]*MainFormSLS->hh_1[0]
 + c2.v[8]*MainFormSLS->hh_1[128]
 + c2.v[9]*MainFormSLS->hh_1[96]
 + c2.v[10]*MainFormSLS->hh_1[64]
 + c2.v[11]*MainFormSLS->hh_1[32]
 + c2.v[12]*MainFormSLS->hh_1[0]
 + c2.v[13]*MainFormSLS->hh_1[128]
 + c2.v[14]*MainFormSLS->hh_1[96]
 + c2.v[15]*MainFormSLS->hh_1[64]
 + c2.v[16]*MainFormSLS->hh_1[32]
 + c2.v[17]*MainFormSLS->hh_1[0]
 + c2.v[18]*MainFormSLS->hh_1[128]
 + c2.v[19]*MainFormSLS->hh_1[96]
 + c2.v[20]*MainFormSLS->hh_1[64]
 + c2.v[21]*MainFormSLS->hh_1[32]
 + c2.v[22]*MainFormSLS->hh_1[0]
 + c2.v[23]*MainFormSLS->hh_1[128]
 + c2.v[24]*MainFormSLS->hh_1[96]
 + c2.v[25]*MainFormSLS->hh_1[64]
 + c2.v[26]*MainFormSLS->hh_1[32]
 + c2.v[27]*MainFormSLS->hh_1[0]
 + c2.v[28]*MainFormSLS->hh_1[128]
 + c2.v[29]*MainFormSLS->hh_1[96]
 + c2.v[30]*MainFormSLS->hh_1[64]
 + c2.v[31]*MainFormSLS->hh_1[32]
 + c2.v[32]*MainFormSLS->hh_1[0]
 + c2.v[33]*MainFormSLS->hh_1[128]
 + c2.v[34]*MainFormSLS->hh_1[96]
 + c2.v[35]*MainFormSLS->hh_1[64]
 + c2.v[36]*MainFormSLS->hh_1[32]
 + c2.v[37]*MainFormSLS->hh_1[0]
 + c2.v[38]*MainFormSLS->hh_1[128]
 + c2.v[39]*MainFormSLS->hh_1[96]
 + c2.v[40]*MainFormSLS->hh_1[64]
 + c2.v[41]*MainFormSLS->hh_1[32]
 + c2.v[42]*MainFormSLS->hh_1[0]
 + c2.v[43]*MainFormSLS->hh_1[128]
 + c2.v[44]*MainFormSLS->hh_1[96]
 + c2.v[45]*MainFormSLS->hh_1[64]
 + c2.v[46]*MainFormSLS->hh_1[32]
 + c2.v[47]*MainFormSLS->hh_1[0]
 + c2.v[48]*MainFormSLS->hh_1[128]
 + c2.v[49]*MainFormSLS->hh_1[96]
 + c2.v[50]*MainFormSLS->hh_1[64]
 + c2.v[51]*MainFormSLS->hh_1[32]
 + c2.v[52]*MainFormSLS->hh_1[0]
 + c2.v[53]*MainFormSLS->hh_1[128]
 + c2.v[54]*MainFormSLS->hh_1[96]
 + c2.v[55]*MainFormSLS->hh_1[64]
 + c2.v[56]*MainFormSLS->hh_1[32]
 + c2.v[57]*MainFormSLS->hh_1[0]
 + c2.v[58]*MainFormSLS->hh_1[128]
 + c2.v[59]*MainFormSLS->hh_1[96]
 + c2.v[60]*MainFormSLS->hh_1[64]
 + c2.v[61]*MainFormSLS->hh_1[32]
 + c2.v[62]*MainFormSLS->hh_1[0]
 + c2.v[63]*MainFormSLS->hh_1[128]
 + c2.v[64]*MainFormSLS->hh_1[96]
 + c2.v[65]*MainFormSLS->hh_1[64]
 + c2.v[66]*MainFormSLS->hh_1[32]
 + c2.v[67]*MainFormSLS->hh_1[0]
 + c2.v[68]*MainFormSLS->hh_1[128]
 + c2.v[69]*MainFormSLS->hh_1[96]
 + c2.v[70]*MainFormSLS->hh_1[64]
 + c2.v[71]*MainFormSLS->hh_1[32]
 + c2.v[72]*MainFormSLS->hh_1[0]
 + c2.v[73]*MainFormSLS->hh_1[128]
 + c2.v[74]*MainFormSLS->hh_1[96]
 + c2.v[75]*MainFormSLS->hh_1[64]
 + c2.v[76]*MainFormSLS->hh_1[32]
 + c2.v[77]*MainFormSLS->hh_1[0]
 + c2.v[78]*MainFormSLS->hh_1[128]
 + c2.v[79]*MainFormSLS->hh_1[96];
s/=N_2;
out.push_back(s);
//������ 65
s =c2.v[0]*MainFormSLS->hh_1[65]
 + c2.v[1]*MainFormSLS->hh_1[35]
 + c2.v[2]*MainFormSLS->hh_1[5]
 + c2.v[3]*MainFormSLS->hh_1[135]
 + c2.v[4]*MainFormSLS->hh_1[105]
 + c2.v[5]*MainFormSLS->hh_1[75]
 + c2.v[6]*MainFormSLS->hh_1[45]
 + c2.v[7]*MainFormSLS->hh_1[15]
 + c2.v[8]*MainFormSLS->hh_1[145]
 + c2.v[9]*MainFormSLS->hh_1[115]
 + c2.v[10]*MainFormSLS->hh_1[85]
 + c2.v[11]*MainFormSLS->hh_1[55]
 + c2.v[12]*MainFormSLS->hh_1[25]
 + c2.v[13]*MainFormSLS->hh_1[155]
 + c2.v[14]*MainFormSLS->hh_1[125]
 + c2.v[15]*MainFormSLS->hh_1[95]
 + c2.v[16]*MainFormSLS->hh_1[65]
 + c2.v[17]*MainFormSLS->hh_1[35]
 + c2.v[18]*MainFormSLS->hh_1[5]
 + c2.v[19]*MainFormSLS->hh_1[135]
 + c2.v[20]*MainFormSLS->hh_1[105]
 + c2.v[21]*MainFormSLS->hh_1[75]
 + c2.v[22]*MainFormSLS->hh_1[45]
 + c2.v[23]*MainFormSLS->hh_1[15]
 + c2.v[24]*MainFormSLS->hh_1[145]
 + c2.v[25]*MainFormSLS->hh_1[115]
 + c2.v[26]*MainFormSLS->hh_1[85]
 + c2.v[27]*MainFormSLS->hh_1[55]
 + c2.v[28]*MainFormSLS->hh_1[25]
 + c2.v[29]*MainFormSLS->hh_1[155]
 + c2.v[30]*MainFormSLS->hh_1[125]
 + c2.v[31]*MainFormSLS->hh_1[95]
 + c2.v[32]*MainFormSLS->hh_1[65]
 + c2.v[33]*MainFormSLS->hh_1[35]
 + c2.v[34]*MainFormSLS->hh_1[5]
 + c2.v[35]*MainFormSLS->hh_1[135]
 + c2.v[36]*MainFormSLS->hh_1[105]
 + c2.v[37]*MainFormSLS->hh_1[75]
 + c2.v[38]*MainFormSLS->hh_1[45]
 + c2.v[39]*MainFormSLS->hh_1[15]
 + c2.v[40]*MainFormSLS->hh_1[145]
 + c2.v[41]*MainFormSLS->hh_1[115]
 + c2.v[42]*MainFormSLS->hh_1[85]
 + c2.v[43]*MainFormSLS->hh_1[55]
 + c2.v[44]*MainFormSLS->hh_1[25]
 + c2.v[45]*MainFormSLS->hh_1[155]
 + c2.v[46]*MainFormSLS->hh_1[125]
 + c2.v[47]*MainFormSLS->hh_1[95]
 + c2.v[48]*MainFormSLS->hh_1[65]
 + c2.v[49]*MainFormSLS->hh_1[35]
 + c2.v[50]*MainFormSLS->hh_1[5]
 + c2.v[51]*MainFormSLS->hh_1[135]
 + c2.v[52]*MainFormSLS->hh_1[105]
 + c2.v[53]*MainFormSLS->hh_1[75]
 + c2.v[54]*MainFormSLS->hh_1[45]
 + c2.v[55]*MainFormSLS->hh_1[15]
 + c2.v[56]*MainFormSLS->hh_1[145]
 + c2.v[57]*MainFormSLS->hh_1[115]
 + c2.v[58]*MainFormSLS->hh_1[85]
 + c2.v[59]*MainFormSLS->hh_1[55]
 + c2.v[60]*MainFormSLS->hh_1[25]
 + c2.v[61]*MainFormSLS->hh_1[155]
 + c2.v[62]*MainFormSLS->hh_1[125]
 + c2.v[63]*MainFormSLS->hh_1[95]
 + c2.v[64]*MainFormSLS->hh_1[65]
 + c2.v[65]*MainFormSLS->hh_1[35]
 + c2.v[66]*MainFormSLS->hh_1[5]
 + c2.v[67]*MainFormSLS->hh_1[135]
 + c2.v[68]*MainFormSLS->hh_1[105]
 + c2.v[69]*MainFormSLS->hh_1[75]
 + c2.v[70]*MainFormSLS->hh_1[45]
 + c2.v[71]*MainFormSLS->hh_1[15]
 + c2.v[72]*MainFormSLS->hh_1[145]
 + c2.v[73]*MainFormSLS->hh_1[115]
 + c2.v[74]*MainFormSLS->hh_1[85]
 + c2.v[75]*MainFormSLS->hh_1[55]
 + c2.v[76]*MainFormSLS->hh_1[25]
 + c2.v[77]*MainFormSLS->hh_1[155]
 + c2.v[78]*MainFormSLS->hh_1[125]
 + c2.v[79]*MainFormSLS->hh_1[95];
s/=N_2;
out.push_back(s);
//������ 66
s =c2.v[0]*MainFormSLS->hh_1[66]
 + c2.v[1]*MainFormSLS->hh_1[38]
 + c2.v[2]*MainFormSLS->hh_1[10]
 + c2.v[3]*MainFormSLS->hh_1[142]
 + c2.v[4]*MainFormSLS->hh_1[114]
 + c2.v[5]*MainFormSLS->hh_1[86]
 + c2.v[6]*MainFormSLS->hh_1[58]
 + c2.v[7]*MainFormSLS->hh_1[30]
 + c2.v[8]*MainFormSLS->hh_1[2]
 + c2.v[9]*MainFormSLS->hh_1[134]
 + c2.v[10]*MainFormSLS->hh_1[106]
 + c2.v[11]*MainFormSLS->hh_1[78]
 + c2.v[12]*MainFormSLS->hh_1[50]
 + c2.v[13]*MainFormSLS->hh_1[22]
 + c2.v[14]*MainFormSLS->hh_1[154]
 + c2.v[15]*MainFormSLS->hh_1[126]
 + c2.v[16]*MainFormSLS->hh_1[98]
 + c2.v[17]*MainFormSLS->hh_1[70]
 + c2.v[18]*MainFormSLS->hh_1[42]
 + c2.v[19]*MainFormSLS->hh_1[14]
 + c2.v[20]*MainFormSLS->hh_1[146]
 + c2.v[21]*MainFormSLS->hh_1[118]
 + c2.v[22]*MainFormSLS->hh_1[90]
 + c2.v[23]*MainFormSLS->hh_1[62]
 + c2.v[24]*MainFormSLS->hh_1[34]
 + c2.v[25]*MainFormSLS->hh_1[6]
 + c2.v[26]*MainFormSLS->hh_1[138]
 + c2.v[27]*MainFormSLS->hh_1[110]
 + c2.v[28]*MainFormSLS->hh_1[82]
 + c2.v[29]*MainFormSLS->hh_1[54]
 + c2.v[30]*MainFormSLS->hh_1[26]
 + c2.v[31]*MainFormSLS->hh_1[158]
 + c2.v[32]*MainFormSLS->hh_1[130]
 + c2.v[33]*MainFormSLS->hh_1[102]
 + c2.v[34]*MainFormSLS->hh_1[74]
 + c2.v[35]*MainFormSLS->hh_1[46]
 + c2.v[36]*MainFormSLS->hh_1[18]
 + c2.v[37]*MainFormSLS->hh_1[150]
 + c2.v[38]*MainFormSLS->hh_1[122]
 + c2.v[39]*MainFormSLS->hh_1[94]
 + c2.v[40]*MainFormSLS->hh_1[66]
 + c2.v[41]*MainFormSLS->hh_1[38]
 + c2.v[42]*MainFormSLS->hh_1[10]
 + c2.v[43]*MainFormSLS->hh_1[142]
 + c2.v[44]*MainFormSLS->hh_1[114]
 + c2.v[45]*MainFormSLS->hh_1[86]
 + c2.v[46]*MainFormSLS->hh_1[58]
 + c2.v[47]*MainFormSLS->hh_1[30]
 + c2.v[48]*MainFormSLS->hh_1[2]
 + c2.v[49]*MainFormSLS->hh_1[134]
 + c2.v[50]*MainFormSLS->hh_1[106]
 + c2.v[51]*MainFormSLS->hh_1[78]
 + c2.v[52]*MainFormSLS->hh_1[50]
 + c2.v[53]*MainFormSLS->hh_1[22]
 + c2.v[54]*MainFormSLS->hh_1[154]
 + c2.v[55]*MainFormSLS->hh_1[126]
 + c2.v[56]*MainFormSLS->hh_1[98]
 + c2.v[57]*MainFormSLS->hh_1[70]
 + c2.v[58]*MainFormSLS->hh_1[42]
 + c2.v[59]*MainFormSLS->hh_1[14]
 + c2.v[60]*MainFormSLS->hh_1[146]
 + c2.v[61]*MainFormSLS->hh_1[118]
 + c2.v[62]*MainFormSLS->hh_1[90]
 + c2.v[63]*MainFormSLS->hh_1[62]
 + c2.v[64]*MainFormSLS->hh_1[34]
 + c2.v[65]*MainFormSLS->hh_1[6]
 + c2.v[66]*MainFormSLS->hh_1[138]
 + c2.v[67]*MainFormSLS->hh_1[110]
 + c2.v[68]*MainFormSLS->hh_1[82]
 + c2.v[69]*MainFormSLS->hh_1[54]
 + c2.v[70]*MainFormSLS->hh_1[26]
 + c2.v[71]*MainFormSLS->hh_1[158]
 + c2.v[72]*MainFormSLS->hh_1[130]
 + c2.v[73]*MainFormSLS->hh_1[102]
 + c2.v[74]*MainFormSLS->hh_1[74]
 + c2.v[75]*MainFormSLS->hh_1[46]
 + c2.v[76]*MainFormSLS->hh_1[18]
 + c2.v[77]*MainFormSLS->hh_1[150]
 + c2.v[78]*MainFormSLS->hh_1[122]
 + c2.v[79]*MainFormSLS->hh_1[94];
s/=N_2;
out.push_back(s);
//������ 67
s =c2.v[0]*MainFormSLS->hh_1[67]
 + c2.v[1]*MainFormSLS->hh_1[41]
 + c2.v[2]*MainFormSLS->hh_1[15]
 + c2.v[3]*MainFormSLS->hh_1[149]
 + c2.v[4]*MainFormSLS->hh_1[123]
 + c2.v[5]*MainFormSLS->hh_1[97]
 + c2.v[6]*MainFormSLS->hh_1[71]
 + c2.v[7]*MainFormSLS->hh_1[45]
 + c2.v[8]*MainFormSLS->hh_1[19]
 + c2.v[9]*MainFormSLS->hh_1[153]
 + c2.v[10]*MainFormSLS->hh_1[127]
 + c2.v[11]*MainFormSLS->hh_1[101]
 + c2.v[12]*MainFormSLS->hh_1[75]
 + c2.v[13]*MainFormSLS->hh_1[49]
 + c2.v[14]*MainFormSLS->hh_1[23]
 + c2.v[15]*MainFormSLS->hh_1[157]
 + c2.v[16]*MainFormSLS->hh_1[131]
 + c2.v[17]*MainFormSLS->hh_1[105]
 + c2.v[18]*MainFormSLS->hh_1[79]
 + c2.v[19]*MainFormSLS->hh_1[53]
 + c2.v[20]*MainFormSLS->hh_1[27]
 + c2.v[21]*MainFormSLS->hh_1[1]
 + c2.v[22]*MainFormSLS->hh_1[135]
 + c2.v[23]*MainFormSLS->hh_1[109]
 + c2.v[24]*MainFormSLS->hh_1[83]
 + c2.v[25]*MainFormSLS->hh_1[57]
 + c2.v[26]*MainFormSLS->hh_1[31]
 + c2.v[27]*MainFormSLS->hh_1[5]
 + c2.v[28]*MainFormSLS->hh_1[139]
 + c2.v[29]*MainFormSLS->hh_1[113]
 + c2.v[30]*MainFormSLS->hh_1[87]
 + c2.v[31]*MainFormSLS->hh_1[61]
 + c2.v[32]*MainFormSLS->hh_1[35]
 + c2.v[33]*MainFormSLS->hh_1[9]
 + c2.v[34]*MainFormSLS->hh_1[143]
 + c2.v[35]*MainFormSLS->hh_1[117]
 + c2.v[36]*MainFormSLS->hh_1[91]
 + c2.v[37]*MainFormSLS->hh_1[65]
 + c2.v[38]*MainFormSLS->hh_1[39]
 + c2.v[39]*MainFormSLS->hh_1[13]
 + c2.v[40]*MainFormSLS->hh_1[147]
 + c2.v[41]*MainFormSLS->hh_1[121]
 + c2.v[42]*MainFormSLS->hh_1[95]
 + c2.v[43]*MainFormSLS->hh_1[69]
 + c2.v[44]*MainFormSLS->hh_1[43]
 + c2.v[45]*MainFormSLS->hh_1[17]
 + c2.v[46]*MainFormSLS->hh_1[151]
 + c2.v[47]*MainFormSLS->hh_1[125]
 + c2.v[48]*MainFormSLS->hh_1[99]
 + c2.v[49]*MainFormSLS->hh_1[73]
 + c2.v[50]*MainFormSLS->hh_1[47]
 + c2.v[51]*MainFormSLS->hh_1[21]
 + c2.v[52]*MainFormSLS->hh_1[155]
 + c2.v[53]*MainFormSLS->hh_1[129]
 + c2.v[54]*MainFormSLS->hh_1[103]
 + c2.v[55]*MainFormSLS->hh_1[77]
 + c2.v[56]*MainFormSLS->hh_1[51]
 + c2.v[57]*MainFormSLS->hh_1[25]
 + c2.v[58]*MainFormSLS->hh_1[159]
 + c2.v[59]*MainFormSLS->hh_1[133]
 + c2.v[60]*MainFormSLS->hh_1[107]
 + c2.v[61]*MainFormSLS->hh_1[81]
 + c2.v[62]*MainFormSLS->hh_1[55]
 + c2.v[63]*MainFormSLS->hh_1[29]
 + c2.v[64]*MainFormSLS->hh_1[3]
 + c2.v[65]*MainFormSLS->hh_1[137]
 + c2.v[66]*MainFormSLS->hh_1[111]
 + c2.v[67]*MainFormSLS->hh_1[85]
 + c2.v[68]*MainFormSLS->hh_1[59]
 + c2.v[69]*MainFormSLS->hh_1[33]
 + c2.v[70]*MainFormSLS->hh_1[7]
 + c2.v[71]*MainFormSLS->hh_1[141]
 + c2.v[72]*MainFormSLS->hh_1[115]
 + c2.v[73]*MainFormSLS->hh_1[89]
 + c2.v[74]*MainFormSLS->hh_1[63]
 + c2.v[75]*MainFormSLS->hh_1[37]
 + c2.v[76]*MainFormSLS->hh_1[11]
 + c2.v[77]*MainFormSLS->hh_1[145]
 + c2.v[78]*MainFormSLS->hh_1[119]
 + c2.v[79]*MainFormSLS->hh_1[93];
s/=N_2;
out.push_back(s);
//������ 68
s =c2.v[0]*MainFormSLS->hh_1[68]
 + c2.v[1]*MainFormSLS->hh_1[44]
 + c2.v[2]*MainFormSLS->hh_1[20]
 + c2.v[3]*MainFormSLS->hh_1[156]
 + c2.v[4]*MainFormSLS->hh_1[132]
 + c2.v[5]*MainFormSLS->hh_1[108]
 + c2.v[6]*MainFormSLS->hh_1[84]
 + c2.v[7]*MainFormSLS->hh_1[60]
 + c2.v[8]*MainFormSLS->hh_1[36]
 + c2.v[9]*MainFormSLS->hh_1[12]
 + c2.v[10]*MainFormSLS->hh_1[148]
 + c2.v[11]*MainFormSLS->hh_1[124]
 + c2.v[12]*MainFormSLS->hh_1[100]
 + c2.v[13]*MainFormSLS->hh_1[76]
 + c2.v[14]*MainFormSLS->hh_1[52]
 + c2.v[15]*MainFormSLS->hh_1[28]
 + c2.v[16]*MainFormSLS->hh_1[4]
 + c2.v[17]*MainFormSLS->hh_1[140]
 + c2.v[18]*MainFormSLS->hh_1[116]
 + c2.v[19]*MainFormSLS->hh_1[92]
 + c2.v[20]*MainFormSLS->hh_1[68]
 + c2.v[21]*MainFormSLS->hh_1[44]
 + c2.v[22]*MainFormSLS->hh_1[20]
 + c2.v[23]*MainFormSLS->hh_1[156]
 + c2.v[24]*MainFormSLS->hh_1[132]
 + c2.v[25]*MainFormSLS->hh_1[108]
 + c2.v[26]*MainFormSLS->hh_1[84]
 + c2.v[27]*MainFormSLS->hh_1[60]
 + c2.v[28]*MainFormSLS->hh_1[36]
 + c2.v[29]*MainFormSLS->hh_1[12]
 + c2.v[30]*MainFormSLS->hh_1[148]
 + c2.v[31]*MainFormSLS->hh_1[124]
 + c2.v[32]*MainFormSLS->hh_1[100]
 + c2.v[33]*MainFormSLS->hh_1[76]
 + c2.v[34]*MainFormSLS->hh_1[52]
 + c2.v[35]*MainFormSLS->hh_1[28]
 + c2.v[36]*MainFormSLS->hh_1[4]
 + c2.v[37]*MainFormSLS->hh_1[140]
 + c2.v[38]*MainFormSLS->hh_1[116]
 + c2.v[39]*MainFormSLS->hh_1[92]
 + c2.v[40]*MainFormSLS->hh_1[68]
 + c2.v[41]*MainFormSLS->hh_1[44]
 + c2.v[42]*MainFormSLS->hh_1[20]
 + c2.v[43]*MainFormSLS->hh_1[156]
 + c2.v[44]*MainFormSLS->hh_1[132]
 + c2.v[45]*MainFormSLS->hh_1[108]
 + c2.v[46]*MainFormSLS->hh_1[84]
 + c2.v[47]*MainFormSLS->hh_1[60]
 + c2.v[48]*MainFormSLS->hh_1[36]
 + c2.v[49]*MainFormSLS->hh_1[12]
 + c2.v[50]*MainFormSLS->hh_1[148]
 + c2.v[51]*MainFormSLS->hh_1[124]
 + c2.v[52]*MainFormSLS->hh_1[100]
 + c2.v[53]*MainFormSLS->hh_1[76]
 + c2.v[54]*MainFormSLS->hh_1[52]
 + c2.v[55]*MainFormSLS->hh_1[28]
 + c2.v[56]*MainFormSLS->hh_1[4]
 + c2.v[57]*MainFormSLS->hh_1[140]
 + c2.v[58]*MainFormSLS->hh_1[116]
 + c2.v[59]*MainFormSLS->hh_1[92]
 + c2.v[60]*MainFormSLS->hh_1[68]
 + c2.v[61]*MainFormSLS->hh_1[44]
 + c2.v[62]*MainFormSLS->hh_1[20]
 + c2.v[63]*MainFormSLS->hh_1[156]
 + c2.v[64]*MainFormSLS->hh_1[132]
 + c2.v[65]*MainFormSLS->hh_1[108]
 + c2.v[66]*MainFormSLS->hh_1[84]
 + c2.v[67]*MainFormSLS->hh_1[60]
 + c2.v[68]*MainFormSLS->hh_1[36]
 + c2.v[69]*MainFormSLS->hh_1[12]
 + c2.v[70]*MainFormSLS->hh_1[148]
 + c2.v[71]*MainFormSLS->hh_1[124]
 + c2.v[72]*MainFormSLS->hh_1[100]
 + c2.v[73]*MainFormSLS->hh_1[76]
 + c2.v[74]*MainFormSLS->hh_1[52]
 + c2.v[75]*MainFormSLS->hh_1[28]
 + c2.v[76]*MainFormSLS->hh_1[4]
 + c2.v[77]*MainFormSLS->hh_1[140]
 + c2.v[78]*MainFormSLS->hh_1[116]
 + c2.v[79]*MainFormSLS->hh_1[92];
s/=N_2;
out.push_back(s);
//������ 69
s =c2.v[0]*MainFormSLS->hh_1[69]
 + c2.v[1]*MainFormSLS->hh_1[47]
 + c2.v[2]*MainFormSLS->hh_1[25]
 + c2.v[3]*MainFormSLS->hh_1[3]
 + c2.v[4]*MainFormSLS->hh_1[141]
 + c2.v[5]*MainFormSLS->hh_1[119]
 + c2.v[6]*MainFormSLS->hh_1[97]
 + c2.v[7]*MainFormSLS->hh_1[75]
 + c2.v[8]*MainFormSLS->hh_1[53]
 + c2.v[9]*MainFormSLS->hh_1[31]
 + c2.v[10]*MainFormSLS->hh_1[9]
 + c2.v[11]*MainFormSLS->hh_1[147]
 + c2.v[12]*MainFormSLS->hh_1[125]
 + c2.v[13]*MainFormSLS->hh_1[103]
 + c2.v[14]*MainFormSLS->hh_1[81]
 + c2.v[15]*MainFormSLS->hh_1[59]
 + c2.v[16]*MainFormSLS->hh_1[37]
 + c2.v[17]*MainFormSLS->hh_1[15]
 + c2.v[18]*MainFormSLS->hh_1[153]
 + c2.v[19]*MainFormSLS->hh_1[131]
 + c2.v[20]*MainFormSLS->hh_1[109]
 + c2.v[21]*MainFormSLS->hh_1[87]
 + c2.v[22]*MainFormSLS->hh_1[65]
 + c2.v[23]*MainFormSLS->hh_1[43]
 + c2.v[24]*MainFormSLS->hh_1[21]
 + c2.v[25]*MainFormSLS->hh_1[159]
 + c2.v[26]*MainFormSLS->hh_1[137]
 + c2.v[27]*MainFormSLS->hh_1[115]
 + c2.v[28]*MainFormSLS->hh_1[93]
 + c2.v[29]*MainFormSLS->hh_1[71]
 + c2.v[30]*MainFormSLS->hh_1[49]
 + c2.v[31]*MainFormSLS->hh_1[27]
 + c2.v[32]*MainFormSLS->hh_1[5]
 + c2.v[33]*MainFormSLS->hh_1[143]
 + c2.v[34]*MainFormSLS->hh_1[121]
 + c2.v[35]*MainFormSLS->hh_1[99]
 + c2.v[36]*MainFormSLS->hh_1[77]
 + c2.v[37]*MainFormSLS->hh_1[55]
 + c2.v[38]*MainFormSLS->hh_1[33]
 + c2.v[39]*MainFormSLS->hh_1[11]
 + c2.v[40]*MainFormSLS->hh_1[149]
 + c2.v[41]*MainFormSLS->hh_1[127]
 + c2.v[42]*MainFormSLS->hh_1[105]
 + c2.v[43]*MainFormSLS->hh_1[83]
 + c2.v[44]*MainFormSLS->hh_1[61]
 + c2.v[45]*MainFormSLS->hh_1[39]
 + c2.v[46]*MainFormSLS->hh_1[17]
 + c2.v[47]*MainFormSLS->hh_1[155]
 + c2.v[48]*MainFormSLS->hh_1[133]
 + c2.v[49]*MainFormSLS->hh_1[111]
 + c2.v[50]*MainFormSLS->hh_1[89]
 + c2.v[51]*MainFormSLS->hh_1[67]
 + c2.v[52]*MainFormSLS->hh_1[45]
 + c2.v[53]*MainFormSLS->hh_1[23]
 + c2.v[54]*MainFormSLS->hh_1[1]
 + c2.v[55]*MainFormSLS->hh_1[139]
 + c2.v[56]*MainFormSLS->hh_1[117]
 + c2.v[57]*MainFormSLS->hh_1[95]
 + c2.v[58]*MainFormSLS->hh_1[73]
 + c2.v[59]*MainFormSLS->hh_1[51]
 + c2.v[60]*MainFormSLS->hh_1[29]
 + c2.v[61]*MainFormSLS->hh_1[7]
 + c2.v[62]*MainFormSLS->hh_1[145]
 + c2.v[63]*MainFormSLS->hh_1[123]
 + c2.v[64]*MainFormSLS->hh_1[101]
 + c2.v[65]*MainFormSLS->hh_1[79]
 + c2.v[66]*MainFormSLS->hh_1[57]
 + c2.v[67]*MainFormSLS->hh_1[35]
 + c2.v[68]*MainFormSLS->hh_1[13]
 + c2.v[69]*MainFormSLS->hh_1[151]
 + c2.v[70]*MainFormSLS->hh_1[129]
 + c2.v[71]*MainFormSLS->hh_1[107]
 + c2.v[72]*MainFormSLS->hh_1[85]
 + c2.v[73]*MainFormSLS->hh_1[63]
 + c2.v[74]*MainFormSLS->hh_1[41]
 + c2.v[75]*MainFormSLS->hh_1[19]
 + c2.v[76]*MainFormSLS->hh_1[157]
 + c2.v[77]*MainFormSLS->hh_1[135]
 + c2.v[78]*MainFormSLS->hh_1[113]
 + c2.v[79]*MainFormSLS->hh_1[91];
s/=N_2;
out.push_back(s);
//������ 70
s =c2.v[0]*MainFormSLS->hh_1[70]
 + c2.v[1]*MainFormSLS->hh_1[50]
 + c2.v[2]*MainFormSLS->hh_1[30]
 + c2.v[3]*MainFormSLS->hh_1[10]
 + c2.v[4]*MainFormSLS->hh_1[150]
 + c2.v[5]*MainFormSLS->hh_1[130]
 + c2.v[6]*MainFormSLS->hh_1[110]
 + c2.v[7]*MainFormSLS->hh_1[90]
 + c2.v[8]*MainFormSLS->hh_1[70]
 + c2.v[9]*MainFormSLS->hh_1[50]
 + c2.v[10]*MainFormSLS->hh_1[30]
 + c2.v[11]*MainFormSLS->hh_1[10]
 + c2.v[12]*MainFormSLS->hh_1[150]
 + c2.v[13]*MainFormSLS->hh_1[130]
 + c2.v[14]*MainFormSLS->hh_1[110]
 + c2.v[15]*MainFormSLS->hh_1[90]
 + c2.v[16]*MainFormSLS->hh_1[70]
 + c2.v[17]*MainFormSLS->hh_1[50]
 + c2.v[18]*MainFormSLS->hh_1[30]
 + c2.v[19]*MainFormSLS->hh_1[10]
 + c2.v[20]*MainFormSLS->hh_1[150]
 + c2.v[21]*MainFormSLS->hh_1[130]
 + c2.v[22]*MainFormSLS->hh_1[110]
 + c2.v[23]*MainFormSLS->hh_1[90]
 + c2.v[24]*MainFormSLS->hh_1[70]
 + c2.v[25]*MainFormSLS->hh_1[50]
 + c2.v[26]*MainFormSLS->hh_1[30]
 + c2.v[27]*MainFormSLS->hh_1[10]
 + c2.v[28]*MainFormSLS->hh_1[150]
 + c2.v[29]*MainFormSLS->hh_1[130]
 + c2.v[30]*MainFormSLS->hh_1[110]
 + c2.v[31]*MainFormSLS->hh_1[90]
 + c2.v[32]*MainFormSLS->hh_1[70]
 + c2.v[33]*MainFormSLS->hh_1[50]
 + c2.v[34]*MainFormSLS->hh_1[30]
 + c2.v[35]*MainFormSLS->hh_1[10]
 + c2.v[36]*MainFormSLS->hh_1[150]
 + c2.v[37]*MainFormSLS->hh_1[130]
 + c2.v[38]*MainFormSLS->hh_1[110]
 + c2.v[39]*MainFormSLS->hh_1[90]
 + c2.v[40]*MainFormSLS->hh_1[70]
 + c2.v[41]*MainFormSLS->hh_1[50]
 + c2.v[42]*MainFormSLS->hh_1[30]
 + c2.v[43]*MainFormSLS->hh_1[10]
 + c2.v[44]*MainFormSLS->hh_1[150]
 + c2.v[45]*MainFormSLS->hh_1[130]
 + c2.v[46]*MainFormSLS->hh_1[110]
 + c2.v[47]*MainFormSLS->hh_1[90]
 + c2.v[48]*MainFormSLS->hh_1[70]
 + c2.v[49]*MainFormSLS->hh_1[50]
 + c2.v[50]*MainFormSLS->hh_1[30]
 + c2.v[51]*MainFormSLS->hh_1[10]
 + c2.v[52]*MainFormSLS->hh_1[150]
 + c2.v[53]*MainFormSLS->hh_1[130]
 + c2.v[54]*MainFormSLS->hh_1[110]
 + c2.v[55]*MainFormSLS->hh_1[90]
 + c2.v[56]*MainFormSLS->hh_1[70]
 + c2.v[57]*MainFormSLS->hh_1[50]
 + c2.v[58]*MainFormSLS->hh_1[30]
 + c2.v[59]*MainFormSLS->hh_1[10]
 + c2.v[60]*MainFormSLS->hh_1[150]
 + c2.v[61]*MainFormSLS->hh_1[130]
 + c2.v[62]*MainFormSLS->hh_1[110]
 + c2.v[63]*MainFormSLS->hh_1[90]
 + c2.v[64]*MainFormSLS->hh_1[70]
 + c2.v[65]*MainFormSLS->hh_1[50]
 + c2.v[66]*MainFormSLS->hh_1[30]
 + c2.v[67]*MainFormSLS->hh_1[10]
 + c2.v[68]*MainFormSLS->hh_1[150]
 + c2.v[69]*MainFormSLS->hh_1[130]
 + c2.v[70]*MainFormSLS->hh_1[110]
 + c2.v[71]*MainFormSLS->hh_1[90]
 + c2.v[72]*MainFormSLS->hh_1[70]
 + c2.v[73]*MainFormSLS->hh_1[50]
 + c2.v[74]*MainFormSLS->hh_1[30]
 + c2.v[75]*MainFormSLS->hh_1[10]
 + c2.v[76]*MainFormSLS->hh_1[150]
 + c2.v[77]*MainFormSLS->hh_1[130]
 + c2.v[78]*MainFormSLS->hh_1[110]
 + c2.v[79]*MainFormSLS->hh_1[90];
s/=N_2;
out.push_back(s);
//������ 71
s =c2.v[0]*MainFormSLS->hh_1[71]
 + c2.v[1]*MainFormSLS->hh_1[53]
 + c2.v[2]*MainFormSLS->hh_1[35]
 + c2.v[3]*MainFormSLS->hh_1[17]
 + c2.v[4]*MainFormSLS->hh_1[159]
 + c2.v[5]*MainFormSLS->hh_1[141]
 + c2.v[6]*MainFormSLS->hh_1[123]
 + c2.v[7]*MainFormSLS->hh_1[105]
 + c2.v[8]*MainFormSLS->hh_1[87]
 + c2.v[9]*MainFormSLS->hh_1[69]
 + c2.v[10]*MainFormSLS->hh_1[51]
 + c2.v[11]*MainFormSLS->hh_1[33]
 + c2.v[12]*MainFormSLS->hh_1[15]
 + c2.v[13]*MainFormSLS->hh_1[157]
 + c2.v[14]*MainFormSLS->hh_1[139]
 + c2.v[15]*MainFormSLS->hh_1[121]
 + c2.v[16]*MainFormSLS->hh_1[103]
 + c2.v[17]*MainFormSLS->hh_1[85]
 + c2.v[18]*MainFormSLS->hh_1[67]
 + c2.v[19]*MainFormSLS->hh_1[49]
 + c2.v[20]*MainFormSLS->hh_1[31]
 + c2.v[21]*MainFormSLS->hh_1[13]
 + c2.v[22]*MainFormSLS->hh_1[155]
 + c2.v[23]*MainFormSLS->hh_1[137]
 + c2.v[24]*MainFormSLS->hh_1[119]
 + c2.v[25]*MainFormSLS->hh_1[101]
 + c2.v[26]*MainFormSLS->hh_1[83]
 + c2.v[27]*MainFormSLS->hh_1[65]
 + c2.v[28]*MainFormSLS->hh_1[47]
 + c2.v[29]*MainFormSLS->hh_1[29]
 + c2.v[30]*MainFormSLS->hh_1[11]
 + c2.v[31]*MainFormSLS->hh_1[153]
 + c2.v[32]*MainFormSLS->hh_1[135]
 + c2.v[33]*MainFormSLS->hh_1[117]
 + c2.v[34]*MainFormSLS->hh_1[99]
 + c2.v[35]*MainFormSLS->hh_1[81]
 + c2.v[36]*MainFormSLS->hh_1[63]
 + c2.v[37]*MainFormSLS->hh_1[45]
 + c2.v[38]*MainFormSLS->hh_1[27]
 + c2.v[39]*MainFormSLS->hh_1[9]
 + c2.v[40]*MainFormSLS->hh_1[151]
 + c2.v[41]*MainFormSLS->hh_1[133]
 + c2.v[42]*MainFormSLS->hh_1[115]
 + c2.v[43]*MainFormSLS->hh_1[97]
 + c2.v[44]*MainFormSLS->hh_1[79]
 + c2.v[45]*MainFormSLS->hh_1[61]
 + c2.v[46]*MainFormSLS->hh_1[43]
 + c2.v[47]*MainFormSLS->hh_1[25]
 + c2.v[48]*MainFormSLS->hh_1[7]
 + c2.v[49]*MainFormSLS->hh_1[149]
 + c2.v[50]*MainFormSLS->hh_1[131]
 + c2.v[51]*MainFormSLS->hh_1[113]
 + c2.v[52]*MainFormSLS->hh_1[95]
 + c2.v[53]*MainFormSLS->hh_1[77]
 + c2.v[54]*MainFormSLS->hh_1[59]
 + c2.v[55]*MainFormSLS->hh_1[41]
 + c2.v[56]*MainFormSLS->hh_1[23]
 + c2.v[57]*MainFormSLS->hh_1[5]
 + c2.v[58]*MainFormSLS->hh_1[147]
 + c2.v[59]*MainFormSLS->hh_1[129]
 + c2.v[60]*MainFormSLS->hh_1[111]
 + c2.v[61]*MainFormSLS->hh_1[93]
 + c2.v[62]*MainFormSLS->hh_1[75]
 + c2.v[63]*MainFormSLS->hh_1[57]
 + c2.v[64]*MainFormSLS->hh_1[39]
 + c2.v[65]*MainFormSLS->hh_1[21]
 + c2.v[66]*MainFormSLS->hh_1[3]
 + c2.v[67]*MainFormSLS->hh_1[145]
 + c2.v[68]*MainFormSLS->hh_1[127]
 + c2.v[69]*MainFormSLS->hh_1[109]
 + c2.v[70]*MainFormSLS->hh_1[91]
 + c2.v[71]*MainFormSLS->hh_1[73]
 + c2.v[72]*MainFormSLS->hh_1[55]
 + c2.v[73]*MainFormSLS->hh_1[37]
 + c2.v[74]*MainFormSLS->hh_1[19]
 + c2.v[75]*MainFormSLS->hh_1[1]
 + c2.v[76]*MainFormSLS->hh_1[143]
 + c2.v[77]*MainFormSLS->hh_1[125]
 + c2.v[78]*MainFormSLS->hh_1[107]
 + c2.v[79]*MainFormSLS->hh_1[89];
s/=N_2;
out.push_back(s);
//������ 72
s =c2.v[0]*MainFormSLS->hh_1[72]
 + c2.v[1]*MainFormSLS->hh_1[56]
 + c2.v[2]*MainFormSLS->hh_1[40]
 + c2.v[3]*MainFormSLS->hh_1[24]
 + c2.v[4]*MainFormSLS->hh_1[8]
 + c2.v[5]*MainFormSLS->hh_1[152]
 + c2.v[6]*MainFormSLS->hh_1[136]
 + c2.v[7]*MainFormSLS->hh_1[120]
 + c2.v[8]*MainFormSLS->hh_1[104]
 + c2.v[9]*MainFormSLS->hh_1[88]
 + c2.v[10]*MainFormSLS->hh_1[72]
 + c2.v[11]*MainFormSLS->hh_1[56]
 + c2.v[12]*MainFormSLS->hh_1[40]
 + c2.v[13]*MainFormSLS->hh_1[24]
 + c2.v[14]*MainFormSLS->hh_1[8]
 + c2.v[15]*MainFormSLS->hh_1[152]
 + c2.v[16]*MainFormSLS->hh_1[136]
 + c2.v[17]*MainFormSLS->hh_1[120]
 + c2.v[18]*MainFormSLS->hh_1[104]
 + c2.v[19]*MainFormSLS->hh_1[88]
 + c2.v[20]*MainFormSLS->hh_1[72]
 + c2.v[21]*MainFormSLS->hh_1[56]
 + c2.v[22]*MainFormSLS->hh_1[40]
 + c2.v[23]*MainFormSLS->hh_1[24]
 + c2.v[24]*MainFormSLS->hh_1[8]
 + c2.v[25]*MainFormSLS->hh_1[152]
 + c2.v[26]*MainFormSLS->hh_1[136]
 + c2.v[27]*MainFormSLS->hh_1[120]
 + c2.v[28]*MainFormSLS->hh_1[104]
 + c2.v[29]*MainFormSLS->hh_1[88]
 + c2.v[30]*MainFormSLS->hh_1[72]
 + c2.v[31]*MainFormSLS->hh_1[56]
 + c2.v[32]*MainFormSLS->hh_1[40]
 + c2.v[33]*MainFormSLS->hh_1[24]
 + c2.v[34]*MainFormSLS->hh_1[8]
 + c2.v[35]*MainFormSLS->hh_1[152]
 + c2.v[36]*MainFormSLS->hh_1[136]
 + c2.v[37]*MainFormSLS->hh_1[120]
 + c2.v[38]*MainFormSLS->hh_1[104]
 + c2.v[39]*MainFormSLS->hh_1[88]
 + c2.v[40]*MainFormSLS->hh_1[72]
 + c2.v[41]*MainFormSLS->hh_1[56]
 + c2.v[42]*MainFormSLS->hh_1[40]
 + c2.v[43]*MainFormSLS->hh_1[24]
 + c2.v[44]*MainFormSLS->hh_1[8]
 + c2.v[45]*MainFormSLS->hh_1[152]
 + c2.v[46]*MainFormSLS->hh_1[136]
 + c2.v[47]*MainFormSLS->hh_1[120]
 + c2.v[48]*MainFormSLS->hh_1[104]
 + c2.v[49]*MainFormSLS->hh_1[88]
 + c2.v[50]*MainFormSLS->hh_1[72]
 + c2.v[51]*MainFormSLS->hh_1[56]
 + c2.v[52]*MainFormSLS->hh_1[40]
 + c2.v[53]*MainFormSLS->hh_1[24]
 + c2.v[54]*MainFormSLS->hh_1[8]
 + c2.v[55]*MainFormSLS->hh_1[152]
 + c2.v[56]*MainFormSLS->hh_1[136]
 + c2.v[57]*MainFormSLS->hh_1[120]
 + c2.v[58]*MainFormSLS->hh_1[104]
 + c2.v[59]*MainFormSLS->hh_1[88]
 + c2.v[60]*MainFormSLS->hh_1[72]
 + c2.v[61]*MainFormSLS->hh_1[56]
 + c2.v[62]*MainFormSLS->hh_1[40]
 + c2.v[63]*MainFormSLS->hh_1[24]
 + c2.v[64]*MainFormSLS->hh_1[8]
 + c2.v[65]*MainFormSLS->hh_1[152]
 + c2.v[66]*MainFormSLS->hh_1[136]
 + c2.v[67]*MainFormSLS->hh_1[120]
 + c2.v[68]*MainFormSLS->hh_1[104]
 + c2.v[69]*MainFormSLS->hh_1[88]
 + c2.v[70]*MainFormSLS->hh_1[72]
 + c2.v[71]*MainFormSLS->hh_1[56]
 + c2.v[72]*MainFormSLS->hh_1[40]
 + c2.v[73]*MainFormSLS->hh_1[24]
 + c2.v[74]*MainFormSLS->hh_1[8]
 + c2.v[75]*MainFormSLS->hh_1[152]
 + c2.v[76]*MainFormSLS->hh_1[136]
 + c2.v[77]*MainFormSLS->hh_1[120]
 + c2.v[78]*MainFormSLS->hh_1[104]
 + c2.v[79]*MainFormSLS->hh_1[88];
s/=N_2;
out.push_back(s);
//������ 73
s =c2.v[0]*MainFormSLS->hh_1[73]
 + c2.v[1]*MainFormSLS->hh_1[59]
 + c2.v[2]*MainFormSLS->hh_1[45]
 + c2.v[3]*MainFormSLS->hh_1[31]
 + c2.v[4]*MainFormSLS->hh_1[17]
 + c2.v[5]*MainFormSLS->hh_1[3]
 + c2.v[6]*MainFormSLS->hh_1[149]
 + c2.v[7]*MainFormSLS->hh_1[135]
 + c2.v[8]*MainFormSLS->hh_1[121]
 + c2.v[9]*MainFormSLS->hh_1[107]
 + c2.v[10]*MainFormSLS->hh_1[93]
 + c2.v[11]*MainFormSLS->hh_1[79]
 + c2.v[12]*MainFormSLS->hh_1[65]
 + c2.v[13]*MainFormSLS->hh_1[51]
 + c2.v[14]*MainFormSLS->hh_1[37]
 + c2.v[15]*MainFormSLS->hh_1[23]
 + c2.v[16]*MainFormSLS->hh_1[9]
 + c2.v[17]*MainFormSLS->hh_1[155]
 + c2.v[18]*MainFormSLS->hh_1[141]
 + c2.v[19]*MainFormSLS->hh_1[127]
 + c2.v[20]*MainFormSLS->hh_1[113]
 + c2.v[21]*MainFormSLS->hh_1[99]
 + c2.v[22]*MainFormSLS->hh_1[85]
 + c2.v[23]*MainFormSLS->hh_1[71]
 + c2.v[24]*MainFormSLS->hh_1[57]
 + c2.v[25]*MainFormSLS->hh_1[43]
 + c2.v[26]*MainFormSLS->hh_1[29]
 + c2.v[27]*MainFormSLS->hh_1[15]
 + c2.v[28]*MainFormSLS->hh_1[1]
 + c2.v[29]*MainFormSLS->hh_1[147]
 + c2.v[30]*MainFormSLS->hh_1[133]
 + c2.v[31]*MainFormSLS->hh_1[119]
 + c2.v[32]*MainFormSLS->hh_1[105]
 + c2.v[33]*MainFormSLS->hh_1[91]
 + c2.v[34]*MainFormSLS->hh_1[77]
 + c2.v[35]*MainFormSLS->hh_1[63]
 + c2.v[36]*MainFormSLS->hh_1[49]
 + c2.v[37]*MainFormSLS->hh_1[35]
 + c2.v[38]*MainFormSLS->hh_1[21]
 + c2.v[39]*MainFormSLS->hh_1[7]
 + c2.v[40]*MainFormSLS->hh_1[153]
 + c2.v[41]*MainFormSLS->hh_1[139]
 + c2.v[42]*MainFormSLS->hh_1[125]
 + c2.v[43]*MainFormSLS->hh_1[111]
 + c2.v[44]*MainFormSLS->hh_1[97]
 + c2.v[45]*MainFormSLS->hh_1[83]
 + c2.v[46]*MainFormSLS->hh_1[69]
 + c2.v[47]*MainFormSLS->hh_1[55]
 + c2.v[48]*MainFormSLS->hh_1[41]
 + c2.v[49]*MainFormSLS->hh_1[27]
 + c2.v[50]*MainFormSLS->hh_1[13]
 + c2.v[51]*MainFormSLS->hh_1[159]
 + c2.v[52]*MainFormSLS->hh_1[145]
 + c2.v[53]*MainFormSLS->hh_1[131]
 + c2.v[54]*MainFormSLS->hh_1[117]
 + c2.v[55]*MainFormSLS->hh_1[103]
 + c2.v[56]*MainFormSLS->hh_1[89]
 + c2.v[57]*MainFormSLS->hh_1[75]
 + c2.v[58]*MainFormSLS->hh_1[61]
 + c2.v[59]*MainFormSLS->hh_1[47]
 + c2.v[60]*MainFormSLS->hh_1[33]
 + c2.v[61]*MainFormSLS->hh_1[19]
 + c2.v[62]*MainFormSLS->hh_1[5]
 + c2.v[63]*MainFormSLS->hh_1[151]
 + c2.v[64]*MainFormSLS->hh_1[137]
 + c2.v[65]*MainFormSLS->hh_1[123]
 + c2.v[66]*MainFormSLS->hh_1[109]
 + c2.v[67]*MainFormSLS->hh_1[95]
 + c2.v[68]*MainFormSLS->hh_1[81]
 + c2.v[69]*MainFormSLS->hh_1[67]
 + c2.v[70]*MainFormSLS->hh_1[53]
 + c2.v[71]*MainFormSLS->hh_1[39]
 + c2.v[72]*MainFormSLS->hh_1[25]
 + c2.v[73]*MainFormSLS->hh_1[11]
 + c2.v[74]*MainFormSLS->hh_1[157]
 + c2.v[75]*MainFormSLS->hh_1[143]
 + c2.v[76]*MainFormSLS->hh_1[129]
 + c2.v[77]*MainFormSLS->hh_1[115]
 + c2.v[78]*MainFormSLS->hh_1[101]
 + c2.v[79]*MainFormSLS->hh_1[87];
s/=N_2;
out.push_back(s);
//������ 74
s =c2.v[0]*MainFormSLS->hh_1[74]
 + c2.v[1]*MainFormSLS->hh_1[62]
 + c2.v[2]*MainFormSLS->hh_1[50]
 + c2.v[3]*MainFormSLS->hh_1[38]
 + c2.v[4]*MainFormSLS->hh_1[26]
 + c2.v[5]*MainFormSLS->hh_1[14]
 + c2.v[6]*MainFormSLS->hh_1[2]
 + c2.v[7]*MainFormSLS->hh_1[150]
 + c2.v[8]*MainFormSLS->hh_1[138]
 + c2.v[9]*MainFormSLS->hh_1[126]
 + c2.v[10]*MainFormSLS->hh_1[114]
 + c2.v[11]*MainFormSLS->hh_1[102]
 + c2.v[12]*MainFormSLS->hh_1[90]
 + c2.v[13]*MainFormSLS->hh_1[78]
 + c2.v[14]*MainFormSLS->hh_1[66]
 + c2.v[15]*MainFormSLS->hh_1[54]
 + c2.v[16]*MainFormSLS->hh_1[42]
 + c2.v[17]*MainFormSLS->hh_1[30]
 + c2.v[18]*MainFormSLS->hh_1[18]
 + c2.v[19]*MainFormSLS->hh_1[6]
 + c2.v[20]*MainFormSLS->hh_1[154]
 + c2.v[21]*MainFormSLS->hh_1[142]
 + c2.v[22]*MainFormSLS->hh_1[130]
 + c2.v[23]*MainFormSLS->hh_1[118]
 + c2.v[24]*MainFormSLS->hh_1[106]
 + c2.v[25]*MainFormSLS->hh_1[94]
 + c2.v[26]*MainFormSLS->hh_1[82]
 + c2.v[27]*MainFormSLS->hh_1[70]
 + c2.v[28]*MainFormSLS->hh_1[58]
 + c2.v[29]*MainFormSLS->hh_1[46]
 + c2.v[30]*MainFormSLS->hh_1[34]
 + c2.v[31]*MainFormSLS->hh_1[22]
 + c2.v[32]*MainFormSLS->hh_1[10]
 + c2.v[33]*MainFormSLS->hh_1[158]
 + c2.v[34]*MainFormSLS->hh_1[146]
 + c2.v[35]*MainFormSLS->hh_1[134]
 + c2.v[36]*MainFormSLS->hh_1[122]
 + c2.v[37]*MainFormSLS->hh_1[110]
 + c2.v[38]*MainFormSLS->hh_1[98]
 + c2.v[39]*MainFormSLS->hh_1[86]
 + c2.v[40]*MainFormSLS->hh_1[74]
 + c2.v[41]*MainFormSLS->hh_1[62]
 + c2.v[42]*MainFormSLS->hh_1[50]
 + c2.v[43]*MainFormSLS->hh_1[38]
 + c2.v[44]*MainFormSLS->hh_1[26]
 + c2.v[45]*MainFormSLS->hh_1[14]
 + c2.v[46]*MainFormSLS->hh_1[2]
 + c2.v[47]*MainFormSLS->hh_1[150]
 + c2.v[48]*MainFormSLS->hh_1[138]
 + c2.v[49]*MainFormSLS->hh_1[126]
 + c2.v[50]*MainFormSLS->hh_1[114]
 + c2.v[51]*MainFormSLS->hh_1[102]
 + c2.v[52]*MainFormSLS->hh_1[90]
 + c2.v[53]*MainFormSLS->hh_1[78]
 + c2.v[54]*MainFormSLS->hh_1[66]
 + c2.v[55]*MainFormSLS->hh_1[54]
 + c2.v[56]*MainFormSLS->hh_1[42]
 + c2.v[57]*MainFormSLS->hh_1[30]
 + c2.v[58]*MainFormSLS->hh_1[18]
 + c2.v[59]*MainFormSLS->hh_1[6]
 + c2.v[60]*MainFormSLS->hh_1[154]
 + c2.v[61]*MainFormSLS->hh_1[142]
 + c2.v[62]*MainFormSLS->hh_1[130]
 + c2.v[63]*MainFormSLS->hh_1[118]
 + c2.v[64]*MainFormSLS->hh_1[106]
 + c2.v[65]*MainFormSLS->hh_1[94]
 + c2.v[66]*MainFormSLS->hh_1[82]
 + c2.v[67]*MainFormSLS->hh_1[70]
 + c2.v[68]*MainFormSLS->hh_1[58]
 + c2.v[69]*MainFormSLS->hh_1[46]
 + c2.v[70]*MainFormSLS->hh_1[34]
 + c2.v[71]*MainFormSLS->hh_1[22]
 + c2.v[72]*MainFormSLS->hh_1[10]
 + c2.v[73]*MainFormSLS->hh_1[158]
 + c2.v[74]*MainFormSLS->hh_1[146]
 + c2.v[75]*MainFormSLS->hh_1[134]
 + c2.v[76]*MainFormSLS->hh_1[122]
 + c2.v[77]*MainFormSLS->hh_1[110]
 + c2.v[78]*MainFormSLS->hh_1[98]
 + c2.v[79]*MainFormSLS->hh_1[86];
s/=N_2;
out.push_back(s);
//������ 75
s =c2.v[0]*MainFormSLS->hh_1[75]
 + c2.v[1]*MainFormSLS->hh_1[65]
 + c2.v[2]*MainFormSLS->hh_1[55]
 + c2.v[3]*MainFormSLS->hh_1[45]
 + c2.v[4]*MainFormSLS->hh_1[35]
 + c2.v[5]*MainFormSLS->hh_1[25]
 + c2.v[6]*MainFormSLS->hh_1[15]
 + c2.v[7]*MainFormSLS->hh_1[5]
 + c2.v[8]*MainFormSLS->hh_1[155]
 + c2.v[9]*MainFormSLS->hh_1[145]
 + c2.v[10]*MainFormSLS->hh_1[135]
 + c2.v[11]*MainFormSLS->hh_1[125]
 + c2.v[12]*MainFormSLS->hh_1[115]
 + c2.v[13]*MainFormSLS->hh_1[105]
 + c2.v[14]*MainFormSLS->hh_1[95]
 + c2.v[15]*MainFormSLS->hh_1[85]
 + c2.v[16]*MainFormSLS->hh_1[75]
 + c2.v[17]*MainFormSLS->hh_1[65]
 + c2.v[18]*MainFormSLS->hh_1[55]
 + c2.v[19]*MainFormSLS->hh_1[45]
 + c2.v[20]*MainFormSLS->hh_1[35]
 + c2.v[21]*MainFormSLS->hh_1[25]
 + c2.v[22]*MainFormSLS->hh_1[15]
 + c2.v[23]*MainFormSLS->hh_1[5]
 + c2.v[24]*MainFormSLS->hh_1[155]
 + c2.v[25]*MainFormSLS->hh_1[145]
 + c2.v[26]*MainFormSLS->hh_1[135]
 + c2.v[27]*MainFormSLS->hh_1[125]
 + c2.v[28]*MainFormSLS->hh_1[115]
 + c2.v[29]*MainFormSLS->hh_1[105]
 + c2.v[30]*MainFormSLS->hh_1[95]
 + c2.v[31]*MainFormSLS->hh_1[85]
 + c2.v[32]*MainFormSLS->hh_1[75]
 + c2.v[33]*MainFormSLS->hh_1[65]
 + c2.v[34]*MainFormSLS->hh_1[55]
 + c2.v[35]*MainFormSLS->hh_1[45]
 + c2.v[36]*MainFormSLS->hh_1[35]
 + c2.v[37]*MainFormSLS->hh_1[25]
 + c2.v[38]*MainFormSLS->hh_1[15]
 + c2.v[39]*MainFormSLS->hh_1[5]
 + c2.v[40]*MainFormSLS->hh_1[155]
 + c2.v[41]*MainFormSLS->hh_1[145]
 + c2.v[42]*MainFormSLS->hh_1[135]
 + c2.v[43]*MainFormSLS->hh_1[125]
 + c2.v[44]*MainFormSLS->hh_1[115]
 + c2.v[45]*MainFormSLS->hh_1[105]
 + c2.v[46]*MainFormSLS->hh_1[95]
 + c2.v[47]*MainFormSLS->hh_1[85]
 + c2.v[48]*MainFormSLS->hh_1[75]
 + c2.v[49]*MainFormSLS->hh_1[65]
 + c2.v[50]*MainFormSLS->hh_1[55]
 + c2.v[51]*MainFormSLS->hh_1[45]
 + c2.v[52]*MainFormSLS->hh_1[35]
 + c2.v[53]*MainFormSLS->hh_1[25]
 + c2.v[54]*MainFormSLS->hh_1[15]
 + c2.v[55]*MainFormSLS->hh_1[5]
 + c2.v[56]*MainFormSLS->hh_1[155]
 + c2.v[57]*MainFormSLS->hh_1[145]
 + c2.v[58]*MainFormSLS->hh_1[135]
 + c2.v[59]*MainFormSLS->hh_1[125]
 + c2.v[60]*MainFormSLS->hh_1[115]
 + c2.v[61]*MainFormSLS->hh_1[105]
 + c2.v[62]*MainFormSLS->hh_1[95]
 + c2.v[63]*MainFormSLS->hh_1[85]
 + c2.v[64]*MainFormSLS->hh_1[75]
 + c2.v[65]*MainFormSLS->hh_1[65]
 + c2.v[66]*MainFormSLS->hh_1[55]
 + c2.v[67]*MainFormSLS->hh_1[45]
 + c2.v[68]*MainFormSLS->hh_1[35]
 + c2.v[69]*MainFormSLS->hh_1[25]
 + c2.v[70]*MainFormSLS->hh_1[15]
 + c2.v[71]*MainFormSLS->hh_1[5]
 + c2.v[72]*MainFormSLS->hh_1[155]
 + c2.v[73]*MainFormSLS->hh_1[145]
 + c2.v[74]*MainFormSLS->hh_1[135]
 + c2.v[75]*MainFormSLS->hh_1[125]
 + c2.v[76]*MainFormSLS->hh_1[115]
 + c2.v[77]*MainFormSLS->hh_1[105]
 + c2.v[78]*MainFormSLS->hh_1[95]
 + c2.v[79]*MainFormSLS->hh_1[85];
s/=N_2;
out.push_back(s);
//������ 76
s =c2.v[0]*MainFormSLS->hh_1[76]
 + c2.v[1]*MainFormSLS->hh_1[68]
 + c2.v[2]*MainFormSLS->hh_1[60]
 + c2.v[3]*MainFormSLS->hh_1[52]
 + c2.v[4]*MainFormSLS->hh_1[44]
 + c2.v[5]*MainFormSLS->hh_1[36]
 + c2.v[6]*MainFormSLS->hh_1[28]
 + c2.v[7]*MainFormSLS->hh_1[20]
 + c2.v[8]*MainFormSLS->hh_1[12]
 + c2.v[9]*MainFormSLS->hh_1[4]
 + c2.v[10]*MainFormSLS->hh_1[156]
 + c2.v[11]*MainFormSLS->hh_1[148]
 + c2.v[12]*MainFormSLS->hh_1[140]
 + c2.v[13]*MainFormSLS->hh_1[132]
 + c2.v[14]*MainFormSLS->hh_1[124]
 + c2.v[15]*MainFormSLS->hh_1[116]
 + c2.v[16]*MainFormSLS->hh_1[108]
 + c2.v[17]*MainFormSLS->hh_1[100]
 + c2.v[18]*MainFormSLS->hh_1[92]
 + c2.v[19]*MainFormSLS->hh_1[84]
 + c2.v[20]*MainFormSLS->hh_1[76]
 + c2.v[21]*MainFormSLS->hh_1[68]
 + c2.v[22]*MainFormSLS->hh_1[60]
 + c2.v[23]*MainFormSLS->hh_1[52]
 + c2.v[24]*MainFormSLS->hh_1[44]
 + c2.v[25]*MainFormSLS->hh_1[36]
 + c2.v[26]*MainFormSLS->hh_1[28]
 + c2.v[27]*MainFormSLS->hh_1[20]
 + c2.v[28]*MainFormSLS->hh_1[12]
 + c2.v[29]*MainFormSLS->hh_1[4]
 + c2.v[30]*MainFormSLS->hh_1[156]
 + c2.v[31]*MainFormSLS->hh_1[148]
 + c2.v[32]*MainFormSLS->hh_1[140]
 + c2.v[33]*MainFormSLS->hh_1[132]
 + c2.v[34]*MainFormSLS->hh_1[124]
 + c2.v[35]*MainFormSLS->hh_1[116]
 + c2.v[36]*MainFormSLS->hh_1[108]
 + c2.v[37]*MainFormSLS->hh_1[100]
 + c2.v[38]*MainFormSLS->hh_1[92]
 + c2.v[39]*MainFormSLS->hh_1[84]
 + c2.v[40]*MainFormSLS->hh_1[76]
 + c2.v[41]*MainFormSLS->hh_1[68]
 + c2.v[42]*MainFormSLS->hh_1[60]
 + c2.v[43]*MainFormSLS->hh_1[52]
 + c2.v[44]*MainFormSLS->hh_1[44]
 + c2.v[45]*MainFormSLS->hh_1[36]
 + c2.v[46]*MainFormSLS->hh_1[28]
 + c2.v[47]*MainFormSLS->hh_1[20]
 + c2.v[48]*MainFormSLS->hh_1[12]
 + c2.v[49]*MainFormSLS->hh_1[4]
 + c2.v[50]*MainFormSLS->hh_1[156]
 + c2.v[51]*MainFormSLS->hh_1[148]
 + c2.v[52]*MainFormSLS->hh_1[140]
 + c2.v[53]*MainFormSLS->hh_1[132]
 + c2.v[54]*MainFormSLS->hh_1[124]
 + c2.v[55]*MainFormSLS->hh_1[116]
 + c2.v[56]*MainFormSLS->hh_1[108]
 + c2.v[57]*MainFormSLS->hh_1[100]
 + c2.v[58]*MainFormSLS->hh_1[92]
 + c2.v[59]*MainFormSLS->hh_1[84]
 + c2.v[60]*MainFormSLS->hh_1[76]
 + c2.v[61]*MainFormSLS->hh_1[68]
 + c2.v[62]*MainFormSLS->hh_1[60]
 + c2.v[63]*MainFormSLS->hh_1[52]
 + c2.v[64]*MainFormSLS->hh_1[44]
 + c2.v[65]*MainFormSLS->hh_1[36]
 + c2.v[66]*MainFormSLS->hh_1[28]
 + c2.v[67]*MainFormSLS->hh_1[20]
 + c2.v[68]*MainFormSLS->hh_1[12]
 + c2.v[69]*MainFormSLS->hh_1[4]
 + c2.v[70]*MainFormSLS->hh_1[156]
 + c2.v[71]*MainFormSLS->hh_1[148]
 + c2.v[72]*MainFormSLS->hh_1[140]
 + c2.v[73]*MainFormSLS->hh_1[132]
 + c2.v[74]*MainFormSLS->hh_1[124]
 + c2.v[75]*MainFormSLS->hh_1[116]
 + c2.v[76]*MainFormSLS->hh_1[108]
 + c2.v[77]*MainFormSLS->hh_1[100]
 + c2.v[78]*MainFormSLS->hh_1[92]
 + c2.v[79]*MainFormSLS->hh_1[84];
s/=N_2;
out.push_back(s);
//������ 77
s =c2.v[0]*MainFormSLS->hh_1[77]
 + c2.v[1]*MainFormSLS->hh_1[71]
 + c2.v[2]*MainFormSLS->hh_1[65]
 + c2.v[3]*MainFormSLS->hh_1[59]
 + c2.v[4]*MainFormSLS->hh_1[53]
 + c2.v[5]*MainFormSLS->hh_1[47]
 + c2.v[6]*MainFormSLS->hh_1[41]
 + c2.v[7]*MainFormSLS->hh_1[35]
 + c2.v[8]*MainFormSLS->hh_1[29]
 + c2.v[9]*MainFormSLS->hh_1[23]
 + c2.v[10]*MainFormSLS->hh_1[17]
 + c2.v[11]*MainFormSLS->hh_1[11]
 + c2.v[12]*MainFormSLS->hh_1[5]
 + c2.v[13]*MainFormSLS->hh_1[159]
 + c2.v[14]*MainFormSLS->hh_1[153]
 + c2.v[15]*MainFormSLS->hh_1[147]
 + c2.v[16]*MainFormSLS->hh_1[141]
 + c2.v[17]*MainFormSLS->hh_1[135]
 + c2.v[18]*MainFormSLS->hh_1[129]
 + c2.v[19]*MainFormSLS->hh_1[123]
 + c2.v[20]*MainFormSLS->hh_1[117]
 + c2.v[21]*MainFormSLS->hh_1[111]
 + c2.v[22]*MainFormSLS->hh_1[105]
 + c2.v[23]*MainFormSLS->hh_1[99]
 + c2.v[24]*MainFormSLS->hh_1[93]
 + c2.v[25]*MainFormSLS->hh_1[87]
 + c2.v[26]*MainFormSLS->hh_1[81]
 + c2.v[27]*MainFormSLS->hh_1[75]
 + c2.v[28]*MainFormSLS->hh_1[69]
 + c2.v[29]*MainFormSLS->hh_1[63]
 + c2.v[30]*MainFormSLS->hh_1[57]
 + c2.v[31]*MainFormSLS->hh_1[51]
 + c2.v[32]*MainFormSLS->hh_1[45]
 + c2.v[33]*MainFormSLS->hh_1[39]
 + c2.v[34]*MainFormSLS->hh_1[33]
 + c2.v[35]*MainFormSLS->hh_1[27]
 + c2.v[36]*MainFormSLS->hh_1[21]
 + c2.v[37]*MainFormSLS->hh_1[15]
 + c2.v[38]*MainFormSLS->hh_1[9]
 + c2.v[39]*MainFormSLS->hh_1[3]
 + c2.v[40]*MainFormSLS->hh_1[157]
 + c2.v[41]*MainFormSLS->hh_1[151]
 + c2.v[42]*MainFormSLS->hh_1[145]
 + c2.v[43]*MainFormSLS->hh_1[139]
 + c2.v[44]*MainFormSLS->hh_1[133]
 + c2.v[45]*MainFormSLS->hh_1[127]
 + c2.v[46]*MainFormSLS->hh_1[121]
 + c2.v[47]*MainFormSLS->hh_1[115]
 + c2.v[48]*MainFormSLS->hh_1[109]
 + c2.v[49]*MainFormSLS->hh_1[103]
 + c2.v[50]*MainFormSLS->hh_1[97]
 + c2.v[51]*MainFormSLS->hh_1[91]
 + c2.v[52]*MainFormSLS->hh_1[85]
 + c2.v[53]*MainFormSLS->hh_1[79]
 + c2.v[54]*MainFormSLS->hh_1[73]
 + c2.v[55]*MainFormSLS->hh_1[67]
 + c2.v[56]*MainFormSLS->hh_1[61]
 + c2.v[57]*MainFormSLS->hh_1[55]
 + c2.v[58]*MainFormSLS->hh_1[49]
 + c2.v[59]*MainFormSLS->hh_1[43]
 + c2.v[60]*MainFormSLS->hh_1[37]
 + c2.v[61]*MainFormSLS->hh_1[31]
 + c2.v[62]*MainFormSLS->hh_1[25]
 + c2.v[63]*MainFormSLS->hh_1[19]
 + c2.v[64]*MainFormSLS->hh_1[13]
 + c2.v[65]*MainFormSLS->hh_1[7]
 + c2.v[66]*MainFormSLS->hh_1[1]
 + c2.v[67]*MainFormSLS->hh_1[155]
 + c2.v[68]*MainFormSLS->hh_1[149]
 + c2.v[69]*MainFormSLS->hh_1[143]
 + c2.v[70]*MainFormSLS->hh_1[137]
 + c2.v[71]*MainFormSLS->hh_1[131]
 + c2.v[72]*MainFormSLS->hh_1[125]
 + c2.v[73]*MainFormSLS->hh_1[119]
 + c2.v[74]*MainFormSLS->hh_1[113]
 + c2.v[75]*MainFormSLS->hh_1[107]
 + c2.v[76]*MainFormSLS->hh_1[101]
 + c2.v[77]*MainFormSLS->hh_1[95]
 + c2.v[78]*MainFormSLS->hh_1[89]
 + c2.v[79]*MainFormSLS->hh_1[83];
s/=N_2;
out.push_back(s);
//������ 78
s =c2.v[0]*MainFormSLS->hh_1[78]
 + c2.v[1]*MainFormSLS->hh_1[74]
 + c2.v[2]*MainFormSLS->hh_1[70]
 + c2.v[3]*MainFormSLS->hh_1[66]
 + c2.v[4]*MainFormSLS->hh_1[62]
 + c2.v[5]*MainFormSLS->hh_1[58]
 + c2.v[6]*MainFormSLS->hh_1[54]
 + c2.v[7]*MainFormSLS->hh_1[50]
 + c2.v[8]*MainFormSLS->hh_1[46]
 + c2.v[9]*MainFormSLS->hh_1[42]
 + c2.v[10]*MainFormSLS->hh_1[38]
 + c2.v[11]*MainFormSLS->hh_1[34]
 + c2.v[12]*MainFormSLS->hh_1[30]
 + c2.v[13]*MainFormSLS->hh_1[26]
 + c2.v[14]*MainFormSLS->hh_1[22]
 + c2.v[15]*MainFormSLS->hh_1[18]
 + c2.v[16]*MainFormSLS->hh_1[14]
 + c2.v[17]*MainFormSLS->hh_1[10]
 + c2.v[18]*MainFormSLS->hh_1[6]
 + c2.v[19]*MainFormSLS->hh_1[2]
 + c2.v[20]*MainFormSLS->hh_1[158]
 + c2.v[21]*MainFormSLS->hh_1[154]
 + c2.v[22]*MainFormSLS->hh_1[150]
 + c2.v[23]*MainFormSLS->hh_1[146]
 + c2.v[24]*MainFormSLS->hh_1[142]
 + c2.v[25]*MainFormSLS->hh_1[138]
 + c2.v[26]*MainFormSLS->hh_1[134]
 + c2.v[27]*MainFormSLS->hh_1[130]
 + c2.v[28]*MainFormSLS->hh_1[126]
 + c2.v[29]*MainFormSLS->hh_1[122]
 + c2.v[30]*MainFormSLS->hh_1[118]
 + c2.v[31]*MainFormSLS->hh_1[114]
 + c2.v[32]*MainFormSLS->hh_1[110]
 + c2.v[33]*MainFormSLS->hh_1[106]
 + c2.v[34]*MainFormSLS->hh_1[102]
 + c2.v[35]*MainFormSLS->hh_1[98]
 + c2.v[36]*MainFormSLS->hh_1[94]
 + c2.v[37]*MainFormSLS->hh_1[90]
 + c2.v[38]*MainFormSLS->hh_1[86]
 + c2.v[39]*MainFormSLS->hh_1[82]
 + c2.v[40]*MainFormSLS->hh_1[78]
 + c2.v[41]*MainFormSLS->hh_1[74]
 + c2.v[42]*MainFormSLS->hh_1[70]
 + c2.v[43]*MainFormSLS->hh_1[66]
 + c2.v[44]*MainFormSLS->hh_1[62]
 + c2.v[45]*MainFormSLS->hh_1[58]
 + c2.v[46]*MainFormSLS->hh_1[54]
 + c2.v[47]*MainFormSLS->hh_1[50]
 + c2.v[48]*MainFormSLS->hh_1[46]
 + c2.v[49]*MainFormSLS->hh_1[42]
 + c2.v[50]*MainFormSLS->hh_1[38]
 + c2.v[51]*MainFormSLS->hh_1[34]
 + c2.v[52]*MainFormSLS->hh_1[30]
 + c2.v[53]*MainFormSLS->hh_1[26]
 + c2.v[54]*MainFormSLS->hh_1[22]
 + c2.v[55]*MainFormSLS->hh_1[18]
 + c2.v[56]*MainFormSLS->hh_1[14]
 + c2.v[57]*MainFormSLS->hh_1[10]
 + c2.v[58]*MainFormSLS->hh_1[6]
 + c2.v[59]*MainFormSLS->hh_1[2]
 + c2.v[60]*MainFormSLS->hh_1[158]
 + c2.v[61]*MainFormSLS->hh_1[154]
 + c2.v[62]*MainFormSLS->hh_1[150]
 + c2.v[63]*MainFormSLS->hh_1[146]
 + c2.v[64]*MainFormSLS->hh_1[142]
 + c2.v[65]*MainFormSLS->hh_1[138]
 + c2.v[66]*MainFormSLS->hh_1[134]
 + c2.v[67]*MainFormSLS->hh_1[130]
 + c2.v[68]*MainFormSLS->hh_1[126]
 + c2.v[69]*MainFormSLS->hh_1[122]
 + c2.v[70]*MainFormSLS->hh_1[118]
 + c2.v[71]*MainFormSLS->hh_1[114]
 + c2.v[72]*MainFormSLS->hh_1[110]
 + c2.v[73]*MainFormSLS->hh_1[106]
 + c2.v[74]*MainFormSLS->hh_1[102]
 + c2.v[75]*MainFormSLS->hh_1[98]
 + c2.v[76]*MainFormSLS->hh_1[94]
 + c2.v[77]*MainFormSLS->hh_1[90]
 + c2.v[78]*MainFormSLS->hh_1[86]
 + c2.v[79]*MainFormSLS->hh_1[82];
s/=N_2;
out.push_back(s);
//������ 79
s =c2.v[0]*MainFormSLS->hh_1[79]
 + c2.v[1]*MainFormSLS->hh_1[77]
 + c2.v[2]*MainFormSLS->hh_1[75]
 + c2.v[3]*MainFormSLS->hh_1[73]
 + c2.v[4]*MainFormSLS->hh_1[71]
 + c2.v[5]*MainFormSLS->hh_1[69]
 + c2.v[6]*MainFormSLS->hh_1[67]
 + c2.v[7]*MainFormSLS->hh_1[65]
 + c2.v[8]*MainFormSLS->hh_1[63]
 + c2.v[9]*MainFormSLS->hh_1[61]
 + c2.v[10]*MainFormSLS->hh_1[59]
 + c2.v[11]*MainFormSLS->hh_1[57]
 + c2.v[12]*MainFormSLS->hh_1[55]
 + c2.v[13]*MainFormSLS->hh_1[53]
 + c2.v[14]*MainFormSLS->hh_1[51]
 + c2.v[15]*MainFormSLS->hh_1[49]
 + c2.v[16]*MainFormSLS->hh_1[47]
 + c2.v[17]*MainFormSLS->hh_1[45]
 + c2.v[18]*MainFormSLS->hh_1[43]
 + c2.v[19]*MainFormSLS->hh_1[41]
 + c2.v[20]*MainFormSLS->hh_1[39]
 + c2.v[21]*MainFormSLS->hh_1[37]
 + c2.v[22]*MainFormSLS->hh_1[35]
 + c2.v[23]*MainFormSLS->hh_1[33]
 + c2.v[24]*MainFormSLS->hh_1[31]
 + c2.v[25]*MainFormSLS->hh_1[29]
 + c2.v[26]*MainFormSLS->hh_1[27]
 + c2.v[27]*MainFormSLS->hh_1[25]
 + c2.v[28]*MainFormSLS->hh_1[23]
 + c2.v[29]*MainFormSLS->hh_1[21]
 + c2.v[30]*MainFormSLS->hh_1[19]
 + c2.v[31]*MainFormSLS->hh_1[17]
 + c2.v[32]*MainFormSLS->hh_1[15]
 + c2.v[33]*MainFormSLS->hh_1[13]
 + c2.v[34]*MainFormSLS->hh_1[11]
 + c2.v[35]*MainFormSLS->hh_1[9]
 + c2.v[36]*MainFormSLS->hh_1[7]
 + c2.v[37]*MainFormSLS->hh_1[5]
 + c2.v[38]*MainFormSLS->hh_1[3]
 + c2.v[39]*MainFormSLS->hh_1[1]
 + c2.v[40]*MainFormSLS->hh_1[159]
 + c2.v[41]*MainFormSLS->hh_1[157]
 + c2.v[42]*MainFormSLS->hh_1[155]
 + c2.v[43]*MainFormSLS->hh_1[153]
 + c2.v[44]*MainFormSLS->hh_1[151]
 + c2.v[45]*MainFormSLS->hh_1[149]
 + c2.v[46]*MainFormSLS->hh_1[147]
 + c2.v[47]*MainFormSLS->hh_1[145]
 + c2.v[48]*MainFormSLS->hh_1[143]
 + c2.v[49]*MainFormSLS->hh_1[141]
 + c2.v[50]*MainFormSLS->hh_1[139]
 + c2.v[51]*MainFormSLS->hh_1[137]
 + c2.v[52]*MainFormSLS->hh_1[135]
 + c2.v[53]*MainFormSLS->hh_1[133]
 + c2.v[54]*MainFormSLS->hh_1[131]
 + c2.v[55]*MainFormSLS->hh_1[129]
 + c2.v[56]*MainFormSLS->hh_1[127]
 + c2.v[57]*MainFormSLS->hh_1[125]
 + c2.v[58]*MainFormSLS->hh_1[123]
 + c2.v[59]*MainFormSLS->hh_1[121]
 + c2.v[60]*MainFormSLS->hh_1[119]
 + c2.v[61]*MainFormSLS->hh_1[117]
 + c2.v[62]*MainFormSLS->hh_1[115]
 + c2.v[63]*MainFormSLS->hh_1[113]
 + c2.v[64]*MainFormSLS->hh_1[111]
 + c2.v[65]*MainFormSLS->hh_1[109]
 + c2.v[66]*MainFormSLS->hh_1[107]
 + c2.v[67]*MainFormSLS->hh_1[105]
 + c2.v[68]*MainFormSLS->hh_1[103]
 + c2.v[69]*MainFormSLS->hh_1[101]
 + c2.v[70]*MainFormSLS->hh_1[99]
 + c2.v[71]*MainFormSLS->hh_1[97]
 + c2.v[72]*MainFormSLS->hh_1[95]
 + c2.v[73]*MainFormSLS->hh_1[93]
 + c2.v[74]*MainFormSLS->hh_1[91]
 + c2.v[75]*MainFormSLS->hh_1[89]
 + c2.v[76]*MainFormSLS->hh_1[87]
 + c2.v[77]*MainFormSLS->hh_1[85]
 + c2.v[78]*MainFormSLS->hh_1[83]
 + c2.v[79]*MainFormSLS->hh_1[81];
s/=N_2;
out.push_back(s);
//������ 80
s =c2.v[0]*MainFormSLS->hh_1[80]
 + c2.v[1]*MainFormSLS->hh_1[80]
 + c2.v[2]*MainFormSLS->hh_1[80]
 + c2.v[3]*MainFormSLS->hh_1[80]
 + c2.v[4]*MainFormSLS->hh_1[80]
 + c2.v[5]*MainFormSLS->hh_1[80]
 + c2.v[6]*MainFormSLS->hh_1[80]
 + c2.v[7]*MainFormSLS->hh_1[80]
 + c2.v[8]*MainFormSLS->hh_1[80]
 + c2.v[9]*MainFormSLS->hh_1[80]
 + c2.v[10]*MainFormSLS->hh_1[80]
 + c2.v[11]*MainFormSLS->hh_1[80]
 + c2.v[12]*MainFormSLS->hh_1[80]
 + c2.v[13]*MainFormSLS->hh_1[80]
 + c2.v[14]*MainFormSLS->hh_1[80]
 + c2.v[15]*MainFormSLS->hh_1[80]
 + c2.v[16]*MainFormSLS->hh_1[80]
 + c2.v[17]*MainFormSLS->hh_1[80]
 + c2.v[18]*MainFormSLS->hh_1[80]
 + c2.v[19]*MainFormSLS->hh_1[80]
 + c2.v[20]*MainFormSLS->hh_1[80]
 + c2.v[21]*MainFormSLS->hh_1[80]
 + c2.v[22]*MainFormSLS->hh_1[80]
 + c2.v[23]*MainFormSLS->hh_1[80]
 + c2.v[24]*MainFormSLS->hh_1[80]
 + c2.v[25]*MainFormSLS->hh_1[80]
 + c2.v[26]*MainFormSLS->hh_1[80]
 + c2.v[27]*MainFormSLS->hh_1[80]
 + c2.v[28]*MainFormSLS->hh_1[80]
 + c2.v[29]*MainFormSLS->hh_1[80]
 + c2.v[30]*MainFormSLS->hh_1[80]
 + c2.v[31]*MainFormSLS->hh_1[80]
 + c2.v[32]*MainFormSLS->hh_1[80]
 + c2.v[33]*MainFormSLS->hh_1[80]
 + c2.v[34]*MainFormSLS->hh_1[80]
 + c2.v[35]*MainFormSLS->hh_1[80]
 + c2.v[36]*MainFormSLS->hh_1[80]
 + c2.v[37]*MainFormSLS->hh_1[80]
 + c2.v[38]*MainFormSLS->hh_1[80]
 + c2.v[39]*MainFormSLS->hh_1[80]
 + c2.v[40]*MainFormSLS->hh_1[80]
 + c2.v[41]*MainFormSLS->hh_1[80]
 + c2.v[42]*MainFormSLS->hh_1[80]
 + c2.v[43]*MainFormSLS->hh_1[80]
 + c2.v[44]*MainFormSLS->hh_1[80]
 + c2.v[45]*MainFormSLS->hh_1[80]
 + c2.v[46]*MainFormSLS->hh_1[80]
 + c2.v[47]*MainFormSLS->hh_1[80]
 + c2.v[48]*MainFormSLS->hh_1[80]
 + c2.v[49]*MainFormSLS->hh_1[80]
 + c2.v[50]*MainFormSLS->hh_1[80]
 + c2.v[51]*MainFormSLS->hh_1[80]
 + c2.v[52]*MainFormSLS->hh_1[80]
 + c2.v[53]*MainFormSLS->hh_1[80]
 + c2.v[54]*MainFormSLS->hh_1[80]
 + c2.v[55]*MainFormSLS->hh_1[80]
 + c2.v[56]*MainFormSLS->hh_1[80]
 + c2.v[57]*MainFormSLS->hh_1[80]
 + c2.v[58]*MainFormSLS->hh_1[80]
 + c2.v[59]*MainFormSLS->hh_1[80]
 + c2.v[60]*MainFormSLS->hh_1[80]
 + c2.v[61]*MainFormSLS->hh_1[80]
 + c2.v[62]*MainFormSLS->hh_1[80]
 + c2.v[63]*MainFormSLS->hh_1[80]
 + c2.v[64]*MainFormSLS->hh_1[80]
 + c2.v[65]*MainFormSLS->hh_1[80]
 + c2.v[66]*MainFormSLS->hh_1[80]
 + c2.v[67]*MainFormSLS->hh_1[80]
 + c2.v[68]*MainFormSLS->hh_1[80]
 + c2.v[69]*MainFormSLS->hh_1[80]
 + c2.v[70]*MainFormSLS->hh_1[80]
 + c2.v[71]*MainFormSLS->hh_1[80]
 + c2.v[72]*MainFormSLS->hh_1[80]
 + c2.v[73]*MainFormSLS->hh_1[80]
 + c2.v[74]*MainFormSLS->hh_1[80]
 + c2.v[75]*MainFormSLS->hh_1[80]
 + c2.v[76]*MainFormSLS->hh_1[80]
 + c2.v[77]*MainFormSLS->hh_1[80]
 + c2.v[78]*MainFormSLS->hh_1[80]
 + c2.v[79]*MainFormSLS->hh_1[80];
s/=N_2;
out.push_back(s);
//������ 81
s =c2.v[0]*MainFormSLS->hh_1[81]
 + c2.v[1]*MainFormSLS->hh_1[83]
 + c2.v[2]*MainFormSLS->hh_1[85]
 + c2.v[3]*MainFormSLS->hh_1[87]
 + c2.v[4]*MainFormSLS->hh_1[89]
 + c2.v[5]*MainFormSLS->hh_1[91]
 + c2.v[6]*MainFormSLS->hh_1[93]
 + c2.v[7]*MainFormSLS->hh_1[95]
 + c2.v[8]*MainFormSLS->hh_1[97]
 + c2.v[9]*MainFormSLS->hh_1[99]
 + c2.v[10]*MainFormSLS->hh_1[101]
 + c2.v[11]*MainFormSLS->hh_1[103]
 + c2.v[12]*MainFormSLS->hh_1[105]
 + c2.v[13]*MainFormSLS->hh_1[107]
 + c2.v[14]*MainFormSLS->hh_1[109]
 + c2.v[15]*MainFormSLS->hh_1[111]
 + c2.v[16]*MainFormSLS->hh_1[113]
 + c2.v[17]*MainFormSLS->hh_1[115]
 + c2.v[18]*MainFormSLS->hh_1[117]
 + c2.v[19]*MainFormSLS->hh_1[119]
 + c2.v[20]*MainFormSLS->hh_1[121]
 + c2.v[21]*MainFormSLS->hh_1[123]
 + c2.v[22]*MainFormSLS->hh_1[125]
 + c2.v[23]*MainFormSLS->hh_1[127]
 + c2.v[24]*MainFormSLS->hh_1[129]
 + c2.v[25]*MainFormSLS->hh_1[131]
 + c2.v[26]*MainFormSLS->hh_1[133]
 + c2.v[27]*MainFormSLS->hh_1[135]
 + c2.v[28]*MainFormSLS->hh_1[137]
 + c2.v[29]*MainFormSLS->hh_1[139]
 + c2.v[30]*MainFormSLS->hh_1[141]
 + c2.v[31]*MainFormSLS->hh_1[143]
 + c2.v[32]*MainFormSLS->hh_1[145]
 + c2.v[33]*MainFormSLS->hh_1[147]
 + c2.v[34]*MainFormSLS->hh_1[149]
 + c2.v[35]*MainFormSLS->hh_1[151]
 + c2.v[36]*MainFormSLS->hh_1[153]
 + c2.v[37]*MainFormSLS->hh_1[155]
 + c2.v[38]*MainFormSLS->hh_1[157]
 + c2.v[39]*MainFormSLS->hh_1[159]
 + c2.v[40]*MainFormSLS->hh_1[1]
 + c2.v[41]*MainFormSLS->hh_1[3]
 + c2.v[42]*MainFormSLS->hh_1[5]
 + c2.v[43]*MainFormSLS->hh_1[7]
 + c2.v[44]*MainFormSLS->hh_1[9]
 + c2.v[45]*MainFormSLS->hh_1[11]
 + c2.v[46]*MainFormSLS->hh_1[13]
 + c2.v[47]*MainFormSLS->hh_1[15]
 + c2.v[48]*MainFormSLS->hh_1[17]
 + c2.v[49]*MainFormSLS->hh_1[19]
 + c2.v[50]*MainFormSLS->hh_1[21]
 + c2.v[51]*MainFormSLS->hh_1[23]
 + c2.v[52]*MainFormSLS->hh_1[25]
 + c2.v[53]*MainFormSLS->hh_1[27]
 + c2.v[54]*MainFormSLS->hh_1[29]
 + c2.v[55]*MainFormSLS->hh_1[31]
 + c2.v[56]*MainFormSLS->hh_1[33]
 + c2.v[57]*MainFormSLS->hh_1[35]
 + c2.v[58]*MainFormSLS->hh_1[37]
 + c2.v[59]*MainFormSLS->hh_1[39]
 + c2.v[60]*MainFormSLS->hh_1[41]
 + c2.v[61]*MainFormSLS->hh_1[43]
 + c2.v[62]*MainFormSLS->hh_1[45]
 + c2.v[63]*MainFormSLS->hh_1[47]
 + c2.v[64]*MainFormSLS->hh_1[49]
 + c2.v[65]*MainFormSLS->hh_1[51]
 + c2.v[66]*MainFormSLS->hh_1[53]
 + c2.v[67]*MainFormSLS->hh_1[55]
 + c2.v[68]*MainFormSLS->hh_1[57]
 + c2.v[69]*MainFormSLS->hh_1[59]
 + c2.v[70]*MainFormSLS->hh_1[61]
 + c2.v[71]*MainFormSLS->hh_1[63]
 + c2.v[72]*MainFormSLS->hh_1[65]
 + c2.v[73]*MainFormSLS->hh_1[67]
 + c2.v[74]*MainFormSLS->hh_1[69]
 + c2.v[75]*MainFormSLS->hh_1[71]
 + c2.v[76]*MainFormSLS->hh_1[73]
 + c2.v[77]*MainFormSLS->hh_1[75]
 + c2.v[78]*MainFormSLS->hh_1[77]
 + c2.v[79]*MainFormSLS->hh_1[79];
s/=N_2;
out.push_back(s);
//������ 82
s =c2.v[0]*MainFormSLS->hh_1[82]
 + c2.v[1]*MainFormSLS->hh_1[86]
 + c2.v[2]*MainFormSLS->hh_1[90]
 + c2.v[3]*MainFormSLS->hh_1[94]
 + c2.v[4]*MainFormSLS->hh_1[98]
 + c2.v[5]*MainFormSLS->hh_1[102]
 + c2.v[6]*MainFormSLS->hh_1[106]
 + c2.v[7]*MainFormSLS->hh_1[110]
 + c2.v[8]*MainFormSLS->hh_1[114]
 + c2.v[9]*MainFormSLS->hh_1[118]
 + c2.v[10]*MainFormSLS->hh_1[122]
 + c2.v[11]*MainFormSLS->hh_1[126]
 + c2.v[12]*MainFormSLS->hh_1[130]
 + c2.v[13]*MainFormSLS->hh_1[134]
 + c2.v[14]*MainFormSLS->hh_1[138]
 + c2.v[15]*MainFormSLS->hh_1[142]
 + c2.v[16]*MainFormSLS->hh_1[146]
 + c2.v[17]*MainFormSLS->hh_1[150]
 + c2.v[18]*MainFormSLS->hh_1[154]
 + c2.v[19]*MainFormSLS->hh_1[158]
 + c2.v[20]*MainFormSLS->hh_1[2]
 + c2.v[21]*MainFormSLS->hh_1[6]
 + c2.v[22]*MainFormSLS->hh_1[10]
 + c2.v[23]*MainFormSLS->hh_1[14]
 + c2.v[24]*MainFormSLS->hh_1[18]
 + c2.v[25]*MainFormSLS->hh_1[22]
 + c2.v[26]*MainFormSLS->hh_1[26]
 + c2.v[27]*MainFormSLS->hh_1[30]
 + c2.v[28]*MainFormSLS->hh_1[34]
 + c2.v[29]*MainFormSLS->hh_1[38]
 + c2.v[30]*MainFormSLS->hh_1[42]
 + c2.v[31]*MainFormSLS->hh_1[46]
 + c2.v[32]*MainFormSLS->hh_1[50]
 + c2.v[33]*MainFormSLS->hh_1[54]
 + c2.v[34]*MainFormSLS->hh_1[58]
 + c2.v[35]*MainFormSLS->hh_1[62]
 + c2.v[36]*MainFormSLS->hh_1[66]
 + c2.v[37]*MainFormSLS->hh_1[70]
 + c2.v[38]*MainFormSLS->hh_1[74]
 + c2.v[39]*MainFormSLS->hh_1[78]
 + c2.v[40]*MainFormSLS->hh_1[82]
 + c2.v[41]*MainFormSLS->hh_1[86]
 + c2.v[42]*MainFormSLS->hh_1[90]
 + c2.v[43]*MainFormSLS->hh_1[94]
 + c2.v[44]*MainFormSLS->hh_1[98]
 + c2.v[45]*MainFormSLS->hh_1[102]
 + c2.v[46]*MainFormSLS->hh_1[106]
 + c2.v[47]*MainFormSLS->hh_1[110]
 + c2.v[48]*MainFormSLS->hh_1[114]
 + c2.v[49]*MainFormSLS->hh_1[118]
 + c2.v[50]*MainFormSLS->hh_1[122]
 + c2.v[51]*MainFormSLS->hh_1[126]
 + c2.v[52]*MainFormSLS->hh_1[130]
 + c2.v[53]*MainFormSLS->hh_1[134]
 + c2.v[54]*MainFormSLS->hh_1[138]
 + c2.v[55]*MainFormSLS->hh_1[142]
 + c2.v[56]*MainFormSLS->hh_1[146]
 + c2.v[57]*MainFormSLS->hh_1[150]
 + c2.v[58]*MainFormSLS->hh_1[154]
 + c2.v[59]*MainFormSLS->hh_1[158]
 + c2.v[60]*MainFormSLS->hh_1[2]
 + c2.v[61]*MainFormSLS->hh_1[6]
 + c2.v[62]*MainFormSLS->hh_1[10]
 + c2.v[63]*MainFormSLS->hh_1[14]
 + c2.v[64]*MainFormSLS->hh_1[18]
 + c2.v[65]*MainFormSLS->hh_1[22]
 + c2.v[66]*MainFormSLS->hh_1[26]
 + c2.v[67]*MainFormSLS->hh_1[30]
 + c2.v[68]*MainFormSLS->hh_1[34]
 + c2.v[69]*MainFormSLS->hh_1[38]
 + c2.v[70]*MainFormSLS->hh_1[42]
 + c2.v[71]*MainFormSLS->hh_1[46]
 + c2.v[72]*MainFormSLS->hh_1[50]
 + c2.v[73]*MainFormSLS->hh_1[54]
 + c2.v[74]*MainFormSLS->hh_1[58]
 + c2.v[75]*MainFormSLS->hh_1[62]
 + c2.v[76]*MainFormSLS->hh_1[66]
 + c2.v[77]*MainFormSLS->hh_1[70]
 + c2.v[78]*MainFormSLS->hh_1[74]
 + c2.v[79]*MainFormSLS->hh_1[78];
s/=N_2;
out.push_back(s);
//������ 83
s =c2.v[0]*MainFormSLS->hh_1[83]
 + c2.v[1]*MainFormSLS->hh_1[89]
 + c2.v[2]*MainFormSLS->hh_1[95]
 + c2.v[3]*MainFormSLS->hh_1[101]
 + c2.v[4]*MainFormSLS->hh_1[107]
 + c2.v[5]*MainFormSLS->hh_1[113]
 + c2.v[6]*MainFormSLS->hh_1[119]
 + c2.v[7]*MainFormSLS->hh_1[125]
 + c2.v[8]*MainFormSLS->hh_1[131]
 + c2.v[9]*MainFormSLS->hh_1[137]
 + c2.v[10]*MainFormSLS->hh_1[143]
 + c2.v[11]*MainFormSLS->hh_1[149]
 + c2.v[12]*MainFormSLS->hh_1[155]
 + c2.v[13]*MainFormSLS->hh_1[1]
 + c2.v[14]*MainFormSLS->hh_1[7]
 + c2.v[15]*MainFormSLS->hh_1[13]
 + c2.v[16]*MainFormSLS->hh_1[19]
 + c2.v[17]*MainFormSLS->hh_1[25]
 + c2.v[18]*MainFormSLS->hh_1[31]
 + c2.v[19]*MainFormSLS->hh_1[37]
 + c2.v[20]*MainFormSLS->hh_1[43]
 + c2.v[21]*MainFormSLS->hh_1[49]
 + c2.v[22]*MainFormSLS->hh_1[55]
 + c2.v[23]*MainFormSLS->hh_1[61]
 + c2.v[24]*MainFormSLS->hh_1[67]
 + c2.v[25]*MainFormSLS->hh_1[73]
 + c2.v[26]*MainFormSLS->hh_1[79]
 + c2.v[27]*MainFormSLS->hh_1[85]
 + c2.v[28]*MainFormSLS->hh_1[91]
 + c2.v[29]*MainFormSLS->hh_1[97]
 + c2.v[30]*MainFormSLS->hh_1[103]
 + c2.v[31]*MainFormSLS->hh_1[109]
 + c2.v[32]*MainFormSLS->hh_1[115]
 + c2.v[33]*MainFormSLS->hh_1[121]
 + c2.v[34]*MainFormSLS->hh_1[127]
 + c2.v[35]*MainFormSLS->hh_1[133]
 + c2.v[36]*MainFormSLS->hh_1[139]
 + c2.v[37]*MainFormSLS->hh_1[145]
 + c2.v[38]*MainFormSLS->hh_1[151]
 + c2.v[39]*MainFormSLS->hh_1[157]
 + c2.v[40]*MainFormSLS->hh_1[3]
 + c2.v[41]*MainFormSLS->hh_1[9]
 + c2.v[42]*MainFormSLS->hh_1[15]
 + c2.v[43]*MainFormSLS->hh_1[21]
 + c2.v[44]*MainFormSLS->hh_1[27]
 + c2.v[45]*MainFormSLS->hh_1[33]
 + c2.v[46]*MainFormSLS->hh_1[39]
 + c2.v[47]*MainFormSLS->hh_1[45]
 + c2.v[48]*MainFormSLS->hh_1[51]
 + c2.v[49]*MainFormSLS->hh_1[57]
 + c2.v[50]*MainFormSLS->hh_1[63]
 + c2.v[51]*MainFormSLS->hh_1[69]
 + c2.v[52]*MainFormSLS->hh_1[75]
 + c2.v[53]*MainFormSLS->hh_1[81]
 + c2.v[54]*MainFormSLS->hh_1[87]
 + c2.v[55]*MainFormSLS->hh_1[93]
 + c2.v[56]*MainFormSLS->hh_1[99]
 + c2.v[57]*MainFormSLS->hh_1[105]
 + c2.v[58]*MainFormSLS->hh_1[111]
 + c2.v[59]*MainFormSLS->hh_1[117]
 + c2.v[60]*MainFormSLS->hh_1[123]
 + c2.v[61]*MainFormSLS->hh_1[129]
 + c2.v[62]*MainFormSLS->hh_1[135]
 + c2.v[63]*MainFormSLS->hh_1[141]
 + c2.v[64]*MainFormSLS->hh_1[147]
 + c2.v[65]*MainFormSLS->hh_1[153]
 + c2.v[66]*MainFormSLS->hh_1[159]
 + c2.v[67]*MainFormSLS->hh_1[5]
 + c2.v[68]*MainFormSLS->hh_1[11]
 + c2.v[69]*MainFormSLS->hh_1[17]
 + c2.v[70]*MainFormSLS->hh_1[23]
 + c2.v[71]*MainFormSLS->hh_1[29]
 + c2.v[72]*MainFormSLS->hh_1[35]
 + c2.v[73]*MainFormSLS->hh_1[41]
 + c2.v[74]*MainFormSLS->hh_1[47]
 + c2.v[75]*MainFormSLS->hh_1[53]
 + c2.v[76]*MainFormSLS->hh_1[59]
 + c2.v[77]*MainFormSLS->hh_1[65]
 + c2.v[78]*MainFormSLS->hh_1[71]
 + c2.v[79]*MainFormSLS->hh_1[77];
s/=N_2;
out.push_back(s);
//������ 84
s =c2.v[0]*MainFormSLS->hh_1[84]
 + c2.v[1]*MainFormSLS->hh_1[92]
 + c2.v[2]*MainFormSLS->hh_1[100]
 + c2.v[3]*MainFormSLS->hh_1[108]
 + c2.v[4]*MainFormSLS->hh_1[116]
 + c2.v[5]*MainFormSLS->hh_1[124]
 + c2.v[6]*MainFormSLS->hh_1[132]
 + c2.v[7]*MainFormSLS->hh_1[140]
 + c2.v[8]*MainFormSLS->hh_1[148]
 + c2.v[9]*MainFormSLS->hh_1[156]
 + c2.v[10]*MainFormSLS->hh_1[4]
 + c2.v[11]*MainFormSLS->hh_1[12]
 + c2.v[12]*MainFormSLS->hh_1[20]
 + c2.v[13]*MainFormSLS->hh_1[28]
 + c2.v[14]*MainFormSLS->hh_1[36]
 + c2.v[15]*MainFormSLS->hh_1[44]
 + c2.v[16]*MainFormSLS->hh_1[52]
 + c2.v[17]*MainFormSLS->hh_1[60]
 + c2.v[18]*MainFormSLS->hh_1[68]
 + c2.v[19]*MainFormSLS->hh_1[76]
 + c2.v[20]*MainFormSLS->hh_1[84]
 + c2.v[21]*MainFormSLS->hh_1[92]
 + c2.v[22]*MainFormSLS->hh_1[100]
 + c2.v[23]*MainFormSLS->hh_1[108]
 + c2.v[24]*MainFormSLS->hh_1[116]
 + c2.v[25]*MainFormSLS->hh_1[124]
 + c2.v[26]*MainFormSLS->hh_1[132]
 + c2.v[27]*MainFormSLS->hh_1[140]
 + c2.v[28]*MainFormSLS->hh_1[148]
 + c2.v[29]*MainFormSLS->hh_1[156]
 + c2.v[30]*MainFormSLS->hh_1[4]
 + c2.v[31]*MainFormSLS->hh_1[12]
 + c2.v[32]*MainFormSLS->hh_1[20]
 + c2.v[33]*MainFormSLS->hh_1[28]
 + c2.v[34]*MainFormSLS->hh_1[36]
 + c2.v[35]*MainFormSLS->hh_1[44]
 + c2.v[36]*MainFormSLS->hh_1[52]
 + c2.v[37]*MainFormSLS->hh_1[60]
 + c2.v[38]*MainFormSLS->hh_1[68]
 + c2.v[39]*MainFormSLS->hh_1[76]
 + c2.v[40]*MainFormSLS->hh_1[84]
 + c2.v[41]*MainFormSLS->hh_1[92]
 + c2.v[42]*MainFormSLS->hh_1[100]
 + c2.v[43]*MainFormSLS->hh_1[108]
 + c2.v[44]*MainFormSLS->hh_1[116]
 + c2.v[45]*MainFormSLS->hh_1[124]
 + c2.v[46]*MainFormSLS->hh_1[132]
 + c2.v[47]*MainFormSLS->hh_1[140]
 + c2.v[48]*MainFormSLS->hh_1[148]
 + c2.v[49]*MainFormSLS->hh_1[156]
 + c2.v[50]*MainFormSLS->hh_1[4]
 + c2.v[51]*MainFormSLS->hh_1[12]
 + c2.v[52]*MainFormSLS->hh_1[20]
 + c2.v[53]*MainFormSLS->hh_1[28]
 + c2.v[54]*MainFormSLS->hh_1[36]
 + c2.v[55]*MainFormSLS->hh_1[44]
 + c2.v[56]*MainFormSLS->hh_1[52]
 + c2.v[57]*MainFormSLS->hh_1[60]
 + c2.v[58]*MainFormSLS->hh_1[68]
 + c2.v[59]*MainFormSLS->hh_1[76]
 + c2.v[60]*MainFormSLS->hh_1[84]
 + c2.v[61]*MainFormSLS->hh_1[92]
 + c2.v[62]*MainFormSLS->hh_1[100]
 + c2.v[63]*MainFormSLS->hh_1[108]
 + c2.v[64]*MainFormSLS->hh_1[116]
 + c2.v[65]*MainFormSLS->hh_1[124]
 + c2.v[66]*MainFormSLS->hh_1[132]
 + c2.v[67]*MainFormSLS->hh_1[140]
 + c2.v[68]*MainFormSLS->hh_1[148]
 + c2.v[69]*MainFormSLS->hh_1[156]
 + c2.v[70]*MainFormSLS->hh_1[4]
 + c2.v[71]*MainFormSLS->hh_1[12]
 + c2.v[72]*MainFormSLS->hh_1[20]
 + c2.v[73]*MainFormSLS->hh_1[28]
 + c2.v[74]*MainFormSLS->hh_1[36]
 + c2.v[75]*MainFormSLS->hh_1[44]
 + c2.v[76]*MainFormSLS->hh_1[52]
 + c2.v[77]*MainFormSLS->hh_1[60]
 + c2.v[78]*MainFormSLS->hh_1[68]
 + c2.v[79]*MainFormSLS->hh_1[76];
s/=N_2;
out.push_back(s);
//������ 85
s =c2.v[0]*MainFormSLS->hh_1[85]
 + c2.v[1]*MainFormSLS->hh_1[95]
 + c2.v[2]*MainFormSLS->hh_1[105]
 + c2.v[3]*MainFormSLS->hh_1[115]
 + c2.v[4]*MainFormSLS->hh_1[125]
 + c2.v[5]*MainFormSLS->hh_1[135]
 + c2.v[6]*MainFormSLS->hh_1[145]
 + c2.v[7]*MainFormSLS->hh_1[155]
 + c2.v[8]*MainFormSLS->hh_1[5]
 + c2.v[9]*MainFormSLS->hh_1[15]
 + c2.v[10]*MainFormSLS->hh_1[25]
 + c2.v[11]*MainFormSLS->hh_1[35]
 + c2.v[12]*MainFormSLS->hh_1[45]
 + c2.v[13]*MainFormSLS->hh_1[55]
 + c2.v[14]*MainFormSLS->hh_1[65]
 + c2.v[15]*MainFormSLS->hh_1[75]
 + c2.v[16]*MainFormSLS->hh_1[85]
 + c2.v[17]*MainFormSLS->hh_1[95]
 + c2.v[18]*MainFormSLS->hh_1[105]
 + c2.v[19]*MainFormSLS->hh_1[115]
 + c2.v[20]*MainFormSLS->hh_1[125]
 + c2.v[21]*MainFormSLS->hh_1[135]
 + c2.v[22]*MainFormSLS->hh_1[145]
 + c2.v[23]*MainFormSLS->hh_1[155]
 + c2.v[24]*MainFormSLS->hh_1[5]
 + c2.v[25]*MainFormSLS->hh_1[15]
 + c2.v[26]*MainFormSLS->hh_1[25]
 + c2.v[27]*MainFormSLS->hh_1[35]
 + c2.v[28]*MainFormSLS->hh_1[45]
 + c2.v[29]*MainFormSLS->hh_1[55]
 + c2.v[30]*MainFormSLS->hh_1[65]
 + c2.v[31]*MainFormSLS->hh_1[75]
 + c2.v[32]*MainFormSLS->hh_1[85]
 + c2.v[33]*MainFormSLS->hh_1[95]
 + c2.v[34]*MainFormSLS->hh_1[105]
 + c2.v[35]*MainFormSLS->hh_1[115]
 + c2.v[36]*MainFormSLS->hh_1[125]
 + c2.v[37]*MainFormSLS->hh_1[135]
 + c2.v[38]*MainFormSLS->hh_1[145]
 + c2.v[39]*MainFormSLS->hh_1[155]
 + c2.v[40]*MainFormSLS->hh_1[5]
 + c2.v[41]*MainFormSLS->hh_1[15]
 + c2.v[42]*MainFormSLS->hh_1[25]
 + c2.v[43]*MainFormSLS->hh_1[35]
 + c2.v[44]*MainFormSLS->hh_1[45]
 + c2.v[45]*MainFormSLS->hh_1[55]
 + c2.v[46]*MainFormSLS->hh_1[65]
 + c2.v[47]*MainFormSLS->hh_1[75]
 + c2.v[48]*MainFormSLS->hh_1[85]
 + c2.v[49]*MainFormSLS->hh_1[95]
 + c2.v[50]*MainFormSLS->hh_1[105]
 + c2.v[51]*MainFormSLS->hh_1[115]
 + c2.v[52]*MainFormSLS->hh_1[125]
 + c2.v[53]*MainFormSLS->hh_1[135]
 + c2.v[54]*MainFormSLS->hh_1[145]
 + c2.v[55]*MainFormSLS->hh_1[155]
 + c2.v[56]*MainFormSLS->hh_1[5]
 + c2.v[57]*MainFormSLS->hh_1[15]
 + c2.v[58]*MainFormSLS->hh_1[25]
 + c2.v[59]*MainFormSLS->hh_1[35]
 + c2.v[60]*MainFormSLS->hh_1[45]
 + c2.v[61]*MainFormSLS->hh_1[55]
 + c2.v[62]*MainFormSLS->hh_1[65]
 + c2.v[63]*MainFormSLS->hh_1[75]
 + c2.v[64]*MainFormSLS->hh_1[85]
 + c2.v[65]*MainFormSLS->hh_1[95]
 + c2.v[66]*MainFormSLS->hh_1[105]
 + c2.v[67]*MainFormSLS->hh_1[115]
 + c2.v[68]*MainFormSLS->hh_1[125]
 + c2.v[69]*MainFormSLS->hh_1[135]
 + c2.v[70]*MainFormSLS->hh_1[145]
 + c2.v[71]*MainFormSLS->hh_1[155]
 + c2.v[72]*MainFormSLS->hh_1[5]
 + c2.v[73]*MainFormSLS->hh_1[15]
 + c2.v[74]*MainFormSLS->hh_1[25]
 + c2.v[75]*MainFormSLS->hh_1[35]
 + c2.v[76]*MainFormSLS->hh_1[45]
 + c2.v[77]*MainFormSLS->hh_1[55]
 + c2.v[78]*MainFormSLS->hh_1[65]
 + c2.v[79]*MainFormSLS->hh_1[75];
s/=N_2;
out.push_back(s);
//������ 86
s =c2.v[0]*MainFormSLS->hh_1[86]
 + c2.v[1]*MainFormSLS->hh_1[98]
 + c2.v[2]*MainFormSLS->hh_1[110]
 + c2.v[3]*MainFormSLS->hh_1[122]
 + c2.v[4]*MainFormSLS->hh_1[134]
 + c2.v[5]*MainFormSLS->hh_1[146]
 + c2.v[6]*MainFormSLS->hh_1[158]
 + c2.v[7]*MainFormSLS->hh_1[10]
 + c2.v[8]*MainFormSLS->hh_1[22]
 + c2.v[9]*MainFormSLS->hh_1[34]
 + c2.v[10]*MainFormSLS->hh_1[46]
 + c2.v[11]*MainFormSLS->hh_1[58]
 + c2.v[12]*MainFormSLS->hh_1[70]
 + c2.v[13]*MainFormSLS->hh_1[82]
 + c2.v[14]*MainFormSLS->hh_1[94]
 + c2.v[15]*MainFormSLS->hh_1[106]
 + c2.v[16]*MainFormSLS->hh_1[118]
 + c2.v[17]*MainFormSLS->hh_1[130]
 + c2.v[18]*MainFormSLS->hh_1[142]
 + c2.v[19]*MainFormSLS->hh_1[154]
 + c2.v[20]*MainFormSLS->hh_1[6]
 + c2.v[21]*MainFormSLS->hh_1[18]
 + c2.v[22]*MainFormSLS->hh_1[30]
 + c2.v[23]*MainFormSLS->hh_1[42]
 + c2.v[24]*MainFormSLS->hh_1[54]
 + c2.v[25]*MainFormSLS->hh_1[66]
 + c2.v[26]*MainFormSLS->hh_1[78]
 + c2.v[27]*MainFormSLS->hh_1[90]
 + c2.v[28]*MainFormSLS->hh_1[102]
 + c2.v[29]*MainFormSLS->hh_1[114]
 + c2.v[30]*MainFormSLS->hh_1[126]
 + c2.v[31]*MainFormSLS->hh_1[138]
 + c2.v[32]*MainFormSLS->hh_1[150]
 + c2.v[33]*MainFormSLS->hh_1[2]
 + c2.v[34]*MainFormSLS->hh_1[14]
 + c2.v[35]*MainFormSLS->hh_1[26]
 + c2.v[36]*MainFormSLS->hh_1[38]
 + c2.v[37]*MainFormSLS->hh_1[50]
 + c2.v[38]*MainFormSLS->hh_1[62]
 + c2.v[39]*MainFormSLS->hh_1[74]
 + c2.v[40]*MainFormSLS->hh_1[86]
 + c2.v[41]*MainFormSLS->hh_1[98]
 + c2.v[42]*MainFormSLS->hh_1[110]
 + c2.v[43]*MainFormSLS->hh_1[122]
 + c2.v[44]*MainFormSLS->hh_1[134]
 + c2.v[45]*MainFormSLS->hh_1[146]
 + c2.v[46]*MainFormSLS->hh_1[158]
 + c2.v[47]*MainFormSLS->hh_1[10]
 + c2.v[48]*MainFormSLS->hh_1[22]
 + c2.v[49]*MainFormSLS->hh_1[34]
 + c2.v[50]*MainFormSLS->hh_1[46]
 + c2.v[51]*MainFormSLS->hh_1[58]
 + c2.v[52]*MainFormSLS->hh_1[70]
 + c2.v[53]*MainFormSLS->hh_1[82]
 + c2.v[54]*MainFormSLS->hh_1[94]
 + c2.v[55]*MainFormSLS->hh_1[106]
 + c2.v[56]*MainFormSLS->hh_1[118]
 + c2.v[57]*MainFormSLS->hh_1[130]
 + c2.v[58]*MainFormSLS->hh_1[142]
 + c2.v[59]*MainFormSLS->hh_1[154]
 + c2.v[60]*MainFormSLS->hh_1[6]
 + c2.v[61]*MainFormSLS->hh_1[18]
 + c2.v[62]*MainFormSLS->hh_1[30]
 + c2.v[63]*MainFormSLS->hh_1[42]
 + c2.v[64]*MainFormSLS->hh_1[54]
 + c2.v[65]*MainFormSLS->hh_1[66]
 + c2.v[66]*MainFormSLS->hh_1[78]
 + c2.v[67]*MainFormSLS->hh_1[90]
 + c2.v[68]*MainFormSLS->hh_1[102]
 + c2.v[69]*MainFormSLS->hh_1[114]
 + c2.v[70]*MainFormSLS->hh_1[126]
 + c2.v[71]*MainFormSLS->hh_1[138]
 + c2.v[72]*MainFormSLS->hh_1[150]
 + c2.v[73]*MainFormSLS->hh_1[2]
 + c2.v[74]*MainFormSLS->hh_1[14]
 + c2.v[75]*MainFormSLS->hh_1[26]
 + c2.v[76]*MainFormSLS->hh_1[38]
 + c2.v[77]*MainFormSLS->hh_1[50]
 + c2.v[78]*MainFormSLS->hh_1[62]
 + c2.v[79]*MainFormSLS->hh_1[74];
s/=N_2;
out.push_back(s);
//������ 87
s =c2.v[0]*MainFormSLS->hh_1[87]
 + c2.v[1]*MainFormSLS->hh_1[101]
 + c2.v[2]*MainFormSLS->hh_1[115]
 + c2.v[3]*MainFormSLS->hh_1[129]
 + c2.v[4]*MainFormSLS->hh_1[143]
 + c2.v[5]*MainFormSLS->hh_1[157]
 + c2.v[6]*MainFormSLS->hh_1[11]
 + c2.v[7]*MainFormSLS->hh_1[25]
 + c2.v[8]*MainFormSLS->hh_1[39]
 + c2.v[9]*MainFormSLS->hh_1[53]
 + c2.v[10]*MainFormSLS->hh_1[67]
 + c2.v[11]*MainFormSLS->hh_1[81]
 + c2.v[12]*MainFormSLS->hh_1[95]
 + c2.v[13]*MainFormSLS->hh_1[109]
 + c2.v[14]*MainFormSLS->hh_1[123]
 + c2.v[15]*MainFormSLS->hh_1[137]
 + c2.v[16]*MainFormSLS->hh_1[151]
 + c2.v[17]*MainFormSLS->hh_1[5]
 + c2.v[18]*MainFormSLS->hh_1[19]
 + c2.v[19]*MainFormSLS->hh_1[33]
 + c2.v[20]*MainFormSLS->hh_1[47]
 + c2.v[21]*MainFormSLS->hh_1[61]
 + c2.v[22]*MainFormSLS->hh_1[75]
 + c2.v[23]*MainFormSLS->hh_1[89]
 + c2.v[24]*MainFormSLS->hh_1[103]
 + c2.v[25]*MainFormSLS->hh_1[117]
 + c2.v[26]*MainFormSLS->hh_1[131]
 + c2.v[27]*MainFormSLS->hh_1[145]
 + c2.v[28]*MainFormSLS->hh_1[159]
 + c2.v[29]*MainFormSLS->hh_1[13]
 + c2.v[30]*MainFormSLS->hh_1[27]
 + c2.v[31]*MainFormSLS->hh_1[41]
 + c2.v[32]*MainFormSLS->hh_1[55]
 + c2.v[33]*MainFormSLS->hh_1[69]
 + c2.v[34]*MainFormSLS->hh_1[83]
 + c2.v[35]*MainFormSLS->hh_1[97]
 + c2.v[36]*MainFormSLS->hh_1[111]
 + c2.v[37]*MainFormSLS->hh_1[125]
 + c2.v[38]*MainFormSLS->hh_1[139]
 + c2.v[39]*MainFormSLS->hh_1[153]
 + c2.v[40]*MainFormSLS->hh_1[7]
 + c2.v[41]*MainFormSLS->hh_1[21]
 + c2.v[42]*MainFormSLS->hh_1[35]
 + c2.v[43]*MainFormSLS->hh_1[49]
 + c2.v[44]*MainFormSLS->hh_1[63]
 + c2.v[45]*MainFormSLS->hh_1[77]
 + c2.v[46]*MainFormSLS->hh_1[91]
 + c2.v[47]*MainFormSLS->hh_1[105]
 + c2.v[48]*MainFormSLS->hh_1[119]
 + c2.v[49]*MainFormSLS->hh_1[133]
 + c2.v[50]*MainFormSLS->hh_1[147]
 + c2.v[51]*MainFormSLS->hh_1[1]
 + c2.v[52]*MainFormSLS->hh_1[15]
 + c2.v[53]*MainFormSLS->hh_1[29]
 + c2.v[54]*MainFormSLS->hh_1[43]
 + c2.v[55]*MainFormSLS->hh_1[57]
 + c2.v[56]*MainFormSLS->hh_1[71]
 + c2.v[57]*MainFormSLS->hh_1[85]
 + c2.v[58]*MainFormSLS->hh_1[99]
 + c2.v[59]*MainFormSLS->hh_1[113]
 + c2.v[60]*MainFormSLS->hh_1[127]
 + c2.v[61]*MainFormSLS->hh_1[141]
 + c2.v[62]*MainFormSLS->hh_1[155]
 + c2.v[63]*MainFormSLS->hh_1[9]
 + c2.v[64]*MainFormSLS->hh_1[23]
 + c2.v[65]*MainFormSLS->hh_1[37]
 + c2.v[66]*MainFormSLS->hh_1[51]
 + c2.v[67]*MainFormSLS->hh_1[65]
 + c2.v[68]*MainFormSLS->hh_1[79]
 + c2.v[69]*MainFormSLS->hh_1[93]
 + c2.v[70]*MainFormSLS->hh_1[107]
 + c2.v[71]*MainFormSLS->hh_1[121]
 + c2.v[72]*MainFormSLS->hh_1[135]
 + c2.v[73]*MainFormSLS->hh_1[149]
 + c2.v[74]*MainFormSLS->hh_1[3]
 + c2.v[75]*MainFormSLS->hh_1[17]
 + c2.v[76]*MainFormSLS->hh_1[31]
 + c2.v[77]*MainFormSLS->hh_1[45]
 + c2.v[78]*MainFormSLS->hh_1[59]
 + c2.v[79]*MainFormSLS->hh_1[73];
s/=N_2;
out.push_back(s);
//������ 88
s =c2.v[0]*MainFormSLS->hh_1[88]
 + c2.v[1]*MainFormSLS->hh_1[104]
 + c2.v[2]*MainFormSLS->hh_1[120]
 + c2.v[3]*MainFormSLS->hh_1[136]
 + c2.v[4]*MainFormSLS->hh_1[152]
 + c2.v[5]*MainFormSLS->hh_1[8]
 + c2.v[6]*MainFormSLS->hh_1[24]
 + c2.v[7]*MainFormSLS->hh_1[40]
 + c2.v[8]*MainFormSLS->hh_1[56]
 + c2.v[9]*MainFormSLS->hh_1[72]
 + c2.v[10]*MainFormSLS->hh_1[88]
 + c2.v[11]*MainFormSLS->hh_1[104]
 + c2.v[12]*MainFormSLS->hh_1[120]
 + c2.v[13]*MainFormSLS->hh_1[136]
 + c2.v[14]*MainFormSLS->hh_1[152]
 + c2.v[15]*MainFormSLS->hh_1[8]
 + c2.v[16]*MainFormSLS->hh_1[24]
 + c2.v[17]*MainFormSLS->hh_1[40]
 + c2.v[18]*MainFormSLS->hh_1[56]
 + c2.v[19]*MainFormSLS->hh_1[72]
 + c2.v[20]*MainFormSLS->hh_1[88]
 + c2.v[21]*MainFormSLS->hh_1[104]
 + c2.v[22]*MainFormSLS->hh_1[120]
 + c2.v[23]*MainFormSLS->hh_1[136]
 + c2.v[24]*MainFormSLS->hh_1[152]
 + c2.v[25]*MainFormSLS->hh_1[8]
 + c2.v[26]*MainFormSLS->hh_1[24]
 + c2.v[27]*MainFormSLS->hh_1[40]
 + c2.v[28]*MainFormSLS->hh_1[56]
 + c2.v[29]*MainFormSLS->hh_1[72]
 + c2.v[30]*MainFormSLS->hh_1[88]
 + c2.v[31]*MainFormSLS->hh_1[104]
 + c2.v[32]*MainFormSLS->hh_1[120]
 + c2.v[33]*MainFormSLS->hh_1[136]
 + c2.v[34]*MainFormSLS->hh_1[152]
 + c2.v[35]*MainFormSLS->hh_1[8]
 + c2.v[36]*MainFormSLS->hh_1[24]
 + c2.v[37]*MainFormSLS->hh_1[40]
 + c2.v[38]*MainFormSLS->hh_1[56]
 + c2.v[39]*MainFormSLS->hh_1[72]
 + c2.v[40]*MainFormSLS->hh_1[88]
 + c2.v[41]*MainFormSLS->hh_1[104]
 + c2.v[42]*MainFormSLS->hh_1[120]
 + c2.v[43]*MainFormSLS->hh_1[136]
 + c2.v[44]*MainFormSLS->hh_1[152]
 + c2.v[45]*MainFormSLS->hh_1[8]
 + c2.v[46]*MainFormSLS->hh_1[24]
 + c2.v[47]*MainFormSLS->hh_1[40]
 + c2.v[48]*MainFormSLS->hh_1[56]
 + c2.v[49]*MainFormSLS->hh_1[72]
 + c2.v[50]*MainFormSLS->hh_1[88]
 + c2.v[51]*MainFormSLS->hh_1[104]
 + c2.v[52]*MainFormSLS->hh_1[120]
 + c2.v[53]*MainFormSLS->hh_1[136]
 + c2.v[54]*MainFormSLS->hh_1[152]
 + c2.v[55]*MainFormSLS->hh_1[8]
 + c2.v[56]*MainFormSLS->hh_1[24]
 + c2.v[57]*MainFormSLS->hh_1[40]
 + c2.v[58]*MainFormSLS->hh_1[56]
 + c2.v[59]*MainFormSLS->hh_1[72]
 + c2.v[60]*MainFormSLS->hh_1[88]
 + c2.v[61]*MainFormSLS->hh_1[104]
 + c2.v[62]*MainFormSLS->hh_1[120]
 + c2.v[63]*MainFormSLS->hh_1[136]
 + c2.v[64]*MainFormSLS->hh_1[152]
 + c2.v[65]*MainFormSLS->hh_1[8]
 + c2.v[66]*MainFormSLS->hh_1[24]
 + c2.v[67]*MainFormSLS->hh_1[40]
 + c2.v[68]*MainFormSLS->hh_1[56]
 + c2.v[69]*MainFormSLS->hh_1[72]
 + c2.v[70]*MainFormSLS->hh_1[88]
 + c2.v[71]*MainFormSLS->hh_1[104]
 + c2.v[72]*MainFormSLS->hh_1[120]
 + c2.v[73]*MainFormSLS->hh_1[136]
 + c2.v[74]*MainFormSLS->hh_1[152]
 + c2.v[75]*MainFormSLS->hh_1[8]
 + c2.v[76]*MainFormSLS->hh_1[24]
 + c2.v[77]*MainFormSLS->hh_1[40]
 + c2.v[78]*MainFormSLS->hh_1[56]
 + c2.v[79]*MainFormSLS->hh_1[72];
s/=N_2;
out.push_back(s);
//������ 89
s =c2.v[0]*MainFormSLS->hh_1[89]
 + c2.v[1]*MainFormSLS->hh_1[107]
 + c2.v[2]*MainFormSLS->hh_1[125]
 + c2.v[3]*MainFormSLS->hh_1[143]
 + c2.v[4]*MainFormSLS->hh_1[1]
 + c2.v[5]*MainFormSLS->hh_1[19]
 + c2.v[6]*MainFormSLS->hh_1[37]
 + c2.v[7]*MainFormSLS->hh_1[55]
 + c2.v[8]*MainFormSLS->hh_1[73]
 + c2.v[9]*MainFormSLS->hh_1[91]
 + c2.v[10]*MainFormSLS->hh_1[109]
 + c2.v[11]*MainFormSLS->hh_1[127]
 + c2.v[12]*MainFormSLS->hh_1[145]
 + c2.v[13]*MainFormSLS->hh_1[3]
 + c2.v[14]*MainFormSLS->hh_1[21]
 + c2.v[15]*MainFormSLS->hh_1[39]
 + c2.v[16]*MainFormSLS->hh_1[57]
 + c2.v[17]*MainFormSLS->hh_1[75]
 + c2.v[18]*MainFormSLS->hh_1[93]
 + c2.v[19]*MainFormSLS->hh_1[111]
 + c2.v[20]*MainFormSLS->hh_1[129]
 + c2.v[21]*MainFormSLS->hh_1[147]
 + c2.v[22]*MainFormSLS->hh_1[5]
 + c2.v[23]*MainFormSLS->hh_1[23]
 + c2.v[24]*MainFormSLS->hh_1[41]
 + c2.v[25]*MainFormSLS->hh_1[59]
 + c2.v[26]*MainFormSLS->hh_1[77]
 + c2.v[27]*MainFormSLS->hh_1[95]
 + c2.v[28]*MainFormSLS->hh_1[113]
 + c2.v[29]*MainFormSLS->hh_1[131]
 + c2.v[30]*MainFormSLS->hh_1[149]
 + c2.v[31]*MainFormSLS->hh_1[7]
 + c2.v[32]*MainFormSLS->hh_1[25]
 + c2.v[33]*MainFormSLS->hh_1[43]
 + c2.v[34]*MainFormSLS->hh_1[61]
 + c2.v[35]*MainFormSLS->hh_1[79]
 + c2.v[36]*MainFormSLS->hh_1[97]
 + c2.v[37]*MainFormSLS->hh_1[115]
 + c2.v[38]*MainFormSLS->hh_1[133]
 + c2.v[39]*MainFormSLS->hh_1[151]
 + c2.v[40]*MainFormSLS->hh_1[9]
 + c2.v[41]*MainFormSLS->hh_1[27]
 + c2.v[42]*MainFormSLS->hh_1[45]
 + c2.v[43]*MainFormSLS->hh_1[63]
 + c2.v[44]*MainFormSLS->hh_1[81]
 + c2.v[45]*MainFormSLS->hh_1[99]
 + c2.v[46]*MainFormSLS->hh_1[117]
 + c2.v[47]*MainFormSLS->hh_1[135]
 + c2.v[48]*MainFormSLS->hh_1[153]
 + c2.v[49]*MainFormSLS->hh_1[11]
 + c2.v[50]*MainFormSLS->hh_1[29]
 + c2.v[51]*MainFormSLS->hh_1[47]
 + c2.v[52]*MainFormSLS->hh_1[65]
 + c2.v[53]*MainFormSLS->hh_1[83]
 + c2.v[54]*MainFormSLS->hh_1[101]
 + c2.v[55]*MainFormSLS->hh_1[119]
 + c2.v[56]*MainFormSLS->hh_1[137]
 + c2.v[57]*MainFormSLS->hh_1[155]
 + c2.v[58]*MainFormSLS->hh_1[13]
 + c2.v[59]*MainFormSLS->hh_1[31]
 + c2.v[60]*MainFormSLS->hh_1[49]
 + c2.v[61]*MainFormSLS->hh_1[67]
 + c2.v[62]*MainFormSLS->hh_1[85]
 + c2.v[63]*MainFormSLS->hh_1[103]
 + c2.v[64]*MainFormSLS->hh_1[121]
 + c2.v[65]*MainFormSLS->hh_1[139]
 + c2.v[66]*MainFormSLS->hh_1[157]
 + c2.v[67]*MainFormSLS->hh_1[15]
 + c2.v[68]*MainFormSLS->hh_1[33]
 + c2.v[69]*MainFormSLS->hh_1[51]
 + c2.v[70]*MainFormSLS->hh_1[69]
 + c2.v[71]*MainFormSLS->hh_1[87]
 + c2.v[72]*MainFormSLS->hh_1[105]
 + c2.v[73]*MainFormSLS->hh_1[123]
 + c2.v[74]*MainFormSLS->hh_1[141]
 + c2.v[75]*MainFormSLS->hh_1[159]
 + c2.v[76]*MainFormSLS->hh_1[17]
 + c2.v[77]*MainFormSLS->hh_1[35]
 + c2.v[78]*MainFormSLS->hh_1[53]
 + c2.v[79]*MainFormSLS->hh_1[71];
s/=N_2;
out.push_back(s);
//������ 90
s =c2.v[0]*MainFormSLS->hh_1[90]
 + c2.v[1]*MainFormSLS->hh_1[110]
 + c2.v[2]*MainFormSLS->hh_1[130]
 + c2.v[3]*MainFormSLS->hh_1[150]
 + c2.v[4]*MainFormSLS->hh_1[10]
 + c2.v[5]*MainFormSLS->hh_1[30]
 + c2.v[6]*MainFormSLS->hh_1[50]
 + c2.v[7]*MainFormSLS->hh_1[70]
 + c2.v[8]*MainFormSLS->hh_1[90]
 + c2.v[9]*MainFormSLS->hh_1[110]
 + c2.v[10]*MainFormSLS->hh_1[130]
 + c2.v[11]*MainFormSLS->hh_1[150]
 + c2.v[12]*MainFormSLS->hh_1[10]
 + c2.v[13]*MainFormSLS->hh_1[30]
 + c2.v[14]*MainFormSLS->hh_1[50]
 + c2.v[15]*MainFormSLS->hh_1[70]
 + c2.v[16]*MainFormSLS->hh_1[90]
 + c2.v[17]*MainFormSLS->hh_1[110]
 + c2.v[18]*MainFormSLS->hh_1[130]
 + c2.v[19]*MainFormSLS->hh_1[150]
 + c2.v[20]*MainFormSLS->hh_1[10]
 + c2.v[21]*MainFormSLS->hh_1[30]
 + c2.v[22]*MainFormSLS->hh_1[50]
 + c2.v[23]*MainFormSLS->hh_1[70]
 + c2.v[24]*MainFormSLS->hh_1[90]
 + c2.v[25]*MainFormSLS->hh_1[110]
 + c2.v[26]*MainFormSLS->hh_1[130]
 + c2.v[27]*MainFormSLS->hh_1[150]
 + c2.v[28]*MainFormSLS->hh_1[10]
 + c2.v[29]*MainFormSLS->hh_1[30]
 + c2.v[30]*MainFormSLS->hh_1[50]
 + c2.v[31]*MainFormSLS->hh_1[70]
 + c2.v[32]*MainFormSLS->hh_1[90]
 + c2.v[33]*MainFormSLS->hh_1[110]
 + c2.v[34]*MainFormSLS->hh_1[130]
 + c2.v[35]*MainFormSLS->hh_1[150]
 + c2.v[36]*MainFormSLS->hh_1[10]
 + c2.v[37]*MainFormSLS->hh_1[30]
 + c2.v[38]*MainFormSLS->hh_1[50]
 + c2.v[39]*MainFormSLS->hh_1[70]
 + c2.v[40]*MainFormSLS->hh_1[90]
 + c2.v[41]*MainFormSLS->hh_1[110]
 + c2.v[42]*MainFormSLS->hh_1[130]
 + c2.v[43]*MainFormSLS->hh_1[150]
 + c2.v[44]*MainFormSLS->hh_1[10]
 + c2.v[45]*MainFormSLS->hh_1[30]
 + c2.v[46]*MainFormSLS->hh_1[50]
 + c2.v[47]*MainFormSLS->hh_1[70]
 + c2.v[48]*MainFormSLS->hh_1[90]
 + c2.v[49]*MainFormSLS->hh_1[110]
 + c2.v[50]*MainFormSLS->hh_1[130]
 + c2.v[51]*MainFormSLS->hh_1[150]
 + c2.v[52]*MainFormSLS->hh_1[10]
 + c2.v[53]*MainFormSLS->hh_1[30]
 + c2.v[54]*MainFormSLS->hh_1[50]
 + c2.v[55]*MainFormSLS->hh_1[70]
 + c2.v[56]*MainFormSLS->hh_1[90]
 + c2.v[57]*MainFormSLS->hh_1[110]
 + c2.v[58]*MainFormSLS->hh_1[130]
 + c2.v[59]*MainFormSLS->hh_1[150]
 + c2.v[60]*MainFormSLS->hh_1[10]
 + c2.v[61]*MainFormSLS->hh_1[30]
 + c2.v[62]*MainFormSLS->hh_1[50]
 + c2.v[63]*MainFormSLS->hh_1[70]
 + c2.v[64]*MainFormSLS->hh_1[90]
 + c2.v[65]*MainFormSLS->hh_1[110]
 + c2.v[66]*MainFormSLS->hh_1[130]
 + c2.v[67]*MainFormSLS->hh_1[150]
 + c2.v[68]*MainFormSLS->hh_1[10]
 + c2.v[69]*MainFormSLS->hh_1[30]
 + c2.v[70]*MainFormSLS->hh_1[50]
 + c2.v[71]*MainFormSLS->hh_1[70]
 + c2.v[72]*MainFormSLS->hh_1[90]
 + c2.v[73]*MainFormSLS->hh_1[110]
 + c2.v[74]*MainFormSLS->hh_1[130]
 + c2.v[75]*MainFormSLS->hh_1[150]
 + c2.v[76]*MainFormSLS->hh_1[10]
 + c2.v[77]*MainFormSLS->hh_1[30]
 + c2.v[78]*MainFormSLS->hh_1[50]
 + c2.v[79]*MainFormSLS->hh_1[70];
s/=N_2;
out.push_back(s);
//������ 91
s =c2.v[0]*MainFormSLS->hh_1[91]
 + c2.v[1]*MainFormSLS->hh_1[113]
 + c2.v[2]*MainFormSLS->hh_1[135]
 + c2.v[3]*MainFormSLS->hh_1[157]
 + c2.v[4]*MainFormSLS->hh_1[19]
 + c2.v[5]*MainFormSLS->hh_1[41]
 + c2.v[6]*MainFormSLS->hh_1[63]
 + c2.v[7]*MainFormSLS->hh_1[85]
 + c2.v[8]*MainFormSLS->hh_1[107]
 + c2.v[9]*MainFormSLS->hh_1[129]
 + c2.v[10]*MainFormSLS->hh_1[151]
 + c2.v[11]*MainFormSLS->hh_1[13]
 + c2.v[12]*MainFormSLS->hh_1[35]
 + c2.v[13]*MainFormSLS->hh_1[57]
 + c2.v[14]*MainFormSLS->hh_1[79]
 + c2.v[15]*MainFormSLS->hh_1[101]
 + c2.v[16]*MainFormSLS->hh_1[123]
 + c2.v[17]*MainFormSLS->hh_1[145]
 + c2.v[18]*MainFormSLS->hh_1[7]
 + c2.v[19]*MainFormSLS->hh_1[29]
 + c2.v[20]*MainFormSLS->hh_1[51]
 + c2.v[21]*MainFormSLS->hh_1[73]
 + c2.v[22]*MainFormSLS->hh_1[95]
 + c2.v[23]*MainFormSLS->hh_1[117]
 + c2.v[24]*MainFormSLS->hh_1[139]
 + c2.v[25]*MainFormSLS->hh_1[1]
 + c2.v[26]*MainFormSLS->hh_1[23]
 + c2.v[27]*MainFormSLS->hh_1[45]
 + c2.v[28]*MainFormSLS->hh_1[67]
 + c2.v[29]*MainFormSLS->hh_1[89]
 + c2.v[30]*MainFormSLS->hh_1[111]
 + c2.v[31]*MainFormSLS->hh_1[133]
 + c2.v[32]*MainFormSLS->hh_1[155]
 + c2.v[33]*MainFormSLS->hh_1[17]
 + c2.v[34]*MainFormSLS->hh_1[39]
 + c2.v[35]*MainFormSLS->hh_1[61]
 + c2.v[36]*MainFormSLS->hh_1[83]
 + c2.v[37]*MainFormSLS->hh_1[105]
 + c2.v[38]*MainFormSLS->hh_1[127]
 + c2.v[39]*MainFormSLS->hh_1[149]
 + c2.v[40]*MainFormSLS->hh_1[11]
 + c2.v[41]*MainFormSLS->hh_1[33]
 + c2.v[42]*MainFormSLS->hh_1[55]
 + c2.v[43]*MainFormSLS->hh_1[77]
 + c2.v[44]*MainFormSLS->hh_1[99]
 + c2.v[45]*MainFormSLS->hh_1[121]
 + c2.v[46]*MainFormSLS->hh_1[143]
 + c2.v[47]*MainFormSLS->hh_1[5]
 + c2.v[48]*MainFormSLS->hh_1[27]
 + c2.v[49]*MainFormSLS->hh_1[49]
 + c2.v[50]*MainFormSLS->hh_1[71]
 + c2.v[51]*MainFormSLS->hh_1[93]
 + c2.v[52]*MainFormSLS->hh_1[115]
 + c2.v[53]*MainFormSLS->hh_1[137]
 + c2.v[54]*MainFormSLS->hh_1[159]
 + c2.v[55]*MainFormSLS->hh_1[21]
 + c2.v[56]*MainFormSLS->hh_1[43]
 + c2.v[57]*MainFormSLS->hh_1[65]
 + c2.v[58]*MainFormSLS->hh_1[87]
 + c2.v[59]*MainFormSLS->hh_1[109]
 + c2.v[60]*MainFormSLS->hh_1[131]
 + c2.v[61]*MainFormSLS->hh_1[153]
 + c2.v[62]*MainFormSLS->hh_1[15]
 + c2.v[63]*MainFormSLS->hh_1[37]
 + c2.v[64]*MainFormSLS->hh_1[59]
 + c2.v[65]*MainFormSLS->hh_1[81]
 + c2.v[66]*MainFormSLS->hh_1[103]
 + c2.v[67]*MainFormSLS->hh_1[125]
 + c2.v[68]*MainFormSLS->hh_1[147]
 + c2.v[69]*MainFormSLS->hh_1[9]
 + c2.v[70]*MainFormSLS->hh_1[31]
 + c2.v[71]*MainFormSLS->hh_1[53]
 + c2.v[72]*MainFormSLS->hh_1[75]
 + c2.v[73]*MainFormSLS->hh_1[97]
 + c2.v[74]*MainFormSLS->hh_1[119]
 + c2.v[75]*MainFormSLS->hh_1[141]
 + c2.v[76]*MainFormSLS->hh_1[3]
 + c2.v[77]*MainFormSLS->hh_1[25]
 + c2.v[78]*MainFormSLS->hh_1[47]
 + c2.v[79]*MainFormSLS->hh_1[69];
s/=N_2;
out.push_back(s);
//������ 92
s =c2.v[0]*MainFormSLS->hh_1[92]
 + c2.v[1]*MainFormSLS->hh_1[116]
 + c2.v[2]*MainFormSLS->hh_1[140]
 + c2.v[3]*MainFormSLS->hh_1[4]
 + c2.v[4]*MainFormSLS->hh_1[28]
 + c2.v[5]*MainFormSLS->hh_1[52]
 + c2.v[6]*MainFormSLS->hh_1[76]
 + c2.v[7]*MainFormSLS->hh_1[100]
 + c2.v[8]*MainFormSLS->hh_1[124]
 + c2.v[9]*MainFormSLS->hh_1[148]
 + c2.v[10]*MainFormSLS->hh_1[12]
 + c2.v[11]*MainFormSLS->hh_1[36]
 + c2.v[12]*MainFormSLS->hh_1[60]
 + c2.v[13]*MainFormSLS->hh_1[84]
 + c2.v[14]*MainFormSLS->hh_1[108]
 + c2.v[15]*MainFormSLS->hh_1[132]
 + c2.v[16]*MainFormSLS->hh_1[156]
 + c2.v[17]*MainFormSLS->hh_1[20]
 + c2.v[18]*MainFormSLS->hh_1[44]
 + c2.v[19]*MainFormSLS->hh_1[68]
 + c2.v[20]*MainFormSLS->hh_1[92]
 + c2.v[21]*MainFormSLS->hh_1[116]
 + c2.v[22]*MainFormSLS->hh_1[140]
 + c2.v[23]*MainFormSLS->hh_1[4]
 + c2.v[24]*MainFormSLS->hh_1[28]
 + c2.v[25]*MainFormSLS->hh_1[52]
 + c2.v[26]*MainFormSLS->hh_1[76]
 + c2.v[27]*MainFormSLS->hh_1[100]
 + c2.v[28]*MainFormSLS->hh_1[124]
 + c2.v[29]*MainFormSLS->hh_1[148]
 + c2.v[30]*MainFormSLS->hh_1[12]
 + c2.v[31]*MainFormSLS->hh_1[36]
 + c2.v[32]*MainFormSLS->hh_1[60]
 + c2.v[33]*MainFormSLS->hh_1[84]
 + c2.v[34]*MainFormSLS->hh_1[108]
 + c2.v[35]*MainFormSLS->hh_1[132]
 + c2.v[36]*MainFormSLS->hh_1[156]
 + c2.v[37]*MainFormSLS->hh_1[20]
 + c2.v[38]*MainFormSLS->hh_1[44]
 + c2.v[39]*MainFormSLS->hh_1[68]
 + c2.v[40]*MainFormSLS->hh_1[92]
 + c2.v[41]*MainFormSLS->hh_1[116]
 + c2.v[42]*MainFormSLS->hh_1[140]
 + c2.v[43]*MainFormSLS->hh_1[4]
 + c2.v[44]*MainFormSLS->hh_1[28]
 + c2.v[45]*MainFormSLS->hh_1[52]
 + c2.v[46]*MainFormSLS->hh_1[76]
 + c2.v[47]*MainFormSLS->hh_1[100]
 + c2.v[48]*MainFormSLS->hh_1[124]
 + c2.v[49]*MainFormSLS->hh_1[148]
 + c2.v[50]*MainFormSLS->hh_1[12]
 + c2.v[51]*MainFormSLS->hh_1[36]
 + c2.v[52]*MainFormSLS->hh_1[60]
 + c2.v[53]*MainFormSLS->hh_1[84]
 + c2.v[54]*MainFormSLS->hh_1[108]
 + c2.v[55]*MainFormSLS->hh_1[132]
 + c2.v[56]*MainFormSLS->hh_1[156]
 + c2.v[57]*MainFormSLS->hh_1[20]
 + c2.v[58]*MainFormSLS->hh_1[44]
 + c2.v[59]*MainFormSLS->hh_1[68]
 + c2.v[60]*MainFormSLS->hh_1[92]
 + c2.v[61]*MainFormSLS->hh_1[116]
 + c2.v[62]*MainFormSLS->hh_1[140]
 + c2.v[63]*MainFormSLS->hh_1[4]
 + c2.v[64]*MainFormSLS->hh_1[28]
 + c2.v[65]*MainFormSLS->hh_1[52]
 + c2.v[66]*MainFormSLS->hh_1[76]
 + c2.v[67]*MainFormSLS->hh_1[100]
 + c2.v[68]*MainFormSLS->hh_1[124]
 + c2.v[69]*MainFormSLS->hh_1[148]
 + c2.v[70]*MainFormSLS->hh_1[12]
 + c2.v[71]*MainFormSLS->hh_1[36]
 + c2.v[72]*MainFormSLS->hh_1[60]
 + c2.v[73]*MainFormSLS->hh_1[84]
 + c2.v[74]*MainFormSLS->hh_1[108]
 + c2.v[75]*MainFormSLS->hh_1[132]
 + c2.v[76]*MainFormSLS->hh_1[156]
 + c2.v[77]*MainFormSLS->hh_1[20]
 + c2.v[78]*MainFormSLS->hh_1[44]
 + c2.v[79]*MainFormSLS->hh_1[68];
s/=N_2;
out.push_back(s);
//������ 93
s =c2.v[0]*MainFormSLS->hh_1[93]
 + c2.v[1]*MainFormSLS->hh_1[119]
 + c2.v[2]*MainFormSLS->hh_1[145]
 + c2.v[3]*MainFormSLS->hh_1[11]
 + c2.v[4]*MainFormSLS->hh_1[37]
 + c2.v[5]*MainFormSLS->hh_1[63]
 + c2.v[6]*MainFormSLS->hh_1[89]
 + c2.v[7]*MainFormSLS->hh_1[115]
 + c2.v[8]*MainFormSLS->hh_1[141]
 + c2.v[9]*MainFormSLS->hh_1[7]
 + c2.v[10]*MainFormSLS->hh_1[33]
 + c2.v[11]*MainFormSLS->hh_1[59]
 + c2.v[12]*MainFormSLS->hh_1[85]
 + c2.v[13]*MainFormSLS->hh_1[111]
 + c2.v[14]*MainFormSLS->hh_1[137]
 + c2.v[15]*MainFormSLS->hh_1[3]
 + c2.v[16]*MainFormSLS->hh_1[29]
 + c2.v[17]*MainFormSLS->hh_1[55]
 + c2.v[18]*MainFormSLS->hh_1[81]
 + c2.v[19]*MainFormSLS->hh_1[107]
 + c2.v[20]*MainFormSLS->hh_1[133]
 + c2.v[21]*MainFormSLS->hh_1[159]
 + c2.v[22]*MainFormSLS->hh_1[25]
 + c2.v[23]*MainFormSLS->hh_1[51]
 + c2.v[24]*MainFormSLS->hh_1[77]
 + c2.v[25]*MainFormSLS->hh_1[103]
 + c2.v[26]*MainFormSLS->hh_1[129]
 + c2.v[27]*MainFormSLS->hh_1[155]
 + c2.v[28]*MainFormSLS->hh_1[21]
 + c2.v[29]*MainFormSLS->hh_1[47]
 + c2.v[30]*MainFormSLS->hh_1[73]
 + c2.v[31]*MainFormSLS->hh_1[99]
 + c2.v[32]*MainFormSLS->hh_1[125]
 + c2.v[33]*MainFormSLS->hh_1[151]
 + c2.v[34]*MainFormSLS->hh_1[17]
 + c2.v[35]*MainFormSLS->hh_1[43]
 + c2.v[36]*MainFormSLS->hh_1[69]
 + c2.v[37]*MainFormSLS->hh_1[95]
 + c2.v[38]*MainFormSLS->hh_1[121]
 + c2.v[39]*MainFormSLS->hh_1[147]
 + c2.v[40]*MainFormSLS->hh_1[13]
 + c2.v[41]*MainFormSLS->hh_1[39]
 + c2.v[42]*MainFormSLS->hh_1[65]
 + c2.v[43]*MainFormSLS->hh_1[91]
 + c2.v[44]*MainFormSLS->hh_1[117]
 + c2.v[45]*MainFormSLS->hh_1[143]
 + c2.v[46]*MainFormSLS->hh_1[9]
 + c2.v[47]*MainFormSLS->hh_1[35]
 + c2.v[48]*MainFormSLS->hh_1[61]
 + c2.v[49]*MainFormSLS->hh_1[87]
 + c2.v[50]*MainFormSLS->hh_1[113]
 + c2.v[51]*MainFormSLS->hh_1[139]
 + c2.v[52]*MainFormSLS->hh_1[5]
 + c2.v[53]*MainFormSLS->hh_1[31]
 + c2.v[54]*MainFormSLS->hh_1[57]
 + c2.v[55]*MainFormSLS->hh_1[83]
 + c2.v[56]*MainFormSLS->hh_1[109]
 + c2.v[57]*MainFormSLS->hh_1[135]
 + c2.v[58]*MainFormSLS->hh_1[1]
 + c2.v[59]*MainFormSLS->hh_1[27]
 + c2.v[60]*MainFormSLS->hh_1[53]
 + c2.v[61]*MainFormSLS->hh_1[79]
 + c2.v[62]*MainFormSLS->hh_1[105]
 + c2.v[63]*MainFormSLS->hh_1[131]
 + c2.v[64]*MainFormSLS->hh_1[157]
 + c2.v[65]*MainFormSLS->hh_1[23]
 + c2.v[66]*MainFormSLS->hh_1[49]
 + c2.v[67]*MainFormSLS->hh_1[75]
 + c2.v[68]*MainFormSLS->hh_1[101]
 + c2.v[69]*MainFormSLS->hh_1[127]
 + c2.v[70]*MainFormSLS->hh_1[153]
 + c2.v[71]*MainFormSLS->hh_1[19]
 + c2.v[72]*MainFormSLS->hh_1[45]
 + c2.v[73]*MainFormSLS->hh_1[71]
 + c2.v[74]*MainFormSLS->hh_1[97]
 + c2.v[75]*MainFormSLS->hh_1[123]
 + c2.v[76]*MainFormSLS->hh_1[149]
 + c2.v[77]*MainFormSLS->hh_1[15]
 + c2.v[78]*MainFormSLS->hh_1[41]
 + c2.v[79]*MainFormSLS->hh_1[67];
s/=N_2;
out.push_back(s);
//������ 94
s =c2.v[0]*MainFormSLS->hh_1[94]
 + c2.v[1]*MainFormSLS->hh_1[122]
 + c2.v[2]*MainFormSLS->hh_1[150]
 + c2.v[3]*MainFormSLS->hh_1[18]
 + c2.v[4]*MainFormSLS->hh_1[46]
 + c2.v[5]*MainFormSLS->hh_1[74]
 + c2.v[6]*MainFormSLS->hh_1[102]
 + c2.v[7]*MainFormSLS->hh_1[130]
 + c2.v[8]*MainFormSLS->hh_1[158]
 + c2.v[9]*MainFormSLS->hh_1[26]
 + c2.v[10]*MainFormSLS->hh_1[54]
 + c2.v[11]*MainFormSLS->hh_1[82]
 + c2.v[12]*MainFormSLS->hh_1[110]
 + c2.v[13]*MainFormSLS->hh_1[138]
 + c2.v[14]*MainFormSLS->hh_1[6]
 + c2.v[15]*MainFormSLS->hh_1[34]
 + c2.v[16]*MainFormSLS->hh_1[62]
 + c2.v[17]*MainFormSLS->hh_1[90]
 + c2.v[18]*MainFormSLS->hh_1[118]
 + c2.v[19]*MainFormSLS->hh_1[146]
 + c2.v[20]*MainFormSLS->hh_1[14]
 + c2.v[21]*MainFormSLS->hh_1[42]
 + c2.v[22]*MainFormSLS->hh_1[70]
 + c2.v[23]*MainFormSLS->hh_1[98]
 + c2.v[24]*MainFormSLS->hh_1[126]
 + c2.v[25]*MainFormSLS->hh_1[154]
 + c2.v[26]*MainFormSLS->hh_1[22]
 + c2.v[27]*MainFormSLS->hh_1[50]
 + c2.v[28]*MainFormSLS->hh_1[78]
 + c2.v[29]*MainFormSLS->hh_1[106]
 + c2.v[30]*MainFormSLS->hh_1[134]
 + c2.v[31]*MainFormSLS->hh_1[2]
 + c2.v[32]*MainFormSLS->hh_1[30]
 + c2.v[33]*MainFormSLS->hh_1[58]
 + c2.v[34]*MainFormSLS->hh_1[86]
 + c2.v[35]*MainFormSLS->hh_1[114]
 + c2.v[36]*MainFormSLS->hh_1[142]
 + c2.v[37]*MainFormSLS->hh_1[10]
 + c2.v[38]*MainFormSLS->hh_1[38]
 + c2.v[39]*MainFormSLS->hh_1[66]
 + c2.v[40]*MainFormSLS->hh_1[94]
 + c2.v[41]*MainFormSLS->hh_1[122]
 + c2.v[42]*MainFormSLS->hh_1[150]
 + c2.v[43]*MainFormSLS->hh_1[18]
 + c2.v[44]*MainFormSLS->hh_1[46]
 + c2.v[45]*MainFormSLS->hh_1[74]
 + c2.v[46]*MainFormSLS->hh_1[102]
 + c2.v[47]*MainFormSLS->hh_1[130]
 + c2.v[48]*MainFormSLS->hh_1[158]
 + c2.v[49]*MainFormSLS->hh_1[26]
 + c2.v[50]*MainFormSLS->hh_1[54]
 + c2.v[51]*MainFormSLS->hh_1[82]
 + c2.v[52]*MainFormSLS->hh_1[110]
 + c2.v[53]*MainFormSLS->hh_1[138]
 + c2.v[54]*MainFormSLS->hh_1[6]
 + c2.v[55]*MainFormSLS->hh_1[34]
 + c2.v[56]*MainFormSLS->hh_1[62]
 + c2.v[57]*MainFormSLS->hh_1[90]
 + c2.v[58]*MainFormSLS->hh_1[118]
 + c2.v[59]*MainFormSLS->hh_1[146]
 + c2.v[60]*MainFormSLS->hh_1[14]
 + c2.v[61]*MainFormSLS->hh_1[42]
 + c2.v[62]*MainFormSLS->hh_1[70]
 + c2.v[63]*MainFormSLS->hh_1[98]
 + c2.v[64]*MainFormSLS->hh_1[126]
 + c2.v[65]*MainFormSLS->hh_1[154]
 + c2.v[66]*MainFormSLS->hh_1[22]
 + c2.v[67]*MainFormSLS->hh_1[50]
 + c2.v[68]*MainFormSLS->hh_1[78]
 + c2.v[69]*MainFormSLS->hh_1[106]
 + c2.v[70]*MainFormSLS->hh_1[134]
 + c2.v[71]*MainFormSLS->hh_1[2]
 + c2.v[72]*MainFormSLS->hh_1[30]
 + c2.v[73]*MainFormSLS->hh_1[58]
 + c2.v[74]*MainFormSLS->hh_1[86]
 + c2.v[75]*MainFormSLS->hh_1[114]
 + c2.v[76]*MainFormSLS->hh_1[142]
 + c2.v[77]*MainFormSLS->hh_1[10]
 + c2.v[78]*MainFormSLS->hh_1[38]
 + c2.v[79]*MainFormSLS->hh_1[66];
s/=N_2;
out.push_back(s);
//������ 95
s =c2.v[0]*MainFormSLS->hh_1[95]
 + c2.v[1]*MainFormSLS->hh_1[125]
 + c2.v[2]*MainFormSLS->hh_1[155]
 + c2.v[3]*MainFormSLS->hh_1[25]
 + c2.v[4]*MainFormSLS->hh_1[55]
 + c2.v[5]*MainFormSLS->hh_1[85]
 + c2.v[6]*MainFormSLS->hh_1[115]
 + c2.v[7]*MainFormSLS->hh_1[145]
 + c2.v[8]*MainFormSLS->hh_1[15]
 + c2.v[9]*MainFormSLS->hh_1[45]
 + c2.v[10]*MainFormSLS->hh_1[75]
 + c2.v[11]*MainFormSLS->hh_1[105]
 + c2.v[12]*MainFormSLS->hh_1[135]
 + c2.v[13]*MainFormSLS->hh_1[5]
 + c2.v[14]*MainFormSLS->hh_1[35]
 + c2.v[15]*MainFormSLS->hh_1[65]
 + c2.v[16]*MainFormSLS->hh_1[95]
 + c2.v[17]*MainFormSLS->hh_1[125]
 + c2.v[18]*MainFormSLS->hh_1[155]
 + c2.v[19]*MainFormSLS->hh_1[25]
 + c2.v[20]*MainFormSLS->hh_1[55]
 + c2.v[21]*MainFormSLS->hh_1[85]
 + c2.v[22]*MainFormSLS->hh_1[115]
 + c2.v[23]*MainFormSLS->hh_1[145]
 + c2.v[24]*MainFormSLS->hh_1[15]
 + c2.v[25]*MainFormSLS->hh_1[45]
 + c2.v[26]*MainFormSLS->hh_1[75]
 + c2.v[27]*MainFormSLS->hh_1[105]
 + c2.v[28]*MainFormSLS->hh_1[135]
 + c2.v[29]*MainFormSLS->hh_1[5]
 + c2.v[30]*MainFormSLS->hh_1[35]
 + c2.v[31]*MainFormSLS->hh_1[65]
 + c2.v[32]*MainFormSLS->hh_1[95]
 + c2.v[33]*MainFormSLS->hh_1[125]
 + c2.v[34]*MainFormSLS->hh_1[155]
 + c2.v[35]*MainFormSLS->hh_1[25]
 + c2.v[36]*MainFormSLS->hh_1[55]
 + c2.v[37]*MainFormSLS->hh_1[85]
 + c2.v[38]*MainFormSLS->hh_1[115]
 + c2.v[39]*MainFormSLS->hh_1[145]
 + c2.v[40]*MainFormSLS->hh_1[15]
 + c2.v[41]*MainFormSLS->hh_1[45]
 + c2.v[42]*MainFormSLS->hh_1[75]
 + c2.v[43]*MainFormSLS->hh_1[105]
 + c2.v[44]*MainFormSLS->hh_1[135]
 + c2.v[45]*MainFormSLS->hh_1[5]
 + c2.v[46]*MainFormSLS->hh_1[35]
 + c2.v[47]*MainFormSLS->hh_1[65]
 + c2.v[48]*MainFormSLS->hh_1[95]
 + c2.v[49]*MainFormSLS->hh_1[125]
 + c2.v[50]*MainFormSLS->hh_1[155]
 + c2.v[51]*MainFormSLS->hh_1[25]
 + c2.v[52]*MainFormSLS->hh_1[55]
 + c2.v[53]*MainFormSLS->hh_1[85]
 + c2.v[54]*MainFormSLS->hh_1[115]
 + c2.v[55]*MainFormSLS->hh_1[145]
 + c2.v[56]*MainFormSLS->hh_1[15]
 + c2.v[57]*MainFormSLS->hh_1[45]
 + c2.v[58]*MainFormSLS->hh_1[75]
 + c2.v[59]*MainFormSLS->hh_1[105]
 + c2.v[60]*MainFormSLS->hh_1[135]
 + c2.v[61]*MainFormSLS->hh_1[5]
 + c2.v[62]*MainFormSLS->hh_1[35]
 + c2.v[63]*MainFormSLS->hh_1[65]
 + c2.v[64]*MainFormSLS->hh_1[95]
 + c2.v[65]*MainFormSLS->hh_1[125]
 + c2.v[66]*MainFormSLS->hh_1[155]
 + c2.v[67]*MainFormSLS->hh_1[25]
 + c2.v[68]*MainFormSLS->hh_1[55]
 + c2.v[69]*MainFormSLS->hh_1[85]
 + c2.v[70]*MainFormSLS->hh_1[115]
 + c2.v[71]*MainFormSLS->hh_1[145]
 + c2.v[72]*MainFormSLS->hh_1[15]
 + c2.v[73]*MainFormSLS->hh_1[45]
 + c2.v[74]*MainFormSLS->hh_1[75]
 + c2.v[75]*MainFormSLS->hh_1[105]
 + c2.v[76]*MainFormSLS->hh_1[135]
 + c2.v[77]*MainFormSLS->hh_1[5]
 + c2.v[78]*MainFormSLS->hh_1[35]
 + c2.v[79]*MainFormSLS->hh_1[65];
s/=N_2;
out.push_back(s);
//������ 96
s =c2.v[0]*MainFormSLS->hh_1[96]
 + c2.v[1]*MainFormSLS->hh_1[128]
 + c2.v[2]*MainFormSLS->hh_1[0]
 + c2.v[3]*MainFormSLS->hh_1[32]
 + c2.v[4]*MainFormSLS->hh_1[64]
 + c2.v[5]*MainFormSLS->hh_1[96]
 + c2.v[6]*MainFormSLS->hh_1[128]
 + c2.v[7]*MainFormSLS->hh_1[0]
 + c2.v[8]*MainFormSLS->hh_1[32]
 + c2.v[9]*MainFormSLS->hh_1[64]
 + c2.v[10]*MainFormSLS->hh_1[96]
 + c2.v[11]*MainFormSLS->hh_1[128]
 + c2.v[12]*MainFormSLS->hh_1[0]
 + c2.v[13]*MainFormSLS->hh_1[32]
 + c2.v[14]*MainFormSLS->hh_1[64]
 + c2.v[15]*MainFormSLS->hh_1[96]
 + c2.v[16]*MainFormSLS->hh_1[128]
 + c2.v[17]*MainFormSLS->hh_1[0]
 + c2.v[18]*MainFormSLS->hh_1[32]
 + c2.v[19]*MainFormSLS->hh_1[64]
 + c2.v[20]*MainFormSLS->hh_1[96]
 + c2.v[21]*MainFormSLS->hh_1[128]
 + c2.v[22]*MainFormSLS->hh_1[0]
 + c2.v[23]*MainFormSLS->hh_1[32]
 + c2.v[24]*MainFormSLS->hh_1[64]
 + c2.v[25]*MainFormSLS->hh_1[96]
 + c2.v[26]*MainFormSLS->hh_1[128]
 + c2.v[27]*MainFormSLS->hh_1[0]
 + c2.v[28]*MainFormSLS->hh_1[32]
 + c2.v[29]*MainFormSLS->hh_1[64]
 + c2.v[30]*MainFormSLS->hh_1[96]
 + c2.v[31]*MainFormSLS->hh_1[128]
 + c2.v[32]*MainFormSLS->hh_1[0]
 + c2.v[33]*MainFormSLS->hh_1[32]
 + c2.v[34]*MainFormSLS->hh_1[64]
 + c2.v[35]*MainFormSLS->hh_1[96]
 + c2.v[36]*MainFormSLS->hh_1[128]
 + c2.v[37]*MainFormSLS->hh_1[0]
 + c2.v[38]*MainFormSLS->hh_1[32]
 + c2.v[39]*MainFormSLS->hh_1[64]
 + c2.v[40]*MainFormSLS->hh_1[96]
 + c2.v[41]*MainFormSLS->hh_1[128]
 + c2.v[42]*MainFormSLS->hh_1[0]
 + c2.v[43]*MainFormSLS->hh_1[32]
 + c2.v[44]*MainFormSLS->hh_1[64]
 + c2.v[45]*MainFormSLS->hh_1[96]
 + c2.v[46]*MainFormSLS->hh_1[128]
 + c2.v[47]*MainFormSLS->hh_1[0]
 + c2.v[48]*MainFormSLS->hh_1[32]
 + c2.v[49]*MainFormSLS->hh_1[64]
 + c2.v[50]*MainFormSLS->hh_1[96]
 + c2.v[51]*MainFormSLS->hh_1[128]
 + c2.v[52]*MainFormSLS->hh_1[0]
 + c2.v[53]*MainFormSLS->hh_1[32]
 + c2.v[54]*MainFormSLS->hh_1[64]
 + c2.v[55]*MainFormSLS->hh_1[96]
 + c2.v[56]*MainFormSLS->hh_1[128]
 + c2.v[57]*MainFormSLS->hh_1[0]
 + c2.v[58]*MainFormSLS->hh_1[32]
 + c2.v[59]*MainFormSLS->hh_1[64]
 + c2.v[60]*MainFormSLS->hh_1[96]
 + c2.v[61]*MainFormSLS->hh_1[128]
 + c2.v[62]*MainFormSLS->hh_1[0]
 + c2.v[63]*MainFormSLS->hh_1[32]
 + c2.v[64]*MainFormSLS->hh_1[64]
 + c2.v[65]*MainFormSLS->hh_1[96]
 + c2.v[66]*MainFormSLS->hh_1[128]
 + c2.v[67]*MainFormSLS->hh_1[0]
 + c2.v[68]*MainFormSLS->hh_1[32]
 + c2.v[69]*MainFormSLS->hh_1[64]
 + c2.v[70]*MainFormSLS->hh_1[96]
 + c2.v[71]*MainFormSLS->hh_1[128]
 + c2.v[72]*MainFormSLS->hh_1[0]
 + c2.v[73]*MainFormSLS->hh_1[32]
 + c2.v[74]*MainFormSLS->hh_1[64]
 + c2.v[75]*MainFormSLS->hh_1[96]
 + c2.v[76]*MainFormSLS->hh_1[128]
 + c2.v[77]*MainFormSLS->hh_1[0]
 + c2.v[78]*MainFormSLS->hh_1[32]
 + c2.v[79]*MainFormSLS->hh_1[64];
s/=N_2;
out.push_back(s);
//������ 97
s =c2.v[0]*MainFormSLS->hh_1[97]
 + c2.v[1]*MainFormSLS->hh_1[131]
 + c2.v[2]*MainFormSLS->hh_1[5]
 + c2.v[3]*MainFormSLS->hh_1[39]
 + c2.v[4]*MainFormSLS->hh_1[73]
 + c2.v[5]*MainFormSLS->hh_1[107]
 + c2.v[6]*MainFormSLS->hh_1[141]
 + c2.v[7]*MainFormSLS->hh_1[15]
 + c2.v[8]*MainFormSLS->hh_1[49]
 + c2.v[9]*MainFormSLS->hh_1[83]
 + c2.v[10]*MainFormSLS->hh_1[117]
 + c2.v[11]*MainFormSLS->hh_1[151]
 + c2.v[12]*MainFormSLS->hh_1[25]
 + c2.v[13]*MainFormSLS->hh_1[59]
 + c2.v[14]*MainFormSLS->hh_1[93]
 + c2.v[15]*MainFormSLS->hh_1[127]
 + c2.v[16]*MainFormSLS->hh_1[1]
 + c2.v[17]*MainFormSLS->hh_1[35]
 + c2.v[18]*MainFormSLS->hh_1[69]
 + c2.v[19]*MainFormSLS->hh_1[103]
 + c2.v[20]*MainFormSLS->hh_1[137]
 + c2.v[21]*MainFormSLS->hh_1[11]
 + c2.v[22]*MainFormSLS->hh_1[45]
 + c2.v[23]*MainFormSLS->hh_1[79]
 + c2.v[24]*MainFormSLS->hh_1[113]
 + c2.v[25]*MainFormSLS->hh_1[147]
 + c2.v[26]*MainFormSLS->hh_1[21]
 + c2.v[27]*MainFormSLS->hh_1[55]
 + c2.v[28]*MainFormSLS->hh_1[89]
 + c2.v[29]*MainFormSLS->hh_1[123]
 + c2.v[30]*MainFormSLS->hh_1[157]
 + c2.v[31]*MainFormSLS->hh_1[31]
 + c2.v[32]*MainFormSLS->hh_1[65]
 + c2.v[33]*MainFormSLS->hh_1[99]
 + c2.v[34]*MainFormSLS->hh_1[133]
 + c2.v[35]*MainFormSLS->hh_1[7]
 + c2.v[36]*MainFormSLS->hh_1[41]
 + c2.v[37]*MainFormSLS->hh_1[75]
 + c2.v[38]*MainFormSLS->hh_1[109]
 + c2.v[39]*MainFormSLS->hh_1[143]
 + c2.v[40]*MainFormSLS->hh_1[17]
 + c2.v[41]*MainFormSLS->hh_1[51]
 + c2.v[42]*MainFormSLS->hh_1[85]
 + c2.v[43]*MainFormSLS->hh_1[119]
 + c2.v[44]*MainFormSLS->hh_1[153]
 + c2.v[45]*MainFormSLS->hh_1[27]
 + c2.v[46]*MainFormSLS->hh_1[61]
 + c2.v[47]*MainFormSLS->hh_1[95]
 + c2.v[48]*MainFormSLS->hh_1[129]
 + c2.v[49]*MainFormSLS->hh_1[3]
 + c2.v[50]*MainFormSLS->hh_1[37]
 + c2.v[51]*MainFormSLS->hh_1[71]
 + c2.v[52]*MainFormSLS->hh_1[105]
 + c2.v[53]*MainFormSLS->hh_1[139]
 + c2.v[54]*MainFormSLS->hh_1[13]
 + c2.v[55]*MainFormSLS->hh_1[47]
 + c2.v[56]*MainFormSLS->hh_1[81]
 + c2.v[57]*MainFormSLS->hh_1[115]
 + c2.v[58]*MainFormSLS->hh_1[149]
 + c2.v[59]*MainFormSLS->hh_1[23]
 + c2.v[60]*MainFormSLS->hh_1[57]
 + c2.v[61]*MainFormSLS->hh_1[91]
 + c2.v[62]*MainFormSLS->hh_1[125]
 + c2.v[63]*MainFormSLS->hh_1[159]
 + c2.v[64]*MainFormSLS->hh_1[33]
 + c2.v[65]*MainFormSLS->hh_1[67]
 + c2.v[66]*MainFormSLS->hh_1[101]
 + c2.v[67]*MainFormSLS->hh_1[135]
 + c2.v[68]*MainFormSLS->hh_1[9]
 + c2.v[69]*MainFormSLS->hh_1[43]
 + c2.v[70]*MainFormSLS->hh_1[77]
 + c2.v[71]*MainFormSLS->hh_1[111]
 + c2.v[72]*MainFormSLS->hh_1[145]
 + c2.v[73]*MainFormSLS->hh_1[19]
 + c2.v[74]*MainFormSLS->hh_1[53]
 + c2.v[75]*MainFormSLS->hh_1[87]
 + c2.v[76]*MainFormSLS->hh_1[121]
 + c2.v[77]*MainFormSLS->hh_1[155]
 + c2.v[78]*MainFormSLS->hh_1[29]
 + c2.v[79]*MainFormSLS->hh_1[63];
s/=N_2;
out.push_back(s);
//������ 98
s =c2.v[0]*MainFormSLS->hh_1[98]
 + c2.v[1]*MainFormSLS->hh_1[134]
 + c2.v[2]*MainFormSLS->hh_1[10]
 + c2.v[3]*MainFormSLS->hh_1[46]
 + c2.v[4]*MainFormSLS->hh_1[82]
 + c2.v[5]*MainFormSLS->hh_1[118]
 + c2.v[6]*MainFormSLS->hh_1[154]
 + c2.v[7]*MainFormSLS->hh_1[30]
 + c2.v[8]*MainFormSLS->hh_1[66]
 + c2.v[9]*MainFormSLS->hh_1[102]
 + c2.v[10]*MainFormSLS->hh_1[138]
 + c2.v[11]*MainFormSLS->hh_1[14]
 + c2.v[12]*MainFormSLS->hh_1[50]
 + c2.v[13]*MainFormSLS->hh_1[86]
 + c2.v[14]*MainFormSLS->hh_1[122]
 + c2.v[15]*MainFormSLS->hh_1[158]
 + c2.v[16]*MainFormSLS->hh_1[34]
 + c2.v[17]*MainFormSLS->hh_1[70]
 + c2.v[18]*MainFormSLS->hh_1[106]
 + c2.v[19]*MainFormSLS->hh_1[142]
 + c2.v[20]*MainFormSLS->hh_1[18]
 + c2.v[21]*MainFormSLS->hh_1[54]
 + c2.v[22]*MainFormSLS->hh_1[90]
 + c2.v[23]*MainFormSLS->hh_1[126]
 + c2.v[24]*MainFormSLS->hh_1[2]
 + c2.v[25]*MainFormSLS->hh_1[38]
 + c2.v[26]*MainFormSLS->hh_1[74]
 + c2.v[27]*MainFormSLS->hh_1[110]
 + c2.v[28]*MainFormSLS->hh_1[146]
 + c2.v[29]*MainFormSLS->hh_1[22]
 + c2.v[30]*MainFormSLS->hh_1[58]
 + c2.v[31]*MainFormSLS->hh_1[94]
 + c2.v[32]*MainFormSLS->hh_1[130]
 + c2.v[33]*MainFormSLS->hh_1[6]
 + c2.v[34]*MainFormSLS->hh_1[42]
 + c2.v[35]*MainFormSLS->hh_1[78]
 + c2.v[36]*MainFormSLS->hh_1[114]
 + c2.v[37]*MainFormSLS->hh_1[150]
 + c2.v[38]*MainFormSLS->hh_1[26]
 + c2.v[39]*MainFormSLS->hh_1[62]
 + c2.v[40]*MainFormSLS->hh_1[98]
 + c2.v[41]*MainFormSLS->hh_1[134]
 + c2.v[42]*MainFormSLS->hh_1[10]
 + c2.v[43]*MainFormSLS->hh_1[46]
 + c2.v[44]*MainFormSLS->hh_1[82]
 + c2.v[45]*MainFormSLS->hh_1[118]
 + c2.v[46]*MainFormSLS->hh_1[154]
 + c2.v[47]*MainFormSLS->hh_1[30]
 + c2.v[48]*MainFormSLS->hh_1[66]
 + c2.v[49]*MainFormSLS->hh_1[102]
 + c2.v[50]*MainFormSLS->hh_1[138]
 + c2.v[51]*MainFormSLS->hh_1[14]
 + c2.v[52]*MainFormSLS->hh_1[50]
 + c2.v[53]*MainFormSLS->hh_1[86]
 + c2.v[54]*MainFormSLS->hh_1[122]
 + c2.v[55]*MainFormSLS->hh_1[158]
 + c2.v[56]*MainFormSLS->hh_1[34]
 + c2.v[57]*MainFormSLS->hh_1[70]
 + c2.v[58]*MainFormSLS->hh_1[106]
 + c2.v[59]*MainFormSLS->hh_1[142]
 + c2.v[60]*MainFormSLS->hh_1[18]
 + c2.v[61]*MainFormSLS->hh_1[54]
 + c2.v[62]*MainFormSLS->hh_1[90]
 + c2.v[63]*MainFormSLS->hh_1[126]
 + c2.v[64]*MainFormSLS->hh_1[2]
 + c2.v[65]*MainFormSLS->hh_1[38]
 + c2.v[66]*MainFormSLS->hh_1[74]
 + c2.v[67]*MainFormSLS->hh_1[110]
 + c2.v[68]*MainFormSLS->hh_1[146]
 + c2.v[69]*MainFormSLS->hh_1[22]
 + c2.v[70]*MainFormSLS->hh_1[58]
 + c2.v[71]*MainFormSLS->hh_1[94]
 + c2.v[72]*MainFormSLS->hh_1[130]
 + c2.v[73]*MainFormSLS->hh_1[6]
 + c2.v[74]*MainFormSLS->hh_1[42]
 + c2.v[75]*MainFormSLS->hh_1[78]
 + c2.v[76]*MainFormSLS->hh_1[114]
 + c2.v[77]*MainFormSLS->hh_1[150]
 + c2.v[78]*MainFormSLS->hh_1[26]
 + c2.v[79]*MainFormSLS->hh_1[62];
s/=N_2;
out.push_back(s);
//������ 99
s =c2.v[0]*MainFormSLS->hh_1[99]
 + c2.v[1]*MainFormSLS->hh_1[137]
 + c2.v[2]*MainFormSLS->hh_1[15]
 + c2.v[3]*MainFormSLS->hh_1[53]
 + c2.v[4]*MainFormSLS->hh_1[91]
 + c2.v[5]*MainFormSLS->hh_1[129]
 + c2.v[6]*MainFormSLS->hh_1[7]
 + c2.v[7]*MainFormSLS->hh_1[45]
 + c2.v[8]*MainFormSLS->hh_1[83]
 + c2.v[9]*MainFormSLS->hh_1[121]
 + c2.v[10]*MainFormSLS->hh_1[159]
 + c2.v[11]*MainFormSLS->hh_1[37]
 + c2.v[12]*MainFormSLS->hh_1[75]
 + c2.v[13]*MainFormSLS->hh_1[113]
 + c2.v[14]*MainFormSLS->hh_1[151]
 + c2.v[15]*MainFormSLS->hh_1[29]
 + c2.v[16]*MainFormSLS->hh_1[67]
 + c2.v[17]*MainFormSLS->hh_1[105]
 + c2.v[18]*MainFormSLS->hh_1[143]
 + c2.v[19]*MainFormSLS->hh_1[21]
 + c2.v[20]*MainFormSLS->hh_1[59]
 + c2.v[21]*MainFormSLS->hh_1[97]
 + c2.v[22]*MainFormSLS->hh_1[135]
 + c2.v[23]*MainFormSLS->hh_1[13]
 + c2.v[24]*MainFormSLS->hh_1[51]
 + c2.v[25]*MainFormSLS->hh_1[89]
 + c2.v[26]*MainFormSLS->hh_1[127]
 + c2.v[27]*MainFormSLS->hh_1[5]
 + c2.v[28]*MainFormSLS->hh_1[43]
 + c2.v[29]*MainFormSLS->hh_1[81]
 + c2.v[30]*MainFormSLS->hh_1[119]
 + c2.v[31]*MainFormSLS->hh_1[157]
 + c2.v[32]*MainFormSLS->hh_1[35]
 + c2.v[33]*MainFormSLS->hh_1[73]
 + c2.v[34]*MainFormSLS->hh_1[111]
 + c2.v[35]*MainFormSLS->hh_1[149]
 + c2.v[36]*MainFormSLS->hh_1[27]
 + c2.v[37]*MainFormSLS->hh_1[65]
 + c2.v[38]*MainFormSLS->hh_1[103]
 + c2.v[39]*MainFormSLS->hh_1[141]
 + c2.v[40]*MainFormSLS->hh_1[19]
 + c2.v[41]*MainFormSLS->hh_1[57]
 + c2.v[42]*MainFormSLS->hh_1[95]
 + c2.v[43]*MainFormSLS->hh_1[133]
 + c2.v[44]*MainFormSLS->hh_1[11]
 + c2.v[45]*MainFormSLS->hh_1[49]
 + c2.v[46]*MainFormSLS->hh_1[87]
 + c2.v[47]*MainFormSLS->hh_1[125]
 + c2.v[48]*MainFormSLS->hh_1[3]
 + c2.v[49]*MainFormSLS->hh_1[41]
 + c2.v[50]*MainFormSLS->hh_1[79]
 + c2.v[51]*MainFormSLS->hh_1[117]
 + c2.v[52]*MainFormSLS->hh_1[155]
 + c2.v[53]*MainFormSLS->hh_1[33]
 + c2.v[54]*MainFormSLS->hh_1[71]
 + c2.v[55]*MainFormSLS->hh_1[109]
 + c2.v[56]*MainFormSLS->hh_1[147]
 + c2.v[57]*MainFormSLS->hh_1[25]
 + c2.v[58]*MainFormSLS->hh_1[63]
 + c2.v[59]*MainFormSLS->hh_1[101]
 + c2.v[60]*MainFormSLS->hh_1[139]
 + c2.v[61]*MainFormSLS->hh_1[17]
 + c2.v[62]*MainFormSLS->hh_1[55]
 + c2.v[63]*MainFormSLS->hh_1[93]
 + c2.v[64]*MainFormSLS->hh_1[131]
 + c2.v[65]*MainFormSLS->hh_1[9]
 + c2.v[66]*MainFormSLS->hh_1[47]
 + c2.v[67]*MainFormSLS->hh_1[85]
 + c2.v[68]*MainFormSLS->hh_1[123]
 + c2.v[69]*MainFormSLS->hh_1[1]
 + c2.v[70]*MainFormSLS->hh_1[39]
 + c2.v[71]*MainFormSLS->hh_1[77]
 + c2.v[72]*MainFormSLS->hh_1[115]
 + c2.v[73]*MainFormSLS->hh_1[153]
 + c2.v[74]*MainFormSLS->hh_1[31]
 + c2.v[75]*MainFormSLS->hh_1[69]
 + c2.v[76]*MainFormSLS->hh_1[107]
 + c2.v[77]*MainFormSLS->hh_1[145]
 + c2.v[78]*MainFormSLS->hh_1[23]
 + c2.v[79]*MainFormSLS->hh_1[61];
s/=N_2;
out.push_back(s);
//������ 100
s =c2.v[0]*MainFormSLS->hh_1[100]
 + c2.v[1]*MainFormSLS->hh_1[140]
 + c2.v[2]*MainFormSLS->hh_1[20]
 + c2.v[3]*MainFormSLS->hh_1[60]
 + c2.v[4]*MainFormSLS->hh_1[100]
 + c2.v[5]*MainFormSLS->hh_1[140]
 + c2.v[6]*MainFormSLS->hh_1[20]
 + c2.v[7]*MainFormSLS->hh_1[60]
 + c2.v[8]*MainFormSLS->hh_1[100]
 + c2.v[9]*MainFormSLS->hh_1[140]
 + c2.v[10]*MainFormSLS->hh_1[20]
 + c2.v[11]*MainFormSLS->hh_1[60]
 + c2.v[12]*MainFormSLS->hh_1[100]
 + c2.v[13]*MainFormSLS->hh_1[140]
 + c2.v[14]*MainFormSLS->hh_1[20]
 + c2.v[15]*MainFormSLS->hh_1[60]
 + c2.v[16]*MainFormSLS->hh_1[100]
 + c2.v[17]*MainFormSLS->hh_1[140]
 + c2.v[18]*MainFormSLS->hh_1[20]
 + c2.v[19]*MainFormSLS->hh_1[60]
 + c2.v[20]*MainFormSLS->hh_1[100]
 + c2.v[21]*MainFormSLS->hh_1[140]
 + c2.v[22]*MainFormSLS->hh_1[20]
 + c2.v[23]*MainFormSLS->hh_1[60]
 + c2.v[24]*MainFormSLS->hh_1[100]
 + c2.v[25]*MainFormSLS->hh_1[140]
 + c2.v[26]*MainFormSLS->hh_1[20]
 + c2.v[27]*MainFormSLS->hh_1[60]
 + c2.v[28]*MainFormSLS->hh_1[100]
 + c2.v[29]*MainFormSLS->hh_1[140]
 + c2.v[30]*MainFormSLS->hh_1[20]
 + c2.v[31]*MainFormSLS->hh_1[60]
 + c2.v[32]*MainFormSLS->hh_1[100]
 + c2.v[33]*MainFormSLS->hh_1[140]
 + c2.v[34]*MainFormSLS->hh_1[20]
 + c2.v[35]*MainFormSLS->hh_1[60]
 + c2.v[36]*MainFormSLS->hh_1[100]
 + c2.v[37]*MainFormSLS->hh_1[140]
 + c2.v[38]*MainFormSLS->hh_1[20]
 + c2.v[39]*MainFormSLS->hh_1[60]
 + c2.v[40]*MainFormSLS->hh_1[100]
 + c2.v[41]*MainFormSLS->hh_1[140]
 + c2.v[42]*MainFormSLS->hh_1[20]
 + c2.v[43]*MainFormSLS->hh_1[60]
 + c2.v[44]*MainFormSLS->hh_1[100]
 + c2.v[45]*MainFormSLS->hh_1[140]
 + c2.v[46]*MainFormSLS->hh_1[20]
 + c2.v[47]*MainFormSLS->hh_1[60]
 + c2.v[48]*MainFormSLS->hh_1[100]
 + c2.v[49]*MainFormSLS->hh_1[140]
 + c2.v[50]*MainFormSLS->hh_1[20]
 + c2.v[51]*MainFormSLS->hh_1[60]
 + c2.v[52]*MainFormSLS->hh_1[100]
 + c2.v[53]*MainFormSLS->hh_1[140]
 + c2.v[54]*MainFormSLS->hh_1[20]
 + c2.v[55]*MainFormSLS->hh_1[60]
 + c2.v[56]*MainFormSLS->hh_1[100]
 + c2.v[57]*MainFormSLS->hh_1[140]
 + c2.v[58]*MainFormSLS->hh_1[20]
 + c2.v[59]*MainFormSLS->hh_1[60]
 + c2.v[60]*MainFormSLS->hh_1[100]
 + c2.v[61]*MainFormSLS->hh_1[140]
 + c2.v[62]*MainFormSLS->hh_1[20]
 + c2.v[63]*MainFormSLS->hh_1[60]
 + c2.v[64]*MainFormSLS->hh_1[100]
 + c2.v[65]*MainFormSLS->hh_1[140]
 + c2.v[66]*MainFormSLS->hh_1[20]
 + c2.v[67]*MainFormSLS->hh_1[60]
 + c2.v[68]*MainFormSLS->hh_1[100]
 + c2.v[69]*MainFormSLS->hh_1[140]
 + c2.v[70]*MainFormSLS->hh_1[20]
 + c2.v[71]*MainFormSLS->hh_1[60]
 + c2.v[72]*MainFormSLS->hh_1[100]
 + c2.v[73]*MainFormSLS->hh_1[140]
 + c2.v[74]*MainFormSLS->hh_1[20]
 + c2.v[75]*MainFormSLS->hh_1[60]
 + c2.v[76]*MainFormSLS->hh_1[100]
 + c2.v[77]*MainFormSLS->hh_1[140]
 + c2.v[78]*MainFormSLS->hh_1[20]
 + c2.v[79]*MainFormSLS->hh_1[60];
s/=N_2;
out.push_back(s);
//������ 101
s =c2.v[0]*MainFormSLS->hh_1[101]
 + c2.v[1]*MainFormSLS->hh_1[143]
 + c2.v[2]*MainFormSLS->hh_1[25]
 + c2.v[3]*MainFormSLS->hh_1[67]
 + c2.v[4]*MainFormSLS->hh_1[109]
 + c2.v[5]*MainFormSLS->hh_1[151]
 + c2.v[6]*MainFormSLS->hh_1[33]
 + c2.v[7]*MainFormSLS->hh_1[75]
 + c2.v[8]*MainFormSLS->hh_1[117]
 + c2.v[9]*MainFormSLS->hh_1[159]
 + c2.v[10]*MainFormSLS->hh_1[41]
 + c2.v[11]*MainFormSLS->hh_1[83]
 + c2.v[12]*MainFormSLS->hh_1[125]
 + c2.v[13]*MainFormSLS->hh_1[7]
 + c2.v[14]*MainFormSLS->hh_1[49]
 + c2.v[15]*MainFormSLS->hh_1[91]
 + c2.v[16]*MainFormSLS->hh_1[133]
 + c2.v[17]*MainFormSLS->hh_1[15]
 + c2.v[18]*MainFormSLS->hh_1[57]
 + c2.v[19]*MainFormSLS->hh_1[99]
 + c2.v[20]*MainFormSLS->hh_1[141]
 + c2.v[21]*MainFormSLS->hh_1[23]
 + c2.v[22]*MainFormSLS->hh_1[65]
 + c2.v[23]*MainFormSLS->hh_1[107]
 + c2.v[24]*MainFormSLS->hh_1[149]
 + c2.v[25]*MainFormSLS->hh_1[31]
 + c2.v[26]*MainFormSLS->hh_1[73]
 + c2.v[27]*MainFormSLS->hh_1[115]
 + c2.v[28]*MainFormSLS->hh_1[157]
 + c2.v[29]*MainFormSLS->hh_1[39]
 + c2.v[30]*MainFormSLS->hh_1[81]
 + c2.v[31]*MainFormSLS->hh_1[123]
 + c2.v[32]*MainFormSLS->hh_1[5]
 + c2.v[33]*MainFormSLS->hh_1[47]
 + c2.v[34]*MainFormSLS->hh_1[89]
 + c2.v[35]*MainFormSLS->hh_1[131]
 + c2.v[36]*MainFormSLS->hh_1[13]
 + c2.v[37]*MainFormSLS->hh_1[55]
 + c2.v[38]*MainFormSLS->hh_1[97]
 + c2.v[39]*MainFormSLS->hh_1[139]
 + c2.v[40]*MainFormSLS->hh_1[21]
 + c2.v[41]*MainFormSLS->hh_1[63]
 + c2.v[42]*MainFormSLS->hh_1[105]
 + c2.v[43]*MainFormSLS->hh_1[147]
 + c2.v[44]*MainFormSLS->hh_1[29]
 + c2.v[45]*MainFormSLS->hh_1[71]
 + c2.v[46]*MainFormSLS->hh_1[113]
 + c2.v[47]*MainFormSLS->hh_1[155]
 + c2.v[48]*MainFormSLS->hh_1[37]
 + c2.v[49]*MainFormSLS->hh_1[79]
 + c2.v[50]*MainFormSLS->hh_1[121]
 + c2.v[51]*MainFormSLS->hh_1[3]
 + c2.v[52]*MainFormSLS->hh_1[45]
 + c2.v[53]*MainFormSLS->hh_1[87]
 + c2.v[54]*MainFormSLS->hh_1[129]
 + c2.v[55]*MainFormSLS->hh_1[11]
 + c2.v[56]*MainFormSLS->hh_1[53]
 + c2.v[57]*MainFormSLS->hh_1[95]
 + c2.v[58]*MainFormSLS->hh_1[137]
 + c2.v[59]*MainFormSLS->hh_1[19]
 + c2.v[60]*MainFormSLS->hh_1[61]
 + c2.v[61]*MainFormSLS->hh_1[103]
 + c2.v[62]*MainFormSLS->hh_1[145]
 + c2.v[63]*MainFormSLS->hh_1[27]
 + c2.v[64]*MainFormSLS->hh_1[69]
 + c2.v[65]*MainFormSLS->hh_1[111]
 + c2.v[66]*MainFormSLS->hh_1[153]
 + c2.v[67]*MainFormSLS->hh_1[35]
 + c2.v[68]*MainFormSLS->hh_1[77]
 + c2.v[69]*MainFormSLS->hh_1[119]
 + c2.v[70]*MainFormSLS->hh_1[1]
 + c2.v[71]*MainFormSLS->hh_1[43]
 + c2.v[72]*MainFormSLS->hh_1[85]
 + c2.v[73]*MainFormSLS->hh_1[127]
 + c2.v[74]*MainFormSLS->hh_1[9]
 + c2.v[75]*MainFormSLS->hh_1[51]
 + c2.v[76]*MainFormSLS->hh_1[93]
 + c2.v[77]*MainFormSLS->hh_1[135]
 + c2.v[78]*MainFormSLS->hh_1[17]
 + c2.v[79]*MainFormSLS->hh_1[59];
s/=N_2;
out.push_back(s);
//������ 102
s =c2.v[0]*MainFormSLS->hh_1[102]
 + c2.v[1]*MainFormSLS->hh_1[146]
 + c2.v[2]*MainFormSLS->hh_1[30]
 + c2.v[3]*MainFormSLS->hh_1[74]
 + c2.v[4]*MainFormSLS->hh_1[118]
 + c2.v[5]*MainFormSLS->hh_1[2]
 + c2.v[6]*MainFormSLS->hh_1[46]
 + c2.v[7]*MainFormSLS->hh_1[90]
 + c2.v[8]*MainFormSLS->hh_1[134]
 + c2.v[9]*MainFormSLS->hh_1[18]
 + c2.v[10]*MainFormSLS->hh_1[62]
 + c2.v[11]*MainFormSLS->hh_1[106]
 + c2.v[12]*MainFormSLS->hh_1[150]
 + c2.v[13]*MainFormSLS->hh_1[34]
 + c2.v[14]*MainFormSLS->hh_1[78]
 + c2.v[15]*MainFormSLS->hh_1[122]
 + c2.v[16]*MainFormSLS->hh_1[6]
 + c2.v[17]*MainFormSLS->hh_1[50]
 + c2.v[18]*MainFormSLS->hh_1[94]
 + c2.v[19]*MainFormSLS->hh_1[138]
 + c2.v[20]*MainFormSLS->hh_1[22]
 + c2.v[21]*MainFormSLS->hh_1[66]
 + c2.v[22]*MainFormSLS->hh_1[110]
 + c2.v[23]*MainFormSLS->hh_1[154]
 + c2.v[24]*MainFormSLS->hh_1[38]
 + c2.v[25]*MainFormSLS->hh_1[82]
 + c2.v[26]*MainFormSLS->hh_1[126]
 + c2.v[27]*MainFormSLS->hh_1[10]
 + c2.v[28]*MainFormSLS->hh_1[54]
 + c2.v[29]*MainFormSLS->hh_1[98]
 + c2.v[30]*MainFormSLS->hh_1[142]
 + c2.v[31]*MainFormSLS->hh_1[26]
 + c2.v[32]*MainFormSLS->hh_1[70]
 + c2.v[33]*MainFormSLS->hh_1[114]
 + c2.v[34]*MainFormSLS->hh_1[158]
 + c2.v[35]*MainFormSLS->hh_1[42]
 + c2.v[36]*MainFormSLS->hh_1[86]
 + c2.v[37]*MainFormSLS->hh_1[130]
 + c2.v[38]*MainFormSLS->hh_1[14]
 + c2.v[39]*MainFormSLS->hh_1[58]
 + c2.v[40]*MainFormSLS->hh_1[102]
 + c2.v[41]*MainFormSLS->hh_1[146]
 + c2.v[42]*MainFormSLS->hh_1[30]
 + c2.v[43]*MainFormSLS->hh_1[74]
 + c2.v[44]*MainFormSLS->hh_1[118]
 + c2.v[45]*MainFormSLS->hh_1[2]
 + c2.v[46]*MainFormSLS->hh_1[46]
 + c2.v[47]*MainFormSLS->hh_1[90]
 + c2.v[48]*MainFormSLS->hh_1[134]
 + c2.v[49]*MainFormSLS->hh_1[18]
 + c2.v[50]*MainFormSLS->hh_1[62]
 + c2.v[51]*MainFormSLS->hh_1[106]
 + c2.v[52]*MainFormSLS->hh_1[150]
 + c2.v[53]*MainFormSLS->hh_1[34]
 + c2.v[54]*MainFormSLS->hh_1[78]
 + c2.v[55]*MainFormSLS->hh_1[122]
 + c2.v[56]*MainFormSLS->hh_1[6]
 + c2.v[57]*MainFormSLS->hh_1[50]
 + c2.v[58]*MainFormSLS->hh_1[94]
 + c2.v[59]*MainFormSLS->hh_1[138]
 + c2.v[60]*MainFormSLS->hh_1[22]
 + c2.v[61]*MainFormSLS->hh_1[66]
 + c2.v[62]*MainFormSLS->hh_1[110]
 + c2.v[63]*MainFormSLS->hh_1[154]
 + c2.v[64]*MainFormSLS->hh_1[38]
 + c2.v[65]*MainFormSLS->hh_1[82]
 + c2.v[66]*MainFormSLS->hh_1[126]
 + c2.v[67]*MainFormSLS->hh_1[10]
 + c2.v[68]*MainFormSLS->hh_1[54]
 + c2.v[69]*MainFormSLS->hh_1[98]
 + c2.v[70]*MainFormSLS->hh_1[142]
 + c2.v[71]*MainFormSLS->hh_1[26]
 + c2.v[72]*MainFormSLS->hh_1[70]
 + c2.v[73]*MainFormSLS->hh_1[114]
 + c2.v[74]*MainFormSLS->hh_1[158]
 + c2.v[75]*MainFormSLS->hh_1[42]
 + c2.v[76]*MainFormSLS->hh_1[86]
 + c2.v[77]*MainFormSLS->hh_1[130]
 + c2.v[78]*MainFormSLS->hh_1[14]
 + c2.v[79]*MainFormSLS->hh_1[58];
s/=N_2;
out.push_back(s);
//������ 103
s =c2.v[0]*MainFormSLS->hh_1[103]
 + c2.v[1]*MainFormSLS->hh_1[149]
 + c2.v[2]*MainFormSLS->hh_1[35]
 + c2.v[3]*MainFormSLS->hh_1[81]
 + c2.v[4]*MainFormSLS->hh_1[127]
 + c2.v[5]*MainFormSLS->hh_1[13]
 + c2.v[6]*MainFormSLS->hh_1[59]
 + c2.v[7]*MainFormSLS->hh_1[105]
 + c2.v[8]*MainFormSLS->hh_1[151]
 + c2.v[9]*MainFormSLS->hh_1[37]
 + c2.v[10]*MainFormSLS->hh_1[83]
 + c2.v[11]*MainFormSLS->hh_1[129]
 + c2.v[12]*MainFormSLS->hh_1[15]
 + c2.v[13]*MainFormSLS->hh_1[61]
 + c2.v[14]*MainFormSLS->hh_1[107]
 + c2.v[15]*MainFormSLS->hh_1[153]
 + c2.v[16]*MainFormSLS->hh_1[39]
 + c2.v[17]*MainFormSLS->hh_1[85]
 + c2.v[18]*MainFormSLS->hh_1[131]
 + c2.v[19]*MainFormSLS->hh_1[17]
 + c2.v[20]*MainFormSLS->hh_1[63]
 + c2.v[21]*MainFormSLS->hh_1[109]
 + c2.v[22]*MainFormSLS->hh_1[155]
 + c2.v[23]*MainFormSLS->hh_1[41]
 + c2.v[24]*MainFormSLS->hh_1[87]
 + c2.v[25]*MainFormSLS->hh_1[133]
 + c2.v[26]*MainFormSLS->hh_1[19]
 + c2.v[27]*MainFormSLS->hh_1[65]
 + c2.v[28]*MainFormSLS->hh_1[111]
 + c2.v[29]*MainFormSLS->hh_1[157]
 + c2.v[30]*MainFormSLS->hh_1[43]
 + c2.v[31]*MainFormSLS->hh_1[89]
 + c2.v[32]*MainFormSLS->hh_1[135]
 + c2.v[33]*MainFormSLS->hh_1[21]
 + c2.v[34]*MainFormSLS->hh_1[67]
 + c2.v[35]*MainFormSLS->hh_1[113]
 + c2.v[36]*MainFormSLS->hh_1[159]
 + c2.v[37]*MainFormSLS->hh_1[45]
 + c2.v[38]*MainFormSLS->hh_1[91]
 + c2.v[39]*MainFormSLS->hh_1[137]
 + c2.v[40]*MainFormSLS->hh_1[23]
 + c2.v[41]*MainFormSLS->hh_1[69]
 + c2.v[42]*MainFormSLS->hh_1[115]
 + c2.v[43]*MainFormSLS->hh_1[1]
 + c2.v[44]*MainFormSLS->hh_1[47]
 + c2.v[45]*MainFormSLS->hh_1[93]
 + c2.v[46]*MainFormSLS->hh_1[139]
 + c2.v[47]*MainFormSLS->hh_1[25]
 + c2.v[48]*MainFormSLS->hh_1[71]
 + c2.v[49]*MainFormSLS->hh_1[117]
 + c2.v[50]*MainFormSLS->hh_1[3]
 + c2.v[51]*MainFormSLS->hh_1[49]
 + c2.v[52]*MainFormSLS->hh_1[95]
 + c2.v[53]*MainFormSLS->hh_1[141]
 + c2.v[54]*MainFormSLS->hh_1[27]
 + c2.v[55]*MainFormSLS->hh_1[73]
 + c2.v[56]*MainFormSLS->hh_1[119]
 + c2.v[57]*MainFormSLS->hh_1[5]
 + c2.v[58]*MainFormSLS->hh_1[51]
 + c2.v[59]*MainFormSLS->hh_1[97]
 + c2.v[60]*MainFormSLS->hh_1[143]
 + c2.v[61]*MainFormSLS->hh_1[29]
 + c2.v[62]*MainFormSLS->hh_1[75]
 + c2.v[63]*MainFormSLS->hh_1[121]
 + c2.v[64]*MainFormSLS->hh_1[7]
 + c2.v[65]*MainFormSLS->hh_1[53]
 + c2.v[66]*MainFormSLS->hh_1[99]
 + c2.v[67]*MainFormSLS->hh_1[145]
 + c2.v[68]*MainFormSLS->hh_1[31]
 + c2.v[69]*MainFormSLS->hh_1[77]
 + c2.v[70]*MainFormSLS->hh_1[123]
 + c2.v[71]*MainFormSLS->hh_1[9]
 + c2.v[72]*MainFormSLS->hh_1[55]
 + c2.v[73]*MainFormSLS->hh_1[101]
 + c2.v[74]*MainFormSLS->hh_1[147]
 + c2.v[75]*MainFormSLS->hh_1[33]
 + c2.v[76]*MainFormSLS->hh_1[79]
 + c2.v[77]*MainFormSLS->hh_1[125]
 + c2.v[78]*MainFormSLS->hh_1[11]
 + c2.v[79]*MainFormSLS->hh_1[57];
s/=N_2;
out.push_back(s);
//������ 104
s =c2.v[0]*MainFormSLS->hh_1[104]
 + c2.v[1]*MainFormSLS->hh_1[152]
 + c2.v[2]*MainFormSLS->hh_1[40]
 + c2.v[3]*MainFormSLS->hh_1[88]
 + c2.v[4]*MainFormSLS->hh_1[136]
 + c2.v[5]*MainFormSLS->hh_1[24]
 + c2.v[6]*MainFormSLS->hh_1[72]
 + c2.v[7]*MainFormSLS->hh_1[120]
 + c2.v[8]*MainFormSLS->hh_1[8]
 + c2.v[9]*MainFormSLS->hh_1[56]
 + c2.v[10]*MainFormSLS->hh_1[104]
 + c2.v[11]*MainFormSLS->hh_1[152]
 + c2.v[12]*MainFormSLS->hh_1[40]
 + c2.v[13]*MainFormSLS->hh_1[88]
 + c2.v[14]*MainFormSLS->hh_1[136]
 + c2.v[15]*MainFormSLS->hh_1[24]
 + c2.v[16]*MainFormSLS->hh_1[72]
 + c2.v[17]*MainFormSLS->hh_1[120]
 + c2.v[18]*MainFormSLS->hh_1[8]
 + c2.v[19]*MainFormSLS->hh_1[56]
 + c2.v[20]*MainFormSLS->hh_1[104]
 + c2.v[21]*MainFormSLS->hh_1[152]
 + c2.v[22]*MainFormSLS->hh_1[40]
 + c2.v[23]*MainFormSLS->hh_1[88]
 + c2.v[24]*MainFormSLS->hh_1[136]
 + c2.v[25]*MainFormSLS->hh_1[24]
 + c2.v[26]*MainFormSLS->hh_1[72]
 + c2.v[27]*MainFormSLS->hh_1[120]
 + c2.v[28]*MainFormSLS->hh_1[8]
 + c2.v[29]*MainFormSLS->hh_1[56]
 + c2.v[30]*MainFormSLS->hh_1[104]
 + c2.v[31]*MainFormSLS->hh_1[152]
 + c2.v[32]*MainFormSLS->hh_1[40]
 + c2.v[33]*MainFormSLS->hh_1[88]
 + c2.v[34]*MainFormSLS->hh_1[136]
 + c2.v[35]*MainFormSLS->hh_1[24]
 + c2.v[36]*MainFormSLS->hh_1[72]
 + c2.v[37]*MainFormSLS->hh_1[120]
 + c2.v[38]*MainFormSLS->hh_1[8]
 + c2.v[39]*MainFormSLS->hh_1[56]
 + c2.v[40]*MainFormSLS->hh_1[104]
 + c2.v[41]*MainFormSLS->hh_1[152]
 + c2.v[42]*MainFormSLS->hh_1[40]
 + c2.v[43]*MainFormSLS->hh_1[88]
 + c2.v[44]*MainFormSLS->hh_1[136]
 + c2.v[45]*MainFormSLS->hh_1[24]
 + c2.v[46]*MainFormSLS->hh_1[72]
 + c2.v[47]*MainFormSLS->hh_1[120]
 + c2.v[48]*MainFormSLS->hh_1[8]
 + c2.v[49]*MainFormSLS->hh_1[56]
 + c2.v[50]*MainFormSLS->hh_1[104]
 + c2.v[51]*MainFormSLS->hh_1[152]
 + c2.v[52]*MainFormSLS->hh_1[40]
 + c2.v[53]*MainFormSLS->hh_1[88]
 + c2.v[54]*MainFormSLS->hh_1[136]
 + c2.v[55]*MainFormSLS->hh_1[24]
 + c2.v[56]*MainFormSLS->hh_1[72]
 + c2.v[57]*MainFormSLS->hh_1[120]
 + c2.v[58]*MainFormSLS->hh_1[8]
 + c2.v[59]*MainFormSLS->hh_1[56]
 + c2.v[60]*MainFormSLS->hh_1[104]
 + c2.v[61]*MainFormSLS->hh_1[152]
 + c2.v[62]*MainFormSLS->hh_1[40]
 + c2.v[63]*MainFormSLS->hh_1[88]
 + c2.v[64]*MainFormSLS->hh_1[136]
 + c2.v[65]*MainFormSLS->hh_1[24]
 + c2.v[66]*MainFormSLS->hh_1[72]
 + c2.v[67]*MainFormSLS->hh_1[120]
 + c2.v[68]*MainFormSLS->hh_1[8]
 + c2.v[69]*MainFormSLS->hh_1[56]
 + c2.v[70]*MainFormSLS->hh_1[104]
 + c2.v[71]*MainFormSLS->hh_1[152]
 + c2.v[72]*MainFormSLS->hh_1[40]
 + c2.v[73]*MainFormSLS->hh_1[88]
 + c2.v[74]*MainFormSLS->hh_1[136]
 + c2.v[75]*MainFormSLS->hh_1[24]
 + c2.v[76]*MainFormSLS->hh_1[72]
 + c2.v[77]*MainFormSLS->hh_1[120]
 + c2.v[78]*MainFormSLS->hh_1[8]
 + c2.v[79]*MainFormSLS->hh_1[56];
s/=N_2;
out.push_back(s);
//������ 105
s =c2.v[0]*MainFormSLS->hh_1[105]
 + c2.v[1]*MainFormSLS->hh_1[155]
 + c2.v[2]*MainFormSLS->hh_1[45]
 + c2.v[3]*MainFormSLS->hh_1[95]
 + c2.v[4]*MainFormSLS->hh_1[145]
 + c2.v[5]*MainFormSLS->hh_1[35]
 + c2.v[6]*MainFormSLS->hh_1[85]
 + c2.v[7]*MainFormSLS->hh_1[135]
 + c2.v[8]*MainFormSLS->hh_1[25]
 + c2.v[9]*MainFormSLS->hh_1[75]
 + c2.v[10]*MainFormSLS->hh_1[125]
 + c2.v[11]*MainFormSLS->hh_1[15]
 + c2.v[12]*MainFormSLS->hh_1[65]
 + c2.v[13]*MainFormSLS->hh_1[115]
 + c2.v[14]*MainFormSLS->hh_1[5]
 + c2.v[15]*MainFormSLS->hh_1[55]
 + c2.v[16]*MainFormSLS->hh_1[105]
 + c2.v[17]*MainFormSLS->hh_1[155]
 + c2.v[18]*MainFormSLS->hh_1[45]
 + c2.v[19]*MainFormSLS->hh_1[95]
 + c2.v[20]*MainFormSLS->hh_1[145]
 + c2.v[21]*MainFormSLS->hh_1[35]
 + c2.v[22]*MainFormSLS->hh_1[85]
 + c2.v[23]*MainFormSLS->hh_1[135]
 + c2.v[24]*MainFormSLS->hh_1[25]
 + c2.v[25]*MainFormSLS->hh_1[75]
 + c2.v[26]*MainFormSLS->hh_1[125]
 + c2.v[27]*MainFormSLS->hh_1[15]
 + c2.v[28]*MainFormSLS->hh_1[65]
 + c2.v[29]*MainFormSLS->hh_1[115]
 + c2.v[30]*MainFormSLS->hh_1[5]
 + c2.v[31]*MainFormSLS->hh_1[55]
 + c2.v[32]*MainFormSLS->hh_1[105]
 + c2.v[33]*MainFormSLS->hh_1[155]
 + c2.v[34]*MainFormSLS->hh_1[45]
 + c2.v[35]*MainFormSLS->hh_1[95]
 + c2.v[36]*MainFormSLS->hh_1[145]
 + c2.v[37]*MainFormSLS->hh_1[35]
 + c2.v[38]*MainFormSLS->hh_1[85]
 + c2.v[39]*MainFormSLS->hh_1[135]
 + c2.v[40]*MainFormSLS->hh_1[25]
 + c2.v[41]*MainFormSLS->hh_1[75]
 + c2.v[42]*MainFormSLS->hh_1[125]
 + c2.v[43]*MainFormSLS->hh_1[15]
 + c2.v[44]*MainFormSLS->hh_1[65]
 + c2.v[45]*MainFormSLS->hh_1[115]
 + c2.v[46]*MainFormSLS->hh_1[5]
 + c2.v[47]*MainFormSLS->hh_1[55]
 + c2.v[48]*MainFormSLS->hh_1[105]
 + c2.v[49]*MainFormSLS->hh_1[155]
 + c2.v[50]*MainFormSLS->hh_1[45]
 + c2.v[51]*MainFormSLS->hh_1[95]
 + c2.v[52]*MainFormSLS->hh_1[145]
 + c2.v[53]*MainFormSLS->hh_1[35]
 + c2.v[54]*MainFormSLS->hh_1[85]
 + c2.v[55]*MainFormSLS->hh_1[135]
 + c2.v[56]*MainFormSLS->hh_1[25]
 + c2.v[57]*MainFormSLS->hh_1[75]
 + c2.v[58]*MainFormSLS->hh_1[125]
 + c2.v[59]*MainFormSLS->hh_1[15]
 + c2.v[60]*MainFormSLS->hh_1[65]
 + c2.v[61]*MainFormSLS->hh_1[115]
 + c2.v[62]*MainFormSLS->hh_1[5]
 + c2.v[63]*MainFormSLS->hh_1[55]
 + c2.v[64]*MainFormSLS->hh_1[105]
 + c2.v[65]*MainFormSLS->hh_1[155]
 + c2.v[66]*MainFormSLS->hh_1[45]
 + c2.v[67]*MainFormSLS->hh_1[95]
 + c2.v[68]*MainFormSLS->hh_1[145]
 + c2.v[69]*MainFormSLS->hh_1[35]
 + c2.v[70]*MainFormSLS->hh_1[85]
 + c2.v[71]*MainFormSLS->hh_1[135]
 + c2.v[72]*MainFormSLS->hh_1[25]
 + c2.v[73]*MainFormSLS->hh_1[75]
 + c2.v[74]*MainFormSLS->hh_1[125]
 + c2.v[75]*MainFormSLS->hh_1[15]
 + c2.v[76]*MainFormSLS->hh_1[65]
 + c2.v[77]*MainFormSLS->hh_1[115]
 + c2.v[78]*MainFormSLS->hh_1[5]
 + c2.v[79]*MainFormSLS->hh_1[55];
s/=N_2;
out.push_back(s);
//������ 106
s =c2.v[0]*MainFormSLS->hh_1[106]
 + c2.v[1]*MainFormSLS->hh_1[158]
 + c2.v[2]*MainFormSLS->hh_1[50]
 + c2.v[3]*MainFormSLS->hh_1[102]
 + c2.v[4]*MainFormSLS->hh_1[154]
 + c2.v[5]*MainFormSLS->hh_1[46]
 + c2.v[6]*MainFormSLS->hh_1[98]
 + c2.v[7]*MainFormSLS->hh_1[150]
 + c2.v[8]*MainFormSLS->hh_1[42]
 + c2.v[9]*MainFormSLS->hh_1[94]
 + c2.v[10]*MainFormSLS->hh_1[146]
 + c2.v[11]*MainFormSLS->hh_1[38]
 + c2.v[12]*MainFormSLS->hh_1[90]
 + c2.v[13]*MainFormSLS->hh_1[142]
 + c2.v[14]*MainFormSLS->hh_1[34]
 + c2.v[15]*MainFormSLS->hh_1[86]
 + c2.v[16]*MainFormSLS->hh_1[138]
 + c2.v[17]*MainFormSLS->hh_1[30]
 + c2.v[18]*MainFormSLS->hh_1[82]
 + c2.v[19]*MainFormSLS->hh_1[134]
 + c2.v[20]*MainFormSLS->hh_1[26]
 + c2.v[21]*MainFormSLS->hh_1[78]
 + c2.v[22]*MainFormSLS->hh_1[130]
 + c2.v[23]*MainFormSLS->hh_1[22]
 + c2.v[24]*MainFormSLS->hh_1[74]
 + c2.v[25]*MainFormSLS->hh_1[126]
 + c2.v[26]*MainFormSLS->hh_1[18]
 + c2.v[27]*MainFormSLS->hh_1[70]
 + c2.v[28]*MainFormSLS->hh_1[122]
 + c2.v[29]*MainFormSLS->hh_1[14]
 + c2.v[30]*MainFormSLS->hh_1[66]
 + c2.v[31]*MainFormSLS->hh_1[118]
 + c2.v[32]*MainFormSLS->hh_1[10]
 + c2.v[33]*MainFormSLS->hh_1[62]
 + c2.v[34]*MainFormSLS->hh_1[114]
 + c2.v[35]*MainFormSLS->hh_1[6]
 + c2.v[36]*MainFormSLS->hh_1[58]
 + c2.v[37]*MainFormSLS->hh_1[110]
 + c2.v[38]*MainFormSLS->hh_1[2]
 + c2.v[39]*MainFormSLS->hh_1[54]
 + c2.v[40]*MainFormSLS->hh_1[106]
 + c2.v[41]*MainFormSLS->hh_1[158]
 + c2.v[42]*MainFormSLS->hh_1[50]
 + c2.v[43]*MainFormSLS->hh_1[102]
 + c2.v[44]*MainFormSLS->hh_1[154]
 + c2.v[45]*MainFormSLS->hh_1[46]
 + c2.v[46]*MainFormSLS->hh_1[98]
 + c2.v[47]*MainFormSLS->hh_1[150]
 + c2.v[48]*MainFormSLS->hh_1[42]
 + c2.v[49]*MainFormSLS->hh_1[94]
 + c2.v[50]*MainFormSLS->hh_1[146]
 + c2.v[51]*MainFormSLS->hh_1[38]
 + c2.v[52]*MainFormSLS->hh_1[90]
 + c2.v[53]*MainFormSLS->hh_1[142]
 + c2.v[54]*MainFormSLS->hh_1[34]
 + c2.v[55]*MainFormSLS->hh_1[86]
 + c2.v[56]*MainFormSLS->hh_1[138]
 + c2.v[57]*MainFormSLS->hh_1[30]
 + c2.v[58]*MainFormSLS->hh_1[82]
 + c2.v[59]*MainFormSLS->hh_1[134]
 + c2.v[60]*MainFormSLS->hh_1[26]
 + c2.v[61]*MainFormSLS->hh_1[78]
 + c2.v[62]*MainFormSLS->hh_1[130]
 + c2.v[63]*MainFormSLS->hh_1[22]
 + c2.v[64]*MainFormSLS->hh_1[74]
 + c2.v[65]*MainFormSLS->hh_1[126]
 + c2.v[66]*MainFormSLS->hh_1[18]
 + c2.v[67]*MainFormSLS->hh_1[70]
 + c2.v[68]*MainFormSLS->hh_1[122]
 + c2.v[69]*MainFormSLS->hh_1[14]
 + c2.v[70]*MainFormSLS->hh_1[66]
 + c2.v[71]*MainFormSLS->hh_1[118]
 + c2.v[72]*MainFormSLS->hh_1[10]
 + c2.v[73]*MainFormSLS->hh_1[62]
 + c2.v[74]*MainFormSLS->hh_1[114]
 + c2.v[75]*MainFormSLS->hh_1[6]
 + c2.v[76]*MainFormSLS->hh_1[58]
 + c2.v[77]*MainFormSLS->hh_1[110]
 + c2.v[78]*MainFormSLS->hh_1[2]
 + c2.v[79]*MainFormSLS->hh_1[54];
s/=N_2;
out.push_back(s);
//������ 107
s =c2.v[0]*MainFormSLS->hh_1[107]
 + c2.v[1]*MainFormSLS->hh_1[1]
 + c2.v[2]*MainFormSLS->hh_1[55]
 + c2.v[3]*MainFormSLS->hh_1[109]
 + c2.v[4]*MainFormSLS->hh_1[3]
 + c2.v[5]*MainFormSLS->hh_1[57]
 + c2.v[6]*MainFormSLS->hh_1[111]
 + c2.v[7]*MainFormSLS->hh_1[5]
 + c2.v[8]*MainFormSLS->hh_1[59]
 + c2.v[9]*MainFormSLS->hh_1[113]
 + c2.v[10]*MainFormSLS->hh_1[7]
 + c2.v[11]*MainFormSLS->hh_1[61]
 + c2.v[12]*MainFormSLS->hh_1[115]
 + c2.v[13]*MainFormSLS->hh_1[9]
 + c2.v[14]*MainFormSLS->hh_1[63]
 + c2.v[15]*MainFormSLS->hh_1[117]
 + c2.v[16]*MainFormSLS->hh_1[11]
 + c2.v[17]*MainFormSLS->hh_1[65]
 + c2.v[18]*MainFormSLS->hh_1[119]
 + c2.v[19]*MainFormSLS->hh_1[13]
 + c2.v[20]*MainFormSLS->hh_1[67]
 + c2.v[21]*MainFormSLS->hh_1[121]
 + c2.v[22]*MainFormSLS->hh_1[15]
 + c2.v[23]*MainFormSLS->hh_1[69]
 + c2.v[24]*MainFormSLS->hh_1[123]
 + c2.v[25]*MainFormSLS->hh_1[17]
 + c2.v[26]*MainFormSLS->hh_1[71]
 + c2.v[27]*MainFormSLS->hh_1[125]
 + c2.v[28]*MainFormSLS->hh_1[19]
 + c2.v[29]*MainFormSLS->hh_1[73]
 + c2.v[30]*MainFormSLS->hh_1[127]
 + c2.v[31]*MainFormSLS->hh_1[21]
 + c2.v[32]*MainFormSLS->hh_1[75]
 + c2.v[33]*MainFormSLS->hh_1[129]
 + c2.v[34]*MainFormSLS->hh_1[23]
 + c2.v[35]*MainFormSLS->hh_1[77]
 + c2.v[36]*MainFormSLS->hh_1[131]
 + c2.v[37]*MainFormSLS->hh_1[25]
 + c2.v[38]*MainFormSLS->hh_1[79]
 + c2.v[39]*MainFormSLS->hh_1[133]
 + c2.v[40]*MainFormSLS->hh_1[27]
 + c2.v[41]*MainFormSLS->hh_1[81]
 + c2.v[42]*MainFormSLS->hh_1[135]
 + c2.v[43]*MainFormSLS->hh_1[29]
 + c2.v[44]*MainFormSLS->hh_1[83]
 + c2.v[45]*MainFormSLS->hh_1[137]
 + c2.v[46]*MainFormSLS->hh_1[31]
 + c2.v[47]*MainFormSLS->hh_1[85]
 + c2.v[48]*MainFormSLS->hh_1[139]
 + c2.v[49]*MainFormSLS->hh_1[33]
 + c2.v[50]*MainFormSLS->hh_1[87]
 + c2.v[51]*MainFormSLS->hh_1[141]
 + c2.v[52]*MainFormSLS->hh_1[35]
 + c2.v[53]*MainFormSLS->hh_1[89]
 + c2.v[54]*MainFormSLS->hh_1[143]
 + c2.v[55]*MainFormSLS->hh_1[37]
 + c2.v[56]*MainFormSLS->hh_1[91]
 + c2.v[57]*MainFormSLS->hh_1[145]
 + c2.v[58]*MainFormSLS->hh_1[39]
 + c2.v[59]*MainFormSLS->hh_1[93]
 + c2.v[60]*MainFormSLS->hh_1[147]
 + c2.v[61]*MainFormSLS->hh_1[41]
 + c2.v[62]*MainFormSLS->hh_1[95]
 + c2.v[63]*MainFormSLS->hh_1[149]
 + c2.v[64]*MainFormSLS->hh_1[43]
 + c2.v[65]*MainFormSLS->hh_1[97]
 + c2.v[66]*MainFormSLS->hh_1[151]
 + c2.v[67]*MainFormSLS->hh_1[45]
 + c2.v[68]*MainFormSLS->hh_1[99]
 + c2.v[69]*MainFormSLS->hh_1[153]
 + c2.v[70]*MainFormSLS->hh_1[47]
 + c2.v[71]*MainFormSLS->hh_1[101]
 + c2.v[72]*MainFormSLS->hh_1[155]
 + c2.v[73]*MainFormSLS->hh_1[49]
 + c2.v[74]*MainFormSLS->hh_1[103]
 + c2.v[75]*MainFormSLS->hh_1[157]
 + c2.v[76]*MainFormSLS->hh_1[51]
 + c2.v[77]*MainFormSLS->hh_1[105]
 + c2.v[78]*MainFormSLS->hh_1[159]
 + c2.v[79]*MainFormSLS->hh_1[53];
s/=N_2;
out.push_back(s);
//������ 108
s =c2.v[0]*MainFormSLS->hh_1[108]
 + c2.v[1]*MainFormSLS->hh_1[4]
 + c2.v[2]*MainFormSLS->hh_1[60]
 + c2.v[3]*MainFormSLS->hh_1[116]
 + c2.v[4]*MainFormSLS->hh_1[12]
 + c2.v[5]*MainFormSLS->hh_1[68]
 + c2.v[6]*MainFormSLS->hh_1[124]
 + c2.v[7]*MainFormSLS->hh_1[20]
 + c2.v[8]*MainFormSLS->hh_1[76]
 + c2.v[9]*MainFormSLS->hh_1[132]
 + c2.v[10]*MainFormSLS->hh_1[28]
 + c2.v[11]*MainFormSLS->hh_1[84]
 + c2.v[12]*MainFormSLS->hh_1[140]
 + c2.v[13]*MainFormSLS->hh_1[36]
 + c2.v[14]*MainFormSLS->hh_1[92]
 + c2.v[15]*MainFormSLS->hh_1[148]
 + c2.v[16]*MainFormSLS->hh_1[44]
 + c2.v[17]*MainFormSLS->hh_1[100]
 + c2.v[18]*MainFormSLS->hh_1[156]
 + c2.v[19]*MainFormSLS->hh_1[52]
 + c2.v[20]*MainFormSLS->hh_1[108]
 + c2.v[21]*MainFormSLS->hh_1[4]
 + c2.v[22]*MainFormSLS->hh_1[60]
 + c2.v[23]*MainFormSLS->hh_1[116]
 + c2.v[24]*MainFormSLS->hh_1[12]
 + c2.v[25]*MainFormSLS->hh_1[68]
 + c2.v[26]*MainFormSLS->hh_1[124]
 + c2.v[27]*MainFormSLS->hh_1[20]
 + c2.v[28]*MainFormSLS->hh_1[76]
 + c2.v[29]*MainFormSLS->hh_1[132]
 + c2.v[30]*MainFormSLS->hh_1[28]
 + c2.v[31]*MainFormSLS->hh_1[84]
 + c2.v[32]*MainFormSLS->hh_1[140]
 + c2.v[33]*MainFormSLS->hh_1[36]
 + c2.v[34]*MainFormSLS->hh_1[92]
 + c2.v[35]*MainFormSLS->hh_1[148]
 + c2.v[36]*MainFormSLS->hh_1[44]
 + c2.v[37]*MainFormSLS->hh_1[100]
 + c2.v[38]*MainFormSLS->hh_1[156]
 + c2.v[39]*MainFormSLS->hh_1[52]
 + c2.v[40]*MainFormSLS->hh_1[108]
 + c2.v[41]*MainFormSLS->hh_1[4]
 + c2.v[42]*MainFormSLS->hh_1[60]
 + c2.v[43]*MainFormSLS->hh_1[116]
 + c2.v[44]*MainFormSLS->hh_1[12]
 + c2.v[45]*MainFormSLS->hh_1[68]
 + c2.v[46]*MainFormSLS->hh_1[124]
 + c2.v[47]*MainFormSLS->hh_1[20]
 + c2.v[48]*MainFormSLS->hh_1[76]
 + c2.v[49]*MainFormSLS->hh_1[132]
 + c2.v[50]*MainFormSLS->hh_1[28]
 + c2.v[51]*MainFormSLS->hh_1[84]
 + c2.v[52]*MainFormSLS->hh_1[140]
 + c2.v[53]*MainFormSLS->hh_1[36]
 + c2.v[54]*MainFormSLS->hh_1[92]
 + c2.v[55]*MainFormSLS->hh_1[148]
 + c2.v[56]*MainFormSLS->hh_1[44]
 + c2.v[57]*MainFormSLS->hh_1[100]
 + c2.v[58]*MainFormSLS->hh_1[156]
 + c2.v[59]*MainFormSLS->hh_1[52]
 + c2.v[60]*MainFormSLS->hh_1[108]
 + c2.v[61]*MainFormSLS->hh_1[4]
 + c2.v[62]*MainFormSLS->hh_1[60]
 + c2.v[63]*MainFormSLS->hh_1[116]
 + c2.v[64]*MainFormSLS->hh_1[12]
 + c2.v[65]*MainFormSLS->hh_1[68]
 + c2.v[66]*MainFormSLS->hh_1[124]
 + c2.v[67]*MainFormSLS->hh_1[20]
 + c2.v[68]*MainFormSLS->hh_1[76]
 + c2.v[69]*MainFormSLS->hh_1[132]
 + c2.v[70]*MainFormSLS->hh_1[28]
 + c2.v[71]*MainFormSLS->hh_1[84]
 + c2.v[72]*MainFormSLS->hh_1[140]
 + c2.v[73]*MainFormSLS->hh_1[36]
 + c2.v[74]*MainFormSLS->hh_1[92]
 + c2.v[75]*MainFormSLS->hh_1[148]
 + c2.v[76]*MainFormSLS->hh_1[44]
 + c2.v[77]*MainFormSLS->hh_1[100]
 + c2.v[78]*MainFormSLS->hh_1[156]
 + c2.v[79]*MainFormSLS->hh_1[52];
s/=N_2;
out.push_back(s);
//������ 109
s =c2.v[0]*MainFormSLS->hh_1[109]
 + c2.v[1]*MainFormSLS->hh_1[7]
 + c2.v[2]*MainFormSLS->hh_1[65]
 + c2.v[3]*MainFormSLS->hh_1[123]
 + c2.v[4]*MainFormSLS->hh_1[21]
 + c2.v[5]*MainFormSLS->hh_1[79]
 + c2.v[6]*MainFormSLS->hh_1[137]
 + c2.v[7]*MainFormSLS->hh_1[35]
 + c2.v[8]*MainFormSLS->hh_1[93]
 + c2.v[9]*MainFormSLS->hh_1[151]
 + c2.v[10]*MainFormSLS->hh_1[49]
 + c2.v[11]*MainFormSLS->hh_1[107]
 + c2.v[12]*MainFormSLS->hh_1[5]
 + c2.v[13]*MainFormSLS->hh_1[63]
 + c2.v[14]*MainFormSLS->hh_1[121]
 + c2.v[15]*MainFormSLS->hh_1[19]
 + c2.v[16]*MainFormSLS->hh_1[77]
 + c2.v[17]*MainFormSLS->hh_1[135]
 + c2.v[18]*MainFormSLS->hh_1[33]
 + c2.v[19]*MainFormSLS->hh_1[91]
 + c2.v[20]*MainFormSLS->hh_1[149]
 + c2.v[21]*MainFormSLS->hh_1[47]
 + c2.v[22]*MainFormSLS->hh_1[105]
 + c2.v[23]*MainFormSLS->hh_1[3]
 + c2.v[24]*MainFormSLS->hh_1[61]
 + c2.v[25]*MainFormSLS->hh_1[119]
 + c2.v[26]*MainFormSLS->hh_1[17]
 + c2.v[27]*MainFormSLS->hh_1[75]
 + c2.v[28]*MainFormSLS->hh_1[133]
 + c2.v[29]*MainFormSLS->hh_1[31]
 + c2.v[30]*MainFormSLS->hh_1[89]
 + c2.v[31]*MainFormSLS->hh_1[147]
 + c2.v[32]*MainFormSLS->hh_1[45]
 + c2.v[33]*MainFormSLS->hh_1[103]
 + c2.v[34]*MainFormSLS->hh_1[1]
 + c2.v[35]*MainFormSLS->hh_1[59]
 + c2.v[36]*MainFormSLS->hh_1[117]
 + c2.v[37]*MainFormSLS->hh_1[15]
 + c2.v[38]*MainFormSLS->hh_1[73]
 + c2.v[39]*MainFormSLS->hh_1[131]
 + c2.v[40]*MainFormSLS->hh_1[29]
 + c2.v[41]*MainFormSLS->hh_1[87]
 + c2.v[42]*MainFormSLS->hh_1[145]
 + c2.v[43]*MainFormSLS->hh_1[43]
 + c2.v[44]*MainFormSLS->hh_1[101]
 + c2.v[45]*MainFormSLS->hh_1[159]
 + c2.v[46]*MainFormSLS->hh_1[57]
 + c2.v[47]*MainFormSLS->hh_1[115]
 + c2.v[48]*MainFormSLS->hh_1[13]
 + c2.v[49]*MainFormSLS->hh_1[71]
 + c2.v[50]*MainFormSLS->hh_1[129]
 + c2.v[51]*MainFormSLS->hh_1[27]
 + c2.v[52]*MainFormSLS->hh_1[85]
 + c2.v[53]*MainFormSLS->hh_1[143]
 + c2.v[54]*MainFormSLS->hh_1[41]
 + c2.v[55]*MainFormSLS->hh_1[99]
 + c2.v[56]*MainFormSLS->hh_1[157]
 + c2.v[57]*MainFormSLS->hh_1[55]
 + c2.v[58]*MainFormSLS->hh_1[113]
 + c2.v[59]*MainFormSLS->hh_1[11]
 + c2.v[60]*MainFormSLS->hh_1[69]
 + c2.v[61]*MainFormSLS->hh_1[127]
 + c2.v[62]*MainFormSLS->hh_1[25]
 + c2.v[63]*MainFormSLS->hh_1[83]
 + c2.v[64]*MainFormSLS->hh_1[141]
 + c2.v[65]*MainFormSLS->hh_1[39]
 + c2.v[66]*MainFormSLS->hh_1[97]
 + c2.v[67]*MainFormSLS->hh_1[155]
 + c2.v[68]*MainFormSLS->hh_1[53]
 + c2.v[69]*MainFormSLS->hh_1[111]
 + c2.v[70]*MainFormSLS->hh_1[9]
 + c2.v[71]*MainFormSLS->hh_1[67]
 + c2.v[72]*MainFormSLS->hh_1[125]
 + c2.v[73]*MainFormSLS->hh_1[23]
 + c2.v[74]*MainFormSLS->hh_1[81]
 + c2.v[75]*MainFormSLS->hh_1[139]
 + c2.v[76]*MainFormSLS->hh_1[37]
 + c2.v[77]*MainFormSLS->hh_1[95]
 + c2.v[78]*MainFormSLS->hh_1[153]
 + c2.v[79]*MainFormSLS->hh_1[51];
s/=N_2;
out.push_back(s);
//������ 110
s =c2.v[0]*MainFormSLS->hh_1[110]
 + c2.v[1]*MainFormSLS->hh_1[10]
 + c2.v[2]*MainFormSLS->hh_1[70]
 + c2.v[3]*MainFormSLS->hh_1[130]
 + c2.v[4]*MainFormSLS->hh_1[30]
 + c2.v[5]*MainFormSLS->hh_1[90]
 + c2.v[6]*MainFormSLS->hh_1[150]
 + c2.v[7]*MainFormSLS->hh_1[50]
 + c2.v[8]*MainFormSLS->hh_1[110]
 + c2.v[9]*MainFormSLS->hh_1[10]
 + c2.v[10]*MainFormSLS->hh_1[70]
 + c2.v[11]*MainFormSLS->hh_1[130]
 + c2.v[12]*MainFormSLS->hh_1[30]
 + c2.v[13]*MainFormSLS->hh_1[90]
 + c2.v[14]*MainFormSLS->hh_1[150]
 + c2.v[15]*MainFormSLS->hh_1[50]
 + c2.v[16]*MainFormSLS->hh_1[110]
 + c2.v[17]*MainFormSLS->hh_1[10]
 + c2.v[18]*MainFormSLS->hh_1[70]
 + c2.v[19]*MainFormSLS->hh_1[130]
 + c2.v[20]*MainFormSLS->hh_1[30]
 + c2.v[21]*MainFormSLS->hh_1[90]
 + c2.v[22]*MainFormSLS->hh_1[150]
 + c2.v[23]*MainFormSLS->hh_1[50]
 + c2.v[24]*MainFormSLS->hh_1[110]
 + c2.v[25]*MainFormSLS->hh_1[10]
 + c2.v[26]*MainFormSLS->hh_1[70]
 + c2.v[27]*MainFormSLS->hh_1[130]
 + c2.v[28]*MainFormSLS->hh_1[30]
 + c2.v[29]*MainFormSLS->hh_1[90]
 + c2.v[30]*MainFormSLS->hh_1[150]
 + c2.v[31]*MainFormSLS->hh_1[50]
 + c2.v[32]*MainFormSLS->hh_1[110]
 + c2.v[33]*MainFormSLS->hh_1[10]
 + c2.v[34]*MainFormSLS->hh_1[70]
 + c2.v[35]*MainFormSLS->hh_1[130]
 + c2.v[36]*MainFormSLS->hh_1[30]
 + c2.v[37]*MainFormSLS->hh_1[90]
 + c2.v[38]*MainFormSLS->hh_1[150]
 + c2.v[39]*MainFormSLS->hh_1[50]
 + c2.v[40]*MainFormSLS->hh_1[110]
 + c2.v[41]*MainFormSLS->hh_1[10]
 + c2.v[42]*MainFormSLS->hh_1[70]
 + c2.v[43]*MainFormSLS->hh_1[130]
 + c2.v[44]*MainFormSLS->hh_1[30]
 + c2.v[45]*MainFormSLS->hh_1[90]
 + c2.v[46]*MainFormSLS->hh_1[150]
 + c2.v[47]*MainFormSLS->hh_1[50]
 + c2.v[48]*MainFormSLS->hh_1[110]
 + c2.v[49]*MainFormSLS->hh_1[10]
 + c2.v[50]*MainFormSLS->hh_1[70]
 + c2.v[51]*MainFormSLS->hh_1[130]
 + c2.v[52]*MainFormSLS->hh_1[30]
 + c2.v[53]*MainFormSLS->hh_1[90]
 + c2.v[54]*MainFormSLS->hh_1[150]
 + c2.v[55]*MainFormSLS->hh_1[50]
 + c2.v[56]*MainFormSLS->hh_1[110]
 + c2.v[57]*MainFormSLS->hh_1[10]
 + c2.v[58]*MainFormSLS->hh_1[70]
 + c2.v[59]*MainFormSLS->hh_1[130]
 + c2.v[60]*MainFormSLS->hh_1[30]
 + c2.v[61]*MainFormSLS->hh_1[90]
 + c2.v[62]*MainFormSLS->hh_1[150]
 + c2.v[63]*MainFormSLS->hh_1[50]
 + c2.v[64]*MainFormSLS->hh_1[110]
 + c2.v[65]*MainFormSLS->hh_1[10]
 + c2.v[66]*MainFormSLS->hh_1[70]
 + c2.v[67]*MainFormSLS->hh_1[130]
 + c2.v[68]*MainFormSLS->hh_1[30]
 + c2.v[69]*MainFormSLS->hh_1[90]
 + c2.v[70]*MainFormSLS->hh_1[150]
 + c2.v[71]*MainFormSLS->hh_1[50]
 + c2.v[72]*MainFormSLS->hh_1[110]
 + c2.v[73]*MainFormSLS->hh_1[10]
 + c2.v[74]*MainFormSLS->hh_1[70]
 + c2.v[75]*MainFormSLS->hh_1[130]
 + c2.v[76]*MainFormSLS->hh_1[30]
 + c2.v[77]*MainFormSLS->hh_1[90]
 + c2.v[78]*MainFormSLS->hh_1[150]
 + c2.v[79]*MainFormSLS->hh_1[50];
s/=N_2;
out.push_back(s);
//������ 111
s =c2.v[0]*MainFormSLS->hh_1[111]
 + c2.v[1]*MainFormSLS->hh_1[13]
 + c2.v[2]*MainFormSLS->hh_1[75]
 + c2.v[3]*MainFormSLS->hh_1[137]
 + c2.v[4]*MainFormSLS->hh_1[39]
 + c2.v[5]*MainFormSLS->hh_1[101]
 + c2.v[6]*MainFormSLS->hh_1[3]
 + c2.v[7]*MainFormSLS->hh_1[65]
 + c2.v[8]*MainFormSLS->hh_1[127]
 + c2.v[9]*MainFormSLS->hh_1[29]
 + c2.v[10]*MainFormSLS->hh_1[91]
 + c2.v[11]*MainFormSLS->hh_1[153]
 + c2.v[12]*MainFormSLS->hh_1[55]
 + c2.v[13]*MainFormSLS->hh_1[117]
 + c2.v[14]*MainFormSLS->hh_1[19]
 + c2.v[15]*MainFormSLS->hh_1[81]
 + c2.v[16]*MainFormSLS->hh_1[143]
 + c2.v[17]*MainFormSLS->hh_1[45]
 + c2.v[18]*MainFormSLS->hh_1[107]
 + c2.v[19]*MainFormSLS->hh_1[9]
 + c2.v[20]*MainFormSLS->hh_1[71]
 + c2.v[21]*MainFormSLS->hh_1[133]
 + c2.v[22]*MainFormSLS->hh_1[35]
 + c2.v[23]*MainFormSLS->hh_1[97]
 + c2.v[24]*MainFormSLS->hh_1[159]
 + c2.v[25]*MainFormSLS->hh_1[61]
 + c2.v[26]*MainFormSLS->hh_1[123]
 + c2.v[27]*MainFormSLS->hh_1[25]
 + c2.v[28]*MainFormSLS->hh_1[87]
 + c2.v[29]*MainFormSLS->hh_1[149]
 + c2.v[30]*MainFormSLS->hh_1[51]
 + c2.v[31]*MainFormSLS->hh_1[113]
 + c2.v[32]*MainFormSLS->hh_1[15]
 + c2.v[33]*MainFormSLS->hh_1[77]
 + c2.v[34]*MainFormSLS->hh_1[139]
 + c2.v[35]*MainFormSLS->hh_1[41]
 + c2.v[36]*MainFormSLS->hh_1[103]
 + c2.v[37]*MainFormSLS->hh_1[5]
 + c2.v[38]*MainFormSLS->hh_1[67]
 + c2.v[39]*MainFormSLS->hh_1[129]
 + c2.v[40]*MainFormSLS->hh_1[31]
 + c2.v[41]*MainFormSLS->hh_1[93]
 + c2.v[42]*MainFormSLS->hh_1[155]
 + c2.v[43]*MainFormSLS->hh_1[57]
 + c2.v[44]*MainFormSLS->hh_1[119]
 + c2.v[45]*MainFormSLS->hh_1[21]
 + c2.v[46]*MainFormSLS->hh_1[83]
 + c2.v[47]*MainFormSLS->hh_1[145]
 + c2.v[48]*MainFormSLS->hh_1[47]
 + c2.v[49]*MainFormSLS->hh_1[109]
 + c2.v[50]*MainFormSLS->hh_1[11]
 + c2.v[51]*MainFormSLS->hh_1[73]
 + c2.v[52]*MainFormSLS->hh_1[135]
 + c2.v[53]*MainFormSLS->hh_1[37]
 + c2.v[54]*MainFormSLS->hh_1[99]
 + c2.v[55]*MainFormSLS->hh_1[1]
 + c2.v[56]*MainFormSLS->hh_1[63]
 + c2.v[57]*MainFormSLS->hh_1[125]
 + c2.v[58]*MainFormSLS->hh_1[27]
 + c2.v[59]*MainFormSLS->hh_1[89]
 + c2.v[60]*MainFormSLS->hh_1[151]
 + c2.v[61]*MainFormSLS->hh_1[53]
 + c2.v[62]*MainFormSLS->hh_1[115]
 + c2.v[63]*MainFormSLS->hh_1[17]
 + c2.v[64]*MainFormSLS->hh_1[79]
 + c2.v[65]*MainFormSLS->hh_1[141]
 + c2.v[66]*MainFormSLS->hh_1[43]
 + c2.v[67]*MainFormSLS->hh_1[105]
 + c2.v[68]*MainFormSLS->hh_1[7]
 + c2.v[69]*MainFormSLS->hh_1[69]
 + c2.v[70]*MainFormSLS->hh_1[131]
 + c2.v[71]*MainFormSLS->hh_1[33]
 + c2.v[72]*MainFormSLS->hh_1[95]
 + c2.v[73]*MainFormSLS->hh_1[157]
 + c2.v[74]*MainFormSLS->hh_1[59]
 + c2.v[75]*MainFormSLS->hh_1[121]
 + c2.v[76]*MainFormSLS->hh_1[23]
 + c2.v[77]*MainFormSLS->hh_1[85]
 + c2.v[78]*MainFormSLS->hh_1[147]
 + c2.v[79]*MainFormSLS->hh_1[49];
s/=N_2;
out.push_back(s);
//������ 112
s =c2.v[0]*MainFormSLS->hh_1[112]
 + c2.v[1]*MainFormSLS->hh_1[16]
 + c2.v[2]*MainFormSLS->hh_1[80]
 + c2.v[3]*MainFormSLS->hh_1[144]
 + c2.v[4]*MainFormSLS->hh_1[48]
 + c2.v[5]*MainFormSLS->hh_1[112]
 + c2.v[6]*MainFormSLS->hh_1[16]
 + c2.v[7]*MainFormSLS->hh_1[80]
 + c2.v[8]*MainFormSLS->hh_1[144]
 + c2.v[9]*MainFormSLS->hh_1[48]
 + c2.v[10]*MainFormSLS->hh_1[112]
 + c2.v[11]*MainFormSLS->hh_1[16]
 + c2.v[12]*MainFormSLS->hh_1[80]
 + c2.v[13]*MainFormSLS->hh_1[144]
 + c2.v[14]*MainFormSLS->hh_1[48]
 + c2.v[15]*MainFormSLS->hh_1[112]
 + c2.v[16]*MainFormSLS->hh_1[16]
 + c2.v[17]*MainFormSLS->hh_1[80]
 + c2.v[18]*MainFormSLS->hh_1[144]
 + c2.v[19]*MainFormSLS->hh_1[48]
 + c2.v[20]*MainFormSLS->hh_1[112]
 + c2.v[21]*MainFormSLS->hh_1[16]
 + c2.v[22]*MainFormSLS->hh_1[80]
 + c2.v[23]*MainFormSLS->hh_1[144]
 + c2.v[24]*MainFormSLS->hh_1[48]
 + c2.v[25]*MainFormSLS->hh_1[112]
 + c2.v[26]*MainFormSLS->hh_1[16]
 + c2.v[27]*MainFormSLS->hh_1[80]
 + c2.v[28]*MainFormSLS->hh_1[144]
 + c2.v[29]*MainFormSLS->hh_1[48]
 + c2.v[30]*MainFormSLS->hh_1[112]
 + c2.v[31]*MainFormSLS->hh_1[16]
 + c2.v[32]*MainFormSLS->hh_1[80]
 + c2.v[33]*MainFormSLS->hh_1[144]
 + c2.v[34]*MainFormSLS->hh_1[48]
 + c2.v[35]*MainFormSLS->hh_1[112]
 + c2.v[36]*MainFormSLS->hh_1[16]
 + c2.v[37]*MainFormSLS->hh_1[80]
 + c2.v[38]*MainFormSLS->hh_1[144]
 + c2.v[39]*MainFormSLS->hh_1[48]
 + c2.v[40]*MainFormSLS->hh_1[112]
 + c2.v[41]*MainFormSLS->hh_1[16]
 + c2.v[42]*MainFormSLS->hh_1[80]
 + c2.v[43]*MainFormSLS->hh_1[144]
 + c2.v[44]*MainFormSLS->hh_1[48]
 + c2.v[45]*MainFormSLS->hh_1[112]
 + c2.v[46]*MainFormSLS->hh_1[16]
 + c2.v[47]*MainFormSLS->hh_1[80]
 + c2.v[48]*MainFormSLS->hh_1[144]
 + c2.v[49]*MainFormSLS->hh_1[48]
 + c2.v[50]*MainFormSLS->hh_1[112]
 + c2.v[51]*MainFormSLS->hh_1[16]
 + c2.v[52]*MainFormSLS->hh_1[80]
 + c2.v[53]*MainFormSLS->hh_1[144]
 + c2.v[54]*MainFormSLS->hh_1[48]
 + c2.v[55]*MainFormSLS->hh_1[112]
 + c2.v[56]*MainFormSLS->hh_1[16]
 + c2.v[57]*MainFormSLS->hh_1[80]
 + c2.v[58]*MainFormSLS->hh_1[144]
 + c2.v[59]*MainFormSLS->hh_1[48]
 + c2.v[60]*MainFormSLS->hh_1[112]
 + c2.v[61]*MainFormSLS->hh_1[16]
 + c2.v[62]*MainFormSLS->hh_1[80]
 + c2.v[63]*MainFormSLS->hh_1[144]
 + c2.v[64]*MainFormSLS->hh_1[48]
 + c2.v[65]*MainFormSLS->hh_1[112]
 + c2.v[66]*MainFormSLS->hh_1[16]
 + c2.v[67]*MainFormSLS->hh_1[80]
 + c2.v[68]*MainFormSLS->hh_1[144]
 + c2.v[69]*MainFormSLS->hh_1[48]
 + c2.v[70]*MainFormSLS->hh_1[112]
 + c2.v[71]*MainFormSLS->hh_1[16]
 + c2.v[72]*MainFormSLS->hh_1[80]
 + c2.v[73]*MainFormSLS->hh_1[144]
 + c2.v[74]*MainFormSLS->hh_1[48]
 + c2.v[75]*MainFormSLS->hh_1[112]
 + c2.v[76]*MainFormSLS->hh_1[16]
 + c2.v[77]*MainFormSLS->hh_1[80]
 + c2.v[78]*MainFormSLS->hh_1[144]
 + c2.v[79]*MainFormSLS->hh_1[48];
s/=N_2;
out.push_back(s);
//������ 113
s =c2.v[0]*MainFormSLS->hh_1[113]
 + c2.v[1]*MainFormSLS->hh_1[19]
 + c2.v[2]*MainFormSLS->hh_1[85]
 + c2.v[3]*MainFormSLS->hh_1[151]
 + c2.v[4]*MainFormSLS->hh_1[57]
 + c2.v[5]*MainFormSLS->hh_1[123]
 + c2.v[6]*MainFormSLS->hh_1[29]
 + c2.v[7]*MainFormSLS->hh_1[95]
 + c2.v[8]*MainFormSLS->hh_1[1]
 + c2.v[9]*MainFormSLS->hh_1[67]
 + c2.v[10]*MainFormSLS->hh_1[133]
 + c2.v[11]*MainFormSLS->hh_1[39]
 + c2.v[12]*MainFormSLS->hh_1[105]
 + c2.v[13]*MainFormSLS->hh_1[11]
 + c2.v[14]*MainFormSLS->hh_1[77]
 + c2.v[15]*MainFormSLS->hh_1[143]
 + c2.v[16]*MainFormSLS->hh_1[49]
 + c2.v[17]*MainFormSLS->hh_1[115]
 + c2.v[18]*MainFormSLS->hh_1[21]
 + c2.v[19]*MainFormSLS->hh_1[87]
 + c2.v[20]*MainFormSLS->hh_1[153]
 + c2.v[21]*MainFormSLS->hh_1[59]
 + c2.v[22]*MainFormSLS->hh_1[125]
 + c2.v[23]*MainFormSLS->hh_1[31]
 + c2.v[24]*MainFormSLS->hh_1[97]
 + c2.v[25]*MainFormSLS->hh_1[3]
 + c2.v[26]*MainFormSLS->hh_1[69]
 + c2.v[27]*MainFormSLS->hh_1[135]
 + c2.v[28]*MainFormSLS->hh_1[41]
 + c2.v[29]*MainFormSLS->hh_1[107]
 + c2.v[30]*MainFormSLS->hh_1[13]
 + c2.v[31]*MainFormSLS->hh_1[79]
 + c2.v[32]*MainFormSLS->hh_1[145]
 + c2.v[33]*MainFormSLS->hh_1[51]
 + c2.v[34]*MainFormSLS->hh_1[117]
 + c2.v[35]*MainFormSLS->hh_1[23]
 + c2.v[36]*MainFormSLS->hh_1[89]
 + c2.v[37]*MainFormSLS->hh_1[155]
 + c2.v[38]*MainFormSLS->hh_1[61]
 + c2.v[39]*MainFormSLS->hh_1[127]
 + c2.v[40]*MainFormSLS->hh_1[33]
 + c2.v[41]*MainFormSLS->hh_1[99]
 + c2.v[42]*MainFormSLS->hh_1[5]
 + c2.v[43]*MainFormSLS->hh_1[71]
 + c2.v[44]*MainFormSLS->hh_1[137]
 + c2.v[45]*MainFormSLS->hh_1[43]
 + c2.v[46]*MainFormSLS->hh_1[109]
 + c2.v[47]*MainFormSLS->hh_1[15]
 + c2.v[48]*MainFormSLS->hh_1[81]
 + c2.v[49]*MainFormSLS->hh_1[147]
 + c2.v[50]*MainFormSLS->hh_1[53]
 + c2.v[51]*MainFormSLS->hh_1[119]
 + c2.v[52]*MainFormSLS->hh_1[25]
 + c2.v[53]*MainFormSLS->hh_1[91]
 + c2.v[54]*MainFormSLS->hh_1[157]
 + c2.v[55]*MainFormSLS->hh_1[63]
 + c2.v[56]*MainFormSLS->hh_1[129]
 + c2.v[57]*MainFormSLS->hh_1[35]
 + c2.v[58]*MainFormSLS->hh_1[101]
 + c2.v[59]*MainFormSLS->hh_1[7]
 + c2.v[60]*MainFormSLS->hh_1[73]
 + c2.v[61]*MainFormSLS->hh_1[139]
 + c2.v[62]*MainFormSLS->hh_1[45]
 + c2.v[63]*MainFormSLS->hh_1[111]
 + c2.v[64]*MainFormSLS->hh_1[17]
 + c2.v[65]*MainFormSLS->hh_1[83]
 + c2.v[66]*MainFormSLS->hh_1[149]
 + c2.v[67]*MainFormSLS->hh_1[55]
 + c2.v[68]*MainFormSLS->hh_1[121]
 + c2.v[69]*MainFormSLS->hh_1[27]
 + c2.v[70]*MainFormSLS->hh_1[93]
 + c2.v[71]*MainFormSLS->hh_1[159]
 + c2.v[72]*MainFormSLS->hh_1[65]
 + c2.v[73]*MainFormSLS->hh_1[131]
 + c2.v[74]*MainFormSLS->hh_1[37]
 + c2.v[75]*MainFormSLS->hh_1[103]
 + c2.v[76]*MainFormSLS->hh_1[9]
 + c2.v[77]*MainFormSLS->hh_1[75]
 + c2.v[78]*MainFormSLS->hh_1[141]
 + c2.v[79]*MainFormSLS->hh_1[47];
s/=N_2;
out.push_back(s);
//������ 114
s =c2.v[0]*MainFormSLS->hh_1[114]
 + c2.v[1]*MainFormSLS->hh_1[22]
 + c2.v[2]*MainFormSLS->hh_1[90]
 + c2.v[3]*MainFormSLS->hh_1[158]
 + c2.v[4]*MainFormSLS->hh_1[66]
 + c2.v[5]*MainFormSLS->hh_1[134]
 + c2.v[6]*MainFormSLS->hh_1[42]
 + c2.v[7]*MainFormSLS->hh_1[110]
 + c2.v[8]*MainFormSLS->hh_1[18]
 + c2.v[9]*MainFormSLS->hh_1[86]
 + c2.v[10]*MainFormSLS->hh_1[154]
 + c2.v[11]*MainFormSLS->hh_1[62]
 + c2.v[12]*MainFormSLS->hh_1[130]
 + c2.v[13]*MainFormSLS->hh_1[38]
 + c2.v[14]*MainFormSLS->hh_1[106]
 + c2.v[15]*MainFormSLS->hh_1[14]
 + c2.v[16]*MainFormSLS->hh_1[82]
 + c2.v[17]*MainFormSLS->hh_1[150]
 + c2.v[18]*MainFormSLS->hh_1[58]
 + c2.v[19]*MainFormSLS->hh_1[126]
 + c2.v[20]*MainFormSLS->hh_1[34]
 + c2.v[21]*MainFormSLS->hh_1[102]
 + c2.v[22]*MainFormSLS->hh_1[10]
 + c2.v[23]*MainFormSLS->hh_1[78]
 + c2.v[24]*MainFormSLS->hh_1[146]
 + c2.v[25]*MainFormSLS->hh_1[54]
 + c2.v[26]*MainFormSLS->hh_1[122]
 + c2.v[27]*MainFormSLS->hh_1[30]
 + c2.v[28]*MainFormSLS->hh_1[98]
 + c2.v[29]*MainFormSLS->hh_1[6]
 + c2.v[30]*MainFormSLS->hh_1[74]
 + c2.v[31]*MainFormSLS->hh_1[142]
 + c2.v[32]*MainFormSLS->hh_1[50]
 + c2.v[33]*MainFormSLS->hh_1[118]
 + c2.v[34]*MainFormSLS->hh_1[26]
 + c2.v[35]*MainFormSLS->hh_1[94]
 + c2.v[36]*MainFormSLS->hh_1[2]
 + c2.v[37]*MainFormSLS->hh_1[70]
 + c2.v[38]*MainFormSLS->hh_1[138]
 + c2.v[39]*MainFormSLS->hh_1[46]
 + c2.v[40]*MainFormSLS->hh_1[114]
 + c2.v[41]*MainFormSLS->hh_1[22]
 + c2.v[42]*MainFormSLS->hh_1[90]
 + c2.v[43]*MainFormSLS->hh_1[158]
 + c2.v[44]*MainFormSLS->hh_1[66]
 + c2.v[45]*MainFormSLS->hh_1[134]
 + c2.v[46]*MainFormSLS->hh_1[42]
 + c2.v[47]*MainFormSLS->hh_1[110]
 + c2.v[48]*MainFormSLS->hh_1[18]
 + c2.v[49]*MainFormSLS->hh_1[86]
 + c2.v[50]*MainFormSLS->hh_1[154]
 + c2.v[51]*MainFormSLS->hh_1[62]
 + c2.v[52]*MainFormSLS->hh_1[130]
 + c2.v[53]*MainFormSLS->hh_1[38]
 + c2.v[54]*MainFormSLS->hh_1[106]
 + c2.v[55]*MainFormSLS->hh_1[14]
 + c2.v[56]*MainFormSLS->hh_1[82]
 + c2.v[57]*MainFormSLS->hh_1[150]
 + c2.v[58]*MainFormSLS->hh_1[58]
 + c2.v[59]*MainFormSLS->hh_1[126]
 + c2.v[60]*MainFormSLS->hh_1[34]
 + c2.v[61]*MainFormSLS->hh_1[102]
 + c2.v[62]*MainFormSLS->hh_1[10]
 + c2.v[63]*MainFormSLS->hh_1[78]
 + c2.v[64]*MainFormSLS->hh_1[146]
 + c2.v[65]*MainFormSLS->hh_1[54]
 + c2.v[66]*MainFormSLS->hh_1[122]
 + c2.v[67]*MainFormSLS->hh_1[30]
 + c2.v[68]*MainFormSLS->hh_1[98]
 + c2.v[69]*MainFormSLS->hh_1[6]
 + c2.v[70]*MainFormSLS->hh_1[74]
 + c2.v[71]*MainFormSLS->hh_1[142]
 + c2.v[72]*MainFormSLS->hh_1[50]
 + c2.v[73]*MainFormSLS->hh_1[118]
 + c2.v[74]*MainFormSLS->hh_1[26]
 + c2.v[75]*MainFormSLS->hh_1[94]
 + c2.v[76]*MainFormSLS->hh_1[2]
 + c2.v[77]*MainFormSLS->hh_1[70]
 + c2.v[78]*MainFormSLS->hh_1[138]
 + c2.v[79]*MainFormSLS->hh_1[46];
s/=N_2;
out.push_back(s);
//������ 115
s =c2.v[0]*MainFormSLS->hh_1[115]
 + c2.v[1]*MainFormSLS->hh_1[25]
 + c2.v[2]*MainFormSLS->hh_1[95]
 + c2.v[3]*MainFormSLS->hh_1[5]
 + c2.v[4]*MainFormSLS->hh_1[75]
 + c2.v[5]*MainFormSLS->hh_1[145]
 + c2.v[6]*MainFormSLS->hh_1[55]
 + c2.v[7]*MainFormSLS->hh_1[125]
 + c2.v[8]*MainFormSLS->hh_1[35]
 + c2.v[9]*MainFormSLS->hh_1[105]
 + c2.v[10]*MainFormSLS->hh_1[15]
 + c2.v[11]*MainFormSLS->hh_1[85]
 + c2.v[12]*MainFormSLS->hh_1[155]
 + c2.v[13]*MainFormSLS->hh_1[65]
 + c2.v[14]*MainFormSLS->hh_1[135]
 + c2.v[15]*MainFormSLS->hh_1[45]
 + c2.v[16]*MainFormSLS->hh_1[115]
 + c2.v[17]*MainFormSLS->hh_1[25]
 + c2.v[18]*MainFormSLS->hh_1[95]
 + c2.v[19]*MainFormSLS->hh_1[5]
 + c2.v[20]*MainFormSLS->hh_1[75]
 + c2.v[21]*MainFormSLS->hh_1[145]
 + c2.v[22]*MainFormSLS->hh_1[55]
 + c2.v[23]*MainFormSLS->hh_1[125]
 + c2.v[24]*MainFormSLS->hh_1[35]
 + c2.v[25]*MainFormSLS->hh_1[105]
 + c2.v[26]*MainFormSLS->hh_1[15]
 + c2.v[27]*MainFormSLS->hh_1[85]
 + c2.v[28]*MainFormSLS->hh_1[155]
 + c2.v[29]*MainFormSLS->hh_1[65]
 + c2.v[30]*MainFormSLS->hh_1[135]
 + c2.v[31]*MainFormSLS->hh_1[45]
 + c2.v[32]*MainFormSLS->hh_1[115]
 + c2.v[33]*MainFormSLS->hh_1[25]
 + c2.v[34]*MainFormSLS->hh_1[95]
 + c2.v[35]*MainFormSLS->hh_1[5]
 + c2.v[36]*MainFormSLS->hh_1[75]
 + c2.v[37]*MainFormSLS->hh_1[145]
 + c2.v[38]*MainFormSLS->hh_1[55]
 + c2.v[39]*MainFormSLS->hh_1[125]
 + c2.v[40]*MainFormSLS->hh_1[35]
 + c2.v[41]*MainFormSLS->hh_1[105]
 + c2.v[42]*MainFormSLS->hh_1[15]
 + c2.v[43]*MainFormSLS->hh_1[85]
 + c2.v[44]*MainFormSLS->hh_1[155]
 + c2.v[45]*MainFormSLS->hh_1[65]
 + c2.v[46]*MainFormSLS->hh_1[135]
 + c2.v[47]*MainFormSLS->hh_1[45]
 + c2.v[48]*MainFormSLS->hh_1[115]
 + c2.v[49]*MainFormSLS->hh_1[25]
 + c2.v[50]*MainFormSLS->hh_1[95]
 + c2.v[51]*MainFormSLS->hh_1[5]
 + c2.v[52]*MainFormSLS->hh_1[75]
 + c2.v[53]*MainFormSLS->hh_1[145]
 + c2.v[54]*MainFormSLS->hh_1[55]
 + c2.v[55]*MainFormSLS->hh_1[125]
 + c2.v[56]*MainFormSLS->hh_1[35]
 + c2.v[57]*MainFormSLS->hh_1[105]
 + c2.v[58]*MainFormSLS->hh_1[15]
 + c2.v[59]*MainFormSLS->hh_1[85]
 + c2.v[60]*MainFormSLS->hh_1[155]
 + c2.v[61]*MainFormSLS->hh_1[65]
 + c2.v[62]*MainFormSLS->hh_1[135]
 + c2.v[63]*MainFormSLS->hh_1[45]
 + c2.v[64]*MainFormSLS->hh_1[115]
 + c2.v[65]*MainFormSLS->hh_1[25]
 + c2.v[66]*MainFormSLS->hh_1[95]
 + c2.v[67]*MainFormSLS->hh_1[5]
 + c2.v[68]*MainFormSLS->hh_1[75]
 + c2.v[69]*MainFormSLS->hh_1[145]
 + c2.v[70]*MainFormSLS->hh_1[55]
 + c2.v[71]*MainFormSLS->hh_1[125]
 + c2.v[72]*MainFormSLS->hh_1[35]
 + c2.v[73]*MainFormSLS->hh_1[105]
 + c2.v[74]*MainFormSLS->hh_1[15]
 + c2.v[75]*MainFormSLS->hh_1[85]
 + c2.v[76]*MainFormSLS->hh_1[155]
 + c2.v[77]*MainFormSLS->hh_1[65]
 + c2.v[78]*MainFormSLS->hh_1[135]
 + c2.v[79]*MainFormSLS->hh_1[45];
s/=N_2;
out.push_back(s);
//������ 116
s =c2.v[0]*MainFormSLS->hh_1[116]
 + c2.v[1]*MainFormSLS->hh_1[28]
 + c2.v[2]*MainFormSLS->hh_1[100]
 + c2.v[3]*MainFormSLS->hh_1[12]
 + c2.v[4]*MainFormSLS->hh_1[84]
 + c2.v[5]*MainFormSLS->hh_1[156]
 + c2.v[6]*MainFormSLS->hh_1[68]
 + c2.v[7]*MainFormSLS->hh_1[140]
 + c2.v[8]*MainFormSLS->hh_1[52]
 + c2.v[9]*MainFormSLS->hh_1[124]
 + c2.v[10]*MainFormSLS->hh_1[36]
 + c2.v[11]*MainFormSLS->hh_1[108]
 + c2.v[12]*MainFormSLS->hh_1[20]
 + c2.v[13]*MainFormSLS->hh_1[92]
 + c2.v[14]*MainFormSLS->hh_1[4]
 + c2.v[15]*MainFormSLS->hh_1[76]
 + c2.v[16]*MainFormSLS->hh_1[148]
 + c2.v[17]*MainFormSLS->hh_1[60]
 + c2.v[18]*MainFormSLS->hh_1[132]
 + c2.v[19]*MainFormSLS->hh_1[44]
 + c2.v[20]*MainFormSLS->hh_1[116]
 + c2.v[21]*MainFormSLS->hh_1[28]
 + c2.v[22]*MainFormSLS->hh_1[100]
 + c2.v[23]*MainFormSLS->hh_1[12]
 + c2.v[24]*MainFormSLS->hh_1[84]
 + c2.v[25]*MainFormSLS->hh_1[156]
 + c2.v[26]*MainFormSLS->hh_1[68]
 + c2.v[27]*MainFormSLS->hh_1[140]
 + c2.v[28]*MainFormSLS->hh_1[52]
 + c2.v[29]*MainFormSLS->hh_1[124]
 + c2.v[30]*MainFormSLS->hh_1[36]
 + c2.v[31]*MainFormSLS->hh_1[108]
 + c2.v[32]*MainFormSLS->hh_1[20]
 + c2.v[33]*MainFormSLS->hh_1[92]
 + c2.v[34]*MainFormSLS->hh_1[4]
 + c2.v[35]*MainFormSLS->hh_1[76]
 + c2.v[36]*MainFormSLS->hh_1[148]
 + c2.v[37]*MainFormSLS->hh_1[60]
 + c2.v[38]*MainFormSLS->hh_1[132]
 + c2.v[39]*MainFormSLS->hh_1[44]
 + c2.v[40]*MainFormSLS->hh_1[116]
 + c2.v[41]*MainFormSLS->hh_1[28]
 + c2.v[42]*MainFormSLS->hh_1[100]
 + c2.v[43]*MainFormSLS->hh_1[12]
 + c2.v[44]*MainFormSLS->hh_1[84]
 + c2.v[45]*MainFormSLS->hh_1[156]
 + c2.v[46]*MainFormSLS->hh_1[68]
 + c2.v[47]*MainFormSLS->hh_1[140]
 + c2.v[48]*MainFormSLS->hh_1[52]
 + c2.v[49]*MainFormSLS->hh_1[124]
 + c2.v[50]*MainFormSLS->hh_1[36]
 + c2.v[51]*MainFormSLS->hh_1[108]
 + c2.v[52]*MainFormSLS->hh_1[20]
 + c2.v[53]*MainFormSLS->hh_1[92]
 + c2.v[54]*MainFormSLS->hh_1[4]
 + c2.v[55]*MainFormSLS->hh_1[76]
 + c2.v[56]*MainFormSLS->hh_1[148]
 + c2.v[57]*MainFormSLS->hh_1[60]
 + c2.v[58]*MainFormSLS->hh_1[132]
 + c2.v[59]*MainFormSLS->hh_1[44]
 + c2.v[60]*MainFormSLS->hh_1[116]
 + c2.v[61]*MainFormSLS->hh_1[28]
 + c2.v[62]*MainFormSLS->hh_1[100]
 + c2.v[63]*MainFormSLS->hh_1[12]
 + c2.v[64]*MainFormSLS->hh_1[84]
 + c2.v[65]*MainFormSLS->hh_1[156]
 + c2.v[66]*MainFormSLS->hh_1[68]
 + c2.v[67]*MainFormSLS->hh_1[140]
 + c2.v[68]*MainFormSLS->hh_1[52]
 + c2.v[69]*MainFormSLS->hh_1[124]
 + c2.v[70]*MainFormSLS->hh_1[36]
 + c2.v[71]*MainFormSLS->hh_1[108]
 + c2.v[72]*MainFormSLS->hh_1[20]
 + c2.v[73]*MainFormSLS->hh_1[92]
 + c2.v[74]*MainFormSLS->hh_1[4]
 + c2.v[75]*MainFormSLS->hh_1[76]
 + c2.v[76]*MainFormSLS->hh_1[148]
 + c2.v[77]*MainFormSLS->hh_1[60]
 + c2.v[78]*MainFormSLS->hh_1[132]
 + c2.v[79]*MainFormSLS->hh_1[44];
s/=N_2;
out.push_back(s);
//������ 117
s =c2.v[0]*MainFormSLS->hh_1[117]
 + c2.v[1]*MainFormSLS->hh_1[31]
 + c2.v[2]*MainFormSLS->hh_1[105]
 + c2.v[3]*MainFormSLS->hh_1[19]
 + c2.v[4]*MainFormSLS->hh_1[93]
 + c2.v[5]*MainFormSLS->hh_1[7]
 + c2.v[6]*MainFormSLS->hh_1[81]
 + c2.v[7]*MainFormSLS->hh_1[155]
 + c2.v[8]*MainFormSLS->hh_1[69]
 + c2.v[9]*MainFormSLS->hh_1[143]
 + c2.v[10]*MainFormSLS->hh_1[57]
 + c2.v[11]*MainFormSLS->hh_1[131]
 + c2.v[12]*MainFormSLS->hh_1[45]
 + c2.v[13]*MainFormSLS->hh_1[119]
 + c2.v[14]*MainFormSLS->hh_1[33]
 + c2.v[15]*MainFormSLS->hh_1[107]
 + c2.v[16]*MainFormSLS->hh_1[21]
 + c2.v[17]*MainFormSLS->hh_1[95]
 + c2.v[18]*MainFormSLS->hh_1[9]
 + c2.v[19]*MainFormSLS->hh_1[83]
 + c2.v[20]*MainFormSLS->hh_1[157]
 + c2.v[21]*MainFormSLS->hh_1[71]
 + c2.v[22]*MainFormSLS->hh_1[145]
 + c2.v[23]*MainFormSLS->hh_1[59]
 + c2.v[24]*MainFormSLS->hh_1[133]
 + c2.v[25]*MainFormSLS->hh_1[47]
 + c2.v[26]*MainFormSLS->hh_1[121]
 + c2.v[27]*MainFormSLS->hh_1[35]
 + c2.v[28]*MainFormSLS->hh_1[109]
 + c2.v[29]*MainFormSLS->hh_1[23]
 + c2.v[30]*MainFormSLS->hh_1[97]
 + c2.v[31]*MainFormSLS->hh_1[11]
 + c2.v[32]*MainFormSLS->hh_1[85]
 + c2.v[33]*MainFormSLS->hh_1[159]
 + c2.v[34]*MainFormSLS->hh_1[73]
 + c2.v[35]*MainFormSLS->hh_1[147]
 + c2.v[36]*MainFormSLS->hh_1[61]
 + c2.v[37]*MainFormSLS->hh_1[135]
 + c2.v[38]*MainFormSLS->hh_1[49]
 + c2.v[39]*MainFormSLS->hh_1[123]
 + c2.v[40]*MainFormSLS->hh_1[37]
 + c2.v[41]*MainFormSLS->hh_1[111]
 + c2.v[42]*MainFormSLS->hh_1[25]
 + c2.v[43]*MainFormSLS->hh_1[99]
 + c2.v[44]*MainFormSLS->hh_1[13]
 + c2.v[45]*MainFormSLS->hh_1[87]
 + c2.v[46]*MainFormSLS->hh_1[1]
 + c2.v[47]*MainFormSLS->hh_1[75]
 + c2.v[48]*MainFormSLS->hh_1[149]
 + c2.v[49]*MainFormSLS->hh_1[63]
 + c2.v[50]*MainFormSLS->hh_1[137]
 + c2.v[51]*MainFormSLS->hh_1[51]
 + c2.v[52]*MainFormSLS->hh_1[125]
 + c2.v[53]*MainFormSLS->hh_1[39]
 + c2.v[54]*MainFormSLS->hh_1[113]
 + c2.v[55]*MainFormSLS->hh_1[27]
 + c2.v[56]*MainFormSLS->hh_1[101]
 + c2.v[57]*MainFormSLS->hh_1[15]
 + c2.v[58]*MainFormSLS->hh_1[89]
 + c2.v[59]*MainFormSLS->hh_1[3]
 + c2.v[60]*MainFormSLS->hh_1[77]
 + c2.v[61]*MainFormSLS->hh_1[151]
 + c2.v[62]*MainFormSLS->hh_1[65]
 + c2.v[63]*MainFormSLS->hh_1[139]
 + c2.v[64]*MainFormSLS->hh_1[53]
 + c2.v[65]*MainFormSLS->hh_1[127]
 + c2.v[66]*MainFormSLS->hh_1[41]
 + c2.v[67]*MainFormSLS->hh_1[115]
 + c2.v[68]*MainFormSLS->hh_1[29]
 + c2.v[69]*MainFormSLS->hh_1[103]
 + c2.v[70]*MainFormSLS->hh_1[17]
 + c2.v[71]*MainFormSLS->hh_1[91]
 + c2.v[72]*MainFormSLS->hh_1[5]
 + c2.v[73]*MainFormSLS->hh_1[79]
 + c2.v[74]*MainFormSLS->hh_1[153]
 + c2.v[75]*MainFormSLS->hh_1[67]
 + c2.v[76]*MainFormSLS->hh_1[141]
 + c2.v[77]*MainFormSLS->hh_1[55]
 + c2.v[78]*MainFormSLS->hh_1[129]
 + c2.v[79]*MainFormSLS->hh_1[43];
s/=N_2;
out.push_back(s);
//������ 118
s =c2.v[0]*MainFormSLS->hh_1[118]
 + c2.v[1]*MainFormSLS->hh_1[34]
 + c2.v[2]*MainFormSLS->hh_1[110]
 + c2.v[3]*MainFormSLS->hh_1[26]
 + c2.v[4]*MainFormSLS->hh_1[102]
 + c2.v[5]*MainFormSLS->hh_1[18]
 + c2.v[6]*MainFormSLS->hh_1[94]
 + c2.v[7]*MainFormSLS->hh_1[10]
 + c2.v[8]*MainFormSLS->hh_1[86]
 + c2.v[9]*MainFormSLS->hh_1[2]
 + c2.v[10]*MainFormSLS->hh_1[78]
 + c2.v[11]*MainFormSLS->hh_1[154]
 + c2.v[12]*MainFormSLS->hh_1[70]
 + c2.v[13]*MainFormSLS->hh_1[146]
 + c2.v[14]*MainFormSLS->hh_1[62]
 + c2.v[15]*MainFormSLS->hh_1[138]
 + c2.v[16]*MainFormSLS->hh_1[54]
 + c2.v[17]*MainFormSLS->hh_1[130]
 + c2.v[18]*MainFormSLS->hh_1[46]
 + c2.v[19]*MainFormSLS->hh_1[122]
 + c2.v[20]*MainFormSLS->hh_1[38]
 + c2.v[21]*MainFormSLS->hh_1[114]
 + c2.v[22]*MainFormSLS->hh_1[30]
 + c2.v[23]*MainFormSLS->hh_1[106]
 + c2.v[24]*MainFormSLS->hh_1[22]
 + c2.v[25]*MainFormSLS->hh_1[98]
 + c2.v[26]*MainFormSLS->hh_1[14]
 + c2.v[27]*MainFormSLS->hh_1[90]
 + c2.v[28]*MainFormSLS->hh_1[6]
 + c2.v[29]*MainFormSLS->hh_1[82]
 + c2.v[30]*MainFormSLS->hh_1[158]
 + c2.v[31]*MainFormSLS->hh_1[74]
 + c2.v[32]*MainFormSLS->hh_1[150]
 + c2.v[33]*MainFormSLS->hh_1[66]
 + c2.v[34]*MainFormSLS->hh_1[142]
 + c2.v[35]*MainFormSLS->hh_1[58]
 + c2.v[36]*MainFormSLS->hh_1[134]
 + c2.v[37]*MainFormSLS->hh_1[50]
 + c2.v[38]*MainFormSLS->hh_1[126]
 + c2.v[39]*MainFormSLS->hh_1[42]
 + c2.v[40]*MainFormSLS->hh_1[118]
 + c2.v[41]*MainFormSLS->hh_1[34]
 + c2.v[42]*MainFormSLS->hh_1[110]
 + c2.v[43]*MainFormSLS->hh_1[26]
 + c2.v[44]*MainFormSLS->hh_1[102]
 + c2.v[45]*MainFormSLS->hh_1[18]
 + c2.v[46]*MainFormSLS->hh_1[94]
 + c2.v[47]*MainFormSLS->hh_1[10]
 + c2.v[48]*MainFormSLS->hh_1[86]
 + c2.v[49]*MainFormSLS->hh_1[2]
 + c2.v[50]*MainFormSLS->hh_1[78]
 + c2.v[51]*MainFormSLS->hh_1[154]
 + c2.v[52]*MainFormSLS->hh_1[70]
 + c2.v[53]*MainFormSLS->hh_1[146]
 + c2.v[54]*MainFormSLS->hh_1[62]
 + c2.v[55]*MainFormSLS->hh_1[138]
 + c2.v[56]*MainFormSLS->hh_1[54]
 + c2.v[57]*MainFormSLS->hh_1[130]
 + c2.v[58]*MainFormSLS->hh_1[46]
 + c2.v[59]*MainFormSLS->hh_1[122]
 + c2.v[60]*MainFormSLS->hh_1[38]
 + c2.v[61]*MainFormSLS->hh_1[114]
 + c2.v[62]*MainFormSLS->hh_1[30]
 + c2.v[63]*MainFormSLS->hh_1[106]
 + c2.v[64]*MainFormSLS->hh_1[22]
 + c2.v[65]*MainFormSLS->hh_1[98]
 + c2.v[66]*MainFormSLS->hh_1[14]
 + c2.v[67]*MainFormSLS->hh_1[90]
 + c2.v[68]*MainFormSLS->hh_1[6]
 + c2.v[69]*MainFormSLS->hh_1[82]
 + c2.v[70]*MainFormSLS->hh_1[158]
 + c2.v[71]*MainFormSLS->hh_1[74]
 + c2.v[72]*MainFormSLS->hh_1[150]
 + c2.v[73]*MainFormSLS->hh_1[66]
 + c2.v[74]*MainFormSLS->hh_1[142]
 + c2.v[75]*MainFormSLS->hh_1[58]
 + c2.v[76]*MainFormSLS->hh_1[134]
 + c2.v[77]*MainFormSLS->hh_1[50]
 + c2.v[78]*MainFormSLS->hh_1[126]
 + c2.v[79]*MainFormSLS->hh_1[42];
s/=N_2;
out.push_back(s);
//������ 119
s =c2.v[0]*MainFormSLS->hh_1[119]
 + c2.v[1]*MainFormSLS->hh_1[37]
 + c2.v[2]*MainFormSLS->hh_1[115]
 + c2.v[3]*MainFormSLS->hh_1[33]
 + c2.v[4]*MainFormSLS->hh_1[111]
 + c2.v[5]*MainFormSLS->hh_1[29]
 + c2.v[6]*MainFormSLS->hh_1[107]
 + c2.v[7]*MainFormSLS->hh_1[25]
 + c2.v[8]*MainFormSLS->hh_1[103]
 + c2.v[9]*MainFormSLS->hh_1[21]
 + c2.v[10]*MainFormSLS->hh_1[99]
 + c2.v[11]*MainFormSLS->hh_1[17]
 + c2.v[12]*MainFormSLS->hh_1[95]
 + c2.v[13]*MainFormSLS->hh_1[13]
 + c2.v[14]*MainFormSLS->hh_1[91]
 + c2.v[15]*MainFormSLS->hh_1[9]
 + c2.v[16]*MainFormSLS->hh_1[87]
 + c2.v[17]*MainFormSLS->hh_1[5]
 + c2.v[18]*MainFormSLS->hh_1[83]
 + c2.v[19]*MainFormSLS->hh_1[1]
 + c2.v[20]*MainFormSLS->hh_1[79]
 + c2.v[21]*MainFormSLS->hh_1[157]
 + c2.v[22]*MainFormSLS->hh_1[75]
 + c2.v[23]*MainFormSLS->hh_1[153]
 + c2.v[24]*MainFormSLS->hh_1[71]
 + c2.v[25]*MainFormSLS->hh_1[149]
 + c2.v[26]*MainFormSLS->hh_1[67]
 + c2.v[27]*MainFormSLS->hh_1[145]
 + c2.v[28]*MainFormSLS->hh_1[63]
 + c2.v[29]*MainFormSLS->hh_1[141]
 + c2.v[30]*MainFormSLS->hh_1[59]
 + c2.v[31]*MainFormSLS->hh_1[137]
 + c2.v[32]*MainFormSLS->hh_1[55]
 + c2.v[33]*MainFormSLS->hh_1[133]
 + c2.v[34]*MainFormSLS->hh_1[51]
 + c2.v[35]*MainFormSLS->hh_1[129]
 + c2.v[36]*MainFormSLS->hh_1[47]
 + c2.v[37]*MainFormSLS->hh_1[125]
 + c2.v[38]*MainFormSLS->hh_1[43]
 + c2.v[39]*MainFormSLS->hh_1[121]
 + c2.v[40]*MainFormSLS->hh_1[39]
 + c2.v[41]*MainFormSLS->hh_1[117]
 + c2.v[42]*MainFormSLS->hh_1[35]
 + c2.v[43]*MainFormSLS->hh_1[113]
 + c2.v[44]*MainFormSLS->hh_1[31]
 + c2.v[45]*MainFormSLS->hh_1[109]
 + c2.v[46]*MainFormSLS->hh_1[27]
 + c2.v[47]*MainFormSLS->hh_1[105]
 + c2.v[48]*MainFormSLS->hh_1[23]
 + c2.v[49]*MainFormSLS->hh_1[101]
 + c2.v[50]*MainFormSLS->hh_1[19]
 + c2.v[51]*MainFormSLS->hh_1[97]
 + c2.v[52]*MainFormSLS->hh_1[15]
 + c2.v[53]*MainFormSLS->hh_1[93]
 + c2.v[54]*MainFormSLS->hh_1[11]
 + c2.v[55]*MainFormSLS->hh_1[89]
 + c2.v[56]*MainFormSLS->hh_1[7]
 + c2.v[57]*MainFormSLS->hh_1[85]
 + c2.v[58]*MainFormSLS->hh_1[3]
 + c2.v[59]*MainFormSLS->hh_1[81]
 + c2.v[60]*MainFormSLS->hh_1[159]
 + c2.v[61]*MainFormSLS->hh_1[77]
 + c2.v[62]*MainFormSLS->hh_1[155]
 + c2.v[63]*MainFormSLS->hh_1[73]
 + c2.v[64]*MainFormSLS->hh_1[151]
 + c2.v[65]*MainFormSLS->hh_1[69]
 + c2.v[66]*MainFormSLS->hh_1[147]
 + c2.v[67]*MainFormSLS->hh_1[65]
 + c2.v[68]*MainFormSLS->hh_1[143]
 + c2.v[69]*MainFormSLS->hh_1[61]
 + c2.v[70]*MainFormSLS->hh_1[139]
 + c2.v[71]*MainFormSLS->hh_1[57]
 + c2.v[72]*MainFormSLS->hh_1[135]
 + c2.v[73]*MainFormSLS->hh_1[53]
 + c2.v[74]*MainFormSLS->hh_1[131]
 + c2.v[75]*MainFormSLS->hh_1[49]
 + c2.v[76]*MainFormSLS->hh_1[127]
 + c2.v[77]*MainFormSLS->hh_1[45]
 + c2.v[78]*MainFormSLS->hh_1[123]
 + c2.v[79]*MainFormSLS->hh_1[41];
s/=N_2;
out.push_back(s);
//������ 120
s =c2.v[0]*MainFormSLS->hh_1[120]
 + c2.v[1]*MainFormSLS->hh_1[40]
 + c2.v[2]*MainFormSLS->hh_1[120]
 + c2.v[3]*MainFormSLS->hh_1[40]
 + c2.v[4]*MainFormSLS->hh_1[120]
 + c2.v[5]*MainFormSLS->hh_1[40]
 + c2.v[6]*MainFormSLS->hh_1[120]
 + c2.v[7]*MainFormSLS->hh_1[40]
 + c2.v[8]*MainFormSLS->hh_1[120]
 + c2.v[9]*MainFormSLS->hh_1[40]
 + c2.v[10]*MainFormSLS->hh_1[120]
 + c2.v[11]*MainFormSLS->hh_1[40]
 + c2.v[12]*MainFormSLS->hh_1[120]
 + c2.v[13]*MainFormSLS->hh_1[40]
 + c2.v[14]*MainFormSLS->hh_1[120]
 + c2.v[15]*MainFormSLS->hh_1[40]
 + c2.v[16]*MainFormSLS->hh_1[120]
 + c2.v[17]*MainFormSLS->hh_1[40]
 + c2.v[18]*MainFormSLS->hh_1[120]
 + c2.v[19]*MainFormSLS->hh_1[40]
 + c2.v[20]*MainFormSLS->hh_1[120]
 + c2.v[21]*MainFormSLS->hh_1[40]
 + c2.v[22]*MainFormSLS->hh_1[120]
 + c2.v[23]*MainFormSLS->hh_1[40]
 + c2.v[24]*MainFormSLS->hh_1[120]
 + c2.v[25]*MainFormSLS->hh_1[40]
 + c2.v[26]*MainFormSLS->hh_1[120]
 + c2.v[27]*MainFormSLS->hh_1[40]
 + c2.v[28]*MainFormSLS->hh_1[120]
 + c2.v[29]*MainFormSLS->hh_1[40]
 + c2.v[30]*MainFormSLS->hh_1[120]
 + c2.v[31]*MainFormSLS->hh_1[40]
 + c2.v[32]*MainFormSLS->hh_1[120]
 + c2.v[33]*MainFormSLS->hh_1[40]
 + c2.v[34]*MainFormSLS->hh_1[120]
 + c2.v[35]*MainFormSLS->hh_1[40]
 + c2.v[36]*MainFormSLS->hh_1[120]
 + c2.v[37]*MainFormSLS->hh_1[40]
 + c2.v[38]*MainFormSLS->hh_1[120]
 + c2.v[39]*MainFormSLS->hh_1[40]
 + c2.v[40]*MainFormSLS->hh_1[120]
 + c2.v[41]*MainFormSLS->hh_1[40]
 + c2.v[42]*MainFormSLS->hh_1[120]
 + c2.v[43]*MainFormSLS->hh_1[40]
 + c2.v[44]*MainFormSLS->hh_1[120]
 + c2.v[45]*MainFormSLS->hh_1[40]
 + c2.v[46]*MainFormSLS->hh_1[120]
 + c2.v[47]*MainFormSLS->hh_1[40]
 + c2.v[48]*MainFormSLS->hh_1[120]
 + c2.v[49]*MainFormSLS->hh_1[40]
 + c2.v[50]*MainFormSLS->hh_1[120]
 + c2.v[51]*MainFormSLS->hh_1[40]
 + c2.v[52]*MainFormSLS->hh_1[120]
 + c2.v[53]*MainFormSLS->hh_1[40]
 + c2.v[54]*MainFormSLS->hh_1[120]
 + c2.v[55]*MainFormSLS->hh_1[40]
 + c2.v[56]*MainFormSLS->hh_1[120]
 + c2.v[57]*MainFormSLS->hh_1[40]
 + c2.v[58]*MainFormSLS->hh_1[120]
 + c2.v[59]*MainFormSLS->hh_1[40]
 + c2.v[60]*MainFormSLS->hh_1[120]
 + c2.v[61]*MainFormSLS->hh_1[40]
 + c2.v[62]*MainFormSLS->hh_1[120]
 + c2.v[63]*MainFormSLS->hh_1[40]
 + c2.v[64]*MainFormSLS->hh_1[120]
 + c2.v[65]*MainFormSLS->hh_1[40]
 + c2.v[66]*MainFormSLS->hh_1[120]
 + c2.v[67]*MainFormSLS->hh_1[40]
 + c2.v[68]*MainFormSLS->hh_1[120]
 + c2.v[69]*MainFormSLS->hh_1[40]
 + c2.v[70]*MainFormSLS->hh_1[120]
 + c2.v[71]*MainFormSLS->hh_1[40]
 + c2.v[72]*MainFormSLS->hh_1[120]
 + c2.v[73]*MainFormSLS->hh_1[40]
 + c2.v[74]*MainFormSLS->hh_1[120]
 + c2.v[75]*MainFormSLS->hh_1[40]
 + c2.v[76]*MainFormSLS->hh_1[120]
 + c2.v[77]*MainFormSLS->hh_1[40]
 + c2.v[78]*MainFormSLS->hh_1[120]
 + c2.v[79]*MainFormSLS->hh_1[40];
s/=N_2;
out.push_back(s);
//������ 121
s =c2.v[0]*MainFormSLS->hh_1[121]
 + c2.v[1]*MainFormSLS->hh_1[43]
 + c2.v[2]*MainFormSLS->hh_1[125]
 + c2.v[3]*MainFormSLS->hh_1[47]
 + c2.v[4]*MainFormSLS->hh_1[129]
 + c2.v[5]*MainFormSLS->hh_1[51]
 + c2.v[6]*MainFormSLS->hh_1[133]
 + c2.v[7]*MainFormSLS->hh_1[55]
 + c2.v[8]*MainFormSLS->hh_1[137]
 + c2.v[9]*MainFormSLS->hh_1[59]
 + c2.v[10]*MainFormSLS->hh_1[141]
 + c2.v[11]*MainFormSLS->hh_1[63]
 + c2.v[12]*MainFormSLS->hh_1[145]
 + c2.v[13]*MainFormSLS->hh_1[67]
 + c2.v[14]*MainFormSLS->hh_1[149]
 + c2.v[15]*MainFormSLS->hh_1[71]
 + c2.v[16]*MainFormSLS->hh_1[153]
 + c2.v[17]*MainFormSLS->hh_1[75]
 + c2.v[18]*MainFormSLS->hh_1[157]
 + c2.v[19]*MainFormSLS->hh_1[79]
 + c2.v[20]*MainFormSLS->hh_1[1]
 + c2.v[21]*MainFormSLS->hh_1[83]
 + c2.v[22]*MainFormSLS->hh_1[5]
 + c2.v[23]*MainFormSLS->hh_1[87]
 + c2.v[24]*MainFormSLS->hh_1[9]
 + c2.v[25]*MainFormSLS->hh_1[91]
 + c2.v[26]*MainFormSLS->hh_1[13]
 + c2.v[27]*MainFormSLS->hh_1[95]
 + c2.v[28]*MainFormSLS->hh_1[17]
 + c2.v[29]*MainFormSLS->hh_1[99]
 + c2.v[30]*MainFormSLS->hh_1[21]
 + c2.v[31]*MainFormSLS->hh_1[103]
 + c2.v[32]*MainFormSLS->hh_1[25]
 + c2.v[33]*MainFormSLS->hh_1[107]
 + c2.v[34]*MainFormSLS->hh_1[29]
 + c2.v[35]*MainFormSLS->hh_1[111]
 + c2.v[36]*MainFormSLS->hh_1[33]
 + c2.v[37]*MainFormSLS->hh_1[115]
 + c2.v[38]*MainFormSLS->hh_1[37]
 + c2.v[39]*MainFormSLS->hh_1[119]
 + c2.v[40]*MainFormSLS->hh_1[41]
 + c2.v[41]*MainFormSLS->hh_1[123]
 + c2.v[42]*MainFormSLS->hh_1[45]
 + c2.v[43]*MainFormSLS->hh_1[127]
 + c2.v[44]*MainFormSLS->hh_1[49]
 + c2.v[45]*MainFormSLS->hh_1[131]
 + c2.v[46]*MainFormSLS->hh_1[53]
 + c2.v[47]*MainFormSLS->hh_1[135]
 + c2.v[48]*MainFormSLS->hh_1[57]
 + c2.v[49]*MainFormSLS->hh_1[139]
 + c2.v[50]*MainFormSLS->hh_1[61]
 + c2.v[51]*MainFormSLS->hh_1[143]
 + c2.v[52]*MainFormSLS->hh_1[65]
 + c2.v[53]*MainFormSLS->hh_1[147]
 + c2.v[54]*MainFormSLS->hh_1[69]
 + c2.v[55]*MainFormSLS->hh_1[151]
 + c2.v[56]*MainFormSLS->hh_1[73]
 + c2.v[57]*MainFormSLS->hh_1[155]
 + c2.v[58]*MainFormSLS->hh_1[77]
 + c2.v[59]*MainFormSLS->hh_1[159]
 + c2.v[60]*MainFormSLS->hh_1[81]
 + c2.v[61]*MainFormSLS->hh_1[3]
 + c2.v[62]*MainFormSLS->hh_1[85]
 + c2.v[63]*MainFormSLS->hh_1[7]
 + c2.v[64]*MainFormSLS->hh_1[89]
 + c2.v[65]*MainFormSLS->hh_1[11]
 + c2.v[66]*MainFormSLS->hh_1[93]
 + c2.v[67]*MainFormSLS->hh_1[15]
 + c2.v[68]*MainFormSLS->hh_1[97]
 + c2.v[69]*MainFormSLS->hh_1[19]
 + c2.v[70]*MainFormSLS->hh_1[101]
 + c2.v[71]*MainFormSLS->hh_1[23]
 + c2.v[72]*MainFormSLS->hh_1[105]
 + c2.v[73]*MainFormSLS->hh_1[27]
 + c2.v[74]*MainFormSLS->hh_1[109]
 + c2.v[75]*MainFormSLS->hh_1[31]
 + c2.v[76]*MainFormSLS->hh_1[113]
 + c2.v[77]*MainFormSLS->hh_1[35]
 + c2.v[78]*MainFormSLS->hh_1[117]
 + c2.v[79]*MainFormSLS->hh_1[39];
s/=N_2;
out.push_back(s);
//������ 122
s =c2.v[0]*MainFormSLS->hh_1[122]
 + c2.v[1]*MainFormSLS->hh_1[46]
 + c2.v[2]*MainFormSLS->hh_1[130]
 + c2.v[3]*MainFormSLS->hh_1[54]
 + c2.v[4]*MainFormSLS->hh_1[138]
 + c2.v[5]*MainFormSLS->hh_1[62]
 + c2.v[6]*MainFormSLS->hh_1[146]
 + c2.v[7]*MainFormSLS->hh_1[70]
 + c2.v[8]*MainFormSLS->hh_1[154]
 + c2.v[9]*MainFormSLS->hh_1[78]
 + c2.v[10]*MainFormSLS->hh_1[2]
 + c2.v[11]*MainFormSLS->hh_1[86]
 + c2.v[12]*MainFormSLS->hh_1[10]
 + c2.v[13]*MainFormSLS->hh_1[94]
 + c2.v[14]*MainFormSLS->hh_1[18]
 + c2.v[15]*MainFormSLS->hh_1[102]
 + c2.v[16]*MainFormSLS->hh_1[26]
 + c2.v[17]*MainFormSLS->hh_1[110]
 + c2.v[18]*MainFormSLS->hh_1[34]
 + c2.v[19]*MainFormSLS->hh_1[118]
 + c2.v[20]*MainFormSLS->hh_1[42]
 + c2.v[21]*MainFormSLS->hh_1[126]
 + c2.v[22]*MainFormSLS->hh_1[50]
 + c2.v[23]*MainFormSLS->hh_1[134]
 + c2.v[24]*MainFormSLS->hh_1[58]
 + c2.v[25]*MainFormSLS->hh_1[142]
 + c2.v[26]*MainFormSLS->hh_1[66]
 + c2.v[27]*MainFormSLS->hh_1[150]
 + c2.v[28]*MainFormSLS->hh_1[74]
 + c2.v[29]*MainFormSLS->hh_1[158]
 + c2.v[30]*MainFormSLS->hh_1[82]
 + c2.v[31]*MainFormSLS->hh_1[6]
 + c2.v[32]*MainFormSLS->hh_1[90]
 + c2.v[33]*MainFormSLS->hh_1[14]
 + c2.v[34]*MainFormSLS->hh_1[98]
 + c2.v[35]*MainFormSLS->hh_1[22]
 + c2.v[36]*MainFormSLS->hh_1[106]
 + c2.v[37]*MainFormSLS->hh_1[30]
 + c2.v[38]*MainFormSLS->hh_1[114]
 + c2.v[39]*MainFormSLS->hh_1[38]
 + c2.v[40]*MainFormSLS->hh_1[122]
 + c2.v[41]*MainFormSLS->hh_1[46]
 + c2.v[42]*MainFormSLS->hh_1[130]
 + c2.v[43]*MainFormSLS->hh_1[54]
 + c2.v[44]*MainFormSLS->hh_1[138]
 + c2.v[45]*MainFormSLS->hh_1[62]
 + c2.v[46]*MainFormSLS->hh_1[146]
 + c2.v[47]*MainFormSLS->hh_1[70]
 + c2.v[48]*MainFormSLS->hh_1[154]
 + c2.v[49]*MainFormSLS->hh_1[78]
 + c2.v[50]*MainFormSLS->hh_1[2]
 + c2.v[51]*MainFormSLS->hh_1[86]
 + c2.v[52]*MainFormSLS->hh_1[10]
 + c2.v[53]*MainFormSLS->hh_1[94]
 + c2.v[54]*MainFormSLS->hh_1[18]
 + c2.v[55]*MainFormSLS->hh_1[102]
 + c2.v[56]*MainFormSLS->hh_1[26]
 + c2.v[57]*MainFormSLS->hh_1[110]
 + c2.v[58]*MainFormSLS->hh_1[34]
 + c2.v[59]*MainFormSLS->hh_1[118]
 + c2.v[60]*MainFormSLS->hh_1[42]
 + c2.v[61]*MainFormSLS->hh_1[126]
 + c2.v[62]*MainFormSLS->hh_1[50]
 + c2.v[63]*MainFormSLS->hh_1[134]
 + c2.v[64]*MainFormSLS->hh_1[58]
 + c2.v[65]*MainFormSLS->hh_1[142]
 + c2.v[66]*MainFormSLS->hh_1[66]
 + c2.v[67]*MainFormSLS->hh_1[150]
 + c2.v[68]*MainFormSLS->hh_1[74]
 + c2.v[69]*MainFormSLS->hh_1[158]
 + c2.v[70]*MainFormSLS->hh_1[82]
 + c2.v[71]*MainFormSLS->hh_1[6]
 + c2.v[72]*MainFormSLS->hh_1[90]
 + c2.v[73]*MainFormSLS->hh_1[14]
 + c2.v[74]*MainFormSLS->hh_1[98]
 + c2.v[75]*MainFormSLS->hh_1[22]
 + c2.v[76]*MainFormSLS->hh_1[106]
 + c2.v[77]*MainFormSLS->hh_1[30]
 + c2.v[78]*MainFormSLS->hh_1[114]
 + c2.v[79]*MainFormSLS->hh_1[38];
s/=N_2;
out.push_back(s);
//������ 123
s =c2.v[0]*MainFormSLS->hh_1[123]
 + c2.v[1]*MainFormSLS->hh_1[49]
 + c2.v[2]*MainFormSLS->hh_1[135]
 + c2.v[3]*MainFormSLS->hh_1[61]
 + c2.v[4]*MainFormSLS->hh_1[147]
 + c2.v[5]*MainFormSLS->hh_1[73]
 + c2.v[6]*MainFormSLS->hh_1[159]
 + c2.v[7]*MainFormSLS->hh_1[85]
 + c2.v[8]*MainFormSLS->hh_1[11]
 + c2.v[9]*MainFormSLS->hh_1[97]
 + c2.v[10]*MainFormSLS->hh_1[23]
 + c2.v[11]*MainFormSLS->hh_1[109]
 + c2.v[12]*MainFormSLS->hh_1[35]
 + c2.v[13]*MainFormSLS->hh_1[121]
 + c2.v[14]*MainFormSLS->hh_1[47]
 + c2.v[15]*MainFormSLS->hh_1[133]
 + c2.v[16]*MainFormSLS->hh_1[59]
 + c2.v[17]*MainFormSLS->hh_1[145]
 + c2.v[18]*MainFormSLS->hh_1[71]
 + c2.v[19]*MainFormSLS->hh_1[157]
 + c2.v[20]*MainFormSLS->hh_1[83]
 + c2.v[21]*MainFormSLS->hh_1[9]
 + c2.v[22]*MainFormSLS->hh_1[95]
 + c2.v[23]*MainFormSLS->hh_1[21]
 + c2.v[24]*MainFormSLS->hh_1[107]
 + c2.v[25]*MainFormSLS->hh_1[33]
 + c2.v[26]*MainFormSLS->hh_1[119]
 + c2.v[27]*MainFormSLS->hh_1[45]
 + c2.v[28]*MainFormSLS->hh_1[131]
 + c2.v[29]*MainFormSLS->hh_1[57]
 + c2.v[30]*MainFormSLS->hh_1[143]
 + c2.v[31]*MainFormSLS->hh_1[69]
 + c2.v[32]*MainFormSLS->hh_1[155]
 + c2.v[33]*MainFormSLS->hh_1[81]
 + c2.v[34]*MainFormSLS->hh_1[7]
 + c2.v[35]*MainFormSLS->hh_1[93]
 + c2.v[36]*MainFormSLS->hh_1[19]
 + c2.v[37]*MainFormSLS->hh_1[105]
 + c2.v[38]*MainFormSLS->hh_1[31]
 + c2.v[39]*MainFormSLS->hh_1[117]
 + c2.v[40]*MainFormSLS->hh_1[43]
 + c2.v[41]*MainFormSLS->hh_1[129]
 + c2.v[42]*MainFormSLS->hh_1[55]
 + c2.v[43]*MainFormSLS->hh_1[141]
 + c2.v[44]*MainFormSLS->hh_1[67]
 + c2.v[45]*MainFormSLS->hh_1[153]
 + c2.v[46]*MainFormSLS->hh_1[79]
 + c2.v[47]*MainFormSLS->hh_1[5]
 + c2.v[48]*MainFormSLS->hh_1[91]
 + c2.v[49]*MainFormSLS->hh_1[17]
 + c2.v[50]*MainFormSLS->hh_1[103]
 + c2.v[51]*MainFormSLS->hh_1[29]
 + c2.v[52]*MainFormSLS->hh_1[115]
 + c2.v[53]*MainFormSLS->hh_1[41]
 + c2.v[54]*MainFormSLS->hh_1[127]
 + c2.v[55]*MainFormSLS->hh_1[53]
 + c2.v[56]*MainFormSLS->hh_1[139]
 + c2.v[57]*MainFormSLS->hh_1[65]
 + c2.v[58]*MainFormSLS->hh_1[151]
 + c2.v[59]*MainFormSLS->hh_1[77]
 + c2.v[60]*MainFormSLS->hh_1[3]
 + c2.v[61]*MainFormSLS->hh_1[89]
 + c2.v[62]*MainFormSLS->hh_1[15]
 + c2.v[63]*MainFormSLS->hh_1[101]
 + c2.v[64]*MainFormSLS->hh_1[27]
 + c2.v[65]*MainFormSLS->hh_1[113]
 + c2.v[66]*MainFormSLS->hh_1[39]
 + c2.v[67]*MainFormSLS->hh_1[125]
 + c2.v[68]*MainFormSLS->hh_1[51]
 + c2.v[69]*MainFormSLS->hh_1[137]
 + c2.v[70]*MainFormSLS->hh_1[63]
 + c2.v[71]*MainFormSLS->hh_1[149]
 + c2.v[72]*MainFormSLS->hh_1[75]
 + c2.v[73]*MainFormSLS->hh_1[1]
 + c2.v[74]*MainFormSLS->hh_1[87]
 + c2.v[75]*MainFormSLS->hh_1[13]
 + c2.v[76]*MainFormSLS->hh_1[99]
 + c2.v[77]*MainFormSLS->hh_1[25]
 + c2.v[78]*MainFormSLS->hh_1[111]
 + c2.v[79]*MainFormSLS->hh_1[37];
s/=N_2;
out.push_back(s);
//������ 124
s =c2.v[0]*MainFormSLS->hh_1[124]
 + c2.v[1]*MainFormSLS->hh_1[52]
 + c2.v[2]*MainFormSLS->hh_1[140]
 + c2.v[3]*MainFormSLS->hh_1[68]
 + c2.v[4]*MainFormSLS->hh_1[156]
 + c2.v[5]*MainFormSLS->hh_1[84]
 + c2.v[6]*MainFormSLS->hh_1[12]
 + c2.v[7]*MainFormSLS->hh_1[100]
 + c2.v[8]*MainFormSLS->hh_1[28]
 + c2.v[9]*MainFormSLS->hh_1[116]
 + c2.v[10]*MainFormSLS->hh_1[44]
 + c2.v[11]*MainFormSLS->hh_1[132]
 + c2.v[12]*MainFormSLS->hh_1[60]
 + c2.v[13]*MainFormSLS->hh_1[148]
 + c2.v[14]*MainFormSLS->hh_1[76]
 + c2.v[15]*MainFormSLS->hh_1[4]
 + c2.v[16]*MainFormSLS->hh_1[92]
 + c2.v[17]*MainFormSLS->hh_1[20]
 + c2.v[18]*MainFormSLS->hh_1[108]
 + c2.v[19]*MainFormSLS->hh_1[36]
 + c2.v[20]*MainFormSLS->hh_1[124]
 + c2.v[21]*MainFormSLS->hh_1[52]
 + c2.v[22]*MainFormSLS->hh_1[140]
 + c2.v[23]*MainFormSLS->hh_1[68]
 + c2.v[24]*MainFormSLS->hh_1[156]
 + c2.v[25]*MainFormSLS->hh_1[84]
 + c2.v[26]*MainFormSLS->hh_1[12]
 + c2.v[27]*MainFormSLS->hh_1[100]
 + c2.v[28]*MainFormSLS->hh_1[28]
 + c2.v[29]*MainFormSLS->hh_1[116]
 + c2.v[30]*MainFormSLS->hh_1[44]
 + c2.v[31]*MainFormSLS->hh_1[132]
 + c2.v[32]*MainFormSLS->hh_1[60]
 + c2.v[33]*MainFormSLS->hh_1[148]
 + c2.v[34]*MainFormSLS->hh_1[76]
 + c2.v[35]*MainFormSLS->hh_1[4]
 + c2.v[36]*MainFormSLS->hh_1[92]
 + c2.v[37]*MainFormSLS->hh_1[20]
 + c2.v[38]*MainFormSLS->hh_1[108]
 + c2.v[39]*MainFormSLS->hh_1[36]
 + c2.v[40]*MainFormSLS->hh_1[124]
 + c2.v[41]*MainFormSLS->hh_1[52]
 + c2.v[42]*MainFormSLS->hh_1[140]
 + c2.v[43]*MainFormSLS->hh_1[68]
 + c2.v[44]*MainFormSLS->hh_1[156]
 + c2.v[45]*MainFormSLS->hh_1[84]
 + c2.v[46]*MainFormSLS->hh_1[12]
 + c2.v[47]*MainFormSLS->hh_1[100]
 + c2.v[48]*MainFormSLS->hh_1[28]
 + c2.v[49]*MainFormSLS->hh_1[116]
 + c2.v[50]*MainFormSLS->hh_1[44]
 + c2.v[51]*MainFormSLS->hh_1[132]
 + c2.v[52]*MainFormSLS->hh_1[60]
 + c2.v[53]*MainFormSLS->hh_1[148]
 + c2.v[54]*MainFormSLS->hh_1[76]
 + c2.v[55]*MainFormSLS->hh_1[4]
 + c2.v[56]*MainFormSLS->hh_1[92]
 + c2.v[57]*MainFormSLS->hh_1[20]
 + c2.v[58]*MainFormSLS->hh_1[108]
 + c2.v[59]*MainFormSLS->hh_1[36]
 + c2.v[60]*MainFormSLS->hh_1[124]
 + c2.v[61]*MainFormSLS->hh_1[52]
 + c2.v[62]*MainFormSLS->hh_1[140]
 + c2.v[63]*MainFormSLS->hh_1[68]
 + c2.v[64]*MainFormSLS->hh_1[156]
 + c2.v[65]*MainFormSLS->hh_1[84]
 + c2.v[66]*MainFormSLS->hh_1[12]
 + c2.v[67]*MainFormSLS->hh_1[100]
 + c2.v[68]*MainFormSLS->hh_1[28]
 + c2.v[69]*MainFormSLS->hh_1[116]
 + c2.v[70]*MainFormSLS->hh_1[44]
 + c2.v[71]*MainFormSLS->hh_1[132]
 + c2.v[72]*MainFormSLS->hh_1[60]
 + c2.v[73]*MainFormSLS->hh_1[148]
 + c2.v[74]*MainFormSLS->hh_1[76]
 + c2.v[75]*MainFormSLS->hh_1[4]
 + c2.v[76]*MainFormSLS->hh_1[92]
 + c2.v[77]*MainFormSLS->hh_1[20]
 + c2.v[78]*MainFormSLS->hh_1[108]
 + c2.v[79]*MainFormSLS->hh_1[36];
s/=N_2;
out.push_back(s);
//������ 125
s =c2.v[0]*MainFormSLS->hh_1[125]
 + c2.v[1]*MainFormSLS->hh_1[55]
 + c2.v[2]*MainFormSLS->hh_1[145]
 + c2.v[3]*MainFormSLS->hh_1[75]
 + c2.v[4]*MainFormSLS->hh_1[5]
 + c2.v[5]*MainFormSLS->hh_1[95]
 + c2.v[6]*MainFormSLS->hh_1[25]
 + c2.v[7]*MainFormSLS->hh_1[115]
 + c2.v[8]*MainFormSLS->hh_1[45]
 + c2.v[9]*MainFormSLS->hh_1[135]
 + c2.v[10]*MainFormSLS->hh_1[65]
 + c2.v[11]*MainFormSLS->hh_1[155]
 + c2.v[12]*MainFormSLS->hh_1[85]
 + c2.v[13]*MainFormSLS->hh_1[15]
 + c2.v[14]*MainFormSLS->hh_1[105]
 + c2.v[15]*MainFormSLS->hh_1[35]
 + c2.v[16]*MainFormSLS->hh_1[125]
 + c2.v[17]*MainFormSLS->hh_1[55]
 + c2.v[18]*MainFormSLS->hh_1[145]
 + c2.v[19]*MainFormSLS->hh_1[75]
 + c2.v[20]*MainFormSLS->hh_1[5]
 + c2.v[21]*MainFormSLS->hh_1[95]
 + c2.v[22]*MainFormSLS->hh_1[25]
 + c2.v[23]*MainFormSLS->hh_1[115]
 + c2.v[24]*MainFormSLS->hh_1[45]
 + c2.v[25]*MainFormSLS->hh_1[135]
 + c2.v[26]*MainFormSLS->hh_1[65]
 + c2.v[27]*MainFormSLS->hh_1[155]
 + c2.v[28]*MainFormSLS->hh_1[85]
 + c2.v[29]*MainFormSLS->hh_1[15]
 + c2.v[30]*MainFormSLS->hh_1[105]
 + c2.v[31]*MainFormSLS->hh_1[35]
 + c2.v[32]*MainFormSLS->hh_1[125]
 + c2.v[33]*MainFormSLS->hh_1[55]
 + c2.v[34]*MainFormSLS->hh_1[145]
 + c2.v[35]*MainFormSLS->hh_1[75]
 + c2.v[36]*MainFormSLS->hh_1[5]
 + c2.v[37]*MainFormSLS->hh_1[95]
 + c2.v[38]*MainFormSLS->hh_1[25]
 + c2.v[39]*MainFormSLS->hh_1[115]
 + c2.v[40]*MainFormSLS->hh_1[45]
 + c2.v[41]*MainFormSLS->hh_1[135]
 + c2.v[42]*MainFormSLS->hh_1[65]
 + c2.v[43]*MainFormSLS->hh_1[155]
 + c2.v[44]*MainFormSLS->hh_1[85]
 + c2.v[45]*MainFormSLS->hh_1[15]
 + c2.v[46]*MainFormSLS->hh_1[105]
 + c2.v[47]*MainFormSLS->hh_1[35]
 + c2.v[48]*MainFormSLS->hh_1[125]
 + c2.v[49]*MainFormSLS->hh_1[55]
 + c2.v[50]*MainFormSLS->hh_1[145]
 + c2.v[51]*MainFormSLS->hh_1[75]
 + c2.v[52]*MainFormSLS->hh_1[5]
 + c2.v[53]*MainFormSLS->hh_1[95]
 + c2.v[54]*MainFormSLS->hh_1[25]
 + c2.v[55]*MainFormSLS->hh_1[115]
 + c2.v[56]*MainFormSLS->hh_1[45]
 + c2.v[57]*MainFormSLS->hh_1[135]
 + c2.v[58]*MainFormSLS->hh_1[65]
 + c2.v[59]*MainFormSLS->hh_1[155]
 + c2.v[60]*MainFormSLS->hh_1[85]
 + c2.v[61]*MainFormSLS->hh_1[15]
 + c2.v[62]*MainFormSLS->hh_1[105]
 + c2.v[63]*MainFormSLS->hh_1[35]
 + c2.v[64]*MainFormSLS->hh_1[125]
 + c2.v[65]*MainFormSLS->hh_1[55]
 + c2.v[66]*MainFormSLS->hh_1[145]
 + c2.v[67]*MainFormSLS->hh_1[75]
 + c2.v[68]*MainFormSLS->hh_1[5]
 + c2.v[69]*MainFormSLS->hh_1[95]
 + c2.v[70]*MainFormSLS->hh_1[25]
 + c2.v[71]*MainFormSLS->hh_1[115]
 + c2.v[72]*MainFormSLS->hh_1[45]
 + c2.v[73]*MainFormSLS->hh_1[135]
 + c2.v[74]*MainFormSLS->hh_1[65]
 + c2.v[75]*MainFormSLS->hh_1[155]
 + c2.v[76]*MainFormSLS->hh_1[85]
 + c2.v[77]*MainFormSLS->hh_1[15]
 + c2.v[78]*MainFormSLS->hh_1[105]
 + c2.v[79]*MainFormSLS->hh_1[35];
s/=N_2;
out.push_back(s);
//������ 126
s =c2.v[0]*MainFormSLS->hh_1[126]
 + c2.v[1]*MainFormSLS->hh_1[58]
 + c2.v[2]*MainFormSLS->hh_1[150]
 + c2.v[3]*MainFormSLS->hh_1[82]
 + c2.v[4]*MainFormSLS->hh_1[14]
 + c2.v[5]*MainFormSLS->hh_1[106]
 + c2.v[6]*MainFormSLS->hh_1[38]
 + c2.v[7]*MainFormSLS->hh_1[130]
 + c2.v[8]*MainFormSLS->hh_1[62]
 + c2.v[9]*MainFormSLS->hh_1[154]
 + c2.v[10]*MainFormSLS->hh_1[86]
 + c2.v[11]*MainFormSLS->hh_1[18]
 + c2.v[12]*MainFormSLS->hh_1[110]
 + c2.v[13]*MainFormSLS->hh_1[42]
 + c2.v[14]*MainFormSLS->hh_1[134]
 + c2.v[15]*MainFormSLS->hh_1[66]
 + c2.v[16]*MainFormSLS->hh_1[158]
 + c2.v[17]*MainFormSLS->hh_1[90]
 + c2.v[18]*MainFormSLS->hh_1[22]
 + c2.v[19]*MainFormSLS->hh_1[114]
 + c2.v[20]*MainFormSLS->hh_1[46]
 + c2.v[21]*MainFormSLS->hh_1[138]
 + c2.v[22]*MainFormSLS->hh_1[70]
 + c2.v[23]*MainFormSLS->hh_1[2]
 + c2.v[24]*MainFormSLS->hh_1[94]
 + c2.v[25]*MainFormSLS->hh_1[26]
 + c2.v[26]*MainFormSLS->hh_1[118]
 + c2.v[27]*MainFormSLS->hh_1[50]
 + c2.v[28]*MainFormSLS->hh_1[142]
 + c2.v[29]*MainFormSLS->hh_1[74]
 + c2.v[30]*MainFormSLS->hh_1[6]
 + c2.v[31]*MainFormSLS->hh_1[98]
 + c2.v[32]*MainFormSLS->hh_1[30]
 + c2.v[33]*MainFormSLS->hh_1[122]
 + c2.v[34]*MainFormSLS->hh_1[54]
 + c2.v[35]*MainFormSLS->hh_1[146]
 + c2.v[36]*MainFormSLS->hh_1[78]
 + c2.v[37]*MainFormSLS->hh_1[10]
 + c2.v[38]*MainFormSLS->hh_1[102]
 + c2.v[39]*MainFormSLS->hh_1[34]
 + c2.v[40]*MainFormSLS->hh_1[126]
 + c2.v[41]*MainFormSLS->hh_1[58]
 + c2.v[42]*MainFormSLS->hh_1[150]
 + c2.v[43]*MainFormSLS->hh_1[82]
 + c2.v[44]*MainFormSLS->hh_1[14]
 + c2.v[45]*MainFormSLS->hh_1[106]
 + c2.v[46]*MainFormSLS->hh_1[38]
 + c2.v[47]*MainFormSLS->hh_1[130]
 + c2.v[48]*MainFormSLS->hh_1[62]
 + c2.v[49]*MainFormSLS->hh_1[154]
 + c2.v[50]*MainFormSLS->hh_1[86]
 + c2.v[51]*MainFormSLS->hh_1[18]
 + c2.v[52]*MainFormSLS->hh_1[110]
 + c2.v[53]*MainFormSLS->hh_1[42]
 + c2.v[54]*MainFormSLS->hh_1[134]
 + c2.v[55]*MainFormSLS->hh_1[66]
 + c2.v[56]*MainFormSLS->hh_1[158]
 + c2.v[57]*MainFormSLS->hh_1[90]
 + c2.v[58]*MainFormSLS->hh_1[22]
 + c2.v[59]*MainFormSLS->hh_1[114]
 + c2.v[60]*MainFormSLS->hh_1[46]
 + c2.v[61]*MainFormSLS->hh_1[138]
 + c2.v[62]*MainFormSLS->hh_1[70]
 + c2.v[63]*MainFormSLS->hh_1[2]
 + c2.v[64]*MainFormSLS->hh_1[94]
 + c2.v[65]*MainFormSLS->hh_1[26]
 + c2.v[66]*MainFormSLS->hh_1[118]
 + c2.v[67]*MainFormSLS->hh_1[50]
 + c2.v[68]*MainFormSLS->hh_1[142]
 + c2.v[69]*MainFormSLS->hh_1[74]
 + c2.v[70]*MainFormSLS->hh_1[6]
 + c2.v[71]*MainFormSLS->hh_1[98]
 + c2.v[72]*MainFormSLS->hh_1[30]
 + c2.v[73]*MainFormSLS->hh_1[122]
 + c2.v[74]*MainFormSLS->hh_1[54]
 + c2.v[75]*MainFormSLS->hh_1[146]
 + c2.v[76]*MainFormSLS->hh_1[78]
 + c2.v[77]*MainFormSLS->hh_1[10]
 + c2.v[78]*MainFormSLS->hh_1[102]
 + c2.v[79]*MainFormSLS->hh_1[34];
s/=N_2;
out.push_back(s);
//������ 127
s =c2.v[0]*MainFormSLS->hh_1[127]
 + c2.v[1]*MainFormSLS->hh_1[61]
 + c2.v[2]*MainFormSLS->hh_1[155]
 + c2.v[3]*MainFormSLS->hh_1[89]
 + c2.v[4]*MainFormSLS->hh_1[23]
 + c2.v[5]*MainFormSLS->hh_1[117]
 + c2.v[6]*MainFormSLS->hh_1[51]
 + c2.v[7]*MainFormSLS->hh_1[145]
 + c2.v[8]*MainFormSLS->hh_1[79]
 + c2.v[9]*MainFormSLS->hh_1[13]
 + c2.v[10]*MainFormSLS->hh_1[107]
 + c2.v[11]*MainFormSLS->hh_1[41]
 + c2.v[12]*MainFormSLS->hh_1[135]
 + c2.v[13]*MainFormSLS->hh_1[69]
 + c2.v[14]*MainFormSLS->hh_1[3]
 + c2.v[15]*MainFormSLS->hh_1[97]
 + c2.v[16]*MainFormSLS->hh_1[31]
 + c2.v[17]*MainFormSLS->hh_1[125]
 + c2.v[18]*MainFormSLS->hh_1[59]
 + c2.v[19]*MainFormSLS->hh_1[153]
 + c2.v[20]*MainFormSLS->hh_1[87]
 + c2.v[21]*MainFormSLS->hh_1[21]
 + c2.v[22]*MainFormSLS->hh_1[115]
 + c2.v[23]*MainFormSLS->hh_1[49]
 + c2.v[24]*MainFormSLS->hh_1[143]
 + c2.v[25]*MainFormSLS->hh_1[77]
 + c2.v[26]*MainFormSLS->hh_1[11]
 + c2.v[27]*MainFormSLS->hh_1[105]
 + c2.v[28]*MainFormSLS->hh_1[39]
 + c2.v[29]*MainFormSLS->hh_1[133]
 + c2.v[30]*MainFormSLS->hh_1[67]
 + c2.v[31]*MainFormSLS->hh_1[1]
 + c2.v[32]*MainFormSLS->hh_1[95]
 + c2.v[33]*MainFormSLS->hh_1[29]
 + c2.v[34]*MainFormSLS->hh_1[123]
 + c2.v[35]*MainFormSLS->hh_1[57]
 + c2.v[36]*MainFormSLS->hh_1[151]
 + c2.v[37]*MainFormSLS->hh_1[85]
 + c2.v[38]*MainFormSLS->hh_1[19]
 + c2.v[39]*MainFormSLS->hh_1[113]
 + c2.v[40]*MainFormSLS->hh_1[47]
 + c2.v[41]*MainFormSLS->hh_1[141]
 + c2.v[42]*MainFormSLS->hh_1[75]
 + c2.v[43]*MainFormSLS->hh_1[9]
 + c2.v[44]*MainFormSLS->hh_1[103]
 + c2.v[45]*MainFormSLS->hh_1[37]
 + c2.v[46]*MainFormSLS->hh_1[131]
 + c2.v[47]*MainFormSLS->hh_1[65]
 + c2.v[48]*MainFormSLS->hh_1[159]
 + c2.v[49]*MainFormSLS->hh_1[93]
 + c2.v[50]*MainFormSLS->hh_1[27]
 + c2.v[51]*MainFormSLS->hh_1[121]
 + c2.v[52]*MainFormSLS->hh_1[55]
 + c2.v[53]*MainFormSLS->hh_1[149]
 + c2.v[54]*MainFormSLS->hh_1[83]
 + c2.v[55]*MainFormSLS->hh_1[17]
 + c2.v[56]*MainFormSLS->hh_1[111]
 + c2.v[57]*MainFormSLS->hh_1[45]
 + c2.v[58]*MainFormSLS->hh_1[139]
 + c2.v[59]*MainFormSLS->hh_1[73]
 + c2.v[60]*MainFormSLS->hh_1[7]
 + c2.v[61]*MainFormSLS->hh_1[101]
 + c2.v[62]*MainFormSLS->hh_1[35]
 + c2.v[63]*MainFormSLS->hh_1[129]
 + c2.v[64]*MainFormSLS->hh_1[63]
 + c2.v[65]*MainFormSLS->hh_1[157]
 + c2.v[66]*MainFormSLS->hh_1[91]
 + c2.v[67]*MainFormSLS->hh_1[25]
 + c2.v[68]*MainFormSLS->hh_1[119]
 + c2.v[69]*MainFormSLS->hh_1[53]
 + c2.v[70]*MainFormSLS->hh_1[147]
 + c2.v[71]*MainFormSLS->hh_1[81]
 + c2.v[72]*MainFormSLS->hh_1[15]
 + c2.v[73]*MainFormSLS->hh_1[109]
 + c2.v[74]*MainFormSLS->hh_1[43]
 + c2.v[75]*MainFormSLS->hh_1[137]
 + c2.v[76]*MainFormSLS->hh_1[71]
 + c2.v[77]*MainFormSLS->hh_1[5]
 + c2.v[78]*MainFormSLS->hh_1[99]
 + c2.v[79]*MainFormSLS->hh_1[33];
s/=N_2;
out.push_back(s);
//������ 128
s =c2.v[0]*MainFormSLS->hh_1[128]
 + c2.v[1]*MainFormSLS->hh_1[64]
 + c2.v[2]*MainFormSLS->hh_1[0]
 + c2.v[3]*MainFormSLS->hh_1[96]
 + c2.v[4]*MainFormSLS->hh_1[32]
 + c2.v[5]*MainFormSLS->hh_1[128]
 + c2.v[6]*MainFormSLS->hh_1[64]
 + c2.v[7]*MainFormSLS->hh_1[0]
 + c2.v[8]*MainFormSLS->hh_1[96]
 + c2.v[9]*MainFormSLS->hh_1[32]
 + c2.v[10]*MainFormSLS->hh_1[128]
 + c2.v[11]*MainFormSLS->hh_1[64]
 + c2.v[12]*MainFormSLS->hh_1[0]
 + c2.v[13]*MainFormSLS->hh_1[96]
 + c2.v[14]*MainFormSLS->hh_1[32]
 + c2.v[15]*MainFormSLS->hh_1[128]
 + c2.v[16]*MainFormSLS->hh_1[64]
 + c2.v[17]*MainFormSLS->hh_1[0]
 + c2.v[18]*MainFormSLS->hh_1[96]
 + c2.v[19]*MainFormSLS->hh_1[32]
 + c2.v[20]*MainFormSLS->hh_1[128]
 + c2.v[21]*MainFormSLS->hh_1[64]
 + c2.v[22]*MainFormSLS->hh_1[0]
 + c2.v[23]*MainFormSLS->hh_1[96]
 + c2.v[24]*MainFormSLS->hh_1[32]
 + c2.v[25]*MainFormSLS->hh_1[128]
 + c2.v[26]*MainFormSLS->hh_1[64]
 + c2.v[27]*MainFormSLS->hh_1[0]
 + c2.v[28]*MainFormSLS->hh_1[96]
 + c2.v[29]*MainFormSLS->hh_1[32]
 + c2.v[30]*MainFormSLS->hh_1[128]
 + c2.v[31]*MainFormSLS->hh_1[64]
 + c2.v[32]*MainFormSLS->hh_1[0]
 + c2.v[33]*MainFormSLS->hh_1[96]
 + c2.v[34]*MainFormSLS->hh_1[32]
 + c2.v[35]*MainFormSLS->hh_1[128]
 + c2.v[36]*MainFormSLS->hh_1[64]
 + c2.v[37]*MainFormSLS->hh_1[0]
 + c2.v[38]*MainFormSLS->hh_1[96]
 + c2.v[39]*MainFormSLS->hh_1[32]
 + c2.v[40]*MainFormSLS->hh_1[128]
 + c2.v[41]*MainFormSLS->hh_1[64]
 + c2.v[42]*MainFormSLS->hh_1[0]
 + c2.v[43]*MainFormSLS->hh_1[96]
 + c2.v[44]*MainFormSLS->hh_1[32]
 + c2.v[45]*MainFormSLS->hh_1[128]
 + c2.v[46]*MainFormSLS->hh_1[64]
 + c2.v[47]*MainFormSLS->hh_1[0]
 + c2.v[48]*MainFormSLS->hh_1[96]
 + c2.v[49]*MainFormSLS->hh_1[32]
 + c2.v[50]*MainFormSLS->hh_1[128]
 + c2.v[51]*MainFormSLS->hh_1[64]
 + c2.v[52]*MainFormSLS->hh_1[0]
 + c2.v[53]*MainFormSLS->hh_1[96]
 + c2.v[54]*MainFormSLS->hh_1[32]
 + c2.v[55]*MainFormSLS->hh_1[128]
 + c2.v[56]*MainFormSLS->hh_1[64]
 + c2.v[57]*MainFormSLS->hh_1[0]
 + c2.v[58]*MainFormSLS->hh_1[96]
 + c2.v[59]*MainFormSLS->hh_1[32]
 + c2.v[60]*MainFormSLS->hh_1[128]
 + c2.v[61]*MainFormSLS->hh_1[64]
 + c2.v[62]*MainFormSLS->hh_1[0]
 + c2.v[63]*MainFormSLS->hh_1[96]
 + c2.v[64]*MainFormSLS->hh_1[32]
 + c2.v[65]*MainFormSLS->hh_1[128]
 + c2.v[66]*MainFormSLS->hh_1[64]
 + c2.v[67]*MainFormSLS->hh_1[0]
 + c2.v[68]*MainFormSLS->hh_1[96]
 + c2.v[69]*MainFormSLS->hh_1[32]
 + c2.v[70]*MainFormSLS->hh_1[128]
 + c2.v[71]*MainFormSLS->hh_1[64]
 + c2.v[72]*MainFormSLS->hh_1[0]
 + c2.v[73]*MainFormSLS->hh_1[96]
 + c2.v[74]*MainFormSLS->hh_1[32]
 + c2.v[75]*MainFormSLS->hh_1[128]
 + c2.v[76]*MainFormSLS->hh_1[64]
 + c2.v[77]*MainFormSLS->hh_1[0]
 + c2.v[78]*MainFormSLS->hh_1[96]
 + c2.v[79]*MainFormSLS->hh_1[32];
s/=N_2;
out.push_back(s);
//������ 129
s =c2.v[0]*MainFormSLS->hh_1[129]
 + c2.v[1]*MainFormSLS->hh_1[67]
 + c2.v[2]*MainFormSLS->hh_1[5]
 + c2.v[3]*MainFormSLS->hh_1[103]
 + c2.v[4]*MainFormSLS->hh_1[41]
 + c2.v[5]*MainFormSLS->hh_1[139]
 + c2.v[6]*MainFormSLS->hh_1[77]
 + c2.v[7]*MainFormSLS->hh_1[15]
 + c2.v[8]*MainFormSLS->hh_1[113]
 + c2.v[9]*MainFormSLS->hh_1[51]
 + c2.v[10]*MainFormSLS->hh_1[149]
 + c2.v[11]*MainFormSLS->hh_1[87]
 + c2.v[12]*MainFormSLS->hh_1[25]
 + c2.v[13]*MainFormSLS->hh_1[123]
 + c2.v[14]*MainFormSLS->hh_1[61]
 + c2.v[15]*MainFormSLS->hh_1[159]
 + c2.v[16]*MainFormSLS->hh_1[97]
 + c2.v[17]*MainFormSLS->hh_1[35]
 + c2.v[18]*MainFormSLS->hh_1[133]
 + c2.v[19]*MainFormSLS->hh_1[71]
 + c2.v[20]*MainFormSLS->hh_1[9]
 + c2.v[21]*MainFormSLS->hh_1[107]
 + c2.v[22]*MainFormSLS->hh_1[45]
 + c2.v[23]*MainFormSLS->hh_1[143]
 + c2.v[24]*MainFormSLS->hh_1[81]
 + c2.v[25]*MainFormSLS->hh_1[19]
 + c2.v[26]*MainFormSLS->hh_1[117]
 + c2.v[27]*MainFormSLS->hh_1[55]
 + c2.v[28]*MainFormSLS->hh_1[153]
 + c2.v[29]*MainFormSLS->hh_1[91]
 + c2.v[30]*MainFormSLS->hh_1[29]
 + c2.v[31]*MainFormSLS->hh_1[127]
 + c2.v[32]*MainFormSLS->hh_1[65]
 + c2.v[33]*MainFormSLS->hh_1[3]
 + c2.v[34]*MainFormSLS->hh_1[101]
 + c2.v[35]*MainFormSLS->hh_1[39]
 + c2.v[36]*MainFormSLS->hh_1[137]
 + c2.v[37]*MainFormSLS->hh_1[75]
 + c2.v[38]*MainFormSLS->hh_1[13]
 + c2.v[39]*MainFormSLS->hh_1[111]
 + c2.v[40]*MainFormSLS->hh_1[49]
 + c2.v[41]*MainFormSLS->hh_1[147]
 + c2.v[42]*MainFormSLS->hh_1[85]
 + c2.v[43]*MainFormSLS->hh_1[23]
 + c2.v[44]*MainFormSLS->hh_1[121]
 + c2.v[45]*MainFormSLS->hh_1[59]
 + c2.v[46]*MainFormSLS->hh_1[157]
 + c2.v[47]*MainFormSLS->hh_1[95]
 + c2.v[48]*MainFormSLS->hh_1[33]
 + c2.v[49]*MainFormSLS->hh_1[131]
 + c2.v[50]*MainFormSLS->hh_1[69]
 + c2.v[51]*MainFormSLS->hh_1[7]
 + c2.v[52]*MainFormSLS->hh_1[105]
 + c2.v[53]*MainFormSLS->hh_1[43]
 + c2.v[54]*MainFormSLS->hh_1[141]
 + c2.v[55]*MainFormSLS->hh_1[79]
 + c2.v[56]*MainFormSLS->hh_1[17]
 + c2.v[57]*MainFormSLS->hh_1[115]
 + c2.v[58]*MainFormSLS->hh_1[53]
 + c2.v[59]*MainFormSLS->hh_1[151]
 + c2.v[60]*MainFormSLS->hh_1[89]
 + c2.v[61]*MainFormSLS->hh_1[27]
 + c2.v[62]*MainFormSLS->hh_1[125]
 + c2.v[63]*MainFormSLS->hh_1[63]
 + c2.v[64]*MainFormSLS->hh_1[1]
 + c2.v[65]*MainFormSLS->hh_1[99]
 + c2.v[66]*MainFormSLS->hh_1[37]
 + c2.v[67]*MainFormSLS->hh_1[135]
 + c2.v[68]*MainFormSLS->hh_1[73]
 + c2.v[69]*MainFormSLS->hh_1[11]
 + c2.v[70]*MainFormSLS->hh_1[109]
 + c2.v[71]*MainFormSLS->hh_1[47]
 + c2.v[72]*MainFormSLS->hh_1[145]
 + c2.v[73]*MainFormSLS->hh_1[83]
 + c2.v[74]*MainFormSLS->hh_1[21]
 + c2.v[75]*MainFormSLS->hh_1[119]
 + c2.v[76]*MainFormSLS->hh_1[57]
 + c2.v[77]*MainFormSLS->hh_1[155]
 + c2.v[78]*MainFormSLS->hh_1[93]
 + c2.v[79]*MainFormSLS->hh_1[31];
s/=N_2;
out.push_back(s);
//������ 130
s =c2.v[0]*MainFormSLS->hh_1[130]
 + c2.v[1]*MainFormSLS->hh_1[70]
 + c2.v[2]*MainFormSLS->hh_1[10]
 + c2.v[3]*MainFormSLS->hh_1[110]
 + c2.v[4]*MainFormSLS->hh_1[50]
 + c2.v[5]*MainFormSLS->hh_1[150]
 + c2.v[6]*MainFormSLS->hh_1[90]
 + c2.v[7]*MainFormSLS->hh_1[30]
 + c2.v[8]*MainFormSLS->hh_1[130]
 + c2.v[9]*MainFormSLS->hh_1[70]
 + c2.v[10]*MainFormSLS->hh_1[10]
 + c2.v[11]*MainFormSLS->hh_1[110]
 + c2.v[12]*MainFormSLS->hh_1[50]
 + c2.v[13]*MainFormSLS->hh_1[150]
 + c2.v[14]*MainFormSLS->hh_1[90]
 + c2.v[15]*MainFormSLS->hh_1[30]
 + c2.v[16]*MainFormSLS->hh_1[130]
 + c2.v[17]*MainFormSLS->hh_1[70]
 + c2.v[18]*MainFormSLS->hh_1[10]
 + c2.v[19]*MainFormSLS->hh_1[110]
 + c2.v[20]*MainFormSLS->hh_1[50]
 + c2.v[21]*MainFormSLS->hh_1[150]
 + c2.v[22]*MainFormSLS->hh_1[90]
 + c2.v[23]*MainFormSLS->hh_1[30]
 + c2.v[24]*MainFormSLS->hh_1[130]
 + c2.v[25]*MainFormSLS->hh_1[70]
 + c2.v[26]*MainFormSLS->hh_1[10]
 + c2.v[27]*MainFormSLS->hh_1[110]
 + c2.v[28]*MainFormSLS->hh_1[50]
 + c2.v[29]*MainFormSLS->hh_1[150]
 + c2.v[30]*MainFormSLS->hh_1[90]
 + c2.v[31]*MainFormSLS->hh_1[30]
 + c2.v[32]*MainFormSLS->hh_1[130]
 + c2.v[33]*MainFormSLS->hh_1[70]
 + c2.v[34]*MainFormSLS->hh_1[10]
 + c2.v[35]*MainFormSLS->hh_1[110]
 + c2.v[36]*MainFormSLS->hh_1[50]
 + c2.v[37]*MainFormSLS->hh_1[150]
 + c2.v[38]*MainFormSLS->hh_1[90]
 + c2.v[39]*MainFormSLS->hh_1[30]
 + c2.v[40]*MainFormSLS->hh_1[130]
 + c2.v[41]*MainFormSLS->hh_1[70]
 + c2.v[42]*MainFormSLS->hh_1[10]
 + c2.v[43]*MainFormSLS->hh_1[110]
 + c2.v[44]*MainFormSLS->hh_1[50]
 + c2.v[45]*MainFormSLS->hh_1[150]
 + c2.v[46]*MainFormSLS->hh_1[90]
 + c2.v[47]*MainFormSLS->hh_1[30]
 + c2.v[48]*MainFormSLS->hh_1[130]
 + c2.v[49]*MainFormSLS->hh_1[70]
 + c2.v[50]*MainFormSLS->hh_1[10]
 + c2.v[51]*MainFormSLS->hh_1[110]
 + c2.v[52]*MainFormSLS->hh_1[50]
 + c2.v[53]*MainFormSLS->hh_1[150]
 + c2.v[54]*MainFormSLS->hh_1[90]
 + c2.v[55]*MainFormSLS->hh_1[30]
 + c2.v[56]*MainFormSLS->hh_1[130]
 + c2.v[57]*MainFormSLS->hh_1[70]
 + c2.v[58]*MainFormSLS->hh_1[10]
 + c2.v[59]*MainFormSLS->hh_1[110]
 + c2.v[60]*MainFormSLS->hh_1[50]
 + c2.v[61]*MainFormSLS->hh_1[150]
 + c2.v[62]*MainFormSLS->hh_1[90]
 + c2.v[63]*MainFormSLS->hh_1[30]
 + c2.v[64]*MainFormSLS->hh_1[130]
 + c2.v[65]*MainFormSLS->hh_1[70]
 + c2.v[66]*MainFormSLS->hh_1[10]
 + c2.v[67]*MainFormSLS->hh_1[110]
 + c2.v[68]*MainFormSLS->hh_1[50]
 + c2.v[69]*MainFormSLS->hh_1[150]
 + c2.v[70]*MainFormSLS->hh_1[90]
 + c2.v[71]*MainFormSLS->hh_1[30]
 + c2.v[72]*MainFormSLS->hh_1[130]
 + c2.v[73]*MainFormSLS->hh_1[70]
 + c2.v[74]*MainFormSLS->hh_1[10]
 + c2.v[75]*MainFormSLS->hh_1[110]
 + c2.v[76]*MainFormSLS->hh_1[50]
 + c2.v[77]*MainFormSLS->hh_1[150]
 + c2.v[78]*MainFormSLS->hh_1[90]
 + c2.v[79]*MainFormSLS->hh_1[30];
s/=N_2;
out.push_back(s);
//������ 131
s =c2.v[0]*MainFormSLS->hh_1[131]
 + c2.v[1]*MainFormSLS->hh_1[73]
 + c2.v[2]*MainFormSLS->hh_1[15]
 + c2.v[3]*MainFormSLS->hh_1[117]
 + c2.v[4]*MainFormSLS->hh_1[59]
 + c2.v[5]*MainFormSLS->hh_1[1]
 + c2.v[6]*MainFormSLS->hh_1[103]
 + c2.v[7]*MainFormSLS->hh_1[45]
 + c2.v[8]*MainFormSLS->hh_1[147]
 + c2.v[9]*MainFormSLS->hh_1[89]
 + c2.v[10]*MainFormSLS->hh_1[31]
 + c2.v[11]*MainFormSLS->hh_1[133]
 + c2.v[12]*MainFormSLS->hh_1[75]
 + c2.v[13]*MainFormSLS->hh_1[17]
 + c2.v[14]*MainFormSLS->hh_1[119]
 + c2.v[15]*MainFormSLS->hh_1[61]
 + c2.v[16]*MainFormSLS->hh_1[3]
 + c2.v[17]*MainFormSLS->hh_1[105]
 + c2.v[18]*MainFormSLS->hh_1[47]
 + c2.v[19]*MainFormSLS->hh_1[149]
 + c2.v[20]*MainFormSLS->hh_1[91]
 + c2.v[21]*MainFormSLS->hh_1[33]
 + c2.v[22]*MainFormSLS->hh_1[135]
 + c2.v[23]*MainFormSLS->hh_1[77]
 + c2.v[24]*MainFormSLS->hh_1[19]
 + c2.v[25]*MainFormSLS->hh_1[121]
 + c2.v[26]*MainFormSLS->hh_1[63]
 + c2.v[27]*MainFormSLS->hh_1[5]
 + c2.v[28]*MainFormSLS->hh_1[107]
 + c2.v[29]*MainFormSLS->hh_1[49]
 + c2.v[30]*MainFormSLS->hh_1[151]
 + c2.v[31]*MainFormSLS->hh_1[93]
 + c2.v[32]*MainFormSLS->hh_1[35]
 + c2.v[33]*MainFormSLS->hh_1[137]
 + c2.v[34]*MainFormSLS->hh_1[79]
 + c2.v[35]*MainFormSLS->hh_1[21]
 + c2.v[36]*MainFormSLS->hh_1[123]
 + c2.v[37]*MainFormSLS->hh_1[65]
 + c2.v[38]*MainFormSLS->hh_1[7]
 + c2.v[39]*MainFormSLS->hh_1[109]
 + c2.v[40]*MainFormSLS->hh_1[51]
 + c2.v[41]*MainFormSLS->hh_1[153]
 + c2.v[42]*MainFormSLS->hh_1[95]
 + c2.v[43]*MainFormSLS->hh_1[37]
 + c2.v[44]*MainFormSLS->hh_1[139]
 + c2.v[45]*MainFormSLS->hh_1[81]
 + c2.v[46]*MainFormSLS->hh_1[23]
 + c2.v[47]*MainFormSLS->hh_1[125]
 + c2.v[48]*MainFormSLS->hh_1[67]
 + c2.v[49]*MainFormSLS->hh_1[9]
 + c2.v[50]*MainFormSLS->hh_1[111]
 + c2.v[51]*MainFormSLS->hh_1[53]
 + c2.v[52]*MainFormSLS->hh_1[155]
 + c2.v[53]*MainFormSLS->hh_1[97]
 + c2.v[54]*MainFormSLS->hh_1[39]
 + c2.v[55]*MainFormSLS->hh_1[141]
 + c2.v[56]*MainFormSLS->hh_1[83]
 + c2.v[57]*MainFormSLS->hh_1[25]
 + c2.v[58]*MainFormSLS->hh_1[127]
 + c2.v[59]*MainFormSLS->hh_1[69]
 + c2.v[60]*MainFormSLS->hh_1[11]
 + c2.v[61]*MainFormSLS->hh_1[113]
 + c2.v[62]*MainFormSLS->hh_1[55]
 + c2.v[63]*MainFormSLS->hh_1[157]
 + c2.v[64]*MainFormSLS->hh_1[99]
 + c2.v[65]*MainFormSLS->hh_1[41]
 + c2.v[66]*MainFormSLS->hh_1[143]
 + c2.v[67]*MainFormSLS->hh_1[85]
 + c2.v[68]*MainFormSLS->hh_1[27]
 + c2.v[69]*MainFormSLS->hh_1[129]
 + c2.v[70]*MainFormSLS->hh_1[71]
 + c2.v[71]*MainFormSLS->hh_1[13]
 + c2.v[72]*MainFormSLS->hh_1[115]
 + c2.v[73]*MainFormSLS->hh_1[57]
 + c2.v[74]*MainFormSLS->hh_1[159]
 + c2.v[75]*MainFormSLS->hh_1[101]
 + c2.v[76]*MainFormSLS->hh_1[43]
 + c2.v[77]*MainFormSLS->hh_1[145]
 + c2.v[78]*MainFormSLS->hh_1[87]
 + c2.v[79]*MainFormSLS->hh_1[29];
s/=N_2;
out.push_back(s);
//������ 132
s =c2.v[0]*MainFormSLS->hh_1[132]
 + c2.v[1]*MainFormSLS->hh_1[76]
 + c2.v[2]*MainFormSLS->hh_1[20]
 + c2.v[3]*MainFormSLS->hh_1[124]
 + c2.v[4]*MainFormSLS->hh_1[68]
 + c2.v[5]*MainFormSLS->hh_1[12]
 + c2.v[6]*MainFormSLS->hh_1[116]
 + c2.v[7]*MainFormSLS->hh_1[60]
 + c2.v[8]*MainFormSLS->hh_1[4]
 + c2.v[9]*MainFormSLS->hh_1[108]
 + c2.v[10]*MainFormSLS->hh_1[52]
 + c2.v[11]*MainFormSLS->hh_1[156]
 + c2.v[12]*MainFormSLS->hh_1[100]
 + c2.v[13]*MainFormSLS->hh_1[44]
 + c2.v[14]*MainFormSLS->hh_1[148]
 + c2.v[15]*MainFormSLS->hh_1[92]
 + c2.v[16]*MainFormSLS->hh_1[36]
 + c2.v[17]*MainFormSLS->hh_1[140]
 + c2.v[18]*MainFormSLS->hh_1[84]
 + c2.v[19]*MainFormSLS->hh_1[28]
 + c2.v[20]*MainFormSLS->hh_1[132]
 + c2.v[21]*MainFormSLS->hh_1[76]
 + c2.v[22]*MainFormSLS->hh_1[20]
 + c2.v[23]*MainFormSLS->hh_1[124]
 + c2.v[24]*MainFormSLS->hh_1[68]
 + c2.v[25]*MainFormSLS->hh_1[12]
 + c2.v[26]*MainFormSLS->hh_1[116]
 + c2.v[27]*MainFormSLS->hh_1[60]
 + c2.v[28]*MainFormSLS->hh_1[4]
 + c2.v[29]*MainFormSLS->hh_1[108]
 + c2.v[30]*MainFormSLS->hh_1[52]
 + c2.v[31]*MainFormSLS->hh_1[156]
 + c2.v[32]*MainFormSLS->hh_1[100]
 + c2.v[33]*MainFormSLS->hh_1[44]
 + c2.v[34]*MainFormSLS->hh_1[148]
 + c2.v[35]*MainFormSLS->hh_1[92]
 + c2.v[36]*MainFormSLS->hh_1[36]
 + c2.v[37]*MainFormSLS->hh_1[140]
 + c2.v[38]*MainFormSLS->hh_1[84]
 + c2.v[39]*MainFormSLS->hh_1[28]
 + c2.v[40]*MainFormSLS->hh_1[132]
 + c2.v[41]*MainFormSLS->hh_1[76]
 + c2.v[42]*MainFormSLS->hh_1[20]
 + c2.v[43]*MainFormSLS->hh_1[124]
 + c2.v[44]*MainFormSLS->hh_1[68]
 + c2.v[45]*MainFormSLS->hh_1[12]
 + c2.v[46]*MainFormSLS->hh_1[116]
 + c2.v[47]*MainFormSLS->hh_1[60]
 + c2.v[48]*MainFormSLS->hh_1[4]
 + c2.v[49]*MainFormSLS->hh_1[108]
 + c2.v[50]*MainFormSLS->hh_1[52]
 + c2.v[51]*MainFormSLS->hh_1[156]
 + c2.v[52]*MainFormSLS->hh_1[100]
 + c2.v[53]*MainFormSLS->hh_1[44]
 + c2.v[54]*MainFormSLS->hh_1[148]
 + c2.v[55]*MainFormSLS->hh_1[92]
 + c2.v[56]*MainFormSLS->hh_1[36]
 + c2.v[57]*MainFormSLS->hh_1[140]
 + c2.v[58]*MainFormSLS->hh_1[84]
 + c2.v[59]*MainFormSLS->hh_1[28]
 + c2.v[60]*MainFormSLS->hh_1[132]
 + c2.v[61]*MainFormSLS->hh_1[76]
 + c2.v[62]*MainFormSLS->hh_1[20]
 + c2.v[63]*MainFormSLS->hh_1[124]
 + c2.v[64]*MainFormSLS->hh_1[68]
 + c2.v[65]*MainFormSLS->hh_1[12]
 + c2.v[66]*MainFormSLS->hh_1[116]
 + c2.v[67]*MainFormSLS->hh_1[60]
 + c2.v[68]*MainFormSLS->hh_1[4]
 + c2.v[69]*MainFormSLS->hh_1[108]
 + c2.v[70]*MainFormSLS->hh_1[52]
 + c2.v[71]*MainFormSLS->hh_1[156]
 + c2.v[72]*MainFormSLS->hh_1[100]
 + c2.v[73]*MainFormSLS->hh_1[44]
 + c2.v[74]*MainFormSLS->hh_1[148]
 + c2.v[75]*MainFormSLS->hh_1[92]
 + c2.v[76]*MainFormSLS->hh_1[36]
 + c2.v[77]*MainFormSLS->hh_1[140]
 + c2.v[78]*MainFormSLS->hh_1[84]
 + c2.v[79]*MainFormSLS->hh_1[28];
s/=N_2;
out.push_back(s);
//������ 133
s =c2.v[0]*MainFormSLS->hh_1[133]
 + c2.v[1]*MainFormSLS->hh_1[79]
 + c2.v[2]*MainFormSLS->hh_1[25]
 + c2.v[3]*MainFormSLS->hh_1[131]
 + c2.v[4]*MainFormSLS->hh_1[77]
 + c2.v[5]*MainFormSLS->hh_1[23]
 + c2.v[6]*MainFormSLS->hh_1[129]
 + c2.v[7]*MainFormSLS->hh_1[75]
 + c2.v[8]*MainFormSLS->hh_1[21]
 + c2.v[9]*MainFormSLS->hh_1[127]
 + c2.v[10]*MainFormSLS->hh_1[73]
 + c2.v[11]*MainFormSLS->hh_1[19]
 + c2.v[12]*MainFormSLS->hh_1[125]
 + c2.v[13]*MainFormSLS->hh_1[71]
 + c2.v[14]*MainFormSLS->hh_1[17]
 + c2.v[15]*MainFormSLS->hh_1[123]
 + c2.v[16]*MainFormSLS->hh_1[69]
 + c2.v[17]*MainFormSLS->hh_1[15]
 + c2.v[18]*MainFormSLS->hh_1[121]
 + c2.v[19]*MainFormSLS->hh_1[67]
 + c2.v[20]*MainFormSLS->hh_1[13]
 + c2.v[21]*MainFormSLS->hh_1[119]
 + c2.v[22]*MainFormSLS->hh_1[65]
 + c2.v[23]*MainFormSLS->hh_1[11]
 + c2.v[24]*MainFormSLS->hh_1[117]
 + c2.v[25]*MainFormSLS->hh_1[63]
 + c2.v[26]*MainFormSLS->hh_1[9]
 + c2.v[27]*MainFormSLS->hh_1[115]
 + c2.v[28]*MainFormSLS->hh_1[61]
 + c2.v[29]*MainFormSLS->hh_1[7]
 + c2.v[30]*MainFormSLS->hh_1[113]
 + c2.v[31]*MainFormSLS->hh_1[59]
 + c2.v[32]*MainFormSLS->hh_1[5]
 + c2.v[33]*MainFormSLS->hh_1[111]
 + c2.v[34]*MainFormSLS->hh_1[57]
 + c2.v[35]*MainFormSLS->hh_1[3]
 + c2.v[36]*MainFormSLS->hh_1[109]
 + c2.v[37]*MainFormSLS->hh_1[55]
 + c2.v[38]*MainFormSLS->hh_1[1]
 + c2.v[39]*MainFormSLS->hh_1[107]
 + c2.v[40]*MainFormSLS->hh_1[53]
 + c2.v[41]*MainFormSLS->hh_1[159]
 + c2.v[42]*MainFormSLS->hh_1[105]
 + c2.v[43]*MainFormSLS->hh_1[51]
 + c2.v[44]*MainFormSLS->hh_1[157]
 + c2.v[45]*MainFormSLS->hh_1[103]
 + c2.v[46]*MainFormSLS->hh_1[49]
 + c2.v[47]*MainFormSLS->hh_1[155]
 + c2.v[48]*MainFormSLS->hh_1[101]
 + c2.v[49]*MainFormSLS->hh_1[47]
 + c2.v[50]*MainFormSLS->hh_1[153]
 + c2.v[51]*MainFormSLS->hh_1[99]
 + c2.v[52]*MainFormSLS->hh_1[45]
 + c2.v[53]*MainFormSLS->hh_1[151]
 + c2.v[54]*MainFormSLS->hh_1[97]
 + c2.v[55]*MainFormSLS->hh_1[43]
 + c2.v[56]*MainFormSLS->hh_1[149]
 + c2.v[57]*MainFormSLS->hh_1[95]
 + c2.v[58]*MainFormSLS->hh_1[41]
 + c2.v[59]*MainFormSLS->hh_1[147]
 + c2.v[60]*MainFormSLS->hh_1[93]
 + c2.v[61]*MainFormSLS->hh_1[39]
 + c2.v[62]*MainFormSLS->hh_1[145]
 + c2.v[63]*MainFormSLS->hh_1[91]
 + c2.v[64]*MainFormSLS->hh_1[37]
 + c2.v[65]*MainFormSLS->hh_1[143]
 + c2.v[66]*MainFormSLS->hh_1[89]
 + c2.v[67]*MainFormSLS->hh_1[35]
 + c2.v[68]*MainFormSLS->hh_1[141]
 + c2.v[69]*MainFormSLS->hh_1[87]
 + c2.v[70]*MainFormSLS->hh_1[33]
 + c2.v[71]*MainFormSLS->hh_1[139]
 + c2.v[72]*MainFormSLS->hh_1[85]
 + c2.v[73]*MainFormSLS->hh_1[31]
 + c2.v[74]*MainFormSLS->hh_1[137]
 + c2.v[75]*MainFormSLS->hh_1[83]
 + c2.v[76]*MainFormSLS->hh_1[29]
 + c2.v[77]*MainFormSLS->hh_1[135]
 + c2.v[78]*MainFormSLS->hh_1[81]
 + c2.v[79]*MainFormSLS->hh_1[27];
s/=N_2;
out.push_back(s);
//������ 134
s =c2.v[0]*MainFormSLS->hh_1[134]
 + c2.v[1]*MainFormSLS->hh_1[82]
 + c2.v[2]*MainFormSLS->hh_1[30]
 + c2.v[3]*MainFormSLS->hh_1[138]
 + c2.v[4]*MainFormSLS->hh_1[86]
 + c2.v[5]*MainFormSLS->hh_1[34]
 + c2.v[6]*MainFormSLS->hh_1[142]
 + c2.v[7]*MainFormSLS->hh_1[90]
 + c2.v[8]*MainFormSLS->hh_1[38]
 + c2.v[9]*MainFormSLS->hh_1[146]
 + c2.v[10]*MainFormSLS->hh_1[94]
 + c2.v[11]*MainFormSLS->hh_1[42]
 + c2.v[12]*MainFormSLS->hh_1[150]
 + c2.v[13]*MainFormSLS->hh_1[98]
 + c2.v[14]*MainFormSLS->hh_1[46]
 + c2.v[15]*MainFormSLS->hh_1[154]
 + c2.v[16]*MainFormSLS->hh_1[102]
 + c2.v[17]*MainFormSLS->hh_1[50]
 + c2.v[18]*MainFormSLS->hh_1[158]
 + c2.v[19]*MainFormSLS->hh_1[106]
 + c2.v[20]*MainFormSLS->hh_1[54]
 + c2.v[21]*MainFormSLS->hh_1[2]
 + c2.v[22]*MainFormSLS->hh_1[110]
 + c2.v[23]*MainFormSLS->hh_1[58]
 + c2.v[24]*MainFormSLS->hh_1[6]
 + c2.v[25]*MainFormSLS->hh_1[114]
 + c2.v[26]*MainFormSLS->hh_1[62]
 + c2.v[27]*MainFormSLS->hh_1[10]
 + c2.v[28]*MainFormSLS->hh_1[118]
 + c2.v[29]*MainFormSLS->hh_1[66]
 + c2.v[30]*MainFormSLS->hh_1[14]
 + c2.v[31]*MainFormSLS->hh_1[122]
 + c2.v[32]*MainFormSLS->hh_1[70]
 + c2.v[33]*MainFormSLS->hh_1[18]
 + c2.v[34]*MainFormSLS->hh_1[126]
 + c2.v[35]*MainFormSLS->hh_1[74]
 + c2.v[36]*MainFormSLS->hh_1[22]
 + c2.v[37]*MainFormSLS->hh_1[130]
 + c2.v[38]*MainFormSLS->hh_1[78]
 + c2.v[39]*MainFormSLS->hh_1[26]
 + c2.v[40]*MainFormSLS->hh_1[134]
 + c2.v[41]*MainFormSLS->hh_1[82]
 + c2.v[42]*MainFormSLS->hh_1[30]
 + c2.v[43]*MainFormSLS->hh_1[138]
 + c2.v[44]*MainFormSLS->hh_1[86]
 + c2.v[45]*MainFormSLS->hh_1[34]
 + c2.v[46]*MainFormSLS->hh_1[142]
 + c2.v[47]*MainFormSLS->hh_1[90]
 + c2.v[48]*MainFormSLS->hh_1[38]
 + c2.v[49]*MainFormSLS->hh_1[146]
 + c2.v[50]*MainFormSLS->hh_1[94]
 + c2.v[51]*MainFormSLS->hh_1[42]
 + c2.v[52]*MainFormSLS->hh_1[150]
 + c2.v[53]*MainFormSLS->hh_1[98]
 + c2.v[54]*MainFormSLS->hh_1[46]
 + c2.v[55]*MainFormSLS->hh_1[154]
 + c2.v[56]*MainFormSLS->hh_1[102]
 + c2.v[57]*MainFormSLS->hh_1[50]
 + c2.v[58]*MainFormSLS->hh_1[158]
 + c2.v[59]*MainFormSLS->hh_1[106]
 + c2.v[60]*MainFormSLS->hh_1[54]
 + c2.v[61]*MainFormSLS->hh_1[2]
 + c2.v[62]*MainFormSLS->hh_1[110]
 + c2.v[63]*MainFormSLS->hh_1[58]
 + c2.v[64]*MainFormSLS->hh_1[6]
 + c2.v[65]*MainFormSLS->hh_1[114]
 + c2.v[66]*MainFormSLS->hh_1[62]
 + c2.v[67]*MainFormSLS->hh_1[10]
 + c2.v[68]*MainFormSLS->hh_1[118]
 + c2.v[69]*MainFormSLS->hh_1[66]
 + c2.v[70]*MainFormSLS->hh_1[14]
 + c2.v[71]*MainFormSLS->hh_1[122]
 + c2.v[72]*MainFormSLS->hh_1[70]
 + c2.v[73]*MainFormSLS->hh_1[18]
 + c2.v[74]*MainFormSLS->hh_1[126]
 + c2.v[75]*MainFormSLS->hh_1[74]
 + c2.v[76]*MainFormSLS->hh_1[22]
 + c2.v[77]*MainFormSLS->hh_1[130]
 + c2.v[78]*MainFormSLS->hh_1[78]
 + c2.v[79]*MainFormSLS->hh_1[26];
s/=N_2;
out.push_back(s);
//������ 135
s =c2.v[0]*MainFormSLS->hh_1[135]
 + c2.v[1]*MainFormSLS->hh_1[85]
 + c2.v[2]*MainFormSLS->hh_1[35]
 + c2.v[3]*MainFormSLS->hh_1[145]
 + c2.v[4]*MainFormSLS->hh_1[95]
 + c2.v[5]*MainFormSLS->hh_1[45]
 + c2.v[6]*MainFormSLS->hh_1[155]
 + c2.v[7]*MainFormSLS->hh_1[105]
 + c2.v[8]*MainFormSLS->hh_1[55]
 + c2.v[9]*MainFormSLS->hh_1[5]
 + c2.v[10]*MainFormSLS->hh_1[115]
 + c2.v[11]*MainFormSLS->hh_1[65]
 + c2.v[12]*MainFormSLS->hh_1[15]
 + c2.v[13]*MainFormSLS->hh_1[125]
 + c2.v[14]*MainFormSLS->hh_1[75]
 + c2.v[15]*MainFormSLS->hh_1[25]
 + c2.v[16]*MainFormSLS->hh_1[135]
 + c2.v[17]*MainFormSLS->hh_1[85]
 + c2.v[18]*MainFormSLS->hh_1[35]
 + c2.v[19]*MainFormSLS->hh_1[145]
 + c2.v[20]*MainFormSLS->hh_1[95]
 + c2.v[21]*MainFormSLS->hh_1[45]
 + c2.v[22]*MainFormSLS->hh_1[155]
 + c2.v[23]*MainFormSLS->hh_1[105]
 + c2.v[24]*MainFormSLS->hh_1[55]
 + c2.v[25]*MainFormSLS->hh_1[5]
 + c2.v[26]*MainFormSLS->hh_1[115]
 + c2.v[27]*MainFormSLS->hh_1[65]
 + c2.v[28]*MainFormSLS->hh_1[15]
 + c2.v[29]*MainFormSLS->hh_1[125]
 + c2.v[30]*MainFormSLS->hh_1[75]
 + c2.v[31]*MainFormSLS->hh_1[25]
 + c2.v[32]*MainFormSLS->hh_1[135]
 + c2.v[33]*MainFormSLS->hh_1[85]
 + c2.v[34]*MainFormSLS->hh_1[35]
 + c2.v[35]*MainFormSLS->hh_1[145]
 + c2.v[36]*MainFormSLS->hh_1[95]
 + c2.v[37]*MainFormSLS->hh_1[45]
 + c2.v[38]*MainFormSLS->hh_1[155]
 + c2.v[39]*MainFormSLS->hh_1[105]
 + c2.v[40]*MainFormSLS->hh_1[55]
 + c2.v[41]*MainFormSLS->hh_1[5]
 + c2.v[42]*MainFormSLS->hh_1[115]
 + c2.v[43]*MainFormSLS->hh_1[65]
 + c2.v[44]*MainFormSLS->hh_1[15]
 + c2.v[45]*MainFormSLS->hh_1[125]
 + c2.v[46]*MainFormSLS->hh_1[75]
 + c2.v[47]*MainFormSLS->hh_1[25]
 + c2.v[48]*MainFormSLS->hh_1[135]
 + c2.v[49]*MainFormSLS->hh_1[85]
 + c2.v[50]*MainFormSLS->hh_1[35]
 + c2.v[51]*MainFormSLS->hh_1[145]
 + c2.v[52]*MainFormSLS->hh_1[95]
 + c2.v[53]*MainFormSLS->hh_1[45]
 + c2.v[54]*MainFormSLS->hh_1[155]
 + c2.v[55]*MainFormSLS->hh_1[105]
 + c2.v[56]*MainFormSLS->hh_1[55]
 + c2.v[57]*MainFormSLS->hh_1[5]
 + c2.v[58]*MainFormSLS->hh_1[115]
 + c2.v[59]*MainFormSLS->hh_1[65]
 + c2.v[60]*MainFormSLS->hh_1[15]
 + c2.v[61]*MainFormSLS->hh_1[125]
 + c2.v[62]*MainFormSLS->hh_1[75]
 + c2.v[63]*MainFormSLS->hh_1[25]
 + c2.v[64]*MainFormSLS->hh_1[135]
 + c2.v[65]*MainFormSLS->hh_1[85]
 + c2.v[66]*MainFormSLS->hh_1[35]
 + c2.v[67]*MainFormSLS->hh_1[145]
 + c2.v[68]*MainFormSLS->hh_1[95]
 + c2.v[69]*MainFormSLS->hh_1[45]
 + c2.v[70]*MainFormSLS->hh_1[155]
 + c2.v[71]*MainFormSLS->hh_1[105]
 + c2.v[72]*MainFormSLS->hh_1[55]
 + c2.v[73]*MainFormSLS->hh_1[5]
 + c2.v[74]*MainFormSLS->hh_1[115]
 + c2.v[75]*MainFormSLS->hh_1[65]
 + c2.v[76]*MainFormSLS->hh_1[15]
 + c2.v[77]*MainFormSLS->hh_1[125]
 + c2.v[78]*MainFormSLS->hh_1[75]
 + c2.v[79]*MainFormSLS->hh_1[25];
s/=N_2;
out.push_back(s);
//������ 136
s =c2.v[0]*MainFormSLS->hh_1[136]
 + c2.v[1]*MainFormSLS->hh_1[88]
 + c2.v[2]*MainFormSLS->hh_1[40]
 + c2.v[3]*MainFormSLS->hh_1[152]
 + c2.v[4]*MainFormSLS->hh_1[104]
 + c2.v[5]*MainFormSLS->hh_1[56]
 + c2.v[6]*MainFormSLS->hh_1[8]
 + c2.v[7]*MainFormSLS->hh_1[120]
 + c2.v[8]*MainFormSLS->hh_1[72]
 + c2.v[9]*MainFormSLS->hh_1[24]
 + c2.v[10]*MainFormSLS->hh_1[136]
 + c2.v[11]*MainFormSLS->hh_1[88]
 + c2.v[12]*MainFormSLS->hh_1[40]
 + c2.v[13]*MainFormSLS->hh_1[152]
 + c2.v[14]*MainFormSLS->hh_1[104]
 + c2.v[15]*MainFormSLS->hh_1[56]
 + c2.v[16]*MainFormSLS->hh_1[8]
 + c2.v[17]*MainFormSLS->hh_1[120]
 + c2.v[18]*MainFormSLS->hh_1[72]
 + c2.v[19]*MainFormSLS->hh_1[24]
 + c2.v[20]*MainFormSLS->hh_1[136]
 + c2.v[21]*MainFormSLS->hh_1[88]
 + c2.v[22]*MainFormSLS->hh_1[40]
 + c2.v[23]*MainFormSLS->hh_1[152]
 + c2.v[24]*MainFormSLS->hh_1[104]
 + c2.v[25]*MainFormSLS->hh_1[56]
 + c2.v[26]*MainFormSLS->hh_1[8]
 + c2.v[27]*MainFormSLS->hh_1[120]
 + c2.v[28]*MainFormSLS->hh_1[72]
 + c2.v[29]*MainFormSLS->hh_1[24]
 + c2.v[30]*MainFormSLS->hh_1[136]
 + c2.v[31]*MainFormSLS->hh_1[88]
 + c2.v[32]*MainFormSLS->hh_1[40]
 + c2.v[33]*MainFormSLS->hh_1[152]
 + c2.v[34]*MainFormSLS->hh_1[104]
 + c2.v[35]*MainFormSLS->hh_1[56]
 + c2.v[36]*MainFormSLS->hh_1[8]
 + c2.v[37]*MainFormSLS->hh_1[120]
 + c2.v[38]*MainFormSLS->hh_1[72]
 + c2.v[39]*MainFormSLS->hh_1[24]
 + c2.v[40]*MainFormSLS->hh_1[136]
 + c2.v[41]*MainFormSLS->hh_1[88]
 + c2.v[42]*MainFormSLS->hh_1[40]
 + c2.v[43]*MainFormSLS->hh_1[152]
 + c2.v[44]*MainFormSLS->hh_1[104]
 + c2.v[45]*MainFormSLS->hh_1[56]
 + c2.v[46]*MainFormSLS->hh_1[8]
 + c2.v[47]*MainFormSLS->hh_1[120]
 + c2.v[48]*MainFormSLS->hh_1[72]
 + c2.v[49]*MainFormSLS->hh_1[24]
 + c2.v[50]*MainFormSLS->hh_1[136]
 + c2.v[51]*MainFormSLS->hh_1[88]
 + c2.v[52]*MainFormSLS->hh_1[40]
 + c2.v[53]*MainFormSLS->hh_1[152]
 + c2.v[54]*MainFormSLS->hh_1[104]
 + c2.v[55]*MainFormSLS->hh_1[56]
 + c2.v[56]*MainFormSLS->hh_1[8]
 + c2.v[57]*MainFormSLS->hh_1[120]
 + c2.v[58]*MainFormSLS->hh_1[72]
 + c2.v[59]*MainFormSLS->hh_1[24]
 + c2.v[60]*MainFormSLS->hh_1[136]
 + c2.v[61]*MainFormSLS->hh_1[88]
 + c2.v[62]*MainFormSLS->hh_1[40]
 + c2.v[63]*MainFormSLS->hh_1[152]
 + c2.v[64]*MainFormSLS->hh_1[104]
 + c2.v[65]*MainFormSLS->hh_1[56]
 + c2.v[66]*MainFormSLS->hh_1[8]
 + c2.v[67]*MainFormSLS->hh_1[120]
 + c2.v[68]*MainFormSLS->hh_1[72]
 + c2.v[69]*MainFormSLS->hh_1[24]
 + c2.v[70]*MainFormSLS->hh_1[136]
 + c2.v[71]*MainFormSLS->hh_1[88]
 + c2.v[72]*MainFormSLS->hh_1[40]
 + c2.v[73]*MainFormSLS->hh_1[152]
 + c2.v[74]*MainFormSLS->hh_1[104]
 + c2.v[75]*MainFormSLS->hh_1[56]
 + c2.v[76]*MainFormSLS->hh_1[8]
 + c2.v[77]*MainFormSLS->hh_1[120]
 + c2.v[78]*MainFormSLS->hh_1[72]
 + c2.v[79]*MainFormSLS->hh_1[24];
s/=N_2;
out.push_back(s);
//������ 137
s =c2.v[0]*MainFormSLS->hh_1[137]
 + c2.v[1]*MainFormSLS->hh_1[91]
 + c2.v[2]*MainFormSLS->hh_1[45]
 + c2.v[3]*MainFormSLS->hh_1[159]
 + c2.v[4]*MainFormSLS->hh_1[113]
 + c2.v[5]*MainFormSLS->hh_1[67]
 + c2.v[6]*MainFormSLS->hh_1[21]
 + c2.v[7]*MainFormSLS->hh_1[135]
 + c2.v[8]*MainFormSLS->hh_1[89]
 + c2.v[9]*MainFormSLS->hh_1[43]
 + c2.v[10]*MainFormSLS->hh_1[157]
 + c2.v[11]*MainFormSLS->hh_1[111]
 + c2.v[12]*MainFormSLS->hh_1[65]
 + c2.v[13]*MainFormSLS->hh_1[19]
 + c2.v[14]*MainFormSLS->hh_1[133]
 + c2.v[15]*MainFormSLS->hh_1[87]
 + c2.v[16]*MainFormSLS->hh_1[41]
 + c2.v[17]*MainFormSLS->hh_1[155]
 + c2.v[18]*MainFormSLS->hh_1[109]
 + c2.v[19]*MainFormSLS->hh_1[63]
 + c2.v[20]*MainFormSLS->hh_1[17]
 + c2.v[21]*MainFormSLS->hh_1[131]
 + c2.v[22]*MainFormSLS->hh_1[85]
 + c2.v[23]*MainFormSLS->hh_1[39]
 + c2.v[24]*MainFormSLS->hh_1[153]
 + c2.v[25]*MainFormSLS->hh_1[107]
 + c2.v[26]*MainFormSLS->hh_1[61]
 + c2.v[27]*MainFormSLS->hh_1[15]
 + c2.v[28]*MainFormSLS->hh_1[129]
 + c2.v[29]*MainFormSLS->hh_1[83]
 + c2.v[30]*MainFormSLS->hh_1[37]
 + c2.v[31]*MainFormSLS->hh_1[151]
 + c2.v[32]*MainFormSLS->hh_1[105]
 + c2.v[33]*MainFormSLS->hh_1[59]
 + c2.v[34]*MainFormSLS->hh_1[13]
 + c2.v[35]*MainFormSLS->hh_1[127]
 + c2.v[36]*MainFormSLS->hh_1[81]
 + c2.v[37]*MainFormSLS->hh_1[35]
 + c2.v[38]*MainFormSLS->hh_1[149]
 + c2.v[39]*MainFormSLS->hh_1[103]
 + c2.v[40]*MainFormSLS->hh_1[57]
 + c2.v[41]*MainFormSLS->hh_1[11]
 + c2.v[42]*MainFormSLS->hh_1[125]
 + c2.v[43]*MainFormSLS->hh_1[79]
 + c2.v[44]*MainFormSLS->hh_1[33]
 + c2.v[45]*MainFormSLS->hh_1[147]
 + c2.v[46]*MainFormSLS->hh_1[101]
 + c2.v[47]*MainFormSLS->hh_1[55]
 + c2.v[48]*MainFormSLS->hh_1[9]
 + c2.v[49]*MainFormSLS->hh_1[123]
 + c2.v[50]*MainFormSLS->hh_1[77]
 + c2.v[51]*MainFormSLS->hh_1[31]
 + c2.v[52]*MainFormSLS->hh_1[145]
 + c2.v[53]*MainFormSLS->hh_1[99]
 + c2.v[54]*MainFormSLS->hh_1[53]
 + c2.v[55]*MainFormSLS->hh_1[7]
 + c2.v[56]*MainFormSLS->hh_1[121]
 + c2.v[57]*MainFormSLS->hh_1[75]
 + c2.v[58]*MainFormSLS->hh_1[29]
 + c2.v[59]*MainFormSLS->hh_1[143]
 + c2.v[60]*MainFormSLS->hh_1[97]
 + c2.v[61]*MainFormSLS->hh_1[51]
 + c2.v[62]*MainFormSLS->hh_1[5]
 + c2.v[63]*MainFormSLS->hh_1[119]
 + c2.v[64]*MainFormSLS->hh_1[73]
 + c2.v[65]*MainFormSLS->hh_1[27]
 + c2.v[66]*MainFormSLS->hh_1[141]
 + c2.v[67]*MainFormSLS->hh_1[95]
 + c2.v[68]*MainFormSLS->hh_1[49]
 + c2.v[69]*MainFormSLS->hh_1[3]
 + c2.v[70]*MainFormSLS->hh_1[117]
 + c2.v[71]*MainFormSLS->hh_1[71]
 + c2.v[72]*MainFormSLS->hh_1[25]
 + c2.v[73]*MainFormSLS->hh_1[139]
 + c2.v[74]*MainFormSLS->hh_1[93]
 + c2.v[75]*MainFormSLS->hh_1[47]
 + c2.v[76]*MainFormSLS->hh_1[1]
 + c2.v[77]*MainFormSLS->hh_1[115]
 + c2.v[78]*MainFormSLS->hh_1[69]
 + c2.v[79]*MainFormSLS->hh_1[23];
s/=N_2;
out.push_back(s);
//������ 138
s =c2.v[0]*MainFormSLS->hh_1[138]
 + c2.v[1]*MainFormSLS->hh_1[94]
 + c2.v[2]*MainFormSLS->hh_1[50]
 + c2.v[3]*MainFormSLS->hh_1[6]
 + c2.v[4]*MainFormSLS->hh_1[122]
 + c2.v[5]*MainFormSLS->hh_1[78]
 + c2.v[6]*MainFormSLS->hh_1[34]
 + c2.v[7]*MainFormSLS->hh_1[150]
 + c2.v[8]*MainFormSLS->hh_1[106]
 + c2.v[9]*MainFormSLS->hh_1[62]
 + c2.v[10]*MainFormSLS->hh_1[18]
 + c2.v[11]*MainFormSLS->hh_1[134]
 + c2.v[12]*MainFormSLS->hh_1[90]
 + c2.v[13]*MainFormSLS->hh_1[46]
 + c2.v[14]*MainFormSLS->hh_1[2]
 + c2.v[15]*MainFormSLS->hh_1[118]
 + c2.v[16]*MainFormSLS->hh_1[74]
 + c2.v[17]*MainFormSLS->hh_1[30]
 + c2.v[18]*MainFormSLS->hh_1[146]
 + c2.v[19]*MainFormSLS->hh_1[102]
 + c2.v[20]*MainFormSLS->hh_1[58]
 + c2.v[21]*MainFormSLS->hh_1[14]
 + c2.v[22]*MainFormSLS->hh_1[130]
 + c2.v[23]*MainFormSLS->hh_1[86]
 + c2.v[24]*MainFormSLS->hh_1[42]
 + c2.v[25]*MainFormSLS->hh_1[158]
 + c2.v[26]*MainFormSLS->hh_1[114]
 + c2.v[27]*MainFormSLS->hh_1[70]
 + c2.v[28]*MainFormSLS->hh_1[26]
 + c2.v[29]*MainFormSLS->hh_1[142]
 + c2.v[30]*MainFormSLS->hh_1[98]
 + c2.v[31]*MainFormSLS->hh_1[54]
 + c2.v[32]*MainFormSLS->hh_1[10]
 + c2.v[33]*MainFormSLS->hh_1[126]
 + c2.v[34]*MainFormSLS->hh_1[82]
 + c2.v[35]*MainFormSLS->hh_1[38]
 + c2.v[36]*MainFormSLS->hh_1[154]
 + c2.v[37]*MainFormSLS->hh_1[110]
 + c2.v[38]*MainFormSLS->hh_1[66]
 + c2.v[39]*MainFormSLS->hh_1[22]
 + c2.v[40]*MainFormSLS->hh_1[138]
 + c2.v[41]*MainFormSLS->hh_1[94]
 + c2.v[42]*MainFormSLS->hh_1[50]
 + c2.v[43]*MainFormSLS->hh_1[6]
 + c2.v[44]*MainFormSLS->hh_1[122]
 + c2.v[45]*MainFormSLS->hh_1[78]
 + c2.v[46]*MainFormSLS->hh_1[34]
 + c2.v[47]*MainFormSLS->hh_1[150]
 + c2.v[48]*MainFormSLS->hh_1[106]
 + c2.v[49]*MainFormSLS->hh_1[62]
 + c2.v[50]*MainFormSLS->hh_1[18]
 + c2.v[51]*MainFormSLS->hh_1[134]
 + c2.v[52]*MainFormSLS->hh_1[90]
 + c2.v[53]*MainFormSLS->hh_1[46]
 + c2.v[54]*MainFormSLS->hh_1[2]
 + c2.v[55]*MainFormSLS->hh_1[118]
 + c2.v[56]*MainFormSLS->hh_1[74]
 + c2.v[57]*MainFormSLS->hh_1[30]
 + c2.v[58]*MainFormSLS->hh_1[146]
 + c2.v[59]*MainFormSLS->hh_1[102]
 + c2.v[60]*MainFormSLS->hh_1[58]
 + c2.v[61]*MainFormSLS->hh_1[14]
 + c2.v[62]*MainFormSLS->hh_1[130]
 + c2.v[63]*MainFormSLS->hh_1[86]
 + c2.v[64]*MainFormSLS->hh_1[42]
 + c2.v[65]*MainFormSLS->hh_1[158]
 + c2.v[66]*MainFormSLS->hh_1[114]
 + c2.v[67]*MainFormSLS->hh_1[70]
 + c2.v[68]*MainFormSLS->hh_1[26]
 + c2.v[69]*MainFormSLS->hh_1[142]
 + c2.v[70]*MainFormSLS->hh_1[98]
 + c2.v[71]*MainFormSLS->hh_1[54]
 + c2.v[72]*MainFormSLS->hh_1[10]
 + c2.v[73]*MainFormSLS->hh_1[126]
 + c2.v[74]*MainFormSLS->hh_1[82]
 + c2.v[75]*MainFormSLS->hh_1[38]
 + c2.v[76]*MainFormSLS->hh_1[154]
 + c2.v[77]*MainFormSLS->hh_1[110]
 + c2.v[78]*MainFormSLS->hh_1[66]
 + c2.v[79]*MainFormSLS->hh_1[22];
s/=N_2;
out.push_back(s);
//������ 139
s =c2.v[0]*MainFormSLS->hh_1[139]
 + c2.v[1]*MainFormSLS->hh_1[97]
 + c2.v[2]*MainFormSLS->hh_1[55]
 + c2.v[3]*MainFormSLS->hh_1[13]
 + c2.v[4]*MainFormSLS->hh_1[131]
 + c2.v[5]*MainFormSLS->hh_1[89]
 + c2.v[6]*MainFormSLS->hh_1[47]
 + c2.v[7]*MainFormSLS->hh_1[5]
 + c2.v[8]*MainFormSLS->hh_1[123]
 + c2.v[9]*MainFormSLS->hh_1[81]
 + c2.v[10]*MainFormSLS->hh_1[39]
 + c2.v[11]*MainFormSLS->hh_1[157]
 + c2.v[12]*MainFormSLS->hh_1[115]
 + c2.v[13]*MainFormSLS->hh_1[73]
 + c2.v[14]*MainFormSLS->hh_1[31]
 + c2.v[15]*MainFormSLS->hh_1[149]
 + c2.v[16]*MainFormSLS->hh_1[107]
 + c2.v[17]*MainFormSLS->hh_1[65]
 + c2.v[18]*MainFormSLS->hh_1[23]
 + c2.v[19]*MainFormSLS->hh_1[141]
 + c2.v[20]*MainFormSLS->hh_1[99]
 + c2.v[21]*MainFormSLS->hh_1[57]
 + c2.v[22]*MainFormSLS->hh_1[15]
 + c2.v[23]*MainFormSLS->hh_1[133]
 + c2.v[24]*MainFormSLS->hh_1[91]
 + c2.v[25]*MainFormSLS->hh_1[49]
 + c2.v[26]*MainFormSLS->hh_1[7]
 + c2.v[27]*MainFormSLS->hh_1[125]
 + c2.v[28]*MainFormSLS->hh_1[83]
 + c2.v[29]*MainFormSLS->hh_1[41]
 + c2.v[30]*MainFormSLS->hh_1[159]
 + c2.v[31]*MainFormSLS->hh_1[117]
 + c2.v[32]*MainFormSLS->hh_1[75]
 + c2.v[33]*MainFormSLS->hh_1[33]
 + c2.v[34]*MainFormSLS->hh_1[151]
 + c2.v[35]*MainFormSLS->hh_1[109]
 + c2.v[36]*MainFormSLS->hh_1[67]
 + c2.v[37]*MainFormSLS->hh_1[25]
 + c2.v[38]*MainFormSLS->hh_1[143]
 + c2.v[39]*MainFormSLS->hh_1[101]
 + c2.v[40]*MainFormSLS->hh_1[59]
 + c2.v[41]*MainFormSLS->hh_1[17]
 + c2.v[42]*MainFormSLS->hh_1[135]
 + c2.v[43]*MainFormSLS->hh_1[93]
 + c2.v[44]*MainFormSLS->hh_1[51]
 + c2.v[45]*MainFormSLS->hh_1[9]
 + c2.v[46]*MainFormSLS->hh_1[127]
 + c2.v[47]*MainFormSLS->hh_1[85]
 + c2.v[48]*MainFormSLS->hh_1[43]
 + c2.v[49]*MainFormSLS->hh_1[1]
 + c2.v[50]*MainFormSLS->hh_1[119]
 + c2.v[51]*MainFormSLS->hh_1[77]
 + c2.v[52]*MainFormSLS->hh_1[35]
 + c2.v[53]*MainFormSLS->hh_1[153]
 + c2.v[54]*MainFormSLS->hh_1[111]
 + c2.v[55]*MainFormSLS->hh_1[69]
 + c2.v[56]*MainFormSLS->hh_1[27]
 + c2.v[57]*MainFormSLS->hh_1[145]
 + c2.v[58]*MainFormSLS->hh_1[103]
 + c2.v[59]*MainFormSLS->hh_1[61]
 + c2.v[60]*MainFormSLS->hh_1[19]
 + c2.v[61]*MainFormSLS->hh_1[137]
 + c2.v[62]*MainFormSLS->hh_1[95]
 + c2.v[63]*MainFormSLS->hh_1[53]
 + c2.v[64]*MainFormSLS->hh_1[11]
 + c2.v[65]*MainFormSLS->hh_1[129]
 + c2.v[66]*MainFormSLS->hh_1[87]
 + c2.v[67]*MainFormSLS->hh_1[45]
 + c2.v[68]*MainFormSLS->hh_1[3]
 + c2.v[69]*MainFormSLS->hh_1[121]
 + c2.v[70]*MainFormSLS->hh_1[79]
 + c2.v[71]*MainFormSLS->hh_1[37]
 + c2.v[72]*MainFormSLS->hh_1[155]
 + c2.v[73]*MainFormSLS->hh_1[113]
 + c2.v[74]*MainFormSLS->hh_1[71]
 + c2.v[75]*MainFormSLS->hh_1[29]
 + c2.v[76]*MainFormSLS->hh_1[147]
 + c2.v[77]*MainFormSLS->hh_1[105]
 + c2.v[78]*MainFormSLS->hh_1[63]
 + c2.v[79]*MainFormSLS->hh_1[21];
s/=N_2;
out.push_back(s);
//������ 140
s =c2.v[0]*MainFormSLS->hh_1[140]
 + c2.v[1]*MainFormSLS->hh_1[100]
 + c2.v[2]*MainFormSLS->hh_1[60]
 + c2.v[3]*MainFormSLS->hh_1[20]
 + c2.v[4]*MainFormSLS->hh_1[140]
 + c2.v[5]*MainFormSLS->hh_1[100]
 + c2.v[6]*MainFormSLS->hh_1[60]
 + c2.v[7]*MainFormSLS->hh_1[20]
 + c2.v[8]*MainFormSLS->hh_1[140]
 + c2.v[9]*MainFormSLS->hh_1[100]
 + c2.v[10]*MainFormSLS->hh_1[60]
 + c2.v[11]*MainFormSLS->hh_1[20]
 + c2.v[12]*MainFormSLS->hh_1[140]
 + c2.v[13]*MainFormSLS->hh_1[100]
 + c2.v[14]*MainFormSLS->hh_1[60]
 + c2.v[15]*MainFormSLS->hh_1[20]
 + c2.v[16]*MainFormSLS->hh_1[140]
 + c2.v[17]*MainFormSLS->hh_1[100]
 + c2.v[18]*MainFormSLS->hh_1[60]
 + c2.v[19]*MainFormSLS->hh_1[20]
 + c2.v[20]*MainFormSLS->hh_1[140]
 + c2.v[21]*MainFormSLS->hh_1[100]
 + c2.v[22]*MainFormSLS->hh_1[60]
 + c2.v[23]*MainFormSLS->hh_1[20]
 + c2.v[24]*MainFormSLS->hh_1[140]
 + c2.v[25]*MainFormSLS->hh_1[100]
 + c2.v[26]*MainFormSLS->hh_1[60]
 + c2.v[27]*MainFormSLS->hh_1[20]
 + c2.v[28]*MainFormSLS->hh_1[140]
 + c2.v[29]*MainFormSLS->hh_1[100]
 + c2.v[30]*MainFormSLS->hh_1[60]
 + c2.v[31]*MainFormSLS->hh_1[20]
 + c2.v[32]*MainFormSLS->hh_1[140]
 + c2.v[33]*MainFormSLS->hh_1[100]
 + c2.v[34]*MainFormSLS->hh_1[60]
 + c2.v[35]*MainFormSLS->hh_1[20]
 + c2.v[36]*MainFormSLS->hh_1[140]
 + c2.v[37]*MainFormSLS->hh_1[100]
 + c2.v[38]*MainFormSLS->hh_1[60]
 + c2.v[39]*MainFormSLS->hh_1[20]
 + c2.v[40]*MainFormSLS->hh_1[140]
 + c2.v[41]*MainFormSLS->hh_1[100]
 + c2.v[42]*MainFormSLS->hh_1[60]
 + c2.v[43]*MainFormSLS->hh_1[20]
 + c2.v[44]*MainFormSLS->hh_1[140]
 + c2.v[45]*MainFormSLS->hh_1[100]
 + c2.v[46]*MainFormSLS->hh_1[60]
 + c2.v[47]*MainFormSLS->hh_1[20]
 + c2.v[48]*MainFormSLS->hh_1[140]
 + c2.v[49]*MainFormSLS->hh_1[100]
 + c2.v[50]*MainFormSLS->hh_1[60]
 + c2.v[51]*MainFormSLS->hh_1[20]
 + c2.v[52]*MainFormSLS->hh_1[140]
 + c2.v[53]*MainFormSLS->hh_1[100]
 + c2.v[54]*MainFormSLS->hh_1[60]
 + c2.v[55]*MainFormSLS->hh_1[20]
 + c2.v[56]*MainFormSLS->hh_1[140]
 + c2.v[57]*MainFormSLS->hh_1[100]
 + c2.v[58]*MainFormSLS->hh_1[60]
 + c2.v[59]*MainFormSLS->hh_1[20]
 + c2.v[60]*MainFormSLS->hh_1[140]
 + c2.v[61]*MainFormSLS->hh_1[100]
 + c2.v[62]*MainFormSLS->hh_1[60]
 + c2.v[63]*MainFormSLS->hh_1[20]
 + c2.v[64]*MainFormSLS->hh_1[140]
 + c2.v[65]*MainFormSLS->hh_1[100]
 + c2.v[66]*MainFormSLS->hh_1[60]
 + c2.v[67]*MainFormSLS->hh_1[20]
 + c2.v[68]*MainFormSLS->hh_1[140]
 + c2.v[69]*MainFormSLS->hh_1[100]
 + c2.v[70]*MainFormSLS->hh_1[60]
 + c2.v[71]*MainFormSLS->hh_1[20]
 + c2.v[72]*MainFormSLS->hh_1[140]
 + c2.v[73]*MainFormSLS->hh_1[100]
 + c2.v[74]*MainFormSLS->hh_1[60]
 + c2.v[75]*MainFormSLS->hh_1[20]
 + c2.v[76]*MainFormSLS->hh_1[140]
 + c2.v[77]*MainFormSLS->hh_1[100]
 + c2.v[78]*MainFormSLS->hh_1[60]
 + c2.v[79]*MainFormSLS->hh_1[20];
s/=N_2;
out.push_back(s);
//������ 141
s =c2.v[0]*MainFormSLS->hh_1[141]
 + c2.v[1]*MainFormSLS->hh_1[103]
 + c2.v[2]*MainFormSLS->hh_1[65]
 + c2.v[3]*MainFormSLS->hh_1[27]
 + c2.v[4]*MainFormSLS->hh_1[149]
 + c2.v[5]*MainFormSLS->hh_1[111]
 + c2.v[6]*MainFormSLS->hh_1[73]
 + c2.v[7]*MainFormSLS->hh_1[35]
 + c2.v[8]*MainFormSLS->hh_1[157]
 + c2.v[9]*MainFormSLS->hh_1[119]
 + c2.v[10]*MainFormSLS->hh_1[81]
 + c2.v[11]*MainFormSLS->hh_1[43]
 + c2.v[12]*MainFormSLS->hh_1[5]
 + c2.v[13]*MainFormSLS->hh_1[127]
 + c2.v[14]*MainFormSLS->hh_1[89]
 + c2.v[15]*MainFormSLS->hh_1[51]
 + c2.v[16]*MainFormSLS->hh_1[13]
 + c2.v[17]*MainFormSLS->hh_1[135]
 + c2.v[18]*MainFormSLS->hh_1[97]
 + c2.v[19]*MainFormSLS->hh_1[59]
 + c2.v[20]*MainFormSLS->hh_1[21]
 + c2.v[21]*MainFormSLS->hh_1[143]
 + c2.v[22]*MainFormSLS->hh_1[105]
 + c2.v[23]*MainFormSLS->hh_1[67]
 + c2.v[24]*MainFormSLS->hh_1[29]
 + c2.v[25]*MainFormSLS->hh_1[151]
 + c2.v[26]*MainFormSLS->hh_1[113]
 + c2.v[27]*MainFormSLS->hh_1[75]
 + c2.v[28]*MainFormSLS->hh_1[37]
 + c2.v[29]*MainFormSLS->hh_1[159]
 + c2.v[30]*MainFormSLS->hh_1[121]
 + c2.v[31]*MainFormSLS->hh_1[83]
 + c2.v[32]*MainFormSLS->hh_1[45]
 + c2.v[33]*MainFormSLS->hh_1[7]
 + c2.v[34]*MainFormSLS->hh_1[129]
 + c2.v[35]*MainFormSLS->hh_1[91]
 + c2.v[36]*MainFormSLS->hh_1[53]
 + c2.v[37]*MainFormSLS->hh_1[15]
 + c2.v[38]*MainFormSLS->hh_1[137]
 + c2.v[39]*MainFormSLS->hh_1[99]
 + c2.v[40]*MainFormSLS->hh_1[61]
 + c2.v[41]*MainFormSLS->hh_1[23]
 + c2.v[42]*MainFormSLS->hh_1[145]
 + c2.v[43]*MainFormSLS->hh_1[107]
 + c2.v[44]*MainFormSLS->hh_1[69]
 + c2.v[45]*MainFormSLS->hh_1[31]
 + c2.v[46]*MainFormSLS->hh_1[153]
 + c2.v[47]*MainFormSLS->hh_1[115]
 + c2.v[48]*MainFormSLS->hh_1[77]
 + c2.v[49]*MainFormSLS->hh_1[39]
 + c2.v[50]*MainFormSLS->hh_1[1]
 + c2.v[51]*MainFormSLS->hh_1[123]
 + c2.v[52]*MainFormSLS->hh_1[85]
 + c2.v[53]*MainFormSLS->hh_1[47]
 + c2.v[54]*MainFormSLS->hh_1[9]
 + c2.v[55]*MainFormSLS->hh_1[131]
 + c2.v[56]*MainFormSLS->hh_1[93]
 + c2.v[57]*MainFormSLS->hh_1[55]
 + c2.v[58]*MainFormSLS->hh_1[17]
 + c2.v[59]*MainFormSLS->hh_1[139]
 + c2.v[60]*MainFormSLS->hh_1[101]
 + c2.v[61]*MainFormSLS->hh_1[63]
 + c2.v[62]*MainFormSLS->hh_1[25]
 + c2.v[63]*MainFormSLS->hh_1[147]
 + c2.v[64]*MainFormSLS->hh_1[109]
 + c2.v[65]*MainFormSLS->hh_1[71]
 + c2.v[66]*MainFormSLS->hh_1[33]
 + c2.v[67]*MainFormSLS->hh_1[155]
 + c2.v[68]*MainFormSLS->hh_1[117]
 + c2.v[69]*MainFormSLS->hh_1[79]
 + c2.v[70]*MainFormSLS->hh_1[41]
 + c2.v[71]*MainFormSLS->hh_1[3]
 + c2.v[72]*MainFormSLS->hh_1[125]
 + c2.v[73]*MainFormSLS->hh_1[87]
 + c2.v[74]*MainFormSLS->hh_1[49]
 + c2.v[75]*MainFormSLS->hh_1[11]
 + c2.v[76]*MainFormSLS->hh_1[133]
 + c2.v[77]*MainFormSLS->hh_1[95]
 + c2.v[78]*MainFormSLS->hh_1[57]
 + c2.v[79]*MainFormSLS->hh_1[19];
s/=N_2;
out.push_back(s);
//������ 142
s =c2.v[0]*MainFormSLS->hh_1[142]
 + c2.v[1]*MainFormSLS->hh_1[106]
 + c2.v[2]*MainFormSLS->hh_1[70]
 + c2.v[3]*MainFormSLS->hh_1[34]
 + c2.v[4]*MainFormSLS->hh_1[158]
 + c2.v[5]*MainFormSLS->hh_1[122]
 + c2.v[6]*MainFormSLS->hh_1[86]
 + c2.v[7]*MainFormSLS->hh_1[50]
 + c2.v[8]*MainFormSLS->hh_1[14]
 + c2.v[9]*MainFormSLS->hh_1[138]
 + c2.v[10]*MainFormSLS->hh_1[102]
 + c2.v[11]*MainFormSLS->hh_1[66]
 + c2.v[12]*MainFormSLS->hh_1[30]
 + c2.v[13]*MainFormSLS->hh_1[154]
 + c2.v[14]*MainFormSLS->hh_1[118]
 + c2.v[15]*MainFormSLS->hh_1[82]
 + c2.v[16]*MainFormSLS->hh_1[46]
 + c2.v[17]*MainFormSLS->hh_1[10]
 + c2.v[18]*MainFormSLS->hh_1[134]
 + c2.v[19]*MainFormSLS->hh_1[98]
 + c2.v[20]*MainFormSLS->hh_1[62]
 + c2.v[21]*MainFormSLS->hh_1[26]
 + c2.v[22]*MainFormSLS->hh_1[150]
 + c2.v[23]*MainFormSLS->hh_1[114]
 + c2.v[24]*MainFormSLS->hh_1[78]
 + c2.v[25]*MainFormSLS->hh_1[42]
 + c2.v[26]*MainFormSLS->hh_1[6]
 + c2.v[27]*MainFormSLS->hh_1[130]
 + c2.v[28]*MainFormSLS->hh_1[94]
 + c2.v[29]*MainFormSLS->hh_1[58]
 + c2.v[30]*MainFormSLS->hh_1[22]
 + c2.v[31]*MainFormSLS->hh_1[146]
 + c2.v[32]*MainFormSLS->hh_1[110]
 + c2.v[33]*MainFormSLS->hh_1[74]
 + c2.v[34]*MainFormSLS->hh_1[38]
 + c2.v[35]*MainFormSLS->hh_1[2]
 + c2.v[36]*MainFormSLS->hh_1[126]
 + c2.v[37]*MainFormSLS->hh_1[90]
 + c2.v[38]*MainFormSLS->hh_1[54]
 + c2.v[39]*MainFormSLS->hh_1[18]
 + c2.v[40]*MainFormSLS->hh_1[142]
 + c2.v[41]*MainFormSLS->hh_1[106]
 + c2.v[42]*MainFormSLS->hh_1[70]
 + c2.v[43]*MainFormSLS->hh_1[34]
 + c2.v[44]*MainFormSLS->hh_1[158]
 + c2.v[45]*MainFormSLS->hh_1[122]
 + c2.v[46]*MainFormSLS->hh_1[86]
 + c2.v[47]*MainFormSLS->hh_1[50]
 + c2.v[48]*MainFormSLS->hh_1[14]
 + c2.v[49]*MainFormSLS->hh_1[138]
 + c2.v[50]*MainFormSLS->hh_1[102]
 + c2.v[51]*MainFormSLS->hh_1[66]
 + c2.v[52]*MainFormSLS->hh_1[30]
 + c2.v[53]*MainFormSLS->hh_1[154]
 + c2.v[54]*MainFormSLS->hh_1[118]
 + c2.v[55]*MainFormSLS->hh_1[82]
 + c2.v[56]*MainFormSLS->hh_1[46]
 + c2.v[57]*MainFormSLS->hh_1[10]
 + c2.v[58]*MainFormSLS->hh_1[134]
 + c2.v[59]*MainFormSLS->hh_1[98]
 + c2.v[60]*MainFormSLS->hh_1[62]
 + c2.v[61]*MainFormSLS->hh_1[26]
 + c2.v[62]*MainFormSLS->hh_1[150]
 + c2.v[63]*MainFormSLS->hh_1[114]
 + c2.v[64]*MainFormSLS->hh_1[78]
 + c2.v[65]*MainFormSLS->hh_1[42]
 + c2.v[66]*MainFormSLS->hh_1[6]
 + c2.v[67]*MainFormSLS->hh_1[130]
 + c2.v[68]*MainFormSLS->hh_1[94]
 + c2.v[69]*MainFormSLS->hh_1[58]
 + c2.v[70]*MainFormSLS->hh_1[22]
 + c2.v[71]*MainFormSLS->hh_1[146]
 + c2.v[72]*MainFormSLS->hh_1[110]
 + c2.v[73]*MainFormSLS->hh_1[74]
 + c2.v[74]*MainFormSLS->hh_1[38]
 + c2.v[75]*MainFormSLS->hh_1[2]
 + c2.v[76]*MainFormSLS->hh_1[126]
 + c2.v[77]*MainFormSLS->hh_1[90]
 + c2.v[78]*MainFormSLS->hh_1[54]
 + c2.v[79]*MainFormSLS->hh_1[18];
s/=N_2;
out.push_back(s);
//������ 143
s =c2.v[0]*MainFormSLS->hh_1[143]
 + c2.v[1]*MainFormSLS->hh_1[109]
 + c2.v[2]*MainFormSLS->hh_1[75]
 + c2.v[3]*MainFormSLS->hh_1[41]
 + c2.v[4]*MainFormSLS->hh_1[7]
 + c2.v[5]*MainFormSLS->hh_1[133]
 + c2.v[6]*MainFormSLS->hh_1[99]
 + c2.v[7]*MainFormSLS->hh_1[65]
 + c2.v[8]*MainFormSLS->hh_1[31]
 + c2.v[9]*MainFormSLS->hh_1[157]
 + c2.v[10]*MainFormSLS->hh_1[123]
 + c2.v[11]*MainFormSLS->hh_1[89]
 + c2.v[12]*MainFormSLS->hh_1[55]
 + c2.v[13]*MainFormSLS->hh_1[21]
 + c2.v[14]*MainFormSLS->hh_1[147]
 + c2.v[15]*MainFormSLS->hh_1[113]
 + c2.v[16]*MainFormSLS->hh_1[79]
 + c2.v[17]*MainFormSLS->hh_1[45]
 + c2.v[18]*MainFormSLS->hh_1[11]
 + c2.v[19]*MainFormSLS->hh_1[137]
 + c2.v[20]*MainFormSLS->hh_1[103]
 + c2.v[21]*MainFormSLS->hh_1[69]
 + c2.v[22]*MainFormSLS->hh_1[35]
 + c2.v[23]*MainFormSLS->hh_1[1]
 + c2.v[24]*MainFormSLS->hh_1[127]
 + c2.v[25]*MainFormSLS->hh_1[93]
 + c2.v[26]*MainFormSLS->hh_1[59]
 + c2.v[27]*MainFormSLS->hh_1[25]
 + c2.v[28]*MainFormSLS->hh_1[151]
 + c2.v[29]*MainFormSLS->hh_1[117]
 + c2.v[30]*MainFormSLS->hh_1[83]
 + c2.v[31]*MainFormSLS->hh_1[49]
 + c2.v[32]*MainFormSLS->hh_1[15]
 + c2.v[33]*MainFormSLS->hh_1[141]
 + c2.v[34]*MainFormSLS->hh_1[107]
 + c2.v[35]*MainFormSLS->hh_1[73]
 + c2.v[36]*MainFormSLS->hh_1[39]
 + c2.v[37]*MainFormSLS->hh_1[5]
 + c2.v[38]*MainFormSLS->hh_1[131]
 + c2.v[39]*MainFormSLS->hh_1[97]
 + c2.v[40]*MainFormSLS->hh_1[63]
 + c2.v[41]*MainFormSLS->hh_1[29]
 + c2.v[42]*MainFormSLS->hh_1[155]
 + c2.v[43]*MainFormSLS->hh_1[121]
 + c2.v[44]*MainFormSLS->hh_1[87]
 + c2.v[45]*MainFormSLS->hh_1[53]
 + c2.v[46]*MainFormSLS->hh_1[19]
 + c2.v[47]*MainFormSLS->hh_1[145]
 + c2.v[48]*MainFormSLS->hh_1[111]
 + c2.v[49]*MainFormSLS->hh_1[77]
 + c2.v[50]*MainFormSLS->hh_1[43]
 + c2.v[51]*MainFormSLS->hh_1[9]
 + c2.v[52]*MainFormSLS->hh_1[135]
 + c2.v[53]*MainFormSLS->hh_1[101]
 + c2.v[54]*MainFormSLS->hh_1[67]
 + c2.v[55]*MainFormSLS->hh_1[33]
 + c2.v[56]*MainFormSLS->hh_1[159]
 + c2.v[57]*MainFormSLS->hh_1[125]
 + c2.v[58]*MainFormSLS->hh_1[91]
 + c2.v[59]*MainFormSLS->hh_1[57]
 + c2.v[60]*MainFormSLS->hh_1[23]
 + c2.v[61]*MainFormSLS->hh_1[149]
 + c2.v[62]*MainFormSLS->hh_1[115]
 + c2.v[63]*MainFormSLS->hh_1[81]
 + c2.v[64]*MainFormSLS->hh_1[47]
 + c2.v[65]*MainFormSLS->hh_1[13]
 + c2.v[66]*MainFormSLS->hh_1[139]
 + c2.v[67]*MainFormSLS->hh_1[105]
 + c2.v[68]*MainFormSLS->hh_1[71]
 + c2.v[69]*MainFormSLS->hh_1[37]
 + c2.v[70]*MainFormSLS->hh_1[3]
 + c2.v[71]*MainFormSLS->hh_1[129]
 + c2.v[72]*MainFormSLS->hh_1[95]
 + c2.v[73]*MainFormSLS->hh_1[61]
 + c2.v[74]*MainFormSLS->hh_1[27]
 + c2.v[75]*MainFormSLS->hh_1[153]
 + c2.v[76]*MainFormSLS->hh_1[119]
 + c2.v[77]*MainFormSLS->hh_1[85]
 + c2.v[78]*MainFormSLS->hh_1[51]
 + c2.v[79]*MainFormSLS->hh_1[17];
s/=N_2;
out.push_back(s);
//������ 144
s =c2.v[0]*MainFormSLS->hh_1[144]
 + c2.v[1]*MainFormSLS->hh_1[112]
 + c2.v[2]*MainFormSLS->hh_1[80]
 + c2.v[3]*MainFormSLS->hh_1[48]
 + c2.v[4]*MainFormSLS->hh_1[16]
 + c2.v[5]*MainFormSLS->hh_1[144]
 + c2.v[6]*MainFormSLS->hh_1[112]
 + c2.v[7]*MainFormSLS->hh_1[80]
 + c2.v[8]*MainFormSLS->hh_1[48]
 + c2.v[9]*MainFormSLS->hh_1[16]
 + c2.v[10]*MainFormSLS->hh_1[144]
 + c2.v[11]*MainFormSLS->hh_1[112]
 + c2.v[12]*MainFormSLS->hh_1[80]
 + c2.v[13]*MainFormSLS->hh_1[48]
 + c2.v[14]*MainFormSLS->hh_1[16]
 + c2.v[15]*MainFormSLS->hh_1[144]
 + c2.v[16]*MainFormSLS->hh_1[112]
 + c2.v[17]*MainFormSLS->hh_1[80]
 + c2.v[18]*MainFormSLS->hh_1[48]
 + c2.v[19]*MainFormSLS->hh_1[16]
 + c2.v[20]*MainFormSLS->hh_1[144]
 + c2.v[21]*MainFormSLS->hh_1[112]
 + c2.v[22]*MainFormSLS->hh_1[80]
 + c2.v[23]*MainFormSLS->hh_1[48]
 + c2.v[24]*MainFormSLS->hh_1[16]
 + c2.v[25]*MainFormSLS->hh_1[144]
 + c2.v[26]*MainFormSLS->hh_1[112]
 + c2.v[27]*MainFormSLS->hh_1[80]
 + c2.v[28]*MainFormSLS->hh_1[48]
 + c2.v[29]*MainFormSLS->hh_1[16]
 + c2.v[30]*MainFormSLS->hh_1[144]
 + c2.v[31]*MainFormSLS->hh_1[112]
 + c2.v[32]*MainFormSLS->hh_1[80]
 + c2.v[33]*MainFormSLS->hh_1[48]
 + c2.v[34]*MainFormSLS->hh_1[16]
 + c2.v[35]*MainFormSLS->hh_1[144]
 + c2.v[36]*MainFormSLS->hh_1[112]
 + c2.v[37]*MainFormSLS->hh_1[80]
 + c2.v[38]*MainFormSLS->hh_1[48]
 + c2.v[39]*MainFormSLS->hh_1[16]
 + c2.v[40]*MainFormSLS->hh_1[144]
 + c2.v[41]*MainFormSLS->hh_1[112]
 + c2.v[42]*MainFormSLS->hh_1[80]
 + c2.v[43]*MainFormSLS->hh_1[48]
 + c2.v[44]*MainFormSLS->hh_1[16]
 + c2.v[45]*MainFormSLS->hh_1[144]
 + c2.v[46]*MainFormSLS->hh_1[112]
 + c2.v[47]*MainFormSLS->hh_1[80]
 + c2.v[48]*MainFormSLS->hh_1[48]
 + c2.v[49]*MainFormSLS->hh_1[16]
 + c2.v[50]*MainFormSLS->hh_1[144]
 + c2.v[51]*MainFormSLS->hh_1[112]
 + c2.v[52]*MainFormSLS->hh_1[80]
 + c2.v[53]*MainFormSLS->hh_1[48]
 + c2.v[54]*MainFormSLS->hh_1[16]
 + c2.v[55]*MainFormSLS->hh_1[144]
 + c2.v[56]*MainFormSLS->hh_1[112]
 + c2.v[57]*MainFormSLS->hh_1[80]
 + c2.v[58]*MainFormSLS->hh_1[48]
 + c2.v[59]*MainFormSLS->hh_1[16]
 + c2.v[60]*MainFormSLS->hh_1[144]
 + c2.v[61]*MainFormSLS->hh_1[112]
 + c2.v[62]*MainFormSLS->hh_1[80]
 + c2.v[63]*MainFormSLS->hh_1[48]
 + c2.v[64]*MainFormSLS->hh_1[16]
 + c2.v[65]*MainFormSLS->hh_1[144]
 + c2.v[66]*MainFormSLS->hh_1[112]
 + c2.v[67]*MainFormSLS->hh_1[80]
 + c2.v[68]*MainFormSLS->hh_1[48]
 + c2.v[69]*MainFormSLS->hh_1[16]
 + c2.v[70]*MainFormSLS->hh_1[144]
 + c2.v[71]*MainFormSLS->hh_1[112]
 + c2.v[72]*MainFormSLS->hh_1[80]
 + c2.v[73]*MainFormSLS->hh_1[48]
 + c2.v[74]*MainFormSLS->hh_1[16]
 + c2.v[75]*MainFormSLS->hh_1[144]
 + c2.v[76]*MainFormSLS->hh_1[112]
 + c2.v[77]*MainFormSLS->hh_1[80]
 + c2.v[78]*MainFormSLS->hh_1[48]
 + c2.v[79]*MainFormSLS->hh_1[16];
s/=N_2;
out.push_back(s);
//������ 145
s =c2.v[0]*MainFormSLS->hh_1[145]
 + c2.v[1]*MainFormSLS->hh_1[115]
 + c2.v[2]*MainFormSLS->hh_1[85]
 + c2.v[3]*MainFormSLS->hh_1[55]
 + c2.v[4]*MainFormSLS->hh_1[25]
 + c2.v[5]*MainFormSLS->hh_1[155]
 + c2.v[6]*MainFormSLS->hh_1[125]
 + c2.v[7]*MainFormSLS->hh_1[95]
 + c2.v[8]*MainFormSLS->hh_1[65]
 + c2.v[9]*MainFormSLS->hh_1[35]
 + c2.v[10]*MainFormSLS->hh_1[5]
 + c2.v[11]*MainFormSLS->hh_1[135]
 + c2.v[12]*MainFormSLS->hh_1[105]
 + c2.v[13]*MainFormSLS->hh_1[75]
 + c2.v[14]*MainFormSLS->hh_1[45]
 + c2.v[15]*MainFormSLS->hh_1[15]
 + c2.v[16]*MainFormSLS->hh_1[145]
 + c2.v[17]*MainFormSLS->hh_1[115]
 + c2.v[18]*MainFormSLS->hh_1[85]
 + c2.v[19]*MainFormSLS->hh_1[55]
 + c2.v[20]*MainFormSLS->hh_1[25]
 + c2.v[21]*MainFormSLS->hh_1[155]
 + c2.v[22]*MainFormSLS->hh_1[125]
 + c2.v[23]*MainFormSLS->hh_1[95]
 + c2.v[24]*MainFormSLS->hh_1[65]
 + c2.v[25]*MainFormSLS->hh_1[35]
 + c2.v[26]*MainFormSLS->hh_1[5]
 + c2.v[27]*MainFormSLS->hh_1[135]
 + c2.v[28]*MainFormSLS->hh_1[105]
 + c2.v[29]*MainFormSLS->hh_1[75]
 + c2.v[30]*MainFormSLS->hh_1[45]
 + c2.v[31]*MainFormSLS->hh_1[15]
 + c2.v[32]*MainFormSLS->hh_1[145]
 + c2.v[33]*MainFormSLS->hh_1[115]
 + c2.v[34]*MainFormSLS->hh_1[85]
 + c2.v[35]*MainFormSLS->hh_1[55]
 + c2.v[36]*MainFormSLS->hh_1[25]
 + c2.v[37]*MainFormSLS->hh_1[155]
 + c2.v[38]*MainFormSLS->hh_1[125]
 + c2.v[39]*MainFormSLS->hh_1[95]
 + c2.v[40]*MainFormSLS->hh_1[65]
 + c2.v[41]*MainFormSLS->hh_1[35]
 + c2.v[42]*MainFormSLS->hh_1[5]
 + c2.v[43]*MainFormSLS->hh_1[135]
 + c2.v[44]*MainFormSLS->hh_1[105]
 + c2.v[45]*MainFormSLS->hh_1[75]
 + c2.v[46]*MainFormSLS->hh_1[45]
 + c2.v[47]*MainFormSLS->hh_1[15]
 + c2.v[48]*MainFormSLS->hh_1[145]
 + c2.v[49]*MainFormSLS->hh_1[115]
 + c2.v[50]*MainFormSLS->hh_1[85]
 + c2.v[51]*MainFormSLS->hh_1[55]
 + c2.v[52]*MainFormSLS->hh_1[25]
 + c2.v[53]*MainFormSLS->hh_1[155]
 + c2.v[54]*MainFormSLS->hh_1[125]
 + c2.v[55]*MainFormSLS->hh_1[95]
 + c2.v[56]*MainFormSLS->hh_1[65]
 + c2.v[57]*MainFormSLS->hh_1[35]
 + c2.v[58]*MainFormSLS->hh_1[5]
 + c2.v[59]*MainFormSLS->hh_1[135]
 + c2.v[60]*MainFormSLS->hh_1[105]
 + c2.v[61]*MainFormSLS->hh_1[75]
 + c2.v[62]*MainFormSLS->hh_1[45]
 + c2.v[63]*MainFormSLS->hh_1[15]
 + c2.v[64]*MainFormSLS->hh_1[145]
 + c2.v[65]*MainFormSLS->hh_1[115]
 + c2.v[66]*MainFormSLS->hh_1[85]
 + c2.v[67]*MainFormSLS->hh_1[55]
 + c2.v[68]*MainFormSLS->hh_1[25]
 + c2.v[69]*MainFormSLS->hh_1[155]
 + c2.v[70]*MainFormSLS->hh_1[125]
 + c2.v[71]*MainFormSLS->hh_1[95]
 + c2.v[72]*MainFormSLS->hh_1[65]
 + c2.v[73]*MainFormSLS->hh_1[35]
 + c2.v[74]*MainFormSLS->hh_1[5]
 + c2.v[75]*MainFormSLS->hh_1[135]
 + c2.v[76]*MainFormSLS->hh_1[105]
 + c2.v[77]*MainFormSLS->hh_1[75]
 + c2.v[78]*MainFormSLS->hh_1[45]
 + c2.v[79]*MainFormSLS->hh_1[15];
s/=N_2;
out.push_back(s);
//������ 146
s =c2.v[0]*MainFormSLS->hh_1[146]
 + c2.v[1]*MainFormSLS->hh_1[118]
 + c2.v[2]*MainFormSLS->hh_1[90]
 + c2.v[3]*MainFormSLS->hh_1[62]
 + c2.v[4]*MainFormSLS->hh_1[34]
 + c2.v[5]*MainFormSLS->hh_1[6]
 + c2.v[6]*MainFormSLS->hh_1[138]
 + c2.v[7]*MainFormSLS->hh_1[110]
 + c2.v[8]*MainFormSLS->hh_1[82]
 + c2.v[9]*MainFormSLS->hh_1[54]
 + c2.v[10]*MainFormSLS->hh_1[26]
 + c2.v[11]*MainFormSLS->hh_1[158]
 + c2.v[12]*MainFormSLS->hh_1[130]
 + c2.v[13]*MainFormSLS->hh_1[102]
 + c2.v[14]*MainFormSLS->hh_1[74]
 + c2.v[15]*MainFormSLS->hh_1[46]
 + c2.v[16]*MainFormSLS->hh_1[18]
 + c2.v[17]*MainFormSLS->hh_1[150]
 + c2.v[18]*MainFormSLS->hh_1[122]
 + c2.v[19]*MainFormSLS->hh_1[94]
 + c2.v[20]*MainFormSLS->hh_1[66]
 + c2.v[21]*MainFormSLS->hh_1[38]
 + c2.v[22]*MainFormSLS->hh_1[10]
 + c2.v[23]*MainFormSLS->hh_1[142]
 + c2.v[24]*MainFormSLS->hh_1[114]
 + c2.v[25]*MainFormSLS->hh_1[86]
 + c2.v[26]*MainFormSLS->hh_1[58]
 + c2.v[27]*MainFormSLS->hh_1[30]
 + c2.v[28]*MainFormSLS->hh_1[2]
 + c2.v[29]*MainFormSLS->hh_1[134]
 + c2.v[30]*MainFormSLS->hh_1[106]
 + c2.v[31]*MainFormSLS->hh_1[78]
 + c2.v[32]*MainFormSLS->hh_1[50]
 + c2.v[33]*MainFormSLS->hh_1[22]
 + c2.v[34]*MainFormSLS->hh_1[154]
 + c2.v[35]*MainFormSLS->hh_1[126]
 + c2.v[36]*MainFormSLS->hh_1[98]
 + c2.v[37]*MainFormSLS->hh_1[70]
 + c2.v[38]*MainFormSLS->hh_1[42]
 + c2.v[39]*MainFormSLS->hh_1[14]
 + c2.v[40]*MainFormSLS->hh_1[146]
 + c2.v[41]*MainFormSLS->hh_1[118]
 + c2.v[42]*MainFormSLS->hh_1[90]
 + c2.v[43]*MainFormSLS->hh_1[62]
 + c2.v[44]*MainFormSLS->hh_1[34]
 + c2.v[45]*MainFormSLS->hh_1[6]
 + c2.v[46]*MainFormSLS->hh_1[138]
 + c2.v[47]*MainFormSLS->hh_1[110]
 + c2.v[48]*MainFormSLS->hh_1[82]
 + c2.v[49]*MainFormSLS->hh_1[54]
 + c2.v[50]*MainFormSLS->hh_1[26]
 + c2.v[51]*MainFormSLS->hh_1[158]
 + c2.v[52]*MainFormSLS->hh_1[130]
 + c2.v[53]*MainFormSLS->hh_1[102]
 + c2.v[54]*MainFormSLS->hh_1[74]
 + c2.v[55]*MainFormSLS->hh_1[46]
 + c2.v[56]*MainFormSLS->hh_1[18]
 + c2.v[57]*MainFormSLS->hh_1[150]
 + c2.v[58]*MainFormSLS->hh_1[122]
 + c2.v[59]*MainFormSLS->hh_1[94]
 + c2.v[60]*MainFormSLS->hh_1[66]
 + c2.v[61]*MainFormSLS->hh_1[38]
 + c2.v[62]*MainFormSLS->hh_1[10]
 + c2.v[63]*MainFormSLS->hh_1[142]
 + c2.v[64]*MainFormSLS->hh_1[114]
 + c2.v[65]*MainFormSLS->hh_1[86]
 + c2.v[66]*MainFormSLS->hh_1[58]
 + c2.v[67]*MainFormSLS->hh_1[30]
 + c2.v[68]*MainFormSLS->hh_1[2]
 + c2.v[69]*MainFormSLS->hh_1[134]
 + c2.v[70]*MainFormSLS->hh_1[106]
 + c2.v[71]*MainFormSLS->hh_1[78]
 + c2.v[72]*MainFormSLS->hh_1[50]
 + c2.v[73]*MainFormSLS->hh_1[22]
 + c2.v[74]*MainFormSLS->hh_1[154]
 + c2.v[75]*MainFormSLS->hh_1[126]
 + c2.v[76]*MainFormSLS->hh_1[98]
 + c2.v[77]*MainFormSLS->hh_1[70]
 + c2.v[78]*MainFormSLS->hh_1[42]
 + c2.v[79]*MainFormSLS->hh_1[14];
s/=N_2;
out.push_back(s);
//������ 147
s =c2.v[0]*MainFormSLS->hh_1[147]
 + c2.v[1]*MainFormSLS->hh_1[121]
 + c2.v[2]*MainFormSLS->hh_1[95]
 + c2.v[3]*MainFormSLS->hh_1[69]
 + c2.v[4]*MainFormSLS->hh_1[43]
 + c2.v[5]*MainFormSLS->hh_1[17]
 + c2.v[6]*MainFormSLS->hh_1[151]
 + c2.v[7]*MainFormSLS->hh_1[125]
 + c2.v[8]*MainFormSLS->hh_1[99]
 + c2.v[9]*MainFormSLS->hh_1[73]
 + c2.v[10]*MainFormSLS->hh_1[47]
 + c2.v[11]*MainFormSLS->hh_1[21]
 + c2.v[12]*MainFormSLS->hh_1[155]
 + c2.v[13]*MainFormSLS->hh_1[129]
 + c2.v[14]*MainFormSLS->hh_1[103]
 + c2.v[15]*MainFormSLS->hh_1[77]
 + c2.v[16]*MainFormSLS->hh_1[51]
 + c2.v[17]*MainFormSLS->hh_1[25]
 + c2.v[18]*MainFormSLS->hh_1[159]
 + c2.v[19]*MainFormSLS->hh_1[133]
 + c2.v[20]*MainFormSLS->hh_1[107]
 + c2.v[21]*MainFormSLS->hh_1[81]
 + c2.v[22]*MainFormSLS->hh_1[55]
 + c2.v[23]*MainFormSLS->hh_1[29]
 + c2.v[24]*MainFormSLS->hh_1[3]
 + c2.v[25]*MainFormSLS->hh_1[137]
 + c2.v[26]*MainFormSLS->hh_1[111]
 + c2.v[27]*MainFormSLS->hh_1[85]
 + c2.v[28]*MainFormSLS->hh_1[59]
 + c2.v[29]*MainFormSLS->hh_1[33]
 + c2.v[30]*MainFormSLS->hh_1[7]
 + c2.v[31]*MainFormSLS->hh_1[141]
 + c2.v[32]*MainFormSLS->hh_1[115]
 + c2.v[33]*MainFormSLS->hh_1[89]
 + c2.v[34]*MainFormSLS->hh_1[63]
 + c2.v[35]*MainFormSLS->hh_1[37]
 + c2.v[36]*MainFormSLS->hh_1[11]
 + c2.v[37]*MainFormSLS->hh_1[145]
 + c2.v[38]*MainFormSLS->hh_1[119]
 + c2.v[39]*MainFormSLS->hh_1[93]
 + c2.v[40]*MainFormSLS->hh_1[67]
 + c2.v[41]*MainFormSLS->hh_1[41]
 + c2.v[42]*MainFormSLS->hh_1[15]
 + c2.v[43]*MainFormSLS->hh_1[149]
 + c2.v[44]*MainFormSLS->hh_1[123]
 + c2.v[45]*MainFormSLS->hh_1[97]
 + c2.v[46]*MainFormSLS->hh_1[71]
 + c2.v[47]*MainFormSLS->hh_1[45]
 + c2.v[48]*MainFormSLS->hh_1[19]
 + c2.v[49]*MainFormSLS->hh_1[153]
 + c2.v[50]*MainFormSLS->hh_1[127]
 + c2.v[51]*MainFormSLS->hh_1[101]
 + c2.v[52]*MainFormSLS->hh_1[75]
 + c2.v[53]*MainFormSLS->hh_1[49]
 + c2.v[54]*MainFormSLS->hh_1[23]
 + c2.v[55]*MainFormSLS->hh_1[157]
 + c2.v[56]*MainFormSLS->hh_1[131]
 + c2.v[57]*MainFormSLS->hh_1[105]
 + c2.v[58]*MainFormSLS->hh_1[79]
 + c2.v[59]*MainFormSLS->hh_1[53]
 + c2.v[60]*MainFormSLS->hh_1[27]
 + c2.v[61]*MainFormSLS->hh_1[1]
 + c2.v[62]*MainFormSLS->hh_1[135]
 + c2.v[63]*MainFormSLS->hh_1[109]
 + c2.v[64]*MainFormSLS->hh_1[83]
 + c2.v[65]*MainFormSLS->hh_1[57]
 + c2.v[66]*MainFormSLS->hh_1[31]
 + c2.v[67]*MainFormSLS->hh_1[5]
 + c2.v[68]*MainFormSLS->hh_1[139]
 + c2.v[69]*MainFormSLS->hh_1[113]
 + c2.v[70]*MainFormSLS->hh_1[87]
 + c2.v[71]*MainFormSLS->hh_1[61]
 + c2.v[72]*MainFormSLS->hh_1[35]
 + c2.v[73]*MainFormSLS->hh_1[9]
 + c2.v[74]*MainFormSLS->hh_1[143]
 + c2.v[75]*MainFormSLS->hh_1[117]
 + c2.v[76]*MainFormSLS->hh_1[91]
 + c2.v[77]*MainFormSLS->hh_1[65]
 + c2.v[78]*MainFormSLS->hh_1[39]
 + c2.v[79]*MainFormSLS->hh_1[13];
s/=N_2;
out.push_back(s);
//������ 148
s =c2.v[0]*MainFormSLS->hh_1[148]
 + c2.v[1]*MainFormSLS->hh_1[124]
 + c2.v[2]*MainFormSLS->hh_1[100]
 + c2.v[3]*MainFormSLS->hh_1[76]
 + c2.v[4]*MainFormSLS->hh_1[52]
 + c2.v[5]*MainFormSLS->hh_1[28]
 + c2.v[6]*MainFormSLS->hh_1[4]
 + c2.v[7]*MainFormSLS->hh_1[140]
 + c2.v[8]*MainFormSLS->hh_1[116]
 + c2.v[9]*MainFormSLS->hh_1[92]
 + c2.v[10]*MainFormSLS->hh_1[68]
 + c2.v[11]*MainFormSLS->hh_1[44]
 + c2.v[12]*MainFormSLS->hh_1[20]
 + c2.v[13]*MainFormSLS->hh_1[156]
 + c2.v[14]*MainFormSLS->hh_1[132]
 + c2.v[15]*MainFormSLS->hh_1[108]
 + c2.v[16]*MainFormSLS->hh_1[84]
 + c2.v[17]*MainFormSLS->hh_1[60]
 + c2.v[18]*MainFormSLS->hh_1[36]
 + c2.v[19]*MainFormSLS->hh_1[12]
 + c2.v[20]*MainFormSLS->hh_1[148]
 + c2.v[21]*MainFormSLS->hh_1[124]
 + c2.v[22]*MainFormSLS->hh_1[100]
 + c2.v[23]*MainFormSLS->hh_1[76]
 + c2.v[24]*MainFormSLS->hh_1[52]
 + c2.v[25]*MainFormSLS->hh_1[28]
 + c2.v[26]*MainFormSLS->hh_1[4]
 + c2.v[27]*MainFormSLS->hh_1[140]
 + c2.v[28]*MainFormSLS->hh_1[116]
 + c2.v[29]*MainFormSLS->hh_1[92]
 + c2.v[30]*MainFormSLS->hh_1[68]
 + c2.v[31]*MainFormSLS->hh_1[44]
 + c2.v[32]*MainFormSLS->hh_1[20]
 + c2.v[33]*MainFormSLS->hh_1[156]
 + c2.v[34]*MainFormSLS->hh_1[132]
 + c2.v[35]*MainFormSLS->hh_1[108]
 + c2.v[36]*MainFormSLS->hh_1[84]
 + c2.v[37]*MainFormSLS->hh_1[60]
 + c2.v[38]*MainFormSLS->hh_1[36]
 + c2.v[39]*MainFormSLS->hh_1[12]
 + c2.v[40]*MainFormSLS->hh_1[148]
 + c2.v[41]*MainFormSLS->hh_1[124]
 + c2.v[42]*MainFormSLS->hh_1[100]
 + c2.v[43]*MainFormSLS->hh_1[76]
 + c2.v[44]*MainFormSLS->hh_1[52]
 + c2.v[45]*MainFormSLS->hh_1[28]
 + c2.v[46]*MainFormSLS->hh_1[4]
 + c2.v[47]*MainFormSLS->hh_1[140]
 + c2.v[48]*MainFormSLS->hh_1[116]
 + c2.v[49]*MainFormSLS->hh_1[92]
 + c2.v[50]*MainFormSLS->hh_1[68]
 + c2.v[51]*MainFormSLS->hh_1[44]
 + c2.v[52]*MainFormSLS->hh_1[20]
 + c2.v[53]*MainFormSLS->hh_1[156]
 + c2.v[54]*MainFormSLS->hh_1[132]
 + c2.v[55]*MainFormSLS->hh_1[108]
 + c2.v[56]*MainFormSLS->hh_1[84]
 + c2.v[57]*MainFormSLS->hh_1[60]
 + c2.v[58]*MainFormSLS->hh_1[36]
 + c2.v[59]*MainFormSLS->hh_1[12]
 + c2.v[60]*MainFormSLS->hh_1[148]
 + c2.v[61]*MainFormSLS->hh_1[124]
 + c2.v[62]*MainFormSLS->hh_1[100]
 + c2.v[63]*MainFormSLS->hh_1[76]
 + c2.v[64]*MainFormSLS->hh_1[52]
 + c2.v[65]*MainFormSLS->hh_1[28]
 + c2.v[66]*MainFormSLS->hh_1[4]
 + c2.v[67]*MainFormSLS->hh_1[140]
 + c2.v[68]*MainFormSLS->hh_1[116]
 + c2.v[69]*MainFormSLS->hh_1[92]
 + c2.v[70]*MainFormSLS->hh_1[68]
 + c2.v[71]*MainFormSLS->hh_1[44]
 + c2.v[72]*MainFormSLS->hh_1[20]
 + c2.v[73]*MainFormSLS->hh_1[156]
 + c2.v[74]*MainFormSLS->hh_1[132]
 + c2.v[75]*MainFormSLS->hh_1[108]
 + c2.v[76]*MainFormSLS->hh_1[84]
 + c2.v[77]*MainFormSLS->hh_1[60]
 + c2.v[78]*MainFormSLS->hh_1[36]
 + c2.v[79]*MainFormSLS->hh_1[12];
s/=N_2;
out.push_back(s);
//������ 149
s =c2.v[0]*MainFormSLS->hh_1[149]
 + c2.v[1]*MainFormSLS->hh_1[127]
 + c2.v[2]*MainFormSLS->hh_1[105]
 + c2.v[3]*MainFormSLS->hh_1[83]
 + c2.v[4]*MainFormSLS->hh_1[61]
 + c2.v[5]*MainFormSLS->hh_1[39]
 + c2.v[6]*MainFormSLS->hh_1[17]
 + c2.v[7]*MainFormSLS->hh_1[155]
 + c2.v[8]*MainFormSLS->hh_1[133]
 + c2.v[9]*MainFormSLS->hh_1[111]
 + c2.v[10]*MainFormSLS->hh_1[89]
 + c2.v[11]*MainFormSLS->hh_1[67]
 + c2.v[12]*MainFormSLS->hh_1[45]
 + c2.v[13]*MainFormSLS->hh_1[23]
 + c2.v[14]*MainFormSLS->hh_1[1]
 + c2.v[15]*MainFormSLS->hh_1[139]
 + c2.v[16]*MainFormSLS->hh_1[117]
 + c2.v[17]*MainFormSLS->hh_1[95]
 + c2.v[18]*MainFormSLS->hh_1[73]
 + c2.v[19]*MainFormSLS->hh_1[51]
 + c2.v[20]*MainFormSLS->hh_1[29]
 + c2.v[21]*MainFormSLS->hh_1[7]
 + c2.v[22]*MainFormSLS->hh_1[145]
 + c2.v[23]*MainFormSLS->hh_1[123]
 + c2.v[24]*MainFormSLS->hh_1[101]
 + c2.v[25]*MainFormSLS->hh_1[79]
 + c2.v[26]*MainFormSLS->hh_1[57]
 + c2.v[27]*MainFormSLS->hh_1[35]
 + c2.v[28]*MainFormSLS->hh_1[13]
 + c2.v[29]*MainFormSLS->hh_1[151]
 + c2.v[30]*MainFormSLS->hh_1[129]
 + c2.v[31]*MainFormSLS->hh_1[107]
 + c2.v[32]*MainFormSLS->hh_1[85]
 + c2.v[33]*MainFormSLS->hh_1[63]
 + c2.v[34]*MainFormSLS->hh_1[41]
 + c2.v[35]*MainFormSLS->hh_1[19]
 + c2.v[36]*MainFormSLS->hh_1[157]
 + c2.v[37]*MainFormSLS->hh_1[135]
 + c2.v[38]*MainFormSLS->hh_1[113]
 + c2.v[39]*MainFormSLS->hh_1[91]
 + c2.v[40]*MainFormSLS->hh_1[69]
 + c2.v[41]*MainFormSLS->hh_1[47]
 + c2.v[42]*MainFormSLS->hh_1[25]
 + c2.v[43]*MainFormSLS->hh_1[3]
 + c2.v[44]*MainFormSLS->hh_1[141]
 + c2.v[45]*MainFormSLS->hh_1[119]
 + c2.v[46]*MainFormSLS->hh_1[97]
 + c2.v[47]*MainFormSLS->hh_1[75]
 + c2.v[48]*MainFormSLS->hh_1[53]
 + c2.v[49]*MainFormSLS->hh_1[31]
 + c2.v[50]*MainFormSLS->hh_1[9]
 + c2.v[51]*MainFormSLS->hh_1[147]
 + c2.v[52]*MainFormSLS->hh_1[125]
 + c2.v[53]*MainFormSLS->hh_1[103]
 + c2.v[54]*MainFormSLS->hh_1[81]
 + c2.v[55]*MainFormSLS->hh_1[59]
 + c2.v[56]*MainFormSLS->hh_1[37]
 + c2.v[57]*MainFormSLS->hh_1[15]
 + c2.v[58]*MainFormSLS->hh_1[153]
 + c2.v[59]*MainFormSLS->hh_1[131]
 + c2.v[60]*MainFormSLS->hh_1[109]
 + c2.v[61]*MainFormSLS->hh_1[87]
 + c2.v[62]*MainFormSLS->hh_1[65]
 + c2.v[63]*MainFormSLS->hh_1[43]
 + c2.v[64]*MainFormSLS->hh_1[21]
 + c2.v[65]*MainFormSLS->hh_1[159]
 + c2.v[66]*MainFormSLS->hh_1[137]
 + c2.v[67]*MainFormSLS->hh_1[115]
 + c2.v[68]*MainFormSLS->hh_1[93]
 + c2.v[69]*MainFormSLS->hh_1[71]
 + c2.v[70]*MainFormSLS->hh_1[49]
 + c2.v[71]*MainFormSLS->hh_1[27]
 + c2.v[72]*MainFormSLS->hh_1[5]
 + c2.v[73]*MainFormSLS->hh_1[143]
 + c2.v[74]*MainFormSLS->hh_1[121]
 + c2.v[75]*MainFormSLS->hh_1[99]
 + c2.v[76]*MainFormSLS->hh_1[77]
 + c2.v[77]*MainFormSLS->hh_1[55]
 + c2.v[78]*MainFormSLS->hh_1[33]
 + c2.v[79]*MainFormSLS->hh_1[11];
s/=N_2;
out.push_back(s);
//������ 150
s =c2.v[0]*MainFormSLS->hh_1[150]
 + c2.v[1]*MainFormSLS->hh_1[130]
 + c2.v[2]*MainFormSLS->hh_1[110]
 + c2.v[3]*MainFormSLS->hh_1[90]
 + c2.v[4]*MainFormSLS->hh_1[70]
 + c2.v[5]*MainFormSLS->hh_1[50]
 + c2.v[6]*MainFormSLS->hh_1[30]
 + c2.v[7]*MainFormSLS->hh_1[10]
 + c2.v[8]*MainFormSLS->hh_1[150]
 + c2.v[9]*MainFormSLS->hh_1[130]
 + c2.v[10]*MainFormSLS->hh_1[110]
 + c2.v[11]*MainFormSLS->hh_1[90]
 + c2.v[12]*MainFormSLS->hh_1[70]
 + c2.v[13]*MainFormSLS->hh_1[50]
 + c2.v[14]*MainFormSLS->hh_1[30]
 + c2.v[15]*MainFormSLS->hh_1[10]
 + c2.v[16]*MainFormSLS->hh_1[150]
 + c2.v[17]*MainFormSLS->hh_1[130]
 + c2.v[18]*MainFormSLS->hh_1[110]
 + c2.v[19]*MainFormSLS->hh_1[90]
 + c2.v[20]*MainFormSLS->hh_1[70]
 + c2.v[21]*MainFormSLS->hh_1[50]
 + c2.v[22]*MainFormSLS->hh_1[30]
 + c2.v[23]*MainFormSLS->hh_1[10]
 + c2.v[24]*MainFormSLS->hh_1[150]
 + c2.v[25]*MainFormSLS->hh_1[130]
 + c2.v[26]*MainFormSLS->hh_1[110]
 + c2.v[27]*MainFormSLS->hh_1[90]
 + c2.v[28]*MainFormSLS->hh_1[70]
 + c2.v[29]*MainFormSLS->hh_1[50]
 + c2.v[30]*MainFormSLS->hh_1[30]
 + c2.v[31]*MainFormSLS->hh_1[10]
 + c2.v[32]*MainFormSLS->hh_1[150]
 + c2.v[33]*MainFormSLS->hh_1[130]
 + c2.v[34]*MainFormSLS->hh_1[110]
 + c2.v[35]*MainFormSLS->hh_1[90]
 + c2.v[36]*MainFormSLS->hh_1[70]
 + c2.v[37]*MainFormSLS->hh_1[50]
 + c2.v[38]*MainFormSLS->hh_1[30]
 + c2.v[39]*MainFormSLS->hh_1[10]
 + c2.v[40]*MainFormSLS->hh_1[150]
 + c2.v[41]*MainFormSLS->hh_1[130]
 + c2.v[42]*MainFormSLS->hh_1[110]
 + c2.v[43]*MainFormSLS->hh_1[90]
 + c2.v[44]*MainFormSLS->hh_1[70]
 + c2.v[45]*MainFormSLS->hh_1[50]
 + c2.v[46]*MainFormSLS->hh_1[30]
 + c2.v[47]*MainFormSLS->hh_1[10]
 + c2.v[48]*MainFormSLS->hh_1[150]
 + c2.v[49]*MainFormSLS->hh_1[130]
 + c2.v[50]*MainFormSLS->hh_1[110]
 + c2.v[51]*MainFormSLS->hh_1[90]
 + c2.v[52]*MainFormSLS->hh_1[70]
 + c2.v[53]*MainFormSLS->hh_1[50]
 + c2.v[54]*MainFormSLS->hh_1[30]
 + c2.v[55]*MainFormSLS->hh_1[10]
 + c2.v[56]*MainFormSLS->hh_1[150]
 + c2.v[57]*MainFormSLS->hh_1[130]
 + c2.v[58]*MainFormSLS->hh_1[110]
 + c2.v[59]*MainFormSLS->hh_1[90]
 + c2.v[60]*MainFormSLS->hh_1[70]
 + c2.v[61]*MainFormSLS->hh_1[50]
 + c2.v[62]*MainFormSLS->hh_1[30]
 + c2.v[63]*MainFormSLS->hh_1[10]
 + c2.v[64]*MainFormSLS->hh_1[150]
 + c2.v[65]*MainFormSLS->hh_1[130]
 + c2.v[66]*MainFormSLS->hh_1[110]
 + c2.v[67]*MainFormSLS->hh_1[90]
 + c2.v[68]*MainFormSLS->hh_1[70]
 + c2.v[69]*MainFormSLS->hh_1[50]
 + c2.v[70]*MainFormSLS->hh_1[30]
 + c2.v[71]*MainFormSLS->hh_1[10]
 + c2.v[72]*MainFormSLS->hh_1[150]
 + c2.v[73]*MainFormSLS->hh_1[130]
 + c2.v[74]*MainFormSLS->hh_1[110]
 + c2.v[75]*MainFormSLS->hh_1[90]
 + c2.v[76]*MainFormSLS->hh_1[70]
 + c2.v[77]*MainFormSLS->hh_1[50]
 + c2.v[78]*MainFormSLS->hh_1[30]
 + c2.v[79]*MainFormSLS->hh_1[10];
s/=N_2;
out.push_back(s);
//������ 151
s =c2.v[0]*MainFormSLS->hh_1[151]
 + c2.v[1]*MainFormSLS->hh_1[133]
 + c2.v[2]*MainFormSLS->hh_1[115]
 + c2.v[3]*MainFormSLS->hh_1[97]
 + c2.v[4]*MainFormSLS->hh_1[79]
 + c2.v[5]*MainFormSLS->hh_1[61]
 + c2.v[6]*MainFormSLS->hh_1[43]
 + c2.v[7]*MainFormSLS->hh_1[25]
 + c2.v[8]*MainFormSLS->hh_1[7]
 + c2.v[9]*MainFormSLS->hh_1[149]
 + c2.v[10]*MainFormSLS->hh_1[131]
 + c2.v[11]*MainFormSLS->hh_1[113]
 + c2.v[12]*MainFormSLS->hh_1[95]
 + c2.v[13]*MainFormSLS->hh_1[77]
 + c2.v[14]*MainFormSLS->hh_1[59]
 + c2.v[15]*MainFormSLS->hh_1[41]
 + c2.v[16]*MainFormSLS->hh_1[23]
 + c2.v[17]*MainFormSLS->hh_1[5]
 + c2.v[18]*MainFormSLS->hh_1[147]
 + c2.v[19]*MainFormSLS->hh_1[129]
 + c2.v[20]*MainFormSLS->hh_1[111]
 + c2.v[21]*MainFormSLS->hh_1[93]
 + c2.v[22]*MainFormSLS->hh_1[75]
 + c2.v[23]*MainFormSLS->hh_1[57]
 + c2.v[24]*MainFormSLS->hh_1[39]
 + c2.v[25]*MainFormSLS->hh_1[21]
 + c2.v[26]*MainFormSLS->hh_1[3]
 + c2.v[27]*MainFormSLS->hh_1[145]
 + c2.v[28]*MainFormSLS->hh_1[127]
 + c2.v[29]*MainFormSLS->hh_1[109]
 + c2.v[30]*MainFormSLS->hh_1[91]
 + c2.v[31]*MainFormSLS->hh_1[73]
 + c2.v[32]*MainFormSLS->hh_1[55]
 + c2.v[33]*MainFormSLS->hh_1[37]
 + c2.v[34]*MainFormSLS->hh_1[19]
 + c2.v[35]*MainFormSLS->hh_1[1]
 + c2.v[36]*MainFormSLS->hh_1[143]
 + c2.v[37]*MainFormSLS->hh_1[125]
 + c2.v[38]*MainFormSLS->hh_1[107]
 + c2.v[39]*MainFormSLS->hh_1[89]
 + c2.v[40]*MainFormSLS->hh_1[71]
 + c2.v[41]*MainFormSLS->hh_1[53]
 + c2.v[42]*MainFormSLS->hh_1[35]
 + c2.v[43]*MainFormSLS->hh_1[17]
 + c2.v[44]*MainFormSLS->hh_1[159]
 + c2.v[45]*MainFormSLS->hh_1[141]
 + c2.v[46]*MainFormSLS->hh_1[123]
 + c2.v[47]*MainFormSLS->hh_1[105]
 + c2.v[48]*MainFormSLS->hh_1[87]
 + c2.v[49]*MainFormSLS->hh_1[69]
 + c2.v[50]*MainFormSLS->hh_1[51]
 + c2.v[51]*MainFormSLS->hh_1[33]
 + c2.v[52]*MainFormSLS->hh_1[15]
 + c2.v[53]*MainFormSLS->hh_1[157]
 + c2.v[54]*MainFormSLS->hh_1[139]
 + c2.v[55]*MainFormSLS->hh_1[121]
 + c2.v[56]*MainFormSLS->hh_1[103]
 + c2.v[57]*MainFormSLS->hh_1[85]
 + c2.v[58]*MainFormSLS->hh_1[67]
 + c2.v[59]*MainFormSLS->hh_1[49]
 + c2.v[60]*MainFormSLS->hh_1[31]
 + c2.v[61]*MainFormSLS->hh_1[13]
 + c2.v[62]*MainFormSLS->hh_1[155]
 + c2.v[63]*MainFormSLS->hh_1[137]
 + c2.v[64]*MainFormSLS->hh_1[119]
 + c2.v[65]*MainFormSLS->hh_1[101]
 + c2.v[66]*MainFormSLS->hh_1[83]
 + c2.v[67]*MainFormSLS->hh_1[65]
 + c2.v[68]*MainFormSLS->hh_1[47]
 + c2.v[69]*MainFormSLS->hh_1[29]
 + c2.v[70]*MainFormSLS->hh_1[11]
 + c2.v[71]*MainFormSLS->hh_1[153]
 + c2.v[72]*MainFormSLS->hh_1[135]
 + c2.v[73]*MainFormSLS->hh_1[117]
 + c2.v[74]*MainFormSLS->hh_1[99]
 + c2.v[75]*MainFormSLS->hh_1[81]
 + c2.v[76]*MainFormSLS->hh_1[63]
 + c2.v[77]*MainFormSLS->hh_1[45]
 + c2.v[78]*MainFormSLS->hh_1[27]
 + c2.v[79]*MainFormSLS->hh_1[9];
s/=N_2;
out.push_back(s);
//������ 152
s =c2.v[0]*MainFormSLS->hh_1[152]
 + c2.v[1]*MainFormSLS->hh_1[136]
 + c2.v[2]*MainFormSLS->hh_1[120]
 + c2.v[3]*MainFormSLS->hh_1[104]
 + c2.v[4]*MainFormSLS->hh_1[88]
 + c2.v[5]*MainFormSLS->hh_1[72]
 + c2.v[6]*MainFormSLS->hh_1[56]
 + c2.v[7]*MainFormSLS->hh_1[40]
 + c2.v[8]*MainFormSLS->hh_1[24]
 + c2.v[9]*MainFormSLS->hh_1[8]
 + c2.v[10]*MainFormSLS->hh_1[152]
 + c2.v[11]*MainFormSLS->hh_1[136]
 + c2.v[12]*MainFormSLS->hh_1[120]
 + c2.v[13]*MainFormSLS->hh_1[104]
 + c2.v[14]*MainFormSLS->hh_1[88]
 + c2.v[15]*MainFormSLS->hh_1[72]
 + c2.v[16]*MainFormSLS->hh_1[56]
 + c2.v[17]*MainFormSLS->hh_1[40]
 + c2.v[18]*MainFormSLS->hh_1[24]
 + c2.v[19]*MainFormSLS->hh_1[8]
 + c2.v[20]*MainFormSLS->hh_1[152]
 + c2.v[21]*MainFormSLS->hh_1[136]
 + c2.v[22]*MainFormSLS->hh_1[120]
 + c2.v[23]*MainFormSLS->hh_1[104]
 + c2.v[24]*MainFormSLS->hh_1[88]
 + c2.v[25]*MainFormSLS->hh_1[72]
 + c2.v[26]*MainFormSLS->hh_1[56]
 + c2.v[27]*MainFormSLS->hh_1[40]
 + c2.v[28]*MainFormSLS->hh_1[24]
 + c2.v[29]*MainFormSLS->hh_1[8]
 + c2.v[30]*MainFormSLS->hh_1[152]
 + c2.v[31]*MainFormSLS->hh_1[136]
 + c2.v[32]*MainFormSLS->hh_1[120]
 + c2.v[33]*MainFormSLS->hh_1[104]
 + c2.v[34]*MainFormSLS->hh_1[88]
 + c2.v[35]*MainFormSLS->hh_1[72]
 + c2.v[36]*MainFormSLS->hh_1[56]
 + c2.v[37]*MainFormSLS->hh_1[40]
 + c2.v[38]*MainFormSLS->hh_1[24]
 + c2.v[39]*MainFormSLS->hh_1[8]
 + c2.v[40]*MainFormSLS->hh_1[152]
 + c2.v[41]*MainFormSLS->hh_1[136]
 + c2.v[42]*MainFormSLS->hh_1[120]
 + c2.v[43]*MainFormSLS->hh_1[104]
 + c2.v[44]*MainFormSLS->hh_1[88]
 + c2.v[45]*MainFormSLS->hh_1[72]
 + c2.v[46]*MainFormSLS->hh_1[56]
 + c2.v[47]*MainFormSLS->hh_1[40]
 + c2.v[48]*MainFormSLS->hh_1[24]
 + c2.v[49]*MainFormSLS->hh_1[8]
 + c2.v[50]*MainFormSLS->hh_1[152]
 + c2.v[51]*MainFormSLS->hh_1[136]
 + c2.v[52]*MainFormSLS->hh_1[120]
 + c2.v[53]*MainFormSLS->hh_1[104]
 + c2.v[54]*MainFormSLS->hh_1[88]
 + c2.v[55]*MainFormSLS->hh_1[72]
 + c2.v[56]*MainFormSLS->hh_1[56]
 + c2.v[57]*MainFormSLS->hh_1[40]
 + c2.v[58]*MainFormSLS->hh_1[24]
 + c2.v[59]*MainFormSLS->hh_1[8]
 + c2.v[60]*MainFormSLS->hh_1[152]
 + c2.v[61]*MainFormSLS->hh_1[136]
 + c2.v[62]*MainFormSLS->hh_1[120]
 + c2.v[63]*MainFormSLS->hh_1[104]
 + c2.v[64]*MainFormSLS->hh_1[88]
 + c2.v[65]*MainFormSLS->hh_1[72]
 + c2.v[66]*MainFormSLS->hh_1[56]
 + c2.v[67]*MainFormSLS->hh_1[40]
 + c2.v[68]*MainFormSLS->hh_1[24]
 + c2.v[69]*MainFormSLS->hh_1[8]
 + c2.v[70]*MainFormSLS->hh_1[152]
 + c2.v[71]*MainFormSLS->hh_1[136]
 + c2.v[72]*MainFormSLS->hh_1[120]
 + c2.v[73]*MainFormSLS->hh_1[104]
 + c2.v[74]*MainFormSLS->hh_1[88]
 + c2.v[75]*MainFormSLS->hh_1[72]
 + c2.v[76]*MainFormSLS->hh_1[56]
 + c2.v[77]*MainFormSLS->hh_1[40]
 + c2.v[78]*MainFormSLS->hh_1[24]
 + c2.v[79]*MainFormSLS->hh_1[8];
s/=N_2;
out.push_back(s);
//������ 153
s =c2.v[0]*MainFormSLS->hh_1[153]
 + c2.v[1]*MainFormSLS->hh_1[139]
 + c2.v[2]*MainFormSLS->hh_1[125]
 + c2.v[3]*MainFormSLS->hh_1[111]
 + c2.v[4]*MainFormSLS->hh_1[97]
 + c2.v[5]*MainFormSLS->hh_1[83]
 + c2.v[6]*MainFormSLS->hh_1[69]
 + c2.v[7]*MainFormSLS->hh_1[55]
 + c2.v[8]*MainFormSLS->hh_1[41]
 + c2.v[9]*MainFormSLS->hh_1[27]
 + c2.v[10]*MainFormSLS->hh_1[13]
 + c2.v[11]*MainFormSLS->hh_1[159]
 + c2.v[12]*MainFormSLS->hh_1[145]
 + c2.v[13]*MainFormSLS->hh_1[131]
 + c2.v[14]*MainFormSLS->hh_1[117]
 + c2.v[15]*MainFormSLS->hh_1[103]
 + c2.v[16]*MainFormSLS->hh_1[89]
 + c2.v[17]*MainFormSLS->hh_1[75]
 + c2.v[18]*MainFormSLS->hh_1[61]
 + c2.v[19]*MainFormSLS->hh_1[47]
 + c2.v[20]*MainFormSLS->hh_1[33]
 + c2.v[21]*MainFormSLS->hh_1[19]
 + c2.v[22]*MainFormSLS->hh_1[5]
 + c2.v[23]*MainFormSLS->hh_1[151]
 + c2.v[24]*MainFormSLS->hh_1[137]
 + c2.v[25]*MainFormSLS->hh_1[123]
 + c2.v[26]*MainFormSLS->hh_1[109]
 + c2.v[27]*MainFormSLS->hh_1[95]
 + c2.v[28]*MainFormSLS->hh_1[81]
 + c2.v[29]*MainFormSLS->hh_1[67]
 + c2.v[30]*MainFormSLS->hh_1[53]
 + c2.v[31]*MainFormSLS->hh_1[39]
 + c2.v[32]*MainFormSLS->hh_1[25]
 + c2.v[33]*MainFormSLS->hh_1[11]
 + c2.v[34]*MainFormSLS->hh_1[157]
 + c2.v[35]*MainFormSLS->hh_1[143]
 + c2.v[36]*MainFormSLS->hh_1[129]
 + c2.v[37]*MainFormSLS->hh_1[115]
 + c2.v[38]*MainFormSLS->hh_1[101]
 + c2.v[39]*MainFormSLS->hh_1[87]
 + c2.v[40]*MainFormSLS->hh_1[73]
 + c2.v[41]*MainFormSLS->hh_1[59]
 + c2.v[42]*MainFormSLS->hh_1[45]
 + c2.v[43]*MainFormSLS->hh_1[31]
 + c2.v[44]*MainFormSLS->hh_1[17]
 + c2.v[45]*MainFormSLS->hh_1[3]
 + c2.v[46]*MainFormSLS->hh_1[149]
 + c2.v[47]*MainFormSLS->hh_1[135]
 + c2.v[48]*MainFormSLS->hh_1[121]
 + c2.v[49]*MainFormSLS->hh_1[107]
 + c2.v[50]*MainFormSLS->hh_1[93]
 + c2.v[51]*MainFormSLS->hh_1[79]
 + c2.v[52]*MainFormSLS->hh_1[65]
 + c2.v[53]*MainFormSLS->hh_1[51]
 + c2.v[54]*MainFormSLS->hh_1[37]
 + c2.v[55]*MainFormSLS->hh_1[23]
 + c2.v[56]*MainFormSLS->hh_1[9]
 + c2.v[57]*MainFormSLS->hh_1[155]
 + c2.v[58]*MainFormSLS->hh_1[141]
 + c2.v[59]*MainFormSLS->hh_1[127]
 + c2.v[60]*MainFormSLS->hh_1[113]
 + c2.v[61]*MainFormSLS->hh_1[99]
 + c2.v[62]*MainFormSLS->hh_1[85]
 + c2.v[63]*MainFormSLS->hh_1[71]
 + c2.v[64]*MainFormSLS->hh_1[57]
 + c2.v[65]*MainFormSLS->hh_1[43]
 + c2.v[66]*MainFormSLS->hh_1[29]
 + c2.v[67]*MainFormSLS->hh_1[15]
 + c2.v[68]*MainFormSLS->hh_1[1]
 + c2.v[69]*MainFormSLS->hh_1[147]
 + c2.v[70]*MainFormSLS->hh_1[133]
 + c2.v[71]*MainFormSLS->hh_1[119]
 + c2.v[72]*MainFormSLS->hh_1[105]
 + c2.v[73]*MainFormSLS->hh_1[91]
 + c2.v[74]*MainFormSLS->hh_1[77]
 + c2.v[75]*MainFormSLS->hh_1[63]
 + c2.v[76]*MainFormSLS->hh_1[49]
 + c2.v[77]*MainFormSLS->hh_1[35]
 + c2.v[78]*MainFormSLS->hh_1[21]
 + c2.v[79]*MainFormSLS->hh_1[7];
s/=N_2;
out.push_back(s);
//������ 154
s =c2.v[0]*MainFormSLS->hh_1[154]
 + c2.v[1]*MainFormSLS->hh_1[142]
 + c2.v[2]*MainFormSLS->hh_1[130]
 + c2.v[3]*MainFormSLS->hh_1[118]
 + c2.v[4]*MainFormSLS->hh_1[106]
 + c2.v[5]*MainFormSLS->hh_1[94]
 + c2.v[6]*MainFormSLS->hh_1[82]
 + c2.v[7]*MainFormSLS->hh_1[70]
 + c2.v[8]*MainFormSLS->hh_1[58]
 + c2.v[9]*MainFormSLS->hh_1[46]
 + c2.v[10]*MainFormSLS->hh_1[34]
 + c2.v[11]*MainFormSLS->hh_1[22]
 + c2.v[12]*MainFormSLS->hh_1[10]
 + c2.v[13]*MainFormSLS->hh_1[158]
 + c2.v[14]*MainFormSLS->hh_1[146]
 + c2.v[15]*MainFormSLS->hh_1[134]
 + c2.v[16]*MainFormSLS->hh_1[122]
 + c2.v[17]*MainFormSLS->hh_1[110]
 + c2.v[18]*MainFormSLS->hh_1[98]
 + c2.v[19]*MainFormSLS->hh_1[86]
 + c2.v[20]*MainFormSLS->hh_1[74]
 + c2.v[21]*MainFormSLS->hh_1[62]
 + c2.v[22]*MainFormSLS->hh_1[50]
 + c2.v[23]*MainFormSLS->hh_1[38]
 + c2.v[24]*MainFormSLS->hh_1[26]
 + c2.v[25]*MainFormSLS->hh_1[14]
 + c2.v[26]*MainFormSLS->hh_1[2]
 + c2.v[27]*MainFormSLS->hh_1[150]
 + c2.v[28]*MainFormSLS->hh_1[138]
 + c2.v[29]*MainFormSLS->hh_1[126]
 + c2.v[30]*MainFormSLS->hh_1[114]
 + c2.v[31]*MainFormSLS->hh_1[102]
 + c2.v[32]*MainFormSLS->hh_1[90]
 + c2.v[33]*MainFormSLS->hh_1[78]
 + c2.v[34]*MainFormSLS->hh_1[66]
 + c2.v[35]*MainFormSLS->hh_1[54]
 + c2.v[36]*MainFormSLS->hh_1[42]
 + c2.v[37]*MainFormSLS->hh_1[30]
 + c2.v[38]*MainFormSLS->hh_1[18]
 + c2.v[39]*MainFormSLS->hh_1[6]
 + c2.v[40]*MainFormSLS->hh_1[154]
 + c2.v[41]*MainFormSLS->hh_1[142]
 + c2.v[42]*MainFormSLS->hh_1[130]
 + c2.v[43]*MainFormSLS->hh_1[118]
 + c2.v[44]*MainFormSLS->hh_1[106]
 + c2.v[45]*MainFormSLS->hh_1[94]
 + c2.v[46]*MainFormSLS->hh_1[82]
 + c2.v[47]*MainFormSLS->hh_1[70]
 + c2.v[48]*MainFormSLS->hh_1[58]
 + c2.v[49]*MainFormSLS->hh_1[46]
 + c2.v[50]*MainFormSLS->hh_1[34]
 + c2.v[51]*MainFormSLS->hh_1[22]
 + c2.v[52]*MainFormSLS->hh_1[10]
 + c2.v[53]*MainFormSLS->hh_1[158]
 + c2.v[54]*MainFormSLS->hh_1[146]
 + c2.v[55]*MainFormSLS->hh_1[134]
 + c2.v[56]*MainFormSLS->hh_1[122]
 + c2.v[57]*MainFormSLS->hh_1[110]
 + c2.v[58]*MainFormSLS->hh_1[98]
 + c2.v[59]*MainFormSLS->hh_1[86]
 + c2.v[60]*MainFormSLS->hh_1[74]
 + c2.v[61]*MainFormSLS->hh_1[62]
 + c2.v[62]*MainFormSLS->hh_1[50]
 + c2.v[63]*MainFormSLS->hh_1[38]
 + c2.v[64]*MainFormSLS->hh_1[26]
 + c2.v[65]*MainFormSLS->hh_1[14]
 + c2.v[66]*MainFormSLS->hh_1[2]
 + c2.v[67]*MainFormSLS->hh_1[150]
 + c2.v[68]*MainFormSLS->hh_1[138]
 + c2.v[69]*MainFormSLS->hh_1[126]
 + c2.v[70]*MainFormSLS->hh_1[114]
 + c2.v[71]*MainFormSLS->hh_1[102]
 + c2.v[72]*MainFormSLS->hh_1[90]
 + c2.v[73]*MainFormSLS->hh_1[78]
 + c2.v[74]*MainFormSLS->hh_1[66]
 + c2.v[75]*MainFormSLS->hh_1[54]
 + c2.v[76]*MainFormSLS->hh_1[42]
 + c2.v[77]*MainFormSLS->hh_1[30]
 + c2.v[78]*MainFormSLS->hh_1[18]
 + c2.v[79]*MainFormSLS->hh_1[6];
s/=N_2;
out.push_back(s);
//������ 155
s =c2.v[0]*MainFormSLS->hh_1[155]
 + c2.v[1]*MainFormSLS->hh_1[145]
 + c2.v[2]*MainFormSLS->hh_1[135]
 + c2.v[3]*MainFormSLS->hh_1[125]
 + c2.v[4]*MainFormSLS->hh_1[115]
 + c2.v[5]*MainFormSLS->hh_1[105]
 + c2.v[6]*MainFormSLS->hh_1[95]
 + c2.v[7]*MainFormSLS->hh_1[85]
 + c2.v[8]*MainFormSLS->hh_1[75]
 + c2.v[9]*MainFormSLS->hh_1[65]
 + c2.v[10]*MainFormSLS->hh_1[55]
 + c2.v[11]*MainFormSLS->hh_1[45]
 + c2.v[12]*MainFormSLS->hh_1[35]
 + c2.v[13]*MainFormSLS->hh_1[25]
 + c2.v[14]*MainFormSLS->hh_1[15]
 + c2.v[15]*MainFormSLS->hh_1[5]
 + c2.v[16]*MainFormSLS->hh_1[155]
 + c2.v[17]*MainFormSLS->hh_1[145]
 + c2.v[18]*MainFormSLS->hh_1[135]
 + c2.v[19]*MainFormSLS->hh_1[125]
 + c2.v[20]*MainFormSLS->hh_1[115]
 + c2.v[21]*MainFormSLS->hh_1[105]
 + c2.v[22]*MainFormSLS->hh_1[95]
 + c2.v[23]*MainFormSLS->hh_1[85]
 + c2.v[24]*MainFormSLS->hh_1[75]
 + c2.v[25]*MainFormSLS->hh_1[65]
 + c2.v[26]*MainFormSLS->hh_1[55]
 + c2.v[27]*MainFormSLS->hh_1[45]
 + c2.v[28]*MainFormSLS->hh_1[35]
 + c2.v[29]*MainFormSLS->hh_1[25]
 + c2.v[30]*MainFormSLS->hh_1[15]
 + c2.v[31]*MainFormSLS->hh_1[5]
 + c2.v[32]*MainFormSLS->hh_1[155]
 + c2.v[33]*MainFormSLS->hh_1[145]
 + c2.v[34]*MainFormSLS->hh_1[135]
 + c2.v[35]*MainFormSLS->hh_1[125]
 + c2.v[36]*MainFormSLS->hh_1[115]
 + c2.v[37]*MainFormSLS->hh_1[105]
 + c2.v[38]*MainFormSLS->hh_1[95]
 + c2.v[39]*MainFormSLS->hh_1[85]
 + c2.v[40]*MainFormSLS->hh_1[75]
 + c2.v[41]*MainFormSLS->hh_1[65]
 + c2.v[42]*MainFormSLS->hh_1[55]
 + c2.v[43]*MainFormSLS->hh_1[45]
 + c2.v[44]*MainFormSLS->hh_1[35]
 + c2.v[45]*MainFormSLS->hh_1[25]
 + c2.v[46]*MainFormSLS->hh_1[15]
 + c2.v[47]*MainFormSLS->hh_1[5]
 + c2.v[48]*MainFormSLS->hh_1[155]
 + c2.v[49]*MainFormSLS->hh_1[145]
 + c2.v[50]*MainFormSLS->hh_1[135]
 + c2.v[51]*MainFormSLS->hh_1[125]
 + c2.v[52]*MainFormSLS->hh_1[115]
 + c2.v[53]*MainFormSLS->hh_1[105]
 + c2.v[54]*MainFormSLS->hh_1[95]
 + c2.v[55]*MainFormSLS->hh_1[85]
 + c2.v[56]*MainFormSLS->hh_1[75]
 + c2.v[57]*MainFormSLS->hh_1[65]
 + c2.v[58]*MainFormSLS->hh_1[55]
 + c2.v[59]*MainFormSLS->hh_1[45]
 + c2.v[60]*MainFormSLS->hh_1[35]
 + c2.v[61]*MainFormSLS->hh_1[25]
 + c2.v[62]*MainFormSLS->hh_1[15]
 + c2.v[63]*MainFormSLS->hh_1[5]
 + c2.v[64]*MainFormSLS->hh_1[155]
 + c2.v[65]*MainFormSLS->hh_1[145]
 + c2.v[66]*MainFormSLS->hh_1[135]
 + c2.v[67]*MainFormSLS->hh_1[125]
 + c2.v[68]*MainFormSLS->hh_1[115]
 + c2.v[69]*MainFormSLS->hh_1[105]
 + c2.v[70]*MainFormSLS->hh_1[95]
 + c2.v[71]*MainFormSLS->hh_1[85]
 + c2.v[72]*MainFormSLS->hh_1[75]
 + c2.v[73]*MainFormSLS->hh_1[65]
 + c2.v[74]*MainFormSLS->hh_1[55]
 + c2.v[75]*MainFormSLS->hh_1[45]
 + c2.v[76]*MainFormSLS->hh_1[35]
 + c2.v[77]*MainFormSLS->hh_1[25]
 + c2.v[78]*MainFormSLS->hh_1[15]
 + c2.v[79]*MainFormSLS->hh_1[5];
s/=N_2;
out.push_back(s);
//������ 156
s =c2.v[0]*MainFormSLS->hh_1[156]
 + c2.v[1]*MainFormSLS->hh_1[148]
 + c2.v[2]*MainFormSLS->hh_1[140]
 + c2.v[3]*MainFormSLS->hh_1[132]
 + c2.v[4]*MainFormSLS->hh_1[124]
 + c2.v[5]*MainFormSLS->hh_1[116]
 + c2.v[6]*MainFormSLS->hh_1[108]
 + c2.v[7]*MainFormSLS->hh_1[100]
 + c2.v[8]*MainFormSLS->hh_1[92]
 + c2.v[9]*MainFormSLS->hh_1[84]
 + c2.v[10]*MainFormSLS->hh_1[76]
 + c2.v[11]*MainFormSLS->hh_1[68]
 + c2.v[12]*MainFormSLS->hh_1[60]
 + c2.v[13]*MainFormSLS->hh_1[52]
 + c2.v[14]*MainFormSLS->hh_1[44]
 + c2.v[15]*MainFormSLS->hh_1[36]
 + c2.v[16]*MainFormSLS->hh_1[28]
 + c2.v[17]*MainFormSLS->hh_1[20]
 + c2.v[18]*MainFormSLS->hh_1[12]
 + c2.v[19]*MainFormSLS->hh_1[4]
 + c2.v[20]*MainFormSLS->hh_1[156]
 + c2.v[21]*MainFormSLS->hh_1[148]
 + c2.v[22]*MainFormSLS->hh_1[140]
 + c2.v[23]*MainFormSLS->hh_1[132]
 + c2.v[24]*MainFormSLS->hh_1[124]
 + c2.v[25]*MainFormSLS->hh_1[116]
 + c2.v[26]*MainFormSLS->hh_1[108]
 + c2.v[27]*MainFormSLS->hh_1[100]
 + c2.v[28]*MainFormSLS->hh_1[92]
 + c2.v[29]*MainFormSLS->hh_1[84]
 + c2.v[30]*MainFormSLS->hh_1[76]
 + c2.v[31]*MainFormSLS->hh_1[68]
 + c2.v[32]*MainFormSLS->hh_1[60]
 + c2.v[33]*MainFormSLS->hh_1[52]
 + c2.v[34]*MainFormSLS->hh_1[44]
 + c2.v[35]*MainFormSLS->hh_1[36]
 + c2.v[36]*MainFormSLS->hh_1[28]
 + c2.v[37]*MainFormSLS->hh_1[20]
 + c2.v[38]*MainFormSLS->hh_1[12]
 + c2.v[39]*MainFormSLS->hh_1[4]
 + c2.v[40]*MainFormSLS->hh_1[156]
 + c2.v[41]*MainFormSLS->hh_1[148]
 + c2.v[42]*MainFormSLS->hh_1[140]
 + c2.v[43]*MainFormSLS->hh_1[132]
 + c2.v[44]*MainFormSLS->hh_1[124]
 + c2.v[45]*MainFormSLS->hh_1[116]
 + c2.v[46]*MainFormSLS->hh_1[108]
 + c2.v[47]*MainFormSLS->hh_1[100]
 + c2.v[48]*MainFormSLS->hh_1[92]
 + c2.v[49]*MainFormSLS->hh_1[84]
 + c2.v[50]*MainFormSLS->hh_1[76]
 + c2.v[51]*MainFormSLS->hh_1[68]
 + c2.v[52]*MainFormSLS->hh_1[60]
 + c2.v[53]*MainFormSLS->hh_1[52]
 + c2.v[54]*MainFormSLS->hh_1[44]
 + c2.v[55]*MainFormSLS->hh_1[36]
 + c2.v[56]*MainFormSLS->hh_1[28]
 + c2.v[57]*MainFormSLS->hh_1[20]
 + c2.v[58]*MainFormSLS->hh_1[12]
 + c2.v[59]*MainFormSLS->hh_1[4]
 + c2.v[60]*MainFormSLS->hh_1[156]
 + c2.v[61]*MainFormSLS->hh_1[148]
 + c2.v[62]*MainFormSLS->hh_1[140]
 + c2.v[63]*MainFormSLS->hh_1[132]
 + c2.v[64]*MainFormSLS->hh_1[124]
 + c2.v[65]*MainFormSLS->hh_1[116]
 + c2.v[66]*MainFormSLS->hh_1[108]
 + c2.v[67]*MainFormSLS->hh_1[100]
 + c2.v[68]*MainFormSLS->hh_1[92]
 + c2.v[69]*MainFormSLS->hh_1[84]
 + c2.v[70]*MainFormSLS->hh_1[76]
 + c2.v[71]*MainFormSLS->hh_1[68]
 + c2.v[72]*MainFormSLS->hh_1[60]
 + c2.v[73]*MainFormSLS->hh_1[52]
 + c2.v[74]*MainFormSLS->hh_1[44]
 + c2.v[75]*MainFormSLS->hh_1[36]
 + c2.v[76]*MainFormSLS->hh_1[28]
 + c2.v[77]*MainFormSLS->hh_1[20]
 + c2.v[78]*MainFormSLS->hh_1[12]
 + c2.v[79]*MainFormSLS->hh_1[4];
s/=N_2;
out.push_back(s);
//������ 157
s =c2.v[0]*MainFormSLS->hh_1[157]
 + c2.v[1]*MainFormSLS->hh_1[151]
 + c2.v[2]*MainFormSLS->hh_1[145]
 + c2.v[3]*MainFormSLS->hh_1[139]
 + c2.v[4]*MainFormSLS->hh_1[133]
 + c2.v[5]*MainFormSLS->hh_1[127]
 + c2.v[6]*MainFormSLS->hh_1[121]
 + c2.v[7]*MainFormSLS->hh_1[115]
 + c2.v[8]*MainFormSLS->hh_1[109]
 + c2.v[9]*MainFormSLS->hh_1[103]
 + c2.v[10]*MainFormSLS->hh_1[97]
 + c2.v[11]*MainFormSLS->hh_1[91]
 + c2.v[12]*MainFormSLS->hh_1[85]
 + c2.v[13]*MainFormSLS->hh_1[79]
 + c2.v[14]*MainFormSLS->hh_1[73]
 + c2.v[15]*MainFormSLS->hh_1[67]
 + c2.v[16]*MainFormSLS->hh_1[61]
 + c2.v[17]*MainFormSLS->hh_1[55]
 + c2.v[18]*MainFormSLS->hh_1[49]
 + c2.v[19]*MainFormSLS->hh_1[43]
 + c2.v[20]*MainFormSLS->hh_1[37]
 + c2.v[21]*MainFormSLS->hh_1[31]
 + c2.v[22]*MainFormSLS->hh_1[25]
 + c2.v[23]*MainFormSLS->hh_1[19]
 + c2.v[24]*MainFormSLS->hh_1[13]
 + c2.v[25]*MainFormSLS->hh_1[7]
 + c2.v[26]*MainFormSLS->hh_1[1]
 + c2.v[27]*MainFormSLS->hh_1[155]
 + c2.v[28]*MainFormSLS->hh_1[149]
 + c2.v[29]*MainFormSLS->hh_1[143]
 + c2.v[30]*MainFormSLS->hh_1[137]
 + c2.v[31]*MainFormSLS->hh_1[131]
 + c2.v[32]*MainFormSLS->hh_1[125]
 + c2.v[33]*MainFormSLS->hh_1[119]
 + c2.v[34]*MainFormSLS->hh_1[113]
 + c2.v[35]*MainFormSLS->hh_1[107]
 + c2.v[36]*MainFormSLS->hh_1[101]
 + c2.v[37]*MainFormSLS->hh_1[95]
 + c2.v[38]*MainFormSLS->hh_1[89]
 + c2.v[39]*MainFormSLS->hh_1[83]
 + c2.v[40]*MainFormSLS->hh_1[77]
 + c2.v[41]*MainFormSLS->hh_1[71]
 + c2.v[42]*MainFormSLS->hh_1[65]
 + c2.v[43]*MainFormSLS->hh_1[59]
 + c2.v[44]*MainFormSLS->hh_1[53]
 + c2.v[45]*MainFormSLS->hh_1[47]
 + c2.v[46]*MainFormSLS->hh_1[41]
 + c2.v[47]*MainFormSLS->hh_1[35]
 + c2.v[48]*MainFormSLS->hh_1[29]
 + c2.v[49]*MainFormSLS->hh_1[23]
 + c2.v[50]*MainFormSLS->hh_1[17]
 + c2.v[51]*MainFormSLS->hh_1[11]
 + c2.v[52]*MainFormSLS->hh_1[5]
 + c2.v[53]*MainFormSLS->hh_1[159]
 + c2.v[54]*MainFormSLS->hh_1[153]
 + c2.v[55]*MainFormSLS->hh_1[147]
 + c2.v[56]*MainFormSLS->hh_1[141]
 + c2.v[57]*MainFormSLS->hh_1[135]
 + c2.v[58]*MainFormSLS->hh_1[129]
 + c2.v[59]*MainFormSLS->hh_1[123]
 + c2.v[60]*MainFormSLS->hh_1[117]
 + c2.v[61]*MainFormSLS->hh_1[111]
 + c2.v[62]*MainFormSLS->hh_1[105]
 + c2.v[63]*MainFormSLS->hh_1[99]
 + c2.v[64]*MainFormSLS->hh_1[93]
 + c2.v[65]*MainFormSLS->hh_1[87]
 + c2.v[66]*MainFormSLS->hh_1[81]
 + c2.v[67]*MainFormSLS->hh_1[75]
 + c2.v[68]*MainFormSLS->hh_1[69]
 + c2.v[69]*MainFormSLS->hh_1[63]
 + c2.v[70]*MainFormSLS->hh_1[57]
 + c2.v[71]*MainFormSLS->hh_1[51]
 + c2.v[72]*MainFormSLS->hh_1[45]
 + c2.v[73]*MainFormSLS->hh_1[39]
 + c2.v[74]*MainFormSLS->hh_1[33]
 + c2.v[75]*MainFormSLS->hh_1[27]
 + c2.v[76]*MainFormSLS->hh_1[21]
 + c2.v[77]*MainFormSLS->hh_1[15]
 + c2.v[78]*MainFormSLS->hh_1[9]
 + c2.v[79]*MainFormSLS->hh_1[3];
s/=N_2;
out.push_back(s);
//������ 158
s =c2.v[0]*MainFormSLS->hh_1[158]
 + c2.v[1]*MainFormSLS->hh_1[154]
 + c2.v[2]*MainFormSLS->hh_1[150]
 + c2.v[3]*MainFormSLS->hh_1[146]
 + c2.v[4]*MainFormSLS->hh_1[142]
 + c2.v[5]*MainFormSLS->hh_1[138]
 + c2.v[6]*MainFormSLS->hh_1[134]
 + c2.v[7]*MainFormSLS->hh_1[130]
 + c2.v[8]*MainFormSLS->hh_1[126]
 + c2.v[9]*MainFormSLS->hh_1[122]
 + c2.v[10]*MainFormSLS->hh_1[118]
 + c2.v[11]*MainFormSLS->hh_1[114]
 + c2.v[12]*MainFormSLS->hh_1[110]
 + c2.v[13]*MainFormSLS->hh_1[106]
 + c2.v[14]*MainFormSLS->hh_1[102]
 + c2.v[15]*MainFormSLS->hh_1[98]
 + c2.v[16]*MainFormSLS->hh_1[94]
 + c2.v[17]*MainFormSLS->hh_1[90]
 + c2.v[18]*MainFormSLS->hh_1[86]
 + c2.v[19]*MainFormSLS->hh_1[82]
 + c2.v[20]*MainFormSLS->hh_1[78]
 + c2.v[21]*MainFormSLS->hh_1[74]
 + c2.v[22]*MainFormSLS->hh_1[70]
 + c2.v[23]*MainFormSLS->hh_1[66]
 + c2.v[24]*MainFormSLS->hh_1[62]
 + c2.v[25]*MainFormSLS->hh_1[58]
 + c2.v[26]*MainFormSLS->hh_1[54]
 + c2.v[27]*MainFormSLS->hh_1[50]
 + c2.v[28]*MainFormSLS->hh_1[46]
 + c2.v[29]*MainFormSLS->hh_1[42]
 + c2.v[30]*MainFormSLS->hh_1[38]
 + c2.v[31]*MainFormSLS->hh_1[34]
 + c2.v[32]*MainFormSLS->hh_1[30]
 + c2.v[33]*MainFormSLS->hh_1[26]
 + c2.v[34]*MainFormSLS->hh_1[22]
 + c2.v[35]*MainFormSLS->hh_1[18]
 + c2.v[36]*MainFormSLS->hh_1[14]
 + c2.v[37]*MainFormSLS->hh_1[10]
 + c2.v[38]*MainFormSLS->hh_1[6]
 + c2.v[39]*MainFormSLS->hh_1[2]
 + c2.v[40]*MainFormSLS->hh_1[158]
 + c2.v[41]*MainFormSLS->hh_1[154]
 + c2.v[42]*MainFormSLS->hh_1[150]
 + c2.v[43]*MainFormSLS->hh_1[146]
 + c2.v[44]*MainFormSLS->hh_1[142]
 + c2.v[45]*MainFormSLS->hh_1[138]
 + c2.v[46]*MainFormSLS->hh_1[134]
 + c2.v[47]*MainFormSLS->hh_1[130]
 + c2.v[48]*MainFormSLS->hh_1[126]
 + c2.v[49]*MainFormSLS->hh_1[122]
 + c2.v[50]*MainFormSLS->hh_1[118]
 + c2.v[51]*MainFormSLS->hh_1[114]
 + c2.v[52]*MainFormSLS->hh_1[110]
 + c2.v[53]*MainFormSLS->hh_1[106]
 + c2.v[54]*MainFormSLS->hh_1[102]
 + c2.v[55]*MainFormSLS->hh_1[98]
 + c2.v[56]*MainFormSLS->hh_1[94]
 + c2.v[57]*MainFormSLS->hh_1[90]
 + c2.v[58]*MainFormSLS->hh_1[86]
 + c2.v[59]*MainFormSLS->hh_1[82]
 + c2.v[60]*MainFormSLS->hh_1[78]
 + c2.v[61]*MainFormSLS->hh_1[74]
 + c2.v[62]*MainFormSLS->hh_1[70]
 + c2.v[63]*MainFormSLS->hh_1[66]
 + c2.v[64]*MainFormSLS->hh_1[62]
 + c2.v[65]*MainFormSLS->hh_1[58]
 + c2.v[66]*MainFormSLS->hh_1[54]
 + c2.v[67]*MainFormSLS->hh_1[50]
 + c2.v[68]*MainFormSLS->hh_1[46]
 + c2.v[69]*MainFormSLS->hh_1[42]
 + c2.v[70]*MainFormSLS->hh_1[38]
 + c2.v[71]*MainFormSLS->hh_1[34]
 + c2.v[72]*MainFormSLS->hh_1[30]
 + c2.v[73]*MainFormSLS->hh_1[26]
 + c2.v[74]*MainFormSLS->hh_1[22]
 + c2.v[75]*MainFormSLS->hh_1[18]
 + c2.v[76]*MainFormSLS->hh_1[14]
 + c2.v[77]*MainFormSLS->hh_1[10]
 + c2.v[78]*MainFormSLS->hh_1[6]
 + c2.v[79]*MainFormSLS->hh_1[2];
s/=N_2;
out.push_back(s);
//������ 159
s =c2.v[0]*MainFormSLS->hh_1[159]
 + c2.v[1]*MainFormSLS->hh_1[157]
 + c2.v[2]*MainFormSLS->hh_1[155]
 + c2.v[3]*MainFormSLS->hh_1[153]
 + c2.v[4]*MainFormSLS->hh_1[151]
 + c2.v[5]*MainFormSLS->hh_1[149]
 + c2.v[6]*MainFormSLS->hh_1[147]
 + c2.v[7]*MainFormSLS->hh_1[145]
 + c2.v[8]*MainFormSLS->hh_1[143]
 + c2.v[9]*MainFormSLS->hh_1[141]
 + c2.v[10]*MainFormSLS->hh_1[139]
 + c2.v[11]*MainFormSLS->hh_1[137]
 + c2.v[12]*MainFormSLS->hh_1[135]
 + c2.v[13]*MainFormSLS->hh_1[133]
 + c2.v[14]*MainFormSLS->hh_1[131]
 + c2.v[15]*MainFormSLS->hh_1[129]
 + c2.v[16]*MainFormSLS->hh_1[127]
 + c2.v[17]*MainFormSLS->hh_1[125]
 + c2.v[18]*MainFormSLS->hh_1[123]
 + c2.v[19]*MainFormSLS->hh_1[121]
 + c2.v[20]*MainFormSLS->hh_1[119]
 + c2.v[21]*MainFormSLS->hh_1[117]
 + c2.v[22]*MainFormSLS->hh_1[115]
 + c2.v[23]*MainFormSLS->hh_1[113]
 + c2.v[24]*MainFormSLS->hh_1[111]
 + c2.v[25]*MainFormSLS->hh_1[109]
 + c2.v[26]*MainFormSLS->hh_1[107]
 + c2.v[27]*MainFormSLS->hh_1[105]
 + c2.v[28]*MainFormSLS->hh_1[103]
 + c2.v[29]*MainFormSLS->hh_1[101]
 + c2.v[30]*MainFormSLS->hh_1[99]
 + c2.v[31]*MainFormSLS->hh_1[97]
 + c2.v[32]*MainFormSLS->hh_1[95]
 + c2.v[33]*MainFormSLS->hh_1[93]
 + c2.v[34]*MainFormSLS->hh_1[91]
 + c2.v[35]*MainFormSLS->hh_1[89]
 + c2.v[36]*MainFormSLS->hh_1[87]
 + c2.v[37]*MainFormSLS->hh_1[85]
 + c2.v[38]*MainFormSLS->hh_1[83]
 + c2.v[39]*MainFormSLS->hh_1[81]
 + c2.v[40]*MainFormSLS->hh_1[79]
 + c2.v[41]*MainFormSLS->hh_1[77]
 + c2.v[42]*MainFormSLS->hh_1[75]
 + c2.v[43]*MainFormSLS->hh_1[73]
 + c2.v[44]*MainFormSLS->hh_1[71]
 + c2.v[45]*MainFormSLS->hh_1[69]
 + c2.v[46]*MainFormSLS->hh_1[67]
 + c2.v[47]*MainFormSLS->hh_1[65]
 + c2.v[48]*MainFormSLS->hh_1[63]
 + c2.v[49]*MainFormSLS->hh_1[61]
 + c2.v[50]*MainFormSLS->hh_1[59]
 + c2.v[51]*MainFormSLS->hh_1[57]
 + c2.v[52]*MainFormSLS->hh_1[55]
 + c2.v[53]*MainFormSLS->hh_1[53]
 + c2.v[54]*MainFormSLS->hh_1[51]
 + c2.v[55]*MainFormSLS->hh_1[49]
 + c2.v[56]*MainFormSLS->hh_1[47]
 + c2.v[57]*MainFormSLS->hh_1[45]
 + c2.v[58]*MainFormSLS->hh_1[43]
 + c2.v[59]*MainFormSLS->hh_1[41]
 + c2.v[60]*MainFormSLS->hh_1[39]
 + c2.v[61]*MainFormSLS->hh_1[37]
 + c2.v[62]*MainFormSLS->hh_1[35]
 + c2.v[63]*MainFormSLS->hh_1[33]
 + c2.v[64]*MainFormSLS->hh_1[31]
 + c2.v[65]*MainFormSLS->hh_1[29]
 + c2.v[66]*MainFormSLS->hh_1[27]
 + c2.v[67]*MainFormSLS->hh_1[25]
 + c2.v[68]*MainFormSLS->hh_1[23]
 + c2.v[69]*MainFormSLS->hh_1[21]
 + c2.v[70]*MainFormSLS->hh_1[19]
 + c2.v[71]*MainFormSLS->hh_1[17]
 + c2.v[72]*MainFormSLS->hh_1[15]
 + c2.v[73]*MainFormSLS->hh_1[13]
 + c2.v[74]*MainFormSLS->hh_1[11]
 + c2.v[75]*MainFormSLS->hh_1[9]
 + c2.v[76]*MainFormSLS->hh_1[7]
 + c2.v[77]*MainFormSLS->hh_1[5]
 + c2.v[78]*MainFormSLS->hh_1[3]
 + c2.v[79]*MainFormSLS->hh_1[1];
s/=N_2;
out.push_back(s);
}
//----------------------------------------------------------------------------