# Virtual-calatog
virtual minlex catalog and DLLs used to run it
Here, I intend to deliver in the next week as a DLL  the virtual min lexical catalog of the 5 472 730 538 solution grids.
The sources are attached for anybody willing to adjust it to its own needs, but some includes are written to work with my 
directories shared organization.
The code is for an intel 64 bit set of instructions, here without use of the 128 bits registers

For each DLL, a xxxx_user;h file is given giving "import" functions and a qucik description of them

The planned content is 

================ shared  sources ================
Some files loading general pieces of code and some often used tables can be called (.h files)
sk0_cpp_floors
sk0_cpp_lookup
sk0_cpp_misc_lookup
sk0_cpp_others
sk0_cpp_symmetry
sk0_cpp_t128
sk0_cpp_tpermbase
sk0_cpp_tpermorder1296



================Bands DLL============= 
A dll giving the band index 0-415 and the mapping from the given to the min lexical morph.
This dll also contains a description of auto morphs and the minimal list of uas. 


skbminlex.dll     Dll
skbminlex_user.h  User file 
skbminlex. cpp   skb_permband.h  skb_bminlex_struct.h  skbminlex.h 


===============Gangster DLL =================
A dll giving the gangster index 0-43 and the mapping from the gangster  to the given and reverse.
This dll also contains all possible fills for a given gangster with the corresponding 0-415 index of the band.
Needed to optimize the virtual catalog, A selection and morphing of these fills is available.

not yet available

==============Band DLL for the virtual catalog==============
Variant of the Bands Dll where a quick return is done if the band index is below the band 1 index.

not yet available

skbminlex_vc.dll     Dll

================= Min Lexical morph of a given grid==================
This is a ganeral function needed here to get the rank of a solution grid given in any morph.

================= Virtual catalog.==================================



