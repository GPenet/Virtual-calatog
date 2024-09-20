


int TblMult3[9] = { 0, 3, 6, 9, 12, 15, 18, 21, 24 };  // 3*i
int TblMult9[9] = { 0, 9, 18, 27, 36, 45, 54, 63, 72 };  // 9*i
int C_minirow[81] = {// TblDiv3 as 27 sub table cell to minirow 
	0, 0, 0, 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6, 7, 7, 7, 8, 8, 8,
	9, 9, 9, 10, 10, 10, 11, 11, 11, 12, 12, 12, 13, 13, 13, 14, 14, 14, 15, 15, 15, 16, 16, 16, 17, 17, 17,
	18, 18, 18, 19, 19, 19, 20, 20, 20, 21, 21, 21, 22, 22, 22, 23, 23, 23, 24, 24, 24, 25, 25, 25, 26, 26, 26,
};
int * Tbldiv3 = C_minirow; //i/3 eg :  mini row or digit in F
int C_row[81] = {// cell to row
	0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 5, 5, 5,
	6, 6, 6, 6, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8,
};
int * Tblofftorow = C_row;
int C_col[81] = {
	0, 1, 2, 3, 4, 5, 6, 7, 8, 0, 1, 2, 3, 4, 5, 6, 7, 8, 0, 1, 2, 3, 4, 5, 6, 7, 8,
	0, 1, 2, 3, 4, 5, 6, 7, 8, 0, 1, 2, 3, 4, 5, 6, 7, 8, 0, 1, 2, 3, 4, 5, 6, 7, 8,
	0, 1, 2, 3, 4, 5, 6, 7, 8, 0, 1, 2, 3, 4, 5, 6, 7, 8, 0, 1, 2, 3, 4, 5, 6, 7, 8,
};
int * TblMod9 = C_col; //i%9 eg : column in block or cell to column
int C_box[81] = {
	0, 0, 0, 1, 1, 1, 2, 2, 2, 0, 0, 0, 1, 1, 1, 2, 2, 2, 0, 0, 0, 1, 1, 1, 2, 2, 2,
	3, 3, 3, 4, 4, 4, 5, 5, 5, 3, 3, 3, 4, 4, 4, 5, 5, 5, 3, 3, 3, 4, 4, 4, 5, 5, 5,
	6, 6, 6, 7, 7, 7, 8, 8, 8, 6, 6, 6, 7, 7, 7, 8, 8, 8, 6, 6, 6, 7, 7, 7, 8, 8, 8,
};
int * Tblofftobox = C_box;//offset to box
int C_stack[81] = {
	0, 0, 0, 1, 1, 1, 2, 2, 2, 0, 0, 0, 1, 1, 1, 2, 2, 2, 0, 0, 0, 1, 1, 1, 2, 2, 2,
	0, 0, 0, 1, 1, 1, 2, 2, 2, 0, 0, 0, 1, 1, 1, 2, 2, 2, 0, 0, 0, 1, 1, 1, 2, 2, 2,
	0, 0, 0, 1, 1, 1, 2, 2, 2, 0, 0, 0, 1, 1, 1, 2, 2, 2, 0, 0, 0, 1, 1, 1, 2, 2, 2,
};
int C_box_rel[81] = {
	0, 1, 2, 0, 1, 2, 0, 1, 2, 3, 4, 5, 3, 4, 5, 3, 4, 5, 6, 7, 8, 6, 7, 8, 6, 7, 8,
	0, 1, 2, 0, 1, 2, 0, 1, 2, 3, 4, 5, 3, 4, 5, 3, 4, 5, 6, 7, 8, 6, 7, 8, 6, 7, 8,
	0, 1, 2, 0, 1, 2, 0, 1, 2, 3, 4, 5, 3, 4, 5, 3, 4, 5, 6, 7, 8, 6, 7, 8, 6, 7, 8,
};
int * TblCelltoBox = C_box_rel;// relative position in the box
int C_transpose_c[81] = {
	80, 79, 78, 77, 76, 75, 74, 73, 72, 71, 70, 69, 68, 67, 66, 65, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0,
};
int C_transpose_d[81] = {
	0, 9, 18, 27, 36, 45, 54, 63, 72, 1, 10, 19, 28, 37, 46, 55, 64, 73, 2, 11, 20, 29, 38, 47, 56, 65, 74, 3, 12, 21, 30, 39, 48, 57, 66, 75, 4, 13, 22, 31, 40, 49, 58, 67, 76, 5, 14, 23, 32, 41, 50, 59, 68, 77, 6, 15, 24, 33, 42, 51, 60, 69, 78, 7, 16, 25, 34, 43, 52, 61, 70, 79, 8, 17, 26, 35, 44, 53, 62, 71, 80,
};

