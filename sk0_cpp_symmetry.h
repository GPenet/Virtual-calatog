



USHORT sh_36[36][2] = {
	0, 72, 1, 73, 2, 74, 3, 75, 4, 76, 5, 77, 6, 78, 7, 79, 8, 80,  // 9
	9, 63, 10, 64, 11, 65, 12, 66, 13, 67, 14, 68, 15, 69, 16, 70, 17, 71,  // 18
	18, 54, 19, 55, 20, 56, 21, 57, 22, 58, 23, 59, 24, 60, 25, 61, 26, 62, //27
	27, 45, 28, 46, 29, 47, 30, 48, 31, 49, 32, 50, 33, 51, 34, 52, 35, 53 // 36
};

USHORT sv_36[36][2] = {  // only searched as direct
	0, 8, 1, 7, 2, 6, 3, 5,  // 4
	9, 17, 10, 16, 11, 15, 12, 14,  // 8
	18, 26, 19, 25, 20, 24, 21, 23,  // 12
	27, 35, 28, 34, 29, 33, 30, 32,  // 16
	36, 44, 37, 43, 38, 42, 39, 41,  // 20
	45, 53, 46, 52, 47, 51, 48, 50,  // 24
	54, 62, 55, 61, 56, 60, 57, 59,  // 28
	63, 71, 64, 70, 65, 69, 66, 68,  // 32
	72, 80, 73, 79, 74, 78, 75, 77  // 36
};

