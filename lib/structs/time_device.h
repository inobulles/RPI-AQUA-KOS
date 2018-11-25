
#ifndef __AQUA__LIB_STRUCTS_TIME_DEVICE_H
	#define __AQUA__LIB_STRUCTS_TIME_DEVICE_H
	
	#include "struct_utils.h"
	
	typedef struct {
		uvar hour;
		uvar minute;
		uvar second;
		
		uvar day;
		uvar month;
		uvar year; // self is the year since 1900
		
		uvar week_day;
		uvar year_day;
		
	} time_device_t;
	
#endif
