//skbminlex.h - band mapping and UAs list
#pragma once
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdlib.h>
using namespace std;

//====================platform-specific settings
#include <inttypes.h>
#include <limits.h>
#ifdef   _MSC_VER
#include <intrin.h>
#else
#include <immintrin.h>
#endif

#ifdef   _MSC_VER
#define _popcnt64(a) __popcnt64(a)
#define _popcnt32(a) __popcnt(a)
#define bitscanforward(A,B) _BitScanForward((unsigned long*)& A, B)
#define bitscanforward64(A,B) _BitScanForward64((unsigned long*)& A, B)
#define bitscanreverse(A,B) _BitScanReverse((unsigned long*)& A, B)
#define bitscanreverse64(A,B) _BitScanReverse64((unsigned long*)& A, B)

#else
#define _popcnt64(a) __builtin_popcountll(a)
#define _popcnt32(a) __builtin_popcount(a)
#define bitscanforward64(res, src) (!(uint64_t)(src) ? 0 : ((res = __builtin_ctzll(src)), 1))
#define bitscanforward(res, src)   (!(uint32_t)(src) ? 0 : ((res = __builtin_ctz(src)), 1))
#define bitscanreverse64(res, src) (!(uint64_t)(src) ? 0 : ((res = __builtin_clzll(src) ^ 63), 1))
#define bitscanreverse(res, src)   (!(uint32_t)(src) ? 0 : ((res = __builtin_clz(src) ^ 31), 1))
#endif

typedef unsigned char byte;
typedef unsigned short word;
typedef unsigned short int  USHORT;
typedef unsigned int UINT;
typedef unsigned long ULONG;
typedef unsigned char UCHAR;
#include "skb_permband.h"
#include "skb_bminlex_struct.h"


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
extern "C" __declspec(dllexport) void SkbGetMappingChar(   const char * a, BANDPERM *  b);
extern "C" __declspec(dllexport) void SkbGetMappingInt(   int* a, BANDPERM * b);

// ======= getting auto morphs 
extern "C" __declspec(dllexport) int SkbGetAutoMorphs(int bandid, BANDPERM** tpermret);

// ======== Getting a band and  UAs of a band
extern "C" __declspec(dllexport) void SkbGetBandChar(int bandid, char* bchar27);
extern "C" __declspec(dllexport) int SkbGetUas(int bandid, int** tuas_ret);
