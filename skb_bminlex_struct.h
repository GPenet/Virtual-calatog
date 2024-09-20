//skbminlex.h - band mapping and UAs list
#pragma once

struct BMINLEX {// receive a band send back i416 and morphing data
	int minirows[9], minicols[9], cx[9], minirr[9];
	int* minir0[3], * minic0[3], * minird[3];
	BMINLEX() {
		minir0[0] = minirows; minir0[1] = &minirows[3]; minir0[2] = &minirows[6];
		minic0[0] = minicols; minic0[1] = &minicols[3]; minic0[2] = &minicols[6];
	}
	int debug;
	BANDPERM pout;
	int* b0;
	int	 goback,   bindex;
	int cmap[9], dmap[9], r3mapped[9], crit4, crit4b, critcomp;
	char r3c[10];
	int ipr, ipst, ipb1, nxcols, nx3, nx2; // perms rows stacks
	int* rr,
		r1, r2, r3, rd1, rd2, rd3, * mr1, * mr2, * mr3;
	int* px;// minicols of the perm
	int* oc1, c1n, c2n, c3n, c4n, c5n, c6n, c7n, c8n, c9n;
	int m1, m2, m3, m4, m5, m6, m7, m8, m9;
	int mc1, mc2, mc3, mc4, mc5, mc6, mc7, mc8, mc9;
	int* ss, s1, s2, s3, m123, m456, m789, m457, m689, mx89;
	int m45, m89, mx, m12;
	int r2c7, r2c8, ir2c4, ir2c7, r3c1, r3c2;
	void InitMiniRows();
	void InitMiniCols();
	void Init(int* grid);

	void I457end();
	inline void MapDigits();
	inline void EndMapping();
	void Mapping();
	int ValidMinlex(int i, int endmap = 1);

	int GetforMinlex(int* grid);

	int SetupRSC_A();
	void GoMinlex_0_30();
	void DoMapping0();
	void DoMapping1();
	void GoA_case6();
	void GoA_case71();
	void GoA_case70();
	void GoA_case8();
	void GoA_case9();


	void GoB_case6();
	void GoB_case70();
	void GoB_case71();
	void GoB_case8_3_go();
	void GoB_case8_1_go();
	void GoB_case8_2_go();

	void SetCrit(int ia);
	int GetIndex4(uint32_t* t, uint32_t v, uint32_t& r);
	int GetCrit9(uint32_t* t, uint32_t v, int i1, int i2);

	void GoB_case9_1_go();
	void GoB_case9_2_go();

	int DoMapping411();
	void T412p();
	int T412p_column367();
	void Go_412();
	void Go_413();
	void Go_414_415();
};
