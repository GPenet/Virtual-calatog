  
#include "C:\_cinc\sk0__h.h"
#include "C:\_cinc\sk0_cpp_tpermbase.h"
#include "C:\_cinc\sk0_cpp_smallbandfunctionse.h"


#include "..\src\skg_gminlex_struct.h"
#include "..\src\skg_tgang_cpp.h"


void GANGMINLEX::SortTcols() {
	int n = 0;
	for (int i = 0; i < ntcols; i++)
		if (tcols_count[i] == 3)tcolss[n++] = i;
	ntcs3 = n;
	for (int i = 0; i < ntcols; i++)
		if (tcols_count[i] == 2)tcolss[n++] = i;
	for (int i = 0; i < ntcols; i++)
		if (tcols_count[i] == 1)tcolss[n++] = i;

}
void GANGMINLEX::Init(int* o) {
	goback = 0;
	memcpy(g0, o, sizeof g0);
	SetColbfNtcols();
	if (ntcols > 5) SetPairscols();
	if (ntcols < 9) {
		SortTcols();
		Settripletscols();
	}
	switch (ntcols) {
	case 3: Go3(); return;
	case 5: Go5(); return;
	case 6: Go6(); return;
	case 7:
	case 8:Go78(); return;
	case 9: Go9(); return;
	}
}

inline void GANGMINLEX::SetColbfNtcols() {
	memset(gb3, 0, sizeof gb3);
	ntcols = 0;
	for (int istk = 0, k = 0, icol = 0; istk < 3; istk++)
		for (int i = 0; i < 3; i++, icol++) {
			for (int j = 0; j < 3; j++, k++) {
				register int c = g0[k];
				gb3[icol] |= 1 << c;
				gb3d[icol][j] = c;
				gdcols[c][istk] = icol;
			}
			register int v = gb3[icol];
			for (int j = 0; j < ntcols; j++) {
				if (v == tcols[j]) {
					tcols_count[j]++;
					tcols_cols[j] |= 1 << icol;
					tcols_stk[j] |= 1 << istk;
					v = 0; break;
				}
			}
			if (v) {
				tcols_count[ntcols] = 1;
				tcols_cols[ntcols] = 1 << icol;
				tcols_stk[ntcols] = 1 << istk;
				tcols[ntcols++] = v;
			}
		}

}
int GANGMINLEX::NpairsStack(int ip, int s1, int s2, int n0) {
	int n = 0, * d1 = tcols_dstack[s1], * d2 = tcols_dstack[s2];
	for (int i = 0; i < 3; i++) {
		int v1 = d1[i];
		for (int j = 0; j < 3; j++) {
			int v1v2 = v1 & d2[j];
			if (_popcnt32(v1v2) == 2)
				spairs[n0 + n++].Enter(v1v2, ip, 3 * s1 + i, 3 * s2 + j);
		}
	}
	return n;
}
int GANGMINLEX::NtripletsStack(int ip, int s1, int s2, int n0) {
	int n = 0, * d1 = tcols_dstack[s1], * d2 = tcols_dstack[s2];
	for (int i = 0; i < 3; i++) {
		int v1 = d1[i];
		for (int j = 0; j < 3; j++) {
			int v1v2 = v1 & d2[j];
			if (_popcnt32(v1v2) == 3) {
				int nx = n0 + n ;
				//cout << "found triplet nx=" << nx << endl;
				striplets[n0 + n++].Enter(v1v2, ip, 3 * s1 + i, 3 * s2 + j);
				//striplets[nx].Dump();
				//striplets[n0 + n++].Enter(v1v2, ip, 3 * s1 + i, 3 * s2 + j);

			}
		}
	}

	return n;
}
void GANGMINLEX::SetPairscols() {
	isp2 = 0;
	if ((npst[0] = NpairsStack(0, 0, 1, 0)) == 2) isp2 = 1;
	if ((npst[1] = NpairsStack(1, 0, 2, npst[0])) == 2) isp2 = 1;
	if ((npst[2] = NpairsStack(2, 1, 2, npst[0] + npst[1])) == 2) isp2 = 1;
	nt2x2 = npst[0] + npst[1] + npst[2];
}
void GANGMINLEX::Settripletscols() {
	ntst[0] = NtripletsStack(0, 0, 1, 0);
	ntst[1] = NtripletsStack(1, 0, 2, ntst[0]);
	ntst[2] = NtripletsStack(2, 1, 2, ntst[0] + ntst[1]);
	nt2x3 = ntst[0] + ntst[1] + ntst[2];
}


