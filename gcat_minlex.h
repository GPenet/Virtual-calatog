//skbminlex.h - band mapping and UAs list
#pragma once
// ________________________ select what has to be loaded in sk0__h.h
//#define SK0FDEBUGGING
//#define SK0FFLOORS
//#define SK0FLOOKUP
//#define SK0FSMALLBANDFUNCTIONS
//#define SK0FOTHERS
//#define SK0FSYMMETRY
//#define SK0FMISCLOOKUP
// SK0FT128 contains include sk_bitfield.h
//#define SK0FT128
#define SK0FTPERMBASE
//#define SK0FTPERM1296
// "obsolete combine cell-fix vv9
//#define SK0FZZ
#include "sk0__h.h"
#include "sk0_loads_cpp.h"
#include "skb_permband.h"



/*
// ======  morphing a band
int GcatGetBandIndex(int* b0, int band1_index);

This is the special morphing of a band used in the virtual catalog;

The band index is of interest only if it is the same as the current band 1 index.
If it is lower, the branch is dead, all fills to come would not be minimal
If it is higher, all fills to come must be checked, but the mapping is not needed.

The band 1 index is the parameter "band1_index"
The return code is -1;0;+1 
-1 he band index is lower than "band1_index"
0 the band index is equal to "band1_inde".  
               The mapping is available in the BMINLEX structure
1 the band index is higher than "band1_index"

Note : a dummy "band1_inde" equal to the expected band index 
   is used in tests to force the mapping

//===== getting the mapping and using it
If the mapping is done (band index equal to "band1_inde", 
  it is available in a permanent BANPERM struct.
The BANDPER pointer is given (usually called once) through 

BANDPERM * GcatGetMappingPointer();  

The user must use the file Banperm.h or any equvalent code to map the band is necessary.

*/
// ======  morphing a band
//extern "C" __declspec(dllexport) int GcatGetBandIndex(int* b0, int band1_index);
// Get mapping pointer 
//extern "C" __declspec(dllexport) BANDPERM* GcatGetMappingPointer();
/*
// ======= getting auto morphs
extern "C" __declspec(dllexport) int GcatGetAutoMorphs(int bandid, BANDPERM * *tpermret);

// ======== Getting a band and  UAs of a band
extern "C" __declspec(dllexport) void GcatGetBandChar(int bandid, char* bchar27);
*/