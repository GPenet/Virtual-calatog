//skbvcminlex_user.h - band mapping for the virtual catalog
#pragma once

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
The BANDPERM pointer is given (usually called once) through 

BANDPERM * GcatGetMappingPointer();  

The user must use the file Banperm.h or any equvalent code to map the band is necessary.

*/

// ======  morphing a band
extern "C" __declspec(dllimport) int GcatGetBandIndex(int* b0, int band1_index);
// Get mapping pointer 
extern "C" __declspec(dllimport) BANDPERM* GcatGetMappingPointer();