int C_transpose_d2[81] = {
	80, 71, 62, 53, 44, 35, 26, 17, 8, 79, 70, 61, 52, 43, 34, 25, 16, 7, 78, 69, 60, 51, 42, 33, 24, 15, 6,
	77, 68, 59, 50, 41, 32, 23, 14, 5, 76, 67, 58, 49, 40, 31, 22, 13, 4, 75, 66, 57, 48, 39, 30, 21, 12, 3,
	74, 65, 56, 47, 38, 29, 20, 11, 2, 73, 64, 55, 46, 37, 28, 19, 10, 1, 72, 63, 54, 45, 36, 27, 18, 9, 0,
};

int C_transpose_r[81] = {
	8, 17, 26, 35, 44, 53, 62, 71, 80, 7, 16, 25, 34, 43, 52, 61, 70, 79, 6, 15, 24, 33, 42, 51, 60, 69, 78,
	5, 14, 23, 32, 41, 50, 59, 68, 77, 4, 13, 22, 31, 40, 49, 58, 67, 76, 3, 12, 21, 30, 39, 48, 57, 66, 75,
	2, 11, 20, 29, 38, 47, 56, 65, 74, 1, 10, 19, 28, 37, 46, 55, 64, 73, 0, 9, 18, 27, 36, 45, 54, 63, 72,
};

int C_transpose_rm[81] = {
	72, 63, 54, 45, 36, 27, 18, 9, 0, 73, 64, 55, 46, 37, 28, 19, 10, 1, 74, 65, 56, 47, 38, 29, 20, 11, 2,
	75, 66, 57, 48, 39, 30, 21, 12, 3, 76, 67, 58, 49, 40, 31, 22, 13, 4, 77, 68, 59, 50, 41, 32, 23, 14, 5,
	78, 69, 60, 51, 42, 33, 24, 15, 6, 79, 70, 61, 52, 43, 34, 25, 16, 7, 80, 71, 62, 53, 44, 35, 26, 17, 8,
};

int C_mod27[81] = {
	0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26,
	0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26,
	0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26,
};
int * Tbloffset = C_mod27; // giving cell to offset in a band
int C_div27[81] = {
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
};
int * TblBoard_Block = C_div27; // giving cell -> band 

int C_To128[81] = {
	0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26,
	32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58,
	64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90
};

