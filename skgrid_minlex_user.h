#pragma once
//skgrid_minlex_user.h - find minlex and auto morphs of a solution gris (no validity check)


/*
this DLL uses the Band mapping DLL skbminlex 

The main entry receives a valid solution grid and send back the minlex morph of the entry.
The entry can be a 81 character field
or a int x[81] where each digit is an integer 0-8 replacing the characters 1-9

If the user is interested in getting back the auto morphs permutations of the solution grid,
a first call (valid for the full run) gives the pointer to a "struct" containing
  the table of permutation giving the minlex out of the entry
  receiving the number of auto morphs
  the number of valid items 
  (first is neutral if the entry is already  minlex)
Are also sent back the main component of the analysis
  bands and stacks indexes
  vertical (band wap and horizontal (first band auto morphs )count of auto morphs
   
  To get it, it must be seen as the following structure  
  
  struct TPGC { char t[648][19]; int nt,bs_id[6],nv,nh; }*p_tpgc;
  
  and the call will return the value for the pointer p_tpgc 
  
//================ First call to get auto morphs
extern "C" __declspec(dllimport) TPGC * SkbsSetModeWithAutos();
 
TPGC * 		 return value for the pointer to the table

struct TPGC { char t[648][19]; int nt;}*p_tpgc;
p_tpgc=SkbsSetModeWithAutos();

//=============== find the min lexical 
2 calls differing by the given solution grid 
(not verified, unpredictable behaviour if it's not a valid entry )
	given is a classical char [81]
	given is a int[81] where each cell has a value 0-8
The min lexical morph is returned as a int [81]

char zc[81];
int zint [81],zret[81];

SkbsGetMinChar(zc, zret); or
SkbsGetMinChar(zint, zret);


*/
struct TPGC { char t[648][19]; int nt, bs_id[6], nv, nh;}*p_tpgc;

extern "C" __declspec(dllexport) void SkbsGetMin(int* g81s, int* g81min);
extern "C" __declspec(dllexport) void SkbsGetMinChar(char* g81sc, int* g81min);
extern "C" __declspec(dllexport) TPGC * SkbsSetModeWithAutos();

/* to come later use of the table of auto morphs 
*/
