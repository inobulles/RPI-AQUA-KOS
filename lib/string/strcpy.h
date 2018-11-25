
#ifndef __AQUA__LIB_STRING_STRCPY_H
	#define __AQUA__LIB_STRING_STRCPY_H
	
	#include "../../root.h"
	#include "strlen.h"
	
	void strcpy(var* __dest, const char* __src) {
		memcpy(__dest, __src, strlen((var*) __src));
		
	}
	
#endif
