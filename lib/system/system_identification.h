
#ifndef __AQUA__LIB_SYSTEM_SYSTEM_IDENTIFICATION_H
	#define __AQUA__LIB_SYSTEM_SYSTEM_IDENTIFICATION_H
	
	#include "../../root.h"
	
	void system_identification(void) {
		printf("\nIdentifing system ...\n");
		var platform_info = get_platform();
		
		printf("OS properties:\n");
		
		printf("\nIs known?: %s\n", platform_info & PLATFORM_KNOWN ? "yes" : "no");
		printf("Version: %d bit\n", platform_info & PLATFORM_64BIT ? 64 : 32);
		printf("Is mobile?: %s\n", platform_info & PLATFORM_MOBILE ? "yes" : "no");
		
		printf("\nIs custom AQUA kernel?: %s\n", platform_info & PLATFORM_CUSTOM ? "yes" : "no");
		printf("Is Unix-based?: %s\n", platform_info & PLATFORM_UNIX ? "yes" : "no");
		printf("Is Windows-based?: %s\n", platform_info & PLATFORM_WINDOWS ? "yes" : "no");
		printf("Is cancerous (Apple)?: %s\n", platform_info & PLATFORM_CANCER ? "yes, stay away" : "thank god, no");
		
	}
	
#endif
