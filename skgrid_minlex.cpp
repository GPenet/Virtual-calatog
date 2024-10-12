
//#define SK0FDEBUGGINGBAND
//#define SK0FDEBUGGING_EXT

int C_transpose_d[81] = {
	0, 9, 18, 27, 36, 45, 54, 63, 72, 1, 10, 19, 28, 37, 46, 55, 64, 73,
	2, 11, 20, 29, 38, 47, 56, 65, 74, 3, 12, 21, 30, 39, 48, 57, 66, 75,
	4, 13, 22, 31, 40, 49, 58, 67, 76, 5, 14, 23, 32, 41, 50, 59, 68, 77,
	6, 15, 24, 33, 42, 51, 60, 69, 78, 7, 16, 25, 34, 43, 52, 61, 70, 79,
	8, 17, 26, 35, 44, 53, 62, 71, 80,
};

#include <utility>
#include <limits.h>
#include "sk0__h.h"
#include "skb_permband.h"
#include "skb_permband_cpp.h"
#include "skb_permgridcells.h"
#include "skb_permgridcells_cpp.h"
#define SK0FTPERMBASE
#define SK0FSMALLBANDFUNCTIONS
#include "C:\_cinc\sk0_loads_cpp.h"
//#include "maingp_user.h"
/*
// ________________________ select what has to be loaded in sk0__h.h
#define SK0FDEBUGGING
// SK0FT128 contains include sk_bitfield.h
#define SK0FTPERM1296h"
*/
struct TPGC {
	char t[648][19];
	int nt, bs_id[6], nv, nh;
}tpgc;

//===================================================================================== used DLLs
extern "C" __declspec(dllimport)  void SkbGetMappingInt(int* a, BANDPERM * b);
extern "C" __declspec(dllimport) int SkbGetAutoMorphs(int bandid, BANDPERM * *tpermret);
extern "C" __declspec(dllimport) void SkbGetBandChar(int bandid, char* bchar27);
//===================================================================================== Entries 
extern "C" __declspec(dllexport) void SkbsGetMin(int* g81s, int* g81min);
extern "C" __declspec(dllexport) void SkbsGetMinChar(char* g81sc, int* g81min);
extern "C" __declspec(dllexport) TPGC * SkbsSetModeWithAutos();
//==================================================== DLL code 

struct WGMIN {
	BANDPERM pg[3], pd[3];
	BANDPERM pmin, p1, p2,pcomp,pmorph;
	BANDPERM* t_auto_b1;
	BANDPERM tvalidautom_b1[108];
	GRIDPERM gperm_min;
	GRIDPERMCELLS gpermcells;
	int getauto;
	WGMIN() {
		getauto = 0;// no need to gat auto morphs
	}
	int itranspose,ngvert, ngauto;
	int ip; // bands perm in Getmin 
	int b1min[27], b2min[27], b3min[27],btemp[27];
	int* wb2, * wb3, b2n[27], b3n[27], b2n2[27], b3n2[27];
	int* sb2, *sb3,* b2comp, * b3comp;
	int * g0,gd[81], n_auto_b1;
	int isnewmin, ismineq;
	int MinCompare();
	void MorphB2B3();
	int SeeNewMin();
	void GetMin(int* g);
	void ApplyGridPerm();
#ifdef  SK0FDEBUGGINGBAND
	void Dumpfout(char* ze);
#endif
}wgmin;