int GANGMINLEX::ValidGangMinlex(int i) {
	igang = i;
	goback = 1;
	// build cmap dmap cellmap
	{
		register int r;
		bitscanforward(r, m1); dmap[r] = 0; bitscanforward(r, m2); dmap[r] = 1;
		bitscanforward(r, m3); dmap[r] = 2; bitscanforward(r, m4); dmap[r] = 3;
		bitscanforward(r, m5); dmap[r] = 4; bitscanforward(r, m6); dmap[r] = 5;
		bitscanforward(r, m7); dmap[r] = 6; bitscanforward(r, m8); dmap[r] = 7;
		bitscanforward(r, m9); dmap[r] = 8;
	}
	{
		cmap[0] = c1n; cmap[1] = c2n; cmap[2] = c3n;
		cmap[3] = c4n; cmap[4] = c5n; cmap[5] = c6n;
		cmap[6] = c7n; cmap[7] = c8n; cmap[8] = c9n;
	}

	{// just colmap to cellmap same rows
		for (int irow = 0, i = 0; irow < 3; irow++) {
			register int drow = 9 * irow;
			for (int icol = 0; icol < 9; icol++, i++)
				cellmap[i] = drow + cmap[icol];
		}
	}
	// do reverse mapping
	{
		for (int i = 0; i < 9; i++) {
			revcmap[cmap[i]] = i;
			revdmap[dmap[i]] =i;
		}
		for (int irow = 0, i = 0; irow < 3; irow++) {
			register int drow = 9 * irow;
			for (int icol = 0; icol < 9; icol++, i++)
				revcellmap[i] = drow + revcmap[icol];
		}

	}
	return goback;
}

#define LOCATEUSING(A,B,C) 	{ register int r = C, * p = &gb3[st3d];\
if (r & *p) { A = *p; B = st3d; }else if (r & *++p) {A = *p; B = st3d + 1; }\
else { A = *++p; B = st3d + 2; }}

#define SPLIT3(X,A,B,C) int a, b;	bitscanforward(a, X);\
	bitscanreverse(b, X);A = 1 << a; C = 1 << b;B=X&~(A|C);

#define SPLIT3N(X,A,B,C) bitscanforward(A, X);	bitscanreverse(C, X);\
X^= 1 << A;bitscanforward(B, X);

#define SPLIT2(C,A,B) int a, b;	bitscanforward(a, C);\
	bitscanreverse(b, C);A = 1 << a; B = 1 << b;

#define END89(I) SPLIT2(m89, m8, m9) ValidGangMinlex(I);return 0
#define END8_9(I) m8 = mc8 & m89; m9 = mc9 & m89; ValidGangMinlex(I);return 0

#define END89F(I) SPLIT2(m89, m8, m9) return ValidGangMinlex(I)
#define END8_9F(I) m8 = mc8 & m89; m9 = mc9 & m89;return ValidGangMinlex(I) 

