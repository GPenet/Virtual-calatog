// all these tables are used in many functions as
#pragma once
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;


// compatibility g++ visual studio
#include "C:\_cinc\sk0_f_platform.h"

// shared bitsets and type def  

#include "C:\_cinc\sk0_f_bitsets_typedef.h"


//=========== preprocessor  base sequences 

#define SKT_MORPHTOA \
int band[27];\
for (int i = 0; i < 9; i++) {\
band[i] = p.m[z[p.c[i]]];\
band[i + 9] = p.m[z[p.c[i] + 9]];\
band[i + 18] = p.m[z[p.c[i] + 18]];	}

#define SKT_MORPHTOP \
int band[27];\
for (int i = 0; i < 9; i++) {\
band[i] = p.map[z[p.cols[i]]];\
band[i + 9] = p.map[z[p.cols[i] + 9]];\
band[i + 18] = p.map[z[p.cols[i] + 18]];}

#ifdef SK0FDEBUGGING
//____________________________________sk0_cpp_debugging
extern void Coutg9(char * zl, int endl = 1);
extern void CoutGrid(char * zc);
extern char * Char9out(int w);
extern char * Char27out(int w);
extern char * Char32out(int w);
extern char * Char54out(uint64_t v);
extern char * Char64out(uint64_t v);
extern char * Char2Xout(uint64_t v);
extern char * CoutGintPuzzle(GINT * t, int n);
//extern char * CoutGint64Puzzle(GINT * t, int n);
extern void BandDump(int* a, const char* lib);
extern void GridDump(int* a, const  char* lib);
#endif

#ifdef SK0FFLOORS
//____________________________________sk0_cpp_floors
// possible 2_templates 3_templates 4 templates 
extern int floors_2d[36];
extern int floors2d_2bands[36];
extern int floors2d_band_stack_free[36];
extern int floors2d_same_band_stack[9];
extern int floors2d_same_band_stack_third[9];
extern int floors_3d[84];
extern int floors_4d[126];
#endif

#ifdef SK0FLOOKUP

//__________________________________________sk0_cpp_misc_lookup
extern int TblMult3[9];  // 3*i
extern int TblMult9[9];  // 9*i
extern int C_minirow[81];
extern int * Tbldiv3; //i/3
extern int C_row[81];
extern int * Tblofftorow;  // i/9 cell to row
extern int C_col[81];
extern int * TblMod9; //  i%9 cell to column
extern int C_box[81];
extern int * Tblofftobox; // cell in band to relative box in band
extern int C_stack[81];
extern int C_box_rel[81]; // relative position in the box
extern int * TblCelltoBox;

extern int  C_transpose_c[81];
extern int  C_transpose_d[81];
extern int  C_transpose_d2[81];
extern int  C_transpose_r[81];// rotate col 9 to row 1
extern int  C_transpose_rm[81]; // rotate row1 to col9

extern int  C_mod27[81];
extern int * Tbloffset; // i%27  giving cell to offset in a band
extern int C_div27[81];
extern int * TblBoard_Block; //  i/27  giving cell -> band 
extern int C_To128[81];
extern int From_128_To_81[128];
extern uint32_t mini_pairs_tripletsbf[36];
extern int box_col_to_row[512];// Flash transpose a box
extern int treverse_mini[8];// Flash reverse three bits
extern int tband_box[6], tband_row[3], tband_box_skrink[3];
#endif

#ifdef SK0FSMALLBANDFUNCTIONS
//_____________________________________sk0_cpp_smallbandfunctionse

extern int BandCompare(int* a, int* b);
extern void BandReOrder(int* d);
#endif

#ifdef SK0FOTHERS
//_____________________________________sk0_cpp_others

extern const  char *  empty_puzzle;
extern const char *  puzstart;
extern char * Blancs(int n, int no);
extern void Sort_uint32_t(uint32_t * t, uint32_t nt);
extern int AddUA64(uint64_t * t, uint32_t & nt, uint64_t ua);
extern int AddUA32(uint32_t * t, uint32_t & nt, uint32_t ua);
extern int AddUA32NoSubset(uint32_t * t, uint32_t & nt, uint32_t ua);
#endif

