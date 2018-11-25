
#ifndef __AQUA__LIB_STRING_STRINDEX_H
	#define __AQUA__LIB_STRING_STRINDEX_H
	
	#include "../../root.h"
	
	#define __lib_function_strindex_get_aligned_and_offset(index) \
		var aligned =  index          >> 3; \
		var offset  = (index & 0b111) << 3; \
	
	chr strindex(uchr string[notnull], var index) {
		lib(strindex_get_aligned_and_offset)(index);
		return (string[aligned] >> offset) & 0xFF;
		
	}
	
#endif
