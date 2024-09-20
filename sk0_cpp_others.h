const char *  empty_puzzle=".................................................................................";
const char *  puzstart="12345678945................2.....................................................";

char * Blancs(int n,int no)
 {static char wt[]="___________________ ",
              wn[]="                    ";
              if(no)return &wn[20-n]; else return &wt[20-n];}

void Sort_uint32_t(uint32_t * t, uint32_t nt) {
	for(uint32_t i=0;i<nt-1;i++)
		for(uint32_t j=i+1;j<nt;j++)
			if (t[i] > t[j]) {
				uint32_t temp=t[i];
				t[i] = t[j];
				t[j] = temp;
			}
}

int AddUA64(uint64_t * t, uint32_t & nt,uint64_t ua) {// ua 2x27  + 5 bit length
	register uint64_t ua2x = ua & BIT_SET_2X;
	for (uint32_t iua = 0; iua < nt; iua++) {
		register uint64_t R = t[iua];
		if (R < ua) {// is it subset
			R &= BIT_SET_2X;
			if ((R&ua2x) == R) return 0;// we have a subset
		}
		else if (R == ua) return 0;
		else {
			for (uint32_t jua = nt; jua > iua; jua--)t[jua] = t[jua - 1];
			t[iua] = ua;// new inserted
			nt++;
			// is it a subset of a previous entry
			for (iua++; iua < nt; iua++) {
				if ((t[iua] & ua2x) == ua2x) {// we have a subset
					for (uint32_t k = iua + 1; k < nt; k++)t[k - 1] = t[k];
					nt--;
					iua--; //continue same position
				}
			}
			return 2;
		}
	}
	t[nt++] = ua;// added
	return 1;
}

int AddUA32(uint32_t * t, uint32_t & nt, uint32_t ua) {// ua1x27  + 5 bit length
	register uint32_t ua1x = ua & BIT_SET_27;
	for (uint32_t iua = 0; iua < nt; iua++) {
		register uint32_t R = t[iua];
		if (R < ua) {// is it subset
			R &= BIT_SET_27;
			if ((R&ua1x) == R) return 0;// we have a subset
		}
		else if (R == ua) return 0;
		else {
			for (uint32_t jua = nt; jua > iua; jua--)t[jua] = t[jua - 1];
			t[iua] = ua;// new inserted
			nt++;
			// is it a subset of a previous entry
			for (iua++; iua < nt; iua++) {
				if ((t[iua] & ua1x) == ua1x) {// we have a subset
					for (uint32_t k = iua + 1; k < nt; k++)t[k - 1] = t[k];
					nt--;
					iua--; //continue same position
				}
			}
			return 2;
		}
	}
	t[nt++] = ua;// added
	return 1;
}

int AddUA32NoSubset(uint32_t * t, uint32_t & nt, uint32_t ua) {// ua1x27  + 5 bit length
	register uint32_t ua1x = ua & BIT_SET_27;
	for (uint32_t iua = 0; iua < nt; iua++) {
		register uint32_t R = t[iua];
		if (R < ua) continue;
		else if (R == ua) return 0;
		else {
			for (uint32_t jua = nt; jua > iua; jua--)t[jua] = t[jua - 1];
			t[iua] = ua;// new inserted
			nt++;
			return 2;
		}
	}
	t[nt++] = ua;// added
	return 1;
}