USHORT sd1_36[36][2] = {
	31, 39, 32, 48, 41, 49, // box 5
	1, 9, 2, 18, 3, 27, 4, 36, 5, 45, // band1 stack 1 
	11, 19, 12, 28, 13, 37, 14, 46,
	21, 29, 22, 38, 23, 47,
	6, 54, 7, 63, 8, 72, 15, 55, 16, 64, 17, 73,
	24, 56, 25, 65, 26, 74,
	33, 57, 34, 66, 35, 75, 42, 58, 43, 67, 44, 76,
	51, 59, 52, 68, 53, 77, 61, 69, 62, 78, 71, 79
};
USHORT sd2_36[36][2] = { // only searched as direct
	7, 17, 6, 26, 5, 35, 4, 44,  // 4
	3, 53, 2, 62, 1, 71, 0, 80,  // 8
	15, 25, 14, 34, 13, 43, 12, 52,  // 12
	11, 61, 10, 70, 9, 79, 23, 33,  // 16
	22, 42, 21, 51, 20, 60, 19, 69,  // 20
	18, 78, 31, 41, 30, 50, 29, 59,  // 24
	28, 68, 27, 77, 39, 49, 38, 58,  // 28
	37, 67, 36, 76, 47, 57, 46, 66,  // 32
	45, 75, 55, 65, 54, 74, 63, 73  // 36
};
USHORT sst_36[36][2] = {
	27, 29, 36, 38, 45, 47,// Box4 and stack 1
	1, 55, 10, 64, 19, 73, 0, 56, 2, 54, 9, 65, 11, 63, 18, 74, 20, 72,
	30, 32, 39, 41, 48, 50, //box 5 stack 2
	4, 58, 13, 67, 22, 76, 3, 59, 12, 68, 21, 77, 5, 57, 14, 66, 23, 75,
	33, 35, 42, 44, 51, 53,  //box 6 stack 3
	7, 61, 16, 70, 25, 79, 6, 62, 15, 71, 24, 80, 8, 60, 17, 69, 26, 78
};
USHORT sc_40[40][2] = {
	80, 0, 79, 1, 78, 2, 77, 3,  //4
	76, 4, 75, 5, 74, 6, 73, 7,  //8
	72, 8, 71, 9, 70, 10, 69, 11,  //12
	68, 12, 67, 13, 66, 14, 65, 15,  //16
	64, 16, 63, 17, 62, 18, 61, 19,  //20
	60, 20, 59, 21, 58, 22, 57, 23,  //24
	56, 24, 55, 25, 54, 26, 53, 27,  //28
	52, 28, 51, 29, 50, 30, 49, 31,  //32
	48, 32, 47, 33, 46, 34, 45, 35,  //36
	44, 36, 43, 37, 42, 38, 41, 39  //40
};
USHORT sr90_20[20][4] = {
	0, 8, 80, 72, 1, 17, 79, 63, 2, 26, 78, 54, 3, 35, 77, 45,  // 4
	4, 44, 76, 36, 9, 7, 71, 73, 10, 16, 70, 64, 11, 25, 69, 55,  // 8
	12, 34, 68, 46, 13, 43, 67, 37, 18, 6, 62, 74, 19, 15, 61, 65,  // 12
	20, 24, 60, 56, 21, 33, 59, 47, 22, 42, 58, 38, 27, 5, 53, 75,  // 16
	28, 14, 52, 66, 29, 23, 51, 57, 30, 32, 50, 48, 31, 41, 49, 39  // 20
};
USHORT sym_81[5][81] = {    // d1  d2  st  c  r90
	0, 9, 18, 27, 36, 45, 54, 63, 72, 1, 10, 19, 28, 37, 46, 55, 64, 73, 2, 11,
	20, 29, 38, 47, 56, 65, 74, 3, 12, 21, 30, 39, 48, 57, 66, 75, 4, 13, 22, 31,
	40, 49, 58, 67, 76, 5, 14, 23, 32, 41, 50, 59, 68, 77, 6, 15, 24, 33, 42, 51,
	60, 69, 78, 7, 16, 25, 34, 43, 52, 61, 70, 79, 8, 17, 26, 35, 44, 53, 62, 71, 80,  // d1
	80, 71, 62, 53, 44, 35, 26, 17, 8, 79, 70, 61, 52, 43, 34, 25, 16, 7, 78, 69,
	60, 51, 42, 33, 24, 15, 6, 77, 68, 59, 50, 41, 32, 23, 14, 5, 76, 67, 58, 49,
	40, 31, 22, 13, 4, 75, 66, 57, 48, 39, 30, 21, 12, 3, 74, 65, 56, 47, 38, 29,
	20, 11, 2, 73, 64, 55, 46, 37, 28, 19, 10, 1, 72, 63, 54, 45, 36, 27, 18, 9, 0,  // d2
	56, 55, 54, 59, 58, 57, 62, 61, 60, 65, 64, 63, 68, 67, 66, 71, 70, 69, 74, 73,
	72, 77, 76, 75, 80, 79, 78, 29, 28, 27, 32, 31, 30, 35, 34, 33, 38, 37, 36, 41,
	40, 39, 44, 43, 42, 47, 46, 45, 50, 49, 48, 53, 52, 51, 2, 1, 0, 5, 4, 3,
	8, 7, 6, 11, 10, 9, 14, 13, 12, 17, 16, 15, 20, 19, 18, 23, 22, 21, 26, 25, 24,  //st
	80, 79, 78, 77, 76, 75, 74, 73, 72, 71, 70, 69, 68, 67, 66, 65, 64, 63, 62, 61,
	60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41,
	40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21,
	20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0,  // c
	8, 17, 26, 35, 44, 53, 62, 71, 80, 7, 16, 25, 34, 43, 52, 61, 70, 79, 6, 15,
	24, 33, 42, 51, 60, 69, 78, 5, 14, 23, 32, 41, 50, 59, 68, 77, 4, 13, 22, 31,
	40, 49, 58, 67, 76, 3, 12, 21, 30, 39, 48, 57, 66, 75, 2, 11, 20, 29, 38, 47,
	56, 65, 74, 1, 10, 19, 28, 37, 46, 55, 64, 73, 0, 9, 18, 27, 36, 45, 54, 63, 72 }; // r90


USHORT sym_f9[3][9] = {  // d1 d2 st
	0, 10, 20, 30, 40, 50, 60, 70, 80,  // d1
	8, 16, 24, 32, 40, 48, 56, 64, 72,  // d2
	28, 31, 34, 37, 40, 43, 46, 49, 52   // st
};

USHORT  sym_tcor[3][9] = {
	0, 2, 1, 4, 3, 6, 5, 8, 7,   // central
	0, 1, 2, 4, 3, 6, 5, 8, 7,   // 3 fix
	0, 2, 3, 4, 1, 6, 7, 8, 5,   // r90
};