int WGMIN::MinCompare() {
	int ir2 = BandCompare(b2comp, b2min);
	if (ir2 > 0) return 1;
	if (ir2 < 0) {
		memcpy(b2min, b2comp, 4 * 27);
		memcpy(b3min, b3comp, 4 * 27);
		isnewmin= ismineq = 1;
		return -1;
	}
	else {	// now same band 2 see band 3
		int ir3 = BandCompare(b3comp, b3min);
		if (ir3 > 0) return 1;
		if (ir3 == 0) {	ismineq ++; return 2;}  // same; 
		// now ir3<0  new min through b3
		memcpy(b3min, b3comp, 4 * 27);
		isnewmin = ismineq = 1;
		return -1;
	}
}
void WGMIN::MorphB2B3() {
	pmorph.MorphOrdered(sb2, b2comp);
	pmorph.MorphOrdered(sb3, b3comp);
	if (b2comp[0] > b3comp[0]) {// exchange b2 b3
		memcpy(btemp, b2comp, 4 * 27);
		memcpy(b2comp, b3comp, 4 * 27);
		memcpy(b3comp, btemp, 4 * 27);
	}
}
int WGMIN::SeeNewMin() {
	isnewmin=ismineq = 0;
	int isminauto = 0;
	// find first min see if it is a new min
	pmin = pmorph=p1;
	sb2 = wb2; sb3 = wb3; b2comp = b2n; b3comp = b3n;
	MorphB2B3(); MinCompare();
	if (n_auto_b1) {
		sb2 = b2n; sb3 = b3n; b2comp = b2n2; b3comp = b3n2;
		for (int i = 0; i < n_auto_b1; i++) {// if nauto_b1 get min "auto"
			pmorph = t_auto_b1[i];
			MorphB2B3();
			int ir = MinCompare();
			if (ir < 0) {
				pmin.Chain(p1, pmorph);
				isminauto = 1;
			}
			else if (ir == 2) {
				if (ismineq==1) {
					pmin.Chain(p1, pmorph);
				}
			}
		}
	}
	if (!isnewmin) {
		if (ismineq) {// Count and Apply 			
			ngvert++;
			ApplyGridPerm();
		}
		return 0;
	}
	ngvert = 1;
	tpgc.nt = 0;// if a new min  see if auto morphs are = 	
	tvalidautom_b1[0].InitBase(p1.i416);// always direct, no change
	ngauto = 1;	
	sb2 = b2min; sb3 = b3min;
	for (int i = 0; i < n_auto_b1; i++) {
		ismineq = 0;
		pmorph = t_auto_b1[i];
		MorphB2B3(); MinCompare();// can not be new min
		if (ismineq)  tvalidautom_b1[ngauto++] = pmorph;
	}
	ApplyGridPerm();
	return 1;
}
void Chain19(char* a, char* b, char* c) {
	c[0] = a[0];// copy transpose first
	int r1[9], r2[9], c1[9], c2[9];
	//switch to 0-8 in rows and cols
	for (int i = 0; i < 9; i++) {
		r1[i] = a[i + 1] - '1';
		c1[i] =a[i+10] - '1';
		r2[i] = b[i + 1] - '1';
		c2[i] = b[i + 10] - '1';
	}
	// chain in 0-8 mode and send back 
	for (int i = 0; i < 9; i++) {
		c[i+1] = r1[r2[i]]+'1';
		c[i+10] = c1[c2[i]]+'1';
	}

}
void WGMIN::ApplyGridPerm() {
	if (!getauto) {	tpgc.nt += ngauto;	return;	}
	char wexp1[20]; wexp1[19] = 0;// first
	char wexp2[20]; wexp2[19] = 0;// auto morph
	char wexp3[20]; wexp3[19] = 0;// chained 1+2
	pmorph = pmin;
	sb2 = wb2; sb3 = wb3; b2comp = b2n; b3comp = b3n;
	MorphB2B3();
	int d6s[6], d6min[6], d6p[6];
	// get the raws first col digits rows 4-9
	{
		int x = pmin.cols[0];
		d6s[0] = wb2[x]; d6s[1] = wb2[x + 9]; d6s[2] = wb2[x + 18];
		d6s[3] = wb3[x]; d6s[4] = wb3[x + 9]; d6s[5] = wb3[x + 18];
	}
	// get the minlex first col digits rows 4-9
	{
		d6min[0] = b2min[0]; d6min[1] = b2min[9]; d6min[2] = b2min[18];
		d6min[3] = b3min[0]; d6min[4] = b3min[9]; d6min[5] = b3min[18];
	}
	// morph t6s to t6p using digit map
	for (int i = 0; i < 6; i++) {
		d6p[i] = pmin.map[d6s[i]];
	}
	// build now the rows 
	int rr[9];
	memcpy(rr, pmin.rows, 12);
	for (int i = 0; i < 6; i++) {
		register int x = d6min[i];
		for (int j = 0; j < 6; j++) {
			register int y = d6p[j];
			if (x != y)continue;
			rr[3 + i] = 3 + j;
			break;
		}
	}
	int* rrp =  tperm3cols[ip];// must chain to first perm
	int rrf[9];
	for (int i = 0; i < 9; i++)rrf[i] = rrp[rr[i]];
	int gout[81];
	GRIDPERM myp; myp.Import(itranspose, pmin, rrf);
	myp.Morph(g0, gout);
	myp.Export(wexp1);
	memcpy(tpgc.t[tpgc.nt++], wexp1, 19);
	if (!ngauto) return;
	// must produce all auto morphs
	for (int ia = 0; ia < ngauto; ia++) {
		pmorph = tvalidautom_b1[ia];
		// get the raws first col digits rows 4-9
		{
			int x = pmorph.cols[0],*wb2=&gout[27],*wb3= &gout[54];
			d6s[0] = wb2[x]; d6s[1] = wb2[x + 9]; d6s[2] = wb2[x + 18];
			d6s[3] = wb3[x]; d6s[4] = wb3[x + 9]; d6s[5] = wb3[x + 18];
		}
		// morph t6s to t6p using digit map
		for (int i = 0; i < 6; i++) {
			d6p[i] = pmorph.map[d6s[i]];
		}
		int rra[9];
		memcpy(rra, pmorph.rows, 12);
		for (int i = 0; i < 6; i++) {
			register int x = d6min[i];
			for (int j = 0; j < 6; j++) {
				register int y = d6p[j];
				if (x != y)continue;
				rra[3 + i] = 3 + j;
				break;
			}
		}
		GRIDPERM myp2; myp2.Import(0, pmorph, rra);
		if (ia) {
			myp2.Export(wexp2);
			Chain19(wexp1,wexp2, wexp3);
			memcpy(tpgc.t[tpgc.nt++], wexp3, 19);
		}
	}
}
void WGMIN::GetMin(int* g) {
	tpgc.nt = 0;
	int minindex, ii; // diagonal symmetry
	memset(b2min, 9, sizeof b2min);
	g0 = g;
	for (int i = 0; i < 81; i++)	gd[i] = g[C_transpose_d[i]];
	// Getindex band/stack and min index
	{
		SkbGetMappingInt(g, &pg[0]); 
		tpgc.bs_id[0] = minindex = pg[0].i416;
		SkbGetMappingInt(&g[27], &pg[1]); 
		tpgc.bs_id[1]=ii = pg[1].i416;
		if (ii < minindex)minindex = ii;
		SkbGetMappingInt(&g[54], &pg[2]);
		tpgc.bs_id[2] = ii = pg[2].i416;
		if (ii < minindex)minindex = ii;
		SkbGetMappingInt(gd, &pd[0]); 
		tpgc.bs_id[3] = ii = pd[0].i416;
		if (ii < minindex)minindex = ii;
		SkbGetMappingInt(&gd[27], &pd[1]); 
		tpgc.bs_id[4] = ii = pd[1].i416;
		if (ii < minindex)minindex = ii;
		SkbGetMappingInt(&gd[54], &pd[2]); 
		tpgc.bs_id[5] = ii = pd[2].i416;
		if (ii < minindex)minindex = ii;
		// get the first band min lex and the auto morphs 
		char b1char[27];
		SkbGetBandChar(minindex, b1char);
		n_auto_b1 = SkbGetAutoMorphs(minindex, &t_auto_b1);
		for (int i = 0; i < 27; i++)	b1min[i] = b1char[i] - '1';

	}
	// try each start equal to min index
	int* bx[3] = { g,&g[27] , &g[54] };
	int* bxd[3] = { gd,&gd[27] , &gd[54] };
	for (ip = 0; ip < 3; ip++) {
		int* p = tperm3[ip];
		if (pg[p[0]].i416 == minindex) {
			itranspose = 0;
			p1 = pg[p[0]]; wb2 = bx[p[1]]; wb3 = bx[p[2]];
			SeeNewMin();
		}
		if (pd[p[0]].i416 == minindex) {
			itranspose = 1;
			p1 = pd[p[0]]; wb2 = bxd[p[1]]; wb3 = bxd[p[2]];
			SeeNewMin();
		}
	}
}