#ifdef SK0FSYMMETRY
//___________________________________sk0_cpp_symmetry
//================= symmetry of given sk0cpp_symmetry
extern USHORT sh_36[36][2];
extern USHORT sv_36[36][2];
extern USHORT sd1_36[36][2];
extern USHORT sd2_36[36][2];
extern USHORT sst_36[36][2];
extern USHORT sc_40[40][2];
extern USHORT sr90_20[20][4];
extern USHORT sym_81[5][81];
extern USHORT sym_f9[3][9];
extern USHORT  sym_tcor[3][9];
#endif


#ifdef SK0FMISCLOOKUP
//_____________________________________sk0_cpp_misc_lookup
extern byte cellsInGroup[27][9];
extern byte miniline[54][3]; // row order
extern byte box_miniline[54][3]; // box order
extern uint64_t tbl_2x_cols[9]; // column bit field in 2x mode(2x27 in 2x32)
extern uint64_t tbl_2x_stacks[3];
extern uint64_t tbl_2x_stacksn[3];
extern int C_rbc27[81];
#endif


#ifdef SK0FT128
//________________________________sk0_cpp_t128
typedef union T128 {// new definition closer to GINTx
	uint64_t    u64[2];
	uint8_t     u8[16];
	uint16_t    u16[8];
	uint32_t    u32[4];
	__m128i		u128;
} T128;
class BUILDSTRING;
#include "C:\_cinc\sk_bitfields.h" 
//  here included a merged version of fsss2 and Gp 128 bits base


extern const T128 maskLSB[129]; // not in fss2
extern const T128 maskffff; // not in fss2
extern T128 cellsInBandBMx[6];
extern T128 cellsInHouseBMx[27];
extern T128 band3xBM[6];
extern T128 units3xBM[27];
extern T128 cell_z3x[81];
#endif

#ifdef SK0FTPERMBASE
//_______________________________sk0_cpp_tpermbase
extern int tperm6[6][3];
extern int tperm3[3][3]; // here all boxes are once in pos 1
extern int tperm6cols[6][9]; // no col perm in stacks
#endif

#ifdef SK0FTPERM1296
//_________________________________sk0cpp_tpermorder1296
extern int tpermorder[1296][9];
#endif

#ifdef SK0FZZ
// =======================================sk0_cpp_zcellfix (obsolete

//!Small class containing the permanent data for a cell
struct CELL_FIX  {
	int
		i8,		///< cell index (0-80)
		el,     ///< row index (0-8)
		pl,     ///< column index (0-8)
		plu,     /// same 9 17
		eb,     ///< box index(0-8) 
		ebu,     ///< box index(18_��) 
		pb;     ///< relative position in the box (0-8)
	char pt[5];	///< printing string like R4C9 with \0

	int ObjCommun(const CELL_FIX *p8) const {
		return((el == p8->el) || (pl == p8->pl) || eb == p8->eb);
	}
	inline void GetRegions(int * tt) { tt[0] = el; tt[1] = plu; tt[2] = ebu; }
	int GetTableRegions(USHORT * tt, CELL_FIX & cell2);
};
extern  CELL_FIX  cellsFixedData[81];

//__________________________________________________sk0_cpp_zcombine
/* COMBINE is a small module giving combination
for a given size   (maths C n;p )

the goal is to have a simpler code, not to improve the performance

*/
class COMBINE
{
public:
	UINT inds[15],  // internal table size p
		p,      // maxi 15
		lim,    // set to p-1 final index at the end
		n;      // numer of objects in the table
	USHORT * entry, *output;
	void Sort(); // internal function formating the output

public:
	void First(int ne, int pe, USHORT * d, USHORT * f); // initial
	int Next(); // get next group of index
};



//========================== various old struct or UA collection

/* class VV9 is a small class
extracting a row or a column   from a GG described puzzle

to see later another use of VV9
*/
class VV9{
public: char v[10];
		VV9(){ v[9] = 0; };
		//   void base(){for(USHORT i=0;i<9;i++)v[i]=(char)i;}
		void row(char * puz, USHORT r){
			for (USHORT i = 0, ii = 9 * r; i<9; i++)
				v[i] = puz[ii++];
		}
		void col(char * puz, USHORT c) {
			for (USHORT i = 0, ii = c; i<9; i++, ii += 9)
				v[i] = puz[ii];
		}

};

#endif
