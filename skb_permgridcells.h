#pragma once
//#include  "bandperm.h"
struct GRIDPERM {
	int transpose;
	int rows[9], cols[9], map[9];
	void Export( char * w);
	void Import( int transp,BANDPERM & p, int* rr);
	void Import19(int *g0,char *x19);
	void Morph(int* s, int* d);
#ifdef SK0FDEBUGGINGBAND
	void Dump();
#endif
};
struct GRIDPERMCELLS {	
	int cells[81], map[9];
	void Build(GRIDPERM& pg);// see skggrid_minlex_cpp
	void Build2(GRIDPERM& pg1, GRIDPERM& pg2);
	void Morph(int* s, int* d);
#ifdef SK0FDEBUGGINGBAND
	void Dump();
#endif
};
