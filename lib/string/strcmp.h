
#ifndef __AQUA__LIB_STRING_STRCMP_H
	#define __AQUA__LIB_STRING_STRCMP_H
	
	#include "../../root.h"
	
	#define DEFAULT_LENGTH 8192
	
	var strcmp(void* _a, void* _b, var max_length) {
		if (max_length < 0) {
			max_length = DEFAULT_LENGTH;
			
		}
		
		uvar* a = (uvar*) _a;
		uvar* b = (uvar*) _b;
		
		uvar byte_a;
		uvar byte_b;
		
		var jmul;
		
		var i;
		var j;
		
		for (i = 0; i < max_length / sizeof(var); i++) {
			for (j = 0; j < sizeof(var); j++) {
				jmul = j * 8;
				
				byte_a = (a[i] >> jmul) & 0xFF;
				byte_b = (b[i] >> jmul) & 0xFF;
				
				//~ printf("\n\n%lld %lld\n\n\n", byte_a, byte_b);
				
				if (byte_a != byte_b) {
					return 1;
					
				}
				
				if (byte_a == 0) {
					if (byte_b == 0) {
						return 0;
						
					} else {
						return -1;
						
					}
					
				}
				
			}
			
		}
		
		return 0;
		
	}
	
#endif

