
//                    0  1  2   3   4   5     6   7
int floors_2d[36] = { 03,05,011,021,041,0101,0201,0401,  
   //  8 9    10 11  12   13   14   15  16  17  18   19  20 
      06,012,022,042,0102,0202,0402,014,024,044,0104,0204,0404,
  // 21   22  23  24   25    26  27   28   29 
	030,050,0110,0210,0410, 060,0120,0220,0420, 
  // 30  31   32     33   34      35
	0140,0240,0440,  0300,0500,  0600 };
int floors2d_2bands[36] = { 0,0,1,1,1,1,1,1,0,1,1,1,1,1,1, //14
							1,1,1,1,1,1,0,0,1,1,1, //25
							0,1,1,1,1,1,1,0,0,0 };
int floors2d_band_stack_free[36] = { 4,4,2,2,2,1,1,1,4,2,2,2,1,1,1,
							2,2,2,1,1,1,4,4,0,0,0,
							4,0,0,0,0,0,0,4,4,4 };
int floors2d_same_band_stack[9] = { 0,1,8,21,22,26,33,34,35 };
int floors2d_same_band_stack_third[9] = { 2,1,0,5,4,3,8,7,6 };

int floors_3d[84] = {
	07, 013, 023, 043, 0103, 0203, 0403, 015, 025, 045, 0105, 0205, 0405, 031, 051, 0111,
	0211, 0411, 061, 0121, 0221, 0421, 0141, 0241, 0441, 0301, 0501, 0601, 016, 026, 046, 0106,
	0206, 0406, 032, 052, 0112, 0212, 0412, 062, 0122, 0222, 0422, 0142, 0242, 0442, 0302, 0502,
	0602, 034, 054, 0114, 0214, 0414, 064, 0124, 0224, 0424, 0144, 0244, 0444, 0304, 0504, 0604,
	070, 0130, 0230, 0430, 0150, 0250, 0450, 0310, 0510, 0610, 0160, 0260, 0460, 0320, 0520, 0620,// 80 lim 3=84
	0340, 0540, 0640, 0700 };
// must follow floors_3d[84] in  go-17sol
int floors_4d[126] = { 017, 027, 047, 0107, 0207, 0407, 033, 053, 0113, 0213, 0413, 063,
	0123, 0223, 0423, 0143, 0243, 0443, 0303, 0503, 0603, 035, 055, 0115, 0215, 0415, 065, 0125,
	0225, 0425, 0145, 0245, 0445, 0305, 0505, 0605, 071, 0131, 0231, 0431, 0151, 0251, 0451, 0311,
	0511, 0611, 0161, 0261, 0461, 0321, 0521, 0621, 0341, 0541, 0641, 0701, 036, 056, 0116, 0216,
	0416, 066, 0126, 0226, 0426, 0146, 0246, 0446, 0306, 0506, 0606, 072, 0132, 0232, 0432, 0152,
	0252, 0452, 0312, 0512, 0612, 0162, 0262, 0462, 0322, 0522, 0622, 0342, 0542, 0642, 0702, 074,
	0134, 0234, 0434, 0154, 0254, 0454, 0314, 0514, 0614, 0164, 0264, 0464, 0324, 0524, 0624, 0344,
	0544, 0644, 0704, 0170, 0270, 0470, 0330, 0530, 0630, 0350, 0550, 0650, 0710, 0360, 0560, 0660,
	0720, 0740, };

