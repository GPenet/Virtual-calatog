
void Go_10() {
	memset(p_cpt2g, 0, sizeof p_cpt2g);
	cout << "hello from go-10" << endl;
	for (int ig = 0; ig < 44; ig++) {// 44 gangsters
		//if (ig < 19) continue;
		//if (ig !=40) continue;
		//if (ig >15) continue;
		const char* myg = t44g[ig];
		for (int i = 0; i < 27; i++) {
			cout << myg[i]; if (i == 8 || i == 17) cout << "  ";
		}
		cout << "igang=" << ig << endl;
		int d0[27], d1[27];
		for (int i = 0; i < 27; i++) d0[i] = myg[i] - '1';
		//for(int i=0;i<10000;i++)
		gangminlex.Initt(myg, 0);
		p_cpt2g[19] = 0;
		for (int ic = 0; ic < 1296; ic++) {
			int* cc = tpermorder[ic];
			for (int i = 0; i < 9; i++) {
				int j= cc[i];
				memcpy(&d1[3 * i], &d0[3 * j], 12);// 3 int
			}
			gangminlex.Init(d1,0);
		}
		cout << p_cpt2g[19] << " hit for 1296 ig=" << ig << endl;
		if (p_cpt2g[19] != 1296) {
			cout << "error" << endl; return;
		}

	}
}

void Go_11() {
	memset(p_cpt2g, 0, sizeof p_cpt2g);
	cout << "hello from go-11" << endl;
	for (int ig = 0; ig < 44; ig++) {// 44 gangsters
		//if (ig < 19) continue;
		//if (ig !=40) continue;
		//if (ig >15) continue;
		const char* myg = t44g[ig];
		for (int i = 0; i < 27; i++) {
			cout << myg[i]; if (i == 8 || i == 17) cout << "  ";
		}
		cout << "igang=" << ig << endl;
		int d0[27];
		for (int i = 0; i < 27; i++) d0[i] = myg[i] - '1';
		int igr = SkgGetGang(d0);
		if (igr != ig) {
			cout << "error get igr" << endl;
			return;
		}
		const char** tfill;
		int nfills= SkgGetFills(igr,& tfill);
		cout << " expected nfills" << nfills << endl;
		//for (int i = 0; i < nfills; i++)cout << tfill[i] << endl;
		//gangminlex.Init(d0, 0);
		cout << p_cpt2g[19] << " hit  ig=" << ig << endl;
	}
}



#include "C:\_cinc\skb_permband.h"

BANDPERM perms94[4] = {
{0,{2,0,1},{8,6,7,0,1,2,5,4,3},{8,7,6,5,4,3,2,1,0}},
{0,{0,1,2},{1,0,2,4,3,5,7,6,8},{1,0,2,4,3,5,7,6,8}},
{0,{0,1,2},{2,0,1,5,3,4,8,6,7},{1,2,0,4,5,3,7,8,6}},
{0,{0,1,2},{1,2,0,4,5,3,7,8,6},{2,0,1,5,3,4,8,6,7}},
};

void Go_12() {
	memset(p_cpt2g, 0, sizeof p_cpt2g);
	cout << "hello from go-12 go" << endl;
	for (int ig = 0; ig < 44; ig++) {// 44 gangsters
		const char* myg = t44g[ig];
		for (int i = 0; i < 27; i++) {
			cout << myg[i]; if (i == 8 || i == 17) cout << "  ";
		}
		cout << "igang=" << ig << endl;
		int d0[27],d1[27];
		for (int i = 0; i < 27; i++) d0[i] = myg[i] - '1';
		for (int ic = 0, icr = 8; ic < 9; ic++, icr--) {
			memcpy(&d1[3 * icr], &d0[3 * ic], 12);
		}
		//perms94[2].Morph(d0, d1);
		for (int i = 0; i < 27; i++) cout<< d1[i]+1;
		cout << "morphed checked" << endl;
		int igr = SkgGetGang(d1);
		if (igr != ig) {
			cout << "error get igr" << endl;
			return;
		}
		else gangminlex.DumpMappingN();
		int nvalid= SkgBuildMorphedTableSortedOver(sgo.vx[0]);
		cout << " expected nvalid " << nvalid << endl;
		for (int i = 0; i < nvalid; i++) {
			if (i > 4) break;
			int* bandr,bandid;
			bandr=Skg_GetMorphedOrdered(i, &bandid);
			cout << bandid << " retour i " << i<<" ";
			BandDump(bandr, " ");
		}
		//	cout << tfill[i] << endl;
		//gangminlex.Init(d0, 0);
		cout << p_cpt2g[19] << " hit  ig=" << ig << endl;
	}
}
void PermBands(char* z163, int* pi1, int* pi2, int i1, int i2) {
	register int ix = *pi1; *pi1 = *pi2; *pi2 = ix;
	char temp[27];
	memcpy(temp, &z163[27 * i1], 27);
	memcpy(&z163[27 * i1], &z163[27 * i2], 27);
	memcpy(&z163[27 * i2], temp, 27);
	memcpy(temp, &z163[27 * i1 + 82], 27);
	memcpy(&z163[27 * i1 + 82], &z163[27 * i2 + 82], 27);
	memcpy(&z163[27 * i2 + 82], temp, 27);
}
