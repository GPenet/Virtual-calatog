extern  const char* t416[416];
extern void SkbGetMappingChar(const char* grid, BANDPERM* mapret);
extern void SkbGetMappingInt(int* grid, BANDPERM* mapret);
extern void SkbGetBandChar(int bandid, char* bchar27);
extern int SkbGetUas(int bandid, int** tuas_ret);
extern int SkbGetAutoMorphs(int bandid, BANDPERM** tpermret);
void GetBand1(int iw, char* bc27, int* g27) {
	memcpy(bc27, "12345678945", 11);
	memcpy(&bc27[11], t416[iw], 16);
	for (int i = 0; i < 27; i++) {
		g27[i] = bc27[i] - '1';
		cout << g27[i] + 1;
	}
	cout << "band index " << iw << endl;
}

void BMINLEX::DumpMapping() {
	cout << "Mapping status perms" << ipr << ipst << " rows " << r1 << r2 << r3 << endl;
	//cout << "columns ";
	//for (int i = 0; i < 9; i++) cout << cmap[i] << ",";
	//cout << " digits ";
	//for (int i = 0; i < 9; i++) cout << dmap[i] << ",";
	//cout << endl;
	cout << "columns ";
	for (int i = 0; i < 9; i++) cout << pout.cols[i] << ",";
	cout << " digits ";
	for (int i = 0; i < 9; i++) cout <<pout.map[i] << ",";
	cout << " rows ";
	for (int i = 0; i < 3; i++) cout << pout.rows[i] << ",";
	cout << endl;
}


void BMINLEX::Status(int op) {
	cout << "setupr col perm " << ipr << ipst << " ir2c4=" << ir2c4 << endl;
	for (int i = 0; i < 9; i++) cout << dmap[i] + 1; cout << " dmap"
		<< endl;
	cout << critcomp << " " << crit4 << " " << crit4b << endl;
	if (op == 0) return;

	cout << Char9out(m123) << " m123 " << endl;
	cout << Char9out(m456) << " m456 " << endl;
	cout << Char9out(m457) << " m457 " << endl;
	cout << Char9out(mx89) << " mx89 " << endl;
	cout << Char9out(m789) << " m789 " << endl;

	cout << Char9out(m1) << " m1 " << endl;
	cout << Char9out(m2) << " m2 " << endl;
	cout << Char9out(m3) << " m3 " << endl;
	cout << Char9out(m4) << " m4 " << endl;
	cout << Char9out(m5) << " m5 " << endl;
	cout << Char9out(m6) << " m6 " << endl;
	cout << Char9out(m7) << " m7 " << endl;
	cout << Char9out(m8) << " m8 " << endl;
	cout << Char9out(m9) << " m9 " << endl;

	cout << Char9out(r2c7) << " r2c7 " << endl;
	cout << Char9out(r2c8) << " r2c8 " << endl;


	cout << c1n << c2n << c3n << c4n << c5n << c6n << c7n << c8n << c9n << " cnn " << endl;
	cout << Char9out(mc1) << " mc1 " << endl;
	cout << Char9out(mc2) << " mc2 " << endl;
	cout << Char9out(mc3) << " mc3 " << endl;
	cout << Char9out(mc4) << " mc4 " << endl;
	cout << Char9out(mc5) << " mc5 " << endl;
	cout << Char9out(mc6) << " mc6 " << endl;
	cout << Char9out(mc7) << " mc7 " << endl;
	cout << Char9out(mc8) << " mc8 " << endl;
	cout << Char9out(mc9) << " mc9 " << endl;
	if (op < 2) return;
	for(int i=0;i<9;i++	)
		cout << Char9out(cx[i]) << " cx i= "<<i << endl;

}
void InitBand1(int iw, int* g, int* colband1) {
	int gbit[81];
	char band[28];
	SkbGetBandChar(iw, band);
	band[27] = 0;
	cout << band << " band index " << iw << endl;
	for (int i = 0; i < 27; i++) {
		g[i] = band[i] - '1';
		gbit[i] = 1 << g[i];
	}
	for (int ic = 0; ic < 9; ic++)
		colband1[ic] = gbit[ic] | gbit[ic + 9] | gbit[ic + 18];
}
void InitColsBand1(int* g, int* colband1) {
	int gbit[81];
	for (int i = 0; i < 27; i++) {
		gbit[i] = 1 << g[i];
	}
	for (int ic = 0; ic < 9; ic++)
		colband1[ic] = gbit[ic] | gbit[ic + 9] | gbit[ic + 18];
}

