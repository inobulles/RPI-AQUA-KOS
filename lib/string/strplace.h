
#ifndef __AQUA__LIB_STRING_STRPLACE_H
	#define __AQUA__LIB_STRING_STRPLACE_H
	
	#include "strindex.h"
	
	void strplace(uchr string[notnull], var index, chr value) {
		lib(strindex_get_aligned_and_offset)(index);
		string[aligned] = (string[aligned] & ~(0xFF << offset)) + (value << offset);
				
	}
	
#endif
