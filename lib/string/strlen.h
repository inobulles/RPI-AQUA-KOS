
#ifndef __AQUA__LIB_STRING_STRLEN_H
	#define __AQUA__LIB_STRING_STRLEN_H
	
	#include "../../root.h"
	
	#define __STRLEN_MAX_LENGTH 0xFFFF
	
	var strlen(var* string) {
		var i;
		var j;
		
		for (i = 0; i < __STRLEN_MAX_LENGTH; i++) {
			for (j = 0; j < sizeof(var); j++) {
				if (!((string[i] >> (j * 8)) & 0xFF)) {
					return i * 8 + j;
					
				}
				
			}
			
		}
		
		return 0;
		
	}
	
#endif