int CheckPermOk(BANDPERM& p, int* s, int* r) {
	int d[27];
	p.MorphOrdered(s, d);
	int ir = BandCompare(d, r);
	if (ir) {
		BandDump(s, " source");
		BandDump(d, " morphed");
		BandDump(r, " expected");
		return 1;
	}
	return 0;
}

//==============================================
void Go_10() {
	memset(p_cpt2g, 0, sizeof p_cpt2g);
	cout << "hello from go-10" << endl;
	int g[27], minicols[9];
	int cpt = 0;
	for (uint32_t ib = 0; ib <= 415; ib++) {
		InitBand1(ib, g, minicols);

		BANDPERM* tauto;
		int nauto = SkbGetAutoMorphs(ib, &tauto);
		if (nauto) {
			cout << nauto << " automorphisms" << endl;
			//for (int i = 0; i < nauto; i++)
			//  tauto[i].Dump();
		}
		int* tuas, nua = SkbGetUas(ib, &tuas);
		if (nua) {
			cout << nua << " UAs for this bands" << endl;
			//for(int i=0;i<nua;i++)
			//cout << Char27out(tuas[i]) << "  ua " <<i<< endl;
		}
		BANDPERM pw;
		char cband[28];
		SkbGetBandChar(ib, cband);
		cband[27] = 0;
		SkbGetMappingChar(cband, &pw);
		pw.Dump();
		if (pw.i416 != ib) {
			cout << " bug get mapping stop" << endl;
			return;
		}
		SkbGetMappingInt(g, &pw);
		pw.Dump();
	}

}

void Go_11() {
	memset(p_cpt2g, 0, sizeof p_cpt2g);
	cout << "hello from go-11" << endl;
	int g[27], g2[27], minicols[9];
	int cpt = 0;
	for (uint32_t ib = 0; ib <= 415; ib++) {
		InitBand1(ib, g, minicols);
		BANDPERM pw, pw2;
		SkbGetMappingInt(g, &pw);
		//pw.Dump();
		if (pw.i416 != ib) {
			cout << " bug get mapping first stop" << endl;
			return;
		}
		cpt = 0;
		for (int id = 0; id < 1296; id += 10) {
			int* cc = tpermorder[id];
			for (int i = 0; i < 9; i++)		pw.map[i] = cc[i];
			for (int ir = 0; ir < 6; ir++) {
				pw.rows[0] = tperm6[ir][0];
				pw.rows[1] = tperm6[ir][1];
				pw.rows[2] = tperm6[ir][2];
				for (int ic = 0; ic < 1296; ic++) {
					int* cc = tpermorder[ic];
					for (int i = 0; i < 9; i++)		pw.cols[i] = cc[i];
					cpt++;
					pw.Morph(g, g2);
					SkbGetMappingInt(g2, &pw2);
					//pw.Dump();
					if (pw2.i416 != ib) {
						cout << " bug get mapping stop " << ir << ic << endl;
						return;
					}
					if (CheckPermOk(pw2, g2, g)) {
						cout << "stop ib= " << ib << " id=" << id << "ir=" << ir << " ic=" << ic << endl;
						pw2.Dump();
						return;
					}

				}
			}
		}
		cout << "n calls ok " << cpt << endl;
	}
}


/*

Band index 0 -- returns an incorrect transformation about 1/2 of the time.
Band index 411 -- returns "-1" for the band type, about ~1/3 of the time.
Band index 413 -- returns an incorrect transformation, about 2/3 of the time.
Band index 415 -- returns 414 for the band type (and incorrect transformation), about 2/3 of the time.

Here are some inputs that highlight the bugs:
215486739793215468486793251 (0)
369457182184362759752189364 (411)
982641357675328914341975628 (413)
287346159694851723135972468 (413)
571962483983471526462538971 (415)

*/
const char* tbugs[5] = {
	"215486739793215468486793251",
	"369457182184362759752189364",
	"982641357675328914341975628",
	"287346159694851723135972468",
	"571962483983471526462538971"
};
int tbugsid[5] = { 0,411,413,413,415 };

void Go_12() {
	memset(p_cpt2g, 0, sizeof p_cpt2g);
	cout << "hello from go-12 go" << endl;
	for (uint32_t it = 0; it < 5; it++) {
		int g[27],ib= tbugsid[it];
		for (int i = 0; i < 27; i++) {
			g[i] = tbugs[it][i] - '1';
			cout << g[i] + 1;
		}
		cout << " band in bug ib=" << ib << endl;
		BANDPERM pw;
		SkbGetMappingInt(g, &pw);
		pw.Dump();
		if (pw.i416 != ib) {
			cout << " bug get mapping first stop" << endl;
			return;
		}
		int g2[27], minicols[9];
		InitBand1(ib, g2, minicols);
		if ( CheckPermOk( pw, g, g2))  return;
	}

}
