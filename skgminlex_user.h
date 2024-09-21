//skgminlex_user.h - gand mapping and gang fills
#pragma once


/*
//=============== find the ganster id
int SkgGetGang(int* g27);
the gangster is defined in a 27 table of values 0-8 
In fact, it is 9 triplets, one for each column, each triplet sorted in increasing value of the three digits.
eg 123 456 789 if the first box for the gangster gangster is

147
258
369

the value returned is the index 0-43 of the gangster

//================ get the table of fills for a gangster
int SkgGetFills(int igang, const char** tfill);
Once the gangster id known (0-43) 
Get access to the table of fills
const char** tfill) get the pointer to the first item of the gangster 
the return vamue is the number of items

// ======  select  valid fills for a given band 1, morph and sort
int SkgBuildMorphedTableSortedOver(int ib1)

designed for the virtual catalog 
where fills with a band index lower than the band 1 index can be ignored,
but giving a band index <=0 delivers the full table of fills, morphed and sorted.
This must follow a call to SkgGetGang (using the results of the mapping)
The table is stored in the DLL, the return value is the numver of fills valid.
Access to the table is through Skg_GetMorphedOrdered

As all parameters have been defined in the SkgGetGang call, 
the only parameter of this call is the band 1 index (0-415)


 //============ getting one item of the valid fills.
 int* Skg_GetMorphedOrdered(int i,int * bandid)

 Acess to one valid fills has 2 results:
 the pointer to the int [27] band (digits 0-8)
 the band index

 i is the item index in the DLL table
 bandid is the pointer to the band id sent back
 and the return value is the pointer to the int [27]


*/
extern "C" __declspec(dllimport) int SkgGetGang(int* g27);
extern "C" __declspec(dllimport) int SkgGetFills(int igang, const char*** tfill);
extern "C" __declspec(dllimport) int SkgBuildMorphedTableSortedOver(int ib1);
extern "C" __declspec(dllimport) int* Skg_GetMorphedOrdered(int i, int* bandid);