void GANGMINLEX::Go3() {
	{SPLIT3(tcols[0], m1,m2,m3) }
	{SPLIT3(tcols[1], m4, m5, m6) }
	{SPLIT3(tcols[2], m7, m8, m9) }
	{SPLIT3N(tcols_cols[0], c1n, c4n,c7n) }	
	{SPLIT3N(tcols_cols[1], c2n, c5n, c8n) }
	{SPLIT3N(tcols_cols[2], c3n, c6n, c9n) }
	ValidGangMinlex(0);	
}
void GANGMINLEX::Go5() {
	SortTcols();
	for (int i = 0; i < 5; i++)  {
		register int ii = tcolss[i];
		vxc[i] = tcols[ii];
		vxcc[i] = tcols_cols[ii];
	}
	int ip = 0;
	for ( ; ip < 3; ip++)if (ntst[ip]==3) {
		{
			int n = 0;
			for (int j = 0; j < nt2x3; j++)  {
				if(striplets[j].ip==ip)		go3t[n++] = striplets[j];
			}
		}
		//match triplets to sorted values 
		for (int i = 0; i < 3; i++) {
			got = go3t[i];
			register int v = got.v;
			if (v == vxc[0]) gota = got;
			else if (v == vxc[1]) gotb = got;
			else gotc = got;
		}
		c1n = gota.c1; c4n = gota.c2; m123 = gota.v;
		c2n = gotb.c1; c5n = gotb.c2; m456 = gotb.v;
		c3n = gotc.c1; c6n = gotc.c2; m789 = gotc.v;
		int c3 = vxcc[0] & ~((1 << c1n) | (1 << c4n));
		bitscanforward(c7n, c3);
		// match stack 3 not triplet to stack 2
		{
			register int v1 = vxc[3], c1 = vxcc[3],
				v2 = vxc[4], c2 = vxcc[4], x = v1 & m456;
			if (_popcnt32(x) == 2) {
				m457 = v1; m689 = v2;
				bitscanforward(c8n, c1);
				bitscanforward(c9n, c2);
			}
			else {
				m457 = v2; m689 = v1;
				bitscanforward(c8n, c2);
				bitscanforward(c9n, c1);
			}
		}
	}
	{SPLIT3(m123, m1, m2, m3) }
	m6 = m456 & m689; m45 = m456 & ~m6;
	m7 = m789 & m457; m89 = m789 & ~m7;
	{SPLIT2(m45, m4, m5)}
	{SPLIT2(m89, m8, m9)}
	ValidGangMinlex(1);
	return;
}
void GANGMINLEX::Go6() {
	SortTcols();
	for (int i = 0; i < 6; i++) {
		register int ii = tcolss[i];
		vxc[i] = tcols[ii];
		vxcc[i]= tcols_cols[ii];
	}
	// catch pairs
	{
		ngop = 0;
		for (int j = 0; j < nt2x2 / 2; j++) {
			gop[ngop++] = spairs[j];
		}
	}
	// call process for any triplet perm
	for (int i = 0; i < 6; i++) {
		int* p = tperm6[i];
		gota = striplets[p[0]]; gotb = striplets[p[1]]; gotc = striplets[p[2]];
		if (Go6b())return;
	}
	return;
}
int GANGMINLEX::Go6b() {
	int  vc8, vc9;
	// align pairs on triplets
	if (nt2x2) {
		gopa.v = gopb.v = gopc.v = 0;
		for (int i = 0; i < ngop; i++) {
			register int x = gop[i].v;
			if (x & gota.v)gopa = gop[i];
			else if(x& gotb.v)gopb = gop[i];
			else gopc = gop[i];
		}
		if ((!gopa.v) || (!gopc.v)) return 0;
	}
	c1n = gota.c1; c4n = gota.c2; m123 = gota.v;
	c2n = gotb.c1; c5n = gotb.c2; m456 = gotb.v;
	c3n = gotc.c1; c6n = gotc.c2; m789 = gotc.v;
	if (!nt2x2) goto gog4;
	else {
		// pairs 12  shared must be 124
		{
			register int y = gopa.v; // y is "12"
			for (int i = 3; i < 6; i++) {
				register int x = vxc[i], xc = vxcc[i];
				if (x & y) {// this is 124
					bitscanforward(c7n, xc);
					m4 = x & m456; m12 = y ;
					if (!m4)  return 0;		
					m3 = m123 & (~m12);
					{  SPLIT2(m12, m1, m2)}
					break;
				}
			}
		}
		{
			for (int i = 3; i < 6; i++) {
				register int x = vxc[i], xc = vxcc[i];
				if (!(x & m123)) {// this is  689 or 569
					bitscanforward(c9n, xc);
					vc9 = x;
				}
				else if(x & m3) {// this is 357 or 378
					bitscanforward(c8n, xc);
					vc8 = x;
				}
			}
		}
		//cout << endl;
		//gopa.Dump(); if (gopb.v)	gopb.Dump(); gopc.Dump();
		//gota.Dump(); gotb.Dump(); gotc.Dump();
		if (nt2x2 == 4) {//  124 357 689igang=2 
			m5 = vc8 & m456; m6 = vc9 & m456; m7 = vc8 & m789;
			{  SPLIT2(vc9 & m789, m8, m9)}
			return	ValidGangMinlex(2);

		}
		else {//  124 378 569igang=3 
			{  SPLIT2(m456 & (~m4), m5, m6)}
			m9 = vc9 & m789;
			{  SPLIT2(m789 & (~m9), m7, m8)}
			return 	ValidGangMinlex(3);
		}

	}

gog4: {	//  147 258 369igang=4 
	{SPLIT3(m123, m1, m2, m3) }// assign 123
	for (int i = 3; i < 6; i++) {
		register int x = vxc[i], xc = vxcc[i];
		if (x & m1) {// this is 147
			bitscanforward(c7n, xc);
			m4 = x & m456; m7 = x & m789;
		}
		else if (x & m2) {// this is 258
			bitscanforward(c8n, xc);
			m5 = x & m456; m8 = x & m789;
		}
		else {// this is 369
			bitscanforward(c9n, xc);
			m6 = x & m456; m9 = x & m789;
		}
	}
	return ValidGangMinlex(4);

}



	return 0;
}
void GANGMINLEX::Go78() {
	//cout << "entry go 78" << endl;
	for (int i = 0; i < 3; i++)if (ntst[i]) {
		//cout << "try stacks 12 for ip " << i << endl;
		{
			for (int j = 0; j < nt2x3; j++) {
				got = striplets[j];
				if (got.ip == i)  break;
			}
			int n = 0;
			for (int j = 0; j < nt2x2; j++) {
				if (spairs[j].ip == i)  gop[n++] = spairs[j];
			}
		}
		gopa = gop[0]; gopb = gop[1];	if (Go78b()) return;
		gopa = gop[1]; gopb = gop[0];	if (Go78b()) return;
		got.ChangeStack(); gop[0].ChangeStack(); gop[1].ChangeStack();
		gopa = gop[0]; gopb = gop[1];	if (Go78b()) return;
		gopa = gop[1]; gopb = gop[0];	if (Go78b()) return;
	}
}
int GANGMINLEX::Go78b() {
	int st3 = 2 - got.ip, st3d = 3 * st3;
	{
		m123 = got.v; m45 = gopa.v; m89 = gopb.v;
		m67 = 0x1ff ^ (m123 | m45 | m89);
		c1n = got.c1; c4n = got.c2;
		c2n = gopa.c1; c5n = gopa.c2;
		c3n = gopb.c1; c6n = gopb.c2;
		m456 = gb3[c2n]; m789 = gb3[c3n];
		m457 = gb3[c5n]; m689 = gb3[c6n];
		m6 = m67 & m456; m7 = m67 & m457;
		m12x = 0;

	}
	// locate 12x if exists
	{
		register int r = m123,*p=&gb3[st3d];
		if (_popcnt32(r & *p) >= 2) { m12x = *p; c7n = st3d; }
		else if (_popcnt32(r & *++p) >= 2) { m12x = *p; c7n = st3d+1; }
		else if (_popcnt32(r & *++p) >= 2) { m12x = *p; c7n = st3d + 2; }
	}
	if (m12x) {
		if (m12x == m123)goto go123;
		else {
			//cout<< Char9out(m12x) << " cas 12x" << endl;
			m12 = m123 & m12x;
			m3 = m123 & ~m12;
			if (m12x & m6)goto go126;
			else if (m12x & m45)goto go124;
			else  return 0;
		}
	}
	else {
		// use number of pairs to split the task
		if (nt2x2 == 6)goto go145;
		else if (nt2x2 == 4)goto go146;
		else if (nt2x2 == 2)goto go148;
		else return 0;
	}

	return 0;
go123: {//  123 458679 ig=5 123 468579 ig=6
	//cout << " case 123" << endl;
	int mc9 = 0;	LOCATEUSING(mc9,c9n, m7)
	int x = mc9 & m456, y = mc9 & m89;
	if (!(x*y)) return 0; // must be one of each
	{  SPLIT2(m123, m1, m3)}
	m2 = m123 & ~(m1 | m3);
	int ns = 3 +3* st3d;// sum of the columns of the stack 3
	c8n = ns - c7n - c9n;
	m9 = y; m8 = m89 & (~m9);
	int mc8 = gb3[c8n];
	if (x & m6) {//  458 679 ig=5
		{  SPLIT2(m45, m4, m5)}
		return 	ValidGangMinlex(5);	
	}
	else {// 468 579 ig = 6
		m4 = mc8 & m45; m5 = mc9 & m45;
		return 	ValidGangMinlex(6);
	}
	return 0;

}
go124: {
	m4 = m12x & m45;
	{  SPLIT2(m12, m1, m2)}// assign 12
	int mc8 = 0; LOCATEUSING(mc8, c8n, m3)
	int ns = 3 + 3 * st3d;// sum of the columns of the stack 3
	c9n = ns - c7n - c8n;
	int mc9 = gb3[c9n];
	if (mc8 & m45) {//356 789 ig=7  358 679 ig=8 
		if (!(mc9 & m7)) return 0;
		 m5 = mc8 & m45;
		 if (mc8 & m6) { END89F(7); }//356 789 ig=7
		else { END8_9F(8); }//	358 679 ig = 8
	}
	m5 = mc9 & m45;
	if (mc8 & m6) {//367 589 ig=9 368 579 ig=10
		if (mc8 & m7) {	END89F(9);	}
		else { END8_9F(10); }
	}
	if (mc8 & m7) return 0;//389 567 ig=11
	END89F(11);
}
go126: {// 7c 345 789 ig=12  8c 347 589 ig=13 348 579 ig=14
{  SPLIT2(m12, m1, m2)}// assign 12
int mc8 = 0; LOCATEUSING(mc8, c8n, m3)
int ns = 3 + 3 * st3d;// sum of the columns of the stack 3
c9n = ns - c7n - c8n;
int mc9 = gb3[c9n];
if (!(mc8 & m45)) return 0;
m4 = mc8 & m45;	m5 = mc9 & m45;
if (mc8 & m7) { END89F(13); } //347 589 ig = 13	
else if(mc8 & m89) {END8_9F(14);}//348 579 ig=14
	
else {// 7c 345 789 ig=12
	{  SPLIT2(m45, m4, m5)}// assign 4 5
	{ END89F(12); }
}
return 0;
}

go145: {// 267 389 ig=15   268 379 ig=16 
	// locate 145 if exists
	int mc7 = 0;
	{
		register int r = m45, * p = &gb3[st3d];
		if (_popcnt32(r & *p) == 2) { mc7 = *p; c7n = st3d; }
		else if (_popcnt32(r & *++p) == 2) { mc7 = *p; c7n = st3d + 1; }
		else if (_popcnt32(r & *++p) == 2) { mc7 = *p; c7n = st3d + 2; }
	}
	if (!mc7)return 0;
	if (!(mc7 & m123)) return 0;
	int mc8 = 0; LOCATEUSING(mc8, c8n, m6)
	int ns = 3 + 3 * st3d;// sum of the columns of the stack 3
	c9n = ns - c7n - c8n;
	int mc9 = gb3[c9n];
	m1 = mc7 & m123; m2 = mc8 & m123; m3 = mc9 & m123;
	if ((!m1) || (!m2) || (!m3)) return 0;
	{  SPLIT2(m45, m4, m5)}// assign 4 5
	if (mc8 & m7) { END89F(15); } // 267 389 ig=15	
	else { END8_9F(16); }//  268 379 ig=16 
}
go146: {//146 258 379 ig = 17
	int mc7 = 0; LOCATEUSING(mc7, c7n, m6)
	int mc9 = 0; LOCATEUSING(mc9, c9n, m7)
	int ns = 3 + 3 * st3d;// sum of the columns of the stack 3
	c8n = ns - c7n - c9n;
	int mc8 = gb3[c8n];
	m1 = mc7 & m123;m2 = mc8 & m123; m3 = mc9 & m123;
	m4 = mc7 & m45;	m5 = mc8 & m45;
	if (!m4) return 0;
	{END8_9F(17); }

}
go148: {// 148 259 367 ig=18 
	int mc9 = 0; LOCATEUSING(mc9, c9n, m7)
		m3 = mc9 & m123; m12=m123 & ~m3;
	if(!(mc9&m6)) return 0;	if (!m3) return 0;
	{  SPLIT2(m12, m1, m2)}// assign 12
	int mc7 = 0; LOCATEUSING(mc7, c7n, m1)
	int ns = 3 + 3 * st3d;// sum of the columns of the stack 3
	c8n = ns - c7n - c9n;
	int mc8 = gb3[c8n];
	m4 = mc7 & m45;	m5 = mc8 & m45;
	m8 = mc7 & m89;	m9 = mc8 & m89;
	return 	ValidGangMinlex(18);
}
return 0;
}

