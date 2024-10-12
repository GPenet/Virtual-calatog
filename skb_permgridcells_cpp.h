#pragma once


void GRIDPERM::Export(char* w) {
	w[0] = transpose + '0';
	for (int i = 0; i < 9; i++) {
		w[i + 1] = rows[i] + '1';
		w[i + 10] = cols[i] + '1';
	}
}


void GRIDPERM::Import19(int* g0, char* x19) {
	transpose = x19[0] - '0';
	for (int i = 0; i < 9; i++) {
		rows[i] = x19[i + 1] - '1';
		cols[i] = x19[i + 10] - '1';
	}
	// must do the digit mapping on morphed row 1
	int w[81];
	if (transpose) {// transpose before 
		for (int i = 0; i < 81; i++)w[i] = g0[C_transpose_d[i]];
	}
	else  memcpy(w, g0, sizeof w);
	// morph row 0
	register int  drows = 9 * rows[0];
	for (int icol = 0; icol < 9; icol++)
		map[w[drows + cols[icol]]] = icol;

}
void GRIDPERM::Import( int transp,BANDPERM& p, int* rr) {
	transpose = transp;
	memcpy(cols, p.cols, sizeof cols);
	memcpy(rows, rr, sizeof rows);
	memcpy(map, p.map, sizeof map);
}
void GRIDPERM::Morph(int* s, int* d) {
	int w[81];
	if (transpose) {// transpose before 
		for (int i = 0; i < 81; i++)w[i] = s[C_transpose_d[i]];
	}
	else  memcpy(w, s, sizeof w);
	for (int irow = 0; irow < 9; irow++) {
		register int drow = 9 * irow, drows = 9 * rows[irow];
		for (int icol = 0; icol < 9; icol++)
			d[drow + icol] = map[w[drows + cols[icol]]];
	}
}


#ifdef SK0FDEBUGGINGBAND

void GRIDPERM::Dump() {
	cout << "gridperm transpose=" << transpose << endl;
	for (int i = 0; i < 9; i++) cout << rows[i]; cout << " rows" << endl;
	for (int i = 0; i < 9; i++) cout << cols[i]; cout << " cols" << endl;
	for (int i = 0; i < 9; i++) cout << map[i]; cout << " maps" << endl;
}
#endif



void GRIDPERMCELLS::Build(GRIDPERM& pg) {
	for (int irow = 0; irow < 9; irow++) {
		int drow = 9 * irow, drowm = 9 * pg.rows[irow];
		for (int icol = 0; icol < 9; icol++)
			cells[drow + icol] = drowm + pg.cols[icol];
	}
	memcpy(map, pg.map, sizeof map);
	if (pg.transpose) {// transpose after 
		int w[81]; memcpy(w, cells, sizeof w);
		for (int i = 0; i < 81; i++)cells[i] = w[C_transpose_d[i]];
	}
}
void GRIDPERMCELLS::Build2(GRIDPERM& pg1, GRIDPERM& pg2) {
	GRIDPERMCELLS wp1,wp2;
	wp1.Build(pg1); wp2.Build(pg2);
	// now do x=>y=>z 
	for (int i = 0; i < 9; i++) map[i] = wp2.map[wp1.map[i]];
	for (int i = 0; i < 9; i++) cells[i] = wp1.cells[wp2.cells[i]];
}
