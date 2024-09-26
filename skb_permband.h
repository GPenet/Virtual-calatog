#pragma once

struct BANDPERM {
	int i416;
	int rows[3], cols[9], map[9];
	inline void InitBase(int i16 = 0) {
		i416 = i16;
		for (int i = 0; i < 9; i++)		cols[i] = map[i] = i;
		for (int i = 0; i < 3; i++)		rows[i] = i;
	}
	void Morph(int* s, int* d) {
		for (int irow = 0; irow < 3; irow++) {
			int drow = 9 * irow;
			for (int icol = 0; icol < 9; icol++)
				d[drow + icol] = map[s[drow + cols[icol]]];
		}
	}
	void MorphOrdered(int* s, int* d) {
		for (int irow = 0; irow < 3; irow++) {
			int drow = 9 * irow;
			for (int icol = 0; icol < 9; icol++)
				d[drow + icol] = map[s[drow + cols[icol]]];
		}
		int temp[9];// now reorder
		if (d[0] > d[9]) {
			memcpy(temp, &d[0], sizeof temp);
			memcpy(&d[0], &d[9], sizeof temp);
			memcpy(&d[9], temp, sizeof temp);
		}
		if (d[0] > d[18]) {
			memcpy(temp, &d[0], sizeof temp);
			memcpy(&d[0], &d[18], sizeof temp);
			memcpy(&d[18], temp, sizeof temp);
		}
		if (d[9] > d[18]) {
			memcpy(temp, &d[9], sizeof temp);
			memcpy(&d[9], &d[18], sizeof temp);
			memcpy(&d[18], temp, sizeof temp);
		}
	}
	int CheckValid() {// should be a debugging sequence
		register int vr = 0,vc=0,vd=0;
		for (int i = 0; i < 3; i++)vr |= 1 << rows[i];
		for (int i = 0; i < 9; i++) {
			vc |= 1 << cols[i];
			vd |= 1 << map[i];
		}
		if (vr != 7 || vc != 0777 || vd != 0777) return 1;
		return 0;
	}
	void BuilCellsMap( int* d) {
		for (int irow = 0; irow < 3; irow++) {
			int drow = 9 * irow,drowm=9*rows[irow];
			for (int icol = 0; icol < 9; icol++)
				d[drow + icol] = drowm + cols[icol];
		}

	}
	int MorphCompare(int* s, int* t) {
		int d0 = map[s[cols[0]]];
		int d9 = map[s[9 + cols[0]]];
		int d18 = map[s[18 + cols[0]]];
		int r1 = 0, r2 = 0, r3 = 0;
		int j;

#define FOO(X,Y,Z) \
        if (d##X<d##Y && d##X<d##Z) { \
          if (d##X<t[0]) return -1; else if (d##X>t[0]) return 1; \
          r1=X; if (d##Y<d##Z) { r2=Y; r3=Z; } else { r2=Z; r3=Y; } \
        }
		FOO(0, 9, 18) else FOO(0, 18, 9) else
			FOO(9, 0, 18) else FOO(9, 18, 0) else
			FOO(18, 0, 9) else FOO(18, 9, 0)
#undef FOO

			for (j = 1; j < 9; j++) {
				int x = map[s[r1 + cols[j]]];
				if (x < t[j]) return -1; else if (x > t[j]) return 1;
			}
		for (j = 0; j < 9; j++) {
			int x = map[s[r2 + cols[j]]];
			if (x < t[9 + j]) return -1; else if (x > t[9 + j]) return 1;
		}
		for (j = 0; j < 9; j++) {
			int x = map[s[r3 + cols[j]]];
			if (x < t[18 + j]) return -1; else if (x > t[18 + j]) return 1;
		}

		return 0;
	}
#ifdef SK0FDEBUGGING
	void Dump() {
		cout << "perm status i416=" << i416 << endl;
		cout << "rows " << rows[0] << rows[1] << rows[2] << endl;
		cout << "cols " << cols[0] << cols[1] << cols[2]
			<< cols[3] << cols[4] << cols[5] << cols[6]
			<< cols[7] << cols[8] << endl;
		cout << "digs " << map[0] << map[1] << map[2]
			<< map[3] << map[4] << map[5] << map[6]
			<< map[7] << map[8] << endl;
	}
#endif
};
