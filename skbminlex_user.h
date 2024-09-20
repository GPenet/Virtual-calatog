//skbminlex_user.h - band mapping and UAs list
#pragma once

#include "C:\_cinc\skb_permband.h"


/*
// ======  morphing a band
void SkbGetMappingChar(   const char * a, BANDPERM *  b);
 const char * a  the given band (char b[27])
 BANDPERM *  b pointer to the return values
   1+3+9+9 int values (see the BANDPERM struct)
_____________
void SkbGetMappingInt(   int* a, &BANDPERM * b);
 same as above, the given is int a[27] filled withe the appropriate integers 0 to 9

 //============ getting from the table auto morphs  of a band
int SkbGetAutoMorphs(int bandid, BANDPERM* tpermret);
 send back the pointer to the appropriate sub table of auto morphs
 return value is the number of automorphs
 return =0 with a pointer to the top part of the table if no response
 
int bandid index 0-415 of the band
 BANDPERM** tpermret where the pointer to the first automorph must be sent

// ======== Getting a band and  UAs of a band
extern "C" __declspec(dllexport) void SkbGetBandChar(int bandid, char* bchar27);
 extract in a char b [27] the band correspondding to the index 0-415 bandid
 return 12345678945 if id is not valid
______________________
extern "C" __declspec(dllexport) int SkbGetUas(int bandid, int** tuas_ret);
	send back the pointer to the appropriate sub table of uas
	return value is the number of uas of the band
    return =0 with a pointer to the top part of the table if no response

	int bandid index 0-415 of the band
    int ** tuas_ret where the pointer to the first ua must be sent


*/
// ======  morphing a band
extern "C" __declspec(dllimport) void SkbGetMappingChar(   const char * a, BANDPERM *  b);
extern "C" __declspec(dllimport) void SkbGetMappingInt(   int* a, BANDPERM * b);

// ======= getting auto morphs 
extern "C" __declspec(dllimport) int SkbGetAutoMorphs(int bandid, BANDPERM** tpermret);

// ======== Getting a band and  UAs of a band
extern "C" __declspec(dllimport) void SkbGetBandChar(int bandid, char* bchar27);
extern "C" __declspec(dllimport) int SkbGetUas(int bandid, int** tuas_ret);