void GANGMINLEX::Go9() {
	//cout << "entry go 9 nt2x2="<<nt2x2 << endl;
	if (!nt2x2) { Go9_43(); return; }
	for (int j = 0; j < 3; j++)
		if (npst[j] == 2) { Go9_19_38(); return; }
	// now 39_42
	for (int i = 0; i < 3; i++) if (npst[i]) {
		//cout << "try stacks 12 for ip " << i << endl;
		{
			int n = 0;
			for (int j = 0; j < nt2x2; j++) {
				if (spairs[j].ip == i)  gop[n++] = spairs[j];
			}
		}
		//gop[0].Dump(); gop[1].Dump(); gop[2].Dump();
		for (int j = 0; j < 3; j++) {
			//cout << "try pair first " << j << endl;
			gopa = gop[j];
			if (Go9_39_42()) return;
			gopa.ChangeStack();
			if (Go9_39_42()) return;
		}
	}

}
void GANGMINLEX::Go9_19_38() {
	for (int i = 0; i < 3; i++)		if (npst[i] == 2) {
		{
			int n = 0;
			for (int j = 0; j < nt2x2; j++) {
				if (spairs[j].ip == i)  gop[n++] = spairs[j];
			}
		}
		gopa = gop[0]; 	gopb = gop[1];
		if (Go9_19_38B()) return;
		gopa.ChangeStack(); gopb.ChangeStack();
		if (Go9_19_38B()) return;
		gopa = gop[1]; 	gopb = gop[0];
		if (Go9_19_38B()) return;
		gopa.ChangeStack(); gopb.ChangeStack();
		if (Go9_19_38B()) return;
	}
}
int GANGMINLEX::Go9_19_38B() {
	// pattern stacks 1 2   123 456 789  124 357 689
	c1n = gopa.c1; c4n = gopa.c2;
	c3n = gopb.c1; c6n = gopb.c2;
	m12 = gopa.v; m89 = gopb.v;

	int s1 = c1n / 3, s2 = c4n / 3, s3 = 3 - s1 - s2,
		s1d = 3 * s1, s2d = 3 * s2, s3d = 3 * s3;
	c2n = (3 + 3 * s1d) - c1n - c3n;
	c5n = (3 + 3 * s2d) - c4n - c6n;
	int v124, v357;
	m123 = gb3[c1n]; m456 = gb3[c2n]; m789 = gb3[c3n];
	v124 = gb3[c4n]; v357 = gb3[c5n]; m689 = gb3[c6n];
	{
		register int r = m123 | v124 | m789 | m689;
		if (_popcnt32(r) != 8) return 0;
		m5 = 0x1ff ^ r;
	}
	m3 = m123 & ~m12; m4 = v124 & ~m12;
	m6 = m689 & ~m89; m7 = m789 & ~m89;
	if (nt2x2 == 2)goto go38;
	{
		int v7n = 0, v8n, v9n;
		for (int i = 0, j = s3d; i < 3; i++, j++) {
			register int vy = gb3[j], x = vy & m123;
			if (_popcnt32(x) == 2) {//12 or 13
				c7n = j; v7n = vy; break;
			}
		}
		if (!v7n) return 0;
		if (v7n & m3) {
			//cout << " seen 29_37" << endl;
			m1 = v7n & m12; m2 = m12 & ~m1;
			for (int i = 0, j = s3d; i < 3; i++, j++) {
				int vy = gb3[j];
				if (vy & m2) { c8n = j; v8n = vy; break; }
			}
			{
				int ns = 3 + 3 * s3d;// sum of the columns of the stack 3
				c9n = ns - c7n - c8n;
				v9n = gb3[c9n];
			}
			if (v8n & m4) return 0;	if (!(v8n & m89)) return 0;
			int vx = v7n & ~m123;
			if (vx & m4) {//258 679 ig=29 268 579 ig=30
				m8 = v8n & m89; m9 = v9n & m89;
				if (v8n & m5) return	ValidGangMinlex(29);
				else if (v8n & m6) return	ValidGangMinlex(30);
				else return 0;
			}
			else if (vx & m5) {//268 479 ig=31 278 469 ig=32
				m8 = v8n & m89; m9 = v9n & m89;
				if (v8n & m6) return	ValidGangMinlex(31);
				else if (v8n & m7) return	ValidGangMinlex(32);
				else return 0;
			}
			else if (vx & m6) {//258 479 ig=33 278 459 ig=34
				m8 = v8n & m89; m9 = v9n & m89;
				if (v8n & m5) return ValidGangMinlex(33);
				else if (v8n & m7) return	ValidGangMinlex(34);
				else return 0;
			}
			else if (vx & m7) {//268 459 ig=35
				if (!(v8n & m6)) return 0;
				m8 = v8n & m89; m9 = v9n & m89;
				return ValidGangMinlex(35);
			}
			else {//138 259 467 ig=36 138 269 457 ig=37
				m8 = vx; m9 = m89 & ~m8;
				if (v8n & m5) return ValidGangMinlex(36);
				else if (v8n & m6) 	return ValidGangMinlex(37);
				else return 0;
			}
		}
		else {
			{  SPLIT2(m12, m1, m2)}// assign 12
			for (int i = 0, j = s3d; i < 3; i++, j++) {
				int vy = gb3[j];
				if (vy & m3) { c8n = j; v8n = vy; break; }
			}
			{
				int ns = 3 + 3 * s3d;// sum of the columns of the stack 3
				c9n = ns - c7n - c8n;
				v9n = gb3[c9n];
			}

			int vx = v7n & ~m12;
			if (vx & m5) {	//348 679 ig=19  367 489 ig=20
				//368 479 ig=21   378 469 ig=22
				if (v8n & m4) {
					m8 = v8n & m89; if (!m8) return 0;
					m9 = v9n & m89;
					return ValidGangMinlex(19);
				}
				else if (v9n & m6) {
					if (!(v8n & m7)) return 0;
					m8 = v8n & m89; if (!m8) return 0;
					m9 = v9n & m89;
					return ValidGangMinlex(22);
				}
				else if (v8n & m7) {
					if (!(v8n & m6)) return 0;
					{  SPLIT2(m89, m8, m9)}// assign 89
					return ValidGangMinlex(20);
				}
				else if (v8n & m6) {
					m8 = v8n & m89; if (!m8) return 0;
					m9 = v9n & m89;
					return ValidGangMinlex(21);
				}
				else return 0;
			}
			else if (vx & m6) {// 358 479 ig=23 378 459 ig=24
				//389 457 ig=25
				if (v8n & m5) {
					m8 = v8n & m89; if (!m8) return 0;
					m9 = v9n & m89;
					return ValidGangMinlex(23);
				}
				else if (v8n & m7) {
					m8 = v8n & m89; if (!m8) return 0;
					m9 = v9n & m89;
					return ValidGangMinlex(24);

				}
				else if (!(v9n & m89)) {
					{  SPLIT2(m89, m8, m9)}// assign 89
					return ValidGangMinlex(25);
				}
				else return 0;
			}
			else if (vx & m89) {//345 679 ig=26 356 479 ig=27
				//359 467 ig=28
				if (!(v8n & m5)) return 0;
				m8 = vx; m9 = m89 & ~m8;
				if (v8n & m4)	return ValidGangMinlex(26);
				else if (v8n & m6) return ValidGangMinlex(27);
				else if (v8n & m9) return ValidGangMinlex(28);
				else return 0;
			}
			else return 0;
		}
	}

go38: {// 158 267 349 ig=38 
		for (int i = 0, j = s3d; i < 3; i++, j++) {
			register int vy = gb3[j];
			if (vy & m5) {//158
				c7n = j;
				m1 = vy & m12; if (!m1) return 0;
				m8 = vy & m89; if (!m8) return 0;
			}
			else if (vy & m6) {//267
				c8n = j; if (!(vy & m7)) return 0;
				m2 = vy & m12; if (!m2) return 0;
			}
			else {//349
				c9n = j; if (!(m4 & vy)) return 0;
				if (!(vy & m3)) return 0;
				m9 = vy & m89;	if (!m9) return 0;
			}
		}
		return ValidGangMinlex(38);	
	}
	return 0;
}

