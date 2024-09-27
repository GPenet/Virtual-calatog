
extern const char* t416[416];
extern int GcatGetBandIndex(int* b0, int band1_index);
extern BANDPERM* GcatGetMappingPointer();
void GetBand1(int iw, char* bc27, int* g27) {
	memcpy(bc27, "12345678945", 11);
	memcpy(&bc27[11], t416[iw], 16);
	for (int i = 0; i < 27; i++) {
		g27[i] = bc27[i] - '1';
		cout << g27[i] + 1;
	}
	cout << "band index " << iw << endl;
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

void InitBand1(int iw, int* g) {
	char band[28]; band[27] = 0;
	memcpy(band, "12345678945", 11);
	memcpy(&band[11], t416[iw], 16);
	band[27] = 0;
	cout << band << " band index " << iw << endl;
	for (int i = 0; i < 27; i++) {
		g[i] = band[i] - '1';
	}
}

void Go_10() {
	int g[27];
	int cpt = 0;
	BANDPERM* mypout = GcatGetMappingPointer();

	for (uint32_t ib = 0; ib <= 415; ib++) {
		InitBand1(ib, g);
		int ibr = GcatGetBandIndex(g, ib);
		if (ibr) {
			cout << ib << " erreur retour " << ibr << endl;
			return;
		}
		else {
			//cout << " band " << ib << " good" << endl;
			//mypout->Morph(g, g2);
			//BandDump(g2, "entry morphed");
		}
		ibr = GcatGetBandIndex(g, ib-1);
		if(ibr<=0)cout << " r over " << ibr << endl;
		ibr = GcatGetBandIndex(g, ib + 1);
		if (ibr >= 0)cout << " r below " << ibr << endl;


	}
}
void Go_11() {
	memset(p_cpt2g, 0, sizeof p_cpt2g);
	cout << "hello from go-11" << endl;
	char bc[28]; bc[27] = 0;
	int b0[27],b1[27];
	BANDPERM* mypout= GcatGetMappingPointer();
	//BMINLEX* mybmlw = GcatGetBminlex();
	for (uint32_t i = 0; i < 5; i++) {
		memcpy(bc, tbugs[i], 27);
		for (int i = 0; i < 27; i++) {
			b0[i] = bc[i] - '1';
			cout << b0[i] + 1;
		}
		int ib = tbugsid[i];
		cout << "band to see index " <<ib << endl;
		int ibr = GcatGetBandIndex(b0, ib);
		if (ibr) {
			cout << ib << " erreur retour " << ibr << endl;
			//mybmlw->Status(1);
			continue;;
		}
		else {
			cout << " band " << ib << " good" << endl;
			//mybmlw->DumpMapping();
			mypout->Morph(b0, b1);
			BandDump(b1, "entry morphed");
			//mybmlw->Status(2);
		}
	};

}

int CheckPermOk(BANDPERM * p, int* s, int* r) {
	int d[27];
	p->Morph(s, d);
	int ir = BandCompare(d, r);
	if (ir) {
		BandDump(s, " source");
		BandDump(d, " morphed");
		BandDump(r, " expected");
		return 1;
	}
	return 0;
}

void Go_12() {
	memset(p_cpt2g, 0, sizeof p_cpt2g);
	cout << "hello from go-12 go" << endl;
	int g[27], g2[27];
	int cpt = 0;
	BANDPERM* mypout = GcatGetMappingPointer();

	for (uint32_t ib = 0; ib <= 415; ib++) {
		InitBand1(ib, g);
		BANDPERM pw;
		int ibr = GcatGetBandIndex(g, ib);
		//pw.Dump();
		if (ibr) {
			cout << ib << " erreur retour " << ibr << endl;
			//mybmlw->Status(1);
			continue;;
		}
		else {
			cout << " band " << ib << " good" << endl;
			//mybmlw->DumpMapping();
			mypout->Morph(g, g2);
			BandDump(g2, "entry morphed");
			//mybmlw->Status(2);
		}
		cpt = 0;
		for (int id = 0; id < 1296; id += 10) {
			int* cc = tpermorder[id];
			for (int i = 0; i < 9; i++)		pw.map[i] = cc[i];
			//cout << "id=" << id << endl;
			for (int ir = 0; ir < 6; ir++) {
				//cout << "ir=" << ir << endl;
				pw.rows[0] = tperm6[ir][0];
				pw.rows[1] = tperm6[ir][1];
				pw.rows[2] = tperm6[ir][2];
				for (int ic = 0; ic < 1296; ic++) {
					//cout << "ic=" << ic << endl;
					int* cc = tpermorder[ic];
					for (int i = 0; i < 9; i++)		pw.cols[i] = cc[i];
					cpt++;
					pw.Morph(g, g2);
					int ibr = GcatGetBandIndex(g2,ib);
					if (ibr) {
						cout << ib << " erreur retour " << ibr << endl;
						continue;;
					}
					else if(CheckPermOk(mypout, g2, g)) {
						cout << "stop ib= " << ib << " id=" << id << "ir=" << ir << " ic=" << ic << endl;
						mypout->Dump();
						return;
					}

				}
			}
		}
		cout << "n calls ok " << cpt << endl;
	}
	
}
