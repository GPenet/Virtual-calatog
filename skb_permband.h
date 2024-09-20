//skbminlex.h - band mapping and UAs list
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
		for (int i = 0; i < 3; i++)vr |= i << rows[i];
		for (int i = 0; i < 9; i++) {
			vc |= i << cols[i];
			vd |= i << map[i];
		}
		if (vr != 7 || vc != 0777 || vd != 0777) return 1;
		return 0;
	}
	void BuilCellsMap( int* d) {
		for (int irow = 0; irow < 3; irow++) {
			int drow = 9 * irow;
			for (int icol = 0; icol < 9; icol++)
				d[drow + icol] = map[drow + cols[icol]];
		}
	}

};