/*
  134 258 679 ig=29 = 2 2 2	6
  134 268 579 ig=30 = 2 2 3	7
  135 268 479 ig=31 = 2 2 2	6
  135 278 469 ig=32 = 2 3 2	7
  136 258 479 ig=33 = 2 2 0	4
  136 278 459 ig=34 = 2 3 0	5
  137 268 459 ig=35 = 2 2 2	6
  138 259 467 ig=36 = 2 2 0	4
  138 269 457 ig=37 = 2 2 2	6

*/

int GANGMINLEX::Go9_39_42() {
	c1n = gopa.c1; c4n = gopa.c2;
	int s1 = c1n / 3, s2 = c4n / 3, s3 = 3 - s1 - s2,
		s1d = 3 * s1, s2d = 3 * s2, s3d = 3 * s3;
	int v125678 = gop[0].v | gop[1].v | gop[2].v, v349 = 0x1ff ^ v125678;
	m12 = gopa.v; m123 = gb3[c1n];
	m3 = m123 & v349; m4 = gb3[c4n] & v349; m9 = v349 & ~(m3 | m4);
	int v56, v78;
	// look for 378 in stack 2
	for (int i = 0, j = s2d; i < 3; i++, j++) {
		register int vy = gb3[j];
		if (!(vy & m3)) continue;
		v78 = vy & ~m3;	c5n = j;	break;
	}
	v56 = v125678 & ~(m12 | v78);
	// find missing columns stacks 1 and 2
	{
		int ns = 3 + 3 * s2d;// sum of the columns of the stack 3
		c6n = ns - c4n - c5n;
		for (int i = 0, j = s1d; i < 3; i++, j++) {
			register int vy = gb3[j];
			if (vy & v56) c2n = j;
			else if (vy & v78) c3n = j;
		}
	}

	// now check stack3 depending on the gang(s) expected
	if (nt2x2 == 3)goto gog42;
	else if (nt2x2 == 6) goto gog40;
	// now can be /129 356 478 igang=39 137 245 689 igang=41
	{ 
		int cx3n, v3n, cx4n, v4n, cx9n, v9n;
		for (int i = 0, j = s3d; i < 3; i++, j++) {
			register int vy = gb3[j];
			if (vy & m3) {	cx3n = j; v3n = vy; }
			else if (vy & m4) { cx4n = j; v4n = vy; }
			else if (vy & m9) { cx9n = j; v9n = vy; }
			else return 0;
		}
		if (cx3n == cx4n || cx3n == cx9n || cx4n == cx9n) return 0;
		if (v9n & v56) {//	137 245 689 igang = 41
			c7n = cx3n; c8n = cx4n; c9n = cx9n;
			m1 = v3n & m12; m2 = v4n & m12;
			m5 = v4n & v56; m6 = v9n & v56;
			m7 = v3n & v78; m8 = v9n & v78;
			return ValidGangMinlex(41);
		}
		else {//129 356 478 igang=39
			c7n = cx9n; c8n = cx3n; c9n = cx4n;
			if ((m12 & v9n) != m12) return 0;
			{SPLIT2(m12,m1, m2)}
			if ((v56 & v3n) != v56) return 0;
			{SPLIT2(v56, m5, m6)}
			{SPLIT2(v78, m7, m8)}
			return ValidGangMinlex(39);
		}
	return 0; 
	}
gog40: {//135 279 468 igang=40 
	{
		for (int i = 0, j = s3d; i < 3; i++, j++) {
			register int vy = gb3[j];
			if (vy & m3) {//135
				m5= vy & v56;
				c7n = j; m1 = vy & m12; if (!m1) return 0;
			}
			else if (vy & m9) {//279
				c8n = j; 
				m7 = vy & v78; m2 = vy & m12;
				if ((!m2) ||(!m7)) return 0;
			}
			else {//468
				c9n = j; if (!(m4 & vy)) return 0;
				m6 = vy & v56; m8 = vy & v78;
				if ((!m6) || (!m8)) return 0;
			}
		}
	}
	return ValidGangMinlex(40);
	}
gog42: {//157 268 349 igang=42 
		{
			int n = 0;
			for (int i = 0, j = s3d; i < 3; i++, j++) {
				int vy = gb3[j];
				if (vy & v349)  c9n = j;
				else if (n) {//268
					c8n = j;
					m2 = vy & m12; m6 = vy & v56; m8 = vy & v78;
				}
				else {//157
					n++; c7n = j;
					m1 = vy & m12; m5 = vy & v56;  m7 = vy & v78;
				}
			}
		}
		return ValidGangMinlex(42);
	}// end go 42
	return 0;
}