//======================================================= entries code 
TPGC* SkbsSetModeWithAutos () {
	wgmin.getauto=1;
	return & tpgc;
}

void SkbsGetMin(int* g, int* g81min) {
	wgmin.GetMin(g);
	memcpy(g81min, wgmin.b1min, 4 * 27);
	memcpy(&g81min[27], wgmin.b2min, 4 * 27);
	memcpy(&g81min[54], wgmin.b3min, 4 * 27);
	tpgc.nv = wgmin.ngvert;
	tpgc.nh = wgmin.ngauto;

}
void SkbsGetMinChar(char* g81sc, int* g81min) {
	int g[81];
	for (int i = 0; i < 81; i++)	g[i] = g81sc[i] - '1';
	SkbsGetMin(g, g81min);
}

//======================================================== debugging code unused here
#ifdef  SK0FDEBUGGINGBAND
void WGMIN::Dumpfout(char* ze){
	if (ngauto==1) return;
	if (ngauto == 3) {
		register int x= pd[0].i416;
		if(x== pd[1].i416 && x == pd[2].i416)	return;
	}

	//n_auto_b1 = SkbGetAutoMorphs(j, &tt);
	BANDPERM* tt;
	int ii[3], iid[3];
	fout1 << ze << " ";
	for (int i = 0; i < 3; i++) {
		register int j= pg[i].i416; fout1 << j << " ";
		ii[i] = SkbGetAutoMorphs(j, &tt);
	}
	fout1 << " d ";
	for (int i = 0; i < 3; i++) {
		register int j = pd[i].i416; fout1 << j << " ";
		iid[i] = SkbGetAutoMorphs(j, &tt);
	}
	fout1 << " nauto ";
	for (int i = 0; i < 3; i++)   fout1 << ii[i] << " "; 
	for (int i = 0; i < 3; i++) fout1 << iid[i] << " ";
	fout1 << "nv " << ngvert << " ngauto " << ngauto;
	fout1 << " total auto " << ngvert * ngauto << endl; ;
}


void Fout12(char * ze) {
	wgmin.Dumpfout(ze);
}
#endif