int From_128_To_81[128] = {
	0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 0, 0, 0, 0, 0,
	27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 0, 0, 0, //54 55 dummy cells mode 54 cells
	54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 0, 0, 0, 0   // 81 dummy cell  mode 81 cells
};
uint32_t mini_pairs_tripletsbf[36] = {
	06,05,03,060,050,030,0600,0500,0300,
	06000,05000,03000,060000,050000,030000,0600000,0500000,0300000,
	06000000,05000000,03000000,
	060000000,050000000,030000000,
	0600000000,0500000000,0300000000,
	07,070,0700,
	07000,070000,0700000,
	07000000,070000000,0700000000,
};
int  box_col_to_row[512] = {// transpose a box
00,01,010,011,0100,0101,0110,0111,02,03,012,013,0102,0103,0112,0113,
020,021,030,031,0120,0121,0130,0131,022,023,032,033,0122,0123,0132,0133,
0200,0201,0210,0211,0300,0301,0310,0311,0202,0203,0212,0213,0302,0303,0312,0313,
0220,0221,0230,0231,0320,0321,0330,0331,0222,0223,0232,0233,0322,0323,0332,0333,
04,05,014,015,0104,0105,0114,0115,06,07,016,017,0106,0107,0116,0117,
024,025,034,035,0124,0125,0134,0135,026,027,036,037,0126,0127,0136,0137,
0204,0205,0214,0215,0304,0305,0314,0315,0206,0207,0216,0217,0306,0307,0316,0317,
0224,0225,0234,0235,0324,0325,0334,0335,0226,0227,0236,0237,0326,0327,0336,0337,
040,041,050,051,0140,0141,0150,0151,042,043,052,053,0142,0143,0152,0153,
060,061,070,071,0160,0161,0170,0171,062,063,072,073,0162,0163,0172,0173,
0240,0241,0250,0251,0340,0341,0350,0351,0242,0243,0252,0253,0342,0343,0352,0353,
0260,0261,0270,0271,0360,0361,0370,0371,0262,0263,0272,0273,0362,0363,0372,0373,
044,045,054,055,0144,0145,0154,0155,046,047,056,057,0146,0147,0156,0157,
064,065,074,075,0164,0165,0174,0175,066,067,076,077,0166,0167,0176,0177,
0244,0245,0254,0255,0344,0345,0354,0355,0246,0247,0256,0257,0346,0347,0356,0357,
0264,0265,0274,0275,0364,0365,0374,0375,0266,0267,0276,0277,0366,0367,0376,0377,
0400,0401,0410,0411,0500,0501,0510,0511,0402,0403,0412,0413,0502,0503,0512,0513,
0420,0421,0430,0431,0520,0521,0530,0531,0422,0423,0432,0433,0522,0523,0532,0533,
0600,0601,0610,0611,0700,0701,0710,0711,0602,0603,0612,0613,0702,0703,0712,0713,
0620,0621,0630,0631,0720,0721,0730,0731,0622,0623,0632,0633,0722,0723,0732,0733,
0404,0405,0414,0415,0504,0505,0514,0515,0406,0407,0416,0417,0506,0507,0516,0517,
0424,0425,0434,0435,0524,0525,0534,0535,0426,0427,0436,0437,0526,0527,0536,0537,
0604,0605,0614,0615,0704,0705,0714,0715,0606,0607,0616,0617,0706,0707,0716,0717,
0624,0625,0634,0635,0724,0725,0734,0735,0626,0627,0636,0637,0726,0727,0736,0737,
0440,0441,0450,0451,0540,0541,0550,0551,0442,0443,0452,0453,0542,0543,0552,0553,
0460,0461,0470,0471,0560,0561,0570,0571,0462,0463,0472,0473,0562,0563,0572,0573,
0640,0641,0650,0651,0740,0741,0750,0751,0642,0643,0652,0653,0742,0743,0752,0753,
0660,0661,0670,0671,0760,0761,0770,0771,0662,0663,0672,0673,0762,0763,0772,0773,
0444,0445,0454,0455,0544,0545,0554,0555,0446,0447,0456,0457,0546,0547,0556,0557,
0464,0465,0474,0475,0564,0565,0574,0575,0466,0467,0476,0477,0566,0567,0576,0577,
0644,0645,0654,0655,0744,0745,0754,0755,0646,0647,0656,0657,0746,0747,0756,0757,
0664,0665,0674,0675,0764,0765,0774,0775,0666,0667,0676,0677,0766,0767,0776,0777,
};
int treverse_mini[8] = { 0,4,2,6,1,5,3,7 };
int tband_box[6] = { 07007007, 070070070, 0700700700, 0777, 0777000, 0777000000 };
int  tband_row[3] = { 0777, 0777000, 0777000000 };
int tband_box_skrink[3] = { 0111, 0222, 0444 };