void GANGMINLEX::Go9_43() {//123 456 789 147 258 369 159 267 348	
	// use first stack as start an set m1 m2 m3
	{
		c1n = 0; c2n = 1; c3n = 2;
		m123 = gb3[0]; m456 = gb3[1]; m789 = gb3[2];
		{  SPLIT2(m123, m1, m3)}
		m2 = m123 & ~(m1 | m3);
	}
	// find columns match in  stack2 3
	int v14759 = 0, v25867 = 0, v36948 = 0;
	int vx = 0x1ff & ~m123;
	{
		for (int i = 3; i < 9; i++) {
			register int v = gb3[i];
			if (v & m1)  v14759 |= v;
			else if (v & m2)  v25867 |= v;
			else v36948 |= v;
		}
	}
	int v68 = vx & ~v14759, v49 = vx & ~v25867,
		v57 = vx & ~v36948;
	// find m4 to m9
	{
		register int r = m456;
		m4 = r & v49; m5 = r & v57; m6 = r & v68;
		r = m789;
		m9 = r & v49; m7 = r & v57;  m8 = r & v68;
	}
	// find columnns
	{
		register int v147 = m1 | m4 | m7, v258 = m2 | m5 | m8,
			v369 = m3 | m6 | m9, v159 = m1 | m5 | m9,
			v267 = m2 | m6 | m7, v348 = m3 | m4 | m8;
		for (int i = 3; i < 9; i++) {
			int v = gb3[i];
			if (v == v147) c4n=i;
			else if (v == v258) c5n = i;
			else if (v == v369) c6n = i;
			else if (v == v159) c7n = i;
			else if (v == v267) c8n = i;
			else  c9n = i;
		}
	}
	ValidGangMinlex(43);
}
int SkgGetGang(int* g27) {
	gangminlex.Init(g27);
	return gangminlex.igang;
}
int SkgGetFills(int igang, const char*** tfill) {
	register int j = tfill_index[igang];
	*tfill  = &t44fills[j];
	return (tfill_index[igang + 1] - j);
}
int SkgBuildMorphedTableSortedOver(int ib1) {
	int istart = tfill_index[gangminlex.igang], 
		iend = tfill_index[gangminlex.igang + 1],
	    nokindex = 0;
	for (int i = istart; i < iend; i++) {
		int bd = tfillband[i];
		if (bd < ib1) continue;
		const char* cx = t44fills[i];
		int b3morphed[27];
		for (int i = 0; i < 9; i++) {
			int c = gangminlex.revcmap[i];
			int* m = gangminlex.revdmap;
			int v = cx[c] - '1';
			b3morphed[i] = m[cx[c] - '1'];
			b3morphed[i + 9] = m[cx[c + 9] - '1'];
			b3morphed[i + 18] = m[cx[c + 18] - '1'];
		}
		BandReOrder(b3morphed);
		tfillbandid[nokindex] = bd;
		memcpy(tfillbandmorphed[nokindex++], b3morphed, 4 * 27);
	}
	if (!nokindex)return 0;

	if (nokindex > 1)SortBandsMorphed(nokindex);
	else tfillorder[0] = 0;
	return nokindex;
}
int* Skg_GetMorphedOrdered(int i,int * bandid) {
	register int j = tfillorder[i];
	*bandid = tfillbandid[j];
	return tfillbandmorphed[j];}
