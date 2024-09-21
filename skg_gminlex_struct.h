  

struct GANGMINLEX {// receive a band send back i44 and morphing data
	struct PAIR_TRIPLET {
		int v, ip, c1, c2;
		inline void Enter(int ve, int ipe, int c1e, int c2e) {
			v = ve; ip = ipe; c1 = c1e; c2 = c2e;
		}
		inline void ChangeStack() {
			register int cx = c1; c1 = c2; c2 = cx;
		}
	}spairs[40],striplets[9],
		got,go3t[3],gota,gotb,gotc,gop[3],gopa,gopb,gopc;
	int gb3[9], gb3d[9][3], gdcols[9][3],g0[27],goback; 
	int tcols[9], tcols_cols[9], tcols_count[9], tcols_stk[9], ntcols,ngop ;

	int tcolss[9],  vxc[6], vxcc[6], ntcs3;
	int* tcols_dstack[3];
	GANGMINLEX() {
		tcols_dstack[0] = gb3;
		tcols_dstack[1] = &gb3[3];
		tcols_dstack[2] = &gb3[6];

	}
	int npst[3], ntst[3], isp2;

	int t2x3[3], t2x3i[3], nt2x3, t2x2[20], t2x2i[20], nt2x2;
	int dmap[9], cmap[9];
	int revdmap[9], revcmap[9],revcellmap[27];
	int cellmap[27], igang;// , stackmap[3], stackmapb[3];
	int c1n, c2n, c3n, c4n, c5n, c6n, c7n, c8n, c9n;
	int m1, m2, m3, m4, m5, m6, m7, m8, m9;
	int m123, m456, m789, m457, m689, m12x,m12;
	int m45, m89, m67;
	void SortTcols();
	inline void SetColbfNtcols();
	int NpairsStack(int ip, int s1, int s2, int n0);
	int NtripletsStack(int ip, int s1, int s2, int n0);
	void SetPairscols();
	void Settripletscols();
	void Init(int* o);
	int ValidGangMinlex(int i);

	void Go3();
	void Go5();
	void Go6();
	int Go6b();
	void Go78();
	int Go78b();

	//================ all columns different patterns
	// 123 456 789 and 124 357 689 or 124 378 569

	void Go9();
	void Go9_19_38();
	int Go9_19_38B();
	int Go9_39_42();
	void Go9_43();

};
static GANGMINLEX gangminlex;
extern "C" __declspec(dllexport) int SkgGetGang(int * g27);
extern "C" __declspec(dllexport) int SkgGetFills(int igand, const char*** tfill);
extern "C" __declspec(dllexport) int SkgBuildMorphedTableSortedOver(int ib1);
extern "C" __declspec(dllexport) int* Skg_GetMorphedOrdered(int i, int* bandid);
